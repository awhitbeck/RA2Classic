// -*- C++ -*-
//
// Package:    MCEffCalculator
// Class:      MCEffCalculator
// 
/**\class MCEffCalculator MCEffCalculator.cc RA2Classic/MCEffCalculator/src/MCEffCalculator.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Arne-Rasmus Draeger,,,uni-hamburg
//         Created:  Thu Sep 27 10:50:02 CEST 2012
// $Id: MCEffCalculator.cc,v 1.12 2012/11/19 11:16:27 adraeger Exp $
//
//


// system include files
#include "RA2Classic/LostLeptonBkg/interface/MCEffCalculator.h"
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
MCEffCalculator::MCEffCalculator(const edm::ParameterSet& iConfig)

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

}


MCEffCalculator::~MCEffCalculator()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
MCEffCalculator::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
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

   edm::Handle <edm::View <reco::Candidate> > MuPromtMatched;
   iEvent.getByLabel(muonPromtMatchedTag_,MuPromtMatched);

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

  

  if (MuPromtMatched.isValid() )
  {
	muPromtMatched_ = MuPromtMatched->size();
  }



   // select muon id 13 on gen level
   // iterates over all gen particles
   for(reco::GenParticleCollection::const_iterator cand = genParticles->begin(); cand!=genParticles->end(); ++cand) 
   {
	// demands only w bosons from the hard interaction
    	if(abs(cand->pdgId())!=24 || cand->status()!=3) continue;
	// only not hadronically decaying w will survive

	for (unsigned int i=0; i < cand->numberOfDaughters(); i++)
	{
		// muon
		if (abs(cand->daughter(i)->pdgId() ) == 13) 
		{
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
			TauFound(cand->daughter(i));
			if(cand->daughter(i)->status()==2)std::cout<<"tau has status 2"<<std::endl;
		}
	
	}
	
   }
genDeltaR_=DRToClosestJet(iEvent, caloJetTag_,genEta_,genPhi_).first;
genPTJet_=DRToClosestJet(iEvent, caloJetTag_,genEta_,genPhi_).second;
genPTRelJet_=genPTJet_/genPt_;


// one muon has been found the three different efficiencies will be determined now. first acc than reco and final iso the results will be stored in th2f histogramms.

   if (nGenMu_==1 && nGenElec_==0)
   {
	deltaGenR_ = DRToClosestJet(iEvent,caloJetTag_, muonGenEta_, muonGenPhi_).first;
	closestJetToMuonGenPt_ = DRToClosestJet(iEvent,caloJetTag_, muonGenEta_,muonGenPhi_).second;

				RecoMuonDeltaR_=DRToClosestJet(iEvent, caloJetTag_,muonGenEta_,muonGenPhi_).first;
				RecoMuonPTJet_=DRToClosestJet(iEvent, caloJetTag_,muonGenEta_,muonGenPhi_).second;
				RecoMuonPTRelJet_=RecoMuonPTJet_/muonRecoPt_;

	// decided if the muon passed or failed the acc criteria 
	if( std::abs(muonGenEta_)> maxMuonEta_ || muonGenPt_ < minMuonPt_ )
	{	
		MuonAccFailedTH2F_->Fill(mht_,nJets_,eventWeight_);

		MuonAccFailedTH1F_->Fill(muonGenPt_,eventWeight_);
		MuonAccFailed2TH1F_->Fill(mht_,eventWeight_);
		nAccMu_=-1;
		isExpectation_+=1;


		
	}
	// else the muon is within the acceptance
	else 
	{
		nAccMu_=+1;
		// This histogramm is used for the actual acceptance caluclation
		MuonAccPassedTH2F_->Fill(mht_,nJets_,eventWeight_);
		MuonAccPassedTH1F_->Fill(muonGenPt_,eventWeight_);
		MuonAccPassed2TH1F_->Fill(mht_,eventWeight_);
		muonPTAccPassed_=muonGenPt_;
		///////////////////// ID checking
		//check if ID criteria are matched
		muonNumberRecoID_=MuID->size();
		//true if no Mu has been reconstructed
		edm::View <reco::Candidate>::const_iterator itRecoMu = LeptonMatch(*MuID, muonGenEta_, muonGenPhi_);
		//true if reco muon matched

		if (itRecoMu != MuID->end() )
			{
			muonRecoPt_=itRecoMu->pt();
			muonRecoEta_ = itRecoMu->eta();
			muonRecoPhi_ = itRecoMu->phi();
			RecoGenMuDeltaR_=deltaR(muonGenEta_,muonGenPhi_,muonRecoEta_,muonRecoPhi_);
				
				nRecoMu_=1;
				RecoMuonDeltaR_=DRToClosestJet(iEvent, caloJetTag_,muonRecoEta_,muonRecoPhi_).first;
				RecoMuonPTJet_=DRToClosestJet(iEvent, caloJetTag_,muonRecoEta_,muonRecoPhi_).second;
				RecoMuonPTRelJet_=RecoMuonPTJet_/muonRecoPt_;
				muonIDPassedTH2F_->Fill(RecoMuonDeltaR_,muonRecoPt_/RecoMuonPTJet_,eventWeight_);
				muonIDPassed2TH2F_->Fill(RecoMuonDeltaR_,muonRecoPt_,eventWeight_);
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
						IsoMuonPTRelJet_=RecoMuonPTJet_/muonRecoPt_;
						muonIsoPassedTH2F_->Fill(RecoMuonDeltaR_,muonRecoPt_/RecoMuonPTJet_,eventWeight_);
						muonIsoPassed2TH2F_->Fill(RecoMuonDeltaR_,muonRecoPt_,eventWeight_);
						mtw_= MTWCalculator(iEvent, metTag_,muonIsoPt_,muonIsoPhi_);
						MTWTH2F_->Fill(mtw_,mht_);
						for (unsigned int i=0; i<nJets_;i++)
						{
							if( abs(htJets->at(i).pt() - muonIsoPt_)/muonIsoPt_ < 0.1 && deltaR(htJets->at(i).eta(),htJets->at(i).phi(), muonIsoEta_,muonIsoPhi_) < 0.2 ) nJets_-=1;
						}



					}
					if(nIsoMu_>0) break;
				}

				if (nIsoMu_==0)
				{
					isExpectation_=1;
					nIsoMu_=-1;
					muonIsoFailedTH2F_->Fill(RecoMuonDeltaR_,muonRecoPt_/RecoMuonPTJet_,eventWeight_);
					muonIsoFailed2TH2F_->Fill(RecoMuonDeltaR_,muonRecoPt_,eventWeight_);
				}
			}
		
		// no gen muon could be matched to a reco muon
		if (nRecoMu_==0)
		{
			nRecoMu_=-1;
			muonIDFailedTH2F_->Fill(deltaGenR_,muonGenPt_/closestJetToMuonGenPt_,eventWeight_);
			muonIDFailed2TH2F_->Fill(deltaGenR_,muonGenPt_,eventWeight_);
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
				RecoElecPTRelJet_=RecoElecPTJet_/elecRecoPt_;

	// decided if the elec passed or failed the acc criteria 
	if( std::abs(elecGenEta_)> maxElecEta_ || elecGenPt_ < minElecPt_)
	{	
		ElecAccFailedTH2F_->Fill(mht_,nJets_,eventWeight_);

		ElecAccFailedTH1F_->Fill(elecGenPt_,eventWeight_);
		ElecAccFailed2TH1F_->Fill(mht_,eventWeight_);
		nAccElec_=-1;
		isExpectation_+=1;


		
	}
	// else the elec is within the acceptance
	else 
	{
		nAccElec_=+1;
		// This histogramm is used for the actual acceptance caluclation
		ElecAccPassedTH2F_->Fill(mht_,nJets_,eventWeight_);
		ElecAccPassedTH1F_->Fill(elecGenPt_,eventWeight_);
		ElecAccPassed2TH1F_->Fill(mht_,eventWeight_);
		elecPTAccPassed_=elecGenPt_;
		///////////////////// ID checking
		//check if ID criteria are matched
		elecNumberRecoID_=ElecID->size();
		//true if no elec has been reconstructed

		edm::View <reco::Candidate>::const_iterator itRecoElec = LeptonMatch(*ElecID, elecGenEta_, elecGenPhi_);
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
				RecoElecPTRelJet_=RecoElecPTJet_/elecRecoPt_;
				elecIDPassedTH2F_->Fill(RecoElecDeltaR_,elecRecoPt_/RecoElecPTJet_,eventWeight_);
				elecIDPassed2TH2F_->Fill(RecoElecDeltaR_,elecRecoPt_,eventWeight_);
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
							IsoElecPTRelJet_=RecoElecPTJet_/elecRecoPt_;
							elecIsoPassedTH2F_->Fill(RecoElecDeltaR_,elecRecoPt_/RecoElecPTJet_,eventWeight_);
							elecIsoPassed2TH2F_->Fill(RecoElecDeltaR_,elecRecoPt_,eventWeight_);
							for (unsigned int i=0; i<nJets_;i++)
							{
								if( abs(htJets->at(i).pt() - elecIsoPt_)/elecIsoPt_ < 0.1 && deltaR(htJets->at(i).eta(),htJets->at(i).phi(), elecIsoEta_,elecIsoPhi_) < 0.3 ) nJets_-=1;
							}


						}
					if(nIsoElec_>0) break;
					}
				}
				if (nIsoElec_==0)
				{
					isExpectation_+=1;
					nIsoElec_=-1;
					elecIsoFailedTH2F_->Fill(RecoElecDeltaR_,elecRecoPt_/RecoElecPTJet_,eventWeight_);
					elecIsoFailed2TH2F_->Fill(RecoElecDeltaR_,elecRecoPt_,eventWeight_);
				}
			}
		// no gen elec could be matched to a reco elec
		if (nRecoElec_==0)
		{
			nRecoElec_=-1;
			elecIDFailedTH2F_->Fill(deltaGenR_,elecGenPt_/closestJetToElecGenPt_,eventWeight_);
			elecIDFailed2TH2F_->Fill(deltaGenR_,elecGenPt_,eventWeight_);
			isExpectation_ =1;
		}
		///////////////////// ID checking DONE

	}
   }


   leptons_ = nGenMu_ + nGenElec_;
// Resets all values to default if more than 1 gen muon or gen elec is found in the event
   if (nGenMu_==2 || (nGenMu_+nGenElec_)>1)
   {

   }
   if (nGenElec_==2 || (nGenMu_+nGenElec_) > 1)
   {

   }

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
  tree_->Fill();
}



// ------------ method called once each job just before starting event loop  ------------
void 
MCEffCalculator::beginJob()
{
	double deltaRbins []={0, 0.5, 0.65, 0.75, 1, 1.1, 1.5, 2, 3};
	double deltaRbinsIso []={0, 0.5, 0.75, 1, 1.1, 1.5, 2, 3};
	int DeltaRbins = 8;
	int DeltaRbinsIso = 7;
//	double deltaRbins []={0, 0.1, 0.2, 0.3, 0.4, 0.5,0.6,0.7,0.8,0.9,1,1.5,2,2.5,3};
	std::cout<<"deltaRbins created"<<std::endl;
	std::cout<<"MinMuonPTforAcc"<<minMuonPt_<<std::endl;
	std::cout<<"MinElecPTforAcc"<<minElecPt_<<std::endl;
	double ptbins []={0, 0.25, 0.5, 1, 2, 5};
	int Ptbins = 5;

	double lepPtbins []={10,20,30,50,70,100,200};
	int LepPtbins = 6;
//	double ptbins [] = {0, 0.1, 0.2, 0.3, 0.4, 0.5,0.6,0.7,0.8,0.9,1,1.5,2,2.5,3};
	// binning for the mtw MHT distribution
	double mhtbins []={200,250,300,400,600,1600};
	double nJetBins []={0,2,4,6,12};
	int NJetBins = 4;
	int MhtBins = 5;
  	edm::Service<TFileService> fs;
  	tree_ = fs->make<TTree>(treeName_,treeName_);
	// book all the result plots
	MuonAccFailedTH2F_ =fs->make<TH2F>("MuonAccFailed", "MuonAccFailed",MhtBins,mhtbins,NJetBins,nJetBins);
	MuonAccPassedTH2F_ =fs->make<TH2F>("MuonAccPassed", "MuonAccPassed",MhtBins,mhtbins,NJetBins,nJetBins);
	ElecAccFailedTH2F_ =fs->make<TH2F>("ElecAccFailed", "ElecAccFailed",MhtBins,mhtbins,NJetBins,nJetBins);
	ElecAccPassedTH2F_ =fs->make<TH2F>("ElecAccPassed", "ElecAccPassed",MhtBins,mhtbins,NJetBins,nJetBins);

	muonIDFailedTH2F_ = fs->make<TH2F>("MuonRecoFailed", "MuonRecoFailed",DeltaRbins,deltaRbins,Ptbins,ptbins);
	muonIDPassedTH2F_ = fs->make<TH2F>("MuonRecoPassed", "MuonRecoPassed",DeltaRbins,deltaRbins,Ptbins,ptbins);
	muonIsoFailedTH2F_ = fs->make<TH2F>("muonIsoFailed","muonIsoFailed",DeltaRbinsIso,deltaRbinsIso,Ptbins,ptbins);
	muonIsoPassedTH2F_ = fs->make<TH2F>("muonIsoPassed","muonIsoPassed",DeltaRbinsIso,deltaRbinsIso,Ptbins,ptbins);

	muonIDFailed2TH2F_ = fs->make<TH2F>("MuonRecoFailed2", "MuonRecoFailed2",DeltaRbins,deltaRbins,LepPtbins,lepPtbins);
	muonIDPassed2TH2F_ = fs->make<TH2F>("MuonRecoPassed2", "MuonRecoPassed2",DeltaRbins,deltaRbins,LepPtbins,lepPtbins);
	muonIsoFailed2TH2F_ = fs->make<TH2F>("muonIsoFailed2","muonIsoFailed2",DeltaRbinsIso,deltaRbinsIso,LepPtbins,lepPtbins);
	muonIsoPassed2TH2F_ = fs->make<TH2F>("muonIsoPassed2","muonIsoPassed2",DeltaRbinsIso,deltaRbinsIso,LepPtbins,lepPtbins);

	MuonAccPassedTH1F_ = fs->make<TH1F>("muonAccPassed","muonAccPassed",40,0,200);
	MuonAccPassed2TH1F_ = fs->make<TH1F>("muonAccPassed2","muonAccPassed2",MhtBins,mhtbins);
	MuonAccFailedTH1F_ = fs->make<TH1F>("muonAccFailed","muonAccFailed",40,0,200);
	MuonAccFailed2TH1F_ = fs->make<TH1F>("muonAccFailed2","muonAccFailed2",MhtBins,mhtbins);
	MuonMTPassedTH2F_ = fs->make<TH2F>("muonMT","muonMT",1,0,1,1,0,1);


	elecIDFailedTH2F_ = fs->make<TH2F>("elecIdFailed","elecIdFailed",DeltaRbins,deltaRbins,Ptbins,ptbins);
	elecIDPassedTH2F_ = fs->make<TH2F>("elecIdPassed","elecIdPassed",DeltaRbins,deltaRbins,Ptbins,ptbins);
	elecIsoFailedTH2F_ = fs->make<TH2F>("elecIsoFailed","elecIsoFailed",DeltaRbins,deltaRbins,Ptbins,ptbins);
	elecIsoPassedTH2F_ = fs->make<TH2F>("elecIsoPassed","elecIsoPassed",DeltaRbins,deltaRbins,Ptbins,ptbins);

	elecIDFailed2TH2F_ = fs->make<TH2F>("elecIdFailed2","elecIdFailed2",DeltaRbins,deltaRbins,LepPtbins,lepPtbins);
	elecIDPassed2TH2F_ = fs->make<TH2F>("elecIdPassed2","elecIdPassed2",DeltaRbins,deltaRbins,LepPtbins,lepPtbins);
	elecIsoFailed2TH2F_ = fs->make<TH2F>("elecIsoFailed2","elecIsoFailed2",DeltaRbinsIso,deltaRbinsIso,LepPtbins,lepPtbins);
	elecIsoPassed2TH2F_ = fs->make<TH2F>("elecIsoPassed2","elecIsoPassed2",DeltaRbinsIso,deltaRbinsIso,LepPtbins,lepPtbins);

	ElecAccPassedTH1F_ = fs->make<TH1F>("elecAccPassed","elecAccPassed",40,0,200);
	ElecAccPassed2TH1F_ = fs->make<TH1F>("elecAccPassed2","elecAccPassed2",MhtBins,mhtbins);
	ElecAccFailedTH1F_ = fs->make<TH1F>("elecAccFailed","elecAccFailed",40,0,200);
	ElecAccFailed2TH1F_ = fs->make<TH1F>("elecAccFailed2","elecAccFailed2",MhtBins,mhtbins);

	// MTW 
	MTWTH2F_ =fs->make<TH2F>("MTW","MTW",400,0,400,MhtBins,mhtbins); 
	
	// special HT1
	lepDeltaR_ = fs->make<TH1F>("lepDeltaR","lepDeltaR",40,0,4);


//create branches in the tree
    
    tree_->Branch("nLeptons",&leptons_,"nLeptons/I");
    tree_->Branch("nGenMu",&nGenMu_,"nGenMu/I");
    tree_->Branch("nGenElec",&nGenElec_,"nGenElec/I");
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

    tree_->Branch("IsoLevelMuonDeltaR",&IsoMuonDeltaR_,"IsoLevelMuonDeltaR/F");
    tree_->Branch("IsoLevelMuonPTJet",&IsoMuonPTJet_,"IsoLevelMuonPTJet/F");
    tree_->Branch("IsoLevelMuonRelPTJet",&IsoMuonPTRelJet_,"IsoLevelMuonRelPTJet/F");

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
}

// ------------ method called once each job just after ending the event loop  ------------
void 
MCEffCalculator::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
void 
MCEffCalculator::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
MCEffCalculator::endRun(edm::Run const&, edm::EventSetup const&)
{

}

// ------------ method called when starting to processes a luminosity block  ------------
void 
MCEffCalculator::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
MCEffCalculator::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
MCEffCalculator::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

void
MCEffCalculator::ResetValues()
{


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
}


void
MCEffCalculator::MuonFound(reco::GenParticleCollection::const_iterator cand, unsigned int i)
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
MCEffCalculator::ElecFound(reco::GenParticleCollection::const_iterator cand, unsigned int i)
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
MCEffCalculator::TauFound(const reco::Candidate* tau)
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
	std::cout<<"MCEffCalculator::TauFound!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1"<<std::endl;
	std::cout<<"MCEffCalculator::Tau"<<cand->daughter(i)->pdgId()<<std::endl;
	std::cout<<"MCEffCalculator::Tau"<<cand->daughter(i)->daughter(itau)->daughter(0)->pdgId()<<std::endl;
	std::cout<<"MCEffCalculator::Tau"<<cand->daughter(i)->daughter(itau)->daughter(1)->pdgId()<<std::endl;
		if (abs(cand->daughter(i)->daughter(itau)->pdgId() ) ==13) 
		{
		std::cout<<"MCEffCalculator::MuonFoundfrom Tau!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
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

std::pair <double,double> MCEffCalculator::DRToClosestJet(const edm::Event& iEvent, edm::InputTag caloJetTag, double lepEta, double lepPhi)
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
		if(tempDeltaR<resultDR && jets->at(i).emEnergyFraction() <0.9 && jets->at(i).emEnergyFraction() > 0.05 && jets->at(i).pt()>29.999 )
		{
			resultDR = tempDeltaR;
			resultJetPt = jets->at(i).pt();
		}
	}


	return std::make_pair(resultDR,resultJetPt);
}


double
MCEffCalculator::MTWCalculator(const edm::Event& iEvent, edm::InputTag metTag, double lepPT, double lepPhi)
{
  edm::Handle< edm::View<reco::Candidate> > met;
  iEvent.getByLabel(metTag,met);
  double metPT = met->at(0).pt();
//  std::cout<<"MTWCalculator:metPT"<<metPT<<std::endl;
 // dR = deltaR(met->at(0).eta(),met->at(0).phi(),lepEta,lepPhi);
    double deltaPhi =reco::deltaPhi(lepPhi, met->at(0).phi());
 //   std::cout<<"MTWCalculator:MTW"<<sqrt(2*lepPT*metPT*(1-cos(deltaPhi)) )<<std::endl;
    return sqrt(2*lepPT*metPT*(1-cos(deltaPhi)) );

}

edm::View <reco::Candidate>::const_iterator
MCEffCalculator::LeptonMatch(const edm::View <reco::Candidate>  &MuID, Float_t lepGenEta, Float_t lepGenPhi)
{
	edm::View <reco::Candidate>::const_iterator result=MuID.end();
	double minRecoDeltaR = 1000;
	double RecoPhi=0;
	double RecoEta=0;
	for( edm::View <reco::Candidate>::const_iterator MuIDCand = MuID.begin(); MuIDCand!=MuID.end();MuIDCand++)
	{

		RecoPhi=MuIDCand->phi();
		RecoEta=MuIDCand->eta();

		if (deltaR(lepGenEta,lepGenPhi,RecoEta,RecoPhi) < 0.3 )
		{
			if (minRecoDeltaR < 0.31)
			{	
				// true if the new found muon is closer thatn 0.1 but the old one isnt
				if ( deltaR(lepGenEta,lepGenPhi,RecoEta,RecoPhi) <0.1 && minRecoDeltaR >0.1) result = MuIDCand;
				if (deltaR(lepGenEta,lepGenPhi,RecoEta,RecoPhi) <0.1 && minRecoDeltaR <0.1)result = MuID.end();
			}
			
			if (deltaR(lepGenEta,lepGenPhi,RecoEta,RecoPhi) < minRecoDeltaR )
			{
				result = MuIDCand;
			}
		}
		
	}
	return result;

}

//define this as a plug-in
DEFINE_FWK_MODULE(MCEffCalculator);
