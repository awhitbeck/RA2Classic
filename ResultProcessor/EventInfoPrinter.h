// $Id: EventInfoPrinter.h,v 1.2 2012/11/02 16:18:58 mschrode Exp $

#ifndef EVENT_INFO_PRINTER_H
#define EVENT_INFO_PRINTER_H

#include <list>
#include <map>
#include <set>
#include <vector>

#include "Config.h"
#include "DataSet.h"
#include "Event.h"

class EventInfoPrinter {
public:
  EventInfoPrinter(const std::vector<DataSet*> &dataSets, const Config &cfg);
  ~EventInfoPrinter() {};

private:
  const Config &cfg_;
  const std::vector<DataSet*> dataSets_;

  std::map< TString, unsigned int > selectionVariables_;
  std::map< TString, std::set<const Event*> > printedEvts_;

  bool init(const TString &key);
  void selectEvents();
  void print() const;
  std::list<TString> listOfPrintedVariables() const;
  bool printAllEvents() const;

  // To sort evts according to one of their quantities
  class EvtValPair {
  public:
    static bool valueGreaterThan(const EvtValPair *idx1, const EvtValPair *idx2);

    EvtValPair(const Event *evt, double value)
      : evt_(evt), val_(value) {}

    const Event* event() const { return evt_; }
    double value() const { return val_; }

  private:
    const Event* evt_;
    const double val_;
  };
};
#endif
