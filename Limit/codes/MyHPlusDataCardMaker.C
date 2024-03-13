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
  bool isSymError = true; //Symmetic error in data card
  
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
  //QCD data driven
  baseDir = "QCDdd";
  TH1F* qcd_dd_raw = DC.readWriteHisto(fQCD_dd, baseDir+"/base"+histSubDir, histName, sf_qcd, fout, fTT, "qcd_base", false);
  //TH1F* qcd_dd = DC.readWriteHisto(fQCD_dd, baseDir+"/base"+histSubDir, histName, sf_qcd, fout, fTT, "qcd", true, true, 0x0);
  TH1F* qcd_dd = DC.readWriteHisto(fQCD_dd, baseDir+"/base"+histSubDir, histName, sf_qcd, fout, fTT, "qcd", true);
  double QCD_DD_Integral = qcd_dd_raw->Integral();
  double stat_unc_qcd = DC.getStatUnc(qcd_dd, 0);
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

  void LineReplace(MyHPlusDataCardMaker& DC, string& line, bool isSymError, TH1F* wh, TH1F* ttbar, TH1F* ttg, TH1F* tth, TH1F* ttz, TH1F* ttw, TH1F* wjet, TH1F* zjet, TH1F* stop, TH1F* vv,
		   TH1F* wh_systUp, TH1F* ttbar_systUp, TH1F* ttg_systUp, TH1F* tth_systUp, TH1F* ttz_systUp, TH1F* ttw_systUp, TH1F* wjet_systUp, TH1F* zjet_systUp, TH1F* stop_systUp, TH1F* vv_systUp,
		   TH1F* wh_systDown, TH1F* ttbar_systDown, TH1F* ttg_systDown, TH1F* tth_systDown, TH1F* ttz_systDown, TH1F* ttw_systDown, TH1F* wjet_systDown, TH1F* zjet_systDown, TH1F* stop_systDown, TH1F* vv_systDown);

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
	
        if(isMuChannel) line.replace( line.find("lep") , 4 , string(Form("%s", "m")));   
        else line.replace( line.find("lep") , 4 , string(Form("%s", "e")));

	stringstream ss(line); string systname; ss >> systname;
	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+hist_extn);
	
	// LineReplace(DC, line, isSymError, wh, ttbar, ttg, tth, ttz, ttw, wjet, zjet, stop, vv,
	// 	    wh_LeptonUp, ttbar_LeptonUp, ttg_LeptonUp, tth_LeptonUp, ttz_LeptonUp, ttw_LeptonUp, wjet_LeptonUp, zjet_LeptonUp, stop_LeptonUp, vv_LeptonUp,
	// 	    wh_LeptonDown, ttbar_LeptonDown, ttg_LeptonDown, tth_LeptonDown, ttz_LeptonDown, ttw_LeptonDown, wjet_LeptonDown, zjet_LeptonDown, stop_LeptonDown, vv_LeptonDown);

        out << line << endl;	
      }  
      else if(line.find("CMS_prefire ")!=string::npos){
	
	LineReplace(DC, line, isSymError, wh, ttbar, ttg, tth, ttz, ttw, wjet, zjet, stop, vv,
		    wh_PrefireUp, ttbar_PrefireUp, ttg_PrefireUp, tth_PrefireUp, ttz_PrefireUp, ttw_PrefireUp, wjet_PrefireUp, zjet_PrefireUp, stop_PrefireUp, vv_PrefireUp,
		    wh_PrefireDown, ttbar_PrefireDown, ttg_PrefireDown, tth_PrefireDown, ttz_PrefireDown, ttw_PrefireDown, wjet_PrefireDown, zjet_PrefireDown, stop_PrefireDown, vv_PrefireDown);

        out << line << endl;
      }
      else if(line.find("CMS_pujetid ")!=string::npos){	
	
	stringstream ss(line); string systname; ss >> systname;
	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+hist_extn);
	
	LineReplace(DC, line, isSymError, wh, ttbar, ttg, tth, ttz, ttw, wjet, zjet, stop, vv,
		    wh_PUJetIDUp, ttbar_PUJetIDUp, ttg_PUJetIDUp, tth_PUJetIDUp, ttz_PUJetIDUp, ttw_PUJetIDUp, wjet_PUJetIDUp, zjet_PUJetIDUp, stop_PUJetIDUp, vv_PUJetIDUp,
		    wh_PUJetIDDown, ttbar_PUJetIDDown, ttg_PUJetIDDown, tth_PUJetIDDown, ttz_PUJetIDDown, ttw_PUJetIDDown, wjet_PUJetIDDown, zjet_PUJetIDDown, stop_PUJetIDDown, vv_PUJetIDDown);
	
        out << line << endl;
      }
      else if(line.find("CMS_pileup ")!=string::npos){

	stringstream ss(line); string systname; ss >> systname;
	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+hist_extn);

	LineReplace(DC, line, isSymError, wh, ttbar, ttg, tth, ttz, ttw, wjet, zjet, stop, vv,
		    wh_PileupUp, ttbar_PileupUp, ttg_PileupUp, tth_PileupUp, ttz_PileupUp, ttw_PileupUp, wjet_PileupUp, zjet_PileupUp, stop_PileupUp, vv_PileupUp,
		    wh_PileupDown, ttbar_PileupDown, ttg_PileupDown, tth_PileupDown, ttz_PileupDown, ttw_PileupDown, wjet_PileupDown, zjet_PileupDown, stop_PileupDown, vv_PileupDown);

        out << line << endl;	
      }
      else if(line.find("CMS_JER ")!=string::npos){

      	stringstream ss(line); string systname; ss >> systname;
      	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+uncorr_extn);

	LineReplace(DC, line, isSymError, wh, ttbar, ttg, tth, ttz, ttw, wjet, zjet, stop, vv,
		    wh_JERUp, ttbar_JERUp, ttg_JERUp, tth_JERUp, ttz_JERUp, ttw_JERUp, wjet_JERUp, zjet_JERUp, stop_JERUp, vv_JERUp,
		    wh_JERDown, ttbar_JERDown, ttg_JERDown, tth_JERDown, ttz_JERDown, ttw_JERDown, wjet_JERDown, zjet_JERDown, stop_JERDown, vv_JERDown);

        out << line << endl;
      }
      else if(line.find("CMS_norm_qcd ")!=string::npos){  

	stringstream ss(line); string systname; ss >> systname;
	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+hist_extn);

        line.replace( line.find("QQQQ") , 4 , string(Form("%.3f", qcd_unc)));   
        //if(isMuChannel) line.replace( line.find("QQQQ") , 4 , string(Form("%.4f", 1.10)));   
        //else line.replace(line.find("QQQQ") , 4 , string(Form("%.4f", 1.10)));   
        out << line << endl;	
      }
      else if(line.find("CMS_hDamp_tt ")!=string::npos){

	stringstream ss(line); string systname; ss >> systname;
	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+hist_extn);

        float matchUnc_ttbar = (ttbar->Integral() > 0) ? DC.getConservativeUnc(ttbar, ttbar_matchingUp, ttbar_matchingDown) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", matchUnc_ttbar)) ); 
        out << line << endl;	
      }
      else if(line.find("CMS_topMass_tt ")!=string::npos){

	stringstream ss(line); string systname; ss >> systname;
	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+hist_extn);

  	float mtopUnc_ttbar = (ttbar->Integral() > 0) ? DC.getConservativeUnc(ttbar, ttbar_mtop1735, ttbar_mtop1715) : 1.00; 
  	line.replace( line.find("TTTT") , 4 , string(Form("%.3f", mtopUnc_ttbar)) ); 
  	out << line << endl;
      }
      else if(line.find("CMS_CP5_tt ")!=string::npos){

	stringstream ss(line); string systname; ss >> systname;
	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+hist_extn);

  	float scaleUnc_ttbar = (ttbar->Integral() > 0) ? DC.getConservativeUnc(ttbar, ttbar_cp5Up, ttbar_cp5Down) : 1.00; 
  	line.replace( line.find("TTTT") , 4 , string(Form("%.3f", scaleUnc_ttbar)) ); 
  	out << line << endl;	
      }
      else if(line.find("CMS_pdf ")!=string::npos){

	stringstream ss(line); string systname; ss >> systname;
	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+hist_extn);

	LineReplace(DC, line, isSymError, wh, ttbar, ttg, tth, ttz, ttw, wjet, zjet, stop, vv,
		    wh_pdfUp, ttbar_pdfUp, ttg_pdfUp, tth_pdfUp, ttz_pdfUp, ttw_pdfUp, wjet_pdfUp, zjet_pdfUp, stop_pdfUp, vv_pdfUp,
		    wh_pdfDown, ttbar_pdfDown, ttg_pdfDown, tth_pdfDown, ttz_pdfDown, ttw_pdfDown, wjet_pdfDown, zjet_pdfDown, stop_pdfDown, vv_pdfDown);

        out << line << endl;
      }
      else if(line.find("CMS_isr ")!=string::npos){

	stringstream ss(line); string systname; ss >> systname;
	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+hist_extn);

	LineReplace(DC, line, isSymError, wh, ttbar, ttg, tth, ttz, ttw, wjet, zjet, stop, vv,
		    wh_isrUp, ttbar_isrUp, ttg_isrUp, tth_isrUp, ttz_isrUp, ttw_isrUp, wjet_isrUp, zjet_isrUp, stop_isrUp, vv_isrUp,
		    wh_isrDown, ttbar_isrDown, ttg_isrDown, tth_isrDown, ttz_isrDown, ttw_isrDown, wjet_isrDown, zjet_isrDown, stop_isrDown, vv_isrDown);

        out << line << endl;
      }
      else if(line.find("CMS_fsr ")!=string::npos){

	stringstream ss(line); string systname; ss >> systname;
	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+hist_extn);

	LineReplace(DC, line, isSymError, wh, ttbar, ttg, tth, ttz, ttw, wjet, zjet, stop, vv,
		    wh_fsrUp, ttbar_fsrUp, ttg_fsrUp, tth_fsrUp, ttz_fsrUp, ttw_fsrUp, wjet_fsrUp, zjet_fsrUp, stop_fsrUp, vv_fsrUp,
		    wh_fsrDown, ttbar_fsrDown, ttg_fsrDown, tth_fsrDown, ttz_fsrDown, ttw_fsrDown, wjet_fsrDown, zjet_fsrDown, stop_fsrDown, vv_fsrDown);

        out << line << endl;
      }
      else if(line.find("CMS_bcstat ")!=string::npos){
	//Default
	stringstream ss(line); string systname; ss >> systname;
	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+uncorr_extn);

	LineReplace(DC, line, isSymError, wh, ttbar, ttg, tth, ttz, ttw, wjet, zjet, stop, vv,
		    wh_bcstatUp, ttbar_bcstatUp, ttg_bcstatUp, tth_bcstatUp, ttz_bcstatUp, ttw_bcstatUp, wjet_bcstatUp, zjet_bcstatUp, stop_bcstatUp, vv_bcstatUp,
		    wh_bcstatDown, ttbar_bcstatDown, ttg_bcstatDown, tth_bcstatDown, ttz_bcstatDown, ttw_bcstatDown, wjet_bcstatDown, zjet_bcstatDown, stop_bcstatDown, vv_bcstatDown);

        out << line << endl;
      }
      else if(line.find("CMS_bclhemuf ")!=string::npos){

	stringstream ss(line); string systname; ss >> systname;
	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+hist_extn);

	LineReplace(DC, line, isSymError, wh, ttbar, ttg, tth, ttz, ttw, wjet, zjet, stop, vv,
		    wh_bclhemufUp, ttbar_bclhemufUp, ttg_bclhemufUp, tth_bclhemufUp, ttz_bclhemufUp, ttw_bclhemufUp, wjet_bclhemufUp, zjet_bclhemufUp, stop_bclhemufUp, vv_bclhemufUp,
		    wh_bclhemufDown, ttbar_bclhemufDown, ttg_bclhemufDown, tth_bclhemufDown, ttz_bclhemufDown, ttw_bclhemufDown, wjet_bclhemufDown, zjet_bclhemufDown, stop_bclhemufDown, vv_bclhemufDown);

        out << line << endl;
      }
      else if(line.find("CMS_bclhemur ")!=string::npos){

	stringstream ss(line); string systname; ss >> systname;
	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+hist_extn);

	LineReplace(DC, line, isSymError, wh, ttbar, ttg, tth, ttz, ttw, wjet, zjet, stop, vv,
		    wh_bclhemurUp, ttbar_bclhemurUp, ttg_bclhemurUp, tth_bclhemurUp, ttz_bclhemurUp, ttw_bclhemurUp, wjet_bclhemurUp, zjet_bclhemurUp, stop_bclhemurUp, vv_bclhemurUp,
		    wh_bclhemurDown, ttbar_bclhemurDown, ttg_bclhemurDown, tth_bclhemurDown, ttz_bclhemurDown, ttw_bclhemurDown, wjet_bclhemurDown, zjet_bclhemurDown, stop_bclhemurDown, vv_bclhemurDown);

        out << line << endl;
      }
      else if(line.find("CMS_bcxdyb ")!=string::npos){

	stringstream ss(line); string systname; ss >> systname;
	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+hist_extn);

	LineReplace(DC, line, isSymError, wh, ttbar, ttg, tth, ttz, ttw, wjet, zjet, stop, vv,
		    wh_bcxdybUp, ttbar_bcxdybUp, ttg_bcxdybUp, tth_bcxdybUp, ttz_bcxdybUp, ttw_bcxdybUp, wjet_bcxdybUp, zjet_bcxdybUp, stop_bcxdybUp, vv_bcxdybUp,
		    wh_bcxdybDown, ttbar_bcxdybDown, ttg_bcxdybDown, tth_bcxdybDown, ttz_bcxdybDown, ttw_bcxdybDown, wjet_bcxdybDown, zjet_bcxdybDown, stop_bcxdybDown, vv_bcxdybDown);

        out << line << endl;
      }
      else if(line.find("CMS_bcxdyc ")!=string::npos){

	stringstream ss(line); string systname; ss >> systname;
	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+hist_extn);

	LineReplace(DC, line, isSymError, wh, ttbar, ttg, tth, ttz, ttw, wjet, zjet, stop, vv,
		    wh_bcxdycUp, ttbar_bcxdycUp, ttg_bcxdycUp, tth_bcxdycUp, ttz_bcxdycUp, ttw_bcxdycUp, wjet_bcxdycUp, zjet_bcxdycUp, stop_bcxdycUp, vv_bcxdycUp,
		    wh_bcxdycDown, ttbar_bcxdycDown, ttg_bcxdycDown, tth_bcxdycDown, ttz_bcxdycDown, ttw_bcxdycDown, wjet_bcxdycDown, zjet_bcxdycDown, stop_bcxdycDown, vv_bcxdycDown);

        out << line << endl;
      }
      else if(line.find("CMS_bcxwjc ")!=string::npos){

	stringstream ss(line); string systname; ss >> systname;
	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+hist_extn);
	
	LineReplace(DC, line, isSymError, wh, ttbar, ttg, tth, ttz, ttw, wjet, zjet, stop, vv,
		    wh_bcxwjcUp, ttbar_bcxwjcUp, ttg_bcxwjcUp, tth_bcxwjcUp, ttz_bcxwjcUp, ttw_bcxwjcUp, wjet_bcxwjcUp, zjet_bcxwjcUp, stop_bcxwjcUp, vv_bcxwjcUp,
		    wh_bcxwjcDown, ttbar_bcxwjcDown, ttg_bcxwjcDown, tth_bcxwjcDown, ttz_bcxwjcDown, ttw_bcxwjcDown, wjet_bcxwjcDown, zjet_bcxwjcDown, stop_bcxwjcDown, vv_bcxwjcDown);

        out << line << endl;
      }
      else if(line.find("CMS_bcintp ")!=string::npos){

	stringstream ss(line); string systname; ss >> systname;
	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+uncorr_extn);
	
	LineReplace(DC, line, isSymError, wh, ttbar, ttg, tth, ttz, ttw, wjet, zjet, stop, vv,
		    wh_bcintpUp, ttbar_bcintpUp, ttg_bcintpUp, tth_bcintpUp, ttz_bcintpUp, ttw_bcintpUp, wjet_bcintpUp, zjet_bcintpUp, stop_bcintpUp, vv_bcintpUp,
		    wh_bcintpDown, ttbar_bcintpDown, ttg_bcintpDown, tth_bcintpDown, ttz_bcintpDown, ttw_bcintpDown, wjet_bcintpDown, zjet_bcintpDown, stop_bcintpDown, vv_bcintpDown);
	
        out << line << endl;
      }
      else if(line.find("CMS_bcextp ")!=string::npos){

	float sf_bcextp = 1.0 ;

	stringstream ss(line); string systname; ss >> systname;
	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+uncorr_extn);

	LineReplace(DC, line, isSymError, wh, ttbar, ttg, tth, ttz, ttw, wjet, zjet, stop, vv,
		    wh_bcextpUp, ttbar_bcextpUp, ttg_bcextpUp, tth_bcextpUp, ttz_bcextpUp, ttw_bcextpUp, wjet_bcextpUp, zjet_bcextpUp, stop_bcextpUp, vv_bcextpUp,
		    wh_bcextpDown, ttbar_bcextpDown, ttg_bcextpDown, tth_bcextpDown, ttz_bcextpDown, ttw_bcextpDown, wjet_bcextpDown, zjet_bcextpDown, stop_bcextpDown, vv_bcextpDown);

        out << line << endl;
      }
      else if(line.find("CMS_topPt ")!=string::npos){

	stringstream ss(line); string systname; ss >> systname;
	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+hist_extn);

        float topPtUnc_wh = (wh->Integral() > 0) ? DC.getConservativeUnc(wh, wh_topPtUp, wh_topPtDown) : 1.00;
        line.replace( line.find("HHHH") , 4 , string(Form("%.3f", topPtUnc_wh)) );
        
        float topPtUnc_ttbar = (ttbar->Integral() > 0) ? DC.getConservativeUnc(ttbar, ttbar_topPtUp, ttbar_topPtDown) : 1.00; 
        line.replace( line.find("TTTT") , 4 , string(Form("%.3f", topPtUnc_ttbar)) ); 
        out << line << endl;
	
      }
      else if(line.find("CMS_flavorqcd ")!=string::npos){

	stringstream ss(line); string systname; ss >> systname;
	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+hist_extn);

	LineReplace(DC, line, isSymError, wh, ttbar, ttg, tth, ttz, ttw, wjet, zjet, stop, vv,
		    wh_flavorqcdUp, ttbar_flavorqcdUp, ttg_flavorqcdUp, tth_flavorqcdUp, ttz_flavorqcdUp, ttw_flavorqcdUp, wjet_flavorqcdUp, zjet_flavorqcdUp, stop_flavorqcdUp, vv_flavorqcdUp,
		    wh_flavorqcdDown, ttbar_flavorqcdDown, ttg_flavorqcdDown, tth_flavorqcdDown, ttz_flavorqcdDown, ttw_flavorqcdDown, wjet_flavorqcdDown, zjet_flavorqcdDown, stop_flavorqcdDown, vv_flavorqcdDown);
	
        out << line << endl;
      }
      else if(line.find("CMS_absmpfb ")!=string::npos){

      	stringstream ss(line); string systname; ss >> systname;
      	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+hist_extn);
	
	LineReplace(DC, line, isSymError, wh, ttbar, ttg, tth, ttz, ttw, wjet, zjet, stop, vv,
		    wh_absmpfbUp, ttbar_absmpfbUp, ttg_absmpfbUp, tth_absmpfbUp, ttz_absmpfbUp, ttw_absmpfbUp, wjet_absmpfbUp, zjet_absmpfbUp, stop_absmpfbUp, vv_absmpfbUp,
		    wh_absmpfbDown, ttbar_absmpfbDown, ttg_absmpfbDown, tth_absmpfbDown, ttz_absmpfbDown, ttw_absmpfbDown, wjet_absmpfbDown, zjet_absmpfbDown, stop_absmpfbDown, vv_absmpfbDown);
	
        out << line << endl;
      }
      else if(line.find("CMS_absscl ")!=string::npos){
	
      	stringstream ss(line); string systname; ss >> systname;
      	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+hist_extn);
	
	LineReplace(DC, line, isSymError, wh, ttbar, ttg, tth, ttz, ttw, wjet, zjet, stop, vv,
		    wh_abssclUp, ttbar_abssclUp, ttg_abssclUp, tth_abssclUp, ttz_abssclUp, ttw_abssclUp, wjet_abssclUp, zjet_abssclUp, stop_abssclUp, vv_abssclUp,
		    wh_abssclDown, ttbar_abssclDown, ttg_abssclDown, tth_abssclDown, ttz_abssclDown, ttw_abssclDown, wjet_abssclDown, zjet_abssclDown, stop_abssclDown, vv_abssclDown);
	
        out << line << endl;
      }
      else if(line.find("CMS_absstat ")!=string::npos){

      	stringstream ss(line); string systname; ss >> systname;
      	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+uncorr_extn);
	
	LineReplace(DC, line, isSymError, wh, ttbar, ttg, tth, ttz, ttw, wjet, zjet, stop, vv,
		    wh_absstatUp, ttbar_absstatUp, ttg_absstatUp, tth_absstatUp, ttz_absstatUp, ttw_absstatUp, wjet_absstatUp, zjet_absstatUp, stop_absstatUp, vv_absstatUp,
		    wh_absstatDown, ttbar_absstatDown, ttg_absstatDown, tth_absstatDown, ttz_absstatDown, ttw_absstatDown, wjet_absstatDown, zjet_absstatDown, stop_absstatDown, vv_absstatDown);
	
        out << line << endl;
      }
      else if(line.find("CMS_frag ")!=string::npos){

      	stringstream ss(line); string systname; ss >> systname;
      	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+hist_extn);
	
	LineReplace(DC, line, isSymError, wh, ttbar, ttg, tth, ttz, ttw, wjet, zjet, stop, vv,
		    wh_fragUp, ttbar_fragUp, ttg_fragUp, tth_fragUp, ttz_fragUp, ttw_fragUp, wjet_fragUp, zjet_fragUp, stop_fragUp, vv_fragUp,
		    wh_fragDown, ttbar_fragDown, ttg_fragDown, tth_fragDown, ttz_fragDown, ttw_fragDown, wjet_fragDown, zjet_fragDown, stop_fragDown, vv_fragDown);

        out << line << endl;
      }
      else if(line.find("CMS_pudatamc ")!=string::npos){

      	stringstream ss(line); string systname; ss >> systname;
      	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+hist_extn);
	
	LineReplace(DC, line, isSymError, wh, ttbar, ttg, tth, ttz, ttw, wjet, zjet, stop, vv,
		    wh_pudatamcUp, ttbar_pudatamcUp, ttg_pudatamcUp, tth_pudatamcUp, ttz_pudatamcUp, ttw_pudatamcUp, wjet_pudatamcUp, zjet_pudatamcUp, stop_pudatamcUp, vv_pudatamcUp,
		    wh_pudatamcDown, ttbar_pudatamcDown, ttg_pudatamcDown, tth_pudatamcDown, ttz_pudatamcDown, ttw_pudatamcDown, wjet_pudatamcDown, zjet_pudatamcDown, stop_pudatamcDown, vv_pudatamcDown);
	
        out << line << endl;
      }
      else if(line.find("CMS_puptbb ")!=string::npos){

      	stringstream ss(line); string systname; ss >> systname;
      	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+hist_extn);
	
	LineReplace(DC, line, isSymError, wh, ttbar, ttg, tth, ttz, ttw, wjet, zjet, stop, vv,
		    wh_puptbbUp, ttbar_puptbbUp, ttg_puptbbUp, tth_puptbbUp, ttz_puptbbUp, ttw_puptbbUp, wjet_puptbbUp, zjet_puptbbUp, stop_puptbbUp, vv_puptbbUp,
		    wh_puptbbDown, ttbar_puptbbDown, ttg_puptbbDown, tth_puptbbDown, ttz_puptbbDown, ttw_puptbbDown, wjet_puptbbDown, zjet_puptbbDown, stop_puptbbDown, vv_puptbbDown);
	
        out << line << endl;
      }
      else if(line.find("CMS_puptec1 ")!=string::npos){

      	stringstream ss(line); string systname; ss >> systname;
      	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+hist_extn);
	
	LineReplace(DC, line, isSymError, wh, ttbar, ttg, tth, ttz, ttw, wjet, zjet, stop, vv,
		    wh_puptec1Up, ttbar_puptec1Up, ttg_puptec1Up, tth_puptec1Up, ttz_puptec1Up, ttw_puptec1Up, wjet_puptec1Up, zjet_puptec1Up, stop_puptec1Up, vv_puptec1Up,
		    wh_puptec1Down, ttbar_puptec1Down, ttg_puptec1Down, tth_puptec1Down, ttz_puptec1Down, ttw_puptec1Down, wjet_puptec1Down, zjet_puptec1Down, stop_puptec1Down, vv_puptec1Down);

        out << line << endl;
      }
      else if(line.find("CMS_puptec2 ")!=string::npos){

      	stringstream ss(line); string systname; ss >> systname;
      	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+hist_extn);
	
	LineReplace(DC, line, isSymError, wh, ttbar, ttg, tth, ttz, ttw, wjet, zjet, stop, vv,
		    wh_puptec2Up, ttbar_puptec2Up, ttg_puptec2Up, tth_puptec2Up, ttz_puptec2Up, ttw_puptec2Up, wjet_puptec2Up, zjet_puptec2Up, stop_puptec2Up, vv_puptec2Up,
		    wh_puptec2Down, ttbar_puptec2Down, ttg_puptec2Down, tth_puptec2Down, ttz_puptec2Down, ttw_puptec2Down, wjet_puptec2Down, zjet_puptec2Down, stop_puptec2Down, vv_puptec2Down);

        out << line << endl;
      }
      else if(line.find("CMS_pupthf ")!=string::npos){

      	stringstream ss(line); string systname; ss >> systname;
      	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+hist_extn);
	
	LineReplace(DC, line, isSymError, wh, ttbar, ttg, tth, ttz, ttw, wjet, zjet, stop, vv,
		    wh_pupthfUp, ttbar_pupthfUp, ttg_pupthfUp, tth_pupthfUp, ttz_pupthfUp, ttw_pupthfUp, wjet_pupthfUp, zjet_pupthfUp, stop_pupthfUp, vv_pupthfUp,
		    wh_pupthfDown, ttbar_pupthfDown, ttg_pupthfDown, tth_pupthfDown, ttz_pupthfDown, ttw_pupthfDown, wjet_pupthfDown, zjet_pupthfDown, stop_pupthfDown, vv_pupthfDown);

        out << line << endl;
      }
      else if(line.find("CMS_puptref ")!=string::npos){

      	stringstream ss(line); string systname; ss >> systname;
      	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+hist_extn);
	
	LineReplace(DC, line, isSymError, wh, ttbar, ttg, tth, ttz, ttw, wjet, zjet, stop, vv,
		    wh_puptrefUp, ttbar_puptrefUp, ttg_puptrefUp, tth_puptrefUp, ttz_puptrefUp, ttw_puptrefUp, wjet_puptrefUp, zjet_puptrefUp, stop_puptrefUp, vv_puptrefUp,
		    wh_puptrefDown, ttbar_puptrefDown, ttg_puptrefDown, tth_puptrefDown, ttz_puptrefDown, ttw_puptrefDown, wjet_puptrefDown, zjet_puptrefDown, stop_puptrefDown, vv_puptrefDown);

        out << line << endl;
      }
      else if(line.find("CMS_relfsr ")!=string::npos){

      	stringstream ss(line); string systname; ss >> systname;
      	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+hist_extn);
	
	LineReplace(DC, line, isSymError, wh, ttbar, ttg, tth, ttz, ttw, wjet, zjet, stop, vv,
		    wh_relfsrUp, ttbar_relfsrUp, ttg_relfsrUp, tth_relfsrUp, ttz_relfsrUp, ttw_relfsrUp, wjet_relfsrUp, zjet_relfsrUp, stop_relfsrUp, vv_relfsrUp,
		    wh_relfsrDown, ttbar_relfsrDown, ttg_relfsrDown, tth_relfsrDown, ttz_relfsrDown, ttw_relfsrDown, wjet_relfsrDown, zjet_relfsrDown, stop_relfsrDown, vv_relfsrDown);

        out << line << endl;
      }
      else if(line.find("CMS_relbal ")!=string::npos){

      	stringstream ss(line); string systname; ss >> systname;
      	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+hist_extn);
	
	LineReplace(DC, line, isSymError, wh, ttbar, ttg, tth, ttz, ttw, wjet, zjet, stop, vv,
		    wh_relbalUp, ttbar_relbalUp, ttg_relbalUp, tth_relbalUp, ttz_relbalUp, ttw_relbalUp, wjet_relbalUp, zjet_relbalUp, stop_relbalUp, vv_relbalUp,
		    wh_relbalDown, ttbar_relbalDown, ttg_relbalDown, tth_relbalDown, ttz_relbalDown, ttw_relbalDown, wjet_relbalDown, zjet_relbalDown, stop_relbalDown, vv_relbalDown);

        out << line << endl;
      }
      else if(line.find("CMS_relsample ")!=string::npos){

      	stringstream ss(line); string systname; ss >> systname;
      	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+uncorr_extn);
	
	LineReplace(DC, line, isSymError, wh, ttbar, ttg, tth, ttz, ttw, wjet, zjet, stop, vv,
		    wh_relsampleUp, ttbar_relsampleUp, ttg_relsampleUp, tth_relsampleUp, ttz_relsampleUp, ttw_relsampleUp, wjet_relsampleUp, zjet_relsampleUp, stop_relsampleUp, vv_relsampleUp,
		    wh_relsampleDown, ttbar_relsampleDown, ttg_relsampleDown, tth_relsampleDown, ttz_relsampleDown, ttw_relsampleDown, wjet_relsampleDown, zjet_relsampleDown, stop_relsampleDown, vv_relsampleDown);

        out << line << endl;
      }
      else if(line.find("CMS_reljerec1 ")!=string::npos){

      	stringstream ss(line); string systname; ss >> systname;
      	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+uncorr_extn);
	
	LineReplace(DC, line, isSymError, wh, ttbar, ttg, tth, ttz, ttw, wjet, zjet, stop, vv,
		    wh_reljerec1Up, ttbar_reljerec1Up, ttg_reljerec1Up, tth_reljerec1Up, ttz_reljerec1Up, ttw_reljerec1Up, wjet_reljerec1Up, zjet_reljerec1Up, stop_reljerec1Up, vv_reljerec1Up,
		    wh_reljerec1Down, ttbar_reljerec1Down, ttg_reljerec1Down, tth_reljerec1Down, ttz_reljerec1Down, ttw_reljerec1Down, wjet_reljerec1Down, zjet_reljerec1Down, stop_reljerec1Down, vv_reljerec1Down);

        out << line << endl;
      }
      else if(line.find("CMS_reljerec2 ")!=string::npos){

      	stringstream ss(line); string systname; ss >> systname;
      	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+uncorr_extn);
	
	LineReplace(DC, line, isSymError, wh, ttbar, ttg, tth, ttz, ttw, wjet, zjet, stop, vv,
		    wh_reljerec2Up, ttbar_reljerec2Up, ttg_reljerec2Up, tth_reljerec2Up, ttz_reljerec2Up, ttw_reljerec2Up, wjet_reljerec2Up, zjet_reljerec2Up, stop_reljerec2Up, vv_reljerec2Up,
		    wh_reljerec2Down, ttbar_reljerec2Down, ttg_reljerec2Down, tth_reljerec2Down, ttz_reljerec2Down, ttw_reljerec2Down, wjet_reljerec2Down, zjet_reljerec2Down, stop_reljerec2Down, vv_reljerec2Down);
	
        out << line << endl;
      }
      else if(line.find("CMS_reljerhf ")!=string::npos){

      	stringstream ss(line); string systname; ss >> systname;
      	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+hist_extn);
	
	LineReplace(DC, line, isSymError, wh, ttbar, ttg, tth, ttz, ttw, wjet, zjet, stop, vv,
		    wh_reljerhfUp, ttbar_reljerhfUp, ttg_reljerhfUp, tth_reljerhfUp, ttz_reljerhfUp, ttw_reljerhfUp, wjet_reljerhfUp, zjet_reljerhfUp, stop_reljerhfUp, vv_reljerhfUp,
		    wh_reljerhfDown, ttbar_reljerhfDown, ttg_reljerhfDown, tth_reljerhfDown, ttz_reljerhfDown, ttw_reljerhfDown, wjet_reljerhfDown, zjet_reljerhfDown, stop_reljerhfDown, vv_reljerhfDown);

        out << line << endl;
      }
      else if(line.find("CMS_relptbb ")!=string::npos){

      	stringstream ss(line); string systname; ss >> systname;
      	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+hist_extn);
	
	LineReplace(DC, line, isSymError, wh, ttbar, ttg, tth, ttz, ttw, wjet, zjet, stop, vv,
		    wh_relptbbUp, ttbar_relptbbUp, ttg_relptbbUp, tth_relptbbUp, ttz_relptbbUp, ttw_relptbbUp, wjet_relptbbUp, zjet_relptbbUp, stop_relptbbUp, vv_relptbbUp,
		    wh_relptbbDown, ttbar_relptbbDown, ttg_relptbbDown, tth_relptbbDown, ttz_relptbbDown, ttw_relptbbDown, wjet_relptbbDown, zjet_relptbbDown, stop_relptbbDown, vv_relptbbDown);

        out << line << endl;
      }
      else if(line.find("CMS_relptec1 ")!=string::npos){

      	stringstream ss(line); string systname; ss >> systname;
      	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+uncorr_extn);
	
	LineReplace(DC, line, isSymError, wh, ttbar, ttg, tth, ttz, ttw, wjet, zjet, stop, vv,
		    wh_relptec1Up, ttbar_relptec1Up, ttg_relptec1Up, tth_relptec1Up, ttz_relptec1Up, ttw_relptec1Up, wjet_relptec1Up, zjet_relptec1Up, stop_relptec1Up, vv_relptec1Up,
		    wh_relptec1Down, ttbar_relptec1Down, ttg_relptec1Down, tth_relptec1Down, ttz_relptec1Down, ttw_relptec1Down, wjet_relptec1Down, zjet_relptec1Down, stop_relptec1Down, vv_relptec1Down);

        out << line << endl;
      }
      else if(line.find("CMS_relptec2 ")!=string::npos){

      	stringstream ss(line); string systname; ss >> systname;
      	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+uncorr_extn);
	
	LineReplace(DC, line, isSymError, wh, ttbar, ttg, tth, ttz, ttw, wjet, zjet, stop, vv,
		    wh_relptec2Up, ttbar_relptec2Up, ttg_relptec2Up, tth_relptec2Up, ttz_relptec2Up, ttw_relptec2Up, wjet_relptec2Up, zjet_relptec2Up, stop_relptec2Up, vv_relptec2Up,
		    wh_relptec2Down, ttbar_relptec2Down, ttg_relptec2Down, tth_relptec2Down, ttz_relptec2Down, ttw_relptec2Down, wjet_relptec2Down, zjet_relptec2Down, stop_relptec2Down, vv_relptec2Down);

        out << line << endl;
      }
      else if(line.find("CMS_relpthf ")!=string::npos){

      	stringstream ss(line); string systname; ss >> systname;
      	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+hist_extn);
	
	LineReplace(DC, line, isSymError, wh, ttbar, ttg, tth, ttz, ttw, wjet, zjet, stop, vv,
		    wh_relpthfUp, ttbar_relpthfUp, ttg_relpthfUp, tth_relpthfUp, ttz_relpthfUp, ttw_relpthfUp, wjet_relpthfUp, zjet_relpthfUp, stop_relpthfUp, vv_relpthfUp,
		    wh_relpthfDown, ttbar_relpthfDown, ttg_relpthfDown, tth_relpthfDown, ttz_relpthfDown, ttw_relpthfDown, wjet_relpthfDown, zjet_relpthfDown, stop_relpthfDown, vv_relpthfDown);
	
        out << line << endl;
      }
      else if(line.find("CMS_relstatec  ")!=string::npos){

      	stringstream ss(line); string systname; ss >> systname;
      	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+uncorr_extn);
	
	LineReplace(DC, line, isSymError, wh, ttbar, ttg, tth, ttz, ttw, wjet, zjet, stop, vv,
		    wh_relstatecUp, ttbar_relstatecUp, ttg_relstatecUp, tth_relstatecUp, ttz_relstatecUp, ttw_relstatecUp, wjet_relstatecUp, zjet_relstatecUp, stop_relstatecUp, vv_relstatecUp,
		    wh_relstatecDown, ttbar_relstatecDown, ttg_relstatecDown, tth_relstatecDown, ttz_relstatecDown, ttw_relstatecDown, wjet_relstatecDown, zjet_relstatecDown, stop_relstatecDown, vv_relstatecDown);

        out << line << endl;
      }
      else if(line.find("CMS_relstatfsr ")!=string::npos){

      	stringstream ss(line); string systname; ss >> systname;
      	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+uncorr_extn);
	
	LineReplace(DC, line, isSymError, wh, ttbar, ttg, tth, ttz, ttw, wjet, zjet, stop, vv,
		    wh_relstatfsrUp, ttbar_relstatfsrUp, ttg_relstatfsrUp, tth_relstatfsrUp, ttz_relstatfsrUp, ttw_relstatfsrUp, wjet_relstatfsrUp, zjet_relstatfsrUp, stop_relstatfsrUp, vv_relstatfsrUp,
		    wh_relstatfsrDown, ttbar_relstatfsrDown, ttg_relstatfsrDown, tth_relstatfsrDown, ttz_relstatfsrDown, ttw_relstatfsrDown, wjet_relstatfsrDown, zjet_relstatfsrDown, stop_relstatfsrDown, vv_relstatfsrDown);
	
        out << line << endl;
      }
      else if(line.find("CMS_relstathf ")!=string::npos){

      	stringstream ss(line); string systname; ss >> systname;
      	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+uncorr_extn);
	
	LineReplace(DC, line, isSymError, wh, ttbar, ttg, tth, ttz, ttw, wjet, zjet, stop, vv,
		    wh_relstathfUp, ttbar_relstathfUp, ttg_relstathfUp, tth_relstathfUp, ttz_relstathfUp, ttw_relstathfUp, wjet_relstathfUp, zjet_relstathfUp, stop_relstathfUp, vv_relstathfUp,
		    wh_relstathfDown, ttbar_relstathfDown, ttg_relstathfDown, tth_relstathfDown, ttz_relstathfDown, ttw_relstathfDown, wjet_relstathfDown, zjet_relstathfDown, stop_relstathfDown, vv_relstathfDown);

        out << line << endl;
      }
      else if(line.find("CMS_singpiecal ")!=string::npos){

      	stringstream ss(line); string systname; ss >> systname;
      	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+hist_extn);
	
	LineReplace(DC, line, isSymError, wh, ttbar, ttg, tth, ttz, ttw, wjet, zjet, stop, vv,
		    wh_singpiecalUp, ttbar_singpiecalUp, ttg_singpiecalUp, tth_singpiecalUp, ttz_singpiecalUp, ttw_singpiecalUp, wjet_singpiecalUp, zjet_singpiecalUp, stop_singpiecalUp, vv_singpiecalUp,
		    wh_singpiecalDown, ttbar_singpiecalDown, ttg_singpiecalDown, tth_singpiecalDown, ttz_singpiecalDown, ttw_singpiecalDown, wjet_singpiecalDown, zjet_singpiecalDown, stop_singpiecalDown, vv_singpiecalDown);

        out << line << endl;
      }
      else if(line.find("CMS_singpihcal ")!=string::npos){

      	stringstream ss(line); string systname; ss >> systname;
      	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+hist_extn);
	
	LineReplace(DC, line, isSymError, wh, ttbar, ttg, tth, ttz, ttw, wjet, zjet, stop, vv,
		    wh_singpihcalUp, ttbar_singpihcalUp, ttg_singpihcalUp, tth_singpihcalUp, ttz_singpihcalUp, ttw_singpihcalUp, wjet_singpihcalUp, zjet_singpihcalUp, stop_singpihcalUp, vv_singpihcalUp,
		    wh_singpihcalDown, ttbar_singpihcalDown, ttg_singpihcalDown, tth_singpihcalDown, ttz_singpihcalDown, ttw_singpihcalDown, wjet_singpihcalDown, zjet_singpihcalDown, stop_singpihcalDown, vv_singpihcalDown);

        out << line << endl;
      }
      else if(line.find("CMS_timepteta ")!=string::npos){

	stringstream ss(line); string systname; ss >> systname;
	if(isUncorrYearLn)  line.replace( line.find(systname) , systname.size() , systname+"_"+uncorr_extn);
	
	LineReplace(DC, line, isSymError, wh, ttbar, ttg, tth, ttz, ttw, wjet, zjet, stop, vv,
		    wh_timeptetaUp, ttbar_timeptetaUp, ttg_timeptetaUp, tth_timeptetaUp, ttz_timeptetaUp, ttw_timeptetaUp, wjet_timeptetaUp, zjet_timeptetaUp, stop_timeptetaUp, vv_timeptetaUp,
		    wh_timeptetaDown, ttbar_timeptetaDown, ttg_timeptetaDown, tth_timeptetaDown, ttz_timeptetaDown, ttw_timeptetaDown, wjet_timeptetaDown, zjet_timeptetaDown, stop_timeptetaDown, vv_timeptetaDown);
	
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

void LineReplace(MyHPlusDataCardMaker& DC, string& line, bool isSymError, TH1F* wh, TH1F* ttbar, TH1F* ttg, TH1F* tth, TH1F* ttz, TH1F* ttw, TH1F* wjet, TH1F* zjet, TH1F* stop, TH1F* vv,
		 TH1F* wh_systUp, TH1F* ttbar_systUp, TH1F* ttg_systUp, TH1F* tth_systUp, TH1F* ttz_systUp, TH1F* ttw_systUp, TH1F* wjet_systUp, TH1F* zjet_systUp, TH1F* stop_systUp, TH1F* vv_systUp,
		 TH1F* wh_systDown, TH1F* ttbar_systDown, TH1F* ttg_systDown, TH1F* tth_systDown, TH1F* ttz_systDown, TH1F* ttw_systDown, TH1F* wjet_systDown, TH1F* zjet_systDown, TH1F* stop_systDown, TH1F* vv_systDown)
{

  if(isSymError){
    
    float systUnc_wh = (wh->Integral() > 0) ? DC.getConservativeUnc(wh, wh_systUp, wh_systDown) : 1.00;
    line.replace( line.find("HHHH") , 4 , string(Form("%.3f", systUnc_wh)) );
  
    float systUnc_ttbar = (ttbar->Integral() > 0) ? DC.getConservativeUnc(ttbar, ttbar_systUp, ttbar_systDown) : 1.00; 
    line.replace( line.find("TTTT") , 4 , string(Form("%.3f", systUnc_ttbar)) ); 
  
    float systUnc_ttg = (ttg->Integral() > 0) ? DC.getConservativeUnc(ttg, ttg_systUp, ttg_systDown) : 1.00; 
    line.replace( line.find("TTGT") , 4 , string(Form("%.3f", systUnc_ttg)) ); 
  
    float systUnc_tth = (tth->Integral() > 0) ? DC.getConservativeUnc(tth, tth_systUp, tth_systDown) : 1.00; 
    line.replace( line.find("TTHT") , 4 , string(Form("%.3f", systUnc_tth)) ); 
  
    float systUnc_ttz = (ttz->Integral() > 0) ? DC.getConservativeUnc(ttz, ttz_systUp, ttz_systDown) : 1.00; 
    line.replace( line.find("TTZT") , 4 , string(Form("%.3f", systUnc_ttz)) ); 
  
    float systUnc_ttw = (ttw->Integral() > 0) ? DC.getConservativeUnc(ttw, ttw_systUp, ttw_systDown) : 1.00; 
    line.replace( line.find("TTWT") , 4 , string(Form("%.3f", systUnc_ttw)) ); 
  
    float systUnc_wjet = (wjet->Integral() > 0) ? DC.getConservativeUnc(wjet, wjet_systUp, wjet_systDown) : 1.00;
    line.replace( line.find("WWWW") , 4 , string(Form("%.3f", systUnc_wjet)) ); 
  
    float systUnc_zjet = (zjet->Integral() > 0) ? DC.getConservativeUnc(zjet, zjet_systUp, zjet_systDown) : 1.00;
    line.replace( line.find("DDDD") , 4 , string(Form("%.3f", systUnc_zjet)) ); 
  
    float systUnc_stop = (stop->Integral() > 0) ? DC.getConservativeUnc(stop, stop_systUp, stop_systDown) : 1.00; 
    line.replace( line.find("SSSS") , 4 , string(Form("%.3f", systUnc_stop)) ); 
  
    float systUnc_vv = (vv->Integral() > 0) ? DC.getConservativeUnc(vv, vv_systUp, vv_systDown) : 1.00;
    line.replace( line.find("VVVV") , 4 , string(Form("%.3f", systUnc_vv)) );
    
  }else{
    
    pair<float,float> defNum = std::make_pair(1.0, 1.0);
    
    auto systUnc_wh = (wh->Integral() > 0) ? DC.getConservativeUncPair(wh, wh_systUp, wh_systDown) : defNum;
    line.replace( line.find("HHHH") , 4 , string(Form("%.4f/%.4f", systUnc_wh.first, systUnc_wh.second)) );
        
    auto systUnc_ttbar = (ttbar->Integral() > 0) ? DC.getConservativeUncPair(ttbar, ttbar_systUp, ttbar_systDown) : defNum; 
    line.replace( line.find("TTTT") , 4 , string(Form("%.4f/%.4f", systUnc_ttbar.first, systUnc_ttbar.second)) ); 
        
    auto systUnc_ttg = (ttg->Integral() > 0) ? DC.getConservativeUncPair(ttg, ttg_systUp, ttg_systDown) : defNum; 
    line.replace( line.find("TTGT") , 4 , string(Form("%.4f/%.4f", systUnc_ttg.first, systUnc_ttg.second)) ); 

    auto systUnc_tth = (tth->Integral() > 0) ? DC.getConservativeUncPair(tth, tth_systUp, tth_systDown) : defNum; 
    line.replace( line.find("TTHT") , 4 , string(Form("%.4f/%.4f", systUnc_tth.first, systUnc_tth.second)) ); 

    auto systUnc_ttz = (ttz->Integral() > 0) ? DC.getConservativeUncPair(ttz, ttz_systUp, ttz_systDown) : defNum; 
    line.replace( line.find("TTZT") , 4 , string(Form("%.4f/%.4f", systUnc_ttz.first, systUnc_ttz.second)) ); 

    auto systUnc_ttw = (ttw->Integral() > 0) ? DC.getConservativeUncPair(ttw, ttw_systUp, ttw_systDown) : defNum; 
    line.replace( line.find("TTWT") , 4 , string(Form("%.4f/%.4f", systUnc_ttw.first, systUnc_ttw.second)) ); 

    auto systUnc_wjet = (wjet->Integral() > 0) ? DC.getConservativeUncPair(wjet, wjet_systUp, wjet_systDown) : defNum;
    line.replace( line.find("WWWW") , 4 , string(Form("%.4f/%.4f", systUnc_wjet.first, systUnc_wjet.second)) ); 
       
    auto systUnc_zjet = (zjet->Integral() > 0) ? DC.getConservativeUncPair(zjet, zjet_systUp, zjet_systDown) : defNum;
    line.replace( line.find("DDDD") , 4 , string(Form("%.4f/%.4f", systUnc_zjet.first, systUnc_zjet.second)) ); 
        
    auto systUnc_stop = (stop->Integral() > 0) ? DC.getConservativeUncPair(stop, stop_systUp, stop_systDown) : defNum; 
    line.replace( line.find("SSSS") , 4 , string(Form("%.4f/%.4f", systUnc_stop.first, systUnc_stop.second)) ); 

    auto systUnc_vv = (vv->Integral() > 0) ? DC.getConservativeUncPair(vv, vv_systUp, vv_systDown) : defNum;
    line.replace( line.find("VVVV") , 4 , string(Form("%.4f/%.4f", systUnc_vv.first, systUnc_vv.second)) ); 

  }

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
