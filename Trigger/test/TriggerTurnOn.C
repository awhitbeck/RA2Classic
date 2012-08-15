#include <TROOT.h>
#include <TSystem.h>
#include <TF1.h>
#include <TH1.h>
#include <TH2.h>
#include <TProfile.h>
#include <TCanvas.h>
#include <TPad.h>
#include <TStyle.h>
#include <TFile.h>
#include <TPostScript.h>
#include <TLegend.h>
#include <TMath.h>
#include <TArrayF.h>
#include <TLine.h>
#include <TString.h>
#include <TGraphAsymmErrors.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

void TriggerTurnOn() 
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
   gStyle->SetMarkerSize(0.7);
   gStyle->SetMarkerStyle(20);
   gStyle->SetMarkerColor(1);
  
   // For the statistics box:
   gStyle->SetOptStat(0);
   //gStyle->SetOptFit(1011);
   //gStyle->SetStatColor(0);
   //gStyle->SetStatBorderSize(2);

   // Margins:
   gStyle->SetPadBottomMargin(0.15);
   gStyle->SetPadTopMargin(0.15);
   gStyle->SetPadLeftMargin(0.10);
   gStyle->SetPadRightMargin(0.05);
   
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
   gStyle->SetTickLength(0.03);

   // For the axis titles:
   gStyle->SetTitleOffset(1.4, "X");
   gStyle->SetTitleOffset(1.15, "Y");
   gStyle->SetTitleOffset(0.5, "Z");
   gStyle->SetTitleSize(0.04, "XYZ");
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

   
   // --- define output file for ps ---//
   //   TString psfile = "TriggerTurnOn/TriggerTurnOn_ProbeHT350MET100_standardJets.ps";
   TString psfile = "TriggerTurnOn/TriggerTurnOn_PFNoPUHT350MET100_standardJets.ps";

   // --- open input files ---//
   // MHT turn-on files
   //  TFile *file_MHT30GeV_TagEle27WP80_ProbeHT350MET100_MHTwoJetID_HT500 = TFile::Open("~/kheine/Data_2012/Trigger_OnData_8TeV_2012_190456-194479modified_HTplusMHTturnon_TagEle27WP80_ProbeHT350MET100_IntEffPlusHisto_withAllFilters_v3.root");
   
   // TFile *file_MHT30GeV_TagEle27WP80_ProbeHT350MET100_MHTwoJetID_HT500 = TFile::Open("~/kheine/Data_2012/Trigger_OnData_8TeV_2012_190456-196531_TagEle27WP80_ProbeHT350MET100_standardJets_v1.root");
   TFile *file_MHT30GeV_TagEle27WP80_ProbeHT350MET100_MHTwoJetID_HT500 = TFile::Open("~/kheine/Data_2012/Trigger_OnData_8TeV_2012_190456-196531_TagEle27WP80_ProbePFNoPUHT350MET100_standardJets_v1.root");


   // online - offline correlation files
   TFile *file_corr30GeV = TFile::Open("~/kheine/Data_2012/Trigger_OnData_8TeV_2012_190456-191859_OnlineOfflineCorrelation_WithEventBool_MHTJet30GeV_v1.root");
   TFile *file_corrHT = TFile::Open("~/kheine/Data_2012/Trigger_OnData_8TeV_2012_190456-191859_OnlineOfflineCorrelation_WithEventBool_v1.root");

  
   // get histos from files  
   // MHT/HT turn-on       
   file_MHT30GeV_TagEle27WP80_ProbeHT350MET100_MHTwoJetID_HT500->cd("trigger;1");

   TH1F* MHTallprobes;
   gDirectory->GetObject("MHTallprobes", MHTallprobes);
   TH1F* MHTpassedprobes;
   gDirectory->GetObject("MHTpassedprobes", MHTpassedprobes);

   TH1F* HTallprobes;
   gDirectory->GetObject("HTallprobes", HTallprobes);
   TH1F* HTpassedprobes;
   gDirectory->GetObject("HTpassedprobes", HTpassedprobes);

   TH1F* MHT_all_IntEff_total;
   gDirectory->GetObject("MHTallprobes_total", MHT_all_IntEff_total);
   TH1F* MHT_passed_IntEff_total;
   gDirectory->GetObject("MHTpassedprobes_total", MHT_passed_IntEff_total);

   TH1F* MHT_all_IntEff;
   gDirectory->GetObject("MHTallprobes_intEff", MHT_all_IntEff);
   TH1F* MHT_passed_IntEff;
   gDirectory->GetObject("MHTpassedprobes_intEff", MHT_passed_IntEff);

   TH1F* HT_all_IntEff;
   gDirectory->GetObject("HTallprobes_intEff", HT_all_IntEff);
   TH1F* HT_passed_IntEff;
   gDirectory->GetObject("HTpassedprobes_intEff", HT_passed_IntEff);
   
   // MHT/HT correlation
   file_corr30GeV->cd("trigger;1");
   TH2F* MHTCorr30GeV;
   gDirectory->GetObject("corr_online_offlineMHT", MHTCorr30GeV);
   TH2F* METCorr30GeV;
   gDirectory->GetObject("corr_online_offlineMET", METCorr30GeV);

   file_corrHT->cd("trigger;1");
   TH2F* HTCorr;
   gDirectory->GetObject("corr_online_offlineHT", HTCorr);
   

   // define Turn On Graphs
   TGraphAsymmErrors* MHTturnon = new TGraphAsymmErrors(MHTpassedprobes, MHTallprobes);
   TGraphAsymmErrors* HTturnon = new TGraphAsymmErrors(HTpassedprobes, HTallprobes);
   TGraphAsymmErrors* IntEff_total = new TGraphAsymmErrors(MHT_passed_IntEff_total, MHT_all_IntEff_total);
   TGraphAsymmErrors* IntEff_MHT = new TGraphAsymmErrors( MHT_passed_IntEff, MHT_all_IntEff);
   TGraphAsymmErrors* IntEff_HT = new TGraphAsymmErrors( HT_passed_IntEff, HT_all_IntEff);

   TCanvas *c; 
   TString jet_pt;
   TString y_title;

   // define fit function
   /*  TF1 *fit = new TF1("fit","0.5*[0]*(TMath::Erf([1]*x-[2])+1)", 0, 500);
   fit->SetParName(0, "plateau efficiency");
   fit->SetParameter(0, 1);
   fit->SetParameter(1, 2);
   fit->SetParameter(2, 100);
 
   TFitResult *res = MHTturnon_MHT0GeV->Fit( fit, "R0S" ).Get();
   TF1 *f = new TF1( *MHTturnon_MHT0GeV->GetFunction("fit") );
   f->SetLineColor( kBlue );
   f->SetLineWidth( 0.5 );
   // f->Draw(); 

   double eff_value = 100*f->GetParameter(0);
   double eff_error = 100*f->GetParError(0);

   TLegend *leg1 = new TLegend(0.15, 0.7, 0.45, 0.8);
   Char_t message[80];
   sprintf(message, "Fit: Plateau efficiency = %.2f +- %.2f", eff_value, eff_error);
   leg1->AddEntry(f, message, "l");
   leg1->SetFillStyle(0);
   leg1->SetTextSize(0.03);
   //  leg1->Draw("same");*/
 
   // MHT turnon ProbeHT350MET100 TagEle27WP80 MHT without jet ID
   // jet_pt = "HLT_PFHT350_PFMET100 (Tag: HLT_Ele27_WP80) HT>500GeV";//, CHS jets";
   jet_pt = "HLT_PFNoPUHT350_PFMET100 (Tag: HLT_Ele27_WP80) HT>500GeV";//, CHS jets";
   y_title = "efficiency";

   c = DrawTurnOn_MHT(MHTturnon, jet_pt, y_title); 

   c->Print( psfile + "[");
   //  c->Print( "TriggerTurnOn/turn_on_MHT_TagEle27WP80_ProbeHT350MET100_MHTwoJetID_HT500.png" );
   c->Print( psfile );

   // HT turnon ProbeHT350MET100 TagEle27WP80 HT without jet ID
   //  jet_pt = "HLT_PFHT350_PFMET100 (Tag: HLT_Ele27_WP80) MHT>200GeV";//, CHS jets";
   jet_pt = "HLT_PFNoPUHT350_PFMET100 (Tag: HLT_Ele27_WP80) MHT>200GeV";//, CHS jets";
   y_title = "efficiency";

   c = DrawTurnOn_HT(HTturnon, jet_pt, y_title); 
  
   //  c->Print( "TriggerTurnOn/turn_on_HT_TagEle27WP80_ProbeHT350MET100_HTwoJetID_MHT200.png" );
   c->Print( psfile );

   // Integrated efficiency for baseline
   jet_pt = "Integrated Efficiency: MHT>200GeV, HT>500GeV";
   y_title = "integrated efficiency";
   c = DrawTurnOn_MHT(IntEff_total, jet_pt, y_title );
   double eff_x;
   double eff_y;
   IntEff_total->GetPoint(0, eff_x, eff_y);

   cout <<"###################################################################################" << endl;
   cout << "Integrated Efficiency HT>500GeV, MHT>200GeV: " << eff_y 
        << " + " << IntEff_total->GetErrorYhigh(0) 
        << " - " << IntEff_total->GetErrorYlow(0) << endl; 
   cout <<"###################################################################################" << endl;
  
   c->Print( "TriggerTurnOn/IntEff_baseline.png" );
   //  c->Print( psfile );

   // Integrated efficiency vs. MHT
   jet_pt = "HLT_PFHT350_PFMET100 (Tag: HLT_Ele27_WP80)";
   y_title = "integrated efficiency";
   c = DrawTurnOn_MHT(IntEff_MHT, jet_pt, y_title ); 
  
   c->Print( "TriggerTurnOn/turn_on_MHT_IntegratedEff.png" );
   // c->Print( psfile );

   // Integrated efficiency vs. HT
   jet_pt = "HLT_PFHT350_PFMET100 (Tag: HLT_Ele27_WP80)";
   y_title = "integrated efficiency";
   c = DrawTurnOn_HT(IntEff_HT, jet_pt, y_title ); 
  
   c->Print( "TriggerTurnOn/turn_on_HT_IntegratedEff.png" );
   //  c->Print( psfile );


   // plot online - offline correlations
   //
   c = DrawOnlineOfflineCorrelation(MHTCorr30GeV, "Trigger PFMET150", "online MHT [GeV]", "offline MHT [GeV]: Jet 30GeV");

   c->Print( "TriggerTurnOn/correlation_MHT30GeV.png" );
   //  c->Print( psfile );

   //
   c = DrawOnlineOfflineCorrelation(METCorr30GeV, "Trigger PFMET150", "online MHT [GeV]", "offline MET [GeV]");

   c->Print( "TriggerTurnOn/correlation_MET.png" );
   //  c->Print( psfile );

   //
   c = DrawOnlineOfflineCorrelation(HTCorr, "Trigger PFHT350", "online HT [GeV]", "offline HT [GeV]");

   c->Print( "TriggerTurnOn/correlation_HT.png" );
   //   c->Print( psfile );


   // close output file
   c->Print( psfile + "]");
}

TCanvas* DrawTurnOn_MHT(TGraphAsymmErrors* TurnOn, TString jet_pt, TString y_title)
{
   TCanvas *c = new TCanvas("Turn On", "MHT", 800, 700);
 
   c->cd();
   TAxis* x = new TAxis();
   x = TurnOn->GetXaxis();
   x->SetTitle("MHT [GeV]");
   x->Draw();
   TAxis* y = new TAxis();
   y = TurnOn->GetYaxis();
   y->SetTitle(y_title);
   y->Draw("same");
   TurnOn->SetTitle(jet_pt);
   TurnOn->Draw("APsame");

   TPaveText* pt = new TPaveText(0.05, 0.98, 0.95, 0.86, "NDC");
   pt->SetBorderSize(0);
   pt->SetFillStyle(0);
   pt->SetTextAlign(12);
   pt->SetTextSize(0.032);
   pt->SetTextFont(42);
   pt->AddText(jet_pt);
   pt->Draw("same");
 
   return c;
}

TCanvas* DrawTurnOn_HT(TGraphAsymmErrors* TurnOn, TString jet_pt, TString y_title)
{
   TCanvas *c = new TCanvas("Turn On", "MHT", 800, 700);
 
   c->cd();
   TAxis* x = new TAxis();
   x = TurnOn->GetXaxis();
   x->SetTitle("HT [GeV]");
   x->Draw();
   TAxis* y = new TAxis();
   y = TurnOn->GetYaxis();
   y->SetTitle(y_title);
   y->Draw("same");
   TurnOn->SetTitle(jet_pt);
   TurnOn->Draw("APsame");

   TPaveText* pt = new TPaveText(0.05, 0.98, 0.95, 0.86, "NDC");
   pt->SetBorderSize(0);
   pt->SetFillStyle(0);
   pt->SetTextAlign(12);
   pt->SetTextSize(0.032);
   pt->SetTextFont(42);
   pt->AddText(jet_pt);
   pt->Draw("same");
 
   return c;
}

TCanvas* DrawOnlineOfflineCorrelation(TH2F* correlation, TString title, TString xtitle, TString ytitle)
{
   TCanvas *c = new TCanvas("Online_offline_correlation", "", 800, 700);
   c->cd();

   correlation->SetMarkerSize(0.3);
   correlation->SetTitle(title);
   correlation->SetXTitle(xtitle);
   correlation->SetYTitle(ytitle);
   correlation->Draw();

   TLine* line = new TLine(0., 200., 1000., 200.);
   line->Draw("same");
  
   return c;
}


