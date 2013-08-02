# $Id: llEff_test_cfg.py,v 1.3 2013/02/15 08:51:52 adraeger Exp $

# cmsRun ../test/llEff_test_cfg.py dataset=/store/user/mschrode/WJetsToLNu_HT-400ToInf_8TeV-madgraph_v2/RA2PreSelection_Summer12_DR53X-PU_S10_START53_V7A-v1_V4/6c50609e978ba7d5388d5439fc628605/RA2Skim_104_1_HGc.root, global_tag=START53_V7F::All, MC=True



# Read parameters
from RA2Classic.Utils.CommandLineParams import CommandLineParams
parameters = CommandLineParams()

dataSetName = parameters.value("dataset","")
global_tag = parameters.value("global_tag","")
MC= parameters.value("MC", False)
RecoLeptonStudy = parameters.value("RecoLeptonStudy",False)
Debug = parameters.value("Debug",False)
#global_tag="START53_V7F::All"
print "***** SETUP ************************************"
print "  dataSetName : "+dataSetName
print "  global_tag : "+global_tag
print "  runningOnMC : "+str(MC)
print "  RecoLeptonStudy : "+str(RecoLeptonStudy)
print "  Debug : "+str(Debug)
print "************************************************"



import FWCore.ParameterSet.Config as cms
process = cms.Process("RA2LostLeptonPrediction")

from RA2Classic.LostLeptonBkg.makeEffFromMC_cff import makeTreeFromPAT
makeTreeFromPAT(process,
                outFileName="LostLeptonEffFromMC",
                useCHSJets=True,
		invertLeptonVeto=True,
                NJetsMin=2,
                HTMin=00.,
                MHTMin=00.,
                reportEveryEvt=5000,
		Global_Tag=global_tag,
		MC=MC,
		RecoLeptonStudyBool=RecoLeptonStudy,
		DebugBool=Debug,
                testFileName=dataSetName,
)
