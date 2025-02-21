#include <cstdlib>
#include <iostream> 
#include <iomanip> 
#include <fstream>
#include <map>
#include <string>
#include <cstring>

#include "TMath.h"
#include "TFile.h"
#include "TString.h"
#include "TObjString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TPluginManager.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TLegend.h"
#include "TGraphAsymmErrors.h"
#include "TGraphPainter.h"
#include "TMultiGraph.h"
#include "TTree.h"
#include "TStyle.h"
#include "TPaveText.h"

using namespace std;

vector<string> dummy;
int LimitPlotter(TString year_dir = "", vector<string>& Val=dummy, TString CHANNEL="mu", TString CAT= "Cat1_Inc",
		  bool obs= false, bool isOut= true)
{

  gStyle->SetFrameLineWidth(0);
  TCanvas *c1 = new TCanvas();
  c1->SetCanvasSize(775,775);
  c1->SetWindowSize(800,800);
  c1->Update();
  gPad->SetLogy();
  c1->SetGrid(0,0);
  c1->SetFillStyle(4000);
  c1->SetFillColor(10);
  c1->SetTickx();
  c1->SetTicky();
  c1->SetObjectStat(0);

  TLegend* leg = new TLegend(0.65,0.68,0.93,0.88,NULL,"brNDC");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.026);
  leg->SetFillColor(0);

  float X[]        = {40, 50, 60, 70, 80, 90, 100,110, 120, 130, 140, 150, 155, 160};
  float obsY[]     = {0., 0.,0.,0, 0., 0.,0.,0, 0, 0, 0, 0, 0, 0, 0};
  float expY[]     = {0., 0.,0.,0, 0., 0.,0.,0, 0, 0, 0, 0, 0, 0, 0};
		      
  float expX1sL[]   = {0., 0.,0.,0, 0., 0.,0.,0, 0, 0, 0, 0, 0, 0, 0};
  float expX1sH[]   = {0., 0.,0.,0, 0., 0.,0.,0, 0, 0, 0, 0, 0, 0, 0};
  float expY1sL[]   = {0., 0.,0.,0, 0., 0.,0.,0, 0, 0, 0, 0, 0, 0, 0};
  float expY1sH[]   = {0., 0.,0.,0, 0., 0.,0.,0, 0, 0, 0, 0, 0, 0, 0};
  float expY1sL_[]  = {0., 0.,0.,0, 0., 0.,0.,0, 0, 0, 0, 0, 0, 0, 0};
  float expY1sH_[]  = {0., 0.,0.,0, 0., 0.,0.,0, 0, 0, 0, 0, 0, 0, 0};

		      
  float expX2sL[]  = {0., 0.,0.,0, 0., 0.,0.,0, 0, 0, 0, 0, 0, 0, 0};
  float expX2sH[]  = {0., 0.,0.,0, 0., 0.,0.,0, 0, 0, 0, 0, 0, 0, 0};
  float expY2sL[]  = {0., 0.,0.,0, 0., 0.,0.,0, 0, 0, 0, 0, 0, 0, 0};
  float expY2sH[]  = {0., 0.,0.,0, 0., 0.,0.,0, 0, 0, 0, 0, 0, 0, 0};

  const int nMassPoints = 14;
  TString ch_hist = CHANNEL+"_"+CAT;
  TString massFiles [nMassPoints] = {
    "Mass40/higgsCombine_hcs_13TeV_"+ch_hist+".AsymptoticLimits.mH40.12543.root",
    "Mass50/higgsCombine_hcs_13TeV_"+ch_hist+".AsymptoticLimits.mH50.12543.root",
    "Mass60/higgsCombine_hcs_13TeV_"+ch_hist+".AsymptoticLimits.mH60.12543.root",
    "Mass70/higgsCombine_hcs_13TeV_"+ch_hist+".AsymptoticLimits.mH70.12543.root",
    "Mass80/higgsCombine_hcs_13TeV_"+ch_hist+".AsymptoticLimits.mH80.12543.root",
    "Mass90/higgsCombine_hcs_13TeV_"+ch_hist+".AsymptoticLimits.mH90.12543.root",
    "Mass100/higgsCombine_hcs_13TeV_"+ch_hist+".AsymptoticLimits.mH100.12543.root",
    "Mass110/higgsCombine_hcs_13TeV_"+ch_hist+".AsymptoticLimits.mH110.12543.root",
    "Mass120/higgsCombine_hcs_13TeV_"+ch_hist+".AsymptoticLimits.mH120.12543.root",
    "Mass130/higgsCombine_hcs_13TeV_"+ch_hist+".AsymptoticLimits.mH130.12543.root",
    "Mass140/higgsCombine_hcs_13TeV_"+ch_hist+".AsymptoticLimits.mH140.12543.root",
    "Mass150/higgsCombine_hcs_13TeV_"+ch_hist+".AsymptoticLimits.mH150.12543.root",
    "Mass155/higgsCombine_hcs_13TeV_"+ch_hist+".AsymptoticLimits.mH155.12543.root",
    "Mass160/higgsCombine_hcs_13TeV_"+ch_hist+".AsymptoticLimits.mH160.12543.root"};
  //   "higgsCombineTest.AsymptoticLimits.mH40.root",
  //   "higgsCombineTest.AsymptoticLimits.mH50.root",
  //   "higgsCombineTest.AsymptoticLimits.mH60.root",
  //   "higgsCombineTest.AsymptoticLimits.mH70.root",
  //   "higgsCombineTest.AsymptoticLimits.mH80.root",
  //   "higgsCombineTest.AsymptoticLimits.mH90.root",
  //   "higgsCombineTest.AsymptoticLimits.mH100.root",
  //   "higgsCombineTest.AsymptoticLimits.mH110.root",
  //   "higgsCombineTest.AsymptoticLimits.mH120.root",
  //   "higgsCombineTest.AsymptoticLimits.mH130.root",
  //   "higgsCombineTest.AsymptoticLimits.mH140.root",
  //   "higgsCombineTest.AsymptoticLimits.mH150.root",
  //   "higgsCombineTest.AsymptoticLimits.mH155.root",
  //   "higgsCombineTest.AsymptoticLimits.mH160.root"
  // };
  
  double maxY = 1.0;  
  for(int i = 0 ; i < nMassPoints; i++){
    //TFile f("local/"+year_dir+CHANNEL+"/"+CAT+"/"+massFiles[i],"READ");
    TFile f(year_dir+CHANNEL+"/"+CAT+"/"+massFiles[i],"READ");
    //TFile f(year_dir+CHANNEL+"/"+massFiles[i],"READ");
    //TFile f(year_dir+"/"+massFiles[i],"READ"); 
    if(f.IsZombie()){
      cout << "Cannot open file "<< f.GetName() <<" for " << string(CHANNEL.Data()) << " and mass " << X[i] << endl;
      continue;
    }
    //cout << "Opened file : " << f.GetName() << endl;
    Double_t r;
    TTree* limit = (TTree*)f.Get("limit");
    limit->SetBranchAddress("limit",&r);
    for(int k = 0 ; k< limit->GetEntries() ; k++){
      limit->GetEntry(k);
      // if(k==0) expY2sL[i] = r;
      // if(k==1) expY1sL[i] = r;
      // if(k==1) expY1sL_[i] = r;
      // if(k==2) expY[i]    = r;
      // if(k==3) expY1sH[i] = r;
      // if(k==3) expY1sH_[i] = r;
      // if(k==4) expY2sH[i] = r;
      // if(k==5) obsY[i]    = r;
      if(k==0) expY2sL[i] = 100.*r;
      if(k==1) expY1sL[i] = 100.*r;
      if(k==1) expY1sL_[i] = 100.*r;
      if(k==2) expY[i]    = 100.*r;
      if(k==3) expY1sH[i] = 100.*r;
      if(k==3) expY1sH_[i] = 100.*r;
      if(k==4) expY2sH[i] = 100.*r;
      if(k==5) obsY[i]    = 100.*r;
    }
    //if(massFiles[i].Contains("80")) maxY = expY2sH[i];
    if(massFiles[i].Contains("80")) maxY = 0.38;
  }

  
  // for(int i = 0 ; i < nMassPoints; i++){
  //   cout << "obsY[i] " << obsY[i] << endl;
  // }
  //cout<<std::setprecision(4)<<endl;
  // cout<<"Mass:"<<setw(15)<<"base value"<<setw(15)<<"-2 #sigma"<<setw(15)<<"-1 #sigma"<<setw(15)<<"+1 #sigma"<<setw(15)<<"+2 #sigma"<<endl; 
  for(int i1 = 0 ; i1 < nMassPoints ; i1++){
    //cout<<X[i1]<<setw(15)<<expY[i1]<<setw(15)<<expY2sL[i1]<<setw(15)<< expY1sL[i1]<<setw(15)<<expY1sH[i1]<<setw(15)<<expY2sH[i1]<<endl; 
    expY1sH[i1] = TMath::Abs(expY1sH[i1]-expY[i1]);
    expY1sL[i1] = TMath::Abs(expY1sL[i1]-expY[i1]);
    expY2sH[i1] = TMath::Abs(expY2sH[i1]-expY[i1]);
    expY2sL[i1] = TMath::Abs(expY2sL[i1]-expY[i1]);
  //cout<<setw(10)<<X[i1]<<setw(15)<<expY[i1]<<setw(15)<<expY2sL[i1]<<setw(15)<< expY1sL[i1]<<setw(15)<<expY1sH[i1]<<setw(15)<<expY2sH[i1]<<endl; 
  }
  FILE *fout = fopen(Form("/tmp/nano_def_%s.txt",CHANNEL.Data()),"w");
  for(int i1 = 0 ; i1 < nMassPoints ; i1++){
    expY1sH_[i1] = TMath::Abs(expY1sH_[i1]-expY[i1]);
    expY1sL_[i1] = TMath::Abs(expY1sL_[i1]-expY[i1]);
    // cout<<"$"<<std::setprecision(2)<<100*expY[i1]<<"^{+"<<expY1sH_[i1]<<"}"<<"_"<<"{-"<< expY1sL_[i1]<<"}"<<"$"<<endl;
    //printf("& $%3.2f^{+%3.2f}_{-%3.2f}$\n",expY[i1],expY1sH_[i1],expY1sL_[i1]);
    if(obs){
      //printf("& $%3.2f^{+%3.2f}_{-%3.2f}$ & $%3.2f$",expY[i1],expY1sH_[i1],expY1sL_[i1], obsY[i1]);
      fprintf(fout,"& $%3.2f^{+%3.2f}_{-%3.2f}$ & $%3.2f$\n",expY[i1],expY1sH_[i1],expY1sL_[i1], obsY[i1]);
      string res = Form("& $%3.2f^{+%3.2f}_{-%3.2f}$ & $%3.2f$",expY[i1],expY1sH_[i1],expY1sL_[i1], obsY[i1]);
      Val.push_back(res);
    }else{
      //printf("& $%3.2f^{+%3.2f}_{-%3.2f}$ ",expY[i1],expY1sH_[i1],expY1sL_[i1]);
      fprintf(fout,"& $%3.2f^{+%3.2f}_{-%3.2f}$ \n",expY[i1],expY1sH_[i1],expY1sL_[i1]);
      string res = Form("& $%3.2f^{+%3.2f}_{-%3.2f}$ ",expY[i1],expY1sH_[i1],expY1sL_[i1]);
      Val.push_back(res);
    }
    //cout<<endl;
  }
  fclose(fout);

  TMultiGraph *mg = new TMultiGraph();
  TString ch_name = "ch";
  //cout<<CHANNEL<<endl;
  if(CHANNEL=="mu" or CHANNEL=="muon") ch_name = "#mu";
  if(CHANNEL=="ele") ch_name = "e";
  if(CHANNEL=="mu_ele" or CHANNEL=="lep") ch_name = "lep";
  //mg->SetMaximum(1.02*maxY);
  mg->SetMaximum(50.);
  mg->SetMinimum(0.06);
  
  TGraphAsymmErrors* expected = new TGraphAsymmErrors(nMassPoints, X, expY, expX1sL ,expX1sL , expX1sL, expX1sL);
  TGraphAsymmErrors* oneSigma = new TGraphAsymmErrors(nMassPoints, X, expY, expX1sL, expX1sL,  expY1sL, expY1sH);
  TGraphAsymmErrors* twoSigma = new TGraphAsymmErrors(nMassPoints, X, expY, expX2sL, expX2sL,  expY2sL, expY2sH);
  TGraphAsymmErrors* observed = new TGraphAsymmErrors(nMassPoints, X, obsY, expX1sL ,expX1sL , expX1sL, expX1sL);
 
  //oneSigma->SetMarkerColor(kBlack);
  //oneSigma->SetMarkerStyle(kFullCircle);
  oneSigma->SetFillColor(kGreen+1);
  oneSigma->SetFillStyle(1001);

  //twoSigma->SetMarkerColor(kBlack);
  //twoSigma->SetMarkerStyle(kFullCircle);
  //twoSigma->SetFillColor(kYellow);
  twoSigma->SetFillColor(kOrange-2);
  twoSigma->SetFillStyle(1001);

  //expected->SetMarkerColor(kBlack);
  //expected->SetMarkerStyle(kFullCircle);
  //expected->SetMarkerSize(0.0);
  expected->SetLineColor(kBlue);
  expected->SetLineWidth(3);
  expected->SetLineStyle(2);
  
  observed->SetMarkerColor(kBlack);
  observed->SetMarkerStyle(20);
  observed->SetLineColor(kBlack);
  observed->SetLineStyle(1);
  observed->SetLineWidth(4);

  mg->Add(twoSigma,"3");
  mg->Add(oneSigma,"3");
  mg->Add(expected);
  mg->Draw("AL");

  if(obs) mg->Add(observed);

  gPad->Modified();
  gPad->SetBottomMargin(0.18);
  gPad->SetLeftMargin(0.18);
  //gPad->SetGridy();
  gPad->SetRightMargin(0.05);
  gStyle->SetFrameLineWidth(3);
  mg->GetXaxis()->SetLimits(35,165);
  mg->GetYaxis()->SetTitleOffset(1.40);
  mg->GetYaxis()->SetMoreLogLabels();
  mg->GetYaxis()->SetNdivisions(6);
  mg->GetXaxis()->SetTitleOffset(1.00);
  mg->SetMinimum(0.02);
  mg->SetMaximum(30.0);
  mg->GetXaxis()->SetTitle("m_{H^{#pm}} (GeV)");
  mg->GetYaxis()->SetTitle("B(t #rightarrow H^{#pm}b) (%)"); 
  mg->GetYaxis()->SetTitleSize(0.04);   
  mg->GetXaxis()->SetTitleSize(0.04);
  mg->GetXaxis()->SetLabelSize(0.04);   
  mg->GetYaxis()->SetLabelSize(0.04);   
  //mg->GetXaxis()->SetTickLength(0.07);
  mg->GetYaxis()->SetTickLength(0.04);

  //leg->SetHeader(Form("#splitline{CMS Preliminary #sqrt{s}=13 TeV}{ LUMI fb^{-1}, %s}",CHANNEL.Data()));

  leg->SetHeader("95% CL upper limits");
  leg->AddEntry(expected,"Median Expected","L");
  if(obs) leg->AddEntry(observed,"Observed","LP");
  leg->AddEntry(oneSigma, "68% expected","F");
  leg->AddEntry(twoSigma, "95% expected","F");
  leg->Draw();
  
  TPaveText *pl2 = new TPaveText(0.22,0.79,0.57,0.87, "brNDC");
  pl2->SetTextSize(0.026);
  pl2->SetFillColor(0);
  pl2->SetBorderSize(0);
  pl2->SetTextAlign(11);
  pl2->AddText("t #rightarrow H^{#pm}b, H^{#pm}#rightarrow cs");
  pl2->AddText("B(H^{#pm}#rightarrow cs) = 100%");
  
  double totLumi = 137.1; //2016
  if(year_dir.Contains("Run2"))
    totLumi = 138; //run2
  if(year_dir.Contains("2016"))
    totLumi = 36.3; // 2016
  if(year_dir.Contains("2017"))
    totLumi = 41.5; // 2017
  if(year_dir.Contains("2018"))
    totLumi = 59.8; //2018
  
  //pave text CMS box
  TPaveText *pt = new TPaveText(0.5,0.9354,0.95,0.9362, "brNDC"); // good_v1
  pt->SetBorderSize(1);
  pt->SetTextSize(0.035);
  pt->SetLineColor(0);
  pt->SetFillColor(0);
  pt->SetTextFont(42);
  TText *text = 0x0;
  if(year_dir.Contains("Run2"))
    text = pt->AddText(Form("%3.0f fb^{-1} (13 TeV)",totLumi));
  else
    text = pt->AddText(Form("%3.1f fb^{-1} (13 TeV)",totLumi));
  //TText *text = pt->AddText(dir+":  CMS Preliminary,    #sqrt{s} = 13 TeV,    35.45 fb^{-1}; ");
  //text->SetTextAlign(11); //left aligned
  text->SetTextAlign(32); //left aligned

  TPaveText *pt1 = new TPaveText(0.2,0.93,0.5,0.94, "brNDC"); // good_v1
  pt1->SetBorderSize(1);
  pt1->SetTextSize(0.035);
  pt1->SetLineColor(0);
  pt1->SetFillColor(0);
  //pt1->SetTextFont(42);
  //TText *text1 = pt1->AddText("CMS Preliminary");
  TText *text1 = pt1->AddText("CMS Preliminary");
  text1->SetTextAlign(12); //left aligned
  //text1->SetTextAlign(32); //left aligned

  //pave text channel box
  TPaveText *ch = new TPaveText(0.63,0.61,0.88,0.67,"brNDC");
  ch->SetFillStyle(0);
  ch->SetLineColor(0);
  ch->SetTextSize(0.026);
  ch->SetBorderSize(0);
  if(CHANNEL=="mu"  or CHANNEL=="muon")ch->AddText("#mu + jets");
  if(CHANNEL=="ele") ch->AddText("#it{e} + jets");
  if(CHANNEL=="mu_ele" or CHANNEL=="lep") ch->AddText("#it{l} + jets");
  pl2->Draw("SAME");
  pt->Draw("SAME");
  pt1->Draw("SAME");
  ch->Draw("SAME");
  leg->Draw("SAME");
  

  // TF1 *line = new TF1("line","1",100,150);
  // line->SetLineColor(kRed);
  // line->SetLineWidth(2);
  // line->Draw("SAME");

  gPad->RedrawAxis();
  //TString outFile = "limit_"+CHANNEL+"_"+CAT;
  TString outFile = CHANNEL;
  //TString outDir = "local/"+CHANNEL+"/"+CAT;
  //TString outDir = year_dir+CHANNEL+"/"+CAT;
  TString outDir = year_dir;
  gPad->SaveAs(outDir+"/"+outFile+".pdf");
  //gPad->SaveAs("result.pdf");
  if(isOut){
    TFile *fout = new TFile(outDir+"/"+outFile+".root", "RECREATE");
    //TFile *fout = new TFile("result.root", "RECREATE");
    expected->Write("expected");
    observed->Write("observed");
    oneSigma->Write("oneSigma");
    twoSigma->Write("twoSigma");
    fout->Close();
  }
  return true;
}

int LoopLimitPlotsNano(TString year_dir = "/home/hep/idas/CMS-Analysis/NanoAOD-Analysis/SkimAna/lx04_impact-data/local/mu_ele_Run2_impact_qcdrange50_qcddd6_bc3_uncorr_brpm2_x0p02_5GeV_iter130/local/"){
//int LoopLimitPlotsNano(TString year_dir = "/home/hep/idas/CMS-Analysis/NanoAOD-Analysis/SkimAna/lx04_impact-data/local/mu_ele_Run2_impact_qcdrange50_qcddd6_bc3_uncorr_brpm2_x0p02_10GeV_iter128/local/"){
//int LoopLimitPlotsNano(TString year_dir = "Imperial-PA-2024-10-08/38_unblinded_MVA_lnNfixed_qcdddfulluncorr_symm_10GeVbin/Run2/Comb/"){
//int LoopLimitPlotsNano(TString year_dir = "savarghe/HplusDatacardsNew/FullRun2/"){
  
  vector<string> muVal, eleVal, mueleVal;
  float X[]        = {40, 50, 60, 70, 80, 90, 100,110, 120, 130, 140, 150, 155, 160};

  //CBA
  LimitPlotter(year_dir, muVal, "mu", "Cat1_Inc", false, true );
  LimitPlotter(year_dir, eleVal, "ele", "Cat1_Inc", false, true );
  LimitPlotter(year_dir, mueleVal, "mu_ele", "Cat1_Inc", false, true );
  // //for MVA
  // LimitPlotter(year_dir, muVal, "muon", "", false, true );
  // LimitPlotter(year_dir, eleVal, "ele", "", false, true );
  // LimitPlotter(year_dir, mueleVal, "lep", "", false, true );
  
  string table_name = "";
  if(year_dir.Contains("Exc")){
    if(year_dir.Contains("ExcL"))
      table_name = "Loose WP";
    else if(year_dir.Contains("ExcM"))
      table_name = "Medium WP";
    else if(year_dir.Contains("ExcT"))
      table_name = "Tight WP";
  }else{
    TObjArray *array = year_dir.Tokenize("/");
    cout << "array->GetEntriesFast() : " << array->GetEntriesFast() << endl;
    TString str = ((TObjString *) array->At(array->GetEntriesFast()-2))->GetString();
    table_name = str.Data();
  }
  ofstream fout;
  fout.open(Form("%s/limit.tex",year_dir.Data()));
  fout<<"\\begin{tabular}{ | c | c | c | c | }\\hline"<<endl;
  fout<<"\\multicolumn{4}{|c|}{"<< table_name <<"}\\\\\\hline"<<endl;
  fout<<"mass point     & $\\mu$ + jets  & $e$ + jets  & $l$ + jets  \\\\ \\cline{2-4}"<<endl;
  fout<<"&  expected      & expected     & expected      \\\\ \\hline"<<endl;
  for(int i = 0; i < int(muVal.size()) ; i++){
    if(i==(int(muVal.size())-1)){
      cout << "$m_{H^{\\pm}}$ = "<< X[i] <<" GeV " << muVal[i] << " " << eleVal[i] << " " << mueleVal[i] << "\\\\\\hline" << endl;
      fout << "$m_{H^{\\pm}}$ = "<< X[i] <<" GeV " << muVal[i] << " " << eleVal[i] << " " << mueleVal[i] << "\\\\\\hline" << endl;
    }else{
      cout << "$m_{H^{\\pm}}$ = "<< X[i] <<" GeV " << muVal[i] << " " << eleVal[i] << " " << mueleVal[i] << "\\\\" << endl;
      fout << "$m_{H^{\\pm}}$ = "<< X[i] <<" GeV " << muVal[i] << " " << eleVal[i] << " " << mueleVal[i] << "\\\\" << endl;
    }
  }
  fout<<"\\end{tabular}"<<endl;
  fout.close();

  return true;
}
