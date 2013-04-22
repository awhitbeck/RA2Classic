// $Id: MrRA2.cc,v 1.11 2013/04/22 16:27:33 mschrode Exp $

#include <cstdlib>
#include <iomanip>
#include <iostream>

#include "TError.h"

#include "Config.h"
#include "DataSet.h"
#include "EventInfoPrinter.h"
#include "GlobalParameters.h"
#include "MrRA2.h"
#include "EventYieldPrinter.h"
#include "Output.h"
#include "PlotBuilder.h"
#include "Selection.h"
#include "Variable.h"



int main(int argc, char *argv[]) {
  if( argc > 1 ) {
    MrRA2* mr = new MrRA2(argv[1]);
    delete mr;
  } else {
    std::cerr << "\n\n  ERROR: Missing configuration file" << std::endl;
    std::cerr << "  Usage './run config-file-name\n" << std::endl;
  }

  return 0;
}


MrRA2::MrRA2(const TString& configFileName) {
  std::cout << "\n +------------------------------------------------+" << std::endl;
  std::cout << " |                                                |" << std::endl;
  std::cout << " |     MrRA2 - the Really Awesome plotting 2l     |" << std::endl;
  std::cout << " |                                                |" << std::endl;
  std::cout << " +------------------------------------------------+\n" << std::endl;
  if( GlobalParameters::cvsTag() == "" ) {
    std::cout << "Developer's version" << std::endl;
  } else {
    std::cout << "Version " << GlobalParameters::cvsTag() << std::endl;
  }
  std::cout << "\n" << std::endl;

  // Initialization
  std::cout << "Initializing MrRA2" << std::endl;
  gErrorIgnoreLevel = 1001;
  Config cfg(configFileName);
  GlobalParameters::init(cfg,"global");
  Variable::init(cfg,"event content");
  Selection::init(cfg,"selection");
  DataSet::init(cfg,"dataset");
  std::cout << "\n\n\n";
  

  // Print setup info
  std::cout << "The following datasets are defined:" << std::endl;
  DataSets inputDataSets = DataSet::findAllUnselected();
  for(DataSetIt itd = inputDataSets.begin(); itd != inputDataSets.end(); ++itd) {
    std::cout << "  " << (*itd)->label() << " (type '" << DataSet::toString((*itd)->type()) << "'): " << (*itd)->size() << " entries" << std::endl;
  }

  std::cout << "\nThe following selections are defined:" << std::endl;
  for(SelectionIt its = Selection::begin(); its != Selection::end(); ++its) {
    std::cout << "  Selection '" << (*its)->uid() << "'" << std::endl;
    (*its)->print();
  }
  std::cout << "\n";


  // Print simple cut flow
  std::cout << "The following number of events (entries) are selected:" << std::endl;
  for(DataSetIt itd = inputDataSets.begin(); itd != inputDataSets.end(); ++itd) {
    std::cout << "  " << std::setw(Selection::maxLabelLength()) << (*itd)->label() << " (" << DataSet::toString((*itd)->type()) << ") : " << std::setw(15) << (*itd)->yield() << " (" << (*itd)->size() << ")" << std::endl;
    DataSets selectedDataSets = DataSet::findAllWithLabel((*itd)->label());
    for(DataSetIt itsd = selectedDataSets.begin(); itsd != selectedDataSets.end(); ++itsd) {
      std::cout << "    " << std::setw(Selection::maxLabelLength()) << (*itsd)->selectionUid() << " : " << std::setw(15) << (*itsd)->yield() << " (" << (*itsd)->size() << ")" << std::endl;
    }
  }

  // Control the output
  Output out;

  // Control plots without selection
  std::cout << "\n\n\nProcessing the output" << std::endl;
  PlotBuilder(cfg,out);
  EventInfoPrinter evtInfoPrinter(cfg);
  EventYieldPrinter evtYieldPrinter;

  std::cout << "Done.\nThank you for using MrRA2! Want to donate money? Contact M. Schroeder." << std::endl;
}

MrRA2::~MrRA2() {
  DataSet::clear();
  Selection::clear();
}

