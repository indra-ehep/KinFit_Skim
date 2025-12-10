#include <iostream>
#include <fstream>
#include <cstring>

#include "TFile.h"
#include "TTree.h"
#include "TGraph.h"
#include "TROOT.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "Math/ProbFunc.h"
#include "TLegend.h"
#include "TArrow.h"

//void count_toys_with_signif_lt_localmax(const char* year, int mass, const char* bkgfile, const char* datafile){
int calcGlobalp()
{
  float getMaxSig(std::string bfitfname, std::string datafname);

  std::string indir = "/home/hep/idas/CMS-Analysis/NanoAOD-Analysis/SkimAna/limit_lx04/local/signif_qcdrange0to50_qcddd6_bc3_uncorr_br0p0010to0p0110_sym_nzlbin_10GeV_grid100_iter1/Run2/Comb/mu_ele/Cat1_Inc/Mass60/";
  
  //Valid [where MultiDimFit has "not" failed] incides created with command
  //
  //rm /tmp/indices.txt ; while read fname ; do  nofline=`grep  "MultiDimFit failed" $fname | wc -l` ; if [ $nofline -eq 0 ] ; then  echo $fname | cut -f 1 -d '.' | cut -d '_' -f 15 >> /tmp/indices.txt ; fi ; done < /tmp/fnames.txt  
  std::string validindex = "/tmp/indices.txt" ;
  int index = 1;
  std::string bkgfile = indir + "higgsCombine_bfit_toy" + std::to_string(index) + ".MultiDimFit.mH60.root";
  std::string datafile = indir + "higgsCombine_data_toy" + std::to_string(index) + ".MultiDimFit.mH60.root";
  std::cout << "index : " << index << ", max_sig: " << getMaxSig(bkgfile, datafile) << std::endl;

  ifstream fin(validindex);
  std::string s;
  vector<float> maxsigs;
  while (getline(fin,s)){
    index = std::stoi(s);
    std::string bkgfile = indir + "higgsCombine_bfit_toy" + std::to_string(index) + ".MultiDimFit.mH60.root";
    std::string datafile = indir + "higgsCombine_data_toy" + std::to_string(index) + ".MultiDimFit.mH60.root";
    float maxsig = getMaxSig(bkgfile, datafile);
    maxsigs.push_back(maxsig);
    std::cout << "index : " << index << ", max_sig: " << getMaxSig(bkgfile, datafile) << std::endl;
  }
  
  TH1F *hSig = new TH1F("hSig","",60,0,3);
  for(uint32_t isig=0;isig<maxsigs.size();isig++){
    if(maxsigs.at(isig)==0.0) continue;
    hSig->Fill(maxsigs.at(isig));
  }
  maxsigs.clear();

  float localp = 2.4041;
  float globalp = hSig->GetMean();
  TArrow *ar = new TArrow(localp,3.0,localp,30,0.02,"<|");
  ar->SetLineWidth(2);
  ar->SetLineColor(kBlack);
  ar->SetFillColor(kOrange +7);

  TObject *obj = 0x0;
  TLegend* leg = new TLegend(0.26,0.19,0.48,0.39,NULL,"brNDC");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.026);
  leg->SetFillColor(0);
  leg->SetHeader("");
  leg->AddEntry(obj, Form("local significance : %2.1f#sigma",localp),"");   //2.4041
  leg->AddEntry(obj, Form("global significance : %2.1f#sigma",globalp),"");  //1.215 from histogram mean
  leg->AddEntry(obj, Form("local p-value : %5.4f",ROOT::Math::normal_cdf_c(localp)),"");  //ROOT::Math::normal_cdf_c(2.4041) = 0.0081
  leg->AddEntry(obj, Form("global p-value : %5.4f",ROOT::Math::normal_cdf_c(globalp)),""); //ROOT::Math::normal_cdf_c(1.215) = 0.1122

  TCanvas *c1 = new TCanvas("c1","c1",800,800); 
  hSig->Draw();
  hSig->Fit("gaus");
  leg->Draw();
  ar->Draw();
  hSig->GetXaxis()->SetTitle("#sigma");
  hSig->GetYaxis()->SetTitle("entries");
  c1->Update();
  

  return true;
}


float getMaxSig(std::string bfitfname, std::string datafname){

  TFile *fbfit = TFile::Open(bfitfname.c_str());
  TFile *fdata = TFile::Open(datafname.c_str());
  
  Float_t BR, deltaNLL, r;
  Double_t nll, nll0;
  Float_t quantileExpected;

  TTree *t=(TTree*)fbfit->Get("limit");
  t->SetBranchAddress("BR",&BR);
  t->SetBranchAddress("deltaNLL",&deltaNLL);
  t->SetBranchAddress("nll",&nll);
  t->SetBranchAddress("nll0",&nll0);
  t->SetBranchAddress("quantileExpected",&quantileExpected);
  //std::cout << "Nofbkg : " << t->GetEntries() << std::endl;
  
  double nll_bfit = 0;
  Long_t nentries = t->GetEntries();
  for (Int_t i = 0; i<1; i++) {
    t->GetEntry(i);
    nll_bfit = nll+nll0;
  }
  //cout<<"nll_bfit="<<nll_bfit<<endl;

  t=(TTree*)fdata->Get("limit");
  t->SetBranchAddress("BR",&BR);
  t->SetBranchAddress("deltaNLL",&deltaNLL);
  t->SetBranchAddress("nll",&nll);
  t->SetBranchAddress("nll0",&nll0);
  t->SetBranchAddress("quantileExpected",&quantileExpected);
  
  nentries = t->GetEntries();
  TGraph hsignif(nentries);
  int ivalid = 0;
  double sig_max = -1, BR_max = 0;
  for (Int_t i = 0; i<nentries; i++) {
    t->GetEntry(i);
    if(quantileExpected < 0.0) continue; //some -ve quantile cases are skipped
    /////////////////////////////////
    double rel_nll = nll+nll0+deltaNLL - nll_bfit;
    if(rel_nll>0) rel_nll=0;
    double sig = sqrt(2*fabs(rel_nll));
    hsignif.Set(i+1);
    hsignif.SetPoint(i, BR, sig);
    //std::cout << "i : " << i << ", (nll+nll0+deltaNLL): " << (nll+nll0+deltaNLL) << ", nll_bfit: " << nll_bfit << ", rel_nll: " << rel_nll << ", BR : " << BR << ",  sig: " << sig << std::endl;
    ivalid++;
  }
  hsignif.Set(ivalid);
  hsignif.Sort();
  for(int i=1; i< hsignif.GetN(); i++){
    double x, y; hsignif.GetPoint(i, x, y);
    if(y>=sig_max){ sig_max=y; BR_max=x;
    }
  }
  //printf("%s\t%03d\t%5.4f\t%5.4f\t%5.4f\n",year,mass,BR_max,sig_max,ROOT::Math::normal_cdf_c(sig_max));

  fbfit->Close();
  fdata->Close();

  delete fbfit;
  delete fdata;

  return sig_max;
}
