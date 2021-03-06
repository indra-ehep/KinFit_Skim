#include<TH2D.h>
#include<TFile.h>

#include <iostream>


using namespace std;

class MuonSF
{
 public:
    MuonSF(string id_filename, string id_histName,
	   string iso_filename, string iso_histName,
	   string trig_filename, string trig_histName){

	TFile* idFile = TFile::Open(id_filename.c_str(),"READ");
	idHist = (TH2F*) idFile->Get(id_histName.c_str());

	TFile* isoFile = TFile::Open(iso_filename.c_str(),"READ");
	isoHist = (TH2F*) isoFile->Get(iso_histName.c_str());

	TFile* trigFile = TFile::Open(trig_filename.c_str(),"READ");
	trigHist = (TH2F*) trigFile->Get(trig_histName.c_str());
	
    }
    std::vector<double> getMuSF(double pt, double eta, int systLevel, int year, bool verbose=false);
    double getMuSF(TH2F *h2, double pt, double eta, int systLevel);
    /* bool splitSystsId = false; */
    /* bool splitSystsIso = false; */
    /* bool splitSystsTrig = false; */
    
 private:
    TH2F* idHist;
    TH2F* isoHist;
    TH2F* trigHist;
    
    /* string isoName; */
    /* string idName; */
    /* string trigName; */
};


double MuonSF::getMuSF(TH2F *h2, double eta, double pt, int systLevel){

  TAxis *axisX = h2->GetXaxis();
  TAxis *axisY = h2->GetYaxis();

  //Get max of x and y range
  double minX = axisX->GetBinCenter(1);
  double maxX = axisX->GetBinCenter(h2->GetNbinsX());
  
  double minY = axisY->GetBinCenter(1);
  double maxY = axisY->GetBinCenter(h2->GetNbinsY());
  
  //Get the bin numbers for a given eta, pt
  //If pt or eta value is out of hist range, choose the first/last bin
  Int_t binX = -1;
  if(eta <= minX)
    binX = 1;
  else if(eta >= maxX)
    binX = h2->GetNbinsX();
  else
    binX = axisX->FindBin(eta);

  Int_t binY = -1;
  if(pt <= minY)
    binY = 1;
  else if(pt >= maxY)
    binY = h2->GetNbinsY();
  else
    binY = axisY->FindBin(pt);

  //Get the scale factor and error for that bin
  double sf = h2->GetBinContent(binX, binY);
  double err = h2->GetBinError(binX, binY);
  if (TMath::AreEqualAbs(sf,0.0,1.e-7) and TMath::AreEqualAbs(err,0.0,1.e-7))
    return 1.0;
  else
    return sf + (systLevel -1)*err;
}


std::vector<double> MuonSF::getMuSF(double pt, double eta, int systLevel, int year, bool verbose){

    /* double abseta = fabs(eta); */

    /* int muEtaRegion_IDIso = -1; */
    /* int muEtaRegion_Trigger = -1; */
    /* int muPtRegion_IDIso = -1; */
    /* int muPtRegion_Trigger = -1; */

    /* int idX = -1; */
    /* int idY = -1; */
    /* int trigX = -1; */
    /* int trigY = -1; */

    /* if (year==2016){ */

    /* 	if (eta < -2.3 ) {  muEtaRegion_IDIso = 1 ; } */
    /* 	else if (eta < -2.2 ) {  muEtaRegion_IDIso = 2 ; } */
    /* 	else if (eta < -2.1 ) {  muEtaRegion_IDIso = 3 ; } */
    /* 	else if (eta < -2   ) {  muEtaRegion_IDIso = 4 ; } */
    /* 	else if (eta < -1.7 ) {  muEtaRegion_IDIso = 5 ; } */
    /* 	else if (eta < -1.6 ) {  muEtaRegion_IDIso = 6 ; } */
    /* 	else if (eta < -1.5 ) {  muEtaRegion_IDIso = 7 ; } */
    /* 	else if (eta < -1.4 ) {  muEtaRegion_IDIso = 8 ; } */
    /* 	else if (eta <  -1.2) {  muEtaRegion_IDIso = 9 ; } */
    /* 	else if (eta <  -0.8) {  muEtaRegion_IDIso = 10; } */
    /* 	else if (eta <  -0.5) {  muEtaRegion_IDIso = 11; } */
    /* 	else if (eta <  -0.3) {  muEtaRegion_IDIso = 12; } */
    /* 	else if (eta <  -0.2) {  muEtaRegion_IDIso = 13; } */
    /* 	else if (eta <  0   ) {  muEtaRegion_IDIso = 14; } */
    /* 	else if (eta <  0.2 ) {  muEtaRegion_IDIso = 15; } */
    /* 	else if (eta <  0.3 ) {  muEtaRegion_IDIso = 16; } */
    /* 	else if (eta <  0.5 ) {  muEtaRegion_IDIso = 17; } */
    /* 	else if (eta <  0.8 ) {  muEtaRegion_IDIso = 18; } */
    /* 	else if (eta <  1.2 ) {  muEtaRegion_IDIso = 19; } */
    /* 	else if (eta <  1.4 ) {  muEtaRegion_IDIso = 20; } */
    /* 	else if (eta <  1.5 ) {  muEtaRegion_IDIso = 21; } */
    /* 	else if (eta <  1.6 ) {  muEtaRegion_IDIso = 22; } */
    /* 	else if (eta <  1.7 ) {  muEtaRegion_IDIso = 23; } */
    /* 	else if (eta <  2   ) {  muEtaRegion_IDIso = 24; } */
    /* 	else if (eta <  2.1 ) {  muEtaRegion_IDIso = 25; } */
    /* 	else if (eta <  2.2 ) {  muEtaRegion_IDIso = 26; } */
    /* 	else if (eta <  2.3 ) {  muEtaRegion_IDIso = 27; } */
    /* 	else {  muEtaRegion_IDIso = 28; } */


    /* 	if (pt < 25.0) { muPtRegion_IDIso =   1; } */
    /* 	else if (pt < 30.0) { muPtRegion_IDIso =   2; } */
    /* 	else if (pt < 40.0) { muPtRegion_IDIso =   3; }  */
    /* 	else if (pt < 50.0) { muPtRegion_IDIso =   4; } */
    /* 	else if (pt < 60.0) { muPtRegion_IDIso =   5; } */
    /* 	else { muPtRegion_IDIso =   6; } */

    /* 	if (abseta < 0.9) {muEtaRegion_Trigger = 1;} */
    /* 	else if (abseta < 1.2) {muEtaRegion_Trigger = 2;} */
    /* 	else if (abseta < 2.1) {muEtaRegion_Trigger = 3;} */
    /* 	else {muEtaRegion_Trigger = 4;} */
    
    /* 	if (pt < 30.) { muPtRegion_Trigger = 1;} */
    /* 	else if (pt < 40.) { muPtRegion_Trigger = 2;} */
    /* 	else if (pt < 50.) { muPtRegion_Trigger = 3;} */
    /* 	else if (pt < 60.) { muPtRegion_Trigger = 4;} */
    /* 	else if (pt < 120.) { muPtRegion_Trigger = 5;} */
    /* 	else if (pt < 200.) { muPtRegion_Trigger = 6;} */
    /* 	else { muPtRegion_Trigger = 7;} */

    /* 	idX = muEtaRegion_IDIso; */
    /* 	idY = muPtRegion_IDIso; */

    /* 	trigX = muEtaRegion_Trigger; */
    /* 	trigY = muPtRegion_Trigger; */

    /* } else if (year==2017) { */


    /* 	if (abseta < 0.9) {muEtaRegion_IDIso = 1;} */
    /* 	else if (abseta < 1.2) {muEtaRegion_IDIso = 2;} */
    /* 	else if (abseta < 2.1) {muEtaRegion_IDIso = 3;} */
    /* 	else {muEtaRegion_IDIso = 4;} */
    
    /* 	if (pt < 25.) { muPtRegion_IDIso = 1;} */
    /* 	else if (pt < 30.) { muPtRegion_IDIso = 2;} */
    /* 	else if (pt < 40.) { muPtRegion_IDIso = 3;} */
    /* 	else if (pt < 50.) { muPtRegion_IDIso = 4;} */
    /* 	else if (pt < 60.) { muPtRegion_IDIso = 5;} */
    /* 	else { muPtRegion_IDIso = 6;} */

    /* 	if (abseta < 0.9) {muEtaRegion_Trigger = 1;} */
    /* 	else if (abseta < 1.2) {muEtaRegion_Trigger = 2;} */
    /* 	else if (abseta < 2.1) {muEtaRegion_Trigger = 3;} */
    /* 	else {muEtaRegion_Trigger = 4;} */
    
    /* 	if (pt < 32.) { muPtRegion_Trigger = 1;} */
    /* 	else if (pt < 40.) { muPtRegion_Trigger = 2;} */
    /* 	else if (pt < 50.) { muPtRegion_Trigger = 3;} */
    /* 	else if (pt < 60.) { muPtRegion_Trigger = 4;} */
    /* 	else if (pt < 120.) { muPtRegion_Trigger = 5;} */
    /* 	else if (pt < 200.) { muPtRegion_Trigger = 6;} */
    /* 	else { muPtRegion_Trigger = 7;} */

    /* 	idX = muPtRegion_IDIso; */
    /* 	idY = muEtaRegion_IDIso; */

    /* 	trigX = muEtaRegion_Trigger; */
    /* 	trigY = muPtRegion_Trigger; */

    /* } else if (year==2018) { */

    /* 	if (abseta < 0.9) {muEtaRegion_IDIso = 1;} */
    /* 	else if (abseta < 1.2) {muEtaRegion_IDIso = 2;} */
    /* 	else if (abseta < 2.1) {muEtaRegion_IDIso = 3;} */
    /* 	else {muEtaRegion_IDIso = 4;} */
    
    /* 	if (pt < 20.) { muPtRegion_IDIso = 1;} */
    /* 	else if (pt < 25.) { muPtRegion_IDIso = 2;} */
    /* 	else if (pt < 30.) { muPtRegion_IDIso = 3;} */
    /* 	else if (pt < 40.) { muPtRegion_IDIso = 4;} */
    /* 	else if (pt < 50.) { muPtRegion_IDIso = 5;} */
    /* 	else if (pt < 60.) { muPtRegion_IDIso = 6;} */
    /* 	else { muPtRegion_IDIso = 7;} */


    /* 	if (abseta < 0.9) {muEtaRegion_Trigger = 1;} */
    /* 	else if (abseta < 1.2) {muEtaRegion_Trigger = 2;} */
    /* 	else if (abseta < 2.1) {muEtaRegion_Trigger = 3;} */
    /* 	else {muEtaRegion_Trigger = 4;} */
    
    /* 	if (pt < 30.) { muPtRegion_Trigger = 1;} */
    /* 	else if (pt < 40.) { muPtRegion_Trigger = 2;} */
    /* 	else if (pt < 50.) { muPtRegion_Trigger = 3;} */
    /* 	else if (pt < 60.) { muPtRegion_Trigger = 4;} */
    /* 	else if (pt < 120.) { muPtRegion_Trigger = 5;} */
    /* 	else if (pt < 200.) { muPtRegion_Trigger = 6;} */
    /* 	else if (pt < 300.) { muPtRegion_Trigger = 7;} */
    /* 	else { muPtRegion_Trigger = 8;} */
	
    /* 	idX = muPtRegion_IDIso; */
    /* 	idY = muEtaRegion_IDIso; */

    /* 	trigX = muEtaRegion_Trigger; */
    /* 	trigY = muPtRegion_Trigger; */

    /* } */

    /* double id_SF_value = idHist->GetBinContent(idX, idY); */
    /* double id_SF_error = idHist->GetBinError(idX, idY); */

    /* double id_SF = id_SF_value + (systLevel-1)*id_SF_error; */

    /* double iso_SF_value = isoHist->GetBinContent(idX, idY); */
    /* double iso_SF_error = isoHist->GetBinError(idX, idY); */

    /* double iso_SF = iso_SF_value + (systLevel-1)*iso_SF_error; */


    /* double trig_SF_value = trigHist->GetBinContent(trigX, trigY); */
    /* double trig_SF_error = trigHist->GetBinError(trigX, trigY); */

    /* double trig_SF = trig_SF_value + (systLevel-1)*trig_SF_error; */
    
    //double pt, double eta, int systLevel, int year, bool verbose
    

    /* //eta = fabs(eta); */
    
    /* ///////// set U/Overflow eta/pt values to the min/max values of TH2 for ID ///////////////// */
    /* double etaID, ptID; */
    /* if(eta <= idHist->GetXaxis()->GetXmin()) */
    /*   etaID = idHist->GetXaxis()->GetXmin(); */
    /* else if(eta >= idHist->GetXaxis()->GetXmax()) */
    /*   etaID = idHist->GetXaxis()->GetXmax(); */
    /* else */
    /*   etaID = eta; */

    /* if(pt <= idHist->GetYaxis()->GetXmin()) */
    /*   ptID = idHist->GetYaxis()->GetXmin(); */
    /* else if(pt >= idHist->GetYaxis()->GetXmax()) */
    /*   ptID = idHist->GetYaxis()->GetXmax(); */
    /* else */
    /*   ptID = pt; */
    /* ///////////////////////////////////////////////////////////////////////////////////////////// */

    /* ///////// set U/Overflow eta/pt values to the min/max values of TH2 for ISO ///////////////// */
    /* double etaISO, ptISO; */
    /* if(eta <= isoHist->GetXaxis()->GetXmin()) */
    /*   etaISO = isoHist->GetXaxis()->GetXmin(); */
    /* else if(eta >= isoHist->GetXaxis()->GetXmax()) */
    /*   etaISO = isoHist->GetXaxis()->GetXmax(); */
    /* else */
    /*   etaISO = eta; */

    /* if(pt <= isoHist->GetYaxis()->GetXmin()) */
    /*   ptISO = isoHist->GetYaxis()->GetXmin(); */
    /* else if(pt >= isoHist->GetYaxis()->GetXmax()) */
    /*   ptISO = isoHist->GetYaxis()->GetXmax(); */
    /* else */
    /*   ptISO = pt; */
    /* ///////////////////////////////////////////////////////////////////////////////////////////// */
    
    /* /////////////////////////////////////////////////////////////////////////////////////////// */
    /* eta = fabs(eta); */
    /* ///////// set U/Overflow eta/pt values to the min/max values of TH2 for Trigger ///////////// */
    /* double etaTRIG, ptTRIG; */
    /* if(eta <= trigHist->GetXaxis()->GetXmin()) */
    /*   etaTRIG = trigHist->GetXaxis()->GetXmin(); */
    /* if(eta >= trigHist->GetXaxis()->GetXmax()) */
    /*   etaTRIG = trigHist->GetXaxis()->GetXmax(); */
    /* else */
    /*   etaTRIG = eta; */

    /* if(pt <= trigHist->GetYaxis()->GetXmin()) */
    /*   ptTRIG = trigHist->GetYaxis()->GetXmin(); */
    /* else if(pt >= trigHist->GetYaxis()->GetXmax()) */
    /*   ptTRIG = trigHist->GetYaxis()->GetXmax(); */
    /* else */
    /*   ptTRIG = pt; */
    /* ///////////////////////////////////////////////////////////////////////////////////////////// */

    /* /\* double id_SF_value = idHist->GetBinContent(idHist->FindBin(etaID,ptID)); *\/ */
    /* /\* double id_SF_error = idHist->GetBinError(idHist->FindBin(etaID,ptID)); *\/ */
    /* double id_SF_value = idHist->GetBinContent(idHist->GetXaxis()->FindBin(etaID), idHist->GetYaxis()->FindBin(ptID)); */
    /* double id_SF_error = idHist->GetBinError(idHist->GetXaxis()->FindBin(etaID), idHist->GetYaxis()->FindBin(ptID)); */
    /* double id_SF = id_SF_value + (systLevel-1)*id_SF_error; */

    /* /\* double iso_SF_value = isoHist->GetBinContent(isoHist->FindBin(etaISO,ptISO)); *\/ */
    /* /\* double iso_SF_error = isoHist->GetBinError(isoHist->FindBin(etaISO,ptISO)); *\/ */
    /* double iso_SF_value = isoHist->GetBinContent(isoHist->GetXaxis()->FindBin(etaISO), isoHist->GetYaxis()->FindBin(ptISO)); */
    /* double iso_SF_error = isoHist->GetBinError(isoHist->GetXaxis()->FindBin(etaISO), isoHist->GetYaxis()->FindBin(ptISO)); */
    /* double iso_SF = iso_SF_value + (systLevel-1)*iso_SF_error; */

    /* double trig_SF_value = trigHist->GetBinContent(trigHist->GetXaxis()->FindBin(etaTRIG), trigHist->GetYaxis()->FindBin(ptTRIG)); */
    /* double trig_SF_error = trigHist->GetBinError(trigHist->GetXaxis()->FindBin(etaTRIG), trigHist->GetYaxis()->FindBin(ptTRIG)); */
    /* double trig_SF = trig_SF_value + (systLevel-1)*trig_SF_error; */

    /* //    double muEffSF=id_SF*iso_SF*trig_SF; */
    /* std::vector<double> muSF {id_SF*iso_SF*trig_SF, id_SF, iso_SF, trig_SF}; */
    
    /* if (verbose) { */
    /* 	cout << "Muon Scale Factors: " << endl; */
    /* 	cout << "    ID   = " << id_SF << endl; */
    /* 	cout << "    Iso  = " << iso_SF << endl; */
    /* 	cout << "    Trig = " << trig_SF << endl; */
    /* 	cout << "    Total= " << id_SF*iso_SF*trig_SF << endl; */
    /* } */

  double idSF    = 1.0;
  double isoSF   = 1.0;
  double trigSF  = 1.0;
  
  idSF    = getMuSF(idHist, TMath::Abs(eta), pt, systLevel);//eta: 0, 2.4
  isoSF   = getMuSF(isoHist, TMath::Abs(eta), pt, systLevel);//eta: 0, 2.4
  trigSF  = getMuSF(trigHist, eta, pt, systLevel);//eta: -2.4, 2.4
  
  vector<double> muSF {idSF*isoSF*trigSF, idSF, isoSF, trigSF};
  if (verbose){
    cout<<"----------------------------"<<endl;
    cout << "Muon Scale Factors: " << endl;
    cout<<  "    pt   = " <<pt<<endl;
    cout<<  "    eta   = " <<eta<<endl;
    cout << "    ID   = " << idSF << endl;
    cout << "    Iso  = " << isoSF << endl;
    cout << "    Trig = " << trigSF << endl;
    cout << "    Total= " << idSF*isoSF*trigSF << endl;
  }

    return muSF;

}

