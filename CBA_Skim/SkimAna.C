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
  
  TDirectory *savedir = gDirectory;
  savedir->cd();
  fFile[0]->cd();
  
  ////////////////////////////// Cut flow histograms //////////////////////////////////
  fNBCFHists = 6;
  fNCFHists = 4*fNBCFHists; // if fNBCFHists = 100, then == 0:99 for Iso HighMET | 100:199 for Iso LowMET | 200:299 nonIso HighMET | 300:399 nonIso LowMET
  
  hCutFlow = new TH1D*[fNCFHists];
  
  hCutFlow[0] = new TH1D("_cutflow_data", "_cutflow_data", 10, 0, 10);
  hCutFlow[1] = new TH1D("_cutflowUS_mu", "_cutflowUS_mu", 10, 0, 10);
  hCutFlow[2] = new TH1D("_cutflow_mu", "_cutflow_mu", 10, 0, 10);
  hCutFlow[3] = new TH1D("_cutflowUS_ele", "_cutflowUS_ele", 10, 0, 10);
  hCutFlow[4] = new TH1D("_cutflow_ele", "_cutflow_ele", 10, 0, 10);
  hCutFlow[5] = new TH1D("_cutflow5", "_cutflow5", 10, 0, 10);
  
  int minHs = fNBCFHists ;
  for(int isyst=minHs;isyst<(minHs+fNBCFHists);isyst++){
    hCutFlow[isyst] = (TH1D *)hCutFlow[isyst-minHs]->Clone(Form("%s_lmet",hCutFlow[isyst-minHs]->GetName()));
    hCutFlow[isyst]->SetTitle(Form("%s_lmet",hCutFlow[isyst-minHs]->GetTitle()));
  }
  
  minHs = 2*fNBCFHists ;
  for(int isyst=minHs;isyst<(minHs+fNBCFHists);isyst++){
    hCutFlow[isyst] = (TH1D *)hCutFlow[isyst-minHs]->Clone(Form("%s_noniso",hCutFlow[isyst-minHs]->GetName()));
    hCutFlow[isyst]->SetTitle(Form("%s_noniso",hCutFlow[isyst-minHs]->GetTitle()));
  }
  
  minHs = 3*fNBCFHists ;
  for(int isyst=minHs;isyst<(minHs+fNBCFHists);isyst++){
    hCutFlow[isyst] = (TH1D *)hCutFlow[isyst-minHs]->Clone(Form("%s_noniso_lmet",hCutFlow[isyst-minHs]->GetName()));
    hCutFlow[isyst]->SetTitle(Form("%s_noniso_lmet",hCutFlow[isyst-minHs]->GetTitle()));
  }
  /////////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////// Weight and other histograms histograms //////////////////////////////////
  fNBWtHists = 29;
  fNWtHists = 4*fNBWtHists; // if fNBaseHists = 100, then == 0:99 for Iso HighMET | 100:199 for Iso LowMET | 200:299 nonIso HighMET | 300:399 nonIso LowMET

  histWt = new TH1D*[fNWtHists];
  
  histWt[0] = new TH1D("_sampleWeight","_sampleWeight",2000, -10, 10);
  histWt[1] = new TH1D("_PUWeight","_PUWeight", 2000, -10, 10);
  histWt[2] = new TH1D("_prefireWeight","_prefireWeight",2000, -10, 10);
  histWt[3] = new TH1D("_muEffWeight","_muEffWeight",2000, -10, 10);
  histWt[4] = new TH1D("_eleEffWeight","_eleEffWeight",2000, -10, 10);
  histWt[5] = new TH1D("_btagWeight_1a","_btagWeight_1a",2000, -10, 10);
  histWt[6] = new TH1D("_btagWeight_1a_b_Do","_btagWeight_1a_b_Do",2000, -10, 10);
  histWt[7] = new TH1D("_btagWeight_1a_b_Up","_btagWeight_1a_b_Up",2000, -10, 10);
  histWt[8] = new TH1D("_btagWeight_1a_l_Do","_btagWeight_1a_l_Do",2000, -10, 10);
  histWt[9] = new TH1D("_btagWeight_1a_l_Up","_btagWeight_1a_l_Up",2000, -10, 10);
  histWt[10] = new TH1D("_muEffWeight_Up","_muEffWeight_Up",2000, -10, 10);
  histWt[11] = new TH1D("_muEffWeight_Do","_muEffWeight_Do",2000, -10, 10);
  histWt[12] = new TH1D("_eleEffWeight_Up","_eleEffWeight_Up",2000, -10, 10);
  histWt[13] = new TH1D("_eleEffWeight_Do","_eleEffWeight_Do",2000, -10, 10);
  histWt[14] = new TH1D("_pdfweight_Up","_pdfweight_Up",2000, -10, 10);
  histWt[15] = new TH1D("_pdfweight_Do","_pdfweight_Do",2000, -10, 10);
  histWt[16] = new TH1D("_q2weight_Up","_q2weight_Up",2000, -10, 10);
  histWt[17] = new TH1D("_q2weight_Do","_q2weight_Do",2000, -10, 10);
  histWt[18] = new TH1D("_FSRweight_Up","_FSRweight_Up",2000, -10, 10);
  histWt[19] = new TH1D("_FSRweight_Do","_FSRweight_Do",2000, -10, 10);
  histWt[20] = new TH1D("_ISRweight_Up","_ISRweight_Up",2000, -10, 10);
  histWt[21] = new TH1D("_ISRweight_Do","_ISRweight_Do",2000, -10, 10);
  histWt[22] = new TH1D("_PUweight_Up","_PUweight_Up",2000, -10, 10);
  histWt[23] = new TH1D("_PUweight_Do","_PUweight_Do",2000, -10, 10);
  histWt[24] = new TH1D("_topPtReweight","_topPtReweight",2000, -10, 10);
  histWt[25] = new TH1D("_muIso","_muIso", 100, 0., 1.);
  histWt[26] = new TH1D("_eleIso","_eleIso", 100, 0., 1.);
  histWt[27] = new TH1D("_muMET","_muMET", 100, 0., 500.);
  histWt[28] = new TH1D("_eleMET","_eleMET", 100, 0., 500.);
  
  minHs = fNBWtHists ;
  for(int isyst=minHs;isyst<(minHs+fNBWtHists);isyst++){
    histWt[isyst] = (TH1D *)histWt[isyst-minHs]->Clone(Form("%s_lmet",histWt[isyst-minHs]->GetName()));
    histWt[isyst]->SetTitle(Form("%s_lmet",histWt[isyst-minHs]->GetTitle()));
  }
  
  minHs = 2*fNBWtHists ;
  for(int isyst=minHs;isyst<(minHs+fNBWtHists);isyst++){
    histWt[isyst] = (TH1D *)histWt[isyst-minHs]->Clone(Form("%s_noniso",histWt[isyst-minHs]->GetName()));
    histWt[isyst]->SetTitle(Form("%s_noniso",histWt[isyst-minHs]->GetTitle()));
  }
  
  minHs = 3*fNBWtHists ;
  for(int isyst=minHs;isyst<(minHs+fNBWtHists);isyst++){
    histWt[isyst] = (TH1D *)histWt[isyst-minHs]->Clone(Form("%s_noniso_lmet",histWt[isyst-minHs]->GetName()));
    histWt[isyst]->SetTitle(Form("%s_noniso_lmet",histWt[isyst-minHs]->GetTitle()));
  }
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  fNBObHists = 44;
  fNObHists = 12*fNBObHists; // if fNBaseHists = 100, then == 0:99 for Iso HighMET | 100:199 for Iso LowMET | 200:299 nonIso HighMET | 300:399 nonIso LowMET

  histObs = new TH1D*[fNObHists];

  histObs[0] = new TH1D("_lb_pt_mu","_lb_pt_mu",100, 0., 1000.);
  histObs[1] = new TH1D("_lb_eta_mu","_lb_eta_mu", 30, -3., 3.);
  histObs[2] = new TH1D("_lb_phi_mu","_lb_phi_mu", 35, -3.5, 3.5);
  histObs[3] = new TH1D("_lb_pt_ele","_lb_pt_ele",100, 0., 1000.);
  histObs[4] = new TH1D("_lb_eta_ele","_lb_eta_ele", 30, -3., 3.);
  histObs[5] = new TH1D("_lb_phi_ele","_lb_phi_ele", 35, -3.5, 3.5);
  histObs[6] = new TH1D("_lb_pt_mu_jets","_lb_pt_mu_jets",100, 0., 1000.);
  histObs[7] = new TH1D("_lb_eta_mu_jets","_lb_eta_mu_jets", 30, -3., 3.);
  histObs[8] = new TH1D("_lb_phi_mu_jets","_lb_phi_mu_jets", 35, -3.5, 3.5);
  histObs[9] = new TH1D("_lb_pt_ele_jets","_lb_pt_ele_jets",100, 0., 1000.);
  histObs[10] = new TH1D("_lb_eta_ele_jets","_lb_eta_ele_jets", 30, -3., 3.);
  histObs[11] = new TH1D("_lb_phi_ele_jets","_lb_phi_ele_jets", 35, -3.5, 3.5);
  histObs[12] = new TH1D("_lb_pt_mu_met","_lb_pt_mu_met",100, 0., 1000.);
  histObs[13] = new TH1D("_lb_phi_mu_met","_lb_phi_mu_met", 35, -3.5, 3.5);
  histObs[14] = new TH1D("_lb_pt_ele_met","_lb_pt_ele_met",100, 0., 1000.);
  histObs[15] = new TH1D("_lb_phi_ele_met","_lb_phi_ele_met", 35, -3.5, 3.5);
  histObs[16] = new TH1D("_lb_njet_mu","_lb_njet_mu", 20, 0., 20);
  histObs[17] = new TH1D("_lb_nbjet_mu","_lb_nbjet_mu", 20, 0., 20);
  histObs[18] = new TH1D("_lb_njet_ele","_lb_njet_ele", 20, 0., 20);
  histObs[19] = new TH1D("_lb_nbjet_ele","_lb_nbjet_ele", 20, 0., 20);

  histObs[20] = new TH1D("_kb_pt_mu","_kb_pt_mu",100, 0., 1000.);
  histObs[21] = new TH1D("_kb_eta_mu","_kb_eta_mu", 30, -3., 3.);
  histObs[22] = new TH1D("_kb_phi_mu","_kb_phi_mu", 35, -3.5, 3.5);
  histObs[23] = new TH1D("_kb_pt_ele","_kb_pt_ele",100, 0., 1000.);
  histObs[24] = new TH1D("_kb_eta_ele","_kb_eta_ele", 30, -3., 3.);
  histObs[25] = new TH1D("_kb_phi_ele","_kb_phi_ele", 35, -3.5, 3.5);
  histObs[26] = new TH1D("_kb_pt_mu_jets","_kb_pt_mu_jets",100, 0., 1000.);
  histObs[27] = new TH1D("_kb_eta_mu_jets","_kb_eta_mu_jets", 30, -3., 3.);
  histObs[28] = new TH1D("_kb_phi_mu_jets","_kb_phi_mu_jets", 35, -3.5, 3.5);
  histObs[29] = new TH1D("_kb_pt_ele_jets","_kb_pt_ele_jets",100, 0., 1000.);
  histObs[30] = new TH1D("_kb_eta_ele_jets","_kb_eta_ele_jets", 30, -3., 3.);
  histObs[31] = new TH1D("_kb_phi_ele_jets","_kb_phi_ele_jets", 35, -3.5, 3.5);
  histObs[32] = new TH1D("_kb_pt_mu_met","_kb_pt_mu_met",100, 0., 1000.);
  histObs[33] = new TH1D("_kb_phi_mu_met","_kb_phi_mu_met", 35, -3.5, 3.5);
  histObs[34] = new TH1D("_kb_pt_ele_met","_kb_pt_ele_met",100, 0., 1000.);
  histObs[35] = new TH1D("_kb_phi_ele_met","_kb_phi_ele_met", 35, -3.5, 3.5);
  histObs[36] = new TH1D("_kb_njet_mu","_kb_njet_mu", 20, 0., 20);
  histObs[37] = new TH1D("_kb_nbjet_mu","_kb_nbjet_mu", 20, 0., 20);
  histObs[38] = new TH1D("_kb_njet_ele","_kb_njet_ele", 20, 0., 20);
  histObs[39] = new TH1D("_kb_nbjet_ele","_kb_nbjet_ele", 20, 0., 20);
  histObs[40] = new TH1D("_kb_mjj_mu","_kb_mjj_mu", 50, 0., 250);
  histObs[41] = new TH1D("_kb_mjj_ele","_kb_mjj_ele", 50, 0., 250);
  histObs[42] = new TH1D("_kb_mjj_bf_mu","_kb_mjj_bf_mu", 50, 0., 250);
  histObs[43] = new TH1D("_kb_mjj_bf_ele","_kb_mjj_bf_ele", 50, 0., 250);

  
  // if fNBaseHists = 100, then == 0:99 for Iso HighMET | 100:199 for Iso LowMET | 200:299 nonIso HighMET | 300:399 nonIso LowMET
  
  minHs = fNBObHists ;
  for(int isyst=minHs;isyst<(minHs+fNBObHists);isyst++){
    histObs[isyst] = (TH1D *)histObs[isyst-minHs]->Clone(Form("%s_lmet",histObs[isyst-minHs]->GetName()));
    histObs[isyst]->SetTitle(Form("%s_lmet",histObs[isyst-minHs]->GetTitle()));
  }
  
  minHs = 2*fNBObHists ;
      for(int isyst=minHs;isyst<(minHs+fNBObHists);isyst++){
    histObs[isyst] = (TH1D *)histObs[isyst-minHs]->Clone(Form("%s_noniso",histObs[isyst-minHs]->GetName()));
    histObs[isyst]->SetTitle(Form("%s_noniso",histObs[isyst-minHs]->GetTitle()));
  }
  
  minHs = 3*fNBObHists ;
  for(int isyst=minHs;isyst<(minHs+fNBObHists);isyst++){
    histObs[isyst] = (TH1D *)histObs[isyst-minHs]->Clone(Form("%s_noniso_lmet",histObs[isyst-minHs]->GetName()));
    histObs[isyst]->SetTitle(Form("%s_noniso_lmet",histObs[isyst-minHs]->GetTitle()));
  }

  //"pdfup", "pdfdown", "q2up", "q2down", "fsrup", "fsrdown", "isrup", "isrdown"

  minHs = 4*fNBObHists ;
  for(int isyst=minHs;isyst<(minHs+fNBObHists);isyst++){
    histObs[isyst] = (TH1D *)histObs[isyst-minHs]->Clone(Form("%s_pdfup",histObs[isyst-minHs]->GetName()));
    histObs[isyst]->SetTitle(Form("%s_pdfup",histObs[isyst-minHs]->GetTitle()));
  }

  minHs = 5*fNBObHists ;
  for(int isyst=minHs;isyst<(minHs+fNBObHists);isyst++){
    histObs[isyst] = (TH1D *)histObs[isyst-minHs]->Clone(Form("%s_pdfdown",histObs[isyst-minHs]->GetName()));
    histObs[isyst]->SetTitle(Form("%s_pdfdown",histObs[isyst-minHs]->GetTitle()));
  }

  minHs = 6*fNBObHists ;
  for(int isyst=minHs;isyst<(minHs+fNBObHists);isyst++){
    histObs[isyst] = (TH1D *)histObs[isyst-minHs]->Clone(Form("%s_q2up",histObs[isyst-minHs]->GetName()));
    histObs[isyst]->SetTitle(Form("%s_q2up",histObs[isyst-minHs]->GetTitle()));
  }

  minHs = 7*fNBObHists ;
  for(int isyst=minHs;isyst<(minHs+fNBObHists);isyst++){
    histObs[isyst] = (TH1D *)histObs[isyst-minHs]->Clone(Form("%s_q2down",histObs[isyst-minHs]->GetName()));
    histObs[isyst]->SetTitle(Form("%s_q2down",histObs[isyst-minHs]->GetTitle()));
  }

  minHs = 8*fNBObHists ;
  for(int isyst=minHs;isyst<(minHs+fNBObHists);isyst++){
    histObs[isyst] = (TH1D *)histObs[isyst-minHs]->Clone(Form("%s_fsrup",histObs[isyst-minHs]->GetName()));
    histObs[isyst]->SetTitle(Form("%s_fsrup",histObs[isyst-minHs]->GetTitle()));
  }

  minHs = 9*fNBObHists ;
  for(int isyst=minHs;isyst<(minHs+fNBObHists);isyst++){
    histObs[isyst] = (TH1D *)histObs[isyst-minHs]->Clone(Form("%s_fsrdown",histObs[isyst-minHs]->GetName()));
    histObs[isyst]->SetTitle(Form("%s_fsrdown",histObs[isyst-minHs]->GetTitle()));
  }

  minHs = 10*fNBObHists ;
  for(int isyst=minHs;isyst<(minHs+fNBObHists);isyst++){
    histObs[isyst] = (TH1D *)histObs[isyst-minHs]->Clone(Form("%s_isrup",histObs[isyst-minHs]->GetName()));
    histObs[isyst]->SetTitle(Form("%s_isrup",histObs[isyst-minHs]->GetTitle()));
  }

  minHs = 11*fNBObHists ;
  for(int isyst=minHs;isyst<(minHs+fNBObHists);isyst++){
    histObs[isyst] = (TH1D *)histObs[isyst-minHs]->Clone(Form("%s_isrdown",histObs[isyst-minHs]->GetName()));
    histObs[isyst]->SetTitle(Form("%s_isrdown",histObs[isyst-minHs]->GetTitle()));
  }
  
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
      fBasePath = "/Data/CMS-Analysis/NanoAOD-Analysis";
    else if(hostname.BeginsWith("lxplus"))
      fBasePath = "/afs/cern.ch/user/i/idas/CMS-Analysis/NanoAOD-Analysis";
    else if(hostname.BeginsWith("ui"))
      fBasePath = "/home/idas/t3store3/NanoAOD-Analysis";
    else if(hostname.BeginsWith("lnx3"))
      fBasePath = "/home/indra/CMS-Analysis/NanoAOD-Analysis";
    fBasePath += "/SkimAna";
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
  jecvar012_g		= 1 ;		// 0:down, 1:norm, 2:up
  jervar012_g		= 1 ;		// 0:down, 1:norm, 2:up
  btagbvar012_g		= 1 ;		// 0:down, 1:norm, 2:up
  btaglvar012_g		= 1 ;		// 0:down, 1:norm, 2:up
  pdfvar012_g		= 1 ;		// 0:down, 1:norm, 2:up
  q2var012_g		= 1 ;		// 0:down, 1:norm, 2:up
  fsrvar012_g		= 1 ;		// 0:down, 1:norm, 2:up
  isrvar012_g		= 1 ;		// 0:down, 1:norm, 2:up
  prefirevar012_g	= 1 ;           // 0:down, 1:norm, 2:up
  btagSystType		= "central" ;
  
  if (fSyst == "base"){

    systType = kBase ;
    Info("SelectSyst","Syst : %s", fSyst.Data()); 

  } else if (fSyst == "puup") {
    
    systType = kPUUp;
    puvar012_g = 2;
    Info("SelectSyst","Syst : %s", fSyst.Data()); 

  } else if (fSyst == "pudown") {

    systType = kPUDown;
    puvar012_g = 0;
    Info("SelectSyst","Syst : %s", fSyst.Data()); 

  } else if (fSyst == "mueffup") {

    systType = kMuEffUp;
    mueffvar012_g = 2;
    Info("SelectSyst","Syst : %s", fSyst.Data()); 

  } else if (fSyst == "mueffdown") {

    systType = kMuEffDown;
    mueffvar012_g = 0;
    Info("SelectSyst","Syst : %s", fSyst.Data()); 

  } else if (fSyst == "eleeffup") {

    systType = kEleEffUp;
    eleeffvar012_g = 2;  
    Info("SelectSyst","Syst : %s", fSyst.Data()); 

  } else if (fSyst == "eleeffdown") {
    
    systType = kEleEffDown;
    eleeffvar012_g = 0;  
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

  } else if (fSyst == "btagbup") {

    systType = kBTagbUp;
    btagbvar012_g = 2;      
    btagSystType = "b_up";
    Info("SelectSyst","Syst : %s", fSyst.Data()); 

  } else if (fSyst == "btagbdown") {

    systType = kBTagbDown;
    btagbvar012_g  = 0;   
    btagSystType = "b_down";    
    Info("SelectSyst","Syst : %s", fSyst.Data()); 

  } else if (fSyst == "btaglup") {

    systType = kBTaglUp;
    btaglvar012_g = 2;    
    btagSystType = "l_up";  
    Info("SelectSyst","Syst : %s", fSyst.Data()); 
  
  } else if (fSyst == "btagldown") {

    systType = kBTaglDown;
    btaglvar012_g = 0;
    btagSystType = "l_down";      
    Info("SelectSyst","Syst : %s", fSyst.Data()); 

  } else if (fSyst == "pdfup") {

    systType = kPdfUp;
    pdfvar012_g = 2;      
    Info("SelectSyst","Syst : %s", fSyst.Data()); 
  
  } else if (fSyst == "pdfdown") {

    systType = kPdfDown;
    pdfvar012_g = 0;      
    Info("SelectSyst","Syst : %s", fSyst.Data()); 
  
  } else if (fSyst == "q2up") {

    systType = kQ2Up;
    q2var012_g = 2;      
    Info("SelectSyst","Syst : %s", fSyst.Data()); 
    
  } else if (fSyst == "q2down") {

    systType = kQ2Down;
    q2var012_g = 0;      
    Info("SelectSyst","Syst : %s", fSyst.Data()); 

  } else if (fSyst == "fsrup") {

    systType = kFsrUp;
    fsrvar012_g = 2;      
    Info("SelectSyst","Syst : %s", fSyst.Data()); 

  } else if (fSyst == "fsrdown") {

    systType = kFsrDown;
    fsrvar012_g = 0;      
    Info("SelectSyst","Syst : %s", fSyst.Data()); 

  } else if (fSyst == "isrup") {

    systType = kIsrUp;
    isrvar012_g = 2;      
    Info("SelectSyst","Syst : %s", fSyst.Data()); 

  } else if (fSyst == "isrdown") {

    systType = kIsrDown;
    isrvar012_g = 0;      
    Info("SelectSyst","Syst : %s", fSyst.Data()); 

  } else if (fSyst == "prefireup") {

    systType = kPreFireUp;
    prefirevar012_g = 2;      
    Info("SelectSyst","Syst : %s", fSyst.Data()); 

  } else if (fSyst == "prefiredown") {
    
    systType = kPreFireDown;
    prefirevar012_g = 0;      
    Info("SelectSyst","Syst : %s", fSyst.Data()); 

  }

  // if(systematicType=="elesmear_down") {elesmear012_g=0;selector->elesmearLevel=0; isSystematicRun = true;}
  // if(systematicType=="elesmear_up")   {elesmear012_g=2;selector->elesmearLevel=2; isSystematicRun = true;}
  // if(systematicType=="elescale_down") {elescale012_g=0;selector->elescaleLevel=0; isSystematicRun = true;}
  // if(systematicType=="elescale_up")   {elescale012_g=2;  selector->elescaleLevel=2; isSystematicRun = true;}
  // if( systematicType=="musmear_up") {musmear012_g = 2; isSystematicRun = true;}
  // if( systematicType=="musmear_do") {musmear012_g = 0; isSystematicRun = true;}

  
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
  selector->DDselect = false ;
  selector->mu_RelIso_loose = 0.4;

  // Cuts used for results presented at PAG dated August, 02, 2021
  // selector->mu_Pt_cut = 30.;
  // selector->mu_Eta_tight = 2.4;
  // selector->ele_Pt_cut = 35.;
  // selector->ele_Eta_cut = 2.4;
  // selector->jet_Pt_cut = 30.;
  // selector->jet_Eta_cut = 2.4;
  
  if(fYear==2016){
    
    // selector->mu_Pt_cut = 30.;
    // selector->mu_Eta_tight = 2.4;
    // selector->ele_Pt_cut = 35.;
    // selector->ele_Eta_cut = 2.4;
    // selector->jet_Pt_cut = 30.;
    // selector->jet_Eta_cut = 2.4;
    
    selector->mu_Pt_cut = 26.;
    selector->mu_Eta_tight = 2.4;
    selector->ele_Pt_cut = 30.;
    selector->ele_Eta_cut = 2.4;
    selector->jet_Pt_cut = 25.;
    selector->jet_Eta_cut = 2.4;
    
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
    // if (fYear==2016) selector->btag_cut_DeepCSV = 0.2219; 
    // if (fYear==2017) selector->btag_cut_DeepCSV = 0.1522;
    // if (fYear==2018) selector->btag_cut_DeepCSV = 0.1241;
    //Medium
    if (fYear==2016) selector->btag_cut_DeepCSV = 0.6324; //in twiki it is 0.6324 instead of 0.6321
    if (fYear==2017) selector->btag_cut_DeepCSV = 0.4941;
    if (fYear==2018) selector->btag_cut_DeepCSV = 0.4184;
    // //Tight
    // if (fYear==2016) selector->btag_cut_DeepCSV = 0.8958; 
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
  
  switch (systType) {
  case kPUUp:
    PUweighter = new PUReweight(nFiles, fileNames, PUfilename_up);
    break;
  case kPUDown:
    PUweighter = new PUReweight(nFiles, fileNames, PUfilename_down);
    break;
  default:
    PUweighter = new PUReweight(nFiles, fileNames, PUfilename);
    break;
  }  
  
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
      calib = BTagCalibration( "deepcsv", Form("%s/weight/BtagSF/new/DeepCSV_Moriond17_B_H.csv",fBasePath.Data()) ) ;
      Info("LoadBTag","%s/weight/BtagSF/new/DeepCSV_Moriond17_B_H.csv",fBasePath.Data());
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
    
    //fName = Form("%s/weight/BtagSF/Efficiency/NanoAOD/DeepCSV/btagL/%d/%s_btag_efficiency_%d.root",fBasePath.Data(),fYear,fSample.Data(),fYear);
    fName = Form("%s/weight/BtagSF/Efficiency/NanoAOD/DeepCSV/%d/%s_btag_efficiency_%d.root",fBasePath.Data(),fYear,fSample.Data(),fYear);    
    //fName = Form("%s/weight/BtagSF/Efficiency/NanoAOD/DeepCSV_hfl/%d/%s_btag_efficiency_%d.root",fBasePath.Data(),fYear,fSample.Data(),fYear);    
    //fName = Form("%s/weight/BtagSF/btag_efficiencies_%d.root",fBasePath.Data(),fYear);
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
      
      f_trackSF_BCDEF 	= new TFile(Form("%s/../Analysis/Analysis/stack/muonSF/trackingSF_BCDEF.root",fBasePath.Data()));
      f_trackSF_GH	= new TFile(Form("%s/../Analysis/Analysis/stack/muonSF/trackingSF_GH.root",fBasePath.Data()));
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
  // if(fMode.Contains("proof"))
  //   fChain->GetTree()->GetEntry(entry);  
  // else
  //   fChain->GetEntry(fProcessed);  
  
  fChain->GetTree()->GetEntry(entry);  
  //fChain->GetEntry(entry);
  
  //    fChain->GetEntry(fProcessed);  

  fProcessed++;
  fStatus++;
  
  // OldMethod();

  _sampleWeight	 = 1.0;
  _prefireWeight = 1.0;
  _PUWeight	 = 1.0;
  _muEffWeight	 = 1.0;
  _eleEffWeight	 = 1.0;
  _bTagWeight	 = 1.0;
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
  
  
  // Set JEC syst
  if( !isData and (systType == kJECUp or systType == kJECDown)){
    // printf("Processing event : %lld\n",entry);
    // for(int jetInd = 0; jetInd < event->nJet_ ; ++jetInd){
    //   printf("Before JEC : (pt,eta,phi) : (%5.2lf, %5.2lf, %5.2lf), (rawfactor,area,rho) : (%5.2lf, %5.2lf, %5.2lf)\n",
    // 	     entry,event->jetPt_[jetInd],event->jetEta_[jetInd],event->jetPhi_[jetInd],
    // 	     event->jetRawFactor_[jetInd],event->jetArea_[jetInd],event->rho_);
    // }
    jecvar->applyJEC(event, jecvar012_g); // 0:down, 1:norm, 2:up
    // for(int jetInd = 0; jetInd < event->nJet_ ; ++jetInd){
    //   printf("After JEC : (pt,eta,phi) : (%5.2lf, %5.2lf, %5.2lf), (rawfactor,area,rho) : (%5.2lf, %5.2lf, %5.2lf)\n",
    // 	     entry,event->jetPt_[jetInd],event->jetEta_[jetInd],event->jetPhi_[jetInd],
    // 	     event->jetRawFactor_[jetInd],event->jetArea_[jetInd],event->rho_);
    // }

  }
  
  // //Clear selector vectors
  selector->clear_vectors();
  
  // if(fProcessed%mod_num==0)
  //   Info("Process","Level 0");
  
  // This is main method to process the objects read from tree
  evtPick->process_event(fBasePath.Data(), event, selector, 1.0); // here last argument 1.0 is weight applied to cutflow

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
      Info("Notify", "DYjets : Updated special event weight : %lf for nLHEPart_ : %d", _local_evtWeight, event->nLHEPart_);
  }

  // if(fProcessed%mod_num==0)
  //   Info("Process","Level 1");
 

  // Sample weight 
  if(!isData)
    _sampleWeight = _local_evtWeight * ((event->genWeight_ >= 0) ? 1.0 : -1.0) ; //_sampleWeight should mimic the MiniAOD

  // Access the prefire weight
  if(!isData){
    switch (systType) {
    case kPreFireUp:
      _prefireWeight = event->L1PreFiringWeight_Up_ ;
      break;
    case kPreFireDown:
      _prefireWeight = event->L1PreFiringWeight_Dn_ ;
      break;
    default:
      _prefireWeight = event->L1PreFiringWeight_Nom_ ;
      break;
    }  
  }

  // Access the PU weight
  if(!isData){
    _PUWeight = PUweighter->getWeight(event->nPUTrue_);
  }
  
  // if(fProcessed%mod_num==0)
  //   Info("Process","Level 2");

  histWt[0]->Fill(_sampleWeight);
  histWt[1]->Fill(_PUWeight);
  if(systType == kPUUp)
    histWt[22]->Fill(_PUWeight);
  if(systType == kPUDown)
    histWt[23]->Fill(_PUWeight);
  histWt[2]->Fill(_prefireWeight);
  //Event level or trigger level conditions will be placed in block below
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //hCutFlow[1]->Fill(_PUWeight); //filled later;

  if(evtPick->passTrigger_mu || evtPick->passTrigger_ele){
    hCutFlow[0]->Fill(0.0);

    hCutFlow[0+fNBCFHists]->Fill(0.0);

    hCutFlow[0+2*fNBCFHists]->Fill(0.0);

    hCutFlow[0+3*fNBCFHists]->Fill(0.0);
  }
  
  if((evtPick->passTrigger_mu || evtPick->passTrigger_ele) && selector->isPVGood && evtPick->passFilter){
    hCutFlow[0]->Fill(1.0);

    hCutFlow[0+fNBCFHists]->Fill(1.0);

    hCutFlow[0+2*fNBCFHists]->Fill(1.0);

    hCutFlow[0+3*fNBCFHists]->Fill(1.0);
  }
  
  if(evtPick->passTrigger_mu){
    hCutFlow[1]->Fill(0.0);
    hCutFlow[2]->Fill(0.0, _sampleWeight*_prefireWeight*_PUWeight);
    hCutFlow[5]->Fill(0.0, _sampleWeight*_PUWeight);

    hCutFlow[1+fNBCFHists]->Fill(0.0);
    hCutFlow[2+fNBCFHists]->Fill(0.0, _sampleWeight*_prefireWeight*_PUWeight);
    hCutFlow[5+fNBCFHists]->Fill(0.0, _sampleWeight*_PUWeight);

    hCutFlow[1+2*fNBCFHists]->Fill(0.0);
    hCutFlow[2+2*fNBCFHists]->Fill(0.0, _sampleWeight*_prefireWeight*_PUWeight);
    hCutFlow[5+2*fNBCFHists]->Fill(0.0, _sampleWeight*_PUWeight);

    hCutFlow[1+3*fNBCFHists]->Fill(0.0);
    hCutFlow[2+3*fNBCFHists]->Fill(0.0, _sampleWeight*_prefireWeight*_PUWeight);
    hCutFlow[5+3*fNBCFHists]->Fill(0.0, _sampleWeight*_PUWeight);
  }
  
  if(evtPick->passTrigger_mu and selector->isPVGood and evtPick->passFilter){
    hCutFlow[1]->Fill(1.0);
    hCutFlow[2]->Fill(1.0, _sampleWeight*_prefireWeight*_PUWeight);
    hCutFlow[5]->Fill(1.0, _sampleWeight*_PUWeight);

    hCutFlow[1+fNBCFHists]->Fill(1.0);
    hCutFlow[2+fNBCFHists]->Fill(1.0, _sampleWeight*_prefireWeight*_PUWeight);
    hCutFlow[5+fNBCFHists]->Fill(1.0, _sampleWeight*_PUWeight);

    hCutFlow[1+2*fNBCFHists]->Fill(1.0);
    hCutFlow[2+2*fNBCFHists]->Fill(1.0, _sampleWeight*_prefireWeight*_PUWeight);
    hCutFlow[5+2*fNBCFHists]->Fill(1.0, _sampleWeight*_PUWeight);

    hCutFlow[1+3*fNBCFHists]->Fill(1.0);
    hCutFlow[2+3*fNBCFHists]->Fill(1.0, _sampleWeight*_prefireWeight*_PUWeight);
    hCutFlow[5+3*fNBCFHists]->Fill(1.0, _sampleWeight*_PUWeight);
  }
  
  //elec
  if(evtPick->passTrigger_ele){
    hCutFlow[3]->Fill(0.0);
    hCutFlow[4]->Fill(0.0, _sampleWeight*_prefireWeight*_PUWeight);

    hCutFlow[3+fNBCFHists]->Fill(0.0);
    hCutFlow[4+fNBCFHists]->Fill(0.0, _sampleWeight*_prefireWeight*_PUWeight);

    hCutFlow[3+2*fNBCFHists]->Fill(0.0);
    hCutFlow[4+2*fNBCFHists]->Fill(0.0, _sampleWeight*_prefireWeight*_PUWeight);

    hCutFlow[3+3*fNBCFHists]->Fill(0.0);
    hCutFlow[4+3*fNBCFHists]->Fill(0.0, _sampleWeight*_prefireWeight*_PUWeight);
  }

  if(evtPick->passTrigger_ele and selector->isPVGood and evtPick->passFilter){
    hCutFlow[3]->Fill(1.0);
    hCutFlow[4]->Fill(1.0, _sampleWeight*_prefireWeight*_PUWeight);
 
    hCutFlow[3+fNBCFHists]->Fill(1.0);
    hCutFlow[4+fNBCFHists]->Fill(1.0, _sampleWeight*_prefireWeight*_PUWeight);

    hCutFlow[3+2*fNBCFHists]->Fill(1.0);
    hCutFlow[4+2*fNBCFHists]->Fill(1.0, _sampleWeight*_prefireWeight*_PUWeight);
 
    hCutFlow[3+3*fNBCFHists]->Fill(1.0);
    hCutFlow[4+3*fNBCFHists]->Fill(1.0, _sampleWeight*_prefireWeight*_PUWeight);
   }
  
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  // if(fProcessed%mod_num==0)
  //   Info("Process","Level 3");
  //MuonsNoIso
  //ElectronsNoIso
  
  //bool singleMu = (evtPick->passFilter and selector->isPVGood and evtPick->passTrigger_mu and selector->ElectronsNoIso.size() == 0 and selector->ElectronsLoose.size() == 0 and selector->MuonsNoIso.size() == 1 and selector->MuonsLoose.size() == 0);
  //bool singleMu = (evtPick->passFilter and selector->isPVGood and evtPick->passTrigger_mu and selector->Electrons.size() == 0 and selector->ElectronsLoose.size() == 0 and selector->Muons.size() == 1 and selector->MuonsLoose.size() == 0);
  
  //The following setup is able to produce results presented in August-02 PAG
  // bool singleMu = (evtPick->passFilter and selector->isPVGood and evtPick->passTrigger_mu and selector->ElectronsNoIso.size() == 0 and selector->ElectronsLoose.size() == 0 and selector->MuonsNoIso.size() == 1 and selector->MuonsLoose.size() == 0);
  // bool singleEle = (evtPick->passFilter and selector->isPVGood and evtPick->passTrigger_ele and selector->ElectronsNoIso.size() == 1 and selector->ElectronsLoose.size() == 0 and selector->MuonsNoIso.size() == 0 and selector->MuonsLoose.size() == 0);
  
  bool singleMu = (evtPick->passFilter and selector->isPVGood and evtPick->passTrigger_mu and selector->ElectronsNoIso.size() == 0 and selector->ElectronsNoIsoLoose.size() == 0 and selector->MuonsNoIso.size() == 1 and selector->MuonsNoIsoLoose.size() == 0);
  bool singleEle = (evtPick->passFilter and selector->isPVGood and evtPick->passTrigger_ele and selector->ElectronsNoIso.size() == 1 and selector->ElectronsNoIsoLoose.size() == 0 and selector->MuonsNoIso.size() == 0 and selector->MuonsNoIsoLoose.size() == 0);
  
  //////=====================================================
  if(!singleMu and !singleEle) return true;
  //////=====================================================
  
  // if(fProcessed%mod_num==0)
  //   Info("Process","Level 4");

  //Processes after single muon/electron selection will be placed in block below
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////
  if(!isData){
    if(singleMu) GetMuonEff(event->muPFRelIso_[selector->MuonsNoIso.at(0)]);
    //if(singleMu) GetMuonEff(event->muPFRelIso_[selector->Muons.at(0)]);
    if(singleEle) GetElectronEff();
  }
  
  bool muonIsoCut = false;
  bool muonNonIsoCut = false;
  if(singleMu){
    muonIsoCut = (event->muPFRelIso_[selector->MuonsNoIso.at(0)] <= 0.15) ? true : false; 
    //muonIsoCut = (event->muPFRelIso_[selector->Muons.at(0)] <= 0.15) ? true : false; 
    muonNonIsoCut = (event->muPFRelIso_[selector->MuonsNoIso.at(0)] > 0.15 and event->muPFRelIso_[selector->MuonsNoIso.at(0)] <= 0.4) ? true : false; 
  }

  bool eleIsoCut = false;
  bool eleNonIsoCut = false;
  if(singleEle){
    double SCeta = event->eleEta_[selector->ElectronsNoIso.at(0)] + event->eleDeltaEtaSC_[selector->ElectronsNoIso.at(0)];
    double absSCEta = TMath::Abs(SCeta);

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
  
  if(singleMu)
    histWt[25]->Fill(event->muPFRelIso_[selector->MuonsNoIso.at(0)]);
  if(singleEle)
    histWt[26]->Fill(event->elePFRelIso_[selector->ElectronsNoIso.at(0)]);

  if(systType == kMuEffUp)
    histWt[10]->Fill(_muEffWeight);
  if(systType == kMuEffDown)
    histWt[11]->Fill(_muEffWeight);
  if(systType == kEleEffUp)
    histWt[12]->Fill(_eleEffWeight);
  if(systType == kEleEffDown)
    histWt[13]->Fill(_muEffWeight);
  
  
  if(singleMu and muonIsoCut){
    histWt[3]->Fill(_muEffWeight);
    histWt[3+fNBWtHists]->Fill(_muEffWeight);
  }
  if(singleMu and muonNonIsoCut){
    histWt[3+2*fNBWtHists]->Fill(_muEffWeight);
    histWt[3+3*fNBWtHists]->Fill(_muEffWeight);
  }

  if(singleEle and eleIsoCut){
    histWt[4]->Fill(_eleEffWeight);
    histWt[4+fNBWtHists]->Fill(_eleEffWeight);
  }
  if(singleEle and eleNonIsoCut){
    histWt[4+2*fNBWtHists]->Fill(_eleEffWeight);
    histWt[4+3*fNBWtHists]->Fill(_eleEffWeight);
  }  
  
  if((singleMu and muonIsoCut) or (singleEle and eleIsoCut)){
    hCutFlow[0]->Fill(2.0);
    hCutFlow[0+fNBCFHists]->Fill(2.0);
  }
  if((singleMu and muonNonIsoCut) or (singleEle and eleNonIsoCut)){
    hCutFlow[0+2*fNBCFHists]->Fill(2.0);
    hCutFlow[0+3*fNBCFHists]->Fill(2.0);
  }
  
  if(singleMu and muonIsoCut){
    hCutFlow[1]->Fill(2.0);
    hCutFlow[2]->Fill(2.0, _sampleWeight*_prefireWeight*_PUWeight*_muEffWeight);
    hCutFlow[5]->Fill(2.0, _sampleWeight*_PUWeight*_muEffWeight);

    hCutFlow[1+fNBCFHists]->Fill(2.0);
    hCutFlow[2+fNBCFHists]->Fill(2.0, _sampleWeight*_prefireWeight*_PUWeight*_muEffWeight);
    hCutFlow[5+fNBCFHists]->Fill(2.0, _sampleWeight*_PUWeight*_muEffWeight);
  }

  if(singleMu and muonNonIsoCut){
    hCutFlow[1+2*fNBCFHists]->Fill(2.0);
    hCutFlow[2+2*fNBCFHists]->Fill(2.0, _sampleWeight*_prefireWeight*_PUWeight*_muEffWeight);
    hCutFlow[5+2*fNBCFHists]->Fill(2.0, _sampleWeight*_PUWeight*_muEffWeight);

    hCutFlow[1+3*fNBCFHists]->Fill(2.0);
    hCutFlow[2+3*fNBCFHists]->Fill(2.0, _sampleWeight*_prefireWeight*_PUWeight*_muEffWeight);
    hCutFlow[5+3*fNBCFHists]->Fill(2.0, _sampleWeight*_PUWeight*_muEffWeight);
  }
  
  //elec
  if(singleEle and eleIsoCut){
    hCutFlow[3]->Fill(2.0);
    hCutFlow[4]->Fill(2.0, _sampleWeight*_prefireWeight*_PUWeight*_eleEffWeight);

    hCutFlow[3+fNBCFHists]->Fill(2.0);
    hCutFlow[4+fNBCFHists]->Fill(2.0, _sampleWeight*_prefireWeight*_PUWeight*_eleEffWeight);
  }

  if(singleEle and eleIsoCut){
    hCutFlow[3+2*fNBCFHists]->Fill(2.0);
    hCutFlow[4+2*fNBCFHists]->Fill(2.0, _sampleWeight*_prefireWeight*_PUWeight*_eleEffWeight);

    hCutFlow[3+3*fNBCFHists]->Fill(2.0);
    hCutFlow[4+3*fNBCFHists]->Fill(2.0, _sampleWeight*_prefireWeight*_PUWeight*_eleEffWeight);
  }

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  //////=====================================================
  if(selector->Jets.size() < 4 ) return true;
  //////=====================================================

  // if(fProcessed%mod_num==0)
  //   Info("Process","Level 5");

  //Processes after njet >= 4 selection will be placed in block below
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // if fNBaseHists = 100, then == 0:99 for Iso HighMET | 100:199 for Iso LowMET | 200:299 nonIso HighMET | 300:399 nonIso LowMET

  if((singleMu and muonIsoCut) or (singleEle and eleIsoCut)){
    hCutFlow[0]->Fill(3.0);
    hCutFlow[0+fNBCFHists]->Fill(3.0);
  }
  if((singleMu and muonNonIsoCut) or (singleEle and eleNonIsoCut)){
    hCutFlow[0+2*fNBCFHists]->Fill(3.0);
    hCutFlow[0+3*fNBCFHists]->Fill(3.0);
  }
  
  if(singleMu and muonIsoCut){
    hCutFlow[1]->Fill(3.0);
    hCutFlow[2]->Fill(3.0, _sampleWeight*_prefireWeight*_PUWeight*_muEffWeight);
    hCutFlow[5]->Fill(3.0, _sampleWeight*_PUWeight*_muEffWeight);

    hCutFlow[1+fNBCFHists]->Fill(3.0);
    hCutFlow[2+fNBCFHists]->Fill(3.0, _sampleWeight*_prefireWeight*_PUWeight*_muEffWeight);
    hCutFlow[5+fNBCFHists]->Fill(3.0, _sampleWeight*_PUWeight*_muEffWeight);
  }

  if(singleMu and muonNonIsoCut){
    hCutFlow[1+2*fNBCFHists]->Fill(3.0);
    hCutFlow[2+2*fNBCFHists]->Fill(3.0, _sampleWeight*_prefireWeight*_PUWeight*_muEffWeight);
    hCutFlow[5+2*fNBCFHists]->Fill(3.0, _sampleWeight*_PUWeight*_muEffWeight);

    hCutFlow[1+3*fNBCFHists]->Fill(3.0);
    hCutFlow[2+3*fNBCFHists]->Fill(3.0, _sampleWeight*_prefireWeight*_PUWeight*_muEffWeight);
    hCutFlow[5+3*fNBCFHists]->Fill(3.0, _sampleWeight*_PUWeight*_muEffWeight);
  }
  
  //elec
  if(singleEle and eleIsoCut){
    hCutFlow[3]->Fill(3.0);
    hCutFlow[4]->Fill(3.0, _sampleWeight*_prefireWeight*_PUWeight*_eleEffWeight);

    hCutFlow[3+fNBCFHists]->Fill(3.0);
    hCutFlow[4+fNBCFHists]->Fill(3.0, _sampleWeight*_prefireWeight*_PUWeight*_eleEffWeight);
  }

  if(singleEle and eleIsoCut){
    hCutFlow[3+2*fNBCFHists]->Fill(3.0);
    hCutFlow[4+2*fNBCFHists]->Fill(3.0, _sampleWeight*_prefireWeight*_PUWeight*_eleEffWeight);

    hCutFlow[3+3*fNBCFHists]->Fill(3.0);
    hCutFlow[4+3*fNBCFHists]->Fill(3.0, _sampleWeight*_prefireWeight*_PUWeight*_eleEffWeight);
  }

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////

  if(singleMu)
    histWt[27]->Fill(selector->METPt);
  
  if(singleEle)
    histWt[28]->Fill(selector->METPt);
  

  METThreshold = 20. ;
  bool isLowMET = false;
  //////=====================================================
  //if(selector->METPt < METThreshold ) return true;
  if(selector->METPt < METThreshold ) isLowMET = true;
  //////=====================================================

  // if(fProcessed%mod_num==0)
  //   Info("Process","Level 6");

  //Processes after MET selection will be placed in block below
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////
  if((singleMu and muonIsoCut) or (singleEle and eleIsoCut)){
    if(!isLowMET)
      hCutFlow[0]->Fill(4.0);
    else
      hCutFlow[0+fNBCFHists]->Fill(4.0);
  }
  if((singleMu and muonNonIsoCut) or (singleEle and eleNonIsoCut)){
    if(!isLowMET)
      hCutFlow[0+2*fNBCFHists]->Fill(4.0);
    else
      hCutFlow[0+3*fNBCFHists]->Fill(4.0);
  }
  
  if(singleMu and muonIsoCut){
    if(!isLowMET){
      hCutFlow[1]->Fill(4.0);
      hCutFlow[2]->Fill(4.0, _sampleWeight*_prefireWeight*_PUWeight*_muEffWeight);
      hCutFlow[5]->Fill(4.0, _sampleWeight*_PUWeight*_muEffWeight);
    }else{
      hCutFlow[1+fNBCFHists]->Fill(4.0);
      hCutFlow[2+fNBCFHists]->Fill(4.0, _sampleWeight*_prefireWeight*_PUWeight*_muEffWeight);
      hCutFlow[5+fNBCFHists]->Fill(4.0, _sampleWeight*_PUWeight*_muEffWeight);
    }
  }

  if(singleMu and muonNonIsoCut){
    if(!isLowMET){
      hCutFlow[1+2*fNBCFHists]->Fill(4.0);
      hCutFlow[2+2*fNBCFHists]->Fill(4.0, _sampleWeight*_prefireWeight*_PUWeight*_muEffWeight);
      hCutFlow[5+2*fNBCFHists]->Fill(4.0, _sampleWeight*_PUWeight*_muEffWeight);
    }else{
      hCutFlow[1+3*fNBCFHists]->Fill(4.0);
      hCutFlow[2+3*fNBCFHists]->Fill(4.0, _sampleWeight*_prefireWeight*_PUWeight*_muEffWeight);
      hCutFlow[5+3*fNBCFHists]->Fill(4.0, _sampleWeight*_PUWeight*_muEffWeight);
    }
  }
  
  //elec
  if(singleEle and eleIsoCut){
    if(!isLowMET){
      hCutFlow[3]->Fill(4.0);
      hCutFlow[4]->Fill(4.0, _sampleWeight*_prefireWeight*_PUWeight*_eleEffWeight);
    }else{
      hCutFlow[3+fNBCFHists]->Fill(4.0);
      hCutFlow[4+fNBCFHists]->Fill(4.0, _sampleWeight*_prefireWeight*_PUWeight*_eleEffWeight);
    }
  }

  if(singleEle and eleIsoCut){
    if(!isLowMET){
      hCutFlow[3+2*fNBCFHists]->Fill(4.0);
      hCutFlow[4+2*fNBCFHists]->Fill(4.0, _sampleWeight*_prefireWeight*_PUWeight*_eleEffWeight);
    }else{
      hCutFlow[3+3*fNBCFHists]->Fill(4.0);
      hCutFlow[4+3*fNBCFHists]->Fill(4.0, _sampleWeight*_prefireWeight*_PUWeight*_eleEffWeight);
    }
  }

  // if((singleMu and muonIsoCut) or (singleEle and eleIsoCut))
  //   hCutFlow[0]->Fill(4.0);
  
  // if(singleMu and muonIsoCut){
  //   hCutFlow[1]->Fill(4.0);
  //   hCutFlow[2]->Fill(4.0, _sampleWeight*_prefireWeight*_PUWeight*_muEffWeight);
  //   hCutFlow[5]->Fill(4.0, _sampleWeight*_PUWeight*_muEffWeight);
  // }
  
  // //elec
  // if(singleEle and eleIsoCut){
  //   hCutFlow[3]->Fill(4.0);
  //   hCutFlow[4]->Fill(4.0, _sampleWeight*_prefireWeight*_PUWeight*_eleEffWeight);
  // }
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////

  //////=====================================================
  if(selector->bJets.size() < 2 ) return true;
  //////=====================================================
  
  // if(fProcessed%mod_num==0)
  //   Info("Process","Level 7");

  //Processes after nbjet >= 2 selection will be placed in block below
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////
  if (fSyst == "base" and !isData){
    
    TheoWeights();
    
    histWt[14]->Fill(_pdfweight_Up);
    histWt[15]->Fill(_pdfweight_Do);
    histWt[16]->Fill(_q2weight_Up);
    histWt[17]->Fill(_q2weight_Do);
    histWt[18]->Fill(_FSRweight_Up);
    histWt[19]->Fill(_FSRweight_Do);
    histWt[20]->Fill(_FSRweight_Up);
    histWt[21]->Fill(_FSRweight_Do);
    
  }

  if(!isData){
    GetBtagSF_1a();
    //_topPtReWeight = topPtReweight();
    _topPtReWeight = 1.0;
  }
  switch (systType) {
  case kBTagbDown:
    histWt[6]->Fill(_bTagWeight);
    break;      
  case kBTagbUp:
    histWt[7]->Fill(_bTagWeight);
    break;
  case kBTaglDown:
    histWt[8]->Fill(_bTagWeight);
    break;
  case kBTaglUp:
    histWt[9]->Fill(_bTagWeight);
    break;
  default:
    histWt[5]->Fill(_bTagWeight);
    break;
  }
  histWt[24]->Fill(_topPtReWeight);
  
  double mu_wt = _sampleWeight*_prefireWeight*_PUWeight*_muEffWeight*_bTagWeight*_topPtReWeight ;
  double ele_wt = _sampleWeight*_prefireWeight*_PUWeight*_eleEffWeight*_bTagWeight*_topPtReWeight ;
  
  if((singleMu and muonIsoCut) or (singleEle and eleIsoCut)){
    if(!isLowMET)
      hCutFlow[0]->Fill(5.0);
    else
      hCutFlow[0+fNBCFHists]->Fill(5.0);
  }

  if((singleMu and muonNonIsoCut) or (singleEle and eleNonIsoCut)){
    if(!isLowMET)
      hCutFlow[0+2*fNBCFHists]->Fill(5.0);
    else
      hCutFlow[0+3*fNBCFHists]->Fill(5.0);
  }

  if (fSyst == "base"){
  
    if(singleMu and muonIsoCut){

      if(!isLowMET){
	
	hCutFlow[1]->Fill(5.0);
	hCutFlow[2]->Fill(5.0, mu_wt);
	hCutFlow[5]->Fill(5.0, _sampleWeight*_PUWeight*_muEffWeight*_bTagWeight*_topPtReWeight);
	////////////////// base ////////////////////////////
	histObs[0]->Fill(event->muPt_[selector->MuonsNoIso.at(0)] * event->muRoccoR_[selector->MuonsNoIso.at(0)], mu_wt);
	histObs[1]->Fill(event->muEta_[selector->MuonsNoIso.at(0)], mu_wt);
	histObs[2]->Fill(event->muPhi_[selector->MuonsNoIso.at(0)], mu_wt);
	for(unsigned int ijet = 0; ijet < selector->Jets.size(); ijet++){
	  int jetInd = selector->Jets.at(ijet);
	  histObs[6]->Fill(selector->JetsPtSmeared.at(ijet), mu_wt);
	  histObs[7]->Fill(event->jetEta_[jetInd], mu_wt);
	  histObs[8]->Fill(event->jetPhi_[jetInd], mu_wt);
	}
	histObs[12]->Fill(selector->METPt, mu_wt);
	histObs[13]->Fill(selector->METPhi, mu_wt);
	histObs[16]->Fill(selector->Jets.size(), mu_wt);
	histObs[17]->Fill(selector->bJets.size(), mu_wt);
	/////////////////////////////////////////////////////
	
	////////////////// pdfup /////////////////////////////
	histObs[0+4*fNBObHists]->Fill(event->muPt_[selector->MuonsNoIso.at(0)] * event->muRoccoR_[selector->MuonsNoIso.at(0)], mu_wt*_pdfweight_Up);
	histObs[1+4*fNBObHists]->Fill(event->muEta_[selector->MuonsNoIso.at(0)], mu_wt*_pdfweight_Up);
	histObs[2+4*fNBObHists]->Fill(event->muPhi_[selector->MuonsNoIso.at(0)], mu_wt*_pdfweight_Up);
	for(unsigned int ijet = 0; ijet < selector->Jets.size(); ijet++){
	  int jetInd = selector->Jets.at(ijet);
	  histObs[6+4*fNBObHists]->Fill(selector->JetsPtSmeared.at(ijet), mu_wt*_pdfweight_Up);
	  histObs[7+4*fNBObHists]->Fill(event->jetEta_[jetInd], mu_wt*_pdfweight_Up);
	  histObs[8+4*fNBObHists]->Fill(event->jetPhi_[jetInd], mu_wt*_pdfweight_Up);
	}
	histObs[12+4*fNBObHists]->Fill(selector->METPt, mu_wt*_pdfweight_Up);
	histObs[13+4*fNBObHists]->Fill(selector->METPhi, mu_wt*_pdfweight_Up);
	histObs[16+4*fNBObHists]->Fill(selector->Jets.size(), mu_wt*_pdfweight_Up);
	histObs[17+4*fNBObHists]->Fill(selector->bJets.size(), mu_wt*_pdfweight_Up);
	/////////////////////////////////////////////////////
	////////////////// pdfdown /////////////////////////////
	histObs[0+5*fNBObHists]->Fill(event->muPt_[selector->MuonsNoIso.at(0)] * event->muRoccoR_[selector->MuonsNoIso.at(0)], mu_wt*_pdfweight_Do);
	histObs[1+5*fNBObHists]->Fill(event->muEta_[selector->MuonsNoIso.at(0)], mu_wt*_pdfweight_Do);
	histObs[2+5*fNBObHists]->Fill(event->muPhi_[selector->MuonsNoIso.at(0)], mu_wt*_pdfweight_Do);
	for(unsigned int ijet = 0; ijet < selector->Jets.size(); ijet++){
	  int jetInd = selector->Jets.at(ijet);
	  histObs[6+5*fNBObHists]->Fill(selector->JetsPtSmeared.at(ijet), mu_wt*_pdfweight_Do);
	  histObs[7+5*fNBObHists]->Fill(event->jetEta_[jetInd], mu_wt*_pdfweight_Do);
	  histObs[8+5*fNBObHists]->Fill(event->jetPhi_[jetInd], mu_wt*_pdfweight_Do);
	}
	histObs[12+5*fNBObHists]->Fill(selector->METPt, mu_wt*_pdfweight_Do);
	histObs[13+5*fNBObHists]->Fill(selector->METPhi, mu_wt*_pdfweight_Do);
	histObs[16+5*fNBObHists]->Fill(selector->Jets.size(), mu_wt*_pdfweight_Do);
	histObs[17+5*fNBObHists]->Fill(selector->bJets.size(), mu_wt*_pdfweight_Do);
	/////////////////////////////////////////////////////
	////////////////// q2up /////////////////////////////
	histObs[0+6*fNBObHists]->Fill(event->muPt_[selector->MuonsNoIso.at(0)] * event->muRoccoR_[selector->MuonsNoIso.at(0)], mu_wt*_q2weight_Up);
	histObs[1+6*fNBObHists]->Fill(event->muEta_[selector->MuonsNoIso.at(0)], mu_wt*_q2weight_Up);
	histObs[2+6*fNBObHists]->Fill(event->muPhi_[selector->MuonsNoIso.at(0)], mu_wt*_q2weight_Up);
	for(unsigned int ijet = 0; ijet < selector->Jets.size(); ijet++){
	  int jetInd = selector->Jets.at(ijet);
	  histObs[6+6*fNBObHists]->Fill(selector->JetsPtSmeared.at(ijet), mu_wt*_q2weight_Up);
	  histObs[7+6*fNBObHists]->Fill(event->jetEta_[jetInd], mu_wt*_q2weight_Up);
	  histObs[8+6*fNBObHists]->Fill(event->jetPhi_[jetInd], mu_wt*_q2weight_Up);
	}
	histObs[12+6*fNBObHists]->Fill(selector->METPt, mu_wt*_q2weight_Up);
	histObs[13+6*fNBObHists]->Fill(selector->METPhi, mu_wt*_q2weight_Up);
	histObs[16+6*fNBObHists]->Fill(selector->Jets.size(), mu_wt*_q2weight_Up);
	histObs[17+6*fNBObHists]->Fill(selector->bJets.size(), mu_wt*_q2weight_Up);
	/////////////////////////////////////////////////////
	////////////////// q2down /////////////////////////////
	histObs[0+7*fNBObHists]->Fill(event->muPt_[selector->MuonsNoIso.at(0)] * event->muRoccoR_[selector->MuonsNoIso.at(0)], mu_wt*_q2weight_Do);
	histObs[1+7*fNBObHists]->Fill(event->muEta_[selector->MuonsNoIso.at(0)], mu_wt*_q2weight_Do);
	histObs[2+7*fNBObHists]->Fill(event->muPhi_[selector->MuonsNoIso.at(0)], mu_wt*_q2weight_Do);
	for(unsigned int ijet = 0; ijet < selector->Jets.size(); ijet++){
	  int jetInd = selector->Jets.at(ijet);
	  histObs[6+7*fNBObHists]->Fill(selector->JetsPtSmeared.at(ijet), mu_wt*_q2weight_Do);
	  histObs[7+7*fNBObHists]->Fill(event->jetEta_[jetInd], mu_wt*_q2weight_Do);
	  histObs[8+7*fNBObHists]->Fill(event->jetPhi_[jetInd], mu_wt*_q2weight_Do);
	}
	histObs[12+7*fNBObHists]->Fill(selector->METPt, mu_wt*_q2weight_Do);
	histObs[13+7*fNBObHists]->Fill(selector->METPhi, mu_wt*_q2weight_Do);
	histObs[16+7*fNBObHists]->Fill(selector->Jets.size(), mu_wt*_q2weight_Do);
	histObs[17+7*fNBObHists]->Fill(selector->bJets.size(), mu_wt*_q2weight_Do);
	/////////////////////////////////////////////////////
	////////////////// fsrup /////////////////////////////
	histObs[0+8*fNBObHists]->Fill(event->muPt_[selector->MuonsNoIso.at(0)] * event->muRoccoR_[selector->MuonsNoIso.at(0)], mu_wt*_FSRweight_Up);
	histObs[1+8*fNBObHists]->Fill(event->muEta_[selector->MuonsNoIso.at(0)], mu_wt*_FSRweight_Up);
	histObs[2+8*fNBObHists]->Fill(event->muPhi_[selector->MuonsNoIso.at(0)], mu_wt*_FSRweight_Up);
	for(unsigned int ijet = 0; ijet < selector->Jets.size(); ijet++){
	  int jetInd = selector->Jets.at(ijet);
	  histObs[6+8*fNBObHists]->Fill(selector->JetsPtSmeared.at(ijet), mu_wt*_FSRweight_Up);
	  histObs[7+8*fNBObHists]->Fill(event->jetEta_[jetInd], mu_wt*_FSRweight_Up);
	  histObs[8+8*fNBObHists]->Fill(event->jetPhi_[jetInd], mu_wt*_FSRweight_Up);
	}
	histObs[12+8*fNBObHists]->Fill(selector->METPt, mu_wt*_FSRweight_Up);
	histObs[13+8*fNBObHists]->Fill(selector->METPhi, mu_wt*_FSRweight_Up);
	histObs[16+8*fNBObHists]->Fill(selector->Jets.size(), mu_wt*_FSRweight_Up);
	histObs[17+8*fNBObHists]->Fill(selector->bJets.size(), mu_wt*_FSRweight_Up);
	/////////////////////////////////////////////////////
	////////////////// fsrdown /////////////////////////////
	histObs[0+9*fNBObHists]->Fill(event->muPt_[selector->MuonsNoIso.at(0)] * event->muRoccoR_[selector->MuonsNoIso.at(0)], mu_wt*_FSRweight_Do);
	histObs[1+9*fNBObHists]->Fill(event->muEta_[selector->MuonsNoIso.at(0)], mu_wt*_FSRweight_Do);
	histObs[2+9*fNBObHists]->Fill(event->muPhi_[selector->MuonsNoIso.at(0)], mu_wt*_FSRweight_Do);
	for(unsigned int ijet = 0; ijet < selector->Jets.size(); ijet++){
	  int jetInd = selector->Jets.at(ijet);
	  histObs[6+9*fNBObHists]->Fill(selector->JetsPtSmeared.at(ijet), mu_wt*_FSRweight_Do);
	  histObs[7+9*fNBObHists]->Fill(event->jetEta_[jetInd], mu_wt*_FSRweight_Do);
	  histObs[8+9*fNBObHists]->Fill(event->jetPhi_[jetInd], mu_wt*_FSRweight_Do);
	}
	histObs[12+9*fNBObHists]->Fill(selector->METPt, mu_wt*_FSRweight_Do);
	histObs[13+9*fNBObHists]->Fill(selector->METPhi, mu_wt*_FSRweight_Do);
	histObs[16+9*fNBObHists]->Fill(selector->Jets.size(), mu_wt*_FSRweight_Do);
	histObs[17+9*fNBObHists]->Fill(selector->bJets.size(), mu_wt*_FSRweight_Do);
	/////////////////////////////////////////////////////
	////////////////// isrup /////////////////////////////
	histObs[0+10*fNBObHists]->Fill(event->muPt_[selector->MuonsNoIso.at(0)] * event->muRoccoR_[selector->MuonsNoIso.at(0)], mu_wt*_ISRweight_Up);
	histObs[1+10*fNBObHists]->Fill(event->muEta_[selector->MuonsNoIso.at(0)], mu_wt*_ISRweight_Up);
	histObs[2+10*fNBObHists]->Fill(event->muPhi_[selector->MuonsNoIso.at(0)], mu_wt*_ISRweight_Up);
	for(unsigned int ijet = 0; ijet < selector->Jets.size(); ijet++){
	  int jetInd = selector->Jets.at(ijet);
	  histObs[6+10*fNBObHists]->Fill(selector->JetsPtSmeared.at(ijet), mu_wt*_ISRweight_Up);
	  histObs[7+10*fNBObHists]->Fill(event->jetEta_[jetInd], mu_wt*_ISRweight_Up);
	  histObs[8+10*fNBObHists]->Fill(event->jetPhi_[jetInd], mu_wt*_ISRweight_Up);
	}
	histObs[12+10*fNBObHists]->Fill(selector->METPt, mu_wt*_ISRweight_Up);
	histObs[13+10*fNBObHists]->Fill(selector->METPhi, mu_wt*_ISRweight_Up);
	histObs[16+10*fNBObHists]->Fill(selector->Jets.size(), mu_wt*_ISRweight_Up);
	histObs[17+10*fNBObHists]->Fill(selector->bJets.size(), mu_wt*_ISRweight_Up);
	/////////////////////////////////////////////////////
	////////////////// isrdown /////////////////////////////
	histObs[0+11*fNBObHists]->Fill(event->muPt_[selector->MuonsNoIso.at(0)] * event->muRoccoR_[selector->MuonsNoIso.at(0)], mu_wt*_ISRweight_Do);
	histObs[1+11*fNBObHists]->Fill(event->muEta_[selector->MuonsNoIso.at(0)], mu_wt*_ISRweight_Do);
	histObs[2+11*fNBObHists]->Fill(event->muPhi_[selector->MuonsNoIso.at(0)], mu_wt*_ISRweight_Do);
	for(unsigned int ijet = 0; ijet < selector->Jets.size(); ijet++){
	  int jetInd = selector->Jets.at(ijet);
	  histObs[6+11*fNBObHists]->Fill(selector->JetsPtSmeared.at(ijet), mu_wt*_ISRweight_Do);
	  histObs[7+11*fNBObHists]->Fill(event->jetEta_[jetInd], mu_wt*_ISRweight_Do);
	  histObs[8+11*fNBObHists]->Fill(event->jetPhi_[jetInd], mu_wt*_ISRweight_Do);
	}
	histObs[12+11*fNBObHists]->Fill(selector->METPt, mu_wt*_ISRweight_Do);
	histObs[13+11*fNBObHists]->Fill(selector->METPhi, mu_wt*_ISRweight_Do);
	histObs[16+11*fNBObHists]->Fill(selector->Jets.size(), mu_wt*_ISRweight_Do);
	histObs[17+11*fNBObHists]->Fill(selector->bJets.size(), mu_wt*_ISRweight_Do);
	/////////////////////////////////////////////////////


      }else{
	hCutFlow[1+fNBCFHists]->Fill(5.0);
	hCutFlow[2+fNBCFHists]->Fill(5.0, mu_wt);
	hCutFlow[5+fNBCFHists]->Fill(5.0, _sampleWeight*_PUWeight*_muEffWeight*_bTagWeight*_topPtReWeight);
	histObs[0+fNBObHists]->Fill(event->muPt_[selector->MuonsNoIso.at(0)] * event->muRoccoR_[selector->MuonsNoIso.at(0)], mu_wt);
	histObs[1+fNBObHists]->Fill(event->muEta_[selector->MuonsNoIso.at(0)], mu_wt);
	histObs[2+fNBObHists]->Fill(event->muPhi_[selector->MuonsNoIso.at(0)], mu_wt);
	for(unsigned int ijet = 0; ijet < selector->Jets.size(); ijet++){
	  int jetInd = selector->Jets.at(ijet);
	  histObs[6+fNBObHists]->Fill(selector->JetsPtSmeared.at(ijet), mu_wt);
	  histObs[7+fNBObHists]->Fill(event->jetEta_[jetInd], mu_wt);
	  histObs[8+fNBObHists]->Fill(event->jetPhi_[jetInd], mu_wt);
	}
	histObs[12+fNBObHists]->Fill(selector->METPt, mu_wt);
	histObs[13+fNBObHists]->Fill(selector->METPhi, mu_wt);
	histObs[16+fNBObHists]->Fill(selector->Jets.size(), mu_wt);
	histObs[17+fNBObHists]->Fill(selector->bJets.size(), mu_wt);
      }
    }

    if(singleMu and muonNonIsoCut){
      if(!isLowMET){
	hCutFlow[1+2*fNBCFHists]->Fill(5.0);
	hCutFlow[2+2*fNBCFHists]->Fill(5.0, mu_wt);
	hCutFlow[5+2*fNBCFHists]->Fill(5.0, _sampleWeight*_PUWeight*_muEffWeight*_bTagWeight*_topPtReWeight);
	histObs[0+2*fNBObHists]->Fill(event->muPt_[selector->MuonsNoIso.at(0)] * event->muRoccoR_[selector->MuonsNoIso.at(0)], mu_wt);
	histObs[1+2*fNBObHists]->Fill(event->muEta_[selector->MuonsNoIso.at(0)], mu_wt);
	histObs[2+2*fNBObHists]->Fill(event->muPhi_[selector->MuonsNoIso.at(0)], mu_wt);
	for(unsigned int ijet = 0; ijet < selector->Jets.size(); ijet++){
	  int jetInd = selector->Jets.at(ijet);
	  histObs[6+2*fNBObHists]->Fill(selector->JetsPtSmeared.at(ijet), mu_wt);
	  histObs[7+2*fNBObHists]->Fill(event->jetEta_[jetInd], mu_wt);
	  histObs[8+2*fNBObHists]->Fill(event->jetPhi_[jetInd], mu_wt);
	}
	histObs[12+2*fNBObHists]->Fill(selector->METPt, mu_wt);
	histObs[13+2*fNBObHists]->Fill(selector->METPhi, mu_wt);
	histObs[16+2*fNBObHists]->Fill(selector->Jets.size(), mu_wt);
	histObs[17+2*fNBObHists]->Fill(selector->bJets.size(), mu_wt);
      }else{
	hCutFlow[1+3*fNBCFHists]->Fill(5.0);
	hCutFlow[2+3*fNBCFHists]->Fill(5.0, mu_wt);
	hCutFlow[5+3*fNBCFHists]->Fill(5.0, _sampleWeight*_PUWeight*_muEffWeight*_bTagWeight*_topPtReWeight);
	histObs[0+3*fNBObHists]->Fill(event->muPt_[selector->MuonsNoIso.at(0)] * event->muRoccoR_[selector->MuonsNoIso.at(0)], mu_wt);
	histObs[1+3*fNBObHists]->Fill(event->muEta_[selector->MuonsNoIso.at(0)], mu_wt);
	histObs[2+3*fNBObHists]->Fill(event->muPhi_[selector->MuonsNoIso.at(0)], mu_wt);
	for(unsigned int ijet = 0; ijet < selector->Jets.size(); ijet++){
	  int jetInd = selector->Jets.at(ijet);
	  histObs[6+3*fNBObHists]->Fill(selector->JetsPtSmeared.at(ijet), mu_wt);
	  histObs[7+3*fNBObHists]->Fill(event->jetEta_[jetInd], mu_wt);
	  histObs[8+3*fNBObHists]->Fill(event->jetPhi_[jetInd], mu_wt);
	}
	histObs[12+3*fNBObHists]->Fill(selector->METPt, mu_wt);
	histObs[13+3*fNBObHists]->Fill(selector->METPhi, mu_wt);
	histObs[16+3*fNBObHists]->Fill(selector->Jets.size(), mu_wt);
	histObs[17+3*fNBObHists]->Fill(selector->bJets.size(), mu_wt);
      }
    }
  
    //elec
    if(singleEle and eleIsoCut){
      if(!isLowMET){
	hCutFlow[3]->Fill(5.0);
	hCutFlow[4]->Fill(5.0, ele_wt);

	/////////////////// base ///////////////////////////////////////////
	histObs[3]->Fill(event->elePt_[selector->ElectronsNoIso.at(0)], ele_wt);
	histObs[4]->Fill(event->eleEta_[selector->ElectronsNoIso.at(0)], ele_wt);
	histObs[5]->Fill(event->elePhi_[selector->ElectronsNoIso.at(0)], ele_wt);
	for(unsigned int ijet = 0; ijet < selector->Jets.size(); ijet++){
	  int jetInd = selector->Jets.at(ijet);
	  histObs[9]->Fill(selector->JetsPtSmeared.at(ijet), ele_wt);
	  histObs[10]->Fill(event->jetEta_[jetInd], ele_wt);
	  histObs[11]->Fill(event->jetPhi_[jetInd], ele_wt);
	}
	histObs[14]->Fill(selector->METPt, ele_wt);
	histObs[15]->Fill(selector->METPhi, ele_wt);
	histObs[18]->Fill(selector->Jets.size(), ele_wt);
	histObs[19]->Fill(selector->bJets.size(), ele_wt);
	///////////////////////////////////////////////////////////////////

	////////////////// pdfup /////////////////////////////
	histObs[3+4*fNBObHists]->Fill(event->elePt_[selector->ElectronsNoIso.at(0)], ele_wt*_pdfweight_Up);
	histObs[4+4*fNBObHists]->Fill(event->eleEta_[selector->ElectronsNoIso.at(0)], ele_wt*_pdfweight_Up);
	histObs[5+4*fNBObHists]->Fill(event->elePhi_[selector->ElectronsNoIso.at(0)], ele_wt*_pdfweight_Up);
	for(unsigned int ijet = 0; ijet < selector->Jets.size(); ijet++){
	  int jetInd = selector->Jets.at(ijet);
	  histObs[9+4*fNBObHists]->Fill(selector->JetsPtSmeared.at(ijet), ele_wt*_pdfweight_Up);
	  histObs[10+4*fNBObHists]->Fill(event->jetEta_[jetInd], ele_wt*_pdfweight_Up);
	  histObs[11+4*fNBObHists]->Fill(event->jetPhi_[jetInd], ele_wt*_pdfweight_Up);
	}
	histObs[14+4*fNBObHists]->Fill(selector->METPt, ele_wt*_pdfweight_Up);
	histObs[15+4*fNBObHists]->Fill(selector->METPhi, ele_wt*_pdfweight_Up);
	histObs[18+4*fNBObHists]->Fill(selector->Jets.size(), ele_wt*_pdfweight_Up);
	histObs[19+4*fNBObHists]->Fill(selector->bJets.size(), ele_wt*_pdfweight_Up);
	/////////////////////////////////////////////////////
	////////////////// pdfdown /////////////////////////////
	histObs[3+5*fNBObHists]->Fill(event->elePt_[selector->ElectronsNoIso.at(0)], ele_wt*_pdfweight_Do);
	histObs[4+5*fNBObHists]->Fill(event->eleEta_[selector->ElectronsNoIso.at(0)], ele_wt*_pdfweight_Do);
	histObs[5+5*fNBObHists]->Fill(event->elePhi_[selector->ElectronsNoIso.at(0)], ele_wt*_pdfweight_Do);
	for(unsigned int ijet = 0; ijet < selector->Jets.size(); ijet++){
	  int jetInd = selector->Jets.at(ijet);
	  histObs[9+5*fNBObHists]->Fill(selector->JetsPtSmeared.at(ijet), ele_wt*_pdfweight_Do);
	  histObs[10+5*fNBObHists]->Fill(event->jetEta_[jetInd], ele_wt*_pdfweight_Do);
	  histObs[11+5*fNBObHists]->Fill(event->jetPhi_[jetInd], ele_wt*_pdfweight_Do);
	}
	histObs[14+5*fNBObHists]->Fill(selector->METPt, ele_wt*_pdfweight_Do);
	histObs[15+5*fNBObHists]->Fill(selector->METPhi, ele_wt*_pdfweight_Do);
	histObs[18+5*fNBObHists]->Fill(selector->Jets.size(), ele_wt*_pdfweight_Do);
	histObs[19+5*fNBObHists]->Fill(selector->bJets.size(), ele_wt*_pdfweight_Do);
	/////////////////////////////////////////////////////
	////////////////// q2up /////////////////////////////
	histObs[3+6*fNBObHists]->Fill(event->elePt_[selector->ElectronsNoIso.at(0)], ele_wt*_q2weight_Up);
	histObs[4+6*fNBObHists]->Fill(event->eleEta_[selector->ElectronsNoIso.at(0)], ele_wt*_q2weight_Up);
	histObs[5+6*fNBObHists]->Fill(event->elePhi_[selector->ElectronsNoIso.at(0)], ele_wt*_q2weight_Up);
	for(unsigned int ijet = 0; ijet < selector->Jets.size(); ijet++){
	  int jetInd = selector->Jets.at(ijet);
	  histObs[9+6*fNBObHists]->Fill(selector->JetsPtSmeared.at(ijet), ele_wt*_q2weight_Up);
	  histObs[10+6*fNBObHists]->Fill(event->jetEta_[jetInd], ele_wt*_q2weight_Up);
	  histObs[11+6*fNBObHists]->Fill(event->jetPhi_[jetInd], ele_wt*_q2weight_Up);
	}
	histObs[14+6*fNBObHists]->Fill(selector->METPt, ele_wt*_q2weight_Up);
	histObs[15+6*fNBObHists]->Fill(selector->METPhi, ele_wt*_q2weight_Up);
	histObs[18+6*fNBObHists]->Fill(selector->Jets.size(), ele_wt*_q2weight_Up);
	histObs[19+6*fNBObHists]->Fill(selector->bJets.size(), ele_wt*_q2weight_Up);
	/////////////////////////////////////////////////////
	////////////////// q2down /////////////////////////////
	histObs[3+7*fNBObHists]->Fill(event->elePt_[selector->ElectronsNoIso.at(0)], ele_wt*_q2weight_Do);
	histObs[4+7*fNBObHists]->Fill(event->eleEta_[selector->ElectronsNoIso.at(0)], ele_wt*_q2weight_Do);
	histObs[5+7*fNBObHists]->Fill(event->elePhi_[selector->ElectronsNoIso.at(0)], ele_wt*_q2weight_Do);
	for(unsigned int ijet = 0; ijet < selector->Jets.size(); ijet++){
	  int jetInd = selector->Jets.at(ijet);
	  histObs[9+7*fNBObHists]->Fill(selector->JetsPtSmeared.at(ijet), ele_wt*_q2weight_Do);
	  histObs[10+7*fNBObHists]->Fill(event->jetEta_[jetInd], ele_wt*_q2weight_Do);
	  histObs[11+7*fNBObHists]->Fill(event->jetPhi_[jetInd], ele_wt*_q2weight_Do);
	}
	histObs[14+7*fNBObHists]->Fill(selector->METPt, ele_wt*_q2weight_Do);
	histObs[15+7*fNBObHists]->Fill(selector->METPhi, ele_wt*_q2weight_Do);
	histObs[18+7*fNBObHists]->Fill(selector->Jets.size(), ele_wt*_q2weight_Do);
	histObs[19+7*fNBObHists]->Fill(selector->bJets.size(), ele_wt*_q2weight_Do);
	/////////////////////////////////////////////////////
	////////////////// fsrup /////////////////////////////
	histObs[3+8*fNBObHists]->Fill(event->elePt_[selector->ElectronsNoIso.at(0)], ele_wt*_FSRweight_Up);
	histObs[4+8*fNBObHists]->Fill(event->eleEta_[selector->ElectronsNoIso.at(0)], ele_wt*_FSRweight_Up);
	histObs[5+8*fNBObHists]->Fill(event->elePhi_[selector->ElectronsNoIso.at(0)], ele_wt*_FSRweight_Up);
	for(unsigned int ijet = 0; ijet < selector->Jets.size(); ijet++){
	  int jetInd = selector->Jets.at(ijet);
	  histObs[9+8*fNBObHists]->Fill(selector->JetsPtSmeared.at(ijet), ele_wt*_FSRweight_Up);
	  histObs[10+8*fNBObHists]->Fill(event->jetEta_[jetInd], ele_wt*_FSRweight_Up);
	  histObs[11+8*fNBObHists]->Fill(event->jetPhi_[jetInd], ele_wt*_FSRweight_Up);
	}
	histObs[14+8*fNBObHists]->Fill(selector->METPt, ele_wt*_FSRweight_Up);
	histObs[15+8*fNBObHists]->Fill(selector->METPhi, ele_wt*_FSRweight_Up);
	histObs[18+8*fNBObHists]->Fill(selector->Jets.size(), ele_wt*_FSRweight_Up);
	histObs[19+8*fNBObHists]->Fill(selector->bJets.size(), ele_wt*_FSRweight_Up);
	/////////////////////////////////////////////////////
	////////////////// fsrdown /////////////////////////////
	histObs[3+9*fNBObHists]->Fill(event->elePt_[selector->ElectronsNoIso.at(0)], ele_wt*_FSRweight_Do);
	histObs[4+9*fNBObHists]->Fill(event->eleEta_[selector->ElectronsNoIso.at(0)], ele_wt*_FSRweight_Do);
	histObs[5+9*fNBObHists]->Fill(event->elePhi_[selector->ElectronsNoIso.at(0)], ele_wt*_FSRweight_Do);
	for(unsigned int ijet = 0; ijet < selector->Jets.size(); ijet++){
	  int jetInd = selector->Jets.at(ijet);
	  histObs[9+9*fNBObHists]->Fill(selector->JetsPtSmeared.at(ijet), ele_wt*_FSRweight_Do);
	  histObs[10+9*fNBObHists]->Fill(event->jetEta_[jetInd], ele_wt*_FSRweight_Do);
	  histObs[11+9*fNBObHists]->Fill(event->jetPhi_[jetInd], ele_wt*_FSRweight_Do);
	}
	histObs[14+9*fNBObHists]->Fill(selector->METPt, ele_wt*_FSRweight_Do);
	histObs[15+9*fNBObHists]->Fill(selector->METPhi, ele_wt*_FSRweight_Do);
	histObs[18+9*fNBObHists]->Fill(selector->Jets.size(), ele_wt*_FSRweight_Do);
	histObs[19+9*fNBObHists]->Fill(selector->bJets.size(), ele_wt*_FSRweight_Do);
	/////////////////////////////////////////////////////
	////////////////// isrup /////////////////////////////
	histObs[3+10*fNBObHists]->Fill(event->elePt_[selector->ElectronsNoIso.at(0)], ele_wt*_ISRweight_Up);
	histObs[4+10*fNBObHists]->Fill(event->eleEta_[selector->ElectronsNoIso.at(0)], ele_wt*_ISRweight_Up);
	histObs[5+10*fNBObHists]->Fill(event->elePhi_[selector->ElectronsNoIso.at(0)], ele_wt*_ISRweight_Up);
	for(unsigned int ijet = 0; ijet < selector->Jets.size(); ijet++){
	  int jetInd = selector->Jets.at(ijet);
	  histObs[9+10*fNBObHists]->Fill(selector->JetsPtSmeared.at(ijet), ele_wt*_ISRweight_Up);
	  histObs[10+10*fNBObHists]->Fill(event->jetEta_[jetInd], ele_wt*_ISRweight_Up);
	  histObs[11+10*fNBObHists]->Fill(event->jetPhi_[jetInd], ele_wt*_ISRweight_Up);
	}
	histObs[14+10*fNBObHists]->Fill(selector->METPt, ele_wt*_ISRweight_Up);
	histObs[15+10*fNBObHists]->Fill(selector->METPhi, ele_wt*_ISRweight_Up);
	histObs[18+10*fNBObHists]->Fill(selector->Jets.size(), ele_wt*_ISRweight_Up);
	histObs[19+10*fNBObHists]->Fill(selector->bJets.size(), ele_wt*_ISRweight_Up);
	/////////////////////////////////////////////////////
	////////////////// isrdown /////////////////////////////
	histObs[3+11*fNBObHists]->Fill(event->elePt_[selector->ElectronsNoIso.at(0)], ele_wt*_ISRweight_Do);
	histObs[4+11*fNBObHists]->Fill(event->eleEta_[selector->ElectronsNoIso.at(0)], ele_wt*_ISRweight_Do);
	histObs[5+11*fNBObHists]->Fill(event->elePhi_[selector->ElectronsNoIso.at(0)], ele_wt*_ISRweight_Do);
	for(unsigned int ijet = 0; ijet < selector->Jets.size(); ijet++){
	  int jetInd = selector->Jets.at(ijet);
	  histObs[9+11*fNBObHists]->Fill(selector->JetsPtSmeared.at(ijet), ele_wt*_ISRweight_Do);
	  histObs[10+11*fNBObHists]->Fill(event->jetEta_[jetInd], ele_wt*_ISRweight_Do);
	  histObs[11+11*fNBObHists]->Fill(event->jetPhi_[jetInd], ele_wt*_ISRweight_Do);
	}
	histObs[14+11*fNBObHists]->Fill(selector->METPt, ele_wt*_ISRweight_Do);
	histObs[15+11*fNBObHists]->Fill(selector->METPhi, ele_wt*_ISRweight_Do);
	histObs[18+11*fNBObHists]->Fill(selector->Jets.size(), ele_wt*_ISRweight_Do);
	histObs[19+11*fNBObHists]->Fill(selector->bJets.size(), ele_wt*_ISRweight_Do);
	/////////////////////////////////////////////////////

      }else{
	hCutFlow[3+fNBCFHists]->Fill(5.0);
	hCutFlow[4+fNBCFHists]->Fill(5.0, ele_wt);
	histObs[3+fNBObHists]->Fill(event->elePt_[selector->ElectronsNoIso.at(0)], ele_wt);
	histObs[4+fNBObHists]->Fill(event->eleEta_[selector->ElectronsNoIso.at(0)], ele_wt);
	histObs[5+fNBObHists]->Fill(event->elePhi_[selector->ElectronsNoIso.at(0)], ele_wt);
	for(unsigned int ijet = 0; ijet < selector->Jets.size(); ijet++){
	  int jetInd = selector->Jets.at(ijet);
	  histObs[9+fNBObHists]->Fill(selector->JetsPtSmeared.at(ijet), ele_wt);
	  histObs[10+fNBObHists]->Fill(event->jetEta_[jetInd], ele_wt);
	  histObs[11+fNBObHists]->Fill(event->jetPhi_[jetInd], ele_wt);
	}
	histObs[14+fNBObHists]->Fill(selector->METPt, ele_wt);
	histObs[15+fNBObHists]->Fill(selector->METPhi, ele_wt);
	histObs[18+fNBObHists]->Fill(selector->Jets.size(), ele_wt);
	histObs[19+fNBObHists]->Fill(selector->bJets.size(), ele_wt);
      }
    }

    if(singleEle and eleNonIsoCut){
      if(!isLowMET){
	hCutFlow[3+2*fNBCFHists]->Fill(5.0);
	hCutFlow[4+2*fNBCFHists]->Fill(5.0, ele_wt);
	histObs[3+2*fNBObHists]->Fill(event->elePt_[selector->ElectronsNoIso.at(0)], ele_wt);
	histObs[4+2*fNBObHists]->Fill(event->eleEta_[selector->ElectronsNoIso.at(0)], ele_wt);
	histObs[5+2*fNBObHists]->Fill(event->elePhi_[selector->ElectronsNoIso.at(0)], ele_wt);
	for(unsigned int ijet = 0; ijet < selector->Jets.size(); ijet++){
	  int jetInd = selector->Jets.at(ijet);
	  histObs[9+2*fNBObHists]->Fill(selector->JetsPtSmeared.at(ijet), ele_wt);
	  histObs[10+2*fNBObHists]->Fill(event->jetEta_[jetInd], ele_wt);
	  histObs[11+2*fNBObHists]->Fill(event->jetPhi_[jetInd], ele_wt);
	}
	histObs[14+2*fNBObHists]->Fill(selector->METPt, ele_wt);
	histObs[15+2*fNBObHists]->Fill(selector->METPhi, ele_wt);
	histObs[18+2*fNBObHists]->Fill(selector->Jets.size(), ele_wt);
	histObs[19+2*fNBObHists]->Fill(selector->bJets.size(), ele_wt);
      }else{
	hCutFlow[3+3*fNBCFHists]->Fill(5.0);
	hCutFlow[4+3*fNBCFHists]->Fill(5.0, ele_wt);
	histObs[3+3*fNBObHists]->Fill(event->elePt_[selector->ElectronsNoIso.at(0)], ele_wt);
	histObs[4+3*fNBObHists]->Fill(event->eleEta_[selector->ElectronsNoIso.at(0)], ele_wt);
	histObs[5+3*fNBObHists]->Fill(event->elePhi_[selector->ElectronsNoIso.at(0)], ele_wt);
	for(unsigned int ijet = 0; ijet < selector->Jets.size(); ijet++){
	  int jetInd = selector->Jets.at(ijet);
	  histObs[9+3*fNBObHists]->Fill(selector->JetsPtSmeared.at(ijet), ele_wt);
	  histObs[10+3*fNBObHists]->Fill(event->jetEta_[jetInd], ele_wt);
	  histObs[11+3*fNBObHists]->Fill(event->jetPhi_[jetInd], ele_wt);
	}
	histObs[14+3*fNBObHists]->Fill(selector->METPt, ele_wt);
	histObs[15+3*fNBObHists]->Fill(selector->METPhi, ele_wt);
	histObs[18+3*fNBObHists]->Fill(selector->Jets.size(), ele_wt);
	histObs[19+3*fNBObHists]->Fill(selector->bJets.size(), ele_wt);
      }
    }
  }else{

    if(singleMu and muonIsoCut and !isLowMET){

      hCutFlow[1]->Fill(5.0);
      hCutFlow[2]->Fill(5.0, mu_wt);
      hCutFlow[5]->Fill(5.0, _sampleWeight*_PUWeight*_muEffWeight*_bTagWeight*_topPtReWeight);

      histObs[0]->Fill(event->muPt_[selector->MuonsNoIso.at(0)] * event->muRoccoR_[selector->MuonsNoIso.at(0)], mu_wt);
      histObs[1]->Fill(event->muEta_[selector->MuonsNoIso.at(0)], mu_wt);
      histObs[2]->Fill(event->muPhi_[selector->MuonsNoIso.at(0)], mu_wt);
      for(unsigned int ijet = 0; ijet < selector->Jets.size(); ijet++){
	int jetInd = selector->Jets.at(ijet);
	histObs[6]->Fill(selector->JetsPtSmeared.at(ijet), mu_wt);
	histObs[7]->Fill(event->jetEta_[jetInd], mu_wt);
	histObs[8]->Fill(event->jetPhi_[jetInd], mu_wt);
      }
      histObs[12]->Fill(selector->METPt, mu_wt);
      histObs[13]->Fill(selector->METPhi, mu_wt);
      histObs[16]->Fill(selector->Jets.size(), mu_wt);
      histObs[17]->Fill(selector->bJets.size(), mu_wt);
    }

    //elec
    if(singleEle and eleIsoCut and !isLowMET){

      hCutFlow[3]->Fill(5.0);
      hCutFlow[4]->Fill(5.0, ele_wt);

      histObs[3]->Fill(event->elePt_[selector->ElectronsNoIso.at(0)], ele_wt);
      histObs[4]->Fill(event->eleEta_[selector->ElectronsNoIso.at(0)], ele_wt);
      histObs[5]->Fill(event->elePhi_[selector->ElectronsNoIso.at(0)], ele_wt);
      for(unsigned int ijet = 0; ijet < selector->Jets.size(); ijet++){
	int jetInd = selector->Jets.at(ijet);
	histObs[9]->Fill(selector->JetsPtSmeared.at(ijet), ele_wt);
	histObs[10]->Fill(event->jetEta_[jetInd], ele_wt);
	histObs[11]->Fill(event->jetPhi_[jetInd], ele_wt);
      }
      histObs[14]->Fill(selector->METPt, ele_wt);
      histObs[15]->Fill(selector->METPhi, ele_wt);
      histObs[18]->Fill(selector->Jets.size(), ele_wt);
      histObs[19]->Fill(selector->bJets.size(), ele_wt);
    }

  }  
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // if(ProcessKinFit((singleMu and muonIsoCut), false) and !isLowMET){
  //     hCutFlow[1]->Fill(6.0);
  //     hCutFlow[2]->Fill(6.0, mu_wt);
  //     hCutFlow[5]->Fill(6.0, _sampleWeight*_PUWeight*_muEffWeight*_bTagWeight*_topPtReWeight);
  //     histObs[20]->Fill(leptonAF.Pt(), mu_wt);
  //     histObs[21]->Fill(leptonAF.Eta(), mu_wt);
  //     histObs[22]->Fill(leptonAF.Phi(), mu_wt);
  
  //     histObs[26]->Fill(bjlepAF.Pt(), mu_wt);
  //     histObs[26]->Fill(bjhadAF.Pt(), mu_wt);
  //     histObs[26]->Fill(cjhadAF.Pt(), mu_wt);
  //     histObs[26]->Fill(sjhadAF.Pt(), mu_wt);

  //     histObs[27]->Fill(bjlepAF.Eta(), mu_wt);
  //     histObs[27]->Fill(bjhadAF.Eta(), mu_wt);
  //     histObs[27]->Fill(cjhadAF.Eta(), mu_wt);
  //     histObs[27]->Fill(sjhadAF.Eta(), mu_wt);

  //     histObs[28]->Fill(bjlepAF.Phi(), mu_wt);
  //     histObs[28]->Fill(bjhadAF.Phi(), mu_wt);
  //     histObs[28]->Fill(cjhadAF.Phi(), mu_wt);
  //     histObs[28]->Fill(sjhadAF.Phi(), mu_wt);
    
  //     histObs[32]->Fill(neutrinoAF.Pt(), mu_wt);
  //     histObs[33]->Fill(neutrinoAF.Phi(), mu_wt);

  //     histObs[36]->Fill(selector->Jets.size(), mu_wt);
  //     histObs[37]->Fill(selector->bJets.size(), mu_wt);
  
  //     histObs[40]->Fill((cjhadAF+sjhadAF).M(), mu_wt);
  //     histObs[42]->Fill((cjhadBF+sjhadBF).M(), mu_wt);
  // }
  
  // if(ProcessKinFit(false, (singleEle and eleIsoCut)) and !isLowMET){
    
  //     hCutFlow[3]->Fill(6.0);
  //     hCutFlow[4]->Fill(6.0, ele_wt);
  //     histObs[23]->Fill(leptonAF.Pt(), ele_wt);
  //     histObs[24]->Fill(leptonAF.Eta(), ele_wt);
  //     histObs[25]->Fill(leptonAF.Phi(), ele_wt);

  //     histObs[29]->Fill(bjlepAF.Pt(), ele_wt);
  //     histObs[29]->Fill(bjhadAF.Pt(), ele_wt);
  //     histObs[29]->Fill(cjhadAF.Pt(), ele_wt);
  //     histObs[29]->Fill(sjhadAF.Pt(), ele_wt);

  //     histObs[30]->Fill(bjlepAF.Eta(), ele_wt);
  //     histObs[30]->Fill(bjhadAF.Eta(), ele_wt);
  //     histObs[30]->Fill(cjhadAF.Eta(), ele_wt);
  //     histObs[30]->Fill(sjhadAF.Eta(), ele_wt);

  //     histObs[31]->Fill(bjlepAF.Phi(), ele_wt);
  //     histObs[31]->Fill(bjhadAF.Phi(), ele_wt);
  //     histObs[31]->Fill(cjhadAF.Phi(), ele_wt);
  //     histObs[31]->Fill(sjhadAF.Phi(), ele_wt);

  //     histObs[34]->Fill(neutrinoAF.Pt(), ele_wt);
  //     histObs[35]->Fill(neutrinoAF.Phi(), ele_wt);

  //     histObs[38]->Fill(selector->Jets.size(), ele_wt);
  //     histObs[39]->Fill(selector->bJets.size(), ele_wt);    

  //     histObs[41]->Fill((cjhadAF+sjhadAF).M(), ele_wt);
  //     histObs[43]->Fill((cjhadBF+sjhadBF).M(), ele_wt);
  //   }

  if (fSyst == "base"){
    
    if(ProcessKinFit((singleMu and muonIsoCut), false)){
      if(!isLowMET){
	hCutFlow[1]->Fill(6.0);
	hCutFlow[2]->Fill(6.0, mu_wt);
	hCutFlow[5]->Fill(6.0, _sampleWeight*_PUWeight*_muEffWeight*_bTagWeight*_topPtReWeight);
	
	/////////////// base ///////////////////////
	histObs[20]->Fill(leptonAF.Pt(), mu_wt);
	histObs[21]->Fill(leptonAF.Eta(), mu_wt);
	histObs[22]->Fill(leptonAF.Phi(), mu_wt);
  
	histObs[26]->Fill(bjlepAF.Pt(), mu_wt);
	histObs[26]->Fill(bjhadAF.Pt(), mu_wt);
	histObs[26]->Fill(cjhadAF.Pt(), mu_wt);
	histObs[26]->Fill(sjhadAF.Pt(), mu_wt);

	histObs[27]->Fill(bjlepAF.Eta(), mu_wt);
	histObs[27]->Fill(bjhadAF.Eta(), mu_wt);
	histObs[27]->Fill(cjhadAF.Eta(), mu_wt);
	histObs[27]->Fill(sjhadAF.Eta(), mu_wt);

	histObs[28]->Fill(bjlepAF.Phi(), mu_wt);
	histObs[28]->Fill(bjhadAF.Phi(), mu_wt);
	histObs[28]->Fill(cjhadAF.Phi(), mu_wt);
	histObs[28]->Fill(sjhadAF.Phi(), mu_wt);
    
	histObs[32]->Fill(neutrinoAF.Pt(), mu_wt);
	histObs[33]->Fill(neutrinoAF.Phi(), mu_wt);

	histObs[36]->Fill(selector->Jets.size(), mu_wt);
	histObs[37]->Fill(selector->bJets.size(), mu_wt);
  
	histObs[40]->Fill((cjhadAF+sjhadAF).M(), mu_wt);
	histObs[42]->Fill((cjhadBF+sjhadBF).M(), mu_wt);

	/////////////// base ///////////////////////

	////////////// pdfup //////////////////////
	histObs[20+4*fNBObHists]->Fill(leptonAF.Pt(), mu_wt*_pdfweight_Up);
	histObs[21+4*fNBObHists]->Fill(leptonAF.Eta(), mu_wt*_pdfweight_Up);
	histObs[22+4*fNBObHists]->Fill(leptonAF.Phi(), mu_wt*_pdfweight_Up);
  
	histObs[26+4*fNBObHists]->Fill(bjlepAF.Pt(), mu_wt*_pdfweight_Up);
	histObs[26+4*fNBObHists]->Fill(bjhadAF.Pt(), mu_wt*_pdfweight_Up);
	histObs[26+4*fNBObHists]->Fill(cjhadAF.Pt(), mu_wt*_pdfweight_Up);
	histObs[26+4*fNBObHists]->Fill(sjhadAF.Pt(), mu_wt*_pdfweight_Up);

	histObs[27+4*fNBObHists]->Fill(bjlepAF.Eta(), mu_wt*_pdfweight_Up);
	histObs[27+4*fNBObHists]->Fill(bjhadAF.Eta(), mu_wt*_pdfweight_Up);
	histObs[27+4*fNBObHists]->Fill(cjhadAF.Eta(), mu_wt*_pdfweight_Up);
	histObs[27+4*fNBObHists]->Fill(sjhadAF.Eta(), mu_wt*_pdfweight_Up);

	histObs[28+4*fNBObHists]->Fill(bjlepAF.Phi(), mu_wt*_pdfweight_Up);
	histObs[28+4*fNBObHists]->Fill(bjhadAF.Phi(), mu_wt*_pdfweight_Up);
	histObs[28+4*fNBObHists]->Fill(cjhadAF.Phi(), mu_wt*_pdfweight_Up);
	histObs[28+4*fNBObHists]->Fill(sjhadAF.Phi(), mu_wt*_pdfweight_Up);
    
	histObs[32+4*fNBObHists]->Fill(neutrinoAF.Pt(), mu_wt*_pdfweight_Up);
	histObs[33+4*fNBObHists]->Fill(neutrinoAF.Phi(), mu_wt*_pdfweight_Up);

	histObs[36+4*fNBObHists]->Fill(selector->Jets.size(), mu_wt*_pdfweight_Up);
	histObs[37+4*fNBObHists]->Fill(selector->bJets.size(), mu_wt*_pdfweight_Up);
  
	histObs[40+4*fNBObHists]->Fill((cjhadAF+sjhadAF).M(), mu_wt*_pdfweight_Up);
	histObs[42+4*fNBObHists]->Fill((cjhadBF+sjhadBF).M(), mu_wt*_pdfweight_Up);
	////////////////////////////////////////////

	////////////// pdfdown //////////////////////
	histObs[20+5*fNBObHists]->Fill(leptonAF.Pt(), mu_wt*_pdfweight_Do);
	histObs[21+5*fNBObHists]->Fill(leptonAF.Eta(), mu_wt*_pdfweight_Do);
	histObs[22+5*fNBObHists]->Fill(leptonAF.Phi(), mu_wt*_pdfweight_Do);
  
	histObs[26+5*fNBObHists]->Fill(bjlepAF.Pt(), mu_wt*_pdfweight_Do);
	histObs[26+5*fNBObHists]->Fill(bjhadAF.Pt(), mu_wt*_pdfweight_Do);
	histObs[26+5*fNBObHists]->Fill(cjhadAF.Pt(), mu_wt*_pdfweight_Do);
	histObs[26+5*fNBObHists]->Fill(sjhadAF.Pt(), mu_wt*_pdfweight_Do);

	histObs[27+5*fNBObHists]->Fill(bjlepAF.Eta(), mu_wt*_pdfweight_Do);
	histObs[27+5*fNBObHists]->Fill(bjhadAF.Eta(), mu_wt*_pdfweight_Do);
	histObs[27+5*fNBObHists]->Fill(cjhadAF.Eta(), mu_wt*_pdfweight_Do);
	histObs[27+5*fNBObHists]->Fill(sjhadAF.Eta(), mu_wt*_pdfweight_Do);

	histObs[28+5*fNBObHists]->Fill(bjlepAF.Phi(), mu_wt*_pdfweight_Do);
	histObs[28+5*fNBObHists]->Fill(bjhadAF.Phi(), mu_wt*_pdfweight_Do);
	histObs[28+5*fNBObHists]->Fill(cjhadAF.Phi(), mu_wt*_pdfweight_Do);
	histObs[28+5*fNBObHists]->Fill(sjhadAF.Phi(), mu_wt*_pdfweight_Do);
    
	histObs[32+5*fNBObHists]->Fill(neutrinoAF.Pt(), mu_wt*_pdfweight_Do);
	histObs[33+5*fNBObHists]->Fill(neutrinoAF.Phi(), mu_wt*_pdfweight_Do);

	histObs[36+5*fNBObHists]->Fill(selector->Jets.size(), mu_wt*_pdfweight_Do);
	histObs[37+5*fNBObHists]->Fill(selector->bJets.size(), mu_wt*_pdfweight_Do);
  
	histObs[40+5*fNBObHists]->Fill((cjhadAF+sjhadAF).M(), mu_wt*_pdfweight_Do);
	histObs[42+5*fNBObHists]->Fill((cjhadBF+sjhadBF).M(), mu_wt*_pdfweight_Do);
	////////////////////////////////////////////

	////////////// q2up //////////////////////
	histObs[20+6*fNBObHists]->Fill(leptonAF.Pt(), mu_wt*_q2weight_Up);
	histObs[21+6*fNBObHists]->Fill(leptonAF.Eta(), mu_wt*_q2weight_Up);
	histObs[22+6*fNBObHists]->Fill(leptonAF.Phi(), mu_wt*_q2weight_Up);
  
	histObs[26+6*fNBObHists]->Fill(bjlepAF.Pt(), mu_wt*_q2weight_Up);
	histObs[26+6*fNBObHists]->Fill(bjhadAF.Pt(), mu_wt*_q2weight_Up);
	histObs[26+6*fNBObHists]->Fill(cjhadAF.Pt(), mu_wt*_q2weight_Up);
	histObs[26+6*fNBObHists]->Fill(sjhadAF.Pt(), mu_wt*_q2weight_Up);

	histObs[27+6*fNBObHists]->Fill(bjlepAF.Eta(), mu_wt*_q2weight_Up);
	histObs[27+6*fNBObHists]->Fill(bjhadAF.Eta(), mu_wt*_q2weight_Up);
	histObs[27+6*fNBObHists]->Fill(cjhadAF.Eta(), mu_wt*_q2weight_Up);
	histObs[27+6*fNBObHists]->Fill(sjhadAF.Eta(), mu_wt*_q2weight_Up);

	histObs[28+6*fNBObHists]->Fill(bjlepAF.Phi(), mu_wt*_q2weight_Up);
	histObs[28+6*fNBObHists]->Fill(bjhadAF.Phi(), mu_wt*_q2weight_Up);
	histObs[28+6*fNBObHists]->Fill(cjhadAF.Phi(), mu_wt*_q2weight_Up);
	histObs[28+6*fNBObHists]->Fill(sjhadAF.Phi(), mu_wt*_q2weight_Up);
    
	histObs[32+6*fNBObHists]->Fill(neutrinoAF.Pt(), mu_wt*_q2weight_Up);
	histObs[33+6*fNBObHists]->Fill(neutrinoAF.Phi(), mu_wt*_q2weight_Up);

	histObs[36+6*fNBObHists]->Fill(selector->Jets.size(), mu_wt*_q2weight_Up);
	histObs[37+6*fNBObHists]->Fill(selector->bJets.size(), mu_wt*_q2weight_Up);
  
	histObs[40+6*fNBObHists]->Fill((cjhadAF+sjhadAF).M(), mu_wt*_q2weight_Up);
	histObs[42+6*fNBObHists]->Fill((cjhadBF+sjhadBF).M(), mu_wt*_q2weight_Up);
	////////////////////////////////////////////

	////////////// q2down //////////////////////
	histObs[20+7*fNBObHists]->Fill(leptonAF.Pt(), mu_wt*_q2weight_Do);
	histObs[21+7*fNBObHists]->Fill(leptonAF.Eta(), mu_wt*_q2weight_Do);
	histObs[22+7*fNBObHists]->Fill(leptonAF.Phi(), mu_wt*_q2weight_Do);
  
	histObs[26+7*fNBObHists]->Fill(bjlepAF.Pt(), mu_wt*_q2weight_Do);
	histObs[26+7*fNBObHists]->Fill(bjhadAF.Pt(), mu_wt*_q2weight_Do);
	histObs[26+7*fNBObHists]->Fill(cjhadAF.Pt(), mu_wt*_q2weight_Do);
	histObs[26+7*fNBObHists]->Fill(sjhadAF.Pt(), mu_wt*_q2weight_Do);

	histObs[27+7*fNBObHists]->Fill(bjlepAF.Eta(), mu_wt*_q2weight_Do);
	histObs[27+7*fNBObHists]->Fill(bjhadAF.Eta(), mu_wt*_q2weight_Do);
	histObs[27+7*fNBObHists]->Fill(cjhadAF.Eta(), mu_wt*_q2weight_Do);
	histObs[27+7*fNBObHists]->Fill(sjhadAF.Eta(), mu_wt*_q2weight_Do);

	histObs[28+7*fNBObHists]->Fill(bjlepAF.Phi(), mu_wt*_q2weight_Do);
	histObs[28+7*fNBObHists]->Fill(bjhadAF.Phi(), mu_wt*_q2weight_Do);
	histObs[28+7*fNBObHists]->Fill(cjhadAF.Phi(), mu_wt*_q2weight_Do);
	histObs[28+7*fNBObHists]->Fill(sjhadAF.Phi(), mu_wt*_q2weight_Do);
    
	histObs[32+7*fNBObHists]->Fill(neutrinoAF.Pt(), mu_wt*_q2weight_Do);
	histObs[33+7*fNBObHists]->Fill(neutrinoAF.Phi(), mu_wt*_q2weight_Do);

	histObs[36+7*fNBObHists]->Fill(selector->Jets.size(), mu_wt*_q2weight_Do);
	histObs[37+7*fNBObHists]->Fill(selector->bJets.size(), mu_wt*_q2weight_Do);
  
	histObs[40+7*fNBObHists]->Fill((cjhadAF+sjhadAF).M(), mu_wt*_q2weight_Do);
	histObs[42+7*fNBObHists]->Fill((cjhadBF+sjhadBF).M(), mu_wt*_q2weight_Do);
	////////////////////////////////////////////

	////////////// fsrup //////////////////////
	histObs[20+8*fNBObHists]->Fill(leptonAF.Pt(), mu_wt*_FSRweight_Up);
	histObs[21+8*fNBObHists]->Fill(leptonAF.Eta(), mu_wt*_FSRweight_Up);
	histObs[22+8*fNBObHists]->Fill(leptonAF.Phi(), mu_wt*_FSRweight_Up);
  
	histObs[26+8*fNBObHists]->Fill(bjlepAF.Pt(), mu_wt*_FSRweight_Up);
	histObs[26+8*fNBObHists]->Fill(bjhadAF.Pt(), mu_wt*_FSRweight_Up);
	histObs[26+8*fNBObHists]->Fill(cjhadAF.Pt(), mu_wt*_FSRweight_Up);
	histObs[26+8*fNBObHists]->Fill(sjhadAF.Pt(), mu_wt*_FSRweight_Up);

	histObs[27+8*fNBObHists]->Fill(bjlepAF.Eta(), mu_wt*_FSRweight_Up);
	histObs[27+8*fNBObHists]->Fill(bjhadAF.Eta(), mu_wt*_FSRweight_Up);
	histObs[27+8*fNBObHists]->Fill(cjhadAF.Eta(), mu_wt*_FSRweight_Up);
	histObs[27+8*fNBObHists]->Fill(sjhadAF.Eta(), mu_wt*_FSRweight_Up);

	histObs[28+8*fNBObHists]->Fill(bjlepAF.Phi(), mu_wt*_FSRweight_Up);
	histObs[28+8*fNBObHists]->Fill(bjhadAF.Phi(), mu_wt*_FSRweight_Up);
	histObs[28+8*fNBObHists]->Fill(cjhadAF.Phi(), mu_wt*_FSRweight_Up);
	histObs[28+8*fNBObHists]->Fill(sjhadAF.Phi(), mu_wt*_FSRweight_Up);
    
	histObs[32+8*fNBObHists]->Fill(neutrinoAF.Pt(), mu_wt*_FSRweight_Up);
	histObs[33+8*fNBObHists]->Fill(neutrinoAF.Phi(), mu_wt*_FSRweight_Up);

	histObs[36+8*fNBObHists]->Fill(selector->Jets.size(), mu_wt*_FSRweight_Up);
	histObs[37+8*fNBObHists]->Fill(selector->bJets.size(), mu_wt*_FSRweight_Up);
  
	histObs[40+8*fNBObHists]->Fill((cjhadAF+sjhadAF).M(), mu_wt*_FSRweight_Up);
	histObs[42+8*fNBObHists]->Fill((cjhadBF+sjhadBF).M(), mu_wt*_FSRweight_Up);
	////////////////////////////////////////////

	////////////// fsrdown //////////////////////
	histObs[20+9*fNBObHists]->Fill(leptonAF.Pt(), mu_wt*_FSRweight_Do);
	histObs[21+9*fNBObHists]->Fill(leptonAF.Eta(), mu_wt*_FSRweight_Do);
	histObs[22+9*fNBObHists]->Fill(leptonAF.Phi(), mu_wt*_FSRweight_Do);
  
	histObs[26+9*fNBObHists]->Fill(bjlepAF.Pt(), mu_wt*_FSRweight_Do);
	histObs[26+9*fNBObHists]->Fill(bjhadAF.Pt(), mu_wt*_FSRweight_Do);
	histObs[26+9*fNBObHists]->Fill(cjhadAF.Pt(), mu_wt*_FSRweight_Do);
	histObs[26+9*fNBObHists]->Fill(sjhadAF.Pt(), mu_wt*_FSRweight_Do);

	histObs[27+9*fNBObHists]->Fill(bjlepAF.Eta(), mu_wt*_FSRweight_Do);
	histObs[27+9*fNBObHists]->Fill(bjhadAF.Eta(), mu_wt*_FSRweight_Do);
	histObs[27+9*fNBObHists]->Fill(cjhadAF.Eta(), mu_wt*_FSRweight_Do);
	histObs[27+9*fNBObHists]->Fill(sjhadAF.Eta(), mu_wt*_FSRweight_Do);

	histObs[28+9*fNBObHists]->Fill(bjlepAF.Phi(), mu_wt*_FSRweight_Do);
	histObs[28+9*fNBObHists]->Fill(bjhadAF.Phi(), mu_wt*_FSRweight_Do);
	histObs[28+9*fNBObHists]->Fill(cjhadAF.Phi(), mu_wt*_FSRweight_Do);
	histObs[28+9*fNBObHists]->Fill(sjhadAF.Phi(), mu_wt*_FSRweight_Do);
    
	histObs[32+9*fNBObHists]->Fill(neutrinoAF.Pt(), mu_wt*_FSRweight_Do);
	histObs[33+9*fNBObHists]->Fill(neutrinoAF.Phi(), mu_wt*_FSRweight_Do);

	histObs[36+9*fNBObHists]->Fill(selector->Jets.size(), mu_wt*_FSRweight_Do);
	histObs[37+9*fNBObHists]->Fill(selector->bJets.size(), mu_wt*_FSRweight_Do);
  
	histObs[40+9*fNBObHists]->Fill((cjhadAF+sjhadAF).M(), mu_wt*_FSRweight_Do);
	histObs[42+9*fNBObHists]->Fill((cjhadBF+sjhadBF).M(), mu_wt*_FSRweight_Do);
	////////////////////////////////////////////

	////////////// isrup //////////////////////
	histObs[20+10*fNBObHists]->Fill(leptonAF.Pt(), mu_wt*_ISRweight_Up);
	histObs[21+10*fNBObHists]->Fill(leptonAF.Eta(), mu_wt*_ISRweight_Up);
	histObs[22+10*fNBObHists]->Fill(leptonAF.Phi(), mu_wt*_ISRweight_Up);
  
	histObs[26+10*fNBObHists]->Fill(bjlepAF.Pt(), mu_wt*_ISRweight_Up);
	histObs[26+10*fNBObHists]->Fill(bjhadAF.Pt(), mu_wt*_ISRweight_Up);
	histObs[26+10*fNBObHists]->Fill(cjhadAF.Pt(), mu_wt*_ISRweight_Up);
	histObs[26+10*fNBObHists]->Fill(sjhadAF.Pt(), mu_wt*_ISRweight_Up);

	histObs[27+10*fNBObHists]->Fill(bjlepAF.Eta(), mu_wt*_ISRweight_Up);
	histObs[27+10*fNBObHists]->Fill(bjhadAF.Eta(), mu_wt*_ISRweight_Up);
	histObs[27+10*fNBObHists]->Fill(cjhadAF.Eta(), mu_wt*_ISRweight_Up);
	histObs[27+10*fNBObHists]->Fill(sjhadAF.Eta(), mu_wt*_ISRweight_Up);

	histObs[28+10*fNBObHists]->Fill(bjlepAF.Phi(), mu_wt*_ISRweight_Up);
	histObs[28+10*fNBObHists]->Fill(bjhadAF.Phi(), mu_wt*_ISRweight_Up);
	histObs[28+10*fNBObHists]->Fill(cjhadAF.Phi(), mu_wt*_ISRweight_Up);
	histObs[28+10*fNBObHists]->Fill(sjhadAF.Phi(), mu_wt*_ISRweight_Up);
    
	histObs[32+10*fNBObHists]->Fill(neutrinoAF.Pt(), mu_wt*_ISRweight_Up);
	histObs[33+10*fNBObHists]->Fill(neutrinoAF.Phi(), mu_wt*_ISRweight_Up);

	histObs[36+10*fNBObHists]->Fill(selector->Jets.size(), mu_wt*_ISRweight_Up);
	histObs[37+10*fNBObHists]->Fill(selector->bJets.size(), mu_wt*_ISRweight_Up);
  
	histObs[40+10*fNBObHists]->Fill((cjhadAF+sjhadAF).M(), mu_wt*_ISRweight_Up);
	histObs[42+10*fNBObHists]->Fill((cjhadBF+sjhadBF).M(), mu_wt*_ISRweight_Up);
	////////////////////////////////////////////

	////////////// isrdown //////////////////////
	histObs[20+11*fNBObHists]->Fill(leptonAF.Pt(), mu_wt*_ISRweight_Do);
	histObs[21+11*fNBObHists]->Fill(leptonAF.Eta(), mu_wt*_ISRweight_Do);
	histObs[22+11*fNBObHists]->Fill(leptonAF.Phi(), mu_wt*_ISRweight_Do);
  
	histObs[26+11*fNBObHists]->Fill(bjlepAF.Pt(), mu_wt*_ISRweight_Do);
	histObs[26+11*fNBObHists]->Fill(bjhadAF.Pt(), mu_wt*_ISRweight_Do);
	histObs[26+11*fNBObHists]->Fill(cjhadAF.Pt(), mu_wt*_ISRweight_Do);
	histObs[26+11*fNBObHists]->Fill(sjhadAF.Pt(), mu_wt*_ISRweight_Do);

	histObs[27+11*fNBObHists]->Fill(bjlepAF.Eta(), mu_wt*_ISRweight_Do);
	histObs[27+11*fNBObHists]->Fill(bjhadAF.Eta(), mu_wt*_ISRweight_Do);
	histObs[27+11*fNBObHists]->Fill(cjhadAF.Eta(), mu_wt*_ISRweight_Do);
	histObs[27+11*fNBObHists]->Fill(sjhadAF.Eta(), mu_wt*_ISRweight_Do);

	histObs[28+11*fNBObHists]->Fill(bjlepAF.Phi(), mu_wt*_ISRweight_Do);
	histObs[28+11*fNBObHists]->Fill(bjhadAF.Phi(), mu_wt*_ISRweight_Do);
	histObs[28+11*fNBObHists]->Fill(cjhadAF.Phi(), mu_wt*_ISRweight_Do);
	histObs[28+11*fNBObHists]->Fill(sjhadAF.Phi(), mu_wt*_ISRweight_Do);
    
	histObs[32+11*fNBObHists]->Fill(neutrinoAF.Pt(), mu_wt*_ISRweight_Do);
	histObs[33+11*fNBObHists]->Fill(neutrinoAF.Phi(), mu_wt*_ISRweight_Do);

	histObs[36+11*fNBObHists]->Fill(selector->Jets.size(), mu_wt*_ISRweight_Do);
	histObs[37+11*fNBObHists]->Fill(selector->bJets.size(), mu_wt*_ISRweight_Do);
  
	histObs[40+11*fNBObHists]->Fill((cjhadAF+sjhadAF).M(), mu_wt*_ISRweight_Do);
	histObs[42+11*fNBObHists]->Fill((cjhadBF+sjhadBF).M(), mu_wt*_ISRweight_Do);
	////////////////////////////////////////////

      }else{
	hCutFlow[1+fNBCFHists]->Fill(6.0);
	hCutFlow[2+fNBCFHists]->Fill(6.0, mu_wt);
	hCutFlow[5+fNBCFHists]->Fill(6.0, _sampleWeight*_PUWeight*_muEffWeight*_bTagWeight*_topPtReWeight);
	histObs[20+fNBObHists]->Fill(leptonAF.Pt(), mu_wt);
	histObs[21+fNBObHists]->Fill(leptonAF.Eta(), mu_wt);
	histObs[22+fNBObHists]->Fill(leptonAF.Phi(), mu_wt);
  
	histObs[26+fNBObHists]->Fill(bjlepAF.Pt(), mu_wt);
	histObs[26+fNBObHists]->Fill(bjhadAF.Pt(), mu_wt);
	histObs[26+fNBObHists]->Fill(cjhadAF.Pt(), mu_wt);
	histObs[26+fNBObHists]->Fill(sjhadAF.Pt(), mu_wt);

	histObs[27+fNBObHists]->Fill(bjlepAF.Eta(), mu_wt);
	histObs[27+fNBObHists]->Fill(bjhadAF.Eta(), mu_wt);
	histObs[27+fNBObHists]->Fill(cjhadAF.Eta(), mu_wt);
	histObs[27+fNBObHists]->Fill(sjhadAF.Eta(), mu_wt);

	histObs[28+fNBObHists]->Fill(bjlepAF.Phi(), mu_wt);
	histObs[28+fNBObHists]->Fill(bjhadAF.Phi(), mu_wt);
	histObs[28+fNBObHists]->Fill(cjhadAF.Phi(), mu_wt);
	histObs[28+fNBObHists]->Fill(sjhadAF.Phi(), mu_wt);
    
	histObs[32+fNBObHists]->Fill(neutrinoAF.Pt(), mu_wt);
	histObs[33+fNBObHists]->Fill(neutrinoAF.Phi(), mu_wt);

	histObs[36+fNBObHists]->Fill(selector->Jets.size(), mu_wt);
	histObs[37+fNBObHists]->Fill(selector->bJets.size(), mu_wt);
  
	histObs[40+fNBObHists]->Fill((cjhadAF+sjhadAF).M(), mu_wt);
	histObs[42+fNBObHists]->Fill((cjhadBF+sjhadBF).M(), mu_wt);
      }
    }

    if(ProcessKinFit((singleMu and muonNonIsoCut), false)){
      if(!isLowMET){
	hCutFlow[1+2*fNBCFHists]->Fill(6.0);
	hCutFlow[2+2*fNBCFHists]->Fill(6.0, mu_wt);
	hCutFlow[5+2*fNBCFHists]->Fill(6.0, _sampleWeight*_PUWeight*_muEffWeight*_bTagWeight*_topPtReWeight);
	histObs[20+2*fNBObHists]->Fill(leptonAF.Pt(), mu_wt);
	histObs[21+2*fNBObHists]->Fill(leptonAF.Eta(), mu_wt);
	histObs[22+2*fNBObHists]->Fill(leptonAF.Phi(), mu_wt);
  
	histObs[26+2*fNBObHists]->Fill(bjlepAF.Pt(), mu_wt);
	histObs[26+2*fNBObHists]->Fill(bjhadAF.Pt(), mu_wt);
	histObs[26+2*fNBObHists]->Fill(cjhadAF.Pt(), mu_wt);
	histObs[26+2*fNBObHists]->Fill(sjhadAF.Pt(), mu_wt);

	histObs[27+2*fNBObHists]->Fill(bjlepAF.Eta(), mu_wt);
	histObs[27+2*fNBObHists]->Fill(bjhadAF.Eta(), mu_wt);
	histObs[27+2*fNBObHists]->Fill(cjhadAF.Eta(), mu_wt);
	histObs[27+2*fNBObHists]->Fill(sjhadAF.Eta(), mu_wt);

	histObs[28+2*fNBObHists]->Fill(bjlepAF.Phi(), mu_wt);
	histObs[28+2*fNBObHists]->Fill(bjhadAF.Phi(), mu_wt);
	histObs[28+2*fNBObHists]->Fill(cjhadAF.Phi(), mu_wt);
	histObs[28+2*fNBObHists]->Fill(sjhadAF.Phi(), mu_wt);
    
	histObs[32+2*fNBObHists]->Fill(neutrinoAF.Pt(), mu_wt);
	histObs[33+2*fNBObHists]->Fill(neutrinoAF.Phi(), mu_wt);

	histObs[36+2*fNBObHists]->Fill(selector->Jets.size(), mu_wt);
	histObs[37+2*fNBObHists]->Fill(selector->bJets.size(), mu_wt);
  
	histObs[40+2*fNBObHists]->Fill((cjhadAF+sjhadAF).M(), mu_wt);
	histObs[42+2*fNBObHists]->Fill((cjhadBF+sjhadBF).M(), mu_wt);
      }else{
	hCutFlow[1+3*fNBCFHists]->Fill(6.0);
	hCutFlow[2+3*fNBCFHists]->Fill(6.0, mu_wt);
	hCutFlow[5+3*fNBCFHists]->Fill(6.0, _sampleWeight*_PUWeight*_muEffWeight*_bTagWeight*_topPtReWeight);
	histObs[20+3*fNBObHists]->Fill(leptonAF.Pt(), mu_wt);
	histObs[21+3*fNBObHists]->Fill(leptonAF.Eta(), mu_wt);
	histObs[22+3*fNBObHists]->Fill(leptonAF.Phi(), mu_wt);
  
	histObs[26+3*fNBObHists]->Fill(bjlepAF.Pt(), mu_wt);
	histObs[26+3*fNBObHists]->Fill(bjhadAF.Pt(), mu_wt);
	histObs[26+3*fNBObHists]->Fill(cjhadAF.Pt(), mu_wt);
	histObs[26+3*fNBObHists]->Fill(sjhadAF.Pt(), mu_wt);

	histObs[27+3*fNBObHists]->Fill(bjlepAF.Eta(), mu_wt);
	histObs[27+3*fNBObHists]->Fill(bjhadAF.Eta(), mu_wt);
	histObs[27+3*fNBObHists]->Fill(cjhadAF.Eta(), mu_wt);
	histObs[27+3*fNBObHists]->Fill(sjhadAF.Eta(), mu_wt);

	histObs[28+3*fNBObHists]->Fill(bjlepAF.Phi(), mu_wt);
	histObs[28+3*fNBObHists]->Fill(bjhadAF.Phi(), mu_wt);
	histObs[28+3*fNBObHists]->Fill(cjhadAF.Phi(), mu_wt);
	histObs[28+3*fNBObHists]->Fill(sjhadAF.Phi(), mu_wt);
    
	histObs[32+3*fNBObHists]->Fill(neutrinoAF.Pt(), mu_wt);
	histObs[33+3*fNBObHists]->Fill(neutrinoAF.Phi(), mu_wt);

	histObs[36+3*fNBObHists]->Fill(selector->Jets.size(), mu_wt);
	histObs[37+3*fNBObHists]->Fill(selector->bJets.size(), mu_wt);
  
	histObs[40+3*fNBObHists]->Fill((cjhadAF+sjhadAF).M(), mu_wt);
	histObs[42+3*fNBObHists]->Fill((cjhadBF+sjhadBF).M(), mu_wt);
      }
    }
  
    if(ProcessKinFit(false, (singleEle and eleIsoCut))){
      if(!isLowMET){
	hCutFlow[3]->Fill(6.0);
	hCutFlow[4]->Fill(6.0, ele_wt);
	////////////////////////////// base ////////////////////////////////
	histObs[23]->Fill(leptonAF.Pt(), ele_wt);
	histObs[24]->Fill(leptonAF.Eta(), ele_wt);
	histObs[25]->Fill(leptonAF.Phi(), ele_wt);

	histObs[29]->Fill(bjlepAF.Pt(), ele_wt);
	histObs[29]->Fill(bjhadAF.Pt(), ele_wt);
	histObs[29]->Fill(cjhadAF.Pt(), ele_wt);
	histObs[29]->Fill(sjhadAF.Pt(), ele_wt);

	histObs[30]->Fill(bjlepAF.Eta(), ele_wt);
	histObs[30]->Fill(bjhadAF.Eta(), ele_wt);
	histObs[30]->Fill(cjhadAF.Eta(), ele_wt);
	histObs[30]->Fill(sjhadAF.Eta(), ele_wt);

	histObs[31]->Fill(bjlepAF.Phi(), ele_wt);
	histObs[31]->Fill(bjhadAF.Phi(), ele_wt);
	histObs[31]->Fill(cjhadAF.Phi(), ele_wt);
	histObs[31]->Fill(sjhadAF.Phi(), ele_wt);

	histObs[34]->Fill(neutrinoAF.Pt(), ele_wt);
	histObs[35]->Fill(neutrinoAF.Phi(), ele_wt);

	histObs[38]->Fill(selector->Jets.size(), ele_wt);
	histObs[39]->Fill(selector->bJets.size(), ele_wt);    

	histObs[41]->Fill((cjhadAF+sjhadAF).M(), ele_wt);
	histObs[43]->Fill((cjhadBF+sjhadBF).M(), ele_wt);
	////////////////////////////////////////////////////////////////
	
	////////////// pdfup //////////////////////
	histObs[23+4*fNBObHists]->Fill(leptonAF.Pt(), ele_wt*_pdfweight_Up);
	histObs[24+4*fNBObHists]->Fill(leptonAF.Eta(), ele_wt*_pdfweight_Up);
	histObs[25+4*fNBObHists]->Fill(leptonAF.Phi(), ele_wt*_pdfweight_Up);
	
	histObs[29+4*fNBObHists]->Fill(bjlepAF.Pt(), ele_wt*_pdfweight_Up);
	histObs[29+4*fNBObHists]->Fill(bjhadAF.Pt(), ele_wt*_pdfweight_Up);
	histObs[29+4*fNBObHists]->Fill(cjhadAF.Pt(), ele_wt*_pdfweight_Up);
	histObs[29+4*fNBObHists]->Fill(sjhadAF.Pt(), ele_wt*_pdfweight_Up);

	histObs[30+4*fNBObHists]->Fill(bjlepAF.Eta(), ele_wt*_pdfweight_Up);
	histObs[30+4*fNBObHists]->Fill(bjhadAF.Eta(), ele_wt*_pdfweight_Up);
	histObs[30+4*fNBObHists]->Fill(cjhadAF.Eta(), ele_wt*_pdfweight_Up);
	histObs[30+4*fNBObHists]->Fill(sjhadAF.Eta(), ele_wt*_pdfweight_Up);

	histObs[31+4*fNBObHists]->Fill(bjlepAF.Phi(), ele_wt*_pdfweight_Up);
	histObs[31+4*fNBObHists]->Fill(bjhadAF.Phi(), ele_wt*_pdfweight_Up);
	histObs[31+4*fNBObHists]->Fill(cjhadAF.Phi(), ele_wt*_pdfweight_Up);
	histObs[31+4*fNBObHists]->Fill(sjhadAF.Phi(), ele_wt*_pdfweight_Up);
    
	histObs[34+4*fNBObHists]->Fill(neutrinoAF.Pt(), ele_wt*_pdfweight_Up);
	histObs[35+4*fNBObHists]->Fill(neutrinoAF.Phi(), ele_wt*_pdfweight_Up);

	histObs[38+4*fNBObHists]->Fill(selector->Jets.size(), ele_wt*_pdfweight_Up);
	histObs[39+4*fNBObHists]->Fill(selector->bJets.size(), ele_wt*_pdfweight_Up);
  
	histObs[41+4*fNBObHists]->Fill((cjhadAF+sjhadAF).M(), ele_wt*_pdfweight_Up);
	histObs[43+4*fNBObHists]->Fill((cjhadBF+sjhadBF).M(), ele_wt*_pdfweight_Up);
	////////////////////////////////////////////

	////////////// pdfdown //////////////////////
	histObs[23+5*fNBObHists]->Fill(leptonAF.Pt(), ele_wt*_pdfweight_Do);
	histObs[24+5*fNBObHists]->Fill(leptonAF.Eta(), ele_wt*_pdfweight_Do);
	histObs[25+5*fNBObHists]->Fill(leptonAF.Phi(), ele_wt*_pdfweight_Do);
  
	histObs[29+5*fNBObHists]->Fill(bjlepAF.Pt(), ele_wt*_pdfweight_Do);
	histObs[29+5*fNBObHists]->Fill(bjhadAF.Pt(), ele_wt*_pdfweight_Do);
	histObs[29+5*fNBObHists]->Fill(cjhadAF.Pt(), ele_wt*_pdfweight_Do);
	histObs[29+5*fNBObHists]->Fill(sjhadAF.Pt(), ele_wt*_pdfweight_Do);

	histObs[30+5*fNBObHists]->Fill(bjlepAF.Eta(), ele_wt*_pdfweight_Do);
	histObs[30+5*fNBObHists]->Fill(bjhadAF.Eta(), ele_wt*_pdfweight_Do);
	histObs[30+5*fNBObHists]->Fill(cjhadAF.Eta(), ele_wt*_pdfweight_Do);
	histObs[30+5*fNBObHists]->Fill(sjhadAF.Eta(), ele_wt*_pdfweight_Do);

	histObs[31+5*fNBObHists]->Fill(bjlepAF.Phi(), ele_wt*_pdfweight_Do);
	histObs[31+5*fNBObHists]->Fill(bjhadAF.Phi(), ele_wt*_pdfweight_Do);
	histObs[31+5*fNBObHists]->Fill(cjhadAF.Phi(), ele_wt*_pdfweight_Do);
	histObs[31+5*fNBObHists]->Fill(sjhadAF.Phi(), ele_wt*_pdfweight_Do);
    
	histObs[34+5*fNBObHists]->Fill(neutrinoAF.Pt(), ele_wt*_pdfweight_Do);
	histObs[35+5*fNBObHists]->Fill(neutrinoAF.Phi(), ele_wt*_pdfweight_Do);

	histObs[38+5*fNBObHists]->Fill(selector->Jets.size(), ele_wt*_pdfweight_Do);
	histObs[39+5*fNBObHists]->Fill(selector->bJets.size(), ele_wt*_pdfweight_Do);
  
	histObs[41+5*fNBObHists]->Fill((cjhadAF+sjhadAF).M(), ele_wt*_pdfweight_Do);
	histObs[43+5*fNBObHists]->Fill((cjhadBF+sjhadBF).M(), ele_wt*_pdfweight_Do);
	////////////////////////////////////////////

	////////////// q2up //////////////////////
	histObs[23+6*fNBObHists]->Fill(leptonAF.Pt(), ele_wt*_q2weight_Up);
	histObs[24+6*fNBObHists]->Fill(leptonAF.Eta(), ele_wt*_q2weight_Up);
	histObs[25+6*fNBObHists]->Fill(leptonAF.Phi(), ele_wt*_q2weight_Up);
  
	histObs[29+6*fNBObHists]->Fill(bjlepAF.Pt(), ele_wt*_q2weight_Up);
	histObs[29+6*fNBObHists]->Fill(bjhadAF.Pt(), ele_wt*_q2weight_Up);
	histObs[29+6*fNBObHists]->Fill(cjhadAF.Pt(), ele_wt*_q2weight_Up);
	histObs[29+6*fNBObHists]->Fill(sjhadAF.Pt(), ele_wt*_q2weight_Up);

	histObs[30+6*fNBObHists]->Fill(bjlepAF.Eta(), ele_wt*_q2weight_Up);
	histObs[30+6*fNBObHists]->Fill(bjhadAF.Eta(), ele_wt*_q2weight_Up);
	histObs[30+6*fNBObHists]->Fill(cjhadAF.Eta(), ele_wt*_q2weight_Up);
	histObs[30+6*fNBObHists]->Fill(sjhadAF.Eta(), ele_wt*_q2weight_Up);

	histObs[31+6*fNBObHists]->Fill(bjlepAF.Phi(), ele_wt*_q2weight_Up);
	histObs[31+6*fNBObHists]->Fill(bjhadAF.Phi(), ele_wt*_q2weight_Up);
	histObs[31+6*fNBObHists]->Fill(cjhadAF.Phi(), ele_wt*_q2weight_Up);
	histObs[31+6*fNBObHists]->Fill(sjhadAF.Phi(), ele_wt*_q2weight_Up);
    
	histObs[34+6*fNBObHists]->Fill(neutrinoAF.Pt(), ele_wt*_q2weight_Up);
	histObs[35+6*fNBObHists]->Fill(neutrinoAF.Phi(), ele_wt*_q2weight_Up);

	histObs[38+6*fNBObHists]->Fill(selector->Jets.size(), ele_wt*_q2weight_Up);
	histObs[39+6*fNBObHists]->Fill(selector->bJets.size(), ele_wt*_q2weight_Up);
  
	histObs[41+6*fNBObHists]->Fill((cjhadAF+sjhadAF).M(), ele_wt*_q2weight_Up);
	histObs[43+6*fNBObHists]->Fill((cjhadBF+sjhadBF).M(), ele_wt*_q2weight_Up);
	////////////////////////////////////////////

	////////////// q2down //////////////////////
	histObs[23+7*fNBObHists]->Fill(leptonAF.Pt(), ele_wt*_q2weight_Do);
	histObs[24+7*fNBObHists]->Fill(leptonAF.Eta(), ele_wt*_q2weight_Do);
	histObs[25+7*fNBObHists]->Fill(leptonAF.Phi(), ele_wt*_q2weight_Do);
  
	histObs[29+7*fNBObHists]->Fill(bjlepAF.Pt(), ele_wt*_q2weight_Do);
	histObs[29+7*fNBObHists]->Fill(bjhadAF.Pt(), ele_wt*_q2weight_Do);
	histObs[29+7*fNBObHists]->Fill(cjhadAF.Pt(), ele_wt*_q2weight_Do);
	histObs[29+7*fNBObHists]->Fill(sjhadAF.Pt(), ele_wt*_q2weight_Do);

	histObs[30+7*fNBObHists]->Fill(bjlepAF.Eta(), ele_wt*_q2weight_Do);
	histObs[30+7*fNBObHists]->Fill(bjhadAF.Eta(), ele_wt*_q2weight_Do);
	histObs[30+7*fNBObHists]->Fill(cjhadAF.Eta(), ele_wt*_q2weight_Do);
	histObs[30+7*fNBObHists]->Fill(sjhadAF.Eta(), ele_wt*_q2weight_Do);

	histObs[31+7*fNBObHists]->Fill(bjlepAF.Phi(), ele_wt*_q2weight_Do);
	histObs[31+7*fNBObHists]->Fill(bjhadAF.Phi(), ele_wt*_q2weight_Do);
	histObs[31+7*fNBObHists]->Fill(cjhadAF.Phi(), ele_wt*_q2weight_Do);
	histObs[31+7*fNBObHists]->Fill(sjhadAF.Phi(), ele_wt*_q2weight_Do);
    
	histObs[34+7*fNBObHists]->Fill(neutrinoAF.Pt(), ele_wt*_q2weight_Do);
	histObs[35+7*fNBObHists]->Fill(neutrinoAF.Phi(), ele_wt*_q2weight_Do);

	histObs[38+7*fNBObHists]->Fill(selector->Jets.size(), ele_wt*_q2weight_Do);
	histObs[39+7*fNBObHists]->Fill(selector->bJets.size(), ele_wt*_q2weight_Do);
  
	histObs[41+7*fNBObHists]->Fill((cjhadAF+sjhadAF).M(), ele_wt*_q2weight_Do);
	histObs[43+7*fNBObHists]->Fill((cjhadBF+sjhadBF).M(), ele_wt*_q2weight_Do);
	////////////////////////////////////////////

	////////////// fsrup //////////////////////
	histObs[23+8*fNBObHists]->Fill(leptonAF.Pt(), ele_wt*_FSRweight_Up);
	histObs[24+8*fNBObHists]->Fill(leptonAF.Eta(), ele_wt*_FSRweight_Up);
	histObs[25+8*fNBObHists]->Fill(leptonAF.Phi(), ele_wt*_FSRweight_Up);
  
	histObs[29+8*fNBObHists]->Fill(bjlepAF.Pt(), ele_wt*_FSRweight_Up);
	histObs[29+8*fNBObHists]->Fill(bjhadAF.Pt(), ele_wt*_FSRweight_Up);
	histObs[29+8*fNBObHists]->Fill(cjhadAF.Pt(), ele_wt*_FSRweight_Up);
	histObs[29+8*fNBObHists]->Fill(sjhadAF.Pt(), ele_wt*_FSRweight_Up);

	histObs[30+8*fNBObHists]->Fill(bjlepAF.Eta(), ele_wt*_FSRweight_Up);
	histObs[30+8*fNBObHists]->Fill(bjhadAF.Eta(), ele_wt*_FSRweight_Up);
	histObs[30+8*fNBObHists]->Fill(cjhadAF.Eta(), ele_wt*_FSRweight_Up);
	histObs[30+8*fNBObHists]->Fill(sjhadAF.Eta(), ele_wt*_FSRweight_Up);

	histObs[31+8*fNBObHists]->Fill(bjlepAF.Phi(), ele_wt*_FSRweight_Up);
	histObs[31+8*fNBObHists]->Fill(bjhadAF.Phi(), ele_wt*_FSRweight_Up);
	histObs[31+8*fNBObHists]->Fill(cjhadAF.Phi(), ele_wt*_FSRweight_Up);
	histObs[31+8*fNBObHists]->Fill(sjhadAF.Phi(), ele_wt*_FSRweight_Up);
    
	histObs[34+8*fNBObHists]->Fill(neutrinoAF.Pt(), ele_wt*_FSRweight_Up);
	histObs[35+8*fNBObHists]->Fill(neutrinoAF.Phi(), ele_wt*_FSRweight_Up);

	histObs[38+8*fNBObHists]->Fill(selector->Jets.size(), ele_wt*_FSRweight_Up);
	histObs[39+8*fNBObHists]->Fill(selector->bJets.size(), ele_wt*_FSRweight_Up);
  
	histObs[41+8*fNBObHists]->Fill((cjhadAF+sjhadAF).M(), ele_wt*_FSRweight_Up);
	histObs[43+8*fNBObHists]->Fill((cjhadBF+sjhadBF).M(), ele_wt*_FSRweight_Up);
	////////////////////////////////////////////

	////////////// fsrdown //////////////////////
	histObs[23+9*fNBObHists]->Fill(leptonAF.Pt(), ele_wt*_FSRweight_Do);
	histObs[24+9*fNBObHists]->Fill(leptonAF.Eta(), ele_wt*_FSRweight_Do);
	histObs[25+9*fNBObHists]->Fill(leptonAF.Phi(), ele_wt*_FSRweight_Do);
  
	histObs[29+9*fNBObHists]->Fill(bjlepAF.Pt(), ele_wt*_FSRweight_Do);
	histObs[29+9*fNBObHists]->Fill(bjhadAF.Pt(), ele_wt*_FSRweight_Do);
	histObs[29+9*fNBObHists]->Fill(cjhadAF.Pt(), ele_wt*_FSRweight_Do);
	histObs[29+9*fNBObHists]->Fill(sjhadAF.Pt(), ele_wt*_FSRweight_Do);

	histObs[30+9*fNBObHists]->Fill(bjlepAF.Eta(), ele_wt*_FSRweight_Do);
	histObs[30+9*fNBObHists]->Fill(bjhadAF.Eta(), ele_wt*_FSRweight_Do);
	histObs[30+9*fNBObHists]->Fill(cjhadAF.Eta(), ele_wt*_FSRweight_Do);
	histObs[30+9*fNBObHists]->Fill(sjhadAF.Eta(), ele_wt*_FSRweight_Do);

	histObs[31+9*fNBObHists]->Fill(bjlepAF.Phi(), ele_wt*_FSRweight_Do);
	histObs[31+9*fNBObHists]->Fill(bjhadAF.Phi(), ele_wt*_FSRweight_Do);
	histObs[31+9*fNBObHists]->Fill(cjhadAF.Phi(), ele_wt*_FSRweight_Do);
	histObs[31+9*fNBObHists]->Fill(sjhadAF.Phi(), ele_wt*_FSRweight_Do);
    
	histObs[34+9*fNBObHists]->Fill(neutrinoAF.Pt(), ele_wt*_FSRweight_Do);
	histObs[35+9*fNBObHists]->Fill(neutrinoAF.Phi(), ele_wt*_FSRweight_Do);

	histObs[38+9*fNBObHists]->Fill(selector->Jets.size(), ele_wt*_FSRweight_Do);
	histObs[39+9*fNBObHists]->Fill(selector->bJets.size(), ele_wt*_FSRweight_Do);
  
	histObs[41+9*fNBObHists]->Fill((cjhadAF+sjhadAF).M(), ele_wt*_FSRweight_Do);
	histObs[43+9*fNBObHists]->Fill((cjhadBF+sjhadBF).M(), ele_wt*_FSRweight_Do);
	////////////////////////////////////////////

	////////////// isrup //////////////////////
	histObs[23+10*fNBObHists]->Fill(leptonAF.Pt(), ele_wt*_ISRweight_Up);
	histObs[24+10*fNBObHists]->Fill(leptonAF.Eta(), ele_wt*_ISRweight_Up);
	histObs[25+10*fNBObHists]->Fill(leptonAF.Phi(), ele_wt*_ISRweight_Up);
  
	histObs[29+10*fNBObHists]->Fill(bjlepAF.Pt(), ele_wt*_ISRweight_Up);
	histObs[29+10*fNBObHists]->Fill(bjhadAF.Pt(), ele_wt*_ISRweight_Up);
	histObs[29+10*fNBObHists]->Fill(cjhadAF.Pt(), ele_wt*_ISRweight_Up);
	histObs[29+10*fNBObHists]->Fill(sjhadAF.Pt(), ele_wt*_ISRweight_Up);

	histObs[30+10*fNBObHists]->Fill(bjlepAF.Eta(), ele_wt*_ISRweight_Up);
	histObs[30+10*fNBObHists]->Fill(bjhadAF.Eta(), ele_wt*_ISRweight_Up);
	histObs[30+10*fNBObHists]->Fill(cjhadAF.Eta(), ele_wt*_ISRweight_Up);
	histObs[30+10*fNBObHists]->Fill(sjhadAF.Eta(), ele_wt*_ISRweight_Up);

	histObs[31+10*fNBObHists]->Fill(bjlepAF.Phi(), ele_wt*_ISRweight_Up);
	histObs[31+10*fNBObHists]->Fill(bjhadAF.Phi(), ele_wt*_ISRweight_Up);
	histObs[31+10*fNBObHists]->Fill(cjhadAF.Phi(), ele_wt*_ISRweight_Up);
	histObs[31+10*fNBObHists]->Fill(sjhadAF.Phi(), ele_wt*_ISRweight_Up);
    
	histObs[34+10*fNBObHists]->Fill(neutrinoAF.Pt(), ele_wt*_ISRweight_Up);
	histObs[35+10*fNBObHists]->Fill(neutrinoAF.Phi(), ele_wt*_ISRweight_Up);

	histObs[38+10*fNBObHists]->Fill(selector->Jets.size(), ele_wt*_ISRweight_Up);
	histObs[39+10*fNBObHists]->Fill(selector->bJets.size(), ele_wt*_ISRweight_Up);
  
	histObs[41+10*fNBObHists]->Fill((cjhadAF+sjhadAF).M(), ele_wt*_ISRweight_Up);
	histObs[43+10*fNBObHists]->Fill((cjhadBF+sjhadBF).M(), ele_wt*_ISRweight_Up);
	////////////////////////////////////////////

	////////////// isrdown //////////////////////
	histObs[23+11*fNBObHists]->Fill(leptonAF.Pt(), ele_wt*_ISRweight_Do);
	histObs[24+11*fNBObHists]->Fill(leptonAF.Eta(), ele_wt*_ISRweight_Do);
	histObs[25+11*fNBObHists]->Fill(leptonAF.Phi(), ele_wt*_ISRweight_Do);
  
	histObs[29+11*fNBObHists]->Fill(bjlepAF.Pt(), ele_wt*_ISRweight_Do);
	histObs[29+11*fNBObHists]->Fill(bjhadAF.Pt(), ele_wt*_ISRweight_Do);
	histObs[29+11*fNBObHists]->Fill(cjhadAF.Pt(), ele_wt*_ISRweight_Do);
	histObs[29+11*fNBObHists]->Fill(sjhadAF.Pt(), ele_wt*_ISRweight_Do);

	histObs[30+11*fNBObHists]->Fill(bjlepAF.Eta(), ele_wt*_ISRweight_Do);
	histObs[30+11*fNBObHists]->Fill(bjhadAF.Eta(), ele_wt*_ISRweight_Do);
	histObs[30+11*fNBObHists]->Fill(cjhadAF.Eta(), ele_wt*_ISRweight_Do);
	histObs[30+11*fNBObHists]->Fill(sjhadAF.Eta(), ele_wt*_ISRweight_Do);

	histObs[31+11*fNBObHists]->Fill(bjlepAF.Phi(), ele_wt*_ISRweight_Do);
	histObs[31+11*fNBObHists]->Fill(bjhadAF.Phi(), ele_wt*_ISRweight_Do);
	histObs[31+11*fNBObHists]->Fill(cjhadAF.Phi(), ele_wt*_ISRweight_Do);
	histObs[31+11*fNBObHists]->Fill(sjhadAF.Phi(), ele_wt*_ISRweight_Do);
    
	histObs[34+11*fNBObHists]->Fill(neutrinoAF.Pt(), ele_wt*_ISRweight_Do);
	histObs[35+11*fNBObHists]->Fill(neutrinoAF.Phi(), ele_wt*_ISRweight_Do);

	histObs[38+11*fNBObHists]->Fill(selector->Jets.size(), ele_wt*_ISRweight_Do);
	histObs[39+11*fNBObHists]->Fill(selector->bJets.size(), ele_wt*_ISRweight_Do);
  
	histObs[41+11*fNBObHists]->Fill((cjhadAF+sjhadAF).M(), ele_wt*_ISRweight_Do);
	histObs[43+11*fNBObHists]->Fill((cjhadBF+sjhadBF).M(), ele_wt*_ISRweight_Do);
	////////////////////////////////////////////

      }else{
	hCutFlow[3+fNBCFHists]->Fill(6.0);
	hCutFlow[4+fNBCFHists]->Fill(6.0, ele_wt);
	histObs[23+fNBObHists]->Fill(leptonAF.Pt(), ele_wt);
	histObs[24+fNBObHists]->Fill(leptonAF.Eta(), ele_wt);
	histObs[25+fNBObHists]->Fill(leptonAF.Phi(), ele_wt);

	histObs[29+fNBObHists]->Fill(bjlepAF.Pt(), ele_wt);
	histObs[29+fNBObHists]->Fill(bjhadAF.Pt(), ele_wt);
	histObs[29+fNBObHists]->Fill(cjhadAF.Pt(), ele_wt);
	histObs[29+fNBObHists]->Fill(sjhadAF.Pt(), ele_wt);

	histObs[30+fNBObHists]->Fill(bjlepAF.Eta(), ele_wt);
	histObs[30+fNBObHists]->Fill(bjhadAF.Eta(), ele_wt);
	histObs[30+fNBObHists]->Fill(cjhadAF.Eta(), ele_wt);
	histObs[30+fNBObHists]->Fill(sjhadAF.Eta(), ele_wt);

	histObs[31+fNBObHists]->Fill(bjlepAF.Phi(), ele_wt);
	histObs[31+fNBObHists]->Fill(bjhadAF.Phi(), ele_wt);
	histObs[31+fNBObHists]->Fill(cjhadAF.Phi(), ele_wt);
	histObs[31+fNBObHists]->Fill(sjhadAF.Phi(), ele_wt);

	histObs[34+fNBObHists]->Fill(neutrinoAF.Pt(), ele_wt);
	histObs[35+fNBObHists]->Fill(neutrinoAF.Phi(), ele_wt);

	histObs[38+fNBObHists]->Fill(selector->Jets.size(), ele_wt);
	histObs[39+fNBObHists]->Fill(selector->bJets.size(), ele_wt);    

	histObs[41+fNBObHists]->Fill((cjhadAF+sjhadAF).M(), ele_wt);
	histObs[43+fNBObHists]->Fill((cjhadBF+sjhadBF).M(), ele_wt);
      }
    }

    if(ProcessKinFit(false, (singleEle and eleNonIsoCut))){
      if(!isLowMET){
	hCutFlow[3+2*fNBCFHists]->Fill(6.0);
	hCutFlow[4+2*fNBCFHists]->Fill(6.0, ele_wt);
	histObs[23+2*fNBObHists]->Fill(leptonAF.Pt(), ele_wt);
	histObs[24+2*fNBObHists]->Fill(leptonAF.Eta(), ele_wt);
	histObs[25+2*fNBObHists]->Fill(leptonAF.Phi(), ele_wt);

	histObs[29+2*fNBObHists]->Fill(bjlepAF.Pt(), ele_wt);
	histObs[29+2*fNBObHists]->Fill(bjhadAF.Pt(), ele_wt);
	histObs[29+2*fNBObHists]->Fill(cjhadAF.Pt(), ele_wt);
	histObs[29+2*fNBObHists]->Fill(sjhadAF.Pt(), ele_wt);

	histObs[30+2*fNBObHists]->Fill(bjlepAF.Eta(), ele_wt);
	histObs[30+2*fNBObHists]->Fill(bjhadAF.Eta(), ele_wt);
	histObs[30+2*fNBObHists]->Fill(cjhadAF.Eta(), ele_wt);
	histObs[30+2*fNBObHists]->Fill(sjhadAF.Eta(), ele_wt);

	histObs[31+2*fNBObHists]->Fill(bjlepAF.Phi(), ele_wt);
	histObs[31+2*fNBObHists]->Fill(bjhadAF.Phi(), ele_wt);
	histObs[31+2*fNBObHists]->Fill(cjhadAF.Phi(), ele_wt);
	histObs[31+2*fNBObHists]->Fill(sjhadAF.Phi(), ele_wt);

	histObs[34+2*fNBObHists]->Fill(neutrinoAF.Pt(), ele_wt);
	histObs[35+2*fNBObHists]->Fill(neutrinoAF.Phi(), ele_wt);

	histObs[38+2*fNBObHists]->Fill(selector->Jets.size(), ele_wt);
	histObs[39+2*fNBObHists]->Fill(selector->bJets.size(), ele_wt);    

	histObs[41+2*fNBObHists]->Fill((cjhadAF+sjhadAF).M(), ele_wt);
	histObs[43+2*fNBObHists]->Fill((cjhadBF+sjhadBF).M(), ele_wt);
      }else{
	hCutFlow[3+3*fNBCFHists]->Fill(6.0);
	hCutFlow[4+3*fNBCFHists]->Fill(6.0, ele_wt);
	histObs[23+3*fNBObHists]->Fill(leptonAF.Pt(), ele_wt);
	histObs[24+3*fNBObHists]->Fill(leptonAF.Eta(), ele_wt);
	histObs[25+3*fNBObHists]->Fill(leptonAF.Phi(), ele_wt);

	histObs[29+3*fNBObHists]->Fill(bjlepAF.Pt(), ele_wt);
	histObs[29+3*fNBObHists]->Fill(bjhadAF.Pt(), ele_wt);
	histObs[29+3*fNBObHists]->Fill(cjhadAF.Pt(), ele_wt);
	histObs[29+3*fNBObHists]->Fill(sjhadAF.Pt(), ele_wt);

	histObs[30+3*fNBObHists]->Fill(bjlepAF.Eta(), ele_wt);
	histObs[30+3*fNBObHists]->Fill(bjhadAF.Eta(), ele_wt);
	histObs[30+3*fNBObHists]->Fill(cjhadAF.Eta(), ele_wt);
	histObs[30+3*fNBObHists]->Fill(sjhadAF.Eta(), ele_wt);

	histObs[31+3*fNBObHists]->Fill(bjlepAF.Phi(), ele_wt);
	histObs[31+3*fNBObHists]->Fill(bjhadAF.Phi(), ele_wt);
	histObs[31+3*fNBObHists]->Fill(cjhadAF.Phi(), ele_wt);
	histObs[31+3*fNBObHists]->Fill(sjhadAF.Phi(), ele_wt);

	histObs[34+3*fNBObHists]->Fill(neutrinoAF.Pt(), ele_wt);
	histObs[35+3*fNBObHists]->Fill(neutrinoAF.Phi(), ele_wt);

	histObs[38+3*fNBObHists]->Fill(selector->Jets.size(), ele_wt);
	histObs[39+3*fNBObHists]->Fill(selector->bJets.size(), ele_wt);    

	histObs[41+3*fNBObHists]->Fill((cjhadAF+sjhadAF).M(), ele_wt);
	histObs[43+3*fNBObHists]->Fill((cjhadBF+sjhadBF).M(), ele_wt);
      }
    }
  }else{

    if(ProcessKinFit((singleMu and muonIsoCut), false) and !isLowMET){
      hCutFlow[1]->Fill(6.0);
      hCutFlow[2]->Fill(6.0, mu_wt);
      hCutFlow[5]->Fill(6.0, _sampleWeight*_PUWeight*_muEffWeight*_bTagWeight*_topPtReWeight);
      histObs[20]->Fill(leptonAF.Pt(), mu_wt);
      histObs[21]->Fill(leptonAF.Eta(), mu_wt);
      histObs[22]->Fill(leptonAF.Phi(), mu_wt);
  
      histObs[26]->Fill(bjlepAF.Pt(), mu_wt);
      histObs[26]->Fill(bjhadAF.Pt(), mu_wt);
      histObs[26]->Fill(cjhadAF.Pt(), mu_wt);
      histObs[26]->Fill(sjhadAF.Pt(), mu_wt);

      histObs[27]->Fill(bjlepAF.Eta(), mu_wt);
      histObs[27]->Fill(bjhadAF.Eta(), mu_wt);
      histObs[27]->Fill(cjhadAF.Eta(), mu_wt);
      histObs[27]->Fill(sjhadAF.Eta(), mu_wt);

      histObs[28]->Fill(bjlepAF.Phi(), mu_wt);
      histObs[28]->Fill(bjhadAF.Phi(), mu_wt);
      histObs[28]->Fill(cjhadAF.Phi(), mu_wt);
      histObs[28]->Fill(sjhadAF.Phi(), mu_wt);
    
      histObs[32]->Fill(neutrinoAF.Pt(), mu_wt);
      histObs[33]->Fill(neutrinoAF.Phi(), mu_wt);

      histObs[36]->Fill(selector->Jets.size(), mu_wt);
      histObs[37]->Fill(selector->bJets.size(), mu_wt);
  
      histObs[40]->Fill((cjhadAF+sjhadAF).M(), mu_wt);
      histObs[42]->Fill((cjhadBF+sjhadBF).M(), mu_wt);
    }
  
    if(ProcessKinFit(false, (singleEle and eleIsoCut)) and !isLowMET){
    
      hCutFlow[3]->Fill(6.0);
      hCutFlow[4]->Fill(6.0, ele_wt);
      histObs[23]->Fill(leptonAF.Pt(), ele_wt);
      histObs[24]->Fill(leptonAF.Eta(), ele_wt);
      histObs[25]->Fill(leptonAF.Phi(), ele_wt);

      histObs[29]->Fill(bjlepAF.Pt(), ele_wt);
      histObs[29]->Fill(bjhadAF.Pt(), ele_wt);
      histObs[29]->Fill(cjhadAF.Pt(), ele_wt);
      histObs[29]->Fill(sjhadAF.Pt(), ele_wt);

      histObs[30]->Fill(bjlepAF.Eta(), ele_wt);
      histObs[30]->Fill(bjhadAF.Eta(), ele_wt);
      histObs[30]->Fill(cjhadAF.Eta(), ele_wt);
      histObs[30]->Fill(sjhadAF.Eta(), ele_wt);

      histObs[31]->Fill(bjlepAF.Phi(), ele_wt);
      histObs[31]->Fill(bjhadAF.Phi(), ele_wt);
      histObs[31]->Fill(cjhadAF.Phi(), ele_wt);
      histObs[31]->Fill(sjhadAF.Phi(), ele_wt);

      histObs[34]->Fill(neutrinoAF.Pt(), ele_wt);
      histObs[35]->Fill(neutrinoAF.Phi(), ele_wt);

      histObs[38]->Fill(selector->Jets.size(), ele_wt);
      histObs[39]->Fill(selector->bJets.size(), ele_wt);    

      histObs[41]->Fill((cjhadAF+sjhadAF).M(), ele_wt);
      histObs[43]->Fill((cjhadBF+sjhadBF).M(), ele_wt);
    }
  }  

  // if(fProcessed%mod_num==0)
  //   Info("Process","Level 8");

  return kTRUE;
}

// //_____________________________________________________________________________
// Bool_t SkimAna::Process(Long64_t entry)
// {
//   // entry is the entry number in the current Tree
  
//   // to read complete event, call fChain->GetTree()->GetEntry(entry)
//   // if(fMode.Contains("proof"))
//   //   fChain->GetTree()->GetEntry(entry);  
//   // else
//   //   fChain->GetEntry(fProcessed);  
  
//   fChain->GetTree()->GetEntry(entry);  
//   //fChain->GetEntry(entry);
  
//   //    fChain->GetEntry(fProcessed);  

//   fProcessed++;
//   fStatus++;
  
//   // OldMethod();

//   _sampleWeight	 = 1.0;
//   _prefireWeight = 1.0;
//   _PUWeight	 = 1.0;
//   _muEffWeight	 = 1.0;
//   _eleEffWeight	 = 1.0;
//   _bTagWeight	 = 1.0;
//   _topPtReWeight = 1.0;

//   int mod_num = 10000;

//   if(fProcessed%mod_num==0){
//     Info("Process","Processing : %lld(%lld) of number of events : %lld and total number of events : %.0lf, year : %s", 
// 	 fProcessed, entry, fChain->GetEntries(), totEventsUS[fSampleType.Data()],evtPick->year.c_str());
//   }
  
  
//   // Set JEC syst
//   if( !isData and (systType == kJECUp or systType == kJECDown)){
//     jecvar->applyJEC(event, jecvar012_g); // 0:down, 1:norm, 2:up
//   }
  
//   // //Clear selector vectors
//   selector->clear_vectors();
  
//   // if(fProcessed%mod_num==0)
//   //   Info("Process","Level 0");
  
//   // This is main method to process the objects read from tree
//   evtPick->process_event(fBasePath.Data(), event, selector, 1.0); // here last argument 1.0 is weight applied to cutflow

//   //Special case of Wjets and DY
//   //if(!isNanoAOD and !isData and fSampleType.Contains("Wjets")){
//   if(!isData and fSampleType.Contains("Wjets")){
//     _local_evtWeight = ScaleLumiW(event->nLHEPart_) * luminosity/1000.;
//     if(fProcessed%100000==0)
//       Info("Process", "Wjets : Updated special event weight : %lf for nLHEPart_ : %d", _local_evtWeight, event->nLHEPart_);
//   }
  
//   if(!isData and fSampleType.Contains("DYjetsM50")){
//     _local_evtWeight = ScaleLumiZ(event->nLHEPart_) * luminosity/1000.;
//     if(fProcessed%100000==0)
//       Info("Notify", "DYjets : Updated special event weight : %lf for nLHEPart_ : %d", _local_evtWeight, event->nLHEPart_);
//   }

//   // if(fProcessed%mod_num==0)
//   //   Info("Process","Level 1");
 

//   // Sample weight 
//   if(!isData)
//     _sampleWeight = _local_evtWeight * ((event->genWeight_ >= 0) ? 1.0 : -1.0) ; //_sampleWeight should mimic the MiniAOD

//   // Access the prefire weight
//   if(!isData){
//     switch (systType) {
//     case kPreFireUp:
//       _prefireWeight = event->L1PreFiringWeight_Up_ ;
//       break;
//     case kPreFireDown:
//       _prefireWeight = event->L1PreFiringWeight_Dn_ ;
//       break;
//     default:
//       _prefireWeight = event->L1PreFiringWeight_Nom_ ;
//       break;
//     }  
//   }

//   // Access the PU weight
//   if(!isData){
//     _PUWeight = PUweighter->getWeight(event->nPUTrue_);
//   }
  
//   // if(fProcessed%mod_num==0)
//   //   Info("Process","Level 2");

//   histWt[0]->Fill(_sampleWeight);
//   histWt[1]->Fill(_PUWeight);
//   histWt[2]->Fill(_prefireWeight);
//   //Event level or trigger level conditions will be placed in block below
//   ////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   //hCutFlow[1]->Fill(_PUWeight); //filled later;
  
//   if(evtPick->passTrigger_mu || evtPick->passTrigger_ele)
//     hCutFlow[0]->Fill(0.0);
//   if((evtPick->passTrigger_mu || evtPick->passTrigger_ele) && selector->isPVGood && evtPick->passFilter)
//     hCutFlow[0]->Fill(1.0);
  
//   if(evtPick->passTrigger_mu){
//     hCutFlow[1]->Fill(0.0);
//     hCutFlow[2]->Fill(0.0, _sampleWeight*_prefireWeight*_PUWeight);
//     hCutFlow[5]->Fill(0.0, _sampleWeight*_PUWeight);
//   }
  
//   if(evtPick->passTrigger_mu and selector->isPVGood and evtPick->passFilter){
//     hCutFlow[1]->Fill(1.0);
//     hCutFlow[2]->Fill(1.0, _sampleWeight*_prefireWeight*_PUWeight);
//     hCutFlow[5]->Fill(1.0, _sampleWeight*_PUWeight);
//   }
  
//   //elec
//   if(evtPick->passTrigger_ele){
//     hCutFlow[3]->Fill(0.0);
//     hCutFlow[4]->Fill(0.0, _sampleWeight*_prefireWeight*_PUWeight);
//   }

//   if(evtPick->passTrigger_ele and selector->isPVGood and evtPick->passFilter){
//     hCutFlow[3]->Fill(1.0);
//     hCutFlow[4]->Fill(1.0, _sampleWeight*_prefireWeight*_PUWeight);
//   }
  
  
//   ////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
//   // if(fProcessed%mod_num==0)
//   //   Info("Process","Level 3");

//   bool singleMu = (evtPick->passFilter and selector->isPVGood and evtPick->passTrigger_mu and selector->Electrons.size() == 0 and selector->ElectronsLoose.size() == 0 and selector->Muons.size() == 1 and selector->MuonsLoose.size() == 0);
//   bool singleEle = (evtPick->passFilter and selector->isPVGood and evtPick->passTrigger_ele and selector->Electrons.size() == 1 and selector->ElectronsLoose.size() == 0 and selector->Muons.size() == 0 and selector->MuonsLoose.size() == 0);
//   //////=====================================================
//   if(!singleMu and !singleEle) return true;
//   //////=====================================================

//   // if(fProcessed%mod_num==0)
//   //   Info("Process","Level 4");

//   //Processes after single muon/electron selection will be placed in block below
//   ////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   if(!isData){
//     if(singleMu) GetMuonEff(event->muPFRelIso_[selector->Muons.at(0)]);
//     if(singleEle) GetElectronEff();
//   }
  
//   histWt[3]->Fill(_muEffWeight);
//   histWt[4]->Fill(_eleEffWeight);

//   bool muonIsoCut = false;
//   if(singleMu)
//     muonIsoCut = (event->muPFRelIso_[selector->Muons.at(0)] < 0.15) ? true : false; 
  
//   bool eleIsoCut = false;
//   if(singleEle)
//     eleIsoCut =  (
//   		  (TMath::Abs(event->eleEta_[selector->Electrons.at(0)]) <= 1.479 and event->elePFRelIso_[selector->Electrons.at(0)] < 0.0695) 
//   		  or 
//   		  (TMath::Abs(event->eleEta_[selector->Electrons.at(0)]) > 1.479 and  event->elePFRelIso_[selector->Electrons.at(0)] < 0.0821)
//   		  ) ? true : false;

//   if((singleMu and muonIsoCut) or (singleEle and eleIsoCut))
//     hCutFlow[0]->Fill(2.0);
  
//   if(singleMu and muonIsoCut){
//     hCutFlow[1]->Fill(2.0);
//     hCutFlow[2]->Fill(2.0, _sampleWeight*_prefireWeight*_PUWeight*_muEffWeight);
//     hCutFlow[5]->Fill(2.0, _sampleWeight*_PUWeight*_muEffWeight);
//   }
  
//   //elec
//   if(singleEle and eleIsoCut){
//     hCutFlow[3]->Fill(2.0);
//     hCutFlow[4]->Fill(2.0, _sampleWeight*_prefireWeight*_PUWeight*_eleEffWeight);
//   }
  
//   ////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
//   //////=====================================================
//   if(selector->Jets.size() < 4 ) return true;
//   //////=====================================================

//   // if(fProcessed%mod_num==0)
//   //   Info("Process","Level 5");

//   //Processes after njet >= 4 selection will be placed in block below
//   ////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
//   if((singleMu and muonIsoCut) or (singleEle and eleIsoCut))
//     hCutFlow[0]->Fill(3.0);
  
//   if(singleMu and muonIsoCut){
//     hCutFlow[1]->Fill(3.0);
//     hCutFlow[2]->Fill(3.0, _sampleWeight*_prefireWeight*_PUWeight*_muEffWeight);
//     hCutFlow[5]->Fill(3.0, _sampleWeight*_PUWeight*_muEffWeight);
//   }
  
//   //elec
//   if(singleEle and eleIsoCut){
//     hCutFlow[3]->Fill(3.0);
//     hCutFlow[4]->Fill(3.0, _sampleWeight*_prefireWeight*_PUWeight*_eleEffWeight);
//   }
//   ////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
//   METThreshold = 20. ;
//   //////=====================================================
//   if(selector->METPt < METThreshold ) return true;
//   //////=====================================================

//   // if(fProcessed%mod_num==0)
//   //   Info("Process","Level 6");

//   //Processes after MET selection will be placed in block below
//   ////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   if((singleMu and muonIsoCut) or (singleEle and eleIsoCut))
//     hCutFlow[0]->Fill(4.0);
  
//   if(singleMu and muonIsoCut){
//     hCutFlow[1]->Fill(4.0);
//     hCutFlow[2]->Fill(4.0, _sampleWeight*_prefireWeight*_PUWeight*_muEffWeight);
//     hCutFlow[5]->Fill(4.0, _sampleWeight*_PUWeight*_muEffWeight);
//   }
  
//   //elec
//   if(singleEle and eleIsoCut){
//     hCutFlow[3]->Fill(4.0);
//     hCutFlow[4]->Fill(4.0, _sampleWeight*_prefireWeight*_PUWeight*_eleEffWeight);
//   }
//   ////////////////////////////////////////////////////////////////////////////////////////////////////////////

//   //////=====================================================
//   if(selector->bJets.size() < 2 ) return true;
//   //////=====================================================
  
//   // if(fProcessed%mod_num==0)
//   //   Info("Process","Level 7");

//   //Processes after nbjet >= 2 selection will be placed in block below
//   ////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   if(!isData){
//     GetBtagSF_1a();
//     //_topPtReWeight = topPtReweight();
//     _topPtReWeight = 1.0;
//   }
//   switch (systType) {
//   case kBTagbDown:
//     histWt[6]->Fill(_bTagWeight);
//     break;      
//   case kBTagbUp:
//     histWt[7]->Fill(_bTagWeight);
//     break;
//   case kBTaglDown:
//     histWt[8]->Fill(_bTagWeight);
//     break;
//   case kBTaglUp:
//     histWt[9]->Fill(_bTagWeight);
//     break;
//   default:
//     histObs[5]->Fill(_bTagWeight);
//     break;
//   }
//   histWt[24]->Fill(_topPtReWeight);
  
//   double mu_wt = _sampleWeight*_prefireWeight*_PUWeight*_muEffWeight*_bTagWeight*_topPtReWeight ;
//   double ele_wt = _sampleWeight*_prefireWeight*_PUWeight*_eleEffWeight*_bTagWeight*_topPtReWeight ;
  
//   if((singleMu and muonIsoCut) or (singleEle and eleIsoCut))
//     hCutFlow[0]->Fill(5.0);
  
//   if(singleMu and muonIsoCut){
//     hCutFlow[1]->Fill(5.0);
//     hCutFlow[2]->Fill(5.0, mu_wt);
//     hCutFlow[5]->Fill(5.0, _sampleWeight*_PUWeight*_muEffWeight*_bTagWeight*_topPtReWeight);
//     histObs[0]->Fill(event->muPt_[selector->Muons.at(0)] * event->muRoccoR_[selector->Muons.at(0)], mu_wt);
//     histObs[1]->Fill(event->muEta_[selector->Muons.at(0)], mu_wt);
//     histObs[2]->Fill(event->muPhi_[selector->Muons.at(0)], mu_wt);
//     for(unsigned int ijet = 0; ijet < selector->Jets.size(); ijet++){
//       int jetInd = selector->Jets.at(ijet);
//       histObs[6]->Fill(selector->JetsPtSmeared.at(ijet), mu_wt);
//       histObs[7]->Fill(event->jetEta_[jetInd], mu_wt);
//       histObs[8]->Fill(event->jetPhi_[jetInd], mu_wt);
//     }
//     histObs[12]->Fill(selector->METPt, mu_wt);
//     histObs[13]->Fill(selector->METPhi, mu_wt);
//     histObs[16]->Fill(selector->Jets.size(), mu_wt);
//     histObs[17]->Fill(selector->bJets.size(), mu_wt);
//   }
  
//   //elec
//   if(singleEle and eleIsoCut){
//     hCutFlow[3]->Fill(5.0);
//     hCutFlow[4]->Fill(5.0, ele_wt);
//     histObs[3]->Fill(event->elePt_[selector->Electrons.at(0)], ele_wt);
//     histObs[4]->Fill(event->eleEta_[selector->Electrons.at(0)], ele_wt);
//     histObs[5]->Fill(event->elePhi_[selector->Electrons.at(0)], ele_wt);
//     for(unsigned int ijet = 0; ijet < selector->Jets.size(); ijet++){
//       int jetInd = selector->Jets.at(ijet);
//       histObs[9]->Fill(selector->JetsPtSmeared.at(ijet), ele_wt);
//       histObs[10]->Fill(event->jetEta_[jetInd], ele_wt);
//       histObs[11]->Fill(event->jetPhi_[jetInd], ele_wt);
//     }
//     histObs[14]->Fill(selector->METPt, ele_wt);
//     histObs[15]->Fill(selector->METPhi, ele_wt);
//     histObs[18]->Fill(selector->Jets.size(), ele_wt);
//     histObs[19]->Fill(selector->bJets.size(), ele_wt);
//   }


//   ////////////////////////////////////////////////////////////////////////////////////////////////////////////

  
//   if(ProcessKinFit((singleMu and muonIsoCut), false)){

//     hCutFlow[1]->Fill(6.0);
//     hCutFlow[2]->Fill(6.0, mu_wt);
//     hCutFlow[5]->Fill(6.0, _sampleWeight*_PUWeight*_muEffWeight*_bTagWeight*_topPtReWeight);
//     histObs[20]->Fill(leptonAF.Pt(), mu_wt);
//     histObs[21]->Fill(leptonAF.Eta(), mu_wt);
//     histObs[22]->Fill(leptonAF.Phi(), mu_wt);
  
//     histObs[26]->Fill(bjlepAF.Pt(), mu_wt);
//     histObs[26]->Fill(bjhadAF.Pt(), mu_wt);
//     histObs[26]->Fill(cjhadAF.Pt(), mu_wt);
//     histObs[26]->Fill(sjhadAF.Pt(), mu_wt);

//     histObs[27]->Fill(bjlepAF.Eta(), mu_wt);
//     histObs[27]->Fill(bjhadAF.Eta(), mu_wt);
//     histObs[27]->Fill(cjhadAF.Eta(), mu_wt);
//     histObs[27]->Fill(sjhadAF.Eta(), mu_wt);

//     histObs[28]->Fill(bjlepAF.Phi(), mu_wt);
//     histObs[28]->Fill(bjhadAF.Phi(), mu_wt);
//     histObs[28]->Fill(cjhadAF.Phi(), mu_wt);
//     histObs[28]->Fill(sjhadAF.Phi(), mu_wt);
    
//     histObs[32]->Fill(neutrinoAF.Pt(), mu_wt);
//     histObs[33]->Fill(neutrinoAF.Phi(), mu_wt);

//     histObs[36]->Fill(selector->Jets.size(), mu_wt);
//     histObs[37]->Fill(selector->bJets.size(), mu_wt);
  
//     histObs[40]->Fill((cjhadAF+sjhadAF).M(), mu_wt);
//     histObs[42]->Fill((cjhadBF+sjhadBF).M(), mu_wt);
//   }

//   if(ProcessKinFit(false, (singleEle and eleIsoCut))){
//     hCutFlow[3]->Fill(6.0);
//     hCutFlow[4]->Fill(6.0, ele_wt);
//     histObs[23]->Fill(leptonAF.Pt(), ele_wt);
//     histObs[24]->Fill(leptonAF.Eta(), ele_wt);
//     histObs[25]->Fill(leptonAF.Phi(), ele_wt);

//     histObs[29]->Fill(bjlepAF.Pt(), ele_wt);
//     histObs[29]->Fill(bjhadAF.Pt(), ele_wt);
//     histObs[29]->Fill(cjhadAF.Pt(), ele_wt);
//     histObs[29]->Fill(sjhadAF.Pt(), ele_wt);

//     histObs[30]->Fill(bjlepAF.Eta(), ele_wt);
//     histObs[30]->Fill(bjhadAF.Eta(), ele_wt);
//     histObs[30]->Fill(cjhadAF.Eta(), ele_wt);
//     histObs[30]->Fill(sjhadAF.Eta(), ele_wt);

//     histObs[31]->Fill(bjlepAF.Phi(), ele_wt);
//     histObs[31]->Fill(bjhadAF.Phi(), ele_wt);
//     histObs[31]->Fill(cjhadAF.Phi(), ele_wt);
//     histObs[31]->Fill(sjhadAF.Phi(), ele_wt);

//     histObs[34]->Fill(neutrinoAF.Pt(), ele_wt);
//     histObs[35]->Fill(neutrinoAF.Phi(), ele_wt);

//     histObs[38]->Fill(selector->Jets.size(), ele_wt);
//     histObs[39]->Fill(selector->bJets.size(), ele_wt);    

//     histObs[41]->Fill((cjhadAF+sjhadAF).M(), ele_wt);
//     histObs[43]->Fill((cjhadBF+sjhadBF).M(), ele_wt);
//   }
  
//   // if(fProcessed%mod_num==0)
//   //   Info("Process","Level 8");

//   return kTRUE;
// }
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
      if(iloop == 0 && x.chi2 >= 0.0 && x.chi2 < 20.){ // Only 1st min chi2
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
  _elePt->clear();
  _eleEta->clear();
  _elePhi->clear();
  _eleCharge->clear();
  
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
    
    // for(int icheck=0;icheck<fNHists;icheck++)
    //   hCheck[icheck]->Write();
    for(int icheck=0;icheck<fNCFHists;icheck++)
      hCutFlow[icheck]->Write();
    for(int icheck=0;icheck<fNWtHists;icheck++)
      histWt[icheck]->Write();
    for(int icheck=0;icheck<fNObHists;icheck++)
      histObs[icheck]->Write();
    
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
    outputTree->Write();
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
  //for(Long64_t ientry = 0 ; ientry < 1000 ; ientry++){
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

  TString op(Form("sample=%s|year=%s|input=%s|index=%s|syst=%s|aod=nano|run=prod",argv[1],argv[2],argv[3],argv[4],argv[5]));

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
  
  return true;
}
