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
    float minmass = 1e9;
    int minNDF = 10;
    double minRdifflepSignif = 20.;
    double minRdiffbjhadSignif = 20.;
    double minRdiffbjlepSignif = 20.;
    double minRdiffcjhadSignif = 20.;
    double minRdiffsjhadSignif = 20.;
    vector<float> chi2_arr;
    chi2_arr.clear();
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
      
      double mjj	= (cjhadBF + sjhadBF).M(); 
      double mjjkF	= (cjhadAF + sjhadAF).M(); 
    
      hMjj->Fill(mjj);
      //hChi2->Fill(kinFit.GetChi2(i)/kinFit.GetNDF(i));
      hChi2->Fill(kinFit.GetChi2(i));
      chi2_arr.push_back(kinFit.GetChi2(i));
      hNbiter->Fill(float(kinFit.GetNumberOfIter(i)));
      if(Rdifflep < 0.2 and Rdiffbjlep < 0.2 and Rdiffbjhad < 0.2 and Rdiffcjhad < 0.2 and Rdiffsjhad < 0.2){
	//hMjjkF->Fill(mjjkF);
	nRdiffPass++;
      }
      if ( kinFit.GetChi2(i) < minChi2 ){
	minChi2 = kinFit.GetChi2(i) ;
	minNDF = kinFit.GetNDF(i) ;
	if(Rdifflep < 0.2 and Rdiffbjlep < 0.2 and Rdiffbjhad < 0.2 and Rdiffcjhad < 0.2 and Rdiffsjhad < 0.2)
	  minmass = mjjkF;
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
      }
    }// for loop
    std::sort(chi2_arr.begin(), chi2_arr.end());
    
    hMinChi2->Fill(minChi2);
    if(chi2_arr.size()>=2)
      h2MinChi2->Fill(chi2_arr.at(1));
    if(chi2_arr.size()>=3)
      h3MinChi2->Fill(chi2_arr.at(2));    
    if(chi2_arr.size()>=4)
      h4MinChi2->Fill(chi2_arr.at(3));    
    if(chi2_arr.size()>=5)
      h5MinChi2->Fill(chi2_arr.at(4));    
    hNbCombiARD->Fill(nRdiffPass);
    hMindRSigLep->Fill(minRdifflepSignif);
    hMindRSigBjHad->Fill(minRdiffbjhadSignif);
    hMindRSigBjLep->Fill(minRdiffbjlepSignif);
    hMindRSigCjHad->Fill(minRdiffcjhadSignif);
    hMindRSigSjHad->Fill(minRdiffsjhadSignif);
    hMjjkF->Fill(minmass);
    chi2_arr.clear();
  }//if fit converges
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
