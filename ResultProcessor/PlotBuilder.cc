#include <cstdlib>
#include <iostream>

#include "TCanvas.h"
#include "TH1D.h"
#include "TPad.h"
#include "TStyle.h"

#include "GlobalParameters.h"
#include "PlotBuilder.h"
#include "Variable.h"


unsigned int PlotBuilder::count_ = 0;


PlotBuilder::PlotBuilder(const TString &selectionLabel, const std::vector<DataSet*> &dataSets, const Config &cfg)
  : cfg_(cfg), canSize_(500), selectionLabel_(selectionLabel), dataSets_(dataSets) {
  setStyle("plot style");
  run("plot");
}


void PlotBuilder::setStyle(const TString &key) {
  // Zero horizontal error bars
  gStyle->SetErrorX(0);

  //  For the canvas
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetCanvasColor(kWhite);
  gStyle->SetCanvasDefH(800); //Height of canvas
  gStyle->SetCanvasDefW(800); //Width of canvas
  gStyle->SetCanvasDefX(0);   //Position on screen
  gStyle->SetCanvasDefY(0);
  
  //  For the frame
  gStyle->SetFrameBorderMode(0);
  gStyle->SetFrameBorderSize(1);
  gStyle->SetFrameFillColor(kBlack);
  gStyle->SetFrameFillStyle(0);
  gStyle->SetFrameLineColor(kBlack);
  gStyle->SetFrameLineStyle(0);
  gStyle->SetFrameLineWidth(1);
    
  //  For the Pad
  gStyle->SetPadBorderMode(0);
  gStyle->SetPadColor(kWhite);
  gStyle->SetPadGridX(false);
  gStyle->SetPadGridY(false);
  gStyle->SetGridColor(0);
  gStyle->SetGridStyle(3);
  gStyle->SetGridWidth(1);
  
  //  Margins
  gStyle->SetPadTopMargin(0.08);
  gStyle->SetPadBottomMargin(0.19);
  gStyle->SetPadLeftMargin(0.20);
  gStyle->SetPadRightMargin(0.07);

  //  For the histo:
  gStyle->SetHistLineColor(kBlack);
  gStyle->SetHistLineStyle(0);
  gStyle->SetHistLineWidth(2);
  gStyle->SetMarkerSize(1.4);
  gStyle->SetEndErrorSize(4);
  
  //  For the statistics box:
  gStyle->SetOptStat(0);
  
  //  For the axis
  gStyle->SetAxisColor(1,"XYZ");
  gStyle->SetTickLength(0.03,"XYZ");
  gStyle->SetNdivisions(510,"XYZ");
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetStripDecimals(kFALSE);
  
  //  For the axis labels and titles
  gStyle->SetTitleColor(1,"XYZ");
  gStyle->SetLabelColor(1,"XYZ");
  gStyle->SetLabelFont(42,"XYZ");
  gStyle->SetLabelOffset(0.007,"XYZ");
  gStyle->SetLabelSize(0.045,"XYZ");
  gStyle->SetTitleFont(42,"XYZ");
  gStyle->SetTitleSize(0.06,"XYZ");
  gStyle->SetTitleXOffset(1.2);
  gStyle->SetTitleYOffset(1.7);

  //  For the legend
  gStyle->SetLegendBorderSize(0);

  std::vector<Config::Attributes> attrList = cfg_.listOfAttributes(key);
  for(std::vector<Config::Attributes>::const_iterator it = attrList.begin();
      it != attrList.end(); ++it) {
    if( it->hasName("dataset") ) {
      TString dataSetLabel = it->value("dataset");
      if( it->hasName("marker") ) {
	markers_[dataSetLabel] = (it->value("marker")).Atoi();
      }
      if( it->hasName("color") ) {
	colors_[dataSetLabel] = cfg_.color(it->value("color"));
      }
    }
  }
}

void PlotBuilder::run(const TString &key) const {
  std::vector<Config::Attributes> attrList = cfg_.listOfAttributes(key);
  for(std::vector<Config::Attributes>::const_iterator it = attrList.begin();
      it != attrList.end(); ++it) {
    if( it->hasName("variable") && it->hasName("histogram") ) {
      TString variable = it->value("variable");
      if( !Variable::exists(variable) ) {
	std::cerr << "\n\nERROR in PlotBuilder::run(): variable '" << variable << "' does not exist" << std::endl;
	exit(-1);
      }
      TString histogram = it->value("histogram");
      if( it->hasName("dataset") ) { // Sinlge spectrum
	TString dataset = it->value("dataset");
	if( !DataSet::exists(dataset) ) {
	  std::cerr << "\n\nERROR in PlotBuilder::run(): dataset '" << dataset << "' does not exist" << std::endl;
	  exit(-1);
	}
	plotSpectrum(variable,dataset,histogram);
      } else if( it->hasName("dataset1") && it->hasName("dataset2") ) {	// Comparison of two stacked datasets
	std::vector<TString> dataLabels1;
	std::vector<TString> dataLabels2;
	Config::split(it->value("dataset1"),"+",dataLabels1);
	Config::split(it->value("dataset2"),"+",dataLabels2);
	for(std::vector<TString>::const_iterator itd = dataLabels1.begin();
	    itd != dataLabels1.end(); ++itd) {
	  if( !DataSet::exists(*itd) ) {
	    std::cerr << "\n\nERROR in PlotBuilder::run(): dataset '" << *itd << "' does not exist" << std::endl;
	    exit(-1);
	  }
	}
	for(std::vector<TString>::const_iterator itd = dataLabels2.begin();
	    itd != dataLabels2.end(); ++itd) {
	  if( !DataSet::exists(*itd) ) {
	    std::cerr << "\n\nERROR in PlotBuilder::run(): dataset '" << *itd << "' does not exist" << std::endl;
	    exit(-1);
	  }
	}
	plotComparisonOfSpectra(variable,dataLabels1,dataLabels2,histogram);
      }
    } else {
      std::cerr << "\n\nERROR in PlotBuilder::run(): wrong syntax" << std::endl;
      std::cerr << "  in line with key '" << key << "'" << std::endl;
      std::cerr << "  in config file '" << cfg_.fileName() << "'" << std::endl;
      exit(-1);
    }
  }
}


void PlotBuilder::parseHistCfg(const TString &cfg, int &nBins, double &xMin, double &xMax) const {
  // Set defaults
  nBins = 100;
  xMin = 0.;
  xMax = 5000.;

  // Parse to overwrite defaults
  std::vector<TString> cfgs;
  if( Config::split(cfg,",",cfgs) ) {
    for(unsigned int i = 0; i < cfgs.size(); ++i) {
      if( i == 0 ) nBins = cfgs.at(i).Atoi();
      else if( i == 1 ) xMin = cfgs.at(i).Atof();
      else if( i == 2 ) xMax = cfgs.at(i).Atof();
    }
  }
}


void PlotBuilder::plotSpectrum(const TString &var, const TString &dataSetLabel, const TString &histCfg) const {
  
  int nBins = 100;
  double xMin = 0.;
  double xMax = 5000.;
  parseHistCfg(histCfg,nBins,xMin,xMax);
  TH1* h = 0;
  DataSet::Type type = createHistogram(dataSetLabel,var,nBins,xMin,xMax,h);

  TCanvas *can = new TCanvas("can",plotName(var,dataSetLabel),canSize_,canSize_);
  //can->SetWindowSize(canSize_+(canSize_-can->GetWw()),canSize_+(canSize_-can->GetWh()));
  if( type == DataSet::Data ) {
    h->Draw("PE1");
  } else {
    h->SetLineColor(kBlack);
    h->SetLineStyle(1);
    h->SetLineWidth(1);
    h->Draw("HIST");
  }
  TPaveText* title = header(dataSetLabel);
  title->Draw("same");
  gPad->RedrawAxis();
  can->SaveAs(plotName(var,dataSetLabel)+".eps","eps");

  delete title;
  delete h;
  delete can;
}


void PlotBuilder::plotComparisonOfSpectra(const TString &var, const std::vector<TString> &dataSetLabels1, const std::vector<TString> &dataSetLabels2, const TString &histCfg) const {
  int nBins = 100;
  double xMin = 0.;
  double xMax = 5000.;
  parseHistCfg(histCfg,nBins,xMin,xMax);

  std::vector<TH1*> hists1;
  std::vector<TString> legEntries1;
  DataSet::Type type1 = createStack(dataSetLabels1,var,nBins,xMin,xMax,hists1,legEntries1);
  std::vector<TH1*> hists2;
  std::vector<TString> legEntries2;
  DataSet::Type type2 = createStack(dataSetLabels2,var,nBins,xMin,xMax,hists2,legEntries2);

  TCanvas* can = new TCanvas("can",plotName(var,dataSetLabels1,dataSetLabels2),canSize_,canSize_);

  TLegend* leg = legend(hists1.size()+hists2.size());
  if( type1 == DataSet::Data && type2 == DataSet::MC ) {
    // Draw histograms
    hists2.front()->Draw();
    for(std::vector<TH1*>::iterator it = hists2.begin();
	it != hists2.end(); ++it) {
      (*it)->Draw("HISTsame");
    }
    for(std::vector<TH1*>::iterator it = hists1.begin();
	it != hists1.end(); ++it) {
      (*it)->Draw("PE1same");
    }
    // Add legend entries (first data, than MC)
    std::vector<TString>::const_iterator itL = legEntries1.begin();
    for(std::vector<TH1*>::iterator itH = hists1.begin();
	itH != hists1.end(); ++itH,++itL) {
      leg->AddEntry(*itH,*itL,"P");
    }
    itL = legEntries2.begin();
    for(std::vector<TH1*>::iterator itH = hists2.begin();
	itH != hists2.end(); ++itH,++itL) {
      leg->AddEntry(*itH,*itL,"F");
    }
  } else if( type2 == DataSet::Data && type1 == DataSet::MC ) {
    hists1.front()->Draw();
    for(std::vector<TH1*>::iterator it = hists1.begin();
	it != hists1.end(); ++it) {
      (*it)->Draw("HISTsame");
    }
    for(std::vector<TH1*>::iterator it = hists2.begin();
	it != hists2.end(); ++it) {
      (*it)->Draw("PE1same");
    }
  } else {
    hists1.front()->Draw();
    for(std::vector<TH1*>::iterator it = hists1.begin();
	it != hists1.end(); ++it) {
      (*it)->Draw("PE1same");
    }
    for(std::vector<TH1*>::iterator it = hists2.begin();
	it != hists2.end(); ++it) {
      (*it)->Draw("PE1same");
    }
  }
  TPaveText* title = header();
  title->Draw("same");
  leg->Draw("same");
  gPad->RedrawAxis();
  can->SaveAs(plotName(var,dataSetLabels1,dataSetLabels2)+".eps","eps");

  for(std::vector<TH1*>::iterator it = hists1.begin();
      it != hists1.end(); ++it) {
    delete *it;
  }
  for(std::vector<TH1*>::iterator it = hists2.begin();
      it != hists2.end(); ++it) {
    delete *it;
  }
  delete leg;
  delete title;
  delete can;
}


DataSet::Type PlotBuilder::createHistogram(const TString &dataSetLabel, const TString &var, int nBins, double min, double max, TH1* &hSum) const {
  ++PlotBuilder::count_;
  
  DataSet* set = dataSet(dataSetLabel);
  TString name = "plot";
  name += count_;
  hSum = new TH1D(name,"",nBins,min,max);
  setXTitle(hSum,var);
  setYTitle(hSum,var);
  setStyle(hSum,dataSetLabel,set->type());
  for(EventIt it = set->begin(); it != set->end(); ++it) {
    hSum->Fill((*it)->get(var),(*it)->weight());
  }

  return set->type();
}


DataSet::Type PlotBuilder::createStack(const std::vector<TString> &dataSetLabels, const TString &var, int nBins, double xMin, double xMax, std::vector<TH1*> &hists, std::vector<TString> &legEntries) const {
  DataSet::Type type;
  for(std::vector<TString>::const_reverse_iterator it = dataSetLabels.rbegin();
      it != dataSetLabels.rend(); ++it) {
    TH1* h = 0;
    type = createHistogram(*it,var,nBins,xMin,xMax,h);
    setStyle(h,*it,type);
    legEntries.push_back(" "+(*it));
    // Add histogram to all previous histograms
    for(std::vector<TH1*>::iterator itH = hists.begin();
	itH != hists.end(); ++itH) {
      (*itH)->Add(h);
    }
    // Add this histogram as new entry
    hists.push_back(h);
  }

  return type;
}


void PlotBuilder::setXTitle(TH1* h, const TString &var) const {
  TString xTitle = Variable::label(var);
  if( Variable::unit(var) != "" ) {
    xTitle += " ("+Variable::unit(var)+")";
  }
  h->GetXaxis()->SetTitle(xTitle);
}


void PlotBuilder::setYTitle(TH1* h, const TString &var) const {
  TString yTitle = Variable::label("Events");
  if( h->GetBinWidth(1) != 1. || Variable::unit(var) != "" ) {
    yTitle += " / ";
    if( h->GetBinWidth(1) != 1. ) {
      yTitle += h->GetBinWidth(1);
    }
    if( Variable::unit(var) != "" ) {
      yTitle += " "+Variable::unit(var);
    }
  }
  h->GetYaxis()->SetTitle(yTitle);
}


void PlotBuilder::setStyle(TH1* h, const TString &dataSetLabel, DataSet::Type type) const {
  if( markers_.find(dataSetLabel) != markers_.end() ) {
    h->SetMarkerStyle(markers_.find(dataSetLabel)->second);
  }
  if( markers_.find(dataSetLabel) != colors_.end() ) {
    int color = colors_.find(dataSetLabel)->second;
    if( type == DataSet::Data ) {
      h->SetMarkerColor(color);
      h->SetLineColor(color);
    } else if( type == DataSet::MC || type == DataSet::Bkg ) {
      h->SetFillColor(color);
      h->SetLineColor(color);
    }
  }
}


TPaveText* PlotBuilder::header(const TString &dataSetLabel) const {
  double x0 = gStyle->GetPadLeftMargin();
  double x1 = 1.-gStyle->GetPadRightMargin();
  double y0 = 1.-gStyle->GetPadTopMargin();
  double y1 = 1.;
  TPaveText *txt = new TPaveText(x0,y0,x1,y1,"NDC");
  txt->SetBorderSize(0);
  txt->SetFillColor(0);
  txt->SetTextFont(42);
  txt->SetTextAlign(02);
  txt->SetTextSize(0.05);
  txt->AddText(lumiLabel()+(dataSetLabel != "" ? ",  "+dataSetLabel : "")+",  "+selectionLabel_);
  
  return txt;
}


TLegend* PlotBuilder::legend(unsigned int nEntries) const {
  double lineHeight = 0.06;
  double margin = 0.02;
  double x0 = 0.7;
  double x1 = 1.-gStyle->GetPadRightMargin()-margin;
  double y1 = 1.-gStyle->GetPadTopMargin()-margin;
  double y0 = y1-nEntries*lineHeight;

  TLegend* leg = new TLegend(x0,y0,x1,y1);
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->SetFillStyle(0);
  leg->SetTextFont(42);
  leg->SetTextSize(0.04);

  return leg;
}


TString PlotBuilder::lumiLabel() const {
  return GlobalParameters::lumi()+" fb^{-1}";
}


TString PlotBuilder::cleanName(const TString &name) const {
  TString cleanedName = name;
  cleanedName.ReplaceAll(" ","_");
  cleanedName.ReplaceAll("#","");
  cleanedName.ReplaceAll("{","");
  cleanedName.ReplaceAll("}","");

  return cleanedName;
}


TString PlotBuilder::plotName(const TString &var, const TString &dataSetLabel) const {
  return cleanName(GlobalParameters::analysisId()+"_"+var+"_"+dataSetLabel+"_"+selectionLabel_);
}


TString PlotBuilder::plotName(const TString &var, const std::vector<TString> &dataSetLabels1, const std::vector<TString> &dataSetLabels2) const {
  TString label1 = dataSetLabels1.front();
  for(std::vector<TString>::const_iterator it = dataSetLabels1.begin()+1;
      it != dataSetLabels1.end(); ++it) {
    label1 += "+"+*it;
  }
  TString label2 = dataSetLabels2.front();
  for(std::vector<TString>::const_iterator it = dataSetLabels2.begin()+1;
      it != dataSetLabels2.end(); ++it) {
    label2 += "+"+*it;
  }

  return cleanName(GlobalParameters::analysisId()+"_"+var+"_"+label1+"_vs_"+label2+"_"+selectionLabel_);
}


DataSet* PlotBuilder::dataSet(const TString &label) const {
  DataSet* dset = 0;
  for(std::vector<DataSet*>::const_iterator it = dataSets_.begin();
      it != dataSets_.end(); ++it) {
    dset = *it;
    if( dset->label() == label ) break;
  }

  return dset;
}
