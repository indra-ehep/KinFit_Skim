/**********************************************************************
 Created on : 16/07/2022
 Purpose    : Prepare the histograms for analysis
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


int HistoBuilder()
{
  TH1F *mjj = new TH1F("mjj","mjj (Inclussive)", 2400, 0., 240.);
  TH1F *mjj_cut1 = new TH1F("mjj_cut1","mjj (Inclusive reweight)", 2400, 0., 240.);
  TH1F *mjj_cut2 = new TH1F("mjj_cut2","mjj (InclRw+passed ttbar #delta#phi > 2.0)", 2400, 0., 240.);
  TH1F *mjj_cut3 = new TH1F("mjj_cut3","mjj (InclRw+failed ttbar #delta#phi > 2.0)", 2400, 0., 240.);
  TH1F *mjj_cut4 = new TH1F("mjj_cut4","mjj (InclRw+#chi^{2} < 1.)", 2400, 0., 240.);
  TH1F *hDelPhi = new TH1F("hDelPhi","hDelPhi",100,-5.0,5.0);
  
  Double_t  chi2;
  Float_t   jetChadPt;
  Float_t   jetChadEta;
  Float_t   jetChadPhi;
  Float_t   jetChadEn;
  Float_t   jetShadPt;
  Float_t   jetShadEta;
  Float_t   jetShadPhi;
  Float_t   jetShadEn;
  Float_t   metPx;
  Float_t   metPy;
  Float_t   metPz;
  Float_t   lepPt;
  Float_t   lepEta;
  Float_t   lepPhi;
  Float_t   lepEn;
  Float_t   jetBhadPt;
  Float_t   jetBhadEta;
  Float_t   jetBhadPhi;
  Float_t   jetBhadEn;
  Float_t   jetBlepPt;
  Float_t   jetBlepEta;
  Float_t   jetBlepPhi;
  Float_t   jetBlepEn;
  Int_t     nJet;
  
  Double_t sampleWeight;
  Double_t prefireWeight;
  Double_t PUWeight;
  Double_t muEffWeight;
  Double_t bTagWeight;
  Bool_t singleMu;
  Bool_t singleEle;
  Bool_t muonIsoCut;
  Bool_t isLowMET;
  Double_t weight, mjjKF;
  
  string sig = "TTbar";
  string syst = "base";
  string input_path = "/run/media/indra/DHEP_Storage_3/Data/NanoAOD/KinFit/CBA_CTagShapeCalib/pre/2016/";
  string input_file_list = "/tmp/histbuild_fl.txt";
  string input_hist_file = Form("root_files/grid_v40_Syst/CBA_CTagShapeCalib/pre/all_TTbar.root");
  string command  = Form("find %s -name \"%s_tree_%s\*.root\" > %s",input_path.c_str(), sig.c_str(), syst.c_str(), input_file_list.c_str());
  cout << command << endl;
  system(command.c_str());

  TChain *tr = new TChain("Kinfit_Reco");
  ifstream fin(input_file_list.c_str());
  string s;
  string inputname = input_file_list.substr(input_file_list.find_last_of("/")+1,input_file_list.find_last_of(".")-input_file_list.find_last_of("/")-1);
  cout << "input filename name : " << inputname << endl;
  int i = 1;
  while(getline(fin,s)){
    cout << "Adding file with index : " << i << " and filename : " <<  s << endl;
    tr->Add(s.c_str());
    i++;
  }
  fin.close();
  cout << "Total Events : " << tr->GetEntries() << endl;
  
  TFile *finhist      = TFile::Open(input_hist_file.c_str());
  TH1D *hWtBefore = (TH1D *)finhist->Get(Form("%s/%s/Iso/_wt_before",sig.c_str(),syst.c_str()));
  TH1D *hWtAfter =  (TH1D *)finhist->Get(Form("%s/%s/Iso/_wt_afterM",sig.c_str(),syst.c_str()));
  TH1F *hMjjSaved = (TH1F *)finhist->Get(Form("%s/%s/Iso/_kb_mjj_mu",sig.c_str(),syst.c_str()));
  
  // hWtBefore->SetLineColor(kRed);
  // hWtBefore->SetMarkerColor(kRed);
  // new TCanvas();
  // hWtBefore->Draw("hist");
  // hWtAfter->Draw("hist sames");
    
  // cout<<"filename : " << fin->GetName() << endl;
  // TTree *tr	= (TTree*)fin->Get("Kinfit_Reco");

  // TH1F *hMjjSaved = (TH1F *)finhist->Get("HplusM160/base/Iso/_kb_mjj_mu");
  // TH1F *hChi2Min1 = (TH1F *)finhist->Get("HplusM160/base/Iso/hMinChi2_mu");
  // TH1F *hChi2Min2 = (TH1F *)finhist->Get("HplusM160/base/Iso/h2MinChi2_mu");
  // TH1F *hChi2Min3 = (TH1F *)finhist->Get("HplusM160/base/Iso/h3MinChi2_mu");
  // TH1F *hChi2Min4 = (TH1F *)finhist->Get("HplusM160/base/Iso/h4MinChi2_mu");
  // TH1F *hChi2Min5 = (TH1F *)finhist->Get("HplusM160/base/Iso/h5MinChi2_mu");
  
  tr->SetBranchAddress("chi2"		, &chi2);
  tr->SetBranchAddress("jetChadPt"	, &jetChadPt);
  tr->SetBranchAddress("jetChadEta"	, &jetChadEta);
  tr->SetBranchAddress("jetChadPhi"	, &jetChadPhi);
  tr->SetBranchAddress("jetChadEnergy"	, &jetChadEn);
  tr->SetBranchAddress("jetShadPt"	, &jetShadPt);
  tr->SetBranchAddress("jetShadEta"	, &jetShadEta);
  tr->SetBranchAddress("jetShadPhi"	, &jetShadPhi);
  tr->SetBranchAddress("jetShadEnergy"	, &jetShadEn);
  tr->SetBranchAddress("metPx"		, &metPx);
  tr->SetBranchAddress("metPy"		, &metPy);
  tr->SetBranchAddress("metPz"		, &metPz);
  tr->SetBranchAddress("lepPt"	, &lepPt);
  tr->SetBranchAddress("lepEta"	, &lepEta);
  tr->SetBranchAddress("lepPhi"	, &lepPhi);
  tr->SetBranchAddress("lepEnergy"	, &lepEn);
  tr->SetBranchAddress("jetBhadPt"	, &jetBhadPt);
  tr->SetBranchAddress("jetBhadEta"	, &jetBhadEta);
  tr->SetBranchAddress("jetBhadPhi"	, &jetBhadPhi);
  tr->SetBranchAddress("jetBhadEnergy"	, &jetBhadEn);
  tr->SetBranchAddress("jetBlepPt"	, &jetBlepPt);
  tr->SetBranchAddress("jetBlepEta"	, &jetBlepEta);
  tr->SetBranchAddress("jetBlepPhi"	, &jetBlepPhi);
  tr->SetBranchAddress("jetBlepEnergy"	, &jetBlepEn);

  tr->SetBranchAddress("nJet"		, &nJet);

  tr->SetBranchAddress("sampleWeight"	, &sampleWeight);
  tr->SetBranchAddress("prefireWeight"	, &prefireWeight);
  tr->SetBranchAddress("PUWeight"	, &PUWeight);
  tr->SetBranchAddress("muEffWeight"	, &muEffWeight);
  tr->SetBranchAddress("bcTagMWeight"	, &bTagWeight);
  tr->SetBranchAddress("singleMu"	, &singleMu);
  tr->SetBranchAddress("singleEle"	, &singleEle);
  tr->SetBranchAddress("muonIsoCut"	, &muonIsoCut);
  tr->SetBranchAddress("isLowMET"	, &isLowMET);
  
  TLorentzVector chad, shad, met, bhad, lep, blep, top, tbar;
  float wt_before, wt_after, wt_ratio;
  cout << "Total Entries : " << tr->GetEntries() << endl;
  for (Long64_t ievent = 0 ; ievent < tr->GetEntries() ; ievent++ ) {    
  //for (Long64_t ievent = 0 ; ievent < 20000 ; ievent++ ) {    
  //for (Long64_t ievent = 0 ; ievent < 5 ; ievent++ ) {
    
    tr->GetEntry(ievent) ;
    if(ievent%1000000==0)
      cout<<"iEvent : " << ievent << ", chi2 : "<<chi2<<endl;
    chad.SetPtEtaPhiE(jetChadPt, jetChadEta, jetChadPhi, jetChadEn);
    shad.SetPtEtaPhiE(jetShadPt, jetShadEta, jetShadPhi, jetShadEn);
    met.SetXYZM(metPx, metPy, metPz, 0.0);
    bhad.SetPtEtaPhiE(jetBhadPt, jetBhadEta, jetBhadPhi, jetBhadEn);
    blep.SetPtEtaPhiE(jetBlepPt, jetBlepEta, jetBlepPhi, jetBlepEn);
    lep.SetPtEtaPhiE(lepPt, lepEta, lepPhi, lepEn);

    top = bhad + chad + shad;
    tbar = blep + lep + met;
    
    wt_before = hWtBefore->GetBinContent(nJet+1);
    wt_after = hWtAfter->GetBinContent(nJet+1);
    wt_ratio = wt_before/wt_after;
    //cout <<"nJet : "<< nJet << ", wt_before : "<<wt_before <<", wt_after : " << wt_after << ", wt_ratio : " << wt_ratio << endl;
    
    weight = sampleWeight*prefireWeight*PUWeight*muEffWeight*bTagWeight;
    mjjKF = (chad+shad).M();
    if(singleMu and !singleEle and muonIsoCut and !isLowMET){
    //if(singleMu and !singleEle and muonIsoCut and met.Pt()>20.0){
      mjj->Fill(mjjKF,weight);
      mjj_cut1->Fill(mjjKF,weight*wt_ratio);
      
      if(TMath::Abs(top.DeltaPhi(tbar))>2.5)
	mjj_cut2->Fill(mjjKF,weight*wt_ratio);
      //else
	
      if(chi2<3.) { //chi^2<2 ~= DelPhi>2.7 // chi^2<10 ~= DelPhi>1.5 // chi^2<5 ~= DelPhi>2.2
	mjj_cut4->Fill(mjjKF,weight*wt_ratio);
	hDelPhi->Fill(TMath::Abs(top.DeltaPhi(tbar)));
      }else
	mjj_cut3->Fill(mjjKF,weight*wt_ratio);
    }
  }//event loop
  
  hMjjSaved->SetLineColor(kBlue);
  mjj->SetLineColor(kRed);
  mjj->SetLineWidth(2);
  mjj_cut1->SetLineColor(kBlue);
  mjj_cut1->SetLineWidth(2);
  mjj_cut2->SetLineColor(kGreen);
  mjj_cut2->SetLineWidth(2);
  mjj_cut3->SetLineColor(kMagenta);
  mjj_cut3->SetLineWidth(2);
  mjj_cut4->SetLineColor(kBlack);
  mjj_cut4->SetLineWidth(2);
  
  gStyle->SetOptStat(1112111);
  // gStyle->SetOptFit(11);
  
  // TF1 *fn = new TF1("fn","gaus",60.,100.);
  TCanvas *c1 = new TCanvas("c1","c1");
  mjj->Draw("hist");
  mjj_cut1->Draw("hist sames");
  mjj_cut2->Draw("hist sames");
  mjj_cut3->Draw("hist sames");
  mjj_cut4->Draw("hist sames");
  
  TCanvas *c2 = new TCanvas("c2","c2");
  hMjjSaved->Draw("hist sames");

  TCanvas *c3 = new TCanvas("c3","c3");
  hDelPhi->Draw("hist sames");
  
  TFile *fout = new TFile(Form("root_files/test/output.root"),"recreate");
  mjj->Write();
  mjj_cut1->Write();
  mjj_cut2->Write();
  mjj_cut3->Write();
  mjj_cut4->Write();
  hMjjSaved->Write();
  // c1->Write();
  // c2->Write();
  // c3->Write();
  fout->Close();
  delete fout;


  return true;
}
