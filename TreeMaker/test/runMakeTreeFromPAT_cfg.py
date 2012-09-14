# $Id: runMakeTreeFromPAT_cfg.py,v 1.1 2012/08/02 14:37:01 mschrode Exp $

import FWCore.ParameterSet.Config as cms
process = cms.Process("RA2EventSelection")

from RA2Classic.TreeMaker.makeTreeFromPAT_cff import makeTreeFromPAT
makeTreeFromPAT(process,
                outFileName="RA2Selection",
                useCHSJets=True,
                NJetsMin=2,
                HTMin=0.,
                MHTMin=0.,
                reportEveryEvt=5000,
                testFileName=["/store/user/kheine/ZJetsToNuNu_200_HT_400_TuneZ2Star_8TeV_madgraph/RA2PreSelectionOnMC_200_HT_400_Summer12-PU_S7_START52_V9-v3_v1//956a76b9479f1eb39208c1bee6fa7dc2/RA2SkimsOnMC_125_3_W97.root"],
                numProcessedEvt=100)
