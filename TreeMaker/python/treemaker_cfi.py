# Description: Writes ntuples (ROOT tree) for RA2Classic analysis
#
# The following variables are stored in the tree:
#  - "RunNum": run number (UInt_t)
#  - "LumiBlockNum": luminosity block number (UInt_t)
#  - "EvtNum": event number (UInt_t)
#  - "Weight": event weight (Float_t)
#  - "NumVtx": number of vertices (UShort_t)
#  - "HT": HT (Float_t)
#  - "NJets": number of jets (UShort_t)
#  - "Jet?Pt": pt of jet ?, where ? = 1,2,3 (Float_t)
#  - "Jet?Eta": eta of jet ?, where ? = 1,2,3 (Float_t)
#  - "MHT": MHT (Float_t)
#  - "DeltaPhi?": deltaPhi between jet ? and MHT, where ? = 1,2,3 (Float_t)

import FWCore.ParameterSet.Config as cms

TreeMaker = cms.EDAnalyzer(
    'TreeMaker',

    # Name of the output tree
    TreeName          = cms.string('RA2Tree'),

    # name of event weight
    Weight            = cms.InputTag('weight'),

    # collection from which the tree variable "NumVtx" is determined
    VertexCollection  = cms.InputTag('goodVertices'),

    # the value of HT. This is taken from the event and not computed by the TreeMaker.
    HT                = cms.InputTag('htPF'),
    # jet collection that has been used to compute HT. The tree variables "NJets", "Jet?Pt", and "Jet?Eta" are taken from this collection.
    HTJets            = cms.InputTag('patJetsAK5PFPt50Eta25'),

    # the MHT vector. This is taken from the event and not computed by the TreeMaker.
    MHT               = cms.InputTag('mhtPF'),
    # jet collection that has been used to compute MHT. The tree variables "DeltaPhi?" are computed from this collection and from "MHT".
    MHTJets           = cms.InputTag('patJetsAK5PFPt30')
)
