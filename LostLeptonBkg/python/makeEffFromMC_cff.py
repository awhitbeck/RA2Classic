# $Id: makeEffFromMC_cff.py,v 1.5 2012/11/19 13:08:37 adraeger Exp $
#


import FWCore.ParameterSet.Config as cms
def makeTreeFromPAT(process,
                    outFileName,
                    useCHSJets=True,
		    invertLeptonVeto=False,
                    NJetsMin=2,
                    HTMin=500.,
                    MHTMin=200.,
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
        process.filterSelection
        )

    # Filter-related selection
#    process.load('RA2Classic.TreeMaker.filterSelection_cff')
#    from RecoMET.METFilters.jetIDFailureFilter_cfi import jetIDFailure
#    process.PBNRFilter = jetIDFailure.clone(
#        JetSource = cms.InputTag('MHTJets'),
#        MinJetPt      = cms.double(30.0),
#        taggingMode   = cms.bool(False)
#        )
#    process.filterSelection += process.PBNRFilter
#    from RecoMET.METFilters.multiEventFilter_cfi import multiEventFilter
#    process.HCALLaserEvtFilterList2012 = multiEventFilter.clone(
#        file        = cms.FileInPath('EventFilter/HcalRawToDigi/data/AllBadHCALLaser.txt'),
#        taggingMode = cms.bool(False)
#        )
 #   process.filterSelection += process.HCALLaserEvtFilterList2012




    # Produce RA2 jets
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
    mhtMin = 0.
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
        

    ## --- Setup of TreeMaker ----------------------------------------------
    FilterNames = cms.VInputTag()  # All filters in AdditionalFiltersInTagMode
    for f in process.AdditionalFiltersInTagMode.moduleNames():
        FilterNames.append(cms.InputTag(f))

##     FilterNames.append(cms.InputTag("HBHENoiseFilterRA2","HBHENoiseFilterResult","PAT"))
##     FilterNames.append(cms.InputTag("beamHaloFilter"))
##     FilterNames.append(cms.InputTag("eeNoiseFilter"))
##     FilterNames.append(cms.InputTag("trackingFailureFilter"))
##     FilterNames.append(cms.InputTag("inconsistentMuons"))
##     FilterNames.append(cms.InputTag("greedyMuons"))
##     FilterNames.append(cms.InputTag("ra2EcalTPFilter"))
##     FilterNames.append(cms.InputTag("ra2EcalBEFilter"))
##     FilterNames.append(cms.InputTag("hcalLaserEventFilter"))
##     FilterNames.append(cms.InputTag("eeBadScFilter"))



    from RA2Classic.TreeMaker.treemaker_cfi import TreeMaker
    process.RA2TreeMaker = TreeMaker.clone(
        TreeName          = cms.string("RA2PreSelection"),
        VertexCollection  = cms.InputTag('goodVertices'),
        HT                = cms.InputTag(htInputCol),
        HTJets            = cms.InputTag('HTJets'),
        MHT               = cms.InputTag(mhtInputCol),
        MHTJets           = cms.InputTag('MHTJets'),
        VarsDouble        = cms.VInputTag(cms.InputTag('WeightProducer:weight'),cms.InputTag('LostLeptonBkgProducer:LostLeptonWeight'),cms.InputTag('LostLeptonBkgProducer:Met'),cms.InputTag('LostLeptonBkgProducer:nMu'),cms.InputTag('LostLeptonBkgProducer:MuPt'),cms.InputTag('LostLeptonBkgProducer:MuEta'),cms.InputTag('LostLeptonBkgProducer:MuPhi' ),cms.InputTag('LostLeptonBkgProducer:deltaRMuJet'),cms.InputTag('LostLeptonBkgProducer:deltaRMuMHT' ),cms.InputTag('LostLeptonBkgProducer:deltaPtMuJet') ),
        VarsDoubleNamesInTree = cms.vstring('Weight','LostLeptonWeight','Met','numberOfMuons','MuPT','MuEta','MuPhi','DeltaRMuJet','DeltaRMuMHT','DeltaPtMuJet'), 
        Filters           = FilterNames
        )
	
	
	
	# filter used to slecte the RA2 baseline important for efficiency caluclaiton
    from RA2Classic.Utils.RA2Selection_cfi import RA2Selection
    process.RA2Selector = RA2Selection.clone(
    	nJets		= cms.uint32 (2)
	
	)

   ## ---- Load lost lepton moduels
   # special calo jets for delta R in efficiencies
    process.load('JetMETCorrections.Configuration.DefaultJEC_cff')
   
#   from RA2Classic.LostLeptonBkg.llPrediction_cff import llPrediction
 #  process.lostLeptonPrediction = llPrediction()
    from RA2Classic.LostLeptonBkg.MCEffCalculator_cfi import MCEffCalculator
    process.LostLeptonBkgMCEffCalculator = MCEffCalculator.clone(
        MuonIDTag = cms.InputTag("patMuonsPFID"),
	MuonIDISOTag = cms.InputTag("patMuonsPFIDIso"),
        ElecIDTag = cms.InputTag("patElectronsIDIso"), 
	ElecIDISOTag = cms.InputTag("patElectronsIDIso"),
	HTTag	   = cms.InputTag(htInputCol),
 	MHTTag	   = cms.InputTag(mhtInputCol),
 #	CaloJetTag = cms.InputTag("ak5CaloJetsL2L3")
    )


    from RA2Classic.LostLeptonBkg.promtisomu_cfi import promtIsoMu
    process.promtLeptons = promtIsoMu.clone(
	MuonIDISOTag = cms.InputTag("patMuonsPFIDIso")
 #	CaloJetTag = cms.InputTag("ak5CaloJetsL2L3")
    )

 #  process.lostLeptonPrediction = llPrediction()
    from RA2Classic.LostLeptonBkg.bkglostlepton_cfi import bkglostlepton
    process.LostLeptonBkgProducer = bkglostlepton.clone(
    	HTJets		= cms.InputTag('HTJets'),
	MetTag		= cms.InputTag('pfMet'),
	CaloJetTag	= cms.InputTag('cleanPatJetsAK5Calo'),
#	MuonTag		= cms.InputTag('promtLeptons:PromtMuon'),
	MuonTag		= cms.InputTag('patMuonsPFIDIso'),
	ElecTag         = cms.InputTag("patElectronsIDIso"), 
	MTWCut		= cms.bool(True),
	EfficiencyFileName = cms.string('MCEff.root'),
	HTTag	   = cms.InputTag(htInputCol),
 	MHTTag	   = cms.InputTag(mhtInputCol),
    )



 #electrons selectors for ID electrons
    from SandBox.Skims.electronSelector_cfi import electronSelector
    process.patElectronsID = electronSelector.clone(
   	 DoElectronIsolation      = cms.bool(False)
    )



    ## --- Final paths ----------------------------------------------------

    process.dump = cms.EDAnalyzer("EventContentAnalyzer")
    
    process.WriteTree = cms.Path(
        process.CleaningSelection *
	process.ProduceRA2Jets *
        process.NumJetSelection *
        process.HTSelection *
        process.MHTSelection *
        process.AdditionalFiltersInTagMode *
        process.WeightProducer *
#	process.promtLeptons *
#	process.patElectronsID *
	process.RA2Selector *
#	process.ak5CaloJetsL2L3 *
	process.LostLeptonBkgMCEffCalculator 
#	process.LostLeptonBkgProducer
#	process.RA2TreeMaker 

        )
