# $Id: treemaker_cfi.py,v 1.5 2012/09/19 13:59:20 mschrode Exp $

# Description: Writes ntuples (ROOT tree) for RA2Classic analysis
#
# The following variables are stored in the tree:
#  - "RunNum": run number (UInt_t)
#  - "LumiBlockNum": luminosity block number (UInt_t)
#  - "EvtNum": event number (UInt_t)
#  - "NumVtx": number of vertices (UShort_t)
#  - "HT": HT (Float_t)
#  - "NJets": number of jets (UShort_t)
#  - "Jet?Pt": pt of jet ?, where ? = 1,2,3 (Float_t)
#  - "Jet?Eta": eta of jet ?, where ? = 1,2,3 (Float_t)
#  - "MHT": MHT (Float_t)
#  - "DeltaPhi?": deltaPhi between jet ? and MHT, where ? = 1,2,3 (Float_t)
#
# The following optional variables are stored in the tree
#  - "Filter_<name>": decision of filter <name>, where 0 means false, 1 means true (UChar_t)
#  - "VarsDouble": list of InputTags for double-precision variables stored
#                  in the event. They are stored in the tree in Float_t
#                  precision with the names given in VarsDoubleNamesInTree or,
#                  if this is not specified, as '<InputTag::label()>'. (Float_t)


import FWCore.ParameterSet.Config as cms

TreeMaker = cms.EDAnalyzer(
    'TreeMaker',

    # Name of the output tree
    TreeName          = cms.string('RA2Tree'),

    # collection from which the tree variable "NumVtx" is determined
    VertexCollection  = cms.InputTag('goodVertices'),

    # the value of HT. This is taken from the event and not computed by the TreeMaker.
    HT                = cms.InputTag('htPF'),
    # jet collection that has been used to compute HT. The tree variables "NJets", "Jet?Pt", and "Jet?Eta" are taken from this collection.
    HTJets            = cms.InputTag('patJetsAK5PFPt50Eta25'),

    # the MHT vector. This is taken from the event and not computed by the TreeMaker.
    MHT               = cms.InputTag('mhtPF'),
    # jet collection that has been used to compute MHT. The tree variables "DeltaPhi?" are computed from this collection and from "MHT".
    MHTJets           = cms.InputTag('patJetsAK5PFPt30'),

    # List of InputTags for double-precision variables (double) stored in
    # the event. (For space reason, they are stored as Float_t in the tree.)
    VarsDouble        = cms.VInputTag(),
    # Names of the double-precision variables as stored in the tree. If
    # this vector is not specified, the generic names "<InputTag::label()>"
    # are used.
    VarsDoubleNamesInTree = cms.vstring(),

    # list of filter decisions (bool) written from filters in tag mode
    # will be stored as "Filter_..."
    Filters           = cms.VInputTag()
)
