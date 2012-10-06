# $Id: jesUncertaintyVariation_cfi.py,v 1.1 2012/10/06 15:53:24 mschrode Exp $

import FWCore.ParameterSet.Config as cms

# Produces a new jet collection, with the jets'
# four-momentum varied by the JES uncertainty.
jesUncertaintyVariation = cms.EDProducer(
    'JESUncertaintyVariation',
    Jets       = cms.InputTag('patJets'), # The input jet collection
    JetTypeId  = cms.string('AK5PFchs'),  # Type of the input jets (to obtain the uncertainty from the data base). See https://twiki.cern.ch/twiki/bin/view/CMS/JECSupportedAlgos#Jet_notation for available types.
    Variation  = cms.string('Up')         # Either 'Up' or 'Dn' to produce jets with JES +/- 1 sigma, respectively
    )
