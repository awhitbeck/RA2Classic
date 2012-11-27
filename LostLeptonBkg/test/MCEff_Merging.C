#include <TH2F.h>
#include <TFile.h>
#include <TGraph.h>
#include <TGraphAsymmErrors.h>


void MCEff_Merging()
{
  gStyle->SetPaintTextFormat("5.2f"); 

  TFile* out = new TFile("MCEff.root","RECREATE");

  out->mkdir("Muon");
  out->mkdir("Electron");

//  out->mkdir("ttbar/Muon");
//  out->mkdir("ttbar/Electron");


  TDirectory *dMu = (TDirectory*)out->Get("Muon");
  TDirectory *dElec = (TDirectory*)out->Get("Electron");


 // Open the input files

  TFile* fInput = TFile::Open("LostLeptonEffFromMC.root");
  TDirectory *dInput = (TDirectory*)fInput->Get("LostLeptonBkgMCEffCalculator");

 // new Histogramms for output

  TH1F *muonAccSum = new TH1F();
  TH1F *muonAccPassed = new TH1F();
  TH1F *muonAccSum2 = new TH1F();
  TH1F *muonAccEff2 = new TH1F();

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

  TH2F *elecRecoSum = new TH2F();
  TH2F *elecRecoEff = new TH2F();

  TH2F *elecIsoSum = new TH2F();
  TH2F *elecIsoEff = new TH2F();




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
  muonAccEff2->SetTitle("#mu acc. eff.;#slash{H}_{T};eff.");
  muonAccEff2->Sumw2();
  muonAccEff2->Divide(muonAccSum2);

std::cout<<"jup"<<std::endl;
 // third version of acceptance eff
  muonAccSum3 = (TH2F*)dInput->Get("MuonAccFailed3");
  muonAccSum3->SetName("MuonAccSum3");
  muonAccSum3->Sumw2();
  muonAccSum3->Add( (TH2F*)dInput->Get("MuonAccPassed3") );

  muonAccEff3 = (TH2F*)dInput->Get("MuonAccPassed3");
  muonAccEff3->SetName("MuonAccEff3");
  muonAccEff3->SetTitle("#mu acc. eff.;#slash{H}_{T};nJets");
  muonAccEff3->Sumw2();
  muonAccEff3->Divide(muonAccSum3);

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
  muonRecoEff->Divide(muonRecoSum);


  muonRecoSum2 = (TH2F*)dInput->Get("MuonRecoFailed2");
  muonRecoSum2->SetName("TotalNumberMuonsAfterAcc2");
  muonRecoSum2->Sumw2();
  muonRecoSum2->Add( ( TH2F*)dInput->Get("MuonRecoPassed2") );

  muonRecoEff2 = (TH2F*)dInput->Get("MuonRecoPassed2");
  muonRecoEff2->SetName("MuonRecoEff2");
  muonRecoEff2->SetTitle("#mu reco. eff.; #Delta R;#mu p_{T};Eff.");
  muonRecoEff2->Sumw2();
  muonRecoEff2->Divide(muonRecoSum2);


  // muon isolation
  
  muonIsoSum = (TH2F*)dInput->Get("muonIsoFailed");
  muonIsoSum->SetName("TotalNumberMuonsAfterReco");
  muonIsoSum->Sumw2();
  muonIsoSum->Add( ( TH2F*)dInput->Get("muonIsoPassed") );

  muonIsoEff = (TH2F*)dInput->Get("muonIsoPassed");
  muonIsoEff->SetName("MuonIsoEff");
  muonIsoEff->SetTitle("MuonIsoEff;#delta R;RelPT;Eff.");
  muonIsoEff->Sumw2();
  muonIsoEff->Divide(muonIsoSum);


  muonIsoSum2 = (TH2F*)dInput->Get("muonIsoFailed2");
  muonIsoSum2->SetName("TotalNumberMuonsAfterReco2");
  muonIsoSum2->Sumw2();
  muonIsoSum2->Add( ( TH2F*)dInput->Get("muonIsoPassed2") );

  muonIsoEff2 = (TH2F*)dInput->Get("muonIsoPassed2");
  muonIsoEff2->SetName("MuonIsoEff2");
  muonIsoEff2->SetTitle("#mu iso. eff.; #Delta R;#mu p_{T};Eff.");
  muonIsoEff2->Sumw2();
  muonIsoEff2->Divide(muonIsoSum2);

  // MTW cut
  MTW = (TH2F*)dInput->Get("MTW");
  MTW->SetName("MTW");
  MTW->SetTitle("MTW;MTW;MHT;Eff.");
  MTW->Sumw2();


  dMu->cd();
  muonAccSum->Write();
  muonAccEff3->Write();
  MTW->Write();

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

/////////////////////////// electron ////////////////////////

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
  elecAccEff2->SetTitle("e acc. eff.;#slash{H}_{T};eff.");
  elecAccEff2->Sumw2();
  elecAccEff2->Divide(elecAccSum2);

 // third version of acceptance eff
  elecAccSum3 = (TH2F*)dInput->Get("ElecAccFailed3");
  elecAccSum3->SetName("ElecAccSum3");
  elecAccSum3->Sumw2();
  elecAccSum3->Add( (TH2F*)dInput->Get("ElecAccPassed3") );

  elecAccEff3 = (TH2F*)dInput->Get("ElecAccPassed3");
  elecAccEff3->SetName("ElecAccEff3");
  elecAccEff3->SetTitle("e acc. eff.;#slash{H}_{T};nJets");
  elecAccEff3->Sumw2();
  elecAccEff3->Divide(elecAccSum3);


  // elec reco eff
  elecRecoSum = (TH2F*)dInput->Get("elecIdFailed");
  elecRecoSum->SetName("TotalNumberElecAfterAcc");
  elecRecoSum->Sumw2();
  elecRecoSum->Add( ( TH2F*)dInput->Get("elecIdPassed") );

  elecRecoEff = (TH2F*)dInput->Get("elecIdPassed");
  elecRecoEff->SetName("ElecRecoEff");
  elecRecoEff->SetTitle("e reco. eff.; #Delta R;RelPT;Eff.");
  elecRecoEff->Sumw2();
  elecRecoEff->Divide(elecRecoSum);

 // second reco version
  elecRecoSum2 = (TH2F*)dInput->Get("elecIdFailed2");
  elecRecoSum2->SetName("TotalNumberElecAfterAcc2");
  elecRecoSum2->Sumw2();
  elecRecoSum2->Add( ( TH2F*)dInput->Get("elecIdPassed2") );

  elecRecoEff2 = (TH2F*)dInput->Get("elecIdPassed2");
  elecRecoEff2->SetName("ElecRecoEff2");
  elecRecoEff2->SetTitle("e reco. eff.; #Delta R;e p_{T};Eff.");
  elecRecoEff2->Sumw2();
  elecRecoEff2->Divide(elecRecoSum2);



  // elec iso eff
  elecIsoSum = (TH2F*)dInput->Get("elecIsoFailed");
  elecIsoSum->SetName("TotalNumberelecsAfterReco");
  elecIsoSum->Sumw2();
  elecIsoSum->Add( ( TH2F*)dInput->Get("elecIsoPassed") );

  elecIsoEff = (TH2F*)dInput->Get("elecIsoPassed");
  elecIsoEff->SetName("ElecIsoEff");
  elecIsoEff->SetTitle("e iso. eff.; #Delta R;RelPT;Eff.");
  elecIsoEff->Sumw2();
  elecIsoEff->Divide(elecIsoSum);

  elecIsoSum2 = (TH2F*)dInput->Get("elecIsoFailed2");
  elecIsoSum2->SetName("TotalNumberelecsAfterReco2");
  elecIsoSum2->Sumw2();
  elecIsoSum2->Add( ( TH2F*)dInput->Get("elecIsoPassed2") );

  elecIsoEff2 = (TH2F*)dInput->Get("elecIsoPassed2");
  elecIsoEff2->SetName("ElecIsoEff2");
  elecIsoEff2->SetTitle("e iso. eff.; #Delta R;e p_{T};Eff.");
  elecIsoEff2->Sumw2();
  elecIsoEff2->Divide(elecIsoSum2);


  // write to file
  dElec->cd();

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
  // close all files and write to output
  out->Write();
  out->Close();
  fInput->Close();
}
