// $Id: EventInfoPrinter.cc,v 1.6 2013/01/28 17:56:54 mschrode Exp $

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>

#include "EventInfoPrinter.h"
#include "Output.h"
#include "Selection.h"
#include "Variable.h"



EventInfoPrinter::EventInfoPrinter(const Config &cfg)
  : cfg_(cfg) {

  // Define names of special variables
  // This should be configurable
  varNameHT = "HT";
  varNameMHT = "MHT";
  varNameRunNum = "RunNum";
  varNameLumiBlockNum = "LumiBlockNum";
  varNameEvtNum = "EvtNum";

  // Init and run
  if( init("print event info") ) {
    selectEvents();
    print();
  }
}


bool EventInfoPrinter::init(const TString &key) {
  std::vector<Config::Attributes> attrList = cfg_.listOfAttributes(key);
  for(std::vector<Config::Attributes>::const_iterator it = attrList.begin();
      it != attrList.end(); ++it) {
    if( it->hasName("variable") ) {
      TString variable = it->value("variable");
      if( !Variable::exists(variable) ) {
	std::cerr << "\n\nERROR in EventInfoPrinter::init(): variable '" << variable << "' does not exist" << std::endl;
	exit(-1);
      }
      int number = -1;
      if( it->hasName("number") ) {
	number = it->value("number").Atoi();
      }
      selectionVariables_[variable] = number;
    } else {
      std::cerr << "\n\nERROR in EventInfoPrinter::init(): wrong syntax" << std::endl;
      std::cerr << "  in line with key '" << key << "'" << std::endl;
      std::cerr << "  in config file '" << cfg_.fileName() << "'" << std::endl;
      exit(-1);
    }
  }

  return attrList.size() > 0;
}


void EventInfoPrinter::selectEvents() {
  // Loop over all global selections
  // !!!!!!!!!!!!!This should be treated more carefully: one set of selectionVariables_
  // per global selection
  for(SelectionIt its = Selection::begin(); its != Selection::end(); ++its) {
    // Loop over all datasets with this global selection
    DataSets selectedDataSets = DataSet::findAllWithSelection((*its)->uid());
    for(DataSetIt itsd = selectedDataSets.begin(); itsd != selectedDataSets.end(); ++itsd) {
      // Select events accoridng to specification
      std::vector<const Event*> selectedEvts;
      if( printAllEvents() ) {	// select all events to print info
	for(EventIt itEvt = (*itsd)->evtsBegin(); itEvt != (*itsd)->evtsEnd(); ++itEvt) {
	  selectedEvts.push_back(*itEvt);
	}
      } else {			// select n (as specified) events with highest value of selection variable
	for(std::map<TString,unsigned int>::const_iterator itSV = selectionVariables_.begin();
	    itSV != selectionVariables_.end(); ++itSV) {
	
	  std::vector<EvtValPair*> evtValPairs;
	  for(EventIt itEvt = (*itsd)->evtsBegin(); itEvt != (*itsd)->evtsEnd(); ++itEvt) {
	    evtValPairs.push_back(new EvtValPair(*itEvt,(*itEvt)->get(itSV->first)));
	  }
	  // sort by size of variable's values
	  std::sort(evtValPairs.begin(),evtValPairs.end(),EvtValPair::valueGreaterThan);
	  // store n (as specified) events with largest value
	  for(unsigned int n = 0; 
	      n < std::min(itSV->second,static_cast<unsigned int>(evtValPairs.size())); ++n) {
	    bool isNewEvt = true;
	    for(std::vector<const Event*>::const_iterator it = selectedEvts.begin();
		it != selectedEvts.end(); ++it) {
	      if( (*it) == evtValPairs.at(n)->event() ) {
		isNewEvt = false;
		break;
	      }
	    }
	    if( isNewEvt ) selectedEvts.push_back(evtValPairs.at(n)->event());
	  }
	  for(std::vector<EvtValPair*>::iterator it = evtValPairs.begin();
	      it != evtValPairs.end(); ++it) {
	    delete *it;
	  }
	}
      }
      // If event contains run-number, sort by it
      if( Variable::exists("RunNum") ) {
	std::sort(selectedEvts.begin(),selectedEvts.end(),EventInfoPrinter::greaterByRunNum);
      }
      // Store list of events
      printedEvts_[(*itsd)->uid()] = selectedEvts;
    }
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

  // Print file with detailed event info and some formatting
  ofstream file(Output::resultDir()+"/"+Output::id()+"_EventInfo.txt");
  // txt-style table
  for(std::map< TString, std::vector<const Event*> >::const_iterator it = printedEvts_.begin(); it != printedEvts_.end(); ++it) {
    file << separator1 << std::endl;
    file << "Dataset: '" << it->first << "'" << std::endl;
    file << separator2 << std::endl;
    for(std::list<TString>::const_iterator itVar = vars.begin(); itVar != vars.end(); ++itVar) {
      file << std::setw(width) << std::fixed << *itVar;
      if( itVar != --vars.end() ) file << " : ";
      else file << std::endl;
    }
    file << separator2 << std::endl;
    
    for(std::vector<const Event*>::const_iterator itEvt = it->second.begin();
	itEvt != it->second.end(); ++itEvt) {
      for(std::list<TString>::const_iterator itVar = vars.begin(); itVar != vars.end(); ++itVar) {
	if( Variable::type(*itVar) == "UShort_t" ||
	    Variable::type(*itVar) == "Int_t" ||
	    Variable::type(*itVar) == "UInt_t" ||
	    Variable::type(*itVar) == "UChar_t"     ) {
	  file << std::setprecision(0);
	} else {
	  file << std::setprecision(3);
	}
	file << std::setw(width) << (*itEvt)->get(*itVar);
	if( itVar != --vars.end() ) file << " : ";
	else file << std::endl;
      }
    }
    file << separator1 << std::endl;
    file << "\n\n\n";
  }
  // LaTeX-style table
  for(std::map< TString, std::vector<const Event*> >::const_iterator it = printedEvts_.begin(); it != printedEvts_.end(); ++it) {
    file << "\n\n\n%" << separator1 << std::endl;
    file << "% Dataset: '" << it->first << "'" << std::endl;
    file << "%" << separator2 << std::endl;
    file << "\n\\begin{tabular}{";
    for(unsigned int i = 0; i < vars.size(); ++i) {
      file << "r";
    }
    file << "}\n";
    file << "\\toprule\n";
    for(std::list<TString>::const_iterator itVar = vars.begin(); itVar != vars.end(); ++itVar) {
      file << std::setw(width) << std::fixed << "\\multicolumn{1}{c}{" << *itVar << "}";
      if( itVar != --vars.end() ) file << " & ";
      else file << " \\\\ \n";
    }
    file << "\\midrule\n";
    
    for(std::vector<const Event*>::const_iterator itEvt = it->second.begin();
	itEvt != it->second.end(); ++itEvt) {
      for(std::list<TString>::const_iterator itVar = vars.begin(); itVar != vars.end(); ++itVar) {
	if( Variable::type(*itVar) == "UShort_t" ||
	    Variable::type(*itVar) == "Int_t" ||
	    Variable::type(*itVar) == "UInt_t" ||
	    Variable::type(*itVar) == "UChar_t"     ) {
	  file << std::setprecision(0);
	} else {
	  file << std::setprecision(2);
	}
	if( (*itEvt)->get(*itVar) == 9999 ) {
	  file << std::setw(width) << "---";
	} else {
	  file << std::setw(width) << (*itEvt)->get(*itVar);
	}
	if( itVar != --vars.end() ) file << " & ";
	else file << " \\\\ \n";
      }
    }
    file << "\\bottomrule \n\\end{tabular}\n\n\n";
  }

  file.close();

  // Print CMSSW-like run lists
  for(std::map< TString, std::vector<const Event*> >::const_iterator it = printedEvts_.begin(); it != printedEvts_.end(); ++it) {
    ofstream file(Output::resultDir()+"/"+Output::id()+"_EventInfo__"+Output::cleanName(it->first)+"__Runlist.txt");
    for(std::vector<const Event*>::const_iterator itEvt = it->second.begin();
	itEvt != it->second.end(); ++itEvt) {
      file << std::setw(width) << (*itEvt)->get(varNameRunNum);
      file << ":";
      file << std::setw(width) << (*itEvt)->get(varNameLumiBlockNum);
      file << ":";
      file << std::setw(width) << std::setprecision(15) << (*itEvt)->get(varNameEvtNum);
      file << std::endl;
    }
    file.close();
  }
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
  varsInOrder.push_back(varNameRunNum);
  varsInOrder.push_back(varNameLumiBlockNum);
  varsInOrder.push_back(varNameEvtNum);
  varsInOrder.push_back(varNameHT);
  varsInOrder.push_back(varNameMHT);

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


bool EventInfoPrinter::printAllEvents() const {
  bool printAll = false;
  for(std::map<TString,unsigned int>::const_iterator itSV = selectionVariables_.begin(); itSV != selectionVariables_.end(); ++itSV) {
    if( itSV->second == -1 ) {
      printAll = true;
      break;
    }
  }

  return printAll;
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



