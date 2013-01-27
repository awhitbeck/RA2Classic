#include <cmath>
#include <cstdlib>
#include <iostream>

#include "TH1D.h"
#include "TPad.h"
#include "TStyle.h"

#include "GlobalParameters.h"
#include "PlotBuilder.h"
#include "Selection.h"
#include "Variable.h"

#include "../AdditionalInputFiles/RA2PlottingStyle.h"


unsigned int PlotBuilder::count_ = 0;


PlotBuilder::PlotBuilder(const Config &cfg, Output &out)
  : cfg_(cfg), canSize_(500), out_(out) {
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
  std::cout << "  - Creating control plots" << std::endl;

  std::vector<Config::Attributes> attrList = cfg_.listOfAttributes(key);
  for(std::vector<Config::Attributes>::const_iterator it = attrList.begin();
      it != attrList.end(); ++it) {
    if( it->hasName("variable") && it->hasName("histogram") ) {
      // General features
      TString variable = it->value("variable");
      if( !Variable::exists(variable) ) {
	std::cerr << "\n\nERROR in PlotBuilder::run(): variable '" << variable << "' does not exist" << std::endl;
	exit(-1);
      }
      HistParams histParams(it->value("histogram"));
      
      // +++ Plot type: Sinlge spectrum for all selections
      if( it->hasName("dataset") ) {
	TString dataSetLabel = it->value("dataset");
 	if( !DataSet::labelExists(dataSetLabel) ) {
 	  std::cerr << "\n\nERROR in PlotBuilder::run(): dataset '" << dataSetLabel << "' does not exist" << std::endl;
 	  exit(-1);
 	}
	for(SelectionIt its = Selection::begin();
	    its != Selection::end(); ++its) {
	  plotSpectrum(variable,DataSet::find(dataSetLabel,*its),histParams);
	}
      }
      // +++ Plot type: Comparison of several datasets (normalised histograms) for all selections
      else if( it->hasName("datasets") ) {
	std::vector<TString> dataSetLabels;
	Config::split(it->value("datasets"),",",dataSetLabels);
	for(std::vector<TString>::const_iterator itd = dataSetLabels.begin();
	    itd != dataSetLabels.end(); ++itd) {
 	  if( !DataSet::labelExists(*itd) ) {
 	    std::cerr << "\n\nERROR in PlotBuilder::run(): dataset '" << *itd << "' does not exist" << std::endl;
 	    exit(-1);
 	  }
	}
	// For each selection, find the datasets to be compared
	for(SelectionIt its = Selection::begin();
	    its != Selection::end(); ++its) {
	  DataSets dataSets;
	  for(std::vector<TString>::const_iterator itd = dataSetLabels.begin();
	      itd != dataSetLabels.end(); ++itd) {
	    dataSets.push_back(DataSet::find(*itd,*its));
	  }
	  plotSpectra(variable,dataSets,histParams);
	}
      }
      // +++ Plot type: Comparison of two (stacked) datasets for all selections
      else if( it->hasName("dataset1") && it->hasName("dataset2") ) {
	// Read names of (stacked) datasets
	std::vector<TString> dataSetLabels1;
	std::vector<TString> dataSetLabels2;
	Config::split(it->value("dataset1"),"+",dataSetLabels1);
	Config::split(it->value("dataset2"),"+",dataSetLabels2);
	for(std::vector<TString>::const_iterator itd = dataSetLabels1.begin();
	    itd != dataSetLabels1.end(); ++itd) {
 	  if( !DataSet::labelExists(*itd) ) {
 	    std::cerr << "\n\nERROR in PlotBuilder::run(): dataset '" << *itd << "' does not exist" << std::endl;
 	    exit(-1);
 	  }
	}
	for(std::vector<TString>::const_iterator itd = dataSetLabels2.begin();
	    itd != dataSetLabels2.end(); ++itd) {
 	  if( !DataSet::labelExists(*itd) ) {
 	    std::cerr << "\n\nERROR in PlotBuilder::run(): dataset '" << *itd << "' does not exist" << std::endl;
 	    exit(-1);
 	  }
	}
	// For each selection, find the datasets to be compared
	for(SelectionIt its = Selection::begin();
	    its != Selection::end(); ++its) {
	  DataSets dataSets1;
	  for(std::vector<TString>::const_iterator itd = dataSetLabels1.begin();
	      itd != dataSetLabels1.end(); ++itd) {
	    dataSets1.push_back(DataSet::find(*itd,*its));
	  }
	  DataSets dataSets2;
	  for(std::vector<TString>::const_iterator itd = dataSetLabels2.begin();
	      itd != dataSetLabels2.end(); ++itd) {
	    dataSets2.push_back(DataSet::find(*itd,*its));
	  }
	  plotComparisonOfSpectra(variable,dataSets1,dataSets2,histParams);
	}

      }
    } else {
      std::cerr << "\n\nERROR in PlotBuilder::run(): wrong syntax" << std::endl;
      std::cerr << "  in line with key '" << key << "'" << std::endl;
      std::cerr << "  in config file '" << cfg_.fileName() << "'" << std::endl;
      exit(-1);
    }
  }
}


void PlotBuilder::plotSpectrum(const TString &var, const DataSet *dataSet, const HistParams &histParams) const {
  TH1* h = 0;
  TGraphAsymmErrors* u = 0;
  createDistribution(dataSet,var,h,u,histParams);

  // Under-/Overflow warning
  checkForUnderOverFlow(h,var,dataSet);

  TCanvas *can = new TCanvas("can","",canSize_,canSize_);
  //can->SetWindowSize(canSize_+(canSize_-can->GetWw()),canSize_+(canSize_-can->GetWh()));
  if( dataSet->type() == DataSet::Data ) {
    h->Draw("PE");
    if( u ) {
      u->Draw("E2same");
      h->Draw("PEsame");
    }
  } else if( dataSet->type() == DataSet::Prediction ) {
    h->SetLineColor(kBlack);
    h->SetLineStyle(1);
    h->SetLineWidth(1);
    h->Draw("HISTE");
    if( u ) {
      u->Draw("E2same");
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
  TString info = dataSet->selectionUid()+",  "+dataSetLabelInPlot(dataSet)+" (";
  info += static_cast<int>(h->Integral(1,h->GetNbinsX()));
  info += ")";
  TPaveText* title = header(true,info);
  title->Draw("same");
  if( histParams.logy() ) can->SetLogy();
  gPad->RedrawAxis();
  storeCanvas(can,var,dataSet);

  delete title;
  delete h;
  if( u ) delete u;
  delete can;
}


void PlotBuilder::plotSpectra(const TString &var, const DataSets &dataSets, const HistParams &histParams) const {
  std::vector<TH1*> hists;
  TLegend* leg = legend(dataSets.size());
  // Loop over datasets and create distributions
  for(DataSetIt itd = dataSets.begin();
      itd != dataSets.end(); ++itd) {
    TH1* h = 0;
    TGraphAsymmErrors* u = 0;
    createDistribution(*itd,var,h,u,histParams);
    if( u ) delete u;
    if( histParams.norm() && h->Integral() ) {
      h->Scale(1./h->Integral("width"));
      h->GetYaxis()->SetTitle("Probability Density");
    }
    if( (*itd)->type() != DataSet::Data ) {
      h->SetLineColor(h->GetFillColor());
      h->SetLineWidth(3);
      h->SetFillStyle(0);
      leg->AddEntry(h," "+dataSetLabelInPlot(*itd),"L");
    } else {
      leg->AddEntry(h," "+dataSetLabelInPlot(*itd),"P");
    }
    if( histParams.norm() ) setYRange(h,histParams.logy()?3E-6:-1.);
    else setYRange(h,histParams.logy()?3E-1:-1.);
    hists.push_back(h);
  }

  TCanvas *can = new TCanvas("can","",canSize_,canSize_);
  if( dataSets.back()->type() == DataSet::Data ) {
    hists.back()->Draw("PE");
  } else {
    hists.back()->Draw("HIST");
  }
  for(int i = hists.size()-2; i >= 0; --i) {
    if( dataSets.at(i)->type() == DataSet::Data ) {
      hists.at(i)->Draw("PEsame");
    } else {
      hists.at(i)->Draw("HISTsame");
    }
  }
  TPaveText* title = header(false,dataSets.front()->selectionUid());
  title->Draw("same");
  leg->Draw("same");
  gPad->RedrawAxis();
  if( histParams.logy() ) can->SetLogy();
  storeCanvas(can,var,dataSets.front()->selectionUid());
  
  delete title;
  delete leg;
  for(std::vector<TH1*>::iterator it = hists.begin();
      it != hists.end(); ++it) {
    delete *it;
  }
  delete can;
}


void PlotBuilder::plotComparisonOfSpectra(const TString &var, const DataSets &dataSets1, const DataSets &dataSets2, const HistParams &histParams) const {
  std::vector<TH1*> hists1;
  std::vector<TString> legEntries1;
  TGraphAsymmErrors* unc1 = 0;
  createStack(dataSets1,var,hists1,legEntries1,unc1,histParams);
  std::vector<TH1*> hists2;
  std::vector<TString> legEntries2;
  TGraphAsymmErrors* unc2 = 0;
  createStack(dataSets2,var,hists2,legEntries2,unc2,histParams);

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
  DataSet::Type type1 = dataSets1.front()->type();
  DataSet::Type type2 = dataSets2.front()->type();
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
	setMarkerStyle(*it,dataSets1.front());
      }
      title        = header(false,dataSets1.front()->selectionUid());
    } else {
      title        = header(true,dataSets1.front()->selectionUid());
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
	setMarkerStyle(*it,dataSets2.front());
      }
      title        = header(false,dataSets1.front()->selectionUid());
    } else {
      title        = header(true,dataSets1.front()->selectionUid());
    }
    ratioYTitle    = "#frac{"+dataSetTypeLabel(type2)+"}{"+dataSetTypeLabel(type1)+"}";
  } else if( type1 == DataSet::MC && type2 == DataSet::MC ) {
    for(std::vector<TH1*>::iterator it = hists1.begin();
	it != hists1.end(); ++it) {
      setMarkerStyle(*it,dataSets1.front());
    }
    histsData      = &hists1; 
    histsMC        = &hists2; 
    uncData        = unc1;
    uncMC          = unc2;
    legEntriesData = &legEntries1;
    legEntriesMC   = &legEntries2;
    title          = header(false,dataSets1.front()->selectionUid());
    ratioYTitle    = "#frac{"+dataSetTypeLabel(type1)+"}{"+dataSetTypeLabel(type2)+"}";
  } else {
    histsData      = &hists1; 
    histsMC        = &hists2; 
    uncData        = unc1;
    uncMC          = unc2;
    legEntriesData = &legEntries1;
    legEntriesMC   = &legEntries2;
    title          = header(false,dataSets1.front()->selectionUid());
    ratioYTitle    = "#frac{"+dataSetTypeLabel(type1)+"}{"+dataSetTypeLabel(type2)+"}";
  }

  // Draw
  can->cd();
  setYRange(histsMC->front(),histParams.logy()?3E-1:-1.);
  histsMC->front()->Draw("HISTE");
  for(std::vector<TH1*>::iterator it = histsMC->begin()+1;
      it != histsMC->end(); ++it) {
    (*it)->Draw("HISTsame");
  }
  // Plot only MC uncertainty band
  if( uncMC ) uncMC->Draw("E2same");
  for(std::vector<TH1*>::iterator it = histsData->begin();
      it != histsData->end(); ++it) {
    (*it)->Draw("PEsame");
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
  hRatio->Draw("PEsame");
  title->Draw("same");
  leg->Draw("same");
  gPad->RedrawAxis();
  if( histParams.logy() ) can->SetLogy();
  storeCanvas(can,var,dataSets1,dataSets2);

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
void PlotBuilder::createDistribution(const DataSet *dataSet, const TString &var, TH1* &h, TGraphAsymmErrors* &uncert, const HistParams &histParams) const {
  ++PlotBuilder::count_;
  
  // Create histogram  
  TString name = "plot";
  name += count_;
  h = new TH1D(name,"",histParams.nBins(),histParams.xMin(),histParams.xMax());
  h->Sumw2();
  if( histParams.xMax() > 1000. ) {
    h->GetXaxis()->SetNdivisions(505);
  }
  setXTitle(h,var);
  setYTitle(h,var);
  setGenericStyle(h,dataSet);

  // Create temporary histograms to store uncertainties
  TH1* hUw = static_cast<TH1*>(h->Clone(name+"Er"));
  TH1* hDn = static_cast<TH1*>(h->Clone(name+"Dn"));
  TH1* hUp = static_cast<TH1*>(h->Clone(name+"Up"));

  // Fill distributions
  for(EventIt itd = dataSet->evtsBegin(); itd != dataSet->evtsEnd(); ++itd) {
    double v = (*itd)->get(var);
    h->Fill(v,(*itd)->weight());
    hUw->Fill(v);
    if( (*itd)->hasUnc() ) {
      hDn->Fill(v,(*itd)->weightUncDn());
      hUp->Fill(v,(*itd)->weightUncUp());
    }
  }

  // Fill overflow bin
  if( histParams.hasOverflowBin() ) {
    double val = h->GetBinContent(h->GetNbinsX()) + h->GetBinContent(h->GetNbinsX()+1);
    double err = sqrt( h->GetBinError(h->GetNbinsX())*h->GetBinError(h->GetNbinsX()) + h->GetBinError(h->GetNbinsX()+1)*h->GetBinError(h->GetNbinsX()+1) );
    h->SetBinContent(h->GetNbinsX(),val);
    h->SetBinError(h->GetNbinsX(),err);

    val = hUw->GetBinContent(hUw->GetNbinsX()) + hUw->GetBinContent(hUw->GetNbinsX()+1);
    err = sqrt( hUw->GetBinError(hUw->GetNbinsX())*hUw->GetBinError(hUw->GetNbinsX()) + hUw->GetBinError(hUw->GetNbinsX()+1)*hUw->GetBinError(hUw->GetNbinsX()+1) );
    hUw->SetBinContent(hUw->GetNbinsX(),val);
    hUw->SetBinError(hUw->GetNbinsX(),err);

    if( hDn->GetEntries() ) {
      val = hDn->GetBinContent(hDn->GetNbinsX()) + hDn->GetBinContent(hDn->GetNbinsX()+1);
      err = sqrt( hDn->GetBinError(hDn->GetNbinsX())*hDn->GetBinError(hDn->GetNbinsX()) + hDn->GetBinError(hDn->GetNbinsX()+1)*hDn->GetBinError(hDn->GetNbinsX()+1) );
      hDn->SetBinContent(hDn->GetNbinsX(),val);
      hDn->SetBinError(hDn->GetNbinsX(),err);
    }
    if( hUp->GetEntries() ) {
      val = hUp->GetBinContent(hUp->GetNbinsX()) + hUp->GetBinContent(hUp->GetNbinsX()+1);
      err = sqrt( hUp->GetBinError(hUp->GetNbinsX())*hUp->GetBinError(hUp->GetNbinsX()) + hUp->GetBinError(hUp->GetNbinsX()+1)*hUp->GetBinError(hUp->GetNbinsX()+1) );
      hUp->SetBinContent(hUp->GetNbinsX(),val);
      hUp->SetBinError(hUp->GetNbinsX(),err);
    }
  }

  // Set error bars (reflect statistical uncertainties)
  // Several cases are distinguished depending on the type of data
  // - 'Data'       : expect unweighted histogram, leave as it is
  // - 'MC'         : sqrt(number of entries) = MC statistics
  // - 'Prediction' : sqrt(number of entries) = control sample statistics
  // See also DataSet::computeYield()
  if( dataSet->type() == DataSet::MC || dataSet->type() == DataSet::Prediction ) {
    for(int bin = 1; bin <= h->GetNbinsX(); ++bin) {
      if( hUw->GetBinContent(bin) > 0. ) {
	double scale = h->GetBinContent(bin)/hUw->GetBinContent(bin);
	h->SetBinError(bin,scale*hUw->GetBinError(bin));
      }
    }
  }


  // Create uncertainty band
  if( hDn->GetEntries() && hUp->GetEntries() ) {
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
  delete hUw;
  delete hDn;
  delete hUp;
}


void PlotBuilder::createStack(const DataSets &dataSets, const TString &var, std::vector<TH1*> &hists, std::vector<TString> &legEntries, TGraphAsymmErrors* &uncert, const HistParams &histParams) const {
  uncert = 0;
  for(DataSetRIt itd = dataSets.rbegin();
      itd != dataSets.rend(); ++itd) {
    TH1* h = 0;
    TGraphAsymmErrors* u = 0;
    createDistribution(*itd,var,h,u,histParams);
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
    setGenericStyle(h,*itd);
    TString entry = " "+dataSetLabelInPlot(*itd)+" (";
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
}


void PlotBuilder::storeCanvas(TCanvas* can, const TString &var, const DataSet* dataSet) const {
    out_.addPlot(can,var,dataSet->label(),dataSet->selectionUid());
  }

void PlotBuilder::storeCanvas(TCanvas* can, const TString &var, const TString &selection) const {
    out_.addPlot(can,var,selection);
  }

void PlotBuilder::storeCanvas(TCanvas* can, const TString &var, const DataSets &dataSets1, const DataSets &dataSets2) const {
    std::vector<TString> dataSetLabels1;
    for(DataSetIt itd = dataSets1.begin(); itd != dataSets1.end(); ++itd) {
      dataSetLabels1.push_back((*itd)->label());
    }
    std::vector<TString> dataSetLabels2;
    for(DataSetIt itd = dataSets2.begin(); itd != dataSets2.end(); ++itd) {
      dataSetLabels2.push_back((*itd)->label());
    }
    out_.addPlot(can,var,dataSetLabels1,dataSetLabels2,dataSets1.front()->selectionUid());
  }


void PlotBuilder::setXTitle(TH1* h, const TString &var) const {
  TString xTitle = Variable::label(var);
  if( Variable::unit(var) != "" ) {
    xTitle += " ["+Variable::unit(var)+"]";
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


int PlotBuilder::color(const DataSet *dataSet) const {
  // Default color
  int color = kGray;
  // Specified colors
  if( colors_.find(dataSet->label()) != colors_.end() ) {
    color = colors_.find(dataSet->label())->second;
  } else {
    // More specific default colors
    if( dataSet->type() == DataSet::Data ) {
      color = kBlack;
    }
  }

  return color;
}


int PlotBuilder::markerStyle(const DataSet *dataSet) const {
  // Default style
  int style = 21;
  // Specified styles
  if( markers_.find(dataSet->label()) != markers_.end() ) {
    style = markers_.find(dataSet->label())->second;
  } else {
    // More specific default styles
    if( dataSet->type() == DataSet::Data ) {
      style = 21;
    }
  }

  return style;
}


void PlotBuilder::setMarkerStyle(TH1* h, const DataSet *dataSet) const {
  h->SetMarkerStyle(markerStyle(dataSet));
  h->SetMarkerColor(color(dataSet));
  h->SetLineColor(h->GetMarkerColor());
}


void PlotBuilder::setGenericStyle(TH1* h, const DataSet *dataSet) const {
  if( dataSet->type() == DataSet::Data ) {
    setMarkerStyle(h,dataSet);
  } else if( dataSet->type() == DataSet::MC || dataSet->type() == DataSet::Prediction ) {
    int c = color(dataSet);
    h->SetMarkerStyle(0);
    h->SetMarkerColor(c);
    h->SetLineColor(c);
    h->SetFillColor(c);
  }
}


TPaveText* PlotBuilder::header(bool showLumi, const TString &info) const {
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
  txt->AddText("8 TeV"+(showLumi ? ",  "+lumiLabel() : "" )+(info != "" ? ",  "+info : ""));
  
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


TString PlotBuilder::dataSetLabelInPlot(const DataSet* dataSet) const {
  TString dataSetLabelInPlot = dataSet->label();
  std::map<TString,TString>::const_iterator it = dataSetLabelsInPlot_.find(dataSet->label());
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


bool PlotBuilder::checkForUnderOverFlow(const TH1* h, const TString &var, const DataSet *dataSet) const {
  bool underOverFlow = true;
  if( h->GetBinContent(0) > 0 ) {
    std::cerr << "    WARNING: Underflow in " << var << " distribution in dataset " << dataSet->label() << std::endl;
  } else if( h->GetBinContent(h->GetNbinsX()+1) > 0 ) {
    std::cerr << "    WARNING: Overflow in " << var << " distribution in dataset " << dataSet->label() << std::endl;
  } else {
    underOverFlow = false;
  }

  return underOverFlow;
}



PlotBuilder::HistParams::HistParams(const TString &cfg)
  : nBins_(1), xMin_(0), xMax_(1), logy_(false), norm_(false), hasOverflowBin_(true) {

  // Parse to overwrite defaults
  std::vector<TString> cfgs;
  if( Config::split(cfg,",",cfgs) ) {
    for(unsigned int i = 0; i < cfgs.size(); ++i) {
      if( i == 0 ) nBins_ = cfgs.at(i).Atoi();
      else if( i == 1 ) xMin_ = cfgs.at(i).Atof();
      else if( i == 2 ) xMax_ = cfgs.at(i).Atof();
      else if( i > 2 && cfgs.at(i) == "log" ) logy_ = true;
      else if( i > 2 && cfgs.at(i) == "norm" ) norm_ = true;
    }
  }

  // Overflow bin
  double binWidth = (xMax_-xMin_)/nBins_;
  xMax_ += binWidth;
  nBins_ += 1;
}
