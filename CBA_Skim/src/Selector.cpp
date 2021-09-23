#include"../interface/Selector.h"

// double dR(double eta1, double phi1, double eta2, double phi2){
//     double dphi = phi2 - phi1;
//     double deta = eta2 - eta1;
//     static const double pi = TMath::Pi();
//     dphi = TMath::Abs( TMath::Abs(dphi) - pi ) - pi;
//     return TMath::Sqrt( dphi*dphi + deta*deta );
// }

//TRandom* generator = new TRandom3(0);
//TRandom* generator = new TRandom3(1234);
TRandom* generator = gRandom;

Selector::Selector(){

    isNanoAOD = true;
    
    year = "2016";

    // jets
    jet_Pt_cut = 30.; //Default
    jet_Eta_cut = 2.4;
    
    //Modified
    //jet_Pt_cut = 0.0; 
    //jet_Eta_cut = 5.0;
    
    printEvent = -1;

    looseJetID = false;
    veto_lep_jet_dR = 0.4; // remove jets with a lepton closer than this cut level
    JERsystLevel  = 1;
    JECsystLevel  = 1;
    elesmearLevel = 1;
    elescaleLevel = 1;
    useDeepCSVbTag = false;
    //https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation80XReReco
    // CSVv2M
    btag_cut = 0.8484;  
    // DeepCSV
    btag_cut_DeepCSV = 0.6324;  

    // whether to invert lepton requirements for 
    QCDselect = false;
    DDselect = false;
    
    // electrons TIGHT
    ele_Pt_cut = 35.0; // Default
    ele_Eta_cut = 2.4;
    // electron nanoAOD VETO
    ele_PtLoose_cut = 15.0;
    ele_EtaLoose_cut = 2.4;

    // muons nanoAOD TIGHT
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
    rc = 0;
    s = 0 ;
    m = 0;

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


}

void Selector::init_JER(std::string inputPrefix){
  
    jetResolution = new JME::JetResolution((inputPrefix+"_MC_PtResolution_AK4PFchs.txt").c_str());
    jetResolutionScaleFactor = new JME::JetResolutionScaleFactor((inputPrefix+"_MC_SF_AK4PFchs.txt").c_str());

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

void Selector::process_objects(string path, EventTree* inp_tree){
    tree = inp_tree;
    clear_vectors();
    
    if(!rc)
      rc = new RoccoR(Form("%s/weight/RoccoR/RoccoR%s.txt",path.c_str(),year.c_str()));
    
    //cout << "before selector muons" << endl;
    filter_muons();

    //Electron selection must be after muon selection
    //cout << "before selector electrons" << endl;
    filter_electrons();

    //cout << "before selector jets" << endl;
    filter_jets();

    filter_jetsNoCorr();
    
    filter_mets();
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
    JetsNoCorr.clear();
}

void Selector::filter_electrons(){
  if (int(tree->event_) == printEvent){
	cout << "Found Event, Starting Electrons" << endl;
	cout << " nEle=" << tree->nEle_ << endl;
    }

  for(int eleInd = 0; eleInd < int(tree->nEle_) ; ++eleInd){

        double eta = tree->eleEta_[eleInd];
        double absEta = TMath::Abs(eta);
	double phi = tree->elePhi_[eleInd];
        double SCeta = eta + tree->eleDeltaEtaSC_[eleInd];
        double absSCEta = TMath::Abs(SCeta);

        double pt = tree->elePt_[eleInd];
        
        // // EA subtraction
        double PFrelIso_corr = tree->elePFRelIso_[eleInd];
        
        uint eleID = tree->eleIDcutbased_[eleInd];
        bool passVetoID   = eleID >= 1;
        bool passLooseID  = eleID >= 2;
	bool passMediumID = eleID >= 3;
        bool passTightID  = eleID >= 4;
        
        // make sure it doesn't fall within the gap
        bool passEtaEBEEGap = (absSCEta < 1.4442) || (absSCEta > 1.566);
        

        // D0 and Dz cuts are different for barrel and endcap
        bool passD0 = ((absEta < 1.479 && abs(tree->eleD0_[eleInd]) < 0.05) ||
                       (absEta > 1.479 && abs(tree->eleD0_[eleInd]) < 0.1));
        bool passDz = ((absEta < 1.479 && abs(tree->eleDz_[eleInd]) < 0.1) ||
                       (absEta > 1.479 && abs(tree->eleDz_[eleInd]) < 0.2));
        
        
	
        //double EleSmear = 1.;

        /////////NEEDS TO BE REIMPLEMENTED

        // if (!tree->isData_ && elesmearLevel==1) {EleSmear = generator->Gaus(1,(tree->eleResol_rho_up_[eleInd]+tree->eleResol_rho_dn_[eleInd])/2.);}
        // if (!tree->isData_ && elesmearLevel==0) {EleSmear = generator->Gaus(1,tree->eleResol_rho_dn_[eleInd]);}
        // if (!tree->isData_ && elesmearLevel==2) {EleSmear = generator->Gaus(1,tree->eleResol_rho_up_[eleInd]);}
        // if (pt<10.){
        //   smearEle= false;
        // }
        // if (smearEle){
        //   pt = pt*EleSmear;
        //   en = EleSmear*en;
        // }
        // tree->elePt_[eleInd] = pt;
        // tree->eleEn_[eleInd]= en;   
        // double EleScale = 1.;
        // double nom_scale =  (float(tree->eleScale_stat_up_[eleInd]+tree->eleScale_stat_dn_[eleInd])/2.);
        // if (tree->isData_ && elescaleLevel==1) {EleScale = ((tree->eleScale_stat_up_[eleInd]+tree->eleScale_stat_dn_[eleInd])/2.);}
        // if (!tree->isData_ && elescaleLevel==2){EleScale = 1.+sqrt(pow((1-tree->eleScale_syst_up_[eleInd]),2)+pow((1-tree->eleScale_stat_up_[eleInd]),2)+pow((1-tree->eleScale_gain_up_[eleInd]),2));}
        // if (!tree->isData_ && elescaleLevel==0){EleScale = 1.-(sqrt(pow((1-tree->eleScale_syst_dn_[eleInd]),2)+pow(1-(tree->eleScale_stat_dn_[eleInd]),2)+pow((1-tree->eleScale_gain_dn_[eleInd]),2)));}
        // if (scaleEle){
        //   //	std::cout<<tree->eleScale_syst_dn_[eleInd]<<   tree->eleScale_stat_dn_[eleInd]<<   tree->eleScale_syst_dn_[eleInd]<<std::endl;
        //   //		std::cout<<"nominal is:"<< nom_scale<<std::endl;
        //   //	std::cout << "stat: "<<EleScale <<std::endl;
        //   pt = pt*EleScale;
        //   en = EleScale*en;
        // }       
        // tree->elePt_[eleInd] = pt;
        // tree->eleEn_[eleInd]= en;
        

	// upper limit on the QCD iso of the vetoID value
	bool passTightID_noIso = passEleID(eleInd, 4,false) && passVetoID;
	
        if (QCDselect){
            Float_t isoEBcut = 0.0287 + 0.506/tree->elePt_[eleInd];
            Float_t isoEECut = 0.0445 + 0.963/tree->elePt_[eleInd];
            passTightID = false;
            passTightID = (passTightID_noIso && 
			   PFrelIso_corr > (absSCEta < 1.479 ? isoEBcut : isoEECut) );
        }
	
	
	bool passVetoIDNoIso = passEleID(eleInd, 1,false) && passVetoID; // Ignore iso requirements
	
	float vetoIsoEBcut = 0.198 + 0.506/tree->elePt_[eleInd];
	float vetoIsoEECut = 0.203 + 0.963/tree->elePt_[eleInd];
	
	//QCD CR now applies veto iso as upper limit, so Veto leptons are the same as they would be otherwise

	// // if using QCD cr, just use cut without iso requirement
	// if(QCDselect){
	//     passVetoID = passVetoIDNoIso;
	// }
	
        bool eleSel = (passEtaEBEEGap && 
                       absEta <= ele_Eta_cut &&
                       pt >= ele_Pt_cut &&
                       passTightID &&
                       passD0 &&
                       passDz);

        bool looseSel = ( passEtaEBEEGap && 
			  absEta <= ele_EtaLoose_cut &&
			  pt >= ele_PtLoose_cut &&
			  passVetoID &&
			  passD0 &&
			  passDz);
        
	bool eleSel_noIso = (passEtaEBEEGap && 
			     absEta <= ele_Eta_cut &&
			     pt >= ele_Pt_cut &&
			     passTightID_noIso &&
			     passD0 &&
			     passDz);

	bool eleSel_noIso_loose = (passEtaEBEEGap && 
				   absEta <= ele_EtaLoose_cut &&
				   pt >= ele_PtLoose_cut &&
				   passVetoIDNoIso &&
				   passD0 &&
				   passDz);
	
        
	if (int(tree->event_)==printEvent){
	  cout << "-- " << eleInd << " eleSel=" <<  eleSel << " looseSel=" <<  looseSel << " pt="<<pt<< " eta="<<eta<< " phi="<<tree->elePhi_[eleInd]<< " eleID="<<eleID << " passD0="<<passD0<< "("<<tree->eleD0_[eleInd]<<") passDz="<<passDz<< "("<<tree->eleDz_[eleInd]<<")"<< endl;
	  cout << "            ";
	  std::cout << std::setbase(8);
	  cout << "            idBits="<<tree->eleVidWPBitmap_[eleInd] << endl;
	  std::cout << std::setbase(10);
	    
	} 
	
	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	// //MinAOD setting as in analysis code
	// bool ObjectSelector::cutBasedElectronID_Summer16_80X_V1_veto(const MyElectron *e)
	// {
	//   bool passID = false;
	//   //barrel
	//   if(abs(e->eleSCEta) <= 1.479 
	//      && e->sigmaIetaIeta 	< 0.0115	 
	//      && abs(e->dEtaInSeed) 	< 0.00749	
	//      && abs(e->dPhiIn) 		< 0.228	
	//      && e->hadOverEm 		< 0.356	
	//      && e->relCombPFIsoEA 	< 0.175	
	//      && abs(e->iEminusiP) 	< 0.299	
	//      && e->nInnerHits       	<= 2
	//      && e->passConversionVeto  
	//      )passID = true;
	//   //endcap 
	//   if(abs(e->eleSCEta) > 1.479 
	//      && e->sigmaIetaIeta 	< 0.037	
	//      && abs(e->dEtaInSeed) 	< 0.00895	 
	//      && abs(e->dPhiIn) 		< 0.213	
	//      && e->hadOverEm 		< 0.211	
	//      && e->relCombPFIsoEA 	< 0.159	
	//      && abs(e->iEminusiP) 	< 0.15	
	//      && e->nInnerHits       	<= 3
	//      && e->passConversionVeto  
	//      )passID = true;
	//   return passID;
	// }

	// //Electron ID: medium
	// bool ObjectSelector::cutBasedElectronID_Summer16_80X_V1_medium(const MyElectron *e, MyVertex & vertex)
	// {
	//   bool passID = false;
	//   //barrel
	//   double dxy = abs(e->D0);
	//   double dz  = abs(e->Dz);
	//   if(abs(e->eleSCEta) <= 1.479 
	//      && e->sigmaIetaIeta 	< 0.00998	 
	//      && abs(e->dEtaInSeed) 	< 0.00311	
	//      && abs(e->dPhiIn) 		< 0.103	
	//      && e->hadOverEm 		< 0.253	
	//      ///&& e->relCombPFIsoEA 	< 0.0695	
	//      && abs(e->iEminusiP) 	< 0.134
	//      && dxy                 < 0.05
	//      && dz                  < 0.10    
	//      && e->nInnerHits       <= 1
	//      && e->passConversionVeto  
	//      )passID = true;
	//   //endcap
	//   if(abs(e->eleSCEta) > 1.479 
	//      && e->sigmaIetaIeta 	< 0.0298	
	//      && abs(e->dEtaInSeed) 	< 0.00609	 
	//      && abs(e->dPhiIn) 		< 0.045	
	//      && e->hadOverEm 		< 0.0878	
	//      ///&& e->relCombPFIsoEA 	< 0.0821	
	//      && abs(e->iEminusiP) 	< 0.13	
	//      && dxy                 < 0.10
	//      && dz                  < 0.20    
	//      && e->nInnerHits       <= 1
	//      && e->passConversionVeto  
	//      )passID = true;
	//   return passID;
	// }

	// void ObjectSelector::preSelectElectrons(vector<int> * e_i, const vector<MyElectron> & vE , MyVertex & vertex, const bool & isPFlow){
	//   //https://twiki.cern.ch/twiki/bin/viewauth/CMS/CutBasedElectronIdentificationRun2#Offline_selection_criteria
	//   for(unsigned int i=0;i<vE.size();i++){
	//     const MyElectron * e    = &vE[i];
	//     double ePt     	        = TMath::Abs(e->p4.pt());
	//     double eEta     	    = TMath::Abs(e->p4.eta());
	//     bool passID = cutBasedElectronID_Summer16_80X_V1_medium(e, vertex);
	//     if(passID && ePt >30.0 && eEta <2.5){e_i->push_back(i);}
	//   }
	// }

        
	// bool ObjectSelector::looseElectronVeto(unsigned long selectedElectron, const vector<MyElectron> & vE, MyVertex & vertex, const bool & isPFlow){
	//   //https://twiki.cern.ch/twiki/bin/viewauth/CMS/CutBasedElectronIdentificationRun2#Offline_selection_criteria
	//   bool looseVeto(false);
	//   for(unsigned long i=0;i<vE.size();i++){
	//     const MyElectron * e   = &vE[i];
	//     double ePt     	   = TMath::Abs(e->p4.pt());
	//     if( i==selectedElectron) continue; 
	//     bool passID = cutBasedElectronID_Summer16_80X_V1_veto(e);
	//     double dxy = abs(e->D0);
	//     double dz  = abs(e->Dz);
	//     if(passID && ePt >15.0 && dxy<0.05 && dz < 0.1){looseVeto = true;}
	//   }
	//   return looseVeto;
	// }

	// void ObjectSelector::ElectronCleaning( const vector<MyElectron> & vE, const vector<MyMuon> & vM, vector<int> * e_old, vector<int> * e_new, vector<int> * mu, const double & DR ){
	//   for(size_t i = 0; i < e_old->size(); i++){
	//     int iele = (*e_old)[i];
	//     double delR2Mu = 5.0;
	//     for(size_t j = 0; j < mu->size(); j++){
	//       int imu = (*mu)[j];
	//       double delR = DeltaR(vE[iele].p4, vM[imu].p4);
	//       if(delR < delR2Mu)delR2Mu = delR;
	//     }
	//     if(delR2Mu > DR) e_new->push_back(iele);
	//   }
	// }
	
	bool passMiniAOD_presel = ( passEtaEBEEGap and absEta <= ele_Eta_cut_miniAOD and  pt >= ele_Pt_cut_miniAOD and passMediumID and passD0 and passDz);
	
	for(std::vector<int>::const_iterator muInd = Muons.begin(); muInd != Muons.end(); muInd++) {
	  if (dR(eta, phi, tree->muEta_[*muInd], tree->muPhi_[*muInd]) < ele_muon_dR_miniAOD) passMiniAOD_presel = false;
	}
	
	bool selectEle = (isNanoAOD) ? eleSel : passMiniAOD_presel ;
	bool selectEleDD = (isNanoAOD) ? eleSel_noIso : passMiniAOD_presel ;
	
        if( selectEle ){
	  Electrons.push_back(eleInd);
        }
        else if( looseSel ){ 
	  ElectronsLoose.push_back(eleInd);
        }
        if( selectEleDD ){
	  ElectronsNoIso.push_back(eleInd);
        } else if( eleSel_noIso_loose ){
	  ElectronsNoIsoLoose.push_back(eleInd);
	}
  }

  if (int(tree->event_)==printEvent){
	if (year=="2016"){
	    cout << "            idBits :   MinPtCut, GsfEleSCEtaMultiRangeCut, GsfEleDEtaInSeedCut, GsfEleDPhiInCut, GsfEleFull5x5SigmaIEtaIEtaCut, GsfEleHadronicOverEMCut, GsfEleEInverseMinusPInverseCut, GsfEleEffAreaPFIsoCut, GsfEleConversionVetoCut, GsfEleMissingHitsCut" << endl;
	} else {
	    cout << "            idBits :   MinPtCut, GsfEleSCEtaMultiRangeCut, GsfEleDEtaInSeedCut, GsfEleDPhiInCut, GsfEleFull5x5SigmaIEtaIEtaCut, GsfEleHadronicOverEMEnergyScaledCut, GsfEleEInverseMinusPInverseCut, GsfEleRelPFIsoScaledCut, GsfEleConversionVetoCut, GsfEleMissingHitsCut" << endl;
	}
    }
    
}

void Selector::filter_muons(){

  if (int(tree->event_)==printEvent){
    cout << "Found Event, Starting Muons" << endl;
    cout << " nMu=" << tree->nMuon_ << endl;
  }
  
  //bool passAllMu = true;
  
  for(int muInd = 0; muInd < int(tree->nMuon_); ++muInd){
    
    double eta = tree->muEta_[muInd];
    double pt = tree->muPt_[muInd];
    
    double SFRochCorr = 1.0;
    if (tree->isData_)
      SFRochCorr *= rc->kScaleDT(tree->muCharge_[muInd], pt, eta, tree->muPhi_[muInd], s, m);
    else
      SFRochCorr *= rc->kSmearMC(tree->muCharge_[muInd], pt, eta, tree->muPhi_[muInd], tree->munTrackerLayers_[muInd], generator->Rndm(), s, m);;	
      //SFRochCorr *= rc->kSmearMC(tree->muCharge_[muInd], pt, eta, tree->muPhi_[muInd], tree->munTrackerLayers_[muInd], 0.5, s, m);;	
    
    tree->muRoccoR_[muInd] = SFRochCorr;
    pt = pt*SFRochCorr;
    
    double PFrelIso_corr = tree->muPFRelIso_[muInd];

    bool looseMuonID = tree->muIsPFMuon_[muInd] && (tree->muIsTracker_[muInd] || tree->muIsGlobal_[muInd]);
    bool mediumMuonID = tree->muMediumId_[muInd];
    bool tightMuonID = tree->muTightId_[muInd];

    bool passTight = (pt >= mu_Pt_cut &&
		      TMath::Abs(eta) <= mu_Eta_tight &&
		      tightMuonID &&
		      (!QCDselect ? (PFrelIso_corr < mu_RelIso_tight): PFrelIso_corr > mu_RelIso_tight)
		      && (PFrelIso_corr < mu_RelIso_loose) //for QCD , upper limit of iso of the loose cut
		      );
    
    bool passLoose = (pt >= mu_PtLoose_cut &&
		      TMath::Abs(eta) <= mu_Eta_loose &&
		      looseMuonID &&
		      (PFrelIso_corr < mu_RelIso_loose)
		      //(!QCDselect ? (PFrelIso_corr < mu_RelIso_loose): PFrelIso_corr > mu_RelIso_loose) 
		      );
    // if (QCDselect){ //ignoring Iso cut in  QCDCR
    //     bool passLoose = (pt >= mu_PtLoose_cut &&
    // 		      TMath::Abs(eta) <= mu_Eta_loose &&
    // 		      looseMuonID 
    // 		      );
    // }
    bool passTight_noIso = (pt >= mu_Pt_cut &&
			    TMath::Abs(eta) <= mu_Eta_tight &&
			    tightMuonID
			    && (PFrelIso_corr < mu_RelIso_loose)
			    );
    
    bool passLoose_noIso = (pt >= mu_PtLoose_cut &&
			    TMath::Abs(eta) <= mu_Eta_loose &&
			    looseMuonID
			    && (PFrelIso_corr < mu_RelIso_loose)
			    );
    
    /*
    // The MiniAOD Selection

    double UncertaintyComputer::muPtWithRochCorr(const MyMuon *mu, bool isData, double u1, double u2, int s, int m){
    double charge = mu->charge;
    double pt 	= mu->p4.pt();
    double eta 	= mu->p4.eta();
    double phi 	= mu->p4.phi();
    int nl 	= mu->nTrackerLayers;
    double dataSF = rc.kScaleDT(charge, pt, eta, phi, s, m); 
    double mcSF 	= rc.kScaleAndSmearMC(charge, pt, eta, phi, nl, u1, u2, s, m); 
    double SF = 1.0; 
    if(isData)SF = dataSF;
    else SF = mcSF;
    ///cout<<pt<<"\t"<<SF<<"\t"<<SF*pt<<"\t"<<charge<<"\t"<<eta<<"\t"<<phi<<"\t"<<nl<<"\t"<<u1<<"\t"<<u2<<"\t"<<s<<"\t"<<m<<endl;
    return SF*pt;
    }
	

    bool ObjectSelector::isMediumMuon(const MyMuon * m){
    bool isMedium(false);
    bool goodGlob = m->isGlobalMuon && m->normChi2 <3 &&  m->chi2LocalPosition < 12 && m->trkKink < 20; 
    bool isLooseMuon =  m->isPFMuon && (m->isGlobalMuon || m->isTrackerMuon) ;
    isMedium =  isLooseMuon && m->validFraction > 0.8 && m->segmentCompatibility >(goodGlob ? 0.303 : 0.451); 
    return isMedium;   
    }
	
    void ObjectSelector::preSelectMuons(TString url, vector<int> * m_i, const vector<MyMuon> & vM , 
    MyVertex & vertex, const bool & isData, const double & random_u1, 
    const double & random_u2, const int & err_member, const int & err_set){
    for( int i=0;i< (int) vM.size();i++){
    const MyMuon * m = &vM[i];
    double mEta     = TMath::Abs(m->p4.eta());
    ///double mPt      = TMath::Abs(m->p4.pt());
    double mPt   = muPtWithRochCorr(m, isData, random_u1, random_u2, err_set, err_member); 
    double dxy = abs(m->D0);
    double dz = abs(m->Dz);
    bool passID = false;
    passID = isMediumMuon(m);
    if(passID && mPt > 26.0 && mEta < 2.4 && dxy < 0.05 && dz <0.2){
    m_i->push_back(i);
    }
    }
    }
    */
    
    bool passMiniAOD_presel = ( mediumMuonID and pt > mu_Pt_cut_miniAOD and 
				TMath::Abs(eta) <= mu_Eta_tight and tree->mudxy_[muInd] < 0.05 and tree->mudz_[muInd] < 0.2 ) ;
	
    if (int(tree->event_)==printEvent){
      cout << "-- " << muInd << " passTight="<<passTight<< " passLoose="<<passLoose << " pt="<<pt<< " eta="<<eta<< " phi="<<tree->muPhi_[muInd]<< " tightID="<<tightMuonID<< " looseID="<<looseMuonID << " pfRelIso="<<PFrelIso_corr << endl;
    } 
    
    bool selectMuon = (isNanoAOD) ? passTight : passMiniAOD_presel ;
    bool selectMuonDD = (isNanoAOD) ? passTight_noIso : passMiniAOD_presel ;
    
    if(selectMuon){
      Muons.push_back(muInd);
    }
    else if (passLoose){
      MuonsLoose.push_back(muInd);
    }
    if(passMiniAOD_presel){
      MuonsMiniAOD.push_back(muInd);
    }
    if(selectMuonDD){
      MuonsNoIso.push_back(muInd);
    } else if(passLoose_noIso){
      MuonsNoIsoLoose.push_back(muInd);
    }
  }
}



void Selector::filter_jets(){
  //    TLorentzVector tMET;
  if (int(tree->event_)==printEvent){
    cout << "Found Event Staring Jets" << endl;
  }

  //TLorentzVector tJET;
  for(int jetInd = 0; jetInd < int(tree->nJet_); ++jetInd){

    double pt = tree->jetPt_[jetInd];
    double eta = tree->jetEta_[jetInd];
    double phi = tree->jetPhi_[jetInd];
    double smearedpt = tree->jetPt_[jetInd];
    
    //if(pt < 17.0 or abs(eta) > 4.0) continue;
    
    //tJET.SetPtEtaPhiM(pt, eta, phi, tree->jetMass_[jetInd]);
    
    //tight ID for 2016 (bit 0), tightLeptVeto for 2017 (bit 1)
    int jetID_cutBit = 1;
    if (year=="2016"){ jetID_cutBit = 0; }
	
    bool jetID_pass = (tree->jetID_[jetInd]>>0 & 1 && looseJetID) || (tree->jetID_[jetInd]>>jetID_cutBit & 1);
        
    double jetSF = 1.;

    double resolution = 0.;
    if (!tree->isData_){
      jetParam.setJetEta(tree->jetEta_[jetInd]);
      jetParam.setJetPt(tree->jetPt_[jetInd]);
      jetParam.setJetArea(tree->jetArea_[jetInd]);
      jetParam.setRho(tree->rho_);
      resolution = jetResolution->getResolution(jetParam);
      
      if (JERsystLevel==1) jetSF = jetResolutionScaleFactor->getScaleFactor(jetParam,Variation::NOMINAL);
      if (JERsystLevel==0) jetSF = jetResolutionScaleFactor->getScaleFactor(jetParam,Variation::DOWN);
      if (JERsystLevel==2) jetSF = jetResolutionScaleFactor->getScaleFactor(jetParam,Variation::UP);
      
      double jetSmear = 1.;
      
      // cout << "genID : " << tree->jetGenJetIdx_[jetInd] << endl;
      
      int genIdx = tree->jetGenJetIdx_[jetInd];

      if ( (genIdx>-1) && (genIdx < int(tree->nGenJet_))){
      	double genJetPt = tree->GenJet_pt_[genIdx];
      	jetSmear = 1. + (jetSF - 1.) * (pt - genJetPt)/pt;
      }else{
      	jetSmear = 1 + generator->Gaus(0, resolution) * sqrt( max(jetSF*jetSF - 1, 0.) );
      }
      
      // bool miniAOD_SF_check = false;
      // if ( (genIdx>-1) && (genIdx < int(tree->nGenJet_))){
      // 	double genJetPt = tree->GenJet_pt_[genIdx];
      // 	double genJetEta = tree->GenJet_eta_[genIdx];
      // 	double genJetPhi = tree->GenJet_phi_[genIdx];
      // 	if( dR(eta, phi, genJetEta, genJetPhi) < veto_lep_jet_dR_miniAOD/2. && TMath::Abs(genJetPt - pt) < 3.0*resolution*pt )
      // 	  miniAOD_SF_check = true;
      // }
      
      // if (miniAOD_SF_check)
      // 	jetSmear = max( 0.0, 1. + (jetSF - 1.) * (pt - tree->GenJet_pt_[genIdx])/pt);
      // else
      // 	jetSmear = 1 + generator->Gaus(0, resolution) * sqrt( max(jetSF*jetSF - 1, 0.) );
      
      
      if (int(tree->event_)==printEvent){
	cout << "DoJetSmear: " << smearJetPt << endl;
	cout << "GenIdx: "<< genIdx << endl;
	cout << "jetSF: "<< jetSF << endl;
	cout << "JetSmear: "<<jetSmear << endl;
      }
      
      // double modPx = jetSmear*tJET.Px(); 
      // double modPy = jetSmear*tJET.Py(); 
      // double modPz = jetSmear*tJET.Pz(); 
      // double modE  = jetSmear*tJET.E(); 
      // tJET.SetPtEtaPhiE(modPx, modPy, modPz, modE);
      
      smearedpt = pt*jetSmear;
      
      if (smearJetPt){

	// Default
	pt = pt*jetSmear;
	// tree->jetPt_[jetInd] = pt;
	
	
	// pt = tJET.Pt();
	// eta = tJET.Eta();
	// phi = tJET.Phi();
	// double mass = tJET.M();
	
	// tree->jetPt_[jetInd]  = pt;
	// tree->jetEta_[jetInd] = eta;
	// tree->jetPhi_[jetInd] = phi;
	// tree->jetMass_[jetInd] = mass;
	
      }
    }//isMC

    bool passDR_lep_jet = true;

    if(!DDselect){
      //loop over selected electrons
      for(std::vector<int>::const_iterator eleInd = Electrons.begin(); eleInd != Electrons.end(); eleInd++) {
    	if (dR(eta, phi, tree->eleEta_[*eleInd], tree->elePhi_[*eleInd]) < veto_lep_jet_dR) passDR_lep_jet = false;
      }
    }else{
      for(std::vector<int>::const_iterator eleInd = ElectronsNoIso.begin(); eleInd != ElectronsNoIso.end(); eleInd++) {
    	if (dR(eta, phi, tree->eleEta_[*eleInd], tree->elePhi_[*eleInd]) < veto_lep_jet_dR) passDR_lep_jet = false;
      }      
    }
    
    //loop over selected muons
    if(!DDselect){
      for(std::vector<int>::const_iterator muInd = Muons.begin(); muInd != Muons.end(); muInd++) {
    	if (dR(eta, phi, tree->muEta_[*muInd], tree->muPhi_[*muInd]) < veto_lep_jet_dR) passDR_lep_jet = false;
      }
    }else{
      for(std::vector<int>::const_iterator muInd = MuonsNoIso.begin(); muInd != MuonsNoIso.end(); muInd++) {
    	if (dR(eta, phi, tree->muEta_[*muInd], tree->muPhi_[*muInd]) < veto_lep_jet_dR) passDR_lep_jet = false;
      }
    }
    
    // //loop over selected electrons
    // for(std::vector<int>::const_iterator eleInd = Electrons.begin(); eleInd != Electrons.end(); eleInd++) {
    //   if (dR(eta, phi, tree->eleEta_[*eleInd], tree->elePhi_[*eleInd]) < veto_lep_jet_dR) passDR_lep_jet = false;
    // }
    
    // //loop over selected muons
    // for(std::vector<int>::const_iterator muInd = Muons.begin(); muInd != Muons.end(); muInd++) {
    //   if (dR(eta, phi, tree->muEta_[*muInd], tree->muPhi_[*muInd]) < veto_lep_jet_dR) passDR_lep_jet = false;
    // }
    
    bool jetPresel = (pt >= jet_Pt_cut &&
    		      TMath::Abs(eta) <= jet_Eta_cut &&
    		      jetID_pass &&
    		      passDR_lep_jet
    		      );
    
    // void ObjectSelector::preSelectJets( string jetAlgo, vector<int> * j_i, const vector<MyJet> & vJ){
    //   //https://twiki.cern.ch/twiki/bin/view/CMS/JetID13TeVRun2016
    //   for(unsigned int i=0;i<vJ.size();i++){
    //     const MyJet *jet= &vJ[i];
    //     double jetEta   = TMath::Abs(jet->p4.eta());
    //     double jetPt    = TMath::Abs(jet->p4.pt());
    //     double NHF      = jet->neutralHadronEnergyFraction;
    //     double NEMF     = jet->neutralEmEnergyFraction;
    //     double CHF      = jet->chargedHadronEnergyFraction;
    //     double CEMF     = jet->chargedEmEnergyFraction;
    //     double NumConst = jet->NumConst;
    //     double CHM      = jet->chargedMultiplicity;
    //     double looseJetID = (NHF<0.99 && NEMF<0.99 && NumConst>1) && (abs(jetEta)<=2.4 && CHF>0 && CHM>0 && CEMF<0.99);
    //     if(looseJetID && jetPt > 25.0) j_i->push_back(i);
    //   }
    // }
    
    ////------------------------------------------------------------------
    ///https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookNanoAOD#Jets
    ////------------------------------------------------------------------
    /// jetId==1 means: pass loose ID, fail tight, fail tightLepVeto
    /// jetId==3 means: pass loose and tight ID, fail tightLepVeto
    /// jetId==7 means: pass loose, tight, tightLepVeto ID. 
    ////------------------------------------------------------------------
    
    bool passMiniAOD_presel =  ((tree->jetID_[jetInd]>>0 & 1 && looseJetID_miniAOD) && pt > jet_Pt_cut_miniAOD && TMath::Abs(eta) <= jet_Eta_cut_miniAOD) ;
    // if(passMiniAOD_presel){
    //   JetsPreSel.push_back(jetInd);
    //   JetsPreSelPt.push_back(smearedpt);
    // }

    bool passDR_lep_jet_miniAOD = true;
	
    //loop over selected electrons
    for(std::vector<int>::const_iterator eleInd = Electrons.begin(); eleInd != Electrons.end(); eleInd++) {
      if (dR(eta, phi, tree->eleEta_[*eleInd], tree->elePhi_[*eleInd]) < veto_lep_jet_dR_miniAOD) passDR_lep_jet_miniAOD = false;
    }
	
    //loop over selected muons
    for(std::vector<int>::const_iterator muInd = Muons.begin(); muInd != Muons.end(); muInd++) {
      if (dR(eta, phi, tree->muEta_[*muInd], tree->muPhi_[*muInd]) < veto_lep_jet_dR_miniAOD) passDR_lep_jet_miniAOD = false;
    }
    // if(passMiniAOD_presel && passDR_lep_jet_miniAOD){
    //   JetsCleaning.push_back(jetInd);
    //   JetsCleaningPt.push_back(smearedpt);
    // }
    
    if (int(tree->event_)==printEvent){
      cout << "   pt=" << pt << "  eta=" << eta << " phi=" << phi << "  jetID=" << jetID_pass << endl;
      cout << "         presel=" << jetPresel << endl;
      cout << "              pt=" << (pt >= jet_Pt_cut) <<endl;
      cout << "              eta=" << (TMath::Abs(eta) <= jet_Eta_cut) <<endl;
      cout << "              jetID=" << jetID_pass <<endl;
      cout << "              dRLep=" << passDR_lep_jet <<endl;
      cout << "              btag="<<(tree->jetBtagDeepB_[jetInd] > btag_cut_DeepCSV) << endl; 
      
    }

    
    bool fwdjetPresel = (pt>= jet_Pt_cut && jetID_pass && TMath::Abs(eta)<=3.0 && TMath::Abs(eta)>2.5 &&
			 passDR_lep_jet
			 );
    
    if(fwdjetPresel){
      FwdJets.push_back(jetInd);
    }
    
    bool selectJet = (isNanoAOD) ? jetPresel : (passMiniAOD_presel && passDR_lep_jet_miniAOD) ;

    if( selectJet ){
      Jets.push_back(jetInd);
      JetsPtSmeared.push_back(smearedpt);
      //jet_resolution.push_back(resolution);
      jet_resolution.push_back(jetSF);
      if (!useDeepCSVbTag){
	if( tree->jetBtagCSVV2_[jetInd] > btag_cut){
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
  
  // // Update the MET for JEC changes
  // if (JECsystLevel==0 || JECsystLevel==2){
  // 	tree->pfMET_ = float(tMET.Pt());
  // 	tree->pfMETPhi_ = float(tMET.Phi());
  // }
}

void Selector::filter_jetsNoCorr(){
  
  //TLorentzVector tJET;
  for(int jetInd = 0; jetInd < int(tree->nJet_); ++jetInd){
    
    double pt = tree->jetPt_[jetInd];
    double eta = tree->jetEta_[jetInd];
    double phi = tree->jetPhi_[jetInd];
    
    //tight ID for 2016 (bit 0), tightLeptVeto for 2017 (bit 1)
    int jetID_cutBit = 1;
    if (year=="2016"){ jetID_cutBit = 0; }
	
    bool jetID_pass = (tree->jetID_[jetInd]>>0 & 1 and looseJetID) || (tree->jetID_[jetInd]>>jetID_cutBit & 1);
    
    //////////////////////////////////////////////// NanoAOD selection //////////////////////////////////////////////////////////
    bool passDR_lep_jet = true;
    //loop over selected electrons
    for(std::vector<int>::const_iterator eleInd = Electrons.begin(); eleInd != Electrons.end(); eleInd++) {
      if (dR(eta, phi, tree->eleEta_[*eleInd], tree->elePhi_[*eleInd]) < veto_lep_jet_dR) passDR_lep_jet = false;
    }
    //loop over selected muons
    for(std::vector<int>::const_iterator muInd = Muons.begin(); muInd != Muons.end(); muInd++) {
      if (dR(eta, phi, tree->muEta_[*muInd], tree->muPhi_[*muInd]) < veto_lep_jet_dR) passDR_lep_jet = false;
    }
    bool jetPresel = (pt >= jet_Pt_cut and TMath::Abs(eta) <= jet_Eta_cut and jetID_pass and passDR_lep_jet);
    //////////////////////////////////////////////// NanoAOD selection //////////////////////////////////////////////////////////

    
    //////////////////////////////////////////////// MiniAOD selection //////////////////////////////////////////////////////////
    bool passMiniAOD_presel =  ((tree->jetID_[jetInd]>>0 & 1 and looseJetID_miniAOD) and pt > jet_Pt_cut_miniAOD and TMath::Abs(eta) <= jet_Eta_cut_miniAOD) ;    
    bool passDR_lep_jet_miniAOD = true;
    //loop over selected electrons
    for(std::vector<int>::const_iterator eleInd = Electrons.begin(); eleInd != Electrons.end(); eleInd++) {
      if (dR(eta, phi, tree->eleEta_[*eleInd], tree->elePhi_[*eleInd]) < veto_lep_jet_dR_miniAOD) passDR_lep_jet_miniAOD = false;
    }
    //loop over selected muons
    for(std::vector<int>::const_iterator muInd = Muons.begin(); muInd != Muons.end(); muInd++) {
      if (dR(eta, phi, tree->muEta_[*muInd], tree->muPhi_[*muInd]) < veto_lep_jet_dR_miniAOD) passDR_lep_jet_miniAOD = false;
    }
    //////////////////////////////////////////////// MiniAOD selection //////////////////////////////////////////////////////////
    
    bool selectJet = (isNanoAOD) ? jetPresel : (passMiniAOD_presel && passDR_lep_jet_miniAOD) ;
    
    if( selectJet ){
      JetsNoCorr.push_back(jetInd);
    }//presel condition

  }//main jet loop 
    
}

// double UncertaintyComputer::metWithJESJER(const vector<MyJet> & vJ, vector<int> *j, MyMET MET, int jes, int jer, bool isData, const int & seed) 
// { 
//   double metX = MET.p4.px(); 
//   double metY = MET.p4.py(); 
//   if(!isData){
//     std::mt19937 m_random_generator;
//     m_random_generator = std::mt19937(seed);
//     for(size_t i = 0; i < j->size(); i++){ 
//       int j_ind = j->at(i); 
//       double gen_pt = vJ[j_ind].Genp4.pt(); 
//       double jet_pt = vJ[j_ind].p4.pt();
//       double sigmaJER = vJ[j_ind].resolution;
//       //apply JER uncert, scaling
//       double delR = DeltaR(vJ[j_ind].Genp4, vJ[j_ind].p4);
//       double rCone = 0.4;
//       //https://github.com/cms-sw/cmssw/blob/CMSSW_8_0_25/PhysicsTools/PatUtils/interface/SmearedJetProducerT.h
//       MyLorentzVector rawJet = vJ[j_ind].p4; 
//       metX += rawJet.px(); 
//       metY += rawJet.py(); 
//       double SF = getJERSF(vJ[j_ind].p4.eta(), jer); 
//       double jerF = 1.0;
//       std::normal_distribution<> d(0, sigmaJER);
//       double N0sigma = d(m_random_generator);
//       //https://twiki.cern.ch/twiki/bin/view/CMS/JetResolution
//       if(delR<rCone/2 && abs(jet_pt -gen_pt)<3*sigmaJER*jet_pt ){
//         jerF = max(0.0, 1.0 + (SF - 1)*(jet_pt - gen_pt)/jet_pt); 
//       }
//       else{
//         jerF   = 1+ N0sigma* std::sqrt(std::max(SF*SF -1, 0.0));
//       }
//       metX -= jerF*rawJet.px(); 
//       metY -= jerF*rawJet.py();
//       //apply JES scaling
//       double jesF = vJ[j_ind].JECUncertainty*double(jes);
//       metX -= jesF*rawJet.px(); 
//       metY -= jesF*rawJet.py();
//     } 
//   }  
//   return sqrt(metX*metX + metY*metY); 
// }

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
      double resolution = jetResolution->getResolution(jetParam);
      
      double jetSF = 1.0;
      if (JERsystLevel==1) jetSF = jetResolutionScaleFactor->getScaleFactor(jetParam,Variation::NOMINAL);
      if (JERsystLevel==0) jetSF = jetResolutionScaleFactor->getScaleFactor(jetParam,Variation::DOWN);
      if (JERsystLevel==2) jetSF = jetResolutionScaleFactor->getScaleFactor(jetParam,Variation::UP);
      
      int genIdx = tree->jetGenJetIdx_[jetInd];
      double jetSmear = 1.0 ;
      if ( (genIdx>-1) && (genIdx < int(tree->nGenJet_))){
      	double genJetPt = tree->GenJet_pt_[genIdx];
      	jetSmear = 1. + (jetSF - 1.) * (pt - genJetPt)/pt;
      }else{
      	jetSmear = 1 + generator->Gaus(0, resolution) * sqrt( max(jetSF*jetSF - 1, 0.) );
      }

      // int genIdx = tree->jetGenJetIdx_[jetInd];
      // if ( (genIdx<0) or (genIdx > int(tree->nGenJet_)) ) continue;
      // bool miniAOD_SF_check = false;
      // double genJetPt = tree->GenJet_pt_[genIdx];
      // double genJetEta = tree->GenJet_eta_[genIdx];
      // double genJetPhi = tree->GenJet_phi_[genIdx];
      // if( dR(eta, phi, genJetEta, genJetPhi) < veto_lep_jet_dR_miniAOD/2. && TMath::Abs(genJetPt - pt) < 3.0*resolution*pt )
      // 	miniAOD_SF_check = true;      
      // if (miniAOD_SF_check)
      // 	jetSmear = max( 0.0, 1. + (jetSF - 1.) * (pt - tree->GenJet_pt_[genIdx])/pt);
      // else
      // 	jetSmear = 1 + generator->Gaus(0, resolution) * sqrt( max(jetSF*jetSF - 1, 0.) );
      
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
  delete rc;
}
