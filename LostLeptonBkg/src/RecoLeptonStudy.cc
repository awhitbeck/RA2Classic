// -*- C++ -*-
//
// Package:    RecoLeptonStudy
// Class:      RecoLeptonStudy
// 
/**\class MCEffCalculator RecoLeptonStudy.cc RA2Classic/RecoLeptonStudy/src/RecoLeptonStudy.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Arne-Rasmus Draeger,,,uni-hamburg
//         Created:  Thu Sep 27 10:50:02 CEST 2012
// $Id: RecoLeptonStudy.cc,v 1.19 2013/02/15 10:54:41 adraeger Exp $
//
//


// system include files
#include "RA2Classic/LostLeptonBkg/interface/RecoLeptonStudy.h"
#include "DataFormats/Math/interface/deltaPhi.h"
#include <DataFormats/Math/interface/deltaR.h>
//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
RecoLeptonStudy::RecoLeptonStudy(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed
  treeName_ = iConfig.getParameter<std::string>("TreeName");
  evtWeightTag_ = iConfig.getParameter<edm::InputTag> ("EventWeightTag");
  // muon elec tags
  muonIDTag_ = iConfig.getParameter<edm::InputTag> ("MuonIDTag");
  muonIDISOTag_= iConfig.getParameter<edm::InputTag> ("MuonIDISOTag");
  muonPromtMatchedTag_= iConfig.getParameter<edm::InputTag> ("MuonPromtMatchedTag");
  elecIDTag_ = iConfig.getParameter<edm::InputTag> ("ElecIDTag");
  elecIDISOTag_ = iConfig.getParameter<edm::InputTag> ("ElecIDISOTag");
  caloJetTag_ =iConfig.getParameter<edm::InputTag> ("CaloJetTag");
  metTag_ = iConfig.getParameter<edm::InputTag> ("METTag");
  genTag_ = iConfig.getParameter<edm::InputTag> ("GenTag"); 
  minMuonPt_ = iConfig.getParameter<double> ("minMuonPt");
  maxMuonEta_ = iConfig.getParameter<double> ("maxMuonEta");
  minElecPt_ = iConfig.getParameter<double> ("minElecPt");
  maxElecEta_ =iConfig.getParameter<double> ("maxElecEta");
  minJetPt_ = iConfig.getParameter<double> ("minJetPt") ;

// addiontial plot related variables
   HtJetsTag_ = iConfig.getParameter<edm::InputTag>("HTJetsTag");
   MhtJetsTag_ = iConfig.getParameter<edm::InputTag>("MhtJetsTag");
   HTTag_ = iConfig.getParameter<edm::InputTag>("HTTag");
   MHTTag_ = iConfig.getParameter<edm::InputTag>("MHTTag");
   NVTag_ = iConfig.getParameter<edm::InputTag>("VertexCollection");
   Z_ = iConfig.getParameter<bool>("UseZResonanze");
   debug_ = iConfig.getParameter<bool>("debug");

}


RecoLeptonStudy::~RecoLeptonStudy()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
RecoLeptonStudy::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
if(debug_)std::cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
if(debug_)std::cout<<"RecoLeptonStudy::Started"<<std::endl;
   // resets all the values
   ResetValues();
   using namespace edm;
   edm::Handle < reco::GenParticleCollection > genParticles;
   iEvent.getByLabel(genTag_, genParticles);
   // get a collection of reco muons
   edm::Handle <edm::View <reco::Candidate> > MuID;
   iEvent.getByLabel(muonIDTag_,MuID);
   edm::Handle <edm::View <reco::Candidate> > MuIDISO;
   iEvent.getByLabel(muonIDISOTag_,MuIDISO);



   // get a collection of reco elec.
   edm::Handle <edm::View <reco::Candidate> > ElecID;
   iEvent.getByLabel(elecIDTag_,ElecID);
   edm::Handle <edm::View <reco::Candidate> > ElecIDISO;
   iEvent.getByLabel(elecIDISOTag_,ElecIDISO);

   // get Event weight
   edm::Handle<double> eventWeight;
   iEvent.getByLabel(evtWeightTag_,eventWeight);
   eventWeight_ = *eventWeight;

   edm::Handle< edm::View<reco::Candidate> > met;
   iEvent.getByLabel(metTag_,met);
   mt_= met->at(0).pt();



// addiontial input for plotting
  edm::Handle< edm::View<reco::Candidate> > htJets;
  iEvent.getByLabel(HtJetsTag_,htJets);

  nJets_ = htJets->size();

  edm::Handle< edm::View<reco::Candidate> > mhtJets;
  iEvent.getByLabel(MhtJetsTag_,mhtJets);
   

  // HT & MHT
  edm::Handle<double> ht;
  iEvent.getByLabel(HTTag_,ht);

    ht_ = *ht;

  edm::Handle< edm::View<reco::Candidate> > mht;
  iEvent.getByLabel(MHTTag_,mht);

    mht_ = mht->at(0).pt();

  edm::Handle<reco::VertexCollection> vertices;
  iEvent.getByLabel(NVTag_,vertices);
  if( vertices.isValid() ) 
  {
    	nV_ = vertices->size();
  }

  





   // select muon id 13 on gen level
   // iterates over all gen particles
   for(reco::GenParticleCollection::const_iterator cand = genParticles->begin(); cand!=genParticles->end(); ++cand) 
   {
	// demands only w bosons from the hard interaction
	if(Z_ && (cand->status()!=3 || abs(cand->pdgId())!=23)) continue;
    	if(!Z_ &&(abs(cand->pdgId())!=24 || cand->status()!=3)) continue;
	// only not hadronically decaying w will survive

	for (unsigned int i=0; i < cand->numberOfDaughters(); i++)
	{
		// muon
		if (abs(cand->daughter(i)->pdgId() ) == 13) 
		{//std::cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
//std::cout<<"RecoLeptonStudy::Started"<<std::endl;
			MuonFound(cand,i);
			if(cand->daughter(i)->status()==2)std::cout<<"muon has status 2"<<std::endl;
		}
		//electrons
		if (abs(cand->daughter(i)->pdgId() ) == 11) 
		{
			ElecFound(cand,i);
			if(cand->daughter(i)->status()==2)std::cout<<"elec has status 2"<<std::endl;
		}
		// tau decay
		if (abs(cand->daughter(i)->pdgId() ) == 15)
		{
			tauFound_++;
			TauFound(cand->daughter(i));
			if(cand->daughter(i)->status()==2)std::cout<<"tau has status 2"<<std::endl;
		}
	
	}
	
   }





genDeltaR_=DRToClosestJet(iEvent, caloJetTag_,genEta_,genPhi_).first;
genPTJet_=DRToClosestJet(iEvent, caloJetTag_,genEta_,genPhi_).second;
genPTRelJet_=genPt_/genPTJet_;









// one muon has been found the three different efficiencies will be determined now. first acc than reco and final iso the results will be stored in th2f histogramms.
   if(nGenElec_==0 && nGenMu_==1 )
//   if (nGenMu_==1 && nGenElec_==0)
   {
	deltaGenR_ = DRToClosestJet(iEvent,caloJetTag_, muonGenEta_, muonGenPhi_).first;
	closestJetToMuonGenPt_ = DRToClosestJet(iEvent,caloJetTag_, muonGenEta_,muonGenPhi_).second;

				RecoMuonDeltaR_=DRToClosestJet(iEvent, caloJetTag_,muonGenEta_,muonGenPhi_).first;
				RecoMuonPTJet_=DRToClosestJet(iEvent, caloJetTag_,muonGenEta_,muonGenPhi_).second;
				RecoMuonPTRelJet_=muonRecoPt_/RecoMuonPTJet_;

	// decided if the muon passed or failed the acc criteria 
	if( std::abs(muonGenEta_)> maxMuonEta_ || muonGenPt_ < minMuonPt_ )
	{	

		nAccMu_=-1;
		isExpectation_+=1;


		
	}
	// else the muon is within the acceptance
	else 
	{
		nAccMu_=+1;
		// This histogramm is used for the actual acceptance caluclation

		muonPTAccPassed_=muonGenPt_;
		///////////////////// ID checking
		//check if ID criteria are matched
		muonNumberRecoID_=MuID->size();
		//true if no Mu has been reconstructed
		edm::View <reco::Candidate>::const_iterator itRecoMu = LeptonMatch(*MuID, muonGenEta_, muonGenPhi_,muonGenPt_);
		//true if reco muon matched

		if (itRecoMu != MuID->end() )
			{
			muonRecoPt_=itRecoMu->pt();
			muonRecoEta_ = itRecoMu->eta();
			muonRecoPhi_ = itRecoMu->phi();
			RecoGenMuDeltaR_=deltaR(muonGenEta_,muonGenPhi_,muonRecoEta_,muonRecoPhi_);
		// calculates the mtw for the reconstructed muon
		recoMtw1_= MTWCalculator(iEvent, metTag_,muonRecoPt_,muonRecoPhi_);
		promtRecoTLVMu_.SetPtEtaPhiE(muonRecoPt_,muonRecoEta_,muonRecoPhi_,0);
		promtRecoTLVMET_.SetPtEtaPhiE(met->at(0).pt(),met->at(0).eta(),met->at(0).phi(),0);
		promtRecoTLVWDecay_=promtRecoTLVMu_ + promtRecoTLVMET_;
		
		recoMuDeltaPTClosestJet1_= muonRecoPt_/DRToClosestJet(iEvent, caloJetTag_,muonRecoEta_,muonRecoPhi_).second;	
		recoMuDeltaRClosestJet1_ = DRToClosestJet(iEvent, caloJetTag_,muonRecoEta_,muonRecoPhi_).first;
				nRecoMu_=1;
				RecoMuonDeltaR_=DRToClosestJet(iEvent, caloJetTag_,muonRecoEta_,muonRecoPhi_).first;
				RecoMuonPTJet_=DRToClosestJet(iEvent, caloJetTag_,muonRecoEta_,muonRecoPhi_).second;
				RecoMuonPTRelJet_=muonRecoPt_/RecoMuonPTJet_;

				// muon Iso check true if there are isolated muons
				for( edm::View <reco::Candidate>::const_iterator MuIDIsoCand = MuIDISO->begin(); MuIDIsoCand!=MuIDISO->end();MuIDIsoCand++)
				{
					muonIsoPt_ = MuIDIsoCand->pt();
					muonIsoEta_ = MuIDIsoCand->eta();
					muonIsoPhi_ = MuIDIsoCand->phi();
					// true if Iso is fulfilled
					if (deltaR(muonIsoEta_,muonIsoPhi_,muonRecoEta_,muonRecoPhi_) < 0.1)
					{	
						isExpectation_=-1;
						nIsoMu_=+1;
						IsoMuonDeltaR_=RecoMuonDeltaR_;
						IsoMuonPTJet_=RecoMuonPTJet_;
						IsoMuonPTRelJet_=muonRecoPt_/RecoMuonPTJet_;

						mtw_= MTWCalculator(iEvent, metTag_,muonIsoPt_,muonIsoPhi_);

//						for (unsigned int i=0; i<nJets_;i++)
//						{
//							if( abs(htJets->at(i).pt() - muonIsoPt_)/muonIsoPt_ < 0.1 && deltaR(htJets->at(i).eta(),htJets->at(i).phi(), muonIsoEta_,muonIsoPhi_) < 0.2 ) nJets_-=1;
//						}



					}
					if(nIsoMu_>0) break;
				}

				if (nIsoMu_==0)
				{
					isExpectation_=1;
					nIsoMu_=-1;

				}
			}
		
		// no gen muon could be matched to a reco muon
		if (nRecoMu_==0)
		{
			nRecoMu_=-1;

			isExpectation_ =1;


		}
		///////////////////// ID checking DONE

	}
   }






// one elec has been found the three different efficiencies will be determined now. first acc than reco and final iso the results will be stored in th2f histogramms.
   if (nGenElec_==1 && nGenMu_==0)
   {

	deltaGenR_ = DRToClosestJet(iEvent,caloJetTag_, elecGenEta_, elecGenPhi_).first;
	closestJetToElecGenPt_ = DRToClosestJet(iEvent,caloJetTag_, elecGenEta_,elecGenPhi_).second;

				RecoElecDeltaR_=DRToClosestJet(iEvent, caloJetTag_,elecGenEta_,elecGenPhi_).first;
				RecoElecPTJet_=DRToClosestJet(iEvent, caloJetTag_,elecGenEta_,elecGenPhi_).second;
				RecoElecPTRelJet_=elecRecoPt_/RecoElecPTJet_;

	// decided if the elec passed or failed the acc criteria 
	if( std::abs(elecGenEta_)> maxElecEta_ || elecGenPt_ < minElecPt_)
	{	

		nAccElec_=-1;
		isExpectation_+=1;


		
	}
	// else the elec is within the acceptance
	else 
	{
		nAccElec_=+1;
		// This histogramm is used for the actual acceptance caluclation

		elecPTAccPassed_=elecGenPt_;
		///////////////////// ID checking
		//check if ID criteria are matched
		elecNumberRecoID_=ElecID->size();
		//true if no elec has been reconstructed

		edm::View <reco::Candidate>::const_iterator itRecoElec = LeptonMatch(*ElecID, elecGenEta_, elecGenPhi_,elecGenPt_);
		//true if reco muon matched
		if (itRecoElec != ElecID->end() )
			{
			elecRecoPt_= itRecoElec->pt();
			elecRecoEta_ = itRecoElec->eta();
			elecRecoPhi_ = itRecoElec->phi();
			RecoGenElecDeltaR_=deltaR(elecGenEta_,elecGenPhi_,elecRecoEta_,elecRecoPhi_);	
				nRecoElec_=+1;
				RecoElecDeltaR_=DRToClosestJet(iEvent, caloJetTag_,elecRecoEta_,elecRecoPhi_).first;
				RecoElecPTJet_=DRToClosestJet(iEvent, caloJetTag_,elecRecoEta_,elecRecoPhi_).second;
				RecoElecPTRelJet_=elecRecoPt_/RecoElecPTJet_;

				// elec Iso check true if there are isolated elec
				if (ElecIDISO->size() > 0 )
				{
					for( edm::View <reco::Candidate>::const_iterator ElecIDIsoCand = ElecIDISO->begin(); ElecIDIsoCand!=ElecIDISO->end();ElecIDIsoCand++)
					{
						elecIsoPt_ = ElecIDIsoCand->pt();
						elecIsoEta_ = ElecIDIsoCand->eta();
						elecIsoPhi_ = ElecIDIsoCand->phi();
						// true if Iso is fulfilled
						if (deltaR(elecIsoEta_,elecIsoPhi_,elecRecoEta_,elecRecoPhi_) < 0.1)
						{
							isExpectation_=-1;
							nIsoElec_=+1;
							IsoElecDeltaR_=RecoElecDeltaR_;
							IsoElecPTJet_=RecoElecPTJet_;
							IsoElecPTRelJet_=elecRecoPt_/RecoElecPTJet_;

//							for (unsigned int i=0; i<nJets_;i++)
//							{
//								if( abs(htJets->at(i).pt() - elecIsoPt_)/elecIsoPt_ < 0.1 && deltaR(htJets->at(i).eta(),htJets->at(i).phi(), elecIsoEta_,elecIsoPhi_) < 0.3 ) nJets_-=1;
//							}


						}
					if(nIsoElec_>0) break;
					}
				}
				if (nIsoElec_==0)
				{
					isExpectation_+=1;
					nIsoElec_=-1;

				}
			}
		// no gen elec could be matched to a reco elec
		if (nRecoElec_==0)
		{
			nRecoElec_=-1;

			isExpectation_ =1;
		}
		///////////////////// ID checking DONE

	}

   }




   leptons_ = nGenMu_ + nGenElec_;


    nMuInIsoMuCollection_= MuIDISO->size();
	// this GEN pt is not GEN anymore it is reco pt
    if(nGenMu_==0 && nMuInIsoMuCollection_>0)
	{
	for( edm::View <reco::Candidate>::const_iterator MuIDIsoCand = MuIDISO->begin(); MuIDIsoCand!=MuIDISO->end();MuIDIsoCand++)
	{
		muonGenPt_ = MuIDIsoCand->pt();
		muonGenEta_ = MuIDIsoCand->eta();
		muonGenPhi_ = MuIDIsoCand->phi();
	}
	}


// if a top decayed to a b and a mu and munu calculate delta r and trans top mass


for (int i=0;i<10;i++)
{
nonPromtMu_[i]=0;
nonPromtMuPt_[i]=0;
nonPromtMuEta_[i]=0;
nonPromtMuPhi_[i]=0;
nonPromtMuDeltaR_[i]=0;
nonPromtMuDeltaPT_[i]=0;
}

// store all reconstructed muons 
	int muIdCount=-1;
	for( edm::View <reco::Candidate>::const_iterator MuIDCand = MuID->begin(); MuIDCand!=MuID->end();MuIDCand++)
	{
	muIdCount++;
	if (muIdCount>9) continue;
		if (nGenMu_>0.5 && nAccMu_>0.5 && nRecoMu_>0.5)
		{
			if ( abs(muonRecoPt_-MuIDCand->pt() )/muonRecoPt_<0.1 && deltaR(muonRecoEta_,muonRecoPhi_,MuIDCand->eta(),MuIDCand->phi() < 0.1) ) nonPromtMu_[muIdCount]=-1;
			else nonPromtMu_[muIdCount]=1;

		}
		else nonPromtMu_[muIdCount]=1;
		nonPromtMuPt_[muIdCount] = MuIDCand->pt();
		nonPromtMuEta_[muIdCount] = MuIDCand->eta();
		nonPromtMuPhi_[muIdCount] = MuIDCand->phi();
		nonPromtMuDeltaR_[muIdCount] = DRToClosestJet(iEvent, caloJetTag_,MuIDCand->eta(),MuIDCand->phi()).first;
		nonPromtMuDeltaPT_[muIdCount] = MuIDCand->pt() / DRToClosestJet(iEvent, caloJetTag_,MuIDCand->eta(),MuIDCand->phi()).second;
	}







  tree_->Fill();
//std::cout<<"RecoLeptonStudy::Ended"<<std::endl;
//std::cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;

}



// ------------ method called once each job just before starting event loop  ------------
void 
RecoLeptonStudy::beginJob()
{

  	edm::Service<TFileService> fs;
  	tree_ = fs->make<TTree>(treeName_,treeName_);
//create branches in the tree
    
    tree_->Branch("nLeptons",&leptons_,"nLeptons/I");
    tree_->Branch("nGenMu",&nGenMu_,"nGenMu/I");
    tree_->Branch("nGenElec",&nGenElec_,"nGenElec/I");
    tree_->Branch("tauFound",&tauFound_,"tauFound/I");
    tree_->Branch("genPt",&genPt_,"genPt/F");
    tree_->Branch("genPhi",&genPhi_,"genPhi/F");
    tree_->Branch("genEta",&genEta_,"genEta/F");
    tree_->Branch("genDeltaR",&genDeltaR_,"genDeltaR/F");
    tree_->Branch("genPTJet",&genPTJet_,"genPTJet/F");
    tree_->Branch("genPTRelJet",&genPTRelJet_,"genPTRelJet/F");

    tree_->Branch("MuonPTAccPassed",&muonPTAccPassed_,"MuonPTAccPassed/F");
    tree_->Branch("MuonIDPassed",&muonIDPassed_,"MuonIDPassed/F");
    tree_->Branch("MuonIDFailed",&muonIDFailed_,"MuonIDFailed/F");
    tree_->Branch("MuonGenPt",&muonGenPt_,"MuonGenPt/F");
    tree_->Branch("MuonGenPhi",&muonGenEta_,"MuonGenPhi/F");
    tree_->Branch("MuonGenEta",&muonGenPhi_,"MuonGenEta/F");
    tree_->Branch("MuonGenNumber",&nGenMu_,"MuonGenNumber/s");
    tree_->Branch("MuonNumberRecoID",&muonNumberRecoID_,"MuonNumberRecoID/I");


    tree_->Branch("ElecPTAccPassed",&elecPTAccPassed_,"ElecPTAccPassed/F");
    tree_->Branch("ElecGenPt",&elecGenPt_,"ElecGenPt/F");
    tree_->Branch("ElecGenPhi",&elecGenEta_,"ElecGenPhi/F");
    tree_->Branch("ElecGenEta",&elecGenPhi_,"ElecGenEta/F");
    tree_->Branch("ElecGenNumber",&nGenElec_,"ElecGenNumber/s");
    tree_->Branch("ElecNumberRecoID",&elecNumberRecoID_,"ElecNumberRecoID/I");


    tree_->Branch("GenDeltaRLepClosestJet",&deltaGenR_,"GenDeltaRLepClosestJet/F");
    tree_->Branch("ClosestJetElecGenPt",&closestJetToElecGenPt_,"ClosestJetElecGenPt/F");
    tree_->Branch("ClosestJetMuonGenPt",&closestJetToMuonGenPt_,"ClosestJetMuonGenPt/F");
    tree_->Branch("MTW",&mtw_,"MTW/F");

    // discriminator for mc expectaiton selector +1 passed -1 failed
    tree_->Branch("nAccMu",&nAccMu_,"nAccMu/I");
    tree_->Branch("nRecoMu",&nRecoMu_,"nRecoMu/I");
    tree_->Branch("nIsoMu",&nIsoMu_,"nIsoMu/I");

    tree_->Branch("nAccElec",&nAccElec_,"nAccElec/I");
    tree_->Branch("nRecoElec",&nRecoElec_,"nRecoElec/I");
    tree_->Branch("nIsoElec",&nIsoElec_,"nIsoElec/I");

    //Testing variables
    tree_->Branch("RecoLevelMuonDeltaR",&RecoMuonDeltaR_,"RecoLevelMuonDeltaR/F");
    tree_->Branch("RecoLevelMuonPTJet",&RecoMuonPTJet_,"RecoLevelMuonPTJet/F");
    tree_->Branch("RecoLevelMuonRelPTJet",&RecoMuonPTRelJet_,"RecoLevelMuonRelPTJet/F");
    tree_->Branch("RecoVsGenLevelMuonDeltaR",&RecoGenMuDeltaR_,"RecoVsGenLevelMuonDeltaR/F");
    tree_->Branch("muonRecoPt",&muonRecoPt_,"muonRecoPt/F");
    tree_->Branch("muonRecoEta",&muonRecoEta_,"muonRecoEta/F");
    tree_->Branch("muonRecoPhi",&muonRecoPhi_,"muonRecoPhi/F");



    tree_->Branch("IsoLevelMuonDeltaR",&IsoMuonDeltaR_,"IsoLevelMuonDeltaR/F");
    tree_->Branch("IsoLevelMuonPTJet",&IsoMuonPTJet_,"IsoLevelMuonPTJet/F");
    tree_->Branch("IsoLevelMuonRelPTJet",&IsoMuonPTRelJet_,"IsoLevelMuonRelPTJet/F");
    tree_->Branch("muonIsoPt",&muonIsoPt_,"muonIsoPt/F");
    tree_->Branch("muonIsoEta",&muonIsoEta_,"muonIsoEta/F");
    tree_->Branch("muonIsoPhi",&muonIsoPhi_,"muonIsoPhi/F");

    tree_->Branch("RecoLevelElecDeltaR",&RecoElecDeltaR_,"RecoLevelElecDeltaR/F");
    tree_->Branch("RecoLevelElecPTJet",&RecoElecPTJet_,"RecoLevelElecPTJet/F");
    tree_->Branch("RecoLevelElecRelPTJet",&RecoElecPTRelJet_,"RecoLevelElecRelPTJet/F");
    tree_->Branch("RecoVsGenLevelElecDeltaR",&RecoGenMuDeltaR_,"RecoVsGenLevelElecDeltaR/F");
    tree_->Branch("ElecRecoPt",&elecRecoPt_,"ElecRecoPt/F");
    tree_->Branch("ElecRecoEta",&elecRecoEta_,"ElecRecoEta/F");
    tree_->Branch("ElecRecoPhi",&elecRecoPhi_,"ElecRecoPhi/F");



    tree_->Branch("IsoLevelElecDeltaR",&IsoElecDeltaR_,"IsoLevelElecDeltaR/F");
    tree_->Branch("IsoLevelElecPTJet",&IsoElecPTJet_,"IsoLevelElecPTJet/F");
    tree_->Branch("IsoLevelElecRelPTJet",&IsoElecPTRelJet_,"IsoLevelElecRelPTJet/F");
    tree_->Branch("ElecIsoPt",&elecIsoPt_,"ElecIsoPt/F");
    tree_->Branch("ElecIsoEta",&elecIsoEta_,"ElecIsoEta/F");
    tree_->Branch("ElecIsoPhi",&elecIsoPhi_,"ElecIsoPhi/F");




    // test if the cs is the same as the selected one from the matching
    tree_->Branch("nMuInIsoMuCollection",&nMuInIsoMuCollection_,"nMuInIsoMuCollection/I");
    tree_->Branch("muPromtMatched",&muPromtMatched_,"muPromtMatched/I");


    // plotting values
    tree_->Branch("HT",&ht_,"HT/F");
    tree_->Branch("MHT",&mht_,"MHT/F");
    tree_->Branch("NJets",&nJets_,"NJets/s");
    tree_->Branch("Weight",&eventWeight_,"Weight/F");
    tree_->Branch("MT",&mt_,"MT/F");
    tree_->Branch("NVtx",&nV_,"NVtx/s");
    tree_->Branch("IsExpectation",&isExpectation_,"IsExpectation/I");

	// testing
	tree_->Branch("ntau",&ntau_,"ntau/I");
	tree_->Branch("ntauMu",&ntauMu_,"ntauMu/I");
	tree_->Branch("ntauElec",&ntauElec_,"ntauElec/I");

	// gen values for top b tagging
	tree_->Branch("nTop",&nTop_,"nTop/I");
	tree_->Branch("nTopB",&nTopB_,"nTopB/I");
	tree_->Branch("nTopW",&nTopW_,"nTopW/I");
	tree_->Branch("nTopMuNu",&nTopMuNu_,"nTopMuNu/I");
	tree_->Branch("nTopMu",&nTopMu_,"nTopMu/I");

	tree_->Branch("TopPT",&TopPT_,"TopPT/F");
	tree_->Branch("BTopPT",&BTopPT_,"BTopPT/F");
	tree_->Branch("WTopPT",&WTopPT_,"WTopPT/F");
	tree_->Branch("WTopEta",&WTopEta_,"WTopEta/F");
	tree_->Branch("WTopPhi",&WTopPhi_,"WTopPhi/F");
	tree_->Branch("MuNuTopPT",&MuNuTopPT_,"MuNuTopPT/F");
	tree_->Branch("MuTopPT",&MuTopPT_,"MuTopPT/F");
	tree_->Branch("ElecTopPT",&ElecTopPT_,"ElecTopPT/F");

	tree_->Branch("BMuTopDeltaR",&BMuTopDeltaR_,"BMuTopDeltaR/F");
	tree_->Branch("promtMuMetCombinedPT",&promtMuMetCombinedPT_,"promtMuMetCombinedPT/F");
	tree_->Branch("wTopMassDifRecoGenPt",&wTopMassDifRecoGenPt_,"wTopMassDifRecoGenPt/F");
	tree_->Branch("promtMuMetCombinedEta",&promtMuMetCombinedEta_,"promtMuMetCombinedEta/F");
	tree_->Branch("wTopMassDifRecoGenEta",&wTopMassDifRecoGenEta_,"wTopMassDifRecoGenEta/F");
	tree_->Branch("promtMuMetCombinedPhi",&promtMuMetCombinedPhi_,"promtMuMetCombinedPhi/F");
	tree_->Branch("wTopMassDifRecoGenPhi",&wTopMassDifRecoGenPhi_,"wTopMassDifRecoGenPhi/F");
	tree_->Branch("mttRecoMuMet",&mttRecoMuMet_,"mttRecoMuMet/F");
	tree_->Branch("mttGen",&mttGen_,"mttGen/F");
	tree_->Branch("mtt",&mtt_,"mtt/F");

	// mtw for all reco muons
	tree_->Branch("recoMtw1",&recoMtw1_,"recoMtw1/F");
	tree_->Branch("recoMuDeltaPTClosestJet1",&recoMuDeltaPTClosestJet1_,"recoMuDeltaPTClosestJet1/F");
	tree_->Branch("recoMuDeltaRClosestJet1",&recoMuDeltaRClosestJet1_,"recoMuDeltaRClosestJet1/F");
	tree_->Branch("recoMtw2",&recoMtw2_,"recoMtw2/F");
	tree_->Branch("recoMuDeltaPTClosestJet2",&recoMuDeltaPTClosestJet2_,"recoMuDeltaPTClosestJet2/F");
	tree_->Branch("recoMuDeltaRClosestJet2",&recoMuDeltaRClosestJet2_,"recoMuDeltaRClosestJet2/F");
	tree_->Branch("recoMtw3",&recoMtw3_,"recoMtw3/F");
	tree_->Branch("recoMuDeltaPTClosestJet3",&recoMuDeltaPTClosestJet3_,"recoMuDeltaPTClosestJet3/F");
	tree_->Branch("recoMuDeltaRClosestJet3",&recoMuDeltaRClosestJet3_,"recoMuDeltaRClosestJet3/F");
	tree_->Branch("recoMtw4",&recoMtw4_,"recoMtw4/F");
	tree_->Branch("recoMuDeltaPTClosestJet4",&recoMuDeltaPTClosestJet4_,"recoMuDeltaPTClosestJet4/F");
	tree_->Branch("recoMuDeltaRClosestJet4",&recoMuDeltaRClosestJet4_,"recoMuDeltaRClosestJet4/F");
	tree_->Branch("recoMtw5",&recoMtw5_,"recoMtw5/F");
	tree_->Branch("recoMuDeltaPTClosestJet5",&recoMuDeltaPTClosestJet5_,"recoMuDeltaPTClosestJet5/F");
	tree_->Branch("recoMuDeltaRClosestJet5",&recoMuDeltaRClosestJet5_,"recoMuDeltaRClosestJet5/F");

	tree_->Branch("nomNonPromtMu",&nomNonPromtMu_,"nomNonPromtMu/I");
	tree_->Branch("nonPromtMu",nonPromtMu_,"nonPromtMu_/I[10]");
	tree_->Branch("nonPromtMuPt",nonPromtMuPt_,"nonPromtMuPt/F[10]");
	tree_->Branch("nonPromtMuEta",nonPromtMuEta_,"nonPromtMuEta/F[10]");
	tree_->Branch("nonPromtMuPhi",nonPromtMuPhi_,"nonPromtMuPhi/F[10]");
	tree_->Branch("nonPromtMuDeltaR",nonPromtMuDeltaR_,"nonPromtMuDeltaR/F[10]");
	tree_->Branch("nonPromtMuDeltaPT",nonPromtMuDeltaPT_,"nonPromtMuDeltaPT/F[10]");

	tree_->Branch("nomMHTJets",&nomMHTJets_,"nomMHTJets/I");
	tree_->Branch("MHTJetsPT",MHTJetsPT_,"MHTJetsPT/F[20]");
	tree_->Branch("MHTJetsEta",MHTJetsEta_,"MHTJetsEta/F[20]");
	tree_->Branch("MHTJetsPhi",MHTJetsPhi_,"MHTJetsPhi/F[20]");

}

// ------------ method called once each job just after ending the event loop  ------------
void 
RecoLeptonStudy::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
void 
RecoLeptonStudy::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
RecoLeptonStudy::endRun(edm::Run const&, edm::EventSetup const&)
{

}

// ------------ method called when starting to processes a luminosity block  ------------
void 
RecoLeptonStudy::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
RecoLeptonStudy::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
RecoLeptonStudy::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

void
RecoLeptonStudy::ResetValues()
{

	tauFound_		=0;
	muonPTAccPassed_	=-100;
	elecPTAccPassed_	=-100;
	muonNumberRecoID_	=-100;
	elecNumberRecoID_	=-100;
	muonIDPassed_		=-100;
	muonIDFailed_		=-100;
	elecIDPassed_		=-100;
	elecIDFailed_		=-100;
	muonRecoPt_		=-100;
	muonRecoEta_		=-100;
	muonRecoPhi_		=-100;
	elecRecoPt_		=-100;
	elecRecoEta_		=-100;
	elecRecoPhi_		=-100;
	muonGenPt_		=-100;
	muonGenEta_		=-100;
	muonGenPhi_		=-100;
	elecGenPt_		=-100;
	elecGenEta_		=-100;
	elecGenPhi_		=-100;
	deltaGenR_		=-100;
	closestJetToMuonGenPt_	=-100;
	closestJetToElecGenPt_	=-100;
	mtw_			=-100;
	mt_			=-100;
	mtwElec_		=-100;
	RecoMuonDeltaR_		=-100;
	RecoMuonPTJet_		=-100;
	RecoMuonPTRelJet_	=-100;
	IsoMuonDeltaR_		=-100;
	IsoMuonPTJet_		=-100;
	IsoMuonPTRelJet_	=-100;
	RecoGenMuDeltaR_	=-100;
	muonIsoPt_		=-100;
	muonIsoEta_		=-100;
	muonIsoPhi_		=-100;
	RecoElecDeltaR_		=-100;
	RecoElecPTJet_		=-100;
	RecoElecPTRelJet_	=-100;
	IsoElecDeltaR_		=-100;
	IsoElecPTJet_		=-100;
	IsoElecPTRelJet_	=-100;
	RecoGenElecDeltaR_	=-100;
	elecIsoPt_		=-100;
	elecIsoEta_		=-100;
	elecIsoPhi_		=-100;
	genPt_			=-100;
	genEta_			=-100;
	genPhi_			=-100;
	
	nGenMu_ =0;
	nGenElec_ =0;
	tauFound_ =0;
	eventWeight_=0;
	nAccMu_=0;
	nAccElec_=0;
	nRecoMu_=0;
	nRecoElec_=0;
	nIsoMu_=0;
	isExpectation_ = 0;
	nIsoElec_=0;

	// TESTING VARIABLES
	nMuInIsoMuCollection_=0;
 	// additonal variables for plotting
	ht_=-100;
	nJets_=0;
	mht_=-100;
	nV_ =0;

	// test
	ntau_=0;
	ntauMu_=0;
	ntauElec_=0;

	// gen values for top b tagging
	nTop_=0;
	nTopW_=0;
	nTopB_=0;
	nTopMuNu_=0;
	nTopMu_=0;
	nTopElec_=0;

	TopPT_=-100;
	BTopPT_=-100;
	WTopPT_=-100;
	MuNuTopPT_=-100;
	MuTopPT_=-100;

	TopEta_=-100;
	BTopEta_=-100;
	WTopEta_=-100;
	MuNuTopEta_=-100;
	MuTopEta_=-100;

	TopPhi_=-100;
	BTopPhi_=-100;
	WTopPhi_=-100;
	MuNuTopPhi_=-100;
	MuTopPhi_=-100;



	ElecTopPT_=-100;

	BMuTopDeltaR_=-100;
	mtt_=-100;
	mttGen_=-100;
	mttRecoMuMet_=-100;
	promtMuMetCombinedPT_=-100;
	promtMuMetCombinedEta_=-100;
	promtMuMetCombinedPhi_=-100;
	wTopMassDifRecoGenPt_=-10000;
	wTopMassDifRecoGenPt_=-10000;
	wTopMassDifRecoGenPt_=-10000;

nTopB_=0;
nTopMu_=0;
nTopMuNu_=0;
nTopW_=0;
TopPT_=-100;
nTop_=0;
recoMtw1_=-100;
recoMtw2_=-100;
recoMtw3_=-100;
recoMtw4_=-100;
recoMtw5_=-100;
recoMuDeltaPTClosestJet1_=-1;
recoMuDeltaPTClosestJet2_=-1;
recoMuDeltaPTClosestJet3_=-1;
recoMuDeltaPTClosestJet4_=-1;
recoMuDeltaPTClosestJet5_=-1;

}


void
RecoLeptonStudy::MuonFound(reco::GenParticleCollection::const_iterator cand, unsigned int i)
{
	nGenMu_+=1;
	muonGenPt_  = cand->daughter(i)->pt();
	muonGenEta_ = cand->daughter(i)->eta();
	muonGenPhi_ = cand->daughter(i)->phi();
	// true if the muon is out of the detector acceptance
			genPt_ = muonGenPt_;
			genEta_= muonGenEta_;
			genPhi_=muonGenPhi_;

}

void
RecoLeptonStudy::ElecFound(reco::GenParticleCollection::const_iterator cand, unsigned int i)
{
	nGenElec_+=1;
		elecGenPt_  = cand->daughter(i)->pt();
		elecGenEta_ = cand->daughter(i)->eta();
		elecGenPhi_ = cand->daughter(i)->phi();
			genPt_ = elecGenPt_;
			genEta_= elecGenEta_;
			genPhi_= elecGenPhi_;

		// true if the elec is out of the detector acceptance


}

void
RecoLeptonStudy::TauFound(const reco::Candidate* tau)
{

	ntau_+=1;
	for (unsigned int ii=0; ii < tau->numberOfDaughters(); ii++)
	{
		// true if the selected tau is not the finally decaying tau but has an intermediate tau or w in the decay
		if (abs(tau->daughter(ii)->pdgId()) == 15 || abs(tau->daughter(ii)->pdgId()) == 24) TauFound(tau->daughter(ii));
		if (abs(tau->daughter(ii)->pdgId() ) == 13 )
		{
			//muon found
			ntauMu_+=1;
			nGenMu_+=1;
			muonGenPt_  = tau->daughter(ii)->pt();
			muonGenEta_ = tau->daughter(ii)->eta();
			muonGenPhi_ = tau->daughter(ii)->phi();
			genPt_ = muonGenPt_;
			genEta_= muonGenEta_;
			genPhi_=muonGenPhi_;
		}
		if (abs(tau->daughter(ii)->pdgId() ) == 11 )
		{
			//elec found
			ntauElec_+=1;
			nGenElec_+=1;
			elecGenPt_  = tau->daughter(ii)->pt();
			elecGenEta_ = tau->daughter(ii)->eta();
			elecGenPhi_ = tau->daughter(ii)->phi();
			genPt_ = elecGenPt_;
			genEta_= elecGenEta_;
			genPhi_= elecGenPhi_;

		}


	}
/*	for (unsigned int itau=0; itau < cand->daughter(i)->numberOfDaughters(); itau++)
	{	
	std::cout<<"RecoLeptonStudy::TauFound!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1"<<std::endl;
	std::cout<<"RecoLeptonStudy::Tau"<<cand->daughter(i)->pdgId()<<std::endl;
	std::cout<<"RecoLeptonStudy::Tau"<<cand->daughter(i)->daughter(itau)->daughter(0)->pdgId()<<std::endl;
	std::cout<<"RecoLeptonStudy::Tau"<<cand->daughter(i)->daughter(itau)->daughter(1)->pdgId()<<std::endl;
		if (abs(cand->daughter(i)->daughter(itau)->pdgId() ) ==13) 
		{
		std::cout<<"RecoLeptonStudy::MuonFoundfrom Tau!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
			ntauMu_+=1;
			nGenMu_+=1;
			muonGenPt_  = cand->daughter(i)->daughter(itau)->pt();
			muonGenEta_ = cand->daughter(i)->daughter(itau)->eta();
			muonGenPhi_ = cand->daughter(i)->daughter(itau)->phi();
		// true if the muon is out of the detector acceptance

		}
		if (abs(cand->daughter(i)->daughter(itau)->pdgId() ) ==11)  
		{
			nGenElec_+=1;
			elecGenPt_  = cand->daughter(i)->daughter(itau)->pt();
			elecGenEta_ = cand->daughter(i)->daughter(itau)->eta();
			elecGenPhi_ = cand->daughter(i)->daughter(itau)->phi();
			// true if the elec is out of the detector acceptance

		}
	}
*/
}

std::pair <double,double> RecoLeptonStudy::DRToClosestJet(const edm::Event& iEvent, edm::InputTag caloJetTag, double lepEta, double lepPhi)
{
	edm::Handle <edm::View<reco::CaloJet> >jets;
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


	return std::make_pair(resultDR,resultJetPt);
}



double
RecoLeptonStudy::MTWCalculator(const edm::Event& iEvent, edm::InputTag metTag, double lepPT, double lepPhi)
{
  edm::Handle< edm::View<reco::Candidate> > met;
  iEvent.getByLabel(metTag,met);
  double metPT = met->at(0).pt();
//  std::cout<<"MTWCalculator:metPT"<<metPT<<std::endl;
//  std::cout<<"MTWCalculator:met->at(0).phi()"<<met->at(0).phi()<<std::endl;
 // dR = deltaR(met->at(0).eta(),met->at(0).phi(),lepEta,lepPhi);
    double deltaPhi =reco::deltaPhi(lepPhi, met->at(0).phi());
//  std::cout<<"MTWCalculator:deltaPhi"<<deltaPhi<<std::endl;
//    std::cout<<"MTWCalculator:MTW"<<sqrt(2*lepPT*metPT*(1-cos(deltaPhi)) )<<std::endl;
    return sqrt(2*lepPT*metPT*(1-cos(deltaPhi)) );

}

edm::View <reco::Candidate>::const_iterator
RecoLeptonStudy::LeptonMatch(const edm::View <reco::Candidate>  &MuID, Float_t lepGenEta, Float_t lepGenPhi, Float_t lepGenPt)
{
	edm::View <reco::Candidate>::const_iterator result=MuID.end();
	double minRecoDeltaR = 1000;
	double RecoPhi=0;
	double RecoEta=0;
       	double RecoPt=0;
	for( edm::View <reco::Candidate>::const_iterator MuIDCand = MuID.begin(); MuIDCand!=MuID.end();MuIDCand++)
	{

		RecoPhi=MuIDCand->phi();
		RecoEta=MuIDCand->eta();
		RecoPt=MuIDCand->pt();

		if (deltaR(lepGenEta,lepGenPhi,RecoEta,RecoPhi) < 0.2 && abs(lepGenPt-RecoPt)/RecoPt < 0.2 && deltaR(lepGenEta,lepGenPhi,RecoEta,RecoPhi) < minRecoDeltaR  )
		{
			if (minRecoDeltaR < 0.21)
			{	
				// true if the new found muon is closer than 0.1 but the old one isnt
				if ( deltaR(lepGenEta,lepGenPhi,RecoEta,RecoPhi) <0.1 && minRecoDeltaR >0.1) result = MuIDCand;
				if (deltaR(lepGenEta,lepGenPhi,RecoEta,RecoPhi) <0.1 && minRecoDeltaR <0.1)result = MuID.end();
			}
			
			result = MuIDCand;
			minRecoDeltaR= deltaR(lepGenEta,lepGenPhi,RecoEta,RecoPhi);

		}
		
	}
	return result;

}

//define this as a plug-in
DEFINE_FWK_MODULE(RecoLeptonStudy);
