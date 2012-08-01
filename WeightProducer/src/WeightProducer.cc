// -*- C++ -*-
//
// Package:    WeightProducer
// Class:      WeightProducer
//
/**\class WeightProducer WeightProducer.cc RA2/WeightProducer/src/WeightProducer.cc

 Description: <one line class summary>

 Implementation:
 <Notes on implementation>
 */
//
//         Created:  Tue Nov 10 17:58:04 CET 2009
// $Id: WeightProducer.cc,v 1.22 2012/08/01 12:34:09 kaussen Exp $
//
//


// system include files
#include <cmath>
#include <memory>
#include <string>
#include <iostream>
#include <vector>

#include "TFile.h"
#include "TH1.h"

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ParameterSet/interface/FileInPath.h"

#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"

//
// class decleration
//

class WeightProducer: public edm::EDProducer {
   public:
      explicit WeightProducer(const edm::ParameterSet&);
      ~WeightProducer();

   private:
      //  virtual void beginJob() ;
      virtual void produce(edm::Event&, const edm::EventSetup&);
      virtual void endJob();

      const std::string _weightingMethod;
      const double _expo;
      const double _startWeight;
      const double _LumiScale;
      const double _xs;
      const double _NumberEvents;
      const double _lumi;

      edm::InputTag _weightName;
      std::vector<double> _puWeigths;
      double _weightFactor;
      bool _applyPUWeights;

    const int _PU; //use this for different PU scenarios

    std::vector<double> generate_flat10_weights(const TH1* data_npu_estimated) const;
    std::vector<double> generate_fall11_weights(const TH1* data_npu_estimated2) const;
    std::vector<double> generate_summer12_weights(const TH1* data_npu_estimated3) const;

    double getPUWeight(int npu) const;

};

WeightProducer::WeightProducer(const edm::ParameterSet& iConfig) :
   _weightingMethod(iConfig.getParameter<std::string> ("Method")), _expo(iConfig.getParameter<double> ("Exponent")),
         _startWeight(iConfig.getParameter<double> ("weight")), _LumiScale(iConfig.getParameter<double> ("LumiScale")),
         _xs(iConfig.getParameter<double> ("XS")), _NumberEvents(iConfig.getParameter<double> ("NumberEvts")), _lumi(
               iConfig.getParameter<double> ("Lumi")), _weightName(iConfig.getParameter<edm::InputTag> ("weightName")),
   	 _PU(iConfig.getParameter<int> ("PU"))

 {

   // Option 1: weight constant, as defined in cfg file
   if (_startWeight >= 0) {
      std::cout << "WeightProducer: Using constant event weight of " << _startWeight << std::endl;
   }

   // Option 2: weight from event
   else if (_weightingMethod == "FromEvent") {
      std::cout << "WeightProducer: Using weight from event" << std::endl;
   }

   // Option 3: compute new weight
   else if (_weightingMethod == "Constant") {
      _weightFactor = _lumi * _xs / _NumberEvents;
      std::cout << "WeightProducer: Using constant event weight of " << _weightFactor << std::endl;
      std::cout << "  Target luminosity (1/pb) : " << _lumi << std::endl;
      std::cout << "        Cross section (pb) : " << _xs << std::endl;
      std::cout << "          Number of events : " << _NumberEvents << std::endl;
   }

   else if (_weightingMethod == "PtHat") {
      _weightFactor = _lumi * _xs / (_NumberEvents * pow(15., _expo));
      std::cout << "WeightProducer: Using ptHat dependent event weight" << std::endl;
   }

   // Option 4: Use generator weight
   else if (_weightingMethod == "BinnedPythia" || _weightingMethod == "BinnedMadGraph") {
      std::cout << "WeightProducer: Using generator event weight" << std::endl;
   }

   // No option specified
   else {
      std::cerr << "WARNING: WeightProducer: No weighting option specified. Using event weights of 1" << std::endl;
   }

   ///This is to consider the lumi-uncertainty, i.e. to scale the weights up- or down by 1sigma of the lumi-scale
   ///uncertainty. In general the scale is 1.0!
   _weightFactor *= _LumiScale;
   if (_LumiScale != 1.) {
      std::cout << "WeightProducer: Scaling event weights by factor " << _LumiScale << std::endl;
   }

   // Optionally, compute multiplicative weight factors for PU reweighting
   // The weights are a function of the generated PU interactions and the
   // expected data distribution is given as a histogram from a ROOT file.
   // See https://twiki.cern.ch/twiki/bin/viewauth/CMS/PileupReweighting
   std::string fileNamePU = iConfig.getParameter<std::string> ("FileNamePUDataDistribution");
   if (fileNamePU.length() != 0 && fileNamePU != "NONE") {
      _applyPUWeights = true;
      edm::FileInPath filePUDataDistr(fileNamePU);

      std::cout << "WeightProducer: Applying multiplicative PU weights" << std::endl;
      std::cout << "  Reading PU scenario from '" << filePUDataDistr.fullPath() << "'" << std::endl;
      TFile file(filePUDataDistr.fullPath().c_str(), "READ");
      TH1 *h = 0;
      file.GetObject("pileup", h);
      if (h) {
         h->SetDirectory(0);
      } else {
         std::cerr << "ERROR in WeightProducer: Histogram 'pileup' does not exist in file '"
               << filePUDataDistr.fullPath() << "'\n.";
         std::cerr
               << "See https://twiki.cern.ch/twiki/bin/view/CMS/HamburgWikiAnalysisCalibration#Pile_Up_Reweighting for available input distributions."
               << std::endl;
         exit(1);
      }
      file.Close();

      std::cout << "  Computing weights" << std::endl;
	if(_PU==0) _puWeigths = generate_flat10_weights(h);
	if(_PU==1) _puWeigths = generate_fall11_weights(h);
	if(_PU==2) _puWeigths = generate_summer12_weights(h);


      delete h;
   } else {
      _applyPUWeights = false;
   }

   //register your products
   produces<double> ("weight");
}

WeightProducer::~WeightProducer() {
}

// ------------ method called to produce the data  ------------
void WeightProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup) {

   double resultWeight = 1.;

   //Option 1: constant start weight from config file
   if (_startWeight >= 0) {
      resultWeight = _startWeight;
   }
   //Option 2: existing weight variable in the event named as in _weightName
   else if (_weightingMethod == "FromEvent") {
      edm::Handle<double> event_weight;
      iEvent.getByLabel(_weightName, event_weight);
      resultWeight = (event_weight.isValid() ? (*event_weight) : 1.0);

      ///This is to consider the lumi-uncertainty, i.e. to scale the weights up- or down by 1sigma of the lumi-scale
      ///uncertainty. In general the scale is 1.0!
      resultWeight *= _LumiScale;
   }
   //Option 3: weighting from lumi, xs, and num evts
   else if (_weightingMethod == "Constant") {
      resultWeight = _weightFactor;
   } else if (_weightingMethod == "PtHat") {
      // Get pthat
      double ptHat = 0.;
      edm::Handle<GenEventInfoProduct> genEvtInfoHandle;
      iEvent.getByLabel("generator", genEvtInfoHandle);
      if (genEvtInfoHandle.isValid()) {
         ptHat = genEvtInfoHandle->binningValues()[0];
         resultWeight = _weightFactor * pow(ptHat, _expo);
      } else {
         std::cout << "WARNING:: PtHat information needed but not available: set weight to 1!" << std::endl;
         resultWeight = 1.;
      }
   } else if (_weightingMethod == "BinnedPythia") {
      // Get pthat
      double ptHat = 0.;
      edm::Handle<GenEventInfoProduct> genEvtInfoHandle;
      iEvent.getByLabel("generator", genEvtInfoHandle);
      if (genEvtInfoHandle.isValid()) {
         ptHat = genEvtInfoHandle->binningValues()[0];
         if (ptHat > 0.)
            resultWeight = 4.844e+10 * _lumi / 1000000;
         if (ptHat > 5.)
            resultWeight = 3.675e+10 * _lumi / 1650000;
         if (ptHat > 15.)
            resultWeight = 8.159e+08 * _lumi / 11000000;
         if (ptHat > 30.)
            resultWeight = 5.312e+07 * _lumi / 6583068;
         if (ptHat > 50.)
            resultWeight = 6.359e+06 * _lumi / 6600000;
         if (ptHat > 80.)
            resultWeight = 7.843e+05 * _lumi / 6589956;
         if (ptHat > 120.)
            resultWeight = 1.151e+05 * _lumi / 6127528;
         if (ptHat > 170.)
            resultWeight = 2.426e+04 * _lumi / 6220160;
         if (ptHat > 300.)
            resultWeight = 1.168e+03 * _lumi / 6432669;
         if (ptHat > 470.)
            resultWeight = 7.022e+01 * _lumi / 3990085;
         if (ptHat > 600.)
            resultWeight = 1.555e+01 * _lumi / 4245695;
         if (ptHat > 800.)
            resultWeight = 1.844e+00 * _lumi / 4053888;
         if (ptHat > 1000.)
            resultWeight = 3.321e-01 * _lumi / 2093222;
         if (ptHat > 1400.)
            resultWeight = 1.087e-02 * _lumi / 2196200;
         if (ptHat > 1800.)
            resultWeight = 3.575e-04 * _lumi / 293139;
         //std::cout << resultWeight << std::endl;
      } else {
         std::cout << "WARNING:: PtHat information needed but not available: set weight to 1!" << std::endl;
         resultWeight = 1.;
      }
   } else if (_weightingMethod == "BinnedMadGraph") {
      // Get pthat
      double ptHat = 0.;
      edm::Handle<GenEventInfoProduct> genEvtInfoHandle;
      iEvent.getByLabel("generator", genEvtInfoHandle);
      if (genEvtInfoHandle.isValid()) {
         ptHat = genEvtInfoHandle->binningValues()[0];
         if (ptHat > 100.)
            resultWeight = 7.0e+06 * _lumi / 21066112;
         if (ptHat > 250.)
            resultWeight = 1.71e+05 * _lumi / 20674219;
         if (ptHat > 500.)
            resultWeight = 5.2e+03 * _lumi / 14437469;
         if (ptHat > 1000.)
            resultWeight = 8.3e+01 * _lumi / 6294851;
         //std::cout << ptHat << " " << resultWeight << std::endl;
      } else {
         std::cout << "WARNING:: PtHat information needed but not available: set weight to 1!" << std::endl;
         resultWeight = 1.;
      }
   }
   // Optionally, multiply PU weight
   edm::Handle<std::vector<PileupSummaryInfo> > puInfo;
   iEvent.getByLabel("addPileupInfo", puInfo);
   int npu = 0;
   if (_applyPUWeights) {
      if (puInfo.isValid()) {
         std::vector<PileupSummaryInfo>::const_iterator puIt;
         int n = 0;
         for (puIt = puInfo->begin(); puIt != puInfo->end(); ++puIt, ++n) {
            //std::cout << " Pileup Information: bunchXing, nvtx: " << puIt->getBunchCrossing() << " " << puIt->getPU_NumInteractions() << std::endl;
            if (puIt->getBunchCrossing() == 0) { // Select in-time bunch crossing
               npu = puIt->getTrueNumInteractions();
               break;
            }
         }
         resultWeight *= getPUWeight(npu);
      } else
         std::cout << "No Valid PileupSummaryInfo Object! PU reweighing not applied!" << std::endl;
   }

   ///Also, here one could define look-up tables for all used samples.
   ///An identifying 'string' for the currently used sample could be read
   ///from the config file. Perhaps this can be obtained dirtectly from crab?
   //---------------------------------------------------------------------------

   // put weight into the Event
   std::auto_ptr<double> pOut(new double(resultWeight));
   iEvent.put(pOut, "weight");
}

// ------------ method called once each job just before starting event loop  ------------
//void
//WeightProducer::beginJob()
//{
//}

// ------------ method called once each job just after ending the event loop  ------------
void WeightProducer::endJob() {
}

// Get weight factor dependent on number of
// added PU interactions
// --------------------------------------------------
double WeightProducer::getPUWeight(int npu) const {
   double w = 1.;
   if (npu < static_cast<int> (_puWeigths.size())) {
      w = _puWeigths.at(npu);
   } else {
      std::cerr << "WARNING in WeightProcessor::getPUWeight: Number of PU vertices = " << npu
            << " out of histogram binning." << std::endl;
   }

   return w;
}

// Generate weights for given data PU distribution
// Code from: https://twiki.cern.ch/twiki/bin/viewauth/CMS/PileupReweighting
// --------------------------------------------------
std::vector<double> WeightProducer::generate_flat10_weights(const TH1* data_npu_estimated) const {
   // see SimGeneral/MixingModule/python/mix_E7TeV_FlatDist10_2011EarlyData_inTimeOnly_cfi.py; copy and paste from there:
   const double npu_probs[25] = { 0.0698146584, 0.0698146584, 0.0698146584, 0.0698146584, 0.0698146584, 0.0698146584,
         0.0698146584, 0.0698146584, 0.0698146584, 0.0698146584, 0.0698146584 /* <-- 10*/, 0.0630151648, 0.0526654164,
         0.0402754482, 0.0292988928, 0.0194384503, 0.0122016783, 0.007207042, 0.004003637, 0.0020278322, 0.0010739954,
         0.0004595759, 0.0002229748, 0.0001028162, 4.58337152809607E-05 /* <-- 24 */};
   std::vector<double> result(25);
   double s = 0.0;
   for (int npu = 0; npu < 25; ++npu) {
      double npu_estimated = data_npu_estimated->GetBinContent(data_npu_estimated->GetXaxis()->FindBin(npu));
      result[npu] = npu_estimated / npu_probs[npu];
      s += npu_estimated;
   }
   // normalize weights such that the total sum of weights over thw whole sample is 1.0, i.e., sum_i  result[i] * npu_probs[i] should be 1.0 (!)
   for (int npu = 0; npu < 25; ++npu) {
      result[npu] /= s;
   }
   return result;
}

std::vector<double> WeightProducer::generate_fall11_weights(const TH1* data_npu_estimated2) const {
    // build from flat10
    const double npu_probs[50] = {
    0.003388501,
    0.010357558,
    0.024724258,
    0.042348605,
    0.058279812,
    0.068851751,
    0.072914824,
    0.071579609,
    0.066811668,
    0.060672356,
    0.054528356,
    0.04919354,
    0.044886042,
    0.041341896,
    0.0384679,
    0.035871463,
    0.03341952,
    0.030915649,
    0.028395374,
    0.025798107,
    0.023237445,
    0.020602754,
    0.0180688,
    0.015559693,
    0.013211063,
    0.010964293,
    0.008920993,
    0.007080504,
    0.005499239,
    0.004187022,
    0.003096474,
    0.002237361,
    0.001566428,
    0.001074149,
    0.000721755,
    0.000470838,
    0.00030268,
    0.000184665,
    0.000112883,
    6.74043E-05,
    3.82178E-05,
    2.22847E-05,
    1.20933E-05,
    6.96173E-06,
    3.4689E-06,
    1.96172E-06,
    8.49283E-07,
    5.02393E-07,
    2.15311E-07,
    9.56938E-08
  };
    std::vector<double> result(50);
    double s = 0.0;
    for (int npu = 0; npu < 50; ++npu) {
        double npu_estimated = data_npu_estimated2->GetBinContent(data_npu_estimated2->GetXaxis()->FindBin(npu));
        result[npu] = npu_estimated / npu_probs[npu];
        s += npu_estimated;
    }
    // normalize weights such that the total sum of weights over thw whole sample is 1.0, i.e., sum_i  result[i] * npu_probs[i] should be 1.0 (!)
    for (int npu = 0; npu < 50; ++npu) {
        result[npu] /= s;
    }
    return result;
}

std::vector<double> WeightProducer::generate_summer12_weights(const TH1* data_npu_estimated3) const {

// Distribution used for Summer2012 MC.
  Double_t Summer2012[60] = {
    2.344E-05,
    2.344E-05,
    2.344E-05,
    2.344E-05,
    4.687E-04,
    4.687E-04,
    7.032E-04,
    9.414E-04,
    1.234E-03,
    1.603E-03,
    2.464E-03,
    3.250E-03,
    5.021E-03,
    6.644E-03,
    8.502E-03,
    1.121E-02,
    1.518E-02,
    2.033E-02,
    2.608E-02,
    3.171E-02,
    3.667E-02,
    4.060E-02,
    4.338E-02,
    4.520E-02,
    4.641E-02,
    4.735E-02,
    4.816E-02,
    4.881E-02,
    4.917E-02,
    4.909E-02,
    4.842E-02,
    4.707E-02,
    4.501E-02,
    4.228E-02,
    3.896E-02,
    3.521E-02,
    3.118E-02,
    2.702E-02,
    2.287E-02,
    1.885E-02,
    1.508E-02,
    1.166E-02,
    8.673E-03,
    6.190E-03,
    4.222E-03,
    2.746E-03,
    1.698E-03,
    9.971E-04,
    5.549E-04,
    2.924E-04,
    1.457E-04,
    6.864E-05,
    3.054E-05,
    1.282E-05,
    5.081E-06,
    1.898E-06,
    6.688E-07,
    2.221E-07,
    6.947E-08,
    2.047E-08
   };  

    std::vector<double> result(60);
    double s = 0.0;
    for (int npu = 0; npu < 60; ++npu) {
        double npu_estimated = data_npu_estimated3->GetBinContent(data_npu_estimated3->GetXaxis()->FindBin(npu));
        result[npu] = npu_estimated / Summer2012[npu];
        s += npu_estimated;
    }

    // normalize weights such that the total sum of weights over the whole sample is 1.0, i.e., sum_i  result[i] * Summer2012[i] should be 1.0 (!)
    for (int npu = 0; npu < 60; ++npu) {
        result[npu] /= s;
    }
    return result;
}

//define this as a plug-in
DEFINE_FWK_MODULE( WeightProducer);
