//#saving the histogramms for the efficiencies


#include <TH2F.h>
#include <TFile.h>
#include <TGraph.h>
#include <vector>
#include <TString.h>
#include <TTree.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <vector>
#include <iostream>
#include <strstream>
#include <iomanip>
#include <map>

void resultTables()
{
//gROOT->SetBatch(true);

// Define search bins and variables to use

cout.setf(ios::fixed);
cout<<setprecision(2);

// scale factor for MC to data!!! 3.789 for 19.78 fb
//double scale= 3.789;
double scale=1;
//change here between true and false to run closure or prediction on data
bool data=false;
bool debug =false;
if(data) 
{
	scale=1;
	cout<<"Running On Data for prediction and datacard!"<<endl;
}
else 
{
	cout<<"Running On MC for closure tests!"<<endl;
scale=3.789;
}
// set here the NUMBER OF BINS IMPORTANT!!
static const int BINS =36;

std::map<int,double*> binmap;
cout<<"Selected amount of bins"<<BINS<<endl;
// bin definition {LowNjet,HighNejt,LowHT,HighHT,LowMHT,HighMHT}
 double bin0 [6] = {3,100,500,10000,200,10000};


 double bin1 [6] = {3,5,500,800,200,300};
binmap[1]=bin1;
 double bin2 [6] = {3,5,500,800,300,450};
binmap[2]=bin2;
 double bin3 [6] = {3,5,500,800,450,600};
binmap[3]=bin3;
 double bin4 [6] = {3,5,500,800,600,10000};
binmap[4]=bin4;

 double bin5 [6] = {3,5,800,1000,200,300};
binmap[5]=bin5;

 double bin6 [6] = {3,5,800,1000,300,450};
binmap[6]=bin6;

 double bin7 [6] = {3,5,800,1000,450,600};
binmap[7]=bin7;
 double bin8 [6] = {3,5,800,1000,600,10000};
binmap[8]=bin8;

 double bin9 [6] = {3,5,1000,1250,200,300};
binmap[9]=bin9;
 double bin10 [6] = {3,5,1000,1250,300,450};
binmap[10]=bin10;
 double bin11 [6] = {3,5,1000,1250,450,600};
binmap[11]=bin11;
 double bin12 [6] = {3,5,1000,1250,600,10000};
binmap[12]=bin12;

 double bin13 [6] = {3,5,1250,1500,200,300};
binmap[13]=bin13;
 double bin14 [6] = {3,5,1250,1500,300,450};
binmap[14]=bin14;
 double bin15 [6] = {3,5,1250,1500,450,10000};
binmap[15]=bin15;

 double bin16 [6] = {3,5,1500,10000,200,300};
binmap[16]=bin16;
 double bin17 [6] = {3,5,1500,10000,300,10000};
binmap[17]=bin17;



 double bin18 [6] = {6,7,500,800,200,300};
binmap[18]=bin18;
 double bin19 [6] = {6,7,500,800,300,450};
binmap[19]=bin19;
 double bin20 [6] = {6,7,500,800,450,10000};
binmap[20]=bin20;
 
 double bin21 [6] = {6,7,800,1000,200,300};
binmap[21]=bin21;
 double bin22 [6] = {6,7,800,1000,300,450};
binmap[22]=bin22;
 double bin23 [6] = {6,7,800,1000,450,10000};
binmap[23]=bin23;

 double bin24 [6] = {6,7,1000,1250,200,300};
binmap[24]=bin24;
 double bin25 [6] = {6,7,1000,1250,300,450};
binmap[25]=bin25;
 double bin26 [6] = {6,7,1000,1250,450,10000};
binmap[26]=bin26;

 double bin27 [6] = {6,7,1250,1500,200,300};
binmap[27]=bin27;
 double bin28 [6] = {6,7,1250,1500,300,450};
binmap[28]=bin28;
 double bin29 [6] = {6,7,1250,1500,450,10000};
binmap[29]=bin29;

 double bin30 [6] = {6,7,1500,10000,200,300};
binmap[30]=bin30;
 double bin31 [6] = {6,7,1500,10000,300,10000};
binmap[31]=bin31;



 double bin32 [6] = {8,10000,500,800,200,10000};
binmap[32]=bin32;
 
 double bin33 [6] = {8,10000,800,1000,200,10000};
binmap[33]=bin33;

 double bin34 [6] = {8,10000,1000,1250,200,10000};
binmap[34]=bin34;

 double bin35 [6] = {8,10000,1250,1500,200,10000};
binmap[35]=bin35;

 double bin36 [6] = {8,10000,1500,10000,200,10000};
binmap[36]=bin36;




cout<<"fromMapentry 1:"<<binmap[1][1]<<endl;

for(int i=1;i<BINS+1;i++)
{

cout<<"Bin["<<i<<"] Njet["<<binmap[i][0]<<","<<binmap[i][1]<<"],HT["<<binmap[i][2]<<","<<binmap[i][3]<<"],MHT["<<binmap[i][4]<<","<<binmap[i][5]<<"]"<<endl;



}

//vector<vector <double> > binsVector{bin1,bin2,bin3,bin4,bin5,bin6,bin7,bin8,bin9,bin10,bin11,bin12,bin13,bin14,bin15,bin16,bin17,bin18,bin19,bin20,bin21,bin22,bin23,bin24,bin25,bin26,bin27,bin28,bin29,bin30,bin31,bin32,bin33,bin34,bin35,bin36};

double baselineWeightMC =0;
double baselineWeightMCStat =0;
double baselineWeightData =0;
double baselineWeightDataStat =0;

double baselineWeightEx =0;
double baselineWeightExStat =0;
double baselineWeightExMuIso =0;
double baselineWeightExMuIsoStat =0;

// uncertainties
double baselineresultBBBWMTWDiLep  =0;
double baselineresultBBBWMTWUp  =0;
double baselineresultBBBWMTWDown  =0;
double baselineresultBBBWMTWDiLepUp  =0;
double baselineresultBBBWMTWDiLepDown  =0;
double baselineresultWeightBinByBinAccUp  =0;
double baselineresultWeightBinByBinAccDown  =0;
double baselineresultWeightBBBDiBoUp  =0;
double baselineresultWeightBBBDiBoDown  =0;
double baselineresultWeightBBBNoCloUp  =0;
double baselineresultWeightBBBNoCloDown  =0;

double baselinemuonRecoTAPUp  =0;
double baselinemuonRecoTAPDown  =0;
double baselineelecIsoTAPUp  =0;
double baselineelecIsoTAPDown  =0;
double baselinemuonIsoTAPUp  =0;
double baselinemuonIsoTAPDown  =0;
double baselineelecRecoTAPUp  =0;
double baselineelecRecoTAPDown  =0;



double baselinemuonTAPdataIsoMC=0;
double baselinemuonTAPdataIsoData=0;
double baselinemuonTAPdataRecoMC=0;
double baselinemuonTAPdataRecoData=0;

double baselineelecTAPdataIsoMC=0;
double baselineelecTAPdataIsoData=0;
double baselineelecTAPdataRecoMC=0;
double baselineelecTAPdataRecoData=0;


double baselinemuonTAPdataIsoMCStat=0;
double baselinemuonTAPdataIsoDataStat=0;
double baselinemuonTAPdataRecoMCStat=0;
double baselinemuonTAPdataRecoDataStat=0;


double baselineelecTAPdataIsoMCStat=0;
double baselineelecTAPdataIsoDataStat=0;
double baselineelecTAPdataRecoMCStat=0;
double baselineelecTAPdataRecoDataStat=0;












 
// total weight
vector<double> ResultWeightMC(BINS,0);
vector<double> ResultWeightMCStat(BINS,0);

vector<double> ResultWeightData(BINS,0);
vector<double> ResultWeightDataCS(BINS,0);
vector<double> ResultWeightDataStat(BINS,0);

vector<double> ResultEx(BINS,0);
vector<double> ResultExStat(BINS,0);






// data total weights and uncertainties
vector<double> aresultBBBWMTWDiLep(BINS,0);
vector<double> aresultBBBWMTWUp(BINS,0);
vector<double> aresultBBBWMTWDown(BINS,0);
vector<double> aresultBBBWMTWDiLepUp(BINS,0);
vector<double> aresultBBBWMTWDiLepDown(BINS,0);
vector<double> aresultWeightBinByBinAccUp(BINS,0);
vector<double> aresultWeightBinByBinAccDown(BINS,0);
vector<double> aresultWeightBBBDiBoUp(BINS,0);
vector<double> aresultWeightBBBDiBoDown(BINS,0);
vector<double> aresultWeightBBBNoCloUp(BINS,0);
vector<double> aresultWeightBBBNoCloDown(BINS,0);

vector<double> amuonRecoTAPUp(BINS,0);
vector<double> amuonRecoTAPDown(BINS,0);
vector<double> aelecIsoTAPUp(BINS,0);
vector<double> aelecIsoTAPDown(BINS,0);
vector<double> amuonIsoTAPUp(BINS,0);
vector<double> amuonIsoTAPDown(BINS,0);
vector<double> aelecRecoTAPUp(BINS,0);
vector<double> aelecRecoTAPDown(BINS,0);



///muon
vector<double> MuIsoEx(BINS,0);

vector<double> MuRecoEx(BINS,0);

vector<double> MuAccEx(BINS,0);


/// elec
vector<double> ElecIsoEx(BINS,0);

vector<double> ElecRecoEx(BINS,0);

vector<double> ElecAccEx(BINS,0);




///muon
vector<double> MuIsoExStat(BINS,0);

vector<double> MuRecoExStat(BINS,0);

vector<double> MuAccExStat(BINS,0);
/// elec
vector<double> ElecIsoExStat(BINS,0);

vector<double> ElecRecoExStat(BINS,0);

vector<double> ElecAccExStat(BINS,0);



// PrMCediction
vector<double> MuIsoPrMC(BINS,0);
vector<double> MuRecoPrMC(BINS,0);
vector<double> MuAccPrMC(BINS,0);

vector<double> ElecIsoPrMC(BINS,0);
vector<double> ElecRecoPrMC(BINS,0);
vector<double> ElecAccPrMC(BINS,0);

vector<double> MuIsoPrMCStat(BINS,0);
vector<double> MuRecoPrMCStat(BINS,0);
vector<double> MuAccPrMCStat(BINS,0);

vector<double> ElecIsoPrMCStat(BINS,0);
vector<double> ElecRecoPrMCStat(BINS,0);
vector<double> ElecAccPrMCStat(BINS,0);


vector<double> muonTAPmcIsoMC(BINS,0);
vector<double> muonTAPmcIsoData(BINS,0);
vector<double> muonTAPmcMCRecoMC(BINS,0);
vector<double> muonTAPmcMCRecoData(BINS,0);

vector<double> elecTAPmcIsoMC(BINS,0);
vector<double> elecTAPmcIsoData(BINS,0);
vector<double> elecTAPmcMCRecoMC(BINS,0);
vector<double> elecTAPmcMCRecoData(BINS,0);


vector<double> muonTAPmcIsoMCStat(BINS,0);
vector<double> muonTAPmcIsoDataStat(BINS,0);
vector<double> muonTAPmcMCRecoMCStat(BINS,0);
vector<double> muonTAPmcMCRecoDataStat(BINS,0);

vector<double> elecTAPmcIsoMCStat(BINS,0);
vector<double> elecTAPmcIsoDataStat(BINS,0);
vector<double> elecTAPmcMCRecoMCStat(BINS,0);
vector<double> elecTAPmcMCRecoDataStat(BINS,0);


// PrDataediction
vector<double> MuIsoPrData(BINS,0);
vector<double> MuRecoPrData(BINS,0);
vector<double> MuAccPrData(BINS,0);

vector<double> ElecIsoPrData(BINS,0);
vector<double> ElecRecoPrData(BINS,0);
vector<double> ElecAccPrData(BINS,0);

vector<double> MuIsoPrDataStat(BINS,0);
vector<double> MuRecoPrDataStat(BINS,0);
vector<double> MuAccPrDataStat(BINS,0);

vector<double> ElecIsoPrDataStat(BINS,0);
vector<double> ElecRecoPrDataStat(BINS,0);
vector<double> ElecAccPrDataStat(BINS,0);


vector<double> muonTAPdataIsoMC(BINS,0);
vector<double> muonTAPdataIsoData(BINS,0);
vector<double> muonTAPdataRecoMC(BINS,0);
vector<double> muonTAPdataRecoData(BINS,0);

vector<double> elecTAPdataIsoMC(BINS,0);
vector<double> elecTAPdataIsoData(BINS,0);
vector<double> elecTAPdataRecoMC(BINS,0);
vector<double> elecTAPdataRecoData(BINS,0);


vector<double> muonTAPdataIsoMCStat(BINS,0);
vector<double> muonTAPdataIsoDataStat(BINS,0);
vector<double> muonTAPdataRecoMCStat(BINS,0);
vector<double> muonTAPdataRecoDataStat(BINS,0);

vector<double> elecTAPdataIsoMCStat(BINS,0);
vector<double> elecTAPdataIsoDataStat(BINS,0);
vector<double> elecTAPdataRecoMCStat(BINS,0);
vector<double> elecTAPdataRecoDataStat(BINS,0);


// file to analysis

/*
  TFile* fMC = TFile::Open("mc.root");

 TDirectory *dMCEx = (TDirectory*)fMC->Get("LostLeptonBkgMCEffCalculator");
  TTree *tMCEx = new TTree();
  tMCEx = (TTree*) dMCEx->Get("LostLeptonMCEff");


  TDirectory *dMCPr = (TDirectory*)fMC->Get("LostLeptonBkgProducer");
  TTree *tMCPr = new TTree();
  tMCPr = (TTree*) dMCPr->Get("LostLeptonBkg");

  TFile* fData = TFile::Open("data.root");

  TDirectory *dDataPr = (TDirectory*)fData->Get("LostLeptonBkgProducer");
  TTree *tDataPr = new TTree();
  tDataPr = (TTree*) dDataPr->Get("LostLeptonBkg");

*/

  vector<TString> prFiles;
  TString prTree("LostLeptonBkgProducer/LostLeptonBkg");
  vector<TString> exFiles;
  TString exTree("LostLeptonBkgMCEffCalculator/LostLeptonMCEff");

  prFiles.push_back("/scratch/adraegermc.root");
  prFiles.push_back("/scratch/adraegermc.root");

/*  if (tMCEx) cout<<"MC_Expectation Tree loaded."<<endl;
  else cout<<"Warning: NO MC_Expectation Tree loaded!!!!"<<endl;

  if (tMCPr) cout<<"MC_Prediction Tree loaded."<<endl;
  else cout<<"Warning: NO MC_Prediction Tree loaded!!!!!"<<endl;

  if (tDataPr) cout<<"Data_Prediction Tree loaded."<<endl;
  else cout<<"Warning: NO Data_Prediction Tree loaded!!!!!"<<endl;
*/

// DATA!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
cout<<"loop over prediction...";
if (1)
{
	TChain* c = new TChain(prTree);

	// change here the input for prediction Note up to now only data or mc are supoorted at a time
	if (data) 	c->Add("/scratch/adraeger/data.root");
	else c->Add("/scratch/adraeger/mc.root");
	if (debug && data) std::cout<<"source file: /scratch/adraeger/data.root"<<std::endl;
	if (debug && !data) std::cout<<"source file: /scratch/adraeger/mc.root"<<std::endl;


	Float_t HT =0;
	c->SetBranchAddress("HT",&HT);
	Float_t MHT =0;
	c->SetBranchAddress("MHT",&MHT);
	UShort_t NJets =0;
	c->SetBranchAddress("NJets",&NJets);
	UShort_t NVtx =0;
	c->SetBranchAddress("NVtx",&NVtx);
	Float_t MTW=0;
	c->SetBranchAddress("MTW",&MTW);
	Float_t Weight=0;
	c->SetBranchAddress("Weight",&Weight);


  	Int_t muPromtMatched =0;
	c->SetBranchAddress("muPromtMatched",&muPromtMatched);
	Int_t nElec=0;
	c->SetBranchAddress("nElec",&nElec);

	Float_t resultBBBWMTWDiLep =0;	
	c->SetBranchAddress("resultBBBWMTWDiLep",&resultBBBWMTWDiLep);
	Float_t muonBinByBinIsoWeight =0;
	c->SetBranchAddress("muonBinByBinIsoWeight",&muonBinByBinIsoWeight);	
	Float_t muonBinByBinRecoWeight =0;
	c->SetBranchAddress("muonBinByBinRecoWeight",&muonBinByBinRecoWeight);	
	Float_t muonBinByBinAccWeight =0;
	c->SetBranchAddress("muonBinByBinAccWeight",&muonBinByBinAccWeight);	
	Float_t elecBinByBinIsoWeight =0;
	c->SetBranchAddress("elecBinByBinIsoWeight",&elecBinByBinIsoWeight);	
	Float_t elecBinByBinRecoWeight =0;
	c->SetBranchAddress("elecBinByBinRecoWeight",&elecBinByBinRecoWeight);	
	Float_t elecBinByBinAccWeight =0;
	c->SetBranchAddress("elecBinByBinAccWeight",&elecBinByBinAccWeight);	


// all uncertainties

	Float_t resultBBBWMTWUp =0;
	c->SetBranchAddress("resultBBBWMTWUp",&resultBBBWMTWUp);
	Float_t resultBBBWMTWDown =0;
	c->SetBranchAddress("resultBBBWMTWDown",&resultBBBWMTWDown);

	Float_t resultBBBWMTWDiLepUp =0;
	c->SetBranchAddress("resultBBBWMTWDiLepUp",&resultBBBWMTWDiLepUp);
	Float_t resultBBBWMTWDiLepDown =0;
	c->SetBranchAddress("resultBBBWMTWDiLepDown",&resultBBBWMTWDiLepDown);


	Float_t resultWeightBinByBinAccUp =0;
	c->SetBranchAddress("resultWeightBinByBinAccUp",&resultWeightBinByBinAccUp);
	Float_t resultWeightBinByBinAccDown =0;
	c->SetBranchAddress("resultWeightBinByBinAccDown",&resultWeightBinByBinAccDown);


	Float_t resultWeightBBBDiBoUp =0;
	c->SetBranchAddress("resultWeightBBBDiBoUp",&resultWeightBBBDiBoUp);
	Float_t resultWeightBBBDiBoDown =0;
	c->SetBranchAddress("resultWeightBBBDiBoDown",&resultWeightBBBDiBoDown);


	Float_t resultWeightBBBNoCloUp =0;
	c->SetBranchAddress("resultWeightBBBNoCloUp",&resultWeightBBBNoCloUp);
	Float_t resultWeightBBBNoCloDown =0;
	c->SetBranchAddress("resultWeightBBBNoCloDown",&resultWeightBBBNoCloDown);

	Float_t muonRecoTAPUp =0;
	c->SetBranchAddress("muonRecoTAPUp",&muonRecoTAPUp);
	Float_t muonRecoTAPDown =0;
	c->SetBranchAddress("muonRecoTAPDown",&muonRecoTAPDown);

	Float_t elecIsoTAPUp =0;
	c->SetBranchAddress("elecIsoTAPUp",&elecIsoTAPUp);
	Float_t elecIsoTAPDown =0;
	c->SetBranchAddress("elecIsoTAPDown",&elecIsoTAPDown);

	Float_t muonIsoTAPUp =0;
	c->SetBranchAddress("muonIsoTAPUp",&muonIsoTAPUp);
	Float_t muonIsoTAPDown =0;
	c->SetBranchAddress("muonIsoTAPDown",&muonIsoTAPDown);

	Float_t elecRecoTAPUp =0;
	c->SetBranchAddress("elecRecoTAPUp",&elecRecoTAPUp);
	Float_t elecRecoTAPDown =0;
	c->SetBranchAddress("elecRecoTAPDown",&elecRecoTAPDown);





// tap weights


	Float_t muonTAPIsoWeightMC =0;
	c->SetBranchAddress("muonTAPIsoWeightMC",&muonTAPIsoWeightMC);	
	Float_t muonTAPIsoWeightData =0;
	c->SetBranchAddress("muonTAPIsoWeightData",&muonTAPIsoWeightData);	
	Float_t muonTAPRecoWeightMC =0;
	c->SetBranchAddress("muonTAPRecoWeightMC",&muonTAPRecoWeightMC);	
	Float_t muonTAPRecoWeightData =0;
	c->SetBranchAddress("muonTAPRecoWeightData",&muonTAPRecoWeightData);	
	Float_t elecTAPIsoWeightMC =0;
	c->SetBranchAddress("elecTAPIsoWeightMC",&elecTAPIsoWeightMC);	
	Float_t elecTAPIsoWeightData =0;
	c->SetBranchAddress("elecTAPIsoWeightData",&elecTAPIsoWeightData);	
	Float_t elecTAPRecoWeightMC =0;
	c->SetBranchAddress("elecTAPRecoWeightMC",&elecTAPRecoWeightMC);	
	Float_t elecTAPRecoWeightData =0;
	c->SetBranchAddress("elecTAPRecoWeightData",&elecTAPRecoWeightData);	



	for(int ii = 0; ii < c->GetEntries(); ++ii) 
	{
  		c->GetEntry(ii);

		// do sth with ht...
		if (HT > 500 && MHT >200 && NJets> 2.5 && MTW <100 && muPromtMatched==1 && nElec==0)
		{
			baselineWeightData+=resultBBBWMTWDiLep;
			baselineWeightDataStat+=resultBBBWMTWDiLep*resultBBBWMTWDiLep;


			baselinemuonTAPdataIsoMC+=muonTAPIsoWeightMC;
			baselinemuonTAPdataIsoData+=muonTAPIsoWeightData;
			baselinemuonTAPdataRecoMC+=muonTAPRecoWeightMC;
			baselinemuonTAPdataRecoData+=muonTAPRecoWeightData;

			baselineelecTAPdataIsoMC+=elecTAPIsoWeightMC;
			baselineelecTAPdataIsoData+=elecTAPIsoWeightData;
			baselineelecTAPdataRecoMC+=elecTAPRecoWeightMC;
			baselineelecTAPdataRecoData+=elecTAPRecoWeightData;


			baselineresultBBBWMTWDiLep+=resultBBBWMTWDiLep;

			baselineresultBBBWMTWUp+=resultBBBWMTWUp;
			baselineresultBBBWMTWDown+=resultBBBWMTWDown;

			baselineresultBBBWMTWDiLepUp+=resultBBBWMTWDiLepUp;
			baselineresultBBBWMTWDiLepDown+=resultBBBWMTWDiLepDown;

			baselineresultWeightBinByBinAccUp+=resultWeightBinByBinAccUp;
			baselineresultWeightBinByBinAccDown+=resultWeightBinByBinAccDown;

			baselineresultWeightBBBDiBoUp+=resultWeightBBBDiBoUp;
			baselineresultWeightBBBDiBoDown+=resultWeightBBBDiBoDown;

			baselineresultWeightBBBNoCloUp+=resultWeightBBBNoCloUp;
			baselineresultWeightBBBNoCloDown+=resultWeightBBBNoCloDown;


			baselinemuonRecoTAPUp+=muonRecoTAPUp;
			baselinemuonRecoTAPDown+=muonRecoTAPDown;

			baselineelecIsoTAPUp+=elecIsoTAPUp;
			baselineelecIsoTAPDown+=elecIsoTAPDown;

			baselinemuonIsoTAPUp+=muonIsoTAPUp;
			baselinemuonIsoTAPDown+=muonIsoTAPDown;

			baselineelecRecoTAPUp+=elecRecoTAPUp;
			baselineelecRecoTAPDown+=elecRecoTAPDown;




			


			baselinemuonTAPdataIsoMCStat+=muonTAPIsoWeightMC*muonTAPIsoWeightMC;
			baselinemuonTAPdataIsoDataStat+=muonTAPIsoWeightData*muonTAPIsoWeightData;
			baselinemuonTAPdataRecoMCStat+=muonTAPRecoWeightMC*muonTAPRecoWeightMC;
			baselinemuonTAPdataRecoDataStat+=muonTAPRecoWeightData*muonTAPRecoWeightData;

			baselineelecTAPdataIsoMCStat+=elecTAPIsoWeightMC*elecTAPIsoWeightMC;
			baselineelecTAPdataIsoDataStat+=elecTAPIsoWeightData*elecTAPIsoWeightData;
			baselineelecTAPdataRecoMCStat+=elecTAPRecoWeightMC*elecTAPRecoWeightMC;
			baselineelecTAPdataRecoDataStat+=elecTAPRecoWeightData*elecTAPRecoWeightData;

		}


// loop over data PrDataediction
for(int i=1;i<BINS+1;i++)
{

//cout<<"Bin["<<i<<"] Njet["<<binmap[i][0]<<","<<binmap[i][1]<<"],HT["<<binmap[i][2]<<","<<binmap[i][3]<<"],MHT["<<binmap[i][4]<<","<<binmap[i][5]<<"]"<<endl;
if (NJets<binmap[i][0]-0.5 || NJets >binmap[i][1]+0.3 || HT<binmap[i][2] || HT>binmap[i][3] || MHT <binmap[i][4] || MHT > binmap[i][5] || MTW>100 || muPromtMatched <0.5 || muPromtMatched > 1.5 || nElec > 0.5) continue;

// central PrDataedictions
ResultWeightData[i-1]+=resultBBBWMTWDiLep;
ResultWeightDataStat[i-1]+=resultBBBWMTWDiLep*resultBBBWMTWDiLep;
ResultWeightDataCS[i-1]+=Weight;
MuIsoPrData[i-1]+=muonBinByBinIsoWeight;
MuIsoPrDataStat[i-1]+=muonBinByBinIsoWeight*muonBinByBinIsoWeight;
MuRecoPrData[i-1]+=muonBinByBinRecoWeight;
MuRecoPrDataStat[i-1]+=muonBinByBinRecoWeight*muonBinByBinRecoWeight;
MuAccPrData[i-1]+=muonBinByBinAccWeight;
MuAccPrDataStat[i-1]+=muonBinByBinAccWeight*muonBinByBinAccWeight;

ElecIsoPrData[i-1]+=elecBinByBinIsoWeight;
ElecIsoPrDataStat[i-1]+=elecBinByBinIsoWeight*elecBinByBinIsoWeight;
ElecRecoPrData[i-1]+=elecBinByBinRecoWeight;
ElecRecoPrDataStat[i-1]+=elecBinByBinRecoWeight*elecBinByBinRecoWeight;
ElecAccPrData[i-1]+=elecBinByBinAccWeight;
ElecAccPrDataStat[i-1]+=elecBinByBinAccWeight*elecBinByBinAccWeight;

// uncertainties

aresultBBBWMTWDiLep[i-1]+=resultBBBWMTWDiLep;
aresultBBBWMTWUp[i-1]+=resultBBBWMTWUp;
aresultBBBWMTWDown[i-1]+=resultBBBWMTWDown;
aresultBBBWMTWDiLepUp[i-1]+=resultBBBWMTWDiLepUp;
aresultBBBWMTWDiLepDown[i-1]+=resultBBBWMTWDiLepDown;
aresultWeightBinByBinAccUp[i-1]+=resultWeightBinByBinAccUp;
aresultWeightBinByBinAccDown[i-1]+=resultWeightBinByBinAccDown;
aresultWeightBBBDiBoUp[i-1]+=resultWeightBBBDiBoUp;
aresultWeightBBBDiBoDown[i-1]+=resultWeightBBBDiBoDown;
aresultWeightBBBNoCloUp[i-1]+=resultWeightBBBNoCloUp;
aresultWeightBBBNoCloDown[i-1]+=resultWeightBBBNoCloDown;

amuonRecoTAPUp[i-1]+=muonRecoTAPUp;
amuonRecoTAPDown[i-1]+=muonRecoTAPDown;
aelecIsoTAPUp[i-1]+=elecIsoTAPUp;
aelecIsoTAPDown[i-1]+=elecIsoTAPDown;
amuonIsoTAPUp[i-1]+=muonIsoTAPUp;
amuonIsoTAPDown[i-1]+=muonIsoTAPDown;
aelecRecoTAPUp[i-1]+=elecRecoTAPUp;
aelecRecoTAPDown[i-1]+=elecRecoTAPDown;




// tag and PrDataobe PrDataedictions

muonTAPdataIsoMC[i-1]+=muonTAPIsoWeightMC;
muonTAPdataIsoData[i-1]+=muonTAPIsoWeightData;
muonTAPdataRecoMC[i-1]+=muonTAPRecoWeightMC;
muonTAPdataRecoData[i-1]+=muonTAPRecoWeightData;

elecTAPdataIsoMC[i-1]+=elecTAPIsoWeightMC;
elecTAPdataIsoData[i-1]+=elecTAPIsoWeightData;
elecTAPdataRecoMC[i-1]+=elecTAPRecoWeightMC;
elecTAPdataRecoData[i-1]+=elecTAPRecoWeightData;


muonTAPdataIsoMCStat[i-1]+=muonTAPIsoWeightMC*muonTAPIsoWeightMC;
muonTAPdataIsoDataStat[i-1]+=muonTAPIsoWeightData*muonTAPIsoWeightData;
muonTAPdataRecoMCStat[i-1]+=muonTAPRecoWeightMC*muonTAPRecoWeightMC;
muonTAPdataRecoDataStat[i-1]+=muonTAPRecoWeightData*muonTAPRecoWeightData;

elecTAPdataIsoMCStat[i-1]+=elecTAPIsoWeightMC*elecTAPIsoWeightMC;
elecTAPdataIsoDataStat[i-1]+=elecTAPIsoWeightData*elecTAPIsoWeightData;
elecTAPdataRecoMCStat[i-1]+=elecTAPRecoWeightMC*elecTAPRecoWeightMC;
elecTAPdataRecoDataStat[i-1]+=elecTAPRecoWeightData*elecTAPRecoWeightData;




}




	}

	if (debug)std::cout<<"-------------------------------------------------------------baselineWeightData"<<baselineWeightData<<std::endl;
	if (debug)
	{	
		double tempResultWeight=0;
		double tempMuonIsoWeight=0;
		double tempMuonRecoWeight=0;
		double tempMuonAccWeight=0;
		double tempElecIsoWeight=0;
		double tempElecRecoWeight=0;
		double tempElecAccWeight=0;
		for (int i=0;i<BINS;i++)
		{
			tempResultWeight+=ResultWeightData[i];
			std::cout<<"MuIsoPrData["<<i+1<<"]:"<<MuIsoPrData[i]<<std::endl;
			tempMuonIsoWeight+=MuIsoPrData[i];
			tempMuonRecoWeight+=MuRecoPrData[i];
			tempMuonAccWeight+=MuAccPrData[i];
			tempElecIsoWeight+=ElecIsoPrData[i];
			tempElecRecoWeight+=ElecRecoPrData[i];
			tempElecAccWeight+=ElecAccPrData[i];
		}
		std::cout<<"-------------------------------------------------------------tempResultWeight"<<tempResultWeight<<std::endl;
		std::cout<<"-------------------------------------------------------------tempMuonIsoWeight"<<tempMuonIsoWeight<<std::endl;
		std::cout<<"-------------------------------------------------------------tempMuonRecoWeight"<<tempMuonRecoWeight<<std::endl;
		std::cout<<"-------------------------------------------------------------tempMuonAccWeight"<<tempMuonAccWeight<<std::endl;
		std::cout<<"-------------------------------------------------------------tempElecIsoWeight"<<tempElecIsoWeight<<std::endl;
		std::cout<<"-------------------------------------------------------------tempElecRecoWeight"<<tempElecRecoWeight<<std::endl;
		std::cout<<"-------------------------------------------------------------tempElecAccWeight"<<tempElecAccWeight<<std::endl;
	}
	delete c;

}
cout<<"done"<<endl;

// mc expectation
cout<<"Loop over prediction...";
if (1)
{
	TChain* c = new TChain(exTree);
	// set here the name of the input for expectation
	c->Add("/scratch/adraeger/mc.root");



	Float_t HT =0;
	c->SetBranchAddress("HT",&HT);
	Float_t MHT =0;
	c->SetBranchAddress("MHT",&MHT);
	UShort_t NJets =0;
	c->SetBranchAddress("NJets",&NJets);
	UShort_t NVtx =0;
	c->SetBranchAddress("NVtx",&NVtx);
	Float_t Weight =0;
	c->SetBranchAddress("Weight",&Weight);


	Int_t IsExpectation=0;
	c->SetBranchAddress("IsExpectation",&IsExpectation);

	Int_t nGenMu=0;
	c->SetBranchAddress("nGenMu",&nGenMu);
	Int_t nIsoMu=0;
	c->SetBranchAddress("nIsoMu",&nIsoMu);
	Int_t nRecoMu=0;
	c->SetBranchAddress("nRecoMu",&nRecoMu);
	Int_t nAccMu=0;
	c->SetBranchAddress("nAccMu",&nAccMu);

	Int_t nGenElec=0;
	c->SetBranchAddress("nGenElec",&nGenElec);
	Int_t nIsoElec=0;
	c->SetBranchAddress("nIsoElec",&nIsoElec);
	Int_t nRecoElec=0;
	c->SetBranchAddress("nRecoElec",&nRecoElec);
	Int_t nAccElec=0;
	c->SetBranchAddress("nAccElec",&nAccElec);


	for(int ii = 0; ii < c->GetEntries(); ++ii) 
	{
  		c->GetEntry(ii);
		// do sth with ht...
		if (HT > 500 && MHT >200 && NJets> 2.5 && IsExpectation >0.4)
		{
			baselineWeightEx+=Weight;
			baselineWeightExStat+=Weight*Weight;
		}
		if (HT > 500 && MHT >200 && NJets> 2.5 && nIsoMu <-0.4)	
		{
			baselineWeightExMuIso+=Weight;
			baselineWeightExMuIsoStat+=Weight*Weight;			
		}


// loop over data PrDataediction
for(int i=1;i<BINS+1;i++)
{

//cout<<"Bin["<<i<<"] Njet["<<binmap[i][0]<<","<<binmap[i][1]<<"],HT["<<binmap[i][2]<<","<<binmap[i][3]<<"],MHT["<<binmap[i][4]<<","<<binmap[i][5]<<"]"<<endl;
if (NJets<binmap[i][0]-0.5 || NJets >binmap[i][1]+0.3 || HT<binmap[i][2] || HT>binmap[i][3] || MHT <binmap[i][4] || MHT > binmap[i][5]) continue;

// central PrDataedictions
if (IsExpectation>0.4)
{
ResultEx[i-1]+=Weight;
ResultExStat[i-1]+=Weight*Weight;
}
if(nIsoMu<-0.4)
{
MuIsoEx[i-1]+=Weight;
MuIsoExStat[i-1]+=Weight*Weight;
}
if(nRecoMu<-0.4)
{
MuRecoEx[i-1]+=Weight;
MuRecoExStat[i-1]+=Weight*Weight;
}
if(nAccMu<-0.4)
{
MuAccEx[i-1]+=Weight;
MuAccExStat[i-1]+=Weight*Weight;
}
if(nIsoElec<-0.4)
{
ElecIsoEx[i-1]+=Weight;
ElecIsoExStat[i-1]+=Weight*Weight;
}

if(nRecoElec<-0.4)
{
ElecRecoEx[i-1]+=Weight;
ElecRecoExStat[i-1]+=Weight*Weight;
}
if(nAccElec<-0.4)
{
ElecAccEx[i-1]+=Weight;
ElecAccExStat[i-1]+=Weight*Weight;
}




}



}
	delete c;

}
cout<<"done"<<endl;
// print the result tables

double lowNjetTemp=0;
if(!data)cout<<"TAP is being skipped please check bool data"<<endl;
if(data)
{

TH1F *TAPTH1MuIso = new TH1F("TAP","Comparison MuIso TAP each search bin",BINS+2,0,BINS+1);
TH1F *TAPTH1MuReco = new TH1F("TAP2","Comparison MuReco TAP each search bin",BINS+2,0,BINS+1);
TH1F *TAPTH1ElecIso = new TH1F("TAP3","Comparison ElecIso TAP each search bin",BINS+2,0,BINS+1);
TH1F *TAPTH1ElecReco = new TH1F("TAP4","Comparison ElecReco TAP each search bin",BINS+2,0,BINS+1);

TAPTH1MuIso->SetBinContent(BINS+2,baselinemuonTAPdataIsoData/baselinemuonTAPdataIsoMC);
double ratioStat=sqrt( ( 1/baselinemuonTAPdataIsoMC * sqrt(baselinemuonTAPdataIsoMCStat)  )* ( 1/baselinemuonTAPdataIsoMC * sqrt(baselinemuonTAPdataIsoMCStat)  ) +   (baselinemuonTAPdataIsoData/(baselinemuonTAPdataIsoMC*baselinemuonTAPdataIsoMC)* sqrt(baselinemuonTAPdataIsoDataStat)  )  *   ( baselinemuonTAPdataIsoData/(baselinemuonTAPdataIsoMC*baselinemuonTAPdataIsoMC)* sqrt(baselinemuonTAPdataIsoDataStat)   )    );
TAPTH1MuIso->SetBinError(BINS+2,ratioStat);
cout<<"MuIsoTAPRatioBaseline:"<<baselinemuonTAPdataIsoData/baselinemuonTAPdataIsoMC<<"+-"<<ratioStat<<endl;

TAPTH1MuReco->SetBinContent(BINS+2,baselinemuonTAPdataRecoData/baselinemuonTAPdataRecoMC);
ratioStat=sqrt( ( 1/baselinemuonTAPdataRecoMC * sqrt(baselinemuonTAPdataRecoMCStat)  )* ( 1/baselinemuonTAPdataRecoMC * sqrt(baselinemuonTAPdataRecoMCStat)  ) +   (baselinemuonTAPdataRecoData/(baselinemuonTAPdataRecoMC*baselinemuonTAPdataRecoMC)* sqrt(baselinemuonTAPdataRecoDataStat)  )  *   ( baselinemuonTAPdataRecoData/(baselinemuonTAPdataRecoMC*baselinemuonTAPdataRecoMC)* sqrt(baselinemuonTAPdataRecoDataStat)   )    );
TAPTH1MuReco->SetBinError(BINS+2,ratioStat);
cout<<"baselinemuonTAPdataRecoData"<<baselinemuonTAPdataRecoData<<endl;
cout<<"baselinemuonTAPdataRecoMC"<<baselinemuonTAPdataRecoMC<<endl;
cout<<"MuRecoTAPRatioBaseline"<<baselinemuonTAPdataRecoData/baselinemuonTAPdataRecoMC<<"+-"<<ratioStat<<endl;

TAPTH1ElecReco->SetBinContent(BINS+2,baselineelecTAPdataRecoData/baselineelecTAPdataRecoMC);
ratioStat=sqrt( ( 1/baselineelecTAPdataRecoMC * sqrt(baselineelecTAPdataRecoMCStat)  )* ( 1/baselineelecTAPdataRecoMC * sqrt(baselineelecTAPdataRecoMCStat)  ) +   (baselineelecTAPdataRecoData/(baselineelecTAPdataRecoMC*baselineelecTAPdataRecoMC)* sqrt(baselineelecTAPdataRecoDataStat)  )  *   ( baselineelecTAPdataRecoData/(baselineelecTAPdataRecoMC*baselineelecTAPdataRecoMC)* sqrt(baselineelecTAPdataRecoDataStat)   )    );
TAPTH1ElecReco->SetBinError(BINS+2,ratioStat);
cout<<"ElecIsoTAPRatioBaseline"<<baselineelecTAPdataRecoData/baselineelecTAPdataRecoMC<<"+-"<<ratioStat<<endl;

TAPTH1ElecIso->SetBinContent(BINS+2,baselineelecTAPdataIsoData/baselineelecTAPdataIsoMC);
ratioStat=sqrt( ( 1/baselineelecTAPdataIsoMC * sqrt(baselineelecTAPdataIsoMCStat)  )* ( 1/baselineelecTAPdataIsoMC * sqrt(baselineelecTAPdataIsoMCStat)  ) +   (baselineelecTAPdataIsoData/(baselineelecTAPdataIsoMC*baselineelecTAPdataIsoMC)* sqrt(baselineelecTAPdataIsoDataStat)  )  *   ( baselineelecTAPdataIsoData/(baselineelecTAPdataIsoMC*baselineelecTAPdataIsoMC)* sqrt(baselineelecTAPdataIsoDataStat)   )    );
TAPTH1ElecIso->SetBinError(BINS+2,ratioStat);
cout<<"ElecRecoTAPRatioBaseline"<<baselineelecTAPdataIsoData/baselineelecTAPdataIsoMC<<"+-"<<ratioStat<<endl;




cout<<"SEARCH BIN DATA used WEIGHTS!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl<<"-------------------------------------------------------------------------"<<endl;
for (int i=0;i<BINS;i++)
{
if(lowNjetTemp < binmap[i+1][0]-0.5)
{
cout<<"NJets["<<binmap[i+1][0]<<","<<binmap[i+1][1]<<"]"<<std::endl;
lowNjetTemp=binmap[i+1][0];
	std::cout<<"\\HT (GeV)& \\MHT (GeV)& Pred. & Stat. &  $M_{T}$ & diLep & other SM & non closure & Accept. & muIso & muId & elecIso & elecId &  Tot. Sys. \\\\"<<std::endl;
	std::cout<<"\\hline"<<std::endl;
}
// bin printing
cout<<binmap[i+1][2]<<"\\ldots "<<binmap[i+1][3]<<"& "<<binmap[i+1][4]<<" \\ldots "<<binmap[i+1][5] <<"  &";

 cout<<ResultWeightData[i];
//if()
//if(ResultWeightData[i]>0.001) 
cout<<"   &"<<sqrt(ResultWeightDataStat[i]);

cout	<<"  &$\\pm$"<<aresultBBBWMTWDiLep[i]-aresultBBBWMTWDown[i]
	<<" "

	<<"  &$\\pm$"<<aresultBBBWMTWDiLep[i]-aresultBBBWMTWDiLepDown[i]
	<<" "

	<<"  &$_{"<<aresultBBBWMTWDiLep[i]-aresultWeightBBBDiBoDown[i]
	<<"}^{+"<<aresultWeightBBBDiBoUp[i]-aresultBBBWMTWDiLep[i]
	<<"} $ "

	<<"  &$\\pm$"<<aresultBBBWMTWDiLep[i]-aresultWeightBBBNoCloDown[i]
	<<" "

	<<"  &$\\pm$"<<aresultBBBWMTWDiLep[i]-aresultWeightBinByBinAccDown[i]
	<<" "



	<<"  &$\\pm$"<<aresultBBBWMTWDiLep[i]-amuonIsoTAPDown[i]
	<<" "

	<<"   &$\\pm$"<<aresultBBBWMTWDiLep[i]-amuonRecoTAPDown[i]
	<<" "

	<<"  &$\\pm$"<<aresultBBBWMTWDiLep[i]-aelecIsoTAPDown[i]
	<<" "

	<<"  &$\\pm$"<<aresultBBBWMTWDiLep[i]-aelecRecoTAPDown[i]

	<<" "

	<<"  &$_{-"<<sqrt(//sqrt(ResultWeightDataStat[i])*sqrt(ResultWeightDataStat[i]) +
					(aresultBBBWMTWDiLep[i]-aresultBBBWMTWDown[i]) * (aresultBBBWMTWDiLep[i]-aresultBBBWMTWDown[i]) + 
					(aresultBBBWMTWDiLep[i]-aresultBBBWMTWDiLepDown[i]) * (aresultBBBWMTWDiLep[i]-aresultBBBWMTWDiLepDown[i]) + 
					(aresultBBBWMTWDiLep[i]-aresultWeightBinByBinAccDown[i]) * ( aresultBBBWMTWDiLep[i]-aresultWeightBinByBinAccDown[i]) +
					(aresultBBBWMTWDiLep[i]-amuonIsoTAPDown[i]) * (aresultBBBWMTWDiLep[i]-amuonIsoTAPDown[i]) + 
					(aresultBBBWMTWDiLep[i]-amuonRecoTAPDown[i]) * (aresultBBBWMTWDiLep[i]-amuonRecoTAPDown[i]) + 
					(aresultBBBWMTWDiLep[i]-aelecIsoTAPDown[i]) * (aresultBBBWMTWDiLep[i]-aelecIsoTAPDown[i]) + 
					(aresultBBBWMTWDiLep[i]-aelecRecoTAPDown[i]) * (aresultBBBWMTWDiLep[i]-aelecRecoTAPDown[i]) +
					(aresultBBBWMTWDiLep[i]-aresultWeightBBBDiBoDown[i]) * (aresultBBBWMTWDiLep[i]-aresultWeightBBBDiBoDown[i]) +
					(aresultBBBWMTWDiLep[i]-aresultWeightBBBNoCloDown[i]) * (aresultBBBWMTWDiLep[i]-aresultWeightBBBNoCloDown[i]) 
			)
	<<"}^{+"<<sqrt(//sqrt(ResultWeightDataStat[i])*sqrt(ResultWeightDataStat[i]) +
					(aresultBBBWMTWDiLep[i]-aresultBBBWMTWUp[i]) * (aresultBBBWMTWDiLep[i]-aresultBBBWMTWUp[i]) +
					(aresultBBBWMTWDiLep[i]-aresultBBBWMTWDiLepUp[i]) * (aresultBBBWMTWDiLep[i]-aresultBBBWMTWDiLepUp[i]) + 
					(aresultBBBWMTWDiLep[i]-aresultWeightBinByBinAccUp[i]) * ( aresultBBBWMTWDiLep[i]-aresultWeightBinByBinAccUp[i]) +
					(aresultBBBWMTWDiLep[i]-amuonIsoTAPUp[i]) * (aresultBBBWMTWDiLep[i]-amuonIsoTAPUp[i]) + 
					(aresultBBBWMTWDiLep[i]-amuonRecoTAPUp[i]) * (aresultBBBWMTWDiLep[i]-amuonRecoTAPUp[i]) + 
					(aresultBBBWMTWDiLep[i]-aelecIsoTAPUp[i]) * (aresultBBBWMTWDiLep[i]-aelecIsoTAPUp[i]) + 
					(aresultBBBWMTWDiLep[i]-aelecRecoTAPUp[i]) * (aresultBBBWMTWDiLep[i]-aelecRecoTAPUp[i]) +
					(aresultBBBWMTWDiLep[i]-aresultWeightBBBDiBoUp[i]) * (aresultBBBWMTWDiLep[i]-aresultWeightBBBDiBoUp[i]) +
					(aresultBBBWMTWDiLep[i]-aresultWeightBBBNoCloUp[i]) * (aresultBBBWMTWDiLep[i]-aresultWeightBBBNoCloUp[i]) 
			)
	<<"} $ "



	<<"  \\\\   "<<std::endl;
}

lowNjetTemp=0;


cout<<"SEARCH BIN DATA used WEIGHTS in %!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl<<"-------------------------------------------------------------------------"<<endl;
for (int i=0;i<BINS;i++)
{
if(lowNjetTemp < binmap[i+1][0]-0.5)
{
cout<<"NJets["<<binmap[i+1][0]<<","<<binmap[i+1][1]<<"]"<<std::endl;
lowNjetTemp=binmap[i+1][0];
	std::cout<<"\\HT (GeV)& \\MHT (GeV)& Pred. & Stat. &  $M_{T}$ & diLep & other SM & non closure & Accept. & muIso & muId & elecIso & elecId &  Tot. Sys. \\\\"<<std::endl;
	std::cout<<"\\hline"<<std::endl;
}
// bin printing
cout<<binmap[i+1][2]<<"\\ldots "<<binmap[i+1][3]<<"& "<<binmap[i+1][4]<<" \\ldots "<<binmap[i+1][5] <<"  &"<<ResultWeightData[i]<<"   &"<<sqrt(ResultWeightDataStat[i])/aresultBBBWMTWDiLep[i] *100
	<<"  &$\\pm$"<<(aresultBBBWMTWDiLep[i]-aresultBBBWMTWDown[i])/aresultBBBWMTWDiLep[i] *100
	<<" "

	<<"  &$\\pm$"<<(aresultBBBWMTWDiLep[i]-aresultBBBWMTWDiLepDown[i])/aresultBBBWMTWDiLep[i] *100
	<<" "

	<<"  &$_{"<<(aresultBBBWMTWDiLep[i]-aresultWeightBBBDiBoDown[i])/aresultBBBWMTWDiLep[i] *100
	<<"}^{+"<<(aresultWeightBBBDiBoUp[i]-aresultBBBWMTWDiLep[i])/aresultBBBWMTWDiLep[i] *100
	<<"} $ "

	<<"  &$\\pm$"<<(aresultBBBWMTWDiLep[i]-aresultWeightBBBNoCloDown[i])/aresultBBBWMTWDiLep[i] *100
	<<" "

	<<"  &$\\pm$"<<(aresultBBBWMTWDiLep[i]-aresultWeightBinByBinAccDown[i])/aresultBBBWMTWDiLep[i] *100
	<<" "



	<<"  &$\\pm$"<<(aresultBBBWMTWDiLep[i]-amuonIsoTAPDown[i])/aresultBBBWMTWDiLep[i] *100
	<<" "

	<<"   &$\\pm$"<<(aresultBBBWMTWDiLep[i]-amuonRecoTAPDown[i])/aresultBBBWMTWDiLep[i] *100
	<<" "

	<<"  &$\\pm$"<<(aresultBBBWMTWDiLep[i]-aelecIsoTAPDown[i])/aresultBBBWMTWDiLep[i] *100
	<<" "

	<<"  &$\\pm$"<<(aresultBBBWMTWDiLep[i]-aelecRecoTAPDown[i])/aresultBBBWMTWDiLep[i] *100

//	<<" ----"<<sqrt(
//			(aresultBBBWMTWDiLep[i]-aelecRecoTAPDown[i])/aresultBBBWMTWDiLep[i] *100 * (aresultBBBWMTWDiLep[i]-aelecRecoTAPDown[i])/aresultBBBWMTWDiLep[i] *100
//			+
//			(aresultBBBWMTWDiLep[i]-aelecIsoTAPDown[i])/aresultBBBWMTWDiLep[i] *100 * (aresultBBBWMTWDiLep[i]-aelecIsoTAPDown[i])/aresultBBBWMTWDiLep[i] *100
//			+
//			(aresultBBBWMTWDiLep[i]-amuonRecoTAPDown[i])/aresultBBBWMTWDiLep[i] *100 * (aresultBBBWMTWDiLep[i]-amuonRecoTAPDown[i])/aresultBBBWMTWDiLep[i] *100
//			+
//			(aresultBBBWMTWDiLep[i]-amuonIsoTAPDown[i])/aresultBBBWMTWDiLep[i] *100 * (aresultBBBWMTWDiLep[i]-amuonIsoTAPDown[i])/aresultBBBWMTWDiLep[i] *100
//			)

	<<"  &$_{-"<<sqrt(//sqrt(ResultWeightDataStat[i])*sqrt(ResultWeightDataStat[i]) +
					(aresultBBBWMTWDiLep[i]-aresultBBBWMTWDown[i]) * (aresultBBBWMTWDiLep[i]-aresultBBBWMTWDown[i]) + 
					(aresultBBBWMTWDiLep[i]-aresultBBBWMTWDiLepDown[i]) * (aresultBBBWMTWDiLep[i]-aresultBBBWMTWDiLepDown[i]) + 
					(aresultBBBWMTWDiLep[i]-aresultWeightBinByBinAccDown[i]) * ( aresultBBBWMTWDiLep[i]-aresultWeightBinByBinAccDown[i]) +
					(aresultBBBWMTWDiLep[i]-amuonIsoTAPDown[i]) * (aresultBBBWMTWDiLep[i]-amuonIsoTAPDown[i]) + 
					(aresultBBBWMTWDiLep[i]-amuonRecoTAPDown[i]) * (aresultBBBWMTWDiLep[i]-amuonRecoTAPDown[i]) + 
					(aresultBBBWMTWDiLep[i]-aelecIsoTAPDown[i]) * (aresultBBBWMTWDiLep[i]-aelecIsoTAPDown[i]) + 
					(aresultBBBWMTWDiLep[i]-aelecRecoTAPDown[i]) * (aresultBBBWMTWDiLep[i]-aelecRecoTAPDown[i]) +
					(aresultBBBWMTWDiLep[i]-aresultWeightBBBDiBoDown[i]) * (aresultBBBWMTWDiLep[i]-aresultWeightBBBDiBoDown[i]) +
					(aresultBBBWMTWDiLep[i]-aresultWeightBBBNoCloDown[i]) * (aresultBBBWMTWDiLep[i]-aresultWeightBBBNoCloDown[i]) 
			)/aresultBBBWMTWDiLep[i] *100
	<<"}^{+"<<sqrt(//sqrt(ResultWeightDataStat[i])*sqrt(ResultWeightDataStat[i]) +
					(aresultBBBWMTWDiLep[i]-aresultBBBWMTWUp[i]) * (aresultBBBWMTWDiLep[i]-aresultBBBWMTWUp[i]) +
					(aresultBBBWMTWDiLep[i]-aresultBBBWMTWDiLepUp[i]) * (aresultBBBWMTWDiLep[i]-aresultBBBWMTWDiLepUp[i]) + 
					(aresultBBBWMTWDiLep[i]-aresultWeightBinByBinAccUp[i]) * ( aresultBBBWMTWDiLep[i]-aresultWeightBinByBinAccUp[i]) +
					(aresultBBBWMTWDiLep[i]-amuonIsoTAPUp[i]) * (aresultBBBWMTWDiLep[i]-amuonIsoTAPUp[i]) + 
					(aresultBBBWMTWDiLep[i]-amuonRecoTAPUp[i]) * (aresultBBBWMTWDiLep[i]-amuonRecoTAPUp[i]) + 
					(aresultBBBWMTWDiLep[i]-aelecIsoTAPUp[i]) * (aresultBBBWMTWDiLep[i]-aelecIsoTAPUp[i]) + 
					(aresultBBBWMTWDiLep[i]-aelecRecoTAPUp[i]) * (aresultBBBWMTWDiLep[i]-aelecRecoTAPUp[i]) +
					(aresultBBBWMTWDiLep[i]-aresultWeightBBBDiBoUp[i]) * (aresultBBBWMTWDiLep[i]-aresultWeightBBBDiBoUp[i]) +
					(aresultBBBWMTWDiLep[i]-aresultWeightBBBNoCloUp[i]) * (aresultBBBWMTWDiLep[i]-aresultWeightBBBNoCloUp[i]) 
			)/aresultBBBWMTWDiLep[i] *100
	<<"} $ "



	<<"  \\\\   "<<std::endl;
}


lowNjetTemp=0;


cout<<endl<<endl<<endl;
cout<<"Tag and Probe!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl<<"-------------------------------------------------------------------------"<<endl;
for (int i=0;i<BINS;i++)
{
if(lowNjetTemp < binmap[i+1][0]-0.5)
{
cout<<"NJets["<<binmap[i+1][0]<<","<<binmap[i+1][1]<<"]"<<std::endl;
lowNjetTemp=binmap[i+1][0];
	std::cout<<"--HT (GeV)& --MHT (GeV)& Pred. & Stat. & T\\&P \\mu IsoMC & T\\&P \\mu IsoData & T\\&P \\mu RecoMC & T\\&P \\mu RecoData----"<<std::endl;
	std::cout<<"--hline"<<std::endl;
}
// bin printing
cout<<binmap[i+1][2]<<"--ldots "<<binmap[i+1][3]<<"& "<<binmap[i+1][4]<<" --ldots "<<binmap[i+1][5] <<"  &"<<ResultWeightData[i]<<"   &"<<sqrt(ResultWeightDataStat[i])
	<<"  &"<<aresultBBBWMTWDiLep[i]//<<"   &"<<sqrt(muonTAPdataIsoMCStat[i])
	<<"  &"<<muonTAPdataIsoData[i]//<<"   &"<<sqrt(muonTAPdataIsoDataStat[i])
	<<"  &"<<muonTAPdataRecoMC[i]//<<"   &"<<sqrt(muonTAPdataRecoMCStat[i])
	<<"  &"<<muonTAPdataRecoData[i]//<<"   &"<<sqrt(muonTAPdataRecoDataStat[i])

	<<"  &"<<elecTAPdataIsoMC[i]//<<"   &"<<sqrt(elecTAPdataIsoMCStat[i])
	<<"  &"<<elecTAPdataIsoData[i]//<<"   &"<<sqrt(elecTAPdataIsoDataStat[i])
	<<"  &"<<elecTAPdataRecoMC[i]//<<"   &"<<sqrt(elecTAPdataRecoMCStat[i])
	<<"  &"<<elecTAPdataRecoData[i]//<<"   &"<<sqrt(elecTAPdataRecoDataStat[i])

	<<"  ----   "<<std::endl;

if (muonTAPdataIsoMC[i]<0.0001) continue;
double ratio=1-muonTAPdataIsoData[i]/muonTAPdataIsoMC[i];
ratioStat=sqrt( ( 1/muonTAPdataIsoMC[i] * sqrt(muonTAPdataIsoMCStat[i])  )* ( 1/muonTAPdataIsoMC[i] * sqrt(muonTAPdataIsoMCStat[i])  ) +   (muonTAPdataIsoData[i]/(muonTAPdataIsoMC[i]*muonTAPdataIsoMC[i])* sqrt(muonTAPdataIsoDataStat[i])  )  *   ( muonTAPdataIsoData[i]/(muonTAPdataIsoMC[i]*muonTAPdataIsoMC[i])* sqrt(muonTAPdataIsoDataStat[i] )  )    );
   TAPTH1MuIso->SetBinContent(i+1,ratio);
   TAPTH1MuIso->SetBinError(i+1,ratioStat);
//cout<<"TAPTH1MuIso["<<i+1<<"]:"<<ratio<<"+-"<<ratioStat<<endl;
//cout<<"MCStat:"<<muonTAPdataIsoMCStat[i]<<", DataStat:"<<muonTAPdataIsoDataStat[i]<<endl;

ratio=1-muonTAPdataRecoData[i]/muonTAPdataRecoMC[i];
ratioStat=sqrt( ( 1/muonTAPdataRecoMC[i] * sqrt(muonTAPdataRecoMCStat[i] ) )* ( 1/muonTAPdataRecoMC[i] * sqrt(muonTAPdataRecoMCStat[i])  ) +   (muonTAPdataRecoData[i]/(muonTAPdataRecoMC[i]*muonTAPdataRecoMC[i])* sqrt(muonTAPdataRecoDataStat[i])  )  *   ( muonTAPdataRecoData[i]/(muonTAPdataRecoMC[i]* muonTAPdataRecoMC[i] )* sqrt(muonTAPdataRecoDataStat[i] )  )    );
   TAPTH1MuReco->SetBinContent(i+1,ratio);
   TAPTH1MuReco->SetBinError(i+1,ratioStat);
//cout<<"TAPTH1MuReco["<<i+1<<"]:"<<ratio<<"+-"<<ratioStat<<endl;
//cout<<"MCStat:"<<muonTAPdataRecoMCStat[i]<<", DataStat:"<<muonTAPdataRecoDataStat[i]<<endl;

ratio=1-elecTAPdataIsoData[i]/elecTAPdataIsoMC[i];
ratioStat=sqrt( ( 1/elecTAPdataIsoMC[i] * sqrt(elecTAPdataIsoMCStat[i])  )* ( 1/elecTAPdataIsoMC[i] * sqrt(elecTAPdataIsoMCStat[i])  ) +   (elecTAPdataIsoData[i]/(elecTAPdataIsoMC[i]*elecTAPdataIsoMC[i])* sqrt(elecTAPdataIsoDataStat[i])  )  *   ( elecTAPdataIsoData[i]/(elecTAPdataIsoMC[i]*elecTAPdataIsoMC[i])* sqrt(elecTAPdataIsoDataStat[i] )  )    );
   TAPTH1ElecIso->SetBinContent(i+1,ratio);
   TAPTH1ElecIso->SetBinError(i+1,ratioStat);
//cout<<"TAPTH1ElecIso["<<i+1<<"]:"<<ratio<<"+-"<<ratioStat<<endl;
//cout<<"MCStat:"<<elecTAPdataIsoMCStat[i]<<", DataStat:"<<elecTAPdataIsoDataStat[i]<<endl;

ratio=1-elecTAPdataRecoData[i]/elecTAPdataRecoMC[i];
ratioStat=sqrt( ( 1/elecTAPdataRecoMC[i] * sqrt(elecTAPdataRecoMCStat[i])  )* ( 1/elecTAPdataRecoMC[i] * sqrt(elecTAPdataRecoMCStat[i] ) ) +   (elecTAPdataRecoData[i]/(elecTAPdataRecoMC[i]*elecTAPdataRecoMC[i])* sqrt(elecTAPdataRecoDataStat[i])  )  *   ( elecTAPdataRecoData[i]/(elecTAPdataRecoMC[i]*elecTAPdataRecoMC[i])* sqrt(elecTAPdataRecoDataStat[i] )  )    );
   TAPTH1ElecReco->SetBinContent(i+1,ratio);
   TAPTH1ElecReco->SetBinError(i+1,ratioStat);
//cout<<"TAPTH1ElecReco["<<i+1<<"]:"<<ratio<<"+-"<<ratioStat<<endl;
//cout<<"MCStat:"<<elecTAPdataRecoMCStat[i]<<", DataStat:"<<elecTAPdataRecoDataStat[i]<<endl;




}

lowNjetTemp=0;
}


cout<<"Closure baseline, search bins!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!--------------!!!!!!!!1!!!!!!"<<endl<<"-------------------------------------------------------------------------"<<endl;
for (int i=0;i<BINS;i++)
{

if(lowNjetTemp < binmap[i+1][0]-0.5)
{
cout<<setprecision(0);
if (lowNjetTemp==0)
{
	std::cout<<"\\HT (GeV)& \\MHT (GeV)& prediction & expectation & ratio  \\\\"<<std::endl;
	std::cout<<"\\hline"<<std::endl;
}
if(lowNjetTemp>0) cout<<"\\hline"<<endl;
cout<<"NJets["<<binmap[i+1][0]<<","<<binmap[i+1][1]<<"] \\\\"<<std::endl;
cout<<"\\hline"<<endl;
lowNjetTemp=binmap[i+1][0];
}


double totalPrediction=(ElecIsoPrData[i]+ElecRecoPrData[i]+ElecAccPrData[i] + MuIsoPrData[i]+MuRecoPrData[i]+MuAccPrData[i])*scale;
double totalPredictionStat=sqrt(ElecIsoPrDataStat[i]+ElecRecoPrDataStat[i]+ElecAccPrDataStat[i] + MuIsoPrDataStat[i]+MuRecoPrDataStat[i]+MuAccPrDataStat[i])*scale;

double totalExpectation=(ElecIsoEx[i]+ElecRecoEx[i]+ElecAccEx[i]+ MuIsoEx[i]+MuRecoEx[i]+MuAccEx[i])*scale;
double totalExpectationStat=sqrt(ElecIsoExStat[i]+ElecRecoExStat[i]+ElecAccExStat[i]+MuIsoExStat[i]+MuRecoExStat[i]+MuAccExStat[i])*scale;

double ratio=totalPrediction/totalExpectation;
double ratioStat=sqrt( ( 1/totalExpectation * totalPredictionStat  )* ( 1/totalExpectation * totalPredictionStat  ) +   (totalPrediction/(totalExpectation*totalExpectation)* totalExpectationStat  )  *   ( totalPrediction/(totalExpectation*totalExpectation)* totalExpectationStat   )    );



// bin printing
cout<<setprecision(0);
cout<<binmap[i+1][2]<<"\\ldots "<<binmap[i+1][3]<<"& "<<binmap[i+1][4]<<" \\ldots "<<binmap[i+1][5] 
cout<<setprecision(2);
cout	<<"  &"<<totalPrediction<<"$\\pm$ "<<totalPredictionStat
	<<"  &"<<totalExpectation<<"$\\pm$"<<totalExpectationStat
	<<"  &"<<ratio<<"$\\pm$ "<<ratioStat

	<<" \\\\ "<<std::endl;
}


lowNjetTemp=0;




cout<<"Closure seperately mu iso reco acc!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl<<"-------------------------------------------------------------------------"<<endl;
for (int i=0;i<BINS;i++)
{

if(lowNjetTemp < binmap[i+1][0]-0.5)
{
cout<<setprecision(0);
if (lowNjetTemp==0)
{
	std::cout<<"\\HT (GeV)& \\MHT (GeV)& IsoPr & IsoEx & RecoPr & RecoEx & AccPr & AccEx & tot $\\mu$ pr & tot $\\mu$ ex  \\\\"<<std::endl;
	std::cout<<"\\hline"<<std::endl;
}
if(lowNjetTemp>0) cout<<"\\hline"<<endl;
cout<<"NJets["<<binmap[i+1][0]<<","<<binmap[i+1][1]<<"] \\\\"<<std::endl;
cout<<"\\hline"<<endl;
lowNjetTemp=binmap[i+1][0];
}
// bin printing
cout<<setprecision(0);
cout<<binmap[i+1][2]<<"\\ldots "<<binmap[i+1][3]<<"& "<<binmap[i+1][4]<<" \\ldots "<<binmap[i+1][5] 
cout<<setprecision(2);
cout	<<"  &"<<MuIsoPrData[i]*scale<<"$\\pm$ "<<sqrt(MuIsoPrDataStat[i])*scale
	<<"  &"<<MuIsoEx[i]*scale<<"$\\pm$"<<sqrt(MuIsoExStat[i])*scale
	<<"  &"<<MuRecoPrData[i]*scale<<"$\\pm$ "<<sqrt(MuRecoPrDataStat[i])*scale
	<<"  &"<<MuRecoEx[i]*scale<<"$\\pm$"<<sqrt(MuRecoExStat[i])*scale
	<<"  &"<<MuAccPrData[i]*scale<<"$\\pm$ "<<sqrt(MuAccPrDataStat[i])*scale
	<<"  &"<<MuAccEx[i]*scale<<"$\\pm$"<<sqrt(MuAccExStat[i])*scale

	<<"  &"<<MuIsoPrData[i]*scale+MuRecoPrData[i]*scale+MuAccPrData[i]*scale<<"$\\pm$ "<<sqrt(MuIsoPrDataStat[i]+MuRecoPrDataStat[i]+MuAccPrDataStat[i])*scale
	<<"  &"<<MuIsoEx[i]*scale+MuRecoEx[i]*scale+MuAccEx[i]*scale<<"$\\pm$ "<<sqrt(MuIsoExStat[i]+MuRecoExStat[i]+MuAccExStat[i])*scale

	<<" \\\\ "<<std::endl;
}


lowNjetTemp=0;


cout<<"Closure seperately Elec iso reco acc!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl<<"-------------------------------------------------------------------------"<<endl;
for (int i=0;i<BINS;i++)
{

if(lowNjetTemp < binmap[i+1][0]-0.5)
{
cout<<setprecision(0);
if (lowNjetTemp==0)
{
	std::cout<<"\\HT (GeV)& \\MHT (GeV)& IsoPr & IsoEx & RecoPr & RecoEx & AccPr & AccEx & tot elec pr & tot elec ex  \\\\"<<std::endl;
	std::cout<<"\\hline"<<std::endl;
}
if(lowNjetTemp>0) cout<<"\\hline"<<endl;
cout<<"NJets["<<binmap[i+1][0]<<","<<binmap[i+1][1]<<"] \\\\"<<std::endl;
cout<<"\\hline"<<endl;
lowNjetTemp=binmap[i+1][0];
}
// bin printing
cout<<setprecision(0);
cout<<binmap[i+1][2]<<"\\ldots "<<binmap[i+1][3]<<"& "<<binmap[i+1][4]<<" \\ldots "<<binmap[i+1][5] 
cout<<setprecision(2);
cout	<<"  &"<<ElecIsoPrData[i]*scale<<"$\\pm$ "<<sqrt(ElecIsoPrDataStat[i])*scale
	<<"  &"<<ElecIsoEx[i]*scale<<"$\\pm$"<<sqrt(ElecIsoExStat[i])*scale
	<<"  &"<<ElecRecoPrData[i]*scale<<"$\\pm$ "<<sqrt(ElecRecoPrDataStat[i])*scale
	<<"  &"<<ElecRecoEx[i]*scale<<"$\\pm$"<<sqrt(ElecRecoExStat[i])*scale
	<<"  &"<<ElecAccPrData[i]*scale<<"$\\pm$ "<<sqrt(ElecAccPrDataStat[i])*scale
	<<"  &"<<ElecAccEx[i]*scale<<"$\\pm$"<<sqrt(ElecAccExStat[i])*scale

	<<"  &"<<ElecIsoPrData[i]*scale+ElecRecoPrData[i]*scale+ElecAccPrData[i]*scale<<"$\\pm$ "<<sqrt(ElecIsoPrDataStat[i]+ElecRecoPrDataStat[i]+ElecAccPrDataStat[i])*scale
	<<"  &"<<ElecIsoEx[i]*scale+ElecRecoEx[i]*scale+ElecAccEx[i]*scale<<"$\\pm$ "<<sqrt(ElecIsoExStat[i]+ElecRecoExStat[i]+ElecAccExStat[i])*scale

	<<" \\\\ "<<std::endl;
}




// plots for non closure each search region


TH1F *ClosureTH1 = new TH1F("Closure","CMS Simulation, 8 TeV, Closure all search bins",BINS+2,0,BINS+1);

TH1F *ClosureTH1LowNJet = new TH1F("Closure","CMS Simulation, 8 TeV, Closure all search bins",17,1,17);
TH1F *ClosureTH1MediumNJet = new TH1F("Closure","CMS Simulation, 8 TeV, Closure all search bins",14,1,14);
TH1F *ClosureTH1HighNJet = new TH1F("Closure","CMS Simulation, 8 TeV, Closure all search bins",5,1,5);


TH1F *Closure1 = new TH1F("LowNjet","Closure for 2 < NJet < 6", 200, 0, 2);
TH1F *Closure2 = new TH1F("LowNjet","Closure for 5 < NJet < 8", 200, 0, 2);
TH1F *Closure3 = new TH1F("LowNjet","Closure for 7 < NJet ", 200, 0, 2);

ClosureTH1->SetBinContent(BINS+2,baselineWeightData/baselineWeightEx);
ratioStat=sqrt( ( 1/baselineWeightEx * baselineWeightDataStat  )* ( 1/baselineWeightEx * baselineWeightDataStat  ) +   (baselineWeightData/(baselineWeightEx*baselineWeightEx)* baselineWeightExStat  )  *   ( baselineWeightData/(baselineWeightEx*baselineWeightEx)* baselineWeightExStat   )    );
cout<<"baselineClosureRatio="<<baselineWeightEx/baselineWeightData<<"+-"<<ratioStat<<endl;
ClosureTH1->SetBinError(BINS+2,ratioStat);


int countter1=1;
int countter2=1;
for (int i=0;i<BINS;i++)
{
double totalPrediction=(ElecIsoPrData[i]+ElecRecoPrData[i]+ElecAccPrData[i] + MuIsoPrData[i]+MuRecoPrData[i]+MuAccPrData[i])*scale;
//totalPrediction=ResultWeightData[i];
double totalPredictionStat=sqrt(ElecIsoPrDataStat[i]+ElecRecoPrDataStat[i]+ElecAccPrDataStat[i] + MuIsoPrDataStat[i]+MuRecoPrDataStat[i]+MuAccPrDataStat[i])*scale;

double totalExpectation=(ElecIsoEx[i]+ElecRecoEx[i]+ElecAccEx[i]+ MuIsoEx[i]+MuRecoEx[i]+MuAccEx[i])*scale;
double totalExpectationStat=sqrt(ElecIsoExStat[i]+ElecRecoExStat[i]+ElecAccExStat[i]+MuIsoExStat[i]+MuRecoExStat[i]+MuAccExStat[i])*scale;

double ratio=totalPrediction/totalExpectation;
double ratioStat=sqrt( ( 1/totalExpectation * totalPredictionStat  )* ( 1/totalExpectation * totalPredictionStat  ) +   (totalPrediction/(totalExpectation*totalExpectation)* totalExpectationStat  )  *   ( totalPrediction/(totalExpectation*totalExpectation)* totalExpectationStat   )    );
//cout<<"ratio"<<ratio<<"+-"<<ratioStat<<endl;
   ClosureTH1->SetBinContent(i+1,ratio);
   ClosureTH1->SetBinError(i+1,ratioStat);

if (-.05<i && i < 17 )
{
	Closure1->Fill(ratio);
	ClosureTH1LowNJet->SetBinContent(i+1,ratio);
	ClosureTH1LowNJet->SetBinError(i+1,ratioStat);

}
if ( 16 < i && i < 31 )
{
	Closure2->Fill(ratio);
	ClosureTH1MediumNJet->SetBinContent(i-16,ratio);
	ClosureTH1MediumNJet->SetBinError(i-16,ratioStat);
countter1++;
}

if ( 30 < i )
{
	Closure3->Fill(ratio);
	ClosureTH1HighNJet->SetBinContent(i-30,ratio);
	ClosureTH1HighNJet->SetBinError(i-30,ratioStat);
countter2++;
}

}


// non closure plots for each contribution


TH1F *ClosureTH1MuIso = new TH1F("MuonIsoClosure","Closure not isolated #mu",BINS+2,0,BINS+1);
double totalisomuex=0;
double totalisomuexerror=0;
double totalisomupr=0;
double totalisomuprerror=0;
for (int i=0;i<BINS;i++)
{
double totalPrediction=(MuIsoPrData[i])*scale;
double totalPredictionStat=sqrt(MuIsoPrDataStat[i])*scale;

double totalExpectation=(MuIsoEx[i])*scale;
double totalExpectationStat=sqrt(MuIsoExStat[i])*scale;

double ratio=totalPrediction/totalExpectation;
double ratioStat=sqrt( ( 1/totalExpectation * totalPredictionStat  )* ( 1/totalExpectation * totalPredictionStat  ) +   (totalPrediction/(totalExpectation*totalExpectation)* totalExpectationStat  )  *   ( totalPrediction/(totalExpectation*totalExpectation)* totalExpectationStat   )    );
if (totalPrediction >0.01 && totalExpectation > 0.01)
{
   ClosureTH1MuIso->SetBinContent(i+1,ratio);
   ClosureTH1MuIso->SetBinError(i+1,ratioStat);

totalisomupr+=totalPrediction;
totalisomuprerror+=MuIsoPrDataStat[i] * scale * scale;

totalisomuex+=totalExpectation;
totalisomuexerror+=MuIsoExStat[i] * scale * scale;

}
cout<<"I="<<i<<endl;
}

ClosureTH1MuIso->SetBinContent(BINS+2,totalisomupr/totalisomuex);
//cout<<"TotalIsoMuEx="<<totalisomuex<<", totalisomupr"<<totalisomupr<<endl;
double ratioStat=sqrt( ( 1/totalisomuex * totalisomuprerror  )* ( 1/totalisomuex * totalisomuprerror  ) +   (totalisomupr/(totalisomuex*totalisomuex)* totalisomuexerror  )  *   ( totalisomupr/(totalisomuex*totalisomuex)* totalisomuexerror   )    );
//cout<<"TotalMuIsoClosure="<<totalisomuex/totalisomupr<<"+-"<<ratioStat<<endl;
ClosureTH1MuIso->SetBinError(BINS+2,ratioStat);


// muon reco


TH1F *ClosureTH1MuReco = new TH1F("MuonRecoClosure","Closure not reco #mu",BINS+2,0,BINS+1);
double totalrecomuex=0;
double totalrecomuexerror=0;
double totalrecomupr=0;
double totalrecomuprerror=0;
for (int i=0;i<BINS;i++)
{
double totalPrediction=(MuRecoPrData[i])*scale;
double totalPredictionStat=sqrt(MuRecoPrDataStat[i])*scale;

double totalExpectation=(MuRecoEx[i])*scale;
double totalExpectationStat=sqrt(MuRecoExStat[i])*scale;
//cout<<"MuReco::totalPrediction"<<totalPrediction<<"+-"<<totalPredictionStat<<endl;
//cout<<"MuReco::totalExpectation"<<totalExpectation<<"+-"<<totalExpectationStat<<endl;
double ratio=totalPrediction/totalExpectation;
double ratioStat=sqrt( ( 1/totalExpectation * totalPredictionStat  )* ( 1/totalExpectation * totalPredictionStat  ) +   (totalPrediction/(totalExpectation*totalExpectation)* totalExpectationStat  )  *   ( totalPrediction/(totalExpectation*totalExpectation)* totalExpectationStat   )    );
if (totalPrediction >0.01 && totalExpectation > 0.01)
{
//	cout<<"!"<<endl;
   ClosureTH1MuReco->SetBinContent(i+1,ratio);
   ClosureTH1MuReco->SetBinError(i+1,ratioStat);

totalrecomupr+=totalPrediction;
totalrecomuprerror+=MuRecoPrDataStat[i] * scale * scale;

totalrecomuex+=totalExpectation;
totalrecomuexerror+=MuRecoExStat[i] * scale * scale;

}

}

ClosureTH1MuReco->SetBinContent(BINS+2,totalrecomupr/totalrecomuex);
double ratioStat=sqrt( ( 1/totalrecomupr * totalrecomuexerror  )* ( 1/totalrecomupr * totalrecomuexerror  ) +   (totalrecomuex/(totalrecomupr*totalrecomupr)* totalrecomuprerror  )  *   ( totalrecomuex/(totalrecomupr*totalrecomupr)* totalrecomuprerror   )    );
//cout<<"TotalMuRecoClosure="<<totalrecomuex/totalrecomupr<<"+-"<<ratioStat<<endl;
ClosureTH1MuReco->SetBinError(BINS+2,ratioStat);




// muon acceptance


TH1F *ClosureTH1MuAcc = new TH1F("MuonAccClosure","Closure not acc #mu",BINS+2,0,BINS+1);
double totalaccmuex=0;
double totalaccmuexerror=0;
double totalaccmupr=0;
double totalaccmuprerror=0;
for (int i=0;i<BINS;i++)
{
double totalPrediction=(MuAccPrData[i])*scale;
double totalPredictionStat=sqrt(MuAccPrDataStat[i])*scale;

double totalExpectation=(MuAccEx[i])*scale;
double totalExpectationStat=sqrt(MuAccExStat[i])*scale;
//cout<<"MuAcc::totalPrediction"<<totalPrediction<<"+-"<<totalPredictionStat<<endl;
//cout<<"MuAcc::totalExpectation"<<totalExpectation<<"+-"<<totalExpectationStat<<endl;
double ratio=totalPrediction/totalExpectation;
double ratioStat=sqrt( ( 1/totalExpectation * totalPredictionStat  )* ( 1/totalExpectation * totalPredictionStat  ) +   (totalPrediction/(totalExpectation*totalExpectation)* totalExpectationStat  )  *   ( totalPrediction/(totalExpectation*totalExpectation)* totalExpectationStat   )    );
if (totalPrediction >0.01 && totalExpectation > 0.01)
{
 // cout<<"!"<<endl;
   ClosureTH1MuAcc->SetBinContent(i+1,ratio);
   ClosureTH1MuAcc->SetBinError(i+1,ratioStat);

totalaccmupr+=totalPrediction;
totalaccmuprerror+=MuAccPrDataStat[i] * scale * scale;

totalaccmuex+=totalExpectation;
totalaccmuexerror+=MuAccExStat[i] * scale * scale;

}

}

ClosureTH1MuAcc->SetBinContent(BINS+2,totalaccmupr/totalaccmuex);
double ratioStat=sqrt( ( 1/totalaccmupr * totalaccmuexerror  )* ( 1/totalaccmupr * totalaccmuexerror  ) +   (totalaccmuex/(totalaccmupr*totalaccmupr)* totalaccmuprerror  )  *   ( totalaccmuex/(totalaccmupr*totalaccmupr)* totalaccmuprerror   )    );
cout<<"TotalMuAccClosure="<<totalaccmuex/totalaccmupr<<"+-"<<ratioStat<<endl;
ClosureTH1MuAcc->SetBinError(BINS+2,ratioStat);




// electron

TH1F *ClosureTH1ElecIso = new TH1F("EleconIsoClosure","Closure not isolated elec",BINS+2,0,BINS+1);
double totalisoelecex=0;
double totalisoelecexerror=0;
double totalisoelecpr=0;
double totalisoelecprerror=0;
for (int i=0;i<BINS;i++)
{
double totalPrediction=(ElecIsoPrData[i])*scale;
double totalPredictionStat=sqrt(ElecIsoPrDataStat[i])*scale;

double totalExpectation=(ElecIsoEx[i])*scale;
double totalExpectationStat=sqrt(ElecIsoExStat[i])*scale;
//cout<<"ElecIso::totalPrediction"<<totalPrediction<<"+-"<<totalPredictionStat<<endl;
//cout<<"ElecIso::totalExpectation"<<totalExpectation<<"+-"<<totalExpectationStat<<endl;
double ratio=totalPrediction/totalExpectation;
double ratioStat=sqrt( ( 1/totalExpectation * totalPredictionStat  )* ( 1/totalExpectation * totalPredictionStat  ) +   (totalPrediction/(totalExpectation*totalExpectation)* totalExpectationStat  )  *   ( totalPrediction/(totalExpectation*totalExpectation)* totalExpectationStat   )    );
if (totalPrediction >0.01 && totalExpectation > 0.01)
{
 // cout<<"!"<<endl;
   ClosureTH1ElecIso->SetBinContent(i+1,ratio);
   ClosureTH1ElecIso->SetBinError(i+1,ratioStat);

totalisoelecpr+=totalPrediction;
totalisoelecprerror+=ElecIsoPrDataStat[i] * scale * scale;

totalisoelecex+=totalExpectation;
totalisoelecexerror+=ElecIsoExStat[i] * scale * scale;

}

}

ClosureTH1ElecIso->SetBinContent(BINS+2,totalisoelecpr/totalisoelecex);
double ratioStat=sqrt( ( 1/totalisoelecpr * totalisoelecexerror  )* ( 1/totalisoelecpr * totalisoelecexerror  ) +   (totalisoelecex/(totalisoelecpr*totalisoelecpr)* totalisoelecprerror  )  *   ( totalisoelecex/(totalisoelecpr*totalisoelecpr)* totalisoelecprerror   )    );
//cout<<"TotalElecIsoClosure="<<totalisoelecex/totalisoelecpr<<"+-"<<ratioStat<<endl;
ClosureTH1ElecIso->SetBinError(BINS+2,ratioStat);


// elecon reco


TH1F *ClosureTH1ElecReco = new TH1F("EleconRecoClosure","Closure not reco elec",BINS+2,0,BINS+1);
double totalrecoelecex=0;
double totalrecoelecexerror=0;
double totalrecoelecpr=0;
double totalrecoelecprerror=0;
for (int i=0;i<BINS;i++)
{
double totalPrediction=(ElecRecoPrData[i])*scale;
double totalPredictionStat=sqrt(ElecRecoPrDataStat[i])*scale;

double totalExpectation=(ElecRecoEx[i])*scale;
double totalExpectationStat=sqrt(ElecRecoExStat[i])*scale;
//cout<<"ElecReco::totalPrediction"<<totalPrediction<<"+-"<<totalPredictionStat<<endl;
//cout<<"ElecReco::totalExpectation"<<totalExpectation<<"+-"<<totalExpectationStat<<endl;
double ratio=totalPrediction/totalExpectation;
double ratioStat=sqrt( ( 1/totalExpectation * totalPredictionStat  )* ( 1/totalExpectation * totalPredictionStat  ) +   (totalPrediction/(totalExpectation*totalExpectation)* totalExpectationStat  )  *   ( totalPrediction/(totalExpectation*totalExpectation)* totalExpectationStat   )    );
if (totalPrediction >0.01 && totalExpectation > 0.01)
{
 // cout<<"!"<<endl;
   ClosureTH1ElecReco->SetBinContent(i+1,ratio);
   ClosureTH1ElecReco->SetBinError(i+1,ratioStat);

totalrecoelecpr+=totalPrediction;
totalrecoelecprerror+=ElecRecoPrDataStat[i] * scale * scale;

totalrecoelecex+=totalExpectation;
totalrecoelecexerror+=ElecRecoExStat[i] * scale * scale;

}

}

ClosureTH1ElecReco->SetBinContent(BINS+2,totalrecoelecpr/totalrecoelecex);
double ratioStat=sqrt( ( 1/totalrecoelecpr * totalrecoelecexerror  )* ( 1/totalrecoelecpr * totalrecoelecexerror  ) +   (totalrecoelecex/(totalrecoelecpr*totalrecoelecpr)* totalrecoelecprerror  )  *   ( totalrecoelecex/(totalrecoelecpr*totalrecoelecpr)* totalrecoelecprerror   )    );
//cout<<"TotalElecRecoClosure="<<totalrecoelecex/totalrecoelecpr<<"+-"<<ratioStat<<endl;
ClosureTH1ElecReco->SetBinError(BINS+2,ratioStat);




// elecon acceptance


TH1F *ClosureTH1ElecAcc = new TH1F("EleconAccClosure","Closure not acc elec",BINS+2,0,BINS+1);
double totalaccelecex=0;
double totalaccelecexerror=0;
double totalaccelecpr=0;
double totalaccelecprerror=0;
for (int i=0;i<BINS;i++)
{
double totalPrediction=(ElecAccPrData[i])*scale;
double totalPredictionStat=sqrt(ElecAccPrDataStat[i])*scale;

double totalExpectation=(ElecAccEx[i])*scale;
double totalExpectationStat=sqrt(ElecAccExStat[i])*scale;
//cout<<"ElecAcc::totalPrediction"<<totalPrediction<<"+-"<<totalPredictionStat<<endl;
//cout<<"ElecAcc::totalExpectation"<<totalExpectation<<"+-"<<totalExpectationStat<<endl;
double ratio=totalPrediction/totalExpectation;
double ratioStat=sqrt( ( 1/totalExpectation * totalPredictionStat  )* ( 1/totalExpectation * totalPredictionStat  ) +   (totalPrediction/(totalExpectation*totalExpectation)* totalExpectationStat  )  *   ( totalPrediction/(totalExpectation*totalExpectation)* totalExpectationStat   )    );
if (totalPrediction >0.01 && totalExpectation > 0.01)
{
//  cout<<"!"<<endl;
   ClosureTH1ElecAcc->SetBinContent(i+1,ratio);
   ClosureTH1ElecAcc->SetBinError(i+1,ratioStat);

totalaccelecpr+=totalPrediction;
totalaccelecprerror+=ElecAccPrDataStat[i] * scale * scale;

totalaccelecex+=totalExpectation;
totalaccelecexerror+=ElecAccExStat[i] * scale * scale;

}

}

ClosureTH1ElecAcc->SetBinContent(BINS+2,totalaccelecpr/totalaccelecex);
double ratioStat=sqrt( ( 1/totalaccelecpr * totalaccelecexerror  )* ( 1/totalaccelecpr * totalaccelecexerror  ) +   (totalaccelecex/(totalaccelecpr*totalaccelecpr)* totalaccelecprerror  )  *   ( totalaccelecex/(totalaccelecpr*totalaccelecpr)* totalaccelecprerror   )    );
cout<<"TotalElecAccClosure="<<totalaccelecex/totalaccelecpr<<"+-"<<ratioStat<<endl;
ClosureTH1ElecAcc->SetBinError(BINS+2,ratioStat);












// plot all the distirubitons need to be saved manually

if (!data)
{
TCanvas *c1= new TCanvas("c1","");
c1->cd();
ClosureTH1->SetTitle("CMS Simulation, 8 TeV, Closure all search bins;Bins;Pre/Exp");
ClosureTH1->Draw();
//c1->SaveAs("ClosureRatio"+".pdf");

TCanvas *muiso= new TCanvas("muiso","");
muiso->cd();
ClosureTH1MuIso->SetTitle("Closure for muon iso (last bin inclusive);Bins;MuIso pre/Exp");
ClosureTH1MuIso->Draw();

TCanvas *mureco= new TCanvas("mureco","");
mureco->cd();
ClosureTH1MuReco->SetTitle("Closure for muon reco (last bin inclusive);Bins;MuReco pre/Exp");
ClosureTH1MuReco->Draw();

TCanvas *muacc= new TCanvas("muacc","");
muacc->cd();
ClosureTH1MuAcc->SetTitle("Closure for muon acc (last bin inclusive);Bins;MuAcc pre/Exp");
ClosureTH1MuAcc->Draw();

// elec
TCanvas *eleciso= new TCanvas("eleciso","");
eleciso->cd();
ClosureTH1ElecIso->SetTitle("Closure for elec iso (last bin inclusive);Bins;ElecIso pre/Exp");
ClosureTH1ElecIso->Draw();

TCanvas *elecreco= new TCanvas("elecreco","");
elecreco->cd();
ClosureTH1ElecReco->SetTitle("Closure for elec reco (last bin inclusive);Bins;ElecReco pre/Exp");
ClosureTH1ElecReco->Draw();

TCanvas *elecacc= new TCanvas("elecacc","");
elecacc->cd();
ClosureTH1ElecAcc->SetTitle("Closure for elec acc (last bin inclusive);Bins;ElecAcc pre/Exp");
ClosureTH1ElecAcc->Draw();

// seperate closure each njet selection nused for RMS calculation
/*TCanvas *closure1= new TCanvas("closure1","");
closure1->cd();
Closure1->SetTitle("Closure for 2<NJet<6;Bins;Tot pre/Exp");
Closure1->Draw();

TCanvas *closure2= new TCanvas("closure2","");
closure2->cd();
Closure2->SetTitle("Closure for 5<NJet<8;Bins;Tot pre/Exp");
Closure2->Draw();

TCanvas *closure3= new TCanvas("closure3","");
closure3->cd();
Closure3->SetTitle("Closure for 7<NJet;Bins;Tot pre/Exp");
Closure3->Draw();
*/
TCanvas *closure1b= new TCanvas("closure1b","");
closure1b->cd();
ClosureTH1LowNJet->SetTitle("CMS Simulation, 8 TeV, Closure for 2<NJet<6;Bins;pre/Exp");
ClosureTH1LowNJet->Draw();

TCanvas *closure2b= new TCanvas("closure2b","");
closure2b->cd();
ClosureTH1MediumNJet->SetTitle("CMS Simulation, 8 TeV, Closure for 5<NJet<8;Bins;pre/Exp");
ClosureTH1MediumNJet->Draw();

TCanvas *closure3b= new TCanvas("closure3b","");
closure3b->cd();
ClosureTH1HighNJet->SetTitle("CMS Simulation, 8 TeV, Closure for 7<NJet;Bins;pre/Exp");
ClosureTH1HighNJet->Draw();

cout<<"check"<<std::endl;

}




if (data)
{
TCanvas *c2= new TCanvas("c2","");
c2->cd();
TAPTH1MuIso->SetTitle("Comparison MuIso TAP for each search bin (last bin inclusive);Bins;Ratio");
TAPTH1MuIso->Draw();

TCanvas *c3= new TCanvas("c3","");
c3->cd();
TAPTH1MuReco->SetTitle("Comparison MuReco TAP for each search bin (last bin inclusive);Bins;Ratio");
TAPTH1MuReco->Draw();

TCanvas *c4= new TCanvas("c4","");
c4->cd();
TAPTH1ElecIso->SetTitle("Comparison ElecIso TAP for each search bin (last bin inclusive);Bins;Ratio");
TAPTH1ElecIso->Draw();

TCanvas *c5= new TCanvas("c5","");
c5->cd();
TAPTH1ElecReco->SetTitle("Comparison ElecReco TAP for each search bin (last bin inclusive);Bins;Ratio");
TAPTH1ElecReco->Draw();



}





double MuIsoExTemp=0;
double MuIsoExTempStat =0;

for (int i=0; i<MuIsoEx.size();i++)
{
MuIsoExTemp+=MuIsoEx[i];
MuIsoExTempStat+=MuIsoExStat[i];
}

cout<<"BaselinePrData:"<<baselineWeightData<<"+-"<<sqrt(baselineWeightDataStat)<<endl;
cout<<"BaselinExMC:"<<baselineWeightEx*scale<<"+-"<<sqrt(baselineWeightExStat)*scale<<endl;
cout<<"MuIsoExBaseline:"<<baselineWeightExMuIso*scale<<"+-"<<sqrt(baselineWeightExMuIsoStat)*scale<<endl;
cout<<"MuIsoExBaselinerecomputed:"<<MuIsoExTemp*scale<<"+-"<<sqrt(MuIsoExTempStat)*scale<<endl;


cout<<"DataCard"<<endl; 


   std::cout<<std::endl<<"# Predicted events"<<std::endl;

   std::cout<<"ll_events = ";

   for (int i=0;i<BINS;i++)
	{
	std::cout<<ResultWeightData[i]<<"  ";
	}




   std::cout<<std::endl<<std::endl<<"# Uncertainties --> stat. and syst."<<std::endl;
   std::cout<<"# uncertainties:: 1:stat, 2:allCombined"<<std::endl;
   std::cout<<std::endl<<std::endl<<"ll_uncertainty_1 = "<<std::endl;
   
	// all combined uncertainties

   for (int i=0;i<BINS ;i++)
   {
	std::cout<<sqrt(ResultWeightDataStat[i])<<"  ";
   }

   std::cout<<std::endl<<std::endl<<"ll_uncertaintyUP_2 = "<<std::endl;
   for (int i=0;i<BINS ;i++)
   {
	std::cout<<sqrt(
					(aresultBBBWMTWDiLep[i]-aresultBBBWMTWUp[i]) * (aresultBBBWMTWDiLep[i]-aresultBBBWMTWUp[i]) +
					(aresultBBBWMTWDiLep[i]-aresultBBBWMTWDiLepUp[i]) * (aresultBBBWMTWDiLep[i]-aresultBBBWMTWDiLepUp[i]) + 
					(aresultBBBWMTWDiLep[i]-aresultWeightBinByBinAccUp[i]) * ( aresultBBBWMTWDiLep[i]-aresultWeightBinByBinAccUp[i]) +
					(aresultBBBWMTWDiLep[i]-amuonIsoTAPUp[i]) * (aresultBBBWMTWDiLep[i]-amuonIsoTAPUp[i]) + 
					(aresultBBBWMTWDiLep[i]-amuonRecoTAPUp[i]) * (aresultBBBWMTWDiLep[i]-amuonRecoTAPUp[i]) + 
					(aresultBBBWMTWDiLep[i]-aelecIsoTAPUp[i]) * (aresultBBBWMTWDiLep[i]-aelecIsoTAPUp[i]) + 
					(aresultBBBWMTWDiLep[i]-aelecRecoTAPUp[i]) * (aresultBBBWMTWDiLep[i]-aelecRecoTAPUp[i]) +
					(aresultBBBWMTWDiLep[i]-aresultWeightBBBDiBoUp[i]) * (aresultBBBWMTWDiLep[i]-aresultWeightBBBDiBoUp[i]) +
					(aresultBBBWMTWDiLep[i]-aresultWeightBBBNoCloUp[i]) * (aresultBBBWMTWDiLep[i]-aresultWeightBBBNoCloUp[i]) 
			)<<"  ";
   }

   std::cout<<std::endl<<std::endl<<"ll_uncertaintyDN_2 = "<<std::endl;
   for (int i=0;i<BINS ;i++)
   {
	std::cout<<sqrt(
					(aresultBBBWMTWDiLep[i]-aresultBBBWMTWDown[i]) * (aresultBBBWMTWDiLep[i]-aresultBBBWMTWDown[i]) + 
					(aresultBBBWMTWDiLep[i]-aresultBBBWMTWDiLepDown[i]) * (aresultBBBWMTWDiLep[i]-aresultBBBWMTWDiLepDown[i]) + 
					(aresultBBBWMTWDiLep[i]-aresultWeightBinByBinAccDown[i]) * ( aresultBBBWMTWDiLep[i]-aresultWeightBinByBinAccDown[i]) +
					(aresultBBBWMTWDiLep[i]-amuonIsoTAPDown[i]) * (aresultBBBWMTWDiLep[i]-amuonIsoTAPDown[i]) + 
					(aresultBBBWMTWDiLep[i]-amuonRecoTAPDown[i]) * (aresultBBBWMTWDiLep[i]-amuonRecoTAPDown[i]) + 
					(aresultBBBWMTWDiLep[i]-aelecIsoTAPDown[i]) * (aresultBBBWMTWDiLep[i]-aelecIsoTAPDown[i]) + 
					(aresultBBBWMTWDiLep[i]-aelecRecoTAPDown[i]) * (aresultBBBWMTWDiLep[i]-aelecRecoTAPDown[i]) +
					(aresultBBBWMTWDiLep[i]-aresultWeightBBBDiBoDown[i]) * (aresultBBBWMTWDiLep[i]-aresultWeightBBBDiBoDown[i]) +
					(aresultBBBWMTWDiLep[i]-aresultWeightBBBNoCloDown[i]) * (aresultBBBWMTWDiLep[i]-aresultWeightBBBNoCloDown[i]) 
			)<<"  ";
   }

/*
   std::cout<<std::endl<<std::endl<<"Baseline"<<std::endl;
   std::cout<<"# Prediction"<<baselineresultBBBWMTWDiLep<<std::endl;
   std::cout<<"MTW = "<<baselineresultBBBWMTWDiLep-baselineresultBBBWMTWDown <<"+"<<baselineresultBBBWMTWDown-baselineresultBBBWMTWDiLep <<std::endl;
   std::cout<<"DiLep = "<<baselineresultBBBWMTWDiLep-baselineresultBBBWMTWDiLepDown <<"+"<<abs(baselineresultBBBWMTWDiLep-baselineresultBBBWMTWDiLepDown) <<std::endl;
   std::cout<<"DiBoson = "<<baselineresultBBBWMTWDiLep-baselineresultWeightBBBDiBoDown <<"+"<<baselineresultWeightBBBDiBoUp-baselineresultBBBWMTWDiLep <<std::endl;
   std::cout<<"Non closure = "<<baselineresultBBBWMTWDiLep-baselineresultWeightBBBNoCloDown <<"+"<<abs(baselineresultBBBWMTWDiLep-baselineresultWeightBBBNoCloDown) <<std::endl;
   std::cout<<"Acceptance = "<<baselineresultBBBWMTWDiLep-baselineresultWeightBinByBinAccDown <<"+"<<baselineresultWeightBinByBinAccUp-baselineresultBBBWMTWDiLep <<std::endl;
   std::cout<<"IsoMu = "<<baselineresultBBBWMTWDiLep-amuonIsoTAPDown <<"+"<<abs(baselineresultBBBWMTWDiLep-amuonIsoTAPDown) <<std::endl;
   std::cout<<"RecoMu = "<<baselineresultBBBWMTWDiLep-amuonRecoTAPDown <<"+"<<abs(baselineresultBBBWMTWDiLep-amuonRecoTAPDown) <<std::endl;
   std::cout<<"IsoElec = "<<baselineresultBBBWMTWDiLep-aelecIsoTAPDown <<"+"<<abs(baselineresultBBBWMTWDiLep-aelecIsoTAPDown) <<std::endl;
   std::cout<<"RecoElec = "<<baselineresultBBBWMTWDiLep-aelecRecoTAPDown <<"+"<<abs(baselineresultBBBWMTWDiLep-aelecRecoTAPDown) <<std::endl;


   std::cout<<"total = -"<<sqrt(
					(baselineresultBBBWMTWDiLep-baselineresultBBBWMTWDown) * (baselineresultBBBWMTWDiLep-baselineresultBBBWMTWDown) + 
					(baselineresultBBBWMTWDiLep-baselineresultBBBWMTWDiLepDown) * (baselineresultBBBWMTWDiLep-baselineresultBBBWMTWDiLepDown) + 
					(baselineresultBBBWMTWDiLep-baselineresultWeightBinByBinAccDown) * ( baselineresultBBBWMTWDiLep-baselineresultWeightBinByBinAccDown) +
					(baselineresultBBBWMTWDiLep-amuonIsoTAPDown) * (baselineresultBBBWMTWDiLep-amuonIsoTAPDown) + 
					(baselineresultBBBWMTWDiLep-amuonRecoTAPDown) * (baselineresultBBBWMTWDiLep-amuonRecoTAPDown) + 
					(baselineresultBBBWMTWDiLep-aelecIsoTAPDown) * (baselineresultBBBWMTWDiLep-aelecIsoTAPDown) + 
					(baselineresultBBBWMTWDiLep-aelecRecoTAPDown) * (baselineresultBBBWMTWDiLep-aelecRecoTAPDown) +
					(baselineresultBBBWMTWDiLep-baselineresultWeightBBBDiBoDown) * (baselineresultBBBWMTWDiLep-baselineresultWeightBBBDiBoDown) +
					(baselineresultBBBWMTWDiLep-baselineresultWeightBBBNoCloDown) * (baselineresultBBBWMTWDiLep-baselineresultWeightBBBNoCloDown) 
			) 
			<<"+"
			<<sqrt(
					(baselineresultBBBWMTWDiLep-baselineresultBBBWMTWUp) * (baselineresultBBBWMTWDiLep-baselineresultBBBWMTWUp) +
					(baselineresultBBBWMTWDiLep-baselineresultBBBWMTWDiLepUp) * (baselineresultBBBWMTWDiLep-baselineresultBBBWMTWDiLepUp) + 
					(baselineresultBBBWMTWDiLep-baselineresultWeightBinByBinAccUp) * ( baselineresultBBBWMTWDiLep-baselineresultWeightBinByBinAccUp) +
					(baselineresultBBBWMTWDiLep-amuonIsoTAPUp) * (baselineresultBBBWMTWDiLep-amuonIsoTAPUp) + 
					(baselineresultBBBWMTWDiLep-amuonRecoTAPUp) * (baselineresultBBBWMTWDiLep-amuonRecoTAPUp) + 
					(baselineresultBBBWMTWDiLep-aelecIsoTAPUp) * (baselineresultBBBWMTWDiLep-aelecIsoTAPUp) + 
					(baselineresultBBBWMTWDiLep-aelecRecoTAPUp) * (baselineresultBBBWMTWDiLep-aelecRecoTAPUp) +
					(baselineresultBBBWMTWDiLep-baselineresultWeightBBBDiBoUp) * (baselineresultBBBWMTWDiLep-baselineresultWeightBBBDiBoUp) +
					(baselineresultBBBWMTWDiLep-baselineresultWeightBBBNoCloUp) * (baselineresultBBBWMTWDiLep-baselineresultWeightBBBNoCloUp) 
			)

			 <<std::endl;
  */


TString prediciton22 ("double llep[NBins] = {");
TString statup ("double llep_sUp[NBins] = {");
TString statdown ("double llep_sdn[NBins] = {");
TString sysup ("double llep_up[NBins] = {");
TString sysdown ("double llep_dn[NBins] = {");
for (int i=0;i<BINS;i++)
{
if(lowNjetTemp < binmap[i+1][0]-0.5)
{
cout<<"NJets["<<binmap[i+1][0]<<","<<binmap[i+1][1]<<"]"<<std::endl;
lowNjetTemp=binmap[i+1][0];
	std::cout<<"\\HT (GeV)& \\MHT (GeV)& Pred. & Stat. &  $M_{T}$ & diLep & other SM & non closure & Accept. & muIso & muId & elecIso & elecId &  Tot. Sys. \\\\"<<std::endl;
	std::cout<<"\\hline"<<std::endl;
}
// bin printing

char num[10];
sprintf(num,"%.2f",ResultWeightData[i]);

TString aa (", ");
TString temp23(num);
prediciton22+=temp23;
prediciton22+=aa;
sprintf(num,"%.2f",sqrt(ResultWeightDataStat[i]));
temp23=num;
statup+=temp23;
statup+=aa;
sprintf(num,"%.2f",sqrt(ResultWeightDataStat[i]));
temp23=num;
statdown+=temp23;
statdown+=aa;
sprintf(num,"%.2f",sqrt(//sqrt(ResultWeightDataStat[i])*sqrt(ResultWeightDataStat[i]) +
					(aresultBBBWMTWDiLep[i]-aresultBBBWMTWDown[i]) * (aresultBBBWMTWDiLep[i]-aresultBBBWMTWDown[i]) + 
					(aresultBBBWMTWDiLep[i]-aresultBBBWMTWDiLepDown[i]) * (aresultBBBWMTWDiLep[i]-aresultBBBWMTWDiLepDown[i]) + 
					(aresultBBBWMTWDiLep[i]-aresultWeightBinByBinAccDown[i]) * ( aresultBBBWMTWDiLep[i]-aresultWeightBinByBinAccDown[i]) +
					(aresultBBBWMTWDiLep[i]-amuonIsoTAPDown[i]) * (aresultBBBWMTWDiLep[i]-amuonIsoTAPDown[i]) + 
					(aresultBBBWMTWDiLep[i]-amuonRecoTAPDown[i]) * (aresultBBBWMTWDiLep[i]-amuonRecoTAPDown[i]) + 
					(aresultBBBWMTWDiLep[i]-aelecIsoTAPDown[i]) * (aresultBBBWMTWDiLep[i]-aelecIsoTAPDown[i]) + 
					(aresultBBBWMTWDiLep[i]-aelecRecoTAPDown[i]) * (aresultBBBWMTWDiLep[i]-aelecRecoTAPDown[i]) +
					(aresultBBBWMTWDiLep[i]-aresultWeightBBBDiBoDown[i]) * (aresultBBBWMTWDiLep[i]-aresultWeightBBBDiBoDown[i]) +
					(aresultBBBWMTWDiLep[i]-aresultWeightBBBNoCloDown[i]) * (aresultBBBWMTWDiLep[i]-aresultWeightBBBNoCloDown[i]) 
			)
	);
temp23=num;
sysdown+=temp23;
sysdown+=aa;
sprintf(num,"%.2f",sqrt(//sqrt(ResultWeightDataStat[i])*sqrt(ResultWeightDataStat[i]) +
					(aresultBBBWMTWDiLep[i]-aresultBBBWMTWUp[i]) * (aresultBBBWMTWDiLep[i]-aresultBBBWMTWUp[i]) +
					(aresultBBBWMTWDiLep[i]-aresultBBBWMTWDiLepUp[i]) * (aresultBBBWMTWDiLep[i]-aresultBBBWMTWDiLepUp[i]) + 
					(aresultBBBWMTWDiLep[i]-aresultWeightBinByBinAccUp[i]) * ( aresultBBBWMTWDiLep[i]-aresultWeightBinByBinAccUp[i]) +
					(aresultBBBWMTWDiLep[i]-amuonIsoTAPUp[i]) * (aresultBBBWMTWDiLep[i]-amuonIsoTAPUp[i]) + 
					(aresultBBBWMTWDiLep[i]-amuonRecoTAPUp[i]) * (aresultBBBWMTWDiLep[i]-amuonRecoTAPUp[i]) + 
					(aresultBBBWMTWDiLep[i]-aelecIsoTAPUp[i]) * (aresultBBBWMTWDiLep[i]-aelecIsoTAPUp[i]) + 
					(aresultBBBWMTWDiLep[i]-aelecRecoTAPUp[i]) * (aresultBBBWMTWDiLep[i]-aelecRecoTAPUp[i]) +
					(aresultBBBWMTWDiLep[i]-aresultWeightBBBDiBoUp[i]) * (aresultBBBWMTWDiLep[i]-aresultWeightBBBDiBoUp[i]) +
					(aresultBBBWMTWDiLep[i]-aresultWeightBBBNoCloUp[i]) * (aresultBBBWMTWDiLep[i]-aresultWeightBBBNoCloUp[i]) 
			)
	);
temp23=num;
sysup+=temp23;
sysup+=aa;


//if()
//if(ResultWeightData[i]>0.001) 
}
TString ende ("};");
prediciton22+=ende;
statup+=ende;
statdown+=ende;
sysup+=ende;
sysdown+=ende;
lowNjetTemp=0;

cout<<"Seema result prediciton output::"<<std::endl;
cout<<prediciton22<<endl;
cout<<statup<<endl;
cout<<statdown<<endl;
cout<<sysup<<endl;
cout<<sysdown<<endl;
cout<<"---------------------------------------------------"<<endl;










if (!data)
{
lowNjetTemp=0;
cout<<"MC avarge weights times 1.84 for poisson 68% cl for each search bin together with avarge systematic uncertainty. These values are used for bins with 0 muon controlsample"<<endl;


for (int i=0;i<BINS;i++)
{
if(lowNjetTemp < binmap[i+1][0]-0.5)
{
cout<<"NJets["<<binmap[i+1][0]<<","<<binmap[i+1][1]<<"]"<<std::endl;
lowNjetTemp=binmap[i+1][0];
	std::cout<<"\\HT (GeV)& \\MHT (GeV)& Pred. & Stat. &  $M_{T}$ & diLep & other SM & non closure & Accept. & muIso & muId & elecIso & elecId &  Tot. Sys. \\\\"<<std::endl;
	std::cout<<"\\hline"<<std::endl;
}
// bin printing
cout<<binmap[i+1][2]<<"\\ldots "<<binmap[i+1][3]<<"& "<<binmap[i+1][4]<<" \\ldots "<<binmap[i+1][5] <<"  &";
cout<<ResultWeightData[i]/ResultWeightDataCS[i]*1.84;
cout	<<"  &$_{-"<<sqrt(//sqrt(ResultWeightDataStat[i])*sqrt(ResultWeightDataStat[i]) +
					(aresultBBBWMTWDiLep[i]-aresultBBBWMTWDown[i]) * (aresultBBBWMTWDiLep[i]-aresultBBBWMTWDown[i]) + 
					(aresultBBBWMTWDiLep[i]-aresultBBBWMTWDiLepDown[i]) * (aresultBBBWMTWDiLep[i]-aresultBBBWMTWDiLepDown[i]) + 
					(aresultBBBWMTWDiLep[i]-aresultWeightBinByBinAccDown[i]) * ( aresultBBBWMTWDiLep[i]-aresultWeightBinByBinAccDown[i]) +
					(aresultBBBWMTWDiLep[i]-amuonIsoTAPDown[i]) * (aresultBBBWMTWDiLep[i]-amuonIsoTAPDown[i]) + 
					(aresultBBBWMTWDiLep[i]-amuonRecoTAPDown[i]) * (aresultBBBWMTWDiLep[i]-amuonRecoTAPDown[i]) + 
					(aresultBBBWMTWDiLep[i]-aelecIsoTAPDown[i]) * (aresultBBBWMTWDiLep[i]-aelecIsoTAPDown[i]) + 
					(aresultBBBWMTWDiLep[i]-aelecRecoTAPDown[i]) * (aresultBBBWMTWDiLep[i]-aelecRecoTAPDown[i]) +
					(aresultBBBWMTWDiLep[i]-aresultWeightBBBDiBoDown[i]) * (aresultBBBWMTWDiLep[i]-aresultWeightBBBDiBoDown[i]) +
					(aresultBBBWMTWDiLep[i]-aresultWeightBBBNoCloDown[i]) * (aresultBBBWMTWDiLep[i]-aresultWeightBBBNoCloDown[i]) 
			)/ResultWeightDataCS[i]*1.84
	<<"}^{+"<<sqrt(//sqrt(ResultWeightDataStat[i])*sqrt(ResultWeightDataStat[i]) +
					(aresultBBBWMTWDiLep[i]-aresultBBBWMTWUp[i]) * (aresultBBBWMTWDiLep[i]-aresultBBBWMTWUp[i]) +
					(aresultBBBWMTWDiLep[i]-aresultBBBWMTWDiLepUp[i]) * (aresultBBBWMTWDiLep[i]-aresultBBBWMTWDiLepUp[i]) + 
					(aresultBBBWMTWDiLep[i]-aresultWeightBinByBinAccUp[i]) * ( aresultBBBWMTWDiLep[i]-aresultWeightBinByBinAccUp[i]) +
					(aresultBBBWMTWDiLep[i]-amuonIsoTAPUp[i]) * (aresultBBBWMTWDiLep[i]-amuonIsoTAPUp[i]) + 
					(aresultBBBWMTWDiLep[i]-amuonRecoTAPUp[i]) * (aresultBBBWMTWDiLep[i]-amuonRecoTAPUp[i]) + 
					(aresultBBBWMTWDiLep[i]-aelecIsoTAPUp[i]) * (aresultBBBWMTWDiLep[i]-aelecIsoTAPUp[i]) + 
					(aresultBBBWMTWDiLep[i]-aelecRecoTAPUp[i]) * (aresultBBBWMTWDiLep[i]-aelecRecoTAPUp[i]) +
					(aresultBBBWMTWDiLep[i]-aresultWeightBBBDiBoUp[i]) * (aresultBBBWMTWDiLep[i]-aresultWeightBBBDiBoUp[i]) +
					(aresultBBBWMTWDiLep[i]-aresultWeightBBBNoCloUp[i]) * (aresultBBBWMTWDiLep[i]-aresultWeightBBBNoCloUp[i]) 
			)/ResultWeightDataCS[i]*1.84;




cout	<<"}  \\\\   "<<std::endl;
}

lowNjetTemp=0;
}
if (debug)
{
std::cout<<"Debug results::"<<std::endl;
std::cout<<"-----------------------------------------------------"<<std::endl;
std::cout<<"BaselineResult(baselineWeightData:"<<baselineWeightData<<"+-"<<baselineWeightDataStat<<std::endl;





}


}
