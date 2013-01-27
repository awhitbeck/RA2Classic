#ifndef SELECTION_H
#define SELECTION_H

#include <map>
#include <vector>

#include "TString.h"

#include "Config.h"
#include "Event.h"


class Selection;

typedef std::vector<Selection*> Selections;
typedef std::vector<Selection*>::const_iterator SelectionIt;


class Selection {
public:
  static void init(const Config &cfg, const TString key);
  static const Selection* find(const TString &uid);
  static SelectionIt begin() { return selections_.begin(); }
  static SelectionIt end() { return selections_.end(); }
  static unsigned int maxLabelLength();
  static void clear();


  Selection() {};
  virtual ~Selection() {};

  virtual TString uid() const = 0;
  virtual void print() const = 0;
  virtual Events apply(EventIt begin, EventIt end, const TString &dataSetLabel) const = 0;

protected:
  static std::vector<Selection*> garbageCollection_;


private:
  static Selections selections_;
  static bool isInit_;
};


class Cut : public Selection {
public:
  Cut();
  Cut(const TString &cut);

  TString uid() const { return "Cut: "+cut_; }
  void print() const;
  Events apply(EventIt begin, EventIt end, const TString &dataSetLabel) const;


private:
  const bool isDummy_;

  TString cut_;
  TString var_;
  bool varIsAbs_;
  double min_;
  double max_;
  std::vector<TString> appliedToDataSets_;
};


class SelectionSequence : public Selection {
public:
  SelectionSequence(const TString &uid);

  void add(const Selection* sel) { sels_.push_back(sel); }

  TString uid() const { return uid_; }
  void print() const;
  Events apply(EventIt begin, EventIt end, const TString &dataSetLabel) const;
  

private:
  const TString uid_;
  
  std::vector<const Selection*> sels_;
};
#endif
