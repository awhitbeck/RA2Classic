# $Id: makeTree_cfg.py,v 1.3 2012/12/28 18:27:04 mschrode Exp $


###############################################################################
##
## GLOBAL PARAMETERS
##
###############################################################################

numProcessedEvt = 100
reportEveryEvt  = 1
globalTag       = 'START53_V15::All'
smsModel        = "T1tttt"
smsMotherMass   = 1000
smsLSPMass      = 400
xs              = 0.000435488
numEvtsInSample = 49994
lumi            = 5088



###############################################################################
##
## GENERAL SETUP
##
###############################################################################

import FWCore.ParameterSet.Config as cms

process = cms.Process("RA2SignalNtupleMaker")

from PhysicsTools.PatAlgos.patTemplate_cfg import *
process.outpath.remove(process.out)


#-- Meta data to be logged in DBS ---------------------------------------------
process.configurationMetadata = cms.untracked.PSet(
    version = cms.untracked.string('$Revision: 1.3 $'),
    name = cms.untracked.string('$Source: /local/reps/CMSSW/UserCode/kheine/RA2Classic/SUSYParams/test/makeTree_cfg.py,v $'),
    annotation = cms.untracked.string('SUSY pattuple definition')
    )


#-- Message Logger ------------------------------------------------------------
process.MessageLogger.categories.append('PATSummaryTables')
process.MessageLogger.cerr.PATSummaryTables = cms.untracked.PSet(
    limit = cms.untracked.int32(-1),
    reportEvery = cms.untracked.int32(1)
    )
process.MessageLogger.cerr.FwkReport.reportEvery = reportEveryEvt


#-- Input Source --------------------------------------------------------------
process.maxEvents.input = numProcessedEvt
process.source.duplicateCheckMode = cms.untracked.string('noDuplicateCheck')
process.source = cms.Source(
    "PoolSource",
    fileNames = cms.untracked.vstring('/store/mc/Summer12_DR53X/TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/FADE7E47-CDE1-E111-8069-003048D4610C.root')
    )



###############################################################################
##
## SUSY PAT FOR RA2
##
###############################################################################

#-- SUSYPAT specifics ---------------------------------------------------------
from PhysicsTools.Configuration.SUSY_pattuple_cff import addDefaultSUSYPAT, getSUSY_pattuple_outputCommands
process.GlobalTag.globaltag = globalTag

addDefaultSUSYPAT(process,
                  mcInfo=True,
                  HLTMenu='Redigi',
                  jetMetCorrections=['L1FastJet', 'L2Relative', 'L3Absolute'],
                  mcVersion='',
                  theJetNames=['AK5PF'],
                  doSusyTopProjection=False
                  )

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
# (patMuons and patElectrons use relaxed pfMuon and pfElectron collections)
process.pfIsolatedElectronsPF.isolationCut = -1
process.pfIsolatedMuonsPF.isolationCut = -1

# make loose clones of the original electron collection
process.pfRelaxedElectronsPF = process.pfIsolatedElectronsPF.clone()
process.pfRelaxedElectronsPF.isolationCut = 9999
process.pfElectronsFromVertexPF.dzCut = 9999.0
process.pfElectronsFromVertexPF.d0Cut = 9999.0
process.pfSelectedElectronsPF.cut = ""
process.patElectronsPF.pfElectronSource  = "pfRelaxedElectronsPF"
process.pfElectronSequencePF.replace(process.pfIsolatedElectronsPF,
                                     process.pfIsolatedElectronsPF + 
                                     process.pfRelaxedElectronsPF)

# make loose clones of the original muon collection
process.pfRelaxedMuonsPF = process.pfIsolatedMuonsPF.clone()
process.pfRelaxedMuonsPF.isolationCut = 9999
process.pfMuonsFromVertexPF.dzCut = 9999.0
process.pfMuonsFromVertexPF.d0Cut = 9999.0
process.pfSelectedMuonsPF.cut = ""
process.patMuonsPF.pfMuonSource  = "pfRelaxedMuonsPF"
process.pfMuonSequencePF.replace(process.pfIsolatedMuonsPF,
                                 process.pfIsolatedMuonsPF + 
                                 process.pfRelaxedMuonsPF)
    

# do not remove taus from the jet collection
process.pfTausPF.discriminators = cms.VPSet()
process.pfUnclusteredTausPF = process.pfTausPF.clone(
    cut = cms.string("pt < 0")
    )
process.pfTauSequencePF.replace(process.pfTausPF, process.pfTausPF+ process.pfUnclusteredTausPF)
process.pfNoTauPF.topCollection = "pfUnclusteredTausPF"
#------------------------------------------------------------------------------

#-- Overwrite default output content ------------------------------------------
from SandBox.Skims.RA2Content_cff import getRA2PATOutput
process.out.outputCommands = getRA2PATOutput(process)
process.out.dropMetaData = cms.untracked.string('DROPPED')




###############################################################################
##
## FILTERS
##
###############################################################################

#-- RA2 filtering -------------------------------------------------------------
process.load('SandBox.Skims.RA2Objects_cff')
process.load('SandBox.Skims.RA2Selection_cff')
process.load('SandBox.Skims.RA2Cleaning_cff')

## # Adjust object filters for signal-scan values
## process.htPFchsFilter.MinHT               = cms.double(300.0)
## process.mhtPFchsFilter.MinMHT             = cms.double(100.0)
## process.countJetsPFchsPt50Eta25.minNumber = cms.uint32(2)

process.ra2NoiseCleaning.remove(process.HBHENoiseFilter)
process.ra2NoiseCleaning.remove(process.HBHENoiseFilterRA2)
process.ra2NoiseCleaning.remove(process.beamHaloFilter)  # No 'reco::BeamHaloSummary' in SMS datasets

process.eeNoiseFilter.taggingMode         = True
process.trackingFailureFilter.taggingMode = True
process.inconsistentMuons.taggingMode     = True
process.greedyMuons.taggingMode           = True
process.ra2EcalTPFilter.taggingMode       = True
process.ra2EcalBEFilter.taggingMode       = True
process.hcalLaserEventFilter.taggingMode  = True
process.ecalLaserCorrFilter.taggingMode   = True
process.eeBadScFilter.taggingMode         = True

from RecoMET.METFilters.jetIDFailureFilter_cfi import jetIDFailure
process.PBNRFilter = jetIDFailure.clone(
    JetSource = cms.InputTag('patJetsPFchsPt30'),
    MinJetPt      = cms.double(30.0),
    taggingMode   = cms.bool(True)
    )
process.ra2NoiseCleaning += process.PBNRFilter

process.load("SandBox.Skims.provInfoMuons_cfi")
process.load("SandBox.Skims.provInfoElectrons_cfi")

process.cleanpatseq = cms.Sequence(
    process.susyPatDefaultSequence *
    process.ra2StdCleaning *
    process.ra2Objects *
    process.provInfoMuons *
    process.provInfoElectrons *
    process.ra2PostCleaning
    )

## --- SMS Model Filter ------------------------------------------------
# Filter files for specified signal point out of dataset
# Code from UserCode/seema/SusyAnalysis/AnalysisUtils
from SusyAnalysis.AnalysisUtils.smsModelFilter_cfi import smsModelFilter
process.SMSModelFilter = smsModelFilter.clone(
    SusyScanTopology   = cms.string(smsModel),
    SusyScanMotherMass = cms.double(smsMotherMass),
    SusyScanLSPMass    = cms.double(smsLSPMass),
    SusyScanFracLSP    = cms.double(0.0)
    )



###############################################################################
##
## WEIGHT PRODUCER
##
###############################################################################

## --- Setup WeightProducer --------------------------------------------
from RA2Classic.WeightProducer.weightProducer_cfi import weightProducer
process.WeightProducer = weightProducer.clone(
    weight     = cms.double(-1.0),
    Method     = cms.string("Constant"),
    XS         = cms.double(xs),
    NumberEvts = cms.double(numEvtsInSample),
    Lumi       = cms.double(lumi),
    LumiScale  = cms.double(1.0),
    FileNamePUDataDistribution = cms.string("NONE"),
    PU         = cms.int32(0)
    )



###############################################################################
##
## EVENT INFO
##
###############################################################################

## --- Pile-Up Info ----------------------------------------------------
from RA2Classic.SUSYParams.puInfo_cfi import PUInfo
process.PUInfo = PUInfo.clone()


## --- PDF Uncertainties -----------------------------------------------
#---JL
#--for PDF sys:
##   cvs co -rV00-04-01 ElectroWeakAnalysis/Utilities
##   scram setup lhapdffull
##   touch $CMSSW_BASE/src/ElectroWeakAnalysis/Utilities/BuildFile.xml
process.pdfWeight = cms.EDProducer(
    "PdfWeightProducer",
    PdfInfoTag = cms.untracked.InputTag("generator"),
    PdfSetNames = cms.untracked.vstring("cteq66.LHgrid","MSTW2008nlo68cl.LHgrid","NNPDF20_100.LHgrid")
    #PdfSetNames = cms.untracked.vstring("NNPDF20_100.LHgrid")
    )
#---for ISR sys
##   cvs co -d UserCode/HistoWeightProducer UserCode/Mrenna/UserCode/HistoWeightProducer
##   cvs co -d UserCode/RA2IsrFsr UserCode/Mrenna/UserCode/RA2IsrFsr
##   cvs co -d UserCode/MyCompositeProducers UserCode/Mrenna/UserCode/MyCompositeProducers
process.lastParticles = cms.EDProducer("ISRProducer")
process.ISRsys = cms.Sequence(process.lastParticles)

#---put the susy params
process.load("RA2Classic.SUSYParams.susyparams_cfi")
process.susyparams.Model = cms.string(smsModel)
#-- end JL



###############################################################################
##
## JET-RELATED INFO
##
###############################################################################


## --- Jets ------------------------------------------------------------

# Store collection with some lose pt cut to be able to
# adjust to JEC/JER changes
process.load('JetMETCorrections.Configuration.DefaultJEC_cff')
from RA2Classic.Utils.patJetCollectionSubsetProducer_cfi import patJetCollectionSubsetProducer
process.patJetsPFchs = patJetCollectionSubsetProducer.clone(
    Jets   = cms.InputTag('patJetsPF'),
    PtMin        = cms.double(10.)
    )
process.genJets = patJetCollectionSubsetProducer.clone(
    Jets   = cms.InputTag('ak5GenJets'),
    PtMin        = cms.double(10.)
    )

# For hadronic tau
process.caloJets = patJetCollectionSubsetProducer.clone(
    Jets   = cms.InputTag('ak5CaloJetsL2L3'),
    PtMin        = cms.double(10.)
    )


## --- Additional jet-related Info -------------------------------------
## Store info are
## - Area for L1 corrections
## - Neutral energy fractions for PBNR filter
## Requires in addition the jet 4-vectors
from RA2Classic.SUSYParams.additionalJetInfo_cfi import AdditionalJetInfo
process.AdditionalJetInfo = AdditionalJetInfo.clone(
    JetSource = cms.InputTag('patJetsPFchs')
    )


## --- JES / JER Uncertainties -----------------------------------------
# Create jet collections with JES varied by +/- JEC uncertainty
from RA2Classic.Utils.jesUncertaintyVariation_cfi import jesUncertaintyVariation
process.patJetsPFJESUp = jesUncertaintyVariation.clone(
    Jets       = cms.InputTag('patJetsPF'),
    METs       = cms.InputTag('patMETsPF'),
    JetTypeId  = cms.string('AK5PFchs'),
    Variation  = cms.string('Up')
    )
process.patJetsPFJESDn = process.patJetsPFJESUp.clone(
    Variation  = cms.string('Dn')
    )

# Create RA2 jets from varied jets and recompute HT, MHT
process.patJetsPFchsPt30JESUp = process.patJetsPFchsPt30.clone(
    src = cms.InputTag('patJetsPFJESUp:Jets')
    )
process.patJetsPFchsPt50Eta25JESUp = process.patJetsPFchsPt50Eta25.clone(
    src = cms.InputTag('patJetsPFchsPt30JESUp')
    )
process.patJetsPFchsPt30JESDn = process.patJetsPFchsPt30.clone(
    src = cms.InputTag('patJetsPFJESDn:Jets')
    )
process.patJetsPFchsPt50Eta25JESDn = process.patJetsPFchsPt50Eta25.clone(
    src = cms.InputTag('patJetsPFchsPt30JESDn')
    )

# Recompute HT, MHT with varied JES
process.htPFchsJESUp = process.htPFchs.clone(
    JetCollection = cms.InputTag('patJetsPFchsPt50Eta25JESUp')
    )
process.mhtPFchsJESUp = process.mhtPFchs.clone(
    JetCollection = cms.InputTag('patJetsPFchsPt30JESUp')
    )
process.htPFchsJESDn = process.htPFchs.clone(
    JetCollection = cms.InputTag('patJetsPFchsPt50Eta25JESDn')
    )
process.mhtPFchsJESDn = process.mhtPFchs.clone(
    JetCollection = cms.InputTag('patJetsPFchsPt30JESDn')
    )

process.varyJES = cms.Sequence(
    process.patJetsPFJESDn *
    process.patJetsPFJESUp *
    process.patJetsPFchsPt30JESUp *
    process.patJetsPFchsPt50Eta25JESUp *
    process.patJetsPFchsPt30JESDn *
    process.patJetsPFchsPt50Eta25JESDn *
    process.htPFchsJESUp *
    process.mhtPFchsJESUp *
    process.htPFchsJESDn *
    process.mhtPFchsJESDn
    )



###############################################################################
##
## TREE-MAKER SETUP
##
###############################################################################

## --- Setup of TreeMaker ----------------------------------------------
process.TFileService = cms.Service(
    "TFileService",
    fileName = cms.string("RA2Selection.root")
    )

# The nominal tree
from RA2Classic.TreeMaker.treemaker_cfi import TreeMaker
process.RA2TreeMaker = TreeMaker.clone(
    TreeName          = cms.string("RA2PreSelection"),
    VertexCollection  = cms.InputTag('goodVertices'),
    HT                = cms.InputTag('htPFchs'),
    HTJets            = cms.InputTag('patJetsPFchsPt50Eta25'),
    MHT               = cms.InputTag('mhtPFchs'),
    MHTJets           = cms.InputTag('patJetsPFchsPt30'),
    Filters           = cms.VInputTag(cms.InputTag('eeNoiseFilter'),
                                      cms.InputTag('trackingFailureFilter'),
                                      cms.InputTag('inconsistentMuons'),
                                      cms.InputTag('greedyMuons'),
                                      cms.InputTag('ra2EcalTPFilter'),
                                      cms.InputTag('ra2EcalBEFilter'),
                                      cms.InputTag('hcalLaserEventFilter'),
                                      cms.InputTag('ecalLaserCorrFilter'),
                                      cms.InputTag('eeBadScFilter'),
                                      cms.InputTag('PBNRFilter')
                                      ),
    VarsDouble        = cms.VInputTag(cms.InputTag('WeightProducer:weight'),
                                      cms.InputTag('PUInfo:Num'),
                                      cms.InputTag('kt6PFJets:rho'),
                                      cms.InputTag('susyparams:m0'),
                                      cms.InputTag('susyparams:m12'),
                                      cms.InputTag('susyparams:evtProcID')
                                      ),
    VarsDoubleNamesInTree = cms.vstring('Weight',
                                        'NumPUInteractions',
                                        'rho',
                                        'massMom',
                                        'massDau',
                                        'procID'
                                        ),
    CandidateCollections  = cms.VInputTag('patJetsPFchs',
                                          'genJets',
                                          'caloJets',
                                          'patMuonsPFIDIso',
                                          'patElectronsIDIso',
                                          'patMETsPF'
                                          ),
    CandidateNamesInTree  = cms.vstring('Jets',
                                        'GenJets',
                                        'CaloJetsRaw',
                                        'PATMuonsPFIDIso',
                                        'PATElectronsIDIso',
                                        'PATMETsPF'
                                        ),
    VarsDoubleV = cms.VInputTag('AdditionalJetInfo:Area',
                                'AdditionalJetInfo:NeutHadF',
                                'AdditionalJetInfo:NeutEmF',
                                "pdfWeight:cteq66",
                                "pdfWeight:MSTW2008nlo68cl",
                                "pdfWeight:NNPDF20"
                                ),
    VarsDoubleNamesInTreeV = cms.vstring('JetArea',
                                         'JetNeutHadF',
                                         'JetNeutEmF',
                                         "cteq66",
                                         "MSTW2008nlo68cl",
                                         "NNPDF20"
                                       )
    )

# Trees with varied JES (reduced content!)
process.RA2TreeMakerJESUp = TreeMaker.clone(
    TreeName          = cms.string("RA2PreSelectionJESUp"),
    VertexCollection  = cms.InputTag('goodVertices'),
    HT                = cms.InputTag('htPFchsJESUp'),
    HTJets            = cms.InputTag('patJetsPFchsPt50Eta25JESUp'),
    MHT               = cms.InputTag('mhtPFchsJESUp'),
    MHTJets           = cms.InputTag('patJetsPFchsPt30JESUp'),
    VarsDouble        = cms.VInputTag(cms.InputTag('WeightProducer:weight'),
                                      cms.InputTag('PUInfo:Num'),
                                      cms.InputTag('susyparams:m0'),
                                      cms.InputTag('susyparams:m12'),
                                      cms.InputTag('susyparams:evtProcID')
                                      ),
    VarsDoubleNamesInTree = cms.vstring('Weight',
                                        'NumPUInteractions',
                                        'massMom',
                                        'massDau',
                                        'procID'
                                        )
    )

process.RA2TreeMakerJESDn = TreeMaker.clone(
    TreeName          = cms.string("RA2PreSelectionJESDn"),
    VertexCollection  = cms.InputTag('goodVertices'),
    HT                = cms.InputTag('htPFchsJESDn'),
    HTJets            = cms.InputTag('patJetsPFchsPt50Eta25JESDn'),
    MHT               = cms.InputTag('mhtPFchsJESDn'),
    MHTJets           = cms.InputTag('patJetsPFchsPt30JESDn'),
    VarsDouble        = cms.VInputTag(cms.InputTag('WeightProducer:weight'),
                                      cms.InputTag('PUInfo:Num'),
                                      cms.InputTag('susyparams:m0'),
                                      cms.InputTag('susyparams:m12'),
                                      cms.InputTag('susyparams:evtProcID')
                                      ),
    VarsDoubleNamesInTree = cms.vstring('Weight',
                                        'NumPUInteractions',
                                        'massMom',
                                        'massDau',
                                        'procID'
                                        )
    )




###############################################################################
##
## PATH
##
###############################################################################

process.dump   = cms.EDAnalyzer("EventContentAnalyzer")

process.writeTree = cms.Path(
    process.SMSModelFilter *
    process.cleanpatseq *
    process.patJetsPFchs *
    process.genJets *
    process.ak5CaloJetsL2L3 * process.caloJets *
    process.varyJES *
    process.AdditionalJetInfo *
    process.WeightProducer *
    process.PUInfo *
    process.pdfWeight*
    process.ISRsys*
    process.susyparams*
#  process.dump *
    process.RA2TreeMaker *
    process.RA2TreeMakerJESUp *
    process.RA2TreeMakerJESDn
    )

process.schedule = cms.Schedule(process.writeTree)
    
   
