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
// ---------------------------------------------------------------
void Selection::init(const Config &cfg, const TString key) {
  if( isInit_ ) {
    std::cerr << "WARNING: Selections already initialized. Skipping." << std::endl;
  } else {
    std::cout << "Preparing selections...  " << std::flush;

    // First, add dummy selection (for unselected datasets)
    SelectionSequence* sequence = new SelectionSequence("unselected");
    sequence->addDummyCut();
    
    // Then, read defined selections from config
    std::vector<Config::Attributes> attrList = cfg.listOfAttributes(key);
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

// std::vector<Selection*> Selection::createSelections(const Config &cfg, const TString key) {
//   std::vector<Selection*> selections; // Collection of selections to be returned

//   std::vector<Config::Attributes> attrList = cfg.listOfAttributes(key);
//   for(std::vector<Config::Attributes>::const_iterator it = attrList.begin();
//       it != attrList.end(); ++it) {
//     if( it->hasName("label") && it->hasName("cuts") ) {
//       TString label = it->value("label"); // Specifies this selection
//       TString cuts = it->value("cuts");	  // Cuts; can be any combination of cuts and previously defined selections

//       // Setup this selection sequence
//       SelectionSequence* sequence = new SelectionSequence(label);

//       // Loop over cuts of this selection
//       std::vector<TString> sels;
//       cfg.split(cuts,"+",sels); // Cuts are separated by '+'
//       for(std::vector<TString>::const_iterator it2 = sels.begin();
// 	  it2 != sels.end(); ++it2) {
// 	// Loop over previously defined selection sequences
// 	// and check whether this cut corresponds to one of their labels
// 	Selection* sel = 0;
// 	for(std::vector<Selection*>::const_iterator itS = selections.begin();
// 	    itS != selections.end(); ++itS) {
// 	  if( (*itS)->label() == *it2 ) { // A selection with this name exists; reuse it
// 	    sel = *itS;
// 	    break;
// 	  }
// 	}
// 	if( sel ) {	// Reuse previously defined selection
// 	  sequence->add(sel);
// 	} else {	// Add new cut
// 	  sequence->add(new Cut(*it2));
// 	}
//       }	// End of loop over cuts

//       // Add this selection sequence to the result
//       selections.push_back(sequence);
//     } else {
//       std::cerr << "\n\nERROR in Selection::createSelection(): wrong syntax" << std::endl;
//       std::cerr << "  in line with key '" << key << "'" << std::endl;
//       std::cerr << "  in config file '" << cfg.fileName() << "'" << std::endl;
//       std::cerr << "  Expect selections to be defined as" << std::endl;
//       std::cerr << "  [key] :: label: [label]; cuts: [previously defined label]+[cuts]+..." << std::endl;
//       exit(-1);
//     }
//   }

//   return selections;
// }


// Use this method to delete all existing selections
// This correctly treats reused selections
// ---------------------------------------------------------------
void Selection::clear() {
  for(std::vector<Selection*>::iterator it = garbageCollection_.begin();
      it != garbageCollection_.end(); ++it) {
    delete *it;
  }
}


// Constructor. Each selection needs a unique uid
// ---------------------------------------------------------------
SelectionSequence::SelectionSequence(const TString &uid)
  : uid_(uid) {
  garbageCollection_.push_back(this);
}



// ---------------------------------------------------------------
Events SelectionSequence::apply(EventIt begin, EventIt end) const {
  Events tmp1 = sels_.front()->apply(begin,end);
  Events tmp2;
  for(std::vector<const Selection*>::const_iterator it = sels_.begin()+1;
      it != sels_.end(); ++it) {
    tmp2 = (*it)->apply(tmp1.begin(),tmp1.end());
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


// ---------------------------------------------------------------
Cut::Cut(const TString &cut, bool isDummy)
  : isDummy_(isDummy), cut_(cut) {
  garbageCollection_.push_back(this);

  if( isDummy_ ) {
    var_ = "";
    varIsAbs_ = false;
    min_ = 0.;
    max_ = 0.;
  } else {
    // Read cut variable and values
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
}


// ---------------------------------------------------------------
Events Cut::apply(EventIt begin, EventIt end) const {
  Events passed;
  for(EventIt it = begin; it != end; ++it) {
    if( !isDummy_ ) {
      double val = (*it)->get(var_);
      if( varIsAbs_ ) val = std::abs(val);
      if( val > min_ && val < max_ ) {
	passed.push_back(*it);
//       } else {
// 	if( var_ == "HT" ) std::cout << std::setprecision(10) << ">>> " << var_ << ": " << val << " > " << min_ << " && " << val << " < " << max_ << std::endl;

      }
    } else {
      passed.push_back(*it);
    }
  }

  return passed;
}
