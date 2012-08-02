# $Id: $

import FWCore.ParameterSet.Config as cms
process = cms.Process("RA2EventSelectionOnData")

from RA2Classic.TreeMaker.makeTreeFromPAT_cff import makeTreeFromPAT
makeTreeFromPAT(process,
                outFileName="RA2Selection",
                useCHSJets=True,
                NJetsMin=2,
                HTMin=350.,
                MHTMin=0.,
                reportEveryEvt=10,
                testFileName=["/store/user/kheine/HT/RA2PreSelectionOnData_Run2012A_HT_PromptReco-v1_v5/71cce229addb17644d40a607fa20b5d7/RA2SkimsOnData_99_3_TPC.root"],
                numProcessedEvt=-100)
