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
  int PlotRatio(TGraph *, TGraph *, TGraph *, TLegend *, const char *);
  
  vector<LimitPoints> lexclMini;
  vector<LimitPoints> lexclMiniInc;
  vector<LimitPoints> lexclMEqv16lnN;
  vector<LimitPoints> lexclMEqv16shape;
  vector<LimitPoints> lexclNano16;
  vector<LimitPoints> lexclNano;
  
  
  //01
  // ReadLimitMiniAOD(lexclMini, "hig-18-021/PublishedPRD/ForANv12/mu_ele/Cat3_cTagEx");
  // ReadLimitNanoAOD(lexclMEqv16lnN, "TIFRAPAR-2023-01-15/01_yearend22-MiniAODEqv/Run2/Comb", "mu_ele");

  //02
  ReadLimitMiniAOD(lexclMini, "hig-18-021/PublishedPRD/ForANv12/mu_ele/Cat3_cTagEx");
  ReadLimitNanoAOD(lexclMEqv16lnN, "TIFRAPAR-2023-01-15/01_yearend22-MiniAODEqv/2016/Comb", "mu_ele");
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



  //ReadLimitMiniAOD(lexclMini, "hig-18-021/PublishedPRD/ForANv12/mu/Cat3_cTagEx");
  ReadLimitMiniAOD(lexclMiniInc, "hig-18-021/PublishedPRD/ForANv12/mu/Cat1_Inc");


  ReadLimitNanoAOD(lexclMEqv16shape, "TIFRAPAR-2023-01-15/09_elereliso-NanoAOD_Shapes/2016/Incl", "mu");
  ReadLimitNanoAOD(lexclNano16, "TIFRAPAR-2023-01-15/22_elereliso_bld_unNorm_cmdMiniAOD_7Shapes_RD/2016/Comb", "mu");
  //ReadLimitNanoAOD(lexclNano, "TIFRAPAR-2023-01-15/28_elereliso_bld_7Shapes_bcStat_lnN/Default_lnN/2016/Comb", "mu");
  //ReadLimitNanoAOD(lexclMEqv16lnN, "TIFRAPAR-2023-01-15/28_elereliso_bld_7Shapes_bcStat_lnN/bcStat_15prcnt/2016/Comb", "mu");
  //ReadLimitNanoAOD(lexclNano, "TIFRAPAR-2023-01-15/44_trigSF_impacts_bld_excLMT/Run2/Comb", "mu_ele");
  //ReadLimitNanoAOD(lexclNano, "TIFRAPAR-2023-01-15/65_JECSplit_bld_all_uncorr_7Shapes_HighQCDSyst/2016/Comb", "mu_ele");
  //ReadLimitNanoAOD(lexclNano, "TIFRAPAR-2023-01-15/66_jetpt15_bld_all_uncorr_7Shapes/2016/Comb", "mu_ele");
  //ReadLimitNanoAOD(lexclNano, "TIFRAPAR-2023-01-15/67_JECSplit_bld_all_uncorr_all_lnN_HighQCDSyst/2016/Comb", "mu_ele");
  ReadLimitNanoAOD(lexclNano, "TIFRAPAR-2023-01-15/68_jetpt15_bld_all_uncorr_all_lnN/2016/Comb", "mu_ele");
  
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
    
  }

  TGraph *grMiniByNano = new TGraph(int(lexclMini.size()));
  for(int i = 0; i < int(lexclMini.size()) ; i++){
    for(int j = 0; j < int(lexclMEqv16lnN.size()) ; j++){
      if(lexclMini[i].mX==lexclMEqv16lnN[j].mX){
	//cout <<"Mass : " << lexclMini[i].mX << ", MiniPublished : "<<lexclMini[i].expY<<", NanoMiniEqv : "<<lexclMEqv16lnN[j].expY<<", MiniByNano : "<<(lexclMini[i].expY/lexclMEqv16lnN[j].expY) << endl;
	//grMiniByNano->SetPoint(i,lexclMini[i].mX, (lexclMini[i].expY/lexclMEqv16lnN[j].expY));
	grMiniByNano->SetPoint(i,lexclMini[i].mX, (lexclNano[j].expY/lexclMini[i].expY));
	printf("%3.0f | %5.2f\% | %5.2f\% | %5.2f \n",lexclMini[i].mX,lexclMini[i].expY,lexclMEqv16lnN[j].expY,(lexclMini[i].expY/lexclMEqv16lnN[j].expY));
      }
    }
  }
  
  SetStyle(grlexclMini, 3,kBlue, kFullCircle,1.2);
  SetStyle(grlexclMiniInc, 3,kRed, kOpenCircle,1.2);
  SetStyle(grlexclMEqv16lnN, 3,kMagenta, kFullSquare,1.2);
  //SetStyle(grlexclMEqv16lnN, 2,kMagenta, kFullDoubleDiamond,3.2);
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

  SetStyle(grMiniByNano, 3, kRed, kFullSquare,1.2);
  
  //TLegend* leg = new TLegend(0.12,0.79,0.73,0.86,NULL,"brNDC"); //Upper part
  TLegend* leg = new TLegend(0.12,0.16,0.73,0.28,NULL,"brNDC"); //lower part
  leg->SetBorderSize(0);
  leg->SetTextSize(0.05);
  leg->SetFillColor(0);
  leg->SetTextSize(0.019);
  leg->AddEntry(grlexclMini,"Published l+jets, lnN, 2016","LP");
  // leg->AddEntry(grlexclMiniInc,"Published:Unblinded:InclKF:MiniAOD #mu+jets, lnN, 2016","LP");
  // leg->AddEntry(grlexclMEqv16lnN, "Current:Blinded:InclKF:Nano #mu+jets, lnN, 2016","LP"); //01
  // leg->AddEntry(grlexclMEqv16shape, "Current:Blinded:InclKF:Nano #mu+jets, shape, 2016","LP");
  
  //leg->AddEntry(grlexclMEqv16lnN, "Current:Blinded:InclKF:NanoAOD #mu+jets, lnN, 2016","LP"); //01
  //leg->AddEntry(grlexclMEqv16shape, "Current:Blinded:InclKF:NanoAOD #mu+jets, shape, 2016","LP");

  //leg->AddEntry(grlexclMEqv16lnN, "Current(UL):Blinded l+jets, lnN, 2016","LP");
  // leg->AddEntry(grlexclMEqv16shape, "Current:Blinded:Excl:NanoAOD l+jets, shape, 2017","LP");
  // leg->AddEntry(grlexclNano16, "Current:Blinded:Excl:NanoAOD l+jets, shape, 2018","LP");
  //leg->AddEntry(grlexclNano16, "NanoAOD : bcstat shape, 2016 (#mu+jets)","LP");
  leg->AddEntry(grlexclNano, "Current l+jets, lnN+shape, Run2","LP");
  //leg->AddEntry(grlexclMEqv16lnN, "NanoAOD : bcstat lnN, 2016 (#mu+jets) : 15%","LP");

  grlexclMini->SetMaximum(10.0);
  grlexclMini->SetMinimum(5.0e-2);
  grlexclMini->GetXaxis()->SetTitleOffset(1.2);
  grlexclMini->GetYaxis()->SetTitleOffset(1.2);
  grlexclMini->GetXaxis()->SetTitle("M_{H^{#pm}} (GeV)");
  grlexclMini->GetYaxis()->SetTitle("BR(t#rightarrow H^{#pm}b) (%)");
  grlexclMini->SetTitle("Comparison of expected values of median");

  // TCanvas *c1 = new TCanvas("c1","c1", 800,800);
  // c1->SetLogy();
  // c1->SetTickx();
  // c1->SetTicky();
  // grlexclMini->Draw("ALP");
  // // grlexclMiniInc->Draw("LP");
  // //grlexclMEqv16lnN->Draw("LP");
  // // grlexclMEqv16shape->Draw("LP");
  // //grlexclNano16->Draw("LP");
  // grlexclNano->Draw("LP");
  // //grlexclMEqv16lnN->Draw("LP");

  // leg->Draw();

  // TLegend* leg2 = new TLegend(0.12,0.16,0.73,0.28,NULL,"brNDC"); //lower part
  // leg2->SetBorderSize(0);
  // leg2->SetTextSize(0.05);
  // leg2->SetFillColor(0);
  // leg2->SetTextSize(0.019);
  // leg2->AddEntry(grMiniByNano,"Published/Current(UL) l+jets, lnN, 2016","LP");

  // grMiniByNano->SetMaximum(3.2);
  // grMiniByNano->SetMinimum(0.0);
  // grMiniByNano->GetXaxis()->SetTitleOffset(1.2);
  // grMiniByNano->GetYaxis()->SetTitleOffset(1.2);
  grMiniByNano->GetXaxis()->SetTitle("M_{H^{#pm}} (GeV)");
  // grMiniByNano->GetYaxis()->SetTitle("Ratio of BR(t#rightarrow H^{#pm}b) (%)");
  // grMiniByNano->SetTitle("Ratio of expected values of median");
  // TCanvas *c2 = new TCanvas("c2","c2", 800,800);
  // c2->SetTickx();
  // c2->SetTicky();
  // grMiniByNano->Draw("ALP");
  // leg2->Draw();

  PlotRatio(grlexclMini, grlexclNano, grMiniByNano, leg, "c3");
  
  // lexclMini.clear();
  // lexclMEqv16lnN.clear();
  // lexclMEqv16shape.clear();
  // lexclNano16.clear();
  // lexclNano.clear();


}

int PlotRatio(TGraph *gr1, TGraph *gr2, TGraph *grRatio, TLegend *leg, const char *cname)
{
  cout<<"gr1 name : "<<gr1->GetName()
      <<", gr2 : " << gr2->GetName()
      <<", grRatio : " << grRatio->GetName()
      << endl;

  TCanvas *canvas = (TCanvas *)gROOT->GetListOfCanvases()->FindObject(cname);
  
  if(!canvas){
    TCanvas *c = new TCanvas(cname, cname, 800, 800);
 
    // Upper plot will be in pad1
    TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
    pad1->SetBottomMargin(0.01); // Upper and lower plot are joined
    //pad1->SetGridx();         // Vertical grid
    pad1->Draw();             // Draw the upper pad: pad1
    pad1->cd();               // pad1 becomes the current pad
    pad1->SetTickx();
    pad1->SetTicky();
    pad1->SetLogy();
    //gr1->SetStats(0);          // No statistics on upper plot
    gr1->Draw("ALP");               // Draw gr1
    gr2->Draw("LP");         // Draw gr2 on top of gr1
    leg->Draw();
#if ROOT_VERSION_CODE >= ROOT_VERSION(6,8,0)
    // Avoid the first label (0) to be clipped.
    TAxis *axis = gr1->GetYaxis();
    axis->ChangeLabel(1, -1, -1, -1, -1, -1, " ");
    axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    axis->SetLabelSize(20);
    TAxis *axisX = gr1->GetXaxis();
    axisX->SetLabelOffset(1.2);
#else
    // Do not draw the Y axis label on the upper plot and redraw a small
    // axis instead, in order to avoid the first label (0) to be clipped.
    gr1->GetYaxis()->SetLabelSize(0.);
    TGaxis *axis = new TGaxis( -5, 20, -5, 220, 20,220,510,"");
    axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    axis->SetLabelSize(15);
    axis->Draw();
#endif
 
    // lower plot will be in pad
    c->cd();          // Go back to the main canvas before defining pad2
    TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
    pad2->SetTopMargin(0.1);
    pad2->SetBottomMargin(0.2);
    pad2->SetGridx(); // vertical grid
    pad2->SetGridy(); // vertical grid
    pad2->Draw();
    pad2->cd();       // pad2 becomes the current pad
    pad2->SetTickx();
    pad2->SetTicky();
 
    // Define the ratio plot
    grRatio->SetLineColor(kBlack);

    //grRatio->SetStats(0);      // No statistics on lower plot

    
    grRatio->SetMinimum(0.0);  // Define Y ..
    grRatio->SetMaximum(2.0); // .. range
    
    grRatio->Draw("ALP");       // Draw the ratio plot
    
    // Y axis gr1 plot settings
    //gr1->GetYaxis()->SetTitle("");
    gr1->GetYaxis()->SetTitleSize(20);
    gr1->GetYaxis()->SetTitleFont(43);
    gr1->GetYaxis()->SetTitleOffset(1.55);
 
    grRatio->SetTitle(""); // Remove the ratio title
 
    // Y axis ratio plot settings
    grRatio->GetYaxis()->SetTitle("#frac{Current}{Published}");
    grRatio->GetYaxis()->SetNdivisions(505);
    grRatio->GetYaxis()->SetTitleSize(20);
    grRatio->GetYaxis()->SetTitleFont(43);
    grRatio->GetYaxis()->SetTitleOffset(1.55);
    grRatio->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    grRatio->GetYaxis()->SetLabelSize(20);
 
    // X axis ratio plot settings
    //grRatio->GetXaxis()->SetTitle("m_{jj} (GeV)");
    grRatio->GetXaxis()->SetTitleSize(20);
    grRatio->GetXaxis()->SetTitleFont(43);
    grRatio->GetXaxis()->SetTitleOffset(3.2);
    grRatio->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    grRatio->GetXaxis()->SetLabelSize(20);
    
    pad1->cd();

    cout<<" nof canvas primitives " << c->GetListOfPrimitives()->GetEntries() << endl ;
    
  }

  return true;
}
