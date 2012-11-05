// $Id: $

#include <iomanip>
#include <iostream>

#include "EventYieldPrinter.h"


void EventYieldPrinter::operator()() const {
  std::cout << "\n\n\n\n\\begin{tabular}{";
  for(unsigned int i = 0; i < nDataSets()+1; ++i) {
    std::cout << "r";
  }
  std::cout << "}\n";
  std::cout << "\\toprule\n";

  unsigned int width = sizeOfSelectionLabels() + 4;
  std::cout << std::setw(width) << "Selection";
  std::map< TString, std::map<TString,TString> >::const_iterator itSels = yields_.begin();
  std::map<TString,TString>::const_iterator itDS = itSels->second.begin();
  for(; itDS != itSels->second.end(); ++itDS) {
    std::cout << std::setw(5) << " & " << std::setw(12) << itDS->first;
  }
  std::cout << "  \\\\ \n\\midrule\n";
  for(; itSels != yields_.end(); ++itSels) {
    std::cout << std::setw(width) << itSels->first;
    std::map<TString,TString>::const_iterator itDS = itSels->second.begin();
    for(; itDS != itSels->second.end(); ++itDS) {
      std::cout << std::setw(5) << " & " << std::setw(12) << itDS->second;
    }
    std::cout << "  \\\\ \n";
  }
  std::cout << "\\bottomrule \n\\end{tabular}\n\n\n";
}


void EventYieldPrinter::add(const TString &dataSetName, const TString &selection, double nEvents) {
  TString y = "";
  y += nEvents;
  add(dataSetName,selection,y);
}


void EventYieldPrinter::add(const TString &dataSetName, const TString &selection, double nEvents, double yield) {
  TString y = "";
  y += static_cast<int>(yield);
  y += " (";
  y += nEvents;
  y += ")";
  add(dataSetName,selection,y);
}


void EventYieldPrinter::add(const TString &dataSetName, const TString &selection, const TString &yield) {
  std::map< TString, std::map<TString,TString> >::iterator it = yields_.find(selection);
  if( it != yields_.end() ) {
    it->second[dataSetName] = yield;
  } else {
    std::map<TString,TString> y;
    y[dataSetName] = yield;
    yields_[selection] = y;
  }
}


unsigned int EventYieldPrinter::nDataSets() const {
  unsigned int n = 0;
  if( yields_.size() ) {
    std::map< TString, std::map<TString,TString> >::const_iterator itSels = yields_.begin();
    n = itSels->second.size();
  }

  return n;
}


unsigned int EventYieldPrinter::sizeOfSelectionLabels() const {
  unsigned int s = 0;
  std::map< TString, std::map<TString,TString> >::const_iterator itSels = yields_.begin();
  for(; itSels != yields_.end(); ++itSels) {
    if( itSels->first.Length() > s ) s = itSels->first.Length();
  }
  
  return s;
}
