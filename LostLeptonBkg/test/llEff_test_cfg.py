# $Id: runMakeTreeFromPAT_cfg.py,v 1.2 2012/09/14 13:10:37 mschrode Exp $

import FWCore.ParameterSet.Config as cms
process = cms.Process("RA2LostLeptonPrediction")

from RA2Classic.LostLeptonBkg.makeEffFromMC_cff import makeTreeFromPAT
makeTreeFromPAT(process,
                outFileName="LostLeptonEffFromMC",
                useCHSJets=True,
		invertLeptonVeto=True,
                NJetsMin=2,
                HTMin=00.,
                MHTMin=00.,
                reportEveryEvt=5000,
                testFileName=["/store/user/kheine/WJetsToLNu_HT-250To300_8TeV-madgraph/RA2PreSelectionOnMC_HT-250To300_Summer12-PU_S7_START52_V9-v1_v1//956a76b9479f1eb39208c1bee6fa7dc2/RA2SkimsOnMC_6_1_D3y.root"],
                numProcessedEvt=100)
