/**********************************************************************
 Created on : 26/03/2023
 Purpose    : Prepare the plots according to the Skim file requirments
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
#include "TProfile.h"
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

int SkimPlots()
{
  //string infile = "/Data/root_files/AOD_files/NanoAODUL/2016/Data_SingleEle_h_postVFP_Skim_NanoAOD_1of16.root";
  //string infile = "/Data/root_files/AOD_files/NanoAODUL/2016/Data_SingleMu_c_preVFP_Skim_NanoAOD_1of5.root";
  //ring infile = "/run/media/indra/DHEP_Storage_3/Data/NanoAOD/Skim_NanoAODUL/2016/QCD_Pt15to20_Mu_postVFP_Skim_NanoAOD_1of4.root";
  //string infile = "/run/media/indra/DHEP_Storage_3/Data/NanoAOD/Skim_NanoAODUL/2016/HminusM080_postVFP_Skim_NanoAOD.root";
  //string infile = "/run/media/indra/DHEP_Storage_3/Data/NanoAOD/Skim_NanoAODUL/2016/TTbarPowheg_Semilept_postVFP_Skim_NanoAOD_1of27.root";
  // string infile = "/run/media/indra/DHEP_Storage_3/Data/NanoAOD/Skim_NanoAODUL/2016/Data_SingleMu_h_postVFP_Skim_NanoAOD_15of16.root";

  // TFile *fin = TFile::Open(infile.c_str());
  // TTree *tr = (TTree *)fin->Get("Events");

  string signal = "QCD";
  int year = 2016;
  string inpath_tree = Form("/run/media/indra/DHEP_Storage_3/Data/NanoAOD/Skim_NanoAODUL/%d",year);
  //string inpath_tree = Form("/run/media/indra/DHEP_Storage_3/Data/NanoAOD/KinFit/CBA_elereliso/");
  string treelist = "/tmp/fl_tree_list.txt";
  string command = Form("find %s -name \"%s_Pt*_Mu_*.root\" > %s",inpath_tree.data(),signal.data(),treelist.data());
  system(command.c_str());
  
  cout<<"filepath : " << inpath_tree.data() << endl;
  string flist;
  ifstream fin(treelist);
  TChain *tr	= new TChain("Events");
  while ( getline(fin,flist)){
    //cout << "Filename : " << flist << endl;
    tr->Add(flist.c_str());
  }
  fin.close();

  tr->SetBranchStatus("*",0);
  tr->SetBranchStatus("MET_pt", 1);
  tr->SetBranchStatus("Muon_pfRelIso03_all", 1);
  tr->SetBranchStatus("nMuon", 1);
  // tr->SetBranchStatus("HLT_IsoMu24", 1);
  // tr->SetBranchStatus("HLT_Mu20", 1);
  // tr->SetBranchStatus("HLT_TrkMu17", 1);
  
  Float_t METpt, MuIso;
  UInt_t nMu;
  //Bool_t HLT_IsoMu24, HLT_Mu20, HLT_TrkMu17;
  
  tr->SetBranchAddress("MET_pt", &METpt);
  tr->SetBranchAddress("Muon_pfRelIso03_all", &MuIso);
  tr->SetBranchAddress("nMuon", &nMu);
  // tr->SetBranchAddress("HLT_IsoMu24", &HLT_IsoMu24);
  // tr->SetBranchAddress("HLT_Mu20", &HLT_Mu20);
  // tr->SetBranchAddress("HLT_TrkMu17", &HLT_TrkMu17);
  
  TProfile *met_iso_mu_data = new TProfile("met_iso_mu_data", "met_iso_mu_data", 500, 0., 500, -0.25, 0.25);
  for (Long64_t ievent = 0 ; ievent < tr->GetEntries()/2 ; ievent++ ) {
    if(!(tr->GetEntry(ievent))) continue ;
    if(nMu==0) continue;
    //if(TMath::AreEqualAbs(Muon_pfRelIso03_all,0.0,1.-5)) continue;
    if(ievent%1000000==0)
      cout<<"iEvent : " << ievent << ", MET_pt : "<<METpt<< ", muiso : "<<MuIso<<endl;
    
    met_iso_mu_data->Fill(METpt, MuIso);
  }
  // fin->Close();
  // delete fin;
  
  TCanvas *c1 = new TCanvas("c1","c1");
  met_iso_mu_data->Draw();
  
  return true;
}
