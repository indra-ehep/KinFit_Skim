/**********************************************************************
 Created on : 17/07/2012
 Purpose    : plot the histograms from file
 Author     : Indranil Das, IPN Orsay
 Email      : indranil.das@cern.ch | indra.ehep@gmail.com
**********************************************************************/
#if !defined(__CINT__) || defined(__MAKECINT__)

#include <iostream>
#include <string>
#include <vector>

#include <TFile.h>
#include <TF1.h>
#include "TH1F.h"
#include "TH2.h"
#include "TCanvas.h"
#include "TList.h"
#include "TTree.h"
#include "TCollection.h" // For TIter function
#include "TKey.h"
#include <TROOT.h>
#include "TObject.h"

using namespace std;

#endif

int GetTreeCountReco()
{
  
  const char *histname1 = "muPt";
  const char *histname2 = "elePt";
  std::vector<float> *_muPt = 0;
  std::vector<float> *_elePt = 0;
  TBranch *bvpt1 = 0;
  TBranch *bvpt2 = 0;

  TH1F *hMuPt = new TH1F("hMuPt","hMuPt",2000,0,2000.0);
  TH1F *hElePt = new TH1F("hElePt","hElePt",2000,0,2000.0);
  
  TFile * fin = (TFile *)gROOT->GetListOfFiles()->At(0);
  TTree *tr = (TTree*)fin->Get("RecoNtuple_Skim");

  cout << "Tree  " <<  tr->GetName() << " has Entries :" << tr->GetEntries() << endl;
      
  tr->SetBranchAddress(histname1, &_muPt, &bvpt1);
  tr->SetBranchAddress(histname2, &_elePt, &bvpt2);

  //cout << "Branch " << bvpt1 << " has Entries : " << bvpt->GetEntries() << endl;

  for (Long64_t i=0;i<tr->GetEntries();i++) {
    tr->GetEntry(i);
    for (int ipt = 0 ; ipt < int(_muPt->size()) ; ipt++ )
      hMuPt->Fill(_muPt->at(ipt));
  }
  cout << "Histogram  " <<  histname1 << " has Entries :" << int(hMuPt->GetEntries()) << ": with mean :" << hMuPt->GetMean() << ": underflow :" << hMuPt->GetBinContent(0) << ": overflow :" << hMuPt->GetBinContent(hMuPt->GetXaxis()->GetLast()+1) <<":"<< endl;

  for (Long64_t i=0;i<tr->GetEntries();i++) {
    tr->GetEntry(i);
    for (int ipt = 0 ; ipt < int(_elePt->size()) ; ipt++ )
      hElePt->Fill(_elePt->at(ipt));
  }
  cout << "Histogram  " <<  histname2 << " has Entries :" << int(hElePt->GetEntries()) << ": with mean :" << hElePt->GetMean() << ": underflow :" << hElePt->GetBinContent(0) << ": overflow :" << hElePt->GetBinContent(hElePt->GetXaxis()->GetLast()+1) <<":"<< endl;
  

  fin->Close();
  delete fin;
  
  // TCanvas *c1 = new TCanvas("c1","c1");
  // hElePt->Draw();

  return 0;
}
