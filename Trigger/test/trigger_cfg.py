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

process = cms.Process("Trigger")

###############################################################################
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 100
###############################################################################

## Options and Output Report
process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32( 10000 ) )

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
###############################################################################
## Global tags and geometry
# default configuration with frontier conditions
process.load("Configuration.Geometry.GeometryIdeal_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string(GlobalTagName)
###############################################################################

###############################################################################
process.TFileService = cms.Service("TFileService",fileName = cms.string("Trigger_2012.root") )
###############################################################################
process.load("RA2Classic.Trigger.trigger_cfi")
process.trigger.jet_pt_cut_MHT = 30.
process.trigger.jet_pt_cut_HT = 50.
process.trigger.num_of_jets = 2
process.trigger.jetCollection = 'patJetsPF'
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
process.load('SandBox.Skims.RA2HT_cff')
###############################################################################

process.dump = cms.EDAnalyzer("EventContentAnalyzer")

process.turnon = cms.Path(
 #  process.dump*
 #  process.htPFchsFilter *  # to be used for chs jets
    process.RA2_HBHENoiseFilterRA2 *
    process.RA2_beamHaloFilter *
 #  process.RA2_eeNoiseFilter *
    process.RA2_trackingFailureFilter *
    process.RA2_inconsistentMuons *
    process.RA2_greedyMuons *
    process.RA2_EcalTPFilter *
    process.RA2_EcalBEFilter *
    process.EEBadScFilter *
    process.HCALLaserEvtFilterList2012 *
    process.PBNRFilter *
    process.trigger
)



