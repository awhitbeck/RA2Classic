#include <cstdlib>
#include <iostream>

#include "TError.h"

#include "Config.h"
#include "DataSet.h"
//#include "EventInfoPrinter.h"
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
    std::cerr << "Please specify configuration file." << std::endl;
  }

  return 0;
}


MrRA2::MrRA2(const TString& configFileName) {
  // Initialization
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
    std::cout << "  " << (*itd)->label() << " (" << DataSet::toString((*itd)->type()) << ")" << std::endl;
  }

  std::cout << "\nThe following selections are defined:" << std::endl;
  for(SelectionIt its = Selection::begin(); its != Selection::end(); ++its) {
    std::cout << "  " << (*its)->uid() << std::endl;
    (*its)->print();
  }
  std::cout << "\n\n\n";


  // Print simple cut flow
  std::cout << "Selected events" << std::endl;
  for(DataSetIt itd = inputDataSets.begin(); itd != inputDataSets.end(); ++itd) {
    std::cout << "  " << (*itd)->label() << " (" << DataSet::toString((*itd)->type()) << ")" << std::endl;
    DataSets selectedDataSets = DataSet::findAllWithLabel((*itd)->label());
    for(DataSetIt itsd = selectedDataSets.begin(); itsd != selectedDataSets.end(); ++itsd) {
      std::cout << "    " <<  std::setw(15) << (*itsd)->selectionUid() << " : " << std::setw(15) << (*itsd)->yield() << " (" << (*itsd)->size() << ")" << std::endl;
    }
  }

  // Control the output
  Output out;

  // Control plots without selection
  std::cout << "\nProcessing the results" << std::endl;
  std::cout << "  - Creating control plots" << std::endl;
  PlotBuilder(cfg,out);

  EventYieldPrinter evtYieldPrinter;
  evtYieldPrinter();


  // // Plots after different selections
  // // Loop over defined selections
  // EventYieldPrinter evtYieldPrinter;
  // for(std::vector<Selection*>::const_iterator itSel = selections_.begin();
  //     itSel != selections_.end(); ++itSel) {
  //   std::cout << "  - for the selection '" << (*itSel)->label() << "'" << std::endl;
  //   // For each dataset, select subsets of events passing this selection
  //   std::vector<DataSet*> selectedDataSets;
  //   for(std::vector<DataSet*>::const_iterator itDat = dataSets_.begin();
  // 	itDat != dataSets_.end(); ++itDat) {
  //     selectedDataSets.push_back((**itSel)(*itDat));
  //     std::cout << "    " << "Dataset '" << selectedDataSets.back()->label() << "' (" << (*itDat)->size() << " entries in tree)" << std::endl;
  //     (*itSel)->print();
  //     if( (*itDat)->type() == DataSet::Data ) {
  // 	evtYieldPrinter.add((*itDat)->label(),(*itSel)->label(),selectedDataSets.back()->size());
  //     } else {
  // 	evtYieldPrinter.add((*itDat)->label(),(*itSel)->label(),selectedDataSets.back()->size(),selectedDataSets.back()->yield());
  //     }
  //   }
  //   // Create output directory
    
  //   // Process the final result for this selection
  //   PlotBuilder(selectedDataSets,cfg,out); // Make plots
  //   EventInfoPrinter(selectedDataSets,cfg); // Print event info (for tail scans) 
  // }

  // // Print selected yields
  // evtYieldPrinter();

  // out.createLaTeXSlide();
}

MrRA2::~MrRA2() {
  DataSet::clear();
  Selection::clear();
}

