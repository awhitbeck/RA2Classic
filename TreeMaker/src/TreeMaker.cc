//
// Package:    TreeMaker
// Class:      TreeMaker
// 
/**\class TreeMaker TreeMaker.cc RA2Classic/TreeMaker/src/TreeMaker.cc

 Description: Writes ntuples (ROOT tree) for RA2Classic analysis

 The following variables are stored in the tree:
  - "RunNum": run number (UInt_t)
  - "LumiBlockNum": luminosity block number (UInt_t)
  - "EvtNum": event number (UInt_t)
  - "NVtx": number of vertices (UShort_t)
  - "HT": HT (Float_t)
  - "NJets": number of jets (UShort_t)
  - "Jet?Pt": pt of jet ?, where ? = 1,2,3 (Float_t)
  - "Jet?Eta": eta of jet ?, where ? = 1,2,3 (Float_t)
  - "MHT": MHT (Float_t)
  - "DeltaPhi?": deltaPhi between jet ? and MHT, where ? = 1,2,3 (Float_t)

 The following optional variables are stored in the tree:
  - "Filter_<name>": decision of filter <name>, where 0 means false, 1 means true (UChar_t)
  - "<VarsDouble_name>": numbers. They are expected to be stored in double-
                         precision in the event but kept in Float_t-precision
                         in the tree (Float_t)


 The following input parameters control how the above variables
 are computed from the information stored in the event:
  - "VertexCollection": collection from which "NVtx" is determined
  - "HT": the value of HT. This is taken from the event and not
          computed by the TreeMaker.
  - "HTJets": jet collection that has been used to compute HT. The
              variables "NJets", "Jet?Pt", and "Jet?Eta" are taken
              from this collection.
  - "MHT": the MHT vector. This is taken from the event and not
           computed by the TreeMaker.
  - "MHTJets": jet collection that has been used to compute MHT. The
               variables "DeltaPhi?" are computed from this collection
	       and from "MHT".
  - "VarsDouble": list of InputTags for double-precision variables stored
                  in the event. They are stored in the tree in Float_t
                  precision with the names given in VarsDoubleNamesInTree or,
                  if this is not specified, as '<InputTag::label()>'.
  - "Filters": list of filter names (InputTags) that have been run in tag mode
               and stored the decision as a boolean


*/
//
// Original Author:  Matthias Schroeder,,,
//         Created:  Mon Jul 30 16:39:54 CEST 2012
// $Id: TreeMaker.cc,v 1.7 2012/09/19 13:59:20 mschrode Exp $
//
//

#include "RA2Classic/TreeMaker/interface/TreeMaker.h"

#include <string>

#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/Math/interface/deltaPhi.h"
#include "DataFormats/Provenance/interface/EventAuxiliary.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "FWCore/Utilities/interface/EDMException.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

//
// constructors and destructor
//
TreeMaker::TreeMaker(const edm::ParameterSet& iConfig)
  : tree_(0) {

  // Set default values for all branch variables
  setBranchVariablesToDefault();

  // Read parameter values
  treeName_ = iConfig.getParameter<std::string>("TreeName");
  vertexCollectionTag_ = iConfig.getParameter<edm::InputTag>("VertexCollection");
  htJetsTag_ = iConfig.getParameter<edm::InputTag>("HTJets");
  htTag_ = iConfig.getParameter<edm::InputTag>("HT");
  mhtJetsTag_ = iConfig.getParameter<edm::InputTag>("MHTJets");;
  mhtTag_ = iConfig.getParameter<edm::InputTag>("MHT");
  varsDoubleTags_ = iConfig.getParameter< std::vector<edm::InputTag> >("VarsDouble");
  varsDoubleNamesInTree_ = iConfig.getParameter< std::vector<std::string> >("VarsDoubleNamesInTree");
  filterDecisionTags_ = iConfig.getParameter< std::vector<edm::InputTag> >("Filters");

  // Setup vector of filter decisions with correct size
  varsDouble_ = std::vector<Float_t>(varsDoubleTags_.size(),1.);
  filterDecisions_ = std::vector<UChar_t>(filterDecisionTags_.size(),0);
}



//
// member functions
//

// ------------ method called for each event  ------------
void
TreeMaker::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
  // Set default values for all branch variables
  setBranchVariablesToDefault();

  // Event information
  edm::EventAuxiliary aux = iEvent.eventAuxiliary();
  runNum_       = aux.run();
  lumiBlockNum_ = aux.luminosityBlock();
  evtNum_       = aux.event();
  
  // Number of vertices
  edm::Handle<reco::VertexCollection> vertices;
  iEvent.getByLabel(vertexCollectionTag_,vertices);
  if( vertices.isValid() ) {
    nVtx_ = vertices->size();
  }

  // HT & MHT
  edm::Handle<double> ht;
  iEvent.getByLabel(htTag_,ht);
  if( ht.isValid() ) {
    ht_ = *ht;
  }
  edm::Handle< edm::View<reco::Candidate> > mht;
  iEvent.getByLabel(mhtTag_,mht);
  if( mht.isValid() ) {
    mht_ = mht->at(0).pt();
  }

  // Jet kinematics (jets used in HT definition)
  edm::Handle< edm::View<reco::Candidate> > htJets;
  iEvent.getByLabel(htJetsTag_,htJets);
  if( htJets.isValid() ) {
    nJets_ = htJets->size();
    if( htJets->size() > 0 ) {
      jet1Pt_ = htJets->at(0).pt();
      jet1Eta_ = htJets->at(0).eta();
      if( htJets->size() > 1 ) {
	jet2Pt_ = htJets->at(1).pt();
	jet2Eta_ = htJets->at(1).eta();
	if( htJets->size() > 2 ) {
	  jet3Pt_ = htJets->at(2).pt();
	  jet3Eta_ = htJets->at(2).eta();
	}
      }
    }
  }

  // DeltaPhi between jets and MHT (jets used in MHT definition)
  edm::Handle< edm::View<reco::Candidate> > mhtJets;
  iEvent.getByLabel(mhtJetsTag_,mhtJets);
  if( mhtJets.isValid() && mht.isValid() ) {
    if( mhtJets->size() > 0 ) {
      deltaPhi1_ = std::abs(reco::deltaPhi(mhtJets->at(0).phi(),mht->at(0).phi()));
      if( mhtJets->size() > 1 ) {
	deltaPhi2_ = std::abs(reco::deltaPhi(mhtJets->at(1).phi(),mht->at(0).phi()));
	if( mhtJets->size() > 2 ) {
	  deltaPhi3_ = std::abs(reco::deltaPhi(mhtJets->at(2).phi(),mht->at(0).phi()));
	}
      }
    }
  }

  // Double-precision variables
  for(unsigned int i = 0; i < varsDoubleTags_.size(); ++i) {
    edm::Handle<double> var;
    iEvent.getByLabel(varsDoubleTags_.at(i),var);
    if( var.isValid() ) {
      varsDouble_.at(i) = *var;
    }
  }

  // Filter decisions
  for(unsigned int i = 0; i < filterDecisionTags_.size(); ++i) {
    edm::Handle<bool> dec;
    iEvent.getByLabel(filterDecisionTags_.at(i),dec);
    if( dec.isValid() ) {
      if( *dec ) filterDecisions_.at(i) = 1;
      else filterDecisions_.at(i) = 0;
    }
  }


  // Fill variables into tree
  tree_->Fill();
}


// ------------ method called once each job just before starting event loop  ------------
void 
TreeMaker::beginJob() {
  edm::Service<TFileService> fs;
  if( !fs ) {
    throw edm::Exception(edm::errors::Configuration, "TFile Service is not registered in cfg file");
  }
  tree_ = fs->make<TTree>(treeName_,treeName_);
  tree_->SetAutoSave(10000000000);
  tree_->SetAutoFlush(1000000);
  tree_->Branch("RunNum",&runNum_,"RunNum/i");
  tree_->Branch("LumiBlockNum",&lumiBlockNum_,"LumiBlockNum/i");
  tree_->Branch("EvtNum",&evtNum_,"EvtNum/i");
  tree_->Branch("NVtx",&nVtx_,"NVtx/s");
  tree_->Branch("HT",&ht_,"HT/F");
  tree_->Branch("MHT",&mht_,"MHT/F");
  tree_->Branch("NJets",&nJets_,"NJets/s");
  tree_->Branch("Jet1Pt",&jet1Pt_,"Jet1Pt/F");
  tree_->Branch("Jet2Pt",&jet2Pt_,"Jet2Pt/F");
  tree_->Branch("Jet3Pt",&jet3Pt_,"Jet3Pt/F");
  tree_->Branch("Jet1Eta",&jet1Eta_,"Jet1Eta/F");
  tree_->Branch("Jet2Eta",&jet2Eta_,"Jet2Eta/F");
  tree_->Branch("Jet3Eta",&jet3Eta_,"Jet3Eta/F");
  tree_->Branch("DeltaPhi1",&deltaPhi1_,"DeltaPhi1/F");
  tree_->Branch("DeltaPhi2",&deltaPhi2_,"DeltaPhi2/F");
  tree_->Branch("DeltaPhi3",&deltaPhi3_,"DeltaPhi3/F");
  for(unsigned int i = 0; i < varsDouble_.size(); ++i) {
    TString name = varsDoubleTags_.at(i).label();
    if( varsDoubleNamesInTree_.size() == varsDoubleTags_.size() ) {
      name = varsDoubleNamesInTree_.at(i);
    }
    tree_->Branch(name,&(varsDouble_.at(i)),name+"/F");
  }
  for(unsigned int i = 0; i < filterDecisionTags_.size(); ++i) {
    TString name = "Filter_";
    name += filterDecisionTags_.at(i).label();
    tree_->Branch(name,&(filterDecisions_.at(i)),name+"/b");
  }
}


// ------------ method called once each job just after ending the event loop  ------------
void 
TreeMaker::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
void 
TreeMaker::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
TreeMaker::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
TreeMaker::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
TreeMaker::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
TreeMaker::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

// ------------ method called once each job just before starting event loop  ------------
void 
TreeMaker::setBranchVariablesToDefault() {
  runNum_ = 0;      
  lumiBlockNum_ = 0;
  evtNum_ = 0;      
  nVtx_ = 0;
  ht_ = 0.;
  mht_ = 0.;
  nJets_ = 0;
  jet1Pt_ = 0.;
  jet2Pt_ = 0.;
  jet3Pt_ = 0.;
  jet1Eta_ = 0.;
  jet2Eta_ = 0.;
  jet3Eta_ = 0.;
  deltaPhi1_ = 0.;
  deltaPhi2_ = 0.;
  deltaPhi3_ = 0.;
  for(unsigned int i = 0; i < varsDouble_.size(); ++i) {
    varsDouble_.at(i) = 1.;
  }
  for(unsigned int i = 0; i < filterDecisions_.size(); ++i) {
    filterDecisions_.at(i) = 0;
  }
}


//define this as a plug-in
DEFINE_FWK_MODULE(TreeMaker);
