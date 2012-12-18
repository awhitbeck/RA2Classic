# $Id: $

import FWCore.ParameterSet.Config as cms

# Define CHS correctors
from JetMETCorrections.Configuration.DefaultJEC_cff import *
ak5PFchsL1Fastjet           = ak5PFL1Fastjet.clone( correctors = cms.vstring('ak5PFchsL1Fastjet') )
ak5PFchsL2Relative          = ak5PFL2Relative.clone( correctors = cms.vstring('ak5PFchsL2Relative') )
ak5PFchsL3Absolute          = ak5PFL3Absolute.clone( correctors = cms.vstring('ak5PFchsL2Absolute') )
ak5PFchsResidual            = ak5PFResidual.clone( correctors = cms.vstring('ak5PFchsResidual') )
ak5PFchsL1FastL2L3Residual  = ak5PFL1FastL2L3Residual.clone( correctors = cms.vstring('ak5PFchsL1Fastjet', 'ak5PFchsL2Relative', 'ak5PFchsL3Absolute' , 'ak5PFchsResidual') )

jesChange = cms.EDProducer(
    'JESChange',
    Jets       = cms.InputTag('patJetsPF'), # The input jet collection
    METs       = cms.InputTag('patMETsPF'), # The input met collection
    JECLevel   = cms.string('ak5PFchsL1FastL2L3Residual')
    )
