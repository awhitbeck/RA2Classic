// $Id: EventYieldPrinter.cc,v 1.11 2013/02/16 18:58:24 mschrode Exp $

#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <vector>

#include "DataSet.h"
#include "EventYieldPrinter.h"
#include "Output.h"
#include "Selection.h"



EventYieldPrinter::EventYieldPrinter() {
  
  const TString outFileNamePrefix = Output::resultDir()+"/"+Output::id();

  std::cout << "  - Writing event-yield information to '" << outFileNamePrefix << "_EventYields.tex'" << std::endl;
  printToLaTeX(outFileNamePrefix+"_EventYields.tex");

  std::cout << "  - Writing data card to '" << outFileNamePrefix << "_DataCard.txt'" << std::endl;
  printDataCard(outFileNamePrefix+"_DataCard.txt");

  printToScreen();
}


void EventYieldPrinter::printToScreen() const {
  DataSets inputDataSets = DataSet::findAllUnselected();
  unsigned int width = Selection::maxLabelLength() + 4;
  unsigned int nSeps = width;

  std::vector<DataSet::Type> printedTypes;
  printedTypes.push_back(DataSet::Data);
  printedTypes.push_back(DataSet::MC);
  printedTypes.push_back(DataSet::Prediction);
  printedTypes.push_back(DataSet::Signal);

  std::vector<bool> printTotalYield(printedTypes.size(),false);


  std::cout << "\n\n\n\n";
  std::cout << std::setw(width) << "Selection";
  for(unsigned int typeIdx = 0; typeIdx < printedTypes.size(); ++typeIdx) {
    unsigned int nDataSetsOfThisType = 0;
    for(DataSetIt itd = inputDataSets.begin(); itd != inputDataSets.end(); ++itd) {
      if( (*itd)->type() == printedTypes.at(typeIdx) ) {
	std::cout << std::setw(5) << " | " << std::setw(12) << (*itd)->label();
	nSeps += 17;
	++nDataSetsOfThisType;
      }
    }
    if( nDataSetsOfThisType > 1 ) {
      printTotalYield.at(typeIdx) = true;
      std::cout << std::setw(5) << " | " << std::setw(12) << "Total " << DataSet::toString(printedTypes.at(typeIdx));
    }
  }
  std::cout << "\n";
  for(unsigned int i = 0; i < nSeps; ++i) {
    std::cout << "-";
  }
  std::cout << "\n";
  for(SelectionIt its = Selection::begin(); its != Selection::end(); ++its) {
    std::cout << std::setw(width) << (*its)->uid();
    DataSets selectedDataSets = DataSet::findAllWithSelection((*its)->uid());
    char yield[50];
    char stat[50];
    char systDn[50];
    char systUp[50];
    for(unsigned int typeIdx = 0; typeIdx < printedTypes.size(); ++typeIdx) {
      double totYield = 0.;
      double totStat = 0.;
      double totSystDn = 0.;
      double totSystUp = 0.;
      for(DataSetIt itsd = selectedDataSets.begin(); itsd != selectedDataSets.end(); ++itsd) {
	if( (*itsd)->type() == printedTypes.at(typeIdx) ) {
	  std::cout << std::setw(5) << " | ";
	  sprintf(yield,"%.1f",(*itsd)->yield());
	  totYield += (*itsd)->yield();
	  sprintf(stat,"%.1f",(*itsd)->stat());
	  totStat += std::sqrt( (*itsd)->stat()*(*itsd)->stat() + totStat*totStat );
	  std::cout << std::setw(12) << yield << " +/- " << stat;
	  if( (*itsd)->hasSyst() ) {
	    sprintf(systDn,"%.1f",(*itsd)->totSystDn());
	    totSystDn += std::sqrt( (*itsd)->totSystDn()*(*itsd)->totSystDn() + totSystDn*totSystDn );
	    sprintf(systUp,"%.1f",(*itsd)->totSystUp());
	    totSystUp += std::sqrt( (*itsd)->totSystUp()*(*itsd)->totSystUp() + totSystUp*totSystUp );
	    std::cout << " +" << systUp << " -" << systDn;
	  }
	}
      }
      if( printTotalYield.at(typeIdx) ) {
	std::cout << std::setw(5) << " | ";
	sprintf(yield,"%.1f",totYield);
	sprintf(stat,"%.1f",totStat);
	sprintf(systDn,"%.1f",totSystDn);
	sprintf(systUp,"%.1f",totSystUp);
	std::cout << std::setw(12) << yield << " +/- " << stat;
	if( totSystDn > 0. ) {
	  std::cout << " +" << systUp << " -" << systDn;
	}
      }
    }
    std::cout << "\n";
  }
}


void EventYieldPrinter::printToLaTeX(const TString &outFileName) const {
  ofstream file(outFileName);

  DataSets inputDataSets = DataSet::findAllUnselected();
  unsigned int width = Selection::maxLabelLength() + 4;

  // Print yields and total uncertainties
  // per datasets (rows) and selections (columns)
  file << "\n\n\n\n";
  file << "%===========================================================================" << std::endl;
  file << "% Datasets vs Selections: yields and total uncertainties" << std::endl;
  file << "%===========================================================================" << std::endl;
  file << "\n\\begin{tabular}{l";
  for(unsigned int i = 1; i < inputDataSets.size()+1; ++i) {
    file << "r";
  }
  file << "}\n";
  file << "\\toprule\n";

  file << std::setw(width) << "Selection";
  for(DataSetIt itd = inputDataSets.begin(); itd != inputDataSets.end(); ++itd) {
    file << std::setw(5) << " & " << std::setw(12) << Output::cleanLatexName((*itd)->label());
  }
  file << "  \\\\ \n\\midrule\n";
  for(SelectionIt its = Selection::begin(); its != Selection::end(); ++its) {
    file << std::setw(width) << Output::cleanLatexName((*its)->uid());
    DataSets selectedDataSets = DataSet::findAllWithSelection((*its)->uid());
    for(DataSetIt itsd = selectedDataSets.begin(); itsd != selectedDataSets.end(); ++itsd) {
      file << std::setw(5) << " & ";
      char yield[50];
      char stat[50];
      if( (*itsd)->type() == DataSet::Data ) {
	sprintf(yield,"%.0f",(*itsd)->yield());
	file << "$" << std::setw(12) << yield;
      } else {	
	sprintf(yield,"%.1f",(*itsd)->yield());
	sprintf(stat,"%.1f",(*itsd)->stat());
	file << "$" << std::setw(12) << yield << " \\pm " << stat;
      }
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
    file << "% Dataset: " << Output::cleanLatexName((*itd)->label()) << std::endl;
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
    if( (*itd)->nSyst() > 1 ) {
      for(std::vector<TString>::const_iterator systIt = (*itd)->systLabelsBegin();
	  systIt != (*itd)->systLabelsEnd(); ++systIt) {
	file << " & " << *systIt << "[\\%]";
      }
    }
    file << "  \\\\ \n\\midrule\n";

    for(SelectionIt its = Selection::begin(); its != Selection::end(); ++its) {
      file << std::setw(width) << Output::cleanLatexName((*its)->uid());      
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
      if( (*itd)->nSyst() > 1 ) {
	for(std::vector<TString>::const_iterator systIt = (*itd)->systLabelsBegin();
	    systIt != (*itd)->systLabelsEnd(); ++systIt) {
	  if( selectedDataSet->yield() > 0. ) {
	    sprintf(systDn,"%.1f",100.*selectedDataSet->systDn(*systIt)/selectedDataSet->yield());
	    sprintf(systUp,"%.1f",100.*selectedDataSet->systUp(*systIt)/selectedDataSet->yield());
	    file << " & ${}^{+" << systUp << "}_{-" << systDn << "}$";	  
	  }
	}
      }
      file << " \\\\" << std::endl;
    }
    file << "\\bottomrule\n\\end{tabular}" << std::endl;
  }

  file.close();
}


void EventYieldPrinter::printDataCard(const TString &outFileName) const {
  ofstream file(outFileName);

  DataSets inputDataSets = DataSet::findAllUnselected();
  unsigned int width = 8;

  // Determine bins
  unsigned int nBins = 0;
  TString commentOnBinning = "# ";
  TString binning = "channel = ";
  for(SelectionIt its = Selection::begin(); its != Selection::end(); ++its) {
    ++nBins;
    binning += "bin";
    binning += nBins;
    binning += "; ";
    commentOnBinning += "bin";
    commentOnBinning += nBins;
    commentOnBinning += " is for " + (*its)->uid() + ", ";
  }

  
  // Loop over input datasets
  for(DataSetIt itd = inputDataSets.begin(); itd != inputDataSets.end(); ++itd) {
    // General informatin
    file << "# General information:" << std::endl;
    file << "luminosity = " << 1000.*(GlobalParameters::lumi()).Atof() << " # given in pb-1" << std::endl;
    file << "channels   = " << nBins << " # total number of channels / bins. Counting ordering, MHT, HT and nJets." << std::endl;
    file << "sample     = " << (*itd)->label() << " # name of the sample" << std::endl;
    if( (*itd)->type() == DataSet::Prediction ) {
      file << "nuisances = " << (*itd)->nSyst() + 1 << " # number of nuisance/uncertainties" << std::endl;
    }

    // Binning information
    file << "\n" << commentOnBinning << std::endl;
    file << binning << std::endl;

    // Yields
    file << (*itd)->label() << "_events = ";
    
    for(SelectionIt its = Selection::begin(); its != Selection::end(); ++its) {
      const DataSet* selectedDataSet = DataSet::find((*itd)->label(),*its);
      file << std::setw(width) << selectedDataSet->yield();
    }
    file << std::endl;

    if( (*itd)->type() != DataSet::Data ) {
      // define number of uncertainties
      file << "# Uncertainties --> at least stat. and syst." << std::endl;
      file << "# In absolute numbers" << std::endl;
      file << "nuisance = stat. uncert.; ";
      if( (*itd)->hasSyst() ) {
	file << GlobalParameters::defaultUncertaintyLabel();
      }
      file << std::endl;
      // define uncertainty distributions
      file << (*itd)->label() << "_uncertaintyDistribution_1 = lnN" << std::endl;
      if( (*itd)->hasSyst() ) {
	file << (*itd)->label() << "_uncertaintyDistribution_2 = lnN" << std::endl;
      }
      // print statistical uncertainties in each bin
      file << (*itd)->label() << "_uncertainty_1 = ";
      for(SelectionIt its = Selection::begin(); its != Selection::end(); ++its) {
	const DataSet* selectedDataSet = DataSet::find((*itd)->label(),*its);
	file << std::setw(width) << selectedDataSet->stat();
      }
      file << std::endl;
      // print total systematic uncertainty in each bin
      if( (*itd)->hasSyst() ) {
	file << (*itd)->label() << "_uncertaintyDN_2 = ";
	for(SelectionIt its = Selection::begin(); its != Selection::end(); ++its) {
	  const DataSet* selectedDataSet = DataSet::find((*itd)->label(),*its);
	  file << std::setw(width) << selectedDataSet->totSystDn() << " ";
	}
	file << std::endl;
	file << (*itd)->label() << "_uncertaintyUP_2 = ";
	for(SelectionIt its = Selection::begin(); its != Selection::end(); ++its) {
	  const DataSet* selectedDataSet = DataSet::find((*itd)->label(),*its);
	  file << std::setw(width) << selectedDataSet->totSystUp() << " ";
	}
	file << std::endl;
      }
    }


    // Optionally, print individual uncertainties
    if( (*itd)->type() != DataSet::Data && (*itd)->nSyst() > 1 ) {
      // General informatin
      file << "\n\n";
      file << "# General information:" << std::endl;
      file << "luminosity = " << 1000.*(GlobalParameters::lumi()).Atof() << " # given in pb-1" << std::endl;
      file << "channels   = " << nBins << " # total number of channels / bins. Counting ordering, MHT, HT and nJets." << std::endl;
      file << "sample     = " << (*itd)->label() << " # name of the sample" << std::endl;
      if( (*itd)->type() == DataSet::Prediction ) {
	file << "nuisances = " << (*itd)->nSyst() + 1 << " # number of nuisance/uncertainties" << std::endl;
      }
      
      // Binning information
      file << "\n" << commentOnBinning << std::endl;
      file << binning << std::endl;
      
      // Yields
      file << (*itd)->label() << "_events = ";
      
      for(SelectionIt its = Selection::begin(); its != Selection::end(); ++its) {
	const DataSet* selectedDataSet = DataSet::find((*itd)->label(),*its);
	file << std::setw(width) << selectedDataSet->yield();
      }
      file << std::endl;
      
      if( (*itd)->type() != DataSet::Data ) {
	// define number of uncertainties
	file << "# Uncertainties --> at least stat. and syst." << std::endl;
	file << "# In absolute numbers" << std::endl;
	file << "nuisance = stat. uncert.; ";
	for(std::vector<TString>::const_iterator itu = (*itd)->systLabelsBegin();
	    itu != (*itd)->systLabelsEnd(); ++itu) {
	  file << *itu << "; ";
	}
	file << std::endl;
	// define uncertainty distributions
	for(unsigned int i = 1; i <= (*itd)->nSyst() + 1; ++i) {
	  file << (*itd)->label() << "_uncertaintyDistribution_" << i << " = lnN" << std::endl;
	}
	// print statistical uncertainties in each bin
	file << (*itd)->label() << "_uncertainty_1 = ";
	for(SelectionIt its = Selection::begin(); its != Selection::end(); ++its) {
	  const DataSet* selectedDataSet = DataSet::find((*itd)->label(),*its);
	  file << std::setw(width) << selectedDataSet->stat();
	}
	file << std::endl;
	// print further uncertainties in each bin
	unsigned int nUncert = 2;
	for(std::vector<TString>::const_iterator itu = (*itd)->systLabelsBegin();
	    itu != (*itd)->systLabelsEnd(); ++itu, ++nUncert) {
	  file << (*itd)->label() << "_uncertaintyDN_" << nUncert << " = ";
	  for(SelectionIt its = Selection::begin(); its != Selection::end(); ++its) {
	    const DataSet* selectedDataSet = DataSet::find((*itd)->label(),*its);
	    file << std::setw(width) << selectedDataSet->systDn(*itu) << " ";
	  }
	  file << std::endl;
	  file << (*itd)->label() << "_uncertaintyUP_" << nUncert << " = ";
	  for(SelectionIt its = Selection::begin(); its != Selection::end(); ++its) {
	    const DataSet* selectedDataSet = DataSet::find((*itd)->label(),*its);
	    file << std::setw(width) << selectedDataSet->systUp(*itu) << " ";
	  }
	  file << std::endl;
	}
      }
    }
    file << "\n\n\n\n";
  }
}
