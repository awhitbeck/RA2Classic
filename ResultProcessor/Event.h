#ifndef EVENT_H
#define EVENT_H

#include <map>
#include <vector>

#include "TString.h"

class Event {
  friend class EventBuilder;

public:
  Event() : weight_(1.), relTotalUncDn_(0.), relTotalUncUp_(0.) {};
  Event(double weight) : weight_(weight), relTotalUncDn_(0.), relTotalUncUp_(0.) {};
  ~Event() {};

  double get(const TString &var) const;
  double weight() const { return weight_; }
  bool hasUnc() const { return relUncDn_.size() > 0; }
  double weightUncDn() const { return weight()*(1.-relTotalUncDn()); };
  double weightUncUp() const { return weight()*(1.+relTotalUncUp()); };
  double relTotalUncDn() const { return relTotalUncDn_; };
  double relTotalUncUp() const { return relTotalUncUp_; };
  double relUncDn(const TString &label) const;
  double relUncUp(const TString &label) const;
  
private:
  const double weight_;

  std::map<TString,double> vars_;
  double relTotalUncDn_;
  double relTotalUncUp_;
  std::map<TString,double> relUncDn_;
  std::map<TString,double> relUncUp_;

  void set(const TString &var, double val);
  void addRelUnc(double dn, double up, const TString &label = "label");
};

typedef std::vector<Event*> Events;
typedef std::vector<Event*>::const_iterator EventIt;
#endif
