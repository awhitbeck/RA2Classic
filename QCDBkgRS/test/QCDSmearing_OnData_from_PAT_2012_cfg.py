###############################################################################
import sys,os

GlobalTagName = ""
if hasattr(sys,"argv"):
    for arg in sys.argv :
        pairs = arg.split(',')
        for pair in pairs:
            vals = pair.split('=')
            if len(vals) == 2 :
                if vals[0] == "GlobalTag":
                    GlobalTagName = vals[1]

GlobalTagName += "::All"

print "********** GlobalTag = "+GlobalTagName

###############################################################################

import FWCore.ParameterSet.Config as cms

process = cms.Process("RA2QCDSmearingClosure")

###############################################################################
#-- Message Logger ------------------------------------------------------------
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 100
process.MessageLogger.suppressWarning = cms.untracked.vstring('TriggerSelectionLow','TriggerSelectionHigh','TriggerSelectionSignal')
 
###############################################################################

## Options and Output Report
process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )

process.source = cms.Source("PoolSource",
	fileNames = cms.untracked.vstring(
           '/store/user/mschrode/HT/RA2PreSelection_Run2012A-13Jul2012-v1_V2/528d417548fa47de754292e17c1b0d17/RA2Skim_215_1_7bE.root',
           '/store/user/mschrode/HT/RA2PreSelection_Run2012A-13Jul2012-v1_V2/528d417548fa47de754292e17c1b0d17/RA2Skim_28_1_EOW.root',
           '/store/user/mschrode/HT/RA2PreSelection_Run2012A-13Jul2012-v1_V2/528d417548fa47de754292e17c1b0d17/RA2Skim_215_1_7bE.root',
           '/store/user/mschrode/HT/RA2PreSelection_Run2012A-13Jul2012-v1_V2/528d417548fa47de754292e17c1b0d17/RA2Skim_27_1_LQC.root',
           '/store/user/mschrode/HT/RA2PreSelection_Run2012A-13Jul2012-v1_V2/528d417548fa47de754292e17c1b0d17/RA2Skim_32_1_HnL.root',
           '/store/user/mschrode/HT/RA2PreSelection_Run2012A-13Jul2012-v1_V2/528d417548fa47de754292e17c1b0d17/RA2Skim_47_1_Q7T.root',
           '/store/user/mschrode/HT/RA2PreSelection_Run2012A-13Jul2012-v1_V2/528d417548fa47de754292e17c1b0d17/RA2Skim_72_1_DcZ.root',
           '/store/user/mschrode/HT/RA2PreSelection_Run2012A-13Jul2012-v1_V2/528d417548fa47de754292e17c1b0d17/RA2Skim_82_1_zkG.root'           
	)
)
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32( 1000 ) )

###############################################################################
## Global tags and geometry
# default configuration with frontier conditions
process.load("Configuration.Geometry.GeometryIdeal_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string(GlobalTagName)
###############################################################################

###############################################################################
process.TFileService = cms.Service("TFileService",fileName = cms.string("QCDSmearing_OnData_reduced_2012.root") )
###############################################################################

###############################################################################
process.load("RA2Classic.QCDBkgRS.qcdbkgrs_cfi")
###############################################################################

###############################################################################
# Rebalancing and Smearing configuration
###############################################################################
#process.QCDfromSmearing.SmearingFile = '/afs/naf.desy.de/user/k/kriheine/Resolution/MCJetResolution_Summer11_QCD_Pt_15to3000_TuneZ2_Flat_7TeV_pythia6_fine_v2.root'
#process.QCDfromSmearing.SmearingFile = '/afs/naf.desy.de/user/k/kriheine/Resolution/MCResolutions_Fall11_QCD_Pt-15to3000_TuneZ2_7TeV_pythia6_fine.root'
process.QCDfromSmearing.SmearingFile = '/afs/naf.desy.de/user/k/kriheine/Resolution/MCJetResolution_Summer12_QCD_Pt_15to3000_TuneZ2star_Flat_8TeV_pythia6_withCHS_withPUReweighting.root'
process.QCDfromSmearing.BProbabilityFile = '/afs/naf.desy.de/user/k/kriheine/Resolution/BJetProbability.root'
process.QCDfromSmearing.jetCollection = 'patJetsPF'
process.QCDfromSmearing.uncertaintyName = ''
#process.QCDfromSmearing.InputHisto1_HF = 'h_b_Jet1_ResponsePt'
#process.QCDfromSmearing.InputHisto2_HF = 'h_b_Jet2_ResponsePt'
#process.QCDfromSmearing.InputHisto3p_HF = 'h_b_Jet3p_ResponsePt'
#process.QCDfromSmearing.InputHisto1_NoHF = 'h_nob_Jet1_ResponsePt'
#process.QCDfromSmearing.InputHisto2_NoHF = 'h_nob_Jet2_ResponsePt'
#process.QCDfromSmearing.InputHisto3p_NoHF = 'h_nob_Jet3p_ResponsePt'
process.QCDfromSmearing.InputHisto1_HF = 'h_tot_JetAll_ResponsePt'
process.QCDfromSmearing.InputHisto2_HF = 'h_tot_JetAll_ResponsePt'
process.QCDfromSmearing.InputHisto3p_HF = 'h_tot_JetAll_ResponsePt'
process.QCDfromSmearing.InputHisto1_NoHF = 'h_tot_JetAll_ResponsePt'
process.QCDfromSmearing.InputHisto2_NoHF = 'h_tot_JetAll_ResponsePt'
process.QCDfromSmearing.InputHisto3p_NoHF = 'h_tot_JetAll_ResponsePt'
process.QCDfromSmearing.NJets = 2
process.QCDfromSmearing.NRebin = 1
process.QCDfromSmearing.SmearCollection = 'Reco'

### Binning and Results from 09.Jul.2011 (with residual JEC)
#process.QCDfromSmearing.PtBinEdges_scaling	= cms.vdouble(0, 220, 270, 300, 350, 500, 2200)
#process.QCDfromSmearing.EtaBinEdges_scaling	= cms.vdouble(0, 0.5, 1.1,  1.7, 2.3, 5.0)
#process.QCDfromSmearing.LowerTailScaling		= cms.vdouble(1.02,1.286,1.058,1.065,1.023,1.117,1.153,1.1,1.1,1.095,1.047,1.047,0.913,0.938,0.938,0.938,1.096,1.096,0.962,1.079,1.079,1.079,1.079,1.079,0.794,0.794,0.794,0.794,0.794,0.794)
#process.QCDfromSmearing.UpperTailScaling		= cms.vdouble(1.02,1.286,1.058,1.065,1.023,1.117,1.153,1.1,1.1,1.095,1.047,1.047,0.913,0.938,0.938,0.938,1.096,1.096,0.962,1.079,1.079,1.079,1.079,1.079,0.794,0.794,0.794,0.794,0.794,0.794)
#process.QCDfromSmearing.AdditionalSmearing	= cms.vdouble(1.052,1.052,1.052,1.052,1.052,1.052,1.057,1.057,1.057,1.057,1.057,1.057,1.096,1.096,1.096,1.096,1.096,1.096,1.134,1.134,1.134,1.134,1.134,1.134,1.288,1.288,1.288,1.288,1.288,1.288)
### Binning and Results from 22.Jul.2011 (without residual JEC)
#process.QCDfromSmearing.PtBinEdges_scaling	= cms.vdouble(0, 220, 270, 300, 350, 500, 2200)
#process.QCDfromSmearing.EtaBinEdges_scaling	= cms.vdouble(0, 0.5, 1.1,  1.7, 2.3, 5.0)
#process.QCDfromSmearing.LowerTailScaling		= cms.vdouble(1.02,1.286,1.058,1.065,1.023,1.117,1.153,1.1,1.1,1.095,1.047,1.047,0.913,0.938,0.938,0.938,1.096,1.096,0.962,1.079,1.079,1.079,1.079,1.079,0.794,0.794,0.794,0.794,0.794,0.794)
#process.QCDfromSmearing.UpperTailScaling		= cms.vdouble(1.02,1.286,1.058,1.065,1.023,1.117,1.153,1.1,1.1,1.095,1.047,1.047,0.913,0.938,0.938,0.938,1.096,1.096,0.962,1.079,1.079,1.079,1.079,1.079,0.794,0.794,0.794,0.794,0.794,0.794)
#process.QCDfromSmearing.AdditionalSmearing	= cms.vdouble(1.062,1.062,1.062,1.062,1.062,1.062,1.057,1.057,1.057,1.057,1.057,1.057,1.089,1.089,1.089,1.089,1.089,1.089,1.127,1.127,1.127,1.127,1.127,1.127,1.158,1.158,1.158,1.158,1.158,1.158)
### Binning and Results from 11.Jan.2012 (with residual JEC)
process.QCDfromSmearing.PtBinEdges_scaling	= cms.vdouble(0, 220, 270, 300, 350, 500, 2200)
process.QCDfromSmearing.EtaBinEdges_scaling	= cms.vdouble(0, 0.5, 1.1,  1.7, 2.3, 5.0)
process.QCDfromSmearing.LowerTailScaling		= cms.vdouble(0.953,1.418,1.156,1.305,1.342,1.353,1.096,1.083,1.083,1.195,1.248,1.248,0.965,1.035,1.035,1.035,1.358,1.358,0.938,1.196,1.196,1.196,1.196,1.196,1.069,1.069,1.069,1.069,1.069,1.069)
process.QCDfromSmearing.UpperTailScaling		= cms.vdouble(0.953,1.418,1.156,1.305,1.342,1.353,1.096,1.083,1.083,1.195,1.248,1.248,0.965,1.035,1.035,1.035,1.358,1.358,0.938,1.196,1.196,1.196,1.196,1.196,1.069,1.069,1.069,1.069,1.069,1.069)
process.QCDfromSmearing.AdditionalSmearing	= cms.vdouble(1.052,1.052,1.052,1.052,1.052,1.052,1.057,1.057,1.057,1.057,1.057,1.057,1.096,1.096,1.096,1.096,1.096,1.096,1.134,1.134,1.134,1.134,1.134,1.134,1.288,1.288,1.288,1.288,1.288,1.288)

process.QCDfromSmearing.absoluteTailScaling = False
process.QCDfromSmearing.SmearedJetPt = 0.
process.QCDfromSmearing.RebalanceJetPt = 15.
process.QCDfromSmearing.RebalanceMode = 'MHThigh'
process.QCDfromSmearing.weightName = 'prescaleweightProducer:weight'
process.QCDfromSmearing.ControlPlots = True
process.QCDfromSmearing.IsData = True 
process.QCDfromSmearing.Ntries = 100
process.QCDfromSmearing.MHTcut_low = cms.double(200.)
process.QCDfromSmearing.MHTcut_medium = cms.double(350.)
process.QCDfromSmearing.MHTcut_high = cms.double(500.)
process.QCDfromSmearing.HTcut_low = cms.double(500.)
process.QCDfromSmearing.HTcut_medium = cms.double(800.)
process.QCDfromSmearing.HTcut_high = cms.double(1000.)
process.QCDfromSmearing.HTcut_veryhigh = cms.double(1200.)
process.QCDfromSmearing.HTcut_extremehigh = cms.double(1400.)
#process.QCDfromSmearing.probExtreme = cms.double(3.e-5)

###############################################################################

###############################################################################
# Weight producer
###############################################################################
process.load("RA2Classic.WeightProducer.prescaleweightproducer_cfi")
process.prescaleweightProducer.PrescaleCut = -1
###############################################################################

###############################################################################
# Filters
###############################################################################
from RecoMET.METFilters.jetIDFailureFilter_cfi import jetIDFailure
process.PBNRFilter = jetIDFailure.clone(
    JetSource = cms.InputTag('patJetsPF'),
    MinJetPt      = cms.double(0.0),
    taggingMode   = cms.bool(False)
    )
from RecoMET.METFilters.multiEventFilter_cfi import multiEventFilter
process.HCALLaserEvtFilterList2012 = multiEventFilter.clone(
    file        = cms.FileInPath('EventFilter/HcalRawToDigi/data/AllBadHCALLaser.txt'),
    taggingMode = cms.bool(False)
    )

process.load("SandBox.Skims.filterBoolean_cfi")
process.RA2_HBHENoiseFilterRA2    = process.booleanFilter.clone()
process.RA2_HBHENoiseFilterRA2.ResultSource = cms.InputTag("HBHENoiseFilterRA2","HBHENoiseFilterResult","PAT")
process.RA2_beamHaloFilter        = process.booleanFilter.clone()
process.RA2_beamHaloFilter.ResultSource = cms.InputTag("beamHaloFilter")
process.RA2_eeNoiseFilter         = process.booleanFilter.clone()
process.RA2_eeNoiseFilter.ResultSource = cms.InputTag("eeNoiseFilter")
process.RA2_trackingFailureFilter = process.booleanFilter.clone()
process.RA2_trackingFailureFilter.ResultSource = cms.InputTag("trackingFailureFilter")
process.RA2_inconsistentMuons     = process.booleanFilter.clone()
process.RA2_inconsistentMuons.ResultSource = cms.InputTag("inconsistentMuons")
process.RA2_greedyMuons           = process.booleanFilter.clone()
process.RA2_greedyMuons.ResultSource = cms.InputTag("greedyMuons")
process.RA2_EcalTPFilter          = process.booleanFilter.clone()
process.RA2_EcalTPFilter.ResultSource = cms.InputTag("ra2EcalTPFilter")
process.RA2_EcalBEFilter          = process.booleanFilter.clone()
process.RA2_EcalBEFilter.ResultSource = cms.InputTag("ra2EcalBEFilter")
#process.HcalLaserEventFilter      = process.booleanFilter.clone()
#process.HcalLaserEventFilter.ResultSource = cms.InputTag("hcalLaserEventFilter")
process.EEBadScFilter             = process.booleanFilter.clone()
process.EEBadScFilter.ResultSource = cms.InputTag("eeBadScFilter")
#process.EcalLaserFilter           = process.booleanFilter.clone()
#process.EcalLaserFilter.ResultSource= cms.InputTag("ecalLaserCorrFilter")
###############################################################################

###############################################################################
# Lepton Veto
###############################################################################
process.load('SandBox.Skims.RA2Leptons_cff')
###############################################################################

###############################################################################
process.dump   = cms.EDAnalyzer("EventContentAnalyzer")
###############################################################################

###############################################################################
# HLThltEventAnalyzer
###############################################################################
process.load("HLTrigger.HLTcore.hltEventAnalyzerAOD_cfi")
###############################################################################

process.dump   = cms.EDAnalyzer("EventContentAnalyzer")

process.prediction = cms.Path(
#	process.dump *
   process.RA2_HBHENoiseFilterRA2 *
   process.RA2_beamHaloFilter *
#   process.RA2_eeNoiseFilter *
   process.RA2_trackingFailureFilter *
   process.RA2_inconsistentMuons *
   process.RA2_greedyMuons *
   process.RA2_EcalTPFilter *
   process.RA2_EcalBEFilter *
   process.EEBadScFilter *
   process.HCALLaserEvtFilterList2012 *
   process.PBNRFilter *
   process.ra2PFMuonVeto *
   process.ra2ElectronVeto *
	process.prescaleweightProducer *
	process.QCDfromSmearing 
)





























