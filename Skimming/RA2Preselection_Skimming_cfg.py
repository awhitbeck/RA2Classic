#  $Id: RA2Preselection_Skimming_cfg.py,v 1.2 2012/10/08 13:27:30 mschrode Exp $
#
# --- Configuration file for RA2 skims from AOD ---------------------------------
#
# The following command-line arguments need to be given as a
# comma-separated list (no spaces)
# - 'is_data=?', where ? = 'True' or 'False'
# - 'global_tag=?'
#
# For example:
# 'cmsRun RA2Preselection_Skimming_cfg.py is_data=True,global_tag=FT_53_V6_AN2'

import sys,os
import FWCore.ParameterSet.Config as cms

#-- Parse command line arguments ------------------------------------------------
is_data=True
global_tag=""
if hasattr(sys,"argv") :
    for args in sys.argv :
        arg = args.split(',')
        for val in arg:
            val = val.split('=')
            if len(val)==2 :
                if val[0]=="is_data":
                    if val[1]=="True":
                        is_data=True
                    else:
                        is_data=False
                elif val[0]=="global_tag":
                    global_tag=val[1]

print "*** JOB SETUP ****************************************************"
if is_data :
    print "     is_data : True"
else:
    print "     is_data : False"
print "  global_tag : "+global_tag+"::All"
print "******************************************************************"


#-- Run the process -------------------------------------------------------------
from PhysicsTools.PatAlgos.patTemplate_cfg import *
from RA2Classic.Skimming.Preselection_cff import runRA2Preselection

runRA2Preselection(process,globalTag=global_tag+"::All",isData=is_data,reportEveryEvt=5000,testFileName="/store/mc/Summer12_DR53X/WJetsToLNu_TuneZ2Star_8TeV-madgraph-tarball/AODSIM/PU_S10_START53_V7A-v2/0004/FE9FA8F7-2BF3-E111-A34E-001E672CC1E7.root")
