# $Id: $
#
# Trees for SMS T2 (pp --> squark-antisquark)
# Cross sections from https://twiki.cern.ch/twiki/bin/view/LHCPhysics/SUSYCrossSections8TeVsquarkantisquark

import FWCore.ParameterSet.Config as cms

from PhysicsTools.PatAlgos.patTemplate_cfg import *
from RA2Classic.TreeMaker.makeTreeFromSignalScan_cff import makeTreeFromSignalScan
makeTreeFromSignalScan(process,
                       globalTag="START52_V11C::All",
                       smsModel="T2",
                       smsMotherMass=900,
                       smsLSPMass=50,
                       xs=0.0106744,
                       numEvtsInSample=10000,
                       lumi=5.088
                       )

# outpath needs to be removed, otherwise crab won't
# create the jobs
if hasattr(process,"outpath"):
    delattr(process,"outpath")
