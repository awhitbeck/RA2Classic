#include <iomanip>
#include <iostream>
#include <cmath>
#include <cstdlib>

#include "Selection.h"
#include "Variable.h"


std::vector<Selection*> Selection::garbageCollection_;
std::vector<Selection*> Selection::selections_; // Collection of selections to be returned
bool Selection::isInit_ = false;


// Create different selections as specified in a config file
// Expect format [key] :: label: [label]; cuts: [previously defined label]+[cuts]+...
// Cuts can optionally be restricted to certain datasets by specifying
// the names of those datasets in brackets directly after the cut:
// ...; cuts: [cut1] ([dataset1],[dataset2],...) + [cut2] + ...
// ---------------------------------------------------------------
void Selection::init(const Config &cfg, const TString key) {
  if( isInit_ ) {
    std::cerr << "WARNING: Selections already initialized. Skipping." << std::endl;
  } else {
    std::cout << "  Preparing selections...  " << std::flush;

    // First, add dummy selection (for unselected datasets)
    SelectionSequence* sequence = new SelectionSequence("unselected");
    sequence->add(new Cut());
    
    // Then, read defined selections from config
    std::vector<Config::Attributes> attrList = cfg(key);
    for(std::vector<Config::Attributes>::const_iterator it = attrList.begin();
	it != attrList.end(); ++it) {
      if( it->hasName("label") && it->hasName("cuts") ) {
	TString label = it->value("label"); // Specifies this selection
	TString cuts = it->value("cuts");	  // Cuts; can be any combination of cuts and previously defined selections
	
	// Setup this selection sequence
	SelectionSequence* sequence = new SelectionSequence(label);
	
	// Loop over cuts of this selection
	std::vector<TString> sels;
	cfg.split(cuts,"+",sels); // Cuts are separated by '+'
	for(std::vector<TString>::const_iterator it2 = sels.begin();
	    it2 != sels.end(); ++it2) {
	  // Loop over previously defined selection sequences
	  // and check whether this cut corresponds to one of their labels
	  Selection* sel = 0;
	  for(SelectionIt itS = selections_.begin(); itS != selections_.end(); ++itS) {
	    if( (*itS)->uid() == *it2 ) { // A selection with this name exists; reuse it
	    sel = *itS;
	    break;
	    }
	  }
	  if( sel ) {	// Reuse previously defined selection
	    sequence->add(sel);
	  } else {	// Add new cut
	    sequence->add(new Cut(*it2));
	  }
	}	// End of loop over cuts
	
	// Add this selection sequence to the result
	selections_.push_back(sequence);
      } else {
	std::cerr << "\n\nERROR in Selection::init(): wrong syntax" << std::endl;
	std::cerr << "  in line with key '" << key << "'" << std::endl;
	std::cerr << "  in config file '" << cfg.fileName() << "'" << std::endl;
	std::cerr << "  Expect selections to be defined as" << std::endl;
	std::cerr << "  [key] :: label: [label]; cuts: [previously defined label]+[cuts]+..." << std::endl;
	exit(-1);
      }
    }
    isInit_ = true;
    std::cout << "ok" << std::endl;
  }
}


// Use this method to delete all existing selections
// This correctly treats reused selections
// ---------------------------------------------------------------
void Selection::clear() {
  for(std::vector<Selection*>::iterator it = garbageCollection_.begin();
      it != garbageCollection_.end(); ++it) {
    delete *it;
  }
}


// ---------------------------------------------------------------
unsigned int Selection::maxLabelLength() {
  unsigned int s = 0;
  for(SelectionIt its = Selection::begin(); its != Selection::end(); ++its) {
    if( (*its)->uid().Length() > s ) s = (*its)->uid().Length();
  }
  
  return s;
}



// Constructor. Each selection needs a unique uid
// ---------------------------------------------------------------
SelectionSequence::SelectionSequence(const TString &uid)
  : uid_(uid) {
  garbageCollection_.push_back(this);
}



// ---------------------------------------------------------------
Events SelectionSequence::apply(EventIt begin, EventIt end, const TString &dataSetLabel) const {
  Events tmp1 = sels_.front()->apply(begin,end,dataSetLabel);
  Events tmp2;
  for(std::vector<const Selection*>::const_iterator it = sels_.begin()+1;
      it != sels_.end(); ++it) {
    tmp2 = (*it)->apply(tmp1.begin(),tmp1.end(),dataSetLabel);
    tmp1.clear();
    tmp1 = tmp2;
  }

  return tmp1;
}


// ---------------------------------------------------------------
void SelectionSequence::print() const {
  for(std::vector<const Selection*>::const_iterator it = sels_.begin();
      it != sels_.end(); ++it) {
    (*it)->print();
  }
}


// Will create dummy cut (that lets pass every event)
// with cut = 'none'
// ---------------------------------------------------------------
Cut::Cut()
  : isDummy_(true), cut_("none") {
  garbageCollection_.push_back(this);
  var_ = "";
  varIsAbs_ = false;
  min_ = 0.;
  max_ = 0.;
}

// ---------------------------------------------------------------
Cut::Cut(const TString &cut)
  : isDummy_(false), cut_(cut) {
  garbageCollection_.push_back(this);

  // Check whether cut is only applied to specified datasets
  // In that case, the names of those datasets are expected in
  // parentheses '()' after the cut expression
  TString dataSetNames = "";
  if( Config::enclosed(cut_,"(",")",dataSetNames) ) { // Extract substring of cut_ in parentheses
    Config::split(dataSetNames,",",appliedToDataSets_);	// Datasetnames separated by comma
    // Remove dataset-specification term, i.e. the part in parentheses,
    // from cut_ expression
    TString tmp;
    Config::split(cut_,"(",cut_,tmp);
  }

  // Read cut variable and values from cut_ expression
  if( cut_.Contains(">") ) {	// Expect VAR > X
    std::vector<TString> cutCfg;
    Config::split(cut_,">",cutCfg);
    if( cutCfg.size() == 2 ) {
      var_ = cutCfg.at(0);
      min_ = cutCfg.at(1).Atof();
      max_ = 99999999.;
      varIsAbs_ = false;
    } else {
      std::cerr << "\n\nERROR in Cut::Cut(): wrong syntax" << std::endl;
      exit(-1);
    }
  } else if( cut_.Contains("<") ) { // Expect VAR < X or X < VAR < Y
    std::vector<TString> cutCfg;
    Config::split(cut_,"<",cutCfg);
    if( cutCfg.size() == 2 ) { // Expect VAR < X
      var_ = cutCfg.at(0);
      min_ = -99999999.;
      max_ = cutCfg.at(1).Atof();
      varIsAbs_ = false;
    } else if( cutCfg.size() == 3 ) { // Expect X < VAR < Y
      min_ = cutCfg.at(0).Atof();
      var_ = cutCfg.at(1);
      max_ = cutCfg.at(2).Atof();
      varIsAbs_ = false;
    } else {
      std::cerr << "\n\nERROR in Cut::Cut(): wrong syntax" << std::endl;
      exit(-1);
    }
  } else {
    std::cerr << "\n\nERROR in Cut::Cut(): wrong syntax" << std::endl;
    exit(-1);
  }
  
  // Check if cut variable exists
  if( !Variable::exists(var_) ) {
    std::cerr << "\n\nERROR in Cut::Cut(): unknown variable '" << var_ << "'" << std::endl;
    exit(-1);
  }
}


// ---------------------------------------------------------------
Events Cut::apply(EventIt begin, EventIt end, const TString &dataSetLabel) const {

  // Check if cut is to be applied to the specified data set
  bool applyCut = !isDummy_;
  if( applyCut && appliedToDataSets_.size() ) { // If there are datasets specified, look for agreement; otherwise, always apply cut
    applyCut = false;
    for(std::vector<TString>::const_iterator it = appliedToDataSets_.begin();
	it != appliedToDataSets_.end(); ++it) {
      if( dataSetLabel == *it ) {
	applyCut = true;
	break;
      }
    }
  }

  Events passed;		// The resulting vector of events passing this cut

  // Loop over events and check if cut is passed
  for(EventIt it = begin; it != end; ++it) {
    if( applyCut ) {		// Check only if this cut is not a dummy and if it is applied to the current dataset
      double val = (*it)->get(var_);
      if( varIsAbs_ ) val = std::abs(val);
      if( val > min_ && val < max_ ) {
	passed.push_back(*it);
      }
    } else {
      passed.push_back(*it);
    }
  }

  return passed;
}



// ---------------------------------------------------------------
void Cut::print() const {
  TString txt = "";
  if( isDummy_ ) {
    txt += "NONE (dummy)";
  } else {
    txt += cut_;
    if( appliedToDataSets_.size() ) {
      txt += " (applied only to ";
      for(std::vector<TString>::const_iterator it = appliedToDataSets_.begin();
	  it != appliedToDataSets_.end(); ++it) {
	if( it != appliedToDataSets_.begin() ) txt += ", ";
	txt += "'"+(*it)+"'";
      }
      txt += ")";
    }
  }

  std::cout << "    " << txt << std::endl;
}
