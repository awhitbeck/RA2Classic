#ifndef MR_RA2_H
#define MR_RA2_H

#include <vector>

#include "TString.h"

#include "Config.h"
#include "DataSet.h"
#include "PlotBuilder.h"
#include "Selection.h"


class MrRA2 {
public:
  MrRA2(const TString& configFileName);
  ~MrRA2();

private:
  std::vector<DataSet*> dataSets_;
  std::vector<Selection*> selections_;

  void init(const Config &cfg, const TString &key);
  void makePlots(const std::vector<DataSet*> &dataSets, const Config &cfg, const TString &outDir) const {
    PlotBuilder(dataSets,cfg,outDir);
  }
};
#endif
