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
process.TFileService = cms.Service("TFileService",fileName = cms.string("QCDSmearing_OnData_reduced_2012.root") )
###############################################################################

###############################################################################
process.load("RA2.QCDSmearProd.qcdsmearprod_cfi")
process.load("RA2.FinalPlots.finalplots_cfi")
process.load("RA2.Selection.RA2Selection_cff")
###############################################################################

###############################################################################
# Rebalancing and Smearing configuration
###############################################################################
#process.QCDfromSmearing.SmearingFile = '/afs/naf.desy.de/user/k/kriheine/Resolution/MCJetResolution_Summer11_QCD_Pt_15to3000_TuneZ2_Flat_7TeV_pythia6_fine_v2.root'
#process.QCDfromSmearing.SmearingFile = '/afs/naf.desy.de/user/k/kriheine/Resolution/MCResolutions_Fall11_QCD_Pt-15to3000_TuneZ2_7TeV_pythia6_fine.root'
process.QCDfromSmearing.SmearingFile = '/afs/naf.desy.de/user/k/kriheine/Resolution/MCJetResolution_Summer12_QCD_Pt_15to3000_TuneZ2_Flat_8TeV_pythia6.root'
process.QCDfromSmearing.BProbabilityFile = '/afs/naf.desy.de/user/k/kriheine/Resolution/BJetProbability.root'
process.QCDfromSmearing.jetCollection = process.PatTagNames.jetTag
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
# Selections with smeared Jets
###############################################################################
process.RA2PreSelection.writeVariables = True
process.RA2PreSelection.onlySimulation = False

process.RA2FinalHT500NoDeltaPhiSelection.writeVariables = True
process.RA2FinalHT500NoDeltaPhiSelection.onlySimulation = True

process.RA2FinalHT500Selection.writeVariables = True
process.RA2FinalHT500Selection.onlySimulation = True

process.RA2FinalHT800Selection.writeVariables = True
process.RA2FinalHT800Selection.onlySimulation = True

process.RA2FinalHT1000Selection.writeVariables = True
process.RA2FinalHT1000Selection.onlySimulation = True

process.RA2FinalHT1200Selection.writeVariables = True
process.RA2FinalHT1200Selection.onlySimulation = True

process.RA2FinalHT1400Selection.writeVariables = True
process.RA2FinalHT1400Selection.onlySimulation = True

#####

process.RA2PreSelectionSmeared = process.RA2PreSelection.clone()
process.RA2FinalHT500NoDeltaPhiSelectionSmeared = process.RA2FinalHT500NoDeltaPhiSelection.clone()
process.RA2FinalHT500Smeared = process.RA2FinalHT500Selection.clone()
process.RA2FinalHT800Smeared = process.RA2FinalHT800Selection.clone()
process.RA2FinalHT1000Smeared = process.RA2FinalHT1000Selection.clone()
process.RA2FinalHT1200Smeared = process.RA2FinalHT1200Selection.clone()
process.RA2FinalHT1400Smeared = process.RA2FinalHT1400Selection.clone()
###############################################################################

###############################################################################
# continue: Selections with smeared Jets

RA2PreSelectionSmeared = cms.Sequence(process.RA2PreSelectionSmeared)
RA2FinalHT500NoDeltaPhiSelectionSmeared = cms.Sequence(process.RA2FinalHT500NoDeltaPhiSelectionSmeared)
RA2FinalHT500Smeared = cms.Sequence(process.RA2FinalHT500Smeared)
RA2FinalHT800Smeared = cms.Sequence(process.RA2FinalHT800Smeared)
RA2FinalHT1000Smeared = cms.Sequence(process.RA2FinalHT1000Smeared)
RA2FinalHT1200Smeared = cms.Sequence(process.RA2FinalHT1200Smeared)
RA2FinalHT1400Smeared = cms.Sequence(process.RA2FinalHT1400Smeared)

from PhysicsTools.PatAlgos.tools.helpers import massSearchReplaceAnyInputTag

massSearchReplaceAnyInputTag(RA2PreSelectionSmeared, process.RA2PreSelection.selections.selectors.JetSelection.jetTag, 'QCDfromSmearing:smearedJets')
massSearchReplaceAnyInputTag(RA2FinalHT500NoDeltaPhiSelectionSmeared, process.RA2FinalHT500NoDeltaPhiSelection.selections.selectors.JetSelection.jetTag, 'QCDfromSmearing:smearedJets')
massSearchReplaceAnyInputTag(RA2FinalHT500Smeared, process.RA2FinalHT500Selection.selections.selectors.JetSelection.jetTag, 'QCDfromSmearing:smearedJets')
massSearchReplaceAnyInputTag(RA2FinalHT800Smeared, process.RA2FinalHT800Selection.selections.selectors.JetSelection.jetTag, 'QCDfromSmearing:smearedJets')
massSearchReplaceAnyInputTag(RA2FinalHT1000Smeared, process.RA2FinalHT1000Selection.selections.selectors.JetSelection.jetTag, 'QCDfromSmearing:smearedJets')
massSearchReplaceAnyInputTag(RA2FinalHT1200Smeared, process.RA2FinalHT1200Selection.selections.selectors.JetSelection.jetTag, 'QCDfromSmearing:smearedJets')
massSearchReplaceAnyInputTag(RA2FinalHT1400Smeared, process.RA2FinalHT1400Selection.selections.selectors.JetSelection.jetTag, 'QCDfromSmearing:smearedJets')
###############################################################################

###############################################################################
# Final plotting with smeared Jets
###############################################################################
process.finalPlot.weightName = 'prescaleweightProducer:weight'

process.FinalPlotsRA2PreSelectionSmeared = process.finalPlot.clone()
process.FinalPlotsRA2PreSelectionSmeared.selectionSequence = process.RA2PreSelectionSmeared.selections.selectionSequence
process.FinalPlotsRA2PreSelectionSmeared.selection = 'RA2PreSelectionSmeared'

process.FinalPlotsRA2FinalHT500NoDeltaPhiSelectionSmeared = process.finalPlot.clone()
process.FinalPlotsRA2FinalHT500NoDeltaPhiSelectionSmeared.selectionSequence = process.RA2FinalHT500NoDeltaPhiSelectionSmeared.selections.selectionSequence
process.FinalPlotsRA2FinalHT500NoDeltaPhiSelectionSmeared.selection = 'RA2FinalHT500NoDeltaPhiSelectionSmeared'

process.FinalPlotsRA2FinalHT500Smeared = process.finalPlot.clone()
process.FinalPlotsRA2FinalHT500Smeared.selectionSequence = process.RA2FinalHT500Smeared.selections.selectionSequence
process.FinalPlotsRA2FinalHT500Smeared.selection = 'RA2FinalHT500Smeared'

process.FinalPlotsRA2FinalHT800Smeared = process.finalPlot.clone()
process.FinalPlotsRA2FinalHT800Smeared.selectionSequence = process.RA2FinalHT800Smeared.selections.selectionSequence
process.FinalPlotsRA2FinalHT800Smeared.selection = 'RA2FinalHT800Smeared'

process.FinalPlotsRA2FinalHT1000Smeared = process.finalPlot.clone()
process.FinalPlotsRA2FinalHT1000Smeared.selectionSequence = process.RA2FinalHT1000Smeared.selections.selectionSequence
process.FinalPlotsRA2FinalHT1000Smeared.selection = 'RA2FinalHT1000Smeared'

process.FinalPlotsRA2FinalHT1200Smeared = process.finalPlot.clone()
process.FinalPlotsRA2FinalHT1200Smeared.selectionSequence = process.RA2FinalHT1200Smeared.selections.selectionSequence
process.FinalPlotsRA2FinalHT1200Smeared.selection = 'RA2FinalHT1200Smeared'

process.FinalPlotsRA2FinalHT1400Smeared = process.finalPlot.clone()
process.FinalPlotsRA2FinalHT1400Smeared.selectionSequence = process.RA2FinalHT1400Smeared.selections.selectionSequence
process.FinalPlotsRA2FinalHT1400Smeared.selection = 'RA2FinalHT1400Smeared'
###############################################################################

###############################################################################
# Final plotting with Data
###############################################################################
process.FinalPlotsRA2PreSelectionData = process.finalPlot.clone()
process.FinalPlotsRA2PreSelectionData.weightName = 'prescaleweightProducer:weight'
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
# Weight producer
###############################################################################
process.load("RA2.WeightProducer.prescaleweightproducer_cfi")
process.prescaleweightProducer.PrescaleCut = -1
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

process.prediction = cms.Path(
    # process.dump *
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
    process.prescaleweightProducer *
    process.RA2WeightSelection *
    process.RA2PreSelection *
    process.QCDfromSmearing *
    process.RA2PreSelectionSmeared *
    process.FinalPlotsRA2PreSelectionSmeared *
    process.RA2FinalHT500NoDeltaPhiSelectionSmeared *
    process.FinalPlotsRA2FinalHT500NoDeltaPhiSelectionSmeared *
    process.RA2FinalHT500Smeared *
    process.FinalPlotsRA2FinalHT500Smeared *
    process.RA2FinalHT800Smeared *
    process.FinalPlotsRA2FinalHT800Smeared *
    process.RA2FinalHT1000Smeared *
    process.FinalPlotsRA2FinalHT1000Smeared *
    process.RA2FinalHT1200Smeared *
    process.FinalPlotsRA2FinalHT1200Smeared * 
    process.RA2FinalHT1400Smeared *
    process.FinalPlotsRA2FinalHT1400Smeared
    )



