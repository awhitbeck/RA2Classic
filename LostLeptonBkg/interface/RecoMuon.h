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


	// tags
	edm::InputTag HtJetsTag_;
	edm::InputTag MHTTag_;
	edm::InputTag MhtTag_;
	edm::InputTag HTTag_;
	edm::InputTag NVTag_;
	edm::InputTag MetTag_;
	edm::InputTag MuonTag_;
	edm::InputTag MuonRecoTag_;
	edm::InputTag ElecTag_;
	edm::InputTag evtWeightTag_;
	// other inputs
	double MTWMax_;
	bool MTWCut_;
	bool debug_;
	double MinMuPT_, MinElecPT_;
	// Variables
	float met_, mht_, ht_, mtw_, eventWeight_;
	int nMu_, nElec_;
	UShort_t nV_, nJets_;
      // ----------member data ---------------------------
};