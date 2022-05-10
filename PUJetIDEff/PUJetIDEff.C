/**********************************************************************
 Created on : 14/07/2021
 Purpose    : Analyse the Skim tree.
              (format adapted from h1analysis)
 Author     : Indranil Das, Visiting Fellow
 Email      : indranil.das@cern.ch | indra.ehep@gmail.com
**********************************************************************/

#include "PUJetIDEff.h"
#include "TH2.h"
#include "TF1.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TPaveStats.h"
#include "TMath.h"
#include "TProof.h"
#include "TObjString.h"
#include "TParticlePDG.h"
#include "TDatabasePDG.h"

//_____________________________________________________________________________
void PUJetIDEff::GetArguments(){

  TString option = GetOption();
  //Info("GetArguments","ending PUJetIDEff with process option: %s", option.Data());

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

  if(fYear==2016){  
    
    mu_Pt_cut = 26.;
    ele_Pt_cut = 30.;
    //jet_Pt_cut = 25.; //Original
    jet_Pt_cut = 20.; // Modified only to avoid non-empty PUJetID bin
    jet_Pt_cut_Max = 50.; // Applicable only for PUJetID which will also make the processing faster

    //DeepCSV
    btag_cut_DeepCSVa = 0.6001; 
    btag_cut_DeepCSVb = 0.5847; 
    //DeepJet
    btag_cuta = 0.2598 ; 
    btag_cutb = 0.2489 ; 

  }else if(fYear==2017){

    mu_Pt_cut = 30.;
    ele_Pt_cut = 35.;
    //jet_Pt_cut = 25.; //Original
    jet_Pt_cut = 20.; // Modified only to avoid non-empty PUJetID bin
    jet_Pt_cut_Max = 50.; // Applicable only for PUJetID which will also make the processing faster

    btag_cut_DeepCSV = 0.4506;
    btag_cut = 0.3040 ;

  }else if(fYear==2018){

    mu_Pt_cut = 26.;
    ele_Pt_cut = 35.;
    //jet_Pt_cut = 25.; //Original
    jet_Pt_cut = 20.; // Modified only to avoid non-empty PUJetID bin
    jet_Pt_cut_Max = 50.; // Applicable only for PUJetID which will also make the processing faster

    btag_cut_DeepCSV = 0.4168;
    btag_cut = 0.2783 ;

  }
    
}

//_____________________________________________________________________________
void PUJetIDEff::Begin(TTree * /*tree*/)
{
   // This is needed when re-processing the object
   Reset();

   //print the option specified in the Process function.
   TString option = GetOption();
   Info("Begin", "starting PUJetIDEff with process option: %s", option.Data());
   // Test tokenize

   if (fChain) fChain->SetEntryList(0);
}

Int_t PUJetIDEff::CreateHistoArrays()
{
  // Create the histogram arrays

  Int_t nPtBins = 4;
  Float_t ptBin[5] = {20., 25., 30., 35., 40.};

  Int_t nEtaBins = 12;
  Float_t etaBin[13] = {-5., -3., -2.75, -2.5, -2.0, -1.479, 0., 1.479, 2., 2.5, 2.75, 3., 5.};

  for(int ifile=0;ifile<1;ifile++){

    TDirectory *savedir = gDirectory;
    savedir->cd();
    
    fFile[ifile]->cd();
    h2_PUJetIDEff_Denom = new TH2D("h2_PUJetIDEff_Denom", ";p_{T} [GeV];#eta", nPtBins, ptBin, nEtaBins, etaBin);
    //Loose PUJetID efficiency 2D histos          
    h2_PUJetIDEff_Num_L = new TH2D("h2_PUJetIDEff_Num_L", ";p_{T} [GeV];#eta", nPtBins, ptBin, nEtaBins, etaBin);
    //Medium PUJetID efficiency 2D histos          
    h2_PUJetIDEff_Num_M = new TH2D("h2_PUJetIDEff_Num_M", ";p_{T} [GeV];#eta", nPtBins, ptBin, nEtaBins, etaBin);
    //Tight PUJetID efficiency 2D histos          
    h2_PUJetIDEff_Num_T = new TH2D("h2_PUJetIDEff_Num_T", ";p_{T} [GeV];#eta", nPtBins, ptBin, nEtaBins, etaBin);

  }//file loop
  
  return true;
}

//_____________________________________________________________________________
void PUJetIDEff::SlaveBegin(TTree *tree)
{
  //initialize the Tree branch addresses
  Init(tree);
  
  //print the option specified in the Process function.
  TString option = GetOption();
  Info("SlaveBegin",
       "starting PUJetIDEff with process option: %s (tree: %p)", option.Data(), tree);

  GetArguments();
  Info("SlaveBegin",
       "sample : %s, year : %d, mode : %s", fSample.Data(), fYear, fMode.Data());
  
  char *filename[3];
  
  filename[0] = Form("%s_pujetid_eff_raw_%d.root",fSample.Data(),fYear) ;
  
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
      TString amsg = TString::Format("PUJetIDEff::SlaveBegin: could not create '%s':"
				     " instance is invalid!", fFile[ifile]->GetName());
      Abort(amsg, kAbortProcess);
      return;
    }

  }//ifile loop
  
  CreateHistoArrays();

}

//_____________________________________________________________________________
bool PUJetIDEff::CheckTrigFilterVertex()
{
  
  Pass_trigger_mu  = false;
  Pass_trigger_ele = false;
 
  if (fYear==2016) {
    Pass_trigger_mu = ( HLT_IsoMu24_ || HLT_IsoTkMu24_ ) ;
    Pass_trigger_ele = HLT_Ele27_WPTight_Gsf_ ;
  }
  if (fYear==2017){
    Pass_trigger_mu = HLT_IsoMu27_ ;
	
    bool allSingleEGL1or = ( L1_SingleEG24_ ||
			    L1_SingleEG26_ ||
			    L1_SingleEG30_ ||
			    L1_SingleEG32_ ||
			    L1_SingleEG34_ ||
			    L1_SingleEG36_ ||
			    L1_SingleEG38_ ||
			    L1_SingleEG40_ ||
			    L1_SingleEG42_ ||
			    L1_SingleEG45_ ||
			    L1_SingleEG50_ ||
			    L1_SingleEG34er2p1_ ||
			    L1_SingleEG36er2p1_ ||
			    L1_SingleEG38er2p1_ ||
			    L1_SingleIsoEG24er2p1_ ||
			    L1_SingleIsoEG26er2p1_ ||
			    L1_SingleIsoEG28er2p1_ ||
			    L1_SingleIsoEG30er2p1_ ||
			    L1_SingleIsoEG32er2p1_ ||
			    L1_SingleIsoEG34er2p1_ ||
			    L1_SingleIsoEG36er2p1_ ||
			    L1_SingleIsoEG24_ ||
			    L1_SingleIsoEG26_ ||
			    L1_SingleIsoEG28_ ||
			    L1_SingleIsoEG30_ ||
			    L1_SingleIsoEG32_ ||
			    L1_SingleIsoEG34_ ||
			    L1_SingleIsoEG36_ ||
			    L1_SingleIsoEG38_ );

    Pass_trigger_ele = ( HLT_Ele32_WPTight_Gsf_L1DoubleEG_ && allSingleEGL1or );
    
  }
  if (fYear==2018){
    Pass_trigger_mu = HLT_IsoMu24_ ;
    Pass_trigger_ele = HLT_Ele32_WPTight_Gsf_ ;
  }
  
  bool filters = ( Flag_goodVertices_ &&
		   Flag_globalSuperTightHalo2016Filter_ &&
		   Flag_HBHENoiseFilter_ &&
		   Flag_HBHENoiseIsoFilter_ &&
		   Flag_EcalDeadCellTriggerPrimitiveFilter_ &&
		   Flag_BadPFMuonFilter_ );
  
  if (fYear==2017 || fYear==2018)
    filters = filters && Flag_ecalBadCalibFilter_ ;
    
  Pass_trigger_mu = Pass_trigger_mu && filters ;
  Pass_trigger_ele = Pass_trigger_ele && filters ;
  
  bool isPVGood = (pvNDOF_>4 &&
		   sqrt(pvX_ * pvX_ + pvY_ * pvY_)<=2. &&
		   abs(pvZ_) <= 24.);
    
  Pass_trigger_mu = Pass_trigger_mu && isPVGood;
  Pass_trigger_ele = Pass_trigger_ele && isPVGood;
  
  return true;

}

//_____________________________________________________________________________
bool PUJetIDEff::passEleID(int eleInd, int cutVal, bool doRelisoCut){

    Int_t WPcutBits = eleVidWPBitmap_[eleInd];

    int nBits = 3;

    bool MinPtCut                            = (WPcutBits>>(0*nBits) & 7) >= cutVal;
    bool GsfEleSCEtaMultiRangeCut            = (WPcutBits>>(1*nBits) & 7) >= cutVal;
    bool GsfEleDEtaInSeedCut                 = (WPcutBits>>(2*nBits) & 7) >= cutVal;
    bool GsfEleDPhiInCut                     = (WPcutBits>>(3*nBits) & 7) >= cutVal;
    bool GsfEleFull5x5SigmaIEtaIEtaCut       = (WPcutBits>>(4*nBits) & 7) >= cutVal;
    bool GsfEleHadronicOverEMEnergyScaledCut = (WPcutBits>>(5*nBits) & 7) >= cutVal;
    bool GsfEleEInverseMinusPInverseCut      = (WPcutBits>>(6*nBits) & 7) >= cutVal;
    bool GsfEleEffAreaPFIsoCut               = (WPcutBits>>(7*nBits) & 7) >= cutVal;
    bool GsfEleConversionVetoCut             = (WPcutBits>>(8*nBits) & 7) >= cutVal;
    bool GsfEleMissingHitsCut                = (WPcutBits>>(9*nBits) & 7) >= cutVal;

    bool passID = (
		   MinPtCut
		   && GsfEleSCEtaMultiRangeCut
		   && GsfEleDEtaInSeedCut
		   && GsfEleDPhiInCut
		   && GsfEleFull5x5SigmaIEtaIEtaCut
		   && GsfEleHadronicOverEMEnergyScaledCut
		   && GsfEleEInverseMinusPInverseCut
		   && (GsfEleEffAreaPFIsoCut || !doRelisoCut)
		   && GsfEleConversionVetoCut
		   && GsfEleMissingHitsCut
		   );

    return passID;

}

//_____________________________________________________________________________
Bool_t PUJetIDEff::Process(Long64_t entry)
{
  // entry is the entry number in the current Tree
  // Selection function to select D* and D0.

  fProcessed++;
  
  // to read complete event, call fChain->GetTree()->GetEntry(entry)
  //fChain->GetTree()->GetEntry(entry);
  
  fChain->GetTree()->GetEntry(entry);

  CheckTrigFilterVertex();
  if(!Pass_trigger_mu and !Pass_trigger_ele) return true;

  bool hasMu = false;
  int nofMu = 0;
  int muIndex = -1;
  for(int muInd = 0; muInd < int(nMuon_); ++muInd){
    int genIdx = int(muGenIdx_[muInd]);
    float eta = muEta_[muInd];
    float pt = muPt_[muInd];
    float phi = muPhi_[muInd];
    int nTrackerLayers = munTrackerLayers_[muInd];
    int charge =  muCharge_[muInd];
    float mudxy = mudxy_[muInd];
    float mudz = mudz_[muInd];
    double PFrelIso_corr = muPFRelIso_[muInd];
    bool mediumMuonID = muMediumId_[muInd];
    bool passMedium_Iso = (pt >= mu_Pt_cut &&
  			   TMath::Abs(eta) <= 2.4 &&
  			   mediumMuonID
  			   && (PFrelIso_corr < 0.4)
  			   );
    
    if(TMath::Abs(charge)!=1 or nTrackerLayers>=20 or nTrackerLayers<0 
       or !(TMath::Finite(eta)) or !(TMath::Finite(pt)) or !(TMath::Finite(phi)) 
       or TMath::Abs(mudxy)>=0.2 or TMath::Abs(mudz)>=0.5 or !passMedium_Iso) continue; 
    
    if ( (genIdx>-1) && (genIdx < int(nGenPart_))){
      unsigned int imc = genIdx ;
      TParticlePDG *partPDG = TDatabasePDG::Instance()->GetParticle(GenPart_pdgId_[imc]);
      TParticlePDG *partPDG_mother = TDatabasePDG::Instance()->GetParticle(GenPart_pdgId_[GenPart_genPartIdxMother_[imc]]);
      if(!partPDG_mother){
      }else{
  	// printf("\tMuon PDG : %5d (%7s), Rec:(%5.2f, %5.2f, %5.2f, %1d, %5.2f), Gen:(%5.2f, %5.2f, %5.2f, %1.0f, %5.2f), Mother : %7s\n", 
  	// 	 GenPart_pdgId_[imc], partPDG->GetName(), 
  	// 	 muPt_[muInd], muEta_[muInd] , muPhi_[muInd], muCharge_[muInd], muMass_[muInd],  
  	// 	 GenPart_pt_[imc], GenPart_eta_[imc] , GenPart_phi_[imc], partPDG->Charge()/3., GenPart_mass_[imc], 
  	// 	 partPDG_mother->GetName());
  	mujetR.SetPtEtaPhiM(muPt_[muInd], muEta_[muInd] , muPhi_[muInd], muMass_[muInd]);
  	mujetG.SetPtEtaPhiM(GenPart_pt_[imc], GenPart_eta_[imc] , GenPart_phi_[imc], GenPart_mass_[imc]);
  	if(mujetR.DeltaR(mujetG) < 0.1 and muCharge_[muInd]==int(partPDG->Charge()/3. and abs(GenPart_pdgId_[imc])==13)){
  	  hasMu = true;
  	  nofMu++;
  	  muIndex = muInd;
  	  //cout << "Found muon " << endl;
  	}
      }
    }
  }//muon loop
    
  bool hasEle = false;
  int nofEle = 0;
  int eleIndex = -1;
  for(int eleInd = 0; eleInd < int(nEle_); ++eleInd){
    int genIdx = int(eleGenIdx_[eleInd]);

    double eta = eleEta_[eleInd];
    double absEta = TMath::Abs(eta);
    double phi = elePhi_[eleInd];
    double SCeta = eta + eleDeltaEtaSC_[eleInd];
    double absSCEta = TMath::Abs(SCeta);    
    double pt = elePt_[eleInd];
    
    // // EA subtraction
    double PFrelIso_corr = elePFRelIso_[eleInd];
    
    uint eleID = eleIDcutbased_[eleInd];
    bool passVetoID   = eleID >= 1;
    // bool passLooseID  = eleID >= 2;
    // bool passMediumID = eleID >= 3;
    // bool passTightID  = eleID >= 4;
    
    // make sure it doesn't fall within the gap
    bool passEtaEBEEGap = (absSCEta < 1.4442) || (absSCEta > 1.566);
    
    // D0 and Dz cuts are different for barrel and endcap
    bool passD0 = ((absSCEta < 1.479 && abs(eleD0_[eleInd]) < 0.05) ||
  		   (absSCEta > 1.479 && abs(eleD0_[eleInd]) < 0.1));
    bool passDz = ((absSCEta < 1.479 && abs(eleDz_[eleInd]) < 0.1) ||
  		   (absSCEta > 1.479 && abs(eleDz_[eleInd]) < 0.2));
    bool passMediumID_noIso = passEleID(eleInd, 3,false) && passVetoID;
    
    bool eleSel_Medium_noIso = (passEtaEBEEGap && 
  				absSCEta <= 2.4 &&
  				pt >= ele_Pt_cut &&
  				passMediumID_noIso &&
  				elePFRelIso_[eleInd] < 0.3 && 
  				passD0 &&
  				passDz);
    
    if(!eleSel_Medium_noIso) continue;
    if ( (genIdx>-1) && (genIdx < int(nGenPart_))){
      unsigned int imc = genIdx ;
      TParticlePDG *partPDG = TDatabasePDG::Instance()->GetParticle(GenPart_pdgId_[imc]);
      TParticlePDG *partPDG_mother = TDatabasePDG::Instance()->GetParticle(GenPart_pdgId_[GenPart_genPartIdxMother_[imc]]);
      if(!partPDG_mother){
      }else{
  	// printf("\tElectron : PDG : %5d (%7s), Rec:(%5.2f, %5.2f, %5.2f, %1d, %5.2f), Gen:(%5.2f, %5.2f, %5.2f, %5.2f), Mother : %7s\n", 
  	// 	 GenPart_pdgId_[imc], partPDG->GetName(), 
  	// 	 elePt_[eleInd], eleEta_[eleInd] , elePhi_[eleInd], eleCharge_[eleInd], eleMass_[eleInd],  
  	// 	 GenPart_pt_[imc], GenPart_eta_[imc] , GenPart_phi_[imc], GenPart_mass_[imc], 
  	// 	 partPDG_mother->GetName());
  	elejetR.SetPtEtaPhiM(elePt_[eleInd], eleEta_[eleInd] , elePhi_[eleInd], eleMass_[eleInd]);
  	elejetG.SetPtEtaPhiM(GenPart_pt_[imc], GenPart_eta_[imc] , GenPart_phi_[imc], GenPart_mass_[imc]);
  	if(elejetR.DeltaR(elejetG) < 0.1 and eleCharge_[eleInd]==int(partPDG->Charge()/3.) and abs(GenPart_pdgId_[imc])==11){
  	  hasEle = true;
  	  nofEle++;
  	  eleIndex = eleInd;
  	  //cout << "Found electron " << endl;
  	}
	  
      }
    }
  }//electron loop



  if((nofMu==1 and nofEle==0) or (nofMu==0 and nofEle==1)){

    int nbjet = 0, nljet = 0;
    for(int jetInd = 0; jetInd < int(nJet_) and int(nJet_) < 10000000; ++jetInd){
      int genIdx = int(jetGenJetIdx_[jetInd]);
      double pt = jetPt_[jetInd];
      double eta = jetEta_[jetInd];
      double phi = jetPhi_[jetInd];
      //bool jetID_pass = (jetID_[jetInd]>=2 and (jetPUID_[jetInd]>=1 or pt>=50.0)) ; //lwp
      bool jetID_pass = jetID_[jetInd]>=2  ; //lwp
      bool passDR_lep_jet = true;
      jetR.SetPtEtaPhiM(jetPt_[jetInd], jetEta_[jetInd] , jetPhi_[jetInd], jetMass_[jetInd]);
      if(nofMu==1)
  	if ( jetR.DeltaR(mujetR) < 0.4) passDR_lep_jet = false;
      if(nofEle==1)
  	if ( jetR.DeltaR(elejetR) < 0.4) passDR_lep_jet = false;
      
      bool jetPresel = (pt >= jet_Pt_cut &&
  			//TMath::Abs(eta) <= 2.4 && // Default
			TMath::Abs(eta) <= 5.0 && //Modified for this study
  			jetID_pass &&
  			passDR_lep_jet
  			);
      
      if(!jetPresel) continue;
      nljet++;
    }//jet loop
    
    // if(nljet < 2 or nbjet < 2) return true;
    if(nljet < 4) return true; // Events with atleast 4 jets
      
    for(unsigned int ijet = 0 ; ijet<nJet_ and int(nJet_) < 10000000; ijet++){

      double pt = jetPt_[ijet];
      double eta = jetEta_[ijet];
      double phi = jetPhi_[ijet];
      bool jetID_pass = jetID_[ijet]>=2 ; //lwp
      bool passDR_lep_jet = true;
      jetR.SetPtEtaPhiM(jetPt_[ijet], jetEta_[ijet] , jetPhi_[ijet], jetMass_[ijet]);
      if(nofMu==1)
	if ( jetR.DeltaR(mujetR) < 0.4) passDR_lep_jet = false;
      if(nofEle==1)
	if ( jetR.DeltaR(elejetR) < 0.4) passDR_lep_jet = false;
    
      bool jetPresel = (pt >= jet_Pt_cut &&
			pt <= jet_Pt_cut_Max &&
			//TMath::Abs(eta) <= 2.4 && //Default
			TMath::Abs(eta) <= 5.0 && //Modified for this study
			jetID_pass &&
			passDR_lep_jet
			);
	
      if(!jetPresel) continue;
    
      bool isPass_L = false;
      bool isPass_M = false;
      bool isPass_T = false;

      if(fYear==2016){
	isPass_L = jetPUID_[ijet]>=1;
	isPass_M = jetPUID_[ijet]>=3;
	isPass_T = jetPUID_[ijet]>=7;
      }else{
	isPass_L = jetPUID_[ijet]>=4;
	isPass_M = jetPUID_[ijet]>=6;
	isPass_T = jetPUID_[ijet]>=7;
      }

      h2_PUJetIDEff_Denom->Fill(jetPt_[ijet], jetEta_[ijet]);
      if( isPass_L ) h2_PUJetIDEff_Num_L->Fill(jetPt_[ijet], jetEta_[ijet]);
      if( isPass_M ) h2_PUJetIDEff_Num_M->Fill(jetPt_[ijet], jetEta_[ijet]);
      if( isPass_T ) h2_PUJetIDEff_Num_T->Fill(jetPt_[ijet], jetEta_[ijet]);
    
    }//jet loop
    

  }//lepton == 1 condn

  fStatus++;
   
  return kTRUE;
}


//_____________________________________________________________________________
void PUJetIDEff::SlaveTerminate()
{
  
  Info("SlaveTerminate",
       "sample : %s, year : %d, mode : %s", fSample.Data(), fYear, fMode.Data());

  
  // File closure
  
  for(int ifile=0;ifile<1;ifile++){

    TDirectory *savedir = gDirectory;
    savedir->cd();

    fFile[ifile]->cd();
    
    ///////////////////////////////
    h2_PUJetIDEff_Denom->Write();
    h2_PUJetIDEff_Num_L->Write();
    h2_PUJetIDEff_Num_M->Write();
    h2_PUJetIDEff_Num_T->Write();
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
void PUJetIDEff::Terminate()
{
// function called at the end of the event loop

   if (!fInput) Info("Terminate", "processed %lld events", fProcessed);
   
   TString option = GetOption();
   Info("Terminate", "stopping PUJetIDEff with process option: %s", option.Data());
   
}
