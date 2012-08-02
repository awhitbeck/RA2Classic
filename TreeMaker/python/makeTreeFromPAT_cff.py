# $Id:  $
#

import FWCore.ParameterSet.Config as cms

def makeTreeFromPAT(process,
                    outFileName,
                    useCHSJets=True,
                    NJetsMin=2,
                    HTMin=350.,
                    MHTMin=0.,
                    reportEveryEvt=10,
                    testFileName=["/store/user/kheine/HT/RA2PreSelectionOnData_Run2012A_HT_PromptReco-v1_v5/71cce229addb17644d40a607fa20b5d7/RA2SkimsOnData_99_3_TPC.root"],
                    numProcessedEvt=1000):
    
    ## --- Log output ------------------------------------------------------
    process.load("FWCore.MessageService.MessageLogger_cfi")
    process.MessageLogger.cerr = cms.untracked.PSet(
        placeholder = cms.untracked.bool(True)
        )
    process.MessageLogger.statistics.append('cout')
    process.MessageLogger.cout = cms.untracked.PSet(
        INFO = cms.untracked.PSet(reportEvery = cms.untracked.int32(reportEveryEvt))
        )


    ## --- Files to process ------------------------------------------------
    process.maxEvents = cms.untracked.PSet(
        input = cms.untracked.int32(numProcessedEvt)
        )
    process.source = cms.Source(
        "PoolSource",
        fileNames = cms.untracked.vstring(testFileName)
        )
        
        
    ## --- Output file -----------------------------------------------------
    process.TFileService = cms.Service(
        "TFileService",
        fileName = cms.string(outFileName+".root")
        )
    

    ## --- Selection sequences ---------------------------------------------

    # Filter-related selection
    process.load('RA2Classic.TreeMaker.filterSelection_cff')
    process.load('SandBox.Skims.RA2Leptons_cff')

    process.CleaningSelection = cms.Sequence(
        process.filterSelection *
        process.ra2PFMuonVeto *
        process.ra2ElectronVeto
        )

    # Jet-related selection
    jetInputCol = "patJetsAK5PF"
    if useCHSJets:
        jetInputCol = "patJetsPF"

    from RA2Classic.TreeMaker.patjetcollectionsubsetproducer_cfi import patJetCollectionSubsetProducer
    # Create collection of jets with pt > 30 (for MHT)
    process.MHTJets = patJetCollectionSubsetProducer.clone(
        Jets   = cms.InputTag(jetInputCol),
        PtMin  = cms.double(30.),
        EtaMax = cms.double(99999.)
        )
    # Create collection of jets with pt > 50 and eta < 2.5 (for NJet, HT)
    process.HTJets = patJetCollectionSubsetProducer.clone(
        Jets   = cms.InputTag(jetInputCol),
        PtMin  = cms.double(50.),
        EtaMax = cms.double(2.5)
        )

    from PhysicsTools.PatAlgos.selectionLayer1.jetCountFilter_cfi import countPatJets
    # Select events with at least 'NJetsMin' of the above jets
    process.NumJetsFilter = countPatJets.clone(
        src       = cms.InputTag('HTJets'),
        minNumber = cms.uint32(NJetsMin)
        )
    
    process.NumJetSelection = cms.Sequence(
        process.MHTJets *
        process.HTJets *
        process.NumJetsFilter
        )

    # HT selection
    htInputCol = 'htPF'
    if useCHSJets:
        htInputCol = 'htPFchs'

    from SandBox.Skims.RA2HT_cff import htPFFilter
    process.HTSelection = htPFFilter.clone(
        HTSource = cms.InputTag(htInputCol),
        MinHT = cms.double(HTMin)
        )

    # MHT selection
    mhtMin = 0.
    mhtInputCol = 'mhtPF'
    if useCHSJets:
        mhtInputCol = 'mhtPFchs'

    from SandBox.Skims.RA2MHT_cff import mhtPFFilter
    process.MHTSelection = mhtPFFilter.clone(
        MHTSource = cms.InputTag(mhtInputCol),
        MinMHT = cms.double(MHTMin)
        )


    ## --- Setup of TreeMaker ----------------------------------------------
    from RA2Classic.TreeMaker.treemaker_cfi import TreeMaker
    process.RA2TreeMaker = TreeMaker.clone(
        TreeName         = cms.string("RA2PreSelection"),
        VertexCollection = cms.InputTag('goodVertices'),
        HT               = cms.InputTag(htInputCol),
        HTJets           = cms.InputTag('HTJets'),
        MHT              = cms.InputTag(mhtInputCol),
        MHTJets          = cms.InputTag('MHTJets')
        )

        
    ## --- Final paths ----------------------------------------------------
    process.WriteTree = cms.Path(
        process.CleaningSelection *
        process.NumJetSelection *
        process.HTSelection *
        process.MHTSelection *
        process.RA2TreeMaker
        )
