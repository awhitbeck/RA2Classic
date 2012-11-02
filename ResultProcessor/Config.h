#ifndef CONFIG_H
#define CONFIG_H

#include <map>
#include <string>
#include <vector>

#include "TString.h"

class Config {
public:
  class Attributes {
    friend class Config;

  public:
    bool hasName(const TString &name) const { return values_.find(name) != values_.end(); }
    TString value(const TString &name) const;
    unsigned int nValues() const { return values_.size(); }
    std::vector<TString> listOfNames() const;
    std::vector<TString> listOfNames(const TString &containedStr) const;

  private:
    std::map<TString,TString> values_;

    void add(const TString &name, const TString &value) { values_[name] = value; }
  };

  static bool split(const TString &str, const TString &delim, std::vector<TString> &parts);
  static bool split(const TString &str, const TString &delim, TString &first, TString &second);
  static TString after(const TString &str, const TString &delim);
  static bool enclosed(const TString &str, const TString &delimStart, const TString &delimEnd, TString &encl);
  static int color(const TString &cfg);

  Config(const TString &fileName)
    : fileName_(fileName), labelAndAttributeListDelimiter_("::"), attributeNameAndValueDelimiter_(":") {};

  TString fileName() const { fileName_; }
  std::vector<Attributes> listOfAttributes(const TString &label) const;


private:
  static bool split(const std::string &str, const std::string &delim, std::string &first, std::string &second);
  static void trim(std::string &str);
  static bool isComment(const std::string &line);

  const std::string labelAndAttributeListDelimiter_;
  const std::string attributeNameAndValueDelimiter_;
  const TString fileName_;

  Attributes getAttributes(const std::string &line) const;
};
#endif
