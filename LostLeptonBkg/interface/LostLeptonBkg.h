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
	edm::InputTag MhtTag_;
	edm::InputTag CaloJetTag_;
	edm::InputTag evtWeightTag_;

	// other inputs
	double MTWMax_;
	bool MTWCut_;
 	double MinMuPT_, MinElecPT_;
	double eventWeight_;

	std::string EfficiencyFileName_;

  	// efficiencies created ones per job!
	TH1F *muonAccSum_, *muonAccPassed_;
	TH1F *elecAccSum_, *elecAccPassed_;
	TH2F *muonRecoEff_, *muonIsoEff_;
	TH2F *elecRecoEff_, *elecIsoEff_;
	double muonAccEff_, elecAccEff_;
	
	// Variables
	float met_;
	float mht_;
	float mtw_; 
	int nMu_;
	double MuPt_;
	double MuEta_;
	double MuPhi_;
	int nJets_;
	int nCaloJets_;


	double deltaRMuJet_;
	double deltaRMuMHT_;
	double deltaPtMuJet_;




      // ----------member data ---------------------------
};