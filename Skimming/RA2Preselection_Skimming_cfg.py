#  $Id: $
#
# --- Configuration file for RA2 skims from AOD ---------------------------------
#
# For data
#

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

runRA2Preselection(process,globalTag=global_tag+"::All",isData=is_data,reportEveryEvt=5000,testFileName="/store/data/Run2012A/HT/AOD/13Jul2012-v1/00000/26B0D540-D0D2-E111-847D-00248C55CC9D.root")


#-- Create resolved config ------------------------------------------------------
# crab should use the resolved config!
file=open("RA2Preselection_Skimming_resolved.py","w")
file.write(str(process.dumpPython()))
file.close()
