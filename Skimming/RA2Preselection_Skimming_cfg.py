#  $Id: RA2Preselection_Skimming_cfg.py,v 1.3 2012/10/30 21:12:13 mschrode Exp $
#
# --- Configuration file for RA2 skims from AOD ---------------------------------
#
# The following command-line arguments need to be given as a
# comma-separated list
# - 'is_data=?', where ? = 'True' or 'False'
# - 'global_tag=?'
#
# For example:
# 'cmsRun RA2Preselection_Skimming_cfg.py is_data=True, global_tag=FT_53_V6_AN2'

# Read parameters
from RA2Classic.Utils.CommandLineParams import CommandLineParams
parameters = CommandLineParams()

isData     = parameters.value("is_data","True")
globalTag  = parameters.value("global_tag","")

globalTag += "::All"

print "***** SETUP ************************************"
print "      is_data : "+str(isData)
print "   global_tag : "+str(globalTag)
print "************************************************"

# The process needs to be defined AFTER calling CommandLineParams
# (more specifically, after reading sys.argv), otherwise edmConfigHash fails
from PhysicsTools.PatAlgos.patTemplate_cfg import *
from RA2Classic.Skimming.Preselection_cff import runRA2Preselection

runRA2Preselection(process,
                   globalTag,
                   isData,
                   reportEveryEvt=5000,
                   testFileName="/store/data/Run2012A/HT/AOD/13Jul2012-v1/00000/FEEF1E85-BACF-E111-807A-002618943877.root",
                   numProcessedEvt=100
                   )
