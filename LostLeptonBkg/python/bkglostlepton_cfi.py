
import FWCore.ParameterSet.Config as cms

bkglostlepton = cms.EDProducer(
    'LostLeptonBkg',
    	HTJets          = cms.InputTag('patJetsAK5PFPt50Eta25'),
	MetTag		= cms.InputTag('patMETsPF'),
	MuonTag		= cms.InputTag('patMuonsPFIDIso'),
	ElecTag		= cms.InputTag('patElectronsIDIso'),
	EventWeightTag	= cms.InputTag("WeightProducer:weight"),
	MhtTag		= cms.InputTag('mhtPF'),
	CaloJetTag	= cms.InputTag('cleanPatJetsAK5Calo'),
	EfficiencyFileName = cms.string('MCEff.root'),
	MTWMax		= cms.double('100'),
	MTWCut		= cms.bool(True),
	MinMuPT		= cms.double('10'),
	MinElecPT	= cms.double('10'),
        HTTag	   	= cms.InputTag('htInputCol'),
        MHTTag	   	= cms.InputTag('mhtInputCol'),
        VertexCollection= cms.InputTag('goodVertices'),

)