/**********************************************************************
 Created on : 12/04/2021
 Purpose    : Analyse the Reco tree to perform KinFit. 
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
  
  const char *filename = Form("result_%5.1f.root",mTop);
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
  hMjjkF = new TH1F("hMjjkF","hMjjkF",80,0,400.0); 
  hChi2 = new TH1F("hChi2","hChi2",500,0,100.0); 
  hNbiter = new TH1F("hNbiter","hNbiter",500,0,500.0); 
  hNbCombiBRD = new TH1F("hNbCombiBRD","hNbCombiBRD", 500, 0.0, 500.0);
  hNbCombiARD = new TH1F("hNbCombiARD","hNbCombiARD", 500, 0.0, 500.0);

  kinFit.SetBtagThresh(0.6321);
  kinFit.SetTopMass(mTop);

  //fOutput->Add(hMuPt);

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
  br_jetPt->GetEntry(entry);
  br_jetEta->GetEntry(entry);
  br_jetPhi->GetEntry(entry);
  br_jetMass->GetEntry(entry);
  br_jetDeepB->GetEntry(entry);
  br_nu_px->GetEntry(entry);
  br_nu_py->GetEntry(entry);
  br_nu_pz->GetEntry(entry);
  br_nu_pz_other->GetEntry(entry);
  
  if(_passPresel_Ele) return true;
  
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
  
  if ( kinFit.Fit() ){

    hNbCombiBRD->Fill(kinFit.GetNCombinations());
    int nRdiffPass = 0;
    for (unsigned int i = 0 ; i < kinFit.GetNCombinations() ; i++ ){
      
      leptonAF		= kinFit.GetLepton(i);
      neutrinoAF	= kinFit.GetNeutrino(i);
      bjlepAF		= kinFit.GetBLepton(i);
      bjhadAF		= kinFit.GetBHadron(i);
      cjhadAF		= kinFit.GetCHadron(i);
      sjhadAF		= kinFit.GetSHadron(i);
      
      leptonBF		= kinFit.GetLeptonUM(i);
      bjlepBF		= kinFit.GetBLeptonUM(i);
      bjhadBF		= kinFit.GetBHadronUM(i);
      cjhadBF		= kinFit.GetCHadronUM(i);
      sjhadBF		= kinFit.GetSHadronUM(i);
      
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
    
      double mjj	= (cjhadBF + sjhadBF).M(); 
      double mjjkF	= (cjhadAF + sjhadAF).M(); 
    
      hMjj->Fill(mjj);
      hChi2->Fill(kinFit.GetChi2(i));
      hNbiter->Fill(float(kinFit.GetNumberOfIter(i)));
      if(Rdifflep < 0.2 and Rdiffbjlep < 0.2 and Rdiffbjhad < 0.2 and Rdiffcjhad < 0.2 and Rdiffsjhad < 0.2){
	hMjjkF->Fill(mjjkF);
	nRdiffPass++;
      }
    }// for loop
    hNbCombiARD->Fill(nRdiffPass);
  }//if fit converger
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
  hNbiter->Write();
  hNbCombiBRD->Write();
  hNbCombiARD->Write();

  fFile->Close();
  if (fMode.BeginsWith("proof")) {
    Info("SlaveTerminate", "objects saved into '%s%s': sending related TProofOutputFile ...",
	 fProofFile->GetFileName(), fProofFile->GetOptionsAnchor());
    fProofFile->Print();
    fOutput->Add(fProofFile);
  }
  
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
