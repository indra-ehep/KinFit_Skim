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
#include "TParticlePDG.h"
#include "TDatabasePDG.h"

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

  if(fYear==2016){  
    
    mu_Pt_cut = 26.;
    ele_Pt_cut = 30.;
    jet_Pt_cut = 25.;
    
    //DeepCSV
    btag_cut_DeepCSVa = 0.6001; 
    btag_cut_DeepCSVb = 0.5847; 
    //DeepJet
    btag_cuta = 0.2598 ; 
    btag_cutb = 0.2489 ; 

  }else if(fYear==2017){

    mu_Pt_cut = 30.;
    ele_Pt_cut = 35.;
    jet_Pt_cut = 25.;

    btag_cut_DeepCSV = 0.4506;
    btag_cut = 0.3040 ;

  }else if(fYear==2018){

    mu_Pt_cut = 26.;
    ele_Pt_cut = 35.;
    jet_Pt_cut = 25.;

    btag_cut_DeepCSV = 0.4168;
    btag_cut = 0.2783 ;

  }
    
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

  Int_t nPtBins = 100; 
  double ptMin = 0;
  double ptMax = 1000;

  Int_t nEtaBins = 50;
  double etaMin = -5;
  double etaMax = 5;

  for(int ifile=0;ifile<1;ifile++){

    TDirectory *savedir = gDirectory;
    savedir->cd();

    fFile[ifile]->cd();
    h2_BTagEff_Denom_b = new TH2D("h2_BTagEff_Denom_b", ";p_{T} [GeV];#eta", nPtBins, ptMin, ptMax, nEtaBins, etaMin, etaMax);
    h2_BTagEff_Denom_c = new TH2D("h2_BTagEff_Denom_c", ";p_{T} [GeV];#eta", nPtBins, ptMin, ptMax, nEtaBins, etaMin, etaMax);
    h2_BTagEff_Denom_udsg = new TH2D("h2_BTagEff_Denom_udsg", ";p_{T} [GeV];#eta", nPtBins, ptMin, ptMax, nEtaBins, etaMin, etaMax);
    //Loose BTag efficiency 2D histos          
    h2_BTagEff_Num_bL = new TH2D("h2_BTagEff_Num_bL", ";p_{T} [GeV];#eta", nPtBins, ptMin, ptMax, nEtaBins, etaMin, etaMax);
    h2_BTagEff_Num_cL = new TH2D("h2_BTagEff_Num_cL", ";p_{T} [GeV];#eta", nPtBins, ptMin, ptMax, nEtaBins, etaMin, etaMax);
    h2_BTagEff_Num_udsgL = new TH2D("h2_BTagEff_Num_udsgL", ";p_{T} [GeV];#eta", nPtBins, ptMin, ptMax, nEtaBins, etaMin, etaMax);
    //Medium BTag efficiency 2D histos          
    h2_BTagEff_Num_bM = new TH2D("h2_BTagEff_Num_bM", ";p_{T} [GeV];#eta", nPtBins, ptMin, ptMax, nEtaBins, etaMin, etaMax);
    h2_BTagEff_Num_cM = new TH2D("h2_BTagEff_Num_cM", ";p_{T} [GeV];#eta", nPtBins, ptMin, ptMax, nEtaBins, etaMin, etaMax);
    h2_BTagEff_Num_udsgM = new TH2D("h2_BTagEff_Num_udsgM", ";p_{T} [GeV];#eta", nPtBins, ptMin, ptMax, nEtaBins, etaMin, etaMax);
    //Tight BTag efficiency 2D histos          
    h2_BTagEff_Num_bT = new TH2D("h2_BTagEff_Num_bT", ";p_{T} [GeV];#eta", nPtBins, ptMin, ptMax, nEtaBins, etaMin, etaMax);
    h2_BTagEff_Num_cT = new TH2D("h2_BTagEff_Num_cT", ";p_{T} [GeV];#eta", nPtBins, ptMin, ptMax, nEtaBins, etaMin, etaMax);
    h2_BTagEff_Num_udsgT = new TH2D("h2_BTagEff_Num_udsgT", ";p_{T} [GeV];#eta", nPtBins, ptMin, ptMax, nEtaBins, etaMin, etaMax);

    h2_CTagEff_Denom_b = new TH2D("h2_CTagEff_Denom_b", ";p_{T} [GeV];#eta", nPtBins, ptMin, ptMax, nEtaBins, etaMin, etaMax);
    h2_CTagEff_Denom_c = new TH2D("h2_CTagEff_Denom_c", ";p_{T} [GeV];#eta", nPtBins, ptMin, ptMax, nEtaBins, etaMin, etaMax);
    h2_CTagEff_Denom_udsg = new TH2D("h2_CTagEff_Denom_udsg", ";p_{T} [GeV];#eta", nPtBins, ptMin, ptMax, nEtaBins, etaMin, etaMax);
    //Loose BTag efficiency 2D histos          
    h2_CTagEff_Num_bL = new TH2D("h2_CTagEff_Num_bL", ";p_{T} [GeV];#eta", nPtBins, ptMin, ptMax, nEtaBins, etaMin, etaMax);
    h2_CTagEff_Num_cL = new TH2D("h2_CTagEff_Num_cL", ";p_{T} [GeV];#eta", nPtBins, ptMin, ptMax, nEtaBins, etaMin, etaMax);
    h2_CTagEff_Num_udsgL = new TH2D("h2_CTagEff_Num_udsgL", ";p_{T} [GeV];#eta", nPtBins, ptMin, ptMax, nEtaBins, etaMin, etaMax);
    //Medium BTag efficiency 2D histos          
    h2_CTagEff_Num_bM = new TH2D("h2_CTagEff_Num_bM", ";p_{T} [GeV];#eta", nPtBins, ptMin, ptMax, nEtaBins, etaMin, etaMax);
    h2_CTagEff_Num_cM = new TH2D("h2_CTagEff_Num_cM", ";p_{T} [GeV];#eta", nPtBins, ptMin, ptMax, nEtaBins, etaMin, etaMax);
    h2_CTagEff_Num_udsgM = new TH2D("h2_CTagEff_Num_udsgM", ";p_{T} [GeV];#eta", nPtBins, ptMin, ptMax, nEtaBins, etaMin, etaMax);
    //Tight BTag efficiency 2D histos          
    h2_CTagEff_Num_bT = new TH2D("h2_CTagEff_Num_bT", ";p_{T} [GeV];#eta", nPtBins, ptMin, ptMax, nEtaBins, etaMin, etaMax);
    h2_CTagEff_Num_cT = new TH2D("h2_CTagEff_Num_cT", ";p_{T} [GeV];#eta", nPtBins, ptMin, ptMax, nEtaBins, etaMin, etaMax);
    h2_CTagEff_Num_udsgT = new TH2D("h2_CTagEff_Num_udsgT", ";p_{T} [GeV];#eta", nPtBins, ptMin, ptMax, nEtaBins, etaMin, etaMax);

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
bool ProcessSkim::CheckTrigFilterVertex()
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
bool ProcessSkim::passEleID(int eleInd, int cutVal, bool doRelisoCut){

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
Bool_t ProcessSkim::Process(Long64_t entry)
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
      bool jetID_pass = (jetID_[jetInd]>=2 and (jetPUID_[jetInd]>=1 or pt>=50.0)) ; //lwp
      bool passDR_lep_jet = true;
      jetR.SetPtEtaPhiM(jetPt_[jetInd], jetEta_[jetInd] , jetPhi_[jetInd], jetMass_[jetInd]);
      if(nofMu==1)
	if ( jetR.DeltaR(mujetR) < 0.4) passDR_lep_jet = false;
      if(nofEle==1)
	if ( jetR.DeltaR(elejetR) < 0.4) passDR_lep_jet = false;
    
      bool jetPresel = (pt >= jet_Pt_cut &&
			TMath::Abs(eta) <= 2.4 &&
			jetID_pass &&
			passDR_lep_jet
			);
      
      if(!jetPresel) continue;
      nljet++;
      // if ( (genIdx>-1) && (genIdx < int(nGenJet_))){
      // 	unsigned int imc = genIdx ;
      // 	// printf("\tJet : Rec:(%2d, %5.2f, %5.2f, %5.2f, %5.2f), Gen:(%2d, %5.2f, %5.2f, %5.2f, %5.2f)\n", 
      // 	//        jetPartFlvr_[jetInd],jetPt_[jetInd], jetEta_[jetInd] , jetPhi_[jetInd], jetMass_[jetInd],  
      // 	//        GenJet_partonFlavour_[genIdx],GenJet_pt_[genIdx], GenJet_eta_[genIdx] , GenJet_phi_[genIdx], GenJet_mass_[genIdx]);
      // 	// if(jetPartFlvr_[jetInd]==GenJet_partonFlavour_[genIdx] and abs(jetPartFlvr_[jetInd])==5 and (jetBtagDeepB_[jetInd] > btag_cut_DeepCSV or jetBtagDeepFlavB_[jetInd] > btag_cut)){
      // 	//   bjetR.SetPtEtaPhiM(jetPt_[jetInd], jetEta_[jetInd] , jetPhi_[jetInd], jetMass_[jetInd]);
      // 	//   bjetG.SetPtEtaPhiM(GenJet_pt_[genIdx], GenJet_eta_[genIdx] , GenJet_phi_[genIdx], GenJet_mass_[genIdx]);
      // 	//   if(bjetR.DeltaR(bjetG)<0.2)
      // 	//     nbjet++;
      // 	// }//b-jet condition
	
      // 	// if(jetPartFlvr_[jetInd]==GenJet_partonFlavour_[genIdx] and ((abs(jetPartFlvr_[jetInd])>=1 and abs(jetPartFlvr_[jetInd])<=4) or abs(jetPartFlvr_[jetInd])==21) ){ //u,d,s,c,g
      // 	//   ljetR.SetPtEtaPhiM(jetPt_[jetInd], jetEta_[jetInd] , jetPhi_[jetInd], jetMass_[jetInd]);
      // 	//   ljetG.SetPtEtaPhiM(GenJet_pt_[genIdx], GenJet_eta_[genIdx] , GenJet_phi_[genIdx], GenJet_mass_[genIdx]);
      // 	//   if(ljetR.DeltaR(ljetG)<0.2)
      // 	//     nljet++;
      // 	// }//l-jet condition
	
      // 	// if(jetPartFlvr_[jetInd]==GenJet_partonFlavour_[genIdx]){ //u,d,s,c,g
      // 	//   ljetR.SetPtEtaPhiM(jetPt_[jetInd], jetEta_[jetInd] , jetPhi_[jetInd], jetMass_[jetInd]);
      // 	//   ljetG.SetPtEtaPhiM(GenJet_pt_[genIdx], GenJet_eta_[genIdx] , GenJet_phi_[genIdx], GenJet_mass_[genIdx]);
      // 	//   if(ljetR.DeltaR(ljetG)<0.2)
      // 	//     nljet++;
      // 	// }//l-jet condition
	
      // }//found the corresponding genjet 
    }//jet loop
    
    // if(nljet < 2 or nbjet < 2) return true;
    if(nljet < 4) return true; // Events with atleast 4 jets

    ////////// Important line ///////////////////////
    bool isDeepCSV = false;
    /////////////////////////////////////////////////
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
	  h2_BTagEff_Denom_b->Fill(jetPt_[ijet], jetEta_[ijet]);
	  if( deepb > deepbL ) h2_BTagEff_Num_bL->Fill(jetPt_[ijet], jetEta_[ijet]);
	  if( deepb > deepbM ) h2_BTagEff_Num_bM->Fill(jetPt_[ijet], jetEta_[ijet]);
	  if( deepb > deepbT ) h2_BTagEff_Num_bT->Fill(jetPt_[ijet], jetEta_[ijet]);

	  h2_CTagEff_Denom_b->Fill(jetPt_[ijet], jetEta_[ijet]);
	  if( deepcvl > deepcvl_L and deepcvb > deepcvb_L ) h2_CTagEff_Num_bL->Fill(jetPt_[ijet], jetEta_[ijet]);
	  if( deepcvl > deepcvl_M and deepcvb > deepcvb_M ) h2_CTagEff_Num_bM->Fill(jetPt_[ijet], jetEta_[ijet]);
	  if( deepcvl > deepcvl_T and deepcvb > deepcvb_T  ) h2_CTagEff_Num_bT->Fill(jetPt_[ijet], jetEta_[ijet]);
	}
	//c-quarks
	else if( abs(partonFlavor)==4 ){
	  //else if( abs(hadronFlavor)==4 ){
	  h2_BTagEff_Denom_c->Fill(jetPt_[ijet], jetEta_[ijet]);
	  if( deepb > deepbL ) h2_BTagEff_Num_cL->Fill(jetPt_[ijet], jetEta_[ijet]);
	  if( deepb > deepbM ) h2_BTagEff_Num_cM->Fill(jetPt_[ijet], jetEta_[ijet]);
	  if( deepb > deepbT ) h2_BTagEff_Num_cT->Fill(jetPt_[ijet], jetEta_[ijet]);

	  h2_CTagEff_Denom_c->Fill(jetPt_[ijet], jetEta_[ijet]);
	  if( deepcvl > deepcvl_L and deepcvb > deepcvb_L ) h2_CTagEff_Num_cL->Fill(jetPt_[ijet], jetEta_[ijet]);
	  if( deepcvl > deepcvl_M and deepcvb > deepcvb_M ) h2_CTagEff_Num_cM->Fill(jetPt_[ijet], jetEta_[ijet]);
	  if( deepcvl > deepcvl_T and deepcvb > deepcvb_T ) h2_CTagEff_Num_cT->Fill(jetPt_[ijet], jetEta_[ijet]);
	}
	//other quarks and gluon
	else{
	  h2_BTagEff_Denom_udsg->Fill(jetPt_[ijet], jetEta_[ijet]);
	  if( deepb > deepbL ) h2_BTagEff_Num_udsgL->Fill(jetPt_[ijet], jetEta_[ijet]);
	  if( deepb > deepbM ) h2_BTagEff_Num_udsgM->Fill(jetPt_[ijet], jetEta_[ijet]);
	  if( deepb > deepbT ) h2_BTagEff_Num_udsgT->Fill(jetPt_[ijet], jetEta_[ijet]);

	  h2_CTagEff_Denom_udsg->Fill(jetPt_[ijet], jetEta_[ijet]);
	  if( deepcvl > deepcvl_L and deepcvb > deepcvb_L ) h2_CTagEff_Num_udsgL->Fill(jetPt_[ijet], jetEta_[ijet]);
	  if( deepcvl > deepcvl_M and deepcvb > deepcvb_M ) h2_CTagEff_Num_udsgM->Fill(jetPt_[ijet], jetEta_[ijet]);
	  if( deepcvl > deepcvl_T and deepcvb > deepcvb_T ) h2_CTagEff_Num_udsgT->Fill(jetPt_[ijet], jetEta_[ijet]);
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
	  h2_BTagEff_Denom_b->Fill(jetPt_[ijet], jetEta_[ijet]);
	  if( deepflavb > deepflavbL ) h2_BTagEff_Num_bL->Fill(jetPt_[ijet], jetEta_[ijet]);
	  if( deepflavb > deepflavbM ) h2_BTagEff_Num_bM->Fill(jetPt_[ijet], jetEta_[ijet]);
	  if( deepflavb > deepflavbT ) h2_BTagEff_Num_bT->Fill(jetPt_[ijet], jetEta_[ijet]);

	  h2_CTagEff_Denom_b->Fill(jetPt_[ijet], jetEta_[ijet]);
	  if( deepflavcvl > deepflavcvl_L and deepflavcvb > deepflavcvb_L ) h2_CTagEff_Num_bL->Fill(jetPt_[ijet], jetEta_[ijet]);
	  if( deepflavcvl > deepflavcvl_M and deepflavcvb > deepflavcvb_M ) h2_CTagEff_Num_bM->Fill(jetPt_[ijet], jetEta_[ijet]);
	  if( deepflavcvl > deepflavcvl_T and deepflavcvb > deepflavcvb_T ) h2_CTagEff_Num_bT->Fill(jetPt_[ijet], jetEta_[ijet]);
	}
	//c-quarks
	else if( abs(partonFlavor)==4 ){
	  //else if( abs(hadronFlavor)==4 ){
	  h2_BTagEff_Denom_c->Fill(jetPt_[ijet], jetEta_[ijet]);
	  if( deepflavb > deepflavbL ) h2_BTagEff_Num_cL->Fill(jetPt_[ijet], jetEta_[ijet]);
	  if( deepflavb > deepflavbM ) h2_BTagEff_Num_cM->Fill(jetPt_[ijet], jetEta_[ijet]);
	  if( deepflavb > deepflavbT ) h2_BTagEff_Num_cT->Fill(jetPt_[ijet], jetEta_[ijet]);

	  h2_CTagEff_Denom_c->Fill(jetPt_[ijet], jetEta_[ijet]);
	  if( deepflavcvl > deepflavcvl_L and deepflavcvb > deepflavcvb_L ) h2_CTagEff_Num_cL->Fill(jetPt_[ijet], jetEta_[ijet]);
	  if( deepflavcvl > deepflavcvl_M and deepflavcvb > deepflavcvb_M ) h2_CTagEff_Num_cM->Fill(jetPt_[ijet], jetEta_[ijet]);
	  if( deepflavcvl > deepflavcvl_T and deepflavcvb > deepflavcvb_T ) h2_CTagEff_Num_cT->Fill(jetPt_[ijet], jetEta_[ijet]);
	}
	//other quarks and gluon
	else{
	  h2_BTagEff_Denom_udsg->Fill(jetPt_[ijet], jetEta_[ijet]);
	  if( deepflavb > deepflavbL ) h2_BTagEff_Num_udsgL->Fill(jetPt_[ijet], jetEta_[ijet]);
	  if( deepflavb > deepflavbM ) h2_BTagEff_Num_udsgM->Fill(jetPt_[ijet], jetEta_[ijet]);
	  if( deepflavb > deepflavbT ) h2_BTagEff_Num_udsgT->Fill(jetPt_[ijet], jetEta_[ijet]);

	  h2_CTagEff_Denom_udsg->Fill(jetPt_[ijet], jetEta_[ijet]);
	  if( deepflavcvl > deepflavcvl_L and deepflavcvb > deepflavcvb_L ) h2_CTagEff_Num_udsgL->Fill(jetPt_[ijet], jetEta_[ijet]);
	  if( deepflavcvl > deepflavcvl_M and deepflavcvb > deepflavcvb_M ) h2_CTagEff_Num_udsgM->Fill(jetPt_[ijet], jetEta_[ijet]);
	  if( deepflavcvl > deepflavcvl_T and deepflavcvb > deepflavcvb_T ) h2_CTagEff_Num_udsgT->Fill(jetPt_[ijet], jetEta_[ijet]);
	}


      }//jet loop

    }
  }//lepton == 1 condn

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
    h2_CTagEff_Denom_b->Write();
    h2_CTagEff_Denom_c->Write();
    h2_CTagEff_Denom_udsg->Write();
    h2_CTagEff_Num_bL->Write();
    h2_CTagEff_Num_cL->Write();
    h2_CTagEff_Num_udsgL->Write();
    h2_CTagEff_Num_bM->Write();
    h2_CTagEff_Num_cM->Write();
    h2_CTagEff_Num_udsgM->Write();
    h2_CTagEff_Num_bT->Write();
    h2_CTagEff_Num_cT->Write();
    h2_CTagEff_Num_udsgT->Write();
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
