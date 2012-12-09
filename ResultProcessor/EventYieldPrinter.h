// $Id: EventYieldPrinter.h,v 1.1 2012/11/05 14:52:14 mschrode Exp $

#ifndef EVENT_YIELD_PRINTER_H
#define EVENT_YIELD_PRINTER_H

class EventYieldPrinter {
public:
  void operator()() const;

private:
  unsigned int sizeOfSelectionLabels() const;
};
#endif
