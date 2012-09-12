// $Id: $

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>

#include "EventInfoPrinter.h"
#include "Variable.h"



EventInfoPrinter::EventInfoPrinter(const std::vector<DataSet*> &dataSets, const Config &cfg) :
  cfg_(cfg), dataSets_(dataSets) {
  init("print event info");
  selectEvents();
  print();
}


void EventInfoPrinter::init(const TString &key) {
  std::vector<Config::Attributes> attrList = cfg_.listOfAttributes(key);
  for(std::vector<Config::Attributes>::const_iterator it = attrList.begin();
      it != attrList.end(); ++it) {
    if( it->hasName("variable") && it->hasName("number") ) {
      TString variable = it->value("variable");
      if( !Variable::exists(variable) ) {
	std::cerr << "\n\nERROR in EventInfoPrinter::init(): variable '" << variable << "' does not exist" << std::endl;
	exit(-1);
      }
      int number = it->value("number").Atoi();
      selectionVariables_[variable] = number;
    } else {
      std::cerr << "\n\nERROR in EventInfoPrinter::init(): wrong syntax" << std::endl;
      std::cerr << "  in line with key '" << key << "'" << std::endl;
      std::cerr << "  in config file '" << cfg_.fileName() << "'" << std::endl;
      exit(-1);
    }
  }
}


void EventInfoPrinter::selectEvents() {
  for(std::vector<DataSet*>::const_iterator itDS = dataSets_.begin();
      itDS != dataSets_.end(); ++itDS) {
    DataSet* ds = *itDS;

    std::set<const Event*> selectedEvts;
    for(std::map<TString,unsigned int>::const_iterator itSV = selectionVariables_.begin(); itSV != selectionVariables_.end(); ++itSV) {
      
      std::vector<EvtValPair*> evtValPairs;
      for(EventIt itEvt = ds->begin(); itEvt != ds->end(); ++itEvt) {
	evtValPairs.push_back(new EvtValPair(*itEvt,(*itEvt)->get(itSV->first)));
      }
      std::sort(evtValPairs.begin(),evtValPairs.end(),EvtValPair::valueGreaterThan);
      for(unsigned int n = 0; n < std::min(itSV->second,static_cast<unsigned int>(evtValPairs.size())); ++n) {
	selectedEvts.insert(evtValPairs.at(n)->event());
      }
      for(std::vector<EvtValPair*>::iterator it = evtValPairs.begin();
	  it != evtValPairs.end(); ++it) {
	delete *it;
      }
    }
    printedEvts_[ds->label()] = selectedEvts;
  }
}


void EventInfoPrinter::print() const {
  const unsigned int width = 18;
  std::list<TString> vars = listOfPrintedVariables();
  TString separator1 = "";
  TString separator2 = "";
  for(unsigned int i = 0; i < vars.size(); ++i) {
    for(unsigned int j = 0; j < width+3; ++j) {
      separator1 += "=";
      separator2 += "-";
    }
  }
  ofstream file("EventInfo_"+(*dataSets_.begin())->selection()+".txt");
  for(std::map< TString, std::set<const Event*> >::const_iterator it = printedEvts_.begin(); it != printedEvts_.end(); ++it) {
    file << separator1 << std::endl;
    file << "Dataset: '" << it->first << "'" << std::endl;
    file << separator2 << std::endl;
    for(std::list<TString>::const_iterator itVar = vars.begin(); itVar != vars.end(); ++itVar) {
      file << std::setw(width) << std::fixed << *itVar;
      if( itVar != --vars.end() ) file << " : ";
      else file << std::endl;
    }
    file << separator2 << std::endl;
    
    for(std::set<const Event*>::const_iterator itEvt = it->second.begin();
	itEvt != it->second.end(); ++itEvt) {
      for(std::list<TString>::const_iterator itVar = vars.begin(); itVar != vars.end(); ++itVar) {
	file << std::setw(width) << (*itEvt)->get(*itVar);
	if( itVar != --vars.end() ) file << " : ";
	else file << std::endl;
      }
    }
    file << separator1 << std::endl;
    file << "\n\n\n";
  }
  file.close();
}


std::list<TString> EventInfoPrinter::listOfPrintedVariables() const {
  // List of variables
  std::list<TString> list;
  for(std::vector<TString>::const_iterator itV = Variable::begin();
      itV != Variable::end(); ++itV) {
    list.push_back(*itV);
  }

  // Order list such that the following variabels
  // are at front
  std::vector<TString> varsInOrder;
  varsInOrder.push_back("RunNum");
  varsInOrder.push_back("LumiBlockNum");
  varsInOrder.push_back("EvtNum");
  varsInOrder.push_back("HT");
  varsInOrder.push_back("MHT");

  // The resulting list
  std::list<TString>::iterator endOfOrderedPart = list.begin();    
  ++endOfOrderedPart;
  for(std::vector<TString>::const_iterator itOV = varsInOrder.begin();
      itOV != varsInOrder.end(); ++itOV) {
    for(std::list<TString>::iterator it = list.begin(); it != list.end(); ++it) {
      if( *it == *itOV ) {
	TString tmp = *it;
	list.erase(it);
	list.insert(endOfOrderedPart,tmp);
	++endOfOrderedPart;
	break;
      }
    }
  }
  
  return list;
}



bool EventInfoPrinter::EvtValPair::valueGreaterThan(const EvtValPair *idx1, const EvtValPair *idx2) {
  if(idx1 == 0) {
    return idx2 != 0;
  } else if(idx2 == 0) {
    return false;
  } else {
    return idx1->value() > idx2->value();
  }
}
