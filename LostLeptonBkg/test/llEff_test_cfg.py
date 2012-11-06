# $Id: llEff_test_cfg.py,v 1.1 2012/10/12 12:29:19 adraeger Exp $

# cmsRun runMakeTreeFromPAT_cfg.py dataset=/store/user/kheine/WJetsToLNu_HT-400ToInf_8TeV-madgraph/RA2PreSelectionOnMC_HT-400ToInf_Summer12-PU_S7_START52_V9-v1_v1//956a76b9479f1eb39208c1bee6fa7dc2/RA2SkimsOnMC_10_1_Lsq.root
import sys,os

dataSetName = ""
if hasattr(sys,"argv"):
    for arg in sys.argv :
        pairs = arg.split(',')
        for pair in pairs:
            vals = pair.split('=')
            if len(vals) == 2 :
                if vals[0] == "dataset":
                    dataSetName = vals[1]

print "***** SETUP ************************************"
print "  dataSetName : "+dataSetName
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
                testFileName=dataSetName,
                numProcessedEvt=-1)
