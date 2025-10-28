/**********************************************************************
 Created on : 26/07/2025
 Purpose    : Correlation of the charm jets with parton
 Author     : Indranil Das, Research Associate, Imperial
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

int PartonCorrelation(const char* infile)
{
  TFile *fin_tree = 0x0;
  fin_tree = TFile::Open(infile);
    
  if(!fin_tree){
    printf("Failed to open file %s\n",infile);
    return false;
  }
  
  double nofKF = 0, nofExcT = 0, nofExcM = 0, nofExcL = 0, nofExc0 = 0;
  ////==============================================================================
  Float_t   metPx;
  Float_t   metPy;
  Float_t   metPz;
  Float_t   jetChadPt;
  Float_t   jetChadEta;
  Float_t   jetChadPhi;
  Float_t   jetChadEn;
  Float_t   jetShadPt;
  Float_t   jetShadEta;
  Float_t   jetShadPhi;
  Float_t   jetShadEn;
  
  Bool_t singleMu;
  Bool_t singleEle;
  Bool_t muonIsoCut;
  Bool_t isLowMET;
  
  int cjhad_ctag, sjhad_ctag;
  int bjhad_pflav, bjlep_pflav, cjhad_pflav, sjhad_pflav;
  
  TTree *tr	= (TTree*)fin_tree->Get("Kinfit_Reco");
  tr->SetBranchAddress("metPx"		, &metPx);
  tr->SetBranchAddress("metPy"		, &metPy);
  tr->SetBranchAddress("metPz"		, &metPz);
  tr->SetBranchAddress("singleMu"	, &singleMu);
  tr->SetBranchAddress("singleEle"	, &singleEle);
  tr->SetBranchAddress("muonIsoCut"	, &muonIsoCut);
  tr->SetBranchAddress("isLowMET"	, &isLowMET);
  tr->SetBranchAddress("cjhad_ctag"	, &cjhad_ctag);
  tr->SetBranchAddress("sjhad_ctag"	, &sjhad_ctag);
  tr->SetBranchAddress("bjhad_pflav"	, &bjhad_pflav);
  tr->SetBranchAddress("bjlep_pflav"	, &bjlep_pflav);
  tr->SetBranchAddress("cjhad_pflav"	, &cjhad_pflav);
  tr->SetBranchAddress("sjhad_pflav"	, &sjhad_pflav);
  
  tr->SetBranchAddress("jetChadPt"	, &jetChadPt);
  tr->SetBranchAddress("jetChadEta"	, &jetChadEta);
  tr->SetBranchAddress("jetChadPhi"	, &jetChadPhi);
  tr->SetBranchAddress("jetChadEnergy"	, &jetChadEn);
  tr->SetBranchAddress("jetShadPt"	, &jetShadPt);
  tr->SetBranchAddress("jetShadEta"	, &jetShadEta);
  tr->SetBranchAddress("jetShadPhi"	, &jetShadPhi);
  tr->SetBranchAddress("jetShadEnergy"	, &jetShadEn);

  TLorentzVector met;
  TLorentzVector chad, shad;
  TH2I *hCombCorr = new TH2I("hCombCorr","Parton correlation (Combined)",12,-5.5,6.5,12,-5.5,6.5); 
  TH2I *hExcLCorr = new TH2I("hExcLCorr","Parton correlation (Exclusive loose)",12,-5.5,6.5,12,-5.5,6.5);
  TH2I *hExcMCorr = new TH2I("hExcMCorr","Parton correlation (Exclusive medium)",12,-5.5,6.5,12,-5.5,6.5);
  TH2I *hExcTCorr = new TH2I("hExcTCorr","Parton correlation (Exclusive tight)",12,-5.5,6.5,12,-5.5,6.5);
  TH2I *hExc0Corr = new TH2I("hExc0Corr","Parton correlation (non-exclusive)",12,-5.5,6.5,12,-5.5,6.5);

  TH1F *hmjj_incl = new TH1F("hmjj_incl","mjj (Inclusive)", 250, 0., 250.);
  TH1F *hmjj_ct_loose = new TH1F("hmjj_ct_loose","mjj (Excl loose)", 250, 0., 250.);
  TH1F *hmjj_ct_medium = new TH1F("hmjj_ct_medium","mjj (Excl medium)", 250, 0., 250.);
  TH1F *hmjj_ct_tight = new TH1F("hmjj_ct_tight","mjj (Excl tight)", 250, 0., 250.);

  cout << "Total Entries : " << tr->GetEntries() << endl;
  for (Long64_t ievent = 0 ; ievent < tr->GetEntries() ; ievent++ ) {        
    tr->GetEntry(ievent) ;
    // if(ievent%1000000==0)
    //   cout<<"iEvent : " << ievent << ", chi2 : "<<chi2<<endl;
    met.SetXYZM(metPx, metPy, metPz, 0.0);
    if(cjhad_pflav==21) cjhad_pflav = 6;
    if(sjhad_pflav==21) sjhad_pflav = 6;
    //if(singleMu and !singleEle and muonIsoCut and !isLowMET){
    if(singleMu and !singleEle and muonIsoCut and met.Pt()>20.0){
      chad.SetPtEtaPhiE(jetChadPt, jetChadEta, jetChadPhi, jetChadEn);
      shad.SetPtEtaPhiE(jetShadPt, jetShadEta, jetShadPhi, jetShadEn);
      nofKF++;
      if(cjhad_ctag==3 or sjhad_ctag==3){
	hExcTCorr->Fill(cjhad_pflav,sjhad_pflav);
	hCombCorr->Fill(cjhad_pflav,sjhad_pflav);
	hmjj_ct_tight->Fill((chad+shad).M());
	hmjj_incl->Fill((chad+shad).M());
	nofExcT++;
      }else if(cjhad_ctag==2 or sjhad_ctag==2){
	hExcMCorr->Fill(cjhad_pflav,sjhad_pflav);
	hCombCorr->Fill(cjhad_pflav,sjhad_pflav);
	hmjj_ct_medium->Fill((chad+shad).M());
	hmjj_incl->Fill((chad+shad).M());
	nofExcM++;
      }else if(cjhad_ctag==1 or sjhad_ctag==1){
	hExcLCorr->Fill(cjhad_pflav,sjhad_pflav);
	hCombCorr->Fill(cjhad_pflav,sjhad_pflav);
	hmjj_ct_loose->Fill((chad+shad).M());
	hmjj_incl->Fill((chad+shad).M());
	nofExcL++;
      }else{
	hExc0Corr->Fill(cjhad_pflav,sjhad_pflav);
	nofExc0++;
      }      
    }
  }//event loop
  ////==============================================================================
  double totExcl = nofExcT + nofExcM + nofExcL + nofExc0 ;
  cout << "NofKF : " << nofKF << ", nofExcL: " << nofExcL << ", nofExcM: " << nofExcM
       << ", nofExcT: " << nofExcT << ", nofExc0: " << nofExc0 << ", totExcl: " << totExcl << endl;
  
  void HistLabel(TH2I *hist);
  HistLabel(hCombCorr);
  HistLabel(hExcTCorr);
  HistLabel(hExcMCorr);
  HistLabel(hExcLCorr);
  HistLabel(hExc0Corr);
  
  //gStyle->SetOptStat(0);
  TCanvas *c1 = new TCanvas("c1","c1",800,800);
  c1->SetTickx();
  c1->SetTicky();
  hCombCorr->Draw("box text");

  TCanvas *c2 = new TCanvas("c2","c2",1800,600);
  c2->Divide(3,1);
  c2->cd(1)->SetTickx();
  c2->cd(1)->SetTicky();
  hExcLCorr->Draw("box text");
  c2->cd(2)->SetTickx();
  c2->cd(2)->SetTicky();
  hExcMCorr->Draw("box text");
  c2->cd(3)->SetTickx();
  c2->cd(3)->SetTicky();
  hExcTCorr->Draw("box text");

  TCanvas *c3 = new TCanvas("c3","c3",800,800);
  c3->SetTickx();
  c3->SetTicky();
  hExc0Corr->Draw("box text");

  TCanvas *c4 = new TCanvas("c4","c4",800,800);
  hmjj_ct_tight->Draw();

  TFile *fout = new TFile("output_hplusM120.root","recreate");
  hmjj_incl->Write();
  hmjj_ct_loose->Write();
  hmjj_ct_medium->Write();
  hmjj_ct_tight->Write();
  fout->Close();
  delete fout;
  
  return true;
}

void HistLabel(TH2I *hist)
{
  string label[12] = {"#bar{b}", "#bar{c}", "#bar{s}", "#bar{u}", "#bar{d}", "", "d", "u", "s", "c", "b", "g"};
  //hist->SetTitle("");
  for(int ibin=1;ibin<=hist->GetNbinsX();ibin++){
    hist->GetXaxis()->SetBinLabel(ibin,label[ibin-1].c_str());
    hist->GetYaxis()->SetBinLabel(ibin,label[ibin-1].c_str());
  }
  hist->GetXaxis()->SetTitle("Leading jet flavour");
  hist->GetYaxis()->SetTitle("Subleading jet flavour");
}
