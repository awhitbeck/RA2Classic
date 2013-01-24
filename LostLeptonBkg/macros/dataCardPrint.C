//#saving the histogramms for the efficiencies


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




 TFile* fInput = TFile::Open("data.root");
  TDirectory *dPr = (TDirectory*)fInput->Get("LostLeptonBkgProducer");
  TTree *tPr = new TTree();
  tPr = (TTree*) dPr->Get("LostLeptonBkg");
   tPr->Draw("HT>> outhist2","(muPromtMatched>0.5 && resultBBBWMTWDiLep<10 + MHT>200 + NJets>2.1 && HT >500)*resultBBBWMTWDiLep","pe");

   std::cout<<"Baseline prediction"<<outhist2->Integral()<<"  ";

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

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWDiLep");
if( outhist2->Integral()<0.1) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1); else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );



   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*resultBBBWMTWDiLep");
if( outhist2->Integral()<0.1) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1); else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*resultBBBWMTWDiLep");
if( outhist2->Integral()<0.1) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1); else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*resultBBBWMTWDiLep");
if( outhist2->Integral()<0.1) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1); else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );





   // NJets 3,5 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDiLep");
//if( outhist2->Integral()<0.1) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
//     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1); else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWDiLep");
if( outhist2->Integral()<0.1) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1); else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*resultBBBWMTWDiLep");
if( outhist2->Integral()<0.1) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1); else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*resultBBBWMTWDiLep");
if( outhist2->Integral()<0.1) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1); else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*resultBBBWMTWDiLep");
if( outhist2->Integral()<0.1) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1); else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );




   // NJets 3,5 HT 1000,1250
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDiLep");
//if( outhist2->Integral()<0.1) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
//     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1); else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWDiLep");
if( outhist2->Integral()<0.1) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1); else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*resultBBBWMTWDiLep");
if( outhist2->Integral()<0.1) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1); else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*resultBBBWMTWDiLep");
if( outhist2->Integral()<0.1) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1); else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*resultBBBWMTWDiLep");
if( outhist2->Integral()<0.1) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1); else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );





   // NJets 3,5 HT 1250,1500
 //  tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDiLep");
//if( outhist2->Integral()<0.1) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
 //    if (outhist2->Integral() <0.2) statUncertainty.push_back(-1); else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWDiLep");
if( outhist2->Integral()<0.1) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1); else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*resultBBBWMTWDiLep");
if( outhist2->Integral()<0.1) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1); else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 450)*resultBBBWMTWDiLep");
if( outhist2->Integral()<0.1) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1); else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );




   // NJets 3,5 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDiLep");
//if( outhist2->Integral()<0.1) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
 //    if (outhist2->Integral() <0.2) statUncertainty.push_back(-1); else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWDiLep");
if( outhist2->Integral()<0.1) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1); else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 300 )*resultBBBWMTWDiLep");
if( outhist2->Integral()<0.1) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1); else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );










   // NJets 6,7 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWDiLep");
if( outhist2->Integral()<0.1) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1); else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*resultBBBWMTWDiLep");
if( outhist2->Integral()<0.1) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1); else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*resultBBBWMTWDiLep");
if( outhist2->Integral()<0.1) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1); else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );





   // NJets 6,7 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDiLep");
//if( outhist2->Integral()<0.1) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
 //    if (outhist2->Integral() <0.2) statUncertainty.push_back(-1); else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWDiLep");
if( outhist2->Integral()<0.1) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1); else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*resultBBBWMTWDiLep");
if( outhist2->Integral()<0.1) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1); else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*resultBBBWMTWDiLep");
if( outhist2->Integral()<0.1) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1); else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );






   // NJets 6,7 HT 1000,1250
 //  tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDiLep");
//if( outhist2->Integral()<0.1) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
 //    if (outhist2->Integral() <0.2) statUncertainty.push_back(-1); else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWDiLep");
if( outhist2->Integral()<0.1) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1); else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*resultBBBWMTWDiLep");
if( outhist2->Integral()<0.1) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1); else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*resultBBBWMTWDiLep");
if( outhist2->Integral()<0.1) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1); else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );







   // NJets 6,7 HT 1250,1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDiLep");
//if( outhist2->Integral()<0.1) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
//     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1); else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWDiLep");
if( outhist2->Integral()<0.1) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1); else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*resultBBBWMTWDiLep");
if( outhist2->Integral()<0.1) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1); else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 450)*resultBBBWMTWDiLep");
if( outhist2->Integral()<0.1) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1); else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );




   // NJets 6,7 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDiLep");
//if( outhist2->Integral()<0.1) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
//     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1); else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWDiLep");
if( outhist2->Integral()<0.1) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1); else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 300 )*resultBBBWMTWDiLep");
if( outhist2->Integral()<0.1) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1); else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );



// --------------------------------------------------------------------------------------------------






   // NJets 8 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 7.5 && MHT > 200 )*resultBBBWMTWDiLep");
if( outhist2->Integral()<0.1) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1); else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );






   // NJets 8 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 7.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDiLep");
//if( outhist2->Integral()<0.1) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
 //    if (outhist2->Integral() <0.2) statUncertainty.push_back(-1);else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 7.5 && MHT > 200 )*resultBBBWMTWDiLep");
if( outhist2->Integral()<0.1) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1);else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );





   // NJets 8 HT 1000,1250
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 7.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDiLep");
//if( outhist2->Integral()<0.1) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
//     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1);else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 7.5 && MHT > 200 )*resultBBBWMTWDiLep");
if( outhist2->Integral()<0.1) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1);else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );








   // NJets 8 HT 1250,1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 7.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDiLep");
//if( outhist2->Integral()<0.1) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
 //    if (outhist2->Integral() <0.2) statUncertainty.push_back(-1);else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 7.5 && MHT > 200  )*resultBBBWMTWDiLep");
if( outhist2->Integral()<0.1) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1);else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );




   // NJets 8 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 7.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDiLep");
//if( outhist2->Integral()<0.1) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
//     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1);else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 7.5 && MHT > 200  )*resultBBBWMTWDiLep");
if( outhist2->Integral()<0.1) predictions.push_back(-1);else predictions.push_back(outhist2->Integral());
     if (outhist2->Integral() <0.2) statUncertainty.push_back(-1);else statUncertainty.push_back(outhist2->Integral() / sqrt(outhist2->GetEntries()) );


// --------------------------------------+++++++++++++++++++++++++++--------------------------------------
// Uncertainties



  // go though all the bins
   // NJets 3,5 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWUp");
if( outhist2->Integral()<0.1) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
      



   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*resultBBBWMTWUp");
if( outhist2->Integral()<0.1) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*resultBBBWMTWUp");
if( outhist2->Integral()<0.1) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*resultBBBWMTWUp");
if( outhist2->Integral()<0.1) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
      





   // NJets 3,5 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWUp");
//if( outhist2->Integral()<0.1) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWUp");
if( outhist2->Integral()<0.1) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*resultBBBWMTWUp");
if( outhist2->Integral()<0.1) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*resultBBBWMTWUp");
if( outhist2->Integral()<0.1) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*resultBBBWMTWUp");
if( outhist2->Integral()<0.1) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
      




   // NJets 3,5 HT 1000,1250
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWUp");
//if( outhist2->Integral()<0.1) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWUp");
if( outhist2->Integral()<0.1) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*resultBBBWMTWUp");
if( outhist2->Integral()<0.1) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*resultBBBWMTWUp");
if( outhist2->Integral()<0.1) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*resultBBBWMTWUp");
if( outhist2->Integral()<0.1) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
      





   // NJets 3,5 HT 1250,1500
 //  tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWUp");
//if( outhist2->Integral()<0.1) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWUp");
if( outhist2->Integral()<0.1) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*resultBBBWMTWUp");
if( outhist2->Integral()<0.1) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 450)*resultBBBWMTWUp");
if( outhist2->Integral()<0.1) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
      




   // NJets 3,5 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWUp");
//if( outhist2->Integral()<0.1) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWUp");
if( outhist2->Integral()<0.1) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 300 )*resultBBBWMTWUp");
if( outhist2->Integral()<0.1) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
      










   // NJets 6,7 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWUp");
if( outhist2->Integral()<0.1) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*resultBBBWMTWUp");
if( outhist2->Integral()<0.1) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*resultBBBWMTWUp");
if( outhist2->Integral()<0.1) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
      





   // NJets 6,7 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWUp");
//if( outhist2->Integral()<0.1) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWUp");
if( outhist2->Integral()<0.1) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*resultBBBWMTWUp");
if( outhist2->Integral()<0.1) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*resultBBBWMTWUp");
if( outhist2->Integral()<0.1) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
      






   // NJets 6,7 HT 1000,1250
 //  tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWUp");
//if( outhist2->Integral()<0.1) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWUp");
if( outhist2->Integral()<0.1) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*resultBBBWMTWUp");
if( outhist2->Integral()<0.1) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*resultBBBWMTWUp");
if( outhist2->Integral()<0.1) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
      







   // NJets 6,7 HT 1250,1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWUp");
//if( outhist2->Integral()<0.1) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWUp");
if( outhist2->Integral()<0.1) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*resultBBBWMTWUp");
if( outhist2->Integral()<0.1) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 450)*resultBBBWMTWUp");
if( outhist2->Integral()<0.1) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
      




   // NJets 6,7 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWUp");
//if( outhist2->Integral()<0.1) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWUp");
if( outhist2->Integral()<0.1) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 300 )*resultBBBWMTWUp");
if( outhist2->Integral()<0.1) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
      



// --------------------------------------------------------------------------------------------------






   // NJets 8 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 7.5 && MHT > 200 )*resultBBBWMTWUp");
if( outhist2->Integral()<0.1) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
      






   // NJets 8 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 7.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWUp");
//if( outhist2->Integral()<0.1) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
 //     

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 7.5 && MHT > 200 )*resultBBBWMTWUp");
if( outhist2->Integral()<0.1) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
      





   // NJets 8 HT 1000,1250
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 7.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWUp");
//if( outhist2->Integral()<0.1) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
//      

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 7.5 && MHT > 200 )*resultBBBWMTWUp");
if( outhist2->Integral()<0.1) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
      








   // NJets 8 HT 1250,1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 7.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWUp");
//if( outhist2->Integral()<0.1) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
 //     

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 7.5 && MHT > 200  )*resultBBBWMTWUp");
if( outhist2->Integral()<0.1) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
      




   // NJets 8 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 7.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWUp");
//if( outhist2->Integral()<0.1) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
//      

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 7.5 && MHT > 200  )*resultBBBWMTWUp");
if( outhist2->Integral()<0.1) mtwup.push_back(-1);else mtwup.push_back(outhist2->Integral());
      



// ------------------------------mtw down










  // go though all the bins
   // NJets 3,5 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWDown");
if( outhist2->Integral()<0.1) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
      



   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*resultBBBWMTWDown");
if( outhist2->Integral()<0.1) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*resultBBBWMTWDown");
if( outhist2->Integral()<0.1) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*resultBBBWMTWDown");
if( outhist2->Integral()<0.1) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
      





   // NJets 3,5 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDown");
//if( outhist2->Integral()<0.1) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWDown");
if( outhist2->Integral()<0.1) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*resultBBBWMTWDown");
if( outhist2->Integral()<0.1) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*resultBBBWMTWDown");
if( outhist2->Integral()<0.1) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*resultBBBWMTWDown");
if( outhist2->Integral()<0.1) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
      




   // NJets 3,5 HT 1000,1250
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDown");
//if( outhist2->Integral()<0.1) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWDown");
if( outhist2->Integral()<0.1) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*resultBBBWMTWDown");
if( outhist2->Integral()<0.1) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*resultBBBWMTWDown");
if( outhist2->Integral()<0.1) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*resultBBBWMTWDown");
if( outhist2->Integral()<0.1) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
      





   // NJets 3,5 HT 1250,1500
 //  tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDown");
//if( outhist2->Integral()<0.1) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWDown");
if( outhist2->Integral()<0.1) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*resultBBBWMTWDown");
if( outhist2->Integral()<0.1) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 450)*resultBBBWMTWDown");
if( outhist2->Integral()<0.1) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
      




   // NJets 3,5 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDown");
//if( outhist2->Integral()<0.1) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWDown");
if( outhist2->Integral()<0.1) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 300 )*resultBBBWMTWDown");
if( outhist2->Integral()<0.1) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
      










   // NJets 6,7 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWDown");
if( outhist2->Integral()<0.1) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*resultBBBWMTWDown");
if( outhist2->Integral()<0.1) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*resultBBBWMTWDown");
if( outhist2->Integral()<0.1) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
      





   // NJets 6,7 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDown");
//if( outhist2->Integral()<0.1) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWDown");
if( outhist2->Integral()<0.1) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*resultBBBWMTWDown");
if( outhist2->Integral()<0.1) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*resultBBBWMTWDown");
if( outhist2->Integral()<0.1) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
      






   // NJets 6,7 HT 1000,1250
 //  tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDown");
//if( outhist2->Integral()<0.1) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWDown");
if( outhist2->Integral()<0.1) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*resultBBBWMTWDown");
if( outhist2->Integral()<0.1) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*resultBBBWMTWDown");
if( outhist2->Integral()<0.1) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
      







   // NJets 6,7 HT 1250,1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDown");
//if( outhist2->Integral()<0.1) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWDown");
if( outhist2->Integral()<0.1) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*resultBBBWMTWDown");
if( outhist2->Integral()<0.1) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 450)*resultBBBWMTWDown");
if( outhist2->Integral()<0.1) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
      




   // NJets 6,7 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDown");
//if( outhist2->Integral()<0.1) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWDown");
if( outhist2->Integral()<0.1) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 300 )*resultBBBWMTWDown");
if( outhist2->Integral()<0.1) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
      



// --------------------------------------------------------------------------------------------------






   // NJets 8 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 7.5 && MHT > 200 )*resultBBBWMTWDown");
if( outhist2->Integral()<0.1) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
      






   // NJets 8 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 7.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDown");
//if( outhist2->Integral()<0.1) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
 //     

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 7.5 && MHT > 200 )*resultBBBWMTWDown");
if( outhist2->Integral()<0.1) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
      





   // NJets 8 HT 1000,1250
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 7.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDown");
//if( outhist2->Integral()<0.1) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
//      

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 7.5 && MHT > 200 )*resultBBBWMTWDown");
if( outhist2->Integral()<0.1) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
      








   // NJets 8 HT 1250,1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 7.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDown");
//if( outhist2->Integral()<0.1) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
 //     

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 7.5 && MHT > 200  )*resultBBBWMTWDown");
if( outhist2->Integral()<0.1) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
      




   // NJets 8 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 7.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDown");
//if( outhist2->Integral()<0.1) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
//      

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 7.5 && MHT > 200  )*resultBBBWMTWDown");
if( outhist2->Integral()<0.1) mtwdn.push_back(-1);else mtwdn.push_back(outhist2->Integral());
      




// --------------------------------------------------------- di lep uncertainty





  // go though all the bins
   // NJets 3,5 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWDiLepUp");
if( outhist2->Integral()<0.1) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
      



   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*resultBBBWMTWDiLepUp");
if( outhist2->Integral()<0.1) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*resultBBBWMTWDiLepUp");
if( outhist2->Integral()<0.1) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*resultBBBWMTWDiLepUp");
if( outhist2->Integral()<0.1) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
      





   // NJets 3,5 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDiLepUp");
//if( outhist2->Integral()<0.1) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWDiLepUp");
if( outhist2->Integral()<0.1) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*resultBBBWMTWDiLepUp");
if( outhist2->Integral()<0.1) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*resultBBBWMTWDiLepUp");
if( outhist2->Integral()<0.1) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*resultBBBWMTWDiLepUp");
if( outhist2->Integral()<0.1) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
      




   // NJets 3,5 HT 1000,1250
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDiLepUp");
//if( outhist2->Integral()<0.1) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWDiLepUp");
if( outhist2->Integral()<0.1) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*resultBBBWMTWDiLepUp");
if( outhist2->Integral()<0.1) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*resultBBBWMTWDiLepUp");
if( outhist2->Integral()<0.1) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*resultBBBWMTWDiLepUp");
if( outhist2->Integral()<0.1) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
      





   // NJets 3,5 HT 1250,1500
 //  tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDiLepUp");
//if( outhist2->Integral()<0.1) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWDiLepUp");
if( outhist2->Integral()<0.1) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*resultBBBWMTWDiLepUp");
if( outhist2->Integral()<0.1) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 450)*resultBBBWMTWDiLepUp");
if( outhist2->Integral()<0.1) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
      




   // NJets 3,5 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDiLepUp");
//if( outhist2->Integral()<0.1) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWDiLepUp");
if( outhist2->Integral()<0.1) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 300 )*resultBBBWMTWDiLepUp");
if( outhist2->Integral()<0.1) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
      










   // NJets 6,7 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWDiLepUp");
if( outhist2->Integral()<0.1) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*resultBBBWMTWDiLepUp");
if( outhist2->Integral()<0.1) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*resultBBBWMTWDiLepUp");
if( outhist2->Integral()<0.1) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
      





   // NJets 6,7 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDiLepUp");
//if( outhist2->Integral()<0.1) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWDiLepUp");
if( outhist2->Integral()<0.1) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*resultBBBWMTWDiLepUp");
if( outhist2->Integral()<0.1) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*resultBBBWMTWDiLepUp");
if( outhist2->Integral()<0.1) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
      






   // NJets 6,7 HT 1000,1250
 //  tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDiLepUp");
//if( outhist2->Integral()<0.1) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWDiLepUp");
if( outhist2->Integral()<0.1) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*resultBBBWMTWDiLepUp");
if( outhist2->Integral()<0.1) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*resultBBBWMTWDiLepUp");
if( outhist2->Integral()<0.1) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
      







   // NJets 6,7 HT 1250,1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDiLepUp");
//if( outhist2->Integral()<0.1) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWDiLepUp");
if( outhist2->Integral()<0.1) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*resultBBBWMTWDiLepUp");
if( outhist2->Integral()<0.1) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 450)*resultBBBWMTWDiLepUp");
if( outhist2->Integral()<0.1) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
      




   // NJets 6,7 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDiLepUp");
//if( outhist2->Integral()<0.1) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWDiLepUp");
if( outhist2->Integral()<0.1) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 300 )*resultBBBWMTWDiLepUp");
if( outhist2->Integral()<0.1) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
      



// --------------------------------------------------------------------------------------------------






   // NJets 8 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 7.5 && MHT > 200 )*resultBBBWMTWDiLepUp");
if( outhist2->Integral()<0.1) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
      






   // NJets 8 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 7.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDiLepUp");
//if( outhist2->Integral()<0.1) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
 //     

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 7.5 && MHT > 200 )*resultBBBWMTWDiLepUp");
if( outhist2->Integral()<0.1) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
      





   // NJets 8 HT 1000,1250
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 7.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDiLepUp");
//if( outhist2->Integral()<0.1) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
//      

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 7.5 && MHT > 200 )*resultBBBWMTWDiLepUp");
if( outhist2->Integral()<0.1) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
      








   // NJets 8 HT 1250,1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 7.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDiLepUp");
//if( outhist2->Integral()<0.1) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
 //     

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 7.5 && MHT > 200  )*resultBBBWMTWDiLepUp");
if( outhist2->Integral()<0.1) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
      




   // NJets 8 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 7.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDiLepUp");
//if( outhist2->Integral()<0.1) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
//      

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 7.5 && MHT > 200  )*resultBBBWMTWDiLepUp");
if( outhist2->Integral()<0.1) dilepup.push_back(-1);else dilepup.push_back(outhist2->Integral());
      












  // go though all the bins
   // NJets 3,5 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWDiLepDown");
if( outhist2->Integral()<0.1) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
      



   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*resultBBBWMTWDiLepDown");
if( outhist2->Integral()<0.1) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*resultBBBWMTWDiLepDown");
if( outhist2->Integral()<0.1) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*resultBBBWMTWDiLepDown");
if( outhist2->Integral()<0.1) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
      





   // NJets 3,5 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDiLepDown");
//if( outhist2->Integral()<0.1) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWDiLepDown");
if( outhist2->Integral()<0.1) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*resultBBBWMTWDiLepDown");
if( outhist2->Integral()<0.1) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*resultBBBWMTWDiLepDown");
if( outhist2->Integral()<0.1) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*resultBBBWMTWDiLepDown");
if( outhist2->Integral()<0.1) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
      




   // NJets 3,5 HT 1000,1250
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDiLepDown");
//if( outhist2->Integral()<0.1) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWDiLepDown");
if( outhist2->Integral()<0.1) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*resultBBBWMTWDiLepDown");
if( outhist2->Integral()<0.1) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*resultBBBWMTWDiLepDown");
if( outhist2->Integral()<0.1) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*resultBBBWMTWDiLepDown");
if( outhist2->Integral()<0.1) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
      





   // NJets 3,5 HT 1250,1500
 //  tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDiLepDown");
//if( outhist2->Integral()<0.1) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWDiLepDown");
if( outhist2->Integral()<0.1) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*resultBBBWMTWDiLepDown");
if( outhist2->Integral()<0.1) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 450)*resultBBBWMTWDiLepDown");
if( outhist2->Integral()<0.1) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
      




   // NJets 3,5 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDiLepDown");
//if( outhist2->Integral()<0.1) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWDiLepDown");
if( outhist2->Integral()<0.1) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 300 )*resultBBBWMTWDiLepDown");
if( outhist2->Integral()<0.1) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
      










   // NJets 6,7 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWDiLepDown");
if( outhist2->Integral()<0.1) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*resultBBBWMTWDiLepDown");
if( outhist2->Integral()<0.1) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*resultBBBWMTWDiLepDown");
if( outhist2->Integral()<0.1) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
      





   // NJets 6,7 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDiLepDown");
//if( outhist2->Integral()<0.1) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWDiLepDown");
if( outhist2->Integral()<0.1) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*resultBBBWMTWDiLepDown");
if( outhist2->Integral()<0.1) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*resultBBBWMTWDiLepDown");
if( outhist2->Integral()<0.1) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
      






   // NJets 6,7 HT 1000,1250
 //  tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDiLepDown");
//if( outhist2->Integral()<0.1) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWDiLepDown");
if( outhist2->Integral()<0.1) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*resultBBBWMTWDiLepDown");
if( outhist2->Integral()<0.1) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*resultBBBWMTWDiLepDown");
if( outhist2->Integral()<0.1) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
      







   // NJets 6,7 HT 1250,1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDiLepDown");
//if( outhist2->Integral()<0.1) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWDiLepDown");
if( outhist2->Integral()<0.1) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*resultBBBWMTWDiLepDown");
if( outhist2->Integral()<0.1) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 450)*resultBBBWMTWDiLepDown");
if( outhist2->Integral()<0.1) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
      




   // NJets 6,7 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDiLepDown");
//if( outhist2->Integral()<0.1) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultBBBWMTWDiLepDown");
if( outhist2->Integral()<0.1) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 300 )*resultBBBWMTWDiLepDown");
if( outhist2->Integral()<0.1) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
      



// --------------------------------------------------------------------------------------------------






   // NJets 8 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 7.5 && MHT > 200 )*resultBBBWMTWDiLepDown");
if( outhist2->Integral()<0.1) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
      






   // NJets 8 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 7.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDiLepDown");
//if( outhist2->Integral()<0.1) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
 //     

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 7.5 && MHT > 200 )*resultBBBWMTWDiLepDown");
if( outhist2->Integral()<0.1) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
      





   // NJets 8 HT 1000,1250
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 7.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDiLepDown");
//if( outhist2->Integral()<0.1) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
//      

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 7.5 && MHT > 200 )*resultBBBWMTWDiLepDown");
if( outhist2->Integral()<0.1) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
      








   // NJets 8 HT 1250,1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 7.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDiLepDown");
//if( outhist2->Integral()<0.1) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
 //     

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 7.5 && MHT > 200  )*resultBBBWMTWDiLepDown");
if( outhist2->Integral()<0.1) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
      




   // NJets 8 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 7.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultBBBWMTWDiLepDown");
//if( outhist2->Integral()<0.1) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
//      

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 7.5 && MHT > 200  )*resultBBBWMTWDiLepDown");
if( outhist2->Integral()<0.1) dilepdn.push_back(-1);else dilepdn.push_back(outhist2->Integral());
      







// -------------------------------------------------- acc uncertainty







  // go though all the bins
   // NJets 3,5 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultWeightBinByBinAccUp");
if( outhist2->Integral()<0.1) accup.push_back(-1);else accup.push_back(outhist2->Integral());
      



   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*resultWeightBinByBinAccUp");
if( outhist2->Integral()<0.1) accup.push_back(-1);else accup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*resultWeightBinByBinAccUp");
if( outhist2->Integral()<0.1) accup.push_back(-1);else accup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*resultWeightBinByBinAccUp");
if( outhist2->Integral()<0.1) accup.push_back(-1);else accup.push_back(outhist2->Integral());
      





   // NJets 3,5 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*resultWeightBinByBinAccUp");
//if( outhist2->Integral()<0.1) accup.push_back(-1);else accup.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultWeightBinByBinAccUp");
if( outhist2->Integral()<0.1) accup.push_back(-1);else accup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*resultWeightBinByBinAccUp");
if( outhist2->Integral()<0.1) accup.push_back(-1);else accup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*resultWeightBinByBinAccUp");
if( outhist2->Integral()<0.1) accup.push_back(-1);else accup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*resultWeightBinByBinAccUp");
if( outhist2->Integral()<0.1) accup.push_back(-1);else accup.push_back(outhist2->Integral());
      




   // NJets 3,5 HT 1000,1250
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*resultWeightBinByBinAccUp");
//if( outhist2->Integral()<0.1) accup.push_back(-1);else accup.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultWeightBinByBinAccUp");
if( outhist2->Integral()<0.1) accup.push_back(-1);else accup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*resultWeightBinByBinAccUp");
if( outhist2->Integral()<0.1) accup.push_back(-1);else accup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*resultWeightBinByBinAccUp");
if( outhist2->Integral()<0.1) accup.push_back(-1);else accup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*resultWeightBinByBinAccUp");
if( outhist2->Integral()<0.1) accup.push_back(-1);else accup.push_back(outhist2->Integral());
      





   // NJets 3,5 HT 1250,1500
 //  tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*resultWeightBinByBinAccUp");
//if( outhist2->Integral()<0.1) accup.push_back(-1);else accup.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultWeightBinByBinAccUp");
if( outhist2->Integral()<0.1) accup.push_back(-1);else accup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*resultWeightBinByBinAccUp");
if( outhist2->Integral()<0.1) accup.push_back(-1);else accup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 450)*resultWeightBinByBinAccUp");
if( outhist2->Integral()<0.1) accup.push_back(-1);else accup.push_back(outhist2->Integral());
      




   // NJets 3,5 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*resultWeightBinByBinAccUp");
//if( outhist2->Integral()<0.1) accup.push_back(-1);else accup.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultWeightBinByBinAccUp");
if( outhist2->Integral()<0.1) accup.push_back(-1);else accup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 300 )*resultWeightBinByBinAccUp");
if( outhist2->Integral()<0.1) accup.push_back(-1);else accup.push_back(outhist2->Integral());
      










   // NJets 6,7 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultWeightBinByBinAccUp");
if( outhist2->Integral()<0.1) accup.push_back(-1);else accup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*resultWeightBinByBinAccUp");
if( outhist2->Integral()<0.1) accup.push_back(-1);else accup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*resultWeightBinByBinAccUp");
if( outhist2->Integral()<0.1) accup.push_back(-1);else accup.push_back(outhist2->Integral());
      





   // NJets 6,7 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultWeightBinByBinAccUp");
//if( outhist2->Integral()<0.1) accup.push_back(-1);else accup.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultWeightBinByBinAccUp");
if( outhist2->Integral()<0.1) accup.push_back(-1);else accup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*resultWeightBinByBinAccUp");
if( outhist2->Integral()<0.1) accup.push_back(-1);else accup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*resultWeightBinByBinAccUp");
if( outhist2->Integral()<0.1) accup.push_back(-1);else accup.push_back(outhist2->Integral());
      






   // NJets 6,7 HT 1000,1250
 //  tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultWeightBinByBinAccUp");
//if( outhist2->Integral()<0.1) accup.push_back(-1);else accup.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultWeightBinByBinAccUp");
if( outhist2->Integral()<0.1) accup.push_back(-1);else accup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*resultWeightBinByBinAccUp");
if( outhist2->Integral()<0.1) accup.push_back(-1);else accup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*resultWeightBinByBinAccUp");
if( outhist2->Integral()<0.1) accup.push_back(-1);else accup.push_back(outhist2->Integral());
      







   // NJets 6,7 HT 1250,1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultWeightBinByBinAccUp");
//if( outhist2->Integral()<0.1) accup.push_back(-1);else accup.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultWeightBinByBinAccUp");
if( outhist2->Integral()<0.1) accup.push_back(-1);else accup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*resultWeightBinByBinAccUp");
if( outhist2->Integral()<0.1) accup.push_back(-1);else accup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 450)*resultWeightBinByBinAccUp");
if( outhist2->Integral()<0.1) accup.push_back(-1);else accup.push_back(outhist2->Integral());
      




   // NJets 6,7 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultWeightBinByBinAccUp");
//if( outhist2->Integral()<0.1) accup.push_back(-1);else accup.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultWeightBinByBinAccUp");
if( outhist2->Integral()<0.1) accup.push_back(-1);else accup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 300 )*resultWeightBinByBinAccUp");
if( outhist2->Integral()<0.1) accup.push_back(-1);else accup.push_back(outhist2->Integral());
      



// --------------------------------------------------------------------------------------------------






   // NJets 8 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 7.5 && MHT > 200 )*resultWeightBinByBinAccUp");
if( outhist2->Integral()<0.1) accup.push_back(-1);else accup.push_back(outhist2->Integral());
      






   // NJets 8 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 7.5 && MHT > 100 && MHT < 200  )*resultWeightBinByBinAccUp");
//if( outhist2->Integral()<0.1) accup.push_back(-1);else accup.push_back(outhist2->Integral());
 //     

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 7.5 && MHT > 200 )*resultWeightBinByBinAccUp");
if( outhist2->Integral()<0.1) accup.push_back(-1);else accup.push_back(outhist2->Integral());
      





   // NJets 8 HT 1000,1250
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 7.5 && MHT > 100 && MHT < 200  )*resultWeightBinByBinAccUp");
//if( outhist2->Integral()<0.1) accup.push_back(-1);else accup.push_back(outhist2->Integral());
//      

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 7.5 && MHT > 200 )*resultWeightBinByBinAccUp");
if( outhist2->Integral()<0.1) accup.push_back(-1);else accup.push_back(outhist2->Integral());
      








   // NJets 8 HT 1250,1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 7.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultWeightBinByBinAccUp");
//if( outhist2->Integral()<0.1) accup.push_back(-1);else accup.push_back(outhist2->Integral());
 //     

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 7.5 && MHT > 200  )*resultWeightBinByBinAccUp");
if( outhist2->Integral()<0.1) accup.push_back(-1);else accup.push_back(outhist2->Integral());
      




   // NJets 8 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 7.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultWeightBinByBinAccUp");
//if( outhist2->Integral()<0.1) accup.push_back(-1);else accup.push_back(outhist2->Integral());
//      

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 7.5 && MHT > 200  )*resultWeightBinByBinAccUp");
if( outhist2->Integral()<0.1) accup.push_back(-1);else accup.push_back(outhist2->Integral());
      















  // go though all the bins
   // NJets 3,5 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultWeightBinByBinAccDown");
if( outhist2->Integral()<0.1) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
      



   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*resultWeightBinByBinAccDown");
if( outhist2->Integral()<0.1) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*resultWeightBinByBinAccDown");
if( outhist2->Integral()<0.1) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*resultWeightBinByBinAccDown");
if( outhist2->Integral()<0.1) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
      





   // NJets 3,5 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*resultWeightBinByBinAccDown");
//if( outhist2->Integral()<0.1) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultWeightBinByBinAccDown");
if( outhist2->Integral()<0.1) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*resultWeightBinByBinAccDown");
if( outhist2->Integral()<0.1) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*resultWeightBinByBinAccDown");
if( outhist2->Integral()<0.1) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*resultWeightBinByBinAccDown");
if( outhist2->Integral()<0.1) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
      




   // NJets 3,5 HT 1000,1250
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*resultWeightBinByBinAccDown");
//if( outhist2->Integral()<0.1) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultWeightBinByBinAccDown");
if( outhist2->Integral()<0.1) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*resultWeightBinByBinAccDown");
if( outhist2->Integral()<0.1) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*resultWeightBinByBinAccDown");
if( outhist2->Integral()<0.1) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*resultWeightBinByBinAccDown");
if( outhist2->Integral()<0.1) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
      





   // NJets 3,5 HT 1250,1500
 //  tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*resultWeightBinByBinAccDown");
//if( outhist2->Integral()<0.1) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultWeightBinByBinAccDown");
if( outhist2->Integral()<0.1) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*resultWeightBinByBinAccDown");
if( outhist2->Integral()<0.1) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 450)*resultWeightBinByBinAccDown");
if( outhist2->Integral()<0.1) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
      




   // NJets 3,5 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*resultWeightBinByBinAccDown");
//if( outhist2->Integral()<0.1) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultWeightBinByBinAccDown");
if( outhist2->Integral()<0.1) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 300 )*resultWeightBinByBinAccDown");
if( outhist2->Integral()<0.1) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
      










   // NJets 6,7 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultWeightBinByBinAccDown");
if( outhist2->Integral()<0.1) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*resultWeightBinByBinAccDown");
if( outhist2->Integral()<0.1) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*resultWeightBinByBinAccDown");
if( outhist2->Integral()<0.1) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
      





   // NJets 6,7 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultWeightBinByBinAccDown");
//if( outhist2->Integral()<0.1) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultWeightBinByBinAccDown");
if( outhist2->Integral()<0.1) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*resultWeightBinByBinAccDown");
if( outhist2->Integral()<0.1) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*resultWeightBinByBinAccDown");
if( outhist2->Integral()<0.1) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
      






   // NJets 6,7 HT 1000,1250
 //  tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultWeightBinByBinAccDown");
//if( outhist2->Integral()<0.1) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultWeightBinByBinAccDown");
if( outhist2->Integral()<0.1) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*resultWeightBinByBinAccDown");
if( outhist2->Integral()<0.1) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*resultWeightBinByBinAccDown");
if( outhist2->Integral()<0.1) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
      







   // NJets 6,7 HT 1250,1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultWeightBinByBinAccDown");
//if( outhist2->Integral()<0.1) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultWeightBinByBinAccDown");
if( outhist2->Integral()<0.1) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*resultWeightBinByBinAccDown");
if( outhist2->Integral()<0.1) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 450)*resultWeightBinByBinAccDown");
if( outhist2->Integral()<0.1) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
      




   // NJets 6,7 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultWeightBinByBinAccDown");
//if( outhist2->Integral()<0.1) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultWeightBinByBinAccDown");
if( outhist2->Integral()<0.1) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 300 )*resultWeightBinByBinAccDown");
if( outhist2->Integral()<0.1) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
      



// --------------------------------------------------------------------------------------------------






   // NJets 8 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 7.5 && MHT > 200 )*resultWeightBinByBinAccDown");
if( outhist2->Integral()<0.1) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
      






   // NJets 8 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 7.5 && MHT > 100 && MHT < 200  )*resultWeightBinByBinAccDown");
//if( outhist2->Integral()<0.1) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
 //     

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 7.5 && MHT > 200 )*resultWeightBinByBinAccDown");
if( outhist2->Integral()<0.1) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
      





   // NJets 8 HT 1000,1250
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 7.5 && MHT > 100 && MHT < 200  )*resultWeightBinByBinAccDown");
//if( outhist2->Integral()<0.1) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
//      

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 7.5 && MHT > 200 )*resultWeightBinByBinAccDown");
if( outhist2->Integral()<0.1) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
      








   // NJets 8 HT 1250,1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 7.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultWeightBinByBinAccDown");
//if( outhist2->Integral()<0.1) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
 //     

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 7.5 && MHT > 200  )*resultWeightBinByBinAccDown");
if( outhist2->Integral()<0.1) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
      




   // NJets 8 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 7.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultWeightBinByBinAccDown");
//if( outhist2->Integral()<0.1) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
//      

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 7.5 && MHT > 200  )*resultWeightBinByBinAccDown");
if( outhist2->Integral()<0.1) accdn.push_back(-1);else accdn.push_back(outhist2->Integral());
      







// -------------------------------------------------------dibson uncertainty








  // go though all the bins
   // NJets 3,5 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultWeightBinByBinDiBosonUp");
if( outhist2->Integral()<0.1) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
      



   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*resultWeightBinByBinDiBosonUp");
if( outhist2->Integral()<0.1) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*resultWeightBinByBinDiBosonUp");
if( outhist2->Integral()<0.1) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*resultWeightBinByBinDiBosonUp");
if( outhist2->Integral()<0.1) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
      





   // NJets 3,5 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*resultWeightBinByBinDiBosonUp");
//if( outhist2->Integral()<0.1) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultWeightBinByBinDiBosonUp");
if( outhist2->Integral()<0.1) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*resultWeightBinByBinDiBosonUp");
if( outhist2->Integral()<0.1) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*resultWeightBinByBinDiBosonUp");
if( outhist2->Integral()<0.1) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*resultWeightBinByBinDiBosonUp");
if( outhist2->Integral()<0.1) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
      




   // NJets 3,5 HT 1000,1250
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*resultWeightBinByBinDiBosonUp");
//if( outhist2->Integral()<0.1) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultWeightBinByBinDiBosonUp");
if( outhist2->Integral()<0.1) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*resultWeightBinByBinDiBosonUp");
if( outhist2->Integral()<0.1) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*resultWeightBinByBinDiBosonUp");
if( outhist2->Integral()<0.1) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*resultWeightBinByBinDiBosonUp");
if( outhist2->Integral()<0.1) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
      





   // NJets 3,5 HT 1250,1500
 //  tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*resultWeightBinByBinDiBosonUp");
//if( outhist2->Integral()<0.1) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultWeightBinByBinDiBosonUp");
if( outhist2->Integral()<0.1) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*resultWeightBinByBinDiBosonUp");
if( outhist2->Integral()<0.1) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 450)*resultWeightBinByBinDiBosonUp");
if( outhist2->Integral()<0.1) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
      




   // NJets 3,5 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*resultWeightBinByBinDiBosonUp");
//if( outhist2->Integral()<0.1) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultWeightBinByBinDiBosonUp");
if( outhist2->Integral()<0.1) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 300 )*resultWeightBinByBinDiBosonUp");
if( outhist2->Integral()<0.1) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
      










   // NJets 6,7 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultWeightBinByBinDiBosonUp");
if( outhist2->Integral()<0.1) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*resultWeightBinByBinDiBosonUp");
if( outhist2->Integral()<0.1) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*resultWeightBinByBinDiBosonUp");
if( outhist2->Integral()<0.1) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
      





   // NJets 6,7 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultWeightBinByBinDiBosonUp");
//if( outhist2->Integral()<0.1) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultWeightBinByBinDiBosonUp");
if( outhist2->Integral()<0.1) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*resultWeightBinByBinDiBosonUp");
if( outhist2->Integral()<0.1) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*resultWeightBinByBinDiBosonUp");
if( outhist2->Integral()<0.1) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
      






   // NJets 6,7 HT 1000,1250
 //  tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultWeightBinByBinDiBosonUp");
//if( outhist2->Integral()<0.1) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultWeightBinByBinDiBosonUp");
if( outhist2->Integral()<0.1) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*resultWeightBinByBinDiBosonUp");
if( outhist2->Integral()<0.1) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*resultWeightBinByBinDiBosonUp");
if( outhist2->Integral()<0.1) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
      







   // NJets 6,7 HT 1250,1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultWeightBinByBinDiBosonUp");
//if( outhist2->Integral()<0.1) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultWeightBinByBinDiBosonUp");
if( outhist2->Integral()<0.1) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*resultWeightBinByBinDiBosonUp");
if( outhist2->Integral()<0.1) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 450)*resultWeightBinByBinDiBosonUp");
if( outhist2->Integral()<0.1) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
      




   // NJets 6,7 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultWeightBinByBinDiBosonUp");
//if( outhist2->Integral()<0.1) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultWeightBinByBinDiBosonUp");
if( outhist2->Integral()<0.1) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 300 )*resultWeightBinByBinDiBosonUp");
if( outhist2->Integral()<0.1) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
      



// --------------------------------------------------------------------------------------------------






   // NJets 8 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 7.5 && MHT > 200 )*resultWeightBinByBinDiBosonUp");
if( outhist2->Integral()<0.1) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
      






   // NJets 8 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 7.5 && MHT > 100 && MHT < 200  )*resultWeightBinByBinDiBosonUp");
//if( outhist2->Integral()<0.1) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
 //     

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 7.5 && MHT > 200 )*resultWeightBinByBinDiBosonUp");
if( outhist2->Integral()<0.1) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
      





   // NJets 8 HT 1000,1250
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 7.5 && MHT > 100 && MHT < 200  )*resultWeightBinByBinDiBosonUp");
//if( outhist2->Integral()<0.1) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
//      

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 7.5 && MHT > 200 )*resultWeightBinByBinDiBosonUp");
if( outhist2->Integral()<0.1) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
      








   // NJets 8 HT 1250,1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 7.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultWeightBinByBinDiBosonUp");
//if( outhist2->Integral()<0.1) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
 //     

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 7.5 && MHT > 200  )*resultWeightBinByBinDiBosonUp");
if( outhist2->Integral()<0.1) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
      




   // NJets 8 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 7.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultWeightBinByBinDiBosonUp");
//if( outhist2->Integral()<0.1) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
//      

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 7.5 && MHT > 200  )*resultWeightBinByBinDiBosonUp");
if( outhist2->Integral()<0.1) diboup.push_back(-1);else diboup.push_back(outhist2->Integral());
      









  // go though all the bins
   // NJets 3,5 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultWeightBinByBinDiBosonDown");
if( outhist2->Integral()<0.1) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
      



   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*resultWeightBinByBinDiBosonDown");
if( outhist2->Integral()<0.1) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*resultWeightBinByBinDiBosonDown");
if( outhist2->Integral()<0.1) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*resultWeightBinByBinDiBosonDown");
if( outhist2->Integral()<0.1) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
      





   // NJets 3,5 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*resultWeightBinByBinDiBosonDown");
//if( outhist2->Integral()<0.1) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultWeightBinByBinDiBosonDown");
if( outhist2->Integral()<0.1) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*resultWeightBinByBinDiBosonDown");
if( outhist2->Integral()<0.1) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*resultWeightBinByBinDiBosonDown");
if( outhist2->Integral()<0.1) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*resultWeightBinByBinDiBosonDown");
if( outhist2->Integral()<0.1) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
      




   // NJets 3,5 HT 1000,1250
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*resultWeightBinByBinDiBosonDown");
//if( outhist2->Integral()<0.1) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultWeightBinByBinDiBosonDown");
if( outhist2->Integral()<0.1) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*resultWeightBinByBinDiBosonDown");
if( outhist2->Integral()<0.1) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*resultWeightBinByBinDiBosonDown");
if( outhist2->Integral()<0.1) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*resultWeightBinByBinDiBosonDown");
if( outhist2->Integral()<0.1) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
      





   // NJets 3,5 HT 1250,1500
 //  tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*resultWeightBinByBinDiBosonDown");
//if( outhist2->Integral()<0.1) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultWeightBinByBinDiBosonDown");
if( outhist2->Integral()<0.1) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*resultWeightBinByBinDiBosonDown");
if( outhist2->Integral()<0.1) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 450)*resultWeightBinByBinDiBosonDown");
if( outhist2->Integral()<0.1) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
      




   // NJets 3,5 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*resultWeightBinByBinDiBosonDown");
//if( outhist2->Integral()<0.1) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*resultWeightBinByBinDiBosonDown");
if( outhist2->Integral()<0.1) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 300 )*resultWeightBinByBinDiBosonDown");
if( outhist2->Integral()<0.1) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
      










   // NJets 6,7 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultWeightBinByBinDiBosonDown");
if( outhist2->Integral()<0.1) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*resultWeightBinByBinDiBosonDown");
if( outhist2->Integral()<0.1) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*resultWeightBinByBinDiBosonDown");
if( outhist2->Integral()<0.1) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
      





   // NJets 6,7 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultWeightBinByBinDiBosonDown");
//if( outhist2->Integral()<0.1) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultWeightBinByBinDiBosonDown");
if( outhist2->Integral()<0.1) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*resultWeightBinByBinDiBosonDown");
if( outhist2->Integral()<0.1) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*resultWeightBinByBinDiBosonDown");
if( outhist2->Integral()<0.1) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
      






   // NJets 6,7 HT 1000,1250
 //  tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultWeightBinByBinDiBosonDown");
//if( outhist2->Integral()<0.1) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultWeightBinByBinDiBosonDown");
if( outhist2->Integral()<0.1) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*resultWeightBinByBinDiBosonDown");
if( outhist2->Integral()<0.1) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*resultWeightBinByBinDiBosonDown");
if( outhist2->Integral()<0.1) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
      







   // NJets 6,7 HT 1250,1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultWeightBinByBinDiBosonDown");
//if( outhist2->Integral()<0.1) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultWeightBinByBinDiBosonDown");
if( outhist2->Integral()<0.1) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*resultWeightBinByBinDiBosonDown");
if( outhist2->Integral()<0.1) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 450)*resultWeightBinByBinDiBosonDown");
if( outhist2->Integral()<0.1) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
      




   // NJets 6,7 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultWeightBinByBinDiBosonDown");
//if( outhist2->Integral()<0.1) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*resultWeightBinByBinDiBosonDown");
if( outhist2->Integral()<0.1) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 300 )*resultWeightBinByBinDiBosonDown");
if( outhist2->Integral()<0.1) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
      



// --------------------------------------------------------------------------------------------------






   // NJets 8 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 7.5 && MHT > 200 )*resultWeightBinByBinDiBosonDown");
if( outhist2->Integral()<0.1) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
      






   // NJets 8 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 7.5 && MHT > 100 && MHT < 200  )*resultWeightBinByBinDiBosonDown");
//if( outhist2->Integral()<0.1) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
 //     

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 7.5 && MHT > 200 )*resultWeightBinByBinDiBosonDown");
if( outhist2->Integral()<0.1) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
      





   // NJets 8 HT 1000,1250
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 7.5 && MHT > 100 && MHT < 200  )*resultWeightBinByBinDiBosonDown");
//if( outhist2->Integral()<0.1) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
//      

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 7.5 && MHT > 200 )*resultWeightBinByBinDiBosonDown");
if( outhist2->Integral()<0.1) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
      








   // NJets 8 HT 1250,1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 7.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultWeightBinByBinDiBosonDown");
//if( outhist2->Integral()<0.1) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
 //     

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 7.5 && MHT > 200  )*resultWeightBinByBinDiBosonDown");
if( outhist2->Integral()<0.1) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
      




   // NJets 8 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 7.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*resultWeightBinByBinDiBosonDown");
//if( outhist2->Integral()<0.1) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
//      

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 7.5 && MHT > 200  )*resultWeightBinByBinDiBosonDown");
if( outhist2->Integral()<0.1) dibodn.push_back(-1);else dibodn.push_back(outhist2->Integral());
      






// *-----------------------------------------------------------tag and probe uncertainty






  // go though all the bins
   // NJets 3,5 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*muonIsoTAPUp");
if( outhist2->Integral()<0.1) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
      



   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*muonIsoTAPUp");
if( outhist2->Integral()<0.1) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*muonIsoTAPUp");
if( outhist2->Integral()<0.1) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*muonIsoTAPUp");
if( outhist2->Integral()<0.1) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
      





   // NJets 3,5 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*muonIsoTAPUp");
//if( outhist2->Integral()<0.1) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*muonIsoTAPUp");
if( outhist2->Integral()<0.1) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*muonIsoTAPUp");
if( outhist2->Integral()<0.1) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*muonIsoTAPUp");
if( outhist2->Integral()<0.1) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*muonIsoTAPUp");
if( outhist2->Integral()<0.1) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
      




   // NJets 3,5 HT 1000,1250
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*muonIsoTAPUp");
//if( outhist2->Integral()<0.1) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*muonIsoTAPUp");
if( outhist2->Integral()<0.1) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*muonIsoTAPUp");
if( outhist2->Integral()<0.1) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*muonIsoTAPUp");
if( outhist2->Integral()<0.1) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*muonIsoTAPUp");
if( outhist2->Integral()<0.1) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
      





   // NJets 3,5 HT 1250,1500
 //  tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*muonIsoTAPUp");
//if( outhist2->Integral()<0.1) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*muonIsoTAPUp");
if( outhist2->Integral()<0.1) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*muonIsoTAPUp");
if( outhist2->Integral()<0.1) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 450)*muonIsoTAPUp");
if( outhist2->Integral()<0.1) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
      




   // NJets 3,5 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*muonIsoTAPUp");
//if( outhist2->Integral()<0.1) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*muonIsoTAPUp");
if( outhist2->Integral()<0.1) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 300 )*muonIsoTAPUp");
if( outhist2->Integral()<0.1) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
      










   // NJets 6,7 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*muonIsoTAPUp");
if( outhist2->Integral()<0.1) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*muonIsoTAPUp");
if( outhist2->Integral()<0.1) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*muonIsoTAPUp");
if( outhist2->Integral()<0.1) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
      





   // NJets 6,7 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*muonIsoTAPUp");
//if( outhist2->Integral()<0.1) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*muonIsoTAPUp");
if( outhist2->Integral()<0.1) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*muonIsoTAPUp");
if( outhist2->Integral()<0.1) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*muonIsoTAPUp");
if( outhist2->Integral()<0.1) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
      






   // NJets 6,7 HT 1000,1250
 //  tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*muonIsoTAPUp");
//if( outhist2->Integral()<0.1) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*muonIsoTAPUp");
if( outhist2->Integral()<0.1) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*muonIsoTAPUp");
if( outhist2->Integral()<0.1) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*muonIsoTAPUp");
if( outhist2->Integral()<0.1) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
      







   // NJets 6,7 HT 1250,1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*muonIsoTAPUp");
//if( outhist2->Integral()<0.1) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*muonIsoTAPUp");
if( outhist2->Integral()<0.1) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*muonIsoTAPUp");
if( outhist2->Integral()<0.1) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 450)*muonIsoTAPUp");
if( outhist2->Integral()<0.1) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
      




   // NJets 6,7 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*muonIsoTAPUp");
//if( outhist2->Integral()<0.1) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*muonIsoTAPUp");
if( outhist2->Integral()<0.1) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 300 )*muonIsoTAPUp");
if( outhist2->Integral()<0.1) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
      



// --------------------------------------------------------------------------------------------------






   // NJets 8 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 7.5 && MHT > 200 )*muonIsoTAPUp");
if( outhist2->Integral()<0.1) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
      






   // NJets 8 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 7.5 && MHT > 100 && MHT < 200  )*muonIsoTAPUp");
//if( outhist2->Integral()<0.1) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
 //     

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 7.5 && MHT > 200 )*muonIsoTAPUp");
if( outhist2->Integral()<0.1) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
      





   // NJets 8 HT 1000,1250
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 7.5 && MHT > 100 && MHT < 200  )*muonIsoTAPUp");
//if( outhist2->Integral()<0.1) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
//      

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 7.5 && MHT > 200 )*muonIsoTAPUp");
if( outhist2->Integral()<0.1) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
      








   // NJets 8 HT 1250,1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 7.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*muonIsoTAPUp");
//if( outhist2->Integral()<0.1) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
 //     

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 7.5 && MHT > 200  )*muonIsoTAPUp");
if( outhist2->Integral()<0.1) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
      




   // NJets 8 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 7.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*muonIsoTAPUp");
//if( outhist2->Integral()<0.1) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
//      

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 7.5 && MHT > 200  )*muonIsoTAPUp");
if( outhist2->Integral()<0.1) muisoup.push_back(-1);else muisoup.push_back(outhist2->Integral());
      








  // go though all the bins
   // NJets 3,5 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*muonIsoTAPDown");
if( outhist2->Integral()<0.1) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
      



   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*muonIsoTAPDown");
if( outhist2->Integral()<0.1) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*muonIsoTAPDown");
if( outhist2->Integral()<0.1) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*muonIsoTAPDown");
if( outhist2->Integral()<0.1) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
      





   // NJets 3,5 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*muonIsoTAPDown");
//if( outhist2->Integral()<0.1) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*muonIsoTAPDown");
if( outhist2->Integral()<0.1) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*muonIsoTAPDown");
if( outhist2->Integral()<0.1) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*muonIsoTAPDown");
if( outhist2->Integral()<0.1) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*muonIsoTAPDown");
if( outhist2->Integral()<0.1) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
      




   // NJets 3,5 HT 1000,1250
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*muonIsoTAPDown");
//if( outhist2->Integral()<0.1) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*muonIsoTAPDown");
if( outhist2->Integral()<0.1) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*muonIsoTAPDown");
if( outhist2->Integral()<0.1) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*muonIsoTAPDown");
if( outhist2->Integral()<0.1) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*muonIsoTAPDown");
if( outhist2->Integral()<0.1) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
      





   // NJets 3,5 HT 1250,1500
 //  tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*muonIsoTAPDown");
//if( outhist2->Integral()<0.1) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*muonIsoTAPDown");
if( outhist2->Integral()<0.1) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*muonIsoTAPDown");
if( outhist2->Integral()<0.1) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 450)*muonIsoTAPDown");
if( outhist2->Integral()<0.1) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
      




   // NJets 3,5 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*muonIsoTAPDown");
//if( outhist2->Integral()<0.1) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*muonIsoTAPDown");
if( outhist2->Integral()<0.1) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 300 )*muonIsoTAPDown");
if( outhist2->Integral()<0.1) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
      










   // NJets 6,7 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*muonIsoTAPDown");
if( outhist2->Integral()<0.1) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*muonIsoTAPDown");
if( outhist2->Integral()<0.1) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*muonIsoTAPDown");
if( outhist2->Integral()<0.1) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
      





   // NJets 6,7 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*muonIsoTAPDown");
//if( outhist2->Integral()<0.1) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*muonIsoTAPDown");
if( outhist2->Integral()<0.1) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*muonIsoTAPDown");
if( outhist2->Integral()<0.1) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*muonIsoTAPDown");
if( outhist2->Integral()<0.1) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
      






   // NJets 6,7 HT 1000,1250
 //  tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*muonIsoTAPDown");
//if( outhist2->Integral()<0.1) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*muonIsoTAPDown");
if( outhist2->Integral()<0.1) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*muonIsoTAPDown");
if( outhist2->Integral()<0.1) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*muonIsoTAPDown");
if( outhist2->Integral()<0.1) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
      







   // NJets 6,7 HT 1250,1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*muonIsoTAPDown");
//if( outhist2->Integral()<0.1) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*muonIsoTAPDown");
if( outhist2->Integral()<0.1) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*muonIsoTAPDown");
if( outhist2->Integral()<0.1) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 450)*muonIsoTAPDown");
if( outhist2->Integral()<0.1) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
      




   // NJets 6,7 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*muonIsoTAPDown");
//if( outhist2->Integral()<0.1) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*muonIsoTAPDown");
if( outhist2->Integral()<0.1) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 300 )*muonIsoTAPDown");
if( outhist2->Integral()<0.1) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
      



// --------------------------------------------------------------------------------------------------






   // NJets 8 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 7.5 && MHT > 200 )*muonIsoTAPDown");
if( outhist2->Integral()<0.1) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
      






   // NJets 8 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 7.5 && MHT > 100 && MHT < 200  )*muonIsoTAPDown");
//if( outhist2->Integral()<0.1) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
 //     

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 7.5 && MHT > 200 )*muonIsoTAPDown");
if( outhist2->Integral()<0.1) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
      





   // NJets 8 HT 1000,1250
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 7.5 && MHT > 100 && MHT < 200  )*muonIsoTAPDown");
//if( outhist2->Integral()<0.1) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
//      

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 7.5 && MHT > 200 )*muonIsoTAPDown");
if( outhist2->Integral()<0.1) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
      








   // NJets 8 HT 1250,1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 7.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*muonIsoTAPDown");
//if( outhist2->Integral()<0.1) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
 //     

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 7.5 && MHT > 200  )*muonIsoTAPDown");
if( outhist2->Integral()<0.1) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
      




   // NJets 8 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 7.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*muonIsoTAPDown");
//if( outhist2->Integral()<0.1) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
//      

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 7.5 && MHT > 200  )*muonIsoTAPDown");
if( outhist2->Integral()<0.1) muisodn.push_back(-1);else muisodn.push_back(outhist2->Integral());
      







// ----------------------------------------------------- elec iso











  // go though all the bins
   // NJets 3,5 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*elecIsoTAPDown");
if( outhist2->Integral()<0.1) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      



   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*elecIsoTAPDown");
if( outhist2->Integral()<0.1) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*elecIsoTAPDown");
if( outhist2->Integral()<0.1) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*elecIsoTAPDown");
if( outhist2->Integral()<0.1) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      





   // NJets 3,5 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*elecIsoTAPDown");
//if( outhist2->Integral()<0.1) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*elecIsoTAPDown");
if( outhist2->Integral()<0.1) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*elecIsoTAPDown");
if( outhist2->Integral()<0.1) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*elecIsoTAPDown");
if( outhist2->Integral()<0.1) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*elecIsoTAPDown");
if( outhist2->Integral()<0.1) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      




   // NJets 3,5 HT 1000,1250
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*elecIsoTAPDown");
//if( outhist2->Integral()<0.1) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*elecIsoTAPDown");
if( outhist2->Integral()<0.1) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*elecIsoTAPDown");
if( outhist2->Integral()<0.1) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*elecIsoTAPDown");
if( outhist2->Integral()<0.1) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*elecIsoTAPDown");
if( outhist2->Integral()<0.1) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      





   // NJets 3,5 HT 1250,1500
 //  tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*elecIsoTAPDown");
//if( outhist2->Integral()<0.1) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*elecIsoTAPDown");
if( outhist2->Integral()<0.1) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*elecIsoTAPDown");
if( outhist2->Integral()<0.1) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 450)*elecIsoTAPDown");
if( outhist2->Integral()<0.1) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      




   // NJets 3,5 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*elecIsoTAPDown");
//if( outhist2->Integral()<0.1) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*elecIsoTAPDown");
if( outhist2->Integral()<0.1) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 300 )*elecIsoTAPDown");
if( outhist2->Integral()<0.1) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      










   // NJets 6,7 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*elecIsoTAPDown");
if( outhist2->Integral()<0.1) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*elecIsoTAPDown");
if( outhist2->Integral()<0.1) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*elecIsoTAPDown");
if( outhist2->Integral()<0.1) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      





   // NJets 6,7 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*elecIsoTAPDown");
//if( outhist2->Integral()<0.1) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*elecIsoTAPDown");
if( outhist2->Integral()<0.1) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*elecIsoTAPDown");
if( outhist2->Integral()<0.1) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*elecIsoTAPDown");
if( outhist2->Integral()<0.1) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      






   // NJets 6,7 HT 1000,1250
 //  tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*elecIsoTAPDown");
//if( outhist2->Integral()<0.1) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*elecIsoTAPDown");
if( outhist2->Integral()<0.1) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*elecIsoTAPDown");
if( outhist2->Integral()<0.1) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*elecIsoTAPDown");
if( outhist2->Integral()<0.1) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      







   // NJets 6,7 HT 1250,1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*elecIsoTAPDown");
//if( outhist2->Integral()<0.1) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*elecIsoTAPDown");
if( outhist2->Integral()<0.1) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*elecIsoTAPDown");
if( outhist2->Integral()<0.1) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 450)*elecIsoTAPDown");
if( outhist2->Integral()<0.1) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      




   // NJets 6,7 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*elecIsoTAPDown");
//if( outhist2->Integral()<0.1) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*elecIsoTAPDown");
if( outhist2->Integral()<0.1) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 300 )*elecIsoTAPDown");
if( outhist2->Integral()<0.1) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      



// --------------------------------------------------------------------------------------------------






   // NJets 8 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 7.5 && MHT > 200 )*elecIsoTAPDown");
if( outhist2->Integral()<0.1) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      






   // NJets 8 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 7.5 && MHT > 100 && MHT < 200  )*elecIsoTAPDown");
//if( outhist2->Integral()<0.1) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
 //     

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 7.5 && MHT > 200 )*elecIsoTAPDown");
if( outhist2->Integral()<0.1) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      





   // NJets 8 HT 1000,1250
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 7.5 && MHT > 100 && MHT < 200  )*elecIsoTAPDown");
//if( outhist2->Integral()<0.1) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
//      

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 7.5 && MHT > 200 )*elecIsoTAPDown");
if( outhist2->Integral()<0.1) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      








   // NJets 8 HT 1250,1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 7.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*elecIsoTAPDown");
//if( outhist2->Integral()<0.1) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
 //     

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 7.5 && MHT > 200  )*elecIsoTAPDown");
if( outhist2->Integral()<0.1) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      




   // NJets 8 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 7.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*elecIsoTAPDown");
//if( outhist2->Integral()<0.1) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
//      

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 7.5 && MHT > 200  )*elecIsoTAPDown");
if( outhist2->Integral()<0.1) elecisodn.push_back(-1);else elecisodn.push_back(outhist2->Integral());
      







  // go though all the bins
   // NJets 3,5 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*elecIsoTAPUp");
if( outhist2->Integral()<0.1) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      



   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*elecIsoTAPUp");
if( outhist2->Integral()<0.1) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*elecIsoTAPUp");
if( outhist2->Integral()<0.1) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*elecIsoTAPUp");
if( outhist2->Integral()<0.1) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      





   // NJets 3,5 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*elecIsoTAPUp");
//if( outhist2->Integral()<0.1) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*elecIsoTAPUp");
if( outhist2->Integral()<0.1) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*elecIsoTAPUp");
if( outhist2->Integral()<0.1) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*elecIsoTAPUp");
if( outhist2->Integral()<0.1) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*elecIsoTAPUp");
if( outhist2->Integral()<0.1) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      




   // NJets 3,5 HT 1000,1250
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*elecIsoTAPUp");
//if( outhist2->Integral()<0.1) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*elecIsoTAPUp");
if( outhist2->Integral()<0.1) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*elecIsoTAPUp");
if( outhist2->Integral()<0.1) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 450 && MHT < 600  )*elecIsoTAPUp");
if( outhist2->Integral()<0.1) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 2.5 && NJets < 5.5 && MHT > 600 )*elecIsoTAPUp");
if( outhist2->Integral()<0.1) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      





   // NJets 3,5 HT 1250,1500
 //  tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*elecIsoTAPUp");
//if( outhist2->Integral()<0.1) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*elecIsoTAPUp");
if( outhist2->Integral()<0.1) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 300 && MHT < 450  )*elecIsoTAPUp");
if( outhist2->Integral()<0.1) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 450)*elecIsoTAPUp");
if( outhist2->Integral()<0.1) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      




   // NJets 3,5 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 100 && MHT < 200  )*elecIsoTAPUp");
//if( outhist2->Integral()<0.1) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 200 && MHT < 300  )*elecIsoTAPUp");
if( outhist2->Integral()<0.1) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 2.5 && NJets < 5.5 && MHT > 300 )*elecIsoTAPUp");
if( outhist2->Integral()<0.1) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      










   // NJets 6,7 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*elecIsoTAPUp");
if( outhist2->Integral()<0.1) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*elecIsoTAPUp");
if( outhist2->Integral()<0.1) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*elecIsoTAPUp");
if( outhist2->Integral()<0.1) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      





   // NJets 6,7 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*elecIsoTAPUp");
//if( outhist2->Integral()<0.1) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*elecIsoTAPUp");
if( outhist2->Integral()<0.1) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*elecIsoTAPUp");
if( outhist2->Integral()<0.1) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*elecIsoTAPUp");
if( outhist2->Integral()<0.1) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      






   // NJets 6,7 HT 1000,1250
 //  tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*elecIsoTAPUp");
//if( outhist2->Integral()<0.1) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
 //     


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*elecIsoTAPUp");
if( outhist2->Integral()<0.1) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*elecIsoTAPUp");
if( outhist2->Integral()<0.1) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 5.5 && NJets < 7.5 && MHT > 450 )*elecIsoTAPUp");
if( outhist2->Integral()<0.1) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      







   // NJets 6,7 HT 1250,1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*elecIsoTAPUp");
//if( outhist2->Integral()<0.1) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*elecIsoTAPUp");
if( outhist2->Integral()<0.1) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 300 && MHT < 450  )*elecIsoTAPUp");
if( outhist2->Integral()<0.1) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 450)*elecIsoTAPUp");
if( outhist2->Integral()<0.1) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      




   // NJets 6,7 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*elecIsoTAPUp");
//if( outhist2->Integral()<0.1) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
//      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 200 && MHT < 300  )*elecIsoTAPUp");
if( outhist2->Integral()<0.1) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      


   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 5.5 && NJets < 7.5 && MHT > 300 )*elecIsoTAPUp");
if( outhist2->Integral()<0.1) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      



// --------------------------------------------------------------------------------------------------






   // NJets 8 HT 500,800

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 500 && HT < 800 && NJets > 7.5 && MHT > 200 )*elecIsoTAPUp");
if( outhist2->Integral()<0.1) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      






   // NJets 8 HT 800,1000
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 7.5 && MHT > 100 && MHT < 200  )*elecIsoTAPUp");
//if( outhist2->Integral()<0.1) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
 //     

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 800 && HT < 1000 && NJets > 7.5 && MHT > 200 )*elecIsoTAPUp");
if( outhist2->Integral()<0.1) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      





   // NJets 8 HT 1000,1250
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 7.5 && MHT > 100 && MHT < 200  )*elecIsoTAPUp");
//if( outhist2->Integral()<0.1) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
//      

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1000 && HT < 1250 && NJets > 7.5 && MHT > 200 )*elecIsoTAPUp");
if( outhist2->Integral()<0.1) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      








   // NJets 8 HT 1250,1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 7.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*elecIsoTAPUp");
//if( outhist2->Integral()<0.1) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
 //     

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1250 && HT < 1500 && NJets > 7.5 && MHT > 200  )*elecIsoTAPUp");
if( outhist2->Integral()<0.1) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      




   // NJets 8 HT 1500
//   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 7.5 && NJets < 7.5 && MHT > 100 && MHT < 200  )*elecIsoTAPUp");
//if( outhist2->Integral()<0.1) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
//      

   tPr->Draw("HT>> outhist2","(muPromtMatched > 0.5 && resultBBBW < 3 && MTW < 100 && HT > 1500 && NJets > 7.5 && MHT > 200  )*elecIsoTAPUp");
if( outhist2->Integral()<0.1) elecisoup.push_back(-1);else elecisoup.push_back(outhist2->Integral());
      


















   std::cout<<std::endl<<"# Predicted events"<<std::endl;

   std::cout<<"ll_events = ";
	double baseline_check=0;
   for (int in=0;in<predictions.size();in++)
	{
	std::cout<<predictions[in]<<"  ";
	if (predictions[in]>0.1)baseline_check+=predictions[in];
	}




   std::cout<<std::endl<<std::endl<<"# Uncertainties --> stat. and syst."<<std::endl;
   std::cout<<"# uncertainties:: 2:mtw, 3:dilep, 4:acc, 5:diboson, 6:muTag&Probe, 7:elecTag&Probe"<<std::endl;
   std::cout<<std::endl<<std::endl<<"ll_uncertainty_1 = "<<std::endl;
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

std::cout<<std::endl<<"baseline_check"<<baseline_check<<sted::endl;
}