#include "Event.h"

#include <cmath>


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


double Event::relUncDn(const TString &label) const {
  double unc = 0.;
  std::map<TString,double>::const_iterator it = relUncDn_.find(label);
  if( it != relUncDn_.end() ) {
    unc = it->second;
  }

  return unc;
}


double Event::relUncUp(const TString &label) const {
  double unc = 0.;
  std::map<TString,double>::const_iterator it = relUncUp_.find(label);
  if( it != relUncUp_.end() ) {
    unc = it->second;
  }

  return unc;
}


void Event::addRelUnc(double dn, double up, const TString &label) {
  if( relUncDn_.find(label) == relUncDn_.end() &&
      relUncUp_.find(label) == relUncUp_.end()    ) { 
    // Add to list of uncertainties
    relUncDn_[label] = dn;
    relUncUp_[label] = up;
    // Recompute total uncertainty
    // (quadratic sum of all uncertainties)
    relTotalUncDn_ = sqrt( relTotalUncDn_*relTotalUncDn_ + dn*dn );
    relTotalUncUp_ = sqrt( relTotalUncUp_*relTotalUncUp_ + up*up );
  }
}

