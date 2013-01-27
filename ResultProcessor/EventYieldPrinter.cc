// $Id: EventYieldPrinter.cc,v 1.3 2013/01/24 22:21:28 mschrode Exp $

#include <fstream>
#include <iomanip>
#include <iostream>

#include "TString.h"

#include "DataSet.h"
#include "EventYieldPrinter.h"
#include "Output.h"
#include "Selection.h"



EventYieldPrinter::EventYieldPrinter() {
  std::cout << " -  Writing event-yield information to '" << Output::resultDir() << "/EventYields.tex'" << std::endl;
  printToLaTeX();
  printToScreen();
}


void EventYieldPrinter::printToScreen() const {
  DataSets inputDataSets = DataSet::findAllUnselected();
  unsigned int width = Selection::maxLabelLength() + 4;
  unsigned int nSeps = width;

  std::cout << "\n\n\n\n";
  std::cout << std::setw(width) << "Selection";
  for(DataSetIt itd = inputDataSets.begin(); itd != inputDataSets.end(); ++itd) {
    std::cout << std::setw(5) << " | " << std::setw(12) << (*itd)->label();
    nSeps += 17;
  }
  std::cout << "\n";
  for(unsigned int i = 0; i < nSeps; ++i) {
    std::cout << "-";
  }
  std::cout << "\n";
  for(SelectionIt its = Selection::begin(); its != Selection::end(); ++its) {
    std::cout << std::setw(width) << (*its)->uid();
    DataSets selectedDataSets = DataSet::findAllWithSelection((*its)->uid());
    for(DataSetIt itsd = selectedDataSets.begin(); itsd != selectedDataSets.end(); ++itsd) {
      std::cout << std::setw(5) << " | ";
      char yield[50];
      char stat[50];
      sprintf(yield,"%.1f",(*itsd)->yield());
      sprintf(stat,"%.1f",(*itsd)->stat());
      if( (*itsd)->hasSyst() ) {
	char systDn[50];
	char systUp[50];
	sprintf(systDn,"%.1f",(*itsd)->totSystDn());
	sprintf(systUp,"%.1f",(*itsd)->totSystUp());
	std::cout << std::setw(12) << yield << " +/- " << stat << " +" << systUp << " -" << systDn;
      } else {
	std::cout << std::setw(12) << yield << " +/- " << stat;
      }
    }
    std::cout << "\n";
  }
}


void EventYieldPrinter::printToLaTeX() const {
  ofstream file(Output::resultDir()+"/EventYields.tex");

  DataSets inputDataSets = DataSet::findAllUnselected();
  unsigned int width = Selection::maxLabelLength() + 4;

  // Print yields and total uncertainties
  // per datasets (rows) and selections (columns)
  file << "\n\n\n\n";
  file << "%===========================================================================" << std::endl;
  file << "% Datasets vs Selections: yields and total uncertainties" << std::endl;
  file << "%===========================================================================" << std::endl;
  file << "\n\\begin{tabular}{";
  for(unsigned int i = 0; i < inputDataSets.size()+1; ++i) {
    file << "r";
  }
  file << "}\n";
  file << "\\toprule\n";

  file << std::setw(width) << "Selection";
  for(DataSetIt itd = inputDataSets.begin(); itd != inputDataSets.end(); ++itd) {
    file << std::setw(5) << " & " << std::setw(12) << (*itd)->label();
  }
  file << "  \\\\ \n\\midrule\n";
  for(SelectionIt its = Selection::begin(); its != Selection::end(); ++its) {
    file << std::setw(width) << (*its)->uid();
    DataSets selectedDataSets = DataSet::findAllWithSelection((*its)->uid());
    for(DataSetIt itsd = selectedDataSets.begin(); itsd != selectedDataSets.end(); ++itsd) {
      file << std::setw(5) << " & ";
      char yield[50];
      char stat[50];
      sprintf(yield,"%.1f",(*itsd)->yield());
      sprintf(stat,"%.1f",(*itsd)->stat());
      file << "$" << std::setw(12) << yield << " \\pm " << stat;
      if( (*itsd)->hasSyst() ) {
	char systDn[50];
	char systUp[50];
	sprintf(systDn,"%.1f",(*itsd)->totSystDn());
	sprintf(systUp,"%.1f",(*itsd)->totSystUp());
	file << "{}^{+" << systUp << "}_{-" << systDn << "}";
      }
      file << "$";
    }
    file << "  \\\\ \n";
  }
  file << "\\bottomrule \n\\end{tabular}\n\n\n";


  // Print yields, total uncertainties, and individual syst uncertainties
  // (columns) per selection (rows) for all datasets
  file << "\n\n\n\n";
  file << "%===========================================================================" << std::endl;
  file << "% Detailed Yields and Uncertainties" << std::endl;
  file << "%===========================================================================" << std::endl;

  for(DataSetIt itd = inputDataSets.begin(); itd != inputDataSets.end(); ++itd) {
    file << "\n\n%---------------------------------------------------------------------------" << std::endl;
    file << "% Dataset: " << (*itd)->label() << std::endl;
    file << "%---------------------------------------------------------------------------" << std::endl;
    file << "\n\\begin{tabular}{l|rrr";
    for(unsigned int i = 0; i < (*itd)->nSyst(); ++i) {
      if( i == 0 ) file << "|";
      file << "r";
    }
    file << "}\n";
    file << "\\toprule\n";
    file << std::setw(width) << "Selection";
    file << " & yield & stat & syst tot ";
    for(std::vector<TString>::const_iterator systIt = (*itd)->systLabelsBegin();
	systIt != (*itd)->systLabelsEnd(); ++systIt) {
      file << " & " << *systIt << "[\%]";
    }
    file << "  \\\\ \n\\midrule\n";

    for(SelectionIt its = Selection::begin(); its != Selection::end(); ++its) {
      file << std::setw(width) << (*its)->uid();      
      const DataSet* selectedDataSet = DataSet::find((*itd)->label(),*its);
      char yield[50];
      char stat[50];
      char systDn[50];
      char systUp[50];
      sprintf(yield,"%.1f",selectedDataSet->yield());
      sprintf(stat,"%.1f",selectedDataSet->stat());
      sprintf(systDn,"%.1f",selectedDataSet->totSystDn());
      sprintf(systUp,"%.1f",selectedDataSet->totSystUp());
      file << " & " << yield << " & " << stat;
      file << " & ${}^{+" << systUp << "}_{-" << systDn << "}$";
      for(std::vector<TString>::const_iterator systIt = (*itd)->systLabelsBegin();
	  systIt != (*itd)->systLabelsEnd(); ++systIt) {
	if( selectedDataSet->yield() > 0. ) {
	  sprintf(systDn,"%.1f",100.*selectedDataSet->systDn(*systIt)/selectedDataSet->yield());
	  sprintf(systUp,"%.1f",100.*selectedDataSet->systUp(*systIt)/selectedDataSet->yield());
	  file << " & ${}^{+" << systUp << "}_{-" << systDn << "}$";	  
	}
      }
      file << " \\\\" << std::endl;
    }
    file << "\\bottomrule\n\\end{tabular}" << std::endl;
  }

  file.close();
}
