# $Id: $
#
# Trees for SMS T1 (pp --> gluino-gluino)
# Cross sections from https://twiki.cern.ch/twiki/bin/view/LHCPhysics/SUSYCrossSections8TeVgluglu

import FWCore.ParameterSet.Config as cms

from PhysicsTools.PatAlgos.patTemplate_cfg import *
from RA2Classic.TreeMaker.makeTreeFromSignalScan_cff import makeTreeFromSignalScan
makeTreeFromSignalScan(process,
                       globalTag="START52_V11C::All",
                       smsModel="T1",
                       smsMotherMass=1150,
                       smsLSPMass=200,
                       xs=0.00666673,
                       numEvtsInSample=10000,
                       lumi=5.088
                       )

# outpath needs to be removed, otherwise crab won't
# create the jobs
if hasattr(process,"outpath"):
    delattr(process,"outpath")
