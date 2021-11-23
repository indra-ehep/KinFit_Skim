/**********************************************************************
 Created on : 01/08/2021
 Purpose    : Read the MC information from skim file.
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

//int ReadMCInfoSkim(string infile = "/run/media/indra/DHEP_Storage_1/Data/NanoAOD/Skim_NanoAOD/2016/HplusM120_Skim_NanoAOD.root")
int ReadMCInfoSkim(string infile = "/run/media/indra/DHEP_Storage_1/Data/NanoAOD/Skim_NanoAOD/2016/TTbarPowheg_Semilept_Skim_NanoAOD_20of21.root")
//ReadMCInfoSkim()
{
  
  bool ishplus = 0; //Use this switch to run for hplus or ttbar

  int momPDG = (ishplus) ? 37 : 24 ; //hplus or W+
  // string infile;
  // if(ishplus)
  //   infile = "root://se01.indiacms.res.in:1094//cms/store/user/idas/Output/cms-hcs-run2/Skim_NanoAOD/2016/HplusM120_Skim_NanoAOD.root";
  // else
  //   infile = "root://se01.indiacms.res.in:1094//cms/store/user/idas/Output/cms-hcs-run2/Skim_NanoAOD/2016/TTbarPowheg_Semilept_Skim_NanoAOD_1of21.root";
  
  bool HasFoundTopology(UInt_t& nGenPart_, Int_t GenPart_pdgId_[], Int_t GenPart_genPartIdxMother_[], 
			Float_t GenPart_pt_[], Float_t GenPart_eta_[], Float_t GenPart_phi_[], Float_t GenPart_mass_[],
			int GrandMomPDG/*top*/, int MomPDG/*H+ or W+*/, int Daughter1_PDG/*c*/, int Daughter2_PDG/*s_bar*/, 
			double& cosTheta/*cosine theta*/);
  
  TFile *fin = TFile::Open(infile.c_str());
  cout<<"Reading from file : "<< fin->GetName() << endl;

  TTree *tr = (TTree *)fin->Get("Events");
  
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

  UInt_t    nLHEPart_;    
  Float_t   LHEPart_pt_[100];
  Float_t   LHEPart_eta_[100];
  Float_t   LHEPart_phi_[100];
  Float_t   LHEPart_mass_[100];
  Int_t   LHEPart_pdgId_[100];
  
  tr->SetBranchAddress("nGenPart", &nGenPart_);
  tr->SetBranchAddress("GenPart_pt", &GenPart_pt_);
  tr->SetBranchAddress("GenPart_eta", &GenPart_eta_);
  tr->SetBranchAddress("GenPart_phi", &GenPart_phi_);
  tr->SetBranchAddress("GenPart_mass", &GenPart_mass_);
  tr->SetBranchAddress("GenPart_genPartIdxMother", &GenPart_genPartIdxMother_);
  tr->SetBranchAddress("GenPart_pdgId", &GenPart_pdgId_);
  tr->SetBranchAddress("GenPart_status", &GenPart_status_);
  tr->SetBranchAddress("GenPart_statusFlags", &GenPart_statusFlags_);

  tr->SetBranchAddress("nGenJet", &nGenJet_);
  tr->SetBranchAddress("GenJet_pt", &GenJet_pt_);
  tr->SetBranchAddress("GenJet_eta", &GenJet_eta_);
  tr->SetBranchAddress("GenJet_phi", &GenJet_phi_);
  tr->SetBranchAddress("GenJet_mass", &GenJet_mass_);

  tr->SetBranchAddress("nLHEPart", &nLHEPart_);
  tr->SetBranchAddress("LHEPart_pt", &LHEPart_pt_);
  tr->SetBranchAddress("LHEPart_eta", &LHEPart_eta_);
  tr->SetBranchAddress("LHEPart_phi", &LHEPart_phi_);
  tr->SetBranchAddress("LHEPart_mass", &LHEPart_mass_);
  tr->SetBranchAddress("LHEPart_pdgId", &LHEPart_pdgId_);
  
  double cosTheta = -1000.;  
  
  TH1F *hCostheta ;
  if(ishplus)
    hCostheta = new TH1F("hCostheta","m_{H^{+}} = 120 GeV", 80, -2.0, 2.0);
  else
    hCostheta = new TH1F("hCostheta","SM t#bar{t}", 80, -2.0, 2.0);
  
  for(int ievent = 0 ; ievent < 10; ievent++){
  //for(int ievent = 0 ; ievent < tr->GetEntries() ; ievent++){
    
    tr->GetEntry(ievent);
    
    
    cosTheta = -1000.;
    // if(!HasFoundTopology(nGenPart_, GenPart_pdgId_, GenPart_genPartIdxMother_, 
    // 			 GenPart_pt_, GenPart_eta_, GenPart_phi_, GenPart_mass_,
    // 			 6, momPDG, 4, -3, 
    // 			 cosTheta)){
      
      //if(ievent%10000==0)
      printf("Event : %03d, npart : %u\n",ievent,nGenPart_);

      for (unsigned int imc = 0 ; imc < nLHEPart_ ; imc++ ){      
      //for (unsigned int imc = 0 ; imc < 30 ; imc++ ){      
	TParticlePDG *partPDG = TDatabasePDG::Instance()->GetParticle(LHEPart_pdgId_[imc]);
	if(!partPDG){
	  printf("\t LHE : %03d, PDG : %5d ( noPDGname), (Pt, Eta, Phi, Mass) = (%5.2f, %5.2f, %5.2f, %5.2f)\n", 
		 imc, LHEPart_pdgId_[imc], LHEPart_pt_[imc], 
		 LHEPart_eta_[imc] , LHEPart_phi_[imc], LHEPart_mass_[imc]);

	}else{
	  printf("\t LHE : %03d, PDG : %5d (%7s), (Pt, Eta, Phi, Mass) = (%5.2f, %5.2f, %5.2f, %5.2f)\n", 
		 imc, LHEPart_pdgId_[imc], partPDG->GetName(), LHEPart_pt_[imc],
		 LHEPart_eta_[imc] , LHEPart_phi_[imc], LHEPart_mass_[imc]);
	}
      }// mc particle loop

      //for (unsigned int imc = 0 ; imc < nGenPart_ ; imc++ ){      
      for (unsigned int imc = 0 ; imc < 30 ; imc++ ){      
    	TParticlePDG *partPDG = TDatabasePDG::Instance()->GetParticle(GenPart_pdgId_[imc]);
    	if(!partPDG){
    	  printf("\t id : %03d, PDG : %5d ( noPDGname), status : %2d, (Pt, Eta, Phi, Mass) = (%5.2f, %5.2f, %5.2f, %5.2f), Mother-id : %03d\n", 
    		 imc, GenPart_pdgId_[imc], GenPart_status_[imc], GenPart_pt_[imc], 
    		 GenPart_eta_[imc] , GenPart_phi_[imc], GenPart_mass_[imc], GenPart_genPartIdxMother_[imc]
    		 );
    	}else{
    	  printf("\t id : %03d, PDG : %5d (%7s), status : %2d, (Pt, Eta, Phi, Mass) = (%5.2f, %5.2f, %5.2f, %5.2f), Mother-id : %03d\n", 
    		 imc, GenPart_pdgId_[imc], partPDG->GetName(), GenPart_status_[imc], GenPart_pt_[imc],
    		 GenPart_eta_[imc] , GenPart_phi_[imc], GenPart_mass_[imc], GenPart_genPartIdxMother_[imc]
    		 );
    	}
      }// mc particle loop
    // }else{
      
      if(ievent%10000==0)
	printf("Processing Event : %03d (total:%lld), npart : %u\n",ievent,tr->GetEntries(),nGenPart_);
      
      //hCostheta->Fill(cosTheta);

      //}
  }//event loop


  // TFile *fout = new TFile("output.root","recreate");
  // hCostheta->Write();
  // fout->Close();
  // delete fout;

  fin->Close();
  delete fin;

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
    int ppidPDG = GenPart_pdgId_[GenPart_genPartIdxMother_[imc]] ;
    
    if(GenPart_pdgId_[imc]==Daughter1_PDG and ppidPDG==MomPDG){
      pid_d1 = imc;
      ppid_d1 = GenPart_genPartIdxMother_[imc];
      //cout<<"1 : Charm found" << endl;
    }
    
    if(GenPart_pdgId_[imc]==Daughter2_PDG and ppidPDG==MomPDG){
      pid_d2 = imc;
      ppid_d2 = GenPart_genPartIdxMother_[imc];
      //cout<<"2 : Sbar found" << endl;
    }
    if(GenPart_pdgId_[imc]==MomPDG and ppidPDG==GrandMomPDG){
      pid_mom	= imc;
      ppid_mom	= GenPart_genPartIdxMother_[imc];
    }else if(GenPart_pdgId_[imc]==MomPDG and ppidPDG==GrandMomPDG and ppid_d1==ppid_d2 and imc==ppid_d2){
      pid_mom	= imc;
      ppid_mom	= GenPart_genPartIdxMother_[imc];
    }else if(GenPart_pdgId_[imc]==MomPDG and ppidPDG==MomPDG and ppid_d1==ppid_d2 and imc==ppid_d2){
      pid_mom	= imc;
      ppid_mom	= GenPart_genPartIdxMother_[imc];
      //cout<<"3 : Hplus found" << endl;
    }
    if(GenPart_pdgId_[imc]==GrandMomPDG and ppid_mom==imc){
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
    cosTheta = TMath::Cos(top.Angle(c3));
    
  }
  
  return hasFound;
}
