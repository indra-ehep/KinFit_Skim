/**********************************************************************
 Created on : 08/01/2023
 Purpose    : Compare the limit evolution for various studies with respect to the published results
 Author     : Indranil Das, Visiting Fellow
 Email      : indranil.das@cern.ch | indra.ehep@gmail.com
**********************************************************************/
#include <cstdlib>
#include <iostream> 
#include <iomanip> 
#include <fstream>
#include <map>
#include <string>
#include <cstring>

#include "TMath.h"
#include "TFile.h"
#include "TString.h"
#include "TObjString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TPluginManager.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TLegend.h"
#include "TGraphAsymmErrors.h"
#include "TGraphPainter.h"
#include "TMultiGraph.h"
#include "TTree.h"
#include "TPaveText.h"
#include "TStyle.h"

using namespace std;

typedef struct {
  float mX;
  float expY, obsY;
  float expY1sL, expY1sH, expY2sL, expY2sH;
}LimitPoints;

void ReadLimitMiniAOD(vector<LimitPoints>& Val, TString indir = "")
{

  float X[]        = {80, 90,100,120, 140, 150, 155, 160};
  float obsY[]     = {0., 0.,0.,0, 0, 0, 0, 0,0};
  float expY[]     = {0., 0.,0.,0, 0, 0, 0, 0,0};
		      
  float expY1sL[]   = {0., 0.,0.,0, 0, 0, 0, 0,0};
  float expY1sH[]   = {0., 0.,0.,0, 0, 0, 0, 0,0};		      
  float expY2sL[]  = {0., 0.,0.,0, 0, 0, 0, 0,0};
  float expY2sH[]  = {0., 0.,0.,0, 0, 0, 0, 0,0};
  
  int nMassPoints = 8;
  
  TString massFiles [8] = {
			   "Mass80/higgsCombineTest.AsymptoticLimits.mH80.root",
			   "Mass90/higgsCombineTest.AsymptoticLimits.mH90.root",
			   "Mass100/higgsCombineTest.AsymptoticLimits.mH100.root",
			   "Mass120/higgsCombineTest.AsymptoticLimits.mH120.root",
			   "Mass140/higgsCombineTest.AsymptoticLimits.mH140.root",
			   "Mass150/higgsCombineTest.AsymptoticLimits.mH150.root",
			   "Mass155/higgsCombineTest.AsymptoticLimits.mH155.root",
			   "Mass160/higgsCombineTest.AsymptoticLimits.mH160.root"
			   //higgsCombineTest.AsymptoticLimits.mH90.root
  };
  
  
  for(unsigned int i = 0 ; i < UInt_t(nMassPoints); i++){
    TFile f(indir+"/"+massFiles[i],"READ"); // higgsCombine_hcs_13TeV_mu.AsymptoticLimits.mH140.root
    if(f.IsZombie()){
      cout << "Cannot open file for " << indir << " and mass " << X[i] << endl;
      continue;
    }
    Double_t r;
    TTree* limit = (TTree*)f.Get("limit");
    limit->SetBranchAddress("limit",&r);
    for(int k = 0 ; k< limit->GetEntries() ; k++){
      limit->GetEntry(k);
      r *= 100.0;
      if(k==0) expY2sL[i] = r;
      if(k==1) expY1sL[i] = r;
      if(k==2) expY[i]    = r;
      if(k==3) expY1sH[i] = r;
      if(k==4) expY2sH[i] = r;
      if(k==5) obsY[i]    = r;
    }
    
    LimitPoints LP;
    LP.mX = X[i]; LP.expY = expY[i]; LP.obsY = obsY[i];
    LP.expY1sL = expY1sL[i]; LP.expY2sL = expY2sL[i];
    LP.expY1sH = expY1sH[i]; LP.expY2sH = expY2sH[i];
    Val.push_back(LP);
    
    f.Close();
  }//mass points
  
}

void ReadLimitNanoAOD(vector<LimitPoints>& Val, TString indir = "", TString ch = "mu_ele")
{

  float X[]        = {80, 90, 100, 110, 120, 130, 140, 150, 155, 160};
  float obsY[]     = {0., 0.,0.,0, 0, 0, 0, 0, 0, 0};
  float expY[]     = {0., 0.,0.,0, 0, 0, 0, 0, 0, 0};
		      
  float expY1sL[]   = {0., 0.,0.,0, 0, 0, 0, 0, 0, 0};
  float expY1sH[]   = {0., 0.,0.,0, 0, 0, 0, 0, 0, 0};		      
  float expY2sL[]  = {0., 0.,0.,0, 0, 0, 0, 0, 0, 0};
  float expY2sH[]  = {0., 0.,0.,0, 0, 0, 0, 0, 0, 0};

  int nMassPoints = 10;

  TString massFiles [10] = {
			   "Mass80/higgsCombine_hcs_13TeV_"+ch+"_Cat1_Inc.AsymptoticLimits.mH80.root",
			   "Mass90/higgsCombine_hcs_13TeV_"+ch+"_Cat1_Inc.AsymptoticLimits.mH90.root",
			   "Mass100/higgsCombine_hcs_13TeV_"+ch+"_Cat1_Inc.AsymptoticLimits.mH100.root",
			   "Mass110/higgsCombine_hcs_13TeV_"+ch+"_Cat1_Inc.AsymptoticLimits.mH110.root",
			   "Mass120/higgsCombine_hcs_13TeV_"+ch+"_Cat1_Inc.AsymptoticLimits.mH120.root",
			   "Mass130/higgsCombine_hcs_13TeV_"+ch+"_Cat1_Inc.AsymptoticLimits.mH130.root",
			   "Mass140/higgsCombine_hcs_13TeV_"+ch+"_Cat1_Inc.AsymptoticLimits.mH140.root",
			   "Mass150/higgsCombine_hcs_13TeV_"+ch+"_Cat1_Inc.AsymptoticLimits.mH150.root",
			   "Mass155/higgsCombine_hcs_13TeV_"+ch+"_Cat1_Inc.AsymptoticLimits.mH155.root",
			   "Mass160/higgsCombine_hcs_13TeV_"+ch+"_Cat1_Inc.AsymptoticLimits.mH160.root"
			   //higgsCombineTest.AsymptoticLimits.mH90.root
			   //higgsCombine_hcs_13TeV_mu_ele_Cat1_Inc.AsymptoticLimits.mH80.root
  };

  
  for(unsigned int i = 0 ; i < UInt_t(nMassPoints); i++){
    TFile f(indir+"/"+ch+"/Cat1_Inc/"+massFiles[i],"READ"); // higgsCombine_hcs_13TeV_mu.AsymptoticLimits.mH140.root
    if(f.IsZombie()){
      cout << "Cannot open file for " << indir << " and mass " << X[i] << endl;
      continue;
    }
    Double_t r;
    TTree* limit = (TTree*)f.Get("limit");
    limit->SetBranchAddress("limit",&r);
    for(int k = 0 ; k< limit->GetEntries() ; k++){
      limit->GetEntry(k);
      r *= 100.0;
      if(k==0) expY2sL[i] = r;
      if(k==1) expY1sL[i] = r;
      if(k==2) expY[i]    = r;
      if(k==3) expY1sH[i] = r;
      if(k==4) expY2sH[i] = r;
      if(k==5) obsY[i]    = r;
    }
    LimitPoints LP;
    LP.mX = X[i]; LP.expY = expY[i]; LP.obsY = obsY[i];
    LP.expY1sL = expY1sL[i]; LP.expY2sL = expY2sL[i];
    LP.expY1sH = expY1sH[i]; LP.expY2sH = expY2sH[i];
    Val.push_back(LP);
    
    f.Close();
  }//mass points
  
}

void SetStyle(TGraph*& gr, Width_t width, Color_t color, Style_t markerstyle, Size_t markersize)
{
  gr->SetLineWidth(width);
  gr->SetLineColor(color);
  gr->SetMarkerStyle(markerstyle);
  gr->SetMarkerSize(markersize);
  gr->SetMarkerColor(color);
}

void CompareLimits(){
  
  void SetStyle(TGraph*&, Width_t, Color_t, Style_t, Size_t);
  void ReadLimitMiniAOD(vector<LimitPoints>&, TString);
  void ReadLimitNanoAOD(vector<LimitPoints>&, TString, TString);
  
  vector<LimitPoints> lexclMini;
  vector<LimitPoints> lexclMiniInc;
  vector<LimitPoints> lexclMEqv16lnN;
  vector<LimitPoints> lexclMEqv16shape;
  vector<LimitPoints> lexclNano16;
  vector<LimitPoints> lexclNano;
  
  vector<LimitPoints> linclNanoUnNorm;
  vector<LimitPoints> linclNanoUN_Rank1;
  vector<LimitPoints> linclNanoUN_Rank13;
  vector<LimitPoints> linclNanoUN_Rank134;
  vector<LimitPoints> linclNanoUN_Rank1345;
  vector<LimitPoints> linclNanoUN_Rank13456;
  vector<LimitPoints> linclNanoUN_Rank134567;
  vector<LimitPoints> linclNanoUN_Rank1345678;
  vector<LimitPoints> linclNanoUN_Rank1t8_17;
  vector<LimitPoints> linclNanoUN_Rank1t8_17_21;
  vector<LimitPoints> linclNanoUN_Rank1t8_17_21_24;
  
  //01
  // ReadLimitMiniAOD(lexclMini, "hig-18-021/PublishedPRD/ForANv12/mu_ele/Cat3_cTagEx");
  // ReadLimitNanoAOD(lexclMEqv16lnN, "TIFRAPAR-2023-01-15/01_yearend22-MiniAODEqv/Run2/Comb", "mu_ele");

  //02
  // ReadLimitMiniAOD(lexclMini, "hig-18-021/PublishedPRD/ForANv12/mu_ele/Cat3_cTagEx");
  // ReadLimitNanoAOD(lexclMEqv16lnN, "TIFRAPAR-2023-01-15/01_yearend22-MiniAODEqv/2016/Comb", "mu_ele");
  // ReadLimitNanoAOD(lexclMEqv16shape, "TIFRAPAR-2023-01-15/11_elereliso-NanoAOD_logN/2016/Comb", "mu_ele");

  //03
  // ReadLimitMiniAOD(lexclMini, "hig-18-021/PublishedPRD/ForANv12/mu_ele/Cat3_cTagEx");
  // ReadLimitNanoAOD(lexclMEqv16lnN, "TIFRAPAR-2023-01-15/01_yearend22-MiniAODEqv/2016/Comb", "mu_ele");
  //ReadLimitNanoAOD(lexclMEqv16shape, "TIFRAPAR-2023-01-15/05_yearend22-MiniAODEqv_Shapes/2016/Comb", "mu_ele");

  //04
  // ReadLimitMiniAOD(lexclMini, "hig-18-021/PublishedPRD/ForANv12/mu_ele/Cat3_cTagEx");
  // ReadLimitNanoAOD(lexclMEqv16lnN, "TIFRAPAR-2023-01-15/01_yearend22-MiniAODEqv/2016/Comb", "mu_ele");
  // ReadLimitNanoAOD(lexclMEqv16shape, "TIFRAPAR-2023-01-15/12_yearend22-MiniAODEqv_unblinded/2016/Comb", "mu_ele");

  //05
  // ReadLimitMiniAOD(lexclMini, "hig-18-021/PublishedPRD/ForANv12/mu_ele/Cat3_cTagEx");
  // ReadLimitNanoAOD(lexclMEqv16lnN, "TIFRAPAR-2023-01-15/01_yearend22-MiniAODEqv/2016/Comb", "mu_ele");
  // ReadLimitNanoAOD(lexclMEqv16shape, "TIFRAPAR-2023-01-15/01_yearend22-MiniAODEqv/Run2/Comb", "mu_ele");

  //06
  // ReadLimitMiniAOD(lexclMini, "hig-18-021/PublishedPRD/ForANv12/mu_ele/Cat3_cTagEx");
  // ReadLimitNanoAOD(lexclMEqv16lnN, "TIFRAPAR-2023-01-15/05_yearend22-MiniAODEqv_Shapes/2016/Comb", "mu_ele");
  // ReadLimitNanoAOD(lexclMEqv16shape, "TIFRAPAR-2023-01-15/05_yearend22-MiniAODEqv_Shapes/Run2/Comb", "mu_ele");

  //07
  // ReadLimitMiniAOD(lexclMini, "hig-18-021/PublishedPRD/ForANv12/mu_ele/Cat3_cTagEx");
  // ReadLimitNanoAOD(lexclMEqv16lnN, "TIFRAPAR-2023-01-15/11_elereliso-NanoAOD_logN/2016/Comb", "mu_ele");
  // ReadLimitNanoAOD(lexclMEqv16shape, "TIFRAPAR-2023-01-15/09_elereliso-NanoAOD_Shapes/2016/Comb", "mu_ele");

  //08
  // ReadLimitMiniAOD(lexclMini, "hig-18-021/PublishedPRD/ForANv12/mu_ele/Cat3_cTagEx");
  // ReadLimitNanoAOD(lexclMEqv16lnN, "TIFRAPAR-2023-01-15/09_elereliso-NanoAOD_Shapes/2016/Comb", "mu_ele");
  // ReadLimitNanoAOD(lexclMEqv16shape, "TIFRAPAR-2023-01-15/14_elereliso-NanoAOD_unblinded/2016/Comb", "mu_ele");

  //09
  // ReadLimitMiniAOD(lexclMini, "hig-18-021/PublishedPRD/ForANv12/mu_ele/Cat3_cTagEx");
  // ReadLimitNanoAOD(lexclMEqv16lnN, "TIFRAPAR-2023-01-15/09_elereliso-NanoAOD_Shapes/2016/Comb", "mu_ele");
  // ReadLimitNanoAOD(lexclMEqv16shape, "TIFRAPAR-2023-01-15/09_elereliso-NanoAOD_Shapes/Run2/Comb", "mu_ele");

  //10
  // ReadLimitMiniAOD(lexclMini, "hig-18-021/PublishedPRD/ForANv12/mu_ele/Cat3_cTagEx");
  // ReadLimitNanoAOD(lexclMEqv16lnN, "TIFRAPAR-2023-01-15/05_yearend22-MiniAODEqv_Shapes/2016/Comb", "mu_ele");
  // ReadLimitNanoAOD(lexclMEqv16shape, "TIFRAPAR-2023-01-15/09_elereliso-NanoAOD_Shapes/2016/Comb", "mu_ele");

  //11
  // ReadLimitMiniAOD(lexclMini, "hig-18-021/PublishedPRD/ForANv12/mu_ele/Cat3_cTagEx");
  // ReadLimitMiniAOD(lexclMiniInc, "hig-18-021/PublishedPRD/ForANv12/mu_ele/Cat1_Inc");
  // ReadLimitNanoAOD(lexclMEqv16lnN, "TIFRAPAR-2023-01-15/01_yearend22-MiniAODEqv/2016/Comb", "mu_ele");
  // ReadLimitNanoAOD(lexclMEqv16shape, "TIFRAPAR-2023-01-15/01_yearend22-MiniAODEqv/2016/Incl", "mu_ele");

  // 12
  // ReadLimitMiniAOD(lexclMini, "hig-18-021/PublishedPRD/ForANv12/mu_ele/Cat3_cTagEx");
  // ReadLimitMiniAOD(lexclMiniInc, "hig-18-021/PublishedPRD/ForANv12/mu_ele/Cat1_Inc");
  // ReadLimitNanoAOD(lexclMEqv16lnN, "TIFRAPAR-2023-01-15/01_yearend22-MiniAODEqv/2016/Incl", "mu_ele");
  // ReadLimitNanoAOD(lexclMEqv16shape, "TIFRAPAR-2023-01-15/04_notoppt-UptoKFBTagSyst/2016/Incl", "mu_ele");

  //14
  // ReadLimitMiniAOD(lexclMini, "hig-18-021/PublishedPRD/ForANv12/mu_ele/Cat3_cTagEx");
  // ReadLimitNanoAOD(lexclMEqv16lnN, "TIFRAPAR-2023-01-15/01_yearend22-MiniAODEqv/Run2/Comb", "mu_ele");
  // ReadLimitNanoAOD(lexclMEqv16shape, "TIFRAPAR-2023-01-15/09_elereliso-NanoAOD_Shapes/Run2/Comb", "mu_ele");
  
  //15
  // ReadLimitMiniAOD(lexclMini, "hig-18-021/PublishedPRD/ForANv12/mu_ele/Cat3_cTagEx");
  // ReadLimitNanoAOD(lexclMEqv16lnN, "TIFRAPAR-2023-01-15/01_yearend22-MiniAODEqv/2016/Comb", "mu_ele");
  // ReadLimitNanoAOD(lexclMEqv16shape, "TIFRAPAR-2023-01-15/01_yearend22-MiniAODEqv/2017/Comb", "mu_ele");
  // ReadLimitNanoAOD(lexclNano16, "TIFRAPAR-2023-01-15/01_yearend22-MiniAODEqv/2018/Comb", "mu_ele");
  // ReadLimitNanoAOD(lexclNano, "TIFRAPAR-2023-01-15/01_yearend22-MiniAODEqv/Run2/Comb", "mu_ele");
  
  //16
  // ReadLimitMiniAOD(lexclMini, "hig-18-021/PublishedPRD/ForANv12/mu_ele/Cat3_cTagEx");
  // ReadLimitNanoAOD(lexclMEqv16lnN, "TIFRAPAR-2023-01-15/09_elereliso-NanoAOD_Shapes/2016/Comb", "mu_ele");
  // ReadLimitNanoAOD(lexclMEqv16shape, "TIFRAPAR-2023-01-15/09_elereliso-NanoAOD_Shapes/2017/Comb", "mu_ele");
  // ReadLimitNanoAOD(lexclNano16, "TIFRAPAR-2023-01-15/09_elereliso-NanoAOD_Shapes/2018/Comb", "mu_ele");
  // ReadLimitNanoAOD(lexclNano, "TIFRAPAR-2023-01-15/09_elereliso-NanoAOD_Shapes/Run2/Comb", "mu_ele");

  // 21
  // ReadLimitMiniAOD(lexclMini, "hig-18-021/PublishedPRD/ForANv12/mu/Cat3_cTagEx");
  // ReadLimitMiniAOD(lexclMiniInc, "hig-18-021/PublishedPRD/ForANv12/mu/Cat1_Inc");
  // ReadLimitNanoAOD(lexclMEqv16lnN, "TIFRAPAR-2023-01-15/11_elereliso-NanoAOD_logN/2016/Incl", "mu");
  // ReadLimitNanoAOD(lexclMEqv16shape, "TIFRAPAR-2023-01-15/09_elereliso-NanoAOD_Shapes/2016/Incl", "mu");
  // //ReadLimitNanoAOD(lexclMEqv16shape, "TIFRAPAR-2023-01-15/09_elereliso-NanoAOD_Shapes/2017/Comb", "mu");
  // ReadLimitNanoAOD(lexclNano16, "TIFRAPAR-2023-01-15/09_elereliso-NanoAOD_Shapes/2018/Comb", "mu");
  // ReadLimitNanoAOD(lexclNano, "TIFRAPAR-2023-01-15/09_elereliso-NanoAOD_Shapes/Run2/Comb", "mu");

  // 22-31
  // ReadLimitMiniAOD(lexclMini, "hig-18-021/PublishedPRD/ForANv12/mu/Cat3_cTagEx");
  // ReadLimitMiniAOD(lexclMiniInc, "hig-18-021/PublishedPRD/ForANv12/mu/Cat1_Inc");
  // ReadLimitNanoAOD(lexclMEqv16lnN, "TIFRAPAR-2023-01-15/11_elereliso-NanoAOD_logN/2016/Incl", "mu");
  // ReadLimitNanoAOD(lexclMEqv16shape, "TIFRAPAR-2023-01-15/09_elereliso-NanoAOD_Shapes/2016/Incl", "mu");
  // ReadLimitNanoAOD(lexclNano16, "TIFRAPAR-2023-01-15/09_elereliso-NanoAOD_Shapes/2018/Comb", "mu");
  // ReadLimitNanoAOD(lexclNano, "TIFRAPAR-2023-01-15/09_elereliso-NanoAOD_Shapes/Run2/Comb", "mu");
  
  // ReadLimitNanoAOD(linclNanoUnNorm, "TIFRAPAR-2023-01-15/15_RankCheck_unNormalized/15_elereliso-NanoAOD_Shapes_unNormalized/2016/Incl", "mu");
  // ReadLimitNanoAOD(linclNanoUN_Rank1, "TIFRAPAR-2023-01-15/15_RankCheck_unNormalized/16_elereliso-NanoAOD_Shapes_unNormalized_Rank1_lnN/2016/Incl", "mu");
  // ReadLimitNanoAOD(linclNanoUN_Rank13, "TIFRAPAR-2023-01-15/15_RankCheck_unNormalized/17_elereliso-NanoAOD_Shapes_unNormalized_Rank13_lnN/2016/Incl", "mu");
  // ReadLimitNanoAOD(linclNanoUN_Rank134, "TIFRAPAR-2023-01-15/15_RankCheck_unNormalized/18_elereliso-NanoAOD_Shapes_unNormalized_Rank134_lnN/2016/Incl", "mu");
  // ReadLimitNanoAOD(linclNanoUN_Rank1345, "TIFRAPAR-2023-01-15/15_RankCheck_unNormalized/19_elereliso-NanoAOD_Shapes_unNormalized_Rank1345_lnN/2016/Incl", "mu");
  // ReadLimitNanoAOD(linclNanoUN_Rank13456, "TIFRAPAR-2023-01-15/15_RankCheck_unNormalized/20_elereliso-NanoAOD_Shapes_unNormalized_Rank13456_lnN/2016/Incl", "mu");
  // ReadLimitNanoAOD(linclNanoUN_Rank134567, "TIFRAPAR-2023-01-15/15_RankCheck_unNormalized/21_elereliso-NanoAOD_Shapes_unNormalized_Rank134567_lnN/2016/Incl", "mu");
  // ReadLimitNanoAOD(linclNanoUN_Rank1345678, "TIFRAPAR-2023-01-15/15_RankCheck_unNormalized/22_elereliso-NanoAOD_Shapes_unNormalized_Rank1345678_lnN/2016/Incl", "mu");
  // ReadLimitNanoAOD(linclNanoUN_Rank1t8_17, "TIFRAPAR-2023-01-15/15_RankCheck_unNormalized/23_elereliso-NanoAOD_Shapes_unNormalized_Rank1-8_17_lnN/2016/Incl", "mu");
  // ReadLimitNanoAOD(linclNanoUN_Rank1t8_17_21, "TIFRAPAR-2023-01-15/15_RankCheck_unNormalized/24_elereliso-NanoAOD_Shapes_unNormalized_Rank1-8_17_21_lnN/2016/Incl", "mu");
  // ReadLimitNanoAOD(linclNanoUN_Rank1t8_17_21_24, "TIFRAPAR-2023-01-15/15_RankCheck_unNormalized/25_elereliso-NanoAOD_Shapes_unNormalized_Rank1-8_17_21_24_lnN/2016/Incl", "mu");

  //32
  //ReadLimitNanoAOD(linclNanoUN_Rank1t8_17_21_24, "TIFRAPAR-2023-01-15/15_RankCheck_unNormalized/30_elereliso-NanoAOD_lnN_unNormalized_theory_Shape/2016/Incl", "mu");

  //33
  //ReadLimitNanoAOD(linclNanoUN_Rank1t8_17_21_24, "TIFRAPAR-2023-01-15/15_RankCheck_unNormalized/29_elereliso-NanoAOD_lnN_unNormalized_bctagging_Shape/2016/Incl", "mu");


  ReadLimitMiniAOD(lexclMini, "hig-18-021/PublishedPRD/ForANv12/mu/Cat3_cTagEx");
  ReadLimitMiniAOD(lexclMiniInc, "hig-18-021/PublishedPRD/ForANv12/mu/Cat1_Inc");
  ReadLimitNanoAOD(lexclMEqv16lnN, "TIFRAPAR-2023-01-15/11_elereliso-NanoAOD_logN/2016/Incl", "mu");
  ReadLimitNanoAOD(lexclMEqv16shape, "TIFRAPAR-2023-01-15/09_elereliso-NanoAOD_Shapes/2016/Incl", "mu");
  // ReadLimitNanoAOD(lexclMEqv16lnN, "TIFRAPAR-2023-01-15/02_yearend22-UptoKFBTagSyst/2016/Incl", "mu");
  // ReadLimitNanoAOD(lexclMEqv16shape, "TIFRAPAR-2023-01-15/06_yearend22-UptoKFBTagSyst_Shapes/2016/Incl", "mu");

  ReadLimitNanoAOD(lexclNano16, "TIFRAPAR-2023-01-15/09_elereliso-NanoAOD_Shapes/2018/Comb", "mu");
  ReadLimitNanoAOD(lexclNano, "TIFRAPAR-2023-01-15/09_elereliso-NanoAOD_Shapes/Run2/Comb", "mu");
  
  ReadLimitNanoAOD(linclNanoUnNorm, "TIFRAPAR-2023-01-15/15_RankCheck_unNormalized/15_elereliso-NanoAOD_Shapes_unNormalized/2016/Incl", "mu");
  ReadLimitNanoAOD(linclNanoUN_Rank1, "TIFRAPAR-2023-01-15/15_RankCheck_unNormalized/16_elereliso-NanoAOD_Shapes_unNormalized_Rank1_lnN/2016/Incl", "mu");
  ReadLimitNanoAOD(linclNanoUN_Rank13, "TIFRAPAR-2023-01-15/15_RankCheck_unNormalized/17_elereliso-NanoAOD_Shapes_unNormalized_Rank13_lnN/2016/Incl", "mu");
  ReadLimitNanoAOD(linclNanoUN_Rank134, "TIFRAPAR-2023-01-15/15_RankCheck_unNormalized/18_elereliso-NanoAOD_Shapes_unNormalized_Rank134_lnN/2016/Incl", "mu");
  ReadLimitNanoAOD(linclNanoUN_Rank1345, "TIFRAPAR-2023-01-15/15_RankCheck_unNormalized/19_elereliso-NanoAOD_Shapes_unNormalized_Rank1345_lnN/2016/Incl", "mu");
  ReadLimitNanoAOD(linclNanoUN_Rank13456, "TIFRAPAR-2023-01-15/15_RankCheck_unNormalized/20_elereliso-NanoAOD_Shapes_unNormalized_Rank13456_lnN/2016/Incl", "mu");
  ReadLimitNanoAOD(linclNanoUN_Rank134567, "TIFRAPAR-2023-01-15/15_RankCheck_unNormalized/21_elereliso-NanoAOD_Shapes_unNormalized_Rank134567_lnN/2016/Incl", "mu");
  ReadLimitNanoAOD(linclNanoUN_Rank1345678, "TIFRAPAR-2023-01-15/15_RankCheck_unNormalized/22_elereliso-NanoAOD_Shapes_unNormalized_Rank1345678_lnN/2016/Incl", "mu");
  ReadLimitNanoAOD(linclNanoUN_Rank1t8_17, "TIFRAPAR-2023-01-15/15_RankCheck_unNormalized/23_elereliso-NanoAOD_Shapes_unNormalized_Rank1-8_17_lnN/2016/Incl", "mu");
  ReadLimitNanoAOD(linclNanoUN_Rank1t8_17_21, "TIFRAPAR-2023-01-15/15_RankCheck_unNormalized/24_elereliso-NanoAOD_Shapes_unNormalized_Rank1-8_17_21_lnN/2016/Incl", "mu");
  //ReadLimitNanoAOD(linclNanoUN_Rank1t8_17_21_24, "TIFRAPAR-2023-01-15/15_RankCheck_unNormalized/25_elereliso-NanoAOD_Shapes_unNormalized_Rank1-8_17_21_24_lnN/2016/Incl", "mu");
  //ReadLimitNanoAOD(linclNanoUN_Rank1t8_17_21_24, "TIFRAPAR-2023-01-15/15_RankCheck_unNormalized/26_elereliso_bcstat-RES-REJ-MuR-intp-extp_lnN/2016/Incl", "mu");
  //ReadLimitNanoAOD(linclNanoUN_Rank1t8_17_21_24, "TIFRAPAR-2023-01-15/15_RankCheck_unNormalized/27_elereliso_REJ-hdamp-cp5_lnN/2016/Incl", "mu");
  //ReadLimitNanoAOD(linclNanoUN_Rank1t8_17_21_24, "TIFRAPAR-2023-01-15/15_RankCheck_unNormalized/28_elereliso_CP5-intp-extp_lnN/2016/Incl", "mu");
  //ReadLimitNanoAOD(linclNanoUN_Rank1t8_17_21_24, "TIFRAPAR-2023-01-15/15_RankCheck_unNormalized/29_elereliso-NanoAOD_lnN_unNormalized_bctagging_Shape/2016/Incl", "mu");
  //ReadLimitNanoAOD(linclNanoUN_Rank1t8_17_21_24, "TIFRAPAR-2023-01-15/15_RankCheck_unNormalized/30_elereliso-NanoAOD_lnN_unNormalized_theory_Shape/2016/Incl", "mu");
  //ReadLimitNanoAOD(linclNanoUN_Rank1t8_17_21_24, "TIFRAPAR-2023-01-15/15_RankCheck_unNormalized/31_yearend22-UptoKFBTagSyst_lnN_unNormalized_btagging_Shape/2016/Incl", "mu");
  //ReadLimitNanoAOD(linclNanoUN_Rank1t8_17_21_24, "TIFRAPAR-2023-01-15/15_RankCheck_unNormalized/32_yearend22-UptoKFBTagSyst_lnN_unNormalized_jet_Shape/2016/Incl", "mu");
  //ReadLimitNanoAOD(linclNanoUN_Rank1t8_17_21_24, "TIFRAPAR-2023-01-15/15_RankCheck_unNormalized/33_yearend22-UptoKFBTagSyst_lnN_unNormalized_theory_Shape/2016/Incl", "mu");
  //ReadLimitNanoAOD(linclNanoUN_Rank1t8_17_21_24, "TIFRAPAR-2023-01-15/15_RankCheck_unNormalized/34_elereliso-lnN_SevenSyst_Shape/2016/Incl", "mu");
  //ReadLimitNanoAOD(linclNanoUN_Rank1t8_17_21_24, "TIFRAPAR-2023-01-15/15_RankCheck_unNormalized/35_elereliso-lnN_FiveSyst_Shape/2016/Incl", "mu");
  //ReadLimitNanoAOD(linclNanoUN_Rank1t8_17_21_24, "TIFRAPAR-2023-01-15/15_RankCheck_unNormalized/36_elereliso-lnN_FourSyst_Shape/2016/Incl", "mu");
  //ReadLimitNanoAOD(linclNanoUN_Rank1t8_17_21_24, "TIFRAPAR-2023-01-15/15_RankCheck_unNormalized/37_elereliso-lnN_ThreeSyst_Shape/2016/Incl", "mu");
  //ReadLimitNanoAOD(linclNanoUN_Rank1t8_17_21_24, "TIFRAPAR-2023-01-15/15_RankCheck_unNormalized/38_elereliso-lnN_hDamp-topmass_Shape/2016/Incl", "mu");
  //ReadLimitNanoAOD(linclNanoUN_Rank1t8_17_21_24, "TIFRAPAR-2023-01-15/15_RankCheck_unNormalized/39_elereliso-lnN_FSR-JES_Shape/2016/Incl", "mu");
  //ReadLimitNanoAOD(linclNanoUN_Rank1t8_17_21_24, "TIFRAPAR-2023-01-15/15_RankCheck_unNormalized/40_elereliso-lnN_FSR-JES-hDamp_Shape/2016/Incl", "mu");
  ReadLimitNanoAOD(linclNanoUN_Rank1t8_17_21_24, "TIFRAPAR-2023-01-15/15_RankCheck_unNormalized/41_elereliso-lnN_FSR-JES-topmas_Shape/2016/Incl", "mu");
  
  //MiniAOD graphs
  TGraph *grlexclMini = new TGraph(int(lexclMini.size()));
  TGraph *grlexclMiniInc = new TGraph(int(lexclMiniInc.size()));
  cout << "lexclMini.size : " << lexclMini.size() << endl;
  for(int i = 0; i < int(lexclMini.size()) ; i++){
    printf("X : %3.0f, Y : %5.2f\%\n",lexclMini[i].mX, lexclMini[i].expY);
    grlexclMini->SetPoint(i,lexclMini[i].mX, lexclMini[i].expY);
    grlexclMiniInc->SetPoint(i,lexclMiniInc[i].mX, lexclMiniInc[i].expY);
  }
  
  //NanoAOD graphs
  TGraph *grlexclMEqv16lnN = new TGraph(int(lexclMEqv16lnN.size()));
  TGraph *grlexclMEqv16shape = new TGraph(int(lexclMEqv16shape.size()));
  TGraph *grlexclNano16 = new TGraph(int(lexclNano16.size()));
  TGraph *grlexclNano = new TGraph(int(lexclNano.size()));
  TGraph *grlinclNanoUnNorm = new TGraph(int(linclNanoUnNorm.size()));
  TGraph *grlinclNanoUN_Rank1 = new TGraph(int(linclNanoUN_Rank1.size()));
  TGraph *grlinclNanoUN_Rank13 = new TGraph(int(linclNanoUN_Rank13.size()));
  TGraph *grlinclNanoUN_Rank134 = new TGraph(int(linclNanoUN_Rank134.size()));
  TGraph *grlinclNanoUN_Rank1345 = new TGraph(int(linclNanoUN_Rank1345.size()));
  TGraph *grlinclNanoUN_Rank13456 = new TGraph(int(linclNanoUN_Rank13456.size()));
  TGraph *grlinclNanoUN_Rank134567 = new TGraph(int(linclNanoUN_Rank134567.size()));
  TGraph *grlinclNanoUN_Rank1345678 = new TGraph(int(linclNanoUN_Rank1345678.size()));
  TGraph *grlinclNanoUN_Rank1t8_17 = new TGraph(int(linclNanoUN_Rank1t8_17.size()));
  TGraph *grlinclNanoUN_Rank1t8_17_21 = new TGraph(int(linclNanoUN_Rank1t8_17_21.size()));
  TGraph *grlinclNanoUN_Rank1t8_17_21_24 = new TGraph(int(linclNanoUN_Rank1t8_17_21_24.size()));

  cout << "lexclMEqv16lnN.size : " << lexclMEqv16lnN.size() << endl;
  cout << "lexclMEqv16shape.size : " << lexclMEqv16shape.size() << endl;
  cout << "lexclNano16.size : " << lexclNano16.size() << endl;
  for(int i = 0; i < int(lexclMEqv16lnN.size()) ; i++){
    printf("X : %3.0f, Y : %5.2f\%\n",lexclMEqv16lnN[i].mX, lexclMEqv16lnN[i].expY);
    //printf("X : %3.0f, Y : %5.2f\%\n",lexclMEqv16shape[i].mX, lexclMEqv16shape[i].expY);
    grlexclMEqv16lnN->SetPoint(i,lexclMEqv16lnN[i].mX, lexclMEqv16lnN[i].expY);
    grlexclMEqv16shape->SetPoint(i,lexclMEqv16shape[i].mX, lexclMEqv16shape[i].expY);
    grlexclNano16->SetPoint(i,lexclNano16[i].mX, lexclNano16[i].expY);
    grlexclNano->SetPoint(i,lexclNano[i].mX, lexclNano[i].expY);
    
    grlinclNanoUnNorm->SetPoint(i, linclNanoUnNorm[i].mX, linclNanoUnNorm[i].expY);;
    grlinclNanoUN_Rank1->SetPoint(i, linclNanoUN_Rank1[i].mX, linclNanoUN_Rank1[i].expY);;
    grlinclNanoUN_Rank13->SetPoint(i, linclNanoUN_Rank13[i].mX, linclNanoUN_Rank13[i].expY);;
    grlinclNanoUN_Rank134->SetPoint(i, linclNanoUN_Rank134[i].mX, linclNanoUN_Rank134[i].expY);;
    grlinclNanoUN_Rank1345->SetPoint(i, linclNanoUN_Rank1345[i].mX, linclNanoUN_Rank1345[i].expY);;
    grlinclNanoUN_Rank13456->SetPoint(i, linclNanoUN_Rank13456[i].mX, linclNanoUN_Rank13456[i].expY);;
    grlinclNanoUN_Rank134567->SetPoint(i, linclNanoUN_Rank134567[i].mX, linclNanoUN_Rank134567[i].expY);;
    grlinclNanoUN_Rank1345678->SetPoint(i, linclNanoUN_Rank1345678[i].mX, linclNanoUN_Rank1345678[i].expY);;
    grlinclNanoUN_Rank1t8_17->SetPoint(i, linclNanoUN_Rank1t8_17[i].mX, linclNanoUN_Rank1t8_17[i].expY);;
    grlinclNanoUN_Rank1t8_17_21->SetPoint(i, linclNanoUN_Rank1t8_17_21[i].mX, linclNanoUN_Rank1t8_17_21[i].expY);;
    grlinclNanoUN_Rank1t8_17_21_24->SetPoint(i, linclNanoUN_Rank1t8_17_21_24[i].mX, linclNanoUN_Rank1t8_17_21_24[i].expY);;

  }
  
  SetStyle(grlexclMini, 2,kBlue, kFullCircle,1.2);
  SetStyle(grlexclMiniInc, 2,kRed, kOpenCircle,1.2);
  //SetStyle(grlexclMEqv16lnN, 2,kMagenta, kFullSquare,1.2);
  SetStyle(grlexclMEqv16lnN, 2,kMagenta, kFullDoubleDiamond,3.2);
  //SetStyle(grlexclMEqv16lnN, 2,kGreen+2, kOpenSquare,2.1);
  //SetStyle(grlexclMEqv16lnN, 3, 28, kFullDoubleDiamond,3.1);
  //SetStyle(grlexclMEqv16lnN, 3,kOrange+2, kFullCrossX,2.1);
  //  SetStyle(grlexclMEqv16lnN, 2,kRed, kFullStar,2.1);
  //SetStyle(grlexclMEqv16lnN, 2,kGreen+2, kOpenSquare,2.1);
  //SetStyle(grlexclMEqv16shape, 3, 28, kFullDoubleDiamond,3.1);
  //SetStyle(grlexclMEqv16shape, 2,kBlack, kFullTriangleDown,2.1);
  //SetStyle(grlexclMEqv16shape, 3,kGreen+2, kOpenTriangleDown,2.1);
  SetStyle(grlexclMEqv16shape, 2, kRed-2, kOpenTriangleUp, 2.1);
  //SetStyle(grlexclMEqv16shape, 3, kGreen+2, kFullTriangleUp,2.1);
  //SetStyle(grlexclMEqv16shape, 3, 49, kFullFourTrianglesPlus,3.1);
  //SetStyle(grlexclMEqv16shape, 3,kOrange+2, kFullCrossX,2.1);
  //SetStyle(grlexclMEqv16shape, 3,kGreen+2, kOpenSquare,1.2);
  //SetStyle(grlexclMEqv16shape, 2,kGreen+2, kOpenSquare,2.1);
  //SetStyle(grlexclMEqv16shape, 2,kRed, kFullStar,2.1);
  //SetStyle(grlexclNano16, 2,kRed, kFullThreeTriangles,3.1);
  SetStyle(grlexclNano16, 2,kRed, kFourSquaresX,2.1);
  //SetStyle(grlexclNano16, 2,kBlack, kFullCross,2.1);
  //SetStyle(grlexclNano, 3,kOrange+2, kFullCrossX,2.1);
  SetStyle(grlexclNano, 2,kBlack, kFullCross,2.1);
  
  SetStyle(grlinclNanoUnNorm, 2, kRed-2, kOpenTriangleUp, 2.1);
  SetStyle(grlinclNanoUN_Rank1, 2, kBlue-2, kOpenSquare, 2.1);
  SetStyle(grlinclNanoUN_Rank13, 2, kGreen-1, kOpenSquare, 2.1);
  SetStyle(grlinclNanoUN_Rank134, 2, kRed-1, kOpenSquare, 2.1);
  SetStyle(grlinclNanoUN_Rank1345, 2, kBlue-1, kOpenSquare, 2.1);
  SetStyle(grlinclNanoUN_Rank13456, 2, kGreen+2, kOpenSquare, 2.1);
  SetStyle(grlinclNanoUN_Rank134567, 2, kRed+1, kOpenSquare, 2.1);
  SetStyle(grlinclNanoUN_Rank1345678, 2, kBlue+1, kOpenSquare, 2.1);
  SetStyle(grlinclNanoUN_Rank1t8_17, 2, kGreen+1, kOpenSquare, 2.1);
  SetStyle(grlinclNanoUN_Rank1t8_17_21, 2, kOrange+2, kOpenSquare, 2.1);
  //SetStyle(grlinclNanoUN_Rank1t8_17_21_24, 3, kOrange+2, kOpenSquare, 2.1);
  SetStyle(grlinclNanoUN_Rank1t8_17_21_24, 3, kBlack, kOpenSquare, 2.1);
  
  //TLegend* leg = new TLegend(0.12,0.79,0.73,0.86,NULL,"brNDC"); //Upper part
  TLegend* leg = new TLegend(0.12,0.16,0.73,0.28,NULL,"brNDC"); //lower part
  leg->SetBorderSize(0);
  leg->SetTextSize(0.05);
  leg->SetFillColor(0);
  leg->SetTextSize(0.019);
  leg->AddEntry(grlexclMini,"Published:Unblinded:Excl:MiniAOD #mu+jets, lnN, 2016","LP");
  leg->AddEntry(grlexclMiniInc,"Published:Unblinded:InclKF:MiniAOD #mu+jets, lnN, 2016","LP");
  leg->AddEntry(grlexclMEqv16lnN, "Current:Blinded:InclKF:Nano #mu+jets, lnN, 2016","LP"); //01
  leg->AddEntry(grlexclMEqv16shape, "Current:Blinded:InclKF:Nano #mu+jets, shape, 2016","LP");
  
  //leg->AddEntry(grlexclMEqv16lnN, "Current:Blinded:InclKF:NanoAOD #mu+jets, lnN, 2016","LP"); //01
  //leg->AddEntry(grlexclMEqv16shape, "Current:Blinded:InclKF:NanoAOD #mu+jets, shape, 2016","LP");
  //leg->AddEntry(grlinclNanoUnNorm, "Current:Blinded:InclKF:NanoAOD #mu+jets, shape, 2016","LP");
  //leg->AddEntry(grlinclNanoUN_Rank1, "Current:Blinded:InclKF:NanoAOD #mu+jets, shape, rank1#rightarrow lnN, 2016","LP");
  //leg->AddEntry(grlinclNanoUN_Rank13, "Current:Blinded:InclKF:NanoAOD #mu+jets, shape, rank1-3#rightarrow lnN, 2016","LP");
  //leg->AddEntry(grlinclNanoUN_Rank134, "Current:Blinded:InclKF:NanoAOD #mu+jets, shape, rank1-4#rightarrow lnN, 2016","LP");
  //leg->AddEntry(grlinclNanoUN_Rank1345, "Current:Blinded:InclKF:NanoAOD #mu+jets, shape, rank1-5#rightarrow lnN, 2016","LP");
  //leg->AddEntry(grlinclNanoUN_Rank13456, "Current:Blinded:InclKF:NanoAOD #mu+jets, shape, rank1-6#rightarrow lnN, 2016","LP");
  //leg->AddEntry(grlinclNanoUN_Rank134567, "Current:Blinded:InclKF:NanoAOD #mu+jets, shape, rank1-7#rightarrow lnN, 2016","LP");
  // leg->AddEntry(grlinclNanoUN_Rank1345678, "Current:Blinded:InclKF:NanoAOD #mu+jets, shape, rank1-8#rightarrow lnN, 2016","LP");
  // leg->AddEntry(grlinclNanoUN_Rank1t8_17, "Current:Blinded:InclKF:NanoAOD #mu+jets, shape, rank1-9#rightarrow lnN, 2016","LP");
  // leg->AddEntry(grlinclNanoUN_Rank1t8_17_21, "Current:Blinded:InclKF:NanoAOD #mu+jets, shape, rank1-10#rightarrow lnN, 2016","LP");
  //leg->AddEntry(grlinclNanoUN_Rank1t8_17_21_24, "Current:Blinded:InclKF:NanoAOD #mu+jets, shape, rank1-11#rightarrow lnN, 2016","LP");
  //leg->AddEntry(grlinclNanoUN_Rank1t8_17_21_24, "Current:Blinded:InclKF:NanoAOD #mu+jets, lnN, theory#rightarrow shape, 2016","LP");
  //leg->AddEntry(grlinclNanoUN_Rank1t8_17_21_24, "Current:Blinded:InclKF:NanoAOD #mu+jets, lnN, bcsyst#rightarrow shape, 2016","LP");
  //leg->AddEntry(grlinclNanoUN_Rank1t8_17_21_24, "Current:Blinded:InclKF:MiniAOD Equivalent  #mu+jets, lnN, bsyst#rightarrow shape, 2016","LP");
  leg->AddEntry(grlinclNanoUN_Rank1t8_17_21_24, "Current:Blinded:InclKF:Nano #mu+jets, lnN, (FSR,JES,mtop)#rightarrow shape, 2016","LP");

  // leg->AddEntry(grlexclMEqv16lnN, "Current:Blinded:Excl:NanoAOD l+jets, shape, 2016","LP");
  // leg->AddEntry(grlexclMEqv16shape, "Current:Blinded:Excl:NanoAOD l+jets, shape, 2017","LP");
  // leg->AddEntry(grlexclNano16, "Current:Blinded:Excl:NanoAOD l+jets, shape, 2018","LP");
  // leg->AddEntry(grlexclNano, "Current:Blinded:Excl:NanoAOD l+jets, shape, Run2","LP");
  // leg->AddEntry(grlexclNano16, "(NanoAOD l+jets, shapes, 2016)","LP");
  
  grlexclMini->SetMaximum(10.0);
  grlexclMini->SetMinimum(5.0e-2);
  grlexclMini->GetXaxis()->SetTitleOffset(1.2);
  grlexclMini->GetYaxis()->SetTitleOffset(1.2);
  grlexclMini->GetXaxis()->SetTitle("M_{H^{#pm}} (GeV)");
  grlexclMini->GetYaxis()->SetTitle("BR(t#rightarrow H^{#pm}b) (%)");
  grlexclMini->SetTitle("Comparison of expected values of median");
  TCanvas *c1 = new TCanvas("c1","c1", 800,800);
  c1->SetLogy();
  c1->SetTickx();
  c1->SetTicky();
  grlexclMini->Draw("ALP");
  grlexclMiniInc->Draw("LP");
  grlexclMEqv16lnN->Draw("LP");
  grlexclMEqv16shape->Draw("LP");
  // grlexclNano16->Draw("LP");
  // grlexclNano->Draw("LP");
  //grlinclNanoUnNorm->Draw("LP");
  //grlinclNanoUN_Rank1->Draw("LP");
  //grlinclNanoUN_Rank13->Draw("LP"); //Sig effect
  // grlinclNanoUN_Rank134->Draw("LP");
  //grlinclNanoUN_Rank1345->Draw("LP");
  //grlinclNanoUN_Rank13456->Draw("LP"); //Sig effect
  //grlinclNanoUN_Rank134567->Draw("LP");
  //grlinclNanoUN_Rank1345678->Draw("LP");
  // grlinclNanoUN_Rank1t8_17->Draw("LP");
  // grlinclNanoUN_Rank1t8_17_21->Draw("LP"); //Sig effect
  grlinclNanoUN_Rank1t8_17_21_24->Draw("LP");
  
  leg->Draw();
  
  lexclMini.clear();
  lexclMEqv16lnN.clear();
  lexclMEqv16shape.clear();
  lexclNano16.clear();
  lexclNano.clear();

  linclNanoUnNorm.clear();
  linclNanoUN_Rank1.clear();
  linclNanoUN_Rank13.clear();
  linclNanoUN_Rank134.clear();
  linclNanoUN_Rank1345.clear();
  linclNanoUN_Rank13456.clear();
  linclNanoUN_Rank134567.clear();
  linclNanoUN_Rank1345678.clear();
  linclNanoUN_Rank1t8_17.clear();
  linclNanoUN_Rank1t8_17_21.clear();
  linclNanoUN_Rank1t8_17_21_24.clear();

}
