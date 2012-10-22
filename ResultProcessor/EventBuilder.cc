#include <cstdlib>
#include <iostream>
#include <vector>

#include "TFile.h"
#include "TTree.h"

#include "EventBuilder.h"
#include "Variable.h"


Events EventBuilder::operator()(const TString &fileName, const TString &treeName, const TString &weightVar, double weightScale) const {
  // Get tree from file
  TFile file(fileName,"READ");
  TTree* tree = 0;
  file.GetObject(treeName,tree);
  if( !tree ) {
    std::cerr << "\n\nERROR in EventBuilder::operator(): no tree with name '" << treeName << "' in file '" << fileName << "'" << std::endl;
    exit(-1);
  }

  // Setup vector with variables to be read from tree
  std::vector<Float_t> varsFloat_t(Variable::nVars(),0.);
  std::vector<Int_t> varsInt_t(Variable::nVars(),0);
  std::vector<UInt_t> varsUInt_t(Variable::nVars(),0);
  std::vector<UShort_t> varsUShort_t(Variable::nVars(),0);
  unsigned int idxFloat_t = 0;
  unsigned int idxInt_t = 0;
  unsigned int idxUInt_t = 0;
  unsigned int idxUShort_t = 0;
  Float_t weightFromTree = 1.;
  // Setup branches
  for(std::vector<TString>::const_iterator it = Variable::begin(); it != Variable::end(); ++it) {
    bool treeHasVar = true;
    if( tree->GetListOfBranches()->FindObject(*it) == 0 ) {
      treeHasVar = false;
      std::cerr << "\nWARNING in EventBuilder" << std::endl;
      std::cerr << "  - TTree '" << treeName << "' in file '" << fileName << "' has no variable named '" << *it << "'" << std::endl;
      std::cerr << "  - Using default value 0 instead" << std::endl;
    }
    if( Variable::type(*it) == "Float_t" ) {
      if( treeHasVar ) tree->SetBranchAddress(*it,&varsFloat_t.at(idxFloat_t));
      ++idxFloat_t;
      if( *it == weightVar && treeHasVar ) {
	tree->SetBranchAddress(*it,&weightFromTree);
      }
    } else if( Variable::type(*it) == "Int_t" ) {
      if( treeHasVar ) tree->SetBranchAddress(*it,&varsInt_t.at(idxInt_t));
      ++idxInt_t;
    } else if( Variable::type(*it) == "UInt_t" ) {
      if( treeHasVar ) tree->SetBranchAddress(*it,&varsUInt_t.at(idxUInt_t));
      ++idxUInt_t;
    } else if( Variable::type(*it) == "UShort_t" ) {
      if( treeHasVar ) tree->SetBranchAddress(*it,&varsUShort_t.at(idxUShort_t));
      ++idxUShort_t;
    }
  }  

  // Loop over tree and build events
  Events evts;
  for(int i = 0; i < tree->GetEntries(); ++i) {
    //for(int i = 0; i < 100000; ++i) {
    //if( i%100 == 0 ) std::cout << "  " << i << std::endl;

    // Read variables of this entry
    tree->GetEntry(i);

    // Create new event and fill variables
    Event* evt = new Event();
    idxFloat_t = 0;
    idxInt_t = 0;
    idxUInt_t = 0;
    idxUShort_t = 0;
    for(std::vector<TString>::const_iterator it = Variable::begin(); it != Variable::end(); ++it) {
      if( Variable::type(*it) == "Float_t" ) {
	evt->set(*it,varsFloat_t.at(idxFloat_t));
	++idxFloat_t;
      } else if( Variable::type(*it) == "Int_t" ) {
	evt->set(*it,varsInt_t.at(idxInt_t));
	++idxInt_t;
      } else if( Variable::type(*it) == "UInt_t" ) {
	evt->set(*it,varsUInt_t.at(idxUInt_t));
	++idxUInt_t;
      } else if( Variable::type(*it) == "UShort_t" ) {
	evt->set(*it,varsUShort_t.at(idxUShort_t));
	++idxUShort_t;
      }
    }
    evt->setWeight(weightFromTree*weightScale);

    evts.push_back(evt);
  }

  file.Close();

  return evts;
}
