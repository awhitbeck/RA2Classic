# $Id: runMakeTreeFromPAT_cfg.py,v 1.9 2013/01/24 15:42:54 mschrode Exp $
#
# Expects a file name as argument e.g.
# cmsRun runMakeTreeFromPAT_cfg.py dataset=/store/user/mschrode/HT/RA2PreSelection_Run2012A-13Jul2012-v1_V4/21a074f94cdbe7cfbeeb19be46b40a6a/RA2Skim_9_1_h6A.root, global_tag=FT_53_V6C_AN3


# Read parameters
from RA2Classic.Utils.CommandLineParams import CommandLineParams
parameters = CommandLineParams()

dataSetName = parameters.value("dataset","")
nJetsMin    = parameters.value("njets_min",2)
htMin       = parameters.value("ht_min",0)
mhtMin      = parameters.value("mht_min",0)
globaltag   = parameters.value("global_tag","none")+"::All"

print "***** SETUP ************************************"
print "  dataSetName : "+dataSetName
print "     nJetsMin : "+str(nJetsMin)
print "        htMin : "+str(htMin)
print "       mhtMin : "+str(mhtMin)
print "    globalTag : "+globaltag
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
                globalTag=globaltag,
                reportEveryEvt=5000,
                testFileName=dataSetName,
                numProcessedEvt=1000)
