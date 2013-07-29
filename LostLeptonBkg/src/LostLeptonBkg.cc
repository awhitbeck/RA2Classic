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
// $Id: LostLeptonBkg.cc,v 1.11 2013/03/21 17:49:07 adraeger Exp $
//
//
#include <TString.h>
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
   MuonRecoTag_ = iConfig.getParameter<edm::InputTag>("MuonRecoTag");
   ElecTag_ = iConfig.getParameter<edm::InputTag>("ElecTag");
   evtWeightTag_ = iConfig.getParameter<edm::InputTag> ("EventWeightTag");
   CaloJetTag_ = iConfig.getParameter<edm::InputTag>("CaloJetTag");
   EfficiencyFileName_ = iConfig.getParameter <std::string> ("EfficiencyFileName");

   // input cuts
   MTWMax_ = iConfig.getParameter <double> ("MTWMax");
   MTWCut_ = iConfig.getParameter <bool> ("MTWCut");
   MinMuPT_ = iConfig.getParameter <double> ("MinMuPT");
   MinElecPT_ = iConfig.getParameter <double> ("MinElecPT");
   HTTag_ = iConfig.getParameter<edm::InputTag>("HTTag");
   MHTTag_ = iConfig.getParameter<edm::InputTag>("MHTTag");
   NVTag_ = iConfig.getParameter<edm::InputTag>("VertexCollection");

   //input corrections & uncertainties
   DiLepCorrection_ = iConfig.getParameter <double> ("DiLepCorrection");
   DiLepCorrectionUp_ = iConfig.getParameter <double> ("DiLepCorrectionUp");
   DiLepCorrectionDown_ = iConfig.getParameter <double> ("DiLepCorrectionDown");
   TAPUncertainties_ = iConfig.getParameter <bool> ("TagAndProbeUncertainty");
   TAPConstUncertainty_ = iConfig.getParameter <bool> ("TagAndProbeConstUncertainty");
   TAPUncertaintiesHTNJET_ = iConfig.getParameter <bool> ("TAPUncertaintiesHTNJET");
   MetJetTagUp_= iConfig.getParameter<edm::InputTag>("MetJetTagUp");
   MetJetTagDown_= iConfig.getParameter<edm::InputTag>("MetJetTagDown");
   MTWUncertaintyUp_ = iConfig.getParameter <double> ("MTWUncertaintyUp");
   MTWUncertaintyDown_ = iConfig.getParameter <double> ("MTWUncertaintyDown");
   muonAccUncertaintyUp_= iConfig.getParameter <double> ("muonAccUncertaintyUp");
   muonAccUncertaintyDown_= iConfig.getParameter <double> ("muonAccUncertaintyDown");
   elecAccUncertaintyUp_= iConfig.getParameter <double> ("elecAccUncertaintyUp");
   elecAccUncertaintyDown_= iConfig.getParameter <double> ("elecAccUncertaintyDown");
   diBosonDown_ = iConfig.getParameter <double> ("diBosonDown");
   nonClosureLowNJet_ = iConfig.getParameter <double> ("nonClosureLowNJet");
   nonClosureHighNJet_ = iConfig.getParameter <double> ("nonClosureHighNJet");
   statErrorEffmaps_ = iConfig.getParameter <bool> ("statErrorEffmaps");
   debug_ = iConfig.getParameter <bool> ("debug");

	// Iso plots for AN
	   IsoPlots_ = iConfig.getParameter <bool> ("IsoPlots");



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
   //if(debug_)	std::cout<<"LostLeptonBkg:EventLoopStarted"<<std::endl;
   using namespace edm;
   ResetValues();
   
  edm::Handle< edm::View<reco::Candidate> > met;
  iEvent.getByLabel(MetTag_,met);
  if( met.isValid() ) {
    met_ = met->at(0).pt();
  }

// up down for mt cut efficiency

  edm::Handle< edm::View<reco::Candidate> > metup;
  iEvent.getByLabel(MetJetTagUp_,metup);
  if( metup.isValid() ) {
    metup_ = metup->at(0).pt();
  }
  edm::Handle< edm::View<reco::Candidate> > metdown;
  iEvent.getByLabel(MetJetTagDown_,metdown);
  if( metdown.isValid() ) {
    metdown_ = metdown->at(0).pt();
  }

  edm::Handle< edm::View<reco::Candidate> > htJets;
  iEvent.getByLabel(HtJetsTag_,htJets);
  if( htJets.isValid() ) 
  {
	nJets_ = htJets->size();
  }
  edm::Handle< edm::View<reco::Candidate> > mht;
  iEvent.getByLabel(MHTTag_,mht);
  mht_ = mht->at(0).pt();

  edm::Handle<double> eventWeight;
  iEvent.getByLabel(evtWeightTag_,eventWeight);
  eventWeight_ = *eventWeight;
  edm::Handle<double> ht;
  iEvent.getByLabel(HTTag_,ht);
  ht_ = *ht;
  edm::Handle<reco::VertexCollection> vertices;
  iEvent.getByLabel(NVTag_,vertices);
  if( vertices.isValid() ) 
  {
    	nV_ = vertices->size();
  }

 


  // Muon criteria
  edm::Handle <edm::View <reco::Candidate> > Mu;
  iEvent.getByLabel(MuonTag_,Mu);
  edm::Handle <edm::View <reco::Candidate> > Elec;
  iEvent.getByLabel(ElecTag_,Elec);
  edm::Handle <edm::View <reco::CaloJet> > caloJets;
  iEvent.getByLabel(CaloJetTag_, caloJets);
  edm::Handle <edm::View <reco::Candidate> > RecoMu;
  iEvent.getByLabel(MuonRecoTag_,RecoMu);



  // set up the result weight


  if (caloJets.isValid() )
  {
	nCaloJets_=caloJets->size();
  }


  // start the prediciton from Muon CS

  // if no isolated muon exist but reconstructed ones start this
  if (Mu->size() ==0 && RecoMu->size()>0)
  {
	nRecoMu_ = RecoMu->size();

// calculate mtw for all reco muons
	int indexZ=1;
	for( edm::View <reco::Candidate>::const_iterator MuIDCand = RecoMu->begin(); MuIDCand!=RecoMu->end();MuIDCand++)
	{
		if(indexZ==1)
		{
			recoMtw1_= MCEffCalculator::MTWCalculator(iEvent, MetTag_,MuIDCand->pt(),MuIDCand->phi());
//			recoMuDeltaPTClosestJet2_ = MuIDCand->pt()/DRToClosestJet(iEvent, caloJetTag_,MuIDCand->eta(),MuIDCand->phi()).second;
//			recoMuDeltaRClosestJet2_ = DRToClosestJet(iEvent, caloJetTag_,MuIDCand->eta(),MuIDCand->phi()).first;
		}
		if(indexZ==2)
		{
			recoMtw2_= MCEffCalculator::MTWCalculator(iEvent, MetTag_,MuIDCand->pt(),MuIDCand->phi());
//			recoMuDeltaPTClosestJet2_ = MuIDCand->pt()/DRToClosestJet(iEvent, caloJetTag_,MuIDCand->eta(),MuIDCand->phi()).second;
//			recoMuDeltaRClosestJet2_ = DRToClosestJet(iEvent, caloJetTag_,MuIDCand->eta(),MuIDCand->phi()).first;
		}
		if(indexZ==3)	
		{
			recoMtw3_= MCEffCalculator::MTWCalculator(iEvent, MetTag_,MuIDCand->pt(),MuIDCand->phi());
//			recoMuDeltaPTClosestJet3_ = MuIDCand->pt()/DRToClosestJet(iEvent, caloJetTag_,MuIDCand->eta(),MuIDCand->phi()).second;
//			recoMuDeltaRClosestJet3_ = DRToClosestJet(iEvent, caloJetTag_,MuIDCand->eta(),MuIDCand->phi()).first;
		}
		if(indexZ==4)
		{
			recoMtw4_= MCEffCalculator::MTWCalculator(iEvent, MetTag_,MuIDCand->pt(),MuIDCand->phi());
//			recoMuDeltaPTClosestJet4_ = MuIDCand->pt()/DRToClosestJet(iEvent, caloJetTag_,MuIDCand->eta(),MuIDCand->phi()).second;
//			recoMuDeltaRClosestJet4_ = DRToClosestJet(iEvent, caloJetTag_,MuIDCand->eta(),MuIDCand->phi()).first;
		}
		if(indexZ==5)
		{
			recoMtw5_= MCEffCalculator::MTWCalculator(iEvent, MetTag_,MuIDCand->pt(),MuIDCand->phi());
//			recoMuDeltaPTClosestJet5_ = MuIDCand->pt()/DRToClosestJet(iEvent, caloJetTag_,MuIDCand->eta(),MuIDCand->phi()).second;
//			recoMuDeltaRClosestJet5_ = DRToClosestJet(iEvent, caloJetTag_,MuIDCand->eta(),MuIDCand->phi()).first;
		}
		indexZ++;
	}
	

  }



nMu_ = Mu->size();
nElec_  = Elec->size();
if (nMu_>0 )
{
lepPt_ = Mu->at(0).pt();
lepEta_ = Mu->at(0).eta();
lepPhi_ = Mu->at(0).phi();
}
if (nElec_>0 )
{
lepPt_ = Elec->at(0).pt();
lepEta_ = Elec->at(0).eta();
lepPhi_ = Elec->at(0).phi();
}

  // true if one isolated muon is found. normal cs case
  if(Mu.isValid() && Mu->size() == 1 && Elec->size()==0 )
  {
	// the jet must not have the same energy as the muon
	nMu_ = Mu->size();
//	if(debug_)	std::cout<<"LostLeptonBkg:MuTag="<<MuonTag_<<std::endl;
	if (nMu_!=1) if(debug_)	std::cout<<"Number of Muons="<<nMu_<<std::endl;
	MuPt_ = Mu->at(0).pt();
	MuEta_ = Mu->at(0).eta();
	MuPhi_ = Mu->at(0).phi();

	// remove muon from nOfJets if muon is clustered as single jet

//	for (unsigned int i=0; i<nJets_;i++)
//	{
//		if( abs(htJets->at(i).pt() - MuPt_)/MuPt_ < 0.1 && deltaR(htJets->at(i).eta(),htJets->at(i).phi(), MuEta_,MuPhi_) < 0.2 ) nJets_-=1;
//	}
//	if(debug_)	std::cout<<"MuFoundStepOneCompleted!"<<std::endl;

  	// calculate relative values for the muon and jets usw.

	//delta R with the closest jet and ptLep/ptJet muonpt vs MHT
	if(caloJets.isValid() )
	{
//	std::pair<double,double> DRtoClostestJet;
//	PtclosestJet = MCEffCalculator::DRToClosestJet(caloJets, 2,3,4);
//		if(debug_)	std::cout<<"CaloJetsValid"<<std::endl;
		deltaRMuJet_ = MCEffCalculator::DRToClosestJet(iEvent,CaloJetTag_, MuEta_, MuPhi_).first;
	if (deltaRMuJet_<0.0001)
	{
		std::cout<<"DeltaRmuJet is samller than 0.0001, it will be set to 0.01"<<std::endl;
		deltaRMuJet_=0.01;
	}
		PtClosestJet_ = MCEffCalculator::DRToClosestJet(iEvent,CaloJetTag_, MuEta_, MuPhi_).second;
		deltaPtClosestJetMu_ =MuPt_/PtClosestJet_;
		genDeltaR_ = MCEffCalculator::DRToClosestJet(iEvent,CaloJetTag_, MuEta_, MuPhi_).first;
		genPTJet_ = MCEffCalculator::DRToClosestJet(iEvent,CaloJetTag_, MuEta_, MuPhi_).second;
		genPTRelJet_ =MuPt_/PtClosestJet_;
		if(debug_)	std::cout<<"deltaRandRelPTcalculated:"<<deltaPtClosestJetMu_<<std::endl;
		
  	}
	
	// Delta R between muon and MHT
	if( mht.isValid() ) 
	{
    		deltaRMuMHT_ = deltaR(mht->at(0).eta(), mht->at(0).phi(),MuEta_,MuPhi_);
//		if(debug_)	std::cout<<"MHT is valid"<<std::endl;
		
	}
	// calculate MTw
	mtw_= MCEffCalculator::MTWCalculator(iEvent, MetTag_, MuPt_, MuPhi_);
	if(debug_)	std::cout<<"MTW"<<mtw_<<std::endl;
	if(debug_)	std::cout<<"mht->at(0).eta()"<<mht->at(0).eta()<<std::endl;
	if(debug_)	std::cout<<"mht->at(0).phi()"<<mht->at(0).phi()<<std::endl;
	if(debug_)	std::cout<<"MuEta_"<<MuEta_<<std::endl;
	if(debug_)	std::cout<<"MuPhi_"<<MuPhi_<<std::endl;


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

if(debug_)	if(debug_)	std::cout<<"-----------------------------------------------------------------------------------StartWeigh2---------------------"<<std::endl;

	// this parametrization is a combination of the first 2 methods for acceptance binned in MHT and Njets eff are used
	// for reco eff parametrized in deltaRMuJet and lepton pt is used
	// the isolation is obtained according to the binbybin method using eff for each search bin obtained from mc
	int muonAccXaxis3= MuonAccEff3_->GetXaxis()->FindBin(mht_);
	if (muonAccXaxis3 > MuonAccEff3_->GetNbinsX()) muonAccXaxis3-=1;
	int muonAccYaxis3= MuonAccEff3_->GetYaxis()->FindBin(nJets_+0.1);
	if (nJets_<3) muonAccYaxis3= MuonAccEff3_->GetYaxis()->FindBin(3);

		
	int muonIsoXaxis2= MuonIsoEff2_->GetXaxis()->FindBin(deltaRMuJet_);
	// check if the deltaRmuJet is greater thatn the maximum in the histogramm
	if(debug_)	std::cout<<"a"<<std::endl;
	if (muonIsoXaxis2 > MuonIsoEff2_->GetNbinsX()) muonIsoXaxis2-=1;
	if (deltaRMuJet_ > MuonIsoEff2_->GetXaxis()->GetXmax() ) 
	{
		std::cout<<"Warning deltaR jet Mu is bigger than maximum delta R in MuonIsoEff2, maximum="<<MuonIsoEff2_->GetXaxis()->GetXmax()<<" with a value of"<<deltaRMuJet_<<std::endl;
		muonIsoXaxis2 = MuonIsoEff2_->GetNbinsX();
	}

	int muonIsoYaxis2= MuonIsoEff2_->GetYaxis()->FindBin(MuPt_);
	// check if the deltaPTclosestJetMu is greater than the maximum stored in the histogramm
	if (muonIsoYaxis2 > MuonIsoEff2_->GetNbinsY()) muonIsoYaxis2-=1;
	if (MuPt_ > MuonIsoEff2_->GetYaxis()->GetXmax() ) 
	{
		std::cout<<"Warning muon pt is bigger than maximum muon PT in MuonIsoEff2, maximum="<<MuonIsoEff2_->GetYaxis()->GetXmax()<<" with a value of"<<MuPt_<<std::endl;
		muonIsoYaxis2 = MuonIsoEff2_->GetNbinsY();
	}
	int muonRecoXaxis2 = MuonRecoEff2_->GetXaxis()->FindBin(deltaRMuJet_);
	if (muonRecoXaxis2 > MuonRecoEff2_->GetNbinsX() ) muonRecoXaxis2-=1;
	if (deltaRMuJet_ > MuonRecoEff2_->GetXaxis()->GetXmax() ) 
	{
		std::cout<<"Warning muon pt is bigger than maximum muon PT in MuonRecoEff2, maximum="<<MuonRecoEff2_->GetXaxis()->GetXmax()<<" with a value of"<<deltaRMuJet_<<std::endl;
		muonRecoXaxis2 = MuonRecoEff2_->GetNbinsX();
	}
	int muonRecoYaxis2 = MuonRecoEff2_->GetYaxis()->FindBin(MuPt_);
	if (muonRecoYaxis2 > MuonRecoEff2_->GetNbinsY() ) muonRecoYaxis2-=1;
	if (MuPt_ > MuonRecoEff2_->GetYaxis()->GetXmax() ) 
	{
		std::cout<<"Warning muon pt is bigger than maximum muon PT in MuonRecoEff2, maximum="<<MuonRecoEff2_->GetYaxis()->GetXmax()<<" with a value of"<<MuPt_<<std::endl;
		muonRecoXaxis2 = MuonRecoEff2_->GetNbinsY();
	}

	muonIsoEff2_ = MuonIsoEff2_->GetBinContent(muonIsoXaxis2,muonIsoYaxis2 );
	if(debug_)	std::cout<<"muonIsoEff2_"<<muonIsoEff2_<<std::endl;
	if (muonIsoEff2_ <0.001 || muonIsoEff2_ > 1) error_+=100;
	if (muonIsoEff2_<0.001) muonIsoEff2_=0.001;
	if (muonIsoEff2_>1 ) muonIsoEff2_=1;
	muonIsoWeight2_ = eventWeight_ * (1 - muonIsoEff2_)/muonIsoEff2_;	
	if(debug_)	std::cout<<"muonIsoWeight2_"<<muonIsoWeight2_<<std::endl;
//	muonIsoWeight2_ =muonBinByBinIsoWeight_;
//	muonIsoEff2_=muonBinByBinIsoEff_;

	muonRecoEff2_ = MuonRecoEff2_->GetBinContent(muonRecoXaxis2,muonRecoYaxis2 );
	if(debug_)	std::cout<<"muonRecoEff2_"<<muonRecoEff2_<<std::endl;
	double muonRecoEff2Error = MuonRecoEff2_->GetBinError(muonRecoXaxis2,muonRecoYaxis2 );
	if (muonRecoEff2_ <0.001 || muonRecoEff2_ > 1) error_+=1000;
	muonRecoWeight2_ = eventWeight_ * 1 / muonIsoEff2_ * (1-muonRecoEff2_)/muonRecoEff2_;
	if(debug_)	std::cout<<"muonRecoWeight2_"<<muonRecoWeight2_<<std::endl;
	muAllIsoWeight2_ =  eventWeight_ * 1 / muonIsoEff2_;
	// the muon out of acceptance fraction
	muonAccEff2_ = MuonAccEff3_->GetBinContent(muonAccXaxis3,muonAccYaxis3);
	if(debug_)	std::cout<<"muonAccEff2_"<<muonAccEff2_<<std::endl;
	double muonAccEff2Error = MuonAccEff3_->GetBinError(muonAccXaxis3,muonAccYaxis3);
	if (statErrorEffmaps_) muonBinByBinAccEffError_= MuonAccEff3_->GetBinError(muonAccXaxis3,muonAccYaxis3);
	muonAccWeight2_ = eventWeight_ * 1/muonIsoEff2_ * 1/muonRecoEff2_ *(1-muonAccEff2_)/muonAccEff2_;
	if(debug_)	std::cout<<"muonAccWeight2_"<<muonAccWeight2_<<std::endl;
	// total muon weight
	totalMuons_ = eventWeight_ / (muonAccEff2_ * muonRecoEff2_ * muonIsoEff2_);
	if(debug_)	std::cout<<"totalMuons_"<<totalMuons_<<std::endl;
	muonTotalWeight2_ = muonIsoWeight2_ + muonRecoWeight2_ + muonAccWeight2_;


	// electrons
	int elecAccXaxis2 = ElecAccEff2_->GetXaxis()->FindBin(mht_);
	if (elecAccXaxis2 > ElecAccEff2_->GetNbinsX()) elecAccXaxis2-=1;
	int elecAccXaxis3= ElecAccEff3_->GetXaxis()->FindBin(mht_);
	if (elecAccXaxis3 > ElecAccEff3_->GetNbinsX()) elecAccXaxis3-=1;
	int elecAccYaxis3= ElecAccEff3_->GetYaxis()->FindBin(nJets_+0.1);
	if (nJets_<3)elecAccYaxis3= ElecAccEff3_->GetYaxis()->FindBin(3);
//	if (elecAccYaxis3 > ElecAccEff3_->GetNbinsY()) elecAccYaxis3-=1;
	
	int elecIsoXaxis2= ElecIsoEff2_->GetXaxis()->FindBin(deltaRMuJet_);
	// check if the deltaRmuJet is greater thatn the maximum in the histogramm
	if(debug_)	std::cout<<"b"<<std::endl;
	if (elecIsoXaxis2 > ElecIsoEff2_->GetNbinsX()) elecIsoXaxis2-=1;
//		//if(debug_)	std::cout<<"muonIsoXaxis has been found"<<std::endl;
	int elecIsoYaxis2= ElecIsoEff2_->GetYaxis()->FindBin(MuPt_);
	// check if the deltaPTclosestJetMu is greater than the maximum stored in the histogramm
	if (elecIsoYaxis2 > ElecIsoEff2_->GetNbinsY()) elecIsoYaxis2-=1;
	int elecRecoXaxis2 = ElecRecoEff2_->GetXaxis()->FindBin(deltaRMuJet_);
	if (elecRecoXaxis2 > ElecRecoEff2_->GetNbinsX() ) elecRecoXaxis2-=1;
//		//if(debug_)	std::cout<<"2";
	int elecRecoYaxis2 = ElecRecoEff2_->GetYaxis()->FindBin(MuPt_);
	if (elecRecoYaxis2 > ElecRecoEff2_->GetNbinsY() ) elecRecoYaxis2-=1;
//		//if(debug_)	std::cout<<"3";

	elecAccEff2_ = ElecAccEff3_->GetBinContent(elecAccXaxis3,elecAccYaxis3);
	if(debug_)	std::cout<<"elecAccEff2_"<<elecAccEff2_<<std::endl;
	double elecAccEff2Error = ElecAccEff3_->GetBinError(elecAccXaxis3,elecAccYaxis3);
	if (elecAccEff2_ >1 || elecAccEff2_ <0.001) error_+=10000;
	elecAccWeight2_ = totalMuons_ * (1 - elecAccEff2_);
	if (statErrorEffmaps_) elecBinByBinAccEffError_= ElecAccEff3_->GetBinError(elecAccXaxis3,elecAccYaxis3);
	if(debug_)	std::cout<<"elecAccWeight2_"<<elecAccWeight2_<<std::endl;
	elecRecoEff2_ = ElecRecoEff2_->GetBinContent(elecRecoXaxis2,elecRecoYaxis2 );
	if(debug_)	std::cout<<"elecRecoEff2_"<<elecRecoEff2_<<std::endl;
	double elecRecoEff2Error = ElecRecoEff2_->GetBinError(elecRecoXaxis2,elecRecoYaxis2 );
	if (elecRecoEff2_ <0.001 || elecRecoEff2_ > 1) error_+=100000;
	elecRecoWeight2_ = totalMuons_ * (elecAccEff2_) * (1 - elecRecoEff2_);
	if(debug_)	std::cout<<"elecRecoWeight2_"<<elecRecoWeight2_<<std::endl;
	if (statErrorEffmaps_) elecBinByBinRecoEffError_= ElecRecoEff2_->GetBinError(elecRecoXaxis2,elecRecoYaxis2);
	
	elecIsoEff2_ = ElecIsoEff2_->GetBinContent(elecIsoXaxis2,elecIsoYaxis2 );
	if(debug_)	std::cout<<"elecIsoEff2_"<<elecIsoEff2_<<std::endl;
	if (elecIsoEff2_ <0.001 || elecIsoEff2_ > 1) error_+=1000000;
	elecIsoWeight2_ = totalMuons_ * elecAccEff2_ * elecRecoEff2_ * (1 - elecIsoEff2_);
//	elecIsoWeight2_ =elecBinByBinIsoWeight_;
	if(debug_)	std::cout<<"elecIsoWeight2_"<<elecIsoWeight2_<<std::endl;
	elecTotalWeight2_ = elecAccWeight2_ + elecRecoWeight2_ + elecIsoWeight2_;
	if(debug_)	std::cout<<"elecTotalWeight2_"<<elecTotalWeight2_<<std::endl;
	resultWeight2_ = muonTotalWeight2_ + elecTotalWeight2_;
	if(debug_)	std::cout<<"resultWeight2_"<<resultWeight2_<<std::endl;

	if(MTWCut_)
	{
		int MTWbin = MTWNJet_->GetXaxis()->FindBin(nJets_);
		if ( MTWbin > MTWNJet_->GetNbinsX() ) MTWbin -=1;
		resultWeight2MTW_ = resultWeight2_ / MTWNJet_->GetBinContent(MTWbin );
	if(debug_)	std::cout<<"resultWeight2MTW_"<<resultWeight2MTW_<<std::endl;
	}

	if(debug_)	std::cout<<"-----------------------------------------------------------------------------------endWeigh2---------------------"<<std::endl;





////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// binbybin seperately
	int muonBinByBinAccXaxis= MuonAccBinByBinEff_->GetXaxis()->FindBin(ht_);
	if (muonBinByBinAccXaxis > MuonAccBinByBinEff_->GetNbinsX()) muonBinByBinAccXaxis-=1;
	int muonBinByBinAccYaxis= MuonAccBinByBinEff_->GetYaxis()->FindBin(mht_);
	if (muonBinByBinAccYaxis > MuonAccBinByBinEff_->GetNbinsY()) muonBinByBinAccYaxis-=1;
	int muonBinByBinAccZaxis= MuonAccBinByBinEff_->GetZaxis()->FindBin(nJets_+0.1);
	if (muonBinByBinAccZaxis > MuonAccBinByBinEff_->GetNbinsZ()) muonBinByBinAccZaxis-=1;

//	int muonBinByBinIsoXaxis= MuonIsoBinByBinEff_->GetXaxis()->FindBin(ht_);
//	if (muonBinByBinIsoXaxis > MuonIsoBinByBinEff_->GetNbinsX()) muonBinByBinIsoXaxis-=1;
//	int muonBinByBinIsoYaxis= MuonIsoBinByBinEff_->GetYaxis()->FindBin(mht_);
//	if (muonBinByBinIsoYaxis > MuonIsoBinByBinEff_->GetNbinsY()) muonBinByBinIsoYaxis-=1;
//	int muonBinByBinIsoZaxis= MuonIsoBinByBinEff_->GetZaxis()->FindBin(nJets_+0.1);
//	if (muonBinByBinIsoZaxis > MuonIsoBinByBinEff_->GetNbinsZ()) muonBinByBinIsoZaxis-=1;

	int muonBinByBinIsoXaxis=0;
	int muonBinByBinIsoYaxis=0;
	int muonBinByBinRecoXaxis=0;
	int muonBinByBinRecoYaxis=0;
	double muonBinByBinRecoEffError = 0; 


	if (nJets_ > 2.5 && 5.5 > nJets_)
	{
		muonBinByBinIsoXaxis = MuonIsoBinByBinEff35_->GetXaxis()->FindBin(ht_);
		muonBinByBinIsoYaxis = MuonIsoBinByBinEff35_->GetYaxis()->FindBin(mht_);
		muonBinByBinIsoEff_ = MuonIsoBinByBinEff35_->GetBinContent(muonBinByBinIsoXaxis,muonBinByBinIsoYaxis);
		if (statErrorEffmaps_) muonBinByBinIsoEffError_= MuonIsoBinByBinEff35_->GetBinError(muonBinByBinIsoXaxis,muonBinByBinIsoYaxis);
		muonBinByBinRecoXaxis = MuonRecoBinByBinEff35_->GetXaxis()->FindBin(ht_);
		muonBinByBinRecoYaxis = MuonRecoBinByBinEff35_->GetYaxis()->FindBin(mht_);
		muonBinByBinRecoEff_ = MuonRecoBinByBinEff35_->GetBinContent(muonBinByBinRecoXaxis,muonBinByBinRecoYaxis);
		if (statErrorEffmaps_) muonBinByBinRecoEffError_= MuonRecoBinByBinEff35_->GetBinError(muonBinByBinRecoXaxis,muonBinByBinRecoYaxis);
	}
	if (nJets_ > 5.5 && 7.5 > nJets_)
	{
		muonBinByBinIsoXaxis = MuonIsoBinByBinEff67_->GetXaxis()->FindBin(ht_);
		muonBinByBinIsoYaxis = MuonIsoBinByBinEff67_->GetYaxis()->FindBin(mht_);
		muonBinByBinIsoEff_ = MuonIsoBinByBinEff67_->GetBinContent(muonBinByBinIsoXaxis,muonBinByBinIsoYaxis);
		if (statErrorEffmaps_) muonBinByBinIsoEffError_= MuonIsoBinByBinEff67_->GetBinError(muonBinByBinIsoXaxis,muonBinByBinIsoYaxis);
		muonBinByBinRecoXaxis = MuonRecoBinByBinEff67_->GetXaxis()->FindBin(ht_);
		muonBinByBinRecoYaxis = MuonRecoBinByBinEff67_->GetYaxis()->FindBin(mht_);
		muonBinByBinRecoEff_ = MuonRecoBinByBinEff67_->GetBinContent(muonBinByBinRecoXaxis,muonBinByBinRecoYaxis);
		if (statErrorEffmaps_) muonBinByBinRecoEffError_= MuonRecoBinByBinEff67_->GetBinError(muonBinByBinRecoXaxis,muonBinByBinRecoYaxis);
	}
	if (nJets_ > 7.5)
	{
		muonBinByBinIsoXaxis = MuonIsoBinByBinEff8Inf_->GetXaxis()->FindBin(ht_);
		muonBinByBinIsoYaxis = MuonIsoBinByBinEff8Inf_->GetYaxis()->FindBin(mht_);
		muonBinByBinIsoEff_ = MuonIsoBinByBinEff8Inf_->GetBinContent(muonBinByBinIsoXaxis,muonBinByBinIsoYaxis);
		if (statErrorEffmaps_) muonBinByBinIsoEffError_= MuonIsoBinByBinEff67_->GetBinError(muonBinByBinIsoXaxis,muonBinByBinIsoYaxis);
		muonBinByBinRecoXaxis = MuonRecoBinByBinEff8Inf_->GetXaxis()->FindBin(ht_);
		muonBinByBinRecoYaxis = MuonRecoBinByBinEff8Inf_->GetYaxis()->FindBin(mht_);
		muonBinByBinRecoEff_ = MuonRecoBinByBinEff8Inf_->GetBinContent(muonBinByBinRecoXaxis,muonBinByBinRecoYaxis);
		if (statErrorEffmaps_) muonBinByBinRecoEffError_= MuonRecoBinByBinEff67_->GetBinError(muonBinByBinRecoXaxis,muonBinByBinRecoYaxis);
	}
if(debug_)	std::cout<<"bb1"<<std::endl;

/*
	muonBinByBinRecoXaxis= MuonRecoBinByBinEff_->GetXaxis()->FindBin(ht_);
	if (muonBinByBinRecoXaxis > MuonRecoBinByBinEff_->GetNbinsX()) muonBinByBinRecoXaxis-=1;
	muonBinByBinRecoYaxis= MuonRecoBinByBinEff_->GetYaxis()->FindBin(mht_);
	if (muonBinByBinRecoYaxis > MuonRecoBinByBinEff_->GetNbinsY()) muonBinByBinRecoYaxis-=1;
	int muonBinByBinRecoZaxis= MuonRecoBinByBinEff_->GetZaxis()->FindBin(nJets_+0.1);
	if (muonBinByBinRecoZaxis > MuonRecoBinByBinEff_->GetNbinsZ()) muonBinByBinRecoZaxis-=1;
*/
	// calc eff and weights
//	muonBinByBinIsoEff_ = MuonIsoBinByBinEff_->GetBinContent(muonBinByBinIsoXaxis,muonBinByBinIsoYaxis,muonBinByBinIsoZaxis );
	if (muonBinByBinIsoEff_ <0.01 || muonBinByBinIsoEff_ > 1) error_+=102;
	if (muonBinByBinIsoEff_<0.01) muonBinByBinIsoEff_=0.01;
	if (muonBinByBinIsoEff_>1 ) muonBinByBinIsoEff_=1;
	muonBinByBinIsoWeight_ = eventWeight_ * (1 - muonBinByBinIsoEff_)/muonBinByBinIsoEff_;	
	//if(debug_)	std::cout<<"muonBinByBinIsoWeight_"<<muonBinByBinIsoWeight_<<std::endl;	
	MuIsoStatUp_ = eventWeight_ * (1 - muonBinByBinIsoEff_ - muonBinByBinIsoEffError_)/ (muonBinByBinIsoEff_ + muonBinByBinIsoEffError_) - muonBinByBinIsoWeight_;	
	//if(debug_)	std::cout<<"MuIsoStatUp_"<<MuIsoStatUp_<<std::endl;
	MuIsoStatDown_ = eventWeight_ * (1 - muonBinByBinIsoEff_ + muonBinByBinIsoEffError_)/ (muonBinByBinIsoEff_ - muonBinByBinIsoEffError_) - muonBinByBinIsoWeight_;	
	//if(debug_)	std::cout<<"MuIsoStatDown_"<<MuIsoStatDown_<<std::endl;
	//if(debug_)	std::cout<<"LostLeptonBkg::muonBinByBinIsoWeight_:"<<muonBinByBinIsoWeight_<<std::endl;
//	muonBinByBinRecoEff_ = MuonRecoBinByBinEff_->GetBinContent(muonBinByBinRecoXaxis,muonBinByBinRecoYaxis,muonBinByBinRecoZaxis );
//	double muonBinByBinRecoEffError = MuonRecoBinByBinEff_->GetBinError(muonBinByBinRecoXaxis,muonBinByBinRecoYaxis,muonBinByBinRecoZaxis );
//	if (statErrorEffmaps_) muonBinByBinRecoEffError_= MuonRecoBinByBinEff_->GetBinError(muonBinByBinRecoXaxis,muonBinByBinRecoYaxis,muonBinByBinRecoZaxis );
	//used these in AN up to now 14Mar2013
//	muonBinByBinRecoEff_ = muonRecoEff2_;
//	muonBinByBinRecoEffError = muonRecoEff2Error;
	if (muonBinByBinRecoEff_ <0.01 || muonBinByBinRecoEff_ > 1) error_+=103;
	if (muonBinByBinRecoEff_<0.01) muonBinByBinRecoEff_=0.01;
	if (muonBinByBinRecoEff_>1 ) muonBinByBinRecoEff_=1;
	muonBinByBinRecoWeight_ = eventWeight_ * 1 / muonBinByBinIsoEff_ * (1-muonBinByBinRecoEff_)/muonBinByBinRecoEff_;
	if(debug_)	std::cout<<"muonBinByBinRecoEffError"<<muonBinByBinRecoEffError<<std::endl;
	if(debug_)	std::cout<<"muonBinByBinRecoEff_"<<muonBinByBinRecoEff_<<std::endl;
	MuRecoStatUp_ = eventWeight_ * 1 / muonBinByBinIsoEff_ * (1-muonBinByBinRecoEff_-muonBinByBinRecoEffError)/(muonBinByBinRecoEff_ + muonBinByBinRecoEffError_)- muonBinByBinRecoWeight_;
	MuRecoStatDown_ = eventWeight_ * 1 / muonBinByBinIsoEff_ * (1-muonBinByBinRecoEff_ + muonBinByBinRecoEffError)/(muonBinByBinRecoEff_ - muonBinByBinRecoEffError_)- muonBinByBinRecoWeight_;
	//if(debug_)	std::cout<<"LostLeptonBkg::muonBinByBinRecoWeight_:"<<muonBinByBinRecoWeight_<<std::endl;
	if(debug_)	std::cout<<"bbb"<<std::endl;
	muonBinByBinAccEff_ = MuonAccBinByBinEff_->GetBinContent(muonBinByBinAccXaxis,muonBinByBinAccYaxis,muonBinByBinAccZaxis );
	double muonBinByBinAccEffError = MuonAccBinByBinEff_->GetBinError(muonBinByBinAccXaxis,muonBinByBinAccYaxis,muonBinByBinAccZaxis );
//	if (statErrorEffmaps_) muonBinByBinAccEffError_= MuonAccBinByBinEff_->GetBinError(muonBinByBinAccXaxis,muonBinByBinAccYaxis,muonBinByBinAccZaxis );
	muonBinByBinAccEff_ = muonAccEff2_;
	muonBinByBinAccEffError = muonAccEff2Error;
	if (muonBinByBinAccEff_ <0.01 || muonBinByBinAccEff_ > 1) error_+=103;
	if (muonBinByBinAccEff_<0.01) muonBinByBinAccEff_=0.01;
	if (muonBinByBinAccEff_>1 ) muonBinByBinAccEff_=1;
	muonBinByBinAccWeight_ = eventWeight_ * 1/muonBinByBinIsoEff_ * 1/muonBinByBinRecoEff_ *(1-muonBinByBinAccEff_)/muonBinByBinAccEff_;
	MuAccStatUp_ = eventWeight_ * 1/muonBinByBinIsoEff_ * 1/muonBinByBinRecoEff_ *(1-muonBinByBinAccEff_ - muonBinByBinAccEffError)/(muonBinByBinAccEff_ + muonBinByBinAccEffError);
	MuAccStatDown_ = eventWeight_ * 1/muonBinByBinIsoEff_ * 1/muonBinByBinRecoEff_ *(1-muonBinByBinAccEff_ + muonBinByBinAccEffError)/(muonBinByBinAccEff_ - muonBinByBinAccEffError);
	//if(debug_)	std::cout<<"LostLeptonBkg::muonBinByBinAccWeight_:"<<muonBinByBinAccWeight_<<std::endl;
	// total binbybin muon weight
	muonBinByBinTotalWeight_ = muonBinByBinIsoWeight_ + muonBinByBinRecoWeight_ + muonBinByBinAccWeight_;
	//if(debug_)	std::cout<<"LostLeptonBkg::muonBinByBinTotalWeight_:"<<muonBinByBinTotalWeight_<<std::endl;
	totalBinByBinMuons_ = eventWeight_ / (muonBinByBinAccEff_ * muonBinByBinRecoEff_ * muonBinByBinIsoEff_);

	// binbybin elec eff

	int elecBinByBinAccXaxis= ElecAccBinByBinEff_->GetXaxis()->FindBin(ht_);
	if (elecBinByBinAccXaxis > ElecAccBinByBinEff_->GetNbinsX()) elecBinByBinAccXaxis-=1;
	int elecBinByBinAccYaxis= ElecAccBinByBinEff_->GetYaxis()->FindBin(mht_);
	if (elecBinByBinAccYaxis > ElecAccBinByBinEff_->GetNbinsY()) elecBinByBinAccYaxis-=1;
	int elecBinByBinAccZaxis= ElecAccBinByBinEff_->GetZaxis()->FindBin(nJets_+0.1);
	if (elecBinByBinAccZaxis > ElecAccBinByBinEff_->GetNbinsZ()) elecBinByBinAccZaxis-=1;

//	int elecBinByBinIsoXaxis= ElecIsoBinByBinEff_->GetXaxis()->FindBin(ht_);
//	if (elecBinByBinIsoXaxis > ElecIsoBinByBinEff_->GetNbinsX()) elecBinByBinIsoXaxis-=1;
//	int elecBinByBinIsoYaxis= ElecIsoBinByBinEff_->GetYaxis()->FindBin(mht_);
//	if (elecBinByBinIsoYaxis > ElecIsoBinByBinEff_->GetNbinsY()) elecBinByBinIsoYaxis-=1;
//	int elecBinByBinIsoZaxis= ElecIsoBinByBinEff_->GetZaxis()->FindBin(nJets_+0.1);
//	if (elecBinByBinIsoZaxis > ElecIsoBinByBinEff_->GetNbinsZ()) elecBinByBinIsoZaxis-=1;

	int elecBinByBinIsoXaxis=0;
	int elecBinByBinIsoYaxis=0;

	int elecBinByBinRecoXaxis=0;
	int elecBinByBinRecoYaxis=0;
	if (nJets_ > 2.5 && 5.5 > nJets_)
	{
		elecBinByBinIsoXaxis = ElecIsoBinByBinEff35_->GetXaxis()->FindBin(ht_);
		elecBinByBinIsoYaxis = ElecIsoBinByBinEff35_->GetYaxis()->FindBin(mht_);
		elecBinByBinIsoEff_ = ElecIsoBinByBinEff35_->GetBinContent(elecBinByBinIsoXaxis,elecBinByBinIsoYaxis);
		if (statErrorEffmaps_) elecBinByBinIsoEffError_= ElecIsoBinByBinEff35_->GetBinError(elecBinByBinIsoXaxis,elecBinByBinIsoYaxis );
		elecBinByBinRecoXaxis = ElecRecoBinByBinEff35_->GetXaxis()->FindBin(ht_);
		elecBinByBinRecoYaxis = ElecRecoBinByBinEff35_->GetYaxis()->FindBin(mht_);
		elecBinByBinRecoEff_ = ElecRecoBinByBinEff35_->GetBinContent(elecBinByBinRecoXaxis,elecBinByBinRecoYaxis);
		if (statErrorEffmaps_) elecBinByBinRecoEffError_= ElecRecoBinByBinEff35_->GetBinError(elecBinByBinRecoXaxis,elecBinByBinRecoYaxis );
	}
	if (nJets_ > 5.5 && 7.5 > nJets_)
	{
		elecBinByBinIsoXaxis = ElecIsoBinByBinEff67_->GetXaxis()->FindBin(ht_);
		elecBinByBinIsoYaxis = ElecIsoBinByBinEff67_->GetYaxis()->FindBin(mht_);
		elecBinByBinIsoEff_ = ElecIsoBinByBinEff67_->GetBinContent(elecBinByBinIsoXaxis,elecBinByBinIsoYaxis);
		if (statErrorEffmaps_) elecBinByBinIsoEffError_= ElecIsoBinByBinEff67_->GetBinError(elecBinByBinIsoXaxis,elecBinByBinIsoYaxis );
		elecBinByBinRecoXaxis = ElecRecoBinByBinEff67_->GetXaxis()->FindBin(ht_);
		elecBinByBinRecoYaxis = ElecRecoBinByBinEff67_->GetYaxis()->FindBin(mht_);
		elecBinByBinRecoEff_ = ElecRecoBinByBinEff67_->GetBinContent(elecBinByBinRecoXaxis,elecBinByBinRecoYaxis);
		if (statErrorEffmaps_) elecBinByBinRecoEffError_= ElecRecoBinByBinEff67_->GetBinError(elecBinByBinRecoXaxis,elecBinByBinRecoYaxis );
	}
	if (nJets_ > 7.5)
	{
		elecBinByBinIsoXaxis = ElecIsoBinByBinEff8Inf_->GetXaxis()->FindBin(ht_);
		elecBinByBinIsoYaxis = ElecIsoBinByBinEff8Inf_->GetYaxis()->FindBin(mht_);
		elecBinByBinIsoEff_ = ElecIsoBinByBinEff8Inf_->GetBinContent(elecBinByBinIsoXaxis,elecBinByBinIsoYaxis);
		if (statErrorEffmaps_) elecBinByBinIsoEffError_= ElecIsoBinByBinEff8Inf_->GetBinError(elecBinByBinIsoXaxis,elecBinByBinIsoYaxis );
		elecBinByBinRecoXaxis = ElecRecoBinByBinEff8Inf_->GetXaxis()->FindBin(ht_);
		elecBinByBinRecoYaxis = ElecRecoBinByBinEff8Inf_->GetYaxis()->FindBin(mht_);
		elecBinByBinRecoEff_ = ElecRecoBinByBinEff8Inf_->GetBinContent(elecBinByBinRecoXaxis,elecBinByBinRecoYaxis);
		if (statErrorEffmaps_) elecBinByBinRecoEffError_= ElecRecoBinByBinEff8Inf_->GetBinError(elecBinByBinRecoXaxis,elecBinByBinRecoYaxis );
	}
	if(debug_)	std::cout<<"bc"<<std::endl;
/*
	elecBinByBinRecoXaxis= ElecRecoBinByBinEff_->GetXaxis()->FindBin(ht_);
	if (elecBinByBinRecoXaxis > ElecRecoBinByBinEff_->GetNbinsX()) elecBinByBinRecoXaxis-=1;
	elecBinByBinRecoYaxis= ElecRecoBinByBinEff_->GetYaxis()->FindBin(mht_);
	if (elecBinByBinRecoYaxis > ElecRecoBinByBinEff_->GetNbinsY()) elecBinByBinRecoYaxis-=1;
	int elecBinByBinRecoZaxis= ElecRecoBinByBinEff_->GetZaxis()->FindBin(nJets_+0.1);
	if (elecBinByBinRecoZaxis > ElecRecoBinByBinEff_->GetNbinsZ()) elecBinByBinRecoZaxis-=1;
*/
	// calc eff and weights
	elecBinByBinAccEff_ = ElecAccBinByBinEff_->GetBinContent(elecBinByBinAccXaxis,elecBinByBinAccYaxis,elecBinByBinAccZaxis );
	double elecBinByBinAccEffError = ElecAccBinByBinEff_->GetBinError(elecBinByBinAccXaxis,elecBinByBinAccYaxis,elecBinByBinAccZaxis );
//	if (statErrorEffmaps_) elecBinByBinAccEffError_= ElecAccBinByBinEff_->GetBinError(elecBinByBinAccXaxis,elecBinByBinAccYaxis,elecBinByBinAccZaxis );

	// use these IN AN up to now 14Mar2013
	elecBinByBinAccEff_ = elecAccEff2_;
//	elecBinByBinAccEffError = elecAccEff2Error;
	if (elecBinByBinAccEff_ <0.01 || elecBinByBinAccEff_ > 1) error_+=103;
	if (elecBinByBinAccEff_<0.01) elecBinByBinAccEff_=0.01;
	if (elecBinByBinAccEff_>1 ) elecBinByBinAccEff_=1;
	elecBinByBinAccWeight_ = totalBinByBinMuons_ * (1 - elecBinByBinAccEff_);
	ElecAccStatUp_ = totalBinByBinMuons_ * (1 - elecBinByBinAccEff_ - elecBinByBinAccEffError) - elecBinByBinAccWeight_;
	ElecAccStatDown_ =-1 * ElecAccStatUp_;
	// total binbybin elec weight


//	elecBinByBinRecoEff_ = ElecRecoBinByBinEff_->GetBinContent(elecBinByBinRecoXaxis,elecBinByBinRecoYaxis,elecBinByBinRecoZaxis );
//	if (statErrorEffmaps_) elecBinByBinRecoEffError_= ElecRecoBinByBinEff_->GetBinError(elecBinByBinRecoXaxis,elecBinByBinRecoYaxis,elecBinByBinRecoZaxis );
//	elecBinByBinRecoEff_ = elecRecoEff2_;
//	double elecBinByBinRecoEffError = elecRecoEff2Error;
	if (elecBinByBinRecoEff_ <0.01 || elecBinByBinRecoEff_ > 1) error_+=103;
	if (elecBinByBinRecoEff_<0.01) elecBinByBinRecoEff_=0.01;
	if (elecBinByBinRecoEff_>1 ) elecBinByBinRecoEff_=1;
	elecBinByBinRecoWeight_ = totalBinByBinMuons_ * (elecBinByBinAccEff_) * (1 - elecBinByBinRecoEff_);
	ElecRecoStatUp_ =totalBinByBinMuons_ * (elecBinByBinAccEff_) * (1 - elecBinByBinRecoEff_ - elecBinByBinRecoEffError_) -elecBinByBinRecoWeight_;
	ElecRecoStatDown_ =totalBinByBinMuons_ * (elecBinByBinAccEff_) * (1 - elecBinByBinRecoEff_ - elecBinByBinRecoEffError_) -elecBinByBinRecoWeight_;

//	elecBinByBinIsoEff_ = ElecIsoBinByBinEff_->GetBinContent(elecBinByBinIsoXaxis,elecBinByBinIsoYaxis,elecBinByBinIsoZaxis );
	if (elecBinByBinIsoEff_ <0.01 || elecBinByBinIsoEff_ > 1) error_+=102;
	if (elecBinByBinIsoEff_<0.01) elecBinByBinIsoEff_=0.01;
	if (elecBinByBinIsoEff_>1 ) elecBinByBinIsoEff_=1;
	elecBinByBinIsoWeight_ = totalBinByBinMuons_ * (elecBinByBinAccEff_) * (elecBinByBinRecoEff_) * (1 - elecBinByBinIsoEff_) ;
	ElecIsoStatUp_ = totalBinByBinMuons_ * (elecBinByBinAccEff_) * (elecBinByBinRecoEff_) * (1 - elecBinByBinIsoEff_ - elecBinByBinIsoEffError_) -elecBinByBinIsoWeight_;
	ElecIsoStatDown_ = totalBinByBinMuons_ * (elecBinByBinAccEff_) * (elecBinByBinRecoEff_) * (1 - elecBinByBinIsoEff_ - elecBinByBinIsoEffError_) -elecBinByBinIsoWeight_;
	if(debug_)	std::cout<<"bd"<<std::endl;
	elecBinByBinTotalWeight_ = elecBinByBinIsoWeight_ + elecBinByBinRecoWeight_ + elecBinByBinAccWeight_;
	resultBBBW_ = elecBinByBinTotalWeight_ + muonBinByBinTotalWeight_;
	// mtw cut correction
	if(MTWCut_)
	{
		int MTWbin = MTWNJet_->GetXaxis()->FindBin(nJets_);
		if ( MTWbin > MTWNJet_->GetNbinsX() ) MTWbin -=1;
		resultBBBWMTW_ = resultBBBW_ / MTWNJet_->GetBinContent(MTWbin );
	}
	else resultBBBWMTW_ = resultBBBW_;
	// dilep correction and corresponding uncertainty
	if (abs(DiLepCorrection_))
	{
		resultBBBWMTWDiLep_= resultBBBWMTW_ * (1 + DiLepCorrection_/100.);
		//if(debug_)	std::cout<<"LostLeptonBkg::resultBBBWMTWDiLep_"<<resultBBBWMTWDiLep_<<std::endl;
		resultBBBWMTWDiLepUp_ = resultBBBWMTWDiLep_ * ( 1 + (std::abs(DiLepCorrection_) * DiLepCorrectionUp_)/10000.);
		resultBBBWMTWDiLepDown_ = resultBBBWMTWDiLep_ * (1 - ((std::abs(DiLepCorrection_)*DiLepCorrectionDown_)/10000.));
	}
	else resultBBBWMTWDiLep_=resultBBBWMTW_;
	// mtw uncertainty
	if (MTWCut_)
	{
		int MTWbin = MTWNJet_->GetXaxis()->FindBin(nJets_);
		if ( MTWbin > MTWNJet_->GetNbinsX() ) MTWbin -=1;
		double MTWStatErrorUp =  resultBBBW_ * (1-MTWNJet_->GetBinContent(MTWbin ) )- resultBBBW_ * (1-MTWNJet_->GetBinContent(MTWbin ) - MTWNJet_->GetBinError(MTWbin) );
		double MTWStatErrorDown =   resultBBBW_ * (1-MTWNJet_->GetBinContent(MTWbin ) + MTWNJet_->GetBinError(MTWbin) ) - resultBBBW_ * (1-MTWNJet_->GetBinContent(MTWbin ) );
		//if(debug_)	std::cout<<"MTWStatErrorUp"<<MTWStatErrorUp<<std::endl;
		//if(debug_)	std::cout<<"MTWStatErrorDown"<<MTWStatErrorDown<<std::endl;
		double MTWSystematicUp = resultBBBWMTW_ * (1-MTWNJet_->GetBinContent(MTWbin ) ) * MTWUncertaintyUp_*0.01;
		//if(debug_)	std::cout<<"MTWSystematicUp"<<MTWSystematicUp<<std::endl;
		double MTWSystematicDown = resultBBBWMTW_ * (1-MTWNJet_->GetBinContent(MTWbin ) ) * MTWUncertaintyDown_*0.01;
		
		resultBBBWMTWUp_ = resultBBBWMTWDiLep_ + sqrt(MTWSystematicUp * MTWSystematicUp+  MTWStatErrorUp * MTWStatErrorUp);
		resultBBBWMTWDown_ = resultBBBWMTWDiLep_ - sqrt(MTWSystematicDown * MTWSystematicDown+  MTWStatErrorDown * MTWStatErrorDown);
		//if(debug_)	std::cout<<"MTWNJet_->GetBinContent(MTWbin )"<<MTWNJet_->GetBinContent(MTWbin )<<std::endl;
		//if(debug_)	std::cout<<"MTWUncertaintyUp_"<<MTWUncertaintyUp_<<std::endl;
		//if(debug_)	std::cout<<"MTWCUT resultBBBWMTW_"<<resultBBBWMTW_<<std::endl;
		//if(debug_)	std::cout<<"MTWCUT resultBBBWMTWUp_"<<resultBBBWMTWUp_<<std::endl;
		//if(debug_)	std::cout<<"MTWCUT resultBBBWMTWDown_"<<resultBBBWMTWDown_<<std::endl;
	}

	//if(debug_)	std::cout<<"lostleptonweights calculated"<<std::endl;

  	// calculated the uncertainties from tag and probe mc data comparison
	// turned off for now
	if(TAPUncertainties_)
  	{
		if(debug_)	std::cout<<"Calculating TAP uncertainties"<<std::endl;
		if (TAPUncertaintiesHTNJET_)
		{
		// muon tag and probe uncertainty
		int muonIsoXaxisMC= MuIsoMCTAP_->GetXaxis()->FindBin(ht_);
		if (muonIsoXaxisMC > MuIsoMCTAP_->GetNbinsX()) muonIsoXaxisMC-=1;
		int muonIsoYaxisMC= MuIsoMCTAP_->GetYaxis()->FindBin(nJets_);
		if (muonIsoYaxisMC > MuIsoMCTAP_->GetNbinsY()) muonIsoYaxisMC-=1;
		


		double muonIsoEffMC = MuIsoMCTAP_->GetBinContent(muonIsoXaxisMC,muonIsoYaxisMC );


		int muonIsoXaxisData= MuIsoDataTAP_->GetXaxis()->FindBin(ht_);
		if (muonIsoXaxisData > MuIsoDataTAP_->GetNbinsX()) muonIsoXaxisData-=1;
		int muonIsoYaxisData= MuIsoDataTAP_->GetYaxis()->FindBin(nJets_);
		if (muonIsoYaxisData > MuIsoDataTAP_->GetNbinsY()) muonIsoYaxisData-=1;
		double muonIsoEffData = MuIsoDataTAP_->GetBinContent(muonIsoXaxisData,muonIsoYaxisData );

		if(TAPUncertaintiesHTNJET_) 
		{
		int muonIsoXaxisMCHTNJet = MuIsoMCTAPHTNJET_->GetXaxis()->FindBin(ht_);
		if (muonIsoXaxisMCHTNJet > MuIsoMCTAPHTNJET_->GetNbinsX()+1) muonIsoXaxisMCHTNJet-=1;
		int muonIsoYaxisMCHTNJet = MuIsoMCTAPHTNJET_->GetYaxis()->FindBin(nJets_);
		if (muonIsoYaxisMCHTNJet > MuIsoMCTAPHTNJET_->GetNbinsY()+1) muonIsoYaxisMCHTNJet-=1;
		muonIsoEffMC = MuIsoMCTAPHTNJET_->GetBinContent(muonIsoXaxisMCHTNJet, muonIsoYaxisMCHTNJet);
		if (muonIsoEffMC>0.999) muonIsoEffMC=0.999;
		if(debug_)	std::cout<<"TAPUncertaintiesHTNJet::muonIsoEffMC="<<MuIsoMCTAPHTNJET_->GetBinContent(muonIsoXaxisMCHTNJet, muonIsoYaxisMCHTNJet)<<std::endl;

		int muonIsoXaxisDataHTNJet = MuIsoDataTAPHTNJET_->GetXaxis()->FindBin(ht_);
		if (muonIsoXaxisDataHTNJet > MuIsoDataTAPHTNJET_->GetNbinsX()+1) muonIsoXaxisDataHTNJet-=1;
		int muonIsoYaxisDataHTNJet = MuIsoDataTAPHTNJET_->GetYaxis()->FindBin(nJets_);
		if (muonIsoYaxisDataHTNJet > MuIsoDataTAPHTNJET_->GetNbinsY()+1) muonIsoYaxisDataHTNJet-=1;
		muonIsoEffData = MuIsoDataTAPHTNJET_->GetBinContent(muonIsoXaxisDataHTNJet, muonIsoYaxisDataHTNJet);
		if (muonIsoEffData>0.999) muonIsoEffData=0.999;
		if(debug_)	std::cout<<"TAPUncertaintiesHTNJet::muonIsoEffData="<<MuIsoDataTAPHTNJET_->GetBinContent(muonIsoXaxisDataHTNJet, muonIsoYaxisDataHTNJet)<<std::endl;
		}
		if (muonIsoEffMC <0.001) error_+=999;
		if (muonIsoEffMC >1) error_+=-999;
		if (muonIsoEffData <0.001) error_+=9999;
		if (muonIsoEffData >1) error_+=-9999;

		if (muonIsoEffMC <0.01) muonIsoEffMC=0.01;
		if (muonIsoEffMC >0.99) muonIsoEffMC=0.99;
		if (muonIsoEffData <0.01) muonIsoEffData=0.01;
		if (muonIsoEffData >0.99) muonIsoEffData=0.99;
		double muonTAPIsoWeightMC = eventWeight_ * (1 - muonIsoEffMC)/muonIsoEffMC;
		double muonTAPIsoWeightData = eventWeight_ * (1 - muonIsoEffData)/muonIsoEffData;
		muonIsoTAPRelUncertainty_ = (muonTAPIsoWeightMC-muonTAPIsoWeightData)/muonTAPIsoWeightMC;
		if (muonIsoTAPRelUncertainty_<-0.00) muonIsoTAPRelUncertainty_=muonIsoTAPRelUncertainty_ * (-1);
		double MuIsoFraction = muonBinByBinIsoWeight_/resultBBBWMTWDiLep_;
		muonTAPIsoWeightMC_= resultBBBWMTWDiLep_ - muonBinByBinIsoWeight_ + muonTAPIsoWeightMC;
		muonTAPIsoWeightData_= resultBBBWMTWDiLep_ - muonBinByBinIsoWeight_ + muonTAPIsoWeightData;
	
		muonIsoTAPUp_ = resultBBBWMTWDiLep_ + sqrt( (resultBBBWMTWDiLep_ *(muonIsoTAPRelUncertainty_ * MuIsoFraction)) * (resultBBBWMTWDiLep_ *(muonIsoTAPRelUncertainty_ * MuIsoFraction)) + MuIsoStatUp_ * MuIsoStatUp_);
		if(debug_)	std::cout<<"muonIsoTAPUp_::"<<muonIsoTAPUp_<<std::endl;
		if(debug_)	std::cout<<"MuIsoStatUp_"<<MuIsoStatUp_<<std::endl;
		muonIsoTAPDown_ = resultBBBWMTWDiLep_ - sqrt( (resultBBBWMTWDiLep_ *(muonIsoTAPRelUncertainty_ * MuIsoFraction)) *(resultBBBWMTWDiLep_ *(muonIsoTAPRelUncertainty_ * MuIsoFraction)) + MuIsoStatDown_ * MuIsoStatDown_);
		if (muonIsoTAPDown_<0.0001)muonIsoTAPDown_=0.0001;
		//if(debug_)	std::cout<<"muonIsoTAPDown_::"<<muonIsoTAPDown_<<std::endl;
		//if(debug_)	std::cout<<"MuIsoStatDown_"<<MuIsoStatDown_<<std::endl;

		if (muonIsoTAPUp_ >10) muonIsoTAPUp_=10;
		if (muonIsoTAPDown_<0.01) muonIsoTAPDown_=0.01;

		int muonRecoXaxisMC= MuRecoMCTAP_->GetXaxis()->FindBin(ht_);

		if (muonRecoXaxisMC > MuRecoMCTAP_->GetNbinsX()) muonRecoXaxisMC-=1;
		int muonRecoYaxisMC= MuRecoMCTAP_->GetYaxis()->FindBin(nJets_);
		if (muonRecoYaxisMC > MuRecoMCTAP_->GetNbinsY()) muonRecoYaxisMC-=1;
		double muonRecoEffMC = MuRecoMCTAP_->GetBinContent(muonRecoXaxisMC,muonRecoYaxisMC );
		if (muonRecoEffMC>0.999) muonRecoEffMC=0.999;
		if(debug_)	std::cout<<"muonRecoEffMCTAP"<<muonRecoEffMC<<std::endl;
		int muonRecoXaxisData= MuRecoDataTAP_->GetXaxis()->FindBin(ht_);
		if (muonRecoXaxisData > MuRecoDataTAP_->GetNbinsX()) muonRecoXaxisData-=1;
		int muonRecoYaxisData= MuRecoDataTAP_->GetYaxis()->FindBin(nJets_);
		if (muonRecoYaxisData > MuRecoDataTAP_->GetNbinsY()) muonRecoYaxisData-=1;
		double muonRecoEffData = MuRecoDataTAP_->GetBinContent(muonRecoXaxisData,muonRecoYaxisData );
		if (muonRecoEffData>0.999) muonRecoEffData=0.999;
		if(debug_)	std::cout<<"muonRecoEffDataTAP"<<muonRecoEffData<<std::endl;
		double muonRecoWeightMC = eventWeight_ * 1 / muonBinByBinIsoEff_ * (1-muonRecoEffMC)/muonRecoEffMC;
		if(debug_)	std::cout<<"muonRecoWeightMCTAP"<<muonRecoWeightMC<<std::endl;
		double muonRecoWeightData = eventWeight_ * 1 / muonBinByBinIsoEff_ * (1-muonRecoEffData)/muonRecoEffData;
		if(debug_)	std::cout<<"muonRecoWeightDataTAP"<<muonRecoWeightData<<std::endl;
		muonTAPRecoWeightMC_= resultBBBWMTWDiLep_ - muonBinByBinRecoWeight_ + muonRecoWeightMC;
		muonTAPRecoWeightData_= resultBBBWMTWDiLep_ - muonBinByBinRecoWeight_ + muonRecoWeightData;

		muonRecoTAPRelUncertainty_ = (muonRecoWeightMC-muonRecoWeightData)/muonRecoWeightMC;
		if(debug_)	std::cout<<"muonRecoTAPRelUncertainty_"<<muonRecoTAPRelUncertainty_<<std::endl;
		if (muonRecoTAPRelUncertainty_<0.00) muonRecoTAPRelUncertainty_=muonRecoTAPRelUncertainty_*(-1);
		if(debug_)	std::cout<<"muonRecoTAPRelUncertainty_"<<muonRecoTAPRelUncertainty_<<std::endl;
		double MuRecoFraction = muonBinByBinRecoWeight_/resultBBBWMTWDiLep_;
		if(debug_)	std::cout<<"MuRecoFraction"<<MuRecoFraction<<std::endl;
		if(debug_)	std::cout<<"resultBBBWMTWDiLep_::"<<resultBBBWMTWDiLep_<<std::endl;	
		if(debug_)	std::cout<<"MuRecoStatUp_::"<<MuRecoStatUp_<<std::endl;	
		if(debug_)	std::cout<<"MuRecoStatDown_::"<<MuRecoStatDown_<<std::endl;
		if(debug_)	std::cout<<"MuRecoTagUp_::"<<resultBBBWMTWDiLep_ * (muonRecoTAPRelUncertainty_ * MuRecoFraction) * resultBBBWMTWDiLep_ * (muonRecoTAPRelUncertainty_ * MuRecoFraction)<<std::endl;	
		if(debug_)	std::cout<<"MuRecoTagDown_::"<<resultBBBWMTWDiLep_ *(muonRecoTAPRelUncertainty_ * MuRecoFraction) * resultBBBWMTWDiLep_ *(muonRecoTAPRelUncertainty_ * MuRecoFraction)<<std::endl;		
		muonRecoTAPUp_ = resultBBBWMTWDiLep_ + sqrt( resultBBBWMTWDiLep_ * (muonRecoTAPRelUncertainty_ * MuRecoFraction) * resultBBBWMTWDiLep_ * (muonRecoTAPRelUncertainty_ * MuRecoFraction) + MuRecoStatUp_ * MuRecoStatUp_ );
		muonRecoTAPDown_ = resultBBBWMTWDiLep_ - sqrt( resultBBBWMTWDiLep_ *(muonRecoTAPRelUncertainty_ * MuRecoFraction) * resultBBBWMTWDiLep_ *(muonRecoTAPRelUncertainty_ * MuRecoFraction) + MuRecoStatDown_ * MuRecoStatDown_);
		if (muonRecoTAPDown_<0.0001)muonRecoTAPDown_=0.0001;
		if(debug_)	std::cout<<"muonRecoTAPUp_::"<<muonRecoTAPUp_<<std::endl;	
		if(debug_)	std::cout<<"muonRecoTAPDown_::"<<muonRecoTAPDown_<<std::endl;

		}


		if (!TAPUncertaintiesHTNJET_)
		{
		if(debug_)	std::cout<<"Calculating TAP uncertainties RelPT/DeltaR"<<std::endl;
		if(debug_)	std::cout<<"Muonstarted"<<std::endl;
		// muon tag and probe uncertainty
		if (!MuIsoMCTAPRel_) if(debug_)	std::cout<<"MuIsoMCTAPRel_ false"<<std::endl;
		int muonIsoXaxisMC= MuIsoMCTAPRel_->GetXaxis()->FindBin(deltaRMuJet_);
		if (MuIsoMCTAPRel_->GetXaxis()->GetXmax() < deltaRMuJet_)  muonIsoXaxisMC=MuIsoMCTAPRel_->GetXaxis()->FindBin(MuIsoMCTAPRel_->GetXaxis()->GetXmax()-0.1 );
		if(debug_)	std::cout<<"0.1";
		if (muonIsoXaxisMC > MuIsoMCTAPRel_->GetNbinsX()) muonIsoXaxisMC-=1;
		int muonIsoYaxisMC= MuIsoMCTAPRel_->GetYaxis()->FindBin(deltaPtClosestJetMu_);
		if (MuIsoMCTAPRel_->GetYaxis()->GetXmax() < deltaPtClosestJetMu_)  muonIsoYaxisMC=MuIsoMCTAPRel_->GetYaxis()->FindBin(MuIsoMCTAPRel_->GetYaxis()->GetXmax()-0.1 );
		if (muonIsoYaxisMC > MuIsoMCTAPRel_->GetNbinsY()) muonIsoYaxisMC-=1;
		


		double muonIsoEffMC = MuIsoMCTAPRel_->GetBinContent(muonIsoXaxisMC,muonIsoYaxisMC );
		if(debug_)	std::cout<<"1";

		int muonIsoXaxisData= MuIsoDataTAPRel_->GetXaxis()->FindBin(deltaRMuJet_);
		if (MuIsoDataTAPRel_->GetXaxis()->GetXmax() < deltaRMuJet_)  muonIsoXaxisData=MuIsoMCTAPRel_->GetXaxis()->FindBin(MuIsoDataTAPRel_->GetXaxis()->GetXmax()-0.1 );
		if (muonIsoXaxisData > MuIsoDataTAPRel_->GetNbinsX()) muonIsoXaxisData-=1;
		int muonIsoYaxisData= MuIsoDataTAPRel_->GetYaxis()->FindBin(deltaPtClosestJetMu_);
		if (MuIsoDataTAPRel_->GetYaxis()->GetXmax() < deltaPtClosestJetMu_)  muonIsoYaxisData=MuIsoDataTAPRel_->GetYaxis()->FindBin(MuIsoDataTAPRel_->GetYaxis()->GetXmax()-0.1 );
		if (muonIsoYaxisData > MuIsoDataTAPRel_->GetNbinsY()) muonIsoYaxisData-=1;
		double muonIsoEffData = MuIsoDataTAPRel_->GetBinContent(muonIsoXaxisData,muonIsoYaxisData );
		if(debug_)	std::cout<<"2";
		if (muonIsoEffMC <0.001) error_+=999;
		if (muonIsoEffMC >1) error_+=-999;
		if (muonIsoEffData <0.001) error_+=9999;
		if (muonIsoEffData >1) error_+=-9999;
		if(debug_)	std::cout<<"3";
		if (muonIsoEffMC <0.01) muonIsoEffMC=0.01;
		if (muonIsoEffMC >0.99) muonIsoEffMC=0.99;
		if (muonIsoEffData <0.01) muonIsoEffData=0.01;
		if (muonIsoEffData >0.99) muonIsoEffData=0.99;
		if(debug_)	std::cout<<"4";
		double muonTAPIsoWeightMC = eventWeight_ * (1 - muonIsoEffMC)/muonIsoEffMC;
		double muonTAPIsoWeightData = eventWeight_ * (1 - muonIsoEffData)/muonIsoEffData;
		muonIsoTAPRelUncertainty_ = (muonTAPIsoWeightMC-muonTAPIsoWeightData)/muonTAPIsoWeightMC;
		if (muonIsoTAPRelUncertainty_<-0.00) muonIsoTAPRelUncertainty_=muonIsoTAPRelUncertainty_ * (-1);
		double MuIsoFraction = muonBinByBinIsoWeight_/resultBBBWMTWDiLep_;
		muonTAPIsoWeightMC_= resultBBBWMTWDiLep_ - muonBinByBinIsoWeight_ + muonTAPIsoWeightMC;
		muonTAPIsoWeightData_= resultBBBWMTWDiLep_ - muonBinByBinIsoWeight_ + muonTAPIsoWeightData;
			if(debug_)	std::cout<<"5";
		muonIsoTAPUp_ = resultBBBWMTWDiLep_ + sqrt( (resultBBBWMTWDiLep_ *(muonIsoTAPRelUncertainty_ * MuIsoFraction)) * (resultBBBWMTWDiLep_ *(muonIsoTAPRelUncertainty_ * MuIsoFraction)) + MuIsoStatUp_ * MuIsoStatUp_);
		if(debug_)	std::cout<<"muonIsoTAPUp_::"<<muonIsoTAPUp_<<std::endl;
		if(debug_)	std::cout<<"MuIsoStatUp_"<<MuIsoStatUp_<<std::endl;
		muonIsoTAPDown_ = resultBBBWMTWDiLep_ - sqrt( (resultBBBWMTWDiLep_ *(muonIsoTAPRelUncertainty_ * MuIsoFraction)) *(resultBBBWMTWDiLep_ *(muonIsoTAPRelUncertainty_ * MuIsoFraction)) + MuIsoStatDown_ * MuIsoStatDown_);
		if (muonIsoTAPDown_<0.0001)muonIsoTAPDown_=0.0001;
		//if(debug_)	std::cout<<"muonIsoTAPDown_::"<<muonIsoTAPDown_<<std::endl;
		//if(debug_)	std::cout<<"MuIsoStatDown_"<<MuIsoStatDown_<<std::endl;
			if(debug_)	std::cout<<"6";
		if (muonIsoTAPUp_ >10) muonIsoTAPUp_=10;
		if (muonIsoTAPDown_<0.01) muonIsoTAPDown_=0.01;

		int muonRecoXaxisMC= MuRecoMCTAPRel_->GetXaxis()->FindBin(deltaRMuJet_);
		if (MuRecoMCTAPRel_->GetXaxis()->GetXmax() < deltaRMuJet_)  muonRecoXaxisMC = MuRecoMCTAPRel_->GetXaxis()->FindBin(MuRecoMCTAPRel_->GetXaxis()->GetXmax()-0.1 );
		if (muonRecoXaxisMC > MuRecoMCTAPRel_->GetNbinsX()) muonRecoXaxisMC-=1;
		int muonRecoYaxisMC= MuRecoMCTAPRel_->GetYaxis()->FindBin(MuPt_);
		if (MuRecoMCTAPRel_->GetYaxis()->GetXmax() < MuPt_)  muonRecoYaxisMC=MuRecoMCTAPRel_->GetYaxis()->FindBin(MuRecoMCTAPRel_->GetYaxis()->GetXmax()-0.1 );
		if (muonRecoYaxisMC > MuRecoMCTAPRel_->GetNbinsY()) muonRecoYaxisMC-=1;
		double muonRecoEffMC = MuRecoMCTAPRel_->GetBinContent(muonRecoXaxisMC,muonRecoYaxisMC );
		if (muonRecoEffMC>0.999) muonRecoEffMC=0.999;
		if (muonRecoEffMC<0.01) muonRecoEffMC=0.01;
		if(debug_)	std::cout<<"muonRecoEffMCTAP"<<muonRecoEffMC<<std::endl;
		int muonRecoXaxisData= MuRecoDataTAPRel_->GetXaxis()->FindBin(deltaRMuJet_);
		if (MuRecoDataTAPRel_->GetXaxis()->GetXmax() < deltaRMuJet_)  muonRecoXaxisData=MuRecoDataTAPRel_->GetXaxis()->FindBin(MuRecoDataTAPRel_->GetXaxis()->GetXmax()-0.1 );
		if (muonRecoXaxisData > MuRecoDataTAPRel_->GetNbinsX()) muonRecoXaxisData-=1;
		int muonRecoYaxisData= MuRecoDataTAPRel_->GetYaxis()->FindBin(MuPt_);
		if (MuRecoDataTAPRel_->GetYaxis()->GetXmax() < MuPt_)  muonRecoYaxisData=MuRecoDataTAPRel_->GetYaxis()->FindBin(MuRecoDataTAPRel_->GetYaxis()->GetXmax()-0.1 );
		if (muonRecoYaxisData > MuRecoDataTAPRel_->GetNbinsY()) muonRecoYaxisData-=1;
		double muonRecoEffData = MuRecoDataTAPRel_->GetBinContent(muonRecoXaxisData,muonRecoYaxisData );
		if (muonRecoEffData>0.999) muonRecoEffData=0.999;
		if (muonRecoEffData<0.01) muonRecoEffData=0.01;
		if(debug_)	std::cout<<"muonRecoEffDataTAP"<<muonRecoEffData<<std::endl;
		double muonRecoWeightMC = eventWeight_ * 1 / muonBinByBinIsoEff_ * (1-muonRecoEffMC)/muonRecoEffMC;
		if(debug_)	std::cout<<"muonRecoWeightMCTAP"<<muonRecoWeightMC<<std::endl;
		double muonRecoWeightData = eventWeight_ * 1 / muonBinByBinIsoEff_ * (1-muonRecoEffData)/muonRecoEffData;
		if(debug_)	std::cout<<"muonRecoWeightDataTAP"<<muonRecoWeightData<<std::endl;
		muonTAPRecoWeightMC_= resultBBBWMTWDiLep_ - muonBinByBinRecoWeight_ + muonRecoWeightMC;
		muonTAPRecoWeightData_= resultBBBWMTWDiLep_ - muonBinByBinRecoWeight_ + muonRecoWeightData;
			if(debug_)	std::cout<<"7";
		muonRecoTAPRelUncertainty_ = (muonRecoWeightMC-muonRecoWeightData)/muonRecoWeightMC;
		if(debug_)	std::cout<<"muonRecoTAPRelUncertainty_"<<muonRecoTAPRelUncertainty_<<std::endl;
		if (muonRecoTAPRelUncertainty_<0.00) muonRecoTAPRelUncertainty_=muonRecoTAPRelUncertainty_*(-1);
		if(debug_)	std::cout<<"muonRecoTAPRelUncertainty_"<<muonRecoTAPRelUncertainty_<<std::endl;
		double MuRecoFraction = muonBinByBinRecoWeight_/resultBBBWMTWDiLep_;
		if(debug_)	std::cout<<"MuRecoFraction"<<MuRecoFraction<<std::endl;
		if(debug_)	std::cout<<"resultBBBWMTWDiLep_::"<<resultBBBWMTWDiLep_<<std::endl;	
		if(debug_)	std::cout<<"MuRecoStatUp_::"<<MuRecoStatUp_<<std::endl;	
		if(debug_)	std::cout<<"MuRecoStatDown_::"<<MuRecoStatDown_<<std::endl;
		if(debug_)	std::cout<<"MuRecoTagUp_::"<<resultBBBWMTWDiLep_ * (muonRecoTAPRelUncertainty_ * MuRecoFraction) * resultBBBWMTWDiLep_ * (muonRecoTAPRelUncertainty_ * MuRecoFraction)<<std::endl;	
		if(debug_)	std::cout<<"MuRecoTagDown_::"<<resultBBBWMTWDiLep_ *(muonRecoTAPRelUncertainty_ * MuRecoFraction) * resultBBBWMTWDiLep_ *(muonRecoTAPRelUncertainty_ * MuRecoFraction)<<std::endl;		
		muonRecoTAPUp_ = resultBBBWMTWDiLep_ + sqrt( resultBBBWMTWDiLep_ * (muonRecoTAPRelUncertainty_ * MuRecoFraction) * resultBBBWMTWDiLep_ * (muonRecoTAPRelUncertainty_ * MuRecoFraction) + MuRecoStatUp_ * MuRecoStatUp_ );
		muonRecoTAPDown_ = resultBBBWMTWDiLep_ - sqrt( resultBBBWMTWDiLep_ *(muonRecoTAPRelUncertainty_ * MuRecoFraction) * resultBBBWMTWDiLep_ *(muonRecoTAPRelUncertainty_ * MuRecoFraction) + MuRecoStatDown_ * MuRecoStatDown_);
		if (muonRecoTAPDown_<0.0001)muonRecoTAPDown_=0.0001;
		if(debug_)	std::cout<<"muonRecoTAPUp_::"<<muonRecoTAPUp_<<std::endl;	
		if(debug_)	std::cout<<"muonRecoTAPDown_::"<<muonRecoTAPDown_<<std::endl;



		if(debug_)	std::cout<<"Muonfinished"<<std::endl;
		}

////

		// elec tag and probev uncertainties

		if (TAPUncertaintiesHTNJET_)
		{

		int elecRecoXaxisMC= ElecRecoMCTAP_->GetXaxis()->FindBin(ht_);
		if (elecRecoXaxisMC > ElecRecoMCTAP_->GetNbinsX()) elecRecoXaxisMC-=1;
		int elecRecoYaxisMC= ElecRecoMCTAP_->GetYaxis()->FindBin(nJets_);
		if (elecRecoYaxisMC > ElecRecoMCTAP_->GetNbinsY()) elecRecoYaxisMC-=1;
		double elecRecoEffMC = ElecRecoMCTAP_->GetBinContent(elecRecoXaxisMC,elecRecoYaxisMC );
		if (elecRecoEffMC>0.999) elecRecoEffMC=0.999;
		if(debug_)	std::cout<<"elecRecoMCTAPEff"<<elecRecoEffMC<<std::endl;
		int elecRecoXaxisData= ElecRecoDataTAP_->GetXaxis()->FindBin(ht_);
		if (elecRecoXaxisData > ElecRecoDataTAP_->GetNbinsX()) elecRecoXaxisData-=1;
		int elecRecoYaxisData= ElecRecoDataTAP_->GetYaxis()->FindBin(nJets_);
		if (elecRecoYaxisData > ElecRecoDataTAP_->GetNbinsY()) elecRecoYaxisData-=1;
		double elecRecoEffData = ElecRecoDataTAP_->GetBinContent(elecRecoXaxisData,elecRecoYaxisData );
		if (elecRecoEffData>0.999) elecRecoEffData=0.999;
		if(debug_)	std::cout<<"elecRecoDataTAPEff"<<elecRecoEffData<<std::endl;
		double elecTAPRecoWeightMC = totalBinByBinMuons_ * (elecBinByBinAccEff_) * (1 - elecRecoEffMC);
		double elecTAPRecoWeightData = totalBinByBinMuons_ * (elecBinByBinAccEff_) * (1 - elecRecoEffData);
		elecRecoTAPRelUncertainty_ = (elecTAPRecoWeightMC-elecTAPRecoWeightData)/elecTAPRecoWeightMC;
		if (elecRecoTAPRelUncertainty_<0.00) elecRecoTAPRelUncertainty_=elecRecoTAPRelUncertainty_*(-1);
		double ElecRecoFraction = elecBinByBinRecoWeight_/resultBBBWMTWDiLep_;
		elecRecoTAPUp_ = resultBBBWMTWDiLep_ + sqrt(resultBBBWMTWDiLep_ * (elecRecoTAPRelUncertainty_ * ElecRecoFraction) * resultBBBWMTWDiLep_ * (elecRecoTAPRelUncertainty_ * ElecRecoFraction) + ElecRecoStatUp_ * ElecRecoStatUp_);
		elecRecoTAPDown_ = resultBBBWMTWDiLep_ - sqrt(resultBBBWMTWDiLep_ * (elecRecoTAPRelUncertainty_ * ElecRecoFraction) * resultBBBWMTWDiLep_ * (elecRecoTAPRelUncertainty_ * ElecRecoFraction) + ElecRecoStatDown_ * ElecRecoStatDown_);
		if (elecRecoTAPDown_<0.001)elecRecoTAPDown_=0.001;

		elecTAPRecoWeightMC_=resultBBBWMTWDiLep_ - elecBinByBinRecoWeight_ + elecTAPRecoWeightMC;
		elecTAPRecoWeightData_=resultBBBWMTWDiLep_ - elecBinByBinRecoWeight_ + elecTAPRecoWeightData;



		int elecIsoXaxisMC= ElecIsoMCTAP_->GetXaxis()->FindBin(ht_);
		if (elecIsoXaxisMC > ElecIsoMCTAP_->GetNbinsX()) elecIsoXaxisMC-=1;
		int elecIsoYaxisMC= ElecIsoMCTAP_->GetYaxis()->FindBin(nJets_);
		if (elecIsoYaxisMC > ElecIsoMCTAP_->GetNbinsY()) elecIsoYaxisMC-=1;
		double elecIsoEffMC = ElecIsoMCTAP_->GetBinContent(elecIsoXaxisMC,elecIsoYaxisMC );
		if (elecIsoEffMC>0.999) elecIsoEffMC=0.999;
		if(debug_)	std::cout<<"elecIsoMCTAPEff"<<elecIsoEffMC<<std::endl;
		int elecIsoXaxisData= ElecIsoDataTAP_->GetXaxis()->FindBin(ht_);
		if (elecIsoXaxisData > ElecIsoDataTAP_->GetNbinsX()) elecIsoXaxisData-=1;
		int elecIsoYaxisData= ElecIsoDataTAP_->GetYaxis()->FindBin(nJets_);
		if (elecIsoYaxisData > ElecIsoDataTAP_->GetNbinsY()) elecIsoYaxisData-=1;
		double elecIsoEffData = ElecIsoDataTAP_->GetBinContent(elecIsoXaxisData,elecIsoYaxisData );
		if (elecIsoEffData>0.999) elecIsoEffData=0.999;
		if(debug_)	std::cout<<"elecIsoDataTAPEff"<<elecIsoEffData<<std::endl;

		double elecTAPIsoWeightMC = totalBinByBinMuons_ * (elecBinByBinAccEff_) * (elecBinByBinRecoEff_) * (1 - elecIsoEffMC);
		double elecTAPIsoWeightData = totalBinByBinMuons_ * (elecBinByBinAccEff_) * (elecBinByBinRecoEff_) * (1 - elecIsoEffData);
		elecIsoTAPRelUncertainty_ = (elecTAPIsoWeightMC-elecTAPIsoWeightData)/elecTAPIsoWeightMC;
		if (elecIsoTAPRelUncertainty_<0.00) elecIsoTAPRelUncertainty_=elecIsoTAPRelUncertainty_*(-1);
		double ElecIsoFraction = elecBinByBinIsoWeight_/resultBBBWMTWDiLep_;
		elecIsoTAPUp_ = resultBBBWMTWDiLep_ + sqrt(resultBBBWMTWDiLep_ * (elecIsoTAPRelUncertainty_ * ElecIsoFraction) * resultBBBWMTWDiLep_ * (elecIsoTAPRelUncertainty_ * ElecIsoFraction)+ ElecIsoStatUp_ * ElecIsoStatUp_);

		elecIsoTAPDown_ = resultBBBWMTWDiLep_ - sqrt(resultBBBWMTWDiLep_ * (elecIsoTAPRelUncertainty_ * ElecIsoFraction) * resultBBBWMTWDiLep_ * (elecIsoTAPRelUncertainty_ * ElecIsoFraction) + ElecIsoStatDown_ * ElecIsoStatDown_ );
		if (elecIsoTAPDown_<0.001)elecIsoTAPDown_=0.001;

		elecTAPIsoWeightMC_=resultBBBWMTWDiLep_ - elecBinByBinIsoWeight_ + elecTAPIsoWeightMC;
		elecTAPIsoWeightData_=resultBBBWMTWDiLep_ - elecBinByBinIsoWeight_ + elecTAPIsoWeightData;

		}

		if (!TAPUncertaintiesHTNJET_)
		{
		if(debug_)	std::cout<<"Elecstarted"<<std::endl;
		int elecRecoXaxisMC= ElecRecoMCTAPRel_->GetXaxis()->FindBin(deltaRMuJet_);
		if (ElecRecoMCTAPRel_->GetXaxis()->GetXmax() < deltaRMuJet_)  elecRecoXaxisMC=ElecRecoMCTAPRel_->GetXaxis()->FindBin(ElecRecoMCTAPRel_->GetXaxis()->GetXmax()-0.1 );
		if (elecRecoXaxisMC > ElecRecoMCTAPRel_->GetNbinsX()) elecRecoXaxisMC-=1;
		int elecRecoYaxisMC= ElecRecoMCTAPRel_->GetYaxis()->FindBin(MuPt_);
		if (ElecRecoMCTAPRel_->GetYaxis()->GetXmax() < MuPt_)  elecRecoYaxisMC=ElecRecoMCTAPRel_->GetYaxis()->FindBin(ElecRecoMCTAPRel_->GetYaxis()->GetXmax()-0.1 );
		if (elecRecoYaxisMC > ElecRecoMCTAPRel_->GetNbinsY()) elecRecoYaxisMC-=1;
		double elecRecoEffMC = ElecRecoMCTAPRel_->GetBinContent(elecRecoXaxisMC,elecRecoYaxisMC );
		if (elecRecoEffMC>0.999) elecRecoEffMC=0.999;
		if(debug_)	std::cout<<"elecRecoMCTAPEff"<<elecRecoEffMC<<std::endl;
		int elecRecoXaxisData= ElecRecoDataTAPRel_->GetXaxis()->FindBin(deltaRMuJet_);
		if (ElecRecoDataTAPRel_->GetXaxis()->GetXmax() < deltaRMuJet_)  elecRecoXaxisData=ElecRecoDataTAPRel_->GetXaxis()->FindBin(ElecRecoDataTAPRel_->GetXaxis()->GetXmax()-0.1 );
		if (elecRecoXaxisData > ElecRecoDataTAPRel_->GetNbinsX()) elecRecoXaxisData-=1;
		int elecRecoYaxisData= ElecRecoDataTAPRel_->GetYaxis()->FindBin(MuPt_);
		if (ElecRecoDataTAPRel_->GetYaxis()->GetXmax() < MuPt_)  elecRecoYaxisData=ElecRecoDataTAPRel_->GetYaxis()->FindBin(ElecRecoDataTAPRel_->GetYaxis()->GetXmax()-0.1 );
		if (elecRecoYaxisData > ElecRecoDataTAPRel_->GetNbinsY()) elecRecoYaxisData-=1;
		double elecRecoEffData = ElecRecoDataTAPRel_->GetBinContent(elecRecoXaxisData,elecRecoYaxisData );
		if (elecRecoEffData>0.999) elecRecoEffData=0.999;
		if(debug_)	std::cout<<"elecRecoDataTAPEff"<<elecRecoEffData<<std::endl;
		double elecTAPRecoWeightMC = totalBinByBinMuons_ * (elecBinByBinAccEff_) * (1 - elecRecoEffMC);
		double elecTAPRecoWeightData = totalBinByBinMuons_ * (elecBinByBinAccEff_) * (1 - elecRecoEffData);
		elecRecoTAPRelUncertainty_ = (elecTAPRecoWeightMC-elecTAPRecoWeightData)/elecTAPRecoWeightMC;
		if (elecRecoTAPRelUncertainty_<0.00) elecRecoTAPRelUncertainty_=elecRecoTAPRelUncertainty_*(-1);
		double ElecRecoFraction = elecBinByBinRecoWeight_/resultBBBWMTWDiLep_;
		elecRecoTAPUp_ = resultBBBWMTWDiLep_ + sqrt(resultBBBWMTWDiLep_ * (elecRecoTAPRelUncertainty_ * ElecRecoFraction) * resultBBBWMTWDiLep_ * (elecRecoTAPRelUncertainty_ * ElecRecoFraction) + ElecRecoStatUp_ * ElecRecoStatUp_);
		elecRecoTAPDown_ = resultBBBWMTWDiLep_ - sqrt(resultBBBWMTWDiLep_ * (elecRecoTAPRelUncertainty_ * ElecRecoFraction) * resultBBBWMTWDiLep_ * (elecRecoTAPRelUncertainty_ * ElecRecoFraction) + ElecRecoStatDown_ * ElecRecoStatDown_);
		if (elecRecoTAPDown_<0.001)elecRecoTAPDown_=0.001;

		elecTAPRecoWeightMC_=resultBBBWMTWDiLep_ - elecBinByBinRecoWeight_ + elecTAPRecoWeightMC;
		elecTAPRecoWeightData_=resultBBBWMTWDiLep_ - elecBinByBinRecoWeight_ + elecTAPRecoWeightData;



		int elecIsoXaxisMC= ElecIsoMCTAPRel_->GetXaxis()->FindBin(deltaRMuJet_);
		if (ElecIsoMCTAPRel_->GetXaxis()->GetXmax() < deltaRMuJet_)  elecIsoXaxisMC=ElecIsoMCTAPRel_->GetXaxis()->FindBin(ElecIsoMCTAPRel_->GetXaxis()->GetXmax()-0.1 );
		if (elecIsoXaxisMC > ElecIsoMCTAPRel_->GetNbinsX()) elecIsoXaxisMC-=1;
		int elecIsoYaxisMC= ElecIsoMCTAPRel_->GetYaxis()->FindBin(MuPt_);
		if (ElecIsoMCTAPRel_->GetYaxis()->GetXmax() < MuPt_)  elecIsoYaxisMC=ElecIsoMCTAPRel_->GetYaxis()->FindBin(ElecIsoMCTAPRel_->GetYaxis()->GetXmax()-0.1 );
		if (elecIsoYaxisMC > ElecIsoMCTAPRel_->GetNbinsY()) elecIsoYaxisMC-=1;
		double elecIsoEffMC = ElecIsoMCTAPRel_->GetBinContent(elecIsoXaxisMC,elecIsoYaxisMC );
		if (elecIsoEffMC>0.999) elecIsoEffMC=0.999;
		if(debug_)	std::cout<<"elecIsoMCTAPEff"<<elecIsoEffMC<<std::endl;
		int elecIsoXaxisData= ElecIsoDataTAPRel_->GetXaxis()->FindBin(deltaRMuJet_);
		if (ElecIsoDataTAPRel_->GetXaxis()->GetXmax() < deltaRMuJet_)  elecIsoXaxisData=ElecIsoDataTAPRel_->GetXaxis()->FindBin(ElecIsoDataTAPRel_->GetXaxis()->GetXmax()-0.1 );
		if (elecIsoXaxisData > ElecIsoDataTAPRel_->GetNbinsX()) elecIsoXaxisData-=1;
		int elecIsoYaxisData= ElecIsoDataTAPRel_->GetYaxis()->FindBin(MuPt_);
		if (ElecIsoDataTAPRel_->GetYaxis()->GetXmax() < MuPt_)  elecIsoYaxisData=ElecIsoDataTAPRel_->GetYaxis()->FindBin(ElecIsoDataTAPRel_->GetYaxis()->GetXmax()-0.1 );
		if (elecIsoYaxisData > ElecIsoDataTAPRel_->GetNbinsY()) elecIsoYaxisData-=1;
		double elecIsoEffData = ElecIsoDataTAPRel_->GetBinContent(elecIsoXaxisData,elecIsoYaxisData );
		if (elecIsoEffData>0.999) elecIsoEffData=0.999;
		if(debug_)	std::cout<<"elecIsoDataTAPEff"<<elecIsoEffData<<std::endl;

		double elecTAPIsoWeightMC = totalBinByBinMuons_ * (elecBinByBinAccEff_) * (elecBinByBinRecoEff_) * (1 - elecIsoEffMC);
		double elecTAPIsoWeightData = totalBinByBinMuons_ * (elecBinByBinAccEff_) * (elecBinByBinRecoEff_) * (1 - elecIsoEffData);
		elecIsoTAPRelUncertainty_ = (elecTAPIsoWeightMC-elecTAPIsoWeightData)/elecTAPIsoWeightMC;
		if (elecIsoTAPRelUncertainty_<0.00) elecIsoTAPRelUncertainty_=elecIsoTAPRelUncertainty_*(-1);
		double ElecIsoFraction = elecBinByBinIsoWeight_/resultBBBWMTWDiLep_;
		elecIsoTAPUp_ = resultBBBWMTWDiLep_ + sqrt(resultBBBWMTWDiLep_ * (elecIsoTAPRelUncertainty_ * ElecIsoFraction) * resultBBBWMTWDiLep_ * (elecIsoTAPRelUncertainty_ * ElecIsoFraction)+ ElecIsoStatUp_ * ElecIsoStatUp_);

		elecIsoTAPDown_ = resultBBBWMTWDiLep_ - sqrt(resultBBBWMTWDiLep_ * (elecIsoTAPRelUncertainty_ * ElecIsoFraction) * resultBBBWMTWDiLep_ * (elecIsoTAPRelUncertainty_ * ElecIsoFraction) + ElecIsoStatDown_ * ElecIsoStatDown_ );
		if (elecIsoTAPDown_<0.001)elecIsoTAPDown_=0.001;

		elecTAPIsoWeightMC_=resultBBBWMTWDiLep_ - elecBinByBinIsoWeight_ + elecTAPIsoWeightMC;
		elecTAPIsoWeightData_=resultBBBWMTWDiLep_ - elecBinByBinIsoWeight_ + elecTAPIsoWeightData;


		if(debug_)	std::cout<<"Elecfinished"<<std::endl;

		}


		// electron uncertainty tag and probe
		if (false)
		{

		int elecRecoXaxisMC= ElecRecoMCTAP_->GetXaxis()->FindBin(deltaRMuJet_);
		if (elecRecoXaxisMC > ElecRecoMCTAP_->GetNbinsX()) elecRecoXaxisMC-=1;
		int elecRecoYaxisMC= ElecRecoMCTAP_->GetYaxis()->FindBin(MuPt_);
		if (elecRecoYaxisMC > ElecRecoMCTAP_->GetNbinsY()) elecRecoYaxisMC-=1;
		double elecRecoEffMC = ElecRecoMCTAP_->GetBinContent(elecRecoXaxisMC,elecRecoYaxisMC );

		int elecRecoXaxisData= ElecRecoDataTAP_->GetXaxis()->FindBin(deltaRMuJet_);
		if (elecRecoXaxisData > ElecRecoDataTAP_->GetNbinsX()) elecRecoXaxisData-=1;
		int elecRecoYaxisData= ElecRecoDataTAP_->GetYaxis()->FindBin(MuPt_);
		if (elecRecoYaxisData > ElecRecoDataTAP_->GetNbinsY()) elecRecoYaxisData-=1;
		double elecRecoEffData = ElecRecoDataTAP_->GetBinContent(elecRecoXaxisData,elecRecoYaxisData );

		double elecRecoWeightMC = totalBinByBinMuons_ * (elecBinByBinAccEff_) * (1 - elecRecoEffMC);
		double elecRecoWeightData = totalBinByBinMuons_ * (elecBinByBinAccEff_) * (1 - elecRecoEffData);
		elecTAPRecoWeightMC_=elecRecoWeightMC;
		elecTAPRecoWeightData_=elecRecoWeightData;
		elecRecoTAPRelUncertainty_ = (elecRecoWeightMC-elecRecoWeightData)/elecRecoWeightData;
		if (elecRecoTAPRelUncertainty_<0.00) elecRecoTAPRelUncertainty_=elecRecoTAPRelUncertainty_*(-1);
		double ElecRecoFraction = elecBinByBinRecoWeight_/resultBBBWMTWDiLep_;
		elecRecoTAPUp_ = resultBBBWMTWDiLep_ + (elecRecoTAPRelUncertainty_ * ElecRecoFraction);
		elecRecoTAPDown_ = resultBBBWMTWDiLep_ - (elecRecoTAPRelUncertainty_ * ElecRecoFraction);


		}
	}
	// const uncertainty of 20% until tag and probe is availabe
	if (TAPConstUncertainty_)
	{
		if(false){
		muonRecoTAPUp_=resultBBBWMTWDiLep_*1.2;
		muonRecoTAPDown_=resultBBBWMTWDiLep_*0.8;
		muonIsoTAPUp_=resultBBBWMTWDiLep_*1.2;
		muonIsoTAPDown_=resultBBBWMTWDiLep_*0.8;}

	//	elecRecoTAPUp_=resultBBBWMTWDiLep_*1.2;
	//	elecRecoTAPDown_=resultBBBWMTWDiLep_*0.8;
	//	elecIsoTAPUp_=resultBBBWMTWDiLep_*1.2;
	//	elecIsoTAPDown_=resultBBBWMTWDiLep_*0.8;
	}
	// acceptance unceratinty
	if (muonAccUncertaintyUp_>0.001 && elecAccUncertaintyUp_>0.001)
	{
		int MTWbin = MTWNJet_->GetXaxis()->FindBin(nJets_);
		if ( MTWbin > MTWNJet_->GetNbinsX() ) MTWbin -=1;
		double mtweff;
		if (MTWCut_)mtweff = MTWNJet_->GetBinContent(MTWbin );
		else mtweff = 1;
		if(debug_)	std::cout<<"acceptanceUncertainty:"<<std::endl;
		if(debug_)	std::cout<<"totalAccweight:"<<muonBinByBinAccWeight_+elecBinByBinAccWeight_<<std::endl;
		if(debug_)	std::cout<<"elecBinByBinAccEffError:"<<elecBinByBinAccEffError<<std::endl;
		double accup=muonBinByBinAccWeight_*muonAccUncertaintyUp_ *0.01 + elecBinByBinAccWeight_* elecAccUncertaintyUp_ *0.01;
		double accdown=muonBinByBinAccWeight_*muonAccUncertaintyDown_ *0.01 + elecBinByBinAccWeight_* elecAccUncertaintyDown_*0.01;
		double accstat=ElecAccStatUp_-muonBinByBinAccWeight_ + MuAccStatUp_-ElecAccStatUp_;
//		if(debug_)	std::cout<<"constatnt fraction up:"<<accup<<std::endl;
//		if(debug_)	std::cout<<"constatnt fraction down:"<<accdown<<std::endl;
//		if(debug_)	std::cout<<"stat up/down:"<<accstat <<std::endl;

		resultWeightBinByBinAccUp_=resultBBBWMTWDiLep_+ sqrt(accup *accup + accstat * accstat);
		resultWeightBinByBinAccDown_=resultBBBWMTWDiLep_- sqrt(accup *accup + accstat * accstat);


		if (resultWeightBinByBinAccDown_<0.0001)resultWeightBinByBinAccDown_=0.0001;
//		if(debug_)	std::cout<<"combined up:"<<resultWeightBinByBinAccUp_ <<std::endl;
//		if(debug_)	std::cout<<"combined down:"<<resultWeightBinByBinAccDown_<<std::endl;
	}
	// diboson Uncertaity
	if (diBosonDown_>0.01)
	{
		resultWeightBinByBinDiBosonDown_ = resultBBBWMTWDiLep_ + resultBBBWMTWDiLep_ * diBosonDown_/100;
	
	}
	if(debug_)	std::cout<<"resultWeightBinByBinDiBosonDown_"<<resultWeightBinByBinDiBosonDown_<<std::endl;
//	if(debug_)	std::cout<<"nonClosureHighNJet_"<<nonClosureHighNJet_<<std::endl;
//	if(debug_)	std::cout<<"nJets_"<<nJets_<<std::endl;
//	if(debug_)	std::cout<<"ht_"<<ht_<<std::endl;
//	if(debug_)	std::cout<<"resultBBBWMTWDiLep_"<<resultBBBWMTWDiLep_<<std::endl;
	// non closure uncertainty
	if (nJets_>2.5)
	{
	resultWeightBinByBinNonClosureUp_= resultBBBWMTWDiLep_ + resultBBBWMTWDiLep_ * nonClosureLowNJet_/100;
	resultWeightBinByBinNonClosureDown_= resultBBBWMTWDiLep_ - resultBBBWMTWDiLep_ * nonClosureLowNJet_/100;
	}
	if ( nJets_>5.5)
	{
	resultWeightBinByBinNonClosureUp_= resultBBBWMTWDiLep_ + resultBBBWMTWDiLep_ * nonClosureHighNJet_/100;
	resultWeightBinByBinNonClosureDown_= resultBBBWMTWDiLep_ - resultBBBWMTWDiLep_ * nonClosureHighNJet_/100;

	}
	if(debug_)	std::cout<<"resultWeightBinByBinNonClosureUp_"<<resultWeightBinByBinNonClosureUp_<<std::endl;
	if(debug_)	std::cout<<"resultWeightBinByBinNonClosureDown_"<<resultWeightBinByBinNonClosureDown_<<std::endl;	



  }
  if (!Mu.isValid() ) error_+=1;
  if ( Mu->size() != 1 ) error_+=10;




   //if(debug_)	std::cout<<"EventLoopDoneExitingPrdocuer"<<std::endl;
	//if(debug_)	std::cout<<"LostLeptonBkg:LostLeptonWeight:"<<resultWeight_<<std::endl;
   tree_->Fill();
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

	// output file
    	edm::Service<TFileService> fs;
  //muons




// produce Iso plots for AN
  if (IsoPlots_)
  {
	TH3F	*muIso = (TH3F*)dMuon->Get("IsoBinByBinMuEff");
	TH2F    *muIso1, *muIso2, *muIso3;
  	// creates the array with the lower edges of the MTW parametrizaion
	double binMHT  [] = {100,200,300,450,600,2500};
	int BinMHT = 5;
	double binHT [] = {500,800,1000,1250,1500,2500};
	int BinHT = 4;
	
	// njet bin 1
	muIso1=fs->make<TH2F>("MuIsoNJet1","MuIsoNJet[3,5]",BinHT,binHT,BinMHT,binMHT);
	muIso2=fs->make<TH2F>("MuIsoNJet2","MuIsoNJet[6,7]",BinHT,binHT,BinMHT,binMHT);
	muIso3=fs->make<TH2F>("MuIsoNJet3","MuIsoNJet[8,Inf]",BinHT,binHT,BinMHT,binMHT);
	muIso1->SetTitle("#mu iso. eff. NJet[3,5];H_{T};#slash{H}_{T};eff.");
	muIso2->SetTitle("#mu iso. eff. NJet[6,7];H_{T};#slash{H}_{T};eff.");
	muIso3->SetTitle("#mu iso. eff. NJet[8,Inf];H_{T};#slash{H}_{T};eff.");

	for (int i=0; i < BinHT+1; i++)
	{
		for (int ii=0;ii < BinMHT+1;ii++)
		{
		muIso1->SetBinContent(i,ii,muIso->GetBinContent(i,ii,2));
		muIso1->SetBinError(i,ii,muIso->GetBinError(i,ii,2));
		muIso2->SetBinContent(i,ii,muIso->GetBinContent(i,ii,3));
		muIso2->SetBinError(i,ii,muIso->GetBinError(i,ii,3));
		muIso3->SetBinContent(i,ii,muIso->GetBinContent(i,ii,4));
		muIso3->SetBinError(i,ii,muIso->GetBinError(i,ii,4));
		}
	}
	
	TH3F	*elecIso = (TH3F*)dElec->Get("IsoBinByBinElecEff");
	TH2F    *elecIso1, *elecIso2, *elecIso3;
  	// creates the array with the lower edges of the MTW parametrizaion
	double binMHTe  [] = {100,200,300,450,600,2500};
	int BinMHTe = 5;
	double binHTe [] = {500,800,1000,1250,1500,2500};
	int BinHTe = 4;
	
	// njet bin 1
	elecIso1=fs->make<TH2F>("ElecIsoNJet1","ElecIsoNJet[3,5]",BinHTe,binHTe,BinMHTe,binMHTe);
	elecIso2=fs->make<TH2F>("ElecIsoNJet2","ElecIsoNJet[6,7]",BinHTe,binHTe,BinMHTe,binMHTe);
	elecIso3=fs->make<TH2F>("ElecIsoNJet3","ElecIsoNJet[8,Inf]",BinHTe,binHTe,BinMHTe,binMHTe);
	elecIso1->SetTitle("elec iso. eff. NJet[3,5];H_{T};#slash{H}_{T};eff.");
	elecIso2->SetTitle("elec iso. eff. NJet[6,7];H_{T};#slash{H}_{T};eff.");
	elecIso3->SetTitle("elec iso. eff. NJet[8,Inf];H_{T};#slash{H}_{T};eff.");

	for (int i=0; i < BinHT+1; i++)
	{
		for (int ii=0;ii < BinMHT+1;ii++)
		{
		elecIso1->SetBinContent(i,ii,elecIso->GetBinContent(i,ii,2));
		elecIso1->SetBinError(i,ii,elecIso->GetBinError(i,ii,2));
		elecIso2->SetBinContent(i,ii,elecIso->GetBinContent(i,ii,3));
		elecIso2->SetBinError(i,ii,elecIso->GetBinError(i,ii,3));
		elecIso3->SetBinContent(i,ii,elecIso->GetBinContent(i,ii,4));
		elecIso3->SetBinError(i,ii,elecIso->GetBinError(i,ii,4));
		}
	}


  }



  //MTW cut eff
  if (MTWCut_)
  {
	MTWNJet_= (TH1F*)dMuon->Get("MTWCutNJet");
  }
//  for (int i=1; 
  // acceptance
//  MuonAccSum_ = (TH1F*)dMuon->Get("MuonAccSum");
//  MuonAccPassed_ = (TH1F*)dMuon->Get("MuonAccPassed");
//  MuonAccEff_ = MuonAccPassed_->Integral(MuonAccPassed_->FindBin(MinMuPT_),(MuonAccPassed_->GetNbinsX()+1))/MuonAccSum_->Integral(0,(MuonAccSum_->GetNbinsX()+1));
//  MuonAccEff2_ = (TH1F*)dMuon->Get("MuonAccEff2");
  //if(debug_)	std::cout<<"LostLeptonBkg:MuonAxxEff Nbinsx:"<<MuonAccEff2_->GetNbinsX()<<std::endl;
//  muonAccXMax_ = MuonAccEff2_->GetXaxis()->GetXmax();
  MuonAccEff3_ = (TH2F*)dMuon->Get("MuonAccEff3");
  muonAccXMax3_ = MuonAccEff3_->GetXaxis()->GetXmax();
  //if(debug_)	std::cout<<"LostLeptonBkg::muonAccXMax_:"<<muonAccXMax_<<std::endl;

  //if(debug_)	std::cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!muonAccEff_"<<MuonAccEff_<<std::endl;
  //if(debug_)	std::cout<<"MinMuPT is set to"<<MinMuPT_<<std::endl;
  //if(debug_)	std::cout<<"Integral boarders"<<MuonAccPassed_->FindBin(MinMuPT_)<<std::endl;
  //if(debug_)	std::cout<<"The Integral for PassedMuons"<<MuonAccPassed_->Integral(MuonAccPassed_->FindBin(MinMuPT_),(MuonAccPassed_->GetNbinsX()+1))<<std::endl;
  //if(debug_)	std::cout<<"The Integral for All muons"<<MuonAccSum_->Integral(0,(MuonAccSum_->GetNbinsX()+1))<<std::endl;





  

  // reconstruction
  MuonRecoEff_ = (TH2F*)dMuon->Get("MuonRecoEff");
  muonRecoXMax_ = MuonRecoEff_->GetXaxis()->GetXmax();
  muonRecoYMax_ = MuonRecoEff_->GetYaxis()->GetXmax();
  MuonRecoEff2_ = (TH2F*)dMuon->Get("MuonRecoEff2");
  muonRecoX2Max_ = MuonRecoEff2_->GetXaxis()->GetXmax();
	//if(debug_)	std::cout<<"muonRecoX2Max_:"<<muonRecoX2Max_<<std::endl;
  muonRecoY2Max_ = MuonRecoEff2_->GetYaxis()->GetXmax();
	//if(debug_)	std::cout<<"muonRecoY2Max_:"<<muonRecoY2Max_<<std::endl;
  // isolation

  MuonIsoEff_ = (TH2F*)dMuon->Get("MuonIsoEff");
  muonIsoXMax_ = MuonIsoEff_->GetXaxis()->GetXmax();
  muonIsoYMax_ = MuonIsoEff_->GetYaxis()->GetXmax();
  MuonIsoEff2_ = (TH2F*)dMuon->Get("MuonIsoEff2");
  muonIsoX2Max_ = MuonIsoEff2_->GetXaxis()->GetXmax();
	//if(debug_)	std::cout<<"muonIsoX2Max_:"<<muonIsoX2Max_<<std::endl;
  muonIsoY2Max_ = MuonIsoEff2_->GetYaxis()->GetXmax();
	//if(debug_)	std::cout<<"muonIsoY2Max_:"<<muonIsoY2Max_<<std::endl;
  //electrons
  // acceptance
  ElecAccSum_ = (TH1F*)dElec->Get("ElecAccSum");
  ElecAccPassed_ = (TH1F*)dElec->Get("ElecAccPassed");
  ElecAccEff_ = ElecAccPassed_->Integral(ElecAccPassed_->FindBin(MinElecPT_),(ElecAccPassed_->GetNbinsX()+1))/ElecAccSum_->Integral(0,(ElecAccSum_->GetNbinsX()+1));
  //if(debug_)	std::cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!elecAccEff_"<<ElecAccEff_<<std::endl;
  // second Acceptance efficiency
  ElecAccEff2_ = (TH1F*)dElec->Get("ElecAccEff2");
  elecAccXMax_ = ElecAccEff2_->GetXaxis()->GetXmax();
  ElecAccEff3_ = (TH2F*)dElec->Get("ElecAccEff3");
  elecAccXMax3_ = ElecAccEff3_->GetXaxis()->GetXmax();
  //if(debug_)	std::cout<<"LostLeptonBkg::elecAccXMax_:"<<elecAccXMax_<<std::endl;
  // reconstruction
  ElecRecoEff_ = (TH2F*)dElec->Get("ElecRecoEff");
  ElecRecoEff2_ = (TH2F*)dElec->Get("ElecRecoEff2");
  // isolation

  ElecIsoEff_ = (TH2F*)dElec->Get("ElecIsoEff");
  ElecIsoEff2_ = (TH2F*)dElec->Get("ElecIsoEff2");

// binbybineff

  MuonBinByBinEff_ = (TH3F*)dMuon->Get("MuonBinByBinEff");
  muonBinByBinXMax_ = MuonBinByBinEff_->GetXaxis()->GetXmax();
  muonBinByBinYMax_ = MuonBinByBinEff_->GetYaxis()->GetXmax();
  muonBinByBinZMax_ = MuonBinByBinEff_->GetZaxis()->GetXmax();


  ElecBinByBinEff_ = (TH3F*)dElec->Get("ElecBinByBinEff");
  elecBinByBinXMax_ = ElecBinByBinEff_->GetXaxis()->GetXmax();
  elecBinByBinYMax_ = ElecBinByBinEff_->GetYaxis()->GetXmax();
  elecBinByBinZMax_ = ElecBinByBinEff_->GetZaxis()->GetXmax();

// seperated binbybineff
  MuonIsoBinByBinEff_ = (TH3F*)dMuon->Get("IsoBinByBinMuEff");
  muonIsoBinByBinXMax_ = MuonIsoBinByBinEff_->GetXaxis()->GetXmax();
  muonIsoBinByBinYMax_ = MuonIsoBinByBinEff_->GetYaxis()->GetXmax();
  muonIsoBinByBinZMax_ = MuonIsoBinByBinEff_->GetZaxis()->GetXmax();

  MuonRecoBinByBinEff_ = (TH3F*)dMuon->Get("RecoBinByBinMuEff");
  muonRecoBinByBinXMax_ = MuonRecoBinByBinEff_->GetXaxis()->GetXmax();
  muonRecoBinByBinYMax_ = MuonRecoBinByBinEff_->GetYaxis()->GetXmax();
  muonRecoBinByBinZMax_ = MuonRecoBinByBinEff_->GetZaxis()->GetXmax();

  MuonAccBinByBinEff_ = (TH3F*)dMuon->Get("AccBinByBinMuEff");
  muonAccBinByBinXMax_ = MuonAccBinByBinEff_->GetXaxis()->GetXmax();
  muonAccBinByBinYMax_ = MuonAccBinByBinEff_->GetYaxis()->GetXmax();
  muonAccBinByBinZMax_ = MuonAccBinByBinEff_->GetZaxis()->GetXmax();


  ElecIsoBinByBinEff_ = (TH3F*)dElec->Get("IsoBinByBinElecEff");
  elecIsoBinByBinXMax_ = ElecIsoBinByBinEff_->GetXaxis()->GetXmax();
  elecIsoBinByBinYMax_ = ElecIsoBinByBinEff_->GetYaxis()->GetXmax();
  elecIsoBinByBinZMax_ = ElecIsoBinByBinEff_->GetZaxis()->GetXmax();

  ElecRecoBinByBinEff_ = (TH3F*)dElec->Get("RecoBinByBinElecEff");
  elecRecoBinByBinXMax_ = ElecRecoBinByBinEff_->GetXaxis()->GetXmax();
  elecRecoBinByBinYMax_ = ElecRecoBinByBinEff_->GetYaxis()->GetXmax();
  elecRecoBinByBinZMax_ = ElecRecoBinByBinEff_->GetZaxis()->GetXmax();

  ElecAccBinByBinEff_ = (TH3F*)dElec->Get("AccBinByBinElecEff");
  elecAccBinByBinXMax_ = ElecAccBinByBinEff_->GetXaxis()->GetXmax();
  elecAccBinByBinYMax_ = ElecAccBinByBinEff_->GetYaxis()->GetXmax();
  elecAccBinByBinZMax_ = ElecAccBinByBinEff_->GetZaxis()->GetXmax();

  // additional iso seperate binbybin bined efficiency
// iso
  MuonIsoBinByBinEff35_ = (TH2F*)dMuon->Get("IsoHTMHTMuEffNJet_35");
  MuonIsoBinByBinEff67_ = (TH2F*)dMuon->Get("IsoHTMHTMuEffNJet_67");
  MuonIsoBinByBinEff8Inf_ = (TH2F*)dMuon->Get("IsoHTMHTMuEffNJet_8Inf");

  ElecIsoBinByBinEff35_ = (TH2F*)dElec->Get("IsoHTMHTElecEffNJet_35");
  ElecIsoBinByBinEff67_ = (TH2F*)dElec->Get("IsoHTMHTElecEffNJet_67");
  ElecIsoBinByBinEff8Inf_ = (TH2F*)dElec->Get("IsoHTMHTElecEffNJet_8Inf");
// reco
  MuonRecoBinByBinEff35_ = (TH2F*)dMuon->Get("RecoHTMHTMuEffNJet_35");
  MuonRecoBinByBinEff67_ = (TH2F*)dMuon->Get("RecoHTMHTMuEffNJet_67");
  MuonRecoBinByBinEff8Inf_ = (TH2F*)dMuon->Get("RecoHTMHTMuEffNJet_8Inf");

  ElecRecoBinByBinEff35_ = (TH2F*)dElec->Get("RecoHTMHTElecEffNJet_35");
  ElecRecoBinByBinEff67_ = (TH2F*)dElec->Get("RecoHTMHTElecEffNJet_67");
  ElecRecoBinByBinEff8Inf_ = (TH2F*)dElec->Get("RecoHTMHTElecEffNJet_8Inf");

//if(debug_)	std::cout<<"LostLeptonBkg::binBybinGetEff ended"<<std::endl;
  if(TAPUncertainties_)
{
	if(debug_)	std::cout<<"LostLeptonBkg::TagAndProbeUncertainties are being calculated!"<<std::endl;
  MuIsoMCTAP_ = (TH2F*)dMuon->Get("MC_TAP_mu_iso_eff");
  MuIsoMCTAPBinXMax_ = MuIsoMCTAP_->GetXaxis()->GetXmax();
  MuIsoMCTAPBinYMax_ = MuIsoMCTAP_->GetYaxis()->GetXmax();


  MuIsoMCTAPRel_ = (TH2F*)dMuon->Get("MC_TAP_mu_iso_eff_deltaR_relPT");



  MuIsoDataTAP_ = (TH2F*)dMuon->Get("Data_TAP_mu_iso_eff");
  MuIsoDataTAPBinXMax_ = MuIsoDataTAP_->GetXaxis()->GetXmax();
  MuIsoDataTAPBinYMax_ = MuIsoDataTAP_->GetYaxis()->GetXmax();

  MuIsoDataTAPRel_ = (TH2F*)dMuon->Get("Data_TAP_mu_iso_eff_deltaR_relPT");



	if(debug_)	std::cout<<"TAPUncertaintiesHTNJET_ being used"<<std::endl;
  MuIsoMCTAPHTNJET_ = (TH2F*)dMuon->Get("MC_TAP_mu_iso_eff");
  MuIsoDataTAPHTNJET_ = (TH2F*)dMuon->Get("Data_TAP_mu_iso_eff");



  MuRecoMCTAP_ = (TH2F*)dMuon->Get("MC_TAP_mu_reco_eff");
  MuRecoMCTAPBinXMax_ = MuRecoMCTAP_->GetXaxis()->GetXmax();
  MuRecoMCTAPBinYMax_ = MuRecoMCTAP_->GetYaxis()->GetXmax();

  MuRecoMCTAPRel_ = (TH2F*)dMuon->Get("MC_TAP_mu_reco_eff_deltaR_PT");
  if(debug_)	std::cout<<"MuRecoMCTAPRel_ X max"<<MuRecoMCTAPRel_->GetXaxis()->GetXmax()<<std::endl;
  if(debug_)	std::cout<<"MuRecoMCTAPRel_ Y max"<<MuRecoMCTAPRel_->GetYaxis()->GetXmax()<<std::endl;



  MuRecoDataTAP_ = (TH2F*)dMuon->Get("Data_TAP_mu_reco_eff");
  MuRecoDataTAPBinXMax_ = MuRecoDataTAP_->GetXaxis()->GetXmax();
  MuRecoDataTAPBinYMax_ = MuRecoDataTAP_->GetYaxis()->GetXmax();

  MuRecoDataTAPRel_ = (TH2F*)dMuon->Get("Data_TAP_mu_reco_eff_deltaR_PT");



  ElecRecoMCTAP_ = (TH2F*)dElec->Get("MC_TAP_elec_reco_eff");
  ElecRecoDataTAP_ = (TH2F*)dElec->Get("Data_TAP_elec_reco_eff");

  ElecRecoMCTAPRel_ = (TH2F*)dElec->Get("MC_TAP_elec_reco_eff_deltaR_PT");
  ElecRecoDataTAPRel_ = (TH2F*)dElec->Get("Data_TAP_elec_reco_eff_deltaR_PT");


  ElecIsoMCTAP_ = (TH2F*)dElec->Get("MC_TAP_elec_iso_eff");
  ElecIsoDataTAP_ = (TH2F*)dElec->Get("Data_TAP_elec_iso_eff");

  ElecIsoMCTAPRel_ = (TH2F*)dElec->Get("MC_TAP_elec_iso_eff_deltaR_PT");
  ElecIsoDataTAPRel_ = (TH2F*)dElec->Get("Data_TAP_elec_iso_eff_deltaR_PT");
}
  // uncertainties tag and probe eff input

  

// output


  	tree_ = fs->make<TTree>("LostLeptonBkg","LostLeptonBkg");

    tree_->Branch("muPromtMatched",&nMu_,"muPromtMatched/I");
    tree_->Branch("nMu",&nMu_,"nMu/I");
    tree_->Branch("nElec",&nElec_,"nElec/I");
    tree_->Branch("LepPt",&lepPt_,"LepPt/F");
    tree_->Branch("LepEta",&lepEta_,"LepEta/F");
    tree_->Branch("LepPhi",&lepPhi_,"LepPhi/F");
    tree_->Branch("MTW",&mtw_,"MTW/F");
    tree_->Branch("MTWCut_",&MTWCut_,"MTWCut_/I");

    tree_->Branch("RecoLevelMuonDeltaR",&deltaRMuJet_,"RecoLevelMuonDeltaR/F");
    tree_->Branch("RecoLevelMuonRelPTJet",&deltaPtClosestJetMu_,"RecoLevelMuonRelPTJet/F");
    tree_->Branch("genDeltaR",&genDeltaR_,"genDeltaR/F");
    tree_->Branch("genPTJet",&genPTJet_,"genPTJet/F");
    tree_->Branch("genPTRelJet",&genPTRelJet_,"genPTRelJet/F");
    tree_->Branch("genPt",&MuPt_,"genPt/F");
    tree_->Branch("genEta",&MuEta_,"genEta/F");
    tree_->Branch("genPhi",&MuPhi_,"genPhi/F");

    tree_->Branch("LostLeptonWeight",&resultWeight_,"LostLeptonWeight/F");
    tree_->Branch("muonAccEff",&MuonAccEff_,"muonAccEff/F");
    tree_->Branch("muonRecoEff",&MuonRecoEff_,"muonRecoEff/F");
    tree_->Branch("muonIsoEff",&MuonIsoEff_,"muonIsoEff/F");
    tree_->Branch("muonIsoWeight",&muonIsoWeight_,"muonIsoWeight/F");
    tree_->Branch("muonRecoWeight",&muonRecoWeight_,"muonRecoWeight/F");
    tree_->Branch("muonAccWeight",&muonAccWeight_,"muonAccWeight/F");

    tree_->Branch("elecAccWeight",&elecAccWeight_,"elecAccWeight/F");
    tree_->Branch("elecRecoWeight",&elecRecoWeight_,"elecRecoWeight/F");
    tree_->Branch("elecIsoWeight",&elecIsoWeight_,"elecIsoWeight/F");
    tree_->Branch("elecAccEff",&elecAccEff_,"elecAccEff/F");
    tree_->Branch("elecRecoEff",&elecRecoEff_,"elecRecoEff/F");
    tree_->Branch("elecIsoEff",&elecIsoEff_,"elecIsoEff/F");

    tree_->Branch("muonIsoWeight2",&muonIsoWeight2_,"muonIsoWeight2/F");
    tree_->Branch("muonAllIsoWeight2",&muAllIsoWeight2_,"muonAllIsoWeight2/F");
    tree_->Branch("muonRecoWeight2",&muonRecoWeight2_,"muonRecoWeight2/F");
    tree_->Branch("muonAccWeight2",&muonAccWeight2_,"muonAccWeight2/F");
    tree_->Branch("muonTotalWeight2",&muonTotalWeight2_,"muonTotalWeight2/F");

    tree_->Branch("elecAccWeight2",&elecAccWeight2_,"elecAccWeight2/F");
    tree_->Branch("elecRecoWeight2",&elecRecoWeight2_,"elecRecoWeight2/F");
    tree_->Branch("elecIsoWeight2",&elecIsoWeight2_,"elecIsoWeight2/F");
    tree_->Branch("elecTotalWeight2",&elecTotalWeight2_,"elecTotalWeight2/F");

    tree_->Branch("resultWeight2",&resultWeight2_,"resultWeight2/F");
    tree_->Branch("resultWeight2MTW_",&resultWeight2MTW_,"resultWeight2MTW/F");
    tree_->Branch("resultWeight",&resultWeight_,"resultWeight/F");
    tree_->Branch("resultWeightMTW_",&resultWeightMTW_,"resultWeightMTW/F");


    tree_->Branch("muonWeightBinByBin",&muonBinByBinWeight_,"muonWeightBinByBin/F");
    tree_->Branch("elecWeightBinByBin",&elecWeightBinByBin_,"elecWeightBinByBin/F");
    tree_->Branch("resultWeightBinByBin",&resultWeightBinByBin_,"resultWeightBinByBin/F");
    tree_->Branch("resultWeightBinByBinMTW",&resultWeightBinByBinMTW_,"resultWeightBinByBinMTW/F");


    tree_->Branch("mtwCorrection",&mtwCorrection_,"mtwCorrection/F");
    // plotting values
    tree_->Branch("HT",&ht_,"HT/F");
    tree_->Branch("MHT",&mht_,"MHT/F");
    tree_->Branch("NJets",&nJets_,"NJets/s");
    tree_->Branch("Weight",&eventWeight_,"Weight/F");
    tree_->Branch("NVtx",&nV_,"NVtx/s");
    tree_->Branch("MT",&met_,"MT/F");
//    tree_->Branch("NVtx",&nV_,"NVtx/s");

	// x check values
	tree_->Branch("muAllIsoWeight",&muAllIsoWeight_,"muAllIsoWeight/F");

	tree_->Branch("Errors",&error_,"Errors/I");
    	tree_->Branch("MuonGenPt",&MuPt_,"MuonGenPt/F");

// binByBin eff seperately
    tree_->Branch("muonBinByBinIsoWeight",&muonBinByBinIsoWeight_,"muonBinByBinIsoWeight/F");
    tree_->Branch("muonBinByBinRecoWeight",&muonBinByBinRecoWeight_,"muonBinByBinRecoWeight/F");
    tree_->Branch("muonBinByBinAccWeight",&muonBinByBinAccWeight_,"muonBinByBinAccWeight/F");
    tree_->Branch("muonBinByBinTotalWeight",&muonBinByBinTotalWeight_,"muonBinByBinTotalWeight/F");

    tree_->Branch("elecBinByBinAccWeight",&elecBinByBinAccWeight_,"elecBinByBinAccWeight/F");
    tree_->Branch("elecBinByBinRecoWeight",&elecBinByBinRecoWeight_,"elecBinByBinRecoWeight/F");
    tree_->Branch("elecBinByBinIsoWeight",&elecBinByBinIsoWeight_,"elecBinByBinIsoWeight/F");
    tree_->Branch("elecBinByBinAccEff",&elecBinByBinAccEff_,"elecBinByBinAccEff/F");
    tree_->Branch("elecBinByBinRecoEff",&elecBinByBinRecoEff_,"elecBinByBinRecoEff/F");
    tree_->Branch("elecBinByBinIsoEff",&elecBinByBinIsoEff_,"elecBinByBinIsoEff/F");
    tree_->Branch("elecBinByBinTotalWeight",&elecBinByBinTotalWeight_,"elecBinByBinTotalWeight/F");

    tree_->Branch("resultBBBW",&resultBBBW_,"resultBBBW/F");

	// corrections and uncertainties
    tree_->Branch("resultBBBWMTW",&resultBBBWMTW_,"resultBBBWMTW/F");
    tree_->Branch("resultBBBWMTWUp",&resultBBBWMTWUp_,"resultBBBWMTWUp/F");
    tree_->Branch("resultBBBWMTWDown",&resultBBBWMTWDown_,"resultBBBWMTWDown/F");

    tree_->Branch("resultBBBWMTWDiLep",&resultBBBWMTWDiLep_,"resultBBBWMTWDiLep/F");
    tree_->Branch("resultBBBWMTWDiLepUp",&resultBBBWMTWDiLepUp_,"resultBBBWMTWDiLepUp/F");
    tree_->Branch("resultBBBWMTWDiLepDown",&resultBBBWMTWDiLepDown_,"resultBBBWMTWDiLepDown/F");

    tree_->Branch("muonIsoTAPRelUncertainty",&muonIsoTAPRelUncertainty_,"muonIsoTAPRelUncertainty/F");
    tree_->Branch("muonIsoTAPUp",&muonIsoTAPUp_,"muonIsoTAPUp/F");
    tree_->Branch("muonIsoTAPDown",&muonIsoTAPDown_,"muonIsoTAPDown/F");

    tree_->Branch("muonRecoTAPRelUncertainty",&muonIsoTAPRelUncertainty_,"muonIsoTAPRelUncertainty/F");
    tree_->Branch("muonRecoTAPUp",&muonRecoTAPUp_,"muonIsoTAPUp/F");
    tree_->Branch("muonRecoTAPDown",&muonRecoTAPDown_,"muonIsoTAPDown/F");

    tree_->Branch("elecIsoTAPRelUncertainty",&elecIsoTAPRelUncertainty_,"elecIsoTAPRelUncertainty/F");
    tree_->Branch("elecIsoTAPUp",&elecIsoTAPUp_,"elecIsoTAPUp/F");
    tree_->Branch("elecIsoTAPDown",&elecIsoTAPDown_,"elecIsoTAPDown/F");

    tree_->Branch("elecRecoTAPRelUncertainty",&elecIsoTAPRelUncertainty_,"elecIsoTAPRelUncertainty/F");
    tree_->Branch("elecRecoTAPUp",&elecRecoTAPUp_,"elecIsoTAPUp/F");
    tree_->Branch("elecRecoTAPDown",&elecRecoTAPDown_,"elecIsoTAPDown/F");

    tree_->Branch("resultWeightBinByBinAccUp",&resultWeightBinByBinAccUp_,"resultWeightBinByBinAccUp/F");
    tree_->Branch("resultWeightBinByBinAccDown",&resultWeightBinByBinAccDown_,"resultWeightBinByBinAccDown/F");
   
    tree_->Branch("resultWeightBBBDiBoUp",&resultBBBWMTWDiLep_,"resultWeightBBBDiBoUp/F");  // set to 0 uncertainty hard coded!!!!
    tree_->Branch("resultWeightBBBDiBoDown",&resultWeightBinByBinDiBosonDown_,"resultWeightBBBDiBoDown/F");

    tree_->Branch("resultWeightBBBNoCloUp",&resultWeightBinByBinNonClosureUp_,"resultWeightBBBNoCloUp/F");  // set to 0 uncertainty hard coded!!!!
    tree_->Branch("resultWeightBBBNoCloDown",&resultWeightBinByBinNonClosureDown_,"resultWeightBBBNoCloDown/F");



	// uncertainty met for mtw
    tree_->Branch("metup",&metup_,"metup/F");
    tree_->Branch("metdown",&metdown_,"metdown/F");


	// MTW match
    tree_->Branch("nRecoMu",&nRecoMu_,"nRecoMu/I");
    tree_->Branch("recoMtw1",&recoMtw1_,"recoMtw1/F");
    tree_->Branch("recoMtw2",&recoMtw2_,"recoMtw2/F");
    tree_->Branch("recoMtw3",&recoMtw3_,"recoMtw3/F");
    tree_->Branch("recoMtw4",&recoMtw4_,"recoMtw4/F");
    tree_->Branch("recoMtw5",&recoMtw5_,"recoMtw5/F");

	// save of configuration
    tree_->Branch("MTWMax",&MTWMax_,"MTWMax/F");
    tree_->Branch("MTWCut",&MTWCut_,"MTWCut/F");
    tree_->Branch("MinMuPT",&MinMuPT_,"MinMuPT/F");
    tree_->Branch("MinElecPT",&MinElecPT_,"MinElecPT/F");
	//if(debug_)	std::cout<<"DiLepCorrection_"<<DiLepCorrection_<<std::endl;
	//if(debug_)	std::cout<<"MTWMax_"<<MTWMax_<<std::endl;
	//if(debug_)	std::cout<<"MTWCut_"<<MTWCut_<<std::endl;
	//if(debug_)	std::cout<<"MinMuPT_"<<MinMuPT_<<std::endl;
    tree_->Branch("DiLepCorrection",&DiLepCorrection_,"DiLepCorrection/F");
    tree_->Branch("DiLepCorrectionUp",&DiLepCorrectionUp_,"DiLepCorrectionUp/F");
    tree_->Branch("DiLepCorrectionDown",&DiLepCorrectionDown_,"DiLepCorrectionDown/F");
    tree_->Branch("TAPUncertainties",&TAPUncertainties_,"TAPUncertainties/F");
    tree_->Branch("TAPConstUncertainty",&TAPConstUncertainty_,"TAPConstUncertainty/F");
    tree_->Branch("MTWUncertaintyUp",&MTWUncertaintyUp_,"MTWUncertaintyUp/F");
    tree_->Branch("MTWUncertaintyDown",&MTWUncertaintyDown_,"MTWUncertaintyDown/F");

	// tag and prob unceratinties
//    tree_->Branch("muonRecoTAPUp",&muonRecoTAPUp_,"muonRecoTAPUp/F");
//    tree_->Branch("muonRecoTAPDown",&muonRecoTAPDown_,"muonRecoTAPDown/F");
//    tree_->Branch("muonIsoTAPUp",&muonIsoTAPUp_,"muonIsoTAPUp/F");
//    tree_->Branch("muonIsoTAPDown",&muonIsoTAPDown_,"muonIsoTAPDown/F");

//    tree_->Branch("elecRecoTAPUp",&elecRecoTAPUp_,"elecRecoTAPUp/F");
//    tree_->Branch("elecRecoTAPDown",&elecRecoTAPDown_,"elecRecoTAPDown/F");
//    tree_->Branch("elecIsoTAPUp",&elecIsoTAPUp_,"elecIsoTAPUp/F");
//    tree_->Branch("elecIsoTAPDown",&elecIsoTAPDown_,"elecIsoTAPDown/F");


    tree_->Branch("muonAccUncertaintyUp",&muonAccUncertaintyUp_,"muonAccUncertaintyUp/F");
    tree_->Branch("muonAccUncertaintyDown",&muonAccUncertaintyDown_,"muonAccUncertaintyDown/F");
    tree_->Branch("elecAccUncertaintyUp",&elecAccUncertaintyUp_,"elecAccUncertaintyUp/F");
    tree_->Branch("elecAccUncertaintyDown",&elecAccUncertaintyDown_,"elecAccUncertaintyDown/F");

    tree_->Branch("muonTAPIsoWeightMC",&muonTAPIsoWeightMC_,"muonTAPIsoWeightMC/F");
    tree_->Branch("muonTAPIsoWeightData",&muonTAPIsoWeightData_,"muonTAPIsoWeightData/F");
    tree_->Branch("muonTAPRecoWeightMC",&muonTAPRecoWeightMC_,"muonTAPRecoWeightMC/F");
    tree_->Branch("muonTAPRecoWeightData",&muonTAPRecoWeightData_,"muonTAPRecoWeightData/F");

    tree_->Branch("elecTAPIsoWeightMC",&elecTAPIsoWeightMC_,"elecTAPIsoWeightMC/F");
    tree_->Branch("elecTAPIsoWeightData",&elecTAPIsoWeightData_,"elecTAPIsoWeightData/F");
    tree_->Branch("elecTAPRecoWeightMC",&elecTAPRecoWeightMC_,"elecTAPRecoWeightMC/F");
    tree_->Branch("elecTAPRecoWeightData",&elecTAPRecoWeightData_,"elecTAPRecoWeightData/F");


	// correctionValues
    tree_->Branch("diBosonDown",&diBosonDown_,"diBosonDown/F");
    tree_->Branch("nonClosureLowNJet",&nonClosureLowNJet_,"nonClosureLowNJet/F");
    tree_->Branch("nonClosureHighNJet",&nonClosureHighNJet_,"nonClosureHighNJet/F");

}
void 
LostLeptonBkg::ResetValues()
{
	met_ =-1;
	mht_ = -1;
	mtw_ =-1;
	nMu_ = 0;
	nElec_= 0;
	lepPt_=0;
	lepPhi_=0;
	lepEta_=0;
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

	muonIsoEff2_=-1;
	muonIsoWeight2_=-1;

	muonRecoEff2_=-1;
	muonRecoWeight2_=-1;
	
	muonAccWeight_=-1;

	elecIsoEff_=-1;
	elecIsoWeight_=-1;
	elecRecoEff_=-1;
	elecRecoWeight_=-1;

	elecAccWeight_=-1;

	muonTotalWeight_=-1;
	elecTotalWeight_=-1;
	mtwCorrection_=0;
	resultWeight_=-1;

	// x check weights
	muAllIsoWeight_=-1;
	muAllIsoWeight2_=-1;
	error_=0;

muonBinByBinWeight_=-1;
elecWeightBinByBin_=-1;
resultWeightBinByBin_=-1;
resultWeightBinByBinMTW_=-1;

resultBBBW_=-1;
resultBBBWMTW_=-1;

resultBBBWMTWDiLep_=0;
resultBBBWMTWDiLepUp_=0;
resultBBBWMTWDiLepDown_=0;

muonBinByBinIsoWeight_=-1;
muonBinByBinRecoWeight_=-1;
muonBinByBinAccWeight_=-1;
muonBinByBinTotalWeight_=-1;
muonBinByBinIsoEff_=-1;
muonBinByBinRecoEff_=-1;
muonBinByBinAccEff_=-1;
muonBinByBinIsoEffError_=-1;
muonBinByBinRecoEffError_=-1;
muonBinByBinAccEffError_=-1;

elecBinByBinAccWeight_=-1;
elecBinByBinAccEff_=-1;
elecBinByBinAccEffError_=-1;
elecBinByBinRecoWeight_=-1;
elecBinByBinRecoEff_=-1;
elecBinByBinRecoEffError_=-1;
elecBinByBinIsoWeight_=-1;
elecBinByBinIsoEff_=-1;
elecBinByBinIsoEffError_=-1;
elecBinByBinTotalWeight_=-1;

// tag and probe uncertainties
muonTAPIsoWeightMC_=0;
muonTAPIsoWeightData_=0;
muonTAPRecoWeightMC_=0;
muonTAPRecoWeightData_=0;

elecTAPIsoWeightMC_=0;
elecTAPIsoWeightData_=0;
elecTAPRecoWeightMC_=0;
elecTAPRecoWeightData_=0;


muonIsoTAPRelUncertainty_=0;
muonIsoTAPUp_=0;
muonIsoTAPDown_=0;
muonRecoTAPRelUncertainty_=0;
muonRecoTAPUp_=0;
muonRecoTAPDown_=0;

elecIsoTAPRelUncertainty_=0;
elecIsoTAPUp_=0;
elecIsoTAPDown_=0;
elecRecoTAPRelUncertainty_=0;
elecRecoTAPUp_=0;
elecRecoTAPDown_=0;

// MTW uncertainty
resultBBBWMTWUp_=0;
resultBBBWMTWDown_=0;

// acceptance unceratinty
resultWeightBinByBinAccUp_=0;
resultWeightBinByBinAccDown_=0;

resultBBBWMTW_=0;
resultBBBWMTWUp_=0;
resultBBBWMTWDown_=0;
resultBBBWMTWDiLep_=0;
resultBBBWMTWDiLepUp_=0;
resultBBBWMTWDiLepDown_=0;
muonIsoTAPRelUncertainty_=0;
muonIsoTAPUp_=0;
muonIsoTAPDown_=0;
muonIsoTAPRelUncertainty_=0;
muonRecoTAPUp_=0;
muonRecoTAPDown_=0;
elecIsoTAPRelUncertainty_=0;
elecIsoTAPUp_=0;
elecIsoTAPDown_=0;
elecIsoTAPRelUncertainty_=0;
elecRecoTAPUp_=0;
elecRecoTAPDown_=0;
resultWeightBinByBinAccUp_=0;
resultWeightBinByBinAccDown_=0;
resultBBBWMTWDiLep_=0;
resultWeightBinByBinDiBosonDown_=0;
resultWeightBinByBinNonClosureUp_=0;
resultWeightBinByBinNonClosureDown_=0;
// not isolated cs but reco good MTW match
nRecoMu_=0;
recoMtw1_=0;
recoMtw2_=0;
recoMtw3_=0;
recoMtw4_=0;
recoMtw5_=0;


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
