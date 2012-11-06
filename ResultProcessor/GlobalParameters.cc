#include <cstdlib>
#include <iostream>
#include <sys/stat.h>

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

  std::cout << "Preparing the environment...  " << std::flush;
  mkdir("results",S_IRWXU);
  mkdir(("results/"+analysisId()).Data(),S_IRWXU);

  std::cout << "ok" << std::endl;
}


TString GlobalParameters::cleanName(const TString &name) {
  TString cleanedName = name;
  cleanedName.ReplaceAll(">","gtr");
  cleanedName.ReplaceAll(" ","_");
  cleanedName.ReplaceAll("#","");
  cleanedName.ReplaceAll("{","");
  cleanedName.ReplaceAll("}","");

  return cleanedName;
}



