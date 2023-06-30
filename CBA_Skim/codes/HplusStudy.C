/**********************************************************************
 Created on : 02/03/2023
 Purpose    : Study the kinematic variables of hplus
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

#include "TH1F.h"
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


//int HplusStudy(bool ishplus = 1, string infile = "/Data/root_files/AOD_files/NanoAODUL/2017/HminusM120_Skim_NanoAOD.root")
int HplusStudy(string infiletxt = "output/fl_hpm.txt")
//int HplusStudy(string infile = "/run/media/indra/DHEP_Storage_3/Data/NanoAOD/Skim_NanoAODUL/2017/HminusM160_Skim_NanoAOD.root")
{
  
  bool ishplus = 1; //Use this switch to run for hplus or ttbar
  
  TH1F *hPtHplus = new TH1F("hPtHplus","hPtHplus",250,0,250);
  TH1F *hEtaHplus = new TH1F("hEtaHplus","hEtaHplus",60,-3.0,3.0);
  TH1F *hPhiHplus = new TH1F("hPhiHplus","hPhiHplus",120,-6.0,6.0);
  TH1F *hMassHplus = new TH1F("hMassHplus","hMassHplus",2500,0,250);
  
  TH1F *hPtMuW = new TH1F("hPtMuW","W#rightarrow#mu",250,0,250);
  TH1F *hPtEleW = new TH1F("hPtEleW","W#rightarrow#it{e}",250,0,250);
  TH1F *hPtCH = new TH1F("hPtCH","H^{#pm}#rightarrow#it{cs}",250,0,250);
  TH1F *hPtSH = new TH1F("hPtSH","H^{#pm}#rightarrow#it{cs}",250,0,250);

  TH1F *hRelIsoMuW = new TH1F("hRelIsoMuW","W#rightarrow#mu (relIso)",300,-1,2);
  TH1F *hRelIsoMuAll = new TH1F("hRelIsoMuAll","hRelIsoMuAll",300,-1,2);
  
  TH1F *hRelIsoEleWEB = new TH1F("hRelIsoEleWEB","W#rightarrow#it{e} (relIso)",300,-1,2);
  TH1F *hRelIsoEleAllEB = new TH1F("hRelIsoEleAllEB","hRelIsoEleAllEB",300,-1,2);
  TH1F *hRelIsoEleWEE = new TH1F("hRelIsoEleWEE","W#rightarrow#it{e} (relIso)",300,-1,2);
  TH1F *hRelIsoEleAllEE = new TH1F("hRelIsoEleAllEE","hRelIsoEleAllEE",300,-1,2);

  int momPDG = (ishplus) ? 37 : 24 ; //hplus or W+
  
  bool HasFoundTopology(UInt_t& nGenPart_, Int_t GenPart_pdgId_[], Int_t GenPart_genPartIdxMother_[], 
			Float_t GenPart_pt_[], Float_t GenPart_eta_[], Float_t GenPart_phi_[], Float_t GenPart_mass_[],
			int GrandMomPDG/*top*/, int MomPDG/*H+ or W+*/, int Daughter1_PDG/*c*/, int Daughter2_PDG/*s_bar*/, 
			double& cosTheta/*cosine theta*/);
  
  double cosTheta = -1000.;  
  TH1F *hCostheta, *hpTheta ;
  if(ishplus)
    hCostheta = new TH1F("hCostheta","charged higgs", 480, -2.0, 10.0);
  else
    hCostheta = new TH1F("hCostheta","SM t#bar{t}", 480, -2.0, 10.0);
  if(ishplus)
    hpTheta = new TH1F("hpTheta","charged higgs", 480, -2.0, 10.0);
  else
    hpTheta = new TH1F("hpTheta","SM t#bar{t}", 480, -2.0, 10.0);

  
  // TFile *fin = TFile::Open(infile.c_str());
  // cout<<"Reading from file : "<< fin->GetName() << endl;
  // TTree *tr = (TTree *)fin->Get("Events");
  TChain *tr = new TChain("Events");
  ifstream fin(infiletxt);
  string fname;
  while(getline(fin,fname)){
    cout << "fname : " << fname << endl;
    tr->Add(fname.c_str());
  }
  
  // return true;
  
  UInt_t	nLHEPart_;    
  Float_t	LHEPart_pt_[100];
  Float_t	LHEPart_eta_[100];
  Float_t	LHEPart_phi_[100];
  Float_t	LHEPart_mass_[100];
  Int_t		LHEPart_pdgId_[100];

  UInt_t	nGenPart_;
  Float_t	GenPart_pt_[300];
  Float_t	GenPart_eta_[300];
  Float_t	GenPart_phi_[300];
  Float_t	GenPart_mass_[300];
  Int_t		GenPart_genPartIdxMother_[300];
  Int_t		GenPart_pdgId_[300];
  Int_t		GenPart_status_[300];
  Int_t		GenPart_statusFlags_[300];

  UInt_t	nGenJet_;    
  Float_t	GenJet_pt_[100];
  Float_t	GenJet_eta_[100];
  Float_t	GenJet_phi_[100];
  Float_t	GenJet_mass_[100];
  Int_t		GenJet_partonFlavour_[100];
  Int_t		GenJet_hadronFlavour_[100];
  
  UInt_t        nJet_;
  Float_t       jetPt_[200];
  Float_t       jetEta_[200];
  Float_t       jetPhi_[200];
  Float_t       jetMass_[200];
  Int_t         jetHadFlvr_[200];
  Int_t         jetPartFlvr_[200];
  Int_t         jetGenJetIdx_[200];
  
  UInt_t          nMuon_;
  Float_t         muPt_[15];
  Float_t         muEta_[15];
  Float_t         muPhi_[15];
  Int_t           muCharge_[15];
  Float_t         muPFRelIso_[15];
  Int_t           muGenPartIdx_[200];

  UInt_t          nEle_;
  Float_t         elePt_[20];
  Float_t         eleEta_[20];
  Float_t         eleDeltaEtaSC_[20];
  Float_t         elePhi_[20];
  Float_t         elePFRelIso_[20]; 
  Int_t           eleGenPartIdx_[20];

  TLorentzVector jetR, jetG;
  TLorentzVector recC, recS;
  
  tr->SetBranchStatus("*",0);
  tr->SetBranchStatus("nLHEPart", 1); tr->SetBranchAddress("nLHEPart", &nLHEPart_);
  tr->SetBranchStatus("LHEPart_pt", 1); tr->SetBranchAddress("LHEPart_pt", &LHEPart_pt_);
  tr->SetBranchStatus("LHEPart_eta", 1); tr->SetBranchAddress("LHEPart_eta", &LHEPart_eta_);
  tr->SetBranchStatus("LHEPart_phi", 1); tr->SetBranchAddress("LHEPart_phi", &LHEPart_phi_);
  tr->SetBranchStatus("LHEPart_mass", 1); tr->SetBranchAddress("LHEPart_mass", &LHEPart_mass_);
  tr->SetBranchStatus("LHEPart_pdgId", 1); tr->SetBranchAddress("LHEPart_pdgId", &LHEPart_pdgId_);
  
  tr->SetBranchStatus("nGenPart", 1); tr->SetBranchAddress("nGenPart", &nGenPart_);
  tr->SetBranchStatus("GenPart_pt", 1); tr->SetBranchAddress("GenPart_pt", &GenPart_pt_);
  tr->SetBranchStatus("GenPart_eta", 1); tr->SetBranchAddress("GenPart_eta", &GenPart_eta_);
  tr->SetBranchStatus("GenPart_phi", 1); tr->SetBranchAddress("GenPart_phi", &GenPart_phi_);
  tr->SetBranchStatus("GenPart_mass", 1); tr->SetBranchAddress("GenPart_mass", &GenPart_mass_);
  tr->SetBranchStatus("GenPart_genPartIdxMother", 1); tr->SetBranchAddress("GenPart_genPartIdxMother", &GenPart_genPartIdxMother_);
  tr->SetBranchStatus("GenPart_pdgId", 1); tr->SetBranchAddress("GenPart_pdgId", &GenPart_pdgId_);
  tr->SetBranchStatus("GenPart_status", 1); tr->SetBranchAddress("GenPart_status", &GenPart_status_);
  tr->SetBranchStatus("GenPart_statusFlags", 1); tr->SetBranchAddress("GenPart_statusFlags", &GenPart_statusFlags_);

  tr->SetBranchStatus("nGenJet", 1); tr->SetBranchAddress("nGenJet", &nGenJet_);
  tr->SetBranchStatus("GenJet_pt", 1); tr->SetBranchAddress("GenJet_pt", &GenJet_pt_);
  tr->SetBranchStatus("GenJet_eta", 1); tr->SetBranchAddress("GenJet_eta", &GenJet_eta_);
  tr->SetBranchStatus("GenJet_phi", 1); tr->SetBranchAddress("GenJet_phi", &GenJet_phi_);
  tr->SetBranchStatus("GenJet_mass", 1); tr->SetBranchAddress("GenJet_mass", &GenJet_mass_);
  tr->SetBranchStatus("GenJet_partonFlavour",1); tr->SetBranchAddress("GenJet_partonFlavour", &GenJet_partonFlavour_);
  tr->SetBranchStatus("GenJet_hadronFlavour",1); tr->SetBranchAddress("GenJet_hadronFlavour", &GenJet_hadronFlavour_);

  tr->SetBranchStatus("nJet",1); tr->SetBranchAddress("nJet", &nJet_);
  tr->SetBranchStatus("Jet_pt",1); tr->SetBranchAddress("Jet_pt", &jetPt_);
  tr->SetBranchStatus("Jet_eta",1); tr->SetBranchAddress("Jet_eta", &jetEta_);
  tr->SetBranchStatus("Jet_phi",1); tr->SetBranchAddress("Jet_phi", &jetPhi_);
  tr->SetBranchStatus("Jet_mass",1); tr->SetBranchAddress("Jet_mass", &jetMass_);
  tr->SetBranchStatus("Jet_hadronFlavour",1); tr->SetBranchAddress("Jet_hadronFlavour", &jetHadFlvr_);
  tr->SetBranchStatus("Jet_partonFlavour",1); tr->SetBranchAddress("Jet_partonFlavour", &jetPartFlvr_);
  tr->SetBranchStatus("Jet_genJetIdx",1); tr->SetBranchAddress("Jet_genJetIdx", &jetGenJetIdx_);
  
  tr->SetBranchStatus("nMuon",1); tr->SetBranchAddress("nMuon", &nMuon_);
  tr->SetBranchStatus("Muon_pt",1); tr->SetBranchAddress("Muon_pt", &muPt_);
  tr->SetBranchStatus("Muon_eta",1); tr->SetBranchAddress("Muon_eta", &muEta_);
  tr->SetBranchStatus("Muon_phi",1); tr->SetBranchAddress("Muon_phi", &muPhi_);
  tr->SetBranchStatus("Muon_charge",1); tr->SetBranchAddress("Muon_charge", &muCharge_);	
  tr->SetBranchStatus("Muon_pfRelIso03_all",1); tr->SetBranchAddress("Muon_pfRelIso03_all", &muPFRelIso_);
  tr->SetBranchStatus("Muon_genPartIdx",1); tr->SetBranchAddress("Muon_genPartIdx", &muGenPartIdx_);

  tr->SetBranchStatus("nElectron",1); tr->SetBranchAddress("nElectron", &nEle_);
  tr->SetBranchStatus("Electron_pt",1); tr->SetBranchAddress("Electron_pt", &elePt_);
  tr->SetBranchStatus("Electron_eta",1); tr->SetBranchAddress("Electron_eta", &eleEta_);
  tr->SetBranchStatus("Electron_deltaEtaSC",1); tr->SetBranchAddress("Electron_deltaEtaSC", &eleDeltaEtaSC_);
  tr->SetBranchStatus("Electron_phi",1); tr->SetBranchAddress("Electron_phi", &elePhi_);
  tr->SetBranchStatus("Electron_pfRelIso03_all",1); tr->SetBranchAddress("Electron_pfRelIso03_all", &elePFRelIso_);
  tr->SetBranchStatus("Electron_genPartIdx",1); tr->SetBranchAddress("Electron_genPartIdx", &eleGenPartIdx_);
  
  bool printLHE = false;
  bool printGenPart = false;
  Long64_t nevents = 100000;//2300636;//tr->GetEntries();
  
  for(Long64_t  ievent = 0 ; ievent < nevents ; ievent++){
    
    tr->GetEntry(ievent);
    
    for (unsigned int imc = 0 ; imc < nLHEPart_ ; imc++ ){      
      TParticlePDG *partPDG = TDatabasePDG::Instance()->GetParticle(LHEPart_pdgId_[imc]);
      if(printLHE){
  	if(!partPDG){
  	  printf("\t Event : %lld, LHE : %03d, PDG : %5d ( noPDGname), (Pt, Eta, Phi, Mass) = (%5.2f, %5.2f, %5.2f, %5.2f)\n", 
  		 ievent, imc, LHEPart_pdgId_[imc], LHEPart_pt_[imc], 
  		 LHEPart_eta_[imc] , LHEPart_phi_[imc], LHEPart_mass_[imc]);

  	}else{
  	  printf("\t Event : %lld, LHE : %03d, PDG : %5d (%7s), (Pt, Eta, Phi, Mass) = (%5.2f, %5.2f, %5.2f, %5.2f)\n", 
  		 ievent, imc, LHEPart_pdgId_[imc], partPDG->GetName(), LHEPart_pt_[imc],
  		 LHEPart_eta_[imc] , LHEPart_phi_[imc], LHEPart_mass_[imc]);
  	}
      }
    }// mc particle loop
    
    for (unsigned int imc = 0 ; imc < nGenPart_ ; imc++ ){      
      TParticlePDG *partPDG = TDatabasePDG::Instance()->GetParticle(GenPart_pdgId_[imc]);
      if(printGenPart){
  	if(!partPDG){
  	  printf("\t Event : %lld, id : %03d, PDG : %5d ( noPDGname), status : %2d, (Pt, Eta, Phi, Mass) = (%5.2f, %5.2f, %5.2f, %5.2f), Mother-id : %03d\n", 
  		 ievent, imc, GenPart_pdgId_[imc], GenPart_status_[imc], GenPart_pt_[imc], 
  		 GenPart_eta_[imc] , GenPart_phi_[imc], GenPart_mass_[imc], GenPart_genPartIdxMother_[imc]
  		 );
  	}else{
  	  printf("\t Event : %lld, id : %03d, PDG : %5d (%7s), status : %2d, (Pt, Eta, Phi, Mass) = (%5.2f, %5.2f, %5.2f, %5.2f), Mother-id : %03d\n", 
  		 ievent, imc, GenPart_pdgId_[imc], partPDG->GetName(), GenPart_status_[imc], GenPart_pt_[imc],
  		 GenPart_eta_[imc] , GenPart_phi_[imc], GenPart_mass_[imc], GenPart_genPartIdxMother_[imc]
  		 );
  	}
      }
      if(abs(GenPart_pdgId_[imc])==37 and abs(GenPart_pdgId_[GenPart_genPartIdxMother_[imc]])==6) {
      	hPtHplus->Fill(GenPart_pt_[imc]);
  	hEtaHplus->Fill(GenPart_eta_[imc]);
  	hPhiHplus->Fill(GenPart_phi_[imc]);
      }
      
      if(abs(GenPart_pdgId_[imc])==13 and abs(GenPart_pdgId_[GenPart_genPartIdxMother_[imc]])==24) {
  	hPtMuW->Fill(GenPart_pt_[imc]);
      }
      if(abs(GenPart_pdgId_[imc])==11 and abs(GenPart_pdgId_[GenPart_genPartIdxMother_[imc]])==24) {
  	hPtEleW->Fill(GenPart_pt_[imc]);
      }
      // if(abs(GenPart_pdgId_[imc])==4 and abs(GenPart_pdgId_[GenPart_genPartIdxMother_[imc]])==37) {
      // 	hPtCH->Fill(GenPart_pt_[imc]);
      // }
      // if(abs(GenPart_pdgId_[imc])==3 and abs(GenPart_pdgId_[GenPart_genPartIdxMother_[imc]])==37) {
      // 	hPtSH->Fill(GenPart_pt_[imc]);
      // }      
    }// mc particle loop

    if(HasFoundTopology(nGenPart_, GenPart_pdgId_, GenPart_genPartIdxMother_, 
  			GenPart_pt_, GenPart_eta_, GenPart_phi_, GenPart_mass_,
  			6, momPDG, 4, 3, 
  			cosTheta)){
      //cout<<"cosTheta : " << cosTheta << endl;
      hCostheta->Fill(cosTheta);
    }      
    
    for (unsigned int imu = 0 ; imu < nMuon_ ; imu++ ){
      int imc = muGenPartIdx_[imu];
      if(abs(GenPart_pdgId_[imc])==13 and abs(GenPart_pdgId_[GenPart_genPartIdxMother_[imc]])==24) {
  	hRelIsoMuW->Fill(muPFRelIso_[imu]);
      }
      hRelIsoMuAll->Fill(muPFRelIso_[imu]);
    }
    
    for (unsigned int iele = 0 ; iele < nEle_ ; iele++ ){
      int imc = eleGenPartIdx_[iele];
      double eta = eleEta_[iele];
      double SCeta = eta + eleDeltaEtaSC_[iele];
      double absSCEta = TMath::Abs(SCeta);
      bool isEB = (absSCEta < 1.479) ? true : false ;
      if(abs(GenPart_pdgId_[imc])==11 and abs(GenPart_pdgId_[GenPart_genPartIdxMother_[imc]])==24) {
  	if(isEB)
  	  hRelIsoEleWEB->Fill(elePFRelIso_[iele]);
  	else
  	  hRelIsoEleWEE->Fill(elePFRelIso_[iele]);
      }
      if(isEB)
  	hRelIsoEleAllEB->Fill(elePFRelIso_[iele]);
      else
  	hRelIsoEleAllEE->Fill(elePFRelIso_[iele]);
    }
    
    
    bool hasRecC = false, hasRecS = false;
    for(int genJetId = 0; genJetId < int(nGenJet_); ++genJetId){
      
      bool hasFoundCGJRJ = false, hasFoundCGJGP = false;
      bool hasFoundSGJRJ = false, hasFoundSGJGP = false;
      double recPtC = 0.0, recPtS = 0.0;
      float delR = 10.0;
      int flav = TMath::Abs(GenJet_partonFlavour_[genJetId]);
      for(int jetInd = 0; jetInd < int(nJet_); ++jetInd){
  	int genIdx = int(jetGenJetIdx_[jetInd]);
  	if(genIdx==genJetId){
  	  jetG.SetPtEtaPhiM(GenJet_pt_[genJetId], GenJet_eta_[genJetId] , GenJet_phi_[genJetId], GenJet_mass_[genJetId]);
  	  jetR.SetPtEtaPhiM(jetPt_[jetInd], jetEta_[jetInd] , jetPhi_[jetInd], jetMass_[jetInd]);
  	  delR = jetR.DeltaR(jetG);
  	  if((delR<0.2) and flav==4){
  	    hasFoundCGJRJ = true;
  	    recPtC = jetPt_[jetInd];
  	    hasRecC = true;
  	    recC = jetG;
  	  }
  	  if((delR<0.2) and flav==3){
  	    hasFoundSGJRJ = true;
  	    recPtS = jetPt_[jetInd];
  	    hasRecS = true;
  	    recS = jetG;
  	  }
  	}//if Recojet matches with the current JenGet
      }//loop over Recojet
      
      for (unsigned int imc = 0 ; imc < nGenPart_ ; imc++ ){      
  	TParticlePDG *partPDG = TDatabasePDG::Instance()->GetParticle(GenPart_pdgId_[imc]);
  	if(abs(GenPart_pdgId_[imc])==4 and abs(GenPart_pdgId_[GenPart_genPartIdxMother_[imc]])==momPDG) {
  	  jetG.SetPtEtaPhiM(GenJet_pt_[genJetId], GenJet_eta_[genJetId] , GenJet_phi_[genJetId], GenJet_mass_[genJetId]);
  	  jetR.SetPtEtaPhiM(GenPart_pt_[imc], GenPart_eta_[imc] , GenPart_phi_[imc], GenPart_mass_[imc]);
  	  delR = jetR.DeltaR(jetG);
  	  if((delR<0.1) and flav==4) hasFoundCGJGP = true;
  	}
  	if(abs(GenPart_pdgId_[imc])==3 and abs(GenPart_pdgId_[GenPart_genPartIdxMother_[imc]])==momPDG) {
  	  jetG.SetPtEtaPhiM(GenJet_pt_[genJetId], GenJet_eta_[genJetId] , GenJet_phi_[genJetId], GenJet_mass_[genJetId]);
  	  jetR.SetPtEtaPhiM(GenPart_pt_[imc], GenPart_eta_[imc] , GenPart_phi_[imc], GenPart_mass_[imc]);
  	  delR = jetR.DeltaR(jetG);
  	  if((delR<0.1) and flav==3) hasFoundSGJGP = true;
  	}
      }
      if(hasFoundCGJRJ and hasFoundCGJGP)
  	hPtCH->Fill(recPtC);
      if(hasFoundSGJRJ and hasFoundSGJGP)
  	hPtSH->Fill(recPtS);
    }//loop over genJet
    if(hasRecC and hasRecS){
      hMassHplus->Fill((recC+recS).M());
      hpTheta->Fill(TMath::Abs(recC.E()-recS.E())/(recC+recS).P());
    }
    if(ievent%10000==0)
      printf("Processing Event : %03lld (total:%lld), npart : %u\n",ievent,tr->GetEntries(),nGenPart_);

    if(printGenPart or printLHE)
      printf("\n");
    
  }//event loop


  hPtMuW->SetLineColor(kRed);
  hPtEleW->SetLineColor(kBlue);
  hPtCH->SetLineColor(kRed);
  hPtSH->SetLineColor(kBlue);
  hRelIsoMuW->SetLineColor(kRed);
  hRelIsoMuAll->SetLineColor(kBlue);
  hRelIsoEleWEB->SetLineColor(kRed);
  hRelIsoEleAllEB->SetLineColor(kBlue);
  hRelIsoEleWEE->SetLineColor(kRed);
  hRelIsoEleAllEE->SetLineColor(kBlue);
  
  TCanvas *c0 = new TCanvas("c0","c0");
  c0->Divide(2,2);
  c0->cd(1);
  hPtHplus->Draw();
  c0->cd(2);
  hEtaHplus->Draw();
  c0->cd(3);
  hPhiHplus->Draw();
  c0->cd(4);
  hMassHplus->Draw();

  TCanvas *c1 = new TCanvas("c1","c1");
  c1->Divide(2,1);
  c1->cd(1);
  hPtMuW->Draw();
  c1->cd(2);
  hPtEleW->Draw();

  TCanvas *c2 = new TCanvas("c2","c2");
  c2->Divide(2,1);
  c2->cd(1);
  hPtCH->Draw();
  c2->cd(2);
  hPtSH->Draw();
  
  TCanvas *c3 = new TCanvas("c3","c3");
  c3->Divide(3,1);
  c3->cd(1)->SetLogy();
  hRelIsoMuAll->Draw();
  hRelIsoMuW->Draw("sames");
  c3->cd(2)->SetLogy();
  hRelIsoEleAllEB->Draw();
  hRelIsoEleWEB->Draw("sames");
  c3->cd(3)->SetLogy();
  hRelIsoEleAllEE->Draw();
  hRelIsoEleWEE->Draw("sames");
  
  TCanvas *c4 = new TCanvas("c4","c4");
  c4->Divide(2,1);
  c4->cd(1);
  hCostheta->Draw();
  c4->cd(2);
  hpTheta->Draw();
  
  // fin->Close();
  // delete fin;
  
  TFile *fout = TFile::Open("output.root","recreate");
  hCostheta->Write();
  hpTheta->Write();
  fout->Close();
  delete fout;
  
  return true;
}



bool HasFoundTopology(UInt_t& nGenPart_, Int_t GenPart_pdgId_[], Int_t GenPart_genPartIdxMother_[],
		      Float_t GenPart_pt_[], Float_t GenPart_eta_[], Float_t GenPart_phi_[], Float_t GenPart_mass_[],
		      int GrandMomPDG/*top*/, int MomPDG/*H+ or W+*/, int Daughter1_PDG/*c*/, int Daughter2_PDG/*s_bar*/, double& cosTheta/*cosine theta*/)
{
  
  // printf("\nNpart : %u\n",nGenPart_);
  // for (unsigned int imc = 0 ; imc < nGenPart_ ; imc++ ){      
  //   TParticlePDG *partPDG = TDatabasePDG::Instance()->GetParticle(GenPart_pdgId_[imc]);
  //   if(!partPDG){
  //     printf("\t id : %03d, PDG : %5d ( noPDGname), (Pt, Eta, Phi, Mass) = (%5.2f, %5.2f, %5.2f, %5.2f), Mother-id : %03d\n", 
  // 	     imc, GenPart_pdgId_[imc], GenPart_pt_[imc], 
  // 	     GenPart_eta_[imc] , GenPart_phi_[imc], GenPart_mass_[imc], GenPart_genPartIdxMother_[imc]
  // 	     );
  //   }else{
  // 	printf("\t id : %03d, PDG : %5d (%7s), (Pt, Eta, Phi, Mass) = (%5.2f, %5.2f, %5.2f, %5.2f), Mother-id : %03d\n", 
  // 	       imc, GenPart_pdgId_[imc], partPDG->GetName(), GenPart_pt_[imc],
  // 	       GenPart_eta_[imc] , GenPart_phi_[imc], GenPart_mass_[imc], GenPart_genPartIdxMother_[imc]
  // 	       );
  //   }
  // }
  // printf("\n");

  int pid_d1	= -9999;
  int ppid_d1	= -9999;
  int pid_d2	= -9999;
  int ppid_d2	= -9999;
  int pid_mom	= -9999;
  int ppid_mom	= -9999;
  int pid_gmom	= -9999;
  
  bool hasFound = false;
  for(int imc = int(nGenPart_) - 1 ; imc >= 2 ; imc-- ){ // 2 since the first two partciles are colliding particles
    
    if(GenPart_genPartIdxMother_[imc] < 0 or GenPart_genPartIdxMother_[imc] > (int(nGenPart_) - 1)) continue;
    int ppidPDG = TMath::Abs(GenPart_pdgId_[GenPart_genPartIdxMother_[imc]]) ;

    //cout<<"imc : " << imc<<", GenPart_pdgId_ : "<< GenPart_pdgId_[imc] <<", Daughter1_PDG : " << TMath::Abs(Daughter1_PDG) <<", ppidPDG : " << ppidPDG <<", momPDG : " << MomPDG << endl;
    if(TMath::Abs(GenPart_pdgId_[imc])==TMath::Abs(Daughter1_PDG) and ppidPDG==TMath::Abs(MomPDG)){
      pid_d1 = imc;
      ppid_d1 = GenPart_genPartIdxMother_[imc];
      //cout<<"1 : Charm found" << endl;
    }
    
    if(TMath::Abs(GenPart_pdgId_[imc])==TMath::Abs(Daughter2_PDG) and ppidPDG==TMath::Abs(MomPDG)){
      pid_d2 = imc;
      ppid_d2 = GenPart_genPartIdxMother_[imc];
      //cout<<"2 : Sbar found" << endl;
    }
    if(TMath::Abs(GenPart_pdgId_[imc])==TMath::Abs(MomPDG) and ppidPDG==TMath::Abs(GrandMomPDG)){
      pid_mom	= imc;
      ppid_mom	= GenPart_genPartIdxMother_[imc];
    }else if(TMath::Abs(GenPart_pdgId_[imc])==TMath::Abs(MomPDG) and ppidPDG==TMath::Abs(GrandMomPDG) and ppid_d1==ppid_d2 and imc==ppid_d2){
      pid_mom	= imc;
      ppid_mom	= GenPart_genPartIdxMother_[imc];
    }else if(TMath::Abs(GenPart_pdgId_[imc])==TMath::Abs(MomPDG) and ppidPDG==TMath::Abs(MomPDG) and ppid_d1==ppid_d2 and imc==ppid_d2){
      pid_mom	= imc;
      ppid_mom	= GenPart_genPartIdxMother_[imc];
      //cout<<"3 : Hplus found" << endl;
    }
    if(TMath::Abs(GenPart_pdgId_[imc])==TMath::Abs(GrandMomPDG) and ppid_mom==imc){
      pid_gmom = imc;
      hasFound = true;
      //cout<<"4 : top found" << endl;
    }
  }
  
  if(hasFound){
    
    TLorentzVector charm, sbar, hplus, top;
    
    charm.SetPtEtaPhiM(GenPart_pt_[pid_d1], GenPart_eta_[pid_d1], GenPart_phi_[pid_d1], GenPart_mass_[pid_d1]);
    sbar.SetPtEtaPhiM(GenPart_pt_[pid_d2], GenPart_eta_[pid_d2], GenPart_phi_[pid_d2], GenPart_mass_[pid_d2]);
    hplus.SetPtEtaPhiM(GenPart_pt_[pid_mom], GenPart_eta_[pid_mom], GenPart_phi_[pid_mom], GenPart_mass_[pid_mom]);
    top.SetPtEtaPhiM(GenPart_pt_[pid_gmom], GenPart_eta_[pid_gmom], GenPart_phi_[pid_gmom], GenPart_mass_[pid_gmom]);
    
    charm.Boost(-hplus.BoostVector());
    // sbar.Boost(-hplus.BoostVector());
    // printf("\t Charm : (Px, Py, Pz, E) = (%5.2f, %5.2f, %5.2f, %5.2f)\n", charm.Px(), charm.Py(), charm.Pz(), charm.E());  
    // printf("\t Sbar : (Px, Py, Pz, E) = (%5.2f, %5.2f, %5.2f, %5.2f)\n", sbar.Px(), sbar.Py(), sbar.Pz(), sbar.E());  
    // cout << "Charm " << charm.P() << " and sbar " << sbar.P() << endl;
    top.Boost(-hplus.BoostVector());
    TVector3 c3 = charm.Vect();
    //cosTheta = TMath::Cos(top.Angle(c3));
    cosTheta = TMath::Abs(charm.E()-sbar.E())/hplus.P();
    
  }
  
  return hasFound;
}
