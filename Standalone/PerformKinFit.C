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
  
  hMuPt = new TH1F("hMuPt","hMuPt",100,0,1000.0); 
  hMjj = new TH1F("hMjj","hMjj",80,0,400.0); 
  hMjjkF = new TH1F("hMjjkF",Form("hMjjkF with chi2cut : %5.2lf",fchi2cut),80,0,400.0); 
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
  fNPtBins = 6;
  float ptmin[] = {00., 40.,  80., 130., 200., 300.};
  float ptmax[] = {40., 80., 130., 200., 300., 10000.};
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
    
    hPtvsRatioPtLep[ipt]  = new TH1F(Form("hPtvsRatioPtLep_%02d",ipt),Form("hPtvsRatioPtLep for pt = (%5.2lf - %5.2lf) GeV/c",ptmin[ipt],ptmax[ipt]),2000,0.0,50.0);
    hPtvsRatioPtNeu[ipt]  = new TH1F(Form("hPtvsRatioPtNeu_%02d",ipt),Form("hPtvsRatioPtNeu for pt = (%5.2lf - %5.2lf) GeV/c",ptmin[ipt],ptmax[ipt]),2000,0.0,50.0);
    hPtvsRatioPtBjHad[ipt]  = new TH1F(Form("hPtvsRatioPtBjHad_%02d",ipt),Form("hPtvsRatioPtBjHad for pt = (%5.2lf - %5.2lf) GeV/c",ptmin[ipt],ptmax[ipt]),2000,0.0,50.0);
    hPtvsRatioPtBjLep[ipt]  = new TH1F(Form("hPtvsRatioPtBjLep_%02d",ipt),Form("hPtvsRatioPtBjLep for pt = (%5.2lf - %5.2lf) GeV/c",ptmin[ipt],ptmax[ipt]),2000,0.0,50.0);
    hPtvsRatioPtCjHad[ipt]  = new TH1F(Form("hPtvsRatioPtCjHad_%02d",ipt),Form("hPtvsRatioPtCjHad for pt = (%5.2lf - %5.2lf) GeV/c",ptmin[ipt],ptmax[ipt]),2000,0.0,50.0);
    hPtvsRatioPtSjHad[ipt]  = new TH1F(Form("hPtvsRatioPtSjHad_%02d",ipt),Form("hPtvsRatioPtSjhad for pt = (%5.2lf - %5.2lf) GeV/c",ptmin[ipt],ptmax[ipt]),2000,0.0,50.0);

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
    
    hMinPtvsRatioPtLep[ipt]  = new TH1F(Form("hMinPtvsRatioPtLep_%02d",ipt),Form("hMinPtvsRatioPtLep for pt = (%5.2lf - %5.2lf) GeV/c",ptmin[ipt],ptmax[ipt]),2000,0.0,50.0);
    hMinPtvsRatioPtNeu[ipt]  = new TH1F(Form("hMinPtvsRatioPtNeu_%02d",ipt),Form("hMinPtvsRatioPtNeu for pt = (%5.2lf - %5.2lf) GeV/c",ptmin[ipt],ptmax[ipt]),2000,0.0,50.0);
    hMinPtvsRatioPtBjHad[ipt]  = new TH1F(Form("hMinPtvsRatioPtBjHad_%02d",ipt),Form("hMinPtvsRatioPtBjHad for pt = (%5.2lf - %5.2lf) GeV/c",ptmin[ipt],ptmax[ipt]),2000,0.0,50.0);
    hMinPtvsRatioPtBjLep[ipt]  = new TH1F(Form("hMinPtvsRatioPtBjLep_%02d",ipt),Form("hMinPtvsRatioPtBjLep for pt = (%5.2lf - %5.2lf) GeV/c",ptmin[ipt],ptmax[ipt]),2000,0.0,50.0);
    hMinPtvsRatioPtCjHad[ipt]  = new TH1F(Form("hMinPtvsRatioPtCjHad_%02d",ipt),Form("hMinPtvsRatioPtCjHad for pt = (%5.2lf - %5.2lf) GeV/c",ptmin[ipt],ptmax[ipt]),2000,0.0,50.0);
    hMinPtvsRatioPtSjHad[ipt]  = new TH1F(Form("hMinPtvsRatioPtSjHad_%02d",ipt),Form("hMinPtvsRatioPtSjhad for pt = (%5.2lf - %5.2lf) GeV/c",ptmin[ipt],ptmax[ipt]),2000,0.0,50.0);
    
  }

  hIsNeuComplex = new TH1F("hIsNeuComplex","hIsNeuComplex",30, -1.0, 2.0);
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
 
  if(_passPresel_Ele) return true;

  if(entry%1000==0)
    cout<<" Processing event : " << entry << endl;

  double reslepEta, reslepPhi, resneuEta, resneuPhi, resbjlepEta, resbjlepPhi, resbjhadEta, resbjhadPhi, rescjhadEta, rescjhadPhi, ressjhadEta, ressjhadPhi ; 
  
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
    float minChi2 = 1e9;
    float minmass = -10.0;
    int minNDF = 10;
    double minRdifflepSignif = 20.;
    double minRdiffbjhadSignif = 20.;
    double minRdiffbjlepSignif = 20.;
    double minRdiffcjhadSignif = 20.;
    double minRdiffsjhadSignif = 20.;
    vector<float> chi2_arr;
    chi2_arr.clear();
    vector<Pair> Chi2ToMass_arr;
    Pair Chi2ToMass;
    Chi2ToMass_arr.clear();
    double minlepPtBF = -1.0, minneuPtBF = -1.0, minbjhadPtBF= -1.0, minbjlepPtBF= -1.0, mincjhadPtBF= -1.0, minsjhadPtBF = -1.0;
    double minlepPt = -1.0, minneuPt = -1.0, minbjhadPt= -1.0, minbjlepPt= -1.0, mincjhadPt= -1.0, minsjhadPt = -1.0;
    double minlepEtDiff= -1.0, minbjhadEtDiff= -1.0, minbjlepEtDiff= -1.0, mincjhadEtDiff= -1.0, minsjhadEtDiff = -1.0;
    double minlepetaDiff= -1.0, minbjhadetaDiff= -1.0, minbjlepetaDiff= -1.0, mincjhadetaDiff= -1.0, minsjhadetaDiff = -1.0;
    double minlepPhiDiff= -1.0, minbjhadPhiDiff= -1.0, minbjlepPhiDiff= -1.0, mincjhadPhiDiff= -1.0, minsjhadPhiDiff = -1.0;
    double minlepPtRatio= -1.0, minneuPtRatio= -1.0, minbjhadPtRatio= -1.0, minbjlepPtRatio= -1.0, mincjhadPtRatio= -1.0, minsjhadPtRatio = -1.0;
    double leptop = 10;
    double hadtop = 10;
    double neueta = 10;
    float A = -1.0, B = -1.0;
    int ithda = -1;
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
      
      double Rdifflep	= TMath::Sqrt( TMath::Power(TMath::Abs(leptonBF.Eta() - leptonAF.Eta()) , 2) 
				       + 
				       TMath::Power(TMath::Abs(leptonBF.Phi() - leptonAF.Phi()) , 2)  
				       );
      double Rdiffbjlep	= TMath::Sqrt( TMath::Power(TMath::Abs(bjlepBF.Eta() - bjlepAF.Eta()) , 2) 
				       + 
				       TMath::Power(TMath::Abs(bjlepBF.Phi() - bjlepAF.Phi()) , 2)  
				       );
      double Rdiffbjhad	= TMath::Sqrt( TMath::Power(TMath::Abs(bjhadBF.Eta() - bjhadAF.Eta()) , 2) 
				       + 
				       TMath::Power(TMath::Abs(bjhadBF.Phi() - bjhadAF.Phi()) , 2)  
				       );
      double Rdiffcjhad	= TMath::Sqrt( TMath::Power(TMath::Abs(cjhadBF.Eta() - cjhadAF.Eta()) , 2) 
				       + 
				       TMath::Power(TMath::Abs(cjhadBF.Phi() - cjhadAF.Phi()) , 2)  
				       );
      double Rdiffsjhad	= TMath::Sqrt( TMath::Power(TMath::Abs(sjhadBF.Eta() - sjhadAF.Eta()) , 2) 
				       + 
				       TMath::Power(TMath::Abs(sjhadBF.Phi() - sjhadAF.Phi()) , 2)  
  				       );
      
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
      hPtBFLep[ithpt]->Fill( leptonBF.Pt() );
      hPtAFLep[ithpt]->Fill( leptonAF.Pt() );
      hPtvsRatioPtLep[ithpt]->Fill( leptonBF.Pt() / leptonAF.Pt() );
      
      ithpt = FindBinIndex(neutrinoAF.Pt(),fPtmin,fPtmax,fNPtBins); 
      hPtBFNeu[ithpt]->Fill( neutrinoBF.Pt() );
      hPtAFNeu[ithpt]->Fill( neutrinoAF.Pt() );
      hPtvsRatioPtNeu[ithpt]->Fill( neutrinoBF.Pt() / neutrinoAF.Pt() );

      ithpt = FindBinIndex(bjhadAF.Pt(),fPtmin,fPtmax,fNPtBins); 
      hPtBFBjHad[ithpt]->Fill( bjhadBF.Pt() );
      hPtAFBjHad[ithpt]->Fill( bjhadAF.Pt() );
      hPtvsRatioPtBjHad[ithpt]->Fill( bjhadBF.Pt() / bjhadAF.Pt() );
      
      ithpt = FindBinIndex(bjlepAF.Pt(),fPtmin,fPtmax,fNPtBins); 
      hPtBFBjLep[ithpt]->Fill( bjlepBF.Pt() );
      hPtAFBjLep[ithpt]->Fill( bjlepAF.Pt() );
      hPtvsRatioPtBjLep[ithpt]->Fill( bjlepBF.Pt() / bjlepAF.Pt() );

      ithpt = FindBinIndex(cjhadAF.Pt(),fPtmin,fPtmax,fNPtBins); 
      hPtBFCjHad[ithpt]->Fill( cjhadBF.Pt() );
      hPtAFCjHad[ithpt]->Fill( cjhadAF.Pt() );
      hPtvsRatioPtCjHad[ithpt]->Fill( cjhadBF.Pt() / cjhadAF.Pt() );

      ithpt = FindBinIndex(sjhadAF.Pt(),fPtmin,fPtmax,fNPtBins); 
      hPtBFSjHad[ithpt]->Fill( sjhadBF.Pt() );
      hPtAFSjHad[ithpt]->Fill( sjhadAF.Pt() );
      hPtvsRatioPtSjHad[ithpt]->Fill( sjhadBF.Pt() / sjhadAF.Pt() );

      if(leptonAF.Pt() >= fptmin and leptonAF.Pt() < fptmax ){
	hPtvsdEtLep->Fill(TMath::Abs(leptonBF.Et() - leptonAF.Et()) );
	hPtvsdetaLep->Fill(TMath::Abs(leptonBF.Eta() - leptonAF.Eta()) );
	hPtvsdPhiLep->Fill(TMath::Abs(leptonBF.Phi() - leptonAF.Phi()) );
      }

      if(neutrinoAF.Pt() >= fptmin and neutrinoAF.Pt() < fptmax ){

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
      A = 0.5 *(lepTopAF3D.Pt() + hadTopAF3D.Pt()); 
      B = TMath::Abs(lepTopAF3D.Pt() - hadTopAF3D.Pt()); 
      ithda = FindBinIndex(A,fDAmin,fDAmax,fNDiffAvgBins); 
      if( ithda >= 0){
	hDiffAvg[ithda]->Fill(B/A);
      }

      double mjj	= (cjhadBF + sjhadBF).M(); 
      double mjjkF	= (cjhadAF + sjhadAF).M(); 
      
      hMjj->Fill(mjj);
      //hChi2->Fill(kinFit.GetChi2(i)/kinFit.GetNDF(i));
      hChi2->Fill(kinFit.GetChi2(i));
      chi2_arr.push_back(kinFit.GetChi2(i));
      hNbiter->Fill(float(kinFit.GetNumberOfIter(i)));
      // if(kinFit.GetChi2(i) < 20)
      // 	hMjjkF->Fill(mjjkF);

      
      
      if(Rdifflep < 0.2 and Rdiffbjlep < 0.2 and Rdiffbjhad < 0.2 and Rdiffcjhad < 0.2 and Rdiffsjhad < 0.2){
	nRdiffPass++;
	Chi2ToMass.chi2 = kinFit.GetChi2(i);
	Chi2ToMass.mass = mjjkF;
	Chi2ToMass.mW = (leptonBF + neutrinoBF).M();
	Chi2ToMass_arr.push_back(Chi2ToMass);

      }
      if ( kinFit.GetChi2(i) < minChi2 and kinFit.GetChi2(i) >= (fchi2cut-20.0)  and kinFit.GetChi2(i) < fchi2cut ){
	
	minChi2 = kinFit.GetChi2(i) ;
	minNDF = kinFit.GetNDF(i) ;
	// if(Rdifflep < 0.2 and Rdiffbjlep < 0.2 and Rdiffbjhad < 0.2 and Rdiffcjhad < 0.2 and Rdiffsjhad < 0.2 and minChi2<20)
	//   minmass = mjjkF;
	//minRdifflepSignif = Rdifflep/sigmaResoRDLep ;
	// minRdiffbjhadSignif = Rdiffbjhad/sigmaResoRDBjHad;
	// minRdiffbjlepSignif = Rdiffbjlep/sigmaResoRDBjLep;
	// minRdiffcjhadSignif = Rdiffcjhad/sigmaResoRDCjHad;
	// minRdiffsjhadSignif = Rdiffsjhad/sigmaResoRDSjHad;
	minRdifflepSignif = Rdifflep ;
	minRdiffbjhadSignif = Rdiffbjhad;
	minRdiffbjlepSignif = Rdiffbjlep;
	minRdiffcjhadSignif = Rdiffcjhad;
	minRdiffsjhadSignif = Rdiffsjhad;
	
	minlepPt = leptonAF.Pt() ;  minneuPt = neutrinoAF.Pt() ;  minbjhadPt = bjhadAF.Pt() ;  minbjlepPt = bjlepAF.Pt() ;  mincjhadPt = cjhadAF.Pt() ;  minsjhadPt = sjhadAF.Pt();
	minlepPtBF = leptonBF.Pt() ;  minneuPtBF = neutrinoBF.Pt() ;  minbjhadPtBF = bjhadBF.Pt() ;  
	minbjlepPtBF = bjlepBF.Pt() ;  mincjhadPtBF = cjhadBF.Pt() ;  minsjhadPtBF = sjhadBF.Pt();
	
	minlepEtDiff = TMath::Abs(leptonBF.Et() - leptonAF.Et()) ; minbjhadEtDiff = TMath::Abs(bjhadBF.Et() - bjhadAF.Et()) ;
	minbjlepEtDiff = TMath::Abs(bjlepBF.Et() - bjlepAF.Et()) ; mincjhadEtDiff = TMath::Abs(cjhadBF.Et() - cjhadAF.Et()) ;  
	minsjhadEtDiff = TMath::Abs(sjhadBF.Et() - sjhadAF.Et()) ;
	
	minlepetaDiff = TMath::Abs(leptonBF.Eta() - leptonAF.Eta()) ;  minbjhadetaDiff = TMath::Abs(bjhadBF.Eta() - bjhadAF.Eta()) ;  
	minbjlepetaDiff = TMath::Abs(bjlepBF.Eta() - bjlepAF.Eta()) ;  mincjhadetaDiff = TMath::Abs(cjhadBF.Eta() - cjhadAF.Eta());  
	minsjhadetaDiff = TMath::Abs(sjhadBF.Eta() - sjhadAF.Eta()) ;
	
	minlepPhiDiff = TMath::Abs(leptonBF.Phi() - leptonAF.Phi()) ; minbjhadPhiDiff = TMath::Abs(bjhadBF.Phi() - bjhadAF.Phi()) ; 
	minbjlepPhiDiff = TMath::Abs(bjlepBF.Phi() - bjlepAF.Phi()) ; mincjhadPhiDiff = TMath::Abs(cjhadBF.Phi() - cjhadAF.Phi()) ; 
	minsjhadPhiDiff = TMath::Abs(sjhadBF.Phi() - sjhadAF.Phi()) ;
	
	minlepPtRatio = TMath::Abs(leptonBF.Pt() / leptonAF.Pt()) ;  minbjhadPtRatio = TMath::Abs(bjhadBF.Pt() / bjhadAF.Pt()) ; 
	minbjlepPtRatio = TMath::Abs(bjlepBF.Pt() / bjlepAF.Pt()) ;  mincjhadPtRatio = TMath::Abs(cjhadBF.Pt() / cjhadAF.Pt()) ; 
	minsjhadPtRatio = TMath::Abs(sjhadBF.Pt() / sjhadAF.Pt()) ;
	minneuPtRatio = TMath::Abs(neutrinoBF.Pt() / neutrinoAF.Pt()) ;

        leptop = lepTopAF.M() ; 
	hadtop = hadTopAF.M() ;
	neueta = neutrinoAF.Eta() ;
	minBbyA = B/A ; 
      }
    }// for loop
    std::sort(chi2_arr.begin(), chi2_arr.end());
    std::sort(Chi2ToMass_arr.begin(), Chi2ToMass_arr.end(), comparePair);
    int iloop = 0;
    for (auto x : Chi2ToMass_arr){
      //cout << "[" << x.chi2 << ", " << x.mass << "] ";
      if(x.chi2 >= (fchi2cut-20.0) and  x.chi2 < fchi2cut and iloop == 0 and minlepPt > 0.0)
    	minmass = x.mass;
      if(!kinFit.IsComplex() and iloop == 0 and  minlepPt > 0.0)
	hMW->Fill( x.mW );
      if(iloop==0 and minlepPt > 0.0)
	hIsNeuComplex->Fill(kinFit.IsComplex());
      iloop++;
    }
    //cout<<endl;
    
    if(chi2_arr.size()>=2 and minlepPt > 0.0)
      h2MinChi2->Fill(chi2_arr.at(1));
    if(chi2_arr.size()>=3 and minlepPt > 0.0)
      h3MinChi2->Fill(chi2_arr.at(2));    
    if(chi2_arr.size()>=4 and minlepPt > 0.0)
      h4MinChi2->Fill(chi2_arr.at(3));    
    if(chi2_arr.size()>=5 and minlepPt > 0.0)
      h5MinChi2->Fill(chi2_arr.at(4));    
    
    if(chi2_arr.size()>=1 and minlepPt > 0.0 ){
    
      //cout << "1 " << minlepPt << ", " << minbjhadPt << ", " << minbjlepPt << ", " << mincjhadPt << ", " << minsjhadPt << endl;
      
      hMinChi2->Fill(minChi2);
      hNbCombiARD->Fill(nRdiffPass);
      hMindRSigLep->Fill(minRdifflepSignif);
      hMindRSigBjHad->Fill(minRdiffbjhadSignif);
      hMindRSigBjLep->Fill(minRdiffbjlepSignif);
      hMindRSigCjHad->Fill(minRdiffcjhadSignif);
      hMindRSigSjHad->Fill(minRdiffsjhadSignif);
      
      ithpt = FindBinIndex(minlepPt,fPtmin,fPtmax,fNPtBins); 
      hMinPtBFLep[ithpt]->Fill( minlepPtBF );
      hMinPtAFLep[ithpt]->Fill( minlepPt );
      hMinPtvsRatioPtLep[ithpt]->Fill( minlepPtRatio  );
      
      ithpt = FindBinIndex(minneuPt,fPtmin,fPtmax,fNPtBins); 
      hMinPtBFNeu[ithpt]->Fill( minneuPtBF );
      hMinPtAFNeu[ithpt]->Fill( minneuPt );
      hMinPtvsRatioPtNeu[ithpt]->Fill( minneuPtRatio );

      ithpt = FindBinIndex(minbjhadPt,fPtmin,fPtmax,fNPtBins); 
      hMinPtBFBjHad[ithpt]->Fill( minbjhadPtBF );
      hMinPtAFBjHad[ithpt]->Fill( minbjhadPt );
      hMinPtvsRatioPtBjHad[ithpt]->Fill( minbjhadPtRatio );

      ithpt = FindBinIndex(minbjlepPt,fPtmin,fPtmax,fNPtBins); 
      hMinPtBFBjLep[ithpt]->Fill( minbjlepPtBF );
      hMinPtAFBjLep[ithpt]->Fill( minbjlepPt );
      hMinPtvsRatioPtBjLep[ithpt]->Fill( minbjlepPtRatio );

      ithpt = FindBinIndex(mincjhadPt,fPtmin,fPtmax,fNPtBins); 
      hMinPtBFCjHad[ithpt]->Fill( mincjhadPtBF );
      hMinPtAFCjHad[ithpt]->Fill( mincjhadPt );
      hMinPtvsRatioPtCjHad[ithpt]->Fill( mincjhadPtRatio );

      ithpt = FindBinIndex(minsjhadPt,fPtmin,fPtmax,fNPtBins); 
      hMinPtBFSjHad[ithpt]->Fill( minsjhadPtBF );
      hMinPtAFSjHad[ithpt]->Fill( minsjhadPt );
      hMinPtvsRatioPtSjHad[ithpt]->Fill( minsjhadPtRatio );
      
      if(minlepPt >= fptmin and minlepPt < fptmax){
	hMinPtvsdEtLep->Fill( minlepEtDiff );
	hMinPtvsdetaLep->Fill( minlepetaDiff );
	hMinPtvsdPhiLep->Fill( minlepPhiDiff );
      }
      
      if(minbjhadPt >= fptmin and minbjhadPt < fptmax){
	hMinPtvsdEtBjHad->Fill( minbjhadEtDiff );
	hMinPtvsdetaBjHad->Fill( minbjhadetaDiff );
	hMinPtvsdPhiBjHad->Fill( minbjhadPhiDiff );
      }
      
      if(minbjlepPt >= fptmin and minbjlepPt < fptmax){
	hMinPtvsdEtBjLep->Fill( minbjlepEtDiff );
	hMinPtvsdetaBjLep->Fill( minbjlepetaDiff );
	hMinPtvsdPhiBjLep->Fill( minbjlepPhiDiff );
      }
      
      if(mincjhadPt >= fptmin and mincjhadPt < fptmax){
	hMinPtvsdEtCjHad->Fill( mincjhadEtDiff );
	hMinPtvsdetaCjHad->Fill( mincjhadetaDiff );
	hMinPtvsdPhiCjHad->Fill( mincjhadPhiDiff );
      }
      
      if(minsjhadPt >= fptmin and minsjhadPt < fptmax){
	hMinPtvsdEtSjHad->Fill( minsjhadEtDiff );
	hMinPtvsdetaSjHad->Fill( minsjhadetaDiff );
	hMinPtvsdPhiSjHad->Fill( minsjhadPhiDiff );
      }
      
      hHadTop->Fill(hadtop);
      hLepTop->Fill(leptop);
      hEtaNeu->Fill(neueta);
      
    }

    if( ithda >= 0 and minBbyA > 0.0){
      hMinDiffAvg[ithda]->Fill(minBbyA);
    }

    if(minmass >= 0.0)
      hMjjkF->Fill(minmass);
    chi2_arr.clear();
    Chi2ToMass_arr.clear();
  }//if fit converges
  //hIsNeuComplex->Fill(kinFit.IsComplex());
  
  kinFit.Clear();
  jetVectors.clear();
  jetBtagVectors.clear();
  
  fStatus++;   
  return kTRUE;
}



void PerformKinFit::SlaveTerminate()
{
  
  Info("SlaveTerminate",
       "sample : %s, year : %d, mode : %s", fSample.Data(), fYear, fMode.Data());  
  
  fFile->cd();
  hMuPt->Write();
  hMjj->Write();
  hMjjkF->Write();
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

  hIsNeuComplex->Write();
  hMW->Write();
  
  hHadTop->Write();
  hLepTop->Write();
  hEtaNeu->Write();
  
  
  
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
