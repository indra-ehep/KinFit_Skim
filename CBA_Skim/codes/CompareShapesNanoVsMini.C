/**********************************************************************
 Created on : 10/11/2021
 Purpose    : Compare the shapes of Nano vs Mini AOD
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

int CompareShapesNanoVsMini()
{
  TPad* PlotRatio(TH1F *h1, TH1F *h2, const char *cname, bool isLog);

  TFile *fin_nanoexcl = TFile::Open("root_files/test/Shapes_hcs_13TeV_mu___kb_mjj_mu_WH80_exclusive.root");
  TH1F *hNanoexclData = (TH1F *)fin_nanoexcl->Get("data_obs");
  TH1F *hNanoexclTTbar = (TH1F *)fin_nanoexcl->Get("ttbar");
  TH1F *hNanoexclStop = (TH1F *)fin_nanoexcl->Get("stop");
  TH1F *hNanoexclWjet = (TH1F *)fin_nanoexcl->Get("wjet");
  TH1F *hNanoexclZjet = (TH1F *)fin_nanoexcl->Get("zjet");
  TH1F *hNanoexclVV = (TH1F *)fin_nanoexcl->Get("vv");
  TH1F *hNanoexclQCD = (TH1F *)fin_nanoexcl->Get("qcd");
  
  TH1F *hNanoexclMC = (TH1F *)hNanoexclTTbar->Clone("hMCNanoexcl");
  // hNanoexclMC->Add(hNanoexclStop);
  // hNanoexclMC->Add(hNanoexclWjet);
  // hNanoexclMC->Add(hNanoexclZjet);
  // hNanoexclMC->Add(hNanoexclVV);
  //hNanoexclMC->Add(hNanoexclQCD);

  TFile *fin_nanoincl = TFile::Open("root_files/test/Shapes_hcs_13TeV_mu___kb_mjj_mu_WH80_inclusive.root");
  TH1F *hNanoinclData = (TH1F *)fin_nanoincl->Get("data_obs");
  TH1F *hNanoinclTTbar = (TH1F *)fin_nanoincl->Get("ttbar");
  TH1F *hNanoinclStop = (TH1F *)fin_nanoincl->Get("stop");
  TH1F *hNanoinclWjet = (TH1F *)fin_nanoincl->Get("wjet");
  TH1F *hNanoinclZjet = (TH1F *)fin_nanoincl->Get("zjet");
  TH1F *hNanoinclVV = (TH1F *)fin_nanoincl->Get("vv");
  TH1F *hNanoinclQCD = (TH1F *)fin_nanoincl->Get("qcd");
  
  TH1F *hNanoinclMC = (TH1F *)hNanoinclTTbar->Clone("hMCNanoincl");
  // hNanoinclMC->Add(hNanoinclStop);
  // hNanoinclMC->Add(hNanoinclWjet);
  // hNanoinclMC->Add(hNanoinclZjet);
  // hNanoinclMC->Add(hNanoinclVV);
  //hNanoinclMC->Add(hNanoinclQCD);

  
  TFile *fin_mini = TFile::Open("/Data/CMS-Software/local/CMSSW_10_2_13/src/Analysis/limit/local/mu/Cat1_Inc/Mass80/Shapes_hcs_13TeV_mu_KinFit_mjj_kfit_WH80.root");
  TH1F *hMiniData = (TH1F *)fin_mini->Get("data_obs");
  TH1F *hMiniTTbar = (TH1F *)fin_mini->Get("ttbar");
  TH1F *hMiniStop = (TH1F *)fin_mini->Get("stop");
  TH1F *hMiniWjet = (TH1F *)fin_mini->Get("wjet");
  TH1F *hMiniZjet = (TH1F *)fin_mini->Get("zjet");
  TH1F *hMiniVV = (TH1F *)fin_mini->Get("vv");
  TH1F *hMiniQCD = (TH1F *)fin_mini->Get("qcd");
  
  TH1F *hMiniMC = (TH1F *)hMiniTTbar->Clone("hMCMini");
  // hMiniMC->Add(hMiniStop);
  // hMiniMC->Add(hMiniWjet);
  // hMiniMC->Add(hMiniZjet);
  // hMiniMC->Add(hMiniVV);
  //hMiniMC->Add(hMiniQCD);

  cout<<"hDataNano(Exl) Binwidth " << hNanoexclData->GetBinWidth(2) << ", Integral : " << hNanoexclData->Integral() <<endl;  
  cout<<"hDataNano(Inc) Binwidth " << hNanoinclData->GetBinWidth(2) << ", Integral : " << hNanoinclData->Integral() <<endl;  
  cout<<"hMiniNano Binwidth " << hMiniData->GetBinWidth(2) << ", Integral : " << hMiniData->Integral() <<endl;  

  // Mini Vs Nano comparison
  // TH1F *hDataRatio = (TH1F *)hMiniData->Clone("data ratio (M/N)");
  // hDataRatio->Sumw2();
  // hDataRatio->Divide(hNanoData);
  // hDataRatio->SetTitle("");
  
  // TH1F *hMCRatio = (TH1F *)hMiniMC->Clone("mc ratio (M/N)");
  // hMCRatio->Sumw2();
  // hMCRatio->Divide(hNanoMC);
  // hMCRatio->SetTitle("");
  
  // TH1F *hDataMCRatio = (TH1F *)hDataRatio->Clone("data ratio / mc ratio");
  // hDataMCRatio->Sumw2();
  // hDataMCRatio->Divide(hMCRatio);
  

  // TCanvas *c1 = new TCanvas("c1","c1");
  // hDataRatio->Draw();

  // TCanvas *c2 = new TCanvas("c2","c2");
  // hMCRatio->Draw();

  // TCanvas *c3 = new TCanvas("c3","c3");
  // hDataMCRatio->Draw();
  
  TH1F *hMiniRatio = (TH1F *)hMiniData->Clone("data/mc (Mini)");
  hMiniRatio->Divide(hMiniMC);
  hMiniRatio->SetTitle("");

  TH1F *hNanoexclRatio = (TH1F *)hNanoexclData->Clone("data/mc (Nanoexcl)");
  hNanoexclRatio->Divide(hNanoexclMC);
  hNanoexclRatio->SetTitle("");

  TH1F *hNanoinclRatio = (TH1F *)hNanoinclData->Clone("data/mc (Nanoincl)");
  hNanoinclRatio->Divide(hNanoinclMC);
  hNanoinclRatio->SetTitle("");
  
  hMiniRatio->SetLineColor(kRed);
  hNanoexclRatio->SetLineColor(kBlue);
  hNanoinclRatio->SetLineColor(kGreen);

  hMiniRatio->SetLineWidth(3);
  hNanoexclRatio->SetLineWidth(3);
  hNanoinclRatio->SetLineWidth(3);

  TCanvas *c1 = new TCanvas("c1","c1");
  hMiniRatio->Draw("hist");
  hNanoexclRatio->Draw("sames hist");
  hNanoinclRatio->Draw("sames hist");


  // PlotRatio(hNanoexclRatio, hMiniRatio, "c2", false);
  // PlotRatio(hNanoinclRatio, hMiniRatio, "c2", false);

  // PlotRatio( hMiniRatio, hNanoexclRatio, "c3", false);
  // PlotRatio( hMiniRatio, hNanoinclRatio, "c3", false);
  
  
  
  return true;
}

//TPad* PlotRatio(THStack *hs, TH1F *h1, TH1F *h2,TGraphAsymmErrors *syst, TGraphAsymmErrors *systRatio, const char *cname, bool isLog)
TPad* PlotRatio(TH1F *h1, TH1F *h2, const char *cname, bool isLog)
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
    //syst->SetFillColorAlpha(kRed,0.7);
    // h2->Draw("hist same");         // Draw h2 on top of h1
    //hs->Draw("same hist");
    //syst->Draw("e2 sames");
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
    TPad *pad2 = new TPad("pad2", "pad2", 0, 0.01, 1, 0.3);
    pad2->SetTopMargin(0.05);
    pad2->SetBottomMargin(0.2);
    //pad2->SetGridx(); // vertical grid
    pad2->SetGridy(); // vertical grid
    pad2->Draw();
    pad2->cd();       // pad2 becomes the current pad
    pad2->SetTickx();
    pad2->SetTicky();

    //pad2->Range(-61.81533,0.01758623,562.5978,1.572414);
    //pad2->SetFillColor(0);
    //pad2->SetBorderMode(0);
    //pad2->SetBorderSize(2);
    //pad2->SetGridy();
    //pad2->SetTickx(1);
    //pad2->SetTicky(1);
    pad2->SetTopMargin(0.004657352);
    pad2->SetBottomMargin(0.3102683);
    //pad2->SetFrameBorderMode(0);
    //pad2->SetFrameBorderMode(0);

 
    // Define the ratio plot
    TH1F *h3 = (TH1F*)h1->Clone("h3");
    h3->SetLineColor(h1->GetLineColor());
    h3->SetMinimum(0.2);  // Define Y ..
    h3->SetMaximum(1.8); // .. range
    // h3->SetMinimum(0.93);  // Define Y ..
    // h3->SetMaximum(1.07); // .. range
    // h3->SetMinimum(0.4);  // Define Y ..
    // h3->SetMaximum(1.6); // .. range
    // h3->SetMinimum(0.8);  // Define Y ..
    // h3->SetMaximum(1.2); // .. range
    // h3->SetMinimum(0.5);  // Define Y ..
    // h3->SetMaximum(1.5); // .. range
    h3->Sumw2();
    h3->SetStats(0);      // No statistics on lower plot
    h3->Divide(h2);
    //h3->SetMarkerStyle(21);
    h3->SetMarkerColor(kBlack);
    //h3->SetFillColor(kRed);
    h3->Draw("p");       // Draw the ratio plot
    //systRatio->SetFillColorAlpha(kRed-9,0.001);
    //systRatio->SetFillColorAlpha(kRed,0.7);
    //systRatio->Draw("e2 sames");
    h3->Draw("p sames");       // Draw the ratio plot
    // h1 settings
    //h1->SetLineColor(kBlue+1);
    //h1->SetLineWidth(2);
 
    // Y axis h1 plot settings
    //h1->GetYaxis()->SetTitle(Form("Entries / %1.0f GeV",h1->GetBinWidth(2)));
    h1->GetYaxis()->SetTitle("Entries / bin");
    h1->GetYaxis()->SetTitleSize(25);
    h1->GetYaxis()->SetTitleFont(43);
    h1->GetYaxis()->SetTitleOffset(1.55);
    h1->GetYaxis()->SetLabelSize(25);

    h1->GetXaxis()->SetTitleOffset(3.5);
    h1->GetXaxis()->SetLabelOffset(0.1);
 
    // h2 settings
    //h2->SetLineColor(kRed);
    //h2->SetLineWidth(2);
 
    // Ratio plot (h3) settings
    h3->SetTitle(""); // Remove the ratio title
 
    // Y axis ratio plot settings
    h3->GetYaxis()->SetTitle("#frac{ex or inc}{mini}");
    h3->GetYaxis()->SetNdivisions(505);
    h3->GetYaxis()->SetTitleSize(25);
    h3->GetYaxis()->SetTitleFont(43);
    h3->GetYaxis()->SetTitleOffset(1.3);
    h3->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    h3->GetYaxis()->SetLabelSize(25);
 
    // X axis ratio plot settings
    h3->GetXaxis()->SetTitle(h1->GetXaxis()->GetTitle());
    h3->GetXaxis()->SetTitleSize(25);
    h3->GetXaxis()->SetTitleFont(43);
    h3->GetXaxis()->SetTitleOffset(3.6);
    h3->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    h3->GetXaxis()->SetLabelSize(25);
    
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
