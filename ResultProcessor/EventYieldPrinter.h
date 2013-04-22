// $Id: EventYieldPrinter.h,v 1.4 2013/02/09 18:44:41 mschrode Exp $

#ifndef EVENT_YIELD_PRINTER_H
#define EVENT_YIELD_PRINTER_H

#include <vector>

#include "TString.h"

class EventYieldPrinter {
public:
  EventYieldPrinter();

private:
  const DataSets inputDataSets_;

  std::vector< std::vector<TString> > summaryTable_;
  std::vector<unsigned int> summaryTableColw_;

  void prepareSummaryTable();
  void printToScreen() const;
  void printToLaTeX(const TString &outFileName) const;
  void printDataCard(const TString &outFileName) const;
};
#endif
