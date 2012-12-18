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

   //input corrections
   DiLepCorrection_ = iConfig.getParameter <double> ("DiLepCorrection");
   DiLepCorrectionUp_ = iConfig.getParameter <double> ("DiLepCorrectionUp");
   DiLepCorrectionDown_ = iConfig.getParameter <double> ("DiLepCorrectionDown");

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

  edm::Handle< edm::View<reco::Candidate> > htJets;
  iEvent.getByLabel(HtJetsTag_,htJets);
  if( htJets.isValid() ) {
    nJets_ = htJets->size();
  }
//  edm::Handle< edm::View<reco::Candidate> > mht;
 // iEvent.getByLabel(MhtTag_,mht);
 // if( mht.isValid() ) {
  //  mht_ = mht->at(0).pt();
 // }

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
  edm::Handle <edm::View <pat::Jet> > caloJets;
  iEvent.getByLabel(CaloJetTag_, caloJets);



  // set up the result weight


  if (caloJets.isValid() )
  {
	nCaloJets_=caloJets->size();
  }

  // start the prediciton from Muon CS

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
//	std::cout<<"mtw calculated. MTW="<<mtw_<<std::endl;
	
	// do the MTW cut
//	std::cout<<"MTWCut_bool"<<MTWCut_<<std::endl;
//	std::cout<<"MTWMax_"<<MTWMax_<<std::endl;
	
	// addional weight calculator
	// check if any of the values is out of the eff bining


//		int muonAccXaxis= MuonAccEff2_->GetXaxis()->FindBin(mht_);
//		if (muonAccXaxis > MuonAccEff2_->GetNbinsX()) muonAccXaxis-=1;
		int muonAccXaxis= MuonAccEff3_->GetXaxis()->FindBin(mht_);
		if (muonAccXaxis > MuonAccEff3_->GetNbinsX()) muonAccXaxis-=1;
		int muonAccYaxis= MuonAccEff3_->GetYaxis()->FindBin(nJets_+0.1);
		if (nJets_<3) muonAccYaxis= MuonAccEff3_->GetYaxis()->FindBin(3);
		if (muonAccYaxis > MuonAccEff3_->GetNbinsY()) muonAccYaxis-=1;
	
		int muonIsoXaxis= MuonIsoEff_->GetXaxis()->FindBin(deltaRMuJet_);
		// check if the deltaRmuJet is greater thatn the maximum in the histogramm
//		std::cout<<"a"<<std::endl;
		if (muonIsoXaxis > MuonIsoEff_->GetNbinsX()) muonIsoXaxis-=1;
//		std::cout<<"muonIsoXaxis has been found"<<std::endl;
		int muonIsoYaxis= MuonIsoEff_->GetYaxis()->FindBin(genPTRelJet_);
		// check if the deltaPTclosestJetMu is greater than the maximum stored in the histogramm
		if (muonIsoYaxis > MuonIsoEff_->GetNbinsY()) muonIsoYaxis-=1;
//		std::cout<<"1";
		int muonRecoXaxis = MuonRecoEff2_->GetXaxis()->FindBin(deltaRMuJet_);
		if (muonRecoXaxis > MuonRecoEff2_->GetNbinsX() ) muonRecoXaxis-=1;
//		std::cout<<"2";
		int muonRecoYaxis = MuonRecoEff2_->GetYaxis()->FindBin(MuPt_);
		if (muonRecoYaxis > MuonRecoEff2_->GetNbinsY() ) muonRecoYaxis-=1;
//		std::cout<<"3";
		muonIsoEff_ = MuonIsoEff_->GetBinContent(muonIsoXaxis,muonIsoYaxis );
		if (muonIsoEff_ <0.01 || muonIsoEff_ > 1) error_+=100;
		if (muonIsoEff_<0.001) muonIsoEff_=0.001;
		if (muonIsoEff_>1 ) muonIsoEff_=1;
		muonIsoWeight_ = eventWeight_ * (1 - muonIsoEff_)/muonIsoEff_;	

		muonRecoEff_ = MuonRecoEff2_->GetBinContent(muonRecoXaxis,muonRecoYaxis);
		if (muonRecoEff_ <0.001 || muonRecoEff_ > 1) error_+=1000;
		muonRecoWeight_ = eventWeight_ * 1 / muonIsoEff_ * (1-muonRecoEff_)/muonRecoEff_;
		muAllIsoWeight_ =  eventWeight_ * 1 / muonIsoEff_;
//		std::cout<<"d"<<std::endl;
		// the muon out of acceptance fraction
		muonAccEff_ = MuonAccEff3_->GetBinContent(muonAccXaxis,muonAccYaxis);
		muonAccWeight_ = eventWeight_ * 1/muonIsoEff_ * 1/muonRecoEff_ *(1-muonAccEff_)/muonAccEff_;
//		std::cout<<"e"<<std::endl;
		// total muon weight
		totalMuons_ = eventWeight_ / (muonAccEff_ * muonRecoEff_ * muonIsoEff_);
		muonTotalWeight_ = muonIsoWeight_ + muonRecoWeight_ + muonAccWeight_;


		// electrons
//		int elecAccXaxis = ElecAccEff2_->GetXaxis()->FindBin(mht_);
//		if (elecAccXaxis > ElecAccEff2_->GetNbinsX()) elecAccXaxis-=1;
		int elecAccXaxis= ElecAccEff3_->GetXaxis()->FindBin(mht_);
		if (elecAccXaxis > ElecAccEff3_->GetNbinsX()) elecAccXaxis-=1;
		int elecAccYaxis= ElecAccEff3_->GetYaxis()->FindBin(nJets_+0.1);
		if (nJets_<3) elecAccYaxis= ElecAccEff3_->GetYaxis()->FindBin(3);
		if (elecAccYaxis > MuonAccEff3_->GetNbinsY()) elecAccYaxis-=1;
	
		int elecIsoXaxis= ElecIsoEff_->GetXaxis()->FindBin(deltaRMuJet_);
		// check if the deltaRmuJet is greater thatn the maximum in the histogramm
//		std::cout<<"a"<<std::endl;
		if (elecIsoXaxis > ElecIsoEff_->GetNbinsX()) elecIsoXaxis-=1;
//		std::cout<<"muonIsoXaxis has been found"<<std::endl;
		int elecIsoYaxis= ElecIsoEff_->GetYaxis()->FindBin(genPTRelJet_);
		// check if the deltaPTclosestJetMu is greater than the maximum stored in the histogramm
		if (elecIsoYaxis > ElecIsoEff_->GetNbinsY()) elecIsoYaxis-=1;
//		std::cout<<"1";
		int elecRecoXaxis = ElecRecoEff2_->GetXaxis()->FindBin(deltaRMuJet_);
		if (elecRecoXaxis > ElecRecoEff2_->GetNbinsX() ) elecRecoXaxis-=1;
//		std::cout<<"2";
		int elecRecoYaxis = ElecRecoEff2_->GetYaxis()->FindBin(MuPt_);
		if (elecRecoYaxis > ElecRecoEff2_->GetNbinsY() ) elecRecoYaxis-=1;
//		std::cout<<"3";

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



		////////////////////////////////////////////////// Second parametrization



		int muonAccXaxis2= MuonAccEff2_->GetXaxis()->FindBin(mht_);
		if (muonAccXaxis2 > MuonAccEff2_->GetNbinsX()) muonAccXaxis2-=1;

		int muonAccXaxis3= MuonAccEff3_->GetXaxis()->FindBin(mht_);
		if (muonAccXaxis3 > MuonAccEff3_->GetNbinsX()) muonAccXaxis3-=1;
		int muonAccYaxis3= MuonAccEff3_->GetYaxis()->FindBin(nJets_+0.1);
		if (nJets_<3) muonAccYaxis3= MuonAccEff3_->GetYaxis()->FindBin(3);
//		if (muonAccYaxis3 > MuonAccEff3_->GetNbinsY()) muonAccYaxis3-=1;
	
		int muonIsoXaxis2= MuonIsoEff2_->GetXaxis()->FindBin(deltaRMuJet_);
		// check if the deltaRmuJet is greater thatn the maximum in the histogramm
//		std::cout<<"a"<<std::endl;
		if (muonIsoXaxis2 > MuonIsoEff2_->GetNbinsX()) muonIsoXaxis2-=1;
		if (muonIsoXaxis2 ==1 ) 
		{
			muonIsoXaxis2 = 2;  // test if the lowest delta R is not functioning
			error_+=2;
		}
//		std::cout<<"muonIsoXaxis has been found"<<std::endl;
		int muonIsoYaxis2= MuonIsoEff2_->GetYaxis()->FindBin(MuPt_);
		// check if the deltaPTclosestJetMu is greater than the maximum stored in the histogramm
		if (muonIsoYaxis2 > MuonIsoEff2_->GetNbinsY()) muonIsoYaxis2-=1;
//		std::cout<<"1";
		int muonRecoXaxis2 = MuonRecoEff2_->GetXaxis()->FindBin(deltaRMuJet_);
		if (muonRecoXaxis2 > MuonRecoEff2_->GetNbinsX() ) muonRecoXaxis2-=1;
//		std::cout<<"2";
		int muonRecoYaxis2 = MuonRecoEff2_->GetYaxis()->FindBin(MuPt_);
		if (muonRecoYaxis2 > MuonRecoEff2_->GetNbinsY() ) muonRecoYaxis2-=1;
//		std::cout<<"3";
		muonIsoEff2_ = MuonIsoEff2_->GetBinContent(muonIsoXaxis2,muonIsoYaxis2 );
		if (muonIsoEff2_ <0.001 || muonIsoEff2_ > 1) error_+=100;
		if (muonIsoEff2_<0.001) muonIsoEff2_=0.001;
		if (muonIsoEff2_>1 ) muonIsoEff2_=1;
		muonIsoWeight2_ = eventWeight_ * (1 - muonIsoEff2_)/muonIsoEff2_;	

		muonRecoEff2_ = MuonRecoEff2_->GetBinContent(muonRecoXaxis2,muonRecoYaxis2 );
		if (muonRecoEff2_ <0.001 || muonRecoEff2_ > 1) error_+=1000;
		muonRecoWeight2_ = eventWeight_ * 1 / muonIsoEff2_ * (1-muonRecoEff2_)/muonRecoEff2_;
		muAllIsoWeight2_ =  eventWeight_ * 1 / muonIsoEff2_;
//		std::cout<<"d"<<std::endl;
		// the muon out of acceptance fraction
		muonAccEff2_ = MuonAccEff3_->GetBinContent(muonAccXaxis3,muonAccYaxis3);
		muonAccWeight2_ = eventWeight_ * 1/muonIsoEff2_ * 1/muonRecoEff2_ *(1-muonAccEff2_)/muonAccEff2_;
//		std::cout<<"e"<<std::endl;
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
//		if (elecAccYaxis3 > ElecAccEff3_->GetNbinsY()) elecAccYaxis3-=1;
	
		int elecIsoXaxis2= ElecIsoEff2_->GetXaxis()->FindBin(deltaRMuJet_);
		// check if the deltaRmuJet is greater thatn the maximum in the histogramm
//		std::cout<<"a"<<std::endl;
		if (elecIsoXaxis2 > ElecIsoEff2_->GetNbinsX()) elecIsoXaxis2-=1;
//		std::cout<<"muonIsoXaxis has been found"<<std::endl;
		int elecIsoYaxis2= ElecIsoEff2_->GetYaxis()->FindBin(MuPt_);
		// check if the deltaPTclosestJetMu is greater than the maximum stored in the histogramm
		if (elecIsoYaxis2 > ElecIsoEff2_->GetNbinsY()) elecIsoYaxis2-=1;
//		std::cout<<"1";
		int elecRecoXaxis2 = ElecRecoEff2_->GetXaxis()->FindBin(deltaRMuJet_);
		if (elecRecoXaxis2 > ElecRecoEff2_->GetNbinsX() ) elecRecoXaxis2-=1;
//		std::cout<<"2";
		int elecRecoYaxis2 = ElecRecoEff2_->GetYaxis()->FindBin(MuPt_);
		if (elecRecoYaxis2 > ElecRecoEff2_->GetNbinsY() ) elecRecoYaxis2-=1;
//		std::cout<<"3";

		// totalMuons_ are the total number of muons including all not iso reoc and acc muons! should be by definiton equal to the electron amount
		elecAccEff2_ = ElecAccEff3_->GetBinContent(elecAccXaxis3,elecAccYaxis3);
		if (elecAccEff2_ >1 || elecAccEff2_ <0.001) error_+=10000;
		elecAccWeight2_ = totalMuons_ * (1 - elecAccEff2_);

		elecRecoEff2_ = ElecRecoEff2_->GetBinContent(elecRecoXaxis2,elecRecoYaxis2 );
		if (elecRecoEff2_ <0.001 || elecRecoEff2_ > 1) error_+=100000;
		elecRecoWeight2_ = totalMuons_ * (elecAccEff2_) * (1 - elecRecoEff2_);
	
		elecIsoEff2_ = ElecIsoEff2_->GetBinContent(elecIsoXaxis2,elecIsoYaxis2 );
		if (elecIsoEff2_ <0.001 || elecIsoEff2_ > 1) error_+=1000000;
		elecIsoWeight2_ = totalMuons_ * elecAccEff2_ * elecRecoEff2_ * (1 - elecIsoEff2_);

		elecTotalWeight2_ = elecAccWeight2_ + elecRecoWeight2_ + elecIsoWeight2_;
		resultWeight2_ = muonTotalWeight2_ + elecTotalWeight2_;

		if(MTWCut_)
		{
			int MTWbin = MTWEff_->GetXaxis()->FindBin(mht_);
			if ( MTWbin > MTWEff_->GetNbinsX() ) MTWbin -=1;
			resultWeight2MTW_ = resultWeight2_ / MTWEff_->GetBinContent(MTWbin );
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

	// binbybin seperately
		int muonBinByBinAccXaxis= MuonAccBinByBinEff_->GetXaxis()->FindBin(ht_);
		if (muonBinByBinAccXaxis > MuonAccBinByBinEff_->GetNbinsX()) muonBinByBinAccXaxis-=1;
		int muonBinByBinAccYaxis= MuonAccBinByBinEff_->GetYaxis()->FindBin(mht_);
		if (muonBinByBinAccYaxis > MuonAccBinByBinEff_->GetNbinsY()) muonBinByBinAccYaxis-=1;
		int muonBinByBinAccZaxis= MuonAccBinByBinEff_->GetZaxis()->FindBin(nJets_+0.1);
		if (muonBinByBinAccZaxis > MuonAccBinByBinEff_->GetNbinsZ()) muonBinByBinAccZaxis-=1;

		int muonBinByBinIsoXaxis= MuonIsoBinByBinEff_->GetXaxis()->FindBin(ht_);
		if (muonBinByBinIsoXaxis > MuonIsoBinByBinEff_->GetNbinsX()) muonBinByBinIsoXaxis-=1;
		int muonBinByBinIsoYaxis= MuonIsoBinByBinEff_->GetYaxis()->FindBin(mht_);
		if (muonBinByBinIsoYaxis > MuonIsoBinByBinEff_->GetNbinsY()) muonBinByBinIsoYaxis-=1;
		int muonBinByBinIsoZaxis= MuonIsoBinByBinEff_->GetZaxis()->FindBin(nJets_+0.1);
		if (muonBinByBinIsoZaxis > MuonIsoBinByBinEff_->GetNbinsZ()) muonBinByBinIsoZaxis-=1;

		int muonBinByBinRecoXaxis= MuonRecoBinByBinEff_->GetXaxis()->FindBin(ht_);
		if (muonBinByBinRecoXaxis > MuonRecoBinByBinEff_->GetNbinsX()) muonBinByBinRecoXaxis-=1;
		int muonBinByBinRecoYaxis= MuonRecoBinByBinEff_->GetYaxis()->FindBin(mht_);
		if (muonBinByBinRecoYaxis > MuonRecoBinByBinEff_->GetNbinsY()) muonBinByBinRecoYaxis-=1;
		int muonBinByBinRecoZaxis= MuonRecoBinByBinEff_->GetZaxis()->FindBin(nJets_+0.1);
		if (muonBinByBinRecoZaxis > MuonRecoBinByBinEff_->GetNbinsZ()) muonBinByBinRecoZaxis-=1;

	// calc eff and weights
		muonBinByBinIsoEff_ = MuonIsoBinByBinEff_->GetBinContent(muonBinByBinIsoXaxis,muonBinByBinIsoYaxis,muonBinByBinIsoZaxis );
		if (muonBinByBinIsoEff_ <0.01 || muonBinByBinIsoEff_ > 1) error_+=102;
		if (muonBinByBinIsoEff_<0.01) muonBinByBinIsoEff_=0.01;
		if (muonBinByBinIsoEff_>1 ) muonBinByBinIsoEff_=1;
		muonBinByBinIsoWeight_ = eventWeight_ * (1 - muonBinByBinIsoEff_)/muonBinByBinIsoEff_;	
	std::cout<<"LostLeptonBkg::muonBinByBinIsoWeight_:"<<muonBinByBinIsoWeight_<<std::endl;
		muonBinByBinRecoEff_ = MuonRecoBinByBinEff_->GetBinContent(muonBinByBinRecoXaxis,muonBinByBinRecoYaxis,muonBinByBinRecoZaxis );
		if (muonBinByBinRecoEff_ <0.01 || muonBinByBinRecoEff_ > 1) error_+=103;
		if (muonBinByBinRecoEff_<0.01) muonBinByBinRecoEff_=0.01;
		if (muonBinByBinRecoEff_>1 ) muonBinByBinRecoEff_=1;
		muonBinByBinRecoWeight_ = eventWeight_ * 1 / muonBinByBinIsoEff_ * (1-muonBinByBinRecoEff_)/muonBinByBinRecoEff_;
	std::cout<<"LostLeptonBkg::muonBinByBinRecoWeight_:"<<muonBinByBinRecoWeight_<<std::endl;

		muonBinByBinAccEff_ = MuonAccBinByBinEff_->GetBinContent(muonBinByBinAccXaxis,muonBinByBinAccYaxis,muonBinByBinAccZaxis );
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

		int elecBinByBinIsoXaxis= ElecIsoBinByBinEff_->GetXaxis()->FindBin(ht_);
		if (elecBinByBinIsoXaxis > ElecIsoBinByBinEff_->GetNbinsX()) elecBinByBinIsoXaxis-=1;
		int elecBinByBinIsoYaxis= ElecIsoBinByBinEff_->GetYaxis()->FindBin(mht_);
		if (elecBinByBinIsoYaxis > ElecIsoBinByBinEff_->GetNbinsY()) elecBinByBinIsoYaxis-=1;
		int elecBinByBinIsoZaxis= ElecIsoBinByBinEff_->GetZaxis()->FindBin(nJets_+0.1);
		if (elecBinByBinIsoZaxis > ElecIsoBinByBinEff_->GetNbinsZ()) elecBinByBinIsoZaxis-=1;

		int elecBinByBinRecoXaxis= ElecRecoBinByBinEff_->GetXaxis()->FindBin(ht_);
		if (elecBinByBinRecoXaxis > ElecRecoBinByBinEff_->GetNbinsX()) elecBinByBinRecoXaxis-=1;
		int elecBinByBinRecoYaxis= ElecRecoBinByBinEff_->GetYaxis()->FindBin(mht_);
		if (elecBinByBinRecoYaxis > ElecRecoBinByBinEff_->GetNbinsY()) elecBinByBinRecoYaxis-=1;
		int elecBinByBinRecoZaxis= ElecRecoBinByBinEff_->GetZaxis()->FindBin(nJets_+0.1);
		if (elecBinByBinRecoZaxis > ElecRecoBinByBinEff_->GetNbinsZ()) elecBinByBinRecoZaxis-=1;

	// calc eff and weights
		elecBinByBinAccEff_ = ElecAccBinByBinEff_->GetBinContent(elecBinByBinAccXaxis,elecBinByBinAccYaxis,elecBinByBinAccZaxis );
		if (elecBinByBinAccEff_ <0.01 || elecBinByBinAccEff_ > 1) error_+=103;
		if (elecBinByBinAccEff_<0.01) elecBinByBinAccEff_=0.01;
		if (elecBinByBinAccEff_>1 ) elecBinByBinAccEff_=1;
		elecBinByBinAccWeight_ = totalBinByBinMuons_ * (1 - elecBinByBinAccEff_);
		// total binbybin elec weight


		elecBinByBinRecoEff_ = ElecRecoBinByBinEff_->GetBinContent(elecBinByBinRecoXaxis,elecBinByBinRecoYaxis,elecBinByBinRecoZaxis );
		if (elecBinByBinRecoEff_ <0.01 || elecBinByBinRecoEff_ > 1) error_+=103;
		if (elecBinByBinRecoEff_<0.01) elecBinByBinRecoEff_=0.01;
		if (elecBinByBinRecoEff_>1 ) elecBinByBinRecoEff_=1;
		elecBinByBinRecoWeight_ = totalBinByBinMuons_ * (elecBinByBinAccEff_) * (1 - elecBinByBinRecoEff_);

		elecBinByBinIsoEff_ = ElecIsoBinByBinEff_->GetBinContent(elecBinByBinIsoXaxis,elecBinByBinIsoYaxis,elecBinByBinIsoZaxis );
		if (elecBinByBinIsoEff_ <0.01 || elecBinByBinIsoEff_ > 1) error_+=102;
		if (elecBinByBinIsoEff_<0.01) elecBinByBinIsoEff_=0.01;
		if (elecBinByBinIsoEff_>1 ) elecBinByBinIsoEff_=1;
		elecBinByBinIsoWeight_ = totalBinByBinMuons_ * (elecBinByBinAccEff_) * (elecBinByBinRecoEff_) * (1 - elecBinByBinIsoEff_) ;

		elecBinByBinTotalWeight_ = elecBinByBinIsoWeight_ + elecBinByBinRecoWeight_ + elecBinByBinAccWeight_;
		resultBinByBinWeight_ = elecBinByBinTotalWeight_ + muonBinByBinTotalWeight_;

		if(MTWCut_)
		{
			int MTWbin = MTWEff_->GetXaxis()->FindBin(mht_);
			if ( MTWbin > MTWEff_->GetNbinsX() ) MTWbin -=1;
			resultBinByBinWeightMTW_ = resultBinByBinWeight_ / MTWEff_->GetBinContent(MTWbin );
		}
		else resultBinByBinWeightMTW_ = resultBinByBinWeight_;
		if (abs(DiLepCorrection_))
		{
			resultBinByBinWeightMTWDiLep_= resultBinByBinWeightMTW_ * (1 + DiLepCorrection_/100.);
			std::cout<<"LostLeptonBkg::resultBinByBinWeightMTWDiLep_"<<resultBinByBinWeightMTWDiLep_<<std::endl;

			resultBinByBinWeightMTWDiLepUp_ = resultBinByBinWeightMTWDiLep_ * ( 1 + (std::abs(DiLepCorrection_) * DiLepCorrectionUp_)/100.);
			resultBinByBinWeightMTWDiLepDown_ = resultBinByBinWeightMTWDiLep_ * (1 - ((std::abs(DiLepCorrection_)*DiLepCorrectionDown_)/100.));
		}



	std::cout<<"lostleptonweights calculated"<<std::endl;


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
  
  //muons


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
  elecIsoBinByBinXMax_ = MuonIsoBinByBinEff_->GetXaxis()->GetXmax();
  elecIsoBinByBinYMax_ = MuonIsoBinByBinEff_->GetYaxis()->GetXmax();
  elecIsoBinByBinZMax_ = MuonIsoBinByBinEff_->GetZaxis()->GetXmax();

  ElecRecoBinByBinEff_ = (TH3F*)dElec->Get("RecoBinByBinElecEff");
  elecRecoBinByBinXMax_ = MuonRecoBinByBinEff_->GetXaxis()->GetXmax();
  elecRecoBinByBinYMax_ = MuonRecoBinByBinEff_->GetYaxis()->GetXmax();
  elecRecoBinByBinZMax_ = MuonRecoBinByBinEff_->GetZaxis()->GetXmax();

  ElecAccBinByBinEff_ = (TH3F*)dElec->Get("AccBinByBinElecEff");
  elecAccBinByBinXMax_ = MuonAccBinByBinEff_->GetXaxis()->GetXmax();
  elecAccBinByBinYMax_ = MuonAccBinByBinEff_->GetYaxis()->GetXmax();
  elecAccBinByBinZMax_ = MuonAccBinByBinEff_->GetZaxis()->GetXmax();

std::cout<<"LostLeptonBkg::binBybinGetEff ended"<<std::endl;


// output

    	edm::Service<TFileService> fs;
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

    tree_->Branch("resultBinByBinWeight",&resultBinByBinWeight_,"resultBinByBinWeight/F");

	// corrections and uncertainties
    tree_->Branch("resultBinByBinWeightMTW_",&resultBinByBinWeightMTW_,"resultBinByBinWeightMTW/F");

    tree_->Branch("resultBinByBinWeightMTWDiLep",&resultBinByBinWeightMTWDiLep_,"resultBinByBinWeightMTWDiLep/F");
    tree_->Branch("resultBinByBinWeightMTWDiLepUp",&resultBinByBinWeightMTWDiLepUp_,"resultBinByBinWeightMTWDiLepUp/F");
    tree_->Branch("resultBinByBinWeightMTWDiLepDown",&resultBinByBinWeightMTWDiLepDown_,"resultBinByBinWeightMTWDiLepDown/F");

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

resultBinByBinWeight_=-1;
resultBinByBinWeightMTW_=-1;

resultBinByBinWeightMTWDiLep_=-1;
resultBinByBinWeightMTWDiLepUp_=-1;
resultBinByBinWeightMTWDiLepDown_=-1;

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
