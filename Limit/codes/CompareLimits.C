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

void ReadLimitNanoAOD14MP(vector<LimitPoints>& Val, TString indir = "", TString ch = "mu_ele")
{

  float X[]        = {40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 155, 160};
  float obsY[]     = {0., 0.,0.,0, 0., 0.,0.,0, 0, 0, 0, 0, 0, 0};
  float expY[]     = {0., 0.,0.,0, 0., 0.,0.,0, 0, 0, 0, 0, 0, 0};
		      
  float expY1sL[]   = {0., 0.,0.,0, 0., 0.,0.,0, 0, 0, 0, 0, 0, 0};
  float expY1sH[]   = {0., 0.,0.,0, 0., 0.,0.,0, 0, 0, 0, 0, 0, 0};		      
  float expY2sL[]  = {0., 0.,0.,0, 0., 0.,0.,0, 0, 0, 0, 0, 0, 0};
  float expY2sH[]  = {0., 0.,0.,0, 0., 0.,0.,0, 0, 0, 0, 0, 0, 0};

  int nMassPoints = 14;
  
  TString massFiles [14] = {
			   "Mass40/higgsCombine_hcs_13TeV_"+ch+"_Cat1_Inc.AsymptoticLimits.mH40.root",
			   "Mass50/higgsCombine_hcs_13TeV_"+ch+"_Cat1_Inc.AsymptoticLimits.mH50.root",
			   "Mass60/higgsCombine_hcs_13TeV_"+ch+"_Cat1_Inc.AsymptoticLimits.mH60.root",
			   "Mass70/higgsCombine_hcs_13TeV_"+ch+"_Cat1_Inc.AsymptoticLimits.mH70.root",
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


void ReadLimitNanoAOD14MPN(vector<LimitPoints>& Val, TString indir = "", TString ch = "mu_ele")
{

  float X[]        = {40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 155, 160};
  float obsY[]     = {0., 0.,0.,0, 0., 0.,0.,0, 0, 0, 0, 0, 0, 0};
  float expY[]     = {0., 0.,0.,0, 0., 0.,0.,0, 0, 0, 0, 0, 0, 0};
		      
  float expY1sL[]   = {0., 0.,0.,0, 0., 0.,0.,0, 0, 0, 0, 0, 0, 0};
  float expY1sH[]   = {0., 0.,0.,0, 0., 0.,0.,0, 0, 0, 0, 0, 0, 0};		      
  float expY2sL[]  = {0., 0.,0.,0, 0., 0.,0.,0, 0, 0, 0, 0, 0, 0};
  float expY2sH[]  = {0., 0.,0.,0, 0., 0.,0.,0, 0, 0, 0, 0, 0, 0};

  int nMassPoints = 14;
  
  TString massFiles [14] = {
			   "Mass40/higgsCombine_hcs_13TeV_"+ch+"_Cat1_Inc.AsymptoticLimits.mH40.12543.root",
			   "Mass50/higgsCombine_hcs_13TeV_"+ch+"_Cat1_Inc.AsymptoticLimits.mH50.12543.root",
			   "Mass60/higgsCombine_hcs_13TeV_"+ch+"_Cat1_Inc.AsymptoticLimits.mH60.12543.root",
			   "Mass70/higgsCombine_hcs_13TeV_"+ch+"_Cat1_Inc.AsymptoticLimits.mH70.12543.root",
			   "Mass80/higgsCombine_hcs_13TeV_"+ch+"_Cat1_Inc.AsymptoticLimits.mH80.12543.root",
			   "Mass90/higgsCombine_hcs_13TeV_"+ch+"_Cat1_Inc.AsymptoticLimits.mH90.12543.root",
			   "Mass100/higgsCombine_hcs_13TeV_"+ch+"_Cat1_Inc.AsymptoticLimits.mH100.12543.root",
			   "Mass110/higgsCombine_hcs_13TeV_"+ch+"_Cat1_Inc.AsymptoticLimits.mH110.12543.root",
			   "Mass120/higgsCombine_hcs_13TeV_"+ch+"_Cat1_Inc.AsymptoticLimits.mH120.12543.root",
			   "Mass130/higgsCombine_hcs_13TeV_"+ch+"_Cat1_Inc.AsymptoticLimits.mH130.12543.root",
			   "Mass140/higgsCombine_hcs_13TeV_"+ch+"_Cat1_Inc.AsymptoticLimits.mH140.12543.root",
			   "Mass150/higgsCombine_hcs_13TeV_"+ch+"_Cat1_Inc.AsymptoticLimits.mH150.12543.root",
			   "Mass155/higgsCombine_hcs_13TeV_"+ch+"_Cat1_Inc.AsymptoticLimits.mH155.12543.root",
			   "Mass160/higgsCombine_hcs_13TeV_"+ch+"_Cat1_Inc.AsymptoticLimits.mH160.12543.root"
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

void ReadLimitNanoAOD14MPMVA(vector<LimitPoints>& Val, TString indir = "", TString ch = "mu_ele")
{

  float X[]        = {40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 155, 160};
  float obsY[]     = {0., 0.,0.,0, 0., 0.,0.,0, 0, 0, 0, 0, 0, 0};
  float expY[]     = {0., 0.,0.,0, 0., 0.,0.,0, 0, 0, 0, 0, 0, 0};
		      
  float expY1sL[]   = {0., 0.,0.,0, 0., 0.,0.,0, 0, 0, 0, 0, 0, 0};
  float expY1sH[]   = {0., 0.,0.,0, 0., 0.,0.,0, 0, 0, 0, 0, 0, 0};		      
  float expY2sL[]  = {0., 0.,0.,0, 0., 0.,0.,0, 0, 0, 0, 0, 0, 0};
  float expY2sH[]  = {0., 0.,0.,0, 0., 0.,0.,0, 0, 0, 0, 0, 0, 0};

  int nMassPoints = 14;
  
  TString massFiles [14] = {
			   "higgsCombineTest.AsymptoticLimits.mH40.root",
			   "higgsCombineTest.AsymptoticLimits.mH50.root",
			   "higgsCombineTest.AsymptoticLimits.mH60.root",
			   "higgsCombineTest.AsymptoticLimits.mH70.root",
			   "higgsCombineTest.AsymptoticLimits.mH80.root",
			   "higgsCombineTest.AsymptoticLimits.mH90.root",
			   "higgsCombineTest.AsymptoticLimits.mH100.root",
			   "higgsCombineTest.AsymptoticLimits.mH110.root",
			   "higgsCombineTest.AsymptoticLimits.mH120.root",
			   "higgsCombineTest.AsymptoticLimits.mH130.root",
			   "higgsCombineTest.AsymptoticLimits.mH140.root",
			   "higgsCombineTest.AsymptoticLimits.mH150.root",
			   "higgsCombineTest.AsymptoticLimits.mH155.root",
			   "higgsCombineTest.AsymptoticLimits.mH160.root"
  };

  
  for(unsigned int i = 0 ; i < UInt_t(nMassPoints); i++){
    TFile f(indir+"/"+ch+"/"+massFiles[i],"READ"); // higgsCombine_hcs_13TeV_mu.AsymptoticLimits.mH140.root
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

int CompareLimits(){
  
  void SetStyle(TGraph*&, Width_t, Color_t, Style_t, Size_t);
  void ReadLimitMiniAOD(vector<LimitPoints>&, TString);
  void ReadLimitNanoAOD(vector<LimitPoints>&, TString, TString);
  void ReadLimitNanoAOD14MP(vector<LimitPoints>&, TString, TString);
  void ReadLimitNanoAOD14MPMVA(vector<LimitPoints>&, TString, TString);
  void ReadLimitNanoAOD14MPN(vector<LimitPoints>&, TString, TString);
  int PlotRatio(TGraph *, TGraph *, TGraph *, TLegend *, const char *);
  int PlotRatio(TGraph *, TGraph *, TGraph *, TGraph *, TGraph *, TGraph *, TGraph *, TLegend *, const char *);
  
  vector<LimitPoints> lexclMini;
  vector<LimitPoints> lexclMiniInc;
  vector<LimitPoints> lexclMEqv16lnN;
  vector<LimitPoints> lexclMEqv16shape;
  vector<LimitPoints> lexclNano16;
  vector<LimitPoints> lexclNano;
  vector<LimitPoints> lexclNanoMVA;
  vector<LimitPoints> lexclNanoShape;
  vector<LimitPoints> lexclNanolnN;
  
  
  //01
  // ReadLimitMiniAOD(lexclMini, "hig-18-021/PublishedPRD/ForANv12/mu_ele/Cat3_cTagEx");
  // ReadLimitNanoAOD(lexclMEqv16lnN, "TIFRAPAR-2023-01-15/01_yearend22-MiniAODEqv/Run2/Comb", "mu_ele");

  //02
  ReadLimitMiniAOD(lexclMini, "hig-18-021/PublishedPRD/ForANv12/mu_ele/Cat3_cTagEx");
  ReadLimitMiniAOD(lexclMiniInc, "hig-18-021/PublishedPRD/ForANv12/mu/Cat1_Inc");
  // ReadLimitNanoAOD(lexclMEqv16lnN, "TIFRAPAR-2023-01-15/01_yearend22-MiniAODEqv/2016/Comb", "mu_ele");
  // ReadLimitNanoAOD(lexclMEqv16shape, "TIFRAPAR-2023-01-15/09_elereliso-NanoAOD_Shapes/2016/Incl", "mu");
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


  //// The following two inputs are defined above.
  // ReadLimitMiniAOD(lexclMini, "hig-18-021/PublishedPRD/ForANv12/mu_ele/Cat3_cTagEx");
  // ReadLimitMiniAOD(lexclMiniInc, "hig-18-021/PublishedPRD/ForANv12/mu/Cat1_Inc");
  // ReadLimitNanoAOD(lexclMEqv16lnN, "TIFRAPAR-2023-01-15/01_yearend22-MiniAODEqv/2016/Comb", "mu_ele");
  // ReadLimitNanoAOD(lexclMEqv16shape, "TIFRAPAR-2023-01-15/09_elereliso-NanoAOD_Shapes/2016/Incl", "mu");

  
  //ReadLimitNanoAOD(lexclNano, "TIFRAPAR-2023-01-15/28_elereliso_bld_7Shapes_bcStat_lnN/Default_lnN/2016/Comb", "mu");
  //ReadLimitNanoAOD(lexclMEqv16lnN, "TIFRAPAR-2023-01-15/28_elereliso_bld_7Shapes_bcStat_lnN/bcStat_15prcnt/2016/Comb", "mu");
  //ReadLimitNanoAOD(lexclNano, "TIFRAPAR-2023-01-15/44_trigSF_impacts_bld_excLMT/Run2/Comb", "mu_ele");
  //ReadLimitNanoAOD(lexclNano, "TIFRAPAR-2023-01-15/65_JECSplit_bld_all_uncorr_7Shapes_HighQCDSyst/2016/Comb", "mu_ele");
  //ReadLimitNanoAOD(lexclNano, "TIFRAPAR-2023-01-15/66_jetpt15_bld_all_uncorr_7Shapes/2016/Comb", "mu_ele");
  //ReadLimitNanoAOD(lexclNano, "TIFRAPAR-2023-01-15/67_JECSplit_bld_all_uncorr_all_lnN_HighQCDSyst/2016/Comb", "mu_ele");
  //ReadLimitNanoAOD(lexclNano, "TIFRAPAR-2023-01-15/68_jetpt15_bld_all_uncorr_all_lnN/2016/Comb", "mu_ele");

  //ReadLimitNanoAOD(lexclMEqv16lnN, "TIFRAPAR-2023-01-15/57_JECSplit_bld_all_uncorr_7Shapes/2016/Comb", "mu_ele");
  //ReadLimitNanoAOD(lexclMEqv16shape, "TIFRAPAR-2023-01-15/68_jetpt15_bld_all_uncorr_all_lnN/2016/Comb", "mu_ele");
  // ReadLimitNanoAOD(lexclNano16, "TIFRAPAR-2023-01-15/70_jetpt15-chi2lt2_bld_all_uncorr_all_lnN/2016/Comb", "mu_ele");
  // ReadLimitNanoAOD(lexclNano, "TIFRAPAR-2023-01-15/71_jetpt15-chi2gt2_bld_all_uncorr_all_lnN/2016/Comb", "mu_ele");
  // ReadLimitNanoAOD(lexclNano16, "TIFRAPAR-2023-01-15/72_jetpt15-nj4nbj2_bld_all_uncorr_all_lnN/2016/Comb", "mu_ele");
  // ReadLimitNanoAOD(lexclNano, "TIFRAPAR-2023-01-15/73_jetpt15-njn4nbjn2_bld_all_uncorr_all_lnN/2016/Comb", "mu_ele");
  // ReadLimitNanoAOD(lexclNano16, "TIFRAPAR-2023-01-15/74_jetpt15-lowptheta_bld_all_uncorr_all_lnN/2016/Comb", "mu_ele");
  // ReadLimitNanoAOD(lexclNano, "TIFRAPAR-2023-01-15/75_jetpt15-highptheta_bld_all_uncorr_all_lnN/2016/Comb", "mu_ele");
  //ReadLimitNanoAOD(lexclMEqv16shape, "TIFRAPAR-2023-01-15/66_jetpt15_bld_all_uncorr_7Shapes/2016/Comb", "mu_ele");
  //ReadLimitNanoAOD(lexclNano16, "TIFRAPAR-2023-01-15/76_jetpt15-ptcut20_bld_all_uncorr_7Shapes/2016/Comb", "mu_ele");
  //ReadLimitNanoAOD(lexclNano, "TIFRAPAR-2023-01-15/77_jetpt15-ptcut25_bld_all_uncorr_7Shapes/2016/Comb", "mu_ele");
  //ReadLimitNanoAOD(lexclNano, "TIFRAPAR-2023-01-15/91_no-dijet-edge-effect_bld/Run2/Comb", "mu_ele");
  
  ReadLimitNanoAOD14MP(lexclNano, "TIFRAPAR-2023-01-15/91_no-dijet-edge-effect_bld/Run2/Comb", "mu_ele");
  ReadLimitNanoAOD14MPN(lexclNanoShape, "Imperial-PA-2024-10-08/10_mixed_MVA_lnNfixed/Run2/Comb", "mu_ele");
  //ReadLimitNanoAOD14MPMVA(lexclNanoMVA, "savarghe/HplusDatacardsNew/FullRun2/", "lep");
  ReadLimitNanoAOD14MPMVA(lexclNanoMVA, "savarghe/HplusDatacards/FullRun2/", "lep");
  
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
  // TGraph *grlexclMEqv16lnN = new TGraph(int(lexclMEqv16lnN.size()));
  // TGraph *grlexclMEqv16shape = new TGraph(int(lexclMEqv16shape.size()));
  // TGraph *grlexclNano16 = new TGraph(int(lexclNano16.size()));
  // TGraph *grlexclNano = new TGraph(int(lexclNano.size()));
  TGraph *grlexclNanoShape = new TGraph(int(lexclNanoShape.size()));
  TGraph *grlexclNanoShape1sL = new TGraph(int(lexclNanoShape.size()));
  TGraph *grlexclNanoShape2sL = new TGraph(int(lexclNanoShape.size()));
  TGraph *grlexclNanoShape1sH = new TGraph(int(lexclNanoShape.size()));
  TGraph *grlexclNanoShape2sH = new TGraph(int(lexclNanoShape.size()));
  TGraph *grlexclNano = new TGraph(int(lexclNano.size()));
  TGraph *grlexclNanoMVA = new TGraph(int(lexclNanoMVA.size()));


  // cout << "lexclMEqv16lnN.size : " << lexclMEqv16lnN.size() << endl;
  // cout << "lexclMEqv16shape.size : " << lexclMEqv16shape.size() << endl;
  // cout << "lexclNano16.size : " << lexclNano16.size() << endl;
  // for(int i = 0; i < int(lexclMEqv16lnN.size()) ; i++){
  //   printf("X : %3.0f, Y : %5.2f\%\n",lexclMEqv16lnN[i].mX, lexclMEqv16lnN[i].expY);
  //   //printf("X : %3.0f, Y : %5.2f\%\n",lexclMEqv16shape[i].mX, lexclMEqv16shape[i].expY);
  //   grlexclMEqv16lnN->SetPoint(i,lexclMEqv16lnN[i].mX, lexclMEqv16lnN[i].expY);
  //   grlexclMEqv16shape->SetPoint(i,lexclMEqv16shape[i].mX, lexclMEqv16shape[i].expY);
  //   grlexclNano16->SetPoint(i,lexclNano16[i].mX, lexclNano16[i].expY);
  //   grlexclNano->SetPoint(i,lexclNano[i].mX, lexclNano[i].expY);    
  // }

  
  
  cout << "lexclNano16.size : " << lexclNanoShape.size() << endl;
  for(int i = 0; i < int(lexclNanoShape.size()) ; i++){
    printf("X : %3.0f, Y : %5.2f\%\n",lexclNanoShape[i].mX, lexclNanoShape[i].expY);
    grlexclNanoShape->SetPoint(i,lexclNanoShape[i].mX, lexclNanoShape[i].expY);
    grlexclNanoShape1sL->SetPoint(i,lexclNanoShape[i].mX, lexclNanoShape[i].expY1sL);
    grlexclNanoShape2sL->SetPoint(i,lexclNanoShape[i].mX, lexclNanoShape[i].expY2sL);
    grlexclNanoShape1sH->SetPoint(i,lexclNanoShape[i].mX, lexclNanoShape[i].expY1sH);
    grlexclNanoShape2sH->SetPoint(i,lexclNanoShape[i].mX, lexclNanoShape[i].expY2sH);
    grlexclNano->SetPoint(i,lexclNano[i].mX, lexclNano[i].expY);
    grlexclNanoMVA->SetPoint(i,lexclNano[i].mX, lexclNanoMVA[i].expY);
  }
  
  TGraph *grMiniByNano = new TGraph(int(lexclMini.size()));
  for(int i = 0; i < int(lexclMini.size()) ; i++){
    for(int j = 0; j < int(lexclNanoShape.size()) ; j++){
      if(lexclMini[i].mX==lexclNanoShape[j].mX){
  	//cout <<"Mass : " << lexclMini[i].mX << ", MiniPublished : "<<lexclMini[i].expY<<", NanoMiniEqv : "<<lexclMEqv16lnN[j].expY<<", MiniByNano : "<<(lexclMini[i].expY/lexclMEqv16lnN[j].expY) << endl;
  	//grMiniByNano->SetPoint(i,lexclMini[i].mX, (lexclMini[i].expY/lexclMEqv16lnN[j].expY));
  	//grMiniByNano->SetPoint(i,lexclMini[i].mX, (lexclNano[j].expY/lexclMini[i].expY));
	grMiniByNano->SetPoint(i,lexclMini[i].mX, (lexclNanoShape[j].expY/lexclMini[i].expY));
  	//printf("Mini/NanoShape: %3.0f | %5.2f\% | %5.2f\% | %5.2f \n",lexclMini[i].mX,lexclMini[i].expY,lexclNanoShape[j].expY,(lexclMini[i].expY/lexclNanoShape[j].expY));
	printf("NanoShape/Mini: %3.0f & %5.2f\\\% & %5.2f\\\% & %5.2f \\\\\n",lexclMini[i].mX,lexclMini[i].expY,lexclNanoShape[j].expY,(lexclNanoShape[j].expY/lexclMini[i].expY));
      }
    }
  }
  
  TGraph *grV10ByCurrentCBA = new TGraph(int(lexclNanoShape.size()));
  for(int i = 0; i < int(lexclNanoShape.size()) ; i++){
    for(int j = 0; j < int(lexclNano.size()) ; j++){
      if(lexclNano[j].mX==lexclNanoShape[i].mX){
	grV10ByCurrentCBA->SetPoint(i,lexclNano[j].mX, (lexclNano[j].expY/lexclNanoShape[i].expY));
	printf("v10/v11: %3.0f & %5.2f\\\% & %5.2f\\\% & %5.2f \\\\\n",lexclNano[j].mX,lexclNano[j].expY,lexclNanoShape[i].expY,(lexclNano[j].expY/lexclNanoShape[i].expY));
      }
    }
  }  
  std::cout << std::endl;
  
  TGraph *grMVAByCBA = new TGraph(int(lexclNanoMVA.size()));
  for(int i = 0; i < int(lexclNanoShape.size()) ; i++){
    for(int j = 0; j < int(lexclNanoMVA.size()) ; j++){
      if(lexclNanoMVA[j].mX==lexclNanoShape[i].mX){
	grMVAByCBA->SetPoint(i,lexclNanoMVA[j].mX, (lexclNanoMVA[j].expY/lexclNanoShape[i].expY));
	printf("MVA/CBA: %3.0f & %5.2f\\\% & %5.2f\\\% & %5.2f \\\\\n",lexclNanoMVA[j].mX,lexclNanoMVA[j].expY,lexclNanoShape[i].expY,(lexclNanoMVA[j].expY/lexclNanoShape[i].expY));
      }
    }
  }


  SetStyle(grlexclMini, 3, kOrange+2, kFullCircle,1.2);
  // SetStyle(grlexclMiniInc, 3,kRed, kOpenCircle,1.2);
  // SetStyle(grlexclMEqv16lnN, 3,kMagenta, kFullSquare,1.2);
  // //SetStyle(grlexclMEqv16lnN, 2,kMagenta, kFullDoubleDiamond,3.2);
  // //SetStyle(grlexclMEqv16lnN, 2,kGreen+2, kOpenSquare,2.1);
  // //SetStyle(grlexclMEqv16lnN, 3, 28, kFullDoubleDiamond,3.1);
  // //SetStyle(grlexclMEqv16lnN, 3,kOrange+2, kFullCrossX,2.1);
  // //  SetStyle(grlexclMEqv16lnN, 2,kRed, kFullStar,2.1);
  // //SetStyle(grlexclMEqv16lnN, 2,kGreen+2, kOpenSquare,2.1);
  // //SetStyle(grlexclMEqv16shape, 3, 28, kFullDoubleDiamond,3.1);
  // //SetStyle(grlexclMEqv16shape, 2,kBlack, kFullTriangleDown,2.1);
  // //SetStyle(grlexclMEqv16shape, 3,kGreen+2, kOpenTriangleDown,2.1);
  // SetStyle(grlexclMEqv16shape, 2, kRed-2, kOpenTriangleUp, 2.1);
  // //SetStyle(grlexclMEqv16shape, 3, kGreen+2, kFullTriangleUp,2.1);
  // //SetStyle(grlexclMEqv16shape, 3, 49, kFullFourTrianglesPlus,3.1);
  // //SetStyle(grlexclMEqv16shape, 3,kOrange+2, kFullCrossX,2.1);
  // //SetStyle(grlexclMEqv16shape, 3,kGreen+2, kOpenSquare,1.2);
  // //SetStyle(grlexclMEqv16shape, 2,kGreen+2, kOpenSquare,2.1);
  // //SetStyle(grlexclMEqv16shape, 2,kRed, kFullStar,2.1);
  // //SetStyle(grlexclNano16, 2,kRed, kFullThreeTriangles,3.1);
  // SetStyle(grlexclNano16, 2,kRed, kFourSquaresX,2.1);
  // //SetStyle(grlexclNano16, 2,kBlack, kFullCross,2.1);
  // //SetStyle(grlexclNano, 3,kOrange+2, kFullCrossX,2.1);
  // SetStyle(grlexclNano, 2,kBlack, kFullCross,2.1);

  SetStyle(grMiniByNano, 3, kRed, kFullSquare,1.2);
  SetStyle(grlexclNanoShape, 3,kBlue, kFullCircle,1.2);
  SetStyle(grlexclNano, 2,kBlack, kFullCross,2.1);
  SetStyle(grlexclNanoMVA, 2,kRed, kFullStar,2.1);
  
  SetStyle(grV10ByCurrentCBA, 3,kOrange+2, kFullCrossX,2.1);
  SetStyle(grMVAByCBA, 3, kRed, kFullSquare,1.2);
  
  TLegend* legmn = new TLegend(0.12,0.16,0.73,0.28,NULL,"brNDC"); //lower part
  legmn->SetBorderSize(0);
  legmn->SetTextSize(0.05);
  legmn->SetFillColor(0);
  legmn->SetTextSize(0.019);
  legmn->AddEntry(grlexclMini,"CMS Published l+jets, log-normal, 2016","LP");
  legmn->AddEntry(grlexclNanoShape, "Current: CBA l+jets, shape, Run2","LP");

  TLegend* leg0 = new TLegend(0.12,0.16,0.73,0.28,NULL,"brNDC"); //lower part
  leg0->SetBorderSize(0);
  leg0->SetTextSize(0.05);
  leg0->SetFillColor(0);
  leg0->SetTextSize(0.019);
  leg0->AddEntry(grlexclNanoMVA,"Current: MVA l+jets, shape, Run2","LP");
  leg0->AddEntry(grlexclNanoShape, "Current: CBA l+jets, shape, Run2","LP");

  TLegend* leg1 = new TLegend(0.12,0.16,0.73,0.28,NULL,"brNDC"); //lower part
  leg1->SetBorderSize(0);
  leg1->SetTextSize(0.05);
  leg1->SetFillColor(0);
  leg1->SetTextSize(0.019);
  leg1->AddEntry(grlexclNano,"AN-V10: CBA l+jets, lnN, Run2","LP");
  leg1->AddEntry(grlexclNanoShape, "Current: CBA l+jets, shape, Run2","LP");


  // TCanvas *c1 = new TCanvas("c1","c1", 800,800);
  // c1->SetLogy();
  // c1->SetTickx();
  // c1->SetTicky();
  // grlexclMini->Draw("ALP");
  // // grlexclMiniInc->Draw("LP");
  // grlexclMEqv16lnN->Draw("LP");
  // grlexclMEqv16shape->Draw("LP");
  // grlexclNano16->Draw("LP");
  // grlexclNano->Draw("LP");

  // leg->Draw();

  grlexclMini->SetMaximum(10.0);
  grlexclMini->SetMinimum(5.0e-2);
  grlexclMini->GetXaxis()->SetTitleOffset(1.2);
  grlexclMini->GetYaxis()->SetTitleOffset(1.2);
  grlexclMini->GetXaxis()->SetTitle("M_{H^{#pm}} (GeV)");
  grlexclMini->GetYaxis()->SetTitle("BR(t#rightarrow H^{#pm}b) (%)");
  grlexclMini->SetTitle("Comparison of expected values of median");
  grMiniByNano->GetXaxis()->SetTitle("M_{H^{#pm}} (GeV)");
  PlotRatio(grlexclMini, grlexclNanoShape, grMiniByNano, legmn, "c2");
  
  grlexclNanoShape->SetMaximum(30.0);
  grlexclNanoShape->SetMinimum(0.02);
  grlexclNanoShape->GetXaxis()->SetTitleOffset(1.2);
  grlexclNanoShape->GetYaxis()->SetTitleOffset(1.2);
  grlexclNanoShape->GetXaxis()->SetTitle("M_{H^{#pm}} (GeV)");
  grlexclNanoShape->GetYaxis()->SetTitle("BR(t#rightarrow H^{#pm}b) (%)");
  grlexclNanoShape->SetTitle("Comparison of expected values of median");
  grMVAByCBA->GetXaxis()->SetTitle("M_{H^{#pm}} (GeV)");
  PlotRatio(grlexclNanoShape, grlexclNanoMVA, grMVAByCBA, leg0, "c3");

  grV10ByCurrentCBA->GetXaxis()->SetTitle("M_{H^{#pm}} (GeV)");
  PlotRatio(grlexclNanoShape, grlexclNano, grV10ByCurrentCBA, leg1, "c4");

  grlexclNanoShape1sL->SetLineWidth(2.0);
  grlexclNanoShape1sL->SetLineColor(kBlue);
  grlexclNanoShape1sL->SetLineStyle(2);
  grlexclNanoShape1sH->SetLineWidth(2.0);
  grlexclNanoShape1sH->SetLineColor(kBlue);
  grlexclNanoShape1sH->SetLineStyle(2);

  grlexclNanoShape2sL->SetLineWidth(2.0);
  grlexclNanoShape2sL->SetLineColor(kBlue);
  grlexclNanoShape2sL->SetLineStyle(10);
  grlexclNanoShape2sH->SetLineWidth(2.0);
  grlexclNanoShape2sH->SetLineColor(kBlue);
  grlexclNanoShape2sH->SetLineStyle(10);
  
  TLegend* leg2 = (TLegend *)leg0->Clone("leg2");
  leg2->AddEntry(grlexclNanoShape1sL, "Current: CBA l+jets, shape, Run2 (68% expected)","L");
  leg2->AddEntry(grlexclNanoShape2sL, "Current: CBA l+jets, shape, Run2 (95% expected)","L");
  PlotRatio(grlexclNanoShape, grlexclNanoShape1sL, grlexclNanoShape1sH, grlexclNanoShape2sL, grlexclNanoShape2sH, grlexclNanoMVA, grMVAByCBA, leg2, "c5");
  
  TFile *fout = new TFile("RatioPlot.root","recreate");
  TCanvas *c2 = (TCanvas *)gROOT->GetListOfCanvases()->FindObject("c2");
  TCanvas *c3 = (TCanvas *)gROOT->GetListOfCanvases()->FindObject("c3");
  TCanvas *c4 = (TCanvas *)gROOT->GetListOfCanvases()->FindObject("c4");
  TCanvas *c5 = (TCanvas *)gROOT->GetListOfCanvases()->FindObject("c5");
  c2->Write();
  c3->Write();
  c4->Write();
  c5->Write();
  fout->Close();

  delete fout;
  // lexclMini.clear();
  // lexclMEqv16lnN.clear();
  // lexclMEqv16shape.clear();
  // lexclNano16.clear();
  // lexclNano.clear();

  return true;

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
    //grRatio->GetYaxis()->SetTitle("#frac{Current}{Published}");
    grRatio->GetYaxis()->SetTitle("#frac{MBA}{CBA}");
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
    grRatio->GetXaxis()->SetTitleOffset(1.02);
    grRatio->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    grRatio->GetXaxis()->SetLabelSize(20);
    
    pad1->cd();

    cout<<" nof canvas primitives " << c->GetListOfPrimitives()->GetEntries() << endl ;
    
  }

  return true;
}


int PlotRatio(TGraph *gr1, TGraph *gr1_1sL, TGraph *gr1_1sH, TGraph *gr1_2sL, TGraph *gr1_2sH, TGraph *gr2, TGraph *grRatio, TLegend *leg, const char *cname)
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
    gr1_1sL->Draw("L");
    gr1_1sH->Draw("L");
    gr1_2sL->Draw("L");
    gr1_2sH->Draw("L");
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
    //grRatio->GetYaxis()->SetTitle("#frac{Current}{Published}");
    grRatio->GetYaxis()->SetTitle("#frac{MVA}{CBA}");
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
    grRatio->GetXaxis()->SetTitleOffset(1.06);
    grRatio->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    grRatio->GetXaxis()->SetLabelSize(20);
    
    pad1->cd();

    cout<<" nof canvas primitives " << c->GetListOfPrimitives()->GetEntries() << endl ;
    
  }

  return true;
}
