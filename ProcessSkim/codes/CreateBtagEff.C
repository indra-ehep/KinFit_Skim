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
  
  int year = 2016;
  //int nofSamples = 27;
  int nofSamples = 3;
  const char *Sample[] = {"TTbar", "singleTop", "Wjets"}; 
  //const char *Sample[] = {"HplusM080", "HplusM090", "HplusM100", "HplusM140", "HplusM150", "HplusM155", "HplusM160"};  //2016

  // const char *Sample[] = {"TTbar", "singleTop", "Wjets", "DYjets", "VBFusion", "MCQCDMu", "MCQCDEle", 
  // 			  "HplusM080", "HplusM090", "HplusM100", "HplusM110", "HplusM120", "HplusM130", "HplusM140", "HplusM150", "HplusM155", "HplusM160",
  // 			  "HminusM080", "HminusM090", "HminusM100", "HminusM110", "HminusM120", "HminusM130", "HminusM140", "HminusM150", "HminusM155", "HminusM160"};  //2016

  //const char *Sample[] = {"HplusM120", "TTbar", "singleTop", "Wjets", "DYjets", "VBFusion", "MCQCDMu", "MCQCDEle", "TTB", "Others"};  //2016
  //const char *Sample[] = {"TTbar", "singleTop", "Wjets", "DYjets", "VBFusion", "MCQCDMu", "MCQCDEle", "TTB", "Others"};  //2017 and 2018
  
  const char *MLname = "deepcsv";
  const char* inputpath = Form("/Data/CMS-Analysis/NanoAOD-Analysis/ProcessSkim/root_files/NanoAODUL/btag_%s_raw",MLname);
  const char* outputpath = Form("/Data/CMS-Analysis/NanoAOD-Analysis/ProcessSkim/root_files/NanoAODUL/btag_%s",MLname);

  for(int ifile = 0 ; ifile < nofSamples ; ifile++ ){
  
    
    TFile *f = TFile::Open(Form("%s/%d/%s_btag_eff_raw_%d.root",inputpath,year,Sample[ifile],year));    
    TFile *fout = new TFile(Form("%s/%d/%s_btag_eff_%s_%d.root",outputpath,year,Sample[ifile],MLname,year),"recreate");    
    
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

    TH2D *h2_CTagEff_Num_bL               = (TH2D*)(f->Get(histPath+"h2_CTagEff_Num_bL"));
    TH2D *h2_CTagEff_Num_cL               = (TH2D*)(f->Get(histPath+"h2_CTagEff_Num_cL"));
    TH2D *h2_CTagEff_Num_udsgL            = (TH2D*)(f->Get(histPath+"h2_CTagEff_Num_udsgL"));
    
    h2_CTagEff_Num_bL->Sumw2();
    h2_CTagEff_Num_cL->Sumw2();
    h2_CTagEff_Num_udsgL->Sumw2();
    h2_CTagEff_Denom_b->Sumw2();
    h2_CTagEff_Denom_c->Sumw2();
    h2_CTagEff_Denom_udsg->Sumw2();
    
    TH2D *h2_CTagEff_Ratio_bL = (TH2D*)h2_CTagEff_Num_bL->Clone("CTag_b_L_efficiency");
    TH2D *h2_CTagEff_Ratio_cL = (TH2D*)h2_CTagEff_Num_cL->Clone("CTag_c_L_efficiency");
    TH2D *h2_CTagEff_Ratio_udsgL = (TH2D*)h2_CTagEff_Num_udsgL->Clone("CTag_l_L_efficiency");
    h2_CTagEff_Ratio_bL->Divide(h2_CTagEff_Denom_b);
    h2_CTagEff_Ratio_cL->Divide(h2_CTagEff_Denom_c);
    h2_CTagEff_Ratio_udsgL->Divide(h2_CTagEff_Denom_udsg);

    fout->cd();
    h2_BTagEff_Ratio_bM->Write();
    h2_BTagEff_Ratio_cM->Write();
    h2_BTagEff_Ratio_udsgM->Write();
    h2_CTagEff_Ratio_bL->Write();
    h2_CTagEff_Ratio_cL->Write();
    h2_CTagEff_Ratio_udsgL->Write();

    fout->Close();
    delete fout;
    
  }
  
  return true;
}
