//
// Package:    TreeMaker
// Class:      TreeMaker
// 
/**\class TreeMaker TreeMaker.cc RA2Classic/TreeMaker/src/TreeMaker.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Matthias Schroeder,,,
//         Created:  Mon Jul 30 16:39:54 CEST 2012
// $Id$
//
//

#include "RA2Classic/TreeMaker/interface/TreeMaker.h"

#include <string>

#include "FWCore/Utilities/interface/EDMException.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

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
  htTag_ = iConfig.getParameter<edm::InputTag>("HT");
  mhtTag_ = iConfig.getParameter<edm::InputTag>("MHT");
}


TreeMaker::~TreeMaker() {

}


//
// member functions
//

// ------------ method called for each event  ------------
void
TreeMaker::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
  // Set default values for all branch variables
  setBranchVariablesToDefault();

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
  edm::Handle<double> mht;
  iEvent.getByLabel(mhtTag_,mht);
  if( mht.isValid() ) {
    mht_ = *mht;
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
  tree_->Branch("NumVtx",&nVtx_,"NumVtx/s");
  tree_->Branch("HT",&ht_,"HT/F");
  tree_->Branch("MHT",&mht_,"MHT/F");
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
  nVtx_ = 0;
  ht_ = 0.;
  mht_ = 0.;
}


//define this as a plug-in
DEFINE_FWK_MODULE(TreeMaker);
