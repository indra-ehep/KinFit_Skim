/**********************************************************************
 Created on : 07/06/2023
 Purpose    : Calculate kappa and plot the correlation
 Author     : Indranil Das, Visiting Fellow
 Email      : indranil.das@cern.ch | indra.ehep@gmail.com
**********************************************************************/
#if !defined(__CINT__) || defined(__MAKECINT__)

#include <TROOT.h>
#include <TChain.h>
#include <TEntryList.h>
#include <TFile.h>
//#include <TProofOutputFile.h>
#include <TSelector.h>
#include <vector>

#include "TH1F.h"
#include "TProfile.h"
#include <THStack.h>
#include "TH2.h"
#include "TF1.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TPaveStats.h"
#include "TMath.h"
//#include "TProof.h"

#include "TParticlePDG.h"
#include "TDatabasePDG.h"

#include "TLorentzVector.h"
#include "TVector3.h"

#include <fstream>

using namespace std;

#endif

void KFCalcKappa(int year = 2016, bool ismu = true)
{
  void makeHistoPositive(TH1F *hist, bool setErrorZero);
  int PlotRatio(TH1F *h1, TH1F *h2, const char *cname, const char *deno_xTitle, const char *deno_yTitle, float kappa, float yield, bool isy);

  // case Validation : Iso : 0.15, MET = 20 GeV
  // case 1 :: A(0.15,20), B(0.2,20), C(0.2,15), D(0.15,15)
  // case 2 :: A(0.15,40), B(0.2,40), C(0.2,10), D(0.15,10)
  // case 3 :: A(0.15,60), B(0.2,60), C(0.2,10), D(0.15,10)
  // case 4 :: A(0.15,60), B(0.2,60), C(0.2,40), D(0.15,40)
  // case 5 :: A(0.15,60), B(0.2,60), C(0.2,60), D(0.15,60)
  // case 6 :: A(0.15,30), B(0.15,30), C(0.15,30), D(0.15,30)
  // case 7 :: A(0.15,40), B(0.15,40), C(0.15,40), D(0.15,40)
  // case 8 :: A(0.15,50), B(0.15,50), C(0.15,50), D(0.15,50)
  // case 9 :: A(0.15,60), B(0.15,60), C(0.15,60), D(0.15,60)
  // case 10 :: A(0.15,10), B(0.15,10), C(0.15,10), D(0.15,10)
  // case 11 :: A(0.1,40), B(0.1,40), C(0.1,40), D(0.1,40)
  // case 12 :: A(0.2,40), B(0.2,40), C(0.2,40), D(0.2,40)
  // case 13 :: A(0.1,20), B(0.1,20), C(0.1,20), D(0.1,20)
  // case 14 :: A(0.2,20), B(0.2,20), C(0.2,20), D(0.2,20)
  // case 15 :: A(0.1,30), B(0.1,30), C(0.1,30), D(0.1,30)
  // case 16 :: A(0.2,30), B(0.2,30), C(0.2,30), D(0.2,30)

  // case 17 :: A(0.2,50), B(0.2,50), C(0.2,50), D(0.2,50)
  // case 18 :: A(0.25,40), B(0.25,40), C(0.25,40), D(0.25,40)
  // case 19 :: A(0.25,30), B(0.25,30), C(0.25,30), D(0.25,30)
  // case 20 :: A(0.3,40), B(0.3,40), C(0.3,40), D(0.3,40)
  
  // case 21 :: A(0.15,35), B(0.15,35), C(0.15,35), D(0.15,35)
  
  string indir = "output/kappa";
  
  string case_n =  "validn";
  //string case_n =  "case9";
  string fprenom = "output_kappa_" + case_n ;
  
  //string cut_title = "A(<0.15(0.07(0.08)),>10 GeV), C(>0.15(0.07(0.08)),<10 GeV)";
  string cut_title = "A(<0.15(0.07(0.08)),>20 GeV), C(>0.15(0.07(0.08)),<20 GeV)";
  //string cut_title = "A(<0.15(0.07(0.08)),>30 GeV), C(>0.15(0.07(0.08)),<30 GeV)";
  //string cut_title = "A(<0.15(0.07(0.08)),>40 GeV), C(>0.15(0.07(0.08)),<40 GeV)";
  //string cut_title = "A(<0.15(0.07(0.08)),>50 GeV), C(>0.15(0.07(0.08)),<50 GeV)";
  //string cut_title = "A(<0.15(0.07(0.08)),>60 GeV), C(>0.15(0.07(0.08)),<60 GeV)";
  //string cut_title = "A(<0.1,>20 GeV), C(>0.1,<20 GeV)";
  //string cut_title = "A(<0.2,>20 GeV), C(>0.2,<20 GeV)";
  //string cut_title = "A(<0.2,>30 GeV), C(>0.2,<30 GeV)";
  //string cut_title = "A(<0.2,>40 GeV), C(>0.2,<40 GeV)";
  //string cut_title = "A(<0.2,>50 GeV), C(>0.2,<50 GeV)";
  //string cut_title = "A(<0.25,>40 GeV), C(>0.25,<40 GeV)";
  //string cut_title = "A(<0.25,>30 GeV), C(>0.25,<30 GeV)";
  //string cut_title = "A(<0.3,>40 GeV), C(>0.3,<40 GeV)";
  //string cut_title = "A(<0.15(0.07(0.08)),>40 GeV), C(>0.15(0.07(0.08)),<40 GeV)";
  // if(!ismu)
  //   cut_title = "A(<0.07(0.08),>40 GeV), C(>0.07(0.08),<40 GeV)";
  
  TFile *fdata = (ismu) ? TFile::Open(Form("%s/%s_DataMu_%d.root",indir.c_str(),fprenom.c_str(),year)) : TFile::Open(Form("%s/%s_DataEle_%d.root",indir.c_str(),fprenom.c_str(),year)); 
  TFile *fttbar = TFile::Open(Form("%s/%s_TTbar_%d.root",indir.c_str(),fprenom.c_str(),year)) ;
  TFile *fstop = TFile::Open(Form("%s/%s_singleTop_%d.root",indir.c_str(),fprenom.c_str(),year)) ;
  TFile *fwjets = TFile::Open(Form("%s/%s_Wjets_%d.root",indir.c_str(),fprenom.c_str(),year)) ;
  TFile *fdyjets = TFile::Open(Form("%s/%s_DYjets_%d.root",indir.c_str(),fprenom.c_str(),year)) ;
  TFile *fvv = TFile::Open(Form("%s/%s_VBFusion_%d.root",indir.c_str(),fprenom.c_str(),year)) ;
  TFile *fmcqcd = (ismu) ? TFile::Open(Form("%s/%s_MCQCDMu_%d.root",indir.c_str(),fprenom.c_str(),year)) : TFile::Open(Form("%s/%s_MCQCDEle_%d.root",indir.c_str(),fprenom.c_str(),year));

  ///////////////// ttbar /////////////////////
  //A
  TH1F	*METptMu_ttbar_A  = (TH1F *)fttbar->Get("METptMu_A"); 
  TH1F	*IsoMu_ttbar_A	  = (TH1F *)fttbar->Get("IsoMu_A"); 
  TH1F	*mjjMu_ttbar_Ap	  = (TH1F *)fttbar->Get("mjjMu_Ap");
  TH1F	*METptEle_ttbar_A = (TH1F *)fttbar->Get("METptEle_A"); 
  TH1F	*IsoEle_ttbar_A	  = (TH1F *)fttbar->Get("IsoEle_A"); 
  TH1F	*mjjEle_ttbar_Ap	  = (TH1F *)fttbar->Get("mjjEle_Ap");
  //B
  TH1F	*METptMu_ttbar_B  = (TH1F *)fttbar->Get("METptMu_B"); 
  TH1F	*IsoMu_ttbar_B	  = (TH1F *)fttbar->Get("IsoMu_B"); 
  TH1F	*mjjMu_ttbar_Bp	  = (TH1F *)fttbar->Get("mjjMu_Bp");
  TH1F	*METptEle_ttbar_B = (TH1F *)fttbar->Get("METptEle_B"); 
  TH1F	*IsoEle_ttbar_B	  = (TH1F *)fttbar->Get("IsoEle_B"); 
  TH1F	*mjjEle_ttbar_Bp	  = (TH1F *)fttbar->Get("mjjEle_Bp");
  //C
  TH1F	*METptMu_ttbar_C  = (TH1F *)fttbar->Get("METptMu_C"); 
  TH1F	*IsoMu_ttbar_C	  = (TH1F *)fttbar->Get("IsoMu_C"); 
  TH1F	*mjjMu_ttbar_Cp	  = (TH1F *)fttbar->Get("mjjMu_Cp");
  TH1F	*METptEle_ttbar_C = (TH1F *)fttbar->Get("METptEle_C"); 
  TH1F	*IsoEle_ttbar_C	  = (TH1F *)fttbar->Get("IsoEle_C"); 
  TH1F	*mjjEle_ttbar_Cp	  = (TH1F *)fttbar->Get("mjjEle_Cp");
  //D
  TH1F	*METptMu_ttbar_D  = (TH1F *)fttbar->Get("METptMu_D"); 
  TH1F	*IsoMu_ttbar_D	  = (TH1F *)fttbar->Get("IsoMu_D"); 
  TH1F	*mjjMu_ttbar_Dp	  = (TH1F *)fttbar->Get("mjjMu_Dp");
  TH1F	*METptEle_ttbar_D = (TH1F *)fttbar->Get("METptEle_D"); 
  TH1F	*IsoEle_ttbar_D	  = (TH1F *)fttbar->Get("IsoEle_D"); 
  TH1F	*mjjEle_ttbar_Dp	  = (TH1F *)fttbar->Get("mjjEle_Dp");

  //////////////////////// data //////////////////////
  //A
  TH1F	*METptMu_data_A  = (TH1F *)fdata->Get("METptMu_A"); 
  TH1F	*IsoMu_data_A	  = (TH1F *)fdata->Get("IsoMu_A"); 
  TH1F	*mjjMu_data_Ap	  = (TH1F *)fdata->Get("mjjMu_Ap");
  TH1F	*METptEle_data_A = (TH1F *)fdata->Get("METptEle_A"); 
  TH1F	*IsoEle_data_A	  = (TH1F *)fdata->Get("IsoEle_A"); 
  TH1F	*mjjEle_data_Ap	  = (TH1F *)fdata->Get("mjjEle_Ap");
  //B
  TH1F	*METptMu_data_B  = (TH1F *)fdata->Get("METptMu_B"); 
  TH1F	*IsoMu_data_B	  = (TH1F *)fdata->Get("IsoMu_B"); 
  TH1F	*mjjMu_data_Bp	  = (TH1F *)fdata->Get("mjjMu_Bp");
  TH1F	*METptEle_data_B = (TH1F *)fdata->Get("METptEle_B"); 
  TH1F	*IsoEle_data_B	  = (TH1F *)fdata->Get("IsoEle_B"); 
  TH1F	*mjjEle_data_Bp	  = (TH1F *)fdata->Get("mjjEle_Bp");
  //C
  TH1F	*METptMu_data_C  = (TH1F *)fdata->Get("METptMu_C"); 
  TH1F	*IsoMu_data_C	  = (TH1F *)fdata->Get("IsoMu_C"); 
  TH1F	*mjjMu_data_Cp	  = (TH1F *)fdata->Get("mjjMu_Cp");
  TH1F	*METptEle_data_C = (TH1F *)fdata->Get("METptEle_C"); 
  TH1F	*IsoEle_data_C	  = (TH1F *)fdata->Get("IsoEle_C"); 
  TH1F	*mjjEle_data_Cp	  = (TH1F *)fdata->Get("mjjEle_Cp");
  //D
  TH1F	*METptMu_data_D  = (TH1F *)fdata->Get("METptMu_D"); 
  TH1F	*IsoMu_data_D	  = (TH1F *)fdata->Get("IsoMu_D"); 
  TH1F	*mjjMu_data_Dp	  = (TH1F *)fdata->Get("mjjMu_Dp");
  TH1F	*METptEle_data_D = (TH1F *)fdata->Get("METptEle_D"); 
  TH1F	*IsoEle_data_D	  = (TH1F *)fdata->Get("IsoEle_D"); 
  TH1F	*mjjEle_data_Dp	  = (TH1F *)fdata->Get("mjjEle_Dp");

  /////////////////// mcqcd /////////////////////////////
  //A
  TH1F	*METptMu_mcqcd_A  = (TH1F *)fmcqcd->Get("METptMu_A"); 
  TH1F	*IsoMu_mcqcd_A	  = (TH1F *)fmcqcd->Get("IsoMu_A"); 
  TH1F	*mjjMu_mcqcd_Ap	  = (TH1F *)fmcqcd->Get("mjjMu_Ap");
  TH1F	*METptEle_mcqcd_A = (TH1F *)fmcqcd->Get("METptEle_A"); 
  TH1F	*IsoEle_mcqcd_A	  = (TH1F *)fmcqcd->Get("IsoEle_A"); 
  TH1F	*mjjEle_mcqcd_Ap	  = (TH1F *)fmcqcd->Get("mjjEle_Ap");
  //B
  TH1F	*METptMu_mcqcd_B  = (TH1F *)fmcqcd->Get("METptMu_B"); 
  TH1F	*IsoMu_mcqcd_B	  = (TH1F *)fmcqcd->Get("IsoMu_B"); 
  TH1F	*mjjMu_mcqcd_Bp	  = (TH1F *)fmcqcd->Get("mjjMu_Bp");
  TH1F	*METptEle_mcqcd_B = (TH1F *)fmcqcd->Get("METptEle_B"); 
  TH1F	*IsoEle_mcqcd_B	  = (TH1F *)fmcqcd->Get("IsoEle_B"); 
  TH1F	*mjjEle_mcqcd_Bp	  = (TH1F *)fmcqcd->Get("mjjEle_Bp");
  //C
  TH1F	*METptMu_mcqcd_C  = (TH1F *)fmcqcd->Get("METptMu_C"); 
  TH1F	*IsoMu_mcqcd_C	  = (TH1F *)fmcqcd->Get("IsoMu_C"); 
  TH1F	*mjjMu_mcqcd_Cp	  = (TH1F *)fmcqcd->Get("mjjMu_Cp");
  TH1F	*METptEle_mcqcd_C = (TH1F *)fmcqcd->Get("METptEle_C"); 
  TH1F	*IsoEle_mcqcd_C	  = (TH1F *)fmcqcd->Get("IsoEle_C"); 
  TH1F	*mjjEle_mcqcd_Cp	  = (TH1F *)fmcqcd->Get("mjjEle_Cp");
  //D
  TH1F	*METptMu_mcqcd_D  = (TH1F *)fmcqcd->Get("METptMu_D"); 
  TH1F	*IsoMu_mcqcd_D	  = (TH1F *)fmcqcd->Get("IsoMu_D"); 
  TH1F	*mjjMu_mcqcd_Dp	  = (TH1F *)fmcqcd->Get("mjjMu_Dp");
  TH1F	*METptEle_mcqcd_D = (TH1F *)fmcqcd->Get("METptEle_D"); 
  TH1F	*IsoEle_mcqcd_D	  = (TH1F *)fmcqcd->Get("IsoEle_D"); 
  TH1F	*mjjEle_mcqcd_Dp	  = (TH1F *)fmcqcd->Get("mjjEle_Dp");

  ///////////////// stop /////////////////////
  //A
  TH1F	*METptMu_stop_A  = (TH1F *)fstop->Get("METptMu_A"); 
  TH1F	*IsoMu_stop_A	  = (TH1F *)fstop->Get("IsoMu_A"); 
  TH1F	*mjjMu_stop_Ap	  = (TH1F *)fstop->Get("mjjMu_Ap");
  TH1F	*METptEle_stop_A = (TH1F *)fstop->Get("METptEle_A"); 
  TH1F	*IsoEle_stop_A	  = (TH1F *)fstop->Get("IsoEle_A"); 
  TH1F	*mjjEle_stop_Ap	  = (TH1F *)fstop->Get("mjjEle_Ap");
  //B
  TH1F	*METptMu_stop_B  = (TH1F *)fstop->Get("METptMu_B"); 
  TH1F	*IsoMu_stop_B	  = (TH1F *)fstop->Get("IsoMu_B"); 
  TH1F	*mjjMu_stop_Bp	  = (TH1F *)fstop->Get("mjjMu_Bp");
  TH1F	*METptEle_stop_B = (TH1F *)fstop->Get("METptEle_B"); 
  TH1F	*IsoEle_stop_B	  = (TH1F *)fstop->Get("IsoEle_B"); 
  TH1F	*mjjEle_stop_Bp	  = (TH1F *)fstop->Get("mjjEle_Bp");
  //C
  TH1F	*METptMu_stop_C  = (TH1F *)fstop->Get("METptMu_C"); 
  TH1F	*IsoMu_stop_C	  = (TH1F *)fstop->Get("IsoMu_C"); 
  TH1F	*mjjMu_stop_Cp	  = (TH1F *)fstop->Get("mjjMu_Cp");
  TH1F	*METptEle_stop_C = (TH1F *)fstop->Get("METptEle_C"); 
  TH1F	*IsoEle_stop_C	  = (TH1F *)fstop->Get("IsoEle_C"); 
  TH1F	*mjjEle_stop_Cp	  = (TH1F *)fstop->Get("mjjEle_Cp");
  //D
  TH1F	*METptMu_stop_D  = (TH1F *)fstop->Get("METptMu_D"); 
  TH1F	*IsoMu_stop_D	  = (TH1F *)fstop->Get("IsoMu_D"); 
  TH1F	*mjjMu_stop_Dp	  = (TH1F *)fstop->Get("mjjMu_Dp");
  TH1F	*METptEle_stop_D = (TH1F *)fstop->Get("METptEle_D"); 
  TH1F	*IsoEle_stop_D	  = (TH1F *)fstop->Get("IsoEle_D"); 
  TH1F	*mjjEle_stop_Dp	  = (TH1F *)fstop->Get("mjjEle_Dp");

  ///////////////// wjets /////////////////////
  //A
  TH1F	*METptMu_wjets_A  = (TH1F *)fwjets->Get("METptMu_A"); 
  TH1F	*IsoMu_wjets_A	  = (TH1F *)fwjets->Get("IsoMu_A"); 
  TH1F	*mjjMu_wjets_Ap	  = (TH1F *)fwjets->Get("mjjMu_Ap");
  TH1F	*METptEle_wjets_A = (TH1F *)fwjets->Get("METptEle_A"); 
  TH1F	*IsoEle_wjets_A	  = (TH1F *)fwjets->Get("IsoEle_A"); 
  TH1F	*mjjEle_wjets_Ap	  = (TH1F *)fwjets->Get("mjjEle_Ap");
  //B
  TH1F	*METptMu_wjets_B  = (TH1F *)fwjets->Get("METptMu_B"); 
  TH1F	*IsoMu_wjets_B	  = (TH1F *)fwjets->Get("IsoMu_B"); 
  TH1F	*mjjMu_wjets_Bp	  = (TH1F *)fwjets->Get("mjjMu_Bp");
  TH1F	*METptEle_wjets_B = (TH1F *)fwjets->Get("METptEle_B"); 
  TH1F	*IsoEle_wjets_B	  = (TH1F *)fwjets->Get("IsoEle_B"); 
  TH1F	*mjjEle_wjets_Bp	  = (TH1F *)fwjets->Get("mjjEle_Bp");
  //C
  TH1F	*METptMu_wjets_C  = (TH1F *)fwjets->Get("METptMu_C"); 
  TH1F	*IsoMu_wjets_C	  = (TH1F *)fwjets->Get("IsoMu_C"); 
  TH1F	*mjjMu_wjets_Cp	  = (TH1F *)fwjets->Get("mjjMu_Cp");
  TH1F	*METptEle_wjets_C = (TH1F *)fwjets->Get("METptEle_C"); 
  TH1F	*IsoEle_wjets_C	  = (TH1F *)fwjets->Get("IsoEle_C"); 
  TH1F	*mjjEle_wjets_Cp	  = (TH1F *)fwjets->Get("mjjEle_Cp");
  //D
  TH1F	*METptMu_wjets_D  = (TH1F *)fwjets->Get("METptMu_D"); 
  TH1F	*IsoMu_wjets_D	  = (TH1F *)fwjets->Get("IsoMu_D"); 
  TH1F	*mjjMu_wjets_Dp	  = (TH1F *)fwjets->Get("mjjMu_Dp");
  TH1F	*METptEle_wjets_D = (TH1F *)fwjets->Get("METptEle_D"); 
  TH1F	*IsoEle_wjets_D	  = (TH1F *)fwjets->Get("IsoEle_D"); 
  TH1F	*mjjEle_wjets_Dp	  = (TH1F *)fwjets->Get("mjjEle_Dp");

  ///////////////// dyjets /////////////////////
  //A
  TH1F	*METptMu_dyjets_A  = (TH1F *)fdyjets->Get("METptMu_A"); 
  TH1F	*IsoMu_dyjets_A	  = (TH1F *)fdyjets->Get("IsoMu_A"); 
  TH1F	*mjjMu_dyjets_Ap	  = (TH1F *)fdyjets->Get("mjjMu_Ap");
  TH1F	*METptEle_dyjets_A = (TH1F *)fdyjets->Get("METptEle_A"); 
  TH1F	*IsoEle_dyjets_A	  = (TH1F *)fdyjets->Get("IsoEle_A"); 
  TH1F	*mjjEle_dyjets_Ap	  = (TH1F *)fdyjets->Get("mjjEle_Ap");
  //B
  TH1F	*METptMu_dyjets_B  = (TH1F *)fdyjets->Get("METptMu_B"); 
  TH1F	*IsoMu_dyjets_B	  = (TH1F *)fdyjets->Get("IsoMu_B"); 
  TH1F	*mjjMu_dyjets_Bp	  = (TH1F *)fdyjets->Get("mjjMu_Bp");
  TH1F	*METptEle_dyjets_B = (TH1F *)fdyjets->Get("METptEle_B"); 
  TH1F	*IsoEle_dyjets_B	  = (TH1F *)fdyjets->Get("IsoEle_B"); 
  TH1F	*mjjEle_dyjets_Bp	  = (TH1F *)fdyjets->Get("mjjEle_Bp");
  //C
  TH1F	*METptMu_dyjets_C  = (TH1F *)fdyjets->Get("METptMu_C"); 
  TH1F	*IsoMu_dyjets_C	  = (TH1F *)fdyjets->Get("IsoMu_C"); 
  TH1F	*mjjMu_dyjets_Cp	  = (TH1F *)fdyjets->Get("mjjMu_Cp");
  TH1F	*METptEle_dyjets_C = (TH1F *)fdyjets->Get("METptEle_C"); 
  TH1F	*IsoEle_dyjets_C	  = (TH1F *)fdyjets->Get("IsoEle_C"); 
  TH1F	*mjjEle_dyjets_Cp	  = (TH1F *)fdyjets->Get("mjjEle_Cp");
  //D
  TH1F	*METptMu_dyjets_D  = (TH1F *)fdyjets->Get("METptMu_D"); 
  TH1F	*IsoMu_dyjets_D	  = (TH1F *)fdyjets->Get("IsoMu_D"); 
  TH1F	*mjjMu_dyjets_Dp	  = (TH1F *)fdyjets->Get("mjjMu_Dp");
  TH1F	*METptEle_dyjets_D = (TH1F *)fdyjets->Get("METptEle_D"); 
  TH1F	*IsoEle_dyjets_D	  = (TH1F *)fdyjets->Get("IsoEle_D"); 
  TH1F	*mjjEle_dyjets_Dp	  = (TH1F *)fdyjets->Get("mjjEle_Dp");

  ///////////////// vv /////////////////////
  //A
  TH1F	*METptMu_vv_A  = (TH1F *)fvv->Get("METptMu_A"); 
  TH1F	*IsoMu_vv_A	  = (TH1F *)fvv->Get("IsoMu_A"); 
  TH1F	*mjjMu_vv_Ap	  = (TH1F *)fvv->Get("mjjMu_Ap");
  TH1F	*METptEle_vv_A = (TH1F *)fvv->Get("METptEle_A"); 
  TH1F	*IsoEle_vv_A	  = (TH1F *)fvv->Get("IsoEle_A"); 
  TH1F	*mjjEle_vv_Ap	  = (TH1F *)fvv->Get("mjjEle_Ap");
  //B
  TH1F	*METptMu_vv_B  = (TH1F *)fvv->Get("METptMu_B"); 
  TH1F	*IsoMu_vv_B	  = (TH1F *)fvv->Get("IsoMu_B"); 
  TH1F	*mjjMu_vv_Bp	  = (TH1F *)fvv->Get("mjjMu_Bp");
  TH1F	*METptEle_vv_B = (TH1F *)fvv->Get("METptEle_B"); 
  TH1F	*IsoEle_vv_B	  = (TH1F *)fvv->Get("IsoEle_B"); 
  TH1F	*mjjEle_vv_Bp	  = (TH1F *)fvv->Get("mjjEle_Bp");
  //C
  TH1F	*METptMu_vv_C  = (TH1F *)fvv->Get("METptMu_C"); 
  TH1F	*IsoMu_vv_C	  = (TH1F *)fvv->Get("IsoMu_C"); 
  TH1F	*mjjMu_vv_Cp	  = (TH1F *)fvv->Get("mjjMu_Cp");
  TH1F	*METptEle_vv_C = (TH1F *)fvv->Get("METptEle_C"); 
  TH1F	*IsoEle_vv_C	  = (TH1F *)fvv->Get("IsoEle_C"); 
  TH1F	*mjjEle_vv_Cp	  = (TH1F *)fvv->Get("mjjEle_Cp");
  //D
  TH1F	*METptMu_vv_D  = (TH1F *)fvv->Get("METptMu_D"); 
  TH1F	*IsoMu_vv_D	  = (TH1F *)fvv->Get("IsoMu_D"); 
  TH1F	*mjjMu_vv_Dp	  = (TH1F *)fvv->Get("mjjMu_Dp");
  TH1F	*METptEle_vv_D = (TH1F *)fvv->Get("METptEle_D"); 
  TH1F	*IsoEle_vv_D	  = (TH1F *)fvv->Get("IsoEle_D"); 
  TH1F	*mjjEle_vv_Dp	  = (TH1F *)fvv->Get("mjjEle_Dp");

  /////////////////////////////////////////////////////////

  if(ismu){
    ////////////////////// ttbar //////////////////////////////////////////
    TH1F *Isomu_ttbar_AB = (TH1F *)IsoMu_ttbar_A->Clone("Isomu_ttbar_AB"); Isomu_ttbar_AB->Add(IsoMu_ttbar_B);
    TH1F *Isomu_ttbar_CD = (TH1F *)IsoMu_ttbar_D->Clone("Isomu_ttbar_CD"); Isomu_ttbar_CD->Add(IsoMu_ttbar_C);
    Isomu_ttbar_AB->SetTitle(Form("%s (ttbar)",cut_title.c_str()));
    Isomu_ttbar_CD->SetTitle(Form("%s (ttbar)",cut_title.c_str()));
  
    int rebin = 1;
    Isomu_ttbar_AB->Rebin(rebin);
    Isomu_ttbar_CD->Rebin(rebin);

    float maxX = 0.3;
    Isomu_ttbar_AB->GetXaxis()->SetRangeUser(0.0, maxX);
    Isomu_ttbar_CD->GetXaxis()->SetRangeUser(0.0, maxX);
    // Isomu_ttbar_AB->GetXaxis()->SetRangeUser(0.0, 0.3);
    // Isomu_ttbar_CD->GetXaxis()->SetRangeUser(0.0, 0.3);
    Isomu_ttbar_CD->SetLineColor(kRed);
    Isomu_ttbar_AB->Scale(1./Isomu_ttbar_AB->Integral());
    Isomu_ttbar_CD->Scale(1./Isomu_ttbar_CD->Integral());
    // TCanvas *c1 = new TCanvas("c1","c1");
    // c1->SetLogy();
    // Isomu_ttbar_AB->Draw();
    // Isomu_ttbar_CD->Draw("sames");
    // Isomu_ttbar_AB->GetXaxis()->SetTitle("I_{rel}^{#mu}");
    // Isomu_ttbar_AB->GetYaxis()->SetTitle("Arb.");

    float kappa = (IsoMu_ttbar_A->Integral()/IsoMu_ttbar_B->Integral())/(IsoMu_ttbar_D->Integral()/IsoMu_ttbar_C->Integral());
    PlotRatio(Isomu_ttbar_CD, Isomu_ttbar_AB, "c2", "Iso^{#mu}", "#frac{CD}{AB}", kappa, IsoMu_ttbar_A->Integral(),1);
    TCanvas *c2 = (TCanvas *)gROOT->GetListOfCanvases()->FindObject("c2");
    string outputpdf = Form("figs/Week_Work_Report/2023-06-02/Kappa/%d/hist_%s_%s.pdf",year,case_n.c_str(),IsoMu_ttbar_A->GetName());
    c2->SaveAs(outputpdf.c_str());

    ////////////////////// ttbar //////////////////////////////////////////
  

    ////////////////////// DD QCD  //////////////////////////////////////////
    TH1F *Isomu_bkg_A = (TH1F *)IsoMu_ttbar_A->Clone("Isomu_bkg_A");
    Isomu_bkg_A->Add(IsoMu_stop_A);
    Isomu_bkg_A->Add(IsoMu_wjets_A);
    Isomu_bkg_A->Add(IsoMu_dyjets_A);
    Isomu_bkg_A->Add(IsoMu_vv_A);
    TH1F *Isomu_bkg_B = (TH1F *)IsoMu_ttbar_B->Clone("Isomu_bkg_B");
    Isomu_bkg_B->Add(IsoMu_stop_B);
    Isomu_bkg_B->Add(IsoMu_wjets_B);
    Isomu_bkg_B->Add(IsoMu_dyjets_B);
    Isomu_bkg_B->Add(IsoMu_vv_B);
    TH1F *Isomu_bkg_C = (TH1F *)IsoMu_ttbar_C->Clone("Isomu_bkg_C");
    Isomu_bkg_C->Add(IsoMu_stop_C);
    Isomu_bkg_C->Add(IsoMu_wjets_C);
    Isomu_bkg_C->Add(IsoMu_dyjets_C);
    Isomu_bkg_C->Add(IsoMu_vv_C);
    TH1F *Isomu_bkg_D = (TH1F *)IsoMu_ttbar_D->Clone("Isomu_bkg_D");
    Isomu_bkg_D->Add(IsoMu_stop_D);
    Isomu_bkg_D->Add(IsoMu_wjets_D);
    Isomu_bkg_D->Add(IsoMu_dyjets_D);
    Isomu_bkg_D->Add(IsoMu_vv_D);
    
    TH1F *Isomu_QCD_A = (TH1F *)IsoMu_data_A->Clone("Isomu_QCD_A");
    Isomu_QCD_A->Add(Isomu_bkg_A, -1);
    TH1F *Isomu_QCD_B = (TH1F *)IsoMu_data_B->Clone("Isomu_QCD_B");
    Isomu_QCD_B->Add(Isomu_bkg_B, -1);
    TH1F *Isomu_QCD_C = (TH1F *)IsoMu_data_C->Clone("Isomu_QCD_C");
    Isomu_QCD_C->Add(Isomu_bkg_C, -1);
    TH1F *Isomu_QCD_D = (TH1F *)IsoMu_data_D->Clone("Isomu_QCD_D");
    Isomu_QCD_D->Add(Isomu_bkg_D, -1);
    
    makeHistoPositive(Isomu_QCD_A,0);
    makeHistoPositive(Isomu_QCD_B,0);
    makeHistoPositive(Isomu_QCD_C,0);
    makeHistoPositive(Isomu_QCD_D,0);
    
    TH1F *Isomu_bkg_AB = (TH1F *)IsoMu_ttbar_A->Clone("Isomu_bkg_AB");
    Isomu_bkg_AB->Add(IsoMu_stop_A);
    Isomu_bkg_AB->Add(IsoMu_wjets_A);
    Isomu_bkg_AB->Add(IsoMu_dyjets_A);
    Isomu_bkg_AB->Add(IsoMu_vv_A);
    Isomu_bkg_AB->Add(IsoMu_ttbar_B);
    Isomu_bkg_AB->Add(IsoMu_stop_B);
    Isomu_bkg_AB->Add(IsoMu_wjets_B);
    Isomu_bkg_AB->Add(IsoMu_dyjets_B);
    Isomu_bkg_AB->Add(IsoMu_vv_B);

    TH1F *Isomu_bkg_CD = (TH1F *)IsoMu_ttbar_D->Clone("Isomu_bkg_CD");
    Isomu_bkg_CD->Add(IsoMu_stop_D);
    Isomu_bkg_CD->Add(IsoMu_wjets_D);
    Isomu_bkg_CD->Add(IsoMu_dyjets_D);
    Isomu_bkg_CD->Add(IsoMu_vv_D);
    Isomu_bkg_CD->Add(IsoMu_ttbar_C);
    Isomu_bkg_CD->Add(IsoMu_stop_C);
    Isomu_bkg_CD->Add(IsoMu_wjets_C);
    Isomu_bkg_CD->Add(IsoMu_dyjets_C);
    Isomu_bkg_CD->Add(IsoMu_vv_C);
  
    TH1F *Isomu_QCD_AB = (TH1F *)IsoMu_data_A->Clone("Isomu_QCD_AB");
    Isomu_QCD_AB->Add(IsoMu_data_B);
    Isomu_QCD_AB->Add(Isomu_bkg_AB, -1);

    TH1F *Isomu_QCD_CD = (TH1F *)IsoMu_data_D->Clone("Isomu_QCD_CD");
    Isomu_QCD_CD->Add(IsoMu_data_C);
    Isomu_QCD_CD->Add(Isomu_bkg_CD, -1);

    makeHistoPositive(Isomu_QCD_AB,0);
    makeHistoPositive(Isomu_QCD_CD,0);

    Isomu_bkg_AB->SetTitle(Form("%s (bkg)",cut_title.c_str()));
    Isomu_bkg_CD->SetTitle(Form("%s (bkg)",cut_title.c_str()));
    Isomu_QCD_AB->SetTitle(Form("%s (QCD)",cut_title.c_str()));
    Isomu_QCD_CD->SetTitle(Form("%s (QCD)",cut_title.c_str()));

    // Isomu_bkg_AB->Rebin(rebin);
    // Isomu_bkg_CD->Rebin(rebin);

    Isomu_bkg_AB->GetXaxis()->SetRangeUser(0.0, maxX);
    Isomu_bkg_CD->GetXaxis()->SetRangeUser(0.0, maxX);
    Isomu_bkg_CD->SetLineColor(kRed);
    Isomu_bkg_AB->Scale(1./Isomu_bkg_AB->Integral());
    Isomu_bkg_CD->Scale(1./Isomu_bkg_CD->Integral());

    kappa = (Isomu_bkg_A->Integral()/Isomu_bkg_B->Integral())/(Isomu_bkg_D->Integral()/Isomu_bkg_C->Integral());
    //PlotRatio(Isomu_bkg_CD, Isomu_bkg_AB, "c4", "Iso^{#mu}", "#frac{CD}{AB}", kappa,Isomu_bkg_A->Integral());

    // Isomu_QCD_AB->Rebin(rebin);
    // Isomu_QCD_CD->Rebin(rebin);

    Isomu_QCD_AB->GetXaxis()->SetRangeUser(0.0, maxX);
    Isomu_QCD_CD->GetXaxis()->SetRangeUser(0.0, maxX);
    Isomu_QCD_CD->SetLineColor(kRed);
    Isomu_QCD_AB->Scale(1./Isomu_QCD_AB->Integral());
    Isomu_QCD_CD->Scale(1./Isomu_QCD_CD->Integral());

    kappa = (Isomu_QCD_A->Integral()/Isomu_QCD_B->Integral())/(Isomu_QCD_D->Integral()/Isomu_QCD_C->Integral());
    PlotRatio(Isomu_QCD_CD, Isomu_QCD_AB, "c5", "Iso^{#mu}", "#frac{CD}{AB}", kappa,Isomu_QCD_A->Integral(),0);
    TCanvas *c5 = (TCanvas *)gROOT->GetListOfCanvases()->FindObject("c5");
    c5->SaveAs("output.pdf");
    string outputpdf1 = Form("figs/Week_Work_Report/2023-06-02/Kappa/%d/hist_%s_%s.pdf",year,case_n.c_str(),Isomu_QCD_A->GetName());
    c5->SaveAs(outputpdf1.c_str());
  
    ////////////////////// DD qcd //////////////////////////////////////////

    ////////////////////// ttbar //////////////////////////////////////////
    TH1F *METptmu_ttbar_AD = (TH1F *)METptMu_ttbar_A->Clone("METptmu_ttbar_AD"); METptmu_ttbar_AD->Add(METptMu_ttbar_D);
    TH1F *METptmu_ttbar_BC = (TH1F *)METptMu_ttbar_B->Clone("METptmu_ttbar_BC"); METptmu_ttbar_BC->Add(METptMu_ttbar_C);
    METptmu_ttbar_AD->SetTitle(Form("%s (ttbar)",cut_title.c_str()));
    METptmu_ttbar_BC->SetTitle(Form("%s (ttbar)",cut_title.c_str()));
  
    rebin = 5;
    METptmu_ttbar_AD->Rebin(rebin);
    METptmu_ttbar_BC->Rebin(rebin);

    maxX = 200.;
    METptmu_ttbar_AD->GetXaxis()->SetRangeUser(0.0, maxX);
    METptmu_ttbar_BC->GetXaxis()->SetRangeUser(0.0, maxX);
    // METptmu_ttbar_AD->GetXaxis()->SetRangeUser(0.0, 0.3);
    // METptmu_ttbar_BC->GetXaxis()->SetRangeUser(0.0, 0.3);
    METptmu_ttbar_BC->SetLineColor(kRed);
    METptmu_ttbar_AD->Scale(1./METptmu_ttbar_AD->Integral());
    METptmu_ttbar_BC->Scale(1./METptmu_ttbar_BC->Integral());
    // TCanvas *c1 = new TCanvas("c1","c1");
    // c1->SetLogy();
    // METptmu_ttbar_AD->Draw();
    // METptmu_ttbar_BC->Draw("sames");
    // METptmu_ttbar_AD->GetXaxis()->SetTitle("I_{rel}^{#mu}");
    // METptmu_ttbar_AD->GetYaxis()->SetTitle("Arb.");

    kappa = (METptMu_ttbar_A->Integral()/METptMu_ttbar_B->Integral())/(METptMu_ttbar_D->Integral()/METptMu_ttbar_C->Integral());
    PlotRatio(METptmu_ttbar_BC, METptmu_ttbar_AD, "c6", "MET (#mu + jets)", "#frac{BC}{AD}", kappa, METptMu_ttbar_A->Integral(),1);
    TCanvas *c6 = (TCanvas *)gROOT->GetListOfCanvases()->FindObject("c6");
    outputpdf = Form("figs/Week_Work_Report/2023-06-02/Kappa/%d/hist_%s_%s.pdf",year,case_n.c_str(),METptMu_ttbar_A->GetName());
    c6->SaveAs(outputpdf.c_str());
    //c6->SaveAs("output.pdf");
    ////////////////////// ttbar //////////////////////////////////////////
  
    ////////////////////// DD QCD  //////////////////////////////////////////
    TH1F *METptmu_bkg_A = (TH1F *)METptMu_ttbar_A->Clone("METptmu_bkg_A");
    METptmu_bkg_A->Add(METptMu_stop_A);
    METptmu_bkg_A->Add(METptMu_wjets_A);
    METptmu_bkg_A->Add(METptMu_dyjets_A);
    METptmu_bkg_A->Add(METptMu_vv_A);
    TH1F *METptmu_bkg_B = (TH1F *)METptMu_ttbar_B->Clone("METptmu_bkg_B");
    METptmu_bkg_B->Add(METptMu_stop_B);
    METptmu_bkg_B->Add(METptMu_wjets_B);
    METptmu_bkg_B->Add(METptMu_dyjets_B);
    METptmu_bkg_B->Add(METptMu_vv_B);
    TH1F *METptmu_bkg_C = (TH1F *)METptMu_ttbar_C->Clone("METptmu_bkg_C");
    METptmu_bkg_C->Add(METptMu_stop_C);
    METptmu_bkg_C->Add(METptMu_wjets_C);
    METptmu_bkg_C->Add(METptMu_dyjets_C);
    METptmu_bkg_C->Add(METptMu_vv_C);
    TH1F *METptmu_bkg_D = (TH1F *)METptMu_ttbar_D->Clone("METptmu_bkg_D");
    METptmu_bkg_D->Add(METptMu_stop_D);
    METptmu_bkg_D->Add(METptMu_wjets_D);
    METptmu_bkg_D->Add(METptMu_dyjets_D);
    METptmu_bkg_D->Add(METptMu_vv_D);

    TH1F *METptmu_QCD_A = (TH1F *)METptMu_data_A->Clone("METptmu_QCD_A");
    METptmu_QCD_A->Add(METptmu_bkg_A, -1);
    TH1F *METptmu_QCD_B = (TH1F *)METptMu_data_B->Clone("METptmu_QCD_B");
    METptmu_QCD_B->Add(METptmu_bkg_B, -1);
    TH1F *METptmu_QCD_C = (TH1F *)METptMu_data_C->Clone("METptmu_QCD_C");
    METptmu_QCD_C->Add(METptmu_bkg_C, -1);
    TH1F *METptmu_QCD_D = (TH1F *)METptMu_data_D->Clone("METptmu_QCD_D");
    METptmu_QCD_D->Add(METptmu_bkg_D, -1);
    
    makeHistoPositive(METptmu_QCD_A,0);
    makeHistoPositive(METptmu_QCD_B,0);
    makeHistoPositive(METptmu_QCD_C,0);
    makeHistoPositive(METptmu_QCD_D,0);
    
    TH1F *METptmu_bkg_AD = (TH1F *)METptMu_ttbar_A->Clone("METptmu_bkg_AD");
    METptmu_bkg_AD->Add(METptMu_stop_A);
    METptmu_bkg_AD->Add(METptMu_wjets_A);
    METptmu_bkg_AD->Add(METptMu_dyjets_A);
    METptmu_bkg_AD->Add(METptMu_vv_A);
    METptmu_bkg_AD->Add(METptMu_ttbar_D);
    METptmu_bkg_AD->Add(METptMu_stop_D);
    METptmu_bkg_AD->Add(METptMu_wjets_D);
    METptmu_bkg_AD->Add(METptMu_dyjets_D);
    METptmu_bkg_AD->Add(METptMu_vv_D);

    TH1F *METptmu_bkg_BC = (TH1F *)METptMu_ttbar_B->Clone("METptmu_bkg_BC");
    METptmu_bkg_BC->Add(METptMu_stop_B);
    METptmu_bkg_BC->Add(METptMu_wjets_B);
    METptmu_bkg_BC->Add(METptMu_dyjets_B);
    METptmu_bkg_BC->Add(METptMu_vv_B);
    METptmu_bkg_BC->Add(METptMu_ttbar_C);
    METptmu_bkg_BC->Add(METptMu_stop_C);
    METptmu_bkg_BC->Add(METptMu_wjets_C);
    METptmu_bkg_BC->Add(METptMu_dyjets_C);
    METptmu_bkg_BC->Add(METptMu_vv_C);
  
    TH1F *METptmu_QCD_AD = (TH1F *)METptMu_data_A->Clone("METptmu_QCD_AD");
    METptmu_QCD_AD->Add(METptMu_data_D);
    METptmu_QCD_AD->Add(METptmu_bkg_AD, -1);

    TH1F *METptmu_QCD_BC = (TH1F *)METptMu_data_B->Clone("METptmu_QCD_BC");
    METptmu_QCD_BC->Add(METptMu_data_C);
    METptmu_QCD_BC->Add(METptmu_bkg_BC, -1);

    makeHistoPositive(METptmu_QCD_AD,0);
    makeHistoPositive(METptmu_QCD_BC,0);

    METptmu_bkg_AD->SetTitle(Form("%s (bkg)",cut_title.c_str()));
    METptmu_bkg_BC->SetTitle(Form("%s (bkg)",cut_title.c_str()));
    METptmu_QCD_AD->SetTitle(Form("%s (QCD)",cut_title.c_str()));
    METptmu_QCD_BC->SetTitle(Form("%s (QCD)",cut_title.c_str()));

    METptmu_bkg_AD->Rebin(rebin);
    METptmu_bkg_BC->Rebin(rebin);

    maxX = 100.;
    METptmu_bkg_AD->GetXaxis()->SetRangeUser(0.0, maxX);
    METptmu_bkg_BC->GetXaxis()->SetRangeUser(0.0, maxX);
    METptmu_bkg_BC->SetLineColor(kRed);
    METptmu_bkg_AD->Scale(1./METptmu_bkg_AD->Integral());
    METptmu_bkg_BC->Scale(1./METptmu_bkg_BC->Integral());

    kappa = (METptmu_bkg_A->Integral()/METptmu_bkg_B->Integral())/(METptmu_bkg_D->Integral()/METptmu_bkg_C->Integral());
    //PlotRatio(METptmu_bkg_BC, METptmu_bkg_AD, "c4",kappa,METptmu_bkg_A->Integral());

    METptmu_QCD_AD->Rebin(rebin);
    METptmu_QCD_BC->Rebin(rebin);

    METptmu_QCD_AD->GetXaxis()->SetRangeUser(0.0, maxX);
    METptmu_QCD_BC->GetXaxis()->SetRangeUser(0.0, maxX);
    METptmu_QCD_BC->SetLineColor(kRed);
    METptmu_QCD_AD->Scale(1./METptmu_QCD_AD->Integral());
    METptmu_QCD_BC->Scale(1./METptmu_QCD_BC->Integral());

    kappa = (METptmu_QCD_A->Integral()/METptmu_QCD_B->Integral())/(METptmu_QCD_D->Integral()/METptmu_QCD_C->Integral());
    PlotRatio(METptmu_QCD_BC, METptmu_QCD_AD, "c7", "MET (#mu + jets)", "#frac{BC}{AD}", kappa,METptmu_QCD_A->Integral(),0);
    TCanvas *c7 = (TCanvas *)gROOT->GetListOfCanvases()->FindObject("c7");
    c7->SaveAs("output.pdf");
    outputpdf1 = Form("figs/Week_Work_Report/2023-06-02/Kappa/%d/hist_%s_%s.pdf",year,case_n.c_str(),METptmu_QCD_A->GetName());
    c7->SaveAs(outputpdf1.c_str());
  
    ////////////////////// DD qcd //////////////////////////////////////////

    outputpdf1 = Form("output/kappaDD/QCD_DD_%s_mu_%d.root",case_n.c_str(),year);
    TFile *fout = new TFile(outputpdf1.c_str(),"recreate");
    Isomu_QCD_A->Write();     Isomu_QCD_B->Write();     Isomu_QCD_C->Write();     Isomu_QCD_D->Write();
    Isomu_QCD_AB->Write();    Isomu_QCD_CD->Write();
    METptmu_QCD_A->Write();   METptmu_QCD_B->Write();   METptmu_QCD_C->Write();   METptmu_QCD_D->Write();
    METptmu_QCD_AD->Write();  METptmu_QCD_BC->Write();
    fout->Close();
    delete fout;

  }else{
    
    ////////////////////// ttbar //////////////////////////////////////////
    TH1F *Isoele_ttbar_AB = (TH1F *)IsoEle_ttbar_A->Clone("Isoele_ttbar_AB"); Isoele_ttbar_AB->Add(IsoEle_ttbar_B);
    TH1F *Isoele_ttbar_CD = (TH1F *)IsoEle_ttbar_D->Clone("Isoele_ttbar_CD"); Isoele_ttbar_CD->Add(IsoEle_ttbar_C);
    Isoele_ttbar_AB->SetTitle(Form("%s (ttbar)",cut_title.c_str()));
    Isoele_ttbar_CD->SetTitle(Form("%s (ttbar)",cut_title.c_str()));
  
    int rebin = 1;
    Isoele_ttbar_AB->Rebin(rebin);
    Isoele_ttbar_CD->Rebin(rebin);

    float maxX = 0.3;
    Isoele_ttbar_AB->GetXaxis()->SetRangeUser(0.0, maxX);
    Isoele_ttbar_CD->GetXaxis()->SetRangeUser(0.0, maxX);
    // Isoele_ttbar_AB->GetXaxis()->SetRangeUser(0.0, 0.3);
    // Isoele_ttbar_CD->GetXaxis()->SetRangeUser(0.0, 0.3);
    Isoele_ttbar_CD->SetLineColor(kRed);
    Isoele_ttbar_AB->Scale(1./Isoele_ttbar_AB->Integral());
    Isoele_ttbar_CD->Scale(1./Isoele_ttbar_CD->Integral());
    // TCanvas *c1 = new TCanvas("c1","c1");
    // c1->SetLogy();
    // Isoele_ttbar_AB->Draw();
    // Isoele_ttbar_CD->Draw("sames");
    // Isoele_ttbar_AB->GetXaxis()->SetTitle("I_{rel}^{e }");
    // Isoele_ttbar_AB->GetYaxis()->SetTitle("Arb.");

    float kappa = (IsoEle_ttbar_A->Integral()/IsoEle_ttbar_B->Integral())/(IsoEle_ttbar_D->Integral()/IsoEle_ttbar_C->Integral());
    PlotRatio(Isoele_ttbar_CD, Isoele_ttbar_AB, "c2", "Iso^{e }", "#frac{CD}{AB}", kappa, IsoEle_ttbar_A->Integral(),1);
    TCanvas *c2 = (TCanvas *)gROOT->GetListOfCanvases()->FindObject("c2");
    string outputpdf = Form("figs/Week_Work_Report/2023-06-02/Kappa/%d/hist_%s_%s.pdf",year,case_n.c_str(),IsoEle_ttbar_A->GetName());
    c2->SaveAs(outputpdf.c_str());

    ////////////////////// ttbar //////////////////////////////////////////
  

    ////////////////////// DD QCD  //////////////////////////////////////////
    TH1F *Isoele_bkg_A = (TH1F *)IsoEle_ttbar_A->Clone("Isoele_bkg_A");
    Isoele_bkg_A->Add(IsoEle_stop_A);
    Isoele_bkg_A->Add(IsoEle_wjets_A);
    Isoele_bkg_A->Add(IsoEle_dyjets_A);
    Isoele_bkg_A->Add(IsoEle_vv_A);
    TH1F *Isoele_bkg_B = (TH1F *)IsoEle_ttbar_B->Clone("Isoele_bkg_B");
    Isoele_bkg_B->Add(IsoEle_stop_B);
    Isoele_bkg_B->Add(IsoEle_wjets_B);
    Isoele_bkg_B->Add(IsoEle_dyjets_B);
    Isoele_bkg_B->Add(IsoEle_vv_B);
    TH1F *Isoele_bkg_C = (TH1F *)IsoEle_ttbar_C->Clone("Isoele_bkg_C");
    Isoele_bkg_C->Add(IsoEle_stop_C);
    Isoele_bkg_C->Add(IsoEle_wjets_C);
    Isoele_bkg_C->Add(IsoEle_dyjets_C);
    Isoele_bkg_C->Add(IsoEle_vv_C);
    TH1F *Isoele_bkg_D = (TH1F *)IsoEle_ttbar_D->Clone("Isoele_bkg_D");
    Isoele_bkg_D->Add(IsoEle_stop_D);
    Isoele_bkg_D->Add(IsoEle_wjets_D);
    Isoele_bkg_D->Add(IsoEle_dyjets_D);
    Isoele_bkg_D->Add(IsoEle_vv_D);

    TH1F *Isoele_QCD_A = (TH1F *)IsoEle_data_A->Clone("Isoele_QCD_A");
    Isoele_QCD_A->Add(Isoele_bkg_A, -1);
    TH1F *Isoele_QCD_B = (TH1F *)IsoEle_data_B->Clone("Isoele_QCD_B");
    Isoele_QCD_B->Add(Isoele_bkg_B, -1);
    TH1F *Isoele_QCD_C = (TH1F *)IsoEle_data_C->Clone("Isoele_QCD_C");
    Isoele_QCD_C->Add(Isoele_bkg_C, -1);
    TH1F *Isoele_QCD_D = (TH1F *)IsoEle_data_D->Clone("Isoele_QCD_D");
    Isoele_QCD_D->Add(Isoele_bkg_D, -1);

    makeHistoPositive(Isoele_QCD_A,0);
    makeHistoPositive(Isoele_QCD_B,0);
    makeHistoPositive(Isoele_QCD_C,0);
    makeHistoPositive(Isoele_QCD_D,0);
    
    TH1F *Isoele_bkg_AB = (TH1F *)IsoEle_ttbar_A->Clone("Isoele_bkg_AB");
    Isoele_bkg_AB->Add(IsoEle_stop_A);
    Isoele_bkg_AB->Add(IsoEle_wjets_A);
    Isoele_bkg_AB->Add(IsoEle_dyjets_A);
    Isoele_bkg_AB->Add(IsoEle_vv_A);
    Isoele_bkg_AB->Add(IsoEle_ttbar_B);
    Isoele_bkg_AB->Add(IsoEle_stop_B);
    Isoele_bkg_AB->Add(IsoEle_wjets_B);
    Isoele_bkg_AB->Add(IsoEle_dyjets_B);
    Isoele_bkg_AB->Add(IsoEle_vv_B);

    TH1F *Isoele_bkg_CD = (TH1F *)IsoEle_ttbar_D->Clone("Isoele_bkg_CD");
    Isoele_bkg_CD->Add(IsoEle_stop_D);
    Isoele_bkg_CD->Add(IsoEle_wjets_D);
    Isoele_bkg_CD->Add(IsoEle_dyjets_D);
    Isoele_bkg_CD->Add(IsoEle_vv_D);
    Isoele_bkg_CD->Add(IsoEle_ttbar_C);
    Isoele_bkg_CD->Add(IsoEle_stop_C);
    Isoele_bkg_CD->Add(IsoEle_wjets_C);
    Isoele_bkg_CD->Add(IsoEle_dyjets_C);
    Isoele_bkg_CD->Add(IsoEle_vv_C);
  
    TH1F *Isoele_QCD_AB = (TH1F *)IsoEle_data_A->Clone("Isoele_QCD_AB");
    Isoele_QCD_AB->Add(IsoEle_data_B);
    Isoele_QCD_AB->Add(Isoele_bkg_AB, -1);

    TH1F *Isoele_QCD_CD = (TH1F *)IsoEle_data_D->Clone("Isoele_QCD_CD");
    Isoele_QCD_CD->Add(IsoEle_data_C);
    Isoele_QCD_CD->Add(Isoele_bkg_CD, -1);

    makeHistoPositive(Isoele_QCD_AB,0);
    makeHistoPositive(Isoele_QCD_CD,0);

    Isoele_bkg_AB->SetTitle(Form("%s (bkg)",cut_title.c_str()));
    Isoele_bkg_CD->SetTitle(Form("%s (bkg)",cut_title.c_str()));
    Isoele_QCD_AB->SetTitle(Form("%s (QCD)",cut_title.c_str()));
    Isoele_QCD_CD->SetTitle(Form("%s (QCD)",cut_title.c_str()));
    
    Isoele_bkg_AB->Rebin(rebin);
    Isoele_bkg_CD->Rebin(rebin);
    
    Isoele_bkg_AB->GetXaxis()->SetRangeUser(0.0, maxX);
    Isoele_bkg_CD->GetXaxis()->SetRangeUser(0.0, maxX);
    Isoele_bkg_CD->SetLineColor(kRed);
    Isoele_bkg_AB->Scale(1./Isoele_bkg_AB->Integral());
    Isoele_bkg_CD->Scale(1./Isoele_bkg_CD->Integral());

    kappa = (Isoele_bkg_A->Integral()/Isoele_bkg_B->Integral())/(Isoele_bkg_D->Integral()/Isoele_bkg_C->Integral());
    //PlotRatio(Isoele_bkg_CD, Isoele_bkg_AB, "c4", "Iso^{e }", "#frac{CD}{AB}", kappa,Isoele_bkg_A->Integral());

    Isoele_QCD_AB->Rebin(rebin);
    Isoele_QCD_CD->Rebin(rebin);

    Isoele_QCD_AB->GetXaxis()->SetRangeUser(0.0, maxX);
    Isoele_QCD_CD->GetXaxis()->SetRangeUser(0.0, maxX);
    Isoele_QCD_CD->SetLineColor(kRed);
    Isoele_QCD_AB->Scale(1./Isoele_QCD_AB->Integral());
    Isoele_QCD_CD->Scale(1./Isoele_QCD_CD->Integral());

    kappa = (Isoele_QCD_A->Integral()/Isoele_QCD_B->Integral())/(Isoele_QCD_D->Integral()/Isoele_QCD_C->Integral());
    PlotRatio(Isoele_QCD_CD, Isoele_QCD_AB, "c5", "Iso^{e }", "#frac{CD}{AB}", kappa,Isoele_QCD_A->Integral(),0);
    TCanvas *c5 = (TCanvas *)gROOT->GetListOfCanvases()->FindObject("c5");
    c5->SaveAs("output.pdf");
    string outputpdf1 = Form("figs/Week_Work_Report/2023-06-02/Kappa/%d/hist_%s_%s.pdf",year,case_n.c_str(),Isoele_QCD_A->GetName());
    c5->SaveAs(outputpdf1.c_str());
  
    ////////////////////// DD qcd //////////////////////////////////////////

    ////////////////////// ttbar //////////////////////////////////////////
    TH1F *METptele_ttbar_AD = (TH1F *)METptEle_ttbar_A->Clone("METptele_ttbar_AD"); METptele_ttbar_AD->Add(METptEle_ttbar_D);
    TH1F *METptele_ttbar_BC = (TH1F *)METptEle_ttbar_B->Clone("METptele_ttbar_BC"); METptele_ttbar_BC->Add(METptEle_ttbar_C);
    METptele_ttbar_AD->SetTitle(Form("%s (ttbar)",cut_title.c_str()));
    METptele_ttbar_BC->SetTitle(Form("%s (ttbar)",cut_title.c_str()));
  
    rebin = 5;
    METptele_ttbar_AD->Rebin(rebin);
    METptele_ttbar_BC->Rebin(rebin);

    maxX = 200.;
    METptele_ttbar_AD->GetXaxis()->SetRangeUser(0.0, maxX);
    METptele_ttbar_BC->GetXaxis()->SetRangeUser(0.0, maxX);
    // METptele_ttbar_AD->GetXaxis()->SetRangeUser(0.0, 0.3);
    // METptele_ttbar_BC->GetXaxis()->SetRangeUser(0.0, 0.3);
    METptele_ttbar_BC->SetLineColor(kRed);
    METptele_ttbar_AD->Scale(1./METptele_ttbar_AD->Integral());
    METptele_ttbar_BC->Scale(1./METptele_ttbar_BC->Integral());
    // TCanvas *c1 = new TCanvas("c1","c1");
    // c1->SetLogy();
    // METptele_ttbar_AD->Draw();
    // METptele_ttbar_BC->Draw("sames");
    // METptele_ttbar_AD->GetXaxis()->SetTitle("I_{rel}^{e }");
    // METptele_ttbar_AD->GetYaxis()->SetTitle("Arb.");

    kappa = (METptEle_ttbar_A->Integral()/METptEle_ttbar_B->Integral())/(METptEle_ttbar_D->Integral()/METptEle_ttbar_C->Integral());
    PlotRatio(METptele_ttbar_BC, METptele_ttbar_AD, "c6", "MET (e  + jets)", "#frac{BC}{AD}", kappa, METptEle_ttbar_A->Integral(),1);
    TCanvas *c6 = (TCanvas *)gROOT->GetListOfCanvases()->FindObject("c6");
    outputpdf = Form("figs/Week_Work_Report/2023-06-02/Kappa/%d/hist_%s_%s.pdf",year,case_n.c_str(),METptEle_ttbar_A->GetName());
    c6->SaveAs(outputpdf.c_str());
    //c6->SaveAs("output.pdf");
    ////////////////////// ttbar //////////////////////////////////////////
  
    ////////////////////// DD QCD  //////////////////////////////////////////
    TH1F *METptele_bkg_A = (TH1F *)METptEle_ttbar_A->Clone("METptele_bkg_A");
    METptele_bkg_A->Add(METptEle_stop_A);
    METptele_bkg_A->Add(METptEle_wjets_A);
    METptele_bkg_A->Add(METptEle_dyjets_A);
    METptele_bkg_A->Add(METptEle_vv_A);
    TH1F *METptele_bkg_B = (TH1F *)METptEle_ttbar_B->Clone("METptele_bkg_B");
    METptele_bkg_B->Add(METptEle_stop_B);
    METptele_bkg_B->Add(METptEle_wjets_B);
    METptele_bkg_B->Add(METptEle_dyjets_B);
    METptele_bkg_B->Add(METptEle_vv_B);
    TH1F *METptele_bkg_C = (TH1F *)METptEle_ttbar_C->Clone("METptele_bkg_C");
    METptele_bkg_C->Add(METptEle_stop_C);
    METptele_bkg_C->Add(METptEle_wjets_C);
    METptele_bkg_C->Add(METptEle_dyjets_C);
    METptele_bkg_C->Add(METptEle_vv_C);
    TH1F *METptele_bkg_D = (TH1F *)METptEle_ttbar_D->Clone("METptele_bkg_D");
    METptele_bkg_D->Add(METptEle_stop_D);
    METptele_bkg_D->Add(METptEle_wjets_D);
    METptele_bkg_D->Add(METptEle_dyjets_D);
    METptele_bkg_D->Add(METptEle_vv_D);

    TH1F *METptele_QCD_A = (TH1F *)METptEle_data_A->Clone("METptele_QCD_A");
    METptele_QCD_A->Add(METptele_bkg_A, -1);
    TH1F *METptele_QCD_B = (TH1F *)METptEle_data_B->Clone("METptele_QCD_B");
    METptele_QCD_B->Add(METptele_bkg_B, -1);
    TH1F *METptele_QCD_C = (TH1F *)METptEle_data_C->Clone("METptele_QCD_C");
    METptele_QCD_C->Add(METptele_bkg_C, -1);
    TH1F *METptele_QCD_D = (TH1F *)METptEle_data_D->Clone("METptele_QCD_D");
    METptele_QCD_D->Add(METptele_bkg_D, -1);

    makeHistoPositive(METptele_QCD_A,0);
    makeHistoPositive(METptele_QCD_B,0);
    makeHistoPositive(METptele_QCD_C,0);
    makeHistoPositive(METptele_QCD_D,0);

    TH1F *METptele_bkg_AD = (TH1F *)METptEle_ttbar_A->Clone("METptele_bkg_AD");
    METptele_bkg_AD->Add(METptEle_stop_A);
    METptele_bkg_AD->Add(METptEle_wjets_A);
    METptele_bkg_AD->Add(METptEle_dyjets_A);
    METptele_bkg_AD->Add(METptEle_vv_A);
    METptele_bkg_AD->Add(METptEle_ttbar_D);
    METptele_bkg_AD->Add(METptEle_stop_D);
    METptele_bkg_AD->Add(METptEle_wjets_D);
    METptele_bkg_AD->Add(METptEle_dyjets_D);
    METptele_bkg_AD->Add(METptEle_vv_D);

    TH1F *METptele_bkg_BC = (TH1F *)METptEle_ttbar_B->Clone("METptele_bkg_BC");
    METptele_bkg_BC->Add(METptEle_stop_B);
    METptele_bkg_BC->Add(METptEle_wjets_B);
    METptele_bkg_BC->Add(METptEle_dyjets_B);
    METptele_bkg_BC->Add(METptEle_vv_B);
    METptele_bkg_BC->Add(METptEle_ttbar_C);
    METptele_bkg_BC->Add(METptEle_stop_C);
    METptele_bkg_BC->Add(METptEle_wjets_C);
    METptele_bkg_BC->Add(METptEle_dyjets_C);
    METptele_bkg_BC->Add(METptEle_vv_C);
  
    TH1F *METptele_QCD_AD = (TH1F *)METptEle_data_A->Clone("METptele_QCD_AD");
    METptele_QCD_AD->Add(METptEle_data_D);
    METptele_QCD_AD->Add(METptele_bkg_AD, -1);

    TH1F *METptele_QCD_BC = (TH1F *)METptEle_data_B->Clone("METptele_QCD_BC");
    METptele_QCD_BC->Add(METptEle_data_C);
    METptele_QCD_BC->Add(METptele_bkg_BC, -1);

    makeHistoPositive(METptele_QCD_AD,0);
    makeHistoPositive(METptele_QCD_BC,0);

    METptele_bkg_AD->SetTitle(Form("%s (bkg)",cut_title.c_str()));
    METptele_bkg_BC->SetTitle(Form("%s (bkg)",cut_title.c_str()));
    METptele_QCD_AD->SetTitle(Form("%s (QCD)",cut_title.c_str()));
    METptele_QCD_BC->SetTitle(Form("%s (QCD)",cut_title.c_str()));

    METptele_bkg_AD->Rebin(rebin);
    METptele_bkg_BC->Rebin(rebin);

    maxX = 100.;
    METptele_bkg_AD->GetXaxis()->SetRangeUser(0.0, maxX);
    METptele_bkg_BC->GetXaxis()->SetRangeUser(0.0, maxX);
    METptele_bkg_BC->SetLineColor(kRed);
    METptele_bkg_AD->Scale(1./METptele_bkg_AD->Integral());
    METptele_bkg_BC->Scale(1./METptele_bkg_BC->Integral());

    kappa = (METptele_bkg_A->Integral()/METptele_bkg_B->Integral())/(METptele_bkg_D->Integral()/METptele_bkg_C->Integral());
    //PlotRatio(METptele_bkg_BC, METptele_bkg_AD, "c4",kappa,METptele_bkg_A->Integral());

    METptele_QCD_AD->Rebin(rebin);
    METptele_QCD_BC->Rebin(rebin);

    METptele_QCD_AD->GetXaxis()->SetRangeUser(0.0, maxX);
    METptele_QCD_BC->GetXaxis()->SetRangeUser(0.0, maxX);
    METptele_QCD_BC->SetLineColor(kRed);
    METptele_QCD_AD->Scale(1./METptele_QCD_AD->Integral());
    METptele_QCD_BC->Scale(1./METptele_QCD_BC->Integral());

    kappa = (METptele_QCD_A->Integral()/METptele_QCD_B->Integral())/(METptele_QCD_D->Integral()/METptele_QCD_C->Integral());
    PlotRatio(METptele_QCD_BC, METptele_QCD_AD, "c7", "MET (e  + jets)", "#frac{BC}{AD}", kappa,METptele_QCD_A->Integral(),0);
    TCanvas *c7 = (TCanvas *)gROOT->GetListOfCanvases()->FindObject("c7");
    c7->SaveAs("output.pdf");
    outputpdf1 = Form("figs/Week_Work_Report/2023-06-02/Kappa/%d/hist_%s_%s.pdf",year,case_n.c_str(),METptele_QCD_A->GetName());
    c7->SaveAs(outputpdf1.c_str());
  
    ////////////////////// DD qcd //////////////////////////////////////////

    outputpdf1 = Form("output/kappaDD/QCD_DD_%s_ele_%d.root",case_n.c_str(),year);
    TFile *fout = new TFile(outputpdf1.c_str(),"recreate");
    Isoele_QCD_A->Write();     Isoele_QCD_B->Write();     Isoele_QCD_C->Write();     Isoele_QCD_D->Write();
    Isoele_QCD_AB->Write();    Isoele_QCD_CD->Write();
    METptele_QCD_A->Write();   METptele_QCD_B->Write();   METptele_QCD_C->Write();   METptele_QCD_D->Write();
    METptele_QCD_AD->Write();    METptele_QCD_BC->Write();
    fout->Close();
    delete fout;
  }
}

int PlotRatio(TH1F *h1, TH1F *h2, const char *cname, const char *deno_xTitle, const char *deno_yTitle, float kappa, float yield, bool isy=false)
{
  //cout<<"h1 name : "<<h1->GetName() <<", Directory : " << h1->GetDirectory()->GetMotherDir()->GetName() << endl;
  int SetLegendStyle(TLegend *& leg);
  TCanvas *canvas = (TCanvas *)gROOT->GetListOfCanvases()->FindObject(cname);
  
  if(!canvas){
    TCanvas *c = new TCanvas(cname, cname, 800, 800);
 
    // Upper plot will be in pad1
    TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
    pad1->SetBottomMargin(0.01); // Upper and lower plot are joined
    //pad1->SetGridx();         // Vertical grid
    pad1->Draw();             // Draw the upper pad: pad1
    pad1->cd();               // pad1 becomes the current pad
    pad1->SetLogy();  
    pad1->SetTickx();
    pad1->SetTicky();
    h1->SetStats(0);          // No statistics on upper plot
    h1->Draw("hist");               // Draw h1
    h2->Draw("hist same");         // Draw h2 on top of h1
 
#if ROOT_VERSION_CODE >= ROOT_VERSION(6,8,0)
    // Avoid the first label (0) to be clipped.
    TAxis *axis = h1->GetYaxis();
    axis->ChangeLabel(1, -1, -1, -1, -1, -1, " ");
    axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    axis->SetLabelSize(15);
#else
    // Do not draw the Y axis label on the upper plot and redraw a small
    // axis instead, in order to avoid the first label (0) to be clipped.
    h1->GetYaxis()->SetLabelSize(0.);
    TGaxis *axis = new TGaxis( -5, 20, -5, 220, 20,220,510,"");
    axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    axis->SetLabelSize(15);
    axis->Draw();
#endif

    //Legends
    TLegend *leg0 = new TLegend(0.6,0.75,0.99,0.85);
    SetLegendStyle(leg0);
    leg0->SetHeader(Form("#kappa = %5.3f",kappa));
    if(isy)
      leg0->AddEntry((TH1F *)0x0,Form("Yield Reg A : %5.0lf",yield),"");
    leg0->Draw();
    
    TLegend *leg1 = new TLegend(0.6,0.6,0.99,0.75);
    SetLegendStyle(leg1);
    leg1->SetHeader(h1->GetName());
    leg1->AddEntry(h1,Form("Entries : %5.0lf",h1->GetEntries()),"lp");
    leg1->AddEntry(h1,Form("Integral : %3.0lf",h1->Integral()),"lp");
    leg1->Draw();
    TLegend *leg2 = new TLegend(0.6,0.45,0.99,0.6);
    SetLegendStyle(leg2);
    leg2->SetHeader(h2->GetName());
    leg2->AddEntry(h2,Form("Entries : %5.0lf",h2->GetEntries()),"lp");
    leg2->AddEntry(h2,Form("Integral : %3.0lf",h2->Integral()),"lp");
    leg2->Draw();
    
    // lower plot will be in pad
    c->cd();          // Go back to the main canvas before defining pad2
    TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
    pad2->SetTopMargin(0.1);
    pad2->SetBottomMargin(0.2);
    //pad2->SetGridx(); // vertical grid
    pad2->SetGridy(); // vertical grid
    pad2->Draw();
    pad2->cd();       // pad2 becomes the current pad
    pad2->SetTickx();
    pad2->SetTicky();
 
    // Define the ratio plot
    TH1F *h3 = (TH1F*)h1->Clone("h3");
    h3->SetLineColor(h1->GetLineColor());

    h3->Sumw2();
    h3->SetStats(0);      // No statistics on lower plot
    h3->Divide(h2);
    
    h3->SetMinimum(0.0);  // Define Y ..
    h3->SetMaximum(2.0); // .. range
    
    
    //h3->SetMarkerStyle(21);
    h3->Draw("ep");       // Draw the ratio plot
    //hAvgErr->Draw("ep same");
    
    // h1 settings
    //h1->SetLineColor(kBlue+1);
    //h1->SetLineWidth(2);
 
    // Y axis h1 plot settings
    //h1->GetYaxis()->SetTitle(Form("Entries / %1.0f GeV",h1->GetBinWidth(2)));
    h1->GetYaxis()->SetTitle(Form("Entries"));
    h1->GetYaxis()->SetTitleSize(20);
    h1->GetYaxis()->SetTitleFont(43);
    h1->GetYaxis()->SetTitleOffset(1.55);
    h1->GetXaxis()->SetLabelOffset(2.1);
 
    // h2 settings
    //h2->SetLineColor(kRed);
    //h2->SetLineWidth(2);
 
    // Ratio plot (h3) settings
    h3->SetTitle(""); // Remove the ratio title
 
    // Y axis ratio plot settings
    h3->GetYaxis()->SetTitle(deno_yTitle);
    h3->GetYaxis()->SetNdivisions(505);
    h3->GetYaxis()->SetTitleSize(20);
    h3->GetYaxis()->SetTitleFont(43);
    h3->GetYaxis()->SetTitleOffset(1.55);
    h3->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    h3->GetYaxis()->SetLabelSize(15);
 
    // X axis ratio plot settings
    h3->GetXaxis()->SetTitle(deno_xTitle);
    h3->GetXaxis()->SetTitleSize(20);
    h3->GetXaxis()->SetTitleFont(43);
    h3->GetXaxis()->SetTitleOffset(3.2);
    h3->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    h3->GetXaxis()->SetLabelSize(15);
    
    pad1->cd();

    cout<<" nof canvas primitives " << c->GetListOfPrimitives()->GetEntries() << endl ;
    
  }

  return true;
}

int SetLegendStyle(TLegend *& leg)
{
  
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->SetTextFont(42);
  leg->SetTextSize(.04); 
  leg->SetMargin(0.1);
  leg->SetEntrySeparation(0.2);
  
  return true;
}

void makeHistoPositive(TH1F *hist, bool setErrorZero = false){
  for(int ibin=1; ibin<hist->GetNbinsX(); ibin++){
    double binCont = hist->GetBinContent(ibin);
    if(binCont<0){
      hist->SetBinContent(ibin, 0);
      if(setErrorZero) hist->SetBinError(ibin, 0);
    }
  }
}
