#ifndef GLOBAL_PARAMETERS_H
#define GLOBAL_PARAMETERS_H

#include "TString.h"

#include "Config.h"


class GlobalParameters {
public:
  static void init(const Config &cfg, const TString &key);

  static bool debug() { return debug_; }
  static TString lumi() { return lumi_; }
  static TString analysisId() { return id_; }
  static TString defaultUncertaintyLabel() { return "syst. uncert."; }

private:
  static bool debug_;
  static TString lumi_;
  static TString id_;
};
#endif
