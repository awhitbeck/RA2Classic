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
#include <TH3F.h>
#include <TFile.h>
#include "TTree.h"

class RecoMuon : public edm::EDProducer {
   public:
      explicit RecoMuon(const edm::ParameterSet&);
      ~RecoMuon();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

   private:
      virtual void beginJob() ;
      virtual void produce(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      virtual void beginRun(edm::Run&, edm::EventSetup const&);
      virtual void endRun(edm::Run&, edm::EventSetup const&);
      virtual void beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);
      virtual void endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);

	void ResetValues();
	bool MuTauDecayMatched(const reco::Candidate* tau);
	bool Match(float firstPT, float firstEta, float firstPhi, float secondPT, float secondEta, float secondPhi);

	// tags
	edm::InputTag HtJetsTag_;
	edm::InputTag MHTTag_;
	edm::InputTag MhtTag_;
	edm::InputTag HTTag_;
	edm::InputTag NVTag_;
	edm::InputTag MetTag_;
	edm::InputTag CaloJetTag_;
	edm::InputTag GenTag_;
	edm::InputTag MuonIsoTag_;
	edm::InputTag MuonRecoTag_;
	edm::InputTag ElecIsoTag_;
	edm::InputTag evtWeightTag_;
	// other inputs
	double MTWMax_;
	bool MTWCut_;
	bool debug_;
	double MinMuPT_, MinElecPT_;
	// Variables
	float met_, mht_, ht_, mtw_, eventWeight_;
	int nIsoMu_, nIsoElec_, nRecoMu_, nGenMu_;
	UShort_t nV_, nJets_;
	std::vector<float> isoMuPt_, isoMuEta_, isoMuPhi_, isoMuMtw_, isoMuDeltaR_, isoMuClosestJetPt_;
	std::vector<float> recoMuPt_, recoMuEta_, recoMuPhi_, recoMuMtw_, recoMuDeltaR_, recoMuClosestJetPt_, recoMuClosestJetRelPt_;
	std::vector<bool>  recoMuIsoMatched_, recoMuGenMatched_, recoMuGenTauDecay_;
	std::vector<float> genMuPt_, genMuEta_, genMuPhi_, genMuMtw_, genMuDeltaR_, genMuClosestJetPt_;
	std::vector<float> isoElecPt_, isoElecEta_, isoElecPhi_, isoElecMtw_, isoElecDeltaR_, isoElecClosestJetPt_;
	bool mc_;
	// study variables and histogramms
	float recoMuPtTemp_, recoMuPhiTemp_, recoMuEtaTemp_;
	std::vector<float> recoMuGenMatchDeltaPT_, recoMuGenMatchDeltaR_;
	// outPutONLY
        TTree* tree_;
      // ----------member data ---------------------------
};