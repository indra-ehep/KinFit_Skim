/**********************************************************************
 Created on : 13/11/2021
 Purpose    : Study the fraction of events for semileptonic, hadronic and 
              dileptonic channel for powheg processes. The following code 
              will not produce desired result for Madgraph production.

// First create the input file as
// for i in `dasgoclient --query='file dataset=/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8/RunIISummer16NanoAODv6-PUMoriond17_Nano25Oct2019_102X_mcRun2_asymptotic_v7-v2/NANOAODSIM status=*'` ; do echo root://cms-xrd-global.cern.ch/$i >> input/files.txt ; done
// Then run on the input/files.txt

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


int MCChannelStudy(int index = 1, string inputfile = "input/files.txt")
{
  TChain *chain = new TChain("Events");

  ifstream fin(inputfile.c_str());
  string s;
  string inputname = inputfile.substr(inputfile.find_last_of("/")+1,inputfile.find_last_of(".")-inputfile.find_last_of("/")-1);
  cout << "input filename name : " << inputname << endl;
  int i = 0;
  while(getline(fin,s)){
    if(i==index){
      cout << "Processing for index : " << index << " and file : " <<  s << endl;
      chain->Add(s.c_str());
    }
    i++;
  }
  fin.close();
  cout << "Total Events : " << chain->GetEntries() << endl;
  
  TH1D *hEvtCount = new TH1D("hEvtCount","hEvtCount",10,0.,10.);
  UInt_t	nLHEPart_;    
  Float_t	LHEPart_pt_[50];
  Float_t	LHEPart_eta_[50];
  Float_t	LHEPart_phi_[50];
  Float_t	LHEPart_mass_[50];
  Int_t		LHEPart_pdgId_[50];
  
  chain->SetBranchAddress("nLHEPart", &nLHEPart_);
  chain->SetBranchAddress("LHEPart_pt", &LHEPart_pt_);
  chain->SetBranchAddress("LHEPart_eta", &LHEPart_eta_);
  chain->SetBranchAddress("LHEPart_phi", &LHEPart_phi_);
  chain->SetBranchAddress("LHEPart_mass", &LHEPart_mass_);
  chain->SetBranchAddress("LHEPart_pdgId", &LHEPart_pdgId_);
  
  Long64_t nofSemiLeptonic = 0 , nofHadronic = 0 , nofDileptonic = 0 ;

  for (Long64_t ievent = 0 ; ievent < chain->GetEntries() ; ievent++ ) {
  //for (Long64_t ievent = 0 ; ievent < 1000 ; ievent++ ) {
    

    chain->GetEntry(ievent);
    
    if(ievent%1000==0)//Print after 10K or one or 10 million
      printf("Processing Event : %lld of total : %lld\n",ievent,chain->GetEntries());

    bool isOne_u = false, isOne_d = false, isOne_c = false, isOne_s = false;
    bool isTwo_u = false, isTwo_d = false, isTwo_c = false, isTwo_s = false;
    // bool isThree_u = false, isThree_d = false, isThree_c = false, isThree_s = false;
    // bool isFour_u = false, isFour_d = false, isFour_c = false, isFour_s = false;
    bool isOne_e = false, isOne_m = false, isOne_t = false;
    bool isTwo_e = false, isTwo_m = false, isTwo_t = false;
    bool isOne_nu_e = false, isOne_nu_m = false, isOne_nu_t = false;
    bool isTwo_nu_e = false, isTwo_nu_m = false, isTwo_nu_t = false;

    for (unsigned int imc = (nLHEPart_-4) ; imc < nLHEPart_ ; imc++ ){      //Check the last four particles

      // if(ievent < 1000){
      // 	TParticlePDG *partPDG = TDatabasePDG::Instance()->GetParticle(LHEPart_pdgId_[imc]);
	
      // 	if(!partPDG){
      // 	  printf("\t LHE : %03d, PDG : %5d ( noPDGname), (Pt, Eta, Phi, Mass) = (%5.2f, %5.2f, %5.2f, %5.2f)\n", 
      // 		 imc, LHEPart_pdgId_[imc], LHEPart_pt_[imc], 
      // 		 LHEPart_eta_[imc] , LHEPart_phi_[imc], LHEPart_mass_[imc]);
	
      // 	}else{
      // 	  printf("\t LHE : %03d, PDG : %5d (%7s), (Pt, Eta, Phi, Mass) = (%5.2f, %5.2f, %5.2f, %5.2f)\n", 
      // 		 imc, LHEPart_pdgId_[imc], partPDG->GetName(), LHEPart_pt_[imc],
      // 		 LHEPart_eta_[imc] , LHEPart_phi_[imc], LHEPart_mass_[imc]);
      // 	}
      // }

      if(abs(LHEPart_pdgId_[imc])==1 and isOne_d) isTwo_d = true; // Two must be above one lepton/parton condition
      if(abs(LHEPart_pdgId_[imc])==1 and !isOne_d) isOne_d = true;
      if(abs(LHEPart_pdgId_[imc])==2 and isOne_u) isTwo_u = true;
      if(abs(LHEPart_pdgId_[imc])==2 and !isOne_u) isOne_u = true;
      if(abs(LHEPart_pdgId_[imc])==3 and isOne_s) isTwo_s = true;
      if(abs(LHEPart_pdgId_[imc])==3 and !isOne_s) isOne_s = true;
      if(abs(LHEPart_pdgId_[imc])==4 and isOne_c) isTwo_c = true;
      if(abs(LHEPart_pdgId_[imc])==4 and !isOne_c) isOne_c = true;

      if(abs(LHEPart_pdgId_[imc])==11 and isOne_e) isTwo_e = true;
      if(abs(LHEPart_pdgId_[imc])==11 and !isOne_e) isOne_e = true;
      if(abs(LHEPart_pdgId_[imc])==13 and isOne_m) isTwo_m = true;
      if(abs(LHEPart_pdgId_[imc])==13 and !isOne_m) isOne_m = true;
      if(abs(LHEPart_pdgId_[imc])==15 and isOne_t) isTwo_t = true;
      if(abs(LHEPart_pdgId_[imc])==15 and !isOne_t) isOne_t = true;


      if(abs(LHEPart_pdgId_[imc])==12 and isOne_nu_e) isTwo_nu_e = true;
      if(abs(LHEPart_pdgId_[imc])==12 and !isOne_nu_e) isOne_nu_e = true;
      if(abs(LHEPart_pdgId_[imc])==14 and isOne_nu_m) isTwo_nu_m = true;
      if(abs(LHEPart_pdgId_[imc])==14 and !isOne_nu_m) isOne_nu_m = true;
      if(abs(LHEPart_pdgId_[imc])==16 and isOne_nu_t) isTwo_nu_t = true;
      if(abs(LHEPart_pdgId_[imc])==16 and !isOne_nu_t) isOne_nu_t = true;

      
      
    }// mc particle loop
    
    bool isSemilepton = false, isDilepton = false, isHadronic = false;

    bool isSameFlavlepton = (isTwo_nu_e and isTwo_e) or (isTwo_nu_m and isTwo_m) or (isTwo_nu_t and isTwo_t) ;
    bool isDiffFlavlepton = (isOne_e and isOne_nu_e and isOne_m and isOne_nu_m) 
                              or (isOne_e and isOne_nu_e and isOne_t and isOne_nu_t) 
                              or (isOne_m and isOne_nu_m and isOne_t and isOne_nu_t);
    if(isSameFlavlepton or isDiffFlavlepton){
      isDilepton = true;
      nofDileptonic++ ;
      //printf("Event type : dileptonic\n");
    }

    if(!isDilepton){
      bool isFourHadron1 = isOne_u and isOne_d and isOne_c and isOne_s;
      bool isFourHadron2 = (isTwo_u and isOne_d and isOne_c) or (isTwo_u and isOne_d and isOne_s) or (isTwo_u and isOne_c and isOne_s) ;
      bool isFourHadron3 = (isTwo_d and isOne_u and isOne_c) or (isTwo_d and isOne_u and isOne_s) or (isTwo_d and isOne_c and isOne_s) ;
      bool isFourHadron4 = (isTwo_c and isOne_u and isOne_d) or (isTwo_c and isOne_u and isOne_s) or (isTwo_c and isOne_d and isOne_s) ;
      bool isFourHadron5 = (isTwo_s and isOne_u and isOne_d) or (isTwo_s and isOne_u and isOne_c) or (isTwo_s and isOne_d and isOne_c) ;
      bool isFourHadron6 = (isTwo_u and isTwo_d) or (isTwo_u and isTwo_c) or (isTwo_u and isTwo_s) or (isTwo_d and isTwo_c) or (isTwo_d and isTwo_s) or (isTwo_c and isTwo_s);
      if(isFourHadron1 or isFourHadron2 or isFourHadron3 or isFourHadron4 or isFourHadron5 or isFourHadron6){
	isHadronic = true;
	nofHadronic++;
	//printf("Event type : hadronic\n");
      }
    }

    if(!isDilepton and !isHadronic){
      bool isOneLepton = (isOne_e and isOne_nu_e) or (isOne_m and isOne_nu_m) or (isOne_t and isOne_nu_t);
      bool isOneHadron = (isOne_u and isOne_d) or (isOne_u and isOne_c) or (isOne_u and isOne_s) or (isOne_d and isOne_c) or (isOne_d and isOne_s) or (isOne_c and isOne_s) ;
      if(isOneLepton and isOneLepton){
	isSemilepton = true;
	nofSemiLeptonic++;
	//printf("Event type : semileptonic\n");
      }
    }

    if(!isDilepton and !isHadronic and !isSemilepton){
      printf("Not identified Event : %lld\n",ievent);
      for (unsigned int imc = 0 ; imc < nLHEPart_ ; imc++ ){      
 
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
      }//LHEPart loop
    }//not (dilepton or semilepton or hadronic) channel 
    
  }//event loop;
  
  Long64_t totalIdentified = nofSemiLeptonic + nofHadronic + nofDileptonic ;
  printf("\nTotal Events : %lld\n",chain->GetEntries());
  printf("Total Identified : %lld\n\n",totalIdentified);
  
  printf("Total dileptonic : %lld\n",nofDileptonic);
  printf("Total hadronic : %lld\n",nofHadronic);
  printf("Total semileptonic : %lld\n\n",nofSemiLeptonic);
  
  hEvtCount->SetBinContent(1,chain->GetEntries());
  hEvtCount->SetBinContent(2,totalIdentified);
  hEvtCount->SetBinContent(3,chain->GetEntries()-totalIdentified);
  hEvtCount->SetBinContent(4,nofDileptonic);
  hEvtCount->SetBinContent(5,nofHadronic);
  hEvtCount->SetBinContent(6,nofSemiLeptonic);
  
  if(totalIdentified == chain->GetEntries()) {
    double total_CS = 831.76;
    printf("Dileptonic CS : %lf\n",total_CS*double(nofDileptonic)/chain->GetEntries());
    printf("Hadronic CS : %lf\n",total_CS*double(nofHadronic)/chain->GetEntries());
    printf("Semileptonic CS : %lf\n\n",total_CS*double(nofSemiLeptonic)/chain->GetEntries());
  }
  
  delete chain;

  TFile *fout = TFile::Open(Form("EventCount_%s_%02d.root",inputname.c_str(),index),"recreate");
  hEvtCount->Write();
  fout->Close();
  delete fout;

  return true;
}
