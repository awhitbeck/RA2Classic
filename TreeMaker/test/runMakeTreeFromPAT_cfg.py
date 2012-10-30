# $Id: runMakeTreeFromPAT_cfg.py,v 1.3 2012/09/19 14:01:37 mschrode Exp $
#
# Expects a file name as argument e.g.
# cmsRun runMakeTreeFromPAT_cfg.py dataset=/store/user/mschrode/HT/RA2PreSelection_Run2012A-13Jul2012-v1_V2//528d417548fa47de754292e17c1b0d17/RA2Skim_105_1_Tzb.root

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

# The process needs to be defined AFTER reading sys.argv,
# otherwise edmConfigHash fails
import FWCore.ParameterSet.Config as cms
process = cms.Process("RA2EventSelection")

from RA2Classic.TreeMaker.makeTreeFromPAT_cff import makeTreeFromPAT
makeTreeFromPAT(process,
                outFileName="RA2Selection",
                useCHSJets=True,
                NJetsMin=2,
                HTMin=500.,
                MHTMin=200.,
                reportEveryEvt=5000,
                testFileName=dataSetName,
                numProcessedEvt=100)
