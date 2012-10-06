# $Id: $

# Sequences to produce pat::Jet collections with
# varied JES

import FWCore.ParameterSet.Config as cms

from RA2Classic.Utils.jesUncertaintyVariation_cfi import jesUncertaintyVariation

# --- For AK5PF jets ----------------------------------

# Helper modules: produce the varied jet collections
patJetsAK5PFJESUp = jesUncertaintyVariation.clone(
    Jets       = cms.InputTag('patJetsAK5PF'),
    JetTypeId  = cms.string('AK5PF'),
    Variation  = cms.string('Up')
    )
patJetsAK5PFJESDn = patJetsAK5PFJESUp.clone(
    Variation  = cms.string('Dn')
    )

# Sequence for usage in config
varyJESPatJetsAK5PF = cms.Sequence(
    patJetsAK5PFJESDn *
    patJetsAK5PFJESUp
    )


# --- For AK5PF CHS jets -------------------------------

# Helper modules: produce the varied jet collections
patJetsPFJESUp = jesUncertaintyVariation.clone(
    Jets       = cms.InputTag('patJetsPF'),
    JetTypeId  = cms.string('AK5PFchs'),
    Variation  = cms.string('Up')
    )
patJetsPFJESDn = patJetsPFJESUp.clone(
    Variation  = cms.string('Dn')
    )

# Sequence for usage in config
varyJESPatJetsPF = cms.Sequence(
    patJetsPFJESDn *
    patJetsPFJESUp
    )

