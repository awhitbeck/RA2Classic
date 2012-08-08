#  $ Id: $
#
# --- Configuration file for RA2 skims from AOD ---------------------------------
#
# For MC
#

import FWCore.ParameterSet.Config as cms


#-- Run the process -------------------------------------------------------------
from PhysicsTools.PatAlgos.patTemplate_cfg import *
from RA2.Configuration.Preselection_cff import runRA2Preselection
runRA2Preselection(process,globalTag="START52_V11C::All",isData=False,reportEveryEvt=5000)


process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(False))

###############################################################################
process.source = cms.Source("PoolSource",
	fileNames = cms.untracked.vstring(
        '/store/mc/Summer12/QCD_Pt-15to3000_TuneZ2_Flat_8TeV_pythia6/AODSIM/PU_S7_START52_V9-v1/0000/2C5FB809-F697-E111-87BB-0025901D4AF0.root'
    )
)
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32( 100 ) )
###############################################################################

###############################################################################
process.load("RA2Classic.MCResolutions.mcresolutions_cfi")
process.MCResolutions.jetTag = 'patJetsAK5PF' #Without CHS: patJetsAK5PF. With CHS: patJetsPF

process.MCResolutions = process.MCResolutions.clone()
process.MCResolutions.fileName = 'MCJetResolution_Pythia_withoutCHS_withPUReweighting.root'
###############################################################################

###############################################################################
# Jet parton matching
#process.load("PhysicsTools.PatAlgos.mcMatchLayer0.jetFlavourId_cff")
#process.patJetPartonAssociation.jets = cms.InputTag("patJetsPF")
process.patJetPartonAssociation.coneSizeToAssociate = 0.5
###############################################################################

###############################################################################
# Weight producer
###############################################################################
process.load("RA2.WeightProducer.weightProducer_cfi")
process.weightProducer.weightName	= 'weight'
process.weightProducer.Method		= 'PtHat'
process.weightProducer.Exponent		= -4.5
process.weightProducer.XS		= 2.99913994e+10
process.weightProducer.NumberEvts	= 9998154
process.weightProducer.Lumi		= 1000
process.weightProducer.weight		= -1.0

#process.weightProducer.FileNamePUDataDistribution = 'NONE'
process.weightProducer.FileNamePUDataDistribution = 'RA2Classic/AdditionalInputFiles/DataPileupHistogram_RA2Summer12_190456-196531_8TeV_PromptReco_WOLowPU.root'
process.weightProducer.PU = 2 # 0==Flat10, 1==Fall11, 2==Summer12
###############################################################################

###############################################################################
#-- process.outpath is set in PhysicsTools.PatAlgos.patTemplate_cfg
#-- No EDM-output file
del process.outpath
del process.ppf
###############################################################################

process.dump   = cms.EDAnalyzer("EventContentAnalyzer")

process.p = cms.Path(
	process.cleanpatseq *
	process.weightProducer *
	process.MCResolutions
)

file=open("mcresolutions_PAT_resolved.py","w")
file.write(str(process.dumpPython()))
file.close()
