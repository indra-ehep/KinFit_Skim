/**********************************************************************
 Created on : 29/10/2022
 Purpose    : MC Info of the semileptonic decay
 Author     : Indranil Das, Visiting Fellow
 Email      : indranil.das@cern.ch | indra.ehep@gmail.com
**********************************************************************/
#if !defined(__CINT__) || defined(__MAKECINT__)

#include <TROOT.h>
#include <TChain.h>
#include <TEntryList.h>
#include <TFile.h>
#include <TProofOutputFile.h>
#include <TSelector.h>
#include <vector>

#include "TH2.h"
#include "TF1.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TPaveStats.h"
#include "TMath.h"
#include "TProof.h"

#include "TParticlePDG.h"
#include "TDatabasePDG.h"

#include "TLorentzVector.h"
#include "TVector3.h"

#include <fstream>

using namespace std;

#endif

int MCInfo(string infile = "/Data/root_files/AOD_files/NanoAODUL/2016/TTbarPowheg_Semilept_postVFP_Skim_NanoAOD_1of27.root")
{
  TFile *fin = TFile::Open(infile.c_str());
  cout<<"Reading from file : "<< fin->GetName() << endl;

  UInt_t    nLHEPart_;
  Int_t   LHEPart_pdgId_[100];
  Float_t   LHEPart_pt_[100];
  Float_t   LHEPart_eta_[100];
  Float_t   LHEPart_phi_[100];
  Float_t   LHEPart_mass_[100];
  
  UInt_t    nGenPart_;
  Float_t   GenPart_pt_[300];
  Float_t   GenPart_eta_[300];
  Float_t   GenPart_phi_[300];
  Float_t   GenPart_mass_[300];
  Int_t     GenPart_genPartIdxMother_[300];
  Int_t     GenPart_pdgId_[300];
  Int_t     GenPart_status_[300];
  Int_t     GenPart_statusFlags_[300];

  UInt_t    nGenJet_;
  Float_t   GenJet_pt_[100];
  Float_t   GenJet_eta_[100];
  Float_t   GenJet_phi_[100];
  Float_t   GenJet_mass_[100];
  Int_t   GenJet_partonFlavour_[100];
  UChar_t   GenJet_hadronFlavour_[100];
  
  // Jet
  UInt_t          nJet_;
  Float_t         jetPt_[200];
  Float_t         jetEta_[200];
  Float_t         jetPhi_[200];
  Float_t         jetMass_[200];
  Int_t           jetID_[200];
  Int_t           jetPUID_[200];
  Float_t         jetBtagDeepFlavB_[200];
  // Float_t         jetBtagDeepFlavCvB_[200];
  // Float_t         jetBtagDeepFlavCvL_[200];
  Int_t           jetHadFlvr_[200];
  Int_t           jetPartFlvr_[200];
  Int_t           jetGenJetIdx_[200];

  Bool_t   HLT_IsoMu24_;
  Bool_t   HLT_IsoTkMu24_;
  Bool_t   HLT_Ele27_WPTight_Gsf_;

  TTree *tree = (TTree *)fin->Get("Events");

  tree->SetCacheSize(100*1024*1024);
  tree->SetBranchStatus("*",0);

  /////////////// LHE ////////////////////////
  tree->SetBranchStatus("nLHEPart",1);
  tree->SetBranchAddress("nLHEPart", &nLHEPart_);
    
  tree->SetBranchStatus("LHEPart_pdgId",1);
  tree->SetBranchAddress("LHEPart_pdgId", &LHEPart_pdgId_);

  tree->SetBranchStatus("LHEPart_pt",1);
  tree->SetBranchAddress("LHEPart_pt", &LHEPart_pt_);

  tree->SetBranchStatus("LHEPart_eta",1);
  tree->SetBranchAddress("LHEPart_eta", &LHEPart_eta_);

  tree->SetBranchStatus("LHEPart_phi",1);
  tree->SetBranchAddress("LHEPart_phi", &LHEPart_phi_);

  tree->SetBranchStatus("LHEPart_mass",1);
  tree->SetBranchAddress("LHEPart_mass", &LHEPart_mass_);
  /////////////// LHE ////////////////////////

  //////////////// GenPart ///////////////////
  tree->SetBranchStatus("nGenPart",1);
  tree->SetBranchAddress("nGenPart", &nGenPart_);
	
  tree->SetBranchStatus("GenPart_pt",1);
  tree->SetBranchAddress("GenPart_pt", &GenPart_pt_);
	
  tree->SetBranchStatus("GenPart_eta",1);
  tree->SetBranchAddress("GenPart_eta", &GenPart_eta_);
	
  tree->SetBranchStatus("GenPart_phi",1);
  tree->SetBranchAddress("GenPart_phi", &GenPart_phi_);

  tree->SetBranchStatus("GenPart_mass",1);
  tree->SetBranchAddress("GenPart_mass", &GenPart_mass_);

  tree->SetBranchStatus("GenPart_genPartIdxMother",1);
  tree->SetBranchAddress("GenPart_genPartIdxMother", &GenPart_genPartIdxMother_);

  tree->SetBranchStatus("GenPart_pdgId",1);
  tree->SetBranchAddress("GenPart_pdgId", &GenPart_pdgId_);
	
  tree->SetBranchStatus("GenPart_status",1);
  tree->SetBranchAddress("GenPart_status", &GenPart_status_);
	
  tree->SetBranchStatus("GenPart_statusFlags",1);
  tree->SetBranchAddress("GenPart_statusFlags", &GenPart_statusFlags_);  
  //////////////// GenPart ///////////////////

  /////////////// GenJet /////////////////////
  tree->SetBranchStatus("nGenJet",1);
  tree->SetBranchAddress("nGenJet", &nGenJet_);
	
  tree->SetBranchStatus("GenJet_pt",1);
  tree->SetBranchAddress("GenJet_pt", &GenJet_pt_);

  tree->SetBranchStatus("GenJet_eta",1);
  tree->SetBranchAddress("GenJet_eta", &GenJet_eta_);

  tree->SetBranchStatus("GenJet_phi",1);
  tree->SetBranchAddress("GenJet_phi", &GenJet_phi_);
 
  tree->SetBranchStatus("GenJet_mass",1);
  tree->SetBranchAddress("GenJet_mass", &GenJet_mass_);

  tree->SetBranchStatus("GenJet_partonFlavour",1);
  tree->SetBranchAddress("GenJet_partonFlavour", &GenJet_partonFlavour_);
  
  tree->SetBranchStatus("GenJet_hadronFlavour",1);
  tree->SetBranchAddress("GenJet_hadronFlavour", &GenJet_hadronFlavour_);
  /////////////// GenJet /////////////////////  


  ////////////////RecoJet////////////////////
  tree->SetBranchStatus("nJet",1);
  tree->SetBranchAddress("nJet", &nJet_);
 
  tree->SetBranchStatus("Jet_pt",1);
  tree->SetBranchAddress("Jet_pt", &jetPt_);
	
  tree->SetBranchStatus("Jet_eta",1);
  tree->SetBranchAddress("Jet_eta", &jetEta_);
	
  tree->SetBranchStatus("Jet_phi",1);
  tree->SetBranchAddress("Jet_phi", &jetPhi_);

  tree->SetBranchStatus("Jet_mass",1);
  tree->SetBranchAddress("Jet_mass", &jetMass_);

  tree->SetBranchStatus("Jet_jetId",1);
  tree->SetBranchAddress("Jet_jetId", &jetID_);

  tree->SetBranchStatus("Jet_puId",1);
  tree->SetBranchAddress("Jet_puId", &jetPUID_);

  tree->SetBranchStatus("Jet_btagDeepFlavB",1);
  tree->SetBranchAddress("Jet_btagDeepFlavB", &jetBtagDeepFlavB_);

  // tree->SetBranchStatus("Jet_btagDeepFlavCvB",1);
  // tree->SetBranchAddress("Jet_btagDeepFlavCvB", &jetBtagDeepFlavCvB_);
  
  // tree->SetBranchStatus("Jet_btagDeepFlavCvL",1);
  // tree->SetBranchAddress("Jet_btagDeepFlavCvL", &jetBtagDeepFlavCvL_);
  
  tree->SetBranchStatus("Jet_partonFlavour",1);
  tree->SetBranchAddress("Jet_partonFlavour", &jetPartFlvr_);

  tree->SetBranchStatus("Jet_hadronFlavour",1);
  tree->SetBranchAddress("Jet_hadronFlavour", &jetHadFlvr_);
	
  tree->SetBranchStatus("Jet_genJetIdx",1);
  tree->SetBranchAddress("Jet_genJetIdx", &jetGenJetIdx_);
  ////////////////RecoJet////////////////////
  
  ///////////// HLT //////////////////////////
  tree->SetBranchStatus("HLT_IsoMu24",1);
  tree->SetBranchAddress("HLT_IsoMu24", &HLT_IsoMu24_);
  
  tree->SetBranchStatus("HLT_IsoTkMu24",1);
  tree->SetBranchAddress("HLT_IsoTkMu24", &HLT_IsoTkMu24_);

  tree->SetBranchStatus("HLT_Ele27_WPTight_Gsf",1);
  tree->SetBranchAddress("HLT_Ele27_WPTight_Gsf", &HLT_Ele27_WPTight_Gsf_);
  //////////////////////////////////////////////////

  /////////////////////////////////////////////////
  TLorentzVector pTemp, pTemp1;
  TLorentzVector pLHE[4]; int lhePDG[4]; int nPLHE = 0;
  TLorentzVector pGP[4], pGJ[4], pRJ[4], pRJAna[4];
  map<double,int, less<double>> delRtoID1;
  map<double,int, less<double>> delRtoID2;
  map<double,int, less<double>> delRtoID3;
  map<double,int, less<double>> delRtoID4;
  map<double, int>::iterator itr_ptr1, itr_ptr2, itr_ptr3, itr_ptr4;
  int refMC = 0;
  
  int nofLHEmu = 0, nofLHEele = 0, nofLHEtau = 0;
  bool isLHEmu = false, isLHEele = false, isLHEtau = false;
  
  int nofHLTmu = 0, nofHLTele = 0;  
  int muAsmu = 0, tauAsmu = 0, eleAsmu = 0;
  int muAsele = 0, tauAsele = 0, eleAsele = 0;

  int nofGPmu = 0, nofGPele = 0, nofGPtau = 0;
  
  cout << "Total tree entries : " <<  tree->GetEntries() << endl;
  
  ///////////////////////////////////////////////////////////////////////////////////////////////////////
  TH1F *dRMuLHEGP = new TH1F("dRMuLHEGP","dRMuLHEGP", 1000 , -0.1, 0.1);
  TH1F *dREleLHEGP = new TH1F("dREleLHEGP","dREleLHEGP", 1000 , -0.1, 0.1);
  TH1F *dRTauLHEGP = new TH1F("dRTauLHEGP","dRTauLHEGP", 1000 , -0.1, 0.1);
  TH1F *dRQdLHEGP = new TH1F("dRQdLHEGP","dRQ-d-LHEGP", 1000 , -0.1, 0.1);
  TH1F *dRQuLHEGP = new TH1F("dRQuLHEGP","dRQ-u-LHEGP", 1000 , -0.1, 0.1);
  TH1F *dRQsLHEGP = new TH1F("dRQsLHEGP","dRQ-s-LHEGP", 1000 , -0.1, 0.1);
  TH1F *dRQcLHEGP = new TH1F("dRQcLHEGP","dRQ-c-LHEGP", 1000 , -0.1, 0.1);

  TH1F *dRQdLHEGJ = new TH1F("dRQdLHEGJ","dRQ-d-LHEGJ", 1000 , -0.1, 0.1);
  TH1F *dRQuLHEGJ = new TH1F("dRQuLHEGJ","dRQ-u-LHEGJ", 1000 , -0.1, 0.1);
  TH1F *dRQsLHEGJ = new TH1F("dRQsLHEGJ","dRQ-s-LHEGJ", 1000 , -0.1, 0.1);
  TH1F *dRQcLHEGJ = new TH1F("dRQcLHEGJ","dRQ-c-LHEGJ", 1000 , -0.1, 0.1);
  TH1F *dRQdGPGJ = new TH1F("dRQdGPGJ","dRQ-d-GPGJ", 1000 , -0.1, 0.1);
  TH1F *dRQuGPGJ = new TH1F("dRQuGPGJ","dRQ-u-GPGJ", 1000 , -0.1, 0.1);
  TH1F *dRQsGPGJ = new TH1F("dRQsGPGJ","dRQ-s-GPGJ", 1000 , -0.1, 0.1);
  TH1F *dRQcGPGJ = new TH1F("dRQcGPGJ","dRQ-c-GPGJ", 1000 , -0.1, 0.1);

  TH1F *dRQdLHERJ = new TH1F("dRQdLHERJ","dRQ-d-LHERJ", 1000 , -0.1, 0.1);
  TH1F *dRQuLHERJ = new TH1F("dRQuLHERJ","dRQ-u-LHERJ", 1000 , -0.1, 0.1);
  TH1F *dRQsLHERJ = new TH1F("dRQsLHERJ","dRQ-s-LHERJ", 1000 , -0.1, 0.1);
  TH1F *dRQcLHERJ = new TH1F("dRQcLHERJ","dRQ-c-LHERJ", 1000 , -0.1, 0.1);
  TH1F *dRQdGPRJ = new TH1F("dRQdGPRJ","dRQ-d-GPRJ", 1000 , -0.1, 0.1);
  TH1F *dRQuGPRJ = new TH1F("dRQuGPRJ","dRQ-u-GPRJ", 1000 , -0.1, 0.1);
  TH1F *dRQsGPRJ = new TH1F("dRQsGPRJ","dRQ-s-GPRJ", 1000 , -0.1, 0.1);
  TH1F *dRQcGPRJ = new TH1F("dRQcGPRJ","dRQ-c-GPRJ", 1000 , -0.1, 0.1);
  TH1F *dRQdGJRJ = new TH1F("dRQdGJRJ","dRQ-d-GJRJ", 1000 , -0.1, 0.1);
  TH1F *dRQuGJRJ = new TH1F("dRQuGJRJ","dRQ-u-GJRJ", 1000 , -0.1, 0.1);
  TH1F *dRQsGJRJ = new TH1F("dRQsGJRJ","dRQ-s-GJRJ", 1000 , -0.1, 0.1);
  TH1F *dRQcGJRJ = new TH1F("dRQcGJRJ","dRQ-c-GJRJ", 1000 , -0.1, 0.1);

  //TH1F *dRMuLHEGP = new TH1F("dRMuLHEGP","dRMuLHEGP", 1000 , -0.1, 0.1);
  ///////////////////////////////////////////////////////////////////////////////////////////////////////
  
  //for(int ievent = 0; ievent < 1000 ; ievent++){
  for(int ievent = 0; ievent < tree->GetEntries() ; ievent++){
    
    //init
    isLHEmu = false; isLHEele = false; isLHEtau = false;
    HLT_IsoMu24_ = kFALSE ;  HLT_IsoTkMu24_ = kFALSE;
    HLT_Ele27_WPTight_Gsf_ = kFALSE;
    
    //getevent
    tree->GetEntry(ievent);
    
    //check trigger bit
    if(HLT_IsoMu24_ || HLT_IsoTkMu24_)
      nofHLTmu++;
    if(HLT_Ele27_WPTight_Gsf_)
      nofHLTele++;

    /////////////////////////////////////////////////////////////////
    //loop over LHE
    nPLHE = 0;
    for (unsigned int imc = nLHEPart_- 4 ; imc < nLHEPart_ ; imc++ ){
      if(TMath::Abs(LHEPart_pdgId_[imc])==11){
	isLHEele = true;
	nofLHEele++;
      }
      if(TMath::Abs(LHEPart_pdgId_[imc])==13){
	isLHEmu = true;
	nofLHEmu++;
      }
      if(TMath::Abs(LHEPart_pdgId_[imc])==15){
	isLHEtau = true;
	nofLHEtau++;
      }
      pLHE[nPLHE].SetPtEtaPhiM(LHEPart_pt_[imc], LHEPart_eta_[imc] , LHEPart_phi_[imc], LHEPart_mass_[imc]);
      lhePDG[nPLHE] = LHEPart_pdgId_[imc];
      nPLHE++;
    }//LHE loop
    /////////////////////////////////////////////////////////////////
    
    //////////////////////////////////////////////////////////////////////////////////
    //Check how many of original LHE leptons are identified as muon or electron by HLT
    if(HLT_IsoMu24_ || HLT_IsoTkMu24_){
      if(isLHEmu) muAsmu++;
      if(isLHEele) eleAsmu++;
      if(isLHEtau) tauAsmu++;
    }
    if(HLT_Ele27_WPTight_Gsf_){
      if(isLHEmu) muAsele++;
      if(isLHEele) eleAsele++;
      if(isLHEtau) tauAsele++;
    }
    //////////////////////////////////////////////////////////////////////////////////
    
    delRtoID1.clear(); delRtoID2.clear(); delRtoID3.clear(); delRtoID4.clear();
    for (unsigned int imc = 0 ; imc < nGenPart_ ; imc++ ){      
      
      pTemp.SetPtEtaPhiM(GenPart_pt_[imc], GenPart_eta_[imc] , GenPart_phi_[imc], GenPart_mass_[imc]);
      
      for(int ilhe=0;ilhe<nPLHE;ilhe++){
	if(lhePDG[ilhe]==GenPart_pdgId_[imc]){
	  float dR = pTemp.DeltaR(pLHE[ilhe]) ;
	  if(TMath::Abs(GenPart_pdgId_[imc])==11 and GenPart_pdgId_[GenPart_genPartIdxMother_[imc]]!=GenPart_pdgId_[imc] and TMath::Abs(GenPart_pdgId_[GenPart_genPartIdxMother_[imc]])==24){
	    dRMuLHEGP->Fill(dR);
	    nofGPele++;
	  }
	  if(TMath::Abs(GenPart_pdgId_[imc])==13 and GenPart_pdgId_[GenPart_genPartIdxMother_[imc]]!=GenPart_pdgId_[imc] and TMath::Abs(GenPart_pdgId_[GenPart_genPartIdxMother_[imc]])==24){
	    dREleLHEGP->Fill(dR);
	    nofGPmu++;
	  }
	  if(TMath::Abs(GenPart_pdgId_[imc])==15 and GenPart_pdgId_[GenPart_genPartIdxMother_[imc]]!=GenPart_pdgId_[imc] and TMath::Abs(GenPart_pdgId_[GenPart_genPartIdxMother_[imc]])==24){
	    dRTauLHEGP->Fill(dR);
	    nofGPtau++;
	  }
	  if(TMath::Abs(GenPart_pdgId_[imc])==1 and GenPart_pdgId_[GenPart_genPartIdxMother_[imc]]!=GenPart_pdgId_[imc] and TMath::Abs(GenPart_pdgId_[GenPart_genPartIdxMother_[imc]])==24){
	    delRtoID1.insert( pair<double,int> (dR, imc) );
	    dRQdLHEGP->Fill(dR);
	  }
	  if(TMath::Abs(GenPart_pdgId_[imc])==2 and GenPart_pdgId_[GenPart_genPartIdxMother_[imc]]!=GenPart_pdgId_[imc] and TMath::Abs(GenPart_pdgId_[GenPart_genPartIdxMother_[imc]])==24){
	    delRtoID2.insert( pair<double,int> (dR, imc) );
	    dRQuLHEGP->Fill(dR);
	  }
	  if(TMath::Abs(GenPart_pdgId_[imc])==3 and GenPart_pdgId_[GenPart_genPartIdxMother_[imc]]!=GenPart_pdgId_[imc] and TMath::Abs(GenPart_pdgId_[GenPart_genPartIdxMother_[imc]])==24){
	    delRtoID3.insert( pair<double,int> (dR, imc) );
	    dRQsLHEGP->Fill(dR);
	  }
	  if(TMath::Abs(GenPart_pdgId_[imc])==4 and GenPart_pdgId_[GenPart_genPartIdxMother_[imc]]!=GenPart_pdgId_[imc] and TMath::Abs(GenPart_pdgId_[GenPart_genPartIdxMother_[imc]])==24){
	    delRtoID4.insert( pair<double,int> (dR, imc) );
	    dRQcLHEGP->Fill(dR);
	  }

	}//check if PDG matching
      }//inner lhe
    }//GP loop
    if(delRtoID1.size()>0){
      itr_ptr1 = delRtoID1.begin(); refMC = itr_ptr1->second;
      pGP[0].SetPtEtaPhiM(GenPart_pt_[refMC], GenPart_eta_[refMC] , GenPart_phi_[refMC], GenPart_mass_[refMC]);
    }
    if(delRtoID2.size()>0){
      itr_ptr2 = delRtoID2.begin(); refMC = itr_ptr2->second;
      pGP[1].SetPtEtaPhiM(GenPart_pt_[refMC], GenPart_eta_[refMC] , GenPart_phi_[refMC], GenPart_mass_[refMC]);
    }
    if(delRtoID3.size()>0){
      itr_ptr3 = delRtoID3.begin(); refMC = itr_ptr3->second;
      pGP[2].SetPtEtaPhiM(GenPart_pt_[refMC], GenPart_eta_[refMC] , GenPart_phi_[refMC], GenPart_mass_[refMC]);
    }
    if(delRtoID4.size()>0){
      itr_ptr4 = delRtoID4.begin(); refMC = itr_ptr4->second;
      pGP[3].SetPtEtaPhiM(GenPart_pt_[refMC], GenPart_eta_[refMC] , GenPart_phi_[refMC], GenPart_mass_[refMC]);
    }
    
    for (unsigned int igj = 0 ; igj < nGenJet_ ; igj++ ){      

      pTemp.SetPtEtaPhiM(GenJet_pt_[igj], GenJet_eta_[igj] , GenJet_phi_[igj], GenJet_mass_[igj]);
      
      for(int ilhe=0;ilhe<nPLHE;ilhe++){
	if(lhePDG[ilhe]==GenJet_partonFlavour_[igj]){
	  float dR = pTemp.DeltaR(pLHE[ilhe]) ;
	  if(TMath::Abs(GenJet_partonFlavour_[igj])==1){
	    dRQdLHEGJ->Fill(dR);
	    if(delRtoID1.size()>0) dRQdGPGJ->Fill(pTemp.DeltaR(pGP[0])) ;
	  }
	  if(TMath::Abs(GenJet_partonFlavour_[igj])==2){
	    dRQuLHEGJ->Fill(dR);
	    if(delRtoID2.size()>0) dRQuGPGJ->Fill(pTemp.DeltaR(pGP[1])) ;
	  }
	  if(TMath::Abs(GenJet_partonFlavour_[igj])==3){
	    dRQsLHEGJ->Fill(dR);
	    if(delRtoID3.size()>0) dRQsGPGJ->Fill(pTemp.DeltaR(pGP[2])) ;
	  }
	  if(TMath::Abs(GenJet_partonFlavour_[igj])==4){
	    dRQcLHEGJ->Fill(dR);
	    if(delRtoID4.size()>0) dRQcGPGJ->Fill(pTemp.DeltaR(pGP[3])) ;
	  }

	}//check if PDG matching
      }//inner lhe
    }//GJ loop

    for (unsigned int irec = 0 ; irec < nGenJet_ ; irec++ ){      

      int igj = jetGenJetIdx_[irec];
      if(igj<0 or igj>=int(nGenJet_)) continue;
      
      pTemp.SetPtEtaPhiM(jetPt_[irec], jetEta_[irec] , jetPhi_[irec], jetMass_[irec]);
      pTemp1.SetPtEtaPhiM(GenJet_pt_[igj], GenJet_eta_[igj] , GenJet_phi_[igj], GenJet_mass_[igj]);

      for(int ilhe=0;ilhe<nPLHE;ilhe++){
      	if(lhePDG[ilhe]==jetPartFlvr_[irec]){
      	  float dR = pTemp.DeltaR(pLHE[ilhe]) ;
	  float dR1 = pTemp.DeltaR(pTemp1) ;
	  
      	  if(TMath::Abs(jetPartFlvr_[irec])==1){
      	    dRQdLHERJ->Fill(dR);
      	    if(delRtoID1.size()>0) dRQdGPRJ->Fill(pTemp.DeltaR(pGP[0])) ;
	    dRQdGJRJ->Fill(dR1);
      	  }
      	  if(TMath::Abs(jetPartFlvr_[irec])==2){
      	    dRQuLHERJ->Fill(dR);
      	    if(delRtoID2.size()>0) dRQuGPRJ->Fill(pTemp.DeltaR(pGP[1])) ;
	    dRQuGJRJ->Fill(dR1);
      	  }
      	  if(TMath::Abs(jetPartFlvr_[irec])==3){
      	    dRQsLHERJ->Fill(dR);
      	    if(delRtoID3.size()>0) dRQsGPRJ->Fill(pTemp.DeltaR(pGP[2])) ;
	    dRQsGJRJ->Fill(dR1);
      	  }
      	  if(TMath::Abs(jetPartFlvr_[irec])==4){
      	    dRQcLHERJ->Fill(dR);
      	    if(delRtoID4.size()>0) dRQcGPRJ->Fill(pTemp.DeltaR(pGP[3])) ;
	    dRQcGJRJ->Fill(dR1);
      	  }

      	}//check if PDG matching
      }//inner lhe
    }//GJ loop

  }//event loop
  ///////////////////////////////////////////////////////////////////////////////////////////////////////
  
  printf("nofHLTmu : %d, nofHLTele : %d, total : %d\n", nofHLTmu, nofHLTele,(nofHLTmu+nofHLTele));
  printf("nofLHEmu : %d, nofLHEele : %d, nofLHEtau : %d, total : %d\n", nofLHEmu, nofLHEele, nofLHEtau, (nofLHEmu+nofLHEele+nofLHEtau));
  printf("muAsmu : %d, eleAsmu : %d, tauAsmu : %d, total : %d\n", muAsmu, eleAsmu, tauAsmu, (muAsmu+eleAsmu+tauAsmu));
  printf("muAsele : %d, eleAsele : %d, tauAsele : %d, total : %d\n", muAsele, eleAsele, tauAsele, (muAsele+eleAsele+tauAsele));
  printf("nofGPmu : %d, nofGPele : %d, nofGPtau : %d, total : %d\n", nofGPmu, nofGPele, nofGPtau, (nofGPmu+nofGPele+nofGPtau));

  TFile *fout = TFile::Open("output/output.root","recreate");
  dRMuLHEGP->Write();
  dREleLHEGP->Write();
  dRTauLHEGP->Write();
  dRQdLHEGP->Write();
  dRQuLHEGP->Write();
  dRQsLHEGP->Write();
  dRQcLHEGP->Write();
  dRQdLHEGJ->Write();
  dRQuLHEGJ->Write();
  dRQsLHEGJ->Write();
  dRQcLHEGJ->Write();
  dRQdGPGJ->Write();
  dRQuGPGJ->Write();
  dRQsGPGJ->Write();
  dRQcGPGJ->Write();
  dRQdLHERJ->Write();
  dRQuLHERJ->Write();
  dRQsLHERJ->Write();
  dRQcLHERJ->Write();
  dRQdGPRJ->Write();
  dRQuGPRJ->Write();
  dRQsGPRJ->Write();
  dRQcGPRJ->Write();
  dRQdGJRJ->Write();
  dRQuGJRJ->Write();
  dRQsGJRJ->Write();
  dRQcGJRJ->Write();
  fout->Close();

  delete fout;
  delete fin;
  
  return true;
}
