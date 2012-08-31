#  $Id: $
#
# --- Configuration file for RA2 skims from AOD ---------------------------------
#
# For data
#

import FWCore.ParameterSet.Config as cms


#-- Run the process -------------------------------------------------------------
from PhysicsTools.PatAlgos.patTemplate_cfg import *
from RA2Classic.Skimming.Preselection_cff import runRA2Preselection
runRA2Preselection(process,globalTag="GR_R_52_V9D::All",isData=True,reportEveryEvt=5000)

#-- Create resolved config ------------------------------------------------------
file=open("RA2PreselectionOnData_Skimming_resolved.py","w")
file.write(str(process.dumpPython()))
file.close()
