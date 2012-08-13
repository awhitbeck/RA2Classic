#include <cstdlib>
#include <iostream>

#include "GlobalParameters.h"


TString GlobalParameters::lumi_ = "";
TString GlobalParameters::id_ = "";


void GlobalParameters::init(const Config &cfg, const TString &key) {
  std::cout << "Setting global parameters...  " << std::flush;
  std::vector<Config::Attributes> attrList = cfg.listOfAttributes(key);
  for(std::vector<Config::Attributes>::const_iterator it = attrList.begin();
      it != attrList.end(); ++it) {
    if( it->hasName("id") ) id_ = it->value("id");
    if( it->hasName("lumi") ) lumi_ = it->value("lumi");
  }
  std::cout << "ok" << std::endl;
}
