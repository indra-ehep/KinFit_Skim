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

  //01
  // ReadLimitMiniAOD(lexclMini, "hig-18-021/PublishedPRD/ForANv12/mu_ele/Cat3_cTagEx");
  // ReadLimitNanoAOD(lexclMEqv16lnN, "TIFRAPAR-2023-01-15/01_yearend22-MiniAODEqv/2016/Comb", "mu_ele");

  //02
  // ReadLimitMiniAOD(lexclMini, "hig-18-021/PublishedPRD/ForANv12/mu_ele/Cat3_cTagEx");
  // ReadLimitNanoAOD(lexclMEqv16lnN, "TIFRAPAR-2023-01-15/01_yearend22-MiniAODEqv/2016/Comb", "mu_ele");
  // ReadLimitNanoAOD(lexclMEqv16shape, "TIFRAPAR-2023-01-15/11_elereliso-NanoAOD_logN/2016/Comb", "mu_ele");

  //03
  // ReadLimitMiniAOD(lexclMini, "hig-18-021/PublishedPRD/ForANv12/mu_ele/Cat3_cTagEx");
  // ReadLimitNanoAOD(lexclMEqv16lnN, "TIFRAPAR-2023-01-15/01_yearend22-MiniAODEqv/2016/Comb", "mu_ele");
  // ReadLimitNanoAOD(lexclMEqv16shape, "TIFRAPAR-2023-01-15/05_yearend22-MiniAODEqv_Shapes/2016/Comb", "mu_ele");

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

  ReadLimitMiniAOD(lexclMini, "hig-18-021/PublishedPRD/ForANv12/mu_ele/Cat3_cTagEx");
  ReadLimitMiniAOD(lexclMiniInc, "hig-18-021/PublishedPRD/ForANv12/mu_ele/Cat1_Inc");
  ReadLimitNanoAOD(lexclMEqv16lnN, "TIFRAPAR-2023-01-15/04_notoppt-UptoKFBTagSyst/2016/Incl", "mu_ele");
  ReadLimitNanoAOD(lexclMEqv16shape, "TIFRAPAR-2023-01-15/04_notoppt-UptoKFBTagSyst/Run2/Incl", "mu_ele");

  // ReadLimitNanoAOD(lexclMEqv16lnN, "TIFRAPAR-2023-01-15/09_elereliso-NanoAOD_Shapes/2016/Comb", "mu_ele");
  // ReadLimitNanoAOD(lexclMEqv16shape, "TIFRAPAR-2023-01-15/14_elereliso-NanoAOD_unblinded/2016/Comb", "mu_ele");
  ReadLimitNanoAOD(lexclNano16, "TIFRAPAR-2023-01-15/13_elereliso-NanoAOD_unblinded_unNormalized/2016/Comb", "mu_ele");


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
  cout << "lexclMEqv16lnN.size : " << lexclMEqv16lnN.size() << endl;
  cout << "lexclMEqv16shape.size : " << lexclMEqv16shape.size() << endl;
  cout << "lexclNano16.size : " << lexclNano16.size() << endl;
  for(int i = 0; i < int(lexclMEqv16lnN.size()) ; i++){
    printf("X : %3.0f, Y : %5.2f\%\n",lexclMEqv16lnN[i].mX, lexclMEqv16lnN[i].expY);
    grlexclMEqv16lnN->SetPoint(i,lexclMEqv16lnN[i].mX, lexclMEqv16lnN[i].expY);
    grlexclMEqv16shape->SetPoint(i,lexclMEqv16shape[i].mX, lexclMEqv16shape[i].expY);
    grlexclNano16->SetPoint(i,lexclNano16[i].mX, lexclNano16[i].expY);
  }
  
  SetStyle(grlexclMini, 2,kBlue, kFullCircle,1.2);
  SetStyle(grlexclMiniInc, 2,kRed, kOpenCircle,1.2);
  //SetStyle(grlexclMEqv16lnN, 2,kMagenta, kFullSquare,1.2);
  //SetStyle(grlexclMEqv16lnN, 2,kGreen+2, kOpenSquare,2.1);
  SetStyle(grlexclMEqv16lnN, 3, 28, kFullDoubleDiamond,3.1);
  //  SetStyle(grlexclMEqv16lnN, 2,kRed, kFullStar,2.1);
  //SetStyle(grlexclMEqv16lnN, 2,kGreen+2, kOpenSquare,2.1);
  //SetStyle(grlexclMEqv16shape, 3, 28, kFullDoubleDiamond,3.1);
  //SetStyle(grlexclMEqv16shape, 2,kBlack, kFullCross,2.1);
  //SetStyle(grlexclMEqv16shape, 3, kGreen+2, kFullTriangleUp,2.1);
  //SetStyle(grlexclMEqv16shape, 3, 49, kFullFourTrianglesPlus,3.1);
  SetStyle(grlexclMEqv16shape, 3,kOrange+2, kFullCrossX,2.1);
  //SetStyle(grlexclMEqv16shape, 3,kGreen+2, kOpenSquare,1.2);
  //SetStyle(grlexclMEqv16shape, 2,kGreen+2, kOpenSquare,2.1);
  //SetStyle(grlexclMEqv16shape, 2,kRed, kFullStar,2.1);
  SetStyle(grlexclNano16, 2,kBlack, kFullCross,2.1);

  TLegend* leg = new TLegend(0.12,0.79,0.73,0.86,NULL,"brNDC");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.05);
  leg->SetFillColor(0);
  leg->SetTextSize(0.019);
  leg->AddEntry(grlexclMini,"Published:Unblinded:Excl:Expected:MiniAOD l+jets, lnN, 2016","LP");
  leg->AddEntry(grlexclMiniInc,"Published:Unblinded:InclKF:Expected:MiniAOD l+jets, lnN, 2016","LP");
  leg->AddEntry(grlexclMEqv16lnN, "Current:Blinded:BTagSyst:Expected:MiniAOD Equivalent l+jets, lnN, 2016","LP"); //01
  leg->AddEntry(grlexclMEqv16shape, "Current:Blinded:BTagSyst:Expected:MiniAOD Equivalent l+jets, lnN, Run2","LP");
  
  //leg->AddEntry(grlexclMEqv16lnN, "Current:Blinded:Excl:Expected:NanoAOD l+jets, shape, 2016","LP");
  //leg->AddEntry(grlexclMEqv16shape, "Current:Blinded:Excl:Expected:NanoAOD l+jets, shape, 2016","LP");
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
  leg->Draw();
  
  lexclMini.clear();
  lexclMEqv16lnN.clear();
  lexclMEqv16shape.clear();
  lexclNano16.clear();
}
