//
// Original Author:  Matthias Schroeder,,,
//         Created:  Mon Jul 30 16:39:54 CEST 2012
// $Id: TreeMaker.h,v 1.3 2012/08/02 13:23:36 mschrode Exp $
//
//

#ifndef RA2CLASSIC_TREEMAKER
#define RA2CLASSIC_TREEMAKER

// system include files
#include <memory>
#include <vector>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Utilities/interface/InputTag.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "TString.h"
#include "TTree.h"

//
// class declaration
//

class TreeMaker : public edm::EDAnalyzer {
public:
  explicit TreeMaker(const edm::ParameterSet&);
  ~TreeMaker() {};
  
  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
  
  
private:
  virtual void beginJob() ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;
  
  virtual void beginRun(edm::Run const&, edm::EventSetup const&);
  virtual void endRun(edm::Run const&, edm::EventSetup const&);
  virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
  virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);

  void setBranchVariablesToDefault();

  TString treeName_;
  TTree* tree_;

  UInt_t runNum_;      
  UInt_t lumiBlockNum_;
  UInt_t evtNum_;
  edm::InputTag weightTag_;
  Float_t weight_;
  edm::InputTag vertexCollectionTag_;
  UShort_t nVtx_;
  edm::InputTag htTag_;
  Float_t ht_;
  edm::InputTag mhtTag_;
  Float_t mht_;
  edm::InputTag htJetsTag_;
  UShort_t nJets_;
  Float_t jet1Pt_, jet2Pt_, jet3Pt_;
  Float_t jet1Eta_, jet2Eta_, jet3Eta_;
  edm::InputTag mhtJetsTag_;
  Float_t deltaPhi1_, deltaPhi2_, deltaPhi3_;
  std::vector<edm::InputTag> filterDecisionTags_;
  std::vector<UChar_t> filterDecisions_;
};

#endif
