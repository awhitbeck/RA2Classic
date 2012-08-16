// -*- C++ -*-
//
// Package:    QCDBkgRS
// Class:      QCDBkgRS
// 
/**\class QCDBkgRS QCDBkgRS.cc RA2Classic/QCDBkgRS/src/QCDBkgRS.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Kristin Heine,,,DESY
//         Created:  Tue Aug  7 15:55:02 CEST 2012
// $Id: QCDBkgRS.cc,v 1.1 2012/08/15 08:52:33 kheine Exp $
//
//

#include "RA2Classic/QCDBkgRS/interface/QCDBkgRS.h"


#include <TROOT.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TPostScript.h>


//--------------------------------------------------------------------------
QCDBkgRS::QCDBkgRS(const edm::ParameterSet& iConfig) 
{
   rebalancedJetPt_ = iConfig.getParameter<double> ("RebalanceJetPt");
   rebalanceMode_ = iConfig.getParameter<std::string> ("RebalanceMode");
   nSmearedJets_ = iConfig.getParameter<int> ("NSmearedJets");
   smearedJetPt_ = iConfig.getParameter<double> ("SmearedJetPt");
   PtBinEdges_scaling_ = iConfig.getParameter<std::vector<double> > ("PtBinEdges_scaling");
   EtaBinEdges_scaling_ = iConfig.getParameter<std::vector<double> > ("EtaBinEdges_scaling");
   AdditionalSmearing_ = iConfig.getParameter<std::vector<double> > ("AdditionalSmearing");
   LowerTailScaling_ = iConfig.getParameter<std::vector<double> > ("LowerTailScaling");
   UpperTailScaling_ = iConfig.getParameter<std::vector<double> > ("UpperTailScaling");
   AdditionalSmearing_variation_ = iConfig.getParameter<double> ("AdditionalSmearing_variation");
   LowerTailScaling_variation_ = iConfig.getParameter<double> ("LowerTailScaling_variation");
   UpperTailScaling_variation_ = iConfig.getParameter<double> ("UpperTailScaling_variation");
   smearCollection_ = iConfig.getParameter<std::string> ("SmearCollection");

   vertices_ = iConfig.getParameter<edm::InputTag>("VertexCollection");
   genjets_ = iConfig.getParameter<edm::InputTag> ("genjetCollection");
   jets_ = iConfig.getParameter<edm::InputTag> ("jetCollection");
   jets_reb_ = iConfig.getParameter<std::string> ("jetCollection_reb");
   jets_smeared_ = iConfig.getParameter<std::string> ("jetCollection_smeared");
   genjets_smeared_ = iConfig.getParameter<std::string> ("genjetCollection_smeared");
   uncertaintyName_ = iConfig.getParameter<std::string> ("uncertaintyName");
   inputhist1HF_ = iConfig.getParameter<std::string> ("InputHisto1_HF");
   inputhist2HF_ = iConfig.getParameter<std::string> ("InputHisto2_HF");
   inputhist3pHF_ = iConfig.getParameter<std::string> ("InputHisto3p_HF");
   inputhist1NoHF_ = iConfig.getParameter<std::string> ("InputHisto1_NoHF");
   inputhist2NoHF_ = iConfig.getParameter<std::string> ("InputHisto2_NoHF");
   inputhist3pNoHF_ = iConfig.getParameter<std::string> ("InputHisto3p_NoHF");
   controlPlots_ = iConfig.getParameter<bool> ("ControlPlots");
   smearingfile_ = iConfig.getParameter<std::string> ("SmearingFile");
   bprobabilityfile_ = iConfig.getParameter<std::string> ("BProbabilityFile");
   outputfile_ = iConfig.getParameter<std::string> ("OutputFile");
   NRebin_ = iConfig.getParameter<int> ("NRebin");
   weightName_ = iConfig.getParameter<edm::InputTag> ("weightName");
   absoluteTailScaling_ = iConfig.getParameter<bool> ("absoluteTailScaling");
   cleverPrescaleTreating_ = iConfig.getParameter<bool> ("cleverPrescaleTreating");
   A0RMS_ = iConfig.getParameter<double> ("A0RMS");
   A1RMS_ = iConfig.getParameter<double> ("A1RMS");
   probExtreme_ = iConfig.getParameter<double> ("probExtreme");
   MHTmin_ = iConfig.getParameter<double> ("MHTmin");
   MHTmax_ = iConfig.getParameter<double> ("MHTmax");
   HTmin_ = iConfig.getParameter<double> ("HTmin");
   HTmax_ = iConfig.getParameter<double> ("HTmax");
   NbinsMHT_ = iConfig.getParameter<int> ("NbinsMHT");
   NbinsHT_ = iConfig.getParameter<int> ("NbinsHT");
   Ntries_ = iConfig.getParameter<int> ("Ntries");
   NJets_ = iConfig.getParameter<int> ("NJets");
   JetsHTPt_ = iConfig.getParameter<double> ("JetsHTPt");
   JetsHTEta_ = iConfig.getParameter<double> ("JetsHTEta");
   JetsMHTPt_ = iConfig.getParameter<double> ("JetsMHTPt");
   JetsMHTEta_ = iConfig.getParameter<double> ("JetsMHTEta");
   JetDeltaMin_ = iConfig.getParameter<std::vector<double> > ("JetDeltaMin");
   MHTcut_low_ = iConfig.getParameter<double> ("MHTcut_low");
   MHTcut_medium_ = iConfig.getParameter<double> ("MHTcut_medium");
   MHTcut_high_ = iConfig.getParameter<double> ("MHTcut_high");
   HTcut_low_ = iConfig.getParameter<double> ("HTcut_low");
   HTcut_medium_ = iConfig.getParameter<double> ("HTcut_medium");
   HTcut_high_ = iConfig.getParameter<double> ("HTcut_high");
   HTcut_veryhigh_ = iConfig.getParameter<double> ("HTcut_veryhigh");
   HTcut_extremehigh_ = iConfig.getParameter<double> ("HTcut_extremehigh");

   PtBinEdges_ = iConfig.getParameter<std::vector<double> > ("PtBinEdges");
   EtaBinEdges_ = iConfig.getParameter<std::vector<double> > ("EtaBinEdges");

   unsigned int needed_dim = (PtBinEdges_scaling_.size() - 1) * (EtaBinEdges_scaling_.size() - 1);
   if (AdditionalSmearing_.size() != needed_dim) {
      throw edm::Exception(edm::errors::Configuration, "AdditionalSmearing has not correct dimension");
   }
   if (LowerTailScaling_.size() != needed_dim) {
      throw edm::Exception(edm::errors::Configuration, "LowerTailScaling has not correct dimension");
   }
   if (UpperTailScaling_.size() != needed_dim) {
      throw edm::Exception(edm::errors::Configuration, "UpperTailScaling has not correct dimension");
   }
 
   // Different seed per initialization
   gRandom->SetSeed(0);
   rand_ = new TRandom3(0);

   // get object of class SmearFunction 
   smearFunc_ = new SmearFunction(iConfig); 
}
//--------------------------------------------------------------------------
  
//--------------------------------------------------------------------------
QCDBkgRS::~QCDBkgRS()
{
   PtBinEdges_.clear();
   EtaBinEdges_.clear();

   delete smearFunc_;

   if (rand_)
      delete rand_;
}
//--------------------------------------------------------------------------

//
// member functions
//

//--------------------------------------------------------------------------
std::string QCDBkgRS::GetName(const std::string plot, const std::string uncert, const std::string ptbin) const {
   std::string result(plot);
   if (uncert != "" && uncert != " ")
      result += "_" + uncert;
   if (ptbin != "" && ptbin != " ")
      result += "_" + ptbin;
   return result;
}
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
int QCDBkgRS::GetIndex(const double& x, const std::vector<double>* vec) {
   int index = -1;
   // this is a check
   //int index = 0;
   for (std::vector<double>::const_iterator it = vec->begin(); it != vec->end(); ++it) {
      if ((*it) > fabs(x))
         break;
      ++index;
   }
   if (index < 0)
      index = 0;
   if (index > (int) vec->size() - 2)
      index = vec->size() - 2;

   return index;
}
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
// pt resolution for KinFitter
double QCDBkgRS::JetResolution_Pt2(const double& pt, const double& eta, const int& i) {
   int i_jet;
   i < 2 ? i_jet = i : i_jet = 2;
   int i_eta = GetIndex(eta, &EtaBinEdges_);
   //return pow(pt, 2) * pow(smearFunc_->getSigmaPtScaledForRebalancing(i_jet, i_eta)->Eval(pt), 2);
   return pow(pt, 2) * pow(smearFunc_->getSigmaPtForRebalancing(i_jet, i_eta)->Eval(pt), 2);
}
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
// relative pt resolution for KinFitter
double QCDBkgRS::JetResolution_Ptrel(const double& pt, const double& eta, const int& i) {
   int i_jet;
   i < 2 ? i_jet = i : i_jet = 2;
   int i_eta = GetIndex(eta, &EtaBinEdges_);
   return smearFunc_->getSigmaPtScaledForRebalancing(i_jet, i_eta)->Eval(pt);
}
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
// eta resolution for KinFitter
double QCDBkgRS::JetResolution_Eta2(const double& e, const double& eta) {
   //may be artifically reduced (no angular fit)
   return (pow(0.05 / TMath::Sqrt(e), 2) + pow(0.005, 2)) / 1.e6;
}
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
// phi resolution for KinFitter
double QCDBkgRS::JetResolution_Phi2(const double& e, const double& eta) {
   //may be artifically reduced (no angular fit)
   return (pow(0.05 / TMath::Sqrt(e), 2) + pow(0.005, 2)) / 1.e6;
}
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
// pt resolution for smearing
double QCDBkgRS::JetResolutionHist_Pt_Smear(const double& pt, const double& eta, const int& i) {
   int i_jet;
   i < 2 ? i_jet = i : i_jet = 2;
   int i_Pt = GetIndex(pt, &PtBinEdges_);
   int i_eta = GetIndex(eta, &EtaBinEdges_);

   double x_rand = rand_->Rndm();
   double hf_prob = GetHFProb(pt, eta, i_jet);

   double res = 1.0;
   if( x_rand <= hf_prob ){
      // get heavy flavor smear function
      res = smearFunc_->getSmearFunc(1, i_jet, i_eta, i_Pt)->GetRandom();
   }
   else {
      // get no heavy flavor smear function
      res = smearFunc_->getSmearFunc(0, i_jet, i_eta, i_Pt)->GetRandom();
   }

   return res;
}
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
// HF probability for smearing
double QCDBkgRS::GetHFProb(const double& pt, const double& eta, const int& i_jet) {
  
   int i_bin;
   if( i_jet == 0 ) {
      i_bin = h_bProb_jet1->FindBin(pt, eta);
      return h_bProb_jet1->GetBinContent(i_bin);
   }
   if( i_jet == 1 ) {
      i_bin = h_bProb_jet2->FindBin(pt, eta);
      return h_bProb_jet2->GetBinContent(i_bin);
   }
   else {
      i_bin = h_bProb_jet3p->FindBin(pt, eta);
      return h_bProb_jet3p->GetBinContent(i_bin);
   }
}
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
// rebalance the events using a kinematic fit and transverse momentum balance
bool QCDBkgRS::RebalanceJets_KinFitter(edm::View<pat::Jet>* Jets_rec, std::vector<pat::Jet> &Jets_reb) {

   bool result = true;

   //// Interface to KinFitter
   TKinFitter* myFit = new TKinFitter();

   std::vector<TLorentzVector*> lvec_m;

   std::vector<TMatrixD*> covMat_m;

   std::vector<TFitParticleEtEtaPhi*> fitted;
   std::vector<TFitParticleEtEtaPhi*> measured;
   std::map<int, const pat::Jet*> JetMap;
   double dPx = 0;
   double dPy = 0;
   double HTreco = 0;
   double HTreb = 0;
   double MHTx_low = 0;
   double MHTy_low = 0;
   double MHTx_high = 0;
   double MHTy_high = 0;

   //// Fill measured particles to vector
   int i = 0;
   for (edm::View<pat::Jet>::const_iterator it = Jets_rec-> begin(); it != Jets_rec->end(); ++it) {

      //if (it->pt() < rebalancedJetPt_ || abs(it->pt()) > 3.0) {
      //if (it->pt() < rebalancedJetPt_ || it->chargedEmEnergyFraction()>0.9 || it->muonEnergyFraction()>0.9) {
      if (it->pt() < rebalancedJetPt_) {
         if (rebalanceMode_ == "MHTall") {
            MHTx_low -= it->px();
            MHTy_low -= it->py();
            pat::Jet rebalancedJet(*((pat::Jet*) &(*it)));
            Jets_reb.push_back(rebalancedJet);
         }
      } else {
         MHTx_high -= it->px();
         MHTy_high -= it->py();
         JetMap[i] = &(*it);

         // The particles before fitting
         double tmppx, tmppy, tmppz, tmpe;
         tmppx = it->px();
         tmppy = it->py();
         tmppz = it->pz();
         tmpe = it->energy();

         TLorentzVector* lv = new TLorentzVector(tmppx, tmppy, tmppz, tmpe);
         lvec_m.push_back(lv);
         TMatrixD* cM = new TMatrixD(3, 3);
         (*cM)(0, 0) = JetResolution_Pt2(it->pt(), it->eta(), i);
         (*cM)(1, 1) = JetResolution_Eta2(it->energy(), it->eta());
         (*cM)(2, 2) = JetResolution_Phi2(it->energy(), it->eta());
         covMat_m.push_back(cM);
         char name[10];
         sprintf(name, "jet%i", i);
         TFitParticleEtEtaPhi* jet1 = new TFitParticleEtEtaPhi(name, name, lvec_m.back(), covMat_m.back());
         measured.push_back(jet1);
         TFitParticleEtEtaPhi* jet2 = new TFitParticleEtEtaPhi(name, name, lvec_m.back(), covMat_m.back());
         fitted.push_back(jet2);
         myFit->addMeasParticle(fitted.back());
         ++i;
      }
   }

   //// Add momentum constraints
   double MET_constraint_x = 0.;
   double MET_constraint_y = 0.;
   if (rebalanceMode_ == "MHTall") {
      //// rebalance MHT of all jets
      MET_constraint_x = MHTx_low;
      MET_constraint_y = MHTy_low;
   } else if (rebalanceMode_ == "MHThigh") {
      //// rebalance MHT of fitted jets
      MET_constraint_x = 0.;
      MET_constraint_y = 0.;
   } else {
      //// default: rebalance MHT of fitted jets
      MET_constraint_x = 0.;
      MET_constraint_y = 0.;
   }
   TFitConstraintEp* momentumConstr1 = new TFitConstraintEp("px", "px", 0, TFitConstraintEp::pX, MET_constraint_x);
   TFitConstraintEp* momentumConstr2 = new TFitConstraintEp("py", "py", 0, TFitConstraintEp::pY, MET_constraint_y);
   for (unsigned int i = 0; i < fitted.size(); ++i) {
      momentumConstr1->addParticle(fitted.at(i));
      momentumConstr2->addParticle(fitted.at(i));
   }
   myFit->addConstraint(momentumConstr1);
   myFit->addConstraint(momentumConstr2);

   //// Set fit parameters
   myFit->setVerbosity(0);
   myFit->setMaxNbIter(100);
   myFit->setMaxF(0.01 * 2);
   myFit->setMaxDeltaS(1.e-3);
   myFit->fit();
   //cout << "KinFitter: " << myFit->getStatus() << endl;
   int status = myFit->getStatus();

   double chi2 = 0;
   double F = 0;
   double prob = 0;
   //if (status == 0 || status == 1) {
   if (status == 0) {
      chi2 = myFit->getS();
      F = myFit->getF();
      int dof = myFit->getNDF();
      prob = TMath::Prob(chi2, dof);
      //if (prob < 1.e-8) result = false;
      //cout << "chi2, prop, F = " << chi2 << " " << prob << " " << F << endl;
   } else {
      chi2 = 99999;
      prob = 0;
      F = 99999;
      result = false;
      //cout << "chi2, prop, F = " << chi2 << " " << prob << " " << F << endl;
   }
   if (controlPlots_)
      h_fitProb->Fill(prob);

   //// Get the output of KinFitter
   for (unsigned int i = 0; i < measured.size(); ++i) {
      // create new rebalanced Jet
      pat::Jet::LorentzVector newP4(fitted.at(i)->getCurr4Vec()->Px(), fitted.at(i)->getCurr4Vec()->Py(),
            fitted.at(i)->getCurr4Vec()->Pz(), fitted.at(i)->getCurr4Vec()->E());
      pat::Jet rebalancedJet(*((pat::Jet*) JetMap[i]));
      HTreco += rebalancedJet.pt();
      //cout << "RECO: " << i << "th: pt = " << rebalancedJet.pt() << " phi = " << rebalancedJet.phi() << endl;
      rebalancedJet.setP4(newP4);
      //cout << "REB: " << i << "th: pt = " << rebalancedJet.pt() << " phi = " << rebalancedJet.phi() << endl;
      Jets_reb.push_back(rebalancedJet);
      dPx -= newP4.Px() - measured.at(i)->getCurr4Vec()->Px();
      dPy -= newP4.Py() - measured.at(i)->getCurr4Vec()->Py();
      HTreb += rebalancedJet.pt();
   }
   //cout << "HT reco = " << HTreco << endl;
   //cout << "HT reb  = " << HTreb << endl;

   delete myFit;
   for (unsigned int i = 0; i < measured.size(); ++i) {
      delete lvec_m.at(i);
      delete covMat_m.at(i);
      delete measured.at(i);
      delete fitted.at(i);
   }
   delete momentumConstr1;
   delete momentumConstr2;

   return result;
}
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
void QCDBkgRS::SmearingJets(const std::vector<pat::Jet> &Jets_reb, std::vector<pat::Jet> &Jets_smeared) {

   double dPx = 0;
   double dPy = 0;

   for (int i = 1; i <= Ntries_; ++i) {
      int Ntries2 = 1;
      double w = weight_;
      if (cleverPrescaleTreating_ == true && weight_ > 1) {
         Ntries2 = (int) weight_;
         w = weight_ / Ntries2;
      }
      for (int j = 1; j <= Ntries2; ++j) {
         Jets_smeared.clear();
         int i_jet = 0;
         for (std::vector<pat::Jet>::const_iterator it = Jets_reb.begin(); it != Jets_reb.end(); ++it) {
            if (it->pt() > smearedJetPt_) {
               double newPt = 0;
               newPt = it->pt() * JetResolutionHist_Pt_Smear(it->pt(), it->eta(), i_jet);
               //double newEta = rand_->Gaus(it->eta(), TMath::Sqrt(JetResolution_Eta2(it->energy(), it->eta())));
               //double newPhi = rand_->Gaus(it->phi(), TMath::Sqrt(JetResolution_Phi2(it->energy(), it->eta())));
               double newEta = it->eta();
               double newPhi = it->phi();
               pat::Jet::PolarLorentzVector newP4(newPt, newEta, newPhi, it->mass());
               pat::Jet smearedJet(*it);
               smearedJet.setP4(newP4);
               Jets_smeared.push_back(smearedJet);
               dPx -= newP4.Px() - it->px();
               dPy -= newP4.Py() - it->py();
               ++i_jet;
            } else {
               pat::Jet smearedJet(*it);
               Jets_smeared.push_back(smearedJet);
            }
         }
         GreaterByPt<reco::Candidate> ptComparator_;
         std::sort(Jets_smeared.begin(), Jets_smeared.end(), ptComparator_);
         //Fill HT and MHT prediction histos for i-th iteration of smearing
         FillPredictions(Jets_smeared, i, w);
      }
   }

   // fill prediction tree 
   PredictionTree->Fill();

   // clear vectors
   weight.clear();
   Ntries_pred.clear();
   Njets_pred.clear();
   HT_pred.clear();
   MHT_pred.clear();
   Jet1Pt_pred.clear();
   Jet2Pt_pred.clear();
   Jet3Pt_pred.clear();
   Jet1Eta_pred.clear();
   Jet2Eta_pred.clear();
   Jet3Eta_pred.clear();
   DeltaPhi1_pred.clear();
   DeltaPhi2_pred.clear();
   DeltaPhi3_pred.clear();

   return;
}
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
void QCDBkgRS::SmearingGenJets(edm::View<reco::GenJet>* Jets_gen, std::vector<reco::GenJet> &GenJets_smeared) {

   double dPx = 0;
   double dPy = 0;

   for (int i = 1; i <= Ntries_; ++i) {
      GenJets_smeared.clear();
      int i_jet = 0;

      for (edm::View<reco::GenJet>::const_iterator it = Jets_gen->begin(); it != Jets_gen->end(); ++it) {

         if (it->pt() > smearedJetPt_) {
            double newPt = 0;
            newPt = it->pt() * JetResolutionHist_Pt_Smear(it->pt(), it->eta(), i_jet);
            //double newEta = rand_->Gaus(it->eta(), TMath::Sqrt(JetResolution_Eta2(it->energy(), it->eta())));
            //double newPhi = rand_->Gaus(it->phi(), TMath::Sqrt(JetResolution_Phi2(it->energy(), it->eta())));
            double newEta = it->eta();
            double newPhi = it->phi();
            reco::GenJet::PolarLorentzVector newP4(newPt, newEta, newPhi, it->mass());
            reco::GenJet smearedJet(*it);
            smearedJet.setP4(newP4);
            GenJets_smeared.push_back(smearedJet);
            dPx -= newP4.Px() - it->px();
            dPy -= newP4.Py() - it->py();
            ++i_jet;
         } else {
            reco::GenJet smearedJet(*it);
            GenJets_smeared.push_back(smearedJet);
         }
      }
      GreaterByPt<reco::Candidate> ptComparator_;
      std::sort(GenJets_smeared.begin(), GenJets_smeared.end(), ptComparator_);
      //Fill HT and MHT prediction histos for i-th iteration of smearing
      FillPredictions_gen(GenJets_smeared, i, weight_);
   }

   // fill prediction tree 
   PredictionTree->Fill();

   // clear vectors
   weight.clear();
   Ntries_pred.clear();
   Njets_pred.clear();
   HT_pred.clear();
   MHT_pred.clear();
   Jet1Pt_pred.clear();
   Jet2Pt_pred.clear();
   Jet3Pt_pred.clear();
   Jet1Eta_pred.clear();
   Jet2Eta_pred.clear();
   Jet3Eta_pred.clear();
   DeltaPhi1_pred.clear();
   DeltaPhi2_pred.clear();
   DeltaPhi3_pred.clear();

   return;
}
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
int QCDBkgRS::calcNJets(const std::vector<pat::Jet>& Jets_smeared) {
   int NJets = 0;
   for (vector<pat::Jet>::const_iterator it = Jets_smeared.begin(); it != Jets_smeared.end(); ++it) {
      if (it->pt() > JetsHTPt_ && std::abs(it->eta()) < JetsHTEta_) {
         ++NJets;
      }
   }
   return NJets;
}
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
double QCDBkgRS::calcHT(const std::vector<pat::Jet>& Jets_smeared) {
   double HT = 0;
   for (vector<pat::Jet>::const_iterator it = Jets_smeared.begin(); it != Jets_smeared.end(); ++it) {
      if (it->pt() > JetsHTPt_ && std::abs(it->eta()) < JetsHTEta_) {
         HT += it->pt();
      }
   }
   return HT;
}
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
bool QCDBkgRS::calcMinDeltaPhi(const std::vector<pat::Jet>& Jets_smeared, math::PtEtaPhiMLorentzVector& MHT) {
   bool result = true;
   unsigned int i = 0;
   for (vector<pat::Jet>::const_iterator it = Jets_smeared.begin(); it != Jets_smeared.end(); ++it) {
      if (it->pt() > JetsMHTPt_ && std::abs(it->eta()) < JetsMHTEta_) {
         if (i < JetDeltaMin_.size()) {
            if (std::abs(deltaPhi(MHT, *it)) < JetDeltaMin_.at(i))
               result = false;
            ++i;
         } else {
            break;
         }
      }
   }
   return result;
}
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
math::PtEtaPhiMLorentzVector QCDBkgRS::calcMHT(const std::vector<pat::Jet>& Jets_smeared) {
   math::PtEtaPhiMLorentzVector MHT(0, 0, 0, 0);
   for (vector<pat::Jet>::const_iterator it = Jets_smeared.begin(); it != Jets_smeared.end(); ++it) {
      if (it->pt() > JetsMHTPt_ && std::abs(it->eta()) < JetsMHTEta_) {
         MHT -= it->p4();
      }
   }
   return MHT;
}
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
void QCDBkgRS::FillLeadingJetVectors(const std::vector<pat::Jet>& Jets_smeared) {
   int NJets = 0;
   for (vector<pat::Jet>::const_iterator it = Jets_smeared.begin(); it != Jets_smeared.end(); ++it) {
      if (it->pt() > JetsHTPt_ && std::abs(it->eta()) < JetsHTEta_) {
         ++NJets;
      
         if( NJets == 1 ) {
            Jet1Pt_pred.push_back(it->pt());
            Jet1Eta_pred.push_back(it->eta());    
         }
         if( NJets == 2 ) {
            Jet2Pt_pred.push_back(it->pt());
            Jet2Eta_pred.push_back(it->eta());    
         }
         if( NJets == 3 ) {
            Jet3Pt_pred.push_back(it->pt());
            Jet3Eta_pred.push_back(it->eta());
            break;    
         }
      }
   }
   if( NJets == 2 ) {
      Jet3Pt_pred.push_back(0.);
      Jet3Eta_pred.push_back(0.);
   }

   return;
}
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
void QCDBkgRS::FillDeltaPhiVectors(const std::vector<pat::Jet>& Jets_smeared, math::PtEtaPhiMLorentzVector& vMHT) {
   int NJets = 0;
   for (vector<pat::Jet>::const_iterator it = Jets_smeared.begin(); it != Jets_smeared.end(); ++it) {
      if (it->pt() > JetsMHTPt_ && std::abs(it->eta()) < JetsMHTEta_) {
         ++NJets;
      
         if( NJets == 1 ) {
            DeltaPhi1_pred.push_back(std::abs(deltaPhi(vMHT, *it)));
         }
         if( NJets == 2 ) {
            DeltaPhi2_pred.push_back(std::abs(deltaPhi(vMHT, *it)));
         }
         if( NJets == 3 ) {
            DeltaPhi3_pred.push_back(std::abs(deltaPhi(vMHT, *it)));
            break;
         }
      }
   }
   if( NJets == 2 ) {
      DeltaPhi3_pred.push_back(0.);
   }

   return;
}
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
int QCDBkgRS::calcNJets_gen(const std::vector<reco::GenJet>& Jets_smeared) {
   int NJets = 0;
   for (vector<reco::GenJet>::const_iterator it = Jets_smeared.begin(); it != Jets_smeared.end(); ++it) {
      if (it->pt() > JetsHTPt_ && std::abs(it->eta()) < JetsHTEta_) {
         ++NJets;
      }
   }
   return NJets;
}
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
double QCDBkgRS::calcHT_gen(const std::vector<reco::GenJet>& Jets_smeared) {
   double HT = 0;
   for (vector<reco::GenJet>::const_iterator it = Jets_smeared.begin(); it != Jets_smeared.end(); ++it) {
      if (it->pt() > JetsHTPt_ && std::abs(it->eta()) < JetsHTEta_) {
         HT += it->pt();
      }
   }
   return HT;
}
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
bool QCDBkgRS::calcMinDeltaPhi_gen(const std::vector<reco::GenJet>& Jets_smeared, math::PtEtaPhiMLorentzVector& MHT) {
   bool result = true;
   unsigned int i = 0;
   for (vector<reco::GenJet>::const_iterator it = Jets_smeared.begin(); it != Jets_smeared.end(); ++it) {
      if (it->pt() > JetsMHTPt_ && std::abs(it->eta()) < JetsMHTEta_) {
         if (i < JetDeltaMin_.size()) {
            if (std::abs(deltaPhi(MHT, *it)) < JetDeltaMin_.at(i))
               result = false;
            ++i;
         } else {
            break;
         }
      }
   }
   return result;
}
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
math::PtEtaPhiMLorentzVector QCDBkgRS::calcMHT_gen(const std::vector<reco::GenJet>& Jets_smeared) {
   math::PtEtaPhiMLorentzVector MHT(0, 0, 0, 0);
   for (vector<reco::GenJet>::const_iterator it = Jets_smeared.begin(); it != Jets_smeared.end(); ++it) {
      if (it->pt() > JetsMHTPt_ && std::abs(it->eta()) < JetsMHTEta_) {
         MHT -= it->p4();
      }
   }
   return MHT;
}
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
void QCDBkgRS::FillLeadingJetVectors_gen(const std::vector<reco::GenJet>& Jets_smeared) {
   int NJets = 0;
   for (vector<reco::GenJet>::const_iterator it = Jets_smeared.begin(); it != Jets_smeared.end(); ++it) {
      if (it->pt() > JetsHTPt_ && std::abs(it->eta()) < JetsHTEta_) {
         ++NJets;
      
         if( NJets == 1 ) {
            Jet1Pt_pred.push_back(it->pt());
            Jet1Eta_pred.push_back(it->eta());    
         }
         if( NJets == 2 ) {
            Jet2Pt_pred.push_back(it->pt());
            Jet2Eta_pred.push_back(it->eta());    
         }
         if( NJets == 3 ) {
            Jet3Pt_pred.push_back(it->pt());
            Jet3Eta_pred.push_back(it->eta());  
            break;  
         }
      }
   }
   if( NJets == 2 ) {
      Jet3Pt_pred.push_back(0.);
      Jet3Eta_pred.push_back(0.);
   }

   return;
}
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
void QCDBkgRS::FillDeltaPhiVectors_gen(const std::vector<reco::GenJet>& Jets_smeared, math::PtEtaPhiMLorentzVector& vMHT) {
   int NJets = 0;
   for (vector<reco::GenJet>::const_iterator it = Jets_smeared.begin(); it != Jets_smeared.end(); ++it) {
      if (it->pt() > JetsMHTPt_ && std::abs(it->eta()) < JetsMHTEta_) {
         ++NJets;
      
         if( NJets == 1 ) {
            DeltaPhi1_pred.push_back(std::abs(deltaPhi(vMHT, *it)));
         }
         if( NJets == 2 ) {
            DeltaPhi2_pred.push_back(std::abs(deltaPhi(vMHT, *it)));
         }
         if( NJets == 3 ) {
            DeltaPhi3_pred.push_back(std::abs(deltaPhi(vMHT, *it)));
            break;
         }
      }
   }
   if( NJets == 2 ) {
      DeltaPhi3_pred.push_back(0.);
   }


   return;
}
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
void QCDBkgRS::FillPredictions(const std::vector<pat::Jet>& Jets_smeared, const int& i, const double& w) {

   int NJets = calcNJets(Jets_smeared);
   double HT = calcHT(Jets_smeared);
   math::PtEtaPhiMLorentzVector vMHT = calcMHT(Jets_smeared);
   double MHT = vMHT.pt();
   //   bool minDeltaPhi = calcMinDeltaPhi(Jets_smeared, vMHT);
   double Meff = HT + MHT;

   if (NJets >= NJets_) {

      // -- fill prediction vectors -- //
      weight.push_back(w);
      Ntries_pred.push_back(i);
      Njets_pred.push_back(NJets);
      HT_pred.push_back(HT);
      MHT_pred.push_back(MHT);
      FillDeltaPhiVectors(Jets_smeared, vMHT);
      FillLeadingJetVectors(Jets_smeared); 
      // ----------------------------- //
   }

   return;
}
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
void QCDBkgRS::FillPredictions_gen(const std::vector<reco::GenJet>& Jets_smeared, const int& i,
      const double& w) {

   int NJets = calcNJets_gen(Jets_smeared);
   double HT = calcHT_gen(Jets_smeared);
   math::PtEtaPhiMLorentzVector vMHT = calcMHT_gen(Jets_smeared);
   double MHT = vMHT.pt();
   bool minDeltaPhi = calcMinDeltaPhi_gen(Jets_smeared, vMHT);
   double Meff = HT + MHT;

   if (NJets >= NJets_) { 

      // -- fill prediction vectors -- //
      weight.push_back(w);
      Ntries_pred.push_back(i);
      Njets_pred.push_back(NJets);
      HT_pred.push_back(HT);
      MHT_pred.push_back(MHT);
      FillDeltaPhiVectors_gen(Jets_smeared, vMHT);
      FillLeadingJetVectors_gen(Jets_smeared); 
      // ----------------------------- //
   }

   return;
}
//--------------------------------------------------------------------------

// ------------ method called for each event  ------------
void QCDBkgRS::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   //Weight
   edm::Handle<double> event_weight;
   iEvent.getByLabel(weightName_, event_weight);
   weight_ = (event_weight.isValid() ? (*event_weight) : 1.0);
   //if (!event_weight.isValid()) cout << "weight not found" << endl;

   if (controlPlots_) {
      h_weight->Fill(log10(weight_));
      h_weightedWeight->Fill(log10(weight_), weight_);
   }

   // Number of vertices
   edm::Handle<reco::VertexCollection> vertices;
   iEvent.getByLabel(vertices_,vertices);
   if( vertices.isValid() ) {
      vtxN = vertices->size();
   }  

   //GenJets
   edm::Handle<edm::View<reco::GenJet> > gj;
   edm::View<reco::GenJet> Jets_gen;
   bool gj_present = iEvent.getByLabel(genjets_, gj);
   if (gj_present) {
      Jets_gen = *gj;
   }

   //PATJets
   edm::Handle<edm::View<pat::Jet> > Jets;
   iEvent.getByLabel(jets_, Jets);
   edm::View<pat::Jet> Jets_rec = *Jets;

   // collection of rebalanced jets
   std::auto_ptr<vector<pat::Jet> > Jets_reb(new vector<pat::Jet> );

   // collection of smeared jets
   std::auto_ptr<vector<pat::Jet> > Jets_smeared(new vector<pat::Jet> );

   // collection of smeared gen jets
   std::auto_ptr<vector<reco::GenJet> > GenJets_smeared(new vector<reco::GenJet> );

   double HTall_rec = 0;
   double HTlow_rec = 0;
   double HThigh_rec = 0;
   HT_seed = 0;
   math::PtEtaPhiMLorentzVector vMHTall_rec(0., 0., 0., 0.);
   math::PtEtaPhiMLorentzVector vMHTlow_rec(0., 0., 0., 0.);
   math::PtEtaPhiMLorentzVector vMHThigh_rec(0., 0., 0., 0.);
   int NJets_reco = 0;
   //// Fill measured particles to vector
   for (edm::View<pat::Jet>::const_iterator it = Jets_rec.begin(); it != Jets_rec.end(); ++it) {
      if (it->pt() > JetsHTPt_ && std::abs(it->eta()) < JetsHTEta_) {
         HT_seed += it->pt();
         NJets_reco++;
      }

      if (it->pt() < JetsHTPt_) {
         HTall_rec += it->pt();
         HTlow_rec += it->pt();
      } else {
         HTall_rec += it->pt();
         HThigh_rec += it->pt();
      }

      if (it->pt() < JetsMHTPt_) {
         vMHTall_rec -= it->p4();
         vMHTlow_rec -= it->p4();
      } else {
         vMHTall_rec -= it->p4();
         vMHThigh_rec -= it->p4();
      }

      /*
        if (it->pt() < JetsHTPt_) {
        vMHTall_rec -= it->p4();
        vMHTlow_rec -= it->p4();
        HTall_rec += it->pt();
        HTlow_rec += it->pt();
        } else {
        vMHTall_rec -= it->p4();
        vMHThigh_rec -= it->p4();
        HTall_rec += it->pt();
        HThigh_rec += it->pt();
        }
      */

      h_JetPt_reco->Fill(it->pt(), weight_);
   }

   if (controlPlots_) {
      h_nJets_reco->Fill(NJets_reco, weight_);
      h_HTall_rec->Fill(HTall_rec, weight_);
      h_HThigh_rec->Fill(HThigh_rec, weight_);
      h_MHTall_rec->Fill(vMHTall_rec.pt(), weight_);
      h_MHThigh_rec->Fill(vMHThigh_rec.pt(), weight_);
   }

   double HTall_gen = 0;
   double HTlow_gen = 0;
   double HThigh_gen = 0;
   math::PtEtaPhiMLorentzVector vMHTall_gen(0., 0., 0., 0.);
   math::PtEtaPhiMLorentzVector vMHTlow_gen(0., 0., 0., 0.);
   math::PtEtaPhiMLorentzVector vMHThigh_gen(0., 0., 0., 0.);
   //// Fill measured particles to vector
   for (edm::View<reco::GenJet>::const_iterator it = Jets_gen.begin(); it != Jets_gen.end(); ++it) {
      if (it->pt() < JetsHTPt_) {
         HTall_gen += it->pt();
         HTlow_gen += it->pt();
      } else {
         HTall_gen += it->pt();
         HThigh_gen += it->pt();
      }

      if (it->pt() < JetsMHTPt_) {
         vMHTall_gen -= it->p4();
         vMHTlow_gen -= it->p4();
      } else {
         vMHTall_gen -= it->p4();
         vMHThigh_gen -= it->p4();
      }

      /*
        if (it->pt() < JetsHTPt_) {
        vMHTall_gen -= it->p4();
        vMHTlow_gen -= it->p4();
        HTall_gen += it->pt();
        HTlow_gen += it->pt();
        } else {
        vMHTall_gen -= it->p4();
        vMHThigh_gen -= it->p4();
        HTall_gen += it->pt();
        HThigh_gen += it->pt();
        }
      */

   }
   if (controlPlots_) {
      h_HTall_gen->Fill(HTall_gen, weight_);
      h_HThigh_gen->Fill(HThigh_gen, weight_);
      h_MHTall_gen->Fill(vMHTall_gen.pt(), weight_);
      h_MHThigh_gen->Fill(vMHThigh_gen.pt(), weight_);
   }
   //cout << "HT gen  = " << HThigh_gen << endl;

   //// Pt resolution of reconstructed CaloJets
   if (gj_present) {
      for (edm::View<reco::GenJet>::const_iterator it = Jets_gen.begin(); it != Jets_gen.end(); ++it) {
         double dRmin = 100;
         const reco::Jet* matchedJet = 0;
         for (edm::View<pat::Jet>::const_iterator jt = Jets_rec.begin(); jt != Jets_rec.end(); ++jt) {
            double dR = deltaR(*jt, *it);
            if (dR < dRmin) {
               dRmin = dR;
               matchedJet = &(*jt);
            }
         }
         if (controlPlots_) {
            if (dRmin < 0.15) {
               h_RecJetMatched_Pt->Fill(matchedJet->pt(), weight_);
               if (fabs(it->eta()) < 1.5)
                  h_RecJetRes_Pt->Fill(it->pt(), matchedJet->pt() / it->pt(), weight_);
               if (it->pt() > 100.)
                  h_RecJetRes_Eta->Fill(it->eta(), matchedJet->pt() / it->pt(), weight_);
            }
            else {
               h_RecJetNotMatched_Pt->Fill(matchedJet->pt(), weight_);
            }
         }
      }
   }

   Jets_reb->reserve(Jets_rec.size());
   Jets_smeared->reserve(Jets_rec.size());

   //
   // Rebalance multi jet system
   //
   if (smearCollection_ == "Reco") {
      bool isRebalanced = RebalanceJets_KinFitter(&Jets_rec, *(Jets_reb.get()));
      if (!isRebalanced) {
         cout << "Bad event: Not possible to rebalance!" << endl;
         weight_ = 0;
      }
      double HThigh_reb = 0;
      math::PtEtaPhiMLorentzVector vMHThigh_reb(0., 0., 0., 0.);
      double HTlow_reb = 0;
      math::PtEtaPhiMLorentzVector vMHTlow_reb(0., 0., 0., 0.);
      double HTall_reb = 0;
      math::PtEtaPhiMLorentzVector vMHTall_reb(0., 0., 0., 0.);
      int NJets_reb = 0;
      for (vector<pat::Jet>::const_iterator it = Jets_reb-> begin(); it != Jets_reb->end(); ++it) {
         if (it->pt() > JetsHTPt_ && std::abs(it->eta()) < JetsHTEta_) {
            NJets_reb++;
         }

         if (it->pt() < JetsHTPt_) {
            HTall_reb += it->pt();
            HTlow_reb += it->pt();
         } else {
            HTall_reb += it->pt();
            HThigh_reb += it->pt();
         }
         
         if (it->pt() < JetsMHTPt_) {
            vMHTall_reb -= it->p4();
            vMHTlow_reb -= it->p4();
         } else {
            vMHTall_reb -= it->p4();
            vMHThigh_reb -= it->p4();
         }

         /*
           if (it->pt() > JetsHTPt_) {
           vMHThigh_reb -= it->p4();
           HThigh_reb += it->pt();
           vMHTall_reb -= it->p4();
           HTall_reb += it->pt();
           } else {
           vMHTlow_reb -= it->p4();
           HTlow_reb += it->pt();
           vMHTall_reb -= it->p4();
           HTall_reb += it->pt();
           }
         */

         h_JetPt_reb->Fill(it->pt(), weight_);
      }
      if (!isRebalanced) {
         cout << "Bad event: Can't be rebalanced!!!" << endl;
         cout << "Reconstructed: HT, MHT = " << HThigh_rec << ", " << vMHThigh_rec.pt() << endl;
         cout << "Rebalanced: HT, MHT = " << HTall_reb << ", " << vMHTall_reb.pt() << endl;
      }
      if (controlPlots_) {
         h_nJets_reb->Fill(NJets_reb, weight_);
         h_HTall_reb->Fill(HTall_reb, weight_);
         h_HThigh_reb->Fill(HThigh_reb, weight_);
         //         if (abs(HThigh_reb - HThigh_rec) > 100) {
         //            cout << "WARNING!!!!!!!!!!!!!!!!!!!" << endl;
         //            cout << uncertaintyName_ << ": HTall reb = " << HTall_reb << " HThigh reb = " << HThigh_reb
         //                  << " HTall rec = " << HTall_rec << " HThigh rec = " << HThigh_rec << " weight = " << weight_ << endl;
         //         }
         h_MHTall_reb->Fill(vMHTall_reb.pt(), weight_);
         h_MHThigh_reb->Fill(vMHThigh_reb.pt(), weight_);
      }

      //// ----------- Control Plots rebalanced jets (sorted) and matched gen jets ------------------
      if(controlPlots_) {  
        
         // sort rebalanced jets
         GreaterByPt<pat::Jet> ptComparator_;
         std::sort(Jets_reb->begin(), Jets_reb->end(), ptComparator_);
         
         //// for MC only
         if (gj_present) {
            
            double HThigh_gen_matched = 0;
            math::PtEtaPhiMLorentzVector vMHThigh_gen_matched(0., 0., 0., 0.);
            double HTlow_gen_matched = 0;
            math::PtEtaPhiMLorentzVector vMHTlow_gen_matched(0., 0., 0., 0.);
            double HTall_gen_matched = 0;
            math::PtEtaPhiMLorentzVector vMHTall_gen_matched(0., 0., 0., 0.);
                     
            // keep leading gen jet
            const reco::GenJet* leadingGenJet = 0;
            
            // --- get gen jet properties with matched reb jets
            for (edm::View<reco::GenJet>::const_iterator it = Jets_gen.begin(); it != Jets_gen.end(); ++it) {
               double dRmin = 100;
               const pat::Jet* matchedJet = 0;
               for (vector<pat::Jet>::const_iterator jt = Jets_reb->begin(); jt != Jets_reb->end(); ++jt) {
                  double dR = deltaR(*jt, *it);
                  if (dR < dRmin) {
                     dRmin = dR;
                     matchedJet = &(*jt);
                  }
               }

               // plot delta R gen - reb               
               h_deltaR_gen_reb->Fill(dRmin, weight_);
                             
               if (dRmin < 0.15) {
                  // get Pt resolution of rebalanced CaloJets
                  if (fabs(it->eta()) < 1.5)
                     h_RebJetRes_Pt->Fill(it->pt(), matchedJet->pt() / it->pt(), weight_);
                  if (it->pt() > 100.)
                     h_RebJetRes_Eta->Fill(it->eta(), matchedJet->pt() / it->pt(), weight_);
                                    
                  // get MHT and HT of gen jets
                  if (it->pt() < JetsHTPt_) {
                     HTall_gen_matched += it->pt();
                     HTlow_gen_matched += it->pt();
                  } else {
                     HTall_gen_matched += it->pt();
                     HThigh_gen_matched += it->pt();
                  }
                  
                  if (it->pt() < JetsMHTPt_) {
                     vMHTall_gen_matched -= it->p4();
                     vMHTlow_gen_matched -= it->p4();
                  } else {
                     vMHTall_gen_matched -= it->p4();
                     vMHThigh_gen_matched -= it->p4();
                  }

                  /*
                    if (it->pt() > JetsHTPt_) {
                    vMHThigh_gen_matched -= it->p4();
                    HThigh_gen_matched += it->pt();
                    vMHTall_gen_matched -= it->p4();
                    HTall_gen_matched += it->pt();
                    } else {
                    vMHTlow_gen_matched -= it->p4();
                    HTlow_gen_matched += it->pt();
                    vMHTall_gen_matched -= it->p4();
                    HTall_gen_matched += it->pt();
                    }
                  */
                  
                  if ( it == Jets_gen.begin() ) {
                     leadingGenJet = &(*it);
                  }
               }        
            }
            
            // get leading jet properties
            if( leadingGenJet ) {
               double deltaPhiJet1MHTallGen = leadingGenJet->phi() - vMHTall_gen_matched.phi();
               double deltaEtaJet1MHTallGen = leadingGenJet->eta() - vMHTall_gen_matched.eta();
               double deltaRJet1MHTallGen = deltaR(*leadingGenJet, vMHTall_gen_matched);
               double deltaPhiJet1MHThighGen = leadingGenJet->phi() - vMHThigh_gen_matched.phi();
               double deltaEtaJet1MHThighGen = leadingGenJet->eta() - vMHThigh_gen_matched.eta();
               double deltaRJet1MHThighGen = deltaR(*leadingGenJet, vMHThigh_gen_matched);

               h_deltaPhiJet1MHTallGen->Fill(deltaPhiJet1MHTallGen, weight_); 
               h_deltaEtaJet1MHTallGen->Fill(deltaEtaJet1MHTallGen, weight_); 
               h_deltaRJet1MHTallGen->Fill(deltaRJet1MHTallGen, weight_); 
               h_deltaPhiJet1MHThighGen->Fill(deltaPhiJet1MHThighGen, weight_); 
               h_deltaEtaJet1MHThighGen->Fill(deltaEtaJet1MHThighGen, weight_); 
               h_deltaRJet1MHThighGen->Fill(deltaRJet1MHThighGen, weight_); 
            }
            
            // fill control hists for gen jets
            h_HTall_gen_matched->Fill(HTall_gen_matched, weight_);
            h_HThigh_gen_matched->Fill(HThigh_gen_matched, weight_);
            h_MHTall_gen_matched->Fill(vMHTall_gen_matched.pt(), weight_);
            h_MHThigh_gen_matched->Fill(vMHThigh_gen_matched.pt(), weight_);
                        
            // ----- //

            double HThigh_reb_matched = 0;
            math::PtEtaPhiMLorentzVector vMHThigh_reb_matched(0., 0., 0., 0.);
            double HTlow_reb_matched = 0;
            math::PtEtaPhiMLorentzVector vMHTlow_reb_matched(0., 0., 0., 0.);
            double HTall_reb_matched = 0;
            math::PtEtaPhiMLorentzVector vMHTall_reb_matched(0., 0., 0., 0.);

            // keep leading reb jet
            const pat::Jet* leadingRebJet = 0; 

            // --- get reb jet properties with matched gen jets
            for (vector<pat::Jet>::const_iterator it = Jets_reb->begin(); it != Jets_reb->end(); ++it) {      
               double dRmin = 100;
               for (edm::View<reco::GenJet>::const_iterator jt = Jets_gen.begin(); jt != Jets_gen.end(); ++jt) {
                  double dR = deltaR(*jt, *it);
                  if (dR < dRmin) {
                     dRmin = dR;
                  }
               }
               
               // plot delta R reb - gen
               h_deltaR_reb_gen->Fill(dRmin, weight_);
                              
               if (dRmin < 0.15) {
                  // MHT and HT of reb jets
                  if (it->pt() < JetsHTPt_) {
                     HTall_reb_matched += it->pt();
                     HTlow_reb_matched += it->pt();
                  } else {
                     HTall_reb_matched += it->pt();
                     HThigh_reb_matched += it->pt();
                  }
                  
                  if (it->pt() < JetsMHTPt_) {
                     vMHTall_reb_matched -= it->p4();
                     vMHTlow_reb_matched -= it->p4();
                  } else {
                     vMHTall_reb_matched -= it->p4();
                     vMHThigh_reb_matched -= it->p4();
                  }

                  /*
                    if (it->pt() > JetsHTPt_) {
                    vMHThigh_reb_matched -= it->p4();
                    HThigh_reb_matched += it->pt();
                    vMHTall_reb_matched -= it->p4();
                    HTall_reb_matched += it->pt();
                    } else {
                    vMHTlow_reb_matched -= it->p4();
                    HTlow_reb_matched += it->pt();
                    vMHTall_reb_matched -= it->p4();
                    HTall_reb_matched += it->pt();
                    }
                  */
                  
                  if ( it == Jets_reb->begin() ) {
                     leadingRebJet = &(*it);
                  }  
               }        
            }            
            
            // get leading jet properties
            if( leadingRebJet ) {
               double deltaPhiJet1MHTallReb = leadingRebJet->phi() - vMHTall_reb_matched.phi();
               double deltaEtaJet1MHTallReb = leadingRebJet->eta() - vMHTall_reb_matched.eta();
               double deltaRJet1MHTallReb = deltaR(*leadingRebJet, vMHTall_reb_matched);
               double deltaPhiJet1MHThighReb = leadingRebJet->phi() - vMHThigh_reb_matched.phi();
               double deltaEtaJet1MHThighReb = leadingRebJet->eta() - vMHThigh_reb_matched.eta();
               double deltaRJet1MHThighReb = deltaR(*leadingRebJet, vMHThigh_reb_matched);

               h_deltaPhiJet1MHTallReb->Fill(deltaPhiJet1MHTallReb, weight_); 
               h_deltaEtaJet1MHTallReb->Fill(deltaEtaJet1MHTallReb, weight_); 
               h_deltaRJet1MHTallReb->Fill(deltaRJet1MHTallReb, weight_); 
               h_deltaPhiJet1MHThighReb->Fill(deltaPhiJet1MHThighReb, weight_); 
               h_deltaEtaJet1MHThighReb->Fill(deltaEtaJet1MHThighReb, weight_); 
               h_deltaRJet1MHThighReb->Fill(deltaRJet1MHThighReb, weight_); 
            }
            
            // fill control hists for reb jets
            h_HTall_reb_matched->Fill(HTall_reb_matched, weight_);
            h_HThigh_reb_matched->Fill(HThigh_reb_matched, weight_);
            h_MHTall_reb_matched->Fill(vMHTall_reb_matched.pt(), weight_);
            h_MHThigh_reb_matched->Fill(vMHThigh_reb_matched.pt(), weight_);           
         }
      }
   }
   
   //
   // Smear rebalanced multi jet system
   //
   if (smearCollection_ == "Reco") {
      SmearingJets(*(Jets_reb.get()), *(Jets_smeared.get()));
   } else if (smearCollection_ == "Gen") {
      SmearingGenJets(&Jets_gen, *(GenJets_smeared.get()));
   }

   double HThigh_smeared = 0;
   math::PtEtaPhiMLorentzVector vMHThigh_smeared(0., 0., 0., 0.);
   int NJets_smear = 0;
   if (smearCollection_ == "Reco") {
      for (vector<pat::Jet>::const_iterator it = Jets_smeared-> begin(); it != Jets_smeared->end(); ++it) {
         if (it->pt() > JetsHTPt_ && std::abs(it->eta()) < JetsHTEta_) {
            NJets_smear++;
         }
         vMHThigh_smeared -= it->p4();
         HThigh_smeared += it->pt();
         h_JetPt_smear->Fill(it->pt(), weight_);
      }
   } else if (smearCollection_ == "Gen") {
      for (vector<reco::GenJet>::const_iterator it = GenJets_smeared-> begin(); it != GenJets_smeared->end(); ++it) {
         vMHThigh_smeared -= it->p4();
         HThigh_smeared += it->pt();
      }
   }
   if (controlPlots_) {
      h_nJets_smear->Fill(NJets_smear, weight_);
      h_HTall_smeared->Fill(HTlow_rec + HThigh_smeared, weight_);
      h_HThigh_smeared->Fill(HThigh_smeared, weight_);
      h_MHTall_smeared->Fill((vMHTlow_rec + vMHThigh_smeared).pt(), weight_);
      h_MHThigh_smeared->Fill(vMHThigh_smeared.pt(), weight_);
   }

   //// Pt resolution of smeared Jets
   if (smearCollection_ == "Gen") {
      if (gj_present) {
         for (edm::View<reco::GenJet>::const_iterator it = Jets_gen.begin(); it != Jets_gen.end(); ++it) {
            double dRmin = 100;
            const reco::GenJet* matchedJet = 0;
            for (vector<reco::GenJet>::const_iterator jt = GenJets_smeared-> begin(); jt != GenJets_smeared->end(); ++jt) {
               double dR = deltaR(*jt, *it);
               if (dR < dRmin) {
                  dRmin = dR;
                  matchedJet = &(*jt);
               }
            }
            if (controlPlots_) {
               if (dRmin < 0.15) {
                  if (fabs(it->eta()) < 1.5)
                     h_SmearedJetRes_Pt->Fill(it->pt(), matchedJet->pt() / it->pt(), weight_);
                  if (it->pt() > 100.)
                     h_SmearedJetRes_Eta->Fill(it->eta(), matchedJet->pt() / it->pt(), weight_);
               }
            }
         }
      }
   } else if (smearCollection_ == "Reco") {
      if (gj_present) {
         for (edm::View<reco::GenJet>::const_iterator it = Jets_gen.begin(); it != Jets_gen.end(); ++it) {
            double dRmin = 100;
            const pat::Jet* matchedJet = 0;
            for (vector<pat::Jet>::const_iterator jt = Jets_smeared-> begin(); jt != Jets_smeared->end(); ++jt) {
               double dR = deltaR(*jt, *it);
               if (dR < dRmin) {
                  dRmin = dR;
                  matchedJet = &(*jt);
               }
            }
            if (controlPlots_) {
               if (dRmin < 0.15) {
                  if (fabs(it->eta()) < 1.5)
                     h_SmearedJetRes_Pt->Fill(it->pt(), matchedJet->pt() / it->pt(), weight_);
                  if (it->pt() > 100.)
                     h_SmearedJetRes_Eta->Fill(it->eta(), matchedJet->pt() / it->pt(), weight_);
               }
            }
         }
      }
   }
}
//--------------------------------------------------------------------------


// ------------ method called once each job just before starting event loop  ------------
void QCDBkgRS::beginJob()
{
 edm::Service<TFileService> fs;
   if (!fs) {
      throw edm::Exception(edm::errors::Configuration, "TFile Service is not registered in cfg file");
   }
   fs->file().SetCompressionLevel(9);

   if (controlPlots_) {
      h_nJets_reco = fs->make<TH1F> ("NJets_reco", "NJets", 15, 0., 15);
      h_nJets_reco->Sumw2();
      h_nJets_reb = fs->make<TH1F> ("NJets_reb", "NJets", 15, 0., 15);
      h_nJets_reb->Sumw2();
      h_nJets_smear = fs->make<TH1F> ("NJets_smear", "NJets", 15, 0., 15);
      h_nJets_smear->Sumw2();

      h_JetPt_reco = fs->make<TH1F> ("JetPt_reco", "Jet pt", 1000, 0., 1000.);
      h_JetPt_reco->Sumw2();
      h_JetPt_reb = fs->make<TH1F> ("JetPt_reb", "Jet pt", 1000, 0., 1000.);
      h_JetPt_reb->Sumw2();
      h_JetPt_smear = fs->make<TH1F> ("JetPt_smear", "Jet pt", 1000, 0., 1000.);
      h_JetPt_smear->Sumw2();

      h_RecJetMatched_Pt = fs->make<TH1F> ("RecJetMatched_Pt", "RecJetMatched_Pt", 500, 0., 1000.);
      h_RecJetMatched_Pt->Sumw2();
      h_RecJetNotMatched_Pt = fs->make<TH1F> ("RecJetNotMatched_Pt", "RecJetNotMatched_Pt", 500, 0., 1000.);
      h_RecJetNotMatched_Pt->Sumw2();
      h_RecJetRes_Pt = fs->make<TH2F> ("RecJetRes_Pt", "RecJetRes_Pt", 100, 0., 1000., 100, 0., 3.);
      h_RecJetRes_Pt->Sumw2();
      h_RecJetRes_Eta = fs->make<TH2F> ("RecJetRes_Eta", "RecJetRes_Eta", 100, -5., 5., 100, 0., 3.);
      h_RecJetRes_Eta->Sumw2();
      h_RebJetRes_Pt = fs->make<TH2F> ("RebJetRes_Pt", "RebJetRes_Pt", 100, 0., 1000., 100, 0., 3.);
      h_RebJetRes_Pt->Sumw2();
      h_RebJetRes_Eta = fs->make<TH2F> ("RebJetRes_Eta", "RebJetRes_Eta", 100, -5., 5., 100, 0., 3.);
      h_RebJetRes_Eta->Sumw2();
      h_SmearedJetRes_Pt = fs->make<TH2F> ("SmearedJetRes_Pt", "SmearedJetRes_Pt", 100, 0., 1000., 100, 0., 3.);
      h_SmearedJetRes_Pt->Sumw2();
      h_SmearedJetRes_Eta = fs->make<TH2F> ("SmearedJetRes_Eta", "SmearedJetRes_Eta", 100, -5., 5., 100, 0., 3.);
      h_SmearedJetRes_Eta->Sumw2();
      h_HTall_gen = fs->make<TH1F> ("HTall_gen", "HTall_gen", NbinsHT_, HTmin_, HTmax_);
      h_HTall_gen->Sumw2();
      h_HTall_rec = fs->make<TH1F> ("HTall_rec", "HTall_rec", NbinsHT_, HTmin_, HTmax_);
      h_HTall_rec->Sumw2();
      h_HTall_smeared = fs->make<TH1F> ("HTall_smeared", "HTall_smeared", NbinsHT_, HTmin_, HTmax_);
      h_HTall_smeared->Sumw2();
      h_HTall_reb = fs->make<TH1F> ("HTall_reb", "HTall_reb", NbinsHT_, HTmin_, HTmax_);
      h_HTall_reb->Sumw2();
      h_HThigh_gen = fs->make<TH1F> ("HThigh_gen", "HThigh_gen", NbinsHT_, HTmin_, HTmax_);
      h_HThigh_gen->Sumw2();
      h_HThigh_rec = fs->make<TH1F> ("HThigh_rec", "HThigh_rec", NbinsHT_, HTmin_, HTmax_);
      h_HThigh_rec->Sumw2();
      h_HThigh_smeared = fs->make<TH1F> ("HThigh_smeared", "HThigh_smeared", NbinsHT_, HTmin_, HTmax_);
      h_HThigh_smeared->Sumw2();
      h_HThigh_reb = fs->make<TH1F> ("HThigh_reb", "HThigh_reb", NbinsHT_, HTmin_, HTmax_);
      h_HThigh_reb->Sumw2();
      h_MHTall_gen = fs->make<TH1F> ("MHTall_gen", "MHTall_gen", NbinsMHT_, MHTmin_, MHTmax_);
      h_MHTall_gen->Sumw2();
      h_MHTall_rec = fs->make<TH1F> ("MHTall_rec", "MHTall_rec", NbinsMHT_, MHTmin_, MHTmax_);
      h_MHTall_rec->Sumw2();
      h_MHTall_smeared = fs->make<TH1F> ("MHTall_smeared", "MHTall_smeared", NbinsMHT_, MHTmin_, MHTmax_);
      h_MHTall_smeared->Sumw2();
      h_MHTall_reb = fs->make<TH1F> ("MHTall_reb", "MHTall_reb", NbinsMHT_, MHTmin_, MHTmax_);
      h_MHTall_reb->Sumw2();
      h_MHThigh_gen = fs->make<TH1F> ("MHThigh_gen", "MHThigh_gen", NbinsMHT_, MHTmin_, MHTmax_);
      h_MHThigh_gen->Sumw2();
      h_MHThigh_rec = fs->make<TH1F> ("MHThigh_rec", "MHThigh_rec", NbinsMHT_, MHTmin_, MHTmax_);
      h_MHThigh_rec->Sumw2();
      h_MHThigh_smeared = fs->make<TH1F> ("MHThigh_smeared", "MHThigh_smeared", NbinsMHT_, MHTmin_, MHTmax_);
      h_MHThigh_smeared->Sumw2();
      h_MHThigh_reb = fs->make<TH1F> ("MHThigh_reb", "MHThigh_reb", NbinsMHT_, MHTmin_, MHTmax_);
      h_MHThigh_reb->Sumw2();
      h_fitProb = fs->make<TH1F> ("h_fitProb", "h_fitProb", 100, 0., 1.);
      h_fitProb->Sumw2();
      h_weight = fs->make<TH1F> ("h_weight", "h_weight", 70, -1., 6.);
      h_weight->Sumw2();
      h_weightedWeight = fs->make<TH1F> ("h_weightedWeight", "h_weightedWeight", 70, -1., 6.);
      h_weightedWeight->Sumw2();

      //// compare reb - gen jets
      h_deltaR_reb_gen = fs->make<TH1F> ("deltaR_reb_gen", "deltaR_reb_gen", 100, 0., 1.);
      h_deltaR_reb_gen->Sumw2();
      h_deltaR_gen_reb = fs->make<TH1F> ("deltaR_gen_reb", "deltaR_gen_reb", 100, 0., 1.);
      h_deltaR_gen_reb->Sumw2();
      h_HTall_gen_matched = fs->make<TH1F> ("HTall_gen_matched", "HTall_gen_matched", NbinsHT_, HTmin_, HTmax_);
      h_HTall_gen_matched->Sumw2();
      h_HThigh_gen_matched = fs->make<TH1F> ("HThigh_gen_matched", "HThigh_gen_matched", NbinsHT_, HTmin_, HTmax_);
      h_HThigh_gen_matched->Sumw2();
      h_MHTall_gen_matched = fs->make<TH1F> ("MHTall_gen_matched", "MHTall_gen_matched", NbinsMHT_, MHTmin_, MHTmax_);
      h_MHTall_gen_matched->Sumw2();
      h_MHThigh_gen_matched = fs->make<TH1F> ("MHThigh_gen_matched", "MHThigh_gen_matched", NbinsMHT_, MHTmin_, MHTmax_);
      h_MHThigh_gen_matched->Sumw2();
      h_HTall_reb_matched = fs->make<TH1F> ("HTall_reb_matched", "HTall_reb_matched", NbinsHT_, HTmin_, HTmax_);
      h_HTall_reb_matched->Sumw2();
      h_HThigh_reb_matched = fs->make<TH1F> ("HThigh_reb_matched", "HThigh_reb_matched", NbinsHT_, HTmin_, HTmax_);
      h_HThigh_reb_matched->Sumw2();
      h_MHTall_reb_matched = fs->make<TH1F> ("MHTall_reb_matched", "MHTall_reb_matched", NbinsMHT_, MHTmin_, MHTmax_);
      h_MHTall_reb_matched->Sumw2();
      h_MHThigh_reb_matched = fs->make<TH1F> ("MHThigh_reb_matched", "MHThigh_reb_matched", NbinsMHT_, MHTmin_, MHTmax_);
      h_MHThigh_reb_matched->Sumw2();
      h_deltaPhiJet1MHTallGen = fs->make<TH1F>("deltaPhiJet1MHTallGen", "deltaPhiJet1MHTallGen", 50, -TMath::Pi(), TMath::Pi() );
      h_deltaPhiJet1MHTallGen->Sumw2();
      h_deltaEtaJet1MHTallGen = fs->make<TH1F>("deltaEtaJet1MHTallGen", "deltaEtaJet1MHTallGen", 50, -5, 5 );
      h_deltaEtaJet1MHTallGen->Sumw2();
      h_deltaRJet1MHTallGen = fs->make<TH1F>("deltaRJet1MHTallGen", "deltaRJet1MHTallGen", 50, 0, 5 ); 
      h_deltaRJet1MHTallGen->Sumw2();
      h_deltaPhiJet1MHThighGen = fs->make<TH1F>("deltaPhiJet1MHThighGen", "deltaPhiJet1MHThighGen", 50, -TMath::Pi(), TMath::Pi() ); 
      h_deltaPhiJet1MHThighGen->Sumw2();
      h_deltaEtaJet1MHThighGen = fs->make<TH1F>("deltaEtaJet1MHThighGen", "deltaEtaJet1MHThighGen", 50, -5, 5 );
      h_deltaEtaJet1MHThighGen->Sumw2();
      h_deltaRJet1MHThighGen = fs->make<TH1F>("deltaRJet1MHThighGen", "deltaRJet1MHThighGen", 50, 0, 5 );  
      h_deltaRJet1MHThighGen->Sumw2();
      h_deltaPhiJet1MHTallReb = fs->make<TH1F>("deltaPhiJet1MHTallReb", "deltaPhiJet1MHTallReb", 50, -TMath::Pi(), TMath::Pi() );
      h_deltaPhiJet1MHTallReb->Sumw2();
      h_deltaEtaJet1MHTallReb = fs->make<TH1F>("deltaEtaJet1MHTallReb", "deltaEtaJet1MHTallReb", 50, -5, 5 );
      h_deltaEtaJet1MHTallReb->Sumw2();
      h_deltaRJet1MHTallReb = fs->make<TH1F>("deltaRJet1MHTallReb", "deltaRJet1MHTallReb", 50, 0, 5 ); 
      h_deltaRJet1MHTallReb->Sumw2();
      h_deltaPhiJet1MHThighReb = fs->make<TH1F>("deltaPhiJet1MHThighReb", "deltaPhiJet1MHThighReb", 50, -TMath::Pi(), TMath::Pi() ); 
      h_deltaPhiJet1MHThighReb->Sumw2();
      h_deltaEtaJet1MHThighReb = fs->make<TH1F>("deltaEtaJet1MHThighReb", "deltaEtaJet1MHThighReb", 50, -5, 5 );
      h_deltaEtaJet1MHThighReb->Sumw2();
      h_deltaRJet1MHThighReb = fs->make<TH1F>("deltaRJet1MHThighReb", "deltaRJet1MHThighReb", 50, 0, 5 );  
      h_deltaRJet1MHThighReb->Sumw2();
   }

   //// load b-jet probability histos
   TFile *f_bProb = new TFile(bprobabilityfile_.c_str(), "READ", "", 0);
   h_bProb_jet1 = (TH2F*) f_bProb->FindObjectAny("Data_truth_Prob_Jet1;1");
   h_bProb_jet2 = (TH2F*) f_bProb->FindObjectAny("Data_truth_Prob_Jet2;1");
   h_bProb_jet3p = (TH2F*) f_bProb->FindObjectAny("Data_truth_Prob_Jet3p;1");

   // define output tree 
   PredictionTree = fs->make<TTree> ("QCDPrediction", "QCDPrediction", 0);
   PredictionTree->SetAutoSave(10000000000);
   PredictionTree->SetAutoFlush(1000000);
    
   // set branches for output tree
   PredictionTree->Branch("NVtx", &vtxN); 
   PredictionTree->Branch("Ntries",&Ntries_pred);
   PredictionTree->Branch("NJets",&Njets_pred);
   PredictionTree->Branch("Weight",&weight);
   PredictionTree->Branch("HT_seed", &HT_seed);
   PredictionTree->Branch("HT", &HT_pred);
   PredictionTree->Branch("MHT", &MHT_pred); 
   PredictionTree->Branch("Jet1Pt", &Jet1Pt_pred); 
   PredictionTree->Branch("Jet2Pt", &Jet2Pt_pred); 
   PredictionTree->Branch("Jet3Pt", &Jet3Pt_pred); 
   PredictionTree->Branch("Jet1Eta", &Jet1Eta_pred); 
   PredictionTree->Branch("Jet2Eta", &Jet2Eta_pred); 
   PredictionTree->Branch("Jet3Eta", &Jet3Eta_pred); 
   PredictionTree->Branch("DeltaPhi1", &DeltaPhi1_pred); 
   PredictionTree->Branch("DeltaPhi2", &DeltaPhi2_pred); 
   PredictionTree->Branch("DeltaPhi3", &DeltaPhi3_pred); 
}
//--------------------------------------------------------------------------



// ------------ method called once each job just after ending the event loop  ------------
void QCDBkgRS::endJob() 
{
}

//define this as a plug-in
DEFINE_FWK_MODULE(QCDBkgRS);
