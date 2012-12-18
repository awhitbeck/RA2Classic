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
	edm::InputTag ElecTag_;
	edm::InputTag MhtTag_,HTTag_,MHTTag_, NVTag_;
	edm::InputTag CaloJetTag_;
	edm::InputTag evtWeightTag_;

	// other inputs
	double MTWMax_;
	bool MTWCut_;
 	double MinMuPT_, MinElecPT_;
	Float_t eventWeight_;

	std::string EfficiencyFileName_;

	// input corrections uncertainties
	double DiLepCorrection_, DiLepCorrectionUp_, DiLepCorrectionDown_;

  	// efficiencies created ones per job!
	TH1F *MuonAccSum_, *MuonAccPassed_;
	TH1F *ElecAccSum_, *ElecAccPassed_;
	TH1F *MuonAccEff2_, *ElecAccEff2_;
	TH2F *MuonAccEff3_, *ElecAccEff3_;
	TH2F *MuonRecoEff_, *MuonIsoEff_;
	TH2F *MuonRecoEff2_, *MuonIsoEff2_;
	TH2F *ElecRecoEff_, *ElecIsoEff_;
	TH2F *ElecRecoEff2_, *ElecIsoEff2_;
	TH1F *MTWEff_;
	Float_t MuonAccEff_, ElecAccEff_;
	Float_t muonAccEff2_, elecAccEff2_;


	TH3F *MuonBinByBinEff_, *ElecBinByBinEff_;
	TH3F *MuonAccBinByBinEff_, *MuonRecoBinByBinEff_, *MuonIsoBinByBinEff_;
	TH3F *ElecAccBinByBinEff_, *ElecRecoBinByBinEff_, *ElecIsoBinByBinEff_;
	Float_t muonBinByBinXMax_,muonBinByBinYMax_,muonBinByBinZMax_,elecBinByBinXMax_,elecBinByBinYMax_,elecBinByBinZMax_;
	Float_t muonAccBinByBinXMax_,muonAccBinByBinYMax_,muonAccBinByBinZMax_;
	Float_t muonRecoBinByBinXMax_,muonRecoBinByBinYMax_,muonRecoBinByBinZMax_;
	Float_t muonIsoBinByBinXMax_,muonIsoBinByBinYMax_,muonIsoBinByBinZMax_;
	Float_t elecAccBinByBinXMax_,elecAccBinByBinYMax_,elecAccBinByBinZMax_;
	Float_t elecRecoBinByBinXMax_,elecRecoBinByBinYMax_,elecRecoBinByBinZMax_;
	Float_t elecIsoBinByBinXMax_,elecIsoBinByBinYMax_,elecIsoBinByBinZMax_;
	Float_t muonBinByBinEff_, muonBinByBinWeight_, totalMuonsBinByBinWeight_, elecBinByBinEff_, elecWeightBinByBin_, resultWeightBinByBin_, resultWeightBinByBinMTW_, totalMuonsBinByBin_;
	
	
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
	Float_t totalMuons_;
	Float_t muonIsoWeight_, muonRecoWeight_, muonAccWeight_, muonAccEff_, elecAccEff_;
	Float_t muonIsoWeight2_, muonRecoWeight2_, muonAccWeight2_, muonTotalWeight2_, muonIsoEff2_, muonRecoEff2_, muAllIsoWeight2_;

	Float_t elecRecoEff_, elecIsoEff_, elecTotalWeight_;
	Float_t elecIsoWeight_, elecRecoWeight_, elecAccWeight_;
	Float_t elecIsoWeight2_, elecRecoWeight2_, elecAccWeight2_, elecTotalWeight2_, elecIsoEff2_, elecRecoEff2_;
	Float_t mtwCorrection_;
	Float_t resultWeight_;
	Float_t resultWeight2_;
	Float_t resultWeight2MTW_, resultWeightMTW_;
	Float_t muonIsoXMax_, muonIsoYMax_;
	Float_t muonRecoXMax_, muonRecoYMax_;
	Float_t muonIsoX2Max_, muonIsoY2Max_;
	Float_t muonRecoX2Max_, muonRecoY2Max_;
	Float_t elecAccXMax_, muonAccXMax_;
	Float_t elecAccXMax3_, muonAccXMax3_;

	Float_t deltaRMuJet_;
	Float_t deltaRMuMHT_;
	Float_t PtClosestJet_;
	Float_t deltaPtClosestJetMu_;
	Float_t genDeltaR_;
	Float_t genPTJet_;
	Float_t genPTRelJet_;
	int muPromtMatched_;


        TTree* tree_;
	// weights for x checks
	Float_t muAllIsoWeight_;
	int error_;

	// binbybin sepearte result values
	Float_t muonBinByBinIsoWeight_, muonBinByBinRecoWeight_, muonBinByBinAccWeight_;
 	Float_t muonBinByBinIsoEff_, muonBinByBinRecoEff_, muonBinByBinAccEff_;

	Float_t elecBinByBinIsoWeight_, elecBinByBinRecoWeight_, elecBinByBinAccWeight_;
 	Float_t elecBinByBinIsoEff_, elecBinByBinRecoEff_, elecBinByBinAccEff_;

	Float_t totalBinByBinMuons_;
	Float_t muonBinByBinTotalWeight_, elecBinByBinTotalWeight_;
	Float_t resultBinByBinWeight_;
	Float_t resultBinByBinWeightMTW_;

	// uncertainties and corrections for binbybin
	Float_t resultBinByBinWeightMTWDiLep_, resultBinByBinWeightMTWDiLepUp_, resultBinByBinWeightMTWDiLepDown_;

      // ----------member data ---------------------------
};