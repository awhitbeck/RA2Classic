#ifndef DATA_SET_H
#define DATA_SET_H

#include <map>
#include <vector>

#include "TString.h"

#include "Config.h"
#include "Event.h"
#include "Selection.h"

class DataSet;
typedef std::vector<const DataSet*> DataSets;
typedef std::vector<const DataSet*>::const_iterator DataSetIt;
typedef std::vector<const DataSet*>::const_reverse_iterator DataSetRIt;
typedef std::map<TString,const DataSet*> DataSetUidMap;
typedef std::map<TString,const DataSet*>::const_iterator DataSetUidIt;

class DataSet {
public:
  enum Type { Data, MC, Prediction, Signal };

  static TString uid(const TString &label, const TString &selectionUid);
  static TString uid(const TString &label, const Selection* selection);
  static const DataSet* find(const TString &uid);
  static const DataSet* find(const TString &label, const Selection* selection);
  static DataSets findAllUnselected() {
    return findAllWithSelection("unselected");
  }
  static DataSets findAllWithSelection(const TString &selectionUid);
  static DataSets findAllWithLabel(const TString &label);
  static DataSetUidIt begin() { return dataSetUidMap_.begin(); }
  static DataSetUidIt end() { return dataSetUidMap_.end(); }
  static void init(const Config &cfg, const TString key);
  static void clear();
  static bool uidExists(const TString &uid);
  static bool labelExists(const TString &label);
  static Type toType(const TString &type);
  static TString toString(Type type);

  virtual ~DataSet();

  TString uid() const { return uid(label(),selectionUid()); }
  Type type() const { return type_; }
  TString label() const { return label_; }
  TString selectionUid() const { return selectionUid_; }

  unsigned int size() const { return evts_.size(); }
  double yield() const { return yield_; }		// Return weighted number of events
  double stat() const { return stat_; }                 // Return statistical uncertainty on yield
  double systDn() const { return systDn_; }
  double systUp() const { return systUp_; }
  bool hasSyst() const { return hasSyst_; }
  EventIt evtsBegin() const { return evts_.begin(); }
  EventIt evtsEnd() const { return evts_.end(); }


private:
  static DataSetUidMap dataSetUidMap_;
  static bool isInit_;

  const Type type_;
  const TString label_;   // This is the label specified in the config
  const bool hasMother_;

  TString selectionUid_;
  Events evts_;
  double yield_;
  double stat_;
  double systDn_;
  double systUp_;
  bool hasSyst_;

  DataSet(Type type, const TString &label, const TString &selection, const TString &fileName, const TString &treeName, const TString &weight, const std::vector<TString> &uncDn, const std::vector<TString> &uncUp, const std::vector<TString> &uncLabel, double scale);
  DataSet(const DataSet *ds, const TString &selectionUid, const Events &evts);
  void computeYield();
};
#endif
