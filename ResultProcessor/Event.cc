#include "Event.h"


double Event::get(const TString &var) const {
  double val = 0.;
  std::map<TString,double>::const_iterator it = vars_.find(var);
  if( it != vars_.end() ) val = it->second;
    
  return val;
}
  

void Event::set(const TString &var, double val) {
  std::map<TString,double>::iterator it = vars_.find(var);
  if( it != vars_.end() ) {
    it->second = val;
  } else {
    vars_[var] = val;
  }
}
