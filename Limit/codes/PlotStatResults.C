/**********************************************************************
 Created on : 28/03/2023
 Purpose    : Plot the statistical results
 Author     : Indranil Das, Visiting Fellow
 Email      : indranil.das@cern.ch | indra.ehep@gmail.com
**********************************************************************/

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
#include "TF1.h"
#include "TPaveText.h"
#include "TStyle.h"
#include "TArrow.h"

using namespace std;

TPaveText * paveText(double minX, double minY, double maxX, double maxY, int lineColor, int fillColor, int size, int style, int font ){
  TPaveText *pt = new TPaveText(minX, minY, maxX, maxY, "brNDC"); // good_v1
  pt->SetBorderSize(size);
  pt->SetFillColor(fillColor);
  pt->SetFillStyle(style);
  pt->SetLineColor(lineColor);
  pt->SetTextFont(font);
  return pt;
}

int PlotStatResults(int mass = 80)
{
  //int mass = 100;
  //string indir = Form("/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/limit/local/mu_ele/Cat1_Inc/Mass%d/",mass);
  string indir = Form("/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/limit/Imperial-PA-2024-10-08/14_CR-Stat_09_exc0_unblinded_with-qcdrate-bound/Run2/Comb/mu_ele/Cat1_Inc/Mass%d/",mass);
  
  //////////////////// Pull test ////////////////////////////////////////////////
  TFile *fPull = TFile::Open((indir+"pull_result.root").c_str());
  TCanvas *postfit_dist = (TCanvas *)fPull->Get("asdf");
  // TCanvas *nuisances_dist = (TCanvas *)fPull->Get("nuisances");
  // TCanvas *postfiterr_dist = (TCanvas *)fPull->Get("post_fit_errs");
  
  // TGraphAsymmErrors *grfit_b_g = (TGraphAsymmErrors *)fPull->Get("fit_b_g");
  // TGraphAsymmErrors *grfit_b_s = (TGraphAsymmErrors *)fPull->Get("fit_b_s");
  // TH1F *hist_prefit = (TH1F *)fPull->Get("prefit_nuisancs");
  // TH1F *hist_err_b = (TH1F *)fPull->Get("errors_b");
  // TH1F *hist_err_s = (TH1F *)fPull->Get("errors_s");

  // double minX = hist_prefit->GetXaxis()->GetBinCenter(1);
  // double maxX = hist_prefit->GetXaxis()->GetBinCenter(hist_prefit->GetNbinsX());
  
  // const int nofBinsPerCanvas = 50;
  // int nofCanvases = TMath::Floor(grfit_b_g->GetN()/nofBinsPerCanvas) + 1;

  // // postfit_dist->Draw();
  // // postfit_dist->SaveAs(Form("%spostfit-dist_m%d.pdf",indir.c_str(),mass));
  // // postfit_dist->SaveAs(Form("%spostfit-dist_m%d.png",indir.c_str(),mass));


  // //nuisances_dist->Draw();
  // // postfit_dist->Draw();
  // //postfiterr_dist->Draw();

  // cout << "grfit_b_g " << grfit_b_g << endl;
  // cout << "grfit_b_s " << grfit_b_s << endl;
  // cout << "N " << grfit_b_g->GetN() << endl;

  // cout << "nofCanvases : " << nofCanvases << "," << maxX << endl;
  // gStyle->SetOptStat(0);


  // TLegend* leg = new TLegend(0.81,0.84,0.99,0.99,NULL,"brNDC");
  // leg->SetTextSize(0.04);
  // leg->SetFillColor(0);
  // leg->AddEntry(hist_prefit, "Prefit","LP");
  // leg->AddEntry(grfit_b_g, "B-only fit","LP");
  // leg->AddEntry(grfit_b_s, "S+B fit","LP");
  
  // for(int ican=1;ican<=nofCanvases;ican++){
  //   hist_prefit->GetXaxis()->SetRange(50*(ican-1)+1,50*ican);
  //   hist_prefit->SetTitle(Form("Nuisance pulls (m_{H^{#pm}} = %d GeV) : part %d",mass,ican));

  //   hist_err_b->GetXaxis()->SetRange(50*(ican-1)+1,50*ican);
  //   hist_err_b->SetTitle(Form("Uncertainty reduction (B-only fit, m_{H^{#pm}} = %d GeV) : part %d",mass,ican));

  //   hist_err_s->GetXaxis()->SetRange(50*(ican-1)+1,50*ican);
  //   hist_err_s->SetTitle(Form("Uncertainty reduction (S+B fit, m_{H^{#pm}} = %d GeV) : part %d",mass,ican));
    
  //   TGraphAsymmErrors *grfit_b_g_cl = (TGraphAsymmErrors *)grfit_b_g->Clone(Form("grfit_b_g_cl_%d",ican));
  //   TGraphAsymmErrors *grfit_b_s_cl = (TGraphAsymmErrors *)grfit_b_s->Clone(Form("grfit_b_s_cl_%d",ican));
  //   for(int i=0;i<50;i++) {
  //     grfit_b_g_cl->SetPoint(i,grfit_b_g->GetPointX(i),grfit_b_g->GetPointY(i+50*(ican-1)));
  //     grfit_b_g_cl->SetPointError(i, grfit_b_g->GetErrorXlow(i), grfit_b_g->GetErrorXhigh(i), grfit_b_g->GetErrorYlow(i+50*(ican-1)), grfit_b_g->GetErrorYhigh(i+50*(ican-1)));
  //     grfit_b_s_cl->SetPoint(i,grfit_b_s->GetPointX(i),grfit_b_s->GetPointY(i+50*(ican-1)));
  //     grfit_b_s_cl->SetPointError(i, grfit_b_s->GetErrorXlow(i), grfit_b_s->GetErrorXhigh(i), grfit_b_s->GetErrorYlow(i+50*(ican-1)), grfit_b_s->GetErrorYhigh(i+50*(ican-1)));
  //   }
    
  //   TCanvas *c1 = new TCanvas(Form("pull_c%d",ican),Form("pull_c%d",ican));
  //   c1->SetBottomMargin(0.3067227);
  //   c1->SetTickx();
  //   c1->SetTicky();
  //   hist_prefit->Draw();
  //   grfit_b_g_cl->Draw("e1p same");
  //   grfit_b_s_cl->Draw("e1p same");
  //   hist_prefit->LabelsOption("v","X");
  //   leg->Draw();
  //   c1->SaveAs(Form("%spull_c%d_m%d.pdf",indir.c_str(),ican,mass));
  //   c1->SaveAs(Form("%spull_c%d_m%d.png",indir.c_str(),ican,mass));
    
  //   hist_err_b->Draw();
  //   hist_err_b->SetMinimum(0.0);
  //   hist_err_b->SetMaximum(1.2);
  //   hist_err_b->LabelsOption("v","X");
  //   c1->SaveAs(Form("%spull_unc_b_c%d_m%d.pdf",indir.c_str(),ican,mass));
  //   c1->SaveAs(Form("%spull_unc_b_c%d_m%d.png",indir.c_str(),ican,mass));

  //   hist_err_s->Draw();
  //   hist_err_s->SetMinimum(0.0);
  //   hist_err_s->SetMaximum(1.2);
  //   hist_err_s->LabelsOption("v","X");
  //   c1->SaveAs(Form("%spull_unc_s_c%d_m%d.pdf",indir.c_str(),ican,mass));
  //   c1->SaveAs(Form("%spull_unc_s_c%d_m%d.png",indir.c_str(),ican,mass));

    
  // }

  
  TObject *obj;
  TIter next(postfit_dist->GetListOfPrimitives());
  while ((obj=next())) {
    //cout << "0:Reading: " << obj->GetName() <<" of type "<<obj->ClassName()<< endl;
    if(!strcmp(obj->GetName(),"pulls")){
        TH1 *h1 = (TH1*)obj;
	string title(h1->GetTitle());
	title += Form(" (m_{H^{#pm}} = %d GeV)",mass);
	h1->SetTitle(title.c_str());
        TCanvas *ch = new TCanvas("ch","ch");
        h1->Draw("e1");
	ch->SaveAs(Form("%spostfit-dist_m%d.pdf",indir.c_str(),mass));
	ch->SaveAs(Form("%spostfit-dist_m%d.png",indir.c_str(),mass));
    }
  }//obj loop

  ///////////////////////////////////////////////////////////////////
  // ////////////////// Parameter Scan ///////////////////////////////////
  // ifstream ftext((indir+"pararray.txt").c_str());
  // string nuisance;
  // int nofline = 0;
  // while(getline(ftext,nuisance)) nofline++;
  // cout << "NofLine : " << nofline << endl;
  // ftext.clear();
  // ftext.seekg(0);
  // int nofrows = 4;
  // int nofcols = 4;
  // int nofpads = nofrows*nofcols ;
  // int nofcanvases = TMath::Ceil(nofline/nofpads);
  // int mod = nofline%nofpads;
  // cout << "nofcanvases : " << nofcanvases << endl;
  // cout << "mod : " << mod << endl;
  // TGraph **gr;
  // gr = new TGraph*[nofline];
  // int inui = 0;
  // while(getline(ftext,nuisance)){
  //   //cout <<"Nuisance : " << nuisance << endl;
  //   TFile *fscan = TFile::Open((indir+Form("higgsCombine_scan_%s.MultiDimFit.mH%d.root",nuisance.c_str(),mass)).c_str());
  //   TTree *limit = (TTree *)fscan->Get("limit");
  //   gr[inui] = new TGraph(int(limit->GetEntries())-1);
  //   gr[inui]->SetTitle(nuisance.c_str());
  //   gr[inui]->SetMarkerStyle(kFullCircle);
  //   gr[inui]->SetMarkerSize(2.0);
  //   gr[inui]->SetLineColor(kBlue);
  //   gr[inui]->GetXaxis()->SetTitle(nuisance.c_str());
  //   gr[inui]->GetYaxis()->SetTitle("-2#Delta Log(#it{L})");
  //   gr[inui]->GetXaxis()->SetTitleSize(0.05);
  //   gr[inui]->GetYaxis()->SetTitleSize(0.05);
  //   gr[inui]->GetXaxis()->SetLabelSize(0.05);
  //   gr[inui]->GetYaxis()->SetLabelSize(0.05);
  //   gr[inui]->GetYaxis()->SetTitleOffset(0.9);

  //   Float_t xval,deltaNLL;
  //   limit->SetBranchAddress(Form("%s",nuisance.c_str()), &xval);
  //   limit->SetBranchAddress("deltaNLL", &deltaNLL);
  //   for(int ie=0;ie<limit->GetEntries();ie++){
  //     limit->GetEntry(ie);
  //     //cout <<"deltaNLL : " << deltaNLL << ", << nuisance.c_str() << " : " << xval << endl;
  //     if(ie>=1)
  // 	gr[inui]->SetPoint(ie-1, xval, deltaNLL);
  //   }
  //   delete fscan;
  //   inui++;
  // }

  // inui = 0;
  // gStyle->SetTitleW(1.0);
  // gStyle->SetTitleH(0.1);
  // for(int ic=1;ic<=nofcanvases;ic++){
  //   TCanvas *c1 = new TCanvas(Form("c%d",ic),Form("c%d",ic),4000,3000);
  //   c1->Divide(nofrows,nofcols);
  //   if(ic<nofcanvases){
  //     for(int ipad = 1; ipad<=nofpads;ipad++){
  // 	c1->cd(ipad);
  // 	c1->SetTickx();
  // 	c1->SetTicky();

  // 	gr[inui]->Draw("acp"); inui++;
  //     }
  //   }else{
  //     for(int ipad = 1; ipad<=mod;ipad++){
  // 	c1->cd(ipad);
  // 	c1->SetTickx();
  // 	c1->SetTicky();

  // 	gr[inui]->Draw("acp"); inui++;
  //     }
  //   }
  //   c1->SaveAs(Form("%sparscan_c%d_m%d.pdf",indir.c_str(),ic,mass));
  //   c1->SaveAs(Form("%sparscan_c%d_m%d.png",indir.c_str(),ic,mass));
  // }


  // // ///////////////////////////////////////////////////////////////////
  // /////////////////////////// GoF ///////////////////////////////////
  // TH1F *histData = new TH1F("histData", "histData", 50, 0., 300.);
  // TH1F *histToy = new TH1F("histToy", "histToy", 50, 0., 300.);
  // histData->SetLineColor(kRed);
  // histToy->SetLineColor(kBlue);
  // histData->SetLineWidth(2);
  // histToy->SetTitle("");
  // histToy->GetYaxis()->SetTitle("Number of Toys");
  // histToy->GetXaxis()->SetTitle("q_{GoF,saturated}");
  // histToy->GetYaxis()->SetTitleSize(0.04);
  // histToy->GetXaxis()->SetTitleSize(0.04);

  // TFile *fgof_data = TFile::Open((indir+Form("higgsCombineTest.GoodnessOfFit.mH%d.root",mass)).c_str());
  // TFile *fgof_toy = TFile::Open((indir+Form("higgsCombineTest.GoodnessOfFit.mH%d.1234.root",mass)).c_str());
  // TTree *limitD = (TTree *)fgof_data->Get("limit");
  // Double_t limit_data;
  // limitD->SetBranchAddress("limit", &limit_data);
  // for(int ie=0;ie<limitD->GetEntries();ie++){
  //   limitD->GetEntry(ie);
  //   histData->Fill(limit_data);
  // }
  // TTree *limitT = (TTree *)fgof_toy->Get("limit");
  // Double_t limit_toy;
  // limitT->SetBranchAddress("limit", &limit_toy);
  // for(int ie=0;ie<limitT->GetEntries();ie++){
  //   limitT->GetEntry(ie);
  //   histToy->Fill(limit_toy);
  // }
  // delete fgof_data;
  // delete fgof_toy;
  
  // TArrow *ar = new TArrow(histData->GetMean(),3.0,histData->GetMean(),30,0.02,"<|");
  // //TArrow *ar = new TArrow(histData->GetBinCenter(histData->GetMaximumBin()),3.0,histData->GetBinCenter(histData->GetMaximumBin()),30,0.02,"<|");
  // ar->SetLineWidth(2);
  // ar->SetLineColor(kBlack);
  // ar->SetFillColor(kOrange +7);

  // TLegend* legGoF = new TLegend(0.15,0.40,0.30,0.75,NULL,"brNDC");
  // legGoF->SetBorderSize(0);
  // legGoF->SetTextSize(0.04);
  // legGoF->SetFillColor(0);
  // TString meanToy = TString(Form("%3.1f #pm %3.1f",histToy->GetMean(),histToy->GetStdDev()));
  // TString histcount = to_string(int(histToy->GetEntries()));
  // TString legToy = "#splitline{Expected from "+histcount+" Toys}{(Mean ="+meanToy+")}";
  // legGoF->AddEntry(histToy, legToy,"L");
  // TString legData = Form("#splitline{Observed}{(%3.1f)}",histData->GetMean());
  // legGoF->AddEntry(histData,legData,"L");
  
  // TPaveText *pt = paveText(0.50,0.9254,0.82,0.9562, 0, 19, 1, 0, 132);
  // pt->SetTextSize(0.06);
  // TText *text = pt->AddText("l + jets         137.6 fb^{-1} (13 TeV) ");

  // TPaveText *cct = paveText(0.20,0.85,0.30,0.85, 0, 19, 1, 0, 132);
  // cct->SetTextSize(0.05);
  // cct->AddText(Form("m_{H^{#pm}} = %d GeV",mass));

  
  
  // // TF1 *fgaus = new TF1("fgaus","[0]*ROOT::Math::chisquared_pdf(x,[1])",0,1000);
  // // fgaus->SetParameters(histToy->GetEntries()*histToy->GetBinWidth(1), histToy->GetMean());
  // TF1 *fgaus = new TF1("fgaus","gaus",0,1000);
  // fgaus->SetParameter(1,histToy->GetMean());
  // fgaus->SetParameter(2,histToy->GetRMS());
  // fgaus->SetNpx(1000);
  // fgaus->SetLineColor(kGreen+2);
  // histToy->Fit(fgaus,"NQLR");
  // TString legchi = Form("#splitline{Gaussian pdf}{(Mean : %3.1f #pm %3.1f)}",fgaus->GetParameter(1),fgaus->GetParameter(2));
  // legGoF->AddEntry(fgaus,legchi,"L");

  // //double pvalue = histToy->Integral(histToy->FindBin(histData->GetMean()),histToy->FindBin(1000.))/histToy->Integral();
  // double pvalue = fgaus->Integral(histData->GetMean(),1000.)/fgaus->Integral(0.,1000.);
  // //double pvalue = fgaus->Integral(histData->GetBinCenter(histData->GetMaximumBin()),2000.)/fgaus->Integral(0.,2000.);
  // legGoF->AddEntry(fgaus,Form("p-value : %4.3f",pvalue),"");
  
  // gStyle->SetOptStat(0);
  // TCanvas *c1 = new TCanvas("cGoF","cGoF");
  // c1->SetTickx();
  // c1->SetTicky();
  // histToy->Draw();
  // histData->Draw("sames");
  // fgaus->Draw("same");
  // ar->Draw();
  // pt->Draw();
  // cct->Draw();
  // legGoF->Draw();
  // c1->SaveAs(Form("%sgof_m%d.png",indir.c_str(),mass));
  // c1->SaveAs(Form("%sgof_m%d.pdf",indir.c_str(),mass));

  // cout <<"Mean : " << histData->GetMean() << endl;;
  // cout <<"Total Integral : " << fgaus->Integral(0,1000.) << endl;;
  // cout <<"Integral : " << fgaus->Integral(histData->GetMean(),1000.)/fgaus->Integral(0,1000.) << endl;;
  // /////////////////////////////////////////////////////////////////////

  // /////////////////////////// GoF MC ///////////////////////////////////
  // ifstream flimit((indir+"limit.txt").c_str());
  // string sline;
  // float br[3]; char lname[3][10];
  // int id = 0;
  // while(getline(flimit,sline)){
  //   stringstream s(sline);
  //   s >> lname[id] >> br[id] ;
  //   cout << sline << endl;
  //   id++;
  // }
  // flimit.close();

  // float minRangeX = 350., maxRangeX = 700. ;
  // int nBinsX = 35;
  // //TH1F *histToy_0 = new TH1F("histToy_0", "histToy_0", 80, 0., 800.);
  // //TH1F *histToy_0 = new TH1F("histToy_0", "histToy_0", 140, 800., 2200.);
  // TH1F *histToy_0 = new TH1F("histToy_0", "histToy_0", nBinsX, minRangeX,maxRangeX);
  // histToy_0->SetLineColor(kRed);  
  // //histToy_0->SetLineWidth(2);  
  // histToy_0->SetTitle("");
  // histToy_0->GetYaxis()->SetTitle("Number of Toys");
  // histToy_0->GetXaxis()->SetTitle("q_{GoF,saturated}");
  // histToy_0->GetYaxis()->SetTitleSize(0.04);
  // histToy_0->GetXaxis()->SetTitleSize(0.04);

  // TH1F *histToy_M = (TH1F *)histToy_0->Clone("histToy_M");
  // TH1F *histToy_1 = (TH1F *)histToy_0->Clone("histToy_1");

  // histToy_1->SetLineColor(kBlue);
  // histToy_0->SetLineColor(kBlack);

  // TFile *fgof_toy_M = TFile::Open((indir+Form("higgsCombine_SRMR_M.GoodnessOfFit.mH%d.123456.root",mass)).c_str());
  // // TFile *fgof_toy_0 = TFile::Open((indir+Form("higgsCombine_SRMR_M.GoodnessOfFit.mH%d.123456.root",mass)).c_str());
  // // TFile *fgof_toy_1 = TFile::Open((indir+Form("higgsCombine_SRMR_M.GoodnessOfFit.mH%d.123456.root",mass)).c_str());
  // TFile *fgof_toy_0 = TFile::Open((indir+Form("higgsCombine_SRMR_0.GoodnessOfFit.mH%d.123456.root",mass)).c_str());
  // TFile *fgof_toy_1 = TFile::Open((indir+Form("higgsCombine_SRMR_1.GoodnessOfFit.mH%d.123456.root",mass)).c_str());
  // TTree *limit = (TTree *)fgof_toy_M->Get("limit");
  // Double_t limit_M;
  // limit->SetBranchAddress("limit", &limit_M);
  // for(int ie=0;ie<limit->GetEntries();ie++){
  //   limit->GetEntry(ie);
  //   histToy_M->Fill(limit_M);
  // }
  // limit = (TTree *)fgof_toy_0->Get("limit");
  // Double_t limit_0;
  // limit->SetBranchAddress("limit", &limit_0);
  // for(int ie=0;ie<limit->GetEntries();ie++){
  //   limit->GetEntry(ie);
  //   histToy_0->Fill(limit_0);
  // }
  // limit = (TTree *)fgof_toy_1->Get("limit");
  // Double_t limit_1;
  // limit->SetBranchAddress("limit", &limit_1);
  // for(int ie=0;ie<limit->GetEntries();ie++){
  //   limit->GetEntry(ie);
  //   histToy_1->Fill(limit_1);
  // }
  // delete fgof_toy_M;
  // delete fgof_toy_0;
  // delete fgof_toy_1;
  
  // // TArrow *ar = new TArrow(histToy_M->GetMean(),3.0,histToy_M->GetMean(),30,0.02,"<|");
  // // ar->SetLineWidth(2);
  // // ar->SetLineColor(kBlack);
  // // ar->SetFillColor(kOrange +7);
  
  // TPaveText *pt = paveText(0.4,0.9254,0.6,0.9562, 0, 19, 1, 0, 132);
  // pt->SetTextSize(0.06);
  // TText *text = pt->AddText("l + jets         137.6 fb^{-1} (13 TeV) ");
  
  // TPaveText *cct_0 = paveText(0.30, 0.78, 0.40, 0.85, 0, 19, 1, 0, 132);
  // cct_0->SetTextSize(0.05);
  // TPaveText *cct_1 = (TPaveText *) cct_0->Clone("cct_1");
  // TPaveText *cct_M = (TPaveText *) cct_0->Clone("cct_M");
  // cct_0->AddText(Form("#splitline{m_{H^{#pm}} = %d GeV}{BR_{inj} = 0}",mass));
  // if(strcmp(lname[2],"M")==0)
  //   cct_M->AddText(Form("#splitline{m_{H^{#pm}} = %d GeV}{BR_{inj} = %5.4f}",mass,br[2]));
  // else
  //   cct_M->AddText(Form("#splitline{m_{H^{#pm}} = %d GeV}{BR_{inj} = M}",mass));
  // cct_1->AddText(Form("#splitline{m_{H^{#pm}} = %d GeV}{BR_{inj} = 1}",mass));
  
  // TLegend* legGoF_0 = new TLegend(0.15,0.50,0.30,0.75,NULL,"brNDC");
  // legGoF_0->SetBorderSize(0);
  // legGoF_0->SetTextSize(0.04);
  // legGoF_0->SetFillColor(0);
  // TLegend* legGoF_M = (TLegend *)legGoF_0->Clone("legGoF_M");
  // TLegend* legGoF_1 = (TLegend *)legGoF_0->Clone("legGoF_1");
  // TString meanToy = TString(Form("%3.1f #pm %3.1f",histToy_0->GetMean(),histToy_0->GetStdDev()));
  // TString legToy = Form("#splitline{Expected from %d Toys}{(Mean = %s)}",int(histToy_0->GetEntries()),meanToy.Data());
  // legGoF_0->AddEntry(histToy_0, legToy,"L");
  // meanToy = TString(Form("%3.1f #pm %3.1f",histToy_M->GetMean(),histToy_M->GetStdDev()));
  // legToy = Form("#splitline{Expected from %d Toys}{(Mean = %s)}",int(histToy_M->GetEntries()),meanToy.Data());
  // legGoF_M->AddEntry(histToy_M, legToy,"L");
  // meanToy = TString(Form("%3.1f #pm %3.1f",histToy_1->GetMean(),histToy_1->GetStdDev()));
  // legToy = Form("#splitline{Expected from %d Toys}{(Mean = %s)}",int(histToy_1->GetEntries()),meanToy.Data());
  // legGoF_1->AddEntry(histToy_1, legToy,"L");
  
  // TF1 *fgaus_0 = new TF1("fgaus_0","gaus",minRangeX,maxRangeX);
  // fgaus_0->SetLineColor(kGreen+2);
  // fgaus_0->SetNpx(1000);
  // TF1 *fgaus_M = new TF1("fgaus_M","gaus",minRangeX,maxRangeX);
  // fgaus_M->SetLineColor(kGreen+2);
  // fgaus_M->SetNpx(1000);
  // TF1 *fgaus_1 = new TF1("fgaus_1","gaus",minRangeX,maxRangeX);
  // fgaus_1->SetLineColor(kGreen+2);
  // fgaus_1->SetNpx(1000);

  // fgaus_0->SetParameter(1,histToy_0->GetMean());
  // fgaus_0->SetParameter(2,histToy_0->GetRMS());
  // histToy_0->Fit(fgaus_0,"NQLR");
  // TString legchi = Form("#splitline{Gaussian pdf}{(Mean : %3.1f #pm %3.1f)}",fgaus_0->GetParameter(1),fgaus_0->GetParameter(2));
  // legGoF_0->AddEntry(fgaus_0,legchi,"L");

  // fgaus_M->SetParameter(1,histToy_M->GetMean());
  // fgaus_M->SetParameter(2,histToy_M->GetRMS());
  // histToy_M->Fit(fgaus_M,"NQLR");
  // legchi = Form("#splitline{Gaussian pdf}{(Mean : %3.1f #pm %3.1f)}",fgaus_M->GetParameter(1),fgaus_M->GetParameter(2));
  // legGoF_M->AddEntry(fgaus_M,legchi,"L");

  // fgaus_1->SetParameter(1,histToy_1->GetMean());
  // fgaus_1->SetParameter(2,histToy_1->GetRMS());
  // histToy_1->Fit(fgaus_1,"NQLR");
  // legchi = Form("#splitline{Gaussian pdf}{(Mean : %3.1f #pm %3.1f)}",fgaus_1->GetParameter(1),fgaus_1->GetParameter(2));
  // legGoF_1->AddEntry(fgaus_1,legchi,"L");

  // gStyle->SetOptStat(0);
  // TCanvas *cGoF_MC = new TCanvas("cGoF_MC","cGoF_MC",1800,600);
  // cGoF_MC->Divide(3,1);

  // histToy_0->SetMaximum(2.0*histToy_0->GetBinContent(histToy_0->GetMaximumBin()));
  // histToy_M->SetMaximum(2.0*histToy_M->GetBinContent(histToy_M->GetMaximumBin()));
  // histToy_1->SetMaximum(2.0*histToy_1->GetBinContent(histToy_1->GetMaximumBin()));
  
  // cGoF_MC->cd(1)->SetTickx();
  // cGoF_MC->cd(1)->SetTicky();
  // histToy_0->Draw();
  // fgaus_0->Draw("same");
  // pt->Draw();
  // cct_0->Draw();
  // legGoF_0->Draw();

  // cGoF_MC->cd(2)->SetTickx();
  // cGoF_MC->cd(2)->SetTicky();
  // histToy_M->Draw();
  // fgaus_M->Draw("same");
  // pt->Draw();
  // cct_M->Draw();
  // legGoF_M->Draw();

  // cGoF_MC->cd(3)->SetTickx();
  // cGoF_MC->cd(3)->SetTicky();
  // histToy_1->Draw();
  // fgaus_1->Draw("same");
  // pt->Draw();
  // cct_1->Draw();
  // legGoF_1->Draw();

  // cGoF_MC->SaveAs(Form("%sgof_m%d.png",indir.c_str(),mass));
  // cGoF_MC->SaveAs(Form("%sgof_m%d.pdf",indir.c_str(),mass));
  // /////////////////////////////////////////////////////////////////////

  // /////////////////////////// Bias Test ///////////////////////////////////
  
  // ifstream flimit((indir+"limit.txt").c_str());
  // string sline;
  // vector<string> lsig;
  // vector<double> brval;
  // float br[3]; char lname[3][10];
  // int id = 0;
  // while(getline(flimit,sline)){
  //   stringstream s(sline);
  //   s >> lname[id] >> br[id] ;
  //   id++;
  // }
  
  // lsig.push_back(lname[0]);
  // brval.push_back(br[0]);
  // lsig.push_back(lname[2]);
  // brval.push_back(br[2]);
  // lsig.push_back(lname[1]);
  // brval.push_back(br[1]);
  
  // for(int ival = 0; ival < 3 ; ival++){
  //   cout <<"lname "<<lsig[ival] <<", Br : " << brval[ival] << endl;
  // }
  
  // TH1F **hDiffBr, **hDiffSigBr;
  // hDiffBr = new TH1F*[brval.size()+2]; //+2 for Br = 0 and Br =1
  // hDiffSigBr = new TH1F*[brval.size()+2]; //+2 for Br = 0 and Br =1
  
  // for(int ih = 0; ih < (int(brval.size())+2) ; ih++){
  // //for(int ih = 1; ih < 2 ; ih++){
  //   string BrName, fname_extn ;
  //   Double_t BRInj;
  //   if(ih==0){
  //     fname_extn = "0";
  //     BrName = "BR_{inj} = 0";
  //     BRInj = 0.0;
  //   }else if(ih==int(brval.size()+1)){
  //     fname_extn = "1"; //actually 1
  //     BrName = "BR_{inj} = 1" ;
  //     BRInj = 1.0; //ideally 1
  //   }else{
  //     fname_extn = lsig[ih-1]; //actually 1
  //     if(fname_extn=="1sL")
  // 	BrName = "BR_{inj} = -1#sigmaCL_{s}";
  //     else if (fname_extn=="1sH")
  // 	BrName = "BR_{inj} = +1#sigmaCL_{s}";
  //     else if (fname_extn=="M")
  // 	BrName = "BR_{inj} = Median";
  //     BRInj = brval[ih-1];
  //   }
  //   cout << "ih " << ih << ", fname_extn : " << fname_extn << ", BrName : " << BrName << ", BRInj : " << BRInj << ", brval.size() : " << brval.size() << endl;
    
  //   hDiffBr[ih] = new TH1F(Form("hDiffBr_%d",ih),Form("(BR_{fit} - BR_{inj}): %s",BrName.c_str()),50,-0.1,0.1);
  //   hDiffSigBr[ih] = new TH1F(Form("hDiffSigBr_%d",ih),Form("(BR_{fit} - BR_{inj})/Br_{err}: %s",BrName.c_str()),50,-10.,10.);
  //   // hDiffBr[ih] = new TH1F(Form("hDiffBr_%d",ih),Form("(BR_{fit}): %s",BrName.c_str()),50,-0.1,0.1);
  //   // hDiffSigBr[ih] = new TH1F(Form("hDiffSigBr_%d",ih),Form("(BR_{fit})/Br_{err}: %s",BrName.c_str()),50,-10.,10.);
  //   TFile *fBT = TFile::Open((indir+Form("fitDiagnosticsBR_%s.root",fname_extn.c_str())).c_str());
    
  //   TTree *trbias = (TTree *)fBT->Get("tree_fit_sb");
  //   Int_t fit_status;
  //   Double_t BR,BRErr,BRLoErr,BRHiErr;
  //   trbias->SetBranchAddress("fit_status", &fit_status);
  //   trbias->SetBranchAddress("BR", &BR);
  //   trbias->SetBranchAddress("BRErr", &BRErr);
  //   trbias->SetBranchAddress("BRLoErr", &BRLoErr);
  //   trbias->SetBranchAddress("BRHiErr", &BRHiErr);

  //   ///////// Dangerous ////////////
  //   //BRInj = 0.0;
  //   ///////// Dangerous ////////////

  //   int nofconv = 0;
  //   // cout << "Nof Events : " << trbias->GetEntries() << endl;
  //   for(int ie=0;ie<trbias->GetEntries();ie++){
  //     trbias->GetEntry(ie);
  //     // cout << "ie : " << ie << ", fit_status : " << fit_status << endl;
  //     //if(fit_status==0){
  //     hDiffBr[ih]->Fill(BR-BRInj);
  //     double err = BRHiErr*(BR-BRInj<0)+BRLoErr*(BR-BRInj>0);
  //     double fillVal = (BR-BRInj)/err;
  //     // cout <<"BR :" << BR << ", BRInj : " << BRInj << ", (BR-BRInj>0) : " << (BR-BRInj>0) << ", (BR-BRInj<0) " << (BR-BRInj<0) 
  //     //      <<", (LErr,HErr) : (" << BRLoErr <<", " << BRHiErr << ") " 
  //     //      <<", err : " << err << ", fillVal : " << fillVal
  //     //      << endl;
  //     if(!TMath::AreEqualAbs(err,0.0,1.e-5))
  // 	hDiffSigBr[ih]->Fill(fillVal);
  //     nofconv++;
  //     //}
  //   }
  //   delete fBT;
  // }

  // TF1 *fn = new TF1("fn","gaus",hDiffSigBr[0]->GetMean()-2*hDiffSigBr[0]->GetRMS(),hDiffSigBr[0]->GetMean()+2*hDiffSigBr[0]->GetRMS());
  // fn->SetParameter(1,hDiffSigBr[0]->GetMean());
  // fn->SetParameter(2,hDiffSigBr[0]->GetRMS());
  // fn->SetNpx(1000);
  
  // gStyle->SetOptStat(0); 
  // gStyle->SetOptFit(0);

  // TCanvas *cDiff = new TCanvas("cDiff","cDiff",1200,800);
  // cDiff->Divide(2,2);
  // for(int ih = 0; ih < (int(brval.size())+2) ; ih++){
  // //for(int ih = 0; ih < 1 ; ih++){
  //   string BrName, fname_extn ;
  //   Double_t BRInj;
  //   if(ih==0){
  //     // fname_extn = "0";
  //     BrName = "BR_{inj} = 0";
  //     // BRInj = 0.0;
  //   }else if(ih==int(brval.size()+1)){
  //     // fname_extn = "1"; //actually 1
  //     BrName = "BR_{inj} = 1" ;
  //     // BRInj = 1.0; //ideally 1
  //   }else{
  //     // fname_extn = lsig[ih-1]; //actually 1
  //     if(fname_extn=="1sL")
  // 	BrName = "BR_{inj} = -1#sigmaCL_{s}";
  //     else if (fname_extn=="1sH")
  // 	BrName = "BR_{inj} = +1#sigmaCL_{s}";
  //     else if (fname_extn=="M")
  // 	BrName = "BR_{inj} = Median";
  //     // BRInj = brval[ih-1];
  //   }
    
  //   cDiff->cd(ih+1);
  //   cDiff->cd(ih+1)->SetTickx();
  //   cDiff->cd(ih+1)->SetTicky();
  //   hDiffBr[ih]->Draw();
  //   hDiffBr[ih]->GetXaxis()->SetTitle("(BR_{fit} - BR_{inj})");
  //   //hDiffBr[ih]->GetXaxis()->SetTitle("(BR_{fit})");
  //   hDiffBr[ih]->GetYaxis()->SetTitle("Entries/bin");
  //   hDiffBr[ih]->GetXaxis()->SetTitleOffset(1.2);
  //   hDiffBr[ih]->GetYaxis()->SetTitleOffset(1.4);
  //   hDiffBr[ih]->SetMaximum(1.2*hDiffBr[ih]->GetBinContent(hDiffBr[ih]->GetMaximumBin()));
    
  //   TLegend* legDiff = new TLegend(0.15,0.50,0.30,0.85,NULL,"brNDC");
  //   legDiff->SetBorderSize(0);
  //   legDiff->SetTextSize(0.04);
  //   legDiff->SetFillColor(0);
  //   legDiff->AddEntry(hDiffBr[ih], Form("m_{H^{#pm}} = %d GeV",mass),"");
  //   legDiff->AddEntry(hDiffBr[ih], Form("nToys : %d",int(hDiffBr[ih]->GetEntries())),"");
  //   legDiff->AddEntry(hDiffBr[ih], Form("%s",BrName.c_str()),"L");
  //   legDiff->AddEntry(hDiffBr[ih], Form("%s",Form("Mean : %3.2e",hDiffBr[ih]->GetMean())),"L");
  //   legDiff->AddEntry(hDiffBr[ih], Form("%s",Form("RMS : %3.2e",hDiffBr[ih]->GetRMS())),"L");
  //   legDiff->DrawClone();

  // }
  
  // TCanvas *cBias = new TCanvas("cBias","cBias",1200,800);
  // cBias->Divide(2,2);
  // for(int ih = 0; ih < (int(brval.size())+1) ; ih++){
  // //for(int ih = 0; ih < 1 ; ih++){
  //   string BrName, fname_extn ;
  //   Double_t BRInj;
  //   if(ih==0){
  //     // fname_extn = "0";
  //     BrName = "BR_{inj} = 0";
  //     // BRInj = 0.0;
  //   }else if(ih==int(brval.size()+1)){
  //     // fname_extn = "1"; //actually 1
  //     BrName = "BR_{inj} = 1" ;
  //     // BRInj = 1.0; //ideally 1
  //   }else{
  //     // fname_extn = lsig[ih-1]; //actually 1
  //     if(fname_extn=="1sL")
  // 	BrName = "BR_{inj} = -1#sigmaCL_{s}";
  //     else if (fname_extn=="1sH")
  // 	BrName = "BR_{inj} = +1#sigmaCL_{s}";
  //     else if (fname_extn=="M")
  // 	BrName = "BR_{inj} = Median";
  //     // BRInj = brval[ih-1];
  //   }
    
    
  //   //cout <<"ih " << ih << ", hist " << hDiffSigBr[ih] <<endl;
  //   cBias->cd(ih+1);
  //   cBias->cd(ih+1)->SetTickx();
  //   cBias->cd(ih+1)->SetTicky();
  //   hDiffSigBr[ih]->Draw();
  //   fn->SetParameter(1,hDiffSigBr[ih]->GetMean());
  //   fn->SetParameter(2,hDiffSigBr[ih]->GetRMS());
  //   fn->SetRange(hDiffSigBr[ih]->GetMean()-2*hDiffSigBr[ih]->GetRMS(),hDiffSigBr[ih]->GetMean()+2*hDiffSigBr[ih]->GetRMS());
  //   hDiffSigBr[ih]->Fit(fn,"NQLR");
  //   //cout <<" Mean " << fn->GetParameter(1)  << ", width : " <<fn->GetParameter(2) << endl;
  //   fn->SetRange(hDiffSigBr[ih]->GetMean()-5*hDiffSigBr[ih]->GetRMS(),hDiffSigBr[ih]->GetMean()+5*hDiffSigBr[ih]->GetRMS());
  //   //hDiffSigBr[ih]->Draw("hist sames");
  //   fn->DrawClone("same");
  //   hDiffSigBr[ih]->GetXaxis()->SetTitle("(BR_{fit} - BR_{inj})/Br_{err}");
  //   //hDiffSigBr[ih]->GetXaxis()->SetTitle("(BR_{fit})/Br_{err}");
  //   hDiffSigBr[ih]->GetYaxis()->SetTitle("Entries/bin");
  //   hDiffSigBr[ih]->GetXaxis()->SetTitleOffset(1.2);
  //   hDiffSigBr[ih]->GetYaxis()->SetTitleOffset(1.4);
  //   hDiffSigBr[ih]->SetMaximum(1.5*hDiffSigBr[ih]->GetBinContent(hDiffSigBr[ih]->GetMaximumBin()));
    
  //   TLegend* legBias = new TLegend(0.15,0.50,0.30,0.85,NULL,"brNDC");
  //   legBias->SetBorderSize(0);
  //   legBias->SetTextSize(0.04);
  //   legBias->SetFillColor(0);
  //   legBias->AddEntry(hDiffSigBr[ih], Form("m_{H^{#pm}} = %d GeV",mass),"");
  //   legBias->AddEntry(hDiffSigBr[ih], Form("nToys : %d",int(hDiffSigBr[ih]->GetEntries())),"");
  //   legBias->AddEntry(hDiffSigBr[ih], Form("%s",BrName.c_str()),"L");
  //   legBias->AddEntry(fn, fn->GetTitle(),"L");
  //   legBias->AddEntry(fn, Form("mean : %4.3f",fn->GetParameter(1)),"L");
  //   legBias->AddEntry(fn, Form("#sigma : %4.3f",fn->GetParameter(2)),"L");
  //   legBias->DrawClone();

  // }
  // // cDiff->SaveAs(Form("%sdiff_no-subtraction_m%d.png",indir.c_str(),mass));
  // // cDiff->SaveAs(Form("%sdiff_no-subtraction_m%d.pdf",indir.c_str(),mass));

  // // cBias->SaveAs(Form("%sbias_no-subtraction_m%d.png",indir.c_str(),mass));
  // // cBias->SaveAs(Form("%sbias_no-subtraction_m%d.pdf",indir.c_str(),mass));

  // cDiff->SaveAs(Form("%sdiff_m%d.png",indir.c_str(),mass));
  // cDiff->SaveAs(Form("%sdiff_m%d.pdf",indir.c_str(),mass));

  // cBias->SaveAs(Form("%sbias_m%d.png",indir.c_str(),mass));
  // cBias->SaveAs(Form("%sbias_m%d.pdf",indir.c_str(),mass));
  
  // lsig.clear();
  // brval.clear();
 
  return true;
}
