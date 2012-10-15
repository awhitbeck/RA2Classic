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
// $Id: MCEffCalculator.cc,v 1.2 2012/10/15 08:41:58 adraeger Exp $
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
  elecIDTag_ = iConfig.getParameter<edm::InputTag> ("ElecIDTag");
  elecIDISOTag_ = iConfig.getParameter<edm::InputTag> ("ElecIDISOTag");
  jetTag_ = iConfig.getParameter<edm::InputTag> ("JetTag");
  caloJetTag_ =iConfig.getParameter<edm::InputTag> ("CaloJetTag");
  metTag_ = iConfig.getParameter<edm::InputTag> ("METTag");
  genTag_ = iConfig.getParameter<edm::InputTag> ("GenTag"); 
  minMuonPt_ = iConfig.getParameter<double> ("minMuonPt");
  maxMuonEta_ = iConfig.getParameter<double> ("maxMuonEta");
  minElecPt_ = iConfig.getParameter<double> ("minElecPt");
  maxElecEta_ =iConfig.getParameter<double> ("maxElecEta");
  minJetPt_ = iConfig.getParameter<double> ("minJetPt") ;
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
   // get a collection of reco elec.
   edm::Handle <edm::View <reco::Candidate> > ElecID;
   iEvent.getByLabel(elecIDTag_,ElecID);
   edm::Handle <edm::View <reco::Candidate> > ElecIDISO;
   iEvent.getByLabel(elecIDISOTag_,ElecIDISO);
   // get Event weight
   edm::Handle<double> eventWeight;
   iEvent.getByLabel(evtWeightTag_,eventWeight);
   eventWeight_ = *eventWeight;

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
			TauFound(cand,i);
			if(cand->daughter(i)->status()==2)std::cout<<"tau has status 2"<<std::endl;
		}
	
	}




/*
	if(abs(cand->pdgId()) == 13 && cand->status() ==3)
	{
		muonPt_  = cand->pt();
		muonEta_ = cand->eta();
		muonPhi_ = cand->phi();
		// true if the muon is out of the detector acceptance
		if( muonPt_ < minMuonPt_ || muonEta_> maxMuonEta_) 
		{
			std::cout<<"muonAccFailed_="<<muonAccFailed_<<std::endl;
			std::cout<<"muonPt_="<<muonPt_<<std::endl;
			muonAccFailed_=eventWeight_;
			muonAccFailedQuadError_=eventWeight_*eventWeight_;
		}
		else 
		{
			std::cout<<"muonAccPassed_="<<muonAccPassed_<<std::endl;
			std::cout<<"muonPt_="<<muonPt_<<std::endl;
			muonAccPassed_=eventWeight_;
			muonAccPassedQuadError_=eventWeight_*eventWeight_;
		}
	}
	
	if (abs(cand->pdgId()) ==24)
*/
	
   }


// one muon has been found the three different efficiencies will be determined now. first acc than reco and final iso the results will be stored in th2f histogramms.
   if (nGenMu_==1 && nGenElec_==0)
   {
	//test comparison of Muons within the MuID MuIDISO and reco
	nRecoMu_=MuID->size();
	nIsoMu_=MuIDISO->size();
	
	deltaGenR_ = DRToClosestJet(iEvent,caloJetTag_, muonGenEta_, muonGenPhi_).first;
	closestJetToMuonGenPt_ = DRToClosestJet(iEvent,caloJetTag_, muonGenEta_,muonGenPhi_).second;
	
	
	
	std::cout<<"ngenMu_=1 and nGenEl =0"<<std::endl;
	// selects muons with a minimum pt

	// decided if the muon passed or failed the acc/id/iso criteria 
	if( std::abs(muonGenEta_)> maxMuonEta_ && minMuonPt_<muonGenPt_)
	{	
		// This histogramm is used for the actual acceptance caluclation
		MuonAccFailedTH1F_->Fill(muonGenPt_,eventWeight_);
		muonAcc_=-1;
		
		}
	// else the muon is within the acceptance
	else 
	{
		muonAcc_=+1;
		// This histogramm is used for the actual acceptance caluclation
		MuonAccPassedTH1F_->Fill(muonGenPt_,eventWeight_);
		muonPTAccPassed_=muonGenPt_;
		//check if ID criteria are matched
		muonNumberRecoID_=MuID->size();
		//true if no Mu has been reconstructed
		if (MuID->size() ==0)
		{
			std::cout<<"MuID->size()==0 but acc passed"<<std::endl;
					muonIDFailedTH2F_->Fill(deltaGenR_,closestJetToMuonGenPt_/muonGenPt_,eventWeight_);
		}
		else
		{
			std::cout<<"MuID size="<<MuID->size()<<std::endl;
			for( edm::View <reco::Candidate>::const_iterator MuIDCand = MuID->begin(); MuIDCand!=MuID->end();MuIDCand++)
			{
				muonRecoPt_ = MuIDCand->pt();
				muonRecoEta_ = MuIDCand->eta();
				muonRecoPhi_ = MuIDCand->phi();
				// true if the reco and 
				RecoGenMuDeltaR_=deltaR(muonGenEta_,muonGenPhi_,muonRecoEta_,muonRecoPhi_);
				if (deltaR(muonGenEta_,muonGenPhi_,muonRecoEta_,muonRecoPhi_) < 0.3)
				{
					RecoMuonDeltaR_=DRToClosestJet(iEvent, caloJetTag_,muonRecoEta_,muonRecoPhi_).first;
					RecoMuonPTJet_=DRToClosestJet(iEvent, caloJetTag_,muonRecoEta_,muonRecoPhi_).second;
					RecoMuonPTRelJet_=RecoMuonPTJet_/muonRecoPt_;
					muonIDPassedTH2F_->Fill(RecoMuonDeltaR_,RecoMuonPTJet_/muonRecoPt_,eventWeight_);
					std::cout<<"muonIDPassed deltaR:"<<RecoMuonDeltaR_<<std::endl<<"ptCloestJet:"<<RecoMuonPTJet_<<std::endl<<"EventWeight"<<eventWeight_<<std::endl<<std::endl;
					//check if Iso is fulfilled
					if (MuIDISO->size() > 0 )
					{
						for( edm::View <reco::Candidate>::const_iterator MuIDIsoCand = MuIDISO->begin(); MuIDIsoCand!=MuIDISO->end();MuIDIsoCand++)
						{
							muonIsoPt_ = MuIDIsoCand->pt();
							muonIsoEta_ = MuIDIsoCand->eta();
							muonIsoPhi_ = MuIDIsoCand->phi();
							if (deltaR(muonIsoEta_,muonIsoPhi_,muonRecoEta_,muonRecoPhi_) < 0.1)
							{
								IsoMuonDeltaR_=RecoMuonDeltaR_;
								IsoMuonPTJet_=RecoMuonPTJet_;
								IsoMuonPTRelJet_=RecoMuonPTJet_/muonRecoPt_;
								muonIsoPassedTH2F_->Fill(RecoMuonDeltaR_,RecoMuonPTJet_/muonRecoPt_,eventWeight_);
								// MT calculation
								mt_= MTCalculator(iEvent, metTag_,muonIsoPt_,muonIsoEta_,muonIsoPhi_);
							}
							// found isolated muon but can not be matched to reco muon
							else
							{
								muonIsoFailedTH2F_->Fill(RecoMuonDeltaR_,RecoMuonPTJet_/muonRecoPt_,eventWeight_);
							}
						// makes sure only one mu has been matched and enteres the eff.
						break;
						}
					}
					// no isolated muon has been found so will be concidert to be iso failed
					else
					{
						muonIsoFailedTH2F_->Fill(RecoMuonDeltaR_,RecoMuonPTJet_/muonRecoPt_,eventWeight_);
					}
					// makes sure only one mu has been matched and enteres the eff.
					break;
				}
				// muon found but can not be matched to a gen muon so failed
				else
				{
					muonIDFailedTH2F_->Fill(RecoMuonDeltaR_,RecoMuonPTJet_/muonRecoPt_,eventWeight_);
				}
				
			}

		}
	}



	
   }
   if (nGenElec_==1 && nGenMu_==0)
   {

	nRecoElec_=ElecID->size();
	nIsoElec_=ElecIDISO->size();

	deltaGenR_ = DRToClosestJet(iEvent,caloJetTag_, elecGenEta_, elecGenPhi_).first;
	closestJetToElecGenPt_ = DRToClosestJet(iEvent,caloJetTag_, elecGenEta_, elecGenPhi_).second;
	std::cout<<"ngenEl_=1 and nGenMu =0"<<std::endl;	

	
	// true if the electron is out of the acceptance
	if(std::abs(elecGenEta_)> maxElecEta_ && minElecPt_<elecGenPt_ || ( (1.4442 < std::abs(elecGenEta_) ) && (std::abs(elecGenEta_) < 1.566) && ( minElecPt_<elecGenPt_) ) ) 
	{
		// This histogramm is used for the actual acceptance caluclation
		ElecAccFailedTH1F_->Fill(elecGenPt_,eventWeight_);
		elecAcc_=-1;
		

	}
	// will run when electron is within the acceptance
	else 
	{
		elecAcc_=+1;
		elecPTAccPassed_=elecGenPt_;	
		// This histogramm is used for the actual acceptance caluclation
		ElecAccPassedTH1F_->Fill(elecGenPt_,eventWeight_);
		
		elecNumberRecoID_=ElecID->size();
		//true if no Mu has been reconstructed
		if (ElecID->size() ==0)
		{
			std::cout<<"ElecID->size()==0 but acc passed"<<std::endl;
					elecIDFailedTH2F_->Fill(deltaGenR_,closestJetToElecGenPt_/elecGenPt_,eventWeight_);
		}
		else
		{
			std::cout<<"ElecID size="<<ElecID->size()<<std::endl;
			for( edm::View <reco::Candidate>::const_iterator ElecIDCand = ElecID->begin(); ElecIDCand!=ElecID->end();ElecIDCand++)
			{
				elecRecoPt_ = ElecIDCand->pt();
				elecRecoEta_ = ElecIDCand->eta();
				elecRecoPhi_ = ElecIDCand->phi();
				// true if the reco and 
				RecoGenElecDeltaR_=deltaR(elecGenEta_,elecGenPhi_,elecRecoEta_,elecRecoPhi_);
				if (deltaR(elecGenEta_,elecGenPhi_,elecRecoEta_,elecRecoPhi_) < 0.3)
				{
					RecoElecDeltaR_=DRToClosestJet(iEvent, caloJetTag_,elecRecoEta_,elecRecoPhi_).first;
					RecoElecPTJet_=DRToClosestJet(iEvent, caloJetTag_,elecRecoEta_,elecRecoPhi_).second;
					RecoElecPTRelJet_=RecoElecPTJet_/elecRecoPt_;
					elecIDPassedTH2F_->Fill(RecoElecDeltaR_,RecoElecPTJet_/elecRecoPt_,eventWeight_);
					std::cout<<"elecIDPassed deltaR:"<<RecoElecDeltaR_<<std::endl<<"ptCloestJet:"<<RecoElecPTJet_<<std::endl<<"EventWeight"<<eventWeight_<<std::endl<<std::endl;
					//check if Iso is fulfilled
					if (ElecIDISO->size() > 0 )
					{
						for( edm::View <reco::Candidate>::const_iterator ElecIDIsoCand = ElecIDISO->begin(); ElecIDIsoCand!=ElecIDISO->end();ElecIDIsoCand++)
						{
							elecIsoPt_ = ElecIDIsoCand->pt();
							elecIsoEta_ = ElecIDIsoCand->eta();
							elecIsoPhi_ = ElecIDIsoCand->phi();
							if (deltaR(elecIsoEta_,elecIsoPhi_,elecRecoEta_,elecRecoPhi_) < 0.1)
							{
								IsoElecDeltaR_=RecoElecDeltaR_;
								IsoElecPTJet_=RecoElecPTJet_;
								IsoElecPTRelJet_=RecoElecPTJet_/elecRecoPt_;
								elecIsoPassedTH2F_->Fill(RecoElecDeltaR_,RecoElecPTJet_/elecRecoPt_,eventWeight_);
								// MT calculation
								mtElec_= MTCalculator(iEvent, metTag_,elecIsoPt_,elecIsoEta_,elecIsoPhi_);
							}
							// found isolated elec but can not be matched to reco elec
							else
							{
								elecIsoFailedTH2F_->Fill(RecoElecDeltaR_,RecoElecPTJet_/elecRecoPt_,eventWeight_);
							}
						// makes sure only one elec has been matched and enteres the eff.
						break;
						}
					}
					// no isolated elec has been found so will be concidert to be iso failed
					else
					{
						elecIsoFailedTH2F_->Fill(RecoElecDeltaR_,RecoElecPTJet_/elecRecoPt_,eventWeight_);
					}
					// makes sure only one elec has been matched and enteres the eff.
					break;
				}
				// elec found but can not be matched to a gen elec failed
				else
				{
					elecIDFailedTH2F_->Fill(RecoElecDeltaR_,RecoElecPTJet_/elecRecoPt_,eventWeight_);
				}
				
			}

		}

	}


   }
// Resets all values to default if more than 1 gen muon or gen elec is found in the event
   if (nGenMu_==2 || (nGenMu_+nGenElec_)>1)
   {
	unsigned int i =nGenMu_;
	
	nGenMu_=i;	
   }
   if (nGenElec_==2 || (nGenMu_+nGenElec_) > 1)
   {
	unsigned int i =nGenElec_;

	nGenElec_=i;	
   }



  tree_->Fill();
}



// ------------ method called once each job just before starting event loop  ------------
void 
MCEffCalculator::beginJob()
{
	double deltaRbins []={0,0.25, 0.5, 1, 2, 3};
	double ptbins []={0,10,20,30,40,60,100};
  	edm::Service<TFileService> fs;
  	tree_ = fs->make<TTree>(treeName_,treeName_);
	// book all the result plots
	muonIDFailedTH2F_ = fs->make<TH2F>("MuonRecoFailed", "MuonRecoFailed",5,deltaRbins,6,ptbins);
	muonIDPassedTH2F_ = fs->make<TH2F>("MuonRecoPassed", "MuonRecoPassed",5,deltaRbins,6,ptbins);
	muonIsoFailedTH2F_ = fs->make<TH2F>("muonIsoFailed","muonIsoFailed",5,deltaRbins,6,ptbins);
	muonIsoPassedTH2F_ = fs->make<TH2F>("muonIsoPassed","muonIsoPassed",5,deltaRbins,6,ptbins);

	MuonAccPassedTH1F_ = fs->make<TH1F>("muonAccPassed","muonAccPassed",40,0,200);
	MuonAccFailedTH1F_ = fs->make<TH1F>("muonAccFailed","muonAccFailed",40,0,200);

	MuonMTPassedTH2F_ = fs->make<TH2F>("muonMT","muonMT",1,0,1,1,0,1);


	elecIDFailedTH2F_ = fs->make<TH2F>("elecIdFailed","elecIdFailed",5,deltaRbins,6,ptbins);
	elecIDPassedTH2F_ = fs->make<TH2F>("elecIdPassed","elecIdPassed",5,deltaRbins,6,ptbins);
	elecIsoFailedTH2F_ = fs->make<TH2F>("elecIsoFailed","elecIsoFailed",5,deltaRbins,6,ptbins);
	elecIsoPassedTH2F_ = fs->make<TH2F>("elecIsoPassed","elecIsoPassed",5,deltaRbins,6,ptbins);

	ElecAccPassedTH1F_ = fs->make<TH1F>("elecAccPassed","elecAccPassed",40,0,200);
	ElecAccFailedTH1F_ = fs->make<TH1F>("elecAccFailed","elecAccFailed",40,0,200);


//create branches in the tree
    
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


    tree_->Branch("DeltaRLepClosestJet",&deltaGenR_,"DeltaRLepClosestJet/F");
    tree_->Branch("ClosestJetElecPt",&closestJetToElecGenPt_,"ClosestJetElecPt/F");
    tree_->Branch("ClosestJetMuonPt",&closestJetToMuonGenPt_,"ClosestJetMuonPt/F");
    tree_->Branch("MT",&mt_,"MT/F");

    //Testing variables
    tree_->Branch("RecoLevelMuonDeltaR",&RecoMuonDeltaR_,"RecoLevelMuonDeltaR/F");
    tree_->Branch("RecoLevelMuonPTJet",&RecoMuonPTJet_,"RecoLevelMuonPTJet/F");
    tree_->Branch("RecoLevelMuonRelPTJet",&RecoMuonPTRelJet_,"RecoLevelMuonRelPTJet/F");
    tree_->Branch("RecoVsGenLevelMuonDeltaR",&RecoGenMuDeltaR_,"RecoVsGenLevelMuonDeltaR/F");
    tree_->Branch("nRecoMu",&nRecoMu_,"nRecoMu/I");
    tree_->Branch("nIsoMu",&nIsoMu_,"nIsoMu/I");


    tree_->Branch("IsoLevelMuonDeltaR",&IsoMuonDeltaR_,"IsoLevelMuonDeltaR/F");
    tree_->Branch("IsoLevelMuonPTJet",&IsoMuonPTJet_,"IsoLevelMuonPTJet/F");
    tree_->Branch("IsoLevelMuonRelPTJet",&IsoMuonPTRelJet_,"IsoLevelMuonRelPTJet/F");
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
	std::cout<<"ende!!!!!!!"<<std::endl;
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

	eventWeight_		=-100;
	nGenMu_			=-100;
	nGenElec_		=-100;
	muonPTAccPassed_	=-100;
	elecPTAccPassed_	=-100;
	muonAcc_		=-100;
	elecAcc_		=-100;
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
	mt_			=-100;
	mtElec_			=-100;
	RecoMuonDeltaR_		=-100;
	RecoMuonPTJet_		=-100;
	RecoMuonPTRelJet_	=-100;
	IsoMuonDeltaR_		=-100;
	IsoMuonPTJet_		=-100;
	IsoMuonPTRelJet_	=-100;
	RecoGenMuDeltaR_	=-100;
	nRecoMu_		=-100;
	nRecoElec_		=-100;
	nIsoMu_			=-100;
	nIsoElec_		=-100;
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
	
	nGenMu_ =0;
	nGenElec_ =0;
	eventWeight_=0;
	muonAcc_=0;
	elecAcc_=0;
	nRecoMu_=0;
	nIsoMu_=0;
	
}


void
MCEffCalculator::MuonFound(reco::GenParticleCollection::const_iterator cand, unsigned int i)
{
	nGenMu_+=1;
	muonGenPt_  = cand->daughter(i)->pt();
	muonGenEta_ = cand->daughter(i)->eta();
	muonGenPhi_ = cand->daughter(i)->phi();
	// true if the muon is out of the detector acceptance

}

void
MCEffCalculator::ElecFound(reco::GenParticleCollection::const_iterator cand, unsigned int i)
{
	nGenElec_+=1;
		elecGenPt_  = cand->daughter(i)->pt();
		elecGenEta_ = cand->daughter(i)->eta();
		elecGenPhi_ = cand->daughter(i)->phi();

		// true if the elec is out of the detector acceptance


}

void
MCEffCalculator::TauFound(reco::GenParticleCollection::const_iterator cand, unsigned int i)
{
	for (unsigned int itau=0; itau < cand->daughter(i)->numberOfDaughters(); itau++)
	{	
		std::cout<<"Tau found!"<<std::endl;
		if (abs(cand->daughter(i)->daughter(itau)->pdgId() ) ==13) 
		{
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
MCEffCalculator::MTCalculator(const edm::Event& iEvent, edm::InputTag metTag, double lepPT, double lepEta, double lepPhi)
{
double metPT =0;
double dR = 0;
  edm::Handle< edm::View<reco::Candidate> > met;
  iEvent.getByLabel(metTag,met);
    metPT = met->at(0).pt();

dR = deltaR(met->at(0).eta(),met->at(0).phi(),lepEta,lepPhi);
return sqrt(2*lepPT*metPT*(1-cos(dR)) );

}
//define this as a plug-in
DEFINE_FWK_MODULE(MCEffCalculator);
