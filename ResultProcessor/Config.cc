#include <cstdlib>
#include <fstream>
#include <iostream>

#include "Rtypes.h"

#include "Config.h"


// Constructor. Parses the configfile and stores the definitions.
// They can be obtained using the 'operator()(key)' method.
//
// The config syntax is as follows:
// - empty line: an empty line is ignored
// - comment: a line starting with '#' is ignored
// - definition: a line of the form '<key> :: <attributes>',
//   where the attributes part is a semi-colon (';') separated
//   list of <name> : <value> pairs. Keys can occour several
//   times.
// ----------------------------------------------------------------------------
Config::Config(const TString &fileName) 
  : fileName_(fileName), keyAndAttributesDelimiter_("::"), attributeNameAndValueDelimiter_(":") {


  // Open file for reading
  std::ifstream file(fileName_.Data());
  if( !file.is_open() ) {
    std::cerr << "\n\nERROR error opening config-file '" << fileName_ << "'\n";
    exit(-1);
  }


  // Loop over lines and parse
  unsigned int lineNum = 0;
  std::string line = "";
  while( !file.eof() ) {
    ++lineNum;
    std::getline(file,line);
    if( !isComment(line) && line.size() ) {
      // separate line into key and attribute list
      std::string key = "";
      std::string attrList;
      if( split(line,keyAndAttributesDelimiter_,key,attrList) ) {
	TString tKey = key;
	std::map< TString,std::vector<Attributes> >::iterator it = keyAttributesMap_.find(tKey);
	if( it == keyAttributesMap_.end() ) {
	  std::vector<Config::Attributes> attr;
	  attr.push_back(getAttributes(attrList,lineNum));
	  keyAttributesMap_[tKey] = attr;
	} else {
	  it->second.push_back(getAttributes(attrList,lineNum));
	}
      }
    }
  }

  file.close();
}


// Returns a vector of attribute (name-value pair) lists for
// a given key. Each vector entry corresponds to one line
// in the config file.
// ----------------------------------------------------------------------------
std::vector<Config::Attributes> Config::operator()(const TString &key) const {
  std::map< TString,std::vector<Attributes> >::const_iterator it = keyAttributesMap_.find(key);
  if( it != keyAttributesMap_.end() ) {
    return it->second;
  } else {
    std::vector<Config::Attributes> list;
    return list;
  }
}


// ----------------------------------------------------------------------------
Config::Attributes Config::getAttributes(const std::string &line, unsigned int lineNum) const {
  Config::Attributes result(lineNum);
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
TString Config::after(const TString &str, const TString &delim) {
  TString first = "";
  TString second = "";
  Config::split(str,delim,first,second);

  return second;
}


// ----------------------------------------------------------------------------
bool Config::enclosed(const TString &str, const TString &delimStart, const TString &delimEnd, TString &encl) {
  bool hasDelims = false;
  std::string strt(str.Data());
  std::string enclt;
  size_t start = strt.find(delimStart.Data());
  size_t end = strt.find(delimEnd.Data());
  if( start != std::string::npos && end != std::string::npos && end > start ) {
    hasDelims = true;
    enclt = strt.substr(start+delimStart.Length(),end-start-1);
  }
  trim(enclt);
  encl = enclt;

  return hasDelims;
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


std::vector<TString> Config::Attributes::listOfNames() const {
  std::vector<TString> list(values_.size());
  unsigned int i = 0;
  for(std::map<TString,TString>::const_iterator it = values_.begin();
      it != values_.end(); ++it,++i) {
    list.at(i) = it->first;
  }

  return list;
}


std::vector<TString> Config::Attributes::listOfNames(const TString &containedStr) const {
  std::vector<TString> list;
  for(std::map<TString,TString>::const_iterator it = values_.begin();
      it != values_.end(); ++it) {
    if( (it->first).Contains(containedStr) ) {
      list.push_back(it->first);
    }
  }

  return list;
}
