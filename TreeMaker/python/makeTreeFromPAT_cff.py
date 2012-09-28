# $Id: makeTreeFromPAT_cff.py,v 1.8 2012/09/19 14:44:08 mschrode Exp $
#

import FWCore.ParameterSet.Config as cms

def makeTreeFromPAT(process,
                    outFileName,
                    useCHSJets=True,
                    NJetsMin=2,
                    HTMin=350.,
                    MHTMin=0.,
                    reportEveryEvt=10,
                    testFileName="",
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
        process.filterSelection
        )
    process.LeptonVeto = cms.Sequence(
        process.ra2PFMuonVeto *
        process.ra2ElectronVeto
        )

    # Produce RA2 jets (produces the collections HTJets and MHTJets)
    if useCHSJets:
        process.load('RA2Classic.Utils.produceRA2JetsPFCHS_cff')
        process.ProduceRA2Jets = cms.Sequence(
            process.produceRA2JetsPFCHS
            )
    else:
        process.load('RA2Classic.Utils.produceRA2JetsAK5PF_cff')
        process.ProduceRA2Jets = cms.Sequence(
            process.produceRA2JetsAK5PF
            )

    # Select events with at least 'NJetsMin' of the above jets
    from PhysicsTools.PatAlgos.selectionLayer1.jetCountFilter_cfi import countPatJets
    process.NumJetSelection = countPatJets.clone(
        src       = cms.InputTag('HTJets'),
        minNumber = cms.uint32(NJetsMin)
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
    mhtInputCol = 'mhtPF'
    if useCHSJets:
        mhtInputCol = 'mhtPFchs'

    from SandBox.Skims.RA2MHT_cff import mhtPFFilter
    process.MHTSelection = mhtPFFilter.clone(
        MHTSource = cms.InputTag(mhtInputCol),
        MinMHT = cms.double(MHTMin)
        )


    ## --- Additional Filters (tagging mode) ------------------------------
    from RecoMET.METFilters.jetIDFailureFilter_cfi import jetIDFailure
    process.PBNRFilter = jetIDFailure.clone(
        JetSource = cms.InputTag('MHTJets'),
        MinJetPt      = cms.double(30.0),
        taggingMode   = cms.bool(True)
        )
    process.AdditionalFiltersInTagMode = cms.Sequence(
        process.PBNRFilter
        )


    ## --- Setup WeightProducer -------------------------------------------
    from RA2Classic.WeightProducer.getWeightProducer_cff import getWeightProducer
    process.WeightProducer = getWeightProducer(process.source.fileNames[0])


    for i in process.source.fileNames:
        print "++++ process.source.fileNames: "+i
        

    ## --- Setup of TreeMaker ----------------------------------------------
    FilterNames = cms.VInputTag()  # Append all filters in AdditionalFiltersInTagMode
    for f in process.AdditionalFiltersInTagMode.moduleNames():
        FilterNames.append(cms.InputTag(f))

    from RA2Classic.TreeMaker.treemaker_cfi import TreeMaker
    process.RA2TreeMaker = TreeMaker.clone(
        TreeName          = cms.string("RA2PreSelection"),
        VertexCollection  = cms.InputTag('goodVertices'),
        HT                = cms.InputTag(htInputCol),
        HTJets            = cms.InputTag('HTJets'),
        MHT               = cms.InputTag(mhtInputCol),
        MHTJets           = cms.InputTag('MHTJets'),
        VarsDouble        = cms.VInputTag(cms.InputTag('WeightProducer:weight')),
        VarsDoubleNamesInTree = cms.vstring('Weight'),
        CandidateCollections  = cms.VInputTag('MHTJets','patMuonsPFIDIso','patElectronsIDIso'),
        CandidateNamesInTree  = cms.vstring('Jets','PATMuonsPFIDIso','PATElectronsIDIso'),
        Filters           = cms.VInputTag() #FilterNames
        )


    ## --- Final paths ----------------------------------------------------

#    process.dump = cms.EDAnalyzer("EventContentAnalyzer")
    
    process.WriteTree = cms.Path(
        process.CleaningSelection *
        process.LeptonVeto *
        process.ProduceRA2Jets *
        process.NumJetSelection *
        process.HTSelection *
        process.MHTSelection *
#        process.AdditionalFiltersInTagMode *
        process.WeightProducer *
#        process.dump *
        process.RA2TreeMaker
        )
