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
	TH1F *MuonAccSum_, *MuonAccPassed_;
	TH1F *ElecAccSum_, *ElecAccPassed_;
	TH2F *MuonRecoEff_, *MuonIsoEff_;
	TH2F *ElecRecoEff_, *ElecIsoEff_;
	TH1F *MTWEff_;
	double MuonAccEff_, ElecAccEff_;
	
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

	
	double muonIsoEff_, muonRecoEff_, muonTotalWeight_;
	double muonIsoWeight_, muonRecoWeight_, muonAccWeight_;
	double elecRecoEff_, elecIsoEff_, elecTotalWeight_;
	double elecIsoWeight_, elecRecoWeight_, elecAccWeight_;
	double mtwCorrection_;
	double resultWeight_;

	double deltaRMuJet_;
	double deltaRMuMHT_;
	double PtClosestJet_;
	double deltaPtClosestJetMu_;




      // ----------member data ---------------------------
};