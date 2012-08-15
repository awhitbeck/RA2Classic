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
process.TFileService = cms.Service("TFileService",fileName = cms.string("QCDSmearing_OnData.root") )
###############################################################################

###############################################################################
process.load("RA2.QCDSmearProd.qcdsmearprod_cfi")
process.load("RA2.FinalPlots.finalplots_cfi")
process.load("RA2.Selection.RA2Selection_cff")
###############################################################################

###############################################################################
# Rebalancing and Smearing configuration
###############################################################################
#process.QCDfromSmearing.SmearingFile = '/afs/naf.desy.de/user/c/csander/Resolution/MCJetResolution_Summer11_QCD_Pt_15to3000_TuneZ2_Flat_7TeV_pythia6_fine_v2.root'
process.QCDfromSmearing.SmearingFile = '/afs/naf.desy.de/user/k/kriheine/Resolution/MCResolutions_Fall11_QCD_Pt-15to3000_TuneZ2_7TeV_pythia6_fine.root'
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
process.QCDfromSmearing.NRebin = 1
process.QCDfromSmearing.SmearCollection = 'Reco'
### Binning and Results from 18.Jan.2011
#process.QCDfromSmearing.PtBinEdges_scaling	= cms.vdouble(0, 43, 150, 170, 250, 2200)
#process.QCDfromSmearing.EtaBinEdges_scaling	= cms.vdouble(0, 1.1, 1.7, 2.3, 5.0)
#process.QCDfromSmearing.LowerTailScaling		= cms.vdouble(0.900,0.900,1.332,1.322,1.257,1.253,1.253,1.253,1.024,1.024,3.155,3.155,3.155,3.155,3.155,1.490,1.490,1.490,1.490,1.490)
#process.QCDfromSmearing.UpperTailScaling		= cms.vdouble(0.900,0.900,1.332,1.322,1.257,1.253,1.253,1.253,1.024,1.024,3.155,3.155,3.155,3.155,3.155,1.490,1.490,1.490,1.490,1.490)
#process.QCDfromSmearing.AdditionalSmearing	= cms.vdouble(1.048,1.048,1.048,1.048,1.048,1.058,1.058,1.058,1.058,1.058,0.983,0.983,0.983,0.983,0.983,1.110,1.110,1.110,1.110,1.110)
### Binning and Results from 21.Jun.2011
#process.QCDfromSmearing.PtBinEdges_scaling	= cms.vdouble(0, 220, 270, 300, 350, 500, 2200)
#process.QCDfromSmearing.EtaBinEdges_scaling	= cms.vdouble(0, 0.5, 1.1,  1.7, 2.3, 5.0)
#process.QCDfromSmearing.LowerTailScaling		= cms.vdouble(1.282,1.493,1.12,1.078,0.947,0.989,1.189,1.214,1.214,1.05,1.127,1.127,0.849,0.845,0.845,0.845,1.072,1.072,0.94,1.003,1.003,1.003,1.003,1.003,0.467,0.467,0.467,0.467,0.467,0.467)
#process.QCDfromSmearing.UpperTailScaling		= cms.vdouble(1.282,1.493,1.12,1.078,0.947,0.989,1.189,1.214,1.214,1.05,1.127,1.127,0.849,0.845,0.845,0.845,1.072,1.072,0.94,1.003,1.003,1.003,1.003,1.003,0.467,0.467,0.467,0.467,0.467,0.467)
#process.QCDfromSmearing.AdditionalSmearing	= cms.vdouble(1.035,1.035,1.035,1.035,1.035,1.035,1.054,1.054,1.054,1.054,1.054,1.054,1.085,1.085,1.085,1.085,1.085,1.085,1.161,1.161,1.161,1.161,1.161,1.161,1.062,1.062,1.062,1.062,1.062,1.062)
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
######
process.QCDfromSmearing.absoluteTailScaling = False
process.QCDfromSmearing.SmearedJetPt = 0.
process.QCDfromSmearing.RebalanceJetPt = 15.
process.QCDfromSmearing.RebalanceMode = 'MHThigh'
process.QCDfromSmearing.weightName = 'prescaleweightProducer:weight'
process.QCDfromSmearing.ControlPlots = False
process.QCDfromSmearing.Ntries = 100
process.QCDfromSmearing.MHTcut_low = cms.double(200.)
process.QCDfromSmearing.MHTcut_medium = cms.double(350.)
process.QCDfromSmearing.MHTcut_high = cms.double(500.)
process.QCDfromSmearing.HTcut_low = cms.double(500.)
process.QCDfromSmearing.HTcut_medium = cms.double(800.)
process.QCDfromSmearing.HTcut_high = cms.double(1000.)
process.QCDfromSmearing.HTcut_veryhigh = cms.double(1200.)
process.QCDfromSmearing.HTcut_extremehigh = cms.double(1400.)

### Binning and Results from 18.Jan.2011
#process.QCDfromSmearingCoreUP = process.QCDfromSmearing.clone()
#process.QCDfromSmearingCoreUP.AdditionalSmearing = cms.vdouble(1.081,1.081,1.081,1.081,1.081,1.097,1.097,1.097,1.097,1.097,1.045,1.045,1.045,1.045,1.045,1.190,1.190,1.190,1.190,1.190)
#process.QCDfromSmearingCoreDN = process.QCDfromSmearing.clone()
#process.QCDfromSmearingCoreDN.AdditionalSmearing = cms.vdouble(1.011,1.011,1.011,1.011,1.011,1.019,1.019,1.019,1.019,1.019,0.923,0.923,0.923,0.923,0.923,1.010,1.010,1.010,1.010,1.010)
#process.QCDfromSmearingTailUP = process.QCDfromSmearing.clone()
#process.QCDfromSmearingTailUP.LowerTailScaling = cms.vdouble(1.061,1.061,1.729,1.729,1.754,1.604,1.604,1.604,1.235,1.235,6.320,6.320,6.320,6.320,6.320,1.986,1.986,1.986,1.986,1.986)
#process.QCDfromSmearingTailUP.UpperTailScaling = cms.vdouble(1.061,1.061,1.729,1.729,1.754,1.604,1.604,1.604,1.235,1.235,6.320,6.320,6.320,6.320,6.320,1.986,1.986,1.986,1.986,1.986)
#process.QCDfromSmearingTailDN = process.QCDfromSmearing.clone()
#process.QCDfromSmearingTailDN.LowerTailScaling = cms.vdouble(0.739,0.739,0.935,0.935,0.760,0.902,0.902,0.902,0.813,0.813,0.000,0.000,0.000,0.000,0.000,0.994,0.994,0.994,0.994,0.994)
#process.QCDfromSmearingTailDN.UpperTailScaling = cms.vdouble(0.739,0.739,0.935,0.935,0.760,0.902,0.902,0.902,0.813,0.813,0.000,0.000,0.000,0.000,0.000,0.994,0.994,0.994,0.994,0.994)

### Binning and Results from 21.Jun.2011
#process.QCDfromSmearingCoreUP = process.QCDfromSmearing.clone()
#process.QCDfromSmearingCoreUP.AdditionalSmearing = cms.vdouble(1.1013,1.1013,1.1013,1.1013,1.1013,1.1013,1.1152,1.1152,1.1152,1.1152,1.1152,1.1152,1.1566,1.1566,1.1566,1.1566,1.1566,1.1566,1.2707,1.2707,1.2707,1.2707,1.2707,1.2707,1.2975,1.2975,1.2975,1.2975,1.2975,1.2975)
#process.QCDfromSmearingCoreUP.uncertaintyName = 'CoreUP'
#process.QCDfromSmearingCoreDN = process.QCDfromSmearing.clone()
#process.QCDfromSmearingCoreDN.AdditionalSmearing = cms.vdouble(0.9698,0.9698,0.9698,0.9698,0.9698,0.9698,0.994,0.994,0.994,0.994,0.994,0.994,1.0144,1.0144,1.0144,1.0144,1.0144,1.0144,1.0539,1.0539,1.0539,1.0539,1.0539,1.0539,0.8277,0.8277,0.8277,0.8277,0.8277,0.8277)
#process.QCDfromSmearingCoreDN.uncertaintyName = 'CoreDN'
#process.QCDfromSmearingTailUP = process.QCDfromSmearing.clone()
#process.QCDfromSmearingTailUP.LowerTailScaling = cms.vdouble(1.598,1.893,1.359,1.332,1.13,1.22,1.52,1.552,1.552,1.404,1.462,1.462,1.13,1.06,1.06,1.06,1.422,1.422,1.253,1.477,1.477,1.477,1.477,1.477,0.975,0.975,0.975,0.975,0.975,0.975)
#process.QCDfromSmearingTailUP.UpperTailScaling = cms.vdouble(1.598,1.893,1.359,1.332,1.13,1.22,1.52,1.552,1.552,1.404,1.462,1.462,1.13,1.06,1.06,1.06,1.422,1.422,1.253,1.477,1.477,1.477,1.477,1.477,0.975,0.975,0.975,0.975,0.975,0.975)
#process.QCDfromSmearingTailUP.uncertaintyName = 'TailUP'
#process.QCDfromSmearingTailDN = process.QCDfromSmearing.clone()
#process.QCDfromSmearingTailDN.LowerTailScaling = cms.vdouble(0.966,1.093,0.881,0.824,0.764,0.758,0.858,0.876,0.876,0.696,0.792,0.792,0.568,0.63,0.63,0.63,0.722,0.722,0.627,0.529,0.529,0.529,0.529,0.529,0.,0.,0.,0.,0.,0.)
#process.QCDfromSmearingTailDN.UpperTailScaling = cms.vdouble(0.966,1.093,0.881,0.824,0.764,0.758,0.858,0.876,0.876,0.696,0.792,0.792,0.568,0.63,0.63,0.63,0.722,0.722,0.627,0.529,0.529,0.529,0.529,0.529,0.,0.,0.,0.,0.,0.)
#process.QCDfromSmearingTailDN.uncertaintyName = 'TailDN'

### Binning and Results from 09.Jul.2011 (with residual JEC)

#process.QCDfromSmearingCoreUP = process.QCDfromSmearing.clone()
#process.QCDfromSmearingCoreUP.AdditionalSmearing = cms.vdouble(1.116,1.116,1.116,1.116,1.116,1.116,1.117,1.117,1.117,1.117,1.117,1.117,1.166,1.166,1.166,1.166,1.166,1.166,1.237,1.237,1.237,1.237,1.237,1.237,1.511,1.511,1.511,1.511,1.511,1.511)
#process.QCDfromSmearingCoreUP.uncertaintyName = 'CoreUP'
#process.QCDfromSmearingCoreDN = process.QCDfromSmearing.clone()
#process.QCDfromSmearingCoreDN.AdditionalSmearing = cms.vdouble(0.988,0.988,0.988,0.988,0.988,0.988,0.999,0.999,0.999,0.999,0.999,0.999,0.998,0.998,0.998,0.998,0.998,0.998,1.033,1.033,1.033,1.033,1.033,1.033,1.067,1.067,1.067,1.067,1.067,1.067)
#process.QCDfromSmearingCoreDN.uncertaintyName = 'CoreDN'
#process.QCDfromSmearingTailUP = process.QCDfromSmearing.clone()
#process.QCDfromSmearingTailUP.LowerTailScaling = cms.vdouble(1.302,1.65,1.317,1.347,1.24,1.387,1.479,1.404,1.404,1.468,1.362,1.362,1.19,1.154,1.154,1.154,1.419,1.419,1.213,1.588,1.588,1.588,1.588,1.588,1.236,1.236,1.236,1.236,1.236,1.236)
#process.QCDfromSmearingTailUP.UpperTailScaling = cms.vdouble(1.302,1.65,1.317,1.347,1.24,1.387,1.479,1.404,1.404,1.468,1.362,1.362,1.19,1.154,1.154,1.154,1.419,1.419,1.213,1.588,1.588,1.588,1.588,1.588,1.236,1.236,1.236,1.236,1.236,1.236)
#process.QCDfromSmearingTailUP.uncertaintyName = 'TailUP'
#process.QCDfromSmearingTailDN = process.QCDfromSmearing.clone()
#process.QCDfromSmearingTailDN.LowerTailScaling = cms.vdouble(0.738,0.922,0.799,0.783,0.806,0.847,0.827,0.796,0.796,0.722,0.732,0.732,0.636,0.722,0.722,0.722,0.773,0.773,0.711,0.57,0.57,0.57,0.57,0.57,0.352,0.352,0.352,0.352,0.352,0.352)
#process.QCDfromSmearingTailDN.UpperTailScaling = cms.vdouble(0.738,0.922,0.799,0.783,0.806,0.847,0.827,0.796,0.796,0.722,0.732,0.732,0.636,0.722,0.722,0.722,0.773,0.773,0.711,0.57,0.57,0.57,0.57,0.57,0.352,0.352,0.352,0.352,0.352,0.352)
#process.QCDfromSmearingTailDN.uncertaintyName = 'TailDN'

### Binning and Results from 22.Jul.2011 (without residual JEC)

#process.QCDfromSmearingCoreUP = process.QCDfromSmearing.clone()
#process.QCDfromSmearingCoreUP.AdditionalSmearing = cms.vdouble(1.125,1.125,1.125,1.125,1.125,1.125,1.114,1.114,1.114,1.114,1.114,1.114,1.154,1.154,1.154,1.154,1.154,1.154,1.222,1.222,1.222,1.222,1.222,1.222,1.359,1.359,1.359,1.359,1.359,1.359)
#process.QCDfromSmearingCoreUP.uncertaintyName = 'CoreUP'
#process.QCDfromSmearingCoreDN = process.QCDfromSmearing.clone()
#process.QCDfromSmearingCoreDN.AdditionalSmearing = cms.vdouble(1.000,1.000,1.000,1.000,1.000,1.000,1.001,1.001,1.001,1.001,1.001,1.001,1.025,1.025,1.025,1.025,1.025,1.025,1.035,1.035,1.035,1.035,1.035,1.035,0.958,0.958,0.958,0.958,0.958,0.958)
#process.QCDfromSmearingCoreDN.uncertaintyName = 'CoreDN'
#process.QCDfromSmearingTailUP = process.QCDfromSmearing.clone()
#process.QCDfromSmearingTailUP.LowerTailScaling = cms.vdouble(1.302,1.65,1.317,1.347,1.24,1.387,1.479,1.404,1.404,1.468,1.362,1.362,1.19,1.154,1.154,1.154,1.419,1.419,1.213,1.588,1.588,1.588,1.588,1.588,1.236,1.236,1.236,1.236,1.236,1.236)
#process.QCDfromSmearingTailUP.UpperTailScaling = cms.vdouble(1.302,1.65,1.317,1.347,1.24,1.387,1.479,1.404,1.404,1.468,1.362,1.362,1.19,1.154,1.154,1.154,1.419,1.419,1.213,1.588,1.588,1.588,1.588,1.588,1.236,1.236,1.236,1.236,1.236,1.236)
#process.QCDfromSmearingTailUP.uncertaintyName = 'TailUP'
#process.QCDfromSmearingTailDN = process.QCDfromSmearing.clone()
#process.QCDfromSmearingTailDN.LowerTailScaling = cms.vdouble(0.738,0.922,0.799,0.783,0.806,0.847,0.827,0.796,0.796,0.722,0.732,0.732,0.636,0.722,0.722,0.722,0.773,0.773,0.711,0.57,0.57,0.57,0.57,0.57,0.352,0.352,0.352,0.352,0.352,0.352)
#process.QCDfromSmearingTailDN.UpperTailScaling = cms.vdouble(0.738,0.922,0.799,0.783,0.806,0.847,0.827,0.796,0.796,0.722,0.732,0.732,0.636,0.722,0.722,0.722,0.773,0.773,0.711,0.57,0.57,0.57,0.57,0.57,0.352,0.352,0.352,0.352,0.352,0.352)
#process.QCDfromSmearingTailDN.uncertaintyName = 'TailDN'

### Binning and Results from 11.Jan.2012 (with residual JEC)

process.QCDfromSmearingCoreUP = process.QCDfromSmearing.clone()
process.QCDfromSmearingCoreUP.AdditionalSmearing = cms.vdouble(1.116,1.116,1.116,1.116,1.116,1.116,1.117,1.117,1.117,1.117,1.117,1.117,1.166,1.166,1.166,1.166,1.166,1.166,1.237,1.237,1.237,1.237,1.237,1.237,1.511,1.511,1.511,1.511,1.511,1.511)
process.QCDfromSmearingCoreUP.uncertaintyName = 'CoreUP'
process.QCDfromSmearingCoreDN = process.QCDfromSmearing.clone()
process.QCDfromSmearingCoreDN.AdditionalSmearing = cms.vdouble(0.988,0.988,0.988,0.988,0.988,0.988,0.999,0.999,0.999,0.999,0.999,0.999,0.998,0.998,0.998,0.998,0.998,0.998,1.033,1.033,1.033,1.033,1.033,1.033,1.067,1.067,1.067,1.067,1.067,1.067)
process.QCDfromSmearingCoreDN.uncertaintyName = 'CoreDN'
process.QCDfromSmearingTailUP = process.QCDfromSmearing.clone()
process.QCDfromSmearingTailUP.LowerTailScaling = cms.vdouble(1.236,1.92,1.505,1.655,1.735,1.703,1.47,1.455,1.455,1.52,1.672,1.672,1.298,1.33,1.33,1.33,1.685,1.685,1.224,1.621,1.621,1.621,1.621,1.621,1.839,1.839,1.839,1.839,1.839,1.839)
process.QCDfromSmearingTailUP.UpperTailScaling = cms.vdouble(1.236,1.92,1.505,1.655,1.735,1.703,1.47,1.455,1.455,1.52,1.672,1.672,1.298,1.33,1.33,1.33,1.685,1.685,1.224,1.621,1.621,1.621,1.621,1.621,1.839,1.839,1.839,1.839,1.839,1.839)
process.QCDfromSmearingTailUP.uncertaintyName = 'TailUP'
process.QCDfromSmearingTailDN = process.QCDfromSmearing.clone()
process.QCDfromSmearingTailDN.LowerTailScaling = cms.vdouble(0.67,0.916,0.807,0.955,0.949,1.003,0.722,0.711,0.711,0.87,0.824,0.824,0.632,0.74,0.74,0.74,1.031,1.031,0.652,0.771,0.771,0.771,0.771,0.771,0.299,0.299,0.299,0.299,0.299,0.299)
process.QCDfromSmearingTailDN.UpperTailScaling = cms.vdouble(0.67,0.916,0.807,0.955,0.949,1.003,0.722,0.711,0.711,0.87,0.824,0.824,0.632,0.74,0.74,0.74,1.031,1.031,0.652,0.771,0.771,0.771,0.771,0.771,0.299,0.299,0.299,0.299,0.299,0.299)
process.QCDfromSmearingTailDN.uncertaintyName = 'TailDN'

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

process.RA2FinalHT500SmearedCoreUP = process.RA2FinalHT500Selection.clone()
process.RA2FinalHT800SmearedCoreUP = process.RA2FinalHT800Selection.clone()
process.RA2FinalHT1000SmearedCoreUP = process.RA2FinalHT1000Selection.clone()
process.RA2FinalHT1200SmearedCoreUP = process.RA2FinalHT1200Selection.clone()
process.RA2FinalHT1400SmearedCoreUP = process.RA2FinalHT1400Selection.clone()

process.RA2FinalHT500SmearedCoreDN = process.RA2FinalHT500Selection.clone()
process.RA2FinalHT800SmearedCoreDN = process.RA2FinalHT800Selection.clone()
process.RA2FinalHT1000SmearedCoreDN = process.RA2FinalHT1000Selection.clone()
process.RA2FinalHT1200SmearedCoreDN = process.RA2FinalHT1200Selection.clone()
process.RA2FinalHT1400SmearedCoreDN = process.RA2FinalHT1400Selection.clone()

process.RA2FinalHT500SmearedTailUP = process.RA2FinalHT500Selection.clone()
process.RA2FinalHT800SmearedTailUP = process.RA2FinalHT800Selection.clone()
process.RA2FinalHT1000SmearedTailUP = process.RA2FinalHT1000Selection.clone()
process.RA2FinalHT1200SmearedTailUP = process.RA2FinalHT1200Selection.clone()
process.RA2FinalHT1400SmearedTailUP = process.RA2FinalHT1400Selection.clone()

process.RA2FinalHT500SmearedTailDN = process.RA2FinalHT500Selection.clone()
process.RA2FinalHT800SmearedTailDN = process.RA2FinalHT800Selection.clone()
process.RA2FinalHT1000SmearedTailDN = process.RA2FinalHT1000Selection.clone()
process.RA2FinalHT1200SmearedTailDN = process.RA2FinalHT1200Selection.clone()
process.RA2FinalHT1400SmearedTailDN = process.RA2FinalHT1400Selection.clone()
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

RA2FinalHT500SmearedCoreUP = cms.Sequence(process.RA2FinalHT500SmearedCoreUP)
RA2FinalHT800SmearedCoreUP = cms.Sequence(process.RA2FinalHT800SmearedCoreUP)
RA2FinalHT1000SmearedCoreUP = cms.Sequence(process.RA2FinalHT1000SmearedCoreUP)
RA2FinalHT1200SmearedCoreUP = cms.Sequence(process.RA2FinalHT1200SmearedCoreUP)
RA2FinalHT1400SmearedCoreUP = cms.Sequence(process.RA2FinalHT1400SmearedCoreUP)

RA2FinalHT500SmearedCoreDN = cms.Sequence(process.RA2FinalHT500SmearedCoreDN)
RA2FinalHT800SmearedCoreDN = cms.Sequence(process.RA2FinalHT800SmearedCoreDN)
RA2FinalHT1000SmearedCoreDN = cms.Sequence(process.RA2FinalHT1000SmearedCoreDN)
RA2FinalHT1200SmearedCoreDN = cms.Sequence(process.RA2FinalHT1200SmearedCoreDN)
RA2FinalHT1400SmearedCoreDN = cms.Sequence(process.RA2FinalHT1400SmearedCoreDN)

RA2FinalHT500SmearedTailUP = cms.Sequence(process.RA2FinalHT500SmearedTailUP)
RA2FinalHT800SmearedTailUP = cms.Sequence(process.RA2FinalHT800SmearedTailUP)
RA2FinalHT1000SmearedTailUP = cms.Sequence(process.RA2FinalHT1000SmearedTailUP)
RA2FinalHT1200SmearedTailUP = cms.Sequence(process.RA2FinalHT1200SmearedTailUP)
RA2FinalHT1400SmearedTailUP = cms.Sequence(process.RA2FinalHT1400SmearedTailUP)

RA2FinalHT500SmearedTailDN = cms.Sequence(process.RA2FinalHT500SmearedTailDN)
RA2FinalHT800SmearedTailDN = cms.Sequence(process.RA2FinalHT800SmearedTailDN)
RA2FinalHT1000SmearedTailDN = cms.Sequence(process.RA2FinalHT1000SmearedTailDN)
RA2FinalHT1200SmearedTailDN = cms.Sequence(process.RA2FinalHT1200SmearedTailDN)
RA2FinalHT1400SmearedTailDN = cms.Sequence(process.RA2FinalHT1400SmearedTailDN)
#####

from PhysicsTools.PatAlgos.tools.helpers import massSearchReplaceAnyInputTag

massSearchReplaceAnyInputTag(RA2PreSelectionSmeared, process.RA2PreSelection.selections.selectors.JetSelection.jetTag, 'QCDfromSmearing:smearedJets')
massSearchReplaceAnyInputTag(RA2FinalHT500NoDeltaPhiSelectionSmeared, process.RA2FinalHT500NoDeltaPhiSelection.selections.selectors.JetSelection.jetTag, 'QCDfromSmearing:smearedJets')
massSearchReplaceAnyInputTag(RA2FinalHT500Smeared, process.RA2FinalHT500Selection.selections.selectors.JetSelection.jetTag, 'QCDfromSmearing:smearedJets')
massSearchReplaceAnyInputTag(RA2FinalHT800Smeared, process.RA2FinalHT800Selection.selections.selectors.JetSelection.jetTag, 'QCDfromSmearing:smearedJets')
massSearchReplaceAnyInputTag(RA2FinalHT1000Smeared, process.RA2FinalHT1000Selection.selections.selectors.JetSelection.jetTag, 'QCDfromSmearing:smearedJets')
massSearchReplaceAnyInputTag(RA2FinalHT1200Smeared, process.RA2FinalHT1200Selection.selections.selectors.JetSelection.jetTag, 'QCDfromSmearing:smearedJets')
massSearchReplaceAnyInputTag(RA2FinalHT1400Smeared, process.RA2FinalHT1400Selection.selections.selectors.JetSelection.jetTag, 'QCDfromSmearing:smearedJets')

massSearchReplaceAnyInputTag(RA2FinalHT500SmearedCoreUP, process.RA2FinalHT500Selection.selections.selectors.JetSelection.jetTag, 'QCDfromSmearingCoreUP:smearedJets')
massSearchReplaceAnyInputTag(RA2FinalHT800SmearedCoreUP, process.RA2FinalHT800Selection.selections.selectors.JetSelection.jetTag, 'QCDfromSmearingCoreUP:smearedJets')
massSearchReplaceAnyInputTag(RA2FinalHT1000SmearedCoreUP, process.RA2FinalHT1000Selection.selections.selectors.JetSelection.jetTag, 'QCDfromSmearingCoreUP:smearedJets')
massSearchReplaceAnyInputTag(RA2FinalHT1200SmearedCoreUP, process.RA2FinalHT1200Selection.selections.selectors.JetSelection.jetTag, 'QCDfromSmearingCoreUP:smearedJets')
massSearchReplaceAnyInputTag(RA2FinalHT1400SmearedCoreUP, process.RA2FinalHT1400Selection.selections.selectors.JetSelection.jetTag, 'QCDfromSmearingCoreUP:smearedJets')

massSearchReplaceAnyInputTag(RA2FinalHT500SmearedCoreDN, process.RA2FinalHT500Selection.selections.selectors.JetSelection.jetTag, 'QCDfromSmearingCoreDN:smearedJets')
massSearchReplaceAnyInputTag(RA2FinalHT800SmearedCoreDN, process.RA2FinalHT800Selection.selections.selectors.JetSelection.jetTag, 'QCDfromSmearingCoreDN:smearedJets')
massSearchReplaceAnyInputTag(RA2FinalHT1000SmearedCoreDN, process.RA2FinalHT1000Selection.selections.selectors.JetSelection.jetTag, 'QCDfromSmearingCoreDN:smearedJets')
massSearchReplaceAnyInputTag(RA2FinalHT1200SmearedCoreDN, process.RA2FinalHT1200Selection.selections.selectors.JetSelection.jetTag, 'QCDfromSmearingCoreDN:smearedJets')
massSearchReplaceAnyInputTag(RA2FinalHT1400SmearedCoreDN, process.RA2FinalHT1400Selection.selections.selectors.JetSelection.jetTag, 'QCDfromSmearingCoreDN:smearedJets')

massSearchReplaceAnyInputTag(RA2FinalHT500SmearedTailUP, process.RA2FinalHT500Selection.selections.selectors.JetSelection.jetTag, 'QCDfromSmearingTailUP:smearedJets')
massSearchReplaceAnyInputTag(RA2FinalHT800SmearedTailUP, process.RA2FinalHT800Selection.selections.selectors.JetSelection.jetTag, 'QCDfromSmearingTailUP:smearedJets')
massSearchReplaceAnyInputTag(RA2FinalHT1000SmearedTailUP, process.RA2FinalHT1000Selection.selections.selectors.JetSelection.jetTag, 'QCDfromSmearingTailUP:smearedJets')
massSearchReplaceAnyInputTag(RA2FinalHT1200SmearedTailUP, process.RA2FinalHT1200Selection.selections.selectors.JetSelection.jetTag, 'QCDfromSmearingTailUP:smearedJets')
massSearchReplaceAnyInputTag(RA2FinalHT1400SmearedTailUP, process.RA2FinalHT1400Selection.selections.selectors.JetSelection.jetTag, 'QCDfromSmearingTailUP:smearedJets')

massSearchReplaceAnyInputTag(RA2FinalHT500SmearedTailDN, process.RA2FinalHT500Selection.selections.selectors.JetSelection.jetTag, 'QCDfromSmearingTailDN:smearedJets')
massSearchReplaceAnyInputTag(RA2FinalHT800SmearedTailDN, process.RA2FinalHT800Selection.selections.selectors.JetSelection.jetTag, 'QCDfromSmearingTailDN:smearedJets')
massSearchReplaceAnyInputTag(RA2FinalHT1000SmearedTailDN, process.RA2FinalHT1000Selection.selections.selectors.JetSelection.jetTag, 'QCDfromSmearingTailDN:smearedJets')
massSearchReplaceAnyInputTag(RA2FinalHT1200SmearedTailDN, process.RA2FinalHT1200Selection.selections.selectors.JetSelection.jetTag, 'QCDfromSmearingTailDN:smearedJets')
massSearchReplaceAnyInputTag(RA2FinalHT1400SmearedTailDN, process.RA2FinalHT1400Selection.selections.selectors.JetSelection.jetTag, 'QCDfromSmearingTailDN:smearedJets')
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
process.FinalPlotsRA2FinalHT500SmearedCoreUP = process.finalPlot.clone()
process.FinalPlotsRA2FinalHT500SmearedCoreUP.selectionSequence = process.RA2FinalHT500SmearedCoreUP.selections.selectionSequence
process.FinalPlotsRA2FinalHT500SmearedCoreUP.selection = 'RA2FinalHT500SmearedCoreUP'
process.FinalPlotsRA2FinalHT500SmearedCoreDN = process.finalPlot.clone()
process.FinalPlotsRA2FinalHT500SmearedCoreDN.selectionSequence = process.RA2FinalHT500SmearedCoreDN.selections.selectionSequence
process.FinalPlotsRA2FinalHT500SmearedCoreDN.selection = 'RA2FinalHT500SmearedCoreDN'
process.FinalPlotsRA2FinalHT500SmearedTailUP = process.finalPlot.clone()
process.FinalPlotsRA2FinalHT500SmearedTailUP.selectionSequence = process.RA2FinalHT500SmearedTailUP.selections.selectionSequence
process.FinalPlotsRA2FinalHT500SmearedTailUP.selection = 'RA2FinalHT500SmearedTailUP'
process.FinalPlotsRA2FinalHT500SmearedTailDN = process.finalPlot.clone()
process.FinalPlotsRA2FinalHT500SmearedTailDN.selectionSequence = process.RA2FinalHT500SmearedTailDN.selections.selectionSequence
process.FinalPlotsRA2FinalHT500SmearedTailDN.selection = 'RA2FinalHT500SmearedTailDN'

process.FinalPlotsRA2FinalHT800Smeared = process.finalPlot.clone()
process.FinalPlotsRA2FinalHT800Smeared.selectionSequence = process.RA2FinalHT800Smeared.selections.selectionSequence
process.FinalPlotsRA2FinalHT800Smeared.selection = 'RA2FinalHT800Smeared'
process.FinalPlotsRA2FinalHT800SmearedCoreUP = process.finalPlot.clone()
process.FinalPlotsRA2FinalHT800SmearedCoreUP.selectionSequence = process.RA2FinalHT800SmearedCoreUP.selections.selectionSequence
process.FinalPlotsRA2FinalHT800SmearedCoreUP.selection = 'RA2FinalHT800SmearedCoreUP'
process.FinalPlotsRA2FinalHT800SmearedCoreDN = process.finalPlot.clone()
process.FinalPlotsRA2FinalHT800SmearedCoreDN.selectionSequence = process.RA2FinalHT800SmearedCoreDN.selections.selectionSequence
process.FinalPlotsRA2FinalHT800SmearedCoreDN.selection = 'RA2FinalHT800SmearedCoreDN'
process.FinalPlotsRA2FinalHT800SmearedTailUP = process.finalPlot.clone()
process.FinalPlotsRA2FinalHT800SmearedTailUP.selectionSequence = process.RA2FinalHT800SmearedTailUP.selections.selectionSequence
process.FinalPlotsRA2FinalHT800SmearedTailUP.selection = 'RA2FinalHT800SmearedTailUP'
process.FinalPlotsRA2FinalHT800SmearedTailDN = process.finalPlot.clone()
process.FinalPlotsRA2FinalHT800SmearedTailDN.selectionSequence = process.RA2FinalHT800SmearedTailDN.selections.selectionSequence
process.FinalPlotsRA2FinalHT800SmearedTailDN.selection = 'RA2FinalHT800SmearedTailDN'

process.FinalPlotsRA2FinalHT1000Smeared = process.finalPlot.clone()
process.FinalPlotsRA2FinalHT1000Smeared.selectionSequence = process.RA2FinalHT1000Smeared.selections.selectionSequence
process.FinalPlotsRA2FinalHT1000Smeared.selection = 'RA2FinalHT1000Smeared'
process.FinalPlotsRA2FinalHT1000SmearedCoreUP = process.finalPlot.clone()
process.FinalPlotsRA2FinalHT1000SmearedCoreUP.selectionSequence = process.RA2FinalHT1000SmearedCoreUP.selections.selectionSequence
process.FinalPlotsRA2FinalHT1000SmearedCoreUP.selection = 'RA2FinalHT1000SmearedCoreUP'
process.FinalPlotsRA2FinalHT1000SmearedCoreDN = process.finalPlot.clone()
process.FinalPlotsRA2FinalHT1000SmearedCoreDN.selectionSequence = process.RA2FinalHT1000SmearedCoreDN.selections.selectionSequence
process.FinalPlotsRA2FinalHT1000SmearedCoreDN.selection = 'RA2FinalHT1000SmearedCoreDN'
process.FinalPlotsRA2FinalHT1000SmearedTailUP = process.finalPlot.clone()
process.FinalPlotsRA2FinalHT1000SmearedTailUP.selectionSequence = process.RA2FinalHT1000SmearedTailUP.selections.selectionSequence
process.FinalPlotsRA2FinalHT1000SmearedTailUP.selection = 'RA2FinalHT1000SmearedTailUP'
process.FinalPlotsRA2FinalHT1000SmearedTailDN = process.finalPlot.clone()
process.FinalPlotsRA2FinalHT1000SmearedTailDN.selectionSequence = process.RA2FinalHT1000SmearedTailDN.selections.selectionSequence
process.FinalPlotsRA2FinalHT1000SmearedTailDN.selection = 'RA2FinalHT1000SmearedTailDN'

process.FinalPlotsRA2FinalHT1200Smeared = process.finalPlot.clone()
process.FinalPlotsRA2FinalHT1200Smeared.selectionSequence = process.RA2FinalHT1200Smeared.selections.selectionSequence
process.FinalPlotsRA2FinalHT1200Smeared.selection = 'RA2FinalHT1200Smeared'
process.FinalPlotsRA2FinalHT1200SmearedCoreUP = process.finalPlot.clone()
process.FinalPlotsRA2FinalHT1200SmearedCoreUP.selectionSequence = process.RA2FinalHT1200SmearedCoreUP.selections.selectionSequence
process.FinalPlotsRA2FinalHT1200SmearedCoreUP.selection = 'RA2FinalHT1200SmearedCoreUP'
process.FinalPlotsRA2FinalHT1200SmearedCoreDN = process.finalPlot.clone()
process.FinalPlotsRA2FinalHT1200SmearedCoreDN.selectionSequence = process.RA2FinalHT1200SmearedCoreDN.selections.selectionSequence
process.FinalPlotsRA2FinalHT1200SmearedCoreDN.selection = 'RA2FinalHT1200SmearedCoreDN'
process.FinalPlotsRA2FinalHT1200SmearedTailUP = process.finalPlot.clone()
process.FinalPlotsRA2FinalHT1200SmearedTailUP.selectionSequence = process.RA2FinalHT1200SmearedTailUP.selections.selectionSequence
process.FinalPlotsRA2FinalHT1200SmearedTailUP.selection = 'RA2FinalHT1200SmearedTailUP'
process.FinalPlotsRA2FinalHT1200SmearedTailDN = process.finalPlot.clone()
process.FinalPlotsRA2FinalHT1200SmearedTailDN.selectionSequence = process.RA2FinalHT1200SmearedTailDN.selections.selectionSequence
process.FinalPlotsRA2FinalHT1200SmearedTailDN.selection = 'RA2FinalHT1200SmearedTailDN'

process.FinalPlotsRA2FinalHT1400Smeared = process.finalPlot.clone()
process.FinalPlotsRA2FinalHT1400Smeared.selectionSequence = process.RA2FinalHT1400Smeared.selections.selectionSequence
process.FinalPlotsRA2FinalHT1400Smeared.selection = 'RA2FinalHT1400Smeared'
process.FinalPlotsRA2FinalHT1400SmearedCoreUP = process.finalPlot.clone()
process.FinalPlotsRA2FinalHT1400SmearedCoreUP.selectionSequence = process.RA2FinalHT1400SmearedCoreUP.selections.selectionSequence
process.FinalPlotsRA2FinalHT1400SmearedCoreUP.selection = 'RA2FinalHT1400SmearedCoreUP'
process.FinalPlotsRA2FinalHT1400SmearedCoreDN = process.finalPlot.clone()
process.FinalPlotsRA2FinalHT1400SmearedCoreDN.selectionSequence = process.RA2FinalHT1400SmearedCoreDN.selections.selectionSequence
process.FinalPlotsRA2FinalHT1400SmearedCoreDN.selection = 'RA2FinalHT1400SmearedCoreDN'
process.FinalPlotsRA2FinalHT1400SmearedTailUP = process.finalPlot.clone()
process.FinalPlotsRA2FinalHT1400SmearedTailUP.selectionSequence = process.RA2FinalHT1400SmearedTailUP.selections.selectionSequence
process.FinalPlotsRA2FinalHT1400SmearedTailUP.selection = 'RA2FinalHT1400SmearedTailUP'
process.FinalPlotsRA2FinalHT1400SmearedTailDN = process.finalPlot.clone()
process.FinalPlotsRA2FinalHT1400SmearedTailDN.selectionSequence = process.RA2FinalHT1400SmearedTailDN.selections.selectionSequence
process.FinalPlotsRA2FinalHT1400SmearedTailDN.selection = 'RA2FinalHT1400SmearedTailDN'
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
   #   process.htPFFilter *     # to be used for standard jets
   process.htPFchsFilter *      # to be used for chs jets 
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

process.predictionCoreUP = cms.Path(
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
	process.QCDfromSmearingCoreUP *
	process.RA2FinalHT500SmearedCoreUP *
	process.FinalPlotsRA2FinalHT500SmearedCoreUP *
	process.RA2FinalHT800SmearedCoreUP *
	process.FinalPlotsRA2FinalHT800SmearedCoreUP *
	process.RA2FinalHT1000SmearedCoreUP *
	process.FinalPlotsRA2FinalHT1000SmearedCoreUP *
	process.RA2FinalHT1200SmearedCoreUP *
	process.FinalPlotsRA2FinalHT1200SmearedCoreUP *
	process.RA2FinalHT1400SmearedCoreUP *
	process.FinalPlotsRA2FinalHT1400SmearedCoreUP
)

process.predictionCoreDN = cms.Path(
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
	process.QCDfromSmearingCoreDN *
	process.RA2FinalHT500SmearedCoreDN *
	process.FinalPlotsRA2FinalHT500SmearedCoreDN *
	process.RA2FinalHT800SmearedCoreDN *
	process.FinalPlotsRA2FinalHT800SmearedCoreDN *
	process.RA2FinalHT1000SmearedCoreDN *
	process.FinalPlotsRA2FinalHT1000SmearedCoreDN *
	process.RA2FinalHT1200SmearedCoreDN *
	process.FinalPlotsRA2FinalHT1200SmearedCoreDN *
	process.RA2FinalHT1400SmearedCoreDN *
	process.FinalPlotsRA2FinalHT1400SmearedCoreDN
)

process.predictionTailUP = cms.Path(
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
	process.QCDfromSmearingTailUP *
	process.RA2FinalHT500SmearedTailUP *
	process.FinalPlotsRA2FinalHT500SmearedTailUP *
	process.RA2FinalHT800SmearedTailUP *
	process.FinalPlotsRA2FinalHT800SmearedTailUP *
	process.RA2FinalHT1000SmearedTailUP *
	process.FinalPlotsRA2FinalHT1000SmearedTailUP *
	process.RA2FinalHT1200SmearedTailUP *
	process.FinalPlotsRA2FinalHT1200SmearedTailUP *
	process.RA2FinalHT1400SmearedTailUP *
	process.FinalPlotsRA2FinalHT1400SmearedTailUP
)

process.predictionTailDN = cms.Path(
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
	process.QCDfromSmearingTailDN *
	process.RA2FinalHT500SmearedTailDN *
	process.FinalPlotsRA2FinalHT500SmearedTailDN *
	process.RA2FinalHT800SmearedTailDN *
	process.FinalPlotsRA2FinalHT800SmearedTailDN *
	process.RA2FinalHT1000SmearedTailDN *
	process.FinalPlotsRA2FinalHT1000SmearedTailDN *
	process.RA2FinalHT1200SmearedTailDN *
	process.FinalPlotsRA2FinalHT1200SmearedTailDN *
	process.RA2FinalHT1400SmearedTailDN *
	process.FinalPlotsRA2FinalHT1400SmearedTailDN
)

