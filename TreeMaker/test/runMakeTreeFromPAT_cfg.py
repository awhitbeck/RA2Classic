# $Id: runMakeTreeFromPAT_cfg.py,v 1.4 2012/10/30 21:13:24 mschrode Exp $
#
# Expects a file name as argument e.g.
# cmsRun runMakeTreeFromPAT_cfg.py dataset=/store/user/mschrode/HT/RA2PreSelection_Run2012A-13Jul2012-v1_V2//528d417548fa47de754292e17c1b0d17/RA2Skim_105_1_Tzb.root


# Read parameters
from RA2Classic.Utils.CommandLineParams import CommandLineParams
parameters = CommandLineParams()

dataSetName = parameters.value("dataset","")
nJetsMin    = parameters.value("njets_min",2)
htMin       = parameters.value("ht_min",500)
mhtMin      = parameters.value("mht_min",200)

print "***** SETUP ************************************"
print "  dataSetName : "+dataSetName
print "     nJetsMin : "+str(nJetsMin)
print "        htMin : "+str(htMin)
print "       mhtMin : "+str(mhtMin)
print "************************************************"

# The process needs to be defined AFTER reading sys.argv,
# otherwise edmConfigHash fails
import FWCore.ParameterSet.Config as cms
process = cms.Process("RA2EventSelection")

from RA2Classic.TreeMaker.makeTreeFromPAT_cff import makeTreeFromPAT
makeTreeFromPAT(process,
                outFileName="RA2Selection",
                NJetsMin=nJetsMin,
                HTMin=htMin,
                MHTMin=mhtMin,
                reportEveryEvt=5000,
                testFileName=dataSetName,
                numProcessedEvt=100)
