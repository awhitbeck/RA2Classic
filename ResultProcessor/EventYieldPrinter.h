// $Id: $

#ifndef EVENT_YIELD_PRINTER_H
#define EVENT_YIELD_PRINTER_H

#include <map>
#include <vector>

#include "TString.h"


class EventYieldPrinter {
public:
  void operator()() const;
  void add(const TString &dataSetName, const TString &selection, double nEvents);
  void add(const TString &dataSetName, const TString &selection, double nEvents, double yield);

private:
  std::map< TString, std::map<TString,TString> > yields_; // (Selection,DataSet,Yield)
  void add(const TString &dataSetName, const TString &selection, const TString &yield);
  unsigned int nDataSets() const;
  unsigned int sizeOfSelectionLabels() const;
};
#endif
