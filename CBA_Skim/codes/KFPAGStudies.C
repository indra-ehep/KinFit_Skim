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

void KFPAGStudies()
{
  string signal = "TTbar";
  int year = 2016;
  
  Double_t  chi2;
  Int_t  ndf;
  
  Float_t   jetBhadPt;
  Float_t   jetBhadEta;
  Float_t   jetBhadPhi;
  Float_t   jetBhadEn;
  
  Float_t   jetChadPt;
  Float_t   jetChadEta;
  Float_t   jetChadPhi;
  Float_t   jetChadEn;
  
  Float_t   jetShadPt;
  Float_t   jetShadEta;
  Float_t   jetShadPhi;
  Float_t   jetShadEn;

  Float_t   jetBlepPt;
  Float_t   jetBlepEta;
  Float_t   jetBlepPhi;
  Float_t   jetBlepEn;

  Float_t   lepPt;
  Float_t   lepEta;
  Float_t   lepPhi;
  Float_t   lepEn;

  Float_t   metPx;
  Float_t   metPy;
  Float_t   metPz;

  Double_t sampleWeight;
  Double_t prefireWeight;
  Double_t PUWeight;
  Double_t muEffWeight;
  Double_t eleEffWeight;
  Double_t puJetIDWeight;
  Double_t bTagWeight;
  Double_t cTagLWeight;
  Double_t cTagMWeight;
  Double_t cTagTWeight;
  Double_t muonpfRelIso,elepfRelIso;
  
  Bool_t singleMu;
  Bool_t singleEle;
  Bool_t muonIsoCut;
  Bool_t eleIsoCut;
  Bool_t isLowMET;
  Bool_t isKFValid;
  Bool_t hasKFMu;
  Bool_t hasKFEle;
  Bool_t isCTagged;
  Int_t count_cJetsIncL;
  Int_t count_cJetsIncM;
  Int_t count_cJetsIncT;

  Double_t weight, mjjKF;
  
  //string inpath_tree = Form("/Data/root_files/KinFit/CBA_elereliso/pre/%d",year);
  string inpath_tree = Form("/run/media/indra/DHEP_Storage_3/Data/NanoAOD/KinFit/CBA_elereliso/");
  string treelist = "/tmp/fl_tree_list.txt";
  string command = Form("find %s -name \"%s_tree_base_*.root\" > %s",inpath_tree.data(),signal.data(),treelist.data());
  system(command.c_str());
  
  cout<<"filepath : " << inpath_tree.data() << endl;
  string flist;
  ifstream fin(treelist);
  TChain *tr	= new TChain("Kinfit_Reco");
  while ( getline(fin,flist)){
    //cout << "Filename : " << flist << endl;
    tr->Add(flist.c_str());
  }
  fin.close();

  tr->SetBranchAddress("chi2"		, &chi2);
  tr->SetBranchAddress("ndf"		, &ndf);

  tr->SetBranchAddress("jetBhadPt"	, &jetBhadPt);
  tr->SetBranchAddress("jetBhadEta"	, &jetBhadEta);
  tr->SetBranchAddress("jetBhadPhi"	, &jetBhadPhi);
  tr->SetBranchAddress("jetBhadEnergy"	, &jetBhadEn);
  
  tr->SetBranchAddress("jetChadPt"	, &jetChadPt);
  tr->SetBranchAddress("jetChadEta"	, &jetChadEta);
  tr->SetBranchAddress("jetChadPhi"	, &jetChadPhi);
  tr->SetBranchAddress("jetChadEnergy"	, &jetChadEn);
  
  tr->SetBranchAddress("jetShadPt"	, &jetShadPt);
  tr->SetBranchAddress("jetShadEta"	, &jetShadEta);
  tr->SetBranchAddress("jetShadPhi"	, &jetShadPhi);
  tr->SetBranchAddress("jetShadEnergy"	, &jetShadEn);

  tr->SetBranchAddress("jetBlepPt"	, &jetBlepPt);
  tr->SetBranchAddress("jetBlepEta"	, &jetBlepEta);
  tr->SetBranchAddress("jetBlepPhi"	, &jetBlepPhi);
  tr->SetBranchAddress("jetBlepEnergy"	, &jetBlepEn);

  tr->SetBranchAddress("lepPt"	, &lepPt);
  tr->SetBranchAddress("lepEta"	, &lepEta);
  tr->SetBranchAddress("lepPhi"	, &lepPhi);
  tr->SetBranchAddress("lepEnergy"	, &lepEn);

  tr->SetBranchAddress("metPx"		, &metPx);
  tr->SetBranchAddress("metPy"		, &metPy);
  tr->SetBranchAddress("metPz"		, &metPz);

  tr->SetBranchAddress("sampleWeight"	, &sampleWeight);
  tr->SetBranchAddress("prefireWeight"	, &prefireWeight);
  tr->SetBranchAddress("PUWeight"	, &PUWeight);
  tr->SetBranchAddress("muEffWeight"	, &muEffWeight);
  tr->SetBranchAddress("eleEffWeight"	, &eleEffWeight);
  tr->SetBranchAddress("puJetIDWeight"	, &puJetIDWeight);
  // tr->SetBranchAddress("bTagWeight"	, &bTagWeight);
  // tr->SetBranchAddress("cTagLWeight"	, &cTagLWeight);
  // tr->SetBranchAddress("cTagMWeight"	, &cTagMWeight);
  // tr->SetBranchAddress("cTagTWeight"	, &cTagTWeight);
  tr->SetBranchAddress("singleMu"	, &singleMu);
  tr->SetBranchAddress("singleEle"	, &singleEle);
  tr->SetBranchAddress("muonIsoCut"	, &muonIsoCut);
  tr->SetBranchAddress("eleIsoCut"	, &eleIsoCut);
  tr->SetBranchAddress("isLowMET"	, &isLowMET);
  tr->SetBranchAddress("isCTagged"	, &isCTagged);
  // tr->SetBranchAddress("isKFValid"	, &isKFValid);
  // tr->SetBranchAddress("hasKFMu"	, &hasKFMu);
  // tr->SetBranchAddress("hasKFEle"	, &hasKFEle);
  tr->SetBranchAddress("muonpfRelIso"	, &muonpfRelIso);
  tr->SetBranchAddress("elepfRelIso"	, &elepfRelIso);


  TLorentzVector chad, shad, bjhad;
  TLorentzVector met, lep, bjlep;
  
  float Min_pt = 25.0;
  float Max_eta = 2.4;
  TH1F *topHM = new TH1F("topHM","#it{t} #rightarrow #it{b}+#it{jj}", 300, 0., 300.);
  TH1F *topLM = new TH1F("topLM","#it{t} #rightarrow #it{b}+#it{l}#nu", 300, 0., 300.);
  TH1F *wLM = new TH1F("wLM","#it{W} #rightarrow #it{l}#nu", 250, 0., 250.);
  TProfile *prefire_Eta_bjet = new TProfile("prefire_Eta_bjet","prefireWt vs eta (bjet)",60,-3,3,0,2);
  TProfile *prefire_Eta_ljet = new TProfile("prefire_Eta_ljet","prefireWt vs eta (ljet)",60,-3,3,0,2);
  TProfile *SFWt_Pt_mu = new TProfile("SFWt_Pt_mu","muSFWt vs pt (muon)",1000,0,500,0,2);
  TProfile *SFWt_Pt_ele = new TProfile("SFWt_Pt_ele","eleSFWt vs pt (electron)",1000,0,500,0,2);
  
  TProfile *Isomu_vs_MET = new TProfile("Isomu_vs_MET",Form("isolation vs MET (muon,%s)",signal.c_str()),50,0,500,-0.15,0.15);
  TProfile *Isoele_vs_MET = new TProfile("Isoele_vs_MET",Form("isolation vs MET (ele,%s)",signal.c_str()),50,0,500,-0.15,0.15);

  TH2F *Isomu_vs_MET_th2 = new TH2F("Isomu_vs_MET_th2","Isomu_vs_MET_th2",50,0,0.3,100,0.,100.);
  TH2F *Isoele_vs_MET_th2 = new TH2F("Isoele_vs_MET_th2","Isoele_vs_MET_th2",50,0,0.3,100,0.,100.);

  TH1F *Isomu_AB = new TH1F("Isomu_AB",Form("Isomu AB vs CD (muon, %s)",signal.c_str()),50,0.0,0.3);
  TH1F *Isomu_CD = new TH1F("Isomu_CD",Form("Isomu AB vs CD (muon, %s)",signal.c_str()),50,0.0,0.3);
  TH1F *Isoele_AB = new TH1F("Isoele_AB",Form("Isoele AB vs CD (ele, %s)",signal.c_str()),50,0.0,0.3);
  TH1F *Isoele_CD = new TH1F("Isoele_CD",Form("Isoele AB vs CD (ele, %s)",signal.c_str()),50,0.0,0.3);
  TH1F *METmu_AD = new TH1F("METmu_AD",Form("MET AD vs BC (muon, %s)",signal.c_str()),50,0.0,500.);
  TH1F *METmu_BC = new TH1F("METmu_BC",Form("MET AD vs BC (muon, %s)",signal.c_str()),50,0.0,500.);
  TH1F *METele_AD = new TH1F("METele_AD",Form("MET AD vs BC (ele, %s)",signal.c_str()),50,0.0,500.);
  TH1F *METele_BC = new TH1F("METele_BC",Form("MET AD vs BC (ele, %s)",signal.c_str()),50,0.0,500.);
  
  bool isControl_mu = false;
  bool isControl_ele = false;
  cout << "Signal : " << signal << ", Total Entries : " << tr->GetEntries() << endl;
  for (Long64_t ievent = 0 ; ievent < tr->GetEntries() ; ievent++ ) {    
  //for (Long64_t ievent = 0 ; ievent < tr->GetEntries()/4 ; ievent++ ) {    
    
    tr->GetEntry(ievent) ;
    if(ievent%1000000==0)
      cout<<"iEvent : " << ievent << ", chi2 : "<<chi2<<endl;
    bjhad.SetPtEtaPhiE(jetBhadPt, jetBhadEta, jetBhadPhi, jetBhadEn);
    chad.SetPtEtaPhiE(jetChadPt, jetChadEta, jetChadPhi, jetChadEn);
    shad.SetPtEtaPhiE(jetShadPt, jetShadEta, jetShadPhi, jetShadEn);
    
    bjlep.SetPtEtaPhiE(jetBlepPt, jetBlepEta, jetBlepPhi, jetBlepEn);
    lep.SetPtEtaPhiE(lepPt, lepEta, lepPhi, lepEn);
    met.SetXYZM(metPx, metPy, metPz, 0.0);
    
    //weight = sampleWeight*prefireWeight*PUWeight*muEffWeight*puJetIDWeight*bTagWeight;
    //weight = sampleWeight*prefireWeight*PUWeight*muEffWeight*puJetIDWeight;
    
    //mjjKF = (chad+shad).M();
    //bool etaCut = abs(jetShadEta) < 2.4 and 
    //bool isPtCut = (jetShadPt > Min_pt and jetChadPt > Min_pt and jetBhadPt > Min_pt and jetBlepPt > Min_pt);
    //bool isEtaCut = (abs(jetShadEta) < Max_eta and abs(jetChadEta) < Max_eta and abs(jetBhadEta) < Max_eta and abs(jetBlepEta) < Max_eta);
    //if(singleMu and !singleEle and muonIsoCut and !isLowMET and isPtCut and isEtaCut){
      
    topHM->Fill( (chad+shad+bjhad).M() );
    topLM->Fill( (lep+met+bjlep).M() );
    wLM->Fill( (lep+met).M() );
    
    prefire_Eta_bjet->Fill( ((bjhad.Pt()>bjlep.Pt())?bjhad.Eta():bjlep.Eta()), prefireWeight);
    prefire_Eta_ljet->Fill( ((chad.Pt()>shad.Pt())?chad.Eta():shad.Eta()), prefireWeight);
    
    if(singleMu and !singleEle)
      SFWt_Pt_mu->Fill( lepPt, muEffWeight);
    else
      SFWt_Pt_ele->Fill( lepPt, eleEffWeight);

    if(muonIsoCut and !isLowMET)
      isControl_mu = false;
    else
      isControl_mu = true;

    if(eleIsoCut and !isLowMET)
      isControl_ele = false;
    else
      isControl_ele = true;
    
    //if(singleMu and !singleEle and isControl_mu){
    if(singleMu and !singleEle){
      Isomu_vs_MET->Fill(met.Et(), muonpfRelIso);
      Isomu_vs_MET_th2->Fill(muonpfRelIso, met.Et());
      if(!isLowMET)
	Isomu_AB->Fill(muonpfRelIso);
      else
	Isomu_CD->Fill(muonpfRelIso);
      if(muonIsoCut)
	METmu_AD->Fill(met.Et());
      else
	METmu_BC->Fill(met.Et());
    }
    if(!singleMu and singleEle){// and isControl_ele){
      Isoele_vs_MET->Fill(met.Et(), elepfRelIso);
      Isoele_vs_MET_th2->Fill(elepfRelIso, met.Et());
      if(!isLowMET)
	Isoele_AB->Fill(elepfRelIso);
      else
	Isoele_CD->Fill(elepfRelIso);
      if(eleIsoCut)
	METele_AD->Fill(met.Et());
      else
	METele_BC->Fill(met.Et());
    }
    //}
  }//event loop
  
  
  // TCanvas *c1_1 = new TCanvas("c1_1","c1_1");
  // topHM->Draw();
  // topHM->GetXaxis()->SetTitle("m_{top} (GeV)");
  // topHM->GetYaxis()->SetTitle("Entries");
    
  // TCanvas *c1_2 = new TCanvas("c1_2","c1_2");
  // topLM->Draw();
  // topLM->GetXaxis()->SetTitle("m_{top} (GeV)");
  // topLM->GetYaxis()->SetTitle("Entries");

  // TCanvas *c1_3 = new TCanvas("c1_3","c1_3");
  // wLM->Draw();
  // wLM->GetXaxis()->SetTitle("m_{W} (GeV)");
  // wLM->GetYaxis()->SetTitle("Entries");


  // TCanvas *c2 = new TCanvas("c2","c2");
  // c2->Divide(2,1);
  // c2->cd(1);
  // prefire_Eta_bjet->Draw();
  // prefire_Eta_bjet->GetXaxis()->SetTitle("#eta^{b-jet}");
  // prefire_Eta_bjet->GetYaxis()->SetTitle("prefire weight");
  // c2->cd(2);
  // prefire_Eta_ljet->Draw();
  // prefire_Eta_ljet->GetXaxis()->SetTitle("#eta^{l-jet}");
  // prefire_Eta_ljet->GetYaxis()->SetTitle("prefire weight");
  
  // TCanvas *c3 = new TCanvas("c3","c3");
  // SFWt_Pt_mu->Draw();
  // SFWt_Pt_mu->GetXaxis()->SetTitle("p^{#mu}_{T} (GeV)");
  // SFWt_Pt_mu->GetYaxis()->SetTitle("muon SF weight");

  // TCanvas *c4 = new TCanvas("c4","c4");
  // SFWt_Pt_ele->Draw();
  // SFWt_Pt_ele->GetXaxis()->SetTitle("p^{e}_{T} (GeV)");
  // SFWt_Pt_ele->GetYaxis()->SetTitle("electron SF weight");

  // Isomu_vs_MET->SetMinimum(0.0);
  // Isomu_vs_MET->SetMaximum(0.04);
  // Isoele_vs_MET->SetMinimum(0.0);
  // Isoele_vs_MET->SetMaximum(0.04);
  // TCanvas *c5_1 = new TCanvas("c5_1","c5_1");
  // Isomu_vs_MET->Draw();
  // Isomu_vs_MET->GetXaxis()->SetTitle("E_{T}^{miss} (GeV)");
  // Isomu_vs_MET->GetYaxis()->SetTitle("I_{rel}^{#mu}");
  
  // TCanvas *c5_2 = new TCanvas("c5_2","c5_2");
  // Isoele_vs_MET->Draw();
  // Isoele_vs_MET->GetXaxis()->SetTitle("E_{T}^{miss} (GeV)");
  // Isoele_vs_MET->GetYaxis()->SetTitle("I_{rel}^{#it{e}}");
  
  // TCanvas *c6 = new TCanvas("c6","c6");
  // c6->Divide(2,1);
  // c6->cd(1);
  // Isomu_vs_MET_th2->Draw();
  // c6->cd(2);
  // Isoele_vs_MET_th2->Draw();

  Isomu_CD->SetLineColor(kRed);
  Isomu_AB->Scale(1./Isomu_AB->Integral());
  Isomu_CD->Scale(1./Isomu_CD->Integral());
  TCanvas *c7 = new TCanvas("c7","c7");
  Isomu_AB->Draw();
  Isomu_CD->Draw("sames");
  Isomu_AB->GetXaxis()->SetTitle("I_{rel}^{#mu}");
  Isomu_AB->GetYaxis()->SetTitle("Arb.");

  Isoele_CD->SetLineColor(kRed);
  Isoele_AB->Scale(1./Isoele_AB->Integral());
  Isoele_CD->Scale(1./Isoele_CD->Integral());
  TCanvas *c8 = new TCanvas("c8","c8");
  Isoele_AB->Draw();
  Isoele_CD->Draw("sames");
  Isoele_AB->GetXaxis()->SetTitle("I_{rel}^{#it{e}}");
  Isoele_AB->GetYaxis()->SetTitle("Arb.");

  METmu_BC->SetLineColor(kRed);
  METmu_AD->Scale(1./METmu_AD->Integral());
  METmu_BC->Scale(1./METmu_BC->Integral());
  TCanvas *c9 = new TCanvas("c9","c9");
  METmu_AD->Draw();
  METmu_BC->Draw("sames");
  METmu_AD->GetXaxis()->SetTitle("E_{T}^{miss} (GeV)");
  METmu_AD->GetYaxis()->SetTitle("Arb.");

  METele_BC->SetLineColor(kRed);
  METele_AD->Scale(1./METele_AD->Integral());
  METele_BC->Scale(1./METele_BC->Integral());
  TCanvas *c10 = new TCanvas("c10","c10");
  METele_AD->Draw();
  METele_BC->Draw("sames");
  METele_AD->GetXaxis()->SetTitle("E_{T}^{miss} (GeV)");
  METele_AD->GetYaxis()->SetTitle("Arb.");

  //delete tr;
}
