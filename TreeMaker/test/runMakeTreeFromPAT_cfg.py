# $Id: runMakeTreeFromPAT_cfg.py,v 1.2 2012/09/14 13:10:37 mschrode Exp $
#
# Expects a file name as argument e.g.
# cmsRun runMakeTreeFromPAT_cfg.py /store/user/kheine/ZJetsToNuNu_200_HT_400_TuneZ2Star_8TeV_madgraph/RA2PreSelectionOnMC_200_HT_400_Summer12-PU_S7_START52_V9-v3_v1//956a76b9479f1eb39208c1bee6fa7dc2/RA2SkimsOnMC_125_3_W97.root

import sys
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
                testFileName=sys.argv[2],
                numProcessedEvt=100)
