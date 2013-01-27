// $Id: EventYieldPrinter.h,v 1.2 2012/12/09 14:47:25 mschrode Exp $

#ifndef EVENT_YIELD_PRINTER_H
#define EVENT_YIELD_PRINTER_H

class EventYieldPrinter {
public:
  EventYieldPrinter();

private:
  void printToScreen() const;
  void printToLaTeX() const;
};
#endif
