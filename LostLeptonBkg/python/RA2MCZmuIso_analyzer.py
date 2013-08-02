import FWCore.ParameterSet.Config as cms

process = cms.Process("TagProbe")
process.source = cms.Source("EmptySource")
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.destinations = ['cout', 'cerr']
process.MessageLogger.cerr.FwkReport.reportEvery = 1000


#### constants  data


#InputFileName = "/scratch/hh/dust/naf/cms/user/draeger/results/Z-MC.root"
InputFileName = "/scratch/adraeger/Z-MC.root"

OutputFilePrefix = "efficiency-data-"

HLTDef = "probe_passingHLT"
PDFName = "gaussPlusLinear"
isMC = True



#specifies the binning of parameters
EfficiencyBins = cms.PSet(
    HT = cms.vdouble(500, 800, 1500 ),
    NJets = cms.vdouble( 3,4,7,20 ), 
    MuIsoDeltaR30GeVJet = cms.vdouble(0.01, 0.5, 1.0, 3.),
    MuIsoProbePt = cms.vdouble(10, 40, 200),
    MuIsoRelPT30GeVJet = cms.vdouble(0.01, 0.5, 1, 1.5, 2, 2.5, 5),
    MuIsoProbeEta = cms.vdouble(-2.1 ,-1.8 ,-1.4 ,-1.0 ,-.8 ,-0.6 ,-0.4 ,-0.2 ,0.2 ,0.4 ,0.6 ,0.8 ,1.0 ,1.4 ,1.8 ,2.1),


)
## for super clusters


#### For data: except for HLT step
EfficiencyBinningSpecification = cms.PSet(
    #specifies what unbinned variables to include in the dataset, the mass is needed for the fit
    UnbinnedVariables = cms.vstring("IsoMuInvariantMass"),
    #specifies the binning of parameters
    BinnedVariables = cms.PSet(EfficiencyBins),
    #first string is the default followed by binRegExp - PDFname pairs
    BinToPDFmap = cms.vstring(PDFName)
)










#### do the analyzing
process.MuIso= cms.EDAnalyzer("TagProbeFitTreeAnalyzer",
    # IO parameters:
    InputFileNames = cms.vstring(InputFileName),
    InputDirectoryName = cms.string("tapTreeMuIso"),
    InputTreeName = cms.string("TAPtreeProducer"),
    OutputFileName = cms.string("MuIsoMC.root"),
                                                 
    #numbrer of CPUs to use for fitting
    NumCPU = cms.uint32(6),
    # specifies wether to save the RooWorkspace containing the data for each bin and
    # the pdf object with the initial and final state snapshots
    SaveWorkspace = cms.bool(False),
    floatShapeParameters = cms.bool(True),
    Variables = cms.PSet(
        IsoMuInvariantMass = cms.vstring("Tag-Probe Mass", "60.0", "120.0", "GeV/c^{2}"),
        HT = cms.vstring("H_{T}", "500","2000", "GeV/c"),
        NJets = cms.vstring("NJets", "3", "15", ""),
	MuIsoDeltaR30GeVJet = cms.vstring("DeltaR30GevJet","0.01","3",""),
	MuIsoProbePt = cms.vstring("#mu p_{T}","10","200",""),
	MuIsoRelPT30GeVJet = cms.vstring("#mu p_{T}/ jet p_{T}","0.1","10",""),
	MuIsoProbeEta = cms.vstring("#mu #eta","-2.4","2.4",""),

    ),    
		    
		      
			
		   
    Categories = cms.PSet(
        MuIsoPass = cms.vstring("MuIsoPass", "dummy[pass=1,fail=0]"), 
##         probe_isWP95 = cms.vstring("probe_isWP95", "dummy[pass=1,fail=0]"),
##         probe_isCicHyperTight2 = cms.vstring("probe_isCicHyperTight2", "dummy[pass=1,fail=0]"),
##         probe_isCicHyperTight3 = cms.vstring("probe_isCicHyperTight3", "dummy[pass=1,fail=0]"),
##         probe_isCicHyperTight4 = cms.vstring("probe_isCicHyperTight4", "dummy[pass=1,fail=0]"),         
    ),
    # defines all the PDFs that will be available for the efficiency calculations; uses RooFit's "factory" syntax;
    # each pdf needs to define "signal", "backgroundPass", "backgroundFail" pdfs, "efficiency[0.9,0,1]" and "signalFractionInPassing[0.9]" are used for initial values  
    PDFs = cms.PSet(
			    
			       
				  
        gaussPlusLinear = cms.vstring(
            "Voigtian::signal(IsoMuInvariantMass, mean[91.2, 84.0, 98.0], width[2.4, 0.5, 5.0], sigma[5., 1., 12.0])",
            "RooExponential::backgroundPass(IsoMuInvariantMass, cPass[0,-2,2])",
            "RooExponential::backgroundFail(IsoMuInvariantMass, cFail[0,-2,2])",
            "efficiency[0.95,0,1]",
            "signalFractionInPassing[0.95]"
        ),
        gaussPlusQuadratic = cms.vstring(
             "Voigtian::signal(IsoMuInvariantMass, mean[91.2, 89.0, 93.0], width[2.4, 0.5, 5.0], sigma[5., 1., 12.0])",
             "RooExponential::backgroundPass(IsoMuInvariantMass, cPass[0,-2,2])",
#             "Chebychev::backgroundPass(mass, {cPass1[0,-2,2], cPass2[0,-2,2]})",
             "Chebychev::backgroundFail(IsoMuInvariantMass, {cFail1[0,-2,2], cFail2[0,-2,2]})",
             "efficiency[0.95,0,1]", 
             "signalFractionInPassing[0.95]"
        ),
        gaussPlusArgus = cms.vstring(
            "Voigtian::signal(IsoMuInvariantMass, mean[91.2, 89.0, 93.0], width[2.4, 0.5, 5.0], sigma[5., 1., 12.0])",
            "RooExponential::backgroundPass(IsoMuInvariantMass, cPass[0,-5,5])",
            "ArgusBG::backgroundFail(IsoMuInvariantMass, cFail1[86.6, 70, 100], cFail2[-2.8, -100, 100])",
            "efficiency[0.95,0,1]",
            "signalFractionInPassing[0.95]"
        ),
        gaussPlusCMS = cms.vstring(
            "Voigtian::signal(IsoMuInvariantMass, mean[91.2, 89.0, 93.0], width[2.4, 0.5, 5.0], sigma[5., 1., 12.0])",
#            "RooExponential::backgroundPass(mass, cPass[0,-2,2])",
            "RooCMSShape::backgroundPass(IsoMuInvariantMass, alphaPass[60.,30.,90.], betaPass[0.001, 0.,0.1], betaPass, peakPass[90.0])",
            "RooCMSShape::backgroundFail(IsoMuInvariantMass, alphaFail[60.,30.,90.], betaFail[0.001, 0.,0.1], betaFail, peakFail[90.0])",
            "efficiency[0.95,0,1]",
            "signalFractionInPassing[0.95]"
        ),
	gaussPlusCubic = cms.vstring(
             "Voigtian::signal(IsoMuInvariantMass, mean[91.2, 84.0, 98.0], width[2.4, 0.5, 5.0], sigma[5., 1., 12.0])",
#             "Chebychev::backgroundPass(IsoMuInvariantMass, {cPass1[0,-2,2], cPass2[0,-2,2],cPass3[0,-2,2]})",			 
#             "Chebychev::backgroundFail(IsoMuInvariantMass, {cFail1[0,-2,2], cFail2[0,-2,2],cFail3[0,-2,2]})",		     
             "Chebychev::backgroundPass(IsoMuInvariantMass, {cPass1[0,-2,2], cPass2[0,-2,2],cPass3[0,-2,2],cPass4[0,-2,2]})",			 
             "Chebychev::backgroundFail(IsoMuInvariantMass, {cFail1[0,-2,2], cFail2[0,-2,2],cFail3[0,-2,2],cFail4[0,-2,2]})",		     
             "efficiency[0.95,0,1]", 
             "signalFractionInPassing[0.95]"				 
		),
#        pdfSignalPlusBackground = cms.vstring(
##     "CBExGaussShape::signalRes(mass, mean[2.0946e-01], sigma[8.5695e-04],alpha[3.8296e-04], n[6.7489e+00], sigma_2[2.5849e+00], frac[6.5704e-01])",  ### the signal function goes here
#     "CBExGaussShape::signalResPass(mass, meanP[90.], sigmaP[1, 0., 3.],alphaP[3.8296e-04], nP[6.7489e+00], sigmaP_2[2.5849e+00], fracP[6.5704e-01,0,1])",  ### signal resolution for "pass" sample
 #    "CBExGaussShape::signalResFail(mass, meanF[2.0946e-01, -5., 5.], sigmaF[8.5695e-04, 0., 5.],alphaF[3.8296e-04], nF[6.7489e+00], sigmaF_2[2.5849e+00], fracF[6.5704e-01])",  ### signal resolution for "fail" sample     
 #   "ZGeneratorLineShape::signalPhy(mass)", ### NLO line shape
 #   "RooCMSShape::backgroundPass(mass, alphaPass[60.,50.,70.], betaPass[0.001, 0.,0.1], betaPass, peakPass[90.0])",
 #   "RooCMSShape::backgroundFail(mass, alphaFail[60.,50.,70.], betaFail[0.001, 0.,0.1], betaFail, peakFail[90.0])",
 #   "FCONV::signalPass(mass, signalPhy, signalResPass)",
 #   "FCONV::signalFail(mass, signalPhy, signalResFail)",     
 #   "efficiency[0.9,0,1]",
 #   "signalFractionInPassing[1.0]"     
    #"Gaussian::signal(mass, mean[91.2, 89.0, 93.0], sigma[2.3, 0.5, 10.0])",
    #"RooExponential::backgroundPass(mass, cPass[-0.02,-5,0])",
    #"RooExponential::backgroundFail(mass, cFail[-0.02,-5,0])",
    #"efficiency[0.9,0,1]",
    #"signalFractionInPassing[0.9]"
 #       ),
    ),

    Efficiencies = cms.PSet(
        #the name of the parameter set becomes the name of the directory
#    MuId = cms.PSet(
#         EfficiencyCategoryAndState = cms.vstring("MuIsoPass","pass"),
#         UnbinnedVariables = cms.vstring("IsoMuInvariantMass"),
#         BinnedVariables = cms.PSet(
#                   HT = cms.vdouble(500, 800, 1500 ),
#    		   NJets = cms.vdouble( 3,4,7,20 ),
#         ),
#         BinToPDFmap = cms.vstring("gaussPlusCubic")
#        ),
#    MuIso_deltaR = cms.PSet(
#         EfficiencyCategoryAndState = cms.vstring("MuIsoPass","pass"),
#         UnbinnedVariables = cms.vstring("IsoMuInvariantMass"),
#         BinnedVariables = cms.PSet(
#                   MuIsoDeltaR30GeVJet = cms.vdouble(0.01, 0.5, 1.0, 3.),
#    		   MuIsoProbePt = cms.vdouble(10, 40, 200),
#		   
#         ),
#         BinToPDFmap = cms.vstring("gaussPlusCubic")
#       ),
#    
#    MuIso_deltaR_RelPt = cms.PSet(
#         EfficiencyCategoryAndState = cms.vstring("MuIsoPass","pass"),
#         UnbinnedVariables = cms.vstring("IsoMuInvariantMass"),
#         BinnedVariables = cms.PSet(
#                   MuIsoDeltaR30GeVJet = cms.vdouble(0.01, 0.5, 1.0, 3.),
#    		   MuIsoRelPT30GeVJet = cms.vdouble(0.01, 0.5, 1, 1.5, 2, 2.5, 5),
#		   
#         ),
#         BinToPDFmap = cms.vstring("gaussPlusCubic")
#        ),
#    MuIso_Pt = cms.PSet(
#         EfficiencyCategoryAndState = cms.vstring("MuIsoPass","pass"),
#         UnbinnedVariables = cms.vstring("IsoMuInvariantMass"),
#         BinnedVariables = cms.PSet(
#                   MuIsoProbePt = cms.vdouble(10, 15, 20, 30., 50,100)
#		   
#         ),
#         BinToPDFmap = cms.vstring("gaussPlusCubic")
#        ),
    MuIso_Eta = cms.PSet(
         EfficiencyCategoryAndState = cms.vstring("MuIsoPass","pass"),
         UnbinnedVariables = cms.vstring("IsoMuInvariantMass"),
         BinnedVariables = cms.PSet(
		   MuIsoProbePt = cms.vdouble(20,500),
                   MuIsoProbeEta = cms.vdouble(-2.1 ,-1.8 ,-1.4 ,-1.0 ,-.8 ,-0.6 ,-0.4 ,-0.2 ,0.2 ,0.4 ,0.6 ,0.8 ,1.0 ,1.4 ,1.8 ,2.1)
		   
         ),
         BinToPDFmap = cms.vstring("gaussPlusCubic")
        ),

    )




)





### run the final pass 
process.fit = cms.Path(
		process.MuIso 

  #  		process.CicSuperTightToHLT +
 #   		process.CicHyperTight1ToHLT ##+
		)






