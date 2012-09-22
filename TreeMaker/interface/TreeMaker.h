//
// Original Author:  Matthias Schroeder,,,
//         Created:  Mon Jul 30 16:39:54 CEST 2012
// $Id: TreeMaker.h,v 1.6 2012/09/19 14:44:07 mschrode Exp $
//
//

#ifndef RA2CLASSIC_TREEMAKER
#define RA2CLASSIC_TREEMAKER

// system include files
#include <string>
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
  ~TreeMaker();
  
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

  const unsigned int nMaxCandidates_;

  TString treeName_;
  TTree* tree_;

  // Event information 
  UInt_t runNum_;      
  UInt_t lumiBlockNum_;
  UInt_t evtNum_;
  edm::InputTag vertexCollectionTag_;
  UShort_t nVtx_;

  // RA2-selection related variables
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

  // Any double-precision variables
  std::vector<edm::InputTag> varsDoubleTags_;
  std::vector<std::string> varsDoubleNamesInTree_;
  std::vector<Float_t> varsDouble_;

  // Any edm::Candidates
  std::vector<edm::InputTag> candidatesInputTag_;
  std::vector<std::string> candidatesNameInTree_;
  std::vector<UShort_t> candidatesN_;
  std::vector<Float_t*> candidatesPt_;
  std::vector<Float_t*> candidatesEta_;
  std::vector<Float_t*> candidatesPhi_;

  // Any boolean variables
  std::vector<edm::InputTag> filterDecisionTags_;
  std::vector<UChar_t> filterDecisions_;
};

#endif
