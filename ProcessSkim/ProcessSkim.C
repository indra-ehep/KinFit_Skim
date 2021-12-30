/**********************************************************************
 Created on : 14/07/2021
 Purpose    : Analyse the Skim tree.
              (format adapted from h1analysis)
 Author     : Indranil Das, Visiting Fellow
 Email      : indranil.das@cern.ch | indra.ehep@gmail.com
**********************************************************************/

#include "ProcessSkim.h"
#include "TH2.h"
#include "TF1.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TPaveStats.h"
#include "TMath.h"
#include "TProof.h"
#include "TObjString.h"

//_____________________________________________________________________________
void ProcessSkim::GetArguments(){

  TString option = GetOption();
  //Info("GetArguments","ending ProcessSkim with process option: %s", option.Data());

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
  }
  
  if(fSample.BeginsWith("Data")){
    fSampleDir = "data_obs";
    isData = true;
  }else{
    fSampleDir = fSample;
    isData = false;
  }

  TString hostname = gSystem->HostName();
  if(hostname.BeginsWith("Indra-Rjn"))
    fBasePath = "/Data/CMS-Analysis/NanoAOD-Analysis";
  else if(hostname.BeginsWith("lxplus"))
    fBasePath = "/afs/cern.ch/user/i/idas/CMS-Analysis/NanoAOD-Analysis";
  else if(hostname.BeginsWith("ui"))
    fBasePath = "/home/idas";
    
}

//_____________________________________________________________________________
void ProcessSkim::Begin(TTree * /*tree*/)
{
   // This is needed when re-processing the object
   Reset();

   //print the option specified in the Process function.
   TString option = GetOption();
   Info("Begin", "starting ProcessSkim with process option: %s", option.Data());
   // Test tokenize

   if (fChain) fChain->SetEntryList(0);
}

Int_t ProcessSkim::CreateHistoArrays()
{
  // Create the histogram arrays
  Int_t nPtBins = 16; 
  Float_t ptBin[17] = {0., 10., 20., 30., 40., 50., 60., 80., 100., 140., 180., 220., 300., 400., 600., 800., 1000.};

  Int_t nEtaBins = 12;
  Float_t etaBin[13] = {0., 0.1, 0.2, 0.4, 0.6, 0.8, 1.0, 1.4, 1.8, 2.4, 3.0, 3.8, 4.6};

  for(int ifile=0;ifile<1;ifile++){

    TDirectory *savedir = gDirectory;
    savedir->cd();

    fFile[ifile]->cd();
    h2_BTagEff_Denom_b = new TH2D("h2_BTagEff_Denom_b", ";p_{T} [GeV];#eta", nPtBins, ptBin, nEtaBins, etaBin);
    h2_BTagEff_Denom_c = new TH2D("h2_BTagEff_Denom_c", ";p_{T} [GeV];#eta", nPtBins, ptBin, nEtaBins, etaBin);
    h2_BTagEff_Denom_udsg = new TH2D("h2_BTagEff_Denom_udsg", ";p_{T} [GeV];#eta", nPtBins, ptBin, nEtaBins, etaBin);
    //Loose BTag efficiency 2D histos          
    h2_BTagEff_Num_bL = new TH2D("h2_BTagEff_Num_bL", ";p_{T} [GeV];#eta", nPtBins, ptBin, nEtaBins, etaBin);
    h2_BTagEff_Num_cL = new TH2D("h2_BTagEff_Num_cL", ";p_{T} [GeV];#eta", nPtBins, ptBin, nEtaBins, etaBin);
    h2_BTagEff_Num_udsgL = new TH2D("h2_BTagEff_Num_udsgL", ";p_{T} [GeV];#eta", nPtBins, ptBin, nEtaBins, etaBin);
    //Medium BTag efficiency 2D histos          
    h2_BTagEff_Num_bM = new TH2D("h2_BTagEff_Num_bM", ";p_{T} [GeV];#eta", nPtBins, ptBin, nEtaBins, etaBin);
    h2_BTagEff_Num_cM = new TH2D("h2_BTagEff_Num_cM", ";p_{T} [GeV];#eta", nPtBins, ptBin, nEtaBins, etaBin);
    h2_BTagEff_Num_udsgM = new TH2D("h2_BTagEff_Num_udsgM", ";p_{T} [GeV];#eta", nPtBins, ptBin, nEtaBins, etaBin);
    //Tight BTag efficiency 2D histos          
    h2_BTagEff_Num_bT = new TH2D("h2_BTagEff_Num_bT", ";p_{T} [GeV];#eta", nPtBins, ptBin, nEtaBins, etaBin);
    h2_BTagEff_Num_cT = new TH2D("h2_BTagEff_Num_cT", ";p_{T} [GeV];#eta", nPtBins, ptBin, nEtaBins, etaBin);
    h2_BTagEff_Num_udsgT = new TH2D("h2_BTagEff_Num_udsgT", ";p_{T} [GeV];#eta", nPtBins, ptBin, nEtaBins, etaBin);

    h2_CTagEff_Denom_b = new TH2D("h2_CTagEff_Denom_b", ";p_{T} [GeV];#eta", nPtBins, ptBin, nEtaBins, etaBin);
    h2_CTagEff_Denom_c = new TH2D("h2_CTagEff_Denom_c", ";p_{T} [GeV];#eta", nPtBins, ptBin, nEtaBins, etaBin);
    h2_CTagEff_Denom_udsg = new TH2D("h2_CTagEff_Denom_udsg", ";p_{T} [GeV];#eta", nPtBins, ptBin, nEtaBins, etaBin);
    //Loose BTag efficiency 2D histos          
    h2_CTagEff_Num_bL = new TH2D("h2_CTagEff_Num_bL", ";p_{T} [GeV];#eta", nPtBins, ptBin, nEtaBins, etaBin);
    h2_CTagEff_Num_cL = new TH2D("h2_CTagEff_Num_cL", ";p_{T} [GeV];#eta", nPtBins, ptBin, nEtaBins, etaBin);
    h2_CTagEff_Num_udsgL = new TH2D("h2_CTagEff_Num_udsgL", ";p_{T} [GeV];#eta", nPtBins, ptBin, nEtaBins, etaBin);
    //Medium BTag efficiency 2D histos          
    h2_CTagEff_Num_bM = new TH2D("h2_CTagEff_Num_bM", ";p_{T} [GeV];#eta", nPtBins, ptBin, nEtaBins, etaBin);
    h2_CTagEff_Num_cM = new TH2D("h2_CTagEff_Num_cM", ";p_{T} [GeV];#eta", nPtBins, ptBin, nEtaBins, etaBin);
    h2_CTagEff_Num_udsgM = new TH2D("h2_CTagEff_Num_udsgM", ";p_{T} [GeV];#eta", nPtBins, ptBin, nEtaBins, etaBin);
    //Tight BTag efficiency 2D histos          
    h2_CTagEff_Num_bT = new TH2D("h2_CTagEff_Num_bT", ";p_{T} [GeV];#eta", nPtBins, ptBin, nEtaBins, etaBin);
    h2_CTagEff_Num_cT = new TH2D("h2_CTagEff_Num_cT", ";p_{T} [GeV];#eta", nPtBins, ptBin, nEtaBins, etaBin);
    h2_CTagEff_Num_udsgT = new TH2D("h2_CTagEff_Num_udsgT", ";p_{T} [GeV];#eta", nPtBins, ptBin, nEtaBins, etaBin);

  }//file loop

  
  return true;
}

//_____________________________________________________________________________
void ProcessSkim::SlaveBegin(TTree *tree)
{
  //initialize the Tree branch addresses
  Init(tree);
  
  //print the option specified in the Process function.
  TString option = GetOption();
  Info("SlaveBegin",
       "starting ProcessSkim with process option: %s (tree: %p)", option.Data(), tree);

  GetArguments();
  Info("SlaveBegin",
       "sample : %s, year : %d, mode : %s", fSample.Data(), fYear, fMode.Data());
  
  char *filename[3];
  
  filename[0] = Form("%s_btag_eff_raw_%d.root",fSample.Data(),fYear) ;
  
  for(int ifile=0;ifile<1;ifile++){
    
    if(fMode.BeginsWith("proof")){
      fProofFile[ifile] = new TProofOutputFile(filename[ifile], "M");
      fFile[ifile] = fProofFile[ifile]->OpenFile("RECREATE");
      if (fFile[ifile] && fFile[ifile]->IsZombie()) SafeDelete(fFile[ifile]);
    }else{
      fFile[ifile] = TFile::Open(filename[ifile],"RECREATE");
    }
    
    // Cannot continue
    if (!fFile[ifile]) {
      TString amsg = TString::Format("ProcessSkim::SlaveBegin: could not create '%s':"
				     " instance is invalid!", fFile[ifile]->GetName());
      Abort(amsg, kAbortProcess);
      return;
    }

  }//ifile loop
  
  CreateHistoArrays();

}



//_____________________________________________________________________________
Bool_t ProcessSkim::Process(Long64_t entry)
{
  // entry is the entry number in the current Tree
  // Selection function to select D* and D0.

  fProcessed++;
  
  // to read complete event, call fChain->GetTree()->GetEntry(entry)
  //fChain->GetTree()->GetEntry(entry);
  
  fChain->GetTree()->GetEntry(entry);

  bool isDeepCSV = true;

  if(isDeepCSV){
    
    for(unsigned int ijet = 0 ; ijet<nJet_ and int(nJet_) < 10000000; ijet++){
    
      double partonFlavor = jetPartFlvr_[ijet];
      double hadronFlavor = jetHadFlvr_[ijet];
      double deepb = jetBtagDeepB_[ijet];
      double deepcvb = jetBtagDeepCvB_[ijet];
      double deepcvl = jetBtagDeepCvL_[ijet];
      
      double deepbL = 1.;
      double deepbM = 1.;
      double deepbT = 1.;
      double deepcvl_L = 1.;
      double deepcvb_L = 1.;
      double deepcvl_M = 1.;
      double deepcvb_M = 1.;
      double deepcvl_T = 1.;
      double deepcvb_T = 1.;
      if(fYear==2016){
	if(isPreVFP){
	  deepbL = 0.2027;
	  deepbM = 0.6001;
	  deepbT = 0.8819 ;
	  deepcvl_L =  0.088 ;
	  deepcvb_L =  0.214 ;
	  deepcvl_M =  0.181 ;
	  deepcvb_M =  0.228 ;
	  deepcvl_T =  0.417 ;
	  deepcvb_T =  0.138 ;
	}
	if(isPostVFP){
	  deepbL = 0.1918;
	  deepbM = 0.5847 ;
	  deepbT = 0.8767 ;
	  deepcvl_L =  0.088 ;
	  deepcvb_L =  0.204 ;
	  deepcvl_M =  0.180 ;
	  deepcvb_M =  0.221 ;
	  deepcvl_T =  0.407 ;
	  deepcvb_T =  0.136 ;
	}
      }else if(fYear==2017){
	deepbL = 0.1355;
	deepbM = 0.4506;
	deepbT = 0.7738  ;
	deepcvl_L =  0.04 ;
	deepcvb_L =  0.345 ;
	deepcvl_M =  0.144 ;
	deepcvb_M =  0.29 ;
	deepcvl_T =  0.73 ;
	deepcvb_T =  0.10 ;
      }else if(fYear==2018){
	deepbL =  0.1208  ;
	deepbM =  0.4168  ;
	deepbT =  0.7665  ;      
	deepcvl_L =  0.064 ;
	deepcvb_L =  0.313 ;
	deepcvl_M =  0.153 ;
	deepcvb_M =  0.363 ;
	deepcvl_T =  0.405 ;
	deepcvb_T =  0.288 ;
      }
      //b-quarks
      if( abs(partonFlavor)==5 ){
	//if( abs(hadronFlavor)==5 ){
	h2_BTagEff_Denom_b->Fill(jetPt_[ijet], TMath::Abs(jetEta_[ijet]));
	if( deepb > deepbL ) h2_BTagEff_Num_bL->Fill(jetPt_[ijet], TMath::Abs(jetEta_[ijet]));
	if( deepb > deepbM ) h2_BTagEff_Num_bM->Fill(jetPt_[ijet], TMath::Abs(jetEta_[ijet]));
	if( deepb > deepbT ) h2_BTagEff_Num_bT->Fill(jetPt_[ijet], TMath::Abs(jetEta_[ijet]));

	h2_CTagEff_Denom_b->Fill(jetPt_[ijet], TMath::Abs(jetEta_[ijet]));
	if( deepcvl > deepcvl_L and deepcvb > deepcvb_L ) h2_CTagEff_Num_bL->Fill(jetPt_[ijet], TMath::Abs(jetEta_[ijet]));
	if( deepcvl > deepcvl_M and deepcvb > deepcvb_M ) h2_CTagEff_Num_bM->Fill(jetPt_[ijet], TMath::Abs(jetEta_[ijet]));
	if( deepcvl > deepcvl_T and deepcvb > deepcvb_T  ) h2_CTagEff_Num_bT->Fill(jetPt_[ijet], TMath::Abs(jetEta_[ijet]));
      }
      //c-quarks
      else if( abs(partonFlavor)==4 ){
	//else if( abs(hadronFlavor)==4 ){
	h2_BTagEff_Denom_c->Fill(jetPt_[ijet], TMath::Abs(jetEta_[ijet]));
	if( deepb > deepbL ) h2_BTagEff_Num_cL->Fill(jetPt_[ijet], TMath::Abs(jetEta_[ijet]));
	if( deepb > deepbM ) h2_BTagEff_Num_cM->Fill(jetPt_[ijet], TMath::Abs(jetEta_[ijet]));
	if( deepb > deepbT ) h2_BTagEff_Num_cT->Fill(jetPt_[ijet], TMath::Abs(jetEta_[ijet]));

	h2_CTagEff_Denom_c->Fill(jetPt_[ijet], TMath::Abs(jetEta_[ijet]));
	if( deepcvl > deepcvl_L and deepcvb > deepcvb_L ) h2_CTagEff_Num_cL->Fill(jetPt_[ijet], TMath::Abs(jetEta_[ijet]));
	if( deepcvl > deepcvl_M and deepcvb > deepcvb_M ) h2_CTagEff_Num_cM->Fill(jetPt_[ijet], TMath::Abs(jetEta_[ijet]));
	if( deepcvl > deepcvl_T and deepcvb > deepcvb_T ) h2_CTagEff_Num_cT->Fill(jetPt_[ijet], TMath::Abs(jetEta_[ijet]));
      }
      //other quarks and gluon
      else{
	h2_BTagEff_Denom_udsg->Fill(jetPt_[ijet], TMath::Abs(jetEta_[ijet]));
	if( deepb > deepbL ) h2_BTagEff_Num_udsgL->Fill(jetPt_[ijet], TMath::Abs(jetEta_[ijet]));
	if( deepb > deepbM ) h2_BTagEff_Num_udsgM->Fill(jetPt_[ijet], TMath::Abs(jetEta_[ijet]));
	if( deepb > deepbT ) h2_BTagEff_Num_udsgT->Fill(jetPt_[ijet], TMath::Abs(jetEta_[ijet]));

	h2_CTagEff_Denom_udsg->Fill(jetPt_[ijet], TMath::Abs(jetEta_[ijet]));
	if( deepcvl > deepcvl_L and deepcvb > deepcvb_L ) h2_CTagEff_Num_udsgL->Fill(jetPt_[ijet], TMath::Abs(jetEta_[ijet]));
	if( deepcvl > deepcvl_M and deepcvb > deepcvb_M ) h2_CTagEff_Num_udsgM->Fill(jetPt_[ijet], TMath::Abs(jetEta_[ijet]));
	if( deepcvl > deepcvl_T and deepcvb > deepcvb_T ) h2_CTagEff_Num_udsgT->Fill(jetPt_[ijet], TMath::Abs(jetEta_[ijet]));
      }
    
    }//jet loop
  }else{ // for MiniAOD
    for(unsigned int ijet = 0 ; ijet<nJet_ and int(nJet_) < 10000000; ijet++){

      double partonFlavor = jetPartFlvr_[ijet];
      double deepflavb = jetBtagDeepFlavB_[ijet];
      double deepflavcvb = jetBtagDeepFlavCvB_[ijet];
      double deepflavcvl = jetBtagDeepFlavCvL_[ijet];

      double deepflavbL = 1.;
      double deepflavbM = 1.;
      double deepflavbT = 1.;
      double deepflavcvl_L = 1.;
      double deepflavcvb_L = 1.;
      double deepflavcvl_M = 1.;
      double deepflavcvb_M = 1.;
      double deepflavcvl_T = 1.;
      double deepflavcvb_T = 1.;
      if(fYear==2016){
	if(isPreVFP){
	  deepflavbL = 0.0508;
	  deepflavbM = 0.2598 ;
	  deepflavbT = 0.6502  ;
	  deepflavcvl_L =  0.039 ;
	  deepflavcvb_L =  0.327 ;
	  deepflavcvl_M =  0.098 ;
	  deepflavcvb_M =  0.370 ;
	  deepflavcvl_T =  0.270 ;
	  deepflavcvb_T =  0.256 ;
	}
	if(isPostVFP){
	  deepflavbL = 0.0480 ;
	  deepflavbM = 0.2489  ;
	  deepflavbT = 0.6377  ;
	  deepflavcvl_L =  0.039 ;
	  deepflavcvb_L =  0.305 ;
	  deepflavcvl_M =  0.099 ;
	  deepflavcvb_M =  0.353 ;
	  deepflavcvl_T =  0.269 ;
	  deepflavcvb_T =  0.247 ;
	}
      }else if(fYear==2017){
	deepflavbL = 0.0532 ;
	deepflavbM = 0.3040 ;
	deepflavbT =  0.7476 ;
	deepflavcvl_L =  0.03 ;
	deepflavcvb_L =  0.4 ;
	deepflavcvl_M =  0.085 ;
	deepflavcvb_M =  0.34 ;
	deepflavcvl_T =  0.52 ;
	deepflavcvb_T =  0.05 ;
      }else if(fYear==2018){
	deepflavbL =  0.0490 ;
	deepflavbM =  0.2783  ;
	deepflavbT =  0.7100  ;      
	deepflavcvl_L =  0.038 ;
	deepflavcvb_L =  0.246 ;
	deepflavcvl_M =  0.099 ;
	deepflavcvb_M =  0.325 ;
	deepflavcvl_T =  0.282 ;
	deepflavcvb_T =  0.267 ;
      }

      if( abs(partonFlavor)==5 ){
	//if( abs(hadronFlavor)==5 ){
	h2_BTagEff_Denom_b->Fill(jetPt_[ijet], TMath::Abs(jetEta_[ijet]));
	if( deepflavb > deepflavbL ) h2_BTagEff_Num_bL->Fill(jetPt_[ijet], TMath::Abs(jetEta_[ijet]));
	if( deepflavb > deepflavbM ) h2_BTagEff_Num_bM->Fill(jetPt_[ijet], TMath::Abs(jetEta_[ijet]));
	if( deepflavb > deepflavbT ) h2_BTagEff_Num_bT->Fill(jetPt_[ijet], TMath::Abs(jetEta_[ijet]));

	h2_CTagEff_Denom_b->Fill(jetPt_[ijet], TMath::Abs(jetEta_[ijet]));
	if( deepflavcvl > deepflavcvl_L and deepflavcvb > deepflavcvb_L ) h2_CTagEff_Num_bL->Fill(jetPt_[ijet], TMath::Abs(jetEta_[ijet]));
	if( deepflavcvl > deepflavcvl_M and deepflavcvb > deepflavcvb_M ) h2_CTagEff_Num_bM->Fill(jetPt_[ijet], TMath::Abs(jetEta_[ijet]));
	if( deepflavcvl > deepflavcvl_T and deepflavcvb > deepflavcvb_T ) h2_CTagEff_Num_bT->Fill(jetPt_[ijet], TMath::Abs(jetEta_[ijet]));
      }
      //c-quarks
      else if( abs(partonFlavor)==4 ){
	//else if( abs(hadronFlavor)==4 ){
	h2_BTagEff_Denom_c->Fill(jetPt_[ijet], TMath::Abs(jetEta_[ijet]));
	if( deepflavb > deepflavbL ) h2_BTagEff_Num_cL->Fill(jetPt_[ijet], TMath::Abs(jetEta_[ijet]));
	if( deepflavb > deepflavbM ) h2_BTagEff_Num_cM->Fill(jetPt_[ijet], TMath::Abs(jetEta_[ijet]));
	if( deepflavb > deepflavbT ) h2_BTagEff_Num_cT->Fill(jetPt_[ijet], TMath::Abs(jetEta_[ijet]));

	h2_CTagEff_Denom_c->Fill(jetPt_[ijet], TMath::Abs(jetEta_[ijet]));
	if( deepflavcvl > deepflavcvl_L and deepflavcvb > deepflavcvb_L ) h2_CTagEff_Num_cL->Fill(jetPt_[ijet], TMath::Abs(jetEta_[ijet]));
	if( deepflavcvl > deepflavcvl_M and deepflavcvb > deepflavcvb_M ) h2_CTagEff_Num_cM->Fill(jetPt_[ijet], TMath::Abs(jetEta_[ijet]));
	if( deepflavcvl > deepflavcvl_T and deepflavcvb > deepflavcvb_T ) h2_CTagEff_Num_cT->Fill(jetPt_[ijet], TMath::Abs(jetEta_[ijet]));
      }
      //other quarks and gluon
      else{
	h2_BTagEff_Denom_udsg->Fill(jetPt_[ijet], TMath::Abs(jetEta_[ijet]));
	if( deepflavb > deepflavbL ) h2_BTagEff_Num_udsgL->Fill(jetPt_[ijet], TMath::Abs(jetEta_[ijet]));
	if( deepflavb > deepflavbM ) h2_BTagEff_Num_udsgM->Fill(jetPt_[ijet], TMath::Abs(jetEta_[ijet]));
	if( deepflavb > deepflavbT ) h2_BTagEff_Num_udsgT->Fill(jetPt_[ijet], TMath::Abs(jetEta_[ijet]));

	h2_CTagEff_Denom_udsg->Fill(jetPt_[ijet], TMath::Abs(jetEta_[ijet]));
	if( deepflavcvl > deepflavcvl_L and deepflavcvb > deepflavcvb_L ) h2_CTagEff_Num_udsgL->Fill(jetPt_[ijet], TMath::Abs(jetEta_[ijet]));
	if( deepflavcvl > deepflavcvl_M and deepflavcvb > deepflavcvb_M ) h2_CTagEff_Num_udsgM->Fill(jetPt_[ijet], TMath::Abs(jetEta_[ijet]));
	if( deepflavcvl > deepflavcvl_T and deepflavcvb > deepflavcvb_T ) h2_CTagEff_Num_udsgT->Fill(jetPt_[ijet], TMath::Abs(jetEta_[ijet]));
      }


    }//jet loop

  }

  fStatus++;
   
  return kTRUE;
}


//_____________________________________________________________________________
void ProcessSkim::SlaveTerminate()
{
  
  Info("SlaveTerminate",
       "sample : %s, year : %d, mode : %s", fSample.Data(), fYear, fMode.Data());

  
  // File closure
  
  for(int ifile=0;ifile<1;ifile++){

    TDirectory *savedir = gDirectory;
    savedir->cd();

    fFile[ifile]->cd();
    
    ///////////////////////////////
    h2_BTagEff_Denom_b->Write();
    h2_BTagEff_Denom_c->Write();
    h2_BTagEff_Denom_udsg->Write();
    h2_BTagEff_Num_bL->Write();
    h2_BTagEff_Num_cL->Write();
    h2_BTagEff_Num_udsgL->Write();
    h2_BTagEff_Num_bM->Write();
    h2_BTagEff_Num_cM->Write();
    h2_BTagEff_Num_udsgM->Write();
    h2_BTagEff_Num_bT->Write();
    h2_BTagEff_Num_cT->Write();
    h2_BTagEff_Num_udsgT->Write();
    ///////////////////////////////
      
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


}

//_____________________________________________________________________________
void ProcessSkim::Terminate()
{
// function called at the end of the event loop

   if (!fInput) Info("Terminate", "processed %lld events", fProcessed);
   
   TString option = GetOption();
   Info("Terminate", "stopping ProcessSkim with process option: %s", option.Data());
   
}
