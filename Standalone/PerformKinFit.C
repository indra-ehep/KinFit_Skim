/**********************************************************************
 Created on : 23/03/2021
 Purpose    : Analyse the Reco tree to create the syst histograms 
              (format adapted from h1analysis)
 Author     : Indranil Das, Visiting Fellow
 Email      : indranil.das@cern.ch | indra.ehep@gmail.com
**********************************************************************/

#include "PerformKinFit.h"
#include "TH2.h"
#include "TF1.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TPaveStats.h"
#include "TMath.h"
#include "TProof.h"

#include "TParticlePDG.h"
#include "TDatabasePDG.h"

//_____________________________________________________________________________
void PerformKinFit::GetArguments(){

  TString option = GetOption();
  //Info("GetArguments","ending PerformKinFit with process option: %s", option.Data());

  Ssiz_t from = 0;
  TString tok;
  // Now analyze the arguments
  while (option.Tokenize(tok , from , "|")) {
    if(tok.BeginsWith("sample"))
      fSample = ((TObjString *) (tok.Tokenize("="))->At(1))->GetString();
    if(tok.BeginsWith("year"))
      fYear = (((TObjString *) (tok.Tokenize("="))->At(1))->GetString()).Atoi();
    if(tok.BeginsWith("mode"))
      fMode = ((TObjString *) (tok.Tokenize("="))->At(1))->GetString();
    if(tok.BeginsWith("mtop"))
      fmTop = (((TObjString *) (tok.Tokenize("="))->At(1))->GetString()).Atof();
    if(tok.BeginsWith("chi2cut"))
      fchi2cut = (((TObjString *) (tok.Tokenize("="))->At(1))->GetString()).Atof();
    if(tok.BeginsWith("ptmin"))
      fptmin = (((TObjString *) (tok.Tokenize("="))->At(1))->GetString()).Atof();
    if(tok.BeginsWith("ptmax"))
      fptmax = (((TObjString *) (tok.Tokenize("="))->At(1))->GetString()).Atof();
  }
  
  if(fSample.BeginsWith("Data")){
    fSampleDir = "data_obs";
    isData = true;
  }else{
    fSampleDir = fSample;
    isData = false;
  }

}

//_____________________________________________________________________________
void PerformKinFit::Begin(TTree * /*tree*/)
{
   // This is needed when re-processing the object
   Reset();
   
   //print the option specified in the Process function.
   TString option = GetOption();
   Info("Begin", "starting PerformKinFit with process option: %s", option.Data());
   // Test tokenize
   
   if (fChain) fChain->SetEntryList(0);
   
}


void PerformKinFit::SlaveBegin(TTree *tree)
{
  //initialize the Tree branch addresses
  Init(tree);
  
  //print the option specified in the Process function.
  TString option = GetOption();
  Info("SlaveBegin",
       "starting PerformKinFit with process option: %s (tree: %p)", option.Data(), tree);

  GetArguments();
  Info("SlaveBegin",
       "sample : %s, year : %d, mode : %s", fSample.Data(), fYear, fMode.Data());
  float mTop = fmTop;
  
  const char *filename = Form("result_m%5.1f_chi2%03.0lf_pt%03.0lf-%03.0lf.root",mTop,fchi2cut,fptmin,fptmax);
  if(fMode.BeginsWith("proof")){
    fProofFile = new TProofOutputFile(filename, "M");
    fFile = fProofFile->OpenFile("RECREATE");
    if (fFile && fFile->IsZombie()) SafeDelete(fFile);
  }else{
    fFile = TFile::Open(filename,"RECREATE");
  }    
  // Cannot continue
  if (!fFile) {
    TString amsg = TString::Format("AnalyseReco::SlaveBegin: could not create '%s':"
				   " instance is invalid!", fFile->GetName());
    Abort(amsg, kAbortProcess);
    return;
  }
  
  outputTree = new TTree("Kinfit_Reco","Kinfit_Reco");
  outputTree->SetAutoSave();
  InitOutBranches();
  
  hMuPt = new TH1F("hMuPt","hMuPt",100,0,1000.0); 
  hMjj = new TH1F("hMjj","hMjj",80,0,400.0); 
  hMjjkF = new TH1F("hMjjkF",Form("hMjjkF with chi2cut : %5.2lf",fchi2cut),80,0,400.0); 
  hMjjkFsc = new TH1F("hMjjkFsc",Form("hMjjkFsc with chi2cut : %5.2lf",fchi2cut),80,0,400.0); 
  hMjjkF3s = new TH1F("hMjjkF3s",Form("hMjjkF3s with chi2cut : %5.2lf",fchi2cut),80,0,400.0); 

  hMjjkF_ms = new TH1F("hMjjkF_ms",Form("hMjjkF_ms : missing counts"),80,0,400.0); 
  hMjjkF_01 = new TH1F("hMjjkF_01",Form("hMjjkF_01 with E > 0 GeV"),80,0,400.0); 
  hMjjkF_02 = new TH1F("hMjjkF_02",Form("hMjjkF_02 with #chi^{2} < %5.2lf",fchi2cut),80,0,400.0); 
  hMjjkF_03 = new TH1F("hMjjkF_03",Form("hMjjkF_03 with p_{T}^{#mu} > 30 GeV/c"),80,0,400.0); 
  hMjjkF_04 = new TH1F("hMjjkF_04",Form("hMjjkF_04 with p_{T}^{bj} > 30 GeV/c"),80,0,400.0); 
  hMjjkF_05 = new TH1F("hMjjkF_05",Form("hMjjkF_05 with p_{T}^{bl} > 30 GeV/c"),80,0,400.0); 
  hMjjkF_06 = new TH1F("hMjjkF_06",Form("hMjjkF_06 with p_{T}^{sj1} > 30 GeV/c"),80,0,400.0); 
  hMjjkF_07 = new TH1F("hMjjkF_07",Form("hMjjkF_07 with p_{T}^{sj2} > 30 GeV/c"),80,0,400.0); 
  hMjjkF_08 = new TH1F("hMjjkF_08",Form("hMjjkF_08 with p_{T}^{MET} > 20 GeV/c"),80,0,400.0); 
  hMjjkF_09 = new TH1F("hMjjkF_09",Form("hMjjkF_09 with #DeltaR^{bj} < 0.2 "),80,0,400.0); 
  hMjjkF_10 = new TH1F("hMjjkF_10",Form("hMjjkF_10 with #DeltaR^{sj1} < 0.2 "),80,0,400.0); 
  hMjjkF_11 = new TH1F("hMjjkF_11",Form("hMjjkF_11 with #DeltaR^{sj2} < 0.2 "),80,0,400.0); 
  hMjjkF_12 = new TH1F("hMjjkF_12",Form("hMjjkF_12 with #DeltaR^{bl} < 0.2 "),80,0,400.0); 
  hMjjkF_13 = new TH1F("hMjjkF_13",Form("hMjjkF_13 with #DeltaR^{#mu} < 0.2 "),80,0,400.0); 
  hMjjkF_14 = new TH1F("hMjjkF_14",Form("hMjjkF_14 with p_{T} ratio cut of neutrino"),80,0,400.0); 
  hMjjkF_15 = new TH1F("hMjjkF_15",Form("hMjjkF_15 with p_{T} ratio cut of bjhadron"),80,0,400.0); 
  hMjjkF_16 = new TH1F("hMjjkF_16",Form("hMjjkF_16 with p_{T} ratio cut of soft jet 1"),80,0,400.0); 
  hMjjkF_17 = new TH1F("hMjjkF_17",Form("hMjjkF_17 with p_{T} ratio cut of soft jet 2"),80,0,400.0); 
  
  hNlep = new TH1F("hNlep","hNlep",200,-10.0,10.0); 
  hChi2 = new TH1F("hChi2","hChi2",500,0,100.0); 
  hMinChi2 = new TH1F("hMinChi2","1^{st} minimum",500,0,100.0); 
  h2MinChi2 = new TH1F("h2MinChi2","2^{nd} minimum",500,0,100.0); 
  h3MinChi2 = new TH1F("h3MinChi2","3^{rd} minimum",500,0,100.0); 
  h4MinChi2 = new TH1F("h4MinChi2","4^{th} minimum",500,0,100.0); 
  h5MinChi2 = new TH1F("h5MinChi2","5^{th} minimum",500,0,100.0); 
  hNbiter = new TH1F("hNbiter","hNbiter",500,0,500.0); 
  hNbCombiBRD = new TH1F("hNbCombiBRD","hNbCombiBRD", 500, 0.0, 500.0);
  hNbCombiARD = new TH1F("hNbCombiARD","hNbCombiARD", 500, 0.0, 500.0);
  hdRSigLep  = new TH1F("hdRSigLep","hdRSigLep",100, -1.0, 9.0);
  hdRSigNeu  = new TH1F("hdRSigNeu","hdRSigNeu",100, -1.0, 9.0);
  hdRSigBjHad  = new TH1F("hdRSigBjHad","hdRSigBjHad",100, -1.0, 9.0);
  hdRSigBjLep  = new TH1F("hdRSigBjLep","hdRSigBjLep",100, -1.0, 9.0);
  hdRSigCjHad = new TH1F("hdRSigCjHad","hdRSigCjHad",100, -1.0, 9.0);
  hdRSigSjHad = new TH1F("hdRSigSjHad","hdRSigSjhad",100, -1.0, 9.0);
  hMindRSigLep  = new TH1F("hMindRSigLep","hMindRSigLep",100, -1.0, 9.0);
  hMindRSigNeu  = new TH1F("hMindRSigNeu","hMindRSigNeu",100, -1.0, 9.0);
  hMindRSigBjHad  = new TH1F("hMindRSigBjHad","hMindRSigBjHad",100, -1.0, 9.0);
  hMindRSigBjLep  = new TH1F("hMindRSigBjLep","hMindRSigBjLep",100, -1.0, 9.0);
  hMindRSigCjHad = new TH1F("hMindRSigCjHad","hMindRSigCjHad",100, -1.0, 9.0);
  hMindRSigSjHad = new TH1F("hMindRSigSjHad","hMindRSigSjhad",100, -1.0, 9.0);
  
  hPtvsdEtLep  = new TH1F("hPtvsdEtLep",Form("hPtvsdEtLep for pt = (%5.2lf - %5.2lf) GeV/c",fptmin,fptmax),1000, 0.0, 100.0);
  hPtvsdEtBjHad  = new TH1F("hPtvsdEtBjHad",Form("hPtvsdEtBjHad for pt = (%5.2lf - %5.2lf) GeV/c",fptmin,fptmax),4000, 0.0, 400.0);
  hPtvsdEtBjLep  = new TH1F("hPtvsdEtBjLep",Form("hPtvsdEtBjLep for pt = (%5.2lf - %5.2lf) GeV/c",fptmin,fptmax),4000, 0.0, 400.0);
  hPtvsdEtCjHad = new TH1F("hPtvsdEtCjHad",Form("hPtvsdEtCjHad for pt = (%5.2lf - %5.2lf) GeV/c",fptmin,fptmax),4000, 0.0, 400.0);
  hPtvsdEtSjHad = new TH1F("hPtvsdEtSjHad",Form("hPtvsdEtSjhad for pt = (%5.2lf - %5.2lf) GeV/c",fptmin,fptmax),4000, 0.0, 400.0);
  
  hPtvsdetaLep  = new TH1F("hPtvsdetaLep",Form("hPtvsdetaLep for pt = (%5.2lf - %5.2lf) GeV/c",fptmin,fptmax),100, 0.0, 10.0);
  hPtvsdetaBjHad  = new TH1F("hPtvsdetaBjHad",Form("hPtvsdetaBjHad for pt = (%5.2lf - %5.2lf) GeV/c",fptmin,fptmax),100, 0.0, 10.0);
  hPtvsdetaBjLep  = new TH1F("hPtvsdetaBjLep",Form("hPtvsdetaBjLep for pt = (%5.2lf - %5.2lf) GeV/c",fptmin,fptmax),100, 0.0, 10.0);
  hPtvsdetaCjHad = new TH1F("hPtvsdetaCjHad",Form("hPtvsdetaCjHad for pt = (%5.2lf - %5.2lf) GeV/c",fptmin,fptmax),100, 0.0, 10.0);
  hPtvsdetaSjHad = new TH1F("hPtvsdetaSjHad",Form("hPtvsdetaSjhad for pt = (%5.2lf - %5.2lf) GeV/c",fptmin,fptmax),100, 0.0, 10.0);

  hMinPtvsdEtLep  = new TH1F("hMinPtvsdEtLep",Form("hMinPtvsdEtLep for pt = (%5.2lf - %5.2lf) GeV/c",fptmin,fptmax),1000, 0.0, 100.0);
  hMinPtvsdEtBjHad  = new TH1F("hMinPtvsdEtBjHad",Form("hMinPtvsdEtBjHad for pt = (%5.2lf - %5.2lf) GeV/c",fptmin,fptmax),4000, 0.0, 400.0);
  hMinPtvsdEtBjLep  = new TH1F("hMinPtvsdEtBjLep",Form("hMinPtvsdEtBjLep for pt = (%5.2lf - %5.2lf) GeV/c",fptmin,fptmax),4000, 0.0, 400.0);
  hMinPtvsdEtCjHad = new TH1F("hMinPtvsdEtCjHad",Form("hMinPtvsdEtCjHad for pt = (%5.2lf - %5.2lf) GeV/c",fptmin,fptmax),4000, 0.0, 400.0);
  hMinPtvsdEtSjHad = new TH1F("hMinPtvsdEtSjHad",Form("hMinPtvsdEtSjhad for pt = (%5.2lf - %5.2lf) GeV/c",fptmin,fptmax),4000, 0.0, 400.0);

  hMinPtvsdetaLep  = new TH1F("hMinPtvsdetaLep",Form("hMinPtvsdetaLep for pt = (%5.2lf - %5.2lf) GeV/c",fptmin,fptmax),100, 0.0, 10.0);
  hMinPtvsdetaBjHad  = new TH1F("hMinPtvsdetaBjHad",Form("hMinPtvsdetaBjHad for pt = (%5.2lf - %5.2lf) GeV/c",fptmin,fptmax),100, 0.0, 10.0);
  hMinPtvsdetaBjLep  = new TH1F("hMinPtvsdetaBjLep",Form("hMinPtvsdetaBjLep for pt = (%5.2lf - %5.2lf) GeV/c",fptmin,fptmax),100, 0.0, 10.0);
  hMinPtvsdetaCjHad = new TH1F("hMinPtvsdetaCjHad",Form("hMinPtvsdetaCjHad for pt = (%5.2lf - %5.2lf) GeV/c",fptmin,fptmax),100, 0.0, 10.0);
  hMinPtvsdetaSjHad = new TH1F("hMinPtvsdetaSjHad",Form("hMinPtvsdetaSjhad for pt = (%5.2lf - %5.2lf) GeV/c",fptmin,fptmax),100, 0.0, 10.0);
  
  hPtvsdPhiLep  = new TH1F("hPtvsdPhiLep",Form("hPtvsdPhiLep for pt = (%5.2lf - %5.2lf) GeV/c",fptmin,fptmax),800,-1.0,7.0);
  hPtvsdPhiBjHad  = new TH1F("hPtvsdPhiBjHad",Form("hPtvsdPhiBjHad for pt = (%5.2lf - %5.2lf) GeV/c",fptmin,fptmax),800,-1.0,7.0);
  hPtvsdPhiBjLep  = new TH1F("hPtvsdPhiBjLep",Form("hPtvsdPhiBjLep for pt = (%5.2lf - %5.2lf) GeV/c",fptmin,fptmax),800,-1.0,7.0);
  hPtvsdPhiCjHad = new TH1F("hPtvsdPhiCjHad",Form("hPtvsdPhiCjHad for pt = (%5.2lf - %5.2lf) GeV/c",fptmin,fptmax),800,-1.0,7.0);
  hPtvsdPhiSjHad = new TH1F("hPtvsdPhiSjHad",Form("hPtvsdPhiSjhad for pt = (%5.2lf - %5.2lf) GeV/c",fptmin,fptmax),800,-1.0,7.0);

  hMinPtvsdPhiLep  = new TH1F("hMinPtvsdPhiLep",Form("hMinPtvsdPhiLep for pt = (%5.2lf - %5.2lf) GeV/c",fptmin,fptmax),800,-1.0,7.0);
  hMinPtvsdPhiBjHad  = new TH1F("hMinPtvsdPhiBjHad",Form("hMinPtvsdPhiBjHad for pt = (%5.2lf - %5.2lf) GeV/c",fptmin,fptmax),800,-1.0,7.0);
  hMinPtvsdPhiBjLep  = new TH1F("hMinPtvsdPhiBjLep",Form("hMinPtvsdPhiBjLep for pt = (%5.2lf - %5.2lf) GeV/c",fptmin,fptmax),800,-1.0,7.0);
  hMinPtvsdPhiCjHad = new TH1F("hMinPtvsdPhiCjHad",Form("hMinPtvsdPhiCjHad for pt = (%5.2lf - %5.2lf) GeV/c",fptmin,fptmax),800,-1.0,7.0);
  hMinPtvsdPhiSjHad = new TH1F("hMinPtvsdPhiSjHad",Form("hMinPtvsdPhiSjhad for pt = (%5.2lf - %5.2lf) GeV/c",fptmin,fptmax),800,-1.0,7.0);  

  //0-40, 40-80, 80-130, 130-200, 200-300, >300
  fNPtBins = 7;
  // float ptmin[] = {00., 40.,  80., 130., 200., 300.};
  // float ptmax[] = {40., 80., 130., 200., 300., 10000.};
  float ptmin[] = {00., 30., 50.,  80., 130., 200., 300.};
  float ptmax[] = {30., 50., 80., 130., 200., 300., 10000.};
  fPtmin = new float[fNPtBins];
  fPtmax = new float[fNPtBins];
  
  hPtBFLep = new TH1F*[fNPtBins];//!
  hPtBFNeu = new TH1F*[fNPtBins];//!
  hPtBFBjHad  = new TH1F*[fNPtBins];//!
  hPtBFBjLep  = new TH1F*[fNPtBins];//!
  hPtBFCjHad = new TH1F*[fNPtBins];//!
  hPtBFSjHad = new TH1F*[fNPtBins];//!

  hPtAFLep = new TH1F*[fNPtBins];//!
  hPtAFNeu = new TH1F*[fNPtBins];//!
  hPtAFBjHad  = new TH1F*[fNPtBins];//!
  hPtAFBjLep  = new TH1F*[fNPtBins];//!
  hPtAFCjHad = new TH1F*[fNPtBins];//!
  hPtAFSjHad = new TH1F*[fNPtBins];//!

  hPtvsRatioPtLep = new TH1F*[fNPtBins];//!
  hPtvsRatioPtNeu = new TH1F*[fNPtBins];//!
  hPtvsRatioPtBjHad  = new TH1F*[fNPtBins];//!
  hPtvsRatioPtBjLep  = new TH1F*[fNPtBins];//!
  hPtvsRatioPtCjHad = new TH1F*[fNPtBins];//!
  hPtvsRatioPtSjHad = new TH1F*[fNPtBins];//!

  hMinPtBFLep = new TH1F*[fNPtBins];//!
  hMinPtBFNeu = new TH1F*[fNPtBins];//!
  hMinPtBFBjHad  = new TH1F*[fNPtBins];//!
  hMinPtBFBjLep  = new TH1F*[fNPtBins];//!
  hMinPtBFCjHad = new TH1F*[fNPtBins];//!
  hMinPtBFSjHad = new TH1F*[fNPtBins];//!

  hMinPtAFLep = new TH1F*[fNPtBins];//!
  hMinPtAFNeu = new TH1F*[fNPtBins];//!
  hMinPtAFBjHad  = new TH1F*[fNPtBins];//!
  hMinPtAFBjLep  = new TH1F*[fNPtBins];//!
  hMinPtAFCjHad = new TH1F*[fNPtBins];//!
  hMinPtAFSjHad = new TH1F*[fNPtBins];//!
  
  hMinPtvsRatioPtLep  = new TH1F*[fNPtBins];//!
  hMinPtvsRatioPtNeu  = new TH1F*[fNPtBins];//!
  hMinPtvsRatioPtBjHad  = new TH1F*[fNPtBins];//!
  hMinPtvsRatioPtBjLep  = new TH1F*[fNPtBins];//!
  hMinPtvsRatioPtCjHad = new TH1F*[fNPtBins];//!
  hMinPtvsRatioPtSjHad = new TH1F*[fNPtBins];//!
  
  for (int ipt = 0 ; ipt < fNPtBins ; ipt++ ){
    
    fPtmin[ipt] = ptmin[ipt];
    fPtmax[ipt] = ptmax[ipt];
    
    hPtBFLep[ipt]  = new TH1F(Form("hPtBFLep_%02d",ipt),Form("hPtBFLep for pt = (%5.2lf - %5.2lf) GeV/c",ptmin[ipt],ptmax[ipt]),2000,0.0,2000.0);
    hPtBFNeu[ipt]  = new TH1F(Form("hPtBFNeu_%02d",ipt),Form("hPtBFNeu for pt = (%5.2lf - %5.2lf) GeV/c",ptmin[ipt],ptmax[ipt]),2000,0.0,2000.0);
    hPtBFBjHad[ipt]  = new TH1F(Form("hPtBFBjHad_%02d",ipt),Form("hPtBFBjHad for pt = (%5.2lf - %5.2lf) GeV/c",ptmin[ipt],ptmax[ipt]),2000,0.0,2000.0);
    hPtBFBjLep[ipt]  = new TH1F(Form("hPtBFBjLep_%02d",ipt),Form("hPtBFBjLep for pt = (%5.2lf - %5.2lf) GeV/c",ptmin[ipt],ptmax[ipt]),2000,0.0,2000.0);
    hPtBFCjHad[ipt]  = new TH1F(Form("hPtBFCjHad_%02d",ipt),Form("hPtBFCjHad for pt = (%5.2lf - %5.2lf) GeV/c",ptmin[ipt],ptmax[ipt]),2000,0.0,2000.0);
    hPtBFSjHad[ipt]  = new TH1F(Form("hPtBFSjHad_%02d",ipt),Form("hPtBFSjhad for pt = (%5.2lf - %5.2lf) GeV/c",ptmin[ipt],ptmax[ipt]),2000,0.0,2000.0);
    
    hPtAFLep[ipt]  = new TH1F(Form("hPtAFLep_%02d",ipt),Form("hPtAFLep for pt = (%5.2lf - %5.2lf) GeV/c",ptmin[ipt],ptmax[ipt]),2000,0.0,2000.0);
    hPtAFNeu[ipt]  = new TH1F(Form("hPtAFNeu_%02d",ipt),Form("hPtAFNeu for pt = (%5.2lf - %5.2lf) GeV/c",ptmin[ipt],ptmax[ipt]),2000,0.0,2000.0);
    hPtAFBjHad[ipt]  = new TH1F(Form("hPtAFBjHad_%02d",ipt),Form("hPtAFBjHad for pt = (%5.2lf - %5.2lf) GeV/c",ptmin[ipt],ptmax[ipt]),2000,0.0,2000.0);
    hPtAFBjLep[ipt]  = new TH1F(Form("hPtAFBjLep_%02d",ipt),Form("hPtAFBjLep for pt = (%5.2lf - %5.2lf) GeV/c",ptmin[ipt],ptmax[ipt]),2000,0.0,2000.0);
    hPtAFCjHad[ipt]  = new TH1F(Form("hPtAFCjHad_%02d",ipt),Form("hPtAFCjHad for pt = (%5.2lf - %5.2lf) GeV/c",ptmin[ipt],ptmax[ipt]),2000,0.0,2000.0);
    hPtAFSjHad[ipt]  = new TH1F(Form("hPtAFSjHad_%02d",ipt),Form("hPtAFSjhad for pt = (%5.2lf - %5.2lf) GeV/c",ptmin[ipt],ptmax[ipt]),2000,0.0,2000.0);
    
    hPtvsRatioPtLep[ipt]  = new TH1F(Form("hPtvsRatioPtLep_%02d",ipt),Form("hPtvsRatioPtLep for pt = (%5.2lf - %5.2lf) GeV/c",ptmin[ipt],ptmax[ipt]),2000,0.0,5.0);
    hPtvsRatioPtNeu[ipt]  = new TH1F(Form("hPtvsRatioPtNeu_%02d",ipt),Form("hPtvsRatioPtNeu for pt = (%5.2lf - %5.2lf) GeV/c",ptmin[ipt],ptmax[ipt]),200,0.0,5.0);
    hPtvsRatioPtBjHad[ipt]  = new TH1F(Form("hPtvsRatioPtBjHad_%02d",ipt),Form("hPtvsRatioPtBjHad for pt = (%5.2lf - %5.2lf) GeV/c",ptmin[ipt],ptmax[ipt]),200,0.0,5.0);
    hPtvsRatioPtBjLep[ipt]  = new TH1F(Form("hPtvsRatioPtBjLep_%02d",ipt),Form("hPtvsRatioPtBjLep for pt = (%5.2lf - %5.2lf) GeV/c",ptmin[ipt],ptmax[ipt]),200,0.0,5.0);
    hPtvsRatioPtCjHad[ipt]  = new TH1F(Form("hPtvsRatioPtCjHad_%02d",ipt),Form("hPtvsRatioPtCjHad for pt = (%5.2lf - %5.2lf) GeV/c",ptmin[ipt],ptmax[ipt]),200,0.0,5.0);
    hPtvsRatioPtSjHad[ipt]  = new TH1F(Form("hPtvsRatioPtSjHad_%02d",ipt),Form("hPtvsRatioPtSjhad for pt = (%5.2lf - %5.2lf) GeV/c",ptmin[ipt],ptmax[ipt]),200,0.0,5.0);

    hMinPtBFLep[ipt]  = new TH1F(Form("hMinPtBFLep_%02d",ipt),Form("hMinPtBFLep for pt = (%5.2lf - %5.2lf) GeV/c",ptmin[ipt],ptmax[ipt]),2000,0.0,2000.0);
    hMinPtBFNeu[ipt]  = new TH1F(Form("hMinPtBFNeu_%02d",ipt),Form("hMinPtBFNeu for pt = (%5.2lf - %5.2lf) GeV/c",ptmin[ipt],ptmax[ipt]),2000,0.0,2000.0);
    hMinPtBFBjHad[ipt]  = new TH1F(Form("hMinPtBFBjHad_%02d",ipt),Form("hMinPtBFBjHad for pt = (%5.2lf - %5.2lf) GeV/c",ptmin[ipt],ptmax[ipt]),2000,0.0,2000.0);
    hMinPtBFBjLep[ipt]  = new TH1F(Form("hMinPtBFBjLep_%02d",ipt),Form("hMinPtBFBjLep for pt = (%5.2lf - %5.2lf) GeV/c",ptmin[ipt],ptmax[ipt]),2000,0.0,2000.0);
    hMinPtBFCjHad[ipt]  = new TH1F(Form("hMinPtBFCjHad_%02d",ipt),Form("hMinPtBFCjHad for pt = (%5.2lf - %5.2lf) GeV/c",ptmin[ipt],ptmax[ipt]),2000,0.0,2000.0);
    hMinPtBFSjHad[ipt]  = new TH1F(Form("hMinPtBFSjHad_%02d",ipt),Form("hMinPtBFSjhad for pt = (%5.2lf - %5.2lf) GeV/c",ptmin[ipt],ptmax[ipt]),2000,0.0,2000.0);
    
    hMinPtAFLep[ipt]  = new TH1F(Form("hMinPtAFLep_%02d",ipt),Form("hMinPtAFLep for pt = (%5.2lf - %5.2lf) GeV/c",ptmin[ipt],ptmax[ipt]),2000,0.0,2000.0);
    hMinPtAFNeu[ipt]  = new TH1F(Form("hMinPtAFNeu_%02d",ipt),Form("hMinPtAFNeu for pt = (%5.2lf - %5.2lf) GeV/c",ptmin[ipt],ptmax[ipt]),2000,0.0,2000.0);
    hMinPtAFBjHad[ipt]  = new TH1F(Form("hMinPtAFBjHad_%02d",ipt),Form("hMinPtAFBjHad for pt = (%5.2lf - %5.2lf) GeV/c",ptmin[ipt],ptmax[ipt]),2000,0.0,2000.0);
    hMinPtAFBjLep[ipt]  = new TH1F(Form("hMinPtAFBjLep_%02d",ipt),Form("hMinPtAFBjLep for pt = (%5.2lf - %5.2lf) GeV/c",ptmin[ipt],ptmax[ipt]),2000,0.0,2000.0);
    hMinPtAFCjHad[ipt]  = new TH1F(Form("hMinPtAFCjHad_%02d",ipt),Form("hMinPtAFCjHad for pt = (%5.2lf - %5.2lf) GeV/c",ptmin[ipt],ptmax[ipt]),2000,0.0,2000.0);
    hMinPtAFSjHad[ipt]  = new TH1F(Form("hMinPtAFSjHad_%02d",ipt),Form("hMinPtAFSjhad for pt = (%5.2lf - %5.2lf) GeV/c",ptmin[ipt],ptmax[ipt]),2000,0.0,2000.0);
    
    hMinPtvsRatioPtLep[ipt]  = new TH1F(Form("hMinPtvsRatioPtLep_%02d",ipt),Form("hMinPtvsRatioPtLep for pt = (%5.2lf - %5.2lf) GeV/c",ptmin[ipt],ptmax[ipt]),2000,0.0,5.0);
    hMinPtvsRatioPtNeu[ipt]  = new TH1F(Form("hMinPtvsRatioPtNeu_%02d",ipt),Form("hMinPtvsRatioPtNeu for pt = (%5.2lf - %5.2lf) GeV/c",ptmin[ipt],ptmax[ipt]),200,0.0,5.0);
    hMinPtvsRatioPtBjHad[ipt]  = new TH1F(Form("hMinPtvsRatioPtBjHad_%02d",ipt),Form("hMinPtvsRatioPtBjHad for pt = (%5.2lf - %5.2lf) GeV/c",ptmin[ipt],ptmax[ipt]),200,0.0,5.0);
    hMinPtvsRatioPtBjLep[ipt]  = new TH1F(Form("hMinPtvsRatioPtBjLep_%02d",ipt),Form("hMinPtvsRatioPtBjLep for pt = (%5.2lf - %5.2lf) GeV/c",ptmin[ipt],ptmax[ipt]),200,0.0,5.0);
    hMinPtvsRatioPtCjHad[ipt]  = new TH1F(Form("hMinPtvsRatioPtCjHad_%02d",ipt),Form("hMinPtvsRatioPtCjHad for pt = (%5.2lf - %5.2lf) GeV/c",ptmin[ipt],ptmax[ipt]),200,0.0,5.0);
    hMinPtvsRatioPtSjHad[ipt]  = new TH1F(Form("hMinPtvsRatioPtSjHad_%02d",ipt),Form("hMinPtvsRatioPtSjhad for pt = (%5.2lf - %5.2lf) GeV/c",ptmin[ipt],ptmax[ipt]),200,0.0,5.0);
    
  }

  hPtTopLep = new TH1F("hPtTopLep","hPtTopLep",1000,0.0,1000.0); 
  hPtTopHad = new TH1F("hPtTopHad","hPtTopHad",1000,0.0,1000.0); 
  hPtTopHL = new TH2F("hPtTopHL","hPtTopHL",1000,0.0,1000.0,1000,0,1000.0); 
  hAssymPt = new TH1F("hAssymPt","hAssymPt",2200,-1.1,1.1); 
  hNeuEta_Ptlow = new TH1F("hNeuEta_Ptlow","hNeuEta_Ptlow",600,-3.0,3.0); 
  hNeuEta_Pthigh = new TH1F("hNeuEta_Pthigh","hNeuEta_Pthigh",600,-3.0,3.0); 
  hMuEta_Ptlow = new TH1F("hMuEta_Ptlow","hMuEta_Ptlow",600,-3.0,3.0); 
  hMuEta_Pthigh = new TH1F("hMuEta_Pthigh","hMuEta_Pthigh",600,-3.0,3.0); 
  

  //hIsNeuComplex = new TH1F("hIsNeuComplex","hIsNeuComplex",30, -1.0, 2.0);
  //hMW = new TH1F("hMW","hMW",400,0,200.0); 
  hMW = new TH1F("hMW","hMW",2000,0,200.0); 
  hMW->GetXaxis()->SetTitle(Form("Mass (MeV/c^{2})"));
  hMW->GetYaxis()->SetTitle(Form("Counts per %2.0f MeV/c^{2}",1000.0*hMW->GetBinWidth(3)));
  
  hHadTop = new TH1F("hHadTop","hHadTop",2000,0,400.0); 
  hLepTop = new TH1F("hLepTop","hLepTop",2000,0,400.0); 
  hEtaNeu = new TH1F("hEtaNeu","hEtaNeu",100,-10,10.0); 

  //0-50, 50-100, 100-150, 150-200, 200-250, >250
  fNDiffAvgBins = 6;
  fDAmin = new float[fNDiffAvgBins];
  fDAmax = new float[fNDiffAvgBins];
  
  float DAmin[] = {00., 50.,  100., 150., 200., 250.};
  float DAmax[] = {50., 100., 150., 200., 250., 10000.};
  
  hDiffAvg = new TH1F*[fNDiffAvgBins];//!
  hMinDiffAvg = new TH1F*[fNDiffAvgBins];//!
  for (int ida = 0 ; ida < fNDiffAvgBins ; ida++ ){

    fDAmin[ida] = DAmin[ida];
    fDAmax[ida] = DAmax[ida];
    
    hDiffAvg[ida] = new TH1F(Form("hDiffAvg_%02d",ida),Form("hDiffAvg for A = (%03.0f - %03.0f)",DAmin[ida],DAmax[ida]),5000,0.0,50.0);
    hMinDiffAvg[ida] = new TH1F(Form("hMinDiffAvg_%02d",ida),Form("hMinDiffAvg for A = (%03.0f - %03.0f)",DAmin[ida],DAmax[ida]),5000,0.0,50.0);
  }
  
  hbtagweight_1a = new TH1F("hbtagweight_1a","hbtagweight_1a", 200.0, 0.0, 2.0);
  
  kinFit.SetBtagThresh(0.6321);
  kinFit.SetTopMass(mTop);
  
  //fOutput->Add(hMuPt);
  
}

Int_t PerformKinFit::FindBinIndex(float val, float *minArray, float *maxArray, int arraySize)
{
  for (int ida = 0 ; ida < arraySize ; ida++ ){
    if(val >= minArray[ida] and val < maxArray[ida])
      return ida;
  }
  return -1;
}

Bool_t PerformKinFit::Process(Long64_t entry)
{

  fProcessed++;
  
  // to read complete event, call fChain->GetTree()->GetEntry(entry)
  //fChain->GetTree()->GetEntry(entry);
  _btagWeight_1a = -100.0;
  
  br_passPresel_Ele->GetEntry(entry);
  br_passPresel_Mu->GetEntry(entry);
  br_muPt->GetEntry(entry);
  br_muEta->GetEntry(entry);
  br_muPhi->GetEntry(entry);
  br_nJet->GetEntry(entry);
  br_nBJet->GetEntry(entry);
  br_jetPt->GetEntry(entry);
  br_jetEta->GetEntry(entry);
  br_jetPhi->GetEntry(entry);
  br_jetMass->GetEntry(entry);
  br_jetDeepB->GetEntry(entry);
  br_nu_px->GetEntry(entry);
  br_nu_py->GetEntry(entry);
  br_nu_pz->GetEntry(entry);
  br_nu_pz_other->GetEntry(entry); 
  br_pfMET->GetEntry(entry); 
  br_pfMETPhi->GetEntry(entry); 
  br_btagWeight_1a->GetEntry(entry); 
  
  
  br_HT->GetEntry(entry);
  br_M3->GetEntry(entry);
  br_M_jjkF->GetEntry(entry);
  br_M_jj->GetEntry(entry);
  br_WtransMass->GetEntry(entry);
  br_elePhi->GetEntry(entry);
  br_elePt->GetEntry(entry);
  br_eleSCEta->GetEntry(entry);
  br_nVtx->GetEntry(entry);
  br_chi2->GetEntry(entry);

  br_evtWeight->GetEntry(entry) ;
  br_PUweight->GetEntry(entry) ;
  br_muEffWeight->GetEntry(entry) ;
  br_eleEffWeight->GetEntry(entry) ;  // 1 * 1 * 1 * 1 for q2 * pdf * isr * fsr
  br_btagWeight_1a->GetEntry(entry) ;  
  br_btagWeight_1a_b_Do->GetEntry(entry) ;
  br_btagWeight_1a_b_Up->GetEntry(entry) ;
  br_btagWeight_1a_l_Do->GetEntry(entry) ;
  br_btagWeight_1a_l_Up->GetEntry(entry) ;
  br_eleEffWeight_Do->GetEntry(entry) ;
  br_eleEffWeight_Up->GetEntry(entry) ;
  br_FSRweight_Do->GetEntry(entry) ;  
  br_FSRweight_Up->GetEntry(entry) ;
  br_ISRweight_Do->GetEntry(entry) ;
  br_ISRweight_Up->GetEntry(entry) ;  
  br_muEffWeight_Do->GetEntry(entry) ;
  br_muEffWeight_Up->GetEntry(entry) ;
  br_pdfweight_Do->GetEntry(entry) ;
  br_pdfweight_Up->GetEntry(entry) ;
  br_PUweight_Do->GetEntry(entry) ;
  br_PUweight_Up->GetEntry(entry) ;
  br_q2weight_Do->GetEntry(entry) ;
  br_q2weight_Up->GetEntry(entry) ;
  
  if(_passPresel_Ele) return true;
  
  hNlep->Fill(int(_muPt->size()));
  
  if(_btagWeight_1a > 0.0)
    hbtagweight_1a->Fill(_btagWeight_1a);
  
  if(entry%1000==0)
    cout<<" Processing event : " << entry << endl;

  double reslepEta, reslepPhi, resneuEta, resneuPhi, resbjlepEta, resbjlepPhi, resbjhadEta, resbjhadPhi, rescjhadEta, rescjhadPhi, ressjhadEta, ressjhadPhi ; 
  int isel = 0;
  const int nSel = 17;
  bool isSel[nSel];
  for(int is = 0 ; is < nSel ; is++ ) 
    isSel[is] = false;

  //for (int ipt = 0 ; ipt < int(_muPt->size()) ; ipt++ )
  hMuPt->Fill(_muPt->at(0));  
  
  jetVectors.clear();
  jetBtagVectors.clear();
  
  for (int ijet = 0 ; ijet < _nJet ; ijet++){
    jetVector.SetPtEtaPhiM( _jetPt->at(ijet), _jetEta->at(ijet) , _jetPhi->at(ijet), _jetMass->at(ijet) );
    jetVectors.push_back(jetVector);
    jetBtagVectors.push_back( _jetDeepB->at(ijet) );
  }
  lepVector.SetPtEtaPhiM(_muPt->at(0), _muEta->at(0) , _muPhi->at(0), TDatabasePDG::Instance()->GetParticle(13)->Mass());
  
  kinFit.SetJetVector(jetVectors);
  //kinFit.SetJetResVector(jetResolutionVectors);
  kinFit.SetBtagVector(jetBtagVectors);
  kinFit.SetLepton(lepVector);
  KinFit::LeptonType ltype = (_passPresel_Ele)?(KinFit::kElectron):(KinFit::kMuon); 
  kinFit.SetLeptonType(ltype);
  kinFit.SetMET(_nu_px, _nu_py, _nu_pz, _nu_pz_other);
  kinFit.SetMETPtPhi(_pfMET, _pfMETPhi);
  
  if(_nBJet >=2 and _nJet>=4){
    hdRSigNeu->Fill(1.0);
    hMindRSigNeu->Fill(1.0);
  }

  if ( kinFit.Fit() ){

    hNbCombiBRD->Fill(kinFit.GetNCombinations());
    int nRdiffPass = 0;
    vector<float> chi2_arr;
    chi2_arr.clear();
    vector<Chi2Array> Chi2ToMass_arr;
    Chi2Array Chi2ToMass;
    Chi2ToMass_arr.clear();
    
    double minlepPt = -1.0;
    float A = -1.0, B = -1.0;
    int ithda = -1;
    int minithda = -1;
    float  minBbyA = -1.0;
    int ithpt = -1;

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
 
      reslepEta = kinFit.GetResLepEta(i);
      reslepPhi = kinFit.GetResLepPhi(i);
      resneuEta = kinFit.GetResNeuEta(i);
      resneuPhi = kinFit.GetResNeuPhi(i);
      resbjlepEta = kinFit.GetResBjLepEta(i);
      resbjlepPhi = kinFit.GetResBjLepPhi(i);
      resbjhadEta = kinFit.GetResBjHadEta(i);
      resbjhadPhi = kinFit.GetResBjHadPhi(i);
      rescjhadEta = kinFit.GetResCjHadEta(i);
      rescjhadPhi = kinFit.GetResCjHadPhi(i);
      ressjhadEta = kinFit.GetResSjHadEta(i);
      ressjhadPhi = kinFit.GetResSjHadPhi(i);
      
      double Rdifflep	= TMath::Sqrt( TMath::Power(TMath::Abs(leptonBF.Eta() - leptonAF.Eta()) , 2) + TMath::Power(TMath::Abs(leptonBF.Phi() - leptonAF.Phi()) , 2) );
      double Rdiffbjlep	= TMath::Sqrt( TMath::Power(TMath::Abs(bjlepBF.Eta() - bjlepAF.Eta()) , 2) + TMath::Power(TMath::Abs(bjlepBF.Phi() - bjlepAF.Phi()) , 2) );
      double Rdiffbjhad	= TMath::Sqrt( TMath::Power(TMath::Abs(bjhadBF.Eta() - bjhadAF.Eta()) , 2) + TMath::Power(TMath::Abs(bjhadBF.Phi() - bjhadAF.Phi()) , 2) );
      double Rdiffcjhad	= TMath::Sqrt( TMath::Power(TMath::Abs(cjhadBF.Eta() - cjhadAF.Eta()) , 2) + TMath::Power(TMath::Abs(cjhadBF.Phi() - cjhadAF.Phi()) , 2) );
      double Rdiffsjhad	= TMath::Sqrt( TMath::Power(TMath::Abs(sjhadBF.Eta() - sjhadAF.Eta()) , 2) + TMath::Power(TMath::Abs(sjhadBF.Phi() - sjhadAF.Phi()) , 2) ); 
      
      double sigmaResoRDLep = TMath::Sqrt( TMath::Power(TMath::Abs(leptonBF.Eta() - leptonAF.Eta()) , 2) * reslepEta * reslepEta
					   +
					   TMath::Power(TMath::Abs(leptonBF.Phi() - leptonAF.Phi()) , 2) * reslepPhi * reslepPhi
					   ) / Rdifflep ;
      double sigmaResoRDBjLep = TMath::Sqrt( TMath::Power(TMath::Abs(bjlepBF.Eta() - bjlepAF.Eta()) , 2) * resbjlepEta * resbjlepEta
					     +
					     TMath::Power(TMath::Abs(bjlepBF.Phi() - bjlepAF.Phi()) , 2) * resbjlepPhi * resbjlepPhi
					     ) / Rdiffbjlep ;
      
      double sigmaResoRDBjHad = TMath::Sqrt( TMath::Power(TMath::Abs(bjhadBF.Eta() - bjhadAF.Eta()) , 2) * resbjhadEta * resbjhadEta
					    +
					    TMath::Power(TMath::Abs(bjhadBF.Phi() - bjhadAF.Phi()) , 2)  * resbjhadPhi * resbjhadPhi
					     ) / Rdiffbjhad ;

      double sigmaResoRDCjHad = TMath::Sqrt( TMath::Power(TMath::Abs(cjhadBF.Eta() - cjhadAF.Eta()) , 2) * rescjhadEta * rescjhadEta
					    +
					    TMath::Power(TMath::Abs(cjhadBF.Phi() - cjhadAF.Phi()) , 2)  * rescjhadPhi * rescjhadPhi
					     ) / Rdiffcjhad ;

      double sigmaResoRDSjHad = TMath::Sqrt( TMath::Power(TMath::Abs(sjhadBF.Eta() - sjhadAF.Eta()) , 2) * ressjhadEta * ressjhadEta
					    +
					    TMath::Power(TMath::Abs(sjhadBF.Phi() - sjhadAF.Phi()) , 2)  * ressjhadPhi * ressjhadPhi
					     ) / Rdiffsjhad ;
      
      // hdRSigLep->Fill(Rdifflep/sigmaResoRDLep);
      // hdRSigBjHad->Fill(Rdiffbjhad/sigmaResoRDBjHad);
      // hdRSigBjLep->Fill(Rdiffbjlep/sigmaResoRDBjLep);
      // hdRSigCjHad->Fill(Rdiffcjhad/sigmaResoRDCjHad);
      // hdRSigSjHad->Fill(Rdiffsjhad/sigmaResoRDSjHad);

      hdRSigLep->Fill(Rdifflep);
      hdRSigBjHad->Fill(Rdiffbjhad);
      hdRSigBjLep->Fill(Rdiffbjlep);
      hdRSigCjHad->Fill(Rdiffcjhad);
      hdRSigSjHad->Fill(Rdiffsjhad);
      
      ithpt = FindBinIndex(leptonAF.Pt(),fPtmin,fPtmax,fNPtBins); 
      if( ithpt >= 0){
	hPtBFLep[ithpt]->Fill( leptonBF.Pt() );
	hPtAFLep[ithpt]->Fill( leptonAF.Pt() );
	hPtvsRatioPtLep[ithpt]->Fill( leptonBF.Pt() / leptonAF.Pt() );
      }

      ithpt = FindBinIndex(neutrinoAF.Pt(),fPtmin,fPtmax,fNPtBins); 
      if( ithpt >= 0){
	hPtBFNeu[ithpt]->Fill( neutrinoBF.Pt() );
	hPtAFNeu[ithpt]->Fill( neutrinoAF.Pt() );
	hPtvsRatioPtNeu[ithpt]->Fill( neutrinoBF.Pt() / neutrinoAF.Pt() );
      }

      ithpt = FindBinIndex(bjhadAF.Pt(),fPtmin,fPtmax,fNPtBins); 
      if( ithpt >= 0){
	hPtBFBjHad[ithpt]->Fill( bjhadBF.Pt() );
	hPtAFBjHad[ithpt]->Fill( bjhadAF.Pt() );
	hPtvsRatioPtBjHad[ithpt]->Fill( bjhadBF.Pt() / bjhadAF.Pt() );
      }

      ithpt = FindBinIndex(bjlepAF.Pt(),fPtmin,fPtmax,fNPtBins); 
      //if( ithpt >= 0){
      if( ithpt >= 0 && neutrinoAF.E() > fptmin ){
	hPtBFBjLep[ithpt]->Fill( bjlepBF.Pt() );
	hPtAFBjLep[ithpt]->Fill( bjlepAF.Pt() );
	hPtvsRatioPtBjLep[ithpt]->Fill( bjlepBF.Pt() / bjlepAF.Pt() );
      }

      ithpt = FindBinIndex(cjhadAF.Pt(),fPtmin,fPtmax,fNPtBins); 
      if( ithpt >= 0){
	hPtBFCjHad[ithpt]->Fill( cjhadBF.Pt() );
	hPtAFCjHad[ithpt]->Fill( cjhadAF.Pt() );
	hPtvsRatioPtCjHad[ithpt]->Fill( cjhadBF.Pt() / cjhadAF.Pt() );
      }

      ithpt = FindBinIndex(sjhadAF.Pt(),fPtmin,fPtmax,fNPtBins); 
      if( ithpt >= 0){
	hPtBFSjHad[ithpt]->Fill( sjhadBF.Pt() );
	hPtAFSjHad[ithpt]->Fill( sjhadAF.Pt() );
	hPtvsRatioPtSjHad[ithpt]->Fill( sjhadBF.Pt() / sjhadAF.Pt() );
      }

      if(leptonAF.Pt() >= fptmin and leptonAF.Pt() < fptmax ){
	hPtvsdEtLep->Fill(TMath::Abs(leptonBF.Et() - leptonAF.Et()) );
	hPtvsdetaLep->Fill(TMath::Abs(leptonBF.Eta() - leptonAF.Eta()) );
	hPtvsdPhiLep->Fill(TMath::Abs(leptonBF.Phi() - leptonAF.Phi()) );
      }
      
      if(bjhadAF.Pt() >= fptmin and bjhadAF.Pt() < fptmax ){
	hPtvsdEtBjHad->Fill(TMath::Abs(bjhadBF.Et() - bjhadAF.Et()) );
	// if(bjhadAF.Pt() < 40.0 and TMath::Abs(bjhadBF.Et() - bjhadAF.Et()) > 50.0){
	// 	printf("BjHad :: Before KinFit : Pt : %6.2f, Pz : %6.2f, P : %6.2f, E : %6.2f, Et : %6.2f\n",bjhadBF.Pt(),bjhadBF.Pz(),bjhadBF.P(),bjhadBF.E(),bjhadBF.Et());
	// 	printf("BjHad :: After KinFit : Pt : %6.2f, Pz : %6.2f, P : %6.2f, E : %6.2f, Et : %6.2f\n",bjhadAF.Pt(),bjhadAF.Pz(),bjhadAF.P(),bjhadAF.E(),bjhadAF.Et());
	// 	cout<<endl;
	// }
	hPtvsdetaBjHad->Fill(TMath::Abs(bjhadBF.Eta() - bjhadAF.Eta()) );
	hPtvsdPhiBjHad->Fill(TMath::Abs(bjhadBF.Phi() - bjhadAF.Phi()) );
	// if(bjhadAF.Pt() < 40.0 and TMath::Abs(bjhadBF.Phi() - bjhadAF.Phi()) > 3.0){
	// 	printf("BjHad :: Before KF : Pt : %6.2f, Pz : %6.2f, P : %6.2f, E : %6.2f, Et : %6.2f, Phi : %6.2f\n",bjhadBF.Pt(),bjhadBF.Pz(),bjhadBF.P(),bjhadBF.E(),bjhadBF.Et(),bjhadBF.Phi());
	// 	printf("BjHad :: After KF : Pt : %6.2f, Pz : %6.2f, P : %6.2f, E : %6.2f, Et : %6.2f, Phi : %6.2f\n",bjhadAF.Pt(),bjhadAF.Pz(),bjhadAF.P(),bjhadAF.E(),bjhadAF.Et(),bjhadAF.Phi());
	// 	cout<<endl;
	// }
      }
      
      if(bjlepAF.Pt() >= fptmin and bjlepAF.Pt() < fptmax ){
	hPtvsdEtBjLep->Fill(TMath::Abs(bjlepBF.Et() - bjlepAF.Et()) );
	hPtvsdetaBjLep->Fill(TMath::Abs(bjlepBF.Eta() - bjlepAF.Eta()) );
	hPtvsdPhiBjLep->Fill(TMath::Abs(bjlepBF.Phi() - bjlepAF.Phi()) );
      }

      if(cjhadAF.Pt() >= fptmin and cjhadAF.Pt() < fptmax ){
	hPtvsdEtCjHad->Fill(TMath::Abs(cjhadBF.Et() - cjhadAF.Et()) );
	hPtvsdetaCjHad->Fill(TMath::Abs(cjhadBF.Eta() - cjhadAF.Eta()) );
	hPtvsdPhiCjHad->Fill(TMath::Abs(cjhadBF.Phi() - cjhadAF.Phi()) );
      }
      
      if(sjhadAF.Pt() >= fptmin and sjhadAF.Pt() < fptmax ){
	hPtvsdEtSjHad->Fill(TMath::Abs(sjhadBF.Et() - sjhadAF.Et()) );
	hPtvsdetaSjHad->Fill(TMath::Abs(sjhadBF.Eta() - sjhadAF.Eta()) );
	hPtvsdPhiSjHad->Fill(TMath::Abs(sjhadBF.Phi() - sjhadAF.Phi()) );
      }
      
      // Case A--
      // A = 0.5 *(lepTopAF + hadTopAF).P(); 
      // B = TMath::Abs((lepTopAF - hadTopAF).P()); 
      TVector3 lepTopAF3D = lepTopAF.Vect();
      TVector3 hadTopAF3D = hadTopAF.Vect();
      // Case B --
      // A = 0.5 *(lepTopAF3D + hadTopAF3D).Mag(); 
      // B = (lepTopAF3D - hadTopAF3D).Mag(); 
      // Case C --
      // A = 0.5 *(lepTopAF3D.Pt() + hadTopAF3D.Pt()); 
      // B = TMath::Abs(lepTopAF3D.Pt() - hadTopAF3D.Pt()); 
      // Case C --
      A = 0.5 *(lepTopAF3D + hadTopAF3D).Pt(); 
      B = (lepTopAF3D - hadTopAF3D).Pt(); 
      ithda = FindBinIndex(A,fDAmin,fDAmax,fNDiffAvgBins); 
      if( ithda >= 0){
	hDiffAvg[ithda]->Fill(B/A);
      }
      
      double mjj	= (cjhadBF + sjhadBF).M(); 
      double mjjkF	= (cjhadAF + sjhadAF).M(); 
      
      hMjj->Fill(mjj);
      hChi2->Fill(kinFit.GetChi2(i));
      
      if(leptonAF.Pt() > 30. and neutrinoAF.Pt() > 20. and bjhadAF.Pt()>30. and bjlepAF.Pt()>30. and cjhadAF.Pt()>30. and sjhadAF.Pt()>30.
	 and Rdifflep < 0.2 and Rdiffbjlep < 0.2 and Rdiffbjhad < 0.2 and Rdiffcjhad < 0.2 and Rdiffsjhad < 0.2)
	chi2_arr.push_back(kinFit.GetChi2(i));

      hNbiter->Fill(float(kinFit.GetNumberOfIter(i)));
      
      Chi2ToMass.chi2	    = kinFit.GetChi2(i);
      Chi2ToMass.mass	    = mjjkF;
      Chi2ToMass.mW	    = (leptonAF + neutrinoAF).M();
      Chi2ToMass.A	    = A;
      Chi2ToMass.B	    = B;
      Chi2ToMass.ndf	    = kinFit.GetNDF(i);
      Chi2ToMass.nb_iter    = kinFit.GetNumberOfIter(i);
      Chi2ToMass.leptonAF   = leptonAF;
      Chi2ToMass.neutrinoAF = neutrinoAF;
      Chi2ToMass.bjlepAF    = bjlepAF; 
      Chi2ToMass.bjhadAF    = bjhadAF;
      Chi2ToMass.cjhadAF    = cjhadAF;
      Chi2ToMass.sjhadAF    = sjhadAF;
      Chi2ToMass.leptonBF   = leptonBF;
      Chi2ToMass.neutrinoBF = neutrinoBF;
      Chi2ToMass.bjlepBF    = bjlepBF; 
      Chi2ToMass.bjhadBF    = bjhadBF;
      Chi2ToMass.cjhadBF    = cjhadBF;
      Chi2ToMass.sjhadBF    = sjhadBF;

      Chi2ToMass_arr.push_back(Chi2ToMass);
      
      if(Rdifflep < 0.2 and Rdiffbjlep < 0.2 and Rdiffbjhad < 0.2 and Rdiffcjhad < 0.2 and Rdiffsjhad < 0.2)
	nRdiffPass++;
      
    }// for loop over all kinfit combinations
    
    std::sort(chi2_arr.begin(), chi2_arr.end());
    // if(Chi2ToMass_arr.size()==5){
    //   printf("==========Before ==========\n");
    //   for (auto x : Chi2ToMass_arr){
    // 	printf("chi2 : %5.3lf, mass : %5.3lf, mW : %5.3lf, leptonBF.Pt() : %5.3lf, bjhadBF.Pt() : %5.3lf | leptonAF.Pt() : %5.3lf, bjhadAF.Pt() : %5.3lf\n",
    // 	       x.chi2, x.mass, x.mW, x.leptonBF.Pt(), x.bjhadBF.Pt(), x.leptonAF.Pt(), x.bjhadAF.Pt());
    //   }
    //   printf("==========Before ==========\n");
    // }
    std::sort(Chi2ToMass_arr.begin(), Chi2ToMass_arr.end(), compareChi2Array);
    // if(Chi2ToMass_arr.size()==5){
    //   printf("==========After ==========\n");
    //   for (auto x : Chi2ToMass_arr){
    // 	printf("chi2 : %5.3lf, mass : %5.3lf, mW : %5.3lf, leptonBF.Pt() : %5.3lf, bjhadBF.Pt() : %5.3lf | leptonAF.Pt() : %5.3lf, bjhadAF.Pt() : %5.3lf\n",
    // 	       x.chi2, x.mass, x.mW, x.leptonBF.Pt(), x.bjhadBF.Pt(), x.leptonAF.Pt(), x.bjhadAF.Pt());
    //   }
    //   printf("==========After ==========\n");
    //   cout<<endl;
    // }


    int iloop = 0;
    for (auto x : Chi2ToMass_arr){
      //cout << "[" << x.chi2 << ", " << x.mass << "] ";
      
      double Rdifflep	= TMath::Sqrt( TMath::Power(TMath::Abs(x.leptonBF.Eta() - x.leptonAF.Eta()) , 2) + TMath::Power(TMath::Abs(x.leptonBF.Phi() - x.leptonAF.Phi()) , 2) );
      double Rdiffbjlep	= TMath::Sqrt( TMath::Power(TMath::Abs(x.bjlepBF.Eta() - x.bjlepAF.Eta()) , 2) + TMath::Power(TMath::Abs(x.bjlepBF.Phi() - x.bjlepAF.Phi()) , 2) );
      double Rdiffbjhad	= TMath::Sqrt( TMath::Power(TMath::Abs(x.bjhadBF.Eta() - x.bjhadAF.Eta()) , 2) + TMath::Power(TMath::Abs(x.bjhadBF.Phi() - x.bjhadAF.Phi()) , 2) );
      double Rdiffcjhad	= TMath::Sqrt( TMath::Power(TMath::Abs(x.cjhadBF.Eta() - x.cjhadAF.Eta()) , 2) + TMath::Power(TMath::Abs(x.cjhadBF.Phi() - x.cjhadAF.Phi()) , 2) );
      double Rdiffsjhad	= TMath::Sqrt( TMath::Power(TMath::Abs(x.sjhadBF.Eta() - x.sjhadAF.Eta()) , 2) + TMath::Power(TMath::Abs(x.sjhadBF.Phi() - x.sjhadAF.Phi()) , 2) ); 
      
      if(iloop == 0){ // Only 1st min chi2
	minlepPt = x.leptonAF.Pt() ;
	if(x.leptonAF.Pt() > 30. and x.neutrinoAF.Pt() > 20. and x.bjhadAF.Pt()>30. and x.bjlepAF.Pt()>30. and x.cjhadAF.Pt()>30. and x.sjhadAF.Pt()>30.
	   and Rdifflep < 0.2 and Rdiffbjlep < 0.2 and Rdiffbjhad < 0.2 and Rdiffcjhad < 0.2 and Rdiffsjhad < 0.2)
	  hMjjkFsc->Fill(x.mass);
	
	// Set the leaf elements of output kinfit tree
	//============================================
	_kFType			= 1;
	_chi2			= x.chi2;
	_NDF			= x.ndf;
	_Nbiter			= x.nb_iter ;
	_M_jj			= (x.cjhadBF + x.sjhadBF).M();
	_M_jjkF			= x.mass;
	
	_pfMET			= x.neutrinoBF.Pt() ;
	_pfMETPhi		= x.neutrinoBF.Phi() ;
	_nu_px			= x.neutrinoBF.Px() ;
	_nu_py			= x.neutrinoBF.Py() ;
	_nu_pz			= x.neutrinoBF.Pz() ;
	//_nu_pz_other		= 0 ;
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
	
	_lepPt			= x.leptonAF.Pt() ;
	_lepEta			= x.leptonAF.Eta() ;
	_lepPhi			= x.leptonAF.Phi() ;
	_lepEnergy		= x.leptonAF.E() ;
	_metPx			= x.neutrinoAF.Px() ;
	_metPy			= x.neutrinoAF.Py() ;
	_metPz			= x.neutrinoAF.Pz() ;
	_jetBlepPt		= x.bjlepAF.Pt() ;
	_jetBlepEta		= x.bjlepAF.Eta() ;
	_jetBlepPhi		= x.bjlepAF.Phi() ;
	_jetBlepEnergy		= x.bjlepAF.E() ;
	_jetBhadPt		= x.bjhadAF.Pt() ;
	_jetBhadEta		= x.bjhadAF.Eta() ;
	_jetBhadPhi		= x.bjhadAF.Phi() ;
	_jetBhadEnergy		= x.bjhadAF.E() ;
	_jetChadPt		= x.cjhadAF.Pt() ;
	_jetChadEta		= x.cjhadAF.Eta() ;
	_jetChadPhi		= x.cjhadAF.Phi() ;
	_jetChadEnergy		= x.cjhadAF.E() ;
	_jetShadPt		= x.sjhadAF.Pt() ;
	_jetShadEta		= x.sjhadAF.Eta()  ;
	_jetShadPhi		= x.sjhadAF.Phi()  ;
	_jetShadEnergy		= x.sjhadAF.E()  ;
	
	//============================================
	
	//mass histo
	//=========================================
	isel = 0;
	hMjjkF_01->Fill(x.mass);                   // E > 0 condn
	isSel[isel++] = true;
	if(x.chi2 >= (fchi2cut-20.0) and  x.chi2 < fchi2cut){
	  hMjjkF_02->Fill(x.mass);                 // chi2 < 20
	  isSel[isel++] = true;
	  if(x.leptonAF.Pt()>30.){
	    hMjjkF_03->Fill(x.mass);               // pt_mu > 30
	    isSel[isel++] = true;
	    if(x.bjhadAF.Pt()>30.){
	      hMjjkF_04->Fill(x.mass);             // pt_bj > 30
	      isSel[isel++] = true;
	      if(x.bjlepAF.Pt()>30.){
		hMjjkF_05->Fill(x.mass);           // pt_bl > 30
		isSel[isel++] = true;
		if(x.cjhadAF.Pt()>30.){
		  hMjjkF_06->Fill(x.mass);         // pt_cj > 30
		  isSel[isel++] = true;
		  if(x.sjhadAF.Pt()>30.){
		    hMjjkF_07->Fill(x.mass);       // pt_sj > 30
		    isSel[isel++] = true;
		    if(x.neutrinoAF.Pt()>20.){
		      hMjjkF_08->Fill(x.mass);     // pt_neu > 20
		      isSel[isel++] = true;
		      if(Rdiffbjhad < 0.2){
			hMjjkF_09->Fill(x.mass);             // Rdiffbjhad < 0.2
			isSel[isel++] = true;
			if(Rdiffcjhad < 0.2){
			  hMjjkF_10->Fill(x.mass);           // Rdiffcjhad < 0.2
			  isSel[isel++] = true;
			  if(Rdiffsjhad < 0.2){
			    hMjjkF_11->Fill(x.mass);         // Rdiffsjhad < 0.2
			    isSel[isel++] = true;
			    if(Rdiffbjlep < 0.2){
			      hMjjkF_12->Fill(x.mass);       // Rdiffbjlep < 0.2
			      isSel[isel++] = true;
			      if(Rdifflep < 0.2){
				hMjjkF_13->Fill(x.mass);     // Rdifflep < 0.2
				isSel[isel++] = true;

				double ratio_neu = x.neutrinoBF.Pt() / x.neutrinoAF.Pt() ;
				double sigcut_neu = exp( -5.19100e-02  - 9.91514e-03*x.neutrinoAF.Pt() ) ; 
				if( (ratio_neu >= (1.0-3.*sigcut_neu) and ratio_neu <= (1.0+3.*sigcut_neu)) ){
				  hMjjkF_14->Fill(x.mass);   // neu 3 sig cut
				  isSel[isel++] = true;

				  double ratio_bj = x.bjhadBF.Pt() / x.bjhadAF.Pt() ;
				  double sigcut_bj = exp( -1.89164e+00  - 4.01351e-03*x.bjhadAF.Pt() ) ; 
				  if( (ratio_bj >= (1.0-3.*sigcut_bj) and ratio_bj <= (1.0+3.*sigcut_bj)) ){
				    hMjjkF_15->Fill(x.mass);   // bjhad 3 sig cut
				    isSel[isel++] = true;

				    double ratio_cj = x.cjhadBF.Pt() / x.cjhadAF.Pt() ;
				    double sigcut_cj = exp( -2.09665e+00  -4.46061e-03*x.cjhadAF.Pt() ) ; 
				    if( (ratio_cj >= (1.0-3.*sigcut_cj) and ratio_cj <= (1.0+3.*sigcut_cj)) ){
				      hMjjkF_16->Fill(x.mass);   // cjhad 3 sig cut
				      isSel[isel++] = true;

				      double ratio_sj = x.sjhadBF.Pt() / x.sjhadAF.Pt() ;
				      double sigcut_sj = exp( -1.87615e+00  -8.24975e-03*x.sjhadAF.Pt() ) ; 
				      if( (ratio_sj >= (1.0-3.*sigcut_sj) and ratio_sj <= (1.0+3.*sigcut_sj)) ){
					hMjjkF_17->Fill(x.mass);   // sjhad 3 sig cut				  
					isSel[isel++] = true;
					
					lepTopAF = (x.leptonAF + x.neutrinoAF + x.bjlepAF) ;
					hadTopAF = (x.bjhadAF + x.cjhadAF + x.sjhadAF);
					
					hPtTopLep->Fill(lepTopAF.Pt());
					hPtTopHad->Fill(hadTopAF.Pt());
					hPtTopHL->Fill(hadTopAF.Pt(),lepTopAF.Pt());
					
					hAssymPt->Fill( (hadTopAF.Pt() - lepTopAF.Pt())/(hadTopAF.Pt() + lepTopAF.Pt()) );
					
					if(x.leptonAF.Pt() > x.neutrinoAF.Pt()){
					  hMuEta_Pthigh->Fill(x.leptonAF.Eta());
					  hNeuEta_Ptlow->Fill(x.neutrinoAF.Eta());
					}else{
					  hNeuEta_Pthigh->Fill(x.neutrinoAF.Eta());
					  hMuEta_Ptlow->Fill(x.leptonAF.Eta());
					}
					
					ithpt = FindBinIndex(x.leptonAF.Pt(),fPtmin,fPtmax,fNPtBins); 
					if( ithpt >= 0){
					  hMinPtBFLep[ithpt]->Fill( x.leptonBF.Pt() );
					  hMinPtAFLep[ithpt]->Fill( x.leptonAF.Pt() );
					  hMinPtvsRatioPtLep[ithpt]->Fill( x.leptonBF.Pt() / x.leptonAF.Pt()  );
					  //printf("ithpt : %d\n",ithpt);
					}
		    
					ithpt = FindBinIndex(x.neutrinoAF.Pt(),fPtmin,fPtmax,fNPtBins); 
					if( ithpt >= 0){
					  hMinPtBFNeu[ithpt]->Fill( x.neutrinoBF.Pt() );
					  hMinPtAFNeu[ithpt]->Fill( x.neutrinoAF.Pt() );
					  hMinPtvsRatioPtNeu[ithpt]->Fill( x.neutrinoBF.Pt() / x.neutrinoAF.Pt() );
					}

					ithpt = FindBinIndex(x.bjhadAF.Pt(),fPtmin,fPtmax,fNPtBins); 
					if( ithpt >= 0){
					  hMinPtBFBjHad[ithpt]->Fill( x.bjhadBF.Pt() );
					  hMinPtAFBjHad[ithpt]->Fill( x.bjhadAF.Pt() );
					  hMinPtvsRatioPtBjHad[ithpt]->Fill( x.bjhadBF.Pt() / x.bjhadAF.Pt() );
					}

					ithpt = FindBinIndex(x.bjlepAF.Pt(),fPtmin,fPtmax,fNPtBins); 
					//if( ithpt >= 0){
					if( ithpt >= 0){
					  hMinPtBFBjLep[ithpt]->Fill( x.bjlepBF.Pt() );
					  hMinPtAFBjLep[ithpt]->Fill( x.bjlepAF.Pt() );
					  hMinPtvsRatioPtBjLep[ithpt]->Fill( x.bjlepBF.Pt() / x.bjlepAF.Pt() );
					}

					ithpt = FindBinIndex(x.cjhadAF.Pt(),fPtmin,fPtmax,fNPtBins); 
					if( ithpt >= 0){
					  hMinPtBFCjHad[ithpt]->Fill( x.cjhadBF.Pt() );
					  hMinPtAFCjHad[ithpt]->Fill( x.cjhadAF.Pt() );
					  hMinPtvsRatioPtCjHad[ithpt]->Fill( x.cjhadBF.Pt() / x.cjhadAF.Pt() );
					}

					ithpt = FindBinIndex(x.sjhadAF.Pt(),fPtmin,fPtmax,fNPtBins); 
					if( ithpt >= 0){
					  hMinPtBFSjHad[ithpt]->Fill( x.sjhadBF.Pt() );
					  hMinPtAFSjHad[ithpt]->Fill( x.sjhadAF.Pt() );
					  hMinPtvsRatioPtSjHad[ithpt]->Fill( x.sjhadBF.Pt() / x.sjhadAF.Pt() );
					}
					
					
					
				      }// sjhad 3 sig cut
				      else
					hMjjkF_ms->Fill(x.mass);
				    }// cjhad 3 sig cut
				    else
				      hMjjkF_ms->Fill(x.mass);				 
				  } // bjhad 3 sig cut
				  else
				    hMjjkF_ms->Fill(x.mass);
				}// neu 3 sig cut
				else
				  hMjjkF_ms->Fill(x.mass);
			      }// Rdifflep < 0.2
			      else
				hMjjkF_ms->Fill(x.mass);
			    }// Rdiffbjlep < 0.2
			    else
			      hMjjkF_ms->Fill(x.mass);
			  }// Rdiffsjhad < 0.2
			  else
			    hMjjkF_ms->Fill(x.mass);
			}// Rdiffcjhad < 0.2
			else
			  hMjjkF_ms->Fill(x.mass);
		      }// Rdiffbjhad < 0.2
		      else
			hMjjkF_ms->Fill(x.mass);
		    }// pt_neu > 30
		    else
		      hMjjkF_ms->Fill(x.mass);
		  }// pt_sj > 30
		  else
		    hMjjkF_ms->Fill(x.mass);
		}// pt_cj > 30
		else
		  hMjjkF_ms->Fill(x.mass);
	      }// pt_bl > 30
	      else
		hMjjkF_ms->Fill(x.mass);
	    }// pt_bj > 30
	    else
	      hMjjkF_ms->Fill(x.mass);
	  }// pt_mu > 30
	  else
	    hMjjkF_ms->Fill(x.mass);
	}//chi2 < 20
	else
	  hMjjkF_ms->Fill(x.mass);

	for(int is = 0 ; is < nSel ; is++ ) 
	  _selStep.push_back(isSel[is]);
  
	outputTree->Fill();

      }//iloop == 0 condition
      
      if(x.chi2 >= (fchi2cut-20.0) and  x.chi2 < fchi2cut and iloop == 0){ // minchi2 < 20
	
	
	hMjjkF->Fill(x.mass);
	

	double ratio_ljet1 = x.cjhadBF.Pt() / x.cjhadAF.Pt() ;
	double ratio_ljet2 = x.sjhadBF.Pt() / x.sjhadAF.Pt() ;
	double sigcut = exp( -1.91  - 0.00463*x.cjhadAF.Pt() ) ; 
	if( (ratio_ljet1 >= (1.0-3.*sigcut) and ratio_ljet1 <= (1.0+3.*sigcut)) and (ratio_ljet2 >= (1.0-3.*sigcut) and ratio_ljet2 <= (1.0+3.*sigcut))){
	  hMjjkF3s->Fill(x.mass);
	}
	
	hNbCombiARD->Fill(nRdiffPass);
	// hMindRSigLep->Fill(minRdifflepSignif);
	// hMindRSigBjHad->Fill(minRdiffbjhadSignif);
	// hMindRSigBjLep->Fill(minRdiffbjlepSignif);
	// hMindRSigCjHad->Fill(minRdiffcjhadSignif);
	// hMindRSigSjHad->Fill(minRdiffsjhadSignif);
	

	if(x.leptonAF.Pt() >= fptmin and x.leptonAF.Pt() < fptmax ){
	  hMinPtvsdEtLep->Fill(TMath::Abs(x.leptonBF.Et() - x.leptonAF.Et()) );
	  hMinPtvsdetaLep->Fill(TMath::Abs(x.leptonBF.Eta() - x.leptonAF.Eta()) );
	  hMinPtvsdPhiLep->Fill(TMath::Abs(x.leptonBF.Phi() - x.leptonAF.Phi()) );
	}
      
	if(x.bjhadAF.Pt() >= fptmin and x.bjhadAF.Pt() < fptmax ){
	  hMinPtvsdEtBjHad->Fill(TMath::Abs(x.bjhadBF.Et() - x.bjhadAF.Et()) );
	  hMinPtvsdetaBjHad->Fill(TMath::Abs(x.bjhadBF.Eta() - x.bjhadAF.Eta()) );
	  hMinPtvsdPhiBjHad->Fill(TMath::Abs(x.bjhadBF.Phi() - x.bjhadAF.Phi()) );
	}
      
	if(x.bjlepAF.Pt() >= fptmin and x.bjlepAF.Pt() < fptmax ){
	  hMinPtvsdEtBjLep->Fill(TMath::Abs(x.bjlepBF.Et() - x.bjlepAF.Et()) );
	  hMinPtvsdetaBjLep->Fill(TMath::Abs(x.bjlepBF.Eta() - x.bjlepAF.Eta()) );
	  hMinPtvsdPhiBjLep->Fill(TMath::Abs(x.bjlepBF.Phi() - x.bjlepAF.Phi()) );
	}

	if(x.cjhadAF.Pt() >= fptmin and x.cjhadAF.Pt() < fptmax ){
	  hMinPtvsdEtCjHad->Fill(TMath::Abs(x.cjhadBF.Et() - x.cjhadAF.Et()) );
	  hMinPtvsdetaCjHad->Fill(TMath::Abs(x.cjhadBF.Eta() - x.cjhadAF.Eta()) );
	  hMinPtvsdPhiCjHad->Fill(TMath::Abs(x.cjhadBF.Phi() - x.cjhadAF.Phi()) );
	}
      
	if(x.sjhadAF.Pt() >= fptmin and x.sjhadAF.Pt() < fptmax ){
	  hMinPtvsdEtSjHad->Fill(TMath::Abs(x.sjhadBF.Et() - x.sjhadAF.Et()) );
	  hMinPtvsdetaSjHad->Fill(TMath::Abs(x.sjhadBF.Eta() - x.sjhadAF.Eta()) );
	  hMinPtvsdPhiSjHad->Fill(TMath::Abs(x.sjhadBF.Phi() - x.sjhadAF.Phi()) );
	}
	
	hHadTop->Fill( (x.bjhadAF + x.cjhadAF + x.sjhadAF).M() );
	hLepTop->Fill( (x.leptonAF + x.neutrinoAF + x.bjlepAF).M() );
	hEtaNeu->Fill( x.neutrinoAF.Eta() );
	hMW->Fill( x.mW );
	
	ithda = FindBinIndex(x.A,fDAmin,fDAmax,fNDiffAvgBins); 
	if( ithda >= 0)
	  hMinDiffAvg[ithda]->Fill( x.B / x.A );
	
      }// Min chi2 condition
      iloop++;
    }// for loop over chi2 arrays
    
    //cout<<endl;    

    if(chi2_arr.size()>=1 and minlepPt > 0.0)
      hMinChi2->Fill(chi2_arr.at(0));
    if(chi2_arr.size()>=2 and minlepPt > 0.0)
      h2MinChi2->Fill(chi2_arr.at(1));
    if(chi2_arr.size()>=3 and minlepPt > 0.0)
      h3MinChi2->Fill(chi2_arr.at(2));    
    if(chi2_arr.size()>=4 and minlepPt > 0.0)
      h4MinChi2->Fill(chi2_arr.at(3));    
    if(chi2_arr.size()>=5 and minlepPt > 0.0)
      h5MinChi2->Fill(chi2_arr.at(4));    
        
    chi2_arr.clear();
    Chi2ToMass_arr.clear();
  }//if fit converges
  //hIsNeuComplex->Fill(kinFit.IsComplex());
  
  
  kinFit.Clear();
  jetVectors.clear();
  jetBtagVectors.clear();
  _selStep.clear();

  fStatus++;   
  return kTRUE;
}



void PerformKinFit::SlaveTerminate()
{
  
  Info("SlaveTerminate",
       "sample : %s, year : %d, mode : %s", fSample.Data(), fYear, fMode.Data());  
  
  fFile->cd();
  outputTree->Write();
  
  hMuPt->Write();
  hMjj->Write();
  hMjjkF->Write();
  hMjjkF3s->Write();
  hMjjkFsc->Write();

  hMjjkF_ms->Write();
  hMjjkF_01->Write();
  hMjjkF_02->Write();
  hMjjkF_03->Write();
  hMjjkF_04->Write();
  hMjjkF_05->Write();
  hMjjkF_06->Write();
  hMjjkF_07->Write();
  hMjjkF_08->Write();
  hMjjkF_09->Write();
  hMjjkF_10->Write();
  hMjjkF_11->Write();
  hMjjkF_12->Write();
  hMjjkF_13->Write();
  hMjjkF_14->Write();
  hMjjkF_15->Write();
  hMjjkF_16->Write();
  hMjjkF_17->Write();
  
  hNlep->Write();
  hChi2->Write();
  hMinChi2->Write();
  h2MinChi2->Write();
  h3MinChi2->Write();
  h4MinChi2->Write();
  h5MinChi2->Write();
  hNbiter->Write();
  hNbCombiBRD->Write();
  hNbCombiARD->Write();
  hdRSigLep->Write();
  hdRSigNeu->Write();
  hdRSigBjHad->Write();
  hdRSigBjLep->Write();
  hdRSigCjHad->Write();
  hdRSigSjHad->Write();
  hMindRSigLep->Write();
  hMindRSigNeu->Write();
  hMindRSigBjHad->Write();
  hMindRSigBjLep->Write();
  hMindRSigCjHad->Write();
  hMindRSigSjHad->Write();

  hPtvsdEtLep->Write();
  hPtvsdEtBjHad->Write();
  hPtvsdEtBjLep->Write();
  hPtvsdEtCjHad->Write();
  hPtvsdEtSjHad->Write();

  hPtvsdetaLep->Write();
  hPtvsdetaBjHad->Write();
  hPtvsdetaBjLep->Write();
  hPtvsdetaCjHad->Write();
  hPtvsdetaSjHad->Write();

  hPtvsdPhiLep->Write(); 
  hPtvsdPhiBjHad->Write();
  hPtvsdPhiBjLep->Write();
  hPtvsdPhiCjHad->Write();
  hPtvsdPhiSjHad->Write();
    
  hMinPtvsdEtLep->Write();
  hMinPtvsdEtBjHad->Write();
  hMinPtvsdEtBjLep->Write();
  hMinPtvsdEtCjHad->Write();
  hMinPtvsdEtSjHad->Write();

  hMinPtvsdetaLep->Write();
  hMinPtvsdetaBjHad->Write();
  hMinPtvsdetaBjLep->Write();
  hMinPtvsdetaCjHad->Write();
  hMinPtvsdetaSjHad->Write();

  hMinPtvsdPhiLep->Write(); 
  hMinPtvsdPhiBjHad->Write();
  hMinPtvsdPhiBjLep->Write();
  hMinPtvsdPhiCjHad->Write();
  hMinPtvsdPhiSjHad->Write();
  
  for (int ipt = 0 ; ipt < fNPtBins ; ipt++ ){
    hPtBFLep[ipt]->Write();
    hPtBFNeu[ipt]->Write();
    hPtBFBjHad[ipt]->Write();
    hPtBFBjLep[ipt]->Write();
    hPtBFCjHad[ipt]->Write();
    hPtBFSjHad[ipt]->Write();

    hPtAFLep[ipt]->Write();
    hPtAFNeu[ipt]->Write();
    hPtAFBjHad[ipt]->Write();
    hPtAFBjLep[ipt]->Write();
    hPtAFCjHad[ipt]->Write();
    hPtAFSjHad[ipt]->Write();

    hPtvsRatioPtLep[ipt]->Write();
    hPtvsRatioPtNeu[ipt]->Write();
    hPtvsRatioPtBjHad[ipt]->Write();
    hPtvsRatioPtBjLep[ipt]->Write();
    hPtvsRatioPtCjHad[ipt]->Write();
    hPtvsRatioPtSjHad[ipt]->Write();

    hMinPtBFLep[ipt]->Write();
    hMinPtBFNeu[ipt]->Write();
    hMinPtBFBjHad[ipt]->Write();
    hMinPtBFBjLep[ipt]->Write();
    hMinPtBFCjHad[ipt]->Write();
    hMinPtBFSjHad[ipt]->Write();

    hMinPtAFLep[ipt]->Write();
    hMinPtAFNeu[ipt]->Write();
    hMinPtAFBjHad[ipt]->Write();
    hMinPtAFBjLep[ipt]->Write();
    hMinPtAFCjHad[ipt]->Write();
    hMinPtAFSjHad[ipt]->Write();

    hMinPtvsRatioPtLep[ipt]->Write();
    hMinPtvsRatioPtNeu[ipt]->Write();
    hMinPtvsRatioPtBjHad[ipt]->Write();
    hMinPtvsRatioPtBjLep[ipt]->Write();
    hMinPtvsRatioPtCjHad[ipt]->Write();
    hMinPtvsRatioPtSjHad[ipt]->Write();
  }

  for (int ida = 0 ; ida < fNDiffAvgBins ; ida++ ){
    hDiffAvg[ida]->Write();
    hMinDiffAvg[ida]->Write();
  }
  
  hPtTopLep->Write();
  hPtTopHad->Write();
  hPtTopHL->Write();
  hAssymPt->Write();
  hNeuEta_Ptlow->Write();
  hNeuEta_Pthigh->Write();
  hMuEta_Ptlow->Write();
  hMuEta_Pthigh->Write();
  
  //hIsNeuComplex->Write();
  hMW->Write();
  
  hHadTop->Write();
  hLepTop->Write();
  hEtaNeu->Write();
  
  hbtagweight_1a->Write();

  fFile->Close();
  if (fMode.BeginsWith("proof")) {
    Info("SlaveTerminate", "objects saved into '%s%s': sending related TProofOutputFile ...",
	 fProofFile->GetFileName(), fProofFile->GetOptionsAnchor());
    fProofFile->Print();
    fOutput->Add(fProofFile);
  }
  
  delete  []fDAmin;
  delete  []fDAmax;
}


void PerformKinFit::Terminate()
{
// function called at the end of the event loop


  // hMuPt = dynamic_cast<TH1F*>(fOutput->FindObject("hMuPt"));

   // if (hMuPt == 0 || hElePt == 0) {
   //    Error("Terminate", "hMuPt = %p , hElePt = %p", hMuPt, hElePt);
   //    return;
   // }
   
   // //create the canvas for the PerformKinFit fit
   // TCanvas *c1 = new TCanvas("c1","c1",10,10,800,600);
   // hMuPt->Draw();
   
  // TCanvas *c2 = new TCanvas("c2","c2",100,100,800,600);
  // hMuPt->Draw();
   
   // Notify the amount of processed events
  if (!fInput) Info("Terminate", "processed %lld events", fProcessed);
  
   TString option = GetOption();
   Info("Terminate", "stopping PerformKinFit with process option: %s", option.Data());
   
}


