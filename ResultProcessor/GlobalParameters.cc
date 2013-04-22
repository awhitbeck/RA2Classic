#include <cstdlib>
#include <iostream>
#include <sys/stat.h>

#include "GlobalParameters.h"


// CVS Information; will be substituted by cvs
TString GlobalParameters::CVSKeyWordRevision_ = "$Revision: 1.11 $";
TString GlobalParameters::CVSKeyWordName_ = "$Name:  $";

bool GlobalParameters::debug_ = false;
TString GlobalParameters::lumi_ = "";
TString GlobalParameters::id_ = "";

void GlobalParameters::init(const Config &cfg, const TString &key) {
  std::cout << "  Setting global parameters...  " << std::flush;
  std::vector<Config::Attributes> attrList = cfg.listOfAttributes(key);
  for(std::vector<Config::Attributes>::const_iterator it = attrList.begin();
      it != attrList.end(); ++it) {
    if( it->hasName("debug") ) it->value("debug") == "true" ? debug_ = true : debug_ = false;
    if( it->hasName("id") ) id_ = it->value("id");
    if( it->hasName("lumi") ) lumi_ = it->value("lumi");
  }
  std::cout << "ok" << std::endl;

  std::cout << "  Preparing the environment...  " << std::flush;
  mkdir("results",S_IRWXU);
  mkdir(("results/"+analysisId()).Data(),S_IRWXU);

  std::cout << "ok" << std::endl;
}


TString GlobalParameters::cvsRevision() {
  TString rev = CVSKeyWordRevision_;
  rev.ReplaceAll(" ","");
  rev.ReplaceAll("$","");
  rev.ReplaceAll("Revision:","");
  
  return rev;
}


TString GlobalParameters::cvsTag() {
  TString name = CVSKeyWordName_;
  name.ReplaceAll(" ","");
  name.ReplaceAll("$","");
  name.ReplaceAll("Name:","");
  
  return name;
}




