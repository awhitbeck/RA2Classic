// $Id: EventYieldPrinter.h,v 1.3 2013/01/27 23:18:34 mschrode Exp $

#ifndef EVENT_YIELD_PRINTER_H
#define EVENT_YIELD_PRINTER_H

#include "TString.h"

class EventYieldPrinter {
public:
  EventYieldPrinter();

private:
  void printToScreen() const;
  void printToLaTeX(const TString &outFileName) const;
  void printDataCard(const TString &outFileName) const;
};
#endif
