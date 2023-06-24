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

void KFDDPlots(int year = 2016, string signal = "DYjets")
{
  //samples_2016="DataMu DataEle TTbar singleTop Wjets DYjets VBFusion MCQCDMu MCQCDEle HplusM080 HplusM090 HplusM100 HplusM110 HplusM120 HplusM130 HplusM140 HplusM150 HplusM155 HplusM160  HminusM080 HminusM090 HminusM100 HminusM110 HminusM120 HminusM130 HminusM140 HminusM150 HminusM155 HminusM160"
  //string signal = "MCQCDMu";
  //string signal = "DataEle";
  //int year = 2016;
  
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
  
  Double_t weight, weightEle, mjjKF;
  
  //string inpath_tree = Form("/Data/root_files/KinFit/CBA_elereliso/pre/%d",year);
  //string inpath_tree = Form("/run/media/indra/DHEP_Storage_3/Data/NanoAOD/KinFit/CBA_elereliso/");
  //string inpath_tree = Form("/eos/user/a/anayak/HplusAnalysisRun2/idas/Output/cms-hcs-run2/CBA_elemva90/*/%d",year);
  string inpath_tree = Form("/eos/user/a/anayak/HplusAnalysisRun2/idas/Output/cms-hcs-run2/CBA_trigSF/*/%d",year);
  if(year==2017)
    inpath_tree = Form("/eos/user/a/anayak/HplusAnalysisRun2/idas/Output/cms-hcs-run2/CBA_HLTeleEmul/%d",year);
  if(year==2018)
    inpath_tree = Form("/eos/user/a/anayak/HplusAnalysisRun2/idas/Output/cms-hcs-run2/CBA_trigSF/%d",year);
  string treelist = "/tmp/fl_tree_list.txt";
  string command = Form("find %s -name \"%s_tree_base_*.root\" > %s",inpath_tree.data(),signal.data(),treelist.data());
  //string command = Form("find %s -name \"%s_tree_iso20_*.root\" > %s",inpath_tree.data(),signal.data(),treelist.data());
  int response = system(command.c_str());
  
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
  tr->SetBranchAddress("bcTagWeight"	, &bcTagWeight);
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
  //tree->SetBranchStatus("nJet",1);
  tr->SetBranchAddress("nJet", &nJet);
  
  TLorentzVector chad, shad, bjhad;
  TLorentzVector met, lep, bjlep;
  
  float Min_pt = 25.0;
  float Max_eta = 2.4;
  TH1F *topHM = new TH1F("topHM","#it{t} #rightarrow #it{b}+#it{jj}", 300, 0., 300.);
  TH1F *topLM = new TH1F("topLM","#it{t} #rightarrow #it{b}+#it{l}#nu", 300, 0., 300.);
  TH1F *wLM = new TH1F("wLM","#it{W} #rightarrow #it{l}#nu", 250, 0., 250.);
  TH1F *METptMu_B = new TH1F("METptMu_B","Reg B : METpt (mu+jets)", 500, 0., 500.);
  TH1F *IsoMu_B = new TH1F("IsoMu_B","Reg B : RelIso (mu+jets)", 1000, 0., 10.0);
  TH1F *METptEle_B = new TH1F("METptEle_B","Reg B : METpt (ele+jets)", 500, 0., 500.);
  TH1F *IsoEle_B = new TH1F("IsoEle_B","Reg B : RelIso (ele+jets)", 1000, 0., 10.0);

  TH1F *mjjMu_Ap = new TH1F("mjjMu_Ap",Form("Reg A^{/} : mjj (%s)",signal.c_str()), 240, 0., 240.0);
  TH1F *mjjMu_Bp = new TH1F("mjjMu_Bp",Form("Reg B^{/} : mjj (%s)",signal.c_str()), 240, 0., 240.0);
  TH1F *mjjMu_Cp = new TH1F("mjjMu_Cp",Form("Reg C^{/} : mjj (%s)",signal.c_str()), 240, 0., 240.0);
  TH1F *mjjMu_Dp = new TH1F("mjjMu_Dp",Form("Reg D^{/} : mjj (%s)",signal.c_str()), 240, 0., 240.0);

  TH1F *mjjEle_Ap = new TH1F("mjjEle_Ap",Form("Reg A^{/} : mjj (%s)",signal.c_str()), 240, 0., 240.0);
  TH1F *mjjEle_Bp = new TH1F("mjjEle_Bp",Form("Reg B^{/} : mjj (%s)",signal.c_str()), 240, 0., 240.0);
  TH1F *mjjEle_Cp = new TH1F("mjjEle_Cp",Form("Reg C^{/} : mjj (%s)",signal.c_str()), 240, 0., 240.0);
  TH1F *mjjEle_Dp = new TH1F("mjjEle_Dp",Form("Reg D^{/} : mjj (%s)",signal.c_str()), 240, 0., 240.0);
  
  bool isControl_mu = false;
  bool isControl_ele = false;

  string inpath_hist = Form("/eos/user/i/idas/Output/cms-hcs-run2/CBA_trigSF/%d",year);
  if(year==2017)
    inpath_hist = Form("/eos/user/i/idas/Output/cms-hcs-run2/CBA_HLTeleEmul/%d/all",year);
  if(year==2018)
    inpath_hist = Form("/eos/user/i/idas/Output/cms-hcs-run2/CBA_trigSF/%d/all",year);

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

  cout << "Signal : " << signal << ", Total Entries : " << tr->GetEntries() << endl;
  for (Long64_t ievent = 0 ; ievent < tr->GetEntries() ; ievent++ ) {    
  //for (Long64_t ievent = 0 ; ievent < tr->GetEntries()/10 ; ievent++ ) {    
    
    tr->GetEntry(ievent) ;

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
    
    wt_ratio_mu = 1.0;
    if(met.Pt() > 15.0 and muonpfRelIso<0.2) //A prime
      wt_ratio_mu = wt_ratio_mu_iso ;
    else if(met.Pt() > 15.0 and muonpfRelIso>0.2) //B prime
      wt_ratio_mu = wt_ratio_mu_noniso ;
    else if(met.Pt() < 15.0 and muonpfRelIso>0.2) //C prime
      wt_ratio_mu = wt_ratio_mu_noniso_lmet ;
    else if(met.Pt() < 15.0 and muonpfRelIso<0.2) //D prime
      wt_ratio_mu = wt_ratio_mu_lmet ;

    wt_ratio_ele = 1.0;
    if(met.Pt() > 15.0 and elepfRelIso<0.13) //A prime
      wt_ratio_ele = wt_ratio_ele_iso ;
    else if(met.Pt() > 15.0 and elepfRelIso>0.13) //B prime
      wt_ratio_ele = wt_ratio_ele_noniso ;
    else if(met.Pt() < 15.0 and elepfRelIso>0.13) //C prime
      wt_ratio_ele = wt_ratio_ele_noniso_lmet ;
    else if(met.Pt() < 15.0 and elepfRelIso<0.13) //D prime
      wt_ratio_ele = wt_ratio_ele_lmet ;

    weight = sampleWeight*prefireWeight*PUWeight*muEffWeight*puJetIDWeight*bcTagWeight*wt_ratio_mu;
    weightEle = sampleWeight*prefireWeight*PUWeight*eleEffWeight*puJetIDWeight*bcTagWeight*wt_ratio_ele;
    if(ievent%1000000==0)
      cout<<"iEvent : " << ievent << ", chi2 : "<<chi2<<", weight : "<<weight<<endl;
    
    mjjKF = (chad+shad).M();
    
    topHM->Fill( (chad+shad+bjhad).M() );
    topLM->Fill( (lep+met+bjlep).M() );
    wLM->Fill( (lep+met).M() );
    
    // if(singleMu and !singleEle){ // Muon
    //   if(!muonIsoCut and !isLowMET){ //Region B
    // 	METptMu_B->Fill(met.Pt());
    // 	IsoMu_B->Fill(muonpfRelIso);	
    // 	if(met.Pt() > 40.0 and muonpfRelIso<0.25) //A prime
    // 	  mjjMu_Ap->Fill(mjjKF, weight);
    // 	else if(met.Pt() > 40.0 and muonpfRelIso>0.25) //B prime
    // 	  mjjMu_Bp->Fill(mjjKF, weight);
    // 	else if(met.Pt() < 40.0 and muonpfRelIso>0.25) //C prime
    // 	  mjjMu_Cp->Fill(mjjKF, weight);
    // 	else if(met.Pt() < 40.0 and muonpfRelIso<0.25) //D prime
    // 	  mjjMu_Dp->Fill(mjjKF, weight);
    //   }
    // }
    
    if(singleMu and !singleEle){ // Muon
      if(met.Pt() > 15.0 and muonpfRelIso>0.2){
	  METptMu_B->Fill(met.Pt(), weight);
	  IsoMu_B->Fill(muonpfRelIso, weight);
	//Nominal Iso = 0.35 and syst Iso = 0.4
  	if(met.Pt() > 40.0 and muonpfRelIso<0.4) //A prime 
  	  mjjMu_Ap->Fill(mjjKF, weight);
  	else if(met.Pt() > 40.0 and muonpfRelIso>0.4) //B prime
  	  mjjMu_Bp->Fill(mjjKF, weight);
	else if(met.Pt() < 40.0 and muonpfRelIso>0.4) //C prime
  	  mjjMu_Cp->Fill(mjjKF, weight);
  	else if(met.Pt() < 40.0 and muonpfRelIso<0.4) //D prime
  	  mjjMu_Dp->Fill(mjjKF, weight);
      }
    }
    
    if(singleEle and !singleMu){
      if(met.Pt() > 15.0 and elepfRelIso>0.13){
  	METptEle_B->Fill(met.Pt(), weightEle);
  	IsoEle_B->Fill(elepfRelIso, weightEle);
	//Nominal Iso = 0.17 and syst Iso = 0.2
  	if(met.Pt() > 40.0 and elepfRelIso<0.2) //A prime
  	  mjjEle_Ap->Fill(mjjKF, weightEle);
  	else if(met.Pt() > 40.0 and elepfRelIso>0.2) //B prime
  	  mjjEle_Bp->Fill(mjjKF, weightEle);
  	else if(met.Pt() < 40.0 and elepfRelIso>0.2) //C prime
  	  mjjEle_Cp->Fill(mjjKF, weightEle);
  	else if(met.Pt() < 40.0 and elepfRelIso<0.2) //C prime
  	  mjjEle_Dp->Fill(mjjKF, weightEle);
      }
    }
    
  }//event loop
  
  
  
  //TFile *fout = new TFile(Form("output_%s.root",signal.c_str()),"recreate");
  //TFile *fout = new TFile(Form("output_%s_%d.root",signal.c_str(),year),"recreate");
  //TFile *fout = new TFile(Form("output_%s_iso20_%d.root",signal.c_str(),year),"recreate");
  TFile *fout = new TFile(Form("output_caseC_splitB_%s_iso20_%d.root",signal.c_str(),year),"recreate");
  //TFile *fout = new TFile(Form("output_caseC_splitB_%s_%d.root",signal.c_str(),year),"recreate");
  METptMu_B->Write();
  IsoMu_B->Write();
  METptEle_B->Write();
  IsoEle_B->Write();
  mjjMu_Ap->Write();
  mjjMu_Bp->Write();
  mjjMu_Cp->Write();
  mjjMu_Dp->Write();
  mjjEle_Ap->Write();
  mjjEle_Bp->Write();
  mjjEle_Cp->Write();
  mjjEle_Dp->Write();
  // c2->Write();
  // c3->Write();
  fout->Close();

  fRefF->Close();
  delete fRefF;

  //delete tr;
}
