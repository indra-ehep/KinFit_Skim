/**********************************************************************
 Created on : 17/10/2023
 Purpose    : Read the counts of Cutflow histograms of a sinlge file
 Author     : Indranil Das, Visiting Fellow
 Email      : indranil.das@cern.ch | indra.ehep@gmail.com
**********************************************************************/
#include <TH1.h>
#include <THStack.h>
#include <TF1.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TAxis.h>
#include <TStyle.h>
#include <TMath.h>
#include <TKey.h>
#include <TPaveStats.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TAttMarker.h>
#include <TAttLine.h>

#include <iostream>

using namespace std;

int CutflowHistCount(const char *input, const char *sample)
{
  TFile *fin = TFile::Open(input);
  TH1D *hcutflow_mu = (TH1D *)fin->Get(Form("%s/base/Iso/_cutflow_mu",sample));
  TH1D *hcutflow_ele = (TH1D *)fin->Get(Form("%s/base/Iso/_cutflow_ele",sample));
  
  const char *cutnames[10] = {"Trigger", Form("Nof lep = 1"), "No. of jets #geq 4", "MET #geq 20 GeV", "No. of #it{b} jets #geq 2", "KinFit Sel.", "Excl. #it{c} jet LWP", "Excl. #it{c} jet MWP" ,"Excl. #it{c} jet TWP",""};
  for (int ibin=2;ibin<hcutflow_mu->GetNbinsX();ibin++){
    printf("%30s (mu) : %5.0lf\n",cutnames[ibin-2],hcutflow_mu->GetBinContent(ibin));
  }
  for (int ibin=2;ibin<hcutflow_ele->GetNbinsX();ibin++){
    printf("%30s (ele) : %5.0lf\n",cutnames[ibin-2],hcutflow_ele->GetBinContent(ibin));
  }
  fin->Close();
  delete fin;
  
  return true;
}
