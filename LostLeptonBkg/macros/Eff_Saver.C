//#saving the histogramms for the efficiencies


#include <TH2F.h>
#include <TFile.h>
#include <TGraph.h>
#include <vector>
#include <TString.h>
#include "TStyle.h"
#include <ostream>
#include <TTree.h>
#include <TH1.h>
#include <TH3.h>
#include <TProfile2D.h>

void Eff_Saver()
{
  vector<TString> names;
   names.clear();
   names.push_back("MCEff");
//   names.push_back("MCEffw");
//   names.push_back("MCEffttMassiv");
//   names.push_back("MCEffttc10"); 

  for (int i=0; i< names.size();i++)
{
 std::cout<<"sizeNames"<<names.size()<<std::endl;
   TString s(names[i]);
 TFile* fInput = TFile::Open(s+".root");
  TDirectory *dMu = (TDirectory*)fInput->Get("Muon");
  TDirectory *dElec = (TDirectory*)fInput->Get("Electron");



  gStyle->SetPaintTextFormat("5.2f"); 
  gStyle->SetStatW(0.1);
  gStyle->SetStatH(0.1);
  gStyle->SetStatY(202);

  dMu->cd();
				MuonAccEff3->SetMarkerSize(2.0);
				  MuonAccEff3->Draw("ColZ,Text,E");
 // c1->SaveAs(s+"MuonAccEff3"+".png");
				  c1->SaveAs(s+"MuonAccEff3"+".pdf");
					MuonRecoEff2->SetMarkerSize(2.0);
					  MuonRecoEff2->Draw("ColZ,Text,E");
//  c1->SaveAs(s+"MuonRecoEff2"+".png");
				  c1->SaveAs(s+"MuonRecoEff2"+".pdf");
				IsoHTMHTMuEffNJet_35->SetMarkerSize(1.5);
				IsoHTMHTMuEffNJet_35->Draw("ColZ,Text,E");
				  c1->SaveAs(s+"mcMuIsoNJet3_5"+".pdf");
IsoHTMHTMuEffNJet_67->SetMarkerSize(1.5);
				IsoHTMHTMuEffNJet_67->Draw("ColZ,Text,E");
				c1->SaveAs(s+"mcMuIsoNJet6_7"+".pdf");
IsoHTMHTMuEffNJet_8Inf->SetMarkerSize(1.5);
				IsoHTMHTMuEffNJet_8Inf->Draw("ColZ,Text,E");
				c1->SaveAs(s+"mcMuIsoNJet8_Inf"+".pdf");


				RecoHTMHTMuEffNJet_35->SetMarkerSize(1.5);
				RecoHTMHTMuEffNJet_35->Draw("ColZ,Text,E");
				  c1->SaveAs(s+"mcMuRecoNJet3_5"+".pdf");
RecoHTMHTMuEffNJet_67->SetMarkerSize(1.5);
				RecoHTMHTMuEffNJet_67->Draw("ColZ,Text,E");
				c1->SaveAs(s+"mcMuRecoNJet6_7"+".pdf");
RecoHTMHTMuEffNJet_8Inf->SetMarkerSize(1.5);
				RecoHTMHTMuEffNJet_8Inf->Draw("ColZ,Text,E");
				c1->SaveAs(s+"mcMuRecoNJet8_Inf"+".pdf");




MC_TAP_mu_iso_eff_HTNJet->SetMarkerSize(2.0);
				MC_TAP_mu_iso_eff_HTNJet->Draw("ColZ,Text,E");
				  c1->SaveAs(s+"MuonIsoTAPEffMCHTNJet"+".pdf");
Data_TAP_mu_iso_eff_HTNJet->SetMarkerSize(2.0);
				Data_TAP_mu_iso_eff_HTNJet->Draw("ColZ,Text,E");
				  c1->SaveAs(s+"MuonIsoTAPEffDataHTNJet"+".pdf");
//				MC_TAP_mu_iso_eff->Draw("ColZ,Text,E");
//				  c1->SaveAs(s+"MuonIsoTAPEffMC"+".pdf");
//				Data_TAP_mu_iso_eff->Draw("ColZ,Text,E");
//				  c1->SaveAs(s+"MuonIsoTAPEffData"+".pdf");

MC_TAP_mu_reco_eff->SetMarkerSize(2.0);
				MC_TAP_mu_reco_eff->Draw("ColZ,Text,E");
				  c1->SaveAs(s+"MuonRecoTAPEffMC"+".pdf");
Data_TAP_mu_reco_eff->SetMarkerSize(2.0);
				Data_TAP_mu_reco_eff->Draw("ColZ,Text,E");
				  c1->SaveAs(s+"MuonRecoTAPEffData"+".pdf");


				MTWCutHTMHT->Draw("ColZ,Text,E");
				c1->SaveAs(s+"MTWCutEffHTMHT"+".pdf");
				MTWCutNJet->Draw();
				c1->SaveAs(s+"MTWCutEffNJet"+".pdf");
//  MuonIsoEff2->Draw("ColZ,Text,E");
//  c1->SaveAs(s+"MuonIsoEff2"+".png");
//  c1->SaveAs(s+"MuonIsoEff2"+".pdf");
//  MuonIsoEff->Draw("ColZ,Text,E");
//  c1->SaveAs(s+"MuonIsoEff"+".png");
//  c1->SaveAs(s+"MuonIsoEff"+".pdf");


  dElec->cd();
ElecAccEff3->SetMarkerSize(2.0);
 				 ElecAccEff3->Draw("ColZ,Text,E");
//  c1->SaveAs(s+"ElecAccEff3"+".png");
 					 c1->SaveAs(s+"ElecAccEff3"+".pdf");
ElecRecoEff2->SetMarkerSize(2.0);
				  ElecRecoEff2->Draw("ColZ,Text,E");
//  c1->SaveAs(s+"ElecRecoEff2"+".png");
					  c1->SaveAs(s+"ElecRecoEff2"+".pdf");
IsoHTMHTElecEffNJet_35->SetMarkerSize(1.5);
				IsoHTMHTElecEffNJet_35->Draw("ColZ,Text,E");
				c1->SaveAs(s+"mcElecIsoNJet3_5"+".pdf");
IsoHTMHTElecEffNJet_67->SetMarkerSize(1.5);
				IsoHTMHTElecEffNJet_67->Draw("ColZ,Text,E");
				c1->SaveAs(s+"mcElecIsoNJet6_7"+".pdf");
IsoHTMHTElecEffNJet_8Inf->SetMarkerSize(1.5);
				IsoHTMHTElecEffNJet_8Inf->Draw("ColZ,Text,E");
				c1->SaveAs(s+"mcElecIsoNJet8_Inf"+".pdf");

RecoHTMHTElecEffNJet_35->SetMarkerSize(1.5);
				RecoHTMHTElecEffNJet_35->Draw("ColZ,Text,E");
				c1->SaveAs(s+"mcElecRecoNJet3_5"+".pdf");
RecoHTMHTElecEffNJet_67->SetMarkerSize(1.5);
				RecoHTMHTElecEffNJet_67->Draw("ColZ,Text,E");
				c1->SaveAs(s+"mcElecRecoNJet6_7"+".pdf");
RecoHTMHTElecEffNJet_8Inf->SetMarkerSize(1.5);
				RecoHTMHTElecEffNJet_8Inf->Draw("ColZ,Text,E");
				c1->SaveAs(s+"mcElecRecoNJet8_Inf"+".pdf");

Data_TAP_elec_reco_eff->SetMarkerSize(2.0);
				Data_TAP_elec_reco_eff->Draw("ColZ,Text,E");
				c1->SaveAs(s+"ElecDataRecoTAPEff"+".pdf");
MC_TAP_elec_reco_eff->SetMarkerSize(2.0);
				MC_TAP_elec_reco_eff->Draw("ColZ,Text,E");
				c1->SaveAs(s+"ElecMCRecoTAPEff"+".pdf");

Data_TAP_elec_iso_eff->SetMarkerSize(2.0);
				Data_TAP_elec_iso_eff->Draw("ColZ,Text,E");
				c1->SaveAs(s+"ElecDataIsoTAPEff"+".pdf");
MC_TAP_elec_iso_eff->SetMarkerSize(2.0);
				MC_TAP_elec_iso_eff->Draw("ColZ,Text,E");
				c1->SaveAs(s+"ElecMCIsoTAPEff"+".pdf");
//  ElecIsoEff2->Draw("ColZ,Text,E");
//  c1->SaveAs(s+"ElecIsoEff2"+".png");
//  c1->SaveAs(s+"ElecIsoEff2"+".pdf");
//  ElecIsoEff->Draw("ColZ,Text,E");
//  c1->SaveAs(s+"ElecIsoEff"+".png");
//  c1->SaveAs(s+"ElecIsoEff"+".pdf");



// save from the 3d hist nJet selections


// TFile* fInputc = TFile::Open("LostLeptonEffFromMC.root");
//  TDirectory *dInputc = (TDirectory*)fInputc->Get("LostLeptonBkgMCEffCalculator");
//  TTree *tEf = new TTree();
//  tEf = (TTree*) dInputc->Get("LostLeptonMCEff");

/*
  TH2F *nJet3_5_mu_Iso= new TH2F;
  TH2F *nJet6_7_mu_Iso= new TH2F;  
  TH2F *nJet8_inf_mu_Iso= new TH2F;
  dMu->cd();
  TH3F *MuIso = (TH3F*)dMu->Get("IsoBinByBinMuEff");


  TProfile2D *tProfile1 = new TProfile2D;
  MuIso->GetZaxis()->SetRange(3,5);
	std::cout<<"MuIso->GetBinContent(2,2,2)"<<MuIso->GetBinContent(2,2,1)<<std::endl;
  tProfile1 = MuIso->Project3DProfile("xy");
//  tProfile1->Draw("ColZ,Text");
  
//  MuIso->Draw();
   static const int MHTbins = MuIso->GetNbinsY();
  double aa = MuIso->GetXaxis()->GetBinLowEdge(2.0);
  static const int HTbins = MuIso->GetNbinsX();
  static const int NJetBins = MuIso->GetNbinsZ();
  std::cout<<"NJet bins:"<<MuIso->GetNbinsZ()<<std::endl;
  IsoBinByBinMuEff->GetZaxis()->SetRange(3,4);
//  IsoBinByBinMuEff->Draw("ColZ,Text,E");
/*

  vector<TString> HTEdges;
  HTEdges.clear();
  double htbins [HTbins];
  vector<TString> MHTEdges;
  MHTEdges.clear();
  vector<TString> NJetEdges;
  NJetEdges.clear();
  std::cout<<"NumberOfHTBins"<<HTbins<<std::endl
  for(int i=1; i<HTbins+2 ;i++)
  {	std::cout<<"htBin#"<<i<<std::endl;
	htbins [i] = MuIso->GetXaxis()->GetBinLowEdge(i) ;
  	HTEdges.push_back(MuIso->GetXaxis()->GetBinLowEdge(i) );
  }
  for(int mhtBin=0; mhtBin<MHTbins ;mhtBin++)
  {
  	MHTEdges.push_back(MuIso->GetYaxis()->GetBinLowEdge(mhtBin) );
  }
  for(int njetBin=0; njetBin<NJetBins ;njetBin++)
  {
  	NJetEdges.push_back(MuIso->GetZaxis()->GetBinLowEdge(njetBin) );
  }
  for(int njetBin=0; njetBin<NJetBins ;njetBin++)
{
   TString njet(NJetBins[njetBin]);
  std::cout<<"TString njet"<<njet<<std::endl;
}
*/
}





}


