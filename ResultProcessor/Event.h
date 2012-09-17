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

  float weight() const { return weight_; }
  float get(const TString &var) const;
  
private:
  float weight_;
  std::map<TString,float> vars_;

  void set(const TString &var, float val);
  void setWeight(float weight) { weight_ = weight; }
};

typedef std::vector<Event*> Events;
typedef std::vector<Event*>::const_iterator EventIt;
#endif
