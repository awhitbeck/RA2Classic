
import FWCore.ParameterSet.Config as cms

RecoMuon = cms.EDProducer(
    'RecoMuon',
	HTJets          = cms.InputTag('patJetsAK5PFPt50Eta25'),
	MetTag		= cms.InputTag('patMETsPF'),
	CaloJetTag	= cms.InputTag('cleanPatJetsAK5Calo'),
	GenTag		= cms.InputTag('genParticles'),
	MuonIsoTag	= cms.InputTag('patMuonsPFIDIso'),
	MuonRecoTag	= cms.InputTag('patMuonsPFID'),
	ElecIsoTag	= cms.InputTag('patElectronsIDIso'),
	EventWeightTag	= cms.InputTag("WeightProducer:weight"),
	MhtTag		= cms.InputTag('mhtPF'),
	MTWMax		= cms.double('100'),
	MTWCut		= cms.bool(True),
	MinMuPT		= cms.double('10'),
	MinElecPT	= cms.double('10'),
        HTTag	   	= cms.InputTag('htInputCol'),
        MHTTag	   	= cms.InputTag('mhtInputCol'),
        VertexCollection= cms.InputTag('goodVertices'),
	debug		= cms.bool(False),
)