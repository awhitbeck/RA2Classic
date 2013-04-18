import FWCore.ParameterSet.Config as cms

Limit_ll = cms.EDProducer(
	'Limit_ll',
	 NTupleName = cms.string('RA2Ntuple_T1-0700-0450.root'),
	 Path = cms.string('RA2TreeMaker/RA2PreSelection'),
	 EfficiencyFileName = cms.string('MCEff.root'),
	 MTWMax		= cms.double('100'),
	 MTWCut		= cms.bool(True),
	 DiLepCorrection = cms.double('-1.5'),
	 DiLepCorrectionUp = cms.double('50'), 
	 DiLepCorrectionDown = cms.double('50'),
	 EventWeight = cms.double('0.003866272'), # T1ttt_mother1100_LSP50 signal point
)
