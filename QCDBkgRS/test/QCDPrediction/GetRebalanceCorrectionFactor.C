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
#include <TArrayF.h>
#include <TLine.h>
#include <TPaveText.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

void GetRebalanceCorrectionFactor()
{
   gROOT->Reset();
   gROOT->SetStyle("Plain");
   //gStyle->SetPalette(51, 0);

   //  gStyle->SetHatchesLineWidth(1.2);

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
   gStyle->SetMarkerSize(0.75);
   gStyle->SetMarkerStyle(20);
   gStyle->SetMarkerColor(1);
  
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


   // --- define output file for ps ---//
   TString pt = "pt10";
   double x_min = 10.;

   TString outfile = "RebalanceCorrectionFactor/RebalanceCorrectionFactors_DR53X_chsJets_TuneZ2star_withoutPUReweighting_" + pt;

   TH2F* RebCorrection_vsReco = new TH2F("RebCorrection_vsReco", "Jet pt", 1000, 0., 1000., 100, 0., 3.);
   TH2F* RebCorrection_vsReco_madgraph = new TH2F("RebCorrection_vsReco_madgraph", "Jet pt", 1000, 0., 1000., 100, 0., 3.);
   TH2F* RebCorrection_vsReco_NVtx0_10 = new TH2F("RebCorrection_vsReco_NVtx0_10", "Jet pt", 1000, 0., 1000., 100, 0., 3.);
   TH2F* RebCorrection_vsReco_NVtx11_20 = new TH2F("RebCorrection_vsReco_NVtx11_20", "Jet pt", 1000, 0., 1000., 100, 0., 3.);
   TH2F* RebCorrection_vsReco_NVtx21_Inf = new TH2F("RebCorrection_vsReco_NVtx21_Inf", "Jet pt", 1000, 0., 1000., 100, 0., 3.);
   
   string root_file;

   // pythia
   ifstream myfile ("filelists_53X/filelist_pythia_DR53X_chs_TuneZ2star_" + pt + "_withoutPUReweighting_RebControlPlots_v1_mc.txt");
   if (myfile.is_open()) {
      while( myfile.good() ) {
         getline (myfile,root_file);
         cout << root_file << endl;
                     
         TH2F* RebCorrection_vsReco_temp; 
               
         TString path = root_file;

         TFile* input_file = TFile::Open(path, "READ");
         input_file->cd("QCDfromSmearing");

         gDirectory->GetObject("RebCorrection_vsReco;1", RebCorrection_vsReco_temp);
         RebCorrection_vsReco->Add(RebCorrection_vsReco_temp);

         input_file->Close();
         
      }
      myfile.close();
   }

   // madgraph 1 HT=100-250
   ifstream myfile2 ("filelists_53X/filelist_madgraph_DR53X_chs_" + pt + "_withoutPUReweighting_HT100-250_RebControlPlots_v1_mc.txt");
   if (myfile2.is_open()) {
      while( myfile2.good() ) {
         getline (myfile2,root_file);
         cout << root_file << endl;
               
         TH2F* RebCorrection_vsReco_madgraph_temp; 
                
         TString path = root_file;

         TFile* input_file = TFile::Open(path, "READ");
         input_file->cd("QCDfromSmearing");

         gDirectory->GetObject("RebCorrection_vsReco;1", RebCorrection_vsReco_madgraph_temp);
         RebCorrection_vsReco_madgraph->Add(RebCorrection_vsReco_madgraph_temp);

         input_file->Close();
         
      }
      myfile2.close();
   }

   // madgraph 2 HT=250-500
   ifstream myfile3 ("filelists_53X/filelist_madgraph_DR53X_chs_" + pt + "_withoutPUReweighting_HT250-500_RebControlPlots_v1_mc.txt");
   if (myfile3.is_open()) {
      while( myfile3.good() ) {
         getline (myfile3,root_file);
         cout << root_file << endl;
               
         TH2F* RebCorrection_vsReco_madgraph_temp; 
                
         TString path = root_file;

         TFile* input_file = TFile::Open(path, "READ");
         input_file->cd("QCDfromSmearing");

         gDirectory->GetObject("RebCorrection_vsReco;1", RebCorrection_vsReco_madgraph_temp);
         RebCorrection_vsReco_madgraph->Add(RebCorrection_vsReco_madgraph_temp);

         input_file->Close();
         
      }
      myfile3.close();
   }

   // madgraph 3 HT=500-1000
   ifstream myfile4 ("filelists_53X/filelist_madgraph_DR53X_chs_" + pt + "_withoutPUReweighting_HT500-1000_RebControlPlots_v1_mc.txt");
   if (myfile4.is_open()) {
      while( myfile4.good() ) {
         getline (myfile4,root_file);
         cout << root_file << endl;
               
         TH2F* RebCorrection_vsReco_madgraph_temp; 
                
         TString path = root_file;

         TFile* input_file = TFile::Open(path, "READ");
         input_file->cd("QCDfromSmearing");

         gDirectory->GetObject("RebCorrection_vsReco;1", RebCorrection_vsReco_madgraph_temp);
         RebCorrection_vsReco_madgraph->Add(RebCorrection_vsReco_madgraph_temp);

         input_file->Close();
         
      }
      myfile4.close();
   }

   // madgraph 4 HT=1000-Inf
   ifstream myfile5 ("filelists_53X/filelist_madgraph_DR53X_chs_" + pt + "_withoutPUReweighting_HT1000-Inf_RebControlPlots_v1_mc.txt");
   if (myfile5.is_open()) {
      while( myfile5.good() ) {
         getline (myfile5,root_file);
         cout << root_file << endl;
               
         TH2F* RebCorrection_vsReco_madgraph_temp; 
                
         TString path = root_file;

         TFile* input_file = TFile::Open(path, "READ");
         input_file->cd("QCDfromSmearing");

         gDirectory->GetObject("RebCorrection_vsReco;1", RebCorrection_vsReco_madgraph_temp);
         RebCorrection_vsReco_madgraph->Add(RebCorrection_vsReco_madgraph_temp);

         input_file->Close();
         
      }
      myfile5.close();
   }

   // pythia - nVtx 0-10
   ifstream myfile ("filelists_53X/filelist_pythia_DR53X_chs_TuneZ2star_" + pt + "_withoutPUReweighting_RebControlPlots_NVtx0-10_v1_mc.txt");
   if (myfile.is_open()) {
      while( myfile.good() ) {
         getline (myfile,root_file);
         cout << root_file << endl;
                     
         TH2F* RebCorrection_vsReco_NVtx0_10_temp; 
               
         TString path = root_file;

         TFile* input_file = TFile::Open(path, "READ");
         input_file->cd("QCDfromSmearing");

         gDirectory->GetObject("RebCorrection_vsReco;1", RebCorrection_vsReco_NVtx0_10_temp);
         RebCorrection_vsReco_NVtx0_10->Add(RebCorrection_vsReco_NVtx0_10_temp);

         input_file->Close();
         
      }
      myfile.close();
   }

   // pythia - nVtx 11-20
   ifstream myfile ("filelists_53X/filelist_pythia_DR53X_chs_TuneZ2star_" + pt + "_withoutPUReweighting_RebControlPlots_NVtx11-20_v1_mc.txt");
   if (myfile.is_open()) {
      while( myfile.good() ) {
         getline (myfile,root_file);
         cout << root_file << endl;
                     
         TH2F* RebCorrection_vsReco_NVtx11_20_temp; 
               
         TString path = root_file;

         TFile* input_file = TFile::Open(path, "READ");
         input_file->cd("QCDfromSmearing");

         gDirectory->GetObject("RebCorrection_vsReco;1", RebCorrection_vsReco_NVtx11_20_temp);
         RebCorrection_vsReco_NVtx11_20->Add(RebCorrection_vsReco_NVtx11_20_temp);

         input_file->Close();
         
      }
      myfile.close();
   }

   // pythia - nVtx 21-Inf
   ifstream myfile ("filelists_53X/filelist_pythia_DR53X_chs_TuneZ2star_" + pt + "_withoutPUReweighting_RebControlPlots_NVtx21-Inf_v1_mc.txt");
   if (myfile.is_open()) {
      while( myfile.good() ) {
         getline (myfile,root_file);
         cout << root_file << endl;
                     
         TH2F* RebCorrection_vsReco_NVtx21_Inf_temp; 
               
         TString path = root_file;

         TFile* input_file = TFile::Open(path, "READ");
         input_file->cd("QCDfromSmearing");

         gDirectory->GetObject("RebCorrection_vsReco;1", RebCorrection_vsReco_NVtx21_Inf_temp);
         RebCorrection_vsReco_NVtx21_Inf->Add(RebCorrection_vsReco_NVtx21_Inf_temp);

         input_file->Close();
         
      }
      myfile.close();
   }

//    RebCorrection_vsReco_NVtx0_10->Rebin2D(2, 1);
//    RebCorrection_vsReco_NVtx11_20->Rebin2D(2, 1);
//    RebCorrection_vsReco_NVtx21_Inf->Rebin2D(2, 1);

   // ---------------------------------------------------- //
   // pythia
   TH1F* correction_vsReco = new TH1F();
   correction_vsReco = (TH1F*) RebCorrection_vsReco->ProjectionX();
   correction_vsReco->Reset();
   for (int i = 0; i <= RebCorrection_vsReco->GetXaxis()->GetNbins(); ++i) {
      TH1F h = *((TH1F*) RebCorrection_vsReco->ProjectionY("py", i, i));
            
      double mean = h.GetMean();
      double error = h.GetMeanError();

      cout << "i: " << i << " " << "mean: " << mean << " " << "error: " << error << endl;
            
      correction_vsReco->SetBinContent(i, mean);
      correction_vsReco->SetBinError(i, error);
   }

   // madgraph
   TH1F* correction_vsReco_madgraph = new TH1F();
   correction_vsReco_madgraph = (TH1F*) RebCorrection_vsReco_madgraph->ProjectionX();
   correction_vsReco_madgraph->Reset();
   for (int i = 0; i <= RebCorrection_vsReco_madgraph->GetXaxis()->GetNbins(); ++i) {
      TH1F h = *((TH1F*) RebCorrection_vsReco_madgraph->ProjectionY("py", i, i));
            
      double mean = h.GetMean();
      double error = h.GetMeanError();

      cout << "i: " << i << " " << "mean: " << mean << " " << "error: " << error << endl;
            
      correction_vsReco_madgraph->SetBinContent(i, mean);
      correction_vsReco_madgraph->SetBinError(i, error);
   }

   // pythia NVtx 0-10
   TH1F* correction_vsReco_NVtx0_10 = new TH1F();
   correction_vsReco_NVtx0_10 = (TH1F*) RebCorrection_vsReco_NVtx0_10->ProjectionX();
   correction_vsReco_NVtx0_10->Reset();
   for (int i = 0; i <= RebCorrection_vsReco_NVtx0_10->GetXaxis()->GetNbins(); ++i) {
      TH1F h = *((TH1F*) RebCorrection_vsReco_NVtx0_10->ProjectionY("py", i, i));
            
      double mean = h.GetMean();
      double error = h.GetMeanError();

      cout << "i: " << i << " " << "mean: " << mean << " " << "error: " << error << endl;
            
      correction_vsReco_NVtx0_10->SetBinContent(i, mean);
      correction_vsReco_NVtx0_10->SetBinError(i, error);
   }

   // pythia NVtx 11-20
   TH1F* correction_vsReco_NVtx11_20 = new TH1F();
   correction_vsReco_NVtx11_20 = (TH1F*) RebCorrection_vsReco_NVtx11_20->ProjectionX();
   correction_vsReco_NVtx11_20->Reset();
   for (int i = 0; i <= RebCorrection_vsReco_NVtx11_20->GetXaxis()->GetNbins(); ++i) {
      TH1F h = *((TH1F*) RebCorrection_vsReco_NVtx11_20->ProjectionY("py", i, i));
            
      double mean = h.GetMean();
      double error = h.GetMeanError();

      cout << "i: " << i << " " << "mean: " << mean << " " << "error: " << error << endl;
            
      correction_vsReco_NVtx11_20->SetBinContent(i, mean);
      correction_vsReco_NVtx11_20->SetBinError(i, error);
   }

   // pythia NVtx 21-Inf
   TH1F* correction_vsReco_NVtx21_Inf = new TH1F();
   correction_vsReco_NVtx21_Inf = (TH1F*) RebCorrection_vsReco_NVtx21_Inf->ProjectionX();
   correction_vsReco_NVtx21_Inf->Reset();
   for (int i = 0; i <= RebCorrection_vsReco_NVtx21_Inf->GetXaxis()->GetNbins(); ++i) {
      TH1F h = *((TH1F*) RebCorrection_vsReco_NVtx21_Inf->ProjectionY("py", i, i));
            
      double mean = h.GetMean();
      double error = h.GetMeanError();

      cout << "i: " << i << " " << "mean: " << mean << " " << "error: " << error << endl;
            
      correction_vsReco_NVtx21_Inf->SetBinContent(i, mean);
      correction_vsReco_NVtx21_Inf->SetBinError(i, error);
   }

   // ---------------------------------------------------- //

   TCanvas *c = new TCanvas("c", "", 700, 700);
   correction_vsReco->SetAxisRange(x_min, correction_vsReco->GetXaxis()->GetXmax());
   correction_vsReco->SetXTitle("reco jet p_{T} [GeV]");
   correction_vsReco->SetYTitle("reb jet p_{T} / gen jet p_{T} ");
   correction_vsReco->Draw();

   TPaveText* pt1 = new TPaveText(0.11, 0.9, 0.95, 0.86, "NDC");
   pt1->SetBorderSize(0);
   pt1->SetFillStyle(0);
   pt1->SetTextAlign(12);
   pt1->SetTextSize(0.03);
   pt1->AddText("CMS Simulation, #sqrt{s} = 8 TeV");
   pt1->Draw();

   c->Print(outfile + "_vsReco.ps");  
   c->Print(outfile + "_vsReco.png"); 

   // ---------------------------------------------------- //

   correction_vsReco_madgraph->SetAxisRange(x_min, correction_vsReco_madgraph->GetXaxis()->GetXmax());
   correction_vsReco_madgraph->SetXTitle("reco jet p_{T} [GeV]");
   correction_vsReco_madgraph->SetYTitle("reb jet p_{T} / gen jet p_{T} ");
   correction_vsReco_madgraph->Draw();

   pt1->Draw();

   c->Print(outfile + "_vsRecoMadgraph.ps");  
   c->Print(outfile + "_vsRecoMadgraph.png"); 

   // ---------------------------------------------------- //

   // ---------------------------------------------------- //

   correction_vsReco_NVtx0_10->SetAxisRange(x_min, correction_vsReco_madgraph->GetXaxis()->GetXmax());
   correction_vsReco_NVtx0_10->SetXTitle("reco jet p_{T} [GeV]");
   correction_vsReco_NVtx0_10->SetYTitle("reb jet p_{T} / gen jet p_{T} ");
   correction_vsReco_NVtx0_10->Draw();
   correction_vsReco_NVtx11_20->SetMarkerStyle(21);
   correction_vsReco_NVtx11_20->SetLineColor(kAzure-3);
   correction_vsReco_NVtx11_20->SetMarkerColor(kAzure-3);
   correction_vsReco_NVtx11_20->Draw("same");
   correction_vsReco_NVtx21_Inf->SetMarkerStyle(22);
   correction_vsReco_NVtx21_Inf->SetLineColor(kPink-3);
   correction_vsReco_NVtx21_Inf->SetMarkerColor(kPink-3);
   correction_vsReco_NVtx21_Inf->Draw("same");

   TLegend* leg = new TLegend(0.5, 0.65, 0.7, 0.82);
   leg->SetFillStyle(0);
   leg->SetLineStyle(1);
   leg->SetTextFont(42);
   leg->SetTextSize(0.04);
   leg->AddEntry(correction_vsReco_NVtx0_10, " 0 - 10 Vertices", "lep");
   leg->AddEntry(correction_vsReco_NVtx11_20, " 11 - 20 Vertices", "lep");
   leg->AddEntry(correction_vsReco_NVtx21_Inf, " > 20 Vertices", "lep");
   leg->Draw("same");

   pt1->Draw();

   c->Print(outfile + "_vsRecoNVtxSplit.ps");  
   c->Print(outfile + "_vsRecoNVtxSplit.png"); 

   // ---------------------------------------------------- //

   TPad *pad1 = new TPad("pad1a", "pad1a", 0, 0.35, 1, 1);
   //  pad1->SetLogy();
   pad1->SetBottomMargin(0);
   pad1->Draw();
   pad1->cd();
  
   correction_vsReco->SetXTitle("reco jet p_{T} [GeV]");
   correction_vsReco->SetTitleSize(0.07, "Y");
   correction_vsReco->SetTitleOffset(0.85, "Y");
   correction_vsReco->SetYTitle("f = reb jet p_{T} / gen jet p_{T} ");
   correction_vsReco->DrawCopy();
   correction_vsReco_madgraph->SetMarkerStyle(21);
   correction_vsReco_madgraph->SetLineColor(kAzure-3);
   correction_vsReco_madgraph->SetMarkerColor(kAzure-3);
   correction_vsReco_madgraph->Draw("same");
   
   // TLegend* leg1 = new TLegend(0.38, 0.53, 0.85, 0.73);
   TLegend* leg1 = new TLegend(0.38, 0.63, 0.85, 0.8);
   leg1->SetFillStyle(0);
   leg1->SetLineStyle(1);
   leg1->SetTextFont(42);
   leg1->SetTextSize(0.06);
   leg1->AddEntry(correction_vsReco, "Pythia QCD sample", "lep");
   leg1->AddEntry(correction_vsReco_madgraph, "Madgraph QCD sample", "lep");
   leg1->Draw("same");

   TPaveText* pt2 = new TPaveText(0.11, 0.98, 0.95, 0.86, "NDC");
   pt2->SetBorderSize(0);
   pt2->SetFillStyle(0);
   pt2->SetTextAlign(12);
   pt2->SetTextSize(0.045);
   pt2->AddText("");
   pt2->AddText("CMS Simulation, #sqrt{s} = 8 TeV");
   pt2->Draw();
 
   c->cd();
   TPad *pad2 = new TPad("pad2a", "pad2a", 0, 0, 1, 0.35);
   pad2->SetTopMargin(0);
   pad2->SetBottomMargin(0.3);
   pad2->Draw();
   pad2->cd();
   TH1F* r = new TH1F(*correction_vsReco);
   r->SetTitle("");
   r->SetLabelSize(0.075, "XYZ");
   r->SetLabelOffset(0.01, "XYZ");
   r->SetTitleSize(0.125, "XYZ");
   r->SetTitleOffset(0.95, "X");
   r->SetTitleOffset(0.53, "Y");
   r->SetTickLength(0.05);
   r->SetYTitle("#Delta f");
   r->SetStats(0);
   r->SetMarkerStyle(20);
   r->SetMarkerSize(0.7);
   r->SetMarkerColor(kBlack);
   r->Reset();
   r->Add(correction_vsReco, 1);
   r->Add(correction_vsReco_madgraph, -1);
   r->Divide(correction_vsReco_madgraph);
   r->SetMaximum(0.07);
   r->SetMinimum(-0.07);
   r->Draw("ep");
   TLine l;
   l.DrawLine(0., 0., 1000., 0.);
   c->cd();

   c->Print(outfile + "_vsRecoWithMadgraphComp.ps");  
   c->Print(outfile + "_vsRecoWithMadgraphComp.png"); 

   // ---------------------------------------------------- //

   TFile* RebalanceCorrection = new TFile("RebalanceCorrectionFactor/RebalanceCorrection_DR53X_withoutPUReweighting_" + pt + ".root", "RECREATE");
   correction_vsReco->Write();
   correction_vsReco_madgraph->Write();

   RebalanceCorrection->Write();
}


