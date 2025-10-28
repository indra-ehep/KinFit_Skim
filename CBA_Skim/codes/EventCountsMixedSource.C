/**********************************************************************
 Created on : 25/07/2025
 Purpose    : Obtain the cutflow numbers from mixed source of cutflow histogram and kinfit tree
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

int EventCountsMixedSource(const char *infile_hist = "", const char *infile_tree = "", const char *infile_hist1 = "", bool isMu = 1)
{
  
  const char* cutflow = (isMu) ? "_cutflow_mu" : "_cutflow_ele";
  const char* cutflowUS = (isMu) ? "_cutflowUS_mu" : "_cutflowUS_ele";
  const char* lch = (isMu) ? "mu" : "ele";
  
  TFile *fin_hist = 0x0, *fin_tree = 0x0;
  fin_hist = TFile::Open(infile_hist);
  fin_tree = TFile::Open(infile_tree);
  TFile *fin_hist1 = TFile::Open(infile_hist1);
  
  if(!fin_hist){
    printf("Failed to open file %s\n",infile_hist);
    return false;
  }
  
  if(!fin_tree){
    printf("Failed to open file %s\n",infile_tree);
    fin_hist->Close();
    delete fin_hist;
    return false;
  }

  if(!fin_hist1){
    printf("Failed to open file %s\n",infile_hist1);
    fin_hist->Close();
    fin_tree->Close();
    delete fin_hist;
    delete fin_tree;
    return false;
  }

  //TH1D *hcf_nano_data	= (TH1D *)fin_hist->Get(Form("TTbar/base/Iso/%s",cutflowUS));
  const char *sample = "TTbar";
  //const char *sample = "HplusM120";
  TH1D *hcf_nano_data	= (TH1D *)fin_hist->Get(Form("%s/base/Iso/%s",sample,cutflowUS));
  TH1D *hcf_nano_wt	= (TH1D *)fin_hist->Get(Form("%s/base/Iso/%s",sample,cutflow));
  TH1D *hbjet_mjj	= (TH1D *)fin_hist1->Get(Form("%s/base/Iso/_lb_mjj_%s",sample,lch));
  TH1D *hkf_mjj	        = (TH1D *)fin_hist1->Get(Form("%s/base/Iso/_kb_mjj_%s",sample,lch));
  TH1D *hkf_mjj_excL	= (TH1D *)fin_hist1->Get(Form("%s/base/Iso/_ct_ExcL_mjj_%s",sample,lch));
  TH1D *hkf_mjj_excM	= (TH1D *)fin_hist1->Get(Form("%s/base/Iso/_ct_ExcM_mjj_%s",sample,lch));
  TH1D *hkf_mjj_excT	= (TH1D *)fin_hist1->Get(Form("%s/base/Iso/_ct_ExcT_mjj_%s",sample,lch));
  TH1D *hkf_mjj_exc0	= (TH1D *)fin_hist1->Get(Form("%s/base/Iso/_ct_Exc0_mjj_%s",sample,lch));
  
  cout<<"Processing : " << fin_hist->GetName() << endl;
  
  double nofKF = 0, nofExcT = 0, nofExcM = 0, nofExcL = 0, nofExc0 = 0;
  void GetKFInfo(TFile *fin_tree, double& nofKF, double& nofExcT, double& nofExcM,
		 double& nofExcL, double& nofExc0);
  GetKFInfo(fin_tree, nofKF, nofExcT, nofExcM, nofExcL, nofExc0);
  double totExcl = nofExcT + nofExcM + nofExcL + nofExc0 ;
  cout << "NofKF : " << nofKF << ", nofExcL: " << nofExcL << ", nofExcM: " << nofExcM
       << ", nofExcT: " << nofExcT << ", nofExc0: " << nofExc0 << ", totExcl: " << totExcl << endl;
  double array[6];
  array[0] = nofKF;
  array[1] = nofExcL;
  array[2] = nofExcM;
  array[3] = nofExcT;
  array[4] = nofExcM;
  array[4] = nofExc0;
  
  printf("%s & ",hcf_nano_data->GetName());
  for (int ibin=2;ibin<hcf_nano_data->GetNbinsX();ibin++){
    if(hcf_nano_data->GetBinContent(ibin)>0.0 and hcf_nano_data->GetBinContent(ibin+1)>0.0){
      if(hcf_nano_data->GetBinContent(ibin)>1e6){
	printf("%.4e & ",hcf_nano_data->GetBinContent(ibin)); 
      }else{
	printf("%.1f & ",hcf_nano_data->GetBinContent(ibin));
      }
    }else if(hcf_nano_data->GetBinContent(ibin)>0.0 and TMath::AreEqualAbs(hcf_nano_data->GetBinContent(ibin+1),0.0,1.e-5)){
      printf("%.1f \\\\\\hline ",hcf_nano_data->GetBinContent(ibin));
    }
  }
  printf("\n\n");
  
  printf("Result & ");
  for (int ibin=1;ibin<=10;ibin++){
    double result = (ibin<6)? hcf_nano_data->GetBinContent(ibin+1) : array[ibin-6] ;
    if(result>1e6)
      printf("%.4e & ",result); 
    else
      printf("%.1f & ",result);    
  }
  printf("\\\\\\hline ");
  printf("\n\n");

  printf("Normalized Result & ");
  for (int ibin=1;ibin<=10;ibin++){
  double result = 0;
  if(ibin<6)
    result = hcf_nano_wt->GetBinContent(ibin+1);
  else if(ibin==5){
    result =  hbjet_mjj->Integral();
  }else if(ibin==6){
    result =  hkf_mjj->Integral();
    nofKF = hkf_mjj->Integral();
  }else if(ibin==7){
    result =  hkf_mjj_excL->Integral();
    nofExcL = hkf_mjj_excL->Integral();
  }else if(ibin==8){
    result =  hkf_mjj_excM->Integral();
    nofExcM = hkf_mjj_excM->Integral();
  }else if(ibin==9){
    result =  hkf_mjj_excT->Integral();
    nofExcT = hkf_mjj_excT->Integral();
  }else if(ibin==10){
    result =  hkf_mjj_exc0->Integral();
    nofExc0 = hkf_mjj_exc0->Integral();
  }
  //Dangerous condition
  if(strcmp(sample,"TTbar")==0) result = 2.0*result;
  
  if(result>1e6)
    printf("%.4e & ",result); 
  else
    printf("%.1f & ",result);    
  }
  printf("\\\\\\hline ");
  printf("\n");
  totExcl = nofExcT + nofExcM + nofExcL ;//+ nofExc0 ;
  cout << "NofKF : " << nofKF << ", nofExcL: " << nofExcL << ", nofExcM: " << nofExcM
       << ", nofExcT: " << nofExcT << ", nofExc0: " << nofExc0 << ", totExcl: " << totExcl << endl;

  fin_hist->Close();
  delete fin_hist;
  
  fin_tree->Close();
  delete fin_tree;
  
  return true;
}

void GetKFInfo(TFile *fin_tree, double& nofKF, double& nofExcT, double& nofExcM, double& nofExcL, double& nofExc0)
{
  
  Float_t   metPx;
  Float_t   metPy;
  Float_t   metPz;
  
  Bool_t singleMu;
  Bool_t singleEle;
  Bool_t muonIsoCut;
  Bool_t isLowMET;
  
  int cjhad_ctag, sjhad_ctag;
  
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

  TLorentzVector met;

  cout << "Total Entries : " << tr->GetEntries() << endl;
  for (Long64_t ievent = 0 ; ievent < tr->GetEntries() ; ievent++ ) {        
    tr->GetEntry(ievent) ;
    // if(ievent%1000000==0)
    //   cout<<"iEvent : " << ievent << ", chi2 : "<<chi2<<endl;
    met.SetXYZM(metPx, metPy, metPz, 0.0);
    //if(singleMu and !singleEle and muonIsoCut and !isLowMET){
    if(singleMu and !singleEle and muonIsoCut and met.Pt()>20.0){
      nofKF++;
      if(cjhad_ctag==3 or sjhad_ctag==3){
	nofExcT++;
      }else if(cjhad_ctag==2 or sjhad_ctag==2){
	nofExcM++;
      }else if(cjhad_ctag==1 or sjhad_ctag==1){
	nofExcL++;
      }else{
	nofExc0++;
      }
    }
  }//event loop

}
