#ifndef OUTPUT_H
#define OUTPUT_H

#include <vector>
#include <map>

#include "TCanvas.h"
#include "TString.h"

#include "GlobalParameters.h"


class Output {
public:
  Output();
  ~Output() {};

  void addPlot(TCanvas* can, const TString &var, const TString &selection);
  void addPlot(TCanvas* can, const TString &var, const TString &dataSetLabel, const TString &selection);
  void addPlot(TCanvas* can, const TString &var, const std::vector<TString> &dataSetLabels1, const std::vector<TString> &dataSetLabels2, const TString &selection);

  void createLaTeXSlide() const;


private:
  std::map< TString, TString > dirs_;
  std::map< TString, std::map< TString, std::vector<TString> > > plotsSingleSpectrum_;
  std::map< TString, std::vector<TString> > plotsNormedSpectra_;
  std::map< TString, std::map< TString, std::vector<TString> > > plotsStack_;

  TString resultDir() const { return "results/"+GlobalParameters::analysisId(); }
  TString dir(const TString &selection);
  TString cleanName(const TString &name) const;
  void storeCanvas(TCanvas* can, const TString &selection, const TString &plotName);
};
#endif
