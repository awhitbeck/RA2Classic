# $Id: getWeightProducer_cff.py,v 1.3 2012/08/30 16:29:43 mschrode Exp $
#
# Returns a WeightProducer module that knows at runtime
# which data sample is produced and thus, what weights
# are required. The function can be used as follows:
#
#    from RA2Classic.WeightProducer.getWeightProducer_cff import getWeightProducer
#    process.WeightProducer = getWeightProducer(process.source.fileNames[0])


import FWCore.ParameterSet.Config as cms

def getWeightProducer(fileName):


    ## --- Setup default WeightProducer ------------------------------------

    # Import weightProducer
    from RA2Classic.WeightProducer.weightProducer_cfi import weightProducer

    # Set default values to produce an event weight of 1
    weightProducer.weight = cms.double(1.0)
    weightProducer.Method = cms.string("")
    weightProducer.LumiScale = cms.double(1.0)
    weightProducer.FileNamePUDataDistribution = cms.string("NONE")
    weightProducer.PU = cms.int32(0)



    ## --- Adjust WeightProducer for Summer12 MC samples --------------------

    mcVersion = "none"                  # For lumi and PU weights

    # For ttbar
    if "TTJets_TuneZ2star_8TeV-madgraph-tauola" in fileName and "Summer12-PU_S7_START52_V9-v1" in fileName:
        mcVersion = "Summer12"
        weightProducer.Method     = cms.string("Constant")
        weightProducer.XS         = cms.double(234)
        weightProducer.NumberEvts = cms.double(6736135)         

    # For WJets
    if "WJetsToLNu_HT-250To300_8TeV-madgraph" in fileName and "Summer12-PU_S7_START52_V9-v1" in fileName:
        mcVersion = "Summer12"
        weightProducer.Method     = cms.string("Constant")
        weightProducer.XS         = cms.double(57.26)
        weightProducer.NumberEvts = cms.double(1634582)         
    if "WJetsToLNu_HT-300To400_8TeV-madgraph" in fileName and "Summer12-PU_S7_START52_V9-v1" in fileName:
        mcVersion = "Summer12"
        weightProducer.Method     = cms.string("Constant")
        weightProducer.XS         = cms.double(45.68)
        weightProducer.NumberEvts = cms.double(1698744)         
    if "WJetsToLNu_HT-400ToInf_8TeV-madgraph" in fileName and "Summer12-PU_S7_START52_V9-v1" in fileName:
        mcVersion = "Summer12"
        weightProducer.Method     = cms.string("Constant")
        weightProducer.XS         = cms.double(30.08)
        weightProducer.NumberEvts = cms.double(1647807)         

    # For ZJets
    if "ZJetsToNuNu_50_HT_100_TuneZ2Star_8TeV_madgraph" in fileName and "Summer12-PU_S7_START52_V9-v1" in fileName:
        mcVersion = "Summer12"
        weightProducer.Method     = cms.string("Constant")
        weightProducer.XS         = cms.double(452.75)
        weightProducer.NumberEvts = cms.double(4053786)         
    if "ZJetsToNuNu_100_HT_200_TuneZ2Star_8TeV_madgraph" in fileName and "Summer12-PU_S7_START52_V9-v1" in fileName:
        mcVersion = "Summer12"
        weightProducer.Method     = cms.string("Constant")
        weightProducer.XS         = cms.double(190.39)
        weightProducer.NumberEvts = cms.double(4416646)         
    if "ZJetsToNuNu_200_HT_400_TuneZ2Star_8TeV_madgraph" in fileName and "Summer12-PU_S7_START52_V9-v3" in fileName:
        mcVersion = "Summer12"
        weightProducer.Method     = cms.string("Constant")
        weightProducer.XS         = cms.double(49.28)
        weightProducer.NumberEvts = cms.double(5066608)         
    if "ZJetsToNuNu_400_HT_inf_TuneZ2Star_8TeV_madgraph" in fileName and "Summer12-PU_S7_START52_V9-v1" in fileName:
        mcVersion = "Summer12"
        weightProducer.Method     = cms.string("Constant")
        weightProducer.XS         = cms.double(6.26)
        weightProducer.NumberEvts = cms.double(1006928)         

    # For QCD
    if "QCD_Pt-15to3000_TuneZ2_Flat_8TeV_pythia6" in fileName and "Summer12-PU_S7_START52_V9-v1" in fileName:
        mcVersion = "Summer12"
        weightProducer.Method     = cms.string("PtHat")
        weightProducer.XS         = cms.double(2.99913994e+10)
        weightProducer.NumberEvts = cms.double(9998154)
        weightProducer.Exponent   = cms.double(-4.5)

    # Defaults for MC
    if mcVersion == "Summer12":
        weightProducer.weight     = cms.double(-1.)
        weightProducer.Lumi       = cms.double(5088)
        weightProducer.PU         = cms.int32(2)
##        weightProducer.FileNamePUDataDistribution = cms.string("RA2Classic/AdditionalInputFiles/DataPileupHistogram_RA2Summer12_190456-196531_8TeV_PromptReco_WOLowPU.root")
        # grid-control requires additional input files to be in the data directory
        weightProducer.FileNamePUDataDistribution = cms.string("RA2Classic/WeightProducer/data/DataPileupHistogram_RA2Summer12_190456-196531_8TeV_PromptReco_WOLowPU.root")


    return weightProducer
