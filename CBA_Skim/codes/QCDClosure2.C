/**********************************************************************
 Created on : 23/10/2021
 Purpose    : Create the root file with QCD DD results
 Author     : Indranil Das, Visiting Fellow
 Email      : indranil.das@cern.ch | indra.ehep@gmail.com
**********************************************************************/
#include <TH1.h>
#include <THStack.h>
#include <TF1.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TAxis.h>
#include <TStyle.h>
#include <TMath.h>
#include <TKey.h>
#include <TPaveStats.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TAttMarker.h>
#include <TAttLine.h>
#include <TRatioPlot.h>
#include <TPaveText.h>

#include <iostream>

using namespace std;
int QCDClosure2(int year = 2016, bool isMu = false)
{

  void makeHistoPositive(TH1D *, bool);
  double getStatUnc(TH1D *, double);
  
  //const char* dir = "grid_v40_Syst/CBA_kfoffset";
  const char* dir = "grid_v40_Syst/CBA_kfoffset-CombHist";
  //const char* dir = "grid_v40_Syst/CBA_kfoffset-CombHist-toppt";
  //const char* dir = "grid_v40_Syst/CBA_kfwidth-CombHist";
  //const char* dir = "grid_v40_Syst/CBA_mutight-CombHist";
  //const char* dir = "grid_v40_Syst/CBA_elemva90-CombHist";

  const char *systType = "iso20";
  //bool isMu = false;
  bool isReBin = true;
  
  string histname = (isMu) ? "_kb_mjj_mu" : "_kb_mjj_ele" ;
  string histname_RegA = histname ;
  string histname_RegB = histname + "_noniso";
  string histname_RegC = histname + "_noniso_lmet";
  string histname_RegD = histname + "_lmet";
  
  const char* qcdfile = (isMu) ? Form("root_files/%s/%d/all_MCQCDMu.root",dir,year) : Form("root_files/%s/%d/all_MCQCDEle.root",dir,year) ;
  TFile *fin_nano_ttbar = TFile::Open(Form("root_files/%s/%d/all_TTbar.root",dir,year));
  TFile *fin_nano_stop	= TFile::Open(Form("root_files/%s/%d/all_singleTop.root",dir,year));
  TFile *fin_nano_wjets	= TFile::Open(Form("root_files/%s/%d/all_Wjets.root",dir,year));
  TFile *fin_nano_dyjets = TFile::Open(Form("root_files/%s/%d/all_DYjets.root",dir,year));
  TFile *fin_nano_vbf	= TFile::Open(Form("root_files/%s/%d/all_VBFusion.root",dir,year));
  TFile *fin_nano_qcd	= TFile::Open(qcdfile);
  
  // ///////////////////////////////////////// Get  the histograms from files //////////////////////////////// 
  TH1D *hcf_RegA_ttbar	= (TH1D *)fin_nano_ttbar->Get(Form("TTbar/%s/Iso/%s",systType,histname_RegA.c_str()));
  TH1D *hcf_RegA_stop	= (TH1D *)fin_nano_stop->Get(Form("singleTop/%s/Iso/%s",systType,histname_RegA.c_str())); 
  TH1D *hcf_RegA_wjets	= (TH1D *)fin_nano_wjets->Get(Form("Wjets/%s/Iso/%s",systType,histname_RegA.c_str()));
  TH1D *hcf_RegA_dyjets	= (TH1D *)fin_nano_dyjets->Get(Form("DYjets/%s/Iso/%s",systType,histname_RegA.c_str()));
  TH1D *hcf_RegA_vbf	= (TH1D *)fin_nano_vbf->Get(Form("VBFusion/%s/Iso/%s",systType,histname_RegA.c_str()));
  TH1D *hcf_RegA_qcd	= (TH1D *)fin_nano_qcd->Get(((isMu) ? Form("MCQCDMu/%s/Iso/%s",systType,histname_RegA.c_str()) : Form("MCQCDEle/%s/Iso/%s",systType,histname_RegA.c_str())));  
  cout<<"MC QCD : " << hcf_RegA_qcd->Integral() <<" +/- "<< getStatUnc(hcf_RegA_qcd,0.0) << endl;
  
  TH1D *hcf_RegB_ttbar	= (TH1D *)fin_nano_ttbar->Get(Form("TTbar/%s/NonIso/%s",systType,histname_RegB.c_str()));
  TH1D *hcf_RegB_stop	= (TH1D *)fin_nano_stop->Get(Form("singleTop/%s/NonIso/%s",systType,histname_RegB.c_str())); 
  TH1D *hcf_RegB_wjets	= (TH1D *)fin_nano_wjets->Get(Form("Wjets/%s/NonIso/%s",systType,histname_RegB.c_str()));
  TH1D *hcf_RegB_dyjets	= (TH1D *)fin_nano_dyjets->Get(Form("DYjets/%s/NonIso/%s",systType,histname_RegB.c_str()));
  TH1D *hcf_RegB_vbf	= (TH1D *)fin_nano_vbf->Get(Form("VBFusion/%s/NonIso/%s",systType,histname_RegB.c_str()));
  TH1D *hcf_RegB_qcd	= (TH1D *)fin_nano_qcd->Get(((isMu) ? Form("MCQCDMu/%s/NonIso/%s",systType,histname_RegB.c_str()) : Form("MCQCDEle/%s/NonIso/%s",systType,histname_RegB.c_str())));  
  
  TH1D *hcf_RegC_ttbar	= (TH1D *)fin_nano_ttbar->Get(Form("TTbar/%s/NonIsoLowMET/%s",systType,histname_RegC.c_str()));
  TH1D *hcf_RegC_stop	= (TH1D *)fin_nano_stop->Get(Form("singleTop/%s/NonIsoLowMET/%s",systType,histname_RegC.c_str())); 
  TH1D *hcf_RegC_wjets	= (TH1D *)fin_nano_wjets->Get(Form("Wjets/%s/NonIsoLowMET/%s",systType,histname_RegC.c_str()));
  TH1D *hcf_RegC_dyjets	= (TH1D *)fin_nano_dyjets->Get(Form("DYjets/%s/NonIsoLowMET/%s",systType,histname_RegC.c_str()));
  TH1D *hcf_RegC_vbf	= (TH1D *)fin_nano_vbf->Get(Form("VBFusion/%s/NonIsoLowMET/%s",systType,histname_RegC.c_str()));
  TH1D *hcf_RegC_qcd	= (TH1D *)fin_nano_qcd->Get(((isMu) ? Form("MCQCDMu/%s/NonIsoLowMET/%s",systType,histname_RegC.c_str()) : Form("MCQCDEle/%s/NonIsoLowMET/%s",systType,histname_RegC.c_str()))); 

  TH1D *hcf_RegD_ttbar	= (TH1D *)fin_nano_ttbar->Get(Form("TTbar/%s/LowMET/%s",systType,histname_RegD.c_str()));
  TH1D *hcf_RegD_stop	= (TH1D *)fin_nano_stop->Get(Form("singleTop/%s/LowMET/%s",systType,histname_RegD.c_str())); 
  TH1D *hcf_RegD_wjets	= (TH1D *)fin_nano_wjets->Get(Form("Wjets/%s/LowMET/%s",systType,histname_RegD.c_str()));
  TH1D *hcf_RegD_dyjets	= (TH1D *)fin_nano_dyjets->Get(Form("DYjets/%s/LowMET/%s",systType,histname_RegD.c_str()));
  TH1D *hcf_RegD_vbf	= (TH1D *)fin_nano_vbf->Get(Form("VBFusion/%s/LowMET/%s",systType,histname_RegD.c_str()));
  TH1D *hcf_RegD_qcd	= (TH1D *)fin_nano_qcd->Get(((isMu) ? Form("MCQCDMu/%s/LowMET/%s",systType,histname_RegD.c_str()) : Form("MCQCDEle/%s/LowMET/%s",systType,histname_RegD.c_str()))); 
  // ////////////////////////////////End of getting the histograms from files //////////////////////////////// 
  
  //////////////////////////////// Add the MCs but MCQCD /////////////////////////////////////////////////
  //All MC but MCQCD
  TH1D *hcf_RegA_bkg = (TH1D *)hcf_RegA_ttbar->Clone("RegA_bkg");
  hcf_RegA_bkg->Add(hcf_RegA_stop);
  hcf_RegA_bkg->Add(hcf_RegA_wjets);
  hcf_RegA_bkg->Add(hcf_RegA_dyjets);
  hcf_RegA_bkg->Add(hcf_RegA_vbf);

  TH1D *hcf_RegB_bkg = (TH1D *)hcf_RegB_ttbar->Clone("RegB_bkg");
  hcf_RegB_bkg->Add(hcf_RegB_stop);
  hcf_RegB_bkg->Add(hcf_RegB_wjets);
  hcf_RegB_bkg->Add(hcf_RegB_dyjets);
  hcf_RegB_bkg->Add(hcf_RegB_vbf);

  TH1D *hcf_RegC_bkg = (TH1D *)hcf_RegC_ttbar->Clone("RegC_bkg");
  hcf_RegC_bkg->Add(hcf_RegC_stop);
  hcf_RegC_bkg->Add(hcf_RegC_wjets);
  hcf_RegC_bkg->Add(hcf_RegC_dyjets);
  hcf_RegC_bkg->Add(hcf_RegC_vbf);
  
  TH1D *hcf_RegD_bkg = (TH1D *)hcf_RegD_ttbar->Clone("RegD_bkg");
  hcf_RegD_bkg->Add(hcf_RegD_stop);
  hcf_RegD_bkg->Add(hcf_RegD_wjets);
  hcf_RegD_bkg->Add(hcf_RegD_dyjets);
  hcf_RegD_bkg->Add(hcf_RegD_vbf);
  /////////////////////////////////////////////////////////////////////////////////////////////////////////

  ///////////////////////////////// Create Data histogram /////////////////////////////////////////////////
  TH1D *hcf_RegA_data = (TH1D *)hcf_RegA_bkg->Clone("RegA_data");
  hcf_RegA_data->Add(hcf_RegA_qcd);
  TH1D *hcf_RegB_data = (TH1D *)hcf_RegB_bkg->Clone("RegB_data");
  hcf_RegB_data->Add(hcf_RegB_qcd);
  TH1D *hcf_RegC_data = (TH1D *)hcf_RegC_bkg->Clone("RegC_data");
  hcf_RegC_data->Add(hcf_RegC_qcd);
  TH1D *hcf_RegD_data = (TH1D *)hcf_RegD_bkg->Clone("RegD_data");
  hcf_RegD_data->Add(hcf_RegD_qcd);
  printf("systType : %10s, hist : %20s, Data(A,B,C,D) : (%5.4lf, %5.4lf, %5.4lf, %5.4lf)\n",
  	 systType, histname.c_str(), hcf_RegA_data->Integral(),hcf_RegB_data->Integral(),hcf_RegC_data->Integral(),hcf_RegD_data->Integral());
  printf("systType : %10s, hist : %20s, MC(A,B,C,D) : (%5.4lf, %5.4lf, %5.4lf, %5.4lf)\n",
  	 systType, histname.c_str(), hcf_RegA_bkg->Integral(),hcf_RegB_bkg->Integral(),hcf_RegC_bkg->Integral(),hcf_RegD_bkg->Integral());
  //////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  if(isReBin){
    int rebin = 50;
    hcf_RegA_bkg->Rebin(rebin);
    hcf_RegB_bkg->Rebin(rebin);
    hcf_RegC_bkg->Rebin(rebin);
    hcf_RegD_bkg->Rebin(rebin);
    hcf_RegA_data->Rebin(rebin);
    hcf_RegB_data->Rebin(rebin);
    hcf_RegC_data->Rebin(rebin);
    hcf_RegD_data->Rebin(rebin);
  }
  
  //////////////////////////////// Get the QCD for regions ////////////////////////////////////////////////
  TH1D *hcf_RegD_QCD = (TH1D *)hcf_RegD_data->Clone("RegD_QCD");
  hcf_RegD_QCD->Add(hcf_RegD_bkg, -1);  
  makeHistoPositive(hcf_RegD_QCD, false) ;
    
  TH1D *hcf_RegC_QCD = (TH1D *)hcf_RegC_data->Clone("RegC_QCD");
  hcf_RegC_QCD->Add(hcf_RegC_bkg, -1);
  makeHistoPositive(hcf_RegC_QCD, false) ;

  TH1D *hcf_RegB_QCD = (TH1D *)hcf_RegB_data->Clone("RegB_QCD");
  hcf_RegB_QCD->Add(hcf_RegB_bkg, -1);
  makeHistoPositive(hcf_RegB_QCD, false) ;

  TH1D *hcf_RegA_QCD = (TH1D *)hcf_RegA_data->Clone("RegA_QCD");
  hcf_RegA_QCD->Add(hcf_RegA_bkg, -1);
  cout<<"QCD (before) : " << hcf_RegA_QCD->Integral() <<" +/- "<< getStatUnc(hcf_RegA_QCD,0.0) << endl;
  makeHistoPositive(hcf_RegA_QCD, false) ;
  cout<<"QCD (after) : " << hcf_RegA_QCD->Integral() <<" +/- "<< getStatUnc(hcf_RegA_QCD,0.0) << endl;
  printf("systType : %10s, hist : %20s, QCD(A,B,C,D) : (%5.4lf, %5.4lf, %5.4lf, %5.4lf)\n",
  	 systType, histname.c_str(), hcf_RegA_QCD->Integral(),hcf_RegB_QCD->Integral(),hcf_RegC_QCD->Integral(),hcf_RegD_QCD->Integral());

  /////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  //////////////////////////////// Calculate the QCD SF ///////////////////////////////////////////////////
  // double intDiffC   = hcf_RegC_QCD->Integral();
  // double errDiffC   = getStatUnc(hcf_RegC_QCD, 0.0);
  // double intDiffD   = hcf_RegD_QCD->Integral();
  // double errDiffD   = getStatUnc(hcf_RegD_QCD, 0.0);
  
  double intDiffC   = TMath::Abs(hcf_RegC_QCD->Integral());
  double errDiffC   = TMath::Abs(getStatUnc(hcf_RegC_QCD, 0.0));
  double intDiffD   = TMath::Abs(hcf_RegD_QCD->Integral());
  double errDiffD   = TMath::Abs(getStatUnc(hcf_RegD_QCD, 0.0));
  
  //Ratio of (Data-MC) from RegionD and RegionC
  double SF = intDiffD/intDiffC;
  if(TMath::AreEqualAbs(intDiffD,0.0,1.e-5) or TMath::AreEqualAbs(intDiffC,0.0,1.e-5)){ //in case hit zero use absolute instead of (Data-MC) this only influencens the control plot of MET pt
    double num = TMath::Max(TMath::Abs(hcf_RegD_data->Integral()-hcf_RegD_bkg->Integral()),1.0);
    double deno = TMath::Max(TMath::Abs(hcf_RegC_data->Integral()-hcf_RegC_bkg->Integral()),1.0);
    SF = num/deno;
  }
  double tmpD = errDiffD/intDiffD;
  if(TMath::AreEqualAbs(intDiffD,0.0,1.e-5)) //in case hit zero use Data only instead of (Data-MC) this only influcens the control plot of MET pt
    tmpD = getStatUnc(hcf_RegD_data, 0.0)/hcf_RegD_data->Integral();
  
  double tmpC = errDiffC/intDiffC;
  if(TMath::AreEqualAbs(intDiffC,0.0,1.e-5)) //in case hit zero use Data only instead of (Data-MC) this only influcens the control plot of MET pt
     tmpC = getStatUnc(hcf_RegC_data, 0.0)/hcf_RegC_data->Integral();
  
  double SF_error = SF*sqrt(tmpD*tmpD + tmpC*tmpC);
  printf("systType : %10s, intDiffC : %5.4lf +/- %5.4lf, , intDiffC : %5.4lf +/- %5.4lf, SF(%20s) : %5.4lf +/- %5.4lf\n",
  	 systType, intDiffC, errDiffC, intDiffD, errDiffD, histname.c_str(),SF,SF_error);
  printf("systType : %10s, SF(%20s) : %5.4lf +/- %5.4lf\n",systType, histname.c_str(),SF,SF_error);
  /////////////////////////////////////////////////////////////////////////////////////////////////////////

  /////////////////////////////// Modify the Region B result //////////////////////////////////////////////
  double sError = 0.0;
  double  norm = hcf_RegB_QCD->IntegralAndError(1, hcf_RegB_QCD->GetNbinsX(), sError);
  //cout<<"intB = "<<norm<<", intB_err = "<<sError<<endl;
  double tot_bin_cont = 0.0;
  double tot_bin_err = 0.0;
  for(int ibin=1; ibin<hcf_RegB_QCD->GetNbinsX(); ibin++){
      double bin_cont = hcf_RegB_QCD->GetBinContent(ibin);
      double bin_err = hcf_RegB_QCD->GetBinError(ibin);
      double new_bin_cont = SF*bin_cont;
      double new_bin_err = sqrt(pow(bin_cont*SF_error, 2) + pow(bin_err*SF, 2));
      tot_bin_cont = tot_bin_cont + new_bin_cont;
      tot_bin_err = tot_bin_err + new_bin_err*new_bin_err;
      hcf_RegA_QCD->SetBinContent(ibin, new_bin_cont);
      //hcf_RegA_QCD->SetBinError(ibin, new_bin_err);
  }
  hcf_RegA_bkg->Add(hcf_RegA_QCD);
  cout<<"tot_bin_cont= "<<tot_bin_cont<<", tot_bin_err = "<<sqrt(tot_bin_err)<<endl;
  // /////////////////////////////////////////////////////////////////////////////////////////////////////////
  // d3->cd();
  TH1D *hDD = (TH1D *)hcf_RegA_QCD->Clone(Form("%s",histname.c_str()));
  
  cout<<"DD QCD : " << hDD->Integral() <<" +/- "<< getStatUnc(hDD,0.0) <<" +/- "<< sqrt(tot_bin_err) << endl;

  
  printf("\\begin{tabular}{c c c}\n");
  printf("\\hline\n");
  //printf("\\multicolumn{5}{>{\\color{%s}\\columncolor[gray]{0.8}}c}{ %s : ($%s$ + jets) for %d } \\\\\\hline \n",color.c_str(),levelname.c_str(),lepname.c_str(),year);
  printf("Year & MC QCD in Region-A & DD QCD in Region-A \\\\ \n");
  printf("%d  & $%2.0lf\\pm%2.0lf$ & $%2.0lf\\pm%2.0lf$  \\\\ \\hline \n",
         year, hcf_RegA_qcd->Integral(), getStatUnc(hcf_RegA_qcd,0.0), hcf_RegA_QCD->Integral(), getStatUnc(hcf_RegA_QCD, 0.0));
  printf("\\end{tabular}\n");
  
  fin_nano_ttbar->Close();   fin_nano_stop->Close();   
  fin_nano_wjets->Close();   fin_nano_dyjets->Close() ; fin_nano_vbf->Close();   //fin_nano_qcd->Close();   

  delete fin_nano_ttbar;   delete fin_nano_stop;   
  delete fin_nano_wjets;   delete fin_nano_dyjets ; delete fin_nano_vbf;   //delete fin_nano_qcd;   

  return true;
}


void makeHistoPositive(TH1D *hist, bool setErrorZero = false){
  for(int ibin=1; ibin<hist->GetNbinsX(); ibin++){
    double binCont = hist->GetBinContent(ibin);
    if(binCont<0){
      hist->SetBinContent(ibin, 0);
      if(setErrorZero) hist->SetBinError(ibin, 0);
    }
  }
}

double getStatUnc(TH1D* hCentral, double sError = 0.0){
  double  norm = hCentral->IntegralAndError(1, hCentral->GetNbinsX(), sError);
  //double statUnc = (norm > 0) ? 1 + (fabs(sError)/norm) : 1.00;
  double statUnc = sError;
  return statUnc;
}
