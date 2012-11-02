// $Id:  $

#ifndef SELECTION_PRINTER_H
#define SELECTION_PRINTER_H

#include <map>
#include <vector>

#include "TString.h"


class SelectionPrinter {
public:
  void operator()() const;
  void add(const TString &dataSetName, const TString &selection, double yield);

private:
  std::map< TString, std::map<TString,double> > yields_;
  unsigned int nDataSets() const;
  unsigned int sizeOfSelectionLabels() const;
};
#endif
