# $Id: filterSelection_cff.py,v 1.2 2012/10/30 21:13:23 mschrode Exp $
#

import FWCore.ParameterSet.Config as cms
from SandBox.Skims.filterBoolean_cfi import booleanFilter

HBHENoiseFilter = booleanFilter.clone(
    ResultSource = cms.InputTag("HBHENoiseFilterRA2","HBHENoiseFilterResult","PAT")
    )
beamHaloFilter = booleanFilter.clone(
    ResultSource = cms.InputTag("beamHaloFilter")
    )
eeNoiseFilter = booleanFilter.clone(
    ResultSource = cms.InputTag("eeNoiseFilter")
    )
trackingFailureFilter = booleanFilter.clone(
    ResultSource = cms.InputTag("trackingFailureFilter")
    )
inconsistentMuonFilter = booleanFilter.clone(
    ResultSource = cms.InputTag("inconsistentMuons")
    )
greedyMuonFilter = booleanFilter.clone(
    ResultSource = cms.InputTag("greedyMuons")
    )
ecalTPFilter = booleanFilter.clone(
    ResultSource = cms.InputTag("ra2EcalTPFilter")
    )
ecalBEFilter = booleanFilter.clone(
    ResultSource = cms.InputTag("ra2EcalBEFilter")
    )
hcalLaserFilter = booleanFilter.clone(
    ResultSource = cms.InputTag("hcalLaserEventFilter")
    )
ecalLaserFilter = booleanFilter.clone(
    ResultSource= cms.InputTag("ecalLaserCorrFilter")
    )
eeBadScFilter = booleanFilter.clone(
    ResultSource = cms.InputTag("eeBadScFilter")
    )
manyStripClustersFilter = booleanFilter.clone(
    ResultSource = cms.InputTag("manystripclus53X")
    )
tooManyStripClustersFilter = booleanFilter.clone(
    ResultSource = cms.InputTag("toomanystripclus53X")
    )
logErrorTooManyClustersFilter = booleanFilter.clone(
    ResultSource = cms.InputTag("logErrorTooManyClusters")
    )


filterSelection = cms.Sequence(
    HBHENoiseFilter *
    beamHaloFilter *
    #eeNoiseFilter *
    trackingFailureFilter *
    inconsistentMuonFilter *
    greedyMuonFilter *
    ecalTPFilter *
    ecalBEFilter *
    hcalLaserFilter *
    ecalLaserFilter *
    eeBadScFilter *
    ~manyStripClustersFilter *
    ~tooManyStripClustersFilter *
    ~logErrorTooManyClustersFilter
    )
