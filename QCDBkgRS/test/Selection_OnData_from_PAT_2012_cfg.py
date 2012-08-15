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
           '/store/user/kheine/HT/RA2PreSelectionOnData_Run2012A_HT_PromptReco-v1_v5/71cce229addb17644d40a607fa20b5d7/RA2SkimsOnData_240_3_Ttj.root',
           '/store/user/kheine/HT/RA2PreSelectionOnData_Run2012A_HT_PromptReco-v1_v5/71cce229addb17644d40a607fa20b5d7/RA2SkimsOnData_65_3_oJh.root',
           '/store/user/kheine/HT/RA2PreSelectionOnData_Run2012A_HT_PromptReco-v1_v5/71cce229addb17644d40a607fa20b5d7/RA2SkimsOnData_533_3_8FE.root',
           '/store/user/kheine/HT/RA2PreSelectionOnData_Run2012A_HT_PromptReco-v1_v5/71cce229addb17644d40a607fa20b5d7/RA2SkimsOnData_246_3_xFc.root',
           '/store/user/kheine/HT/RA2PreSelectionOnData_Run2012A_HT_PromptReco-v1_v5/71cce229addb17644d40a607fa20b5d7/RA2SkimsOnData_516_3_dGK.root',
           '/store/user/kheine/HT/RA2PreSelectionOnData_Run2012A_HT_PromptReco-v1_v5/71cce229addb17644d40a607fa20b5d7/RA2SkimsOnData_201_3_3sC.root',
           '/store/user/kheine/HT/RA2PreSelectionOnData_Run2012A_HT_PromptReco-v1_v5/71cce229addb17644d40a607fa20b5d7/RA2SkimsOnData_458_3_HwI.root',
           '/store/user/kheine/HT/RA2PreSelectionOnData_Run2012A_HT_PromptReco-v1_v5/71cce229addb17644d40a607fa20b5d7/RA2SkimsOnData_345_3_t0O.root',  
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
process.load("RA2.FinalPlots.finalplots_cfi")
process.load("RA2.Selection.RA2Selection_cff")
###############################################################################

###############################################################################
# Selections with smeared Jets
###############################################################################
process.RA2PreSelection.writeVariables = True
process.RA2PreSelection.onlySimulation = False

process.RA2FinalHT500NoDeltaPhiSelection.writeVariables = True
process.RA2FinalHT500NoDeltaPhiSelection.onlySimulation = False

process.RA2FinalHT500Selection.writeVariables = True
process.RA2FinalHT500Selection.onlySimulation = False

process.RA2FinalHT800Selection.writeVariables = True
process.RA2FinalHT800Selection.onlySimulation = False

process.RA2FinalHT1000Selection.writeVariables = True
process.RA2FinalHT1000Selection.onlySimulation = False

process.RA2FinalHT1200Selection.writeVariables = True
process.RA2FinalHT1200Selection.onlySimulation = False

process.RA2FinalHT1400Selection.writeVariables = True
process.RA2FinalHT1400Selection.onlySimulation = False
###############################################################################

###############################################################################
# Final plotting with Data
###############################################################################
process.FinalPlotsRA2PreSelectionData = process.finalPlot.clone()
process.FinalPlotsRA2PreSelectionData.selectionSequence = process.RA2PreSelection.selections.selectionSequence
process.FinalPlotsRA2PreSelectionData.selection = 'RA2PreSelection'

process.FinalPlotsRA2FinalHT500NoDeltaPhiSelectionData = process.finalPlot.clone()
process.FinalPlotsRA2FinalHT500NoDeltaPhiSelectionData.weightName = 'weightProducer:weight'
process.FinalPlotsRA2FinalHT500NoDeltaPhiSelectionData.selectionSequence = process.RA2FinalHT500NoDeltaPhiSelection.selections.selectionSequence
process.FinalPlotsRA2FinalHT500NoDeltaPhiSelectionData.selection = 'RA2FinalHT500NoDeltaPhiSelection'

process.FinalPlotsRA2FinalHT500Data = process.finalPlot.clone()
process.FinalPlotsRA2FinalHT500Data.weightName = 'weightProducer:weight'
process.FinalPlotsRA2FinalHT500Data.selectionSequence = process.RA2FinalHT500Selection.selections.selectionSequence
process.FinalPlotsRA2FinalHT500Data.selection = 'RA2FinalHT500Selection'

process.FinalPlotsRA2FinalHT800Data = process.finalPlot.clone()
process.FinalPlotsRA2FinalHT800Data.weightName = 'weightProducer:weight'
process.FinalPlotsRA2FinalHT800Data.selectionSequence = process.RA2FinalHT800Selection.selections.selectionSequence
process.FinalPlotsRA2FinalHT800Data.selection = 'RA2FinalHT800Selection'

process.FinalPlotsRA2FinalHT1000Data = process.finalPlot.clone()
process.FinalPlotsRA2FinalHT1000Data.weightName = 'weightProducer:weight'
process.FinalPlotsRA2FinalHT1000Data.selectionSequence = process.RA2FinalHT1000Selection.selections.selectionSequence
process.FinalPlotsRA2FinalHT1000Data.selection = 'RA2FinalHT1000Selection'

process.FinalPlotsRA2FinalHT1200Data = process.finalPlot.clone()
process.FinalPlotsRA2FinalHT1200Data.weightName = 'weightProducer:weight'
process.FinalPlotsRA2FinalHT1200Data.selectionSequence = process.RA2FinalHT1200Selection.selections.selectionSequence
process.FinalPlotsRA2FinalHT1200Data.selection = 'RA2FinalHT1200Selection'

process.FinalPlotsRA2FinalHT1400Data = process.finalPlot.clone()
process.FinalPlotsRA2FinalHT1400Data.weightName = 'weightProducer:weight'
process.FinalPlotsRA2FinalHT1400Data.selectionSequence = process.RA2FinalHT1400Selection.selections.selectionSequence
process.FinalPlotsRA2FinalHT1400Data.selection = 'RA2FinalHT1400Selection'
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
###############################################################################

###############################################################################
# HLThltEventAnalyzer
###############################################################################
process.load("HLTrigger.HLTcore.hltEventAnalyzerAOD_cfi")
###############################################################################

process.dump   = cms.EDAnalyzer("EventContentAnalyzer")

process.data = cms.Path(
   #   process.htPFFilter *    # to be used for standard jets
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
	process.RA2PreSelection *
	process.FinalPlotsRA2PreSelectionData *
	process.RA2FinalHT500NoDeltaPhiSelection *
	process.FinalPlotsRA2FinalHT500NoDeltaPhiSelectionData *
	process.RA2FinalHT500Selection *
	process.FinalPlotsRA2FinalHT500Data *
	process.RA2FinalHT800Selection *
	process.FinalPlotsRA2FinalHT800Data *
	process.RA2FinalHT1000Selection *
	process.FinalPlotsRA2FinalHT1000Data *
	process.RA2FinalHT1200Selection *
	process.FinalPlotsRA2FinalHT1200Data *
	process.RA2FinalHT1400Selection *
	process.FinalPlotsRA2FinalHT1400Data
)
