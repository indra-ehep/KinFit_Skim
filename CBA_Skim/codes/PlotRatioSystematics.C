/**********************************************************************
 Created on : 03/11/2021
 Purpose    : Draw the ratio plots with systematics
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
#include <TGraphAsymmErrors.h>

#include <TRatioPlot.h>

#include <iostream>

using namespace std;

int PlotRatioSystematics(bool isBtag = 0, bool isMu = 1, int htype = 10){

  // Setters
  int SetGlobalStyle(void);
  int SetStatMarkerStyle(TGraphErrors *&, Color_t, Style_t, Size_t);
  int SetStatMarkerStyle(TH1F *&, Color_t, Style_t, Size_t);
  int SetStatMarkerStyle(TH1D *&, Color_t, Style_t, Size_t);
  int SetSysMarkerStyle(TGraphErrors *&, Color_t, Style_t);
  int SetCanvasStyle(TCanvas *&);
  int SetLegendStyle(TLegend *&);
  int PrintHSeparator(void);

  TPad *PlotRatio(THStack *hs, TH1D *h1, TH1D *h2, const char *cname, bool isLog);

  TGraphAsymmErrors *SystGraph(TH1F *hCentral,  vector<TH1D *> vSystUp, vector<TH1D *> vSystDown, bool isFullGraph = false, bool isRatioGraph = false);



  // ///////////////////////////////////////////////////////////////////////////////////////////  
  int year = 2016;
  float luminosity[3] = {35.9, 41.5, 59.7};

  // bool isMu = 1; // 1 muon, 0 ele
  // bool isBtag = 1 ; // 1 btag, 0 kinfit
  // int htype = 0 ; // 0:leppt, 1:jetpt, 2:metpt, 3:lepeta, 4:jeteta, 5:lepphi, 6:jetphi, 7:metphi, 8:njet, 9:nbjet, 10:mjj
    
  const char* cutflow = (isMu) ? "_cutflow_mu" : "_cutflow_ele";
  const char* cutflowUS = (isMu) ? "_cutflowUS_mu" : "_cutflowUS_ele";
  const char* leppt = (isMu) ? "_lb_pt_mu" : "_lb_pt_ele";
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
  
  cout << "Histname : " << histname << endl;
  
  string outputpdf = Form("figs/Week_Work_Report/2021-11-05/%d/MCQCD/hist%s.pdf",year,histname.c_str());
  //const char* dir = "grid_v31_Syst/CBA_Skim_Syst_MedID";
  //const char* dir = "grid_v32_Syst/CBA_Skim_Syst_jet_tightID";
  const char* dir = "grid_v35_Syst/CBA_Skim_Syst_jetsmeared";

  const char *basedir = "/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna";  
  const char* datafile = (isMu) ? Form("root_files/%s/%d/all_DataMu.root",dir,year) : Form("root_files/%s/%d/all_DataEle.root",dir,year) ;
  //const char* qcdfile = (isMu) ? Form("root_files/%s/%d/all_MCQCDMu.root",dir,year) : Form("root_files/%s/%d/all_MCQCDEle.root",dir,year) ;
  const char* qcdfile = Form("root_files/%s/%d/all_QCD_dd.root",dir,year);
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
  
  TH1D *hcf_nano_data	= (TH1D *)fin_nano_data->Get(((isMu) ? Form("DataMu/base/Iso/%s",histname.c_str()) : Form("DataEle/base/Iso/%s",histname.c_str())));
  TH1D *hcf_nano_sig = 0x0 ;
  if(year == 2016)
    hcf_nano_sig	= (TH1D *)fin_nano_sig->Get(Form("HplusM120/base/Iso/%s",histname.c_str()));
  TH1D *hcf_nano_ttbar	= (TH1D *)fin_nano_ttbar->Get(Form("TTbar/base/Iso/%s",histname.c_str()));
  TH1D *hcf_nano_stop	= (TH1D *)fin_nano_stop->Get(Form("singleTop/base/Iso/%s",histname.c_str())); 
  TH1D *hcf_nano_wjets	= (TH1D *)fin_nano_wjets->Get(Form("Wjets/base/Iso/%s",histname.c_str()));
  TH1D *hcf_nano_dyjets	= (TH1D *)fin_nano_dyjets->Get(Form("DYjets/base/Iso/%s",histname.c_str()));
  TH1D *hcf_nano_vbf	= (TH1D *)fin_nano_vbf->Get(Form("VBFusion/base/Iso/%s",histname.c_str()));
  //TH1D *hcf_nano_qcd	= (TH1D *)fin_nano_qcd->Get(((isMu) ? Form("MCQCDMu/base/Iso/%s",histname.c_str()) : Form("MCQCDEle/base/Iso/%s",histname.c_str())));
  TH1D *hcf_nano_qcd	= (TH1D *)fin_nano_qcd->Get(Form("QCDdd/base/Iso/%s",histname.c_str()));
  
  const char *syst[] = {"JES", "Pileup", "JER", "bcTag1", "bcTag2"};


  TH1D *hcf_nano_bkg = (TH1D *)hcf_nano_ttbar->Clone("Bkg");
  hcf_nano_bkg->Add(hcf_nano_stop);
  hcf_nano_bkg->Add(hcf_nano_wjets);
  hcf_nano_bkg->Add(hcf_nano_dyjets);
  hcf_nano_bkg->Add(hcf_nano_vbf);
  hcf_nano_bkg->Add(hcf_nano_qcd);

  hcf_nano_data->SetMarkerStyle(kFullCircle);
  hcf_nano_data->SetMarkerColor(kBlack);
  hcf_nano_data->SetMarkerSize(1.2);
  
  if(year == 2016){
    hcf_nano_sig->SetLineStyle(kDashed);
    hcf_nano_sig->SetLineColor(kRed);
    hcf_nano_sig->SetLineWidth(2);
  }

  hcf_nano_ttbar->SetFillColor(kCyan+1);
  
  hcf_nano_stop->SetFillColor(kViolet);

  hcf_nano_wjets->SetFillColor(kYellow+1);

  hcf_nano_dyjets->SetFillColor(kOrange+1);
  
  hcf_nano_vbf->SetFillColor(kGreen+2);

  hcf_nano_qcd->SetFillColor(kBlue);
  
  THStack *hs = new THStack("hs","");
  hs->Add(hcf_nano_vbf);
  hs->Add(hcf_nano_dyjets);
  hs->Add(hcf_nano_wjets);
  hs->Add(hcf_nano_qcd);
  hs->Add(hcf_nano_stop);
  hs->Add(hcf_nano_ttbar);


  TH1D *hData = (TH1D*)hcf_nano_data->Clone("hData"); 
  hData->SetTitle("");
  TH1D *hMC = (TH1D*)hcf_nano_bkg->Clone("hMC"); 
  ///////////////////////////////////////////////////////////////////////////////////////////  
  const char *hist_num_title = "Data";
  const char *hist_den_title = "All Bkg";

  const char *canvas_title = "NanoAOD vs MiniAOD"; //canvas and pad title
 
  string upper_pad_yaxis_title,upper_pad_xaxis_title,lower_pad_yaxis_title,lower_pad_xaxis_title;

  // 0:leppt, 1:jetpt, 2:metpt, 3:lepeta, 4:jeteta, 5:lepphi, 6:jetphi, 7:metphi, 8:njet, 9:nbjet, 10:mjj
  
  if(htype==0){
    if(isMu){
      upper_pad_yaxis_title = "Events / bin"; upper_pad_xaxis_title = "p_{T}^{#mu} (GeV)"; // upper pad axis titles
      lower_pad_yaxis_title = "#frac{Data}{Bkg}"; lower_pad_xaxis_title = "p_{T}^{#mu} (GeV)"; // lower pad axis titles
    }else{
      upper_pad_yaxis_title = "Events / bin"; upper_pad_xaxis_title = "p_{T}^{#it{e}} (GeV)"; // upper pad axis titles
      lower_pad_yaxis_title = "#frac{Data}{Bkg}"; lower_pad_xaxis_title = "p_{T}^{#it{e}} (GeV)"; // lower pad axis titles
    }
  }else if(htype==1){
    upper_pad_yaxis_title = "Events / bin"; upper_pad_xaxis_title = "p_{T}^{jets} (GeV)"; // upper pad axis titles
    lower_pad_yaxis_title = "#frac{Data}{Bkg}"; lower_pad_xaxis_title = "p_{T}^{jets} (GeV)"; // lower pad axis titles
  }else if(htype==2){
    upper_pad_yaxis_title = "Events / bin"; upper_pad_xaxis_title = "p_{T}^{miss} (GeV)"; // upper pad axis titles
    lower_pad_yaxis_title = "#frac{Data}{Bkg}"; lower_pad_xaxis_title = "p_{T}^{miss} (GeV)"; // lower pad axis titles
  }else if(htype==3){
    if(isMu){
      upper_pad_yaxis_title = "Events / bin"; upper_pad_xaxis_title = "#eta^{#mu}"; // upper pad axis titles
      lower_pad_yaxis_title = "#frac{Data}{Bkg}"; lower_pad_xaxis_title = "#eta^{#mu}"; // lower pad axis titles
    }else{
      upper_pad_yaxis_title = "Events / bin"; upper_pad_xaxis_title = "#eta^{#it{e}}"; // upper pad axis titles
      lower_pad_yaxis_title = "#frac{Data}{Bkg}"; lower_pad_xaxis_title = "#eta^{#it{e}}"; // lower pad axis titles
    }
  }else if(htype==4){
     upper_pad_yaxis_title = "Events / bin"; upper_pad_xaxis_title = "#eta^{jets}"; // upper pad axis titles
     lower_pad_yaxis_title = "#frac{Data}{Bkg}"; lower_pad_xaxis_title = "#eta^{jets}"; // lower pad axis titles
  }else if(htype==5){
    if(isMu){
      upper_pad_yaxis_title = "Events / bin"; upper_pad_xaxis_title = "#phi^{#mu}"; // upper pad axis titles
      lower_pad_yaxis_title = "#frac{Data}{Bkg}"; lower_pad_xaxis_title = "#phi^{#mu}"; // lower pad axis titles
    }else{
      upper_pad_yaxis_title = "Events / bin"; upper_pad_xaxis_title = "#phi^{#it{e}}"; // upper pad axis titles
      lower_pad_yaxis_title = "#frac{Data}{Bkg}"; lower_pad_xaxis_title = "#phi^{#it{e}}"; // lower pad axis titles
    }
  }else if(htype==6){
    upper_pad_yaxis_title = "Events / bin"; upper_pad_xaxis_title = "#phi^{jets}"; // upper pad axis titles
    lower_pad_yaxis_title = "#frac{Data}{Bkg}"; lower_pad_xaxis_title = "#phi^{jets}"; // lower pad axis titles
  }else if(htype==7){
    upper_pad_yaxis_title = "Events / bin"; upper_pad_xaxis_title = "#phi^{miss}"; // upper pad axis titles
    lower_pad_yaxis_title = "#frac{Data}{Bkg}"; lower_pad_xaxis_title = "#phi^{miss}"; // lower pad axis titles
  }else if(htype==8){
    upper_pad_yaxis_title = "Events / bin"; upper_pad_xaxis_title = "N^{jets}"; // upper pad axis titles
    lower_pad_yaxis_title = "#frac{Data}{Bkg}"; lower_pad_xaxis_title = "N^{jets}"; // lower pad axis titles
  }else if(htype==9){
    upper_pad_yaxis_title = "Events / bin"; upper_pad_xaxis_title = "N^{#it{b} jets}"; // upper pad axis titles
    lower_pad_yaxis_title = "#frac{Data}{Bkg}"; lower_pad_xaxis_title = "N^{#it{b} jets}"; // lower pad axis titles
  }else if(htype==10){
    upper_pad_yaxis_title = "Events / bin"; upper_pad_xaxis_title = "m_{jj} (GeV)"; // upper pad axis titles
    lower_pad_yaxis_title = "#frac{Data}{Bkg}"; lower_pad_xaxis_title = "m_{jj} (GeV)"; // lower pad axis titles
  }

  float upper_minY = 1.0e-1; float upper_maxY = 5.e7;  //y-axis range of upper pad
  //float upper_minY = 1.0e-1; float upper_maxY = 5.e12;  //y-axis range of upper pad
  float lower_minY = 0.5; float lower_maxY = 1.5;     //y-axis range of lower pad
  
  // 0:leppt, 1:jetpt, 2:metpt, 3:lepeta, 4:jeteta, 5:lepphi, 6:jetphi, 7:metphi, 8:njet, 9:nbjet, 10:mjj
  float upper_minX = 0.0; float upper_maxX = 500.0;
  if(htype>=0 and htype<=2){
    upper_minX = 0.0; upper_maxX = 500.0;   //x-axis range
  }else if(htype>=3 and htype<=7){
    upper_minX = -5.0; upper_maxX = 5.0;   //x-axis range
  }else if(htype==8){
    upper_minX = 0.0; upper_maxX = 16.0;   //x-axis range
  }else if(htype==9){
    upper_minX = 0.0; upper_maxX = 10.0;   //x-axis range
  }else if(htype==10){
    upper_minX = 0.0; upper_maxX = 200.0;   //x-axis range
  }

  float integral_min = upper_minX; float integral_max = upper_maxX; // for integral calculation
  //float integral_min = 4.0; float integral_max = upper_maxX; // for integral calculation

  //float legend_pos[4] = {0.5, 0.65, 0.88, 0.86};
  float legend_pos1[4] = {0.38, 0.70, 0.54, 0.86};
  float legend_pos2[4] = {0.55, 0.70, 0.71, 0.86};
  float legend_pos3[4] = {0.72, 0.70, 0.88, 0.86};
  ///////////////////////////////////////////////////////////////////////////////////////////  

  gStyle->SetOptStat(0);
  //Ranges
  hData->SetMaximum(upper_maxY);
  hData->SetMinimum(upper_minY);
  hData->GetXaxis()->SetRangeUser(upper_minX, upper_maxX);
  hMC->GetXaxis()->SetRangeUser(upper_minX, upper_maxX);
  //hData->GetXaxis()->SetRange(hData->FindBin(upper_minX), hData->FindBin(upper_maxX));
  //hMC->GetXaxis()->SetRange(upper_minX, upper_maxX);
  //axis Titles
  hData->GetXaxis()->SetTitle(upper_pad_xaxis_title.c_str());
  hData->GetYaxis()->SetTitle(upper_pad_yaxis_title.c_str());
  //Now add style and color
  SetStatMarkerStyle(hData, kBlack, kFullCircle, 1);
  SetStatMarkerStyle(hMC, kBlue, kFullSquare, 0.1);  
  
  float canvas_scale = 1;
  int canvas_width = TMath::Nint(canvas_scale*900) ;
  int canvas_height = TMath::Nint(canvas_scale*800) ;
  
  TPad *p = PlotRatio(hs, hData, hMC, "c1", true);
  
  TLegend *leg1 = p->BuildLegend();
  for(int i = 0 ; i < 10 ; i++)
    leg1->DeleteEntry() ;// This is to delete default title of hData
  leg1->AddEntry(hData, Form("%s",hist_num_title) ,"lp");
  leg1->AddEntry(hMC, Form("%s",hist_den_title) ,"lp");
  leg1->AddEntry(hcf_nano_ttbar, Form("#it{t}#bar{#it{t}}") ,"f");

  TLegend *leg2 = p->BuildLegend();
  for(int i = 0 ; i < 10 ; i++)
    leg2->DeleteEntry() ;// This is to delete default title of hData  
  leg2->AddEntry(hcf_nano_stop, Form("Single #it{t}") ,"f");
  leg2->AddEntry(hcf_nano_wjets, Form("#it{W} + jets") ,"f");
  leg2->AddEntry(hcf_nano_dyjets, Form("#it{Z}/#gamma + jets") ,"f");

  TLegend *leg3 = p->BuildLegend();
  for(int i = 0 ; i < 10 ; i++)
    leg3->DeleteEntry() ;// This is to delete default title of hData  
  leg3->AddEntry(hcf_nano_vbf, Form("VV") ,"f");
  leg3->AddEntry(hcf_nano_qcd, Form("QCD") ,"f");
  if(year == 2016)
    leg3->AddEntry(hcf_nano_sig, Form("m_{H^{+}} = 120 GeV") ,"l");

  leg1->SetX1(legend_pos1[0]); leg1->SetY1(legend_pos1[1]); 
  leg1->SetX2(legend_pos1[2]); leg1->SetY2(legend_pos1[3]); 

  leg2->SetX1(legend_pos2[0]); leg2->SetY1(legend_pos2[1]); 
  leg2->SetX2(legend_pos2[2]); leg2->SetY2(legend_pos2[3]); 

  leg3->SetX1(legend_pos3[0]); leg3->SetY1(legend_pos3[1]); 
  leg3->SetX2(legend_pos3[2]); leg3->SetY2(legend_pos3[3]); 

  SetLegendStyle(leg1);
  SetLegendStyle(leg2);
  SetLegendStyle(leg3);

  leg1->Draw();
  leg2->Draw();
  leg3->Draw();

  TPaveText *t1 = new TPaveText(0.60,0.91,0.90,0.98,"NDC");
  t1->SetFillStyle(0);
  t1->SetBorderSize(0);
  t1->SetTextFont(42);
  t1->SetTextSize(.05); 
  t1->SetMargin(0.1);
  t1->AddText(Form("%3.1f fb^{-1} (%d) (13 TeV)",luminosity[year%2016],year));
  t1->Draw();
  
  TPaveText *t2 = new TPaveText(0.08, 0.78, 0.36, 0.86,"NDC");
  t2->SetFillStyle(0);
  t2->SetBorderSize(0);
  t2->SetTextFont(42);
  t2->SetTextSize(.05); 
  t2->SetMargin(0.1);
  if(isBtag and isMu)
    t2->AddText("BTag: (#mu + jets)");
  if(isBtag and !isMu)
    t2->AddText("BTag: (#it{e} + jets)");
  if(!isBtag and isMu)
    t2->AddText("KinFit: (#mu + jets)");
  if(!isBtag and !isMu)
    t2->AddText("KinFit: (#it{e} + jets)");
  t2->Draw();


  return true;
}

TPad* PlotRatio(THStack *hs, TH1D *h1, TH1D *h2, const char *cname, bool isLog)
{

  TCanvas *canvas = (TCanvas *)gROOT->GetListOfCanvases()->FindObject(cname);
  TPad *pad1 = 0x0;

  if(!canvas){
    TCanvas *c = new TCanvas(cname, cname, 800, 800);
 
    // Upper plot will be in pad1
    pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
    pad1->SetBottomMargin(0.01); // Upper and lower plot are joined
    //pad1->SetGridx();         // Vertical grid
    if(isLog) pad1->SetLogy();
    pad1->Draw();             // Draw the upper pad: pad1
    pad1->cd();               // pad1 becomes the current pad
    pad1->SetTickx();
    pad1->SetTicky();
    h1->SetStats(0);          // No statistics on upper plot
    h1->Draw("e1p");               // Draw h1
    // h2->Draw("hist same");         // Draw h2 on top of h1
    hs->Draw("same hist");
    h1->Draw("e1p sames");               // Draw h1

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
 
    // lower plot will be in pad2
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
    // h3->SetMinimum(0.2);  // Define Y ..
    // h3->SetMaximum(1.8); // .. range
    // h3->SetMinimum(0.93);  // Define Y ..
    // h3->SetMaximum(1.07); // .. range
    // h3->SetMinimum(0.4);  // Define Y ..
    // h3->SetMaximum(1.6); // .. range
    // h3->SetMinimum(0.8);  // Define Y ..
    // h3->SetMaximum(1.2); // .. range
    h3->SetMinimum(0.5);  // Define Y ..
    h3->SetMaximum(1.5); // .. range
    h3->Sumw2();
    h3->SetStats(0);      // No statistics on lower plot
    h3->Divide(h2);
    //h3->SetMarkerStyle(21);
    h3->SetMarkerColor(kBlack);
    h3->SetFillColor(kRed);
    h3->Draw("e2");       // Draw the ratio plot
    h3->Draw("p sames");       // Draw the ratio plot
 
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
    h3->GetYaxis()->SetTitle("#frac{Data}{Bkg}");
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

    pad1 = (TPad *)canvas->GetListOfPrimitives()->FindObject("pad1") ;
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
    
    pad1->cd();
  }

  return pad1;
}

int PrintHSeparator(void){
  for (int i=0;i<130;i++) 
    printf("="); 
  cout << endl;
  return true;
}

int SetLegendStyle(TLegend *& leg)
{
  
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->SetTextFont(42);
  leg->SetTextSize(.04); 
  leg->SetMargin(0.1);
  leg->SetEntrySeparation(0.2);
  
  return true;
}

int SetCanvasStyle(TCanvas *& canvas)
{

  canvas->SetFillColor(0);
  canvas->SetBorderMode(0);
  canvas->SetBorderSize(2);
  canvas->SetLogy();
  canvas->SetTickx(1);
  canvas->SetTicky(1);
  canvas->SetLeftMargin(0.1178707);
  canvas->SetRightMargin(0.02471483);
  canvas->SetTopMargin(0.02941176);
  canvas->SetBottomMargin(0.1221719);
  canvas->SetFrameBorderMode(0);
  canvas->SetFrameBorderMode(0);

  // canvas->SetFillColor(0);
  // canvas->SetBorderMode(0);
  // canvas->SetBorderSize(2);
  // canvas->SetLeftMargin(0.10);
  // canvas->SetRightMargin(0.03);
  // canvas->SetTopMargin(0.03);
  // canvas->SetBottomMargin(0.12);
  // canvas->SetFrameBorderMode(0);
  // canvas->SetLogy();
  // canvas->SetTickx();
  // canvas->SetTicky();
  
  return 0;
}

int SetGlobalStyle(void)
{
  //----------------
  // // drawing options
  int font = 42;
	
  gStyle->SetOptStat(0);
  gROOT->SetStyle("Plain");
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetCanvasColor(kWhite);
  gStyle->SetFrameBorderMode(0);
  gStyle->SetFrameFillColor(kWhite);
  gStyle->SetPalette(1);
  gStyle->SetTextFont(font);
  gStyle->SetLabelFont(font,"x");
  gStyle->SetTitleFont(font,"x");
  gStyle->SetLabelFont(font,"y");
  gStyle->SetTitleFont(font,"y");
	
  if (1){ // extracted from pwg2 ref
    gStyle->SetFrameBorderMode(0);
    gStyle->SetFrameFillColor(0);
    gStyle->SetCanvasBorderMode(0);
    gStyle->SetPadBorderMode(0);
    gStyle->SetPadColor(10);
    gStyle->SetCanvasColor(10);
    gStyle->SetTitleFillColor(10);
    gStyle->SetTitleBorderSize(1);
    gStyle->SetStatColor(10);
    gStyle->SetStatBorderSize(1);
    gStyle->SetLegendBorderSize(1);
    //
    gStyle->SetDrawBorder(0);
    gStyle->SetTextFont(font);
    gStyle->SetStatFont(font);
    gStyle->SetStatFontSize(0.05);
    gStyle->SetStatX(0.97);
    gStyle->SetStatY(0.98);
    gStyle->SetStatH(0.03);
    gStyle->SetStatW(0.3);
    gStyle->SetTickLength(0.02,"y");
    gStyle->SetEndErrorSize(3);
    gStyle->SetLabelSize(0.042,"xyz");
    gStyle->SetLabelFont(font,"xyz");
    gStyle->SetLabelOffset(0.003,"xyz");
    gStyle->SetTitleFont(font,"xyz");
    gStyle->SetTitleOffset(1.35,"xyz");
    gStyle->SetTitleSize(0.042,"xyz");
    gStyle->SetMarkerSize(1);
    gStyle->SetPalette(1,0);
  }
  gROOT->ForceStyle();
  gStyle->SetEndErrorSize(0);

  // int font = 42;
  // gROOT->SetStyle("Plain");
  // gStyle->SetPalette(1); 
  // gStyle->SetFrameBorderMode(0);
  // gStyle->SetFrameFillColor(0);
  // gStyle->SetCanvasBorderMode(0);
  // gStyle->SetPadBorderMode(0);
  // gStyle->SetPadColor(10);
  // gStyle->SetCanvasColor(10);
  // gStyle->SetTitleFillColor(10);
  // gStyle->SetTitleBorderSize(1);
  // gStyle->SetStatColor(10);
  // gStyle->SetStatBorderSize(1);
  // gStyle->SetLegendBorderSize(1);
  // gStyle->SetDrawBorder(0);
  // gStyle->SetTextFont(font);
  // gStyle->SetStatFont(font);
  // gStyle->SetStatFontSize(0.05);
  // gStyle->SetStatX(0.97);
  // gStyle->SetStatY(0.98);
  // gStyle->SetStatH(0.03);
  // gStyle->SetStatW(0.3);
  // gStyle->SetPadTickX(1);
  // gStyle->SetPadTickY(1);
  // gStyle->SetTickLength(0.02,"y");
  // gStyle->SetEndErrorSize(3);
  // gStyle->SetLabelSize(0.05,"xyz");
  // gStyle->SetLabelFont(font,"xyz"); 
  // gStyle->SetLabelOffset(0.01,"xyz");
  // gStyle->SetTitleFont(font,"xyz");
  // gStyle->SetTitleOffset(1.2,"x"); 
  // gStyle->SetTitleOffset(1.2,"y");  
  // gStyle->SetTitleSize(0.05,"xyz");  
  // gStyle->SetMarkerSize(1.3); 
  // gStyle->SetPalette(1,0); 
  // gROOT->ForceStyle();
  // gStyle->SetOptStat(0);
  // gStyle->SetOptTitle(0);
  // gStyle->SetEndErrorSize(0);

  return 0;
}

int SetStatMarkerStyle(TGraphErrors*& grDataSt, Color_t color, Style_t style, Size_t markerSize)
{
  grDataSt->SetFillColor(1);
  grDataSt->SetLineColor(color);
  grDataSt->SetLineWidth(2);
  grDataSt->SetMarkerColor(color);
  grDataSt->SetMarkerStyle(style);
  grDataSt->SetMarkerSize(markerSize);

  return 0;
}

int SetSysMarkerStyle(TGraphErrors*& grDataSy, Color_t color, Style_t style)
{
  grDataSy->SetFillStyle(0);
  grDataSy->SetLineColor(color);
  grDataSy->SetLineWidth(2);
  grDataSy->SetMarkerColor(0);
  grDataSy->SetMarkerStyle(style);
  grDataSy->SetMarkerSize(2);


  return 0;
}


int SetStatMarkerStyle(TH1F*& h1, Color_t color, Style_t style, Size_t markerSize)
{
  h1->SetLineColor(color);
  h1->SetLineWidth(1);
  h1->SetMarkerColor(color);
  h1->SetMarkerStyle(style);
  h1->SetMarkerSize(markerSize);
  
  return true;
}

int SetStatMarkerStyle(TH1D*& h1, Color_t color, Style_t style, Size_t markerSize)
{
  h1->SetLineColor(color);
  h1->SetLineWidth(1);
  h1->SetMarkerColor(color);
  h1->SetMarkerStyle(style);
  h1->SetMarkerSize(markerSize);
  
  return true;
}

/////////////////////////////////////////////////////////////////////////////////////
double errBandUp(int iBin, TH1D *hCentral, vector<TH1D *> vSystUp){
  double errUp = 0.0;
  for(unsigned int isys = 0 ; isys < vSystUp.size() ; isys++){
    TH1D *hSyst = vSystUp.at(isys);
    errUp += pow((hSyst->GetBinContent(iBin+1) - hCentral->GetBinContent(iBin+1)),2) ;
  }
  errUp = sqrt(errUp);
  return errUp;
}

double errBandDown(int iBin, TH1D *hCentral, vector<TH1D *> vSystDown){
  double errDown = 0.0;
  for(unsigned int isys = 0 ; isys < vSystDown.size() ; isys++){
    TH1D *hSyst = vSystDown.at(isys);
    errDown += pow((hCentral->GetBinContent(iBin+1) - hSyst->GetBinContent(iBin+1)),2) ;
  }
  errDown = sqrt(errDown);
  return errDown;
}

TGraphAsymmErrors *SystGraph(TH1D *hCentral,  vector<TH1D *> vSystUp, vector<TH1D *> vSystDown, bool isFullGraph = false, bool isRatioGraph = false){
  
  TGraphAsymmErrors *gr;
  int n1 = hCentral->GetNbinsX(); 
  double *Yval, *errorU, *errorD, *XerrorU, *XerrorD, *Xval ;
  
  Yval = new double[n1]; errorU = new double[n1]; errorD = new double[n1];
  XerrorU=new double[n1]; XerrorD=new double[n1]; Xval=new double[n1];
  
  //cout << "No. of bins= " << n1 << endl;
  for(int i=0; i<n1; i++){
    if(isFullGraph){
      Yval[i]   = hCentral->GetBinContent(i+1);
      errorU[i] = errBandUp(i, hCentral, vSystUp); 
      errorD[i] = errBandDown(i, hCentral, vSystDown); 
    }
    if(isRatioGraph){
      Yval[i]   = 1;
      errorU[i] = errBandUp(i, hCentral, vSystUp); 
      errorD[i] = errBandDown(i, hCentral, vSystDown); 
      //cout<<"bin = "<<i<<endl;
      //cout<<Yval[i]<<"\t"<<errorU[i]<<"\t"<<hCentral->GetBinContent(i+1)<<endl;
      errorU[i] = errorU[i]/hCentral->GetBinContent(i+1);
      errorD[i] = errorD[i]/hCentral->GetBinContent(i+1);
      //cout<<Yval[i]<<"\t"<<errorU[i]<<"\t"<<hCentral->GetBinContent(i+1)<<endl;
    }
    Xval[i]   = hCentral->GetBinCenter(i+1);
    XerrorU[i]= hCentral->GetBinWidth(i+1)/2;
    XerrorD[i]= hCentral->GetBinWidth(i+1)/2;
  }
  
  gr = new TGraphAsymmErrors(n1, Xval, Yval, XerrorD, XerrorU, errorD, errorU);
  //delete [] Yval; delete [] errorU; delete [] errorD; delete [] XerrorU; delete [] XerrorD; delete [] Xval;

  return gr;
  
} 

/////////////////////////////////////////////////////////////////////////////////////
//// The following parts are taken from Ravindra's code

// double errBandUp(int iBin, TH1F *hCentral, TH1F *hJESPlus, TH1F *hJERPlus, TH1F *bTagPlus, TH1F *cTagPlus, TH1F* PileupPlus, TH1F *hQCD_dd, double qcd_sf_err){
//   double errUp = sqrt(pow(fabs(hJESPlus->GetBinContent(iBin+1) - hCentral->GetBinContent(iBin+1)),2) + 
// 		  pow(fabs(hJERPlus->GetBinContent(iBin+1) - hCentral->GetBinContent(iBin+1)),2) + 
// 		  pow(fabs(bTagPlus->GetBinContent(iBin+1) - hCentral->GetBinContent(iBin+1)),2) + 
// 		  pow(fabs(cTagPlus->GetBinContent(iBin+1) - hCentral->GetBinContent(iBin+1)),2) + 
// 		  pow(fabs(PileupPlus->GetBinContent(iBin+1) - hCentral->GetBinContent(iBin+1)),2) + 
// 		  pow(hCentral->GetBinError(iBin+1),2)+ pow(qcd_sf_err*hQCD_dd->GetBinContent(iBin+1),2));
//   return errUp;
// }

// double errBandDown(int iBin, TH1F *hCentral, TH1F *hJESMinus, TH1F *hJERMinus, TH1F *bTagMinus, TH1F *cTagMinus, TH1F* PileupMinus, TH1F *hQCD_dd, double qcd_sf_err){
//   double errDown =sqrt(pow(fabs(hCentral->GetBinContent(iBin+1) - hJESMinus->GetBinContent(iBin+1)),2) + 
// 		  pow(fabs(hCentral->GetBinContent(iBin+1) - hJERMinus->GetBinContent(iBin+1)),2) + 
// 		  pow(fabs(hCentral->GetBinContent(iBin+1) - bTagMinus->GetBinContent(iBin+1)),2) + 
// 		  pow(fabs(hCentral->GetBinContent(iBin+1) - cTagMinus->GetBinContent(iBin+1)),2) + 
// 		  pow(fabs(hCentral->GetBinContent(iBin+1) - PileupMinus->GetBinContent(iBin+1)),2) + 
// 		  pow(hCentral->GetBinError(iBin+1),2)+pow(qcd_sf_err*hQCD_dd->GetBinContent(iBin+1),2));
//   return errDown;
// }

// TGraphAsymmErrors *UNCGRAPH(TH1F *hCentral, TH1F *hJESPlus, TH1F *hJESMinus, TH1F *hJERPlus, TH1F *hJERMinus, TH1F *bTagPlus, TH1F *bTagMinus, TH1F *cTagPlus, TH1F *cTagMinus, TH1F* PileupPlus, TH1F* PileupMinus, TH1F* hQCD_dd, double qcd_sf_err, bool isFullGraph = false, bool isRatioGraph = false){
//   TGraphAsymmErrors *gr;
//   int n1 = hCentral->GetNbinsX(); 
//   double *Yval, *errorU, *errorD, *XerrorU, *XerrorD, *Xval ;
//   Yval = new double[n1]; errorU = new double[n1]; errorD = new double[n1];
//   XerrorU=new double[n1]; XerrorD=new double[n1]; Xval=new double[n1];
//   //cout << "No. of bins= " << n1 << endl;
//   for(int i=0; i<n1; i++){
//     if(isFullGraph){
//     Yval[i]   = hCentral->GetBinContent(i+1);
//     errorU[i] = errBandUp(i, hCentral, hJESPlus, hJERPlus, bTagPlus, cTagPlus, PileupPlus, hQCD_dd, qcd_sf_err); 
//     errorD[i] = errBandDown(i, hCentral, hJESMinus, hJERMinus, bTagMinus, cTagMinus, PileupMinus, hQCD_dd, qcd_sf_err); 
//     }
//     if(isRatioGraph){
//     Yval[i]   = 1;
//     errorU[i] = errBandUp(i, hCentral, hJESPlus, hJERPlus, bTagPlus, cTagPlus, PileupPlus, hQCD_dd, qcd_sf_err); 
//     errorD[i] = errBandDown(i, hCentral, hJESMinus, hJERMinus, bTagMinus, cTagMinus, PileupMinus, hQCD_dd, qcd_sf_err); 
//     //cout<<"bin = "<<i<<endl;
//     //cout<<Yval[i]<<"\t"<<errorU[i]<<"\t"<<hCentral->GetBinContent(i+1)<<endl;
//     errorU[i] = errorU[i]/hCentral->GetBinContent(i+1);
//     errorD[i] = errorD[i]/hCentral->GetBinContent(i+1);
//     //cout<<Yval[i]<<"\t"<<errorU[i]<<"\t"<<hCentral->GetBinContent(i+1)<<endl;
//     }
//     Xval[i]   = hCentral->GetBinCenter(i+1);
//     XerrorU[i]= hCentral->GetBinWidth(i+1)/2;
//     XerrorD[i]= hCentral->GetBinWidth(i+1)/2;
//   }
//   gr = new TGraphAsymmErrors(n1, Xval, Yval, XerrorD, XerrorU, errorD, errorU);
//   return gr;
//   delete [] Yval; delete [] errorU; delete [] errorD; delete [] XerrorU; delete [] XerrorD; delete [] Xval;
// } 

// TH1F* addHistoForUnc(TString dir, TString histname, TString sys, bool isDataDrivenQCD = false, double qcd_sf=1){
//   TH1F* hVV = getHisto(fVV, sys+"/Iso", dir, histname); 
//   TH1F* hDY = getHisto(fDY, sys+"/Iso", dir, histname); 
//   TH1F* hQCD_mc = getHisto(fQCD, sys+"/Iso", dir, histname); 
//   TH1F* hWJ = getHisto(fWJ, sys+"/Iso", dir, histname); 
//   TH1F* hST = getHisto(fST, sys+"/Iso", dir, histname); 
//   TH1F* hTT = getHisto(fTT, sys+"/Iso", dir, histname); 
//   TH1F* hAll = (TH1F*)hVV->Clone("hAllMC");
//   hAll->Add(hDY);
//   hAll->Add(hWJ);
//   hAll->Add(hST);
//   hAll->Add(hTT);
//   if(isDataDrivenQCD) hQCD_mc = getDataDrivenQCD(dir, histname, qcd_sf);
//   hAll->Add(hQCD_mc);
//   return hAll;
// }

//// The above parts are taken from Ravindra's code
