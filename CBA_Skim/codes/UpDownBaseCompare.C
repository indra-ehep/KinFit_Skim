/**********************************************************************
 Created on : 12/09/2021
 Purpose    : Compare Up/Down with base
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
#include <TROOT.h>

#include <TRatioPlot.h>

#include <iostream>

using namespace std;

int UpDownBaseCompare(int isysup = 2){

  int PlotRatio(TH1D *h1, TH1D *h2, const char *cname);

  const char *samples_2016[] = {"HplusM080", "HplusM090", "HplusM100", "HplusM140", 
				"HplusM150", "HplusM155", "HplusM160", "HplusM120", 
				"DataMu", "DataEle", "TTbar", "singleTop", 
				"Wjets", "DYjets", "VBFusion", "MCQCDMu", 
				"MCQCDEle"};
  
  const char *syst_2016[] = {"base", 
			     "puup", "pudown", "mueffup", "mueffdown", 
			     "eleeffup", "eleeffdown",  "jecup", "jecdown", 
			     "jerup", "jerdown", "btagbup", "btagbdown", 
			     "btaglup", "btagldown", "prefireup", "prefiredown",
                             "pdfup", "pdfdown", "q2fup", "q2down",
			     "isrup", "isrdown", "fsrup", "fsrdown",
			     "cp5up", "cp5down", "hdampup", "hdampdown",
                             "mtopup", "mtopdown"};
  
  const char *systname_2016[] = {"nominal", 
				 "pileup up", "pileup down", "muon efficiency up", "muon efficiency down", 
				 "electron efficiency up", "electron efficiency down",  "jet energy correction up", "jet energy correction down", 
				 "jet energy resolution up", "jet energy resolution down", "btag b-quark up", "btag b-quark down", 
				 "btag l-quark up", "btag l-quark down", "prefire up", "prefire down",
				 "PDF up", "PDF down", "renormalization up", "renormalization down",
				 "ISR up", "ISR down", "FSR up", "FSR down",
				 "CP5tune up", "CP5tune down", "hdamp up", "hdamp down",
				 "mtop1695 up", "mtop1755 down"};

  //const char *inputdir = "/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v28_Syst/CBA_Skim_Syst" ;
  //const char *inputdir = "/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v30_Syst/CBA_Skim_Syst_MDPt" ;
  const char *inputdir = "/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v39_Syst/CBA_CTagM" ;
  
  int isample = 11; isample--;
  int ibase = 1; ibase--;
  int isysdown = isysup ;
  //int isysup = 2; 
  isysup--;

  
  const char *histname = "_kb_mjj_ele";
  const char *histnameup = (isysup<=16) ? Form("%s",histname) :  Form("%s_%s",histname,syst_2016[isysup]) ;
  const char *histnamedown = (isysdown<=17) ? Form("%s",histname) :  Form("%s_%s",histname,syst_2016[isysdown]) ;

  cout << "isample : "<<isample << ", ibase : "<<ibase << ", isysup : "<< isysup << ", isysdown : " << isysdown << endl;
  
  TFile *finBase = TFile::Open(Form("%s/2016/all_%s.root",inputdir,samples_2016[isample])); 
  TFile *finSysUp = finBase; 
  TFile *finSysDown = finBase;
 
  TH1D *hBase = (TH1D *)finBase->Get(Form("%s/base/Iso/%s",samples_2016[isample],histname));
  TH1D *hSysUp = (TH1D *)finSysUp->Get(Form("%s/%s/Iso/%s",samples_2016[isample],syst_2016[isysup],histname));
  TH1D *hSysDown = (TH1D *)finSysDown->Get(Form("%s/%s/Iso/%s",samples_2016[isample],syst_2016[isysdown],histname));

  // hBase->Sumw2();
  // hSysUp->Sumw2();
  // hSysDown->Sumw2();
  
  hBase->SetLineColor(kRed);
  hSysUp->SetLineColor(kBlue);
  hSysDown->SetLineColor(kGreen+1);

  hBase->SetLineWidth(2);
  hSysUp->SetLineWidth(2);
  hSysDown->SetLineWidth(2);
  
  // TCanvas *c1 = new TCanvas("c1", "c1", 500, 500); // FIRST create the canvas
  // TRatioPlot *rpu = new TRatioPlot(hSysUp, hBase, "divsym");
  // TRatioPlot *rpd = new TRatioPlot(hSysDown, hBase, "divsym");
  // rpu->Draw();
  // rpd->Draw("same");
  // c1->Update();

  TLegend *leg = new TLegend(0.6729323,0.803838,0.9974937,0.9957356);
  leg->SetFillColor(10);
  //leg->SetHeader("m_{H^{+}} = 120 GeV, #mu + jets (2016)");
  leg->SetHeader("m_{H^{+}} = 120 GeV, #it{e} + jets (2016)");
  leg->AddEntry(hSysUp, Form("%s",systname_2016[isysup]) ,"lfp");
  leg->AddEntry(hBase, Form("%s",systname_2016[ibase]) ,"lfp");
  leg->AddEntry(hSysDown, Form("%s",systname_2016[isysdown]) ,"lfp");

  
  hSysUp->SetMaximum(1.2*hSysUp->GetBinContent(hSysUp->FindBin(80.0)));
  hSysUp->SetTitle("");
  hSysUp->GetXaxis()->SetRangeUser(0.,170.);
  PlotRatio(hSysUp, hBase, "c1");
  PlotRatio(hSysDown, hBase, "c1");
  leg->Draw();
  
  TCanvas *c1 = (TCanvas *)gROOT->GetListOfCanvases()->FindObject("c1");
  c1->SaveAs(Form("ele_%s_sys.pdf",syst_2016[isysup]));
  c1->SaveAs("output.pdf");
  
  return true;
}

int PlotRatio(TH1D *h1, TH1D *h2, const char *cname)
{

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
    // h3->SetMinimum(0.2);  // Define Y ..
    // h3->SetMaximum(1.8); // .. range
    h3->SetMinimum(0.8);  // Define Y ..
    h3->SetMaximum(1.2); // .. range
    h3->Sumw2();
    h3->SetStats(0);      // No statistics on lower plot
    h3->Divide(h2);
    //h3->SetMarkerStyle(21);
    h3->Draw("ep");       // Draw the ratio plot
 
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
    
    pad1->cd();
  }

  return true;
}
