#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <fstream>
#include <iomanip>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <algorithm> 
#include "MyHPlusDataCardMaker.h"

//----------------------------------------//
//make data card for each mass
//----------------------------------------//

void MyHPlusDataCardMakerMini(TString inFileDir="stack_20180418_Mu_Sys_PreAppComent",
			      TString syear="2016", 
			      TString histSubDir_="KinFit",
			      TString histName="mjj_kfit", 
			      TString channelName="mu", 
			      int mass=80, 
			      TString label="WH80", 
			      TString hPlusFileName="all_Hplus80.root")
{


  MyHPlusDataCardMaker DC;
  //TString baseDir = "topPtWeight";
  TString baseDir = "base";
  TString histSubDir = "Iso/"+histSubDir_+"/";
  bool isMuChannel = false; 
  if(channelName=="mu") isMuChannel = true;
  inFileDir = inFileDir + "/" + syear;

  int year = syear.Atoi();
  double totLumi = 35.9; //2016
  if(year==2017)
    totLumi = 41.5; // 2017
  if(year==2018)
    totLumi = 59.7; //2018

  ///INPUT FILES
  TFile* fData    = TFile::Open(inFileDir+"/all_Data.root");
  //bkg
  TFile* fVV      = TFile::Open(inFileDir+"/all_VV.root");
  TFile* fDY      = TFile::Open(inFileDir+"/all_DY.root");
  TFile* fWJ      = TFile::Open(inFileDir+"/all_WJets.root");
  TFile* fQCD     = TFile::Open(inFileDir+"/all_QCD.root");
  TFile* fST      = TFile::Open(inFileDir+"/all_ST.root");
  TFile* fTT      = TFile::Open(inFileDir+"/all_TTJetsP.root");
  TFile* fTT_up      	= TFile::Open(inFileDir+"/all_TTJetsP_up.root");
  TFile* fTT_down      	= TFile::Open(inFileDir+"/all_TTJetsP_down.root");
  TFile* fTT_mtop1715     = TFile::Open(inFileDir+"/all_TTJetsP_mtop1715.root");
  TFile* fTT_mtop1735     = TFile::Open(inFileDir+"/all_TTJetsP_mtop1735.root");
  TFile* fTT_hdampUP      = TFile::Open(inFileDir+"/all_TTJetsP_hdampUP.root");
  TFile* fTT_hdampDOWN    = TFile::Open(inFileDir+"/all_TTJetsP_hdampDOWN.root");
  //signal
  TFile *fWH  = TFile::Open(inFileDir+"/"+hPlusFileName);
  //data driven qcd
  TFile* fQCD_dd = TFile::Open(inFileDir+"/all_QCD_dd.root"); 
  
  //OUTPUT FILE
  TFile *fout = new TFile(TString("Shapes_hcs_13TeV_")+channelName+TString("_")+histSubDir_+TString("_")+histName+TString("_")+label+TString(".root"), "RECREATE");

  //For one extra NP
  bool isExL = false;
  bool isExM = false;
  if(histName.Contains("ExL")) isExL = true;
  if(histName.Contains("ExM")) isExM = true;

  //ttbar
  double sf_ttbar = 1.0; 
  TH1F* ttbar = DC.readWriteHisto(fTT, baseDir+"/"+histSubDir, histName, sf_ttbar, fout, fTT,  "ttbar", true);
  TH1F* ttbar_JESUp = DC.readWriteHisto(fTT, "JESPlus/"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_JESUp", true);
  TH1F* ttbar_JESDown = DC.readWriteHisto(fTT, "JESMinus/"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_JESDown", true);
  TH1F* ttbar_PileupUp = DC.readWriteHisto(fTT, "PileupPlus/"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_PileupUp", true);
  TH1F* ttbar_PileupDown = DC.readWriteHisto(fTT, "PileupMinus/"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_PileupDown", true);
  TH1F* ttbar_JERUp = DC.readWriteHisto(fTT, "JERPlus/"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_JERUp", true);
  TH1F* ttbar_JERDown = DC.readWriteHisto(fTT, "JERMinus/"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_JERDown", true);
  TH1F* ttbar_topPtUp = DC.readWriteHisto(fTT, "TopPtPlus/"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_topPtUp", true);
  TH1F* ttbar_topPtDown = DC.readWriteHisto(fTT, "TopPtMinus/"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_topPtDown", true);
  TH1F* ttbar_bcTag1Up = DC.readWriteHisto(fTT, "bcTagPlus1/"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_bcTag1Up", true);
  TH1F* ttbar_bcTag1Down = DC.readWriteHisto(fTT, "bcTagMinus1/"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_bcTag1Down", true);
  TH1F* ttbar_bcTag2Up = DC.readWriteHisto(fTT, "bcTagPlus2/"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_bcTag2Up", true);
  TH1F* ttbar_bcTag2Down = DC.readWriteHisto(fTT, "bcTagMinus2/"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_bcTag2Down", true);
  TH1F* ttbar_bcTag3Up = DC.readWriteHisto(fTT, "bcTagPlus3/"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_bcTag3Up", true);
  TH1F* ttbar_bcTag3Down = DC.readWriteHisto(fTT, "bcTagMinus3/"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_bcTag3Down", true);
  
  double unc_ttbar_ExL = 1.0;
  double unc_ttbar_ExM = 1.0;
  if(isExL){
    TH1F* ttbar_yLyMyT = DC.getHisto(fTT, baseDir+"/Iso/ExCTag/", "sf_CTag_yLyMyT_wt", fTT);
    TH1F* ttbar_yLyMnT = DC.getHisto(fTT, baseDir+"/Iso/ExCTag/", "sf_CTag_yLyMnT_wt", fTT);
    TH1F* ttbar_yLnMyT = DC.getHisto(fTT, baseDir+"/Iso/ExCTag/", "sf_CTag_yLnMyT_wt", fTT);
    TH1F* ttbar_yLnMnT = DC.getHisto(fTT, baseDir+"/Iso/ExCTag/", "sf_CTag_yLnMnT_wt", fTT);
    unc_ttbar_ExL = DC.getUncExL(ttbar_yLyMyT, ttbar_yLyMnT, ttbar_yLnMyT, ttbar_yLnMnT);
  }
  if(isExM){
    TH1F* ttbar_yMyT = DC.getHisto(fTT, baseDir+"/Iso/ExCTag/", "sf_CTag_yMyT_wt", fTT);
    TH1F* ttbar_yMnT = DC.getHisto(fTT, baseDir+"/Iso/ExCTag/", "sf_CTag_yMnT_wt", fTT);
    unc_ttbar_ExM = DC.getUncExM(ttbar_yMyT, ttbar_yMnT);
  }
  //ttbar scaleUp
  double sf_ttbar_scaleUp = 1; 
  TH1F* ttbar_scaleUp = DC.readWriteHisto(fTT_up, baseDir+"/"+histSubDir, histName, sf_ttbar_scaleUp, fout, fTT, "ttbar_scaleRF_ttUp", true);
  //ttbar scaleDown
  double sf_ttbar_scaleDown = 1; 
  TH1F* ttbar_scaleDown = DC.readWriteHisto(fTT_down, baseDir+"/"+histSubDir, histName, sf_ttbar_scaleDown, fout, fTT, "ttbar_scaleRF_ttDown", true);
  //ttbar mtop1715
  double sf_ttbar_mtop1715 = 1; 
  TH1F* ttbar_mtop1715 = DC.readWriteHisto(fTT_mtop1715, baseDir+"/"+histSubDir, histName, sf_ttbar_mtop1715, fout, fTT, "ttbar_topMass_ttUp", true);
  //ttbar mtop1735
  double sf_ttbar_mtop1735 = 1; 
  TH1F* ttbar_mtop1735 = DC.readWriteHisto(fTT_mtop1735, baseDir+"/"+histSubDir, histName, sf_ttbar_mtop1735, fout, fTT, "ttbar_topMass_ttDown", true);
  //ttbar matchingUp
  double sf_ttbar_matchingUp = 1; 
  TH1F* ttbar_matchingUp = DC.readWriteHisto(fTT_hdampUP, baseDir+"/"+histSubDir, histName, sf_ttbar_matchingUp, fout, fTT, "ttbar_hDamp_ttUp", true);
  //ttbar matchingDown
  double sf_ttbar_matchingDown = 1; 
  TH1F* ttbar_matchingDown = DC.readWriteHisto(fTT_hdampDOWN, baseDir+"/"+histSubDir, histName, sf_ttbar_matchingDown, fout, fTT, "ttbar_hDamp_ttDown", true);

  //w+jets
  double sf_wjet = 1;
  TH1F* wjet = DC.readWriteHisto(fWJ, baseDir+"/"+histSubDir, histName, sf_wjet, fout, fTT, "wjet", true);
  TH1F* wjet_JESUp = DC.readWriteHisto(fWJ, "JESPlus/"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_JESUp", true);
  TH1F* wjet_JESDown = DC.readWriteHisto(fWJ, "JESMinus/"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_JESDown", true);
  TH1F* wjet_PileupUp = DC.readWriteHisto(fWJ, "PileupPlus/"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_PileupUp", true);
  TH1F* wjet_PileupDown = DC.readWriteHisto(fWJ, "PileupMinus/"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_PileupDown", true);
  TH1F* wjet_JERUp = DC.readWriteHisto(fWJ, "JERPlus/"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_JERUp", true);
  TH1F* wjet_JERDown = DC.readWriteHisto(fWJ, "JERMinus/"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_JERDown", true);
  TH1F* wjet_bcTag1Up = DC.readWriteHisto(fWJ, "bcTagPlus1/"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_bcTag1Up", true);
  TH1F* wjet_bcTag1Down = DC.readWriteHisto(fWJ, "bcTagMinus1/"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_bcTag1Down", true); 
  TH1F* wjet_bcTag2Up = DC.readWriteHisto(fWJ, "bcTagPlus2/"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_bcTag2Up", true);
  TH1F* wjet_bcTag2Down = DC.readWriteHisto(fWJ, "bcTagMinus2/"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_bcTag2Down", true); 
  TH1F* wjet_bcTag3Up = DC.readWriteHisto(fWJ, "bcTagPlus3/"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_bcTag3Up", true);
  TH1F* wjet_bcTag3Down = DC.readWriteHisto(fWJ, "bcTagMinus3/"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_bcTag3Down", true); 
  double unc_wjet_ExL = 1.0;
  double unc_wjet_ExM = 1.0;
  if(isExL){
    TH1F* wjet_yLyMyT = DC.getHisto(fWJ, baseDir+"/Iso/ExCTag/", "sf_CTag_yLyMyT_wt", fTT);
    TH1F* wjet_yLyMnT = DC.getHisto(fWJ, baseDir+"/Iso/ExCTag/", "sf_CTag_yLyMnT_wt", fTT);
    TH1F* wjet_yLnMyT = DC.getHisto(fWJ, baseDir+"/Iso/ExCTag/", "sf_CTag_yLnMyT_wt", fTT);
    TH1F* wjet_yLnMnT = DC.getHisto(fWJ, baseDir+"/Iso/ExCTag/", "sf_CTag_yLnMnT_wt", fTT);
    unc_wjet_ExL = DC.getUncExL(wjet_yLyMyT, wjet_yLyMnT, wjet_yLnMyT, wjet_yLnMnT);
  }
  if(isExM){
    TH1F* wjet_yMyT = DC.getHisto(fWJ, baseDir+"/Iso/ExCTag/", "sf_CTag_yMyT_wt", fTT);
    TH1F* wjet_yMnT = DC.getHisto(fWJ, baseDir+"/Iso/ExCTag/", "sf_CTag_yMnT_wt", fTT);
    unc_wjet_ExM = DC.getUncExM(wjet_yMyT, wjet_yMnT);
  }

  //Z+Jets
  double sf_zjet = 1;
  TH1F* zjet = DC.readWriteHisto(fDY, baseDir+"/"+histSubDir, histName, sf_zjet, fout, fTT, "zjet", true);
  TH1F* zjet_JESUp = DC.readWriteHisto(fDY, "JESPlus/"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_JESUp", true);
  TH1F* zjet_JESDown = DC.readWriteHisto(fDY, "JESMinus/"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_JESDown", true);
  TH1F* zjet_PileupUp = DC.readWriteHisto(fDY, "PileupPlus/"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_PileupUp", true);
  TH1F* zjet_PileupDown = DC.readWriteHisto(fDY, "PileupMinus/"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_PileupDown", true);
  TH1F* zjet_JERUp = DC.readWriteHisto(fDY, "JERPlus/"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_JERUp", true);
  TH1F* zjet_JERDown = DC.readWriteHisto(fDY, "JERMinus/"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_JERDown", true);
  TH1F* zjet_bcTag1Up = DC.readWriteHisto(fDY, "bcTagPlus1/"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_bcTag1Up", true);
  TH1F* zjet_bcTag1Down = DC.readWriteHisto(fDY, "bcTagMinus1/"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_bcTag1Down", true);
  TH1F* zjet_bcTag2Up = DC.readWriteHisto(fDY, "bcTagPlus2/"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_bcTag2Up", true);
  TH1F* zjet_bcTag2Down = DC.readWriteHisto(fDY, "bcTagMinus2/"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_bcTag2Down", true);
  TH1F* zjet_bcTag3Up = DC.readWriteHisto(fDY, "bcTagPlus3/"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_bcTag3Up", true);
  TH1F* zjet_bcTag3Down = DC.readWriteHisto(fDY, "bcTagMinus3/"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_bcTag3Down", true);
  double unc_zjet_ExL = 1.0;
  double unc_zjet_ExM = 1.0;
  if(isExL){
    TH1F* zjet_yLyMyT = DC.getHisto(fDY, baseDir+"/Iso/ExCTag/", "sf_CTag_yLyMyT_wt", fTT);
    TH1F* zjet_yLyMnT = DC.getHisto(fDY, baseDir+"/Iso/ExCTag/", "sf_CTag_yLyMnT_wt", fTT);
    TH1F* zjet_yLnMyT = DC.getHisto(fDY, baseDir+"/Iso/ExCTag/", "sf_CTag_yLnMyT_wt", fTT);
    TH1F* zjet_yLnMnT = DC.getHisto(fDY, baseDir+"/Iso/ExCTag/", "sf_CTag_yLnMnT_wt", fTT);
    unc_zjet_ExL = DC.getUncExL(zjet_yLyMyT, zjet_yLyMnT, zjet_yLnMyT, zjet_yLnMnT);
  }
  if(isExM){
    TH1F* zjet_yMyT = DC.getHisto(fDY, baseDir+"/Iso/ExCTag/", "sf_CTag_yMyT_wt", fTT);
    TH1F* zjet_yMnT = DC.getHisto(fDY, baseDir+"/Iso/ExCTag/", "sf_CTag_yMnT_wt", fTT);
    unc_zjet_ExM = DC.getUncExM(zjet_yMyT, zjet_yMnT);
  }

  //SingleTop
  double sf_stop = 1.0;
  TH1F* stop = DC.readWriteHisto(fST, baseDir+"/"+histSubDir, histName, sf_stop, fout, fTT, "stop", true);
  TH1F* stop_JESUp = DC.readWriteHisto(fST, "JESPlus/"+histSubDir, histName, sf_stop, fout, fTT, "stop_JESUp", true);
  TH1F* stop_JESDown = DC.readWriteHisto(fST, "JESMinus/"+histSubDir, histName, sf_stop, fout, fTT, "stop_JESDown", true);
  TH1F* stop_PileupUp = DC.readWriteHisto(fST, "PileupPlus/"+histSubDir, histName, sf_stop, fout, fTT, "stop_PileupUp", true);
  TH1F* stop_PileupDown = DC.readWriteHisto(fST, "PileupMinus/"+histSubDir, histName, sf_stop, fout, fTT, "stop_PileupDown", true);
  TH1F* stop_JERUp = DC.readWriteHisto(fST, "JERPlus/"+histSubDir, histName, sf_stop, fout, fTT, "stop_JERUp", true);
  TH1F* stop_JERDown = DC.readWriteHisto(fST, "JERMinus/"+histSubDir, histName, sf_stop, fout, fTT, "stop_JERDown", true);
  TH1F* stop_bcTag1Up = DC.readWriteHisto(fST, "bcTagPlus1/"+histSubDir, histName, sf_stop, fout, fTT, "stop_bcTag1Up", true);
  TH1F* stop_bcTag1Down = DC.readWriteHisto(fST, "bcTagMinus1/"+histSubDir, histName, sf_stop, fout, fTT, "stop_bcTag1Down", true);
  TH1F* stop_bcTag2Up = DC.readWriteHisto(fST, "bcTagPlus2/"+histSubDir, histName, sf_stop, fout, fTT, "stop_bcTag2Up", true);
  TH1F* stop_bcTag2Down = DC.readWriteHisto(fST, "bcTagMinus2/"+histSubDir, histName, sf_stop, fout, fTT, "stop_bcTag2Down", true);
  TH1F* stop_bcTag3Up = DC.readWriteHisto(fST, "bcTagPlus3/"+histSubDir, histName, sf_stop, fout, fTT, "stop_bcTag3Up", true);
  TH1F* stop_bcTag3Down = DC.readWriteHisto(fST, "bcTagMinus3/"+histSubDir, histName, sf_stop, fout, fTT, "stop_bcTag3Down", true);
  double unc_stop_ExL = 1.0;
  double unc_stop_ExM = 1.0;
  if(isExL){
    TH1F* stop_yLyMyT = DC.getHisto(fST, baseDir+"/Iso/ExCTag/", "sf_CTag_yLyMyT_wt", fTT);
    TH1F* stop_yLyMnT = DC.getHisto(fST, baseDir+"/Iso/ExCTag/", "sf_CTag_yLyMnT_wt", fTT);
    TH1F* stop_yLnMyT = DC.getHisto(fST, baseDir+"/Iso/ExCTag/", "sf_CTag_yLnMyT_wt", fTT);
    TH1F* stop_yLnMnT = DC.getHisto(fST, baseDir+"/Iso/ExCTag/", "sf_CTag_yLnMnT_wt", fTT);
    unc_stop_ExL = DC.getUncExL(stop_yLyMyT, stop_yLyMnT, stop_yLnMyT, stop_yLnMnT);
  }
  if(isExM){
    TH1F* stop_yMyT = DC.getHisto(fST, baseDir+"/Iso/ExCTag/", "sf_CTag_yMyT_wt", fTT);
    TH1F* stop_yMnT = DC.getHisto(fST, baseDir+"/Iso/ExCTag/", "sf_CTag_yMnT_wt", fTT);
    unc_stop_ExM = DC.getUncExM(stop_yMyT, stop_yMnT);
  }

  //Dibosons
  double sf_vv = 1;
  TH1F* vv = DC.readWriteHisto(fVV, baseDir+"/"+histSubDir, histName, sf_vv, fout, fTT, "vv", true);
  TH1F* vv_JESUp = DC.readWriteHisto(fVV, "JESPlus/"+histSubDir, histName, sf_vv, fout, fTT, "vv_JESUp", true);
  TH1F* vv_JESDown = DC.readWriteHisto(fVV, "JESMinus/"+histSubDir, histName, sf_vv, fout, fTT, "vv_JESDown", true);
  TH1F* vv_PileupUp = DC.readWriteHisto(fVV, "PileupPlus/"+histSubDir, histName, sf_vv, fout, fTT, "vv_PileupUp", true);
  TH1F* vv_PileupDown = DC.readWriteHisto(fVV, "PileupMinus/"+histSubDir, histName, sf_vv, fout, fTT, "vv_PileupDown", true);
  TH1F* vv_JERUp = DC.readWriteHisto(fVV, "JERPlus/"+histSubDir, histName, sf_vv, fout, fTT, "vv_JERUp", true);
  TH1F* vv_JERDown = DC.readWriteHisto(fVV, "JERMinus/"+histSubDir, histName, sf_vv, fout, fTT, "vv_JERDown", true);
  TH1F* vv_bcTag1Up = DC.readWriteHisto(fVV, "bcTagPlus1/"+histSubDir, histName, sf_vv, fout, fTT, "vv_bcTag1Up", true);
  TH1F* vv_bcTag1Down = DC.readWriteHisto(fVV, "bcTagMinus1/"+histSubDir, histName, sf_vv, fout, fTT, "vv_bcTag1Down", true);
  TH1F* vv_bcTag2Up = DC.readWriteHisto(fVV, "bcTagPlus2/"+histSubDir, histName, sf_vv, fout, fTT, "vv_bcTag2Up", true);
  TH1F* vv_bcTag2Down = DC.readWriteHisto(fVV, "bcTagMinus2/"+histSubDir, histName, sf_vv, fout, fTT, "vv_bcTag2Down", true);
  TH1F* vv_bcTag3Up = DC.readWriteHisto(fVV, "bcTagPlus3/"+histSubDir, histName, sf_vv, fout, fTT, "vv_bcTag3Up", true);
  TH1F* vv_bcTag3Down = DC.readWriteHisto(fVV, "bcTagMinus3/"+histSubDir, histName, sf_vv, fout, fTT, "vv_bcTag3Down", true);
  double unc_vv_ExL = 1.0;
  double unc_vv_ExM = 1.0;
  if(isExL){
    TH1F* vv_yLyMyT = DC.getHisto(fVV, baseDir+"/Iso/ExCTag/", "sf_CTag_yLyMyT_wt", fTT);
    TH1F* vv_yLyMnT = DC.getHisto(fVV, baseDir+"/Iso/ExCTag/", "sf_CTag_yLyMnT_wt", fTT);
    TH1F* vv_yLnMyT = DC.getHisto(fVV, baseDir+"/Iso/ExCTag/", "sf_CTag_yLnMyT_wt", fTT);
    TH1F* vv_yLnMnT = DC.getHisto(fVV, baseDir+"/Iso/ExCTag/", "sf_CTag_yLnMnT_wt", fTT);
    unc_vv_ExL = DC.getUncExL(vv_yLyMyT, vv_yLyMnT, vv_yLnMyT, vv_yLnMnT);
  }
  if(isExM){
    TH1F* vv_yMyT = DC.getHisto(fVV, baseDir+"/Iso/ExCTag/", "sf_CTag_yMyT_wt", fTT);
    TH1F* vv_yMnT = DC.getHisto(fVV, baseDir+"/Iso/ExCTag/", "sf_CTag_yMnT_wt", fTT);
    unc_vv_ExM = DC.getUncExM(vv_yMyT, vv_yMnT);
  }

  //QCD MC
  double sf_qcd = 1.0;
  /*
  TH1F* qcd = DC.readWriteHisto(fQCD, baseDir+"/"+histSubDir, histName, sf_qcd, fout, fTT, "qcd", true);
  TH1F* qcd_JESUp = DC.readWriteHisto(fQCD, "JESPlus/"+histSubDir, histName, sf_qcd, fout, fTT, "qcd_JESUp", true);
  TH1F* qcd_JESDown = DC.readWriteHisto(fQCD, "JESMinus/"+histSubDir, histName, sf_qcd, fout, fTT, "qcd_JESDown", true);
  TH1F* qcd_PileupUp = DC.readWriteHisto(fQCD, "PileupPlus/"+histSubDir, histName, sf_qcd, fout, fTT, "qcd_PileupUp", true);
  TH1F* qcd_PileupDown = DC.readWriteHisto(fQCD, "PileupMinus/"+histSubDir, histName, sf_qcd, fout, fTT, "qcd_PileupDown", true);
  TH1F* qcd_JERUp = DC.readWriteHisto(fQCD, "JERPlus/"+histSubDir, histName, sf_qcd, fout, fTT, "qcd_JERUp", true);
  TH1F* qcd_JERDown = DC.readWriteHisto(fQCD, "JERMinus/"+histSubDir, histName, sf_qcd, fout, fTT, "qcd_JERDown", true);
  TH1F* qcd_bcTag1Up = DC.readWriteHisto(fQCD, "bcTagPlus1/"+histSubDir, histName, sf_qcd, fout, fTT, "qcd_bcTag1Up", true);
  TH1F* qcd_bcTag1Down = DC.readWriteHisto(fQCD, "bcTagMinus1/"+histSubDir, histName, sf_qcd, fout, fTT, "qcd_bcTag1Down", true);
  TH1F* qcd_bcTag2Up = DC.readWriteHisto(fQCD, "bcTagPlus2/"+histSubDir, histName, sf_qcd, fout, fTT, "qcd_bcTag2Up", true);
  TH1F* qcd_bcTag2Down = DC.readWriteHisto(fQCD, "bcTagMinus2/"+histSubDir, histName, sf_qcd, fout, fTT, "qcd_bcTag2Down", true);
  TH1F* qcd_bcTag3Up = DC.readWriteHisto(fQCD, "bcTagPlus3/"+histSubDir, histName, sf_qcd, fout, fTT, "qcd_bcTag3Up", true);
  TH1F* qcd_bcTag3Down = DC.readWriteHisto(fQCD, "bcTagMinus3/"+histSubDir, histName, sf_qcd, fout, fTT, "qcd_bcTag3Down", true);
  */
  //QCD data driven
  //cout<<baseDir+"/"+histSubDir+"/"+histName<<endl;
  TH1F* qcd_dd = DC.readWriteHisto(fQCD_dd, baseDir+"/"+histSubDir, histName, sf_qcd, fout, fTT, "qcd", true);
  double stat_unc_qcd = DC.getStatUnc(qcd_dd, 0);
  // cout<<"qcd stat unc: "<<stat_unc_qcd<<endl;
  // cout<<"qcd = "<<qcd_dd->Integral()<<endl;
  double qcd_unc = DC.getSysUncQcd(fData, fTT, fST, fWJ, fDY,  fVV, histSubDir_+"/", histName, false);

  //Data
  double sf_data = 1.0; //should be 1, always
  TH1F* data_obs = DC.readWriteHisto(fData, baseDir+"/"+histSubDir, histName, sf_data, fout, fTT, "data_obs", true);
  //cout<<"data_obs================: "<<data_obs->Integral()<<endl;

  //wh
  //double sf_wh = 1.0;
  double sf_wh = 1.0/0.12155; //2*0.065*(1-0.065) 
  TH1F* wh = DC.readWriteHisto(fWH, baseDir+"/"+histSubDir, histName, sf_wh, fout, fTT, label, true);
  TH1F* wh_JESUp = DC.readWriteHisto(fWH, "JESPlus/"+histSubDir, histName, sf_wh, fout, fTT, label+"_JESUp", true);
  TH1F* wh_JESDown = DC.readWriteHisto(fWH, "JESMinus/"+histSubDir, histName, sf_wh, fout, fTT, label+"_JESDown", true);
  TH1F* wh_PileupUp = DC.readWriteHisto(fWH, "PileupPlus/"+histSubDir, histName, sf_wh, fout, fTT, label+"_PileupUp", true);
  TH1F* wh_PileupDown = DC.readWriteHisto(fWH, "PileupMinus/"+histSubDir, histName, sf_wh, fout, fTT, label+"_PileupDown", true);
  TH1F* wh_JERUp = DC.readWriteHisto(fWH, "JERPlus/"+histSubDir, histName, sf_wh, fout, fTT, label+"_JERUp", true);
  TH1F* wh_JERDown = DC.readWriteHisto(fWH, "JERMinus/"+histSubDir, histName, sf_wh, fout, fTT, label+"_JERDown", true);
  TH1F* wh_topPtUp = DC.readWriteHisto(fWH,  "TopPtPlus/"+histSubDir, histName, sf_wh, fout, fTT, label+"_topPtUp", true);
  TH1F* wh_topPtDown = DC.readWriteHisto(fWH, "TopPtMinus/"+histSubDir, histName, sf_wh, fout, fTT, label+"_topPtDown", true);
  TH1F* wh_bcTag1Up = DC.readWriteHisto(fWH, "bcTagPlus1/"+histSubDir, histName, sf_wh, fout, fTT, label+"_bcTag1Up", true);
  TH1F* wh_bcTag1Down = DC.readWriteHisto(fWH, "bcTagMinus1/"+histSubDir, histName, sf_wh, fout, fTT, label+"_bcTag1Down", true);
  TH1F* wh_bcTag2Up = DC.readWriteHisto(fWH, "bcTagPlus2/"+histSubDir, histName, sf_wh, fout, fTT, label+"_bcTag2Up", true);
  TH1F* wh_bcTag2Down = DC.readWriteHisto(fWH, "bcTagMinus2/"+histSubDir, histName, sf_wh, fout, fTT, label+"_bcTag2Down", true);
  TH1F* wh_bcTag3Up = DC.readWriteHisto(fWH, "bcTagPlus3/"+histSubDir, histName, sf_wh, fout, fTT, label+"_bcTag3Up", true);
  TH1F* wh_bcTag3Down = DC.readWriteHisto(fWH, "bcTagMinus3/"+histSubDir, histName, sf_wh, fout, fTT, label+"_bcTag3Down", true);
  //TH1F* wh_bin9up = DC.readWriteHisto(fWH, baseDir+"/"+histSubDir, histName, sf_wh, fout, fTT, label+"_CMS_stat_cat1_WH_bin_9Up", true);
  
  double unc_wh_ExL = 1.0;
  double unc_wh_ExM = 1.0;
  if(isExL){
    TH1F* wh_yLyMyT = DC.getHisto(fWH, baseDir+"/Iso/ExCTag/", "sf_CTag_yLyMyT_wt", fTT, sf_wh);
    TH1F* wh_yLyMnT = DC.getHisto(fWH, baseDir+"/Iso/ExCTag/", "sf_CTag_yLyMnT_wt", fTT, sf_wh);
    TH1F* wh_yLnMyT = DC.getHisto(fWH, baseDir+"/Iso/ExCTag/", "sf_CTag_yLnMyT_wt", fTT, sf_wh);
    TH1F* wh_yLnMnT = DC.getHisto(fWH, baseDir+"/Iso/ExCTag/", "sf_CTag_yLnMnT_wt", fTT, sf_wh);
    unc_wh_ExL = DC.getUncExL(wh_yLyMyT, wh_yLyMnT, wh_yLnMyT, wh_yLnMnT);
  }
  if(isExM){
    TH1F* wh_yMyT = DC.getHisto(fWH, baseDir+"/Iso/ExCTag/", "sf_CTag_yMyT_wt", fTT, sf_wh);
    TH1F* wh_yMnT = DC.getHisto(fWH, baseDir+"/Iso/ExCTag/", "sf_CTag_yMnT_wt", fTT, sf_wh);
    unc_wh_ExM = DC.getUncExM(wh_yMyT, wh_yMnT);
  }
  //open input template data card
  ifstream in;
  char* c = new char[1000];
  in.open("MyTemplateDataCard.txt");
  //create output data card for 13 TeV
  string outDataCard = "datacard_hcs_13TeV_WH.txt";
  string histName_str(histSubDir_+TString("_")+histName);
  if(isMuChannel) outDataCard = "datacard_hcs_13TeV_mu_"+histName_str+"_WH%d.txt"; 
  else outDataCard = "datacard_hcs_13TeV_ele_"+histName_str+"_WH%d.txt";
  ofstream out(Form(outDataCard.c_str(), mass));
  out.precision(8);

  time_t secs=time(0);
  tm *t=localtime(&secs);
  while (in.good()){
    in.getline(c,1000,'\n');
    if (in.good()){
      string line(c);
      if(line.find("Date")!=string::npos){
        string day = string(Form("%d",t->tm_mday));
        string month = string(Form("%d",t->tm_mon+1));
        string year = string(Form("%d",t->tm_year+1900));
        line.replace( line.find("XXX") , 3 , day+"/"+month+"/"+year);
        out << line << endl;
      }
      else if(line.find("Description")!=string::npos){
        line.replace( line.find("YYY") , 3 , string(Form("%d", mass)) );
        line.replace( line.find("ZZZ") , 3 , string(Form("%f", totLumi)) ); 
        line.replace( line.find("CCC") , 3 , string(Form("%s", string(channelName).c_str())) ); 
        out << line << endl;
      }
      else if(line.find("shapes")!=string::npos){
        line.replace( line.find("XXX") , 3 , string(TString("Shapes_hcs_13TeV_")+channelName+TString("_")+histSubDir_+TString("_")+histName+TString("_")+label));
        out << line << endl;
      }
      else if(line.find("Observation")!=string::npos){
        line.replace( line.find("XXX") , 3 , string(Form("%.0f", data_obs->Integral())));
        out << line << endl;
      }
      else if(line.find("process")!=string::npos && line.find("WH")!=string::npos){
        line.replace( line.find("YYY") , 3 , string(Form("%d", mass)) );
        out << line << endl;
      }
      else if(line.find("rate")!=string::npos){
        string rate = "rate               ";  
        string space = "     ";
        out << rate ;
        out << space << wh->Integral()
            << space << ttbar->Integral()
            << space << wjet->Integral()
            << space << zjet->Integral()
            << space << stop->Integral()
            << space << vv->Integral()
            << space << qcd_dd->Integral()
            << endl;
      }
      else if(line.find("CMS_eff_lep ")!=string::npos){  
        if(isMuChannel) line.replace( line.find("lep") , 4 , string(Form("%s", "m")));   
        else line.replace( line.find("lep") , 4 , string(Form("%s", "e")));
        out << line << endl;
      }  
      else if(line.find("CMS_eff_bcInc1 ")!=string::npos){
        float bTagUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_bcTag1Up, wh_bcTag1Down) : 1.00;
        line.replace( line.find("HHHH") , 4 , string(Form("%.3f", bTagUnc_wh)) );
        
        float bTagUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_bcTag1Up, ttbar_bcTag1Down) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", bTagUnc_ttbar)) ); 
        
        float bTagUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_bcTag1Up, wjet_bcTag1Down) : 1.00;
        line.replace( line.find("WWWW") , 4 , string(Form("%.3f", bTagUnc_wjet)) ); 
       
        float bTagUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_bcTag1Up, zjet_bcTag1Down) : 1.00;
        line.replace( line.find("DDDD") , 4 , string(Form("%.3f", bTagUnc_zjet)) ); 

        float bTagUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_bcTag1Up, stop_bcTag1Down) : 1.00; 
        line.replace( line.find("SSSS") , 4 , string(Form("%.3f", bTagUnc_stop)) ); 

        float bTagUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_bcTag1Up, vv_bcTag1Down) : 1.00;
        line.replace( line.find("VVVV") , 4 , string(Form("%.3f", bTagUnc_vv)) ); 
        out << line << endl;
      }
      else if(line.find("CMS_eff_bcInc2 ")!=string::npos){
        float cTagUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_bcTag2Up, wh_bcTag2Down) : 1.00;
        line.replace( line.find("HHHH") , 4 , string(Form("%.3f", cTagUnc_wh)) );
        
        float cTagUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_bcTag2Up, ttbar_bcTag2Down) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", cTagUnc_ttbar)) ); 
        
        float cTagUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_bcTag2Up, wjet_bcTag2Down) : 1.00;
        line.replace( line.find("WWWW") , 4 , string(Form("%.3f", cTagUnc_wjet)) ); 
       
        float cTagUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_bcTag2Up, zjet_bcTag2Down) : 1.00;
        line.replace( line.find("DDDD") , 4 , string(Form("%.3f", cTagUnc_zjet)) ); 
        
        float cTagUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_bcTag2Up, stop_bcTag2Down) : 1.00; 
        line.replace( line.find("SSSS") , 4 , string(Form("%.3f", cTagUnc_stop)) ); 

        float cTagUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_bcTag2Up, vv_bcTag2Down) : 1.00;
        line.replace( line.find("VVVV") , 4 , string(Form("%.3f", cTagUnc_vv)) ); 
        out << line << endl;
      }
      else if(line.find("CMS_eff_bcInc3 ")!=string::npos){
        float cTagUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_bcTag3Up, wh_bcTag3Down) : 1.00;
        line.replace( line.find("HHHH") , 4 , string(Form("%.3f", cTagUnc_wh)) );
        
        float cTagUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_bcTag3Up, ttbar_bcTag3Down) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", cTagUnc_ttbar)) ); 
        
        float cTagUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_bcTag3Up, wjet_bcTag3Down) : 1.00;
        line.replace( line.find("WWWW") , 4 , string(Form("%.3f", cTagUnc_wjet)) ); 
       
        float cTagUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_bcTag3Up, zjet_bcTag3Down) : 1.00;
        line.replace( line.find("DDDD") , 4 , string(Form("%.3f", cTagUnc_zjet)) ); 
        
        float cTagUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_bcTag3Up, stop_bcTag3Down) : 1.00; 
        line.replace( line.find("SSSS") , 4 , string(Form("%.3f", cTagUnc_stop)) ); 

        float cTagUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_bcTag3Up, vv_bcTag3Down) : 1.00;
        line.replace( line.find("VVVV") , 4 , string(Form("%.3f", cTagUnc_vv)) ); 
        out << line << endl;
      }
      else if(line.find("CMS_pileup")!=string::npos){
        float PileupUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_PileupUp, wh_PileupDown) : 1.00;
        line.replace( line.find("HHHH") , 4 , string(Form("%.3f", PileupUnc_wh)) );
        
        float PileupUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_PileupUp, ttbar_PileupDown) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", PileupUnc_ttbar)) ); 
        
        float PileupUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_PileupUp, wjet_PileupDown) : 1.00;
        line.replace( line.find("WWWW") , 4 , string(Form("%.3f", PileupUnc_wjet)) ); 
       
        float PileupUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_PileupUp, zjet_PileupDown) : 1.00;
        line.replace( line.find("DDDD") , 4 , string(Form("%.3f", PileupUnc_zjet)) ); 
        
        float PileupUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_PileupUp, stop_PileupDown) : 1.00; 
        line.replace( line.find("SSSS") , 4 , string(Form("%.3f", PileupUnc_stop)) ); 

        float PileupUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_PileupUp, vv_PileupDown) : 1.00;
        line.replace( line.find("VVVV") , 4 , string(Form("%.3f", PileupUnc_vv)) ); 
        out << line << endl;
      }
      else if(line.find("CMS_scale_j")!=string::npos){
        float JESUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_JESUp, wh_JESDown) : 1.00;
        line.replace( line.find("HHHH") , 4 , string(Form("%.3f", JESUnc_wh)) );
        
        float JESUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_JESUp, ttbar_JESDown) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", JESUnc_ttbar)) ); 
        
        float JESUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_JESUp, wjet_JESDown) : 1.00;
        line.replace( line.find("WWWW") , 4 , string(Form("%.3f", JESUnc_wjet)) ); 
       
        float JESUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_JESUp, zjet_JESDown) : 1.00;
        line.replace( line.find("DDDD") , 4 , string(Form("%.3f", JESUnc_zjet)) ); 
        
        float JESUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_JESUp, stop_JESDown) : 1.00; 
        line.replace( line.find("SSSS") , 4 , string(Form("%.3f", JESUnc_stop)) ); 

        float JESUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_JESUp, vv_JESDown) : 1.00;
        line.replace( line.find("VVVV") , 4 , string(Form("%.3f", JESUnc_vv)) ); 
        out << line << endl;
      }
      else if(line.find("CMS_res_j")!=string::npos){
        float JERUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_JERUp, wh_JERDown) : 1.00;
        line.replace( line.find("HHHH") , 4 , string(Form("%.3f", JERUnc_wh)) );
        
        float JERUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_JERUp, ttbar_JERDown) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", JERUnc_ttbar)) ); 
        
        float JERUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_JERUp, wjet_JERDown) : 1.00;
        line.replace( line.find("WWWW") , 4 , string(Form("%.3f", JERUnc_wjet)) ); 
       
        float JERUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_JERUp, zjet_JERDown) : 1.00;
        line.replace( line.find("DDDD") , 4 , string(Form("%.3f", JERUnc_zjet)) ); 
        
        float JERUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_JERUp, stop_JERDown) : 1.00; 
        line.replace( line.find("SSSS") , 4 , string(Form("%.3f", JERUnc_stop)) ); 

        float JERUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_JERUp, vv_JERDown) : 1.00;
        line.replace( line.find("VVVV") , 4 , string(Form("%.3f", JERUnc_vv)) ); 
        out << line << endl;
      }
      else if(line.find("CMS_norm_qcd")!=string::npos){  
        line.replace( line.find("QQQQ") , 4 , string(Form("%.3f", qcd_unc)));   
        //if(isMuChannel) line.replace( line.find("QQQQ") , 4 , string(Form("%.4f", 1.10)));   
        //else line.replace(line.find("QQQQ") , 4 , string(Form("%.4f", 1.10)));   
        out << line << endl;  
      }
      else if(line.find("CMS_topPtReweight")!=string::npos){
        float topPtUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_topPtUp, wh_topPtDown) : 1.00;
        line.replace( line.find("HHHH") , 4 , string(Form("%.3f", topPtUnc_wh)) );
        
        float topPtUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_topPtUp, ttbar_topPtDown) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", topPtUnc_ttbar)) ); 
        out << line << endl;
      }
      else if(line.find("scaleRF_tt")!=string::npos){
        float scaleUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_scaleUp, ttbar_scaleDown) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", scaleUnc_ttbar)) ); 
        out << line << endl;
      }
      else if(line.find("hDamp_tt")!=string::npos){
        float matchUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_matchingUp, ttbar_matchingDown) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", matchUnc_ttbar)) ); 
        out << line << endl;
      }
      else if(line.find("topMass_tt")!=string::npos){
        float mtopUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_mtop1735, ttbar_mtop1715) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", mtopUnc_ttbar)) ); 
        out << line << endl;
      }
      else{ //default without changes
        out << line << endl;
      }
    }
  } 
  if(isExL){
    string rate = "CMS_eff_cExL       lnN";  
    string space = "     ";
    out << rate ;
    out << space <<string(Form("%.3f", unc_wh_ExL))
        << space <<string(Form("%.3f", unc_ttbar_ExL))
        << space <<string(Form("%.3f", unc_wjet_ExL))
        << space <<string(Form("%.3f", unc_zjet_ExL))
        << space <<string(Form("%.3f", unc_stop_ExL))
        << space <<string(Form("%.3f", unc_vv_ExL))
        << space <<string(Form("%.3f", 1.0))
        << endl;
  }
  if(isExM){
    string rate = "CMS_eff_cExM       lnN";  
    string space = "     ";
    out << rate ;
    out << space <<string(Form("%.3f", unc_wh_ExM))
        << space <<string(Form("%.3f", unc_ttbar_ExM))
        << space <<string(Form("%.3f", unc_wjet_ExM))
        << space <<string(Form("%.3f", unc_zjet_ExM))
        << space <<string(Form("%.3f", unc_stop_ExM))
        << space <<string(Form("%.3f", unc_vv_ExM))
        << space <<string(Form("%.3f", 1.0))
        << endl;
  }
  out<<"* autoMCStats 0 1"<<endl;
  out.close();
  in.close();
  fout->Close();
}

void MyHPlusDataCardMakerNano(TString inFileDir="stack_20180418_Mu_Sys_PreAppComent",
			      TString syear="", 
			      TString histSubDir_="", 
			      TString histName="_kb_mjj_", 
			      TString channelName="mu", 
			      int mass=80, 
			      TString label="WH80", 
			      TString hPlusFileName="all_HplusM80.root")
  {
    
  bool isBinStat = false;  int nonStatBins = 30;
  MyHPlusDataCardMaker DC;
  //TString baseDir = "topPtWeight";
  TString baseDir = "base";
  TString histSubDir = "/Iso/";
  bool isMuChannel = false; 
  if(channelName=="mu") isMuChannel = true;
  inFileDir = inFileDir + "/" + syear;
  int year = syear.Atoi();
  double totLumi = 36.31; //2016
  float lumiUnc = 1.012;//1.2% for 2016 following https://twiki.cern.ch/twiki/bin/viewauth/CMS/TWikiLUM
  if(year==2017){
    totLumi = 41.48; // 2017
    lumiUnc = 1.023; //
  }
  if(year==2018){
    totLumi = 59.83; //2018
    lumiUnc = 1.025; //
  }
  //lumiUnc = 1.016; //run2
  histName += channelName;
  
  printf("==== Year : %d ======\n",year);
  ///INPUT FILES
  TFile* fData    = (isMuChannel) ? TFile::Open(inFileDir+"/all_DataMu.root") : TFile::Open(inFileDir+"/all_DataEle.root");
  //bkg
  TFile* fVV      = TFile::Open(inFileDir+"/all_VBFusion.root");
  TFile* fDY      = TFile::Open(inFileDir+"/all_DYjets.root");
  TFile* fWJ      = TFile::Open(inFileDir+"/all_Wjets.root");
  TFile* fQCD     = (isMuChannel) ? TFile::Open(inFileDir+"/all_MCQCDMu.root") : TFile::Open(inFileDir+"/all_MCQCDEle.root");
  TFile* fST      = TFile::Open(inFileDir+"/all_singleTop.root");
  TFile* fTT      = TFile::Open(inFileDir+"/all_TTbar.root");
  TFile* fTG      = TFile::Open(inFileDir+"/all_TTG.root");
  TFile* fTH      = TFile::Open(inFileDir+"/all_TTH.root");
  TFile* fTW      = TFile::Open(inFileDir+"/all_TTW.root");
  TFile* fTZ      = TFile::Open(inFileDir+"/all_TTZ.root");
  
  //signal
  TFile *fWH  = TFile::Open(inFileDir+"/"+hPlusFileName);
  TString sigFile = hPlusFileName;
  //data driven qcd
  TFile* fQCD_dd = TFile::Open(inFileDir+"/all_QCDdd.root"); 
  
  //OUTPUT FILE
  TFile *fout = new TFile(TString("Shapes_hcs_13TeV_")+channelName+TString("_")+histSubDir_+TString("_")+histName+TString("_")+label+TString("_")+syear+TString(".root"), "RECREATE");
  
  //For one extra NP
  bool isExL = false;
  bool isExM = false;
  if(histName.Contains("ExL")) isExL = true;
  if(histName.Contains("ExM")) isExM = true;
  
  string hist_extn = "";
  //hist_extn += channelName.Data();
  //hist_extn += syear.Data();
  // hist_extn = "";
  bool isUncorrYearLn = true;
  bool isUncorrYearShape = true;
  string hist_extn_temp = hist_extn;
  if(!isUncorrYearShape) hist_extn = "";
  string uncorr_extn = syear.Data();

  bool isNormalized = false;
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //ttbar
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  double sf_ttbar = 1.0; 
  baseDir = "TTbar";
  TH1F* ttbar = DC.readWriteHisto(fTT, baseDir+"/base"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar", true);
  TH1F *ttbar_LeptonUp,*ttbar_LeptonDown;
  if(isMuChannel){
    ttbar_LeptonUp = DC.readWriteHisto(fTT, baseDir+"/mueffup"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_Lepton"+hist_extn+"Up", true);
    ttbar_LeptonDown = DC.readWriteHisto(fTT, baseDir+"/mueffdown"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_Lepton"+hist_extn+"Down", true);
  }else{
    ttbar_LeptonUp = DC.readWriteHisto(fTT, baseDir+"/eleeffup"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_Lepton"+hist_extn+"Up", true);
    ttbar_LeptonDown = DC.readWriteHisto(fTT, baseDir+"/eleeffdown"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_Lepton"+hist_extn+"Down", true);
  }
  TH1F* ttbar_absmpfbUp = DC.readWriteHisto(fTT, baseDir+"/absmpfbup"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_absmpfb"+hist_extn+"Up", true);
  TH1F* ttbar_absmpfbDown = DC.readWriteHisto(fTT, baseDir+"/absmpfbdown"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_absmpfb"+hist_extn+"Down", true);
  TH1F* ttbar_abssclUp = DC.readWriteHisto(fTT, baseDir+"/abssclup"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_absscl"+hist_extn+"Up", true);
  TH1F* ttbar_abssclDown = DC.readWriteHisto(fTT, baseDir+"/absscldown"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_absscl"+hist_extn+"Down", true);
  TH1F* ttbar_absstatUp = DC.readWriteHisto(fTT, baseDir+"/absstatup"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_absstat"+uncorr_extn+"Up", true);
  TH1F* ttbar_absstatDown = DC.readWriteHisto(fTT, baseDir+"/absstatdown"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_absstat"+uncorr_extn+"Down", true);
  
  TH1F* ttbar_fragUp = DC.readWriteHisto(fTT, baseDir+"/fragup"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_frag"+hist_extn+"Up", true);
  TH1F* ttbar_fragDown = DC.readWriteHisto(fTT, baseDir+"/fragdown"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_frag"+hist_extn+"Down", true);
  TH1F* ttbar_pudatamcUp = DC.readWriteHisto(fTT, baseDir+"/pudatamcup"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_pudatamc"+hist_extn+"Up", true);
  TH1F* ttbar_pudatamcDown = DC.readWriteHisto(fTT, baseDir+"/pudatamcdown"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_pudatamc"+hist_extn+"Down", true);

  TH1F* ttbar_puptbbUp = DC.readWriteHisto(fTT, baseDir+"/puptbbup"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_puptbb"+hist_extn+"Up", true);
  TH1F* ttbar_puptbbDown = DC.readWriteHisto(fTT, baseDir+"/puptbbdown"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_puptbb"+hist_extn+"Down", true);
  TH1F* ttbar_puptec1Up = DC.readWriteHisto(fTT, baseDir+"/puptec1up"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_puptec1"+hist_extn+"Up", true);
  TH1F* ttbar_puptec1Down = DC.readWriteHisto(fTT, baseDir+"/puptec1down"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_puptec1"+hist_extn+"Down", true);

  TH1F* ttbar_puptec2Up = DC.readWriteHisto(fTT, baseDir+"/puptec2up"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_puptec2"+hist_extn+"Up", true);
  TH1F* ttbar_puptec2Down = DC.readWriteHisto(fTT, baseDir+"/puptec2down"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_puptec2"+hist_extn+"Down", true);
  TH1F* ttbar_pupthfUp = DC.readWriteHisto(fTT, baseDir+"/pupthfup"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_pupthf"+hist_extn+"Up", true);
  TH1F* ttbar_pupthfDown = DC.readWriteHisto(fTT, baseDir+"/pupthfdown"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_pupthf"+hist_extn+"Down", true);

  TH1F* ttbar_puptrefUp = DC.readWriteHisto(fTT, baseDir+"/puptrefup"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_puptref"+hist_extn+"Up", true);
  TH1F* ttbar_puptrefDown = DC.readWriteHisto(fTT, baseDir+"/puptrefdown"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_puptref"+hist_extn+"Down", true);
  TH1F* ttbar_relfsrUp = DC.readWriteHisto(fTT, baseDir+"/relfsrup"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_relfsr"+hist_extn+"Up", true);
  TH1F* ttbar_relfsrDown = DC.readWriteHisto(fTT, baseDir+"/relfsrdown"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_relfsr"+hist_extn+"Down", true);

  TH1F* ttbar_relbalUp = DC.readWriteHisto(fTT, baseDir+"/relbalup"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_relbal"+hist_extn+"Up", true);
  TH1F* ttbar_relbalDown = DC.readWriteHisto(fTT, baseDir+"/relbaldown"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_relbal"+hist_extn+"Down", true);
  TH1F* ttbar_relsampleUp = DC.readWriteHisto(fTT, baseDir+"/relsampleup"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_relsample"+uncorr_extn+"Up", true);
  TH1F* ttbar_relsampleDown = DC.readWriteHisto(fTT, baseDir+"/relsampledown"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_relsample"+uncorr_extn+"Down", true);

  TH1F* ttbar_reljerec1Up = DC.readWriteHisto(fTT, baseDir+"/reljerec1up"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_reljerec1"+uncorr_extn+"Up", true);
  TH1F* ttbar_reljerec1Down = DC.readWriteHisto(fTT, baseDir+"/reljerec1down"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_reljerec1"+uncorr_extn+"Down", true);
  TH1F* ttbar_reljerec2Up = DC.readWriteHisto(fTT, baseDir+"/reljerec2up"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_reljerec2"+uncorr_extn+"Up", true);
  TH1F* ttbar_reljerec2Down = DC.readWriteHisto(fTT, baseDir+"/reljerec2down"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_reljerec2"+uncorr_extn+"Down", true);

  TH1F* ttbar_reljerhfUp = DC.readWriteHisto(fTT, baseDir+"/reljerhfup"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_reljerhf"+hist_extn+"Up", true);
  TH1F* ttbar_reljerhfDown = DC.readWriteHisto(fTT, baseDir+"/reljerhfdown"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_reljerhf"+hist_extn+"Down", true);
  TH1F* ttbar_relptbbUp = DC.readWriteHisto(fTT, baseDir+"/relptbbup"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_relptbb"+hist_extn+"Up", true);
  TH1F* ttbar_relptbbDown = DC.readWriteHisto(fTT, baseDir+"/relptbbdown"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_relptbb"+hist_extn+"Down", true);

  TH1F* ttbar_relptec1Up = DC.readWriteHisto(fTT, baseDir+"/relptec1up"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_relptec1"+uncorr_extn+"Up", true);
  TH1F* ttbar_relptec1Down = DC.readWriteHisto(fTT, baseDir+"/relptec1down"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_relptec1"+uncorr_extn+"Down", true);
  TH1F* ttbar_relptec2Up = DC.readWriteHisto(fTT, baseDir+"/relptec2up"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_relptec2"+uncorr_extn+"Up", true);
  TH1F* ttbar_relptec2Down = DC.readWriteHisto(fTT, baseDir+"/relptec2down"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_relptec2"+uncorr_extn+"Down", true);

  TH1F* ttbar_relpthfUp = DC.readWriteHisto(fTT, baseDir+"/relpthfup"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_relpthf"+hist_extn+"Up", true);
  TH1F* ttbar_relpthfDown = DC.readWriteHisto(fTT, baseDir+"/relpthfdown"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_relpthf"+hist_extn+"Down", true);
  TH1F* ttbar_relstatecUp = DC.readWriteHisto(fTT, baseDir+"/relstatecup"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_relstatec"+uncorr_extn+"Up", true);
  TH1F* ttbar_relstatecDown = DC.readWriteHisto(fTT, baseDir+"/relstatecdown"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_relstatec"+uncorr_extn+"Down", true);

  TH1F* ttbar_relstatfsrUp = DC.readWriteHisto(fTT, baseDir+"/relstatfsrup"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_relstatfsr"+uncorr_extn+"Up", true);
  TH1F* ttbar_relstatfsrDown = DC.readWriteHisto(fTT, baseDir+"/relstatfsrdown"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_relstatfsr"+uncorr_extn+"Down", true);
  TH1F* ttbar_relstathfUp = DC.readWriteHisto(fTT, baseDir+"/relstathfup"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_relstathf"+uncorr_extn+"Up", true);
  TH1F* ttbar_relstathfDown = DC.readWriteHisto(fTT, baseDir+"/relstathfdown"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_relstathf"+uncorr_extn+"Down", true);

  TH1F* ttbar_singpiecalUp = DC.readWriteHisto(fTT, baseDir+"/singpiecalup"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_singpiecal"+hist_extn+"Up", true);
  TH1F* ttbar_singpiecalDown = DC.readWriteHisto(fTT, baseDir+"/singpiecaldown"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_singpiecal"+hist_extn+"Down", true);
  TH1F* ttbar_singpihcalUp = DC.readWriteHisto(fTT, baseDir+"/singpihcalup"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_singpihcal"+hist_extn+"Up", true);
  TH1F* ttbar_singpihcalDown = DC.readWriteHisto(fTT, baseDir+"/singpihcaldown"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_singpihcal"+hist_extn+"Down", true);

  TH1F* ttbar_flavorqcdUp = DC.readWriteHisto(fTT, baseDir+"/flavorqcdup"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_flavorqcd"+hist_extn+"Up", true);
  TH1F* ttbar_flavorqcdDown = DC.readWriteHisto(fTT, baseDir+"/flavorqcddown"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_flavorqcd"+hist_extn+"Down", true);
  TH1F* ttbar_timeptetaUp = DC.readWriteHisto(fTT, baseDir+"/timeptetaup"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_timepteta"+hist_extn+"Up", true);
  TH1F* ttbar_timeptetaDown = DC.readWriteHisto(fTT, baseDir+"/timeptetadown"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_timepteta"+hist_extn+"Down", true);

  TH1F* ttbar_PileupUp = DC.readWriteHisto(fTT, baseDir+"/puup"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_Pileup"+hist_extn+"Up", true);
  TH1F* ttbar_PileupDown = DC.readWriteHisto(fTT, baseDir+"/pudown"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_Pileup"+hist_extn+"Down", true);
  TH1F *ttbar_PrefireUp, *ttbar_PrefireDown;
  if(year==2016 or year==2017){
    ttbar_PrefireUp = DC.readWriteHisto(fTT, baseDir+"/prefireup"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_Prefire"+hist_extn+"Up", true);
    ttbar_PrefireDown = DC.readWriteHisto(fTT, baseDir+"/prefiredown"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_Prefire"+hist_extn+"Down", true);
  }else{
    ttbar_PrefireUp = DC.readWriteHisto(fTT, baseDir+"/base"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_Prefire"+hist_extn+"Up", true);
    ttbar_PrefireDown = DC.readWriteHisto(fTT, baseDir+"/base"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_Prefire"+hist_extn+"Down", true);
  }
  TH1F* ttbar_PUJetIDUp = DC.readWriteHisto(fTT, baseDir+"/pujetidup"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_PUJetID"+hist_extn+"Up", true);
  TH1F* ttbar_PUJetIDDown = DC.readWriteHisto(fTT, baseDir+"/pujetiddown"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_PUJetID"+hist_extn+"Down", true);
  TH1F* ttbar_JERUp = DC.readWriteHisto(fTT, baseDir+"/jerup"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_JER"+hist_extn+"Up", true);
  TH1F* ttbar_JERDown = DC.readWriteHisto(fTT, baseDir+"/jerdown"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_JER"+hist_extn+"Down", true);
  //\([a-z]+\)_\([a-zA-Z]+\) = DC.readWriteHisto(\([a-zA-Z]+\), baseDir\+"/\([a-z]+\)"\+histSubDir, histName, sf_\([a-z]+\), fout, \([a-zA-Z]+\), \(label\+\)?"\([a-zA-Z_]+\)", true, true, \([a-z]+\)); \1_\2 = DC.readWriteHisto(\3, baseDir+"/\4"+histSubDir, histName, sf_\5, fout, \6, \7"\8", true);
  TH1F* ttbar_bcstatUp = DC.readWriteHisto(fTT, baseDir+"/bcstatup"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_bcstat"+hist_extn+"Up", true, isNormalized, ttbar);
  TH1F* ttbar_bcstatDown = DC.readWriteHisto(fTT, baseDir+"/bcstatdown"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_bcstat"+hist_extn+"Down", true, isNormalized, ttbar);
  TH1F *ttbar_bcintpUp, *ttbar_bcintpDown, *ttbar_bcextpUp, *ttbar_bcextpDown, *ttbar_bcxdybUp, *ttbar_bcxdybDown, *ttbar_bcxdycUp, *ttbar_bcxdycDown, *ttbar_bcxwjcUp, *ttbar_bcxwjcDown;
  ttbar_bcintpUp = DC.readWriteHisto(fTT, baseDir+"/bcintpup"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_bcintp"+hist_extn+"Up", true, isNormalized, ttbar);
  ttbar_bcintpDown = DC.readWriteHisto(fTT, baseDir+"/bcintpdown"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_bcintp"+hist_extn+"Down", true, isNormalized, ttbar);
  ttbar_bcextpUp = DC.readWriteHisto(fTT, baseDir+"/bcextpup"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_bcextp"+hist_extn+"Up", true, isNormalized, ttbar);
  ttbar_bcextpDown = DC.readWriteHisto(fTT, baseDir+"/bcextpdown"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_bcextp"+hist_extn+"Down", true, isNormalized, ttbar);
  ttbar_bcxdybUp = DC.readWriteHisto(fTT, baseDir+"/bcxdybup"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_bcxdyb"+hist_extn+"Up", true, isNormalized, ttbar);
  ttbar_bcxdybDown = DC.readWriteHisto(fTT, baseDir+"/bcxdybdown"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_bcxdyb"+hist_extn+"Down", true, isNormalized, ttbar);
  ttbar_bcxdycUp = DC.readWriteHisto(fTT, baseDir+"/bcxdycup"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_bcxdyc"+hist_extn+"Up", true, isNormalized, ttbar);
  ttbar_bcxdycDown = DC.readWriteHisto(fTT, baseDir+"/bcxdycdown"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_bcxdyc"+hist_extn+"Down", true, isNormalized, ttbar);
  ttbar_bcxwjcUp = DC.readWriteHisto(fTT, baseDir+"/bcxwjcup"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_bcxwjc"+hist_extn+"Up", true, isNormalized, ttbar);
  ttbar_bcxwjcDown = DC.readWriteHisto(fTT, baseDir+"/bcxwjcdown"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_bcxwjc"+hist_extn+"Down", true, isNormalized, ttbar);
  
  TH1F* ttbar_pdfUp = DC.readWriteHisto(fTT, baseDir+"/pdfup"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_pdf"+hist_extn+"Up", true);
  TH1F* ttbar_pdfDown = DC.readWriteHisto(fTT, baseDir+"/pdfdown"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_pdf"+hist_extn+"Down", true);
  TH1F* ttbar_bclhemufUp = DC.readWriteHisto(fTT, baseDir+"/bclhemufup"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_bclhemuf"+hist_extn+"Up", true, isNormalized, ttbar);
  TH1F* ttbar_bclhemufDown = DC.readWriteHisto(fTT, baseDir+"/bclhemufdown"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_bclhemuf"+hist_extn+"Down", true, isNormalized, ttbar);
  TH1F* ttbar_bclhemurUp = DC.readWriteHisto(fTT, baseDir+"/bclhemurup"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_bclhemur"+hist_extn+"Up", true, isNormalized, ttbar);
  TH1F* ttbar_bclhemurDown = DC.readWriteHisto(fTT, baseDir+"/bclhemurdown"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_bclhemur"+hist_extn+"Down", true, isNormalized, ttbar);
  TH1F* ttbar_isrUp = DC.readWriteHisto(fTT, baseDir+"/isrup"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_isr"+hist_extn+"Up", true, isNormalized, ttbar);
  TH1F* ttbar_isrDown = DC.readWriteHisto(fTT, baseDir+"/isrdown"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_isr"+hist_extn+"Down", true, isNormalized, ttbar);
  TH1F* ttbar_fsrUp = DC.readWriteHisto(fTT, baseDir+"/fsrup"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_fsr"+hist_extn+"Up", true, isNormalized, ttbar);
  TH1F* ttbar_fsrDown = DC.readWriteHisto(fTT, baseDir+"/fsrdown"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_fsr"+hist_extn+"Down", true, isNormalized, ttbar);
  TH1F* ttbar_topPtUp = DC.readWriteHisto(fTT, baseDir+"/topptup"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_topPt"+hist_extn+"Up", true, isNormalized, ttbar);
  TH1F* ttbar_topPtDown = DC.readWriteHisto(fTT, baseDir+"/topptdown"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_topPt"+hist_extn+"Down", true, isNormalized, ttbar);
  
  double sf_ttbar_cp5Up = 1; 
  TH1F* ttbar_cp5Up = DC.readWriteHisto(fTT, baseDir+"/cp5up"+histSubDir, histName, sf_ttbar_cp5Up, fout, fTT, "ttbar_CP5_tt"+hist_extn+"Up", true, isNormalized, ttbar);
  double sf_ttbar_cp5Down = 1; 
  TH1F* ttbar_cp5Down = DC.readWriteHisto(fTT, baseDir+"/cp5down"+histSubDir, histName, sf_ttbar_cp5Down, fout, fTT, "ttbar_CP5_tt"+hist_extn+"Down", true, isNormalized, ttbar);
  double sf_ttbar_matchingUp = 1; 
  TH1F* ttbar_matchingUp = DC.readWriteHisto(fTT, baseDir+"/hdampup"+histSubDir, histName, sf_ttbar_matchingUp, fout, fTT, "ttbar_hDamp_tt"+hist_extn+"Up", true, isNormalized, ttbar);
  double sf_ttbar_matchingDown = 1; 
  TH1F* ttbar_matchingDown = DC.readWriteHisto(fTT, baseDir+"/hdampdown"+histSubDir, histName, sf_ttbar_matchingDown, fout, fTT, "ttbar_hDamp_tt"+hist_extn+"Down", true, isNormalized, ttbar);
  double sf_ttbar_mtop1715 = 1; 
  TH1F* ttbar_mtop1715 = DC.readWriteHisto(fTT, baseDir+"/mtopup"+histSubDir, histName, sf_ttbar_mtop1715, fout, fTT, "ttbar_topMass_tt"+hist_extn+"Down", true, isNormalized, ttbar);
  double sf_ttbar_mtop1735 = 1; 
  TH1F* ttbar_mtop1735 = DC.readWriteHisto(fTT, baseDir+"/mtopdown"+histSubDir, histName, sf_ttbar_mtop1735, fout, fTT, "ttbar_topMass_tt"+hist_extn+"Up", true, isNormalized, ttbar);
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // TT+G
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //ttg+jets
  double sf_ttg = 1;
  baseDir = "TTG";
  TH1F* ttg = DC.readWriteHisto(fTG, baseDir+"/base"+histSubDir, histName, sf_ttg, fout, fTT, "ttg", true);
  TH1F *ttg_LeptonUp,*ttg_LeptonDown;
  if(isMuChannel){
    ttg_LeptonUp = DC.readWriteHisto(fTG, baseDir+"/mueffup"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_Lepton"+hist_extn+"Up", true);
    ttg_LeptonDown = DC.readWriteHisto(fTG, baseDir+"/mueffdown"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_Lepton"+hist_extn+"Down", true);
  }else{
    ttg_LeptonUp = DC.readWriteHisto(fTG, baseDir+"/eleeffup"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_Lepton"+hist_extn+"Up", true);
    ttg_LeptonDown = DC.readWriteHisto(fTG, baseDir+"/eleeffdown"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_Lepton"+hist_extn+"Down", true);
  }
  TH1F* ttg_absmpfbUp = DC.readWriteHisto(fTG, baseDir+"/absmpfbup"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_absmpfb"+hist_extn+"Up", true);
  TH1F* ttg_absmpfbDown = DC.readWriteHisto(fTG, baseDir+"/absmpfbdown"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_absmpfb"+hist_extn+"Down", true);
  TH1F* ttg_abssclUp = DC.readWriteHisto(fTG, baseDir+"/abssclup"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_absscl"+hist_extn+"Up", true);
  TH1F* ttg_abssclDown = DC.readWriteHisto(fTG, baseDir+"/absscldown"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_absscl"+hist_extn+"Down", true);
  TH1F* ttg_absstatUp = DC.readWriteHisto(fTG, baseDir+"/absstatup"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_absstat"+uncorr_extn+"Up", true);
  TH1F* ttg_absstatDown = DC.readWriteHisto(fTG, baseDir+"/absstatdown"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_absstat"+uncorr_extn+"Down", true);
  
  TH1F* ttg_fragUp = DC.readWriteHisto(fTG, baseDir+"/fragup"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_frag"+hist_extn+"Up", true);
  TH1F* ttg_fragDown = DC.readWriteHisto(fTG, baseDir+"/fragdown"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_frag"+hist_extn+"Down", true);
  TH1F* ttg_pudatamcUp = DC.readWriteHisto(fTG, baseDir+"/pudatamcup"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_pudatamc"+hist_extn+"Up", true);
  TH1F* ttg_pudatamcDown = DC.readWriteHisto(fTG, baseDir+"/pudatamcdown"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_pudatamc"+hist_extn+"Down", true);

  TH1F* ttg_puptbbUp = DC.readWriteHisto(fTG, baseDir+"/puptbbup"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_puptbb"+hist_extn+"Up", true);
  TH1F* ttg_puptbbDown = DC.readWriteHisto(fTG, baseDir+"/puptbbdown"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_puptbb"+hist_extn+"Down", true);
  TH1F* ttg_puptec1Up = DC.readWriteHisto(fTG, baseDir+"/puptec1up"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_puptec1"+hist_extn+"Up", true);
  TH1F* ttg_puptec1Down = DC.readWriteHisto(fTG, baseDir+"/puptec1down"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_puptec1"+hist_extn+"Down", true);

  TH1F* ttg_puptec2Up = DC.readWriteHisto(fTG, baseDir+"/puptec2up"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_puptec2"+hist_extn+"Up", true);
  TH1F* ttg_puptec2Down = DC.readWriteHisto(fTG, baseDir+"/puptec2down"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_puptec2"+hist_extn+"Down", true);
  TH1F* ttg_pupthfUp = DC.readWriteHisto(fTG, baseDir+"/pupthfup"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_pupthf"+hist_extn+"Up", true);
  TH1F* ttg_pupthfDown = DC.readWriteHisto(fTG, baseDir+"/pupthfdown"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_pupthf"+hist_extn+"Down", true);

  TH1F* ttg_puptrefUp = DC.readWriteHisto(fTG, baseDir+"/puptrefup"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_puptref"+hist_extn+"Up", true);
  TH1F* ttg_puptrefDown = DC.readWriteHisto(fTG, baseDir+"/puptrefdown"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_puptref"+hist_extn+"Down", true);
  TH1F* ttg_relfsrUp = DC.readWriteHisto(fTG, baseDir+"/relfsrup"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_relfsr"+hist_extn+"Up", true);
  TH1F* ttg_relfsrDown = DC.readWriteHisto(fTG, baseDir+"/relfsrdown"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_relfsr"+hist_extn+"Down", true);

  TH1F* ttg_relbalUp = DC.readWriteHisto(fTG, baseDir+"/relbalup"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_relbal"+hist_extn+"Up", true);
  TH1F* ttg_relbalDown = DC.readWriteHisto(fTG, baseDir+"/relbaldown"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_relbal"+hist_extn+"Down", true);
  TH1F* ttg_relsampleUp = DC.readWriteHisto(fTG, baseDir+"/relsampleup"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_relsample"+uncorr_extn+"Up", true);
  TH1F* ttg_relsampleDown = DC.readWriteHisto(fTG, baseDir+"/relsampledown"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_relsample"+uncorr_extn+"Down", true);

  TH1F* ttg_reljerec1Up = DC.readWriteHisto(fTG, baseDir+"/reljerec1up"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_reljerec1"+uncorr_extn+"Up", true);
  TH1F* ttg_reljerec1Down = DC.readWriteHisto(fTG, baseDir+"/reljerec1down"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_reljerec1"+uncorr_extn+"Down", true);
  TH1F* ttg_reljerec2Up = DC.readWriteHisto(fTG, baseDir+"/reljerec2up"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_reljerec2"+uncorr_extn+"Up", true);
  TH1F* ttg_reljerec2Down = DC.readWriteHisto(fTG, baseDir+"/reljerec2down"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_reljerec2"+uncorr_extn+"Down", true);

  TH1F* ttg_reljerhfUp = DC.readWriteHisto(fTG, baseDir+"/reljerhfup"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_reljerhf"+hist_extn+"Up", true);
  TH1F* ttg_reljerhfDown = DC.readWriteHisto(fTG, baseDir+"/reljerhfdown"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_reljerhf"+hist_extn+"Down", true);
  TH1F* ttg_relptbbUp = DC.readWriteHisto(fTG, baseDir+"/relptbbup"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_relptbb"+hist_extn+"Up", true);
  TH1F* ttg_relptbbDown = DC.readWriteHisto(fTG, baseDir+"/relptbbdown"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_relptbb"+hist_extn+"Down", true);

  TH1F* ttg_relptec1Up = DC.readWriteHisto(fTG, baseDir+"/relptec1up"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_relptec1"+uncorr_extn+"Up", true);
  TH1F* ttg_relptec1Down = DC.readWriteHisto(fTG, baseDir+"/relptec1down"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_relptec1"+uncorr_extn+"Down", true);
  TH1F* ttg_relptec2Up = DC.readWriteHisto(fTG, baseDir+"/relptec2up"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_relptec2"+uncorr_extn+"Up", true);
  TH1F* ttg_relptec2Down = DC.readWriteHisto(fTG, baseDir+"/relptec2down"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_relptec2"+uncorr_extn+"Down", true);

  TH1F* ttg_relpthfUp = DC.readWriteHisto(fTG, baseDir+"/relpthfup"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_relpthf"+hist_extn+"Up", true);
  TH1F* ttg_relpthfDown = DC.readWriteHisto(fTG, baseDir+"/relpthfdown"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_relpthf"+hist_extn+"Down", true);
  TH1F* ttg_relstatecUp = DC.readWriteHisto(fTG, baseDir+"/relstatecup"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_relstatec"+uncorr_extn+"Up", true);
  TH1F* ttg_relstatecDown = DC.readWriteHisto(fTG, baseDir+"/relstatecdown"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_relstatec"+uncorr_extn+"Down", true);

  TH1F* ttg_relstatfsrUp = DC.readWriteHisto(fTG, baseDir+"/relstatfsrup"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_relstatfsr"+uncorr_extn+"Up", true);
  TH1F* ttg_relstatfsrDown = DC.readWriteHisto(fTG, baseDir+"/relstatfsrdown"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_relstatfsr"+uncorr_extn+"Down", true);
  TH1F* ttg_relstathfUp = DC.readWriteHisto(fTG, baseDir+"/relstathfup"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_relstathf"+uncorr_extn+"Up", true);
  TH1F* ttg_relstathfDown = DC.readWriteHisto(fTG, baseDir+"/relstathfdown"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_relstathf"+uncorr_extn+"Down", true);

  TH1F* ttg_singpiecalUp = DC.readWriteHisto(fTG, baseDir+"/singpiecalup"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_singpiecal"+hist_extn+"Up", true);
  TH1F* ttg_singpiecalDown = DC.readWriteHisto(fTG, baseDir+"/singpiecaldown"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_singpiecal"+hist_extn+"Down", true);
  TH1F* ttg_singpihcalUp = DC.readWriteHisto(fTG, baseDir+"/singpihcalup"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_singpihcal"+hist_extn+"Up", true);
  TH1F* ttg_singpihcalDown = DC.readWriteHisto(fTG, baseDir+"/singpihcaldown"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_singpihcal"+hist_extn+"Down", true);

  TH1F* ttg_flavorqcdUp = DC.readWriteHisto(fTG, baseDir+"/flavorqcdup"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_flavorqcd"+hist_extn+"Up", true);
  TH1F* ttg_flavorqcdDown = DC.readWriteHisto(fTG, baseDir+"/flavorqcddown"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_flavorqcd"+hist_extn+"Down", true);
  TH1F* ttg_timeptetaUp = DC.readWriteHisto(fTG, baseDir+"/timeptetaup"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_timepteta"+hist_extn+"Up", true);
  TH1F* ttg_timeptetaDown = DC.readWriteHisto(fTG, baseDir+"/timeptetadown"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_timepteta"+hist_extn+"Down", true);
  TH1F* ttg_PileupUp = DC.readWriteHisto(fTG, baseDir+"/puup"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_Pileup"+hist_extn+"Up", true);
  TH1F* ttg_PileupDown = DC.readWriteHisto(fTG, baseDir+"/pudown"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_Pileup"+hist_extn+"Down", true);
  TH1F* ttg_PrefireUp, *ttg_PrefireDown;
  if(year==2016 or year==2017){
    ttg_PrefireUp = DC.readWriteHisto(fTG, baseDir+"/prefireup"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_Prefire"+hist_extn+"Up", true);
    ttg_PrefireDown = DC.readWriteHisto(fTG, baseDir+"/prefiredown"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_Prefire"+hist_extn+"Down", true);
  }else{
    ttg_PrefireUp = DC.readWriteHisto(fTG, baseDir+"/base"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_Prefire"+hist_extn+"Up", true);
    ttg_PrefireDown = DC.readWriteHisto(fTG, baseDir+"/base"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_Prefire"+hist_extn+"Down", true);
  }
  TH1F* ttg_PUJetIDUp = DC.readWriteHisto(fTG, baseDir+"/pujetidup"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_PUJetID"+hist_extn+"Up", true);
  TH1F* ttg_PUJetIDDown = DC.readWriteHisto(fTG, baseDir+"/pujetiddown"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_PUJetID"+hist_extn+"Down", true);
  TH1F* ttg_JERUp = DC.readWriteHisto(fTG, baseDir+"/jerup"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_JER"+hist_extn+"Up", true);
  TH1F* ttg_JERDown = DC.readWriteHisto(fTG, baseDir+"/jerdown"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_JER"+hist_extn+"Down", true);
  TH1F* ttg_bcstatUp = DC.readWriteHisto(fTG, baseDir+"/bcstatup"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_bcstat"+hist_extn+"Up", true, isNormalized, ttg);
  TH1F* ttg_bcstatDown = DC.readWriteHisto(fTG, baseDir+"/bcstatdown"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_bcstat"+hist_extn+"Down", true, isNormalized, ttg);
  TH1F *ttg_bcintpUp, *ttg_bcintpDown, *ttg_bcextpUp, *ttg_bcextpDown, *ttg_bcxdybUp, *ttg_bcxdybDown, *ttg_bcxdycUp, *ttg_bcxdycDown, *ttg_bcxwjcUp, *ttg_bcxwjcDown;

  ttg_bcintpUp = DC.readWriteHisto(fTG, baseDir+"/bcintpup"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_bcintp"+hist_extn+"Up", true, isNormalized, ttg);
  ttg_bcintpDown = DC.readWriteHisto(fTG, baseDir+"/bcintpdown"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_bcintp"+hist_extn+"Down", true, isNormalized, ttg);
  ttg_bcextpUp = DC.readWriteHisto(fTG, baseDir+"/bcextpup"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_bcextp"+hist_extn+"Up", true, isNormalized, ttg);
  ttg_bcextpDown = DC.readWriteHisto(fTG, baseDir+"/bcextpdown"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_bcextp"+hist_extn+"Down", true, isNormalized, ttg);
  ttg_bcxdybUp = DC.readWriteHisto(fTG, baseDir+"/bcxdybup"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_bcxdyb"+hist_extn+"Up", true, isNormalized, ttg);
  ttg_bcxdybDown = DC.readWriteHisto(fTG, baseDir+"/bcxdybdown"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_bcxdyb"+hist_extn+"Down", true, isNormalized, ttg);
  ttg_bcxdycUp = DC.readWriteHisto(fTG, baseDir+"/bcxdycup"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_bcxdyc"+hist_extn+"Up", true, isNormalized, ttg);
  ttg_bcxdycDown = DC.readWriteHisto(fTG, baseDir+"/bcxdycdown"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_bcxdyc"+hist_extn+"Down", true, isNormalized, ttg);
  ttg_bcxwjcUp = DC.readWriteHisto(fTG, baseDir+"/bcxwjcup"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_bcxwjc"+hist_extn+"Up", true, isNormalized, ttg);
  ttg_bcxwjcDown = DC.readWriteHisto(fTG, baseDir+"/bcxwjcdown"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_bcxwjc"+hist_extn+"Down", true, isNormalized, ttg);

  TH1F* ttg_pdfUp = DC.readWriteHisto(fTG, baseDir+"/pdfup"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_pdf"+hist_extn+"Up", true);
  TH1F* ttg_pdfDown = DC.readWriteHisto(fTG, baseDir+"/pdfdown"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_pdf"+hist_extn+"Down", true);
  // TH1F* ttg_q2Up = DC.readWriteHisto(fTG, baseDir+"/q2up"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_q2"+hist_extn+"Up", true);
  // TH1F* ttg_q2Down = DC.readWriteHisto(fTG, baseDir+"/q2down"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_q2"+hist_extn+"Down", true);
  TH1F* ttg_bclhemufUp = DC.readWriteHisto(fTG, baseDir+"/bclhemufup"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_bclhemuf"+hist_extn+"Up", true, isNormalized, ttg);
  TH1F* ttg_bclhemufDown = DC.readWriteHisto(fTG, baseDir+"/bclhemufdown"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_bclhemuf"+hist_extn+"Down", true, isNormalized, ttg);
  TH1F* ttg_bclhemurUp = DC.readWriteHisto(fTG, baseDir+"/bclhemurup"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_bclhemur"+hist_extn+"Up", true, isNormalized, ttg);
  TH1F* ttg_bclhemurDown = DC.readWriteHisto(fTG, baseDir+"/bclhemurdown"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_bclhemur"+hist_extn+"Down", true, isNormalized, ttg);
  TH1F* ttg_isrUp = DC.readWriteHisto(fTG, baseDir+"/isrup"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_isr"+hist_extn+"Up", true, isNormalized, ttg);
  TH1F* ttg_isrDown = DC.readWriteHisto(fTG, baseDir+"/isrdown"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_isr"+hist_extn+"Down", true, isNormalized, ttg);
  TH1F* ttg_fsrUp = DC.readWriteHisto(fTG, baseDir+"/fsrup"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_fsr"+hist_extn+"Up", true, isNormalized, ttg);
  TH1F* ttg_fsrDown = DC.readWriteHisto(fTG, baseDir+"/fsrdown"+histSubDir, histName, sf_ttg, fout, fTT, "ttg_fsr"+hist_extn+"Down", true, isNormalized, ttg);
  
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // TT+H
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //ttH+jets
  double sf_tth = 1;
  baseDir = "TTH";
  TH1F* tth = DC.readWriteHisto(fTH, baseDir+"/base"+histSubDir, histName, sf_tth, fout, fTT, "tth", true);
  TH1F *tth_LeptonUp,*tth_LeptonDown;
  if(isMuChannel){
    tth_LeptonUp = DC.readWriteHisto(fTH, baseDir+"/mueffup"+histSubDir, histName, sf_tth, fout, fTT, "tth_Lepton"+hist_extn+"Up", true);
    tth_LeptonDown = DC.readWriteHisto(fTH, baseDir+"/mueffdown"+histSubDir, histName, sf_tth, fout, fTT, "tth_Lepton"+hist_extn+"Down", true);
  }else{
    tth_LeptonUp = DC.readWriteHisto(fTH, baseDir+"/eleeffup"+histSubDir, histName, sf_tth, fout, fTT, "tth_Lepton"+hist_extn+"Up", true);
    tth_LeptonDown = DC.readWriteHisto(fTH, baseDir+"/eleeffdown"+histSubDir, histName, sf_tth, fout, fTT, "tth_Lepton"+hist_extn+"Down", true);
  }
  TH1F* tth_absmpfbUp = DC.readWriteHisto(fTH, baseDir+"/absmpfbup"+histSubDir, histName, sf_tth, fout, fTT, "tth_absmpfb"+hist_extn+"Up", true);
  TH1F* tth_absmpfbDown = DC.readWriteHisto(fTH, baseDir+"/absmpfbdown"+histSubDir, histName, sf_tth, fout, fTT, "tth_absmpfb"+hist_extn+"Down", true);
  TH1F* tth_abssclUp = DC.readWriteHisto(fTH, baseDir+"/abssclup"+histSubDir, histName, sf_tth, fout, fTT, "tth_absscl"+hist_extn+"Up", true);
  TH1F* tth_abssclDown = DC.readWriteHisto(fTH, baseDir+"/absscldown"+histSubDir, histName, sf_tth, fout, fTT, "tth_absscl"+hist_extn+"Down", true);
  TH1F* tth_absstatUp = DC.readWriteHisto(fTH, baseDir+"/absstatup"+histSubDir, histName, sf_tth, fout, fTT, "tth_absstat"+uncorr_extn+"Up", true);
  TH1F* tth_absstatDown = DC.readWriteHisto(fTH, baseDir+"/absstatdown"+histSubDir, histName, sf_tth, fout, fTT, "tth_absstat"+uncorr_extn+"Down", true);
  
  TH1F* tth_fragUp = DC.readWriteHisto(fTH, baseDir+"/fragup"+histSubDir, histName, sf_tth, fout, fTT, "tth_frag"+hist_extn+"Up", true);
  TH1F* tth_fragDown = DC.readWriteHisto(fTH, baseDir+"/fragdown"+histSubDir, histName, sf_tth, fout, fTT, "tth_frag"+hist_extn+"Down", true);
  TH1F* tth_pudatamcUp = DC.readWriteHisto(fTH, baseDir+"/pudatamcup"+histSubDir, histName, sf_tth, fout, fTT, "tth_pudatamc"+hist_extn+"Up", true);
  TH1F* tth_pudatamcDown = DC.readWriteHisto(fTH, baseDir+"/pudatamcdown"+histSubDir, histName, sf_tth, fout, fTT, "tth_pudatamc"+hist_extn+"Down", true);

  TH1F* tth_puptbbUp = DC.readWriteHisto(fTH, baseDir+"/puptbbup"+histSubDir, histName, sf_tth, fout, fTT, "tth_puptbb"+hist_extn+"Up", true);
  TH1F* tth_puptbbDown = DC.readWriteHisto(fTH, baseDir+"/puptbbdown"+histSubDir, histName, sf_tth, fout, fTT, "tth_puptbb"+hist_extn+"Down", true);
  TH1F* tth_puptec1Up = DC.readWriteHisto(fTH, baseDir+"/puptec1up"+histSubDir, histName, sf_tth, fout, fTT, "tth_puptec1"+hist_extn+"Up", true);
  TH1F* tth_puptec1Down = DC.readWriteHisto(fTH, baseDir+"/puptec1down"+histSubDir, histName, sf_tth, fout, fTT, "tth_puptec1"+hist_extn+"Down", true);

  TH1F* tth_puptec2Up = DC.readWriteHisto(fTH, baseDir+"/puptec2up"+histSubDir, histName, sf_tth, fout, fTT, "tth_puptec2"+hist_extn+"Up", true);
  TH1F* tth_puptec2Down = DC.readWriteHisto(fTH, baseDir+"/puptec2down"+histSubDir, histName, sf_tth, fout, fTT, "tth_puptec2"+hist_extn+"Down", true);
  TH1F* tth_pupthfUp = DC.readWriteHisto(fTH, baseDir+"/pupthfup"+histSubDir, histName, sf_tth, fout, fTT, "tth_pupthf"+hist_extn+"Up", true);
  TH1F* tth_pupthfDown = DC.readWriteHisto(fTH, baseDir+"/pupthfdown"+histSubDir, histName, sf_tth, fout, fTT, "tth_pupthf"+hist_extn+"Down", true);

  TH1F* tth_puptrefUp = DC.readWriteHisto(fTH, baseDir+"/puptrefup"+histSubDir, histName, sf_tth, fout, fTT, "tth_puptref"+hist_extn+"Up", true);
  TH1F* tth_puptrefDown = DC.readWriteHisto(fTH, baseDir+"/puptrefdown"+histSubDir, histName, sf_tth, fout, fTT, "tth_puptref"+hist_extn+"Down", true);
  TH1F* tth_relfsrUp = DC.readWriteHisto(fTH, baseDir+"/relfsrup"+histSubDir, histName, sf_tth, fout, fTT, "tth_relfsr"+hist_extn+"Up", true);
  TH1F* tth_relfsrDown = DC.readWriteHisto(fTH, baseDir+"/relfsrdown"+histSubDir, histName, sf_tth, fout, fTT, "tth_relfsr"+hist_extn+"Down", true);

  TH1F* tth_relbalUp = DC.readWriteHisto(fTH, baseDir+"/relbalup"+histSubDir, histName, sf_tth, fout, fTT, "tth_relbal"+hist_extn+"Up", true);
  TH1F* tth_relbalDown = DC.readWriteHisto(fTH, baseDir+"/relbaldown"+histSubDir, histName, sf_tth, fout, fTT, "tth_relbal"+hist_extn+"Down", true);
  TH1F* tth_relsampleUp = DC.readWriteHisto(fTH, baseDir+"/relsampleup"+histSubDir, histName, sf_tth, fout, fTT, "tth_relsample"+uncorr_extn+"Up", true);
  TH1F* tth_relsampleDown = DC.readWriteHisto(fTH, baseDir+"/relsampledown"+histSubDir, histName, sf_tth, fout, fTT, "tth_relsample"+uncorr_extn+"Down", true);

  TH1F* tth_reljerec1Up = DC.readWriteHisto(fTH, baseDir+"/reljerec1up"+histSubDir, histName, sf_tth, fout, fTT, "tth_reljerec1"+uncorr_extn+"Up", true);
  TH1F* tth_reljerec1Down = DC.readWriteHisto(fTH, baseDir+"/reljerec1down"+histSubDir, histName, sf_tth, fout, fTT, "tth_reljerec1"+uncorr_extn+"Down", true);
  TH1F* tth_reljerec2Up = DC.readWriteHisto(fTH, baseDir+"/reljerec2up"+histSubDir, histName, sf_tth, fout, fTT, "tth_reljerec2"+uncorr_extn+"Up", true);
  TH1F* tth_reljerec2Down = DC.readWriteHisto(fTH, baseDir+"/reljerec2down"+histSubDir, histName, sf_tth, fout, fTT, "tth_reljerec2"+uncorr_extn+"Down", true);

  TH1F* tth_reljerhfUp = DC.readWriteHisto(fTH, baseDir+"/reljerhfup"+histSubDir, histName, sf_tth, fout, fTT, "tth_reljerhf"+hist_extn+"Up", true);
  TH1F* tth_reljerhfDown = DC.readWriteHisto(fTH, baseDir+"/reljerhfdown"+histSubDir, histName, sf_tth, fout, fTT, "tth_reljerhf"+hist_extn+"Down", true);
  TH1F* tth_relptbbUp = DC.readWriteHisto(fTH, baseDir+"/relptbbup"+histSubDir, histName, sf_tth, fout, fTT, "tth_relptbb"+hist_extn+"Up", true);
  TH1F* tth_relptbbDown = DC.readWriteHisto(fTH, baseDir+"/relptbbdown"+histSubDir, histName, sf_tth, fout, fTT, "tth_relptbb"+hist_extn+"Down", true);

  TH1F* tth_relptec1Up = DC.readWriteHisto(fTH, baseDir+"/relptec1up"+histSubDir, histName, sf_tth, fout, fTT, "tth_relptec1"+uncorr_extn+"Up", true);
  TH1F* tth_relptec1Down = DC.readWriteHisto(fTH, baseDir+"/relptec1down"+histSubDir, histName, sf_tth, fout, fTT, "tth_relptec1"+uncorr_extn+"Down", true);
  TH1F* tth_relptec2Up = DC.readWriteHisto(fTH, baseDir+"/relptec2up"+histSubDir, histName, sf_tth, fout, fTT, "tth_relptec2"+uncorr_extn+"Up", true);
  TH1F* tth_relptec2Down = DC.readWriteHisto(fTH, baseDir+"/relptec2down"+histSubDir, histName, sf_tth, fout, fTT, "tth_relptec2"+uncorr_extn+"Down", true);

  TH1F* tth_relpthfUp = DC.readWriteHisto(fTH, baseDir+"/relpthfup"+histSubDir, histName, sf_tth, fout, fTT, "tth_relpthf"+hist_extn+"Up", true);
  TH1F* tth_relpthfDown = DC.readWriteHisto(fTH, baseDir+"/relpthfdown"+histSubDir, histName, sf_tth, fout, fTT, "tth_relpthf"+hist_extn+"Down", true);
  TH1F* tth_relstatecUp = DC.readWriteHisto(fTH, baseDir+"/relstatecup"+histSubDir, histName, sf_tth, fout, fTT, "tth_relstatec"+uncorr_extn+"Up", true);
  TH1F* tth_relstatecDown = DC.readWriteHisto(fTH, baseDir+"/relstatecdown"+histSubDir, histName, sf_tth, fout, fTT, "tth_relstatec"+uncorr_extn+"Down", true);

  TH1F* tth_relstatfsrUp = DC.readWriteHisto(fTH, baseDir+"/relstatfsrup"+histSubDir, histName, sf_tth, fout, fTT, "tth_relstatfsr"+uncorr_extn+"Up", true);
  TH1F* tth_relstatfsrDown = DC.readWriteHisto(fTH, baseDir+"/relstatfsrdown"+histSubDir, histName, sf_tth, fout, fTT, "tth_relstatfsr"+uncorr_extn+"Down", true);
  TH1F* tth_relstathfUp = DC.readWriteHisto(fTH, baseDir+"/relstathfup"+histSubDir, histName, sf_tth, fout, fTT, "tth_relstathf"+uncorr_extn+"Up", true);
  TH1F* tth_relstathfDown = DC.readWriteHisto(fTH, baseDir+"/relstathfdown"+histSubDir, histName, sf_tth, fout, fTT, "tth_relstathf"+uncorr_extn+"Down", true);

  TH1F* tth_singpiecalUp = DC.readWriteHisto(fTH, baseDir+"/singpiecalup"+histSubDir, histName, sf_tth, fout, fTT, "tth_singpiecal"+hist_extn+"Up", true);
  TH1F* tth_singpiecalDown = DC.readWriteHisto(fTH, baseDir+"/singpiecaldown"+histSubDir, histName, sf_tth, fout, fTT, "tth_singpiecal"+hist_extn+"Down", true);
  TH1F* tth_singpihcalUp = DC.readWriteHisto(fTH, baseDir+"/singpihcalup"+histSubDir, histName, sf_tth, fout, fTT, "tth_singpihcal"+hist_extn+"Up", true);
  TH1F* tth_singpihcalDown = DC.readWriteHisto(fTH, baseDir+"/singpihcaldown"+histSubDir, histName, sf_tth, fout, fTT, "tth_singpihcal"+hist_extn+"Down", true);

  TH1F* tth_flavorqcdUp = DC.readWriteHisto(fTH, baseDir+"/flavorqcdup"+histSubDir, histName, sf_tth, fout, fTT, "tth_flavorqcd"+hist_extn+"Up", true);
  TH1F* tth_flavorqcdDown = DC.readWriteHisto(fTH, baseDir+"/flavorqcddown"+histSubDir, histName, sf_tth, fout, fTT, "tth_flavorqcd"+hist_extn+"Down", true);
  TH1F* tth_timeptetaUp = DC.readWriteHisto(fTH, baseDir+"/timeptetaup"+histSubDir, histName, sf_tth, fout, fTT, "tth_timepteta"+hist_extn+"Up", true);
  TH1F* tth_timeptetaDown = DC.readWriteHisto(fTH, baseDir+"/timeptetadown"+histSubDir, histName, sf_tth, fout, fTT, "tth_timepteta"+hist_extn+"Down", true);
  TH1F* tth_PileupUp = DC.readWriteHisto(fTH, baseDir+"/puup"+histSubDir, histName, sf_tth, fout, fTT, "tth_Pileup"+hist_extn+"Up", true);
  TH1F* tth_PileupDown = DC.readWriteHisto(fTH, baseDir+"/pudown"+histSubDir, histName, sf_tth, fout, fTT, "tth_Pileup"+hist_extn+"Down", true);
  TH1F* tth_PrefireUp, *tth_PrefireDown;
  if(year==2016 or year==2017){
    tth_PrefireUp = DC.readWriteHisto(fTH, baseDir+"/prefireup"+histSubDir, histName, sf_tth, fout, fTT, "tth_Prefire"+hist_extn+"Up", true);
    tth_PrefireDown = DC.readWriteHisto(fTH, baseDir+"/prefiredown"+histSubDir, histName, sf_tth, fout, fTT, "tth_Prefire"+hist_extn+"Down", true);
  }else{
    tth_PrefireUp = DC.readWriteHisto(fTH, baseDir+"/base"+histSubDir, histName, sf_tth, fout, fTT, "tth_Prefire"+hist_extn+"Up", true);
    tth_PrefireDown = DC.readWriteHisto(fTH, baseDir+"/base"+histSubDir, histName, sf_tth, fout, fTT, "tth_Prefire"+hist_extn+"Down", true);
  }
  TH1F* tth_PUJetIDUp = DC.readWriteHisto(fTH, baseDir+"/pujetidup"+histSubDir, histName, sf_tth, fout, fTT, "tth_PUJetID"+hist_extn+"Up", true);
  TH1F* tth_PUJetIDDown = DC.readWriteHisto(fTH, baseDir+"/pujetiddown"+histSubDir, histName, sf_tth, fout, fTT, "tth_PUJetID"+hist_extn+"Down", true);
  TH1F* tth_JERUp = DC.readWriteHisto(fTH, baseDir+"/jerup"+histSubDir, histName, sf_tth, fout, fTT, "tth_JER"+hist_extn+"Up", true);
  TH1F* tth_JERDown = DC.readWriteHisto(fTH, baseDir+"/jerdown"+histSubDir, histName, sf_tth, fout, fTT, "tth_JER"+hist_extn+"Down", true);
  TH1F* tth_bcstatUp = DC.readWriteHisto(fTH, baseDir+"/bcstatup"+histSubDir, histName, sf_tth, fout, fTT, "tth_bcstat"+hist_extn+"Up", true, isNormalized, tth);
  TH1F* tth_bcstatDown = DC.readWriteHisto(fTH, baseDir+"/bcstatdown"+histSubDir, histName, sf_tth, fout, fTT, "tth_bcstat"+hist_extn+"Down", true, isNormalized, tth);
  TH1F *tth_bcintpUp, *tth_bcintpDown, *tth_bcextpUp, *tth_bcextpDown, *tth_bcxdybUp, *tth_bcxdybDown, *tth_bcxdycUp, *tth_bcxdycDown, *tth_bcxwjcUp, *tth_bcxwjcDown;

  tth_bcintpUp = DC.readWriteHisto(fTH, baseDir+"/bcintpup"+histSubDir, histName, sf_tth, fout, fTT, "tth_bcintp"+hist_extn+"Up", true, isNormalized, tth);
  tth_bcintpDown = DC.readWriteHisto(fTH, baseDir+"/bcintpdown"+histSubDir, histName, sf_tth, fout, fTT, "tth_bcintp"+hist_extn+"Down", true, isNormalized, tth);
  tth_bcextpUp = DC.readWriteHisto(fTH, baseDir+"/bcextpup"+histSubDir, histName, sf_tth, fout, fTT, "tth_bcextp"+hist_extn+"Up", true, isNormalized, tth);
  tth_bcextpDown = DC.readWriteHisto(fTH, baseDir+"/bcextpdown"+histSubDir, histName, sf_tth, fout, fTT, "tth_bcextp"+hist_extn+"Down", true, isNormalized, tth);
  tth_bcxdybUp = DC.readWriteHisto(fTH, baseDir+"/bcxdybup"+histSubDir, histName, sf_tth, fout, fTT, "tth_bcxdyb"+hist_extn+"Up", true, isNormalized, tth);
  tth_bcxdybDown = DC.readWriteHisto(fTH, baseDir+"/bcxdybdown"+histSubDir, histName, sf_tth, fout, fTT, "tth_bcxdyb"+hist_extn+"Down", true, isNormalized, tth);
  tth_bcxdycUp = DC.readWriteHisto(fTH, baseDir+"/bcxdycup"+histSubDir, histName, sf_tth, fout, fTT, "tth_bcxdyc"+hist_extn+"Up", true, isNormalized, tth);
  tth_bcxdycDown = DC.readWriteHisto(fTH, baseDir+"/bcxdycdown"+histSubDir, histName, sf_tth, fout, fTT, "tth_bcxdyc"+hist_extn+"Down", true, isNormalized, tth);
  tth_bcxwjcUp = DC.readWriteHisto(fTH, baseDir+"/bcxwjcup"+histSubDir, histName, sf_tth, fout, fTT, "tth_bcxwjc"+hist_extn+"Up", true, isNormalized, tth);
  tth_bcxwjcDown = DC.readWriteHisto(fTH, baseDir+"/bcxwjcdown"+histSubDir, histName, sf_tth, fout, fTT, "tth_bcxwjc"+hist_extn+"Down", true, isNormalized, tth);

  TH1F* tth_pdfUp = DC.readWriteHisto(fTH, baseDir+"/pdfup"+histSubDir, histName, sf_tth, fout, fTT, "tth_pdf"+hist_extn+"Up", true);
  TH1F* tth_pdfDown = DC.readWriteHisto(fTH, baseDir+"/pdfdown"+histSubDir, histName, sf_tth, fout, fTT, "tth_pdf"+hist_extn+"Down", true);
  // TH1F* tth_q2Up = DC.readWriteHisto(fTH, baseDir+"/q2up"+histSubDir, histName, sf_tth, fout, fTT, "tth_q2"+hist_extn+"Up", true);
  // TH1F* tth_q2Down = DC.readWriteHisto(fTH, baseDir+"/q2down"+histSubDir, histName, sf_tth, fout, fTT, "tth_q2"+hist_extn+"Down", true);
  TH1F* tth_bclhemufUp = DC.readWriteHisto(fTH, baseDir+"/bclhemufup"+histSubDir, histName, sf_tth, fout, fTT, "tth_bclhemuf"+hist_extn+"Up", true, isNormalized, tth);
  TH1F* tth_bclhemufDown = DC.readWriteHisto(fTH, baseDir+"/bclhemufdown"+histSubDir, histName, sf_tth, fout, fTT, "tth_bclhemuf"+hist_extn+"Down", true, isNormalized, tth);
  TH1F* tth_bclhemurUp = DC.readWriteHisto(fTH, baseDir+"/bclhemurup"+histSubDir, histName, sf_tth, fout, fTT, "tth_bclhemur"+hist_extn+"Up", true, isNormalized, tth);
  TH1F* tth_bclhemurDown = DC.readWriteHisto(fTH, baseDir+"/bclhemurdown"+histSubDir, histName, sf_tth, fout, fTT, "tth_bclhemur"+hist_extn+"Down", true, isNormalized, tth);
  TH1F* tth_isrUp = DC.readWriteHisto(fTH, baseDir+"/isrup"+histSubDir, histName, sf_tth, fout, fTT, "tth_isr"+hist_extn+"Up", true, isNormalized, tth);
  TH1F* tth_isrDown = DC.readWriteHisto(fTH, baseDir+"/isrdown"+histSubDir, histName, sf_tth, fout, fTT, "tth_isr"+hist_extn+"Down", true, isNormalized, tth);
  TH1F* tth_fsrUp = DC.readWriteHisto(fTH, baseDir+"/fsrup"+histSubDir, histName, sf_tth, fout, fTT, "tth_fsr"+hist_extn+"Up", true, isNormalized, tth);
  TH1F* tth_fsrDown = DC.readWriteHisto(fTH, baseDir+"/fsrdown"+histSubDir, histName, sf_tth, fout, fTT, "tth_fsr"+hist_extn+"Down", true, isNormalized, tth);  
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // TT+Z
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //ttHb+jets
  double sf_ttz = 1;
  baseDir = "TTZ";
  TH1F* ttz = DC.readWriteHisto(fTZ, baseDir+"/base"+histSubDir, histName, sf_ttz, fout, fTT, "ttz", true);
  TH1F *ttz_LeptonUp,*ttz_LeptonDown;
  if(isMuChannel){
    ttz_LeptonUp = DC.readWriteHisto(fTZ, baseDir+"/mueffup"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_Lepton"+hist_extn+"Up", true);
    ttz_LeptonDown = DC.readWriteHisto(fTZ, baseDir+"/mueffdown"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_Lepton"+hist_extn+"Down", true);
  }else{
    ttz_LeptonUp = DC.readWriteHisto(fTZ, baseDir+"/eleeffup"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_Lepton"+hist_extn+"Up", true);
    ttz_LeptonDown = DC.readWriteHisto(fTZ, baseDir+"/eleeffdown"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_Lepton"+hist_extn+"Down", true);
  }
  TH1F* ttz_absmpfbUp = DC.readWriteHisto(fTZ, baseDir+"/absmpfbup"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_absmpfb"+hist_extn+"Up", true);
  TH1F* ttz_absmpfbDown = DC.readWriteHisto(fTZ, baseDir+"/absmpfbdown"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_absmpfb"+hist_extn+"Down", true);
  TH1F* ttz_abssclUp = DC.readWriteHisto(fTZ, baseDir+"/abssclup"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_absscl"+hist_extn+"Up", true);
  TH1F* ttz_abssclDown = DC.readWriteHisto(fTZ, baseDir+"/absscldown"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_absscl"+hist_extn+"Down", true);
  TH1F* ttz_absstatUp = DC.readWriteHisto(fTZ, baseDir+"/absstatup"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_absstat"+uncorr_extn+"Up", true);
  TH1F* ttz_absstatDown = DC.readWriteHisto(fTZ, baseDir+"/absstatdown"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_absstat"+uncorr_extn+"Down", true);
  
  TH1F* ttz_fragUp = DC.readWriteHisto(fTZ, baseDir+"/fragup"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_frag"+hist_extn+"Up", true);
  TH1F* ttz_fragDown = DC.readWriteHisto(fTZ, baseDir+"/fragdown"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_frag"+hist_extn+"Down", true);
  TH1F* ttz_pudatamcUp = DC.readWriteHisto(fTZ, baseDir+"/pudatamcup"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_pudatamc"+hist_extn+"Up", true);
  TH1F* ttz_pudatamcDown = DC.readWriteHisto(fTZ, baseDir+"/pudatamcdown"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_pudatamc"+hist_extn+"Down", true);

  TH1F* ttz_puptbbUp = DC.readWriteHisto(fTZ, baseDir+"/puptbbup"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_puptbb"+hist_extn+"Up", true);
  TH1F* ttz_puptbbDown = DC.readWriteHisto(fTZ, baseDir+"/puptbbdown"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_puptbb"+hist_extn+"Down", true);
  TH1F* ttz_puptec1Up = DC.readWriteHisto(fTZ, baseDir+"/puptec1up"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_puptec1"+hist_extn+"Up", true);
  TH1F* ttz_puptec1Down = DC.readWriteHisto(fTZ, baseDir+"/puptec1down"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_puptec1"+hist_extn+"Down", true);

  TH1F* ttz_puptec2Up = DC.readWriteHisto(fTZ, baseDir+"/puptec2up"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_puptec2"+hist_extn+"Up", true);
  TH1F* ttz_puptec2Down = DC.readWriteHisto(fTZ, baseDir+"/puptec2down"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_puptec2"+hist_extn+"Down", true);
  TH1F* ttz_pupthfUp = DC.readWriteHisto(fTZ, baseDir+"/pupthfup"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_pupthf"+hist_extn+"Up", true);
  TH1F* ttz_pupthfDown = DC.readWriteHisto(fTZ, baseDir+"/pupthfdown"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_pupthf"+hist_extn+"Down", true);

  TH1F* ttz_puptrefUp = DC.readWriteHisto(fTZ, baseDir+"/puptrefup"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_puptref"+hist_extn+"Up", true);
  TH1F* ttz_puptrefDown = DC.readWriteHisto(fTZ, baseDir+"/puptrefdown"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_puptref"+hist_extn+"Down", true);
  TH1F* ttz_relfsrUp = DC.readWriteHisto(fTZ, baseDir+"/relfsrup"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_relfsr"+hist_extn+"Up", true);
  TH1F* ttz_relfsrDown = DC.readWriteHisto(fTZ, baseDir+"/relfsrdown"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_relfsr"+hist_extn+"Down", true);

  TH1F* ttz_relbalUp = DC.readWriteHisto(fTZ, baseDir+"/relbalup"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_relbal"+hist_extn+"Up", true);
  TH1F* ttz_relbalDown = DC.readWriteHisto(fTZ, baseDir+"/relbaldown"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_relbal"+hist_extn+"Down", true);
  TH1F* ttz_relsampleUp = DC.readWriteHisto(fTZ, baseDir+"/relsampleup"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_relsample"+uncorr_extn+"Up", true);
  TH1F* ttz_relsampleDown = DC.readWriteHisto(fTZ, baseDir+"/relsampledown"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_relsample"+uncorr_extn+"Down", true);

  TH1F* ttz_reljerec1Up = DC.readWriteHisto(fTZ, baseDir+"/reljerec1up"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_reljerec1"+uncorr_extn+"Up", true);
  TH1F* ttz_reljerec1Down = DC.readWriteHisto(fTZ, baseDir+"/reljerec1down"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_reljerec1"+uncorr_extn+"Down", true);
  TH1F* ttz_reljerec2Up = DC.readWriteHisto(fTZ, baseDir+"/reljerec2up"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_reljerec2"+uncorr_extn+"Up", true);
  TH1F* ttz_reljerec2Down = DC.readWriteHisto(fTZ, baseDir+"/reljerec2down"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_reljerec2"+uncorr_extn+"Down", true);

  TH1F* ttz_reljerhfUp = DC.readWriteHisto(fTZ, baseDir+"/reljerhfup"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_reljerhf"+hist_extn+"Up", true);
  TH1F* ttz_reljerhfDown = DC.readWriteHisto(fTZ, baseDir+"/reljerhfdown"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_reljerhf"+hist_extn+"Down", true);
  TH1F* ttz_relptbbUp = DC.readWriteHisto(fTZ, baseDir+"/relptbbup"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_relptbb"+hist_extn+"Up", true);
  TH1F* ttz_relptbbDown = DC.readWriteHisto(fTZ, baseDir+"/relptbbdown"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_relptbb"+hist_extn+"Down", true);

  TH1F* ttz_relptec1Up = DC.readWriteHisto(fTZ, baseDir+"/relptec1up"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_relptec1"+uncorr_extn+"Up", true);
  TH1F* ttz_relptec1Down = DC.readWriteHisto(fTZ, baseDir+"/relptec1down"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_relptec1"+uncorr_extn+"Down", true);
  TH1F* ttz_relptec2Up = DC.readWriteHisto(fTZ, baseDir+"/relptec2up"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_relptec2"+uncorr_extn+"Up", true);
  TH1F* ttz_relptec2Down = DC.readWriteHisto(fTZ, baseDir+"/relptec2down"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_relptec2"+uncorr_extn+"Down", true);

  TH1F* ttz_relpthfUp = DC.readWriteHisto(fTZ, baseDir+"/relpthfup"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_relpthf"+hist_extn+"Up", true);
  TH1F* ttz_relpthfDown = DC.readWriteHisto(fTZ, baseDir+"/relpthfdown"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_relpthf"+hist_extn+"Down", true);
  TH1F* ttz_relstatecUp = DC.readWriteHisto(fTZ, baseDir+"/relstatecup"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_relstatec"+uncorr_extn+"Up", true);
  TH1F* ttz_relstatecDown = DC.readWriteHisto(fTZ, baseDir+"/relstatecdown"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_relstatec"+uncorr_extn+"Down", true);

  TH1F* ttz_relstatfsrUp = DC.readWriteHisto(fTZ, baseDir+"/relstatfsrup"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_relstatfsr"+uncorr_extn+"Up", true);
  TH1F* ttz_relstatfsrDown = DC.readWriteHisto(fTZ, baseDir+"/relstatfsrdown"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_relstatfsr"+uncorr_extn+"Down", true);
  TH1F* ttz_relstathfUp = DC.readWriteHisto(fTZ, baseDir+"/relstathfup"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_relstathf"+uncorr_extn+"Up", true);
  TH1F* ttz_relstathfDown = DC.readWriteHisto(fTZ, baseDir+"/relstathfdown"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_relstathf"+uncorr_extn+"Down", true);

  TH1F* ttz_singpiecalUp = DC.readWriteHisto(fTZ, baseDir+"/singpiecalup"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_singpiecal"+hist_extn+"Up", true);
  TH1F* ttz_singpiecalDown = DC.readWriteHisto(fTZ, baseDir+"/singpiecaldown"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_singpiecal"+hist_extn+"Down", true);
  TH1F* ttz_singpihcalUp = DC.readWriteHisto(fTZ, baseDir+"/singpihcalup"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_singpihcal"+hist_extn+"Up", true);
  TH1F* ttz_singpihcalDown = DC.readWriteHisto(fTZ, baseDir+"/singpihcaldown"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_singpihcal"+hist_extn+"Down", true);

  TH1F* ttz_flavorqcdUp = DC.readWriteHisto(fTZ, baseDir+"/flavorqcdup"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_flavorqcd"+hist_extn+"Up", true);
  TH1F* ttz_flavorqcdDown = DC.readWriteHisto(fTZ, baseDir+"/flavorqcddown"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_flavorqcd"+hist_extn+"Down", true);
  TH1F* ttz_timeptetaUp = DC.readWriteHisto(fTZ, baseDir+"/timeptetaup"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_timepteta"+hist_extn+"Up", true);
  TH1F* ttz_timeptetaDown = DC.readWriteHisto(fTZ, baseDir+"/timeptetadown"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_timepteta"+hist_extn+"Down", true);
  TH1F* ttz_PileupUp = DC.readWriteHisto(fTZ, baseDir+"/puup"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_Pileup"+hist_extn+"Up", true);
  TH1F* ttz_PileupDown = DC.readWriteHisto(fTZ, baseDir+"/pudown"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_Pileup"+hist_extn+"Down", true);
  TH1F* ttz_PrefireUp, *ttz_PrefireDown;
  if(year==2016 or year==2017){
    ttz_PrefireUp = DC.readWriteHisto(fTZ, baseDir+"/prefireup"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_Prefire"+hist_extn+"Up", true);
    ttz_PrefireDown = DC.readWriteHisto(fTZ, baseDir+"/prefiredown"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_Prefire"+hist_extn+"Down", true);
  }else{
    ttz_PrefireUp = DC.readWriteHisto(fTZ, baseDir+"/base"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_Prefire"+hist_extn+"Up", true);
    ttz_PrefireDown = DC.readWriteHisto(fTZ, baseDir+"/base"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_Prefire"+hist_extn+"Down", true);
  }
  TH1F* ttz_PUJetIDUp = DC.readWriteHisto(fTZ, baseDir+"/pujetidup"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_PUJetID"+hist_extn+"Up", true);
  TH1F* ttz_PUJetIDDown = DC.readWriteHisto(fTZ, baseDir+"/pujetiddown"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_PUJetID"+hist_extn+"Down", true);
  TH1F* ttz_JERUp = DC.readWriteHisto(fTZ, baseDir+"/jerup"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_JER"+hist_extn+"Up", true);
  TH1F* ttz_JERDown = DC.readWriteHisto(fTZ, baseDir+"/jerdown"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_JER"+hist_extn+"Down", true);
  TH1F* ttz_bcstatUp = DC.readWriteHisto(fTZ, baseDir+"/bcstatup"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_bcstat"+hist_extn+"Up", true, isNormalized, ttz);
  TH1F* ttz_bcstatDown = DC.readWriteHisto(fTZ, baseDir+"/bcstatdown"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_bcstat"+hist_extn+"Down", true, isNormalized, ttz);
  TH1F *ttz_bcintpUp, *ttz_bcintpDown, *ttz_bcextpUp, *ttz_bcextpDown, *ttz_bcxdybUp, *ttz_bcxdybDown, *ttz_bcxdycUp, *ttz_bcxdycDown, *ttz_bcxwjcUp, *ttz_bcxwjcDown;

  ttz_bcintpUp = DC.readWriteHisto(fTZ, baseDir+"/bcintpup"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_bcintp"+hist_extn+"Up", true, isNormalized, ttz);
  ttz_bcintpDown = DC.readWriteHisto(fTZ, baseDir+"/bcintpdown"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_bcintp"+hist_extn+"Down", true, isNormalized, ttz);
  ttz_bcextpUp = DC.readWriteHisto(fTZ, baseDir+"/bcextpup"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_bcextp"+hist_extn+"Up", true, isNormalized, ttz);
  ttz_bcextpDown = DC.readWriteHisto(fTZ, baseDir+"/bcextpdown"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_bcextp"+hist_extn+"Down", true, isNormalized, ttz);
  ttz_bcxdybUp = DC.readWriteHisto(fTZ, baseDir+"/bcxdybup"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_bcxdyb"+hist_extn+"Up", true, isNormalized, ttz);
  ttz_bcxdybDown = DC.readWriteHisto(fTZ, baseDir+"/bcxdybdown"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_bcxdyb"+hist_extn+"Down", true, isNormalized, ttz);
  ttz_bcxdycUp = DC.readWriteHisto(fTZ, baseDir+"/bcxdycup"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_bcxdyc"+hist_extn+"Up", true, isNormalized, ttz);
  ttz_bcxdycDown = DC.readWriteHisto(fTZ, baseDir+"/bcxdycdown"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_bcxdyc"+hist_extn+"Down", true, isNormalized, ttz);
  ttz_bcxwjcUp = DC.readWriteHisto(fTZ, baseDir+"/bcxwjcup"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_bcxwjc"+hist_extn+"Up", true, isNormalized, ttz);
  ttz_bcxwjcDown = DC.readWriteHisto(fTZ, baseDir+"/bcxwjcdown"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_bcxwjc"+hist_extn+"Down", true, isNormalized, ttz);

  TH1F* ttz_pdfUp = DC.readWriteHisto(fTZ, baseDir+"/pdfup"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_pdf"+hist_extn+"Up", true);
  TH1F* ttz_pdfDown = DC.readWriteHisto(fTZ, baseDir+"/pdfdown"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_pdf"+hist_extn+"Down", true);
  // TH1F* ttz_q2Up = DC.readWriteHisto(fTZ, baseDir+"/q2up"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_q2"+hist_extn+"Up", true);
  // TH1F* ttz_q2Down = DC.readWriteHisto(fTZ, baseDir+"/q2down"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_q2"+hist_extn+"Down", true);
  TH1F* ttz_bclhemufUp = DC.readWriteHisto(fTZ, baseDir+"/bclhemufup"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_bclhemuf"+hist_extn+"Up", true, isNormalized, ttz);
  TH1F* ttz_bclhemufDown = DC.readWriteHisto(fTZ, baseDir+"/bclhemufdown"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_bclhemuf"+hist_extn+"Down", true, isNormalized, ttz);
  TH1F* ttz_bclhemurUp = DC.readWriteHisto(fTZ, baseDir+"/bclhemurup"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_bclhemur"+hist_extn+"Up", true, isNormalized, ttz);
  TH1F* ttz_bclhemurDown = DC.readWriteHisto(fTZ, baseDir+"/bclhemurdown"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_bclhemur"+hist_extn+"Down", true, isNormalized, ttz);
  TH1F* ttz_isrUp = DC.readWriteHisto(fTZ, baseDir+"/isrup"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_isr"+hist_extn+"Up", true, isNormalized, ttz);
  TH1F* ttz_isrDown = DC.readWriteHisto(fTZ, baseDir+"/isrdown"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_isr"+hist_extn+"Down", true, isNormalized, ttz);
  TH1F* ttz_fsrUp = DC.readWriteHisto(fTZ, baseDir+"/fsrup"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_fsr"+hist_extn+"Up", true, isNormalized, ttz);
  TH1F* ttz_fsrDown = DC.readWriteHisto(fTZ, baseDir+"/fsrdown"+histSubDir, histName, sf_ttz, fout, fTT, "ttz_fsr"+hist_extn+"Down", true, isNormalized, ttz);  
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // TT+W
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //ttw+jets
  double sf_ttw = 1;
  baseDir = "TTW";
  TH1F* ttw = DC.readWriteHisto(fTW, baseDir+"/base"+histSubDir, histName, sf_ttw, fout, fTT, "ttw", true);
  TH1F *ttw_LeptonUp,*ttw_LeptonDown;
  if(isMuChannel){
    ttw_LeptonUp = DC.readWriteHisto(fTW, baseDir+"/mueffup"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_Lepton"+hist_extn+"Up", true);
    ttw_LeptonDown = DC.readWriteHisto(fTW, baseDir+"/mueffdown"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_Lepton"+hist_extn+"Down", true);
  }else{
    ttw_LeptonUp = DC.readWriteHisto(fTW, baseDir+"/eleeffup"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_Lepton"+hist_extn+"Up", true);
    ttw_LeptonDown = DC.readWriteHisto(fTW, baseDir+"/eleeffdown"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_Lepton"+hist_extn+"Down", true);
  }
  TH1F* ttw_absmpfbUp = DC.readWriteHisto(fTW, baseDir+"/absmpfbup"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_absmpfb"+hist_extn+"Up", true);
  TH1F* ttw_absmpfbDown = DC.readWriteHisto(fTW, baseDir+"/absmpfbdown"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_absmpfb"+hist_extn+"Down", true);
  TH1F* ttw_abssclUp = DC.readWriteHisto(fTW, baseDir+"/abssclup"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_absscl"+hist_extn+"Up", true);
  TH1F* ttw_abssclDown = DC.readWriteHisto(fTW, baseDir+"/absscldown"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_absscl"+hist_extn+"Down", true);
  TH1F* ttw_absstatUp = DC.readWriteHisto(fTW, baseDir+"/absstatup"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_absstat"+uncorr_extn+"Up", true);
  TH1F* ttw_absstatDown = DC.readWriteHisto(fTW, baseDir+"/absstatdown"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_absstat"+uncorr_extn+"Down", true);
  
  TH1F* ttw_fragUp = DC.readWriteHisto(fTW, baseDir+"/fragup"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_frag"+hist_extn+"Up", true);
  TH1F* ttw_fragDown = DC.readWriteHisto(fTW, baseDir+"/fragdown"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_frag"+hist_extn+"Down", true);
  TH1F* ttw_pudatamcUp = DC.readWriteHisto(fTW, baseDir+"/pudatamcup"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_pudatamc"+hist_extn+"Up", true);
  TH1F* ttw_pudatamcDown = DC.readWriteHisto(fTW, baseDir+"/pudatamcdown"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_pudatamc"+hist_extn+"Down", true);

  TH1F* ttw_puptbbUp = DC.readWriteHisto(fTW, baseDir+"/puptbbup"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_puptbb"+hist_extn+"Up", true);
  TH1F* ttw_puptbbDown = DC.readWriteHisto(fTW, baseDir+"/puptbbdown"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_puptbb"+hist_extn+"Down", true);
  TH1F* ttw_puptec1Up = DC.readWriteHisto(fTW, baseDir+"/puptec1up"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_puptec1"+hist_extn+"Up", true);
  TH1F* ttw_puptec1Down = DC.readWriteHisto(fTW, baseDir+"/puptec1down"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_puptec1"+hist_extn+"Down", true);

  TH1F* ttw_puptec2Up = DC.readWriteHisto(fTW, baseDir+"/puptec2up"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_puptec2"+hist_extn+"Up", true);
  TH1F* ttw_puptec2Down = DC.readWriteHisto(fTW, baseDir+"/puptec2down"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_puptec2"+hist_extn+"Down", true);
  TH1F* ttw_pupthfUp = DC.readWriteHisto(fTW, baseDir+"/pupthfup"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_pupthf"+hist_extn+"Up", true);
  TH1F* ttw_pupthfDown = DC.readWriteHisto(fTW, baseDir+"/pupthfdown"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_pupthf"+hist_extn+"Down", true);

  TH1F* ttw_puptrefUp = DC.readWriteHisto(fTW, baseDir+"/puptrefup"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_puptref"+hist_extn+"Up", true);
  TH1F* ttw_puptrefDown = DC.readWriteHisto(fTW, baseDir+"/puptrefdown"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_puptref"+hist_extn+"Down", true);
  TH1F* ttw_relfsrUp = DC.readWriteHisto(fTW, baseDir+"/relfsrup"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_relfsr"+hist_extn+"Up", true);
  TH1F* ttw_relfsrDown = DC.readWriteHisto(fTW, baseDir+"/relfsrdown"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_relfsr"+hist_extn+"Down", true);

  TH1F* ttw_relbalUp = DC.readWriteHisto(fTW, baseDir+"/relbalup"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_relbal"+hist_extn+"Up", true);
  TH1F* ttw_relbalDown = DC.readWriteHisto(fTW, baseDir+"/relbaldown"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_relbal"+hist_extn+"Down", true);
  TH1F* ttw_relsampleUp = DC.readWriteHisto(fTW, baseDir+"/relsampleup"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_relsample"+uncorr_extn+"Up", true);
  TH1F* ttw_relsampleDown = DC.readWriteHisto(fTW, baseDir+"/relsampledown"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_relsample"+uncorr_extn+"Down", true);

  TH1F* ttw_reljerec1Up = DC.readWriteHisto(fTW, baseDir+"/reljerec1up"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_reljerec1"+uncorr_extn+"Up", true);
  TH1F* ttw_reljerec1Down = DC.readWriteHisto(fTW, baseDir+"/reljerec1down"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_reljerec1"+uncorr_extn+"Down", true);
  TH1F* ttw_reljerec2Up = DC.readWriteHisto(fTW, baseDir+"/reljerec2up"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_reljerec2"+uncorr_extn+"Up", true);
  TH1F* ttw_reljerec2Down = DC.readWriteHisto(fTW, baseDir+"/reljerec2down"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_reljerec2"+uncorr_extn+"Down", true);

  TH1F* ttw_reljerhfUp = DC.readWriteHisto(fTW, baseDir+"/reljerhfup"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_reljerhf"+hist_extn+"Up", true);
  TH1F* ttw_reljerhfDown = DC.readWriteHisto(fTW, baseDir+"/reljerhfdown"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_reljerhf"+hist_extn+"Down", true);
  TH1F* ttw_relptbbUp = DC.readWriteHisto(fTW, baseDir+"/relptbbup"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_relptbb"+hist_extn+"Up", true);
  TH1F* ttw_relptbbDown = DC.readWriteHisto(fTW, baseDir+"/relptbbdown"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_relptbb"+hist_extn+"Down", true);

  TH1F* ttw_relptec1Up = DC.readWriteHisto(fTW, baseDir+"/relptec1up"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_relptec1"+uncorr_extn+"Up", true);
  TH1F* ttw_relptec1Down = DC.readWriteHisto(fTW, baseDir+"/relptec1down"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_relptec1"+uncorr_extn+"Down", true);
  TH1F* ttw_relptec2Up = DC.readWriteHisto(fTW, baseDir+"/relptec2up"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_relptec2"+uncorr_extn+"Up", true);
  TH1F* ttw_relptec2Down = DC.readWriteHisto(fTW, baseDir+"/relptec2down"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_relptec2"+uncorr_extn+"Down", true);

  TH1F* ttw_relpthfUp = DC.readWriteHisto(fTW, baseDir+"/relpthfup"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_relpthf"+hist_extn+"Up", true);
  TH1F* ttw_relpthfDown = DC.readWriteHisto(fTW, baseDir+"/relpthfdown"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_relpthf"+hist_extn+"Down", true);
  TH1F* ttw_relstatecUp = DC.readWriteHisto(fTW, baseDir+"/relstatecup"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_relstatec"+uncorr_extn+"Up", true);
  TH1F* ttw_relstatecDown = DC.readWriteHisto(fTW, baseDir+"/relstatecdown"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_relstatec"+uncorr_extn+"Down", true);

  TH1F* ttw_relstatfsrUp = DC.readWriteHisto(fTW, baseDir+"/relstatfsrup"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_relstatfsr"+uncorr_extn+"Up", true);
  TH1F* ttw_relstatfsrDown = DC.readWriteHisto(fTW, baseDir+"/relstatfsrdown"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_relstatfsr"+uncorr_extn+"Down", true);
  TH1F* ttw_relstathfUp = DC.readWriteHisto(fTW, baseDir+"/relstathfup"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_relstathf"+uncorr_extn+"Up", true);
  TH1F* ttw_relstathfDown = DC.readWriteHisto(fTW, baseDir+"/relstathfdown"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_relstathf"+uncorr_extn+"Down", true);

  TH1F* ttw_singpiecalUp = DC.readWriteHisto(fTW, baseDir+"/singpiecalup"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_singpiecal"+hist_extn+"Up", true);
  TH1F* ttw_singpiecalDown = DC.readWriteHisto(fTW, baseDir+"/singpiecaldown"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_singpiecal"+hist_extn+"Down", true);
  TH1F* ttw_singpihcalUp = DC.readWriteHisto(fTW, baseDir+"/singpihcalup"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_singpihcal"+hist_extn+"Up", true);
  TH1F* ttw_singpihcalDown = DC.readWriteHisto(fTW, baseDir+"/singpihcaldown"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_singpihcal"+hist_extn+"Down", true);

  TH1F* ttw_flavorqcdUp = DC.readWriteHisto(fTW, baseDir+"/flavorqcdup"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_flavorqcd"+hist_extn+"Up", true);
  TH1F* ttw_flavorqcdDown = DC.readWriteHisto(fTW, baseDir+"/flavorqcddown"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_flavorqcd"+hist_extn+"Down", true);
  TH1F* ttw_timeptetaUp = DC.readWriteHisto(fTW, baseDir+"/timeptetaup"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_timepteta"+hist_extn+"Up", true);
  TH1F* ttw_timeptetaDown = DC.readWriteHisto(fTW, baseDir+"/timeptetadown"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_timepteta"+hist_extn+"Down", true);
  TH1F* ttw_PileupUp = DC.readWriteHisto(fTW, baseDir+"/puup"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_Pileup"+hist_extn+"Up", true);
  TH1F* ttw_PileupDown = DC.readWriteHisto(fTW, baseDir+"/pudown"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_Pileup"+hist_extn+"Down", true);
  TH1F* ttw_PrefireUp, *ttw_PrefireDown;
  if(year==2016 or year==2017){
    ttw_PrefireUp = DC.readWriteHisto(fTW, baseDir+"/prefireup"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_Prefire"+hist_extn+"Up", true);
    ttw_PrefireDown = DC.readWriteHisto(fTW, baseDir+"/prefiredown"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_Prefire"+hist_extn+"Down", true);
  }else{
    ttw_PrefireUp = DC.readWriteHisto(fTW, baseDir+"/base"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_Prefire"+hist_extn+"Up", true);
    ttw_PrefireDown = DC.readWriteHisto(fTW, baseDir+"/base"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_Prefire"+hist_extn+"Down", true);
  }
  TH1F* ttw_PUJetIDUp = DC.readWriteHisto(fTW, baseDir+"/pujetidup"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_PUJetID"+hist_extn+"Up", true);
  TH1F* ttw_PUJetIDDown = DC.readWriteHisto(fTW, baseDir+"/pujetiddown"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_PUJetID"+hist_extn+"Down", true);
  TH1F* ttw_JERUp = DC.readWriteHisto(fTW, baseDir+"/jerup"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_JER"+hist_extn+"Up", true);
  TH1F* ttw_JERDown = DC.readWriteHisto(fTW, baseDir+"/jerdown"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_JER"+hist_extn+"Down", true);
  TH1F* ttw_bcstatUp = DC.readWriteHisto(fTW, baseDir+"/bcstatup"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_bcstat"+hist_extn+"Up", true, isNormalized, ttw);
  TH1F* ttw_bcstatDown = DC.readWriteHisto(fTW, baseDir+"/bcstatdown"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_bcstat"+hist_extn+"Down", true, isNormalized, ttw);
  TH1F *ttw_bcintpUp, *ttw_bcintpDown, *ttw_bcextpUp, *ttw_bcextpDown, *ttw_bcxdybUp, *ttw_bcxdybDown, *ttw_bcxdycUp, *ttw_bcxdycDown, *ttw_bcxwjcUp, *ttw_bcxwjcDown;

  ttw_bcintpUp = DC.readWriteHisto(fTW, baseDir+"/bcintpup"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_bcintp"+hist_extn+"Up", true, isNormalized, ttw);
  ttw_bcintpDown = DC.readWriteHisto(fTW, baseDir+"/bcintpdown"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_bcintp"+hist_extn+"Down", true, isNormalized, ttw);
  ttw_bcextpUp = DC.readWriteHisto(fTW, baseDir+"/bcextpup"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_bcextp"+hist_extn+"Up", true, isNormalized, ttw);
  ttw_bcextpDown = DC.readWriteHisto(fTW, baseDir+"/bcextpdown"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_bcextp"+hist_extn+"Down", true, isNormalized, ttw);
  ttw_bcxdybUp = DC.readWriteHisto(fTW, baseDir+"/bcxdybup"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_bcxdyb"+hist_extn+"Up", true, isNormalized, ttw);
  ttw_bcxdybDown = DC.readWriteHisto(fTW, baseDir+"/bcxdybdown"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_bcxdyb"+hist_extn+"Down", true, isNormalized, ttw);
  ttw_bcxdycUp = DC.readWriteHisto(fTW, baseDir+"/bcxdycup"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_bcxdyc"+hist_extn+"Up", true, isNormalized, ttw);
  ttw_bcxdycDown = DC.readWriteHisto(fTW, baseDir+"/bcxdycdown"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_bcxdyc"+hist_extn+"Down", true, isNormalized, ttw);
  ttw_bcxwjcUp = DC.readWriteHisto(fTW, baseDir+"/bcxwjcup"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_bcxwjc"+hist_extn+"Up", true, isNormalized, ttw);
  ttw_bcxwjcDown = DC.readWriteHisto(fTW, baseDir+"/bcxwjcdown"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_bcxwjc"+hist_extn+"Down", true, isNormalized, ttw);

  TH1F* ttw_pdfUp = DC.readWriteHisto(fTW, baseDir+"/pdfup"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_pdf"+hist_extn+"Up", true);
  TH1F* ttw_pdfDown = DC.readWriteHisto(fTW, baseDir+"/pdfdown"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_pdf"+hist_extn+"Down", true);
  // TH1F* ttw_q2Up = DC.readWriteHisto(fTW, baseDir+"/q2up"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_q2"+hist_extn+"Up", true);
  // TH1F* ttw_q2Down = DC.readWriteHisto(fTW, baseDir+"/q2down"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_q2"+hist_extn+"Down", true);
  TH1F* ttw_bclhemufUp = DC.readWriteHisto(fTW, baseDir+"/bclhemufup"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_bclhemuf"+hist_extn+"Up", true, isNormalized, ttw);
  TH1F* ttw_bclhemufDown = DC.readWriteHisto(fTW, baseDir+"/bclhemufdown"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_bclhemuf"+hist_extn+"Down", true, isNormalized, ttw);
  TH1F* ttw_bclhemurUp = DC.readWriteHisto(fTW, baseDir+"/bclhemurup"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_bclhemur"+hist_extn+"Up", true, isNormalized, ttw);
  TH1F* ttw_bclhemurDown = DC.readWriteHisto(fTW, baseDir+"/bclhemurdown"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_bclhemur"+hist_extn+"Down", true, isNormalized, ttw);
  TH1F* ttw_isrUp = DC.readWriteHisto(fTW, baseDir+"/isrup"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_isr"+hist_extn+"Up", true, isNormalized, ttw);
  TH1F* ttw_isrDown = DC.readWriteHisto(fTW, baseDir+"/isrdown"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_isr"+hist_extn+"Down", true, isNormalized, ttw);
  TH1F* ttw_fsrUp = DC.readWriteHisto(fTW, baseDir+"/fsrup"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_fsr"+hist_extn+"Up", true, isNormalized, ttw);
  TH1F* ttw_fsrDown = DC.readWriteHisto(fTW, baseDir+"/fsrdown"+histSubDir, histName, sf_ttw, fout, fTT, "ttw_fsr"+hist_extn+"Down", true, isNormalized, ttw);  
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //w+jets
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  double sf_wjet = 1;
  baseDir = "Wjets";
  TH1F* wjet = DC.readWriteHisto(fWJ, baseDir+"/base"+histSubDir, histName, sf_wjet, fout, fTT, "wjet", true);
  TH1F *wjet_LeptonUp,*wjet_LeptonDown;
  if(isMuChannel){
    wjet_LeptonUp = DC.readWriteHisto(fWJ, baseDir+"/mueffup"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_Lepton"+hist_extn+"Up", true);
    wjet_LeptonDown = DC.readWriteHisto(fWJ, baseDir+"/mueffdown"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_Lepton"+hist_extn+"Down", true);
  }else{
    wjet_LeptonUp = DC.readWriteHisto(fWJ, baseDir+"/eleeffup"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_Lepton"+hist_extn+"Up", true);
    wjet_LeptonDown = DC.readWriteHisto(fWJ, baseDir+"/eleeffdown"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_Lepton"+hist_extn+"Down", true);
  }
  // TH1F* wjet_JESUp = DC.readWriteHisto(fWJ, baseDir+"/jecup"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_JES"+hist_extn+"Up", true);
  // TH1F* wjet_JESDown = DC.readWriteHisto(fWJ, baseDir+"/jecdown"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_JES"+hist_extn+"Down", true);
  //TH1F* wjet_stotpuUp = DC.readWriteHisto(fWJ, baseDir+"/stotpuup"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_stotpu"+hist_extn+"Up", true);
  //TH1F* wjet_stotpuDown = DC.readWriteHisto(fWJ, baseDir+"/stotpudown"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_stotpu"+hist_extn+"Down", true);
  //TH1F* wjet_stotrelUp = DC.readWriteHisto(fWJ, baseDir+"/stotrelup"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_stotrel"+hist_extn+"Up", true);
  //TH1F* wjet_stotrelDown = DC.readWriteHisto(fWJ, baseDir+"/stotreldown"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_stotrel"+hist_extn+"Down", true);
  //TH1F* wjet_stotptUp = DC.readWriteHisto(fWJ, baseDir+"/stotptup"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_stotpt"+hist_extn+"Up", true);
  //TH1F* wjet_stotptDown = DC.readWriteHisto(fWJ, baseDir+"/stotptdown"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_stotpt"+hist_extn+"Down", true);
  //TH1F* wjet_stotscaleUp = DC.readWriteHisto(fWJ, baseDir+"/stotscaleup"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_stotscale"+hist_extn+"Up", true);
  //TH1F* wjet_stotscaleDown = DC.readWriteHisto(fWJ, baseDir+"/stotscaledown"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_stotscale"+hist_extn+"Down", true);
  TH1F* wjet_absmpfbUp = DC.readWriteHisto(fWJ, baseDir+"/absmpfbup"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_absmpfb"+hist_extn+"Up", true);
  TH1F* wjet_absmpfbDown = DC.readWriteHisto(fWJ, baseDir+"/absmpfbdown"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_absmpfb"+hist_extn+"Down", true);
  TH1F* wjet_abssclUp = DC.readWriteHisto(fWJ, baseDir+"/abssclup"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_absscl"+hist_extn+"Up", true);
  TH1F* wjet_abssclDown = DC.readWriteHisto(fWJ, baseDir+"/absscldown"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_absscl"+hist_extn+"Down", true);
  TH1F* wjet_absstatUp = DC.readWriteHisto(fWJ, baseDir+"/absstatup"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_absstat"+uncorr_extn+"Up", true);
  TH1F* wjet_absstatDown = DC.readWriteHisto(fWJ, baseDir+"/absstatdown"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_absstat"+uncorr_extn+"Down", true);
  
  TH1F* wjet_fragUp = DC.readWriteHisto(fWJ, baseDir+"/fragup"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_frag"+hist_extn+"Up", true);
  TH1F* wjet_fragDown = DC.readWriteHisto(fWJ, baseDir+"/fragdown"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_frag"+hist_extn+"Down", true);
  TH1F* wjet_pudatamcUp = DC.readWriteHisto(fWJ, baseDir+"/pudatamcup"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_pudatamc"+hist_extn+"Up", true);
  TH1F* wjet_pudatamcDown = DC.readWriteHisto(fWJ, baseDir+"/pudatamcdown"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_pudatamc"+hist_extn+"Down", true);

  TH1F* wjet_puptbbUp = DC.readWriteHisto(fWJ, baseDir+"/puptbbup"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_puptbb"+hist_extn+"Up", true);
  TH1F* wjet_puptbbDown = DC.readWriteHisto(fWJ, baseDir+"/puptbbdown"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_puptbb"+hist_extn+"Down", true);
  TH1F* wjet_puptec1Up = DC.readWriteHisto(fWJ, baseDir+"/puptec1up"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_puptec1"+hist_extn+"Up", true);
  TH1F* wjet_puptec1Down = DC.readWriteHisto(fWJ, baseDir+"/puptec1down"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_puptec1"+hist_extn+"Down", true);

  TH1F* wjet_puptec2Up = DC.readWriteHisto(fWJ, baseDir+"/puptec2up"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_puptec2"+hist_extn+"Up", true);
  TH1F* wjet_puptec2Down = DC.readWriteHisto(fWJ, baseDir+"/puptec2down"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_puptec2"+hist_extn+"Down", true);
  TH1F* wjet_pupthfUp = DC.readWriteHisto(fWJ, baseDir+"/pupthfup"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_pupthf"+hist_extn+"Up", true);
  TH1F* wjet_pupthfDown = DC.readWriteHisto(fWJ, baseDir+"/pupthfdown"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_pupthf"+hist_extn+"Down", true);

  TH1F* wjet_puptrefUp = DC.readWriteHisto(fWJ, baseDir+"/puptrefup"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_puptref"+hist_extn+"Up", true);
  TH1F* wjet_puptrefDown = DC.readWriteHisto(fWJ, baseDir+"/puptrefdown"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_puptref"+hist_extn+"Down", true);
  TH1F* wjet_relfsrUp = DC.readWriteHisto(fWJ, baseDir+"/relfsrup"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_relfsr"+hist_extn+"Up", true);
  TH1F* wjet_relfsrDown = DC.readWriteHisto(fWJ, baseDir+"/relfsrdown"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_relfsr"+hist_extn+"Down", true);

  TH1F* wjet_relbalUp = DC.readWriteHisto(fWJ, baseDir+"/relbalup"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_relbal"+hist_extn+"Up", true);
  TH1F* wjet_relbalDown = DC.readWriteHisto(fWJ, baseDir+"/relbaldown"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_relbal"+hist_extn+"Down", true);
  TH1F* wjet_relsampleUp = DC.readWriteHisto(fWJ, baseDir+"/relsampleup"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_relsample"+uncorr_extn+"Up", true);
  TH1F* wjet_relsampleDown = DC.readWriteHisto(fWJ, baseDir+"/relsampledown"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_relsample"+uncorr_extn+"Down", true);

  TH1F* wjet_reljerec1Up = DC.readWriteHisto(fWJ, baseDir+"/reljerec1up"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_reljerec1"+uncorr_extn+"Up", true);
  TH1F* wjet_reljerec1Down = DC.readWriteHisto(fWJ, baseDir+"/reljerec1down"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_reljerec1"+uncorr_extn+"Down", true);
  TH1F* wjet_reljerec2Up = DC.readWriteHisto(fWJ, baseDir+"/reljerec2up"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_reljerec2"+uncorr_extn+"Up", true);
  TH1F* wjet_reljerec2Down = DC.readWriteHisto(fWJ, baseDir+"/reljerec2down"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_reljerec2"+uncorr_extn+"Down", true);

  TH1F* wjet_reljerhfUp = DC.readWriteHisto(fWJ, baseDir+"/reljerhfup"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_reljerhf"+hist_extn+"Up", true);
  TH1F* wjet_reljerhfDown = DC.readWriteHisto(fWJ, baseDir+"/reljerhfdown"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_reljerhf"+hist_extn+"Down", true);
  TH1F* wjet_relptbbUp = DC.readWriteHisto(fWJ, baseDir+"/relptbbup"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_relptbb"+hist_extn+"Up", true);
  TH1F* wjet_relptbbDown = DC.readWriteHisto(fWJ, baseDir+"/relptbbdown"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_relptbb"+hist_extn+"Down", true);

  TH1F* wjet_relptec1Up = DC.readWriteHisto(fWJ, baseDir+"/relptec1up"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_relptec1"+uncorr_extn+"Up", true);
  TH1F* wjet_relptec1Down = DC.readWriteHisto(fWJ, baseDir+"/relptec1down"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_relptec1"+uncorr_extn+"Down", true);
  TH1F* wjet_relptec2Up = DC.readWriteHisto(fWJ, baseDir+"/relptec2up"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_relptec2"+uncorr_extn+"Up", true);
  TH1F* wjet_relptec2Down = DC.readWriteHisto(fWJ, baseDir+"/relptec2down"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_relptec2"+uncorr_extn+"Down", true);

  TH1F* wjet_relpthfUp = DC.readWriteHisto(fWJ, baseDir+"/relpthfup"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_relpthf"+hist_extn+"Up", true);
  TH1F* wjet_relpthfDown = DC.readWriteHisto(fWJ, baseDir+"/relpthfdown"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_relpthf"+hist_extn+"Down", true);
  TH1F* wjet_relstatecUp = DC.readWriteHisto(fWJ, baseDir+"/relstatecup"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_relstatec"+uncorr_extn+"Up", true);
  TH1F* wjet_relstatecDown = DC.readWriteHisto(fWJ, baseDir+"/relstatecdown"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_relstatec"+uncorr_extn+"Down", true);

  TH1F* wjet_relstatfsrUp = DC.readWriteHisto(fWJ, baseDir+"/relstatfsrup"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_relstatfsr"+uncorr_extn+"Up", true);
  TH1F* wjet_relstatfsrDown = DC.readWriteHisto(fWJ, baseDir+"/relstatfsrdown"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_relstatfsr"+uncorr_extn+"Down", true);
  TH1F* wjet_relstathfUp = DC.readWriteHisto(fWJ, baseDir+"/relstathfup"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_relstathf"+uncorr_extn+"Up", true);
  TH1F* wjet_relstathfDown = DC.readWriteHisto(fWJ, baseDir+"/relstathfdown"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_relstathf"+uncorr_extn+"Down", true);

  TH1F* wjet_singpiecalUp = DC.readWriteHisto(fWJ, baseDir+"/singpiecalup"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_singpiecal"+hist_extn+"Up", true);
  TH1F* wjet_singpiecalDown = DC.readWriteHisto(fWJ, baseDir+"/singpiecaldown"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_singpiecal"+hist_extn+"Down", true);
  TH1F* wjet_singpihcalUp = DC.readWriteHisto(fWJ, baseDir+"/singpihcalup"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_singpihcal"+hist_extn+"Up", true);
  TH1F* wjet_singpihcalDown = DC.readWriteHisto(fWJ, baseDir+"/singpihcaldown"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_singpihcal"+hist_extn+"Down", true);

  TH1F* wjet_flavorqcdUp = DC.readWriteHisto(fWJ, baseDir+"/flavorqcdup"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_flavorqcd"+hist_extn+"Up", true);
  TH1F* wjet_flavorqcdDown = DC.readWriteHisto(fWJ, baseDir+"/flavorqcddown"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_flavorqcd"+hist_extn+"Down", true);
  TH1F* wjet_timeptetaUp = DC.readWriteHisto(fWJ, baseDir+"/timeptetaup"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_timepteta"+hist_extn+"Up", true);
  TH1F* wjet_timeptetaDown = DC.readWriteHisto(fWJ, baseDir+"/timeptetadown"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_timepteta"+hist_extn+"Down", true);
  TH1F* wjet_PileupUp = DC.readWriteHisto(fWJ, baseDir+"/puup"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_Pileup"+hist_extn+"Up", true);
  TH1F* wjet_PileupDown = DC.readWriteHisto(fWJ, baseDir+"/pudown"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_Pileup"+hist_extn+"Down", true);
  TH1F* wjet_PrefireUp, *wjet_PrefireDown;
  if(year==2016 or year==2017){
    wjet_PrefireUp = DC.readWriteHisto(fWJ, baseDir+"/prefireup"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_Prefire"+hist_extn+"Up", true);
    wjet_PrefireDown = DC.readWriteHisto(fWJ, baseDir+"/prefiredown"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_Prefire"+hist_extn+"Down", true);
  }else{
    wjet_PrefireUp = DC.readWriteHisto(fWJ, baseDir+"/base"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_Prefire"+hist_extn+"Up", true);
    wjet_PrefireDown = DC.readWriteHisto(fWJ, baseDir+"/base"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_Prefire"+hist_extn+"Down", true);
  }
  TH1F* wjet_PUJetIDUp = DC.readWriteHisto(fWJ, baseDir+"/pujetidup"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_PUJetID"+hist_extn+"Up", true);
  TH1F* wjet_PUJetIDDown = DC.readWriteHisto(fWJ, baseDir+"/pujetiddown"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_PUJetID"+hist_extn+"Down", true);
  TH1F* wjet_JERUp = DC.readWriteHisto(fWJ, baseDir+"/jerup"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_JER"+hist_extn+"Up", true);
  TH1F* wjet_JERDown = DC.readWriteHisto(fWJ, baseDir+"/jerdown"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_JER"+hist_extn+"Down", true);
  TH1F* wjet_bcstatUp = DC.readWriteHisto(fWJ, baseDir+"/bcstatup"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_bcstat"+hist_extn+"Up", true, isNormalized, wjet);
  TH1F* wjet_bcstatDown = DC.readWriteHisto(fWJ, baseDir+"/bcstatdown"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_bcstat"+hist_extn+"Down", true, isNormalized, wjet);
  TH1F *wjet_bcintpUp, *wjet_bcintpDown, *wjet_bcextpUp, *wjet_bcextpDown, *wjet_bcxdybUp, *wjet_bcxdybDown, *wjet_bcxdycUp, *wjet_bcxdycDown, *wjet_bcxwjcUp, *wjet_bcxwjcDown;

  wjet_bcintpUp = DC.readWriteHisto(fWJ, baseDir+"/bcintpup"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_bcintp"+hist_extn+"Up", true, isNormalized, wjet);
  wjet_bcintpDown = DC.readWriteHisto(fWJ, baseDir+"/bcintpdown"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_bcintp"+hist_extn+"Down", true, isNormalized, wjet);
  wjet_bcextpUp = DC.readWriteHisto(fWJ, baseDir+"/bcextpup"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_bcextp"+hist_extn+"Up", true, isNormalized, wjet);
  wjet_bcextpDown = DC.readWriteHisto(fWJ, baseDir+"/bcextpdown"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_bcextp"+hist_extn+"Down", true, isNormalized, wjet);
  wjet_bcxdybUp = DC.readWriteHisto(fWJ, baseDir+"/bcxdybup"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_bcxdyb"+hist_extn+"Up", true, isNormalized, wjet);
  wjet_bcxdybDown = DC.readWriteHisto(fWJ, baseDir+"/bcxdybdown"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_bcxdyb"+hist_extn+"Down", true, isNormalized, wjet);
  wjet_bcxdycUp = DC.readWriteHisto(fWJ, baseDir+"/bcxdycup"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_bcxdyc"+hist_extn+"Up", true, isNormalized, wjet);
  wjet_bcxdycDown = DC.readWriteHisto(fWJ, baseDir+"/bcxdycdown"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_bcxdyc"+hist_extn+"Down", true, isNormalized, wjet);
  wjet_bcxwjcUp = DC.readWriteHisto(fWJ, baseDir+"/bcxwjcup"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_bcxwjc"+hist_extn+"Up", true, isNormalized, wjet);
  wjet_bcxwjcDown = DC.readWriteHisto(fWJ, baseDir+"/bcxwjcdown"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_bcxwjc"+hist_extn+"Down", true, isNormalized, wjet);

  TH1F* wjet_pdfUp = DC.readWriteHisto(fWJ, baseDir+"/pdfup"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_pdf"+hist_extn+"Up", true);
  TH1F* wjet_pdfDown = DC.readWriteHisto(fWJ, baseDir+"/pdfdown"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_pdf"+hist_extn+"Down", true);
  // TH1F* wjet_q2Up = DC.readWriteHisto(fWJ, baseDir+"/q2up"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_q2"+hist_extn+"Up", true);
  // TH1F* wjet_q2Down = DC.readWriteHisto(fWJ, baseDir+"/q2down"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_q2"+hist_extn+"Down", true);
  TH1F* wjet_bclhemufUp = DC.readWriteHisto(fWJ, baseDir+"/bclhemufup"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_bclhemuf"+hist_extn+"Up", true, isNormalized, wjet);
  TH1F* wjet_bclhemufDown = DC.readWriteHisto(fWJ, baseDir+"/bclhemufdown"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_bclhemuf"+hist_extn+"Down", true, isNormalized, wjet);
  TH1F* wjet_bclhemurUp = DC.readWriteHisto(fWJ, baseDir+"/bclhemurup"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_bclhemur"+hist_extn+"Up", true, isNormalized, wjet);
  TH1F* wjet_bclhemurDown = DC.readWriteHisto(fWJ, baseDir+"/bclhemurdown"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_bclhemur"+hist_extn+"Down", true, isNormalized, wjet);
  TH1F* wjet_isrUp = DC.readWriteHisto(fWJ, baseDir+"/isrup"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_isr"+hist_extn+"Up", true, isNormalized, wjet);
  TH1F* wjet_isrDown = DC.readWriteHisto(fWJ, baseDir+"/isrdown"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_isr"+hist_extn+"Down", true, isNormalized, wjet);
  TH1F* wjet_fsrUp = DC.readWriteHisto(fWJ, baseDir+"/fsrup"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_fsr"+hist_extn+"Up", true, isNormalized, wjet);
  TH1F* wjet_fsrDown = DC.readWriteHisto(fWJ, baseDir+"/fsrdown"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_fsr"+hist_extn+"Down", true, isNormalized, wjet);
  // //MiniAOD nuisances
  // TH1F* wjet_bcTag1Up = DC.readWriteHisto(fWJ, baseDir+"/bctag1up"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_bcTag1"+hist_extn+"Up", true, isNormalized, wjet);
  // TH1F* wjet_bcTag1Down = DC.readWriteHisto(fWJ, baseDir+"/bctag1down"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_bcTag1"+hist_extn+"Down", true, isNormalized, wjet);
  // TH1F* wjet_bcTag2Up = DC.readWriteHisto(fWJ, baseDir+"/bctag2up"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_bcTag2"+hist_extn+"Up", true, isNormalized, wjet);
  // TH1F* wjet_bcTag2Down = DC.readWriteHisto(fWJ, baseDir+"/bctag2down"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_bcTag2"+hist_extn+"Down", true, isNormalized, wjet);
  // TH1F* wjet_bcTag3Up = DC.readWriteHisto(fWJ, baseDir+"/bctag3up"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_bcTag3"+hist_extn+"Up", true, isNormalized, wjet);
  // TH1F* wjet_bcTag3Down = DC.readWriteHisto(fWJ, baseDir+"/bctag3down"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_bcTag3"+hist_extn+"Down", true, isNormalized, wjet);
  // TH1F* wjet_bTagbcUp = DC.readWriteHisto(fWJ, baseDir+"/btagbup"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_bTagbc"+hist_extn+"Up", true, isNormalized, wjet);
  // TH1F* wjet_bTagbcDown = DC.readWriteHisto(fWJ, baseDir+"/btagbdown"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_bTagbc"+hist_extn+"Down", true, isNormalized, wjet);
  // TH1F* wjet_bTaglUp = DC.readWriteHisto(fWJ, baseDir+"/btaglup"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_bTagl"+hist_extn+"Up", true, isNormalized, wjet);
  // TH1F* wjet_bTaglDown = DC.readWriteHisto(fWJ, baseDir+"/btagldown"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_bTagl"+hist_extn+"Down", true, isNormalized, wjet);
  
  if(isBinStat){
    for(int ibin = 1; ibin <= nonStatBins ; ibin++){
      TH1F *wjet_bin_stat_Up = DC.readWriteHisto(fWJ, baseDir+"/base"+histSubDir, histName, sf_wjet, fout, fTT, Form("wjet_CMS_stat_cat1_wjet_bin_%dUp",ibin), true);
      TH1F *wjet_bin_stat_Do = DC.readWriteHisto(fWJ, baseDir+"/base"+histSubDir, histName, sf_wjet, fout, fTT, Form("wjet_CMS_stat_cat1_wjet_bin_%dDown",ibin), true);
    }
  }

  double unc_wjet_ExL = 1.0;
  double unc_wjet_ExM = 1.0;
  if(isExL){
    TH1F* wjet_yLyMyT = DC.getHisto(fWJ, baseDir+"/Iso/ExCTag/", "sf_CTag_yLyMyT_wt", fTT);
    TH1F* wjet_yLyMnT = DC.getHisto(fWJ, baseDir+"/Iso/ExCTag/", "sf_CTag_yLyMnT_wt", fTT);
    TH1F* wjet_yLnMyT = DC.getHisto(fWJ, baseDir+"/Iso/ExCTag/", "sf_CTag_yLnMyT_wt", fTT);
    TH1F* wjet_yLnMnT = DC.getHisto(fWJ, baseDir+"/Iso/ExCTag/", "sf_CTag_yLnMnT_wt", fTT);
    unc_wjet_ExL = DC.getUncExL(wjet_yLyMyT, wjet_yLyMnT, wjet_yLnMyT, wjet_yLnMnT);
  }
  if(isExM){
    TH1F* wjet_yMyT = DC.getHisto(fWJ, baseDir+"/Iso/ExCTag/", "sf_CTag_yMyT_wt", fTT);
    TH1F* wjet_yMnT = DC.getHisto(fWJ, baseDir+"/Iso/ExCTag/", "sf_CTag_yMnT_wt", fTT);
    unc_wjet_ExM = DC.getUncExM(wjet_yMyT, wjet_yMnT);
  }
  //=====================================================================================================================================================================
  //Z+Jets
  double sf_zjet = 1;
  baseDir = "DYjets";
  TH1F* zjet = DC.readWriteHisto(fDY, baseDir+"/base"+histSubDir, histName, sf_zjet, fout, fTT, "zjet", true);
  TH1F *zjet_LeptonUp,*zjet_LeptonDown;
  if(isMuChannel){
    zjet_LeptonUp = DC.readWriteHisto(fDY, baseDir+"/mueffup"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_Lepton"+hist_extn+"Up", true);
    zjet_LeptonDown = DC.readWriteHisto(fDY, baseDir+"/mueffdown"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_Lepton"+hist_extn+"Down", true);
  }else{
    zjet_LeptonUp = DC.readWriteHisto(fDY, baseDir+"/eleeffup"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_Lepton"+hist_extn+"Up", true);
    zjet_LeptonDown = DC.readWriteHisto(fDY, baseDir+"/eleeffdown"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_Lepton"+hist_extn+"Down", true);
  }
  // TH1F* zjet_JESUp = DC.readWriteHisto(fDY, baseDir+"/jecup"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_JES"+hist_extn+"Up", true);
  // TH1F* zjet_JESDown = DC.readWriteHisto(fDY, baseDir+"/jecdown"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_JES"+hist_extn+"Down", true);
  //TH1F* zjet_stotpuUp = DC.readWriteHisto(fDY, baseDir+"/stotpuup"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_stotpu"+hist_extn+"Up", true);
  //TH1F* zjet_stotpuDown = DC.readWriteHisto(fDY, baseDir+"/stotpudown"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_stotpu"+hist_extn+"Down", true);
  //TH1F* zjet_stotrelUp = DC.readWriteHisto(fDY, baseDir+"/stotrelup"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_stotrel"+hist_extn+"Up", true);
  //TH1F* zjet_stotrelDown = DC.readWriteHisto(fDY, baseDir+"/stotreldown"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_stotrel"+hist_extn+"Down", true);
  //TH1F* zjet_stotptUp = DC.readWriteHisto(fDY, baseDir+"/stotptup"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_stotpt"+hist_extn+"Up", true);
  //TH1F* zjet_stotptDown = DC.readWriteHisto(fDY, baseDir+"/stotptdown"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_stotpt"+hist_extn+"Down", true);
  //TH1F* zjet_stotscaleUp = DC.readWriteHisto(fDY, baseDir+"/stotscaleup"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_stotscale"+hist_extn+"Up", true);
  //TH1F* zjet_stotscaleDown = DC.readWriteHisto(fDY, baseDir+"/stotscaledown"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_stotscale"+hist_extn+"Down", true);
  TH1F* zjet_absmpfbUp = DC.readWriteHisto(fDY, baseDir+"/absmpfbup"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_absmpfb"+hist_extn+"Up", true);
  TH1F* zjet_absmpfbDown = DC.readWriteHisto(fDY, baseDir+"/absmpfbdown"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_absmpfb"+hist_extn+"Down", true);
  TH1F* zjet_abssclUp = DC.readWriteHisto(fDY, baseDir+"/abssclup"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_absscl"+hist_extn+"Up", true);
  TH1F* zjet_abssclDown = DC.readWriteHisto(fDY, baseDir+"/absscldown"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_absscl"+hist_extn+"Down", true);
  TH1F* zjet_absstatUp = DC.readWriteHisto(fDY, baseDir+"/absstatup"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_absstat"+uncorr_extn+"Up", true);
  TH1F* zjet_absstatDown = DC.readWriteHisto(fDY, baseDir+"/absstatdown"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_absstat"+uncorr_extn+"Down", true);
  
  TH1F* zjet_fragUp = DC.readWriteHisto(fDY, baseDir+"/fragup"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_frag"+hist_extn+"Up", true);
  TH1F* zjet_fragDown = DC.readWriteHisto(fDY, baseDir+"/fragdown"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_frag"+hist_extn+"Down", true);
  TH1F* zjet_pudatamcUp = DC.readWriteHisto(fDY, baseDir+"/pudatamcup"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_pudatamc"+hist_extn+"Up", true);
  TH1F* zjet_pudatamcDown = DC.readWriteHisto(fDY, baseDir+"/pudatamcdown"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_pudatamc"+hist_extn+"Down", true);

  TH1F* zjet_puptbbUp = DC.readWriteHisto(fDY, baseDir+"/puptbbup"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_puptbb"+hist_extn+"Up", true);
  TH1F* zjet_puptbbDown = DC.readWriteHisto(fDY, baseDir+"/puptbbdown"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_puptbb"+hist_extn+"Down", true);
  TH1F* zjet_puptec1Up = DC.readWriteHisto(fDY, baseDir+"/puptec1up"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_puptec1"+hist_extn+"Up", true);
  TH1F* zjet_puptec1Down = DC.readWriteHisto(fDY, baseDir+"/puptec1down"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_puptec1"+hist_extn+"Down", true);

  TH1F* zjet_puptec2Up = DC.readWriteHisto(fDY, baseDir+"/puptec2up"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_puptec2"+hist_extn+"Up", true);
  TH1F* zjet_puptec2Down = DC.readWriteHisto(fDY, baseDir+"/puptec2down"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_puptec2"+hist_extn+"Down", true);
  TH1F* zjet_pupthfUp = DC.readWriteHisto(fDY, baseDir+"/pupthfup"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_pupthf"+hist_extn+"Up", true);
  TH1F* zjet_pupthfDown = DC.readWriteHisto(fDY, baseDir+"/pupthfdown"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_pupthf"+hist_extn+"Down", true);

  TH1F* zjet_puptrefUp = DC.readWriteHisto(fDY, baseDir+"/puptrefup"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_puptref"+hist_extn+"Up", true);
  TH1F* zjet_puptrefDown = DC.readWriteHisto(fDY, baseDir+"/puptrefdown"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_puptref"+hist_extn+"Down", true);
  TH1F* zjet_relfsrUp = DC.readWriteHisto(fDY, baseDir+"/relfsrup"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_relfsr"+hist_extn+"Up", true);
  TH1F* zjet_relfsrDown = DC.readWriteHisto(fDY, baseDir+"/relfsrdown"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_relfsr"+hist_extn+"Down", true);

  TH1F* zjet_relbalUp = DC.readWriteHisto(fDY, baseDir+"/relbalup"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_relbal"+hist_extn+"Up", true);
  TH1F* zjet_relbalDown = DC.readWriteHisto(fDY, baseDir+"/relbaldown"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_relbal"+hist_extn+"Down", true);
  TH1F* zjet_relsampleUp = DC.readWriteHisto(fDY, baseDir+"/relsampleup"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_relsample"+uncorr_extn+"Up", true);
  TH1F* zjet_relsampleDown = DC.readWriteHisto(fDY, baseDir+"/relsampledown"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_relsample"+uncorr_extn+"Down", true);

  TH1F* zjet_reljerec1Up = DC.readWriteHisto(fDY, baseDir+"/reljerec1up"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_reljerec1"+uncorr_extn+"Up", true);
  TH1F* zjet_reljerec1Down = DC.readWriteHisto(fDY, baseDir+"/reljerec1down"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_reljerec1"+uncorr_extn+"Down", true);
  TH1F* zjet_reljerec2Up = DC.readWriteHisto(fDY, baseDir+"/reljerec2up"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_reljerec2"+uncorr_extn+"Up", true);
  TH1F* zjet_reljerec2Down = DC.readWriteHisto(fDY, baseDir+"/reljerec2down"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_reljerec2"+uncorr_extn+"Down", true);

  TH1F* zjet_reljerhfUp = DC.readWriteHisto(fDY, baseDir+"/reljerhfup"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_reljerhf"+hist_extn+"Up", true);
  TH1F* zjet_reljerhfDown = DC.readWriteHisto(fDY, baseDir+"/reljerhfdown"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_reljerhf"+hist_extn+"Down", true);
  TH1F* zjet_relptbbUp = DC.readWriteHisto(fDY, baseDir+"/relptbbup"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_relptbb"+hist_extn+"Up", true);
  TH1F* zjet_relptbbDown = DC.readWriteHisto(fDY, baseDir+"/relptbbdown"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_relptbb"+hist_extn+"Down", true);

  TH1F* zjet_relptec1Up = DC.readWriteHisto(fDY, baseDir+"/relptec1up"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_relptec1"+uncorr_extn+"Up", true);
  TH1F* zjet_relptec1Down = DC.readWriteHisto(fDY, baseDir+"/relptec1down"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_relptec1"+uncorr_extn+"Down", true);
  TH1F* zjet_relptec2Up = DC.readWriteHisto(fDY, baseDir+"/relptec2up"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_relptec2"+uncorr_extn+"Up", true);
  TH1F* zjet_relptec2Down = DC.readWriteHisto(fDY, baseDir+"/relptec2down"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_relptec2"+uncorr_extn+"Down", true);

  TH1F* zjet_relpthfUp = DC.readWriteHisto(fDY, baseDir+"/relpthfup"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_relpthf"+hist_extn+"Up", true);
  TH1F* zjet_relpthfDown = DC.readWriteHisto(fDY, baseDir+"/relpthfdown"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_relpthf"+hist_extn+"Down", true);
  TH1F* zjet_relstatecUp = DC.readWriteHisto(fDY, baseDir+"/relstatecup"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_relstatec"+uncorr_extn+"Up", true);
  TH1F* zjet_relstatecDown = DC.readWriteHisto(fDY, baseDir+"/relstatecdown"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_relstatec"+uncorr_extn+"Down", true);

  TH1F* zjet_relstatfsrUp = DC.readWriteHisto(fDY, baseDir+"/relstatfsrup"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_relstatfsr"+uncorr_extn+"Up", true);
  TH1F* zjet_relstatfsrDown = DC.readWriteHisto(fDY, baseDir+"/relstatfsrdown"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_relstatfsr"+uncorr_extn+"Down", true);
  TH1F* zjet_relstathfUp = DC.readWriteHisto(fDY, baseDir+"/relstathfup"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_relstathf"+uncorr_extn+"Up", true);
  TH1F* zjet_relstathfDown = DC.readWriteHisto(fDY, baseDir+"/relstathfdown"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_relstathf"+uncorr_extn+"Down", true);

  TH1F* zjet_singpiecalUp = DC.readWriteHisto(fDY, baseDir+"/singpiecalup"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_singpiecal"+hist_extn+"Up", true);
  TH1F* zjet_singpiecalDown = DC.readWriteHisto(fDY, baseDir+"/singpiecaldown"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_singpiecal"+hist_extn+"Down", true);
  TH1F* zjet_singpihcalUp = DC.readWriteHisto(fDY, baseDir+"/singpihcalup"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_singpihcal"+hist_extn+"Up", true);
  TH1F* zjet_singpihcalDown = DC.readWriteHisto(fDY, baseDir+"/singpihcaldown"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_singpihcal"+hist_extn+"Down", true);

  TH1F* zjet_flavorqcdUp = DC.readWriteHisto(fDY, baseDir+"/flavorqcdup"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_flavorqcd"+hist_extn+"Up", true);
  TH1F* zjet_flavorqcdDown = DC.readWriteHisto(fDY, baseDir+"/flavorqcddown"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_flavorqcd"+hist_extn+"Down", true);
  TH1F* zjet_timeptetaUp = DC.readWriteHisto(fDY, baseDir+"/timeptetaup"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_timepteta"+uncorr_extn+"Up", true);
  TH1F* zjet_timeptetaDown = DC.readWriteHisto(fDY, baseDir+"/timeptetadown"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_timepteta"+uncorr_extn+"Down", true);
  TH1F* zjet_PileupUp = DC.readWriteHisto(fDY, baseDir+"/puup"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_Pileup"+hist_extn+"Up", true);
  TH1F* zjet_PileupDown = DC.readWriteHisto(fDY, baseDir+"/pudown"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_Pileup"+hist_extn+"Down", true);
  TH1F* zjet_PrefireUp, *zjet_PrefireDown;
  if(year==2016 or year==2017){
    zjet_PrefireUp = DC.readWriteHisto(fDY, baseDir+"/prefireup"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_Prefire"+hist_extn+"Up", true);
    zjet_PrefireDown = DC.readWriteHisto(fDY, baseDir+"/prefiredown"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_Prefire"+hist_extn+"Down", true);
  }else{
    zjet_PrefireUp = DC.readWriteHisto(fDY, baseDir+"/base"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_Prefire"+hist_extn+"Up", true);
    zjet_PrefireDown = DC.readWriteHisto(fDY, baseDir+"/base"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_Prefire"+hist_extn+"Down", true);
  }
  TH1F* zjet_PUJetIDUp = DC.readWriteHisto(fDY, baseDir+"/pujetidup"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_PUJetID"+hist_extn+"Up", true);
  TH1F* zjet_PUJetIDDown = DC.readWriteHisto(fDY, baseDir+"/pujetiddown"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_PUJetID"+hist_extn+"Down", true);
  TH1F* zjet_JERUp = DC.readWriteHisto(fDY, baseDir+"/jerup"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_JER"+hist_extn+"Up", true);
  TH1F* zjet_JERDown = DC.readWriteHisto(fDY, baseDir+"/jerdown"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_JER"+hist_extn+"Down", true);
  TH1F* zjet_bcstatUp = DC.readWriteHisto(fDY, baseDir+"/bcstatup"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_bcstat"+hist_extn+"Up", true, isNormalized, zjet);
  TH1F* zjet_bcstatDown = DC.readWriteHisto(fDY, baseDir+"/bcstatdown"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_bcstat"+hist_extn+"Down", true, isNormalized, zjet);
  TH1F *zjet_bcintpUp, *zjet_bcintpDown, *zjet_bcextpUp, *zjet_bcextpDown, *zjet_bcxdybUp, *zjet_bcxdybDown, *zjet_bcxdycUp, *zjet_bcxdycDown, *zjet_bcxwjcUp, *zjet_bcxwjcDown;

  zjet_bcintpUp = DC.readWriteHisto(fDY, baseDir+"/bcintpup"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_bcintp"+hist_extn+"Up", true, isNormalized, zjet);
  zjet_bcintpDown = DC.readWriteHisto(fDY, baseDir+"/bcintpdown"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_bcintp"+hist_extn+"Down", true, isNormalized, zjet);
  zjet_bcextpUp = DC.readWriteHisto(fDY, baseDir+"/bcextpup"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_bcextp"+hist_extn+"Up", true, isNormalized, zjet);
  zjet_bcextpDown = DC.readWriteHisto(fDY, baseDir+"/bcextpdown"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_bcextp"+hist_extn+"Down", true, isNormalized, zjet);
  zjet_bcxdybUp = DC.readWriteHisto(fDY, baseDir+"/bcxdybup"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_bcxdyb"+hist_extn+"Up", true, isNormalized, zjet);
  zjet_bcxdybDown = DC.readWriteHisto(fDY, baseDir+"/bcxdybdown"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_bcxdyb"+hist_extn+"Down", true, isNormalized, zjet);
  zjet_bcxdycUp = DC.readWriteHisto(fDY, baseDir+"/bcxdycup"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_bcxdyc"+hist_extn+"Up", true, isNormalized, zjet);
  zjet_bcxdycDown = DC.readWriteHisto(fDY, baseDir+"/bcxdycdown"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_bcxdyc"+hist_extn+"Down", true, isNormalized, zjet);
  zjet_bcxwjcUp = DC.readWriteHisto(fDY, baseDir+"/bcxwjcup"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_bcxwjc"+hist_extn+"Up", true, isNormalized, zjet);
  zjet_bcxwjcDown = DC.readWriteHisto(fDY, baseDir+"/bcxwjcdown"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_bcxwjc"+hist_extn+"Down", true, isNormalized, zjet);
  
  TH1F* zjet_pdfUp = DC.readWriteHisto(fDY, baseDir+"/pdfup"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_pdf"+hist_extn+"Up", true);
  TH1F* zjet_pdfDown = DC.readWriteHisto(fDY, baseDir+"/pdfdown"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_pdf"+hist_extn+"Down", true);
  // TH1F* zjet_q2Up = DC.readWriteHisto(fDY, baseDir+"/q2up"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_q2"+hist_extn+"Up", true);
  // TH1F* zjet_q2Down = DC.readWriteHisto(fDY, baseDir+"/q2down"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_q2"+hist_extn+"Down", true);
  TH1F* zjet_bclhemufUp = DC.readWriteHisto(fDY, baseDir+"/bclhemufup"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_bclhemuf"+hist_extn+"Up", true, isNormalized, zjet);
  TH1F* zjet_bclhemufDown = DC.readWriteHisto(fDY, baseDir+"/bclhemufdown"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_bclhemuf"+hist_extn+"Down", true, isNormalized, zjet);
  TH1F* zjet_bclhemurUp = DC.readWriteHisto(fDY, baseDir+"/bclhemurup"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_bclhemur"+hist_extn+"Up", true, isNormalized, zjet);
  TH1F* zjet_bclhemurDown = DC.readWriteHisto(fDY, baseDir+"/bclhemurdown"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_bclhemur"+hist_extn+"Down", true, isNormalized, zjet);
  TH1F* zjet_isrUp = DC.readWriteHisto(fDY, baseDir+"/isrup"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_isr"+hist_extn+"Up", true, isNormalized, zjet);
  TH1F* zjet_isrDown = DC.readWriteHisto(fDY, baseDir+"/isrdown"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_isr"+hist_extn+"Down", true, isNormalized, zjet);
  TH1F* zjet_fsrUp = DC.readWriteHisto(fDY, baseDir+"/fsrup"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_fsr"+hist_extn+"Up", true, isNormalized, zjet);
  TH1F* zjet_fsrDown = DC.readWriteHisto(fDY, baseDir+"/fsrdown"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_fsr"+hist_extn+"Down", true, isNormalized, zjet);
  // //MiniAOD nuisances
  // TH1F* zjet_bcTag1Up = DC.readWriteHisto(fDY, baseDir+"/bctag1up"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_bcTag1"+hist_extn+"Up", true, isNormalized, zjet);
  // TH1F* zjet_bcTag1Down = DC.readWriteHisto(fDY, baseDir+"/bctag1down"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_bcTag1"+hist_extn+"Down", true, isNormalized, zjet);
  // TH1F* zjet_bcTag2Up = DC.readWriteHisto(fDY, baseDir+"/bctag2up"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_bcTag2"+hist_extn+"Up", true, isNormalized, zjet);
  // TH1F* zjet_bcTag2Down = DC.readWriteHisto(fDY, baseDir+"/bctag2down"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_bcTag2"+hist_extn+"Down", true, isNormalized, zjet);
  // TH1F* zjet_bcTag3Up = DC.readWriteHisto(fDY, baseDir+"/bctag3up"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_bcTag3"+hist_extn+"Up", true, isNormalized, zjet);
  // TH1F* zjet_bcTag3Down = DC.readWriteHisto(fDY, baseDir+"/bctag3down"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_bcTag3"+hist_extn+"Down", true, isNormalized, zjet);
  // TH1F* zjet_bTagbcUp = DC.readWriteHisto(fDY, baseDir+"/btagbup"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_bTagbc"+hist_extn+"Up", true, isNormalized, zjet);
  // TH1F* zjet_bTagbcDown = DC.readWriteHisto(fDY, baseDir+"/btagbdown"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_bTagbc"+hist_extn+"Down", true, isNormalized, zjet);
  // TH1F* zjet_bTaglUp = DC.readWriteHisto(fDY, baseDir+"/btaglup"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_bTagl"+hist_extn+"Up", true, isNormalized, zjet);
  // TH1F* zjet_bTaglDown = DC.readWriteHisto(fDY, baseDir+"/btagldown"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_bTagl"+hist_extn+"Down", true, isNormalized, zjet);

  if(isBinStat){
    for(int ibin = 1; ibin <= nonStatBins ; ibin++){
      TH1F *zjet_bin_stat_Up = DC.readWriteHisto(fDY, baseDir+"/base"+histSubDir, histName, sf_zjet, fout, fTT, Form("zjet_CMS_stat_cat1_zjet_bin_%dUp",ibin), true);
      TH1F *zjet_bin_stat_Do = DC.readWriteHisto(fDY, baseDir+"/base"+histSubDir, histName, sf_zjet, fout, fTT, Form("zjet_CMS_stat_cat1_zjet_bin_%dDown",ibin), true);
    }
  }
  
  double unc_zjet_ExL = 1.0;
  double unc_zjet_ExM = 1.0;
  if(isExL){
    TH1F* zjet_yLyMyT = DC.getHisto(fDY, baseDir+"/Iso/ExCTag/", "sf_CTag_yLyMyT_wt", fTT);
    TH1F* zjet_yLyMnT = DC.getHisto(fDY, baseDir+"/Iso/ExCTag/", "sf_CTag_yLyMnT_wt", fTT);
    TH1F* zjet_yLnMyT = DC.getHisto(fDY, baseDir+"/Iso/ExCTag/", "sf_CTag_yLnMyT_wt", fTT);
    TH1F* zjet_yLnMnT = DC.getHisto(fDY, baseDir+"/Iso/ExCTag/", "sf_CTag_yLnMnT_wt", fTT);
    unc_zjet_ExL = DC.getUncExL(zjet_yLyMyT, zjet_yLyMnT, zjet_yLnMyT, zjet_yLnMnT);
  }
  if(isExM){
    TH1F* zjet_yMyT = DC.getHisto(fDY, baseDir+"/Iso/ExCTag/", "sf_CTag_yMyT_wt", fTT);
    TH1F* zjet_yMnT = DC.getHisto(fDY, baseDir+"/Iso/ExCTag/", "sf_CTag_yMnT_wt", fTT);
    unc_zjet_ExM = DC.getUncExM(zjet_yMyT, zjet_yMnT);
  }

  //SingleTop
  double sf_stop = 1.0;
  baseDir = "singleTop";
  TH1F* stop = DC.readWriteHisto(fST, baseDir+"/base"+histSubDir, histName, sf_stop, fout, fTT, "stop", true);
  TH1F *stop_LeptonUp,*stop_LeptonDown;
  if(isMuChannel){
    stop_LeptonUp = DC.readWriteHisto(fST, baseDir+"/mueffup"+histSubDir, histName, sf_stop, fout, fTT, "stop_Lepton"+hist_extn+"Up", true);
    stop_LeptonDown = DC.readWriteHisto(fST, baseDir+"/mueffdown"+histSubDir, histName, sf_stop, fout, fTT, "stop_Lepton"+hist_extn+"Down", true);
  }else{
    stop_LeptonUp = DC.readWriteHisto(fST, baseDir+"/eleeffup"+histSubDir, histName, sf_stop, fout, fTT, "stop_Lepton"+hist_extn+"Up", true);
    stop_LeptonDown = DC.readWriteHisto(fST, baseDir+"/eleeffdown"+histSubDir, histName, sf_stop, fout, fTT, "stop_Lepton"+hist_extn+"Down", true);
  }
  // TH1F* stop_JESUp = DC.readWriteHisto(fST, baseDir+"/jecup"+histSubDir, histName, sf_stop, fout, fTT, "stop_JES"+hist_extn+"Up", true);
  // TH1F* stop_JESDown = DC.readWriteHisto(fST, baseDir+"/jecdown"+histSubDir, histName, sf_stop, fout, fTT, "stop_JES"+hist_extn+"Down", true);
  //TH1F* stop_stotpuUp = DC.readWriteHisto(fST, baseDir+"/stotpuup"+histSubDir, histName, sf_stop, fout, fTT, "stop_stotpu"+hist_extn+"Up", true);
  //TH1F* stop_stotpuDown = DC.readWriteHisto(fST, baseDir+"/stotpudown"+histSubDir, histName, sf_stop, fout, fTT, "stop_stotpu"+hist_extn+"Down", true);
  //TH1F* stop_stotrelUp = DC.readWriteHisto(fST, baseDir+"/stotrelup"+histSubDir, histName, sf_stop, fout, fTT, "stop_stotrel"+hist_extn+"Up", true);
  //TH1F* stop_stotrelDown = DC.readWriteHisto(fST, baseDir+"/stotreldown"+histSubDir, histName, sf_stop, fout, fTT, "stop_stotrel"+hist_extn+"Down", true);
  //TH1F* stop_stotptUp = DC.readWriteHisto(fST, baseDir+"/stotptup"+histSubDir, histName, sf_stop, fout, fTT, "stop_stotpt"+hist_extn+"Up", true);
  //TH1F* stop_stotptDown = DC.readWriteHisto(fST, baseDir+"/stotptdown"+histSubDir, histName, sf_stop, fout, fTT, "stop_stotpt"+hist_extn+"Down", true);
  //TH1F* stop_stotscaleUp = DC.readWriteHisto(fST, baseDir+"/stotscaleup"+histSubDir, histName, sf_stop, fout, fTT, "stop_stotscale"+hist_extn+"Up", true);
  //TH1F* stop_stotscaleDown = DC.readWriteHisto(fST, baseDir+"/stotscaledown"+histSubDir, histName, sf_stop, fout, fTT, "stop_stotscale"+hist_extn+"Down", true);
  TH1F* stop_absmpfbUp = DC.readWriteHisto(fST, baseDir+"/absmpfbup"+histSubDir, histName, sf_stop, fout, fTT, "stop_absmpfb"+hist_extn+"Up", true);
  TH1F* stop_absmpfbDown = DC.readWriteHisto(fST, baseDir+"/absmpfbdown"+histSubDir, histName, sf_stop, fout, fTT, "stop_absmpfb"+hist_extn+"Down", true);
  TH1F* stop_abssclUp = DC.readWriteHisto(fST, baseDir+"/abssclup"+histSubDir, histName, sf_stop, fout, fTT, "stop_absscl"+hist_extn+"Up", true);
  TH1F* stop_abssclDown = DC.readWriteHisto(fST, baseDir+"/absscldown"+histSubDir, histName, sf_stop, fout, fTT, "stop_absscl"+hist_extn+"Down", true);
  TH1F* stop_absstatUp = DC.readWriteHisto(fST, baseDir+"/absstatup"+histSubDir, histName, sf_stop, fout, fTT, "stop_absstat"+uncorr_extn+"Up", true);
  TH1F* stop_absstatDown = DC.readWriteHisto(fST, baseDir+"/absstatdown"+histSubDir, histName, sf_stop, fout, fTT, "stop_absstat"+uncorr_extn+"Down", true);
  
  TH1F* stop_fragUp = DC.readWriteHisto(fST, baseDir+"/fragup"+histSubDir, histName, sf_stop, fout, fTT, "stop_frag"+hist_extn+"Up", true);
  TH1F* stop_fragDown = DC.readWriteHisto(fST, baseDir+"/fragdown"+histSubDir, histName, sf_stop, fout, fTT, "stop_frag"+hist_extn+"Down", true);
  TH1F* stop_pudatamcUp = DC.readWriteHisto(fST, baseDir+"/pudatamcup"+histSubDir, histName, sf_stop, fout, fTT, "stop_pudatamc"+hist_extn+"Up", true);
  TH1F* stop_pudatamcDown = DC.readWriteHisto(fST, baseDir+"/pudatamcdown"+histSubDir, histName, sf_stop, fout, fTT, "stop_pudatamc"+hist_extn+"Down", true);

  TH1F* stop_puptbbUp = DC.readWriteHisto(fST, baseDir+"/puptbbup"+histSubDir, histName, sf_stop, fout, fTT, "stop_puptbb"+hist_extn+"Up", true);
  TH1F* stop_puptbbDown = DC.readWriteHisto(fST, baseDir+"/puptbbdown"+histSubDir, histName, sf_stop, fout, fTT, "stop_puptbb"+hist_extn+"Down", true);
  TH1F* stop_puptec1Up = DC.readWriteHisto(fST, baseDir+"/puptec1up"+histSubDir, histName, sf_stop, fout, fTT, "stop_puptec1"+hist_extn+"Up", true);
  TH1F* stop_puptec1Down = DC.readWriteHisto(fST, baseDir+"/puptec1down"+histSubDir, histName, sf_stop, fout, fTT, "stop_puptec1"+hist_extn+"Down", true);

  TH1F* stop_puptec2Up = DC.readWriteHisto(fST, baseDir+"/puptec2up"+histSubDir, histName, sf_stop, fout, fTT, "stop_puptec2"+hist_extn+"Up", true);
  TH1F* stop_puptec2Down = DC.readWriteHisto(fST, baseDir+"/puptec2down"+histSubDir, histName, sf_stop, fout, fTT, "stop_puptec2"+hist_extn+"Down", true);
  TH1F* stop_pupthfUp = DC.readWriteHisto(fST, baseDir+"/pupthfup"+histSubDir, histName, sf_stop, fout, fTT, "stop_pupthf"+hist_extn+"Up", true);
  TH1F* stop_pupthfDown = DC.readWriteHisto(fST, baseDir+"/pupthfdown"+histSubDir, histName, sf_stop, fout, fTT, "stop_pupthf"+hist_extn+"Down", true);

  TH1F* stop_puptrefUp = DC.readWriteHisto(fST, baseDir+"/puptrefup"+histSubDir, histName, sf_stop, fout, fTT, "stop_puptref"+hist_extn+"Up", true);
  TH1F* stop_puptrefDown = DC.readWriteHisto(fST, baseDir+"/puptrefdown"+histSubDir, histName, sf_stop, fout, fTT, "stop_puptref"+hist_extn+"Down", true);
  TH1F* stop_relfsrUp = DC.readWriteHisto(fST, baseDir+"/relfsrup"+histSubDir, histName, sf_stop, fout, fTT, "stop_relfsr"+hist_extn+"Up", true);
  TH1F* stop_relfsrDown = DC.readWriteHisto(fST, baseDir+"/relfsrdown"+histSubDir, histName, sf_stop, fout, fTT, "stop_relfsr"+hist_extn+"Down", true);

  TH1F* stop_relbalUp = DC.readWriteHisto(fST, baseDir+"/relbalup"+histSubDir, histName, sf_stop, fout, fTT, "stop_relbal"+hist_extn+"Up", true);
  TH1F* stop_relbalDown = DC.readWriteHisto(fST, baseDir+"/relbaldown"+histSubDir, histName, sf_stop, fout, fTT, "stop_relbal"+hist_extn+"Down", true);
  TH1F* stop_relsampleUp = DC.readWriteHisto(fST, baseDir+"/relsampleup"+histSubDir, histName, sf_stop, fout, fTT, "stop_relsample"+uncorr_extn+"Up", true);
  TH1F* stop_relsampleDown = DC.readWriteHisto(fST, baseDir+"/relsampledown"+histSubDir, histName, sf_stop, fout, fTT, "stop_relsample"+uncorr_extn+"Down", true);

  TH1F* stop_reljerec1Up = DC.readWriteHisto(fST, baseDir+"/reljerec1up"+histSubDir, histName, sf_stop, fout, fTT, "stop_reljerec1"+uncorr_extn+"Up", true);
  TH1F* stop_reljerec1Down = DC.readWriteHisto(fST, baseDir+"/reljerec1down"+histSubDir, histName, sf_stop, fout, fTT, "stop_reljerec1"+uncorr_extn+"Down", true);
  TH1F* stop_reljerec2Up = DC.readWriteHisto(fST, baseDir+"/reljerec2up"+histSubDir, histName, sf_stop, fout, fTT, "stop_reljerec2"+uncorr_extn+"Up", true);
  TH1F* stop_reljerec2Down = DC.readWriteHisto(fST, baseDir+"/reljerec2down"+histSubDir, histName, sf_stop, fout, fTT, "stop_reljerec2"+uncorr_extn+"Down", true);

  TH1F* stop_reljerhfUp = DC.readWriteHisto(fST, baseDir+"/reljerhfup"+histSubDir, histName, sf_stop, fout, fTT, "stop_reljerhf"+hist_extn+"Up", true);
  TH1F* stop_reljerhfDown = DC.readWriteHisto(fST, baseDir+"/reljerhfdown"+histSubDir, histName, sf_stop, fout, fTT, "stop_reljerhf"+hist_extn+"Down", true);
  TH1F* stop_relptbbUp = DC.readWriteHisto(fST, baseDir+"/relptbbup"+histSubDir, histName, sf_stop, fout, fTT, "stop_relptbb"+hist_extn+"Up", true);
  TH1F* stop_relptbbDown = DC.readWriteHisto(fST, baseDir+"/relptbbdown"+histSubDir, histName, sf_stop, fout, fTT, "stop_relptbb"+hist_extn+"Down", true);

  TH1F* stop_relptec1Up = DC.readWriteHisto(fST, baseDir+"/relptec1up"+histSubDir, histName, sf_stop, fout, fTT, "stop_relptec1"+uncorr_extn+"Up", true);
  TH1F* stop_relptec1Down = DC.readWriteHisto(fST, baseDir+"/relptec1down"+histSubDir, histName, sf_stop, fout, fTT, "stop_relptec1"+uncorr_extn+"Down", true);
  TH1F* stop_relptec2Up = DC.readWriteHisto(fST, baseDir+"/relptec2up"+histSubDir, histName, sf_stop, fout, fTT, "stop_relptec2"+uncorr_extn+"Up", true);
  TH1F* stop_relptec2Down = DC.readWriteHisto(fST, baseDir+"/relptec2down"+histSubDir, histName, sf_stop, fout, fTT, "stop_relptec2"+uncorr_extn+"Down", true);

  TH1F* stop_relpthfUp = DC.readWriteHisto(fST, baseDir+"/relpthfup"+histSubDir, histName, sf_stop, fout, fTT, "stop_relpthf"+hist_extn+"Up", true);
  TH1F* stop_relpthfDown = DC.readWriteHisto(fST, baseDir+"/relpthfdown"+histSubDir, histName, sf_stop, fout, fTT, "stop_relpthf"+hist_extn+"Down", true);
  TH1F* stop_relstatecUp = DC.readWriteHisto(fST, baseDir+"/relstatecup"+histSubDir, histName, sf_stop, fout, fTT, "stop_relstatec"+uncorr_extn+"Up", true);
  TH1F* stop_relstatecDown = DC.readWriteHisto(fST, baseDir+"/relstatecdown"+histSubDir, histName, sf_stop, fout, fTT, "stop_relstatec"+uncorr_extn+"Down", true);

  TH1F* stop_relstatfsrUp = DC.readWriteHisto(fST, baseDir+"/relstatfsrup"+histSubDir, histName, sf_stop, fout, fTT, "stop_relstatfsr"+uncorr_extn+"Up", true);
  TH1F* stop_relstatfsrDown = DC.readWriteHisto(fST, baseDir+"/relstatfsrdown"+histSubDir, histName, sf_stop, fout, fTT, "stop_relstatfsr"+uncorr_extn+"Down", true);
  TH1F* stop_relstathfUp = DC.readWriteHisto(fST, baseDir+"/relstathfup"+histSubDir, histName, sf_stop, fout, fTT, "stop_relstathf"+uncorr_extn+"Up", true);
  TH1F* stop_relstathfDown = DC.readWriteHisto(fST, baseDir+"/relstathfdown"+histSubDir, histName, sf_stop, fout, fTT, "stop_relstathf"+uncorr_extn+"Down", true);

  TH1F* stop_singpiecalUp = DC.readWriteHisto(fST, baseDir+"/singpiecalup"+histSubDir, histName, sf_stop, fout, fTT, "stop_singpiecal"+hist_extn+"Up", true);
  TH1F* stop_singpiecalDown = DC.readWriteHisto(fST, baseDir+"/singpiecaldown"+histSubDir, histName, sf_stop, fout, fTT, "stop_singpiecal"+hist_extn+"Down", true);
  TH1F* stop_singpihcalUp = DC.readWriteHisto(fST, baseDir+"/singpihcalup"+histSubDir, histName, sf_stop, fout, fTT, "stop_singpihcal"+hist_extn+"Up", true);
  TH1F* stop_singpihcalDown = DC.readWriteHisto(fST, baseDir+"/singpihcaldown"+histSubDir, histName, sf_stop, fout, fTT, "stop_singpihcal"+hist_extn+"Down", true);

  TH1F* stop_flavorqcdUp = DC.readWriteHisto(fST, baseDir+"/flavorqcdup"+histSubDir, histName, sf_stop, fout, fTT, "stop_flavorqcd"+hist_extn+"Up", true);
  TH1F* stop_flavorqcdDown = DC.readWriteHisto(fST, baseDir+"/flavorqcddown"+histSubDir, histName, sf_stop, fout, fTT, "stop_flavorqcd"+hist_extn+"Down", true);
  TH1F* stop_timeptetaUp = DC.readWriteHisto(fST, baseDir+"/timeptetaup"+histSubDir, histName, sf_stop, fout, fTT, "stop_timepteta"+uncorr_extn+"Up", true);
  TH1F* stop_timeptetaDown = DC.readWriteHisto(fST, baseDir+"/timeptetadown"+histSubDir, histName, sf_stop, fout, fTT, "stop_timepteta"+uncorr_extn+"Down", true);
  TH1F* stop_PileupUp = DC.readWriteHisto(fST, baseDir+"/puup"+histSubDir, histName, sf_stop, fout, fTT, "stop_Pileup"+hist_extn+"Up", true);
  TH1F* stop_PileupDown = DC.readWriteHisto(fST, baseDir+"/pudown"+histSubDir, histName, sf_stop, fout, fTT, "stop_Pileup"+hist_extn+"Down", true);
  TH1F* stop_PrefireUp, *stop_PrefireDown;
  if(year==2016 or year==2017){
    stop_PrefireUp = DC.readWriteHisto(fST, baseDir+"/prefireup"+histSubDir, histName, sf_stop, fout, fTT, "stop_Prefire"+hist_extn+"Up", true);
    stop_PrefireDown = DC.readWriteHisto(fST, baseDir+"/prefiredown"+histSubDir, histName, sf_stop, fout, fTT, "stop_Prefire"+hist_extn+"Down", true);
  }else{
    stop_PrefireUp = DC.readWriteHisto(fST, baseDir+"/base"+histSubDir, histName, sf_stop, fout, fTT, "stop_Prefire"+hist_extn+"Up", true);
    stop_PrefireDown = DC.readWriteHisto(fST, baseDir+"/base"+histSubDir, histName, sf_stop, fout, fTT, "stop_Prefire"+hist_extn+"Down", true);
  }
  TH1F* stop_PUJetIDUp = DC.readWriteHisto(fST, baseDir+"/pujetidup"+histSubDir, histName, sf_stop, fout, fTT, "stop_PUJetID"+hist_extn+"Up", true);
  TH1F* stop_PUJetIDDown = DC.readWriteHisto(fST, baseDir+"/pujetiddown"+histSubDir, histName, sf_stop, fout, fTT, "stop_PUJetID"+hist_extn+"Down", true);
  TH1F* stop_JERUp = DC.readWriteHisto(fST, baseDir+"/jerup"+histSubDir, histName, sf_stop, fout, fTT, "stop_JER"+hist_extn+"Up", true);
  TH1F* stop_JERDown = DC.readWriteHisto(fST, baseDir+"/jerdown"+histSubDir, histName, sf_stop, fout, fTT, "stop_JER"+hist_extn+"Down", true);
  TH1F* stop_bcstatUp = DC.readWriteHisto(fST, baseDir+"/bcstatup"+histSubDir, histName, sf_stop, fout, fTT, "stop_bcstat"+hist_extn+"Up", true, isNormalized, stop);
  TH1F* stop_bcstatDown = DC.readWriteHisto(fST, baseDir+"/bcstatdown"+histSubDir, histName, sf_stop, fout, fTT, "stop_bcstat"+hist_extn+"Down", true, isNormalized, stop);
  TH1F *stop_bcintpUp, *stop_bcintpDown, *stop_bcextpUp, *stop_bcextpDown, *stop_bcxdybUp, *stop_bcxdybDown, *stop_bcxdycUp, *stop_bcxdycDown, *stop_bcxwjcUp, *stop_bcxwjcDown;

    stop_bcintpUp = DC.readWriteHisto(fST, baseDir+"/bcintpup"+histSubDir, histName, sf_stop, fout, fTT, "stop_bcintp"+hist_extn+"Up", true, isNormalized, stop);
    stop_bcintpDown = DC.readWriteHisto(fST, baseDir+"/bcintpdown"+histSubDir, histName, sf_stop, fout, fTT, "stop_bcintp"+hist_extn+"Down", true, isNormalized, stop);
    stop_bcextpUp = DC.readWriteHisto(fST, baseDir+"/bcextpup"+histSubDir, histName, sf_stop, fout, fTT, "stop_bcextp"+hist_extn+"Up", true, isNormalized, stop);
    stop_bcextpDown = DC.readWriteHisto(fST, baseDir+"/bcextpdown"+histSubDir, histName, sf_stop, fout, fTT, "stop_bcextp"+hist_extn+"Down", true, isNormalized, stop);
    stop_bcxdybUp = DC.readWriteHisto(fST, baseDir+"/bcxdybup"+histSubDir, histName, sf_stop, fout, fTT, "stop_bcxdyb"+hist_extn+"Up", true, isNormalized, stop);
    stop_bcxdybDown = DC.readWriteHisto(fST, baseDir+"/bcxdybdown"+histSubDir, histName, sf_stop, fout, fTT, "stop_bcxdyb"+hist_extn+"Down", true, isNormalized, stop);
    stop_bcxdycUp = DC.readWriteHisto(fST, baseDir+"/bcxdycup"+histSubDir, histName, sf_stop, fout, fTT, "stop_bcxdyc"+hist_extn+"Up", true, isNormalized, stop);
    stop_bcxdycDown = DC.readWriteHisto(fST, baseDir+"/bcxdycdown"+histSubDir, histName, sf_stop, fout, fTT, "stop_bcxdyc"+hist_extn+"Down", true, isNormalized, stop);
    stop_bcxwjcUp = DC.readWriteHisto(fST, baseDir+"/bcxwjcup"+histSubDir, histName, sf_stop, fout, fTT, "stop_bcxwjc"+hist_extn+"Up", true, isNormalized, stop);
    stop_bcxwjcDown = DC.readWriteHisto(fST, baseDir+"/bcxwjcdown"+histSubDir, histName, sf_stop, fout, fTT, "stop_bcxwjc"+hist_extn+"Down", true, isNormalized, stop);

  TH1F* stop_pdfUp = DC.readWriteHisto(fST, baseDir+"/pdfup"+histSubDir, histName, sf_stop, fout, fTT, "stop_pdf"+hist_extn+"Up", true);
  TH1F* stop_pdfDown = DC.readWriteHisto(fST, baseDir+"/pdfdown"+histSubDir, histName, sf_stop, fout, fTT, "stop_pdf"+hist_extn+"Down", true);
  // TH1F* stop_q2Up = DC.readWriteHisto(fST, baseDir+"/q2up"+histSubDir, histName, sf_stop, fout, fTT, "stop_q2"+hist_extn+"Up", true);
  // TH1F* stop_q2Down = DC.readWriteHisto(fST, baseDir+"/q2down"+histSubDir, histName, sf_stop, fout, fTT, "stop_q2"+hist_extn+"Down", true);
  TH1F* stop_bclhemufUp = DC.readWriteHisto(fST, baseDir+"/bclhemufup"+histSubDir, histName, sf_stop, fout, fTT, "stop_bclhemuf"+hist_extn+"Up", true, isNormalized, stop);
  TH1F* stop_bclhemufDown = DC.readWriteHisto(fST, baseDir+"/bclhemufdown"+histSubDir, histName, sf_stop, fout, fTT, "stop_bclhemuf"+hist_extn+"Down", true, isNormalized, stop);
  TH1F* stop_bclhemurUp = DC.readWriteHisto(fST, baseDir+"/bclhemurup"+histSubDir, histName, sf_stop, fout, fTT, "stop_bclhemur"+hist_extn+"Up", true, isNormalized, stop);
  TH1F* stop_bclhemurDown = DC.readWriteHisto(fST, baseDir+"/bclhemurdown"+histSubDir, histName, sf_stop, fout, fTT, "stop_bclhemur"+hist_extn+"Down", true, isNormalized, stop);
  TH1F* stop_isrUp = DC.readWriteHisto(fST, baseDir+"/isrup"+histSubDir, histName, sf_stop, fout, fTT, "stop_isr"+hist_extn+"Up", true, isNormalized, stop);
  TH1F* stop_isrDown = DC.readWriteHisto(fST, baseDir+"/isrdown"+histSubDir, histName, sf_stop, fout, fTT, "stop_isr"+hist_extn+"Down", true, isNormalized, stop);
  TH1F* stop_fsrUp = DC.readWriteHisto(fST, baseDir+"/fsrup"+histSubDir, histName, sf_stop, fout, fTT, "stop_fsr"+hist_extn+"Up", true, isNormalized, stop);
  TH1F* stop_fsrDown = DC.readWriteHisto(fST, baseDir+"/fsrdown"+histSubDir, histName, sf_stop, fout, fTT, "stop_fsr"+hist_extn+"Down", true, isNormalized, stop);
  // //MiniAOD nuisances
  // TH1F* stop_bcTag1Up = DC.readWriteHisto(fST, baseDir+"/bctag1up"+histSubDir, histName, sf_stop, fout, fTT, "stop_bcTag1"+hist_extn+"Up", true, isNormalized, stop);
  // TH1F* stop_bcTag1Down = DC.readWriteHisto(fST, baseDir+"/bctag1down"+histSubDir, histName, sf_stop, fout, fTT, "stop_bcTag1"+hist_extn+"Down", true, isNormalized, stop);
  // TH1F* stop_bcTag2Up = DC.readWriteHisto(fST, baseDir+"/bctag2up"+histSubDir, histName, sf_stop, fout, fTT, "stop_bcTag2"+hist_extn+"Up", true, isNormalized, stop);
  // TH1F* stop_bcTag2Down = DC.readWriteHisto(fST, baseDir+"/bctag2down"+histSubDir, histName, sf_stop, fout, fTT, "stop_bcTag2"+hist_extn+"Down", true, isNormalized, stop);
  // TH1F* stop_bcTag3Up = DC.readWriteHisto(fST, baseDir+"/bctag3up"+histSubDir, histName, sf_stop, fout, fTT, "stop_bcTag3"+hist_extn+"Up", true, isNormalized, stop);
  // TH1F* stop_bcTag3Down = DC.readWriteHisto(fST, baseDir+"/bctag3down"+histSubDir, histName, sf_stop, fout, fTT, "stop_bcTag3"+hist_extn+"Down", true, isNormalized, stop);
  // TH1F* stop_bTagbcUp = DC.readWriteHisto(fST, baseDir+"/btagbup"+histSubDir, histName, sf_stop, fout, fTT, "stop_bTagbc"+hist_extn+"Up", true, isNormalized, stop);
  // TH1F* stop_bTagbcDown = DC.readWriteHisto(fST, baseDir+"/btagbdown"+histSubDir, histName, sf_stop, fout, fTT, "stop_bTagbc"+hist_extn+"Down", true, isNormalized, stop);
  // TH1F* stop_bTaglUp = DC.readWriteHisto(fST, baseDir+"/btaglup"+histSubDir, histName, sf_stop, fout, fTT, "stop_bTagl"+hist_extn+"Up", true, isNormalized, stop);
  // TH1F* stop_bTaglDown = DC.readWriteHisto(fST, baseDir+"/btagldown"+histSubDir, histName, sf_stop, fout, fTT, "stop_bTagl"+hist_extn+"Down", true, isNormalized, stop);
  
  if(isBinStat){
    for(int ibin = 1; ibin <= nonStatBins ; ibin++){
      TH1F *stop_bin_stat_Up = DC.readWriteHisto(fST, baseDir+"/base"+histSubDir, histName, sf_stop, fout, fTT, Form("stop_CMS_stat_cat1_stop_bin_%dUp",ibin), true);
      TH1F *stop_bin_stat_Do = DC.readWriteHisto(fST, baseDir+"/base"+histSubDir, histName, sf_stop, fout, fTT, Form("stop_CMS_stat_cat1_stop_bin_%dDown",ibin), true);
    }
  }

  double unc_stop_ExL = 1.0;
  double unc_stop_ExM = 1.0;
  if(isExL){
    TH1F* stop_yLyMyT = DC.getHisto(fST, baseDir+"/Iso/ExCTag/", "sf_CTag_yLyMyT_wt", fTT);
    TH1F* stop_yLyMnT = DC.getHisto(fST, baseDir+"/Iso/ExCTag/", "sf_CTag_yLyMnT_wt", fTT);
    TH1F* stop_yLnMyT = DC.getHisto(fST, baseDir+"/Iso/ExCTag/", "sf_CTag_yLnMyT_wt", fTT);
    TH1F* stop_yLnMnT = DC.getHisto(fST, baseDir+"/Iso/ExCTag/", "sf_CTag_yLnMnT_wt", fTT);
    unc_stop_ExL = DC.getUncExL(stop_yLyMyT, stop_yLyMnT, stop_yLnMyT, stop_yLnMnT);
  }
  if(isExM){
    TH1F* stop_yMyT = DC.getHisto(fST, baseDir+"/Iso/ExCTag/", "sf_CTag_yMyT_wt", fTT);
    TH1F* stop_yMnT = DC.getHisto(fST, baseDir+"/Iso/ExCTag/", "sf_CTag_yMnT_wt", fTT);
    unc_stop_ExM = DC.getUncExM(stop_yMyT, stop_yMnT);
  }

  //Dibosons
  double sf_vv = 1;
  baseDir = "VBFusion";
  TH1F* vv = DC.readWriteHisto(fVV, baseDir+"/base"+histSubDir, histName, sf_vv, fout, fTT, "vv", true);
  TH1F *vv_LeptonUp,*vv_LeptonDown;
  if(isMuChannel){
    vv_LeptonUp = DC.readWriteHisto(fVV, baseDir+"/mueffup"+histSubDir, histName, sf_vv, fout, fTT, "vv_Lepton"+hist_extn+"Up", true);
    vv_LeptonDown = DC.readWriteHisto(fVV, baseDir+"/mueffdown"+histSubDir, histName, sf_vv, fout, fTT, "vv_Lepton"+hist_extn+"Down", true);
  }else{
    vv_LeptonUp = DC.readWriteHisto(fVV, baseDir+"/eleeffup"+histSubDir, histName, sf_vv, fout, fTT, "vv_Lepton"+hist_extn+"Up", true);
    vv_LeptonDown = DC.readWriteHisto(fVV, baseDir+"/eleeffdown"+histSubDir, histName, sf_vv, fout, fTT, "vv_Lepton"+hist_extn+"Down", true);
  }
  // TH1F* vv_JESUp = DC.readWriteHisto(fVV, baseDir+"/jecup"+histSubDir, histName, sf_vv, fout, fTT, "vv_JES"+hist_extn+"Up", true);
  // TH1F* vv_JESDown = DC.readWriteHisto(fVV, baseDir+"/jecdown"+histSubDir, histName, sf_vv, fout, fTT, "vv_JES"+hist_extn+"Down", true);
  //TH1F* vv_stotpuUp = DC.readWriteHisto(fVV, baseDir+"/stotpuup"+histSubDir, histName, sf_vv, fout, fTT, "vv_stotpu"+hist_extn+"Up", true);
  //TH1F* vv_stotpuDown = DC.readWriteHisto(fVV, baseDir+"/stotpudown"+histSubDir, histName, sf_vv, fout, fTT, "vv_stotpu"+hist_extn+"Down", true);
  //TH1F* vv_stotrelUp = DC.readWriteHisto(fVV, baseDir+"/stotrelup"+histSubDir, histName, sf_vv, fout, fTT, "vv_stotrel"+hist_extn+"Up", true);
  //TH1F* vv_stotrelDown = DC.readWriteHisto(fVV, baseDir+"/stotreldown"+histSubDir, histName, sf_vv, fout, fTT, "vv_stotrel"+hist_extn+"Down", true);
  //TH1F* vv_stotptUp = DC.readWriteHisto(fVV, baseDir+"/stotptup"+histSubDir, histName, sf_vv, fout, fTT, "vv_stotpt"+hist_extn+"Up", true);
  //TH1F* vv_stotptDown = DC.readWriteHisto(fVV, baseDir+"/stotptdown"+histSubDir, histName, sf_vv, fout, fTT, "vv_stotpt"+hist_extn+"Down", true);
  //TH1F* vv_stotscaleUp = DC.readWriteHisto(fVV, baseDir+"/stotscaleup"+histSubDir, histName, sf_vv, fout, fTT, "vv_stotscale"+hist_extn+"Up", true);
  //TH1F* vv_stotscaleDown = DC.readWriteHisto(fVV, baseDir+"/stotscaledown"+histSubDir, histName, sf_vv, fout, fTT, "vv_stotscale"+hist_extn+"Down", true);
  TH1F* vv_absmpfbUp = DC.readWriteHisto(fVV, baseDir+"/absmpfbup"+histSubDir, histName, sf_vv, fout, fTT, "vv_absmpfb"+hist_extn+"Up", true);
  TH1F* vv_absmpfbDown = DC.readWriteHisto(fVV, baseDir+"/absmpfbdown"+histSubDir, histName, sf_vv, fout, fTT, "vv_absmpfb"+hist_extn+"Down", true);
  TH1F* vv_abssclUp = DC.readWriteHisto(fVV, baseDir+"/abssclup"+histSubDir, histName, sf_vv, fout, fTT, "vv_absscl"+hist_extn+"Up", true);
  TH1F* vv_abssclDown = DC.readWriteHisto(fVV, baseDir+"/absscldown"+histSubDir, histName, sf_vv, fout, fTT, "vv_absscl"+hist_extn+"Down", true);
  TH1F* vv_absstatUp = DC.readWriteHisto(fVV, baseDir+"/absstatup"+histSubDir, histName, sf_vv, fout, fTT, "vv_absstat"+uncorr_extn+"Up", true);
  TH1F* vv_absstatDown = DC.readWriteHisto(fVV, baseDir+"/absstatdown"+histSubDir, histName, sf_vv, fout, fTT, "vv_absstat"+uncorr_extn+"Down", true);
  
  TH1F* vv_fragUp = DC.readWriteHisto(fVV, baseDir+"/fragup"+histSubDir, histName, sf_vv, fout, fTT, "vv_frag"+hist_extn+"Up", true);
  TH1F* vv_fragDown = DC.readWriteHisto(fVV, baseDir+"/fragdown"+histSubDir, histName, sf_vv, fout, fTT, "vv_frag"+hist_extn+"Down", true);
  TH1F* vv_pudatamcUp = DC.readWriteHisto(fVV, baseDir+"/pudatamcup"+histSubDir, histName, sf_vv, fout, fTT, "vv_pudatamc"+hist_extn+"Up", true);
  TH1F* vv_pudatamcDown = DC.readWriteHisto(fVV, baseDir+"/pudatamcdown"+histSubDir, histName, sf_vv, fout, fTT, "vv_pudatamc"+hist_extn+"Down", true);

  TH1F* vv_puptbbUp = DC.readWriteHisto(fVV, baseDir+"/puptbbup"+histSubDir, histName, sf_vv, fout, fTT, "vv_puptbb"+hist_extn+"Up", true);
  TH1F* vv_puptbbDown = DC.readWriteHisto(fVV, baseDir+"/puptbbdown"+histSubDir, histName, sf_vv, fout, fTT, "vv_puptbb"+hist_extn+"Down", true);
  TH1F* vv_puptec1Up = DC.readWriteHisto(fVV, baseDir+"/puptec1up"+histSubDir, histName, sf_vv, fout, fTT, "vv_puptec1"+hist_extn+"Up", true);
  TH1F* vv_puptec1Down = DC.readWriteHisto(fVV, baseDir+"/puptec1down"+histSubDir, histName, sf_vv, fout, fTT, "vv_puptec1"+hist_extn+"Down", true);

  TH1F* vv_puptec2Up = DC.readWriteHisto(fVV, baseDir+"/puptec2up"+histSubDir, histName, sf_vv, fout, fTT, "vv_puptec2"+hist_extn+"Up", true);
  TH1F* vv_puptec2Down = DC.readWriteHisto(fVV, baseDir+"/puptec2down"+histSubDir, histName, sf_vv, fout, fTT, "vv_puptec2"+hist_extn+"Down", true);
  TH1F* vv_pupthfUp = DC.readWriteHisto(fVV, baseDir+"/pupthfup"+histSubDir, histName, sf_vv, fout, fTT, "vv_pupthf"+hist_extn+"Up", true);
  TH1F* vv_pupthfDown = DC.readWriteHisto(fVV, baseDir+"/pupthfdown"+histSubDir, histName, sf_vv, fout, fTT, "vv_pupthf"+hist_extn+"Down", true);

  TH1F* vv_puptrefUp = DC.readWriteHisto(fVV, baseDir+"/puptrefup"+histSubDir, histName, sf_vv, fout, fTT, "vv_puptref"+hist_extn+"Up", true);
  TH1F* vv_puptrefDown = DC.readWriteHisto(fVV, baseDir+"/puptrefdown"+histSubDir, histName, sf_vv, fout, fTT, "vv_puptref"+hist_extn+"Down", true);
  TH1F* vv_relfsrUp = DC.readWriteHisto(fVV, baseDir+"/relfsrup"+histSubDir, histName, sf_vv, fout, fTT, "vv_relfsr"+hist_extn+"Up", true);
  TH1F* vv_relfsrDown = DC.readWriteHisto(fVV, baseDir+"/relfsrdown"+histSubDir, histName, sf_vv, fout, fTT, "vv_relfsr"+hist_extn+"Down", true);

  TH1F* vv_relbalUp = DC.readWriteHisto(fVV, baseDir+"/relbalup"+histSubDir, histName, sf_vv, fout, fTT, "vv_relbal"+hist_extn+"Up", true);
  TH1F* vv_relbalDown = DC.readWriteHisto(fVV, baseDir+"/relbaldown"+histSubDir, histName, sf_vv, fout, fTT, "vv_relbal"+hist_extn+"Down", true);
  TH1F* vv_relsampleUp = DC.readWriteHisto(fVV, baseDir+"/relsampleup"+histSubDir, histName, sf_vv, fout, fTT, "vv_relsample"+uncorr_extn+"Up", true);
  TH1F* vv_relsampleDown = DC.readWriteHisto(fVV, baseDir+"/relsampledown"+histSubDir, histName, sf_vv, fout, fTT, "vv_relsample"+uncorr_extn+"Down", true);

  TH1F* vv_reljerec1Up = DC.readWriteHisto(fVV, baseDir+"/reljerec1up"+histSubDir, histName, sf_vv, fout, fTT, "vv_reljerec1"+uncorr_extn+"Up", true);
  TH1F* vv_reljerec1Down = DC.readWriteHisto(fVV, baseDir+"/reljerec1down"+histSubDir, histName, sf_vv, fout, fTT, "vv_reljerec1"+uncorr_extn+"Down", true);
  TH1F* vv_reljerec2Up = DC.readWriteHisto(fVV, baseDir+"/reljerec2up"+histSubDir, histName, sf_vv, fout, fTT, "vv_reljerec2"+uncorr_extn+"Up", true);
  TH1F* vv_reljerec2Down = DC.readWriteHisto(fVV, baseDir+"/reljerec2down"+histSubDir, histName, sf_vv, fout, fTT, "vv_reljerec2"+uncorr_extn+"Down", true);

  TH1F* vv_reljerhfUp = DC.readWriteHisto(fVV, baseDir+"/reljerhfup"+histSubDir, histName, sf_vv, fout, fTT, "vv_reljerhf"+hist_extn+"Up", true);
  TH1F* vv_reljerhfDown = DC.readWriteHisto(fVV, baseDir+"/reljerhfdown"+histSubDir, histName, sf_vv, fout, fTT, "vv_reljerhf"+hist_extn+"Down", true);
  TH1F* vv_relptbbUp = DC.readWriteHisto(fVV, baseDir+"/relptbbup"+histSubDir, histName, sf_vv, fout, fTT, "vv_relptbb"+hist_extn+"Up", true);
  TH1F* vv_relptbbDown = DC.readWriteHisto(fVV, baseDir+"/relptbbdown"+histSubDir, histName, sf_vv, fout, fTT, "vv_relptbb"+hist_extn+"Down", true);

  TH1F* vv_relptec1Up = DC.readWriteHisto(fVV, baseDir+"/relptec1up"+histSubDir, histName, sf_vv, fout, fTT, "vv_relptec1"+uncorr_extn+"Up", true);
  TH1F* vv_relptec1Down = DC.readWriteHisto(fVV, baseDir+"/relptec1down"+histSubDir, histName, sf_vv, fout, fTT, "vv_relptec1"+uncorr_extn+"Down", true);
  TH1F* vv_relptec2Up = DC.readWriteHisto(fVV, baseDir+"/relptec2up"+histSubDir, histName, sf_vv, fout, fTT, "vv_relptec2"+uncorr_extn+"Up", true);
  TH1F* vv_relptec2Down = DC.readWriteHisto(fVV, baseDir+"/relptec2down"+histSubDir, histName, sf_vv, fout, fTT, "vv_relptec2"+uncorr_extn+"Down", true);

  TH1F* vv_relpthfUp = DC.readWriteHisto(fVV, baseDir+"/relpthfup"+histSubDir, histName, sf_vv, fout, fTT, "vv_relpthf"+hist_extn+"Up", true);
  TH1F* vv_relpthfDown = DC.readWriteHisto(fVV, baseDir+"/relpthfdown"+histSubDir, histName, sf_vv, fout, fTT, "vv_relpthf"+hist_extn+"Down", true);
  TH1F* vv_relstatecUp = DC.readWriteHisto(fVV, baseDir+"/relstatecup"+histSubDir, histName, sf_vv, fout, fTT, "vv_relstatec"+uncorr_extn+"Up", true);
  TH1F* vv_relstatecDown = DC.readWriteHisto(fVV, baseDir+"/relstatecdown"+histSubDir, histName, sf_vv, fout, fTT, "vv_relstatec"+uncorr_extn+"Down", true);

  TH1F* vv_relstatfsrUp = DC.readWriteHisto(fVV, baseDir+"/relstatfsrup"+histSubDir, histName, sf_vv, fout, fTT, "vv_relstatfsr"+uncorr_extn+"Up", true);
  TH1F* vv_relstatfsrDown = DC.readWriteHisto(fVV, baseDir+"/relstatfsrdown"+histSubDir, histName, sf_vv, fout, fTT, "vv_relstatfsr"+uncorr_extn+"Down", true);
  TH1F* vv_relstathfUp = DC.readWriteHisto(fVV, baseDir+"/relstathfup"+histSubDir, histName, sf_vv, fout, fTT, "vv_relstathf"+uncorr_extn+"Up", true);
  TH1F* vv_relstathfDown = DC.readWriteHisto(fVV, baseDir+"/relstathfdown"+histSubDir, histName, sf_vv, fout, fTT, "vv_relstathf"+uncorr_extn+"Down", true);

  TH1F* vv_singpiecalUp = DC.readWriteHisto(fVV, baseDir+"/singpiecalup"+histSubDir, histName, sf_vv, fout, fTT, "vv_singpiecal"+hist_extn+"Up", true);
  TH1F* vv_singpiecalDown = DC.readWriteHisto(fVV, baseDir+"/singpiecaldown"+histSubDir, histName, sf_vv, fout, fTT, "vv_singpiecal"+hist_extn+"Down", true);
  TH1F* vv_singpihcalUp = DC.readWriteHisto(fVV, baseDir+"/singpihcalup"+histSubDir, histName, sf_vv, fout, fTT, "vv_singpihcal"+hist_extn+"Up", true);
  TH1F* vv_singpihcalDown = DC.readWriteHisto(fVV, baseDir+"/singpihcaldown"+histSubDir, histName, sf_vv, fout, fTT, "vv_singpihcal"+hist_extn+"Down", true);

  TH1F* vv_flavorqcdUp = DC.readWriteHisto(fVV, baseDir+"/flavorqcdup"+histSubDir, histName, sf_vv, fout, fTT, "vv_flavorqcd"+hist_extn+"Up", true);
  TH1F* vv_flavorqcdDown = DC.readWriteHisto(fVV, baseDir+"/flavorqcddown"+histSubDir, histName, sf_vv, fout, fTT, "vv_flavorqcd"+hist_extn+"Down", true);
  TH1F* vv_timeptetaUp = DC.readWriteHisto(fVV, baseDir+"/timeptetaup"+histSubDir, histName, sf_vv, fout, fTT, "vv_timepteta"+uncorr_extn+"Up", true);
  TH1F* vv_timeptetaDown = DC.readWriteHisto(fVV, baseDir+"/timeptetadown"+histSubDir, histName, sf_vv, fout, fTT, "vv_timepteta"+uncorr_extn+"Down", true);
  TH1F* vv_PileupUp = DC.readWriteHisto(fVV, baseDir+"/puup"+histSubDir, histName, sf_vv, fout, fTT, "vv_Pileup"+hist_extn+"Up", true);
  TH1F* vv_PileupDown = DC.readWriteHisto(fVV, baseDir+"/pudown"+histSubDir, histName, sf_vv, fout, fTT, "vv_Pileup"+hist_extn+"Down", true);
  TH1F* vv_PrefireUp, *vv_PrefireDown;
  if(year==2016 or year==2017){
    vv_PrefireUp = DC.readWriteHisto(fVV, baseDir+"/prefireup"+histSubDir, histName, sf_vv, fout, fTT, "vv_Prefire"+hist_extn+"Up", true);
    vv_PrefireDown = DC.readWriteHisto(fVV, baseDir+"/prefiredown"+histSubDir, histName, sf_vv, fout, fTT, "vv_Prefire"+hist_extn+"Down", true);
  }else{
    vv_PrefireUp = DC.readWriteHisto(fVV, baseDir+"/base"+histSubDir, histName, sf_vv, fout, fTT, "vv_Prefire"+hist_extn+"Up", true);
    vv_PrefireDown = DC.readWriteHisto(fVV, baseDir+"/base"+histSubDir, histName, sf_vv, fout, fTT, "vv_Prefire"+hist_extn+"Down", true);
  }
  TH1F* vv_PUJetIDUp = DC.readWriteHisto(fVV, baseDir+"/pujetidup"+histSubDir, histName, sf_vv, fout, fTT, "vv_PUJetID"+hist_extn+"Up", true);
  TH1F* vv_PUJetIDDown = DC.readWriteHisto(fVV, baseDir+"/pujetiddown"+histSubDir, histName, sf_vv, fout, fTT, "vv_PUJetID"+hist_extn+"Down", true);
  TH1F* vv_JERUp = DC.readWriteHisto(fVV, baseDir+"/jerup"+histSubDir, histName, sf_vv, fout, fTT, "vv_JER"+hist_extn+"Up", true);
  TH1F* vv_JERDown = DC.readWriteHisto(fVV, baseDir+"/jerdown"+histSubDir, histName, sf_vv, fout, fTT, "vv_JER"+hist_extn+"Down", true);
  TH1F* vv_bcstatUp = DC.readWriteHisto(fVV, baseDir+"/bcstatup"+histSubDir, histName, sf_vv, fout, fTT, "vv_bcstat"+hist_extn+"Up", true, isNormalized, vv);
  TH1F* vv_bcstatDown = DC.readWriteHisto(fVV, baseDir+"/bcstatdown"+histSubDir, histName, sf_vv, fout, fTT, "vv_bcstat"+hist_extn+"Down", true, isNormalized, vv);
  TH1F *vv_bcintpUp, *vv_bcintpDown, *vv_bcextpUp, *vv_bcextpDown, *vv_bcxdybUp, *vv_bcxdybDown, *vv_bcxdycUp, *vv_bcxdycDown, *vv_bcxwjcUp, *vv_bcxwjcDown;

  vv_bcintpUp = DC.readWriteHisto(fVV, baseDir+"/bcintpup"+histSubDir, histName, sf_vv, fout, fTT, "vv_bcintp"+hist_extn+"Up", true, isNormalized, vv);
  vv_bcintpDown = DC.readWriteHisto(fVV, baseDir+"/bcintpdown"+histSubDir, histName, sf_vv, fout, fTT, "vv_bcintp"+hist_extn+"Down", true, isNormalized, vv);
  vv_bcextpUp = DC.readWriteHisto(fVV, baseDir+"/bcextpup"+histSubDir, histName, sf_vv, fout, fTT, "vv_bcextp"+hist_extn+"Up", true, isNormalized, vv);
  vv_bcextpDown = DC.readWriteHisto(fVV, baseDir+"/bcextpdown"+histSubDir, histName, sf_vv, fout, fTT, "vv_bcextp"+hist_extn+"Down", true, isNormalized, vv);
  vv_bcxdybUp = DC.readWriteHisto(fVV, baseDir+"/bcxdybup"+histSubDir, histName, sf_vv, fout, fTT, "vv_bcxdyb"+hist_extn+"Up", true, isNormalized, vv);
  vv_bcxdybDown = DC.readWriteHisto(fVV, baseDir+"/bcxdybdown"+histSubDir, histName, sf_vv, fout, fTT, "vv_bcxdyb"+hist_extn+"Down", true, isNormalized, vv);
  vv_bcxdycUp = DC.readWriteHisto(fVV, baseDir+"/bcxdycup"+histSubDir, histName, sf_vv, fout, fTT, "vv_bcxdyc"+hist_extn+"Up", true, isNormalized, vv);
  vv_bcxdycDown = DC.readWriteHisto(fVV, baseDir+"/bcxdycdown"+histSubDir, histName, sf_vv, fout, fTT, "vv_bcxdyc"+hist_extn+"Down", true, isNormalized, vv);
  vv_bcxwjcUp = DC.readWriteHisto(fVV, baseDir+"/bcxwjcup"+histSubDir, histName, sf_vv, fout, fTT, "vv_bcxwjc"+hist_extn+"Up", true, isNormalized, vv);
  vv_bcxwjcDown = DC.readWriteHisto(fVV, baseDir+"/bcxwjcdown"+histSubDir, histName, sf_vv, fout, fTT, "vv_bcxwjc"+hist_extn+"Down", true, isNormalized, vv);

  TH1F* vv_pdfUp = DC.readWriteHisto(fVV, baseDir+"/pdfup"+histSubDir, histName, sf_vv, fout, fTT, "vv_pdf"+hist_extn+"Up", true);
  TH1F* vv_pdfDown = DC.readWriteHisto(fVV, baseDir+"/pdfdown"+histSubDir, histName, sf_vv, fout, fTT, "vv_pdf"+hist_extn+"Down", true);
  // TH1F* vv_q2Up = DC.readWriteHisto(fVV, baseDir+"/q2up"+histSubDir, histName, sf_vv, fout, fTT, "vv_q2"+hist_extn+"Up", true);
  // TH1F* vv_q2Down = DC.readWriteHisto(fVV, baseDir+"/q2down"+histSubDir, histName, sf_vv, fout, fTT, "vv_q2"+hist_extn+"Down", true);
  TH1F* vv_bclhemufUp = DC.readWriteHisto(fVV, baseDir+"/bclhemufup"+histSubDir, histName, sf_vv, fout, fTT, "vv_bclhemuf"+hist_extn+"Up", true, isNormalized, vv);
  TH1F* vv_bclhemufDown = DC.readWriteHisto(fVV, baseDir+"/bclhemufdown"+histSubDir, histName, sf_vv, fout, fTT, "vv_bclhemuf"+hist_extn+"Down", true, isNormalized, vv);
  TH1F* vv_bclhemurUp = DC.readWriteHisto(fVV, baseDir+"/bclhemurup"+histSubDir, histName, sf_vv, fout, fTT, "vv_bclhemur"+hist_extn+"Up", true, isNormalized, vv);
  TH1F* vv_bclhemurDown = DC.readWriteHisto(fVV, baseDir+"/bclhemurdown"+histSubDir, histName, sf_vv, fout, fTT, "vv_bclhemur"+hist_extn+"Down", true, isNormalized, vv);
  TH1F* vv_isrUp = DC.readWriteHisto(fVV, baseDir+"/isrup"+histSubDir, histName, sf_vv, fout, fTT, "vv_isr"+hist_extn+"Up", true, isNormalized, vv);
  TH1F* vv_isrDown = DC.readWriteHisto(fVV, baseDir+"/isrdown"+histSubDir, histName, sf_vv, fout, fTT, "vv_isr"+hist_extn+"Down", true, isNormalized, vv);
  TH1F* vv_fsrUp = DC.readWriteHisto(fVV, baseDir+"/fsrup"+histSubDir, histName, sf_vv, fout, fTT, "vv_fsr"+hist_extn+"Up", true, isNormalized, vv);
  TH1F* vv_fsrDown = DC.readWriteHisto(fVV, baseDir+"/fsrdown"+histSubDir, histName, sf_vv, fout, fTT, "vv_fsr"+hist_extn+"Down", true, isNormalized, vv);
  // //MiniAOD nuisances
  // TH1F* vv_bcTag1Up = DC.readWriteHisto(fVV, baseDir+"/bctag1up"+histSubDir, histName, sf_vv, fout, fTT, "vv_bcTag1"+hist_extn+"Up", true, isNormalized, vv);
  // TH1F* vv_bcTag1Down = DC.readWriteHisto(fVV, baseDir+"/bctag1down"+histSubDir, histName, sf_vv, fout, fTT, "vv_bcTag1"+hist_extn+"Down", true, isNormalized, vv);
  // TH1F* vv_bcTag2Up = DC.readWriteHisto(fVV, baseDir+"/bctag2up"+histSubDir, histName, sf_vv, fout, fTT, "vv_bcTag2"+hist_extn+"Up", true, isNormalized, vv);
  // TH1F* vv_bcTag2Down = DC.readWriteHisto(fVV, baseDir+"/bctag2down"+histSubDir, histName, sf_vv, fout, fTT, "vv_bcTag2"+hist_extn+"Down", true, isNormalized, vv);
  // TH1F* vv_bcTag3Up = DC.readWriteHisto(fVV, baseDir+"/bctag3up"+histSubDir, histName, sf_vv, fout, fTT, "vv_bcTag3"+hist_extn+"Up", true, isNormalized, vv);
  // TH1F* vv_bcTag3Down = DC.readWriteHisto(fVV, baseDir+"/bctag3down"+histSubDir, histName, sf_vv, fout, fTT, "vv_bcTag3"+hist_extn+"Down", true, isNormalized, vv);
  // TH1F* vv_bTagbcUp = DC.readWriteHisto(fVV, baseDir+"/btagbup"+histSubDir, histName, sf_vv, fout, fTT, "vv_bTagbc"+hist_extn+"Up", true, isNormalized, vv);
  // TH1F* vv_bTagbcDown = DC.readWriteHisto(fVV, baseDir+"/btagbdown"+histSubDir, histName, sf_vv, fout, fTT, "vv_bTagbc"+hist_extn+"Down", true, isNormalized, vv);
  // TH1F* vv_bTaglUp = DC.readWriteHisto(fVV, baseDir+"/btaglup"+histSubDir, histName, sf_vv, fout, fTT, "vv_bTagl"+hist_extn+"Up", true, isNormalized, vv);
  // TH1F* vv_bTaglDown = DC.readWriteHisto(fVV, baseDir+"/btagldown"+histSubDir, histName, sf_vv, fout, fTT, "vv_bTagl"+hist_extn+"Down", true, isNormalized, vv);

  if(isBinStat){
    for(int ibin = 1; ibin <= nonStatBins ; ibin++){
      TH1F *vv_bin_stat_Up = DC.readWriteHisto(fVV, baseDir+"/base"+histSubDir, histName, sf_vv, fout, fTT, Form("vv_CMS_stat_cat1_vv_bin_%dUp",ibin), true);
      TH1F *vv_bin_stat_Do = DC.readWriteHisto(fVV, baseDir+"/base"+histSubDir, histName, sf_vv, fout, fTT, Form("vv_CMS_stat_cat1_vv_bin_%dDown",ibin), true);
    }
  }
  double unc_vv_ExL = 1.0;
  double unc_vv_ExM = 1.0;
  if(isExL){
    TH1F* vv_yLyMyT = DC.getHisto(fVV, baseDir+"/Iso/ExCTag/", "sf_CTag_yLyMyT_wt", fTT);
    TH1F* vv_yLyMnT = DC.getHisto(fVV, baseDir+"/Iso/ExCTag/", "sf_CTag_yLyMnT_wt", fTT);
    TH1F* vv_yLnMyT = DC.getHisto(fVV, baseDir+"/Iso/ExCTag/", "sf_CTag_yLnMyT_wt", fTT);
    TH1F* vv_yLnMnT = DC.getHisto(fVV, baseDir+"/Iso/ExCTag/", "sf_CTag_yLnMnT_wt", fTT);
    unc_vv_ExL = DC.getUncExL(vv_yLyMyT, vv_yLyMnT, vv_yLnMyT, vv_yLnMnT);
  }
  if(isExM){
    TH1F* vv_yMyT = DC.getHisto(fVV, baseDir+"/Iso/ExCTag/", "sf_CTag_yMyT_wt", fTT);
    TH1F* vv_yMnT = DC.getHisto(fVV, baseDir+"/Iso/ExCTag/", "sf_CTag_yMnT_wt", fTT);
    unc_vv_ExM = DC.getUncExM(vv_yMyT, vv_yMnT);
  }
  
  //QCD MC
  double sf_qcd = 1.0;
  /*
  TH1F* qcd = DC.readWriteHisto(fQCD, baseDir+"/base"+histSubDir, histName, sf_qcd, fout, fTT, "qcd", true);
  TH1F* qcd_JESUp = DC.readWriteHisto(fQCD, baseDir+"/jecup"+histSubDir, histName, sf_qcd, fout, fTT, "qcd_JESUp", true);
  TH1F* qcd_JESDown = DC.readWriteHisto(fQCD, baseDir+"/jecdown"+histSubDir, histName, sf_qcd, fout, fTT, "qcd_JESDown", true);
  TH1F* qcd_PileupUp = DC.readWriteHisto(fQCD, baseDir+"/puup"+histSubDir, histName, sf_qcd, fout, fTT, "qcd_PileupUp", true);
  TH1F* qcd_PileupDown = DC.readWriteHisto(fQCD, baseDir+"/pudown"+histSubDir, histName, sf_qcd, fout, fTT, "qcd_PileupDown", true);
  TH1F* qcd_JERUp = DC.readWriteHisto(fQCD, baseDir+"/jerup"+histSubDir, histName, sf_qcd, fout, fTT, "qcd_JERUp", true);
  TH1F* qcd_JERDown = DC.readWriteHisto(fQCD, baseDir+"/jerdown"+histSubDir, histName, sf_qcd, fout, fTT, "qcd_JERDown", true);
  //TH1F* qcd_bcTag1Up = DC.readWriteHisto(fQCD, baseDir+"/bctag1up"+histSubDir, histName, sf_qcd, fout, fTT, "qcd_bcTag1Up", true);
  //TH1F* qcd_bcTag1Down = DC.readWriteHisto(fQCD, baseDir+"/bctag1down"+histSubDir, histName, sf_qcd, fout, fTT, "qcd_bcTag1Down", true);
  //TH1F* qcd_bcTag2Up = DC.readWriteHisto(fQCD, baseDir+"/bctag2up"+histSubDir, histName, sf_qcd, fout, fTT, "qcd_bcTag2Up", true);
  //TH1F* qcd_bcTag2Down = DC.readWriteHisto(fQCD, baseDir+"/bctag2down"+histSubDir, histName, sf_qcd, fout, fTT, "qcd_bcTag2Down", true);
  //TH1F* qcd_bcTag3Up = DC.readWriteHisto(fQCD, baseDir+"/bctag3up"+histSubDir, histName, sf_qcd, fout, fTT, "qcd_bcTag3Up", true);
  //TH1F* qcd_bcTag3Down = DC.readWriteHisto(fQCD, baseDir+"/bctag3down"+histSubDir, histName, sf_qcd, fout, fTT, "qcd_bcTag3Down", true);
  */
  //QCD data driven
  //cout<<baseDir+"/base"+histSubDir+"/"+histName<<endl;
  baseDir = "QCDdd";
  TH1F* qcd_dd_raw = DC.readWriteHisto(fQCD_dd, baseDir+"/base"+histSubDir, histName, sf_qcd, fout, fTT, "qcd_base", false);
  //TH1F* qcd_dd = DC.readWriteHisto(fQCD_dd, baseDir+"/base"+histSubDir, histName, sf_qcd, fout, fTT, "qcd", true, true, 0x0);
  TH1F* qcd_dd = DC.readWriteHisto(fQCD_dd, baseDir+"/base"+histSubDir, histName, sf_qcd, fout, fTT, "qcd", true);
  double QCD_DD_Integral = qcd_dd_raw->Integral();
  double stat_unc_qcd = DC.getStatUnc(qcd_dd, 0);
  // cout<<"qcd stat unc: "<<stat_unc_qcd<<endl;
  // cout<<"qcd = "<<qcd_dd->Integral()<<endl;
  //double qcd_unc = DC.getSysUncQcd(fData, fTT, fST, fWJ, fDY,  fVV, histSubDir_+"/", histName, false);
  cout << "histname : "<<histName << ", histSubDir : " << histSubDir << endl;
  TH1D* qcd_dd_error = (TH1D *)fQCD_dd->Get(Form("%s/syst%s%s",baseDir.Data(),histSubDir.Data(), histName.Data()));
  cout << "histname : "<<qcd_dd_error->GetName() << ", content : " << qcd_dd_error->GetBinContent(1) << ", Error : " << qcd_dd_error->GetBinError(1) << endl;
  //double qcd_unc = DC.getSysUncQcdNano(isMuChannel, fData, fTT, fST, fWJ, fDY,  fVV, histSubDir_+"/", histName, false);
  double qcd_unc = 1 + qcd_dd_error->GetBinError(1)/100.0;
  if(isBinStat){
    for(int ibin = 1; ibin <= nonStatBins ; ibin++){
      TH1F *qcd_bin_stat_Up = DC.readWriteHisto(fQCD_dd, baseDir+"/base"+histSubDir, histName, sf_qcd, fout, fTT, Form("qcd_CMS_stat_cat1_qcd_bin_%dUp",ibin), true);
      TH1F *qcd_bin_stat_Do = DC.readWriteHisto(fQCD_dd, baseDir+"/base"+histSubDir, histName, sf_qcd, fout, fTT, Form("qcd_CMS_stat_cat1_qcd_bin_%dDown",ibin), true);
    }
  }
  cout <<"QCD uncertainty : " << qcd_unc << endl;
  
  //Data
  double sf_data = 1.0; //should be 1, always
  baseDir = (isMuChannel) ? "DataMu" : "DataEle";
  TH1F* data_obs = DC.readWriteHisto(fData, baseDir+"/base"+histSubDir, histName, sf_data, fout, fTT, "data_obs", true);
  //TH1F* data_obs = DC.readWriteHisto(fTT, "TTbar/base"+histSubDir, histName, sf_data, fout, fTT, "data_obs", true);
  //cout<<":data_obs ================: "<<data_obs->Integral()<<endl;
  
  //wh
  // double sf_wh = 1.0;
  // baseDir = Form("HplusM%03d",mass);
  double sf_wh = 1.0/2.0;
  //double sf_wh = 1.0/(2.0*0.32);
  baseDir = Form("HplmiM%03d",mass);
  TH1F* wh = DC.readWriteHisto(fWH, baseDir+"/base"+histSubDir, histName, sf_wh, fout, fTT, label, true);
  TH1F *wh_LeptonUp,*wh_LeptonDown;
  if(isMuChannel){
    wh_LeptonUp = DC.readWriteHisto(fWH, baseDir+"/mueffup"+histSubDir, histName, sf_wh, fout, fTT, label+"_Lepton"+hist_extn.data()+"Up", true);
    wh_LeptonDown = DC.readWriteHisto(fWH, baseDir+"/mueffdown"+histSubDir, histName, sf_wh, fout, fTT, label+"_Lepton"+hist_extn.data()+"Down", true);
  }else{
    wh_LeptonUp = DC.readWriteHisto(fWH, baseDir+"/eleeffup"+histSubDir, histName, sf_wh, fout, fTT, label+"_Lepton"+hist_extn.data()+"Up", true);
    wh_LeptonDown = DC.readWriteHisto(fWH, baseDir+"/eleeffdown"+histSubDir, histName, sf_wh, fout, fTT, label+"_Lepton"+hist_extn.data()+"Down", true);
  }
  // TH1F* wh_JESUp = DC.readWriteHisto(fWH, baseDir+"/jecup"+histSubDir, histName, sf_wh, fout, fTT, label+"_JES"+hist_extn.data()+"Up", true);
  // TH1F* wh_JESDown = DC.readWriteHisto(fWH, baseDir+"/jecdown"+histSubDir, histName, sf_wh, fout, fTT, label+"_JES"+hist_extn.data()+"Down", true);
  //TH1F* wh_stotpuUp = DC.readWriteHisto(fWH, baseDir+"/stotpuup"+histSubDir, histName, sf_wh, fout, fTT, label+"_stotpu"+hist_extn.data()+"Up", true);
  //TH1F* wh_stotpuDown = DC.readWriteHisto(fWH, baseDir+"/stotpudown"+histSubDir, histName, sf_wh, fout, fTT, label+"_stotpu"+hist_extn.data()+"Down", true);
  //TH1F* wh_stotrelUp = DC.readWriteHisto(fWH, baseDir+"/stotrelup"+histSubDir, histName, sf_wh, fout, fTT, label+"_stotrel"+hist_extn.data()+"Up", true);
  //TH1F* wh_stotrelDown = DC.readWriteHisto(fWH, baseDir+"/stotreldown"+histSubDir, histName, sf_wh, fout, fTT, label+"_stotrel"+hist_extn.data()+"Down", true);
  //TH1F* wh_stotptUp = DC.readWriteHisto(fWH, baseDir+"/stotptup"+histSubDir, histName, sf_wh, fout, fTT, label+"_stotpt"+hist_extn.data()+"Up", true);
  //TH1F* wh_stotptDown = DC.readWriteHisto(fWH, baseDir+"/stotptdown"+histSubDir, histName, sf_wh, fout, fTT, label+"_stotpt"+hist_extn.data()+"Down", true);
  //TH1F* wh_stotscaleUp = DC.readWriteHisto(fWH, baseDir+"/stotscaleup"+histSubDir, histName, sf_wh, fout, fTT, label+"_stotscale"+hist_extn.data()+"Up", true);
  //TH1F* wh_stotscaleDown = DC.readWriteHisto(fWH, baseDir+"/stotscaledown"+histSubDir, histName, sf_wh, fout, fTT, label+"_stotscale"+hist_extn.data()+"Down", true);
  TH1F* wh_absmpfbUp = DC.readWriteHisto(fWH, baseDir+"/absmpfbup"+histSubDir, histName, sf_wh, fout, fTT, label+"_absmpfb"+hist_extn.data()+"Up", true);
  TH1F* wh_absmpfbDown = DC.readWriteHisto(fWH, baseDir+"/absmpfbdown"+histSubDir, histName, sf_wh, fout, fTT, label+"_absmpfb"+hist_extn.data()+"Down", true);
  TH1F* wh_abssclUp = DC.readWriteHisto(fWH, baseDir+"/abssclup"+histSubDir, histName, sf_wh, fout, fTT, label+"_absscl"+hist_extn.data()+"Up", true);
  TH1F* wh_abssclDown = DC.readWriteHisto(fWH, baseDir+"/absscldown"+histSubDir, histName, sf_wh, fout, fTT, label+"_absscl"+hist_extn.data()+"Down", true);
  TH1F* wh_absstatUp = DC.readWriteHisto(fWH, baseDir+"/absstatup"+histSubDir, histName, sf_wh, fout, fTT, label+"_absstat"+uncorr_extn.data()+"Up", true);
  TH1F* wh_absstatDown = DC.readWriteHisto(fWH, baseDir+"/absstatdown"+histSubDir, histName, sf_wh, fout, fTT, label+"_absstat"+uncorr_extn.data()+"Down", true);
  
  TH1F* wh_fragUp = DC.readWriteHisto(fWH, baseDir+"/fragup"+histSubDir, histName, sf_wh, fout, fTT, label+"_frag"+hist_extn.data()+"Up", true);
  TH1F* wh_fragDown = DC.readWriteHisto(fWH, baseDir+"/fragdown"+histSubDir, histName, sf_wh, fout, fTT, label+"_frag"+hist_extn.data()+"Down", true);
  TH1F* wh_pudatamcUp = DC.readWriteHisto(fWH, baseDir+"/pudatamcup"+histSubDir, histName, sf_wh, fout, fTT, label+"_pudatamc"+hist_extn.data()+"Up", true);
  TH1F* wh_pudatamcDown = DC.readWriteHisto(fWH, baseDir+"/pudatamcdown"+histSubDir, histName, sf_wh, fout, fTT, label+"_pudatamc"+hist_extn.data()+"Down", true);

  TH1F* wh_puptbbUp = DC.readWriteHisto(fWH, baseDir+"/puptbbup"+histSubDir, histName, sf_wh, fout, fTT, label+"_puptbb"+hist_extn.data()+"Up", true);
  TH1F* wh_puptbbDown = DC.readWriteHisto(fWH, baseDir+"/puptbbdown"+histSubDir, histName, sf_wh, fout, fTT, label+"_puptbb"+hist_extn.data()+"Down", true);
  TH1F* wh_puptec1Up = DC.readWriteHisto(fWH, baseDir+"/puptec1up"+histSubDir, histName, sf_wh, fout, fTT, label+"_puptec1"+hist_extn.data()+"Up", true);
  TH1F* wh_puptec1Down = DC.readWriteHisto(fWH, baseDir+"/puptec1down"+histSubDir, histName, sf_wh, fout, fTT, label+"_puptec1"+hist_extn.data()+"Down", true);

  TH1F* wh_puptec2Up = DC.readWriteHisto(fWH, baseDir+"/puptec2up"+histSubDir, histName, sf_wh, fout, fTT, label+"_puptec2"+hist_extn.data()+"Up", true);
  TH1F* wh_puptec2Down = DC.readWriteHisto(fWH, baseDir+"/puptec2down"+histSubDir, histName, sf_wh, fout, fTT, label+"_puptec2"+hist_extn.data()+"Down", true);
  TH1F* wh_pupthfUp = DC.readWriteHisto(fWH, baseDir+"/pupthfup"+histSubDir, histName, sf_wh, fout, fTT, label+"_pupthf"+hist_extn.data()+"Up", true);
  TH1F* wh_pupthfDown = DC.readWriteHisto(fWH, baseDir+"/pupthfdown"+histSubDir, histName, sf_wh, fout, fTT, label+"_pupthf"+hist_extn.data()+"Down", true);

  TH1F* wh_puptrefUp = DC.readWriteHisto(fWH, baseDir+"/puptrefup"+histSubDir, histName, sf_wh, fout, fTT, label+"_puptref"+hist_extn.data()+"Up", true);
  TH1F* wh_puptrefDown = DC.readWriteHisto(fWH, baseDir+"/puptrefdown"+histSubDir, histName, sf_wh, fout, fTT, label+"_puptref"+hist_extn.data()+"Down", true);
  TH1F* wh_relfsrUp = DC.readWriteHisto(fWH, baseDir+"/relfsrup"+histSubDir, histName, sf_wh, fout, fTT, label+"_relfsr"+hist_extn.data()+"Up", true);
  TH1F* wh_relfsrDown = DC.readWriteHisto(fWH, baseDir+"/relfsrdown"+histSubDir, histName, sf_wh, fout, fTT, label+"_relfsr"+hist_extn.data()+"Down", true);

  TH1F* wh_relbalUp = DC.readWriteHisto(fWH, baseDir+"/relbalup"+histSubDir, histName, sf_wh, fout, fTT, label+"_relbal"+hist_extn.data()+"Up", true);
  TH1F* wh_relbalDown = DC.readWriteHisto(fWH, baseDir+"/relbaldown"+histSubDir, histName, sf_wh, fout, fTT, label+"_relbal"+hist_extn.data()+"Down", true);
  TH1F* wh_relsampleUp = DC.readWriteHisto(fWH, baseDir+"/relsampleup"+histSubDir, histName, sf_wh, fout, fTT, label+"_relsample"+uncorr_extn.data()+"Up", true);
  TH1F* wh_relsampleDown = DC.readWriteHisto(fWH, baseDir+"/relsampledown"+histSubDir, histName, sf_wh, fout, fTT, label+"_relsample"+uncorr_extn.data()+"Down", true);

  TH1F* wh_reljerec1Up = DC.readWriteHisto(fWH, baseDir+"/reljerec1up"+histSubDir, histName, sf_wh, fout, fTT, label+"_reljerec1"+uncorr_extn.data()+"Up", true);
  TH1F* wh_reljerec1Down = DC.readWriteHisto(fWH, baseDir+"/reljerec1down"+histSubDir, histName, sf_wh, fout, fTT, label+"_reljerec1"+uncorr_extn.data()+"Down", true);
  TH1F* wh_reljerec2Up = DC.readWriteHisto(fWH, baseDir+"/reljerec2up"+histSubDir, histName, sf_wh, fout, fTT, label+"_reljerec2"+uncorr_extn.data()+"Up", true);
  TH1F* wh_reljerec2Down = DC.readWriteHisto(fWH, baseDir+"/reljerec2down"+histSubDir, histName, sf_wh, fout, fTT, label+"_reljerec2"+uncorr_extn.data()+"Down", true);

  TH1F* wh_reljerhfUp = DC.readWriteHisto(fWH, baseDir+"/reljerhfup"+histSubDir, histName, sf_wh, fout, fTT, label+"_reljerhf"+hist_extn.data()+"Up", true);
  TH1F* wh_reljerhfDown = DC.readWriteHisto(fWH, baseDir+"/reljerhfdown"+histSubDir, histName, sf_wh, fout, fTT, label+"_reljerhf"+hist_extn.data()+"Down", true);
  TH1F* wh_relptbbUp = DC.readWriteHisto(fWH, baseDir+"/relptbbup"+histSubDir, histName, sf_wh, fout, fTT, label+"_relptbb"+hist_extn.data()+"Up", true);
  TH1F* wh_relptbbDown = DC.readWriteHisto(fWH, baseDir+"/relptbbdown"+histSubDir, histName, sf_wh, fout, fTT, label+"_relptbb"+hist_extn.data()+"Down", true);

  TH1F* wh_relptec1Up = DC.readWriteHisto(fWH, baseDir+"/relptec1up"+histSubDir, histName, sf_wh, fout, fTT, label+"_relptec1"+uncorr_extn.data()+"Up", true);
  TH1F* wh_relptec1Down = DC.readWriteHisto(fWH, baseDir+"/relptec1down"+histSubDir, histName, sf_wh, fout, fTT, label+"_relptec1"+uncorr_extn.data()+"Down", true);
  TH1F* wh_relptec2Up = DC.readWriteHisto(fWH, baseDir+"/relptec2up"+histSubDir, histName, sf_wh, fout, fTT, label+"_relptec2"+uncorr_extn.data()+"Up", true);
  TH1F* wh_relptec2Down = DC.readWriteHisto(fWH, baseDir+"/relptec2down"+histSubDir, histName, sf_wh, fout, fTT, label+"_relptec2"+uncorr_extn.data()+"Down", true);

  TH1F* wh_relpthfUp = DC.readWriteHisto(fWH, baseDir+"/relpthfup"+histSubDir, histName, sf_wh, fout, fTT, label+"_relpthf"+hist_extn.data()+"Up", true);
  TH1F* wh_relpthfDown = DC.readWriteHisto(fWH, baseDir+"/relpthfdown"+histSubDir, histName, sf_wh, fout, fTT, label+"_relpthf"+hist_extn.data()+"Down", true);
  TH1F* wh_relstatecUp = DC.readWriteHisto(fWH, baseDir+"/relstatecup"+histSubDir, histName, sf_wh, fout, fTT, label+"_relstatec"+uncorr_extn.data()+"Up", true);
  TH1F* wh_relstatecDown = DC.readWriteHisto(fWH, baseDir+"/relstatecdown"+histSubDir, histName, sf_wh, fout, fTT, label+"_relstatec"+uncorr_extn.data()+"Down", true);

  TH1F* wh_relstatfsrUp = DC.readWriteHisto(fWH, baseDir+"/relstatfsrup"+histSubDir, histName, sf_wh, fout, fTT, label+"_relstatfsr"+uncorr_extn.data()+"Up", true);
  TH1F* wh_relstatfsrDown = DC.readWriteHisto(fWH, baseDir+"/relstatfsrdown"+histSubDir, histName, sf_wh, fout, fTT, label+"_relstatfsr"+uncorr_extn.data()+"Down", true);
  TH1F* wh_relstathfUp = DC.readWriteHisto(fWH, baseDir+"/relstathfup"+histSubDir, histName, sf_wh, fout, fTT, label+"_relstathf"+uncorr_extn.data()+"Up", true);
  TH1F* wh_relstathfDown = DC.readWriteHisto(fWH, baseDir+"/relstathfdown"+histSubDir, histName, sf_wh, fout, fTT, label+"_relstathf"+uncorr_extn.data()+"Down", true);

  TH1F* wh_singpiecalUp = DC.readWriteHisto(fWH, baseDir+"/singpiecalup"+histSubDir, histName, sf_wh, fout, fTT, label+"_singpiecal"+hist_extn.data()+"Up", true);
  TH1F* wh_singpiecalDown = DC.readWriteHisto(fWH, baseDir+"/singpiecaldown"+histSubDir, histName, sf_wh, fout, fTT, label+"_singpiecal"+hist_extn.data()+"Down", true);
  TH1F* wh_singpihcalUp = DC.readWriteHisto(fWH, baseDir+"/singpihcalup"+histSubDir, histName, sf_wh, fout, fTT, label+"_singpihcal"+hist_extn.data()+"Up", true);
  TH1F* wh_singpihcalDown = DC.readWriteHisto(fWH, baseDir+"/singpihcaldown"+histSubDir, histName, sf_wh, fout, fTT, label+"_singpihcal"+hist_extn.data()+"Down", true);

  TH1F* wh_flavorqcdUp = DC.readWriteHisto(fWH, baseDir+"/flavorqcdup"+histSubDir, histName, sf_wh, fout, fTT, label+"_flavorqcd"+hist_extn.data()+"Up", true);
  TH1F* wh_flavorqcdDown = DC.readWriteHisto(fWH, baseDir+"/flavorqcddown"+histSubDir, histName, sf_wh, fout, fTT, label+"_flavorqcd"+hist_extn.data()+"Down", true);
  TH1F* wh_timeptetaUp = DC.readWriteHisto(fWH, baseDir+"/timeptetaup"+histSubDir, histName, sf_wh, fout, fTT, label+"_timepteta"+uncorr_extn.data()+"Up", true);
  TH1F* wh_timeptetaDown = DC.readWriteHisto(fWH, baseDir+"/timeptetadown"+histSubDir, histName, sf_wh, fout, fTT, label+"_timepteta"+uncorr_extn.data()+"Down", true);
  TH1F* wh_PileupUp = DC.readWriteHisto(fWH, baseDir+"/puup"+histSubDir, histName, sf_wh, fout, fTT, label+"_Pileup"+hist_extn.data()+"Up", true);
  TH1F* wh_PileupDown = DC.readWriteHisto(fWH, baseDir+"/pudown"+histSubDir, histName, sf_wh, fout, fTT, label+"_Pileup"+hist_extn.data()+"Down", true);
  TH1F* wh_PrefireUp, *wh_PrefireDown;
  if(year==2016 or year==2017){
    wh_PrefireUp = DC.readWriteHisto(fWH, baseDir+"/prefireup"+histSubDir, histName, sf_wh, fout, fTT, label+"_Prefire"+hist_extn.data()+"Up", true);
    wh_PrefireDown = DC.readWriteHisto(fWH, baseDir+"/prefiredown"+histSubDir, histName, sf_wh, fout, fTT, label+"_Prefire"+hist_extn.data()+"Down", true);
  }else{
    wh_PrefireUp = DC.readWriteHisto(fWH, baseDir+"/base"+histSubDir, histName, sf_wh, fout, fTT, label+"_Prefire"+hist_extn.data()+"Up", true);
    wh_PrefireDown = DC.readWriteHisto(fWH, baseDir+"/base"+histSubDir, histName, sf_wh, fout, fTT, label+"_Prefire"+hist_extn.data()+"Down", true);
  }
  TH1F* wh_PUJetIDUp = DC.readWriteHisto(fWH, baseDir+"/pujetidup"+histSubDir, histName, sf_wh, fout, fTT, label+"_PUJetID"+hist_extn.data()+"Up", true);
  TH1F* wh_PUJetIDDown = DC.readWriteHisto(fWH, baseDir+"/pujetiddown"+histSubDir, histName, sf_wh, fout, fTT, label+"_PUJetID"+hist_extn.data()+"Down", true);
  TH1F* wh_JERUp = DC.readWriteHisto(fWH, baseDir+"/jerup"+histSubDir, histName, sf_wh, fout, fTT, label+"_JER"+hist_extn.data()+"Up", true);
  TH1F* wh_JERDown = DC.readWriteHisto(fWH, baseDir+"/jerdown"+histSubDir, histName, sf_wh, fout, fTT, label+"_JER"+hist_extn.data()+"Down", true);
  TH1F* wh_bcstatUp = DC.readWriteHisto(fWH, baseDir+"/bcstatup"+histSubDir, histName, sf_wh, fout, fTT, label+"_bcstat"+hist_extn.data()+"Up", true, isNormalized, wh);
  TH1F* wh_bcstatDown = DC.readWriteHisto(fWH, baseDir+"/bcstatdown"+histSubDir, histName, sf_wh, fout, fTT, label+"_bcstat"+hist_extn.data()+"Down", true, isNormalized, wh);
  TH1F *wh_bcintpUp, *wh_bcintpDown, *wh_bcextpUp, *wh_bcextpDown, *wh_bcxdybUp, *wh_bcxdybDown, *wh_bcxdycUp, *wh_bcxdycDown, *wh_bcxwjcUp, *wh_bcxwjcDown;
  wh_bcintpUp = DC.readWriteHisto(fWH, baseDir+"/bcintpup"+histSubDir, histName, sf_wh, fout, fTT, label+"_bcintp"+hist_extn.data()+"Up", true, isNormalized, wh);
  wh_bcintpDown = DC.readWriteHisto(fWH, baseDir+"/bcintpdown"+histSubDir, histName, sf_wh, fout, fTT, label+"_bcintp"+hist_extn.data()+"Down", true, isNormalized, wh);
  wh_bcextpUp = DC.readWriteHisto(fWH, baseDir+"/bcextpup"+histSubDir, histName, sf_wh, fout, fTT, label+"_bcextp"+hist_extn.data()+"Up", true, isNormalized, wh);
  wh_bcextpDown = DC.readWriteHisto(fWH, baseDir+"/bcextpdown"+histSubDir, histName, sf_wh, fout, fTT, label+"_bcextp"+hist_extn.data()+"Down", true, isNormalized, wh);
  wh_bcxdybUp = DC.readWriteHisto(fWH, baseDir+"/bcxdybup"+histSubDir, histName, sf_wh, fout, fTT, label+"_bcxdyb"+hist_extn.data()+"Up", true, isNormalized, wh);
  wh_bcxdybDown = DC.readWriteHisto(fWH, baseDir+"/bcxdybdown"+histSubDir, histName, sf_wh, fout, fTT, label+"_bcxdyb"+hist_extn.data()+"Down", true, isNormalized, wh);
  wh_bcxdycUp = DC.readWriteHisto(fWH, baseDir+"/bcxdycup"+histSubDir, histName, sf_wh, fout, fTT, label+"_bcxdyc"+hist_extn.data()+"Up", true, isNormalized, wh);
  wh_bcxdycDown = DC.readWriteHisto(fWH, baseDir+"/bcxdycdown"+histSubDir, histName, sf_wh, fout, fTT, label+"_bcxdyc"+hist_extn.data()+"Down", true, isNormalized, wh);
  wh_bcxwjcUp = DC.readWriteHisto(fWH, baseDir+"/bcxwjcup"+histSubDir, histName, sf_wh, fout, fTT, label+"_bcxwjc"+hist_extn.data()+"Up", true, isNormalized, wh);
  wh_bcxwjcDown = DC.readWriteHisto(fWH, baseDir+"/bcxwjcdown"+histSubDir, histName, sf_wh, fout, fTT, label+"_bcxwjc"+hist_extn.data()+"Down", true, isNormalized, wh);
  
  TH1F* wh_pdfUp = DC.readWriteHisto(fWH, baseDir+"/pdfup"+histSubDir, histName, sf_wh, fout, fTT, label+"_pdf"+hist_extn.data()+"Up", true);
  TH1F* wh_pdfDown = DC.readWriteHisto(fWH, baseDir+"/pdfdown"+histSubDir, histName, sf_wh, fout, fTT, label+"_pdf"+hist_extn.data()+"Down", true);
  // TH1F* wh_q2Up = DC.readWriteHisto(fWH, baseDir+"/q2up"+histSubDir, histName, sf_wh, fout, fTT, label+"_q2"+hist_extn.data()+"Up", true);
  // TH1F* wh_q2Down = DC.readWriteHisto(fWH, baseDir+"/q2down"+histSubDir, histName, sf_wh, fout, fTT, label+"_q2"+hist_extn.data()+"Down", true);
  TH1F* wh_bclhemufUp = DC.readWriteHisto(fWH, baseDir+"/bclhemufup"+histSubDir, histName, sf_wh, fout, fTT, label+"_bclhemuf"+hist_extn.data()+"Up", true, isNormalized, wh);
  TH1F* wh_bclhemufDown = DC.readWriteHisto(fWH, baseDir+"/bclhemufdown"+histSubDir, histName, sf_wh, fout, fTT, label+"_bclhemuf"+hist_extn.data()+"Down", true, isNormalized, wh);
  TH1F* wh_bclhemurUp = DC.readWriteHisto(fWH, baseDir+"/bclhemurup"+histSubDir, histName, sf_wh, fout, fTT, label+"_bclhemur"+hist_extn.data()+"Up", true, isNormalized, wh);
  TH1F* wh_bclhemurDown = DC.readWriteHisto(fWH, baseDir+"/bclhemurdown"+histSubDir, histName, sf_wh, fout, fTT, label+"_bclhemur"+hist_extn.data()+"Down", true, isNormalized, wh);
  TH1F* wh_isrUp = DC.readWriteHisto(fWH, baseDir+"/isrup"+histSubDir, histName, sf_wh, fout, fTT, label+"_isr"+hist_extn.data()+"Up", true, isNormalized, wh);
  TH1F* wh_isrDown = DC.readWriteHisto(fWH, baseDir+"/isrdown"+histSubDir, histName, sf_wh, fout, fTT, label+"_isr"+hist_extn.data()+"Down", true, isNormalized, wh);
  TH1F* wh_fsrUp = DC.readWriteHisto(fWH, baseDir+"/fsrup"+histSubDir, histName, sf_wh, fout, fTT, label+"_fsr"+hist_extn.data()+"Up", true, isNormalized, wh);
  TH1F* wh_fsrDown = DC.readWriteHisto(fWH, baseDir+"/fsrdown"+histSubDir, histName, sf_wh, fout, fTT, label+"_fsr"+hist_extn.data()+"Down", true, isNormalized, wh);
  TH1F* wh_topPtUp = DC.readWriteHisto(fWH, baseDir+"/topptup"+histSubDir, histName, sf_wh, fout, fTT, label+"_topPt"+hist_extn.data()+"Up", true, isNormalized, wh);
  TH1F* wh_topPtDown = DC.readWriteHisto(fWH, baseDir+"/topptdown"+histSubDir, histName, sf_wh, fout, fTT, label+"_topPt"+hist_extn.data()+"Down", true, isNormalized, wh);
  // //MiniAOD nuisances
  // TH1F* wh_bcTag1Up = DC.readWriteHisto(fWH, baseDir+"/bctag1up"+histSubDir, histName, sf_wh, fout, fTT, label+"_bcTag1"+hist_extn.data()+"Up", true, isNormalized, wh);
  // TH1F* wh_bcTag1Down = DC.readWriteHisto(fWH, baseDir+"/bctag1down"+histSubDir, histName, sf_wh, fout, fTT, label+"_bcTag1"+hist_extn.data()+"Down", true, isNormalized, wh);
  // TH1F* wh_bcTag2Up = DC.readWriteHisto(fWH, baseDir+"/bctag2up"+histSubDir, histName, sf_wh, fout, fTT, label+"_bcTag2"+hist_extn.data()+"Up", true, isNormalized, wh);
  // TH1F* wh_bcTag2Down = DC.readWriteHisto(fWH, baseDir+"/bctag2down"+histSubDir, histName, sf_wh, fout, fTT, label+"_bcTag2"+hist_extn.data()+"Down", true, isNormalized, wh);
  // TH1F* wh_bcTag3Up = DC.readWriteHisto(fWH, baseDir+"/bctag3up"+histSubDir, histName, sf_wh, fout, fTT, label+"_bcTag3"+hist_extn.data()+"Up", true, isNormalized, wh);
  // TH1F* wh_bcTag3Down = DC.readWriteHisto(fWH, baseDir+"/bctag3down"+histSubDir, histName, sf_wh, fout, fTT, label+"_bcTag3"+hist_extn.data()+"Down", true, isNormalized, wh);
  // TH1F* wh_topPtUp = DC.readWriteHisto(fWH, baseDir+"/topptup"+histSubDir, histName, sf_wh, fout, fTT, label+"_topPt"+hist_extn.data()+"Up", true, isNormalized, wh);
  // TH1F* wh_topPtDown = DC.readWriteHisto(fWH, baseDir+"/topptdown"+histSubDir, histName, sf_wh, fout, fTT, label+"_topPt"+hist_extn.data()+"Down", true, isNormalized, wh);
  // TH1F* wh_bTagbcUp = DC.readWriteHisto(fWH, baseDir+"/btagbup"+histSubDir, histName, sf_wh, fout, fTT, label+"_bTagbc"+hist_extn.data()+"Up", true, isNormalized, wh);
  // TH1F* wh_bTagbcDown = DC.readWriteHisto(fWH, baseDir+"/btagbdown"+histSubDir, histName, sf_wh, fout, fTT, label+"_bTagbc"+hist_extn.data()+"Down", true, isNormalized, wh);
  // TH1F* wh_bTaglUp = DC.readWriteHisto(fWH, baseDir+"/btaglup"+histSubDir, histName, sf_wh, fout, fTT, label+"_bTagl"+hist_extn.data()+"Up", true, isNormalized, wh);
  // TH1F* wh_bTaglDown = DC.readWriteHisto(fWH, baseDir+"/btagldown"+histSubDir, histName, sf_wh, fout, fTT, label+"_bTagl"+hist_extn.data()+"Down", true, isNormalized, wh);

  if(isBinStat){
    for(int ibin = 1; ibin <= nonStatBins ; ibin++){
      TH1F* wh_bin_stat_Up = DC.readWriteHisto(fWH, baseDir+"/base"+histSubDir, histName, sf_wh, fout, fTT, label+Form("_CMS_stat_cat1_WH_bin_%dUp",ibin), true);
      TH1F* wh_bin_stat_Down = DC.readWriteHisto(fWH, baseDir+"/base"+histSubDir, histName, sf_wh, fout, fTT, label+Form("_CMS_stat_cat1_WH_bin_%dDown",ibin), true);
    }
  }

  double unc_wh_ExL = 1.0;
  double unc_wh_ExM = 1.0;
  if(isExL){
    TH1F* wh_yLyMyT = DC.getHisto(fWH, baseDir+"/Iso/ExCTag/", "sf_CTag_yLyMyT_wt", fTT, sf_wh);
    TH1F* wh_yLyMnT = DC.getHisto(fWH, baseDir+"/Iso/ExCTag/", "sf_CTag_yLyMnT_wt", fTT, sf_wh);
    TH1F* wh_yLnMyT = DC.getHisto(fWH, baseDir+"/Iso/ExCTag/", "sf_CTag_yLnMyT_wt", fTT, sf_wh);
    TH1F* wh_yLnMnT = DC.getHisto(fWH, baseDir+"/Iso/ExCTag/", "sf_CTag_yLnMnT_wt", fTT, sf_wh);
    unc_wh_ExL = DC.getUncExL(wh_yLyMyT, wh_yLyMnT, wh_yLnMyT, wh_yLnMnT);
  }
  if(isExM){
    TH1F* wh_yMyT = DC.getHisto(fWH, baseDir+"/Iso/ExCTag/", "sf_CTag_yMyT_wt", fTT, sf_wh);
    TH1F* wh_yMnT = DC.getHisto(fWH, baseDir+"/Iso/ExCTag/", "sf_CTag_yMnT_wt", fTT, sf_wh);
    unc_wh_ExM = DC.getUncExM(wh_yMyT, wh_yMnT);
  }
  
  if(!isUncorrYearShape){
    hist_extn = hist_extn_temp;
  }

  
  //open input template data card
  ifstream in;
  char* c = new char[1000];
  in.open("MyTemplateDataCard.txt");
  //create output data card for 13 TeV
  string outDataCard = "datacard_hcs_13TeV_WH.txt";
  string histName_str(histSubDir_+TString("_")+histName);
  string thisYear = syear.Data();
  if(isMuChannel) outDataCard = "datacard_hcs_13TeV_mu_"+histName_str+"_WH%d"+"_"+thisYear+".txt"; 
  else outDataCard = "datacard_hcs_13TeV_ele_"+histName_str+"_WH%d"+"_"+thisYear+".txt";
  ofstream out(Form(outDataCard.c_str(), mass));
  out.precision(8);

  
  time_t secs=time(0);
  tm *t=localtime(&secs);
  while (in.good()){
    in.getline(c,1000,'\n');
    if (in.good()){
      string line(c);
      if(line.find("Date")!=string::npos){
        string day = string(Form("%d",t->tm_mday));
        string month = string(Form("%d",t->tm_mon+1));
        string year = string(Form("%d",t->tm_year+1900));
        line.replace( line.find("XXX") , 3 , day+"/"+month+"/"+year);
        out << line << endl;
	
      }
      else if(line.find("Description")!=string::npos){
        line.replace( line.find("YYY") , 3 , string(Form("%d", mass)) );
        line.replace( line.find("ZZZ") , 3 , string(Form("%f", totLumi)) ); 
        line.replace( line.find("CCC") , 3 , string(Form("%s", string(channelName).c_str())) ); 
        out << line << endl;
	
      }
      else if(line.find("shapes")!=string::npos){
        line.replace( line.find("XXX") , 3 , string(TString("Shapes_hcs_13TeV_")+channelName+TString("_")+histSubDir_+TString("_")+histName+TString("_")+label+TString("_")+syear));
        out << line << endl;
	
      }
      else if(line.find("Observation ")!=string::npos){
        line.replace( line.find("XXX") , 3 , string(Form("%.0f", data_obs->Integral())));
        out << line << endl;
	
      }
      else if(line.find("process ")!=string::npos && line.find("WH")!=string::npos){
        line.replace( line.find("YYY") , 3 , string(Form("%d", mass)) );
        out << line << endl;
	
      }
      else if(line.find("rate ")!=string::npos){
        string rate = "rate               ";  
        string space = "     ";
        out << rate ;
        out << space << wh->Integral()
            << space << ttbar->Integral()
	    << space << ttg->Integral()
	    << space << tth->Integral()
	    << space << ttz->Integral()
	    << space << ttw->Integral()
  	    << space << wjet->Integral()
  	    << space << zjet->Integral()
  	    << space << stop->Integral()
  	    << space << vv->Integral()
            << space << qcd_dd->Integral()
            << endl;
	
      }
      else if(line.find(" shape ")!=string::npos){
        //line.replace( line.find("XXX") , 3 , string(TString("Shapes_hcs_13TeV_")+channelName+TString("_")+histSubDir_+TString("_")+histName+TString("_")+label+TString("_")+syear));
        //out << line << endl;
	//cout << line << endl;
	stringstream ss(line);
	string systname;
	ss >> systname;
	if(isUncorrYearShape)
	  systname += hist_extn;
	//cout << systname << "    " ;
	out << systname << "    " ;
	while(ss >> systname){
	  //cout << systname << "   " ;
	  out << systname << "   " ;
	}
	//cout<<endl;
	out<<endl;
      }
      else if(line.find("CMS_lumi_13TeV ")!=string::npos){
	
        // line.replace( line.find("HHHH") , 4 , string(Form("%.3f", lumiUnc)) );
        // line.replace( line.find("TTTT") , 4 , string(Form("%.3f", lumiUnc)) ); 
        // line.replace( line.find("WWWW") , 4 , string(Form("%.3f", lumiUnc)) ); 
        // line.replace( line.find("DDDD") , 4 , string(Form("%.3f", lumiUnc)) ); 
        // line.replace( line.find("SSSS") , 4 , string(Form("%.3f", lumiUnc)) ); 
        // line.replace( line.find("VVVV") , 4 , string(Form("%.3f", lumiUnc)) ); 
        // out << line << endl;

	float corr_16_17_18 = 1.006;//following
	if(year==2016){
	  corr_16_17_18 = 1.006;
	  float uncorr_16 = 1.01;
	  line.replace( line.find("HHHH") , 4 , string(Form("%.3f", corr_16_17_18)) );
	  line.replace( line.find("TTTT") , 4 , string(Form("%.3f", corr_16_17_18)) );
	  line.replace( line.find("TTGT") , 4 , string(Form("%.3f", corr_16_17_18)) );
	  line.replace( line.find("TTHT") , 4 , string(Form("%.3f", corr_16_17_18)) );
	  line.replace( line.find("TTZT") , 4 , string(Form("%.3f", corr_16_17_18)) ); 
	  line.replace( line.find("TTWT") , 4 , string(Form("%.3f", corr_16_17_18)) );
	  line.replace( line.find("WWWW") , 4 , string(Form("%.3f", corr_16_17_18)) ); 
	  line.replace( line.find("DDDD") , 4 , string(Form("%.3f", corr_16_17_18)) ); 
	  line.replace( line.find("SSSS") , 4 , string(Form("%.3f", corr_16_17_18)) ); 
	  line.replace( line.find("VVVV") , 4 , string(Form("%.3f", corr_16_17_18)) ); 
	  out << line << endl;
	  out << "CMS_lumi_16\tlnN\t"<< uncorr_16 << "\t" << uncorr_16<< "\t"
	                             << uncorr_16<< "\t"<< uncorr_16<< "\t"<< uncorr_16<< "\t"<< uncorr_16<< "\t"
	                              << uncorr_16 << "\t"<< uncorr_16 << "\t" << uncorr_16 << "\t" << uncorr_16 << "\t 1.00 \t   2016 uncorr"<<endl;
	    
	}else if (year==2017){
	  corr_16_17_18 = 1.009;
	  float uncorr_17 = 1.02;
	  float corr_17_18 = 1.006;
	  line.replace( line.find("HHHH") , 4 , string(Form("%.3f", corr_16_17_18)) );
	  line.replace( line.find("TTTT") , 4 , string(Form("%.3f", corr_16_17_18)) ); 
	  line.replace( line.find("TTGT") , 4 , string(Form("%.3f", corr_16_17_18)) );
	  line.replace( line.find("TTHT") , 4 , string(Form("%.3f", corr_16_17_18)) );
	  line.replace( line.find("TTZT") , 4 , string(Form("%.3f", corr_16_17_18)) ); 
	  line.replace( line.find("TTWT") , 4 , string(Form("%.3f", corr_16_17_18)) );
	  line.replace( line.find("WWWW") , 4 , string(Form("%.3f", corr_16_17_18)) ); 
	  line.replace( line.find("DDDD") , 4 , string(Form("%.3f", corr_16_17_18)) ); 
	  line.replace( line.find("SSSS") , 4 , string(Form("%.3f", corr_16_17_18)) ); 
	  line.replace( line.find("VVVV") , 4 , string(Form("%.3f", corr_16_17_18)) ); 
	  out << line << endl;
	  out << "CMS_lumi_17\tlnN\t"<< uncorr_17 << "\t" << uncorr_17 << "\t" << uncorr_17 << "\t"
                               	     << uncorr_17<< "\t"<< uncorr_17<< "\t"<< uncorr_17<< "\t"<< uncorr_17<< "\t"
	                             << uncorr_17 << "\t" << uncorr_17 << "\t" << uncorr_17 << "\t 1.00 \t   2017 uncorr"<<endl;
	  out << "CMS_lumi_17_18\tlnN\t"<< corr_17_18 << "\t" << corr_17_18 << "\t" << corr_17_18 << "\t"
	                                << corr_17_18<< "\t"<< corr_17_18<< "\t"<< corr_17_18<< "\t"<< corr_17_18<< "\t"
	                                << corr_17_18 << "\t" << corr_17_18 << "\t" << corr_17_18 << "\t 1.00 \t   2017-18 corr"<<endl;

	}else if (year==2018){
	  corr_16_17_18 = 1.02;
	  float uncorr_18 = 1.015;
	  float corr_17_18 = 1.002;
	  line.replace( line.find("HHHH") , 4 , string(Form("%.3f", corr_16_17_18)) );
	  line.replace( line.find("TTTT") , 4 , string(Form("%.3f", corr_16_17_18)) ); 
	  line.replace( line.find("TTGT") , 4 , string(Form("%.3f", corr_16_17_18)) );
	  line.replace( line.find("TTHT") , 4 , string(Form("%.3f", corr_16_17_18)) );
	  line.replace( line.find("TTZT") , 4 , string(Form("%.3f", corr_16_17_18)) ); 
	  line.replace( line.find("TTWT") , 4 , string(Form("%.3f", corr_16_17_18)) );
	  line.replace( line.find("WWWW") , 4 , string(Form("%.3f", corr_16_17_18)) ); 
	  line.replace( line.find("DDDD") , 4 , string(Form("%.3f", corr_16_17_18)) ); 
	  line.replace( line.find("SSSS") , 4 , string(Form("%.3f", corr_16_17_18)) ); 
	  line.replace( line.find("VVVV") , 4 , string(Form("%.3f", corr_16_17_18)) ); 
	  out << line << endl;
	  out << "CMS_lumi_18\tlnN\t"<< uncorr_18 << "\t" << uncorr_18 << "\t" << uncorr_18 << "\t"
	                              << uncorr_18<< "\t"<< uncorr_18<< "\t"<< uncorr_18<< "\t"<< uncorr_18<< "\t"
	                              << uncorr_18 << "\t" << uncorr_18 << "\t" << uncorr_18 << "\t 1.00 \t   2018 uncorr"<<endl;
	  out << "CMS_lumi_17_18\tlnN\t"<< corr_17_18 << "\t" << corr_17_18 << "\t" << corr_17_18 << "\t"
	    	                        << corr_17_18<< "\t"<< corr_17_18<< "\t"<< corr_17_18<< "\t"<< corr_17_18<< "\t"
	                                << corr_17_18 << "\t" << corr_17_18 << "\t" << corr_17_18 << "\t 1.00 \t   2017-18 corr"<<endl;

	}
      }
      else if(line.find("CMS_eff_lep ")!=string::npos){  
	
	float sf_lep = 1.0;
        if(isMuChannel) line.replace( line.find("lep") , 4 , string(Form("%s", "m")));   
        else line.replace( line.find("lep") , 4 , string(Form("%s", "e")));

	stringstream ss(line); string systname; ss >> systname;
	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+hist_extn);

  	float leptonUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_LeptonUp, wh_LeptonDown) : 1.00;
  	line.replace( line.find("HHHH") , 4 , string(Form("%.3f", sf_lep*leptonUnc_wh)) );
        
  	float leptonUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_LeptonUp, ttbar_LeptonDown) : 1.00; 
  	line.replace( line.find("TTTT") , 4 , string(Form("%.3f", sf_lep*leptonUnc_ttbar)) ); 

	float leptonUnc_ttg = (ttg->Integral() > 0) ? DC.getBTagUnc(ttg, ttg_LeptonUp, ttg_LeptonDown) : 1.00; 
  	line.replace( line.find("TTGT") , 4 , string(Form("%.3f", sf_lep*leptonUnc_ttg)) ); 

	float leptonUnc_tth = (tth->Integral() > 0) ? DC.getBTagUnc(tth, tth_LeptonUp, tth_LeptonDown) : 1.00; 
  	line.replace( line.find("TTHT") , 4 , string(Form("%.3f", sf_lep*leptonUnc_tth)) ); 

	float leptonUnc_ttz = (ttz->Integral() > 0) ? DC.getBTagUnc(ttz, ttz_LeptonUp, ttz_LeptonDown) : 1.00; 
  	line.replace( line.find("TTZT") , 4 , string(Form("%.3f", sf_lep*leptonUnc_ttz)) ); 

	float leptonUnc_ttw = (ttw->Integral() > 0) ? DC.getBTagUnc(ttw, ttw_LeptonUp, ttw_LeptonDown) : 1.00; 
  	line.replace( line.find("TTWT") , 4 , string(Form("%.3f", sf_lep*leptonUnc_ttw)) ); 

  	float leptonUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_LeptonUp, wjet_LeptonDown) : 1.00;
  	line.replace( line.find("WWWW") , 4 , string(Form("%.3f", sf_lep*leptonUnc_wjet)) ); 
	
  	float leptonUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_LeptonUp, zjet_LeptonDown) : 1.00;
  	line.replace( line.find("DDDD") , 4 , string(Form("%.3f", sf_lep*leptonUnc_zjet)) ); 
	
  	float leptonUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_LeptonUp, stop_LeptonDown) : 1.00; 
  	line.replace( line.find("SSSS") , 4 , string(Form("%.3f", sf_lep*leptonUnc_stop)) ); 

  	float leptonUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_LeptonUp, vv_LeptonDown) : 1.00;
  	line.replace( line.find("VVVV") , 4 , string(Form("%.3f", sf_lep*leptonUnc_vv)) ); 
	
        out << line << endl;	
	
      }  
      else if(line.find("CMS_prefire ")!=string::npos){

        float prefireUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_PrefireUp, wh_PrefireDown) : 1.00;
        line.replace( line.find("HHHH") , 4 , string(Form("%.3f", prefireUnc_wh)) );
        
        float prefireUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_PrefireUp, ttbar_PrefireDown) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", prefireUnc_ttbar)) ); 
        
	float prefireUnc_ttg = (ttg->Integral() > 0) ? DC.getBTagUnc(ttg, ttg_PrefireUp, ttg_PrefireDown) : 1.00; 
  	line.replace( line.find("TTGT") , 4 , string(Form("%.3f", prefireUnc_ttg)) ); 

	float prefireUnc_tth = (tth->Integral() > 0) ? DC.getBTagUnc(tth, tth_PrefireUp, tth_PrefireDown) : 1.00; 
  	line.replace( line.find("TTHT") , 4 , string(Form("%.3f", prefireUnc_tth)) ); 

	float prefireUnc_ttz = (ttz->Integral() > 0) ? DC.getBTagUnc(ttz, ttz_PrefireUp, ttz_PrefireDown) : 1.00; 
  	line.replace( line.find("TTZT") , 4 , string(Form("%.3f", prefireUnc_ttz)) ); 

	float prefireUnc_ttw = (ttw->Integral() > 0) ? DC.getBTagUnc(ttw, ttw_PrefireUp, ttw_PrefireDown) : 1.00; 
  	line.replace( line.find("TTWT") , 4 , string(Form("%.3f", prefireUnc_ttw)) ); 

        float prefireUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_PrefireUp, wjet_PrefireDown) : 1.00;
        line.replace( line.find("WWWW") , 4 , string(Form("%.3f", prefireUnc_wjet)) ); 
	
        float prefireUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_PrefireUp, zjet_PrefireDown) : 1.00;
        line.replace( line.find("DDDD") , 4 , string(Form("%.3f", prefireUnc_zjet)) ); 
	
        float prefireUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_PrefireUp, stop_PrefireDown) : 1.00; 
        line.replace( line.find("SSSS") , 4 , string(Form("%.3f", prefireUnc_stop)) ); 

        float prefireUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_PrefireUp, vv_PrefireDown) : 1.00;
        line.replace( line.find("VVVV") , 4 , string(Form("%.3f", prefireUnc_vv)) ); 
        out << line << endl;

      }
      else if(line.find("CMS_pujetid ")!=string::npos){	

	stringstream ss(line); string systname; ss >> systname;
	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+hist_extn);

        float pujetidUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_PUJetIDUp, wh_PUJetIDDown) : 1.00;
        line.replace( line.find("HHHH") , 4 , string(Form("%.3f", pujetidUnc_wh)) );
        
        float pujetidUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_PUJetIDUp, ttbar_PUJetIDDown) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", pujetidUnc_ttbar)) ); 
                
	float pujetidUnc_ttg = (ttg->Integral() > 0) ? DC.getBTagUnc(ttg, ttg_PUJetIDUp, ttg_PUJetIDDown) : 1.00; 
  	line.replace( line.find("TTGT") , 4 , string(Form("%.3f", pujetidUnc_ttg)) ); 

	float pujetidUnc_tth = (tth->Integral() > 0) ? DC.getBTagUnc(tth, tth_PUJetIDUp, tth_PUJetIDDown) : 1.00; 
  	line.replace( line.find("TTHT") , 4 , string(Form("%.3f", pujetidUnc_tth)) ); 

	float pujetidUnc_ttz = (ttz->Integral() > 0) ? DC.getBTagUnc(ttz, ttz_PUJetIDUp, ttz_PUJetIDDown) : 1.00; 
  	line.replace( line.find("TTZT") , 4 , string(Form("%.3f", pujetidUnc_ttz)) ); 

	float pujetidUnc_ttw = (ttw->Integral() > 0) ? DC.getBTagUnc(ttw, ttw_PUJetIDUp, ttw_PUJetIDDown) : 1.00; 
  	line.replace( line.find("TTWT") , 4 , string(Form("%.3f", pujetidUnc_ttw)) ); 

        float pujetidUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_PUJetIDUp, wjet_PUJetIDDown) : 1.00;
        line.replace( line.find("WWWW") , 4 , string(Form("%.3f", pujetidUnc_wjet)) ); 
	
        float pujetidUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_PUJetIDUp, zjet_PUJetIDDown) : 1.00;
        line.replace( line.find("DDDD") , 4 , string(Form("%.3f", pujetidUnc_zjet)) ); 
	
        float pujetidUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_PUJetIDUp, stop_PUJetIDDown) : 1.00; 
        line.replace( line.find("SSSS") , 4 , string(Form("%.3f", pujetidUnc_stop)) ); 
	
        float pujetidUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_PUJetIDUp, vv_PUJetIDDown) : 1.00;
        line.replace( line.find("VVVV") , 4 , string(Form("%.3f", pujetidUnc_vv)) );
	
        out << line << endl;
	
      }
      else if(line.find("CMS_pileup ")!=string::npos){

	stringstream ss(line); string systname; ss >> systname;
	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+hist_extn);

        float PileupUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_PileupUp, wh_PileupDown) : 1.00;
        line.replace( line.find("HHHH") , 4 , string(Form("%.3f", PileupUnc_wh)) );
        
        float PileupUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_PileupUp, ttbar_PileupDown) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", PileupUnc_ttbar)) ); 
        
	float PileupUnc_ttg = (ttg->Integral() > 0) ? DC.getBTagUnc(ttg, ttg_PileupUp, ttg_PileupDown) : 1.00; 
  	line.replace( line.find("TTGT") , 4 , string(Form("%.3f", PileupUnc_ttg)) ); 

	float PileupUnc_tth = (tth->Integral() > 0) ? DC.getBTagUnc(tth, tth_PileupUp, tth_PileupDown) : 1.00; 
  	line.replace( line.find("TTHT") , 4 , string(Form("%.3f", PileupUnc_tth)) ); 

	float PileupUnc_ttz = (ttz->Integral() > 0) ? DC.getBTagUnc(ttz, ttz_PileupUp, ttz_PileupDown) : 1.00; 
  	line.replace( line.find("TTZT") , 4 , string(Form("%.3f", PileupUnc_ttz)) ); 

	float PileupUnc_ttw = (ttw->Integral() > 0) ? DC.getBTagUnc(ttw, ttw_PileupUp, ttw_PileupDown) : 1.00; 
  	line.replace( line.find("TTWT") , 4 , string(Form("%.3f", PileupUnc_ttw)) ); 

        float PileupUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_PileupUp, wjet_PileupDown) : 1.00;
        line.replace( line.find("WWWW") , 4 , string(Form("%.3f", PileupUnc_wjet)) ); 
       
        float PileupUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_PileupUp, zjet_PileupDown) : 1.00;
        line.replace( line.find("DDDD") , 4 , string(Form("%.3f", PileupUnc_zjet)) ); 
        
        float PileupUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_PileupUp, stop_PileupDown) : 1.00; 
        line.replace( line.find("SSSS") , 4 , string(Form("%.3f", PileupUnc_stop)) ); 

        float PileupUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_PileupUp, vv_PileupDown) : 1.00;
        line.replace( line.find("VVVV") , 4 , string(Form("%.3f", PileupUnc_vv)) ); 
        out << line << endl;	
	
      }
      // else if(line.find("CMS_scale_j ")!=string::npos){
      //   float JESUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_JESUp, wh_JESDown) : 1.00;
      //   line.replace( line.find("HHHH") , 4 , string(Form("%.3f", JESUnc_wh)) );
        
      //   float JESUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_JESUp, ttbar_JESDown) : 1.00; 
      //   line.replace( line.find("TTTT") , 4 , string(Form("%.3f", JESUnc_ttbar)) ); 
        
      //   float JESUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_JESUp, wjet_JESDown) : 1.00;
      //   line.replace( line.find("WWWW") , 4 , string(Form("%.3f", JESUnc_wjet)) ); 
       
      //   float JESUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_JESUp, zjet_JESDown) : 1.00;
      //   line.replace( line.find("DDDD") , 4 , string(Form("%.3f", JESUnc_zjet)) ); 
        
      //   float JESUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_JESUp, stop_JESDown) : 1.00; 
      //   line.replace( line.find("SSSS") , 4 , string(Form("%.3f", JESUnc_stop)) ); 

      //   float JESUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_JESUp, vv_JESDown) : 1.00;
      //   line.replace( line.find("VVVV") , 4 , string(Form("%.3f", JESUnc_vv)) ); 
      //   out << line << endl;
	
      // }
      // else if(line.find("CMS_JER ")!=string::npos){

      // 	stringstream ss(line); string systname; ss >> systname;
      // 	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+hist_extn);

      //   float JERUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_JERUp, wh_JERDown) : 1.00;
      //   line.replace( line.find("HHHH") , 4 , string(Form("%.3f", JERUnc_wh)) );
        
      //   float JERUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_JERUp, ttbar_JERDown) : 1.00; 
      //   line.replace( line.find("TTTT") , 4 , string(Form("%.3f", JERUnc_ttbar)) ); 
        
      //   float JERUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_JERUp, wjet_JERDown) : 1.00;
      //   line.replace( line.find("WWWW") , 4 , string(Form("%.3f", JERUnc_wjet)) ); 
       
      //   float JERUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_JERUp, zjet_JERDown) : 1.00;
      //   line.replace( line.find("DDDD") , 4 , string(Form("%.3f", JERUnc_zjet)) ); 
        
      //   float JERUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_JERUp, stop_JERDown) : 1.00; 
      //   line.replace( line.find("SSSS") , 4 , string(Form("%.3f", JERUnc_stop)) ); 

      //   float JERUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_JERUp, vv_JERDown) : 1.00;
      //   line.replace( line.find("VVVV") , 4 , string(Form("%.3f", JERUnc_vv)) ); 
      //   out << line << endl;
	
      // }
      else if(line.find("CMS_norm_qcd ")!=string::npos){  

	stringstream ss(line); string systname; ss >> systname;
	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+hist_extn);

        line.replace( line.find("QQQQ") , 4 , string(Form("%.3f", qcd_unc)));   
        //if(isMuChannel) line.replace( line.find("QQQQ") , 4 , string(Form("%.4f", 1.10)));   
        //else line.replace(line.find("QQQQ") , 4 , string(Form("%.4f", 1.10)));   
        out << line << endl;
	
      }
      // else if(line.find("CMS_topPtReweight ")!=string::npos){
      //   float topPtUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_topPtUp, wh_topPtDown) : 1.00;
      //   line.replace( line.find("HHHH") , 4 , string(Form("%.3f", topPtUnc_wh)) );
        
      //   float topPtUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_topPtUp, ttbar_topPtDown) : 1.00; 
      //   line.replace( line.find("TTTT") , 4 , string(Form("%.3f", topPtUnc_ttbar)) ); 
      //   out << line << endl;
      // }
      // else if(line.find("CMS_muF_tt ")!=string::npos){
      //   float muf_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_bclhemufUp, ttbar_bclhemufDown) : 1.00; 
      //   line.replace( line.find("TTTT") , 4 , string(Form("%.3f", muf_ttbar)) ); 
      //   out << line << endl;
	
      // }
      // else if(line.find("CMS_muR_tt ")!=string::npos){
      //   float mur_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_bclhemurUp, ttbar_bclhemurDown) : 1.00; 
      //   line.replace( line.find("TTTT") , 4 , string(Form("%.3f", mur_ttbar)) ); 
      //   out << line << endl;
	
      // }
      else if(line.find("CMS_hDamp_tt ")!=string::npos){

	stringstream ss(line); string systname; ss >> systname;
	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+hist_extn);

        float matchUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_matchingUp, ttbar_matchingDown) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", matchUnc_ttbar)) ); 
        out << line << endl;
	
      }
      else if(line.find("CMS_topMass_tt ")!=string::npos){

	stringstream ss(line); string systname; ss >> systname;
	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+hist_extn);

  	float mtopUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_mtop1735, ttbar_mtop1715) : 1.00; 
  	line.replace( line.find("TTTT") , 4 , string(Form("%.3f", mtopUnc_ttbar)) ); 
  	out << line << endl;
      }
      else if(line.find("CMS_CP5_tt ")!=string::npos){

	stringstream ss(line); string systname; ss >> systname;
	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+hist_extn);

  	float scaleUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_cp5Up, ttbar_cp5Down) : 1.00; 
  	line.replace( line.find("TTTT") , 4 , string(Form("%.3f", scaleUnc_ttbar)) ); 
  	out << line << endl;
	
      }
      else if(line.find("CMS_pdf ")!=string::npos){

	stringstream ss(line); string systname; ss >> systname;
	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+hist_extn);

        float pdfUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_pdfUp, wh_pdfDown) : 1.00;
        line.replace( line.find("HHHH") , 4 , string(Form("%.3f", pdfUnc_wh)) );
        
        float pdfUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_pdfUp, ttbar_pdfDown) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", pdfUnc_ttbar)) ); 
        
	float pdfUnc_ttg = (ttg->Integral() > 0) ? DC.getBTagUnc(ttg, ttg_pdfUp, ttg_pdfDown) : 1.00; 
  	line.replace( line.find("TTGT") , 4 , string(Form("%.3f", pdfUnc_ttg)) ); 

	float pdfUnc_tth = (tth->Integral() > 0) ? DC.getBTagUnc(tth, tth_pdfUp, tth_pdfDown) : 1.00; 
  	line.replace( line.find("TTHT") , 4 , string(Form("%.3f", pdfUnc_tth)) ); 

	float pdfUnc_ttz = (ttz->Integral() > 0) ? DC.getBTagUnc(ttz, ttz_pdfUp, ttz_pdfDown) : 1.00; 
  	line.replace( line.find("TTZT") , 4 , string(Form("%.3f", pdfUnc_ttz)) ); 

	float pdfUnc_ttw = (ttw->Integral() > 0) ? DC.getBTagUnc(ttw, ttw_pdfUp, ttw_pdfDown) : 1.00; 
  	line.replace( line.find("TTWT") , 4 , string(Form("%.3f", pdfUnc_ttw)) ); 

        float pdfUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_pdfUp, wjet_pdfDown) : 1.00;
        line.replace( line.find("WWWW") , 4 , string(Form("%.3f", pdfUnc_wjet)) ); 
       
        float pdfUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_pdfUp, zjet_pdfDown) : 1.00;
        line.replace( line.find("DDDD") , 4 , string(Form("%.3f", pdfUnc_zjet)) ); 
        
        float pdfUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_pdfUp, stop_pdfDown) : 1.00; 
        line.replace( line.find("SSSS") , 4 , string(Form("%.3f", pdfUnc_stop)) ); 

        float pdfUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_pdfUp, vv_pdfDown) : 1.00;
        line.replace( line.find("VVVV") , 4 , string(Form("%.3f", pdfUnc_vv)) ); 
        out << line << endl;
      }
      else if(line.find("CMS_isr ")!=string::npos){

	stringstream ss(line); string systname; ss >> systname;
	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+hist_extn);

        float isrUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_isrUp, wh_isrDown) : 1.00;
        line.replace( line.find("HHHH") , 4 , string(Form("%.3f", isrUnc_wh)) );
        
        float isrUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_isrUp, ttbar_isrDown) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", isrUnc_ttbar)) ); 
        
	float isrUnc_ttg = (ttg->Integral() > 0) ? DC.getBTagUnc(ttg, ttg_isrUp, ttg_isrDown) : 1.00; 
  	line.replace( line.find("TTGT") , 4 , string(Form("%.3f", isrUnc_ttg)) ); 

	float isrUnc_tth = (tth->Integral() > 0) ? DC.getBTagUnc(tth, tth_isrUp, tth_isrDown) : 1.00; 
  	line.replace( line.find("TTHT") , 4 , string(Form("%.3f", isrUnc_tth)) ); 

	float isrUnc_ttz = (ttz->Integral() > 0) ? DC.getBTagUnc(ttz, ttz_isrUp, ttz_isrDown) : 1.00; 
  	line.replace( line.find("TTZT") , 4 , string(Form("%.3f", isrUnc_ttz)) ); 

	float isrUnc_ttw = (ttw->Integral() > 0) ? DC.getBTagUnc(ttw, ttw_isrUp, ttw_isrDown) : 1.00; 
  	line.replace( line.find("TTWT") , 4 , string(Form("%.3f", isrUnc_ttw)) ); 

        float isrUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_isrUp, wjet_isrDown) : 1.00;
        line.replace( line.find("WWWW") , 4 , string(Form("%.3f", isrUnc_wjet)) ); 
       
        float isrUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_isrUp, zjet_isrDown) : 1.00;
        line.replace( line.find("DDDD") , 4 , string(Form("%.3f", isrUnc_zjet)) ); 
        
        float isrUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_isrUp, stop_isrDown) : 1.00; 
        line.replace( line.find("SSSS") , 4 , string(Form("%.3f", isrUnc_stop)) ); 

        float isrUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_isrUp, vv_isrDown) : 1.00;
        line.replace( line.find("VVVV") , 4 , string(Form("%.3f", isrUnc_vv)) ); 
        out << line << endl;
      }
      else if(line.find("CMS_fsr ")!=string::npos){

	stringstream ss(line); string systname; ss >> systname;
	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+hist_extn);

        float fsrUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_fsrUp, wh_fsrDown) : 1.00;
        line.replace( line.find("HHHH") , 4 , string(Form("%.3f", fsrUnc_wh)) );
        
        float fsrUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_fsrUp, ttbar_fsrDown) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", fsrUnc_ttbar)) ); 
        
	float fsrUnc_ttg = (ttg->Integral() > 0) ? DC.getBTagUnc(ttg, ttg_fsrUp, ttg_fsrDown) : 1.00; 
  	line.replace( line.find("TTGT") , 4 , string(Form("%.3f", fsrUnc_ttg)) ); 

	float fsrUnc_tth = (tth->Integral() > 0) ? DC.getBTagUnc(tth, tth_fsrUp, tth_fsrDown) : 1.00; 
  	line.replace( line.find("TTHT") , 4 , string(Form("%.3f", fsrUnc_tth)) ); 

	float fsrUnc_ttz = (ttz->Integral() > 0) ? DC.getBTagUnc(ttz, ttz_fsrUp, ttz_fsrDown) : 1.00; 
  	line.replace( line.find("TTZT") , 4 , string(Form("%.3f", fsrUnc_ttz)) ); 

	float fsrUnc_ttw = (ttw->Integral() > 0) ? DC.getBTagUnc(ttw, ttw_fsrUp, ttw_fsrDown) : 1.00; 
  	line.replace( line.find("TTWT") , 4 , string(Form("%.3f", fsrUnc_ttw)) ); 

        float fsrUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_fsrUp, wjet_fsrDown) : 1.00;
        line.replace( line.find("WWWW") , 4 , string(Form("%.3f", fsrUnc_wjet)) ); 
       
        float fsrUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_fsrUp, zjet_fsrDown) : 1.00;
        line.replace( line.find("DDDD") , 4 , string(Form("%.3f", fsrUnc_zjet)) ); 
        
        float fsrUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_fsrUp, stop_fsrDown) : 1.00; 
        line.replace( line.find("SSSS") , 4 , string(Form("%.3f", fsrUnc_stop)) ); 

        float fsrUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_fsrUp, vv_fsrDown) : 1.00;
        line.replace( line.find("VVVV") , 4 , string(Form("%.3f", fsrUnc_vv)) ); 
        out << line << endl;
      }
      // else if(line.find("CMS_eff_bcInc1 ")!=string::npos){
      //   float bTagUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_bcTag1Up, wh_bcTag1Down) : 1.00;
      //   line.replace( line.find("HHHH") , 4 , string(Form("%.3f", bTagUnc_wh)) );
        
      //   float bTagUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_bcTag1Up, ttbar_bcTag1Down) : 1.00; 
      //   line.replace( line.find("TTTT") , 4 , string(Form("%.3f", bTagUnc_ttbar)) ); 
        
      //   float bTagUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_bcTag1Up, wjet_bcTag1Down) : 1.00;
      //   line.replace( line.find("WWWW") , 4 , string(Form("%.3f", bTagUnc_wjet)) ); 
       
      //   float bTagUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_bcTag1Up, zjet_bcTag1Down) : 1.00;
      //   line.replace( line.find("DDDD") , 4 , string(Form("%.3f", bTagUnc_zjet)) ); 

      //   float bTagUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_bcTag1Up, stop_bcTag1Down) : 1.00; 
      //   line.replace( line.find("SSSS") , 4 , string(Form("%.3f", bTagUnc_stop)) ); 

      //   float bTagUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_bcTag1Up, vv_bcTag1Down) : 1.00;
      //   line.replace( line.find("VVVV") , 4 , string(Form("%.3f", bTagUnc_vv)) ); 
      //   out << line << endl;
      // }
      // else if(line.find("CMS_eff_bcInc2 ")!=string::npos){
      //   float cTagUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_bcTag2Up, wh_bcTag2Down) : 1.00;
      //   line.replace( line.find("HHHH") , 4 , string(Form("%.3f", cTagUnc_wh)) );
        
      //   float cTagUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_bcTag2Up, ttbar_bcTag2Down) : 1.00; 
      //   line.replace( line.find("TTTT") , 4 , string(Form("%.3f", cTagUnc_ttbar)) ); 
        
      //   float cTagUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_bcTag2Up, wjet_bcTag2Down) : 1.00;
      //   line.replace( line.find("WWWW") , 4 , string(Form("%.3f", cTagUnc_wjet)) ); 
       
      //   float cTagUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_bcTag2Up, zjet_bcTag2Down) : 1.00;
      //   line.replace( line.find("DDDD") , 4 , string(Form("%.3f", cTagUnc_zjet)) ); 
        
      //   float cTagUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_bcTag2Up, stop_bcTag2Down) : 1.00; 
      //   line.replace( line.find("SSSS") , 4 , string(Form("%.3f", cTagUnc_stop)) ); 

      //   float cTagUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_bcTag2Up, vv_bcTag2Down) : 1.00;
      //   line.replace( line.find("VVVV") , 4 , string(Form("%.3f", cTagUnc_vv)) ); 
      //   out << line << endl;
      // }
      // else if(line.find("CMS_eff_bcInc3 ")!=string::npos){
      //   float cTagUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_bcTag3Up, wh_bcTag3Down) : 1.00;
      //   line.replace( line.find("HHHH") , 4 , string(Form("%.3f", cTagUnc_wh)) );
        
      //   float cTagUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_bcTag3Up, ttbar_bcTag3Down) : 1.00; 
      //   line.replace( line.find("TTTT") , 4 , string(Form("%.3f", cTagUnc_ttbar)) ); 
        
      //   float cTagUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_bcTag3Up, wjet_bcTag3Down) : 1.00;
      //   line.replace( line.find("WWWW") , 4 , string(Form("%.3f", cTagUnc_wjet)) ); 
       
      //   float cTagUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_bcTag3Up, zjet_bcTag3Down) : 1.00;
      //   line.replace( line.find("DDDD") , 4 , string(Form("%.3f", cTagUnc_zjet)) ); 
        
      //   float cTagUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_bcTag3Up, stop_bcTag3Down) : 1.00; 
      //   line.replace( line.find("SSSS") , 4 , string(Form("%.3f", cTagUnc_stop)) ); 

      //   float cTagUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_bcTag3Up, vv_bcTag3Down) : 1.00;
      //   line.replace( line.find("VVVV") , 4 , string(Form("%.3f", cTagUnc_vv)) ); 
      //   out << line << endl;
      // }
      // else if(line.find("CMS_eff_bTagbc ")!=string::npos){
      //   float bTagUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_bTagbcUp, wh_bTagbcDown) : 1.00;
      //   line.replace( line.find("HHHH") , 4 , string(Form("%.3f", bTagUnc_wh)) );
        
      //   float bTagUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_bTagbcUp, ttbar_bTagbcDown) : 1.00; 
      //   line.replace( line.find("TTTT") , 4 , string(Form("%.3f", bTagUnc_ttbar)) ); 
        
      //   float bTagUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_bTagbcUp, wjet_bTagbcDown) : 1.00;
      //   line.replace( line.find("WWWW") , 4 , string(Form("%.3f", bTagUnc_wjet)) ); 
       
      //   float bTagUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_bTagbcUp, zjet_bTagbcDown) : 1.00;
      //   line.replace( line.find("DDDD") , 4 , string(Form("%.3f", bTagUnc_zjet)) ); 

      //   float bTagUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_bTagbcUp, stop_bTagbcDown) : 1.00; 
      //   line.replace( line.find("SSSS") , 4 , string(Form("%.3f", bTagUnc_stop)) ); 

      //   float bTagUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_bTagbcUp, vv_bTagbcDown) : 1.00;
      //   line.replace( line.find("VVVV") , 4 , string(Form("%.3f", bTagUnc_vv)) ); 
      //   out << line << endl;
      // }
      // else if(line.find("CMS_eff_bTagl ")!=string::npos){
      //   float bTagUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_bTaglUp, wh_bTaglDown) : 1.00;
      //   line.replace( line.find("HHHH") , 4 , string(Form("%.3f", bTagUnc_wh)) );
        
      //   float bTagUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_bTaglUp, ttbar_bTaglDown) : 1.00; 
      //   line.replace( line.find("TTTT") , 4 , string(Form("%.3f", bTagUnc_ttbar)) ); 
        
      //   float bTagUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_bTaglUp, wjet_bTaglDown) : 1.00;
      //   line.replace( line.find("WWWW") , 4 , string(Form("%.3f", bTagUnc_wjet)) ); 
       
      //   float bTagUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_bTaglUp, zjet_bTaglDown) : 1.00;
      //   line.replace( line.find("DDDD") , 4 , string(Form("%.3f", bTagUnc_zjet)) ); 

      //   float bTagUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_bTaglUp, stop_bTaglDown) : 1.00; 
      //   line.replace( line.find("SSSS") , 4 , string(Form("%.3f", bTagUnc_stop)) ); 

      //   float bTagUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_bTaglUp, vv_bTaglDown) : 1.00;
      //   line.replace( line.find("VVVV") , 4 , string(Form("%.3f", bTagUnc_vv)) ); 
      //   out << line << endl;
      // }
      else if(line.find("CMS_bcstat ")!=string::npos){
	//Default
	stringstream ss(line); string systname; ss >> systname;
	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+hist_extn);

        float bcstatUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_bcstatUp, wh_bcstatDown) : 1.00;
        line.replace( line.find("HHHH") , 4 , string(Form("%.3f", bcstatUnc_wh)) );
        
        float bcstatUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_bcstatUp, ttbar_bcstatDown) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", bcstatUnc_ttbar)) ); 
        
	float bcstatUnc_ttg = (ttg->Integral() > 0) ? DC.getBTagUnc(ttg, ttg_bcstatUp, ttg_bcstatDown) : 1.00; 
  	line.replace( line.find("TTGT") , 4 , string(Form("%.3f", bcstatUnc_ttg)) ); 

	float bcstatUnc_tth = (tth->Integral() > 0) ? DC.getBTagUnc(tth, tth_bcstatUp, tth_bcstatDown) : 1.00; 
  	line.replace( line.find("TTHT") , 4 , string(Form("%.3f", bcstatUnc_tth)) ); 

	float bcstatUnc_ttz = (ttz->Integral() > 0) ? DC.getBTagUnc(ttz, ttz_bcstatUp, ttz_bcstatDown) : 1.00; 
  	line.replace( line.find("TTZT") , 4 , string(Form("%.3f", bcstatUnc_ttz)) ); 

	float bcstatUnc_ttw = (ttw->Integral() > 0) ? DC.getBTagUnc(ttw, ttw_bcstatUp, ttw_bcstatDown) : 1.00; 
  	line.replace( line.find("TTWT") , 4 , string(Form("%.3f", bcstatUnc_ttw)) ); 

        float bcstatUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_bcstatUp, wjet_bcstatDown) : 1.00;
        line.replace( line.find("WWWW") , 4 , string(Form("%.3f", bcstatUnc_wjet)) ); 
	
        float bcstatUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_bcstatUp, zjet_bcstatDown) : 1.00;
        line.replace( line.find("DDDD") , 4 , string(Form("%.3f", bcstatUnc_zjet)) ); 
        
        float bcstatUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_bcstatUp, stop_bcstatDown) : 1.00; 
        line.replace( line.find("SSSS") , 4 , string(Form("%.3f", bcstatUnc_stop)) ); 
	
        float bcstatUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_bcstatUp, vv_bcstatDown) : 1.00;
        line.replace( line.find("VVVV") , 4 , string(Form("%.3f", bcstatUnc_vv)) ); 
        out << line << endl;
	
	// float globbcstatUnc = 1.15;
        // float bcstatUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_bcstatUp, wh_bcstatDown) : 1.00;
        // line.replace( line.find("HHHH") , 4 , string(Form("%.3f", globbcstatUnc)) );
        
        // float bcstatUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_bcstatUp, ttbar_bcstatDown) : 1.00; 
        // line.replace( line.find("TTTT") , 4 , string(Form("%.3f", globbcstatUnc)) ); 
        
        // float bcstatUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_bcstatUp, wjet_bcstatDown) : 1.00;
        // line.replace( line.find("WWWW") , 4 , string(Form("%.3f", globbcstatUnc)) ); 
       
        // float bcstatUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_bcstatUp, zjet_bcstatDown) : 1.00;
        // line.replace( line.find("DDDD") , 4 , string(Form("%.3f", globbcstatUnc)) ); 
        
        // float bcstatUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_bcstatUp, stop_bcstatDown) : 1.00; 
        // line.replace( line.find("SSSS") , 4 , string(Form("%.3f", globbcstatUnc)) ); 

        // float bcstatUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_bcstatUp, vv_bcstatDown) : 1.00;
        // line.replace( line.find("VVVV") , 4 , string(Form("%.3f", globbcstatUnc)) ); 
        // out << line << endl;
      }
      else if(line.find("CMS_bclhemuf ")!=string::npos){

	stringstream ss(line); string systname; ss >> systname;
	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+hist_extn);

        float bclhemufUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_bclhemufUp, wh_bclhemufDown) : 1.00;
        line.replace( line.find("HHHH") , 4 , string(Form("%.3f", bclhemufUnc_wh)) );
        
        float bclhemufUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_bclhemufUp, ttbar_bclhemufDown) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", bclhemufUnc_ttbar)) ); 
        
	float bclhemufUnc_ttg = (ttg->Integral() > 0) ? DC.getBTagUnc(ttg, ttg_bclhemufUp, ttg_bclhemufDown) : 1.00; 
  	line.replace( line.find("TTGT") , 4 , string(Form("%.3f", bclhemufUnc_ttg)) ); 

	float bclhemufUnc_tth = (tth->Integral() > 0) ? DC.getBTagUnc(tth, tth_bclhemufUp, tth_bclhemufDown) : 1.00; 
  	line.replace( line.find("TTHT") , 4 , string(Form("%.3f", bclhemufUnc_tth)) ); 

	float bclhemufUnc_ttz = (ttz->Integral() > 0) ? DC.getBTagUnc(ttz, ttz_bclhemufUp, ttz_bclhemufDown) : 1.00; 
  	line.replace( line.find("TTZT") , 4 , string(Form("%.3f", bclhemufUnc_ttz)) ); 

	float bclhemufUnc_ttw = (ttw->Integral() > 0) ? DC.getBTagUnc(ttw, ttw_bclhemufUp, ttw_bclhemufDown) : 1.00; 
  	line.replace( line.find("TTWT") , 4 , string(Form("%.3f", bclhemufUnc_ttw)) ); 

        float bclhemufUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_bclhemufUp, wjet_bclhemufDown) : 1.00;
        line.replace( line.find("WWWW") , 4 , string(Form("%.3f", bclhemufUnc_wjet)) ); 
       
        float bclhemufUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_bclhemufUp, zjet_bclhemufDown) : 1.00;
        line.replace( line.find("DDDD") , 4 , string(Form("%.3f", bclhemufUnc_zjet)) ); 
        
        float bclhemufUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_bclhemufUp, stop_bclhemufDown) : 1.00; 
        line.replace( line.find("SSSS") , 4 , string(Form("%.3f", bclhemufUnc_stop)) ); 

        float bclhemufUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_bclhemufUp, vv_bclhemufDown) : 1.00;
        line.replace( line.find("VVVV") , 4 , string(Form("%.3f", bclhemufUnc_vv)) ); 
        out << line << endl;
      }
      else if(line.find("CMS_bclhemur ")!=string::npos){

	stringstream ss(line); string systname; ss >> systname;
	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+hist_extn);

        float bclhemurUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_bclhemurUp, wh_bclhemurDown) : 1.00;
        line.replace( line.find("HHHH") , 4 , string(Form("%.3f", bclhemurUnc_wh)) );
        
        float bclhemurUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_bclhemurUp, ttbar_bclhemurDown) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", bclhemurUnc_ttbar)) ); 
        
	float bclhemurUnc_ttg = (ttg->Integral() > 0) ? DC.getBTagUnc(ttg, ttg_bclhemurUp, ttg_bclhemurDown) : 1.00; 
  	line.replace( line.find("TTGT") , 4 , string(Form("%.3f", bclhemurUnc_ttg)) ); 

	float bclhemurUnc_tth = (tth->Integral() > 0) ? DC.getBTagUnc(tth, tth_bclhemurUp, tth_bclhemurDown) : 1.00; 
  	line.replace( line.find("TTHT") , 4 , string(Form("%.3f", bclhemurUnc_tth)) ); 

	float bclhemurUnc_ttz = (ttz->Integral() > 0) ? DC.getBTagUnc(ttz, ttz_bclhemurUp, ttz_bclhemurDown) : 1.00; 
  	line.replace( line.find("TTZT") , 4 , string(Form("%.3f", bclhemurUnc_ttz)) ); 

	float bclhemurUnc_ttw = (ttw->Integral() > 0) ? DC.getBTagUnc(ttw, ttw_bclhemurUp, ttw_bclhemurDown) : 1.00; 
  	line.replace( line.find("TTWT") , 4 , string(Form("%.3f", bclhemurUnc_ttw)) ); 

        float bclhemurUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_bclhemurUp, wjet_bclhemurDown) : 1.00;
        line.replace( line.find("WWWW") , 4 , string(Form("%.3f", bclhemurUnc_wjet)) ); 
       
        float bclhemurUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_bclhemurUp, zjet_bclhemurDown) : 1.00;
        line.replace( line.find("DDDD") , 4 , string(Form("%.3f", bclhemurUnc_zjet)) ); 
        
        float bclhemurUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_bclhemurUp, stop_bclhemurDown) : 1.00; 
        line.replace( line.find("SSSS") , 4 , string(Form("%.3f", bclhemurUnc_stop)) ); 

        float bclhemurUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_bclhemurUp, vv_bclhemurDown) : 1.00;
        line.replace( line.find("VVVV") , 4 , string(Form("%.3f", bclhemurUnc_vv)) ); 
        out << line << endl;
      }
      else if(line.find("CMS_bcxdyb ")!=string::npos){

	stringstream ss(line); string systname; ss >> systname;
	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+hist_extn);

        float bcxdybUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_bcxdybUp, wh_bcxdybDown) : 1.00;
        line.replace( line.find("HHHH") , 4 , string(Form("%.3f", bcxdybUnc_wh)) );
        
        float bcxdybUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_bcxdybUp, ttbar_bcxdybDown) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", bcxdybUnc_ttbar)) ); 
        
	float bcxdybUnc_ttg = (ttg->Integral() > 0) ? DC.getBTagUnc(ttg, ttg_bcxdybUp, ttg_bcxdybDown) : 1.00; 
  	line.replace( line.find("TTGT") , 4 , string(Form("%.3f", bcxdybUnc_ttg)) ); 

	float bcxdybUnc_tth = (tth->Integral() > 0) ? DC.getBTagUnc(tth, tth_bcxdybUp, tth_bcxdybDown) : 1.00; 
  	line.replace( line.find("TTHT") , 4 , string(Form("%.3f", bcxdybUnc_tth)) ); 

	float bcxdybUnc_ttz = (ttz->Integral() > 0) ? DC.getBTagUnc(ttz, ttz_bcxdybUp, ttz_bcxdybDown) : 1.00; 
  	line.replace( line.find("TTZT") , 4 , string(Form("%.3f", bcxdybUnc_ttz)) ); 

	float bcxdybUnc_ttw = (ttw->Integral() > 0) ? DC.getBTagUnc(ttw, ttw_bcxdybUp, ttw_bcxdybDown) : 1.00; 
  	line.replace( line.find("TTWT") , 4 , string(Form("%.3f", bcxdybUnc_ttw)) ); 

        float bcxdybUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_bcxdybUp, wjet_bcxdybDown) : 1.00;
        line.replace( line.find("WWWW") , 4 , string(Form("%.3f", bcxdybUnc_wjet)) ); 
       
        float bcxdybUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_bcxdybUp, zjet_bcxdybDown) : 1.00;
        line.replace( line.find("DDDD") , 4 , string(Form("%.3f", bcxdybUnc_zjet)) ); 
        
        float bcxdybUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_bcxdybUp, stop_bcxdybDown) : 1.00; 
        line.replace( line.find("SSSS") , 4 , string(Form("%.3f", bcxdybUnc_stop)) ); 

        float bcxdybUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_bcxdybUp, vv_bcxdybDown) : 1.00;
        line.replace( line.find("VVVV") , 4 , string(Form("%.3f", bcxdybUnc_vv)) ); 
        out << line << endl;
      }
      else if(line.find("CMS_bcxdyc ")!=string::npos){

	stringstream ss(line); string systname; ss >> systname;
	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+hist_extn);

        float bcxdycUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_bcxdycUp, wh_bcxdycDown) : 1.00;
        line.replace( line.find("HHHH") , 4 , string(Form("%.3f", bcxdycUnc_wh)) );
        
        float bcxdycUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_bcxdycUp, ttbar_bcxdycDown) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", bcxdycUnc_ttbar)) ); 
        
	float bcxdycUnc_ttg = (ttg->Integral() > 0) ? DC.getBTagUnc(ttg, ttg_bcxdycUp, ttg_bcxdycDown) : 1.00; 
  	line.replace( line.find("TTGT") , 4 , string(Form("%.3f", bcxdycUnc_ttg)) ); 

	float bcxdycUnc_tth = (tth->Integral() > 0) ? DC.getBTagUnc(tth, tth_bcxdycUp, tth_bcxdycDown) : 1.00; 
  	line.replace( line.find("TTHT") , 4 , string(Form("%.3f", bcxdycUnc_tth)) ); 

	float bcxdycUnc_ttz = (ttz->Integral() > 0) ? DC.getBTagUnc(ttz, ttz_bcxdycUp, ttz_bcxdycDown) : 1.00; 
  	line.replace( line.find("TTZT") , 4 , string(Form("%.3f", bcxdycUnc_ttz)) ); 

	float bcxdycUnc_ttw = (ttw->Integral() > 0) ? DC.getBTagUnc(ttw, ttw_bcxdycUp, ttw_bcxdycDown) : 1.00; 
  	line.replace( line.find("TTWT") , 4 , string(Form("%.3f", bcxdycUnc_ttw)) ); 

        float bcxdycUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_bcxdycUp, wjet_bcxdycDown) : 1.00;
        line.replace( line.find("WWWW") , 4 , string(Form("%.3f", bcxdycUnc_wjet)) ); 
       
        float bcxdycUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_bcxdycUp, zjet_bcxdycDown) : 1.00;
        line.replace( line.find("DDDD") , 4 , string(Form("%.3f", bcxdycUnc_zjet)) ); 
        
        float bcxdycUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_bcxdycUp, stop_bcxdycDown) : 1.00; 
        line.replace( line.find("SSSS") , 4 , string(Form("%.3f", bcxdycUnc_stop)) ); 

        float bcxdycUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_bcxdycUp, vv_bcxdycDown) : 1.00;
        line.replace( line.find("VVVV") , 4 , string(Form("%.3f", bcxdycUnc_vv)) ); 
        out << line << endl;
      }
      else if(line.find("CMS_bcxwjc ")!=string::npos){

	stringstream ss(line); string systname; ss >> systname;
	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+hist_extn);

        float bcxwjcUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_bcxwjcUp, wh_bcxwjcDown) : 1.00;
        line.replace( line.find("HHHH") , 4 , string(Form("%.3f", bcxwjcUnc_wh)) );
        
        float bcxwjcUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_bcxwjcUp, ttbar_bcxwjcDown) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", bcxwjcUnc_ttbar)) ); 
        
	float bcxwjcUnc_ttg = (ttg->Integral() > 0) ? DC.getBTagUnc(ttg, ttg_bcxwjcUp, ttg_bcxwjcDown) : 1.00; 
  	line.replace( line.find("TTGT") , 4 , string(Form("%.3f", bcxwjcUnc_ttg)) ); 

	float bcxwjcUnc_tth = (tth->Integral() > 0) ? DC.getBTagUnc(tth, tth_bcxwjcUp, tth_bcxwjcDown) : 1.00; 
  	line.replace( line.find("TTHT") , 4 , string(Form("%.3f", bcxwjcUnc_tth)) ); 

	float bcxwjcUnc_ttz = (ttz->Integral() > 0) ? DC.getBTagUnc(ttz, ttz_bcxwjcUp, ttz_bcxwjcDown) : 1.00; 
  	line.replace( line.find("TTZT") , 4 , string(Form("%.3f", bcxwjcUnc_ttz)) ); 

	float bcxwjcUnc_ttw = (ttw->Integral() > 0) ? DC.getBTagUnc(ttw, ttw_bcxwjcUp, ttw_bcxwjcDown) : 1.00; 
  	line.replace( line.find("TTWT") , 4 , string(Form("%.3f", bcxwjcUnc_ttw)) ); 

        float bcxwjcUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_bcxwjcUp, wjet_bcxwjcDown) : 1.00;
        line.replace( line.find("WWWW") , 4 , string(Form("%.3f", bcxwjcUnc_wjet)) ); 
       
        float bcxwjcUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_bcxwjcUp, zjet_bcxwjcDown) : 1.00;
        line.replace( line.find("DDDD") , 4 , string(Form("%.3f", bcxwjcUnc_zjet)) ); 
        
        float bcxwjcUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_bcxwjcUp, stop_bcxwjcDown) : 1.00; 
        line.replace( line.find("SSSS") , 4 , string(Form("%.3f", bcxwjcUnc_stop)) ); 

        float bcxwjcUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_bcxwjcUp, vv_bcxwjcDown) : 1.00;
        line.replace( line.find("VVVV") , 4 , string(Form("%.3f", bcxwjcUnc_vv)) ); 
        out << line << endl;
      }
      else if(line.find("CMS_bcintp ")!=string::npos){

	stringstream ss(line); string systname; ss >> systname;
	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+hist_extn);

        float bcintpUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_bcintpUp, wh_bcintpDown) : 1.00;
        line.replace( line.find("HHHH") , 4 , string(Form("%.3f", bcintpUnc_wh)) );
        
        float bcintpUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_bcintpUp, ttbar_bcintpDown) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", bcintpUnc_ttbar)) ); 
        
	float bcintpUnc_ttg = (ttg->Integral() > 0) ? DC.getBTagUnc(ttg, ttg_bcintpUp, ttg_bcintpDown) : 1.00; 
  	line.replace( line.find("TTGT") , 4 , string(Form("%.3f", bcintpUnc_ttg)) ); 

	float bcintpUnc_tth = (tth->Integral() > 0) ? DC.getBTagUnc(tth, tth_bcintpUp, tth_bcintpDown) : 1.00; 
  	line.replace( line.find("TTHT") , 4 , string(Form("%.3f", bcintpUnc_tth)) ); 

	float bcintpUnc_ttz = (ttz->Integral() > 0) ? DC.getBTagUnc(ttz, ttz_bcintpUp, ttz_bcintpDown) : 1.00; 
  	line.replace( line.find("TTZT") , 4 , string(Form("%.3f", bcintpUnc_ttz)) ); 

	float bcintpUnc_ttw = (ttw->Integral() > 0) ? DC.getBTagUnc(ttw, ttw_bcintpUp, ttw_bcintpDown) : 1.00; 
  	line.replace( line.find("TTWT") , 4 , string(Form("%.3f", bcintpUnc_ttw)) ); 

        float bcintpUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_bcintpUp, wjet_bcintpDown) : 1.00;
        line.replace( line.find("WWWW") , 4 , string(Form("%.3f", bcintpUnc_wjet)) ); 
       
        float bcintpUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_bcintpUp, zjet_bcintpDown) : 1.00;
        line.replace( line.find("DDDD") , 4 , string(Form("%.3f", bcintpUnc_zjet)) ); 
        
        float bcintpUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_bcintpUp, stop_bcintpDown) : 1.00; 
        line.replace( line.find("SSSS") , 4 , string(Form("%.3f", bcintpUnc_stop)) ); 

        float bcintpUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_bcintpUp, vv_bcintpDown) : 1.00;
        line.replace( line.find("VVVV") , 4 , string(Form("%.3f", bcintpUnc_vv)) ); 
        out << line << endl;
      }
      else if(line.find("CMS_bcextp ")!=string::npos){

	float sf_bcextp = 1.0 ;

	stringstream ss(line); string systname; ss >> systname;
	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+hist_extn);

        float bcextpUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_bcextpUp, wh_bcextpDown) : 1.00;
        line.replace( line.find("HHHH") , 4 , string(Form("%.3f", sf_bcextp*bcextpUnc_wh)) );
        
        float bcextpUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_bcextpUp, ttbar_bcextpDown) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", sf_bcextp*bcextpUnc_ttbar)) ); 
        
	float bcextpUnc_ttg = (ttg->Integral() > 0) ? DC.getBTagUnc(ttg, ttg_bcextpUp, ttg_bcextpDown) : 1.00; 
  	line.replace( line.find("TTGT") , 4 , string(Form("%.3f", bcextpUnc_ttg)) ); 

	float bcextpUnc_tth = (tth->Integral() > 0) ? DC.getBTagUnc(tth, tth_bcextpUp, tth_bcextpDown) : 1.00; 
  	line.replace( line.find("TTHT") , 4 , string(Form("%.3f", bcextpUnc_tth)) ); 

	float bcextpUnc_ttz = (ttz->Integral() > 0) ? DC.getBTagUnc(ttz, ttz_bcextpUp, ttz_bcextpDown) : 1.00; 
  	line.replace( line.find("TTZT") , 4 , string(Form("%.3f", bcextpUnc_ttz)) ); 

	float bcextpUnc_ttw = (ttw->Integral() > 0) ? DC.getBTagUnc(ttw, ttw_bcextpUp, ttw_bcextpDown) : 1.00; 
  	line.replace( line.find("TTWT") , 4 , string(Form("%.3f", bcextpUnc_ttw)) ); 

        float bcextpUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_bcextpUp, wjet_bcextpDown) : 1.00;
        line.replace( line.find("WWWW") , 4 , string(Form("%.3f", sf_bcextp*bcextpUnc_wjet)) ); 
       
        float bcextpUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_bcextpUp, zjet_bcextpDown) : 1.00;
        line.replace( line.find("DDDD") , 4 , string(Form("%.3f", sf_bcextp*bcextpUnc_zjet)) ); 
        
        float bcextpUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_bcextpUp, stop_bcextpDown) : 1.00; 
        line.replace( line.find("SSSS") , 4 , string(Form("%.3f", sf_bcextp*bcextpUnc_stop)) ); 

        float bcextpUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_bcextpUp, vv_bcextpDown) : 1.00;
        line.replace( line.find("VVVV") , 4 , string(Form("%.3f", sf_bcextp*bcextpUnc_vv)) ); 
        out << line << endl;
      }
      else if(line.find("CMS_topPt ")!=string::npos){

	stringstream ss(line); string systname; ss >> systname;
	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+hist_extn);

        float topPtUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_topPtUp, wh_topPtDown) : 1.00;
        line.replace( line.find("HHHH") , 4 , string(Form("%.3f", topPtUnc_wh)) );
        
        float topPtUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_topPtUp, ttbar_topPtDown) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", topPtUnc_ttbar)) ); 
        out << line << endl;
	
      }
      // else if(line.find("CMS_stotpu ")!=string::npos){

      // 	stringstream ss(line); string systname; ss >> systname;
      // 	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+hist_extn);
	
      //   float stotpuUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_stotpuUp, wh_stotpuDown) : 1.00;
      //   line.replace( line.find("HHHH") , 4 , string(Form("%.3f", stotpuUnc_wh)) );
        
      //   float stotpuUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_stotpuUp, ttbar_stotpuDown) : 1.00; 
      //   line.replace( line.find("TTTT") , 4 , string(Form("%.3f", stotpuUnc_ttbar)) ); 
        
      //   float stotpuUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_stotpuUp, wjet_stotpuDown) : 1.00;
      //   line.replace( line.find("WWWW") , 4 , string(Form("%.3f", stotpuUnc_wjet)) ); 
       
      //   float stotpuUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_stotpuUp, zjet_stotpuDown) : 1.00;
      //   line.replace( line.find("DDDD") , 4 , string(Form("%.3f", stotpuUnc_zjet)) ); 
        
      //   float stotpuUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_stotpuUp, stop_stotpuDown) : 1.00; 
      //   line.replace( line.find("SSSS") , 4 , string(Form("%.3f", stotpuUnc_stop)) ); 

      //   float stotpuUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_stotpuUp, vv_stotpuDown) : 1.00;
      //   line.replace( line.find("VVVV") , 4 , string(Form("%.3f", stotpuUnc_vv)) ); 
      //   out << line << endl;
      // }
      // else if(line.find("CMS_stotrel ")!=string::npos){

      // 	stringstream ss(line); string systname; ss >> systname;
      // 	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+hist_extn);
	
      //   float stotrelUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_stotrelUp, wh_stotrelDown) : 1.00;
      //   line.replace( line.find("HHHH") , 4 , string(Form("%.3f", stotrelUnc_wh)) );
        
      //   float stotrelUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_stotrelUp, ttbar_stotrelDown) : 1.00; 
      //   line.replace( line.find("TTTT") , 4 , string(Form("%.3f", stotrelUnc_ttbar)) ); 
        
      //   float stotrelUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_stotrelUp, wjet_stotrelDown) : 1.00;
      //   line.replace( line.find("WWWW") , 4 , string(Form("%.3f", stotrelUnc_wjet)) ); 
       
      //   float stotrelUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_stotrelUp, zjet_stotrelDown) : 1.00;
      //   line.replace( line.find("DDDD") , 4 , string(Form("%.3f", stotrelUnc_zjet)) ); 
        
      //   float stotrelUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_stotrelUp, stop_stotrelDown) : 1.00; 
      //   line.replace( line.find("SSSS") , 4 , string(Form("%.3f", stotrelUnc_stop)) ); 

      //   float stotrelUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_stotrelUp, vv_stotrelDown) : 1.00;
      //   line.replace( line.find("VVVV") , 4 , string(Form("%.3f", stotrelUnc_vv)) ); 
      //   out << line << endl;
      // }
      else if(line.find("CMS_flavorqcd ")!=string::npos){

	stringstream ss(line); string systname; ss >> systname;
	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+hist_extn);
	
        float flavorqcdUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_flavorqcdUp, wh_flavorqcdDown) : 1.00;
        line.replace( line.find("HHHH") , 4 , string(Form("%.3f", flavorqcdUnc_wh)) );
        
        float flavorqcdUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_flavorqcdUp, ttbar_flavorqcdDown) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", flavorqcdUnc_ttbar)) ); 
        
	float flavorqcdUnc_ttg = (ttg->Integral() > 0) ? DC.getBTagUnc(ttg, ttg_flavorqcdUp, ttg_flavorqcdDown) : 1.00; 
  	line.replace( line.find("TTGT") , 4 , string(Form("%.3f", flavorqcdUnc_ttg)) ); 

	float flavorqcdUnc_tth = (tth->Integral() > 0) ? DC.getBTagUnc(tth, tth_flavorqcdUp, tth_flavorqcdDown) : 1.00; 
  	line.replace( line.find("TTHT") , 4 , string(Form("%.3f", flavorqcdUnc_tth)) ); 

	float flavorqcdUnc_ttz = (ttz->Integral() > 0) ? DC.getBTagUnc(ttz, ttz_flavorqcdUp, ttz_flavorqcdDown) : 1.00; 
  	line.replace( line.find("TTZT") , 4 , string(Form("%.3f", flavorqcdUnc_ttz)) ); 

	float flavorqcdUnc_ttw = (ttw->Integral() > 0) ? DC.getBTagUnc(ttw, ttw_flavorqcdUp, ttw_flavorqcdDown) : 1.00; 
  	line.replace( line.find("TTWT") , 4 , string(Form("%.3f", flavorqcdUnc_ttw)) ); 

        float flavorqcdUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_flavorqcdUp, wjet_flavorqcdDown) : 1.00;
        line.replace( line.find("WWWW") , 4 , string(Form("%.3f", flavorqcdUnc_wjet)) ); 
       
        float flavorqcdUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_flavorqcdUp, zjet_flavorqcdDown) : 1.00;
        line.replace( line.find("DDDD") , 4 , string(Form("%.3f", flavorqcdUnc_zjet)) ); 
        
        float flavorqcdUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_flavorqcdUp, stop_flavorqcdDown) : 1.00; 
        line.replace( line.find("SSSS") , 4 , string(Form("%.3f", flavorqcdUnc_stop)) ); 

        float flavorqcdUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_flavorqcdUp, vv_flavorqcdDown) : 1.00;
        line.replace( line.find("VVVV") , 4 , string(Form("%.3f", flavorqcdUnc_vv)) ); 
        out << line << endl;
      }
      // else if(line.find("CMS_stotpt ")!=string::npos){

      // 	stringstream ss(line); string systname; ss >> systname;
      // 	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+hist_extn);
	
      //   float stotptUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_stotptUp, wh_stotptDown) : 1.00;
      //   line.replace( line.find("HHHH") , 4 , string(Form("%.3f", stotptUnc_wh)) );
        
      //   float stotptUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_stotptUp, ttbar_stotptDown) : 1.00; 
      //   line.replace( line.find("TTTT") , 4 , string(Form("%.3f", stotptUnc_ttbar)) ); 
        
      //   float stotptUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_stotptUp, wjet_stotptDown) : 1.00;
      //   line.replace( line.find("WWWW") , 4 , string(Form("%.3f", stotptUnc_wjet)) ); 
       
      //   float stotptUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_stotptUp, zjet_stotptDown) : 1.00;
      //   line.replace( line.find("DDDD") , 4 , string(Form("%.3f", stotptUnc_zjet)) ); 
        
      //   float stotptUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_stotptUp, stop_stotptDown) : 1.00; 
      //   line.replace( line.find("SSSS") , 4 , string(Form("%.3f", stotptUnc_stop)) ); 

      //   float stotptUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_stotptUp, vv_stotptDown) : 1.00;
      //   line.replace( line.find("VVVV") , 4 , string(Form("%.3f", stotptUnc_vv)) ); 
      //   out << line << endl;
      // }
      // else if(line.find("CMS_stotpt ")!=string::npos){

      // 	stringstream ss(line); string systname; ss >> systname;
      // 	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+hist_extn);
	
      //   float stotptUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_stotptUp, wh_stotptDown) : 1.00;
      //   line.replace( line.find("HHHH") , 4 , string(Form("%.3f", stotptUnc_wh)) );
        
      //   float stotptUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_stotptUp, ttbar_stotptDown) : 1.00; 
      //   line.replace( line.find("TTTT") , 4 , string(Form("%.3f", stotptUnc_ttbar)) ); 
        
      //   float stotptUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_stotptUp, wjet_stotptDown) : 1.00;
      //   line.replace( line.find("WWWW") , 4 , string(Form("%.3f", stotptUnc_wjet)) ); 
       
      //   float stotptUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_stotptUp, zjet_stotptDown) : 1.00;
      //   line.replace( line.find("DDDD") , 4 , string(Form("%.3f", stotptUnc_zjet)) ); 
        
      //   float stotptUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_stotptUp, stop_stotptDown) : 1.00; 
      //   line.replace( line.find("SSSS") , 4 , string(Form("%.3f", stotptUnc_stop)) ); 

      //   float stotptUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_stotptUp, vv_stotptDown) : 1.00;
      //   line.replace( line.find("VVVV") , 4 , string(Form("%.3f", stotptUnc_vv)) ); 
      //   out << line << endl;
      // }
      // else if(line.find("CMS_stotscale ")!=string::npos){

      // 	stringstream ss(line); string systname; ss >> systname;
      // 	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+hist_extn);
	
      //   float stotscaleUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_stotscaleUp, wh_stotscaleDown) : 1.00;
      //   line.replace( line.find("HHHH") , 4 , string(Form("%.3f", stotscaleUnc_wh)) );
        
      //   float stotscaleUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_stotscaleUp, ttbar_stotscaleDown) : 1.00; 
      //   line.replace( line.find("TTTT") , 4 , string(Form("%.3f", stotscaleUnc_ttbar)) ); 
        
      //   float stotscaleUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_stotscaleUp, wjet_stotscaleDown) : 1.00;
      //   line.replace( line.find("WWWW") , 4 , string(Form("%.3f", stotscaleUnc_wjet)) ); 
       
      //   float stotscaleUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_stotscaleUp, zjet_stotscaleDown) : 1.00;
      //   line.replace( line.find("DDDD") , 4 , string(Form("%.3f", stotscaleUnc_zjet)) ); 
        
      //   float stotscaleUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_stotscaleUp, stop_stotscaleDown) : 1.00; 
      //   line.replace( line.find("SSSS") , 4 , string(Form("%.3f", stotscaleUnc_stop)) ); 

      //   float stotscaleUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_stotscaleUp, vv_stotscaleDown) : 1.00;
      //   line.replace( line.find("VVVV") , 4 , string(Form("%.3f", stotscaleUnc_vv)) ); 
      //   out << line << endl;
      // }
      else if(line.find("CMS_absmpfb ")!=string::npos){

      	stringstream ss(line); string systname; ss >> systname;
      	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+hist_extn);
	
        float absmpfbUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_absmpfbUp, wh_absmpfbDown) : 1.00;
        line.replace( line.find("HHHH") , 4 , string(Form("%.3f", absmpfbUnc_wh)) );
        
        float absmpfbUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_absmpfbUp, ttbar_absmpfbDown) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", absmpfbUnc_ttbar)) ); 
        
	float absmpfbUnc_ttg = (ttg->Integral() > 0) ? DC.getBTagUnc(ttg, ttg_absmpfbUp, ttg_absmpfbDown) : 1.00; 
  	line.replace( line.find("TTGT") , 4 , string(Form("%.3f", absmpfbUnc_ttg)) ); 

	float absmpfbUnc_tth = (tth->Integral() > 0) ? DC.getBTagUnc(tth, tth_absmpfbUp, tth_absmpfbDown) : 1.00; 
  	line.replace( line.find("TTHT") , 4 , string(Form("%.3f", absmpfbUnc_tth)) ); 

	float absmpfbUnc_ttz = (ttz->Integral() > 0) ? DC.getBTagUnc(ttz, ttz_absmpfbUp, ttz_absmpfbDown) : 1.00; 
  	line.replace( line.find("TTZT") , 4 , string(Form("%.3f", absmpfbUnc_ttz)) ); 

	float absmpfbUnc_ttw = (ttw->Integral() > 0) ? DC.getBTagUnc(ttw, ttw_absmpfbUp, ttw_absmpfbDown) : 1.00; 
  	line.replace( line.find("TTWT") , 4 , string(Form("%.3f", absmpfbUnc_ttw)) ); 

        float absmpfbUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_absmpfbUp, wjet_absmpfbDown) : 1.00;
        line.replace( line.find("WWWW") , 4 , string(Form("%.3f", absmpfbUnc_wjet)) ); 
       
        float absmpfbUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_absmpfbUp, zjet_absmpfbDown) : 1.00;
        line.replace( line.find("DDDD") , 4 , string(Form("%.3f", absmpfbUnc_zjet)) ); 
        
        float absmpfbUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_absmpfbUp, stop_absmpfbDown) : 1.00; 
        line.replace( line.find("SSSS") , 4 , string(Form("%.3f", absmpfbUnc_stop)) ); 

        float absmpfbUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_absmpfbUp, vv_absmpfbDown) : 1.00;
        line.replace( line.find("VVVV") , 4 , string(Form("%.3f", absmpfbUnc_vv)) ); 
        out << line << endl;
      }
      else if(line.find("CMS_absscl ")!=string::npos){

      	stringstream ss(line); string systname; ss >> systname;
      	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+hist_extn);
	
        float abssclUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_abssclUp, wh_abssclDown) : 1.00;
        line.replace( line.find("HHHH") , 4 , string(Form("%.3f", abssclUnc_wh)) );
        
        float abssclUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_abssclUp, ttbar_abssclDown) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", abssclUnc_ttbar)) ); 
        
	float abssclUnc_ttg = (ttg->Integral() > 0) ? DC.getBTagUnc(ttg, ttg_abssclUp, ttg_abssclDown) : 1.00; 
  	line.replace( line.find("TTGT") , 4 , string(Form("%.3f", abssclUnc_ttg)) ); 

	float abssclUnc_tth = (tth->Integral() > 0) ? DC.getBTagUnc(tth, tth_abssclUp, tth_abssclDown) : 1.00; 
  	line.replace( line.find("TTHT") , 4 , string(Form("%.3f", abssclUnc_tth)) ); 

	float abssclUnc_ttz = (ttz->Integral() > 0) ? DC.getBTagUnc(ttz, ttz_abssclUp, ttz_abssclDown) : 1.00; 
  	line.replace( line.find("TTZT") , 4 , string(Form("%.3f", abssclUnc_ttz)) ); 

	float abssclUnc_ttw = (ttw->Integral() > 0) ? DC.getBTagUnc(ttw, ttw_abssclUp, ttw_abssclDown) : 1.00; 
  	line.replace( line.find("TTWT") , 4 , string(Form("%.3f", abssclUnc_ttw)) ); 

        float abssclUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_abssclUp, wjet_abssclDown) : 1.00;
        line.replace( line.find("WWWW") , 4 , string(Form("%.3f", abssclUnc_wjet)) ); 
       
        float abssclUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_abssclUp, zjet_abssclDown) : 1.00;
        line.replace( line.find("DDDD") , 4 , string(Form("%.3f", abssclUnc_zjet)) ); 
        
        float abssclUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_abssclUp, stop_abssclDown) : 1.00; 
        line.replace( line.find("SSSS") , 4 , string(Form("%.3f", abssclUnc_stop)) ); 

        float abssclUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_abssclUp, vv_abssclDown) : 1.00;
        line.replace( line.find("VVVV") , 4 , string(Form("%.3f", abssclUnc_vv)) ); 
        out << line << endl;
      }
      else if(line.find("CMS_absstat ")!=string::npos){

      	stringstream ss(line); string systname; ss >> systname;
      	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+uncorr_extn);
	
        float absstatUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_absstatUp, wh_absstatDown) : 1.00;
        line.replace( line.find("HHHH") , 4 , string(Form("%.3f", absstatUnc_wh)) );
        
        float absstatUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_absstatUp, ttbar_absstatDown) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", absstatUnc_ttbar)) ); 
        
	float absstatUnc_ttg = (ttg->Integral() > 0) ? DC.getBTagUnc(ttg, ttg_absstatUp, ttg_absstatDown) : 1.00; 
  	line.replace( line.find("TTGT") , 4 , string(Form("%.3f", absstatUnc_ttg)) ); 

	float absstatUnc_tth = (tth->Integral() > 0) ? DC.getBTagUnc(tth, tth_absstatUp, tth_absstatDown) : 1.00; 
  	line.replace( line.find("TTHT") , 4 , string(Form("%.3f", absstatUnc_tth)) ); 

	float absstatUnc_ttz = (ttz->Integral() > 0) ? DC.getBTagUnc(ttz, ttz_absstatUp, ttz_absstatDown) : 1.00; 
  	line.replace( line.find("TTZT") , 4 , string(Form("%.3f", absstatUnc_ttz)) ); 

	float absstatUnc_ttw = (ttw->Integral() > 0) ? DC.getBTagUnc(ttw, ttw_absstatUp, ttw_absstatDown) : 1.00; 
  	line.replace( line.find("TTWT") , 4 , string(Form("%.3f", absstatUnc_ttw)) ); 

        float absstatUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_absstatUp, wjet_absstatDown) : 1.00;
        line.replace( line.find("WWWW") , 4 , string(Form("%.3f", absstatUnc_wjet)) ); 
       
        float absstatUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_absstatUp, zjet_absstatDown) : 1.00;
        line.replace( line.find("DDDD") , 4 , string(Form("%.3f", absstatUnc_zjet)) ); 
        
        float absstatUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_absstatUp, stop_absstatDown) : 1.00; 
        line.replace( line.find("SSSS") , 4 , string(Form("%.3f", absstatUnc_stop)) ); 

        float absstatUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_absstatUp, vv_absstatDown) : 1.00;
        line.replace( line.find("VVVV") , 4 , string(Form("%.3f", absstatUnc_vv)) ); 
        out << line << endl;
      }
      else if(line.find("CMS_frag ")!=string::npos){

      	stringstream ss(line); string systname; ss >> systname;
      	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+hist_extn);
	
        float fragUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_fragUp, wh_fragDown) : 1.00;
        line.replace( line.find("HHHH") , 4 , string(Form("%.3f", fragUnc_wh)) );
        
        float fragUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_fragUp, ttbar_fragDown) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", fragUnc_ttbar)) ); 
        
	float fragUnc_ttg = (ttg->Integral() > 0) ? DC.getBTagUnc(ttg, ttg_fragUp, ttg_fragDown) : 1.00; 
  	line.replace( line.find("TTGT") , 4 , string(Form("%.3f", fragUnc_ttg)) ); 

	float fragUnc_tth = (tth->Integral() > 0) ? DC.getBTagUnc(tth, tth_fragUp, tth_fragDown) : 1.00; 
  	line.replace( line.find("TTHT") , 4 , string(Form("%.3f", fragUnc_tth)) ); 

	float fragUnc_ttz = (ttz->Integral() > 0) ? DC.getBTagUnc(ttz, ttz_fragUp, ttz_fragDown) : 1.00; 
  	line.replace( line.find("TTZT") , 4 , string(Form("%.3f", fragUnc_ttz)) ); 

	float fragUnc_ttw = (ttw->Integral() > 0) ? DC.getBTagUnc(ttw, ttw_fragUp, ttw_fragDown) : 1.00; 
  	line.replace( line.find("TTWT") , 4 , string(Form("%.3f", fragUnc_ttw)) ); 

        float fragUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_fragUp, wjet_fragDown) : 1.00;
        line.replace( line.find("WWWW") , 4 , string(Form("%.3f", fragUnc_wjet)) ); 
       
        float fragUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_fragUp, zjet_fragDown) : 1.00;
        line.replace( line.find("DDDD") , 4 , string(Form("%.3f", fragUnc_zjet)) ); 
        
        float fragUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_fragUp, stop_fragDown) : 1.00; 
        line.replace( line.find("SSSS") , 4 , string(Form("%.3f", fragUnc_stop)) ); 

        float fragUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_fragUp, vv_fragDown) : 1.00;
        line.replace( line.find("VVVV") , 4 , string(Form("%.3f", fragUnc_vv)) ); 
        out << line << endl;
      }
      else if(line.find("CMS_pudatamc ")!=string::npos){

      	stringstream ss(line); string systname; ss >> systname;
      	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+hist_extn);
	
        float pudatamcUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_pudatamcUp, wh_pudatamcDown) : 1.00;
        line.replace( line.find("HHHH") , 4 , string(Form("%.3f", pudatamcUnc_wh)) );
        
        float pudatamcUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_pudatamcUp, ttbar_pudatamcDown) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", pudatamcUnc_ttbar)) ); 
        
	float pudatamcUnc_ttg = (ttg->Integral() > 0) ? DC.getBTagUnc(ttg, ttg_pudatamcUp, ttg_pudatamcDown) : 1.00; 
  	line.replace( line.find("TTGT") , 4 , string(Form("%.3f", pudatamcUnc_ttg)) ); 

	float pudatamcUnc_tth = (tth->Integral() > 0) ? DC.getBTagUnc(tth, tth_pudatamcUp, tth_pudatamcDown) : 1.00; 
  	line.replace( line.find("TTHT") , 4 , string(Form("%.3f", pudatamcUnc_tth)) ); 

	float pudatamcUnc_ttz = (ttz->Integral() > 0) ? DC.getBTagUnc(ttz, ttz_pudatamcUp, ttz_pudatamcDown) : 1.00; 
  	line.replace( line.find("TTZT") , 4 , string(Form("%.3f", pudatamcUnc_ttz)) ); 

	float pudatamcUnc_ttw = (ttw->Integral() > 0) ? DC.getBTagUnc(ttw, ttw_pudatamcUp, ttw_pudatamcDown) : 1.00; 
  	line.replace( line.find("TTWT") , 4 , string(Form("%.3f", pudatamcUnc_ttw)) ); 

        float pudatamcUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_pudatamcUp, wjet_pudatamcDown) : 1.00;
        line.replace( line.find("WWWW") , 4 , string(Form("%.3f", pudatamcUnc_wjet)) ); 
       
        float pudatamcUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_pudatamcUp, zjet_pudatamcDown) : 1.00;
        line.replace( line.find("DDDD") , 4 , string(Form("%.3f", pudatamcUnc_zjet)) ); 
        
        float pudatamcUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_pudatamcUp, stop_pudatamcDown) : 1.00; 
        line.replace( line.find("SSSS") , 4 , string(Form("%.3f", pudatamcUnc_stop)) ); 

        float pudatamcUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_pudatamcUp, vv_pudatamcDown) : 1.00;
        line.replace( line.find("VVVV") , 4 , string(Form("%.3f", pudatamcUnc_vv)) ); 
        out << line << endl;
      }
      else if(line.find("CMS_puptbb ")!=string::npos){

      	stringstream ss(line); string systname; ss >> systname;
      	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+hist_extn);
	
        float puptbbUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_puptbbUp, wh_puptbbDown) : 1.00;
        line.replace( line.find("HHHH") , 4 , string(Form("%.3f", puptbbUnc_wh)) );
        
        float puptbbUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_puptbbUp, ttbar_puptbbDown) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", puptbbUnc_ttbar)) ); 
        
	float puptbbUnc_ttg = (ttg->Integral() > 0) ? DC.getBTagUnc(ttg, ttg_puptbbUp, ttg_puptbbDown) : 1.00; 
  	line.replace( line.find("TTGT") , 4 , string(Form("%.3f", puptbbUnc_ttg)) ); 

	float puptbbUnc_tth = (tth->Integral() > 0) ? DC.getBTagUnc(tth, tth_puptbbUp, tth_puptbbDown) : 1.00; 
  	line.replace( line.find("TTHT") , 4 , string(Form("%.3f", puptbbUnc_tth)) ); 

	float puptbbUnc_ttz = (ttz->Integral() > 0) ? DC.getBTagUnc(ttz, ttz_puptbbUp, ttz_puptbbDown) : 1.00; 
  	line.replace( line.find("TTZT") , 4 , string(Form("%.3f", puptbbUnc_ttz)) ); 

	float puptbbUnc_ttw = (ttw->Integral() > 0) ? DC.getBTagUnc(ttw, ttw_puptbbUp, ttw_puptbbDown) : 1.00; 
  	line.replace( line.find("TTWT") , 4 , string(Form("%.3f", puptbbUnc_ttw)) ); 

        float puptbbUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_puptbbUp, wjet_puptbbDown) : 1.00;
        line.replace( line.find("WWWW") , 4 , string(Form("%.3f", puptbbUnc_wjet)) ); 
       
        float puptbbUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_puptbbUp, zjet_puptbbDown) : 1.00;
        line.replace( line.find("DDDD") , 4 , string(Form("%.3f", puptbbUnc_zjet)) ); 
        
        float puptbbUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_puptbbUp, stop_puptbbDown) : 1.00; 
        line.replace( line.find("SSSS") , 4 , string(Form("%.3f", puptbbUnc_stop)) ); 

        float puptbbUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_puptbbUp, vv_puptbbDown) : 1.00;
        line.replace( line.find("VVVV") , 4 , string(Form("%.3f", puptbbUnc_vv)) ); 
        out << line << endl;
      }
      else if(line.find("CMS_puptec1 ")!=string::npos){

      	stringstream ss(line); string systname; ss >> systname;
      	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+hist_extn);
	
        float puptec1Unc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_puptec1Up, wh_puptec1Down) : 1.00;
        line.replace( line.find("HHHH") , 4 , string(Form("%.3f", puptec1Unc_wh)) );
        
        float puptec1Unc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_puptec1Up, ttbar_puptec1Down) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", puptec1Unc_ttbar)) ); 
        
	float puptec1Unc_ttg = (ttg->Integral() > 0) ? DC.getBTagUnc(ttg, ttg_puptec1Up, ttg_puptec1Down) : 1.00; 
  	line.replace( line.find("TTGT") , 4 , string(Form("%.3f", puptec1Unc_ttg)) ); 

	float puptec1Unc_tth = (tth->Integral() > 0) ? DC.getBTagUnc(tth, tth_puptec1Up, tth_puptec1Down) : 1.00; 
  	line.replace( line.find("TTHT") , 4 , string(Form("%.3f", puptec1Unc_tth)) ); 

	float puptec1Unc_ttz = (ttz->Integral() > 0) ? DC.getBTagUnc(ttz, ttz_puptec1Up, ttz_puptec1Down) : 1.00; 
  	line.replace( line.find("TTZT") , 4 , string(Form("%.3f", puptec1Unc_ttz)) ); 

	float puptec1Unc_ttw = (ttw->Integral() > 0) ? DC.getBTagUnc(ttw, ttw_puptec1Up, ttw_puptec1Down) : 1.00; 
  	line.replace( line.find("TTWT") , 4 , string(Form("%.3f", puptec1Unc_ttw)) ); 

        float puptec1Unc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_puptec1Up, wjet_puptec1Down) : 1.00;
        line.replace( line.find("WWWW") , 4 , string(Form("%.3f", puptec1Unc_wjet)) ); 
       
        float puptec1Unc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_puptec1Up, zjet_puptec1Down) : 1.00;
        line.replace( line.find("DDDD") , 4 , string(Form("%.3f", puptec1Unc_zjet)) ); 
        
        float puptec1Unc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_puptec1Up, stop_puptec1Down) : 1.00; 
        line.replace( line.find("SSSS") , 4 , string(Form("%.3f", puptec1Unc_stop)) ); 

        float puptec1Unc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_puptec1Up, vv_puptec1Down) : 1.00;
        line.replace( line.find("VVVV") , 4 , string(Form("%.3f", puptec1Unc_vv)) ); 
        out << line << endl;
      }
      else if(line.find("CMS_puptec2 ")!=string::npos){

      	stringstream ss(line); string systname; ss >> systname;
      	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+hist_extn);
	
        float puptec2Unc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_puptec2Up, wh_puptec2Down) : 1.00;
        line.replace( line.find("HHHH") , 4 , string(Form("%.3f", puptec2Unc_wh)) );
        
        float puptec2Unc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_puptec2Up, ttbar_puptec2Down) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", puptec2Unc_ttbar)) ); 
        
	float puptec2Unc_ttg = (ttg->Integral() > 0) ? DC.getBTagUnc(ttg, ttg_puptec2Up, ttg_puptec2Down) : 1.00; 
  	line.replace( line.find("TTGT") , 4 , string(Form("%.3f", puptec2Unc_ttg)) ); 

	float puptec2Unc_tth = (tth->Integral() > 0) ? DC.getBTagUnc(tth, tth_puptec2Up, tth_puptec2Down) : 1.00; 
  	line.replace( line.find("TTHT") , 4 , string(Form("%.3f", puptec2Unc_tth)) ); 

	float puptec2Unc_ttz = (ttz->Integral() > 0) ? DC.getBTagUnc(ttz, ttz_puptec2Up, ttz_puptec2Down) : 1.00; 
  	line.replace( line.find("TTZT") , 4 , string(Form("%.3f", puptec2Unc_ttz)) ); 

	float puptec2Unc_ttw = (ttw->Integral() > 0) ? DC.getBTagUnc(ttw, ttw_puptec2Up, ttw_puptec2Down) : 1.00; 
  	line.replace( line.find("TTWT") , 4 , string(Form("%.3f", puptec2Unc_ttw)) ); 

        float puptec2Unc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_puptec2Up, wjet_puptec2Down) : 1.00;
        line.replace( line.find("WWWW") , 4 , string(Form("%.3f", puptec2Unc_wjet)) ); 
       
        float puptec2Unc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_puptec2Up, zjet_puptec2Down) : 1.00;
        line.replace( line.find("DDDD") , 4 , string(Form("%.3f", puptec2Unc_zjet)) ); 
        
        float puptec2Unc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_puptec2Up, stop_puptec2Down) : 1.00; 
        line.replace( line.find("SSSS") , 4 , string(Form("%.3f", puptec2Unc_stop)) ); 

        float puptec2Unc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_puptec2Up, vv_puptec2Down) : 1.00;
        line.replace( line.find("VVVV") , 4 , string(Form("%.3f", puptec2Unc_vv)) ); 
        out << line << endl;
      }
      else if(line.find("CMS_pupthf ")!=string::npos){

      	stringstream ss(line); string systname; ss >> systname;
      	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+hist_extn);
	
        float pupthfUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_pupthfUp, wh_pupthfDown) : 1.00;
        line.replace( line.find("HHHH") , 4 , string(Form("%.3f", pupthfUnc_wh)) );
        
        float pupthfUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_pupthfUp, ttbar_pupthfDown) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", pupthfUnc_ttbar)) ); 
        
	float pupthfUnc_ttg = (ttg->Integral() > 0) ? DC.getBTagUnc(ttg, ttg_pupthfUp, ttg_pupthfDown) : 1.00; 
  	line.replace( line.find("TTGT") , 4 , string(Form("%.3f", pupthfUnc_ttg)) ); 

	float pupthfUnc_tth = (tth->Integral() > 0) ? DC.getBTagUnc(tth, tth_pupthfUp, tth_pupthfDown) : 1.00; 
  	line.replace( line.find("TTHT") , 4 , string(Form("%.3f", pupthfUnc_tth)) ); 

	float pupthfUnc_ttz = (ttz->Integral() > 0) ? DC.getBTagUnc(ttz, ttz_pupthfUp, ttz_pupthfDown) : 1.00; 
  	line.replace( line.find("TTZT") , 4 , string(Form("%.3f", pupthfUnc_ttz)) ); 

	float pupthfUnc_ttw = (ttw->Integral() > 0) ? DC.getBTagUnc(ttw, ttw_pupthfUp, ttw_pupthfDown) : 1.00; 
  	line.replace( line.find("TTWT") , 4 , string(Form("%.3f", pupthfUnc_ttw)) ); 

        float pupthfUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_pupthfUp, wjet_pupthfDown) : 1.00;
        line.replace( line.find("WWWW") , 4 , string(Form("%.3f", pupthfUnc_wjet)) ); 
       
        float pupthfUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_pupthfUp, zjet_pupthfDown) : 1.00;
        line.replace( line.find("DDDD") , 4 , string(Form("%.3f", pupthfUnc_zjet)) ); 
        
        float pupthfUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_pupthfUp, stop_pupthfDown) : 1.00; 
        line.replace( line.find("SSSS") , 4 , string(Form("%.3f", pupthfUnc_stop)) ); 

        float pupthfUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_pupthfUp, vv_pupthfDown) : 1.00;
        line.replace( line.find("VVVV") , 4 , string(Form("%.3f", pupthfUnc_vv)) ); 
        out << line << endl;
      }
      else if(line.find("CMS_puptref ")!=string::npos){

      	stringstream ss(line); string systname; ss >> systname;
      	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+hist_extn);
	
        float puptrefUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_puptrefUp, wh_puptrefDown) : 1.00;
        line.replace( line.find("HHHH") , 4 , string(Form("%.3f", puptrefUnc_wh)) );
        
        float puptrefUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_puptrefUp, ttbar_puptrefDown) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", puptrefUnc_ttbar)) ); 
        
	float puptrefUnc_ttg = (ttg->Integral() > 0) ? DC.getBTagUnc(ttg, ttg_puptrefUp, ttg_puptrefDown) : 1.00; 
  	line.replace( line.find("TTGT") , 4 , string(Form("%.3f", puptrefUnc_ttg)) ); 

	float puptrefUnc_tth = (tth->Integral() > 0) ? DC.getBTagUnc(tth, tth_puptrefUp, tth_puptrefDown) : 1.00; 
  	line.replace( line.find("TTHT") , 4 , string(Form("%.3f", puptrefUnc_tth)) ); 

	float puptrefUnc_ttz = (ttz->Integral() > 0) ? DC.getBTagUnc(ttz, ttz_puptrefUp, ttz_puptrefDown) : 1.00; 
  	line.replace( line.find("TTZT") , 4 , string(Form("%.3f", puptrefUnc_ttz)) ); 

	float puptrefUnc_ttw = (ttw->Integral() > 0) ? DC.getBTagUnc(ttw, ttw_puptrefUp, ttw_puptrefDown) : 1.00; 
  	line.replace( line.find("TTWT") , 4 , string(Form("%.3f", puptrefUnc_ttw)) ); 

        float puptrefUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_puptrefUp, wjet_puptrefDown) : 1.00;
        line.replace( line.find("WWWW") , 4 , string(Form("%.3f", puptrefUnc_wjet)) ); 
       
        float puptrefUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_puptrefUp, zjet_puptrefDown) : 1.00;
        line.replace( line.find("DDDD") , 4 , string(Form("%.3f", puptrefUnc_zjet)) ); 
        
        float puptrefUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_puptrefUp, stop_puptrefDown) : 1.00; 
        line.replace( line.find("SSSS") , 4 , string(Form("%.3f", puptrefUnc_stop)) ); 

        float puptrefUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_puptrefUp, vv_puptrefDown) : 1.00;
        line.replace( line.find("VVVV") , 4 , string(Form("%.3f", puptrefUnc_vv)) ); 
        out << line << endl;
      }
      else if(line.find("CMS_relfsr ")!=string::npos){

      	stringstream ss(line); string systname; ss >> systname;
      	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+hist_extn);
	
        float relfsrUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_relfsrUp, wh_relfsrDown) : 1.00;
        line.replace( line.find("HHHH") , 4 , string(Form("%.3f", relfsrUnc_wh)) );
        
        float relfsrUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_relfsrUp, ttbar_relfsrDown) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", relfsrUnc_ttbar)) ); 
        
	float relfsrUnc_ttg = (ttg->Integral() > 0) ? DC.getBTagUnc(ttg, ttg_relfsrUp, ttg_relfsrDown) : 1.00; 
  	line.replace( line.find("TTGT") , 4 , string(Form("%.3f", relfsrUnc_ttg)) ); 

	float relfsrUnc_tth = (tth->Integral() > 0) ? DC.getBTagUnc(tth, tth_relfsrUp, tth_relfsrDown) : 1.00; 
  	line.replace( line.find("TTHT") , 4 , string(Form("%.3f", relfsrUnc_tth)) ); 

	float relfsrUnc_ttz = (ttz->Integral() > 0) ? DC.getBTagUnc(ttz, ttz_relfsrUp, ttz_relfsrDown) : 1.00; 
  	line.replace( line.find("TTZT") , 4 , string(Form("%.3f", relfsrUnc_ttz)) ); 

	float relfsrUnc_ttw = (ttw->Integral() > 0) ? DC.getBTagUnc(ttw, ttw_relfsrUp, ttw_relfsrDown) : 1.00; 
  	line.replace( line.find("TTWT") , 4 , string(Form("%.3f", relfsrUnc_ttw)) ); 

        float relfsrUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_relfsrUp, wjet_relfsrDown) : 1.00;
        line.replace( line.find("WWWW") , 4 , string(Form("%.3f", relfsrUnc_wjet)) ); 
       
        float relfsrUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_relfsrUp, zjet_relfsrDown) : 1.00;
        line.replace( line.find("DDDD") , 4 , string(Form("%.3f", relfsrUnc_zjet)) ); 
        
        float relfsrUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_relfsrUp, stop_relfsrDown) : 1.00; 
        line.replace( line.find("SSSS") , 4 , string(Form("%.3f", relfsrUnc_stop)) ); 

        float relfsrUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_relfsrUp, vv_relfsrDown) : 1.00;
        line.replace( line.find("VVVV") , 4 , string(Form("%.3f", relfsrUnc_vv)) ); 
        out << line << endl;
      }
      else if(line.find("CMS_relbal ")!=string::npos){

      	stringstream ss(line); string systname; ss >> systname;
      	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+hist_extn);
	
        float relbalUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_relbalUp, wh_relbalDown) : 1.00;
        line.replace( line.find("HHHH") , 4 , string(Form("%.3f", relbalUnc_wh)) );
        
        float relbalUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_relbalUp, ttbar_relbalDown) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", relbalUnc_ttbar)) ); 
        
	float relbalUnc_ttg = (ttg->Integral() > 0) ? DC.getBTagUnc(ttg, ttg_relbalUp, ttg_relbalDown) : 1.00; 
  	line.replace( line.find("TTGT") , 4 , string(Form("%.3f", relbalUnc_ttg)) ); 

	float relbalUnc_tth = (tth->Integral() > 0) ? DC.getBTagUnc(tth, tth_relbalUp, tth_relbalDown) : 1.00; 
  	line.replace( line.find("TTHT") , 4 , string(Form("%.3f", relbalUnc_tth)) ); 

	float relbalUnc_ttz = (ttz->Integral() > 0) ? DC.getBTagUnc(ttz, ttz_relbalUp, ttz_relbalDown) : 1.00; 
  	line.replace( line.find("TTZT") , 4 , string(Form("%.3f", relbalUnc_ttz)) ); 

	float relbalUnc_ttw = (ttw->Integral() > 0) ? DC.getBTagUnc(ttw, ttw_relbalUp, ttw_relbalDown) : 1.00; 
  	line.replace( line.find("TTWT") , 4 , string(Form("%.3f", relbalUnc_ttw)) ); 

        float relbalUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_relbalUp, wjet_relbalDown) : 1.00;
        line.replace( line.find("WWWW") , 4 , string(Form("%.3f", relbalUnc_wjet)) ); 
       
        float relbalUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_relbalUp, zjet_relbalDown) : 1.00;
        line.replace( line.find("DDDD") , 4 , string(Form("%.3f", relbalUnc_zjet)) ); 
        
        float relbalUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_relbalUp, stop_relbalDown) : 1.00; 
        line.replace( line.find("SSSS") , 4 , string(Form("%.3f", relbalUnc_stop)) ); 

        float relbalUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_relbalUp, vv_relbalDown) : 1.00;
        line.replace( line.find("VVVV") , 4 , string(Form("%.3f", relbalUnc_vv)) ); 
        out << line << endl;
      }
      else if(line.find("CMS_relsample ")!=string::npos){

      	stringstream ss(line); string systname; ss >> systname;
      	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+uncorr_extn);
	
        float relsampleUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_relsampleUp, wh_relsampleDown) : 1.00;
        line.replace( line.find("HHHH") , 4 , string(Form("%.3f", relsampleUnc_wh)) );
        
        float relsampleUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_relsampleUp, ttbar_relsampleDown) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", relsampleUnc_ttbar)) ); 
        
	float relsampleUnc_ttg = (ttg->Integral() > 0) ? DC.getBTagUnc(ttg, ttg_relsampleUp, ttg_relsampleDown) : 1.00; 
  	line.replace( line.find("TTGT") , 4 , string(Form("%.3f", relsampleUnc_ttg)) ); 

	float relsampleUnc_tth = (tth->Integral() > 0) ? DC.getBTagUnc(tth, tth_relsampleUp, tth_relsampleDown) : 1.00; 
  	line.replace( line.find("TTHT") , 4 , string(Form("%.3f", relsampleUnc_tth)) ); 

	float relsampleUnc_ttz = (ttz->Integral() > 0) ? DC.getBTagUnc(ttz, ttz_relsampleUp, ttz_relsampleDown) : 1.00; 
  	line.replace( line.find("TTZT") , 4 , string(Form("%.3f", relsampleUnc_ttz)) ); 

	float relsampleUnc_ttw = (ttw->Integral() > 0) ? DC.getBTagUnc(ttw, ttw_relsampleUp, ttw_relsampleDown) : 1.00; 
  	line.replace( line.find("TTWT") , 4 , string(Form("%.3f", relsampleUnc_ttw)) ); 

        float relsampleUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_relsampleUp, wjet_relsampleDown) : 1.00;
        line.replace( line.find("WWWW") , 4 , string(Form("%.3f", relsampleUnc_wjet)) ); 
       
        float relsampleUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_relsampleUp, zjet_relsampleDown) : 1.00;
        line.replace( line.find("DDDD") , 4 , string(Form("%.3f", relsampleUnc_zjet)) ); 
        
        float relsampleUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_relsampleUp, stop_relsampleDown) : 1.00; 
        line.replace( line.find("SSSS") , 4 , string(Form("%.3f", relsampleUnc_stop)) ); 

        float relsampleUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_relsampleUp, vv_relsampleDown) : 1.00;
        line.replace( line.find("VVVV") , 4 , string(Form("%.3f", relsampleUnc_vv)) ); 
        out << line << endl;
      }
      else if(line.find("CMS_reljerec1 ")!=string::npos){

      	stringstream ss(line); string systname; ss >> systname;
      	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+uncorr_extn);
	
        float reljerec1Unc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_reljerec1Up, wh_reljerec1Down) : 1.00;
        line.replace( line.find("HHHH") , 4 , string(Form("%.3f", reljerec1Unc_wh)) );
        
        float reljerec1Unc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_reljerec1Up, ttbar_reljerec1Down) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", reljerec1Unc_ttbar)) ); 
        
	float reljerec1Unc_ttg = (ttg->Integral() > 0) ? DC.getBTagUnc(ttg, ttg_reljerec1Up, ttg_reljerec1Down) : 1.00; 
  	line.replace( line.find("TTGT") , 4 , string(Form("%.3f", reljerec1Unc_ttg)) ); 

	float reljerec1Unc_tth = (tth->Integral() > 0) ? DC.getBTagUnc(tth, tth_reljerec1Up, tth_reljerec1Down) : 1.00; 
  	line.replace( line.find("TTHT") , 4 , string(Form("%.3f", reljerec1Unc_tth)) ); 

	float reljerec1Unc_ttz = (ttz->Integral() > 0) ? DC.getBTagUnc(ttz, ttz_reljerec1Up, ttz_reljerec1Down) : 1.00; 
  	line.replace( line.find("TTZT") , 4 , string(Form("%.3f", reljerec1Unc_ttz)) ); 

	float reljerec1Unc_ttw = (ttw->Integral() > 0) ? DC.getBTagUnc(ttw, ttw_reljerec1Up, ttw_reljerec1Down) : 1.00; 
  	line.replace( line.find("TTWT") , 4 , string(Form("%.3f", reljerec1Unc_ttw)) ); 

        float reljerec1Unc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_reljerec1Up, wjet_reljerec1Down) : 1.00;
        line.replace( line.find("WWWW") , 4 , string(Form("%.3f", reljerec1Unc_wjet)) ); 
       
        float reljerec1Unc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_reljerec1Up, zjet_reljerec1Down) : 1.00;
        line.replace( line.find("DDDD") , 4 , string(Form("%.3f", reljerec1Unc_zjet)) ); 
        
        float reljerec1Unc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_reljerec1Up, stop_reljerec1Down) : 1.00; 
        line.replace( line.find("SSSS") , 4 , string(Form("%.3f", reljerec1Unc_stop)) ); 

        float reljerec1Unc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_reljerec1Up, vv_reljerec1Down) : 1.00;
        line.replace( line.find("VVVV") , 4 , string(Form("%.3f", reljerec1Unc_vv)) ); 
        out << line << endl;
      }
      else if(line.find("CMS_reljerec2 ")!=string::npos){

      	stringstream ss(line); string systname; ss >> systname;
      	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+uncorr_extn);
	
        float reljerec2Unc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_reljerec2Up, wh_reljerec2Down) : 1.00;
        line.replace( line.find("HHHH") , 4 , string(Form("%.3f", reljerec2Unc_wh)) );
        
        float reljerec2Unc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_reljerec2Up, ttbar_reljerec2Down) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", reljerec2Unc_ttbar)) ); 
        
	float reljerec2Unc_ttg = (ttg->Integral() > 0) ? DC.getBTagUnc(ttg, ttg_reljerec2Up, ttg_reljerec2Down) : 1.00; 
  	line.replace( line.find("TTGT") , 4 , string(Form("%.3f", reljerec2Unc_ttg)) ); 

	float reljerec2Unc_tth = (tth->Integral() > 0) ? DC.getBTagUnc(tth, tth_reljerec2Up, tth_reljerec2Down) : 1.00; 
  	line.replace( line.find("TTHT") , 4 , string(Form("%.3f", reljerec2Unc_tth)) ); 

	float reljerec2Unc_ttz = (ttz->Integral() > 0) ? DC.getBTagUnc(ttz, ttz_reljerec2Up, ttz_reljerec2Down) : 1.00; 
  	line.replace( line.find("TTZT") , 4 , string(Form("%.3f", reljerec2Unc_ttz)) ); 

	float reljerec2Unc_ttw = (ttw->Integral() > 0) ? DC.getBTagUnc(ttw, ttw_reljerec2Up, ttw_reljerec2Down) : 1.00; 
  	line.replace( line.find("TTWT") , 4 , string(Form("%.3f", reljerec2Unc_ttw)) ); 

        float reljerec2Unc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_reljerec2Up, wjet_reljerec2Down) : 1.00;
        line.replace( line.find("WWWW") , 4 , string(Form("%.3f", reljerec2Unc_wjet)) ); 
       
        float reljerec2Unc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_reljerec2Up, zjet_reljerec2Down) : 1.00;
        line.replace( line.find("DDDD") , 4 , string(Form("%.3f", reljerec2Unc_zjet)) ); 
        
        float reljerec2Unc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_reljerec2Up, stop_reljerec2Down) : 1.00; 
        line.replace( line.find("SSSS") , 4 , string(Form("%.3f", reljerec2Unc_stop)) ); 

        float reljerec2Unc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_reljerec2Up, vv_reljerec2Down) : 1.00;
        line.replace( line.find("VVVV") , 4 , string(Form("%.3f", reljerec2Unc_vv)) ); 
        out << line << endl;
      }
      else if(line.find("CMS_reljerhf ")!=string::npos){

      	stringstream ss(line); string systname; ss >> systname;
      	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+hist_extn);
	
        float reljerhfUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_reljerhfUp, wh_reljerhfDown) : 1.00;
        line.replace( line.find("HHHH") , 4 , string(Form("%.3f", reljerhfUnc_wh)) );
        
        float reljerhfUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_reljerhfUp, ttbar_reljerhfDown) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", reljerhfUnc_ttbar)) ); 
        
	float reljerhfUnc_ttg = (ttg->Integral() > 0) ? DC.getBTagUnc(ttg, ttg_reljerhfUp, ttg_reljerhfDown) : 1.00; 
  	line.replace( line.find("TTGT") , 4 , string(Form("%.3f", reljerhfUnc_ttg)) ); 

	float reljerhfUnc_tth = (tth->Integral() > 0) ? DC.getBTagUnc(tth, tth_reljerhfUp, tth_reljerhfDown) : 1.00; 
  	line.replace( line.find("TTHT") , 4 , string(Form("%.3f", reljerhfUnc_tth)) ); 

	float reljerhfUnc_ttz = (ttz->Integral() > 0) ? DC.getBTagUnc(ttz, ttz_reljerhfUp, ttz_reljerhfDown) : 1.00; 
  	line.replace( line.find("TTZT") , 4 , string(Form("%.3f", reljerhfUnc_ttz)) ); 

	float reljerhfUnc_ttw = (ttw->Integral() > 0) ? DC.getBTagUnc(ttw, ttw_reljerhfUp, ttw_reljerhfDown) : 1.00; 
  	line.replace( line.find("TTWT") , 4 , string(Form("%.3f", reljerhfUnc_ttw)) ); 

        float reljerhfUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_reljerhfUp, wjet_reljerhfDown) : 1.00;
        line.replace( line.find("WWWW") , 4 , string(Form("%.3f", reljerhfUnc_wjet)) ); 
       
        float reljerhfUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_reljerhfUp, zjet_reljerhfDown) : 1.00;
        line.replace( line.find("DDDD") , 4 , string(Form("%.3f", reljerhfUnc_zjet)) ); 
        
        float reljerhfUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_reljerhfUp, stop_reljerhfDown) : 1.00; 
        line.replace( line.find("SSSS") , 4 , string(Form("%.3f", reljerhfUnc_stop)) ); 

        float reljerhfUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_reljerhfUp, vv_reljerhfDown) : 1.00;
        line.replace( line.find("VVVV") , 4 , string(Form("%.3f", reljerhfUnc_vv)) ); 
        out << line << endl;
      }
      else if(line.find("CMS_relptbb ")!=string::npos){

      	stringstream ss(line); string systname; ss >> systname;
      	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+hist_extn);
	
        float relptbbUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_relptbbUp, wh_relptbbDown) : 1.00;
        line.replace( line.find("HHHH") , 4 , string(Form("%.3f", relptbbUnc_wh)) );
        
        float relptbbUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_relptbbUp, ttbar_relptbbDown) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", relptbbUnc_ttbar)) ); 
        
	float relptbbUnc_ttg = (ttg->Integral() > 0) ? DC.getBTagUnc(ttg, ttg_relptbbUp, ttg_relptbbDown) : 1.00; 
  	line.replace( line.find("TTGT") , 4 , string(Form("%.3f", relptbbUnc_ttg)) ); 

	float relptbbUnc_tth = (tth->Integral() > 0) ? DC.getBTagUnc(tth, tth_relptbbUp, tth_relptbbDown) : 1.00; 
  	line.replace( line.find("TTHT") , 4 , string(Form("%.3f", relptbbUnc_tth)) ); 

	float relptbbUnc_ttz = (ttz->Integral() > 0) ? DC.getBTagUnc(ttz, ttz_relptbbUp, ttz_relptbbDown) : 1.00; 
  	line.replace( line.find("TTZT") , 4 , string(Form("%.3f", relptbbUnc_ttz)) ); 

	float relptbbUnc_ttw = (ttw->Integral() > 0) ? DC.getBTagUnc(ttw, ttw_relptbbUp, ttw_relptbbDown) : 1.00; 
  	line.replace( line.find("TTWT") , 4 , string(Form("%.3f", relptbbUnc_ttw)) ); 

        float relptbbUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_relptbbUp, wjet_relptbbDown) : 1.00;
        line.replace( line.find("WWWW") , 4 , string(Form("%.3f", relptbbUnc_wjet)) ); 
       
        float relptbbUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_relptbbUp, zjet_relptbbDown) : 1.00;
        line.replace( line.find("DDDD") , 4 , string(Form("%.3f", relptbbUnc_zjet)) ); 
        
        float relptbbUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_relptbbUp, stop_relptbbDown) : 1.00; 
        line.replace( line.find("SSSS") , 4 , string(Form("%.3f", relptbbUnc_stop)) ); 

        float relptbbUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_relptbbUp, vv_relptbbDown) : 1.00;
        line.replace( line.find("VVVV") , 4 , string(Form("%.3f", relptbbUnc_vv)) ); 
        out << line << endl;
      }
      else if(line.find("CMS_relptec1 ")!=string::npos){

      	stringstream ss(line); string systname; ss >> systname;
      	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+uncorr_extn);
	
        float relptec1Unc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_relptec1Up, wh_relptec1Down) : 1.00;
        line.replace( line.find("HHHH") , 4 , string(Form("%.3f", relptec1Unc_wh)) );
        
        float relptec1Unc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_relptec1Up, ttbar_relptec1Down) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", relptec1Unc_ttbar)) ); 
        
	float relptec1Unc_ttg = (ttg->Integral() > 0) ? DC.getBTagUnc(ttg, ttg_relptec1Up, ttg_relptec1Down) : 1.00; 
  	line.replace( line.find("TTGT") , 4 , string(Form("%.3f", relptec1Unc_ttg)) ); 

	float relptec1Unc_tth = (tth->Integral() > 0) ? DC.getBTagUnc(tth, tth_relptec1Up, tth_relptec1Down) : 1.00; 
  	line.replace( line.find("TTHT") , 4 , string(Form("%.3f", relptec1Unc_tth)) ); 

	float relptec1Unc_ttz = (ttz->Integral() > 0) ? DC.getBTagUnc(ttz, ttz_relptec1Up, ttz_relptec1Down) : 1.00; 
  	line.replace( line.find("TTZT") , 4 , string(Form("%.3f", relptec1Unc_ttz)) ); 

	float relptec1Unc_ttw = (ttw->Integral() > 0) ? DC.getBTagUnc(ttw, ttw_relptec1Up, ttw_relptec1Down) : 1.00; 
  	line.replace( line.find("TTWT") , 4 , string(Form("%.3f", relptec1Unc_ttw)) ); 

        float relptec1Unc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_relptec1Up, wjet_relptec1Down) : 1.00;
        line.replace( line.find("WWWW") , 4 , string(Form("%.3f", relptec1Unc_wjet)) ); 
       
        float relptec1Unc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_relptec1Up, zjet_relptec1Down) : 1.00;
        line.replace( line.find("DDDD") , 4 , string(Form("%.3f", relptec1Unc_zjet)) ); 
        
        float relptec1Unc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_relptec1Up, stop_relptec1Down) : 1.00; 
        line.replace( line.find("SSSS") , 4 , string(Form("%.3f", relptec1Unc_stop)) ); 

        float relptec1Unc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_relptec1Up, vv_relptec1Down) : 1.00;
        line.replace( line.find("VVVV") , 4 , string(Form("%.3f", relptec1Unc_vv)) ); 
        out << line << endl;
      }
      else if(line.find("CMS_relptec2 ")!=string::npos){

      	stringstream ss(line); string systname; ss >> systname;
      	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+uncorr_extn);
	
        float relptec2Unc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_relptec2Up, wh_relptec2Down) : 1.00;
        line.replace( line.find("HHHH") , 4 , string(Form("%.3f", relptec2Unc_wh)) );
        
        float relptec2Unc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_relptec2Up, ttbar_relptec2Down) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", relptec2Unc_ttbar)) ); 
        
	float relptec2Unc_ttg = (ttg->Integral() > 0) ? DC.getBTagUnc(ttg, ttg_relptec2Up, ttg_relptec2Down) : 1.00; 
  	line.replace( line.find("TTGT") , 4 , string(Form("%.3f", relptec2Unc_ttg)) ); 

	float relptec2Unc_tth = (tth->Integral() > 0) ? DC.getBTagUnc(tth, tth_relptec2Up, tth_relptec2Down) : 1.00; 
  	line.replace( line.find("TTHT") , 4 , string(Form("%.3f", relptec2Unc_tth)) ); 

	float relptec2Unc_ttz = (ttz->Integral() > 0) ? DC.getBTagUnc(ttz, ttz_relptec2Up, ttz_relptec2Down) : 1.00; 
  	line.replace( line.find("TTZT") , 4 , string(Form("%.3f", relptec2Unc_ttz)) ); 

	float relptec2Unc_ttw = (ttw->Integral() > 0) ? DC.getBTagUnc(ttw, ttw_relptec2Up, ttw_relptec2Down) : 1.00; 
  	line.replace( line.find("TTWT") , 4 , string(Form("%.3f", relptec2Unc_ttw)) ); 

        float relptec2Unc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_relptec2Up, wjet_relptec2Down) : 1.00;
        line.replace( line.find("WWWW") , 4 , string(Form("%.3f", relptec2Unc_wjet)) ); 
       
        float relptec2Unc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_relptec2Up, zjet_relptec2Down) : 1.00;
        line.replace( line.find("DDDD") , 4 , string(Form("%.3f", relptec2Unc_zjet)) ); 
        
        float relptec2Unc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_relptec2Up, stop_relptec2Down) : 1.00; 
        line.replace( line.find("SSSS") , 4 , string(Form("%.3f", relptec2Unc_stop)) ); 

        float relptec2Unc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_relptec2Up, vv_relptec2Down) : 1.00;
        line.replace( line.find("VVVV") , 4 , string(Form("%.3f", relptec2Unc_vv)) ); 
        out << line << endl;
      }
      else if(line.find("CMS_relpthf ")!=string::npos){

      	stringstream ss(line); string systname; ss >> systname;
      	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+hist_extn);
	
        float relpthfUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_relpthfUp, wh_relpthfDown) : 1.00;
        line.replace( line.find("HHHH") , 4 , string(Form("%.3f", relpthfUnc_wh)) );
        
        float relpthfUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_relpthfUp, ttbar_relpthfDown) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", relpthfUnc_ttbar)) ); 
        
	float relpthfUnc_ttg = (ttg->Integral() > 0) ? DC.getBTagUnc(ttg, ttg_relpthfUp, ttg_relpthfDown) : 1.00; 
  	line.replace( line.find("TTGT") , 4 , string(Form("%.3f", relpthfUnc_ttg)) ); 

	float relpthfUnc_tth = (tth->Integral() > 0) ? DC.getBTagUnc(tth, tth_relpthfUp, tth_relpthfDown) : 1.00; 
  	line.replace( line.find("TTHT") , 4 , string(Form("%.3f", relpthfUnc_tth)) ); 

	float relpthfUnc_ttz = (ttz->Integral() > 0) ? DC.getBTagUnc(ttz, ttz_relpthfUp, ttz_relpthfDown) : 1.00; 
  	line.replace( line.find("TTZT") , 4 , string(Form("%.3f", relpthfUnc_ttz)) ); 

	float relpthfUnc_ttw = (ttw->Integral() > 0) ? DC.getBTagUnc(ttw, ttw_relpthfUp, ttw_relpthfDown) : 1.00; 
  	line.replace( line.find("TTWT") , 4 , string(Form("%.3f", relpthfUnc_ttw)) ); 

        float relpthfUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_relpthfUp, wjet_relpthfDown) : 1.00;
        line.replace( line.find("WWWW") , 4 , string(Form("%.3f", relpthfUnc_wjet)) ); 
       
        float relpthfUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_relpthfUp, zjet_relpthfDown) : 1.00;
        line.replace( line.find("DDDD") , 4 , string(Form("%.3f", relpthfUnc_zjet)) ); 
        
        float relpthfUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_relpthfUp, stop_relpthfDown) : 1.00; 
        line.replace( line.find("SSSS") , 4 , string(Form("%.3f", relpthfUnc_stop)) ); 

        float relpthfUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_relpthfUp, vv_relpthfDown) : 1.00;
        line.replace( line.find("VVVV") , 4 , string(Form("%.3f", relpthfUnc_vv)) ); 
        out << line << endl;
      }
      else if(line.find("CMS_relstatec  ")!=string::npos){

      	stringstream ss(line); string systname; ss >> systname;
      	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+uncorr_extn);
	
        float relstatecUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_relstatecUp, wh_relstatecDown) : 1.00;
        line.replace( line.find("HHHH") , 4 , string(Form("%.3f", relstatecUnc_wh)) );
        
        float relstatecUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_relstatecUp, ttbar_relstatecDown) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", relstatecUnc_ttbar)) ); 
        
	float relstatecUnc_ttg = (ttg->Integral() > 0) ? DC.getBTagUnc(ttg, ttg_relstatecUp, ttg_relstatecDown) : 1.00; 
  	line.replace( line.find("TTGT") , 4 , string(Form("%.3f", relstatecUnc_ttg)) ); 

	float relstatecUnc_tth = (tth->Integral() > 0) ? DC.getBTagUnc(tth, tth_relstatecUp, tth_relstatecDown) : 1.00; 
  	line.replace( line.find("TTHT") , 4 , string(Form("%.3f", relstatecUnc_tth)) ); 

	float relstatecUnc_ttz = (ttz->Integral() > 0) ? DC.getBTagUnc(ttz, ttz_relstatecUp, ttz_relstatecDown) : 1.00; 
  	line.replace( line.find("TTZT") , 4 , string(Form("%.3f", relstatecUnc_ttz)) ); 

	float relstatecUnc_ttw = (ttw->Integral() > 0) ? DC.getBTagUnc(ttw, ttw_relstatecUp, ttw_relstatecDown) : 1.00; 
  	line.replace( line.find("TTWT") , 4 , string(Form("%.3f", relstatecUnc_ttw)) ); 

        float relstatecUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_relstatecUp, wjet_relstatecDown) : 1.00;
        line.replace( line.find("WWWW") , 4 , string(Form("%.3f", relstatecUnc_wjet)) ); 
       
        float relstatecUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_relstatecUp, zjet_relstatecDown) : 1.00;
        line.replace( line.find("DDDD") , 4 , string(Form("%.3f", relstatecUnc_zjet)) ); 
        
        float relstatecUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_relstatecUp, stop_relstatecDown) : 1.00; 
        line.replace( line.find("SSSS") , 4 , string(Form("%.3f", relstatecUnc_stop)) ); 

        float relstatecUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_relstatecUp, vv_relstatecDown) : 1.00;
        line.replace( line.find("VVVV") , 4 , string(Form("%.3f", relstatecUnc_vv)) ); 
        out << line << endl;
      }
      else if(line.find("CMS_relstatfsr ")!=string::npos){

      	stringstream ss(line); string systname; ss >> systname;
      	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+uncorr_extn);
	
        float relstatfsrUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_relstatfsrUp, wh_relstatfsrDown) : 1.00;
        line.replace( line.find("HHHH") , 4 , string(Form("%.3f", relstatfsrUnc_wh)) );
        
        float relstatfsrUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_relstatfsrUp, ttbar_relstatfsrDown) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", relstatfsrUnc_ttbar)) ); 
        
	float relstatfsrUnc_ttg = (ttg->Integral() > 0) ? DC.getBTagUnc(ttg, ttg_relstatfsrUp, ttg_relstatfsrDown) : 1.00; 
  	line.replace( line.find("TTGT") , 4 , string(Form("%.3f", relstatfsrUnc_ttg)) ); 

	float relstatfsrUnc_tth = (tth->Integral() > 0) ? DC.getBTagUnc(tth, tth_relstatfsrUp, tth_relstatfsrDown) : 1.00; 
  	line.replace( line.find("TTHT") , 4 , string(Form("%.3f", relstatfsrUnc_tth)) ); 

	float relstatfsrUnc_ttz = (ttz->Integral() > 0) ? DC.getBTagUnc(ttz, ttz_relstatfsrUp, ttz_relstatfsrDown) : 1.00; 
  	line.replace( line.find("TTZT") , 4 , string(Form("%.3f", relstatfsrUnc_ttz)) ); 

	float relstatfsrUnc_ttw = (ttw->Integral() > 0) ? DC.getBTagUnc(ttw, ttw_relstatfsrUp, ttw_relstatfsrDown) : 1.00; 
  	line.replace( line.find("TTWT") , 4 , string(Form("%.3f", relstatfsrUnc_ttw)) ); 

        float relstatfsrUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_relstatfsrUp, wjet_relstatfsrDown) : 1.00;
        line.replace( line.find("WWWW") , 4 , string(Form("%.3f", relstatfsrUnc_wjet)) ); 
       
        float relstatfsrUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_relstatfsrUp, zjet_relstatfsrDown) : 1.00;
        line.replace( line.find("DDDD") , 4 , string(Form("%.3f", relstatfsrUnc_zjet)) ); 
        
        float relstatfsrUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_relstatfsrUp, stop_relstatfsrDown) : 1.00; 
        line.replace( line.find("SSSS") , 4 , string(Form("%.3f", relstatfsrUnc_stop)) ); 

        float relstatfsrUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_relstatfsrUp, vv_relstatfsrDown) : 1.00;
        line.replace( line.find("VVVV") , 4 , string(Form("%.3f", relstatfsrUnc_vv)) ); 
        out << line << endl;
      }
      else if(line.find("CMS_relstathf ")!=string::npos){

      	stringstream ss(line); string systname; ss >> systname;
      	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+uncorr_extn);
	
        float relstathfUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_relstathfUp, wh_relstathfDown) : 1.00;
        line.replace( line.find("HHHH") , 4 , string(Form("%.3f", relstathfUnc_wh)) );
        
        float relstathfUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_relstathfUp, ttbar_relstathfDown) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", relstathfUnc_ttbar)) ); 
        
	float relstathfUnc_ttg = (ttg->Integral() > 0) ? DC.getBTagUnc(ttg, ttg_relstathfUp, ttg_relstathfDown) : 1.00; 
  	line.replace( line.find("TTGT") , 4 , string(Form("%.3f", relstathfUnc_ttg)) ); 

	float relstathfUnc_tth = (tth->Integral() > 0) ? DC.getBTagUnc(tth, tth_relstathfUp, tth_relstathfDown) : 1.00; 
  	line.replace( line.find("TTHT") , 4 , string(Form("%.3f", relstathfUnc_tth)) ); 

	float relstathfUnc_ttz = (ttz->Integral() > 0) ? DC.getBTagUnc(ttz, ttz_relstathfUp, ttz_relstathfDown) : 1.00; 
  	line.replace( line.find("TTZT") , 4 , string(Form("%.3f", relstathfUnc_ttz)) ); 

	float relstathfUnc_ttw = (ttw->Integral() > 0) ? DC.getBTagUnc(ttw, ttw_relstathfUp, ttw_relstathfDown) : 1.00; 
  	line.replace( line.find("TTWT") , 4 , string(Form("%.3f", relstathfUnc_ttw)) ); 

        float relstathfUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_relstathfUp, wjet_relstathfDown) : 1.00;
        line.replace( line.find("WWWW") , 4 , string(Form("%.3f", relstathfUnc_wjet)) ); 
       
        float relstathfUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_relstathfUp, zjet_relstathfDown) : 1.00;
        line.replace( line.find("DDDD") , 4 , string(Form("%.3f", relstathfUnc_zjet)) ); 
        
        float relstathfUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_relstathfUp, stop_relstathfDown) : 1.00; 
        line.replace( line.find("SSSS") , 4 , string(Form("%.3f", relstathfUnc_stop)) ); 

        float relstathfUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_relstathfUp, vv_relstathfDown) : 1.00;
        line.replace( line.find("VVVV") , 4 , string(Form("%.3f", relstathfUnc_vv)) ); 
        out << line << endl;
      }
      else if(line.find("CMS_singpiecal ")!=string::npos){

      	stringstream ss(line); string systname; ss >> systname;
      	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+hist_extn);
	
        float singpiecalUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_singpiecalUp, wh_singpiecalDown) : 1.00;
        line.replace( line.find("HHHH") , 4 , string(Form("%.3f", singpiecalUnc_wh)) );
        
        float singpiecalUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_singpiecalUp, ttbar_singpiecalDown) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", singpiecalUnc_ttbar)) ); 
        
	float singpiecalUnc_ttg = (ttg->Integral() > 0) ? DC.getBTagUnc(ttg, ttg_singpiecalUp, ttg_singpiecalDown) : 1.00; 
  	line.replace( line.find("TTGT") , 4 , string(Form("%.3f", singpiecalUnc_ttg)) ); 

	float singpiecalUnc_tth = (tth->Integral() > 0) ? DC.getBTagUnc(tth, tth_singpiecalUp, tth_singpiecalDown) : 1.00; 
  	line.replace( line.find("TTHT") , 4 , string(Form("%.3f", singpiecalUnc_tth)) ); 

	float singpiecalUnc_ttz = (ttz->Integral() > 0) ? DC.getBTagUnc(ttz, ttz_singpiecalUp, ttz_singpiecalDown) : 1.00; 
  	line.replace( line.find("TTZT") , 4 , string(Form("%.3f", singpiecalUnc_ttz)) ); 

	float singpiecalUnc_ttw = (ttw->Integral() > 0) ? DC.getBTagUnc(ttw, ttw_singpiecalUp, ttw_singpiecalDown) : 1.00; 
  	line.replace( line.find("TTWT") , 4 , string(Form("%.3f", singpiecalUnc_ttw)) ); 

        float singpiecalUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_singpiecalUp, wjet_singpiecalDown) : 1.00;
        line.replace( line.find("WWWW") , 4 , string(Form("%.3f", singpiecalUnc_wjet)) ); 
       
        float singpiecalUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_singpiecalUp, zjet_singpiecalDown) : 1.00;
        line.replace( line.find("DDDD") , 4 , string(Form("%.3f", singpiecalUnc_zjet)) ); 
        
        float singpiecalUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_singpiecalUp, stop_singpiecalDown) : 1.00; 
        line.replace( line.find("SSSS") , 4 , string(Form("%.3f", singpiecalUnc_stop)) ); 

        float singpiecalUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_singpiecalUp, vv_singpiecalDown) : 1.00;
        line.replace( line.find("VVVV") , 4 , string(Form("%.3f", singpiecalUnc_vv)) ); 
        out << line << endl;
      }
      else if(line.find("CMS_singpihcal ")!=string::npos){

      	stringstream ss(line); string systname; ss >> systname;
      	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+hist_extn);
	
        float singpihcalUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_singpihcalUp, wh_singpihcalDown) : 1.00;
        line.replace( line.find("HHHH") , 4 , string(Form("%.3f", singpihcalUnc_wh)) );
        
        float singpihcalUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_singpihcalUp, ttbar_singpihcalDown) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", singpihcalUnc_ttbar)) ); 
        
	float singpihcalUnc_ttg = (ttg->Integral() > 0) ? DC.getBTagUnc(ttg, ttg_singpihcalUp, ttg_singpihcalDown) : 1.00; 
  	line.replace( line.find("TTGT") , 4 , string(Form("%.3f", singpihcalUnc_ttg)) ); 

	float singpihcalUnc_tth = (tth->Integral() > 0) ? DC.getBTagUnc(tth, tth_singpihcalUp, tth_singpihcalDown) : 1.00; 
  	line.replace( line.find("TTHT") , 4 , string(Form("%.3f", singpihcalUnc_tth)) ); 

	float singpihcalUnc_ttz = (ttz->Integral() > 0) ? DC.getBTagUnc(ttz, ttz_singpihcalUp, ttz_singpihcalDown) : 1.00; 
  	line.replace( line.find("TTZT") , 4 , string(Form("%.3f", singpihcalUnc_ttz)) ); 

	float singpihcalUnc_ttw = (ttw->Integral() > 0) ? DC.getBTagUnc(ttw, ttw_singpihcalUp, ttw_singpihcalDown) : 1.00; 
  	line.replace( line.find("TTWT") , 4 , string(Form("%.3f", singpihcalUnc_ttw)) ); 

        float singpihcalUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_singpihcalUp, wjet_singpihcalDown) : 1.00;
        line.replace( line.find("WWWW") , 4 , string(Form("%.3f", singpihcalUnc_wjet)) ); 
       
        float singpihcalUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_singpihcalUp, zjet_singpihcalDown) : 1.00;
        line.replace( line.find("DDDD") , 4 , string(Form("%.3f", singpihcalUnc_zjet)) ); 
        
        float singpihcalUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_singpihcalUp, stop_singpihcalDown) : 1.00; 
        line.replace( line.find("SSSS") , 4 , string(Form("%.3f", singpihcalUnc_stop)) ); 

        float singpihcalUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_singpihcalUp, vv_singpihcalDown) : 1.00;
        line.replace( line.find("VVVV") , 4 , string(Form("%.3f", singpihcalUnc_vv)) ); 
        out << line << endl;
      }
      else if(line.find("CMS_timepteta ")!=string::npos){

	stringstream ss(line); string systname; ss >> systname;
	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+uncorr_extn);
	
        float timeptetaUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_timeptetaUp, wh_timeptetaDown) : 1.00;
        line.replace( line.find("HHHH") , 4 , string(Form("%.3f", timeptetaUnc_wh)) );
        
        float timeptetaUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_timeptetaUp, ttbar_timeptetaDown) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", timeptetaUnc_ttbar)) ); 
        
	float timeptetaUnc_ttg = (ttg->Integral() > 0) ? DC.getBTagUnc(ttg, ttg_timeptetaUp, ttg_timeptetaDown) : 1.00; 
  	line.replace( line.find("TTGT") , 4 , string(Form("%.3f", timeptetaUnc_ttg)) ); 

	float timeptetaUnc_tth = (tth->Integral() > 0) ? DC.getBTagUnc(tth, tth_timeptetaUp, tth_timeptetaDown) : 1.00; 
  	line.replace( line.find("TTHT") , 4 , string(Form("%.3f", timeptetaUnc_tth)) ); 

	float timeptetaUnc_ttz = (ttz->Integral() > 0) ? DC.getBTagUnc(ttz, ttz_timeptetaUp, ttz_timeptetaDown) : 1.00; 
  	line.replace( line.find("TTZT") , 4 , string(Form("%.3f", timeptetaUnc_ttz)) ); 

	float timeptetaUnc_ttw = (ttw->Integral() > 0) ? DC.getBTagUnc(ttw, ttw_timeptetaUp, ttw_timeptetaDown) : 1.00; 
  	line.replace( line.find("TTWT") , 4 , string(Form("%.3f", timeptetaUnc_ttw)) ); 

        float timeptetaUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_timeptetaUp, wjet_timeptetaDown) : 1.00;
        line.replace( line.find("WWWW") , 4 , string(Form("%.3f", timeptetaUnc_wjet)) ); 
       
        float timeptetaUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_timeptetaUp, zjet_timeptetaDown) : 1.00;
        line.replace( line.find("DDDD") , 4 , string(Form("%.3f", timeptetaUnc_zjet)) ); 
        
        float timeptetaUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_timeptetaUp, stop_timeptetaDown) : 1.00; 
        line.replace( line.find("SSSS") , 4 , string(Form("%.3f", timeptetaUnc_stop)) ); 

        float timeptetaUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_timeptetaUp, vv_timeptetaDown) : 1.00;
        line.replace( line.find("VVVV") , 4 , string(Form("%.3f", timeptetaUnc_vv)) ); 
        out << line << endl;
      }
      else{ //default without changes
        out << line << endl;
  	//
      }
    }
    
  }
  
  // if(isExL){
  //   string rate = "CMS_eff_cExL       lnN";  
  //   string space = "     ";
  //   out << rate ;
  //   out << space <<string(Form("%.3f", unc_wh_ExL))
  //       << space <<string(Form("%.3f", unc_ttbar_ExL))
  //       << space <<string(Form("%.3f", unc_wjet_ExL))
  //       << space <<string(Form("%.3f", unc_zjet_ExL))
  //       << space <<string(Form("%.3f", unc_stop_ExL))
  //       << space <<string(Form("%.3f", unc_vv_ExL))
  //       << space <<string(Form("%.3f", 1.0))
  //       << endl;
  // }
  // if(isExM){
  //   string rate = "CMS_eff_cExM       lnN";  
  //   string space = "     ";
  //   out << rate ;
  //   out << space <<string(Form("%.3f", unc_wh_ExM))
  //       << space <<string(Form("%.3f", unc_ttbar_ExM))
  //       << space <<string(Form("%.3f", unc_wjet_ExM))
  //       << space <<string(Form("%.3f", unc_zjet_ExM))
  //       << space <<string(Form("%.3f", unc_stop_ExM))
  //       << space <<string(Form("%.3f", unc_vv_ExM))
  //       << space <<string(Form("%.3f", 1.0))
  //       << endl;
  // }
  if(!isBinStat)
    out<<"* autoMCStats 0 1"<<endl;
  //out<<"qcdrate rateParam * qcd "<< QCD_DD_Integral <<" ["<<0.5*QCD_DD_Integral<<","<<2.*QCD_DD_Integral<<"]"<<endl;
  out<<"qcdrate rateParam * qcd 1.0 [0.0,2.0]"<<endl;
  out.close();
  in.close();
  fout->Close();
  delete fout;
}


void MyHPlusDataCardMaker(TString inFileDir="stack_20180418_Mu_Sys_PreAppComent",
			  TString year="2016", 
			  TString histSubDir_="KinFit",
			  TString histName="mjj_kfit", 
			  TString channelName="mu", 
			  int mass=80, 
			  TString label="WH80", 
			  TString hPlusFileName="all_Hplus80.root")
  {

    //MyHPlusDataCardMakerMini(inFileDir, year, histSubDir_, histName, channelName, mass, label, hPlusFileName);
    MyHPlusDataCardMakerNano(inFileDir, year, histSubDir_, histName, channelName, mass, label, hPlusFileName);


  }
