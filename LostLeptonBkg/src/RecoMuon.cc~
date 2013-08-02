// -*- C++ -*-
//
// Package:    RecoMuon
// Class:      RecoMuon
// 
/**\class RecoMuon RecoMuon.cc RA2Classic/RecoMuon/src/RecoMuon.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Arne-Rasmus Draeger,68/111,4719,
//         Created:  Mon Jul 29 16:37:03 CEST 2013
// $Id$
//
//


// system include files
#include "RA2Classic/LostLeptonBkg/interface/RecoMuon.h"
#include <TString.h>
#include "DataFormats/Math/interface/deltaPhi.h"
#include <DataFormats/Math/interface/deltaR.h>
#include <DataFormats/PatCandidates/interface/Jet.h>
#include "RA2Classic/LostLeptonBkg/interface/MCEffCalculator.h"


//
// class declaration
//



//
// constants, enums and typedefs
//


//
// static data member definitions
//

//
// constructors and destructor
//
RecoMuon::RecoMuon(const edm::ParameterSet& iConfig)
{
   HtJetsTag_ = iConfig.getParameter<edm::InputTag>("HTJets");
   MhtTag_ = iConfig.getParameter<edm::InputTag>("MhtTag");
   MetTag_ = iConfig.getParameter<edm::InputTag>("MetTag");
   CaloJetTag_ = iConfig.getParameter<edm::InputTag>("CaloJetTag");
   GenTag_ = iConfig.getParameter<edm::InputTag> ("GenTag"); 
   MuonIsoTag_ = iConfig.getParameter<edm::InputTag>("MuonIsoTag");
   MuonRecoTag_ = iConfig.getParameter<edm::InputTag>("MuonRecoTag");
   ElecIsoTag_ = iConfig.getParameter<edm::InputTag>("ElecIsoTag");
   evtWeightTag_ = iConfig.getParameter<edm::InputTag> ("EventWeightTag");
   MTWMax_ = iConfig.getParameter <double> ("MTWMax");
   MTWCut_ = iConfig.getParameter <bool> ("MTWCut");
   MinMuPT_ = iConfig.getParameter <double> ("MinMuPT");
   MinElecPT_ = iConfig.getParameter <double> ("MinElecPT");
   HTTag_ = iConfig.getParameter<edm::InputTag>("HTTag");
   MHTTag_ = iConfig.getParameter<edm::InputTag>("MHTTag");
   NVTag_ = iConfig.getParameter<edm::InputTag>("VertexCollection"); 
   debug_ = iConfig.getParameter<bool> ("debug");
}


RecoMuon::~RecoMuon()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
RecoMuon::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
ResetValues();
if(debug_) std::cout<<"RecoMuon::EventLoop stared"<<std::endl;

// translate tags to objects
edm::Handle< edm::View<reco::Candidate> > met;
iEvent.getByLabel(MetTag_,met);
if( met.isValid() ) 
{
	met_ = met->at(0).pt();
}
  edm::Handle < reco::GenParticleCollection > genParticles;
  iEvent.getByLabel(GenTag_, genParticles);
  if ( genParticles.isValid() ) mc_=true;

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

  edm::Handle <edm::View <reco::Candidate> > MuIso;
  iEvent.getByLabel(MuonIsoTag_,MuIso);
  edm::Handle <edm::View <reco::Candidate> > ElecIso;
  iEvent.getByLabel(ElecIsoTag_,ElecIso);
  edm::Handle <edm::View <reco::Candidate> > MuReco;
  iEvent.getByLabel(MuonRecoTag_,MuReco);
  nIsoMu_=MuIso->size();
  nRecoMu_=MuReco->size();
  nIsoElec_=ElecIso->size();
// loop over iso/reco muons and iso electrons
for( edm::View <reco::Candidate>::const_iterator MuIsoCand = MuIso->begin(); MuIsoCand!=MuIso->end();MuIsoCand++)
{
	isoMuPt_.push_back(MuIsoCand->pt() );
	isoMuEta_.push_back(MuIsoCand->eta() );
	isoMuPhi_.push_back(MuIsoCand->phi() );
	isoMuMtw_.push_back( MCEffCalculator::MTWCalculator(iEvent, MetTag_,MuIsoCand->pt(),MuIsoCand->phi()) );
	isoMuClosestJetPt_.push_back( MCEffCalculator::DRToClosestJet(iEvent,CaloJetTag_, MuIsoCand->eta(), MuIsoCand->phi()).second );
 	isoMuDeltaR_.push_back( MCEffCalculator::DRToClosestJet(iEvent,CaloJetTag_, MuIsoCand->eta(), MuIsoCand->phi()).first );
}
for( edm::View <reco::Candidate>::const_iterator MuIDCand = MuReco->begin(); MuIDCand!=MuReco->end();MuIDCand++)
{
	recoMuPt_.push_back(MuIDCand->pt() );
	recoMuPtTemp_=MuIDCand->pt();
	recoMuEta_.push_back(MuIDCand->eta() );
	recoMuEtaTemp_=MuIDCand->eta();
	recoMuPhi_.push_back(MuIDCand->phi() );
	recoMuPhiTemp_=MuIDCand->phi();
	recoMuMtw_.push_back( MCEffCalculator::MTWCalculator(iEvent, MetTag_,MuIDCand->pt(),MuIDCand->phi()) );
	recoMuClosestJetPt_.push_back( MCEffCalculator::DRToClosestJet(iEvent,CaloJetTag_, MuIDCand->eta(), MuIDCand->phi()).second );
	recoMuClosestJetRelPt_.push_back (MuIDCand->pt()/MCEffCalculator::DRToClosestJet(iEvent,CaloJetTag_, MuIDCand->eta(), MuIDCand->phi()).second );
 	recoMuDeltaR_.push_back( MCEffCalculator::DRToClosestJet(iEvent,CaloJetTag_, MuIDCand->eta(), MuIDCand->phi()).first );
	bool matched=false;
	// try to match reco to iso muon
	for (unsigned int ii=0;ii < isoMuPt_.size();ii++)
	{
		if (debug_)std::cout<<"MuReco::RecoToIsoMatch:IDCandPT"<<MuIDCand->pt()<<std::endl;
		if (debug_)std::cout<<"MuReco::RecoToIsoMatch:IDCandEta"<<MuIDCand->eta()<<std::endl;
		if (debug_)std::cout<<"MuReco::RecoToIsoMatch:IDCandPHi"<<MuIDCand->phi()<<std::endl;		
		if ( RecoMuon::Match(recoMuPtTemp_, recoMuEtaTemp_, recoMuPhiTemp_, isoMuPt_.at(ii), isoMuEta_.at(ii), isoMuPhi_.at(ii)) ) matched=true;
	} 
	recoMuIsoMatched_.push_back(matched);
	// try to match the reco muon to a promt muon
	bool recoMuGenMatched=false;
	if (mc_)
	{
		recoMuGenMatched=false;
		// loop over genparticle collection
		for(reco::GenParticleCollection::const_iterator cand = genParticles->begin(); cand!=genParticles->end(); ++cand) 
		{
			if ( abs(cand->pdgId())!=24 || cand->status()!=3) continue;
			for (unsigned int iii=0; iii < cand->numberOfDaughters(); iii++)
			{
				//muon
				if(abs(cand->daughter(iii)->pdgId() ) == 13) 
				{
					double pt=cand->daughter(iii)->pt();
					double eta=cand->daughter(iii)->eta();
					double phi=cand->daughter(iii)->phi();
					if (debug_)std::cout<<"MuReco::RecoToGen:IDCandPT"<<MuIDCand->pt()<<std::endl;
					if (debug_)std::cout<<"MuReco::RecoToGen:IDCandEta"<<MuIDCand->eta()<<std::endl;
					if (debug_)std::cout<<"MuReco::RecoToGen:IDCandPHi"<<MuIDCand->phi()<<std::endl;	
					if ( RecoMuon::Match(recoMuPtTemp_, recoMuEtaTemp_, recoMuPhiTemp_, pt,eta,phi) ) recoMuGenMatched=true;
					recoMuGenMatchDeltaPT_.push_back(abs(recoMuPtTemp_-pt)/recoMuPtTemp_);
					recoMuGenMatchDeltaR_.push_back(deltaR(recoMuEtaTemp_,recoMuPhiTemp_,eta,phi));
					genMuPt_.push_back(pt);
					genMuEta_.push_back(eta);
					genMuPhi_.push_back(phi);
				}
				//tau
				if (abs(cand->daughter(iii)->pdgId() ) == 15)
				{
					if(RecoMuon::MuTauDecayMatched(cand->daughter(iii)) ) recoMuGenMatched=true;
				}
			}
		}
	}
	recoMuGenMatched_.push_back(recoMuGenMatched);
}
for( edm::View <reco::Candidate>::const_iterator ElecIsoCand = ElecIso->begin(); ElecIsoCand!=ElecIso->end();ElecIsoCand++)
{
	isoElecPt_.push_back(ElecIsoCand->pt() );
	isoElecEta_.push_back(ElecIsoCand->eta() );
	isoElecPhi_.push_back(ElecIsoCand->phi() );
	isoElecMtw_.push_back( MCEffCalculator::MTWCalculator(iEvent, MetTag_,ElecIsoCand->pt(),ElecIsoCand->phi()) );
	isoElecClosestJetPt_.push_back( MCEffCalculator::DRToClosestJet(iEvent,CaloJetTag_, ElecIsoCand->eta(), ElecIsoCand->phi()).second );
 	isoElecDeltaR_.push_back( MCEffCalculator::DRToClosestJet(iEvent,CaloJetTag_, ElecIsoCand->eta(), ElecIsoCand->phi()).first );
}



if (nIsoMu_!=0 || nRecoMu_!=0 || nIsoElec_!=0) tree_->Fill(); 
if(debug_) std::cout<<"RecoMuon::eventLoopEnd"<<std::endl;
}
void
RecoMuon::ResetValues()
{
nIsoMu_=0;
nRecoMu_=0;
nIsoElec_=0;
met_=0;
mht_=0;
ht_=0;
nV_=0;
nJets_=0;
mtw_=0;
mc_=false;
eventWeight_=0;
isoMuPt_.clear();
isoMuEta_.clear();
isoMuPhi_.clear();
isoMuMtw_.clear();
isoMuDeltaR_.clear();
isoMuClosestJetPt_.clear();
recoMuPt_.clear();
recoMuEta_.clear();
recoMuPhi_.clear();
recoMuMtw_.clear();
recoMuDeltaR_.clear();
recoMuClosestJetPt_.clear();
recoMuClosestJetRelPt_.clear();
recoMuIsoMatched_.clear();
recoMuGenMatched_.clear();
recoMuGenMatchDeltaPT_.clear();
recoMuGenMatchDeltaR_.clear();	
recoMuGenTauDecay_.clear();
genMuPt_.clear();
genMuEta_.clear();
genMuPhi_.clear();
genMuMtw_.clear();
genMuDeltaR_.clear();
genMuClosestJetPt_.clear();
isoElecPt_.clear();
isoElecEta_.clear();
isoElecPhi_.clear();
isoElecMtw_.clear();
isoElecDeltaR_.clear();
isoElecClosestJetPt_.clear();

// only temporary used not saved to tree
recoMuPtTemp_=0;
recoMuPhiTemp_=0;
recoMuEtaTemp_=0;
}


// ------------ method called once each job just before starting event loop  ------------
void 
RecoMuon::beginJob()
{
if(debug_) std::cout<<"RecoMuon::beginJob stared"<<std::endl;
if(debug_) std::cout<<"RecoMuon::List of all input values::"<<std::endl;
if(debug_) std::cout<<"RecoMuon::HtJetsTag_"<<HtJetsTag_<<std::endl;
if(debug_) std::cout<<"RecoMuon::MhtTag_"<<MhtTag_<<std::endl;
if(debug_) std::cout<<"RecoMuon::MetTag_"<<MetTag_<<std::endl;
if(debug_) std::cout<<"RecoMuon::CaloJetTag_"<<CaloJetTag_<<std::endl;
if(debug_) std::cout<<"RecoMuon::MuonIsoTag_"<<MuonIsoTag_<<std::endl;
if(debug_) std::cout<<"RecoMuon::MuonRecoTag_"<<MuonRecoTag_<<std::endl;
if(debug_) std::cout<<"RecoMuon::ElecIsoTag_"<<ElecIsoTag_<<std::endl;
if(debug_) std::cout<<"RecoMuon::evtWeightTag_"<<evtWeightTag_<<std::endl;
if(debug_) std::cout<<"RecoMuon::MTWMax_"<<MTWMax_<<std::endl;
if(debug_) std::cout<<"RecoMuon::MTWCut_"<<MTWCut_<<std::endl;
if(debug_) std::cout<<"RecoMuon::MinMuPT_"<<MinMuPT_<<std::endl;
if(debug_) std::cout<<"RecoMuon::MinElecPT_"<<MinElecPT_<<std::endl;
if(debug_) std::cout<<"RecoMuon::HTTag_"<<HTTag_<<std::endl;
if(debug_) std::cout<<"RecoMuon::MHTTag_"<<MHTTag_<<std::endl;
if(debug_) std::cout<<"RecoMuon::NVTag_"<<NVTag_<<std::endl;
if(debug_) std::cout<<"RecoMuon::debug_"<<debug_<<std::endl;

	// output file
    	edm::Service<TFileService> fs;
	tree_ = fs->make<TTree>("LostLeptonBkg","LostLeptonBkg");
    tree_->Branch("HT",&ht_,"HT/F");
    tree_->Branch("MHT",&mht_,"MHT/F");
    tree_->Branch("NJets",&nJets_,"NJets/s");
    tree_->Branch("Weight",&eventWeight_,"Weight/F");
    tree_->Branch("NVtx",&nV_,"NVtx/s");
    tree_->Branch("MTW",&mtw_,"MTW/F");
    tree_->Branch("MTWCut_",&MTWCut_,"MTWCut_/I");
    tree_->Branch("nIsoMu",&nIsoMu_,"nIsoMu/I");
    tree_->Branch("isoMuPt",&isoMuPt_);
    tree_->Branch("isoMuEta",&isoMuEta_);
    tree_->Branch("isoMuPhi",&isoMuPhi_);
    tree_->Branch("isoMuMtw",&isoMuMtw_);
    tree_->Branch("isoMuDeltaR",&isoMuDeltaR_);
    tree_->Branch("isoMuClosestJetPt",&isoMuClosestJetPt_);
    tree_->Branch("nRecoMu",&nRecoMu_,"nRecoMu/I");
    tree_->Branch("recoMuPt",&recoMuPt_);
    tree_->Branch("recoMuEta",&recoMuEta_);
    tree_->Branch("recoMuPhi",&recoMuPhi_);
    tree_->Branch("recoMuMtw",&recoMuMtw_);
    tree_->Branch("recoMuDeltaR",&recoMuDeltaR_);
    tree_->Branch("recoMuClosestJetPt",&recoMuClosestJetPt_);
    tree_->Branch("recoMuClosestJetRelPt",&recoMuClosestJetRelPt_);
    tree_->Branch("recoMuIsoMatched",&recoMuIsoMatched_);
    tree_->Branch("recoMuGenMatched",&recoMuGenMatched_);
    tree_->Branch("recoMuGenMatchDeltaPT",&recoMuGenMatchDeltaPT_);
    tree_->Branch("recoMuGenMatchDeltaR",&recoMuGenMatchDeltaR_);
    tree_->Branch("recoMuGenTauDecay",&recoMuGenTauDecay_);
    tree_->Branch("nGenMu",&nGenMu_,"nGenMu/I");
    tree_->Branch("genMuPt",&genMuPt_);
    tree_->Branch("genMuEta",&genMuEta_);
    tree_->Branch("genMuPhi",&genMuPhi_);
    tree_->Branch("nIsoElec",&nIsoElec_,"nIsoElec/I");
    tree_->Branch("isoElecPt",&isoElecPt_);
    tree_->Branch("isoElecEta",&isoElecEta_);
    tree_->Branch("isoElecPhi",&isoElecPhi_);
    tree_->Branch("isoElecMtw",&isoElecMtw_);
    tree_->Branch("isoElecDeltaR",&isoElecDeltaR_);
    tree_->Branch("isoElecClosestJetPt",&isoElecClosestJetPt_);

if(debug_) std::cout<<"RecoMuon::beginJob ended"<<std::endl;
}

// ------------ method called once each job just after ending the event loop  ------------
void 
RecoMuon::endJob() {
}

// ------------ method called when starting to processes a run  ------------
void 
RecoMuon::beginRun(edm::Run&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
RecoMuon::endRun(edm::Run&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
RecoMuon::beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
RecoMuon::endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
RecoMuon::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}
bool
	RecoMuon::MuTauDecayMatched(const reco::Candidate* tau)
{
	bool muonDecayMatched=false;
	for (unsigned int ii=0; ii < tau->numberOfDaughters(); ii++)
	{
		if (abs(tau->daughter(ii)->pdgId()) == 15 || abs(tau->daughter(ii)->pdgId()) == 24) muonDecayMatched=RecoMuon::MuTauDecayMatched(tau->daughter(ii));
		if (abs(tau->daughter(ii)->pdgId() ) == 13 && RecoMuon::Match(recoMuPtTemp_,recoMuEtaTemp_,recoMuPhiTemp_,tau->daughter(ii)->pt(),tau->daughter(ii)->eta(),tau->daughter(ii)->phi())) muonDecayMatched=true;
		if ( abs(tau->daughter(ii)->pdgId() ) == 13 )
		{
			genMuPt_.push_back(tau->daughter(ii)->pt());
			genMuEta_.push_back(tau->daughter(ii)->eta());
			genMuPhi_.push_back(tau->daughter(ii)->phi());
			recoMuGenTauDecay_.push_back(true);
			recoMuGenMatchDeltaPT_.push_back(abs(recoMuPtTemp_-tau->daughter(ii)->pt())/recoMuPtTemp_);
			recoMuGenMatchDeltaR_.push_back(deltaR(recoMuEtaTemp_,recoMuPhiTemp_,tau->daughter(ii)->eta(),tau->daughter(ii)->phi()));
		}
	}

	return muonDecayMatched;
}
bool
	RecoMuon::Match(float firstPT, float firstEta, float firstPhi, float secondPT, float secondEta, float secondPhi)
{
	bool result=false;
	if(debug_)std::cout<<"RecoMuon::Match::firstPT"<<firstPT<<std::endl;
	if(debug_)std::cout<<"RecoMuon::Match::firstEta"<<firstEta<<std::endl;
	if(debug_)std::cout<<"RecoMuon::Match::firstPhi"<<firstPhi<<std::endl;
	if(debug_)std::cout<<"RecoMuon::Match::secondPT"<<secondPT<<std::endl;
	if(debug_)std::cout<<"RecoMuon::Match::secondEta"<<secondEta<<std::endl;
	if(debug_)std::cout<<"RecoMuon::Match::secondPhi"<<secondPhi<<std::endl;
	if(debug_)std::cout<<"RecoMuon::Match::RelPT"<<abs(firstPT-secondPT)/firstPT<<std::endl;
	if(debug_)std::cout<<"RecoMuon::Match::DeltaR"<< deltaR(firstEta,firstPhi,secondEta,secondPhi)<<std::endl;
	if ( abs(firstPT-secondPT)/firstPT<0.2 && deltaR(firstEta,firstPhi,secondEta,secondPhi) <0.1) result=true;
	if(debug_)std::cout<<"RecoMuon::Match::result"<<result<<std::endl;
	return result;
}
//define this as a plug-in
DEFINE_FWK_MODULE(RecoMuon);
