/**********************************************************************
 Created on : 17/07/2012
 Purpose    : plot the histograms from file
 Author     : Indranil Das, IPN Orsay
 Email      : indranil.das@cern.ch | indra.ehep@gmail.com
**********************************************************************/
#if !defined(__CINT__) || defined(__MAKECINT__)

#include <iostream>
#include <string>

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

//int GetTreeCount(const char *infile="output.root",const char* option="E")
int GetTreeCount()
{
  // TFile *fin = TFile::Open(infile);
  // if(!fin)
  //   return 1;

  // //TCanvas *c[100];
  // int icanvas=0;
  // gStyle->SetOptStat("ourmen");  
  
  const char *histname1 = "Muon_pt";
  const char *histname2 = "Electron_pt";

  TFile * fin = (TFile *)gROOT->GetListOfFiles()->At(0);

  TIter nextkey(fin->GetListOfKeys());
  TKey *key;
  while ( (key = (TKey*)nextkey()) ) {
    
    TObject *obj = key->ReadObj();
    //cout << "name : " << obj->GetName() << endl;
    
    if ( obj->IsA()->InheritsFrom( "TTree" ) ) {
      TTree *tr = (TTree*)obj;
      cout << "Tree  " <<  tr->GetName() << " has Entries :" << tr->GetEntries() << endl;
      tr->Draw(histname1);
      TH1F *hist1 = (TH1F *)((TCanvas *)gROOT->GetListOfCanvases()->At(0))->GetPrimitive("htemp");
      //cout<< "is underflow " << hist1->IsBinUnderflow(0) << ", is overflow " << hist1->IsBinOverflow(hist1->GetXaxis()->GetLast()+1) << endl;
      cout << "Histogram  " <<  histname1 << " has Entries :" << int(hist1->GetEntries()) << ": with mean :" << hist1->GetMean() << ": underflow :" << hist1->GetBinContent(0) << ": overflow :" << hist1->GetBinContent(hist1->GetXaxis()->GetLast()+1) <<":"<< endl;
      tr->Draw(histname2);
      TH1F *hist2 = (TH1F *)((TCanvas *)gROOT->GetListOfCanvases()->At(0))->GetPrimitive("htemp");
      cout << "Histogram  " <<  histname2 << " has Entries :" << int(hist2->GetEntries()) << ": with mean :" << hist2->GetMean() << ": underflow :" << hist2->GetBinContent(0) << ": overflow :" << hist2->GetBinContent(hist2->GetXaxis()->GetLast()+1) <<":"<< endl;

    }
    
  }//key loop
  fin->Close();
  delete fin;
  
  return 0;
}
