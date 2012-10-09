#include <TROOT.h>
#include <TSystem.h>
#include <TH1.h>
#include <TH2.h>
#include <TProfile.h>
#include <TCanvas.h>
#include <TColor.h>
#include <TChain.h>
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
#include "../../../AdditionalInputFiles/RA2PlottingStyle.h" 

using namespace std;

TCanvas* DrawComparison(TH1F* prediction, TH1F* selection, TString Title, TString LumiTitle, TString xTitle, bool isData)
{
   double MinX = selection->GetXaxis()->GetXmin();
   double MaxX = selection->GetXaxis()->GetXmax();
   double MaxY = selection->GetMaximum();
   double YRangeMax = 120.*MaxY;
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
   static Int_t c_LightGray    = TColor::GetColor( "#DDDDDD" );

   prediction->SetAxisRange(MinX, MaxX, "X");
   prediction->GetYaxis()->SetRangeUser(0.005, YRangeMax);
   prediction->SetMarkerStyle(20);
   prediction->SetMarkerSize(0.9);
   prediction->SetMarkerColor(kBlack);
   prediction->SetXTitle(xTitle);
   prediction->SetYTitle("Events");
   selection->SetAxisRange(MinX, MaxX, "X");
   selection->GetYaxis()->SetRangeUser(0.05, YRangeMax);
   // selection->SetFillColor(c_LightBrown);
   selection->SetFillColor(c_LightGray);
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
   //  selection->SetFillColor(c_LightBrown);
   selection->SetFillColor(c_LightGray);

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

   gStyle->SetHatchesLineWidth(1.2);

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

   ////////////////////////////////////////   
   // open files for MC --- pythia QCD ---- //

   TString mc_directory = "/afs/naf.desy.de/user/k/kriheine/kriheine/QCDSmearing_MCClosure_8TeV_2012_WithPUReweighting_chsJets_pt13_NJetsCorrected_v1/QCD_Pt-15to3000_TuneZ2_Flat_8TeV_pythia6/";
   // TString mc_directory = "/afs/naf.desy.de/user/k/kriheine/kriheine/QCDSmearing_MCClosure_8TeV_2012_WithPUReweighting_chsJets_pt13_WithBProbFromData_v1/QCD_Pt-15to3000_TuneZ2_Flat_8TeV_pythia6/";

   // ------------------- file with prediction
   /* TChain* prediction = new TChain("QCDfromSmearing/QCDPrediction");
	prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_0.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_1.root");
	prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_2.root");
	prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_3.root");
	prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_4.root");
	prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_5.root");
	prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_6.root");
	prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_7.root");
	prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_8.root");
	prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_9.root");
	prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_10.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_11.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_12.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_13.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_14.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_15.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_16.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_17.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_18.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_19.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_20.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_21.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_22.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_23.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_24.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_25.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_26.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_27.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_28.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_29.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_30.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_31.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_32.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_33.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_34.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_35.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_36.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_37.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_38.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_39.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_40.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_41.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_42.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_43.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_44.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_45.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_46.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_47.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_48.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_49.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_50.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_51.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_52.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_53.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_54.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_55.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_56.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_57.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_58.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_59.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_60.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_61.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_62.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_63.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_64.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_65.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_66.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_67.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_68.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_69.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_70.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_71.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_72.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_73.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_74.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_75.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_76.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_77.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_78.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_79.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_80.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_81.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_82.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_83.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_84.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_85.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_86.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_87.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_88.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_89.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_90.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_91.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_92.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_93.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_94.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_95.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_96.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_97.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_98.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_99.root");
	prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_100.root");
	prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_101.root");
	prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_102.root");
	prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_103.root");
	prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_104.root");
	prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_105.root");
	prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_106.root");
	prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_107.root");
	prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_108.root");
	prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_109.root");
	prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_110.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_111.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_112.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_113.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_114.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_115.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_116.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_117.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_118.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_119.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_120.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_121.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_122.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_123.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_124.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_125.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_126.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_127.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_128.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_129.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_130.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_131.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_132.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_133.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_134.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_135.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_136.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_137.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_138.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_139.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_140.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_141.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_142.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_143.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_144.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_145.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_146.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_147.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_148.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_149.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_150.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_151.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_152.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_153.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_154.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_155.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_156.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_157.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_158.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_159.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_160.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_161.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_162.root");
   prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_163.root");
   //  prediction->Add(mc_directory + "QCDSmearingClosure_OnMC_164.root");
  
   // ------------------- event selection
   TChain* selection = new TChain("RA2TreeMaker/RA2PreSelection");
	selection->Add(mc_directory + "QCDSmearingClosure_OnMC_0.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_1.root");
	selection->Add(mc_directory + "QCDSmearingClosure_OnMC_2.root");
	selection->Add(mc_directory + "QCDSmearingClosure_OnMC_3.root");
	selection->Add(mc_directory + "QCDSmearingClosure_OnMC_4.root");
	selection->Add(mc_directory + "QCDSmearingClosure_OnMC_5.root");
	selection->Add(mc_directory + "QCDSmearingClosure_OnMC_6.root");
	selection->Add(mc_directory + "QCDSmearingClosure_OnMC_7.root");
	selection->Add(mc_directory + "QCDSmearingClosure_OnMC_8.root");
	selection->Add(mc_directory + "QCDSmearingClosure_OnMC_9.root");
	selection->Add(mc_directory + "QCDSmearingClosure_OnMC_10.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_11.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_12.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_13.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_14.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_15.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_16.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_17.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_18.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_19.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_20.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_21.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_22.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_23.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_24.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_25.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_26.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_27.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_28.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_29.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_30.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_31.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_32.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_33.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_34.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_35.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_36.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_37.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_38.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_39.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_40.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_41.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_42.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_43.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_44.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_45.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_46.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_47.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_48.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_49.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_50.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_51.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_52.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_53.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_54.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_55.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_56.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_57.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_58.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_59.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_60.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_61.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_62.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_63.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_64.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_65.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_66.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_67.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_68.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_69.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_70.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_71.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_72.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_73.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_74.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_75.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_76.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_77.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_78.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_79.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_80.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_81.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_82.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_83.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_84.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_85.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_86.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_87.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_88.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_89.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_90.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_91.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_92.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_93.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_94.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_95.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_96.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_97.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_98.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_99.root");
	selection->Add(mc_directory + "QCDSmearingClosure_OnMC_100.root");
	selection->Add(mc_directory + "QCDSmearingClosure_OnMC_101.root");
	selection->Add(mc_directory + "QCDSmearingClosure_OnMC_102.root");
	selection->Add(mc_directory + "QCDSmearingClosure_OnMC_103.root");
	selection->Add(mc_directory + "QCDSmearingClosure_OnMC_104.root");
	selection->Add(mc_directory + "QCDSmearingClosure_OnMC_105.root");
	selection->Add(mc_directory + "QCDSmearingClosure_OnMC_106.root");
	selection->Add(mc_directory + "QCDSmearingClosure_OnMC_107.root");
	selection->Add(mc_directory + "QCDSmearingClosure_OnMC_108.root");
	selection->Add(mc_directory + "QCDSmearingClosure_OnMC_109.root");
	selection->Add(mc_directory + "QCDSmearingClosure_OnMC_110.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_111.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_112.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_113.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_114.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_115.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_116.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_117.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_118.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_119.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_120.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_121.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_122.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_123.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_124.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_125.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_126.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_127.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_128.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_129.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_130.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_131.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_132.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_133.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_134.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_135.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_136.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_137.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_138.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_139.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_140.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_141.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_142.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_143.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_144.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_145.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_146.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_147.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_148.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_149.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_150.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_151.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_152.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_153.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_154.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_155.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_156.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_157.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_158.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_159.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_160.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_161.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_162.root");
   selection->Add(mc_directory + "QCDSmearingClosure_OnMC_163.root");*/
   // selection->Add(mc_directory + "QCDSmearingClosure_OnMC_164.root");

   // -------- madgraph QCD --------------------------------------------- //

   //  TString mc_directory_mad1 = "/afs/naf.desy.de/user/k/kriheine/kriheine/QCDSmearing_MCClosure_8TeV_2012_WithoutPUReweighting_chsJets_pt13_madgraph_HT250-500_v1/QCD_HT-250To500_TuneZ2star_8TeV_madgraph_pythia6/";
   // TString mc_directory_mad2 = "/afs/naf.desy.de/user/k/kriheine/kriheine/QCDSmearing_MCClosure_8TeV_2012_WithoutPUReweighting_chsJets_pt13_madgraph_HT500-1000_v2/QCD_HT-500To1000_TuneZ2star_8TeV_madgraph_pythia6/";
   // TString mc_directory_mad3 = "/afs/naf.desy.de/user/k/kriheine/kriheine/QCDSmearing_MCClosure_8TeV_2012_WithoutPUReweighting_chsJets_pt13_madgraph_HT1000-inf_v1/QCD_HT-1000ToInf_TuneZ2star_8TeV_madgraph_pythia6/";

   TString mc_directory_mad1 = "/afs/naf.desy.de/user/k/kriheine/kriheine/QCDSmearing_MCClosure_8TeV_2012_WithoutPUReweighting_chsJets_pt13_madgraph_HT250-500_PythiaResolutions_withBProb_v1/QCD_HT-250To500_TuneZ2star_8TeV_madgraph_pythia6/";
   TString mc_directory_mad2 = "/afs/naf.desy.de/user/k/kriheine/kriheine/QCDSmearing_MCClosure_8TeV_2012_WithoutPUReweighting_chsJets_pt13_madgraph_HT500-1000_PythiaResolutions_withBProb_v1/QCD_HT-500To1000_TuneZ2star_8TeV_madgraph_pythia6/";
   TString mc_directory_mad3 = "/afs/naf.desy.de/user/k/kriheine/kriheine/QCDSmearing_MCClosure_8TeV_2012_WithoutPUReweighting_chsJets_pt13_madgraph_HT1000-inf_PythiaResolutions_withBProb_v1/QCD_HT-1000ToInf_TuneZ2star_8TeV_madgraph_pythia6/";

   // ------------------- file with prediction
   TChain* prediction = new TChain("QCDfromSmearing/QCDPrediction");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_0.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_1.root");
	prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_2.root");
	prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_3.root");
	prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_4.root");
	prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_5.root");
	prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_6.root");
	prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_7.root");
	prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_8.root");
	prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_9.root");
	prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_10.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_11.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_12.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_13.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_14.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_15.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_16.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_17.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_18.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_19.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_20.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_21.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_22.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_23.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_24.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_25.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_26.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_27.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_28.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_29.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_30.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_31.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_32.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_33.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_34.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_35.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_36.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_37.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_38.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_39.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_40.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_41.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_42.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_43.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_44.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_45.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_46.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_47.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_48.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_49.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_50.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_51.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_52.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_53.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_54.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_55.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_56.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_57.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_58.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_59.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_60.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_61.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_62.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_63.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_64.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_65.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_66.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_67.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_68.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_69.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_70.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_71.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_72.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_73.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_74.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_75.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_76.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_77.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_78.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_79.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_80.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_81.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_82.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_83.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_84.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_85.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_86.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_87.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_88.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_89.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_90.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_91.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_92.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_93.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_94.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_95.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_96.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_97.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_98.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_99.root");
	prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_100.root");
	prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_101.root");
	prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_102.root");
	prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_103.root");
	prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_104.root");
	prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_105.root");
	prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_106.root");
	prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_107.root");
	prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_108.root");
	prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_109.root");
	prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_110.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_111.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_112.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_113.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_114.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_115.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_116.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_117.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_118.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_119.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_120.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_121.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_122.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_123.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_124.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_125.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_126.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_127.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_128.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_129.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_130.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_131.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_132.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_133.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_134.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_135.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_136.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_137.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_138.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_139.root");
   prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_140.root");
   //  prediction->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_141.root");
	prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_0.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_1.root");
	prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_2.root");
	prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_3.root");
	prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_4.root");
	prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_5.root");
	prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_6.root");
	prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_7.root");
	prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_8.root");
	prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_9.root");
	prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_10.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_11.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_12.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_13.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_14.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_15.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_16.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_17.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_18.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_19.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_20.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_21.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_22.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_23.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_24.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_25.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_26.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_27.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_28.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_29.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_30.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_31.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_32.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_33.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_34.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_35.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_36.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_37.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_38.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_39.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_40.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_41.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_42.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_43.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_44.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_45.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_46.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_47.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_48.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_49.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_50.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_51.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_52.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_53.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_54.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_55.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_56.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_57.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_58.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_59.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_60.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_61.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_62.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_63.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_64.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_65.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_66.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_67.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_68.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_69.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_70.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_71.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_72.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_73.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_74.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_75.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_76.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_77.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_78.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_79.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_80.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_81.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_82.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_83.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_84.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_85.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_86.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_87.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_88.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_89.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_90.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_91.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_92.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_93.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_94.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_95.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_96.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_97.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_98.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_99.root");
	prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_100.root");
	prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_101.root");
	prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_102.root");
	prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_103.root");
	prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_104.root");
	prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_105.root");
	prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_106.root");
	prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_107.root");
	prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_108.root");
	prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_109.root");
	prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_110.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_111.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_112.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_113.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_114.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_115.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_116.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_117.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_118.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_119.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_120.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_121.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_122.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_123.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_124.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_125.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_126.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_127.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_128.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_129.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_130.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_131.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_132.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_133.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_134.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_135.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_136.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_137.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_138.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_139.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_140.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_141.root");
	prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_142.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_143.root");
	prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_144.root");
	prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_145.root");
	prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_146.root");
	prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_147.root");
	prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_148.root");
	prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_149.root");
	prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_150.root");
	prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_151.root");
	prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_152.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_153.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_154.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_155.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_156.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_157.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_158.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_159.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_160.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_161.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_162.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_163.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_164.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_165.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_166.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_167.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_168.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_169.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_170.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_171.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_172.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_173.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_174.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_175.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_176.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_177.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_178.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_179.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_180.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_181.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_182.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_183.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_184.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_185.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_186.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_187.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_188.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_189.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_190.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_191.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_192.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_193.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_194.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_195.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_196.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_197.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_198.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_199.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_200.root");
	prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_201.root");
	prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_202.root");
	prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_203.root");
	prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_204.root");
	prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_205.root");
	prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_206.root");
	prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_207.root");
	prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_208.root");
	prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_209.root");
	prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_210.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_211.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_212.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_213.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_214.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_215.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_216.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_217.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_218.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_219.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_220.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_221.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_222.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_223.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_224.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_225.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_226.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_227.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_228.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_229.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_230.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_231.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_232.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_233.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_234.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_235.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_236.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_237.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_238.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_239.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_240.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_241.root");
	prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_242.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_243.root");
	prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_244.root");
	prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_245.root");
	prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_246.root");
	prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_247.root");
	prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_248.root");
	prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_249.root");
	prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_250.root");
	prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_251.root");
	prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_252.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_253.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_254.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_255.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_256.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_257.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_258.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_259.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_260.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_261.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_262.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_263.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_264.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_265.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_266.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_267.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_268.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_269.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_270.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_271.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_272.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_273.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_274.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_275.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_276.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_277.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_278.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_279.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_280.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_281.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_282.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_283.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_284.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_285.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_286.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_287.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_288.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_289.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_290.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_291.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_292.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_293.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_294.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_295.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_296.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_297.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_298.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_299.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_300.root");
	prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_301.root");
	prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_302.root");
	prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_303.root");
	prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_304.root");
	prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_305.root");
	prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_306.root");
	prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_307.root");
	prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_308.root");
	prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_309.root");
	prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_310.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_311.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_312.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_313.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_314.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_315.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_316.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_317.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_318.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_319.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_320.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_321.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_322.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_323.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_324.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_325.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_326.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_327.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_328.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_329.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_330.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_331.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_332.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_333.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_334.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_335.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_336.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_337.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_338.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_339.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_340.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_341.root");
	prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_342.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_343.root");
	prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_344.root");
	prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_345.root");
	prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_346.root");
	prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_347.root");
	prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_348.root");
	prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_349.root");
	prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_350.root");
	prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_351.root");
	prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_352.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_353.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_354.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_355.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_356.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_357.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_358.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_359.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_360.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_361.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_362.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_363.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_364.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_365.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_366.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_367.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_368.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_369.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_370.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_371.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_372.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_373.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_374.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_375.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_376.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_377.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_378.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_379.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_380.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_381.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_382.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_383.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_384.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_385.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_386.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_387.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_388.root");
   prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_389.root");
   //  prediction->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_390.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_0.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_1.root");
	prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_2.root");
	prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_3.root");
	prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_4.root");
	prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_5.root");
	prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_6.root");
	prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_7.root");
	prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_8.root");
	prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_9.root");
	prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_10.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_11.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_12.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_13.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_14.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_15.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_16.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_17.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_18.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_19.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_20.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_21.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_22.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_23.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_24.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_25.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_26.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_27.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_28.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_29.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_30.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_31.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_32.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_33.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_34.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_35.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_36.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_37.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_38.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_39.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_40.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_41.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_42.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_43.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_44.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_45.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_46.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_47.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_48.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_49.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_50.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_51.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_52.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_53.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_54.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_55.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_56.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_57.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_58.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_59.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_60.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_61.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_62.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_63.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_64.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_65.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_66.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_67.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_68.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_69.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_70.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_71.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_72.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_73.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_74.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_75.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_76.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_77.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_78.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_79.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_80.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_81.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_82.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_83.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_84.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_85.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_86.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_87.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_88.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_89.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_90.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_91.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_92.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_93.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_94.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_95.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_96.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_97.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_98.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_99.root");
	prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_100.root");
	prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_101.root");
	prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_102.root");
	prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_103.root");
	prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_104.root");
	prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_105.root");
	prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_106.root");
	prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_107.root");
	prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_108.root");
	prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_109.root");
	prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_110.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_111.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_112.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_113.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_114.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_115.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_116.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_117.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_118.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_119.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_120.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_121.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_122.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_123.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_124.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_125.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_126.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_127.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_128.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_129.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_130.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_131.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_132.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_133.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_134.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_135.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_136.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_137.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_138.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_139.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_140.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_141.root");
	prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_142.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_143.root");
	prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_144.root");
	prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_145.root");
	prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_146.root");
	prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_147.root");
	prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_148.root");
	prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_149.root");
	prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_150.root");
	prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_151.root");
	prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_152.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_153.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_154.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_155.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_156.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_157.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_158.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_159.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_160.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_161.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_162.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_163.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_164.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_165.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_166.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_167.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_168.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_169.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_170.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_171.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_172.root");
   prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_173.root");
   //  prediction->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_174.root");
    
   // ------------------- event selection
   TChain* selection = new TChain("RA2TreeMaker/RA2PreSelection");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_0.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_1.root");
	selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_2.root");
	selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_3.root");
	selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_4.root");
	selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_5.root");
	selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_6.root");
	selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_7.root");
	selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_8.root");
	selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_9.root");
	selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_10.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_11.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_12.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_13.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_14.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_15.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_16.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_17.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_18.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_19.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_20.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_21.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_22.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_23.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_24.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_25.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_26.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_27.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_28.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_29.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_30.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_31.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_32.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_33.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_34.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_35.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_36.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_37.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_38.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_39.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_40.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_41.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_42.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_43.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_44.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_45.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_46.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_47.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_48.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_49.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_50.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_51.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_52.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_53.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_54.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_55.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_56.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_57.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_58.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_59.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_60.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_61.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_62.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_63.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_64.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_65.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_66.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_67.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_68.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_69.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_70.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_71.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_72.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_73.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_74.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_75.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_76.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_77.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_78.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_79.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_80.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_81.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_82.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_83.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_84.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_85.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_86.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_87.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_88.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_89.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_90.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_91.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_92.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_93.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_94.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_95.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_96.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_97.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_98.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_99.root");
	selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_100.root");
	selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_101.root");
	selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_102.root");
	selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_103.root");
	selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_104.root");
	selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_105.root");
	selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_106.root");
	selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_107.root");
	selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_108.root");
	selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_109.root");
	selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_110.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_111.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_112.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_113.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_114.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_115.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_116.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_117.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_118.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_119.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_120.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_121.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_122.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_123.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_124.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_125.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_126.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_127.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_128.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_129.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_130.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_131.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_132.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_133.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_134.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_135.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_136.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_137.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_138.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_139.root");
   selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_140.root");
   // selection->Add(mc_directory_mad1 + "QCDSmearingClosure_OnMC_141.root");
	selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_0.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_1.root");
	selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_2.root");
	selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_3.root");
	selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_4.root");
	selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_5.root");
	selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_6.root");
	selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_7.root");
	selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_8.root");
	selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_9.root");
	selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_10.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_11.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_12.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_13.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_14.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_15.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_16.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_17.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_18.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_19.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_20.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_21.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_22.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_23.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_24.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_25.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_26.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_27.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_28.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_29.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_30.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_31.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_32.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_33.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_34.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_35.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_36.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_37.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_38.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_39.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_40.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_41.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_42.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_43.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_44.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_45.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_46.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_47.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_48.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_49.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_50.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_51.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_52.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_53.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_54.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_55.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_56.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_57.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_58.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_59.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_60.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_61.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_62.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_63.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_64.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_65.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_66.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_67.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_68.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_69.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_70.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_71.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_72.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_73.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_74.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_75.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_76.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_77.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_78.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_79.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_80.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_81.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_82.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_83.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_84.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_85.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_86.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_87.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_88.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_89.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_90.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_91.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_92.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_93.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_94.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_95.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_96.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_97.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_98.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_99.root");
	selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_100.root");
	selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_101.root");
	selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_102.root");
	selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_103.root");
	selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_104.root");
	selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_105.root");
	selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_106.root");
	selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_107.root");
	selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_108.root");
	selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_109.root");
	selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_110.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_111.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_112.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_113.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_114.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_115.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_116.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_117.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_118.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_119.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_120.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_121.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_122.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_123.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_124.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_125.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_126.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_127.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_128.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_129.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_130.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_131.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_132.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_133.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_134.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_135.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_136.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_137.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_138.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_139.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_140.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_141.root");
	selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_142.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_143.root");
	selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_144.root");
	selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_145.root");
	selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_146.root");
	selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_147.root");
	selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_148.root");
	selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_149.root");
	selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_150.root");
	selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_151.root");
	selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_152.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_153.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_154.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_155.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_156.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_157.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_158.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_159.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_160.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_161.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_162.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_163.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_164.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_165.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_166.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_167.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_168.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_169.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_170.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_171.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_172.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_173.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_174.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_175.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_176.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_177.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_178.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_179.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_180.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_181.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_182.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_183.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_184.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_185.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_186.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_187.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_188.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_189.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_190.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_191.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_192.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_193.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_194.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_195.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_196.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_197.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_198.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_199.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_200.root");
	selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_201.root");
	selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_202.root");
	selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_203.root");
	selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_204.root");
	selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_205.root");
	selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_206.root");
	selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_207.root");
	selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_208.root");
	selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_209.root");
	selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_210.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_211.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_212.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_213.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_214.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_215.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_216.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_217.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_218.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_219.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_220.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_221.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_222.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_223.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_224.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_225.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_226.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_227.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_228.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_229.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_230.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_231.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_232.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_233.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_234.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_235.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_236.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_237.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_238.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_239.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_240.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_241.root");
	selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_242.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_243.root");
	selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_244.root");
	selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_245.root");
	selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_246.root");
	selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_247.root");
	selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_248.root");
	selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_249.root");
	selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_250.root");
	selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_251.root");
	selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_252.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_253.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_254.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_255.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_256.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_257.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_258.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_259.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_260.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_261.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_262.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_263.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_264.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_265.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_266.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_267.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_268.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_269.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_270.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_271.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_272.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_273.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_274.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_275.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_276.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_277.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_278.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_279.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_280.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_281.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_282.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_283.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_284.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_285.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_286.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_287.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_288.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_289.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_290.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_291.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_292.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_293.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_294.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_295.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_296.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_297.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_298.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_299.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_300.root");
	selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_301.root");
	selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_302.root");
	selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_303.root");
	selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_304.root");
	selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_305.root");
	selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_306.root");
	selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_307.root");
	selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_308.root");
	selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_309.root");
	selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_310.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_311.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_312.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_313.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_314.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_315.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_316.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_317.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_318.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_319.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_320.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_321.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_322.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_323.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_324.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_325.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_326.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_327.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_328.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_329.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_330.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_331.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_332.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_333.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_334.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_335.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_336.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_337.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_338.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_339.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_340.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_341.root");
	selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_342.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_343.root");
	selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_344.root");
	selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_345.root");
	selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_346.root");
	selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_347.root");
	selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_348.root");
	selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_349.root");
	selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_350.root");
	selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_351.root");
	selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_352.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_353.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_354.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_355.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_356.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_357.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_358.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_359.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_360.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_361.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_362.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_363.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_364.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_365.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_366.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_367.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_368.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_369.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_370.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_371.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_372.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_373.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_374.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_375.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_376.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_377.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_378.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_379.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_380.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_381.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_382.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_383.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_384.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_385.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_386.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_387.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_388.root");
   selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_389.root");
   //  selection->Add(mc_directory_mad2 + "QCDSmearingClosure_OnMC_390.root");
	selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_0.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_1.root");
	selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_2.root");
	selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_3.root");
	selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_4.root");
	selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_5.root");
	selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_6.root");
	selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_7.root");
	selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_8.root");
	selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_9.root");
	selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_10.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_11.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_12.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_13.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_14.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_15.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_16.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_17.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_18.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_19.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_20.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_21.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_22.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_23.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_24.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_25.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_26.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_27.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_28.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_29.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_30.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_31.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_32.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_33.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_34.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_35.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_36.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_37.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_38.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_39.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_40.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_41.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_42.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_43.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_44.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_45.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_46.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_47.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_48.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_49.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_50.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_51.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_52.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_53.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_54.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_55.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_56.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_57.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_58.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_59.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_60.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_61.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_62.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_63.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_64.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_65.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_66.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_67.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_68.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_69.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_70.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_71.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_72.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_73.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_74.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_75.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_76.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_77.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_78.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_79.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_80.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_81.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_82.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_83.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_84.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_85.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_86.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_87.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_88.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_89.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_90.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_91.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_92.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_93.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_94.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_95.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_96.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_97.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_98.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_99.root");
	selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_100.root");
	selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_101.root");
	selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_102.root");
	selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_103.root");
	selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_104.root");
	selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_105.root");
	selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_106.root");
	selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_107.root");
	selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_108.root");
	selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_109.root");
	selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_110.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_111.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_112.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_113.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_114.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_115.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_116.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_117.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_118.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_119.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_120.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_121.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_122.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_123.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_124.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_125.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_126.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_127.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_128.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_129.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_130.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_131.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_132.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_133.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_134.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_135.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_136.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_137.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_138.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_139.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_140.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_141.root");
	selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_142.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_143.root");
	selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_144.root");
	selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_145.root");
	selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_146.root");
	selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_147.root");
	selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_148.root");
	selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_149.root");
	selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_150.root");
	selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_151.root");
	selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_152.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_153.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_154.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_155.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_156.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_157.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_158.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_159.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_160.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_161.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_162.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_163.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_164.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_165.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_166.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_167.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_168.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_169.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_170.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_171.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_172.root");
   selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_173.root");
   // selection->Add(mc_directory_mad3 + "QCDSmearingClosure_OnMC_174.root");
  

   // ------------------------------------------------------------------- //
     
   // initialize new Prediction object
   Prediction *pred_;
   pred_ = new Prediction(*prediction, *selection);
   bool isData = false;
  
   TString LumiTitle;
   if( isData ) LumiTitle = "CMS preliminary, L = 5.1 fb^{  -1}, #sqrt{s} = 8 TeV";
   //else LumiTitle = "CMS Simulation, #sqrt{s} = 8 TeV";
   else LumiTitle = "CMS work in progress, #sqrt{s} = 8 TeV";

   // TString postfix = "_genJets_withChsJets_withPUReweighting";
   //TString postfix = "_genJets_withStandardJets_withoutPUReweighting";
   //TString postfix = "_chsJets_withPUReweighting_pt13";
   //TString postfix = "_chsJets_withPUReweighting_WithBProbFromData_pt13";
   // TString postfix = "_chsJets_withoutPUReweighting_madgraph_pt13";
   TString postfix = "_chsJets_withoutPUReweighting_madgraph_PythiaResolutions_withBProb_pt13";
   //TString postfix = "_chsJets_withoutPUReweighting_madgraph_HT500-1000_exclusive_pt13";
   //TString postfix = "_chsJets_withPUReweighting_pt15";
   //TString postfix = "_standardJets_withoutPUReweighting_pt15";
   // TString postfix = "_standardJets_withoutPUReweighting_pt18";
   // TString postfix = "_test";

   vector<TString> xTitle_presel;
   xTitle_presel.push_back("H_{T} (GeV)");
   xTitle_presel.push_back("#slash{H}_{T} (GeV)");
   xTitle_presel.push_back("Jet1 p_{T} (GeV)");
   xTitle_presel.push_back("Jet2 p_{T} (GeV)");
   xTitle_presel.push_back("Jet1 #eta");
   xTitle_presel.push_back("Jet2 #eta");

   vector<TString> xTitle_deltaPhi;
   xTitle_deltaPhi.push_back("H_{T} (GeV)");
   xTitle_deltaPhi.push_back("#slash{H}_{T} (GeV)");
   xTitle_deltaPhi.push_back("Jet1 p_{T} (GeV)");
   xTitle_deltaPhi.push_back("Jet2 p_{T} (GeV)");
   xTitle_deltaPhi.push_back("Jet1 #eta");
   xTitle_deltaPhi.push_back("Jet2 #eta");

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
   hist_type_presel.push_back("Jet1Eta_presel");
   hist_type_presel.push_back("Jet2Eta_presel");

   vector<TString> hist_type_deltaPhi;
   hist_type_deltaPhi.push_back("HT_deltaPhi");
   hist_type_deltaPhi.push_back("MHT_deltaPhi");    
   hist_type_deltaPhi.push_back("Jet1Pt_deltaPhi"); 
   hist_type_deltaPhi.push_back("Jet2Pt_deltaPhi"); 
   hist_type_deltaPhi.push_back("Jet1Eta_deltaPhi");
   hist_type_deltaPhi.push_back("Jet2Eta_deltaPhi");
  
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
   Title = ">= 2 jets";

   if( hist_type_presel.size() != xTitle_presel.size() ) cout << "Error: Missing xTitles preselection!!" << endl;

   for(int i = 0; i < hist_type_presel.size(); i++ ) {
      TCanvas *c = DrawComparison( pred_->GetPredictionHisto(hist_type_presel.at(i)), pred_->GetSelectionHisto(hist_type_presel.at(i)), Title, LumiTitle, xTitle_presel.at(i), isData); 

      if      ( i == 0) c->Print("outpout_GetPrediction/QCD_presel" + postfix + ".ps(");
      else if ( i == hist_type_presel.size()-1 ) c->Print("outpout_GetPrediction/QCD_presel" + postfix + ".ps)");
      else c->Print("outpout_GetPrediction/QCD_presel" + postfix + ".ps");

      c->Print("outpout_GetPrediction/" + hist_type_presel.at(i) + postfix + ".png");
   }

   // plots for deltaPhi 
   Title = ">= 2 jets, #Delta#phi(#slash{H}_{T}, jet1-2,3)";

   if( hist_type_deltaPhi.size() != xTitle_deltaPhi.size() ) cout << "Error: Missing xTitles preselection!!" << endl;

   for(int i = 0; i < hist_type_deltaPhi.size(); i++ ) {
      TCanvas *c = DrawComparison( pred_->GetPredictionHisto(hist_type_deltaPhi.at(i)), pred_->GetSelectionHisto(hist_type_deltaPhi.at(i)), Title, LumiTitle, xTitle_deltaPhi.at(i), isData); 

      if      ( i == 0) c->Print("outpout_GetPrediction/QCD_deltaPhi" + postfix + ".ps(");
      else if ( i == hist_type_deltaPhi.size()-1 ) c->Print("outpout_GetPrediction/QCD_deltaPhi" + postfix + ".ps)");
      else c->Print("outpout_GetPrediction/QCD_deltaPhi" + postfix + ".ps");

      c->Print("outpout_GetPrediction/" + hist_type_deltaPhi.at(i) + postfix + ".png");
   }

   // plots for search bins 
   //jet Bin 1
   Title = "2 jets, #Delta#phi cut, HT = 500 - 900 GeV";
   TCanvas *c = DrawComparison( pred_->GetPredictionHisto("MHT_JetBin1_HTlow"), pred_->GetSelectionHisto("MHT_JetBin1_HTlow"), Title, LumiTitle,"#slash{H}_{T} (GeV)", isData); 
   c->Print("outpout_GetPrediction/QCD_searchBins" + postfix + ".ps(");
   c->Print("outpout_GetPrediction/MHT_JetBin1_HTlow" + postfix + ".png");

   Title = "2 jets, #Delta#phi cut, HT = 900 - 1300 GeV";
   c =  DrawComparison( pred_->GetPredictionHisto("MHT_JetBin1_HTmedium"), pred_->GetSelectionHisto("MHT_JetBin1_HTmedium"), Title, LumiTitle,"#slash{H}_{T} (GeV)", isData);
   c->Print("outpout_GetPrediction/QCD_searchBins" + postfix + ".ps");
   c->Print("outpout_GetPrediction/MHT_JetBin1_HTmedium" + postfix + ".png");

   Title = "2 jets, #Delta#phi cut, HT >= 1300 GeV";
   c =  DrawComparison( pred_->GetPredictionHisto("MHT_JetBin1_HThigh"), pred_->GetSelectionHisto("MHT_JetBin1_HThigh"), Title, LumiTitle,"#slash{H}_{T} (GeV)", isData); 
   c->Print("outpout_GetPrediction/QCD_searchBins" + postfix + ".ps");
   c->Print("outpout_GetPrediction/MHT_JetBin1_HThigh" + postfix + ".png");

   // jet Bin2
   Title = "3 - 5 jets, #Delta#phi cut, HT = 500 - 900 GeV";
   c = DrawComparison( pred_->GetPredictionHisto("MHT_JetBin2_HTlow"), pred_->GetSelectionHisto("MHT_JetBin2_HTlow"), Title, LumiTitle,"#slash{H}_{T} (GeV)", isData); 
   c->Print("outpout_GetPrediction/QCD_searchBins" + postfix + ".ps");
   c->Print("outpout_GetPrediction/MHT_JetBin2_HTlow" + postfix + ".png");

   Title = "3 - 5 jets, #Delta#phi cut, HT = 900 - 1300 GeV";
   c =  DrawComparison( pred_->GetPredictionHisto("MHT_JetBin2_HTmedium"), pred_->GetSelectionHisto("MHT_JetBin2_HTmedium"), Title, LumiTitle,"#slash{H}_{T} (GeV)", isData);
   c->Print("outpout_GetPrediction/QCD_searchBins" + postfix + ".ps");
   c->Print("outpout_GetPrediction/MHT_JetBin2_HTmedium" + postfix + ".png");

   Title = "3 - 5 jets, #Delta#phi cut, HT >= 1300 GeV";
   c =  DrawComparison( pred_->GetPredictionHisto("MHT_JetBin2_HThigh"), pred_->GetSelectionHisto("MHT_JetBin2_HThigh"), Title, LumiTitle,"#slash{H}_{T} (GeV)", isData);
   c->Print("outpout_GetPrediction/QCD_searchBins" + postfix + ".ps");
   c->Print("outpout_GetPrediction/MHT_JetBin2_HThigh" + postfix + ".png");

   // jet Bin3
   Title = "6 - 7 jets, #Delta#phi cut, HT = 500 - 900 GeV";
   c = DrawComparison( pred_->GetPredictionHisto("MHT_JetBin3_HTlow"), pred_->GetSelectionHisto("MHT_JetBin3_HTlow"), Title, LumiTitle,"#slash{H}_{T} (GeV)", isData); 
   c->Print("outpout_GetPrediction/QCD_searchBins" + postfix + ".ps");
   c->Print("outpout_GetPrediction/MHT_JetBin3_HTlow" + postfix + ".png");

   Title = "6 - 7 jets, #Delta#phi cut, HT = 900 - 1300 GeV";
   c =  DrawComparison( pred_->GetPredictionHisto("MHT_JetBin3_HTmedium"), pred_->GetSelectionHisto("MHT_JetBin3_HTmedium"), Title, LumiTitle,"#slash{H}_{T} (GeV)", isData);
   c->Print("outpout_GetPrediction/QCD_searchBins" + postfix + ".ps");
   c->Print("outpout_GetPrediction/MHT_JetBin3_HTmedium" + postfix + ".png");

   Title = "6 - 7 jets, #Delta#phi cut, HT >= 1300 GeV";
   c =  DrawComparison( pred_->GetPredictionHisto("MHT_JetBin3_HThigh"), pred_->GetSelectionHisto("MHT_JetBin3_HThigh"), Title, LumiTitle,"#slash{H}_{T} (GeV)", isData);
   c->Print("outpout_GetPrediction/QCD_searchBins" + postfix + ".ps");
   c->Print("outpout_GetPrediction/MHT_JetBin3_HThigh" + postfix + ".png");

   // jet Bin 4
   Title = ">= 8 jets, #Delta#phi cut, HT = 500 - 900 GeV";
   c = DrawComparison( pred_->GetPredictionHisto("MHT_JetBin4_HTlow"), pred_->GetSelectionHisto("MHT_JetBin4_HTlow"), Title, LumiTitle,"#slash{H}_{T} (GeV)", isData); 
   c->Print("outpout_GetPrediction/QCD_searchBins" + postfix + ".ps");
   c->Print("outpout_GetPrediction/MHT_JetBin4_HTlow" + postfix + ".png");

   Title = ">= 8 jets, #Delta#phi cut, HT = 900 - 1300 GeV";
   c =  DrawComparison( pred_->GetPredictionHisto("MHT_JetBin4_HTmedium"), pred_->GetSelectionHisto("MHT_JetBin4_HTmedium"), Title, LumiTitle,"#slash{H}_{T} (GeV)", isData);
   c->Print("outpout_GetPrediction/QCD_searchBins" + postfix + ".ps");
   c->Print("outpout_GetPrediction/MHT_JetBin4_HTmedium" + postfix + ".png");
  
   Title = ">= 8 jets, #Delta#phi cut, HT >= 1300 GeV";
   c =  DrawComparison( pred_->GetPredictionHisto("MHT_JetBin4_HThigh"), pred_->GetSelectionHisto("MHT_JetBin4_HThigh"), Title, LumiTitle,"#slash{H}_{T} (GeV)", isData);
   c->Print("outpout_GetPrediction/QCD_searchBins" + postfix + ".ps)");
   c->Print("outpout_GetPrediction/MHT_JetBin4_HThigh" + postfix + ".png");

   // plots for inclusive jet bins
   //jet Bin 1
   Title = "2 jets, #Delta#phi cut, HT > 500 GeV";
   c = DrawComparison( pred_->GetPredictionHisto("MHT_JetBin1_HTinclusive"), pred_->GetSelectionHisto("MHT_JetBin1_HTinclusive"), Title, LumiTitle,"#slash{H}_{T} (GeV)", isData); 
   c->Print("outpout_GetPrediction/QCD_HTinclusiveNJetBins" + postfix + ".ps(");
   c->Print("outpout_GetPrediction/MHT_JetBin1_HTinclusive" + postfix + ".png");

   // jet Bin2
   Title = "3 - 5 jets, #Delta#phi cut, HT > 500 GeV";
   c = DrawComparison( pred_->GetPredictionHisto("MHT_JetBin2_HTinclusive"), pred_->GetSelectionHisto("MHT_JetBin2_HTinclusive"), Title, LumiTitle,"#slash{H}_{T} (GeV)", isData); 
   c->Print("outpout_GetPrediction/QCD_HTinclusiveNJetBins" + postfix + ".ps");
   c->Print("outpout_GetPrediction/MHT_JetBin2_HTinclusive" + postfix + ".png");

   // jet Bin3
   Title = "6 - 7 jets, #Delta#phi cut, HT > 500 GeV";
   c = DrawComparison( pred_->GetPredictionHisto("MHT_JetBin3_HTinclusive"), pred_->GetSelectionHisto("MHT_JetBin3_HTinclusive"), Title, LumiTitle,"#slash{H}_{T} (GeV)", isData); 
   c->Print("outpout_GetPrediction/QCD_HTinclusiveNJetBins" + postfix + ".ps");
   c->Print("outpout_GetPrediction/MHT_JetBin3_HTinclusive" + postfix + ".png");

   // jet Bin 4
   Title = ">= 8 jets, #Delta#phi cut, HT > 500 GeV";
   c = DrawComparison( pred_->GetPredictionHisto("MHT_JetBin4_HTinclusive"), pred_->GetSelectionHisto("MHT_JetBin4_HTinclusive"), Title, LumiTitle,"#slash{H}_{T} (GeV)", isData); 
   c->Print("outpout_GetPrediction/QCD_HTinclusiveNJetBins" + postfix + ".ps)");
   c->Print("outpout_GetPrediction/MHT_JetBin4_HTinclusive" + postfix + ".png");

   // baseline plots
   Title = "#Delta#phi cut, HT > 500 GeV";
   c =  DrawComparison( pred_->GetPredictionHisto("NJets_baseline_withoutMHT"), pred_->GetSelectionHisto("NJets_baseline_withoutMHT"), Title, LumiTitle,"N_{Jets}", isData);
   c->Print("outpout_GetPrediction/QCD_NJets_withoutMHT" + postfix + ".ps");
   c->Print("outpout_GetPrediction/NJets_baseline_withoutMHT" + postfix + ".png");

   Title = "#Delta#phi cut, HT > 500 GeV, MHT > 200 GeV";
   c =  DrawComparison( pred_->GetPredictionHisto("NJets_baseline"), pred_->GetSelectionHisto("NJets_baseline"), Title, LumiTitle,"N_{Jets}", isData);
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

   // deltaPhi plots
   Title = ">= 2 jets";
   c =  DrawComparison( pred_->GetPredictionHisto("DeltaPhi1_presel"), pred_->GetSelectionHisto("DeltaPhi1_presel"), Title, LumiTitle,"#Delta#phi (jet1, MHT)", isData);
   c->Print("outpout_GetPrediction/QCD_DeltaPhiPlots_presel" + postfix + ".ps(");
   c->Print("outpout_GetPrediction/DeltaPhi1_presel" + postfix + ".png");

   Title = ">= 2 jets";
   c =  DrawComparison( pred_->GetPredictionHisto("DeltaPhi2_presel"), pred_->GetSelectionHisto("DeltaPhi2_presel"), Title, LumiTitle,"#Delta#phi (jet2, MHT)", isData);
   c->Print("outpout_GetPrediction/QCD_DeltaPhiPlots_presel" + postfix + ".ps");
   c->Print("outpout_GetPrediction/DeltaPhi2_presel" + postfix + ".png");

   Title = "> 2 jets";
   c =  DrawComparison( pred_->GetPredictionHisto("DeltaPhi3_presel"), pred_->GetSelectionHisto("DeltaPhi3_presel"), Title, LumiTitle,"#Delta#phi (jet3, MHT)", isData);
   c->Print("outpout_GetPrediction/QCD_DeltaPhiPlots_presel" + postfix + ".ps)");
   c->Print("outpout_GetPrediction/DeltaPhi3_presel" + postfix + ".png");

  

   // set search bin cut values for HT and MHT (check with Prediction.C)
   double HTlow = 500;
   double HTmedium = 900;
   double HThigh = 1300;
   double MHTlow = 200;
   double MHTmedium = 350;
   double MHThigh = 500;
   int SmearRep = 100;
  
   /* // has to be adjusted to the new NJet Bins 
   // QCD predictions in search bins
   // first jet multiplicity bin
   cout << "----------------------" << endl;
   cout << "----------------------" << endl;
   cout << "NJets = 2 " << endl;
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
   cout << "NJets = 3 - 5" << endl;
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




