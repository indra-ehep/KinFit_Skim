/**********************************************************************
 Created on : 23/09/2024
 Purpose    : Further QCD DD studies following the suggestion from RBI
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

int KFQCDRBI(string signal = "DataMu", int year = 2018, string inpath_tree = "/eos/cms/store/group/phys_b2g/idas/Output/cms-hcs-run2/Result/CBA_metxycorr/2018")
{
  //;
  //;
  
  Double_t  chi2;
  Int_t  ndf;

  Int_t     nJet;
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
  Double_t bcTagWeight;
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
  
  //string inpath_tree = Form("/eos/cms/store/group/phys_b2g/idas/Output/cms-hcs-run2/Result/CBA_metxycorr/%d",year);
  string treelist = "/tmp/idas/fl_tree_list.txt";
  string command = Form("find %s -name \"%s_tree_base_*.root\" > %s",inpath_tree.data(),signal.data(),treelist.data());
  int ret = system(command.c_str());
  
  cout<<"filepath : " << inpath_tree.data() << endl;
  string flist;
  ifstream fin(treelist);
  TChain *tr	= new TChain("Kinfit_Reco");
  while ( getline(fin,flist)){
    //cout << "Filename : " << flist << endl;
    tr->Add(flist.c_str());
  }
  fin.close();

  tr->SetCacheSize(100*1024*1024);
  tr->SetBranchStatus("*",0);

  tr->SetBranchStatus("chi2",1);
  tr->SetBranchStatus("ndf",1);  
  tr->SetBranchAddress("chi2"		, &chi2);
  tr->SetBranchAddress("ndf"		, &ndf);

  tr->SetBranchStatus("jetBhadPt",1);
  tr->SetBranchStatus("jetBhadEta",1);
  tr->SetBranchStatus("jetBhadPhi",1);
  tr->SetBranchStatus("jetBhadEnergy",1);  
  tr->SetBranchAddress("jetBhadPt"	, &jetBhadPt);
  tr->SetBranchAddress("jetBhadEta"	, &jetBhadEta);
  tr->SetBranchAddress("jetBhadPhi"	, &jetBhadPhi);
  tr->SetBranchAddress("jetBhadEnergy"	, &jetBhadEn);

  tr->SetBranchStatus("jetChadPt",1);
  tr->SetBranchStatus("jetChadEta",1);
  tr->SetBranchStatus("jetChadPhi",1);
  tr->SetBranchStatus("jetChadEnergy",1);  
  tr->SetBranchAddress("jetChadPt"	, &jetChadPt);
  tr->SetBranchAddress("jetChadEta"	, &jetChadEta);
  tr->SetBranchAddress("jetChadPhi"	, &jetChadPhi);
  tr->SetBranchAddress("jetChadEnergy"	, &jetChadEn);
  
  tr->SetBranchStatus("jetShadPt",1);
  tr->SetBranchStatus("jetShadEta",1);
  tr->SetBranchStatus("jetShadPhi",1);
  tr->SetBranchStatus("jetShadEnergy",1);  
  tr->SetBranchAddress("jetShadPt"	, &jetShadPt);
  tr->SetBranchAddress("jetShadEta"	, &jetShadEta);
  tr->SetBranchAddress("jetShadPhi"	, &jetShadPhi);
  tr->SetBranchAddress("jetShadEnergy"	, &jetShadEn);

  tr->SetBranchStatus("jetBlepPt",1);
  tr->SetBranchStatus("jetBlepEta",1);
  tr->SetBranchStatus("jetBlepPhi",1);
  tr->SetBranchStatus("jetBlepEnergy",1);  
  tr->SetBranchAddress("jetBlepPt"	, &jetBlepPt);
  tr->SetBranchAddress("jetBlepEta"	, &jetBlepEta);
  tr->SetBranchAddress("jetBlepPhi"	, &jetBlepPhi);
  tr->SetBranchAddress("jetBlepEnergy"	, &jetBlepEn);

  tr->SetBranchStatus("lepPt",1);
  tr->SetBranchStatus("lepEta",1);
  tr->SetBranchStatus("lepPhi",1);
  tr->SetBranchStatus("lepEnergy",1);  
  tr->SetBranchAddress("lepPt"	, &lepPt);
  tr->SetBranchAddress("lepEta"	, &lepEta);
  tr->SetBranchAddress("lepPhi"	, &lepPhi);
  tr->SetBranchAddress("lepEnergy"	, &lepEn);

  tr->SetBranchStatus("metPx",1);
  tr->SetBranchStatus("metPy",1);
  tr->SetBranchStatus("metPz",1);  
  tr->SetBranchAddress("metPx"		, &metPx);
  tr->SetBranchAddress("metPy"		, &metPy);
  tr->SetBranchAddress("metPz"		, &metPz);

  tr->SetBranchStatus("sampleWeight"	, 1);
  tr->SetBranchStatus("prefireWeight"	, 1);
  tr->SetBranchStatus("PUWeight"	, 1);
  tr->SetBranchStatus("muEffWeight"	, 1);
  tr->SetBranchStatus("eleEffWeight"	, 1);
  tr->SetBranchStatus("puJetIDWeight"	, 1);
  tr->SetBranchStatus("bcTagWeight"	, 1);
  tr->SetBranchAddress("sampleWeight"	, &sampleWeight);
  tr->SetBranchAddress("prefireWeight"	, &prefireWeight);
  tr->SetBranchAddress("PUWeight"	, &PUWeight);
  tr->SetBranchAddress("muEffWeight"	, &muEffWeight);
  tr->SetBranchAddress("eleEffWeight"	, &eleEffWeight);
  tr->SetBranchAddress("puJetIDWeight"	, &puJetIDWeight);
  tr->SetBranchAddress("bcTagWeight"	, &bcTagWeight);

  tr->SetBranchStatus("singleMu"	, 1);
  tr->SetBranchStatus("singleEle"	, 1);
  tr->SetBranchStatus("muonIsoCut"	, 1);
  tr->SetBranchStatus("eleIsoCut"	, 1);
  tr->SetBranchStatus("isLowMET"	, 1);
  tr->SetBranchStatus("muonpfRelIso"	, 1);
  tr->SetBranchStatus("elepfRelIso"	, 1);
  tr->SetBranchAddress("singleMu"	, &singleMu);
  tr->SetBranchAddress("singleEle"	, &singleEle);
  tr->SetBranchAddress("muonIsoCut"	, &muonIsoCut);
  tr->SetBranchAddress("eleIsoCut"	, &eleIsoCut);
  tr->SetBranchAddress("isLowMET"	, &isLowMET);
  // tr->SetBranchAddress("isCTagged"	, &isCTagged);
  // tr->SetBranchAddress("isKFValid"	, &isKFValid);
  // tr->SetBranchAddress("hasKFMu"	, &hasKFMu);
  // tr->SetBranchAddress("hasKFEle"	, &hasKFEle);
  tr->SetBranchAddress("muonpfRelIso"	, &muonpfRelIso);
  tr->SetBranchAddress("elepfRelIso"	, &elepfRelIso);
  
  tr->SetBranchStatus("nJet",1);
  tr->SetBranchAddress("nJet", &nJet);

  tr->SetBranchStatus("count_cJetsIncL",1);
  tr->SetBranchAddress("count_cJetsIncL", &count_cJetsIncL);
  tr->SetBranchStatus("count_cJetsIncM",1);
  tr->SetBranchAddress("count_cJetsIncM", &count_cJetsIncM);
  tr->SetBranchStatus("count_cJetsIncT",1);
  tr->SetBranchAddress("count_cJetsIncT", &count_cJetsIncT);

  cout << "NofEvents : " << tr->GetEntries() << endl;

  TLorentzVector chad, shad, bjhad;
  TLorentzVector met, lep, bjlep;
  double weight_ele, weight_mu;
  double mjjKF;

  string inpath_hist = Form("root_files/grid_v40_Syst/CBA_metxycorr/%d",year);

  TFile *fRefF = TFile::Open(Form("%s/all_%s.root",inpath_hist.data(),signal.data()));
  TH1D *hWtB_mu_iso = (TH1D *)fRefF->Get(Form("%s/base/Iso/_wt_before_mu",signal.data()));
  TH1D *hWtA_mu_iso = (TH1D *)fRefF->Get(Form("%s/base/Iso/_wt_after_mu",signal.data()));
  TH1D *hWtB_mu_lmet = (TH1D *)fRefF->Get(Form("%s/base/LowMET/_wt_before_mu_lmet",signal.data()));
  TH1D *hWtA_mu_lmet = (TH1D *)fRefF->Get(Form("%s/base/LowMET/_wt_after_mu_lmet",signal.data()));
  TH1D *hWtB_mu_noniso = (TH1D *)fRefF->Get(Form("%s/base/NonIso/_wt_before_mu_noniso",signal.data()));
  TH1D *hWtA_mu_noniso = (TH1D *)fRefF->Get(Form("%s/base/NonIso/_wt_after_mu_noniso",signal.data()));
  TH1D *hWtB_mu_noniso_lmet = (TH1D *)fRefF->Get(Form("%s/base/NonIsoLowMET/_wt_before_mu_noniso_lmet",signal.data()));
  TH1D *hWtA_mu_noniso_lmet = (TH1D *)fRefF->Get(Form("%s/base/NonIsoLowMET/_wt_after_mu_noniso_lmet",signal.data()));
  
  double wt_before_mu_iso, wt_before_mu_lmet, wt_before_mu_noniso, wt_before_mu_noniso_lmet;
  double wt_after_mu_iso, wt_after_mu_lmet, wt_after_mu_noniso, wt_after_mu_noniso_lmet;
  double wt_ratio_mu_iso, wt_ratio_mu_lmet, wt_ratio_mu_noniso, wt_ratio_mu_noniso_lmet;
  double wt_ratio_mu = 1.0;

  TH1D *hWtB_ele_iso = (TH1D *)fRefF->Get(Form("%s/base/Iso/_wt_before_ele",signal.data()));
  TH1D *hWtA_ele_iso = (TH1D *)fRefF->Get(Form("%s/base/Iso/_wt_after_ele",signal.data()));
  TH1D *hWtB_ele_lmet = (TH1D *)fRefF->Get(Form("%s/base/LowMET/_wt_before_ele_lmet",signal.data()));
  TH1D *hWtA_ele_lmet = (TH1D *)fRefF->Get(Form("%s/base/LowMET/_wt_after_ele_lmet",signal.data()));
  TH1D *hWtB_ele_noniso = (TH1D *)fRefF->Get(Form("%s/base/NonIso/_wt_before_ele_noniso",signal.data()));
  TH1D *hWtA_ele_noniso = (TH1D *)fRefF->Get(Form("%s/base/NonIso/_wt_after_ele_noniso",signal.data()));
  TH1D *hWtB_ele_noniso_lmet = (TH1D *)fRefF->Get(Form("%s/base/NonIsoLowMET/_wt_before_ele_noniso_lmet",signal.data()));
  TH1D *hWtA_ele_noniso_lmet = (TH1D *)fRefF->Get(Form("%s/base/NonIsoLowMET/_wt_after_ele_noniso_lmet",signal.data()));

  double wt_before_ele_iso, wt_before_ele_lmet, wt_before_ele_noniso, wt_before_ele_noniso_lmet;
  double wt_after_ele_iso, wt_after_ele_lmet, wt_after_ele_noniso, wt_after_ele_noniso_lmet;
  double wt_ratio_ele_iso, wt_ratio_ele_lmet, wt_ratio_ele_noniso, wt_ratio_ele_noniso_lmet;
  double wt_ratio_ele = 1.0;


  TH1F *Isomu_AB = new TH1F("Isomu_AB",Form("Isomu AB vs CD (muon, %s)",signal.c_str()),50,0.0,0.3);
  TH1F *Isomu_CD = new TH1F("Isomu_CD",Form("Isomu AB vs CD (muon, %s)",signal.c_str()),50,0.0,0.3);
  TH1F *Isoele_AB = new TH1F("Isoele_AB",Form("Isoele AB vs CD (ele, %s)",signal.c_str()),50,0.0,0.3);
  TH1F *Isoele_CD = new TH1F("Isoele_CD",Form("Isoele AB vs CD (ele, %s)",signal.c_str()),50,0.0,0.3);

  TH1F *METmu_AD = new TH1F("METmu_AD",Form("MET AD vs BC (muon, %s)",signal.c_str()),50,0.0,500.);
  TH1F *METmu_BC = new TH1F("METmu_BC",Form("MET AD vs BC (muon, %s)",signal.c_str()),50,0.0,500.);
  TH1F *METele_AD = new TH1F("METele_AD",Form("MET AD vs BC (ele, %s)",signal.c_str()),50,0.0,500.);
  TH1F *METele_BC = new TH1F("METele_BC",Form("MET AD vs BC (ele, %s)",signal.c_str()),50,0.0,500.);

  TH1F *mjj_mu_RegA = new TH1F("mjj_mu_RegA","Muon mjj", 250, 0., 250.);
  TH1F *mjj_mu_RegA_met_down = new TH1F("mjj_mu_RegA_met_down","Muon mjj MET down", 250, 0., 250.);
  TH1F *mjj_mu_RegA_met_up = new TH1F("mjj_mu_RegA_met_up","Muon mjj MET up", 250, 0., 250.);
  TH1F *mjj_mu_RegA_iso_down = new TH1F("mjj_mu_RegA_iso_down","Muon mjj ISO down", 250, 0., 250.);
  TH1F *mjj_mu_RegA_iso_up = new TH1F("mjj_mu_RegA_iso_up","Muon mjj ISO up", 250, 0., 250.);

  TH1F *mjj_mu_RegB = new TH1F("mjj_mu_RegB","Muon mjj", 250, 0., 250.);
  TH1F *mjj_mu_RegB_met_down = new TH1F("mjj_mu_RegB_met_down","Muon mjj MET down", 250, 0., 250.);
  TH1F *mjj_mu_RegB_met_up = new TH1F("mjj_mu_RegB_met_up","Muon mjj MET up", 250, 0., 250.);
  TH1F *mjj_mu_RegB_iso_down = new TH1F("mjj_mu_RegB_iso_down","Muon mjj ISO down", 250, 0., 250.);
  TH1F *mjj_mu_RegB_iso_up = new TH1F("mjj_mu_RegB_iso_up","Muon mjj ISO up", 250, 0., 250.);

  TH1F *mjj_mu_RegC = new TH1F("mjj_mu_RegC","Muon mjj", 250, 0., 250.);
  TH1F *mjj_mu_RegC_met_down = new TH1F("mjj_mu_RegC_met_down","Muon mjj MET down", 250, 0., 250.);
  TH1F *mjj_mu_RegC_met_up = new TH1F("mjj_mu_RegC_met_up","Muon mjj MET up", 250, 0., 250.);
  TH1F *mjj_mu_RegC_iso_down = new TH1F("mjj_mu_RegC_iso_down","Muon mjj ISO down", 250, 0., 250.);
  TH1F *mjj_mu_RegC_iso_up = new TH1F("mjj_mu_RegC_iso_up","Muon mjj ISO up", 250, 0., 250.);
  
  TH1F *mjj_mu_RegD = new TH1F("mjj_mu_RegD","Muon mjj", 250, 0., 250.);
  TH1F *mjj_mu_RegD_met_down = new TH1F("mjj_mu_RegD_met_down","Muon mjj MET down", 250, 0., 250.);
  TH1F *mjj_mu_RegD_met_up = new TH1F("mjj_mu_RegD_met_up","Muon mjj MET up", 250, 0., 250.);
  TH1F *mjj_mu_RegD_iso_down = new TH1F("mjj_mu_RegD_iso_down","Muon mjj ISO down", 250, 0., 250.);
  TH1F *mjj_mu_RegD_iso_up = new TH1F("mjj_mu_RegD_iso_up","Muon mjj ISO up", 250, 0., 250.);

  TH1F *mjj_ele_RegA = new TH1F("mjj_ele_RegA","Electron mjj", 250, 0., 250.);
  TH1F *mjj_ele_RegA_met_down = new TH1F("mjj_ele_RegA_met_down","Electron mjj MET down", 250, 0., 250.);
  TH1F *mjj_ele_RegA_met_up = new TH1F("mjj_ele_RegA_met_up","Electron mjj MET up", 250, 0., 250.);
  TH1F *mjj_ele_RegA_iso_down = new TH1F("mjj_ele_RegA_iso_down","Electron mjj ISO down", 250, 0., 250.);
  TH1F *mjj_ele_RegA_iso_up = new TH1F("mjj_ele_RegA_iso_up","Electron mjj ISO up", 250, 0., 250.);

  TH1F *mjj_ele_RegB = new TH1F("mjj_ele_RegB","Electron mjj", 250, 0., 250.);
  TH1F *mjj_ele_RegB_met_down = new TH1F("mjj_ele_RegB_met_down","Electron mjj MET down", 250, 0., 250.);
  TH1F *mjj_ele_RegB_met_up = new TH1F("mjj_ele_RegB_met_up","Electron mjj MET up", 250, 0., 250.);
  TH1F *mjj_ele_RegB_iso_down = new TH1F("mjj_ele_RegB_iso_down","Electron mjj ISO down", 250, 0., 250.);
  TH1F *mjj_ele_RegB_iso_up = new TH1F("mjj_ele_RegB_iso_up","Electron mjj ISO up", 250, 0., 250.);

  TH1F *mjj_ele_RegC = new TH1F("mjj_ele_RegC","Electron mjj", 250, 0., 250.);
  TH1F *mjj_ele_RegC_met_down = new TH1F("mjj_ele_RegC_met_down","Electron mjj MET down", 250, 0., 250.);
  TH1F *mjj_ele_RegC_met_up = new TH1F("mjj_ele_RegC_met_up","Electron mjj MET up", 250, 0., 250.);
  TH1F *mjj_ele_RegC_iso_down = new TH1F("mjj_ele_RegC_iso_down","Electron mjj ISO down", 250, 0., 250.);
  TH1F *mjj_ele_RegC_iso_up = new TH1F("mjj_ele_RegC_iso_up","Electron mjj ISO up", 250, 0., 250.);
  
  TH1F *mjj_ele_RegD = new TH1F("mjj_ele_RegD","Electron mjj", 250, 0., 250.);
  TH1F *mjj_ele_RegD_met_down = new TH1F("mjj_ele_RegD_met_down","Electron mjj MET down", 250, 0., 250.);
  TH1F *mjj_ele_RegD_met_up = new TH1F("mjj_ele_RegD_met_up","Electron mjj MET up", 250, 0., 250.);
  TH1F *mjj_ele_RegD_iso_down = new TH1F("mjj_ele_RegD_iso_down","Electron mjj ISO down", 250, 0., 250.);
  TH1F *mjj_ele_RegD_iso_up = new TH1F("mjj_ele_RegD_iso_up","Electron mjj ISO up", 250, 0., 250.);

  ////////////////////////////////////////ExcL///////////////////////////////////////////////
  TH1F *mjj_excL_mu_RegA = new TH1F("mjj_excL_mu_RegA","Muon mjj", 250, 0., 250.);
  TH1F *mjj_excL_mu_RegA_met_down = new TH1F("mjj_excL_mu_RegA_met_down","Muon mjj MET down", 250, 0., 250.);
  TH1F *mjj_excL_mu_RegA_met_up = new TH1F("mjj_excL_mu_RegA_met_up","Muon mjj MET up", 250, 0., 250.);
  TH1F *mjj_excL_mu_RegA_iso_down = new TH1F("mjj_excL_mu_RegA_iso_down","Muon mjj ISO down", 250, 0., 250.);
  TH1F *mjj_excL_mu_RegA_iso_up = new TH1F("mjj_excL_mu_RegA_iso_up","Muon mjj ISO up", 250, 0., 250.);

  TH1F *mjj_excL_mu_RegB = new TH1F("mjj_excL_mu_RegB","Muon mjj", 250, 0., 250.);
  TH1F *mjj_excL_mu_RegB_met_down = new TH1F("mjj_excL_mu_RegB_met_down","Muon mjj MET down", 250, 0., 250.);
  TH1F *mjj_excL_mu_RegB_met_up = new TH1F("mjj_excL_mu_RegB_met_up","Muon mjj MET up", 250, 0., 250.);
  TH1F *mjj_excL_mu_RegB_iso_down = new TH1F("mjj_excL_mu_RegB_iso_down","Muon mjj ISO down", 250, 0., 250.);
  TH1F *mjj_excL_mu_RegB_iso_up = new TH1F("mjj_excL_mu_RegB_iso_up","Muon mjj ISO up", 250, 0., 250.);

  TH1F *mjj_excL_mu_RegC = new TH1F("mjj_excL_mu_RegC","Muon mjj", 250, 0., 250.);
  TH1F *mjj_excL_mu_RegC_met_down = new TH1F("mjj_excL_mu_RegC_met_down","Muon mjj MET down", 250, 0., 250.);
  TH1F *mjj_excL_mu_RegC_met_up = new TH1F("mjj_excL_mu_RegC_met_up","Muon mjj MET up", 250, 0., 250.);
  TH1F *mjj_excL_mu_RegC_iso_down = new TH1F("mjj_excL_mu_RegC_iso_down","Muon mjj ISO down", 250, 0., 250.);
  TH1F *mjj_excL_mu_RegC_iso_up = new TH1F("mjj_excL_mu_RegC_iso_up","Muon mjj ISO up", 250, 0., 250.);
  
  TH1F *mjj_excL_mu_RegD = new TH1F("mjj_excL_mu_RegD","Muon mjj", 250, 0., 250.);
  TH1F *mjj_excL_mu_RegD_met_down = new TH1F("mjj_excL_mu_RegD_met_down","Muon mjj MET down", 250, 0., 250.);
  TH1F *mjj_excL_mu_RegD_met_up = new TH1F("mjj_excL_mu_RegD_met_up","Muon mjj MET up", 250, 0., 250.);
  TH1F *mjj_excL_mu_RegD_iso_down = new TH1F("mjj_excL_mu_RegD_iso_down","Muon mjj ISO down", 250, 0., 250.);
  TH1F *mjj_excL_mu_RegD_iso_up = new TH1F("mjj_excL_mu_RegD_iso_up","Muon mjj ISO up", 250, 0., 250.);

  TH1F *mjj_excL_ele_RegA = new TH1F("mjj_excL_ele_RegA","Electron mjj", 250, 0., 250.);
  TH1F *mjj_excL_ele_RegA_met_down = new TH1F("mjj_excL_ele_RegA_met_down","Electron mjj MET down", 250, 0., 250.);
  TH1F *mjj_excL_ele_RegA_met_up = new TH1F("mjj_excL_ele_RegA_met_up","Electron mjj MET up", 250, 0., 250.);
  TH1F *mjj_excL_ele_RegA_iso_down = new TH1F("mjj_excL_ele_RegA_iso_down","Electron mjj ISO down", 250, 0., 250.);
  TH1F *mjj_excL_ele_RegA_iso_up = new TH1F("mjj_excL_ele_RegA_iso_up","Electron mjj ISO up", 250, 0., 250.);

  TH1F *mjj_excL_ele_RegB = new TH1F("mjj_excL_ele_RegB","Electron mjj", 250, 0., 250.);
  TH1F *mjj_excL_ele_RegB_met_down = new TH1F("mjj_excL_ele_RegB_met_down","Electron mjj MET down", 250, 0., 250.);
  TH1F *mjj_excL_ele_RegB_met_up = new TH1F("mjj_excL_ele_RegB_met_up","Electron mjj MET up", 250, 0., 250.);
  TH1F *mjj_excL_ele_RegB_iso_down = new TH1F("mjj_excL_ele_RegB_iso_down","Electron mjj ISO down", 250, 0., 250.);
  TH1F *mjj_excL_ele_RegB_iso_up = new TH1F("mjj_excL_ele_RegB_iso_up","Electron mjj ISO up", 250, 0., 250.);

  TH1F *mjj_excL_ele_RegC = new TH1F("mjj_excL_ele_RegC","Electron mjj", 250, 0., 250.);
  TH1F *mjj_excL_ele_RegC_met_down = new TH1F("mjj_excL_ele_RegC_met_down","Electron mjj MET down", 250, 0., 250.);
  TH1F *mjj_excL_ele_RegC_met_up = new TH1F("mjj_excL_ele_RegC_met_up","Electron mjj MET up", 250, 0., 250.);
  TH1F *mjj_excL_ele_RegC_iso_down = new TH1F("mjj_excL_ele_RegC_iso_down","Electron mjj ISO down", 250, 0., 250.);
  TH1F *mjj_excL_ele_RegC_iso_up = new TH1F("mjj_excL_ele_RegC_iso_up","Electron mjj ISO up", 250, 0., 250.);
  
  TH1F *mjj_excL_ele_RegD = new TH1F("mjj_excL_ele_RegD","Electron mjj", 250, 0., 250.);
  TH1F *mjj_excL_ele_RegD_met_down = new TH1F("mjj_excL_ele_RegD_met_down","Electron mjj MET down", 250, 0., 250.);
  TH1F *mjj_excL_ele_RegD_met_up = new TH1F("mjj_excL_ele_RegD_met_up","Electron mjj MET up", 250, 0., 250.);
  TH1F *mjj_excL_ele_RegD_iso_down = new TH1F("mjj_excL_ele_RegD_iso_down","Electron mjj ISO down", 250, 0., 250.);
  TH1F *mjj_excL_ele_RegD_iso_up = new TH1F("mjj_excL_ele_RegD_iso_up","Electron mjj ISO up", 250, 0., 250.);
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////// ExcM ///////////////////////////////////////////////
  TH1F *mjj_excM_mu_RegA = new TH1F("mjj_excM_mu_RegA","Muon mjj", 250, 0., 250.);
  TH1F *mjj_excM_mu_RegA_met_down = new TH1F("mjj_excM_mu_RegA_met_down","Muon mjj MET down", 250, 0., 250.);
  TH1F *mjj_excM_mu_RegA_met_up = new TH1F("mjj_excM_mu_RegA_met_up","Muon mjj MET up", 250, 0., 250.);
  TH1F *mjj_excM_mu_RegA_iso_down = new TH1F("mjj_excM_mu_RegA_iso_down","Muon mjj ISO down", 250, 0., 250.);
  TH1F *mjj_excM_mu_RegA_iso_up = new TH1F("mjj_excM_mu_RegA_iso_up","Muon mjj ISO up", 250, 0., 250.);

  TH1F *mjj_excM_mu_RegB = new TH1F("mjj_excM_mu_RegB","Muon mjj", 250, 0., 250.);
  TH1F *mjj_excM_mu_RegB_met_down = new TH1F("mjj_excM_mu_RegB_met_down","Muon mjj MET down", 250, 0., 250.);
  TH1F *mjj_excM_mu_RegB_met_up = new TH1F("mjj_excM_mu_RegB_met_up","Muon mjj MET up", 250, 0., 250.);
  TH1F *mjj_excM_mu_RegB_iso_down = new TH1F("mjj_excM_mu_RegB_iso_down","Muon mjj ISO down", 250, 0., 250.);
  TH1F *mjj_excM_mu_RegB_iso_up = new TH1F("mjj_excM_mu_RegB_iso_up","Muon mjj ISO up", 250, 0., 250.);

  TH1F *mjj_excM_mu_RegC = new TH1F("mjj_excM_mu_RegC","Muon mjj", 250, 0., 250.);
  TH1F *mjj_excM_mu_RegC_met_down = new TH1F("mjj_excM_mu_RegC_met_down","Muon mjj MET down", 250, 0., 250.);
  TH1F *mjj_excM_mu_RegC_met_up = new TH1F("mjj_excM_mu_RegC_met_up","Muon mjj MET up", 250, 0., 250.);
  TH1F *mjj_excM_mu_RegC_iso_down = new TH1F("mjj_excM_mu_RegC_iso_down","Muon mjj ISO down", 250, 0., 250.);
  TH1F *mjj_excM_mu_RegC_iso_up = new TH1F("mjj_excM_mu_RegC_iso_up","Muon mjj ISO up", 250, 0., 250.);
  
  TH1F *mjj_excM_mu_RegD = new TH1F("mjj_excM_mu_RegD","Muon mjj", 250, 0., 250.);
  TH1F *mjj_excM_mu_RegD_met_down = new TH1F("mjj_excM_mu_RegD_met_down","Muon mjj MET down", 250, 0., 250.);
  TH1F *mjj_excM_mu_RegD_met_up = new TH1F("mjj_excM_mu_RegD_met_up","Muon mjj MET up", 250, 0., 250.);
  TH1F *mjj_excM_mu_RegD_iso_down = new TH1F("mjj_excM_mu_RegD_iso_down","Muon mjj ISO down", 250, 0., 250.);
  TH1F *mjj_excM_mu_RegD_iso_up = new TH1F("mjj_excM_mu_RegD_iso_up","Muon mjj ISO up", 250, 0., 250.);

  TH1F *mjj_excM_ele_RegA = new TH1F("mjj_excM_ele_RegA","Electron mjj", 250, 0., 250.);
  TH1F *mjj_excM_ele_RegA_met_down = new TH1F("mjj_excM_ele_RegA_met_down","Electron mjj MET down", 250, 0., 250.);
  TH1F *mjj_excM_ele_RegA_met_up = new TH1F("mjj_excM_ele_RegA_met_up","Electron mjj MET up", 250, 0., 250.);
  TH1F *mjj_excM_ele_RegA_iso_down = new TH1F("mjj_excM_ele_RegA_iso_down","Electron mjj ISO down", 250, 0., 250.);
  TH1F *mjj_excM_ele_RegA_iso_up = new TH1F("mjj_excM_ele_RegA_iso_up","Electron mjj ISO up", 250, 0., 250.);

  TH1F *mjj_excM_ele_RegB = new TH1F("mjj_excM_ele_RegB","Electron mjj", 250, 0., 250.);
  TH1F *mjj_excM_ele_RegB_met_down = new TH1F("mjj_excM_ele_RegB_met_down","Electron mjj MET down", 250, 0., 250.);
  TH1F *mjj_excM_ele_RegB_met_up = new TH1F("mjj_excM_ele_RegB_met_up","Electron mjj MET up", 250, 0., 250.);
  TH1F *mjj_excM_ele_RegB_iso_down = new TH1F("mjj_excM_ele_RegB_iso_down","Electron mjj ISO down", 250, 0., 250.);
  TH1F *mjj_excM_ele_RegB_iso_up = new TH1F("mjj_excM_ele_RegB_iso_up","Electron mjj ISO up", 250, 0., 250.);

  TH1F *mjj_excM_ele_RegC = new TH1F("mjj_excM_ele_RegC","Electron mjj", 250, 0., 250.);
  TH1F *mjj_excM_ele_RegC_met_down = new TH1F("mjj_excM_ele_RegC_met_down","Electron mjj MET down", 250, 0., 250.);
  TH1F *mjj_excM_ele_RegC_met_up = new TH1F("mjj_excM_ele_RegC_met_up","Electron mjj MET up", 250, 0., 250.);
  TH1F *mjj_excM_ele_RegC_iso_down = new TH1F("mjj_excM_ele_RegC_iso_down","Electron mjj ISO down", 250, 0., 250.);
  TH1F *mjj_excM_ele_RegC_iso_up = new TH1F("mjj_excM_ele_RegC_iso_up","Electron mjj ISO up", 250, 0., 250.);
  
  TH1F *mjj_excM_ele_RegD = new TH1F("mjj_excM_ele_RegD","Electron mjj", 250, 0., 250.);
  TH1F *mjj_excM_ele_RegD_met_down = new TH1F("mjj_excM_ele_RegD_met_down","Electron mjj MET down", 250, 0., 250.);
  TH1F *mjj_excM_ele_RegD_met_up = new TH1F("mjj_excM_ele_RegD_met_up","Electron mjj MET up", 250, 0., 250.);
  TH1F *mjj_excM_ele_RegD_iso_down = new TH1F("mjj_excM_ele_RegD_iso_down","Electron mjj ISO down", 250, 0., 250.);
  TH1F *mjj_excM_ele_RegD_iso_up = new TH1F("mjj_excM_ele_RegD_iso_up","Electron mjj ISO up", 250, 0., 250.);
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////// ExcT ///////////////////////////////////////////////
  TH1F *mjj_excT_mu_RegA = new TH1F("mjj_excT_mu_RegA","Muon mjj", 250, 0., 250.);
  TH1F *mjj_excT_mu_RegA_met_down = new TH1F("mjj_excT_mu_RegA_met_down","Muon mjj MET down", 250, 0., 250.);
  TH1F *mjj_excT_mu_RegA_met_up = new TH1F("mjj_excT_mu_RegA_met_up","Muon mjj MET up", 250, 0., 250.);
  TH1F *mjj_excT_mu_RegA_iso_down = new TH1F("mjj_excT_mu_RegA_iso_down","Muon mjj ISO down", 250, 0., 250.);
  TH1F *mjj_excT_mu_RegA_iso_up = new TH1F("mjj_excT_mu_RegA_iso_up","Muon mjj ISO up", 250, 0., 250.);

  TH1F *mjj_excT_mu_RegB = new TH1F("mjj_excT_mu_RegB","Muon mjj", 250, 0., 250.);
  TH1F *mjj_excT_mu_RegB_met_down = new TH1F("mjj_excT_mu_RegB_met_down","Muon mjj MET down", 250, 0., 250.);
  TH1F *mjj_excT_mu_RegB_met_up = new TH1F("mjj_excT_mu_RegB_met_up","Muon mjj MET up", 250, 0., 250.);
  TH1F *mjj_excT_mu_RegB_iso_down = new TH1F("mjj_excT_mu_RegB_iso_down","Muon mjj ISO down", 250, 0., 250.);
  TH1F *mjj_excT_mu_RegB_iso_up = new TH1F("mjj_excT_mu_RegB_iso_up","Muon mjj ISO up", 250, 0., 250.);

  TH1F *mjj_excT_mu_RegC = new TH1F("mjj_excT_mu_RegC","Muon mjj", 250, 0., 250.);
  TH1F *mjj_excT_mu_RegC_met_down = new TH1F("mjj_excT_mu_RegC_met_down","Muon mjj MET down", 250, 0., 250.);
  TH1F *mjj_excT_mu_RegC_met_up = new TH1F("mjj_excT_mu_RegC_met_up","Muon mjj MET up", 250, 0., 250.);
  TH1F *mjj_excT_mu_RegC_iso_down = new TH1F("mjj_excT_mu_RegC_iso_down","Muon mjj ISO down", 250, 0., 250.);
  TH1F *mjj_excT_mu_RegC_iso_up = new TH1F("mjj_excT_mu_RegC_iso_up","Muon mjj ISO up", 250, 0., 250.);
  
  TH1F *mjj_excT_mu_RegD = new TH1F("mjj_excT_mu_RegD","Muon mjj", 250, 0., 250.);
  TH1F *mjj_excT_mu_RegD_met_down = new TH1F("mjj_excT_mu_RegD_met_down","Muon mjj MET down", 250, 0., 250.);
  TH1F *mjj_excT_mu_RegD_met_up = new TH1F("mjj_excT_mu_RegD_met_up","Muon mjj MET up", 250, 0., 250.);
  TH1F *mjj_excT_mu_RegD_iso_down = new TH1F("mjj_excT_mu_RegD_iso_down","Muon mjj ISO down", 250, 0., 250.);
  TH1F *mjj_excT_mu_RegD_iso_up = new TH1F("mjj_excT_mu_RegD_iso_up","Muon mjj ISO up", 250, 0., 250.);

  TH1F *mjj_excT_ele_RegA = new TH1F("mjj_excT_ele_RegA","Electron mjj", 250, 0., 250.);
  TH1F *mjj_excT_ele_RegA_met_down = new TH1F("mjj_excT_ele_RegA_met_down","Electron mjj MET down", 250, 0., 250.);
  TH1F *mjj_excT_ele_RegA_met_up = new TH1F("mjj_excT_ele_RegA_met_up","Electron mjj MET up", 250, 0., 250.);
  TH1F *mjj_excT_ele_RegA_iso_down = new TH1F("mjj_excT_ele_RegA_iso_down","Electron mjj ISO down", 250, 0., 250.);
  TH1F *mjj_excT_ele_RegA_iso_up = new TH1F("mjj_excT_ele_RegA_iso_up","Electron mjj ISO up", 250, 0., 250.);

  TH1F *mjj_excT_ele_RegB = new TH1F("mjj_excT_ele_RegB","Electron mjj", 250, 0., 250.);
  TH1F *mjj_excT_ele_RegB_met_down = new TH1F("mjj_excT_ele_RegB_met_down","Electron mjj MET down", 250, 0., 250.);
  TH1F *mjj_excT_ele_RegB_met_up = new TH1F("mjj_excT_ele_RegB_met_up","Electron mjj MET up", 250, 0., 250.);
  TH1F *mjj_excT_ele_RegB_iso_down = new TH1F("mjj_excT_ele_RegB_iso_down","Electron mjj ISO down", 250, 0., 250.);
  TH1F *mjj_excT_ele_RegB_iso_up = new TH1F("mjj_excT_ele_RegB_iso_up","Electron mjj ISO up", 250, 0., 250.);

  TH1F *mjj_excT_ele_RegC = new TH1F("mjj_excT_ele_RegC","Electron mjj", 250, 0., 250.);
  TH1F *mjj_excT_ele_RegC_met_down = new TH1F("mjj_excT_ele_RegC_met_down","Electron mjj MET down", 250, 0., 250.);
  TH1F *mjj_excT_ele_RegC_met_up = new TH1F("mjj_excT_ele_RegC_met_up","Electron mjj MET up", 250, 0., 250.);
  TH1F *mjj_excT_ele_RegC_iso_down = new TH1F("mjj_excT_ele_RegC_iso_down","Electron mjj ISO down", 250, 0., 250.);
  TH1F *mjj_excT_ele_RegC_iso_up = new TH1F("mjj_excT_ele_RegC_iso_up","Electron mjj ISO up", 250, 0., 250.);
  
  TH1F *mjj_excT_ele_RegD = new TH1F("mjj_excT_ele_RegD","Electron mjj", 250, 0., 250.);
  TH1F *mjj_excT_ele_RegD_met_down = new TH1F("mjj_excT_ele_RegD_met_down","Electron mjj MET down", 250, 0., 250.);
  TH1F *mjj_excT_ele_RegD_met_up = new TH1F("mjj_excT_ele_RegD_met_up","Electron mjj MET up", 250, 0., 250.);
  TH1F *mjj_excT_ele_RegD_iso_down = new TH1F("mjj_excT_ele_RegD_iso_down","Electron mjj ISO down", 250, 0., 250.);
  TH1F *mjj_excT_ele_RegD_iso_up = new TH1F("mjj_excT_ele_RegD_iso_up","Electron mjj ISO up", 250, 0., 250.);
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  float Min_pt = 25.0;
  float Max_eta = 2.4;

  float ele_rel_cut_EB = 0.0821;
  float ele_rel_cut_EE = 0.0695;
  float mu_rel_cut = 0.15;
  float met_cut = 20.0;

  
  bool isControl_mu = false;
  bool isControl_ele = false;
  for (Long64_t ievent = 0 ; ievent < tr->GetEntries() ; ievent++ ) {    
  //for (Long64_t ievent = 0 ; ievent < tr->GetEntries()/10 ; ievent++ ) {    
    
    tr->GetEntry(ievent) ;
    if(ievent%1000000==0)
      cout<<"iEvent : " << ievent << ", chi2 : "<<chi2<<endl;

    ////////////////////////// Muon ////////////////////////////////////
    wt_before_mu_iso = hWtB_mu_iso->GetBinContent(nJet+1);
    wt_after_mu_iso = hWtA_mu_iso->GetBinContent(nJet+1);
    wt_ratio_mu_iso = 1 ;
    if(!TMath::AreEqualAbs(wt_after_mu_iso,0.0,1.0e-5))
      wt_ratio_mu_iso = wt_before_mu_iso/wt_after_mu_iso;

    wt_before_mu_lmet = hWtB_mu_lmet->GetBinContent(nJet+1);
    wt_after_mu_lmet = hWtA_mu_lmet->GetBinContent(nJet+1);
    wt_ratio_mu_lmet = 1 ;
    if(!TMath::AreEqualAbs(wt_after_mu_lmet,0.0,1.0e-5))
      wt_ratio_mu_lmet = wt_before_mu_lmet/wt_after_mu_lmet;

    wt_before_mu_noniso = hWtB_mu_noniso->GetBinContent(nJet+1);
    wt_after_mu_noniso = hWtA_mu_noniso->GetBinContent(nJet+1);
    wt_ratio_mu_noniso = 1 ;
    if(!TMath::AreEqualAbs(wt_after_mu_noniso,0.0,1.0e-5))
      wt_ratio_mu_noniso = wt_before_mu_noniso/wt_after_mu_noniso;

    wt_before_mu_noniso_lmet = hWtB_mu_noniso_lmet->GetBinContent(nJet+1);
    wt_after_mu_noniso_lmet = hWtA_mu_noniso_lmet->GetBinContent(nJet+1);
    wt_ratio_mu_noniso_lmet = 1 ;
    if(!TMath::AreEqualAbs(wt_after_mu_noniso_lmet,0.0,1.0e-5))
      wt_ratio_mu_noniso_lmet = wt_before_mu_noniso_lmet/wt_after_mu_noniso_lmet;

    ///////////////////////////////////////////////////////////////////

    /////////////////////// Ele //////////////////////////////////////
    wt_before_ele_iso = hWtB_ele_iso->GetBinContent(nJet+1);
    wt_after_ele_iso = hWtA_ele_iso->GetBinContent(nJet+1);
    wt_ratio_ele_iso = 1 ;
    if(!TMath::AreEqualAbs(wt_after_ele_iso,0.0,1.0e-5))
      wt_ratio_ele_iso = wt_before_ele_iso/wt_after_ele_iso;

    wt_before_ele_lmet = hWtB_ele_lmet->GetBinContent(nJet+1);
    wt_after_ele_lmet = hWtA_ele_lmet->GetBinContent(nJet+1);
    wt_ratio_ele_lmet = 1 ;
    if(!TMath::AreEqualAbs(wt_after_ele_lmet,0.0,1.0e-5))
      wt_ratio_ele_lmet = wt_before_ele_lmet/wt_after_ele_lmet;

    wt_before_ele_noniso = hWtB_ele_noniso->GetBinContent(nJet+1);
    wt_after_ele_noniso = hWtA_ele_noniso->GetBinContent(nJet+1);
    wt_ratio_ele_noniso = 1 ;
    if(!TMath::AreEqualAbs(wt_after_ele_noniso,0.0,1.0e-5))
      wt_ratio_ele_noniso = wt_before_ele_noniso/wt_after_ele_noniso;

    wt_before_ele_noniso_lmet = hWtB_ele_noniso_lmet->GetBinContent(nJet+1);
    wt_after_ele_noniso_lmet = hWtA_ele_noniso_lmet->GetBinContent(nJet+1);
    wt_ratio_ele_noniso_lmet = 1 ;
    if(!TMath::AreEqualAbs(wt_after_ele_noniso_lmet,0.0,1.0e-5))
      wt_ratio_ele_noniso_lmet = wt_before_ele_noniso_lmet/wt_after_ele_noniso_lmet;
    /////////////////////////////////////////////////////////////////////

    bjhad.SetPtEtaPhiE(jetBhadPt, jetBhadEta, jetBhadPhi, jetBhadEn);
    chad.SetPtEtaPhiE(jetChadPt, jetChadEta, jetChadPhi, jetChadEn);
    shad.SetPtEtaPhiE(jetShadPt, jetShadEta, jetShadPhi, jetShadEn);
    
    bjlep.SetPtEtaPhiE(jetBlepPt, jetBlepEta, jetBlepPhi, jetBlepEn);
    lep.SetPtEtaPhiE(lepPt, lepEta, lepPhi, lepEn);
    met.SetXYZM(metPx, metPy, metPz, 0.0);
    
    weight_mu = sampleWeight*prefireWeight*PUWeight*muEffWeight*puJetIDWeight*bcTagWeight;
    weight_ele = sampleWeight*prefireWeight*PUWeight*eleEffWeight*puJetIDWeight*bcTagWeight;
    mjjKF = (chad+shad).M();

    bool isPtCut = (jetShadPt > Min_pt and jetChadPt > Min_pt and jetBhadPt > Min_pt and jetBlepPt > Min_pt);
    bool isEtaCut = (abs(jetShadEta) < Max_eta and abs(jetChadEta) < Max_eta and abs(jetBhadEta) < Max_eta and abs(jetBlepEta) < Max_eta);
    bool passRelIso_ele = ((lepEta < 1.479 && elepfRelIso < ele_rel_cut_EB) || (lepEta > 1.479 && elepfRelIso < ele_rel_cut_EE));  //gap has been taken care before KF
    bool passRelIso_ele_down = ((lepEta < 1.479 && elepfRelIso < 0.5*ele_rel_cut_EB) || (lepEta > 1.479 && elepfRelIso < 0.5*ele_rel_cut_EE));  //gap has been taken care before KF
    bool passRelIso_ele_up = ((lepEta < 1.479 && elepfRelIso < 1.5*ele_rel_cut_EB) || (lepEta > 1.479 && elepfRelIso < 1.5*ele_rel_cut_EE));  //gap has been taken care before KF
    bool passRelIso_mu = (muonpfRelIso<mu_rel_cut);
    bool passRelIso_mu_down = (muonpfRelIso<0.5*mu_rel_cut);
    bool passRelIso_mu_up = (muonpfRelIso<1.5*mu_rel_cut);
    bool passMET = (met.Pt()>met_cut);
    bool passMET_down = (met.Pt()> 0.5*met_cut);
    bool passMET_up = (met.Pt()> 1.5*met_cut);
    
    if(isPtCut and isEtaCut and singleMu and !singleEle){
      if(passRelIso_mu and passMET) mjj_mu_RegA->Fill(mjjKF,weight_mu*wt_ratio_mu_iso);
      if(!passRelIso_mu and passMET) mjj_mu_RegB->Fill(mjjKF,weight_mu*wt_ratio_mu_noniso);
      if(!passRelIso_mu and !passMET) mjj_mu_RegC->Fill(mjjKF,weight_mu*wt_ratio_mu_noniso_lmet);
      if(passRelIso_mu and !passMET) mjj_mu_RegD->Fill(mjjKF,weight_mu*wt_ratio_mu_lmet);
      
      if(passRelIso_mu and passMET_down) mjj_mu_RegA_met_down->Fill(mjjKF,weight_mu*wt_ratio_mu_iso);
      if(!passRelIso_mu and passMET_down) mjj_mu_RegB_met_down->Fill(mjjKF,weight_mu*wt_ratio_mu_noniso);
      if(!passRelIso_mu and !passMET_down) mjj_mu_RegC_met_down->Fill(mjjKF,weight_mu*wt_ratio_mu_noniso_lmet);
      if(passRelIso_mu and !passMET_down) mjj_mu_RegD_met_down->Fill(mjjKF,weight_mu*wt_ratio_mu_lmet);
      
      if(passRelIso_mu and passMET_up) mjj_mu_RegA_met_up->Fill(mjjKF,weight_mu*wt_ratio_mu_iso);
      if(!passRelIso_mu and passMET_up) mjj_mu_RegB_met_up->Fill(mjjKF,weight_mu*wt_ratio_mu_noniso);
      if(!passRelIso_mu and !passMET_up) mjj_mu_RegC_met_up->Fill(mjjKF,weight_mu*wt_ratio_mu_noniso_lmet);
      if(passRelIso_mu and !passMET_up) mjj_mu_RegD_met_up->Fill(mjjKF,weight_mu*wt_ratio_mu_lmet);

      if(passRelIso_mu_down and passMET) mjj_mu_RegA_iso_down->Fill(mjjKF,weight_mu*wt_ratio_mu_iso);
      if(!passRelIso_mu_down and passMET) mjj_mu_RegB_iso_down->Fill(mjjKF,weight_mu*wt_ratio_mu_noniso);
      if(!passRelIso_mu_down and !passMET) mjj_mu_RegC_iso_down->Fill(mjjKF,weight_mu*wt_ratio_mu_noniso_lmet);
      if(passRelIso_mu_down and !passMET) mjj_mu_RegD_iso_down->Fill(mjjKF,weight_mu*wt_ratio_mu_lmet);
      
      if(passRelIso_mu_up and passMET) mjj_mu_RegA_iso_up->Fill(mjjKF,weight_mu*wt_ratio_mu_iso);
      if(!passRelIso_mu_up and passMET) mjj_mu_RegB_iso_up->Fill(mjjKF,weight_mu*wt_ratio_mu_noniso);
      if(!passRelIso_mu_up and !passMET) mjj_mu_RegC_iso_up->Fill(mjjKF,weight_mu*wt_ratio_mu_noniso_lmet);
      if(passRelIso_mu_up and !passMET) mjj_mu_RegD_iso_up->Fill(mjjKF,weight_mu*wt_ratio_mu_lmet);
      
      if(count_cJetsIncT>0){
	if(passRelIso_mu and passMET) mjj_excT_mu_RegA->Fill(mjjKF,weight_mu*wt_ratio_mu_iso);
	if(!passRelIso_mu and passMET) mjj_excT_mu_RegB->Fill(mjjKF,weight_mu*wt_ratio_mu_noniso);
	if(!passRelIso_mu and !passMET) mjj_excT_mu_RegC->Fill(mjjKF,weight_mu*wt_ratio_mu_noniso_lmet);
	if(passRelIso_mu and !passMET) mjj_excT_mu_RegD->Fill(mjjKF,weight_mu*wt_ratio_mu_lmet);
      
	if(passRelIso_mu and passMET_down) mjj_excT_mu_RegA_met_down->Fill(mjjKF,weight_mu*wt_ratio_mu_iso);
	if(!passRelIso_mu and passMET_down) mjj_excT_mu_RegB_met_down->Fill(mjjKF,weight_mu*wt_ratio_mu_noniso);
	if(!passRelIso_mu and !passMET_down) mjj_excT_mu_RegC_met_down->Fill(mjjKF,weight_mu*wt_ratio_mu_noniso_lmet);
	if(passRelIso_mu and !passMET_down) mjj_excT_mu_RegD_met_down->Fill(mjjKF,weight_mu*wt_ratio_mu_lmet);
      
	if(passRelIso_mu and passMET_up) mjj_excT_mu_RegA_met_up->Fill(mjjKF,weight_mu*wt_ratio_mu_iso);
	if(!passRelIso_mu and passMET_up) mjj_excT_mu_RegB_met_up->Fill(mjjKF,weight_mu*wt_ratio_mu_noniso);
	if(!passRelIso_mu and !passMET_up) mjj_excT_mu_RegC_met_up->Fill(mjjKF,weight_mu*wt_ratio_mu_noniso_lmet);
	if(passRelIso_mu and !passMET_up) mjj_excT_mu_RegD_met_up->Fill(mjjKF,weight_mu*wt_ratio_mu_lmet);

	if(passRelIso_mu_down and passMET) mjj_excT_mu_RegA_iso_down->Fill(mjjKF,weight_mu*wt_ratio_mu_iso);
	if(!passRelIso_mu_down and passMET) mjj_excT_mu_RegB_iso_down->Fill(mjjKF,weight_mu*wt_ratio_mu_noniso);
	if(!passRelIso_mu_down and !passMET) mjj_excT_mu_RegC_iso_down->Fill(mjjKF,weight_mu*wt_ratio_mu_noniso_lmet);
	if(passRelIso_mu_down and !passMET) mjj_excT_mu_RegD_iso_down->Fill(mjjKF,weight_mu*wt_ratio_mu_lmet);
      
	if(passRelIso_mu_up and passMET) mjj_excT_mu_RegA_iso_up->Fill(mjjKF,weight_mu*wt_ratio_mu_iso);
	if(!passRelIso_mu_up and passMET) mjj_excT_mu_RegB_iso_up->Fill(mjjKF,weight_mu*wt_ratio_mu_noniso);
	if(!passRelIso_mu_up and !passMET) mjj_excT_mu_RegC_iso_up->Fill(mjjKF,weight_mu*wt_ratio_mu_noniso_lmet);
	if(passRelIso_mu_up and !passMET) mjj_excT_mu_RegD_iso_up->Fill(mjjKF,weight_mu*wt_ratio_mu_lmet);
      } else if(count_cJetsIncM>0){
	if(passRelIso_mu and passMET) mjj_excM_mu_RegA->Fill(mjjKF,weight_mu*wt_ratio_mu_iso);
	if(!passRelIso_mu and passMET) mjj_excM_mu_RegB->Fill(mjjKF,weight_mu*wt_ratio_mu_noniso);
	if(!passRelIso_mu and !passMET) mjj_excM_mu_RegC->Fill(mjjKF,weight_mu*wt_ratio_mu_noniso_lmet);
	if(passRelIso_mu and !passMET) mjj_excM_mu_RegD->Fill(mjjKF,weight_mu*wt_ratio_mu_lmet);
      
	if(passRelIso_mu and passMET_down) mjj_excM_mu_RegA_met_down->Fill(mjjKF,weight_mu*wt_ratio_mu_iso);
	if(!passRelIso_mu and passMET_down) mjj_excM_mu_RegB_met_down->Fill(mjjKF,weight_mu*wt_ratio_mu_noniso);
	if(!passRelIso_mu and !passMET_down) mjj_excM_mu_RegC_met_down->Fill(mjjKF,weight_mu*wt_ratio_mu_noniso_lmet);
	if(passRelIso_mu and !passMET_down) mjj_excM_mu_RegD_met_down->Fill(mjjKF,weight_mu*wt_ratio_mu_lmet);
      
	if(passRelIso_mu and passMET_up) mjj_excM_mu_RegA_met_up->Fill(mjjKF,weight_mu*wt_ratio_mu_iso);
	if(!passRelIso_mu and passMET_up) mjj_excM_mu_RegB_met_up->Fill(mjjKF,weight_mu*wt_ratio_mu_noniso);
	if(!passRelIso_mu and !passMET_up) mjj_excM_mu_RegC_met_up->Fill(mjjKF,weight_mu*wt_ratio_mu_noniso_lmet);
	if(passRelIso_mu and !passMET_up) mjj_excM_mu_RegD_met_up->Fill(mjjKF,weight_mu*wt_ratio_mu_lmet);

	if(passRelIso_mu_down and passMET) mjj_excM_mu_RegA_iso_down->Fill(mjjKF,weight_mu*wt_ratio_mu_iso);
	if(!passRelIso_mu_down and passMET) mjj_excM_mu_RegB_iso_down->Fill(mjjKF,weight_mu*wt_ratio_mu_noniso);
	if(!passRelIso_mu_down and !passMET) mjj_excM_mu_RegC_iso_down->Fill(mjjKF,weight_mu*wt_ratio_mu_noniso_lmet);
	if(passRelIso_mu_down and !passMET) mjj_excM_mu_RegD_iso_down->Fill(mjjKF,weight_mu*wt_ratio_mu_lmet);
      
	if(passRelIso_mu_up and passMET) mjj_excM_mu_RegA_iso_up->Fill(mjjKF,weight_mu*wt_ratio_mu_iso);
	if(!passRelIso_mu_up and passMET) mjj_excM_mu_RegB_iso_up->Fill(mjjKF,weight_mu*wt_ratio_mu_noniso);
	if(!passRelIso_mu_up and !passMET) mjj_excM_mu_RegC_iso_up->Fill(mjjKF,weight_mu*wt_ratio_mu_noniso_lmet);
	if(passRelIso_mu_up and !passMET) mjj_excM_mu_RegD_iso_up->Fill(mjjKF,weight_mu*wt_ratio_mu_lmet);
      }else if(count_cJetsIncL>0){
	if(passRelIso_mu and passMET) mjj_excL_mu_RegA->Fill(mjjKF,weight_mu*wt_ratio_mu_iso);
	if(!passRelIso_mu and passMET) mjj_excL_mu_RegB->Fill(mjjKF,weight_mu*wt_ratio_mu_noniso);
	if(!passRelIso_mu and !passMET) mjj_excL_mu_RegC->Fill(mjjKF,weight_mu*wt_ratio_mu_noniso_lmet);
	if(passRelIso_mu and !passMET) mjj_excL_mu_RegD->Fill(mjjKF,weight_mu*wt_ratio_mu_lmet);
      
	if(passRelIso_mu and passMET_down) mjj_excL_mu_RegA_met_down->Fill(mjjKF,weight_mu*wt_ratio_mu_iso);
	if(!passRelIso_mu and passMET_down) mjj_excL_mu_RegB_met_down->Fill(mjjKF,weight_mu*wt_ratio_mu_noniso);
	if(!passRelIso_mu and !passMET_down) mjj_excL_mu_RegC_met_down->Fill(mjjKF,weight_mu*wt_ratio_mu_noniso_lmet);
	if(passRelIso_mu and !passMET_down) mjj_excL_mu_RegD_met_down->Fill(mjjKF,weight_mu*wt_ratio_mu_lmet);
      
	if(passRelIso_mu and passMET_up) mjj_excL_mu_RegA_met_up->Fill(mjjKF,weight_mu*wt_ratio_mu_iso);
	if(!passRelIso_mu and passMET_up) mjj_excL_mu_RegB_met_up->Fill(mjjKF,weight_mu*wt_ratio_mu_noniso);
	if(!passRelIso_mu and !passMET_up) mjj_excL_mu_RegC_met_up->Fill(mjjKF,weight_mu*wt_ratio_mu_noniso_lmet);
	if(passRelIso_mu and !passMET_up) mjj_excL_mu_RegD_met_up->Fill(mjjKF,weight_mu*wt_ratio_mu_lmet);

	if(passRelIso_mu_down and passMET) mjj_excL_mu_RegA_iso_down->Fill(mjjKF,weight_mu*wt_ratio_mu_iso);
	if(!passRelIso_mu_down and passMET) mjj_excL_mu_RegB_iso_down->Fill(mjjKF,weight_mu*wt_ratio_mu_noniso);
	if(!passRelIso_mu_down and !passMET) mjj_excL_mu_RegC_iso_down->Fill(mjjKF,weight_mu*wt_ratio_mu_noniso_lmet);
	if(passRelIso_mu_down and !passMET) mjj_excL_mu_RegD_iso_down->Fill(mjjKF,weight_mu*wt_ratio_mu_lmet);
      
	if(passRelIso_mu_up and passMET) mjj_excL_mu_RegA_iso_up->Fill(mjjKF,weight_mu*wt_ratio_mu_iso);
	if(!passRelIso_mu_up and passMET) mjj_excL_mu_RegB_iso_up->Fill(mjjKF,weight_mu*wt_ratio_mu_noniso);
	if(!passRelIso_mu_up and !passMET) mjj_excL_mu_RegC_iso_up->Fill(mjjKF,weight_mu*wt_ratio_mu_noniso_lmet);
	if(passRelIso_mu_up and !passMET) mjj_excL_mu_RegD_iso_up->Fill(mjjKF,weight_mu*wt_ratio_mu_lmet);
      } else {
	;
      }//exclusive
    }//single muon condn
    
    if(isPtCut and isEtaCut and !singleMu and singleEle){
      if(passRelIso_ele and passMET) mjj_ele_RegA->Fill(mjjKF,weight_ele*wt_ratio_ele_iso);
      if(!passRelIso_ele and passMET) mjj_ele_RegB->Fill(mjjKF,weight_ele*wt_ratio_ele_noniso);
      if(!passRelIso_ele and !passMET) mjj_ele_RegC->Fill(mjjKF,weight_ele*wt_ratio_ele_noniso_lmet);
      if(passRelIso_ele and !passMET) mjj_ele_RegD->Fill(mjjKF,weight_ele*wt_ratio_ele_lmet);
      
      if(passRelIso_ele and passMET_down) mjj_ele_RegA_met_down->Fill(mjjKF,weight_ele*wt_ratio_ele_iso);
      if(!passRelIso_ele and passMET_down) mjj_ele_RegB_met_down->Fill(mjjKF,weight_ele*wt_ratio_ele_noniso);
      if(!passRelIso_ele and !passMET_down) mjj_ele_RegC_met_down->Fill(mjjKF,weight_ele*wt_ratio_ele_noniso_lmet);
      if(passRelIso_ele and !passMET_down) mjj_ele_RegD_met_down->Fill(mjjKF,weight_ele*wt_ratio_ele_lmet);
      
      if(passRelIso_ele and passMET_up) mjj_ele_RegA_met_up->Fill(mjjKF,weight_ele*wt_ratio_ele_iso);
      if(!passRelIso_ele and passMET_up) mjj_ele_RegB_met_up->Fill(mjjKF,weight_ele*wt_ratio_ele_noniso);
      if(!passRelIso_ele and !passMET_up) mjj_ele_RegC_met_up->Fill(mjjKF,weight_ele*wt_ratio_ele_noniso_lmet);
      if(passRelIso_ele and !passMET_up) mjj_ele_RegD_met_up->Fill(mjjKF,weight_ele*wt_ratio_ele_lmet);
      
      if(passRelIso_ele_down and passMET) mjj_ele_RegA_iso_down->Fill(mjjKF,weight_ele*wt_ratio_ele_iso);
      if(!passRelIso_ele_down and passMET) mjj_ele_RegB_iso_down->Fill(mjjKF,weight_ele*wt_ratio_ele_noniso);
      if(!passRelIso_ele_down and !passMET) mjj_ele_RegC_iso_down->Fill(mjjKF,weight_ele*wt_ratio_ele_noniso_lmet);
      if(passRelIso_ele_down and !passMET) mjj_ele_RegD_iso_down->Fill(mjjKF,weight_ele*wt_ratio_ele_lmet);
      
      if(passRelIso_ele_up and passMET) mjj_ele_RegA_iso_up->Fill(mjjKF,weight_ele*wt_ratio_ele_iso);
      if(!passRelIso_ele_up and passMET) mjj_ele_RegB_iso_up->Fill(mjjKF,weight_ele*wt_ratio_ele_noniso);
      if(!passRelIso_ele_up and !passMET) mjj_ele_RegC_iso_up->Fill(mjjKF,weight_ele*wt_ratio_ele_noniso_lmet);
      if(passRelIso_ele_up and !passMET) mjj_ele_RegD_iso_up->Fill(mjjKF,weight_ele*wt_ratio_ele_lmet);
      if(count_cJetsIncT>0){
	if(passRelIso_ele and passMET) mjj_excT_ele_RegA->Fill(mjjKF,weight_ele*wt_ratio_ele_iso);
	if(!passRelIso_ele and passMET) mjj_excT_ele_RegB->Fill(mjjKF,weight_ele*wt_ratio_ele_noniso);
	if(!passRelIso_ele and !passMET) mjj_excT_ele_RegC->Fill(mjjKF,weight_ele*wt_ratio_ele_noniso_lmet);
	if(passRelIso_ele and !passMET) mjj_excT_ele_RegD->Fill(mjjKF,weight_ele*wt_ratio_ele_lmet);
      
	if(passRelIso_ele and passMET_down) mjj_excT_ele_RegA_met_down->Fill(mjjKF,weight_ele*wt_ratio_ele_iso);
	if(!passRelIso_ele and passMET_down) mjj_excT_ele_RegB_met_down->Fill(mjjKF,weight_ele*wt_ratio_ele_noniso);
	if(!passRelIso_ele and !passMET_down) mjj_excT_ele_RegC_met_down->Fill(mjjKF,weight_ele*wt_ratio_ele_noniso_lmet);
	if(passRelIso_ele and !passMET_down) mjj_excT_ele_RegD_met_down->Fill(mjjKF,weight_ele*wt_ratio_ele_lmet);
      
	if(passRelIso_ele and passMET_up) mjj_excT_ele_RegA_met_up->Fill(mjjKF,weight_ele*wt_ratio_ele_iso);
	if(!passRelIso_ele and passMET_up) mjj_excT_ele_RegB_met_up->Fill(mjjKF,weight_ele*wt_ratio_ele_noniso);
	if(!passRelIso_ele and !passMET_up) mjj_excT_ele_RegC_met_up->Fill(mjjKF,weight_ele*wt_ratio_ele_noniso_lmet);
	if(passRelIso_ele and !passMET_up) mjj_excT_ele_RegD_met_up->Fill(mjjKF,weight_ele*wt_ratio_ele_lmet);

	if(passRelIso_ele_down and passMET) mjj_excT_ele_RegA_iso_down->Fill(mjjKF,weight_ele*wt_ratio_ele_iso);
	if(!passRelIso_ele_down and passMET) mjj_excT_ele_RegB_iso_down->Fill(mjjKF,weight_ele*wt_ratio_ele_noniso);
	if(!passRelIso_ele_down and !passMET) mjj_excT_ele_RegC_iso_down->Fill(mjjKF,weight_ele*wt_ratio_ele_noniso_lmet);
	if(passRelIso_ele_down and !passMET) mjj_excT_ele_RegD_iso_down->Fill(mjjKF,weight_ele*wt_ratio_ele_lmet);
      
	if(passRelIso_ele_up and passMET) mjj_excT_ele_RegA_iso_up->Fill(mjjKF,weight_ele*wt_ratio_ele_iso);
	if(!passRelIso_ele_up and passMET) mjj_excT_ele_RegB_iso_up->Fill(mjjKF,weight_ele*wt_ratio_ele_noniso);
	if(!passRelIso_ele_up and !passMET) mjj_excT_ele_RegC_iso_up->Fill(mjjKF,weight_ele*wt_ratio_ele_noniso_lmet);
	if(passRelIso_ele_up and !passMET) mjj_excT_ele_RegD_iso_up->Fill(mjjKF,weight_ele*wt_ratio_ele_lmet);
      }else if (count_cJetsIncM>0){
	if(passRelIso_ele and passMET) mjj_excM_ele_RegA->Fill(mjjKF,weight_ele*wt_ratio_ele_iso);
	if(!passRelIso_ele and passMET) mjj_excM_ele_RegB->Fill(mjjKF,weight_ele*wt_ratio_ele_noniso);
	if(!passRelIso_ele and !passMET) mjj_excM_ele_RegC->Fill(mjjKF,weight_ele*wt_ratio_ele_noniso_lmet);
	if(passRelIso_ele and !passMET) mjj_excM_ele_RegD->Fill(mjjKF,weight_ele*wt_ratio_ele_lmet);
      
	if(passRelIso_ele and passMET_down) mjj_excM_ele_RegA_met_down->Fill(mjjKF,weight_ele*wt_ratio_ele_iso);
	if(!passRelIso_ele and passMET_down) mjj_excM_ele_RegB_met_down->Fill(mjjKF,weight_ele*wt_ratio_ele_noniso);
	if(!passRelIso_ele and !passMET_down) mjj_excM_ele_RegC_met_down->Fill(mjjKF,weight_ele*wt_ratio_ele_noniso_lmet);
	if(passRelIso_ele and !passMET_down) mjj_excM_ele_RegD_met_down->Fill(mjjKF,weight_ele*wt_ratio_ele_lmet);
      
	if(passRelIso_ele and passMET_up) mjj_excM_ele_RegA_met_up->Fill(mjjKF,weight_ele*wt_ratio_ele_iso);
	if(!passRelIso_ele and passMET_up) mjj_excM_ele_RegB_met_up->Fill(mjjKF,weight_ele*wt_ratio_ele_noniso);
	if(!passRelIso_ele and !passMET_up) mjj_excM_ele_RegC_met_up->Fill(mjjKF,weight_ele*wt_ratio_ele_noniso_lmet);
	if(passRelIso_ele and !passMET_up) mjj_excM_ele_RegD_met_up->Fill(mjjKF,weight_ele*wt_ratio_ele_lmet);

	if(passRelIso_ele_down and passMET) mjj_excM_ele_RegA_iso_down->Fill(mjjKF,weight_ele*wt_ratio_ele_iso);
	if(!passRelIso_ele_down and passMET) mjj_excM_ele_RegB_iso_down->Fill(mjjKF,weight_ele*wt_ratio_ele_noniso);
	if(!passRelIso_ele_down and !passMET) mjj_excM_ele_RegC_iso_down->Fill(mjjKF,weight_ele*wt_ratio_ele_noniso_lmet);
	if(passRelIso_ele_down and !passMET) mjj_excM_ele_RegD_iso_down->Fill(mjjKF,weight_ele*wt_ratio_ele_lmet);
      
	if(passRelIso_ele_up and passMET) mjj_excM_ele_RegA_iso_up->Fill(mjjKF,weight_ele*wt_ratio_ele_iso);
	if(!passRelIso_ele_up and passMET) mjj_excM_ele_RegB_iso_up->Fill(mjjKF,weight_ele*wt_ratio_ele_noniso);
	if(!passRelIso_ele_up and !passMET) mjj_excM_ele_RegC_iso_up->Fill(mjjKF,weight_ele*wt_ratio_ele_noniso_lmet);
	if(passRelIso_ele_up and !passMET) mjj_excM_ele_RegD_iso_up->Fill(mjjKF,weight_ele*wt_ratio_ele_lmet);
      }else if (count_cJetsIncL>0){
	if(passRelIso_ele and passMET) mjj_excL_ele_RegA->Fill(mjjKF,weight_ele*wt_ratio_ele_iso);
	if(!passRelIso_ele and passMET) mjj_excL_ele_RegB->Fill(mjjKF,weight_ele*wt_ratio_ele_noniso);
	if(!passRelIso_ele and !passMET) mjj_excL_ele_RegC->Fill(mjjKF,weight_ele*wt_ratio_ele_noniso_lmet);
	if(passRelIso_ele and !passMET) mjj_excL_ele_RegD->Fill(mjjKF,weight_ele*wt_ratio_ele_lmet);
      
	if(passRelIso_ele and passMET_down) mjj_excL_ele_RegA_met_down->Fill(mjjKF,weight_ele*wt_ratio_ele_iso);
	if(!passRelIso_ele and passMET_down) mjj_excL_ele_RegB_met_down->Fill(mjjKF,weight_ele*wt_ratio_ele_noniso);
	if(!passRelIso_ele and !passMET_down) mjj_excL_ele_RegC_met_down->Fill(mjjKF,weight_ele*wt_ratio_ele_noniso_lmet);
	if(passRelIso_ele and !passMET_down) mjj_excL_ele_RegD_met_down->Fill(mjjKF,weight_ele*wt_ratio_ele_lmet);
      
	if(passRelIso_ele and passMET_up) mjj_excL_ele_RegA_met_up->Fill(mjjKF,weight_ele*wt_ratio_ele_iso);
	if(!passRelIso_ele and passMET_up) mjj_excL_ele_RegB_met_up->Fill(mjjKF,weight_ele*wt_ratio_ele_noniso);
	if(!passRelIso_ele and !passMET_up) mjj_excL_ele_RegC_met_up->Fill(mjjKF,weight_ele*wt_ratio_ele_noniso_lmet);
	if(passRelIso_ele and !passMET_up) mjj_excL_ele_RegD_met_up->Fill(mjjKF,weight_ele*wt_ratio_ele_lmet);

	if(passRelIso_ele_down and passMET) mjj_excL_ele_RegA_iso_down->Fill(mjjKF,weight_ele*wt_ratio_ele_iso);
	if(!passRelIso_ele_down and passMET) mjj_excL_ele_RegB_iso_down->Fill(mjjKF,weight_ele*wt_ratio_ele_noniso);
	if(!passRelIso_ele_down and !passMET) mjj_excL_ele_RegC_iso_down->Fill(mjjKF,weight_ele*wt_ratio_ele_noniso_lmet);
	if(passRelIso_ele_down and !passMET) mjj_excL_ele_RegD_iso_down->Fill(mjjKF,weight_ele*wt_ratio_ele_lmet);
      
	if(passRelIso_ele_up and passMET) mjj_excL_ele_RegA_iso_up->Fill(mjjKF,weight_ele*wt_ratio_ele_iso);
	if(!passRelIso_ele_up and passMET) mjj_excL_ele_RegB_iso_up->Fill(mjjKF,weight_ele*wt_ratio_ele_noniso);
	if(!passRelIso_ele_up and !passMET) mjj_excL_ele_RegC_iso_up->Fill(mjjKF,weight_ele*wt_ratio_ele_noniso_lmet);
	if(passRelIso_ele_up and !passMET) mjj_excL_ele_RegD_iso_up->Fill(mjjKF,weight_ele*wt_ratio_ele_lmet);
      } else {
	;
      }//exclusive
    }//single-electron

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
      // Isomu_vs_MET->Fill(met.Et(), muonpfRelIso);
      // Isomu_vs_MET_th2->Fill(muonpfRelIso, met.Et());
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
      // Isoele_vs_MET->Fill(met.Et(), elepfRelIso);
      // Isoele_vs_MET_th2->Fill(elepfRelIso, met.Et());
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

  TFile *fout = new TFile("IsoMET_QCD.root","recreate");
  Isomu_AB->Write();
  Isomu_CD->Write();
  Isoele_AB->Write();
  Isoele_CD->Write();
  METmu_AD->Write();
  METmu_BC->Write();
  METele_AD->Write(); 
  METele_BC->Write();
  mjj_mu_RegA->Write();
  mjj_mu_RegB->Write();
  mjj_mu_RegC->Write();
  mjj_mu_RegD->Write();
  mjj_mu_RegA_met_down->Write();
  mjj_mu_RegB_met_down->Write();
  mjj_mu_RegC_met_down->Write();
  mjj_mu_RegD_met_down->Write();
  mjj_mu_RegA_met_up->Write();
  mjj_mu_RegB_met_up->Write();
  mjj_mu_RegC_met_up->Write();
  mjj_mu_RegD_met_up->Write();
  mjj_mu_RegA_iso_down->Write();
  mjj_mu_RegB_iso_down->Write();
  mjj_mu_RegC_iso_down->Write();
  mjj_mu_RegD_iso_down->Write();
  mjj_mu_RegA_iso_up->Write();
  mjj_mu_RegB_iso_up->Write();
  mjj_mu_RegC_iso_up->Write();
  mjj_mu_RegD_iso_up->Write();
  mjj_ele_RegA->Write();
  mjj_ele_RegB->Write();
  mjj_ele_RegC->Write();
  mjj_ele_RegD->Write();
  mjj_ele_RegA_met_down->Write();
  mjj_ele_RegB_met_down->Write();
  mjj_ele_RegC_met_down->Write();
  mjj_ele_RegD_met_down->Write();
  mjj_ele_RegA_met_up->Write();
  mjj_ele_RegB_met_up->Write();
  mjj_ele_RegC_met_up->Write();
  mjj_ele_RegD_met_up->Write();
  mjj_ele_RegA_iso_down->Write();
  mjj_ele_RegB_iso_down->Write();
  mjj_ele_RegC_iso_down->Write();
  mjj_ele_RegD_iso_down->Write();
  mjj_ele_RegA_iso_up->Write();
  mjj_ele_RegB_iso_up->Write();
  mjj_ele_RegC_iso_up->Write();
  mjj_ele_RegD_iso_up->Write();

  mjj_excL_mu_RegA->Write();
  mjj_excL_mu_RegB->Write();
  mjj_excL_mu_RegC->Write();
  mjj_excL_mu_RegD->Write();
  mjj_excL_mu_RegA_met_down->Write();
  mjj_excL_mu_RegB_met_down->Write();
  mjj_excL_mu_RegC_met_down->Write();
  mjj_excL_mu_RegD_met_down->Write();
  mjj_excL_mu_RegA_met_up->Write();
  mjj_excL_mu_RegB_met_up->Write();
  mjj_excL_mu_RegC_met_up->Write();
  mjj_excL_mu_RegD_met_up->Write();
  mjj_excL_mu_RegA_iso_down->Write();
  mjj_excL_mu_RegB_iso_down->Write();
  mjj_excL_mu_RegC_iso_down->Write();
  mjj_excL_mu_RegD_iso_down->Write();
  mjj_excL_mu_RegA_iso_up->Write();
  mjj_excL_mu_RegB_iso_up->Write();
  mjj_excL_mu_RegC_iso_up->Write();
  mjj_excL_mu_RegD_iso_up->Write();
  mjj_excL_ele_RegA->Write();
  mjj_excL_ele_RegB->Write();
  mjj_excL_ele_RegC->Write();
  mjj_excL_ele_RegD->Write();
  mjj_excL_ele_RegA_met_down->Write();
  mjj_excL_ele_RegB_met_down->Write();
  mjj_excL_ele_RegC_met_down->Write();
  mjj_excL_ele_RegD_met_down->Write();
  mjj_excL_ele_RegA_met_up->Write();
  mjj_excL_ele_RegB_met_up->Write();
  mjj_excL_ele_RegC_met_up->Write();
  mjj_excL_ele_RegD_met_up->Write();
  mjj_excL_ele_RegA_iso_down->Write();
  mjj_excL_ele_RegB_iso_down->Write();
  mjj_excL_ele_RegC_iso_down->Write();
  mjj_excL_ele_RegD_iso_down->Write();
  mjj_excL_ele_RegA_iso_up->Write();
  mjj_excL_ele_RegB_iso_up->Write();
  mjj_excL_ele_RegC_iso_up->Write();
  mjj_excL_ele_RegD_iso_up->Write();

  mjj_excM_mu_RegA->Write();
  mjj_excM_mu_RegB->Write();
  mjj_excM_mu_RegC->Write();
  mjj_excM_mu_RegD->Write();
  mjj_excM_mu_RegA_met_down->Write();
  mjj_excM_mu_RegB_met_down->Write();
  mjj_excM_mu_RegC_met_down->Write();
  mjj_excM_mu_RegD_met_down->Write();
  mjj_excM_mu_RegA_met_up->Write();
  mjj_excM_mu_RegB_met_up->Write();
  mjj_excM_mu_RegC_met_up->Write();
  mjj_excM_mu_RegD_met_up->Write();
  mjj_excM_mu_RegA_iso_down->Write();
  mjj_excM_mu_RegB_iso_down->Write();
  mjj_excM_mu_RegC_iso_down->Write();
  mjj_excM_mu_RegD_iso_down->Write();
  mjj_excM_mu_RegA_iso_up->Write();
  mjj_excM_mu_RegB_iso_up->Write();
  mjj_excM_mu_RegC_iso_up->Write();
  mjj_excM_mu_RegD_iso_up->Write();
  mjj_excM_ele_RegA->Write();
  mjj_excM_ele_RegB->Write();
  mjj_excM_ele_RegC->Write();
  mjj_excM_ele_RegD->Write();
  mjj_excM_ele_RegA_met_down->Write();
  mjj_excM_ele_RegB_met_down->Write();
  mjj_excM_ele_RegC_met_down->Write();
  mjj_excM_ele_RegD_met_down->Write();
  mjj_excM_ele_RegA_met_up->Write();
  mjj_excM_ele_RegB_met_up->Write();
  mjj_excM_ele_RegC_met_up->Write();
  mjj_excM_ele_RegD_met_up->Write();
  mjj_excM_ele_RegA_iso_down->Write();
  mjj_excM_ele_RegB_iso_down->Write();
  mjj_excM_ele_RegC_iso_down->Write();
  mjj_excM_ele_RegD_iso_down->Write();
  mjj_excM_ele_RegA_iso_up->Write();
  mjj_excM_ele_RegB_iso_up->Write();
  mjj_excM_ele_RegC_iso_up->Write();
  mjj_excM_ele_RegD_iso_up->Write();
  
  mjj_excT_mu_RegA->Write();
  mjj_excT_mu_RegB->Write();
  mjj_excT_mu_RegC->Write();
  mjj_excT_mu_RegD->Write();
  mjj_excT_mu_RegA_met_down->Write();
  mjj_excT_mu_RegB_met_down->Write();
  mjj_excT_mu_RegC_met_down->Write();
  mjj_excT_mu_RegD_met_down->Write();
  mjj_excT_mu_RegA_met_up->Write();
  mjj_excT_mu_RegB_met_up->Write();
  mjj_excT_mu_RegC_met_up->Write();
  mjj_excT_mu_RegD_met_up->Write();
  mjj_excT_mu_RegA_iso_down->Write();
  mjj_excT_mu_RegB_iso_down->Write();
  mjj_excT_mu_RegC_iso_down->Write();
  mjj_excT_mu_RegD_iso_down->Write();
  mjj_excT_mu_RegA_iso_up->Write();
  mjj_excT_mu_RegB_iso_up->Write();
  mjj_excT_mu_RegC_iso_up->Write();
  mjj_excT_mu_RegD_iso_up->Write();
  mjj_excT_ele_RegA->Write();
  mjj_excT_ele_RegB->Write();
  mjj_excT_ele_RegC->Write();
  mjj_excT_ele_RegD->Write();
  mjj_excT_ele_RegA_met_down->Write();
  mjj_excT_ele_RegB_met_down->Write();
  mjj_excT_ele_RegC_met_down->Write();
  mjj_excT_ele_RegD_met_down->Write();
  mjj_excT_ele_RegA_met_up->Write();
  mjj_excT_ele_RegB_met_up->Write();
  mjj_excT_ele_RegC_met_up->Write();
  mjj_excT_ele_RegD_met_up->Write();
  mjj_excT_ele_RegA_iso_down->Write();
  mjj_excT_ele_RegB_iso_down->Write();
  mjj_excT_ele_RegC_iso_down->Write();
  mjj_excT_ele_RegD_iso_down->Write();
  mjj_excT_ele_RegA_iso_up->Write();
  mjj_excT_ele_RegB_iso_up->Write();
  mjj_excT_ele_RegC_iso_up->Write();
  mjj_excT_ele_RegD_iso_up->Write();
  fout->Close();
  delete fout;
  
  delete tr;
  
  return true;
}
