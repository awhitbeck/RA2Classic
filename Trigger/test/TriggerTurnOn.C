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
   TString psfile = "TriggerTurnOn/TriggerTurnOn_chsJets.ps";
 
   // --- open input files ---//
   // turn-on file
   TFile *file_TagEle27WP80 = TFile::Open("/afs/naf.desy.de/user/k/kriheine/kriheine/Data_8TeV_2012_RunA+B+C_CMSSW535_Trigger_v1.root");
    
   // get histos from files  
   // MHT/HT turn-on       
   file_TagEle27WP80->cd("trigger;1");

   // PFHT histos
   TH1F* MHTallprobes_PFHT;
   gDirectory->GetObject("MHTallprobes_PFHT", MHTallprobes_PFHT);
   TH1F* MHTpassedprobes_PFHT;
   gDirectory->GetObject("MHTpassedprobes_PFHT", MHTpassedprobes_PFHT);

   TH1F* HTallprobes_PFHT;
   gDirectory->GetObject("HTallprobes_PFHT", HTallprobes_PFHT);
   TH1F* HTpassedprobes_PFHT;
   gDirectory->GetObject("HTpassedprobes_PFHT", HTpassedprobes_PFHT);

   TH1F* MHT_all_total_PFHT;
   gDirectory->GetObject("MHTallprobes_total_PFHT", MHT_all_total_PFHT);
   TH1F* MHT_passed_total_PFHT;
   gDirectory->GetObject("MHTpassedprobes_total_PFHT", MHT_passed_total_PFHT);

   TH1F* MHT_all_IntEff_PFHT;
   gDirectory->GetObject("MHTallprobes_intEff_PFHT", MHT_all_IntEff_PFHT);
   TH1F* MHT_passed_IntEff_PFHT;
   gDirectory->GetObject("MHTpassedprobes_intEff_PFHT", MHT_passed_IntEff_PFHT);

   TH1F* HT_all_IntEff_PFHT;
   gDirectory->GetObject("HTallprobes_intEff_PFHT", HT_all_IntEff_PFHT);
   TH1F* HT_passed_IntEff_PFHT;
   gDirectory->GetObject("HTpassedprobes_intEff_PFHT", HT_passed_IntEff_PFHT); 

   // PFNoPUHT histos
   TH1F* MHTallprobes_PFNoPUHT;
   gDirectory->GetObject("MHTallprobes_PFNoPUHT", MHTallprobes_PFNoPUHT);
   TH1F* MHTpassedprobes_PFNoPUHT;
   gDirectory->GetObject("MHTpassedprobes_PFNoPUHT", MHTpassedprobes_PFNoPUHT);

   TH1F* HTallprobes_PFNoPUHT;
   gDirectory->GetObject("HTallprobes_PFNoPUHT", HTallprobes_PFNoPUHT);
   TH1F* HTpassedprobes_PFNoPUHT;
   gDirectory->GetObject("HTpassedprobes_PFNoPUHT", HTpassedprobes_PFNoPUHT);

   TH1F* MHT_all_total_PFNoPUHT;
   gDirectory->GetObject("MHTallprobes_total_PFNoPUHT", MHT_all_total_PFNoPUHT);
   TH1F* MHT_passed_total_PFNoPUHT;
   gDirectory->GetObject("MHTpassedprobes_total_PFNoPUHT", MHT_passed_total_PFNoPUHT);

   TH1F* MHT_all_IntEff_PFNoPUHT;
   gDirectory->GetObject("MHTallprobes_intEff_PFNoPUHT", MHT_all_IntEff_PFNoPUHT);
   TH1F* MHT_passed_IntEff_PFNoPUHT;
   gDirectory->GetObject("MHTpassedprobes_intEff_PFNoPUHT", MHT_passed_IntEff_PFNoPUHT);

   TH1F* HT_all_IntEff_PFNoPUHT;
   gDirectory->GetObject("HTallprobes_intEff_PFNoPUHT", HT_all_IntEff_PFNoPUHT);
   TH1F* HT_passed_IntEff_PFNoPUHT;
   gDirectory->GetObject("HTpassedprobes_intEff_PFNoPUHT", HT_passed_IntEff_PFNoPUHT); 

   // PFHT650 histos
   TH1F* HTallprobes_PFHT650;
   gDirectory->GetObject("HTallprobes_PFHT650", HTallprobes_PFHT650);
   TH1F* HTpassedprobes_PFHT650;
   gDirectory->GetObject("HTpassedprobes_PFHT650", HTpassedprobes_PFHT650);

   // PFNoPUHT650 histos
   TH1F* HTallprobes_PFNoPUHT650;
   gDirectory->GetObject("HTallprobes_PFNoPUHT650", HTallprobes_PFNoPUHT650);
   TH1F* HTpassedprobes_PFNoPUHT650;
   gDirectory->GetObject("HTpassedprobes_PFNoPUHT650", HTpassedprobes_PFNoPUHT650);

   // define Turn On Graphs
   // PFHT
   TGraphAsymmErrors* MHTturnon_PFHT = new TGraphAsymmErrors(MHTpassedprobes_PFHT, MHTallprobes_PFHT);
   TGraphAsymmErrors* HTturnon_PFHT = new TGraphAsymmErrors(HTpassedprobes_PFHT, HTallprobes_PFHT);
   TGraphAsymmErrors* Eff_total_PFHT = new TGraphAsymmErrors(MHT_passed_total_PFHT, MHT_all_total_PFHT);
   TGraphAsymmErrors* IntEff_MHT_PFHT = new TGraphAsymmErrors( MHT_passed_IntEff_PFHT, MHT_all_IntEff_PFHT);
   TGraphAsymmErrors* IntEff_HT_PFHT = new TGraphAsymmErrors( HT_passed_IntEff_PFHT, HT_all_IntEff_PFHT);

   // PFNoPUHT
   TGraphAsymmErrors* MHTturnon_PFNoPUHT = new TGraphAsymmErrors(MHTpassedprobes_PFNoPUHT, MHTallprobes_PFNoPUHT);
   TGraphAsymmErrors* HTturnon_PFNoPUHT = new TGraphAsymmErrors(HTpassedprobes_PFNoPUHT, HTallprobes_PFNoPUHT);
   TGraphAsymmErrors* Eff_total_PFNoPUHT = new TGraphAsymmErrors(MHT_passed_total_PFNoPUHT, MHT_all_total_PFNoPUHT);
   TGraphAsymmErrors* IntEff_MHT_PFNoPUHT = new TGraphAsymmErrors( MHT_passed_IntEff_PFNoPUHT, MHT_all_IntEff_PFNoPUHT);
   TGraphAsymmErrors* IntEff_HT_PFNoPUHT = new TGraphAsymmErrors( HT_passed_IntEff_PFNoPUHT, HT_all_IntEff_PFNoPUHT);

   // PFHT650
   TGraphAsymmErrors* HTturnon_PFHT650 = new TGraphAsymmErrors(HTpassedprobes_PFHT650, HTallprobes_PFHT650);

   // PFNoPUHT650
   TGraphAsymmErrors* HTturnon_PFNoPUHT650 = new TGraphAsymmErrors(HTpassedprobes_PFNoPUHT650, HTallprobes_PFNoPUHT650);

   TCanvas *c; 
   TString trigger;
   TString y_title;

   /////////////////////////////////////////////////////////////////////////////

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

   /////////////////////////////////////////////////////////////////////////////
   //----------------------------------------//
   //-------------- PFHT --------------------//
   //----------------------------------------//

   // MHT turnon ProbePFHT350PFMET100 TagEle27WP80 
   trigger = "HLT_PFHT350_PFMET100, HT>500GeV";//, CHS jets";
   y_title = "efficiency";

   c = DrawTurnOn_MHT(MHTturnon_PFHT, trigger, y_title); 

   c->Print( psfile + "[");
   c->Print( "TriggerTurnOn/turn_on_MHT_TagEle27WP80_ProbePFHT350PFMET100_HT500_chs.png" );
   c->Print( psfile );

   // HT turnon ProbeHT350MET100 TagEle27WP80 
   trigger = "HLT_PFHT350_PFMET100, MHT>200GeV";//, CHS jets";
   y_title = "efficiency";

   c = DrawTurnOn_HT(HTturnon_PFHT, trigger, y_title); 
  
   c->Print( "TriggerTurnOn/turn_on_HT_TagEle27WP80_ProbePFHT350PFMET100_MHT200_chs.png" );
   c->Print( psfile );

   // Total efficiency for baseline
   trigger = "Total Efficiency HLT_PFHT350_PFMET100: MHT>200GeV, HT>500GeV";
   y_title = "total efficiency";
   c = DrawTurnOn_MHT(Eff_total_PFHT, trigger, y_title );
   double eff_x;
   double eff_y;
   Eff_total_PFHT->GetPoint(0, eff_x, eff_y);

   cout <<"###################################################################################" << endl;
   cout << "Integrated Efficiency HLT_PFHT350_PFMET100 HT>500GeV, MHT>200GeV: " << eff_y 
        << " + " << Eff_total_PFHT->GetErrorYhigh(0) 
        << " - " << Eff_total_PFHT->GetErrorYlow(0) << endl; 
   cout <<"###################################################################################" << endl;
  
   c->Print( "TriggerTurnOn/IntEff_baseline_HLT_PFHT350PFMET100.png" );
   c->Print( psfile );

   // Integrated efficiency vs. MHT
   trigger = "HLT_PFHT350_PFMET100, HT>500GeV";
   y_title = "integrated efficiency";
   c = DrawTurnOn_MHT(IntEff_MHT_PFHT, trigger, y_title ); 
  
   c->Print( "TriggerTurnOn/turn_on_MHT_IntegratedEff_HLT_PFHT350PFMET100.png" );
   c->Print( psfile );

   // Integrated efficiency vs. HT
   trigger = "HLT_PFHT350_PFMET100, MHT>200GeV";
   y_title = "integrated efficiency";
   c = DrawTurnOn_HT(IntEff_HT_PFHT, trigger, y_title ); 
  
   c->Print( "TriggerTurnOn/turn_on_HT_IntegratedEff_HLT_PFHT350PFMET100.png" );
   c->Print( psfile );

   //--------------------------------------------//
   //-------------- PFNoPUHT --------------------//
   //--------------------------------------------//

   // MHT turnon ProbeHT350MET100 TagEle27WP80 
   trigger = "HLT_PFNoPUHT350_PFMET100, HT>500GeV";//, CHS jets";
   y_title = "efficiency";

   c = DrawTurnOn_MHT(MHTturnon_PFNoPUHT, trigger, y_title); 

   c->Print( "TriggerTurnOn/turn_on_MHT_TagEle27WP80_ProbePFNoPUHT350PFMET100_HT500_chs.png" );
   c->Print( psfile );

   // HT turnon ProbeHT350MET100 TagEle27WP80 
   trigger = "HLT_PFNoPUHT350_PFMET100, MHT>200GeV";//, CHS jets";
   y_title = "efficiency";

   c = DrawTurnOn_HT(HTturnon_PFNoPUHT, trigger, y_title); 
  
   c->Print( "TriggerTurnOn/turn_on_HT_TagEle27WP80_ProbePFNoPUHT350PFMET100_MHT200_chs.png" );
   c->Print( psfile );

   // Total efficiency for baseline
   trigger = "Total Efficiency HLT_PFNoPUHT350_PFMET100: MHT>200GeV, HT>500GeV";
   y_title = "total efficiency";
   c = DrawTurnOn_MHT(Eff_total_PFNoPUHT, trigger, y_title );
   double eff_x;
   double eff_y;
   Eff_total_PFNoPUHT->GetPoint(0, eff_x, eff_y);

   cout <<"###################################################################################" << endl;
   cout << "Integrated Efficiency HLT_PFNoPUHT350_PFMET100 HT>500GeV, MHT>200GeV: " << eff_y 
        << " + " << Eff_total_PFNoPUHT->GetErrorYhigh(0) 
        << " - " << Eff_total_PFNoPUHT->GetErrorYlow(0) << endl; 
   cout <<"###################################################################################" << endl;
  
   c->Print( "TriggerTurnOn/IntEff_baseline_HLT_PFNoPUHT350PFMET100.png" );
   c->Print( psfile );

   // Integrated efficiency vs. MHT
   trigger = "HLT_PFNoPUHT350_PFMET100, HT>500GeV";
   y_title = "integrated efficiency";
   c = DrawTurnOn_MHT(IntEff_MHT_PFNoPUHT, trigger, y_title ); 
  
   c->Print( "TriggerTurnOn/turn_on_MHT_IntegratedEff_HLT_PFNoPUHT350PFMET100.png" );
   c->Print( psfile );

   // Integrated efficiency vs. HT
   trigger = "HLT_PFNoPUHT350_PFMET100, MHT>200GeV";
   y_title = "integrated efficiency";
   c = DrawTurnOn_HT(IntEff_HT_PFNoPUHT, trigger, y_title ); 
  
   c->Print( "TriggerTurnOn/turn_on_HT_IntegratedEff_HLT_PFNoPUHT350PFMET100.png" );
   c->Print( psfile );

   //----------------------------------------//
   //-------------- PFHT650 --------------------//
   //----------------------------------------//

   // HT turnon Probe PFHT650 TagEle27WP80 
   trigger = "HLT_PFHT650";//, CHS jets";
   y_title = "efficiency";

   c = DrawTurnOn_HT(HTturnon_PFHT650, trigger, y_title); 
  
   c->Print( "TriggerTurnOn/turn_on_HT_TagEle27WP80_ProbePFHT650_chs.png" );
   c->Print( psfile );

   //----------------------------------------//
   //-------------- PFNoPUHT650 --------------------//
   //----------------------------------------//

   // HT turnon Probe PFNoPUHT650 TagEle27WP80 
   trigger = "HLT_PFNoPUHT650";//, CHS jets";
   y_title = "efficiency";

   c = DrawTurnOn_HT(HTturnon_PFNoPUHT650, trigger, y_title); 
  
   c->Print( "TriggerTurnOn/turn_on_HT_TagEle27WP80_ProbePFNoPUHT650_chs.png" );
   c->Print( psfile );

   // close output file
   c->Print( psfile + "]");
}

TCanvas* DrawTurnOn_MHT(TGraphAsymmErrors* TurnOn, TString trigger, TString y_title)
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
   // TurnOn->SetTitle(trigger);
   TurnOn->Draw("APsame");

   //  TPaveText* pt = new TPaveText(0.05, 0.98, 0.95, 0.86, "NDC");
   TPaveText* pt = new TPaveText(0.35, 0.3, 0.95, 0.3, "NDC");
   pt->SetBorderSize(0);
   pt->SetFillStyle(0);
   pt->SetTextAlign(12);
   pt->SetTextSize(0.032);
   pt->SetTextFont(42);
   pt->AddText(trigger);
   pt->Draw("same");
 
   return c;
}

TCanvas* DrawTurnOn_HT(TGraphAsymmErrors* TurnOn, TString trigger, TString y_title)
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
   //  TurnOn->SetTitle(trigger);
   TurnOn->Draw("APsame");

   if ( trigger.Contains("650") ) {
      TPaveText* pt = new TPaveText(0.5, 0.4, 0.65, 0.4, "NDC");
      pt->SetBorderSize(0);
      pt->SetFillStyle(0);
      pt->SetTextAlign(12);
      pt->SetTextSize(0.032);
      pt->SetTextFont(42);
      pt->AddText(trigger);
      pt->Draw("same");
   }
   else {
      TPaveText* pt = new TPaveText(0.097, 0.3, 0.65, 0.3, "NDC");
      pt->SetBorderSize(0);
      pt->SetFillStyle(0);
      pt->SetTextAlign(12);
      pt->SetTextSize(0.032);
      pt->SetTextFont(42);
      pt->AddText(trigger);
      pt->Draw("same");
   }
 
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


