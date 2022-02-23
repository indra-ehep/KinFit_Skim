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

int CreateBtagEff()
{
  
  int year = 2017;
  // int nofSamples = 3;
  // const char *Sample[] = {"TTbar", "singleTop", "Wjets"}; 
  //const char *Sample[] = {"HplusM080", "HplusM090", "HplusM100", "HplusM140", "HplusM150", "HplusM155", "HplusM160"};  //2016
  int nofSamples = 28;
  const char *Sample[] = {"TTbar", "singleTop", "Wjets", "DYjets", "VBFusion", "MCQCDMu", "MCQCDEle", 
  			  "HplusM080", "HplusM090", "HplusM100", "HplusM110", "HplusM120", "HplusM130", "HplusM140", "HplusM150", "HplusM155", "HplusM160",
  			  "HminusM080", "HminusM090", "HminusM100", "HminusM110", "HminusM120", "HminusM130", "HminusM140", "HminusM150", "HminusM155", "HminusM160", "AllMC"};  //2016
  
  //const char *Sample[] = {"HplusM120", "TTbar", "singleTop", "Wjets", "DYjets", "VBFusion", "MCQCDMu", "MCQCDEle", "TTB", "Others"};  //2016
  //const char *Sample[] = {"TTbar", "singleTop", "Wjets", "DYjets", "VBFusion", "MCQCDMu", "MCQCDEle", "TTB", "Others"};  //2017 and 2018
  
  string MLname = "deepjet";
  string inputpath = Form("/Data/CMS-Analysis/NanoAOD-Analysis/ProcessSkim/root_files/NanoAODUL/btag_%s_raw_hadronflavour",MLname.c_str());
  string outputpath = Form("/Data/CMS-Analysis/NanoAOD-Analysis/ProcessSkim/root_files/NanoAODUL/btag_%s_hadronflavour",MLname.c_str());

  for(int ifile = 0 ; ifile < nofSamples ; ifile++ ){
  
    
    TFile *f = TFile::Open(Form("%s/%d/%s_btag_eff_raw_%d.root",inputpath.c_str(),year,Sample[ifile],year));    
    TFile *fout = new TFile(Form("%s/%d/%s_btag_eff_%s_%d.root",outputpath.c_str(),year,Sample[ifile],MLname.c_str(),year),"recreate");    
    
    if(!f) continue;

    TString histPath("");

    TH2D *h2_BTagEff_Denom_b              = (TH2D*)(f->Get(histPath+"h2_BTagEff_Denom_b"));
    TH2D *h2_BTagEff_Denom_c              = (TH2D*)(f->Get(histPath+"h2_BTagEff_Denom_c"));
    TH2D *h2_BTagEff_Denom_udsg           = (TH2D*)(f->Get(histPath+"h2_BTagEff_Denom_udsg"));

    TH2D *h2_BTagEff_Num_bM               = (TH2D*)(f->Get(histPath+"h2_BTagEff_Num_bM"));
    TH2D *h2_BTagEff_Num_cM               = (TH2D*)(f->Get(histPath+"h2_BTagEff_Num_cM"));
    TH2D *h2_BTagEff_Num_udsgM            = (TH2D*)(f->Get(histPath+"h2_BTagEff_Num_udsgM"));
    
    h2_BTagEff_Num_bM->Sumw2();
    h2_BTagEff_Num_cM->Sumw2();
    h2_BTagEff_Num_udsgM->Sumw2();
    h2_BTagEff_Denom_b->Sumw2();
    h2_BTagEff_Denom_c->Sumw2();
    h2_BTagEff_Denom_udsg->Sumw2();
    
    TH2D *h2_BTagEff_Ratio_bM = (TH2D*)h2_BTagEff_Num_bM->Clone("BTag_b_M_efficiency");
    TH2D *h2_BTagEff_Ratio_cM = (TH2D*)h2_BTagEff_Num_cM->Clone("BTag_c_M_efficiency");
    TH2D *h2_BTagEff_Ratio_udsgM = (TH2D*)h2_BTagEff_Num_udsgM->Clone("BTag_l_M_efficiency");
    h2_BTagEff_Ratio_bM->Divide(h2_BTagEff_Denom_b);
    h2_BTagEff_Ratio_cM->Divide(h2_BTagEff_Denom_c);
    h2_BTagEff_Ratio_udsgM->Divide(h2_BTagEff_Denom_udsg);

    TH2D *h2_CTagEff_Denom_b              = (TH2D*)(f->Get(histPath+"h2_CTagEff_Denom_b"));
    TH2D *h2_CTagEff_Denom_c              = (TH2D*)(f->Get(histPath+"h2_CTagEff_Denom_c"));
    TH2D *h2_CTagEff_Denom_udsg           = (TH2D*)(f->Get(histPath+"h2_CTagEff_Denom_udsg"));
    h2_CTagEff_Denom_b->Sumw2();
    h2_CTagEff_Denom_c->Sumw2();
    h2_CTagEff_Denom_udsg->Sumw2();

    TH2D *h2_CTagEff_Num_bL               = (TH2D*)(f->Get(histPath+"h2_CTagEff_Num_bL"));
    TH2D *h2_CTagEff_Num_cL               = (TH2D*)(f->Get(histPath+"h2_CTagEff_Num_cL"));
    TH2D *h2_CTagEff_Num_udsgL            = (TH2D*)(f->Get(histPath+"h2_CTagEff_Num_udsgL"));    
    h2_CTagEff_Num_bL->Sumw2();
    h2_CTagEff_Num_cL->Sumw2();
    h2_CTagEff_Num_udsgL->Sumw2();
    TH2D *h2_CTagEff_Ratio_bL = (TH2D*)h2_CTagEff_Num_bL->Clone("CTag_b_L_efficiency");
    TH2D *h2_CTagEff_Ratio_cL = (TH2D*)h2_CTagEff_Num_cL->Clone("CTag_c_L_efficiency");
    TH2D *h2_CTagEff_Ratio_udsgL = (TH2D*)h2_CTagEff_Num_udsgL->Clone("CTag_l_L_efficiency");
    h2_CTagEff_Ratio_bL->Divide(h2_CTagEff_Denom_b);
    h2_CTagEff_Ratio_cL->Divide(h2_CTagEff_Denom_c);
    h2_CTagEff_Ratio_udsgL->Divide(h2_CTagEff_Denom_udsg);

    TH2D *h2_CTagEff_Num_bM               = (TH2D*)(f->Get(histPath+"h2_CTagEff_Num_bM"));
    TH2D *h2_CTagEff_Num_cM               = (TH2D*)(f->Get(histPath+"h2_CTagEff_Num_cM"));
    TH2D *h2_CTagEff_Num_udsgM            = (TH2D*)(f->Get(histPath+"h2_CTagEff_Num_udsgM"));    
    h2_CTagEff_Num_bM->Sumw2();
    h2_CTagEff_Num_cM->Sumw2();
    h2_CTagEff_Num_udsgM->Sumw2();
    TH2D *h2_CTagEff_Ratio_bM = (TH2D*)h2_CTagEff_Num_bM->Clone("CTag_b_M_efficiency");
    TH2D *h2_CTagEff_Ratio_cM = (TH2D*)h2_CTagEff_Num_cM->Clone("CTag_c_M_efficiency");
    TH2D *h2_CTagEff_Ratio_udsgM = (TH2D*)h2_CTagEff_Num_udsgM->Clone("CTag_l_M_efficiency");
    h2_CTagEff_Ratio_bM->Divide(h2_CTagEff_Denom_b);
    h2_CTagEff_Ratio_cM->Divide(h2_CTagEff_Denom_c);
    h2_CTagEff_Ratio_udsgM->Divide(h2_CTagEff_Denom_udsg);

    TH2D *h2_CTagEff_Num_bT               = (TH2D*)(f->Get(histPath+"h2_CTagEff_Num_bT"));
    TH2D *h2_CTagEff_Num_cT               = (TH2D*)(f->Get(histPath+"h2_CTagEff_Num_cT"));
    TH2D *h2_CTagEff_Num_udsgT            = (TH2D*)(f->Get(histPath+"h2_CTagEff_Num_udsgT"));    
    h2_CTagEff_Num_bT->Sumw2();
    h2_CTagEff_Num_cT->Sumw2();
    h2_CTagEff_Num_udsgT->Sumw2();
    TH2D *h2_CTagEff_Ratio_bT = (TH2D*)h2_CTagEff_Num_bT->Clone("CTag_b_T_efficiency");
    TH2D *h2_CTagEff_Ratio_cT = (TH2D*)h2_CTagEff_Num_cT->Clone("CTag_c_T_efficiency");
    TH2D *h2_CTagEff_Ratio_udsgT = (TH2D*)h2_CTagEff_Num_udsgT->Clone("CTag_l_T_efficiency");
    h2_CTagEff_Ratio_bT->Divide(h2_CTagEff_Denom_b);
    h2_CTagEff_Ratio_cT->Divide(h2_CTagEff_Denom_c);
    h2_CTagEff_Ratio_udsgT->Divide(h2_CTagEff_Denom_udsg);
    
    fout->cd();
    h2_BTagEff_Ratio_bM->Write();
    h2_BTagEff_Ratio_cM->Write();
    h2_BTagEff_Ratio_udsgM->Write();
    h2_CTagEff_Ratio_bL->Write();
    h2_CTagEff_Ratio_cL->Write();
    h2_CTagEff_Ratio_udsgL->Write();
    h2_CTagEff_Ratio_bM->Write();
    h2_CTagEff_Ratio_cM->Write();
    h2_CTagEff_Ratio_udsgM->Write();
    h2_CTagEff_Ratio_bT->Write();
    h2_CTagEff_Ratio_cT->Write();
    h2_CTagEff_Ratio_udsgT->Write();
    
    fout->Close();
    delete fout;
    
  }
  
  return true;
}
