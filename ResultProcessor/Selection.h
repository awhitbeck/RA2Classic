#ifndef SELECTION_H
#define SELECTION_H

#include <iomanip>
#include <iostream>
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

  static void clear();


  Selection() {};
  virtual ~Selection() {};

  virtual TString uid() const = 0;
  virtual void print() const = 0;
  virtual Events apply(EventIt begin, EventIt end) const = 0;

protected:
  static std::vector<Selection*> garbageCollection_;


private:
  static Selections selections_;
  static bool isInit_;
};


class Cut : public Selection {
public:
  Cut(const TString &cut, bool isDummy = false);

  TString uid() const { return "Cut: "+cut_; }
  void print() const { 
    std::cout << "    " << cut_ << std::endl;
  }
  Events apply(EventIt begin, EventIt end) const;


private:
  const bool isDummy_;

  TString cut_;
  TString var_;
  bool varIsAbs_;
  double min_;
  double max_;
};


class SelectionSequence : public Selection {
public:
  SelectionSequence(const TString &uid);

  void add(const Selection* sel) { sels_.push_back(sel); }
  void addDummyCut() { sels_.push_back(new Cut("none",true)); }

  TString uid() const { return uid_; }
  void print() const;
  Events apply(EventIt begin, EventIt end) const;
  

private:
  const TString uid_;
  
  std::vector<const Selection*> sels_;
};
#endif
