#ifndef GLOBAL_PARAMETERS_H
#define GLOBAL_PARAMETERS_H

#include "TString.h"

#include "Config.h"


class GlobalParameters {
public:
  static void init(const Config &cfg, const TString &key);

  static TString lumi() { return lumi_; }
  static TString analysisId() { return id_; }
  static TString resultDir() { return "results/"+analysisId(); }

  static TString cleanName(const TString &name);

private:
  static TString lumi_;
  static TString id_;
};
#endif
