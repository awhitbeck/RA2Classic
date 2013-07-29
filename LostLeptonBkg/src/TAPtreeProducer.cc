		// -*- C++ -*-
		//
		// Package:    TAPtreeProducer
		// Class:      TAPtreeProducer
		// 
		/**\class TAPtreeProducer TAPtreeProducer.cc RA2Classic/TAPtreeProducer/src/TAPtreeProducer.cc
		
		Description: [one line class summary]
		
		Implementation:
		[Notes on implementation]
		*/
		//
		// Original Author:  Arne-Rasmus Draeger,,,uni-hamburg
		//         Created:  Tue Sep 25 13:40:40 CEST 2012
		// $Id: TAPtreeProducer.cc,v 1.10 2013/02/15 10:53:34 adraeger Exp $
		//
		//
		#include <TMath.h>
		#include <DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h>
		#include "FWCore/Common/interface/TriggerNames.h"
		#include "FWCore/Common/interface/TriggerResultsByName.h"
		#include "DataFormats/Common/interface/TriggerResults.h"
		#include "DataFormats/HLTReco/interface/TriggerEvent.h"
		#include "DataFormats/HLTReco/interface/TriggerObject.h"
		#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"
		#include <TRandom2.h>
		#include <math.h>
		#include <TString.h>
		#include "RA2Classic/LostLeptonBkg/interface/TAPtreeProducer.h"
		#include "DataFormats/Math/interface/deltaPhi.h"
		#include <DataFormats/Math/interface/deltaR.h>
		#include <DataFormats/PatCandidates/interface/Jet.h>
		#include "RA2Classic/LostLeptonBkg/interface/MCEffCalculator.h"
		#include "DataFormats/EgammaReco/interface/SuperClusterFwd.h"
		#include <DataFormats/EgammaReco/interface/SuperCluster.h>
		#include "DataFormats/EgammaReco/interface/BasicClusterFwd.h"
		#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
		#include "DataFormats/EgammaCandidates/interface/Electron.h"
		#include "FWCore/Framework/interface/Event.h"
		#include "DataFormats/Common/interface/Handle.h"
		#include "DataFormats/Common/interface/View.h"
		#include "DataFormats/PatCandidates/interface/Muon.h"
		#include "DataFormats/VertexReco/interface/Vertex.h"
		// electrons
		#include <vector>
		#include "DataFormats/Common/interface/ValueMap.h"
		#include "DataFormats/RecoCandidate/interface/IsoDeposit.h"
		#include "DataFormats/VertexReco/interface/Vertex.h"
		#include "DataFormats/VertexReco/interface/VertexFwd.h"
		#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
		#include "DataFormats/EgammaCandidates/interface/GsfElectronFwd.h"
		#include "DataFormats/EgammaCandidates/interface/Conversion.h"
		#include "DataFormats/EgammaCandidates/interface/ConversionFwd.h"
		#include "RecoEgamma/EgammaTools/interface/ConversionTools.h"
		#include "DataFormats/GsfTrackReco/interface/GsfTrack.h"
		#include "DataFormats/RecoCandidate/interface/IsoDeposit.h"
		//#include "EGamma/EGammaAnalysisTools/interface/EGammaCutBasedEleId.h"
		#include "SandBox/Skims/plugins/ElectronEffectiveArea.h"
		//
		// constants, enums and typedefs
		//
		
		
		//
		// static data member definitions
		//
		
		//
		// constructors and destructor
		//
		typedef std::vector< edm::Handle< edm::ValueMap<reco::IsoDeposit> > >   IsoDepositMaps;
		typedef std::vector< edm::Handle< edm::ValueMap<double> > >             IsoDepositVals;
		typedef std::vector< edm::Handle< edm::ValueMap<reco::IsoDeposit> > >   IsoDepositMaps;
		typedef std::vector< edm::Handle< edm::ValueMap<double> > >             IsoDepositVals;
		TAPtreeProducer::TAPtreeProducer(const edm::ParameterSet& iConfig)
		{
		HtJetsTag_ = iConfig.getParameter<edm::InputTag>("HTJets");
		MhtTag_ = iConfig.getParameter<edm::InputTag>("MhtTag");
		MetTag_ = iConfig.getParameter<edm::InputTag>("MetTag");
		
		MuElecIdIso_ = iConfig.getParameter <unsigned int> ("MuElecIdIso");
		
		IsoMuonTag_ = iConfig.getParameter<edm::InputTag>("IsoMuonTag");
		IsoElecTag_ = iConfig.getParameter<edm::InputTag>("IsoElecTag");
		
		RecoMuonTag_ = iConfig.getParameter<edm::InputTag>("RecoMuonTag");
		RecoElecTag_ = iConfig.getParameter<edm::InputTag>("RecoElecTag");
		
		PromtMuonTag_ = iConfig.getParameter<edm::InputTag>("PromtMuonTag");
		PromtElecTag_ = iConfig.getParameter<edm::InputTag>("PromtElecTag");
		GsfElecTag_ = iConfig.getParameter<edm::InputTag>("GsfElecTag");
		
		evtWeightTag_ = iConfig.getParameter<edm::InputTag> ("EventWeightTag");
		CaloJetTag_ = iConfig.getParameter<edm::InputTag>("CaloJetTag");
		
		// input cuts
		MTWMax_ = iConfig.getParameter <double> ("MTWMax");
		MTWCut_ = iConfig.getParameter <bool> ("MTWCut");
		MinMuPT_ = iConfig.getParameter <double> ("MinMuPT");
		MinElecPT_ = iConfig.getParameter <double> ("MinElecPT");
		HTTag_ = iConfig.getParameter<edm::InputTag>("HTTag");
		MHTTag_ = iConfig.getParameter<edm::InputTag>("MHTTag");
		NVTag_ = iConfig.getParameter<edm::InputTag>("VertexCollection");
		
		// iso reco muon values
		muonSrc_     = iConfig.getParameter<edm::InputTag>("MuonSource");
		muonTrigger_  = iConfig.getParameter<std::string>("MuonTrigger");
		vtxSrc_      = iConfig.getParameter<edm::InputTag>("VertexSource");
		minMuPt_     = iConfig.getParameter<double>("MinMuPt");
		maxMuEta_    = iConfig.getParameter<double>("MaxMuEta");
		maxMuD0_     = iConfig.getParameter<double>("MaxMuD0");
		maxMuDz_     = iConfig.getParameter<double>("MaxMuDz");
		maxMuRelIso_ = iConfig.getParameter<double>("MaxMuRelIso");
		minMuNumHit_ = iConfig.getParameter<double>("MinMuNumHit");
		
		oldMethod_ = iConfig.getParameter<bool>("oldMethod");
		
		// electron iso reco values
		
		electronSrc_   = iConfig.getParameter<edm::InputTag>("ElectronSource");
		conversionsSrc_= iConfig.getParameter<edm::InputTag>("ConversionsSource");
		beamSpotSrc_   = iConfig.getParameter<edm::InputTag>("BeamSpotSource");
		rhoIsoSrc_     = iConfig.getParameter<edm::InputTag>("RhoIsoSource");
		isoValsSrc_    = iConfig.getParameter<std::vector<edm::InputTag> >("IsoValInputTags");
		minElePt_      = iConfig.getParameter<double>("MinElePt");
		maxEleEta_     = iConfig.getParameter<double>("MaxEleEta");
		
		// MC
		MC_  =iConfig.getParameter<bool>("MC");
		Muon_ =iConfig.getParameter<bool>("Muon");
		HLTTriggerTag_ = iConfig.getParameter<edm::InputTag>("HLTTriggerTag");
		HLTTriggerResultTag_ = iConfig.getParameter<edm::InputTag>("HLTTriggerResultTag");
		trgEvtObjTag_ = iConfig.getParameter<edm::InputTag> ("trgEvtObjTag");
		
		
		
		
		
		}
		
		
		TAPtreeProducer::~TAPtreeProducer()
		{
		
		// do anything here that needs to be done at desctruction time
		// (e.g. close files, deallocate resources etc.)
		
		}
		
		
		//
		// member functions
		//
		
		// ------------ method called to produce the data  ------------
		void
		TAPtreeProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
		{
		
		
		
		
		
		
		
		
		
		
		//std::cout<<"TAPtreeProducer::loopstarted"<<std::endl;
		//std::cout<<"TAPtreeProducer:EventLoopStarted"<<std::endl;
		using namespace edm;
		ResetValues();
		//	if (MC_)	std::cout<<"MC!"<<std::endl;
		//	else std::cout<<"Data!"<<std::endl;
		
		
		/*
		edm::Handle< edm::TriggerResults > hltresults;
		if( iEvent.getByLabel(edm::InputTag("TriggerResults::HLT"),hltresults) ) {
		const edm::TriggerNames & trigNames = iEvent.triggerNames(*hltresults);
		for(unsigned int itrig = 0; itrig != hltresults->size(); ++itrig) {
		std::string trigName = trigNames.triggerName(itrig);
			std::cout<<"TrigName="<<trigName<<std::endl;
		}	
		}
		*/
		
		edm::Handle< edm::View<reco::Candidate> > met;
		iEvent.getByLabel(MetTag_,met);
		if( met.isValid() ) {
		met_ = met->at(0).pt();
		}
		
		// up down for mt cut efficiency
		
		
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
		edm::Handle<reco::VertexCollection> vertices2;
		iEvent.getByLabel(NVTag_,vertices2);
		if( vertices2.isValid() ) 
		{
			nV_ = vertices2->size();
		}
		
		
		
		// trigger information
/*		std::string trigname("");
		edm::Handle<edm::TriggerResults> triggerResults;
		if (!iEvent.getByLabel(HLTTriggerResultTag_, triggerResults)) {
		cout << ">>> TRIGGER collection does not exist !!!" << endl;
		}
		const edm::TriggerNames & trigNames = iEvent.triggerNames(*triggerResults);
		for(unsigned int itrig = 0; itrig != triggerResults->size(); ++itrig) {
		std::string trigName = trigNames.triggerName(itrig);

			std::cout<<"TrigName="<<trigName<<std::endl;
			trigname=trigName;

		}	
		std::cout<<"TriggerNameStored:"<<trigname<<std::endl; 
*/
		size_t htflt(0);
		
		
		
		
		
		
		edm::Handle<trigger::TriggerEvent> trgEvtObj;
		if (!iEvent.getByLabel(trgEvtObjTag_, trgEvtObj)) {
			cout << ">>> TRIGGER event summary does not exist !!!" << endl;
		}
		
		const trigger::TriggerObjectCollection& toc(trgEvtObj->getObjects());
		
		//	std::string temp("::HLT");
		//      trigname+=temp;
	
		
	
		double triggerElecEta=0;
		double triggerElecPhi=0;
	if (!MC_)
		{
		htflt = trgEvtObj->filterIndex(HLTTriggerTag_);
		std::cout<<"htflt"<<htflt<<std::endl;
		std::cout<<"trgEvtObjFilterSize"<<trgEvtObj->sizeFilters()<<std::endl;

		if (htflt != trgEvtObj->sizeFilters()) {
			const trigger::Keys& htKey = trgEvtObj->filterKeys(htflt);
			for (trigger::Keys::const_iterator htkit = htKey.begin(); htkit != htKey.end(); htkit++) {
			std::cout<<"Trigger PT"<< toc[*htkit].pt()<<std::endl;
			noElecTriggered_=false;
			triggerElecEta=toc[*htkit].eta();
			triggerElecPhi=toc[*htkit].phi();
			}
		}
		else noElecTriggered_=true;
		}
		
		// Muon criteria
		edm::Handle <edm::View <reco::CaloJet> > caloJets;
		iEvent.getByLabel(CaloJetTag_, caloJets);
		
		edm::Handle<std::vector<pat::Muon> > muons;
		if (Muon_) iEvent.getByLabel(muonSrc_, muons);
		
		
		
		
		
		
		
		//  std::cout<<"Muon Trigger input name:"<<muonTrigger_<<std::endl;
		edm::Handle< std::vector<reco::Vertex> > vertices;
		iEvent.getByLabel(vtxSrc_, vertices);
		reco::Vertex::Point vtxpos = (vertices->size() > 0 ? (*vertices)[0].position() : reco::Vertex::Point());
		
		
		// electrons
		edm::Handle< std::vector<reco::GsfElectron> > electrons;   
		iEvent.getByLabel(electronSrc_, electrons);
		
		// conversions
		edm::Handle< std::vector<reco::Conversion> > conversions;
		iEvent.getByLabel(conversionsSrc_, conversions);
		
		// iso deposits
		IsoDepositVals isoVals(isoValsSrc_.size());
		for (size_t j = 0; j < isoValsSrc_.size(); ++j) {
		iEvent.getByLabel(isoValsSrc_[j], isoVals[j]);
		}
		
		// beam spot
		edm::Handle<reco::BeamSpot> beamspot;
		iEvent.getByLabel(beamSpotSrc_, beamspot);
		const reco::BeamSpot &beamSpot = *(beamspot.product());
		
		// rho for isolation                                                                                                
		edm::Handle<double> rhoIsoH;
		iEvent.getByLabel(rhoIsoSrc_, rhoIsoH);
		double rhoIso = *(rhoIsoH.product());
		
		
		float cut_dEtaIn[2]         = {999.9, 999.9};
		float cut_dPhiIn[2]         = {999.9, 999.9};
		float cut_sigmaIEtaIEta[2]  = {999.9, 999.9};
		float cut_hoe[2]            = {999.9, 999.9};
		float cut_ooemoop[2]        = {999.9, 999.9};
		float cut_d0vtx[2]          = {999.9, 999.9};
		float cut_dzvtx[2]          = {999.9, 999.9};
		float cut_iso[2]            = {999.9, 999.9};
		bool cut_vtxFit[2]          = {false, false};
		unsigned int cut_mHits[2]   = {999, 999};
		
		cut_dEtaIn[0]        = 0.007; cut_dEtaIn[1]        = 0.010;
		cut_dPhiIn[0]        = 0.800; cut_dPhiIn[1]        = 0.700;
		cut_sigmaIEtaIEta[0] = 0.010; cut_sigmaIEtaIEta[1] = 0.030;
		cut_hoe[0]           = 0.150; cut_hoe[1]           = 999.9;
		cut_ooemoop[0]       = 999.9; cut_ooemoop[1]       = 999.9;
		cut_d0vtx[0]         = 0.040; cut_d0vtx[1]         = 0.040;
		cut_dzvtx[0]         = 0.200; cut_dzvtx[1]         = 0.200;
		cut_vtxFit[0]        = false; cut_vtxFit[1]        = false;
		cut_mHits[0]         = 999  ; cut_mHits[1]         = 999;
		cut_iso[0]           = 0.150; cut_iso[1]           = 0.150;
		
		
		
		
		
		
		
		
		edm::Handle <edm::View <reco::Candidate> > IsoMu;
		iEvent.getByLabel(IsoMuonTag_,IsoMu);
		edm::Handle <edm::View <reco::Candidate> > IsoElec;
		iEvent.getByLabel(IsoElecTag_,IsoElec);
		
		edm::Handle <edm::View <reco::Candidate> > RecoMu;
		iEvent.getByLabel(RecoMuonTag_,RecoMu);
		edm::Handle <edm::View <reco::Candidate> > RecoElec;
		iEvent.getByLabel(RecoElecTag_,RecoElec);

		edm::Handle <edm::View <reco::Candidate> > PromtMu;
		iEvent.getByLabel(PromtMuonTag_,PromtMu);
		
		edm::Handle <reco::SuperClusterCollection >  PromtElec;
		iEvent.getByLabel(PromtElecTag_,PromtElec);

		
		edm::Handle <edm::View <reco::Candidate> >  GsfElec;
		iEvent.getByLabel(GsfElecTag_,GsfElec);

		
		
		if (!vertices.isValid() )
		{
			std::cout<<"Vertices is invalid!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
		}
		
		if (IsoMu.isValid() )
		{
			nIsoMu_=IsoMu->size();
		//	std::cout<<"nIsoMu_"<<nIsoMu_<<std::endl;
		}
		else std::cout<<"IsoMu Not valid!"<<std::endl;
		
		if (RecoMu.isValid() )
		{
			nRecoMu_=RecoMu->size();
		//	std::cout<<"nRecoMu_"<<nRecoMu_<<std::endl;
		}
		else std::cout<<"RecoMu Not valid!"<<std::endl;
		
		if (PromtMu.isValid() )
		{
			nPromtMu_=PromtMu->size();
		//	std::cout<<"nPromtMu_"<<nPromtMu_<<std::endl;
		}
		else std::cout<<"PromtMu Not valid!"<<std::endl;
		
		if (IsoElec.isValid() )
		{
			nIsoElec_=IsoElec->size();
		//	std::cout<<"nIsoElec_"<<nIsoElec_<<std::endl;
		}
		else std::cout<<"IsoElec Not valid!"<<std::endl;
		if (RecoElec.isValid() )
		{
			nRecoElec_=RecoElec->size();
		//	std::cout<<"nRecoElec_"<<nRecoElec_<<std::endl;
		}
		else std::cout<<"RecoElec Not valid!"<<std::endl;
		if (PromtElec.isValid() )
		{
			nPromtElec_=PromtElec->size();
		//	std::cout<<"nPromtElec_"<<nPromtElec_<<std::endl;
		}
		else std::cout<<"PromtElec Not valid!"<<std::endl;
		
		if (!GsfElec.isValid() )
		{
		std::cout<<"GsfElec not valid!!"<<std::endl;
		}
		
		
		
		
		
		// set up the result weight
		
		
		if (caloJets.isValid() )
		{//	std::cout<<"CaloJetsarevalid!"<<std::endl;
			nCaloJets_=caloJets->size();
		}
		else
			{
		//	std::cout<<"CaloJetsareinvalid!!!!!!!!!!!!!!!!!!"<<std::endl;
		//	std::cout<<"CaloJetsTag"<<CaloJetTag_<<std::endl;
			}
		
		
		// start the prediciton from Muon CS
		
		// loop over all reconstructed muons as tag muons for reconstruction eff
		
		//loop over all promtMu cands to find the tag muon
		//if(!oldMethod_)std::cout<<"Using the new method!"<<std::endl;
		//if(oldMethod_)std::cout<<"Using the old method!"<<std::endl;
	if (Muon_)
	{
	std::cout<<"MuonTrue, ";
		// true if the new method should be used for muons
		if ( (!oldMethod_ && MuElecIdIso_ == 0) || (!oldMethod_ && MuElecIdIso_ == 1) )
		{
			std::cout<<"newVersionStarted, ";
			vector<int> muTagReco;
			muTagReco.clear();
		
			vector<int> muTagIso;
			muTagIso.clear();
		
			vector<int> muProbeReco;
			muProbeReco.clear();
		
			vector<int> muProbeIso;
			muProbeIso.clear();
			
			int muPromtCandCounter =0;
			int muPromtCandCounter2 =0;
		
			vector<int> inputMu;
			inputMu.clear();
			unsigned int muSize= muons->size();
		

			int indexx=0;
			bool skipx=false;
			bool onlyOneTriggered=false;
			bool matchedMu=false;
			double triggerEta=0;
			double triggerPt=0;
			double triggerPhi=0;
			if (!MC_)
			{
			std::cout<<"NoMC, ";
				for (unsigned int i=0; i<muons->size();i++)
				{
		
					pat::MuonRef m(muons, i);
					vector <pat::TriggerObjectStandAlone> muTrigger =m->triggerObjectMatchesByPath(muonTrigger_);
					for (unsigned int ii=0; ii<muTrigger.size(); ii++)
					{
						if (muTrigger[ii].hasCollection("hltL3MuonCandidates") ) 
						{
							matchedMu=true;
		//					if (muTrigger[ii].hasCollection("hltMuTrackJpsiCtfTrackCands") ) std::cout<<"matchedTrack"<<std::endl;	
							triggerEta=muTrigger[ii].eta();
							triggerPt=muTrigger[ii].pt();
							triggerPhi=muTrigger[ii].phi();
						}
					}
				}
			}
		

		
		
		
		/*  USED THIS FOR RANDOM TAG MUON SELECTION 
		for (unsigned int in=0;inputMu.size()<muSize; ++in)
		{
			unsigned int temp = muSize;
		TRandom2 * random = new TRandom2(0);
			indexx = (int) random->Uniform(temp);
		//	std::cout<<"random"<<indexx<<std::endl;
		//	std::cout<<"skipx"<<skipx<<std::endl;
		
		
			for (unsigned int ii=0; (inputMu.size())>ii; ii++)
			{
				if (inputMu[ii]== indexx) skipx=true;
				else skipx=false;
		//		std::cout<<"index"<<index<<std::endl;
		//		std::cout<<"inputElec["<<ii<<"]:"<<inputElec[ii]<<std::endl;
			}
		//	std::cout<<"skipx"<<skipx<<std::endl;
		
		if (!skipx || inputMu.size()==0) inputMu.push_back(indexx);
		//	std::cout<<"inputMu.size()"<<inputMu.size()<<", muSize"<<muSize<<std::endl;
		if (skipx) continue;
		
		*/
		// check if one muon has been found in the trigger menu or if MC is being used
			if (matchedMu || MC_)
			{

				for (unsigned int i=0; i<muons->size();i++)
				{
					if (MC_)
					{
				std::cout<<"MCTrue, ";
						for (unsigned int in=0;inputMu.size()<muSize; ++in)
						{
							unsigned int temp = muSize;
							TRandom2 * random = new TRandom2(0);
							indexx = (int) random->Uniform(temp);	
				std::cout<<"Random:"<<indexx<<", ";
		
							for (unsigned int ii=0; (inputMu.size())>ii; ii++)
							{
								if (inputMu[ii]== indexx) skipx=true;
								else skipx=false;
							}
	
		
							if (!skipx || inputMu.size()==0) inputMu.push_back(indexx);
							//	std::cout<<"inputMu.size()"<<inputMu.size()<<", muSize"<<muSize<<std::endl;
						}
					}
					if (skipx) continue;
					int iMu=i;
					if (!skipx && MC_) iMu=indexx;
					pat::MuonRef m(muons, iMu);
					if (!MC_)
					{
							std::cout<<"MCTrue, ";
						if (deltaR(triggerEta,triggerPhi,m->eta(),m->phi() ) >0.03 ) continue;
						else std::cout<<"Muon MATCHED FROM TRIGGER TO RECO COLLECTION"<<std::endl;
		
					}
		
					muPromtCandCounter2=0;
					muPromtCandCounter++;
					bool tagIso=false;
		
					bool alreadyProbeRecoMu=false;
					for (unsigned int l=0; l <  muProbeReco.size(); l++)
					{
						if (muProbeReco[l] == muPromtCandCounter) alreadyProbeRecoMu=true;
					}
					if (alreadyProbeRecoMu) continue;
		
					bool alreadyProbeIsoMu=false;
					for (unsigned int l=0; l < muProbeIso.size(); l++)
					{
						if (muProbeIso[l] == muPromtCandCounter) alreadyProbeIsoMu=true;
					}
					// acceptance cuts
					if (m->pt() < minMuPt_) continue;
					if (std::abs(m->eta()) >= maxMuEta_) continue;
		
		
					// ID cuts - always ask isGlobalMuon()
					if (m->muonID("AllGlobalMuons") == 0) continue;
		
					if(!m->isPFMuon() ) continue; 
					if( m->globalTrack()->normalizedChi2() >= 10. ) continue;
					if( m->globalTrack()->hitPattern().numberOfValidMuonHits() <=0 ) continue;
					if( m->numberOfMatchedStations() <=1 ) continue;
					if( m->innerTrack()->hitPattern().numberOfValidPixelHits() == 0) continue;
					if( m->innerTrack()->hitPattern().trackerLayersWithMeasurement() <=5 ) continue;
					// vertex association cuts - ignore if no vertex (see further)
		
					if (std::abs(m->innerTrack()->dxy(vtxpos)) >= maxMuD0_ && vertices->size() > 0) continue;
					if (std::abs(m->innerTrack()->dz(vtxpos))  >= maxMuDz_ && vertices->size() > 0) continue;
		
					//here only RA2 reconstructed muons should end up
		
					// store the number of this event 
					muTagReco.push_back(muPromtCandCounter);
		
					double tagPt = m->pt();
					double tagPhi = m->phi();
					double tagEta = m->eta();
					double tagE = m->energy();
					double tagPx = m->px();
					double tagPy = m->py();
					double tagPz = m->pz();
					tagCharge_ = m->charge();
					TLorentzVector TagLorentzReco(tagPx, tagPy, tagPz, tagE);
					float muRelIso = -1;
					muRelIso = (m->pfIsolationR04().sumChargedHadronPt + std::max(0., m->pfIsolationR04().sumNeutralHadronEt + m->pfIsolationR04().sumPhotonEt - 0.5*m->pfIsolationR04().sumPUPt) )/ m->pt();
					// true if mu is isolatedcontinue
					if (maxMuRelIso_ >= muRelIso )
					{
						TLorentzVector TagLorentzIso(tagPx, tagPy, tagPz, tagE);
						tagIso=true;
						muTagIso.push_back(muPromtCandCounter);
					}
		
					for (std::vector<pat::Muon>::const_iterator m2 = muons->begin(); m2 != muons->end(); ++m2) 
					{
						MuIdPass_=false;
						MuIsoPass_=false;
						muPromtCandCounter++;
						// loop over all used reco tag muons to make sure they are not being used twice
						bool alreadyTagRecoMu=false;
						for (unsigned int l=0; l < muTagReco.size(); l++)
						{
							if (muTagReco[l] == muPromtCandCounter2) alreadyTagRecoMu=true;
						}
						if (alreadyTagRecoMu)continue;
						double probeE = m2->energy();
						double probePx = m2->px();
						double probePy = m2->py();
						double probePz = m2->pz();
						TLorentzVector ProbeLorentzReco(probePx, probePy, probePz, probeE);
						TLorentzVector vreco;
						vreco = TagLorentzReco + ProbeLorentzReco;
						RecoMuInvariantMass_ = vreco.M();
						if ( vreco.M()<120 && vreco.M()>60 && (tagCharge_ != m2->charge()) ) 
						{
							RecoMuInvariantMass_ = vreco.M();
							IsoMuInvariantMass_ =RecoMuInvariantMass_;
							MuIdProbePt_=m2->pt();
							MuIsoProbePt_=MuIdProbePt_;
							MuIdProbeEta_=m2->eta();
							MuIsoProbeEta_=MuIdProbeEta_;
							MuIdProbePhi_=m2->phi();
							MuIsoProbePhi_=MuIdProbePhi_;
							MuIdProbeCharge_ = m2->charge();
							MuIsoProbeCharge_ = m2->charge();
							MuIdRelPT30GeVJet_ = MuIdProbePt_/TAPtreeProducer::DRToClosestJet(iEvent, CaloJetTag_,m2->eta(),m2->phi()).second;
							MuIsoRelPT30GeVJet_=MuIdRelPT30GeVJet_;
							MuIdDeltaR30GeVJet_ = TAPtreeProducer::DRToClosestJet(iEvent, CaloJetTag_,m2->eta(),m2->phi()).first;
							MuIsoDeltaR30GeVJet_=MuIdDeltaR30GeVJet_;
		
							// check if this muon fullfils the ra2 mu reco condidtions
							if ( 	!(m2->pt() < minMuPt_) &&
								!(std::abs(m2->eta()) >= maxMuEta_) && 
								!(m2->muonID("AllGlobalMuons") == 0) &&
								m2->isPFMuon() &&
								!( m2->globalTrack()->normalizedChi2() >= 10. ) &&
								!( m2->globalTrack()->hitPattern().numberOfValidMuonHits() <=0 ) &&
								!( m2->numberOfMatchedStations() <=1 ) &&
								!( m2->innerTrack()->hitPattern().numberOfValidPixelHits() == 0) &&
								!( m2->innerTrack()->hitPattern().trackerLayersWithMeasurement() <=5 ) &&
								!(std::abs(m2->innerTrack()->dxy(vtxpos)) >= maxMuD0_ && vertices->size() > 0) &&
								!(std::abs(m2->innerTrack()->dz(vtxpos))  >= maxMuDz_ && vertices->size() > 0)
							    )	
							{	
								muProbeReco.push_back(muPromtCandCounter2);
								MuIdPass_=true;
								// check if also iso is fullfied
								float muRelIso2 = -1;
								muRelIso2 = (m2->pfIsolationR04().sumChargedHadronPt + std::max(0., m2->pfIsolationR04().sumNeutralHadronEt + m2->pfIsolationR04().sumPhotonEt - 0.5*m2->pfIsolationR04().sumPUPt) )/ m2->pt();
								// true if mu is isolated
								if (maxMuRelIso_ >= muRelIso2  && tagIso)
								{
									muProbeIso.push_back(muPromtCandCounter2);
									TLorentzVector ProbeLorentzIso(tagPx, tagPy, tagPz, tagE);
									MuIsoPass_=true;
								}
		
							}
		
							//std::cout<<"MuRecoPassDoneFill!:"<<muPromtCandCounter<<std::endl;
								// true if the ID is being tested
							if (MuElecIdIso_==0 && vertices->size() > 0) tree_->Fill();
		
							// check if the tag iso muon is the same as the prob muon true if both are isolated and if the isolated probe muon has been used before as isolated probe muon
							bool alreadyTagIsoMu=false;
							for (unsigned int l=0; l < muTagIso.size(); l++)
							{
								if (muTagIso[l] == muPromtCandCounter2) alreadyTagIsoMu=true;
							}
							if (MuElecIdIso_==1 && MuIdPass_ && tagIso && vertices->size() > 0 && !alreadyTagIsoMu && !alreadyProbeIsoMu) tree_->Fill();
						}
					}
				}
			}
		}
						std::cout<<"MuonDone"<<std::endl;
	}

		// electron 
		
		if (!Muon_)
		{
				std::cout<<"ElectronStarted, ";
		if ( (!oldMethod_ && MuElecIdIso_ == 3) || (!oldMethod_ && MuElecIdIso_ == 4) )
		{
		
						std::cout<<"NewMethod, ";
		
		
		
		//  std::cout<<"EventLoopElecStarted("<<MuElecIdIso_<<")!!"<<std::endl;
		int elecPromtCandCounter =0;
		int elecPromtCandCounter2 =0;
		
		vector<int> elecTagReco;
		elecTagReco.clear();
		
		vector<int> elecTagIso;
		elecTagIso.clear();
		
		vector<int> elecProbeReco;
		elecProbeReco.clear();
		
		vector<int> elecProbeIso;
		elecProbeIso.clear();
		
		
		vector<int> inputElec;
		inputElec.clear();
		unsigned int electronSize= electrons->size();
		unsigned int elecSize=electrons->size();
		
		
		int index=0;
		unsigned int triggerElecIndex=0;
		bool skip=false;
		bool onlyOneTriggered=false;
		bool matchedElec=false;
		if (!MC_)
		{
						std::cout<<"NoMC, ";
			for (unsigned int i=0; i<electrons->size();i++)
			{
				reco::GsfElectronRef ele(electrons,i);
				if (deltaR(triggerElecEta,triggerElecPhi,ele->eta(),ele->phi() ) <0.03)
				{
					triggerElecIndex=i;
					matchedElec=true;
				}
			}
		}
		
		if (matchedElec || MC_)
		{
		std::cout<<"MCTrueOrMatchedElec, ";
			for (unsigned int i=0; i < electrons->size();i++)
			{
				if (MC_)
				{
				std::cout<<"MCTrue, ";
					for (unsigned int in=0; inputElec.size()<elecSize; in++)
					{
						unsigned int temp =elecSize;
						TRandom2 * random = new TRandom2(0);
						index = (int) random->Uniform(temp);
					std::cout<<"randomNumber:"<<index<<", ";
						for (unsigned int ii=0; inputElec.size()>ii; ii++)
						{
							if (inputElec[ii]== index) skip=true;
							else skip=false;
						}
						if (!skip || inputElec.size()==0) inputElec.push_back(index);
						
					}
				}
				if (skip) continue;
				int iElec=i;
				if (!skip && MC_) iElec=index;
				reco::GsfElectronRef ele(electrons,i);
				if (!MC_)
				{
							std::cout<<"NoMC(triggerMatchIsBeingDone, ";
					if (deltaR(triggerElecEta,triggerElecPhi,ele->eta(),ele->phi() ) >0.05 ) continue;
					else std::cout<<"Elec MATCHED FROM TRIGGER TO RECO COLLECTION"<<std::endl;
				}
	
	
		elecPromtCandCounter2=0;
		elecPromtCandCounter++;
	
		
			// check if the electron has been used previously as probe iso or reco
			bool alreadyProbeRecoElec=false;
			for (unsigned int l=0; l < elecProbeReco.size(); l++)
			{
				if (elecProbeReco[l] == elecPromtCandCounter) alreadyProbeRecoElec=true;
			}
			if (alreadyProbeRecoElec) continue;
		
			bool alreadyProbeIsoElec=false;
			for (unsigned int l=0; l < elecProbeIso.size(); l++)
			{
				if (elecProbeIso[l] == elecPromtCandCounter) alreadyProbeIsoElec=true;
			}
		
		
			bool tagIso=false;
		// get reference to electron
	
		
		double pt = ele->pt();
		if (ele->pt() < minElePt_) continue;
		
		
		// get particle flow isolation
		double iso_ch = (*(isoVals)[0])[ele];
		double iso_em = (*(isoVals)[1])[ele];
		double iso_nh = (*(isoVals)[2])[ele];
		
		// working points
		//bool veto       = EgammaCutBasedEleId::PassWP(EgammaCutBasedEleId::VETO, ele, conversions, beamSpot, vertices, iso_ch, iso_em, iso_nh, rhoIso);
		
		// get the ID variables from the electron object
		// kinematic variables
		bool isEB           = ele->isEB() ? true : false;
		float eta           = ele->superCluster()->eta();
		
		// id variables
		float dEtaIn        = ele->deltaEtaSuperClusterTrackAtVtx();
		float dPhiIn        = ele->deltaPhiSuperClusterTrackAtVtx();
		float sigmaIEtaIEta = ele->sigmaIetaIeta();
		float hoe           = ele->hadronicOverEm();
		float ooemoop       = (1.0/ele->ecalEnergy() - ele->eSuperClusterOverP()/ele->ecalEnergy());
		
		// impact parameter variables
		float d0vtx         = 0.0;
		float dzvtx         = 0.0;
		if (vertices->size() > 0) 
			{
			reco::VertexRef vtx(vertices, 0);    
			d0vtx = ele->gsfTrack()->dxy(vtx->position());
			dzvtx = ele->gsfTrack()->dz(vtx->position());
			} 
			else 
			{
			d0vtx = ele->gsfTrack()->dxy();
			dzvtx = ele->gsfTrack()->dz();
			}
		
		// conversion rejection variables
		bool vtxFitConversion = ConversionTools::hasMatchedConversion( *ele, conversions, beamSpot.position());
		float mHits = ele->gsfTrack()->trackerExpectedHitsInner().numberOfHits(); 
		
		// choose cut if barrel or endcap
		unsigned int idx = isEB ? 0 : 1;
		
		// test cuts
		if (fabs(dEtaIn) > cut_dEtaIn[idx])             continue;
		if (fabs(dPhiIn) > cut_dPhiIn[idx])             continue;
		if (sigmaIEtaIEta > cut_sigmaIEtaIEta[idx])     continue;
		if (hoe > cut_hoe[idx])                         continue;
		if (fabs(ooemoop) > cut_ooemoop[idx])           continue;
		if (fabs(d0vtx) > cut_d0vtx[idx])               continue;
		if (fabs(dzvtx) > cut_dzvtx[idx])               continue;
		//if (!cut_vtxFit[idx] || !vtxFitConversion)      mask |= VTXFIT;
		if (mHits > cut_mHits[idx])                     continue;
		
		
		// electron is reconstructed
			elecTagReco.push_back(elecPromtCandCounter);
			double tagPt = ele->pt();
			double tagPhi = ele->phi();
			double tagEta = ele->eta();
			double tagE = ele->energy();
			double tagPx = ele->px();
			double tagPy = ele->py();
			double tagPz = ele->pz();
			tagCharge_=ele->charge();
			TLorentzVector TagLorentzReco(tagPx, tagPy, tagPz, tagE);
		// isolation cuts                                                                                                                                        
		
		
		// effective area for isolation
		float AEff = ElectronEffectiveArea::GetElectronEffectiveArea(ElectronEffectiveArea::kEleGammaAndNeutralHadronIso03, eta, ElectronEffectiveArea::kEleEAData2012);
		
		// apply to neutrals
		double rhoPrime = std::max(rhoIso, 0.0);
		double iso_n = std::max(iso_nh + iso_em - rhoPrime * AEff, 0.0);
		
		// compute final isolation
		double iso = (iso_n + iso_ch)/pt;
		
		
		// true if elec isolated
			if(iso < cut_iso[idx]) 
			{
				elecTagIso.push_back(elecPromtCandCounter);
				TLorentzVector TagLorentzIso(tagPx, tagPy, tagPz, tagE);
				tagIso=true;
			}
		
			for(unsigned int ii = 0; ii < electrons->size(); ++ii) 
			{
				reco::GsfElectronRef ele2(electrons, ii);
				ElecIdPass_=false;
				ElecIsoPass_=false;
				elecPromtCandCounter2++;
				bool alreadyTagRecoElec=false;
				for (unsigned int l=0; l < elecTagReco.size(); l++)
				{
				if (elecTagReco[l] == elecPromtCandCounter2) alreadyTagRecoElec=true;
				}
				if (alreadyTagRecoElec)continue;
		
			
				double probeE = ele2->energy();
				double probePx = ele2->px();
				double probePy = ele2->py();
				double probePz = ele2->pz();
				TLorentzVector ProbeLorentzReco(probePx, probePy, probePz, probeE);
				TLorentzVector vreco;
				vreco = TagLorentzReco + ProbeLorentzReco;
				RecoGsfElecInvariantMass_ = vreco.M();
				if ( vreco.M()<120 && vreco.M()>60 && (tagCharge_!=ele2->charge() ) ) 
				{
					RecoGsfElecInvariantMass_ = vreco.M();
					IsoElecInvariantMass_ =RecoGsfElecInvariantMass_;
					ElecIdGsfProbePt_=ele2->pt();
					ElecIsoProbePt_=ElecIdGsfProbePt_;
					ElecIdGsfProbeEta_=ele2->eta();
					ElecIsoProbeEta_=ElecIdGsfProbeEta_;
					ElecIdGsfProbePhi_=ele2->phi();
					ElecIsoProbePhi_=ElecIdGsfProbePhi_;
					ElecIsoCharge_=ele2->charge();
					ElecIdGsfCharge_=ele2->charge();
					ElecIdGsfRelPT30GeVJet_ = ElecIdGsfProbePt_/TAPtreeProducer::DRToClosestJet(iEvent, CaloJetTag_,ele2->eta(),ele2->phi()).second;
					ElecIsoRelPT30GeVJet_=ElecIdGsfRelPT30GeVJet_;
					ElecIdGsfDeltaR30GeVJet_ = TAPtreeProducer::DRToClosestJet(iEvent, CaloJetTag_,ele2->eta(),ele2->phi()).first;
					ElecIsoDeltaR30GeVJet_=ElecIdGsfDeltaR30GeVJet_;
		
					// check if the tag electron fullfils the  ra2 elec reco definitions
					double pt2 = ele2->pt();
					double probeReco=true;
					if (ele2->pt() < minElePt_) probeReco=false;
		
					// get particle flow isolation
					double iso_ch2 = (*(isoVals)[0])[ele2];
					double iso_em2 = (*(isoVals)[1])[ele2];
					double iso_nh2 = (*(isoVals)[2])[ele2];
			
					bool isEB2           = ele2->isEB() ? true : false;
					float eta2           = ele2->superCluster()->eta();
		
					// id variables
					float dEtaIn2        = ele2->deltaEtaSuperClusterTrackAtVtx();
					float dPhiIn2        = ele2->deltaPhiSuperClusterTrackAtVtx();
					float sigmaIEtaIEta2 = ele2->sigmaIetaIeta();
					float hoe2           = ele2->hadronicOverEm();
					float ooemoop2       = (1.0/ele2->ecalEnergy() - ele2->eSuperClusterOverP()/ele2->ecalEnergy());
		
					// impact parameter variables
					float d0vtx2         = 0.0;
					float dzvtx2         = 0.0;
					if (vertices->size() > 0) 
					{
						reco::VertexRef vtx2(vertices, 0);    
						d0vtx2 = ele2->gsfTrack()->dxy(vtx2->position());
						dzvtx2 = ele2->gsfTrack()->dz(vtx2->position());
					} 
					else 
					{
						d0vtx2 = ele2->gsfTrack()->dxy();
						dzvtx2 = ele2->gsfTrack()->dz();
					}
		
					// conversion rejection variables
					bool vtxFitConversion2 = ConversionTools::hasMatchedConversion( *ele2, conversions, beamSpot.position());
					float mHits2 = ele2->gsfTrack()->trackerExpectedHitsInner().numberOfHits(); 
		
					// choose cut if barrel or endcap
					unsigned int idx2 = isEB ? 0 : 1;
		
					// test cuts
					if (fabs(dEtaIn2) > cut_dEtaIn[idx2])             probeReco=false;
					if (fabs(dPhiIn2) > cut_dPhiIn[idx2])             probeReco=false;
					if (sigmaIEtaIEta2 > cut_sigmaIEtaIEta[idx2])     probeReco=false;
					if (hoe2 > cut_hoe[idx2])                         probeReco=false;
					if (fabs(ooemoop2) > cut_ooemoop[idx2])           probeReco=false;
					if (fabs(d0vtx2) > cut_d0vtx[idx2])               probeReco=false;
					if (fabs(dzvtx2) > cut_dzvtx[idx2])               probeReco=false;
					//if (!cut_vtxFit[idx] || !vtxFitConversion)      mask |= VTXFIT;
					if (mHits2 > cut_mHits[idx2])                     probeReco=false;
		
						// true if the probe elec has been reconstructed with ra2 criteria
					if (probeReco	)
					{	
						elecProbeReco.push_back(elecPromtCandCounter2);
						ElecIdGsfPass_=true;
						// check if tag elec also fullfils the isolation criteria
						// effective area for isolation
						float AEff2 = ElectronEffectiveArea::GetElectronEffectiveArea(ElectronEffectiveArea::kEleGammaAndNeutralHadronIso03, eta2, ElectronEffectiveArea::kEleEAData2012);
		
						// apply to neutrals
						double rhoPrime2 = std::max(rhoIso, 0.0);
						double iso_n2 = std::max(iso_nh2 + iso_em2 - rhoPrime2 * AEff2, 0.0);
		
						// compute final isolation
						double iso2 = (iso_n2 + iso_ch2)/pt2;
		
		
						// true if probe elec isolated
						if(iso2 < cut_iso[idx2]) 
						{
							elecProbeIso.push_back(elecPromtCandCounter2);
							TLorentzVector TagLorentzIso(probePx, probePy, probePz, probeE);
							ElecIsoPass_= true;
						}
			
					}
		//			std::cout<<"Elec Iso Reco  now filling Loop ended";
		//			std::cout<<"MuElecIdIso_"<<MuElecIdIso_<<", vertices size"<<vertices->size()<<", tagIso"<<tagIso<<", ElecIdGsfPass_"<<ElecIdGsfPass_<<std::endl;
					if (MuElecIdIso_==4 && vertices->size() > 0) 
					{
						std::cout<<"ElecRecoFillTree"<<std::endl;
						tree_->Fill();
					}
					// check if the probe iso muon has alkready been used as tag iso muon return true if so
					bool alreadyTagIsoElec=false;
					for (unsigned int l=0; l < elecTagIso.size(); l++)
					{
						if (elecTagIso[l] == elecPromtCandCounter2) alreadyTagIsoElec=true;
					}
		
					if (MuElecIdIso_==3 && ElecIdGsfPass_ && tagIso && vertices->size() > 0 && !alreadyTagIsoElec && !alreadyProbeIsoElec) 
					{
		//				std::cout<<"ElecIsoFillTree"<<std::endl;
						tree_->Fill();
					}
				}
			// get reference to electron
			}
		
		
		// electron is ID'd and isolated! - only accept if vertex present
		
		
		}
		
		
		//std::cout<<"electronSize"<<electronSize<<std::endl;
		//for (unsigned int iii=0;iii<inputElec.size();iii++)
		//{
		//std::cout<<"inputElec"<<inputElec[iii]<<",";
		
		//}
		//std::cout<<std::endl;
		
		
		}
		
		}
		std::cout<<"ElecDone"<<std::endl;
		}

		if (oldMethod_)
		{
		std::cout<<"OLDMETHODSTARTED!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
		for (edm::View <reco::Candidate>::const_iterator MuIDCand = RecoMu->begin(); MuIDCand!=RecoMu->end();MuIDCand++ )
		{	
			if(MuIdPairFound_) continue;
			double tagPt = MuIDCand->pt();
			double tagPhi = MuIDCand->phi();
			double tagEta = MuIDCand->eta();
			double tagE = MuIDCand->energy();
			double tagPx = MuIDCand->px();
			double tagPy = MuIDCand->py();
			double tagPz = MuIDCand->pz();
			TLorentzVector TagLorentz(tagPx, tagPy, tagPz, tagE);
			
			// search for probe muon from PromtMu collection for reconstruction
			for(edm::View <reco::Candidate>::const_iterator MuPromtCand = PromtMu->begin(); MuPromtCand!=PromtMu->end();MuPromtCand++ )
			{
				if (deltaPTMuRecoClosestLep_> abs(tagPt - MuPromtCand->pt() ) )
				{
					deltaPTMuRecoClosestLep_=abs(tagPt - MuPromtCand->pt() );
					deltaRMuRecoClosestLep_ = deltaR(tagEta,tagPhi,MuPromtCand->eta(),MuPromtCand->phi());
				}
				// if the tag is the probe muon skip the probe muon
				if ( deltaR(tagEta,tagPhi,MuPromtCand->eta(),MuPromtCand->phi())<0.05 &&abs(tagPt - MuPromtCand->pt() )/tagPt <0.05) 
				{
				continue;
		//		std::cout<<"the tag reconstructed muon is the probe promtMu muon skippt"<<std::endl;
				}
		//		std::cout<<"The tag reconstructed muon is not the probe continue"<<std::endl;
				double probeE = MuPromtCand->energy();
				double probePx = MuPromtCand->px();
				double probePy = MuPromtCand->py();
				double probePz = MuPromtCand->pz();
				TLorentzVector ProbeLorentz(probePx, probePy, probePz, probeE);
				TLorentzVector v1;
				v1 = TagLorentz + ProbeLorentz;
				RecoMuInvariantMass_ = v1.M();
				MuIdPairFound_=true;
				if ( v1.M()<120 && v1.M()>60 && !MuIdPass_) 
				{
				RecoMuInvariantMass_ = v1.M();
				MuIdProbePt_=MuPromtCand->pt();
				MuIdProbeEta_=MuPromtCand->eta();
				MuIdProbePhi_=MuPromtCand->phi();
				MuIdRelPT30GeVJet_ = MuIdProbePt_/TAPtreeProducer::DRToClosestJet(iEvent, CaloJetTag_,MuPromtCand->eta(),MuPromtCand->phi()).second;
				MuIdDeltaR30GeVJet_ = TAPtreeProducer::DRToClosestJet(iEvent, CaloJetTag_,MuPromtCand->eta(),MuPromtCand->phi()).first;
		//		std::cout<<"ProduceMuIdDeltaR30GeVJet_"<<MuIdDeltaR30GeVJet_<<std::endl;
				// loop over all Id muons to see if the probe muon can be matched to a Id muon
				for (edm::View <reco::Candidate>::const_iterator MuIDCand2 = RecoMu->begin(); MuIDCand2!=RecoMu->end();MuIDCand2++)
				{
					if (deltaR(MuIDCand2->eta(),MuIDCand2->phi(),MuPromtCand->eta(),MuPromtCand->phi())<0.05 && abs(MuIDCand2->pt()-MuPromtCand->pt())/MuIDCand2->pt()<0.2 ) MuIdPass_=true;
				}
				}
				
		//		std::cout<<"Invariant mass"<<v1.M();
				
				
			}
		
		}
		
		
		
		
		
		
		
		
		
		// loop over all isolated muons as tag muons for isolated eff
		for (edm::View <reco::Candidate>::const_iterator MuISOCand = IsoMu->begin(); MuISOCand!=IsoMu->end();MuISOCand++ )
		{	
			if(MuIsoPairFound_) continue;
			double tagPt = MuISOCand->pt();
			double tagPhi = MuISOCand->phi();
			double tagEta = MuISOCand->eta();
			double tagE = MuISOCand->energy();
			double tagPx = MuISOCand->px();
			double tagPy = MuISOCand->py();
			double tagPz = MuISOCand->pz();
			TLorentzVector TagLorentz(tagPx, tagPy, tagPz, tagE);
			
			// search for probe muon from RecoMu collection for reconstruction
			for(edm::View <reco::Candidate>::const_iterator MuRecoCand = RecoMu->begin(); MuRecoCand!=RecoMu->end();MuRecoCand++ )
			{
				if (deltaPTMuIsoClosestLep_> abs(tagPt - MuRecoCand->pt() ) )
				{
					deltaPTMuIsoClosestLep_=abs(tagPt - MuRecoCand->pt() );
					deltaRMuIsoClosestLep_ = deltaR(tagEta,tagPhi,MuRecoCand->eta(),MuRecoCand->phi());
				}
				// if the tag is the probe muon skip the probe muon
				if ( deltaR(tagEta,tagPhi,MuRecoCand->eta(),MuRecoCand->phi())<0.05 && abs(tagPt - MuRecoCand->pt() )/tagPt <0.05 ) continue;
				double probeE = MuRecoCand->energy();
				double probePx = MuRecoCand->px();
				double probePy = MuRecoCand->py();
				double probePz = MuRecoCand->pz();
				TLorentzVector ProbeLorentz(probePx, probePy, probePz, probeE);
				TLorentzVector v1;
		
				v1 = TagLorentz + ProbeLorentz;
				MuIsoPairFound_=true;
				IsoMuInvariantMass_ = v1.M();
				if ( v1.M()<120 && v1.M()>60 && !MuIsoPass_) 
				{
				IsoMuInvariantMass_ = v1.M();
				MuIsoProbePt_=MuRecoCand->pt();
				MuIsoProbeEta_=MuRecoCand->eta();
				MuIsoProbePhi_=MuRecoCand->phi();
				MuIsoRelPT30GeVJet_ = MuIsoProbePt_/TAPtreeProducer::DRToClosestJet(iEvent, CaloJetTag_,MuRecoCand->eta(),MuRecoCand->phi()).second;
				MuIsoDeltaR30GeVJet_ = TAPtreeProducer::DRToClosestJet(iEvent, CaloJetTag_,MuRecoCand->eta(),MuRecoCand->phi()).first;
				std::cout<<"ProduceMuIsoDeltaR30GeVJet_"<<MuIsoDeltaR30GeVJet_<<std::endl;
				// loop over all Id muons to see if the probe muon can be matched to a Id muon
				for (edm::View <reco::Candidate>::const_iterator MuISOCand2 = IsoMu->begin(); MuISOCand2!=IsoMu->end();MuISOCand2++)
				{
					if (deltaR(MuISOCand2->eta(),MuISOCand2->phi(),MuRecoCand->eta(),MuRecoCand->phi())<0.05   && abs(MuISOCand2->pt()-MuRecoCand->pt())/MuISOCand2->pt()<0.2 ) MuIsoPass_=true;
				}
				}
				
		//		std::cout<<"Invariant mass"<<v1.M();
				
				
			}
		
		}
		
		
		
		
		if (false)
		
		{
		std::cout<<"nRecoElec_"<<nRecoElec_<<std::endl;
		// loop over all reconstructed elecs as tag elecs for reconstruction eff
		for (edm::View <reco::Candidate>::const_iterator ElecIDCand = RecoElec->begin(); ElecIDCand!=RecoElec->end();ElecIDCand++ )
		{	
			if(ElecIdPairFound_) continue;
			double tagPt = ElecIDCand->pt();
			double tagPhi = ElecIDCand->phi();
			double tagEta = ElecIDCand->eta();
			double tagE = ElecIDCand->energy();
			double tagPx = ElecIDCand->px();
			double tagPy = ElecIDCand->py();
			double tagPz = ElecIDCand->pz();
			TLorentzVector TagLorentz(tagPx, tagPy, tagPz, tagE);
			
		
			reco::SuperClusterCollection::const_iterator ElecPromtCand;
			// search for probe elec from PromtElec collection for reconstruction
			for(ElecPromtCand=PromtElec->begin() ;  ElecPromtCand!=PromtElec->end() ; ElecPromtCand++)
			{
				// if the tag is the probe elec skip the probe elec
				double probeE = ElecPromtCand->energy();
				double eta = ElecPromtCand->eta();
				double phi = ElecPromtCand->phi();
				double theta = atan(exp(-eta)) * 2;
				if(deltaR(eta,phi,tagEta,tagPhi)<0.3 && abs(tagE-probeE)/tagE <0.5) continue;
		
				double probePx = probeE * sin(theta) * cos(phi);
				double probePy = probeE * sin(theta) * sin(phi);
				double probePz = probeE * cos(theta);
				TLorentzVector ProbeLorentz(probePx, probePy, probePz, probeE);
				TLorentzVector v1;
				v1 = TagLorentz + ProbeLorentz;
				RecoElecInvariantMass_ = v1.M();
				ElecIdPairFound_=true;
				if ( v1.M()<120 && v1.M()>60 && !ElecIdPass_) 
				{
				RecoElecInvariantMass_ = v1.M();
				ElecIdProbePt_=sqrt(probePx*probePx + probePy * probePy);
				ElecIdProbeEta_=ElecPromtCand->eta();
				ElecIdProbePhi_=ElecPromtCand->phi();
				// loop over all Id elecs to see if the probe elec can be matched to a Id elec
				for (edm::View <reco::Candidate>::const_iterator ElecIDCand2 = RecoElec->begin(); ElecIDCand2!=RecoElec->end();ElecIDCand2++)
				{
					if (deltaR(ElecIDCand2->eta(),ElecIDCand2->phi(),ElecPromtCand->eta(),ElecPromtCand->phi())<0.2   && abs(ElecIDCand2->pt()-ElecIdProbePt_)/ElecIDCand2->pt()<0.2) ElecIdPass_=true;
				}
				}
				
		//		std::cout<<"Invariant mass"<<v1.M();
				
				
			}
		
		}
		
		}
		
		
		
		
		// loop over all reconstructed elecs as tag elecs for reconstruction eff probe::gsfElectrons
		for (edm::View <reco::Candidate>::const_iterator ElecIDCand = RecoElec->begin(); ElecIDCand!=RecoElec->end();ElecIDCand++ )
		{	// make sure only one pair is found and saved
		//	std::cout<<"ElecIDGSf loop started, elecIdPairFound:"<<ElecIdGsfPairFound_<<std::endl;
			if(ElecIdGsfPairFound_) continue;
			double tagPt = ElecIDCand->pt();
			double tagPhi = ElecIDCand->phi();
			double tagEta = ElecIDCand->eta();
			double tagE = ElecIDCand->energy();
			double tagPx = ElecIDCand->px();
			double tagPy = ElecIDCand->py();
			double tagPz = ElecIDCand->pz();
			TLorentzVector TagLorentz(tagPx, tagPy, tagPz, tagE);
			
			// search for probe elec from RecoElec collection for reconstruction
			for(edm::View <reco::Candidate>::const_iterator ElecGsfCand = GsfElec->begin(); ElecGsfCand!=GsfElec->end();ElecGsfCand++ )
			{
				if (deltaPTElecRecoGsfClosestLep_> abs(tagPt - ElecGsfCand->pt() ) )
				{
					deltaPTElecRecoGsfClosestLep_=abs(tagPt - ElecGsfCand->pt() );
					deltaRElecRecoGsfClosestLep_ = deltaR(tagEta,tagPhi,ElecGsfCand->eta(),ElecGsfCand->phi());
				}
				// if the tag is the probe elec skip the probe elec
				if ( deltaR(tagEta,tagPhi,ElecGsfCand->eta(),ElecGsfCand->phi())<0.15 && abs(tagPt - ElecGsfCand->pt() )/tagPt <0.1 ) continue;
				double probeE = ElecGsfCand->energy();
				double probePx = ElecGsfCand->px();
				double probePy = ElecGsfCand->py();
				double probePz = ElecGsfCand->pz();
				TLorentzVector ProbeLorentz(probePx, probePy, probePz, probeE);
				TLorentzVector v1;
				v1 = TagLorentz + ProbeLorentz;
				RecoGsfElecInvariantMass_ = v1.M();
				ElecIdGsfPairFound_=true;
				if ( v1.M()<120 && v1.M()>60 && !ElecIdGsfPass_) 
				{
				RecoGsfElecInvariantMass_ = v1.M();
				ElecIdGsfProbePt_=ElecGsfCand->pt();
				ElecIdGsfProbeEta_=ElecGsfCand->eta();
				ElecIdGsfProbePhi_=ElecGsfCand->phi();
				ElecIdGsfRelPT30GeVJet_ = ElecIdGsfProbePt_/TAPtreeProducer::DRToClosestJet(iEvent, CaloJetTag_,ElecGsfCand->eta(),ElecGsfCand->phi()).second;
				ElecIdGsfDeltaR30GeVJet_ = TAPtreeProducer::DRToClosestJet(iEvent, CaloJetTag_,ElecGsfCand->eta(),ElecGsfCand->phi()).first;
				std::cout<<"ProduceElecIdGsfDeltaR30GeVJet_"<<ElecIdGsfDeltaR30GeVJet_<<std::endl;
				// loop over all Id elecs to see if the probe elec can be matched to a Id elec
				for (edm::View <reco::Candidate>::const_iterator ElecIDCand2 = RecoElec->begin(); ElecIDCand2!=RecoElec->end();ElecIDCand2++)
				{
					if (deltaR(ElecIDCand2->eta(),ElecIDCand2->phi(),ElecGsfCand->eta(),ElecGsfCand->phi())<0.1 && abs(ElecIDCand2->pt()-ElecGsfCand->pt())/ElecIDCand2->pt()<0.2  ) ElecIdGsfPass_=true;
				}
				}
				
		//		std::cout<<"Invariant mass"<<v1.M();
				
				
			}
		
		}
		
		
		
		
		
		// loop over all isolated elecs as tag elecs for reconstruction eff
		for (edm::View <reco::Candidate>::const_iterator ElecISOCand = IsoElec->begin(); ElecISOCand!=IsoElec->end();ElecISOCand++ )
		{	
			double tagPt = ElecISOCand->pt();
			double tagPhi = ElecISOCand->phi();
			double tagEta = ElecISOCand->eta();
			double tagE = ElecISOCand->energy();
			double tagPx = ElecISOCand->px();
			double tagPy = ElecISOCand->py();
			double tagPz = ElecISOCand->pz();
			TLorentzVector TagLorentz(tagPx, tagPy, tagPz, tagE);
			
			// search for probe elec from RecoElec collection for reconstruction
			for(edm::View <reco::Candidate>::const_iterator ElecRecoCand = RecoElec->begin(); ElecRecoCand!=RecoElec->end();ElecRecoCand++ )
			{
		//		std::cout<<"ElecIsoStarted"<<std::endl;
		//		std::cout<<"deltaPTClosestLep_"<<deltaPTClosestLep_<<std::endl;
				if (deltaPTElecIsoClosestLep_> abs(tagPt - ElecRecoCand->pt() ) )
				{
					deltaPTElecIsoClosestLep_=abs(tagPt - ElecRecoCand->pt() );
					deltaRElecIsoClosestLep_ = deltaR(tagEta,tagPhi,ElecRecoCand->eta(),ElecRecoCand->phi());
				}
				// if the tag is the probe elec skip the probe elec
				if ( deltaR(tagEta,tagPhi,ElecRecoCand->eta(),ElecRecoCand->phi())<0.05 && abs(tagPt - ElecRecoCand->pt() )/tagPt <0.05 ) continue;
				double probeE = ElecRecoCand->energy();
				double probePx = ElecRecoCand->px();
				double probePy = ElecRecoCand->py();
				double probePz = ElecRecoCand->pz();
				TLorentzVector ProbeLorentz(probePx, probePy, probePz, probeE);
				TLorentzVector v1;
				v1 = TagLorentz + ProbeLorentz;
				IsoElecInvariantMass_ = v1.M();
				ElecIsoPairFound_=true;
				if ( v1.M()<120 && v1.M()>60 && !ElecIsoPass_) 
				{
				IsoElecInvariantMass_ = v1.M();
				ElecIsoProbePt_=ElecRecoCand->pt();
				ElecIsoProbeEta_=ElecRecoCand->eta();
				ElecIsoProbePhi_=ElecRecoCand->phi();
				ElecIsoRelPT30GeVJet_ = ElecIsoProbePt_/TAPtreeProducer::DRToClosestJet(iEvent, CaloJetTag_,ElecRecoCand->eta(),ElecRecoCand->phi()).second;
				ElecIsoDeltaR30GeVJet_ = TAPtreeProducer::DRToClosestJet(iEvent, CaloJetTag_,ElecRecoCand->eta(),ElecRecoCand->phi()).first;
				std::cout<<"ProduceElecIsoDeltaR30GeVJet_"<<ElecIsoDeltaR30GeVJet_<<std::endl;
				// loop over all Id elecs to see if the probe elec can be matched to a Id elec
				for (edm::View <reco::Candidate>::const_iterator ElecISOCand2 = IsoElec->begin(); ElecISOCand2!=IsoElec->end();ElecISOCand2++)
				{
					if (deltaR(ElecISOCand2->eta(),ElecISOCand2->phi(),ElecRecoCand->eta(),ElecRecoCand->phi())<0.3 && abs(ElecISOCand2->pt()-ElecRecoCand->pt())/ElecISOCand2->pt()<0.5  ) ElecIsoPass_=true;
				}
				}
				
		//		std::cout<<"Invariant mass"<<v1.M();
				
				
			}
		
		}
		
		
		
		
		
		if (false)
		{
		
			nMu_ = IsoMu->size();
		//	std::cout<<"TAPtreeProducer:MuTag="<<MuonTag_<<std::endl;
			if (nMu_!=1) std::cout<<"Number of Muons="<<nMu_<<std::endl;
			MuPt_ = IsoMu->at(0).pt();
			MuEta_ = IsoMu->at(0).eta();
			MuPhi_ = IsoMu->at(0).phi();
		
		}
		
		if ( (MuElecIdIso_==0 && MuIdPairFound_) || (MuElecIdIso_==1 && MuIsoPairFound_) || (MuElecIdIso_==2 && ElecIdPairFound_) || (MuElecIdIso_==3 && ElecIsoPairFound_) || (MuElecIdIso_==4 && ElecIdGsfPairFound_))
		{
		std::cout<<"select_"<<select_<<std::endl;
		tree_->Fill();
		//	std::cout<<"ResultMuIsoDeltaR30GeVJet_"<<MuIsoDeltaR30GeVJet_<<std::endl;
		//	std::cout<<"ResultElecIsoDeltaR30GeVJet_"<<ElecIsoDeltaR30GeVJet_<<std::endl;
		//	std::cout<<"ResultElecIdGsfDeltaR30GeVJet_"<<ElecIdGsfDeltaR30GeVJet_<<std::endl;
		//	std::cout<<"ResultMuIdDeltaR30GeVJet_"<<MuIdDeltaR30GeVJet_<<std::endl;
		}
		
		
		}
		
		
		
		
		}
		
		// ------------ method called once each job just before starting event loop  ------------
		void 
		TAPtreeProducer::beginJob()
		{
		//std::cout<<"TAPtreeProducer::beginJob:started"<<std::endl;
			edm::Service<TFileService> fs;
			tree_ = fs->make<TTree>("TAPtreeProducer","TAPtreeProducer");
		// plotting values
		tree_->Branch("HT",&ht_,"HT/F");
		tree_->Branch("MHT",&mht_,"MHT/F");
		tree_->Branch("NJets",&nJets_,"NJets/i");
		tree_->Branch("Weight",&eventWeight_,"Weight/F");
		tree_->Branch("NVtx",&nV_,"NVtx/s");
		tree_->Branch("MT",&met_,"MT/F");
		//    tree_->Branch("NVtx",&nV_,"NVtx/s");
		tree_->Branch("tagIsoMu",&tagIsoMu_,"tagIsoMu/F");
		tree_->Branch("tagIsoElec",&tagIsoElec_,"tagIsoElec/F");
		
		tree_->Branch("probeIsoMu",&probeIsoMu_,"probeIsoMu/F");
		tree_->Branch("probeIsoElec",&probeIsoElec_,"probeIsoElec/F");
		
		tree_->Branch("nIsoMu",&nIsoMu_,"nIsoMu/s");
		tree_->Branch("nRecoMu",&nRecoMu_,"nRecoMu/s");
		tree_->Branch("nPromtMu",&nPromtMu_,"nPromtMu/s");
		
		tree_->Branch("nIsoElec",&nIsoElec_,"nIsoElec/s");
		tree_->Branch("nRecoElec",&nRecoElec_,"nRecoElec/s");
		tree_->Branch("nPromtElec",&nPromtElec_,"nPromtElec/s");
		if(MuElecIdIso_==1)
		{
		std::cout<<"MuIso"<<std::endl;
		tree_->Branch("IsoMuInvariantMass",&IsoMuInvariantMass_,"IsoMuInvariantMass/F");
		tree_->Branch("MuIsoPass",&MuIsoPass_,"MuIsoPass/I");
		tree_->Branch("MuIsoProbePt",&MuIsoProbePt_,"MuIsoProbePt/F");
		tree_->Branch("MuIsoProbeEta",&MuIsoProbeEta_,"MuIsoProbeEta/F");
		tree_->Branch("MuIsoProbePhi",&MuIsoProbePhi_,"MuIsoProbePhi/F");
		tree_->Branch("MuIsoTagCharge",&tagCharge_,"MuIsoTagCharge/I");
		tree_->Branch("MuIsoProbeCharge",&MuIsoProbeCharge_,"MuIsoProbeCharge/I");
		
		tree_->Branch("MuIsoDeltaR30GeVJet",&MuIsoDeltaR30GeVJet_,"MuIsoDeltaR30GeVJet/F");
		tree_->Branch("MuIsoRelPT30GeVJet",&MuIsoRelPT30GeVJet_,"MuIsoRelPT30GeVJet/F");
		tree_->Branch("deltaPTMuIsoClosestLep",&deltaPTMuIsoClosestLep_,"deltaPTMuIsoClosestLep/F");
		tree_->Branch("deltaRMuIsoClosestLep",&deltaRMuIsoClosestLep_,"deltaRMuIsoClosestLep/F");
		}
		if(MuElecIdIso_==0)
		{
		std::cout<<"MuReco"<<std::endl;
		tree_->Branch("RecoMuInvariantMass",&RecoMuInvariantMass_,"RecoMuInvariantMass/F");
		tree_->Branch("MuIdPass",&MuIdPass_,"MuIdPass/I");
		tree_->Branch("MuIdTagCharge",&tagCharge_,"MuIdTagCharge/I");
		tree_->Branch("MuIdProbeCharge",&MuIdProbeCharge_,"MuIdProbeCharge/I");
		tree_->Branch("MuIdProbePt",&MuIdProbePt_,"MuIdProbePt/F");
		tree_->Branch("MuIdProbeEta",&MuIdProbeEta_,"MuIdProbeEta/F");
		tree_->Branch("MuIdProbePhi",&MuIdProbePhi_,"MuIdProbePhi/F");
		
		tree_->Branch("MuIdDeltaR30GeVJet",&MuIdDeltaR30GeVJet_,"MuIdDeltaR30GeVJet/F");
		tree_->Branch("MuIdRelPT30GeVJet",&MuIdRelPT30GeVJet_,"MuIdRelPT30GeVJet/F");
		tree_->Branch("deltaPTMuRecoClosestLep",&deltaPTMuRecoClosestLep_,"deltaPTMuRecoClosestLep/F");
		tree_->Branch("deltaRMuRecoClosestLep",&deltaRMuRecoClosestLep_,"deltaRMuRecoClosestLep/F");
		}
		if(MuElecIdIso_==3)
		{
		std::cout<<"ElecIso"<<std::endl;
		tree_->Branch("IsoElecInvariantMass",&IsoElecInvariantMass_,"IsoElecInvariantMass/F");
		tree_->Branch("ElecIsoPass",&ElecIsoPass_,"ElecIsoPass/I");
		tree_->Branch("ElecIsoProbePt",&ElecIsoProbePt_,"ElecIsoProbePt/F");
		tree_->Branch("ElecIsoProbeEta",&ElecIsoProbeEta_,"ElecIsoProbeEta/F");
		tree_->Branch("ElecIsoProbePhi",&ElecIsoProbePhi_,"ElecIsoProbePhi/F");
		tree_->Branch("ElecIsoTagCharge",&tagCharge_,"ElecIsoTagCharge/I");
		tree_->Branch("ElecIdProbeCharge",&ElecIsoCharge_,"ElecIdProbeCharge/I");
		
		tree_->Branch("ElecIsoDeltaR30GeVJet",&ElecIsoDeltaR30GeVJet_,"ElecIsoDeltaR30GeVJet/F");
		tree_->Branch("ElecIsoRelPT30GeVJet",&ElecIsoRelPT30GeVJet_,"ElecIsoRelPT30GeVJet/F");
		tree_->Branch("deltaPTElecIsoClosestLep",&deltaPTElecIsoClosestLep_,"deltaPTElecIsoClosestLep/F");
		tree_->Branch("deltaRElecIsoClosestLep",&deltaRElecIsoClosestLep_,"deltaRElecIsoClosestLep/F");
		}
		if(MuElecIdIso_==2)
		{
		std::cout<<"ElecReco"<<std::endl;
		tree_->Branch("RecoElecInvariantMass",&RecoElecInvariantMass_,"RecoElecInvariantMass/F");
		tree_->Branch("ElecIdPass",&ElecIdPass_,"ElecIdPass/I");
		tree_->Branch("ElecIdProbePt",&ElecIdProbePt_,"ElecIdProbePt/F");
		tree_->Branch("ElecIdProbeEta",&ElecIdProbeEta_,"ElecIdProbeEta/F");
		tree_->Branch("ElecIdProbePhi",&ElecIdProbePhi_,"ElecIdProbePhi/F");
		
		}
		if(MuElecIdIso_==4)
		{
		std::cout<<"ElecRecoGSF"<<std::endl;
		tree_->Branch("RecoGsfElecInvariantMass",&RecoGsfElecInvariantMass_,"RecoGsfElecInvariantMass/F");
		tree_->Branch("ElecIdGsfPass",&ElecIdGsfPass_,"ElecIdGsfPass/I");
		tree_->Branch("ElecIdGsfProbePt",&ElecIdGsfProbePt_,"ElecIdGsfProbePt/F");
		tree_->Branch("ElecIdGsfProbeEta",&ElecIdGsfProbeEta_,"ElecIdGsfProbeEta/F");
		tree_->Branch("ElecIdGsfProbePhi",&ElecIdGsfProbePhi_,"ElecIdGsfProbePhi/F");
		tree_->Branch("ElecIdGsfTagCharge",&tagCharge_,"ElecIdGsfTagCharge/I");
		tree_->Branch("ElecIdGsfCharge",&ElecIdGsfCharge_,"ElecIdGsfCharge/I");
		
		tree_->Branch("ElecIdGsfDeltaR30GeVJet",&ElecIdGsfDeltaR30GeVJet_,"ElecIdGsfDeltaR30GeVJet/F");
		tree_->Branch("ElecIdGsfRelPT30GeVJet",&ElecIdGsfRelPT30GeVJet_,"ElecIdGsfRelPT30GeVJet/F");
		
		tree_->Branch("deltaPTElecRecoGsfClosestLep",&deltaPTElecRecoGsfClosestLep_,"deltaPTElecRecoGsfClosestLep/F");
		tree_->Branch("deltaRElecRecoGsfClosestLep",&deltaRElecRecoGsfClosestLep_,"deltaRElecRecoGsfClosestLep/F");
		}
		tree_->Branch("MuIdPairFound",&MuIdPairFound_,"MuIdPairFound/b");
		tree_->Branch("MuIsoPairFound",&MuIsoPairFound_,"MuIsoPairFound/b");
		tree_->Branch("ElecIdPairFound",&ElecIdPairFound_,"ElecIdPairFound/b");
		tree_->Branch("ElecIdGsfPairFound",&ElecIdGsfPairFound_,"ElecIdGsfPairFound/b");
		tree_->Branch("ElecIsoPairFound",&ElecIsoPairFound_,"ElecIsoPairFound/b");
		
		
			// delta PT and delta R next lepton
		
		
		
		
			// x check values;
		
		
		// binByBin eff seperately
		
		
		
		
		
		
		
		
			// tag and prob unceratinties
		//    tree_->Branch("muonRecoTAPUp",&muonRecoTAPUp_,"muonRecoTAPUp/F");
		//    tree_->Branch("muonRecoTAPDown",&muonRecoTAPDown_,"muonRecoTAPDown/F");
		//    tree_->Branch("muonIsoTAPUp",&muonIsoTAPUp_,"muonIsoTAPUp/F");
		//    tree_->Branch("muonIsoTAPDown",&muonIsoTAPDown_,"muonIsoTAPDown/F");
		
		//    tree_->Branch("elecRecoTAPUp",&elecRecoTAPUp_,"elecRecoTAPUp/F");
		//    tree_->Branch("elecRecoTAPDown",&elecRecoTAPDown_,"elecRecoTAPDown/F");
		//    tree_->Branch("elecIsoTAPUp",&elecIsoTAPUp_,"elecIsoTAPUp/F");
		//    tree_->Branch("elecIsoTAPDown",&elecIsoTAPDown_,"elecIsoTAPDown/F");
		
		
		//std::cout<<"TAPtreeProducer::beginJob:finished"<<std::endl;
		}
		void 
		TAPtreeProducer::ResetValues()
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
		
			tagCharge_=0;
			MuIdProbeCharge_=0;
			MuIsoProbeCharge_=0;
			eventWeight_=0;
			error_=0;
		
			tagIsoMu_=0;
			probeIsoMu_=0;
		
			nIsoMu_=0;
			nRecoMu_=0;
			nPromtMu_=0;
		
			nIsoElec_=0;
			nRecoElec_=0;
			nPromtElec_=0;
		
			IsoMuInvariantMass_=0;
			RecoMuInvariantMass_=0;
			MuIdPass_=false;
			MuIsoPass_=false;
		
			IsoElecInvariantMass_=0;
			RecoElecInvariantMass_=0;
			RecoGsfElecInvariantMass_=0;
			ElecIdPass_=false;
			ElecIdGsfPass_=false;
			ElecIsoPass_=false;
		
			ElecIsoProbePt_=0;
			ElecIsoProbePhi_=0;
			ElecIsoProbeEta_=0;
			ElecIdProbePt_=0;
			ElecIdProbePhi_=0;
			ElecIdProbeEta_=0;
			ElecIdGsfProbePt_=0;
			ElecIdGsfProbePhi_=0;
			ElecIdGsfProbeEta_=0;
		
			MuIsoProbePt_=0;
			MuIsoProbePhi_=0;
			MuIsoProbeEta_=0;
			MuIdProbePt_=0;
			MuIdProbePhi_=0;
			MuIdProbeEta_=0;
		
		MuIdDeltaR30GeVJet_=0;
		MuIdRelPT30GeVJet_=0;
		MuIsoDeltaR30GeVJet_=0;
		MuIsoRelPT30GeVJet_=0;
		ElecIdGsfDeltaR30GeVJet_=0;
		ElecIdGsfRelPT30GeVJet_=0;
		ElecIsoDeltaR30GeVJet_=0;
		ElecIsoRelPT30GeVJet_=0;
		
		MuIdPairFound_=false;
		MuIsoPairFound_=false;
		ElecIdPairFound_=false;
		ElecIsoPairFound_=false;
		ElecIdGsfPairFound_=false;
		
		// check distance leptons
		
		deltaPTMuRecoClosestLep_=1000;
		deltaRMuRecoClosestLep_=1000;
		deltaPTMuIsoClosestLep_=1000;
		deltaRMuIsoClosestLep_=1000;
		
		deltaPTElecRecoGsfClosestLep_=1000;
		deltaRElecRecoGsfClosestLep_=1000;
		deltaPTElecIsoClosestLep_=1000;
		deltaRElecIsoClosestLep_=1000;
		
		}
		// ------------ method called once each job just after ending the event loop  ------------
		void 
		TAPtreeProducer::endJob() {
		}
		
		// ------------ method called when starting to processes a run  ------------
		void 
		TAPtreeProducer::beginRun(edm::Run&, edm::EventSetup const&)
		{
		}
		
		// ------------ method called when ending the processing of a run  ------------
		void 
		TAPtreeProducer::endRun(edm::Run&, edm::EventSetup const&)
		{
		}
		
		// ------------ method called when starting to processes a luminosity block  ------------
		void 
		TAPtreeProducer::beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
		{
		}
		
		// ------------ method called when ending the processing of a luminosity block  ------------
		void 
		TAPtreeProducer::endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
		{
		}
		
		// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
		void
		TAPtreeProducer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
		//The following says we do not know what parameters are allowed so do no validation
		// Please change this to state exactly what you do use, even if it is no parameters
		edm::ParameterSetDescription desc;
		desc.setUnknown();
		descriptions.addDefault(desc);
		}
		
		//define this as a plug-in
		DEFINE_FWK_MODULE(TAPtreeProducer);
		
		
		std::pair <double,double> TAPtreeProducer::DRToClosestJet(const edm::Event& iEvent, edm::InputTag caloJetTag, double lepEta, double lepPhi)
		{
			edm::Handle <edm::View<pat::Jet> >jets;
			iEvent.getByLabel(caloJetTag,jets);
			double resultDR=9999;
			double resultJetPt=9999;
			unsigned int nJets = jets->size();
			// loop over all the jets in the event
			for (unsigned int i=0; i<nJets;i++)
			{
				double tempDeltaR = deltaR(jets->at(i).eta(),jets->at(i).phi(),lepEta,lepPhi);
				if(tempDeltaR<resultDR && jets->at(i).emEnergyFraction() <0.9 && jets->at(i).emEnergyFraction() > 0.05 && jets->at(i).pt()>29.999 ) // removed here && tempDeltaR>0.1 
				{
					resultDR = tempDeltaR;
					resultJetPt = jets->at(i).pt();
				}
			}
		
		//	std::cout<<"DRToClosestJet::resultDR"<<resultDR<<std::endl;
			return std::make_pair(resultDR,resultJetPt);
		}
