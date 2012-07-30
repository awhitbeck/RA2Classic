import FWCore.ParameterSet.Config as cms

TreeMaker = cms.EDAnalyzer(
    'TreeMaker',
    TreeName          = cms.string('RA2Tree'),
    VertexCollection  = cms.InputTag('goodVertices'),
    HT                = cms.InputTag('htPF'),
    MHT               = cms.InputTag('mhtPF')
)
