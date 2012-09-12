#include <cstdlib>
#include <iostream>

#include "TError.h"

#include "EventInfoPrinter.h"
#include "GlobalParameters.h"
#include "MrRA2.h"
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
  init(cfg,"dataset");

  // Control plots without selection
  std::cout << "\nProcessing the results" << std::endl;
  makePlots(dataSets_,cfg);
  std::cout << "  - for the preselection" << std::endl;

  // Plots after different selections
  for(std::vector<Selection*>::const_iterator itSel = selections_.begin();
      itSel != selections_.end(); ++itSel) {
    std::cout << "  - for the selection '" << (*itSel)->label() << "'" << std::endl;
    std::vector<DataSet*> selectedDataSets;
    for(std::vector<DataSet*>::const_iterator itDat = dataSets_.begin();
	itDat != dataSets_.end(); ++itDat) {
      selectedDataSets.push_back((**itSel)(*itDat));
      std::cout << "    Dataset '" << (*itDat)->label() << "':" << std::endl;
      (*itSel)->print();
    }
    makePlots(selectedDataSets,cfg);
    EventInfoPrinter(selectedDataSets,cfg);
  }
}

MrRA2::~MrRA2() {
  for(std::vector<DataSet*>::iterator it = dataSets_.begin();
      it != dataSets_.end(); ++it) {
    delete *it;
  }
  Selection::deleteAllSelections();
}


void MrRA2::init(const Config &cfg, const TString &key) {
  // Setup datasets
  std::cout << "Reading datasets...  " << std::flush;
  dataSets_ = DataSet::createDataSets(cfg,key);
  std::cout << "ok" << std::endl;

  // Setup selections
  std::cout << "Preparing selections...  " << std::flush;
  selections_ = Selection::createSelections(cfg,"selection");
  std::cout << "ok" << std::endl;
}

