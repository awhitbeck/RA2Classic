#ifndef EVENT_H
#define EVENT_H

#include <map>
#include <vector>

#include "TString.h"

class Event {
  friend class EventBuilder;

public:
  Event() {};
  ~Event() {};

  double weight() const { return weight_; }
  double get(const TString &var) const;
  
private:
  double weight_;
  std::map<TString,double> vars_;

  void set(const TString &var, double val);
  void setWeight(double weight) { weight_ = weight; }
};

typedef std::vector<Event*> Events;
typedef std::vector<Event*>::const_iterator EventIt;
#endif
