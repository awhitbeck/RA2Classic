#include <cmath>
#include <cstdlib>
#include <iostream>

#include "TH1D.h"
#include "TPad.h"
#include "TStyle.h"

#include "GlobalParameters.h"
#include "PlotBuilder.h"
#include "Variable.h"

#include "../AdditionalInputFiles/RA2PlottingStyle.h"


unsigned int PlotBuilder::count_ = 0;


PlotBuilder::PlotBuilder(const std::vector<DataSet*> &dataSets, const Config &cfg, const TString &outDir)
  : cfg_(cfg), canSize_(500), dataSets_(dataSets), outDir_(outDir) {
  setStyle("plot style");
  run("plot");
}


PlotBuilder::~PlotBuilder() {
  
}


void PlotBuilder::setStyle(const TString &key) {
  RA2PlottingStyle::init();
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
      if( it->hasName("plot label") ) {
	dataSetLabelsInPlot_[dataSetLabel] = it->value("plot label");
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
      } else if( it->hasName("datasets") ) { // Comparison of several datasets (normalised histograms)
	std::vector<TString> dataLabels;
	Config::split(it->value("datasets"),",",dataLabels);
	for(std::vector<TString>::const_iterator itd = dataLabels.begin();
	    itd != dataLabels.end(); ++itd) {
	  if( !DataSet::exists(*itd) ) {
	    std::cerr << "\n\nERROR in PlotBuilder::run(): dataset '" << *itd << "' does not exist" << std::endl;
	    exit(-1);
	  }
	}
	plotSpectra(variable,dataLabels,histogram);
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


void PlotBuilder::parseHistCfg(const TString &cfg, int &nBins, double &xMin, double &xMax, bool &logy) const {
  // Set defaults
  nBins = 100;
  xMin = 0.;
  xMax = 5000.;
  logy = false;

  // Parse to overwrite defaults
  std::vector<TString> cfgs;
  if( Config::split(cfg,",",cfgs) ) {
    for(unsigned int i = 0; i < cfgs.size(); ++i) {
      if( i == 0 ) nBins = cfgs.at(i).Atoi();
      else if( i == 1 ) xMin = cfgs.at(i).Atof();
      else if( i == 2 ) xMax = cfgs.at(i).Atof();
      else if( i == 3 && cfgs.at(i) == "log" ) logy = true;
    }
  }
}


void PlotBuilder::plotSpectrum(const TString &var, const TString &dataSetLabel, const TString &histCfg) const {
  
  int nBins = 100;
  double xMin = 0.;
  double xMax = 5000.;
  bool logy = false;
  parseHistCfg(histCfg,nBins,xMin,xMax,logy);
  TH1* h = 0;
  TGraphAsymmErrors* u = 0;
  DataSet::Type type = createDistribution(dataSetLabel,var,h,u,nBins,xMin,xMax);

  TCanvas *can = new TCanvas("can","",canSize_,canSize_);
  //can->SetWindowSize(canSize_+(canSize_-can->GetWw()),canSize_+(canSize_-can->GetWh()));
  if( type == DataSet::Data ) {
    h->Draw("PE1");
    if( u ) {
      u->Draw("E2same");
      h->Draw("PE1same");
    }
  } else {
    h->SetLineColor(kBlack);
    h->SetLineStyle(1);
    h->SetLineWidth(1);
    h->Draw("HIST");
    if( u ) {
      u->Draw("E2same");
    }
  }
  TString dataSetLabelInHeader = dataSetLabelInPlot(dataSetLabel)+" (";
  dataSetLabelInHeader += static_cast<int>(h->Integral(1,h->GetNbinsX()));
  dataSetLabelInHeader += ")";
  TPaveText* title = header(true,dataSetLabelInHeader);
  title->Draw("same");
  if( logy ) can->SetLogy();
  gPad->RedrawAxis();
  storeCanvas(can,plotName(var,dataSetLabel));

  delete title;
  delete h;
  if( u ) delete u;
  delete can;
}


void PlotBuilder::plotSpectra(const TString &var, const std::vector<TString> &dataSetLabels, const TString &histCfg) const {
  int nBins = 100;
  double xMin = 0.;
  double xMax = 5000.;
  bool logy = false;
  parseHistCfg(histCfg,nBins,xMin,xMax,logy);

  std::vector<TH1*> hists;
  std::vector<DataSet::Type> types;
  TLegend* leg = legend(dataSetLabels.size());
  for(std::vector<TString>::const_iterator it = dataSetLabels.begin();
      it != dataSetLabels.end(); ++it) {
    TH1* h = 0;
    TGraphAsymmErrors* u = 0;
    types.push_back(createDistribution(*it,var,h,u,nBins,xMin,xMax));
    if( u ) delete u;
    if( h->Integral() ) h->Scale(1./h->Integral("width"));
    h->GetYaxis()->SetTitle("Probability Density");
    if( types.back() != DataSet::Data ) {
      h->SetLineColor(h->GetFillColor());
      h->SetLineWidth(3);
      h->SetFillStyle(0);
      leg->AddEntry(h," "+dataSetLabelInPlot(*it),"L");
    } else {
      leg->AddEntry(h," "+dataSetLabelInPlot(*it),"P");
    }
    setYRange(h,logy?3E-6:-1.);
    hists.push_back(h);
  }

  TCanvas *can = new TCanvas("can","",canSize_,canSize_);
  if( types.back() == DataSet::Data ) {
    hists.back()->Draw("PE1");
  } else {
    hists.back()->Draw("HIST");
  }
  for(int i = hists.size()-2; i >= 0; --i) {
    if( types.at(i) == DataSet::Data ) {
      hists.at(i)->Draw("PE1same");
    } else {
      hists.at(i)->Draw("HISTsame");
    }
  }
  TPaveText* title = header(false);
  title->Draw("same");
  leg->Draw("same");
  gPad->RedrawAxis();
  if( logy ) can->SetLogy();
  storeCanvas(can,plotName(var));

  delete title;
  delete leg;
  for(std::vector<TH1*>::iterator it = hists.begin();
      it != hists.end(); ++it) {
    delete *it;
  }
  delete can;
}


void PlotBuilder::plotComparisonOfSpectra(const TString &var, const std::vector<TString> &dataSetLabels1, const std::vector<TString> &dataSetLabels2, const TString &histCfg) const {
  int nBins = 100;
  double xMin = 0.;
  double xMax = 5000.;
  bool logy = false;
  parseHistCfg(histCfg,nBins,xMin,xMax,logy);

  std::vector<TH1*> hists1;
  std::vector<TString> legEntries1;
  TGraphAsymmErrors* unc1 = 0;
  DataSet::Type type1 = createStack(dataSetLabels1,var,hists1,legEntries1,unc1,nBins,xMin,xMax);
  std::vector<TH1*> hists2;
  std::vector<TString> legEntries2;
  TGraphAsymmErrors* unc2 = 0;
  DataSet::Type type2 = createStack(dataSetLabels2,var,hists2,legEntries2,unc2,nBins,xMin,xMax);

  TCanvas* can = new TCanvas("can","",canSize_,canSize_);
  can->SetBottomMargin(0.2 + 0.8*can->GetBottomMargin()-0.2*can->GetTopMargin());
  can->cd();
  TPad *ratioPad = new TPad("bpad","",0,0,1,1);
  ratioPad->SetTopMargin(0.8 - 0.8*ratioPad->GetBottomMargin()+0.2*ratioPad->GetTopMargin());
  ratioPad->SetFillStyle(0);
  ratioPad->SetFrameFillColor(10);
  ratioPad->SetFrameBorderMode(0);

  // Ratio plot
  TH1 *hRatio = 0;
  TH1 *hRatioFrame = static_cast<TH1*>(hists1.front()->Clone("RatioFrame"));
  for(int xBin = 1; xBin <= hRatioFrame->GetNbinsX(); ++xBin) {
    hRatioFrame->SetBinContent(xBin,1.);
  }
  hRatioFrame->GetXaxis()->SetTitle(hists1.front()->GetXaxis()->GetTitle());
  hRatioFrame->GetYaxis()->SetRangeUser(0.55,1.95);
  hRatioFrame->SetLineStyle(2);
  hRatioFrame->SetLineColor(kBlack);
  hRatioFrame->SetLineWidth(2);
  hRatioFrame->SetFillColor(0);
  hRatioFrame->GetYaxis()->SetNdivisions(205);
  hRatioFrame->GetYaxis()->SetTickLength(gStyle->GetTickLength("Y")/0.2);
  hRatioFrame->GetXaxis()->SetLabelSize(gStyle->GetLabelSize("X"));
  hRatioFrame->GetYaxis()->CenterTitle();
  hRatioFrame->GetYaxis()->SetTitleOffset(0.9*hRatioFrame->GetYaxis()->GetTitleOffset());
  for(std::vector<TH1*>::iterator it = hists1.begin();
      it != hists1.end(); ++it) {
    (*it)->GetXaxis()->SetLabelSize(0);
    (*it)->GetXaxis()->SetTitle("");
    (*it)->GetYaxis()->SetTickLength(gStyle->GetTickLength("Y")/0.8);
  }
  for(std::vector<TH1*>::iterator it = hists2.begin();
      it != hists2.end(); ++it) {
    (*it)->GetXaxis()->SetLabelSize(0);
    (*it)->GetXaxis()->SetTitle("");
    (*it)->GetYaxis()->SetTickLength(gStyle->GetTickLength("Y")/0.8);
  }

  TLegend* leg = legend(hists1.size()+hists2.size());
  TPaveText* title = 0;
  TString ratioYTitle = "";

  // Decide which hist is plotted data-like (dots, on top)
  // and which hist is plotted mc-like (filled, below)
  std::vector<TH1*>* histsData = 0;
  std::vector<TH1*>* histsMC = 0;
  std::vector<TString>* legEntriesData = 0;
  std::vector<TString>* legEntriesMC = 0;
  TGraphAsymmErrors* uncData = 0;
  TGraphAsymmErrors* uncMC = 0;
  if( (type1 == DataSet::Data && type2 == DataSet::MC) ||
      (type1 == DataSet::Data && type2 == DataSet::Prediction) ||
      (type1 == DataSet::Prediction && type2 == DataSet::MC)      ) {
    histsData      = &hists1; 
    histsMC        = &hists2; 
    legEntriesData = &legEntries1;
    legEntriesMC   = &legEntries2;
    uncData        = unc1;
    uncMC          = unc2;
    if( type1 == DataSet::Prediction && type2 == DataSet::MC ) {
      for(std::vector<TH1*>::iterator it = hists1.begin();
	  it != hists1.end(); ++it) {
	setMarkerStyle(*it,dataSetLabels1.front());
      }
      title        = header(false);
    } else {
      title        = header(true);
    }
    ratioYTitle    = "#frac{"+dataSetTypeLabel(type1)+"}{"+dataSetTypeLabel(type2)+"}";
  } else if( (type2 == DataSet::Data && type1 == DataSet::MC) ||
	     (type2 == DataSet::Data && type1 == DataSet::Prediction) ||
	     (type2 == DataSet::Prediction && type1 == DataSet::MC)      ) {
    histsData      = &hists2; 
    histsMC        = &hists1; 
    legEntriesData = &legEntries2;
    legEntriesMC   = &legEntries1;
    uncData        = unc2;
    uncMC          = unc1;
    if( type2 == DataSet::Prediction && type1 == DataSet::MC ) {
      for(std::vector<TH1*>::iterator it = hists2.begin();
	  it != hists2.end(); ++it) {
	setMarkerStyle(*it,dataSetLabels2.front());
      }
      title        = header(false);
    } else {
      title        = header(true);
    }
    ratioYTitle    = "#frac{"+dataSetTypeLabel(type2)+"}{"+dataSetTypeLabel(type1)+"}";
  } else if( type1 == DataSet::MC && type2 == DataSet::MC ) {
    for(std::vector<TH1*>::iterator it = hists1.begin();
	it != hists1.end(); ++it) {
      setMarkerStyle(*it,dataSetLabels1.front());
    }
    histsData      = &hists1; 
    histsMC        = &hists2; 
    uncData        = unc1;
    uncMC          = unc2;
    legEntriesData = &legEntries1;
    legEntriesMC   = &legEntries2;
    title          = header(false);
    ratioYTitle    = "#frac{"+dataSetTypeLabel(type1)+"}{"+dataSetTypeLabel(type2)+"}";
  } else {
    histsData      = &hists1; 
    histsMC        = &hists2; 
    uncData        = unc1;
    uncMC          = unc2;
    legEntriesData = &legEntries1;
    legEntriesMC   = &legEntries2;
    title          = header(false);
    ratioYTitle    = "#frac{"+dataSetTypeLabel(type1)+"}{"+dataSetTypeLabel(type2)+"}";
  }

  // Draw
  can->cd();
  //setYRange(histsMC->front(),logy?3E-1:-1.);
  histsMC->front()->GetYaxis()->SetRangeUser(3E-1,3E4);
  histsMC->front()->Draw();
  for(std::vector<TH1*>::iterator it = histsMC->begin();
      it != histsMC->end(); ++it) {
    (*it)->Draw("HISTsame");
  }
  // Plot only MC uncertainty band
  if( uncMC ) uncMC->Draw("E2same");
  for(std::vector<TH1*>::iterator it = histsData->begin();
      it != histsData->end(); ++it) {
    (*it)->Draw("PE1same");
  }
  // Add legend entries (first data, than MC)
  std::vector<TString>::const_iterator itL = legEntriesData->begin();
  for(std::vector<TH1*>::iterator itH = histsData->begin();
      itH != histsData->end(); ++itH,++itL) {
      leg->AddEntry(*itH,*itL,"P");
    }
  itL = legEntriesMC->begin();
  for(std::vector<TH1*>::iterator itH = histsMC->begin();
      itH != histsMC->end(); ++itH,++itL) {
    leg->AddEntry(*itH,*itL,"F");
  }
  gPad->RedrawAxis();
  // Add ratio plot (data/MC)
  ratioPad->Draw();
  ratioPad->cd();
  hRatio = static_cast<TH1*>(histsData->front()->Clone("Ratio"));
  hRatio->Divide(histsMC->front());
  hRatioFrame->GetYaxis()->SetTitle(ratioYTitle);
  hRatioFrame->Draw("HIST");
  TGraphAsymmErrors* uncRatio = 0;
  if( uncMC ) {
    uncRatio = static_cast<TGraphAsymmErrors*>(uncMC->Clone());
    for(unsigned int i = 0; i < uncRatio->GetN(); ++i) {
      double denom  = uncRatio->GetY()[i];
      if( denom > 0. ) {
	uncRatio->GetY()[i] = 1.;
	uncRatio->GetEYlow()[i] = uncRatio->GetEYlow()[i]/denom;
	uncRatio->GetEYhigh()[i] = uncRatio->GetEYhigh()[i]/denom;
      }
    }
    uncRatio->Draw("E2same");
  }
  hRatio->Draw("PE1same");
  title->Draw("same");
  leg->Draw("same");
  gPad->RedrawAxis();
  if( logy ) can->SetLogy();
  storeCanvas(can,plotName(var,dataSetLabels1,dataSetLabels2));

  for(std::vector<TH1*>::iterator it = hists1.begin();
      it != hists1.end(); ++it) {
    delete *it;
  }
  for(std::vector<TH1*>::iterator it = hists2.begin();
      it != hists2.end(); ++it) {
    delete *it;
  }
  if( unc1 ) delete unc1;
  if( unc2 ) delete unc2;
  if( uncRatio ) delete uncRatio;
  delete leg;
  delete title;
  delete can;
  delete hRatio;
  delete hRatioFrame;
}


// Fill distribution of variable 'var' for dataSet with label 'dataSetLabel'
// and an uncertainty band 'uncert'. 
// ----------------------------------------------------------------------------
DataSet::Type PlotBuilder::createDistribution(const TString &dataSetLabel, const TString &var, TH1* &h, TGraphAsymmErrors* &uncert, int nBins, double min, double max) const {
  ++PlotBuilder::count_;
  
  // Create histogram  
  TString name = "plot";
  name += count_;
  h = new TH1D(name,"",nBins,min,max);
  h->Sumw2();
  if( max > 1000. ) {
    h->GetXaxis()->SetNdivisions(505);
  }
  setXTitle(h,var);
  setYTitle(h,var);
  setGenericStyle(h,dataSetLabel);

  // Create temporary histograms to store uncertainties
  TH1* hDn = static_cast<TH1*>(h->Clone(name+"Dn"));
  TH1* hUp = static_cast<TH1*>(h->Clone(name+"Up"));

  // Fill distributions
  DataSet* set = dataSet(dataSetLabel);
  for(EventIt it = set->begin(); it != set->end(); ++it) {
    double v = (*it)->get(var);
    h->Fill(v,(*it)->weight());
    if( (*it)->hasUnc() ) {
      hDn->Fill(v,(*it)->weightUncDn());
      hUp->Fill(v,(*it)->weightUncUp());
    }
  }

  // Create uncertainty band
  if( hDn->GetEntries() && hDn->GetEntries() ) {
    std::vector<double> x(h->GetNbinsX());
    std::vector<double> xe(h->GetNbinsX());
    std::vector<double> y(h->GetNbinsX());
    std::vector<double> yed(h->GetNbinsX());
    std::vector<double> yeu(h->GetNbinsX());
    for(unsigned int i = 0; i < x.size(); ++i) {
      int bin = i+1;
      x.at(i) = h->GetBinCenter(bin);
      xe.at(i) = h->GetBinWidth(bin)/2.;
      y.at(i) = h->GetBinContent(bin);
      yed.at(i) = std::abs(h->GetBinContent(bin)-hDn->GetBinContent(bin));
      yeu.at(i) = std::abs(h->GetBinContent(bin)-hUp->GetBinContent(bin));
    }
    uncert = new TGraphAsymmErrors(x.size(),&(x.front()),&(y.front()),&(xe.front()),&(xe.front()),&(yed.front()),&(yeu.front()));
    uncert->SetMarkerStyle(1);
    uncert->SetMarkerColor(kBlue+2);
    uncert->SetFillColor(uncert->GetMarkerColor());
    uncert->SetLineColor(uncert->GetMarkerColor());
    uncert->SetFillStyle(3004);
  }

  // Delete temporary hists
  delete hDn;
  delete hUp;

  return set->type();
}


DataSet::Type PlotBuilder::createStack(const std::vector<TString> &dataSetLabels, const TString &var, std::vector<TH1*> &hists, std::vector<TString> &legEntries, TGraphAsymmErrors* &uncert, int nBins, double xMin, double xMax) const {
  DataSet::Type type;
  uncert = 0;
  for(std::vector<TString>::const_reverse_iterator it = dataSetLabels.rbegin();
      it != dataSetLabels.rend(); ++it) {
    TH1* h = 0;
    TGraphAsymmErrors* u = 0;
    type = createDistribution(*it,var,h,u,nBins,xMin,xMax);
    if( u ) {
      if( uncert ) {		// Add uncertainties in quadrature
	for(unsigned int i = 0; i < uncert->GetN(); ++i) {
	  double y1  = uncert->GetY()[i];
	  double ed1 = uncert->GetEYlow()[i];
	  double eu1 = uncert->GetEYhigh()[i];
	  double y2  = u->GetY()[i];
	  double ed2 = u->GetEYlow()[i];
	  double eu2 = u->GetEYhigh()[i];
	  uncert->GetY()[i] = y1+y2;
 	  uncert->SetPointEYlow(i,sqrt(ed1*ed1+ed2*ed2));
 	  uncert->SetPointEYhigh(i,sqrt(eu1*eu1+eu2*eu2));
	}
      } else {
	uncert = u;
      }
    }
    setGenericStyle(h,*it);
    TString entry = " "+dataSetLabelInPlot(*it)+" (";
    entry += static_cast<int>(h->Integral(1,h->GetNbinsX()));
    entry += +")";
    legEntries.push_back(entry);
    
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
      TString bw = "";
      bw += h->GetBinWidth(1);
      if( bw.Contains(".") && bw.Length() > 5 ) bw = bw(0,5);
      yTitle += bw;
    }
    if( Variable::unit(var) != "" ) {
      yTitle += " "+Variable::unit(var);
    }
  }
  h->GetYaxis()->SetTitle(yTitle);
}


int PlotBuilder::color(const TString &dataSetLabel) const {
  // Default color
  int color = kGray;
  // Specified colors
  if( colors_.find(dataSetLabel) != colors_.end() ) {
    color = colors_.find(dataSetLabel)->second;
  } else {
    // More specific default colors
    DataSet::Type type = dataSet(dataSetLabel)->type();
    if( type == DataSet::Data ) {
      color = kBlack;
    }
  }

  return color;
}


int PlotBuilder::markerStyle(const TString &dataSetLabel) const {
  // Default style
  int style = 21;
  // Specified styles
  if( markers_.find(dataSetLabel) != markers_.end() ) {
    style = markers_.find(dataSetLabel)->second;
  } else {
    // More specific default styles
    DataSet::Type type = dataSet(dataSetLabel)->type();
    if( type == DataSet::Data ) {
      style = 21;
    }
  }

  return style;
}


void PlotBuilder::setMarkerStyle(TH1* h, const TString &dataSetLabel) const {
  h->SetMarkerStyle(markerStyle(dataSetLabel));
  h->SetMarkerColor(color(dataSetLabel));
  h->SetLineColor(h->GetMarkerColor());
}


void PlotBuilder::setGenericStyle(TH1* h, const TString &dataSetLabel) const {
  DataSet::Type type = dataSet(dataSetLabel)->type();
  if( type == DataSet::Data ) {
    setMarkerStyle(h,dataSetLabel);
  } else if( type == DataSet::MC || type == DataSet::Prediction ) {
    int c = color(dataSetLabel);
    h->SetMarkerStyle(0);
    h->SetMarkerColor(c);
    h->SetLineColor(c);
    h->SetFillColor(c);
  }
}


TPaveText* PlotBuilder::header(bool showLumi, const TString &add) const {
  double x0 = gStyle->GetPadLeftMargin();
  double x1 = 1.-gStyle->GetPadRightMargin();
  double y0 = 1.-gStyle->GetPadTopMargin();
  double y1 = 1.;
  TPaveText *txt = new TPaveText(x0,y0,x1,y1,"NDC");
  txt->SetBorderSize(0);
  txt->SetFillColor(0);
  txt->SetTextFont(42);
  txt->SetTextAlign(12);
  txt->SetTextSize(0.05);
  txt->SetMargin(0.);
  txt->AddText("8 TeV"+(showLumi ? ",  "+lumiLabel() : "" )+",  "+dataSets_.front()->selection()+(add != "" ? ",  "+add : ""));
  
  return txt;
}


TLegend* PlotBuilder::legend(unsigned int nEntries) const {
  double lineHeight = 0.06;
  double margin = 0.02;
  double x0 = 0.45;
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


DataSet* PlotBuilder::dataSet(const TString &label) const {
  DataSet* dset = 0;
  for(std::vector<DataSet*>::const_iterator it = dataSets_.begin();
      it != dataSets_.end(); ++it) {
    dset = *it;
    if( dset->label() == label ) break;
  }

  return dset;
}


void PlotBuilder::storeCanvas(TCanvas* can, const TString &name) const {
  can->SetName(name);
  can->SetTitle(name);
  can->SaveAs(outDir_+"/"+name+".eps","eps");
}


TString PlotBuilder::plotName(const TString &var) const {
  return GlobalParameters::cleanName(GlobalParameters::analysisId()+"_"+var+"_"+dataSets_.front()->selection());
}


TString PlotBuilder::plotName(const TString &var, const TString &dataSetLabel) const {
  return GlobalParameters::cleanName(GlobalParameters::analysisId()+"_"+var+"_"+dataSetLabel+"_"+dataSets_.front()->selection());
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

  return GlobalParameters::cleanName(GlobalParameters::analysisId()+"_"+var+"_"+label1+"_vs_"+label2+"_"+dataSets_.front()->selection());
}


TString PlotBuilder::dataSetLabelInPlot(const TString &dataSetLabel) const {
  TString dataSetLabelInPlot = dataSetLabel;
  std::map<TString,TString>::const_iterator it = dataSetLabelsInPlot_.find(dataSetLabel);
  if( it != dataSetLabelsInPlot_.end() ) dataSetLabelInPlot = it->second;

  return dataSetLabelInPlot;
}


TString PlotBuilder::dataSetTypeLabel(DataSet::Type type) const {
  TString label = "";
  if( type == DataSet::Data )            label = "Data";
  else if( type == DataSet::MC )         label = "Sim.";
  else if( type == DataSet::Prediction ) label = "Pred.";
  else if( type == DataSet::Signal )     label = "Signal";

  return label;
}


void PlotBuilder::setYRange(TH1* &h, double logMin) const {
  bool log = logMin > 0.;
  double max = h->GetBinContent(h->GetMaximumBin());
  double min = 0.;
  if( log ) min = logMin;

  double relHistHeight = 1. - (gStyle->GetPadTopMargin() + gStyle->GetPadBottomMargin() );
  if( log ) {
    max = min * std::pow(max/min,1./relHistHeight);
  } else {
    relHistHeight -= 0.3;
    max = (max-min)/relHistHeight + min;
  }
  h->GetYaxis()->SetRangeUser(min,max);
}
