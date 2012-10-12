import FWCore.ParameterSet.Config as cms

MCEffCalculator = cms.EDAnalyzer(
	'MCEffCalculator',
	      TreeName          = cms.string('LostLeptonMCEff'),
	      EventWeightTag = cms.InputTag("WeightProducer:weight"),           
              MuonIDTag = cms.InputTag("patMuonsPFID"),
              MuonIDISOTag = cms.InputTag("patMuonsPFIDIso"),
              ElecIDTag = cms.InputTag("selectedPatElectronsPF"), 
	      ElecIDISOTag = cms.InputTag("patElectronsIDIso"),
              JetTag = cms.InputTag("patJetsPF"),
	      CaloJetTag = cms.InputTag("cleanPatJetsAK5Calo"),
              METTag = cms.InputTag("patMETsPF"),
              GenTag = cms.InputTag("genParticles"),                  
              minMuonPt = cms.double(10),
	      maxMuonEta = cms.double(2.4),
              minElecPt = cms.double(10),
	      maxElecEta = cms.double(2.5),
              minJetPt = cms.double(30),

	)