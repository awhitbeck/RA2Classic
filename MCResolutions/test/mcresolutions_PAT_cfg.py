#
#  SUSY-PAT configuration file adapted for RA2 workflow
#
#  PAT configuration for the SUSY group - 52X series
#  More information here:
#  https://twiki.cern.ch/twiki/bin/view/CMS/SusyPatLayer1DefV12
#

# Starting with a skeleton process which gets imported with the following line
from PhysicsTools.PatAlgos.patTemplate_cfg import *

runningOnMC = True 
#runningOnMC = False

#-- Message Logger ------------------------------------------------------------
process.MessageLogger.categories.append('PATSummaryTables')
process.MessageLogger.cerr.PATSummaryTables = cms.untracked.PSet(
    limit = cms.untracked.int32(10),
    reportEvery = cms.untracked.int32(1)
    )
process.MessageLogger.cerr.FwkReport.reportEvery = 100


#-- Input Source --------------------------------------------------------------
process.maxEvents.input = 100

# Due to problem in production of LM samples: same event number appears multiple times
process.source.duplicateCheckMode = cms.untracked.string('noDuplicateCheck')

############################# START SUSYPAT specifics ####################################
from PhysicsTools.Configuration.SUSY_pattuple_cff import addDefaultSUSYPAT, getSUSY_pattuple_outputCommands

hltMenu = 'HLT'

theJetColls = ['AK5PF']

jetMetCorr = ['L1FastJet', 'L2Relative', 'L3Absolute']
if runningOnMC == False: jetMetCorr.append('L2L3Residual')  

process.GlobalTag.globaltag = "START52_V11C::All"
if runningOnMC == False:
    process.GlobalTag.globaltag = "GR_R_52_V9D::All"

process.source = cms.Source("PoolSource",
   fileNames = cms.untracked.vstring('/store/mc/Summer12/QCD_Pt-15to3000_TuneZ2_Flat_8TeV_pythia6/AODSIM/PU_S7_START52_V9-v1/0000/2C5FB809-F697-E111-87BB-0025901D4AF0.root')
)
if runningOnMC == False:
    process.source = cms.Source("PoolSource",
     fileNames = cms.untracked.vstring('/store/data/Run2012B/HTMHT/AOD/PromptReco-v1/000/194/052/9A12DE52-699E-E111-BC9F-5404A638869E.root')
    )

# Due to problem in production of LM samples: same event number appears multiple times
process.source.duplicateCheckMode = cms.untracked.string('noDuplicateCheck')

addDefaultSUSYPAT(process,mcInfo=runningOnMC,HLTMenu=hltMenu,jetMetCorrections=jetMetCorr,mcVersion='',theJetNames=theJetColls, doSusyTopProjection=False)

# Remove the PAT cleaning and filtering sequences
process.patDefaultSequence.remove(process.selectedPatCandidates)
process.patDefaultSequence.remove(process.cleanPatCandidates)
process.patDefaultSequence.remove(process.countPatCandidates)

# Disable embedment so that lepton cleaning method works
process.patJetsAK5PF.embedCaloTowers = False
process.patJetsAK5PF.embedPFCandidates = False
process.patJetsPF.embedCaloTowers = False
process.patJetsPF.embedPFCandidates = False

#-- Adjust collections to use PFNoPU jets -------------------------------------
    
# do not use Z-mass window for PU subtraction
# such that JEC works properly
process.pfPileUpPF.checkClosestZVertex = cms.bool(False)

# do not remove muons and electrons from the jet clustering input
process.pfIsolatedElectronsPF.isolationCut = -1.0
process.pfIsolatedMuonsPF.isolationCut = -1.0

# do not remove taus from the jet collection
process.pfTausPF.discriminators = cms.VPSet()
process.pfUnclusteredTausPF = process.pfTausPF.clone(
    cut = cms.string("pt < 0")
    )
process.pfTauSequencePF.replace(process.pfTausPF, process.pfTausPF+ process.pfUnclusteredTausPF)
process.pfNoTauPF.topCollection = "pfUnclusteredTausPF"

# make loose clones of the original electron collection
process.pfRelaxedElectronsPF = process.pfIsolatedElectronsPF.clone()
process.pfRelaxedElectronsPF.isolationCut = 9999.0
process.pfElectronsFromVertexPF.dzCut = 9999.0
process.pfElectronsFromVertexPF.d0Cut = 9999.0
process.pfSelectedElectronsPF.cut = ""
process.patElectronsPF.pfElectronSource  = "pfRelaxedElectronsPF"
process.pfElectronSequencePF.replace(process.pfIsolatedElectronsPF,
                                     process.pfIsolatedElectronsPF +
                                     process.pfRelaxedElectronsPF)

# make loose clones of the original muon collection
process.pfRelaxedMuonsPF = process.pfIsolatedMuonsPF.clone()
process.pfRelaxedMuonsPF.isolationCut = 9999.0
process.pfMuonsFromVertexPF.dzCut = 9999.0
process.pfMuonsFromVertexPF.d0Cut = 9999.0
process.pfSelectedMuonsPF.cut = ""
process.patMuonsPF.pfMuonSource  = "pfRelaxedMuonsPF"
process.pfMuonSequencePF.replace(process.pfIsolatedMuonsPF,
                                 process.pfIsolatedMuonsPF +
                                 process.pfRelaxedMuonsPF)



#------------------------------------------------------------------------------

#SUSY_pattuple_outputCommands = getSUSY_pattuple_outputCommands( process )

# overwrite default output content
from SandBox.Skims.RA2Content_cff import getRA2PATOutput
process.out.outputCommands = getRA2PATOutput(process)
process.out.dropMetaData = cms.untracked.string('DROPPED')
############################## END SUSYPAT specifics ####################################

#-- HLT selection ------------------------------------------------------------
import HLTrigger.HLTfilters.hltHighLevel_cfi as hlt
hltSelection=''
#if options.hltSelection:
if hltSelection:
    process.hltFilter = hlt.hltHighLevel.clone(
        HLTPaths = cms.vstring(hltSelection),
        TriggerResultsTag = cms.InputTag("TriggerResults","",hltMenu),
        throw = False
    )
    process.susyPatDefaultSequence.replace(process.eventCountProducer, process.eventCountProducer * process.hltFilter)


#-- check RA2 recipe here ------------------------------------------------------------
process.prefilterCounter        = cms.EDProducer("EventCountProducer")
process.postStdCleaningCounter  = cms.EDProducer("EventCountProducer")

#-- Output module configuration -----------------------------------------------
process.load('SandBox.Skims.RA2Objects_cff')
process.load('SandBox.Skims.RA2Selection_cff')
process.load('SandBox.Skims.RA2Cleaning_cff')

## please comment this block to remove tagging mode of
##filters and reject events failing any of following filters
#process.eeNoiseFilter.taggingMode         = True
#process.trackingFailureFilter.taggingMode = True
#process.beamHaloFilter.taggingMode        = True
#process.ra2NoiseCleaning.remove(process.HBHENoiseFilter)
#process.inconsistentMuons.taggingMode     = True
#process.greedyMuons.taggingMode           = True
#process.ra2EcalTPFilter.taggingMode       = True
#process.ra2EcalBEFilter.taggingMode       = True
#process.hcalLaserEventFilter.taggingMode  = True
#process.eeBadScFilter.taggingMode         = True

process.load("SandBox.Skims.provInfoMuons_cfi")
process.load("SandBox.Skims.provInfoElectrons_cfi")

###############################################################################
process.load("RA2Classic.MCResolutions.mcresolutions_cfi")
process.MCResolutions.jetTag = 'patJetsPF' #Without CHS: patJetsAK5PF. With CHS: patJetsPF

process.MCResolutions = process.MCResolutions.clone()
process.MCResolutions.fileName = 'MCJetResolution_MadGraph1000ToInf_withCHS_withoutPUReweighting.root'
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
process.load("RA2Classic.WeightProducer.weightProducer_cfi")
process.weightProducer.weightName       = 'weight'

## QCD_Pt-15to3000_TuneZ2_Flat_8TeV_pythia6
#process.weightProducer.Method          = 'PtHat'
#process.weightProducer.Exponent        = -4.5
#process.weightProducer.XS              = 2.99913994e+10
#process.weightProducer.NumberEvts      = 9998154
#process.weightProducer.Lumi            = 1000
#process.weightProducer.weight          = -1.0

## MadGraph 
process.weightProducer.Method           = 'Constant'
process.weightProducer.Lumi             = 1000
#process.weightProducer.NumberEvts       = 27057349 #250To500
#process.weightProducer.XS               = 276000.0
#process.weightProducer.NumberEvts      = 32255694 #500To1000
#process.weightProducer.XS               = 8426.0
process.weightProducer.NumberEvts      = 13879218 #1000ToInf
process.weightProducer.XS               = 204.0

process.weightProducer.FileNamePUDataDistribution = 'NONE'
#process.weightProducer.FileNamePUDataDistribution = 'RA2Classic/AdditionalInputFiles/DataPileupHistogram_RA2Summer12_190456-196531_8TeV_PromptReco_WOLowPU.root'
process.weightProducer.PU = 2 # 0==Flat10, 1==Fall11, 2==Summer12
###############################################################################

###############################################################################
#-- process.outpath is set in PhysicsTools.PatAlgos.patTemplate_cfg
#-- No EDM-output file
del process.outpath
#del process.ppf
###############################################################################

# an example sequence to create skimmed susypat-tuples
process.cleanpatseq = cms.Sequence(
                      process.susyPatDefaultSequence *
                      #process.prefilterCounter *
                      process.ra2StdCleaning *
                      #process.postStdCleaningCounter *
                      process.ra2Objects * process.provInfoMuons * process.provInfoElectrons *
                      process.ra2PostCleaning 
                      #process.ra2FullPFchsSelectionNoMHT 
                      #process.mhtchsPFFilter
                      )

process.p = cms.Path(
	process.cleanpatseq *
	process.weightProducer *
	process.MCResolutions
)

file=open("mcresolutions_PAT_resolved.py","w")
file.write(str(process.dumpPython()))
file.close()
