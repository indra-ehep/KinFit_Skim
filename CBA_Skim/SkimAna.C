/**********************************************************************
 Created on : 14/07/2021
 Purpose    : Analyse the Skim tree.
              (format adapted from h1analysis)
 Author     : Indranil Das, Visiting Fellow
 Email      : indranil.das@cern.ch | indra.ehep@gmail.com
**********************************************************************/

#include <fstream>
#include <string>
#include <cstring>

#include "SkimAna.h"
#include "TH2.h"
#include "TF1.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TPaveStats.h"
#include "TMath.h"
#include "TProof.h"


//ClassImp(SkimAna)

Int_t SkimAna::CreateHistoArrays()
{
  // Create the histogram arrays

  fNDDReg = 4;
  ////////////////////////////// Cut flow histograms //////////////////////////////////
  fNBCFHists = 20;//18;
  fNCFHists = fNDDReg*fNBCFHists; // if fNBCFHists = 100, then == 0:99 for Iso HighMET | 100:199 for Iso LowMET | 200:299 nonIso HighMET | 300:399 nonIso LowMET
  int totNHists = fNCFHists*fNSyst;
  hCutFlow = new TH1D*[totNHists];
  ////////////////////////////// Cut flow histograms //////////////////////////////////

  ////////////////////////////////// Observables //////////////////////////////////////
  fNBObHists = 44;//132;
  fNObHists = fNDDReg*fNBObHists; // if fNBaseHists = 100, then == 0:99 for Iso HighMET | 100:199 for Iso LowMET | 200:299 nonIso HighMET | 300:399 nonIso LowMET
  totNHists = fNObHists*fNSyst;
  histObs = new TH1D*[totNHists];
  ////////////////////////////////// Observables //////////////////////////////////////

  ////////////////////// Weight and other histograms histograms ///////////////////////
  fNBWtHists = 45;
  fNWtHists = fNDDReg*fNBWtHists; // if fNBaseHists = 100, then == 0:99 for Iso HighMET | 100:199 for Iso LowMET | 200:299 nonIso HighMET | 300:399 nonIso LowMET
  totNHists = fNWtHists*fNSyst;
  histWt = new TH1D*[totNHists];
  ///////////////////// Weight and other histograms histograms ////////////////////////
  
  TDirectory *savedir = gDirectory;
  savedir->cd();
  fFile[0]->cd();
  
  //fNHist = fNSyst;
  fFileDir = new TDirectory*[fNSyst*fNDDReg];  
  
  TDirectory *d1 = fFile[0]->mkdir(fSample.Data());
  d1->cd();
  
  for(int isyst=0;isyst<fNSyst;isyst++){
    
    //if(isData && isyst>0) continue;
    
    TDirectory *d2 = d1->mkdir(fSystList[isyst]);
    d2->cd();
    fFileDir[isyst*fNDDReg + 0] = d2->mkdir("Iso");
    fFileDir[isyst*fNDDReg + 1] = d2->mkdir("LowMET");
    fFileDir[isyst*fNDDReg + 2] = d2->mkdir("NonIso");
    fFileDir[isyst*fNDDReg + 3] = d2->mkdir("NonIsoLowMET");

    //fFileDir[isyst*fNDDReg + 0]->pwd(); //fFileDir[isyst*fNDDReg+0]->GetPath() ;

    ////////////////////////////// Cut flow histograms //////////////////////////////////
    fFileDir[isyst*fNDDReg + 0]->cd();
    //fFileDir[isyst*fNDDReg + 0]->pwd(); cout <<" path " << fFileDir[isyst*fNDDReg+0]->GetPath() << endl;

    hCutFlow[fNCFHists*isyst + 0] = new TH1D("_cutflow_data", "_cutflow_data", 10, 0, 10);
    hCutFlow[fNCFHists*isyst + 1] = new TH1D("_cutflowUS_mu", "_cutflowUS_mu", 10, 0, 10);
    hCutFlow[fNCFHists*isyst + 2] = new TH1D("_cutflow_mu", "_cutflow_mu", 10, 0, 10);
    hCutFlow[fNCFHists*isyst + 3] = new TH1D("_cutflowUS_ele", "_cutflowUS_ele", 10, 0, 10);
    hCutFlow[fNCFHists*isyst + 4] = new TH1D("_cutflow_ele", "_cutflow_ele", 10, 0, 10);
    hCutFlow[fNCFHists*isyst + 5] = new TH1D("_cutflow5", "_cutflow5", 10, 0, 10);

    hCutFlow[fNCFHists*isyst + 6] = new TH1D("_cutflow_nofSlEle_mu", "_cutflow_nofSlEle_mu", 10, 0, 10);
    hCutFlow[fNCFHists*isyst + 7] = new TH1D("_cutflow_nofSlMu_mu", "_cutflow_nofSlMu_mu", 10, 0, 10);
    hCutFlow[fNCFHists*isyst + 8] = new TH1D("_cutflow_nofSlTau_mu", "_cutflow_nofSlTau_mu", 10, 0, 10);
    hCutFlow[fNCFHists*isyst + 9] = new TH1D("_cutflow_nofSlcs_mu", "_cutflow_nofSlcs_mu", 10, 0, 10);
    hCutFlow[fNCFHists*isyst + 10] = new TH1D("_cutflow_nofSlud_mu", "_cutflow_nofSlud_mu", 10, 0, 10);
    hCutFlow[fNCFHists*isyst + 11] = new TH1D("_cutflow_nofSlus_mu", "_cutflow_nofSlus_mu", 10, 0, 10);
    hCutFlow[fNCFHists*isyst + 12] = new TH1D("_cutflow_nofSldc_mu", "_cutflow_nofSldc_mu", 10, 0, 10);

    hCutFlow[fNCFHists*isyst + 13] = new TH1D("_cutflow_nofSlEle_ele", "_cutflow_nofSlEle_ele", 10, 0, 10);
    hCutFlow[fNCFHists*isyst + 14] = new TH1D("_cutflow_nofSlMu_ele", "_cutflow_nofSlMu_ele", 10, 0, 10);
    hCutFlow[fNCFHists*isyst + 15] = new TH1D("_cutflow_nofSlTau_ele", "_cutflow_nofSlTau_ele", 10, 0, 10);
    hCutFlow[fNCFHists*isyst + 16] = new TH1D("_cutflow_nofSlcs_ele", "_cutflow_nofSlcs_ele", 10, 0, 10);
    hCutFlow[fNCFHists*isyst + 17] = new TH1D("_cutflow_nofSlud_ele", "_cutflow_nofSlud_ele", 10, 0, 10);
    hCutFlow[fNCFHists*isyst + 18] = new TH1D("_cutflow_nofSlus_ele", "_cutflow_nofSlus_ele", 10, 0, 10);
    hCutFlow[fNCFHists*isyst + 19] = new TH1D("_cutflow_nofSldc_ele", "_cutflow_nofSldc_ele", 10, 0, 10);
    
    
    // hCutFlow[fNCFHists*isyst + 6 + 0] = new TH1D("_cutflow_data1", "_cutflow_data1", 10, 0, 10);
    // hCutFlow[fNCFHists*isyst + 6 + 1] = new TH1D("_cutflowUS_mu1", "_cutflowUS_mu1", 10, 0, 10);
    // hCutFlow[fNCFHists*isyst + 6 + 2] = new TH1D("_cutflow_mu1", "_cutflow_mu1", 10, 0, 10);
    // hCutFlow[fNCFHists*isyst + 6 + 3] = new TH1D("_cutflowUS_ele1", "_cutflowUS_ele1", 10, 0, 10);
    // hCutFlow[fNCFHists*isyst + 6 + 4] = new TH1D("_cutflow_ele1", "_cutflow_ele1", 10, 0, 10);
    // hCutFlow[fNCFHists*isyst + 6 + 5] = new TH1D("_cutflow51", "_cutflow51", 10, 0, 10);

    // hCutFlow[fNCFHists*isyst + 12 + 0] = new TH1D("_cutflow_data2", "_cutflow_data2", 10, 0, 10);
    // hCutFlow[fNCFHists*isyst + 12 + 1] = new TH1D("_cutflowUS_mu2", "_cutflowUS_mu2", 10, 0, 10);
    // hCutFlow[fNCFHists*isyst + 12 + 2] = new TH1D("_cutflow_mu2", "_cutflow_mu2", 10, 0, 10);
    // hCutFlow[fNCFHists*isyst + 12 + 3] = new TH1D("_cutflowUS_ele2", "_cutflowUS_ele2", 10, 0, 10);
    // hCutFlow[fNCFHists*isyst + 12 + 4] = new TH1D("_cutflow_ele2", "_cutflow_ele2", 10, 0, 10);
    // hCutFlow[fNCFHists*isyst + 12 + 5] = new TH1D("_cutflow52", "_cutflow52", 10, 0, 10);

    for(int icf=0;icf<fNBCFHists;icf++)
      hCutFlow[fNCFHists*isyst + icf]->SetDirectory(fFileDir[isyst*fNDDReg + 0]);

    fFileDir[isyst*fNDDReg + 1]->cd();
    //fFileDir[isyst*fNDDReg + 1]->pwd(); cout <<" path " << fFileDir[isyst*fNDDReg+1]->GetPath() << endl;
    int minHs = fNBCFHists ;
    for(int ilmet=minHs;ilmet<(minHs+fNBCFHists);ilmet++){
      hCutFlow[fNCFHists*isyst + ilmet] = (TH1D *)hCutFlow[ilmet-minHs]->Clone(Form("%s_lmet",hCutFlow[ilmet-minHs]->GetName()));
      hCutFlow[fNCFHists*isyst + ilmet]->SetTitle(Form("%s_lmet",hCutFlow[ilmet-minHs]->GetTitle()));
      hCutFlow[fNCFHists*isyst + ilmet]->SetDirectory(fFileDir[isyst*fNDDReg + 1]);
    }
    
    fFileDir[isyst*fNDDReg + 2]->cd();
    //fFileDir[isyst*fNDDReg + 2]->pwd(); cout <<" path " << fFileDir[isyst*fNDDReg+2]->GetPath() << endl;
    minHs = 2*fNBCFHists ;
    for(int iniso=minHs;iniso<(minHs+fNBCFHists);iniso++){
      hCutFlow[fNCFHists*isyst + iniso] = (TH1D *)hCutFlow[iniso-minHs]->Clone(Form("%s_noniso",hCutFlow[iniso-minHs]->GetName()));
      hCutFlow[fNCFHists*isyst + iniso]->SetTitle(Form("%s_noniso",hCutFlow[iniso-minHs]->GetTitle()));
      hCutFlow[fNCFHists*isyst + iniso]->SetDirectory(fFileDir[isyst*fNDDReg + 2]);
    }

    fFileDir[isyst*fNDDReg + 3]->cd();
    //fFileDir[isyst*fNDDReg + 3]->pwd(); cout <<" path " << fFileDir[isyst*fNDDReg+3]->GetPath() << endl;
    minHs = 3*fNBCFHists ;
    for(int inisolmet=minHs;inisolmet<(minHs+fNBCFHists);inisolmet++){
      hCutFlow[fNCFHists*isyst + inisolmet] = (TH1D *)hCutFlow[inisolmet-minHs]->Clone(Form("%s_noniso_lmet",hCutFlow[inisolmet-minHs]->GetName()));
      hCutFlow[fNCFHists*isyst + inisolmet]->SetTitle(Form("%s_noniso_lmet",hCutFlow[inisolmet-minHs]->GetTitle()));
      hCutFlow[fNCFHists*isyst + inisolmet]->SetDirectory(fFileDir[isyst*fNDDReg + 3]);
    }
    ////////////////////////////// Cut flow histograms //////////////////////////////////

    ////////////////////////////////// Observables //////////////////////////////////////
    fFileDir[isyst*fNDDReg + 0]->cd();
    //fFileDir[isyst*fNDDReg + 0]->pwd(); cout <<" path " << fFileDir[isyst*fNDDReg+0]->GetPath() << endl;
    
    histObs[fNObHists*isyst + 0] = new TH1D("_lb_pt_mu","_lb_pt_mu",100, 0., 1000.);
    histObs[fNObHists*isyst + 1] = new TH1D("_lb_eta_mu","_lb_eta_mu", 30, -3., 3.);
    histObs[fNObHists*isyst + 2] = new TH1D("_lb_phi_mu","_lb_phi_mu", 35, -3.5, 3.5);
    histObs[fNObHists*isyst + 3] = new TH1D("_lb_pt_ele","_lb_pt_ele",100, 0., 1000.);
    histObs[fNObHists*isyst + 4] = new TH1D("_lb_eta_ele","_lb_eta_ele", 30, -3., 3.);
    histObs[fNObHists*isyst + 5] = new TH1D("_lb_phi_ele","_lb_phi_ele", 35, -3.5, 3.5);
    histObs[fNObHists*isyst + 6] = new TH1D("_lb_pt_mu_jets","_lb_pt_mu_jets",100, 0., 1000.);
    histObs[fNObHists*isyst + 7] = new TH1D("_lb_eta_mu_jets","_lb_eta_mu_jets", 30, -3., 3.);
    histObs[fNObHists*isyst + 8] = new TH1D("_lb_phi_mu_jets","_lb_phi_mu_jets", 35, -3.5, 3.5);
    histObs[fNObHists*isyst + 9] = new TH1D("_lb_pt_ele_jets","_lb_pt_ele_jets",100, 0., 1000.);
    histObs[fNObHists*isyst + 10] = new TH1D("_lb_eta_ele_jets","_lb_eta_ele_jets", 30, -3., 3.);
    histObs[fNObHists*isyst + 11] = new TH1D("_lb_phi_ele_jets","_lb_phi_ele_jets", 35, -3.5, 3.5);
    histObs[fNObHists*isyst + 12] = new TH1D("_lb_pt_mu_met","_lb_pt_mu_met",100, 0., 1000.);
    histObs[fNObHists*isyst + 13] = new TH1D("_lb_phi_mu_met","_lb_phi_mu_met", 35, -3.5, 3.5);
    histObs[fNObHists*isyst + 14] = new TH1D("_lb_pt_ele_met","_lb_pt_ele_met",100, 0., 1000.);
    histObs[fNObHists*isyst + 15] = new TH1D("_lb_phi_ele_met","_lb_phi_ele_met", 35, -3.5, 3.5);
    histObs[fNObHists*isyst + 16] = new TH1D("_lb_njet_mu","_lb_njet_mu", 30, 0., 30);
    histObs[fNObHists*isyst + 17] = new TH1D("_lb_nbjet_mu","_lb_nbjet_mu", 30, 0., 30);
    histObs[fNObHists*isyst + 18] = new TH1D("_lb_njet_ele","_lb_njet_ele", 30, 0., 30);
    histObs[fNObHists*isyst + 19] = new TH1D("_lb_nbjet_ele","_lb_nbjet_ele", 30, 0., 30);
    histObs[fNObHists*isyst + 20] = new TH1D("_kb_pt_mu","_kb_pt_mu",100, 0., 1000.);
    histObs[fNObHists*isyst + 21] = new TH1D("_kb_eta_mu","_kb_eta_mu", 30, -3., 3.);
    histObs[fNObHists*isyst + 22] = new TH1D("_kb_phi_mu","_kb_phi_mu", 35, -3.5, 3.5);
    histObs[fNObHists*isyst + 23] = new TH1D("_kb_pt_ele","_kb_pt_ele",100, 0., 1000.);
    histObs[fNObHists*isyst + 24] = new TH1D("_kb_eta_ele","_kb_eta_ele", 30, -3., 3.);
    histObs[fNObHists*isyst + 25] = new TH1D("_kb_phi_ele","_kb_phi_ele", 35, -3.5, 3.5);
    histObs[fNObHists*isyst + 26] = new TH1D("_kb_pt_mu_jets","_kb_pt_mu_jets",100, 0., 1000.);
    histObs[fNObHists*isyst + 27] = new TH1D("_kb_eta_mu_jets","_kb_eta_mu_jets", 30, -3., 3.);
    histObs[fNObHists*isyst + 28] = new TH1D("_kb_phi_mu_jets","_kb_phi_mu_jets", 35, -3.5, 3.5);
    histObs[fNObHists*isyst + 29] = new TH1D("_kb_pt_ele_jets","_kb_pt_ele_jets",100, 0., 1000.);
    histObs[fNObHists*isyst + 30] = new TH1D("_kb_eta_ele_jets","_kb_eta_ele_jets", 30, -3., 3.);
    histObs[fNObHists*isyst + 31] = new TH1D("_kb_phi_ele_jets","_kb_phi_ele_jets", 35, -3.5, 3.5);
    histObs[fNObHists*isyst + 32] = new TH1D("_kb_pt_mu_met","_kb_pt_mu_met",100, 0., 1000.);
    histObs[fNObHists*isyst + 33] = new TH1D("_kb_phi_mu_met","_kb_phi_mu_met", 35, -3.5, 3.5);
    histObs[fNObHists*isyst + 34] = new TH1D("_kb_pt_ele_met","_kb_pt_ele_met",100, 0., 1000.);
    histObs[fNObHists*isyst + 35] = new TH1D("_kb_phi_ele_met","_kb_phi_ele_met", 35, -3.5, 3.5);
    histObs[fNObHists*isyst + 36] = new TH1D("_kb_njet_mu","_kb_njet_mu", 30, 0., 30);
    histObs[fNObHists*isyst + 37] = new TH1D("_kb_nbjet_mu","_kb_nbjet_mu", 30, 0., 30);
    histObs[fNObHists*isyst + 38] = new TH1D("_kb_njet_ele","_kb_njet_ele", 30, 0., 30);
    histObs[fNObHists*isyst + 39] = new TH1D("_kb_nbjet_ele","_kb_nbjet_ele", 30, 0., 30);
    histObs[fNObHists*isyst + 40] = new TH1D("_kb_mjj_mu","_kb_mjj_mu", 50, 0., 250);
    histObs[fNObHists*isyst + 41] = new TH1D("_kb_mjj_ele","_kb_mjj_ele", 50, 0., 250);
    histObs[fNObHists*isyst + 42] = new TH1D("_kb_mjj_bf_mu","_kb_mjj_bf_mu", 50, 0., 250);
    histObs[fNObHists*isyst + 43] = new TH1D("_kb_mjj_bf_ele","_kb_mjj_bf_ele", 50, 0., 250);

    // histObs[fNObHists*isyst + 44 + 0] = new TH1D("_lb_pt_mu1","_lb_pt_mu1",100, 0., 1000.);
    // histObs[fNObHists*isyst + 44 + 1] = new TH1D("_lb_eta_mu1","_lb_eta_mu1", 30, -3., 3.);
    // histObs[fNObHists*isyst + 44 + 2] = new TH1D("_lb_phi_mu1","_lb_phi_mu1", 35, -3.5, 3.5);
    // histObs[fNObHists*isyst + 44 + 3] = new TH1D("_lb_pt_ele1","_lb_pt_ele1",100, 0., 1000.);
    // histObs[fNObHists*isyst + 44 + 4] = new TH1D("_lb_eta_ele1","_lb_eta_ele1", 30, -3., 3.);
    // histObs[fNObHists*isyst + 44 + 5] = new TH1D("_lb_phi_ele1","_lb_phi_ele1", 35, -3.5, 3.5);
    // histObs[fNObHists*isyst + 44 + 6] = new TH1D("_lb_pt_mu_jets1","_lb_pt_mu_jets1",100, 0., 1000.);
    // histObs[fNObHists*isyst + 44 + 7] = new TH1D("_lb_eta_mu_jets1","_lb_eta_mu_jets1", 30, -3., 3.);
    // histObs[fNObHists*isyst + 44 + 8] = new TH1D("_lb_phi_mu_jets1","_lb_phi_mu_jets1", 35, -3.5, 3.5);
    // histObs[fNObHists*isyst + 44 + 9] = new TH1D("_lb_pt_ele_jets1","_lb_pt_ele_jets1",100, 0., 1000.);
    // histObs[fNObHists*isyst + 44 + 10] = new TH1D("_lb_eta_ele_jets1","_lb_eta_ele_jets1", 30, -3., 3.);
    // histObs[fNObHists*isyst + 44 + 11] = new TH1D("_lb_phi_ele_jets1","_lb_phi_ele_jets1", 35, -3.5, 3.5);
    // histObs[fNObHists*isyst + 44 + 12] = new TH1D("_lb_pt_mu_met1","_lb_pt_mu_met1",100, 0., 1000.);
    // histObs[fNObHists*isyst + 44 + 13] = new TH1D("_lb_phi_mu_met1","_lb_phi_mu_met1", 35, -3.5, 3.5);
    // histObs[fNObHists*isyst + 44 + 14] = new TH1D("_lb_pt_ele_met1","_lb_pt_ele_met1",100, 0., 1000.);
    // histObs[fNObHists*isyst + 44 + 15] = new TH1D("_lb_phi_ele_met1","_lb_phi_ele_met1", 35, -3.5, 3.5);
    // histObs[fNObHists*isyst + 44 + 16] = new TH1D("_lb_njet_mu1","_lb_njet_mu1", 30, 0., 30);
    // histObs[fNObHists*isyst + 44 + 17] = new TH1D("_lb_nbjet_mu1","_lb_nbjet_mu1", 30, 0., 30);
    // histObs[fNObHists*isyst + 44 + 18] = new TH1D("_lb_njet_ele1","_lb_njet_ele1", 30, 0., 30);
    // histObs[fNObHists*isyst + 44 + 19] = new TH1D("_lb_nbjet_ele1","_lb_nbjet_ele1", 30, 0., 30);
    // histObs[fNObHists*isyst + 44 + 20] = new TH1D("_kb_pt_mu1","_kb_pt_mu1",100, 0., 1000.);
    // histObs[fNObHists*isyst + 44 + 21] = new TH1D("_kb_eta_mu1","_kb_eta_mu1", 30, -3., 3.);
    // histObs[fNObHists*isyst + 44 + 22] = new TH1D("_kb_phi_mu1","_kb_phi_mu1", 35, -3.5, 3.5);
    // histObs[fNObHists*isyst + 44 + 23] = new TH1D("_kb_pt_ele1","_kb_pt_ele1",100, 0., 1000.);
    // histObs[fNObHists*isyst + 44 + 24] = new TH1D("_kb_eta_ele1","_kb_eta_ele1", 30, -3., 3.);
    // histObs[fNObHists*isyst + 44 + 25] = new TH1D("_kb_phi_ele1","_kb_phi_ele1", 35, -3.5, 3.5);
    // histObs[fNObHists*isyst + 44 + 26] = new TH1D("_kb_pt_mu_jets1","_kb_pt_mu_jets1",100, 0., 1000.);
    // histObs[fNObHists*isyst + 44 + 27] = new TH1D("_kb_eta_mu_jets1","_kb_eta_mu_jets1", 30, -3., 3.);
    // histObs[fNObHists*isyst + 44 + 28] = new TH1D("_kb_phi_mu_jets1","_kb_phi_mu_jets1", 35, -3.5, 3.5);
    // histObs[fNObHists*isyst + 44 + 29] = new TH1D("_kb_pt_ele_jets1","_kb_pt_ele_jets1",100, 0., 1000.);
    // histObs[fNObHists*isyst + 44 + 30] = new TH1D("_kb_eta_ele_jets1","_kb_eta_ele_jets1", 30, -3., 3.);
    // histObs[fNObHists*isyst + 44 + 31] = new TH1D("_kb_phi_ele_jets1","_kb_phi_ele_jets1", 35, -3.5, 3.5);
    // histObs[fNObHists*isyst + 44 + 32] = new TH1D("_kb_pt_mu_met1","_kb_pt_mu_met1",100, 0., 1000.);
    // histObs[fNObHists*isyst + 44 + 33] = new TH1D("_kb_phi_mu_met1","_kb_phi_mu_met1", 35, -3.5, 3.5);
    // histObs[fNObHists*isyst + 44 + 34] = new TH1D("_kb_pt_ele_met1","_kb_pt_ele_met1",100, 0., 1000.);
    // histObs[fNObHists*isyst + 44 + 35] = new TH1D("_kb_phi_ele_met1","_kb_phi_ele_met1", 35, -3.5, 3.5);
    // histObs[fNObHists*isyst + 44 + 36] = new TH1D("_kb_njet_mu1","_kb_njet_mu1", 30, 0., 30);
    // histObs[fNObHists*isyst + 44 + 37] = new TH1D("_kb_nbjet_mu1","_kb_nbjet_mu1", 30, 0., 30);
    // histObs[fNObHists*isyst + 44 + 38] = new TH1D("_kb_njet_ele1","_kb_njet_ele1", 30, 0., 30);
    // histObs[fNObHists*isyst + 44 + 39] = new TH1D("_kb_nbjet_ele1","_kb_nbjet_ele1", 30, 0., 30);
    // histObs[fNObHists*isyst + 44 + 40] = new TH1D("_kb_mjj_mu1","_kb_mjj_mu1", 50, 0., 250);
    // histObs[fNObHists*isyst + 44 + 41] = new TH1D("_kb_mjj_ele1","_kb_mjj_ele1", 50, 0., 250);
    // histObs[fNObHists*isyst + 44 + 42] = new TH1D("_kb_mjj_bf_mu1","_kb_mjj_bf_mu1", 50, 0., 250);
    // histObs[fNObHists*isyst + 44 + 43] = new TH1D("_kb_mjj_bf_ele1","_kb_mjj_bf_ele1", 50, 0., 250);

    // histObs[fNObHists*isyst + 88 + 0] = new TH1D("_lb_pt_mu2","_lb_pt_mu2",100, 0., 1000.);
    // histObs[fNObHists*isyst + 88 + 1] = new TH1D("_lb_eta_mu2","_lb_eta_mu2", 30, -3., 3.);
    // histObs[fNObHists*isyst + 88 + 2] = new TH1D("_lb_phi_mu2","_lb_phi_mu2", 35, -3.5, 3.5);
    // histObs[fNObHists*isyst + 88 + 3] = new TH1D("_lb_pt_ele2","_lb_pt_ele2",100, 0., 1000.);
    // histObs[fNObHists*isyst + 88 + 4] = new TH1D("_lb_eta_ele2","_lb_eta_ele2", 30, -3., 3.);
    // histObs[fNObHists*isyst + 88 + 5] = new TH1D("_lb_phi_ele2","_lb_phi_ele2", 35, -3.5, 3.5);
    // histObs[fNObHists*isyst + 88 + 6] = new TH1D("_lb_pt_mu_jets2","_lb_pt_mu_jets2",100, 0., 1000.);
    // histObs[fNObHists*isyst + 88 + 7] = new TH1D("_lb_eta_mu_jets2","_lb_eta_mu_jets2", 30, -3., 3.);
    // histObs[fNObHists*isyst + 88 + 8] = new TH1D("_lb_phi_mu_jets2","_lb_phi_mu_jets2", 35, -3.5, 3.5);
    // histObs[fNObHists*isyst + 88 + 9] = new TH1D("_lb_pt_ele_jets2","_lb_pt_ele_jets2",100, 0., 1000.);
    // histObs[fNObHists*isyst + 88 + 10] = new TH1D("_lb_eta_ele_jets2","_lb_eta_ele_jets2", 30, -3., 3.);
    // histObs[fNObHists*isyst + 88 + 11] = new TH1D("_lb_phi_ele_jets2","_lb_phi_ele_jets2", 35, -3.5, 3.5);
    // histObs[fNObHists*isyst + 88 + 12] = new TH1D("_lb_pt_mu_met2","_lb_pt_mu_met2",100, 0., 1000.);
    // histObs[fNObHists*isyst + 88 + 13] = new TH1D("_lb_phi_mu_met2","_lb_phi_mu_met2", 35, -3.5, 3.5);
    // histObs[fNObHists*isyst + 88 + 14] = new TH1D("_lb_pt_ele_met2","_lb_pt_ele_met2",100, 0., 1000.);
    // histObs[fNObHists*isyst + 88 + 15] = new TH1D("_lb_phi_ele_met2","_lb_phi_ele_met2", 35, -3.5, 3.5);
    // histObs[fNObHists*isyst + 88 + 16] = new TH1D("_lb_njet_mu2","_lb_njet_mu2", 30, 0., 30);
    // histObs[fNObHists*isyst + 88 + 17] = new TH1D("_lb_nbjet_mu2","_lb_nbjet_mu2", 30, 0., 30);
    // histObs[fNObHists*isyst + 88 + 18] = new TH1D("_lb_njet_ele2","_lb_njet_ele2", 30, 0., 30);
    // histObs[fNObHists*isyst + 88 + 19] = new TH1D("_lb_nbjet_ele2","_lb_nbjet_ele2", 30, 0., 30);
    // histObs[fNObHists*isyst + 88 + 20] = new TH1D("_kb_pt_mu2","_kb_pt_mu2",100, 0., 1000.);
    // histObs[fNObHists*isyst + 88 + 21] = new TH1D("_kb_eta_mu2","_kb_eta_mu2", 30, -3., 3.);
    // histObs[fNObHists*isyst + 88 + 22] = new TH1D("_kb_phi_mu2","_kb_phi_mu2", 35, -3.5, 3.5);
    // histObs[fNObHists*isyst + 88 + 23] = new TH1D("_kb_pt_ele2","_kb_pt_ele2",100, 0., 1000.);
    // histObs[fNObHists*isyst + 88 + 24] = new TH1D("_kb_eta_ele2","_kb_eta_ele2", 30, -3., 3.);
    // histObs[fNObHists*isyst + 88 + 25] = new TH1D("_kb_phi_ele2","_kb_phi_ele2", 35, -3.5, 3.5);
    // histObs[fNObHists*isyst + 88 + 26] = new TH1D("_kb_pt_mu_jets2","_kb_pt_mu_jets2",100, 0., 1000.);
    // histObs[fNObHists*isyst + 88 + 27] = new TH1D("_kb_eta_mu_jets2","_kb_eta_mu_jets2", 30, -3., 3.);
    // histObs[fNObHists*isyst + 88 + 28] = new TH1D("_kb_phi_mu_jets2","_kb_phi_mu_jets2", 35, -3.5, 3.5);
    // histObs[fNObHists*isyst + 88 + 29] = new TH1D("_kb_pt_ele_jets2","_kb_pt_ele_jets2",100, 0., 1000.);
    // histObs[fNObHists*isyst + 88 + 30] = new TH1D("_kb_eta_ele_jets2","_kb_eta_ele_jets2", 30, -3., 3.);
    // histObs[fNObHists*isyst + 88 + 31] = new TH1D("_kb_phi_ele_jets2","_kb_phi_ele_jets2", 35, -3.5, 3.5);
    // histObs[fNObHists*isyst + 88 + 32] = new TH1D("_kb_pt_mu_met2","_kb_pt_mu_met2",100, 0., 1000.);
    // histObs[fNObHists*isyst + 88 + 33] = new TH1D("_kb_phi_mu_met2","_kb_phi_mu_met2", 35, -3.5, 3.5);
    // histObs[fNObHists*isyst + 88 + 34] = new TH1D("_kb_pt_ele_met2","_kb_pt_ele_met2",100, 0., 1000.);
    // histObs[fNObHists*isyst + 88 + 35] = new TH1D("_kb_phi_ele_met2","_kb_phi_ele_met2", 35, -3.5, 3.5);
    // histObs[fNObHists*isyst + 88 + 36] = new TH1D("_kb_njet_mu2","_kb_njet_mu2", 30, 0., 30);
    // histObs[fNObHists*isyst + 88 + 37] = new TH1D("_kb_nbjet_mu2","_kb_nbjet_mu2", 30, 0., 30);
    // histObs[fNObHists*isyst + 88 + 38] = new TH1D("_kb_njet_ele2","_kb_njet_ele2", 30, 0., 30);
    // histObs[fNObHists*isyst + 88 + 39] = new TH1D("_kb_nbjet_ele2","_kb_nbjet_ele2", 30, 0., 30);
    // histObs[fNObHists*isyst + 88 + 40] = new TH1D("_kb_mjj_mu2","_kb_mjj_mu2", 50, 0., 250);
    // histObs[fNObHists*isyst + 88 + 41] = new TH1D("_kb_mjj_ele2","_kb_mjj_ele2", 50, 0., 250);
    // histObs[fNObHists*isyst + 88 + 42] = new TH1D("_kb_mjj_bf_mu2","_kb_mjj_bf_mu2", 50, 0., 250);
    // histObs[fNObHists*isyst + 88 + 43] = new TH1D("_kb_mjj_bf_ele2","_kb_mjj_bf_ele2", 50, 0., 250);

    for(int icf=0;icf<fNBObHists;icf++)
      histObs[fNObHists*isyst + icf]->SetDirectory(fFileDir[isyst*fNDDReg + 0]);
    
    fFileDir[isyst*fNDDReg + 1]->cd();
    //fFileDir[isyst*fNDDReg + 1]->pwd(); cout <<" path " << fFileDir[isyst*fNDDReg+1]->GetPath() << endl;
    minHs = fNBObHists ;
    for(int ilmet=minHs;ilmet<(minHs+fNBObHists);ilmet++){
      histObs[fNObHists*isyst + ilmet] = (TH1D *)histObs[ilmet-minHs]->Clone(Form("%s_lmet",histObs[ilmet-minHs]->GetName()));
      histObs[fNObHists*isyst + ilmet]->SetTitle(Form("%s_lmet",histObs[ilmet-minHs]->GetTitle()));
      histObs[fNObHists*isyst + ilmet]->SetDirectory(fFileDir[isyst*fNDDReg + 1]);
    }
    
    fFileDir[isyst*fNDDReg + 2]->cd();
    //fFileDir[isyst*fNDDReg + 2]->pwd(); cout <<" path " << fFileDir[isyst*fNDDReg+2]->GetPath() << endl;
    minHs = 2*fNBObHists ;
    for(int iniso=minHs;iniso<(minHs+fNBObHists);iniso++){
      histObs[fNObHists*isyst + iniso] = (TH1D *)histObs[iniso-minHs]->Clone(Form("%s_noniso",histObs[iniso-minHs]->GetName()));
      histObs[fNObHists*isyst + iniso]->SetTitle(Form("%s_noniso",histObs[iniso-minHs]->GetTitle()));
      histObs[fNObHists*isyst + iniso]->SetDirectory(fFileDir[isyst*fNDDReg + 2]);
    }

    fFileDir[isyst*fNDDReg + 3]->cd();
    //fFileDir[isyst*fNDDReg + 3]->pwd(); cout <<" path " << fFileDir[isyst*fNDDReg+3]->GetPath() << endl;
    minHs = 3*fNBObHists ;
    for(int inisolmet=minHs;inisolmet<(minHs+fNBObHists);inisolmet++){
      histObs[fNObHists*isyst + inisolmet] = (TH1D *)histObs[inisolmet-minHs]->Clone(Form("%s_noniso_lmet",histObs[inisolmet-minHs]->GetName()));
      histObs[fNObHists*isyst + inisolmet]->SetTitle(Form("%s_noniso_lmet",histObs[inisolmet-minHs]->GetTitle()));
      histObs[fNObHists*isyst + inisolmet]->SetDirectory(fFileDir[isyst*fNDDReg + 3]);
    }
    ////////////////////////////////// Observables //////////////////////////////////////

    ////////////////////// Weight and other histograms histograms ///////////////////////
    histWt[fNWtHists*isyst + 0] = new TH1D("_sampleWeight","_sampleWeight",2000, -10, 10);
    histWt[fNWtHists*isyst + 1] = new TH1D("_PUWeight","_PUWeight", 2000, -10, 10);
    histWt[fNWtHists*isyst + 2] = new TH1D("_prefireWeight","_prefireWeight",2000, -10, 10);
    histWt[fNWtHists*isyst + 3] = new TH1D("_muEffWeight","_muEffWeight",2000, -10, 10);
    histWt[fNWtHists*isyst + 4] = new TH1D("_eleEffWeight","_eleEffWeight",2000, -10, 10);
    histWt[fNWtHists*isyst + 5] = new TH1D("_btagWeight_1a","_btagWeight_1a",2000, -10, 10);
    histWt[fNWtHists*isyst + 6] = new TH1D("_btagWeight_1a_b_Do","_btagWeight_1a_b_Do",2000, -10, 10);
    histWt[fNWtHists*isyst + 7] = new TH1D("_btagWeight_1a_b_Up","_btagWeight_1a_b_Up",2000, -10, 10);
    histWt[fNWtHists*isyst + 8] = new TH1D("_btagWeight_1a_l_Do","_btagWeight_1a_l_Do",2000, -10, 10);
    histWt[fNWtHists*isyst + 9] = new TH1D("_btagWeight_1a_l_Up","_btagWeight_1a_l_Up",2000, -10, 10);
    histWt[fNWtHists*isyst + 10] = new TH1D("_muEffWeight_Up","_muEffWeight_Up",2000, -10, 10);
    histWt[fNWtHists*isyst + 11] = new TH1D("_muEffWeight_Do","_muEffWeight_Do",2000, -10, 10);
    histWt[fNWtHists*isyst + 12] = new TH1D("_eleEffWeight_Up","_eleEffWeight_Up",2000, -10, 10);
    histWt[fNWtHists*isyst + 13] = new TH1D("_eleEffWeight_Do","_eleEffWeight_Do",2000, -10, 10);
    histWt[fNWtHists*isyst + 14] = new TH1D("_pdfweight_Up","_pdfweight_Up",2000, -10, 10);
    histWt[fNWtHists*isyst + 15] = new TH1D("_pdfweight_Do","_pdfweight_Do",2000, -10, 10);
    histWt[fNWtHists*isyst + 16] = new TH1D("_q2weight_Up","_q2weight_Up",2000, -10, 10);
    histWt[fNWtHists*isyst + 17] = new TH1D("_q2weight_Do","_q2weight_Do",2000, -10, 10);
    histWt[fNWtHists*isyst + 18] = new TH1D("_FSRweight_Up","_FSRweight_Up",2000, -10, 10);
    histWt[fNWtHists*isyst + 19] = new TH1D("_FSRweight_Do","_FSRweight_Do",2000, -10, 10);
    histWt[fNWtHists*isyst + 20] = new TH1D("_ISRweight_Up","_ISRweight_Up",2000, -10, 10);
    histWt[fNWtHists*isyst + 21] = new TH1D("_ISRweight_Do","_ISRweight_Do",2000, -10, 10);
    histWt[fNWtHists*isyst + 22] = new TH1D("_PUWeight_Up","_PUWeight_Up",2000, -10, 10);
    histWt[fNWtHists*isyst + 23] = new TH1D("_PUWeight_Do","_PUWeight_Do",2000, -10, 10);
    histWt[fNWtHists*isyst + 24] = new TH1D("_topPtReweight","_topPtReweight",2000, -10, 10);
    histWt[fNWtHists*isyst + 25] = new TH1D("_muIso","_muIso", 100, 0., 1.);
    histWt[fNWtHists*isyst + 26] = new TH1D("_eleIso","_eleIso", 100, 0., 1.);
    histWt[fNWtHists*isyst + 27] = new TH1D("_muMET","_muMET", 100, 0., 500.);
    histWt[fNWtHists*isyst + 28] = new TH1D("_eleMET","_eleMET", 100, 0., 500.);    
    histWt[fNWtHists*isyst + 29] = new TH1D("_bjet1Pt_AF_mu","_bjet1Pt_AF_mu", 100, 0., 1000.);
    histWt[fNWtHists*isyst + 30] = new TH1D("_bjet2Pt_AF_mu","_bjet2Pt_AF_mu", 100, 0., 1000.);
    histWt[fNWtHists*isyst + 31] = new TH1D("_ljet1Pt_AF_mu","_ljet1Pt_AF_mu", 100, 0., 1000.);
    histWt[fNWtHists*isyst + 32] = new TH1D("_ljet2Pt_AF_mu","_ljet2Pt_AF_mu", 100, 0., 1000.);
    histWt[fNWtHists*isyst + 33] = new TH1D("_bjet1Pt_BF_mu","_bjet1Pt_BF_mu", 100, 0., 1000.);
    histWt[fNWtHists*isyst + 34] = new TH1D("_bjet2Pt_BF_mu","_bjet2Pt_BF_mu", 100, 0., 1000.);
    histWt[fNWtHists*isyst + 35] = new TH1D("_ljet1Pt_BF_mu","_ljet1Pt_BF_mu", 100, 0., 1000.);
    histWt[fNWtHists*isyst + 36] = new TH1D("_ljet2Pt_BF_mu","_ljet2Pt_BF_mu", 100, 0., 1000.);
    histWt[fNWtHists*isyst + 37] = new TH1D("_bjet1Pt_AF_ele","_bjet1Pt_AF_ele", 100, 0., 1000.);
    histWt[fNWtHists*isyst + 38] = new TH1D("_bjet2Pt_AF_ele","_bjet2Pt_AF_ele", 100, 0., 1000.);
    histWt[fNWtHists*isyst + 39] = new TH1D("_ljet1Pt_AF_ele","_ljet1Pt_AF_ele", 100, 0., 1000.);
    histWt[fNWtHists*isyst + 40] = new TH1D("_ljet2Pt_AF_ele","_ljet2Pt_AF_ele", 100, 0., 1000.);
    histWt[fNWtHists*isyst + 41] = new TH1D("_bjet1Pt_BF_ele","_bjet1Pt_BF_ele", 100, 0., 1000.);
    histWt[fNWtHists*isyst + 42] = new TH1D("_bjet2Pt_BF_ele","_bjet2Pt_BF_ele", 100, 0., 1000.);
    histWt[fNWtHists*isyst + 43] = new TH1D("_ljet1Pt_BF_ele","_ljet1Pt_BF_ele", 100, 0., 1000.);
    histWt[fNWtHists*isyst + 44] = new TH1D("_ljet2Pt_BF_ele","_ljet2Pt_BF_ele", 100, 0., 1000.);

    for(int icf=0;icf<fNBWtHists;icf++)
      histWt[fNWtHists*isyst + icf]->SetDirectory(fFileDir[isyst*fNDDReg + 0]);
  
    fFileDir[isyst*fNDDReg + 1]->cd();
    //fFileDir[isyst*fNDDReg + 1]->pwd(); cout <<" path " << fFileDir[isyst*fNDDReg+1]->GetPath() << endl;
    minHs = fNBWtHists ;
    for(int ilmet=minHs;ilmet<(minHs+fNBWtHists);ilmet++){
      histWt[fNWtHists*isyst + ilmet] = (TH1D *)histWt[ilmet-minHs]->Clone(Form("%s_lmet",histWt[ilmet-minHs]->GetName()));
      histWt[fNWtHists*isyst + ilmet]->SetTitle(Form("%s_lmet",histWt[ilmet-minHs]->GetTitle()));
      histWt[fNWtHists*isyst + ilmet]->SetDirectory(fFileDir[isyst*fNDDReg + 1]);
    }
    
    fFileDir[isyst*fNDDReg + 2]->cd();
    //fFileDir[isyst*fNDDReg + 2]->pwd(); cout <<" path " << fFileDir[isyst*fNDDReg+2]->GetPath() << endl;
    minHs = 2*fNBWtHists ;
    for(int iniso=minHs;iniso<(minHs+fNBWtHists);iniso++){
      histWt[fNWtHists*isyst + iniso] = (TH1D *)histWt[iniso-minHs]->Clone(Form("%s_noniso",histWt[iniso-minHs]->GetName()));
      histWt[fNWtHists*isyst + iniso]->SetTitle(Form("%s_noniso",histWt[iniso-minHs]->GetTitle()));
      histWt[fNWtHists*isyst + iniso]->SetDirectory(fFileDir[isyst*fNDDReg + 2]);
    }

    fFileDir[isyst*fNDDReg + 3]->cd();
    //fFileDir[isyst*fNDDReg + 3]->pwd(); cout <<" path " << fFileDir[isyst*fNDDReg+3]->GetPath() << endl;
    minHs = 3*fNBWtHists ;
    for(int inisolmet=minHs;inisolmet<(minHs+fNBWtHists);inisolmet++){
      histWt[fNWtHists*isyst + inisolmet] = (TH1D *)histWt[inisolmet-minHs]->Clone(Form("%s_noniso_lmet",histWt[inisolmet-minHs]->GetName()));
      histWt[fNWtHists*isyst + inisolmet]->SetTitle(Form("%s_noniso_lmet",histWt[inisolmet-minHs]->GetTitle()));
      histWt[fNWtHists*isyst + inisolmet]->SetDirectory(fFileDir[isyst*fNDDReg + 3]);
    }
    ////////////////////// Weight and other histograms histograms ///////////////////////

    //fFileDir[ifile*fNSyst + isyst]->pwd();
    // cout <<"file ptr : " << fFileDir[ifile*fNSyst + isyst] << endl;
    // cout << "index : " << ifile*fNSyst + isyst << endl;
  }
  savedir->cd();

  // for(int isyst=0;isyst<fNSyst;isyst++){
  //   cout << "Nof Objects " << fFileDir[isyst*fNDDReg + 0]->GetList()->GetEntries() << endl ; 
  //   cout << "First Object " << fFileDir[isyst*fNDDReg + 0]->GetList()->At(0)->GetName() << endl ; 
  //   cout << "Last Object " << fFileDir[isyst*fNDDReg + 0]->GetList()->At(fFileDir[isyst*fNDDReg + 0]->GetList()->GetEntries()-1)->GetName() << endl ; 
  //   cout << "Nof Objects " << fFileDir[isyst*fNDDReg + 3]->GetList()->GetEntries() << endl ; 
  //   cout << "First Object " << fFileDir[isyst*fNDDReg + 3]->GetList()->At(0)->GetName() << endl ; 
  //   cout << "Last Object " << fFileDir[isyst*fNDDReg + 3]->GetList()->At(fFileDir[isyst*fNDDReg + 3]->GetList()->GetEntries()-1)->GetName() << endl ; 
  // }
  
  hMinChi2_mu = new TH1F("hMinChi2_mu","1^{st} minimum",500,0,100.0); 
  h2MinChi2_mu = new TH1F("h2MinChi2_mu","2^{nd} minimum",500,0,100.0); 
  h3MinChi2_mu = new TH1F("h3MinChi2_mu","3^{rd} minimum",500,0,100.0); 
  h4MinChi2_mu = new TH1F("h4MinChi2_mu","4^{th} minimum",500,0,100.0); 
  h5MinChi2_mu = new TH1F("h5MinChi2_mu","5^{th} minimum",500,0,100.0); 

  hMinChi2_ele = new TH1F("hMinChi2_ele","1^{st} minimum",500,0,100.0); 
  h2MinChi2_ele = new TH1F("h2MinChi2_ele","2^{nd} minimum",500,0,100.0); 
  h3MinChi2_ele = new TH1F("h3MinChi2_ele","3^{rd} minimum",500,0,100.0); 
  h4MinChi2_ele = new TH1F("h4MinChi2_ele","4^{th} minimum",500,0,100.0); 
  h5MinChi2_ele = new TH1F("h5MinChi2_ele","5^{th} minimum",500,0,100.0); 

  savedir->cd();

  fFile[1]->cd();
  outputTree = new TTree("Kinfit_Reco","Kinfit_Reco");
  outputTree->SetAutoSave();
  InitOutBranches();
  savedir->cd();
  
  



  return true;
}

//_____________________________________________________________________________
void SkimAna::GetArguments(){
  
  TString option = GetOption();
  //Info("GetArguments","ending SkimAna with process option: %s", option.Data());
  
  Ssiz_t from = 0;
  TString tok;
  // Now analyze the arguments
  while (option.Tokenize(tok , from , "|")) {
    if(tok.BeginsWith("sample"))
      fSample = ((TObjString *) (tok.Tokenize("="))->At(1))->GetString();
    if(tok.BeginsWith("input"))
      fFileName = ((TObjString *) (tok.Tokenize("="))->At(1))->GetString();
    if(tok.BeginsWith("year"))
      fYear = (((TObjString *) (tok.Tokenize("="))->At(1))->GetString()).Atoi();
    if(tok.BeginsWith("mode"))
      fMode = ((TObjString *) (tok.Tokenize("="))->At(1))->GetString();
    if(tok.BeginsWith("index"))
      fIndex = (((TObjString *) (tok.Tokenize("="))->At(1))->GetString()).Atoi();
    if(tok.BeginsWith("total"))
      fTotal = (((TObjString *) (tok.Tokenize("="))->At(1))->GetString()).Atoi();
    if(tok.BeginsWith("syst"))
      fSyst = ((TObjString *) (tok.Tokenize("="))->At(1))->GetString();
    if(tok.BeginsWith("aod"))
      isNanoAOD = (((TObjString *) (tok.Tokenize("="))->At(1))->GetString() == "mini") ? false : true;
    if(tok.BeginsWith("trs"))
      doTreeSave = (((TObjString *) (tok.Tokenize("="))->At(1))->GetString() == "yes") ? true : false;
  }
  fSyst.ToLower();
  fIndex++;

  if(fSample.BeginsWith("Data")){
    fSampleDir = "data_obs";
    isData = true;
  }else{
    fSampleDir = fSample;
    isData = false;
  }
  
  TString hostname = gSystem->HostName();
  if(fMode.Contains("proof")){
    if(hostname.BeginsWith("Indra-Rjn"))
      fBasePath = "/Data/CMS-Analysis/NanoAOD-Analysis/Git_KinFit_Skim/KinFit_Skim/CBA_Skim";
    else if(hostname.BeginsWith("lxplus"))
      fBasePath = "/afs/cern.ch/user/i/idas/CMS-Analysis/NanoAOD-Analysis";
    else if(hostname.BeginsWith("ui"))
      fBasePath = "/home/idas/t3store3/NanoAOD-Analysis";
    else if(hostname.BeginsWith("lnx3"))
      fBasePath = "/home/indra/CMS-Analysis/NanoAOD-Analysis/KinFit_Skim/CBA_Skim";
    //fBasePath += "/SkimAna";
  }else{
    fBasePath = gSystem->pwd();
  }
  
}
//_____________________________________________________________________________
void SkimAna::SelectSyst()
{
  
  puvar012_g		= 1 ;		// 0:down, 1:norm, 2:up
  mueffvar012_g		= 1 ;		// 0:down, 1:norm, 2:up
  eleeffvar012_g	= 1 ;		// 0:down, 1:norm, 2:up
  btagbvar012_g		= 1 ;		// 0:down, 1:norm, 2:up
  btaglvar012_g		= 1 ;		// 0:down, 1:norm, 2:up
  pdfvar012_g		= 1 ;		// 0:down, 1:norm, 2:up
  q2var012_g		= 1 ;		// 0:down, 1:norm, 2:up
  fsrvar012_g		= 1 ;		// 0:down, 1:norm, 2:up
  isrvar012_g		= 1 ;		// 0:down, 1:norm, 2:up
  prefirevar012_g	= 1 ;           // 0:down, 1:norm, 2:up
  btagSystType		= "central" ;

  jecvar012_g		= 1 ;		// 0:down, 1:norm, 2:up
  jervar012_g		= 1 ;		// 0:down, 1:norm, 2:up

  fNSyst = 28 ; 
  fSystList = new char*[fNSyst];
  const char *syst[] = {"base", 
			"puup", "pudown", "mueffup", "mueffdown", 
			"eleeffup", "eleeffdown",  "jecup", "jecdown", 
			"jerup", "jerdown", "btagbup", "btagbdown", 
			"btaglup", "btagldown", "prefireup", "prefiredown",
			"pdfup", "pdfdown", "q2fup", "q2down",
			"isrup", "isrdown", "fsrup", "fsrdown",
			"iso20", "metup", "metdown"};

  for(int isyst=0;isyst<fNSyst;isyst++){
    fSystList[isyst] = new char[20];
    strcpy(fSystList[isyst],syst[isyst]);
  }
  
  if (fSyst == "base"){

    systType = kBase ;
    Info("SelectSyst","Syst : %s", fSyst.Data()); 

  } else if (fSyst == "jecup") {
    
    systType = kJECUp;
    jecvar012_g = 2;      
    Info("SelectSyst","Syst : %s", fSyst.Data()); 
    
  } else if (fSyst == "jecdown") {
    
    systType = kJECDown;
    jecvar012_g = 0;      
    Info("SelectSyst","Syst : %s", fSyst.Data()); 
    
  } else if (fSyst == "jerup") {

    systType = kJERUp;
    jervar012_g = 2;      
    Info("SelectSyst","Syst : %s", fSyst.Data()); 
    
  } else if (fSyst == "jerdown") {

    systType = kJERDown;
    jervar012_g = 0;      
    Info("SelectSyst","Syst : %s", fSyst.Data()); 

  } else if (fSyst == "iso20") {
    
    systType = kIso20;    
    Info("SelectSyst","Syst : %s", fSyst.Data()); 
    
  } else if (fSyst == "metup") {

    systType = kMETUp;
    Info("SelectSyst","Syst : %s", fSyst.Data()); 
    
  } else if (fSyst == "metdown") {
    
    systType = kMETDown;
    Info("SelectSyst","Syst : %s", fSyst.Data()); 

  }


  
}

//_____________________________________________________________________________
void SkimAna::SetTrio()
{
  
  //event = new EventTree(nFiles, false, Form("%d",fYear), isData, fileNames);
  event = new EventTree();
  selector = new Selector();    
  evtPick = new EventPick("");
  
  selector->year = Form("%d",fYear);
  selector->looseJetID = false;
  selector->smearJetPt = true; // default setting was false for cutflow and for prining jet pt
  selector->useDeepCSVbTag = (isNanoAOD) ? true : false ;
  selector->JECsystLevel = jecvar012_g;
  selector->JERsystLevel = jervar012_g;
  selector->isNanoAOD = isNanoAOD ;
  
  //selector->QCDselect = true ;
  selector->DDselect = true ;
  selector->mu_RelIso_loose = 0.4;

  if(systType == kMETUp){
    selector->METUnc = 1.0;
    selector->selectMETUnc = true;
  }else if(systType == kMETDown){
    selector->METUnc = -1.0;
    selector->selectMETUnc = true;    
  }else{
    selector->METUnc = 0.0;
    selector->selectMETUnc = false;    
  }
  
  // Cuts used for results presented at PAG dated August, 02, 2021
  // selector->mu_Pt_cut = 30.;
  // selector->mu_Eta_tight = 2.4;
  // selector->ele_Pt_cut = 35.;
  // selector->ele_Eta_cut = 2.4;
  // selector->jet_Pt_cut = 30.;
  // selector->jet_Eta_cut = 2.4;
  
  if(fYear==2016){
    
    selector->mu_Pt_cut = 30.;
    selector->mu_Eta_tight = 2.4;
    selector->ele_Pt_cut = 35.;
    selector->ele_Eta_cut = 2.4;
    selector->jet_Pt_cut = 30.;
    selector->jet_Eta_cut = 2.4;
    
    // selector->mu_Pt_cut = 26.;
    // selector->mu_Eta_tight = 2.4;
    // selector->ele_Pt_cut = 30.;
    // selector->ele_Eta_cut = 2.4;
    // selector->jet_Pt_cut = 25.;
    // selector->jet_Eta_cut = 2.4;
    
  }else if(fYear==2017){
    selector->mu_Pt_cut = 30.;
    selector->mu_Eta_tight = 2.4;
    selector->ele_Pt_cut = 35.;
    selector->ele_Eta_cut = 2.4;
    selector->jet_Pt_cut = 25.;
    selector->jet_Eta_cut = 2.4;
  }else if(fYear==2018){
    selector->mu_Pt_cut = 26.;
    selector->mu_Eta_tight = 2.4;
    selector->ele_Pt_cut = 35.;
    selector->ele_Eta_cut = 2.4;
    selector->jet_Pt_cut = 25.;
    selector->jet_Eta_cut = 2.4;
  }
  
  evtPick->year = Form("%d",fYear);
  evtPick->Njet_ge = 2;
  evtPick->NBjet_ge = 0;
  evtPick->applyMetFilter = true; 
  // bool applyHemVeto=true; 
  
  if (selector->useDeepCSVbTag){
    // While changing cut to L,M,T make sure to change the efficiency file
    //Light
    // if (fYear==2016) selector->btag_cut_DeepCSV = 0.2217; 
    // if (fYear==2017) selector->btag_cut_DeepCSV = 0.1522;
    // if (fYear==2018) selector->btag_cut_DeepCSV = 0.1241;
    //Medium
    if (fYear==2016) selector->btag_cut_DeepCSV = 0.6321; 
    if (fYear==2017) selector->btag_cut_DeepCSV = 0.4941;
    if (fYear==2018) selector->btag_cut_DeepCSV = 0.4184;
    // //Tight
    // if (fYear==2016) selector->btag_cut_DeepCSV = 0.8953; 
    // if (fYear==2017) selector->btag_cut_DeepCSV = 0.8001;
    // if (fYear==2018) selector->btag_cut_DeepCSV = 0.7527;
    selector->btag_cut = 1.0;
    kinFit.SetBtagThresh(selector->btag_cut_DeepCSV);
  }else{
    // CSVv2M
    if (fYear==2016) selector->btag_cut = 0.8484 ;
    if (fYear==2017) selector->btag_cut = 0.8838 ;
    if (fYear==2018) selector->btag_cut = 0.8838 ;
    selector->btag_cut_DeepCSV = 1.0;
    // Twiki not found for WP recommendation for CSVv2 for 2018;
    kinFit.SetBtagThresh(selector->btag_cut);
  }
  
  float mTop = 172.76;
  kinFit.SetTopMass(mTop);
  
}


//_____________________________________________________________________________
void SkimAna::GetNumberofEvents()
{
  ifstream fin(Form("%s/%s",fBasePath.Data(),fFileName.Data()));
  string s;
  
  totEvents.clear();
  totEventsUS.clear();
  fnameList.clear();
  std::map<std::string, vector<double> >::iterator crossIt;
  for(crossIt = crossSections.begin(); crossIt != crossSections.end(); crossIt++)
    totEvents[crossIt->first] = 0.0;
  
  while(getline(fin,s)){
    
    Info("GetNumberofEvents", "filename : %s", s.c_str());
    
    string sample = s.substr(s.find_last_of("/")+1,s.size());    
    if(sample.find("_ext4_Skim") != string::npos)
      sample = sample.substr(0,sample.find("_ext4_Skim"));
    else if (sample.find("_ext3_Skim") != string::npos)
      sample = sample.substr(0,sample.find("_ext3_Skim"));
    else if (sample.find("_ext2_Skim") != string::npos)
      sample = sample.substr(0,sample.find("_ext2_Skim"));
    else if (sample.find("_ext1_Skim") != string::npos)
      sample = sample.substr(0,sample.find("_ext1_Skim"));
    else if (sample.find("_Skim") != string::npos)
      sample = sample.substr(0,sample.find("_Skim"));
    
    TFile *file = TFile::Open(s.c_str(),"read");
    TH1D *hEvents = (TH1D*) file->Get("hEvents");
    double nMC_thisFile = (hEvents->GetBinContent(2)); //sum of gen weights
    
    totEvents[sample] += nMC_thisFile;
    totEventsUS[sample] += hEvents->GetEntries()/2.0;
    fnameList[sample].push_back(s);

    file->Close();
    delete file;
  }
  fin.close();

  LumiWZ.clear();
  map<string,double>::iterator evIt;
  for(evIt = totEvents.begin(); evIt != totEvents.end(); evIt++){
    if(evIt->second > 0.0){
      cout<<"sample  \""<< evIt->first <<"\" has number of events = " << evIt->second << endl;
      if(fSample.Contains("Wjets")){
	double kf  = 1.21377; 
	LumiWZ[evIt->first] = totEventsUS[evIt->first] / ( kf * crossSections[evIt->first].at(0)); // Here at(0) is for year 2016, but we consider it same for all years
      }
      if(fSample.Contains("DYjets")){
	double kf  = 1.1777; 
	LumiWZ[evIt->first] = totEventsUS[evIt->first] / ( kf * crossSections[evIt->first].at(0)); // Here at(0) is for year 2016, but we consider it same for all years
      }
    }
  }

  if (fYear==2016) {
    luminosity = 35921.875595;
    lumiFracI  = 19.695422959/35.921875595 ;
    lumiFracII = 16.226452636/35.921875595 ;
  }
  if (fYear==2017) {
    luminosity = 41529.548819;
    lumiFracI  = 1.;
    lumiFracII = 1.;
  }
  if (fYear==2018) {
    luminosity = 59740.565202;
    lumiFracI  = 8.950818835/59.740565202;
    lumiFracII = 50.789746366/59.740565202;
  }
  
}

//_____________________________________________________________________________
void SkimAna::LoadPU()
{
  
  std::string PUfilename; 
  std::string PUfilename_up;
  std::string PUfilename_down;
  
  if (fYear==2016){
    PUfilename      = Form("%s/weight/PileupSF/Data_2016BCDGH_Pileup.root", fBasePath.Data()) ;
    PUfilename_up   = Form("%s/weight/PileupSF/Data_2016BCDGH_Pileup_scaledUp.root", fBasePath.Data()) ;
    PUfilename_down = Form("%s/weight/PileupSF/Data_2016BCDGH_Pileup_scaledDown.root", fBasePath.Data()) ;
  }
  if (fYear==2017){
    PUfilename      = Form("%s/weight/PileupSF/Data_2017BCDEF_Pileup.root", fBasePath.Data()) ;
    PUfilename_up   = Form("%s/weight/PileupSF/Data_2017BCDEF_Pileup_scaledUp.root", fBasePath.Data()) ;
    PUfilename_down = Form("%s/weight/PileupSF/Data_2017BCDEF_Pileup_scaledDown.root", fBasePath.Data()) ;
  }
  if (fYear==2018){
    PUfilename      = Form("%s/weight/PileupSF/Data_2018ABCD_Pileup.root", fBasePath.Data()) ;
    PUfilename_up   = Form("%s/weight/PileupSF/Data_2018ABCD_Pileup_scaledUp.root", fBasePath.Data()) ;
    PUfilename_down = Form("%s/weight/PileupSF/Data_2018ABCD_Pileup_scaledDown.root", fBasePath.Data()) ;
  }
  
  vector<string> fnames = fnameList[fSampleType.Data()];
  unsigned int maxArraySize = 0;
  vector<string>::iterator fnIt;
  for(fnIt = fnames.begin(); fnIt != fnames.end(); fnIt++){
    string s = *fnIt;
    if(s.size()>maxArraySize)
      maxArraySize = s.size();
  }
  nFiles = int(fnames.size());
  fileNames = new char*[nFiles];
  for(int i = 0; i < nFiles; i++){
    fileNames[i] = new char[maxArraySize+2];
    strcpy(fileNames[i],fnames.at(i).c_str());
  }
  fnames.clear();
  
  PUweighterUp = new PUReweight(nFiles, fileNames, PUfilename_up);
  PUweighterDown = new PUReweight(nFiles, fileNames, PUfilename_down);
  PUweighter = new PUReweight(nFiles, fileNames, PUfilename);
  
  for(int i = 0; i < nFiles; i++) 
    delete [] fileNames[i];
  delete [] fileNames;

}

//_____________________________________________________________________________
void SkimAna::LoadJECJER()
{
  if (!isData){
    if (fYear==2016) selector->init_JER( Form("%s/weight/JetSF/JER/Summer16_25nsV1",fBasePath.Data()) );
    if (fYear==2017) selector->init_JER( Form("%s/weight/JetSF/JER/Fall17_V3",fBasePath.Data()) );
    if (fYear==2018) selector->init_JER( Form("%s/weight/JetSF/JER/Autumn18_V7b",fBasePath.Data()) );
    
  
    if (systType == kJECUp or systType == kJECDown) { // if (isMC && jecvar012_g!=1) {
      //		jecvar = new JECvariation("weight/JetSF/Summer16_23Sep2016V4", isMC, "Total");//SubTotalAbsolute");
      //cout << "Applying JEC uncertainty variations : " << JECsystLevel << endl;
      string JECsystLevel = "Total";
      if (std::end(allowedJECUncertainties) == std::find(std::begin(allowedJECUncertainties), std::end(allowedJECUncertainties), JECsystLevel)){
            cout << "The JEC systematic source, " << JECsystLevel << ", is not in the list of allowed sources (found in JEC/UncertaintySourcesList.h" << endl;
            cout << "Exiting" << endl;
            return;
      }
      if (fYear==2016) jecvar = new JECvariation( Form("%s/weight/JetSF/Summer16_07Aug2017_V11",fBasePath.Data()), !isData, JECsystLevel);
      if (fYear==2017) jecvar = new JECvariation( Form("%s/weight/JetSF/Fall17_17Nov2017_V32",fBasePath.Data()), !isData, JECsystLevel);
      if (fYear==2018) jecvar = new JECvariation( Form("%s/weight/JetSF/Autumn18_V19",fBasePath.Data()), !isData, JECsystLevel);
      cout << "Here I am " << endl;
    }
  }//isData

}

//_____________________________________________________________________________
void SkimAna::LoadBTag()
{
  
  if(isData)
    return ;

  Info("LoadBTag","Begin");
  // DeepCSV
  
  if (!selector->useDeepCSVbTag){
    Info("LoadBTag","CSVV2 calibration has been selected");
    if (fYear==2016) calib = BTagCalibration("csvv2", Form("%s/weight/BtagSF/CSVv2_Moriond17_B_H.csv",fBasePath.Data()));
    if (fYear==2017) calib = BTagCalibration("csvv2", Form("%s/weight/BtagSF/CSVv2_94XSF_V2_B_F.csv",fBasePath.Data()));
    if (fYear==2018) calib = BTagCalibration("csvv2", Form("%s/weight/BtagSF/CSVv2_94XSF_V2_B_F.csv",fBasePath.Data()));
    Info("LoadBTag","CSVV2 calibration has been loaded");
  } else {
    Info("LoadBTag","DeepCSV calibration has been selected");
    // if (fYear==2016){ calib = BTagCalibration( "deepcsv", Form("%s/weight/BtagSF/DeepCSV_2016LegacySF_V1.csv",fBasePath.Data()) ) ;}
    // if (fYear==2017){ calib = BTagCalibration( "deepcsv", Form("%s/weight/BtagSF/DeepCSV_94XSF_V3_B_F.csv",fBasePath.Data()) ) ;}
    // if (fYear==2018){ calib = BTagCalibration( "deepcsv", Form("%s/weight/BtagSF/DeepCSV_102XSF_V1.csv",fBasePath.Data()) ) ;} //DeepCSV_102XSF_V1.csv  
    if (fYear==2016){ 
      Info("LoadBTag","DeepCSV calibration has been selected : 2016");
      
      // if(fSample.BeginsWith("TTbar") or fSample.BeginsWith("singleTop")){
      // 	calib = BTagCalibration( "deepcsv", Form("%s/weight/BtagSF/new/DeepCSV_2016LegacySF_V1_TuneCP5.csv",fBasePath.Data()) ) ;
      // 	Info("LoadBTag","%s/weight/BtagSF/new/DeepCSV_2016LegacySF_V1_TuneCP5.csv",fBasePath.Data());
      // }else{
      // 	calib = BTagCalibration( "deepcsv", Form("%s/weight/BtagSF/new/DeepCSV_2016LegacySF_V1.csv",fBasePath.Data()) ) ;
      // 	Info("LoadBTag","%s/weight/BtagSF/new/DeepCSV_2016LegacySF_V1.csv",fBasePath.Data());
      // }
      
      // A temporary workaround the proper implementation should be like above
      calib = BTagCalibration( "deepcsv", Form("%s/weight/BtagSF/new/DeepCSV_2016LegacySF_V1.csv",fBasePath.Data()) ) ;
      Info("LoadBTag","%s/weight/BtagSF/new/DeepCSV_2016LegacySF_V1.csv",fBasePath.Data());

    }
    if (fYear==2017){ 
      Info("LoadBTag","DeepCSV calibration has been selected : 2017 %s",fBasePath.Data());
      calib = BTagCalibration( "deepcsv", Form("%s/weight/BtagSF/new/DeepCSV_94XSF_V5_B_F.csv",fBasePath.Data()) ) ;
      Info("LoadBTag","%s/weight/BtagSF/new/DeepCSV_94XSF_V5_B_F.csv",fBasePath.Data());
    }
    if (fYear==2018){ 
      Info("LoadBTag","DeepCSV calibration has been selected : 2018");
      calib = BTagCalibration( "deepcsv", Form("%s/weight/BtagSF/new/DeepCSV_102XSF_V2.csv",fBasePath.Data()) ) ;
      Info("LoadBTag","%s/weight/BtagSF/new/DeepCSV_102XSF_V2.csv",fBasePath.Data());
    } //DeepCSV_102XSF_V1.csv  
  }
  
  reader = BTagCalibrationReader(BTagEntry::OP_MEDIUM, "central", {"up", "down"});
  
  reader.load(calib, BTagEntry::FLAV_B,"comb");          
  reader.load(calib, BTagEntry::FLAV_C, "comb"); 
  reader.load(calib, BTagEntry::FLAV_UDSG, "incl"); 
  
  //string year = "2016";
  std::string fName = "" ;
  if(!selector->useDeepCSVbTag){ //CSVV2
    if(fSample.BeginsWith("MCQCD"))
      fName = Form("%s/weight/BtagSF/btag_efficiencies_%d.root",fBasePath.Data(),fYear);
    else
      fName = Form("%s/weight/BtagSF/Efficiency/MiniAOD/CSVV2/%s_btag_efficiency.root",fBasePath.Data(),fSample.Data());
  }else{ //DeepCSV
    
    // if(fSample.BeginsWith("TTbar") or fSample.BeginsWith("Hplus"))
    //   fName = Form("%s/weight/BtagSF/Efficiency/NanoAOD/DeepCSV/%d/TTB_btag_efficiency_%d.root",fBasePath.Data(),fYear,fYear);    
    // else
    //   fName = Form("%s/weight/BtagSF/Efficiency/NanoAOD/DeepCSV/%d/Others_btag_efficiency_%d.root",fBasePath.Data(),fYear,fYear);    
    
    fName = Form("%s/weight/BtagSF/Efficiency/NanoAOD/DeepCSV/%d/%s_btag_efficiency_%d.root",fBasePath.Data(),fYear,fSample.Data(),fYear);    
  }
  Info("LoadBTag","Efficientcy file : %s",fName.c_str());
  Info("LoadBTag","Btag threshold : %lf",((selector->useDeepCSVbTag) ? selector->btag_cut_DeepCSV  : selector->btag_cut));
  
  std::string effType = "Other";
  // if (fSample.BeginsWith("TTbar"))
  //   effType = "Top";
  
  std::string leffName = effType+"_l_efficiency";
  std::string ceffName = effType+"_c_efficiency";
  std::string beffName = effType+"_b_efficiency";
  
  TFile* inputFile = TFile::Open(fName.c_str(),"read");
  l_eff = (TH2D*) inputFile->Get(leffName.c_str());
  c_eff = (TH2D*) inputFile->Get(ceffName.c_str());
  b_eff = (TH2D*) inputFile->Get(beffName.c_str());
  
}

//_____________________________________________________________________________
void SkimAna::LoadLeptonSF(){

  if (fYear==2016){
    if(isNanoAOD){
      muSFa = new MuonSF(Form("%s/weight/MuEleSF/mu2016/EfficienciesStudies_2016_legacy_rereco_rootfiles_RunBCDEF_SF_ID.root",fBasePath.Data()), 
			 "NUM_TightID_DEN_genTracks_eta_pt",
			 Form("%s/weight/MuEleSF/mu2016/EfficienciesStudies_2016_legacy_rereco_rootfiles_RunBCDEF_SF_ISO.root",fBasePath.Data()), 
			 "NUM_TightRelIso_DEN_TightIDandIPCut_eta_pt",
			 Form("%s/weight/MuEleSF/mu2016/EfficienciesStudies_2016_trigger_EfficienciesAndSF_RunBtoF.root",fBasePath.Data()), 
			 "IsoMu24_OR_IsoTkMu24_PtEtaBins/abseta_pt_ratio");
      
      muSFb = new MuonSF(Form("%s/weight/MuEleSF/mu2016/EfficienciesStudies_2016_legacy_rereco_rootfiles_RunGH_SF_ID.root",fBasePath.Data()), 
			 "NUM_TightID_DEN_genTracks_eta_pt",
			 Form("%s/weight/MuEleSF/mu2016/EfficienciesStudies_2016_legacy_rereco_rootfiles_RunGH_SF_ISO.root",fBasePath.Data()), 
			 "NUM_TightRelIso_DEN_TightIDandIPCut_eta_pt",
			 Form("%s/weight/MuEleSF/mu2016/EfficienciesStudies_2016_trigger_EfficienciesAndSF_RunGtoH.root",fBasePath.Data()), 
			 "IsoMu24_OR_IsoTkMu24_PtEtaBins/abseta_pt_ratio");
      
      eleSF = new ElectronSF(Form("%s/weight/MuEleSF/ele2016/2016LegacyReReco_ElectronTight_Fall17V2.root",fBasePath.Data()),
			     Form("%s/weight/MuEleSF/ele2016/EGM2D_BtoH_GT20GeV_RecoSF_Legacy2016.root",fBasePath.Data()),
			     Form("%s/weight/MuEleSF/ele2016/sf_ele_2016_trig_v5.root",fBasePath.Data()));
    }else{

      muSFa = new MuonSF(Form("%s/weight/MuEleSF/mu2016/EfficienciesStudies_2016_legacy_rereco_rootfiles_RunBCDEF_SF_ID.root",fBasePath.Data()), 
			 "NUM_MediumID_DEN_genTracks_eta_pt",
			 Form("%s/weight/MuEleSF/mu2016/EfficienciesStudies_2016_legacy_rereco_rootfiles_RunBCDEF_SF_ISO.root",fBasePath.Data()), 
			 "NUM_TightRelIso_DEN_MediumID_eta_pt",
			 Form("%s/weight/MuEleSF/mu2016/EfficienciesStudies_2016_trigger_EfficienciesAndSF_RunBtoF.root",fBasePath.Data()), 
			 "IsoMu24_OR_IsoTkMu24_PtEtaBins/abseta_pt_ratio");
      
      muSFb = new MuonSF(Form("%s/weight/MuEleSF/mu2016/EfficienciesStudies_2016_legacy_rereco_rootfiles_RunGH_SF_ID.root",fBasePath.Data()), 
			 "NUM_MediumID_DEN_genTracks_eta_pt",
			 Form("%s/weight/MuEleSF/mu2016/EfficienciesStudies_2016_legacy_rereco_rootfiles_RunGH_SF_ISO.root",fBasePath.Data()), 
			 "NUM_TightRelIso_DEN_MediumID_eta_pt",
			 Form("%s/weight/MuEleSF/mu2016/EfficienciesStudies_2016_trigger_EfficienciesAndSF_RunGtoH.root",fBasePath.Data()), 
			 "IsoMu24_OR_IsoTkMu24_PtEtaBins/abseta_pt_ratio");
      
      // f_trackSF_BCDEF 	= new TFile(Form("%s/../../../Analysis/Analysis/stack/muonSF/trackingSF_BCDEF.root",fBasePath.Data()));
      // f_trackSF_GH	= new TFile(Form("%s/../../../Analysis/Analysis/stack/muonSF/trackingSF_GH.root",fBasePath.Data()));
      f_trackSF_BCDEF 	= new TFile(Form("%s/weight/MuEleSF/mu2016_mini/trackingSF_BCDEF.root",fBasePath.Data()));
      f_trackSF_GH	= new TFile(Form("%s/weight/MuEleSF/mu2016_mini/trackingSF_GH.root",fBasePath.Data()));

      tg_trackSF_BCDEF 	= (TGraphAsymmErrors*)f_trackSF_BCDEF->Get("ratio_eff_aeta_dr030e030_corr");
      tg_trackSF_GH 	= (TGraphAsymmErrors*)f_trackSF_GH->Get("ratio_eff_aeta_dr030e030_corr");
      
      //eleSF may not be currect for MiniAOD, take care.
      eleSF = new ElectronSF(Form("%s/weight/MuEleSF/ele2016/2016LegacyReReco_ElectronMedium_Fall17V2.root",fBasePath.Data()),
			     Form("%s/weight/MuEleSF/ele2016/EGM2D_BtoH_GT20GeV_RecoSF_Legacy2016.root",fBasePath.Data()),
			     Form("%s/weight/MuEleSF/ele2016/sf_ele_2016_trig_v5.root",fBasePath.Data()));
      
    }
  } else if (fYear==2017) {
	
    muSFa = new MuonSF(Form("%s/weight/MuEleSF/mu2017/RunBCDEF_SF_ID.root",fBasePath.Data()), "NUM_TightID_DEN_genTracks_pt_abseta",
		       Form("%s/weight/MuEleSF/mu2017/RunBCDEF_SF_ISO.root",fBasePath.Data()), "NUM_TightRelIso_DEN_TightIDandIPCut_pt_abseta",
		       Form("%s/weight/MuEleSF/mu2017/EfficienciesAndSF_RunBtoF_Nov17Nov2017.root",fBasePath.Data()), "IsoMu27_PtEtaBins/abseta_pt_ratio");
	
    eleSF = new ElectronSF(Form("%s/weight/MuEleSF/ele2017/2017_ElectronTight.root",fBasePath.Data()),
			   Form("%s/weight/MuEleSF/ele2017/egammaEffi.txt_EGM2D_runBCDEF_passingRECO.root",fBasePath.Data()),
			   Form("%s/weight/MuEleSF/ele2017/sf_ele_2017_trig_v5.root",fBasePath.Data()));

  } else if (fYear==2018) {

    muSFa = new MuonSF(Form("%s/weight/MuEleSF/mu2018/EfficienciesStudies_2018_rootfiles_RunABCD_SF_ID.root",fBasePath.Data()),  
		       "NUM_TightID_DEN_TrackerMuons_pt_abseta",
		       Form("%s/weight/MuEleSF/mu2018/EfficienciesStudies_2018_rootfiles_RunABCD_SF_ISO.root",fBasePath.Data()), 
		       "NUM_TightRelIso_DEN_TightIDandIPCut_pt_abseta",
		       Form("%s/weight/MuEleSF/mu2018/EfficienciesStudies_2018_trigger_EfficienciesAndSF_2018Data_BeforeMuonHLTUpdate.root",fBasePath.Data()), 
		       "IsoMu24_PtEtaBins/abseta_pt_ratio");
    
    muSFb = new MuonSF(Form("%s/weight/MuEleSF/mu2018/EfficienciesStudies_2018_rootfiles_RunABCD_SF_ID.root",fBasePath.Data()),  
		       "NUM_TightID_DEN_TrackerMuons_pt_abseta",
		       Form("%s/weight/MuEleSF/mu2018/EfficienciesStudies_2018_rootfiles_RunABCD_SF_ISO.root",fBasePath.Data()), 
		       "NUM_TightRelIso_DEN_TightIDandIPCut_pt_abseta",
		       Form("%s/weight/MuEleSF/mu2018/EfficienciesStudies_2018_trigger_EfficienciesAndSF_2018Data_AfterMuonHLTUpdate.root",fBasePath.Data()), 
		       "IsoMu24_PtEtaBins/abseta_pt_ratio");
    
    eleSF = new ElectronSF(Form("%s/weight/MuEleSF/ele2018/2018_ElectronTight.root",fBasePath.Data()),
			   Form("%s/weight/MuEleSF/ele2018/egammaEffi.txt_EGM2D_updatedAll.root",fBasePath.Data()),
			   Form("%s/weight/MuEleSF/ele2018/sf_ele_2018_trig_v5.root",fBasePath.Data()));
  }

}
//_____________________________________________________________________________
void SkimAna::GetBtagSF_1a(){
  
  double jetPt;
  double jetEta;
  double jetBtag;
  int jetFlavor;
  double SFb;
  double Eff;

  double pMC = 1.0;
  double pData = 1.0;
	
  string b_sysType = "central";
  string l_sysType = "central";
  if (btagSystType=="b_up"){
    b_sysType = "up";
  } else if (btagSystType=="b_down"){
    b_sysType = "down";
  } else if (btagSystType=="l_up"){
    l_sysType = "up";
  } else if (btagSystType=="l_down"){
    l_sysType = "down";
  }	
  
  double btagThreshold = (selector->useDeepCSVbTag) ? selector->btag_cut_DeepCSV  : selector->btag_cut  ;
  
  int xbin,ybin;
  int maxbinX, maxbinY;
  
  for(std::vector<int>::const_iterator jetInd = selector->Jets.begin(); jetInd != selector->Jets.end(); jetInd++){
    
    jetPt = event->jetPt_[*jetInd];
    jetEta = fabs(event->jetEta_[*jetInd]);
    jetFlavor = abs(event->jetPartFlvr_[*jetInd]);
    //jetFlavor = abs(event->jetHadFlvr_[*jetInd]);
    jetBtag = (selector->useDeepCSVbTag) ? event->jetBtagDeepB_[*jetInd] : event->jetBtagCSVV2_[*jetInd] ;

    if (jetFlavor == 5){
      SFb = reader.eval_auto_bounds(b_sysType, BTagEntry::FLAV_B, jetEta, jetPt); 
      xbin = b_eff->GetXaxis()->FindBin(min(jetPt,799.));
      ybin = b_eff->GetYaxis()->FindBin(abs(jetEta));
      maxbinX = b_eff->GetXaxis()->GetLast();
      maxbinY = b_eff->GetYaxis()->GetLast();
      Eff = b_eff->GetBinContent(xbin,ybin);
    }
    else if(jetFlavor == 4){
      SFb = reader.eval_auto_bounds(b_sysType, BTagEntry::FLAV_C, jetEta, jetPt); 
      xbin = c_eff->GetXaxis()->FindBin(min(jetPt,799.));
      ybin = c_eff->GetYaxis()->FindBin(abs(jetEta));
      maxbinX = c_eff->GetXaxis()->GetLast();
      maxbinY = c_eff->GetYaxis()->GetLast();
      Eff = c_eff->GetBinContent(xbin,ybin);
    }
    else {
      SFb = reader.eval_auto_bounds(l_sysType, BTagEntry::FLAV_UDSG, jetEta, jetPt); 
      xbin = l_eff->GetXaxis()->FindBin(min(jetPt,799.));
      ybin = l_eff->GetYaxis()->FindBin(abs(jetEta));
      maxbinX = l_eff->GetXaxis()->GetLast();
      maxbinY = l_eff->GetYaxis()->GetLast();
      Eff = l_eff->GetBinContent(xbin,ybin);
    }
	
    if( (xbin==0 or xbin>maxbinX or ybin==0 or ybin>maxbinY) and TMath::AreEqualAbs(Eff,0.0,1.0e-7) ) continue;

    if (jetBtag > btagThreshold ){
      pMC *= Eff;
      pData *= Eff*SFb;
    } else {
      pMC *= 1. - Eff;
      pData *= 1. - (Eff*SFb);
    }
  }//end of jet loop
  
  //   _bTagWeight = pData/pMC;
  if ( TMath::AreEqualAbs(pMC,0.0,1.0e-7) )
    _bTagWeight = 0.;
  else 
    _bTagWeight = pData/pMC;

}

//_____________________________________________________________________________
void SkimAna::GetMuonEff(double iso){

  int muInd_ = selector->MuonsNoIso.at(0);
  
  if (fYear==2016){
    vector<double> muWeights_a    = muSFa->getMuSF(event->muPt_[muInd_],event->muEta_[muInd_], mueffvar012_g, 2016);
    vector<double> muWeights_b    = muSFb->getMuSF(event->muPt_[muInd_],event->muEta_[muInd_], mueffvar012_g, 2016);
    vector<double> muWeights;

    for (int i=0; i < int(muWeights_a.size()); i++)
      muWeights.push_back( muWeights_a.at(i)*lumiFracI + muWeights_b.at(i)*lumiFracII );    
    
    if(isNanoAOD){
      _muEffWeight = (iso < 0.15) ? muWeights.at(0) : (muWeights.at(1) * muWeights.at(3));  // if iso>=0.15 then exclude iso eff at(2)
    }else{
      double muSFtrack_BCDEF 	= getMuonTrackSF(tg_trackSF_BCDEF, event->muEta_[muInd_]);
      double muSFtrack_GH 	= getMuonTrackSF(tg_trackSF_GH, event->muEta_[muInd_]);
      double muSFtrack 		= muSFtrack_BCDEF*lumiFracI + muSFtrack_GH*lumiFracII;

      if(iso<0.15)
	_muEffWeight    = muWeights.at(1) * muWeights.at(2) * muWeights.at(3) * muSFtrack; //id * iso * trig * track
      else
	_muEffWeight    = muWeights.at(1) * muWeights.at(3) * muSFtrack; //id * trig * track
    }

    muWeights_a.clear(); muWeights_b.clear(); muWeights.clear();
  }
  if (fYear==2017){    
    vector<double> muWeights    = muSFa->getMuSF(event->muPt_[muInd_],event->muEta_[muInd_],mueffvar012_g, 2017);

    _muEffWeight = (iso < 0.15) ? muWeights.at(0) : (muWeights.at(1) * muWeights.at(3)) ;  
    
    muWeights.clear();
  }
  if(fYear==2018){
    vector<double> muWeights_a    = muSFa->getMuSF(event->muPt_[muInd_],event->muEta_[muInd_],mueffvar012_g, 2018);
    vector<double> muWeights_b    = muSFb->getMuSF(event->muPt_[muInd_],event->muEta_[muInd_],mueffvar012_g, 2018);
    vector<double> muWeights;

    for (int i=0; i < int(muWeights_a.size()); i++)
      muWeights.push_back( muWeights_a.at(i)*lumiFracI + muWeights_b.at(i)*lumiFracII );    

    _muEffWeight = (iso < 0.15) ? muWeights.at(0) : (muWeights.at(1) * muWeights.at(3));  // if iso>=0.15 then exclude iso eff at(2)

    muWeights_a.clear(); muWeights_b.clear(); muWeights.clear();
  }
  
}

//_____________________________________________________________________________
void SkimAna::GetElectronEff(){

  int eleInd_ = selector->ElectronsNoIso.at(0);
  vector<double> eleWeights    = eleSF->getEleSF(event->elePt_[eleInd_],event->eleEta_[eleInd_] + event->eleDeltaEtaSC_[eleInd_],eleeffvar012_g);
  _eleEffWeight    = eleWeights.at(0);
  eleWeights.clear();
}

//_____________________________________________________________________________
void SkimAna::Begin(TTree */*tree*/)
{
   // This is needed when re-processing the object
   Reset();
   
   //print the option specified in the Process function.
   TString option = GetOption();
   Info("Begin", "starting SkimAna with process option: %s", option.Data());
   
   //if (fChain) fChain->SetEntryList(0);
}


//_____________________________________________________________________________
void SkimAna::SlaveBegin(TTree *tree)
{  
  //print the option specified in the Process function.
  TString option = GetOption();
  Info("SlaveBegin",
       "starting SkimAna with process option: %s (tree: %p)", option.Data(), tree);
  
  GetArguments();  
  Info("SlaveBegin",
       "sample : %s, year : %d, mode : %s", fSample.Data(), fYear, fMode.Data());

  SelectSyst();
  SetTrio(); // SetTrio method should be after SelectSyst
  // Info("SlaveBegin",
  //      "Chain %p (tree: %p)", event->chain, tree);
  
  //initialize the Tree branch addresses
  Init(tree);
  
  char *filename[3];
  
  filename[0] = Form("%s_hist_%s_%dof%d.root",fSample.Data(),fSyst.Data(),fIndex,fTotal) ;
  filename[1] = Form("%s_tree_%s_%dof%d.root",fSample.Data(),fSyst.Data(),fIndex,fTotal) ;
  
  for(int ifile=0;ifile<2;ifile++){
    
    if(fMode.BeginsWith("proof")){
      fProofFile[ifile] = new TProofOutputFile(filename[ifile], "M");
      fFile[ifile] = fProofFile[ifile]->OpenFile("RECREATE");
      if (fFile[ifile] && fFile[ifile]->IsZombie()) SafeDelete(fFile[ifile]);
    }else{
      fFile[ifile] = TFile::Open(filename[ifile],"RECREATE");
    }
    
    // Cannot continue
    if (!fFile[ifile]) {
      TString amsg = TString::Format("SkimAna::SlaveBegin: could not create '%s':"
				     " instance is invalid!", fFile[ifile]->GetName());
      Abort(amsg, kAbortProcess);
      return;
    }
        
  }//ifile loop

  if(!isData){
    Info("SlaveBegin", "CS Init");
    initCrossSections();
    Info("SlaveBegin", "GetNumber of Events and files");
    GetNumberofEvents();
    
    //LoadPU();
    Info("SlaveBegin", "Loading Lepton SF");
    LoadLeptonSF();
    Info("SlaveBegin", "Loading JEC JER");
    LoadJECJER();
    Info("SlaveBegin", "Loading BTag");
    LoadBTag();
  }
  Info("SlaveBegin", "Create Histos");
  CreateHistoArrays();
  // IsDebug = true;
  // evtPick->IsDebug = true;
  // selector->IsDebug = true;
  Info("SlaveBegin", "End of SlaveBegin");

       

}

//_____________________________________________________________________________
void SkimAna::TheoWeights(){

  _q2weight_Up = 1.;
  _q2weight_Do = 1.;

  if(event->nLHEScaleWeight_ >=9 ){

    vector<float>     genScaleSystWeights;
    vector<float>     q2ScaleSystWeights;
    if (event->nLHEScaleWeight_==9){
      
      double q2Mean = 0.;
      
      for (int j=0; j < int(event->nLHEScaleWeight_); j++ ){
	//if(j==2||j==6){continue;}
	if(j==0||j==2||j==6||j==7){continue;}
	q2ScaleSystWeights.push_back(event->LHEScaleWeight_[j]);
	q2Mean += event->LHEPdfWeight_[j];
      }

      q2Mean = q2Mean/q2ScaleSystWeights.size();

      double q2Variance = 0.;
      for (int j=0; j < int(q2ScaleSystWeights.size()); j++){
	q2Variance += pow((q2ScaleSystWeights[j]-q2Mean),2.);
      }
    
      if (TMath::AreEqualAbs(q2Mean,0.0,1.0e-7)) 
	q2Mean = 1;
    
      double _q2uncer = sqrt(q2Variance/q2ScaleSystWeights.size())/q2Mean;
      double _Q2weight_Up = (1. + _q2uncer);
      double _Q2weight_Do = (1. - _q2uncer);

      for (int i = 0; i < 9; i++){
	//if(i==2||i==6){continue;}
	if(i==0||i==2||i==6||i==7){continue;}
	genScaleSystWeights.push_back(event->LHEScaleWeight_[i]);
      }
      
      // cout << "Event" << endl;
      // for(vector<float>::iterator it = genScaleSystWeights.begin() ; it!=genScaleSystWeights.end() ; ++it)
      // 	cout <<"\t val " << *it << endl;

      double nomWeight=event->LHEScaleWeight_[4];
      if (!TMath::AreEqualAbs(nomWeight,0.0,1.e-7)){
	_q2weight_Up = *max_element(genScaleSystWeights.begin(), genScaleSystWeights.end())/nomWeight;
	_q2weight_Do = *min_element(genScaleSystWeights.begin(), genScaleSystWeights.end())/nomWeight;
      }
      // cout << "norm " << nomWeight  << ", _q2weight_Up : " << _q2weight_Up << ", _q2weight_Do : " << _q2weight_Do << endl; 
      // cout << "q2Mean " << q2Mean << ", _q2weight_Up : " << _Q2weight_Up << ", _q2weight_Do : " << _Q2weight_Do << endl; 
    }
    
    if (event->nLHEScaleWeight_==44){
      genScaleSystWeights.push_back(event->LHEScaleWeight_[0]);
      genScaleSystWeights.push_back(event->LHEScaleWeight_[5]);
      genScaleSystWeights.push_back(event->LHEScaleWeight_[15]);
      genScaleSystWeights.push_back(event->LHEScaleWeight_[24]);
      genScaleSystWeights.push_back(event->LHEScaleWeight_[34]);
      genScaleSystWeights.push_back(event->LHEScaleWeight_[39]);

      _q2weight_Up = *max_element(genScaleSystWeights.begin(), genScaleSystWeights.end());
      _q2weight_Do = *min_element(genScaleSystWeights.begin(), genScaleSystWeights.end());
    }
    genScaleSystWeights.clear();
    q2ScaleSystWeights.clear();
  }
  
  _pdfweight_Up = 1. ;
  _pdfweight_Do = 1. ;
  
  if(event->nLHEPdfWeight_ > 0){
    
    vector<float>	 pdfSystWeight;
    double pdfMean = 0.;

    for (int j=0; j < int(event->nLHEPdfWeight_); j++ ){
      pdfSystWeight.push_back(event->LHEPdfWeight_[j]);
      pdfMean += event->LHEPdfWeight_[j];
    }
    pdfMean = pdfMean/pdfSystWeight.size();
    
    double pdfVariance = 0.;
    for (int j=0; j < int(pdfSystWeight.size()); j++){
      pdfVariance += pow((pdfSystWeight[j]-pdfMean),2.);
    }
    
    if (TMath::AreEqualAbs(pdfMean,0.0,1.0e-7)) 
      pdfMean = 1;
    
    _pdfuncer = sqrt(pdfVariance/pdfSystWeight.size())/pdfMean;
    _pdfweight_Up = (1. + _pdfuncer);
    _pdfweight_Do = (1. - _pdfuncer);
    pdfSystWeight.clear();
  }
  
  _ISRweight_Up = 1.;
  _ISRweight_Do = 1.;
  
  _FSRweight_Up = 1.;
  _FSRweight_Do = 1.;
  
  if (event->nPSWeight_==4){
    if (event->genWeight_ != 0){
      _ISRweight_Up = event->PSWeight_[2];
      _ISRweight_Do = event->PSWeight_[0];
      
      _FSRweight_Up = event->PSWeight_[3];
      _FSRweight_Do = event->PSWeight_[1];
    }
  }


}

//_____________________________________________________________________________
Bool_t SkimAna::Process(Long64_t entry)
{
  // entry is the entry number in the current Tree
  
  // to read complete event, call fChain->GetTree()->GetEntry(entry)  
  fChain->GetTree()->GetEntry(entry);  

  fProcessed++;
  fStatus++;
  
  _sampleWeight	 = 1.0;
  _prefireWeight = 1.0;
  _prefireWeight_Up = 1.0 ;
  _prefireWeight_Do = 1.0 ;
  _PUWeight	 = 1.0;
  _PUWeight_Up	 = 1.0;
  _PUWeight_Do	 = 1.0;
  _muEffWeight = 1.0;
  _muEffWeight_Up = 1.0;
  _muEffWeight_Do = 1.0;
  _eleEffWeight = 1.0;
  _eleEffWeight_Up = 1.0;
  _eleEffWeight_Do = 1.0;
  _bTagWeight	 = 1.0;
  _bTagWeight_b_Up = 1.0 ;
  _bTagWeight_b_Do = 1.0 ;
  _bTagWeight_l_Up = 1.0 ;
  _bTagWeight_l_Do = 1.0 ;

  _topPtReWeight = 1.0;
  _pdfweight_Up = 1.0;
  _pdfweight_Do = 1.0;
  _q2weight_Up = 1.0;
  _q2weight_Do = 1.0;
  _FSRweight_Up = 1.0;
  _FSRweight_Do = 1.0;
  _FSRweight_Up = 1.0;
  _FSRweight_Do = 1.0;

  int mod_num = 10000;

  if(fProcessed%mod_num==0){
    Info("Process","Processing : %lld(%lld) of number of events : %lld and total number of events : %.0lf, year : %s", 
	 fProcessed, entry, fChain->GetEntries(), totEventsUS[fSampleType.Data()],evtPick->year.c_str());
  }
  if(IsDebug) Info("Process","Completed process count");
  
  // Set JEC syst
  if( !isData and (systType == kJECUp or systType == kJECDown)){
    jecvar->applyJEC(event, jecvar012_g); // 0:down, 1:norm, 2:up
  }
  if(IsDebug) Info("Process","Completed JEC correction");

  // //Clear selector vectors
  selector->clear_vectors();
  if(IsDebug) Info("Process","Completed cleaning vectors");

  // This is main method to process the objects read from tree
  evtPick->process_event(fBasePath.Data(), event, selector, 1.0); // here last argument 1.0 is weight applied to cutflow
  if(IsDebug) Info("Process","Completed selector process");

  //Special case of Wjets and DY
  //if(!isNanoAOD and !isData and fSampleType.Contains("Wjets")){
  if(!isData and fSampleType.Contains("Wjets")){
    _local_evtWeight = ScaleLumiW(event->nLHEPart_) * luminosity/1000.;
    if(fProcessed%100000==0)
      Info("Process", "Wjets : Updated special event weight : %lf for nLHEPart_ : %d", _local_evtWeight, event->nLHEPart_);
  }
  
  if(!isData and fSampleType.Contains("DYjetsM50")){
    _local_evtWeight = ScaleLumiZ(event->nLHEPart_) * luminosity/1000.;
    if(fProcessed%100000==0)
      Info("Process", "DYjets : Updated special event weight : %lf for nLHEPart_ : %d", _local_evtWeight, event->nLHEPart_);
  }
  
  if(!isData and (fSampleType.Contains("TTbar") or fSampleType.Contains("Hplus"))){
    SelectTTbarChannel();
  }

  // Sample weight 
  if(!isData)
    _sampleWeight = _local_evtWeight * ((event->genWeight_ >= 0) ? 1.0 : -1.0) ; //_sampleWeight should mimic the MiniAOD

  if(IsDebug) Info("Process","Completed event weight application");

  // Access the prefire weight
  if(!isData){
    _prefireWeight_Up = event->L1PreFiringWeight_Up_ ;
    _prefireWeight_Do = event->L1PreFiringWeight_Dn_ ;
    _prefireWeight = event->L1PreFiringWeight_Nom_ ;
  }
  
  // Access the PU weight
  if(!isData){
    _PUWeight = PUweighter->getWeight(event->nPUTrue_);
    _PUWeight_Up = PUweighterUp->getWeight(event->nPUTrue_);
    _PUWeight_Do = PUweighterDown->getWeight(event->nPUTrue_);
  }
    
  //Event level or trigger level conditions will be placed in block below
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  FillEventCutFlow();
  FillEventWt();
  if(IsDebug) Info("Process","Completed Event filling");
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  //The following setup is able to produce results presented in August-02 PAG
  bool singleMu = (evtPick->passFilter and selector->isPVGood and evtPick->passTrigger_mu and selector->ElectronsNoIso.size() == 0 and selector->ElectronsNoIsoLoose.size() == 0 and selector->MuonsNoIso.size() == 1 and selector->MuonsNoIsoLoose.size() == 0);
  bool singleEle = (evtPick->passFilter and selector->isPVGood and evtPick->passTrigger_ele and selector->ElectronsNoIso.size() == 1 and selector->ElectronsNoIsoLoose.size() == 0 and selector->MuonsNoIso.size() == 0 and selector->MuonsNoIsoLoose.size() == 0);
  
  //////=====================================================
  if(!singleMu and !singleEle) return true;
  //////=====================================================
  
  
  //Processes after single muon/electron selection will be placed in block below
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////

  FillLeptonIso(singleMu, singleEle);

  if(!isData){
    if(singleMu){
      if(fSyst == "base"){
	mueffvar012_g = 2;		// 0:down, 1:norm, 2:up
	GetMuonEff(event->muPFRelIso_[selector->MuonsNoIso.at(0)]);
	_muEffWeight_Up = _muEffWeight;
	
	mueffvar012_g = 0;		// 0:down, 1:norm, 2:up
	GetMuonEff(event->muPFRelIso_[selector->MuonsNoIso.at(0)]);
	_muEffWeight_Do = _muEffWeight;
      }
      mueffvar012_g = 1;		// 0:down, 1:norm, 2:up
      GetMuonEff(event->muPFRelIso_[selector->MuonsNoIso.at(0)]);
    }

    //if(singleMu) GetMuonEff(event->muPFRelIso_[selector->Muons.at(0)]);
  
    if(singleEle){
      if(fSyst == "base"){
	eleeffvar012_g = 2;		// 0:down, 1:norm, 2:up
	GetElectronEff();
	_eleEffWeight_Up = _eleEffWeight;
	
	eleeffvar012_g = 0;		// 0:down, 1:norm, 2:up
	GetElectronEff();
	_eleEffWeight_Do = _eleEffWeight;
      }
      eleeffvar012_g = 1;		// 0:down, 1:norm, 2:up
      GetElectronEff();
    }

  }

  bool muonIsoCut = false;
  bool muonNonIsoCut = false;
  if(singleMu){
    if(systType == kIso20){
      muonIsoCut = (event->muPFRelIso_[selector->MuonsNoIso.at(0)] <= 0.17) ? true : false; 
      muonNonIsoCut = (event->muPFRelIso_[selector->MuonsNoIso.at(0)] > 0.17 and event->muPFRelIso_[selector->MuonsNoIso.at(0)] <= 0.4) ? true : false; 
    }else{
      muonIsoCut = (event->muPFRelIso_[selector->MuonsNoIso.at(0)] <= 0.15) ? true : false; 
      muonNonIsoCut = (event->muPFRelIso_[selector->MuonsNoIso.at(0)] > 0.15 and event->muPFRelIso_[selector->MuonsNoIso.at(0)] <= 0.4) ? true : false; 
    }
  }

  bool eleIsoCut = false;
  bool eleNonIsoCut = false;
  if(singleEle){
    double SCeta = event->eleEta_[selector->ElectronsNoIso.at(0)] + event->eleDeltaEtaSC_[selector->ElectronsNoIso.at(0)];
    double absSCEta = TMath::Abs(SCeta);
    if(systType == kIso20){
      eleIsoCut =  (event->elePFRelIso_[selector->ElectronsNoIso.at(0)] <= 0.11) ? true : false;
      eleNonIsoCut = (event->elePFRelIso_[selector->ElectronsNoIso.at(0)] > 0.11 and event->elePFRelIso_[selector->ElectronsNoIso.at(0)] < 0.3 ) ? true : false;
    }else{
      eleIsoCut =  (
		    (absSCEta <= 1.479 and event->elePFRelIso_[selector->ElectronsNoIso.at(0)] <= 0.0695) 
		    or 
		    (absSCEta > 1.479 and  event->elePFRelIso_[selector->ElectronsNoIso.at(0)] <= 0.0821)
		    ) ? true : false;

      eleNonIsoCut =  (
		       (
			absSCEta <= 1.479 
			and 
			event->elePFRelIso_[selector->ElectronsNoIso.at(0)] > 0.0695 
			and 
			event->elePFRelIso_[selector->ElectronsNoIso.at(0)] <= 0.3
			) 
		       or 
		       (
			absSCEta > 1.479 
			and  
			event->elePFRelIso_[selector->ElectronsNoIso.at(0)] < 0.0821
			and
			event->elePFRelIso_[selector->ElectronsNoIso.at(0)] <= 0.3
			)
		       ) ? true : false;
    }

  }
  
  FillLeptonCutFlow(singleMu, muonIsoCut, muonNonIsoCut, singleEle, eleIsoCut, eleNonIsoCut);
  FillLeptonWt(singleMu, muonIsoCut, muonNonIsoCut, singleEle, eleIsoCut, eleNonIsoCut);
  if(IsDebug) Info("Process","Completed Lepton processing");

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  //////=====================================================
  if(selector->Jets.size() < 4 ) return true; //original condn
  //if(selector->Jets.size() < 4 or selector->Jets.size() >= 9 ) return true;
  //////=====================================================
  
  
  //Processes after njet >= 4 selection will be placed in block below
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////

  FillNjetCutFlow(singleMu, muonIsoCut, muonNonIsoCut, singleEle, eleIsoCut, eleNonIsoCut);
  FillNjetWt(singleMu, muonIsoCut, muonNonIsoCut, singleEle, eleIsoCut, eleNonIsoCut);
  if(IsDebug) Info("Process","Completed Njet processing");

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////

  
  
  METThreshold = 20. ;
  bool isLowMET = false;
  //////=====================================================
  if(selector->METPt < METThreshold ) isLowMET = true;
  //////=====================================================


  //Processes after MET selection will be placed in block below
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////

  FillMETCutFlow(singleMu, muonIsoCut, muonNonIsoCut, singleEle, eleIsoCut, eleNonIsoCut, isLowMET);
  if(IsDebug) Info("Process","Completed MET processing");

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////

  //////=====================================================
  if(selector->bJets.size() < 2 ) return true;
  //////=====================================================
  

  //Processes after nbjet >= 2 selection will be placed in block below
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////
  if(!isData){
    if(fSyst == "base"){
      btagSystType  = "b_up" ;
      GetBtagSF_1a();
      _bTagWeight_b_Up = _bTagWeight;
      
      btagSystType  = "b_down" ;
      GetBtagSF_1a();
      _bTagWeight_b_Do = _bTagWeight;
      
      btagSystType  = "l_up" ;
      GetBtagSF_1a();
      _bTagWeight_l_Up = _bTagWeight;
      
      btagSystType  = "l_down" ;
      GetBtagSF_1a();
      _bTagWeight_l_Do = _bTagWeight;
      
      TheoWeights();
    }
    
    btagSystType  = "central" ;
    GetBtagSF_1a();
    //_topPtReWeight = topPtReweight();

  }
  
  //FillBTagCutFlow(singleMu, muonIsoCut, muonNonIsoCut, singleEle, eleIsoCut, eleNonIsoCut, isLowMET);
  FillBTagObs(singleMu, muonIsoCut, muonNonIsoCut, singleEle, eleIsoCut, eleNonIsoCut, isLowMET);
  FillBTagWt(singleMu, muonIsoCut, muonNonIsoCut, singleEle, eleIsoCut, eleNonIsoCut, isLowMET);  
  if(IsDebug) Info("Process","Completed b-jet processing");
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  //Processes for KinFit selection will be placed in block below
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////
  FillKFCFObs(singleMu, muonIsoCut, muonNonIsoCut, singleEle, eleIsoCut, eleNonIsoCut, isLowMET);
  if(IsDebug) Info("Process","Completed KinFit processing");
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  return kTRUE;

}

//_____________________________________________________________________________
bool SkimAna::SelectTTbarChannel(){

    bool isOne_u = false, isOne_d = false, isOne_c = false, isOne_s = false;
    bool isTwo_u = false, isTwo_d = false, isTwo_c = false, isTwo_s = false;
    bool isOne_e = false, isOne_m = false, isOne_t = false;
    bool isTwo_e = false, isTwo_m = false, isTwo_t = false;
    bool isOne_nu_e = false, isOne_nu_m = false, isOne_nu_t = false;
    bool isTwo_nu_e = false, isTwo_nu_m = false, isTwo_nu_t = false;
    
    for (unsigned int imc = (event->nLHEPart_-4) ; imc < event->nLHEPart_ ; imc++ ){      //Check the last four particles


      if(abs(event->LHEPart_pdgId_[imc])==1 and isOne_d) isTwo_d = true; // Two must be above one lepton/parton condition
      if(abs(event->LHEPart_pdgId_[imc])==1 and !isOne_d) isOne_d = true;
      if(abs(event->LHEPart_pdgId_[imc])==2 and isOne_u) isTwo_u = true;
      if(abs(event->LHEPart_pdgId_[imc])==2 and !isOne_u) isOne_u = true;
      if(abs(event->LHEPart_pdgId_[imc])==3 and isOne_s) isTwo_s = true;
      if(abs(event->LHEPart_pdgId_[imc])==3 and !isOne_s) isOne_s = true;
      if(abs(event->LHEPart_pdgId_[imc])==4 and isOne_c) isTwo_c = true;
      if(abs(event->LHEPart_pdgId_[imc])==4 and !isOne_c) isOne_c = true;

      if(abs(event->LHEPart_pdgId_[imc])==11 and isOne_e) isTwo_e = true;
      if(abs(event->LHEPart_pdgId_[imc])==11 and !isOne_e) isOne_e = true;
      if(abs(event->LHEPart_pdgId_[imc])==13 and isOne_m) isTwo_m = true;
      if(abs(event->LHEPart_pdgId_[imc])==13 and !isOne_m) isOne_m = true;
      if(abs(event->LHEPart_pdgId_[imc])==15 and isOne_t) isTwo_t = true;
      if(abs(event->LHEPart_pdgId_[imc])==15 and !isOne_t) isOne_t = true;


      if(abs(event->LHEPart_pdgId_[imc])==12 and isOne_nu_e) isTwo_nu_e = true;
      if(abs(event->LHEPart_pdgId_[imc])==12 and !isOne_nu_e) isOne_nu_e = true;
      if(abs(event->LHEPart_pdgId_[imc])==14 and isOne_nu_m) isTwo_nu_m = true;
      if(abs(event->LHEPart_pdgId_[imc])==14 and !isOne_nu_m) isOne_nu_m = true;
      if(abs(event->LHEPart_pdgId_[imc])==16 and isOne_nu_t) isTwo_nu_t = true;
      if(abs(event->LHEPart_pdgId_[imc])==16 and !isOne_nu_t) isOne_nu_t = true;

      
      
    }// mc particle loop
    
    bool isSemilepton = false, isDilepton = false, isHadronic = false;

    bool isSameFlavlepton = (isTwo_nu_e and isTwo_e) or (isTwo_nu_m and isTwo_m) or (isTwo_nu_t and isTwo_t) ;
    bool isDiffFlavlepton = (isOne_e and isOne_nu_e and isOne_m and isOne_nu_m) 
                              or (isOne_e and isOne_nu_e and isOne_t and isOne_nu_t) 
                              or (isOne_m and isOne_nu_m and isOne_t and isOne_nu_t);
    if(isSameFlavlepton or isDiffFlavlepton){
      isDilepton = true;
      _kFType = 11;
      // nofDileptonic++ ;
      //printf("Event type : dileptonic\n");
    }

    if(!isDilepton){
      bool isFourHadron1 = isOne_u and isOne_d and isOne_c and isOne_s;
      bool isFourHadron2 = (isTwo_u and isOne_d and isOne_c) or (isTwo_u and isOne_d and isOne_s) or (isTwo_u and isOne_c and isOne_s) ;
      bool isFourHadron3 = (isTwo_d and isOne_u and isOne_c) or (isTwo_d and isOne_u and isOne_s) or (isTwo_d and isOne_c and isOne_s) ;
      bool isFourHadron4 = (isTwo_c and isOne_u and isOne_d) or (isTwo_c and isOne_u and isOne_s) or (isTwo_c and isOne_d and isOne_s) ;
      bool isFourHadron5 = (isTwo_s and isOne_u and isOne_d) or (isTwo_s and isOne_u and isOne_c) or (isTwo_s and isOne_d and isOne_c) ;
      bool isFourHadron6 = (isTwo_u and isTwo_d) or (isTwo_u and isTwo_c) or (isTwo_u and isTwo_s) or (isTwo_d and isTwo_c) or (isTwo_d and isTwo_s) or (isTwo_c and isTwo_s);
      if(isFourHadron1 or isFourHadron2 or isFourHadron3 or isFourHadron4 or isFourHadron5 or isFourHadron6){
	isHadronic = true;
	_kFType = 12;
	// nofHadronic++;
	//printf("Event type : hadronic\n");
      }
    }

    if(!isDilepton and !isHadronic){
      bool isOneLepton = (isOne_e and isOne_nu_e) or (isOne_m and isOne_nu_m) or (isOne_t and isOne_nu_t);
      bool isOneHadron = (isOne_u and isOne_d) or (isOne_u and isOne_c) or (isOne_u and isOne_s) or (isOne_d and isOne_c) or (isOne_d and isOne_s) or (isOne_c and isOne_s) ;
      if(isOneLepton and isOneLepton){
	isSemilepton = true;
	_kFType = 13;
	
	// if((isOne_c and isOne_s) and (isOne_e and isOne_nu_e)) nofcsEle++;
	// if((isOne_c and isOne_s) and (isOne_m and isOne_nu_m)) nofcsMu++;
	// if((isOne_c and isOne_s) and (isOne_t and isOne_nu_t)) nofcsTau++;

	//enum SlType { kSlEle, kSlMu, kSlTau, kSlcs, kSlud, kSlus,  kSldc};
	if(isOne_e and isOne_nu_e) slType = kSlEle;
	if(isOne_m and isOne_nu_m) slType = kSlMu;
	if(isOne_t and isOne_nu_t) slType = kSlTau;
	if(isOne_c and isOne_s) slType = kSlcs;
	if(isOne_u and isOne_d) slType = kSlud;
	if(isOne_u and isOne_s) slType = kSlus;
	if(isOne_d and isOne_c) slType = kSldc;
	// nofSemiLeptonic++;
	//printf("Event type : semileptonic\n");
      }
    }
    
    return true;
}

//_____________________________________________________________________________
bool SkimAna::FillCFHists(TList *list, string hist_extn, bool isMu, double value, double wt, double wt1){
  
  // if(_kFType == 12){
    
  //   ((TH1D *) list->FindObject(Form("_cutflow_data1%s",hist_extn.c_str())))->Fill(value);
  //   if(isMu){
  //     ((TH1D *) list->FindObject(Form("_cutflowUS_mu1%s",hist_extn.c_str())))->Fill(value);
  //     ((TH1D *) list->FindObject(Form("_cutflow_mu1%s",hist_extn.c_str())))->Fill(value, wt);
  //     ((TH1D *) list->FindObject(Form("_cutflow51%s",hist_extn.c_str())))->Fill(value, wt1);
  //   }else{
  //     ((TH1D *) list->FindObject(Form("_cutflowUS_ele1%s",hist_extn.c_str())))->Fill(value);
  //     ((TH1D *) list->FindObject(Form("_cutflow_ele1%s",hist_extn.c_str())))->Fill(value, wt);
  //   }

  // } else if(_kFType == 13){

  //   ((TH1D *) list->FindObject(Form("_cutflow_data2%s",hist_extn.c_str())))->Fill(value);
  //   if(isMu){
  //     ((TH1D *) list->FindObject(Form("_cutflowUS_mu2%s",hist_extn.c_str())))->Fill(value);
  //     ((TH1D *) list->FindObject(Form("_cutflow_mu2%s",hist_extn.c_str())))->Fill(value, wt);
  //     ((TH1D *) list->FindObject(Form("_cutflow52%s",hist_extn.c_str())))->Fill(value, wt1);
  //   }else{
  //     ((TH1D *) list->FindObject(Form("_cutflowUS_ele2%s",hist_extn.c_str())))->Fill(value);
  //     ((TH1D *) list->FindObject(Form("_cutflow_ele2%s",hist_extn.c_str())))->Fill(value, wt);
  //   }    

  // }else{

    ((TH1D *) list->FindObject(Form("_cutflow_data%s",hist_extn.c_str())))->Fill(value);
    if(isMu){
      ((TH1D *) list->FindObject(Form("_cutflowUS_mu%s",hist_extn.c_str())))->Fill(value);
      ((TH1D *) list->FindObject(Form("_cutflow_mu%s",hist_extn.c_str())))->Fill(value, wt);
      ((TH1D *) list->FindObject(Form("_cutflow5%s",hist_extn.c_str())))->Fill(value, wt1);
    }else{
      ((TH1D *) list->FindObject(Form("_cutflowUS_ele%s",hist_extn.c_str())))->Fill(value);
      ((TH1D *) list->FindObject(Form("_cutflow_ele%s",hist_extn.c_str())))->Fill(value, wt);
    }

    //enum SlType { kSlEle, kSlMu, kSlTau, kSlcs, kSlud, kSlus,  kSldc};

    if(_kFType == 13){
      if(isMu){
	switch(slType){
	case kSlEle:
	  ((TH1D *) list->FindObject(Form("_cutflow_nofSlEle_mu%s",hist_extn.c_str())))->Fill(value, wt);
	  break;
	case kSlMu:
	  ((TH1D *) list->FindObject(Form("_cutflow_nofSlMu_mu%s",hist_extn.c_str())))->Fill(value, wt);
	  break;
	case kSlTau:
	  ((TH1D *) list->FindObject(Form("_cutflow_nofSlTau_mu%s",hist_extn.c_str())))->Fill(value, wt);
	  break;
	case kSlcs:
	  ((TH1D *) list->FindObject(Form("_cutflow_nofSlcs_mu%s",hist_extn.c_str())))->Fill(value, wt);
	  break;
	case kSlud:
	  ((TH1D *) list->FindObject(Form("_cutflow_nofSlud_mu%s",hist_extn.c_str())))->Fill(value, wt);
	  break;
	case kSlus:
	  ((TH1D *) list->FindObject(Form("_cutflow_nofSlus_mu%s",hist_extn.c_str())))->Fill(value, wt);
	  break;
	case kSldc:
	  ((TH1D *) list->FindObject(Form("_cutflow_nofSldc_mu%s",hist_extn.c_str())))->Fill(value, wt);
	  break;
	}
      }else{
	switch(slType){
	case kSlEle:
	  ((TH1D *) list->FindObject(Form("_cutflow_nofSlEle_ele%s",hist_extn.c_str())))->Fill(value, wt);
	  break;
	case kSlMu:
	  ((TH1D *) list->FindObject(Form("_cutflow_nofSlMu_ele%s",hist_extn.c_str())))->Fill(value, wt);
	  break;
	case kSlTau:
	  ((TH1D *) list->FindObject(Form("_cutflow_nofSlTau_ele%s",hist_extn.c_str())))->Fill(value, wt);
	  break;
	case kSlcs:
	  ((TH1D *) list->FindObject(Form("_cutflow_nofSlcs_ele%s",hist_extn.c_str())))->Fill(value, wt);
	  break;
	case kSlud:
	  ((TH1D *) list->FindObject(Form("_cutflow_nofSlud_ele%s",hist_extn.c_str())))->Fill(value, wt);
	  break;
	case kSlus:
	  ((TH1D *) list->FindObject(Form("_cutflow_nofSlus_ele%s",hist_extn.c_str())))->Fill(value, wt);
	  break;
	case kSldc:
	  ((TH1D *) list->FindObject(Form("_cutflow_nofSldc_ele%s",hist_extn.c_str())))->Fill(value, wt);
	  break;
	}
      }    
    }

  // }
  return true;
}

//_____________________________________________________________________________
bool SkimAna::FillKFHists(TList *list, string hist_extn, bool isMu, double wt){
  
  string lep = (isMu) ? "mu" : "ele";
  
  // if(_kFType == 12){

  //   ((TH1D *) list->FindObject(Form("_kb_pt_%s1%s",lep.c_str(),hist_extn.c_str())))->Fill(leptonAF.Pt(), wt);
  //   ((TH1D *) list->FindObject(Form("_kb_eta_%s1%s",lep.c_str(),hist_extn.c_str())))->Fill(leptonAF.Eta(), wt);
  //   ((TH1D *) list->FindObject(Form("_kb_phi_%s1%s",lep.c_str(),hist_extn.c_str())))->Fill(leptonAF.Phi(), wt);

  //   ((TH1D *) list->FindObject(Form("_kb_pt_%s_jets1%s",lep.c_str(),hist_extn.c_str())))->Fill(bjlepAF.Pt(), wt);
  //   ((TH1D *) list->FindObject(Form("_kb_pt_%s_jets1%s",lep.c_str(),hist_extn.c_str())))->Fill(bjhadAF.Pt(), wt);
  //   ((TH1D *) list->FindObject(Form("_kb_pt_%s_jets1%s",lep.c_str(),hist_extn.c_str())))->Fill(cjhadAF.Pt(), wt);
  //   ((TH1D *) list->FindObject(Form("_kb_pt_%s_jets1%s",lep.c_str(),hist_extn.c_str())))->Fill(sjhadAF.Pt(), wt);

  //   ((TH1D *) list->FindObject(Form("_kb_eta_%s_jets1%s",lep.c_str(),hist_extn.c_str())))->Fill(bjlepAF.Eta(), wt);
  //   ((TH1D *) list->FindObject(Form("_kb_eta_%s_jets1%s",lep.c_str(),hist_extn.c_str())))->Fill(bjhadAF.Eta(), wt);
  //   ((TH1D *) list->FindObject(Form("_kb_eta_%s_jets1%s",lep.c_str(),hist_extn.c_str())))->Fill(cjhadAF.Eta(), wt);
  //   ((TH1D *) list->FindObject(Form("_kb_eta_%s_jets1%s",lep.c_str(),hist_extn.c_str())))->Fill(sjhadAF.Eta(), wt);
	    
  //   ((TH1D *) list->FindObject(Form("_kb_phi_%s_jets1%s",lep.c_str(),hist_extn.c_str())))->Fill(bjlepAF.Phi(), wt);
  //   ((TH1D *) list->FindObject(Form("_kb_phi_%s_jets1%s",lep.c_str(),hist_extn.c_str())))->Fill(bjhadAF.Phi(), wt);
  //   ((TH1D *) list->FindObject(Form("_kb_phi_%s_jets1%s",lep.c_str(),hist_extn.c_str())))->Fill(cjhadAF.Phi(), wt);
  //   ((TH1D *) list->FindObject(Form("_kb_phi_%s_jets1%s",lep.c_str(),hist_extn.c_str())))->Fill(sjhadAF.Phi(), wt);

  //   ((TH1D *) list->FindObject(Form("_kb_pt_%s_met1%s",lep.c_str(),hist_extn.c_str())))->Fill(neutrinoAF.Pt(), wt);
  //   ((TH1D *) list->FindObject(Form("_kb_phi_%s_met1%s",lep.c_str(),hist_extn.c_str())))->Fill(neutrinoAF.Phi(), wt);
  //   ((TH1D *) list->FindObject(Form("_kb_njet_%s1%s",lep.c_str(),hist_extn.c_str())))->Fill(selector->Jets.size(), wt);
  //   ((TH1D *) list->FindObject(Form("_kb_nbjet_%s1%s",lep.c_str(),hist_extn.c_str())))->Fill(selector->bJets.size(), wt);
  
  //   ((TH1D *) list->FindObject(Form("_kb_mjj_%s1%s",lep.c_str(),hist_extn.c_str())))->Fill((cjhadAF+sjhadAF).M(), wt);
  //   ((TH1D *) list->FindObject(Form("_kb_mjj_bf_%s1%s",lep.c_str(),hist_extn.c_str())))->Fill((cjhadBF+sjhadBF).M(), wt);

  // }else if(_kFType == 13){

  //   ((TH1D *) list->FindObject(Form("_kb_pt_%s2%s",lep.c_str(),hist_extn.c_str())))->Fill(leptonAF.Pt(), wt);
  //   ((TH1D *) list->FindObject(Form("_kb_eta_%s2%s",lep.c_str(),hist_extn.c_str())))->Fill(leptonAF.Eta(), wt);
  //   ((TH1D *) list->FindObject(Form("_kb_phi_%s2%s",lep.c_str(),hist_extn.c_str())))->Fill(leptonAF.Phi(), wt);

  //   ((TH1D *) list->FindObject(Form("_kb_pt_%s_jets2%s",lep.c_str(),hist_extn.c_str())))->Fill(bjlepAF.Pt(), wt);
  //   ((TH1D *) list->FindObject(Form("_kb_pt_%s_jets2%s",lep.c_str(),hist_extn.c_str())))->Fill(bjhadAF.Pt(), wt);
  //   ((TH1D *) list->FindObject(Form("_kb_pt_%s_jets2%s",lep.c_str(),hist_extn.c_str())))->Fill(cjhadAF.Pt(), wt);
  //   ((TH1D *) list->FindObject(Form("_kb_pt_%s_jets2%s",lep.c_str(),hist_extn.c_str())))->Fill(sjhadAF.Pt(), wt);

  //   ((TH1D *) list->FindObject(Form("_kb_eta_%s_jets2%s",lep.c_str(),hist_extn.c_str())))->Fill(bjlepAF.Eta(), wt);
  //   ((TH1D *) list->FindObject(Form("_kb_eta_%s_jets2%s",lep.c_str(),hist_extn.c_str())))->Fill(bjhadAF.Eta(), wt);
  //   ((TH1D *) list->FindObject(Form("_kb_eta_%s_jets2%s",lep.c_str(),hist_extn.c_str())))->Fill(cjhadAF.Eta(), wt);
  //   ((TH1D *) list->FindObject(Form("_kb_eta_%s_jets2%s",lep.c_str(),hist_extn.c_str())))->Fill(sjhadAF.Eta(), wt);
	    
  //   ((TH1D *) list->FindObject(Form("_kb_phi_%s_jets2%s",lep.c_str(),hist_extn.c_str())))->Fill(bjlepAF.Phi(), wt);
  //   ((TH1D *) list->FindObject(Form("_kb_phi_%s_jets2%s",lep.c_str(),hist_extn.c_str())))->Fill(bjhadAF.Phi(), wt);
  //   ((TH1D *) list->FindObject(Form("_kb_phi_%s_jets2%s",lep.c_str(),hist_extn.c_str())))->Fill(cjhadAF.Phi(), wt);
  //   ((TH1D *) list->FindObject(Form("_kb_phi_%s_jets2%s",lep.c_str(),hist_extn.c_str())))->Fill(sjhadAF.Phi(), wt);

  //   ((TH1D *) list->FindObject(Form("_kb_pt_%s_met2%s",lep.c_str(),hist_extn.c_str())))->Fill(neutrinoAF.Pt(), wt);
  //   ((TH1D *) list->FindObject(Form("_kb_phi_%s_met2%s",lep.c_str(),hist_extn.c_str())))->Fill(neutrinoAF.Phi(), wt);
  //   ((TH1D *) list->FindObject(Form("_kb_njet_%s2%s",lep.c_str(),hist_extn.c_str())))->Fill(selector->Jets.size(), wt);
  //   ((TH1D *) list->FindObject(Form("_kb_nbjet_%s2%s",lep.c_str(),hist_extn.c_str())))->Fill(selector->bJets.size(), wt);
  
  //   ((TH1D *) list->FindObject(Form("_kb_mjj_%s2%s",lep.c_str(),hist_extn.c_str())))->Fill((cjhadAF+sjhadAF).M(), wt);
  //   ((TH1D *) list->FindObject(Form("_kb_mjj_bf_%s2%s",lep.c_str(),hist_extn.c_str())))->Fill((cjhadBF+sjhadBF).M(), wt);

  // }else{

    ((TH1D *) list->FindObject(Form("_kb_pt_%s%s",lep.c_str(),hist_extn.c_str())))->Fill(leptonAF.Pt(), wt);
    ((TH1D *) list->FindObject(Form("_kb_eta_%s%s",lep.c_str(),hist_extn.c_str())))->Fill(leptonAF.Eta(), wt);
    ((TH1D *) list->FindObject(Form("_kb_phi_%s%s",lep.c_str(),hist_extn.c_str())))->Fill(leptonAF.Phi(), wt);

    ((TH1D *) list->FindObject(Form("_kb_pt_%s_jets%s",lep.c_str(),hist_extn.c_str())))->Fill(bjlepAF.Pt(), wt);
    ((TH1D *) list->FindObject(Form("_kb_pt_%s_jets%s",lep.c_str(),hist_extn.c_str())))->Fill(bjhadAF.Pt(), wt);
    ((TH1D *) list->FindObject(Form("_kb_pt_%s_jets%s",lep.c_str(),hist_extn.c_str())))->Fill(cjhadAF.Pt(), wt);
    ((TH1D *) list->FindObject(Form("_kb_pt_%s_jets%s",lep.c_str(),hist_extn.c_str())))->Fill(sjhadAF.Pt(), wt);

    ((TH1D *) list->FindObject(Form("_kb_eta_%s_jets%s",lep.c_str(),hist_extn.c_str())))->Fill(bjlepAF.Eta(), wt);
    ((TH1D *) list->FindObject(Form("_kb_eta_%s_jets%s",lep.c_str(),hist_extn.c_str())))->Fill(bjhadAF.Eta(), wt);
    ((TH1D *) list->FindObject(Form("_kb_eta_%s_jets%s",lep.c_str(),hist_extn.c_str())))->Fill(cjhadAF.Eta(), wt);
    ((TH1D *) list->FindObject(Form("_kb_eta_%s_jets%s",lep.c_str(),hist_extn.c_str())))->Fill(sjhadAF.Eta(), wt);
	    
    ((TH1D *) list->FindObject(Form("_kb_phi_%s_jets%s",lep.c_str(),hist_extn.c_str())))->Fill(bjlepAF.Phi(), wt);
    ((TH1D *) list->FindObject(Form("_kb_phi_%s_jets%s",lep.c_str(),hist_extn.c_str())))->Fill(bjhadAF.Phi(), wt);
    ((TH1D *) list->FindObject(Form("_kb_phi_%s_jets%s",lep.c_str(),hist_extn.c_str())))->Fill(cjhadAF.Phi(), wt);
    ((TH1D *) list->FindObject(Form("_kb_phi_%s_jets%s",lep.c_str(),hist_extn.c_str())))->Fill(sjhadAF.Phi(), wt);

    ((TH1D *) list->FindObject(Form("_kb_pt_%s_met%s",lep.c_str(),hist_extn.c_str())))->Fill(neutrinoAF.Pt(), wt);
    ((TH1D *) list->FindObject(Form("_kb_phi_%s_met%s",lep.c_str(),hist_extn.c_str())))->Fill(neutrinoAF.Phi(), wt);
    ((TH1D *) list->FindObject(Form("_kb_njet_%s%s",lep.c_str(),hist_extn.c_str())))->Fill(selector->Jets.size(), wt);
    ((TH1D *) list->FindObject(Form("_kb_nbjet_%s%s",lep.c_str(),hist_extn.c_str())))->Fill(selector->bJets.size(), wt);
  
    ((TH1D *) list->FindObject(Form("_kb_mjj_%s%s",lep.c_str(),hist_extn.c_str())))->Fill((cjhadAF+sjhadAF).M(), wt);
    ((TH1D *) list->FindObject(Form("_kb_mjj_bf_%s%s",lep.c_str(),hist_extn.c_str())))->Fill((cjhadBF+sjhadBF).M(), wt);

    if(_kFType == 13 and hist_extn == ""){
      
      ((TH1D *) list->FindObject(Form("_bjet1Pt_AF_%s",lep.c_str())))->Fill(bjhadAF.Pt(), wt);
      ((TH1D *) list->FindObject(Form("_bjet1Pt_BF_%s",lep.c_str())))->Fill(bjhadBF.Pt(), wt);
      ((TH1D *) list->FindObject(Form("_bjet2Pt_AF_%s",lep.c_str())))->Fill(bjlepAF.Pt(), wt);
      ((TH1D *) list->FindObject(Form("_bjet2Pt_BF_%s",lep.c_str())))->Fill(bjlepBF.Pt(), wt);
      
      ((TH1D *) list->FindObject(Form("_ljet1Pt_AF_%s",lep.c_str())))->Fill( ((cjhadAF.Pt()>sjhadAF.Pt()) ? cjhadAF.Pt() : sjhadAF.Pt()), wt);
      ((TH1D *) list->FindObject(Form("_ljet1Pt_BF_%s",lep.c_str())))->Fill( ((cjhadAF.Pt()>sjhadAF.Pt()) ? cjhadBF.Pt() : sjhadBF.Pt()), wt);
      ((TH1D *) list->FindObject(Form("_ljet2Pt_AF_%s",lep.c_str())))->Fill( ((cjhadAF.Pt()>sjhadAF.Pt()) ? sjhadAF.Pt() : cjhadAF.Pt()), wt);
      ((TH1D *) list->FindObject(Form("_ljet2Pt_BF_%s",lep.c_str())))->Fill( ((cjhadAF.Pt()>sjhadAF.Pt()) ? sjhadBF.Pt() : cjhadBF.Pt()), wt);
      
    }

  // }
  
  return true;
}

//_____________________________________________________________________________
bool SkimAna::FillBTHists(TList *list, string hist_extn, bool isMu, double wt){
  
  string lep = (isMu) ? "mu" : "ele";
  
  // if(_kFType == 12){

  //   if(isMu){
  //     ((TH1D *) list->FindObject(Form("_lb_pt_mu1%s",hist_extn.c_str())))->Fill(event->muPt_[selector->MuonsNoIso.at(0)] * event->muRoccoR_[selector->MuonsNoIso.at(0)], wt);
  //     ((TH1D *) list->FindObject(Form("_lb_eta_mu1%s",hist_extn.c_str())))->Fill(event->muEta_[selector->MuonsNoIso.at(0)], wt);
  //     ((TH1D *) list->FindObject(Form("_lb_phi_mu1%s",hist_extn.c_str())))->Fill(event->muEta_[selector->MuonsNoIso.at(0)], wt);
  //   }else{
  //     ((TH1D *) list->FindObject(Form("_lb_pt_ele1%s",hist_extn.c_str())))->Fill(event->elePt_[selector->ElectronsNoIso.at(0)], wt);
  //     ((TH1D *) list->FindObject(Form("_lb_eta_ele1%s",hist_extn.c_str())))->Fill(event->eleEta_[selector->ElectronsNoIso.at(0)], wt);
  //     ((TH1D *) list->FindObject(Form("_lb_phi_ele1%s",hist_extn.c_str())))->Fill(event->elePhi_[selector->ElectronsNoIso.at(0)], wt);
  //   }
  //   for(unsigned int ijet = 0; ijet < selector->Jets.size(); ijet++){
  //     int jetInd = selector->Jets.at(ijet);
  //     ((TH1D *) list->FindObject(Form("_lb_pt_%s_jets1%s",lep.c_str(),hist_extn.c_str())))->Fill(selector->JetsPtSmeared.at(ijet), wt);
  //     ((TH1D *) list->FindObject(Form("_lb_eta_%s_jets1%s",lep.c_str(),hist_extn.c_str())))->Fill(event->jetEta_[jetInd], wt);
  //     ((TH1D *) list->FindObject(Form("_lb_phi_%s_jets1%s",lep.c_str(),hist_extn.c_str())))->Fill(event->jetPhi_[jetInd], wt);
  //   }
  //   ((TH1D *) list->FindObject(Form("_lb_pt_%s_met1%s",lep.c_str(),hist_extn.c_str())))->Fill(selector->METPt, wt);
  //   ((TH1D *) list->FindObject(Form("_lb_phi_%s_met1%s",lep.c_str(),hist_extn.c_str())))->Fill(selector->METPhi, wt);
  //   ((TH1D *) list->FindObject(Form("_lb_njet_%s1%s",lep.c_str(),hist_extn.c_str())))->Fill(selector->Jets.size(), wt);
  //   ((TH1D *) list->FindObject(Form("_lb_nbjet_%s1%s",lep.c_str(),hist_extn.c_str())))->Fill(selector->bJets.size(), wt);

  // } else if(_kFType == 13){

  //   if(isMu){
  //     ((TH1D *) list->FindObject(Form("_lb_pt_mu2%s",hist_extn.c_str())))->Fill(event->muPt_[selector->MuonsNoIso.at(0)] * event->muRoccoR_[selector->MuonsNoIso.at(0)], wt);
  //     ((TH1D *) list->FindObject(Form("_lb_eta_mu2%s",hist_extn.c_str())))->Fill(event->muEta_[selector->MuonsNoIso.at(0)], wt);
  //     ((TH1D *) list->FindObject(Form("_lb_phi_mu2%s",hist_extn.c_str())))->Fill(event->muEta_[selector->MuonsNoIso.at(0)], wt);
  //   }else{
  //     ((TH1D *) list->FindObject(Form("_lb_pt_ele2%s",hist_extn.c_str())))->Fill(event->elePt_[selector->ElectronsNoIso.at(0)], wt);
  //     ((TH1D *) list->FindObject(Form("_lb_eta_ele2%s",hist_extn.c_str())))->Fill(event->eleEta_[selector->ElectronsNoIso.at(0)], wt);
  //     ((TH1D *) list->FindObject(Form("_lb_phi_ele2%s",hist_extn.c_str())))->Fill(event->elePhi_[selector->ElectronsNoIso.at(0)], wt);
  //   }
  //   for(unsigned int ijet = 0; ijet < selector->Jets.size(); ijet++){
  //     int jetInd = selector->Jets.at(ijet);
  //     ((TH1D *) list->FindObject(Form("_lb_pt_%s_jets2%s",lep.c_str(),hist_extn.c_str())))->Fill(selector->JetsPtSmeared.at(ijet), wt);
  //     ((TH1D *) list->FindObject(Form("_lb_eta_%s_jets2%s",lep.c_str(),hist_extn.c_str())))->Fill(event->jetEta_[jetInd], wt);
  //     ((TH1D *) list->FindObject(Form("_lb_phi_%s_jets2%s",lep.c_str(),hist_extn.c_str())))->Fill(event->jetPhi_[jetInd], wt);
  //   }
  //   ((TH1D *) list->FindObject(Form("_lb_pt_%s_met2%s",lep.c_str(),hist_extn.c_str())))->Fill(selector->METPt, wt);
  //   ((TH1D *) list->FindObject(Form("_lb_phi_%s_met2%s",lep.c_str(),hist_extn.c_str())))->Fill(selector->METPhi, wt);
  //   ((TH1D *) list->FindObject(Form("_lb_njet_%s2%s",lep.c_str(),hist_extn.c_str())))->Fill(selector->Jets.size(), wt);
  //   ((TH1D *) list->FindObject(Form("_lb_nbjet_%s2%s",lep.c_str(),hist_extn.c_str())))->Fill(selector->bJets.size(), wt);

  // }else{

    if(isMu){
      ((TH1D *) list->FindObject(Form("_lb_pt_mu%s",hist_extn.c_str())))->Fill(event->muPt_[selector->MuonsNoIso.at(0)] * event->muRoccoR_[selector->MuonsNoIso.at(0)], wt);
      ((TH1D *) list->FindObject(Form("_lb_eta_mu%s",hist_extn.c_str())))->Fill(event->muEta_[selector->MuonsNoIso.at(0)], wt);
      ((TH1D *) list->FindObject(Form("_lb_phi_mu%s",hist_extn.c_str())))->Fill(event->muEta_[selector->MuonsNoIso.at(0)], wt);
    }else{
      ((TH1D *) list->FindObject(Form("_lb_pt_ele%s",hist_extn.c_str())))->Fill(event->elePt_[selector->ElectronsNoIso.at(0)], wt);
      ((TH1D *) list->FindObject(Form("_lb_eta_ele%s",hist_extn.c_str())))->Fill(event->eleEta_[selector->ElectronsNoIso.at(0)], wt);
      ((TH1D *) list->FindObject(Form("_lb_phi_ele%s",hist_extn.c_str())))->Fill(event->elePhi_[selector->ElectronsNoIso.at(0)], wt);
    }
    for(unsigned int ijet = 0; ijet < selector->Jets.size(); ijet++){
      int jetInd = selector->Jets.at(ijet);
      ((TH1D *) list->FindObject(Form("_lb_pt_%s_jets%s",lep.c_str(),hist_extn.c_str())))->Fill(selector->JetsPtSmeared.at(ijet), wt);
      ((TH1D *) list->FindObject(Form("_lb_eta_%s_jets%s",lep.c_str(),hist_extn.c_str())))->Fill(event->jetEta_[jetInd], wt);
      ((TH1D *) list->FindObject(Form("_lb_phi_%s_jets%s",lep.c_str(),hist_extn.c_str())))->Fill(event->jetPhi_[jetInd], wt);
    }
    ((TH1D *) list->FindObject(Form("_lb_pt_%s_met%s",lep.c_str(),hist_extn.c_str())))->Fill(selector->METPt, wt);
    ((TH1D *) list->FindObject(Form("_lb_phi_%s_met%s",lep.c_str(),hist_extn.c_str())))->Fill(selector->METPhi, wt);
    ((TH1D *) list->FindObject(Form("_lb_njet_%s%s",lep.c_str(),hist_extn.c_str())))->Fill(selector->Jets.size(), wt);
    ((TH1D *) list->FindObject(Form("_lb_nbjet_%s%s",lep.c_str(),hist_extn.c_str())))->Fill(selector->bJets.size(), wt);

  // }
  
  return true;
}

//_____________________________________________________________________________
bool SkimAna::GetCombinedWt(TString systname, double& combined_muwt, double& combined_muwt1, double& combined_elewt){

  double puwt = _PUWeight ; if(systname == "puup") puwt = _PUWeight_Up ; if(systname == "pudown") puwt = _PUWeight_Do ;
  double prefirewt = _prefireWeight ; if(systname == "prefireup")  prefirewt = _prefireWeight_Up ; if(systname == "prefiredown") prefirewt = _prefireWeight_Do ;
  double muwt = _muEffWeight ; if(systname == "mueffup") muwt = _muEffWeight_Up ; if(systname == "mueffdown") muwt = _muEffWeight_Do ; 
  double elewt = _eleEffWeight ; if(systname == "eleeffup") elewt = _eleEffWeight_Up ; if(systname == "eleeffdown") elewt = _eleEffWeight_Do ; 
  double btagwt = _bTagWeight ; if(systname == "btagbup") btagwt = _bTagWeight_b_Up ; if(systname == "btagbdown") btagwt = _bTagWeight_b_Do ; 
  if(systname == "btaglup") btagwt = _bTagWeight_l_Up ; if(systname == "btagldown") btagwt = _bTagWeight_l_Do ; 
  double pdfwt = 1.0 ; if(systname == "pdfup") pdfwt = _pdfweight_Up ; if(systname == "pdfdown") pdfwt = _pdfweight_Do ;
  double q2wt = 1.0 ; if(systname == "q2up") q2wt = _q2weight_Up ; if(systname == "q2down") q2wt = _q2weight_Do ;
  double isrwt = 1.0 ; if(systname == "isrup") isrwt = _ISRweight_Up ; if(systname == "isrdown") isrwt = _ISRweight_Do ;
  double fsrwt = 1.0 ; if(systname == "fsrup") fsrwt = _FSRweight_Up ; if(systname == "fsrdown") fsrwt = _FSRweight_Do ;

  combined_muwt = _sampleWeight * prefirewt * puwt * muwt * btagwt * pdfwt * q2wt * isrwt * fsrwt ;
  combined_muwt1 = _sampleWeight * puwt * muwt * btagwt * pdfwt * q2wt * isrwt * fsrwt ;
  combined_elewt = _sampleWeight * prefirewt * puwt * elewt * btagwt * pdfwt * q2wt * isrwt * fsrwt ;
  
  return true;
}

//_____________________________________________________________________________

bool SkimAna::FillKFCFObs(bool singleMu, bool muonIsoCut, bool muonNonIsoCut, bool singleEle, bool eleIsoCut, bool eleNonIsoCut, bool isLowMET){
  
  double combined_muwt = 1.0,  combined_muwt1 = 1.0, combined_elewt = 1.0;

  if(systType == kBase){

    if(ProcessKinFit((singleMu and muonIsoCut), false)){

      for(int isyst=0;isyst<fNSyst;isyst++){
	
	TString systname = fSystList[isyst];
	
	if(!systname.Contains("jec") and !systname.Contains("jer") and !systname.Contains("iso20") and !systname.Contains("met")) {
  
	  GetCombinedWt(systname, combined_muwt, combined_muwt1, combined_elewt);

	  if(!isLowMET){

	    ////////////////// base ////////////////////////////
	    TList *lIso = (TList *)fFileDir[isyst*fNDDReg + 0]->GetList();
	    //FillCFHists(TList *list, string hist_extn, bool isMu, double value, double wt, double wt1)
	    FillCFHists(lIso, "", true, 6.0, combined_muwt, combined_muwt1);
	    //FillKFHists(TList *list, string hist_extn, bool isMu, double wt);
	    FillKFHists(lIso,"",true,combined_muwt);
	    /////////////////////////////////////////////////////

	  }else{

	    TList *lLowMET = (TList *)fFileDir[isyst*fNDDReg + 1]->GetList();
	    FillCFHists(lLowMET,"_lmet", true, 6.0, combined_muwt, combined_muwt1);
	    FillKFHists(lLowMET,"_lmet",true,combined_muwt);

	  }//lowmet
	}//not jec jer
      }//syst loop
    }//muon iso
	
    if(ProcessKinFit((singleMu and muonNonIsoCut), false)){
      for(int isyst=0;isyst<fNSyst;isyst++){
	
	TString systname = fSystList[isyst];
	
	if(!systname.Contains("jec") and !systname.Contains("jer") and !systname.Contains("iso20") and !systname.Contains("met")) {
	
	  GetCombinedWt(systname, combined_muwt, combined_muwt1, combined_elewt);

	  if(!isLowMET){

	    TList *lNonIso = (TList *)fFileDir[isyst*fNDDReg + 2]->GetList();
	    FillCFHists(lNonIso,"_noniso", true, 6.0, combined_muwt, combined_muwt1);
	    FillKFHists(lNonIso,"_noniso",true,combined_muwt);

	  }else{

	    TList *lNonIsoLowMET = (TList *)fFileDir[isyst*fNDDReg + 3]->GetList();
	    FillCFHists(lNonIsoLowMET,"_noniso_lmet", true, 6.0, combined_muwt, combined_muwt1);
	    FillKFHists(lNonIsoLowMET,"_noniso_lmet",true,combined_muwt);
	    
	  }//lowmet
	}//no jec jer
      }//syst loop
    }// muon noniso
	
    //elec
    if(ProcessKinFit(false, (singleEle and eleIsoCut))){

      for(int isyst=0;isyst<fNSyst;isyst++){
	
	TString systname = fSystList[isyst];
	
	if(!systname.Contains("jec") and !systname.Contains("jer") and !systname.Contains("iso20") and !systname.Contains("met")) {
	
	  GetCombinedWt(systname, combined_muwt, combined_muwt1, combined_elewt);
	  
	  if(!isLowMET){
	    
	    ////////////////// base ////////////////////////////	    
	    TList *lIso = (TList *)fFileDir[isyst*fNDDReg + 0]->GetList();
	    //FillCFHists(TList *list, string hist_extn, bool isMu, double value, double wt, double wt1)
	    FillCFHists(lIso,"", false, 6.0, combined_elewt, 1.0);
	    //FillKFHists(TList *list, string hist_extn, bool isMu, double wt);
	    FillKFHists(lIso,"",false,combined_elewt);	    
	    /////////////////////////////////////////////////////

	  }else{

	    TList *lLowMET = (TList *)fFileDir[isyst*fNDDReg + 1]->GetList();
	    FillCFHists(lLowMET,"_lmet", false, 6.0, combined_elewt, 1.0);
	    FillKFHists(lLowMET,"_lmet",false,combined_elewt);	    	    
	    
	  }//lowmet
	}//no jec jer
      }//syst loop
    }//ele iso
	
    if(ProcessKinFit(false, (singleEle and eleNonIsoCut))){

      for(int isyst=0;isyst<fNSyst;isyst++){
	
	TString systname = fSystList[isyst];
	
	if(!systname.Contains("jec") and !systname.Contains("jer") and !systname.Contains("iso20") and !systname.Contains("met")) {
	
	  GetCombinedWt(systname, combined_muwt, combined_muwt1, combined_elewt);

	  if(!isLowMET){

	    TList *lNonIso = (TList *)fFileDir[isyst*fNDDReg + 2]->GetList();
	    FillCFHists(lNonIso,"_noniso", false, 6.0, combined_elewt, 1.0);
	    FillKFHists(lNonIso,"_noniso",false,combined_elewt);	    
	    
	  }else{
	    
	    TList *lNonIsoLowMET = (TList *)fFileDir[isyst*fNDDReg + 3]->GetList();
	    FillCFHists(lNonIsoLowMET,"_noniso_lmet", false, 6.0, combined_elewt, 1.0);
	    FillKFHists(lNonIsoLowMET,"_noniso_lmet",false,combined_elewt);	    
	    
	  }//lowmet
	}//jec jer condn
      }//syst loop
    }//ele noniso

  }else if(systType == kIso20){ //if systType == kBase

    combined_muwt = _sampleWeight*_prefireWeight*_PUWeight*_muEffWeight*_bTagWeight;
    combined_muwt1 = _sampleWeight*_PUWeight*_muEffWeight*_bTagWeight;
    combined_elewt = _sampleWeight*_prefireWeight*_PUWeight*_eleEffWeight*_bTagWeight;
    
    if(ProcessKinFit((singleMu and muonIsoCut), false)){
      for(int isyst=0;isyst<fNSyst;isyst++){
	TString systname = fSystList[isyst];
	if(systname.Contains("iso20")) {
  	  if(!isLowMET){
	    ////////////////// base ////////////////////////////
	    TList *lIso = (TList *)fFileDir[isyst*fNDDReg + 0]->GetList();
	    FillCFHists(lIso, "", true, 6.0, combined_muwt, combined_muwt1);
	    //FillKFHists(TList *list, string hist_extn, bool isMu, double wt);
	    FillKFHists(lIso,"",true,combined_muwt);
	    /////////////////////////////////////////////////////
	  }else{
	    TList *lLowMET = (TList *)fFileDir[isyst*fNDDReg + 1]->GetList();
	    FillCFHists(lLowMET,"_lmet", true, 6.0, combined_muwt, combined_muwt1);
	    FillKFHists(lLowMET,"_lmet",true,combined_muwt);
	  }//lowmet
	}//iso20 condn
      }//syst loop
    }//muon iso
	
    if(ProcessKinFit((singleMu and muonNonIsoCut), false)){
      for(int isyst=0;isyst<fNSyst;isyst++){
	TString systname = fSystList[isyst];
	if(systname.Contains("iso20")) {
	  if(!isLowMET){
	    TList *lNonIso = (TList *)fFileDir[isyst*fNDDReg + 2]->GetList();
	    FillCFHists(lNonIso,"_noniso", true, 6.0, combined_muwt, combined_muwt1);
	    FillKFHists(lNonIso,"_noniso",true,combined_muwt);
	  }else{
	    TList *lNonIsoLowMET = (TList *)fFileDir[isyst*fNDDReg + 3]->GetList();
	    FillCFHists(lNonIsoLowMET,"_noniso_lmet", true, 6.0, combined_muwt, combined_muwt1);
	    FillKFHists(lNonIsoLowMET,"_noniso_lmet",true,combined_muwt);
	  }//lowmet
	}//iso20 condn
      }//syst loop
    }// muon noniso
	
    //elec
    if(ProcessKinFit(false, (singleEle and eleIsoCut))){
      for(int isyst=0;isyst<fNSyst;isyst++){
	TString systname = fSystList[isyst];
	if(systname.Contains("iso20")) {
	  if(!isLowMET){	    
	    ////////////////// base ////////////////////////////	    
	    TList *lIso = (TList *)fFileDir[isyst*fNDDReg + 0]->GetList();
	    //FillKFHists(TList *list, string hist_extn, bool isMu, double wt);
	    FillCFHists(lIso,"",false, 6.0, combined_elewt, 1.0);
	    FillKFHists(lIso,"",false,combined_elewt);	    
	    /////////////////////////////////////////////////////
	  }else{
	    TList *lLowMET = (TList *)fFileDir[isyst*fNDDReg + 1]->GetList();
	    FillCFHists(lLowMET,"_lmet",false, 6.0, combined_elewt, 1.0);
	    FillKFHists(lLowMET,"_lmet",false,combined_elewt);	    	    
	  }//lowmet
	}//iso20 condn
      }//syst loop
    }//ele iso
	
    if(ProcessKinFit(false, (singleEle and eleNonIsoCut))){
      for(int isyst=0;isyst<fNSyst;isyst++){
	TString systname = fSystList[isyst];
	if(systname.Contains("iso20")) {
	  if(!isLowMET){
	    TList *lNonIso = (TList *)fFileDir[isyst*fNDDReg + 2]->GetList();
	    FillCFHists(lNonIso,"_noniso",false, 6.0, combined_elewt, 1.0);
	    FillKFHists(lNonIso,"_noniso",false,combined_elewt);	    	    
	  }else{
	    TList *lNonIsoLowMET = (TList *)fFileDir[isyst*fNDDReg + 3]->GetList();
	    FillCFHists(lNonIsoLowMET,"_noniso_lmet",false, 6.0, combined_elewt, 1.0);
	    FillKFHists(lNonIsoLowMET,"_noniso_lmet",false,combined_elewt);	    
	  }//lowmet
	}//iso20 condn
      }//syst loop
    }//ele noniso

  }else { //if systType == kBase

    combined_muwt = _sampleWeight*_prefireWeight*_PUWeight*_muEffWeight*_bTagWeight;
    combined_muwt1 = _sampleWeight*_PUWeight*_muEffWeight*_bTagWeight;
    combined_elewt = _sampleWeight*_prefireWeight*_PUWeight*_eleEffWeight*_bTagWeight;


    if(ProcessKinFit((singleMu and muonIsoCut), false)){
      for(int isyst=0;isyst<fNSyst;isyst++){
	TString systname = fSystList[isyst];
	if( (systType == kJECUp and systname == "jecup") or (systType == kJECDown and systname == "jecdown") 
	    or (systType == kJERUp and systname == "jerup") or (systType == kJERDown and systname == "jerdown")
	    or (systType == kMETUp and systname == "metup") or (systType == kMETDown and systname == "metdown")){	    
  	  if(!isLowMET){
	    ////////////////// base ////////////////////////////
	    TList *lIso = (TList *)fFileDir[isyst*fNDDReg + 0]->GetList();
	    FillCFHists(lIso, "", true, 6.0, combined_muwt, combined_muwt1);
	    //FillKFHists(TList *list, string hist_extn, bool isMu, double wt);
	    FillKFHists(lIso,"",true,combined_muwt);
	    /////////////////////////////////////////////////////
	  }else{
	    TList *lLowMET = (TList *)fFileDir[isyst*fNDDReg + 1]->GetList();
	    FillCFHists(lLowMET,"_lmet", true, 6.0, combined_muwt, combined_muwt1);
	    FillKFHists(lLowMET,"_lmet",true,combined_muwt);
	  }//lowmet
	}//jec jer condn
      }//syst loop
    }//muon iso
	
    if(ProcessKinFit((singleMu and muonNonIsoCut), false)){
      for(int isyst=0;isyst<fNSyst;isyst++){
	TString systname = fSystList[isyst];
	if( (systType == kJECUp and systname == "jecup") or (systType == kJECDown and systname == "jecdown") 
	    or (systType == kJERUp and systname == "jerup") or (systType == kJERDown and systname == "jerdown")
	    or (systType == kMETUp and systname == "metup") or (systType == kMETDown and systname == "metdown")){	    
	    
	  if(!isLowMET){
	    TList *lNonIso = (TList *)fFileDir[isyst*fNDDReg + 2]->GetList();
	    FillCFHists(lNonIso,"_noniso", true, 6.0, combined_muwt, combined_muwt1);
	    FillKFHists(lNonIso,"_noniso",true,combined_muwt);
	  }else{
	    TList *lNonIsoLowMET = (TList *)fFileDir[isyst*fNDDReg + 3]->GetList();
	    FillCFHists(lNonIsoLowMET,"_noniso_lmet", true, 6.0, combined_muwt, combined_muwt1);
	    FillKFHists(lNonIsoLowMET,"_noniso_lmet",true,combined_muwt);
	  }//lowmet
	}//jec jer condn
      }//syst loop
    }// muon noniso

    // //mu
    // if(ProcessKinFit((singleMu and muonIsoCut), false) and !isLowMET){      
    //   for(int isyst=0;isyst<fNSyst;isyst++){
    // 	TString systname = fSystList[isyst];
    // 	if( (systType == kJECUp and systname == "jecup") or (systType == kJECDown and systname == "jecdown") 
    // 	    or (systType == kJERUp and systname == "jerup") or (systType == kJERDown and systname == "jerdown")
	    // or (systType == kMETUp and systname == "metup") or (systType == kMETDown and systname == "metdown")){	    	    
    // 	  ////////////////// base ////////////////////////////
    // 	  TList *lIso = (TList *)fFileDir[isyst*fNDDReg + 0]->GetList();
    // 	  FillCFHists(lIso,"",true, 6.0, combined_muwt, combined_muwt1);
    // 	  FillKFHists(lIso,"",true,combined_muwt);	    
    // 	  /////////////////////////////////////////////////////
    // 	}//jec jer condn
    //   }//syst loop
    // }//muon iso

    //elec
    if(ProcessKinFit(false, (singleEle and eleIsoCut))){
      for(int isyst=0;isyst<fNSyst;isyst++){
	TString systname = fSystList[isyst];
	if( (systType == kJECUp and systname == "jecup") or (systType == kJECDown and systname == "jecdown") 
	    or (systType == kJERUp and systname == "jerup") or (systType == kJERDown and systname == "jerdown")
	    or (systType == kMETUp and systname == "metup") or (systType == kMETDown and systname == "metdown")){	    
	    
	  if(!isLowMET){	    
	    ////////////////// base ////////////////////////////	    
	    TList *lIso = (TList *)fFileDir[isyst*fNDDReg + 0]->GetList();
	    //FillKFHists(TList *list, string hist_extn, bool isMu, double wt);
	    FillCFHists(lIso,"",false, 6.0, combined_elewt, 1.0);
	    FillKFHists(lIso,"",false,combined_elewt);	    
	    /////////////////////////////////////////////////////
	  }else{
	    TList *lLowMET = (TList *)fFileDir[isyst*fNDDReg + 1]->GetList();
	    FillCFHists(lLowMET,"_lmet",false, 6.0, combined_elewt, 1.0);
	    FillKFHists(lLowMET,"_lmet",false,combined_elewt);	    	    
	  }//lowmet
	}//jec jer condn
      }//syst loop
    }//ele iso
	
    if(ProcessKinFit(false, (singleEle and eleNonIsoCut))){
      for(int isyst=0;isyst<fNSyst;isyst++){
	TString systname = fSystList[isyst];
	if( (systType == kJECUp and systname == "jecup") or (systType == kJECDown and systname == "jecdown") 
	    or (systType == kJERUp and systname == "jerup") or (systType == kJERDown and systname == "jerdown")
	    or (systType == kMETUp and systname == "metup") or (systType == kMETDown and systname == "metdown")){	    
	    
	  if(!isLowMET){
	    TList *lNonIso = (TList *)fFileDir[isyst*fNDDReg + 2]->GetList();
	    FillCFHists(lNonIso,"_noniso",false, 6.0, combined_elewt, 1.0);
	    FillKFHists(lNonIso,"_noniso",false,combined_elewt);	    	    
	  }else{
	    TList *lNonIsoLowMET = (TList *)fFileDir[isyst*fNDDReg + 3]->GetList();
	    FillCFHists(lNonIsoLowMET,"_noniso_lmet",false, 6.0, combined_elewt, 1.0);
	    FillKFHists(lNonIsoLowMET,"_noniso_lmet",false,combined_elewt);	    
	  }//lowmet
	}//jec jer condn
      }//syst loop
    }//ele noniso

    
    // //elec
    // if(ProcessKinFit(false, (singleEle and eleIsoCut)) and !isLowMET){
    //   for(int isyst=0;isyst<fNSyst;isyst++){
    // 	TString systname = fSystList[isyst];
    // 	if( (systType == kJECUp and systname == "jecup") or (systType == kJECDown and systname == "jecdown") 
    // 	    or (systType == kJERUp and systname == "jerup") or (systType == kJERDown and systname == "jerdown")
    // or (systType == kMETUp and systname == "metup") or (systType == kMETDown and systname == "metdown")){	    
    // 	  ////////////////// base ////////////////////////////
    // 	  TList *lIso = (TList *)fFileDir[isyst*fNDDReg + 0]->GetList();
    // 	  FillCFHists(lIso,"",false, 6.0, combined_elewt, 1.0);
    // 	  FillKFHists(lIso,"",false,combined_elewt);	    	  
    // 	  /////////////////////////////////////////////////////
    // 	}//jec jer condn
    //   }//sys loop
    // }//ele iso

  }//syst base vs jec/jer condn
  
  return true;
}
//_____________________________________________________________________________
bool SkimAna::FillBTagCFBTHists(int isyst, double combined_muwt, double combined_muwt1, double combined_elewt, 
				bool singleMu, bool muonIsoCut, bool muonNonIsoCut, bool singleEle, bool eleIsoCut, bool eleNonIsoCut, bool isLowMET)
{

  if(singleMu and muonIsoCut){
    if(!isLowMET){
      ////////////////// base ////////////////////////////
      TList *lIso = (TList *)fFileDir[isyst*fNDDReg + 0]->GetList();
      FillCFHists(lIso, "", true, 5.0, combined_muwt, combined_muwt1);
      FillBTHists(lIso, "", true, combined_muwt);
      /////////////////////////////////////////////////////
    }else{
      TList *lLowMET = (TList *)fFileDir[isyst*fNDDReg + 1]->GetList();
      FillCFHists(lLowMET, "_lmet", true, 5.0, combined_muwt, combined_muwt1);
      FillBTHists(lLowMET, "_lmet", true, combined_muwt);
    }//lowmet
  }
	
  if(singleMu and muonNonIsoCut){
    if(!isLowMET){
      TList *lNonIso = (TList *)fFileDir[isyst*fNDDReg + 2]->GetList();
      FillCFHists(lNonIso, "_noniso", true, 5.0, combined_muwt, combined_muwt1);
      FillBTHists(lNonIso, "_noniso", true, combined_muwt);
    }else{
      TList *lNonIsoLowMET = (TList *)fFileDir[isyst*fNDDReg + 3]->GetList();
      FillCFHists(lNonIsoLowMET, "_noniso_lmet", true, 5.0, combined_muwt, combined_muwt1);
      FillBTHists(lNonIsoLowMET, "_noniso_lmet", true, combined_muwt);
    }//lowmet
  }
	
  //elec
  if(singleEle and eleIsoCut){
    if(!isLowMET){
      ////////////////// base ////////////////////////////
      TList *lIso = (TList *)fFileDir[isyst*fNDDReg + 0]->GetList();
      FillCFHists(lIso, "", false, 5.0, combined_elewt, 1.0);
      FillBTHists(lIso, "", false, combined_elewt);
      /////////////////////////////////////////////////////
    }else{
      TList *lLowMET = (TList *)fFileDir[isyst*fNDDReg + 1]->GetList();
      FillCFHists(lLowMET, "_lmet", false, 5.0, combined_elewt, 1.0);
      FillBTHists(lLowMET, "_lmet", false, combined_elewt);
    }//lowmet
  }
	
  if(singleEle and eleNonIsoCut){
    if(!isLowMET){
      TList *lNonIso = (TList *)fFileDir[isyst*fNDDReg + 2]->GetList();
      FillCFHists(lNonIso, "_noniso", false, 5.0, combined_elewt, 1.0);
      FillBTHists(lNonIso, "_noniso", false, combined_elewt);
    }else{
      TList *lNonIsoLowMET = (TList *)fFileDir[isyst*fNDDReg + 3]->GetList();
      FillCFHists(lNonIsoLowMET, "_noniso_lmet", false, 5.0, combined_elewt, 1.0);
      FillBTHists(lNonIsoLowMET, "_noniso_lmet", false, combined_elewt);
    }//lowmet
  }
  
  return true;
}

//_____________________________________________________________________________

bool SkimAna::FillBTagObs(bool singleMu, bool muonIsoCut, bool muonNonIsoCut, bool singleEle, bool eleIsoCut, bool eleNonIsoCut, bool isLowMET){

  for(int isyst=0;isyst<fNSyst;isyst++){

    TString systname = fSystList[isyst];

    double combined_muwt = _sampleWeight*_prefireWeight*_PUWeight*_muEffWeight*_bTagWeight;
    double combined_muwt1 = _sampleWeight*_PUWeight*_muEffWeight*_bTagWeight;
    double combined_elewt = _sampleWeight*_prefireWeight*_PUWeight*_eleEffWeight*_bTagWeight;

    if(systType == kBase){

      if(!systname.Contains("jec") and !systname.Contains("jer") and !systname.Contains("iso20") and !systname.Contains("met") ) {
	
	GetCombinedWt(systname, combined_muwt, combined_muwt1, combined_elewt);
	FillBTagCFBTHists(isyst, combined_muwt, combined_muwt1, combined_elewt, singleMu, muonIsoCut, muonNonIsoCut, singleEle, eleIsoCut, eleNonIsoCut, isLowMET);

      }//jec jer condn

    }else if(systType == kIso20){ //if(systType == kBase

      if(systname.Contains("iso20")) {
	
	FillBTagCFBTHists(isyst, combined_muwt, combined_muwt1, combined_elewt, singleMu, muonIsoCut, muonNonIsoCut, singleEle, eleIsoCut, eleNonIsoCut, isLowMET);
	
      }//iso20 condn
      
    }else{ //if(systType == kBase
      
      if( (systType == kJECUp and systname == "jecup") or (systType == kJECDown and systname == "jecdown") 
	  or (systType == kJERUp and systname == "jerup") or (systType == kJERDown and systname == "jerdown")
	  or (systType == kMETUp and systname == "metup") or (systType == kMETDown and systname == "metdown")){

	FillBTagCFBTHists(isyst, combined_muwt, combined_muwt1, combined_elewt, singleMu, muonIsoCut, muonNonIsoCut, singleEle, eleIsoCut, eleNonIsoCut, isLowMET);
	
      }
    }//systType condn
  }//syst loop
  
  return true;
}


// //_____________________________________________________________________________

// bool SkimAna::FillBTagCutFlow(bool singleMu, bool muonIsoCut, bool muonNonIsoCut, bool singleEle, bool eleIsoCut, bool eleNonIsoCut, bool isLowMET){

//   for(int isyst=0;isyst<fNSyst;isyst++){

//     TString systname = fSystList[isyst];

//     if(systType == kBase){

//       if(!systname.Contains("jec") and !systname.Contains("jer") and !systname.Contains("iso20")) {

// 	if((singleMu and muonIsoCut) or (singleEle and eleIsoCut)){
// 	  if(!isLowMET)
// 	    hCutFlow[fNCFHists*isyst + 0]->Fill(5.0);
// 	  else
// 	    hCutFlow[fNCFHists*isyst + 0 + fNBCFHists]->Fill(5.0);
// 	}
// 	if((singleMu and muonNonIsoCut) or (singleEle and eleNonIsoCut)){
// 	  if(!isLowMET)
// 	    hCutFlow[fNCFHists*isyst + 0 + 2*fNBCFHists]->Fill(5.0);
// 	  else
// 	    hCutFlow[fNCFHists*isyst + 0 + 3*fNBCFHists]->Fill(5.0);
// 	}
	
// 	double puwt = _PUWeight ; if(systname == "puup") puwt = _PUWeight_Up ; if(systname == "pudown") puwt = _PUWeight_Do ;
// 	double prefirewt = _prefireWeight ; if(systname == "prefireup")  prefirewt = _prefireWeight_Up ; if(systname == "prefiredown") prefirewt = _prefireWeight_Do ;
// 	double muwt = _muEffWeight ; if(systname == "mueffup") muwt = _muEffWeight_Up ; if(systname == "mueffdown") muwt = _muEffWeight_Do ; 
// 	double elewt = _eleEffWeight ; if(systname == "eleeffup") elewt = _eleEffWeight_Up ; if(systname == "eleeffdown") elewt = _eleEffWeight_Do ; 
// 	double btagwt = _bTagWeight ; if(systname == "btagbup") btagwt = _bTagWeight_b_Up ; if(systname == "btagbdown") btagwt = _bTagWeight_b_Do ; 
// 	if(systname == "btaglup") btagwt = _bTagWeight_l_Up ; if(systname == "btagldown") btagwt = _bTagWeight_l_Do ; 
// 	double pdfwt = 1.0 ; if(systname == "pdfup") pdfwt = _pdfweight_Up ; if(systname == "pdfdown") pdfwt = _pdfweight_Do ;
// 	double q2wt = 1.0 ; if(systname == "q2up") q2wt = _q2weight_Up ; if(systname == "q2down") q2wt = _q2weight_Do ;
// 	double isrwt = 1.0 ; if(systname == "isrup") isrwt = _ISRweight_Up ; if(systname == "isrdown") isrwt = _ISRweight_Do ;
// 	double fsrwt = 1.0 ; if(systname == "fsrup") fsrwt = _FSRweight_Up ; if(systname == "fsrdown") fsrwt = _FSRweight_Do ;
	
// 	double combined_muwt = _sampleWeight * prefirewt * puwt * muwt * btagwt * pdfwt * q2wt * isrwt * fsrwt ;
// 	double combined_muwt1 = _sampleWeight * puwt * muwt * btagwt * pdfwt * q2wt * isrwt * fsrwt ;
// 	double combined_elewt = _sampleWeight * prefirewt * puwt * elewt * btagwt * pdfwt * q2wt * isrwt * fsrwt ;

// 	if(singleMu and muonIsoCut){
// 	  if(!isLowMET){
// 	    hCutFlow[fNCFHists*isyst + 1]->Fill(5.0);
// 	    hCutFlow[fNCFHists*isyst + 2]->Fill(5.0, combined_muwt);
// 	    hCutFlow[fNCFHists*isyst + 5]->Fill(5.0, combined_muwt1);
// 	  }else{
// 	    hCutFlow[fNCFHists*isyst + 1 + fNBCFHists]->Fill(5.0);
// 	    hCutFlow[fNCFHists*isyst + 2 + fNBCFHists]->Fill(5.0, combined_muwt);
// 	    hCutFlow[fNCFHists*isyst + 5 + fNBCFHists]->Fill(5.0, combined_muwt1);
// 	  }//lowmet
// 	}

// 	if(singleMu and muonNonIsoCut){
// 	  if(!isLowMET){
// 	    hCutFlow[fNCFHists*isyst + 1 + 2*fNBCFHists]->Fill(5.0);
// 	    hCutFlow[fNCFHists*isyst + 2 + 2*fNBCFHists]->Fill(5.0, combined_muwt);
// 	    hCutFlow[fNCFHists*isyst + 5 + 2*fNBCFHists]->Fill(5.0, combined_muwt1);
// 	  }else{
// 	    hCutFlow[fNCFHists*isyst + 1 + 3*fNBCFHists]->Fill(5.0);
// 	    hCutFlow[fNCFHists*isyst + 2 + 3*fNBCFHists]->Fill(5.0, combined_muwt);
// 	    hCutFlow[fNCFHists*isyst + 5 + 3*fNBCFHists]->Fill(5.0, combined_muwt1);
// 	  }//lowmet
// 	}
  
// 	//elec
// 	if(singleEle and eleIsoCut){
// 	  if(!isLowMET){
// 	    hCutFlow[fNCFHists*isyst + 3]->Fill(5.0);
// 	    hCutFlow[fNCFHists*isyst + 4]->Fill(5.0, combined_elewt);
// 	  }else{
// 	    hCutFlow[fNCFHists*isyst + 3 + fNBCFHists]->Fill(5.0);
// 	    hCutFlow[fNCFHists*isyst + 4 + fNBCFHists]->Fill(5.0, combined_elewt);
// 	  }//lowmet
// 	}
	
// 	if(singleEle and eleNonIsoCut){
// 	  if(!isLowMET){
// 	    hCutFlow[fNCFHists*isyst + 3 + 2*fNBCFHists]->Fill(5.0);
// 	    hCutFlow[fNCFHists*isyst + 4 + 2*fNBCFHists]->Fill(5.0, combined_elewt);
// 	  }else{
// 	    hCutFlow[fNCFHists*isyst + 3 + 3*fNBCFHists]->Fill(5.0);
// 	    hCutFlow[fNCFHists*isyst + 4 + 3*fNBCFHists]->Fill(5.0, combined_elewt);
// 	  }//lowmet
// 	}
//       }//jec jer condn
//     }else {//if(systType == kJECUp){

//       if( (systType == kJECUp and systname == "jecup") or (systType == kJECDown and systname == "jecdown") 
// 	  or (systType == kJERUp and systname == "jerup") or (systType == kJERDown and systname == "jerdown")
// 	  or (systType == kIso20 and systname == "iso20")){

// 	if((singleMu and muonIsoCut) or (singleEle and eleIsoCut)){
// 	  if(!isLowMET)
// 	    hCutFlow[fNCFHists*isyst + 0]->Fill(5.0);
// 	  else
// 	    hCutFlow[fNCFHists*isyst + 0 + fNBCFHists]->Fill(5.0);
// 	}
// 	//mu
// 	if(singleMu and muonIsoCut and !isLowMET){
// 	  hCutFlow[fNCFHists*isyst + 1]->Fill(5.0);
// 	  hCutFlow[fNCFHists*isyst + 2]->Fill(5.0, _sampleWeight*_prefireWeight*_PUWeight*_muEffWeight*_bTagWeight);
// 	  hCutFlow[fNCFHists*isyst + 5]->Fill(5.0, _sampleWeight*_PUWeight*_muEffWeight*_bTagWeight);
	  
// 	}
// 	//elec
// 	if(singleEle and eleIsoCut and !isLowMET){
// 	  hCutFlow[fNCFHists*isyst + 3]->Fill(5.0);
// 	  hCutFlow[fNCFHists*isyst + 4]->Fill(5.0, _sampleWeight*_prefireWeight*_PUWeight*_eleEffWeight*_bTagWeight);     
// 	}	
//       }//jec jer condn
//     }//systType condn
//   }//syst loop
  
//   return true;
// }
//_____________________________________________________________________________
bool SkimAna::FillMETCFHists(int isyst, double combined_muwt, double combined_muwt1, double combined_elewt, 
			     bool singleMu, bool muonIsoCut, bool muonNonIsoCut, bool singleEle, bool eleIsoCut, bool eleNonIsoCut, bool isLowMET)
{

  if(singleMu and muonIsoCut){
    if(!isLowMET){
      TList *list = (TList *)fFileDir[isyst*fNDDReg + 0]->GetList();
      FillCFHists(list, "", true, 4.0, combined_muwt, combined_muwt1);
    }else{
      TList *list = (TList *)fFileDir[isyst*fNDDReg + 1]->GetList();
      FillCFHists(list, "_lmet", true, 4.0, combined_muwt, combined_muwt1);
    }//lowmet
  }

  if(singleMu and muonNonIsoCut){
    if(!isLowMET){
      TList *list = (TList *)fFileDir[isyst*fNDDReg + 2]->GetList();
      FillCFHists(list, "_noniso", true, 4.0, combined_muwt, combined_muwt1);
    }else{
      TList *list = (TList *)fFileDir[isyst*fNDDReg + 3]->GetList();
      FillCFHists(list, "_noniso_lmet", true, 4.0, combined_muwt, combined_muwt1);
    }//lowmet
  }
  
  //elec
  if(singleEle and eleIsoCut){
    if(!isLowMET){
      TList *list = (TList *)fFileDir[isyst*fNDDReg + 0]->GetList();
      FillCFHists(list, "", false, 4.0, combined_elewt, 1.0);
    }else{
      TList *list = (TList *)fFileDir[isyst*fNDDReg + 1]->GetList();
      FillCFHists(list, "_lmet", false, 4.0, combined_elewt, 1.0);
    }//lowmet
  }
	
  if(singleEle and eleNonIsoCut){
    if(!isLowMET){
      TList *list = (TList *)fFileDir[isyst*fNDDReg + 2]->GetList();
      FillCFHists(list, "_noniso", false, 4.0, combined_elewt, 1.0);
    }else{
      TList *list = (TList *)fFileDir[isyst*fNDDReg + 3]->GetList();
      FillCFHists(list, "_noniso_lmet", false, 4.0, combined_elewt, 1.0);
    }//lowmet
  }
  
  return true;
}
//_____________________________________________________________________________

bool SkimAna::FillMETCutFlow(bool singleMu, bool muonIsoCut, bool muonNonIsoCut, bool singleEle, bool eleIsoCut, bool eleNonIsoCut, bool isLowMET){

  for(int isyst=0;isyst<fNSyst;isyst++){

    TString systname = fSystList[isyst];

    double combined_muwt = _sampleWeight*_prefireWeight*_PUWeight*_muEffWeight;
    double combined_muwt1 = _sampleWeight*_PUWeight*_muEffWeight;
    double combined_elewt = _sampleWeight*_prefireWeight*_PUWeight*_eleEffWeight;

    if(systType == kBase){

      if(!systname.Contains("jec") and !systname.Contains("jer") and !systname.Contains("iso20") and !systname.Contains("met")) {
	
	double puwt = _PUWeight ; if(systname == "puup") puwt = _PUWeight_Up ; if(systname == "pudown") puwt = _PUWeight_Do ;
	double prefirewt = _prefireWeight ; if(systname == "prefireup")  prefirewt = _prefireWeight_Up ; if(systname == "prefiredown") prefirewt = _prefireWeight_Do ;
	double muwt = _muEffWeight ; if(systname == "mueffup") muwt = _muEffWeight_Up ; if(systname == "mueffdown") muwt = _muEffWeight_Do ; 
	double elewt = _eleEffWeight ; if(systname == "eleeffup") elewt = _eleEffWeight_Up ; if(systname == "eleeffdown") elewt = _eleEffWeight_Do ; 

	combined_muwt = _sampleWeight*prefirewt*puwt*muwt;
	combined_muwt1 = _sampleWeight*puwt*muwt;
	combined_elewt = _sampleWeight*prefirewt*puwt*elewt;

	FillMETCFHists(isyst, combined_muwt, combined_muwt1, combined_elewt, singleMu, muonIsoCut, muonNonIsoCut, singleEle, eleIsoCut, eleNonIsoCut, isLowMET);
	
      }//jec jer condn

    }else if(systType == kIso20){// if(systType == kBase){

      if(systname.Contains("iso20")) {
		
	FillMETCFHists(isyst, combined_muwt, combined_muwt1, combined_elewt, singleMu, muonIsoCut, muonNonIsoCut, singleEle, eleIsoCut, eleNonIsoCut, isLowMET);

      }//iso20 condn
      
    }else {// if(systType == kBase){

      if( (systType == kJECUp and systname == "jecup") or (systType == kJECDown and systname == "jecdown") 
	  or (systType == kJERUp and systname == "jerup") or (systType == kJERDown and systname == "jerdown")
	  or (systType == kMETUp and systname == "metup") or (systType == kMETDown and systname == "metdown")){
	
	FillMETCFHists(isyst, combined_muwt, combined_muwt1, combined_elewt, singleMu, muonIsoCut, muonNonIsoCut, singleEle, eleIsoCut, eleNonIsoCut, isLowMET);
	
      }//jec jer condn
    }//systType condn
  }//syst loop
  
  return true;
}

//_____________________________________________________________________________
bool SkimAna::FillNjetCFHists(int isyst, double combined_muwt, double combined_muwt1, double combined_elewt, 
				 bool singleMu, bool muonIsoCut, bool muonNonIsoCut, bool singleEle, bool eleIsoCut, bool eleNonIsoCut)
{

  if(singleMu and muonIsoCut){
    TList *list = (TList *)fFileDir[isyst*fNDDReg + 0]->GetList();
    FillCFHists(list, "", true, 3.0, combined_muwt, combined_muwt1);
    TList *list1 = (TList *)fFileDir[isyst*fNDDReg + 1]->GetList();
    FillCFHists(list1, "_lmet", true, 3.0, combined_muwt, combined_muwt1);
  }

  if(singleMu and muonNonIsoCut){
    TList *list = (TList *)fFileDir[isyst*fNDDReg + 2]->GetList();
    FillCFHists(list, "_noniso", true, 3.0, combined_muwt, combined_muwt1);
    TList *list1 = (TList *)fFileDir[isyst*fNDDReg + 3]->GetList();
    FillCFHists(list1, "_noniso_lmet", true, 3.0, combined_muwt, combined_muwt1);
  }
  
  //elec
  if(singleEle and eleIsoCut){
    TList *list = (TList *)fFileDir[isyst*fNDDReg + 0]->GetList();
    FillCFHists(list, "", false, 3.0, combined_elewt, 1.0);
    TList *list1 = (TList *)fFileDir[isyst*fNDDReg + 1]->GetList();
    FillCFHists(list1, "_lmet", false, 3.0, combined_elewt, 1.0);
  }
	
  if(singleEle and eleNonIsoCut){
    TList *list = (TList *)fFileDir[isyst*fNDDReg + 2]->GetList();
    FillCFHists(list, "_noniso", false, 3.0, combined_elewt, 1.0);
    TList *list1 = (TList *)fFileDir[isyst*fNDDReg + 3]->GetList();
    FillCFHists(list1, "_noniso_lmet", false, 3.0, combined_elewt, 1.0);
  }
  
  return true;
}

//_____________________________________________________________________________

bool SkimAna::FillNjetCutFlow(bool singleMu, bool muonIsoCut, bool muonNonIsoCut, bool singleEle, bool eleIsoCut, bool eleNonIsoCut){

  for(int isyst=0;isyst<fNSyst;isyst++){

    TString systname = fSystList[isyst];

    double combined_muwt = _sampleWeight*_prefireWeight*_PUWeight*_muEffWeight;
    double combined_muwt1 = _sampleWeight*_PUWeight*_muEffWeight;
    double combined_elewt = _sampleWeight*_prefireWeight*_PUWeight*_eleEffWeight;
    
    if(systType == kBase){
      
      if(!systname.Contains("jec") and !systname.Contains("jer") and !systname.Contains("iso20") and !systname.Contains("met")) {
	
	double puwt = _PUWeight ; if(systname == "puup") puwt = _PUWeight_Up ; if(systname == "pudown") puwt = _PUWeight_Do ;
	double prefirewt = _prefireWeight ; if(systname == "prefireup")  prefirewt = _prefireWeight_Up ; if(systname == "prefiredown") prefirewt = _prefireWeight_Do ;
	double muwt = _muEffWeight ; if(systname == "mueffup") muwt = _muEffWeight_Up ; if(systname == "mueffdown") muwt = _muEffWeight_Do ; 
	double elewt = _eleEffWeight ; if(systname == "eleeffup") elewt = _eleEffWeight_Up ; if(systname == "eleeffdown") elewt = _eleEffWeight_Do ; 

	combined_muwt = _sampleWeight*prefirewt*puwt*muwt;
	combined_muwt1 = _sampleWeight*puwt*muwt;
	combined_elewt = _sampleWeight*prefirewt*puwt*elewt;
	
	FillNjetCFHists(isyst, combined_muwt, combined_muwt1, combined_elewt, singleMu, muonIsoCut, muonNonIsoCut, singleEle, eleIsoCut, eleNonIsoCut);
	
      }//jec jer condn

    }else if(systType == kIso20){// if(systType == kBase){

      if(systname.Contains("iso20")) {
		
	FillNjetCFHists(isyst, combined_muwt, combined_muwt1, combined_elewt, singleMu, muonIsoCut, muonNonIsoCut, singleEle, eleIsoCut, eleNonIsoCut);

      }//iso20 condn
      
    }else {// if(systType == kBase){

      if( (systType == kJECUp and systname == "jecup") or (systType == kJECDown and systname == "jecdown") 
	  or (systType == kJERUp and systname == "jerup") or (systType == kJERDown and systname == "jerdown")
	  or (systType == kMETUp and systname == "metup") or (systType == kMETDown and systname == "metdown")){
	
	FillNjetCFHists(isyst, combined_muwt, combined_muwt1, combined_elewt, singleMu, muonIsoCut, muonNonIsoCut, singleEle, eleIsoCut, eleNonIsoCut);
	
      }//jec jer condn
    }//systType condn
  }//syst loop
  
  
  //   }else if(systType == kJECUp){
  //     if(systname == "jecup") {
  //     }
  //   }else if(systType == kJECDown){
  //     if(systname == "jecdown") {
  //     }
  //   }else if(systType == kJERUp){
  //     if(systname == "jerup") {
  //     }
  //   }else if(systType == kJERDown){
  //     if(systname == "jerdown") {
  //     }
  //   }//systType condn
  // }//syst loop
  

  return true;

}
//_____________________________________________________________________________
bool SkimAna::FillLeptonCFHists(int isyst, double combined_muwt, double combined_muwt1, double combined_elewt, 
				bool singleMu, bool muonIsoCut, bool muonNonIsoCut, bool singleEle, bool eleIsoCut, bool eleNonIsoCut)
{

  if(singleMu and muonIsoCut){
    TList *list = (TList *)fFileDir[isyst*fNDDReg + 0]->GetList();
    FillCFHists(list, "", true, 2.0, combined_muwt, combined_muwt1);
    TList *list1 = (TList *)fFileDir[isyst*fNDDReg + 1]->GetList();
    FillCFHists(list1, "_lmet", true, 2.0, combined_muwt, combined_muwt1);
  }

  if(singleMu and muonNonIsoCut){
    TList *list = (TList *)fFileDir[isyst*fNDDReg + 2]->GetList();
    FillCFHists(list, "_noniso", true, 2.0, combined_muwt, combined_muwt1);
    TList *list1 = (TList *)fFileDir[isyst*fNDDReg + 3]->GetList();
    FillCFHists(list1, "_noniso_lmet", true, 2.0, combined_muwt, combined_muwt1);
  }
  
  //elec
  if(singleEle and eleIsoCut){
    TList *list = (TList *)fFileDir[isyst*fNDDReg + 0]->GetList();
    FillCFHists(list, "", false, 2.0, combined_elewt, 1.0);
    TList *list1 = (TList *)fFileDir[isyst*fNDDReg + 1]->GetList();
    FillCFHists(list1, "_lmet", false, 2.0, combined_elewt, 1.0);
  }
	
  if(singleEle and eleNonIsoCut){
    TList *list = (TList *)fFileDir[isyst*fNDDReg + 2]->GetList();
    FillCFHists(list, "_noniso", false, 2.0, combined_elewt, 1.0);
    TList *list1 = (TList *)fFileDir[isyst*fNDDReg + 3]->GetList();
    FillCFHists(list1, "_noniso_lmet", false, 2.0, combined_elewt, 1.0);
  }
  
  return true;
}
//_____________________________________________________________________________

bool SkimAna::FillLeptonCutFlow(bool singleMu, bool muonIsoCut, bool muonNonIsoCut, bool singleEle, bool eleIsoCut, bool eleNonIsoCut){
  
 
  for(int isyst=0;isyst<fNSyst;isyst++){

    TString systname = fSystList[isyst];

    double combined_muwt = _sampleWeight*_prefireWeight*_PUWeight*_muEffWeight;
    double combined_muwt1 = _sampleWeight*_PUWeight*_muEffWeight;
    double combined_elewt = _sampleWeight*_prefireWeight*_PUWeight*_eleEffWeight;
    
    if(systType == kBase){
      
      if(!systname.Contains("jec") and !systname.Contains("jer") and !systname.Contains("iso20") and !systname.Contains("met")) {
	
	double puwt = _PUWeight ; if(systname == "puup") puwt = _PUWeight_Up ; if(systname == "pudown") puwt = _PUWeight_Do ;
	double prefirewt = _prefireWeight ; if(systname == "prefireup")  prefirewt = _prefireWeight_Up ; if(systname == "prefiredown") prefirewt = _prefireWeight_Do ;
	double muwt = _muEffWeight ; if(systname == "mueffup") muwt = _muEffWeight_Up ; if(systname == "mueffdown") muwt = _muEffWeight_Do ; 
	double elewt = _eleEffWeight ; if(systname == "eleeffup") elewt = _eleEffWeight_Up ; if(systname == "eleeffdown") elewt = _eleEffWeight_Do ; 

	combined_muwt = _sampleWeight*prefirewt*puwt*muwt;
	combined_muwt1 = _sampleWeight*puwt*muwt;
	combined_elewt = _sampleWeight*prefirewt*puwt*elewt;

	FillLeptonCFHists(isyst, combined_muwt, combined_muwt1, combined_elewt, singleMu, muonIsoCut, muonNonIsoCut, singleEle, eleIsoCut, eleNonIsoCut);
			  
	
      }//jec jer condn

    }else if(systType == kIso20){// if(systType == kBase){

      if(systname.Contains("iso20")) {
		
	FillLeptonCFHists(isyst, combined_muwt, combined_muwt1, combined_elewt, singleMu, muonIsoCut, muonNonIsoCut, singleEle, eleIsoCut, eleNonIsoCut);

      }//iso20 condn
      
    }else {// if(systType == kBase){

      if( (systType == kJECUp and systname == "jecup") or (systType == kJECDown and systname == "jecdown") 
	  or (systType == kJERUp and systname == "jerup") or (systType == kJERDown and systname == "jerdown")
	  or (systType == kMETUp and systname == "metup") or (systType == kMETDown and systname == "metdown")){
	
	FillLeptonCFHists(isyst, combined_muwt, combined_muwt1, combined_elewt, singleMu, muonIsoCut, muonNonIsoCut, singleEle, eleIsoCut, eleNonIsoCut);
	
      }//jec jer condn
    }//systType condn
  }//syst loop
  
  //   }else if(systType == kJECUp){
  //     if(systname == "jecup") {
  //     }
  //   }else if(systType == kJECDown){
  //     if(systname == "jecdown") {
  //     }
  //   }else if(systType == kJERUp){
  //     if(systname == "jerup") {
  //     }
  //   }else if(systType == kJERDown){
  //     if(systname == "jerdown") {
  //     }
  //   }//systType condn
  // }//syst loop
  

  return true;
}

//_____________________________________________________________________________
bool SkimAna::FillEventCFHists(int isyst, double combined_muwt, double combined_muwt1, double combined_elewt){

  //mu
  if(evtPick->passTrigger_mu){
      
    TList *list = (TList *)fFileDir[isyst*fNDDReg + 0]->GetList();
    TList *list1 = (TList *)fFileDir[isyst*fNDDReg + 1]->GetList();
    TList *list2 = (TList *)fFileDir[isyst*fNDDReg + 2]->GetList();
    TList *list3 = (TList *)fFileDir[isyst*fNDDReg + 3]->GetList();
	  
    FillCFHists(list, "", true, 0.0, combined_muwt, combined_muwt1);
    FillCFHists(list1, "_lmet", true, 0.0, combined_muwt, combined_muwt1);
    FillCFHists(list2, "_noniso", true, 0.0, combined_muwt, combined_muwt1);
    FillCFHists(list3, "_noniso_lmet", true, 0.0, combined_muwt, combined_muwt1);
      
    if(selector->isPVGood and evtPick->passFilter){

      FillCFHists(list, "", true, 1.0, combined_muwt, combined_muwt1);
      FillCFHists(list1, "_lmet", true, 1.0, combined_muwt, combined_muwt1);
      FillCFHists(list2, "_noniso", true, 1.0, combined_muwt, combined_muwt1);
      FillCFHists(list3, "_noniso_lmet", true, 1.0, combined_muwt, combined_muwt1);

    }
  }//mu condn

  //elec
  if(evtPick->passTrigger_ele){

    TList *list = (TList *)fFileDir[isyst*fNDDReg + 0]->GetList();
    TList *list1 = (TList *)fFileDir[isyst*fNDDReg + 1]->GetList();
    TList *list2 = (TList *)fFileDir[isyst*fNDDReg + 2]->GetList();
    TList *list3 = (TList *)fFileDir[isyst*fNDDReg + 3]->GetList();
	  
    FillCFHists(list, "", false, 0.0, combined_elewt, 1.0);
    FillCFHists(list1, "_lmet", false, 0.0, combined_elewt, 1.0);
    FillCFHists(list2, "_noniso", false, 0.0, combined_elewt, 1.0);
    FillCFHists(list3, "_noniso_lmet", false, 0.0, combined_elewt, 1.0);
      
    if(selector->isPVGood and evtPick->passFilter){

      FillCFHists(list, "", false, 1.0, combined_elewt, 1.0);
      FillCFHists(list1, "_lmet", false, 1.0, combined_elewt, 1.0);
      FillCFHists(list2, "_noniso", false, 1.0, combined_elewt, 1.0);
      FillCFHists(list3, "_noniso_lmet", false, 1.0, combined_elewt, 1.0);
	    
    }
  }//ele condn
  
  return true;
}
//_____________________________________________________________________________

bool SkimAna::FillEventCutFlow(){

  for(int isyst=0;isyst<fNSyst;isyst++){

    TString systname = fSystList[isyst];

    double combined_muwt = _sampleWeight*_prefireWeight*_PUWeight;
    double combined_muwt1 = _sampleWeight*_PUWeight;
    double combined_elewt = _sampleWeight*_prefireWeight*_PUWeight;

    if(systType == kBase){

      if(!systname.Contains("jec") and !systname.Contains("jer") and !systname.Contains("iso20") and !systname.Contains("met") ){

	double puwt = _PUWeight ; if(systname == "puup") puwt = _PUWeight_Up ; if(systname == "pudown") puwt = _PUWeight_Do ;
	double prefirewt = _prefireWeight ; if(systname == "prefireup")  prefirewt = _prefireWeight_Up ; if(systname == "prefiredown") prefirewt = _prefireWeight_Do ;
	//printf("syst : %s, puwt : %f, prefirewt : %f\n",systname.Data(),puwt,prefirewt);

	combined_muwt = _sampleWeight*prefirewt*puwt;
	combined_muwt1 = _sampleWeight*puwt;
	combined_elewt = _sampleWeight*prefirewt*puwt;
	
	FillEventCFHists(isyst, combined_muwt, combined_muwt1, combined_elewt);

      }//no jec and/or jer condn
      
    }else if(systType == kIso20){ //if(systType == kBase){

      if(systname.Contains("iso20")) {
	
	FillEventCFHists(isyst, combined_muwt, combined_muwt1, combined_elewt);
	
      }//iso20 condn

    }else { //if(systType == kBase){
      
      if( (systType == kJECUp and systname == "jecup") or (systType == kJECDown and systname == "jecdown") 
	  or (systType == kJERUp and systname == "jerup") or (systType == kJERDown and systname == "jerdown")
	  or (systType == kMETUp and systname == "metup") or (systType == kMETDown and systname == "metdown")){
	
	FillEventCFHists(isyst, combined_muwt, combined_muwt1, combined_elewt);
	
      }//jec jer condn
    }//systType    
  }//syst loop
  
  return true;
}

//_____________________________________________________________________________

bool SkimAna::FillBTagWt(bool singleMu, bool muonIsoCut, bool muonNonIsoCut, bool singleEle, bool eleIsoCut, bool eleNonIsoCut, bool isLowMET){

  // histWt[fNWtHists*isyst + 0] = new TH1D("_sampleWeight","_sampleWeight",2000, -10, 10);
  // histWt[fNWtHists*isyst + 1] = new TH1D("_PUWeight","_PUWeight", 2000, -10, 10);
  // histWt[fNWtHists*isyst + 2] = new TH1D("_prefireWeight","_prefireWeight",2000, -10, 10);
  // histWt[fNWtHists*isyst + 3] = new TH1D("_muEffWeight","_muEffWeight",2000, -10, 10);
  // histWt[fNWtHists*isyst + 4] = new TH1D("_eleEffWeight","_eleEffWeight",2000, -10, 10);
  // histWt[fNWtHists*isyst + 5] = new TH1D("_btagWeight_1a","_btagWeight_1a",2000, -10, 10);
  // histWt[fNWtHists*isyst + 6] = new TH1D("_btagWeight_1a_b_Do","_btagWeight_1a_b_Do",2000, -10, 10);
  // histWt[fNWtHists*isyst + 7] = new TH1D("_btagWeight_1a_b_Up","_btagWeight_1a_b_Up",2000, -10, 10);
  // histWt[fNWtHists*isyst + 8] = new TH1D("_btagWeight_1a_l_Do","_btagWeight_1a_l_Do",2000, -10, 10);
  // histWt[fNWtHists*isyst + 9] = new TH1D("_btagWeight_1a_l_Up","_btagWeight_1a_l_Up",2000, -10, 10);
  // histWt[fNWtHists*isyst + 10] = new TH1D("_muEffWeight_Up","_muEffWeight_Up",2000, -10, 10);
  // histWt[fNWtHists*isyst + 11] = new TH1D("_muEffWeight_Do","_muEffWeight_Do",2000, -10, 10);
  // histWt[fNWtHists*isyst + 12] = new TH1D("_eleEffWeight_Up","_eleEffWeight_Up",2000, -10, 10);
  // histWt[fNWtHists*isyst + 13] = new TH1D("_eleEffWeight_Do","_eleEffWeight_Do",2000, -10, 10);
  // histWt[fNWtHists*isyst + 14] = new TH1D("_pdfweight_Up","_pdfweight_Up",2000, -10, 10);
  // histWt[fNWtHists*isyst + 15] = new TH1D("_pdfweight_Do","_pdfweight_Do",2000, -10, 10);
  // histWt[fNWtHists*isyst + 16] = new TH1D("_q2weight_Up","_q2weight_Up",2000, -10, 10);
  // histWt[fNWtHists*isyst + 17] = new TH1D("_q2weight_Do","_q2weight_Do",2000, -10, 10);
  // histWt[fNWtHists*isyst + 18] = new TH1D("_FSRweight_Up","_FSRweight_Up",2000, -10, 10);
  // histWt[fNWtHists*isyst + 19] = new TH1D("_FSRweight_Do","_FSRweight_Do",2000, -10, 10);
  // histWt[fNWtHists*isyst + 20] = new TH1D("_ISRweight_Up","_ISRweight_Up",2000, -10, 10);
  // histWt[fNWtHists*isyst + 21] = new TH1D("_ISRweight_Do","_ISRweight_Do",2000, -10, 10);
  // histWt[fNWtHists*isyst + 22] = new TH1D("_PUWeight_Up","_PUWeight_Up",2000, -10, 10);
  // histWt[fNWtHists*isyst + 23] = new TH1D("_PUWeight_Do","_PUWeight_Do",2000, -10, 10);
  // histWt[fNWtHists*isyst + 24] = new TH1D("_topPtReweight","_topPtReweight",2000, -10, 10);
  // histWt[fNWtHists*isyst + 25] = new TH1D("_muIso","_muIso", 100, 0., 1.);
  // histWt[fNWtHists*isyst + 26] = new TH1D("_eleIso","_eleIso", 100, 0., 1.);
  // histWt[fNWtHists*isyst + 27] = new TH1D("_muMET","_muMET", 100, 0., 500.);
  // histWt[fNWtHists*isyst + 28] = new TH1D("_eleMET","_eleMET", 100, 0., 500.);
  
  for(int isyst=0;isyst<fNSyst;isyst++){
    TList *list = (TList *)fFileDir[isyst*fNDDReg + 0]->GetList();
    
    ((TH1D *) list->FindObject("_pdfweight_Up"))->Fill(_pdfweight_Up);
    ((TH1D *) list->FindObject("_pdfweight_Do"))->Fill(_pdfweight_Do);
    ((TH1D *) list->FindObject("_q2weight_Up"))->Fill(_q2weight_Up);
    ((TH1D *) list->FindObject("_q2weight_Do"))->Fill(_q2weight_Do);
    ((TH1D *) list->FindObject("_FSRweight_Up"))->Fill(_FSRweight_Up);
    ((TH1D *) list->FindObject("_FSRweight_Do"))->Fill(_FSRweight_Do);
    ((TH1D *) list->FindObject("_ISRweight_Up"))->Fill(_ISRweight_Up);
    ((TH1D *) list->FindObject("_ISRweight_Do"))->Fill(_ISRweight_Do);
    ((TH1D *) list->FindObject("_btagWeight_1a_b_Up"))->Fill(_bTagWeight_b_Up);
    ((TH1D *) list->FindObject("_btagWeight_1a_b_Do"))->Fill(_bTagWeight_b_Do);
    ((TH1D *) list->FindObject("_btagWeight_1a_l_Up"))->Fill(_bTagWeight_l_Up);
    ((TH1D *) list->FindObject("_btagWeight_1a_l_Do"))->Fill(_bTagWeight_l_Do);
    ((TH1D *) list->FindObject("_btagWeight_1a"))->Fill(_bTagWeight);
    ((TH1D *) list->FindObject("_topPtReweight"))->Fill(_topPtReWeight);
  }
  return true;
}

//_____________________________________________________________________________

bool SkimAna::FillNjetWt(bool singleMu, bool muonIsoCut, bool muonNonIsoCut, bool singleEle, bool eleIsoCut, bool eleNonIsoCut){

  for(int isyst=0;isyst<fNSyst;isyst++){
    TList *list = (TList *)fFileDir[isyst*fNDDReg + 0]->GetList();
    if(singleMu)
      ((TH1D *) list->FindObject("_muMET"))->Fill(selector->METPt);
    if(singleEle)
      ((TH1D *) list->FindObject("_eleMET"))->Fill(selector->METPt);
  }
  return true;
}

//_____________________________________________________________________________

bool SkimAna::FillLeptonIso(bool singleMu, bool singleEle){

  for(int isyst=0;isyst<fNSyst;isyst++){
    TList *list = (TList *)fFileDir[isyst*fNDDReg + 0]->GetList();
  
    if(singleMu)
      ((TH1D *) list->FindObject("_muIso"))->Fill(event->muPFRelIso_[selector->MuonsNoIso.at(0)]);
    if(singleEle)
      ((TH1D *) list->FindObject("_eleIso"))->Fill(event->elePFRelIso_[selector->ElectronsNoIso.at(0)]);
  }

  return true;

}
//_____________________________________________________________________________

bool SkimAna::FillLeptonWt(bool singleMu, bool muonIsoCut, bool muonNonIsoCut, bool singleEle, bool eleIsoCut, bool eleNonIsoCut){

  for(int isyst=0;isyst<fNSyst;isyst++){
    TList *list = (TList *)fFileDir[isyst*fNDDReg + 0]->GetList();
    TList *list1 = (TList *)fFileDir[isyst*fNDDReg + 1]->GetList();
    TList *list2 = (TList *)fFileDir[isyst*fNDDReg + 2]->GetList();
    TList *list3 = (TList *)fFileDir[isyst*fNDDReg + 3]->GetList();

    if(singleMu and muonIsoCut){
      ((TH1D *) list->FindObject("_muEffWeight"))->Fill(_muEffWeight);
      ((TH1D *) list->FindObject("_muEffWeight_Up"))->Fill(_muEffWeight_Up);
      ((TH1D *) list->FindObject("_muEffWeight_Do"))->Fill(_muEffWeight_Do);

      ((TH1D *) list1->FindObject("_muEffWeight_lmet"))->Fill(_muEffWeight);
      ((TH1D *) list1->FindObject("_muEffWeight_Up_lmet"))->Fill(_muEffWeight_Up);
      ((TH1D *) list1->FindObject("_muEffWeight_Do_lmet"))->Fill(_muEffWeight_Do);
    }
    if(singleMu and muonNonIsoCut){
      ((TH1D *) list2->FindObject("_muEffWeight_noniso"))->Fill(_muEffWeight);
      ((TH1D *) list2->FindObject("_muEffWeight_Up_noniso"))->Fill(_muEffWeight_Up);
      ((TH1D *) list2->FindObject("_muEffWeight_Do_noniso"))->Fill(_muEffWeight_Do);

      ((TH1D *) list3->FindObject("_muEffWeight_noniso_lmet"))->Fill(_muEffWeight);
      ((TH1D *) list3->FindObject("_muEffWeight_Up_noniso_lmet"))->Fill(_muEffWeight_Up);
      ((TH1D *) list3->FindObject("_muEffWeight_Do_noniso_lmet"))->Fill(_muEffWeight_Do);

    }

    if(singleEle and eleIsoCut){
      ((TH1D *) list->FindObject("_eleEffWeight"))->Fill(_eleEffWeight);
      ((TH1D *) list->FindObject("_eleEffWeight_Up"))->Fill(_eleEffWeight_Up);
      ((TH1D *) list->FindObject("_eleEffWeight_Do"))->Fill(_eleEffWeight_Do);

      ((TH1D *) list1->FindObject("_eleEffWeight_lmet"))->Fill(_eleEffWeight);
      ((TH1D *) list1->FindObject("_eleEffWeight_Up_lmet"))->Fill(_eleEffWeight_Up);
      ((TH1D *) list1->FindObject("_eleEffWeight_Do_lmet"))->Fill(_eleEffWeight_Do);
    }
    if(singleEle and eleNonIsoCut){
      ((TH1D *) list2->FindObject("_eleEffWeight_noniso"))->Fill(_eleEffWeight);
      ((TH1D *) list2->FindObject("_eleEffWeight_Up_noniso"))->Fill(_eleEffWeight_Up);
      ((TH1D *) list2->FindObject("_eleEffWeight_Do_noniso"))->Fill(_eleEffWeight_Do);

      ((TH1D *) list3->FindObject("_eleEffWeight_noniso_lmet"))->Fill(_eleEffWeight);
      ((TH1D *) list3->FindObject("_eleEffWeight_Up_noniso_lmet"))->Fill(_eleEffWeight_Up);
      ((TH1D *) list3->FindObject("_eleEffWeight_Do_noniso_lmet"))->Fill(_eleEffWeight_Do);

    }
  }
  return true;
}

//_____________________________________________________________________________

bool SkimAna::FillEventWt(){
  
  for(int isyst=0;isyst<fNSyst;isyst++){
    TList *list = (TList *)fFileDir[isyst*fNDDReg + 0]->GetList();
    ((TH1D *) list->FindObject("_sampleWeight"))->Fill(_sampleWeight);
    ((TH1D *) list->FindObject("_PUWeight"))->Fill(_PUWeight);
    ((TH1D *) list->FindObject("_prefireWeight"))->Fill(_prefireWeight);
    ((TH1D *) list->FindObject("_PUWeight_Up"))->Fill(_PUWeight_Up);
    ((TH1D *) list->FindObject("_PUWeight_Do"))->Fill(_PUWeight_Do);
  }

  return true;
}

//_____________________________________________________________________________
bool SkimAna::ProcessKinFit(bool isMuon, bool isEle)
{
  if( (isMuon and isEle) or (!isMuon and !isEle) ) return false;

  bool isValid = false;
  float jetPtThresh, lepPtThresh;
  if(isNanoAOD){
    jetPtThresh = selector->jet_Pt_cut ;
    lepPtThresh = (isEle)? selector->ele_Pt_cut : selector->mu_Pt_cut ;
  }else{
    jetPtThresh = selector->jet_Pt_cut_miniAOD ;
    lepPtThresh = (isEle)? selector->ele_Pt_cut_miniAOD : selector->mu_Pt_cut_miniAOD ;
  }

  float jetEtaThresh, lepEtaThresh;
  if(isNanoAOD){
    jetEtaThresh = selector->jet_Eta_cut ;
    lepEtaThresh = (isEle)? selector->ele_Eta_cut : selector->mu_Eta_tight ; 
  }else{
    jetEtaThresh = selector->jet_Eta_cut_miniAOD ;
    lepEtaThresh = (isEle)? selector->ele_Eta_cut_miniAOD : selector->mu_Eta_tight ; //tight for muon in miniAOD is correct
  }
  

  jetVectors.clear();
  jetBtagVectors.clear();

  _run = event->run_ ;
  _event = event->event_ ;
  _lumis = event->lumis_ ;
  _isData = event->isData_ ;
  _nVtx = event->nVtx_ ;
  _nGoodVtx = event->nGoodVtx_ ;
  
  _nJet = selector->Jets.size();
  _nBJet = 0 ;
  
  //cout<<" _jetPt : " << _jetPt << endl;
  //return true;
  

  _jetPt->clear() ;
  _jetEta->clear() ;
  _jetPhi->clear() ;
  _jetMass->clear() ;
  _jetDeepB->clear() ;
  double btagThreshold = (selector->useDeepCSVbTag) ? selector->btag_cut_DeepCSV  : selector->btag_cut  ;
  for (unsigned int ijet = 0; ijet < selector->Jets.size(); ijet++){
    int jetInd = selector->Jets.at(ijet);
    jetVector.SetPtEtaPhiM(selector->JetsPtSmeared.at(ijet), event->jetEta_[jetInd] , event->jetPhi_[jetInd] , event->jetMass_[jetInd] );
    jetVectors.push_back(jetVector);
    double jetBtag = (selector->useDeepCSVbTag) ? event->jetBtagDeepB_[jetInd] : event->jetBtagCSVV2_[jetInd] ;
    jetBtagVectors.push_back( jetBtag );
    
    _jetPt->push_back(selector->JetsPtSmeared.at(ijet));
    _jetEta->push_back(event->jetEta_[jetInd]);
    _jetPhi->push_back(event->jetPhi_[jetInd]);
    _jetMass->push_back(event->jetMass_[jetInd]);
    _jetDeepB->push_back(jetBtag);
    if(jetBtag>btagThreshold)
      _nBJet++;
  }
  
  _nMu = selector->MuonsNoIso.size();
  _muPt->clear();
  _muEta->clear();
  _muPhi->clear();
  _muCharge->clear();
  _muPFRelIso->clear();
  if(isMuon){
    lepVector.SetPtEtaPhiM( event->muPt_[selector->MuonsNoIso.at(0)] * event->muRoccoR_[selector->MuonsNoIso.at(0)], 
			    event->muEta_[selector->MuonsNoIso.at(0)] , event->muPhi_[selector->MuonsNoIso.at(0)], 
			    TDatabasePDG::Instance()->GetParticle(13)->Mass());
    
    _muPt->push_back(event->muPt_[selector->MuonsNoIso.at(0)] * event->muRoccoR_[selector->MuonsNoIso.at(0)]);
    _muEta->push_back(event->muEta_[selector->MuonsNoIso.at(0)]);
    _muPhi->push_back(event->muPhi_[selector->MuonsNoIso.at(0)]);
    _muCharge->push_back(event->muCharge_[selector->MuonsNoIso.at(0)]);
    _muPFRelIso->push_back(event->muPFRelIso_[selector->MuonsNoIso.at(0)]);
  }

  _nEle = selector->ElectronsNoIso.size();
  _elePt->clear();
  _eleEta->clear();
  _elePhi->clear();
  _eleCharge->clear();
  _elePFRelIso->clear();
  if(isEle){
    lepVector.SetPtEtaPhiM( event->elePt_[selector->ElectronsNoIso.at(0)], event->eleEta_[selector->ElectronsNoIso.at(0)], 
			    event->elePhi_[selector->ElectronsNoIso.at(0)], TDatabasePDG::Instance()->GetParticle(11)->Mass());
    _elePt->push_back(event->elePt_[selector->ElectronsNoIso.at(0)]);
    _eleEta->push_back(event->eleEta_[selector->ElectronsNoIso.at(0)]);
    _elePhi->push_back(event->elePhi_[selector->ElectronsNoIso.at(0)]);
    _eleCharge->push_back(event->eleCharge_[selector->ElectronsNoIso.at(0)]);
    _elePFRelIso->push_back(event->elePFRelIso_[selector->ElectronsNoIso.at(0)]);
  }		    
  

  kinFit.SetJetVector(jetVectors);
  //kinFit.SetJetResVector(jetResolutionVectors);
  kinFit.SetBtagVector(jetBtagVectors);
  kinFit.SetLepton(lepVector);
  KinFit::LeptonType ltype = (isEle)?(KinFit::kElectron):(KinFit::kMuon); 
  kinFit.SetLeptonType(ltype);
  kinFit.SetMETPtPhi(selector->METPt, selector->METPhi);
  
  if ( kinFit.Fit() ){

    Chi2Array	     Chi2ToMass;
    vector<Chi2Array> Chi2ToMass_arr;    	    
    //Chi2ToMass_arr.clear();    
    
    for (unsigned int i = 0 ; i < kinFit.GetNCombinations() ; i++ ){
      
      leptonAF		= kinFit.GetLepton(i);
      neutrinoAF	= kinFit.GetNeutrino(i);
      bjlepAF		= kinFit.GetBLepton(i);
      bjhadAF		= kinFit.GetBHadron(i);
      cjhadAF		= kinFit.GetCHadron(i);
      sjhadAF		= kinFit.GetSHadron(i);
      
      leptonBF		= kinFit.GetLeptonUM(i);
      neutrinoBF        = kinFit.GetNeutrinoUM(i);
      bjlepBF		= kinFit.GetBLeptonUM(i);
      bjhadBF		= kinFit.GetBHadronUM(i);
      cjhadBF		= kinFit.GetCHadronUM(i);
      sjhadBF		= kinFit.GetSHadronUM(i);
      
      if(leptonAF.E()<0.0 or neutrinoAF.E()<0.0 or bjlepAF.E()<0.0 or bjhadAF.E()<0.0 or cjhadAF.E()<0.0 or sjhadAF.E()<0.0) continue;

      lepTopAF = (leptonAF + neutrinoAF + bjlepAF) ;
      hadTopAF = (bjhadAF + cjhadAF + sjhadAF);
      
      double mjj	= (cjhadBF + sjhadBF).M(); 
      double mjjkF	= (cjhadAF + sjhadAF).M(); 
      
      Chi2ToMass.chi2			= kinFit.GetChi2(i);
      Chi2ToMass.mass			= mjjkF;
      Chi2ToMass.mW			= (leptonAF + neutrinoAF).M();
      Chi2ToMass.A			= 1.;
      Chi2ToMass.B			= 1.;
      Chi2ToMass.ndf			= kinFit.GetNDF(i);
      Chi2ToMass.nb_iter		= kinFit.GetNumberOfIter(i);
      Chi2ToMass.chi2_thad		= kinFit.GetChi2_thad(i);
      Chi2ToMass.chi2_tlep		= kinFit.GetChi2_tlep(i);
      Chi2ToMass.leptonAF		= leptonAF;
      Chi2ToMass.neutrinoAF		= neutrinoAF;
      Chi2ToMass.bjlepAF		= bjlepAF; 
      Chi2ToMass.bjhadAF		= bjhadAF;
      Chi2ToMass.cjhadAF		= cjhadAF;
      Chi2ToMass.sjhadAF		= sjhadAF;
      Chi2ToMass.leptonBF		= leptonBF;
      Chi2ToMass.neutrinoBF		= neutrinoBF;
      Chi2ToMass.bjlepBF		= bjlepBF; 
      Chi2ToMass.bjhadBF		= bjhadBF;
      Chi2ToMass.cjhadBF		= cjhadBF;
      Chi2ToMass.sjhadBF		= sjhadBF;
      Chi2ToMass.bjhadAF_thad		= kinFit.GetBHadron_thad(i);
      Chi2ToMass.cjhadAF_thad		= kinFit.GetCHadron_thad(i);    
      Chi2ToMass.sjhadAF_thad		= kinFit.GetSHadron_thad(i);
      Chi2ToMass.leptonAF_tlep		= kinFit.GetLepton_tlep(i);
      Chi2ToMass.neutrinoAF_tlep	= kinFit.GetNeutrino_tlep(i);
      Chi2ToMass.bjlepAF_tlep		= kinFit.GetBLepton_tlep(i);
      
      Chi2ToMass.reslepEta		= kinFit.GetResLepEta(i);
      Chi2ToMass.reslepPhi		= kinFit.GetResLepPhi(i);
      Chi2ToMass.resneuEta		= kinFit.GetResNeuEta(i);
      Chi2ToMass.resneuPhi		= kinFit.GetResNeuPhi(i);
      Chi2ToMass.resbjlepEta		= kinFit.GetResBjLepEta(i);
      Chi2ToMass.resbjlepPhi		= kinFit.GetResBjLepPhi(i);
      Chi2ToMass.resbjhadEta		= kinFit.GetResBjHadEta(i);
      Chi2ToMass.resbjhadPhi		= kinFit.GetResBjHadPhi(i);
      Chi2ToMass.rescjhadEta		= kinFit.GetResCjHadEta(i);
      Chi2ToMass.rescjhadPhi		= kinFit.GetResCjHadPhi(i);
      Chi2ToMass.ressjhadEta		= kinFit.GetResSjHadEta(i);
      Chi2ToMass.ressjhadPhi		= kinFit.GetResSjHadPhi(i);
      
      Chi2ToMass.bjlep_id		= kinFit.GetJetID_BLep(i); 
      Chi2ToMass.bjhad_id		= kinFit.GetJetID_BHad(i); 
      Chi2ToMass.cjhad_id		= kinFit.GetJetID_CHad(i);
      Chi2ToMass.sjhad_id		= kinFit.GetJetID_SHad(i);
      
      Chi2ToMass_arr.push_back(Chi2ToMass);
      
      
    }// for loop over all kinfit combinations
    
    std::sort(Chi2ToMass_arr.begin(), Chi2ToMass_arr.end(), compareChi2Array);
    //
    int iloop = 0;
    for (auto x : Chi2ToMass_arr){
      //cout << "[" << x.chi2 << ", " << x.mass << "] ";
      
      //new
      double Rdifflep	= x.leptonBF.DeltaR(x.leptonAF); 
      double Rdiffbjlep	= x.bjlepBF.DeltaR(x.bjlepAF);  
      double Rdiffbjhad	= x.bjhadBF.DeltaR(x.bjhadAF); 
      double Rdiffcjhad	= x.cjhadBF.DeltaR(x.cjhadAF); 
      double Rdiffsjhad	= x.sjhadBF.DeltaR(x.sjhadAF); 
      
      double dRcjsjBF,	dRcjsjAF,  dRLepNuBF,	dRLepNuAF;
      dRcjsjBF	= x.cjhadBF.DeltaR(x.sjhadBF);     dRcjsjAF  = x.cjhadAF.DeltaR(x.sjhadAF);
      dRLepNuBF	= x.leptonBF.DeltaR(x.neutrinoBF); dRLepNuAF = x.leptonAF.DeltaR(x.neutrinoAF);
      //
      
      //if(iloop == 0 && x.chi2 > -1.0 ){ // Only 1st min chi2
      //if(iloop == 0 && x.chi2 >= 0.0 && x.chi2 < 20.){ // Only 1st min chi2
      if(iloop == 0 && x.chi2 >= 0.0 && x.chi2 < 8.){ // Only 1st min chi2, tight cut
    	if(
	   x.leptonAF.Pt() > lepPtThresh and x.neutrinoAF.Pt() > METThreshold 
	   and 
	   x.bjhadAF.Pt()  > jetPtThresh and x.bjlepAF.Pt() > jetPtThresh and x.cjhadAF.Pt() > jetPtThresh and x.sjhadAF.Pt() > jetPtThresh 
	   and
	   abs(x.leptonAF.Eta()) < lepEtaThresh 
	   and
	   abs(x.bjhadAF.Eta()) < jetEtaThresh and abs(x.bjlepAF.Eta()) < jetEtaThresh and abs(x.cjhadAF.Eta()) < jetEtaThresh and abs(x.sjhadAF.Eta()) < jetEtaThresh
    	   and
	   Rdifflep < 0.2 and Rdiffbjlep < 0.2 and Rdiffbjhad < 0.2 and Rdiffcjhad < 0.2 and Rdiffsjhad < 0.2
	   ){
	  
    	  //hMjjkFsc->Fill(x.mass);
	  
	  kinFitMinChi2		= x.chi2;
	  
	  leptonAF		= x.leptonAF;
	  neutrinoAF		= x.neutrinoAF;
	  
	  bjlepAF		= x.bjlepAF;
	  bjhadAF		= x.bjhadAF;
	  
	  cjhadAF		= x.cjhadAF;
	  sjhadAF		= x.sjhadAF;
	  
	  cjhadBF		= x.cjhadBF;
	  sjhadBF		= x.sjhadBF;
	  
	  isValid		= true;
	  
	  //To fill the Tree for DNN other MVA
	  _chi2			= x.chi2;
	  _chi2_thad     	= x.chi2_thad;
	  _chi2_tlep     	= x.chi2_tlep;
	  _NDF			= x.ndf;
	  _Nbiter		= x.nb_iter ;
	  _M_jj			= (x.cjhadBF + x.sjhadBF).M();
	  _M_jjkF		= x.mass;
	  
	  _pfMET		= x.neutrinoBF.Pt() ;
	  _pfMETPhi		= x.neutrinoBF.Phi() ;
	  _nu_px		= x.neutrinoBF.Px() ;
	  _nu_py		= x.neutrinoBF.Py() ;
	  _nu_pz		= x.neutrinoBF.Pz() ;
	  //_nu_pz_other	= 0 ;
	  _jetBlepPtUM		= x.bjlepBF.Pt() ;
	  _jetBlepEtaUM		= x.bjlepBF.Eta() ;
	  _jetBlepPhiUM		= x.bjlepBF.Phi() ;
	  _jetBlepEnergyUM	= x.bjlepBF.E() ;
	  _jetBhadPtUM		= x.bjhadBF.Pt() ;
	  _jetBhadEtaUM		= x.bjhadBF.Eta() ;
	  _jetBhadPhiUM		= x.bjhadBF.Phi() ;
	  _jetBhadEnergyUM	= x.bjhadBF.E() ;
	  _jetChadPtUM		= x.cjhadBF.Pt() ;
	  _jetChadEtaUM		= x.cjhadBF.Eta() ;
	  _jetChadPhiUM		= x.cjhadBF.Phi() ;
	  _jetChadEnergyUM	= x.cjhadBF.E() ;
	  _jetShadPtUM		= x.sjhadBF.Pt() ;
	  _jetShadEtaUM		= x.sjhadBF.Eta()  ;
	  _jetShadPhiUM		= x.sjhadBF.Phi()  ;
	  _jetShadEnergyUM	= x.sjhadBF.E()  ;
	  
	  _lepPt		= x.leptonAF.Pt() ;
	  _lepEta		= x.leptonAF.Eta() ;
	  _lepPhi		= x.leptonAF.Phi() ;
	  _lepEnergy		= x.leptonAF.E() ;
	  _metPx		= x.neutrinoAF.Px() ;
	  _metPy		= x.neutrinoAF.Py() ;
	  _metPz		= x.neutrinoAF.Pz() ;
	  _jetBlepPt		= x.bjlepAF.Pt() ;
	  _jetBlepEta		= x.bjlepAF.Eta() ;
	  _jetBlepPhi		= x.bjlepAF.Phi() ;
	  _jetBlepEnergy	= x.bjlepAF.E() ;
	  _jetBhadPt		= x.bjhadAF.Pt() ;
	  _jetBhadEta		= x.bjhadAF.Eta() ;
	  _jetBhadPhi		= x.bjhadAF.Phi() ;
	  _jetBhadEnergy	= x.bjhadAF.E() ;
	  _jetChadPt		= x.cjhadAF.Pt() ;
	  _jetChadEta		= x.cjhadAF.Eta() ;
	  _jetChadPhi		= x.cjhadAF.Phi() ;
	  _jetChadEnergy	= x.cjhadAF.E() ;
	  _jetShadPt		= x.sjhadAF.Pt() ;
	  _jetShadEta		= x.sjhadAF.Eta()  ;
	  _jetShadPhi		= x.sjhadAF.Phi()  ;
	  _jetShadEnergy	= x.sjhadAF.E()  ;
	  
	  _reslepEta		= x.reslepEta ;   
	  _reslepPhi		= x.reslepPhi ;   
	  _resneuEta		= x.resneuEta ;   
	  _resneuPhi		= x.resneuPhi ;
	  _resbjlepEta		= x.resbjlepEta ;
	  _resbjlepPhi		= x.resbjlepPhi ; 
	  _resbjhadEta		= x.resbjhadEta ; 
	  _resbjhadPhi		= x.resbjhadPhi ;
	  _rescjhadEta		= x.rescjhadEta ; 
	  _rescjhadPhi		= x.rescjhadPhi ; 
	  _ressjhadEta		= x.ressjhadEta ; 
	  _ressjhadPhi		= x.ressjhadPhi ; 
	  _bjlepDeepCSV		= jetBtagVectors[x.bjlep_id] ;
	  _bjhadDeepCSV		= jetBtagVectors[x.bjhad_id] ; 
	  _cjhadDeepCSV		= jetBtagVectors[x.cjhad_id] ;  
	  _sjhadDeepCSV		= jetBtagVectors[x.sjhad_id] ;
	  _bjlep_id		= x.bjlep_id ;
	  _bjhad_id		= x.bjhad_id ;
	  _cjhad_id		= x.cjhad_id ;
	  _sjhad_id		= x.sjhad_id ;
		      
	  //Fill for non-negative chi2
	  if(doTreeSave)
	    outputTree->Fill();
	}//DeltaR and pt cuts
      }//iloop == 0 condition      
      iloop++;
    }// for loop over chi2 arrays

    if(isMuon){
      if(Chi2ToMass_arr.size()>=1 and Chi2ToMass_arr.at(0).leptonAF.Pt() > 0.0)
	hMinChi2_mu->Fill(Chi2ToMass_arr.at(0).chi2);
      if(Chi2ToMass_arr.size()>=2 and Chi2ToMass_arr.at(0).leptonAF.Pt() > 0.0)
	h2MinChi2_mu->Fill(Chi2ToMass_arr.at(1).chi2);
      if(Chi2ToMass_arr.size()>=3 and Chi2ToMass_arr.at(0).leptonAF.Pt() > 0.0)
	h3MinChi2_mu->Fill(Chi2ToMass_arr.at(2).chi2);
      if(Chi2ToMass_arr.size()>=4 and Chi2ToMass_arr.at(0).leptonAF.Pt() > 0.0)
	h4MinChi2_mu->Fill(Chi2ToMass_arr.at(3).chi2);
      if(Chi2ToMass_arr.size()>=5 and Chi2ToMass_arr.at(0).leptonAF.Pt() > 0.0)
	h5MinChi2_mu->Fill(Chi2ToMass_arr.at(4).chi2);
    }else{
      if(Chi2ToMass_arr.size()>=1 and Chi2ToMass_arr.at(0).leptonAF.Pt() > 0.0)
	hMinChi2_ele->Fill(Chi2ToMass_arr.at(0).chi2);
      if(Chi2ToMass_arr.size()>=2 and Chi2ToMass_arr.at(0).leptonAF.Pt() > 0.0)
	h2MinChi2_ele->Fill(Chi2ToMass_arr.at(1).chi2);
      if(Chi2ToMass_arr.size()>=3 and Chi2ToMass_arr.at(0).leptonAF.Pt() > 0.0)
	h3MinChi2_ele->Fill(Chi2ToMass_arr.at(2).chi2);
      if(Chi2ToMass_arr.size()>=4 and Chi2ToMass_arr.at(0).leptonAF.Pt() > 0.0)
	h4MinChi2_ele->Fill(Chi2ToMass_arr.at(3).chi2);
      if(Chi2ToMass_arr.size()>=5 and Chi2ToMass_arr.at(0).leptonAF.Pt() > 0.0)
	h5MinChi2_ele->Fill(Chi2ToMass_arr.at(4).chi2);
    }

    Chi2ToMass_arr.clear();
    
  }//if fit converges
  
  kinFit.Clear();
  jetVectors.clear();
  jetBtagVectors.clear();
  _jetPt->clear() ;
  _jetEta->clear() ;
  _jetPhi->clear() ;
  _jetMass->clear() ;
  _jetDeepB->clear() ;
  _muPt->clear();
  _muEta->clear();
  _muPhi->clear();
  _muCharge->clear();
  _muPFRelIso->clear();
  _elePt->clear();
  _eleEta->clear();
  _elePhi->clear();
  _eleCharge->clear();
  _elePFRelIso->clear();

  return isValid;
}

//_____________________________________________________________________________
void SkimAna::SlaveTerminate()
{
  
  Info("SlaveTerminate",
       "sample : %s, year : %d, mode : %s", fSample.Data(), fYear, fMode.Data());

  
  // File closure
  TDirectory *savedir = gDirectory;
  
  for(int ifile=0;ifile<1;ifile++){

    savedir->cd();
    
    fFile[ifile]->cd();
    
    for(int isyst=0;isyst<fNSyst;isyst++){

      //method 1
      //fFileDir[isyst*fNDDReg + 0]->cd();
      // for(int icf=0;icf<fNBCFHists;icf++){
      // 	cout << "index : " << fNCFHists*isyst + icf << endl;
      // 	hCutFlow[fNCFHists*isyst + icf]->Write();
      // }
      //method 2
      // for(int il=0;il<fFileDir[isyst*fNDDReg + 0]->GetList()->GetEntries();il++)
      // 	fFileDir[isyst*fNDDReg + 0]->GetList()->At(il)->Write();
      //method 3
      //fFileDir[isyst*fNDDReg + 0]->Write();

      fFileDir[isyst*fNDDReg + 0]->Write();
      fFileDir[isyst*fNDDReg + 1]->Write();
      fFileDir[isyst*fNDDReg + 2]->Write();
      fFileDir[isyst*fNDDReg + 3]->Write();
      fFileDir[isyst*fNDDReg + 0]->cd();
      
      hMinChi2_mu->Write();
      h2MinChi2_mu->Write();
      h3MinChi2_mu->Write();
      h4MinChi2_mu->Write();
      h5MinChi2_mu->Write();
      
      hMinChi2_ele->Write();
      h2MinChi2_ele->Write();
      h3MinChi2_ele->Write();
      h4MinChi2_ele->Write();
      h5MinChi2_ele->Write();

      fFile[ifile]->cd();
    }
    
    fFile[ifile]->cd();

    // for(int icheck=0;icheck<fNWtHists;icheck++)
    //   histWt[icheck]->Write();
    // for(int icheck=0;icheck<fNObHists;icheck++)
    //   histObs[icheck]->Write();

    
    printf("DataMu & ");
    for (int ibin=2;ibin<hCutFlow[1]->GetNbinsX();ibin++){
      if(hCutFlow[1]->GetBinContent(ibin)>0.0 and hCutFlow[1]->GetBinContent(ibin+1)>0.0){
	if(hCutFlow[1]->GetBinContent(ibin)>1e6){
	  printf("%.4e & ",hCutFlow[1]->GetBinContent(ibin)); 
	}else{
	  printf("%.1f & ",hCutFlow[1]->GetBinContent(ibin));
	}
      }else if(hCutFlow[1]->GetBinContent(ibin)>0.0 and TMath::AreEqualAbs(hCutFlow[1]->GetBinContent(ibin+1),0.0,1.e-5)){
	printf("%.1f \\\\\\hline ",hCutFlow[1]->GetBinContent(ibin));
      }
    }
    printf("\n");

    printf("WtMu & ");
    for (int ibin=2;ibin<hCutFlow[2]->GetNbinsX();ibin++){
      if(hCutFlow[2]->GetBinContent(ibin)>0.0 and hCutFlow[2]->GetBinContent(ibin+1)>0.0){
	if(hCutFlow[2]->GetBinContent(ibin)>1e6){
	  printf("%.4e & ",hCutFlow[2]->GetBinContent(ibin)); 
	}else{
	  printf("%.1f & ",hCutFlow[2]->GetBinContent(ibin));
	}
      }else if(hCutFlow[2]->GetBinContent(ibin)>0.0 and TMath::AreEqualAbs(hCutFlow[2]->GetBinContent(ibin+1),0.0,1.e-5)){
	printf("%.1f \\\\\\hline ",hCutFlow[2]->GetBinContent(ibin));
      }
    }
    printf("\n");
    
    printf("DataEle & ");
    for (int ibin=2;ibin<hCutFlow[3]->GetNbinsX();ibin++){
      if(hCutFlow[3]->GetBinContent(ibin)>0.0 and hCutFlow[3]->GetBinContent(ibin+1)>0.0){
	if(hCutFlow[3]->GetBinContent(ibin)>1e6){
	  printf("%.4e & ",hCutFlow[3]->GetBinContent(ibin)); 
	}else{
	  printf("%.1f & ",hCutFlow[3]->GetBinContent(ibin));
	}
      }else if(hCutFlow[3]->GetBinContent(ibin)>0.0 and TMath::AreEqualAbs(hCutFlow[3]->GetBinContent(ibin+1),0.0,1.e-5)){
	printf("%.1f \\\\\\hline ",hCutFlow[3]->GetBinContent(ibin));
      }
    }
    printf("\n");

    printf("WtEle & ");
    for (int ibin=2;ibin<hCutFlow[4]->GetNbinsX();ibin++){
      if(hCutFlow[4]->GetBinContent(ibin)>0.0 and hCutFlow[4]->GetBinContent(ibin+1)>0.0){
	if(hCutFlow[4]->GetBinContent(ibin)>1e6){
	  printf("%.4e & ",hCutFlow[4]->GetBinContent(ibin)); 
	}else{
	  printf("%.1f & ",hCutFlow[4]->GetBinContent(ibin));
	}
      }else if(hCutFlow[4]->GetBinContent(ibin)>0.0 and TMath::AreEqualAbs(hCutFlow[4]->GetBinContent(ibin+1),0.0,1.e-5)){
	printf("%.1f \\\\\\hline ",hCutFlow[4]->GetBinContent(ibin));
      }
    }
    printf("\n");
    
      
    fFile[ifile]->cd();
    
    savedir->cd();
    
    fFile[ifile]->Close();
    
    
    if (fMode.BeginsWith("proof")) {
      Info("SlaveTerminate", "objects saved into '%s%s': sending related TProofOutputFile ...",
	   fProofFile[ifile]->GetFileName(), fProofFile[ifile]->GetOptionsAnchor());
      fProofFile[ifile]->Print();
      fOutput->Add(fProofFile[ifile]);    
    }
    
  }//file loop
  
  
  for(int ifile=1;ifile<2;ifile++){
    
    savedir->cd();
    
    fFile[ifile]->cd();
    if(doTreeSave){
      outputTree->Write();
    }
    fFile[ifile]->Close();
    savedir->cd();

    if (fMode.BeginsWith("proof")) {
      Info("SlaveTerminate", "objects saved into '%s%s': sending related TProofOutputFile ...",
	   fProofFile[ifile]->GetFileName(), fProofFile[ifile]->GetOptionsAnchor());
      fProofFile[ifile]->Print();
      fOutput->Add(fProofFile[ifile]);    
    }
  }  

  if(PUweighter)
    delete PUweighter;
  if(PUweighterUp)
    delete PUweighterUp;
  if(PUweighterDown)
    delete PUweighterDown;
    
  if(jecvar)
    delete jecvar;
  
  if(event)
    delete event;
  if(selector)
    delete selector;
  if(evtPick)
    delete evtPick;
  
  if(muSFa)
    delete muSFa ;
  if(muSFb)
    delete muSFb ;
  if(eleSF)
    delete eleSF ;
  
  if(f_trackSF_BCDEF)
    delete f_trackSF_BCDEF;
  if(f_trackSF_GH)
    delete f_trackSF_GH;
  
  if(fSystList)
    delete fSystList;

  totEvents.clear();
  totEventsUS.clear();
  fnameList.clear();

  crossSections.clear();
  numberOfEvents.clear();
  LumiWZ.clear();
}

//_____________________________________________________________________________
void SkimAna::Terminate()
{
// function called at the end of the event loop

   if (!fInput) Info("Terminate", "processed %lld events", fProcessed);
   
   TString option = GetOption();
   Info("Terminate", "stopping SkimAna with process option: %s", option.Data());
   
}

bool SkimAna::ExecSerial(const char* infile)
{
  
  TString option = GetOption();
  Info("ExecSerial", "starting SkimAna with process option: %s", option.Data());
  Info("ExecSerial", "opening file %s", infile);
  
  TFile *fin = TFile::Open(infile);
  TTree *tree = (TTree *)fin->Get("Events");
  SlaveBegin(tree);
  tree->GetEntry(0);
  Notify();
  for(Long64_t ientry = 0 ; ientry < tree->GetEntries() ; ientry++){
  //for(Long64_t ientry = 0 ; ientry < 20000 ; ientry++){
  //for(Long64_t ientry = 0 ; ientry < 800000 ; ientry++){
  //for(Long64_t ientry = 0 ; ientry < 10 ; ientry++){
  //cout<<"Procesing : " << ientry << endl;
    Process(ientry);
  }
  SlaveTerminate();
  
  fin->Close();
  delete fin;

  return true;
}

int main(int argc, char** argv)
{
  // year=$1
  // sample=$2
  // input=$3
  // index=$4
  // syst=$5
  
  TString op(Form("sample=%s|year=%s|input=%s|index=%s|syst=%s|aod=nano|run=prod|trs=no",argv[1],argv[2],argv[3],argv[4],argv[5]));

  cout << "Input filename: " << argv[3] << endl;
  ifstream fin(argv[3]);
  int index = atoi(argv[4]);

  string s;
  int idx = 0;
  TString inputfile = ""; 
  while(getline(fin,s)){
    //cout << s << endl;
    if(idx==index){
      inputfile = s.c_str();
    }
    idx++;
  }
  cout <<" Total files "<<idx<<endl; 
  op += Form("|total=%d",idx);
  
  SkimAna *skim = new SkimAna();
  skim->SetOption(op.Data());
  skim->ExecSerial(inputfile.Data());
  delete skim;
  
  return 1;
}
