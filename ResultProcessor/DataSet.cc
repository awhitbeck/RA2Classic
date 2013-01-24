#include <cmath>
#include <cstdlib>
#include <iostream>

#include "DataSet.h"
#include "EventBuilder.h"
#include "Variable.h"


DataSetUidMap DataSet::dataSetUidMap_;
bool DataSet::isInit_ = false;


TString DataSet::uid(const TString &label, const TString &selectionUid) {
  return label+":"+selectionUid;
}

TString DataSet::uid(const TString &label, const Selection* selection) {
  return uid(label,selection->uid());
}

const DataSet* DataSet::find(const TString &label, const Selection* selection) {
  return find(uid(label,selection));
}

const DataSet* DataSet::find(const TString &uid) {
  DataSetUidIt it = dataSetUidMap_.find(uid);
  if( it == dataSetUidMap_.end() ) {
    std::cerr << "ERROR: DataSet with uid '" << uid << "' does not exist" << std::endl;
    exit(-1);
  }
  
  return it->second;
}


DataSets DataSet::findAllWithSelection(const TString &selectionUid) {
  DataSets dataSets;
  for(DataSetUidIt it = dataSetUidMap_.begin(); it != dataSetUidMap_.end(); ++it) {
    if( it->second->selectionUid() == selectionUid ) {
      dataSets.push_back(it->second);
    }
  }

  return dataSets;
}

DataSets DataSet::findAllWithLabel(const TString &label) {
  DataSets dataSets;
  for(SelectionIt its = Selection::begin(); its != Selection::end(); ++its) {
    dataSets.push_back(find(label,*its));
  }

  return dataSets;
}


bool DataSet::uidExists(const TString &uid) {
  return dataSetUidMap_.find(uid) != DataSet::dataSetUidMap_.end();
}


bool DataSet::labelExists(const TString &label) {
  bool exists = false;
  for(DataSetUidIt it = dataSetUidMap_.begin(); it != dataSetUidMap_.end(); ++it) {
    if( it->second->label() = label ) {
      exists = true;
      break;
    }
  }

  return exists;
}

DataSet::Type DataSet::toType(const TString &type) {
  DataSet::Type result;
  if( type == "Data" || type == "data" ) result = Data;
  else if( type == "MC" || type == "mc" ) result = MC;
  else if( type == "Prediction" || type == "prediction" ) result = Prediction;
  else if( type == "Signal" || type == "signal" ) result = Signal;
  else {
    std::cerr << "\n\nERROR in DataSet::toType(): type '" << type << "' does not exist" << std::endl;
    exit(-1);
  }

  return result;
}


TString DataSet::toString(Type type) {
  TString result = "none";
  if( type == Data ) result = "data";
  else if( type == MC ) result = "mc";
  else if( type == Prediction ) result = "prediction";
  else if( type == Signal ) result = "signal";

  return result;
}


void DataSet::init(const Config &cfg, const TString key) {
  if( isInit_ ) {
    std::cerr << "WARNING: Datasets already initialized. Skipping." << std::endl;
  } else {
    std::cout << "Reading datasets and applying selections...  " << std::flush;

    std::vector<Config::Attributes> attrList = cfg.listOfAttributes(key);
    for(std::vector<Config::Attributes>::const_iterator it = attrList.begin();
	it != attrList.end(); ++it) {
      if( it->nValues() >= 4 ) {
	TString label = it->value("label");
	TString type = it->value("type");
	TString file = it->value("file");
	TString tree = it->value("tree");
	TString weight = "";
	double scale = 1.;
	std::vector<TString> uncDn;
	std::vector<TString> uncUp;
	std::vector<TString> uncLabel;
	if( it->hasName("weight") ) {
	  weight = it->value("weight");
	  if( !(Variable::exists(weight) || weight.IsFloat()) ) {
	    std::cerr << "\n\nERROR in DataSet::createDataSets(): wrong config syntax" << std::endl;
	    std::cerr << "  when specifying the weight in line with key '" << key << "'" << std::endl;
	    std::cerr << "  Syntax is '..., weight : expr, ...', where 'expr' is either a float or an existing variable" << std::endl;
	  }
	}
	if( it->hasName("scale") ) {
	  if( !(it->value("scale")).IsFloat() ) {
	    std::cerr << "\n\nERROR in DataSet::createDataSets(): wrong config syntax" << std::endl;
	    std::cerr << "  when specifying the scale in line with key '" << key << "'" << std::endl;
	    std::cerr << "  Syntax is '..., scale : expr, ...', where 'expr' is a float" << std::endl;
	  }
	  scale = (it->value("scale")).Atof();
	}
	// Optionally, parse uncertainties:
	// Get all key-value pairs that contain the key 'uncertainty'
	// The expected format is 'uncertainty <label> : ...'
	std::vector<TString> uncNames = it->listOfNames("uncertainty");
	for(std::vector<TString>::const_iterator uit = uncNames.begin();
	    uit != uncNames.end(); ++uit) {
	  // Find uncertainty label
	  TString tmp = "";	// this will just read 'uncertainty' and is ignored
	  TString ul = "";	// this will be the label, if specified
	  Config::split(*uit," ",tmp,ul);

	  // Special case: no uncertainty label specified
	  // Assume this is the total uncertainty and there are
	  // no other sources
	  if( ul == "" ) {
	    if( uncNames.size() > 1 ) {
	      std::cerr << "\n\nERROR in DataSet::createDataSets(): wrong config syntax" << std::endl;
	      std::cerr << "  when specifying the uncertainties in line with key '" << key << "'" << std::endl;
	      exit(-1);
	    }
	    ul = "syst. uncert.";	// Default uncertainty label
	  }
	  uncLabel.push_back(ul);

	  // Now, parse the uncertainty value for the lower and upper
	  // uncertainty variables
	  std::vector<TString> uCfgs;
	  Config::split(it->value(*uit),",",uCfgs);
	  // Case 1: one uncertainty, used as symmetric uncertainty
	  if( uCfgs.size() == 1 ) {
	    uncDn.push_back(uCfgs.front());
	    uncUp.push_back(uCfgs.front());
	  }
	  // Case 2: separate lower and upper uncertainty,
	  // specified by '-' and '+', respectively
	  else if( uCfgs.size() == 2 &&
		   ( 
		    ( uCfgs.at(0).Contains("+") && uCfgs.at(1).Contains("-") )
		    ||
		    ( uCfgs.at(0).Contains("-") && uCfgs.at(1).Contains("+") )
		     )
		   ) {
	    if( uCfgs.at(0).Contains("+") && uCfgs.at(1).Contains("-") ) {
	      uncDn.push_back(Config::after(uCfgs.at(1),"-"));
	      uncUp.push_back(Config::after(uCfgs.at(0),"+"));
	    } else if( uCfgs.at(0).Contains("-") && uCfgs.at(1).Contains("+") ) {
	      uncDn.push_back(Config::after(uCfgs.at(0),"-"));
	      uncUp.push_back(Config::after(uCfgs.at(1),"+"));
	    }
	  }
	  else {
	    std::cerr << "\n\nERROR in DataSet::createDataSets(): wrong config syntax" << std::endl;
	    std::cerr << "  when specifying the uncertainties in line with key '" << key << "'" << std::endl;
	    exit(-1);
	  }
	}

	// First, create basic (unselected) datasets and
	// store it in global map of datasets
	DataSet* basicDataSet = new DataSet(DataSet::toType(type),label,"unselected",file,tree,weight,uncDn,uncUp,uncLabel,scale);
	dataSetUidMap_[basicDataSet->uid()] = basicDataSet;

	// From this one, create selected datasets
	for(SelectionIt selIt = Selection::begin();
	    selIt != Selection::end(); ++selIt) {
	  if( (*selIt)->uid() != "unselected" ) {
	    // Select events from basic dataset
	    Events selectedEvts = (*selIt)->apply(basicDataSet->evtsBegin(),basicDataSet->evtsEnd());
	    // Create selected dataset and store it
	    // in global map of datasets
	    DataSet* selectedDataSet = new DataSet(basicDataSet,(*selIt)->uid(),selectedEvts);
	    dataSetUidMap_[selectedDataSet->uid()] = selectedDataSet;
	  }
	}
      } else {
	std::cerr << "\n\nERROR in DataSet::createDataSets(): wrong config syntax" << std::endl;
	std::cerr << "  in line with key '" << key << "'" << std::endl;
	std::cerr << "  in config file '" << cfg.fileName() << "'." << std::endl;
	std::cerr << "  Syntax is '" << key << " : label [label], type [type], file [fileName], tree [treeName], weight <weight_expr>'" << std::endl;
	exit(-1);
      }
    }
    isInit_ = true;
    std::cout << "ok" << std::endl;
  }
}


void DataSet::clear() {
  for(std::map<TString,const DataSet*>::iterator it = dataSetUidMap_.begin();
      it != dataSetUidMap_.end(); ++it) {
    delete it->second;
  }
}


DataSet::DataSet(Type type, const TString &label, const TString &selectionUid, const TString &fileName, const TString &treeName, const TString &weight, const std::vector<TString> &uncDn, const std::vector<TString> &uncUp, const std::vector<TString> &uncLabel, double scale)
  : hasMother_(false), type_(type), label_(label), selectionUid_(selectionUid) {
  if( uidExists(uid()) ) {
    std::cerr << "\n\nERROR in DataSet::DataSet(): a dataset with label '" << label << "' and selection '" << selectionUid << "' already exists." << std::endl;
    exit(-1);
  }

  // Read events from tree
  EventBuilder ebd;
  evts_ = ebd(fileName,treeName,weight,uncDn,uncUp,uncLabel,scale);

  // Compute yield and uncertainties
  computeYield();
}


DataSet::DataSet(const DataSet *ds, const TString &selectionUid, const Events &evts)
  : hasMother_(true), type_(ds->type()), label_(ds->label()), selectionUid_(selectionUid) {
  if( uidExists(uid()) ) {
    std::cerr << "\n\nERROR in DataSet::DataSet(): a dataset with label '" << label_ << "' and selection '" << selectionUid << "' already exists." << std::endl;
    exit(-1);
  }
  
  // Store events
  for(EventIt it = evts.begin(); it != evts.end(); ++it) {
    evts_.push_back(*it);
  }

  // Compute yield and uncertainties
  computeYield();
}


DataSet::~DataSet() {
  if( !hasMother_ ) {
    for(Events::iterator it = evts_.begin(); it != evts_.end(); ++it) {
      delete *it;
    }
  }
  evts_.clear();
}


// Compute yield (weighted number of events)
// and uncertainties
void DataSet::computeYield() {
  yield_  = 0.;
  stat_   = 0.;
  systDn_ = 0.;
  systUp_ = 0.;
  for(EventIt it = evts_.begin(); it != evts_.end(); ++it) {
    yield_ += (*it)->weight();
    if( (*it)->hasUnc() ) {
      systDn_ += (*it)->weightUncDn();
      systUp_ += (*it)->weightUncUp();
    }
  }
  if( evts_.front()->hasUnc() ) {
    hasSyst_ = true;
    systDn_ = std::abs(yield_-systDn_);
    systUp_ = std::abs(systUp_-yield_);
  } else {
    hasSyst_ = false;
  }
  stat_ = sqrt(yield_);
}
