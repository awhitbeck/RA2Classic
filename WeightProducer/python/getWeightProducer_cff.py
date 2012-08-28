# $Id: getWeightProducer_cff.py,v 1.1 2012/08/28 17:00:46 mschrode Exp $
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
        weightProducer.XS         = cms.double(48.01)
        weightProducer.NumberEvts = cms.double(1634582)         
    if "WJetsToLNu_HT-300To400_8TeV-madgraph" in fileName and "Summer12-PU_S7_START52_V9-v1" in fileName:
        mcVersion = "Summer12"
        weightProducer.Method     = cms.string("Constant")
        weightProducer.XS         = cms.double(38.3)
        weightProducer.NumberEvts = cms.double(1698744)         
    if "WJetsToLNu_HT-400ToInf_8TeV-madgraph" in fileName and "Summer12-PU_S7_START52_V9-v1" in fileName:
        mcVersion = "Summer12"
        weightProducer.Method     = cms.string("Constant")
        weightProducer.XS         = cms.double(25.22)
        weightProducer.NumberEvts = cms.double(1647807)         

    # For ZJets
    if "ZJetsToNuNu_50_HT_100_TuneZ2Star_8TeV_madgraph" in fileName and "Summer12-PU_S7_START52_V9-v1" in fileName:
        mcVersion = "Summer12"
        weightProducer.Method     = cms.string("Constant")
        weightProducer.XS         = cms.double(381.2)
        weightProducer.NumberEvts = cms.double(4053786)         
    if "ZJetsToNuNu_100_HT_200_TuneZ2Star_8TeV_madgraph" in fileName and "Summer12-PU_S7_START52_V9-v1" in fileName:
        mcVersion = "Summer12"
        weightProducer.Method     = cms.string("Constant")
        weightProducer.XS         = cms.double(160.3)
        weightProducer.NumberEvts = cms.double(4416646)         
##     if "ZJetsToNuNu_200_HT_400_TuneZ2Star_8TeV_madgraph" in fileName and "Summer12-PU_S7_START52_V9-v1" in fileName:
##         mcVersion = "Summer12"
##         weightProducer.Method     = cms.string("Constant")
##         weightProducer.XS         = cms.double(41.49)
##         weightProducer.NumberEvts = cms.double()         
    if "ZJetsToNuNu_400_HT_inf_TuneZ2Star_8TeV_madgraph" in fileName and "Summer12-PU_S7_START52_V9-v1" in fileName:
        mcVersion = "Summer12"
        weightProducer.Method     = cms.string("Constant")
        weightProducer.XS         = cms.double(5.274)
        weightProducer.NumberEvts = cms.double(1006928)         


    # Defaults for MC
    if mcVersion == "Summer12":
        weightProducer.weight     = cms.double(-1.)
        weightProducer.Lumi       = cms.double(5088)
        weightProducer.PU         = cms.int32(2)
##        weightProducer.FileNamePUDataDistribution = cms.string("RA2Classic/AdditionalInputFiles/DataPileupHistogram_RA2Summer12_190456-196531_8TeV_PromptReco_WOLowPU.root")
        # grid-control requires additional input files to be in the data directory
        weightProducer.FileNamePUDataDistribution = cms.string("RA2Classic/WeightProducer/data/DataPileupHistogram_RA2Summer12_190456-196531_8TeV_PromptReco_WOLowPU.root")


    return weightProducer
