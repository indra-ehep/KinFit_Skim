/**********************************************************************
 Created on : 14/07/2021
 Purpose    : Prepare the btag efficiency histogram.
 Author     : Indranil Das, Visiting Fellow
 Email      : indranil.das@cern.ch | indra.ehep@gmail.com
**********************************************************************/
#if !defined(__CINT__) || defined(__MAKECINT__)

#include <TROOT.h>
#include <TChain.h>
#include <TEntryList.h>
#include <TFile.h>
#include <TProofOutputFile.h>
#include <TSelector.h>
#include <vector>

#include "TH2.h"
#include "TF1.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TPaveStats.h"
#include "TMath.h"
#include "TProof.h"

#include "TParticlePDG.h"
#include "TDatabasePDG.h"

#include "TLorentzVector.h"
#include "TVector3.h"

#include <fstream>

using namespace std;

#endif

int CreatePUJetIDEff()
{
  
  int year = 2016;
  // int nofSamples = 3;
  // const char *Sample[] = {"TTbar", "singleTop", "Wjets"}; 
  // int nofSamples = 28;
  // const char *Sample[] = {"TTbar", "singleTop", "Wjets", "DYjets", "VBFusion", "MCQCDMu", "MCQCDEle", 
  // 			  "HplusM080", "HplusM090", "HplusM100", "HplusM110", "HplusM120", "HplusM130", "HplusM140", "HplusM150", "HplusM155", "HplusM160",
  // 			  "HminusM080", "HminusM090", "HminusM100", "HminusM110", "HminusM120", "HminusM130", "HminusM140", "HminusM150", "HminusM155", "HminusM160", "AllMC"};  //2016
  int nofSamples = 27;
  const char *Sample[] = {"TTbar", "singleTop", "Wjets", "DYjets", "VBFusion", "MCQCDMu", "MCQCDEle", 
  			  "HplusM080", "HplusM090", "HplusM100", "HplusM110", "HplusM120", "HplusM130", "HplusM140", "HplusM150", "HplusM155", "HplusM160",
  			  "HminusM080", "HminusM090", "HminusM100", "HminusM110", "HminusM120", "HminusM130", "HminusM140", "HminusM150", "HminusM155", "HminusM160"};  
  
  string inputpath = Form("/Data/CMS-Analysis/NanoAOD-Analysis/PUJetIDEff/root_files/iter1/raw");
  string outputpath = Form("/Data/CMS-Analysis/NanoAOD-Analysis/PUJetIDEff/root_files/iter1/eff");
  
  for(int ifile = 0 ; ifile < nofSamples ; ifile++ ){
  
    
    TFile *f = TFile::Open(Form("%s/%d/%s_pujetid_eff_raw_%d.root",inputpath.c_str(),year,Sample[ifile],year));    
    TFile *fout = new TFile(Form("%s/%d/%s_pujetid_eff_%d.root",outputpath.c_str(),year,Sample[ifile],year),"recreate");    
    
    // TFile *f = TFile::Open(Form("%s/%d_post/%s_pujetid_eff_raw_%d.root",inputpath.c_str(),year,Sample[ifile],year));    
    // TFile *fout = new TFile(Form("%s/%d_post/%s_pujetid_eff_%d.root",outputpath.c_str(),year,Sample[ifile],year),"recreate");    
    
    if(!f) continue;

    TString histPath("");

    TH2D *h2_PUJetIDEff_Denom   = (TH2D*)(f->Get(histPath+"h2_PUJetIDEff_Denom"));

    TH2D *h2_PUJetIDEff_Num_L   = (TH2D*)(f->Get(histPath+"h2_PUJetIDEff_Num_L"));
    TH2D *h2_PUJetIDEff_Num_M   = (TH2D*)(f->Get(histPath+"h2_PUJetIDEff_Num_M"));
    TH2D *h2_PUJetIDEff_Num_T   = (TH2D*)(f->Get(histPath+"h2_PUJetIDEff_Num_T"));
    
    h2_PUJetIDEff_Denom->Sumw2();
    h2_PUJetIDEff_Num_L->Sumw2();
    h2_PUJetIDEff_Num_M->Sumw2();
    h2_PUJetIDEff_Num_T->Sumw2();
    
    TH2D *h2_PUJetIDEff_Ratio_L = (TH2D*)h2_PUJetIDEff_Num_L->Clone("PUJetID_L_efficiency");
    TH2D *h2_PUJetIDEff_Ratio_M = (TH2D*)h2_PUJetIDEff_Num_M->Clone("PUJetID_M_efficiency");
    TH2D *h2_PUJetIDEff_Ratio_T = (TH2D*)h2_PUJetIDEff_Num_T->Clone("PUJetID_T_efficiency");

    h2_PUJetIDEff_Ratio_L->Divide(h2_PUJetIDEff_Denom);
    h2_PUJetIDEff_Ratio_M->Divide(h2_PUJetIDEff_Denom);
    h2_PUJetIDEff_Ratio_T->Divide(h2_PUJetIDEff_Denom);

    
    fout->cd();
    h2_PUJetIDEff_Ratio_L->Write();
    h2_PUJetIDEff_Ratio_M->Write();
    h2_PUJetIDEff_Ratio_T->Write();
    
    fout->Close();
    delete fout;
    
  }
  
  return true;
}
