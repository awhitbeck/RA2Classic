// -*- C++ -*-
//
// Package:    RecoMuon
// Class:      RecoMuon
// 
/**\class RecoMuon RecoMuon.cc RA2Classic/RecoMuon/src/RecoMuon.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Arne-Rasmus Draeger,68/111,4719,
//         Created:  Mon Jul 29 16:37:03 CEST 2013
// $Id$
//
//


// system include files
#include "RA2Classic/LostLeptonBkg/interface/RecoMuon.h"
#include <TString.h>
#include "DataFormats/Math/interface/deltaPhi.h"
#include <DataFormats/Math/interface/deltaR.h>
#include <DataFormats/PatCandidates/interface/Jet.h>
#include "RA2Classic/LostLeptonBkg/interface/MCEffCalculator.h"


//
// class declaration
//



//
// constants, enums and typedefs
//


//
// static data member definitions
//

//
// constructors and destructor
//
RecoMuon::RecoMuon(const edm::ParameterSet& iConfig)
{
   HtJetsTag_ = iConfig.getParameter<edm::InputTag>("HTJets");
   MhtTag_ = iConfig.getParameter<edm::InputTag>("MhtTag");
   MetTag_ = iConfig.getParameter<edm::InputTag>("MetTag");
   MuonTag_ = iConfig.getParameter<edm::InputTag>("MuonTag");
   MuonRecoTag_ = iConfig.getParameter<edm::InputTag>("MuonRecoTag");
   ElecTag_ = iConfig.getParameter<edm::InputTag>("ElecTag");
   evtWeightTag_ = iConfig.getParameter<edm::InputTag> ("EventWeightTag");
   MTWMax_ = iConfig.getParameter <double> ("MTWMax");
   MTWCut_ = iConfig.getParameter <bool> ("MTWCut");
   MinMuPT_ = iConfig.getParameter <double> ("MinMuPT");
   MinElecPT_ = iConfig.getParameter <double> ("MinElecPT");
   HTTag_ = iConfig.getParameter<edm::InputTag>("HTTag");
   MHTTag_ = iConfig.getParameter<edm::InputTag>("MHTTag");
   NVTag_ = iConfig.getParameter<edm::InputTag>("VertexCollection");
}


RecoMuon::~RecoMuon()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
RecoMuon::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

// translate tags to objects
edm::Handle< edm::View<reco::Candidate> > met;
iEvent.getByLabel(MetTag_,met);
if( met.isValid() ) 
{
	met_ = met->at(0).pt();
}
  edm::Handle< edm::View<reco::Candidate> > htJets;
  iEvent.getByLabel(HtJetsTag_,htJets);
  if( htJets.isValid() ) 
  {
	nJets_ = htJets->size();
  }
  edm::Handle< edm::View<reco::Candidate> > mht;
  iEvent.getByLabel(MHTTag_,mht);
  mht_ = mht->at(0).pt();

  edm::Handle<double> eventWeight;
  iEvent.getByLabel(evtWeightTag_,eventWeight);
  eventWeight_ = *eventWeight;

  edm::Handle<double> ht;
  iEvent.getByLabel(HTTag_,ht);
  ht_ = *ht;

  edm::Handle<reco::VertexCollection> vertices;
  iEvent.getByLabel(NVTag_,vertices);
  if( vertices.isValid() ) 
  {
    	nV_ = vertices->size();
  }

  edm::Handle <edm::View <reco::Candidate> > Mu;
  iEvent.getByLabel(MuonTag_,Mu);
  edm::Handle <edm::View <reco::Candidate> > Elec;
  iEvent.getByLabel(ElecTag_,Elec);
  edm::Handle <edm::View <reco::Candidate> > RecoMu;
  iEvent.getByLabel(MuonRecoTag_,RecoMu);

 
}

// ------------ method called once each job just before starting event loop  ------------
void 
RecoMuon::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
RecoMuon::endJob() {
}

// ------------ method called when starting to processes a run  ------------
void 
RecoMuon::beginRun(edm::Run&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
RecoMuon::endRun(edm::Run&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
RecoMuon::beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
RecoMuon::endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
RecoMuon::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(RecoMuon);
