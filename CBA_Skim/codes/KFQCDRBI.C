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
  
  //string inpath_tree = Form("/eos/cms/store/group/phys_b2g/idas/Output/cms-hcs-run2/Result/CBA_metxycorr/%d",year);
  string treelist = "/tmp/idas/fl_tree_list.txt";
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

  // tr->SetBranchAddress("sampleWeight"	, &sampleWeight);
  // tr->SetBranchAddress("prefireWeight"	, &prefireWeight);
  // tr->SetBranchAddress("PUWeight"	, &PUWeight);
  // tr->SetBranchAddress("muEffWeight"	, &muEffWeight);
  // tr->SetBranchAddress("eleEffWeight"	, &eleEffWeight);
  // tr->SetBranchAddress("puJetIDWeight"	, &puJetIDWeight);
  // // tr->SetBranchAddress("bTagWeight"	, &bTagWeight);
  // // tr->SetBranchAddress("cTagLWeight"	, &cTagLWeight);
  // // tr->SetBranchAddress("cTagMWeight"	, &cTagMWeight);
  // // tr->SetBranchAddress("cTagTWeight"	, &cTagTWeight);

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

  cout << "NofEvents : " << tr->GetEntries() << endl;

  TLorentzVector chad, shad, bjhad;
  TLorentzVector met, lep, bjlep;
  
  TH1F *Isomu_AB = new TH1F("Isomu_AB",Form("Isomu AB vs CD (muon, %s)",signal.c_str()),50,0.0,0.3);
  TH1F *Isomu_CD = new TH1F("Isomu_CD",Form("Isomu AB vs CD (muon, %s)",signal.c_str()),50,0.0,0.3);
  TH1F *Isoele_AB = new TH1F("Isoele_AB",Form("Isoele AB vs CD (ele, %s)",signal.c_str()),50,0.0,0.3);
  TH1F *Isoele_CD = new TH1F("Isoele_CD",Form("Isoele AB vs CD (ele, %s)",signal.c_str()),50,0.0,0.3);

  TH1F *METmu_AD = new TH1F("METmu_AD",Form("MET AD vs BC (muon, %s)",signal.c_str()),50,0.0,500.);
  TH1F *METmu_BC = new TH1F("METmu_BC",Form("MET AD vs BC (muon, %s)",signal.c_str()),50,0.0,500.);
  TH1F *METele_AD = new TH1F("METele_AD",Form("MET AD vs BC (ele, %s)",signal.c_str()),50,0.0,500.);
  TH1F *METele_BC = new TH1F("METele_BC",Form("MET AD vs BC (ele, %s)",signal.c_str()),50,0.0,500.);
  
  float Min_pt = 25.0;
  float Max_eta = 2.4;

  bool isControl_mu = false;
  bool isControl_ele = false;
  for (Long64_t ievent = 0 ; ievent < tr->GetEntries() ; ievent++ ) {    
  //for (Long64_t ievent = 0 ; ievent < tr->GetEntries()/10 ; ievent++ ) {    
    
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
      
    // topHM->Fill( (chad+shad+bjhad).M() );
    // topLM->Fill( (lep+met+bjlep).M() );
    // wLM->Fill( (lep+met).M() );
    
    // prefire_Eta_bjet->Fill( ((bjhad.Pt()>bjlep.Pt())?bjhad.Eta():bjlep.Eta()), prefireWeight);
    // prefire_Eta_ljet->Fill( ((chad.Pt()>shad.Pt())?chad.Eta():shad.Eta()), prefireWeight);
    
    // if(singleMu and !singleEle)
    //   SFWt_Pt_mu->Fill( lepPt, muEffWeight);
    // else
    //   SFWt_Pt_ele->Fill( lepPt, eleEffWeight);

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
  fout->Close();
  delete fout;
  
  delete tr;
  
  return true;
}
