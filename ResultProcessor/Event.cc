#include "Event.h"


float Event::get(const TString &var) const {
  float val = 0.;
  std::map<TString,float>::const_iterator it = vars_.find(var);
  if( it != vars_.end() ) val = it->second;
    
  return val;
}
  

void Event::set(const TString &var, float val) {
  std::map<TString,float>::iterator it = vars_.find(var);
  if( it != vars_.end() ) {
    it->second = val;
  } else {
    vars_[var] = val;
  }
}
