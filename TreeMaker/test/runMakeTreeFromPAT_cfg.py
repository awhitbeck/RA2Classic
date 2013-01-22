# $Id: runMakeTreeFromPAT_cfg.py,v 1.6 2012/12/06 15:27:10 mschrode Exp $
#
# Expects a file name as argument e.g.
# cmsRun runMakeTreeFromPAT_cfg.py dataset=/store/user/mschrode/HT/RA2PreSelection_Run2012A-13Jul2012-v1_V2//528d417548fa47de754292e17c1b0d17/RA2Skim_105_1_Tzb.root


# Read parameters
from RA2Classic.Utils.CommandLineParams import CommandLineParams
parameters = CommandLineParams()

dataSetName = parameters.value("dataset","")
nJetsMin    = parameters.value("njets_min",2)
htMin       = parameters.value("ht_min",0)
mhtMin      = parameters.value("mht_min",0)

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
                testFileName='/store/user/mschrode/HTMHT/RA2PreSelection_Run2012C-PromptReco-v2_V4/1d5bc287a8c7728f9d7414517d1cc2d8/RA2Skim_1000_1_QDh.root',
                numProcessedEvt=1000)
