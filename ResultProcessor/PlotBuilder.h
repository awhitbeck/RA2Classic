#ifndef PLOT_BUILDER_H
#define PLOT_BUILDER_H

#include <map>
#include <vector>

#include "TCanvas.h"
#include "TH1.h"
#include "TLegend.h"
#include "TPaveText.h"
#include "TString.h"

#include "Config.h"
#include "DataSet.h"


class PlotBuilder {
public:
  PlotBuilder(const std::vector<DataSet*> &dataSets, const Config &cfg);
  ~PlotBuilder();

private:
  static unsigned int count_;

  const Config &cfg_;
  const unsigned int canSize_;
  const std::vector<DataSet*> dataSets_;

  std::map<TString,int> markers_;
  std::map<TString,int> colors_;
  std::map<TString,TString> dataSetLabelsInPlot_;

  void run(const TString &key) const;
  void setStyle(const TString &key);
  void plotSpectrum(const TString &var, const TString &dataLabel, const TString &histCfg) const;
  void plotSpectra(const TString &var, const std::vector<TString> &dataSetLabels, const TString &histCfg) const;
  void plotComparisonOfSpectra(const TString &var, const std::vector<TString> &dataSetLabels1, const std::vector<TString> &dataSetLabels2, const TString &histCfg) const;
  DataSet::Type createHistogram(const TString &dataSetLabel, const TString &var, int nBins, double min, double max, TH1* &h) const;
  DataSet::Type createStack(const std::vector<TString> &dataSetLabels, const TString &var, int nBins, double xMin, double xMax, std::vector<TH1*> &hists, std::vector<TString> &legEntries) const;
  void parseHistCfg(const TString &cfg, int &nBins, double &xMin, double &xMax, bool &logy) const;
  void setStyle(TH1* h, const TString &dataSetLabel) const;
  void setXTitle(TH1* h, const TString &var) const;
  void setYTitle(TH1* h, const TString &var) const;
  TPaveText* header(const TString &dataSetLabel = "", bool doNotShowLabel = true, const TString &add = "") const;
  TLegend* legend(unsigned int nEntries) const;
  TString lumiLabel(const TString &dataSetLabel) const;
  TString cleanName(const TString &name) const;
  TString plotName(const TString &var) const;
  TString plotName(const TString &var, const TString &dataSetLabel) const;
  TString plotName(const TString &var, const std::vector<TString> &dataSetLabels1, const std::vector<TString> &dataSetLabels2) const;
  void storeCanvas(TCanvas* can, const TString &name) const;
  DataSet* dataSet(const TString &label) const;
  TString dataSetLabelInPlot(const TString &dataSetLabel) const;
  TString dataSetTypeLabel(DataSet::Type type) const;
  void setYRange(TH1* &h, double logMin = -1.) const;
};
#endif
