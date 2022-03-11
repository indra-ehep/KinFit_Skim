/**********************************************************************
 Created on : 06/03/2022
 Purpose    : Plot jet resolutions for PAG presentation
 Author     : Indranil Das, Visiting Fellow
 Email      : indranil.das@cern.ch | indra.ehep@gmail.com
**********************************************************************/
#include <TH1.h>
#include <TF1.h>
#include <TFile.h>
#include <TTree.h>
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
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

#include "TParticlePDG.h"
#include "TDatabasePDG.h"

#include "TLorentzVector.h"
#include "TVector3.h"

int PlotJetResolutions()
{
  const int nofHists = 37;
  TFile *fin = TFile::Open("/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/proof_v41_KFObjects/2017/AllBkg_KFObjectsReso_2017.root");
  TH1F *hist[nofHists];
  for(int ih=0;ih<nofHists;ih++){
    hist[ih] = (TH1F *)fin->Get(Form("hBJetETReso_26_%d",ih));
  }

  gStyle->SetOptStat(112211);
  gStyle->SetOptFit(11);

  TF1 *fn = new TF1("fn","gaus",-200.,200.);
  fn->SetNpx(1000);
  
  TCanvas *c1 = new TCanvas("c1","c1");
  hist[0]->Draw();
  hist[0]->Fit(fn,"QL");
  hist[0]->GetXaxis()->SetTitle("E_{T} GeV");
  hist[0]->GetYaxis()->SetTitle("(Rec_{E_{T}} - Gen_{E_{T}}) GeV");

  TCanvas *c2 = new TCanvas("c2","c2");
  c2->Divide(2,2);
  c2->cd(1);
  hist[0]->Draw();
  hist[0]->Fit(fn,"QL");
  hist[0]->GetXaxis()->SetTitle("E_{T} GeV");
  hist[0]->GetYaxis()->SetTitle("(Rec_{E_{T}} - Gen_{E_{T}}) GeV");
  c2->cd(2);
  hist[10]->Draw();
  hist[10]->Fit(fn,"QL");
  hist[10]->GetXaxis()->SetTitle("E_{T} GeV");
  hist[10]->GetYaxis()->SetTitle("(Rec_{E_{T}} - Gen_{E_{T}}) GeV");
  c2->cd(3);
  hist[25]->Draw();
  hist[25]->Fit(fn,"QL");
  hist[25]->GetXaxis()->SetTitle("E_{T} GeV");
  hist[25]->GetYaxis()->SetTitle("(Rec_{E_{T}} - Gen_{E_{T}}) GeV");
  c2->cd(4);
  hist[36]->Draw();
  hist[36]->Fit(fn,"QL");
  hist[36]->GetXaxis()->SetTitle("E_{T} GeV");
  hist[36]->GetYaxis()->SetTitle("(Rec_{E_{T}} - Gen_{E_{T}}) GeV");


  return true;
}
