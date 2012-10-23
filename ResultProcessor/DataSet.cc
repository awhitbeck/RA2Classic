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
  else if( type == "Bkg" || type == "bkg" ) result = Bkg;
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
      TString weightVarFromTree = "";
      double weightScale = 1.;
      if( it->nValues() == 5 ) {
	TString weightScaleStr;
	if( Config::split(it->value("weight"),"*",weightScaleStr,weightVarFromTree) ) {
	  weightScale = weightScaleStr.Atof();
	} else if( Variable::exists(it->value("weight")) ){
	  weightVarFromTree = it->value("weight");
	} else {
	  weightScale = it->value("weight").Atof();
	}
      }
      dataSets.push_back(new DataSet(DataSet::toType(type),label,"preselection",file,tree,weightVarFromTree,weightScale));
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



DataSet::DataSet(Type type, const TString &label, const TString &selection, const TString &fileName, const TString &treeName, const TString &weightVarName, double weightScale)
  : hasMother_(false), type_(type), label_(label), selectionLabel_(selection), weightScale_(weightScale) {
  if( exists(label) ) {
    std::cerr << "\n\nERROR in DataSet::DataSet(): a dataset with label '" << label << "' already exists." << std::endl;
    exit(-1);
  }
  DataSet::labels_.insert(label);
  DataSet::types_[label] = type;
  EventBuilder ebd;
  evts_ = ebd(fileName,treeName,weightVarName,weightScale_);
}


DataSet::DataSet(Type type, const TString &label, const TString &selection, const Events &evts, double weightScale)
  : hasMother_(true), type_(type), label_(label), selectionLabel_(selection), weightScale_(weightScale) {
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
