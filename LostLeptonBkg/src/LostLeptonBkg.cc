// -*- C++ -*-
//
// Package:    LostLeptonBkg
// Class:      LostLeptonBkg
// 
/**\class LostLeptonBkg LostLeptonBkg.cc RA2Classic/LostLeptonBkg/src/LostLeptonBkg.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Arne-Rasmus Draeger,,,uni-hamburg
//         Created:  Tue Sep 25 13:40:40 CEST 2012
// $Id$
//
//

#include "RA2Classic/LostLeptonBkg/interface/LostLeptonBkg.h"
#include "DataFormats/Math/interface/deltaPhi.h"
#include <DataFormats/Math/interface/deltaR.h>
#include <DataFormats/PatCandidates/interface/Jet.h>
#include "RA2Classic/LostLeptonBkg/interface/MCEffCalculator.h"


//
// constants, enums and typedefs
//


//
// static data member definitions
//

//
// constructors and destructor
//
LostLeptonBkg::LostLeptonBkg(const edm::ParameterSet& iConfig)
{
   HtJetsTag_ = iConfig.getParameter<edm::InputTag>("HTJets");
   MhtTag_ = iConfig.getParameter<edm::InputTag>("MhtTag");
   MetTag_ = iConfig.getParameter<edm::InputTag>("MetTag");
   MuonTag_ = iConfig.getParameter<edm::InputTag>("MuonTag");
   evtWeightTag_ = iConfig.getParameter<edm::InputTag> ("EventWeightTag");
   CaloJetTag_ = iConfig.getParameter<edm::InputTag>("CaloJetTag");
   EfficiencyFileName_ = iConfig.getParameter <std::string> ("EfficiencyFileName");

   // input cuts
   MTWMax_ = iConfig.getParameter <double> ("MTWMax");
   MTWCut_ = iConfig.getParameter <bool> ("MTWCut");
   MinMuPT_ = iConfig.getParameter <double> ("MinMuPT");
   MinElecPT_ = iConfig.getParameter <double> ("MinElecPT");
   //register your products


   //if do put with a label
   produces<double>("LostLeptonWeight");
   produces<double>("Met");
   produces<int>("nLeptons");
   produces<double>("MuPt");
   produces<double>("MuEta");
   produces<double>("MuPhi");
   produces<double>("deltaRMuJet");
   produces<double>("deltaRMuMHT");
   produces<double>("deltaPtMuJet");
   produces<double>("deltaPtClosestJetMu");
   produces<int>("nCaloJets");
   produces<double> ("MTW");
   produces<int> ("MTWCut");
   produces<double> ("mtwCorrectionWeight");
   produces<double>("muonTotalWeight");
   produces<double>("elecTotalWeight");
   produces<double>("muonIsoWeight");
   produces<double>("muonRecoWeight");
   produces<double>("muonAccWeight");
   produces<double>("elecIsoWeight");
   produces<double>("elecRecoWeight");
   produces<double>("elecAccWeight");
   produces<double>("mtwCorrection");

   // used efficiencies
   produces<double>("muonAccEff");
   produces<double>("elecAccEff");
   produces<double>("muonRecoEff");
   produces<double>("elecRecoEff");
   produces<double>("muonIsoEff");
   produces<double>("elecIsoEff");

   //now do what ever other initialization is needed
  
}


LostLeptonBkg::~LostLeptonBkg()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
LostLeptonBkg::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   ResetValues();
   
  edm::Handle< edm::View<reco::Candidate> > met;
  iEvent.getByLabel(MetTag_,met);
  if( met.isValid() ) {
    met_ = met->at(0).pt();
  }

  edm::Handle< edm::View<reco::Candidate> > htJets;
  iEvent.getByLabel(HtJetsTag_,htJets);
  if( htJets.isValid() ) {
    nJets_ = htJets->size();
  }
  edm::Handle< edm::View<reco::Candidate> > mht;
  iEvent.getByLabel(MhtTag_,mht);
  if( mht.isValid() ) {
    mht_ = mht->at(0).pt();
  }
   edm::Handle<double> eventWeight;
   iEvent.getByLabel(evtWeightTag_,eventWeight);
   eventWeight_ = *eventWeight;
 


  // Muon criteria
  edm::Handle <edm::View <reco::Candidate> > Mu;
  iEvent.getByLabel(MuonTag_,Mu);
  edm::Handle <edm::View <pat::Jet> > caloJets;
  iEvent.getByLabel(CaloJetTag_, caloJets);



  // set up the result weight


  if (caloJets.isValid() )
  {
	nCaloJets_=caloJets->size();
  }

  // start the prediciton from Muon CS

  if(Mu.isValid() ) 
  {
	// the jet must not have the same energy as the muon
	nMu_ = Mu->size();
	
	if (nMu_!=1) std::cout<<"Number of Muons="<<nMu_<<std::endl;
	MuPt_ = Mu->at(0).pt();
	MuEta_ = Mu->at(0).eta();
	MuPhi_ = Mu->at(0).phi();
	std::cout<<"MuFoundStepOneCompleted!"<<std::endl;

  	// calculate relative values for the muon and jets usw.

	//delta R with the closest jet and ptLep/ptJet muonpt vs MHT
	if(caloJets.isValid() )
	{
//	std::pair<double,double> DRtoClostestJet;
//	PtclosestJet = MCEffCalculator::DRToClosestJet(caloJets, 2,3,4);
		std::cout<<"CaloJetsValid"<<std::endl;
		deltaRMuJet_ = MCEffCalculator::DRToClosestJet(iEvent,CaloJetTag_, MuEta_, MuPhi_).first;
		PtClosestJet_ = MCEffCalculator::DRToClosestJet(iEvent,CaloJetTag_, MuEta_, MuPhi_).second;
		deltaPtClosestJetMu_ =PtClosestJet_/MuPt_;
		std::cout<<"deltaRandRelPTcalculated:"<<deltaPtClosestJetMu_<<std::endl;
		
  	}
	
	// Delta R between muon and MHT
	if( mht.isValid() ) 
	{
    		deltaRMuMHT_ = deltaR(mht->at(0).eta(), mht->at(0).phi(),MuEta_,MuPhi_);
		std::cout<<"MHT is valid"<<std::endl;
		
	}
	// calculate MTw
	mtw_= MCEffCalculator::MTWCalculator(iEvent, MetTag_, MuPt_, MuPhi_);
	std::cout<<"mtw calculated. MTW="<<mtw_<<std::endl;
	
	// do the MTW cut
	std::cout<<"MTWCut_bool"<<MTWCut_<<std::endl;
	std::cout<<"MTWMax_"<<MTWMax_<<std::endl;

		// calculate lost lepton Estimation weights from the eff.	
		// calulcate the delta r and lepton bin for iso and reco
		std::cout<<"MuonFound starting to get the curent efficiencies"<<std::endl;
		int muonIsoXaxis= MuonIsoEff_->GetXaxis()->FindBin(deltaRMuJet_);
		// check if the deltaRmuJet is greater thatn the maximum in the histogramm
		std::cout<<"a"<<std::endl;
		if (muonIsoXaxis > MuonIsoEff_->GetNbinsX()) muonIsoXaxis-=1;
		std::cout<<"muonIsoXaxis has been found"<<std::endl;
		int muonIsoYaxis= MuonIsoEff_->GetYaxis()->FindBin(deltaPtClosestJetMu_);
		// check if the deltaPTclosestJetMu is greater than the maximum stored in the histogramm
		if (muonIsoYaxis > MuonIsoEff_->GetNbinsY()) muonIsoYaxis-=1;
		std::cout<<"1";
		int muonRecoXaxis = MuonRecoEff_->GetXaxis()->FindBin(deltaRMuJet_);
		if (muonRecoXaxis > MuonRecoEff_->GetNbinsX() ) muonRecoXaxis-=1;
		std::cout<<"2";
		int muonRecoYaxis = MuonRecoEff_->GetYaxis()->FindBin(deltaPtClosestJetMu_);
		if (muonRecoYaxis > MuonRecoEff_->GetNbinsY() ) muonRecoYaxis-=1;
		std::cout<<"3";

		int elecIsoXaxis= ElecIsoEff_->GetXaxis()->FindBin(deltaRMuJet_);
		if (elecIsoXaxis > ElecIsoEff_->GetNbinsX() ) elecIsoXaxis-=1;
		std::cout<<"4";
		int elecIsoYaxis= ElecIsoEff_->GetYaxis()->FindBin(deltaPtClosestJetMu_);
		if (elecIsoYaxis > ElecIsoEff_->GetNbinsY() ) elecIsoYaxis-=1;
		std::cout<<"5";
		int elecRecoXaxis = ElecRecoEff_->GetXaxis()->FindBin(deltaRMuJet_);
		if (elecRecoXaxis > ElecRecoEff_->GetNbinsX() ) elecRecoXaxis-=1;
		std::cout<<"6";
		int elecRecoYaxis = ElecRecoEff_->GetYaxis()->FindBin(deltaPtClosestJetMu_);
		if (elecRecoYaxis > ElecRecoEff_->GetNbinsY() ) elecRecoYaxis-=1;
		std::cout<<"7";


		// LostLepton background estimation weights for each contribution
		std::cout<<"b"<<std::endl;
		// the muon isolation fraction
		muonIsoEff_ = MuonIsoEff_->GetBinContent(muonIsoXaxis,muonIsoYaxis );
		muonIsoWeight_ = eventWeight_ * (1 - muonIsoEff_)/muonIsoEff_;	
		std::cout<<"c"<<std::endl;
		// the muon reconstruciton fraction
		muonRecoEff_ = MuonRecoEff_->GetBinContent(muonRecoXaxis,muonRecoYaxis );
		muonRecoWeight_ = eventWeight_ * 1/muonIsoEff_ * (1-muonRecoEff_)/muonRecoEff_;
		std::cout<<"d"<<std::endl;
		// the muon out of acceptance fraction
		muonAccWeight_ = eventWeight_ * 1/muonIsoEff_ * 1/muonRecoEff_ *(1-MuonAccEff_)/MuonAccEff_;
		std::cout<<"e"<<std::endl;
		// total muon weight
		muonTotalWeight_ = muonIsoWeight_ + muonRecoWeight_ + muonAccWeight_;



		// electron weight
		elecAccWeight_ = (eventWeight_ + muonTotalWeight_)*ElecAccEff_;	

		// the electron reconstruciton fraction
		elecRecoEff_ = ElecRecoEff_->GetBinContent(elecRecoXaxis, elecRecoYaxis);
		elecRecoWeight_ = elecAccWeight_*elecRecoEff_;

		// the electron isolation fraction
		elecIsoEff_ = ElecIsoEff_->GetBinContent(elecIsoXaxis, elecIsoYaxis);  
		elecIsoWeight_ = elecRecoWeight_*elecIsoEff_;

		//total elec weight
		elecTotalWeight_ = elecAccWeight_ + elecRecoWeight_ + elecIsoWeight_;

		//additional corrections
		if (MTWCut_) mtwCorrection_ = muonTotalWeight_ + elecTotalWeight_ + (muonTotalWeight_ + elecTotalWeight_) * ( ( 1 / MTWEff_->GetBinContent(MTWEff_->GetXaxis()->FindBin(mht_) ) ) - 1);
		
		// total lostlepton weight
		resultWeight_ = muonTotalWeight_ + elecTotalWeight_;
		//if (MTWCut_)resultWeight_= mtwCorrection_;
	std::cout<<"lostleptonweights calculated"<<std::endl;

   std::auto_ptr<int> pOut3(new int(nMu_));
   iEvent.put(pOut3, "nLeptons");
   std::auto_ptr<double> pOut4(new double(MuPt_));
   iEvent.put(pOut4, "MuPt");
   std::auto_ptr<double> pOut5(new double(MuEta_));
   iEvent.put(pOut5, "MuEta");
   std::auto_ptr<double> pOut6(new double(MuPhi_));
   iEvent.put(pOut6, "MuPhi");
   std::auto_ptr<double> pOut7(new double(deltaRMuJet_));
   iEvent.put(pOut7, "deltaRMuJet");
   std::auto_ptr<double> pOut8(new double(deltaRMuMHT_));
   iEvent.put(pOut8, "deltaRMuMHT");
   std::auto_ptr<double> pOut9(new double(PtClosestJet_));
   iEvent.put(pOut9, "deltaPtMuJet");
   std::auto_ptr<double> pOut9a(new double(deltaPtClosestJetMu_));
   iEvent.put(pOut9a, "deltaPtClosestJetMu");
   std::auto_ptr<int> pOut10(new int(nCaloJets_));
   iEvent.put(pOut10, "nCaloJets");
   std::auto_ptr<double> pOut11a(new double(mtw_));
   iEvent.put(pOut11a, "MTW");
   std::auto_ptr<int> pOut32(new int(MTWCut_) );
   iEvent.put(pOut32, "MTWCut");

   std::auto_ptr<double> aOut1(new double(MuonAccEff_));
   iEvent.put(aOut1,"muonAccEff");
   std::auto_ptr<double> aOut2(new double(ElecAccEff_));
   iEvent.put(aOut2,"elecAccEff");
   std::auto_ptr<double> aOut3(new double(muonRecoEff_));
   iEvent.put(aOut3,"muonRecoEff");
   std::auto_ptr<double> aOut4(new double(elecRecoEff_));
   iEvent.put(aOut4,"elecRecoEff");
   std::auto_ptr<double> aOut5(new double(muonIsoEff_));
   iEvent.put(aOut5,"muonIsoEff");
   std::auto_ptr<double> aOut6(new double(elecIsoEff_));
   iEvent.put(aOut6,"elecIsoEff");


   // store all the different weights in the event
   
   std::auto_ptr<double> pOut111(new double(mtwCorrection_));
   iEvent.put(pOut111, "mtwCorrectionWeight");
   std::auto_ptr<double> pOut1(new double(resultWeight_));
   iEvent.put(pOut1, "LostLeptonWeight");
   std::cout<<"resultWeight_"<<resultWeight_<<std::endl;
   std::auto_ptr<double> pOut2a(new double(muonTotalWeight_));
   iEvent.put(pOut2a, "muonTotalWeight");
   std::auto_ptr<double> pOut3b(new double(elecTotalWeight_));
   iEvent.put(pOut3b, "elecTotalWeight");
   std::auto_ptr<double> pOut4b(new double(muonIsoWeight_));
   iEvent.put(pOut4b, "muonIsoWeight");
   std::auto_ptr<double> pOut5b(new double(muonRecoWeight_));
   iEvent.put(pOut5b, "muonRecoWeight");
   std::auto_ptr<double> pOut6b(new double(muonAccWeight_));
   iEvent.put(pOut6b, "muonAccWeight");
   std::auto_ptr<double> pOut7b(new double(elecIsoWeight_));
   iEvent.put(pOut7b, "elecIsoWeight");
   std::auto_ptr<double> pOut8b(new double(elecRecoWeight_));
   iEvent.put(pOut8b, "elecRecoWeight");
   std::auto_ptr<double> pOut9b(new double(elecAccWeight_));
   iEvent.put(pOut9b, "elecAccWeight");
   std::cout<<"MuonValidIfSchleifeFertig"<<std::endl;
  }
/* This is an event example
   //Read 'ExampleData' from the Event
   Handle<ExampleData> pIn;
   iEvent.getByLabel("example",pIn);

   //Use the ExampleData to create an ExampleData2 which 
   // is put into the Event
   std::auto_ptr<ExampleData2> pOut(new ExampleData2(*pIn));
   iEvent.put(pOut);
*/

/* this is an EventSetup example
   //Read SetupData from the SetupRecord in the EventSetup
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
*/

   std::auto_ptr<double> pOut2(new double(met_));
   iEvent.put(pOut2, "Met");

   std::cout<<"EventLoopDoneExitingPrdocuer"<<std::endl;
}

// ------------ method called once each job just before starting event loop  ------------
void 
LostLeptonBkg::beginJob()
{
	// make the histogramms for the efficiencies available
  std::string fileName("RA2Classic/LostLeptonBkg/data/");
  fileName += EfficiencyFileName_;
  edm::FileInPath fip(fileName);


  TFile* effInput = TFile::Open(fip.fullPath().c_str());

  TDirectory *dMuon = (TDirectory*)effInput->Get("Muon");
  
  TDirectory *dElec = (TDirectory*)effInput->Get("Electron");
  
  //muons
  // acceptance
  MuonAccSum_ = (TH1F*)dMuon->Get("MuonAccSum");
  MuonAccPassed_ = (TH1F*)dMuon->Get("MuonAccPassed");
  MuonAccEff_ = MuonAccPassed_->Integral(MuonAccPassed_->FindBin(MinMuPT_),(MuonAccPassed_->GetNbinsX()+1))/MuonAccSum_->Integral(0,(MuonAccSum_->GetNbinsX()+1));

  std::cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!muonAccEff_"<<MuonAccEff_<<std::endl;
  std::cout<<"MinMuPT is set to"<<MinMuPT_<<std::endl;
  std::cout<<"Integral boarders"<<MuonAccPassed_->FindBin(MinMuPT_)<<std::endl;
  std::cout<<"The Integral for PassedMuons"<<MuonAccPassed_->Integral(MuonAccPassed_->FindBin(MinMuPT_),(MuonAccPassed_->GetNbinsX()+1))<<std::endl;
  std::cout<<"The Integral for All muons"<<MuonAccSum_->Integral(0,(MuonAccSum_->GetNbinsX()+1))<<std::endl;

  //MTW cut eff
  if (MTWCut_)
  {
  	TH2F *MTWTemp = (TH2F*)dMuon->Get("MTW");
  	int MHTbins = MTWTemp->GetNbinsY();
  	// creates the array with the lower edges of the MTW parametrizaion
  	double mhtbins [MHTbins];
  	// the binN=0 is the underflow there are n bins and we need n+1 lowerbinedges for the mhtbins array
  	for (int i=1;i < MHTbins+2 ;i++)
  	{
		mhtbins [i] = MTWTemp->GetYaxis()->GetBinLowEdge(i);
		std::cout<<"MTWlowedeNr:"<<i<<" with the value:"<<mhtbins [i]<<std::endl;
  	}
  	MTWEff_ = new TH1F("MTWEff", "MTWEff", MHTbins, mhtbins);
  	for (int i=1; i < MHTbins+2 ;i++)
  	{
		std::cout<<"MTWMax_"<<MTWMax_<<std::endl;
		std::cout<<"MTWBin"<<MTWTemp->GetXaxis()->FindBin(MTWMax_)<<std::endl;
		double passed = MTWTemp->Integral (1,MTWTemp->GetXaxis()->FindBin(MTWMax_),i, i);
		std::cout<<"The amount of passed for the MTW cut is"<<passed<<std::endl;
		double failed = MTWTemp->Integral (MTWTemp->GetXaxis()->FindBin(MTWMax_),MTWTemp->GetNbinsX()+1,i,i);
		std::cout<<"The amount of failed for the MTW cut is"<<failed<<std::endl;
		double sum = passed + failed;
		std::cout<<"MTWEff for the "<<i<<" bin:"<<MTWEff_->GetYaxis()->GetBinLowEdge(i) <<"is"<<passed/sum<<std::endl;
		MTWEff_->SetBinContent(i,passed/sum);
  	}
  }
//  for (int i=1; 

  

  // reconstruction
  MuonRecoEff_ = (TH2F*)dMuon->Get("MuonRecoEff");

  // isolation

  MuonIsoEff_ = (TH2F*)dMuon->Get("MuonIsoEff");


  //electrons
  // acceptance
  ElecAccSum_ = (TH1F*)dElec->Get("ElecAccSum");
  ElecAccPassed_ = (TH1F*)dElec->Get("ElecAccPassed");
  ElecAccEff_ = ElecAccPassed_->Integral(ElecAccPassed_->FindBin(MinElecPT_),(ElecAccPassed_->GetNbinsX()+1))/ElecAccSum_->Integral(0,(ElecAccSum_->GetNbinsX()+1));
  std::cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!elecAccEff_"<<ElecAccEff_<<std::endl;
  
  // reconstruction
  ElecRecoEff_ = (TH2F*)dElec->Get("ElecRecoEff");

  // isolation

  ElecIsoEff_ = (TH2F*)dElec->Get("ElecIsoEff");
  

}
void 
LostLeptonBkg::ResetValues()
{
	met_ =-1;
	mht_ = -1;
	mtw_ =-1;
	nMu_ = -1;
	MuPt_ = -1;
	MuEta_ =-1;
	MuPhi_ = -1;
	nJets_ = -1;
	nCaloJets_ = -1;
	

	deltaRMuJet_ = 5000;
	deltaRMuMHT_ = 5000;
	deltaRMuJet_ =5000;
	deltaPtClosestJetMu_ = 5000;
	PtClosestJet_= -1;	

	eventWeight_=0;


	muonIsoEff_=-1;
	muonIsoWeight_=-1;

	muonRecoEff_=-1;
	muonRecoWeight_=-1;
	
	muonAccWeight_=-1;

	elecIsoEff_=-1;
	elecIsoWeight_=-1;
	elecRecoEff_=-1;
	elecRecoWeight_=-1;

	elecAccWeight_=-1;

	muonTotalWeight_=-1;
	elecTotalWeight_=-1;
	mtwCorrection_=0;


}
// ------------ method called once each job just after ending the event loop  ------------
void 
LostLeptonBkg::endJob() {
}

// ------------ method called when starting to processes a run  ------------
void 
LostLeptonBkg::beginRun(edm::Run&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
LostLeptonBkg::endRun(edm::Run&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
LostLeptonBkg::beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
LostLeptonBkg::endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
LostLeptonBkg::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(LostLeptonBkg);
