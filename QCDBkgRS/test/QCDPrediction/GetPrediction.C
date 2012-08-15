#include <TROOT.h>
#include <TSystem.h>
#include <TH1.h>
#include <TH2.h>
#include <TProfile.h>
#include <TCanvas.h>
#include <TColor.h>
#include <TPad.h>
#include <TStyle.h>
#include <TFile.h>
#include <TPostScript.h>
#include <TLegend.h>
#include <TMath.h>
#include <TString.h>
#include <iostream>
#include <vector>
#include <string>

#include "Prediction.h"

using namespace std;

TCanvas* DrawComparison(TH1F* prediction, TH1F* selection, TString Title, TString LumiTitle, TString xTitle, bool isData)
{
   double MinX = selection->GetXaxis()->GetXmin();
   double MaxX = selection->GetXaxis()->GetXmax();
   TString titlePrediction;
   TString titleSelection;
   TString RatioTitle;
   
   if( isData ){
      titlePrediction = "Pred. from Data";
      titleSelection = "Data";
      RatioTitle = "(Pred-Data)/Data";
   }
   else {
      titlePrediction = "Data-driven Pred. from MC";
      titleSelection = "MC Expectation";
      RatioTitle = "(Pred-MC)/MC";
   }

   static Int_t c_LightBrown   = TColor::GetColor( "#D9D9CC" );

   prediction->SetAxisRange(MinX, MaxX, "X");
   prediction->SetMarkerStyle(20);
   prediction->SetMarkerSize(0.9);
   prediction->SetMarkerColor(kBlack);
   prediction->SetXTitle(xTitle);
   prediction->SetYTitle("Events");
   selection->SetAxisRange(MinX, MaxX, "X");
   selection->SetFillColor(c_LightBrown);
   selection->SetTitle("");
   selection->SetXTitle(xTitle);
   selection->SetYTitle("Events");

   TCanvas *c = new TCanvas("ca", "Comparison and ratio of two histos", 700, 700);

   TPad *pad1 = new TPad("pad1a", "pad1a", 0, 0.35, 1, 1);
   pad1->SetLogy();
   pad1->SetBottomMargin(0);
   pad1->Draw();
   pad1->cd();
  
   selection->DrawCopy("hist");
   prediction->Draw("same");
   selection->SetFillColor(kAzure-3);
   selection->SetFillStyle(3354);
   selection->DrawCopy("e2same");

   selection->SetFillStyle(1001);
   selection->SetFillColor(c_LightBrown);

   TLegend* leg1 = new TLegend(0.48, 0.63, 0.95, 0.83);
   leg1->SetFillStyle(0);
   leg1->SetLineStyle(1);
   leg1->SetTextFont(42);
   leg1->SetTextSize(0.04);
   leg1->AddEntry(selection, titleSelection, "lf");
   leg1->AddEntry(prediction, titlePrediction, "lep");
   leg1->Draw("same");
 
   TPaveText* pt = new TPaveText(0.11, 0.98, 0.95, 0.86, "NDC");
   pt->SetBorderSize(0);
   pt->SetFillStyle(0);
   pt->SetTextAlign(12);
   pt->SetTextSize(0.045);
   pt->AddText(Title);
   pt->AddText(LumiTitle);
   pt->Draw();

   c->cd();
   TPad *pad2 = new TPad("pad2a", "pad2a", 0, 0, 1, 0.35);
   pad2->SetTopMargin(0);
   pad2->Draw();
   pad2->cd();
   TH1F* r = new TH1F(*selection);
   r->SetTitle("");
   r->SetLabelSize(0.08, "XYZ");
   r->SetLabelOffset(0.01, "XYZ");
   r->SetTitleSize(0.09, "XYZ");
   r->SetTitleOffset(0.65, "Y");
   r->SetTickLength(0.05);
   r->SetYTitle(RatioTitle);
   r->SetStats(0);
   r->SetMarkerStyle(20);
   r->SetMarkerSize(0.9);
   r->SetMarkerColor(kBlack);
   r->Reset();
   r->Add(prediction, 1);
   r->Add(selection, -1);
   r->Divide(selection);
   r->SetMaximum(1.2);
   r->SetMinimum(-1.2);
   r->Draw("ep");
   TLine l;
   l.DrawLine(MinX, 0., MaxX, 0.);
   c->cd();
   return c;
}

int main()
{
   gROOT->Reset();
   gROOT->SetStyle("Plain");
   //gStyle->SetPalette(51, 0);

   // For the canvas:
   gStyle->SetCanvasColor(0);
   //gStyle->SetCanvasBorderMode(0);

   // For the Pad:
   gStyle->SetPadColor(0);  
   gStyle->SetPadTickX(1);
   gStyle->SetPadTickY(1);
   gStyle->SetPadBorderSize(2);
   //gStyle->SetPadBorderMode(0);
  
   // For the frame:
   gStyle->SetFrameBorderMode(0);

   // For the histo:
   // gStyle->SetMarkerSize(0.7);
   // gStyle->SetMarkerStyle(20);
   // gStyle->SetMarkerColor(1);
  
   // For the statistics box:
   gStyle->SetOptStat(0);
   //gStyle->SetOptFit(1011);
  
   // Margins:
   gStyle->SetPadBottomMargin(0.25);
   gStyle->SetPadTopMargin(0.15);
   gStyle->SetPadLeftMargin(0.15);
   gStyle->SetPadRightMargin(0.1);
      
   // For the Global title:
   gStyle->SetOptTitle(0);
   gStyle->SetTitleColor(1);
   gStyle->SetTitleFillColor(10);
   gStyle->SetTitleTextColor(1); 
   gStyle->SetTitleFont(42);
   gStyle->SetTitleFontSize(0.05);
   gStyle->SetTitleBorderSize(0);

   // For the axis
   gStyle->SetNdivisions(510, "X");
   gStyle->SetNdivisions(510, "Y");
   gStyle->SetTickLength(0.03);

   // For the axis titles:
   gStyle->SetTitleOffset(1.4, "X");
   gStyle->SetTitleOffset(1.25, "Y");
   gStyle->SetTitleOffset(0.5, "Z");
   gStyle->SetTitleSize(0.05, "XYZ");
   gStyle->SetTitleFont(42, "XYZ");
   //gStyle->SetTitleX(0.15);
   //gStyle->SetTitleY(0.99);

   // For the axis labels:
   gStyle->SetLabelSize(0.04, "XYZ");
   gStyle->SetLabelOffset(0.01, "XYZ");
   gStyle->SetLabelFont(42, "XYZ");

   // For the legend
   gStyle->SetLegendBorderSize(0);
  
   gROOT->ForceStyle();

   /////////////////////////////////   
   // open files for MC

   // file with prediction
   TFile *f = TFile::Open("/afs/naf.desy.de/user/k/kriheine/kheine/grid-control_jobs/QCDSmearing_MCClosure_8TeV_2012_NoPUReweighting_standardJets_pt15_v1.root");
   //TFile *f = TFile::Open("../QCDSmearingClosure_OnMC.root");

   // file with event selection
   TFile *g = TFile::Open("/afs/naf.desy.de/user/k/kriheine/kheine/grid-control_jobs/QCDSmearing_MCClosure_8TeV_2012_NoPUReweighting_standardJets_pt15_v1.root");
   //TFile *g = TFile::Open("../QCDSmearingClosure_OnMC.root");

     
   // initialize new Prediction object
   Prediction *pred_;
   pred_ = new Prediction(*f, *g);
   bool isData = false;
  
   TString LumiTitle;
   if( isData ) LumiTitle = "CMS preliminary, L = x.yz fb^{  -1}, #sqrt{s} = 8 TeV";
   else LumiTitle = "CMS Simulation, #sqrt{s} = 8 TeV";

   //TString postfix = "_genJets";
   // TString postfix = "_chsJets";
   TString postfix = "_standardJets";

   vector<TString> xTitle_presel;
   xTitle_presel.push_back("H_{T} (GeV)");
   xTitle_presel.push_back("#slash{H}_{T} (GeV)");
   xTitle_presel.push_back("Jet1 p_{T} (GeV)");
   xTitle_presel.push_back("Jet2 p_{T} (GeV)");
   //    // xTitle_presel.push_back("Jet3 p_{T} (GeV)");
   xTitle_presel.push_back("Jet1 #eta");
   xTitle_presel.push_back("Jet2 #eta");
   //    // xTitle_presel.push_back("Jet3 #eta");

   vector<TString> xTitle_deltaPhi;
   xTitle_deltaPhi.push_back("H_{T} (GeV)");
   xTitle_deltaPhi.push_back("#slash{H}_{T} (GeV)");
   xTitle_deltaPhi.push_back("Jet1 p_{T} (GeV)");
   xTitle_deltaPhi.push_back("Jet2 p_{T} (GeV)");
   //  xTitle_deltaPhi.push_back("Jet3 p_{T} (GeV)");
   xTitle_deltaPhi.push_back("Jet1 #eta");
   xTitle_deltaPhi.push_back("Jet2 #eta");
   // xTitle_deltaPhi.push_back("Jet3 #eta");

   vector<TString> xTitle_searchBins;
   xTitle_searchBins.push_back("#slash{H}_{T} (GeV)");
   xTitle_searchBins.push_back("#slash{H}_{T} (GeV)");
   xTitle_searchBins.push_back("#slash{H}_{T} (GeV)");
   xTitle_searchBins.push_back("#slash{H}_{T} (GeV)");
   xTitle_searchBins.push_back("#slash{H}_{T} (GeV)");
   xTitle_searchBins.push_back("#slash{H}_{T} (GeV)");
   xTitle_searchBins.push_back("#slash{H}_{T} (GeV)");
   xTitle_searchBins.push_back("#slash{H}_{T} (GeV)");
   xTitle_searchBins.push_back("#slash{H}_{T} (GeV)");
   xTitle_searchBins.push_back("#slash{H}_{T} (GeV)");
   xTitle_searchBins.push_back("#slash{H}_{T} (GeV)");
   xTitle_searchBins.push_back("#slash{H}_{T} (GeV)");

   vector<TString> hist_type_presel;
   hist_type_presel.push_back("HT_presel");
   hist_type_presel.push_back("MHT_presel");
   hist_type_presel.push_back("Jet1Pt_presel");
   hist_type_presel.push_back("Jet2Pt_presel");
//    //  hist_type_presel.push_back("Jet3Pt_presel");
   hist_type_presel.push_back("Jet1Eta_presel");
   hist_type_presel.push_back("Jet2Eta_presel");
//    //  hist_type_presel.push_back("Jet3Eta_presel");

   vector<TString> hist_type_deltaPhi;
   hist_type_deltaPhi.push_back("HT_deltaPhi");
   hist_type_deltaPhi.push_back("MHT_deltaPhi");    
   hist_type_deltaPhi.push_back("Jet1Pt_deltaPhi"); 
   hist_type_deltaPhi.push_back("Jet2Pt_deltaPhi"); 
   //  hist_type_deltaPhi.push_back("Jet3Pt_deltaPhi"); 
   hist_type_deltaPhi.push_back("Jet1Eta_deltaPhi");
   hist_type_deltaPhi.push_back("Jet2Eta_deltaPhi");
   //  hist_type_deltaPhi.push_back("Jet3Eta_deltaPhi");

   vector<TString> hist_type_searchBins;
   hist_type_searchBins.push_back("MHT_JetBin1_HTlow");    
   hist_type_searchBins.push_back("MHT_JetBin1_HTmedium"); 
   hist_type_searchBins.push_back("MHT_JetBin1_HThigh");   
   hist_type_searchBins.push_back("MHT_JetBin2_HTlow");    
   hist_type_searchBins.push_back("MHT_JetBin2_HTmedium"); 
   hist_type_searchBins.push_back("MHT_JetBin2_HThigh");   
   hist_type_searchBins.push_back("MHT_JetBin3_HTlow");    
   hist_type_searchBins.push_back("MHT_JetBin3_HTmedium"); 
   hist_type_searchBins.push_back("MHT_JetBin3_HThigh");   
   hist_type_searchBins.push_back("MHT_JetBin4_HTlow");    
   hist_type_searchBins.push_back("MHT_JetBin4_HTmedium"); 
   hist_type_searchBins.push_back("MHT_JetBin4_HThigh");  


   // plots for preselection (2 jets)
   TString Title;
   Title = "2 jets";

 //   if( hist_type_presel.size() != xTitle_presel.size() ) cout << "Error: Missing xTitles preselection!!" << endl;

//    for(int i = 0; i < hist_type_presel.size(); i++ ) {
//       TCanvas *c = DrawComparison( pred_->GetPredictionHisto(hist_type_presel.at(i)), pred_->GetSelectionHisto(hist_type_presel.at(i)), Title, LumiTitle, xTitle_presel.at(i), isData); 

//       if      ( i == 0) c->Print("outpout_GetPrediction/QCD_presel" + postfix + ".ps(");
//       else if ( i == hist_type_presel.size()-1 ) c->Print("outpout_GetPrediction/QCD_presel" + postfix + ".ps)");
//       else c->Print("outpout_GetPrediction/QCD_presel" + postfix + ".ps");

//       c->Print("outpout_GetPrediction/" + hist_type_presel.at(i) + postfix + ".png");
//    }

   // plots for deltaPhi 
   Title = "2 jets, #Delta#phi(#slash{H}_{T}, jet1-2,3)";

  //  if( hist_type_deltaPhi.size() != xTitle_deltaPhi.size() ) cout << "Error: Missing xTitles preselection!!" << endl;

//    for(int i = 0; i < hist_type_deltaPhi.size(); i++ ) {
//       TCanvas *c = DrawComparison( pred_->GetPredictionHisto(hist_type_deltaPhi.at(i)), pred_->GetSelectionHisto(hist_type_deltaPhi.at(i)), Title, LumiTitle, xTitle_deltaPhi.at(i), isData); 

//       if      ( i == 0) c->Print("outpout_GetPrediction/QCD_deltaPhi" + postfix + ".ps(");
//       else if ( i == hist_type_deltaPhi.size()-1 ) c->Print("outpout_GetPrediction/QCD_deltaPhi" + postfix + ".ps)");
//       else c->Print("outpout_GetPrediction/QCD_deltaPhi" + postfix + ".ps");

//       c->Print("outpout_GetPrediction/" + hist_type_deltaPhi.at(i) + postfix + ".png");
//    }

   // plots for search bins 
   //jet Bin 1
  //  Title = "2 - 3 jets, #Delta#phi cut, HT = 500 - 900 GeV";
//    TCanvas *c = DrawComparison( pred_->GetPredictionHisto("MHT_JetBin1_HTlow"), pred_->GetSelectionHisto("MHT_JetBin1_HTlow"), Title, LumiTitle,"#slash{H}_{T} (GeV)", isData); 
//    c->Print("outpout_GetPrediction/QCD_searchBins" + postfix + ".ps(");
//    c->Print("outpout_GetPrediction/MHT_JetBin1_HTlow" + postfix + ".png");

//    Title = "2 - 3 jets, #Delta#phi cut, HT = 900 - 1300 GeV";
//    c =  DrawComparison( pred_->GetPredictionHisto("MHT_JetBin1_HTmedium"), pred_->GetSelectionHisto("MHT_JetBin1_HTmedium"), Title, LumiTitle,"#slash{H}_{T} (GeV)", isData);
//    c->Print("outpout_GetPrediction/QCD_searchBins" + postfix + ".ps");
//    c->Print("outpout_GetPrediction/MHT_JetBin1_HTmedium" + postfix + ".png");

//    Title = "2 - 3 jets, #Delta#phi cut, HT >= 1300 GeV";
//    c =  DrawComparison( pred_->GetPredictionHisto("MHT_JetBin1_HThigh"), pred_->GetSelectionHisto("MHT_JetBin1_HThigh"), Title, LumiTitle,"#slash{H}_{T} (GeV)", isData); 
//    c->Print("outpout_GetPrediction/QCD_searchBins" + postfix + ".ps");
//    c->Print("outpout_GetPrediction/MHT_JetBin1_HThigh" + postfix + ".png");

//    // jet Bin2
//    Title = "4 - 5 jets, #Delta#phi cut, HT = 500 - 900 GeV";
//    c = DrawComparison( pred_->GetPredictionHisto("MHT_JetBin2_HTlow"), pred_->GetSelectionHisto("MHT_JetBin2_HTlow"), Title, LumiTitle,"#slash{H}_{T} (GeV)", isData); 
//    c->Print("outpout_GetPrediction/QCD_searchBins" + postfix + ".ps");
//    c->Print("outpout_GetPrediction/MHT_JetBin2_HTlow" + postfix + ".png");

//    Title = "4 - 5 jets, #Delta#phi cut, HT = 900 - 1300 GeV";
//    c =  DrawComparison( pred_->GetPredictionHisto("MHT_JetBin2_HTmedium"), pred_->GetSelectionHisto("MHT_JetBin2_HTmedium"), Title, LumiTitle,"#slash{H}_{T} (GeV)", isData);
//    c->Print("outpout_GetPrediction/QCD_searchBins" + postfix + ".ps");
//    c->Print("outpout_GetPrediction/MHT_JetBin2_HTmedium" + postfix + ".png");

//    Title = "4 - 5 jets, #Delta#phi cut, HT >= 1300 GeV";
//    c =  DrawComparison( pred_->GetPredictionHisto("MHT_JetBin2_HThigh"), pred_->GetSelectionHisto("MHT_JetBin2_HThigh"), Title, LumiTitle,"#slash{H}_{T} (GeV)", isData);
//    c->Print("outpout_GetPrediction/QCD_searchBins" + postfix + ".ps");
//    c->Print("outpout_GetPrediction/MHT_JetBin2_HThigh" + postfix + ".png");

//    // jet Bin3
//    Title = "6 - 7 jets, #Delta#phi cut, HT = 500 - 900 GeV";
//    c = DrawComparison( pred_->GetPredictionHisto("MHT_JetBin3_HTlow"), pred_->GetSelectionHisto("MHT_JetBin3_HTlow"), Title, LumiTitle,"#slash{H}_{T} (GeV)", isData); 
//    c->Print("outpout_GetPrediction/QCD_searchBins" + postfix + ".ps");
//    c->Print("outpout_GetPrediction/MHT_JetBin3_HTlow" + postfix + ".png");

//    Title = "6 - 7 jets, #Delta#phi cut, HT = 900 - 1300 GeV";
//    c =  DrawComparison( pred_->GetPredictionHisto("MHT_JetBin3_HTmedium"), pred_->GetSelectionHisto("MHT_JetBin3_HTmedium"), Title, LumiTitle,"#slash{H}_{T} (GeV)", isData);
//    c->Print("outpout_GetPrediction/QCD_searchBins" + postfix + ".ps");
//    c->Print("outpout_GetPrediction/MHT_JetBin3_HTmedium" + postfix + ".png");

//    Title = "6 - 7 jets, #Delta#phi cut, HT >= 1300 GeV";
//    c =  DrawComparison( pred_->GetPredictionHisto("MHT_JetBin3_HThigh"), pred_->GetSelectionHisto("MHT_JetBin3_HThigh"), Title, LumiTitle,"#slash{H}_{T} (GeV)", isData);
//    c->Print("outpout_GetPrediction/QCD_searchBins" + postfix + ".ps");
//    c->Print("outpout_GetPrediction/MHT_JetBin3_HThigh" + postfix + ".png");

//    // jet Bin 4
//    Title = ">= 8 jets, #Delta#phi cut, HT = 500 - 900 GeV";
//    c = DrawComparison( pred_->GetPredictionHisto("MHT_JetBin4_HTlow"), pred_->GetSelectionHisto("MHT_JetBin4_HTlow"), Title, LumiTitle,"#slash{H}_{T} (GeV)", isData); 
//    c->Print("outpout_GetPrediction/QCD_searchBins" + postfix + ".ps");
//    c->Print("outpout_GetPrediction/MHT_JetBin4_HTlow" + postfix + ".png");

//    Title = ">= 8 jets, #Delta#phi cut, HT = 900 - 1300 GeV";
//    c =  DrawComparison( pred_->GetPredictionHisto("MHT_JetBin4_HTmedium"), pred_->GetSelectionHisto("MHT_JetBin4_HTmedium"), Title, LumiTitle,"#slash{H}_{T} (GeV)", isData);
//    c->Print("outpout_GetPrediction/QCD_searchBins" + postfix + ".ps");
//    c->Print("outpout_GetPrediction/MHT_JetBin4_HTmedium" + postfix + ".png");
  
//    Title = ">= 8 jets, #Delta#phi cut, HT >= 1300 GeV";
//    c =  DrawComparison( pred_->GetPredictionHisto("MHT_JetBin4_HThigh"), pred_->GetSelectionHisto("MHT_JetBin4_HThigh"), Title, LumiTitle,"#slash{H}_{T} (GeV)", isData);
//    c->Print("outpout_GetPrediction/QCD_searchBins" + postfix + ".ps)");
//    c->Print("outpout_GetPrediction/MHT_JetBin4_HThigh" + postfix + ".png");

   Title = "#Delta#phi cut, HT > 500 GeV, MHT > 200 GeV";
   TCanvas *c =  DrawComparison( pred_->GetPredictionHisto("NJets_baseline"), pred_->GetSelectionHisto("NJets_baseline"), Title, LumiTitle,"NJets", isData);
   c->Print("outpout_GetPrediction/QCD_NJets" + postfix + ".ps");
   c->Print("outpout_GetPrediction/NJets_baseline" + postfix + ".png");

   Title = ">= 2 jets, #Delta#phi cut, HT > 500 GeV";
   c =  DrawComparison( pred_->GetPredictionHisto("MHT_baseline"), pred_->GetSelectionHisto("MHT_baseline"), Title, LumiTitle,"#slash{H}_{T} (GeV)", isData);
   c->Print("outpout_GetPrediction/QCD_MHT_baseline" + postfix + ".ps");
   c->Print("outpout_GetPrediction/MHT_baseline" + postfix + ".png");

   Title = ">= 2 jets, #Delta#phi cut, MHT > 200 GeV";
   c =  DrawComparison( pred_->GetPredictionHisto("HT_baseline"), pred_->GetSelectionHisto("HT_baseline"), Title, LumiTitle,"H_{T} (GeV)", isData);
   c->Print("outpout_GetPrediction/QCD_HT_baseline" + postfix + ".ps");
   c->Print("outpout_GetPrediction/HT_baseline" + postfix + ".png");
  

   // set search bin cut values for HT and MHT (check with Prediction.C)
   double HTlow = 500;
   double HTmedium = 900;
   double HThigh = 1300;
   double MHTlow = 200;
   double MHTmedium = 350;
   double MHThigh = 500;
   int SmearRep = 100;
  
   /*
   // QCD predictions in search bins
   // first jet multiplicity bin
   cout << "----------------------" << endl;
   cout << "----------------------" << endl;
   cout << "NJets = 2 or 3" << endl;
   cout << "----------------------" << endl;
   cout << "----------------------" << endl;
   cout << "HT = " << HTlow << "-" << HTmedium << endl;
   cout << "----------------------" << endl;
   cout << "MHT = " << MHTlow << "-" << MHTmedium << endl;
   cout << "----------------------" << endl;
   cout << "Integral Selection:  " << pred_->GetResultValue(pred_->GetSelectionHisto("MHT_JetBin1_HTlow"),
                                                      MHTlow, MHTmedium) 
        << " +- " << pred_->GetResultError( pred_->GetSelectionHisto("MHT_JetBin1_HTlow"), MHTlow, MHTmedium)
        << endl;
   cout << "Integral Prediction: " << pred_->GetResultValue(pred_->GetPredictionHisto("MHT_JetBin1_HTlow"),
                                                      MHTlow, MHTmedium) 
        << " +- " << pred_->GetResultError( pred_->GetPredictionHisto("MHT_JetBin1_HTlow"), MHTlow, MHTmedium)
        << endl;
   cout << "Ratio Selection/Pred: " << pred_->GetResultValue(pred_->GetSelectionHisto("MHT_JetBin1_HTlow"), 
                                                      MHTlow, MHTmedium)/ pred_->GetResultValue(pred_->GetPredictionHisto("MHT_JetBin1_HTlow"), MHTlow, MHTmedium); 

   cout << "----------------------" << endl;
   cout << "----------------------" << endl;
   cout << "HT = " << HTlow << "-" << HTmedium << endl;
   cout << "----------------------" << endl;
   cout << "MHT = " << MHTmedium << "-" << MHThigh << endl;
   cout << "----------------------" << endl;
   cout << "Integral Selection:  " << pred_->GetResultValue(pred_->GetSelectionHisto("MHT_JetBin1_HTlow"), MHTmedium, MHThigh) 
        << " +- " << pred_->GetResultError(pred_->GetSelectionHisto("MHT_JetBin1_HTlow"), MHTmedium, MHThigh) << endl;
   cout << "Integral Prediction: " << pred_->GetResultValue(pred_->GetPredictionHisto("MHT_JetBin1_HTlow"), MHTmedium, MHThigh) 
        << " +- " << pred_->GetResultError(pred_->GetPredictionHisto("MHT_JetBin1_HTlow"), MHTmedium, MHThigh) << endl;
   cout << "Ratio Selection/Pred: " << pred_->GetResultValue(pred_->GetSelectionHisto("MHT_JetBin1_HTlow"), MHTmedium, MHThigh)/pred_->GetResultValue(pred_->GetPredictionHisto("MHT_JetBin1_HTlow"), MHTmedium, MHThigh); 
   cout << "----------------------" << endl;

   cout << "----------------------" << endl;
   cout << "HT = " << HTlow << "-" << HTmedium << endl;
   cout << "----------------------" << endl;
   cout << "MHT > " << MHThigh << endl;
   cout << "----------------------" << endl;
   cout << "Integral Selection:  " << pred_->GetResultValue(pred_->GetSelectionHisto("MHT_JetBin1_HTlow"), MHThigh, -1) 
        << " +- " << pred_->GetResultError(pred_->GetSelectionHisto("MHT_JetBin1_HTlow"), MHThigh, -1) << endl;
   cout << "Integral Prediction: " << pred_->GetResultValue(pred_->GetPredictionHisto("MHT_JetBin1_HTlow"), MHThigh, -1) 
        << " +- " << pred_->GetResultError(pred_->GetPredictionHisto("MHT_JetBin1_HTlow"), MHThigh, -1) << endl;
   cout << "Ratio Selection/Pred: " << pred_->GetResultValue(pred_->GetSelectionHisto("MHT_JetBin1_HTlow"), MHThigh, -1)/pred_->GetResultValue(pred_->GetPredictionHisto("MHT_JetBin1_HTlow"), MHThigh, -1); 
   cout << "----------------------" << endl;

   cout << "----------------------" << endl;
   cout << "HT = " << HTmedium << "-" << HThigh << endl;
   cout << "----------------------" << endl;
   cout << "MHT = " << MHTlow << "-" << MHTmedium << endl;
   cout << "----------------------" << endl;
   cout << "Integral Selection:  " << pred_->GetResultValue(pred_->GetSelectionHisto("MHT_JetBin1_HTmedium"), MHTlow, MHTmedium) 
        << " +- " << pred_->GetResultError(pred_->GetSelectionHisto("MHT_JetBin1_HTmedium"), MHTlow, MHTmedium) << endl;
   cout << "Integral Prediction: " << pred_->GetResultValue(pred_->GetPredictionHisto("MHT_JetBin1_HTmedium"), MHTlow, MHTmedium) 
        << " +- " << pred_->GetResultError(pred_->GetPredictionHisto("MHT_JetBin1_HTmedium"), MHTlow, MHTmedium) << endl;
   cout << "Ratio Selection/Pred: " << pred_->GetResultValue(pred_->GetSelectionHisto("MHT_JetBin1_HTmedium"), MHTlow, MHTmedium)/pred_->GetResultValue(pred_->GetPredictionHisto("MHT_JetBin1_HTmedium"), MHTlow, MHTmedium); 
   cout << "----------------------" << endl;

   cout << "----------------------" << endl;
   cout << "HT = " << HTmedium << "-" << HThigh << endl;
   cout << "----------------------" << endl;
   cout << "MHT = " << MHTmedium << "-" << MHThigh << endl;
   cout << "----------------------" << endl;
   cout << "Integral Selection:  " << pred_->GetResultValue(pred_->GetSelectionHisto("MHT_JetBin1_HTmedium"), MHTmedium, MHThigh) 
        << " +- " << pred_->GetResultError(pred_->GetSelectionHisto("MHT_JetBin1_HTmedium"), MHTmedium, MHThigh) << endl;
   cout << "Integral Prediction: " << pred_->GetResultValue(pred_->GetPredictionHisto("MHT_JetBin1_HTmedium"), MHTmedium, MHThigh) 
        << " +- " << pred_->GetResultError(pred_->GetPredictionHisto("MHT_JetBin1_HTmedium"), MHTmedium, MHThigh) << endl;
   cout << "Ratio Selection/Pred: " << pred_->GetResultValue(pred_->GetSelectionHisto("MHT_JetBin1_HTmedium"), MHTmedium, MHThigh)/pred_->GetResultValue(pred_->GetPredictionHisto("MHT_JetBin1_HTmedium"), MHTmedium, MHThigh); 
   cout << "----------------------" << endl;

   cout << "----------------------" << endl;
   cout << "HT = " << HTmedium << "-" << HThigh << endl;
   cout << "----------------------" << endl;
   cout << "MHT > " << MHThigh << endl;
   cout << "----------------------" << endl;
   cout << "Integral Selection:  " << pred_->GetResultValue(pred_->GetSelectionHisto("MHT_JetBin1_HTmedium"), MHThigh, -1) 
        << " +- " << pred_->GetResultError(pred_->GetSelectionHisto("MHT_JetBin1_HTmedium"), MHThigh, -1) << endl;
   cout << "Integral Prediction: " << pred_->GetResultValue(pred_->GetPredictionHisto("MHT_JetBin1_HTmedium"), MHThigh, -1) 
        << " +- " << pred_->GetResultError(pred_->GetPredictionHisto("MHT_JetBin1_HTmedium"), MHThigh, -1) << endl;
   cout << "Ratio Selection/Pred: " << pred_->GetResultValue(pred_->GetPredictionHisto("MHT_JetBin1_HTmedium"), MHThigh, -1)/pred_->GetResultValue(pred_->GetSelectionHisto("MHT_JetBin1_HTmedium"), MHThigh, -1); 
   cout << "----------------------" << endl;

 cout << "----------------------" << endl;
   cout << "HT > " << HThigh << endl;
   cout << "----------------------" << endl;
   cout << "MHT = " << MHTlow << "-" << MHTmedium << endl;
   cout << "----------------------" << endl;
   cout << "Integral Selection:  " << pred_->GetResultValue(pred_->GetSelectionHisto("MHT_JetBin1_HThigh"), MHTlow, MHTmedium) 
        << " +- " << pred_->GetResultError(pred_->GetSelectionHisto("MHT_JetBin1_HThigh"), MHTlow, MHTmedium) << endl;
   cout << "Integral Prediction: " << pred_->GetResultValue(pred_->GetPredictionHisto("MHT_JetBin1_HThigh"), MHTlow, MHTmedium) 
        << " +- " << pred_->GetResultError(pred_->GetPredictionHisto("MHT_JetBin1_HThigh"), MHTlow, MHTmedium) << endl;
   cout << "Ratio Selection/Pred: " << pred_->GetResultValue(pred_->GetSelectionHisto("MHT_JetBin1_HThigh"), MHTlow, MHTmedium)/pred_->GetResultValue(pred_->GetPredictionHisto("MHT_JetBin1_HThigh"), MHTlow, MHTmedium); 
   cout << "----------------------" << endl;

   cout << "----------------------" << endl;
   cout << "HT > " << HThigh << endl;
   cout << "----------------------" << endl;
   cout << "MHT = " << MHTmedium << "-" << MHThigh << endl;
   cout << "----------------------" << endl;
   cout << "Integral Selection:  " << pred_->GetResultValue(pred_->GetSelectionHisto("MHT_JetBin1_HThigh"), MHTmedium, MHThigh) 
        << " +- " << pred_->GetResultError(pred_->GetSelectionHisto("MHT_JetBin1_HThigh"), MHTmedium, MHThigh) << endl;
   cout << "Integral Prediction: " << pred_->GetResultValue(pred_->GetPredictionHisto("MHT_JetBin1_HThigh"), MHTmedium, MHThigh) 
        << " +- " << pred_->GetResultError(pred_->GetPredictionHisto("MHT_JetBin1_HThigh"), MHTmedium, MHThigh) << endl;
   cout << "Ratio Selection/Pred: " << pred_->GetResultValue(pred_->GetSelectionHisto("MHT_JetBin1_HThigh"), MHTmedium, MHThigh)/pred_->GetResultValue(pred_->GetPredictionHisto("MHT_JetBin1_HThigh"), MHTmedium, MHThigh); 
   cout << "----------------------" << endl;

   cout << "----------------------" << endl;
   cout << "HT > " << HThigh << endl;
   cout << "----------------------" << endl;
   cout << "MHT > " << MHThigh << endl;
   cout << "----------------------" << endl;
   cout << "Integral Selection:  " << pred_->GetResultValue(pred_->GetSelectionHisto("MHT_JetBin1_HThigh"), MHThigh, -1) 
        << " +- " << pred_->GetResultError(pred_->GetSelectionHisto("MHT_JetBin1_HThigh"), MHThigh, -1) << endl;
   cout << "Integral Prediction: " << pred_->GetResultValue(pred_->GetPredictionHisto("MHT_JetBin1_HThigh"), MHThigh, -1) 
        << " +- " << pred_->GetResultError(pred_->GetPredictionHisto("MHT_JetBin1_HThigh"), MHThigh, -1) << endl;
   cout << "Ratio Selection/Pred: " << pred_->GetResultValue(pred_->GetSelectionHisto("MHT_JetBin1_HThigh"), MHThigh, -1)/pred_->GetResultValue(pred_->GetPredictionHisto("MHT_JetBin1_HThigh"), MHThigh, -1); 
   cout << "----------------------" << endl;


   // second jet multiplicity bin
   cout << "----------------------" << endl;
   cout << "----------------------" << endl;
   cout << "NJets = 4 or 5" << endl;
   cout << "----------------------" << endl;
   cout << "----------------------" << endl;
   cout << "HT = " << HTlow << "-" << HTmedium << endl;
   cout << "----------------------" << endl;
   cout << "MHT = " << MHTlow << "-" << MHTmedium << endl;
   cout << "----------------------" << endl;
   cout << "Integral Selection:  " << pred_->GetResultValue(pred_->GetSelectionHisto("MHT_JetBin2_HTlow"), MHTlow, MHTmedium) 
        << " +- " << pred_->GetResultError(pred_->GetSelectionHisto("MHT_JetBin2_HTlow"), MHTlow, MHTmedium) << endl;
   cout << "Integral Prediction: " << pred_->GetResultValue(pred_->GetPredictionHisto("MHT_JetBin2_HTlow"), MHTlow, MHTmedium) 
        << " +- " << pred_->GetResultError(pred_->GetPredictionHisto("MHT_JetBin2_HTlow"), MHTlow, MHTmedium) << endl;
   cout << "Ratio Selection/Pred: " << pred_->GetResultValue(pred_->GetSelectionHisto("MHT_JetBin2_HTlow"), MHTlow, MHTmedium)/pred_->GetResultValue(pred_->GetPredictionHisto("MHT_JetBin2_HTlow"), MHTlow, MHTmedium); 
   cout << "----------------------" << endl;

   cout << "----------------------" << endl;
   cout << "HT = " << HTlow << "-" << HTmedium << endl;
   cout << "----------------------" << endl;
   cout << "MHT = " << MHTmedium << "-" << MHThigh << endl;
   cout << "----------------------" << endl;
   cout << "Integral Selection:  " << pred_->GetResultValue(pred_->GetSelectionHisto("MHT_JetBin2_HTlow"), MHTmedium, MHThigh) 
        << " +- " << pred_->GetResultError(pred_->GetSelectionHisto("MHT_JetBin2_HTlow"), MHTmedium, MHThigh) << endl;
   cout << "Integral Prediction: " << pred_->GetResultValue(pred_->GetPredictionHisto("MHT_JetBin2_HTlow"), MHTmedium, MHThigh) 
        << " +- " << pred_->GetResultError(pred_->GetPredictionHisto("MHT_JetBin2_HTlow"), MHTmedium, MHThigh) << endl;
   cout << "Ratio Selection/Pred: " << pred_->GetResultValue(pred_->GetSelectionHisto("MHT_JetBin2_HTlow"), MHTmedium, MHThigh)/pred_->GetResultValue(pred_->GetPredictionHisto("MHT_JetBin2_HTlow"), MHTmedium, MHThigh); 
   cout << "----------------------" << endl;

   cout << "----------------------" << endl;
   cout << "HT = " << HTlow << "-" << HTmedium << endl;
   cout << "----------------------" << endl;
   cout << "MHT > " << MHThigh << endl;
   cout << "----------------------" << endl;
   cout << "Integral Selection:  " << pred_->GetResultValue(pred_->GetSelectionHisto("MHT_JetBin2_HTlow"), MHThigh, -1) 
        << " +- " << pred_->GetResultError(pred_->GetSelectionHisto("MHT_JetBin2_HTlow"), MHThigh, -1) << endl;
   cout << "Integral Prediction: " << pred_->GetResultValue(pred_->GetPredictionHisto("MHT_JetBin2_HTlow"), MHThigh, -1) 
        << " +- " << pred_->GetResultError(pred_->GetPredictionHisto("MHT_JetBin2_HTlow"), MHThigh, -1) << endl;
   cout << "Ratio Selection/Pred: " << pred_->GetResultValue(pred_->GetSelectionHisto("MHT_JetBin2_HTlow"), MHThigh, -1)/pred_->GetResultValue(pred_->GetPredictionHisto("MHT_JetBin2_HTlow"), MHThigh, -1); 
   cout << "----------------------" << endl;

   cout << "----------------------" << endl;
   cout << "HT = " << HTmedium << "-" << HThigh << endl;
   cout << "----------------------" << endl;
   cout << "MHT = " << MHTlow << "-" << MHTmedium << endl;
   cout << "----------------------" << endl;
   cout << "Integral Selection:  " << pred_->GetResultValue(pred_->GetSelectionHisto("MHT_JetBin2_HTmedium"), MHTlow, MHTmedium) 
        << " +- " << pred_->GetResultError(pred_->GetSelectionHisto("MHT_JetBin2_HTmedium"), MHTlow, MHTmedium) << endl;
   cout << "Integral Prediction: " << pred_->GetResultValue(pred_->GetPredictionHisto("MHT_JetBin2_HTmedium"), MHTlow, MHTmedium) 
        << " +- " << pred_->GetResultError(pred_->GetPredictionHisto("MHT_JetBin2_HTmedium"), MHTlow, MHTmedium) << endl;
   cout << "Ratio Selection/Pred: " << pred_->GetResultValue(pred_->GetSelectionHisto("MHT_JetBin2_HTmedium"), MHTlow, MHTmedium)/pred_->GetResultValue(pred_->GetPredictionHisto("MHT_JetBin2_HTmedium"), MHTlow, MHTmedium); 
   cout << "----------------------" << endl;

   cout << "----------------------" << endl;
   cout << "HT = " << HTmedium << "-" << HThigh << endl;
   cout << "----------------------" << endl;
   cout << "MHT = " << MHTmedium << "-" << MHThigh << endl;
   cout << "----------------------" << endl;
   cout << "Integral Selection:  " << pred_->GetResultValue(pred_->GetSelectionHisto("MHT_JetBin2_HTmedium"), MHTmedium, MHThigh) 
        << " +- " << pred_->GetResultError(pred_->GetSelectionHisto("MHT_JetBin2_HTmedium"), MHTmedium, MHThigh) << endl;
   cout << "Integral Prediction: " << pred_->GetResultValue(pred_->GetPredictionHisto("MHT_JetBin2_HTmedium"), MHTmedium, MHThigh) 
        << " +- " << pred_->GetResultError(pred_->GetPredictionHisto("MHT_JetBin2_HTmedium"), MHTmedium, MHThigh) << endl;
   cout << "Ratio Selection/Pred: " << pred_->GetResultValue(pred_->GetSelectionHisto("MHT_JetBin2_HTmedium"), MHTmedium, MHThigh)/pred_->GetResultValue(pred_->GetPredictionHisto("MHT_JetBin2_HTmedium"), MHTmedium, MHThigh); 
   cout << "----------------------" << endl;

   cout << "----------------------" << endl;
   cout << "HT = " << HTmedium << "-" << HThigh << endl;
   cout << "----------------------" << endl;
   cout << "MHT > " << MHThigh << endl;
   cout << "----------------------" << endl;
   cout << "Integral Selection:  " << pred_->GetResultValue(pred_->GetSelectionHisto("MHT_JetBin2_HTmedium"), MHThigh, -1) 
        << " +- " << pred_->GetResultError(pred_->GetSelectionHisto("MHT_JetBin2_HTmedium"), MHThigh, -1) << endl;
   cout << "Integral Prediction: " << pred_->GetResultValue(pred_->GetPredictionHisto("MHT_JetBin2_HTmedium"), MHThigh, -1) 
        << " +- " << pred_->GetResultError(pred_->GetPredictionHisto("MHT_JetBin2_HTmedium"), MHThigh, -1) << endl;
   cout << "Ratio Selection/Pred: " << pred_->GetResultValue(pred_->GetSelectionHisto("MHT_JetBin2_HTmedium"), MHThigh, -1)/pred_->GetResultValue(pred_->GetPredictionHisto("MHT_JetBin2_HTmedium"), MHThigh, -1); 
   cout << "----------------------" << endl;

 cout << "----------------------" << endl;
   cout << "HT > " << HThigh << endl;
   cout << "----------------------" << endl;
   cout << "MHT = " << MHTlow << "-" << MHTmedium << endl;
   cout << "----------------------" << endl;
   cout << "Integral Selection:  " << pred_->GetResultValue(pred_->GetSelectionHisto("MHT_JetBin2_HThigh"), MHTlow, MHTmedium) 
        << " +- " << pred_->GetResultError(pred_->GetSelectionHisto("MHT_JetBin2_HThigh"), MHTlow, MHTmedium) << endl;
   cout << "Integral Prediction: " << pred_->GetResultValue(pred_->GetPredictionHisto("MHT_JetBin2_HThigh"), MHTlow, MHTmedium) 
        << " +- " << pred_->GetResultError(pred_->GetPredictionHisto("MHT_JetBin2_HThigh"), MHTlow, MHTmedium) << endl;
   cout << "Ratio Selection/Pred: " << pred_->GetResultValue(pred_->GetSelectionHisto("MHT_JetBin2_HThigh"), MHTlow, MHTmedium)/pred_->GetResultValue(pred_->GetPredictionHisto("MHT_JetBin2_HThigh"), MHTlow, MHTmedium); 
   cout << "----------------------" << endl;

   cout << "----------------------" << endl;
   cout << "HT > " << HThigh << endl;
   cout << "----------------------" << endl;
   cout << "MHT = " << MHTmedium << "-" << MHThigh << endl;
   cout << "----------------------" << endl;
   cout << "Integral Selection:  " << pred_->GetResultValue(pred_->GetSelectionHisto("MHT_JetBin2_HThigh"), MHTmedium, MHThigh) 
        << " +- " << pred_->GetResultError(pred_->GetSelectionHisto("MHT_JetBin2_HThigh"), MHTmedium, MHThigh) << endl;
   cout << "Integral Prediction: " << pred_->GetResultValue(pred_->GetPredictionHisto("MHT_JetBin2_HThigh"), MHTmedium, MHThigh) 
        << " +- " << pred_->GetResultError(pred_->GetPredictionHisto("MHT_JetBin2_HThigh"), MHTmedium, MHThigh) << endl;
   cout << "Ratio Selection/Pred: " << pred_->GetResultValue(pred_->GetSelectionHisto("MHT_JetBin2_HThigh"), MHTmedium, MHThigh)/pred_->GetResultValue(pred_->GetPredictionHisto("MHT_JetBin2_HThigh"), MHTmedium, MHThigh); 
   cout << "----------------------" << endl;

   cout << "----------------------" << endl;
   cout << "HT > " << HThigh << endl;
   cout << "----------------------" << endl;
   cout << "MHT > " << MHThigh << endl;
   cout << "----------------------" << endl;
   cout << "Integral Selection:  " << pred_->GetResultValue(pred_->GetSelectionHisto("MHT_JetBin2_HThigh"), MHThigh, -1) 
        << " +- " << pred_->GetResultError(pred_->GetSelectionHisto("MHT_JetBin2_HThigh"), MHThigh, -1) << endl;
   cout << "Integral Prediction: " << pred_->GetResultValue(pred_->GetPredictionHisto("MHT_JetBin2_HThigh"), MHThigh, -1) 
        << " +- " << pred_->GetResultError(pred_->GetPredictionHisto("MHT_JetBin2_HThigh"), MHThigh, -1) << endl;
   cout << "Ratio Selection/Pred: " << pred_->GetResultValue(pred_->GetSelectionHisto("MHT_JetBin2_HThigh"), MHThigh, -1)/pred_->GetResultValue(pred_->GetPredictionHisto("MHT_JetBin2_HThigh"), MHThigh, -1); 
   cout << "----------------------" << endl;

   // third jet multiplicity bin
   cout << "----------------------" << endl;
   cout << "----------------------" << endl;
   cout << "NJets = 6 or 7" << endl;
   cout << "----------------------" << endl;
   cout << "----------------------" << endl;
   cout << "HT = " << HTlow << "-" << HTmedium << endl;
   cout << "----------------------" << endl;
   cout << "MHT = " << MHTlow << "-" << MHTmedium << endl;
   cout << "----------------------" << endl;
   cout << "Integral Selection:  " << pred_->GetResultValue(pred_->GetSelectionHisto("MHT_JetBin3_HTlow"), MHTlow, MHTmedium) 
        << " +- " << pred_->GetResultError(pred_->GetSelectionHisto("MHT_JetBin3_HTlow"), MHTlow, MHTmedium) << endl;
   cout << "Integral Prediction: " << pred_->GetResultValue(pred_->GetPredictionHisto("MHT_JetBin3_HTlow"), MHTlow, MHTmedium) 
        << " +- " << pred_->GetResultError(pred_->GetPredictionHisto("MHT_JetBin3_HTlow"), MHTlow, MHTmedium) << endl;
   cout << "Ratio Selection/Pred: " << pred_->GetResultValue(pred_->GetSelectionHisto("MHT_JetBin3_HTlow"), MHTlow, MHTmedium)/pred_->GetResultValue(pred_->GetPredictionHisto("MHT_JetBin3_HTlow"), MHTlow, MHTmedium); 
   cout << "----------------------" << endl;

   cout << "----------------------" << endl;
   cout << "HT = " << HTlow << "-" << HTmedium << endl;
   cout << "----------------------" << endl;
   cout << "MHT = " << MHTmedium << "-" << MHThigh << endl;
   cout << "----------------------" << endl;
   cout << "Integral Selection:  " << pred_->GetResultValue(pred_->GetSelectionHisto("MHT_JetBin3_HTlow"), MHTmedium, MHThigh) 
        << " +- " << pred_->GetResultError(pred_->GetSelectionHisto("MHT_JetBin3_HTlow"), MHTmedium, MHThigh) << endl;
   cout << "Integral Prediction: " << pred_->GetResultValue(pred_->GetPredictionHisto("MHT_JetBin3_HTlow"), MHTmedium, MHThigh) 
        << " +- " << pred_->GetResultError(pred_->GetPredictionHisto("MHT_JetBin3_HTlow"), MHTmedium, MHThigh) << endl;
   cout << "Ratio Selection/Pred: " << pred_->GetResultValue(pred_->GetSelectionHisto("MHT_JetBin3_HTlow"), MHTmedium, MHThigh)/pred_->GetResultValue(pred_->GetPredictionHisto("MHT_JetBin3_HTlow"), MHTmedium, MHThigh); 
   cout << "----------------------" << endl;

   cout << "----------------------" << endl;
   cout << "HT = " << HTlow << "-" << HTmedium << endl;
   cout << "----------------------" << endl;
   cout << "MHT > " << MHThigh << endl;
   cout << "----------------------" << endl;
   cout << "Integral Selection:  " << pred_->GetResultValue(pred_->GetSelectionHisto("MHT_JetBin3_HTlow"), MHThigh, -1) 
        << " +- " << pred_->GetResultError(pred_->GetSelectionHisto("MHT_JetBin3_HTlow"), MHThigh, -1) << endl;
   cout << "Integral Prediction: " << pred_->GetResultValue(pred_->GetPredictionHisto("MHT_JetBin3_HTlow"), MHThigh, -1) 
        << " +- " << pred_->GetResultError(pred_->GetPredictionHisto("MHT_JetBin3_HTlow"), MHThigh, -1) << endl;
   cout << "Ratio Selection/Pred: " << pred_->GetResultValue(pred_->GetSelectionHisto("MHT_JetBin3_HTlow"), MHThigh, -1)/pred_->GetResultValue(pred_->GetPredictionHisto("MHT_JetBin3_HTlow"), MHThigh, -1); 
   cout << "----------------------" << endl;

   cout << "----------------------" << endl;
   cout << "HT = " << HTmedium << "-" << HThigh << endl;
   cout << "----------------------" << endl;
   cout << "MHT = " << MHTlow << "-" << MHTmedium << endl;
   cout << "----------------------" << endl;
   cout << "Integral Selection:  " << pred_->GetResultValue(pred_->GetSelectionHisto("MHT_JetBin3_HTmedium"), MHTlow, MHTmedium) 
        << " +- " << pred_->GetResultError(pred_->GetSelectionHisto("MHT_JetBin3_HTmedium"), MHTlow, MHTmedium) << endl;
   cout << "Integral Prediction: " << pred_->GetResultValue(pred_->GetPredictionHisto("MHT_JetBin3_HTmedium"), MHTlow, MHTmedium) 
        << " +- " << pred_->GetResultError(pred_->GetPredictionHisto("MHT_JetBin3_HTmedium"), MHTlow, MHTmedium) << endl;
   cout << "Ratio Selection/Pred: " << pred_->GetResultValue(pred_->GetSelectionHisto("MHT_JetBin3_HTmedium"), MHTlow, MHTmedium)/pred_->GetResultValue(pred_->GetPredictionHisto("MHT_JetBin3_HTmedium"), MHTlow, MHTmedium); 
   cout << "----------------------" << endl;

   cout << "----------------------" << endl;
   cout << "HT = " << HTmedium << "-" << HThigh << endl;
   cout << "----------------------" << endl;
   cout << "MHT = " << MHTmedium << "-" << MHThigh << endl;
   cout << "----------------------" << endl;
   cout << "Integral Selection:  " << pred_->GetResultValue(pred_->GetSelectionHisto("MHT_JetBin3_HTmedium"), MHTmedium, MHThigh) 
        << " +- " << pred_->GetResultError(pred_->GetSelectionHisto("MHT_JetBin3_HTmedium"), MHTmedium, MHThigh) << endl;
   cout << "Integral Prediction: " << pred_->GetResultValue(pred_->GetPredictionHisto("MHT_JetBin3_HTmedium"), MHTmedium, MHThigh) 
        << " +- " << pred_->GetResultError(pred_->GetPredictionHisto("MHT_JetBin3_HTmedium"), MHTmedium, MHThigh) << endl;
   cout << "Ratio Selection/Pred: " << pred_->GetResultValue(pred_->GetSelectionHisto("MHT_JetBin3_HTmedium"), MHTmedium, MHThigh)/pred_->GetResultValue(pred_->GetPredictionHisto("MHT_JetBin3_HTmedium"), MHTmedium, MHThigh); 
   cout << "----------------------" << endl;

   cout << "----------------------" << endl;
   cout << "HT = " << HTmedium << "-" << HThigh << endl;
   cout << "----------------------" << endl;
   cout << "MHT > " << MHThigh << endl;
   cout << "----------------------" << endl;
   cout << "Integral Selection:  " << pred_->GetResultValue(pred_->GetSelectionHisto("MHT_JetBin3_HTmedium"), MHThigh, -1) 
        << " +- " << pred_->GetResultError(pred_->GetSelectionHisto("MHT_JetBin3_HTmedium"), MHThigh, -1) << endl;
   cout << "Integral Prediction: " << pred_->GetResultValue(pred_->GetPredictionHisto("MHT_JetBin3_HTmedium"), MHThigh, -1) 
        << " +- " << pred_->GetResultError(pred_->GetPredictionHisto("MHT_JetBin3_HTmedium"), MHThigh, -1) << endl;
   cout << "Ratio Selection/Pred: " << pred_->GetResultValue(pred_->GetSelectionHisto("MHT_JetBin3_HTmedium"), MHThigh, -1)/pred_->GetResultValue(pred_->GetPredictionHisto("MHT_JetBin3_HTmedium"), MHThigh, -1); 
   cout << "----------------------" << endl;

 cout << "----------------------" << endl;
   cout << "HT > " << HThigh << endl;
   cout << "----------------------" << endl;
   cout << "MHT = " << MHTlow << "-" << MHTmedium << endl;
   cout << "----------------------" << endl;
   cout << "Integral Selection:  " << pred_->GetResultValue(pred_->GetSelectionHisto("MHT_JetBin3_HThigh"), MHTlow, MHTmedium) 
        << " +- " << pred_->GetResultError(pred_->GetSelectionHisto("MHT_JetBin3_HThigh"), MHTlow, MHTmedium) << endl;
   cout << "Integral Prediction: " << pred_->GetResultValue(pred_->GetPredictionHisto("MHT_JetBin3_HThigh"), MHTlow, MHTmedium) 
        << " +- " << pred_->GetResultError(pred_->GetPredictionHisto("MHT_JetBin3_HThigh"), MHTlow, MHTmedium) << endl;
   cout << "Ratio Selection/Pred: " << pred_->GetResultValue(pred_->GetSelectionHisto("MHT_JetBin3_HThigh"), MHTlow, MHTmedium)/pred_->GetResultValue(pred_->GetPredictionHisto("MHT_JetBin3_HThigh"), MHTlow, MHTmedium); 
   cout << "----------------------" << endl;

   cout << "----------------------" << endl;
   cout << "HT > " << HThigh << endl;
   cout << "----------------------" << endl;
   cout << "MHT = " << MHTmedium << "-" << MHThigh << endl;
   cout << "----------------------" << endl;
   cout << "Integral Selection:  " << pred_->GetResultValue(pred_->GetSelectionHisto("MHT_JetBin3_HThigh"), MHTmedium, MHThigh) 
        << " +- " << pred_->GetResultError(pred_->GetSelectionHisto("MHT_JetBin3_HThigh"), MHTmedium, MHThigh) << endl;
   cout << "Integral Prediction: " << pred_->GetResultValue(pred_->GetPredictionHisto("MHT_JetBin3_HThigh"), MHTmedium, MHThigh) 
        << " +- " << pred_->GetResultError(pred_->GetPredictionHisto("MHT_JetBin3_HThigh"), MHTmedium, MHThigh) << endl;
   cout << "Ratio Selection/Pred: " << pred_->GetResultValue(pred_->GetSelectionHisto("MHT_JetBin3_HThigh"), MHTmedium, MHThigh)/pred_->GetResultValue(pred_->GetPredictionHisto("MHT_JetBin3_HThigh"), MHTmedium, MHThigh); 
   cout << "----------------------" << endl;

   cout << "----------------------" << endl;
   cout << "HT > " << HThigh << endl;
   cout << "----------------------" << endl;
   cout << "MHT > " << MHThigh << endl;
   cout << "----------------------" << endl;
   cout << "Integral Selection:  " << pred_->GetResultValue(pred_->GetSelectionHisto("MHT_JetBin3_HThigh"), MHThigh, -1) 
        << " +- " << pred_->GetResultError(pred_->GetSelectionHisto("MHT_JetBin3_HThigh"), MHThigh, -1) << endl;
   cout << "Integral Prediction: " << pred_->GetResultValue(pred_->GetPredictionHisto("MHT_JetBin3_HThigh"), MHThigh, -1) 
        << " +- " << pred_->GetResultError(pred_->GetPredictionHisto("MHT_JetBin3_HThigh"), MHThigh, -1) << endl;
   cout << "Ratio Selection/Pred: " << pred_->GetResultValue(pred_->GetSelectionHisto("MHT_JetBin3_HThigh"), MHThigh, -1)/pred_->GetResultValue(pred_->GetPredictionHisto("MHT_JetBin3_HThigh"), MHThigh, -1); 
   cout << "----------------------" << endl;

   // fourth jet multiplicity bin
   cout << "----------------------" << endl;
   cout << "----------------------" << endl;
   cout << "NJets >= 8" << endl;
   cout << "----------------------" << endl;
   cout << "----------------------" << endl;
   cout << "HT = " << HTlow << "-" << HTmedium << endl;
   cout << "----------------------" << endl;
   cout << "MHT = " << MHTlow << "-" << MHTmedium << endl;
   cout << "----------------------" << endl;
   cout << "Integral Selection:  " << pred_->GetResultValue(pred_->GetSelectionHisto("MHT_JetBin4_HTlow"), MHTlow, MHTmedium) 
        << " +- " << pred_->GetResultError(pred_->GetSelectionHisto("MHT_JetBin4_HTlow"), MHTlow, MHTmedium) << endl;
   cout << "Integral Prediction: " << pred_->GetResultValue(pred_->GetPredictionHisto("MHT_JetBin4_HTlow"), MHTlow, MHTmedium) 
        << " +- " << pred_->GetResultError(pred_->GetPredictionHisto("MHT_JetBin4_HTlow"), MHTlow, MHTmedium) << endl;
   cout << "Ratio Selection/Pred: " << pred_->GetResultValue(pred_->GetSelectionHisto("MHT_JetBin4_HTlow"), MHTlow, MHTmedium)/pred_->GetResultValue(pred_->GetPredictionHisto("MHT_JetBin4_HTlow"), MHTlow, MHTmedium); 
   cout << "----------------------" << endl;

   cout << "----------------------" << endl;
   cout << "HT = " << HTlow << "-" << HTmedium << endl;
   cout << "----------------------" << endl;
   cout << "MHT = " << MHTmedium << "-" << MHThigh << endl;
   cout << "----------------------" << endl;
   cout << "Integral Selection:  " << pred_->GetResultValue(pred_->GetSelectionHisto("MHT_JetBin4_HTlow"), MHTmedium, MHThigh) 
        << " +- " << pred_->GetResultError(pred_->GetSelectionHisto("MHT_JetBin4_HTlow"), MHTmedium, MHThigh) << endl;
   cout << "Integral Prediction: " << pred_->GetResultValue(pred_->GetPredictionHisto("MHT_JetBin4_HTlow"), MHTmedium, MHThigh) 
        << " +- " << pred_->GetResultError(pred_->GetPredictionHisto("MHT_JetBin4_HTlow"), MHTmedium, MHThigh) << endl;
   cout << "Ratio Selection/Pred: " << pred_->GetResultValue(pred_->GetSelectionHisto("MHT_JetBin4_HTlow"), MHTmedium, MHThigh)/pred_->GetResultValue(pred_->GetPredictionHisto("MHT_JetBin4_HTlow"), MHTmedium, MHThigh); 
   cout << "----------------------" << endl;

   cout << "----------------------" << endl;
   cout << "HT = " << HTlow << "-" << HTmedium << endl;
   cout << "----------------------" << endl;
   cout << "MHT > " << MHThigh << endl;
   cout << "----------------------" << endl;
   cout << "Integral Selection:  " << pred_->GetResultValue(pred_->GetSelectionHisto("MHT_JetBin4_HTlow"), MHThigh, -1) 
        << " +- " << pred_->GetResultError(pred_->GetSelectionHisto("MHT_JetBin4_HTlow"), MHThigh, -1) << endl;
   cout << "Integral Prediction: " << pred_->GetResultValue(pred_->GetPredictionHisto("MHT_JetBin4_HTlow"), MHThigh, -1) 
        << " +- " << pred_->GetResultError(pred_->GetPredictionHisto("MHT_JetBin4_HTlow"), MHThigh, -1) << endl;
   cout << "Ratio Selection/Pred: " << pred_->GetResultValue(pred_->GetSelectionHisto("MHT_JetBin4_HTlow"), MHThigh, -1)/pred_->GetResultValue(pred_->GetPredictionHisto("MHT_JetBin4_HTlow"), MHThigh, -1); 
   cout << "----------------------" << endl;

   cout << "----------------------" << endl;
   cout << "HT = " << HTmedium << "-" << HThigh << endl;
   cout << "----------------------" << endl;
   cout << "MHT = " << MHTlow << "-" << MHTmedium << endl;

   cout << "----------------------" << endl;
   cout << "Integral Selection:  " << pred_->GetResultValue(pred_->GetSelectionHisto("MHT_JetBin4_HTmedium"), MHTlow, MHTmedium) 
        << " +- " << pred_->GetResultError(pred_->GetSelectionHisto("MHT_JetBin4_HTmedium"), MHTlow, MHTmedium) << endl;
   cout << "Integral Prediction: " << pred_->GetResultValue(pred_->GetPredictionHisto("MHT_JetBin4_HTmedium"), MHTlow, MHTmedium) 
        << " +- " << pred_->GetResultError(pred_->GetPredictionHisto("MHT_JetBin4_HTmedium"), MHTlow, MHTmedium) << endl;
   cout << "Ratio Selection/Pred: " << pred_->GetResultValue(pred_->GetSelectionHisto("MHT_JetBin4_HTmedium"), MHTlow, MHTmedium)/pred_->GetResultValue(pred_->GetPredictionHisto("MHT_JetBin4_HTmedium"), MHTlow, MHTmedium); 
   cout << "----------------------" << endl;

   cout << "----------------------" << endl;
   cout << "HT = " << HTmedium << "-" << HThigh << endl;
   cout << "----------------------" << endl;
   cout << "MHT = " << MHTmedium << "-" << MHThigh << endl;
   cout << "----------------------" << endl;
   cout << "Integral Selection:  " << pred_->GetResultValue(pred_->GetSelectionHisto("MHT_JetBin4_HTmedium"), MHTmedium, MHThigh) 
        << " +- " << pred_->GetResultError(pred_->GetSelectionHisto("MHT_JetBin4_HTmedium"), MHTmedium, MHThigh) << endl;
   cout << "Integral Prediction: " << pred_->GetResultValue(pred_->GetPredictionHisto("MHT_JetBin4_HTmedium"), MHTmedium, MHThigh) 
        << " +- " << pred_->GetResultError(pred_->GetPredictionHisto("MHT_JetBin4_HTmedium"), MHTmedium, MHThigh) << endl;
   cout << "Ratio Selection/Pred: " << pred_->GetResultValue(pred_->GetSelectionHisto("MHT_JetBin4_HTmedium"), MHTmedium, MHThigh)/pred_->GetResultValue(pred_->GetPredictionHisto("MHT_JetBin4_HTmedium"), MHTmedium, MHThigh); 
   cout << "----------------------" << endl;

   cout << "----------------------" << endl;
   cout << "HT = " << HTmedium << "-" << HThigh << endl;
   cout << "----------------------" << endl;
   cout << "MHT > " << MHThigh << endl;
   cout << "----------------------" << endl;
   cout << "Integral Selection:  " << pred_->GetResultValue(pred_->GetSelectionHisto("MHT_JetBin4_HTmedium"), MHThigh, -1) 
        << " +- " << pred_->GetResultError(pred_->GetSelectionHisto("MHT_JetBin4_HTmedium"), MHThigh, -1) << endl;
   cout << "Integral Prediction: " << pred_->GetResultValue(pred_->GetPredictionHisto("MHT_JetBin4_HTmedium"), MHThigh, -1) 
        << " +- " << pred_->GetResultError(pred_->GetPredictionHisto("MHT_JetBin4_HTmedium"), MHThigh, -1) << endl;
   cout << "Ratio Selection/Pred: " << pred_->GetResultValue(pred_->GetSelectionHisto("MHT_JetBin4_HTmedium"), MHThigh, -1)/pred_->GetResultValue(pred_->GetPredictionHisto("MHT_JetBin4_HTmedium"), MHThigh, -1); 
   cout << "----------------------" << endl;

 cout << "----------------------" << endl;
   cout << "HT > " << HThigh << endl;
   cout << "----------------------" << endl;
   cout << "MHT = " << MHTlow << "-" << MHTmedium << endl;
   cout << "----------------------" << endl;
   cout << "Integral Selection:  " << pred_->GetResultValue(pred_->GetSelectionHisto("MHT_JetBin4_HThigh"), MHTlow, MHTmedium) 
        << " +- " << pred_->GetResultError(pred_->GetSelectionHisto("MHT_JetBin4_HThigh"), MHTlow, MHTmedium) << endl;
   cout << "Integral Prediction: " << pred_->GetResultValue(pred_->GetPredictionHisto("MHT_JetBin4_HThigh"), MHTlow, MHTmedium) 
        << " +- " << pred_->GetResultError(pred_->GetPredictionHisto("MHT_JetBin4_HThigh"), MHTlow, MHTmedium) << endl;
   cout << "Ratio Selection/Pred: " << pred_->GetResultValue(pred_->GetSelectionHisto("MHT_JetBin4_HThigh"), MHTlow, MHTmedium)/pred_->GetResultValue(pred_->GetPredictionHisto("MHT_JetBin4_HThigh"), MHTlow, MHTmedium); 
   cout << "----------------------" << endl;

   cout << "----------------------" << endl;
   cout << "HT > " << HThigh << endl;
   cout << "----------------------" << endl;
   cout << "MHT = " << MHTmedium << "-" << MHThigh << endl;
   cout << "----------------------" << endl;
   cout << "Integral Selection:  " << pred_->GetResultValue(pred_->GetSelectionHisto("MHT_JetBin4_HThigh"), MHTmedium, MHThigh) 
        << " +- " << pred_->GetResultError(pred_->GetSelectionHisto("MHT_JetBin4_HThigh"), MHTmedium, MHThigh) << endl;
   cout << "Integral Prediction: " << pred_->GetResultValue(pred_->GetPredictionHisto("MHT_JetBin4_HThigh"), MHTmedium, MHThigh) 
        << " +- " << pred_->GetResultError(pred_->GetPredictionHisto("MHT_JetBin4_HThigh"), MHTmedium, MHThigh) << endl;
   cout << "Ratio Selection/Pred: " << pred_->GetResultValue(pred_->GetSelectionHisto("MHT_JetBin4_HThigh"), MHTmedium, MHThigh)/pred_->GetResultValue(pred_->GetPredictionHisto("MHT_JetBin4_HThigh"), MHTmedium, MHThigh); 
   cout << "----------------------" << endl;

   cout << "----------------------" << endl;
   cout << "HT > " << HThigh << endl;
   cout << "----------------------" << endl;
   cout << "MHT > " << MHThigh << endl;
   cout << "----------------------" << endl;
   cout << "Integral Selection:  " << pred_->GetResultValue(pred_->GetSelectionHisto("MHT_JetBin4_HThigh"), MHThigh, -1) 
        << " +- " << pred_->GetResultError(pred_->GetSelectionHisto("MHT_JetBin4_HThigh"), MHThigh, -1) << endl;
   cout << "Integral Prediction: " << pred_->GetResultValue(pred_->GetPredictionHisto("MHT_JetBin4_HThigh"), MHThigh, -1) 
        << " +- " << pred_->GetResultError(pred_->GetPredictionHisto("MHT_JetBin4_HThigh"), MHThigh, -1) << endl;
   cout << "Ratio Selection/Pred: " << pred_->GetResultValue(pred_->GetSelectionHisto("MHT_JetBin4_HThigh"), MHThigh, -1)/pred_->GetResultValue(pred_->GetPredictionHisto("MHT_JetBin4_HThigh"), MHThigh, -1); 
   cout << "----------------------" << endl;
   */

   return 1;
}




