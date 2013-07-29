# $Id: llEff_test_cfg.py,v 1.3 2013/02/15 08:51:52 adraeger Exp $

# cmsRun ../test/llTAP_test_cfg.py dataset=/store/user/adraeger/TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7A-v1_V2//9a64257873f37bce72f62fbdaab014a9/RA2Skim_100_1_DnI.root, global_tag=START53_V7F::All
# cmsRun ../test/llTAP_test_cfg.py dataset=/store/user/adraeger/SingleElectron/RA2PreSelection_Summer12_DR53X-PU_S10_START53_V7A-v1_V4_ElecRunD_desy/bc449038902628d6090f37dce94cb78e/RA2Skim_670_1_gOE.root, global_tag=GR_P_V42_AN2::All, MCTAP=False, muonTrigger=HLT_IsoMu24_v*, Muon=False

# Read parameters
from RA2Classic.Utils.CommandLineParams import CommandLineParams
parameters = CommandLineParams()

dataSetName = parameters.value("dataset","")
global_tag = parameters.value("global_tag","")
MCTAP= parameters.value("MCTAP",True)
Muon= parameters.value("Muon", True)
muonTrigger = parameters.value("muonTrigger","")

#global_tag="START53_V7F::All"
print "***** SETUP ************************************"
print "  dataSetName : "+dataSetName
print "  global_tag : "+global_tag
print "  MCTAP : "+str(MCTAP)
print "  Using Muon : "+str(Muon)
print "  muonTrigger : "+muonTrigger
print "************************************************"



import FWCore.ParameterSet.Config as cms
process = cms.Process("RA2LostLeptonPrediction")

from RA2Classic.LostLeptonBkg.makeTAPTree_cff import makeTreeFromPAT
makeTreeFromPAT(process,
                outFileName="TAPTree",
                useCHSJets=True,
		invertLeptonVeto=True,
                NJetsMin=2,
                HTMin=00.,
                MHTMin=00.,
                reportEveryEvt=5000,
                testFileName=dataSetName,
		Global_Tag=global_tag,
		MCTAP=MCTAP,
		Muon=Muon,
		muonTrigger=muonTrigger,
                numProcessedEvt=-1)
