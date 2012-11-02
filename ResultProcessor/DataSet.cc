#include <cstdlib>
#include <iostream>

#include "DataSet.h"
#include "EventBuilder.h"
#include "Variable.h"

std::set<TString> DataSet::labels_;
std::map<TString,DataSet::Type> DataSet::types_;

bool DataSet::exists(const TString &label) {
  return DataSet::labels_.find(label) != DataSet::labels_.end();
}

DataSet::Type DataSet::type(const TString &label) {
  DataSet::Type type;
  std::map<TString,DataSet::Type>::const_iterator it = types_.find(label);
  if( it == types_.end() ) {
    std::cerr << "ERROR in DataSet::type(): DataSet with label '" << label << "' does not exist" << std::endl;
    exit(-1);
  }
  
  return it->second;
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


std::vector<DataSet*> DataSet::createDataSets(const Config &cfg, const TString key) {
  std::vector<DataSet*> dataSets;

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
	if( !(it->value("weight")).IsFloat() ) {
	  std::cerr << "\n\nERROR in DataSet::createDataSets(): wrong config syntax" << std::endl;
	  std::cerr << "  when specifying the scale in line with key '" << key << "'" << std::endl;
	  std::cerr << "  Syntax is '..., scale : expr, ...', where 'expr' is a float" << std::endl;
	}
	scale = (it->value("weight")).Atof();
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
      dataSets.push_back(new DataSet(DataSet::toType(type),label,"preselection",file,tree,weight,uncDn,uncUp,uncLabel,scale));
    } else {
      std::cerr << "\n\nERROR in DataSet::createDataSets(): wrong config syntax" << std::endl;
      std::cerr << "  in line with key '" << key << "'" << std::endl;
      std::cerr << "  in config file '" << cfg.fileName() << "'." << std::endl;
      std::cerr << "  Syntax is '" << key << " : label [label], type [type], file [fileName], tree [treeName], weight <weight_expr>'" << std::endl;
      exit(-1);
    }
  }

  return dataSets;
}



DataSet::DataSet(Type type, const TString &label, const TString &selection, const TString &fileName, const TString &treeName, const TString &weight, const std::vector<TString> &uncDn, const std::vector<TString> &uncUp, const std::vector<TString> &uncLabel, double scale)
  : hasMother_(false), type_(type), label_(label), selectionLabel_(selection) {
  if( exists(label) ) {
    std::cerr << "\n\nERROR in DataSet::DataSet(): a dataset with label '" << label << "' already exists." << std::endl;
    exit(-1);
  }
  DataSet::labels_.insert(label);
  DataSet::types_[label] = type;
  EventBuilder ebd;
  evts_ = ebd(fileName,treeName,weight,uncDn,uncUp,uncLabel,scale);
}


DataSet::DataSet(Type type, const TString &label, const TString &selection, const Events &evts)
  : hasMother_(true), type_(type), label_(label), selectionLabel_(selection) {
  for(EventIt it = evts.begin(); it != evts.end(); ++it) {
    evts_.push_back(*it);
  }
}


DataSet::~DataSet() {
  if( !hasMother_ ) {
    for(Events::iterator it = evts_.begin(); it != evts_.end(); ++it) {
      delete *it;
    }
  }
  evts_.clear();
}
