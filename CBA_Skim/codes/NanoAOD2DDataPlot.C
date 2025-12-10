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

int NanoAOD2DDataPlot(const char* infile = "input/test/2018/tree_mu_data_ab.txt")
{

  UInt_t   nJet;
  Float_t  jetEta[200];
  Float_t  jetPhi[200];

  string treelist = infile;
  cout<<"input file : " << treelist.data() << endl;
  string flist;
  ifstream fin(treelist);
  TChain *tr	= new TChain("Events");
  while ( getline(fin,flist)){
    //cout << "Filename : " << flist << endl;
    tr->Add(flist.c_str());
  }
  fin.close();

  cout << "Total Entries : " << tr->GetEntries() << std::endl;
  
  tr->SetCacheSize(100*1024*1024);
  tr->SetBranchStatus("*",0);

  tr->SetBranchStatus("nJet",1);
  tr->SetBranchStatus("Jet_eta",1);
  tr->SetBranchStatus("Jet_phi",1);
  
  tr->SetBranchAddress("nJet", &nJet);
  tr->SetBranchAddress("Jet_eta", &jetEta);
  tr->SetBranchAddress("Jet_phi", &jetPhi);

  TH2D *hEtaPhi = new TH2D("hEtaPhi","NanoAOD: Jet #eta-#phi",1000,-6.0,6.0, 1000,-4.0,4.0);
  hEtaPhi->GetXaxis()->SetTitle("#eta^{jets}");
  hEtaPhi->GetYaxis()->SetTitle("#phi^{jets}");
  
  for (Long64_t ievent = 0 ; ievent < tr->GetEntries() ; ievent++ ) {    
  //for (Long64_t ievent = 0 ; ievent < tr->GetEntries()/10 ; ievent++ ) {
    
    tr->GetEntry(ievent) ;
    if(ievent%1000000==0)
      cout<<"iEvent : " << ievent <<endl;
    if(nJet>200) continue;
    for(UInt_t ijet = 0; ijet < nJet; ijet++)      
      hEtaPhi->Fill(jetEta[ijet], jetPhi[ijet]);
    
  }//event loop
  
  TFile *fout = TFile::Open("NanoAOD2DData.root","recreate");
  hEtaPhi->Write();
  fout->Close();
  delete fout;

  delete tr;

  return true;
}
