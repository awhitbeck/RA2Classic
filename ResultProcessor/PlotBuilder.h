#ifndef PLOT_BUILDER_H
#define PLOT_BUILDER_H

#include <map>
#include <vector>

#include "TCanvas.h"
#include "TGraphAsymmErrors.h"
#include "TH1.h"
#include "TLegend.h"
#include "TPaveText.h"
#include "TString.h"

#include "Config.h"
#include "DataSet.h"


class PlotBuilder {
public:
  PlotBuilder(const std::vector<DataSet*> &dataSets, const Config &cfg, const TString &outDir);
  ~PlotBuilder();

private:
  class HistParams {
  public:
    HistParams() : nBins_(1), xMin_(0), xMax_(1), logy_(false), norm_(false) {};
    HistParams(const TString &cfg);

    int nBins() const { return nBins_; }
    double xMin() const { return xMin_; }
    double xMax() const { return xMax_; }
    bool logy() const { return logy_; }
    bool norm() const { return norm_; }

  private:
    int nBins_;
    double xMin_;
    double xMax_;
    bool logy_;
    bool norm_;
  };

  static unsigned int count_;

  const Config &cfg_;
  const unsigned int canSize_;
  const std::vector<DataSet*> dataSets_;
  const TString outDir_;

  std::map<TString,int> markers_;
  std::map<TString,int> colors_;
  std::map<TString,TString> dataSetLabelsInPlot_;

  void run(const TString &key) const;
  void setStyle(const TString &key);
  void plotSpectrum(const TString &var, const TString &dataLabel, const HistParams &histParams) const;
  void plotSpectra(const TString &var, const std::vector<TString> &dataSetLabels, const HistParams &histParams) const;
  void plotComparisonOfSpectra(const TString &var, const std::vector<TString> &dataSetLabels1, const std::vector<TString> &dataSetLabels2, const HistParams &histParams) const;
  DataSet::Type createDistribution(const TString &dataSetLabel, const TString &var, TH1* &h, TGraphAsymmErrors* &uncert, const HistParams &histParams) const;
  DataSet::Type createStack(const std::vector<TString> &dataSetLabels, const TString &var, std::vector<TH1*> &hists, std::vector<TString> &legEntries, TGraphAsymmErrors* &uncert, const HistParams &histParams) const;
  int color(const TString &dataSetLabel) const;
  int markerStyle(const TString &dataSetLabel) const;
  void setMarkerStyle(TH1* h, const TString &dataSetLabel) const;
  void setGenericStyle(TH1* h, const TString &dataSetLabel) const;
  void setXTitle(TH1* h, const TString &var) const;
  void setYTitle(TH1* h, const TString &var) const;
  TPaveText* header(bool showLumi, const TString &add = "") const;
  TLegend* legend(unsigned int nEntries) const;
  TString lumiLabel() const;
  TString plotName(const TString &var) const;
  TString plotName(const TString &var, const TString &dataSetLabel) const;
  TString plotName(const TString &var, const std::vector<TString> &dataSetLabels1, const std::vector<TString> &dataSetLabels2) const;
  void storeCanvas(TCanvas* can, const TString &name) const;
  DataSet* dataSet(const TString &label) const;
  TString dataSetLabelInPlot(const TString &dataSetLabel) const;
  TString dataSetTypeLabel(DataSet::Type type) const;
  void setYRange(TH1* &h, double logMin = -1.) const;
  bool checkForUnderOverFlow(const TH1* h, const TString &var, const TString &dataSetLabel) const;
};
#endif
