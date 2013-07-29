//#saving the histogramms for the efficiencies

#include <iostream>
#include <strstream>
#include <iomanip>
#include <TH2F.h>
#include <TFile.h>
#include <TGraph.h>
#include <vector>
#include <TString.h>
#include <TTree.h>
void dataCardPrint()
{

   // input 
  // number of search bins
   int searchbins = 36;
gROOT->SetBatch(true);
  std::cout.setf(ios::fixed);
  std::cout<<setprecision(2);
  vector<double> htBins;
   htBins.clear();
  vector<double> mhtBins;
   mhtBins.clear();
  vector<int> njetsBins;
   njetsBins.clear();

  // fill all the bins

  htBins.push_back(500);
  htBins.push_back(800);
  htBins.push_back(1000);
  htBins.push_back(1250);
  htBins.push_back(1500);
  htBins.push_back(10000);

  mhtBins.push_back(200);
  mhtBins.push_back(300);
  mhtBins.push_back(450);
  mhtBins.push_back(600);
  mhtBins.push_back(10000);

  njetsBins.push_back(3);
  njetsBins.push_back(6);
  njetsBins.push_back(8);
  njetsBins.push_back(10000);


  vector<double> predictions;
   predictions.clear();
  vector<double> statUncertainty;
   predictions.clear();

  vector<double> mtwup;
   mtwup.clear();

  vector<double> mtwdn;
   mtwdn.clear();

  vector<double> dilepup;
   dilepup.clear();

  vector<double> dilepdn;
   dilepdn.clear();

  vector<double> nonclosureup;
   nonclosureup.clear();

  vector<double> nonclosuredn;
   nonclosuredn.clear();

  vector<double> accup;
   accup.clear();

  vector<double> accdn;
   accdn.clear();

  vector<double> diboup;
   diboup.clear();

  vector<double> dibodn;
   dibodn.clear();

  vector<double> muisoup;
   muisoup.clear();

  vector<double> muisodn;
   muisodn.clear();

  vector<double> elecisoup;
   elecisoup.clear();

  vector<double> elecisodn;
   elecisodn.clear();


  vector<double> murecoup;
   murecoup.clear();

  vector<double> murecodn;
   murecodn.clear();

  vector<double> elecrecoup;
   elecrecoup.clear();

  vector<double> elecrecodn;
   elecrecodn.clear();




 TFile* fInput = TFile::Open("data.root");
  TDirectory *dPr = (TDirectory*)fInput->Get("LostLeptonBkgProducer");
  TTree *tPr = new TTree();
  tPr = (TTree*) dPr->Get("LostLeptonBkg");
   tPr->Draw("HT>> outhist2","(muPromtMatched>0.5 && resultBBBWMTWDiLep<10 + MHT>200 + NJets>2.1 && HT >500)*resultBBBWMTWDiLep","pe");

   std::cout<<"Baseline predictionJamJam"<<outhist2->Integral()<<"  ";

//   statUncertainty.push_back(outhist2->Integral() * sqrt(outhist2->GetEntrie()));

   std::cout<<"LostLeptonPrediction for each search bin:"<<std::endl;

   std::cout<<"---------------------------------------------------------------------------"<<std::endl;
   std::cout<<"---------------------------------------------------------------------------"<<std::endl;
   std::cout<<"# bin1 is for nJets [3, 5], HT [500, 800] and MHT [200, 300]; bin2 is for nJets [3, 5], HT [500, 800] and MHT  [300, 450] ..."<<std::endl;

   std::cout<<"channel = ";
   for (int i=0;i<searchbins;i++)
   {
    std::cout<<"bin"<<i+1<<"; ";

   }




  // go though all the bins
   // NJets 3,5 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWDiLep");
if( outhist2->Integral()<0.001) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1); else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );



   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*resultBBBWMTWDiLep");
if( outhist2->Integral()<0.001) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1); else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*resultBBBWMTWDiLep");
if( outhist2->Integral()<0.001) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1); else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*resultBBBWMTWDiLep");
if( outhist2->Integral()<0.001) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1); else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );





   // NJets 3,5 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDiLep");
//if( outhist2->Integral()<0.001) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
//     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1); else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWDiLep");
if( outhist2->Integral()<0.001) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1); else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*resultBBBWMTWDiLep");
if( outhist2->Integral()<0.001) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1); else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*resultBBBWMTWDiLep");
if( outhist2->Integral()<0.001) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1); else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*resultBBBWMTWDiLep");
if( outhist2->Integral()<0.001) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1); else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );




   // NJets 3,5 HT 1000,1250
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDiLep");
//if( outhist2->Integral()<0.001) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
//     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1); else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWDiLep");
if( outhist2->Integral()<0.001) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1); else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*resultBBBWMTWDiLep");
if( outhist2->Integral()<0.001) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1); else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*resultBBBWMTWDiLep");
if( outhist2->Integral()<0.001) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1); else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*resultBBBWMTWDiLep");
if( outhist2->Integral()<0.001) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1); else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );





   // NJets 3,5 HT 1250,1500
 //  tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDiLep");
//if( outhist2->Integral()<0.001) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
 //    if (outhist2->Integral() <0.2) statUncertainty.push_back(-1); else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWDiLep");
if( outhist2->Integral()<0.001) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1); else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*resultBBBWMTWDiLep");
if( outhist2->Integral()<0.001) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1); else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 450)*resultBBBWMTWDiLep");
if( outhist2->Integral()<0.001) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1); else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );




   // NJets 3,5 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDiLep");
//if( outhist2->Integral()<0.001) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
 //    if (outhist2->Integral() <0.2) statUncertainty.push_back(-1); else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWDiLep");
if( outhist2->Integral()<0.001) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1); else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 300 )*resultBBBWMTWDiLep");
if( outhist2->Integral()<0.001) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1); else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );










   // NJets 6,7 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWDiLep");
if( outhist2->Integral()<0.001) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1); else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*resultBBBWMTWDiLep");
if( outhist2->Integral()<0.001) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1); else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*resultBBBWMTWDiLep");
if( outhist2->Integral()<0.001) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1); else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );





   // NJets 6,7 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDiLep");
//if( outhist2->Integral()<0.001) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
 //    if (outhist2->Integral() <0.2) statUncertainty.push_back(-1); else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWDiLep");
if( outhist2->Integral()<0.001) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1); else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*resultBBBWMTWDiLep");
if( outhist2->Integral()<0.001) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1); else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*resultBBBWMTWDiLep");
if( outhist2->Integral()<0.001) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1); else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );






   // NJets 6,7 HT 1000,1250
 //  tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDiLep");
//if( outhist2->Integral()<0.001) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
 //    if (outhist2->Integral() <0.2) statUncertainty.push_back(-1); else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWDiLep");
if( outhist2->Integral()<0.001) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1); else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*resultBBBWMTWDiLep");
if( outhist2->Integral()<0.001) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1); else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*resultBBBWMTWDiLep");
if( outhist2->Integral()<0.001) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1); else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );







   // NJets 6,7 HT 1250,1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDiLep");
//if( outhist2->Integral()<0.001) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
//     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1); else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWDiLep");
if( outhist2->Integral()<0.001) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1); else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*resultBBBWMTWDiLep");
if( outhist2->Integral()<0.001) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1); else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 450)*resultBBBWMTWDiLep");
if( outhist2->Integral()<0.001) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1); else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );




   // NJets 6,7 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDiLep");
//if( outhist2->Integral()<0.001) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
//     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1); else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWDiLep");
if( outhist2->Integral()<0.001) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1); else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 300 )*resultBBBWMTWDiLep");
if( outhist2->Integral()<0.001) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1); else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );



// --------------------------------------------------------------------------------------------------






   // NJets 8 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 7.5 && MHT > 200 )*resultBBBWMTWDiLep");
if( outhist2->Integral()<0.001) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1); else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );






   // NJets 8 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 7.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDiLep");
//if( outhist2->Integral()<0.001) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
 //    if (outhist2->Integral() <0.2) statUncertainty.push_back(-1);else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 7.5 && MHT > 200 )*resultBBBWMTWDiLep");
if( outhist2->Integral()<0.001) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1);else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );





   // NJets 8 HT 1000,1250
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 7.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDiLep");
//if( outhist2->Integral()<0.001) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
//     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1);else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 7.5 && MHT > 200 )*resultBBBWMTWDiLep");
if( outhist2->Integral()<0.001) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1);else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );








   // NJets 8 HT 1250,1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 7.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDiLep");
//if( outhist2->Integral()<0.001) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
 //    if (outhist2->Integral() <0.2) statUncertainty.push_back(-1);else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 7.5 && MHT > 200  )*resultBBBWMTWDiLep");
if( outhist2->Integral()<0.001) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1);else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );




   // NJets 8 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 7.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDiLep");
//if( outhist2->Integral()<0.001) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
//     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1);else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 7.5 && MHT > 200  )*resultBBBWMTWDiLep");
if( outhist2->Integral()<0.001) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1);else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );


// --------------------------------------+++++++++++++++++++++++++++--------------------------------------
// Uncertainties



  // go though all the bins
   // NJets 3,5 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWUp");
if( outhist2->Integral()<0.001) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
      



   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*resultBBBWMTWUp");
if( outhist2->Integral()<0.001) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*resultBBBWMTWUp");
if( outhist2->Integral()<0.001) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*resultBBBWMTWUp");
if( outhist2->Integral()<0.001) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
      





   // NJets 3,5 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWUp");
//if( outhist2->Integral()<0.001) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWUp");
if( outhist2->Integral()<0.001) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*resultBBBWMTWUp");
if( outhist2->Integral()<0.001) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*resultBBBWMTWUp");
if( outhist2->Integral()<0.001) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*resultBBBWMTWUp");
if( outhist2->Integral()<0.001) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
      




   // NJets 3,5 HT 1000,1250
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWUp");
//if( outhist2->Integral()<0.001) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWUp");
if( outhist2->Integral()<0.001) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*resultBBBWMTWUp");
if( outhist2->Integral()<0.001) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*resultBBBWMTWUp");
if( outhist2->Integral()<0.001) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*resultBBBWMTWUp");
if( outhist2->Integral()<0.001) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
      





   // NJets 3,5 HT 1250,1500
 //  tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWUp");
//if( outhist2->Integral()<0.001) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWUp");
if( outhist2->Integral()<0.001) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*resultBBBWMTWUp");
if( outhist2->Integral()<0.001) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 450)*resultBBBWMTWUp");
if( outhist2->Integral()<0.001) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
      




   // NJets 3,5 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWUp");
//if( outhist2->Integral()<0.001) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWUp");
if( outhist2->Integral()<0.001) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 300 )*resultBBBWMTWUp");
if( outhist2->Integral()<0.001) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
      










   // NJets 6,7 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWUp");
if( outhist2->Integral()<0.001) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*resultBBBWMTWUp");
if( outhist2->Integral()<0.001) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*resultBBBWMTWUp");
if( outhist2->Integral()<0.001) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
      





   // NJets 6,7 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWUp");
//if( outhist2->Integral()<0.001) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWUp");
if( outhist2->Integral()<0.001) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*resultBBBWMTWUp");
if( outhist2->Integral()<0.001) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*resultBBBWMTWUp");
if( outhist2->Integral()<0.001) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
      






   // NJets 6,7 HT 1000,1250
 //  tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWUp");
//if( outhist2->Integral()<0.001) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWUp");
if( outhist2->Integral()<0.001) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*resultBBBWMTWUp");
if( outhist2->Integral()<0.001) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*resultBBBWMTWUp");
if( outhist2->Integral()<0.001) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
      







   // NJets 6,7 HT 1250,1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWUp");
//if( outhist2->Integral()<0.001) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWUp");
if( outhist2->Integral()<0.001) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*resultBBBWMTWUp");
if( outhist2->Integral()<0.001) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 450)*resultBBBWMTWUp");
if( outhist2->Integral()<0.001) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
      




   // NJets 6,7 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWUp");
//if( outhist2->Integral()<0.001) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWUp");
if( outhist2->Integral()<0.001) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 300 )*resultBBBWMTWUp");
if( outhist2->Integral()<0.001) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
      



// --------------------------------------------------------------------------------------------------






   // NJets 8 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 7.5 && MHT > 200 )*resultBBBWMTWUp");
if( outhist2->Integral()<0.001) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
      






   // NJets 8 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 7.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWUp");
//if( outhist2->Integral()<0.001) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
 //     

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 7.5 && MHT > 200 )*resultBBBWMTWUp");
if( outhist2->Integral()<0.001) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
      





   // NJets 8 HT 1000,1250
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 7.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWUp");
//if( outhist2->Integral()<0.001) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
//      

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 7.5 && MHT > 200 )*resultBBBWMTWUp");
if( outhist2->Integral()<0.001) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
      








   // NJets 8 HT 1250,1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 7.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWUp");
//if( outhist2->Integral()<0.001) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
 //     

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 7.5 && MHT > 200  )*resultBBBWMTWUp");
if( outhist2->Integral()<0.001) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
      




   // NJets 8 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 7.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWUp");
//if( outhist2->Integral()<0.001) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
//      

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 7.5 && MHT > 200  )*resultBBBWMTWUp");
if( outhist2->Integral()<0.001) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
      



// ------------------------------mtw down










  // go though all the bins
   // NJets 3,5 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWDown");
if( outhist2->Integral()<0.001) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
      



   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*resultBBBWMTWDown");
if( outhist2->Integral()<0.001) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*resultBBBWMTWDown");
if( outhist2->Integral()<0.001) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*resultBBBWMTWDown");
if( outhist2->Integral()<0.001) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
      





   // NJets 3,5 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDown");
//if( outhist2->Integral()<0.001) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWDown");
if( outhist2->Integral()<0.001) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*resultBBBWMTWDown");
if( outhist2->Integral()<0.001) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*resultBBBWMTWDown");
if( outhist2->Integral()<0.001) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*resultBBBWMTWDown");
if( outhist2->Integral()<0.001) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
      




   // NJets 3,5 HT 1000,1250
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDown");
//if( outhist2->Integral()<0.001) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWDown");
if( outhist2->Integral()<0.001) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*resultBBBWMTWDown");
if( outhist2->Integral()<0.001) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*resultBBBWMTWDown");
if( outhist2->Integral()<0.001) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*resultBBBWMTWDown");
if( outhist2->Integral()<0.001) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
      





   // NJets 3,5 HT 1250,1500
 //  tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDown");
//if( outhist2->Integral()<0.001) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWDown");
if( outhist2->Integral()<0.001) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*resultBBBWMTWDown");
if( outhist2->Integral()<0.001) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 450)*resultBBBWMTWDown");
if( outhist2->Integral()<0.001) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
      




   // NJets 3,5 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDown");
//if( outhist2->Integral()<0.001) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWDown");
if( outhist2->Integral()<0.001) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 300 )*resultBBBWMTWDown");
if( outhist2->Integral()<0.001) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
      










   // NJets 6,7 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWDown");
if( outhist2->Integral()<0.001) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*resultBBBWMTWDown");
if( outhist2->Integral()<0.001) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*resultBBBWMTWDown");
if( outhist2->Integral()<0.001) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
      





   // NJets 6,7 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDown");
//if( outhist2->Integral()<0.001) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWDown");
if( outhist2->Integral()<0.001) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*resultBBBWMTWDown");
if( outhist2->Integral()<0.001) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*resultBBBWMTWDown");
if( outhist2->Integral()<0.001) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
      






   // NJets 6,7 HT 1000,1250
 //  tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDown");
//if( outhist2->Integral()<0.001) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWDown");
if( outhist2->Integral()<0.001) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*resultBBBWMTWDown");
if( outhist2->Integral()<0.001) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*resultBBBWMTWDown");
if( outhist2->Integral()<0.001) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
      







   // NJets 6,7 HT 1250,1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDown");
//if( outhist2->Integral()<0.001) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWDown");
if( outhist2->Integral()<0.001) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*resultBBBWMTWDown");
if( outhist2->Integral()<0.001) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 450)*resultBBBWMTWDown");
if( outhist2->Integral()<0.001) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
      




   // NJets 6,7 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDown");
//if( outhist2->Integral()<0.001) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWDown");
if( outhist2->Integral()<0.001) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 300 )*resultBBBWMTWDown");
if( outhist2->Integral()<0.001) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
      



// --------------------------------------------------------------------------------------------------






   // NJets 8 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 7.5 && MHT > 200 )*resultBBBWMTWDown");
if( outhist2->Integral()<0.001) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
      






   // NJets 8 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 7.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDown");
//if( outhist2->Integral()<0.001) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
 //     

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 7.5 && MHT > 200 )*resultBBBWMTWDown");
if( outhist2->Integral()<0.001) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
      





   // NJets 8 HT 1000,1250
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 7.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDown");
//if( outhist2->Integral()<0.001) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
//      

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 7.5 && MHT > 200 )*resultBBBWMTWDown");
if( outhist2->Integral()<0.001) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
      








   // NJets 8 HT 1250,1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 7.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDown");
//if( outhist2->Integral()<0.001) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
 //     

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 7.5 && MHT > 200  )*resultBBBWMTWDown");
if( outhist2->Integral()<0.001) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
      




   // NJets 8 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 7.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDown");
//if( outhist2->Integral()<0.001) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
//      

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 7.5 && MHT > 200  )*resultBBBWMTWDown");
if( outhist2->Integral()<0.001) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
      




// --------------------------------------------------------- di lep uncertainty





  // go though all the bins
   // NJets 3,5 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWDiLepUp");
if( outhist2->Integral()<0.001) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
      



   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*resultBBBWMTWDiLepUp");
if( outhist2->Integral()<0.001) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*resultBBBWMTWDiLepUp");
if( outhist2->Integral()<0.001) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*resultBBBWMTWDiLepUp");
if( outhist2->Integral()<0.001) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
      





   // NJets 3,5 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDiLepUp");
//if( outhist2->Integral()<0.001) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWDiLepUp");
if( outhist2->Integral()<0.001) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*resultBBBWMTWDiLepUp");
if( outhist2->Integral()<0.001) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*resultBBBWMTWDiLepUp");
if( outhist2->Integral()<0.001) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*resultBBBWMTWDiLepUp");
if( outhist2->Integral()<0.001) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
      




   // NJets 3,5 HT 1000,1250
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDiLepUp");
//if( outhist2->Integral()<0.001) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWDiLepUp");
if( outhist2->Integral()<0.001) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*resultBBBWMTWDiLepUp");
if( outhist2->Integral()<0.001) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*resultBBBWMTWDiLepUp");
if( outhist2->Integral()<0.001) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*resultBBBWMTWDiLepUp");
if( outhist2->Integral()<0.001) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
      





   // NJets 3,5 HT 1250,1500
 //  tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDiLepUp");
//if( outhist2->Integral()<0.001) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWDiLepUp");
if( outhist2->Integral()<0.001) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*resultBBBWMTWDiLepUp");
if( outhist2->Integral()<0.001) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 450)*resultBBBWMTWDiLepUp");
if( outhist2->Integral()<0.001) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
      




   // NJets 3,5 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDiLepUp");
//if( outhist2->Integral()<0.001) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWDiLepUp");
if( outhist2->Integral()<0.001) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 300 )*resultBBBWMTWDiLepUp");
if( outhist2->Integral()<0.001) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
      










   // NJets 6,7 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWDiLepUp");
if( outhist2->Integral()<0.001) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*resultBBBWMTWDiLepUp");
if( outhist2->Integral()<0.001) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*resultBBBWMTWDiLepUp");
if( outhist2->Integral()<0.001) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
      





   // NJets 6,7 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDiLepUp");
//if( outhist2->Integral()<0.001) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWDiLepUp");
if( outhist2->Integral()<0.001) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*resultBBBWMTWDiLepUp");
if( outhist2->Integral()<0.001) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*resultBBBWMTWDiLepUp");
if( outhist2->Integral()<0.001) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
      






   // NJets 6,7 HT 1000,1250
 //  tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDiLepUp");
//if( outhist2->Integral()<0.001) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWDiLepUp");
if( outhist2->Integral()<0.001) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*resultBBBWMTWDiLepUp");
if( outhist2->Integral()<0.001) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*resultBBBWMTWDiLepUp");
if( outhist2->Integral()<0.001) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
      







   // NJets 6,7 HT 1250,1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDiLepUp");
//if( outhist2->Integral()<0.001) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWDiLepUp");
if( outhist2->Integral()<0.001) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*resultBBBWMTWDiLepUp");
if( outhist2->Integral()<0.001) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 450)*resultBBBWMTWDiLepUp");
if( outhist2->Integral()<0.001) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
      




   // NJets 6,7 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDiLepUp");
//if( outhist2->Integral()<0.001) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWDiLepUp");
if( outhist2->Integral()<0.001) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 300 )*resultBBBWMTWDiLepUp");
if( outhist2->Integral()<0.001) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
      



// --------------------------------------------------------------------------------------------------






   // NJets 8 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 7.5 && MHT > 200 )*resultBBBWMTWDiLepUp");
if( outhist2->Integral()<0.001) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
      






   // NJets 8 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 7.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDiLepUp");
//if( outhist2->Integral()<0.001) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
 //     

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 7.5 && MHT > 200 )*resultBBBWMTWDiLepUp");
if( outhist2->Integral()<0.001) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
      





   // NJets 8 HT 1000,1250
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 7.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDiLepUp");
//if( outhist2->Integral()<0.001) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
//      

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 7.5 && MHT > 200 )*resultBBBWMTWDiLepUp");
if( outhist2->Integral()<0.001) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
      








   // NJets 8 HT 1250,1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 7.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDiLepUp");
//if( outhist2->Integral()<0.001) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
 //     

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 7.5 && MHT > 200  )*resultBBBWMTWDiLepUp");
if( outhist2->Integral()<0.001) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
      




   // NJets 8 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 7.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDiLepUp");
//if( outhist2->Integral()<0.001) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
//      

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 7.5 && MHT > 200  )*resultBBBWMTWDiLepUp");
if( outhist2->Integral()<0.001) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
      












  // go though all the bins
   // NJets 3,5 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWDiLepDown");
if( outhist2->Integral()<0.001) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
      



   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*resultBBBWMTWDiLepDown");
if( outhist2->Integral()<0.001) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*resultBBBWMTWDiLepDown");
if( outhist2->Integral()<0.001) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*resultBBBWMTWDiLepDown");
if( outhist2->Integral()<0.001) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
      





   // NJets 3,5 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDiLepDown");
//if( outhist2->Integral()<0.001) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWDiLepDown");
if( outhist2->Integral()<0.001) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*resultBBBWMTWDiLepDown");
if( outhist2->Integral()<0.001) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*resultBBBWMTWDiLepDown");
if( outhist2->Integral()<0.001) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*resultBBBWMTWDiLepDown");
if( outhist2->Integral()<0.001) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
      




   // NJets 3,5 HT 1000,1250
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDiLepDown");
//if( outhist2->Integral()<0.001) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWDiLepDown");
if( outhist2->Integral()<0.001) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*resultBBBWMTWDiLepDown");
if( outhist2->Integral()<0.001) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*resultBBBWMTWDiLepDown");
if( outhist2->Integral()<0.001) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*resultBBBWMTWDiLepDown");
if( outhist2->Integral()<0.001) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
      





   // NJets 3,5 HT 1250,1500
 //  tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDiLepDown");
//if( outhist2->Integral()<0.001) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWDiLepDown");
if( outhist2->Integral()<0.001) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*resultBBBWMTWDiLepDown");
if( outhist2->Integral()<0.001) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 450)*resultBBBWMTWDiLepDown");
if( outhist2->Integral()<0.001) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
      




   // NJets 3,5 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDiLepDown");
//if( outhist2->Integral()<0.001) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWDiLepDown");
if( outhist2->Integral()<0.001) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 300 )*resultBBBWMTWDiLepDown");
if( outhist2->Integral()<0.001) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
      










   // NJets 6,7 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWDiLepDown");
if( outhist2->Integral()<0.001) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*resultBBBWMTWDiLepDown");
if( outhist2->Integral()<0.001) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*resultBBBWMTWDiLepDown");
if( outhist2->Integral()<0.001) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
      





   // NJets 6,7 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDiLepDown");
//if( outhist2->Integral()<0.001) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWDiLepDown");
if( outhist2->Integral()<0.001) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*resultBBBWMTWDiLepDown");
if( outhist2->Integral()<0.001) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*resultBBBWMTWDiLepDown");
if( outhist2->Integral()<0.001) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
      






   // NJets 6,7 HT 1000,1250
 //  tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDiLepDown");
//if( outhist2->Integral()<0.001) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWDiLepDown");
if( outhist2->Integral()<0.001) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*resultBBBWMTWDiLepDown");
if( outhist2->Integral()<0.001) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*resultBBBWMTWDiLepDown");
if( outhist2->Integral()<0.001) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
      







   // NJets 6,7 HT 1250,1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDiLepDown");
//if( outhist2->Integral()<0.001) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWDiLepDown");
if( outhist2->Integral()<0.001) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*resultBBBWMTWDiLepDown");
if( outhist2->Integral()<0.001) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 450)*resultBBBWMTWDiLepDown");
if( outhist2->Integral()<0.001) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
      




   // NJets 6,7 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDiLepDown");
//if( outhist2->Integral()<0.001) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWDiLepDown");
if( outhist2->Integral()<0.001) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 300 )*resultBBBWMTWDiLepDown");
if( outhist2->Integral()<0.001) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
      



// --------------------------------------------------------------------------------------------------






   // NJets 8 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 7.5 && MHT > 200 )*resultBBBWMTWDiLepDown");
if( outhist2->Integral()<0.001) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
      






   // NJets 8 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 7.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDiLepDown");
//if( outhist2->Integral()<0.001) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
 //     

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 7.5 && MHT > 200 )*resultBBBWMTWDiLepDown");
if( outhist2->Integral()<0.001) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
      





   // NJets 8 HT 1000,1250
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 7.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDiLepDown");
//if( outhist2->Integral()<0.001) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
//      

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 7.5 && MHT > 200 )*resultBBBWMTWDiLepDown");
if( outhist2->Integral()<0.001) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
      








   // NJets 8 HT 1250,1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 7.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDiLepDown");
//if( outhist2->Integral()<0.001) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
 //     

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 7.5 && MHT > 200  )*resultBBBWMTWDiLepDown");
if( outhist2->Integral()<0.001) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
      




   // NJets 8 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 7.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDiLepDown");
//if( outhist2->Integral()<0.001) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
//      

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 7.5 && MHT > 200  )*resultBBBWMTWDiLepDown");
if( outhist2->Integral()<0.001) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
      









// --------------------------------------------------------- di lep uncertainty





  // go though all the bins
   // NJets 3,5 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultWeightBBBNoCloUp");
if( outhist2->Integral()<0.001) nonclosureup.push_back(-1);else nonclosureup.push_back(outhist2->Integral());
      



   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*resultWeightBBBNoCloUp");
if( outhist2->Integral()<0.001) nonclosureup.push_back(-1);else nonclosureup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*resultWeightBBBNoCloUp");
if( outhist2->Integral()<0.001) nonclosureup.push_back(-1);else nonclosureup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*resultWeightBBBNoCloUp");
if( outhist2->Integral()<0.001) nonclosureup.push_back(-1);else nonclosureup.push_back(outhist2->Integral());
      





   // NJets 3,5 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*resultWeightBBBNoCloUp");
//if( outhist2->Integral()<0.001) nonclosureup.push_back(-1);else nonclosureup.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultWeightBBBNoCloUp");
if( outhist2->Integral()<0.001) nonclosureup.push_back(-1);else nonclosureup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*resultWeightBBBNoCloUp");
if( outhist2->Integral()<0.001) nonclosureup.push_back(-1);else nonclosureup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*resultWeightBBBNoCloUp");
if( outhist2->Integral()<0.001) nonclosureup.push_back(-1);else nonclosureup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*resultWeightBBBNoCloUp");
if( outhist2->Integral()<0.001) nonclosureup.push_back(-1);else nonclosureup.push_back(outhist2->Integral());
      




   // NJets 3,5 HT 1000,1250
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*resultWeightBBBNoCloUp");
//if( outhist2->Integral()<0.001) nonclosureup.push_back(-1);else nonclosureup.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultWeightBBBNoCloUp");
if( outhist2->Integral()<0.001) nonclosureup.push_back(-1);else nonclosureup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*resultWeightBBBNoCloUp");
if( outhist2->Integral()<0.001) nonclosureup.push_back(-1);else nonclosureup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*resultWeightBBBNoCloUp");
if( outhist2->Integral()<0.001) nonclosureup.push_back(-1);else nonclosureup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*resultWeightBBBNoCloUp");
if( outhist2->Integral()<0.001) nonclosureup.push_back(-1);else nonclosureup.push_back(outhist2->Integral());
      





   // NJets 3,5 HT 1250,1500
 //  tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*resultWeightBBBNoCloUp");
//if( outhist2->Integral()<0.001) nonclosureup.push_back(-1);else nonclosureup.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultWeightBBBNoCloUp");
if( outhist2->Integral()<0.001) nonclosureup.push_back(-1);else nonclosureup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*resultWeightBBBNoCloUp");
if( outhist2->Integral()<0.001) nonclosureup.push_back(-1);else nonclosureup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 450)*resultWeightBBBNoCloUp");
if( outhist2->Integral()<0.001) nonclosureup.push_back(-1);else nonclosureup.push_back(outhist2->Integral());
      




   // NJets 3,5 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*resultWeightBBBNoCloUp");
//if( outhist2->Integral()<0.001) nonclosureup.push_back(-1);else nonclosureup.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultWeightBBBNoCloUp");
if( outhist2->Integral()<0.001) nonclosureup.push_back(-1);else nonclosureup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 300 )*resultWeightBBBNoCloUp");
if( outhist2->Integral()<0.001) nonclosureup.push_back(-1);else nonclosureup.push_back(outhist2->Integral());
      










   // NJets 6,7 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultWeightBBBNoCloUp");
if( outhist2->Integral()<0.001) nonclosureup.push_back(-1);else nonclosureup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*resultWeightBBBNoCloUp");
if( outhist2->Integral()<0.001) nonclosureup.push_back(-1);else nonclosureup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*resultWeightBBBNoCloUp");
if( outhist2->Integral()<0.001) nonclosureup.push_back(-1);else nonclosureup.push_back(outhist2->Integral());
      





   // NJets 6,7 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultWeightBBBNoCloUp");
//if( outhist2->Integral()<0.001) nonclosureup.push_back(-1);else nonclosureup.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultWeightBBBNoCloUp");
if( outhist2->Integral()<0.001) nonclosureup.push_back(-1);else nonclosureup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*resultWeightBBBNoCloUp");
if( outhist2->Integral()<0.001) nonclosureup.push_back(-1);else nonclosureup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*resultWeightBBBNoCloUp");
if( outhist2->Integral()<0.001) nonclosureup.push_back(-1);else nonclosureup.push_back(outhist2->Integral());
      






   // NJets 6,7 HT 1000,1250
 //  tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultWeightBBBNoCloUp");
//if( outhist2->Integral()<0.001) nonclosureup.push_back(-1);else nonclosureup.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultWeightBBBNoCloUp");
if( outhist2->Integral()<0.001) nonclosureup.push_back(-1);else nonclosureup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*resultWeightBBBNoCloUp");
if( outhist2->Integral()<0.001) nonclosureup.push_back(-1);else nonclosureup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*resultWeightBBBNoCloUp");
if( outhist2->Integral()<0.001) nonclosureup.push_back(-1);else nonclosureup.push_back(outhist2->Integral());
      







   // NJets 6,7 HT 1250,1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultWeightBBBNoCloUp");
//if( outhist2->Integral()<0.001) nonclosureup.push_back(-1);else nonclosureup.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultWeightBBBNoCloUp");
if( outhist2->Integral()<0.001) nonclosureup.push_back(-1);else nonclosureup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*resultWeightBBBNoCloUp");
if( outhist2->Integral()<0.001) nonclosureup.push_back(-1);else nonclosureup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 450)*resultWeightBBBNoCloUp");
if( outhist2->Integral()<0.001) nonclosureup.push_back(-1);else nonclosureup.push_back(outhist2->Integral());
      




   // NJets 6,7 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultWeightBBBNoCloUp");
//if( outhist2->Integral()<0.001) nonclosureup.push_back(-1);else nonclosureup.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultWeightBBBNoCloUp");
if( outhist2->Integral()<0.001) nonclosureup.push_back(-1);else nonclosureup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 300 )*resultWeightBBBNoCloUp");
if( outhist2->Integral()<0.001) nonclosureup.push_back(-1);else nonclosureup.push_back(outhist2->Integral());
      



// --------------------------------------------------------------------------------------------------






   // NJets 8 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 7.5 && MHT > 200 )*resultWeightBBBNoCloUp");
if( outhist2->Integral()<0.001) nonclosureup.push_back(-1);else nonclosureup.push_back(outhist2->Integral());
      






   // NJets 8 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 7.5 && MHT > 100 && MHT < 200  )*resultWeightBBBNoCloUp");
//if( outhist2->Integral()<0.001) nonclosureup.push_back(-1);else nonclosureup.push_back(outhist2->Integral());
 //     

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 7.5 && MHT > 200 )*resultWeightBBBNoCloUp");
if( outhist2->Integral()<0.001) nonclosureup.push_back(-1);else nonclosureup.push_back(outhist2->Integral());
      





   // NJets 8 HT 1000,1250
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 7.5 && MHT > 100 && MHT < 200  )*resultWeightBBBNoCloUp");
//if( outhist2->Integral()<0.001) nonclosureup.push_back(-1);else nonclosureup.push_back(outhist2->Integral());
//      

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 7.5 && MHT > 200 )*resultWeightBBBNoCloUp");
if( outhist2->Integral()<0.001) nonclosureup.push_back(-1);else nonclosureup.push_back(outhist2->Integral());
      








   // NJets 8 HT 1250,1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 7.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultWeightBBBNoCloUp");
//if( outhist2->Integral()<0.001) nonclosureup.push_back(-1);else nonclosureup.push_back(outhist2->Integral());
 //     

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 7.5 && MHT > 200  )*resultWeightBBBNoCloUp");
if( outhist2->Integral()<0.001) nonclosureup.push_back(-1);else nonclosureup.push_back(outhist2->Integral());
      




   // NJets 8 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 7.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultWeightBBBNoCloUp");
//if( outhist2->Integral()<0.001) nonclosureup.push_back(-1);else nonclosureup.push_back(outhist2->Integral());
//      

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 7.5 && MHT > 200  )*resultWeightBBBNoCloUp");
if( outhist2->Integral()<0.001) nonclosureup.push_back(-1);else nonclosureup.push_back(outhist2->Integral());
      












  // go though all the bins
   // NJets 3,5 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultWeightBBBNoCloDown");
if( outhist2->Integral()<0.001) nonclosuredn.push_back(-1);else nonclosuredn.push_back(outhist2->Integral());
      



   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*resultWeightBBBNoCloDown");
if( outhist2->Integral()<0.001) nonclosuredn.push_back(-1);else nonclosuredn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*resultWeightBBBNoCloDown");
if( outhist2->Integral()<0.001) nonclosuredn.push_back(-1);else nonclosuredn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*resultWeightBBBNoCloDown");
if( outhist2->Integral()<0.001) nonclosuredn.push_back(-1);else nonclosuredn.push_back(outhist2->Integral());
      





   // NJets 3,5 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*resultWeightBBBNoCloDown");
//if( outhist2->Integral()<0.001) nonclosuredn.push_back(-1);else nonclosuredn.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultWeightBBBNoCloDown");
if( outhist2->Integral()<0.001) nonclosuredn.push_back(-1);else nonclosuredn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*resultWeightBBBNoCloDown");
if( outhist2->Integral()<0.001) nonclosuredn.push_back(-1);else nonclosuredn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*resultWeightBBBNoCloDown");
if( outhist2->Integral()<0.001) nonclosuredn.push_back(-1);else nonclosuredn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*resultWeightBBBNoCloDown");
if( outhist2->Integral()<0.001) nonclosuredn.push_back(-1);else nonclosuredn.push_back(outhist2->Integral());
      




   // NJets 3,5 HT 1000,1250
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*resultWeightBBBNoCloDown");
//if( outhist2->Integral()<0.001) nonclosuredn.push_back(-1);else nonclosuredn.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultWeightBBBNoCloDown");
if( outhist2->Integral()<0.001) nonclosuredn.push_back(-1);else nonclosuredn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*resultWeightBBBNoCloDown");
if( outhist2->Integral()<0.001) nonclosuredn.push_back(-1);else nonclosuredn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*resultWeightBBBNoCloDown");
if( outhist2->Integral()<0.001) nonclosuredn.push_back(-1);else nonclosuredn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*resultWeightBBBNoCloDown");
if( outhist2->Integral()<0.001) nonclosuredn.push_back(-1);else nonclosuredn.push_back(outhist2->Integral());
      





   // NJets 3,5 HT 1250,1500
 //  tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*resultWeightBBBNoCloDown");
//if( outhist2->Integral()<0.001) nonclosuredn.push_back(-1);else nonclosuredn.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultWeightBBBNoCloDown");
if( outhist2->Integral()<0.001) nonclosuredn.push_back(-1);else nonclosuredn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*resultWeightBBBNoCloDown");
if( outhist2->Integral()<0.001) nonclosuredn.push_back(-1);else nonclosuredn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 450)*resultWeightBBBNoCloDown");
if( outhist2->Integral()<0.001) nonclosuredn.push_back(-1);else nonclosuredn.push_back(outhist2->Integral());
      




   // NJets 3,5 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*resultWeightBBBNoCloDown");
//if( outhist2->Integral()<0.001) nonclosuredn.push_back(-1);else nonclosuredn.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultWeightBBBNoCloDown");
if( outhist2->Integral()<0.001) nonclosuredn.push_back(-1);else nonclosuredn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 300 )*resultWeightBBBNoCloDown");
if( outhist2->Integral()<0.001) nonclosuredn.push_back(-1);else nonclosuredn.push_back(outhist2->Integral());
      










   // NJets 6,7 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultWeightBBBNoCloDown");
if( outhist2->Integral()<0.001) nonclosuredn.push_back(-1);else nonclosuredn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*resultWeightBBBNoCloDown");
if( outhist2->Integral()<0.001) nonclosuredn.push_back(-1);else nonclosuredn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*resultWeightBBBNoCloDown");
if( outhist2->Integral()<0.001) nonclosuredn.push_back(-1);else nonclosuredn.push_back(outhist2->Integral());
      





   // NJets 6,7 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultWeightBBBNoCloDown");
//if( outhist2->Integral()<0.001) nonclosuredn.push_back(-1);else nonclosuredn.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultWeightBBBNoCloDown");
if( outhist2->Integral()<0.001) nonclosuredn.push_back(-1);else nonclosuredn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*resultWeightBBBNoCloDown");
if( outhist2->Integral()<0.001) nonclosuredn.push_back(-1);else nonclosuredn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*resultWeightBBBNoCloDown");
if( outhist2->Integral()<0.001) nonclosuredn.push_back(-1);else nonclosuredn.push_back(outhist2->Integral());
      






   // NJets 6,7 HT 1000,1250
 //  tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultWeightBBBNoCloDown");
//if( outhist2->Integral()<0.001) nonclosuredn.push_back(-1);else nonclosuredn.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultWeightBBBNoCloDown");
if( outhist2->Integral()<0.001) nonclosuredn.push_back(-1);else nonclosuredn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*resultWeightBBBNoCloDown");
if( outhist2->Integral()<0.001) nonclosuredn.push_back(-1);else nonclosuredn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*resultWeightBBBNoCloDown");
if( outhist2->Integral()<0.001) nonclosuredn.push_back(-1);else nonclosuredn.push_back(outhist2->Integral());
      







   // NJets 6,7 HT 1250,1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultWeightBBBNoCloDown");
//if( outhist2->Integral()<0.001) nonclosuredn.push_back(-1);else nonclosuredn.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultWeightBBBNoCloDown");
if( outhist2->Integral()<0.001) nonclosuredn.push_back(-1);else nonclosuredn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*resultWeightBBBNoCloDown");
if( outhist2->Integral()<0.001) nonclosuredn.push_back(-1);else nonclosuredn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 450)*resultWeightBBBNoCloDown");
if( outhist2->Integral()<0.001) nonclosuredn.push_back(-1);else nonclosuredn.push_back(outhist2->Integral());
      




   // NJets 6,7 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultWeightBBBNoCloDown");
//if( outhist2->Integral()<0.001) nonclosuredn.push_back(-1);else nonclosuredn.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultWeightBBBNoCloDown");
if( outhist2->Integral()<0.001) nonclosuredn.push_back(-1);else nonclosuredn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 300 )*resultWeightBBBNoCloDown");
if( outhist2->Integral()<0.001) nonclosuredn.push_back(-1);else nonclosuredn.push_back(outhist2->Integral());
      



// --------------------------------------------------------------------------------------------------






   // NJets 8 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 7.5 && MHT > 200 )*resultWeightBBBNoCloDown");
if( outhist2->Integral()<0.001) nonclosuredn.push_back(-1);else nonclosuredn.push_back(outhist2->Integral());
      






   // NJets 8 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 7.5 && MHT > 100 && MHT < 200  )*resultWeightBBBNoCloDown");
//if( outhist2->Integral()<0.001) nonclosuredn.push_back(-1);else nonclosuredn.push_back(outhist2->Integral());
 //     

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 7.5 && MHT > 200 )*resultWeightBBBNoCloDown");
if( outhist2->Integral()<0.001) nonclosuredn.push_back(-1);else nonclosuredn.push_back(outhist2->Integral());
      





   // NJets 8 HT 1000,1250
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 7.5 && MHT > 100 && MHT < 200  )*resultWeightBBBNoCloDown");
//if( outhist2->Integral()<0.001) nonclosuredn.push_back(-1);else nonclosuredn.push_back(outhist2->Integral());
//      

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 7.5 && MHT > 200 )*resultWeightBBBNoCloDown");
if( outhist2->Integral()<0.001) nonclosuredn.push_back(-1);else nonclosuredn.push_back(outhist2->Integral());
      








   // NJets 8 HT 1250,1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 7.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultWeightBBBNoCloDown");
//if( outhist2->Integral()<0.001) nonclosuredn.push_back(-1);else nonclosuredn.push_back(outhist2->Integral());
 //     

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 7.5 && MHT > 200  )*resultWeightBBBNoCloDown");
if( outhist2->Integral()<0.001) nonclosuredn.push_back(-1);else nonclosuredn.push_back(outhist2->Integral());
      




   // NJets 8 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 7.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultWeightBBBNoCloDown");
//if( outhist2->Integral()<0.001) nonclosuredn.push_back(-1);else nonclosuredn.push_back(outhist2->Integral());
//      

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 7.5 && MHT > 200  )*resultWeightBBBNoCloDown");
if( outhist2->Integral()<0.001) nonclosuredn.push_back(-1);else nonclosuredn.push_back(outhist2->Integral());
      












// -------------------------------------------------- acc uncertainty







  // go though all the bins
   // NJets 3,5 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultWeightBinByBinAccUp");
if( outhist2->Integral()<0.001) accup.push_back(-1);else accup.push_back(outhist2->Integral());
      



   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*resultWeightBinByBinAccUp");
if( outhist2->Integral()<0.001) accup.push_back(-1);else accup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*resultWeightBinByBinAccUp");
if( outhist2->Integral()<0.001) accup.push_back(-1);else accup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*resultWeightBinByBinAccUp");
if( outhist2->Integral()<0.001) accup.push_back(-1);else accup.push_back(outhist2->Integral());
      





   // NJets 3,5 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*resultWeightBinByBinAccUp");
//if( outhist2->Integral()<0.001) accup.push_back(-1);else accup.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultWeightBinByBinAccUp");
if( outhist2->Integral()<0.001) accup.push_back(-1);else accup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*resultWeightBinByBinAccUp");
if( outhist2->Integral()<0.001) accup.push_back(-1);else accup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*resultWeightBinByBinAccUp");
if( outhist2->Integral()<0.001) accup.push_back(-1);else accup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*resultWeightBinByBinAccUp");
if( outhist2->Integral()<0.001) accup.push_back(-1);else accup.push_back(outhist2->Integral());
      




   // NJets 3,5 HT 1000,1250
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*resultWeightBinByBinAccUp");
//if( outhist2->Integral()<0.001) accup.push_back(-1);else accup.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultWeightBinByBinAccUp");
if( outhist2->Integral()<0.001) accup.push_back(-1);else accup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*resultWeightBinByBinAccUp");
if( outhist2->Integral()<0.001) accup.push_back(-1);else accup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*resultWeightBinByBinAccUp");
if( outhist2->Integral()<0.001) accup.push_back(-1);else accup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*resultWeightBinByBinAccUp");
if( outhist2->Integral()<0.001) accup.push_back(-1);else accup.push_back(outhist2->Integral());
      





   // NJets 3,5 HT 1250,1500
 //  tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*resultWeightBinByBinAccUp");
//if( outhist2->Integral()<0.001) accup.push_back(-1);else accup.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultWeightBinByBinAccUp");
if( outhist2->Integral()<0.001) accup.push_back(-1);else accup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*resultWeightBinByBinAccUp");
if( outhist2->Integral()<0.001) accup.push_back(-1);else accup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 450)*resultWeightBinByBinAccUp");
if( outhist2->Integral()<0.001) accup.push_back(-1);else accup.push_back(outhist2->Integral());
      




   // NJets 3,5 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*resultWeightBinByBinAccUp");
//if( outhist2->Integral()<0.001) accup.push_back(-1);else accup.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultWeightBinByBinAccUp");
if( outhist2->Integral()<0.001) accup.push_back(-1);else accup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 300 )*resultWeightBinByBinAccUp");
if( outhist2->Integral()<0.001) accup.push_back(-1);else accup.push_back(outhist2->Integral());
      










   // NJets 6,7 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultWeightBinByBinAccUp");
if( outhist2->Integral()<0.001) accup.push_back(-1);else accup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*resultWeightBinByBinAccUp");
if( outhist2->Integral()<0.001) accup.push_back(-1);else accup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*resultWeightBinByBinAccUp");
if( outhist2->Integral()<0.001) accup.push_back(-1);else accup.push_back(outhist2->Integral());
      





   // NJets 6,7 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultWeightBinByBinAccUp");
//if( outhist2->Integral()<0.001) accup.push_back(-1);else accup.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultWeightBinByBinAccUp");
if( outhist2->Integral()<0.001) accup.push_back(-1);else accup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*resultWeightBinByBinAccUp");
if( outhist2->Integral()<0.001) accup.push_back(-1);else accup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*resultWeightBinByBinAccUp");
if( outhist2->Integral()<0.001) accup.push_back(-1);else accup.push_back(outhist2->Integral());
      






   // NJets 6,7 HT 1000,1250
 //  tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultWeightBinByBinAccUp");
//if( outhist2->Integral()<0.001) accup.push_back(-1);else accup.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultWeightBinByBinAccUp");
if( outhist2->Integral()<0.001) accup.push_back(-1);else accup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*resultWeightBinByBinAccUp");
if( outhist2->Integral()<0.001) accup.push_back(-1);else accup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*resultWeightBinByBinAccUp");
if( outhist2->Integral()<0.001) accup.push_back(-1);else accup.push_back(outhist2->Integral());
      







   // NJets 6,7 HT 1250,1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultWeightBinByBinAccUp");
//if( outhist2->Integral()<0.001) accup.push_back(-1);else accup.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultWeightBinByBinAccUp");
if( outhist2->Integral()<0.001) accup.push_back(-1);else accup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*resultWeightBinByBinAccUp");
if( outhist2->Integral()<0.001) accup.push_back(-1);else accup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 450)*resultWeightBinByBinAccUp");
if( outhist2->Integral()<0.001) accup.push_back(-1);else accup.push_back(outhist2->Integral());
      




   // NJets 6,7 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultWeightBinByBinAccUp");
//if( outhist2->Integral()<0.001) accup.push_back(-1);else accup.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultWeightBinByBinAccUp");
if( outhist2->Integral()<0.001) accup.push_back(-1);else accup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 300 )*resultWeightBinByBinAccUp");
if( outhist2->Integral()<0.001) accup.push_back(-1);else accup.push_back(outhist2->Integral());
      



// --------------------------------------------------------------------------------------------------






   // NJets 8 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 7.5 && MHT > 200 )*resultWeightBinByBinAccUp");
if( outhist2->Integral()<0.001) accup.push_back(-1);else accup.push_back(outhist2->Integral());
      






   // NJets 8 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 7.5 && MHT > 100 && MHT < 200  )*resultWeightBinByBinAccUp");
//if( outhist2->Integral()<0.001) accup.push_back(-1);else accup.push_back(outhist2->Integral());
 //     

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 7.5 && MHT > 200 )*resultWeightBinByBinAccUp");
if( outhist2->Integral()<0.001) accup.push_back(-1);else accup.push_back(outhist2->Integral());
      





   // NJets 8 HT 1000,1250
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 7.5 && MHT > 100 && MHT < 200  )*resultWeightBinByBinAccUp");
//if( outhist2->Integral()<0.001) accup.push_back(-1);else accup.push_back(outhist2->Integral());
//      

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 7.5 && MHT > 200 )*resultWeightBinByBinAccUp");
if( outhist2->Integral()<0.001) accup.push_back(-1);else accup.push_back(outhist2->Integral());
      








   // NJets 8 HT 1250,1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 7.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultWeightBinByBinAccUp");
//if( outhist2->Integral()<0.001) accup.push_back(-1);else accup.push_back(outhist2->Integral());
 //     

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 7.5 && MHT > 200  )*resultWeightBinByBinAccUp");
if( outhist2->Integral()<0.001) accup.push_back(-1);else accup.push_back(outhist2->Integral());
      




   // NJets 8 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 7.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultWeightBinByBinAccUp");
//if( outhist2->Integral()<0.001) accup.push_back(-1);else accup.push_back(outhist2->Integral());
//      

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 7.5 && MHT > 200  )*resultWeightBinByBinAccUp");
if( outhist2->Integral()<0.001) accup.push_back(-1);else accup.push_back(outhist2->Integral());
      















  // go though all the bins
   // NJets 3,5 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultWeightBinByBinAccDown");
if( outhist2->Integral()<0.001) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
      



   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*resultWeightBinByBinAccDown");
if( outhist2->Integral()<0.001) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*resultWeightBinByBinAccDown");
if( outhist2->Integral()<0.001) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*resultWeightBinByBinAccDown");
if( outhist2->Integral()<0.001) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
      





   // NJets 3,5 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*resultWeightBinByBinAccDown");
//if( outhist2->Integral()<0.001) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultWeightBinByBinAccDown");
if( outhist2->Integral()<0.001) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*resultWeightBinByBinAccDown");
if( outhist2->Integral()<0.001) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*resultWeightBinByBinAccDown");
if( outhist2->Integral()<0.001) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*resultWeightBinByBinAccDown");
if( outhist2->Integral()<0.001) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
      




   // NJets 3,5 HT 1000,1250
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*resultWeightBinByBinAccDown");
//if( outhist2->Integral()<0.001) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultWeightBinByBinAccDown");
if( outhist2->Integral()<0.001) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*resultWeightBinByBinAccDown");
if( outhist2->Integral()<0.001) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*resultWeightBinByBinAccDown");
if( outhist2->Integral()<0.001) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*resultWeightBinByBinAccDown");
if( outhist2->Integral()<0.001) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
      





   // NJets 3,5 HT 1250,1500
 //  tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*resultWeightBinByBinAccDown");
//if( outhist2->Integral()<0.001) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultWeightBinByBinAccDown");
if( outhist2->Integral()<0.001) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*resultWeightBinByBinAccDown");
if( outhist2->Integral()<0.001) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 450)*resultWeightBinByBinAccDown");
if( outhist2->Integral()<0.001) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
      




   // NJets 3,5 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*resultWeightBinByBinAccDown");
//if( outhist2->Integral()<0.001) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultWeightBinByBinAccDown");
if( outhist2->Integral()<0.001) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 300 )*resultWeightBinByBinAccDown");
if( outhist2->Integral()<0.001) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
      










   // NJets 6,7 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultWeightBinByBinAccDown");
if( outhist2->Integral()<0.001) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*resultWeightBinByBinAccDown");
if( outhist2->Integral()<0.001) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*resultWeightBinByBinAccDown");
if( outhist2->Integral()<0.001) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
      





   // NJets 6,7 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultWeightBinByBinAccDown");
//if( outhist2->Integral()<0.001) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultWeightBinByBinAccDown");
if( outhist2->Integral()<0.001) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*resultWeightBinByBinAccDown");
if( outhist2->Integral()<0.001) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*resultWeightBinByBinAccDown");
if( outhist2->Integral()<0.001) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
      






   // NJets 6,7 HT 1000,1250
 //  tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultWeightBinByBinAccDown");
//if( outhist2->Integral()<0.001) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultWeightBinByBinAccDown");
if( outhist2->Integral()<0.001) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*resultWeightBinByBinAccDown");
if( outhist2->Integral()<0.001) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*resultWeightBinByBinAccDown");
if( outhist2->Integral()<0.001) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
      







   // NJets 6,7 HT 1250,1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultWeightBinByBinAccDown");
//if( outhist2->Integral()<0.001) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultWeightBinByBinAccDown");
if( outhist2->Integral()<0.001) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*resultWeightBinByBinAccDown");
if( outhist2->Integral()<0.001) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 450)*resultWeightBinByBinAccDown");
if( outhist2->Integral()<0.001) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
      




   // NJets 6,7 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultWeightBinByBinAccDown");
//if( outhist2->Integral()<0.001) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultWeightBinByBinAccDown");
if( outhist2->Integral()<0.001) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 300 )*resultWeightBinByBinAccDown");
if( outhist2->Integral()<0.001) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
      



// --------------------------------------------------------------------------------------------------






   // NJets 8 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 7.5 && MHT > 200 )*resultWeightBinByBinAccDown");
if( outhist2->Integral()<0.001) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
      






   // NJets 8 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 7.5 && MHT > 100 && MHT < 200  )*resultWeightBinByBinAccDown");
//if( outhist2->Integral()<0.001) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
 //     

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 7.5 && MHT > 200 )*resultWeightBinByBinAccDown");
if( outhist2->Integral()<0.001) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
      





   // NJets 8 HT 1000,1250
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 7.5 && MHT > 100 && MHT < 200  )*resultWeightBinByBinAccDown");
//if( outhist2->Integral()<0.001) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
//      

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 7.5 && MHT > 200 )*resultWeightBinByBinAccDown");
if( outhist2->Integral()<0.001) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
      








   // NJets 8 HT 1250,1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 7.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultWeightBinByBinAccDown");
//if( outhist2->Integral()<0.001) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
 //     

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 7.5 && MHT > 200  )*resultWeightBinByBinAccDown");
if( outhist2->Integral()<0.001) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
      




   // NJets 8 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 7.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultWeightBinByBinAccDown");
//if( outhist2->Integral()<0.001) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
//      

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 7.5 && MHT > 200  )*resultWeightBinByBinAccDown");
if( outhist2->Integral()<0.001) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
      







// -------------------------------------------------------dibson uncertainty








  // go though all the bins
   // NJets 3,5 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultWeightBBBDiBoUp");
if( outhist2->Integral()<0.001) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
      



   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*resultWeightBBBDiBoUp");
if( outhist2->Integral()<0.001) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*resultWeightBBBDiBoUp");
if( outhist2->Integral()<0.001) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*resultWeightBBBDiBoUp");
if( outhist2->Integral()<0.001) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
      





   // NJets 3,5 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*resultWeightBBBDiBoUp");
//if( outhist2->Integral()<0.001) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultWeightBBBDiBoUp");
if( outhist2->Integral()<0.001) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*resultWeightBBBDiBoUp");
if( outhist2->Integral()<0.001) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*resultWeightBBBDiBoUp");
if( outhist2->Integral()<0.001) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*resultWeightBBBDiBoUp");
if( outhist2->Integral()<0.001) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
      




   // NJets 3,5 HT 1000,1250
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*resultWeightBBBDiBoUp");
//if( outhist2->Integral()<0.001) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultWeightBBBDiBoUp");
if( outhist2->Integral()<0.001) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*resultWeightBBBDiBoUp");
if( outhist2->Integral()<0.001) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*resultWeightBBBDiBoUp");
if( outhist2->Integral()<0.001) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*resultWeightBBBDiBoUp");
if( outhist2->Integral()<0.001) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
      





   // NJets 3,5 HT 1250,1500
 //  tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*resultWeightBBBDiBoUp");
//if( outhist2->Integral()<0.001) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultWeightBBBDiBoUp");
if( outhist2->Integral()<0.001) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*resultWeightBBBDiBoUp");
if( outhist2->Integral()<0.001) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 450)*resultWeightBBBDiBoUp");
if( outhist2->Integral()<0.001) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
      




   // NJets 3,5 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*resultWeightBBBDiBoUp");
//if( outhist2->Integral()<0.001) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultWeightBBBDiBoUp");
if( outhist2->Integral()<0.001) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 300 )*resultWeightBBBDiBoUp");
if( outhist2->Integral()<0.001) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
      










   // NJets 6,7 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultWeightBBBDiBoUp");
if( outhist2->Integral()<0.001) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*resultWeightBBBDiBoUp");
if( outhist2->Integral()<0.001) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*resultWeightBBBDiBoUp");
if( outhist2->Integral()<0.001) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
      





   // NJets 6,7 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultWeightBBBDiBoUp");
//if( outhist2->Integral()<0.001) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultWeightBBBDiBoUp");
if( outhist2->Integral()<0.001) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*resultWeightBBBDiBoUp");
if( outhist2->Integral()<0.001) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*resultWeightBBBDiBoUp");
if( outhist2->Integral()<0.001) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
      






   // NJets 6,7 HT 1000,1250
 //  tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultWeightBBBDiBoUp");
//if( outhist2->Integral()<0.001) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultWeightBBBDiBoUp");
if( outhist2->Integral()<0.001) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*resultWeightBBBDiBoUp");
if( outhist2->Integral()<0.001) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*resultWeightBBBDiBoUp");
if( outhist2->Integral()<0.001) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
      







   // NJets 6,7 HT 1250,1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultWeightBBBDiBoUp");
//if( outhist2->Integral()<0.001) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultWeightBBBDiBoUp");
if( outhist2->Integral()<0.001) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*resultWeightBBBDiBoUp");
if( outhist2->Integral()<0.001) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 450)*resultWeightBBBDiBoUp");
if( outhist2->Integral()<0.001) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
      




   // NJets 6,7 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultWeightBBBDiBoUp");
//if( outhist2->Integral()<0.001) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultWeightBBBDiBoUp");
if( outhist2->Integral()<0.001) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 300 )*resultWeightBBBDiBoUp");
if( outhist2->Integral()<0.001) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
      



// --------------------------------------------------------------------------------------------------






   // NJets 8 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 7.5 && MHT > 200 )*resultWeightBBBDiBoUp");
if( outhist2->Integral()<0.001) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
      






   // NJets 8 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 7.5 && MHT > 100 && MHT < 200  )*resultWeightBBBDiBoUp");
//if( outhist2->Integral()<0.001) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
 //     

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 7.5 && MHT > 200 )*resultWeightBBBDiBoUp");
if( outhist2->Integral()<0.001) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
      





   // NJets 8 HT 1000,1250
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 7.5 && MHT > 100 && MHT < 200  )*resultWeightBBBDiBoUp");
//if( outhist2->Integral()<0.001) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
//      

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 7.5 && MHT > 200 )*resultWeightBBBDiBoUp");
if( outhist2->Integral()<0.001) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
      








   // NJets 8 HT 1250,1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 7.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultWeightBBBDiBoUp");
//if( outhist2->Integral()<0.001) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
 //     

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 7.5 && MHT > 200  )*resultWeightBBBDiBoUp");
if( outhist2->Integral()<0.001) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
      




   // NJets 8 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 7.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultWeightBBBDiBoUp");
//if( outhist2->Integral()<0.001) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
//      

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 7.5 && MHT > 200  )*resultWeightBBBDiBoUp");
if( outhist2->Integral()<0.001) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
      









  // go though all the bins
   // NJets 3,5 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultWeightBBBDiBoDown");
if( outhist2->Integral()<0.001) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
      



   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*resultWeightBBBDiBoDown");
if( outhist2->Integral()<0.001) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*resultWeightBBBDiBoDown");
if( outhist2->Integral()<0.001) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*resultWeightBBBDiBoDown");
if( outhist2->Integral()<0.001) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
      





   // NJets 3,5 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*resultWeightBBBDiBoDown");
//if( outhist2->Integral()<0.001) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultWeightBBBDiBoDown");
if( outhist2->Integral()<0.001) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*resultWeightBBBDiBoDown");
if( outhist2->Integral()<0.001) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*resultWeightBBBDiBoDown");
if( outhist2->Integral()<0.001) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*resultWeightBBBDiBoDown");
if( outhist2->Integral()<0.001) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
      




   // NJets 3,5 HT 1000,1250
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*resultWeightBBBDiBoDown");
//if( outhist2->Integral()<0.001) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultWeightBBBDiBoDown");
if( outhist2->Integral()<0.001) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*resultWeightBBBDiBoDown");
if( outhist2->Integral()<0.001) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*resultWeightBBBDiBoDown");
if( outhist2->Integral()<0.001) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*resultWeightBBBDiBoDown");
if( outhist2->Integral()<0.001) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
      





   // NJets 3,5 HT 1250,1500
 //  tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*resultWeightBBBDiBoDown");
//if( outhist2->Integral()<0.001) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultWeightBBBDiBoDown");
if( outhist2->Integral()<0.001) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*resultWeightBBBDiBoDown");
if( outhist2->Integral()<0.001) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 450)*resultWeightBBBDiBoDown");
if( outhist2->Integral()<0.001) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
      




   // NJets 3,5 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*resultWeightBBBDiBoDown");
//if( outhist2->Integral()<0.001) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultWeightBBBDiBoDown");
if( outhist2->Integral()<0.001) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 300 )*resultWeightBBBDiBoDown");
if( outhist2->Integral()<0.001) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
      










   // NJets 6,7 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultWeightBBBDiBoDown");
if( outhist2->Integral()<0.001) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*resultWeightBBBDiBoDown");
if( outhist2->Integral()<0.001) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*resultWeightBBBDiBoDown");
if( outhist2->Integral()<0.001) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
      





   // NJets 6,7 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultWeightBBBDiBoDown");
//if( outhist2->Integral()<0.001) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultWeightBBBDiBoDown");
if( outhist2->Integral()<0.001) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*resultWeightBBBDiBoDown");
if( outhist2->Integral()<0.001) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*resultWeightBBBDiBoDown");
if( outhist2->Integral()<0.001) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
      






   // NJets 6,7 HT 1000,1250
 //  tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultWeightBBBDiBoDown");
//if( outhist2->Integral()<0.001) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultWeightBBBDiBoDown");
if( outhist2->Integral()<0.001) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*resultWeightBBBDiBoDown");
if( outhist2->Integral()<0.001) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*resultWeightBBBDiBoDown");
if( outhist2->Integral()<0.001) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
      







   // NJets 6,7 HT 1250,1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultWeightBBBDiBoDown");
//if( outhist2->Integral()<0.001) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultWeightBBBDiBoDown");
if( outhist2->Integral()<0.001) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*resultWeightBBBDiBoDown");
if( outhist2->Integral()<0.001) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 450)*resultWeightBBBDiBoDown");
if( outhist2->Integral()<0.001) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
      




   // NJets 6,7 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultWeightBBBDiBoDown");
//if( outhist2->Integral()<0.001) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultWeightBBBDiBoDown");
if( outhist2->Integral()<0.001) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 300 )*resultWeightBBBDiBoDown");
if( outhist2->Integral()<0.001) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
      



// --------------------------------------------------------------------------------------------------






   // NJets 8 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 7.5 && MHT > 200 )*resultWeightBBBDiBoDown");
if( outhist2->Integral()<0.001) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
      






   // NJets 8 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 7.5 && MHT > 100 && MHT < 200  )*resultWeightBBBDiBoDown");
//if( outhist2->Integral()<0.001) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
 //     

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 7.5 && MHT > 200 )*resultWeightBBBDiBoDown");
if( outhist2->Integral()<0.001) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
      





   // NJets 8 HT 1000,1250
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 7.5 && MHT > 100 && MHT < 200  )*resultWeightBBBDiBoDown");
//if( outhist2->Integral()<0.001) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
//      

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 7.5 && MHT > 200 )*resultWeightBBBDiBoDown");
if( outhist2->Integral()<0.001) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
      








   // NJets 8 HT 1250,1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 7.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultWeightBBBDiBoDown");
//if( outhist2->Integral()<0.001) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
 //     

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 7.5 && MHT > 200  )*resultWeightBBBDiBoDown");
if( outhist2->Integral()<0.001) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
      




   // NJets 8 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 7.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultWeightBBBDiBoDown");
//if( outhist2->Integral()<0.001) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
//      

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 7.5 && MHT > 200  )*resultWeightBBBDiBoDown");
if( outhist2->Integral()<0.001) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
      






// *-----------------------------------------------------------tag and probe uncertainty






  // go though all the bins
   // NJets 3,5 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*muonIsoTAPUp");
if( outhist2->Integral()<0.001) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
      



   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*muonIsoTAPUp");
if( outhist2->Integral()<0.001) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*muonIsoTAPUp");
if( outhist2->Integral()<0.001) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*muonIsoTAPUp");
if( outhist2->Integral()<0.001) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
      





   // NJets 3,5 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*muonIsoTAPUp");
//if( outhist2->Integral()<0.001) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*muonIsoTAPUp");
if( outhist2->Integral()<0.001) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*muonIsoTAPUp");
if( outhist2->Integral()<0.001) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*muonIsoTAPUp");
if( outhist2->Integral()<0.001) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*muonIsoTAPUp");
if( outhist2->Integral()<0.001) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
      




   // NJets 3,5 HT 1000,1250
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*muonIsoTAPUp");
//if( outhist2->Integral()<0.001) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*muonIsoTAPUp");
if( outhist2->Integral()<0.001) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*muonIsoTAPUp");
if( outhist2->Integral()<0.001) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*muonIsoTAPUp");
if( outhist2->Integral()<0.001) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*muonIsoTAPUp");
if( outhist2->Integral()<0.001) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
      





   // NJets 3,5 HT 1250,1500
 //  tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*muonIsoTAPUp");
//if( outhist2->Integral()<0.001) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*muonIsoTAPUp");
if( outhist2->Integral()<0.001) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*muonIsoTAPUp");
if( outhist2->Integral()<0.001) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 450)*muonIsoTAPUp");
if( outhist2->Integral()<0.001) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
      




   // NJets 3,5 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*muonIsoTAPUp");
//if( outhist2->Integral()<0.001) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*muonIsoTAPUp");
if( outhist2->Integral()<0.001) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 300 )*muonIsoTAPUp");
if( outhist2->Integral()<0.001) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
      










   // NJets 6,7 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*muonIsoTAPUp");
if( outhist2->Integral()<0.001) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*muonIsoTAPUp");
if( outhist2->Integral()<0.001) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*muonIsoTAPUp");
if( outhist2->Integral()<0.001) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
      





   // NJets 6,7 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*muonIsoTAPUp");
//if( outhist2->Integral()<0.001) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*muonIsoTAPUp");
if( outhist2->Integral()<0.001) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*muonIsoTAPUp");
if( outhist2->Integral()<0.001) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*muonIsoTAPUp");
if( outhist2->Integral()<0.001) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
      






   // NJets 6,7 HT 1000,1250
 //  tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*muonIsoTAPUp");
//if( outhist2->Integral()<0.001) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*muonIsoTAPUp");
if( outhist2->Integral()<0.001) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*muonIsoTAPUp");
if( outhist2->Integral()<0.001) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*muonIsoTAPUp");
if( outhist2->Integral()<0.001) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
      







   // NJets 6,7 HT 1250,1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*muonIsoTAPUp");
//if( outhist2->Integral()<0.001) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*muonIsoTAPUp");
if( outhist2->Integral()<0.001) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*muonIsoTAPUp");
if( outhist2->Integral()<0.001) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 450)*muonIsoTAPUp");
if( outhist2->Integral()<0.001) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
      




   // NJets 6,7 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*muonIsoTAPUp");
//if( outhist2->Integral()<0.001) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*muonIsoTAPUp");
if( outhist2->Integral()<0.001) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 300 )*muonIsoTAPUp");
if( outhist2->Integral()<0.001) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
      



// --------------------------------------------------------------------------------------------------






   // NJets 8 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 7.5 && MHT > 200 )*muonIsoTAPUp");
if( outhist2->Integral()<0.001) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
      






   // NJets 8 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 7.5 && MHT > 100 && MHT < 200  )*muonIsoTAPUp");
//if( outhist2->Integral()<0.001) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
 //     

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 7.5 && MHT > 200 )*muonIsoTAPUp");
if( outhist2->Integral()<0.001) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
      





   // NJets 8 HT 1000,1250
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 7.5 && MHT > 100 && MHT < 200  )*muonIsoTAPUp");
//if( outhist2->Integral()<0.001) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
//      

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 7.5 && MHT > 200 )*muonIsoTAPUp");
if( outhist2->Integral()<0.001) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
      








   // NJets 8 HT 1250,1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 7.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*muonIsoTAPUp");
//if( outhist2->Integral()<0.001) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
 //     

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 7.5 && MHT > 200  )*muonIsoTAPUp");
if( outhist2->Integral()<0.001) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
      




   // NJets 8 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 7.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*muonIsoTAPUp");
//if( outhist2->Integral()<0.001) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
//      

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 7.5 && MHT > 200  )*muonIsoTAPUp");
if( outhist2->Integral()<0.001) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
      








  // go though all the bins
   // NJets 3,5 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*muonIsoTAPDown");
if( outhist2->Integral()<0.001) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
      



   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*muonIsoTAPDown");
if( outhist2->Integral()<0.001) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*muonIsoTAPDown");
if( outhist2->Integral()<0.001) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*muonIsoTAPDown");
if( outhist2->Integral()<0.001) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
      





   // NJets 3,5 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*muonIsoTAPDown");
//if( outhist2->Integral()<0.001) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*muonIsoTAPDown");
if( outhist2->Integral()<0.001) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*muonIsoTAPDown");
if( outhist2->Integral()<0.001) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*muonIsoTAPDown");
if( outhist2->Integral()<0.001) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*muonIsoTAPDown");
if( outhist2->Integral()<0.001) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
      




   // NJets 3,5 HT 1000,1250
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*muonIsoTAPDown");
//if( outhist2->Integral()<0.001) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*muonIsoTAPDown");
if( outhist2->Integral()<0.001) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*muonIsoTAPDown");
if( outhist2->Integral()<0.001) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*muonIsoTAPDown");
if( outhist2->Integral()<0.001) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*muonIsoTAPDown");
if( outhist2->Integral()<0.001) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
      





   // NJets 3,5 HT 1250,1500
 //  tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*muonIsoTAPDown");
//if( outhist2->Integral()<0.001) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*muonIsoTAPDown");
if( outhist2->Integral()<0.001) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*muonIsoTAPDown");
if( outhist2->Integral()<0.001) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 450)*muonIsoTAPDown");
if( outhist2->Integral()<0.001) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
      




   // NJets 3,5 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*muonIsoTAPDown");
//if( outhist2->Integral()<0.001) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*muonIsoTAPDown");
if( outhist2->Integral()<0.001) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 300 )*muonIsoTAPDown");
if( outhist2->Integral()<0.001) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
      










   // NJets 6,7 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*muonIsoTAPDown");
if( outhist2->Integral()<0.001) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*muonIsoTAPDown");
if( outhist2->Integral()<0.001) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*muonIsoTAPDown");
if( outhist2->Integral()<0.001) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
      





   // NJets 6,7 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*muonIsoTAPDown");
//if( outhist2->Integral()<0.001) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*muonIsoTAPDown");
if( outhist2->Integral()<0.001) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*muonIsoTAPDown");
if( outhist2->Integral()<0.001) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*muonIsoTAPDown");
if( outhist2->Integral()<0.001) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
      






   // NJets 6,7 HT 1000,1250
 //  tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*muonIsoTAPDown");
//if( outhist2->Integral()<0.001) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*muonIsoTAPDown");
if( outhist2->Integral()<0.001) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*muonIsoTAPDown");
if( outhist2->Integral()<0.001) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*muonIsoTAPDown");
if( outhist2->Integral()<0.001) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
      







   // NJets 6,7 HT 1250,1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*muonIsoTAPDown");
//if( outhist2->Integral()<0.001) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*muonIsoTAPDown");
if( outhist2->Integral()<0.001) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*muonIsoTAPDown");
if( outhist2->Integral()<0.001) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 450)*muonIsoTAPDown");
if( outhist2->Integral()<0.001) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
      




   // NJets 6,7 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*muonIsoTAPDown");
//if( outhist2->Integral()<0.001) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*muonIsoTAPDown");
if( outhist2->Integral()<0.001) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 300 )*muonIsoTAPDown");
if( outhist2->Integral()<0.001) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
      



// --------------------------------------------------------------------------------------------------






   // NJets 8 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 7.5 && MHT > 200 )*muonIsoTAPDown");
if( outhist2->Integral()<0.001) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
      






   // NJets 8 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 7.5 && MHT > 100 && MHT < 200  )*muonIsoTAPDown");
//if( outhist2->Integral()<0.001) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
 //     

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 7.5 && MHT > 200 )*muonIsoTAPDown");
if( outhist2->Integral()<0.001) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
      





   // NJets 8 HT 1000,1250
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 7.5 && MHT > 100 && MHT < 200  )*muonIsoTAPDown");
//if( outhist2->Integral()<0.001) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
//      

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 7.5 && MHT > 200 )*muonIsoTAPDown");
if( outhist2->Integral()<0.001) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
      








   // NJets 8 HT 1250,1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 7.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*muonIsoTAPDown");
//if( outhist2->Integral()<0.001) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
 //     

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 7.5 && MHT > 200  )*muonIsoTAPDown");
if( outhist2->Integral()<0.001) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
      




   // NJets 8 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 7.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*muonIsoTAPDown");
//if( outhist2->Integral()<0.001) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
//      

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 7.5 && MHT > 200  )*muonIsoTAPDown");
if( outhist2->Integral()<0.001) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
      







// ----------------------------------------------------- elec iso


  // go though all the bins
   // NJets 3,5 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*elecIsoTAPUp");
if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      



   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*elecIsoTAPUp");
if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*elecIsoTAPUp");
if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*elecIsoTAPUp");
if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      





   // NJets 3,5 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*elecIsoTAPUp");
//if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*elecIsoTAPUp");
if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*elecIsoTAPUp");
if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*elecIsoTAPUp");
if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*elecIsoTAPUp");
if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      




   // NJets 3,5 HT 1000,1250
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*elecIsoTAPUp");
//if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*elecIsoTAPUp");
if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*elecIsoTAPUp");
if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*elecIsoTAPUp");
if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*elecIsoTAPUp");
if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      





   // NJets 3,5 HT 1250,1500
 //  tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*elecIsoTAPUp");
//if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*elecIsoTAPUp");
if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*elecIsoTAPUp");
if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 450)*elecIsoTAPUp");
if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      




   // NJets 3,5 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*elecIsoTAPUp");
//if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*elecIsoTAPUp");
if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 300 )*elecIsoTAPUp");
if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      










   // NJets 6,7 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*elecIsoTAPUp");
if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*elecIsoTAPUp");
if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*elecIsoTAPUp");
if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      





   // NJets 6,7 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*elecIsoTAPUp");
//if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*elecIsoTAPUp");
if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*elecIsoTAPUp");
if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*elecIsoTAPUp");
if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      






   // NJets 6,7 HT 1000,1250
 //  tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*elecIsoTAPUp");
//if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*elecIsoTAPUp");
if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*elecIsoTAPUp");
if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*elecIsoTAPUp");
if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      







   // NJets 6,7 HT 1250,1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*elecIsoTAPUp");
//if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*elecIsoTAPUp");
if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*elecIsoTAPUp");
if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 450)*elecIsoTAPUp");
if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      




   // NJets 6,7 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*elecIsoTAPUp");
//if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*elecIsoTAPUp");
if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 300 )*elecIsoTAPUp");
if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      



// --------------------------------------------------------------------------------------------------






   // NJets 8 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 7.5 && MHT > 200 )*elecIsoTAPUp");
if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      






   // NJets 8 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 7.5 && MHT > 100 && MHT < 200  )*elecIsoTAPUp");
//if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
 //     

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 7.5 && MHT > 200 )*elecIsoTAPUp");
if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      





   // NJets 8 HT 1000,1250
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 7.5 && MHT > 100 && MHT < 200  )*elecIsoTAPUp");
//if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
//      

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 7.5 && MHT > 200 )*elecIsoTAPUp");
if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      








   // NJets 8 HT 1250,1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 7.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*elecIsoTAPUp");
//if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
 //     

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 7.5 && MHT > 200  )*elecIsoTAPUp");
if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      




   // NJets 8 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 7.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*elecIsoTAPUp");
//if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
//      

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 7.5 && MHT > 200  )*elecIsoTAPUp");
if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      








  // go though all the bins
   // NJets 3,5 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*elecIsoTAPDown");
if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      



   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*elecIsoTAPDown");
if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*elecIsoTAPDown");
if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*elecIsoTAPDown");
if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      





   // NJets 3,5 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*elecIsoTAPDown");
//if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*elecIsoTAPDown");
if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*elecIsoTAPDown");
if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*elecIsoTAPDown");
if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*elecIsoTAPDown");
if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      




   // NJets 3,5 HT 1000,1250
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*elecIsoTAPDown");
//if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*elecIsoTAPDown");
if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*elecIsoTAPDown");
if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*elecIsoTAPDown");
if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*elecIsoTAPDown");
if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      





   // NJets 3,5 HT 1250,1500
 //  tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*elecIsoTAPDown");
//if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*elecIsoTAPDown");
if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*elecIsoTAPDown");
if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 450)*elecIsoTAPDown");
if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      




   // NJets 3,5 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*elecIsoTAPDown");
//if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*elecIsoTAPDown");
if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 300 )*elecIsoTAPDown");
if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      










   // NJets 6,7 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*elecIsoTAPDown");
if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*elecIsoTAPDown");
if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*elecIsoTAPDown");
if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      





   // NJets 6,7 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*elecIsoTAPDown");
//if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*elecIsoTAPDown");
if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*elecIsoTAPDown");
if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*elecIsoTAPDown");
if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      






   // NJets 6,7 HT 1000,1250
 //  tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*elecIsoTAPDown");
//if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*elecIsoTAPDown");
if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*elecIsoTAPDown");
if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*elecIsoTAPDown");
if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      







   // NJets 6,7 HT 1250,1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*elecIsoTAPDown");
//if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*elecIsoTAPDown");
if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*elecIsoTAPDown");
if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 450)*elecIsoTAPDown");
if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      




   // NJets 6,7 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*elecIsoTAPDown");
//if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*elecIsoTAPDown");
if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 300 )*elecIsoTAPDown");
if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      



// --------------------------------------------------------------------------------------------------






   // NJets 8 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 7.5 && MHT > 200 )*elecIsoTAPDown");
if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      






   // NJets 8 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 7.5 && MHT > 100 && MHT < 200  )*elecIsoTAPDown");
//if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
 //     

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 7.5 && MHT > 200 )*elecIsoTAPDown");
if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      





   // NJets 8 HT 1000,1250
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 7.5 && MHT > 100 && MHT < 200  )*elecIsoTAPDown");
//if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
//      

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 7.5 && MHT > 200 )*elecIsoTAPDown");
if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      








   // NJets 8 HT 1250,1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 7.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*elecIsoTAPDown");
//if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
 //     

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 7.5 && MHT > 200  )*elecIsoTAPDown");
if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      




   // NJets 8 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 7.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*elecIsoTAPDown");
//if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
//      

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 7.5 && MHT > 200  )*elecIsoTAPDown");
if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      





///////////////// muon reco tag and probe eff







///// elec reco tag and probe eff unceratinty




  // go though all the bins
   // NJets 3,5 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*elecRecoTAPUp");
if( outhist2->Integral()<0.001) elecrecoup.push_back(-1);else elecrecoup.push_back(outhist2->Integral());
      



   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*elecRecoTAPUp");
if( outhist2->Integral()<0.001) elecrecoup.push_back(-1);else elecrecoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*elecRecoTAPUp");
if( outhist2->Integral()<0.001) elecrecoup.push_back(-1);else elecrecoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*elecRecoTAPUp");
if( outhist2->Integral()<0.001) elecrecoup.push_back(-1);else elecrecoup.push_back(outhist2->Integral());
      





   // NJets 3,5 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*elecRecoTAPUp");
//if( outhist2->Integral()<0.001) elecrecoup.push_back(-1);else elecrecoup.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*elecRecoTAPUp");
if( outhist2->Integral()<0.001) elecrecoup.push_back(-1);else elecrecoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*elecRecoTAPUp");
if( outhist2->Integral()<0.001) elecrecoup.push_back(-1);else elecrecoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*elecRecoTAPUp");
if( outhist2->Integral()<0.001) elecrecoup.push_back(-1);else elecrecoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*elecRecoTAPUp");
if( outhist2->Integral()<0.001) elecrecoup.push_back(-1);else elecrecoup.push_back(outhist2->Integral());
      




   // NJets 3,5 HT 1000,1250
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*elecRecoTAPUp");
//if( outhist2->Integral()<0.001) elecrecoup.push_back(-1);else elecrecoup.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*elecRecoTAPUp");
if( outhist2->Integral()<0.001) elecrecoup.push_back(-1);else elecrecoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*elecRecoTAPUp");
if( outhist2->Integral()<0.001) elecrecoup.push_back(-1);else elecrecoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*elecRecoTAPUp");
if( outhist2->Integral()<0.001) elecrecoup.push_back(-1);else elecrecoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*elecRecoTAPUp");
if( outhist2->Integral()<0.001) elecrecoup.push_back(-1);else elecrecoup.push_back(outhist2->Integral());
      





   // NJets 3,5 HT 1250,1500
 //  tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*elecRecoTAPUp");
//if( outhist2->Integral()<0.001) elecrecoup.push_back(-1);else elecrecoup.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*elecRecoTAPUp");
if( outhist2->Integral()<0.001) elecrecoup.push_back(-1);else elecrecoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*elecRecoTAPUp");
if( outhist2->Integral()<0.001) elecrecoup.push_back(-1);else elecrecoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 450)*elecRecoTAPUp");
if( outhist2->Integral()<0.001) elecrecoup.push_back(-1);else elecrecoup.push_back(outhist2->Integral());
      




   // NJets 3,5 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*elecRecoTAPUp");
//if( outhist2->Integral()<0.001) elecrecoup.push_back(-1);else elecrecoup.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*elecRecoTAPUp");
if( outhist2->Integral()<0.001) elecrecoup.push_back(-1);else elecrecoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 300 )*elecRecoTAPUp");
if( outhist2->Integral()<0.001) elecrecoup.push_back(-1);else elecrecoup.push_back(outhist2->Integral());
      










   // NJets 6,7 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*elecRecoTAPUp");
if( outhist2->Integral()<0.001) elecrecoup.push_back(-1);else elecrecoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*elecRecoTAPUp");
if( outhist2->Integral()<0.001) elecrecoup.push_back(-1);else elecrecoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*elecRecoTAPUp");
if( outhist2->Integral()<0.001) elecrecoup.push_back(-1);else elecrecoup.push_back(outhist2->Integral());
      





   // NJets 6,7 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*elecRecoTAPUp");
//if( outhist2->Integral()<0.001) elecrecoup.push_back(-1);else elecrecoup.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*elecRecoTAPUp");
if( outhist2->Integral()<0.001) elecrecoup.push_back(-1);else elecrecoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*elecRecoTAPUp");
if( outhist2->Integral()<0.001) elecrecoup.push_back(-1);else elecrecoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*elecRecoTAPUp");
if( outhist2->Integral()<0.001) elecrecoup.push_back(-1);else elecrecoup.push_back(outhist2->Integral());
      






   // NJets 6,7 HT 1000,1250
 //  tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*elecRecoTAPUp");
//if( outhist2->Integral()<0.001) elecrecoup.push_back(-1);else elecrecoup.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*elecRecoTAPUp");
if( outhist2->Integral()<0.001) elecrecoup.push_back(-1);else elecrecoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*elecRecoTAPUp");
if( outhist2->Integral()<0.001) elecrecoup.push_back(-1);else elecrecoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*elecRecoTAPUp");
if( outhist2->Integral()<0.001) elecrecoup.push_back(-1);else elecrecoup.push_back(outhist2->Integral());
      







   // NJets 6,7 HT 1250,1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*elecRecoTAPUp");
//if( outhist2->Integral()<0.001) elecrecoup.push_back(-1);else elecrecoup.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*elecRecoTAPUp");
if( outhist2->Integral()<0.001) elecrecoup.push_back(-1);else elecrecoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*elecRecoTAPUp");
if( outhist2->Integral()<0.001) elecrecoup.push_back(-1);else elecrecoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 450)*elecRecoTAPUp");
if( outhist2->Integral()<0.001) elecrecoup.push_back(-1);else elecrecoup.push_back(outhist2->Integral());
      




   // NJets 6,7 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*elecRecoTAPUp");
//if( outhist2->Integral()<0.001) elecrecoup.push_back(-1);else elecrecoup.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*elecRecoTAPUp");
if( outhist2->Integral()<0.001) elecrecoup.push_back(-1);else elecrecoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 300 )*elecRecoTAPUp");
if( outhist2->Integral()<0.001) elecrecoup.push_back(-1);else elecrecoup.push_back(outhist2->Integral());
      



// --------------------------------------------------------------------------------------------------






   // NJets 8 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 7.5 && MHT > 200 )*elecRecoTAPUp");
if( outhist2->Integral()<0.001) elecrecoup.push_back(-1);else elecrecoup.push_back(outhist2->Integral());
      






   // NJets 8 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 7.5 && MHT > 100 && MHT < 200  )*elecRecoTAPUp");
//if( outhist2->Integral()<0.001) elecrecoup.push_back(-1);else elecrecoup.push_back(outhist2->Integral());
 //     

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 7.5 && MHT > 200 )*elecRecoTAPUp");
if( outhist2->Integral()<0.001) elecrecoup.push_back(-1);else elecrecoup.push_back(outhist2->Integral());
      





   // NJets 8 HT 1000,1250
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 7.5 && MHT > 100 && MHT < 200  )*elecRecoTAPUp");
//if( outhist2->Integral()<0.001) elecrecoup.push_back(-1);else elecrecoup.push_back(outhist2->Integral());
//      

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 7.5 && MHT > 200 )*elecRecoTAPUp");
if( outhist2->Integral()<0.001) elecrecoup.push_back(-1);else elecrecoup.push_back(outhist2->Integral());
      








   // NJets 8 HT 1250,1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 7.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*elecRecoTAPUp");
//if( outhist2->Integral()<0.001) elecrecoup.push_back(-1);else elecrecoup.push_back(outhist2->Integral());
 //     

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 7.5 && MHT > 200  )*elecRecoTAPUp");
if( outhist2->Integral()<0.001) elecrecoup.push_back(-1);else elecrecoup.push_back(outhist2->Integral());
      




   // NJets 8 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 7.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*elecRecoTAPUp");
//if( outhist2->Integral()<0.001) elecrecoup.push_back(-1);else elecrecoup.push_back(outhist2->Integral());
//      

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 7.5 && MHT > 200  )*elecRecoTAPUp");
if( outhist2->Integral()<0.001) elecrecoup.push_back(-1);else elecrecoup.push_back(outhist2->Integral());
      








  // go though all the bins
   // NJets 3,5 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*elecRecoTAPDown");
if( outhist2->Integral()<0.001) elecrecodn.push_back(-1);else elecrecodn.push_back(outhist2->Integral());
      



   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*elecRecoTAPDown");
if( outhist2->Integral()<0.001) elecrecodn.push_back(-1);else elecrecodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*elecRecoTAPDown");
if( outhist2->Integral()<0.001) elecrecodn.push_back(-1);else elecrecodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*elecRecoTAPDown");
if( outhist2->Integral()<0.001) elecrecodn.push_back(-1);else elecrecodn.push_back(outhist2->Integral());
      





   // NJets 3,5 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*elecRecoTAPDown");
//if( outhist2->Integral()<0.001) elecrecodn.push_back(-1);else elecrecodn.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*elecRecoTAPDown");
if( outhist2->Integral()<0.001) elecrecodn.push_back(-1);else elecrecodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*elecRecoTAPDown");
if( outhist2->Integral()<0.001) elecrecodn.push_back(-1);else elecrecodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*elecRecoTAPDown");
if( outhist2->Integral()<0.001) elecrecodn.push_back(-1);else elecrecodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*elecRecoTAPDown");
if( outhist2->Integral()<0.001) elecrecodn.push_back(-1);else elecrecodn.push_back(outhist2->Integral());
      




   // NJets 3,5 HT 1000,1250
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*elecRecoTAPDown");
//if( outhist2->Integral()<0.001) elecrecodn.push_back(-1);else elecrecodn.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*elecRecoTAPDown");
if( outhist2->Integral()<0.001) elecrecodn.push_back(-1);else elecrecodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*elecRecoTAPDown");
if( outhist2->Integral()<0.001) elecrecodn.push_back(-1);else elecrecodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*elecRecoTAPDown");
if( outhist2->Integral()<0.001) elecrecodn.push_back(-1);else elecrecodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*elecRecoTAPDown");
if( outhist2->Integral()<0.001) elecrecodn.push_back(-1);else elecrecodn.push_back(outhist2->Integral());
      





   // NJets 3,5 HT 1250,1500
 //  tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*elecRecoTAPDown");
//if( outhist2->Integral()<0.001) elecrecodn.push_back(-1);else elecrecodn.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*elecRecoTAPDown");
if( outhist2->Integral()<0.001) elecrecodn.push_back(-1);else elecrecodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*elecRecoTAPDown");
if( outhist2->Integral()<0.001) elecrecodn.push_back(-1);else elecrecodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 450)*elecRecoTAPDown");
if( outhist2->Integral()<0.001) elecrecodn.push_back(-1);else elecrecodn.push_back(outhist2->Integral());
      




   // NJets 3,5 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*elecRecoTAPDown");
//if( outhist2->Integral()<0.001) elecrecodn.push_back(-1);else elecrecodn.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*elecRecoTAPDown");
if( outhist2->Integral()<0.001) elecrecodn.push_back(-1);else elecrecodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 300 )*elecRecoTAPDown");
if( outhist2->Integral()<0.001) elecrecodn.push_back(-1);else elecrecodn.push_back(outhist2->Integral());
      










   // NJets 6,7 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*elecRecoTAPDown");
if( outhist2->Integral()<0.001) elecrecodn.push_back(-1);else elecrecodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*elecRecoTAPDown");
if( outhist2->Integral()<0.001) elecrecodn.push_back(-1);else elecrecodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*elecRecoTAPDown");
if( outhist2->Integral()<0.001) elecrecodn.push_back(-1);else elecrecodn.push_back(outhist2->Integral());
      





   // NJets 6,7 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*elecRecoTAPDown");
//if( outhist2->Integral()<0.001) elecrecodn.push_back(-1);else elecrecodn.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*elecRecoTAPDown");
if( outhist2->Integral()<0.001) elecrecodn.push_back(-1);else elecrecodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*elecRecoTAPDown");
if( outhist2->Integral()<0.001) elecrecodn.push_back(-1);else elecrecodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*elecRecoTAPDown");
if( outhist2->Integral()<0.001) elecrecodn.push_back(-1);else elecrecodn.push_back(outhist2->Integral());
      






   // NJets 6,7 HT 1000,1250
 //  tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*elecRecoTAPDown");
//if( outhist2->Integral()<0.001) elecrecodn.push_back(-1);else elecrecodn.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*elecRecoTAPDown");
if( outhist2->Integral()<0.001) elecrecodn.push_back(-1);else elecrecodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*elecRecoTAPDown");
if( outhist2->Integral()<0.001) elecrecodn.push_back(-1);else elecrecodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*elecRecoTAPDown");
if( outhist2->Integral()<0.001) elecrecodn.push_back(-1);else elecrecodn.push_back(outhist2->Integral());
      







   // NJets 6,7 HT 1250,1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*elecRecoTAPDown");
//if( outhist2->Integral()<0.001) elecrecodn.push_back(-1);else elecrecodn.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*elecRecoTAPDown");
if( outhist2->Integral()<0.001) elecrecodn.push_back(-1);else elecrecodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*elecRecoTAPDown");
if( outhist2->Integral()<0.001) elecrecodn.push_back(-1);else elecrecodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 450)*elecRecoTAPDown");
if( outhist2->Integral()<0.001) elecrecodn.push_back(-1);else elecrecodn.push_back(outhist2->Integral());
      




   // NJets 6,7 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*elecRecoTAPDown");
//if( outhist2->Integral()<0.001) elecrecodn.push_back(-1);else elecrecodn.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*elecRecoTAPDown");
if( outhist2->Integral()<0.001) elecrecodn.push_back(-1);else elecrecodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 300 )*elecRecoTAPDown");
if( outhist2->Integral()<0.001) elecrecodn.push_back(-1);else elecrecodn.push_back(outhist2->Integral());
      



// --------------------------------------------------------------------------------------------------






   // NJets 8 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 7.5 && MHT > 200 )*elecRecoTAPDown");
if( outhist2->Integral()<0.001) elecrecodn.push_back(-1);else elecrecodn.push_back(outhist2->Integral());
      






   // NJets 8 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 7.5 && MHT > 100 && MHT < 200  )*elecRecoTAPDown");
//if( outhist2->Integral()<0.001) elecrecodn.push_back(-1);else elecrecodn.push_back(outhist2->Integral());
 //     

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 7.5 && MHT > 200 )*elecRecoTAPDown");
if( outhist2->Integral()<0.001) elecrecodn.push_back(-1);else elecrecodn.push_back(outhist2->Integral());
      





   // NJets 8 HT 1000,1250
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 7.5 && MHT > 100 && MHT < 200  )*elecRecoTAPDown");
//if( outhist2->Integral()<0.001) elecrecodn.push_back(-1);else elecrecodn.push_back(outhist2->Integral());
//      

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 7.5 && MHT > 200 )*elecRecoTAPDown");
if( outhist2->Integral()<0.001) elecrecodn.push_back(-1);else elecrecodn.push_back(outhist2->Integral());
      








   // NJets 8 HT 1250,1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 7.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*elecRecoTAPDown");
//if( outhist2->Integral()<0.001) elecrecodn.push_back(-1);else elecrecodn.push_back(outhist2->Integral());
 //     

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 7.5 && MHT > 200  )*elecRecoTAPDown");
if( outhist2->Integral()<0.001) elecrecodn.push_back(-1);else elecrecodn.push_back(outhist2->Integral());
      




   // NJets 8 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 7.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*elecRecoTAPDown");
//if( outhist2->Integral()<0.001) elecrecodn.push_back(-1);else elecrecodn.push_back(outhist2->Integral());
//      

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 7.5 && MHT > 200  )*elecRecoTAPDown");
if( outhist2->Integral()<0.001) elecrecodn.push_back(-1);else elecrecodn.push_back(outhist2->Integral());
      











































  // go though all the bins
   // NJets 3,5 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*elecIsoTAPDown");
if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      



   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*elecIsoTAPDown");
if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*elecIsoTAPDown");
if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*elecIsoTAPDown");
if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      





   // NJets 3,5 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*elecIsoTAPDown");
//if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*elecIsoTAPDown");
if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*elecIsoTAPDown");
if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*elecIsoTAPDown");
if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*elecIsoTAPDown");
if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      




   // NJets 3,5 HT 1000,1250
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*elecIsoTAPDown");
//if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*elecIsoTAPDown");
if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*elecIsoTAPDown");
if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*elecIsoTAPDown");
if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*elecIsoTAPDown");
if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      





   // NJets 3,5 HT 1250,1500
 //  tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*elecIsoTAPDown");
//if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*elecIsoTAPDown");
if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*elecIsoTAPDown");
if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 450)*elecIsoTAPDown");
if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      




   // NJets 3,5 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*elecIsoTAPDown");
//if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*elecIsoTAPDown");
if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 300 )*elecIsoTAPDown");
if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      










   // NJets 6,7 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*elecIsoTAPDown");
if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*elecIsoTAPDown");
if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*elecIsoTAPDown");
if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      





   // NJets 6,7 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*elecIsoTAPDown");
//if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*elecIsoTAPDown");
if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*elecIsoTAPDown");
if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*elecIsoTAPDown");
if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      






   // NJets 6,7 HT 1000,1250
 //  tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*elecIsoTAPDown");
//if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*elecIsoTAPDown");
if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*elecIsoTAPDown");
if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*elecIsoTAPDown");
if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      







   // NJets 6,7 HT 1250,1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*elecIsoTAPDown");
//if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*elecIsoTAPDown");
if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*elecIsoTAPDown");
if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 450)*elecIsoTAPDown");
if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      




   // NJets 6,7 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*elecIsoTAPDown");
//if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*elecIsoTAPDown");
if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 300 )*elecIsoTAPDown");
if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      



// --------------------------------------------------------------------------------------------------






   // NJets 8 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 7.5 && MHT > 200 )*elecIsoTAPDown");
if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      






   // NJets 8 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 7.5 && MHT > 100 && MHT < 200  )*elecIsoTAPDown");
//if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
 //     

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 7.5 && MHT > 200 )*elecIsoTAPDown");
if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      





   // NJets 8 HT 1000,1250
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 7.5 && MHT > 100 && MHT < 200  )*elecIsoTAPDown");
//if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
//      

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 7.5 && MHT > 200 )*elecIsoTAPDown");
if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      








   // NJets 8 HT 1250,1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 7.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*elecIsoTAPDown");
//if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
 //     

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 7.5 && MHT > 200  )*elecIsoTAPDown");
if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      




   // NJets 8 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 7.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*elecIsoTAPDown");
//if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
//      

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 7.5 && MHT > 200  )*elecIsoTAPDown");
if( outhist2->Integral()<0.001) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      







  // go though all the bins
   // NJets 3,5 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*elecIsoTAPUp");
if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      



   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*elecIsoTAPUp");
if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*elecIsoTAPUp");
if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*elecIsoTAPUp");
if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      





   // NJets 3,5 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*elecIsoTAPUp");
//if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*elecIsoTAPUp");
if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*elecIsoTAPUp");
if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*elecIsoTAPUp");
if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*elecIsoTAPUp");
if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      




   // NJets 3,5 HT 1000,1250
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*elecIsoTAPUp");
//if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*elecIsoTAPUp");
if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*elecIsoTAPUp");
if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*elecIsoTAPUp");
if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*elecIsoTAPUp");
if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      





   // NJets 3,5 HT 1250,1500
 //  tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*elecIsoTAPUp");
//if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*elecIsoTAPUp");
if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*elecIsoTAPUp");
if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 450)*elecIsoTAPUp");
if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      




   // NJets 3,5 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*elecIsoTAPUp");
//if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*elecIsoTAPUp");
if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 300 )*elecIsoTAPUp");
if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      










   // NJets 6,7 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*elecIsoTAPUp");
if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*elecIsoTAPUp");
if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*elecIsoTAPUp");
if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      





   // NJets 6,7 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*elecIsoTAPUp");
//if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*elecIsoTAPUp");
if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*elecIsoTAPUp");
if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*elecIsoTAPUp");
if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      






   // NJets 6,7 HT 1000,1250
 //  tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*elecIsoTAPUp");
//if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*elecIsoTAPUp");
if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*elecIsoTAPUp");
if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*elecIsoTAPUp");
if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      







   // NJets 6,7 HT 1250,1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*elecIsoTAPUp");
//if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*elecIsoTAPUp");
if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*elecIsoTAPUp");
if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 450)*elecIsoTAPUp");
if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      




   // NJets 6,7 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*elecIsoTAPUp");
//if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*elecIsoTAPUp");
if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 300 )*elecIsoTAPUp");
if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      



// --------------------------------------------------------------------------------------------------






   // NJets 8 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 7.5 && MHT > 200 )*elecIsoTAPUp");
if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      






   // NJets 8 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 7.5 && MHT > 100 && MHT < 200  )*elecIsoTAPUp");
//if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
 //     

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 7.5 && MHT > 200 )*elecIsoTAPUp");
if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      





   // NJets 8 HT 1000,1250
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 7.5 && MHT > 100 && MHT < 200  )*elecIsoTAPUp");
//if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
//      

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 7.5 && MHT > 200 )*elecIsoTAPUp");
if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      








   // NJets 8 HT 1250,1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 7.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*elecIsoTAPUp");
//if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
 //     

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 7.5 && MHT > 200  )*elecIsoTAPUp");
if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      




   // NJets 8 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 7.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*elecIsoTAPUp");
//if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
//      

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 7.5 && MHT > 200  )*elecIsoTAPUp");
if( outhist2->Integral()<0.001) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      





  // go though all the bins
   // NJets 3,5 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*muonRecoTAPUp");
if( outhist2->Integral()<0.001) murecoup.push_back(-1);else murecoup.push_back(outhist2->Integral());
      



   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*muonRecoTAPUp");
if( outhist2->Integral()<0.001) murecoup.push_back(-1);else murecoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*muonRecoTAPUp");
if( outhist2->Integral()<0.001) murecoup.push_back(-1);else murecoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*muonRecoTAPUp");
if( outhist2->Integral()<0.001) murecoup.push_back(-1);else murecoup.push_back(outhist2->Integral());
      





   // NJets 3,5 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*muonRecoTAPUp");
//if( outhist2->Integral()<0.001) murecoup.push_back(-1);else murecoup.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*muonRecoTAPUp");
if( outhist2->Integral()<0.001) murecoup.push_back(-1);else murecoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*muonRecoTAPUp");
if( outhist2->Integral()<0.001) murecoup.push_back(-1);else murecoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*muonRecoTAPUp");
if( outhist2->Integral()<0.001) murecoup.push_back(-1);else murecoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*muonRecoTAPUp");
if( outhist2->Integral()<0.001) murecoup.push_back(-1);else murecoup.push_back(outhist2->Integral());
      




   // NJets 3,5 HT 1000,1250
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*muonRecoTAPUp");
//if( outhist2->Integral()<0.001) murecoup.push_back(-1);else murecoup.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*muonRecoTAPUp");
if( outhist2->Integral()<0.001) murecoup.push_back(-1);else murecoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*muonRecoTAPUp");
if( outhist2->Integral()<0.001) murecoup.push_back(-1);else murecoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*muonRecoTAPUp");
if( outhist2->Integral()<0.001) murecoup.push_back(-1);else murecoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*muonRecoTAPUp");
if( outhist2->Integral()<0.001) murecoup.push_back(-1);else murecoup.push_back(outhist2->Integral());
      





   // NJets 3,5 HT 1250,1500
 //  tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*muonRecoTAPUp");
//if( outhist2->Integral()<0.001) murecoup.push_back(-1);else murecoup.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*muonRecoTAPUp");
if( outhist2->Integral()<0.001) murecoup.push_back(-1);else murecoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*muonRecoTAPUp");
if( outhist2->Integral()<0.001) murecoup.push_back(-1);else murecoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 450)*muonRecoTAPUp");
if( outhist2->Integral()<0.001) murecoup.push_back(-1);else murecoup.push_back(outhist2->Integral());
      




   // NJets 3,5 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*muonRecoTAPUp");
//if( outhist2->Integral()<0.001) murecoup.push_back(-1);else murecoup.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*muonRecoTAPUp");
if( outhist2->Integral()<0.001) murecoup.push_back(-1);else murecoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 300 )*muonRecoTAPUp");
if( outhist2->Integral()<0.001) murecoup.push_back(-1);else murecoup.push_back(outhist2->Integral());
      










   // NJets 6,7 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*muonRecoTAPUp");
if( outhist2->Integral()<0.001) murecoup.push_back(-1);else murecoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*muonRecoTAPUp");
if( outhist2->Integral()<0.001) murecoup.push_back(-1);else murecoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*muonRecoTAPUp");
if( outhist2->Integral()<0.001) murecoup.push_back(-1);else murecoup.push_back(outhist2->Integral());
      





   // NJets 6,7 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*muonRecoTAPUp");
//if( outhist2->Integral()<0.001) murecoup.push_back(-1);else murecoup.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*muonRecoTAPUp");
if( outhist2->Integral()<0.001) murecoup.push_back(-1);else murecoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*muonRecoTAPUp");
if( outhist2->Integral()<0.001) murecoup.push_back(-1);else murecoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*muonRecoTAPUp");
if( outhist2->Integral()<0.001) murecoup.push_back(-1);else murecoup.push_back(outhist2->Integral());
      






   // NJets 6,7 HT 1000,1250
 //  tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*muonRecoTAPUp");
//if( outhist2->Integral()<0.001) murecoup.push_back(-1);else murecoup.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*muonRecoTAPUp");
if( outhist2->Integral()<0.001) murecoup.push_back(-1);else murecoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*muonRecoTAPUp");
if( outhist2->Integral()<0.001) murecoup.push_back(-1);else murecoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*muonRecoTAPUp");
if( outhist2->Integral()<0.001) murecoup.push_back(-1);else murecoup.push_back(outhist2->Integral());
      







   // NJets 6,7 HT 1250,1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*muonRecoTAPUp");
//if( outhist2->Integral()<0.001) murecoup.push_back(-1);else murecoup.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*muonRecoTAPUp");
if( outhist2->Integral()<0.001) murecoup.push_back(-1);else murecoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*muonRecoTAPUp");
if( outhist2->Integral()<0.001) murecoup.push_back(-1);else murecoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 450)*muonRecoTAPUp");
if( outhist2->Integral()<0.001) murecoup.push_back(-1);else murecoup.push_back(outhist2->Integral());
      




   // NJets 6,7 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*muonRecoTAPUp");
//if( outhist2->Integral()<0.001) murecoup.push_back(-1);else murecoup.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*muonRecoTAPUp");
if( outhist2->Integral()<0.001) murecoup.push_back(-1);else murecoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 300 )*muonRecoTAPUp");
if( outhist2->Integral()<0.001) murecoup.push_back(-1);else murecoup.push_back(outhist2->Integral());
      



// --------------------------------------------------------------------------------------------------






   // NJets 8 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 7.5 && MHT > 200 )*muonRecoTAPUp");
if( outhist2->Integral()<0.001) murecoup.push_back(-1);else murecoup.push_back(outhist2->Integral());
      






   // NJets 8 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 7.5 && MHT > 100 && MHT < 200  )*muonRecoTAPUp");
//if( outhist2->Integral()<0.001) murecoup.push_back(-1);else murecoup.push_back(outhist2->Integral());
 //     

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 7.5 && MHT > 200 )*muonRecoTAPUp");
if( outhist2->Integral()<0.001) murecoup.push_back(-1);else murecoup.push_back(outhist2->Integral());
      





   // NJets 8 HT 1000,1250
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 7.5 && MHT > 100 && MHT < 200  )*muonRecoTAPUp");
//if( outhist2->Integral()<0.001) murecoup.push_back(-1);else murecoup.push_back(outhist2->Integral());
//      

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 7.5 && MHT > 200 )*muonRecoTAPUp");
if( outhist2->Integral()<0.001) murecoup.push_back(-1);else murecoup.push_back(outhist2->Integral());
      








   // NJets 8 HT 1250,1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 7.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*muonRecoTAPUp");
//if( outhist2->Integral()<0.001) murecoup.push_back(-1);else murecoup.push_back(outhist2->Integral());
 //     

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 7.5 && MHT > 200  )*muonRecoTAPUp");
if( outhist2->Integral()<0.001) murecoup.push_back(-1);else murecoup.push_back(outhist2->Integral());
      




   // NJets 8 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 7.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*muonRecoTAPUp");
//if( outhist2->Integral()<0.001) murecoup.push_back(-1);else murecoup.push_back(outhist2->Integral());
//      

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 7.5 && MHT > 200  )*muonRecoTAPUp");
if( outhist2->Integral()<0.001) murecoup.push_back(-1);else murecoup.push_back(outhist2->Integral());
      








  // go though all the bins
   // NJets 3,5 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*muonRecoTAPDown");
if( outhist2->Integral()<0.001) murecodn.push_back(-1);else murecodn.push_back(outhist2->Integral());
      



   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*muonRecoTAPDown");
if( outhist2->Integral()<0.001) murecodn.push_back(-1);else murecodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*muonRecoTAPDown");
if( outhist2->Integral()<0.001) murecodn.push_back(-1);else murecodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*muonRecoTAPDown");
if( outhist2->Integral()<0.001) murecodn.push_back(-1);else murecodn.push_back(outhist2->Integral());
      





   // NJets 3,5 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*muonRecoTAPDown");
//if( outhist2->Integral()<0.001) murecodn.push_back(-1);else murecodn.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*muonRecoTAPDown");
if( outhist2->Integral()<0.001) murecodn.push_back(-1);else murecodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*muonRecoTAPDown");
if( outhist2->Integral()<0.001) murecodn.push_back(-1);else murecodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*muonRecoTAPDown");
if( outhist2->Integral()<0.001) murecodn.push_back(-1);else murecodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*muonRecoTAPDown");
if( outhist2->Integral()<0.001) murecodn.push_back(-1);else murecodn.push_back(outhist2->Integral());
      




   // NJets 3,5 HT 1000,1250
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*muonRecoTAPDown");
//if( outhist2->Integral()<0.001) murecodn.push_back(-1);else murecodn.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*muonRecoTAPDown");
if( outhist2->Integral()<0.001) murecodn.push_back(-1);else murecodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*muonRecoTAPDown");
if( outhist2->Integral()<0.001) murecodn.push_back(-1);else murecodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*muonRecoTAPDown");
if( outhist2->Integral()<0.001) murecodn.push_back(-1);else murecodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*muonRecoTAPDown");
if( outhist2->Integral()<0.001) murecodn.push_back(-1);else murecodn.push_back(outhist2->Integral());
      





   // NJets 3,5 HT 1250,1500
 //  tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*muonRecoTAPDown");
//if( outhist2->Integral()<0.001) murecodn.push_back(-1);else murecodn.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*muonRecoTAPDown");
if( outhist2->Integral()<0.001) murecodn.push_back(-1);else murecodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*muonRecoTAPDown");
if( outhist2->Integral()<0.001) murecodn.push_back(-1);else murecodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 450)*muonRecoTAPDown");
if( outhist2->Integral()<0.001) murecodn.push_back(-1);else murecodn.push_back(outhist2->Integral());
      




   // NJets 3,5 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*muonRecoTAPDown");
//if( outhist2->Integral()<0.001) murecodn.push_back(-1);else murecodn.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*muonRecoTAPDown");
if( outhist2->Integral()<0.001) murecodn.push_back(-1);else murecodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 300 )*muonRecoTAPDown");
if( outhist2->Integral()<0.001) murecodn.push_back(-1);else murecodn.push_back(outhist2->Integral());
      










   // NJets 6,7 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*muonRecoTAPDown");
if( outhist2->Integral()<0.001) murecodn.push_back(-1);else murecodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*muonRecoTAPDown");
if( outhist2->Integral()<0.001) murecodn.push_back(-1);else murecodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*muonRecoTAPDown");
if( outhist2->Integral()<0.001) murecodn.push_back(-1);else murecodn.push_back(outhist2->Integral());
      





   // NJets 6,7 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*muonRecoTAPDown");
//if( outhist2->Integral()<0.001) murecodn.push_back(-1);else murecodn.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*muonRecoTAPDown");
if( outhist2->Integral()<0.001) murecodn.push_back(-1);else murecodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*muonRecoTAPDown");
if( outhist2->Integral()<0.001) murecodn.push_back(-1);else murecodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*muonRecoTAPDown");
if( outhist2->Integral()<0.001) murecodn.push_back(-1);else murecodn.push_back(outhist2->Integral());
      






   // NJets 6,7 HT 1000,1250
 //  tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*muonRecoTAPDown");
//if( outhist2->Integral()<0.001) murecodn.push_back(-1);else murecodn.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*muonRecoTAPDown");
if( outhist2->Integral()<0.001) murecodn.push_back(-1);else murecodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*muonRecoTAPDown");
if( outhist2->Integral()<0.001) murecodn.push_back(-1);else murecodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*muonRecoTAPDown");
if( outhist2->Integral()<0.001) murecodn.push_back(-1);else murecodn.push_back(outhist2->Integral());
      







   // NJets 6,7 HT 1250,1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*muonRecoTAPDown");
//if( outhist2->Integral()<0.001) murecodn.push_back(-1);else murecodn.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*muonRecoTAPDown");
if( outhist2->Integral()<0.001) murecodn.push_back(-1);else murecodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*muonRecoTAPDown");
if( outhist2->Integral()<0.001) murecodn.push_back(-1);else murecodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 450)*muonRecoTAPDown");
if( outhist2->Integral()<0.001) murecodn.push_back(-1);else murecodn.push_back(outhist2->Integral());
      




   // NJets 6,7 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*muonRecoTAPDown");
//if( outhist2->Integral()<0.001) murecodn.push_back(-1);else murecodn.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*muonRecoTAPDown");
if( outhist2->Integral()<0.001) murecodn.push_back(-1);else murecodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 300 )*muonRecoTAPDown");
if( outhist2->Integral()<0.001) murecodn.push_back(-1);else murecodn.push_back(outhist2->Integral());
      



// --------------------------------------------------------------------------------------------------






   // NJets 8 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 500 && HT < 800 && NJets > 7.5 && MHT > 200 )*muonRecoTAPDown");
if( outhist2->Integral()<0.001) murecodn.push_back(-1);else murecodn.push_back(outhist2->Integral());
      






   // NJets 8 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 7.5 && MHT > 100 && MHT < 200  )*muonRecoTAPDown");
//if( outhist2->Integral()<0.001) murecodn.push_back(-1);else murecodn.push_back(outhist2->Integral());
 //     

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 800 && HT < 1000 && NJets > 7.5 && MHT > 200 )*muonRecoTAPDown");
if( outhist2->Integral()<0.001) murecodn.push_back(-1);else murecodn.push_back(outhist2->Integral());
      





   // NJets 8 HT 1000,1250
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 7.5 && MHT > 100 && MHT < 200  )*muonRecoTAPDown");
//if( outhist2->Integral()<0.001) murecodn.push_back(-1);else murecodn.push_back(outhist2->Integral());
//      

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 7.5 && MHT > 200 )*muonRecoTAPDown");
if( outhist2->Integral()<0.001) murecodn.push_back(-1);else murecodn.push_back(outhist2->Integral());
      








   // NJets 8 HT 1250,1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 7.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*muonRecoTAPDown");
//if( outhist2->Integral()<0.001) murecodn.push_back(-1);else murecodn.push_back(outhist2->Integral());
 //     

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 7.5 && MHT > 200  )*muonRecoTAPDown");
if( outhist2->Integral()<0.001) murecodn.push_back(-1);else murecodn.push_back(outhist2->Integral());
      




   // NJets 8 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 7.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*muonRecoTAPDown");
//if( outhist2->Integral()<0.001) murecodn.push_back(-1);else murecodn.push_back(outhist2->Integral());
//      

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5  && MTW < 100 && HT > 1500 && NJets > 7.5 && MHT > 200  )*muonRecoTAPDown");
if( outhist2->Integral()<0.001) murecodn.push_back(-1);else murecodn.push_back(outhist2->Integral());
      















   std::cout<<std::endl<<"# Predicted events"<<std::endl;

   std::cout<<"ll_events = ";
	double baseline_check=0;
   for (int in=0;in<predictions.size();in++)
	{
	std::cout<<predictions[in]<<"  ";
	if (predictions[in]>0.1)baseline_check+=predictions[in];
	}




   std::cout<<std::endl<<std::endl<<"# Uncertainties --> stat. and syst."<<std::endl;
   std::cout<<"# uncertainties:: 2:mtw, 3:dilep, 4:acc, 5:diboson, 6:muTag&Probe, 7:elecIso, 8:elecReco"<<std::endl;
   std::cout<<std::endl<<std::endl<<"ll_uncertainty_1 = "<<std::endl;
   
	// all combined uncertainties

   for (int i=0;i<statUncertainty.size() ;i++)
   {
	std::cout<<statUncertainty[i]<<"  ";
   }

   std::cout<<std::endl<<std::endl<<"ll_uncertaintyUP_2 = "<<std::endl;
   for (int i=0;i<mtwup.size() ;i++)
   {
	std::cout<<mtwup[i]-predictions[i]<<"  ";
   }

   std::cout<<std::endl<<std::endl<<"ll_uncertaintyDN_2 = "<<std::endl;
   for (int i=0;i<mtwdn.size() ;i++)
   {
	std::cout<<predictions[i]-mtwdn[i]<<"  ";
   }

//
   std::cout<<std::endl<<std::endl<<"ll_uncertaintyUP_3 = "<<std::endl;
   for (int i=0;i<dilepup.size() ;i++)
   {
	std::cout<<dilepup[i]-predictions[i]<<"  ";
   }

   std::cout<<std::endl<<std::endl<<"ll_uncertaintyDN_3 = "<<std::endl;
   for (int i=0;i<dilepdn.size() ;i++)
   {
	std::cout<<predictions[i]-dilepdn[i]<<"  ";
   }

//
   std::cout<<std::endl<<std::endl<<"ll_uncertaintyUP_4 = "<<std::endl;
   for (int i=0;i<accup.size() ;i++)
   {
	std::cout<<accup[i]-predictions[i]<<"  ";
   }

   std::cout<<std::endl<<std::endl<<"ll_uncertaintyDN_4 = "<<std::endl;
   for (int i=0;i<accdn.size() ;i++)
   {
	std::cout<<predictions[i]-accdn[i]<<"  ";
   }

//
   std::cout<<std::endl<<std::endl<<"ll_uncertaintyUP_5 = "<<std::endl;
   for (int i=0;i<diboup.size() ;i++)
   {
	std::cout<<diboup[i]-predictions[i]<<"  ";
   }

   std::cout<<std::endl<<std::endl<<"ll_uncertaintyDN_5 = "<<std::endl;
   for (int i=0;i<dibodn.size() ;i++)
   {
	std::cout<<dibodn[i]-predictions[i]<<"  ";
   }


//
   std::cout<<std::endl<<std::endl<<"ll_uncertaintyUP_6 = "<<std::endl;
   for (int i=0;i<muisoup.size() ;i++)
   {
	std::cout<<muisoup[i]-predictions[i]<<"  ";
   }

   std::cout<<std::endl<<std::endl<<"ll_uncertaintyDN_6 = "<<std::endl;
   for (int i=0;i<muisodn.size() ;i++)
   {
	std::cout<<predictions[i]-muisodn[i]<<"  ";
   }

//
   std::cout<<std::endl<<std::endl<<"ll_uncertaintyUP_7 = "<<std::endl;
   for (int i=0;i<elecisoup.size() ;i++)
   {
	std::cout<<elecisoup[i]-predictions[i]<<"  ";
   }

   std::cout<<std::endl<<std::endl<<"ll_uncertaintyDN_7 = "<<std::endl;
   for (int i=0;i<elecisodn.size() ;i++)
   {
	std::cout<<predictions[i]-elecisodn[i]<<"  ";
   }
//
   std::cout<<std::endl<<std::endl<<"ll_uncertaintyUP_8 = "<<std::endl;
   for (int i=0;i<elecrecoup.size() ;i++)
   {
	std::cout<<elecrecoup[i]-predictions[i]<<"  ";
   }

   std::cout<<std::endl<<std::endl<<"ll_uncertaintyDN_8 = "<<std::endl;
   for (int i=0;i<elecrecodn.size() ;i++)
   {
	std::cout<<predictions[i]-elecrecodn[i]<<"  ";
   }

   std::cout<<std::endl<<std::endl<<"ll_uncertaintyUP_9 = "<<std::endl;
   for (int i=0;i<nonclosureup.size() ;i++)
   {
	std::cout<<nonclosureup[i]-predictions[i]<<"  ";
   }

   std::cout<<std::endl<<std::endl<<"ll_uncertaintyDN_9 = "<<std::endl;
   for (int i=0;i<nonclosuredn.size() ;i++)
   {
	std::cout<<predictions[i]-nonclosuredn[i]<<"  ";
   }

std::cout<<std::endl;
std::cout<<std::endl<<"predictions size"<<predictions.size()<<sted::endl;
std::cout<<std::endl<<"statUncertainty size"<<statUncertainty.size()<<sted::endl;
std::cout<<std::endl<<"mtwup size"<<mtwup.size()<<sted::endl;
std::cout<<std::endl<<"mtwdn size"<<mtwdn.size()<<sted::endl;
std::cout<<std::endl<<"dilepup size"<<dilepup.size()<<sted::endl;
std::cout<<std::endl<<"dilepdn size"<<dilepdn.size()<<sted::endl;
std::cout<<std::endl<<"accup size"<<accup.size()<<sted::endl;
std::cout<<std::endl<<"accdn size"<<accdn.size()<<sted::endl;
std::cout<<std::endl<<"muisoup size"<<muisoup.size()<<sted::endl;
std::cout<<std::endl<<"muisodn size"<<muisodn.size()<<sted::endl;
std::cout<<std::endl<<"elecisoup size"<<elecisoup.size()<<sted::endl;
std::cout<<std::endl<<"elecisodn size"<<elecisodn.size()<<sted::endl;
std::cout<<std::endl<<"murecoup size"<<murecoup.size()<<sted::endl;
std::cout<<std::endl<<"murecodn size"<<murecodn.size()<<sted::endl;
std::cout<<std::endl<<"elecrecoup size"<<elecrecoup.size()<<sted::endl;
std::cout<<std::endl<<"elecrecodn size"<<elecrecodn.size()<<sted::endl;

std::cout<<std::endl<<"baseline_check"<<baseline_check<<sted::endl;

   std::cout<<std::endl<<"# ###############################################"<<std::endl;
   std::cout<<std::endl<<"# ###############################################"<<std::endl;
   std::cout<<std::endl<<"# ###############################################"<<std::endl;
   std::cout<<std::endl<<"# ###############################################"<<std::endl;
   std::cout<<std::endl<<"# latex table"<<std::endl;
	int nbin=0;
	std::cout<<"-- needs to be replaced by slashes as well as __"<<std::endl;


   vector<double> combinedUncertainties;
   combinedUncertainties.clear();
   vector<double> resultsSorted;
   resultsSorted.clear();

for (int intNJets=1; intNJets<njetsBins.size(); intNJets++)
{	
	std::cout<<"NJets["<<njetsBins[intNJets-1]<<","<<njetsBins[intNJets]-1<<"]"<<std::endl;

	
	std::cout<<"--HT (GeV)& --MHT (GeV)& Pred. & Stat. & M_{T} & diLep & Accept. & muIso & muId & elecIso & elecId & other SM & non Closure& Tot. Sys.----"<<std::endl;
	std::cout<<"--hline"<<std::endl;

	for (int intHT=1; intHT <htBins.size(); intHT++)
	{

		for (int intMHT=1; intMHT <mhtBins.size(); intMHT++)
		{
		// continue if not a search region
		if ( (htBins[intHT-1] >1230 && mhtBins[intMHT-1]>580) || (htBins[intHT-1] >1400 && mhtBins[intMHT-1]>310) || ( mhtBins[intMHT-1]>460 && njetsBins[intNJets-1]>5.4) || (njetsBins[intNJets-1]>7.4) && mhtBins[intMHT-1]>210 )
		{continue;}
			std::cout<<htBins[intHT-1]<<"--ldots "<<htBins[intHT]<<"& "<<mhtBins[intMHT-1]<<" --ldots "<<mhtBins[intMHT] <<"  &"<<predictions[nbin]<<"   &"<<statUncertainty[nbin]<<"     &$--pm$ "<<predictions[nbin]-mtwdn[nbin]<<"  "<<"     &$--pm$ "<<predictions[nbin]-dilepdn[nbin]<<"  "<<"      &$--pm$ "<<predictions[nbin]-accdn[nbin]<<"  "<<"      &$--pm$ "<<predictions[nbin]-muisodn[nbin]<<"  "<<"  &$--pm$ "<<predictions[nbin]-murecodn[nbin]<<"  "<<"     &$--pm$ "<<predictions[nbin]-elecisodn[nbin]<<"  "<<"     &$--pm$ "<<predictions[nbin]-elecrecodn[nbin]<<"  "<<"     &$_{"<<predictions[nbin]-dibodn[nbin]<<"}^{+"<<diboup[nbin]-predictions[nbin]<<"} $ "<<"     &$_{"<<predictions[nbin]-nonclosuredn[nbin]<<"}^{+"<<nonclosureup[nbin]-predictions[nbin]<<"}$     ";
		// calculated the full uncerainty
		std::cout<<"     &$_{-"<<sqrt(statUncertainty[nbin]*statUncertainty[nbin] +
					(predictions[nbin]-mtwdn[nbin]) * (predictions[nbin]-mtwdn[nbin]) + 
					(predictions[nbin]-dilepdn[nbin]) * (predictions[nbin]-dilepdn[nbin]) + 
					(predictions[nbin]-accdn[nbin]) * ( predictions[nbin]-accdn[nbin]) +
					(predictions[nbin]-muisodn[nbin]) * (predictions[nbin]-muisodn[nbin]) + 
					(predictions[nbin]-murecodn[nbin]) * (predictions[nbin]-murecodn[nbin]) + 
					(predictions[nbin]-elecisodn[nbin]) * (predictions[nbin]-elecisodn[nbin]) + 
					(predictions[nbin]-elecrecodn[nbin]) * (predictions[nbin]-elecrecodn[nbin]) +
					(predictions[nbin]-dibodn[nbin]) * (predictions[nbin]-dibodn[nbin]) +
					(predictions[nbin]-nonclosuredn[nbin]) * (predictions[nbin]-nonclosuredn[nbin])
					)<<"}^{+"
				<<sqrt(statUncertainty[nbin] * statUncertainty[nbin] + 
					(predictions[nbin]-mtwup[nbin]) * (predictions[nbin]-mtwup[nbin]) +
					(predictions[nbin]-dilepdn[nbin]) * (predictions[nbin]-dilepdn[nbin]) + 
					(predictions[nbin]-accdn[nbin]) * ( predictions[nbin]-accdn[nbin]) +
					(predictions[nbin]-muisoup[nbin]) * (predictions[nbin]-muisoup[nbin]) + 
					(predictions[nbin]-murecoup[nbin]) * (predictions[nbin]-murecoup[nbin]) + 
					(predictions[nbin]-elecisoup[nbin]) * (predictions[nbin]-elecisoup[nbin]) + 
					(predictions[nbin]-elecrecoup[nbin]) * (predictions[nbin]-elecrecoup[nbin]) +
					(predictions[nbin]-diboup[nbin]) * (predictions[nbin]-diboup[nbin]) +
					(predictions[nbin]-nonclosureup[nbin]) * (predictions[nbin]-nonclosureup[nbin])
					
				)<<"}$ ----"<<std::endl;

//		std::cout<<"     &$_{-"<<sqrt(statUncertainty[nbin]*statUncertainty[nbin] + (predictions[nbin]-mtwdn[nbin])*(predictions[nbin]-mtwdn[nbin]) + (predictions[nbin]-dilepdn[nbin])*(predictions[nbin]-dilepdn[nbin]) + (predictions[nbin]-accdn[nbin])*(predictions[nbin]-accdn[nbin]) + (predictions[nbin]-muisodn[nbin])*(predictions[nbin]-muisodn[nbin]) + (predictions[nbin]-elecisodn[nbin])*(predictions[nbin]-elecisodn[nbin]) + (predictions[nbin]-dibodn[nbin])*(predictions[nbin]-dibodn[nbin]) ) <<"}^{+"<<sqrt((statUncertainty[nbin])*(statUncertainty[nbin]) + (mtwup[nbin]-predictions[nbin])*(mtwup[nbin]-predictions[nbin]) + (dilepup[nbin]-predictions[nbin])*(dilepup[nbin]-predictions[nbin]) + (accup[nbin]-predictions[nbin])*(accup[nbin]-predictions[nbin]) + (muisoup[nbin]-predictions[nbin])*(muisoup[nbin]-predictions[nbin]) + (murecoup[nbin]-predictions[nbin])*(murecoup[nbin]-predictions[nbin]) + (elecisoup[nbin]-predictions[nbin])*(elecisoup[nbin]-predictions[nbin]) + (elecrecoup[nbin]-predictions[nbin])*(elecrecoup[nbin]-predictions[nbin]) + (diboup[nbin]-predictions[nbin])*(diboup[nbin]-predictions[nbin]) )<<"}$ ----"<<std::endl;
		nbin++;
		resultsSorted.push_back( predictions[nbin] );
		//combinedUncertainties.push_back( sqrt(statUncertainty[nbin]*statUncertainty[nbin] + (predictions[nbin]-mtwdn[nbin])*(predictions[nbin]-mtwdn[nbin]) + (predictions[nbin]-dilepdn[nbin])*(predictions[nbin]-dilepdn[nbin]) + (predictions[nbin]-accdn[nbin])*(predictions[nbin]-accdn[nbin]) + (predictions[nbin]-muisodn[nbin])*(predictions[nbin]-muisodn[nbin]) + (predictions[nbin]-elecisodn[nbin])*(predictions[nbin]-elecisodn[nbin]) + (predictions[nbin]-dibodn[nbin])*(predictions[nbin]-dibodn[nbin])) <<"}^{+"<<sqrt((statUncertainty[nbin])*(statUncertainty[nbin]) + (mtwup[nbin]-predictions[nbin])*(mtwup[nbin]-predictions[nbin]) + (dilepup[nbin]-predictions[nbin])*(dilepup[nbin]-predictions[nbin]) + (accup[nbin]-predictions[nbin])*(accup[nbin]-predictions[nbin]) + (muisoup[nbin]-predictions[nbin])*(muisoup[nbin]-predictions[nbin]) + (murecoup[nbin]-predictions[nbin])*(murecoup[nbin]-predictions[nbin]) + (elecisoup[nbin]-predictions[nbin])*(elecisoup[nbin]-predictions[nbin]) + (diboup[nbin]-predictions[nbin])*(diboup[nbin]-predictions[nbin])) );

		}	
	}
std::cout<<std::endl<<std::endl;
}
	std::cout<<"nbinForResults:"<<nbin<<std::endl;	
	std::cout<<"HT bins"<<htBins.size()<<std::endl;
	std::cout<<"MHT bins"<<mhtBins.size()<<std::endl;
	std::cout<<"NJets bins"<<njetsBins.size()<<std::endl;	


//\HT (GeV)& \MHT (GeV)& Pred. & Stat.(\%) & tauES & Trigger & Accept. & muIDmuISO & SM Sub & non-closure & BR & Tot. Sys.\\
//\hline
//500\ldots 800& 200 \ldots 300   &1936.57      &1.8      &$_{-0.96\%}^{+3.5\%}$     &x.x\%  &$_{-3.0\%}^{+3.0\%}$

/*
  std::cout<<std::endl<<"# Predicted events"<<std::endl;

   std::cout<<"ll_events = ";
	double baseline_check=0;
   for (int in=0;in<resultsSorted.size();in++)	std::cout<<resultsSorted[in]<<"  ";

   std::cout<<std::endl<<std::endl<<"# Uncertainties --> stat. and syst."<<std::endl;
   std::cout<<"# uncertainties:: 1:AllCombined"<<std::endl;
   std::cout<<std::endl<<std::endl<<"ll_uncertainty_1 = "<<std::endl;
   for (int in=0;in<combinedUncertainties.size();in++)	std::cout<<combinedUncertainties[in]<<"  ";
std::cout<<std::endl;
*/
nbin=0;
for (int intNJets=1; intNJets<njetsBins.size(); intNJets++)
{	
	std::cout<<"NJets["<<njetsBins[intNJets-1]<<","<<njetsBins[intNJets]-1<<"]"<<std::endl;

	
	std::cout<<"--HT (GeV)& --MHT (GeV)& Pred. & Stat. & muIsoUp & muIsoDown ----"<<std::endl;
	std::cout<<"--hline"<<std::endl;

	for (int intHT=1; intHT <htBins.size(); intHT++)
	{

		for (int intMHT=1; intMHT <mhtBins.size(); intMHT++)
		{
		// continue if not a search region
		if ( (htBins[intHT-1] >1230 && mhtBins[intMHT-1]>580) || (htBins[intHT-1] >1400 && mhtBins[intMHT-1]>310) || ( mhtBins[intMHT-1]>460 && njetsBins[intNJets-1]>5.4) || (njetsBins[intNJets-1]>7.4) && mhtBins[intMHT-1]>210 )
		{continue;}
			std::cout<<htBins[intHT-1]<<"--ldots "<<htBins[intHT]<<"& "<<mhtBins[intMHT-1]<<" --ldots "<<mhtBins[intMHT] <<"  &"<<predictions[nbin]<<"   &"<<statUncertainty[nbin]<<"     &$--pm$ "<<muisoup[nbin]<<"  "<<"  &$--pm$ "<<muisodn[nbin]<<"}$     "<<std::endl;
		// calculated the full unceraint
		nbin++;
		}	
	}
std::cout<<std::endl<<std::endl;
}



}