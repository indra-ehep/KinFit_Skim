/**********************************************************************
 Created on : 06/10/2024
 Purpose    : Validate and symmetize up down plots of higgs combine
 Author     : Indranil Das, Research Associate, Imperial
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
#include "TF1.h"
#include "TPaveText.h"
#include "TStyle.h"
#include "TArrow.h"

using namespace std;

int symmetrize(string infile = "local/ele/Cat1_Inc/Mass80/Shapes_hcs_13TeV_ele___ct_ExcL_mjj_ele_WH80_2016.root")
{
  int PlotRatio(TH1F *h1, TH1F *h2, TH1F*& h3, const char *cname);
  
  //string infile = "local/mu_ele/Cat1_Inc/Mass80/Shapes_hcs_13TeV_mu___kb_mjj_mu_WH80_2016.root";
  //string infile = "local/ele/Cat1_Inc/Mass80/Shapes_hcs_13TeV_ele___kb_mjj_ele_WH80_2016.root";
  string signal = "ttbar";
  //string signal = "qcd";
  // string systUp = "LeptonUp";
  // string systDown = "LeptonDown";
  // string systUp = "JERUp";
  // string systDown = "JERDown";
  string systUp = "bcstatUp";
  string systDown = "bcstatDown";
  // string systUp = "qcdddUp";
  // string systDown = "qcdddDown";
  TFile *fin = TFile::Open(infile.c_str());
  TH1F *hBase = (TH1F *)fin->Get(signal.data());
  TH1F *hSysUp = (TH1F *)fin->Get((signal+"_"+systUp).data());
  TH1F *hSysDown = (TH1F *)fin->Get((signal+"_"+systDown).data());
  //ttbar_LeptonUp
  // hBase->SetLineColor(kRed);
  // hSysUp->SetLineColor(kBlue);
  // hSysDown->SetLineColor(kGreen);
  
  // TCanvas *c1 = new TCanvas("c1","c1");
  // hBase->Draw();
  // hSysUp->Draw("sames");
  // hSysDown->Draw("sames");

  Double_t error_frac = max(fabs(hSysUp->Integral() - hBase->Integral()), fabs(hBase->Integral() - hSysDown->Integral()))/hBase->Integral();
  TH1F *hRelErrUp = (TH1F *)hBase->Clone("hRelErrUp");
  TH1F *hRelErrDown = (TH1F *)hBase->Clone("hRelErrDown");
  // hRelErrUp->SetTitle(Form("Max. Unc. %5.3lf",(1+error_frac)));
    
  hBase->SetLineColor(kRed);
  hSysUp->SetLineColor(kBlue);
  hSysDown->SetLineColor(kGreen+1);
    
  hBase->SetLineWidth(2);
  hSysUp->SetLineWidth(2);
  hSysDown->SetLineWidth(2);

  hSysUp->SetTitle("");
  //hSysUp->GetXaxis()->SetRangeUser(0.,170.);
  PlotRatio(hSysUp, hBase, hRelErrUp, "c1");
  PlotRatio(hSysDown, hBase, hRelErrDown, "c1");
  
  TCanvas *c1 = (TCanvas *)gROOT->GetListOfCanvases()->FindObject("c1");
  c1->SaveAs("output.pdf");

  int ModifyUpDownHisto(TH1F*& hnom, TH1F*& hup, TH1F*& hdown, TH1F *hupbynom, TH1F *hdownbynom);
  ModifyUpDownHisto(hBase, hSysUp, hSysDown, hRelErrUp, hRelErrDown);  
  PlotRatio(hSysUp, hBase, hRelErrUp, "c2");
  PlotRatio(hSysDown, hBase, hRelErrDown, "c2");
  TCanvas *c2 = (TCanvas *)gROOT->GetListOfCanvases()->FindObject("c2");
  c2->SaveAs("output1.pdf");

  return true;
}

int ModifyUpDownHisto(TH1F*& hnom, TH1F*& hup, TH1F*& hdown, TH1F *hupbynom, TH1F *hdownbynom)
{
  
  for(int ibin=1; ibin<hupbynom->GetNbinsX(); ibin++){
    double bindiff = TMath::Abs(hupbynom->GetBinContent(ibin) - hdownbynom->GetBinContent(ibin));
    double binerror = hupbynom->GetBinError(ibin) + hdownbynom->GetBinError(ibin);
    double bindiff_up = TMath::Abs(hupbynom->GetBinContent(ibin) - 1.0);
    double bindiff_down = TMath::Abs(hdownbynom->GetBinContent(ibin) - 1.0);
    cout << hupbynom->GetName() << " at bin : " << ibin << ", at x = " << hupbynom->GetXaxis()->GetBinCenter(ibin) << " has bindiff_up: " << bindiff_up << " has content: " << hupbynom->GetBinContent(ibin) << endl;
    cout << hdownbynom->GetName() << " at bin : " << ibin << ", at x = " << hdownbynom->GetXaxis()->GetBinCenter(ibin) << " has bindiff_down: " << bindiff_down << " has content: " << hdownbynom->GetBinContent(ibin) << endl;
    cout << hnom->GetName() << " at bin : " << ibin << ", at x = " << hnom->GetXaxis()->GetBinCenter(ibin) << " has content: " << hnom->GetBinContent(ibin) << endl; 
    //if(binerror>bindiff or TMath::AreEqualAbs(hup->GetBinContent(ibin),0.0,1e-5)  or TMath::AreEqualAbs(hdown->GetBinContent(ibin),0.0,1e-5) or bindiff_down>1.0 or bindiff_up>1.0){
    if(TMath::AreEqualAbs(hup->GetBinContent(ibin),0.0,1e-5)  or TMath::AreEqualAbs(hdown->GetBinContent(ibin),0.0,1e-5) or bindiff_down>1.0 or bindiff_up>1.0){
      cout << "ZERO for " << hupbynom->GetName() << " at bin : " << ibin << ", at x = " << hupbynom->GetXaxis()->GetBinCenter(ibin) << " has bindiff: " << bindiff << " and binerror: " << binerror << endl ;
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

  // hdown->Scale(hnom->Integral()/hdown->Integral());
  // hup->Scale(hnom->Integral()/hup->Integral());

  return true;
  
}

int PlotRatio(TH1F *h1, TH1F *h2, TH1F*& hAvgErr, const char *cname)
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
    //h1->SetStats(0);          // No statistics on upper plot
    h1->Draw("hist");               // Draw h1
    h2->Draw("hist sames");         // Draw h2 on top of h1
 
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
    hAvgErr = (TH1F*)h3->Clone(hAvgErr->GetName());
    
    h3->SetMinimum(0.92);  // Define Y ..
    h3->SetMaximum(1.08); // .. range

    // h3->SetMinimum(0.5);  // Define Y ..
    // h3->SetMaximum(1.5); // .. range

    // h3->SetMinimum(0.0);  // Define Y ..
    // h3->SetMaximum(2.0); // .. range

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
    
    h1->Draw("hist sames");             
    h2->Draw("hist sames");         
    
    TPad *pad2 = (TPad *)canvas->GetListOfPrimitives()->FindObject("pad2") ;
    pad2->cd();
    

    TH1F *h3 = (TH1F*)h1->Clone("h3");
    h3->SetLineColor(h1->GetLineColor());
    h3->Sumw2();
    h3->SetStats(0);      // No statistics on lower plot
    h3->Divide(h2);
    hAvgErr = (TH1F*)h3->Clone(hAvgErr->GetName());
    h3->Draw("ep same");       // Draw the ratio plot
    //hAvgErr->Draw("ep same");
    pad1->cd();
  }

  return true;
}
