// -*- C++ -*-
//
// Package:    Trigger
// Class:      Trigger
// 
/**\class Trigger Trigger.cc PhysicsTools/Trigger/src/Trigger.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Kristin Heine,,,DESY
//         Created:  Wed Apr 18 15:00:58 CEST 2012
// $Id: Trigger.cc,v 1.1 2012/08/15 11:45:25 kheine Exp $
//
//

// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Utilities/interface/EDMException.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Photon.h"

#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

#include "PhysicsTools/SelectorUtils/interface/PFJetIDSelectionFunctor.h"
#include "DataFormats/BTauReco/interface/JetTag.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"
#include "FWCore/Common/interface/TriggerResultsByName.h"
#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "DataFormats/HLTReco/interface/TriggerObject.h"

#include "TH1F.h"
#include "TH2F.h"
#include "TFile.h"

//
// class declaration
//

using namespace edm;
using namespace std;
using namespace reco;
using namespace trigger;

class Trigger : public edm::EDAnalyzer {
   public:
      explicit Trigger(const edm::ParameterSet&);
      ~Trigger();
      bool goodElectron(const pat::Electron* ele);
      bool goodMuon(const pat::Muon* mu);
      bool goodJet_MHT(const pat::Jet* jet);
      bool goodJet_HT(const pat::Jet* jet);

   private:
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      // ----------member data ---------------------------
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

edm::InputTag jets_;
edm::InputTag met_;
edm::InputTag electrons_;
edm::InputTag muons_;
edm::InputTag photons_;
edm::InputTag vertex_;
edm::InputTag triggerTag_;

double elec_pt_cut_;
double elec_eta_cut_;

double muon_pt_cut_;
double muon_eta_cut_;

double jet_pt_cut_MHT_;
double jet_eta_cut_MHT_;
double jet_pt_cut_HT_;
double jet_eta_cut_HT_;
bool jet_useJetID_;

math::XYZPoint bs;

TH1F* h_met;
TH1F* h_jetpt_MHT;
TH1F* h_jetphi_MHT;
TH1F* h_jeteta_MHT;
TH1F* h_jetpt_HT;
TH1F* h_jetphi_HT;
TH1F* h_jeteta_HT;

TH1F* h_HTallprobes;
TH1F* h_HTpassedprobes;
TH1F* h_HTturnon;
TH1F* h_HTallprobes_total;
TH1F* h_HTpassedprobes_total;
TH1F* h_HTallprobes_intEff;
TH1F* h_HTpassedprobes_intEff;
TH1F* h_MHTallprobes;
TH1F* h_MHTpassedprobes;
TH1F* h_MHTturnon;
TH1F* h_METallprobes;
TH1F* h_MHTallprobes_total;
TH1F* h_MHTpassedprobes_total;
TH1F* h_MHTallprobes_intEff;
TH1F* h_MHTpassedprobes_intEff;
TH1F* h_METpassedprobes;

TH2F* h_Corr_JetPt_MuonPT;
TH2F* h_Corr_JetPt_ElectronPT;
TH2F* h_Corr_OnlineHT_OfflineHT;
TH2F* h_Corr_OnlineMHT_OfflineMHT;
TH2F* h_Corr_OnlineMHT_OfflineMET;

//
// constructors and destructor
//
Trigger::Trigger(const edm::ParameterSet& pset)
{
   //now do what ever initialization is needed
   jets_ = pset.getParameter < edm::InputTag > ("jetCollection");
   met_ = pset.getParameter < edm::InputTag > ("metCollection");
   electrons_ = pset.getParameter < edm::InputTag > ("electronCollection");
   muons_ = pset.getParameter < edm::InputTag > ("muonCollection");
   photons_ = pset.getParameter < edm::InputTag > ("photonCollection");
   vertex_ = pset.getParameter < edm::InputTag > ("vertexCollection");
   triggerTag_ = pset.getParameter < edm::InputTag > ("TriggerTag");

   muon_pt_cut_ = pset.getParameter<double>("muon_pt_cut");
   muon_eta_cut_ = pset.getParameter<double>("muon_eta_cut");

   elec_pt_cut_ = pset.getParameter<double>("elec_pt_cut");
   elec_eta_cut_ = pset.getParameter<double>("elec_eta_cut");

   jet_pt_cut_MHT_ = pset.getParameter<double>("jet_pt_cut_MHT");
   jet_eta_cut_MHT_ = pset.getParameter<double>("jet_eta_cut_MHT");
   jet_pt_cut_HT_ = pset.getParameter<double>("jet_pt_cut_HT");
   jet_eta_cut_HT_ = pset.getParameter<double>("jet_eta_cut_HT");
   jet_useJetID_ = pset.getParameter<bool>("jet_useJetID");

}


Trigger::~Trigger()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
Trigger::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   //// Load all the PAT collections

   //Jets
   Handle < edm::View<pat::Jet> > Jets;
   bool isFound = iEvent.getByLabel(jets_, Jets);
   if (!isFound)
      return;
   edm::View < pat::Jet > Jets_rec = *Jets;

   //MET
   Handle < edm::View<pat::MET> > Met;
   isFound = iEvent.getByLabel(met_, Met);
   if (!isFound)
      return;
   edm::View < pat::MET > Met_rec = *Met;

   //Electrons
   Handle < edm::View<pat::Electron> > Electrons;
   isFound = iEvent.getByLabel(electrons_, Electrons);
   if (!isFound)
      return;
   edm::View < pat::Electron > Electrons_rec = *Electrons;

   //Muons
   Handle < edm::View<pat::Muon> > Muons;
   isFound = iEvent.getByLabel(muons_, Muons);
   if (!isFound)
      return;
   edm::View < pat::Muon > Muons_rec = *Muons;

   //Photons
   Handle < edm::View<pat::Photon> > Photons;
   isFound = iEvent.getByLabel(photons_, Photons);
   if (!isFound)
      return;
   edm::View < pat::Photon > Photons_rec = *Photons;

   //Vertex
   edm::Handle < reco::VertexCollection > vertices;
   isFound = iEvent.getByLabel(vertex_, vertices);
   if (!isFound)
      return;

   for (reco::VertexCollection::const_iterator vertex = vertices->begin(); vertex != vertices->end(); ++vertex) {
      bs = vertex->position();
      break;
   }

   // trigger info
   edm::Handle < edm::TriggerResults > hltresults;
   iEvent.getByLabel(triggerTag_, hltresults);

   // ----------------------------------------------------------------------------- //
   // fill MET histo 
   // ----------------------------------------------------------------------------- //
   for (edm::View<pat::MET>::const_iterator it = Met_rec.begin(); it != Met_rec.end(); ++it) {
      h_met->Fill(it->pt());
      break;
   }

   // select appropriate run range for trigger under study
   if( iEvent.id().run() < 198022 ) { // <  198022 for PFHT, >= 198022 for PFNoPUHT

      // ----------------------------------------------------------------------------- //
      // check trigger results
      // ----------------------------------------------------------------------------- //
      // tag for HT
      const edm::TriggerNames & triggerNames_ = iEvent.triggerNames(*hltresults);
      bool triggered_tag_HT = false;
      for (unsigned int itrig = 0; itrig != hltresults->size(); ++itrig) {
         std::string trigName = triggerNames_.triggerName(itrig);
         //  std::cout<<" trigger name = " << trigName << std::endl;
         bool thistrig = false;
         if (trigName.find("HLT_Ele27_WP80_v") != std::string::npos)
            thistrig = hltresults->accept(itrig);
         if (thistrig)
            triggered_tag_HT = true;
      }

      // probe for HT
      bool triggered_probe_HT = false;
      for (unsigned int itrig = 0; itrig != hltresults->size(); ++itrig) {
         std::string trigName = triggerNames_.triggerName(itrig);
         //  std::cout<<" trigger name = " << trigName << std::endl;
         bool thistrig = false;
         // if (trigName.find("HLT_PFNoPUHT350_PFMET100_v") != std::string::npos)
         if (trigName.find("HLT_PFHT350_PFMET100_v") != std::string::npos)
            thistrig = hltresults->accept(itrig);
         if (thistrig) 
            triggered_probe_HT = true;
      }

      // tag for MHT
      bool triggered_tag_MHT = false;
      for (unsigned int itrig = 0; itrig != hltresults->size(); ++itrig) {
         std::string trigName = triggerNames_.triggerName(itrig);
         //  std::cout<<" trigger name = " << trigName << std::endl;
         bool thistrig = false;
         if (trigName.find("HLT_Ele27_WP80_v") != std::string::npos)
            thistrig = hltresults->accept(itrig);
         if (thistrig) 
            triggered_tag_MHT = true;
      }

      // probe for MHT
      bool triggered_probe_MHT = false;
      for (unsigned int itrig = 0; itrig != hltresults->size(); ++itrig) {
         std::string trigName = triggerNames_.triggerName(itrig);
         //  std::cout<<" trigger name = " << trigName << std::endl;
         bool thistrig = false;
         //if (trigName.find("HLT_PFNoPUHT350_PFMET100_v") != std::string::npos)
         if (trigName.find("HLT_PFHT350_PFMET100_v") != std::string::npos)
            thistrig = hltresults->accept(itrig);
         if (thistrig)
            triggered_probe_MHT = true;
      }

      // ----------------------------------------------------------------------------- //
      // check if jets in event fulfill jet ID
      // ----------------------------------------------------------------------------- //
      bool goodJetEvent = true;
      for (edm::View<pat::Jet>::const_iterator it = Jets_rec.begin(); it != Jets_rec.end(); ++it) {
         if ( it->pt() > 30. ) {
            PFJetIDSelectionFunctor jetIDLoosePF(PFJetIDSelectionFunctor::FIRSTDATA, PFJetIDSelectionFunctor::LOOSE);
            pat::strbitset ret = jetIDLoosePF.getBitTemplate();
            ret.set(false);
            bool loose = jetIDLoosePF(*it, ret);
            if (!loose) {
               goodJetEvent = false;
               break;
            } 
         }
      }

      // ----------------------------------------------------------------------------- //
      //// Fill the histograms
      // ----------------------------------------------------------------------------- //
      double HT = 0.;
      math::PtEtaPhiMLorentzVector MHT(0., 0., 0., 0.);
      for (edm::View<pat::Jet>::const_iterator it = Jets_rec.begin(); it != Jets_rec.end(); ++it) {
         if (goodJet_MHT(&(*it))) {
            h_jetpt_MHT->Fill(it->pt());
            h_jeteta_MHT->Fill(it->eta());
            h_jetphi_MHT->Fill(it->phi());
            MHT -= it->p4();
         }
      
         if (goodJet_HT(&(*it))) {
            h_jetpt_HT->Fill(it->pt());
            h_jeteta_HT->Fill(it->eta());
            h_jetphi_HT->Fill(it->phi());
            HT += it->pt();
         }
      }

      // fill histos for MHT + MET turn-on
      if (triggered_tag_MHT && HT > 500. && goodJetEvent) {
         h_MHTallprobes->Fill(MHT.pt());
         if( MHT.pt() > 200. ) {
            h_MHTallprobes_total->Fill(0.);
         }
         for (edm::View<pat::MET>::const_iterator it = Met_rec.begin(); it != Met_rec.end(); ++it) {
            h_METallprobes->Fill(it->pt());
            break;
         }
      }
      if (triggered_probe_MHT && triggered_tag_MHT && HT > 500. && goodJetEvent) {
         h_MHTpassedprobes->Fill(MHT.pt());
         if( MHT.pt() > 200. ) {
            h_MHTpassedprobes_total->Fill(0.);
         }
         for (edm::View<pat::MET>::const_iterator it = Met_rec.begin(); it != Met_rec.end(); ++it) {
            h_METpassedprobes->Fill(it->pt());
            break;
         }
      }
    
      // fill histos for HT turn-on
      if (triggered_tag_HT && MHT.pt() > 200. && goodJetEvent) {
         h_HTallprobes->Fill(HT);
         if( HT > 500. ) {
            h_HTallprobes_total->Fill(0.);
         }
      }
      if (triggered_probe_HT && triggered_tag_HT && MHT.pt() > 200. && goodJetEvent) {
         h_HTpassedprobes->Fill(HT);
         if( HT > 500. ) {
            h_HTpassedprobes_total->Fill(0.);
         }
      }

      // ----------------------------------------------------------------------------- //
      // check events which do NOT pass the signal trigger
      // ----------------------------------------------------------------------------- //
      int jetCounter = 0;
      // control plots
      if (triggered_tag_MHT && HT > 500. && MHT.pt() > 200. && !triggered_probe_MHT ) {
         cout << "Bad event EventNumber:" << iEvent.id().event() << endl;
         cout << "Bad event LumiNumber:" << iEvent.id().luminosityBlock() << endl;
         cout << "Bad event RunNumber:" << iEvent.id().run() << endl;
         cout << "Bad event HT:" << HT << endl;
         cout << "Bad event MHT:" << MHT.pt() << endl;

         for (edm::View<pat::Jet>::const_iterator it = Jets_rec.begin(); it != Jets_rec.end(); ++it) {
            jetCounter++;
            if (goodJet_MHT(&(*it))) {
               cout << "MHT jet:" << jetCounter << ": pt:" << it->pt() << endl;
               cout << "MHT jet:" << jetCounter << ": eta:" << it->eta() << endl;
               cout << "MHT jet:" << jetCounter << ": phi:" << it->phi() << endl;
               cout << "MHT jet:" << jetCounter << ": photonEnergyFraction:" << it->photonEnergyFraction() << endl;
               cout << "MHT jet:" << jetCounter << ": electronEnergyFraction:" << it->electronEnergyFraction() << endl;
               cout << "MHT jet:" << jetCounter << ": muonEnergyFraction:" << it->muonEnergyFraction() << endl;
               cout << "MHT jet:" << jetCounter << ": HFHadronEnergyFraction:" << it->HFHadronEnergyFraction() << endl;
               cout << "MHT jet:" << jetCounter << ": HFEMEnergyFraction:" << it->HFEMEnergyFraction() << endl;
               cout << "MHT jet:" << jetCounter << ": chargedHadronMultiplicity:" << it->chargedHadronMultiplicity() << endl;
               cout << "MHT jet:" << jetCounter << ": neutralHadronMultiplicity:" << it->neutralHadronMultiplicity() << endl;
               cout << "MHT jet:" << jetCounter << ": photonMultiplicity:" << it->photonMultiplicity() << endl;
               cout << "MHT jet:" << jetCounter << ": electronMultiplicity:" << it->electronMultiplicity() << endl;
               cout << "MHT jet:" << jetCounter << ": HFHadronMultiplicity:" << it->HFHadronMultiplicity() << endl;
               cout << "MHT jet:" << jetCounter << ": HFEMMultiplicity:" << it->HFEMMultiplicity() << endl;
            }

            if (goodJet_HT(&(*it))) {
               cout << "HT jet:" << jetCounter << ": pt:" << it->pt() << endl;
               cout << "HT jet:" << jetCounter << ": eta:" << it->eta() << endl;
               cout << "HT jet:" << jetCounter << ": phi:" << it->phi() << endl;
               cout << "HT jet:" << jetCounter << ": photonEnergyFraction:" << it->photonEnergyFraction() << endl;
               cout << "HT jet:" << jetCounter << ": electronEnergyFraction:" << it->electronEnergyFraction() << endl;
               cout << "HT jet:" << jetCounter << ": muonEnergyFraction:" << it->muonEnergyFraction() << endl;
               cout << "HT jet:" << jetCounter << ": HFHadronEnergyFraction:" << it->HFHadronEnergyFraction() << endl;
               cout << "HT jet:" << jetCounter << ": HFEMEnergyFraction:" << it->HFEMEnergyFraction() << endl;
               cout << "HT jet:" << jetCounter << ": chargedHadronMultiplicity:" << it->chargedHadronMultiplicity() << endl;
               cout << "HT jet:" << jetCounter << ": neutralHadronMultiplicity:" << it->neutralHadronMultiplicity() << endl;
               cout << "HT jet:" << jetCounter << ": photonMultiplicity:" << it->photonMultiplicity() << endl;
               cout << "HT jet:" << jetCounter << ": electronMultiplicity:" << it->electronMultiplicity() << endl;
               cout << "HT jet:" << jetCounter << ": HFHadronMultiplicity:" << it->HFHadronMultiplicity() << endl;
               cout << "HT jet:" << jetCounter << ": HFEMMultiplicity:" << it->HFEMMultiplicity() << endl;
            }
         }
      }

      // ----------------------------------------------------------------------------- //
      // get online HT and MHT --> does not work properly for HT
      // ----------------------------------------------------------------------------- //
      //--- get trigger event
      edm::InputTag trigEventTag("hltTriggerSummaryAOD::HLT"); 
      edm::Handle < trigger::TriggerEvent > trigEvent; 
      iEvent.getByLabel(trigEventTag,trigEvent);

      //--- specify trigger filter names ---//
      std::string filterName_ht("hltPFHT350"); 
      std::string filterName_mht("hltPFMHT150Filter"); 
   
      //--- get index of specified trigger filter ---//
      trigger::size_type filterIndex_ht = 
         trigEvent->filterIndex(edm::InputTag(filterName_ht,"",trigEventTag.process())); 
      trigger::size_type filterIndex_mht = 
         trigEvent->filterIndex(edm::InputTag(filterName_mht,"",trigEventTag.process())); 

      //--- define online HT and MHT ---//
      float hltHt(0);
      float hltMHt(0);

      //--- fill online HT ---// --> does not work properly for HT
      if(filterIndex_ht < trigEvent->sizeFilters()){ 
         const trigger::Keys& trigKeys = trigEvent->filterKeys(filterIndex_ht); 
         const trigger::TriggerObjectCollection & trigObjColl(trigEvent->getObjects());
         //now loop over the trigger objects passing filter
         for(trigger::Keys::const_iterator keyIt = trigKeys.begin(); keyIt != trigKeys.end(); ++keyIt){ 
            const trigger::TriggerObject& obj = trigObjColl[*keyIt];
            hltHt = obj.pt();
            //    cout<< "hltHT:" << hltHt << endl;
         }   
      }

      //--- fill online MHT ---// 
      if(filterIndex_mht < trigEvent->sizeFilters()){ 
         const trigger::Keys& trigKeys = trigEvent->filterKeys(filterIndex_mht); 
         const trigger::TriggerObjectCollection & trigObjColl(trigEvent->getObjects());
         //now loop over the trigger objects passing filter
         for(trigger::Keys::const_iterator keyIt = trigKeys.begin(); keyIt != trigKeys.end(); ++keyIt){ 
            const trigger::TriggerObject& obj = trigObjColl[*keyIt];
            hltMHt = obj.pt();
         }   
      }

      // fill correlation histos online/offline HT/MHT --> does not work properly for HT
      if(triggered_probe_HT) {
         h_Corr_OnlineHT_OfflineHT->Fill(hltHt, HT);
      }
      if(triggered_probe_MHT) {
         h_Corr_OnlineMHT_OfflineMHT->Fill(hltMHt, MHT.pt());
         for (edm::View<pat::MET>::const_iterator it = Met_rec.begin(); it != Met_rec.end(); ++it) {
            h_Corr_OnlineMHT_OfflineMET->Fill(hltMHt, it->pt());
            break;
         }
      }

      // ----------------------------------------------------------------------------- //
      // correlation between pt of jets and muons
      // ----------------------------------------------------------------------------- //
      for (edm::View<pat::Jet>::const_iterator it = Jets_rec.begin(); it != Jets_rec.end(); ++it) {
         double dRmin = 100;
         const reco::Muon* matchedMuon = 0;
         for (edm::View<pat::Muon>::const_iterator jt = Muons_rec.begin(); jt != Muons_rec.end(); ++jt) {
            double dR = deltaR(*jt, *it);
            if (dR < dRmin) {
               dRmin = dR;
               matchedMuon = &(*jt);
            }
            if (dRmin < 0.1){
               h_Corr_JetPt_MuonPT->Fill( matchedMuon->pt(), it->pt() );
            }
         }
      }

      // ----------------------------------------------------------------------------- //
      // correlation between pt of jets and electrons
      // ----------------------------------------------------------------------------- //
      for (edm::View<pat::Jet>::const_iterator it = Jets_rec.begin(); it != Jets_rec.end(); ++it) {
         double dRmin = 100;
         const reco::GsfElectron* matchedElectron = 0;
         for (edm::View<pat::Electron>::const_iterator jt = Electrons_rec.begin(); jt != Electrons_rec.end(); ++jt) {
            double dR = deltaR(*jt, *it);
            if (dR < dRmin) {
               dRmin = dR;
               matchedElectron = &(*jt);
            }
            if (dRmin < 0.1){
               h_Corr_JetPt_ElectronPT->Fill( matchedElectron->pt(), it->pt() );
            }
         }
      }
   }
}


// ------------ method called once each job just before starting event loop  ------------
void 
Trigger::beginJob()
{
   edm::Service < TFileService > fs;
   if (!fs) {
      throw edm::Exception(edm::errors::Configuration, "TFile Service is not registered in cfg file");
   }
  
   h_met = fs->make < TH1F > ("met", "Met (Type I)", 100, 0., 1000.);
   h_met->Sumw2();

   h_jetpt_MHT = fs->make < TH1F > ("jetpt_MHT", "Jet Pt", 100, 0., 1000.);
   h_jetpt_MHT->Sumw2();
   h_jeteta_MHT = fs->make < TH1F > ("jeteta_MHT", "Jet Eta", 100, -5., 5.);
   h_jeteta_MHT->Sumw2();
   h_jetphi_MHT = fs->make < TH1F > ("jetphi_MHT", "Jet Phi", 100, -TMath::Pi(), -TMath::Pi());
   h_jetphi_MHT->Sumw2();

   h_jetpt_HT = fs->make < TH1F > ("jetpt_HT", "Jet Pt", 100, 0., 1000.);
   h_jetpt_HT->Sumw2();
   h_jeteta_HT = fs->make < TH1F > ("jeteta_HT", "Jet Eta", 100, -5., 5.);
   h_jeteta_HT->Sumw2();
   h_jetphi_HT = fs->make < TH1F > ("jetphi_HT", "Jet Phi", 100, -TMath::Pi(), -TMath::Pi());
   h_jetphi_HT->Sumw2();

   // ----------------------------------------------------------------------------- //

   h_MHTallprobes = fs->make < TH1F > ("MHTallprobes", "MHT all probes", 100, 0., 500.);
   h_MHTallprobes->Sumw2();
   h_MHTpassedprobes = fs->make < TH1F > ("MHTpassedprobes", "MHT passed probes", 100, 0., 500.);
   h_MHTpassedprobes->Sumw2();
   h_MHTturnon = fs->make < TH1F > ("MHTturnon", "MHTturnon", 100, 0., 500.);
   h_MHTturnon->Sumw2();

   h_MHTallprobes_total = fs->make < TH1F > ("MHTallprobes_total", "MHT all probes", 1, -0.5, 0.5);
   h_MHTallprobes_total->Sumw2();
   h_MHTpassedprobes_total = fs->make < TH1F > ("MHTpassedprobes_total", "MHT passed probes", 1, -0.5, 0.5);
   h_MHTpassedprobes_total->Sumw2();

   h_MHTallprobes_intEff = fs->make < TH1F > ("MHTallprobes_intEff", "MHT all probes", 100, 0., 500.);
   h_MHTallprobes_intEff->Sumw2();
   h_MHTpassedprobes_intEff = fs->make < TH1F > ("MHTpassedprobes_intEff", "MHT passed probes", 100, 0., 500.);
   h_MHTpassedprobes_intEff->Sumw2();

   h_METallprobes = fs->make < TH1F > ("METallprobes", "MET all probes", 100, 0., 500.);
   h_METallprobes->Sumw2();
   h_METpassedprobes = fs->make < TH1F > ("METpassedprobes", "MET passed probes", 100, 0., 500.);
   h_METpassedprobes->Sumw2();

   h_HTallprobes = fs->make < TH1F > ("HTallprobes", "HT all probes", 100, 0., 2000.);
   h_HTallprobes->Sumw2();
   h_HTpassedprobes = fs->make < TH1F > ("HTpassedprobes", "HT passed probes", 100, 0., 2000.);
   h_HTpassedprobes->Sumw2();
   h_HTturnon = fs->make < TH1F > ("HTturnon", "HTturnon", 100, 0., 2000.);
   h_HTturnon->Sumw2();

   h_HTallprobes_total = fs->make < TH1F > ("HTallprobes_total", "HT all probes", 1, -0.5, 0.5);
   h_HTallprobes_total->Sumw2();
   h_HTpassedprobes_total = fs->make < TH1F > ("HTpassedprobes_total", "HT passed probes", 1, -0.5, 0.5);
   h_HTpassedprobes_total->Sumw2();

   h_HTallprobes_intEff = fs->make < TH1F > ("HTallprobes_intEff", "HT all probes", 100, 0., 2000.);
   h_HTallprobes_intEff->Sumw2();
   h_HTpassedprobes_intEff = fs->make < TH1F > ("HTpassedprobes_intEff", "HT passed probes", 100, 0., 2000.);
   h_HTpassedprobes_intEff->Sumw2();

   // ----------------------------------------------------------------------------- //

   h_Corr_JetPt_MuonPT = fs->make < TH2F > ("corr_JetPt_MuonPT", "Correlation JetPT-MuonPT", 
                                            100, 0., 1000., 100, 0., 1000.);
   h_Corr_JetPt_MuonPT->Sumw2();

   h_Corr_JetPt_ElectronPT = fs->make < TH2F > ("corr_JetPt_ElectronPT", "Correlation JetPT-ElectronPT", 
                                            100, 0., 1000., 100, 0., 1000.);
   h_Corr_JetPt_ElectronPT->Sumw2();

   h_Corr_OnlineHT_OfflineHT = fs->make < TH2F > ("corr_online_offlineHT","Correlation Online/Offline HT",
                                                  100, 0., 1000., 100, 0., 1000.);
   h_Corr_OnlineHT_OfflineHT->Sumw2();
   h_Corr_OnlineMHT_OfflineMHT= fs->make < TH2F > ("corr_online_offlineMHT","Correlation Online/Offline MHT",
                                                   100, 0., 1000., 100, 0., 1000.);
   h_Corr_OnlineMHT_OfflineMHT->Sumw2();
   h_Corr_OnlineMHT_OfflineMET= fs->make < TH2F > ("corr_online_offlineMET","Correlation Online/Offline MET",
                                                   100, 0., 1000., 100, 0., 1000.);
   h_Corr_OnlineMHT_OfflineMET->Sumw2();

   // ----------------------------------------------------------------------------- //
}

// ------------ method called once each job just after ending the event loop  ------------
void 
Trigger::endJob() 
{
   // ----------------------------------------------------------------------------- //
   // calculate integrated efficiencies
   // ----------------------------------------------------------------------------- //
   double MHTallprobes_error;
   double MHTpassedprobes_error;
   for(int i = 1; i< h_MHTallprobes->GetNbinsX(); i++) {
      if( h_MHTallprobes->GetBinContent(i) != 0 ) {
         h_MHTallprobes_intEff->SetBinContent(i, h_MHTallprobes->IntegralAndError(i, h_MHTallprobes->GetNbinsX(),MHTallprobes_error));
         h_MHTallprobes_intEff->SetBinError(i, MHTallprobes_error);
         h_MHTpassedprobes_intEff->SetBinContent(i, h_MHTpassedprobes->IntegralAndError(i, h_MHTallprobes->GetNbinsX(),MHTpassedprobes_error));
         h_MHTpassedprobes_intEff->SetBinError(i, MHTpassedprobes_error);
      }
   }

   double HTallprobes_error;
   double HTpassedprobes_error;
   for(int i = 1; i< h_HTallprobes->GetNbinsX(); i++) {
      if( h_HTallprobes->GetBinContent(i) != 0 ) {
         h_HTallprobes_intEff->SetBinContent(i, h_HTallprobes->IntegralAndError(i, h_HTallprobes->GetNbinsX(), HTallprobes_error));
         h_HTallprobes_intEff->SetBinError(i, HTallprobes_error); 
         h_HTpassedprobes_intEff->SetBinContent(i, h_HTpassedprobes->IntegralAndError(i, h_HTallprobes->GetNbinsX(),HTpassedprobes_error));
         h_HTpassedprobes_intEff->SetBinError(i, HTpassedprobes_error); 
      }
   }
}

bool Trigger::goodElectron(const pat::Electron* ele) {
   if (ele->pt() < elec_pt_cut_)
      return false;
   if (fabs(ele->eta()) > elec_eta_cut_)
      return false;
   return true;
}

bool Trigger::goodMuon(const pat::Muon* mu) {
   if (mu->pt() < muon_pt_cut_)
      return false;
   if (fabs(mu->eta()) > muon_eta_cut_)
      return false;
   return true;
}

bool Trigger::goodJet_MHT(const pat::Jet* jet) {
   if (jet->pt() < jet_pt_cut_MHT_)
      return false;
   if (fabs(jet->eta()) > jet_eta_cut_MHT_)
      return false;

   return true;
}

bool Trigger::goodJet_HT(const pat::Jet* jet) {
   if (jet->pt() < jet_pt_cut_HT_)
      return false;
   if (fabs(jet->eta()) > jet_eta_cut_HT_)
      return false;

   /* PFJetIDSelectionFunctor jetIDLoosePF(PFJetIDSelectionFunctor::FIRSTDATA, PFJetIDSelectionFunctor::LOOSE);
   pat::strbitset ret = jetIDLoosePF.getBitTemplate();
   ret.set(false);
   bool loose = jetIDLoosePF(*jet, ret);
   if (!loose)
   return false;*/

   return true;
}

//define this as a plug-in
DEFINE_FWK_MODULE(Trigger);
