#include <cstdlib>
#include <fstream>
#include <iostream>

#include "Rtypes.h"

#include "Config.h"


// ----------------------------------------------------------------------------
std::vector<Config::Attributes> Config::listOfAttributes(const TString &label) const {
  std::vector<Config::Attributes> list;

  // Open file for reading
  std::ifstream file(fileName_.Data());
  if( !file.is_open() ) {
    std::cerr << "\n\nERROR in Config::listOfAttributes(): error opening file '" << fileName_ << "'\n";
    exit(-1);
  }

  // Loop over lines and parse
  std::string line = "";
  while( !file.eof() ) {
    std::getline(file,line);
    if( !isComment(line) && line.size() ) {
      // separate line into label and attribute list
      std::string labelCand = "";
      std::string attrList;
      if( split(line,labelAndAttributeListDelimiter_,labelCand,attrList) ) {
	if( labelCand == label ) {
	  list.push_back(getAttributes(attrList));
	}
      }
    }
  }

  return list;
}


// ----------------------------------------------------------------------------
Config::Attributes Config::getAttributes(const std::string &line) const {
  Config::Attributes result;
  std::string str = line;
  while( str.find(";") != std::string::npos ) {
    // Comma-separated list of attributes
    size_t end = str.find(";");
    std::string nameAndValue = str.substr(0,end);
    str = str.substr(end+1,str.size());

    // Each attribute has a name and value, separated by attributeNameAndValueDelimiter_
    std::string name = "";
    std::string value = "";
    split(nameAndValue,attributeNameAndValueDelimiter_,name,value);
    result.add(name,value);
  }
  // Last attribute
  trim(str);
  std::string name = "";
  std::string value = "";
  split(str,attributeNameAndValueDelimiter_,name,value);
  result.add(name,value);

  return result;
}


// ----------------------------------------------------------------------------
bool Config::split(const TString &str, const TString &delim, std::vector<TString> &parts) {
  TString rest = str;
  TString part1 = "";
  TString part2 = "";
  while( split(rest,delim,part1,part2) ) {
    parts.push_back(part1);
    rest = part2;
  }
  parts.push_back(rest);

  return split(str,delim,part1,part2);
}


// ----------------------------------------------------------------------------
bool Config::split(const TString &str, const TString &delim, TString &first, TString &second) {
  std::string strt(str.Data());
  std::string delimt(delim.Data());
  std::string firstt(first.Data());
  std::string secondt(second.Data());
  bool result = split(strt,delimt,firstt,secondt);
  first = firstt.c_str();
  second = secondt.c_str();

  return result;
}


// ----------------------------------------------------------------------------
bool Config::split(const std::string &str, const std::string &delim, std::string &first, std::string &second) {
  bool hasDelim = false;
  first = str;
  second = "";
  if( str.find(delim) != std::string::npos ) {
    hasDelim = true;
    size_t end = str.find(delim);
    first = str.substr(0,end);
    second = str.substr(end+delim.size(),str.size());
  }
  trim(first);
  trim(second);

  return hasDelim;
}


// ----------------------------------------------------------------------------
bool Config::isComment(const std::string &line) {
  bool result = false;
  if( line.length() && line.at(0) == '#' ) result = true;

  return result;
}


// ----------------------------------------------------------------------------
void Config::trim(std::string &str) {
  while( str.size() && str[0] == ' ' ) str.erase(0,1);
  while( str.size() && str[str.size()-1] == ' ' ) str.erase(str.size()-1,str.size());    
}


// Expects one of the following configuration strings:
// - an integer number
// - a TColor mnemonic, e.g. kRed
// - a TColor mnemonic modified by an integer number, e.g. kRed+3, kBlue-2
// ----------------------------------------------------------------------------
int Config::color(const TString &cfg) {
  int color = 1;
  if( cfg.Contains("k") ) {	// Expect mnemonic
    std::string kSth;
    int modifier = 0;
    std::string str(cfg.Data());
    std::string modifierStr;
    if( split(str,"+",kSth,modifierStr) ) {
      TString tmp(modifierStr);
      modifier = tmp.Atoi();
    } else if( split(str,"-",kSth,modifierStr) ) {
      TString tmp(modifierStr);
      modifier = -1*(tmp.Atoi());
    }
    if( kSth == "kYellow" ) color = kYellow+modifier;
    else if( kSth == "kOrange" ) color = kOrange+modifier;
    else if( kSth == "kRed" ) color = kRed+modifier;
    else if( kSth == "kPink" ) color = kPink+modifier;
    else if( kSth == "kMagenta" ) color = kMagenta+modifier;
    else if( kSth == "kViolet" ) color = kViolet+modifier;
    else if( kSth == "kBlue" ) color = kBlue+modifier;
    else if( kSth == "kAzure" ) color = kAzure+modifier;
    else if( kSth == "kCyan" ) color = kCyan+modifier;
    else if( kSth == "kTeal" ) color = kTeal+modifier;
    else if( kSth == "kGreen" ) color = kGreen+modifier;
    else if( kSth == "kSpring" ) color = kSpring+modifier;
  } else {			// Expect integer
    color = cfg.Atoi();
  }

  return color;
}


TString Config::Attributes::value(const TString &name) const {
  TString val = "";
  std::map<TString,TString>::const_iterator it = values_.find(name);
  if( it != values_.end() ) val = it->second;

  return val;
}
