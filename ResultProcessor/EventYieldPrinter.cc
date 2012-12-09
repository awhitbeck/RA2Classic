// $Id: EventYieldPrinter.cc,v 1.1 2012/11/05 14:52:14 mschrode Exp $

#include <iomanip>
#include <iostream>

#include "TString.h"

#include "DataSet.h"
#include "EventYieldPrinter.h"
#include "Selection.h"


void EventYieldPrinter::operator()() const {
  DataSets inputDataSets = DataSet::findAllUnselected();
  std::cout << "\n\n\n\n\\begin{tabular}{";
  for(unsigned int i = 0; i < inputDataSets.size()+1; ++i) {
    std::cout << "r";
  }
  std::cout << "}\n";
  std::cout << "\\toprule\n";

  unsigned int width = sizeOfSelectionLabels() + 4;
  std::cout << std::setw(width) << "Selection";
  for(DataSetIt itd = inputDataSets.begin(); itd != inputDataSets.end(); ++itd) {
    std::cout << std::setw(5) << " & " << std::setw(12) << (*itd)->label();
  }
  std::cout << "  \\\\ \n\\midrule\n";
  for(SelectionIt its = Selection::begin(); its != Selection::end(); ++its) {
    std::cout << std::setw(width) << (*its)->uid();
    DataSets selectedDataSets = DataSet::findAllWithSelection((*its)->uid());
    for(DataSetIt itsd = selectedDataSets.begin(); itsd != selectedDataSets.end(); ++itsd) {
      std::cout << std::setw(5) << " & ";
      if( (*itsd)->type() == DataSet::Data ) {
	std::cout << std::setw(12) << std::setprecision(0) << (*itsd)->size();
      } else {
	TString str = "";
	str += static_cast<int>((*itsd)->yield());
	if( str == "0" ) str = "";
	std::cout << std::setprecision(str.Length()+1) << std::setw(12) << (*itsd)->yield() << " (" << (*itsd)->size() << ")";
      }
    }
    std::cout << "  \\\\ \n";
  }
  std::cout << "\\bottomrule \n\\end{tabular}\n\n\n";
}


unsigned int EventYieldPrinter::sizeOfSelectionLabels() const {
  unsigned int s = 0;
  for(SelectionIt its = Selection::begin(); its != Selection::end(); ++its) {
    if( (*its)->uid().Length() > s ) s = (*its)->uid().Length();
  }
  
  return s;
}
