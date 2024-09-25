/**********************************************************************
 Created on : 24/09/2024
 Purpose    : KFDD plots
 Author     : Indranil Das
 Email      : indranil.das@cern.ch | indra.ehep@gmail.com
**********************************************************************/
#include <TROOT.h>
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

#include <iostream>

using namespace std;

int KFDDPlot(int year = 2016, bool isMu = 1)
{  

  const char* channel = (isMu) ? "mu" : "ele";
  const char* mjj_RegB = (isMu) ? "mjj_mu_RegB" : "mjj_ele_RegB";
  const char* mjj_RegB_met_up = (isMu) ? "mjj_mu_RegB_met_up" : "mjj_ele_RegB_met_up";
  const char* mjj_RegB_met_down = (isMu) ? "mjj_mu_RegB_met_down" : "mjj_ele_RegB_met_down";

  const char* mjj_RegA = (isMu) ? "mjj_mu_RegA" : "mjj_ele_RegA";
  const char* mjj_RegA_met_up = (isMu) ? "mjj_mu_RegA_met_up" : "mjj_ele_RegA_met_up";
  const char* mjj_RegA_met_down = (isMu) ? "mjj_mu_RegA_met_down" : "mjj_ele_RegA_met_down";

  const char* mjj_RegB_iso_up = (isMu) ? "mjj_mu_RegB_iso_up" : "mjj_ele_RegB_iso_up";
  const char* mjj_RegB_iso_down = (isMu) ? "mjj_mu_RegB_iso_down" : "mjj_ele_RegB_iso_down";

  const char* mjj_RegA_iso_up = (isMu) ? "mjj_mu_RegA_iso_up" : "mjj_ele_RegA_iso_up";
  const char* mjj_RegA_iso_down = (isMu) ? "mjj_mu_RegA_iso_down" : "mjj_ele_RegA_iso_down";

  const char* dir = "QCDRBI";

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

  void makeHistoPositive(TH1D *, bool);
  int PlotRatio(TH1D *h1, TH1D *h2, TH1D *h3, const char *cname);
  
  //////////////////////////////// Open files ////////////////////////////////////////////////
  const char* datafile = (isMu) ? Form("root_files/%s/%d/IsoMET_QCD_DataMu_%d.root",dir,year,year) : Form("root_files/%s/%d/IsoMET_QCD_DataEle_%d.root",dir,year,year) ;
  const char* qcdfile = (isMu) ? Form("root_files/%s/%d/IsoMET_QCD_MCQCDMu_%d.root",dir,year,year) : Form("root_files/%s/%d/IsoMET_QCD_MCQCDEle_%d.root",dir,year,year) ;
  TFile *fin_nano_data	= TFile::Open(datafile);
  TFile *fin_nano_ttbar = TFile::Open(Form("root_files/%s/%d/IsoMET_QCD_TTbar_%d.root",dir,year,year));
  TFile *fin_nano_stop	= TFile::Open(Form("root_files/%s/%d/IsoMET_QCD_singleTop_%d.root",dir,year,year));
  TFile *fin_nano_wjets	= TFile::Open(Form("root_files/%s/%d/IsoMET_QCD_Wjets_%d.root",dir,year,year));
  TFile *fin_nano_dyjets = TFile::Open(Form("root_files/%s/%d/IsoMET_QCD_DYjets_%d.root",dir,year,year));
  TFile *fin_nano_vbf	= TFile::Open(Form("root_files/%s/%d/IsoMET_QCD_VBFusion_%d.root",dir,year,year));
  TFile *fin_nano_ttw	= TFile::Open(Form("root_files/%s/%d/IsoMET_QCD_TTW_%d.root",dir,year,year));
  TFile *fin_nano_ttz	= TFile::Open(Form("root_files/%s/%d/IsoMET_QCD_TTZ_%d.root",dir,year,year));
  TFile *fin_nano_ttg	= TFile::Open(Form("root_files/%s/%d/IsoMET_QCD_TTG_%d.root",dir,year,year));
  TFile *fin_nano_tth	= TFile::Open(Form("root_files/%s/%d/IsoMET_QCD_TTH_%d.root",dir,year,year));
  TFile *fin_nano_qcd	= TFile::Open(qcdfile);
  /////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  //////////////////////////////// Get the histograms ////////////////////////////////////////////////
  TH1F *hmjj_RegB_data	= (TH1F *)fin_nano_data->Get(((isMu) ? Form("%s",mjj_RegB) : Form("%s",mjj_RegB)));
  TH1F *hmjj_RegB_ttbar	= (TH1F *)fin_nano_ttbar->Get(Form("%s",mjj_RegB));
  TH1F *hmjj_RegB_stop	= (TH1F *)fin_nano_stop->Get(Form("%s",mjj_RegB)); 
  TH1F *hmjj_RegB_wjets	= (TH1F *)fin_nano_wjets->Get(Form("%s",mjj_RegB));
  TH1F *hmjj_RegB_dyjets = (TH1F *)fin_nano_dyjets->Get(Form("%s",mjj_RegB));
  TH1F *hmjj_RegB_vbf	= (TH1F *)fin_nano_vbf->Get(Form("%s",mjj_RegB));
  TH1F *hmjj_RegB_ttw	= (TH1F *)fin_nano_ttw->Get(Form("%s",mjj_RegB));
  TH1F *hmjj_RegB_ttz	= (TH1F *)fin_nano_ttz->Get(Form("%s",mjj_RegB));
  TH1F *hmjj_RegB_ttg	= (TH1F *)fin_nano_ttg->Get(Form("%s",mjj_RegB));
  TH1F *hmjj_RegB_tth	= (TH1F *)fin_nano_tth->Get(Form("%s",mjj_RegB));
  TH1F *hmjj_RegB_qcd	= (TH1F *)fin_nano_qcd->Get(((isMu) ? Form("%s",mjj_RegB) : Form("%s",mjj_RegB)));

  TH1F *hmjj_RegB_met_up_data	= (TH1F *)fin_nano_data->Get(((isMu) ? Form("%s",mjj_RegB_met_up) : Form("%s",mjj_RegB_met_up)));
  TH1F *hmjj_RegB_met_up_ttbar	= (TH1F *)fin_nano_ttbar->Get(Form("%s",mjj_RegB_met_up));
  TH1F *hmjj_RegB_met_up_stop	= (TH1F *)fin_nano_stop->Get(Form("%s",mjj_RegB_met_up)); 
  TH1F *hmjj_RegB_met_up_wjets	= (TH1F *)fin_nano_wjets->Get(Form("%s",mjj_RegB_met_up));
  TH1F *hmjj_RegB_met_up_dyjets = (TH1F *)fin_nano_dyjets->Get(Form("%s",mjj_RegB_met_up));
  TH1F *hmjj_RegB_met_up_vbf	= (TH1F *)fin_nano_vbf->Get(Form("%s",mjj_RegB_met_up));
  TH1F *hmjj_RegB_met_up_ttw	= (TH1F *)fin_nano_ttw->Get(Form("%s",mjj_RegB_met_up));
  TH1F *hmjj_RegB_met_up_ttz	= (TH1F *)fin_nano_ttz->Get(Form("%s",mjj_RegB_met_up));
  TH1F *hmjj_RegB_met_up_ttg	= (TH1F *)fin_nano_ttg->Get(Form("%s",mjj_RegB_met_up));
  TH1F *hmjj_RegB_met_up_tth	= (TH1F *)fin_nano_tth->Get(Form("%s",mjj_RegB_met_up));
  TH1F *hmjj_RegB_met_up_qcd	= (TH1F *)fin_nano_qcd->Get(((isMu) ? Form("%s",mjj_RegB_met_up) : Form("%s",mjj_RegB_met_up)));

  TH1F *hmjj_RegB_met_down_data	= (TH1F *)fin_nano_data->Get(((isMu) ? Form("%s",mjj_RegB_met_down) : Form("%s",mjj_RegB_met_down)));
  TH1F *hmjj_RegB_met_down_ttbar	= (TH1F *)fin_nano_ttbar->Get(Form("%s",mjj_RegB_met_down));
  TH1F *hmjj_RegB_met_down_stop	= (TH1F *)fin_nano_stop->Get(Form("%s",mjj_RegB_met_down)); 
  TH1F *hmjj_RegB_met_down_wjets	= (TH1F *)fin_nano_wjets->Get(Form("%s",mjj_RegB_met_down));
  TH1F *hmjj_RegB_met_down_dyjets = (TH1F *)fin_nano_dyjets->Get(Form("%s",mjj_RegB_met_down));
  TH1F *hmjj_RegB_met_down_vbf	= (TH1F *)fin_nano_vbf->Get(Form("%s",mjj_RegB_met_down));
  TH1F *hmjj_RegB_met_down_ttw	= (TH1F *)fin_nano_ttw->Get(Form("%s",mjj_RegB_met_down));
  TH1F *hmjj_RegB_met_down_ttz	= (TH1F *)fin_nano_ttz->Get(Form("%s",mjj_RegB_met_down));
  TH1F *hmjj_RegB_met_down_ttg	= (TH1F *)fin_nano_ttg->Get(Form("%s",mjj_RegB_met_down));
  TH1F *hmjj_RegB_met_down_tth	= (TH1F *)fin_nano_tth->Get(Form("%s",mjj_RegB_met_down));
  TH1F *hmjj_RegB_met_down_qcd	= (TH1F *)fin_nano_qcd->Get(((isMu) ? Form("%s",mjj_RegB_met_down) : Form("%s",mjj_RegB_met_down)));

  TH1F *hmjj_RegA_data	= (TH1F *)fin_nano_data->Get(((isMu) ? Form("%s",mjj_RegA) : Form("%s",mjj_RegA)));
  TH1F *hmjj_RegA_ttbar	= (TH1F *)fin_nano_ttbar->Get(Form("%s",mjj_RegA));
  TH1F *hmjj_RegA_stop	= (TH1F *)fin_nano_stop->Get(Form("%s",mjj_RegA)); 
  TH1F *hmjj_RegA_wjets	= (TH1F *)fin_nano_wjets->Get(Form("%s",mjj_RegA));
  TH1F *hmjj_RegA_dyjets = (TH1F *)fin_nano_dyjets->Get(Form("%s",mjj_RegA));
  TH1F *hmjj_RegA_vbf	= (TH1F *)fin_nano_vbf->Get(Form("%s",mjj_RegA));
  TH1F *hmjj_RegA_ttw	= (TH1F *)fin_nano_ttw->Get(Form("%s",mjj_RegA));
  TH1F *hmjj_RegA_ttz	= (TH1F *)fin_nano_ttz->Get(Form("%s",mjj_RegA));
  TH1F *hmjj_RegA_ttg	= (TH1F *)fin_nano_ttg->Get(Form("%s",mjj_RegA));
  TH1F *hmjj_RegA_tth	= (TH1F *)fin_nano_tth->Get(Form("%s",mjj_RegA));
  TH1F *hmjj_RegA_qcd	= (TH1F *)fin_nano_qcd->Get(((isMu) ? Form("%s",mjj_RegA) : Form("%s",mjj_RegA)));

  TH1F *hmjj_RegA_met_up_data	= (TH1F *)fin_nano_data->Get(((isMu) ? Form("%s",mjj_RegA_met_up) : Form("%s",mjj_RegA_met_up)));
  TH1F *hmjj_RegA_met_up_ttbar	= (TH1F *)fin_nano_ttbar->Get(Form("%s",mjj_RegA_met_up));
  TH1F *hmjj_RegA_met_up_stop	= (TH1F *)fin_nano_stop->Get(Form("%s",mjj_RegA_met_up)); 
  TH1F *hmjj_RegA_met_up_wjets	= (TH1F *)fin_nano_wjets->Get(Form("%s",mjj_RegA_met_up));
  TH1F *hmjj_RegA_met_up_dyjets = (TH1F *)fin_nano_dyjets->Get(Form("%s",mjj_RegA_met_up));
  TH1F *hmjj_RegA_met_up_vbf	= (TH1F *)fin_nano_vbf->Get(Form("%s",mjj_RegA_met_up));
  TH1F *hmjj_RegA_met_up_ttw	= (TH1F *)fin_nano_ttw->Get(Form("%s",mjj_RegA_met_up));
  TH1F *hmjj_RegA_met_up_ttz	= (TH1F *)fin_nano_ttz->Get(Form("%s",mjj_RegA_met_up));
  TH1F *hmjj_RegA_met_up_ttg	= (TH1F *)fin_nano_ttg->Get(Form("%s",mjj_RegA_met_up));
  TH1F *hmjj_RegA_met_up_tth	= (TH1F *)fin_nano_tth->Get(Form("%s",mjj_RegA_met_up));
  TH1F *hmjj_RegA_met_up_qcd	= (TH1F *)fin_nano_qcd->Get(((isMu) ? Form("%s",mjj_RegA_met_up) : Form("%s",mjj_RegA_met_up)));

  TH1F *hmjj_RegA_met_down_data	= (TH1F *)fin_nano_data->Get(((isMu) ? Form("%s",mjj_RegA_met_down) : Form("%s",mjj_RegA_met_down)));
  TH1F *hmjj_RegA_met_down_ttbar	= (TH1F *)fin_nano_ttbar->Get(Form("%s",mjj_RegA_met_down));
  TH1F *hmjj_RegA_met_down_stop	= (TH1F *)fin_nano_stop->Get(Form("%s",mjj_RegA_met_down)); 
  TH1F *hmjj_RegA_met_down_wjets	= (TH1F *)fin_nano_wjets->Get(Form("%s",mjj_RegA_met_down));
  TH1F *hmjj_RegA_met_down_dyjets = (TH1F *)fin_nano_dyjets->Get(Form("%s",mjj_RegA_met_down));
  TH1F *hmjj_RegA_met_down_vbf	= (TH1F *)fin_nano_vbf->Get(Form("%s",mjj_RegA_met_down));
  TH1F *hmjj_RegA_met_down_ttw	= (TH1F *)fin_nano_ttw->Get(Form("%s",mjj_RegA_met_down));
  TH1F *hmjj_RegA_met_down_ttz	= (TH1F *)fin_nano_ttz->Get(Form("%s",mjj_RegA_met_down));
  TH1F *hmjj_RegA_met_down_ttg	= (TH1F *)fin_nano_ttg->Get(Form("%s",mjj_RegA_met_down));
  TH1F *hmjj_RegA_met_down_tth	= (TH1F *)fin_nano_tth->Get(Form("%s",mjj_RegA_met_down));
  TH1F *hmjj_RegA_met_down_qcd	= (TH1F *)fin_nano_qcd->Get(((isMu) ? Form("%s",mjj_RegA_met_down) : Form("%s",mjj_RegA_met_down)));

  TH1F *hmjj_RegB_iso_up_data	= (TH1F *)fin_nano_data->Get(((isMu) ? Form("%s",mjj_RegB_iso_up) : Form("%s",mjj_RegB_iso_up)));
  TH1F *hmjj_RegB_iso_up_ttbar	= (TH1F *)fin_nano_ttbar->Get(Form("%s",mjj_RegB_iso_up));
  TH1F *hmjj_RegB_iso_up_stop	= (TH1F *)fin_nano_stop->Get(Form("%s",mjj_RegB_iso_up)); 
  TH1F *hmjj_RegB_iso_up_wjets	= (TH1F *)fin_nano_wjets->Get(Form("%s",mjj_RegB_iso_up));
  TH1F *hmjj_RegB_iso_up_dyjets = (TH1F *)fin_nano_dyjets->Get(Form("%s",mjj_RegB_iso_up));
  TH1F *hmjj_RegB_iso_up_vbf	= (TH1F *)fin_nano_vbf->Get(Form("%s",mjj_RegB_iso_up));
  TH1F *hmjj_RegB_iso_up_ttw	= (TH1F *)fin_nano_ttw->Get(Form("%s",mjj_RegB_iso_up));
  TH1F *hmjj_RegB_iso_up_ttz	= (TH1F *)fin_nano_ttz->Get(Form("%s",mjj_RegB_iso_up));
  TH1F *hmjj_RegB_iso_up_ttg	= (TH1F *)fin_nano_ttg->Get(Form("%s",mjj_RegB_iso_up));
  TH1F *hmjj_RegB_iso_up_tth	= (TH1F *)fin_nano_tth->Get(Form("%s",mjj_RegB_iso_up));
  TH1F *hmjj_RegB_iso_up_qcd	= (TH1F *)fin_nano_qcd->Get(((isMu) ? Form("%s",mjj_RegB_iso_up) : Form("%s",mjj_RegB_iso_up)));

  TH1F *hmjj_RegB_iso_down_data	= (TH1F *)fin_nano_data->Get(((isMu) ? Form("%s",mjj_RegB_iso_down) : Form("%s",mjj_RegB_iso_down)));
  TH1F *hmjj_RegB_iso_down_ttbar	= (TH1F *)fin_nano_ttbar->Get(Form("%s",mjj_RegB_iso_down));
  TH1F *hmjj_RegB_iso_down_stop	= (TH1F *)fin_nano_stop->Get(Form("%s",mjj_RegB_iso_down)); 
  TH1F *hmjj_RegB_iso_down_wjets	= (TH1F *)fin_nano_wjets->Get(Form("%s",mjj_RegB_iso_down));
  TH1F *hmjj_RegB_iso_down_dyjets = (TH1F *)fin_nano_dyjets->Get(Form("%s",mjj_RegB_iso_down));
  TH1F *hmjj_RegB_iso_down_vbf	= (TH1F *)fin_nano_vbf->Get(Form("%s",mjj_RegB_iso_down));
  TH1F *hmjj_RegB_iso_down_ttw	= (TH1F *)fin_nano_ttw->Get(Form("%s",mjj_RegB_iso_down));
  TH1F *hmjj_RegB_iso_down_ttz	= (TH1F *)fin_nano_ttz->Get(Form("%s",mjj_RegB_iso_down));
  TH1F *hmjj_RegB_iso_down_ttg	= (TH1F *)fin_nano_ttg->Get(Form("%s",mjj_RegB_iso_down));
  TH1F *hmjj_RegB_iso_down_tth	= (TH1F *)fin_nano_tth->Get(Form("%s",mjj_RegB_iso_down));
  TH1F *hmjj_RegB_iso_down_qcd	= (TH1F *)fin_nano_qcd->Get(((isMu) ? Form("%s",mjj_RegB_iso_down) : Form("%s",mjj_RegB_iso_down)));

  TH1F *hmjj_RegA_iso_up_data	= (TH1F *)fin_nano_data->Get(((isMu) ? Form("%s",mjj_RegA_iso_up) : Form("%s",mjj_RegA_iso_up)));
  TH1F *hmjj_RegA_iso_up_ttbar	= (TH1F *)fin_nano_ttbar->Get(Form("%s",mjj_RegA_iso_up));
  TH1F *hmjj_RegA_iso_up_stop	= (TH1F *)fin_nano_stop->Get(Form("%s",mjj_RegA_iso_up)); 
  TH1F *hmjj_RegA_iso_up_wjets	= (TH1F *)fin_nano_wjets->Get(Form("%s",mjj_RegA_iso_up));
  TH1F *hmjj_RegA_iso_up_dyjets = (TH1F *)fin_nano_dyjets->Get(Form("%s",mjj_RegA_iso_up));
  TH1F *hmjj_RegA_iso_up_vbf	= (TH1F *)fin_nano_vbf->Get(Form("%s",mjj_RegA_iso_up));
  TH1F *hmjj_RegA_iso_up_ttw	= (TH1F *)fin_nano_ttw->Get(Form("%s",mjj_RegA_iso_up));
  TH1F *hmjj_RegA_iso_up_ttz	= (TH1F *)fin_nano_ttz->Get(Form("%s",mjj_RegA_iso_up));
  TH1F *hmjj_RegA_iso_up_ttg	= (TH1F *)fin_nano_ttg->Get(Form("%s",mjj_RegA_iso_up));
  TH1F *hmjj_RegA_iso_up_tth	= (TH1F *)fin_nano_tth->Get(Form("%s",mjj_RegA_iso_up));
  TH1F *hmjj_RegA_iso_up_qcd	= (TH1F *)fin_nano_qcd->Get(((isMu) ? Form("%s",mjj_RegA_iso_up) : Form("%s",mjj_RegA_iso_up)));

  TH1F *hmjj_RegA_iso_down_data	= (TH1F *)fin_nano_data->Get(((isMu) ? Form("%s",mjj_RegA_iso_down) : Form("%s",mjj_RegA_iso_down)));
  TH1F *hmjj_RegA_iso_down_ttbar	= (TH1F *)fin_nano_ttbar->Get(Form("%s",mjj_RegA_iso_down));
  TH1F *hmjj_RegA_iso_down_stop	= (TH1F *)fin_nano_stop->Get(Form("%s",mjj_RegA_iso_down)); 
  TH1F *hmjj_RegA_iso_down_wjets	= (TH1F *)fin_nano_wjets->Get(Form("%s",mjj_RegA_iso_down));
  TH1F *hmjj_RegA_iso_down_dyjets = (TH1F *)fin_nano_dyjets->Get(Form("%s",mjj_RegA_iso_down));
  TH1F *hmjj_RegA_iso_down_vbf	= (TH1F *)fin_nano_vbf->Get(Form("%s",mjj_RegA_iso_down));
  TH1F *hmjj_RegA_iso_down_ttw	= (TH1F *)fin_nano_ttw->Get(Form("%s",mjj_RegA_iso_down));
  TH1F *hmjj_RegA_iso_down_ttz	= (TH1F *)fin_nano_ttz->Get(Form("%s",mjj_RegA_iso_down));
  TH1F *hmjj_RegA_iso_down_ttg	= (TH1F *)fin_nano_ttg->Get(Form("%s",mjj_RegA_iso_down));
  TH1F *hmjj_RegA_iso_down_tth	= (TH1F *)fin_nano_tth->Get(Form("%s",mjj_RegA_iso_down));
  TH1F *hmjj_RegA_iso_down_qcd	= (TH1F *)fin_nano_qcd->Get(((isMu) ? Form("%s",mjj_RegA_iso_down) : Form("%s",mjj_RegA_iso_down)));


  /////////////////////////////////////////////////////////////////////////////////////////////////////////

  //////////////////////////////// Rebin histogram ////////////////////////////////////////////////
  int rebin = 5;
  hmjj_RegB_data->Rebin(rebin);
  hmjj_RegB_ttbar->Rebin(rebin);
  hmjj_RegB_ttg->Rebin(rebin);
  hmjj_RegB_tth->Rebin(rebin);
  hmjj_RegB_ttw->Rebin(rebin);
  hmjj_RegB_ttz->Rebin(rebin);
  hmjj_RegB_stop->Rebin(rebin);
  hmjj_RegB_wjets->Rebin(rebin);
  hmjj_RegB_dyjets->Rebin(rebin);
  hmjj_RegB_vbf->Rebin(rebin);
  hmjj_RegB_qcd->Rebin(rebin);

  hmjj_RegB_met_up_data->Rebin(rebin);
  hmjj_RegB_met_up_ttbar->Rebin(rebin);
  hmjj_RegB_met_up_ttg->Rebin(rebin);
  hmjj_RegB_met_up_tth->Rebin(rebin);
  hmjj_RegB_met_up_ttw->Rebin(rebin);
  hmjj_RegB_met_up_ttz->Rebin(rebin);
  hmjj_RegB_met_up_stop->Rebin(rebin);
  hmjj_RegB_met_up_wjets->Rebin(rebin);
  hmjj_RegB_met_up_dyjets->Rebin(rebin);
  hmjj_RegB_met_up_vbf->Rebin(rebin);
  hmjj_RegB_met_up_qcd->Rebin(rebin);

  hmjj_RegB_met_down_data->Rebin(rebin);
  hmjj_RegB_met_down_ttbar->Rebin(rebin);
  hmjj_RegB_met_down_ttg->Rebin(rebin);
  hmjj_RegB_met_down_tth->Rebin(rebin);
  hmjj_RegB_met_down_ttw->Rebin(rebin);
  hmjj_RegB_met_down_ttz->Rebin(rebin);
  hmjj_RegB_met_down_stop->Rebin(rebin);
  hmjj_RegB_met_down_wjets->Rebin(rebin);
  hmjj_RegB_met_down_dyjets->Rebin(rebin);
  hmjj_RegB_met_down_vbf->Rebin(rebin);
  hmjj_RegB_met_down_qcd->Rebin(rebin);
  
  hmjj_RegA_data->Rebin(rebin);
  hmjj_RegA_ttbar->Rebin(rebin);
  hmjj_RegA_ttg->Rebin(rebin);
  hmjj_RegA_tth->Rebin(rebin);
  hmjj_RegA_ttw->Rebin(rebin);
  hmjj_RegA_ttz->Rebin(rebin);
  hmjj_RegA_stop->Rebin(rebin);
  hmjj_RegA_wjets->Rebin(rebin);
  hmjj_RegA_dyjets->Rebin(rebin);
  hmjj_RegA_vbf->Rebin(rebin);
  hmjj_RegA_qcd->Rebin(rebin);

  hmjj_RegA_met_up_data->Rebin(rebin);
  hmjj_RegA_met_up_ttbar->Rebin(rebin);
  hmjj_RegA_met_up_ttg->Rebin(rebin);
  hmjj_RegA_met_up_tth->Rebin(rebin);
  hmjj_RegA_met_up_ttw->Rebin(rebin);
  hmjj_RegA_met_up_ttz->Rebin(rebin);
  hmjj_RegA_met_up_stop->Rebin(rebin);
  hmjj_RegA_met_up_wjets->Rebin(rebin);
  hmjj_RegA_met_up_dyjets->Rebin(rebin);
  hmjj_RegA_met_up_vbf->Rebin(rebin);
  hmjj_RegA_met_up_qcd->Rebin(rebin);

  hmjj_RegA_met_down_data->Rebin(rebin);
  hmjj_RegA_met_down_ttbar->Rebin(rebin);
  hmjj_RegA_met_down_ttg->Rebin(rebin);
  hmjj_RegA_met_down_tth->Rebin(rebin);
  hmjj_RegA_met_down_ttw->Rebin(rebin);
  hmjj_RegA_met_down_ttz->Rebin(rebin);
  hmjj_RegA_met_down_stop->Rebin(rebin);
  hmjj_RegA_met_down_wjets->Rebin(rebin);
  hmjj_RegA_met_down_dyjets->Rebin(rebin);
  hmjj_RegA_met_down_vbf->Rebin(rebin);
  hmjj_RegA_met_down_qcd->Rebin(rebin);

  hmjj_RegB_iso_up_data->Rebin(rebin);
  hmjj_RegB_iso_up_ttbar->Rebin(rebin);
  hmjj_RegB_iso_up_ttg->Rebin(rebin);
  hmjj_RegB_iso_up_tth->Rebin(rebin);
  hmjj_RegB_iso_up_ttw->Rebin(rebin);
  hmjj_RegB_iso_up_ttz->Rebin(rebin);
  hmjj_RegB_iso_up_stop->Rebin(rebin);
  hmjj_RegB_iso_up_wjets->Rebin(rebin);
  hmjj_RegB_iso_up_dyjets->Rebin(rebin);
  hmjj_RegB_iso_up_vbf->Rebin(rebin);
  hmjj_RegB_iso_up_qcd->Rebin(rebin);

  hmjj_RegB_iso_down_data->Rebin(rebin);
  hmjj_RegB_iso_down_ttbar->Rebin(rebin);
  hmjj_RegB_iso_down_ttg->Rebin(rebin);
  hmjj_RegB_iso_down_tth->Rebin(rebin);
  hmjj_RegB_iso_down_ttw->Rebin(rebin);
  hmjj_RegB_iso_down_ttz->Rebin(rebin);
  hmjj_RegB_iso_down_stop->Rebin(rebin);
  hmjj_RegB_iso_down_wjets->Rebin(rebin);
  hmjj_RegB_iso_down_dyjets->Rebin(rebin);
  hmjj_RegB_iso_down_vbf->Rebin(rebin);
  hmjj_RegB_iso_down_qcd->Rebin(rebin);

  hmjj_RegA_iso_up_data->Rebin(rebin);
  hmjj_RegA_iso_up_ttbar->Rebin(rebin);
  hmjj_RegA_iso_up_ttg->Rebin(rebin);
  hmjj_RegA_iso_up_tth->Rebin(rebin);
  hmjj_RegA_iso_up_ttw->Rebin(rebin);
  hmjj_RegA_iso_up_ttz->Rebin(rebin);
  hmjj_RegA_iso_up_stop->Rebin(rebin);
  hmjj_RegA_iso_up_wjets->Rebin(rebin);
  hmjj_RegA_iso_up_dyjets->Rebin(rebin);
  hmjj_RegA_iso_up_vbf->Rebin(rebin);
  hmjj_RegA_iso_up_qcd->Rebin(rebin);

  hmjj_RegA_iso_down_data->Rebin(rebin);
  hmjj_RegA_iso_down_ttbar->Rebin(rebin);
  hmjj_RegA_iso_down_ttg->Rebin(rebin);
  hmjj_RegA_iso_down_tth->Rebin(rebin);
  hmjj_RegA_iso_down_ttw->Rebin(rebin);
  hmjj_RegA_iso_down_ttz->Rebin(rebin);
  hmjj_RegA_iso_down_stop->Rebin(rebin);
  hmjj_RegA_iso_down_wjets->Rebin(rebin);
  hmjj_RegA_iso_down_dyjets->Rebin(rebin);
  hmjj_RegA_iso_down_vbf->Rebin(rebin);
  hmjj_RegA_iso_down_qcd->Rebin(rebin);
/////////////////////////////////////////////////////////////////////////////////////////////////////////

  //////////////////////////////// Add Backgrounds ////////////////////////////////////////////////
  TH1D *hmjj_RegB_bkg = (TH1D *)hmjj_RegB_ttbar->Clone("hmjj_RegB_bkg");
  hmjj_RegB_bkg->Add(hmjj_RegB_stop);
  hmjj_RegB_bkg->Add(hmjj_RegB_wjets);
  hmjj_RegB_bkg->Add(hmjj_RegB_dyjets);
  hmjj_RegB_bkg->Add(hmjj_RegB_vbf);
  hmjj_RegB_bkg->Add(hmjj_RegB_ttw);
  hmjj_RegB_bkg->Add(hmjj_RegB_ttz);
  hmjj_RegB_bkg->Add(hmjj_RegB_ttg);
  hmjj_RegB_bkg->Add(hmjj_RegB_tth);
  //hmjj_RegB_bkg->Add(hmjj_RegB_qcd);
  
  TH1D *hmjj_RegB_met_up_bkg = (TH1D *)hmjj_RegB_met_up_ttbar->Clone("hmjj_RegB_met_up_bkg");
  hmjj_RegB_met_up_bkg->Add(hmjj_RegB_met_up_stop);
  hmjj_RegB_met_up_bkg->Add(hmjj_RegB_met_up_wjets);
  hmjj_RegB_met_up_bkg->Add(hmjj_RegB_met_up_dyjets);
  hmjj_RegB_met_up_bkg->Add(hmjj_RegB_met_up_vbf);
  hmjj_RegB_met_up_bkg->Add(hmjj_RegB_met_up_ttw);
  hmjj_RegB_met_up_bkg->Add(hmjj_RegB_met_up_ttz);
  hmjj_RegB_met_up_bkg->Add(hmjj_RegB_met_up_ttg);
  hmjj_RegB_met_up_bkg->Add(hmjj_RegB_met_up_tth);

  TH1D *hmjj_RegB_met_down_bkg = (TH1D *)hmjj_RegB_met_down_ttbar->Clone("hmjj_RegB_met_down_bkg");
  hmjj_RegB_met_down_bkg->Add(hmjj_RegB_met_down_stop);
  hmjj_RegB_met_down_bkg->Add(hmjj_RegB_met_down_wjets);
  hmjj_RegB_met_down_bkg->Add(hmjj_RegB_met_down_dyjets);
  hmjj_RegB_met_down_bkg->Add(hmjj_RegB_met_down_vbf);
  hmjj_RegB_met_down_bkg->Add(hmjj_RegB_met_down_ttw);
  hmjj_RegB_met_down_bkg->Add(hmjj_RegB_met_down_ttz);
  hmjj_RegB_met_down_bkg->Add(hmjj_RegB_met_down_ttg);
  hmjj_RegB_met_down_bkg->Add(hmjj_RegB_met_down_tth);

  
  TH1D *hmjj_RegA_bkg = (TH1D *)hmjj_RegA_ttbar->Clone("hmjj_RegA_bkg");
  hmjj_RegA_bkg->Add(hmjj_RegA_stop);
  hmjj_RegA_bkg->Add(hmjj_RegA_wjets);
  hmjj_RegA_bkg->Add(hmjj_RegA_dyjets);
  hmjj_RegA_bkg->Add(hmjj_RegA_vbf);
  hmjj_RegA_bkg->Add(hmjj_RegA_ttw);
  hmjj_RegA_bkg->Add(hmjj_RegA_ttz);
  hmjj_RegA_bkg->Add(hmjj_RegA_ttg);
  hmjj_RegA_bkg->Add(hmjj_RegA_tth);
  //hmjj_RegA_bkg->Add(hmjj_RegA_qcd);
  
  TH1D *hmjj_RegA_met_up_bkg = (TH1D *)hmjj_RegA_met_up_ttbar->Clone("hmjj_RegA_met_up_bkg");
  hmjj_RegA_met_up_bkg->Add(hmjj_RegA_met_up_stop);
  hmjj_RegA_met_up_bkg->Add(hmjj_RegA_met_up_wjets);
  hmjj_RegA_met_up_bkg->Add(hmjj_RegA_met_up_dyjets);
  hmjj_RegA_met_up_bkg->Add(hmjj_RegA_met_up_vbf);
  hmjj_RegA_met_up_bkg->Add(hmjj_RegA_met_up_ttw);
  hmjj_RegA_met_up_bkg->Add(hmjj_RegA_met_up_ttz);
  hmjj_RegA_met_up_bkg->Add(hmjj_RegA_met_up_ttg);
  hmjj_RegA_met_up_bkg->Add(hmjj_RegA_met_up_tth);

  TH1D *hmjj_RegA_met_down_bkg = (TH1D *)hmjj_RegA_met_down_ttbar->Clone("hmjj_RegA_met_down_bkg");
  hmjj_RegA_met_down_bkg->Add(hmjj_RegA_met_down_stop);
  hmjj_RegA_met_down_bkg->Add(hmjj_RegA_met_down_wjets);
  hmjj_RegA_met_down_bkg->Add(hmjj_RegA_met_down_dyjets);
  hmjj_RegA_met_down_bkg->Add(hmjj_RegA_met_down_vbf);
  hmjj_RegA_met_down_bkg->Add(hmjj_RegA_met_down_ttw);
  hmjj_RegA_met_down_bkg->Add(hmjj_RegA_met_down_ttz);
  hmjj_RegA_met_down_bkg->Add(hmjj_RegA_met_down_ttg);
  hmjj_RegA_met_down_bkg->Add(hmjj_RegA_met_down_tth);

  TH1D *hmjj_RegB_iso_up_bkg = (TH1D *)hmjj_RegB_iso_up_ttbar->Clone("hmjj_RegB_iso_up_bkg");
  hmjj_RegB_iso_up_bkg->Add(hmjj_RegB_iso_up_stop);
  hmjj_RegB_iso_up_bkg->Add(hmjj_RegB_iso_up_wjets);
  hmjj_RegB_iso_up_bkg->Add(hmjj_RegB_iso_up_dyjets);
  hmjj_RegB_iso_up_bkg->Add(hmjj_RegB_iso_up_vbf);
  hmjj_RegB_iso_up_bkg->Add(hmjj_RegB_iso_up_ttw);
  hmjj_RegB_iso_up_bkg->Add(hmjj_RegB_iso_up_ttz);
  hmjj_RegB_iso_up_bkg->Add(hmjj_RegB_iso_up_ttg);
  hmjj_RegB_iso_up_bkg->Add(hmjj_RegB_iso_up_tth);

  TH1D *hmjj_RegB_iso_down_bkg = (TH1D *)hmjj_RegB_iso_down_ttbar->Clone("hmjj_RegB_iso_down_bkg");
  hmjj_RegB_iso_down_bkg->Add(hmjj_RegB_iso_down_stop);
  hmjj_RegB_iso_down_bkg->Add(hmjj_RegB_iso_down_wjets);
  hmjj_RegB_iso_down_bkg->Add(hmjj_RegB_iso_down_dyjets);
  hmjj_RegB_iso_down_bkg->Add(hmjj_RegB_iso_down_vbf);
  hmjj_RegB_iso_down_bkg->Add(hmjj_RegB_iso_down_ttw);
  hmjj_RegB_iso_down_bkg->Add(hmjj_RegB_iso_down_ttz);
  hmjj_RegB_iso_down_bkg->Add(hmjj_RegB_iso_down_ttg);
  hmjj_RegB_iso_down_bkg->Add(hmjj_RegB_iso_down_tth);
  
  TH1D *hmjj_RegA_iso_up_bkg = (TH1D *)hmjj_RegA_iso_up_ttbar->Clone("hmjj_RegA_iso_up_bkg");
  hmjj_RegA_iso_up_bkg->Add(hmjj_RegA_iso_up_stop);
  hmjj_RegA_iso_up_bkg->Add(hmjj_RegA_iso_up_wjets);
  hmjj_RegA_iso_up_bkg->Add(hmjj_RegA_iso_up_dyjets);
  hmjj_RegA_iso_up_bkg->Add(hmjj_RegA_iso_up_vbf);
  hmjj_RegA_iso_up_bkg->Add(hmjj_RegA_iso_up_ttw);
  hmjj_RegA_iso_up_bkg->Add(hmjj_RegA_iso_up_ttz);
  hmjj_RegA_iso_up_bkg->Add(hmjj_RegA_iso_up_ttg);
  hmjj_RegA_iso_up_bkg->Add(hmjj_RegA_iso_up_tth);

  TH1D *hmjj_RegA_iso_down_bkg = (TH1D *)hmjj_RegA_iso_down_ttbar->Clone("hmjj_RegA_iso_down_bkg");
  hmjj_RegA_iso_down_bkg->Add(hmjj_RegA_iso_down_stop);
  hmjj_RegA_iso_down_bkg->Add(hmjj_RegA_iso_down_wjets);
  hmjj_RegA_iso_down_bkg->Add(hmjj_RegA_iso_down_dyjets);
  hmjj_RegA_iso_down_bkg->Add(hmjj_RegA_iso_down_vbf);
  hmjj_RegA_iso_down_bkg->Add(hmjj_RegA_iso_down_ttw);
  hmjj_RegA_iso_down_bkg->Add(hmjj_RegA_iso_down_ttz);
  hmjj_RegA_iso_down_bkg->Add(hmjj_RegA_iso_down_ttg);
  hmjj_RegA_iso_down_bkg->Add(hmjj_RegA_iso_down_tth);
  /////////////////////////////////////////////////////////////////////////////////////////////////////////

  //////////////////////////////// Get the QCD for regions ////////////////////////////////////////////////
  TH1D *hmjj_RegB_QCD = (TH1D *)hmjj_RegB_data->Clone("hmjj_RegB_QCD");
  hmjj_RegB_QCD->Add(hmjj_RegB_bkg, -1);
  makeHistoPositive(hmjj_RegB_QCD, false) ;

  TH1D *hmjj_RegB_met_up_QCD = (TH1D *)hmjj_RegB_met_up_data->Clone("hmjj_RegB_met_up_QCD");
  hmjj_RegB_met_up_QCD->Add(hmjj_RegB_met_up_bkg, -1);
  makeHistoPositive(hmjj_RegB_met_up_QCD, false) ;

  TH1D *hmjj_RegB_met_down_QCD = (TH1D *)hmjj_RegB_met_down_data->Clone("hmjj_RegB_met_down_QCD");
  hmjj_RegB_met_down_QCD->Add(hmjj_RegB_met_down_bkg, -1);
  makeHistoPositive(hmjj_RegB_met_down_QCD, false) ;

  TH1D *hmjj_RegA_QCD = (TH1D *)hmjj_RegA_data->Clone("hmjj_RegA_QCD");
  hmjj_RegA_QCD->Add(hmjj_RegA_bkg, -1);
  makeHistoPositive(hmjj_RegA_QCD, false) ;

  TH1D *hmjj_RegA_met_up_QCD = (TH1D *)hmjj_RegA_met_up_data->Clone("hmjj_RegA_met_up_QCD");
  hmjj_RegA_met_up_QCD->Add(hmjj_RegA_met_up_bkg, -1);
  makeHistoPositive(hmjj_RegA_met_up_QCD, false) ;

  TH1D *hmjj_RegA_met_down_QCD = (TH1D *)hmjj_RegA_met_down_data->Clone("hmjj_RegA_met_down_QCD");
  hmjj_RegA_met_down_QCD->Add(hmjj_RegA_met_down_bkg, -1);
  makeHistoPositive(hmjj_RegA_met_down_QCD, false) ;

  //////// iso ////////
  TH1D *hmjj_RegB_iso_up_QCD = (TH1D *)hmjj_RegB_iso_up_data->Clone("hmjj_RegB_iso_up_QCD");
  hmjj_RegB_iso_up_QCD->Add(hmjj_RegB_iso_up_bkg, -1);
  makeHistoPositive(hmjj_RegB_iso_up_QCD, false) ;

  TH1D *hmjj_RegB_iso_down_QCD = (TH1D *)hmjj_RegB_iso_down_data->Clone("hmjj_RegB_iso_down_QCD");
  hmjj_RegB_iso_down_QCD->Add(hmjj_RegB_iso_down_bkg, -1);
  makeHistoPositive(hmjj_RegB_iso_down_QCD, false) ;

  TH1D *hmjj_RegA_iso_up_QCD = (TH1D *)hmjj_RegA_iso_up_data->Clone("hmjj_RegA_iso_up_QCD");
  hmjj_RegA_iso_up_QCD->Add(hmjj_RegA_iso_up_bkg, -1);
  makeHistoPositive(hmjj_RegA_iso_up_QCD, false) ;

  TH1D *hmjj_RegA_iso_down_QCD = (TH1D *)hmjj_RegA_iso_down_data->Clone("hmjj_RegA_iso_down_QCD");
  hmjj_RegA_iso_down_QCD->Add(hmjj_RegA_iso_down_bkg, -1);
  makeHistoPositive(hmjj_RegA_iso_down_QCD, false) ;
/////////////////////////////////////////////////////////////////////////////////////////////////////////

  
  //////////////////////////////// Stack plot for checking ////////////////////////////////////////////////
  hmjj_RegA_data->SetMarkerStyle(kFullCircle);
  hmjj_RegA_data->SetMarkerColor(kBlack);
  hmjj_RegA_data->SetMarkerSize(1.2);
  
  hmjj_RegA_vbf->SetFillColor(kGreen+2);
  hmjj_RegA_ttw->SetFillColor(kOrange+1);
  hmjj_RegA_tth->SetFillColor(kGray);
  hmjj_RegA_ttz->SetFillColor(kMagenta);
  hmjj_RegA_dyjets->SetFillColor(kSpring+2);
  hmjj_RegA_ttg->SetFillColor(kYellow+1);
  hmjj_RegA_wjets->SetFillColor(kAzure);
  hmjj_RegA_qcd->SetFillColor(kMagenta-9);
  hmjj_RegA_stop->SetFillColor(kYellow-8);
  hmjj_RegA_ttbar->SetFillColor(kCyan+1);

  THStack *hs = new THStack("hs","");
  hs->Add(hmjj_RegA_vbf);
  hs->Add(hmjj_RegA_dyjets);
  hs->Add(hmjj_RegA_wjets);
  //  hs->Add(hmjj_RegA_qcd);
  hs->Add(hmjj_RegA_stop);
  hs->Add(hmjj_RegA_ttw);
  hs->Add(hmjj_RegA_ttz);
  hs->Add(hmjj_RegA_ttg);
  hs->Add(hmjj_RegA_tth);
  hs->Add(hmjj_RegA_ttbar);
  

  hmjj_RegA_data->SetTitle(((isMu)? Form("%d : #mu + jets (#it{L}_{int} = %3.1f fb^{-1})",year,totLumi):Form("%d : #it{e} + jets (#it{L}_{int} = %3.1f fb^{-1})",year,totLumi)));
  
  TLegend *leg1 = new TLegend(0.6962751,0.5611814,0.8925501,0.8924051);
  leg1->SetFillColor(10);
  leg1->AddEntry(hmjj_RegA_data, Form("Data") ,"lp");
  leg1->AddEntry(hmjj_RegA_ttbar, Form("#it{t}#bar{#it{t}}") ,"f");
  leg1->AddEntry(hmjj_RegA_ttg, Form("#it{t}#bar{#it{t}}#it{g}") ,"f");
  leg1->AddEntry(hmjj_RegA_tth, Form("#it{t}#bar{#it{t}}#it{h}") ,"f");
  leg1->AddEntry(hmjj_RegA_ttw, Form("#it{t}#bar{#it{t}}#it{w}") ,"f");
  leg1->AddEntry(hmjj_RegA_ttz, Form("#it{t}#bar{#it{t}}#it{z}") ,"f");
  leg1->AddEntry(hmjj_RegA_stop, Form("Single #it{t}") ,"f");
  leg1->AddEntry(hmjj_RegA_wjets, Form("#it{W} + jets") ,"f");
  leg1->AddEntry(hmjj_RegA_dyjets, Form("#it{Z}/#gamma + jets") ,"f");
  leg1->AddEntry(hmjj_RegA_vbf, Form("VV") ,"f");
  leg1->AddEntry(hmjj_RegA_qcd, Form("QCD") ,"f");
  
  
  hmjj_RegA_data->SetMinimum(1.0e-1);
  hmjj_RegA_data->SetMaximum(1.0e6);
  //hmjj_RegA_data->SetMaximum(1.0e12);
  //hmjj_RegA_data->SetMaximum(1.0e9);
  
  string outname = (isMu) ? Form("figs/temp/mjj_%d_mu.pdf",year) : Form("figs/temp/mjj_%d_ele.pdf",year) ;
  TCanvas *c1 = new TCanvas("c1","c1");
  gStyle->SetOptStat(0);
  //gStyle->SetOptTitle(0);
  c1->SetLogy();
  c1->SetTickx();
  c1->SetTicky();
  hmjj_RegA_data->Draw("e1p");
  hs->Draw("same hist");
  hmjj_RegA_data->Draw("e1p same");
  leg1->Draw();
  c1->Update();
  c1->SaveAs(outname.c_str());
  /////////////////////////////////////////////////////////////////////////////////////////////////////////

  //////////////////////////////// Plot up/down ratio MET RegB ////////////////////////////////////////////////
  bool isShape = true;
  if(isShape){
    hmjj_RegB_met_up_QCD->Scale(hmjj_RegB_QCD->Integral()/hmjj_RegB_met_up_QCD->Integral());
    hmjj_RegB_met_down_QCD->Scale(hmjj_RegB_QCD->Integral()/hmjj_RegB_met_down_QCD->Integral());
    std::cout << "Using shape comparison " << std::endl;
  }

  Double_t error_frac_RegB = max(fabs(hmjj_RegB_met_up_QCD->Integral() - hmjj_RegB_QCD->Integral()), fabs(hmjj_RegB_QCD->Integral() - hmjj_RegB_met_down_QCD->Integral()))/hmjj_RegB_QCD->Integral();
  TH1D *hRelErr_RegB_met_up = (TH1D *)hmjj_RegB_QCD->Clone("hRelErr_RegB_met_up");
  TH1D *hRelErr_RegB_met_down = (TH1D *)hmjj_RegB_QCD->Clone("hRelErr_RegB_met_down");
  for(int ibin=1; ibin<hRelErr_RegB_met_up->GetNbinsX(); ibin++){
    //cout<<"ibin : "<<ibin<<", Error Frac : "<<error_frac_RegB<<endl;
    hRelErr_RegB_met_up->SetBinContent(ibin, 1+error_frac_RegB);
    hRelErr_RegB_met_up->SetBinError(ibin, 0.1*error_frac_RegB);
    hRelErr_RegB_met_down->SetBinContent(ibin, 1.-error_frac_RegB);
    hRelErr_RegB_met_down->SetBinError(ibin, 0.1*error_frac_RegB);
  }
  hRelErr_RegB_met_up->SetTitle(Form("Max. Unc. %5.3lf",(1+error_frac_RegB)));

  hmjj_RegB_QCD->SetLineColor(kRed);
  hmjj_RegB_met_up_QCD->SetLineColor(kBlue);
  hmjj_RegB_met_down_QCD->SetLineColor(kGreen+1);
  hRelErr_RegB_met_up->SetLineColor(kMagenta);
  hRelErr_RegB_met_down->SetLineColor(kMagenta);
    
  hmjj_RegB_QCD->SetLineWidth(2);
  hmjj_RegB_met_up_QCD->SetLineWidth(2);
  hmjj_RegB_met_down_QCD->SetLineWidth(2);
  hRelErr_RegB_met_up->SetLineWidth(2);
  hRelErr_RegB_met_down->SetLineWidth(2);

  TLegend *leg2 = new TLegend(0.6729323,0.803838,0.9974937,0.9957356);
  leg2->SetFillColor(10);
  leg2->SetHeader(Form("Data-knownMC : %s (%d)",hmjj_RegB_QCD->GetName(),year));
  leg2->AddEntry(hmjj_RegB_met_up_QCD, Form("%s",hmjj_RegB_met_up_QCD->GetName()) ,"lfp");
  leg2->AddEntry(hmjj_RegB_QCD, Form("%s",hmjj_RegB_QCD->GetName()) ,"lfp");
  leg2->AddEntry(hmjj_RegB_met_down_QCD, Form("%s",hmjj_RegB_met_down_QCD->GetName()) ,"lfp");

  hmjj_RegB_met_up_QCD->SetMaximum(2.0*hmjj_RegB_met_up_QCD->GetBinContent(hmjj_RegB_met_up_QCD->FindBin(80.0)));
  hmjj_RegB_met_up_QCD->SetTitle("");
  hmjj_RegB_met_up_QCD->GetXaxis()->SetRangeUser(0.,170.);
  PlotRatio(hmjj_RegB_met_up_QCD, hmjj_RegB_QCD, hRelErr_RegB_met_up, "c2");
  PlotRatio(hmjj_RegB_met_down_QCD, hmjj_RegB_QCD, hRelErr_RegB_met_down, "c2");
  leg2->Draw();

  TCanvas *c2 = (TCanvas *)gROOT->GetListOfCanvases()->FindObject("c2");
  string s = hmjj_RegB_met_down_QCD->GetName();
  string systname = s.substr(0,s.find("down"));
  c2->SaveAs(Form("figs/temp/%s%s_%d.pdf",systname.c_str(),channel,year));

  c2->SaveAs("output.pdf");
  /////////////////////////////////////////////////////////////////////////////////////////////////////////

  //////////////////////////////// Plot up/down ratio MET RegA ////////////////////////////////////////////////
  //bool isShape = true;
  if(isShape){
    hmjj_RegA_met_up_QCD->Scale(hmjj_RegA_QCD->Integral()/hmjj_RegA_met_up_QCD->Integral());
    hmjj_RegA_met_down_QCD->Scale(hmjj_RegA_QCD->Integral()/hmjj_RegA_met_down_QCD->Integral());
    std::cout << "Using shape comparison " << std::endl;
  }

  Double_t error_frac_RegA = max(fabs(hmjj_RegA_met_up_QCD->Integral() - hmjj_RegA_QCD->Integral()), fabs(hmjj_RegA_QCD->Integral() - hmjj_RegA_met_down_QCD->Integral()))/hmjj_RegA_QCD->Integral();
  TH1D *hRelErr_RegA_met_up = (TH1D *)hmjj_RegA_QCD->Clone("hRelErr_RegA_met_up");
  TH1D *hRelErr_RegA_met_down = (TH1D *)hmjj_RegA_QCD->Clone("hRelErr_RegA_met_down");
  for(int ibin=1; ibin<hRelErr_RegA_met_up->GetNbinsX(); ibin++){
    //cout<<"ibin : "<<ibin<<", Error Frac : "<<error_frac_RegA<<endl;
    hRelErr_RegA_met_up->SetBinContent(ibin, 1+error_frac_RegA);
    hRelErr_RegA_met_up->SetBinError(ibin, 0.1*error_frac_RegA);
    hRelErr_RegA_met_down->SetBinContent(ibin, 1.-error_frac_RegA);
    hRelErr_RegA_met_down->SetBinError(ibin, 0.1*error_frac_RegA);
  }
  hRelErr_RegA_met_up->SetTitle(Form("Max. Unc. %5.3lf",(1+error_frac_RegA)));

  hmjj_RegA_QCD->SetLineColor(kRed);
  hmjj_RegA_met_up_QCD->SetLineColor(kBlue);
  hmjj_RegA_met_down_QCD->SetLineColor(kGreen+1);
  hRelErr_RegA_met_up->SetLineColor(kMagenta);
  hRelErr_RegA_met_down->SetLineColor(kMagenta);
    
  hmjj_RegA_QCD->SetLineWidth(2);
  hmjj_RegA_met_up_QCD->SetLineWidth(2);
  hmjj_RegA_met_down_QCD->SetLineWidth(2);
  hRelErr_RegA_met_up->SetLineWidth(2);
  hRelErr_RegA_met_down->SetLineWidth(2);

  TLegend *leg3 = new TLegend(0.6729323,0.803838,0.9974937,0.9957356);
  leg3->SetFillColor(10);
  leg3->SetHeader(Form("Data-knownMC : %s (%d)",hmjj_RegA_QCD->GetName(),year));
  leg3->AddEntry(hmjj_RegA_met_up_QCD, Form("%s",hmjj_RegA_met_up_QCD->GetName()) ,"lfp");
  leg3->AddEntry(hmjj_RegA_QCD, Form("%s",hmjj_RegA_QCD->GetName()) ,"lfp");
  leg3->AddEntry(hmjj_RegA_met_down_QCD, Form("%s",hmjj_RegA_met_down_QCD->GetName()) ,"lfp");

  //hmjj_RegA_met_up_QCD->SetMaximum(2.0*hmjj_RegA_met_up_QCD->GetBinContent(hmjj_RegA_met_up_QCD->FindBin(80.0)));
  hmjj_RegA_met_up_QCD->SetMinimum(0.0);
  hmjj_RegA_met_up_QCD->SetTitle("");
  hmjj_RegA_met_up_QCD->GetXaxis()->SetRangeUser(0.,170.);
  PlotRatio(hmjj_RegA_met_up_QCD, hmjj_RegA_QCD, hRelErr_RegA_met_up, "c3");
  PlotRatio(hmjj_RegA_met_down_QCD, hmjj_RegA_QCD, hRelErr_RegA_met_down, "c3");
  leg3->Draw();

  TCanvas *c3 = (TCanvas *)gROOT->GetListOfCanvases()->FindObject("c3");
  s = hmjj_RegA_met_down_QCD->GetName();
  systname = s.substr(0,s.find("down"));
  c3->SaveAs(Form("figs/temp/%s%s_%d.pdf",systname.c_str(),channel,year));

  c3->SaveAs("output.pdf");
  /////////////////////////////////////////////////////////////////////////////////////////////////////////

  //////////////////////////////// Plot up/down ratio Iso RegB ////////////////////////////////////////////////
  //isShape = true;
  if(isShape){
    hmjj_RegB_iso_up_QCD->Scale(hmjj_RegB_QCD->Integral()/hmjj_RegB_iso_up_QCD->Integral());
    hmjj_RegB_iso_down_QCD->Scale(hmjj_RegB_QCD->Integral()/hmjj_RegB_iso_down_QCD->Integral());
    std::cout << "Using shape comparison " << std::endl;
  }

  error_frac_RegB = max(fabs(hmjj_RegB_iso_up_QCD->Integral() - hmjj_RegB_QCD->Integral()), fabs(hmjj_RegB_QCD->Integral() - hmjj_RegB_iso_down_QCD->Integral()))/hmjj_RegB_QCD->Integral();
  TH1D *hRelErr_RegB_iso_up = (TH1D *)hmjj_RegB_QCD->Clone("hRelErr_RegB_iso_up");
  TH1D *hRelErr_RegB_iso_down = (TH1D *)hmjj_RegB_QCD->Clone("hRelErr_RegB_iso_down");
  for(int ibin=1; ibin<hRelErr_RegB_iso_up->GetNbinsX(); ibin++){
    //cout<<"ibin : "<<ibin<<", Error Frac : "<<error_frac_RegB<<endl;
    hRelErr_RegB_iso_up->SetBinContent(ibin, 1+error_frac_RegB);
    hRelErr_RegB_iso_up->SetBinError(ibin, 0.1*error_frac_RegB);
    hRelErr_RegB_iso_down->SetBinContent(ibin, 1.-error_frac_RegB);
    hRelErr_RegB_iso_down->SetBinError(ibin, 0.1*error_frac_RegB);
  }
  hRelErr_RegB_iso_up->SetTitle(Form("Max. Unc. %5.3lf",(1+error_frac_RegB)));

  hmjj_RegB_QCD->SetLineColor(kRed);
  hmjj_RegB_iso_up_QCD->SetLineColor(kBlue);
  hmjj_RegB_iso_down_QCD->SetLineColor(kGreen+1);
  hRelErr_RegB_iso_up->SetLineColor(kMagenta);
  hRelErr_RegB_iso_down->SetLineColor(kMagenta);
    
  hmjj_RegB_QCD->SetLineWidth(2);
  hmjj_RegB_iso_up_QCD->SetLineWidth(2);
  hmjj_RegB_iso_down_QCD->SetLineWidth(2);
  hRelErr_RegB_iso_up->SetLineWidth(2);
  hRelErr_RegB_iso_down->SetLineWidth(2);

  TLegend *leg4 = new TLegend(0.6729323,0.803838,0.9974937,0.9957356);
  leg4->SetFillColor(10);
  leg4->SetHeader(Form("Data-knownMC : %s (%d)",hmjj_RegB_QCD->GetName(),year));
  leg4->AddEntry(hmjj_RegB_iso_up_QCD, Form("%s",hmjj_RegB_iso_up_QCD->GetName()) ,"lfp");
  leg4->AddEntry(hmjj_RegB_QCD, Form("%s",hmjj_RegB_QCD->GetName()) ,"lfp");
  leg4->AddEntry(hmjj_RegB_iso_down_QCD, Form("%s",hmjj_RegB_iso_down_QCD->GetName()) ,"lfp");

  hmjj_RegB_iso_up_QCD->SetMaximum(2.0*hmjj_RegB_iso_up_QCD->GetBinContent(hmjj_RegB_iso_up_QCD->FindBin(80.0)));
  hmjj_RegB_iso_up_QCD->SetTitle("");
  hmjj_RegB_iso_up_QCD->GetXaxis()->SetRangeUser(0.,170.);
  PlotRatio(hmjj_RegB_iso_up_QCD, hmjj_RegB_QCD, hRelErr_RegB_iso_up, "c4");
  PlotRatio(hmjj_RegB_iso_down_QCD, hmjj_RegB_QCD, hRelErr_RegB_iso_down, "c4");
  leg4->Draw();

  TCanvas *c4 = (TCanvas *)gROOT->GetListOfCanvases()->FindObject("c4");
  s = hmjj_RegB_iso_down_QCD->GetName();
  systname = s.substr(0,s.find("down"));
  c4->SaveAs(Form("figs/temp/%s%s_%d.pdf",systname.c_str(),channel,year));

  c4->SaveAs("output.pdf");
  /////////////////////////////////////////////////////////////////////////////////////////////////////////

  //////////////////////////////// Plot up/down ratio Iso RegA ////////////////////////////////////////////////
  //bool isShape = true;
  if(isShape){
    hmjj_RegA_iso_up_QCD->Scale(hmjj_RegA_QCD->Integral()/hmjj_RegA_iso_up_QCD->Integral());
    hmjj_RegA_iso_down_QCD->Scale(hmjj_RegA_QCD->Integral()/hmjj_RegA_iso_down_QCD->Integral());
    std::cout << "Using shape comparison " << std::endl;
  }

  error_frac_RegA = max(fabs(hmjj_RegA_iso_up_QCD->Integral() - hmjj_RegA_QCD->Integral()), fabs(hmjj_RegA_QCD->Integral() - hmjj_RegA_iso_down_QCD->Integral()))/hmjj_RegA_QCD->Integral();
  TH1D *hRelErr_RegA_iso_up = (TH1D *)hmjj_RegA_QCD->Clone("hRelErr_RegA_iso_up");
  TH1D *hRelErr_RegA_iso_down = (TH1D *)hmjj_RegA_QCD->Clone("hRelErr_RegA_iso_down");
  for(int ibin=1; ibin<hRelErr_RegA_iso_up->GetNbinsX(); ibin++){
    //cout<<"ibin : "<<ibin<<", Error Frac : "<<error_frac_RegA<<endl;
    hRelErr_RegA_iso_up->SetBinContent(ibin, 1+error_frac_RegA);
    hRelErr_RegA_iso_up->SetBinError(ibin, 0.1*error_frac_RegA);
    hRelErr_RegA_iso_down->SetBinContent(ibin, 1.-error_frac_RegA);
    hRelErr_RegA_iso_down->SetBinError(ibin, 0.1*error_frac_RegA);
  }
  hRelErr_RegA_iso_up->SetTitle(Form("Max. Unc. %5.3lf",(1+error_frac_RegA)));

  hmjj_RegA_QCD->SetLineColor(kRed);
  hmjj_RegA_iso_up_QCD->SetLineColor(kBlue);
  hmjj_RegA_iso_down_QCD->SetLineColor(kGreen+1);
  hRelErr_RegA_iso_up->SetLineColor(kMagenta);
  hRelErr_RegA_iso_down->SetLineColor(kMagenta);
    
  hmjj_RegA_QCD->SetLineWidth(2);
  hmjj_RegA_iso_up_QCD->SetLineWidth(2);
  hmjj_RegA_iso_down_QCD->SetLineWidth(2);
  hRelErr_RegA_iso_up->SetLineWidth(2);
  hRelErr_RegA_iso_down->SetLineWidth(2);

  TLegend *leg5 = new TLegend(0.6729323,0.803838,0.9974937,0.9957356);
  leg5->SetFillColor(10);
  leg5->SetHeader(Form("Data-knownMC : %s (%d)",hmjj_RegA_QCD->GetName(),year));
  leg5->AddEntry(hmjj_RegA_iso_up_QCD, Form("%s",hmjj_RegA_iso_up_QCD->GetName()) ,"lfp");
  leg5->AddEntry(hmjj_RegA_QCD, Form("%s",hmjj_RegA_QCD->GetName()) ,"lfp");
  leg5->AddEntry(hmjj_RegA_iso_down_QCD, Form("%s",hmjj_RegA_iso_down_QCD->GetName()) ,"lfp");

  //hmjj_RegA_iso_up_QCD->SetMaximum(2.0*hmjj_RegA_iso_up_QCD->GetBinContent(hmjj_RegA_iso_up_QCD->FindBin(80.0)));
  hmjj_RegA_iso_up_QCD->SetMinimum(0.0);
  hmjj_RegA_iso_up_QCD->SetTitle("");
  hmjj_RegA_iso_up_QCD->GetXaxis()->SetRangeUser(0.,170.);
  PlotRatio(hmjj_RegA_iso_up_QCD, hmjj_RegA_QCD, hRelErr_RegA_iso_up, "c5");
  PlotRatio(hmjj_RegA_iso_down_QCD, hmjj_RegA_QCD, hRelErr_RegA_iso_down, "c5");
  leg5->Draw();

  TCanvas *c5 = (TCanvas *)gROOT->GetListOfCanvases()->FindObject("c5");
  s = hmjj_RegA_iso_down_QCD->GetName();
  systname = s.substr(0,s.find("down"));
  c5->SaveAs(Form("figs/temp/%s%s_%d.pdf",systname.c_str(),channel,year));

  c5->SaveAs("output.pdf");
  /////////////////////////////////////////////////////////////////////////////////////////////////////////

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


int PlotRatio(TH1D *h1, TH1D *h2, TH1D *hAvgErr, const char *cname)
{
  //cout<<"h1 name : "<<h1->GetName() <<", Directory : " << h1->GetDirectory()->GetMotherDir()->GetName() << endl;

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
    h1->SetStats(0);          // No statistics on upper plot
    h1->Draw("hist");               // Draw h1
    h2->Draw("hist same");         // Draw h2 on top of h1
 
#if ROOT_VERSION_CODE >= ROOT_VERSION(6,8,0)
    // Avoid the first label (0) to be clipped.
    TAxis *axis = h1->GetYaxis();
    axis->ChangeLabel(1, -1, -1, -1, -1, -1, " ");
    axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    axis->SetLabelSize(15);
#else
    // Do not draw the Y axis label on the upper plot and redraw a small
    // axis instead, in order to avoid the first label (0) to be clipped.
    h1->GetYaxis()->SetLabelSize(0.);
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
    //pad2->SetGridx(); // vertical grid
    pad2->SetGridy(); // vertical grid
    pad2->Draw();
    pad2->cd();       // pad2 becomes the current pad
    pad2->SetTickx();
    pad2->SetTicky();
 
    // Define the ratio plot
    TH1F *h3 = (TH1F*)h1->Clone("h3");
    h3->SetLineColor(h1->GetLineColor());

    h3->Sumw2();
    h3->SetStats(0);      // No statistics on lower plot
    h3->Divide(h2);
    
    h3->SetMinimum(0.5);  // Define Y ..
    h3->SetMaximum(1.5); // .. range
    
    // cout << "h3->GetBinContent(h3->FindBin(80.0))" << h3->GetBinContent(h3->FindBin(80.0)) << endl;
    // h3->SetMaximum(1+2*(h3->GetBinContent(h3->FindBin(80.0))-1.));
    // h3->SetMinimum(1-2*(h3->GetBinContent(h3->FindBin(80.0))-1.));

    // float minX = 20.;
    // float maxX = 165.;
    // int minbinX = h3->FindBin(minX);
    // int maxbinX = h3->FindBin(maxX);
    // double integral = h3->Integral(minbinX,maxbinX);
    // //double avgBinContent = integral/double(maxbinX-minbinX);
    // //double avgBinContent = integral/double(maxX-minX);
    // //cout << "integral : " << integral << ", (Avg bin - 1) :  " << TMath::Abs(avgBinContent-1) << endl;
    // // double maxZoom = TMath::Abs(avgBinContent-1)<0.08 ? TMath::Abs(avgBinContent-1) : 0.2/1.2 ;
    // // cout << "maxZoom " << maxZoom << endl;
    // // cout << "Max:Min " << (1+1.2*maxZoom) << " : " << (1-1.2*maxZoom) << endl;
    // // h3->SetMaximum(1+1.2*maxZoom);
    // // h3->SetMinimum(1-1.2*maxZoom);

    // int maxBin = 0;
    // double maxDiff = -1.;
    // cout<<" h3->GetNbinsX() : " << h3->GetNbinsX() << endl;
    // for (Int_t i=int(minX); i<=int(maxX); ++i) {
    //   int bin = h3->FindBin(i);
    //   if (TMath::Abs(h3->GetBinContent(bin)-1)>=maxDiff) {
    // 	maxDiff = TMath::Abs(h3->GetBinContent(bin)-1);
    // 	maxBin  = bin;
    //   }
    // }
    // cout << "h3->GetBinContent(maxBin) : " << h3->GetBinContent(maxBin) << ", maxDiff : " << maxDiff << ", bincenter : " << h3->GetXaxis()->GetBinCenter(maxBin) << endl;
    // h3->SetMaximum(1+1.2*maxDiff);
    // h3->SetMinimum(1-1.2*maxDiff);
    
    //h3->SetMarkerStyle(21);
    h3->Draw("ep");       // Draw the ratio plot
    //hAvgErr->Draw("ep same");
    
    // h1 settings
    //h1->SetLineColor(kBlue+1);
    //h1->SetLineWidth(2);
 
    // Y axis h1 plot settings
    h1->GetYaxis()->SetTitle(Form("Entries / %1.0f GeV",h1->GetBinWidth(2)));
    h1->GetYaxis()->SetTitleSize(20);
    h1->GetYaxis()->SetTitleFont(43);
    h1->GetYaxis()->SetTitleOffset(1.55);
 
    // h2 settings
    //h2->SetLineColor(kRed);
    //h2->SetLineWidth(2);
 
    // Ratio plot (h3) settings
    h3->SetTitle(""); // Remove the ratio title
 
    // Y axis ratio plot settings
    h3->GetYaxis()->SetTitle("#frac{unc}{nominal}");
    h3->GetYaxis()->SetNdivisions(505);
    h3->GetYaxis()->SetTitleSize(20);
    h3->GetYaxis()->SetTitleFont(43);
    h3->GetYaxis()->SetTitleOffset(1.55);
    h3->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    h3->GetYaxis()->SetLabelSize(15);
 
    // X axis ratio plot settings
    h3->GetXaxis()->SetTitle("m_{jj} (GeV)");
    h3->GetXaxis()->SetTitleSize(20);
    h3->GetXaxis()->SetTitleFont(43);
    h3->GetXaxis()->SetTitleOffset(3.2);
    h3->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    h3->GetXaxis()->SetLabelSize(15);
    
    pad1->cd();

    cout<<" nof canvas primitives " << c->GetListOfPrimitives()->GetEntries() << endl ;
    
  }else {

    TPad *pad1 = (TPad *)canvas->GetListOfPrimitives()->FindObject("pad1") ;
    pad1->cd();
    
    h1->Draw("hist same");             
    h2->Draw("hist same");         
    
    TPad *pad2 = (TPad *)canvas->GetListOfPrimitives()->FindObject("pad2") ;
    pad2->cd();
    

    TH1F *h3 = (TH1F*)h1->Clone("h3");
    h3->SetLineColor(h1->GetLineColor());
    h3->Sumw2();
    h3->SetStats(0);      // No statistics on lower plot
    h3->Divide(h2);
    h3->Draw("ep same");       // Draw the ratio plot
    //hAvgErr->Draw("ep same");
    pad1->cd();
  }

  return true;
}
