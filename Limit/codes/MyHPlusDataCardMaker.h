#ifndef MyHPlusDataCardMaker_h
#define MyHPlusDataCardMaker_h

#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <fstream>
#include <iomanip>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <algorithm>
#include <TH1F.h>
#include <TFile.h>
#include <TMath.h>
#include <TKey.h>

using namespace std;
double sysSF = 1.0;

class MyHPlusDataCardMaker{
  
  public:

  TH1F* getHisto(TFile *inRootFile, TString histPath, TString histName, TFile* fTT, double sf);
  //TH1F* readWriteHisto(TFile *inFile, TString histPath, TString inHistName, double sf, TFile *outFile, TFile *fTT, TString outHistName,  bool isWrite, double min_thres, bool isNeffThreshold);
  TH1F* readWriteHisto(TFile *inFile, TString histPath, TString inHistName, double sf, TFile *outFile, TFile *fTT, TString outHistName,  bool isWrite, bool isNorm, TH1F *hBase);
  double getBTagUnc(TH1F *hCentral, TH1F* hUp, TH1F* hDown);
  double getConservativeUnc(TH1F *hCentral, TH1F* hUp, TH1F* hDown);
  double getConservativeUnc(TH1F *hCentral, TH1F* hUp, TH1F* hDown, TFile* fTT);
  pair<float,float> getConservativeUncPair(TH1F *hCentral, TH1F* hUp, TH1F* hDown);
  double getStatUnc(TH1F* hCentral, double sError);
  double getUncExL(TH1F* yLyMyT, TH1F* yLyMnT, TH1F* yLnMyT, TH1F* yLnMnT);
  double getUncExM(TH1F* yMyT, TH1F* yMnT);

  double getQcdSF(TString baseIsoDir, TFile* fData, TFile* fTT, TFile* fST, TFile* fWJ, TFile* fDY, TFile* fVV, TString histDir, TString histName);
  double getQcdDD(TString baseDir, TFile* fData, TFile* fTT, TFile* fST, TFile* fWJ, TFile* fDY, TFile* fVV, TString histDir, TString histName, double qcd_sf);
  double getSysUncQcd(TFile* fData, TFile* fTT, TFile* fST, TFile* fWJ, TFile* fDY, TFile* fVV, TString histDir, TString histName, bool isUncSF);
  TH1F* trimHisto(TH1F* hist, TString histName, int binWidth, int xMin, int xMax);
  TH1F* trimHistoNano(TH1F* hist, TString histName, float binWidth, float xMin, float xMax);
  
  double getQcdSFNano(bool isMu, TString baseDir, TFile* fData, TFile* fTT, TFile* fST, TFile* fWJ, TFile* fDY, TFile* fVV, TString histDir, TString histName);
  double getQcdDDNano(bool isMu, TString baseDir, TFile* fData, TFile* fTT, TFile* fST, TFile* fWJ, TFile* fDY, TFile* fVV, TString histDir, TString histName, double qcd_sf);
  double getSysUncQcdNano(bool isMu, TFile* fData, TFile* fTT, TFile* fST, TFile* fWJ, TFile* fDY, TFile* fVV, TString histDir, TString histName, bool isUncSF);
  int SymmetrizeErrors(string signal, TFile* fTT);
  int ModifyUpDownHisto(TH1F* hnom, TH1F*& hup, TH1F*& hdown, bool isnorm);

private:
  double dont_use;
};

////////////////////////////////////////////////////////////////////////

/* class MyHPlusDataCardMakerNano{ */
/*  public: */

/*   TH1F* getHisto(TFile *inRootFile, TString histPath, TString histName, double sf); */
/*   TH1F* readWriteHisto(TFile *inFile, TString histPath, TString inHistName, double sf, TFile *outFile, TFile *fTT, TString outHistName,  bool isWrite, TString sigFile); */
/*   double getBTagUnc(TH1F *hCentral, TH1F* hUp, TH1F* hDown); */
/*   double getStatUnc(TH1F* hCentral, double sError); */
/*   double getUncExL(TH1F* yLyMyT, TH1F* yLyMnT, TH1F* yLnMyT, TH1F* yLnMnT); */
/*   double getUncExM(TH1F* yMyT, TH1F* yMnT); */
/*   double getQcdSF(bool isMu, TString baseIsoDir, TFile* fData, TFile* fTT, TFile* fST, TFile* fWJ, TFile* fDY, TFile* fVV, TString histDir, TString histName); */
/*   double getQcdDD(bool isMu, TString baseDir, TFile* fData, TFile* fTT, TFile* fST, TFile* fWJ, TFile* fDY, TFile* fVV, TString histDir, TString histName, double qcd_sf); */
/*   double getSysUncQcd(bool isMu, TFile* fData, TFile* fTT, TFile* fST, TFile* fWJ, TFile* fDY, TFile* fVV, TString histDir, TString histName, bool isUncSF); */
/*   TH1F* trimHisto(TH1F* hist, TString histName, int binWidth, int xMin, int xMax); */
/*   TH1F* trimHistoNano(TH1F* hist, TString histName, float binWidth, float xMin, float xMax); */

/*  private: */
/*   double dont_use; */
  
/*   /\* ClassDef(MyHPlusDataCardMakerNano,1); *\/ */

/* }; */
//////////////////////////////////////////////////////////////////////////
//----------------------------------------//
//Variuos functions
//----------------------------------------//
TH1F*  MyHPlusDataCardMaker:: getHisto(TFile *inRootFile, TString histPath, TString histName, TFile *fTT, double sf=1.0){
  TH1F* hist;
  TString fullPath = histPath+histName;
  string exception_msg (inRootFile->GetName()+TString("/")+fullPath+", does not exist");
  try{
    if(!(inRootFile->Get(fullPath)))
       throw  exception_msg.c_str();
  }catch (const char *e){
    cout<<"WARNING:"<<e<<endl;
  }
  if(!(inRootFile->Get(fullPath))){
    hist = (TH1F*)(fTT->Get(fullPath))->Clone(histName);
    hist->Reset();
  }else {
    hist = (TH1F*)(inRootFile->Get(fullPath))->Clone(histName);
  }
  hist->Scale(sf);
  return hist;
}

//Read histos from input file. Write to another file.

TH1F* MyHPlusDataCardMaker::readWriteHisto(TFile *inFile, TString histPath, TString inHistName, double sf, TFile *outFile, TFile *fTT, TString outHistName,  bool isWrite = false, bool isNorm = false, TH1F *hBase = 0x0){
  TH1F* hist = (TH1F*) getHisto(inFile, histPath, inHistName, fTT)->Clone(outHistName);
  hist->Scale(sf);
  if(hist->GetNbinsX()==50)
    hist->Rebin(1);
  if(hist->GetNbinsX()==2400)
    hist->Rebin(50);
  TH1F* trimmedHist = trimHistoNano(hist, outHistName+"_1", 5., 20., 170.);
  // if(hist->GetNbinsX()==50)
  //   hist->Rebin(2);
  // if(hist->GetNbinsX()==2400)
  //   hist->Rebin(100);
  // TH1F* trimmedHist = trimHistoNano(hist, outHistName+"_1", 10., 20., 170.);
  if(outHistName.Contains("CMS_stat_")){
    string hname = outHistName.Data();
    string binnum  = "";
    if(hname.find("Up")!=string::npos){
      binnum = hname.substr( hname.find_last_of("_")+1, hname.find_last_of("Up") - hname.find_last_of("_") - 1 - 1);
    }
    if(hname.find("Down")!=string::npos){
      binnum = hname.substr( hname.find_last_of("_")+1, hname.find_last_of("Do") - hname.find_last_of("_") - 1 - 1);
    }
    int ibin = atoi(binnum.c_str());
    TH1F* trimmedHist_Temp = (TH1F *)trimmedHist->Clone("temp");
    if(hname.find("Up")!=string::npos and trimmedHist->GetBinContent(ibin) > 0.0){
      float error = trimmedHist->GetBinError(ibin);
      float up_val = trimmedHist->GetBinContent(ibin) + error;
      trimmedHist_Temp->SetBinContent(ibin, up_val);
      trimmedHist_Temp->SetBinError(ibin, error);
    }
    if(hname.find("Down")!=string::npos and trimmedHist->GetBinContent(ibin) > 0.0){
      float error = trimmedHist->GetBinError(ibin);
      float down_val = trimmedHist->GetBinContent(ibin) - error;
      down_val = (down_val>0.0) ? down_val : 0.0 ;
      error = (down_val>0.0) ? error : 0.0;
      trimmedHist_Temp->SetBinContent(ibin, down_val);
      trimmedHist_Temp->SetBinError(ibin, error);
    }
    trimmedHist = (TH1F *)trimmedHist_Temp->Clone(outHistName);
    delete trimmedHist_Temp ; 
  }
  if(isNorm){
    if(!hBase){
      trimmedHist->Scale(1.0/trimmedHist->Integral());
    }else{
      cout<<"====trimmed name : "<<trimmedHist->GetName()<<", base name : "<<hBase->GetName() << endl;
      cout<<"====trimmed integral : "<<trimmedHist->Integral()<<", base integral : "<<hBase->Integral() << endl;
      if(trimmedHist->Integral() > 0.) trimmedHist->Scale(hBase->Integral()/trimmedHist->Integral());
    }
  }
  if(isWrite){
    outFile->cd();
    ///hist->Write(outHistName);
    trimmedHist->Write(outHistName);
  }
  
  ///return hist;
  return trimmedHist;
}

//get normalised uncertainity
double MyHPlusDataCardMaker::getBTagUnc(TH1F *hCentral, TH1F* hUp, TH1F* hDown){
  return 1 + max(fabs(hUp->Integral() - hCentral->Integral()), fabs(hCentral->Integral() - hDown->Integral()))/hCentral->Integral();
}

double MyHPlusDataCardMaker::getConservativeUnc(TH1F *hCentral, TH1F* hUp, TH1F* hDown){
  double maxUp = -1.;
  double maxDown = -1.;
  for(int ibin=1;ibin<=hCentral->GetNbinsX();ibin++){
    double upBin = TMath::Abs(hUp->GetBinContent(ibin));
    double downBin = TMath::Abs(hDown->GetBinContent(ibin));
    double baseBin = TMath::Abs(hCentral->GetBinContent(ibin));
    double fracBase = baseBin/hCentral->Integral(); //to avoid edge bins that contains less than 1% of total yield
    //if(TMath::AreEqualAbs(upBin,0.0,1.e-5) or TMath::AreEqualAbs(downBin,0.0,1.e-5) or TMath::AreEqualAbs(baseBin,0.0,1.e-5) or fracBase<0.03) continue;
    if(TMath::AreEqualAbs(upBin,0.0,1.e-5) or TMath::AreEqualAbs(downBin,0.0,1.e-5) or TMath::AreEqualAbs(baseBin,0.0,1.e-5)) continue;
    double ratioUp = (baseBin>upBin) ?  upBin/baseBin : baseBin/upBin;
    double ratioDown = (baseBin>downBin) ?  downBin/baseBin : baseBin/downBin;
    double fracUp = 1.0 - ratioUp;
    double fracDown = 1.0 - ratioDown;
    maxUp = max(fracUp,maxUp);
    maxDown = max(fracDown,maxDown);
  }
  return 1 + max(maxUp, maxDown);
}

double MyHPlusDataCardMaker::getConservativeUnc(TH1F *hCentral, TH1F* hUp, TH1F* hDown, TFile* outFile){
  
  // double maxUp = 0.;
  // double maxDown = 0.;
  string basename = hCentral->GetName(); 
  string upsystname = hUp->GetName(); 
  string downsystname = hDown->GetName(); 
  
  if(basename.find("_1") == string::npos) basename += "_1";
  if(upsystname.find("_1") == string::npos) upsystname += "_1";
  if(downsystname.find("_1") == string::npos) downsystname += "_1";
  
  TH1F *hBase = (TH1F *)outFile->Get(basename.data());
  TH1F *hSysUp = (TH1F *)outFile->Get(upsystname.data());
  TH1F *hSysDown = (TH1F *)outFile->Get(downsystname.data());
  // cout <<"MyHPlusDataCardMaker::getConservativeUnc: hBase : " << hBase << ", hBase name: "<<basename
  //      <<", Up: " << hSysUp << ", hUp name: " << upsystname
  //      << ", Down: " <<  hSysDown << ", hDown name: " << downsystname
  //      << endl;
  ModifyUpDownHisto(hBase, hSysUp, hSysDown, false);
  
  // for(int ibin=1;ibin<=hCentral->GetNbinsX();ibin++){
  //   double upBin = TMath::Abs(hSysUp->GetBinContent(ibin));
  //   double downBin = TMath::Abs(hSysDown->GetBinContent(ibin));
  //   double baseBin = TMath::Abs(hBase->GetBinContent(ibin));
  //   double fracBase = baseBin/hBase->Integral(); //to avoid edge bins that contains less than 1% of total yield
  //   //if(TMath::AreEqualAbs(upBin,0.0,1.e-5) or TMath::AreEqualAbs(downBin,0.0,1.e-5) or TMath::AreEqualAbs(baseBin,0.0,1.e-5) or fracBase<0.03) continue;
  //   if(TMath::AreEqualAbs(upBin,0.0,1.e-5) or TMath::AreEqualAbs(downBin,0.0,1.e-5) or TMath::AreEqualAbs(baseBin,0.0,1.e-5)) continue;
  //   double ratioUp = (baseBin>upBin) ?  upBin/baseBin : baseBin/upBin;
  //   double ratioDown = (baseBin>downBin) ?  downBin/baseBin : baseBin/downBin;
  //   double fracUp = 1.0 - ratioUp;
  //   double fracDown = 1.0 - ratioDown;
  //   maxUp = max(fracUp,maxUp);
  //   maxDown = max(fracDown,maxDown);
  // }
  //return 1 + max(maxUp, maxDown);
  
  return 1 + max(fabs(hSysUp->Integral() - hBase->Integral()), fabs(hBase->Integral() - hSysDown->Integral()))/hBase->Integral();

}

pair<float,float> MyHPlusDataCardMaker::getConservativeUncPair(TH1F *hCentral, TH1F* hUp, TH1F* hDown){
  double maxUp = -1.;
  double maxDown = -1.;
  for(int ibin=1;ibin<=hCentral->GetNbinsX();ibin++){
    double upBin = TMath::Abs(hUp->GetBinContent(ibin));
    double downBin = TMath::Abs(hDown->GetBinContent(ibin));
    double baseBin = TMath::Abs(hCentral->GetBinContent(ibin));
    if(TMath::AreEqualAbs(upBin,0.0,1.e-5) or TMath::AreEqualAbs(downBin,0.0,1.e-5) or TMath::AreEqualAbs(baseBin,0.0,1.e-5)) continue;
    double ratioUp = (baseBin>upBin) ?  upBin/baseBin : baseBin/upBin;
    double ratioDown = (baseBin>downBin) ?  downBin/baseBin : baseBin/downBin;
    double fracUp = 1.0 - ratioUp;
    double fracDown = 1.0 - ratioDown;
    maxUp = max(fracUp,maxUp);
    maxDown = max(fracDown,maxDown);
  }
  maxUp /= 1.0;
  maxDown /= 1.0;
  return std::make_pair(1 + maxUp, 1 + maxDown);
}

//get statistical uncertainity
double MyHPlusDataCardMaker::getStatUnc(TH1F* hCentral, double sError = 0.0){
  double  norm = hCentral->IntegralAndError(1, hCentral->GetNbinsX(), sError);
  double statUnc = (norm > 0) ? 1 + (fabs(sError)/norm) : 1.00;
  return statUnc;
}

TH1F* MyHPlusDataCardMaker::trimHisto(TH1F* hist, TString histName, int binWidth, int xMin, int xMax){
    double nBin = (xMax-xMin)/binWidth;
    TH1F* newHisto = new TH1F(histName, histName, nBin, xMin, xMax);
    double initX = xMin/binWidth;
    double lastX = xMax/binWidth;
    for(int i = initX; i<lastX; i++){
      double binVal = hist->GetBinContent(i);
      double binErr = hist->GetBinError(i);
      int i_new = i- initX+1;
      newHisto->SetBinContent(i_new, binVal);
      newHisto->SetBinError(i_new, binErr);
    }
    return newHisto;
}

TH1F* MyHPlusDataCardMaker::trimHistoNano(TH1F* hist, TString histName, float binWidth, float xMin, float xMax){
  int nBin = TMath::Nint((xMax-xMin)/binWidth);
    TH1F* newHisto = new TH1F(histName, histName, nBin, xMin, xMax);
    int initX = TMath::Nint(xMin/binWidth);
    int lastX = TMath::Nint(xMax/binWidth);
    for(int i = initX; i<lastX; i++){
      double binVal = hist->GetBinContent(i);
      double binErr = hist->GetBinError(i);
      int i_new = i - initX;
      newHisto->SetBinContent(i_new, binVal);
      newHisto->SetBinError(i_new, binErr);
    }
    return newHisto;
}

double MyHPlusDataCardMaker::getUncExL(TH1F* yLyMyT, TH1F* yLyMnT, TH1F* yLnMyT, TH1F* yLnMnT){
  double m_yLyMyT = yLyMyT->GetMean();
  double m_yLyMnT = yLyMnT->GetMean();
  double m_yLnMyT = yLnMyT->GetMean();
  double m_yLnMnT = yLnMnT->GetMean();
  vector<double> vecExL;
  vecExL.push_back(m_yLyMyT);
  vecExL.push_back(m_yLyMnT);
  vecExL.push_back(m_yLnMyT);
  vecExL.push_back(m_yLnMnT);
  auto it_min = min_element(std::begin(vecExL), std::end(vecExL));
  auto it_max = max_element(std::begin(vecExL), std::end(vecExL));
  double min = *it_min;
  double max = *it_max;
  double unc = max/min;
  //--------------------
  //double tmp_budh = unc -1;
  //unc = 1+ 2*tmp_budh;
  //--------------------
  return (min>0 && max>0)?unc:1.0;
}

double MyHPlusDataCardMaker::getUncExM(TH1F* yMyT, TH1F* yMnT){
  double m_yMyT = yMyT->GetMean();
  double m_yMnT = yMnT->GetMean();
  vector<double> vecExM;
  vecExM.push_back(m_yMyT);
  vecExM.push_back(m_yMnT);
  auto it_min = min_element(std::begin(vecExM), std::end(vecExM));
  auto it_max = max_element(std::begin(vecExM), std::end(vecExM));
  double min = *it_min;
  double max = *it_max;
  double unc = max/min;
  //--------------------
  //double tmp_budh = unc -1;
  //unc = 1+ 2*tmp_budh;
  //--------------------
  return (min>0 && max>0)?unc:1.0;
}

// qcd SF for data-driven QCD
double MyHPlusDataCardMaker::getQcdSF(TString baseIsoDir, TFile* fData, TFile* fTT, TFile* fST, TFile* fWJ, TFile* fDY, TFile* fVV, TString histDir, TString histName){
  //RegionC = LowMET, Iso
  TH1F* hVV_RegC = getHisto(fVV,   baseIsoDir+"/NonIso/"+histDir, histName, fTT);
  TH1F* hDY_RegC = getHisto(fDY,   baseIsoDir+"/NonIso/"+histDir, histName, fTT);
  TH1F* hWJ_RegC = getHisto(fWJ,   baseIsoDir+"/NonIso/"+histDir, histName, fTT);
  TH1F* hST_RegC = getHisto(fST,   baseIsoDir+"/NonIso/"+histDir, histName, fTT);
  TH1F* hTT_RegC = getHisto(fTT,   baseIsoDir+"/NonIso/"+histDir, histName, fTT);
  TH1F* hMC_RegC = (TH1F*)hVV_RegC->Clone("hAllMC_RegC");
  hMC_RegC->Add(hDY_RegC);
  hMC_RegC->Add(hWJ_RegC);
  hMC_RegC->Add(hST_RegC);
  hMC_RegC->Add(hTT_RegC);
  TH1F* hData_RegC= getHisto(fData, baseIsoDir+"/NonIso/"+histDir, histName, fTT);
  //RegionD = LowMET, NonIso
  TH1F* hVV_RegD = getHisto(fVV,   baseIsoDir+"/Iso/"+histDir, histName, fTT);
  TH1F* hDY_RegD = getHisto(fDY,   baseIsoDir+"/Iso/"+histDir, histName, fTT);
  TH1F* hWJ_RegD = getHisto(fWJ,   baseIsoDir+"/Iso/"+histDir, histName, fTT);
  TH1F* hST_RegD = getHisto(fST,   baseIsoDir+"/Iso/"+histDir, histName, fTT);
  TH1F* hTT_RegD = getHisto(fTT,   baseIsoDir+"/Iso/"+histDir, histName, fTT);
  TH1F* hMC_RegD = (TH1F*)hVV_RegD->Clone("hAllMC_RegD");
  hMC_RegD->Add(hDY_RegD);
  hMC_RegD->Add(hWJ_RegD);
  hMC_RegD->Add(hST_RegD);
  hMC_RegD->Add(hTT_RegD);
  TH1F* hData_RegD=  getHisto(fData, baseIsoDir+"/Iso/"+histDir, histName, fTT);
  TH1F* hDiffC = (TH1F*)hData_RegC->Clone("hDiffC");
  hDiffC->Add(hMC_RegC, -1);
  //If binContent < 0, set it to 0
  for(int ibin=1; ibin<hDiffC->GetNbinsX(); ibin++){
    double binCont = hDiffC->GetBinContent(ibin);
    if(binCont<0){
      hDiffC->SetBinContent(ibin, 0);
      //hDiffC->SetBinError(ibin, 0);
    }
  }
  TH1F* hDiffD = (TH1F*)hData_RegD->Clone("hDiffD");
  hDiffD->Add(hMC_RegD, -1);
  for(int ibin=1; ibin<hDiffD->GetNbinsX(); ibin++){
    double binCont = hDiffD->GetBinContent(ibin);
    if(binCont<0){
      hDiffD->SetBinContent(ibin, 0);
      //hDiffD->SetBinError(ibin, 0);
    }
  }
  double intDiffC   = hDiffC->Integral();
  double intDiffD   = hDiffD->Integral();
  double ratioDiffDC = intDiffD/intDiffC;
  return ratioDiffDC;
}

double MyHPlusDataCardMaker::getQcdDD(TString baseDir, TFile* fData, TFile* fTT, TFile* fST, TFile* fWJ, TFile* fDY, TFile* fVV, TString histDir, TString histName, double qcd_sf=1.0){
  TH1F* hVV = getHisto(fVV,   baseDir+"/NonIso/"+histDir, histName, fTT);
  TH1F* hDY = getHisto(fDY,   baseDir+"/NonIso/"+histDir, histName, fTT);
  TH1F* hWJ = getHisto(fWJ,   baseDir+"/NonIso/"+histDir, histName, fTT);
  TH1F* hST = getHisto(fST,   baseDir+"/NonIso/"+histDir, histName, fTT);
  TH1F* hTT = getHisto(fTT,   baseDir+"/NonIso/"+histDir, histName, fTT);
  TH1F* hData= getHisto(fData, baseDir+"/NonIso/"+histDir, histName, fTT);
  TH1F* hOtherMC = (TH1F*)hVV->Clone("hOtherMC");
  hOtherMC->Add(hDY);
  hOtherMC->Add(hST);
  hOtherMC->Add(hWJ);
  hOtherMC->Add(hTT);
  TH1F* hQCD = (TH1F*)hData->Clone(histName);
  hQCD->Add(hOtherMC, -1);
  //If binContent < 0, set it to 0
  for(int ibin=1; ibin<hQCD->GetNbinsX(); ibin++){
    double binCont = hQCD->GetBinContent(ibin);
    if(binCont<0){
      hQCD->SetBinContent(ibin, 0);
      //hQCD->SetBinError(ibin, 0);
    }
  }
  hQCD->Scale(qcd_sf);
  return hQCD->Integral();
}

double MyHPlusDataCardMaker::getSysUncQcd(TFile* fData, TFile* fTT, TFile* fST, TFile* fWJ, TFile* fDY, TFile* fVV, TString histDir, TString histName, bool isUncSF){
  double sf_baseIsoDir = getQcdSF("baseLowMET", fData, fTT, fST, fWJ, fDY, fVV, histDir, histName);
  double qcd_baseIsoDir = getQcdDD("base", fData, fTT, fST, fWJ, fDY, fVV, histDir, histName, sf_baseIsoDir);
  double sf_baseShiftedIsoDir = getQcdSF("baseIso20LowMET", fData, fTT, fST, fWJ, fDY, fVV, histDir, histName);
  double qcd_baseShiftedIsoDir = getQcdDD("baseIso20HighMET", fData, fTT, fST, fWJ, fDY, fVV, histDir, histName, sf_baseShiftedIsoDir);
  double sf_unc = abs(sf_baseIsoDir - sf_baseShiftedIsoDir)/sf_baseIsoDir;
  double qcd_unc = abs(qcd_baseIsoDir - qcd_baseShiftedIsoDir)/qcd_baseIsoDir;
  /* cout<<"-------------------------------------"<<endl; */
  /* cout<<"sf_baseIsoDir 	      = "<<sf_baseIsoDir<<endl; */
  /* cout<<"sf_baseShiftedIsoDir = "<<sf_baseShiftedIsoDir<<endl; */
  /* cout<<"sf_unc               = "<<sf_unc<<endl; */
  /* cout<<"qcd_baseIsoDir 	   = "<<qcd_baseIsoDir<<endl; */
  /* cout<<"qcd_baseShiftedIsoDir = "<<qcd_baseShiftedIsoDir<<endl; */
  /* cout<<"qcd_unc               = "<<qcd_unc<<endl; */
  /* cout<<"-------------------------------------"<<endl; */
  double unc = 0.0;
  if(isUncSF) unc = sf_unc;
  else unc = qcd_unc;
  return 1+unc;
}
//////////////////////////////////////////////////////////////////////////////////////


/* TH1F*  MyHPlusDataCardMakerNano:: getHisto(TFile *inRootFile, TString histPath, TString histName, double sf=1.0){ */
/*   TH1F* hist; */
/*   TString fullPath = histPath+histName; */
/*   /\* cout << "file : " << inRootFile->GetName() << ", fullPath : " << fullPath << ", histName : " << histName << endl; *\/ */
  
/*   string exception_msg (inRootFile->GetName()+TString("/")+fullPath+", does not exist"); */
/*   try{ */
/*     if(!(inRootFile->Get(fullPath))) */
/*        throw  exception_msg.c_str(); */
/*   }catch (const char *e){ */
/*     ///cout<<"WARNING:"<<e<<endl; */
/*   } */
/*   /\* try{ *\/ */
/*   /\*   if(!(fTT->Get(fullPath))) *\/ */
/*   /\*      throw  exception_msg.c_str(); *\/ */
/*   /\* }catch (const char *e){ *\/ */
/*   /\*   cout<<"\033[01;31mERROR: \033[0m"<<e<< endl; *\/ */
/*   /\*   exit(0); *\/ */
/*   /\* } *\/ */
/*   /\* if(!(inRootFile->Get(fullPath))){ *\/ */
/*   /\*   hist = (TH1F*)(fTT->Get(fullPath))->Clone(histName); *\/ */
/*   /\*   hist->Reset(); *\/ */
/*   /\* } *\/ */
/*   /\* else  *\/ */
/*   hist = (TH1F*)(inRootFile->Get(fullPath))->Clone(histName); */
  
/*   hist->Scale(sf); */
  
/*   return hist; */
/* } */

/* //Read histos from input file. Write to another file. */
/* TH1F* MyHPlusDataCardMakerNano::readWriteHisto(TFile *inFile, TString histPath, TString inHistName, double sf, TFile *outFile, TFile *fTT, TString outHistName,  bool isWrite, TString sigFile){ */
  
/*   /\* cout << "infile : " << inFile->GetName() << ", histPath : " << histPath << ", histName : " << inHistName << endl; *\/ */
/*   TH1F* hist = (TH1F*) getHisto(inFile, histPath, inHistName)->Clone(outHistName); */
/*   /\* cout << "Infile : " << inFile->GetName() << ", inHistName : " << inHistName *\/ */
/*   /\*      << ",\nOutFile : " << outFile->GetName() << ", outHistName : " << outHistName *\/ */
/*   /\*      << endl; *\/ */
  
/*   //hist->SetBins(20,50.,150.); */
/*   hist->Scale(sf); */

  
/*   //hist->Rebin(1); */
  
/*   /\* double mjjMin = 10; *\/ */
/*   /\* double mjjMax = 165; *\/ */
/*   /\* if(sigFile.Contains("80")) { *\/ */
/*   /\*   mjjMin = 10; mjjMax = 165; *\/ */
/*   /\* } *\/ */
/*   /\* if(sigFile.Contains("90")) { *\/ */
/*   /\*   mjjMin = 10; mjjMax = 165; *\/ */
/*   /\* } *\/ */
  
/*   TH1F* trimmedHist = trimHisto(hist, outHistName, 5, 20, 170); */
/*   trimmedHist->Rebin(1); */
/*   //TH1F* trimmedHist = trimHistoNano(hist, outHistName, 0.1, 20., 170.); */
/*   //trimmedHist->Rebin(50); */
/*   if(isWrite){ */
/*     outFile->cd(); */
/*     //hist->Write(outHistName); */
/*     trimmedHist->Write(outHistName); */
/*   } */
  

/*   //return hist; */
/*   return trimmedHist; */
/* } */

/* //get normalised uncertainity */
/* double MyHPlusDataCardMakerNano::getBTagUnc(TH1F *hCentral, TH1F* hUp, TH1F* hDown){ */
/*   return 1 + sysSF* max(fabs(hUp->Integral() - hCentral->Integral()), fabs(hCentral->Integral() - hDown->Integral()))/hCentral->Integral(); */
/* } */

/* //get statistical uncertainity */
/* double MyHPlusDataCardMakerNano::getStatUnc(TH1F* hCentral, double sError = 0.0){ */
/*   double  norm = hCentral->IntegralAndError(1, hCentral->GetNbinsX(), sError); */
/*   double statUnc = (norm > 0) ? 1 + (fabs(sError)/norm) : 1.00; */
/*   return statUnc; */
/* } */

/* TH1F* MyHPlusDataCardMakerNano::trimHisto(TH1F* hist, TString histName, int binWidth, int xMin, int xMax){ */
/*     double nBin = (xMax-xMin)/binWidth; */
/*     TH1F* newHisto = new TH1F(histName, histName, nBin, xMin, xMax); */
/*     double initX = xMin/binWidth; */
/*     double lastX = xMax/binWidth; */
/*     for(int i = initX; i<lastX; i++){ */
/*       double binVal = hist->GetBinContent(i); */
/*       double binErr = hist->GetBinError(i); */
/*       int i_new = i- initX+1; */
/*       newHisto->SetBinContent(i_new, binVal); */
/*       newHisto->SetBinError(i_new, binErr); */
/*     } */
/*     return newHisto; */
/* } */


/* TH1F* MyHPlusDataCardMakerNano::trimHistoNano(TH1F* hist, TString histName, float binWidth, float xMin, float xMax){ */

/*   int nBin = TMath::Nint((xMax-xMin)/binWidth); */
/*   TH1F* newHisto = new TH1F(histName, histName, nBin, xMin, xMax); */
/*   double initX = xMin/binWidth; */
/*   double lastX = xMax/binWidth; */
/*   for(int i = initX; i<lastX; i++){ */
/*     double binVal = hist->GetBinContent(i); */
/*     double binErr = hist->GetBinError(i); */
/*     int i_new = i - initX+1; */
/*     newHisto->SetBinContent(i_new, binVal); */
/*     newHisto->SetBinError(i_new, binErr); */
/*   } */
/*   return newHisto; */
/* } */

/* double MyHPlusDataCardMakerNano::getUncExL(TH1F* yLyMyT, TH1F* yLyMnT, TH1F* yLnMyT, TH1F* yLnMnT){ */
/*   double m_yLyMyT = yLyMyT->GetMean(); */
/*   double m_yLyMnT = yLyMnT->GetMean(); */
/*   double m_yLnMyT = yLnMyT->GetMean(); */
/*   double m_yLnMnT = yLnMnT->GetMean(); */
/*   vector<double> vecExL; */
/*   vecExL.push_back(m_yLyMyT); */
/*   vecExL.push_back(m_yLyMnT); */
/*   vecExL.push_back(m_yLnMyT); */
/*   vecExL.push_back(m_yLnMnT); */
/*   auto it_min = min_element(std::begin(vecExL), std::end(vecExL)); */
/*   auto it_max = max_element(std::begin(vecExL), std::end(vecExL)); */
/*   double min = *it_min; */
/*   double max = *it_max; */
/*   double unc = max/min; */
/*   //-------------------- */
/*   //double tmp_budh = unc -1; */
/*   //unc = 1+ 2*tmp_budh; */
/*   //-------------------- */
/*   return (min>0 && max>0)?unc:1.0; */
/* } */

/* double MyHPlusDataCardMakerNano::getUncExM(TH1F* yMyT, TH1F* yMnT){ */
/*   double m_yMyT = yMyT->GetMean(); */
/*   double m_yMnT = yMnT->GetMean(); */
/*   vector<double> vecExM; */
/*   vecExM.push_back(m_yMyT); */
/*   vecExM.push_back(m_yMnT); */
/*   auto it_min = min_element(std::begin(vecExM), std::end(vecExM)); */
/*   auto it_max = max_element(std::begin(vecExM), std::end(vecExM)); */
/*   double min = *it_min; */
/*   double max = *it_max; */
/*   double unc = max/min; */
/*   //-------------------- */
/*   //double tmp_budh = unc -1; */
/*   //unc = 1+ 2*tmp_budh; */
/*   //-------------------- */
/*   return (min>0 && max>0)?unc:1.0; */
/* } */

// qcd SF for data-driven QCD
double MyHPlusDataCardMaker::getQcdSFNano(bool isMu, TString baseDir, TFile* fData, TFile* fTT, TFile* fST, TFile* fWJ, TFile* fDY, TFile* fVV, TString histDir, TString histName){
  //RegionC = LowMET, NonIso
  TH1F* hVV_RegC = getHisto(fVV,   "VBFusion/"+baseDir+"/NonIsoLowMET/" , histName+"_noniso_lmet", fTT);
  TH1F* hDY_RegC = getHisto(fDY,   "DYjets/"+baseDir+"/NonIsoLowMET/" , histName+"_noniso_lmet", fTT);
  TH1F* hWJ_RegC = getHisto(fWJ,   "Wjets/"+baseDir+"/NonIsoLowMET/" , histName+"_noniso_lmet", fTT);
  TH1F* hST_RegC = getHisto(fST,   "singleTop/"+baseDir+"/NonIsoLowMET/" , histName+"_noniso_lmet", fTT);
  TH1F* hTT_RegC = getHisto(fTT,   "TTbar/"+baseDir+"/NonIsoLowMET/" , histName+"_noniso_lmet", fTT);
  TH1F* hMC_RegC = (TH1F*)hVV_RegC->Clone("hAllMC_RegC");
  hMC_RegC->Add(hDY_RegC);
  hMC_RegC->Add(hWJ_RegC);
  hMC_RegC->Add(hST_RegC);
  hMC_RegC->Add(hTT_RegC);
  TH1F* hData_RegC = (isMu) ? getHisto(fData, "DataMu/"+baseDir+"/NonIsoLowMET/", histName+"_noniso_lmet", fTT) : getHisto(fData, "DataEle/"+baseDir+"/NonIsoLowMET/", histName+"_noniso_lmet", fTT);
  
  //RegionD = LowMET, Iso
  TH1F* hVV_RegD = getHisto(fVV,   "VBFusion/"+baseDir+"/LowMET/" , histName+"_lmet", fTT);
  TH1F* hDY_RegD = getHisto(fDY,   "DYjets/"+baseDir+"/LowMET/" , histName+"_lmet", fTT);
  TH1F* hWJ_RegD = getHisto(fWJ,   "Wjets/"+baseDir+"/LowMET/" , histName+"_lmet", fTT);
  TH1F* hST_RegD = getHisto(fST,   "singleTop/"+baseDir+"/LowMET/" , histName+"_lmet", fTT);
  TH1F* hTT_RegD = getHisto(fTT,   "TTbar/"+baseDir+"/LowMET/" , histName+"_lmet", fTT);
  TH1F* hMC_RegD = (TH1F*)hVV_RegD->Clone("hAllMC_RegD");
  hMC_RegD->Add(hDY_RegD);
  hMC_RegD->Add(hWJ_RegD);
  hMC_RegD->Add(hST_RegD);
  hMC_RegD->Add(hTT_RegD);
  TH1F* hData_RegD=  (isMu) ? getHisto(fData, "DataMu/"+baseDir+"/LowMET/", histName+"_lmet", fTT) : getHisto(fData, "DataEle/"+baseDir+"/LowMET/", histName+"_lmet", fTT);

  TH1F* hDiffC = (TH1F*)hData_RegC->Clone("hDiffC");
  hDiffC->Add(hMC_RegC, -1);
  //If binContent < 0, set it to 0
  for(int ibin=1; ibin<hDiffC->GetNbinsX(); ibin++){
    double binCont = hDiffC->GetBinContent(ibin);
    if(binCont<0){
      hDiffC->SetBinContent(ibin, 0);
      //hDiffC->SetBinError(ibin, 0);
    }
  }
  TH1F* hDiffD = (TH1F*)hData_RegD->Clone("hDiffD");
  hDiffD->Add(hMC_RegD, -1);
  for(int ibin=1; ibin<hDiffD->GetNbinsX(); ibin++){
    double binCont = hDiffD->GetBinContent(ibin);
    if(binCont<0){
      hDiffD->SetBinContent(ibin, 0);
      //hDiffD->SetBinError(ibin, 0);
    }
  }
  //cout <<"hTT_RegC :: Name : "<< hTT_RegC->GetName()<<", bins : " << hTT_RegC->GetNbinsX() << ", Integral : " << hTT_RegC->Integral() << endl;
  double intDiffC   = hDiffC->Integral();
  double intDiffD   = hDiffD->Integral();
  double ratioDiffDC = intDiffD/intDiffC;
  if(TMath::AreEqualAbs(intDiffD,0.0,1.e-5) or TMath::AreEqualAbs(intDiffC,0.0,1.e-5)){ //in case hit zero use absolute instead of (Data-MC) this only influencens the control plot of MET pt
    double num = TMath::Max(TMath::Abs(hData_RegD->Integral()-hMC_RegD->Integral()),1.0);
    double deno = TMath::Max(TMath::Abs(hData_RegC->Integral()-hMC_RegC->Integral()),1.0);
    ratioDiffDC = num/deno;
  }
  cout<<"intDiffC : " << intDiffC <<", intDiffD : "<<intDiffD<<", ratioDiffDC : " << ratioDiffDC<<endl;
  return ratioDiffDC;
  
}

double MyHPlusDataCardMaker::getQcdDDNano(bool isMu, TString baseDir, TFile* fData, TFile* fTT, TFile* fST, TFile* fWJ, TFile* fDY, TFile* fVV, TString histDir, TString histName, double qcd_sf=1.0){
  /* TH1F* hVV = getHisto(fVV,   baseDir+"/NonIso/"+histDir, histName, fTT); */
  /* TH1F* hDY = getHisto(fDY,   baseDir+"/NonIso/"+histDir, histName, fTT); */
  /* TH1F* hWJ = getHisto(fWJ,   baseDir+"/NonIso/"+histDir, histName, fTT); */
  /* TH1F* hST = getHisto(fST,   baseDir+"/NonIso/"+histDir, histName, fTT); */
  /* TH1F* hTT = getHisto(fTT,   baseDir+"/NonIso/"+histDir, histName, fTT); */
  /* TH1F* hData= getHisto(fData, baseDir+"/NonIso/"+histDir, histName, fTT); */
  
  TH1F* hVV = getHisto(fVV,   "VBFusion/"+baseDir+"/NonIso/" , histName+"_noniso", fTT);
  TH1F* hDY = getHisto(fDY,   "DYjets/"+baseDir+"/NonIso/", histName+"_noniso", fTT);
  TH1F* hWJ = getHisto(fWJ,   "Wjets/"+baseDir+"/NonIso/", histName+"_noniso", fTT);
  TH1F* hST = getHisto(fST,   "singleTop/"+baseDir+"/NonIso/", histName+"_noniso", fTT);
  TH1F* hTT = getHisto(fTT,   "TTbar/"+baseDir+"/NonIso/", histName+"_noniso", fTT);
  TH1F* hData= (isMu) ? getHisto(fData,"DataMu/"+baseDir+"/NonIso/", histName+"_noniso", fTT) : getHisto(fData,"DataEle/"+baseDir+"/NonIso/", histName+"_noniso", fTT);
  
  TH1F* hOtherMC = (TH1F*)hVV->Clone("hOtherMC");
  hOtherMC->Add(hDY);
  hOtherMC->Add(hST);
  hOtherMC->Add(hWJ);
  hOtherMC->Add(hTT);
  TH1F* hQCD = (TH1F*)hData->Clone(histName+"_noniso");
  hQCD->Add(hOtherMC, -1);
  //If binContent < 0, set it to 0
  for(int ibin=1; ibin<hQCD->GetNbinsX(); ibin++){
    double binCont = hQCD->GetBinContent(ibin);
    if(binCont<0){
      hQCD->SetBinContent(ibin, 0);
      //hQCD->SetBinError(ibin, 0);
    }
  }
  hQCD->Scale(qcd_sf);
  return hQCD->Integral();
}

double MyHPlusDataCardMaker::getSysUncQcdNano(bool isMu, TFile* fData, TFile* fTT, TFile* fST, TFile* fWJ, TFile* fDY, TFile* fVV, TString histDir, TString histName, bool isUncSF){
  
  double sf_baseIsoDir = getQcdSFNano(isMu, "base", fData, fTT, fST, fWJ, fDY, fVV, histDir, histName);
  double qcd_baseIsoDir = getQcdDDNano(isMu, "base", fData, fTT, fST, fWJ, fDY, fVV, histDir, histName, sf_baseIsoDir);
  double sf_baseShiftedIsoDir = getQcdSFNano(isMu, "iso20", fData, fTT, fST, fWJ, fDY, fVV, histDir, histName);
  double qcd_baseShiftedIsoDir = getQcdDDNano(isMu, "iso20", fData, fTT, fST, fWJ, fDY, fVV, histDir, histName, sf_baseShiftedIsoDir);
  
  double sf_unc = abs(sf_baseIsoDir - sf_baseShiftedIsoDir)/sf_baseIsoDir;
  double qcd_unc = sysSF* abs(qcd_baseIsoDir - qcd_baseShiftedIsoDir)/qcd_baseIsoDir;
  cout<<"-------------------------------------"<<endl;
  cout<<"sysSF  	      = "<<sysSF<<endl;
  cout<<"sf_baseIsoDir 	      = "<<sf_baseIsoDir<<endl;
  cout<<"sf_baseShiftedIsoDir = "<<sf_baseShiftedIsoDir<<endl;
  cout<<"sf_unc               = "<<sf_unc<<endl;
  cout<<"qcd_baseIsoDir 	   = "<<qcd_baseIsoDir<<endl;
  cout<<"qcd_baseShiftedIsoDir = "<<qcd_baseShiftedIsoDir<<endl;
  cout<<"qcd_unc               = "<<qcd_unc<<endl;
  cout<<"-------------------------------------"<<endl;
  double unc = 0.0;
  if(isUncSF) unc = sf_unc;
  else unc = qcd_unc;
  return 1+unc;
}

int MyHPlusDataCardMaker::SymmetrizeErrors(string signal, TFile* outFile)
{
  outFile->cd();
  vector<string> systnames;
  TIter nextkey(outFile->GetListOfKeys());
  TKey *key;
  while ((key = ((TKey*)nextkey())) ) {
    TObject *obj = key->ReadObj();
    if ( obj->IsA()->InheritsFrom( "TH1" ) ) {
      TH1 *h1 = (TH1*)obj;
      string kname =  key->GetName();
      string sname = "";
      if(((kname.find("Up") != string::npos) or (kname.find("Down") != string::npos)) and kname.find(signal)!=string::npos){
	if(signal=="qcd" and (kname.find("flavorqcd") != string::npos)) continue;
  	sname = (kname.find("Up") != string::npos) ? kname.substr(kname.find("_")+1,kname.find_last_of("U")-kname.find("_")-1) : kname.substr(kname.find("_")+1,kname.find_last_of("D")-kname.find("_")-1) ;
  	if(std::find(systnames.begin(), systnames.end(), sname) == systnames.end()) systnames.push_back(sname);
      }
    }
  }
  TH1F *hBase = (TH1F *)outFile->Get((signal+"_1").data());
  for(const auto sname : systnames) {
    TH1F *hSysUp = (TH1F *)outFile->Get((signal+"_"+sname+"Up_1").data());
    TH1F *hSysDown = (TH1F *)outFile->Get((signal+"_"+sname+"Down_1").data());
    // if((sname.find("fsr") != string::npos) or (sname.find("bcstat") != string::npos) or (sname.find("isr") != string::npos))
    //ModifyUpDownHisto(hBase, hSysUp, hSysDown, true);
    // else
    //if(sname.find("qcddd") == string::npos){
    ModifyUpDownHisto(hBase, hSysUp, hSysDown, false);
    hSysUp->Write((signal+"_"+sname+"Up").data(),TObject::kWriteDelete);
    hSysDown->Write((signal+"_"+sname+"Down").data(),TObject::kWriteDelete);
  }

  return true;
}

int MyHPlusDataCardMaker::ModifyUpDownHisto(TH1F* hnom, TH1F*& hup, TH1F*& hdown, bool isnorm)
{

  TH1F *hupbynom = (TH1F *)hup->Clone("hRelErrUp");
  hupbynom->Divide(hnom);
  TH1F *hdownbynom = (TH1F *)hdown->Clone("hRelErrDown");
  hdownbynom->Divide(hnom);

  for(int ibin=1; ibin<hupbynom->GetNbinsX(); ibin++){
    double bindiff = TMath::Abs(hupbynom->GetBinContent(ibin) - hdownbynom->GetBinContent(ibin));
    double binerror = hupbynom->GetBinError(ibin) + hdownbynom->GetBinError(ibin);
    double bindiff_up = TMath::Abs(hupbynom->GetBinContent(ibin) - 1.0);
    double bindiff_down = TMath::Abs(hdownbynom->GetBinContent(ibin) - 1.0);
    // cout << hupbynom->GetName() << " at bin : " << ibin << ", at x = " << hupbynom->GetXaxis()->GetBinCenter(ibin) << " has bindiff_up: " << bindiff_up << " has content: " << hupbynom->GetBinContent(ibin) << endl;
    // cout << hdownbynom->GetName() << " at bin : " << ibin << ", at x = " << hdownbynom->GetXaxis()->GetBinCenter(ibin) << " has bindiff_down: " << bindiff_down << " has content: " << hdownbynom->GetBinContent(ibin) << endl;
    // cout << hnom->GetName() << " at bin : " << ibin << ", at x = " << hnom->GetXaxis()->GetBinCenter(ibin) << " has content: " << hnom->GetBinContent(ibin) << endl; 
    //if(binerror>bindiff or TMath::AreEqualAbs(hup->GetBinContent(ibin),0.0,1e-5)  or TMath::AreEqualAbs(hdown->GetBinContent(ibin),0.0,1e-5) or bindiff_down>1.0 or bindiff_up>1.0){
    if(TMath::AreEqualAbs(hup->GetBinContent(ibin),0.0,1e-5)  or TMath::AreEqualAbs(hdown->GetBinContent(ibin),0.0,1e-5) or bindiff_down>1.0 or bindiff_up>1.0){
      //cout << "ZERO for " << hupbynom->GetName() << " at bin : " << ibin << ", at x = " << hupbynom->GetXaxis()->GetBinCenter(ibin) << " has bindiff: " << bindiff << " and binerror: " << binerror << endl ;
      hup->SetBinContent(ibin, hnom->GetBinContent(ibin));
      hup->SetBinError(ibin, hnom->GetBinError(ibin));
      hdown->SetBinContent(ibin, hnom->GetBinContent(ibin));
      hdown->SetBinError(ibin, hnom->GetBinError(ibin));
    }else{
      if(bindiff_up>bindiff_down){
	hdown->SetBinContent(ibin, (2.0-hupbynom->GetBinContent(ibin))*hnom->GetBinContent(ibin));
      }else{
	hup->SetBinContent(ibin, (2.0-hdownbynom->GetBinContent(ibin))*hnom->GetBinContent(ibin));
      }//content symmetric condition
    }//binerror condn
  }
  
  if(isnorm){
    hdown->Scale(hnom->Integral()/hdown->Integral());
    hup->Scale(hnom->Integral()/hup->Integral());
  }
  
  TH1F *hup_temp = (TH1F *)hup->Clone("hUpTemp");
  TH1F *hdown_temp = (TH1F *)hdown->Clone("hDownTemp");

  //if "ICES" is specified, resets only Integral, Contents, Errors and Statistics
  //See https://root.cern.ch/doc/master/classTH1.html#a537509270db4e59efb39619b94c3a9a4
  hup->Reset("ICES"); 
  hdown->Reset("ICES");
  for(int ibin=1;ibin<=hup_temp->GetNbinsX();ibin++) {
    double binVal = hup_temp->GetBinContent(ibin);
    double binErr = hup_temp->GetBinError(ibin);
    hup->SetBinContent(ibin, binVal);
    hup->SetBinError(ibin, binErr);
  }
  for(int ibin=1;ibin<=hdown_temp->GetNbinsX();ibin++) {
    double binVal = hdown_temp->GetBinContent(ibin);
    double binErr = hdown_temp->GetBinError(ibin);
    hdown->SetBinContent(ibin, binVal);
    hdown->SetBinError(ibin, binErr);
  }
  
  delete hup_temp;
  delete hdown_temp;
  delete hupbynom;
  delete hdownbynom;
  
  return true;
  
}

#endif
