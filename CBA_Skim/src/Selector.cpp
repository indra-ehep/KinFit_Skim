#include"../interface/Selector.h"

TRandom* generator = gRandom;

Selector::Selector(){

    isNanoAOD = true;
    
    year = "2016";

    // jets
    jet_Pt_cut = 30.; //Default
    jet_Eta_cut = 2.4;
        
    printEvent = -1;
    IsDebug = false;
    
    looseJetID = false;
    veto_lep_jet_dR = 0.4; // remove jets with a lepton closer than this cut level
    JERsystLevel  = 1;
    JECsystLevel  = 1;
    elesmearLevel = 1;
    elescaleLevel = 1;
    useDeepCSVbTag = false;
    //https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation80XReReco
    // // CSVv2M
    // btag_cut = 0.8484;  
    // DeepJet
    btag_cut = 0.2598 ; 
    // DeepCSV
    btag_cut_DeepCSV = 0.6001;
    
    // whether to invert lepton requirements for 
    QCDselect = false;
    DDselect = false;
    
    // electrons 
    ele_Pt_cut = 35.0; // Default
    ele_Eta_cut = 2.4;
    // electron nanoAOD VETO
    ele_PtLoose_cut = 15.0;
    ele_EtaLoose_cut = 2.4;
    ele_RelIso_tight_EB = 0.0821;
    ele_RelIso_tight_EE = 0.0695;
    ele_RelIso_loose_EB = 0.175;
    ele_RelIso_loose_EE = 0.159;
    
    // muons nanoAOD 
    mu_Pt_cut = 30; // Default
    mu_Eta_tight = 2.4;
    mu_RelIso_tight = 0.15;
    // muons nanoAOD VETO
    mu_PtLoose_cut = 15.0;
    mu_Eta_loose = 2.4;
    mu_RelIso_loose = 0.25;
    
    mu_Iso_invert = false;
    //smearJetPt = true; // Deafult
    smearJetPt = false;
    smearEle = true;
    scaleEle = true;
    
    ///////// MiniAOD ///////////////////
    //muons miniAOD MEDIUM
    mu_Pt_cut_miniAOD = 26.0;
    s = 0 ;
    m = 0;
    isPreVFP = false ; isPostVFP = false ;

    //electron miniAOD MEDIUM
    ele_Pt_cut_miniAOD = 30.0;
    ele_Eta_cut_miniAOD = 2.5;
    ele_muon_dR_miniAOD = 0.4;

    //jets miniAOD
    looseJetID_miniAOD = true;
    jet_Pt_cut_miniAOD = 25.; 
    jet_Eta_cut_miniAOD = 2.4;
    veto_lep_jet_dR_miniAOD = 0.4;
    ////////////////////////////////////
    
    //met defaults
    METPt  = -9999;
    METPhi  = -9999;
    METUnc = 1.0;
    selectMETUnc = false;

  
}

void Selector::init_JER(std::string inputPrefix){
  
    // jetResolution = new JME::JetResolution((inputPrefix+"_MC_PtResolution_AK4PFchs.txt").c_str());
    // jetResolutionScaleFactor = new JME::JetResolutionScaleFactor((inputPrefix+"_MC_SF_AK4PFchs.txt").c_str());
  if(year=="2016"){
    jetResolutiona = new JME::JetResolution((inputPrefix+"/preVFP_JRV3/Summer20UL16APV_JRV3_MC_PtResolution_AK4PFchs.txt").c_str());
    jetResolutionScaleFactora = new JME::JetResolutionScaleFactor((inputPrefix+"/preVFP_JRV3/Summer20UL16APV_JRV3_MC_SF_AK4PFchs.txt").c_str());

    jetResolutionb = new JME::JetResolution((inputPrefix+"/postVFP_JRV3/Summer20UL16_JRV3_MC_PtResolution_AK4PFchs.txt").c_str());
    jetResolutionScaleFactorb = new JME::JetResolutionScaleFactor((inputPrefix+"/postVFP_JRV3/Summer20UL16_JRV3_MC_SF_AK4PFchs.txt").c_str());
  }else{
    jetResolution = new JME::JetResolution((inputPrefix+"_MC_PtResolution_AK4PFchs.txt").c_str());
    jetResolutionScaleFactor = new JME::JetResolutionScaleFactor((inputPrefix+"_MC_SF_AK4PFchs.txt").c_str());
  }
    //jetParam = new JME::JetParameters();

    // cout << "INIT JER" << endl;
    // JERParam = new JetCorrectorParameters((inputPrefix+"_MC_PtResolution_AK4PFchs.txt").c_str());
    // cout << "INIT JER" << endl;
    // std::vector<JetCorrectorParameters> vPar;
    // cout << "INIT JER" << endl;
    // vPar.push_back(*JERParam);
    // cout << "INIT JER" << endl;
    // JetCorrector = new FactorizedJetCorrector(vPar);
    // cout << "INIT JER" << endl;

    // cout << JetCorrector << endl;
}

void Selector::init_RoccoR(std::string path)
{
  rc16 = RoccoR(Form("%s/weight/RoccoR/RoccoR2016.txt",path.c_str()));
  rc16a = RoccoR(Form("%s/weightUL/RoccoR/RoccoR2016aUL.txt",path.c_str()));
  rc16b = RoccoR(Form("%s/weightUL/RoccoR/RoccoR2016bUL.txt",path.c_str()));
  rc17 = RoccoR(Form("%s/weightUL/RoccoR/RoccoR2017UL.txt",path.c_str()));
  rc18 = RoccoR(Form("%s/weightUL/RoccoR/RoccoR2018UL.txt",path.c_str()));

  if(IsDebug) Info("Selector::init_RoccoR","Rochester correction files loaded.");
}

void Selector::process_objects(string path, EventTree* inp_tree){
    tree = inp_tree;
    clear_vectors();
    if(IsDebug) Info("Selector::process_objects","Cleared vectors");
        
}

void Selector::clear_vectors(){

    Electrons.clear();
    ElectronsLoose.clear();
    ElectronsMedium.clear();
    ElectronsNoIso.clear();
    ElectronsNoIsoLoose.clear();

    Muons.clear();
    MuonsLoose.clear();
    MuonsNoIso.clear();
    MuonsNoIsoLoose.clear();
    MuonsMiniAOD.clear();

    Jets.clear();
    bJets.clear();
    FwdJets.clear();

    MuRelIso_corr.clear();
    // JetsJERPt.clear();
    // JetsPreSelPt.clear();;
    // JetsCleaningPt.clear();;
    // JetsPreSel.clear();;
    // JetsCleaning.clear();;
    JetsPtSmeared.clear();
    jet_resolution.clear();
    jet_isTagged.clear();

    JetsNoCorr.clear();

    nEleSelIso = 0;
    nMuSelIso = 0;
}

void Selector::filter_electrons(EventTree *event){
  
  tree = event;

  for(int eleInd = 0; eleInd < int(tree->nEle_) and int(tree->nEle_) <= 20 ; ++eleInd){
    //20 is the arraysize for electron as defined in EventTree.h

    double eta = tree->eleEta_[eleInd];
    double absEta = TMath::Abs(eta);
    double phi = tree->elePhi_[eleInd];
    double SCeta = eta + tree->eleDeltaEtaSC_[eleInd];
    double absSCEta = TMath::Abs(SCeta);
	
    double pt = tree->elePt_[eleInd];
        
    // // EA subtraction
    double PFrelIso_corr = tree->elePFRelIso_[eleInd];
    
    // uint eleID = tree->eleIDcutbased_[eleInd];
    // bool passVetoID   = eleID >= 1;
    // bool passLooseID  = eleID >= 2;
    // bool passMediumID = eleID >= 3;
    // bool passTightID  = eleID >= 4;
    
    bool passMVALooseID = tree->eleIDmvaLoose_[eleInd];
    bool passMVAWP80ID = tree->eleIDmvaWP80_[eleInd];
    bool passMVAWP90ID = tree->eleIDmvaWP90_[eleInd];
    
    bool passRelIsoSel = ((absSCEta < 1.479 && PFrelIso_corr < ele_RelIso_tight_EB) ||
			   (absSCEta > 1.479 && PFrelIso_corr < ele_RelIso_tight_EE));
    bool passRelIsoVeto = ((absSCEta < 1.479 && PFrelIso_corr < ele_RelIso_loose_EB) ||
			   (absSCEta > 1.479 && PFrelIso_corr < ele_RelIso_loose_EE));
    
    // make sure it doesn't fall within the gap
    bool passEtaEBEEGap = (absSCEta < 1.4442) || (absSCEta > 1.566);
	
    // D0 and Dz cuts are different for barrel and endcap
    bool passD0 = ((absSCEta < 1.479 && TMath::Abs(tree->eleD0_[eleInd]) < 0.05) ||
		   (absSCEta > 1.479 && TMath::Abs(tree->eleD0_[eleInd]) < 0.1));
    bool passDz = ((absSCEta < 1.479 && TMath::Abs(tree->eleDz_[eleInd]) < 0.1) ||
		   (absSCEta > 1.479 && TMath::Abs(tree->eleDz_[eleInd]) < 0.2));
        
        
    // bool eleSel = (passEtaEBEEGap && 
    // 		   absSCEta <= ele_Eta_cut &&
    // 		   pt >= ele_Pt_cut &&
    // 		   passMediumID &&
    // 		   passD0 &&
    // 		   passDz);
	
    // bool looseSel = ( passEtaEBEEGap && 
    // 		      absSCEta <= ele_EtaLoose_cut &&
    // 		      pt >= ele_PtLoose_cut &&
    // 		      passVetoID &&
    // 		      passD0 &&
    // 		      passDz);
    
    bool eleSel = (passEtaEBEEGap && 
		   absSCEta <= ele_Eta_cut &&
		   pt >= ele_Pt_cut &&
		   //passMVAWP80ID &&
		   passMVAWP90ID &&
		   passD0 &&
		   passDz);
	
    bool looseSel = ( passEtaEBEEGap && 
		      absSCEta <= ele_EtaLoose_cut &&
		      pt >= ele_PtLoose_cut &&
		      passMVALooseID &&
		      passRelIsoVeto &&
		      passD0 &&
		      passDz);
	

    if( eleSel ){
      Electrons.push_back(eleInd);
      if(passRelIsoSel) nEleSelIso++ ;
    }else if( looseSel ){ 
      ElectronsLoose.push_back(eleInd);
    }
  }//ele loop

    
}

void Selector::filter_muons(EventTree *event){
  
  tree = event;
  
  for(int muInd = 0; muInd < int(tree->nMuon_) and int(tree->nMuon_) <= 15; ++muInd){
    //15 is the arraysize for muon as defined in EventTree.h
    
    float eta = tree->muEta_[muInd];
    float pt = tree->muPt_[muInd];
    float phi = tree->muPhi_[muInd];
    int nTrackerLayers = tree->munTrackerLayers_[muInd];
    int charge =  tree->muCharge_[muInd];
    float mudxy = tree->mudxy_[muInd];
    float mudz = tree->mudz_[muInd];

    //Protection for crash during RochCorr
    if(TMath::Abs(charge)!=1 or nTrackerLayers>=20 or nTrackerLayers<0
       or !(TMath::Finite(eta)) or !(TMath::Finite(pt)) or !(TMath::Finite(phi))
       or TMath::Abs(mudxy)>=0.2 or TMath::Abs(mudz)>=0.5) continue; 
    //max nTrackerLayers should be 18 as seen in data and MC
    
    double SFRochCorr = 1.0;
    if(!TMath::AreEqualAbs(eta,0.0,1.0e-7) and !TMath::AreEqualAbs(pt,0.0,1.0e-7) and !TMath::AreEqualAbs(phi,0.0,1.0e-7)){
      if (tree->isData_){
	if(year=="2016"){
	  if(isPreVFP)
	    SFRochCorr *= rc16a.kScaleDT(charge, pt, eta, phi);
	  if(isPostVFP)
	    SFRochCorr *= rc16b.kScaleDT(charge, pt, eta, phi);
	}else if(year=="2017"){
	  SFRochCorr *= rc17.kScaleDT(charge, pt, eta, phi);
	}else if(year=="2018"){
	  SFRochCorr *= rc18.kScaleDT(charge, pt, eta, phi);
	}
      }else{
	int genIdx = tree->muGenPartIdx_[muInd];
	
	if ( (genIdx>-1) && (genIdx < int(tree->nGenPart_))){
	  double genPt = tree->GenPart_pt_[genIdx];
	  //cout << "rec PT " << pt << ", Gen PT " << genPt << endl;
	  if(year=="2016"){
	    if(isPreVFP)
	      SFRochCorr *= rc16a.kSpreadMC(charge, pt, eta, phi, genPt);
	    if(isPostVFP)
	      SFRochCorr *= rc16b.kSpreadMC(charge, pt, eta, phi, genPt);	
	  }else if(year=="2017"){
	    SFRochCorr *= rc17.kSpreadMC(charge, pt, eta, phi, genPt);	
	  }else if(year=="2018"){
	    SFRochCorr *= rc18.kSpreadMC(charge, pt, eta, phi, genPt);	
	  }
	}else{
	  if(year=="2016"){
	    if(isPreVFP)
	      SFRochCorr *= rc16a.kSmearMC(charge, pt, eta, phi, nTrackerLayers, generator->Rndm());
	    if(isPostVFP)
	      SFRochCorr *= rc16b.kSmearMC(charge, pt, eta, phi, nTrackerLayers, generator->Rndm());	
	  }else if(year=="2017"){
	    SFRochCorr *= rc17.kSmearMC(charge, pt, eta, phi, nTrackerLayers, generator->Rndm());	
	  }else if(year=="2018"){
	    SFRochCorr *= rc18.kSmearMC(charge, pt, eta, phi, nTrackerLayers, generator->Rndm());	
	  }	  
	}//if GenPart

      }//is Data or MC
    }
    tree->muRoccoR_[muInd] = SFRochCorr;
    pt = pt*SFRochCorr;
    
    double PFrelIso_corr = tree->muPFRelIso_[muInd];
    
    //bool vetoMuonID = tree->muIsPFMuon_[muInd] && (tree->muIsTracker_[muInd] || tree->muIsGlobal_[muInd]);
    //bool mediumMuonID = tree->muMediumId_[muInd];
    bool looseMuonID = tree->muLooseId_[muInd]; //This is same as veto condition defined above
    bool mediumPromptMuonID = tree->muMediumPromptId_[muInd];
    bool tightMuonID = tree->muTightId_[muInd];
    
    bool muSel = (TMath::Abs(eta) <= mu_Eta_tight &&
		  pt >= mu_Pt_cut &&
		  //tightMuonID
		  mediumPromptMuonID 
		  //mediumMuonID 
		  );
    
    bool passLoose = (TMath::Abs(eta) <= mu_Eta_loose &&
		      pt >= mu_PtLoose_cut &&
		      looseMuonID &&
		      PFrelIso_corr < mu_RelIso_loose);
    
    if(muSel){
      Muons.push_back(muInd);
      if(PFrelIso_corr<mu_RelIso_tight) nMuSelIso++;
    }else if (passLoose){
      MuonsLoose.push_back(muInd);
    }
    
  }//muon loop
}


void Selector::filter_jets(){
  
  for(int jetInd = 0; jetInd < int(tree->nJet_) and int(tree->nJet_) <= 200 ; ++jetInd){ //200 is the array size for jets as defined in EventTree 
    
    double pt = tree->jetPt_[jetInd];
    double eta = tree->jetEta_[jetInd];
    double phi = tree->jetPhi_[jetInd];
    double smearedpt = tree->jetPt_[jetInd];

    if(pt<=jet_Pt_cut) continue;

    //Applied for Legacy Rereco
    // //tight ID for 2016 (bit 0), tightLeptVeto for 2017 (bit 1)
    // int jetID_cutBit = 1;
    // //if (year=="2016"){ jetID_cutBit = 0; }
    // bool jetID_pass = (tree->jetID_[jetInd]>>0 & 1 && looseJetID) || (tree->jetID_[jetInd]>>jetID_cutBit & 1);
    
    //Default applied for LRR
    //bool jetID_pass = (tree->jetID_[jetInd]>=2) ;    
    //Applied for UL
    //bool jetID_pass = (tree->jetID_[jetInd]>=2) ;    
    //Applied for UL
    //bool jetID_pass = (tree->jetID_[jetInd]>=2 and (tree->jetPUID_[jetInd]>=1 or pt>=50.0)) ; //lwp
    //tight PU
    //bool jetID_pass = (tree->jetID_[jetInd]>=2 and (tree->jetPUID_[jetInd]>=7 or pt>=50.0)) ; //twp
    //TLV only
    bool jetID_pass = (tree->jetID_[jetInd]>=6 and (tree->jetPUID_[jetInd]>=1 or pt>=50.0)) ; //twp
    //Tightmost test
    //bool jetID_pass = (tree->jetID_[jetInd]>=6 and (tree->jetPUID_[jetInd]>=7 or pt>=50.0)) ; //twp
    
    
    double jetSF = 1.;

    double resolution = 0.;
    if (!tree->isData_){
      jetParam.setJetEta(tree->jetEta_[jetInd]);
      jetParam.setJetPt(tree->jetPt_[jetInd]);
      jetParam.setJetArea(tree->jetArea_[jetInd]);
      jetParam.setRho(tree->rho_);
      if(year=="2016"){
	if(isPreVFP){
	  resolution = jetResolutiona->getResolution(jetParam);  
	  if (JERsystLevel==1) jetSF = jetResolutionScaleFactora->getScaleFactor(jetParam,Variation::NOMINAL);
	  if (JERsystLevel==0) jetSF = jetResolutionScaleFactora->getScaleFactor(jetParam,Variation::DOWN);
	  if (JERsystLevel==2) jetSF = jetResolutionScaleFactora->getScaleFactor(jetParam,Variation::UP);
	}
	if(isPostVFP){
	  resolution = jetResolutionb->getResolution(jetParam);  
	  if (JERsystLevel==1) jetSF = jetResolutionScaleFactorb->getScaleFactor(jetParam,Variation::NOMINAL);
	  if (JERsystLevel==0) jetSF = jetResolutionScaleFactorb->getScaleFactor(jetParam,Variation::DOWN);
	  if (JERsystLevel==2) jetSF = jetResolutionScaleFactorb->getScaleFactor(jetParam,Variation::UP);
	}
      }else{
	
	resolution = jetResolution->getResolution(jetParam);  
	if (JERsystLevel==1) jetSF = jetResolutionScaleFactor->getScaleFactor(jetParam,Variation::NOMINAL);
	if (JERsystLevel==0) jetSF = jetResolutionScaleFactor->getScaleFactor(jetParam,Variation::DOWN);
	if (JERsystLevel==2) jetSF = jetResolutionScaleFactor->getScaleFactor(jetParam,Variation::UP);

      }
      double jetSmear = 1.;
      
      if(IsDebug) 
	cout << "\t genID : " << tree->jetGenJetIdx_[jetInd] << ", ngenjet : " << int(tree->nGenJet_) << ", recojet : " << int(tree->nJet_) <<  endl;
      
      int genIdx = tree->jetGenJetIdx_[jetInd];
      
      if ( (genIdx>-1) && (genIdx < int(tree->nGenJet_))){
      	double genJetPt = tree->GenJet_pt_[genIdx];
      	jetSmear = 1. + (jetSF - 1.) * (pt - genJetPt)/pt;
      }else{
      	jetSmear = 1 + generator->Gaus(0, resolution) * sqrt( max(jetSF*jetSF - 1, 0.) );
      }
      
      smearedpt = pt*jetSmear;
      
      if (smearJetPt) // Default
	pt = pt*jetSmear;
      
    }//isMC

    bool passDR_lep_jet = true;

    //loop over selected electrons
    for(std::vector<int>::const_iterator eleInd = Electrons.begin(); eleInd != Electrons.end(); eleInd++) 
      if (dR(eta, phi, tree->eleEta_[*eleInd], tree->elePhi_[*eleInd]) < veto_lep_jet_dR) passDR_lep_jet = false;
    
    //loop over selected muons
    for(std::vector<int>::const_iterator muInd = Muons.begin(); muInd != Muons.end(); muInd++) 
      if (dR(eta, phi, tree->muEta_[*muInd], tree->muPhi_[*muInd]) < veto_lep_jet_dR) passDR_lep_jet = false;
    
    bool jetSel = (TMath::Abs(eta) <= jet_Eta_cut &&
		   pt >= jet_Pt_cut &&
		   jetID_pass &&
		   passDR_lep_jet);
    
    if( jetSel ){
      Jets.push_back(jetInd);
      JetsPtSmeared.push_back(smearedpt);
      //jet_resolution.push_back(resolution);
      jet_resolution.push_back(jetSF);
      if (!useDeepCSVbTag){
	//if( tree->jetBtagCSVV2_[jetInd] > btag_cut){
	if( tree->jetBtagDeepFlavB_[jetInd] > btag_cut){
	  bJets.push_back(jetInd);
	  jet_isTagged.push_back(true);
	} else {
	  jet_isTagged.push_back(false);
	}
      } else {
	if( tree->jetBtagDeepB_[jetInd] > btag_cut_DeepCSV){
	  bJets.push_back(jetInd);
	  jet_isTagged.push_back(true);
	} else {
	  jet_isTagged.push_back(false);
	}
      }		
    }//presel condition
    
  }//main jet loop 
  
}

void Selector::filter_jetsNoCorr(){
  
  
  for(int jetInd = 0; jetInd < int(tree->nJet_) and int(tree->nJet_) <= 200 ; ++jetInd){
    
    double pt = tree->jetPt_[jetInd];
    double eta = tree->jetEta_[jetInd];
    double phi = tree->jetPhi_[jetInd];
    
    //Default applied for LRR
    //bool jetID_pass = (tree->jetID_[jetInd]>=2) ;    
    //bool jetID_pass = (tree->jetID_[jetInd]>=2 and (tree->jetPUID_[jetInd]>=1 or pt>=50.0)) ; //loose wp
    //TLV only
    bool jetID_pass = (tree->jetID_[jetInd]>=6 and (tree->jetPUID_[jetInd]>=1 or pt>=50.0)) ; //twp

    if(IsDebug) Info("Selector::filter_jetsNoCorr","applied filter");
    //////////////////////////////////////////////// NanoAOD selection //////////////////////////////////////////////////////////
    bool passDR_lep_jet = true;
    //loop over selected electrons
    for(std::vector<int>::const_iterator eleInd = Electrons.begin(); eleInd != Electrons.end(); eleInd++) 
      if (dR(eta, phi, tree->eleEta_[*eleInd], tree->elePhi_[*eleInd]) < veto_lep_jet_dR) passDR_lep_jet = false;

    //loop over selected muons
    for(std::vector<int>::const_iterator muInd = Muons.begin(); muInd != Muons.end(); muInd++) 
      if (dR(eta, phi, tree->muEta_[*muInd], tree->muPhi_[*muInd]) < veto_lep_jet_dR) passDR_lep_jet = false;
      
    bool jetPresel = (pt >= jet_Pt_cut and TMath::Abs(eta) <= jet_Eta_cut and jetID_pass and passDR_lep_jet);
    if(IsDebug) Info("Selector::filter_jetsNoCorr","Processed nano");
    //////////////////////////////////////////////// NanoAOD selection //////////////////////////////////////////////////////////
    
    if( jetPresel ){
      JetsNoCorr.push_back(jetInd);
    }//presel condition

  }//main jet loop 
    
}


void Selector::filter_mets(){
  
  TLorentzVector MET;
  MET.SetPtEtaPhiM(tree->MET_pt_, 0., tree->MET_phi_, 0.);
  
  TVector3 jet, jetSmeared;
  double metX = MET.Px(); 
  double metY = MET.Py();
  if (!tree->isData_){
    for (unsigned int ijet = 0; ijet < JetsNoCorr.size(); ijet++){		
      int jetInd = JetsNoCorr.at(ijet);
      double pt = tree->jetPt_[jetInd];
      double eta = tree->jetEta_[jetInd];
      double phi = tree->jetPhi_[jetInd];

      jetParam.setJetEta(tree->jetEta_[jetInd]);
      jetParam.setJetPt(tree->jetPt_[jetInd]);
      jetParam.setJetArea(tree->jetArea_[jetInd]);
      jetParam.setRho(tree->rho_);
      double resolution = 1.0;
      double jetSF = 1.0;
      
      if(year=="2016"){
	if(isPreVFP){
	  resolution = jetResolutiona->getResolution(jetParam);  
	  if (JERsystLevel==1) jetSF = jetResolutionScaleFactora->getScaleFactor(jetParam,Variation::NOMINAL);
	  if (JERsystLevel==0) jetSF = jetResolutionScaleFactora->getScaleFactor(jetParam,Variation::DOWN);
	  if (JERsystLevel==2) jetSF = jetResolutionScaleFactora->getScaleFactor(jetParam,Variation::UP);
	}
	if(isPostVFP){
	  resolution = jetResolutionb->getResolution(jetParam);  
	  if (JERsystLevel==1) jetSF = jetResolutionScaleFactorb->getScaleFactor(jetParam,Variation::NOMINAL);
	  if (JERsystLevel==0) jetSF = jetResolutionScaleFactorb->getScaleFactor(jetParam,Variation::DOWN);
	  if (JERsystLevel==2) jetSF = jetResolutionScaleFactorb->getScaleFactor(jetParam,Variation::UP);
	}
      }else{
	
	resolution = jetResolution->getResolution(jetParam);  
	if (JERsystLevel==1) jetSF = jetResolutionScaleFactor->getScaleFactor(jetParam,Variation::NOMINAL);
	if (JERsystLevel==0) jetSF = jetResolutionScaleFactor->getScaleFactor(jetParam,Variation::DOWN);
	if (JERsystLevel==2) jetSF = jetResolutionScaleFactor->getScaleFactor(jetParam,Variation::UP);

      }

      
      int genIdx = tree->jetGenJetIdx_[jetInd];
      double jetSmear = 1.0 ;
      if ( (genIdx>-1) && (genIdx < int(tree->nGenJet_))){
      	double genJetPt = tree->GenJet_pt_[genIdx];
      	jetSmear = 1. + (jetSF - 1.) * (pt - genJetPt)/pt;
      }else{
      	jetSmear = 1 + generator->Gaus(0, resolution) * sqrt( max(jetSF*jetSF - 1, 0.) );
      }
      
      jet.SetPtEtaPhi(pt,eta,phi);
      jetSmeared.SetPtEtaPhi(jetSmear*pt,eta,phi);
      
      metX += jet.Px(); 
      metY += jet.Py(); 

      metX -= jetSmeared.Px();
      metY -= jetSmeared.Py();

    }
  }//isMC
  
  MET.SetXYZM(metX, metY, 0., 0.);
  
  METPt  = MET.Pt();
  METPhi = MET.Phi();

  
}



void Selector::metWithUncl()
{

  TLorentzVector MET;
  //MET.SetPtEtaPhiM(tree->MET_pt_, 0., tree->MET_phi_, 0.);
  MET.SetPtEtaPhiM(METPt, 0., METPhi, 0.);

  double metX = MET.Px(); 
  double metY = MET.Py();

  if (!tree->isData_){

    TVector3 jet; 
    for (unsigned int ijet = 0; ijet < JetsNoCorr.size(); ijet++){		
      int jetInd = JetsNoCorr.at(ijet);
      double pt = tree->jetPt_[jetInd];
      double eta = tree->jetEta_[jetInd];
      double phi = tree->jetPhi_[jetInd];
      
      jet.SetPtEtaPhi(pt,eta,phi);
      
      metX += jet.Px(); 
      metY += jet.Py(); 
    }

    //loop over selected muons
    TVector3 muon; 
    for(std::vector<int>::const_iterator muInd = Muons.begin(); muInd != Muons.end(); muInd++) {
      muon.SetPtEtaPhi(tree->muPt_[*muInd], tree->muEta_[*muInd], tree->muPhi_[*muInd]);
      metX += muon.Px(); 
      metY += muon.Py(); 
    }

    //loop over selected electrons
    TVector3 electron; 
    for(std::vector<int>::const_iterator eleInd = Electrons.begin(); eleInd != Electrons.end(); eleInd++) {
      electron.SetPtEtaPhi(tree->elePt_[*eleInd], tree->eleEta_[*eleInd], tree->elePhi_[*eleInd]);
      metX += electron.Px(); 
      metY += electron.Py(); 	
    }
    
    metX *= (1 + METUnc*0.1); //vary by 10%
    metY *= (1 + METUnc*0.1);

    //loop over selected electrons
    for(std::vector<int>::const_iterator eleInd = Electrons.begin(); eleInd != Electrons.end(); eleInd++) {
      electron.SetPtEtaPhi(tree->elePt_[*eleInd], tree->eleEta_[*eleInd], tree->elePhi_[*eleInd]);
      metX -= electron.Px(); 
      metY -= electron.Py(); 	
    }

    for(std::vector<int>::const_iterator muInd = Muons.begin(); muInd != Muons.end(); muInd++) {
      muon.SetPtEtaPhi(tree->muPt_[*muInd], tree->muEta_[*muInd], tree->muPhi_[*muInd]);
      metX -= muon.Px(); 
      metY -= muon.Py(); 
    }
    
    for (unsigned int ijet = 0; ijet < JetsNoCorr.size(); ijet++){		
      int jetInd = JetsNoCorr.at(ijet);
      double pt = tree->jetPt_[jetInd];
      double eta = tree->jetEta_[jetInd];
      double phi = tree->jetPhi_[jetInd];
      
      jet.SetPtEtaPhi(pt,eta,phi);
      
      metX -= jet.Px(); 
      metY -= jet.Py(); 
    }
    
  }//isMC

  MET.SetXYZM(metX, metY, 0., 0.);
  
  METPt  = MET.Pt();
  METPhi = MET.Phi();

}

// Code from https://lathomas.web.cern.ch/lathomas/METStuff/XYCorrections/XYMETCorrection_withUL17andUL18andUL16.h
//_____________________________________________________________________________
// enum TheRunEra{
//   y2016B,y2016C,y2016D,y2016E,y2016F,y2016G,y2016H,
//   y2017B,y2017C,y2017D,y2017E,y2017F,
//   y2018A,y2018B,y2018C,y2018D,
//   y2016MC,
//   y2017MC,
//   y2018MC,
//   yUL2016B,yUL2016C,yUL2016D,yUL2016E,yUL2016F,yUL2016Flate,yUL2016G,yUL2016H,
//   yUL2017B,yUL2017C,yUL2017D,yUL2017E,yUL2017F,
//   yUL2018A,yUL2018B,yUL2018C,yUL2018D,
//   yUL2016MCAPV,
//   yUL2016MCnonAPV,
//   yUL2017MC,
//   yUL2018MC
// };

std::pair<double,double> Selector::METXYCorr_Met_MetPhi(double uncormet, double uncormet_phi, int runnb, TString year, bool isMC, int npv, bool isUL =false,bool ispuppi=false){

  std::pair<double,double>  TheXYCorr_Met_MetPhi(uncormet,uncormet_phi);
  
  if(npv>100) npv=100;
  int runera =-1;
  bool usemetv2 =false;
  if(isMC && year == "2016" && !isUL) runera = y2016MC;
  else if(isMC && year == "2017" && !isUL) {runera = y2017MC; usemetv2 =true;}
  else if(isMC && year == "2018" && !isUL) runera = y2018MC;
  else if(isMC && year == "2016APV" && isUL) runera = yUL2016MCAPV;
  else if(isMC && year == "2016nonAPV" && isUL) runera = yUL2016MCnonAPV;
  else if(isMC && year == "2017" && isUL) runera = yUL2017MC;
  else if(isMC && year == "2018" && isUL) runera = yUL2018MC;
  
  
  else if(!isMC && runnb >=272007 && runnb <=275376 && !isUL) runera = y2016B;
  else if(!isMC && runnb >=275657 && runnb <=276283 && !isUL) runera = y2016C;
  else if(!isMC && runnb >=276315 && runnb <=276811 && !isUL) runera = y2016D;
  else if(!isMC && runnb >=276831 && runnb <=277420 && !isUL) runera = y2016E;
  else if(!isMC && runnb >=277772 && runnb <=278808 && !isUL) runera = y2016F;
  else if(!isMC && runnb >=278820 && runnb <=280385 && !isUL) runera = y2016G;
  else if(!isMC && runnb >=280919 && runnb <=284044 && !isUL) runera = y2016H;
  
  else if(!isMC && runnb >=297020 && runnb <=299329 && !isUL){ runera = y2017B; usemetv2 =true;}
  else if(!isMC && runnb >=299337 && runnb <=302029 && !isUL){ runera = y2017C; usemetv2 =true;}
  else if(!isMC && runnb >=302030 && runnb <=303434 && !isUL){ runera = y2017D; usemetv2 =true;}
  else if(!isMC && runnb >=303435 && runnb <=304826 && !isUL){ runera = y2017E; usemetv2 =true;}
  else if(!isMC && runnb >=304911 && runnb <=306462 && !isUL){ runera = y2017F; usemetv2 =true;}
  
  else if(!isMC && runnb >=315252 && runnb <=316995 && !isUL) runera = y2018A;
  else if(!isMC && runnb >=316998 && runnb <=319312 && !isUL) runera = y2018B;
  else if(!isMC && runnb >=319313 && runnb <=320393 && !isUL) runera = y2018C;
  else if(!isMC && runnb >=320394 && runnb <=325273 && !isUL) runera = y2018D;

  else if(!isMC && runnb >=315252 && runnb <=316995 && isUL) runera = yUL2018A;
  else if(!isMC && runnb >=316998 && runnb <=319312 && isUL) runera = yUL2018B;
  else if(!isMC && runnb >=319313 && runnb <=320393 && isUL) runera = yUL2018C;
  else if(!isMC && runnb >=320394 && runnb <=325273 && isUL) runera = yUL2018D;

  else if(!isMC && runnb >=297020 && runnb <=299329 && isUL){ runera = yUL2017B; usemetv2 =false;}
  else if(!isMC && runnb >=299337 && runnb <=302029 && isUL){ runera = yUL2017C; usemetv2 =false;}
  else if(!isMC && runnb >=302030 && runnb <=303434 && isUL){ runera = yUL2017D; usemetv2 =false;}
  else if(!isMC && runnb >=303435 && runnb <=304826 && isUL){ runera = yUL2017E; usemetv2 =false;}
  else if(!isMC && runnb >=304911 && runnb <=306462 && isUL){ runera = yUL2017F; usemetv2 =false;}

  else if(!isMC && runnb >=272007 && runnb <=275376 && isUL) runera = yUL2016B;
  else if(!isMC && runnb >=275657 && runnb <=276283 && isUL) runera = yUL2016C;
  else if(!isMC && runnb >=276315 && runnb <=276811 && isUL) runera = yUL2016D;
  else if(!isMC && runnb >=276831 && runnb <=277420 && isUL) runera = yUL2016E;
  else if(!isMC && ((runnb >=277772 && runnb <=278768) || runnb==278770) && isUL) runera = yUL2016F;
  else if(!isMC && ((runnb >=278801 && runnb <=278808) || runnb==278769) && isUL) runera = yUL2016Flate;
  else if(!isMC && runnb >=278820 && runnb <=280385 && isUL) runera = yUL2016G;
  else if(!isMC && runnb >=280919 && runnb <=284044 && isUL) runera = yUL2016H;


  else {
    //Couldn't find data/MC era => no correction applied
    return TheXYCorr_Met_MetPhi;
  }
  
  double METxcorr(0.),METycorr(0.);

  if(!usemetv2){//Current recommendation for 2016 and 2018
    if(!ispuppi){
      if(runera==y2016B) METxcorr = -(-0.0478335*npv -0.108032);
      if(runera==y2016B) METycorr = -(0.125148*npv +0.355672);
      if(runera==y2016C) METxcorr = -(-0.0916985*npv +0.393247);
      if(runera==y2016C) METycorr = -(0.151445*npv +0.114491);
      if(runera==y2016D) METxcorr = -(-0.0581169*npv +0.567316);
      if(runera==y2016D) METycorr = -(0.147549*npv +0.403088);
      if(runera==y2016E) METxcorr = -(-0.065622*npv +0.536856);
      if(runera==y2016E) METycorr = -(0.188532*npv +0.495346);
      if(runera==y2016F) METxcorr = -(-0.0313322*npv +0.39866);
      if(runera==y2016F) METycorr = -(0.16081*npv +0.960177);
      if(runera==y2016G) METxcorr = -(0.040803*npv -0.290384);
      if(runera==y2016G) METycorr = -(0.0961935*npv +0.666096);
      if(runera==y2016H) METxcorr = -(0.0330868*npv -0.209534);
      if(runera==y2016H) METycorr = -(0.141513*npv +0.816732);
      if(runera==y2017B) METxcorr = -(-0.259456*npv +1.95372);
      if(runera==y2017B) METycorr = -(0.353928*npv -2.46685);
      if(runera==y2017C) METxcorr = -(-0.232763*npv +1.08318);
      if(runera==y2017C) METycorr = -(0.257719*npv -1.1745);
      if(runera==y2017D) METxcorr = -(-0.238067*npv +1.80541);
      if(runera==y2017D) METycorr = -(0.235989*npv -1.44354);
      if(runera==y2017E) METxcorr = -(-0.212352*npv +1.851);
      if(runera==y2017E) METycorr = -(0.157759*npv -0.478139);
      if(runera==y2017F) METxcorr = -(-0.232733*npv +2.24134);
      if(runera==y2017F) METycorr = -(0.213341*npv +0.684588);
      if(runera==y2018A) METxcorr = -(0.362865*npv -1.94505);
      if(runera==y2018A) METycorr = -(0.0709085*npv -0.307365);
      if(runera==y2018B) METxcorr = -(0.492083*npv -2.93552);
      if(runera==y2018B) METycorr = -(0.17874*npv -0.786844);
      if(runera==y2018C) METxcorr = -(0.521349*npv -1.44544);
      if(runera==y2018C) METycorr = -(0.118956*npv -1.96434);
      if(runera==y2018D) METxcorr = -(0.531151*npv -1.37568);
      if(runera==y2018D) METycorr = -(0.0884639*npv -1.57089);
      if(runera==y2016MC) METxcorr = -(-0.195191*npv -0.170948);
      if(runera==y2016MC) METycorr = -(-0.0311891*npv +0.787627);
      if(runera==y2017MC) METxcorr = -(-0.217714*npv +0.493361);
      if(runera==y2017MC) METycorr = -(0.177058*npv -0.336648);
      if(runera==y2018MC) METxcorr = -(0.296713*npv -0.141506);
      if(runera==y2018MC) METycorr = -(0.115685*npv +0.0128193);
    
      //UL2017
      if(runera==yUL2017B) METxcorr = -(-0.211161*npv +0.419333);
      if(runera==yUL2017B) METycorr = -(0.251789*npv +-1.28089);
      if(runera==yUL2017C) METxcorr = -(-0.185184*npv +-0.164009);
      if(runera==yUL2017C) METycorr = -(0.200941*npv +-0.56853);
      if(runera==yUL2017D) METxcorr = -(-0.201606*npv +0.426502);
      if(runera==yUL2017D) METycorr = -(0.188208*npv +-0.58313);
      if(runera==yUL2017E) METxcorr = -(-0.162472*npv +0.176329);
      if(runera==yUL2017E) METycorr = -(0.138076*npv +-0.250239);
      if(runera==yUL2017F) METxcorr = -(-0.210639*npv +0.72934);
      if(runera==yUL2017F) METycorr = -(0.198626*npv +1.028);
      if(runera==yUL2017MC) METxcorr = -(-0.300155*npv +1.90608);
      if(runera==yUL2017MC) METycorr = -(0.300213*npv +-2.02232);

      //UL2018
      if(runera==yUL2018A) METxcorr = -(0.263733*npv +-1.91115);
      if(runera==yUL2018A) METycorr = -(0.0431304*npv +-0.112043);
      if(runera==yUL2018B) METxcorr = -(0.400466*npv +-3.05914);
      if(runera==yUL2018B) METycorr = -(0.146125*npv +-0.533233);
      if(runera==yUL2018C) METxcorr = -(0.430911*npv +-1.42865);
      if(runera==yUL2018C) METycorr = -(0.0620083*npv +-1.46021);
      if(runera==yUL2018D) METxcorr = -(0.457327*npv +-1.56856);
      if(runera==yUL2018D) METycorr = -(0.0684071*npv +-0.928372);
      if(runera==yUL2018MC) METxcorr = -(0.183518*npv +0.546754);
      if(runera==yUL2018MC) METycorr = -(0.192263*npv +-0.42121);

      //UL2016
      if(runera==yUL2016B) METxcorr = -(-0.0214894*npv +-0.188255);
      if(runera==yUL2016B) METycorr = -(0.0876624*npv +0.812885);
      if(runera==yUL2016C) METxcorr = -(-0.032209*npv +0.067288);
      if(runera==yUL2016C) METycorr = -(0.113917*npv +0.743906);
      if(runera==yUL2016D) METxcorr = -(-0.0293663*npv +0.21106);
      if(runera==yUL2016D) METycorr = -(0.11331*npv +0.815787);
      if(runera==yUL2016E) METxcorr = -(-0.0132046*npv +0.20073);
      if(runera==yUL2016E) METycorr = -(0.134809*npv +0.679068);
      if(runera==yUL2016F) METxcorr = -(-0.0543566*npv +0.816597);
      if(runera==yUL2016F) METycorr = -(0.114225*npv +1.17266);
      if(runera==yUL2016Flate) METxcorr = -(0.134616*npv +-0.89965);
      if(runera==yUL2016Flate) METycorr = -(0.0397736*npv +1.0385);
      if(runera==yUL2016G) METxcorr = -(0.121809*npv +-0.584893);
      if(runera==yUL2016G) METycorr = -(0.0558974*npv +0.891234);
      if(runera==yUL2016H) METxcorr = -(0.0868828*npv +-0.703489);
      if(runera==yUL2016H) METycorr = -(0.0888774*npv +0.902632);
      if(runera==yUL2016MCnonAPV) METxcorr = -(-0.153497*npv +-0.231751);
      if(runera==yUL2016MCnonAPV) METycorr = -(0.00731978*npv +0.243323);
      if(runera==yUL2016MCAPV) METxcorr = -(-0.188743*npv +0.136539);
      if(runera==yUL2016MCAPV) METycorr = -(0.0127927*npv +0.117747);



    }
    
    //UL2017Puppi
    if(ispuppi){
      if(runera==yUL2017B) METxcorr = -(-0.00382117*npv +-0.666228);
      if(runera==yUL2017B) METycorr = -(0.0109034*npv +0.172188);
      if(runera==yUL2017C) METxcorr = -(-0.00110699*npv +-0.747643);
      if(runera==yUL2017C) METycorr = -(-0.0012184*npv +0.303817);
      if(runera==yUL2017D) METxcorr = -(-0.00141442*npv +-0.721382);
      if(runera==yUL2017D) METycorr = -(-0.0011873*npv +0.21646);
      if(runera==yUL2017E) METxcorr = -(0.00593859*npv +-0.851999);
      if(runera==yUL2017E) METycorr = -(-0.00754254*npv +0.245956);
      if(runera==yUL2017F) METxcorr = -(0.00765682*npv +-0.945001);
      if(runera==yUL2017F) METycorr = -(-0.0154974*npv +0.804176);
      if(runera==yUL2017MC) METxcorr = -(-0.0102265*npv +-0.446416);
      if(runera==yUL2017MC) METycorr = -(0.0198663*npv +0.243182);

      //UL2018Puppi
      if(runera==yUL2018A) METxcorr = -(-0.0073377*npv +0.0250294);
      if(runera==yUL2018A) METycorr = -(-0.000406059*npv +0.0417346);
      if(runera==yUL2018B) METxcorr = -(0.00434261*npv +0.00892927);
      if(runera==yUL2018B) METycorr = -(0.00234695*npv +0.20381);
      if(runera==yUL2018C) METxcorr = -(0.00198311*npv +0.37026);
      if(runera==yUL2018C) METycorr = -(-0.016127*npv +0.402029);
      if(runera==yUL2018D) METxcorr = -(0.00220647*npv +0.378141);
      if(runera==yUL2018D) METycorr = -(-0.0160244*npv +0.471053);
      if(runera==yUL2018MC) METxcorr = -(-0.0214557*npv +0.969428);
      if(runera==yUL2018MC) METycorr = -(0.0167134*npv +0.199296);

      //UL2016Puppi
      if(runera==yUL2016B) METxcorr = -(-0.00109025*npv +-0.338093);
      if(runera==yUL2016B) METycorr = -(-0.00356058*npv +0.128407);
      if(runera==yUL2016C) METxcorr = -(-0.00271913*npv +-0.342268);
      if(runera==yUL2016C) METycorr = -(0.00187386*npv +0.104);
      if(runera==yUL2016D) METxcorr = -(-0.00254194*npv +-0.305264);
      if(runera==yUL2016D) METycorr = -(-0.00177408*npv +0.164639);
      if(runera==yUL2016E) METxcorr = -(-0.00358835*npv +-0.225435);
      if(runera==yUL2016E) METycorr = -(-0.000444268*npv +0.180479);
      if(runera==yUL2016F) METxcorr = -(0.0056759*npv +-0.454101);
      if(runera==yUL2016F) METycorr = -(-0.00962707*npv +0.35731);
      if(runera==yUL2016Flate) METxcorr = -(0.0234421*npv +-0.371298);
      if(runera==yUL2016Flate) METycorr = -(-0.00997438*npv +0.0809178);
      if(runera==yUL2016G) METxcorr = -(0.0182134*npv +-0.335786);
      if(runera==yUL2016G) METycorr = -(-0.0063338*npv +0.093349);
      if(runera==yUL2016H) METxcorr = -(0.015702*npv +-0.340832);
      if(runera==yUL2016H) METycorr = -(-0.00544957*npv +0.199093);
      if(runera==yUL2016MCnonAPV) METxcorr = -(-0.0058341*npv +-0.395049);
      if(runera==yUL2016MCnonAPV) METycorr = -(0.00971595*npv +-0.101288);
      if(runera==yUL2016MCAPV) METxcorr = -(-0.0060447*npv +-0.4183);
      if(runera==yUL2016MCAPV) METycorr = -(0.008331*npv +-0.0990046);


    }


  }
  else {//these are the corrections for v2 MET recipe (currently recommended for 2017)
    if(runera==y2016B) METxcorr = -(-0.0374977*npv +0.00488262);
    if(runera==y2016B) METycorr = -(0.107373*npv +-0.00732239);
    if(runera==y2016C) METxcorr = -(-0.0832562*npv +0.550742);
    if(runera==y2016C) METycorr = -(0.142469*npv +-0.153718);
    if(runera==y2016D) METxcorr = -(-0.0400931*npv +0.753734);
    if(runera==y2016D) METycorr = -(0.127154*npv +0.0175228);
    if(runera==y2016E) METxcorr = -(-0.0409231*npv +0.755128);
    if(runera==y2016E) METycorr = -(0.168407*npv +0.126755);
    if(runera==y2016F) METxcorr = -(-0.0161259*npv +0.516919);
    if(runera==y2016F) METycorr = -(0.141176*npv +0.544062);
    if(runera==y2016G) METxcorr = -(0.0583851*npv +-0.0987447);
    if(runera==y2016G) METycorr = -(0.0641427*npv +0.319112);
    if(runera==y2016H) METxcorr = -(0.0706267*npv +-0.13118);
    if(runera==y2016H) METycorr = -(0.127481*npv +0.370786);
    if(runera==y2017B) METxcorr = -(-0.19563*npv +1.51859);
    if(runera==y2017B) METycorr = -(0.306987*npv +-1.84713);
    if(runera==y2017C) METxcorr = -(-0.161661*npv +0.589933);
    if(runera==y2017C) METycorr = -(0.233569*npv +-0.995546);
    if(runera==y2017D) METxcorr = -(-0.180911*npv +1.23553);
    if(runera==y2017D) METycorr = -(0.240155*npv +-1.27449);
    if(runera==y2017E) METxcorr = -(-0.149494*npv +0.901305);
    if(runera==y2017E) METycorr = -(0.178212*npv +-0.535537);
    if(runera==y2017F) METxcorr = -(-0.165154*npv +1.02018);
    if(runera==y2017F) METycorr = -(0.253794*npv +0.75776);
    if(runera==y2018A) METxcorr = -(0.362642*npv +-1.55094);
    if(runera==y2018A) METycorr = -(0.0737842*npv +-0.677209);
    if(runera==y2018B) METxcorr = -(0.485614*npv +-2.45706);
    if(runera==y2018B) METycorr = -(0.181619*npv +-1.00636);
    if(runera==y2018C) METxcorr = -(0.503638*npv +-1.01281);
    if(runera==y2018C) METycorr = -(0.147811*npv +-1.48941);
    if(runera==y2018D) METxcorr = -(0.520265*npv +-1.20322);
    if(runera==y2018D) METycorr = -(0.143919*npv +-0.979328);
    if(runera==y2016MC) METxcorr = -(-0.159469*npv +-0.407022);
    if(runera==y2016MC) METycorr = -(-0.0405812*npv +0.570415);
    if(runera==y2017MC) METxcorr = -(-0.182569*npv +0.276542);
    if(runera==y2017MC) METycorr = -(0.155652*npv +-0.417633);
    if(runera==y2018MC) METxcorr = -(0.299448*npv +-0.13866);
    if(runera==y2018MC) METycorr = -(0.118785*npv +0.0889588);




    
  }

  double CorrectedMET_x = uncormet *cos( uncormet_phi)+METxcorr;
  double CorrectedMET_y = uncormet *sin( uncormet_phi)+METycorr;

  double CorrectedMET = sqrt(CorrectedMET_x*CorrectedMET_x+CorrectedMET_y*CorrectedMET_y);
  double CorrectedMETPhi;
  if(CorrectedMET_x==0 && CorrectedMET_y>0) CorrectedMETPhi = TMath::Pi();
  else if(CorrectedMET_x==0 && CorrectedMET_y<0 )CorrectedMETPhi = -TMath::Pi();
  else if(CorrectedMET_x >0) CorrectedMETPhi = TMath::ATan(CorrectedMET_y/CorrectedMET_x);
  else if(CorrectedMET_x <0&& CorrectedMET_y>0) CorrectedMETPhi = TMath::ATan(CorrectedMET_y/CorrectedMET_x) + TMath::Pi();
  else if(CorrectedMET_x <0&& CorrectedMET_y<0) CorrectedMETPhi = TMath::ATan(CorrectedMET_y/CorrectedMET_x) - TMath::Pi();
  else CorrectedMETPhi =0;

  TheXYCorr_Met_MetPhi.first= CorrectedMET;
  TheXYCorr_Met_MetPhi.second= CorrectedMETPhi;
  return TheXYCorr_Met_MetPhi;

}

bool Selector::passEleID(int eleInd, int cutVal, bool doRelisoCut){

    Int_t WPcutBits = tree->eleVidWPBitmap_[eleInd];

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


Selector::~Selector(){

  // if(year=="2016"){
  //   delete rca;  
  //   delete rcb;
  // }else
  //   delete rc;
  
}

