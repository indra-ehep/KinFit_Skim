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
int CreateQCDDD()
{
  
  int QCDDDAll(bool isBtag, bool isMu, int htype,int year,TDirectory *d3, const char *, const char *, TH1D *hDD);
  
  int year = 2017;
  //const char* dir = "grid_v35_Syst/CBA_Skim_Syst_jetsmeared";
  //const char* dir = "grid_v35_Syst/CBA_Skim_Syst_jetsmeared_metcorr";
  //const char* dir = "grid_v35_Syst/CBA_Skim_Syst_allDD";
  //const char* dir = "grid_v35_Syst/CBA_Skim_Syst_highreso";
  //const char* dir = "grid_v36_Syst/CBA_Skim_Syst_metMG";
  //const char* dir = "grid_v36_Syst/CBA_Skim_Syst_njet4to8";
  //const char* dir = "grid_v36_Syst/CBA_Skim_Syst_lowreso";
  //const char* dir = "grid_v36_Syst/CBA_Skim_Syst_btagCSV";
  //const char* dir = "grid_v37_Syst/CBA_Skim_Syst_SlStudy2";
  //const char* dir = "grid_v37_Syst/CBA_Skim_Syst_SlStudy3";
  //const char* dir = "grid_v37_Syst/CBA_Skim_Syst_SlStudy4";
  //const char* dir = "grid_v37_Syst/CBA_Skim_Syst_SlStudy5";
  //const char* dir = "grid_v37_Syst/CBA_Skim_Syst_SlStudy6";
  //const char* dir = "grid_v37_Syst/CBA_Skim_Syst_SlStudy7";
  //const char* dir = "grid_v38_Syst/CBA_Skim_Syst_TuneTest1";
  //const char* dir = "grid_v39_Syst/ULv9_long";
  //const char* dir = "grid_v39_Syst/CBA_KFNewReso";
  //const char* dir = "grid_v39_Syst/CBA_1718_Resubmit";
  //const char* dir = "grid_v39_Syst/CBA_CTagM";
  //const char* dir = "grid_v39_Syst/CBA_GeneratorWt";
  const char* dir = "grid_v39_Syst/CBA_CTagDD";
  
  const char *syst[] = {"base", 
			"puup", "pudown", "mueffup", "mueffdown", 
			"eleeffup", "eleeffdown",  "jecup", "jecdown", 
			"jerup", "jerdown", "btagbup", "btagbdown", 
			"btaglup", "btagldown", "prefireup", "prefiredown",
			"pdfup", "pdfdown", "q2fup", "q2down",
			"isrup", "isrdown", "fsrup", "fsrdown", 
			"iso20", "metup", "metdown",
			"bctag1up", "bctag1down", "bctag2up", "bctag2down",
			"bctag3up", "bctag3down"};

  
  TFile *fout = new TFile("all_QCDdd.root","recreate");
  TDirectory *d1 = fout->mkdir("QCDdd");
  d1->cd();
  
  for(int isys = 0 ; isys < 34 ; isys++) {

    TDirectory *d2 = d1->mkdir(Form("%s",syst[isys]));
    d2->cd();
    TDirectory *d3 = d2->mkdir("Iso");
    d3->cd();
    TH1D *hDD;
    int htype_max[2] = {16, 9};
    for(int ibtag = 0 ; ibtag < 2 ; ibtag++)
      for(int ismu = 0 ; ismu < 2 ; ismu++)
	for(int htype = 0 ; htype <= htype_max[ibtag] ; htype++)
	  QCDDDAll((bool)ibtag, (bool)ismu, htype, year, d3, dir, syst[isys], hDD);
    d3->Write();
  }
  fout->Close();
  delete fout;

  return true;
}

string GetHistName(bool isBtag = 1, bool isMu = 1, int htype = 0)
{
  string histname;
  histname += (isBtag) ? "_lb" : "_kb" ; 
  
  if(htype==0)
    histname += (isMu) ? "_pt_mu" : "_pt_ele" ;  
  else if (htype==1)
    histname += (isMu) ? "_pt_mu_jets" : "_pt_ele_jets" ;  
  else if (htype==2)
    histname += (isMu) ? "_pt_mu_met" : "_pt_ele_met" ;  
  else if(htype==3)
    histname += (isMu) ? "_eta_mu" : "_eta_ele" ;  
  else if (htype==4)
    histname += (isMu) ? "_eta_mu_jets" : "_eta_ele_jets" ;
  else if(htype==5)
    histname += (isMu) ? "_phi_mu" : "_phi_ele" ;  
  else if (htype==6)
    histname += (isMu) ? "_phi_mu_jets" : "_phi_ele_jets" ;  
  else if (htype==7)
    histname += (isMu) ? "_phi_mu_met" : "_phi_ele_met" ;  
  else if (htype==8)
    histname += (isMu) ? "_njet_mu" : "_njet_ele" ;  
  else if (htype==9)
    histname += (isMu) ? "_nbjet_mu" : "_nbjet_ele" ;  
  else if (htype==10)
    histname += (isMu) ? "_mjj_mu" : "_mjj_ele" ;  
  else if (htype==11)
    histname = (isMu) ? "_ct_IncL_mjj_mu" : "_ct_IncL_mjj_ele" ;  
  else if (htype==12)
    histname = (isMu) ? "_ct_IncM_mjj_mu" : "_ct_IncM_mjj_ele" ;  
  else if (htype==13)
    histname = (isMu) ? "_ct_IncT_mjj_mu" : "_ct_IncT_mjj_ele" ;  
  else if (htype==14)
    histname = (isMu) ? "_ct_ExcL_mjj_mu" : "_ct_ExcL_mjj_ele" ;  
  else if (htype==15)
    histname = (isMu) ? "_ct_ExcM_mjj_mu" : "_ct_ExcM_mjj_ele" ;  
  else if (htype==16)
    histname = (isMu) ? "_ct_ExcT_mjj_mu" : "_ct_ExcT_mjj_ele" ;  

  return histname;
}

int QCDDDAll(bool isBtag, bool isMu, int htype, int year, TDirectory *d3, const char* dir, const char *systType, TH1D *hDD)
{
  
  void makeHistoPositive(TH1D *, bool);
  double getStatUnc(TH1D *, double);
  
  string GetHistName(bool isBtag, bool isMu, int htype);
  
  ///////////////////////////////////////////////////////////////////////////////////////////////  
  float luminosity[3] = {35.9, 41.5, 59.7};

  string histname = GetHistName(isBtag, isMu, htype) ;
  string histname_RegA = histname ;
  string histname_RegB = histname + "_noniso";
  string histname_RegC = histname + "_noniso_lmet";
  string histname_RegD = histname + "_lmet";
  
  string outputpdf = Form("figs/Week_Work_Report/2021-11-05/%d/DD/hist%s.pdf",year,histname.c_str());
  //const char* dir = "grid_v31_Syst/CBA_Skim_Syst_MedID";
  //const char* dir = "grid_v32_Syst/CBA_Skim_Syst_jet_tightID";
  //const char* dir = "grid_v33_Syst/CBA_Skim_Syst_EqPAGAug02";
  //const char* dir = "grid_v34_Syst/CBA_Skim_Syst_jet_tightID_mW140";
  string SystType(systType);
  
  const char* datafile = (isMu) ? Form("root_files/%s/%d/all_DataMu.root",dir,year) : Form("root_files/%s/%d/all_DataEle.root",dir,year) ;
  const char* qcdfile = (isMu) ? Form("root_files/%s/%d/all_MCQCDMu.root",dir,year) : Form("root_files/%s/%d/all_MCQCDEle.root",dir,year) ;
  TFile *fin_nano_data	= TFile::Open(datafile);
  TFile *fin_nano_sig = 0x0 ;
  if(year == 2016)
    fin_nano_sig	= TFile::Open(Form("root_files/%s/%d/all_HplusM120.root",dir,year));
  TFile *fin_nano_ttbar = TFile::Open(Form("root_files/%s/%d/all_TTbar.root",dir,year));
  TFile *fin_nano_stop	= TFile::Open(Form("root_files/%s/%d/all_singleTop.root",dir,year));
  TFile *fin_nano_wjets	= TFile::Open(Form("root_files/%s/%d/all_Wjets.root",dir,year));
  TFile *fin_nano_dyjets = TFile::Open(Form("root_files/%s/%d/all_DYjets.root",dir,year));
  TFile *fin_nano_vbf	= TFile::Open(Form("root_files/%s/%d/all_VBFusion.root",dir,year));
  TFile *fin_nano_qcd	= TFile::Open(qcdfile);
  
  ///////////////////////////////////////// Get  the histograms from files //////////////////////////////// 
  TH1D *hcf_RegA_data	= 0x0;
  if(SystType=="iso20")
    hcf_RegA_data = (TH1D *)fin_nano_data->Get(((isMu) ? Form("DataMu/%s/Iso/%s",systType,histname_RegA.c_str()) : Form("DataEle/%s/Iso/%s",systType,histname_RegA.c_str())));
  else
    hcf_RegA_data = (TH1D *)fin_nano_data->Get(((isMu) ? Form("DataMu/base/Iso/%s",histname_RegA.c_str()) : Form("DataEle/base/Iso/%s",histname_RegA.c_str())));
  //TH1D *hcf_RegA_data	= (TH1D *)fin_nano_data->Get(((isMu) ? Form("DataMu/base/Iso/%s",histname_RegA.c_str()) : Form("DataEle/base/Iso/%s",histname_RegA.c_str())));
  TH1D *hcf_RegA_sig = 0x0 ;
  if(year == 2016)
    hcf_RegA_sig	= (TH1D *)fin_nano_sig->Get(Form("HplusM120/%s/Iso/%s",systType,histname_RegA.c_str()));
  TH1D *hcf_RegA_ttbar	= (TH1D *)fin_nano_ttbar->Get(Form("TTbar/%s/Iso/%s",systType,histname_RegA.c_str()));
  TH1D *hcf_RegA_stop	= (TH1D *)fin_nano_stop->Get(Form("singleTop/%s/Iso/%s",systType,histname_RegA.c_str())); 
  TH1D *hcf_RegA_wjets	= (TH1D *)fin_nano_wjets->Get(Form("Wjets/%s/Iso/%s",systType,histname_RegA.c_str()));
  TH1D *hcf_RegA_dyjets	= (TH1D *)fin_nano_dyjets->Get(Form("DYjets/%s/Iso/%s",systType,histname_RegA.c_str()));
  TH1D *hcf_RegA_vbf	= (TH1D *)fin_nano_vbf->Get(Form("VBFusion/%s/Iso/%s",systType,histname_RegA.c_str()));
  TH1D *hcf_RegA_qcd	= (TH1D *)fin_nano_qcd->Get(((isMu) ? Form("MCQCDMu/%s/Iso/%s",systType,histname_RegA.c_str()) : Form("MCQCDEle/%s/Iso/%s",systType,histname_RegA.c_str())));  
  
  
  TH1D *hcf_RegB_data	= 0x0;
  if(SystType=="iso20")
    hcf_RegB_data = (TH1D *)fin_nano_data->Get(((isMu) ? Form("DataMu/%s/NonIso/%s",systType,histname_RegB.c_str()) : Form("DataEle/%s/NonIso/%s",systType,histname_RegB.c_str())));
  else
    hcf_RegB_data = (TH1D *)fin_nano_data->Get(((isMu) ? Form("DataMu/base/NonIso/%s",histname_RegB.c_str()) : Form("DataEle/base/NonIso/%s",histname_RegB.c_str())));
  //TH1D *hcf_RegB_data	= (TH1D *)fin_nano_data->Get(((isMu) ? Form("DataMu/base/NonIso/%s",histname_RegB.c_str()) : Form("DataEle/base/NonIso/%s",histname_RegB.c_str())));xs
  TH1D *hcf_RegB_sig = 0x0 ;
  if(year == 2016)
    hcf_RegB_sig	= (TH1D *)fin_nano_sig->Get(Form("HplusM120/%s/NonIso/%s",systType,histname_RegB.c_str()));
  TH1D *hcf_RegB_ttbar	= (TH1D *)fin_nano_ttbar->Get(Form("TTbar/%s/NonIso/%s",systType,histname_RegB.c_str()));
  TH1D *hcf_RegB_stop	= (TH1D *)fin_nano_stop->Get(Form("singleTop/%s/NonIso/%s",systType,histname_RegB.c_str())); 
  TH1D *hcf_RegB_wjets	= (TH1D *)fin_nano_wjets->Get(Form("Wjets/%s/NonIso/%s",systType,histname_RegB.c_str()));
  TH1D *hcf_RegB_dyjets	= (TH1D *)fin_nano_dyjets->Get(Form("DYjets/%s/NonIso/%s",systType,histname_RegB.c_str()));
  TH1D *hcf_RegB_vbf	= (TH1D *)fin_nano_vbf->Get(Form("VBFusion/%s/NonIso/%s",systType,histname_RegB.c_str()));
  TH1D *hcf_RegB_qcd	= (TH1D *)fin_nano_qcd->Get(((isMu) ? Form("MCQCDMu/%s/NonIso/%s",systType,histname_RegB.c_str()) : Form("MCQCDEle/%s/NonIso/%s",systType,histname_RegB.c_str())));  

  
  TH1D *hcf_RegC_data	= 0x0;
  if(SystType=="iso20")
    hcf_RegC_data = (TH1D *)fin_nano_data->Get(((isMu) ? Form("DataMu/%s/NonIsoLowMET/%s",systType,histname_RegC.c_str()) : Form("DataEle/%s/NonIsoLowMET/%s",systType,histname_RegC.c_str())));
  else
    hcf_RegC_data = (TH1D *)fin_nano_data->Get(((isMu) ? Form("DataMu/base/NonIsoLowMET/%s",histname_RegC.c_str()) : Form("DataEle/base/NonIsoLowMET/%s",histname_RegC.c_str())));
  //TH1D *hcf_RegC_data	= (TH1D *)fin_nano_data->Get(((isMu) ? Form("DataMu/base/NonIsoLowMET/%s",histname_RegC.c_str()) : Form("DataEle/base/NonIsoLowMET/%s",histname_RegC.c_str())));
  TH1D *hcf_RegC_sig = 0x0 ;
  if(year == 2016)
    hcf_RegC_sig	= (TH1D *)fin_nano_sig->Get(Form("HplusM120/%s/NonIsoLowMET/%s",systType,histname_RegC.c_str()));
  TH1D *hcf_RegC_ttbar	= (TH1D *)fin_nano_ttbar->Get(Form("TTbar/%s/NonIsoLowMET/%s",systType,histname_RegC.c_str()));
  TH1D *hcf_RegC_stop	= (TH1D *)fin_nano_stop->Get(Form("singleTop/%s/NonIsoLowMET/%s",systType,histname_RegC.c_str())); 
  TH1D *hcf_RegC_wjets	= (TH1D *)fin_nano_wjets->Get(Form("Wjets/%s/NonIsoLowMET/%s",systType,histname_RegC.c_str()));
  TH1D *hcf_RegC_dyjets	= (TH1D *)fin_nano_dyjets->Get(Form("DYjets/%s/NonIsoLowMET/%s",systType,histname_RegC.c_str()));
  TH1D *hcf_RegC_vbf	= (TH1D *)fin_nano_vbf->Get(Form("VBFusion/%s/NonIsoLowMET/%s",systType,histname_RegC.c_str()));
  TH1D *hcf_RegC_qcd	= (TH1D *)fin_nano_qcd->Get(((isMu) ? Form("MCQCDMu/%s/NonIsoLowMET/%s",systType,histname_RegC.c_str()) : Form("MCQCDEle/%s/NonIsoLowMET/%s",systType,histname_RegC.c_str()))); 


  TH1D *hcf_RegD_data	= 0x0;
  if(SystType=="iso20")
    hcf_RegD_data = (TH1D *)fin_nano_data->Get(((isMu) ? Form("DataMu/%s/LowMET/%s",systType,histname_RegD.c_str()) : Form("DataEle/%s/LowMET/%s",systType,histname_RegD.c_str())));
  else
    hcf_RegD_data = (TH1D *)fin_nano_data->Get(((isMu) ? Form("DataMu/base/LowMET/%s",histname_RegD.c_str()) : Form("DataEle/base/LowMET/%s",histname_RegD.c_str())));
  // TH1D *hcf_RegD_data	= (TH1D *)fin_nano_data->Get(((isMu) ? Form("DataMu/base/LowMET/%s",histname_RegD.c_str()) : Form("DataEle/base/LowMET/%s",histname_RegD.c_str())));
  TH1D *hcf_RegD_sig = 0x0 ;
  if(year == 2016)
    hcf_RegD_sig	= (TH1D *)fin_nano_sig->Get(Form("HplusM120/%s/LowMET/%s",systType,histname_RegD.c_str()));
  TH1D *hcf_RegD_ttbar	= (TH1D *)fin_nano_ttbar->Get(Form("TTbar/%s/LowMET/%s",systType,histname_RegD.c_str()));
  TH1D *hcf_RegD_stop	= (TH1D *)fin_nano_stop->Get(Form("singleTop/%s/LowMET/%s",systType,histname_RegD.c_str())); 
  TH1D *hcf_RegD_wjets	= (TH1D *)fin_nano_wjets->Get(Form("Wjets/%s/LowMET/%s",systType,histname_RegD.c_str()));
  TH1D *hcf_RegD_dyjets	= (TH1D *)fin_nano_dyjets->Get(Form("DYjets/%s/LowMET/%s",systType,histname_RegD.c_str()));
  TH1D *hcf_RegD_vbf	= (TH1D *)fin_nano_vbf->Get(Form("VBFusion/%s/LowMET/%s",systType,histname_RegD.c_str()));
  TH1D *hcf_RegD_qcd	= (TH1D *)fin_nano_qcd->Get(((isMu) ? Form("MCQCDMu/%s/LowMET/%s",systType,histname_RegD.c_str()) : Form("MCQCDEle/%s/LowMET/%s",systType,histname_RegD.c_str()))); 
  ////////////////////////////////End of getting the histograms from files //////////////////////////////// 
  
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
  // printf("systType : %10s, hist : %20s, Data(A,B,C,D) : (%5.4lf, %5.4lf, %5.4lf, %5.4lf), MC(A,B,C,D) : (%5.4lf, %5.4lf, %5.4lf, %5.4lf)\n",
  // 	 systType, histname.c_str(), hcf_RegA_data->Integral(),hcf_RegB_data->Integral(),hcf_RegB_data->Integral(),hcf_RegD_data->Integral(), 
  // 	 hcf_RegA_bkg->Integral(),hcf_RegB_bkg->Integral(),hcf_RegB_bkg->Integral(),hcf_RegD_bkg->Integral());
  /////////////////////////////////////////////////////////////////////////////////////////////////////////

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
  makeHistoPositive(hcf_RegA_QCD, false) ;
  /////////////////////////////////////////////////////////////////////////////////////////////////////////

  //////////////////////////////// Calculate the QCD SF ///////////////////////////////////////////////////
  double intDiffC   = hcf_RegC_QCD->Integral();
  double errDiffC   = getStatUnc(hcf_RegC_QCD, 0.0);
  double intDiffD   = hcf_RegD_QCD->Integral();
  double errDiffD   = getStatUnc(hcf_RegD_QCD, 0.0);
  //Ratio of (Data-MC) from RegionD and RegionC
  double SF = intDiffD/intDiffC;
  double tmpD = errDiffD/intDiffD;
  double tmpC = errDiffC/intDiffC;
  double SF_error = SF*sqrt(tmpD*tmpD + tmpC*tmpC);
  // printf("systType : %10s, intDiffC : %5.4lf +/- %5.4lf, , intDiffC : %5.4lf +/- %5.4lf, SF(%20s) : %5.4lf +/- %5.4lf\n",
  // 	 systType, intDiffC, errDiffC, intDiffD, errDiffD, histname.c_str(),SF,SF_error);
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
      hcf_RegA_QCD->SetBinError(ibin, new_bin_err);
    }
  hcf_RegA_bkg->Add(hcf_RegA_QCD);
  //cout<<"tot_bin_cont= "<<tot_bin_cont<<", tot_bin_err = "<<sqrt(tot_bin_err)<<endl;
  /////////////////////////////////////////////////////////////////////////////////////////////////////////
  d3->cd();
  hDD = (TH1D *)hcf_RegA_QCD->Clone(Form("%s",histname.c_str()));

  fin_nano_data->Close() ;   if(year == 2016) fin_nano_sig->Close() ;   fin_nano_ttbar->Close();   fin_nano_stop->Close();   
  fin_nano_wjets->Close();   fin_nano_dyjets->Close() ; fin_nano_vbf->Close();   fin_nano_qcd->Close();   

  delete fin_nano_data ;   if(year == 2016) delete fin_nano_sig ;   delete fin_nano_ttbar;   delete fin_nano_stop;   
  delete fin_nano_wjets;   delete fin_nano_dyjets ; delete fin_nano_vbf;   delete fin_nano_qcd;   
  
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
