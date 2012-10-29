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
           '/store/user/kheine/HT/RA2PreSelectionOnData_Run2012A_HT_PromptReco-v1_v7/e99cf838fe40ef4081c91a81748e6000/RA2SkimsOnData_312_1_l4U.root',
           '/store/user/kheine/HT/RA2PreSelectionOnData_Run2012A_HT_PromptReco-v1_v7/e99cf838fe40ef4081c91a81748e6000/RA2SkimsOnData_195_1_Dhl.root',
           '/store/user/kheine/HT/RA2PreSelectionOnData_Run2012A_HT_PromptReco-v1_v7/e99cf838fe40ef4081c91a81748e6000/RA2SkimsOnData_156_1_xny.root',
           '/store/user/kheine/HT/RA2PreSelectionOnData_Run2012A_HT_PromptReco-v1_v7/e99cf838fe40ef4081c91a81748e6000/RA2SkimsOnData_321_1_IhY.root',
           '/store/user/kheine/HT/RA2PreSelectionOnData_Run2012A_HT_PromptReco-v1_v7/e99cf838fe40ef4081c91a81748e6000/RA2SkimsOnData_230_1_bRi.root',
           '/store/user/kheine/HT/RA2PreSelectionOnData_Run2012A_HT_PromptReco-v1_v7/e99cf838fe40ef4081c91a81748e6000/RA2SkimsOnData_67_1_olT.root',
           '/store/user/kheine/HT/RA2PreSelectionOnData_Run2012A_HT_PromptReco-v1_v7/e99cf838fe40ef4081c91a81748e6000/RA2SkimsOnData_646_1_rR0.root',
           '/store/user/kheine/HT/RA2PreSelectionOnData_Run2012A_HT_PromptReco-v1_v7/e99cf838fe40ef4081c91a81748e6000/RA2SkimsOnData_500_1_agk.root', 
	)
)
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32( 1000 ) )

###############################################################################
## Global tags and geometry
# default configuration with frontier conditions
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string('GR_R_52_V9D::All')
###############################################################################

###############################################################################
process.TFileService = cms.Service("TFileService",fileName = cms.string("Selection_OnData_2012.root") )
###############################################################################

###############################################################################
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
process.HcalLaserEventFilter      = process.booleanFilter.clone()
process.HcalLaserEventFilter.ResultSource = cms.InputTag("hcalLaserEventFilter")
process.EEBadScFilter             = process.booleanFilter.clone()
process.EEBadScFilter.ResultSource = cms.InputTag("eeBadScFilter")
###############################################################################

###############################################################################
process.load('SandBox.Skims.RA2HT_cff')
process.load('SandBox.Skims.RA2Leptons_cff')
###############################################################################

###############################################################################
## --- Setup of TreeMaker ----------------------------------------------
from RA2Classic.TreeMaker.treemaker_cfi import TreeMaker
process.RA2TreeMaker = TreeMaker.clone(
    TreeName         = cms.string("RA2PreSelection"),
    VarsDouble       = cms.VInputTag(cms.InputTag('weightProducer:weight')),
    VarsDoubleNamesInTree = cms.vstring('Weight'),
    VertexCollection = cms.InputTag('goodVertices'),
 #   HT               = cms.InputTag('htPF'),
    HT               = cms.InputTag('htPFchs'),
    HTJets           = cms.InputTag('HTJets'),
 #   MHT              = cms.InputTag('mhtPF'),
    MHT              = cms.InputTag('mhtPFchs'),
    MHTJets          = cms.InputTag('MHTJets')
    )
process.load('RA2Classic.Utils.produceRA2JetsPFCHS_cff')
#process.load('RA2Classic.Utils.produceRA2JetsAK5PF_cff')
###############################################################################

###############################################################################
# HLThltEventAnalyzer
###############################################################################
process.load("HLTrigger.HLTcore.hltEventAnalyzerAOD_cfi")
###############################################################################

process.dump   = cms.EDAnalyzer("EventContentAnalyzer")

process.data = cms.Path(
 #  process.htPFFilter *    # to be used for standard jets
   process.htPFchsFilter *     # to be used for chs jets 
   process.RA2_HBHENoiseFilterRA2 *
   process.RA2_beamHaloFilter *
   process.RA2_eeNoiseFilter *
   process.RA2_trackingFailureFilter *
   process.RA2_inconsistentMuons *
   process.RA2_greedyMuons *
   process.RA2_EcalTPFilter *
   process.RA2_EcalBEFilter *
   process.HcalLaserEventFilter *
   process.EEBadScFilter *
   process.ra2PFMuonVeto *
   process.ra2ElectronVeto * 
   process.produceRA2JetsPFCHS *
 #  process.produceRA2JetsAK5PF *
   process.RA2TreeMaker   
)

