//
// Original Author:  Matthias Schroeder,,,
//         Created:  Mon Jul 30 16:39:54 CEST 2012
// $Id$
//
//

#ifndef RA2CLASSIC_TREEMAKER
#define RA2CLASSIC_TREEMAKER

// system include files
#include <memory>

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

  TString treeName_;
  TTree* tree_;

  edm::InputTag vertexCollectionTag_;
  UShort_t nVtx_;
  edm::InputTag htTag_;
  Float_t ht_;
  edm::InputTag mhtTag_;
  Float_t mht_;
};

#endif
