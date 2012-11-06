// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/Provenance/interface/EventAuxiliary.h"
#include "FWCore/Utilities/interface/EDMException.h"

#include <TH2F.h>
#include <TFile.h>
#include "TTree.h"
//
// class declaration
//

class LostLeptonBkg : public edm::EDProducer {
   public:
      explicit LostLeptonBkg(const edm::ParameterSet&);
      ~LostLeptonBkg();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

   private:
      virtual void beginJob() ;
      virtual void produce(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      
      virtual void beginRun(edm::Run&, edm::EventSetup const&);
      virtual void endRun(edm::Run&, edm::EventSetup const&);
      virtual void beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);
      virtual void endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);

	// Functions
	void ResetValues();

	// Tags
	edm::InputTag HtJetsTag_;
	edm::InputTag MetTag_;
	edm::InputTag MuonTag_;
	edm::InputTag MhtTag_,HTTag_,MHTTag_, NVTag_;
	edm::InputTag CaloJetTag_;
	edm::InputTag evtWeightTag_;

	// other inputs
	double MTWMax_;
	bool MTWCut_;
 	double MinMuPT_, MinElecPT_;
	Float_t eventWeight_;

	std::string EfficiencyFileName_;

  	// efficiencies created ones per job!
	TH1F *MuonAccSum_, *MuonAccPassed_;
	TH1F *ElecAccSum_, *ElecAccPassed_;
	TH2F *MuonRecoEff_, *MuonIsoEff_;
	TH2F *ElecRecoEff_, *ElecIsoEff_;
	TH1F *MTWEff_;
	Float_t MuonAccEff_, ElecAccEff_;
	
	// Variables
	float met_;
	float mht_, ht_;
	float mtw_; 
	int nMu_;
	Float_t MuPt_;
	Float_t MuEta_;
	Float_t MuPhi_;
	UShort_t nV_, nJets_;
	int nCaloJets_;

	
	Float_t muonIsoEff_, muonRecoEff_, muonTotalWeight_;
	Float_t muonIsoWeight_, muonRecoWeight_, muonAccWeight_;
	Float_t elecRecoEff_, elecIsoEff_, elecTotalWeight_;
	Float_t elecIsoWeight_, elecRecoWeight_, elecAccWeight_;
	Float_t mtwCorrection_;
	Float_t resultWeight_;

	Float_t deltaRMuJet_;
	Float_t deltaRMuMHT_;
	Float_t PtClosestJet_;
	Float_t deltaPtClosestJetMu_;
	int muPromtMatched_;


        TTree* tree_;


      // ----------member data ---------------------------
};