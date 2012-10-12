#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/Provenance/interface/EventAuxiliary.h"
#include "FWCore/Utilities/interface/EDMException.h"


#include <DataFormats/PatCandidates/interface/Jet.h>
#include <DataFormats/PatCandidates/interface/MET.h>
#include <DataFormats/PatCandidates/interface/Muon.h>
#include <DataFormats/PatCandidates/interface/Electron.h>
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "DataFormats/Common/interface/View.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "TH2.h"
#include <utility>
#include <vector>
#include "TString.h"
#include "TTree.h"

#include "DataFormats/Candidate/interface/CandMatchMap.h"





//
// class declaration
//

class MCEffCalculator : public edm::EDAnalyzer {
   public:
      explicit MCEffCalculator(const edm::ParameterSet&);
      ~MCEffCalculator();
	// first deltaR second CloestJetPT
	static std::pair <double,double> DRToClosestJet(const edm::Event& iEvent, edm::InputTag caloJetTag_, double lepEta, double lepPhi);
	static double MTCalculator(const edm::Event& iEvent, edm::InputTag MTTag, double lepPT, double lepEta, double lepPhi);

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      virtual void beginRun(edm::Run const&, edm::EventSetup const&);
      virtual void endRun(edm::Run const&, edm::EventSetup const&);
      virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
      virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);

	//special functions
	void MuonFound(reco::GenParticleCollection::const_iterator cand, unsigned int i);
	void ElecFound(reco::GenParticleCollection::const_iterator cand, unsigned int i);
	void TauFound(reco::GenParticleCollection::const_iterator cand, unsigned int i);
	void ResetValues();

	//Tags
  	edm::InputTag evtWeightTag_;
  	edm::InputTag muonIDTag_, muonIDISOTag_;
  	edm::InputTag elecIDTag_, elecIDISOTag_;
  	edm::InputTag jetTag_;
	edm::InputTag caloJetTag_;
  	edm::InputTag metTag_;
  	edm::InputTag genTag_;
	


      // Variables
	//Input
	double minMuonPt_, minElecPt_, minJetPt_, maxMuonEta_, maxElecEta_;
	double eventWeight_;
	unsigned int nGenMu_, nGenElec_;
	TH2F *muonIDPassedTH2F_, *muonIsoPassedTH2F_, *muonIsoPassedUpTH2F_, *muonIsoPassedDownTH2F_;
	TH2F *elecIDPassedTH2F_, *elecIsoPassedTH2F_, *elecIsoPassedUpTH2F_, *elecIsoPassedDownTH2F_;
 	TH2F *muonIDFailedTH2F_, *muonIsoFailedTH2F_, *muonIsoFailedUpTH2F_, *muonIsoFailedDownTH2F_;
	TH2F *elecIDFailedTH2F_, *elecIsoFailedTH2F_, *elecIsoFailedUpTH2F_, *elecIsoFailedDownTH2F_;

	TH2F *MuonMTPassedTH2F_, *MuonMTFailedTH2F_;

	TH1F *MuonAccPassedTH1F_, *MuonAccFailedTH1F_;
	TH1F *ElecAccPassedTH1F_, *ElecAccFailedTH1F_;


	//Tree and stuff to be filed in it
        TString treeName_;
        TTree* tree_;
	int muonAcc_, elecAcc_;
	int muonNumberRecoID_, elecNumberRecoID_;
	Float_t muonPTAccPassed_, elecPTAccPassed_;
	Float_t muonIDPassed_, muonIDFailed_, elecIDPassed_, elecIDFailed_, muonRecoPt_, muonRecoEta_, muonRecoPhi_, elecRecoPt_, elecRecoEta_, elecRecoPhi_;
	Float_t muonGenPt_, muonGenEta_, muonGenPhi_, elecGenPt_, elecGenEta_, elecGenPhi_;
	Float_t deltaGenR_, closestJetToMuonGenPt_,closestJetToElecGenPt_, mt_, mtElec_;
	// reco iso eff plots
	TH2F *elecIdEffTH2F_, *elecIsoEffTH2F_, *elecIsoEffUpTH2F_, *elecIsoEffDownTH2F_;
 	TH2F *muonIdEffTH2F_, *muonIsoEffTH2F_, *muonIsoEffUpTH2F_, *muonIsoEffDownTH2F_;	

	//Varialbes used for studies
	Float_t RecoMuonDeltaR_, RecoMuonPTJet_, RecoMuonPTRelJet_, IsoMuonDeltaR_, IsoMuonPTJet_, IsoMuonPTRelJet_, RecoGenMuDeltaR_;
	unsigned int nRecoMu_, nRecoElec_, nIsoMu_, nIsoElec_;
	//not plotted
	Float_t muonIsoPt_, muonIsoEta_, muonIsoPhi_;

	Float_t RecoElecDeltaR_, RecoElecPTJet_, RecoElecPTRelJet_, IsoElecDeltaR_, IsoElecPTJet_, IsoElecPTRelJet_, RecoGenElecDeltaR_;
	//not plotted
	Float_t elecIsoPt_, elecIsoEta_, elecIsoPhi_;

};