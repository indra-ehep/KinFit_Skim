/**********************************************************************
 Created on : 22/03/2023
 Purpose    : The studies to answer the PAG converner queries on v1
 Author     : Indranil Das, Visiting Fellow
 Email      : indranil.das@cern.ch | indra.ehep@gmail.com
**********************************************************************/
#if !defined(__CINT__) || defined(__MAKECINT__)

#include <TROOT.h>
#include <TChain.h>
#include <TEntryList.h>
#include <TFile.h>
//#include <TProofOutputFile.h>
#include <TSelector.h>
#include <vector>

#include "TH1F.h"
#include "TProfile.h"
#include <THStack.h>
#include "TH2.h"
#include "TF1.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TPaveStats.h"
#include "TMath.h"
//#include "TProof.h"

#include "TParticlePDG.h"
#include "TDatabasePDG.h"

#include "TLorentzVector.h"
#include "TVector3.h"

#include <fstream>

using namespace std;

#endif

int KF2DDataPlot(const char* infile = "input/test/2018/tree_mu_data_ab.txt")
{
  
  Float_t   jetBhadEta;
  Float_t   jetBhadPhi;
  
  Float_t   jetChadEta;
  Float_t   jetChadPhi;

  Float_t   jetShadEta;
  Float_t   jetShadPhi;

  Float_t   jetBlepEta;
  Float_t   jetBlepPhi;

  string treelist = infile;
  cout<<"input file : " << treelist.data() << endl;
  string flist;
  ifstream fin(treelist);
  TChain *tr	= new TChain("Kinfit_Reco");
  while ( getline(fin,flist)){
    //cout << "Filename : " << flist << endl;
    tr->Add(flist.c_str());
  }
  fin.close();

  cout << "Total Entries : " << tr->GetEntries() << std::endl;
  
  tr->SetCacheSize(100*1024*1024);
  tr->SetBranchStatus("*",0);
  
  tr->SetBranchStatus("jetBhadEta",1);  tr->SetBranchStatus("jetBhadPhi",1);
  tr->SetBranchAddress("jetBhadEta"	, &jetBhadEta);
  tr->SetBranchAddress("jetBhadPhi"	, &jetBhadPhi);
  
  tr->SetBranchStatus("jetChadEta",1);  tr->SetBranchStatus("jetChadPhi",1);
  tr->SetBranchAddress("jetChadEta"	, &jetChadEta);
  tr->SetBranchAddress("jetChadPhi"	, &jetChadPhi);
  
  tr->SetBranchStatus("jetShadEta",1);  tr->SetBranchStatus("jetShadPhi",1);
  tr->SetBranchAddress("jetShadEta"	, &jetShadEta);
  tr->SetBranchAddress("jetShadPhi"	, &jetShadPhi);
  
  tr->SetBranchStatus("jetBlepEta",1);  tr->SetBranchStatus("jetBlepPhi",1);
  tr->SetBranchAddress("jetBlepEta"	, &jetBlepEta);
  tr->SetBranchAddress("jetBlepPhi"	, &jetBlepPhi);


  TH2D *hEtaPhi = new TH2D("hEtaPhi","Kinfit: Jet #eta-#phi",1000,-6.0,6.0, 1000,-4.0,4.0);
  hEtaPhi->GetXaxis()->SetTitle("#eta^{jets}");
  hEtaPhi->GetYaxis()->SetTitle("#phi^{jets}");
  
  for (Long64_t ievent = 0 ; ievent < tr->GetEntries() ; ievent++ ) {    
  //for (Long64_t ievent = 0 ; ievent < tr->GetEntries()/10 ; ievent++ ) {    
    
    tr->GetEntry(ievent) ;
    if(ievent%1000000==0)
      cout<<"iEvent : " << ievent <<endl;
    hEtaPhi->Fill(jetBhadEta, jetBhadPhi);
    hEtaPhi->Fill(jetChadEta, jetChadPhi);
    hEtaPhi->Fill(jetShadEta, jetShadPhi);
    hEtaPhi->Fill(jetBlepEta, jetBlepPhi);
  }//event loop
  
  TFile *fout = TFile::Open("KF2DData.root","recreate");
  hEtaPhi->Write();
  fout->Close();
  delete fout;

  delete tr;

  return true;
}
