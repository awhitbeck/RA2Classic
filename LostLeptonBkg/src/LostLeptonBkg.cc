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
// $Id: LostLeptonBkg.cc,v 1.7 2012/12/05 13:10:48 adraeger Exp $
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
   MetJetTagUp_= iConfig.getParameter<edm::InputTag>("MetJetTagUp");
   MetJetTagDown_= iConfig.getParameter<edm::InputTag>("MetJetTagDown");
   MTWUncertaintyUp_ = iConfig.getParameter <double> ("MTWUncertaintyUp");
   MTWUncertaintyDown_ = iConfig.getParameter <double> ("MTWUncertaintyDown");
   muonAccUncertaintyUp_= iConfig.getParameter <double> ("muonAccUncertaintyUp");
   muonAccUncertaintyDown_= iConfig.getParameter <double> ("muonAccUncertaintyDown");
   elecAccUncertaintyUp_= iConfig.getParameter <double> ("elecAccUncertaintyUp");
   elecAccUncertaintyDown_= iConfig.getParameter <double> ("elecAccUncertaintyDown");
   diBosonDown_ = iConfig.getParameter <double> ("diBosonDown");

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
   std::cout<<"LostLeptonBkg:EventLoopStarted"<<std::endl;
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


  // true if one isolated muon is found. normal cs case
  if(Mu.isValid() && Mu->size() == 1 && Elec->size()==0 )
  {
	// the jet must not have the same energy as the muon
	nMu_ = Mu->size();
//	std::cout<<"LostLeptonBkg:MuTag="<<MuonTag_<<std::endl;
	if (nMu_!=1) std::cout<<"Number of Muons="<<nMu_<<std::endl;
	MuPt_ = Mu->at(0).pt();
	MuEta_ = Mu->at(0).eta();
	MuPhi_ = Mu->at(0).phi();

	// remove muon from nOfJets if muon is clustered as single jet

//	for (unsigned int i=0; i<nJets_;i++)
//	{
//		if( abs(htJets->at(i).pt() - MuPt_)/MuPt_ < 0.1 && deltaR(htJets->at(i).eta(),htJets->at(i).phi(), MuEta_,MuPhi_) < 0.2 ) nJets_-=1;
//	}
//	std::cout<<"MuFoundStepOneCompleted!"<<std::endl;

  	// calculate relative values for the muon and jets usw.

	//delta R with the closest jet and ptLep/ptJet muonpt vs MHT
	if(caloJets.isValid() )
	{
//	std::pair<double,double> DRtoClostestJet;
//	PtclosestJet = MCEffCalculator::DRToClosestJet(caloJets, 2,3,4);
//		std::cout<<"CaloJetsValid"<<std::endl;
		deltaRMuJet_ = MCEffCalculator::DRToClosestJet(iEvent,CaloJetTag_, MuEta_, MuPhi_).first;
		PtClosestJet_ = MCEffCalculator::DRToClosestJet(iEvent,CaloJetTag_, MuEta_, MuPhi_).second;
		deltaPtClosestJetMu_ =MuPt_/PtClosestJet_;
		genDeltaR_ = MCEffCalculator::DRToClosestJet(iEvent,CaloJetTag_, MuEta_, MuPhi_).first;
		genPTJet_ = MCEffCalculator::DRToClosestJet(iEvent,CaloJetTag_, MuEta_, MuPhi_).second;
		genPTRelJet_ =MuPt_/PtClosestJet_;
//		std::cout<<"deltaRandRelPTcalculated:"<<deltaPtClosestJetMu_<<std::endl;
		
  	}
	
	// Delta R between muon and MHT
	if( mht.isValid() ) 
	{
    		deltaRMuMHT_ = deltaR(mht->at(0).eta(), mht->at(0).phi(),MuEta_,MuPhi_);
//		std::cout<<"MHT is valid"<<std::endl;
		
	}
	// calculate MTw
	mtw_= MCEffCalculator::MTWCalculator(iEvent, MetTag_, MuPt_, MuPhi_);
//	int muonAccXaxis= MuonAccEff2_->GetXaxis()->FindBin(mht_);
//	if (muonAccXaxis > MuonAccEff2_->GetNbinsX()) muonAccXaxis-=1;
	int muonAccXaxis= MuonAccEff3_->GetXaxis()->FindBin(mht_);
	if (muonAccXaxis > MuonAccEff3_->GetNbinsX()) muonAccXaxis-=1;
	int muonAccYaxis= MuonAccEff3_->GetYaxis()->FindBin(nJets_+0.1);
	if (nJets_<3) muonAccYaxis= MuonAccEff3_->GetYaxis()->FindBin(3);
	if (muonAccYaxis > MuonAccEff3_->GetNbinsY()) muonAccYaxis-=1;
	
	int muonIsoXaxis= MuonIsoEff_->GetXaxis()->FindBin(deltaRMuJet_);
	// check if the deltaRmuJet is greater thatn the maximum in the histogramm
//	std::cout<<"a"<<std::endl;
	if (muonIsoXaxis > MuonIsoEff_->GetNbinsX()) muonIsoXaxis-=1;
//	std::cout<<"muonIsoXaxis has been found"<<std::endl;
	int muonIsoYaxis= MuonIsoEff_->GetYaxis()->FindBin(genPTRelJet_);
	// check if the deltaPTclosestJetMu is greater than the maximum stored in the histogramm
	if (muonIsoYaxis > MuonIsoEff_->GetNbinsY()) muonIsoYaxis-=1;
//	std::cout<<"1";
	int muonRecoXaxis = MuonRecoEff2_->GetXaxis()->FindBin(deltaRMuJet_);
	if (muonRecoXaxis > MuonRecoEff2_->GetNbinsX() ) muonRecoXaxis-=1;
//	std::cout<<"2";
	int muonRecoYaxis = MuonRecoEff2_->GetYaxis()->FindBin(MuPt_);
	if (muonRecoYaxis > MuonRecoEff2_->GetNbinsY() ) muonRecoYaxis-=1;
//	std::cout<<"3";
	muonIsoEff_ = MuonIsoEff_->GetBinContent(muonIsoXaxis,muonIsoYaxis );
	if (muonIsoEff_ <0.01 || muonIsoEff_ > 1) error_+=100;
	if (muonIsoEff_<0.001) muonIsoEff_=0.001;
	if (muonIsoEff_>1 ) muonIsoEff_=1;
	muonIsoWeight_ = eventWeight_ * (1 - muonIsoEff_)/muonIsoEff_;	

	muonRecoEff_ = MuonRecoEff2_->GetBinContent(muonRecoXaxis,muonRecoYaxis);
	if (muonRecoEff_ <0.001 || muonRecoEff_ > 1) error_+=1000;
	muonRecoWeight_ = eventWeight_ * 1 / muonIsoEff_ * (1-muonRecoEff_)/muonRecoEff_;
	muAllIsoWeight_ =  eventWeight_ * 1 / muonIsoEff_;
//	std::cout<<"d"<<std::endl;
	// the muon out of acceptance fraction
	muonAccEff_ = MuonAccEff3_->GetBinContent(muonAccXaxis,muonAccYaxis);
	muonAccWeight_ = eventWeight_ * 1/muonIsoEff_ * 1/muonRecoEff_ *(1-muonAccEff_)/muonAccEff_;
//	std::cout<<"e"<<std::endl;
	// total muon weight
	totalMuons_ = eventWeight_ / (muonAccEff_ * muonRecoEff_ * muonIsoEff_);
	muonTotalWeight_ = muonIsoWeight_ + muonRecoWeight_ + muonAccWeight_;


	// electrons
//	int elecAccXaxis = ElecAccEff2_->GetXaxis()->FindBin(mht_);
//	if (elecAccXaxis > ElecAccEff2_->GetNbinsX()) elecAccXaxis-=1;
	int elecAccXaxis= ElecAccEff3_->GetXaxis()->FindBin(mht_);
	if (elecAccXaxis > ElecAccEff3_->GetNbinsX()) elecAccXaxis-=1;
	int elecAccYaxis= ElecAccEff3_->GetYaxis()->FindBin(nJets_+0.1);
	if (nJets_<3) elecAccYaxis= ElecAccEff3_->GetYaxis()->FindBin(3);
	if (elecAccYaxis > MuonAccEff3_->GetNbinsY()) elecAccYaxis-=1;
	int elecIsoXaxis= ElecIsoEff_->GetXaxis()->FindBin(deltaRMuJet_);
	// check if the deltaRmuJet is greater thatn the maximum in the histogramm
//	std::cout<<"a"<<std::endl;
	if (elecIsoXaxis > ElecIsoEff_->GetNbinsX()) elecIsoXaxis-=1;
//	std::cout<<"muonIsoXaxis has been found"<<std::endl;
	int elecIsoYaxis= ElecIsoEff_->GetYaxis()->FindBin(genPTRelJet_);
	// check if the deltaPTclosestJetMu is greater than the maximum stored in the histogramm
	if (elecIsoYaxis > ElecIsoEff_->GetNbinsY()) elecIsoYaxis-=1;
//	std::cout<<"1";
	int elecRecoXaxis = ElecRecoEff2_->GetXaxis()->FindBin(deltaRMuJet_);
	if (elecRecoXaxis > ElecRecoEff2_->GetNbinsX() ) elecRecoXaxis-=1;
//	std::cout<<"2";
	int elecRecoYaxis = ElecRecoEff2_->GetYaxis()->FindBin(MuPt_);
	if (elecRecoYaxis > ElecRecoEff2_->GetNbinsY() ) elecRecoYaxis-=1;
//	std::cout<<"3";
	// totalMuons_ are the total number of muons including all not iso reoc and acc muons! should be by definiton equal to the electron amount
	elecAccEff_ = ElecAccEff3_->GetBinContent(elecAccXaxis,elecAccYaxis);
	if (elecAccEff_ >1 || elecAccEff_ <0.001) error_+=10000;
	elecAccWeight_ = totalMuons_ * (1 - elecAccEff_);

	elecRecoEff_ = ElecRecoEff2_->GetBinContent(elecRecoXaxis,elecRecoYaxis);
	if (elecRecoEff_ <0.001 || elecRecoEff_ > 1) error_+=100000;
	elecRecoWeight_ = totalMuons_ * (elecAccEff_) * (1 - elecRecoEff_);

	elecIsoEff_ = ElecIsoEff_->GetBinContent(elecIsoXaxis,elecIsoYaxis );
	if (elecIsoEff_ <0.001 || elecIsoEff_ > 1) error_+=1000000;
	elecIsoWeight_ = totalMuons_ * elecAccEff_ * elecRecoEff_ * (1 - elecIsoEff_);

	elecTotalWeight_ = elecAccWeight_ + elecRecoWeight_ + elecIsoWeight_;
	resultWeight_ = muonTotalWeight_ + elecTotalWeight_;
	if(MTWCut_)
	{
		int MTWbin = MTWEff_->GetXaxis()->FindBin(mht_);
		if ( MTWbin > MTWEff_->GetNbinsX() ) MTWbin -=1;
		resultWeightMTW_ = resultWeight_ / MTWEff_->GetBinContent(MTWbin );
	}
	// electron
	// binBybin
	int muonBinByBinXAxis = MuonBinByBinEff_->GetXaxis()->FindBin(ht_);
	if (muonBinByBinXAxis > MuonBinByBinEff_->GetNbinsX() ) muonBinByBinXAxis-=1;
	int muonBinByBinYAxis = MuonBinByBinEff_->GetYaxis()->FindBin(mht_);
	if (muonBinByBinYAxis > MuonBinByBinEff_->GetNbinsY() ) muonBinByBinYAxis-=1;
	int muonBinByBinZAxis = MuonBinByBinEff_->GetZaxis()->FindBin(nJets_+0.1);
	if (muonBinByBinZAxis > MuonBinByBinEff_->GetNbinsZ() ) muonBinByBinZAxis-=1;
	muonBinByBinEff_ = MuonBinByBinEff_->GetBinContent(muonBinByBinXAxis,muonBinByBinYAxis,muonBinByBinZAxis);
	if (muonBinByBinEff_>1) muonBinByBinEff_=1;
	if (muonBinByBinEff_<0.001) 
	{
		muonBinByBinEff_=0.001;
		error_+=666;
	}
	muonBinByBinWeight_= eventWeight_ * (1 - muonBinByBinEff_)/muonBinByBinEff_;
	std::cout<<"LostLeptonBkg::muonBinByBinWeight_:"<<muonBinByBinWeight_<<std::endl;

	totalMuonsBinByBin_ = eventWeight_ / (muonBinByBinEff_);
	int elecBinByBinXAxis = ElecBinByBinEff_->GetXaxis()->FindBin(ht_);
	if (elecBinByBinXAxis > ElecBinByBinEff_->GetNbinsX() ) elecBinByBinXAxis-=1;
	int elecBinByBinYAxis = ElecBinByBinEff_->GetYaxis()->FindBin(mht_);
	if (elecBinByBinYAxis > ElecBinByBinEff_->GetNbinsY() ) elecBinByBinYAxis-=1;
	int elecBinByBinZAxis = ElecBinByBinEff_->GetZaxis()->FindBin(nJets_+0.1);
	if (elecBinByBinZAxis > ElecBinByBinEff_->GetNbinsZ() ) elecBinByBinZAxis-=1;
	elecBinByBinEff_ = ElecBinByBinEff_->GetBinContent(elecBinByBinXAxis,elecBinByBinYAxis,elecBinByBinZAxis);
	if (elecBinByBinEff_>1) elecBinByBinEff_=1;
	if (elecBinByBinEff_<0.001) 
	{
		elecBinByBinEff_=0.001;
		error_+=6666;
	}


	elecWeightBinByBin_ = totalMuonsBinByBin_ * (1 - elecBinByBinEff_);
	resultWeightBinByBin_ = elecWeightBinByBin_ + muonBinByBinWeight_;
	if(MTWCut_)
	{
		int MTWbin = MTWEff_->GetXaxis()->FindBin(mht_);
		if ( MTWbin > MTWEff_->GetNbinsX() ) MTWbin -=1;
		resultWeightBinByBinMTW_ = resultWeightBinByBin_ / MTWEff_->GetBinContent(MTWbin );
	}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



	// this parametrization is a combination of the first 2 methods for acceptance binned in MHT and Njets eff are used
	// for reco eff parametrized in deltaRMuJet and lepton pt is used
	// the isolation is obtained according to the binbybin method using eff for each search bin obtained from mc
	int muonAccXaxis3= MuonAccEff3_->GetXaxis()->FindBin(mht_);
	if (muonAccXaxis3 > MuonAccEff3_->GetNbinsX()) muonAccXaxis3-=1;
	int muonAccYaxis3= MuonAccEff3_->GetYaxis()->FindBin(nJets_+0.1);
	if (nJets_<3) muonAccYaxis3= MuonAccEff3_->GetYaxis()->FindBin(3);

		
	int muonIsoXaxis2= MuonIsoEff2_->GetXaxis()->FindBin(deltaRMuJet_);
	// check if the deltaRmuJet is greater thatn the maximum in the histogramm
	std::cout<<"a"<<std::endl;
	if (muonIsoXaxis2 > MuonIsoEff2_->GetNbinsX()) muonIsoXaxis2-=1;
	if (muonIsoXaxis2 ==1 ) 
	{
		muonIsoXaxis2 = 2;  // test if the lowest delta R is not functioning
		error_+=2;
	}
	int muonIsoYaxis2= MuonIsoEff2_->GetYaxis()->FindBin(MuPt_);
	// check if the deltaPTclosestJetMu is greater than the maximum stored in the histogramm
	if (muonIsoYaxis2 > MuonIsoEff2_->GetNbinsY()) muonIsoYaxis2-=1;
	int muonRecoXaxis2 = MuonRecoEff2_->GetXaxis()->FindBin(deltaRMuJet_);
	if (muonRecoXaxis2 > MuonRecoEff2_->GetNbinsX() ) muonRecoXaxis2-=1;
	int muonRecoYaxis2 = MuonRecoEff2_->GetYaxis()->FindBin(MuPt_);
	if (muonRecoYaxis2 > MuonRecoEff2_->GetNbinsY() ) muonRecoYaxis2-=1;
	muonIsoEff2_ = MuonIsoEff2_->GetBinContent(muonIsoXaxis2,muonIsoYaxis2 );
	if (muonIsoEff2_ <0.001 || muonIsoEff2_ > 1) error_+=100;
	if (muonIsoEff2_<0.001) muonIsoEff2_=0.001;
	if (muonIsoEff2_>1 ) muonIsoEff2_=1;
	//muonIsoWeight2_ = eventWeight_ * (1 - muonIsoEff2_)/muonIsoEff2_;	
	
	muonIsoWeight2_ =muonBinByBinIsoWeight_;
	muonIsoEff2_=muonBinByBinIsoEff_;

	muonRecoEff2_ = MuonRecoEff2_->GetBinContent(muonRecoXaxis2,muonRecoYaxis2 );
	if (muonRecoEff2_ <0.001 || muonRecoEff2_ > 1) error_+=1000;
	muonRecoWeight2_ = eventWeight_ * 1 / muonIsoEff2_ * (1-muonRecoEff2_)/muonRecoEff2_;
	muAllIsoWeight2_ =  eventWeight_ * 1 / muonIsoEff2_;
	// the muon out of acceptance fraction
	muonAccEff2_ = MuonAccEff3_->GetBinContent(muonAccXaxis3,muonAccYaxis3);
	muonAccWeight2_ = eventWeight_ * 1/muonIsoEff2_ * 1/muonRecoEff2_ *(1-muonAccEff2_)/muonAccEff2_;
	// total muon weight
	totalMuons_ = eventWeight_ / (muonAccEff2_ * muonRecoEff2_ * muonIsoEff2_);

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
//	std::cout<<"a"<<std::endl;
	if (elecIsoXaxis2 > ElecIsoEff2_->GetNbinsX()) elecIsoXaxis2-=1;
//		std::cout<<"muonIsoXaxis has been found"<<std::endl;
	int elecIsoYaxis2= ElecIsoEff2_->GetYaxis()->FindBin(MuPt_);
	// check if the deltaPTclosestJetMu is greater than the maximum stored in the histogramm
	if (elecIsoYaxis2 > ElecIsoEff2_->GetNbinsY()) elecIsoYaxis2-=1;
	int elecRecoXaxis2 = ElecRecoEff2_->GetXaxis()->FindBin(deltaRMuJet_);
	if (elecRecoXaxis2 > ElecRecoEff2_->GetNbinsX() ) elecRecoXaxis2-=1;
//		std::cout<<"2";
	int elecRecoYaxis2 = ElecRecoEff2_->GetYaxis()->FindBin(MuPt_);
	if (elecRecoYaxis2 > ElecRecoEff2_->GetNbinsY() ) elecRecoYaxis2-=1;
//		std::cout<<"3";

	elecAccEff2_ = ElecAccEff3_->GetBinContent(elecAccXaxis3,elecAccYaxis3);
	if (elecAccEff2_ >1 || elecAccEff2_ <0.001) error_+=10000;
	elecAccWeight2_ = totalMuons_ * (1 - elecAccEff2_);

	elecRecoEff2_ = ElecRecoEff2_->GetBinContent(elecRecoXaxis2,elecRecoYaxis2 );
	if (elecRecoEff2_ <0.001 || elecRecoEff2_ > 1) error_+=100000;
	elecRecoWeight2_ = totalMuons_ * (elecAccEff2_) * (1 - elecRecoEff2_);
	
	elecIsoEff2_ = ElecIsoEff2_->GetBinContent(elecIsoXaxis2,elecIsoYaxis2 );
	if (elecIsoEff2_ <0.001 || elecIsoEff2_ > 1) error_+=1000000;
	//elecIsoWeight2_ = totalMuons_ * elecAccEff2_ * elecRecoEff2_ * (1 - elecIsoEff2_);
	elecIsoWeight2_ =elecBinByBinIsoWeight_;

	elecTotalWeight2_ = elecAccWeight2_ + elecRecoWeight2_ + elecIsoWeight2_;
	resultWeight2_ = muonTotalWeight2_ + elecTotalWeight2_;

	if(MTWCut_)
	{
		int MTWbin = MTWEff_->GetXaxis()->FindBin(mht_);
		if ( MTWbin > MTWEff_->GetNbinsX() ) MTWbin -=1;
		resultWeight2MTW_ = resultWeight2_ / MTWEff_->GetBinContent(MTWbin );
	}







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
	if (nJets_ > 2.5 && 5.5 > nJets_)
	{
		muonBinByBinIsoXaxis = MuonIsoBinByBinEff35_->GetXaxis()->FindBin(ht_);
		muonBinByBinIsoYaxis = MuonIsoBinByBinEff35_->GetYaxis()->FindBin(mht_);
		muonBinByBinIsoEff_ = MuonIsoBinByBinEff35_->GetBinContent(muonBinByBinIsoXaxis,muonBinByBinIsoYaxis);
	}
	if (nJets_ > 5.5 && 7.5 > nJets_)
	{
		muonBinByBinIsoXaxis = MuonIsoBinByBinEff67_->GetXaxis()->FindBin(ht_);
		muonBinByBinIsoYaxis = MuonIsoBinByBinEff67_->GetYaxis()->FindBin(mht_);
		muonBinByBinIsoEff_ = MuonIsoBinByBinEff67_->GetBinContent(muonBinByBinIsoXaxis,muonBinByBinIsoYaxis);
	}
	if (nJets_ > 7.5)
	{
		muonBinByBinIsoXaxis = MuonIsoBinByBinEff8Inf_->GetXaxis()->FindBin(ht_);
		muonBinByBinIsoYaxis = MuonIsoBinByBinEff8Inf_->GetYaxis()->FindBin(mht_);
		muonBinByBinIsoEff_ = MuonIsoBinByBinEff8Inf_->GetBinContent(muonBinByBinIsoXaxis,muonBinByBinIsoYaxis);
	}



	int muonBinByBinRecoXaxis= MuonRecoBinByBinEff_->GetXaxis()->FindBin(ht_);
	if (muonBinByBinRecoXaxis > MuonRecoBinByBinEff_->GetNbinsX()) muonBinByBinRecoXaxis-=1;
	int muonBinByBinRecoYaxis= MuonRecoBinByBinEff_->GetYaxis()->FindBin(mht_);
	if (muonBinByBinRecoYaxis > MuonRecoBinByBinEff_->GetNbinsY()) muonBinByBinRecoYaxis-=1;
	int muonBinByBinRecoZaxis= MuonRecoBinByBinEff_->GetZaxis()->FindBin(nJets_+0.1);
	if (muonBinByBinRecoZaxis > MuonRecoBinByBinEff_->GetNbinsZ()) muonBinByBinRecoZaxis-=1;

	// calc eff and weights
//	muonBinByBinIsoEff_ = MuonIsoBinByBinEff_->GetBinContent(muonBinByBinIsoXaxis,muonBinByBinIsoYaxis,muonBinByBinIsoZaxis );
	if (muonBinByBinIsoEff_ <0.01 || muonBinByBinIsoEff_ > 1) error_+=102;
	if (muonBinByBinIsoEff_<0.01) muonBinByBinIsoEff_=0.01;
	if (muonBinByBinIsoEff_>1 ) muonBinByBinIsoEff_=1;
	muonBinByBinIsoWeight_ = eventWeight_ * (1 - muonBinByBinIsoEff_)/muonBinByBinIsoEff_;	
	std::cout<<"LostLeptonBkg::muonBinByBinIsoWeight_:"<<muonBinByBinIsoWeight_<<std::endl;
	muonBinByBinRecoEff_ = MuonRecoBinByBinEff_->GetBinContent(muonBinByBinRecoXaxis,muonBinByBinRecoYaxis,muonBinByBinRecoZaxis );
	muonBinByBinRecoEff_ = muonRecoEff2_;
	if (muonBinByBinRecoEff_ <0.01 || muonBinByBinRecoEff_ > 1) error_+=103;
	if (muonBinByBinRecoEff_<0.01) muonBinByBinRecoEff_=0.01;
	if (muonBinByBinRecoEff_>1 ) muonBinByBinRecoEff_=1;
	muonBinByBinRecoWeight_ = eventWeight_ * 1 / muonBinByBinIsoEff_ * (1-muonBinByBinRecoEff_)/muonBinByBinRecoEff_;
	std::cout<<"LostLeptonBkg::muonBinByBinRecoWeight_:"<<muonBinByBinRecoWeight_<<std::endl;

	muonBinByBinAccEff_ = MuonAccBinByBinEff_->GetBinContent(muonBinByBinAccXaxis,muonBinByBinAccYaxis,muonBinByBinAccZaxis );
	muonBinByBinAccEff_ = muonAccEff2_;
	if (muonBinByBinAccEff_ <0.01 || muonBinByBinAccEff_ > 1) error_+=103;
	if (muonBinByBinAccEff_<0.01) muonBinByBinAccEff_=0.01;
	if (muonBinByBinAccEff_>1 ) muonBinByBinAccEff_=1;
	muonBinByBinAccWeight_ = eventWeight_ * 1/muonBinByBinIsoEff_ * 1/muonBinByBinRecoEff_ *(1-muonBinByBinAccEff_)/muonBinByBinAccEff_;
	std::cout<<"LostLeptonBkg::muonBinByBinAccWeight_:"<<muonBinByBinAccWeight_<<std::endl;
	// total binbybin muon weight
	muonBinByBinTotalWeight_ = muonBinByBinIsoWeight_ + muonBinByBinRecoWeight_ + muonBinByBinAccWeight_;
	std::cout<<"LostLeptonBkg::muonBinByBinTotalWeight_:"<<muonBinByBinTotalWeight_<<std::endl;
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
	if (nJets_ > 2.5 && 5.5 > nJets_)
	{
		elecBinByBinAccXaxis = ElecIsoBinByBinEff35_->GetXaxis()->FindBin(ht_);
		elecBinByBinAccYaxis = ElecIsoBinByBinEff35_->GetYaxis()->FindBin(mht_);
		elecBinByBinIsoEff_ = ElecIsoBinByBinEff35_->GetBinContent(elecBinByBinIsoXaxis,elecBinByBinIsoYaxis);
	}
	if (nJets_ > 5.5 && 7.5 > nJets_)
	{
		elecBinByBinAccXaxis = ElecIsoBinByBinEff67_->GetXaxis()->FindBin(ht_);
		elecBinByBinAccYaxis = ElecIsoBinByBinEff67_->GetYaxis()->FindBin(mht_);
		elecBinByBinIsoEff_ = ElecIsoBinByBinEff67_->GetBinContent(elecBinByBinIsoXaxis,elecBinByBinIsoYaxis);
	}
	if (nJets_ > 7.5)
	{
		elecBinByBinAccXaxis = ElecIsoBinByBinEff8Inf_->GetXaxis()->FindBin(ht_);
		elecBinByBinAccYaxis = ElecIsoBinByBinEff8Inf_->GetYaxis()->FindBin(mht_);
		elecBinByBinIsoEff_ = ElecIsoBinByBinEff8Inf_->GetBinContent(elecBinByBinIsoXaxis,elecBinByBinIsoYaxis);
	}


	int elecBinByBinRecoXaxis= ElecRecoBinByBinEff_->GetXaxis()->FindBin(ht_);
	if (elecBinByBinRecoXaxis > ElecRecoBinByBinEff_->GetNbinsX()) elecBinByBinRecoXaxis-=1;
	int elecBinByBinRecoYaxis= ElecRecoBinByBinEff_->GetYaxis()->FindBin(mht_);
	if (elecBinByBinRecoYaxis > ElecRecoBinByBinEff_->GetNbinsY()) elecBinByBinRecoYaxis-=1;
	int elecBinByBinRecoZaxis= ElecRecoBinByBinEff_->GetZaxis()->FindBin(nJets_+0.1);
	if (elecBinByBinRecoZaxis > ElecRecoBinByBinEff_->GetNbinsZ()) elecBinByBinRecoZaxis-=1;

	// calc eff and weights
	elecBinByBinAccEff_ = ElecAccBinByBinEff_->GetBinContent(elecBinByBinAccXaxis,elecBinByBinAccYaxis,elecBinByBinAccZaxis );
	elecBinByBinAccEff_ = elecAccEff2_;
	if (elecBinByBinAccEff_ <0.01 || elecBinByBinAccEff_ > 1) error_+=103;
	if (elecBinByBinAccEff_<0.01) elecBinByBinAccEff_=0.01;
	if (elecBinByBinAccEff_>1 ) elecBinByBinAccEff_=1;
	elecBinByBinAccWeight_ = totalBinByBinMuons_ * (1 - elecBinByBinAccEff_);
	// total binbybin elec weight


	elecBinByBinRecoEff_ = ElecRecoBinByBinEff_->GetBinContent(elecBinByBinRecoXaxis,elecBinByBinRecoYaxis,elecBinByBinRecoZaxis );
	elecBinByBinRecoEff_ = elecRecoEff2_;
	if (elecBinByBinRecoEff_ <0.01 || elecBinByBinRecoEff_ > 1) error_+=103;
	if (elecBinByBinRecoEff_<0.01) elecBinByBinRecoEff_=0.01;
	if (elecBinByBinRecoEff_>1 ) elecBinByBinRecoEff_=1;
	elecBinByBinRecoWeight_ = totalBinByBinMuons_ * (elecBinByBinAccEff_) * (1 - elecBinByBinRecoEff_);

//	elecBinByBinIsoEff_ = ElecIsoBinByBinEff_->GetBinContent(elecBinByBinIsoXaxis,elecBinByBinIsoYaxis,elecBinByBinIsoZaxis );
	if (elecBinByBinIsoEff_ <0.01 || elecBinByBinIsoEff_ > 1) error_+=102;
	if (elecBinByBinIsoEff_<0.01) elecBinByBinIsoEff_=0.01;
	if (elecBinByBinIsoEff_>1 ) elecBinByBinIsoEff_=1;
	elecBinByBinIsoWeight_ = totalBinByBinMuons_ * (elecBinByBinAccEff_) * (elecBinByBinRecoEff_) * (1 - elecBinByBinIsoEff_) ;

	elecBinByBinTotalWeight_ = elecBinByBinIsoWeight_ + elecBinByBinRecoWeight_ + elecBinByBinAccWeight_;
	resultBBBW_ = elecBinByBinTotalWeight_ + muonBinByBinTotalWeight_;
	// mtw cut correction
	if(MTWCut_)
	{
		int MTWbin = MTWEff_->GetXaxis()->FindBin(mht_);
		if ( MTWbin > MTWEff_->GetNbinsX() ) MTWbin -=1;
		resultBBBWMTW_ = resultBBBW_ / MTWEff_->GetBinContent(MTWbin );
	}
	else resultBBBWMTW_ = resultBBBW_;
	// dilep correction and corresponding uncertainty
	if (abs(DiLepCorrection_))
	{
		resultBBBWMTWDiLep_= resultBBBWMTW_ * (1 + DiLepCorrection_/100.);
		std::cout<<"LostLeptonBkg::resultBBBWMTWDiLep_"<<resultBBBWMTWDiLep_<<std::endl;
		resultBBBWMTWDiLepUp_ = resultBBBWMTWDiLep_ * ( 1 + (std::abs(DiLepCorrection_) * DiLepCorrectionUp_)/10000.);
		resultBBBWMTWDiLepDown_ = resultBBBWMTWDiLep_ * (1 - ((std::abs(DiLepCorrection_)*DiLepCorrectionDown_)/10000.));
	}
	else resultBBBWMTWDiLep_=resultBBBWMTW_;
	// mtw uncertainty
	if (MTWCut_)
	{
		int MTWbin = MTWEff_->GetXaxis()->FindBin(mht_);
		if ( MTWbin > MTWEff_->GetNbinsX() ) MTWbin -=1;
		resultBBBWMTWUp_ = resultBBBWMTWDiLep_ + resultBBBWMTW_ * (1-MTWEff_->GetBinContent(MTWbin ) ) * MTWUncertaintyUp_*0.01;
		resultBBBWMTWDown_ = resultBBBWMTWDiLep_ - resultBBBWMTW_ * (1-MTWEff_->GetBinContent(MTWbin ) ) * MTWUncertaintyDown_*0.01;
		std::cout<<"MTWEff_->GetBinContent(MTWbin )"<<MTWEff_->GetBinContent(MTWbin )<<std::endl;
		std::cout<<"MTWUncertaintyUp_"<<MTWUncertaintyUp_<<std::endl;
		std::cout<<"MTWCUT resultBBBWMTW_"<<resultBBBWMTW_<<std::endl;
		std::cout<<"MTWCUT resultBBBWMTWUp_"<<resultBBBWMTWUp_<<std::endl;
		std::cout<<"MTWCUT resultBBBWMTWDown_"<<resultBBBWMTWDown_<<std::endl;
	}

	std::cout<<"lostleptonweights calculated"<<std::endl;

  	// calculated the uncertainties from tag and probe mc data comparison
	// turned off for now
	if(TAPUncertainties_)
  	{
		// muon tag and probe uncertainty
		int muonIsoXaxisMC= MuIsoMCTAP_->GetXaxis()->FindBin(deltaRMuJet_);
		if (muonIsoXaxisMC > MuIsoMCTAP_->GetNbinsX()) muonIsoXaxisMC-=1;
		int muonIsoYaxisMC= MuIsoMCTAP_->GetYaxis()->FindBin(genPTRelJet_);
		if (muonIsoYaxisMC > MuIsoMCTAP_->GetNbinsY()) muonIsoYaxisMC-=1;
		double muonIsoEffMC = MuIsoMCTAP_->GetBinContent(muonIsoXaxisMC,muonIsoYaxisMC );

		int muonIsoXaxisData= MuIsoDataTAP_->GetXaxis()->FindBin(deltaRMuJet_);
		if (muonIsoXaxisData > MuIsoDataTAP_->GetNbinsX()) muonIsoXaxisData-=1;
		int muonIsoYaxisData= MuIsoDataTAP_->GetYaxis()->FindBin(genPTRelJet_);
		if (muonIsoYaxisData > MuIsoDataTAP_->GetNbinsY()) muonIsoYaxisData-=1;
		double muonIsoEffData = MuIsoDataTAP_->GetBinContent(muonIsoXaxisData,muonIsoYaxisData );

		double muonIsoWeightMC = eventWeight_ * (1 - muonIsoEffMC)/muonIsoEffMC;
		double muonIsoWeightData = eventWeight_ * (1 - muonIsoEffData)/muonIsoEffData;
		
		muonIsoTAPRelUncertainty_ = (muonIsoWeightMC-muonIsoWeightData)/muonIsoWeightData;
		if (muonIsoTAPRelUncertainty_<-0.00) muonIsoTAPRelUncertainty_=muonIsoTAPRelUncertainty_ * (-1);
		double MuIsoFraction = muonBinByBinIsoWeight_/resultBBBWMTWDiLep_;
		muonIsoTAPUp_ = resultBBBWMTWDiLep_ + (muonIsoTAPRelUncertainty_ * MuIsoFraction);
		muonIsoTAPDown_ = resultBBBWMTWDiLep_ - (muonIsoTAPRelUncertainty_ * MuIsoFraction);

		int muonRecoXaxisMC= MuRecoMCTAP_->GetXaxis()->FindBin(deltaRMuJet_);
		if (muonRecoXaxisMC > MuRecoMCTAP_->GetNbinsX()) muonRecoXaxisMC-=1;
		int muonRecoYaxisMC= MuRecoMCTAP_->GetYaxis()->FindBin(MuPt_);
		if (muonRecoYaxisMC > MuRecoMCTAP_->GetNbinsY()) muonRecoYaxisMC-=1;
		double muonRecoEffMC = MuRecoMCTAP_->GetBinContent(muonRecoXaxisMC,muonRecoYaxisMC );

		int muonRecoXaxisData= MuRecoDataTAP_->GetXaxis()->FindBin(deltaRMuJet_);
		if (muonRecoXaxisData > MuRecoDataTAP_->GetNbinsX()) muonRecoXaxisData-=1;
		int muonRecoYaxisData= MuRecoDataTAP_->GetYaxis()->FindBin(MuPt_);
		if (muonRecoYaxisData > MuRecoDataTAP_->GetNbinsY()) muonRecoYaxisData-=1;
		double muonRecoEffData = MuRecoDataTAP_->GetBinContent(muonRecoXaxisData,muonRecoYaxisData );

		double muonRecoWeightMC = eventWeight_ * 1 / muonBinByBinIsoEff_ * (1-muonRecoEffMC)/muonRecoEffMC;
		double muonRecoWeightData = eventWeight_ * 1 / muonBinByBinIsoEff_ * (1-muonRecoEffData)/muonRecoEffData;
		muonRecoTAPRelUncertainty_ = (muonRecoWeightMC-muonRecoWeightData)/muonRecoWeightData;
		if (muonRecoTAPRelUncertainty_<0.00) muonRecoTAPRelUncertainty_=muonRecoTAPRelUncertainty_*(-1);
		double MuRecoFraction = muonBinByBinRecoWeight_/resultBBBWMTWDiLep_;
		muonRecoTAPUp_ = resultBBBWMTWDiLep_ + (muonRecoTAPRelUncertainty_ * MuRecoFraction);
		muonRecoTAPDown_ = resultBBBWMTWDiLep_ - (muonRecoTAPRelUncertainty_ * MuRecoFraction);

		// electron uncertainty tag and probe
		if (false)
		{
		// elec tag and probe uncertainty
		int elecIsoXaxisMC= ElecIsoMCTAP_->GetXaxis()->FindBin(deltaRMuJet_);
		if (elecIsoXaxisMC > ElecIsoMCTAP_->GetNbinsX()) elecIsoXaxisMC-=1;
		int elecIsoYaxisMC= ElecIsoMCTAP_->GetYaxis()->FindBin(genPTRelJet_);
		if (elecIsoYaxisMC > ElecIsoMCTAP_->GetNbinsY()) elecIsoYaxisMC-=1;
		double elecIsoEffMC = ElecIsoMCTAP_->GetBinContent(elecIsoXaxisMC,elecIsoYaxisMC );

		int elecIsoXaxisData= ElecIsoDataTAP_->GetXaxis()->FindBin(deltaRMuJet_);
		if (elecIsoXaxisData > ElecIsoDataTAP_->GetNbinsX()) elecIsoXaxisData-=1;
		int elecIsoYaxisData= ElecIsoDataTAP_->GetYaxis()->FindBin(genPTRelJet_);
		if (elecIsoYaxisData > ElecIsoDataTAP_->GetNbinsY()) elecIsoYaxisData-=1;
		double elecIsoEffData = ElecIsoDataTAP_->GetBinContent(elecIsoXaxisData,elecIsoYaxisData );

		double elecIsoWeightMC = totalBinByBinMuons_ * (elecBinByBinAccEff_) * (elecBinByBinRecoEff_) * (1 - elecIsoEffMC) ;
		double elecIsoWeightData = totalBinByBinMuons_ * (elecBinByBinAccEff_) * (elecBinByBinRecoEff_) * (1 - elecIsoEffData) ;
		
		elecIsoTAPRelUncertainty_ = (elecIsoWeightMC-elecIsoWeightData)/elecIsoWeightData;
		if (elecIsoTAPRelUncertainty_<-0.00) elecIsoTAPRelUncertainty_=elecIsoTAPRelUncertainty_ * (-1);
		double ElecIsoFraction = elecBinByBinIsoWeight_/resultBBBWMTWDiLep_;
		elecIsoTAPUp_ = resultBBBWMTWDiLep_ + (elecIsoTAPRelUncertainty_ * ElecIsoFraction);
		elecIsoTAPDown_ = resultBBBWMTWDiLep_ - (elecIsoTAPRelUncertainty_ * ElecIsoFraction);

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

		elecRecoTAPUp_=resultBBBWMTWDiLep_*1.2;
		elecRecoTAPDown_=resultBBBWMTWDiLep_*0.8;
		elecIsoTAPUp_=resultBBBWMTWDiLep_*1.2;
		elecIsoTAPDown_=resultBBBWMTWDiLep_*0.8;
	}
	// acceptance unceratinty
	if (muonAccUncertaintyUp_>0.001 && elecAccUncertaintyUp_>0.001)
	{
		int MTWbin = MTWEff_->GetXaxis()->FindBin(mht_);
		if ( MTWbin > MTWEff_->GetNbinsX() ) MTWbin -=1;
		double mtweff;
		if (MTWCut_)mtweff = MTWEff_->GetBinContent(MTWbin );
		else mtweff = 1;
		
		resultWeightBinByBinAccUp_=resultBBBWMTWDiLep_ + muonBinByBinAccWeight_*muonAccUncertaintyUp_ *0.01 * mtweff + elecBinByBinAccWeight_* elecAccUncertaintyUp_ *0.01 * mtweff;
		resultWeightBinByBinAccDown_=resultBBBWMTWDiLep_ - muonBinByBinAccWeight_*muonAccUncertaintyDown_ *0.01 * mtweff - elecBinByBinAccWeight_* elecAccUncertaintyDown_*0.01  * mtweff;
	}
	// diboson Uncertaity
	if (diBosonDown_>0.01)
	{
		resultWeightBinByBinDiBosonDown_ = resultBBBWMTWDiLep_ + resultBBBWMTWDiLep_ * diBosonDown_/100;
	
	}




  }
  if (!Mu.isValid() ) error_+=1;
  if ( Mu->size() != 1 ) error_+=10;




   std::cout<<"EventLoopDoneExitingPrdocuer"<<std::endl;
	std::cout<<"LostLeptonBkg:LostLeptonWeight:"<<resultWeight_<<std::endl;
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
  // acceptance
  MuonAccSum_ = (TH1F*)dMuon->Get("MuonAccSum");
  MuonAccPassed_ = (TH1F*)dMuon->Get("MuonAccPassed");
  MuonAccEff_ = MuonAccPassed_->Integral(MuonAccPassed_->FindBin(MinMuPT_),(MuonAccPassed_->GetNbinsX()+1))/MuonAccSum_->Integral(0,(MuonAccSum_->GetNbinsX()+1));
  MuonAccEff2_ = (TH1F*)dMuon->Get("MuonAccEff2");
  std::cout<<"LostLeptonBkg:MuonAxxEff Nbinsx:"<<MuonAccEff2_->GetNbinsX()<<std::endl;
  muonAccXMax_ = MuonAccEff2_->GetXaxis()->GetXmax();
  MuonAccEff3_ = (TH2F*)dMuon->Get("MuonAccEff3");
  muonAccXMax3_ = MuonAccEff3_->GetXaxis()->GetXmax();
  std::cout<<"LostLeptonBkg::muonAccXMax_:"<<muonAccXMax_<<std::endl;

  std::cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!muonAccEff_"<<MuonAccEff_<<std::endl;
  std::cout<<"MinMuPT is set to"<<MinMuPT_<<std::endl;
  std::cout<<"Integral boarders"<<MuonAccPassed_->FindBin(MinMuPT_)<<std::endl;
  std::cout<<"The Integral for PassedMuons"<<MuonAccPassed_->Integral(MuonAccPassed_->FindBin(MinMuPT_),(MuonAccPassed_->GetNbinsX()+1))<<std::endl;
  std::cout<<"The Integral for All muons"<<MuonAccSum_->Integral(0,(MuonAccSum_->GetNbinsX()+1))<<std::endl;





  

  // reconstruction
  MuonRecoEff_ = (TH2F*)dMuon->Get("MuonRecoEff");
  muonRecoXMax_ = MuonRecoEff_->GetXaxis()->GetXmax();
  muonRecoYMax_ = MuonRecoEff_->GetYaxis()->GetXmax();
  MuonRecoEff2_ = (TH2F*)dMuon->Get("MuonRecoEff2");
  muonRecoX2Max_ = MuonRecoEff2_->GetXaxis()->GetXmax();
	std::cout<<"muonRecoX2Max_:"<<muonRecoX2Max_<<std::endl;
  muonRecoY2Max_ = MuonRecoEff2_->GetYaxis()->GetXmax();
	std::cout<<"muonRecoY2Max_:"<<muonRecoY2Max_<<std::endl;
  // isolation

  MuonIsoEff_ = (TH2F*)dMuon->Get("MuonIsoEff");
  muonIsoXMax_ = MuonIsoEff_->GetXaxis()->GetXmax();
  muonIsoYMax_ = MuonIsoEff_->GetYaxis()->GetXmax();
  MuonIsoEff2_ = (TH2F*)dMuon->Get("MuonIsoEff2");
  muonIsoX2Max_ = MuonIsoEff2_->GetXaxis()->GetXmax();
	std::cout<<"muonIsoX2Max_:"<<muonIsoX2Max_<<std::endl;
  muonIsoY2Max_ = MuonIsoEff2_->GetYaxis()->GetXmax();
	std::cout<<"muonIsoY2Max_:"<<muonIsoY2Max_<<std::endl;
  //electrons
  // acceptance
  ElecAccSum_ = (TH1F*)dElec->Get("ElecAccSum");
  ElecAccPassed_ = (TH1F*)dElec->Get("ElecAccPassed");
  ElecAccEff_ = ElecAccPassed_->Integral(ElecAccPassed_->FindBin(MinElecPT_),(ElecAccPassed_->GetNbinsX()+1))/ElecAccSum_->Integral(0,(ElecAccSum_->GetNbinsX()+1));
  std::cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!elecAccEff_"<<ElecAccEff_<<std::endl;
  // second Acceptance efficiency
  ElecAccEff2_ = (TH1F*)dElec->Get("ElecAccEff2");
  elecAccXMax_ = ElecAccEff2_->GetXaxis()->GetXmax();
  ElecAccEff3_ = (TH2F*)dElec->Get("ElecAccEff3");
  elecAccXMax3_ = ElecAccEff3_->GetXaxis()->GetXmax();
  std::cout<<"LostLeptonBkg::elecAccXMax_:"<<elecAccXMax_<<std::endl;
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
  MuonIsoBinByBinEff35_ = (TH2F*)dMuon->Get("IsoHTMHTMuEffNJet_35");
  MuonIsoBinByBinEff67_ = (TH2F*)dMuon->Get("IsoHTMHTMuEffNJet_67");
  MuonIsoBinByBinEff8Inf_ = (TH2F*)dMuon->Get("IsoHTMHTMuEffNJet_8Inf");

  ElecIsoBinByBinEff35_ = (TH2F*)dElec->Get("IsoHTMHTElecEffNJet_35");
  ElecIsoBinByBinEff67_ = (TH2F*)dElec->Get("IsoHTMHTElecEffNJet_67");
  ElecIsoBinByBinEff8Inf_ = (TH2F*)dElec->Get("IsoHTMHTElecEffNJet_8Inf");

std::cout<<"LostLeptonBkg::binBybinGetEff ended"<<std::endl;
  if(TAPUncertainties_)
{
	std::cout<<"LostLeptonBkg::TagAndProbeUncertainties are being calculated!"<<std::endl;
  MuIsoMCTAP_ = (TH2F*)dMuon->Get("MC_TAP_mu_iso_eff");
  MuIsoMCTAPBinXMax_ = MuIsoMCTAP_->GetXaxis()->GetXmax();
  MuIsoMCTAPBinYMax_ = MuIsoMCTAP_->GetYaxis()->GetXmax();

  MuIsoDataTAP_ = (TH2F*)dMuon->Get("Data_TAP_mu_iso_eff");
  MuIsoDataTAPBinXMax_ = MuIsoDataTAP_->GetXaxis()->GetXmax();
  MuIsoDataTAPBinYMax_ = MuIsoDataTAP_->GetYaxis()->GetXmax();


  MuRecoMCTAP_ = (TH2F*)dMuon->Get("MC_TAP_mu_reco_eff");
  MuRecoMCTAPBinXMax_ = MuRecoMCTAP_->GetXaxis()->GetXmax();
  MuRecoMCTAPBinYMax_ = MuRecoMCTAP_->GetYaxis()->GetXmax();

  MuRecoDataTAP_ = (TH2F*)dMuon->Get("Data_TAP_mu_reco_eff");
  MuRecoDataTAPBinXMax_ = MuRecoDataTAP_->GetXaxis()->GetXmax();
  MuRecoDataTAPBinYMax_ = MuRecoDataTAP_->GetYaxis()->GetXmax();
  std::cout<<"prestuff done"<<std::endl;
}
  // uncertainties tag and probe eff input

  

// output


  	tree_ = fs->make<TTree>("LostLeptonBkg","LostLeptonBkg");

    tree_->Branch("muPromtMatched",&nMu_,"muPromtMatched/I");
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
    tree_->Branch("muonRecoTAPUp",&muonIsoTAPUp_,"muonIsoTAPUp/F");
    tree_->Branch("muonRecoTAPDown",&muonIsoTAPDown_,"muonIsoTAPDown/F");

    tree_->Branch("elecIsoTAPRelUncertainty",&elecIsoTAPRelUncertainty_,"elecIsoTAPRelUncertainty/F");
    tree_->Branch("elecIsoTAPUp",&elecIsoTAPUp_,"elecIsoTAPUp/F");
    tree_->Branch("elecIsoTAPDown",&elecIsoTAPDown_,"elecIsoTAPDown/F");

    tree_->Branch("elecRecoTAPRelUncertainty",&elecIsoTAPRelUncertainty_,"elecIsoTAPRelUncertainty/F");
    tree_->Branch("elecRecoTAPUp",&elecIsoTAPUp_,"elecIsoTAPUp/F");
    tree_->Branch("elecRecoTAPDown",&elecIsoTAPDown_,"elecIsoTAPDown/F");

    tree_->Branch("resultWeightBinByBinAccUp",&resultWeightBinByBinAccUp_,"resultWeightBinByBinAccUp/F");
    tree_->Branch("resultWeightBinByBinAccDown",&resultWeightBinByBinAccDown_,"resultWeightBinByBinAccDown/F");
   
    tree_->Branch("resultWeightBinByBinDiBosonUp",&resultBBBWMTWDiLep_,"resultWeightBinByBinDiBosonUp/F");  // set to 0 uncertainty hard coded!!!!
    tree_->Branch("resultWeightBinByBinDiBosonDown",&resultWeightBinByBinDiBosonDown_,"resultWeightBinByBinDiBosonDown/F");


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
	std::cout<<"DiLepCorrection_"<<DiLepCorrection_<<std::endl;
	std::cout<<"MTWMax_"<<MTWMax_<<std::endl;
	std::cout<<"MTWCut_"<<MTWCut_<<std::endl;
	std::cout<<"MinMuPT_"<<MinMuPT_<<std::endl;
    tree_->Branch("DiLepCorrection",&DiLepCorrection_,"DiLepCorrection/F");
    tree_->Branch("DiLepCorrectionUp",&DiLepCorrectionUp_,"DiLepCorrectionUp/F");
    tree_->Branch("DiLepCorrectionDown",&DiLepCorrectionDown_,"DiLepCorrectionDown/F");
    tree_->Branch("TAPUncertainties",&TAPUncertainties_,"TAPUncertainties/F");
    tree_->Branch("TAPConstUncertainty",&TAPConstUncertainty_,"TAPConstUncertainty/F");
    tree_->Branch("MTWUncertaintyUp",&MTWUncertaintyUp_,"MTWUncertaintyUp/F");
    tree_->Branch("MTWUncertaintyDown",&MTWUncertaintyDown_,"MTWUncertaintyDown/F");

	// tag and prob unceratinties
    tree_->Branch("muonRecoTAPUp",&muonRecoTAPUp_,"muonRecoTAPUp/F");
    tree_->Branch("muonRecoTAPDown",&muonRecoTAPDown_,"muonRecoTAPDown/F");
    tree_->Branch("muonIsoTAPUp",&muonIsoTAPUp_,"muonIsoTAPUp/F");
    tree_->Branch("muonIsoTAPDown",&muonIsoTAPDown_,"muonIsoTAPDown/F");

    tree_->Branch("elecRecoTAPUp",&elecRecoTAPUp_,"elecRecoTAPUp/F");
    tree_->Branch("elecRecoTAPDown",&elecRecoTAPDown_,"elecRecoTAPDown/F");
    tree_->Branch("elecIsoTAPUp",&elecIsoTAPUp_,"elecIsoTAPUp/F");
    tree_->Branch("elecIsoTAPDown",&elecIsoTAPDown_,"elecIsoTAPDown/F");


    tree_->Branch("muonAccUncertaintyUp",&muonAccUncertaintyUp_,"muonAccUncertaintyUp/F");
    tree_->Branch("muonAccUncertaintyDown",&muonAccUncertaintyDown_,"muonAccUncertaintyDown/F");
    tree_->Branch("elecAccUncertaintyUp",&elecAccUncertaintyUp_,"elecAccUncertaintyUp/F");
    tree_->Branch("elecAccUncertaintyDown",&elecAccUncertaintyDown_,"elecAccUncertaintyDown/F");

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

elecBinByBinAccWeight_=-1;
elecBinByBinAccEff_=-1;
elecBinByBinRecoWeight_=-1;
elecBinByBinRecoEff_=-1;
elecBinByBinIsoWeight_=-1;
elecBinByBinIsoEff_=-1;
elecBinByBinTotalWeight_=-1;

// tag and probe uncertainties

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
