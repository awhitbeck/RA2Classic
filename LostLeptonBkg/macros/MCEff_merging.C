#include <TH2F.h>
#include <TFile.h>
#include <TGraph.h>
#include <TGraphAsymmErrors.h>
#include <iostream>
#include "TStyle.h"
#include <ostream>
#include <TTree.h>
#include <TH1.h>
#include <TH3.h>
#include <TCanvas.h>


void MCEff_merging()
{
  gStyle->SetPaintTextFormat("5.2f"); 
    gStyle->SetTitleYOffset(2.2);
  gROOT->SetBatch(true);
  TFile* out = new TFile("MCEff.root","RECREATE");

  out->mkdir("Muon");
  out->mkdir("Electron");

  


  bool tapHTNjet =1;


//  out->mkdir("ttbar/Muon");
//  out->mkdir("ttbar/Electron");


  TDirectory *dMu = (TDirectory*)out->Get("Muon");
  TDirectory *dElec = (TDirectory*)out->Get("Electron");
  dMu->mkdir("IsoFitts");
  TDirectory *MuFit = (TDirectory*)dMu->Get("IsoFitts");


 // Open the input files

  TFile* fInput = TFile::Open("mc.root");
  TDirectory *dInput = (TDirectory*)fInput->Get("LostLeptonBkgMCEffCalculator");

 // second input file for uncertainty tag and probe efficiencies
//  TFile* fInputTagAndProbeMCmu = TFile::Open("fit_Muon_MC_Comb.root");
//  TDirectory *dInputTagAndProbeMCIsomu = (TDirectory*)fInputTagAndProbeMCmu->Get("muonEffs/ISO_emfdrjCalo_emfptRelCalo");
  TFile* fInputTagAndProbeMCmu = TFile::Open("MuMC.root");
  TDirectory *dInputTagAndProbeMCIsomu = (TDirectory*)fInputTagAndProbeMCmu->Get("tapTreeMuIso/MuId/fit_eff_plots");
  TDirectory *dInputTagAndProbeMCIsomuRelPT = (TDirectory*)fInputTagAndProbeMCmu->Get("tapTreeMuIso/MuIso_deltaR_RelPt/fit_eff_plots");
  TDirectory *dInputTagAndProbeMCIdmu = (TDirectory*)fInputTagAndProbeMCmu->Get("tapTreeMuId/MuId/fit_eff_plots");
  TDirectory *dInputTagAndProbeMCIdmuPT = (TDirectory*)fInputTagAndProbeMCmu->Get("tapTreeMuId/MuId_deltaR/fit_eff_plots");

  TFile* fInputTagAndProbeDatamu = TFile::Open("MuData.root");
  TDirectory *dInputTagAndProbeDataIsomu = (TDirectory*)fInputTagAndProbeDatamu->Get("tapTreeMuIso/MuId/fit_eff_plots");
  TDirectory *dInputTagAndProbeDataIsomuRelPT = (TDirectory*)fInputTagAndProbeDatamu->Get("tapTreeMuIso/MuIso_deltaR_RelPt/fit_eff_plots");
  TDirectory *dInputTagAndProbeDataIdmu = (TDirectory*)fInputTagAndProbeDatamu->Get("tapTreeMuId/MuId/fit_eff_plots");
  TDirectory *dInputTagAndProbeDataIdmuPT = (TDirectory*)fInputTagAndProbeDatamu->Get("tapTreeMuId/MuId_deltaR/fit_eff_plots");


  TFile* fInputTagAndProbeMCelec = TFile::Open("ElecMC.root");
  TDirectory *dInputTagAndProbeMCIsoelec = (TDirectory*)fInputTagAndProbeMCelec->Get("tapTreeElecIso/ElecIso/fit_eff_plots");
  TDirectory *dInputTagAndProbeMCIsoelecPT = (TDirectory*)fInputTagAndProbeMCelec->Get("tapTreeElecIso/ElecIso_deltaR/fit_eff_plots");
  TDirectory *dInputTagAndProbeMCIdelec = (TDirectory*)fInputTagAndProbeMCelec->Get("tapTreeElecIdGsf/ElecIdGsf/fit_eff_plots");
  TDirectory *dInputTagAndProbeMCIdelecPT = (TDirectory*)fInputTagAndProbeMCelec->Get("tapTreeElecIdGsf/ElecIdGsf_deltaR/fit_eff_plots");
  TDirectory *dInputTagAndProbeMCIdelecPT2 = (TDirectory*)fInputTagAndProbeMCelec->Get("tapTreeElecIdGsf/ElecIdGsf_Pt/fit_eff_plots");

  TFile* fInputTagAndProbeDataelec = TFile::Open("ElecData.root");
  TDirectory *dInputTagAndProbeDataIsoelec = (TDirectory*)fInputTagAndProbeDataelec->Get("tapTreeElecIso/ElecIso/fit_eff_plots");
  TDirectory *dInputTagAndProbeDataIsoelecPT = (TDirectory*)fInputTagAndProbeDataelec->Get("tapTreeElecIso/ElecIso_deltaR/fit_eff_plots");
  TDirectory *dInputTagAndProbeDataIdelec = (TDirectory*)fInputTagAndProbeDataelec->Get("tapTreeElecIdGsf/ElecIdGsf/fit_eff_plots");
  TDirectory *dInputTagAndProbeDataIdelecPT = (TDirectory*)fInputTagAndProbeDataelec->Get("tapTreeElecIdGsf/ElecIdGsf_deltaR/fit_eff_plots");
  TDirectory *dInputTagAndProbeDataIdelecPT2 = (TDirectory*)fInputTagAndProbeDataelec->Get("tapTreeElecIdGsf/ElecIdGsf_Pt/fit_eff_plots");

/*
  TFile* fInputTagAndProbeMCmuIso = TFile::Open("fit_Muon_MC_HT500_1000_1500.root");
  TDirectory *dInputTagAndProbeMCIsomuHTNJet = (TDirectory*)fInputTagAndProbeMCmuIso->Get("muonEffsID/ISO_HT_nJets/fit_eff_plots");

  TFile* fInputTagAndProbeMCmuReco = TFile::Open("fit_Muon_ID_MC_MuPtmin10_Feb14.root");
  TDirectory *dInputTagAndProbeMCRecomu = (TDirectory*)fInputTagAndProbeMCmuReco->Get("muonEffs/ID_emfdrjCalo_pt/fit_eff_plots");
  TH2F *mc_tap_eff_mu_iso = new TH2F;
  TH2F *mc_tap_eff_mu_reco = new TH2F;


  TFile* fInputTagAndProbeDatamu = TFile::Open("fit_Muon_Data_Comb.root");
  TDirectory *dInputTagAndProbeDataIsomu = (TDirectory*)fInputTagAndProbeDatamu->Get("muonEffs/ISO_emfdrjCalo_emfptRelCalo");

  TFile* fInputTagAndProbeDatamuIso = TFile::Open("fit_Muon_Data_HT500_1000_1500.root");
  TDirectory *dInputTagAndProbeDataIsomuHTNJet = (TDirectory*)fInputTagAndProbeDatamuIso->Get("muonEffsID/ISO_HT_nJets/fit_eff_plots");

  TFile* fInputTagAndProbeDatamuReco = TFile::Open("fit_Muon_ID_Data_MuPtmin10_Feb14.root");
  TDirectory *dInputTagAndProbeDataRecomu = (TDirectory*)fInputTagAndProbeDatamuReco->Get("muonEffs/ID_emfdrjCalo_pt/fit_eff_plots");
  TH2F *data_tap_eff_mu_iso = new TH2F;
  TH2F *data_tap_eff_mu_reco = new TH2F;
  TH2F *mc_tap_eff_mu_iso_HTNJet = new TH2F;
  TH2F *data_tap_eff_mu_iso_HTNJet = new TH2F;



  TFile* fInputTagAndProbeMCEleciso = TFile::Open("GsfElectronToIdMC.root");
  TFile* fInputTagAndProbeMCElecreco = TFile::Open("CMS Simulation, L=19.47 fb-1, sqrt(s)=8 TeV, efficiency-data-SCToGsfElectronMC.root");
  TDirectory *dInputTagAndProbeMCRecoElec = (TDirectory*)fInputTagAndProbeMCElecreco->Get("SuperClusterToGsfElectron/efficiency/fit_eff_plots");
  TDirectory *dInputTagAndProbeMCIsoElec = (TDirectory*)fInputTagAndProbeMCEleciso->Get("GsfElectronToId/WP85/fit_eff_plots");
  TH2F *mc_tap_eff_elec_reco = new TH2F;
  TH2F *mc_tap_eff_elec_iso = new TH2F;

  TFile* fInputTagAndProbeDataEleciso = TFile::Open("GsfElectronToIdData.root");
  TFile* fInputTagAndProbeDataElecreco = TFile::Open("CMS Simulation, L=19.47 fb-1, sqrt(s)=8 TeV, efficiency-data-SCToGsfElectronData.root");
  TDirectory *dInputTagAndProbeDataRecoElec = (TDirectory*)fInputTagAndProbeDataElecreco->Get("SuperClusterToGsfElectron/efficiency/fit_eff_plots");
  TDirectory *dInputTagAndProbeDataIsoElec = (TDirectory*)fInputTagAndProbeDataEleciso->Get("GsfElectronToId/WP85/fit_eff_plots");
  TH2F *data_tap_eff_elec_reco = new TH2F;
  TH2F *data_tap_eff_elec_iso = new TH2F;

*/
/*
  TFile* fInputTagAndProbeMCelec = TFile::Open("fit_Elec_MC_Comb.root");
  TDirectory *dInputTagAndProbeMCIsoelec = (TDirectory*)fInputTagAndProbeMCelec->"eleconEffs/ISO_emfdrjCalo_emfptRelCalo");
  TDirectory *dInputTagAndProbeMCRecoelec = (TDirectory*)fInputTagAndProbeMCelec->"eleconEffs/ID_emfdrjCalo_pt");
  TH2F *mc_tap_eff_elec_iso = new TH2F;
  TH2F *mc_tap_eff_elec_reco = new TH2F;

  TFile* fInputTagAndProbeDataelec = TFile::Open("fit_Elec_Data_Comb.root");
  TDirectory *dInputTagAndProbeDataIsoelec = (TDirectory*)fInputTagAndProbeDataelec->"eleconEffs/ISO_emfdrjCalo_emfptRelCalo");
  TDirectory *dInputTagAndProbeDataRecoelec = (TDirectory*)fInputTagAndProbeDataelec->"eleconEffs/ID_emfdrjCalo_pt");
  TH2F *mc_tap_eff_elec_iso = new TH2F;
  TH2F *data_tap_eff_elec_iso = new TH2F;
  TH2F *mc_tap_eff_elec_reco = new TH2F;
  TH2F *data_tap_eff_elec_reco = new TH2F;
*/

 // new Histogramms for output

  TH1F *muonAccSum = new TH1F();
  TH1F *muonAccPassed = new TH1F();
  TH1F *muonAccSum2 = new TH1F();
  TH1F *muonAccEff2 = new TH1F();
  TH2F *muonAccSum3 = new TH2F();
  TH2F *muonAccEff3 = new TH2F();

  TH2F *muonRecoSum = new TH2F();
  TH2F *muonRecoEff = new TH2F();
  TH2F *muonRecoSum2 = new TH2F();
  TH2F *muonRecoEff2 = new TH2F();

  TH2F *muonIsoSum = new TH2F();
  TH2F *muonIsoEff = new TH2F();
  TH2F *muonIsoSum2 = new TH2F();
  TH2F *muonIsoEff2 = new TH2F();
  
  TH2F *MTW = new TH2F();


  TH1F *elecAccSum = new TH1F();
  TH1F *elecAccPassed = new TH1F();
  TH1F *elecAccSum2 = new TH1F();
  TH1F *elecAccEff2 = new TH1F();
  TH2F *elecAccSum3 = new TH2F();
  TH2F *elecAccEff3 = new TH2F();

  TH2F *elecRecoSum = new TH2F();
  TH2F *elecRecoEff = new TH2F();
  TH2F *elecRecoSum2 = new TH2F();
  TH2F *elecRecoEff2 = new TH2F();

  TH2F *elecIsoSum = new TH2F();
  TH2F *elecIsoEff = new TH2F();
  TH2F *elecIsoSum2 = new TH2F();
  TH2F *elecIsoEff2 = new TH2F();


  TH3F *muonBinByBinSum = new TH3F();
  TH3F *muonBinByBinEff = new TH3F();
  TH3F *muonAccBinByBinSum = new TH3F();
  TH3F *muonAccBinByBinEff = new TH3F();
  TH3F *muonRecoBinByBinSum = new TH3F();
  TH3F *muonRecoBinByBinEff = new TH3F();
  TH3F *muonIsoBinByBinSum = new TH3F();
  TH3F *muonIsoBinByBinEff = new TH3F();

  TH3F *elecBinByBinSum = new TH3F();
  TH3F *elecBinByBinEff = new TH3F();
  TH3F *elecAccBinByBinSum = new TH3F();
  TH3F *elecAccBinByBinEff = new TH3F();
  TH3F *elecRecoBinByBinSum = new TH3F();
  TH3F *elecRecoBinByBinEff = new TH3F();
  TH3F *elecIsoBinByBinSum = new TH3F();
  TH3F *elecIsoBinByBinEff = new TH3F();

// iso htmht different njets
  TH2F *muonIsoBinByBinNJet35Sum = new TH2F();
  TH2F *muonIsoBinByBinNJet35Eff = new TH2F();
  TH2F *muonIsoBinByBinNJet67Sum = new TH2F();
  TH2F *muonIsoBinByBinNJet67Eff = new TH2F();
  TH2F *muonIsoBinByBinNJet8InfSum = new TH2F();
  TH2F *muonIsoBinByBinNJet8InfEff = new TH2F();

  TH2F *ElecIsoBinByBinNJet35Sum = new TH2F();
  TH2F *ElecIsoBinByBinNJet35Eff = new TH2F();
  TH2F *ElecIsoBinByBinNJet67Sum = new TH2F();
  TH2F *ElecIsoBinByBinNJet67Eff = new TH2F();
  TH2F *ElecIsoBinByBinNJet8InfSum = new TH2F();
  TH2F *ElecIsoBinByBinNJet8InfEff = new TH2F();

// reco htmht different njets
  TH2F *muonRecoBinByBinNJet35Sum = new TH2F();
  TH2F *muonRecoBinByBinNJet35Eff = new TH2F();
  TH2F *muonRecoBinByBinNJet67Sum = new TH2F();
  TH2F *muonRecoBinByBinNJet67Eff = new TH2F();
  TH2F *muonRecoBinByBinNJet8InfSum = new TH2F();
  TH2F *muonRecoBinByBinNJet8InfEff = new TH2F();

  TH2F *ElecRecoBinByBinNJet35Sum = new TH2F();
  TH2F *ElecRecoBinByBinNJet35Eff = new TH2F();
  TH2F *ElecRecoBinByBinNJet67Sum = new TH2F();
  TH2F *ElecRecoBinByBinNJet67Eff = new TH2F();
  TH2F *ElecRecoBinByBinNJet8InfSum = new TH2F();
  TH2F *ElecRecoBinByBinNJet8InfEff = new TH2F();

 ///////////////////////////// Muon ///////////////////////////////

  // store the Acc in the new files and do the ratio

  muonAccSum = (TH1F*)dInput->Get("muonAccFailed");
  muonAccSum->SetName("MuonAccSum");
  muonAccSum->Sumw2();
  muonAccSum->Add( (TH1F*)dInput->Get("muonAccPassed") );

  muonAccPassed = (TH1F*)dInput->Get("muonAccPassed");
  muonAccPassed->SetName("MuonAccPassed");
  muonAccPassed->Sumw2();

  TGraphAsymmErrors *muonAccRatio = new TGraphAsymmErrors(muonAccPassed,muonAccSum);
  muonAccRatio->SetName("MuonAccRatio");
  muonAccRatio->SetTitle("MuonAccRatio;MuonPT;Ratio;ZAxLabel");


 // second version of acceptance eff
  muonAccSum2 = (TH1F*)dInput->Get("muonAccFailed2");
  muonAccSum2->SetName("MuonAccSum2");
  muonAccSum2->Sumw2();
  muonAccSum2->Add( (TH1F*)dInput->Get("muonAccPassed2") );

  muonAccEff2 = (TH1F*)dInput->Get("muonAccPassed2");
  muonAccEff2->SetName("MuonAccEff2");
  muonAccEff2->SetTitle("CMS Simulation, L=19.47 fb-1, sqrt(s)=8 TeV, #mu acc. eff.;#slash{H}_{T} [GeV];eff.");
  muonAccEff2->Sumw2();
  muonAccEff2->Divide(muonAccEff2,muonAccSum2,1,1,"B");

std::cout<<"jup"<<std::endl;
 // third version of acceptance eff
  muonAccSum3 = (TH2F*)dInput->Get("MuonAccFailed3");
  muonAccSum3->SetName("MuonAccSum3");
  muonAccSum3->Sumw2();
  muonAccSum3->Add( (TH2F*)dInput->Get("MuonAccPassed3") );

  muonAccEff3 = (TH2F*)dInput->Get("MuonAccPassed3");
  muonAccEff3->SetName("MuonAccEff3");
  muonAccEff3->SetTitle("CMS Simulation, L=19.47 fb-1, sqrt(s)=8 TeV, #mu acc. eff.;#slash{H}_{T} [GeV];nJets");
  muonAccEff3->Sumw2();
  muonAccEff3->Divide(muonAccEff3,muonAccSum3,1,1,"B");

std::cout<<"stts"<<std::endl;

  // the reconstruciton

  muonRecoSum = (TH2F*)dInput->Get("MuonRecoFailed");
  muonRecoSum->SetName("TotalNumberMuonsAfterAcc");
  muonRecoSum->Sumw2();
  muonRecoSum->Add( ( TH2F*)dInput->Get("MuonRecoPassed") );

  muonRecoEff = (TH2F*)dInput->Get("MuonRecoPassed");
  muonRecoEff->SetName("MuonRecoEff");
  muonRecoEff->SetTitle("MuonRecoEff;DeltaR;RelPT;Eff.");
  muonRecoEff->Sumw2();
  muonRecoEff->Divide(muonRecoEff,muonRecoSum,1,1,"B");


  muonRecoSum2 = (TH2F*)dInput->Get("MuonRecoFailed2");
  muonRecoSum2->SetName("TotalNumberMuonsAfterAcc2");
  muonRecoSum2->Sumw2();
  muonRecoSum2->Add( ( TH2F*)dInput->Get("MuonRecoPassed2") );

  muonRecoEff2 = (TH2F*)dInput->Get("MuonRecoPassed2");
  muonRecoEff2->SetName("MuonRecoEff2");
  muonRecoEff2->SetTitle("CMS Simulation, L=19.47 fb-1, sqrt(s)=8 TeV, #mu reco. eff.; #Delta R;#mu p_{T};Eff.");
  muonRecoEff2->Sumw2();
  muonRecoEff2->Divide(muonRecoEff2,muonRecoSum2,1,1,"B");


  // muon isolation

	//fitting

  
  
  muonIsoSum = (TH2F*)dInput->Get("muonIsoFailed");
  muonIsoSum->SetName("TotalNumberMuonsAfterReco");
  muonIsoSum->Sumw2();
  muonIsoSum->Add( ( TH2F*)dInput->Get("muonIsoPassed") );

  muonIsoEff = (TH2F*)dInput->Get("muonIsoPassed");
  muonIsoEff->SetName("MuonIsoEff");
  muonIsoEff->SetTitle("MuonIsoEff;#delta R;RelPT;Eff.");
  muonIsoEff->Sumw2();
  muonIsoEff->Divide(muonIsoEff,muonIsoSum,1,1,"B");


  TTree * tree = (TTree*) dInput->Get("LostLeptonMCEff");

  const Int_t LepPtBins = muonIsoSum->GetNbinsY();

/*  TH1 *h1;
int ii=0;
  for (int i=1; i<LepPtBins;i++)
  {
   double down = muonIsoSum->GetYaxis()->GetBinLowEdge(i);
  double up = muonIsoSum->GetYaxis()->GetBinLowEdge(i+1);

TString low="";
low+=down;
TString high="";
high+=up;


  dInput->cd();
TCanvas *tc1= new TCanvas(low,low,1000,1000);
tc1->cd();
TH1 *h1= new TH1F("h1","h1",20,0,1); 
  tree->Draw("genDeltaR>>h1","(NJets >1 && nGenMu>0.2 && nIsoMu>0.5 && genDeltaR <1 && RecoLevelMuonRelPTJet>"+ low +" && RecoLevelMuonRelPTJet<"+high+")*Weight");
TH1 *h2= new TH1F("h2","h2",20,0,1);
  tree->Draw("genDeltaR>>h2","(NJets >1 && nGenMu>0.2 && nIsoMu<-0.5 && genDeltaR <1 && RecoLevelMuonRelPTJet>"+ low +" && RecoLevelMuonRelPTJet<"+high+")*Weight");
h2->Add(h1);
TH1 *hRatio= new TH1F("hRatio","hRatio",20,0,1);
  tree->Draw("genDeltaR>>hRatio","(NJets >1 && nGenMu>0.2 && nIsoMu>0.5 && genDeltaR <1 && RecoLevelMuonRelPTJet>"+ low +" && RecoLevelMuonRelPTJet<"+high+")*Weight");
hRatio->Divide(h2);
//h1->Fit("gaus");
tc1->Update();
std::cout<<"down"<<down<<", up"<<up<<std::endl;
std::cout<<"low"<<low<<", high"<<high<<std::endl;
low+="-";
low+=high;
low+=".eps";

tc1->SaveAs(low,"CMS Simulation, L=19.47 fb-1, sqrt(s)=8 TeV, eps");
high="";
low="";




  }
*/
/*

  const Int_t DeltaRBins = muonIsoSum->GetNbinsX();
  TH1 *h12;
  for (int i=1; i<DeltaRBins;i++)
  {

// second part
  double down2 = muonIsoSum->GetXaxis()->GetBinLowEdge(i);
  double up2 = muonIsoSum->GetXaxis()->GetBinLowEdge(i+1);

TString low2="";
low2+=down2;
TString high2="";
high2+=up2;


  dInput->cd();
TCanvas *tc12= new TCanvas(low2,low2,1000,1000);
tc12->cd();
TH1 *h12= new TH1F("h12","h12",30,0,3); 
  tree->Draw("RecoLevelMuonRelPTJet>>h12","(nGenMu>0.2 && nIsoMu>0.5 && RecoLevelMuonRelPTJet <3&& genDeltaR>"+ low2 +" && genDeltaR<"+high2+")*Weight");
TH1 *h22= new TH1F("h22","h22",30,0,3);
  tree->Draw("RecoLevelMuonRelPTJet>>h22","(nGenMu>0.2 && nIsoMu<-0.5 && RecoLevelMuonRelPTJet <3&& genDeltaR>"+ low2 +" && genDeltaR<"+high2+")*Weight");
h22->Add(h12);
TH1 *hRatio2= new TH1F("hRatio2","hRatio2",30,0,3);
  tree->Draw("RecoLevelMuonRelPTJet>>hRatio","(nGenMu>0.2 && nIsoMu>0.5 && RecoLevelMuonRelPTJet <3&& genDeltaR>"+ low2 +" && genDeltaR<"+high2+")*Weight");
hRatio2->Divide(h22);
//h1->Fit("gaus");
tc12->Update();
std::cout<<"down2"<<down2<<", up2"<<up2<<std::endl;
std::cout<<"low2"<<low2<<", high2"<<high2<<std::endl;
low2+="-";
low2+=high2;
low2+=".eps";

tc12->SaveAs(low2,"CMS Simulation, L=19.47 fb-1, sqrt(s)=8 TeV, eps");
high2="";
low2="";

  }
*/




  muonIsoSum2 = (TH2F*)dInput->Get("muonIsoFailed2");
  muonIsoSum2->SetName("TotalNumberMuonsAfterReco2");
  muonIsoSum2->Sumw2();
  muonIsoSum2->Add( ( TH2F*)dInput->Get("muonIsoPassed2") );

  muonIsoEff2 = (TH2F*)dInput->Get("muonIsoPassed2");
  muonIsoEff2->SetName("MuonIsoEff2");
  muonIsoEff2->SetTitle("CMS Simulation, L=19.47 fb-1, sqrt(s)=8 TeV, #mu iso. eff.; #Delta R;#mu p_{T};Eff.");
  muonIsoEff2->Sumw2();
  muonIsoEff2->Divide(muonIsoEff2,muonIsoSum2,1,1,"B");

  // MTW cut
  MTW = (TH2F*)dInput->Get("MTW");
  MTW->SetName("MTW");
  MTW->SetTitle("CMS Simulation, L=19.47 fb-1, sqrt(s)=8 TeV, MTW;MTW;MHT;Eff.");
  MTW->Sumw2();


   //bin by bin eff
  muonBinByBinSum = (TH3F*)dInput->Get("BinByBinEffMuFailed");
  muonBinByBinSum->SetName("BinByBinEffMuFailed");
  muonBinByBinSum->Sumw2();
  muonBinByBinSum->Add( ( TH3F*)dInput->Get("BinByBinEffMuPassed") );

  muonBinByBinEff = (TH3F*)dInput->Get("BinByBinEffMuPassed");
  muonBinByBinEff->SetName("MuonBinByBinEff");
  muonBinByBinEff->SetTitle("CMS Simulation, L=19.47 fb-1, sqrt(s)=8 TeV, #mu total eff; H_{T} [GeV];#slash{H}_{T} [GeV]; N_{Jets}");
  muonBinByBinEff->Sumw2();
  muonBinByBinEff->Divide(muonBinByBinSum);

// seperated
  muonAccBinByBinSum = (TH3F*)dInput->Get("AccBinByBinEffMuFailed");
  muonAccBinByBinSum->SetName("AccBinByBinEffMuFailed");
  muonAccBinByBinSum->Sumw2();
  muonAccBinByBinSum->Add( ( TH3F*)dInput->Get("AccBinByBinEffMuPassed") );

  muonAccBinByBinEff = (TH3F*)dInput->Get("AccBinByBinEffMuPassed");
  muonAccBinByBinEff->SetName("AccBinByBinMuEff");
  muonAccBinByBinEff->SetTitle("CMS Simulation, L=19.47 fb-1, sqrt(s)=8 TeV, #mu acc eff; H_{T} [GeV];#slash{H}_{T} [GeV]; N_{Jets}");
  muonAccBinByBinEff->Sumw2();
  muonAccBinByBinEff->Divide(muonAccBinByBinSum);


  muonRecoBinByBinSum = (TH3F*)dInput->Get("RecoBinByBinEffMuFailed");
  muonRecoBinByBinSum->SetName("RecoBinByBinMuFailed");
  muonRecoBinByBinSum->Sumw2();
  muonRecoBinByBinSum->Add( ( TH3F*)dInput->Get("RecoBinByBinEffMuPassed") );

  muonRecoBinByBinEff = (TH3F*)dInput->Get("RecoBinByBinEffMuPassed");
  muonRecoBinByBinEff->SetName("RecoBinByBinMuEff");
  muonRecoBinByBinEff->SetTitle("CMS Simulation, L=19.47 fb-1, sqrt(s)=8 TeV, #mu Reco eff; H_{T} [GeV];#slash{H}_{T} [GeV]; N_{Jets}");
  muonRecoBinByBinEff->Sumw2();
  muonRecoBinByBinEff->Divide(muonRecoBinByBinSum);


  muonIsoBinByBinSum = (TH3F*)dInput->Get("IsoBinByBinEffMuFailed");
  muonIsoBinByBinSum->SetName("IsoBinByBinMuFailed");
  muonIsoBinByBinSum->Sumw2();
  muonIsoBinByBinSum->Add( ( TH3F*)dInput->Get("IsoBinByBinEffMuPassed") );

  muonIsoBinByBinEff = (TH3F*)dInput->Get("IsoBinByBinEffMuPassed");
  muonIsoBinByBinEff->SetName("IsoBinByBinMuEff");
  muonIsoBinByBinEff->SetTitle("CMS Simulation, L=19.47 fb-1, sqrt(s)=8 TeV, #mu Iso eff; H_{T} [GeV];#slash{H}_{T} [GeV]; N_{Jets}");
  muonIsoBinByBinEff->Sumw2();
  muonIsoBinByBinEff->Divide(muonIsoBinByBinSum);

	// sperately binning for each nJet region

  muonIsoBinByBinNJet35Sum = (TH2F*) dInput->Get("isoEffTH2FailedMuNJet35");
  muonIsoBinByBinNJet35Sum->Sumw2();
  muonIsoBinByBinNJet35Sum->Add( (TH2F*)dInput->Get("isoEffTH2PassedMuNJet35") );
  
  muonIsoBinByBinNJet35Eff = (TH2F*)dInput->Get("isoEffTH2PassedMuNJet35");
  muonIsoBinByBinNJet35Eff->SetName("IsoHTMHTMuEffNJet_35");
  muonIsoBinByBinNJet35Eff->SetTitle("CMS Simulation, L=19.47 fb-1, sqrt(s)=8 TeV, #mu Iso eff 3 #leqN_{Jets} #leq5; H_{T} [GeV];#slash{H}_{T} [GeV]");
  muonIsoBinByBinNJet35Eff->Sumw2();
  muonIsoBinByBinNJet35Eff->Divide(muonIsoBinByBinNJet35Eff,muonIsoBinByBinNJet35Sum,1,1,"B");


  muonIsoBinByBinNJet67Sum = (TH2F*) dInput->Get("isoEffTH2FailedMuNJet67");
  muonIsoBinByBinNJet67Sum->Sumw2();
  muonIsoBinByBinNJet67Sum->Add( (TH2F*)dInput->Get("isoEffTH2PassedMuNJet67") );
  
  muonIsoBinByBinNJet67Eff = (TH2F*)dInput->Get("isoEffTH2PassedMuNJet67");
  muonIsoBinByBinNJet67Eff->SetName("IsoHTMHTMuEffNJet_67");
  muonIsoBinByBinNJet67Eff->SetTitle("CMS Simulation, L=19.47 fb-1, sqrt(s)=8 TeV, #mu Iso eff 6 #leqN_{Jets} #leq7; H_{T} [GeV];#slash{H}_{T} [GeV]");
  muonIsoBinByBinNJet67Eff->Sumw2();
  muonIsoBinByBinNJet67Eff->Divide(muonIsoBinByBinNJet67Eff,muonIsoBinByBinNJet67Sum,1,1,"B");


  muonIsoBinByBinNJet8InfSum = (TH2F*) dInput->Get("isoEffTH2FailedMuNJet8Inf");
  muonIsoBinByBinNJet8InfSum->Sumw2();
  muonIsoBinByBinNJet8InfSum->Add( (TH2F*)dInput->Get("isoEffTH2PassedMuNJet8Inf") );
  
  muonIsoBinByBinNJet8InfEff = (TH2F*)dInput->Get("isoEffTH2PassedMuNJet8Inf");
  muonIsoBinByBinNJet8InfEff->SetName("IsoHTMHTMuEffNJet_8Inf");
  muonIsoBinByBinNJet8InfEff->SetTitle("CMS Simulation, L=19.47 fb-1, sqrt(s)=8 TeV, #mu Iso eff 8 #leqN_{Jets}; H_{T} [GeV];#slash{H}_{T} [GeV]");
  muonIsoBinByBinNJet8InfEff->Sumw2();
  muonIsoBinByBinNJet8InfEff->Divide(muonIsoBinByBinNJet8InfEff,muonIsoBinByBinNJet8InfSum,1,1,"B");



  muonRecoBinByBinNJet35Sum = (TH2F*) dInput->Get("recoEffTH2FailedMuNJet35");
  muonRecoBinByBinNJet35Sum->Sumw2();
  muonRecoBinByBinNJet35Sum->Add( (TH2F*)dInput->Get("recoEffTH2PassedMuNJet35") );
  
  muonRecoBinByBinNJet35Eff = (TH2F*)dInput->Get("recoEffTH2PassedMuNJet35");
  muonRecoBinByBinNJet35Eff->SetName("RecoHTMHTMuEffNJet_35");
  muonRecoBinByBinNJet35Eff->SetTitle("CMS Simulation, L=19.47 fb-1, sqrt(s)=8 TeV, #mu Reco eff 3 #leqN_{Jets} #leq 5; H_{T} [GeV];#slash{H}_{T} [GeV]");
  muonRecoBinByBinNJet35Eff->Sumw2();
  muonRecoBinByBinNJet35Eff->Divide(muonRecoBinByBinNJet35Eff,muonRecoBinByBinNJet35Sum,1,1,"B");


  muonRecoBinByBinNJet67Sum = (TH2F*) dInput->Get("recoEffTH2FailedMuNJet67");
  muonRecoBinByBinNJet67Sum->Sumw2();
  muonRecoBinByBinNJet67Sum->Add( (TH2F*)dInput->Get("recoEffTH2PassedMuNJet67") );
  
  muonRecoBinByBinNJet67Eff = (TH2F*)dInput->Get("recoEffTH2PassedMuNJet67");
  muonRecoBinByBinNJet67Eff->SetName("RecoHTMHTMuEffNJet_67");
  muonRecoBinByBinNJet67Eff->SetTitle("CMS Simulation, L=19.47 fb-1, sqrt(s)=8 TeV, #mu Reco eff 6 #leq N_{Jets} #leq 7; H_{T} [GeV];#slash{H}_{T} [GeV]");
  muonRecoBinByBinNJet67Eff->Sumw2();
  muonRecoBinByBinNJet67Eff->Divide(muonRecoBinByBinNJet67Eff,muonRecoBinByBinNJet67Sum,1,1,"B");


  muonRecoBinByBinNJet8InfSum = (TH2F*) dInput->Get("recoEffTH2FailedMuNJet8Inf");
  muonRecoBinByBinNJet8InfSum->Sumw2();
  muonRecoBinByBinNJet8InfSum->Add( (TH2F*)dInput->Get("recoEffTH2PassedMuNJet8Inf") );
  
  muonRecoBinByBinNJet8InfEff = (TH2F*)dInput->Get("recoEffTH2PassedMuNJet8Inf");
  muonRecoBinByBinNJet8InfEff->SetName("RecoHTMHTMuEffNJet_8Inf");
  muonRecoBinByBinNJet8InfEff->SetTitle("CMS Simulation, L=19.47 fb-1, sqrt(s)=8 TeV, #mu Reco eff 8 #leq N_{Jets}; H_{T} [GeV];#slash{H}_{T} [GeV]");
  muonRecoBinByBinNJet8InfEff->Sumw2();
  muonRecoBinByBinNJet8InfEff->Divide(muonRecoBinByBinNJet8InfEff,muonRecoBinByBinNJet8InfSum,1,1,"B");



   // tag and probe uncertainty eff.
/*
  mc_tap_eff_mu_iso =  (TH2F*) dInputTagAndProbeMCIsomu->Get("probe_emfdrjCalo_probe_emfptRelCalo_PLOT");
  mc_tap_eff_mu_iso->SetName("MC_TAP_mu_iso_eff");
  mc_tap_eff_mu_iso->SetTitle("CMS Simulation, L=19.47 fb-1, sqrt(s)=8 TeV, #mu Iso MC T&P eff; #Delta R;#mu p_{T}/jet p_{T};Eff");

  data_tap_eff_mu_iso =  (TH2F*) dInputTagAndProbeDataIsomu->Get("probe_emfdrjCalo_probe_emfptRelCalo_PLOT");
  data_tap_eff_mu_iso->SetName("Data_TAP_mu_iso_eff");
  data_tap_eff_mu_iso->SetTitle("CMS Simulation, L=19.47 fb-1, sqrt(s)=8 TeV, #mu Iso Data T&P eff; #Delta R;#mu p_{T}/jet p_{T};Eff");

  mc_tap_eff_mu_reco =  (TH2F*) dInputTagAndProbeMCRecomu->Get("probe_emfdrjCalo_probe_pt_PLOT");
  mc_tap_eff_mu_reco->SetName("MC_TAP_mu_reco_eff");
  mc_tap_eff_mu_reco->SetTitle("CMS Simulation, L=19.47 fb-1, sqrt(s)=8 TeV, #mu Reco MC T&P eff; #Delta R;#mu p_{T};Eff");

  data_tap_eff_mu_reco =  (TH2F*) dInputTagAndProbeDataRecomu->Get("probe_emfdrjCalo_probe_pt_PLOT");
  data_tap_eff_mu_reco->SetName("Data_TAP_mu_reco_eff");
  data_tap_eff_mu_reco->SetTitle("CMS Simulation, L=19.47 fb-1, sqrt(s)=8 TeV, #mu Reco Data T&P eff; #Delta R;#mu p_{T};Eff");
*/
  TCanvas* TMC00 = (TCanvas*)dInputTagAndProbeMCIsomu->Get("HT_NJets_PLOT")->Clone();
  mc_tap_eff_mu_iso = (TH2F*)TMC00->GetPrimitive("HT_NJets_PLOT")->Clone();
  mc_tap_eff_mu_iso->SetName("MC_TAP_mu_iso_eff");
  mc_tap_eff_mu_iso->SetTitle("CMS Simulation, L=19.47 fb-1, sqrt(s)=8 TeV, #mu Iso MC T&P eff; H_{T} [GeV];NJet;Eff");

  TCanvas* TMCXX = (TCanvas*)dInputTagAndProbeMCIsomuRelPT->Get("MuIsoDeltaR30GeVJet_MuIsoRelPT30GeVJet_PLOT")->Clone();
  mc_TAP_mu_iso_eff_deltaR_relPT = (TH2F*)TMCXX->GetPrimitive("MuIsoDeltaR30GeVJet_MuIsoRelPT30GeVJet_PLOT")->Clone();
  mc_TAP_mu_iso_eff_deltaR_relPT->SetName("MC_TAP_mu_iso_eff_deltaR_relPT");
  mc_TAP_mu_iso_eff_deltaR_relPT->SetTitle("CMS Simulation, L=19.47 fb-1, sqrt(s)=8 TeV, #mu Iso MC T&P eff; #Delta R; #mu p_{T}/ Jet p_{T};Eff");


  TCanvas* TMC11 = (TCanvas*)dInputTagAndProbeDataIsomu->Get("HT_NJets_PLOT")->Clone();
  data_tap_eff_mu_iso = (TH2F*)TMC11->GetPrimitive("HT_NJets_PLOT")->Clone();
  data_tap_eff_mu_iso->SetName("Data_TAP_mu_iso_eff");
  data_tap_eff_mu_iso->SetTitle("CMS Preliminary, L=19.47 fb-1, sqrt(s)=8 TeV, #mu Iso Data T&P eff; H_{T} [GeV];NJet;Eff");

  TCanvas* TMCZZ = (TCanvas*)dInputTagAndProbeDataIsomuRelPT->Get("MuIsoDeltaR30GeVJet_MuIsoRelPT30GeVJet_PLOT")->Clone();
  data_TAP_mu_iso_eff_deltaR_relPT = (TH2F*)TMCZZ->GetPrimitive("MuIsoDeltaR30GeVJet_MuIsoRelPT30GeVJet_PLOT")->Clone();
  data_TAP_mu_iso_eff_deltaR_relPT->SetName("Data_TAP_mu_iso_eff_deltaR_relPT");
  data_TAP_mu_iso_eff_deltaR_relPT->SetTitle("CMS Preliminary, L=19.47 fb-1, sqrt(s)=8 TeV, #mu Iso Data T&P eff; #Delta R; #mu p_{T}/ Jet p_{T};Eff");


  TCanvas* TMC00 = (TCanvas*)dInputTagAndProbeMCIdmu->Get("HT_NJets_PLOT")->Clone();
  mc_tap_eff_mu_reco = (TH2F*)TMC00->GetPrimitive("HT_NJets_PLOT")->Clone();
  mc_tap_eff_mu_reco->SetName("MC_TAP_mu_reco_eff");
  mc_tap_eff_mu_reco->SetTitle("CMS Simulation, L=19.47 fb-1, sqrt(s)=8 TeV, #mu Reco MC T&P eff; H_{T} [GeV];NJet;Eff");

  TCanvas* TMC00a = (TCanvas*)dInputTagAndProbeMCIdmuPT->Get("MuIdDeltaR30GeVJet_MuIdProbePt_PLOT")->Clone();
  mc_tap_eff_mu_reco_deltaR_PT = (TH2F*)TMC00a->GetPrimitive("MuIdDeltaR30GeVJet_MuIdProbePt_PLOT")->Clone();
  mc_tap_eff_mu_reco_deltaR_PT->SetName("MC_TAP_mu_reco_eff_deltaR_PT");
  mc_tap_eff_mu_reco_deltaR_PT->SetTitle("CMS Simulation, L=19.47 fb-1, sqrt(s)=8 TeV, #mu Reco MC T&P eff; #Delta R; #mu p_{T};Eff");


  TCanvas* TMC11 = (TCanvas*)dInputTagAndProbeDataIdmu->Get("HT_NJets_PLOT")->Clone();
  data_tap_eff_mu_reco = (TH2F*)TMC11->GetPrimitive("HT_NJets_PLOT")->Clone();
  data_tap_eff_mu_reco->SetName("Data_TAP_mu_reco_eff");
  data_tap_eff_mu_reco->SetTitle("CMS Preliminary, L=19.47 fb-1, sqrt(s)=8 TeV, #mu Reco Data T&P eff; H_{T} [GeV];NJet;Eff");

  TCanvas* TMC11a = (TCanvas*)dInputTagAndProbeDataIdmuPT->Get("MuIdDeltaR30GeVJet_MuIdProbePt_PLOT")->Clone();
  data_tap_eff_mu_reco_deltaR_PT = (TH2F*)TMC11a->GetPrimitive("MuIdDeltaR30GeVJet_MuIdProbePt_PLOT")->Clone();
  data_tap_eff_mu_reco_deltaR_PT->SetName("Data_TAP_mu_reco_eff_deltaR_PT");
  data_tap_eff_mu_reco_deltaR_PT->SetTitle("CMS Preliminary, L=19.47 fb-1, sqrt(s)=8 TeV, #mu Reco Data T&P eff; #Delta R; #mu p_{T};Eff");


/*
if (tapHTNjet)
  {
  TCanvas* TMC = (TCanvas*)dInputTagAndProbeMCIsomuHTNJet->Get("probe_HT_probe_nJets_PLOT")->Clone();
  mc_tap_eff_mu_iso_HTNJet = (TH2F*)TMC->GetPrimitive("probe_HT_probe_nJets_PLOT")->Clone();
  mc_tap_eff_mu_iso_HTNJet->SetName("MC_TAP_mu_iso_eff_HT N_{Jets}");
  mc_tap_eff_mu_iso_HTNJet->SetTitle("CMS Simulation, L=19.47 fb-1, sqrt(s)=8 TeV, #mu Iso MC T&P eff; H_{T} [GeV];NJet;Eff");


  TCanvas* TMC2 = (TCanvas*)dInputTagAndProbeDataIsomuHTNJet->Get("probe_HT_probe_nJets_PLOT")->Clone();
  data_tap_eff_mu_iso_HTNJet = (TH2F*)TMC2->GetPrimitive("probe_HT_probe_nJets_PLOT")->Clone();
  data_tap_eff_mu_iso_HTNJet->SetName("Data_TAP_mu_iso_eff_HT N_{Jets}");
  data_tap_eff_mu_iso_HTNJet->SetTitle("CMS Simulation, L=19.47 fb-1, sqrt(s)=8 TeV, #mu Iso Data T&P eff; H_{T} [GeV];NJet;Eff");



  }
*/

   // create MTW TH2s
	double hTBins []={500,800,1000,1500};
	int HTBins = 3;
	double mHTBins []={200,400,600,1500};
	int MHTBins = 3;
	double nJets []={3,6,8,14};
  	int NJets = 3;


  TH2F *mtwCutHTMHT= new TH2F ("MTWCutHTMHT","MTW cut eff.",HTBins,hTBins,MHTBins,mHTBins);
  mtwCutHTMHT->SetTitle("CMS Simulation, L=19.47 fb-1, sqrt(s)=8 TeV MTW cut eff; H_{T} [GeV];#slash{H}_{T} [GeV];Eff");
// good error calculation
//  TH2F mtwCutHTMHTPass= new TH2F ("MTWCutHTMHT","MTW cut eff.",HTBins,hTBins,MHTBins,mHTBins);
//mtwCutHTMHTPass->Sumw2();
  //mtwCutHTMHTPass->SetTitle("MTW cut eff; H_{T} [GeV];#slash{H}_{T} [GeV];Eff");
//  TH2F mtwCutHTMHTAll= new TH2F ("MTWCutHTMHT","MTW cut eff.",HTBins,hTBins,MHTBins,mHTBins);
//mtwCutHTMHTAll->Sumw2();
  //mtwCutHTMHTAll->SetTitle("MTW cut eff; H_{T} [GeV];#slash{H}_{T} [GeV];Eff");


  TH1F *mtwCutNJet= new TH1F("MTWCutNJet","CMS Simulation, L=19.47 fb-1, sqrt(s)=8 TeV MTW cut eff.",NJets,nJets);
  mtwCutNJet->SetTitle("CMS Simulation, L=19.47 fb-1, sqrt(s)=8 TeV, MTW cut eff;NJet;Eff");
// good error calculation
  TH1F *mtwCutNJetPass= new TH1F("MTWCutNJet","CMS Simulation, L=19.47 fb-1, sqrt(s)=8 TeV MTW cut eff.",NJets,nJets);
mtwCutNJetPass->Sumw2();
  mtwCutNJetPass->SetTitle("CMS Simulation, L=19.47 fb-1, sqrt(s)=8 TeV, MTW cut eff;NJet;Eff");
  TH1F *mtwCutNJetAll= new TH1F("MTWCutNJet","CMS Simulation, L=19.47 fb-1, sqrt(s)=8 TeV MTW cut eff.",NJets,nJets);
mtwCutNJetAll->Sumw2();
  mtwCutNJetAll->SetTitle("CMS Simulation, L=19.47 fb-1, sqrt(s)=8 TeV, MTW cut eff;NJet;Eff");
  


gROOT->SetBatch(true);
  TTree *tEff = new TTree();
  tEff = (TTree*) dInput->Get("LostLeptonMCEff");
   double pass = 0;
   double all = 0;
   double error =0;
   tEff->Draw("HT>> outhist2","(nIsoMu==1 && MTW < 100 &&MHT>200 + NJets>2.1 && HT >500)","pe");
  pass = outhist2->Integral();
   tEff->Draw("HT>> outhist2","(nIsoMu==1 && MHT>200 + NJets>2.1 && HT >500)","pe");
  all = outhist2->Integral();
  std::cout<<"Baseline MTW pass"<<pass<<std::endl;
  std::cout<<"Baseline MTW total"<<all<<std::endl;
  std::cout<<"Baseline MTW eff"<<pass/all<<std::endl;

// loop over bins

  tEff->Draw("HT>> outhist2","(nIsoMu==1 && MTW < 100 && MHT <400 && MHT>200 && HT < 800 && HT >500 && NJets>2.1)","pe");
  pass = outhist2->Integral();
  tEff->Draw("HT>> outhist2","(nIsoMu==1 && MHT <400 && MHT>200 && HT < 800 && HT >500 && NJets>2.1)","pe");
  all = outhist2->Integral();
  std::cout<<"Baseline MTW eff"<<pass/all<<std::endl;
  mtwCutHTMHT->SetBinContent(1,1,pass/all);
  //mtwCutHTMHTPass->SetBinContent(1,1,pass);
  //mtwCutHTMHTAll->SetBinContent(1,1,all);
  error = sqrt(  (1/all * sqrt(pass)) * (1/all * sqrt(pass))   + (pass/(all * all) * sqrt(all)) * (pass/(all * all) * sqrt(all)) );
  error = sqrt( pass/all *( 1 - pass/all) / all );
  mtwCutHTMHT->SetBinError(1,1,error);



  tEff->Draw("HT>> outhist2","(nIsoMu==1 && MTW < 100 && MHT <400 && MHT>200 && HT < 1000 && HT >800 && NJets>2.1)","pe");
  pass = outhist2->Integral();
  tEff->Draw("HT>> outhist2","(nIsoMu==1 && MHT <400 && MHT>200 && HT < 1000 && HT >800 && NJets>2.1)","pe");
  all = outhist2->Integral();
  std::cout<<"Baseline MTW eff"<<pass/all<<std::endl;
  mtwCutHTMHT->SetBinContent(2,1,pass/all);
  //mtwCutHTMHTPass->SetBinContent(2,1,pass);
  //mtwCutHTMHTAll->SetBinContent(2,1,all);
  error = sqrt(  (1/all * sqrt(pass)) * (1/all * sqrt(pass))   + (pass/(all * all) * sqrt(all)) * (pass/(all * all) * sqrt(all)) );
  error = sqrt( pass/all *( 1 - pass/all) / all );
  mtwCutHTMHT->SetBinError(2,1,error);



  tEff->Draw("HT>> outhist2","(nIsoMu==1 && MTW < 100 && MHT <400 && MHT>200 && HT < 9000 && HT > 1000 && NJets>2.1)","pe");
  pass = outhist2->Integral();
  tEff->Draw("HT>> outhist2","(nIsoMu==1 && MHT <400 && MHT>200 && HT < 9000 && HT >1000 && NJets>2.1)","pe");
  all = outhist2->Integral();
  std::cout<<"Baseline MTW eff"<<pass/all<<std::endl;
  mtwCutHTMHT->SetBinContent(3,1,pass/all);
  //mtwCutHTMHTPass->SetBinContent(3,1,pass);
  //mtwCutHTMHTAll->SetBinContent(3,1,all);
  error = sqrt(  (1/all * sqrt(pass)) * (1/all * sqrt(pass))   + (pass/(all * all) * sqrt(all)) * (pass/(all * all) * sqrt(all)) );
  error = sqrt( pass/all *( 1 - pass/all) / all );
  mtwCutHTMHT->SetBinError(3,1,error);

  std::cout<<"NEXT";




  tEff->Draw("HT>> outhist2","(nIsoMu==1 && MTW < 100 && MHT <600 && MHT>400 && HT < 800 && HT >500 && NJets>2.1)","pe");
  pass = outhist2->Integral();
  tEff->Draw("HT>> outhist2","(nIsoMu==1 && MHT <600 && MHT>400 && HT < 800 && HT >500 && NJets>2.1)","pe");
  all = outhist2->Integral();
  std::cout<<"Baseline MTW eff"<<pass/all<<std::endl;
  mtwCutHTMHT->SetBinContent(1,2,pass/all);
  //mtwCutHTMHTPass->SetBinContent(1,2,pass);
  //mtwCutHTMHTAll->SetBinContent(1,2,all);
  error = sqrt(  (1/all * sqrt(pass)) * (1/all * sqrt(pass))   + (pass/(all * all) * sqrt(all)) * (pass/(all * all) * sqrt(all)) );
  error = sqrt( pass/all *( 1 - pass/all) / all );
  mtwCutHTMHT->SetBinError(1,2,error);



  tEff->Draw("HT>> outhist2","(nIsoMu==1 && MTW < 100 && MHT <600 && MHT>400 && HT < 1000 && HT >800 && NJets>2.1)","pe");
  pass = outhist2->Integral();
  tEff->Draw("HT>> outhist2","(nIsoMu==1 && MHT <600 && MHT>400 && HT < 1000 && HT >800 && NJets>2.1)","pe");
  all = outhist2->Integral();
  std::cout<<"Baseline MTW eff"<<pass/all<<std::endl;
  mtwCutHTMHT->SetBinContent(2,2,pass/all);
  //mtwCutHTMHTPass->SetBinContent(2,2,pass);
  //mtwCutHTMHTAll->SetBinContent(2,2,all);
  error = sqrt(  (1/all * sqrt(pass)) * (1/all * sqrt(pass))   + (pass/(all * all) * sqrt(all)) * (pass/(all * all) * sqrt(all)) );
  error = sqrt( pass/all *( 1 - pass/all) / all );
  mtwCutHTMHT->SetBinError(2,2,error);



  tEff->Draw("HT>> outhist2","(nIsoMu==1 && MTW < 100 && MHT <600 && MHT>400 && HT < 9000 && HT > 1000 && NJets>2.1)","pe");
  pass = outhist2->Integral();
  tEff->Draw("HT>> outhist2","(nIsoMu==1 && MHT <600 && MHT>400 && HT < 9000 && HT >1000 && NJets>2.1)","pe");
  all = outhist2->Integral();
  std::cout<<"Baseline MTW eff"<<pass/all<<std::endl;
  mtwCutHTMHT->SetBinContent(3,2,pass/all);
  //mtwCutHTMHTPass->SetBinContent(3,2,pass);
  //mtwCutHTMHTAll->SetBinContent(3,2,all);
  error = sqrt(  (1/all * sqrt(pass)) * (1/all * sqrt(pass))   + (pass/(all * all) * sqrt(all)) * (pass/(all * all) * sqrt(all)) );
  error = sqrt( pass/all *( 1 - pass/all) / all );
  mtwCutHTMHT->SetBinError(3,2,error);




  std::cout<<"NEXT";




  tEff->Draw("HT>> outhist2","(nIsoMu==1 && MTW < 100 && MHT <9000 && MHT>600 && HT < 800 && HT >500 && NJets>2.1)","pe");
  pass = outhist2->Integral();
  tEff->Draw("HT>> outhist2","(nIsoMu==1 && MHT <9000 && MHT>600 && HT < 800 && HT >500 && NJets>2.1)","pe");
  all = outhist2->Integral();
  std::cout<<"Baseline MTW eff"<<pass/all<<std::endl;
  mtwCutHTMHT->SetBinContent(1,3,pass/all);
  //mtwCutHTMHTPass->SetBinContent(1,3,pass);
  //mtwCutHTMHTAll->SetBinContent(1,3,all);
  error = sqrt(  (1/all * sqrt(pass)) * (1/all * sqrt(pass))   + (pass/(all * all) * sqrt(all)) * (pass/(all * all) * sqrt(all)) );
  error = sqrt( pass/all *( 1 - pass/all) / all );
  mtwCutHTMHT->SetBinError(1,3,error);



  tEff->Draw("HT>> outhist2","(nIsoMu==1 && MTW < 100 && MHT <9000 && MHT>600 && HT < 1000 && HT >800 && NJets>2.1)","pe");
  pass = outhist2->Integral();
  tEff->Draw("HT>> outhist2","(nIsoMu==1 && MHT <9000 && MHT>600 && HT < 1000 && HT >800 && NJets>2.1)","pe");
  all = outhist2->Integral();
  std::cout<<"Baseline MTW eff"<<pass/all<<std::endl;
  mtwCutHTMHT->SetBinContent(2,3,pass/all);
  //mtwCutHTMHTPass->SetBinContent(2,3,pass);
  //mtwCutHTMHTAll->SetBinContent(2,3,all);
  error = sqrt(  (1/all * sqrt(pass)) * (1/all * sqrt(pass))   + (pass/(all * all) * sqrt(all)) * (pass/(all * all) * sqrt(all)) );
  error = sqrt( pass/all *( 1 - pass/all) / all );
  mtwCutHTMHT->SetBinError(2,3,error);



  tEff->Draw("HT>> outhist2","(nIsoMu==1 && MTW < 100 && MHT <9000 && MHT>600 && HT < 9000 && HT > 1000 && NJets>2.1)","pe");
  pass = outhist2->Integral();
  tEff->Draw("HT>> outhist2","(nIsoMu==1 && MHT <9000 && MHT>600 && HT < 9000 && HT >1000 && NJets>2.1)","pe");
  all = outhist2->Integral();
  std::cout<<"Baseline MTW eff"<<pass/all<<std::endl;
  mtwCutHTMHT->SetBinContent(3,3,pass/all);
  //mtwCutHTMHTPass->SetBinContent(3,3,pass);
  //mtwCutHTMHTAll->SetBinContent(3,3,all);
  error = sqrt(  (1/all * sqrt(pass)) * (1/all * sqrt(pass))   + (pass/(all * all) * sqrt(all)) * (pass/(all * all) * sqrt(all)) );
  error = sqrt( pass/all *( 1 - pass/all) / all );
  mtwCutHTMHT->SetBinError(3,3,error);

// njets

 tEff->Draw("HT>> outhist2","(nIsoMu==1 && MTW < 100 && MHT>200 && HT >500 && NJets < 5.9 && NJets> 2.1)","pe");
  pass = outhist2->Integral();
  tEff->Draw("HT>> outhist2","(nIsoMu==1  && MHT>200 && HT >500 && NJets < 5.9 && NJets> 2.1)","pe");
  all = outhist2->Integral();
  std::cout<<"Baseline MTW eff"<<pass/all<<std::endl;
  mtwCutNJet->SetBinContent(1,pass/all);
  mtwCutNJetPass->SetBinContent(1,pass);
  mtwCutNJetAll->SetBinContent(1,all);
  error = sqrt(  (1/all * sqrt(pass)) * (1/all * sqrt(pass))   + (pass/(all * all) * sqrt(all)) * (pass/(all * all) * sqrt(all)) );
  error = sqrt( pass/all *( 1 - pass/all) / all );
  mtwCutNJet->SetBinError(1,error);



 tEff->Draw("HT>> outhist2","(nIsoMu==1 && MTW < 100 && MHT>200 && HT >500 && NJets < 7.6 && NJets> 5.9)","pe");
  pass = outhist2->Integral();
  tEff->Draw("HT>> outhist2","(nIsoMu==1 && MHT>200 && HT >500 && NJets < 7.6 && NJets> 5.9)","pe");
  all = outhist2->Integral();
  std::cout<<"Baseline MTW eff"<<pass/all<<std::endl;
  mtwCutNJet->SetBinContent(2,pass/all);
  mtwCutNJetPass->SetBinContent(2,pass);
  mtwCutNJetAll->SetBinContent(2,all);
  error = sqrt(  (1/all * sqrt(pass)) * (1/all * sqrt(pass))   + (pass/(all * all) * sqrt(all)) * (pass/(all * all) * sqrt(all)) );
  error = sqrt( pass/all *( 1 - pass/all) / all );
  mtwCutNJet->SetBinError(2,error);


 tEff->Draw("HT>> outhist2","(nIsoMu==1 && MTW < 100 && MHT>200 && HT >500 && NJets < 99 && NJets> 7.8)","pe");
  pass = outhist2->Integral();
  tEff->Draw("HT>> outhist2","(nIsoMu==1 && MHT>200 && HT >500 && NJets < 99 && NJets> 7.8)","pe");
  all = outhist2->Integral();
  std::cout<<"Baseline MTW eff"<<pass/all<<std::endl;
  mtwCutNJet->SetBinContent(3,pass/all);
  mtwCutNJetPass->SetBinContent(3,pass);
  mtwCutNJetAll->SetBinContent(3,all);
  error = sqrt(  (1/all * sqrt(pass)) * (1/all * sqrt(pass))   + (pass/(all * all) * sqrt(all)) * (pass/(all * all) * sqrt(all)) );
  error = sqrt( pass/all *( 1 - pass/all) / all );
  mtwCutNJet->SetBinError(3,error);
  mtwCutNJetPass->Divide(mtwCutNJetPass,mtwCutNJetAll,1,1,"B");
  //mtwCutHTMHTPass->Divide(//mtwCutHTMHTPass,//mtwCutHTMHTAll,1,1,"B");


  dMu->cd();
  muonBinByBinEff->Write();
  muonIsoBinByBinEff->Write();
muonIsoBinByBinNJet35Eff->Write();
muonIsoBinByBinNJet67Eff->Write();
muonIsoBinByBinNJet8InfEff->Write();
muonRecoBinByBinNJet35Eff->Write();
muonRecoBinByBinNJet67Eff->Write();
muonRecoBinByBinNJet8InfEff->Write();
  muonRecoBinByBinEff->Write();
  muonAccBinByBinEff->Write();
  muonAccSum->Write();
  muonAccEff3->Write();




  MTW->Write();
  mtwCutHTMHT->Write();
  mtwCutNJet->Write();
//mtwCutNJetPass->Write();
////mtwCutHTMHTPass->Write();

  muonAccRatio->Write();
  muonAccEff2->Write();
  muonRecoEff->Write();
  muonRecoEff2->Write();
  muonIsoEff->Write();
  muonIsoEff2->Write();



  muonAccPassed->Write();
  muonRecoSum->Write();
  muonIsoSum->Write();
  muonRecoSum2->Write();
  muonIsoSum2->Write();

  mc_tap_eff_mu_iso->Write();
  data_tap_eff_mu_iso->Write();
  mc_tap_eff_mu_reco->Write();
  data_tap_eff_mu_reco->Write();

  mc_TAP_mu_iso_eff_deltaR_relPT->Write();
  data_TAP_mu_iso_eff_deltaR_relPT->Write();
  mc_tap_eff_mu_reco_deltaR_PT->Write();
  data_tap_eff_mu_reco_deltaR_PT->Write();
/*  if(tapHTNjet)->Write();
{
mc_tap_eff_mu_iso_HTNJet->Write();
data_tap_eff_mu_iso_HTNJet->Write();
}
*/

/////////////////////////// electron ////////////////////////data_tap_eff_mu_reco

  // store the Acc ratio and the sum in the new files

  elecAccSum = (TH1F*)dInput->Get("elecAccFailed");
  elecAccSum->SetName("ElecAccSum");
  elecAccSum->Sumw2();
  elecAccSum->Add( (TH1F*)dInput->Get("elecAccPassed") );
  elecAccPassed = (TH1F*)dInput->Get("elecAccPassed");
  elecAccPassed->Sumw2();
  elecAccPassed->SetName("ElecAccPassed");

  TGraphAsymmErrors *elecAccRatio = new TGraphAsymmErrors(elecAccPassed,elecAccSum);
  elecAccRatio->SetName("ElecAccRatio");
  elecAccRatio->SetTitle("ElecAccRatio;ElecPT;Ratio;ZAX");

// second acc version
  elecAccSum2 = (TH1F*)dInput->Get("elecAccFailed2");
  elecAccSum2->SetName("ElecAccSum2");
  elecAccSum2->Sumw2();
  elecAccSum2->Add( (TH1F*)dInput->Get("elecAccPassed2") );
  elecAccEff2 = (TH1F*)dInput->Get("elecAccPassed2");
  elecAccEff2->SetName("ElecAccEff2");
  elecAccEff2->SetTitle("CMS Simulation, L=19.47 fb-1, sqrt(s)=8 TeV, e acc. eff.;#slash{H}_{T} [GeV];eff.");
  elecAccEff2->Sumw2();
  elecAccEff2->Divide(elecAccEff2,elecAccSum2,1,1,"B");

 // third version of acceptance eff
  elecAccSum3 = (TH2F*)dInput->Get("ElecAccFailed3");
  elecAccSum3->SetName("ElecAccSum3");
  elecAccSum3->Sumw2();
  elecAccSum3->Add( (TH2F*)dInput->Get("ElecAccPassed3") );

  elecAccEff3 = (TH2F*)dInput->Get("ElecAccPassed3");
  elecAccEff3->SetName("ElecAccEff3");
  elecAccEff3->SetTitle("CMS Simulation, L=19.47 fb-1, sqrt(s)=8 TeV, e acc. eff.;#slash{H}_{T} [GeV];N_{Jets}");
  elecAccEff3->Sumw2();
  elecAccEff3->Divide(elecAccEff3,elecAccSum3,1,1,"B");


  // elec reco eff
  elecRecoSum = (TH2F*)dInput->Get("elecIdFailed");
  elecRecoSum->SetName("TotalNumberElecAfterAcc");
  elecRecoSum->Sumw2();
  elecRecoSum->Add( ( TH2F*)dInput->Get("elecIdPassed") );

  elecRecoEff = (TH2F*)dInput->Get("elecIdPassed");
  elecRecoEff->SetName("ElecRecoEff");
  elecRecoEff->SetTitle("CMS Simulation, L=19.47 fb-1, sqrt(s)=8 TeV, e reco. eff.; #Delta R;RelPT;Eff.");
  elecRecoEff->Sumw2();
  elecRecoEff->Divide(elecRecoEff,elecRecoSum,1,1,"B");

 // second reco version
  elecRecoSum2 = (TH2F*)dInput->Get("elecIdFailed2");
  elecRecoSum2->SetName("TotalNumberElecAfterAcc2");
  elecRecoSum2->Sumw2();
  elecRecoSum2->Add( ( TH2F*)dInput->Get("elecIdPassed2") );

  elecRecoEff2 = (TH2F*)dInput->Get("elecIdPassed2");
  elecRecoEff2->SetName("ElecRecoEff2");
  elecRecoEff2->SetTitle("CMS Simulation, L=19.47 fb-1, sqrt(s)=8 TeV, e reco. eff.; #Delta R;e p_{T};Eff.");
  elecRecoEff2->Sumw2();
  elecRecoEff2->Divide(elecRecoEff2,elecRecoSum2,1,1,"B");



  // elec iso eff
  elecIsoSum = (TH2F*)dInput->Get("elecIsoFailed");
  elecIsoSum->SetName("TotalNumberelecsAfterReco");
  elecIsoSum->Sumw2();
  elecIsoSum->Add( ( TH2F*)dInput->Get("elecIsoPassed") );

  elecIsoEff = (TH2F*)dInput->Get("elecIsoPassed");
  elecIsoEff->SetName("ElecIsoEff");
  elecIsoEff->SetTitle("CMS Simulation, L=19.47 fb-1, sqrt(s)=8 TeV, e iso. eff.; #Delta R;RelPT;Eff.");
  elecIsoEff->Sumw2();
  elecIsoEff->Divide(elecIsoEff,elecIsoSum,1,1,"B");

  elecIsoSum2 = (TH2F*)dInput->Get("elecIsoFailed2");
  elecIsoSum2->SetName("TotalNumberelecsAfterReco2");
  elecIsoSum2->Sumw2();
  elecIsoSum2->Add( ( TH2F*)dInput->Get("elecIsoPassed2") );

  elecIsoEff2 = (TH2F*)dInput->Get("elecIsoPassed2");
  elecIsoEff2->SetName("ElecIsoEff2");
  elecIsoEff2->SetTitle("CMS Simulation, L=19.47 fb-1, sqrt(s)=8 TeV, e iso. eff.; #Delta R;e p_{T};Eff.");
  elecIsoEff2->Sumw2();
  elecIsoEff2->Divide(elecIsoEff2,elecIsoSum2,1,1,"B");

   //bin by bin eff
  elecBinByBinSum = (TH3F*)dInput->Get("BinByBinEffElecFailed");
  elecBinByBinSum->SetName("BinByBinEffElecFailed");
  elecBinByBinSum->Sumw2();
  elecBinByBinSum->Add( ( TH3F*)dInput->Get("BinByBinEffElecPassed") );

  elecBinByBinEff = (TH3F*)dInput->Get("BinByBinEffElecPassed");
  elecBinByBinEff->SetName("ElecBinByBinEff");
  elecBinByBinEff->SetTitle("CMS Simulation, L=19.47 fb-1, sqrt(s)=8 TeV, elec total eff; H_{T} [GeV];#slash{H}_{T} [GeV]; N_{Jets}");
  elecBinByBinEff->Sumw2();
  elecBinByBinEff->Divide(elecBinByBinEff,elecBinByBinSum,1,1,"B");
  // seperated

// seperated
  elecAccBinByBinSum = (TH3F*)dInput->Get("AccBinByBinEffElecFailed");
  elecAccBinByBinSum->SetName("AccBinByBinElecFailed");
  elecAccBinByBinSum->Sumw2();
  elecAccBinByBinSum->Add( ( TH3F*)dInput->Get("AccBinByBinEffElecPassed") );

  elecAccBinByBinEff = (TH3F*)dInput->Get("AccBinByBinEffElecPassed");
  elecAccBinByBinEff->SetName("AccBinByBinElecEff");
  elecAccBinByBinEff->SetTitle("CMS Simulation, L=19.47 fb-1, sqrt(s)=8 TeV, #mu acc eff; H_{T} [GeV];#slash{H}_{T} [GeV]; N_{Jets}");
  elecAccBinByBinEff->Sumw2();
  elecAccBinByBinEff->Divide(elecAccBinByBinSum);


  elecRecoBinByBinSum = (TH3F*)dInput->Get("RecoBinByBinEffElecFailed");
  elecRecoBinByBinSum->SetName("RecoBinByBinElecFailed");
  elecRecoBinByBinSum->Sumw2();
  elecRecoBinByBinSum->Add( ( TH3F*)dInput->Get("RecoBinByBinEffElecPassed") );

  elecRecoBinByBinEff = (TH3F*)dInput->Get("RecoBinByBinEffElecPassed");
  elecRecoBinByBinEff->SetName("RecoBinByBinElecEff");
  elecRecoBinByBinEff->SetTitle("CMS Simulation, L=19.47 fb-1, sqrt(s)=8 TeV, #mu Reco eff; H_{T} [GeV];#slash{H}_{T} [GeV]; N_{Jets}");
  elecRecoBinByBinEff->Sumw2();
  elecRecoBinByBinEff->Divide(elecRecoBinByBinSum);


  elecIsoBinByBinSum = (TH3F*)dInput->Get("IsoBinByBinEffElecFailed");
  elecIsoBinByBinSum->SetName("IsoBinByBinElecFailed");
  elecIsoBinByBinSum->Sumw2();
  elecIsoBinByBinSum->Add( ( TH3F*)dInput->Get("IsoBinByBinEffElecPassed") );

  elecIsoBinByBinEff = (TH3F*)dInput->Get("IsoBinByBinEffElecPassed");
  elecIsoBinByBinEff->SetName("IsoBinByBinElecEff");
  elecIsoBinByBinEff->SetTitle("CMS Simulation, L=19.47 fb-1, sqrt(s)=8 TeV, #mu Iso eff; H_{T} [GeV];#slash{H}_{T} [GeV]; N_{Jets}");
  elecIsoBinByBinEff->Sumw2();
  elecIsoBinByBinEff->Divide(elecIsoBinByBinSum);





  EleconIsoBinByBinNJet35Sum = (TH2F*) dInput->Get("isoEffTH2FailedElecNJet35");
  EleconIsoBinByBinNJet35Sum->Sumw2();
  EleconIsoBinByBinNJet35Sum->Add( (TH2F*)dInput->Get("isoEffTH2PassedElecNJet35") );
  
  EleconIsoBinByBinNJet35Eff = (TH2F*)dInput->Get("isoEffTH2PassedElecNJet35");
  EleconIsoBinByBinNJet35Eff->SetName("IsoHTMHTElecEffNJet_35");
  EleconIsoBinByBinNJet35Eff->SetTitle("CMS Simulation, L=19.47 fb-1, sqrt(s)=8 TeV, elec Iso eff 3 #leq N_{Jets} #leq 5; H_{T} [GeV];#slash{H}_{T} [GeV]");
  EleconIsoBinByBinNJet35Eff->Sumw2();
  EleconIsoBinByBinNJet35Eff->Divide(EleconIsoBinByBinNJet35Eff,EleconIsoBinByBinNJet35Sum,1,1,"B");
std::cout<<"EleconIsoBinByBinNJet35Eff"<<EleconIsoBinByBinNJet35Eff->GetBinContent(1,1)<<std::endl;

  EleconIsoBinByBinNJet67Sum = (TH2F*) dInput->Get("isoEffTH2FailedElecNJet67");
  EleconIsoBinByBinNJet67Sum->Sumw2();
  EleconIsoBinByBinNJet67Sum->Add( (TH2F*)dInput->Get("isoEffTH2PassedElecNJet67") );
  
  EleconIsoBinByBinNJet67Eff = (TH2F*)dInput->Get("isoEffTH2PassedElecNJet67");
  EleconIsoBinByBinNJet67Eff->SetName("IsoHTMHTElecEffNJet_67");
  EleconIsoBinByBinNJet67Eff->SetTitle("CMS Simulation, L=19.47 fb-1, sqrt(s)=8 TeV, elec Iso eff 6 #leq N_{Jets} #leq 7; H_{T} [GeV];#slash{H}_{T} [GeV]");
  EleconIsoBinByBinNJet67Eff->Sumw2();
  EleconIsoBinByBinNJet67Eff->Divide(EleconIsoBinByBinNJet67Eff,EleconIsoBinByBinNJet67Sum,1,1,"B");


  EleconIsoBinByBinNJet8InfSum = (TH2F*) dInput->Get("isoEffTH2FailedElecNJet8Inf");
  EleconIsoBinByBinNJet8InfSum->Sumw2();
  EleconIsoBinByBinNJet8InfSum->Add( (TH2F*)dInput->Get("isoEffTH2PassedElecNJet8Inf") );
  
  EleconIsoBinByBinNJet8InfEff = (TH2F*)dInput->Get("isoEffTH2PassedElecNJet8Inf");
  EleconIsoBinByBinNJet8InfEff->SetName("IsoHTMHTElecEffNJet_8Inf");
  EleconIsoBinByBinNJet8InfEff->SetTitle("CMS Simulation, L=19.47 fb-1, sqrt(s)=8 TeV, elec Iso eff 8 #leq N_{Jets}; H_{T} [GeV];#slash{H}_{T} [GeV]");
  EleconIsoBinByBinNJet8InfEff->Sumw2();
  EleconIsoBinByBinNJet8InfEff->Divide(EleconIsoBinByBinNJet8InfEff,EleconIsoBinByBinNJet8InfSum,1,1,"B");



  EleconRecoBinByBinNJet35Sum = (TH2F*) dInput->Get("recoEffTH2FailedElecNJet35");
  EleconRecoBinByBinNJet35Sum->Sumw2();
  EleconRecoBinByBinNJet35Sum->Add( (TH2F*)dInput->Get("recoEffTH2PassedElecNJet35") );
  
  EleconRecoBinByBinNJet35Eff = (TH2F*)dInput->Get("recoEffTH2PassedElecNJet35");
  EleconRecoBinByBinNJet35Eff->SetName("RecoHTMHTElecEffNJet_35");
  EleconRecoBinByBinNJet35Eff->SetTitle("CMS Simulation, L=19.47 fb-1, sqrt(s)=8 TeV, elec Reco eff 3 #leq N_{Jets} #leq 5; H_{T} [GeV];#slash{H}_{T} [GeV]");
  EleconRecoBinByBinNJet35Eff->Sumw2();
  EleconRecoBinByBinNJet35Eff->Divide(EleconRecoBinByBinNJet35Eff,EleconRecoBinByBinNJet35Sum,1,1,"B");
std::cout<<"EleconRecoBinByBinNJet35Eff"<<EleconRecoBinByBinNJet35Eff->GetBinContent(1,1)<<std::endl;

  EleconRecoBinByBinNJet67Sum = (TH2F*) dInput->Get("recoEffTH2FailedElecNJet67");
  EleconRecoBinByBinNJet67Sum->Sumw2();
  EleconRecoBinByBinNJet67Sum->Add( (TH2F*)dInput->Get("recoEffTH2PassedElecNJet67") );
  
  EleconRecoBinByBinNJet67Eff = (TH2F*)dInput->Get("recoEffTH2PassedElecNJet67");
  EleconRecoBinByBinNJet67Eff->SetName("RecoHTMHTElecEffNJet_67");
  EleconRecoBinByBinNJet67Eff->SetTitle("CMS Simulation, L=19.47 fb-1, sqrt(s)=8 TeV, elec Reco eff 6 #leq N_{Jets} #leq 7; H_{T} [GeV];#slash{H}_{T} [GeV]");
  EleconRecoBinByBinNJet67Eff->Sumw2();
  EleconRecoBinByBinNJet67Eff->Divide(EleconRecoBinByBinNJet67Eff,EleconRecoBinByBinNJet67Sum,1,1,"B");


  EleconRecoBinByBinNJet8InfSum = (TH2F*) dInput->Get("recoEffTH2FailedElecNJet8Inf");
  EleconRecoBinByBinNJet8InfSum->Sumw2();
  EleconRecoBinByBinNJet8InfSum->Add( (TH2F*)dInput->Get("recoEffTH2PassedElecNJet8Inf") );
  
  EleconRecoBinByBinNJet8InfEff = (TH2F*)dInput->Get("recoEffTH2PassedElecNJet8Inf");
  EleconRecoBinByBinNJet8InfEff->SetName("RecoHTMHTElecEffNJet_8Inf");
  EleconRecoBinByBinNJet8InfEff->SetTitle("CMS Simulation, L=19.47 fb-1, sqrt(s)=8 TeV, elec Reco eff 8 #leq N_{Jets}; H_{T} [GeV];#slash{H}_{T} [GeV]");
  EleconRecoBinByBinNJet8InfEff->Sumw2();
  EleconRecoBinByBinNJet8InfEff->Divide(EleconRecoBinByBinNJet8InfEff,EleconRecoBinByBinNJet8InfSum,1,1,"B");

// tag and probe stuff

  TCanvas* TMC001 = (TCanvas*)dInputTagAndProbeMCIsoelec->Get("HT_NJets_PLOT")->Clone();
  mc_tap_eff_elec_iso = (TH2F*)TMC001->GetPrimitive("HT_NJets_PLOT")->Clone();
  mc_tap_eff_elec_iso->SetName("MC_TAP_elec_iso_eff");
  mc_tap_eff_elec_iso->SetTitle("CMS Simulation, L=19.47 fb-1, sqrt(s)=8 TeV, elec iso MC T&P eff; H_{T} [GeV];NJet;Eff");


  TCanvas* TMC001a = (TCanvas*)dInputTagAndProbeMCIsoelecPT->Get("ElecIsoDeltaR30GeVJet_ElecIsoProbePt_PLOT")->Clone();
  mc_tap_eff_elec_iso_PT = (TH2F*)TMC001a->GetPrimitive("ElecIsoDeltaR30GeVJet_ElecIsoProbePt_PLOT")->Clone();
  mc_tap_eff_elec_iso_PT->SetName("MC_TAP_elec_iso_eff_deltaR_PT");
  mc_tap_eff_elec_iso_PT->SetTitle("CMS Simulation, L=19.47 fb-1, sqrt(s)=8 TeV, elec iso MC T&P eff; #Delta R; elec p_{T};Eff");


  TCanvas* TMC111 = (TCanvas*)dInputTagAndProbeDataIsoelec->Get("HT_NJets_PLOT")->Clone();
  data_tap_eff_elec_iso = (TH2F*)TMC111->GetPrimitive("HT_NJets_PLOT")->Clone();
  data_tap_eff_elec_iso->SetName("Data_TAP_elec_iso_eff");
  data_tap_eff_elec_iso->SetTitle("CMS Preliminary, L=19.47 fb-1, sqrt(s)=8 TeV, elec Iso Data T&P eff; H_{T} [GeV];NJet;Eff");

  TCanvas* TMC001b = (TCanvas*)dInputTagAndProbeDataIsoelecPT->Get("ElecIsoDeltaR30GeVJet_ElecIsoProbePt_PLOT")->Clone();
  data_tap_eff_elec_iso_PT = (TH2F*)TMC001b->GetPrimitive("ElecIsoDeltaR30GeVJet_ElecIsoProbePt_PLOT")->Clone();
  data_tap_eff_elec_iso_PT->SetName("Data_TAP_elec_iso_eff_deltaR_PT");
  data_tap_eff_elec_iso_PT->SetTitle("CMS Preliminary, L=19.47 fb-1, sqrt(s)=8 TeV, elec iso Data T&P eff; #Delta R; elec p_{T};Eff");


  TCanvas* TMC002 = (TCanvas*)dInputTagAndProbeMCIdelec->Get("HT_NJets_PLOT")->Clone();
  mc_tap_eff_elec_reco = (TH2F*)TMC002->GetPrimitive("HT_NJets_PLOT")->Clone();
  mc_tap_eff_elec_reco->SetName("MC_TAP_elec_reco_eff");
  mc_tap_eff_elec_reco->SetTitle("CMS Simulation, L=19.47 fb-1, sqrt(s)=8 TeV, elec Reco MC T&P eff; H_{T} [GeV];NJet;Eff");

  TCanvas* TMC002a = (TCanvas*)dInputTagAndProbeMCIdelecPT->Get("ElecIdGsfDeltaR30GeVJet_ElecIdGsfProbePt_PLOT")->Clone();
  mc_tap_eff_elec_reco_PT = (TH2F*)TMC002a->GetPrimitive("ElecIdGsfDeltaR30GeVJet_ElecIdGsfProbePt_PLOT")->Clone();
  mc_tap_eff_elec_reco_PT->SetName("MC_TAP_elec_reco_eff_deltaR_PT");
  mc_tap_eff_elec_reco_PT->SetTitle("CMS Simulation, L=19.47 fb-1, sqrt(s)=8 TeV, elec Reco MC T&P eff; #Delta R; elec p_{T};Eff");

  TCanvas* TMC002aaa = (TCanvas*)dInputTagAndProbeMCIdelecPT2->Get("ElecIdGsfProbePt_PLOT")->Clone();
  mc_tap_eff_elec_reco_PT2 = (TGraphAsymmErrors*)TMC002aaa->GetPrimitive("hxy_fit_eff")->Clone();
  mc_tap_eff_elec_reco_PT2->SetName("MC_TAP_elec_reco_eff_deltaR_PT2");
  mc_tap_eff_elec_reco_PT2->SetTitle("CMS Simulation, L=19.47 fb-1, sqrt(s)=8 TeV, elec Reco MC T&P eff; elec p_{T};Eff");


  TCanvas* TMC112 = (TCanvas*)dInputTagAndProbeDataIdelec->Get("HT_NJets_PLOT")->Clone();
  data_tap_eff_elec_reco = (TH2F*)TMC112->GetPrimitive("HT_NJets_PLOT")->Clone();
  data_tap_eff_elec_reco->SetName("Data_TAP_elec_reco_eff");
  data_tap_eff_elec_reco->SetTitle("CMS Preliminary, L=19.47 fb-1, sqrt(s)=8 TeV, elec Reco Data T&P eff; H_{T} [GeV];NJet;Eff");

  TCanvas* TMC002b = (TCanvas*)dInputTagAndProbeDataIdelecPT->Get("ElecIdGsfDeltaR30GeVJet_ElecIdGsfProbePt_PLOT")->Clone();
  data_tap_eff_elec_reco_PT = (TH2F*)TMC002b->GetPrimitive("ElecIdGsfDeltaR30GeVJet_ElecIdGsfProbePt_PLOT")->Clone();
  data_tap_eff_elec_reco_PT->SetName("Data_TAP_elec_reco_eff_deltaR_PT");
  data_tap_eff_elec_reco_PT->SetTitle("CMS Preliminary, L=19.47 fb-1, sqrt(s)=8 TeV, elec Reco Data T&P eff; #Delta R; elec p_{T};Eff");

  TCanvas* TMC002b2 = (TCanvas*)dInputTagAndProbeDataIdelecPT2->Get("ElecIdGsfProbePt_PLOT")->Clone();
  data_tap_eff_elec_reco_PT2 = (TGraphAsymmErrors*)TMC002b2->GetPrimitive("hxy_fit_eff")->Clone();
  data_tap_eff_elec_reco_PT2->SetName("Data_TAP_elec_reco_eff_deltaR_PT2");
  data_tap_eff_elec_reco_PT2->SetTitle("CMS Preliminary, L=19.47 fb-1, sqrt(s)=8 TeV, elec Reco Data T&P eff; elec p_{T};Eff");


  TGraphAsymmErrors* ratio_tap_eff_elec_reco_PT2 = data_tap_eff_elec_reco_PT2->Clone();
  ratio_tap_eff_elec_reco_PT2->SetName("ElecRecoTAPRatio");
  ratio_tap_eff_elec_reco_PT2->SetTitle("CMS Simulation, L=19.47 fb-1, sqrt(s)=8 TeV, elec Reco eff ; elec p_{T};data eff / mc eff");



      TGraphAsymmErrors *gRatio = new TGraphAsymmErrors(data_tap_eff_elec_reco_PT2->GetN());
      for(int i = 0; i < data_tap_eff_elec_reco_PT2->GetN() && i < mc_tap_eff_elec_reco_PT2->GetN(); ++i) {
	double denom = mc_tap_eff_elec_reco_PT2->GetY()[i];
	double x = 0.5*(data_tap_eff_elec_reco_PT2->GetX()[i]+mc_tap_eff_elec_reco_PT2->GetX()[i]); // Mean value of x1 and x2
	double e1 = data_tap_eff_elec_reco_PT2->GetEXhigh()[i];
	double e2 = mc_tap_eff_elec_reco_PT2->GetEXhigh()[i];
	double xehigh = e1; // Quadratic mean of x1e and x2e
	double xelow = mc_tap_eff_elec_reco_PT2->GetEXlow()[i];
	if( denom != 0. ) {
	  double y = data_tap_eff_elec_reco_PT2->GetY()[i]/denom;
	  e1 = data_tap_eff_elec_reco_PT2->GetEYhigh()[i];
	  e2 = mc_tap_eff_elec_reco_PT2->GetEYhigh()[i];
	  double ye = sqrt(pow(e1/denom,2.)+pow(data_tap_eff_elec_reco_PT2->GetY()[i]*e2/denom/denom,2.));
	  gRatio->SetPoint(i,x,y);
	  gRatio->SetPointError(i,xelow,xehigh,ye,ye);
	} else {
	  gRatio->SetPoint(i,x,0.);
	  gRatio->SetPointError(i,xelow,xehigh,0.,0.);
	}
      }
      gRatio->SetMarkerStyle(data_tap_eff_elec_reco_PT2->GetMarkerStyle());
      gRatio->SetMarkerColor(data_tap_eff_elec_reco_PT2->GetMarkerColor());
      gRatio->SetLineColor(data_tap_eff_elec_reco_PT2->GetLineColor());
	gRatio->SetTitle("CMS Simulation, L=19.47 fb-1, sqrt(s)=8 TeV, elec Reco eff; elec p_{T};data eff / mc eff");







/*

  TCanvas* TMC3 = (TCanvas*)dInputTagAndProbeMCRecoElec->Get("probe_eta_probe_et_PLOT")->Clone();
  mc_tap_eff_elec_reco = (TH2F*)TMC3->GetPrimitive("probe_eta_probe_et_PLOT")->Clone();
  mc_tap_eff_elec_reco->SetName("MC_TAP_elec_iso_eff");
  mc_tap_eff_elec_reco->SetTitle("CMS Simulation, L=19.47 fb-1, sqrt(s)=8 TeV, e Iso MC T&P eff; #eta;e_{T};Eff");


  TCanvas* TMC4 = (TCanvas*)dInputTagAndProbeDataRecoElec->Get("probe_eta_probe_et_PLOT")->Clone();
  data_tap_eff_elec_reco = (TH2F*)TMC4->GetPrimitive("probe_eta_probe_et_PLOT")->Clone();
  data_tap_eff_elec_reco->SetName("Data_TAP_elec_iso_eff");
  data_tap_eff_elec_reco->SetTitle("CMS Simulation, L=19.47 fb-1, sqrt(s)=8 TeV, e Iso Datat T&P eff; #eta;e_{T};Eff");


  TCanvas* TMC3 = (TCanvas*)dInputTagAndProbeMCIsoElec->Get("probe_sc_eta_probe_sc_et_PLOT")->Clone();
  mc_tap_eff_elec_iso = (TH2F*)TMC3->GetPrimitive("probe_sc_eta_probe_sc_et_PLOT")->Clone();
  mc_tap_eff_elec_iso->SetName("MC_TAP_elec_reco_eff");
  mc_tap_eff_elec_iso->SetTitle("CMS Simulation, L=19.47 fb-1, sqrt(s)=8 TeV, e Reco MC T&P eff; #eta;e_{T};Eff");


  TCanvas* TMC4 = (TCanvas*)dInputTagAndProbeDataIsoElec->Get("probe_sc_eta_probe_sc_et_PLOT")->Clone();
  data_tap_eff_elec_iso = (TH2F*)TMC4->GetPrimitive("probe_sc_eta_probe_sc_et_PLOT")->Clone();
  data_tap_eff_elec_iso->SetName("Data_TAP_elec_reco_eff");
  data_tap_eff_elec_iso->SetTitle("CMS Simulation, L=19.47 fb-1, sqrt(s)=8 TeV, e Reco Datat T&P eff; #eta;e_{T};Eff");

*/


   // tag and probe uncertainty eff.
/*
  mc_tap_eff_elec_iso =  (TH2F*) dInputTagAndProbeMCIsoelec->Get("probe_emfdrjCalo_probe_emfptRelCalo_PLOT");
  mc_tap_eff_elec_iso->SetName("MC_TAP_elec_iso_eff");

  data_tap_eff_elec_iso =  (TH2F*) dInputTagAndProbeDataIsoelec->Get("probe_emfdrjCalo_probe_emfptRelCalo_PLOT");
  data_tap_eff_elec_iso->SetName("Data_TAP_elec_iso_eff");


  mc_tap_eff_elec_reco =  (TH2F*) dInputTagAndProbeMCRecoelec->Get("probe_emfdrjCalo_probe_pt_PLOT");
  mc_tap_eff_elec_reco->SetName("MC_TAP_elec_reco_eff");

  data_tap_eff_elec_reco =  (TH2F*) dInputTagAndProbeDataRecoelec->Get("probe_emfdrjCalo_probe_pt_PLOT");
  data_tap_eff_elec_reco->SetName("Data_TAP_elec_reco_eff");
*/
  // write to file
  dElec->cd();
  elecBinByBinEff->Write();
  elecIsoBinByBinEff->Write();
EleconIsoBinByBinNJet35Eff->Write();
EleconIsoBinByBinNJet67Eff->Write();
EleconIsoBinByBinNJet8InfEff->Write();
EleconRecoBinByBinNJet35Eff->Write();
EleconRecoBinByBinNJet67Eff->Write();
EleconRecoBinByBinNJet8InfEff->Write();
  elecRecoBinByBinEff->Write();
  elecAccBinByBinEff->Write();
  elecAccRatio->Write();
  elecAccEff2->Write();
  elecAccEff3->Write();
  elecRecoEff->Write();
  elecRecoEff2->Write();
  elecIsoEff->Write();
  elecIsoEff2->Write();

  elecAccSum->Write();  
  elecAccPassed->Write();
  elecRecoSum->Write();
  elecIsoSum->Write();

data_tap_eff_elec_reco->Write();
mc_tap_eff_elec_reco->Write();
data_tap_eff_elec_iso->Write();
mc_tap_eff_elec_iso->Write();

  mc_tap_eff_elec_iso_PT->Write();
  data_tap_eff_elec_iso_PT->Write();
  mc_tap_eff_elec_reco_PT->Write();
  data_tap_eff_elec_reco_PT->Write();
  mc_tap_eff_elec_reco_PT2->Write();
  data_tap_eff_elec_reco_PT2->Write();
ratio_tap_eff_elec_reco_PT2->Write();
gRatio->Write();
/*
  mc_tap_eff_elec_iso->Write();
  data_tap_eff_elec_iso->Write();
  mc_tap_eff_elec_reco->Write();
  data_tap_eff_elec_reco->Write();
*/
  // close all files and write to output
  out->Write();
  out->Close();
  fInput->Close();
}
