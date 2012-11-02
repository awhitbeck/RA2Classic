#include <cmath>
#include <cstdlib>

#include "Selection.h"


std::vector<Selection*> Selection::garbageCollection_;

// Create different selections as specified in a config file
// Expect format [key] :: label: [label]; cuts: [previously defined label]+[cuts]+...
// ---------------------------------------------------------------
std::vector<Selection*> Selection::createSelections(const Config &cfg, const TString key) {
  std::vector<Selection*> selections; // Collection of selections to be returned

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
	for(std::vector<Selection*>::const_iterator itS = selections.begin();
	    itS != selections.end(); ++itS) {
	  if( (*itS)->label() == *it2 ) { // A selection with this name exists; reuse it
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
      selections.push_back(sequence);
    } else {
      std::cerr << "\n\nERROR in Selection::createSelection(): wrong syntax" << std::endl;
      std::cerr << "  in line with key '" << key << "'" << std::endl;
      std::cerr << "  in config file '" << cfg.fileName() << "'" << std::endl;
      std::cerr << "  Expect selections to be defined as" << std::endl;
      std::cerr << "  [key] :: label: [label]; cuts: [previously defined label]+[cuts]+..." << std::endl;
      exit(-1);
    }
  }

  return selections;
}


// Use this method to delete all existing selections
// This correctly treats reused selections
// ---------------------------------------------------------------
void Selection::deleteAllSelections() {
  for(std::vector<Selection*>::iterator it = garbageCollection_.begin();
      it != garbageCollection_.end(); ++it) {
    delete *it;
  }
}


// Constructor. Each selection needs a unique label
// ---------------------------------------------------------------
SelectionSequence::SelectionSequence(const TString &label)
  : label_(label) {
  garbageCollection_.push_back(this);
}


// ---------------------------------------------------------------
DataSet* SelectionSequence::operator()(const DataSet* dataSet) const {
  DataSet* tmp1 = (*sels_.front())(dataSet);
  DataSet* tmp2 = 0;
  for(std::vector<const Selection*>::const_iterator it = sels_.begin()+1;
      it != sels_.end(); ++it) {
    tmp2 = (**it)(tmp1);
    delete tmp1;
    tmp1 = tmp2;
  }
  tmp1->selection(label());

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
Cut::Cut(const TString &cut)
  : cut_(cut), count_(0) {
  garbageCollection_.push_back(this);

  // Check whether cut is only applied to specified datasets
  TString dataSetCfg = "";
  if( Config::enclosed(cut_,"(",")",dataSetCfg) ) {
    Config::split(dataSetCfg,",",appliedToDataSets_);
    for(std::vector<TString>::const_iterator it = appliedToDataSets_.begin();
	it != appliedToDataSets_.end(); ++it) {
      if( !DataSet::exists(*it) ) {
	std::cerr << "\n\nERROR in Cut::Cut(): dataset '" << *it << "' does not exist" << std::endl;
	exit(-1);
      }
    }
    TString tmp;
    Config::split(cut_,"(",cut_,tmp);
  }

  // Read cut variable and values
  if( cut_.Contains(">") ) {	// Expect VAR > X
    std::vector<TString> cutCfg;
    Config::split(cut_,">",cutCfg);
    if( cutCfg.size() == 2 ) {
      var_ = cutCfg.at(0);
      min_ = cutCfg.at(1).Atof();
      max_ = 99999.;
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
      min_ = -99999.;
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
}

// ---------------------------------------------------------------
DataSet* Cut::operator()(const DataSet* dataSet) const {
  // Check if cut is to be applied to this data set
  bool apply = true;
  if( appliedToDataSets_.size() ) {
    apply = false;
    for(std::vector<TString>::const_iterator it = appliedToDataSets_.begin();
	it != appliedToDataSets_.end(); ++it) {
      if( dataSet->label() == *it ) {
	apply = true;
	break;
      }
    }
  }

  Events passed;
  for(EventIt it = dataSet->begin(); it != dataSet->end(); ++it) {
    double val = (*it)->get(var_);
    if( apply ) {
      if( varIsAbs_ ) val = std::abs(val);
      if( val > min_ && val < max_ ) {
	passed.push_back(*it);
      }
    } else {
      passed.push_back(*it);
    }
    //      std::cout << ">>> " << var_ << ": " << val << " > " << min_ << " && " << val << " < " << max_ << std::endl;
  }
  count_ = passed.size();

  return new SelectedDataSet(dataSet->type(),dataSet->label(),label(),passed);
}
