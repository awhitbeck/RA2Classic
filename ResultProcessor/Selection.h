#ifndef SELECTION_H
#define SELECTION_H

#include <iomanip>
#include <iostream>
#include <vector>

#include "TString.h"

#include "Config.h"
#include "DataSet.h"

class Selection {
public:
  static std::vector<Selection*> createSelections(const Config &cfg, const TString key);
  static void deleteAllSelections();

  Selection() {};
  virtual ~Selection() {};
  
  virtual DataSet* operator()(const DataSet* dataSet) const = 0;

  virtual TString label() const = 0;
  virtual void print() const = 0;

protected:
  static std::vector<Selection*> garbageCollection_;
};


class SelectionSequence : public Selection {
public:
  SelectionSequence(const TString &label);

  void add(const Selection* sel) { sels_.push_back(sel); }

  DataSet* operator()(const DataSet* dataSet) const;
  TString label() const { return label_; }
  void print() const;


private:
  const TString label_;
  
  std::vector<const Selection*> sels_;
};


class Cut : public Selection {
public:
  Cut(const TString &cut);

  DataSet* operator()(const DataSet* dataSet) const;
  TString label() const { return "Cut: "+cut_; }
  void print() const { 
    std::cout << "      " << std::setw(15) << cut_ << ": " << std::setw(10) << count_ << std::endl;
  }


private:
  TString cut_;
  TString var_;
  bool varIsAbs_;
  double min_;
  double max_;
  std::vector<TString> appliedToDataSets_;

  mutable unsigned int count_;
};
#endif
