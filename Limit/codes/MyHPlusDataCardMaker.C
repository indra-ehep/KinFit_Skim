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
  float lumiUnc = 1.012;//2.5% for 2016 following https://twiki.cern.ch/twiki/bin/viewauth/CMS/TWikiLUM
  if(year==2017){
    totLumi = 41.48; // 2017
    lumiUnc = 1.023; //
  }
  if(year==2018){
    totLumi = 59.83; //2018
    lumiUnc = 1.025; //
  }
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
  
  bool isNormalized = true;
  //ttbar
  double sf_ttbar = 1.0; 
  baseDir = "TTbar";
  TH1F* ttbar = DC.readWriteHisto(fTT, baseDir+"/base"+histSubDir, histName, sf_ttbar, fout, fTT,  "ttbar", true);
  // baseDir = "DataMu";
  // TH1F* ttbar = DC.readWriteHisto(fData, baseDir+"/base"+histSubDir, histName, sf_ttbar, fout, fTT,  "ttbar", true);
  // baseDir = "TTbar";
  TH1F *ttbar_LeptonUp,*ttbar_LeptonDown;
  if(isMuChannel){
    ttbar_LeptonUp = DC.readWriteHisto(fTT, baseDir+"/mueffup"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_LeptonUp", true);
    ttbar_LeptonDown = DC.readWriteHisto(fTT, baseDir+"/mueffdown"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_LeptonDown", true);
  }else{
    ttbar_LeptonUp = DC.readWriteHisto(fTT, baseDir+"/eleeffup"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_LeptonUp", true);
    ttbar_LeptonDown = DC.readWriteHisto(fTT, baseDir+"/eleeffdown"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_LeptonDown", true);
  }
  TH1F* ttbar_JESUp = DC.readWriteHisto(fTT, baseDir+"/jecup"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_JESUp", true);
  TH1F* ttbar_JESDown = DC.readWriteHisto(fTT, baseDir+"/jecdown"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_JESDown", true);
  TH1F* ttbar_PileupUp = DC.readWriteHisto(fTT, baseDir+"/puup"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_PileupUp", true);
  TH1F* ttbar_PileupDown = DC.readWriteHisto(fTT, baseDir+"/pudown"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_PileupDown", true);
  TH1F *ttbar_PrefireUp, *ttbar_PrefireDown;
  if(year==2016 or year==2017){
    ttbar_PrefireUp = DC.readWriteHisto(fTT, baseDir+"/prefireup"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_PrefireUp", true);
    ttbar_PrefireDown = DC.readWriteHisto(fTT, baseDir+"/prefiredown"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_PrefireDown", true);
  }else{
    ttbar_PrefireUp = DC.readWriteHisto(fTT, baseDir+"/base"+histSubDir, histName, sf_ttbar, fout, fTT,  "ttbar_PrefireUp", true);
    ttbar_PrefireDown = DC.readWriteHisto(fTT, baseDir+"/base"+histSubDir, histName, sf_ttbar, fout, fTT,  "ttbar_PrefireDown", true);
  }
  TH1F* ttbar_PUJetIDUp = DC.readWriteHisto(fTT, baseDir+"/pujetidup"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_PUJetIDUp", true);
  TH1F* ttbar_PUJetIDDown = DC.readWriteHisto(fTT, baseDir+"/pujetiddown"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_PUJetIDDown", true);
  TH1F* ttbar_JERUp = DC.readWriteHisto(fTT, baseDir+"/jerup"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_JERUp", true);
  TH1F* ttbar_JERDown = DC.readWriteHisto(fTT, baseDir+"/jerdown"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_JERDown", true);
  //\([a-z]+\)_\([a-zA-Z]+\) = DC.readWriteHisto(\([a-zA-Z]+\), baseDir\+"/\([a-z]+\)"\+histSubDir, histName, sf_\([a-z]+\), fout, \([a-zA-Z]+\), \(label\+\)?"\([a-zA-Z_]+\)", true, true, \([a-z]+\)); \1_\2 = DC.readWriteHisto(\3, baseDir+"/\4"+histSubDir, histName, sf_\5, fout, \6, \7"\8", true);
  TH1F* ttbar_bcstatUp = DC.readWriteHisto(fTT, baseDir+"/bcstatup"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_bcstatUp", true, isNormalized, ttbar);
  TH1F* ttbar_bcstatDown = DC.readWriteHisto(fTT, baseDir+"/bcstatdown"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_bcstatDown", true, isNormalized, ttbar);
  TH1F *ttbar_bcintpUp, *ttbar_bcintpDown, *ttbar_bcextpUp, *ttbar_bcextpDown, *ttbar_bcxdybUp, *ttbar_bcxdybDown, *ttbar_bcxdycUp, *ttbar_bcxdycDown, *ttbar_bcxwjcUp, *ttbar_bcxwjcDown;
  ttbar_bcintpUp = DC.readWriteHisto(fTT, baseDir+"/bcintpup"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_bcintpUp", true, isNormalized, ttbar);
  ttbar_bcintpDown = DC.readWriteHisto(fTT, baseDir+"/bcintpdown"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_bcintpDown", true, isNormalized, ttbar);
  ttbar_bcextpUp = DC.readWriteHisto(fTT, baseDir+"/bcextpup"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_bcextpUp", true, isNormalized, ttbar);
  ttbar_bcextpDown = DC.readWriteHisto(fTT, baseDir+"/bcextpdown"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_bcextpDown", true, isNormalized, ttbar);
  ttbar_bcxdybUp = DC.readWriteHisto(fTT, baseDir+"/bcxdybup"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_bcxdybUp", true, isNormalized, ttbar);
  ttbar_bcxdybDown = DC.readWriteHisto(fTT, baseDir+"/bcxdybdown"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_bcxdybDown", true, isNormalized, ttbar);
  ttbar_bcxdycUp = DC.readWriteHisto(fTT, baseDir+"/bcxdycup"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_bcxdycUp", true, isNormalized, ttbar);
  ttbar_bcxdycDown = DC.readWriteHisto(fTT, baseDir+"/bcxdycdown"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_bcxdycDown", true, isNormalized, ttbar);
  ttbar_bcxwjcUp = DC.readWriteHisto(fTT, baseDir+"/bcxwjcup"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_bcxwjcUp", true, isNormalized, ttbar);
  ttbar_bcxwjcDown = DC.readWriteHisto(fTT, baseDir+"/bcxwjcdown"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_bcxwjcDown", true, isNormalized, ttbar);

  TH1F* ttbar_pdfUp = DC.readWriteHisto(fTT, baseDir+"/pdfup"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_pdfUp", true);
  TH1F* ttbar_pdfDown = DC.readWriteHisto(fTT, baseDir+"/pdfdown"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_pdfDown", true);
  TH1F* ttbar_bclhemufUp = DC.readWriteHisto(fTT, baseDir+"/bclhemufup"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_bclhemufUp", true, isNormalized, ttbar);
  TH1F* ttbar_bclhemufDown = DC.readWriteHisto(fTT, baseDir+"/bclhemufdown"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_bclhemufDown", true, isNormalized, ttbar);
  TH1F* ttbar_bclhemurUp = DC.readWriteHisto(fTT, baseDir+"/bclhemurup"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_bclhemurUp", true, isNormalized, ttbar);
  TH1F* ttbar_bclhemurDown = DC.readWriteHisto(fTT, baseDir+"/bclhemurdown"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_bclhemurDown", true, isNormalized, ttbar);
  TH1F* ttbar_isrUp = DC.readWriteHisto(fTT, baseDir+"/isrup"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_isrUp", true, isNormalized, ttbar);
  TH1F* ttbar_isrDown = DC.readWriteHisto(fTT, baseDir+"/isrdown"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_isrDown", true, isNormalized, ttbar);
  TH1F* ttbar_fsrUp = DC.readWriteHisto(fTT, baseDir+"/fsrup"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_fsrUp", true, isNormalized, ttbar);
  TH1F* ttbar_fsrDown = DC.readWriteHisto(fTT, baseDir+"/fsrdown"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_fsrDown", true, isNormalized, ttbar);
  // //MiniAOD nuisances
  // TH1F* ttbar_bcTag1Up = DC.readWriteHisto(fTT, baseDir+"/bctag1up"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_bcTag1Up", true, isNormalized, ttbar);
  // TH1F* ttbar_bcTag1Down = DC.readWriteHisto(fTT, baseDir+"/bctag1down"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_bcTag1Down", true, isNormalized, ttbar);
  // TH1F* ttbar_bcTag2Up = DC.readWriteHisto(fTT, baseDir+"/bctag2up"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_bcTag2Up", true, isNormalized, ttbar);
  // TH1F* ttbar_bcTag2Down = DC.readWriteHisto(fTT, baseDir+"/bctag2down"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_bcTag2Down", true, isNormalized, ttbar);
  // TH1F* ttbar_bcTag3Up = DC.readWriteHisto(fTT, baseDir+"/bctag3up"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_bcTag3Up", true, isNormalized, ttbar);
  // TH1F* ttbar_bcTag3Down = DC.readWriteHisto(fTT, baseDir+"/bctag3down"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_bcTag3Down", true, isNormalized, ttbar);
  // TH1F* ttbar_topPtUp = DC.readWriteHisto(fTT, baseDir+"/topptup"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_topPtUp", true, isNormalized, ttbar);
  // TH1F* ttbar_topPtDown = DC.readWriteHisto(fTT, baseDir+"/topptdown"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_topPtDown", true, isNormalized, ttbar);
  // TH1F* ttbar_bTagbcUp = DC.readWriteHisto(fTT, baseDir+"/btagbup"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_bTagbcUp", true, isNormalized, ttbar);
  // TH1F* ttbar_bTagbcDown = DC.readWriteHisto(fTT, baseDir+"/btagbdown"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_bTagbcDown", true, isNormalized, ttbar);
  // TH1F* ttbar_bTaglUp = DC.readWriteHisto(fTT, baseDir+"/btaglup"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_bTaglUp", true, isNormalized, ttbar);
  // TH1F* ttbar_bTaglDown = DC.readWriteHisto(fTT, baseDir+"/btagldown"+histSubDir, histName, sf_ttbar, fout, fTT, "ttbar_bTaglDown", true, isNormalized, ttbar);
  
  if(isBinStat){
    for(int ibin = 1; ibin <= nonStatBins ; ibin++){
      TH1F *ttbar_bin_stat_Up = DC.readWriteHisto(fTT, baseDir+"/base"+histSubDir, histName, sf_ttbar, fout, fTT, Form("ttbar_CMS_stat_cat1_ttbar_bin_%dUp",ibin), true);
      TH1F *ttbar_bin_stat_Down = DC.readWriteHisto(fTT, baseDir+"/base"+histSubDir, histName, sf_ttbar, fout, fTT, Form("ttbar_CMS_stat_cat1_ttbar_bin_%dDown",ibin), true);
    }
  }
  
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
  
  double sf_ttbar_cp5Up = 1; 
  TH1F* ttbar_cp5Up = DC.readWriteHisto(fTT, baseDir+"/cp5up"+histSubDir, histName, sf_ttbar_cp5Up, fout, fTT, "ttbar_CP5_ttUp", true, isNormalized, ttbar);
  double sf_ttbar_cp5Down = 1; 
  TH1F* ttbar_cp5Down = DC.readWriteHisto(fTT, baseDir+"/cp5down"+histSubDir, histName, sf_ttbar_cp5Down, fout, fTT, "ttbar_CP5_ttDown", true, isNormalized, ttbar);
  double sf_ttbar_matchingUp = 1; 
  TH1F* ttbar_matchingUp = DC.readWriteHisto(fTT, baseDir+"/hdampup"+histSubDir, histName, sf_ttbar_matchingUp, fout, fTT, "ttbar_hDamp_ttUp", true, isNormalized, ttbar);
  double sf_ttbar_matchingDown = 1; 
  TH1F* ttbar_matchingDown = DC.readWriteHisto(fTT, baseDir+"/hdampdown"+histSubDir, histName, sf_ttbar_matchingDown, fout, fTT, "ttbar_hDamp_ttDown", true, isNormalized, ttbar);
  double sf_ttbar_mtop1715 = 1; 
  TH1F* ttbar_mtop1715 = DC.readWriteHisto(fTT, baseDir+"/mtopup"+histSubDir, histName, sf_ttbar_mtop1715, fout, fTT, "ttbar_topMass_ttDown", true, isNormalized, ttbar);
  double sf_ttbar_mtop1735 = 1; 
  TH1F* ttbar_mtop1735 = DC.readWriteHisto(fTT, baseDir+"/mtopdown"+histSubDir, histName, sf_ttbar_mtop1735, fout, fTT, "ttbar_topMass_ttUp", true, isNormalized, ttbar);

  //w+jets
  double sf_wjet = 1;
  baseDir = "Wjets";
  TH1F* wjet = DC.readWriteHisto(fWJ, baseDir+"/base"+histSubDir, histName, sf_wjet, fout, fTT, "wjet", true);
  TH1F *wjet_LeptonUp,*wjet_LeptonDown;
  if(isMuChannel){
    wjet_LeptonUp = DC.readWriteHisto(fWJ, baseDir+"/mueffup"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_LeptonUp", true);
    wjet_LeptonDown = DC.readWriteHisto(fWJ, baseDir+"/mueffdown"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_LeptonDown", true);
  }else{
    wjet_LeptonUp = DC.readWriteHisto(fWJ, baseDir+"/eleeffup"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_LeptonUp", true);
    wjet_LeptonDown = DC.readWriteHisto(fWJ, baseDir+"/eleeffdown"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_LeptonDown", true);
  }
  TH1F* wjet_JESUp = DC.readWriteHisto(fWJ, baseDir+"/jecup"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_JESUp", true);
  TH1F* wjet_JESDown = DC.readWriteHisto(fWJ, baseDir+"/jecdown"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_JESDown", true);
  TH1F* wjet_PileupUp = DC.readWriteHisto(fWJ, baseDir+"/puup"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_PileupUp", true);
  TH1F* wjet_PileupDown = DC.readWriteHisto(fWJ, baseDir+"/pudown"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_PileupDown", true);
  TH1F* wjet_PrefireUp, *wjet_PrefireDown;
  if(year==2016 or year==2017){
    wjet_PrefireUp = DC.readWriteHisto(fWJ, baseDir+"/prefireup"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_PrefireUp", true);
    wjet_PrefireDown = DC.readWriteHisto(fWJ, baseDir+"/prefiredown"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_PrefireDown", true);
  }else{
    wjet_PrefireUp = DC.readWriteHisto(fWJ, baseDir+"/base"+histSubDir, histName, sf_wjet, fout, fTT,  "wjet_PrefireUp", true);
    wjet_PrefireDown = DC.readWriteHisto(fWJ, baseDir+"/base"+histSubDir, histName, sf_wjet, fout, fTT,  "wjet_PrefireDown", true);
  }
  TH1F* wjet_PUJetIDUp = DC.readWriteHisto(fWJ, baseDir+"/pujetidup"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_PUJetIDUp", true);
  TH1F* wjet_PUJetIDDown = DC.readWriteHisto(fWJ, baseDir+"/pujetiddown"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_PUJetIDDown", true);
  TH1F* wjet_JERUp = DC.readWriteHisto(fWJ, baseDir+"/jerup"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_JERUp", true);
  TH1F* wjet_JERDown = DC.readWriteHisto(fWJ, baseDir+"/jerdown"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_JERDown", true);
  TH1F* wjet_bcstatUp = DC.readWriteHisto(fWJ, baseDir+"/bcstatup"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_bcstatUp", true, isNormalized, wjet);
  TH1F* wjet_bcstatDown = DC.readWriteHisto(fWJ, baseDir+"/bcstatdown"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_bcstatDown", true, isNormalized, wjet);
  TH1F *wjet_bcintpUp, *wjet_bcintpDown, *wjet_bcextpUp, *wjet_bcextpDown, *wjet_bcxdybUp, *wjet_bcxdybDown, *wjet_bcxdycUp, *wjet_bcxdycDown, *wjet_bcxwjcUp, *wjet_bcxwjcDown;

  wjet_bcintpUp = DC.readWriteHisto(fWJ, baseDir+"/bcintpup"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_bcintpUp", true, isNormalized, wjet);
  wjet_bcintpDown = DC.readWriteHisto(fWJ, baseDir+"/bcintpdown"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_bcintpDown", true, isNormalized, wjet);
  wjet_bcextpUp = DC.readWriteHisto(fWJ, baseDir+"/bcextpup"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_bcextpUp", true, isNormalized, wjet);
  wjet_bcextpDown = DC.readWriteHisto(fWJ, baseDir+"/bcextpdown"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_bcextpDown", true, isNormalized, wjet);
  wjet_bcxdybUp = DC.readWriteHisto(fWJ, baseDir+"/bcxdybup"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_bcxdybUp", true, isNormalized, wjet);
  wjet_bcxdybDown = DC.readWriteHisto(fWJ, baseDir+"/bcxdybdown"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_bcxdybDown", true, isNormalized, wjet);
  wjet_bcxdycUp = DC.readWriteHisto(fWJ, baseDir+"/bcxdycup"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_bcxdycUp", true, isNormalized, wjet);
  wjet_bcxdycDown = DC.readWriteHisto(fWJ, baseDir+"/bcxdycdown"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_bcxdycDown", true, isNormalized, wjet);
  wjet_bcxwjcUp = DC.readWriteHisto(fWJ, baseDir+"/bcxwjcup"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_bcxwjcUp", true, isNormalized, wjet);
  wjet_bcxwjcDown = DC.readWriteHisto(fWJ, baseDir+"/bcxwjcdown"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_bcxwjcDown", true, isNormalized, wjet);

  TH1F* wjet_pdfUp = DC.readWriteHisto(fWJ, baseDir+"/pdfup"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_pdfUp", true);
  TH1F* wjet_pdfDown = DC.readWriteHisto(fWJ, baseDir+"/pdfdown"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_pdfDown", true);
  // TH1F* wjet_q2Up = DC.readWriteHisto(fWJ, baseDir+"/q2up"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_q2Up", true);
  // TH1F* wjet_q2Down = DC.readWriteHisto(fWJ, baseDir+"/q2down"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_q2Down", true);
  TH1F* wjet_bclhemufUp = DC.readWriteHisto(fWJ, baseDir+"/bclhemufup"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_bclhemufUp", true, isNormalized, wjet);
  TH1F* wjet_bclhemufDown = DC.readWriteHisto(fWJ, baseDir+"/bclhemufdown"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_bclhemufDown", true, isNormalized, wjet);
  TH1F* wjet_bclhemurUp = DC.readWriteHisto(fWJ, baseDir+"/bclhemurup"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_bclhemurUp", true, isNormalized, wjet);
  TH1F* wjet_bclhemurDown = DC.readWriteHisto(fWJ, baseDir+"/bclhemurdown"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_bclhemurDown", true, isNormalized, wjet);
  TH1F* wjet_isrUp = DC.readWriteHisto(fWJ, baseDir+"/isrup"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_isrUp", true, isNormalized, wjet);
  TH1F* wjet_isrDown = DC.readWriteHisto(fWJ, baseDir+"/isrdown"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_isrDown", true, isNormalized, wjet);
  TH1F* wjet_fsrUp = DC.readWriteHisto(fWJ, baseDir+"/fsrup"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_fsrUp", true, isNormalized, wjet);
  TH1F* wjet_fsrDown = DC.readWriteHisto(fWJ, baseDir+"/fsrdown"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_fsrDown", true, isNormalized, wjet);
  // //MiniAOD nuisances
  // TH1F* wjet_bcTag1Up = DC.readWriteHisto(fWJ, baseDir+"/bctag1up"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_bcTag1Up", true, isNormalized, wjet);
  // TH1F* wjet_bcTag1Down = DC.readWriteHisto(fWJ, baseDir+"/bctag1down"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_bcTag1Down", true, isNormalized, wjet);
  // TH1F* wjet_bcTag2Up = DC.readWriteHisto(fWJ, baseDir+"/bctag2up"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_bcTag2Up", true, isNormalized, wjet);
  // TH1F* wjet_bcTag2Down = DC.readWriteHisto(fWJ, baseDir+"/bctag2down"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_bcTag2Down", true, isNormalized, wjet);
  // TH1F* wjet_bcTag3Up = DC.readWriteHisto(fWJ, baseDir+"/bctag3up"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_bcTag3Up", true, isNormalized, wjet);
  // TH1F* wjet_bcTag3Down = DC.readWriteHisto(fWJ, baseDir+"/bctag3down"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_bcTag3Down", true, isNormalized, wjet);
  // TH1F* wjet_bTagbcUp = DC.readWriteHisto(fWJ, baseDir+"/btagbup"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_bTagbcUp", true, isNormalized, wjet);
  // TH1F* wjet_bTagbcDown = DC.readWriteHisto(fWJ, baseDir+"/btagbdown"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_bTagbcDown", true, isNormalized, wjet);
  // TH1F* wjet_bTaglUp = DC.readWriteHisto(fWJ, baseDir+"/btaglup"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_bTaglUp", true, isNormalized, wjet);
  // TH1F* wjet_bTaglDown = DC.readWriteHisto(fWJ, baseDir+"/btagldown"+histSubDir, histName, sf_wjet, fout, fTT, "wjet_bTaglDown", true, isNormalized, wjet);
  
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

  //Z+Jets
  double sf_zjet = 1;
  baseDir = "DYjets";
  TH1F* zjet = DC.readWriteHisto(fDY, baseDir+"/base"+histSubDir, histName, sf_zjet, fout, fTT, "zjet", true);
  TH1F *zjet_LeptonUp,*zjet_LeptonDown;
  if(isMuChannel){
    zjet_LeptonUp = DC.readWriteHisto(fDY, baseDir+"/mueffup"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_LeptonUp", true);
    zjet_LeptonDown = DC.readWriteHisto(fDY, baseDir+"/mueffdown"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_LeptonDown", true);
  }else{
    zjet_LeptonUp = DC.readWriteHisto(fDY, baseDir+"/eleeffup"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_LeptonUp", true);
    zjet_LeptonDown = DC.readWriteHisto(fDY, baseDir+"/eleeffdown"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_LeptonDown", true);
  }
  TH1F* zjet_JESUp = DC.readWriteHisto(fDY, baseDir+"/jecup"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_JESUp", true);
  TH1F* zjet_JESDown = DC.readWriteHisto(fDY, baseDir+"/jecdown"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_JESDown", true);
  TH1F* zjet_PileupUp = DC.readWriteHisto(fDY, baseDir+"/puup"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_PileupUp", true);
  TH1F* zjet_PileupDown = DC.readWriteHisto(fDY, baseDir+"/pudown"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_PileupDown", true);
  TH1F* zjet_PrefireUp, *zjet_PrefireDown;
  if(year==2016 or year==2017){
    zjet_PrefireUp = DC.readWriteHisto(fDY, baseDir+"/prefireup"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_PrefireUp", true);
    zjet_PrefireDown = DC.readWriteHisto(fDY, baseDir+"/prefiredown"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_PrefireDown", true);
  }else{
    zjet_PrefireUp = DC.readWriteHisto(fDY, baseDir+"/base"+histSubDir, histName, sf_zjet, fout, fTT,  "zjet_PrefireUp", true);
    zjet_PrefireDown = DC.readWriteHisto(fDY, baseDir+"/base"+histSubDir, histName, sf_zjet, fout, fTT,  "zjet_PrefireDown", true);
  }
  TH1F* zjet_PUJetIDUp = DC.readWriteHisto(fDY, baseDir+"/pujetidup"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_PUJetIDUp", true);
  TH1F* zjet_PUJetIDDown = DC.readWriteHisto(fDY, baseDir+"/pujetiddown"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_PUJetIDDown", true);
  TH1F* zjet_JERUp = DC.readWriteHisto(fDY, baseDir+"/jerup"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_JERUp", true);
  TH1F* zjet_JERDown = DC.readWriteHisto(fDY, baseDir+"/jerdown"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_JERDown", true);
  TH1F* zjet_bcstatUp = DC.readWriteHisto(fDY, baseDir+"/bcstatup"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_bcstatUp", true, isNormalized, zjet);
  TH1F* zjet_bcstatDown = DC.readWriteHisto(fDY, baseDir+"/bcstatdown"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_bcstatDown", true, isNormalized, zjet);
  TH1F *zjet_bcintpUp, *zjet_bcintpDown, *zjet_bcextpUp, *zjet_bcextpDown, *zjet_bcxdybUp, *zjet_bcxdybDown, *zjet_bcxdycUp, *zjet_bcxdycDown, *zjet_bcxwjcUp, *zjet_bcxwjcDown;

  zjet_bcintpUp = DC.readWriteHisto(fDY, baseDir+"/bcintpup"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_bcintpUp", true, isNormalized, zjet);
  zjet_bcintpDown = DC.readWriteHisto(fDY, baseDir+"/bcintpdown"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_bcintpDown", true, isNormalized, zjet);
  zjet_bcextpUp = DC.readWriteHisto(fDY, baseDir+"/bcextpup"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_bcextpUp", true, isNormalized, zjet);
  zjet_bcextpDown = DC.readWriteHisto(fDY, baseDir+"/bcextpdown"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_bcextpDown", true, isNormalized, zjet);
  zjet_bcxdybUp = DC.readWriteHisto(fDY, baseDir+"/bcxdybup"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_bcxdybUp", true, isNormalized, zjet);
  zjet_bcxdybDown = DC.readWriteHisto(fDY, baseDir+"/bcxdybdown"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_bcxdybDown", true, isNormalized, zjet);
  zjet_bcxdycUp = DC.readWriteHisto(fDY, baseDir+"/bcxdycup"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_bcxdycUp", true, isNormalized, zjet);
  zjet_bcxdycDown = DC.readWriteHisto(fDY, baseDir+"/bcxdycdown"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_bcxdycDown", true, isNormalized, zjet);
  zjet_bcxwjcUp = DC.readWriteHisto(fDY, baseDir+"/bcxwjcup"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_bcxwjcUp", true, isNormalized, zjet);
  zjet_bcxwjcDown = DC.readWriteHisto(fDY, baseDir+"/bcxwjcdown"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_bcxwjcDown", true, isNormalized, zjet);
  
  TH1F* zjet_pdfUp = DC.readWriteHisto(fDY, baseDir+"/pdfup"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_pdfUp", true);
  TH1F* zjet_pdfDown = DC.readWriteHisto(fDY, baseDir+"/pdfdown"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_pdfDown", true);
  // TH1F* zjet_q2Up = DC.readWriteHisto(fDY, baseDir+"/q2up"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_q2Up", true);
  // TH1F* zjet_q2Down = DC.readWriteHisto(fDY, baseDir+"/q2down"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_q2Down", true);
  TH1F* zjet_bclhemufUp = DC.readWriteHisto(fDY, baseDir+"/bclhemufup"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_bclhemufUp", true, isNormalized, zjet);
  TH1F* zjet_bclhemufDown = DC.readWriteHisto(fDY, baseDir+"/bclhemufdown"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_bclhemufDown", true, isNormalized, zjet);
  TH1F* zjet_bclhemurUp = DC.readWriteHisto(fDY, baseDir+"/bclhemurup"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_bclhemurUp", true, isNormalized, zjet);
  TH1F* zjet_bclhemurDown = DC.readWriteHisto(fDY, baseDir+"/bclhemurdown"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_bclhemurDown", true, isNormalized, zjet);
  TH1F* zjet_isrUp = DC.readWriteHisto(fDY, baseDir+"/isrup"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_isrUp", true, isNormalized, zjet);
  TH1F* zjet_isrDown = DC.readWriteHisto(fDY, baseDir+"/isrdown"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_isrDown", true, isNormalized, zjet);
  TH1F* zjet_fsrUp = DC.readWriteHisto(fDY, baseDir+"/fsrup"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_fsrUp", true, isNormalized, zjet);
  TH1F* zjet_fsrDown = DC.readWriteHisto(fDY, baseDir+"/fsrdown"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_fsrDown", true, isNormalized, zjet);
  // //MiniAOD nuisances
  // TH1F* zjet_bcTag1Up = DC.readWriteHisto(fDY, baseDir+"/bctag1up"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_bcTag1Up", true, isNormalized, zjet);
  // TH1F* zjet_bcTag1Down = DC.readWriteHisto(fDY, baseDir+"/bctag1down"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_bcTag1Down", true, isNormalized, zjet);
  // TH1F* zjet_bcTag2Up = DC.readWriteHisto(fDY, baseDir+"/bctag2up"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_bcTag2Up", true, isNormalized, zjet);
  // TH1F* zjet_bcTag2Down = DC.readWriteHisto(fDY, baseDir+"/bctag2down"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_bcTag2Down", true, isNormalized, zjet);
  // TH1F* zjet_bcTag3Up = DC.readWriteHisto(fDY, baseDir+"/bctag3up"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_bcTag3Up", true, isNormalized, zjet);
  // TH1F* zjet_bcTag3Down = DC.readWriteHisto(fDY, baseDir+"/bctag3down"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_bcTag3Down", true, isNormalized, zjet);
  // TH1F* zjet_bTagbcUp = DC.readWriteHisto(fDY, baseDir+"/btagbup"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_bTagbcUp", true, isNormalized, zjet);
  // TH1F* zjet_bTagbcDown = DC.readWriteHisto(fDY, baseDir+"/btagbdown"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_bTagbcDown", true, isNormalized, zjet);
  // TH1F* zjet_bTaglUp = DC.readWriteHisto(fDY, baseDir+"/btaglup"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_bTaglUp", true, isNormalized, zjet);
  // TH1F* zjet_bTaglDown = DC.readWriteHisto(fDY, baseDir+"/btagldown"+histSubDir, histName, sf_zjet, fout, fTT, "zjet_bTaglDown", true, isNormalized, zjet);

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
    stop_LeptonUp = DC.readWriteHisto(fST, baseDir+"/mueffup"+histSubDir, histName, sf_stop, fout, fTT, "stop_LeptonUp", true);
    stop_LeptonDown = DC.readWriteHisto(fST, baseDir+"/mueffdown"+histSubDir, histName, sf_stop, fout, fTT, "stop_LeptonDown", true);
  }else{
    stop_LeptonUp = DC.readWriteHisto(fST, baseDir+"/eleeffup"+histSubDir, histName, sf_stop, fout, fTT, "stop_LeptonUp", true);
    stop_LeptonDown = DC.readWriteHisto(fST, baseDir+"/eleeffdown"+histSubDir, histName, sf_stop, fout, fTT, "stop_LeptonDown", true);
  }
  TH1F* stop_JESUp = DC.readWriteHisto(fST, baseDir+"/jecup"+histSubDir, histName, sf_stop, fout, fTT, "stop_JESUp", true);
  TH1F* stop_JESDown = DC.readWriteHisto(fST, baseDir+"/jecdown"+histSubDir, histName, sf_stop, fout, fTT, "stop_JESDown", true);
  TH1F* stop_PileupUp = DC.readWriteHisto(fST, baseDir+"/puup"+histSubDir, histName, sf_stop, fout, fTT, "stop_PileupUp", true);
  TH1F* stop_PileupDown = DC.readWriteHisto(fST, baseDir+"/pudown"+histSubDir, histName, sf_stop, fout, fTT, "stop_PileupDown", true);
  TH1F* stop_PrefireUp, *stop_PrefireDown;
  if(year==2016 or year==2017){
    stop_PrefireUp = DC.readWriteHisto(fST, baseDir+"/prefireup"+histSubDir, histName, sf_stop, fout, fTT, "stop_PrefireUp", true);
    stop_PrefireDown = DC.readWriteHisto(fST, baseDir+"/prefiredown"+histSubDir, histName, sf_stop, fout, fTT, "stop_PrefireDown", true);
  }else{
    stop_PrefireUp = DC.readWriteHisto(fST, baseDir+"/base"+histSubDir, histName, sf_stop, fout, fTT,  "stop_PrefireUp", true);
    stop_PrefireDown = DC.readWriteHisto(fST, baseDir+"/base"+histSubDir, histName, sf_stop, fout, fTT,  "stop_PrefireDown", true);
  }
  TH1F* stop_PUJetIDUp = DC.readWriteHisto(fST, baseDir+"/pujetidup"+histSubDir, histName, sf_stop, fout, fTT, "stop_PUJetIDUp", true);
  TH1F* stop_PUJetIDDown = DC.readWriteHisto(fST, baseDir+"/pujetiddown"+histSubDir, histName, sf_stop, fout, fTT, "stop_PUJetIDDown", true);
  TH1F* stop_JERUp = DC.readWriteHisto(fST, baseDir+"/jerup"+histSubDir, histName, sf_stop, fout, fTT, "stop_JERUp", true);
  TH1F* stop_JERDown = DC.readWriteHisto(fST, baseDir+"/jerdown"+histSubDir, histName, sf_stop, fout, fTT, "stop_JERDown", true);
  TH1F* stop_bcstatUp = DC.readWriteHisto(fST, baseDir+"/bcstatup"+histSubDir, histName, sf_stop, fout, fTT, "stop_bcstatUp", true, isNormalized, stop);
  TH1F* stop_bcstatDown = DC.readWriteHisto(fST, baseDir+"/bcstatdown"+histSubDir, histName, sf_stop, fout, fTT, "stop_bcstatDown", true, isNormalized, stop);
  TH1F *stop_bcintpUp, *stop_bcintpDown, *stop_bcextpUp, *stop_bcextpDown, *stop_bcxdybUp, *stop_bcxdybDown, *stop_bcxdycUp, *stop_bcxdycDown, *stop_bcxwjcUp, *stop_bcxwjcDown;

    stop_bcintpUp = DC.readWriteHisto(fST, baseDir+"/bcintpup"+histSubDir, histName, sf_stop, fout, fTT, "stop_bcintpUp", true, isNormalized, stop);
    stop_bcintpDown = DC.readWriteHisto(fST, baseDir+"/bcintpdown"+histSubDir, histName, sf_stop, fout, fTT, "stop_bcintpDown", true, isNormalized, stop);
    stop_bcextpUp = DC.readWriteHisto(fST, baseDir+"/bcextpup"+histSubDir, histName, sf_stop, fout, fTT, "stop_bcextpUp", true, isNormalized, stop);
    stop_bcextpDown = DC.readWriteHisto(fST, baseDir+"/bcextpdown"+histSubDir, histName, sf_stop, fout, fTT, "stop_bcextpDown", true, isNormalized, stop);
    stop_bcxdybUp = DC.readWriteHisto(fST, baseDir+"/bcxdybup"+histSubDir, histName, sf_stop, fout, fTT, "stop_bcxdybUp", true, isNormalized, stop);
    stop_bcxdybDown = DC.readWriteHisto(fST, baseDir+"/bcxdybdown"+histSubDir, histName, sf_stop, fout, fTT, "stop_bcxdybDown", true, isNormalized, stop);
    stop_bcxdycUp = DC.readWriteHisto(fST, baseDir+"/bcxdycup"+histSubDir, histName, sf_stop, fout, fTT, "stop_bcxdycUp", true, isNormalized, stop);
    stop_bcxdycDown = DC.readWriteHisto(fST, baseDir+"/bcxdycdown"+histSubDir, histName, sf_stop, fout, fTT, "stop_bcxdycDown", true, isNormalized, stop);
    stop_bcxwjcUp = DC.readWriteHisto(fST, baseDir+"/bcxwjcup"+histSubDir, histName, sf_stop, fout, fTT, "stop_bcxwjcUp", true, isNormalized, stop);
    stop_bcxwjcDown = DC.readWriteHisto(fST, baseDir+"/bcxwjcdown"+histSubDir, histName, sf_stop, fout, fTT, "stop_bcxwjcDown", true, isNormalized, stop);

  TH1F* stop_pdfUp = DC.readWriteHisto(fST, baseDir+"/pdfup"+histSubDir, histName, sf_stop, fout, fTT, "stop_pdfUp", true);
  TH1F* stop_pdfDown = DC.readWriteHisto(fST, baseDir+"/pdfdown"+histSubDir, histName, sf_stop, fout, fTT, "stop_pdfDown", true);
  // TH1F* stop_q2Up = DC.readWriteHisto(fST, baseDir+"/q2up"+histSubDir, histName, sf_stop, fout, fTT, "stop_q2Up", true);
  // TH1F* stop_q2Down = DC.readWriteHisto(fST, baseDir+"/q2down"+histSubDir, histName, sf_stop, fout, fTT, "stop_q2Down", true);
  TH1F* stop_bclhemufUp = DC.readWriteHisto(fST, baseDir+"/bclhemufup"+histSubDir, histName, sf_stop, fout, fTT, "stop_bclhemufUp", true, isNormalized, stop);
  TH1F* stop_bclhemufDown = DC.readWriteHisto(fST, baseDir+"/bclhemufdown"+histSubDir, histName, sf_stop, fout, fTT, "stop_bclhemufDown", true, isNormalized, stop);
  TH1F* stop_bclhemurUp = DC.readWriteHisto(fST, baseDir+"/bclhemurup"+histSubDir, histName, sf_stop, fout, fTT, "stop_bclhemurUp", true, isNormalized, stop);
  TH1F* stop_bclhemurDown = DC.readWriteHisto(fST, baseDir+"/bclhemurdown"+histSubDir, histName, sf_stop, fout, fTT, "stop_bclhemurDown", true, isNormalized, stop);
  TH1F* stop_isrUp = DC.readWriteHisto(fST, baseDir+"/isrup"+histSubDir, histName, sf_stop, fout, fTT, "stop_isrUp", true, isNormalized, stop);
  TH1F* stop_isrDown = DC.readWriteHisto(fST, baseDir+"/isrdown"+histSubDir, histName, sf_stop, fout, fTT, "stop_isrDown", true, isNormalized, stop);
  TH1F* stop_fsrUp = DC.readWriteHisto(fST, baseDir+"/fsrup"+histSubDir, histName, sf_stop, fout, fTT, "stop_fsrUp", true, isNormalized, stop);
  TH1F* stop_fsrDown = DC.readWriteHisto(fST, baseDir+"/fsrdown"+histSubDir, histName, sf_stop, fout, fTT, "stop_fsrDown", true, isNormalized, stop);
  // //MiniAOD nuisances
  // TH1F* stop_bcTag1Up = DC.readWriteHisto(fST, baseDir+"/bctag1up"+histSubDir, histName, sf_stop, fout, fTT, "stop_bcTag1Up", true, isNormalized, stop);
  // TH1F* stop_bcTag1Down = DC.readWriteHisto(fST, baseDir+"/bctag1down"+histSubDir, histName, sf_stop, fout, fTT, "stop_bcTag1Down", true, isNormalized, stop);
  // TH1F* stop_bcTag2Up = DC.readWriteHisto(fST, baseDir+"/bctag2up"+histSubDir, histName, sf_stop, fout, fTT, "stop_bcTag2Up", true, isNormalized, stop);
  // TH1F* stop_bcTag2Down = DC.readWriteHisto(fST, baseDir+"/bctag2down"+histSubDir, histName, sf_stop, fout, fTT, "stop_bcTag2Down", true, isNormalized, stop);
  // TH1F* stop_bcTag3Up = DC.readWriteHisto(fST, baseDir+"/bctag3up"+histSubDir, histName, sf_stop, fout, fTT, "stop_bcTag3Up", true, isNormalized, stop);
  // TH1F* stop_bcTag3Down = DC.readWriteHisto(fST, baseDir+"/bctag3down"+histSubDir, histName, sf_stop, fout, fTT, "stop_bcTag3Down", true, isNormalized, stop);
  // TH1F* stop_bTagbcUp = DC.readWriteHisto(fST, baseDir+"/btagbup"+histSubDir, histName, sf_stop, fout, fTT, "stop_bTagbcUp", true, isNormalized, stop);
  // TH1F* stop_bTagbcDown = DC.readWriteHisto(fST, baseDir+"/btagbdown"+histSubDir, histName, sf_stop, fout, fTT, "stop_bTagbcDown", true, isNormalized, stop);
  // TH1F* stop_bTaglUp = DC.readWriteHisto(fST, baseDir+"/btaglup"+histSubDir, histName, sf_stop, fout, fTT, "stop_bTaglUp", true, isNormalized, stop);
  // TH1F* stop_bTaglDown = DC.readWriteHisto(fST, baseDir+"/btagldown"+histSubDir, histName, sf_stop, fout, fTT, "stop_bTaglDown", true, isNormalized, stop);
  
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
    vv_LeptonUp = DC.readWriteHisto(fVV, baseDir+"/mueffup"+histSubDir, histName, sf_vv, fout, fTT, "vv_LeptonUp", true);
    vv_LeptonDown = DC.readWriteHisto(fVV, baseDir+"/mueffdown"+histSubDir, histName, sf_vv, fout, fTT, "vv_LeptonDown", true);
  }else{
    vv_LeptonUp = DC.readWriteHisto(fVV, baseDir+"/eleeffup"+histSubDir, histName, sf_vv, fout, fTT, "vv_LeptonUp", true);
    vv_LeptonDown = DC.readWriteHisto(fVV, baseDir+"/eleeffdown"+histSubDir, histName, sf_vv, fout, fTT, "vv_LeptonDown", true);
  }
  TH1F* vv_JESUp = DC.readWriteHisto(fVV, baseDir+"/jecup"+histSubDir, histName, sf_vv, fout, fTT, "vv_JESUp", true);
  TH1F* vv_JESDown = DC.readWriteHisto(fVV, baseDir+"/jecdown"+histSubDir, histName, sf_vv, fout, fTT, "vv_JESDown", true);
  TH1F* vv_PileupUp = DC.readWriteHisto(fVV, baseDir+"/puup"+histSubDir, histName, sf_vv, fout, fTT, "vv_PileupUp", true);
  TH1F* vv_PileupDown = DC.readWriteHisto(fVV, baseDir+"/pudown"+histSubDir, histName, sf_vv, fout, fTT, "vv_PileupDown", true);
  TH1F* vv_PrefireUp, *vv_PrefireDown;
  if(year==2016 or year==2017){
    vv_PrefireUp = DC.readWriteHisto(fVV, baseDir+"/prefireup"+histSubDir, histName, sf_vv, fout, fTT, "vv_PrefireUp", true);
    vv_PrefireDown = DC.readWriteHisto(fVV, baseDir+"/prefiredown"+histSubDir, histName, sf_vv, fout, fTT, "vv_PrefireDown", true);
  }else{
    vv_PrefireUp = DC.readWriteHisto(fVV, baseDir+"/base"+histSubDir, histName, sf_vv, fout, fTT,  "vv_PrefireUp", true);
    vv_PrefireDown = DC.readWriteHisto(fVV, baseDir+"/base"+histSubDir, histName, sf_vv, fout, fTT,  "vv_PrefireDown", true);
  }
  TH1F* vv_PUJetIDUp = DC.readWriteHisto(fVV, baseDir+"/pujetidup"+histSubDir, histName, sf_vv, fout, fTT, "vv_PUJetIDUp", true);
  TH1F* vv_PUJetIDDown = DC.readWriteHisto(fVV, baseDir+"/pujetiddown"+histSubDir, histName, sf_vv, fout, fTT, "vv_PUJetIDDown", true);
  TH1F* vv_JERUp = DC.readWriteHisto(fVV, baseDir+"/jerup"+histSubDir, histName, sf_vv, fout, fTT, "vv_JERUp", true);
  TH1F* vv_JERDown = DC.readWriteHisto(fVV, baseDir+"/jerdown"+histSubDir, histName, sf_vv, fout, fTT, "vv_JERDown", true);
  TH1F* vv_bcstatUp = DC.readWriteHisto(fVV, baseDir+"/bcstatup"+histSubDir, histName, sf_vv, fout, fTT, "vv_bcstatUp", true, isNormalized, vv);
  TH1F* vv_bcstatDown = DC.readWriteHisto(fVV, baseDir+"/bcstatdown"+histSubDir, histName, sf_vv, fout, fTT, "vv_bcstatDown", true, isNormalized, vv);
  TH1F *vv_bcintpUp, *vv_bcintpDown, *vv_bcextpUp, *vv_bcextpDown, *vv_bcxdybUp, *vv_bcxdybDown, *vv_bcxdycUp, *vv_bcxdycDown, *vv_bcxwjcUp, *vv_bcxwjcDown;

  vv_bcintpUp = DC.readWriteHisto(fVV, baseDir+"/bcintpup"+histSubDir, histName, sf_vv, fout, fTT, "vv_bcintpUp", true, isNormalized, vv);
  vv_bcintpDown = DC.readWriteHisto(fVV, baseDir+"/bcintpdown"+histSubDir, histName, sf_vv, fout, fTT, "vv_bcintpDown", true, isNormalized, vv);
  vv_bcextpUp = DC.readWriteHisto(fVV, baseDir+"/bcextpup"+histSubDir, histName, sf_vv, fout, fTT, "vv_bcextpUp", true, isNormalized, vv);
  vv_bcextpDown = DC.readWriteHisto(fVV, baseDir+"/bcextpdown"+histSubDir, histName, sf_vv, fout, fTT, "vv_bcextpDown", true, isNormalized, vv);
  vv_bcxdybUp = DC.readWriteHisto(fVV, baseDir+"/bcxdybup"+histSubDir, histName, sf_vv, fout, fTT, "vv_bcxdybUp", true, isNormalized, vv);
  vv_bcxdybDown = DC.readWriteHisto(fVV, baseDir+"/bcxdybdown"+histSubDir, histName, sf_vv, fout, fTT, "vv_bcxdybDown", true, isNormalized, vv);
  vv_bcxdycUp = DC.readWriteHisto(fVV, baseDir+"/bcxdycup"+histSubDir, histName, sf_vv, fout, fTT, "vv_bcxdycUp", true, isNormalized, vv);
  vv_bcxdycDown = DC.readWriteHisto(fVV, baseDir+"/bcxdycdown"+histSubDir, histName, sf_vv, fout, fTT, "vv_bcxdycDown", true, isNormalized, vv);
  vv_bcxwjcUp = DC.readWriteHisto(fVV, baseDir+"/bcxwjcup"+histSubDir, histName, sf_vv, fout, fTT, "vv_bcxwjcUp", true, isNormalized, vv);
  vv_bcxwjcDown = DC.readWriteHisto(fVV, baseDir+"/bcxwjcdown"+histSubDir, histName, sf_vv, fout, fTT, "vv_bcxwjcDown", true, isNormalized, vv);

  TH1F* vv_pdfUp = DC.readWriteHisto(fVV, baseDir+"/pdfup"+histSubDir, histName, sf_vv, fout, fTT, "vv_pdfUp", true);
  TH1F* vv_pdfDown = DC.readWriteHisto(fVV, baseDir+"/pdfdown"+histSubDir, histName, sf_vv, fout, fTT, "vv_pdfDown", true);
  // TH1F* vv_q2Up = DC.readWriteHisto(fVV, baseDir+"/q2up"+histSubDir, histName, sf_vv, fout, fTT, "vv_q2Up", true);
  // TH1F* vv_q2Down = DC.readWriteHisto(fVV, baseDir+"/q2down"+histSubDir, histName, sf_vv, fout, fTT, "vv_q2Down", true);
  TH1F* vv_bclhemufUp = DC.readWriteHisto(fVV, baseDir+"/bclhemufup"+histSubDir, histName, sf_vv, fout, fTT, "vv_bclhemufUp", true, isNormalized, vv);
  TH1F* vv_bclhemufDown = DC.readWriteHisto(fVV, baseDir+"/bclhemufdown"+histSubDir, histName, sf_vv, fout, fTT, "vv_bclhemufDown", true, isNormalized, vv);
  TH1F* vv_bclhemurUp = DC.readWriteHisto(fVV, baseDir+"/bclhemurup"+histSubDir, histName, sf_vv, fout, fTT, "vv_bclhemurUp", true, isNormalized, vv);
  TH1F* vv_bclhemurDown = DC.readWriteHisto(fVV, baseDir+"/bclhemurdown"+histSubDir, histName, sf_vv, fout, fTT, "vv_bclhemurDown", true, isNormalized, vv);
  TH1F* vv_isrUp = DC.readWriteHisto(fVV, baseDir+"/isrup"+histSubDir, histName, sf_vv, fout, fTT, "vv_isrUp", true, isNormalized, vv);
  TH1F* vv_isrDown = DC.readWriteHisto(fVV, baseDir+"/isrdown"+histSubDir, histName, sf_vv, fout, fTT, "vv_isrDown", true, isNormalized, vv);
  TH1F* vv_fsrUp = DC.readWriteHisto(fVV, baseDir+"/fsrup"+histSubDir, histName, sf_vv, fout, fTT, "vv_fsrUp", true, isNormalized, vv);
  TH1F* vv_fsrDown = DC.readWriteHisto(fVV, baseDir+"/fsrdown"+histSubDir, histName, sf_vv, fout, fTT, "vv_fsrDown", true, isNormalized, vv);
  // //MiniAOD nuisances
  // TH1F* vv_bcTag1Up = DC.readWriteHisto(fVV, baseDir+"/bctag1up"+histSubDir, histName, sf_vv, fout, fTT, "vv_bcTag1Up", true, isNormalized, vv);
  // TH1F* vv_bcTag1Down = DC.readWriteHisto(fVV, baseDir+"/bctag1down"+histSubDir, histName, sf_vv, fout, fTT, "vv_bcTag1Down", true, isNormalized, vv);
  // TH1F* vv_bcTag2Up = DC.readWriteHisto(fVV, baseDir+"/bctag2up"+histSubDir, histName, sf_vv, fout, fTT, "vv_bcTag2Up", true, isNormalized, vv);
  // TH1F* vv_bcTag2Down = DC.readWriteHisto(fVV, baseDir+"/bctag2down"+histSubDir, histName, sf_vv, fout, fTT, "vv_bcTag2Down", true, isNormalized, vv);
  // TH1F* vv_bcTag3Up = DC.readWriteHisto(fVV, baseDir+"/bctag3up"+histSubDir, histName, sf_vv, fout, fTT, "vv_bcTag3Up", true, isNormalized, vv);
  // TH1F* vv_bcTag3Down = DC.readWriteHisto(fVV, baseDir+"/bctag3down"+histSubDir, histName, sf_vv, fout, fTT, "vv_bcTag3Down", true, isNormalized, vv);
  // TH1F* vv_bTagbcUp = DC.readWriteHisto(fVV, baseDir+"/btagbup"+histSubDir, histName, sf_vv, fout, fTT, "vv_bTagbcUp", true, isNormalized, vv);
  // TH1F* vv_bTagbcDown = DC.readWriteHisto(fVV, baseDir+"/btagbdown"+histSubDir, histName, sf_vv, fout, fTT, "vv_bTagbcDown", true, isNormalized, vv);
  // TH1F* vv_bTaglUp = DC.readWriteHisto(fVV, baseDir+"/btaglup"+histSubDir, histName, sf_vv, fout, fTT, "vv_bTaglUp", true, isNormalized, vv);
  // TH1F* vv_bTaglDown = DC.readWriteHisto(fVV, baseDir+"/btagldown"+histSubDir, histName, sf_vv, fout, fTT, "vv_bTaglDown", true, isNormalized, vv);

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
  TH1F* qcd_dd = DC.readWriteHisto(fQCD_dd, baseDir+"/base"+histSubDir, histName, sf_qcd, fout, fTT, "qcd", true);
  double stat_unc_qcd = DC.getStatUnc(qcd_dd, 0);
  // cout<<"qcd stat unc: "<<stat_unc_qcd<<endl;
  // cout<<"qcd = "<<qcd_dd->Integral()<<endl;
  //double qcd_unc = DC.getSysUncQcd(fData, fTT, fST, fWJ, fDY,  fVV, histSubDir_+"/", histName, false);
  cout << "histname : "<<histName << endl;  
  double qcd_unc = DC.getSysUncQcdNano(isMuChannel, fData, fTT, fST, fWJ, fDY,  fVV, histSubDir_+"/", histName, false);
  if(isBinStat){
    for(int ibin = 1; ibin <= nonStatBins ; ibin++){
      TH1F *qcd_bin_stat_Up = DC.readWriteHisto(fQCD_dd, baseDir+"/base"+histSubDir, histName, sf_qcd, fout, fTT, Form("qcd_CMS_stat_cat1_qcd_bin_%dUp",ibin), true);
      TH1F *qcd_bin_stat_Do = DC.readWriteHisto(fQCD_dd, baseDir+"/base"+histSubDir, histName, sf_qcd, fout, fTT, Form("qcd_CMS_stat_cat1_qcd_bin_%dDown",ibin), true);
    }
  }
  
  //Data
  double sf_data = 1.0; //should be 1, always
  baseDir = (isMuChannel) ? "DataMu" : "DataEle";
  TH1F* data_obs = DC.readWriteHisto(fData, baseDir+"/base"+histSubDir, histName, sf_data, fout, fTT, "data_obs", true);
  //TH1F* data_obs = DC.readWriteHisto(fTT, "TTbar/base"+histSubDir, histName, sf_data, fout, fTT, "data_obs", true);
  //cout<<":data_obs ================: "<<data_obs->Integral()<<endl;
  
  //wh
  double sf_wh = 1.0;
  baseDir = Form("HplusM%03d",mass);
  // double sf_wh = 1.0/2.0;
  // baseDir = Form("HplmiM%03d",mass);
  TH1F* wh = DC.readWriteHisto(fWH, baseDir+"/base"+histSubDir, histName, sf_wh, fout, fTT, label, true);
  TH1F *wh_LeptonUp,*wh_LeptonDown;
  if(isMuChannel){
    wh_LeptonUp = DC.readWriteHisto(fWH, baseDir+"/mueffup"+histSubDir, histName, sf_wh, fout, fTT, label+"_LeptonUp", true);
    wh_LeptonDown = DC.readWriteHisto(fWH, baseDir+"/mueffdown"+histSubDir, histName, sf_wh, fout, fTT, label+"_LeptonDown", true);
  }else{
    wh_LeptonUp = DC.readWriteHisto(fWH, baseDir+"/eleeffup"+histSubDir, histName, sf_wh, fout, fTT, label+"_LeptonUp", true);
    wh_LeptonDown = DC.readWriteHisto(fWH, baseDir+"/eleeffdown"+histSubDir, histName, sf_wh, fout, fTT, label+"_LeptonDown", true);
  }
  TH1F* wh_JESUp = DC.readWriteHisto(fWH, baseDir+"/jecup"+histSubDir, histName, sf_wh, fout, fTT, label+"_JESUp", true);
  TH1F* wh_JESDown = DC.readWriteHisto(fWH, baseDir+"/jecdown"+histSubDir, histName, sf_wh, fout, fTT, label+"_JESDown", true);
  TH1F* wh_PileupUp = DC.readWriteHisto(fWH, baseDir+"/puup"+histSubDir, histName, sf_wh, fout, fTT, label+"_PileupUp", true);
  TH1F* wh_PileupDown = DC.readWriteHisto(fWH, baseDir+"/pudown"+histSubDir, histName, sf_wh, fout, fTT, label+"_PileupDown", true);
  TH1F* wh_PrefireUp, *wh_PrefireDown;
  if(year==2016 or year==2017){
    wh_PrefireUp = DC.readWriteHisto(fWH, baseDir+"/prefireup"+histSubDir, histName, sf_wh, fout, fTT, label+"_PrefireUp", true);
    wh_PrefireDown = DC.readWriteHisto(fWH, baseDir+"/prefiredown"+histSubDir, histName, sf_wh, fout, fTT, label+"_PrefireDown", true);
  }else{
    wh_PrefireUp = DC.readWriteHisto(fWH, baseDir+"/base"+histSubDir, histName, sf_wh, fout, fTT,  label+"_PrefireUp", true);
    wh_PrefireDown = DC.readWriteHisto(fWH, baseDir+"/base"+histSubDir, histName, sf_wh, fout, fTT,  label+"_PrefireDown", true);
  }
  TH1F* wh_PUJetIDUp = DC.readWriteHisto(fWH, baseDir+"/pujetidup"+histSubDir, histName, sf_wh, fout, fTT, label+"_PUJetIDUp", true);
  TH1F* wh_PUJetIDDown = DC.readWriteHisto(fWH, baseDir+"/pujetiddown"+histSubDir, histName, sf_wh, fout, fTT, label+"_PUJetIDDown", true);
  TH1F* wh_JERUp = DC.readWriteHisto(fWH, baseDir+"/jerup"+histSubDir, histName, sf_wh, fout, fTT, label+"_JERUp", true);
  TH1F* wh_JERDown = DC.readWriteHisto(fWH, baseDir+"/jerdown"+histSubDir, histName, sf_wh, fout, fTT, label+"_JERDown", true);
  TH1F* wh_bcstatUp = DC.readWriteHisto(fWH, baseDir+"/bcstatup"+histSubDir, histName, sf_wh, fout, fTT, label+"_bcstatUp", true, isNormalized, wh);
  TH1F* wh_bcstatDown = DC.readWriteHisto(fWH, baseDir+"/bcstatdown"+histSubDir, histName, sf_wh, fout, fTT, label+"_bcstatDown", true, isNormalized, wh);
  TH1F *wh_bcintpUp, *wh_bcintpDown, *wh_bcextpUp, *wh_bcextpDown, *wh_bcxdybUp, *wh_bcxdybDown, *wh_bcxdycUp, *wh_bcxdycDown, *wh_bcxwjcUp, *wh_bcxwjcDown;
  wh_bcintpUp = DC.readWriteHisto(fWH, baseDir+"/bcintpup"+histSubDir, histName, sf_wh, fout, fTT, label+"_bcintpUp", true, isNormalized, wh);
  wh_bcintpDown = DC.readWriteHisto(fWH, baseDir+"/bcintpdown"+histSubDir, histName, sf_wh, fout, fTT, label+"_bcintpDown", true, isNormalized, wh);
  wh_bcextpUp = DC.readWriteHisto(fWH, baseDir+"/bcextpup"+histSubDir, histName, sf_wh, fout, fTT, label+"_bcextpUp", true, isNormalized, wh);
  wh_bcextpDown = DC.readWriteHisto(fWH, baseDir+"/bcextpdown"+histSubDir, histName, sf_wh, fout, fTT, label+"_bcextpDown", true, isNormalized, wh);
  wh_bcxdybUp = DC.readWriteHisto(fWH, baseDir+"/bcxdybup"+histSubDir, histName, sf_wh, fout, fTT, label+"_bcxdybUp", true, isNormalized, wh);
  wh_bcxdybDown = DC.readWriteHisto(fWH, baseDir+"/bcxdybdown"+histSubDir, histName, sf_wh, fout, fTT, label+"_bcxdybDown", true, isNormalized, wh);
  wh_bcxdycUp = DC.readWriteHisto(fWH, baseDir+"/bcxdycup"+histSubDir, histName, sf_wh, fout, fTT, label+"_bcxdycUp", true, isNormalized, wh);
  wh_bcxdycDown = DC.readWriteHisto(fWH, baseDir+"/bcxdycdown"+histSubDir, histName, sf_wh, fout, fTT, label+"_bcxdycDown", true, isNormalized, wh);
  wh_bcxwjcUp = DC.readWriteHisto(fWH, baseDir+"/bcxwjcup"+histSubDir, histName, sf_wh, fout, fTT, label+"_bcxwjcUp", true, isNormalized, wh);
  wh_bcxwjcDown = DC.readWriteHisto(fWH, baseDir+"/bcxwjcdown"+histSubDir, histName, sf_wh, fout, fTT, label+"_bcxwjcDown", true, isNormalized, wh);
  
  TH1F* wh_pdfUp = DC.readWriteHisto(fWH, baseDir+"/pdfup"+histSubDir, histName, sf_wh, fout, fTT, label+"_pdfUp", true);
  TH1F* wh_pdfDown = DC.readWriteHisto(fWH, baseDir+"/pdfdown"+histSubDir, histName, sf_wh, fout, fTT, label+"_pdfDown", true);
  // TH1F* wh_q2Up = DC.readWriteHisto(fWH, baseDir+"/q2up"+histSubDir, histName, sf_wh, fout, fTT, label+"_q2Up", true);
  // TH1F* wh_q2Down = DC.readWriteHisto(fWH, baseDir+"/q2down"+histSubDir, histName, sf_wh, fout, fTT, label+"_q2Down", true);
  TH1F* wh_bclhemufUp = DC.readWriteHisto(fWH, baseDir+"/bclhemufup"+histSubDir, histName, sf_wh, fout, fTT, label+"_bclhemufUp", true, isNormalized, wh);
  TH1F* wh_bclhemufDown = DC.readWriteHisto(fWH, baseDir+"/bclhemufdown"+histSubDir, histName, sf_wh, fout, fTT, label+"_bclhemufDown", true, isNormalized, wh);
  TH1F* wh_bclhemurUp = DC.readWriteHisto(fWH, baseDir+"/bclhemurup"+histSubDir, histName, sf_wh, fout, fTT, label+"_bclhemurUp", true, isNormalized, wh);
  TH1F* wh_bclhemurDown = DC.readWriteHisto(fWH, baseDir+"/bclhemurdown"+histSubDir, histName, sf_wh, fout, fTT, label+"_bclhemurDown", true, isNormalized, wh);
  TH1F* wh_isrUp = DC.readWriteHisto(fWH, baseDir+"/isrup"+histSubDir, histName, sf_wh, fout, fTT, label+"_isrUp", true, isNormalized, wh);
  TH1F* wh_isrDown = DC.readWriteHisto(fWH, baseDir+"/isrdown"+histSubDir, histName, sf_wh, fout, fTT, label+"_isrDown", true, isNormalized, wh);
  TH1F* wh_fsrUp = DC.readWriteHisto(fWH, baseDir+"/fsrup"+histSubDir, histName, sf_wh, fout, fTT, label+"_fsrUp", true, isNormalized, wh);
  TH1F* wh_fsrDown = DC.readWriteHisto(fWH, baseDir+"/fsrdown"+histSubDir, histName, sf_wh, fout, fTT, label+"_fsrDown", true, isNormalized, wh);
  // //MiniAOD nuisances
  // TH1F* wh_bcTag1Up = DC.readWriteHisto(fWH, baseDir+"/bctag1up"+histSubDir, histName, sf_wh, fout, fTT, label+"_bcTag1Up", true, isNormalized, wh);
  // TH1F* wh_bcTag1Down = DC.readWriteHisto(fWH, baseDir+"/bctag1down"+histSubDir, histName, sf_wh, fout, fTT, label+"_bcTag1Down", true, isNormalized, wh);
  // TH1F* wh_bcTag2Up = DC.readWriteHisto(fWH, baseDir+"/bctag2up"+histSubDir, histName, sf_wh, fout, fTT, label+"_bcTag2Up", true, isNormalized, wh);
  // TH1F* wh_bcTag2Down = DC.readWriteHisto(fWH, baseDir+"/bctag2down"+histSubDir, histName, sf_wh, fout, fTT, label+"_bcTag2Down", true, isNormalized, wh);
  // TH1F* wh_bcTag3Up = DC.readWriteHisto(fWH, baseDir+"/bctag3up"+histSubDir, histName, sf_wh, fout, fTT, label+"_bcTag3Up", true, isNormalized, wh);
  // TH1F* wh_bcTag3Down = DC.readWriteHisto(fWH, baseDir+"/bctag3down"+histSubDir, histName, sf_wh, fout, fTT, label+"_bcTag3Down", true, isNormalized, wh);
  // TH1F* wh_topPtUp = DC.readWriteHisto(fWH, baseDir+"/topptup"+histSubDir, histName, sf_wh, fout, fTT, label+"_topPtUp", true, isNormalized, wh);
  // TH1F* wh_topPtDown = DC.readWriteHisto(fWH, baseDir+"/topptdown"+histSubDir, histName, sf_wh, fout, fTT, label+"_topPtDown", true, isNormalized, wh);
  // TH1F* wh_bTagbcUp = DC.readWriteHisto(fWH, baseDir+"/btagbup"+histSubDir, histName, sf_wh, fout, fTT, label+"_bTagbcUp", true, isNormalized, wh);
  // TH1F* wh_bTagbcDown = DC.readWriteHisto(fWH, baseDir+"/btagbdown"+histSubDir, histName, sf_wh, fout, fTT, label+"_bTagbcDown", true, isNormalized, wh);
  // TH1F* wh_bTaglUp = DC.readWriteHisto(fWH, baseDir+"/btaglup"+histSubDir, histName, sf_wh, fout, fTT, label+"_bTaglUp", true, isNormalized, wh);
  // TH1F* wh_bTaglDown = DC.readWriteHisto(fWH, baseDir+"/btagldown"+histSubDir, histName, sf_wh, fout, fTT, label+"_bTaglDown", true, isNormalized, wh);

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
  	    << space << wjet->Integral()
  	    << space << zjet->Integral()
  	    << space << stop->Integral()
  	    << space << vv->Integral()
            << space << qcd_dd->Integral()
            << endl;
	
      }
      else if(line.find("CMS_lumi_13TeV ")!=string::npos){
        line.replace( line.find("HHHH") , 4 , string(Form("%.3f", lumiUnc)) );
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", lumiUnc)) ); 
        line.replace( line.find("WWWW") , 4 , string(Form("%.3f", lumiUnc)) ); 
        line.replace( line.find("DDDD") , 4 , string(Form("%.3f", lumiUnc)) ); 
        line.replace( line.find("SSSS") , 4 , string(Form("%.3f", lumiUnc)) ); 
        line.replace( line.find("VVVV") , 4 , string(Form("%.3f", lumiUnc)) ); 
        out << line << endl;

      }
      else if(line.find("CMS_eff_lep ")!=string::npos){  

        if(isMuChannel) line.replace( line.find("lep") , 4 , string(Form("%s", "m")));   
        else line.replace( line.find("lep") , 4 , string(Form("%s", "e")));

  	float leptonUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_LeptonUp, wh_LeptonDown) : 1.00;
  	line.replace( line.find("HHHH") , 4 , string(Form("%.3f", leptonUnc_wh)) );
        
  	float leptonUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_LeptonUp, ttbar_LeptonDown) : 1.00; 
  	line.replace( line.find("TTTT") , 4 , string(Form("%.3f", leptonUnc_ttbar)) ); 
	
  	float leptonUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_LeptonUp, wjet_LeptonDown) : 1.00;
  	line.replace( line.find("WWWW") , 4 , string(Form("%.3f", leptonUnc_wjet)) ); 
	
  	float leptonUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_LeptonUp, zjet_LeptonDown) : 1.00;
  	line.replace( line.find("DDDD") , 4 , string(Form("%.3f", leptonUnc_zjet)) ); 
	
  	float leptonUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_LeptonUp, stop_LeptonDown) : 1.00; 
  	line.replace( line.find("SSSS") , 4 , string(Form("%.3f", leptonUnc_stop)) ); 

  	float leptonUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_LeptonUp, vv_LeptonDown) : 1.00;
  	line.replace( line.find("VVVV") , 4 , string(Form("%.3f", leptonUnc_vv)) ); 
	
        out << line << endl;	
	
      }  
      else if(line.find("CMS_prefire ")!=string::npos){

        float prefireUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_PrefireUp, wh_PrefireDown) : 1.00;
        line.replace( line.find("HHHH") , 4 , string(Form("%.3f", prefireUnc_wh)) );
        
        float prefireUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_PrefireUp, ttbar_PrefireDown) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", prefireUnc_ttbar)) ); 
        
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
	
        float pujetidUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_PUJetIDUp, wh_PUJetIDDown) : 1.00;
        line.replace( line.find("HHHH") , 4 , string(Form("%.3f", pujetidUnc_wh)) );
        
        float pujetidUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_PUJetIDUp, ttbar_PUJetIDDown) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", pujetidUnc_ttbar)) ); 
        
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
      else if(line.find("CMS_scale_j ")!=string::npos){
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
      else if(line.find("CMS_res_j ")!=string::npos){
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
      else if(line.find("CMS_norm_qcd ")!=string::npos){  
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
        float matchUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_matchingUp, ttbar_matchingDown) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", matchUnc_ttbar)) ); 
        out << line << endl;
	
      }
      else if(line.find("CMS_topMass_tt ")!=string::npos){
  	float mtopUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_mtop1735, ttbar_mtop1715) : 1.00; 
  	line.replace( line.find("TTTT") , 4 , string(Form("%.3f", mtopUnc_ttbar)) ); 
  	out << line << endl;
      }
      else if(line.find("CMS_CP5_tt ")!=string::npos){
  	float scaleUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_cp5Up, ttbar_cp5Down) : 1.00; 
  	line.replace( line.find("TTTT") , 4 , string(Form("%.3f", scaleUnc_ttbar)) ); 
  	out << line << endl;
	
      }
      else if(line.find("CMS_pdf ")!=string::npos){
        float pdfUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_pdfUp, wh_pdfDown) : 1.00;
        line.replace( line.find("HHHH") , 4 , string(Form("%.3f", pdfUnc_wh)) );
        
        float pdfUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_pdfUp, ttbar_pdfDown) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", pdfUnc_ttbar)) ); 
        
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
        float isrUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_isrUp, wh_isrDown) : 1.00;
        line.replace( line.find("HHHH") , 4 , string(Form("%.3f", isrUnc_wh)) );
        
        float isrUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_isrUp, ttbar_isrDown) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", isrUnc_ttbar)) ); 
        
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
        float fsrUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_fsrUp, wh_fsrDown) : 1.00;
        line.replace( line.find("HHHH") , 4 , string(Form("%.3f", fsrUnc_wh)) );
        
        float fsrUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_fsrUp, ttbar_fsrDown) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", fsrUnc_ttbar)) ); 
        
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
        float bcstatUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_bcstatUp, wh_bcstatDown) : 1.00;
        line.replace( line.find("HHHH") , 4 , string(Form("%.3f", bcstatUnc_wh)) );
        
        float bcstatUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_bcstatUp, ttbar_bcstatDown) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", bcstatUnc_ttbar)) ); 
        
        float bcstatUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_bcstatUp, wjet_bcstatDown) : 1.00;
        line.replace( line.find("WWWW") , 4 , string(Form("%.3f", bcstatUnc_wjet)) ); 
       
        float bcstatUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_bcstatUp, zjet_bcstatDown) : 1.00;
        line.replace( line.find("DDDD") , 4 , string(Form("%.3f", bcstatUnc_zjet)) ); 
        
        float bcstatUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_bcstatUp, stop_bcstatDown) : 1.00; 
        line.replace( line.find("SSSS") , 4 , string(Form("%.3f", bcstatUnc_stop)) ); 

        float bcstatUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_bcstatUp, vv_bcstatDown) : 1.00;
        line.replace( line.find("VVVV") , 4 , string(Form("%.3f", bcstatUnc_vv)) ); 
        out << line << endl;
      }
      else if(line.find("CMS_bclhemuf ")!=string::npos){
        float bclhemufUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_bclhemufUp, wh_bclhemufDown) : 1.00;
        line.replace( line.find("HHHH") , 4 , string(Form("%.3f", bclhemufUnc_wh)) );
        
        float bclhemufUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_bclhemufUp, ttbar_bclhemufDown) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", bclhemufUnc_ttbar)) ); 
        
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
        float bclhemurUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_bclhemurUp, wh_bclhemurDown) : 1.00;
        line.replace( line.find("HHHH") , 4 , string(Form("%.3f", bclhemurUnc_wh)) );
        
        float bclhemurUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_bclhemurUp, ttbar_bclhemurDown) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", bclhemurUnc_ttbar)) ); 
        
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
      // else if(line.find("CMS_bcbfrag ")!=string::npos){
      //   float bcbfragUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_bcbfragUp, wh_bcbfragDown) : 1.00;
      //   line.replace( line.find("HHHH") , 4 , string(Form("%.3f", bcbfragUnc_wh)) );
        
      //   float bcbfragUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_bcbfragUp, ttbar_bcbfragDown) : 1.00; 
      //   line.replace( line.find("TTTT") , 4 , string(Form("%.3f", bcbfragUnc_ttbar)) ); 
        
      //   float bcbfragUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_bcbfragUp, wjet_bcbfragDown) : 1.00;
      //   line.replace( line.find("WWWW") , 4 , string(Form("%.3f", bcbfragUnc_wjet)) ); 
       
      //   float bcbfragUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_bcbfragUp, zjet_bcbfragDown) : 1.00;
      //   line.replace( line.find("DDDD") , 4 , string(Form("%.3f", bcbfragUnc_zjet)) ); 
        
      //   float bcbfragUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_bcbfragUp, stop_bcbfragDown) : 1.00; 
      //   line.replace( line.find("SSSS") , 4 , string(Form("%.3f", bcbfragUnc_stop)) ); 

      //   float bcbfragUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_bcbfragUp, vv_bcbfragDown) : 1.00;
      //   line.replace( line.find("VVVV") , 4 , string(Form("%.3f", bcbfragUnc_vv)) ); 
      //   out << line << endl;
      // }      
      // else if(line.find("CMS_bcxdy ")!=string::npos){
      //   float bcxdyUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_bcxdyUp, wh_bcxdyDown) : 1.00;
      //   line.replace( line.find("HHHH") , 4 , string(Form("%.3f", bcxdyUnc_wh)) );
        
      //   float bcxdyUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_bcxdyUp, ttbar_bcxdyDown) : 1.00; 
      //   line.replace( line.find("TTTT") , 4 , string(Form("%.3f", bcxdyUnc_ttbar)) ); 
        
      //   float bcxdyUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_bcxdyUp, wjet_bcxdyDown) : 1.00;
      //   line.replace( line.find("WWWW") , 4 , string(Form("%.3f", bcxdyUnc_wjet)) ); 
       
      //   float bcxdyUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_bcxdyUp, zjet_bcxdyDown) : 1.00;
      //   line.replace( line.find("DDDD") , 4 , string(Form("%.3f", bcxdyUnc_zjet)) ); 
        
      //   float bcxdyUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_bcxdyUp, stop_bcxdyDown) : 1.00; 
      //   line.replace( line.find("SSSS") , 4 , string(Form("%.3f", bcxdyUnc_stop)) ); 

      //   float bcxdyUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_bcxdyUp, vv_bcxdyDown) : 1.00;
      //   line.replace( line.find("VVVV") , 4 , string(Form("%.3f", bcxdyUnc_vv)) ); 
      //   out << line << endl;
      // }
      // else if(line.find("CMS_bcxst ")!=string::npos){
      //   float bcxstUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_bcxstUp, wh_bcxstDown) : 1.00;
      //   line.replace( line.find("HHHH") , 4 , string(Form("%.3f", bcxstUnc_wh)) );
        
      //   float bcxstUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_bcxstUp, ttbar_bcxstDown) : 1.00; 
      //   line.replace( line.find("TTTT") , 4 , string(Form("%.3f", bcxstUnc_ttbar)) ); 
        
      //   float bcxstUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_bcxstUp, wjet_bcxstDown) : 1.00;
      //   line.replace( line.find("WWWW") , 4 , string(Form("%.3f", bcxstUnc_wjet)) ); 
       
      //   float bcxstUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_bcxstUp, zjet_bcxstDown) : 1.00;
      //   line.replace( line.find("DDDD") , 4 , string(Form("%.3f", bcxstUnc_zjet)) ); 
        
      //   float bcxstUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_bcxstUp, stop_bcxstDown) : 1.00; 
      //   line.replace( line.find("SSSS") , 4 , string(Form("%.3f", bcxstUnc_stop)) ); 

      //   float bcxstUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_bcxstUp, vv_bcxstDown) : 1.00;
      //   line.replace( line.find("VVVV") , 4 , string(Form("%.3f", bcxstUnc_vv)) ); 
      //   out << line << endl;
      // }
      // else if(line.find("CMS_bcxwj ")!=string::npos){
      //   float bcxwjUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_bcxwjUp, wh_bcxwjDown) : 1.00;
      //   line.replace( line.find("HHHH") , 4 , string(Form("%.3f", bcxwjUnc_wh)) );
        
      //   float bcxwjUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_bcxwjUp, ttbar_bcxwjDown) : 1.00; 
      //   line.replace( line.find("TTTT") , 4 , string(Form("%.3f", bcxwjUnc_ttbar)) ); 
        
      //   float bcxwjUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_bcxwjUp, wjet_bcxwjDown) : 1.00;
      //   line.replace( line.find("WWWW") , 4 , string(Form("%.3f", bcxwjUnc_wjet)) ); 
       
      //   float bcxwjUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_bcxwjUp, zjet_bcxwjDown) : 1.00;
      //   line.replace( line.find("DDDD") , 4 , string(Form("%.3f", bcxwjUnc_zjet)) ); 
        
      //   float bcxwjUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_bcxwjUp, stop_bcxwjDown) : 1.00; 
      //   line.replace( line.find("SSSS") , 4 , string(Form("%.3f", bcxwjUnc_stop)) ); 

      //   float bcxwjUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_bcxwjUp, vv_bcxwjDown) : 1.00;
      //   line.replace( line.find("VVVV") , 4 , string(Form("%.3f", bcxwjUnc_vv)) ); 
      //   out << line << endl;
      // }
      // else if(line.find("CMS_bcxtt ")!=string::npos){
      //   float bcxttUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_bcxttUp, wh_bcxttDown) : 1.00;
      //   line.replace( line.find("HHHH") , 4 , string(Form("%.3f", bcxttUnc_wh)) );
        
      //   float bcxttUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_bcxttUp, ttbar_bcxttDown) : 1.00; 
      //   line.replace( line.find("TTTT") , 4 , string(Form("%.3f", bcxttUnc_ttbar)) ); 
        
      //   float bcxttUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_bcxttUp, wjet_bcxttDown) : 1.00;
      //   line.replace( line.find("WWWW") , 4 , string(Form("%.3f", bcxttUnc_wjet)) ); 
       
      //   float bcxttUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_bcxttUp, zjet_bcxttDown) : 1.00;
      //   line.replace( line.find("DDDD") , 4 , string(Form("%.3f", bcxttUnc_zjet)) ); 
        
      //   float bcxttUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_bcxttUp, stop_bcxttDown) : 1.00; 
      //   line.replace( line.find("SSSS") , 4 , string(Form("%.3f", bcxttUnc_stop)) ); 

      //   float bcxttUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_bcxttUp, vv_bcxttDown) : 1.00;
      //   line.replace( line.find("VVVV") , 4 , string(Form("%.3f", bcxttUnc_vv)) ); 
      //   out << line << endl;
      // }
      else if(line.find("CMS_bcxdyb ")!=string::npos){
        float bcxdybUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_bcxdybUp, wh_bcxdybDown) : 1.00;
        line.replace( line.find("HHHH") , 4 , string(Form("%.3f", bcxdybUnc_wh)) );
        
        float bcxdybUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_bcxdybUp, ttbar_bcxdybDown) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", bcxdybUnc_ttbar)) ); 
        
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
        float bcxdycUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_bcxdycUp, wh_bcxdycDown) : 1.00;
        line.replace( line.find("HHHH") , 4 , string(Form("%.3f", bcxdycUnc_wh)) );
        
        float bcxdycUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_bcxdycUp, ttbar_bcxdycDown) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", bcxdycUnc_ttbar)) ); 
        
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
        float bcxwjcUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_bcxwjcUp, wh_bcxwjcDown) : 1.00;
        line.replace( line.find("HHHH") , 4 , string(Form("%.3f", bcxwjcUnc_wh)) );
        
        float bcxwjcUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_bcxwjcUp, ttbar_bcxwjcDown) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", bcxwjcUnc_ttbar)) ); 
        
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
        float bcintpUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_bcintpUp, wh_bcintpDown) : 1.00;
        line.replace( line.find("HHHH") , 4 , string(Form("%.3f", bcintpUnc_wh)) );
        
        float bcintpUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_bcintpUp, ttbar_bcintpDown) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", bcintpUnc_ttbar)) ); 
        
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
        float bcextpUnc_wh = (wh->Integral() > 0) ? DC.getBTagUnc(wh, wh_bcextpUp, wh_bcextpDown) : 1.00;
        line.replace( line.find("HHHH") , 4 , string(Form("%.3f", bcextpUnc_wh)) );
        
        float bcextpUnc_ttbar = (ttbar->Integral() > 0) ? DC.getBTagUnc(ttbar, ttbar_bcextpUp, ttbar_bcextpDown) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", bcextpUnc_ttbar)) ); 
        
        float bcextpUnc_wjet = (wjet->Integral() > 0) ? DC.getBTagUnc(wjet, wjet_bcextpUp, wjet_bcextpDown) : 1.00;
        line.replace( line.find("WWWW") , 4 , string(Form("%.3f", bcextpUnc_wjet)) ); 
       
        float bcextpUnc_zjet = (zjet->Integral() > 0) ? DC.getBTagUnc(zjet, zjet_bcextpUp, zjet_bcextpDown) : 1.00;
        line.replace( line.find("DDDD") , 4 , string(Form("%.3f", bcextpUnc_zjet)) ); 
        
        float bcextpUnc_stop = (stop->Integral() > 0) ? DC.getBTagUnc(stop, stop_bcextpUp, stop_bcextpDown) : 1.00; 
        line.replace( line.find("SSSS") , 4 , string(Form("%.3f", bcextpUnc_stop)) ); 

        float bcextpUnc_vv = (vv->Integral() > 0) ? DC.getBTagUnc(vv, vv_bcextpUp, vv_bcextpDown) : 1.00;
        line.replace( line.find("VVVV") , 4 , string(Form("%.3f", bcextpUnc_vv)) ); 
        out << line << endl;
      }
      else{ //default without changes
        out << line << endl;
  	//
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
  if(!isBinStat)
    out<<"* autoMCStats 0 1"<<endl;
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
