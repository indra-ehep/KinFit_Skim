/**********************************************************************
 Created on : 13/03/2025
 Purpose    : Plot local-p values
 Author     : Indranil Das, Research Associate, Imperial
 Email      : indranil.das@cern.ch | indra.ehep@gmail.com
**********************************************************************/
#include <iostream>
#include <fstream>
#include <sstream>
#include<TGraph.h>
#include<TAxis.h>
#include<TCanvas.h>
#include<TLegend.h>
#include<TMath.h>
#include<TROOT.h>


int plot_localp(){

  int GetPoints(std::string, TGraph*);
  
  std::string fname2016, fname2017, fname2018, fnamerun2;
  
  fname2016 = "../input/local-p_2016.txt";
  fname2017 = "../input/local-p_2017.txt";
  fname2018 = "../input/local-p_2018.txt";
  fnamerun2 = "../input/local-p_run2.txt";

  TGraph *gr2016 = new TGraph(14);
  TGraph *gr2017 = new TGraph(14);
  TGraph *gr2018 = new TGraph(14);
  TGraph *grrun2 = new TGraph(14);
  TGraph *gr0sig = new TGraph(2);
  TGraph *gr1sig = new TGraph(2);
  TGraph *gr2sig = new TGraph(2);
  TGraph *gr3sig = new TGraph(2);
  TGraph *gr4sig = new TGraph(2);
  TGraph *gr5sig = new TGraph(2);

  GetPoints(fname2016, gr2016);
  GetPoints(fname2017, gr2017);
  GetPoints(fname2018, gr2018);
  GetPoints(fnamerun2, grrun2);
  
  gr0sig->SetPoint(0, 20, 0.5);
  gr0sig->SetPoint(1, 200, 0.5);
  gr1sig->SetPoint(0, 20, 0.15865525);
  gr1sig->SetPoint(1, 200, 0.15865525);
  gr2sig->SetPoint(0, 20, 0.022750132);
  gr2sig->SetPoint(1, 200, 0.022750132);
  gr3sig->SetPoint(0, 20, 0.0013498980);
  gr3sig->SetPoint(1, 200, 0.0013498980);
  gr4sig->SetPoint(0, 20, 3.1671242e-05);
  gr4sig->SetPoint(1, 200, 3.1671242e-05);
  gr5sig->SetPoint(0, 20, 2.8665157e-07);
  gr5sig->SetPoint(1, 200, 2.8665157e-07);

  gr0sig->SetLineColor(kOrange+2);
  gr1sig->SetLineColor(kOrange+2);
  gr2sig->SetLineColor(kOrange+2);
  gr3sig->SetLineColor(kOrange+2);
  gr4sig->SetLineColor(kOrange+2);
  gr5sig->SetLineColor(kOrange+2);
  

  gr0sig->SetLineStyle(2);
  gr1sig->SetLineStyle(2);
  gr2sig->SetLineStyle(2);
  gr3sig->SetLineStyle(2);
  gr4sig->SetLineStyle(2);
  gr5sig->SetLineStyle(2);
  
  gr2016->SetLineColor(kMagenta);
  gr2017->SetLineColor(kBlue);
  gr2018->SetLineColor(kBlack);
  grrun2->SetLineColor(kRed);

  gr2016->SetLineWidth(2);
  gr2017->SetLineWidth(2);
  gr2018->SetLineWidth(2);
  grrun2->SetLineWidth(3);

  TLegend* leg = new TLegend(0.65,0.68,0.93,0.88,NULL,"brNDC");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);
  leg->AddEntry(gr2016,"2016","L");
  leg->AddEntry(gr2017,"2017","L");
  leg->AddEntry(gr2018,"2018","L");
  leg->AddEntry(grrun2,"Run2","L");
  
  gr2016->SetTitle("");
  gr2016->SetMinimum(1e-7);
  gr2016->SetMaximum(1.0);
  gr2016->GetXaxis()->SetTitle("m_{H^{#pm}}");
  gr2016->GetYaxis()->SetTitle("local p-values");
  TCanvas *c1 = new TCanvas("c1","c1");
  c1->SetLogy();
  c1->SetTickx();
  c1->SetTicky();
  gr2016->Draw("ALP");
  gr2017->Draw("LP");
  gr2018->Draw("LP");
  grrun2->Draw("LP");
  gr0sig->Draw("LP");
  gr1sig->Draw("LP");
  gr2sig->Draw("LP");
  gr3sig->Draw("LP");
  gr4sig->Draw("LP");
  gr5sig->Draw("LP");
  leg->Draw();
  return true;
}

int GetPoints(std::string fname, TGraph* gr){

  ifstream fin;
  fin.open(fname);
  std::string s;
  char year[5];
  float mass, br, signifcance, localp;
  int ipoint = 0;
  while(getline(fin,s)){
    //std::cout << s << std::endl;
    std::stringstream ss(s);
    ss >> year >> mass >> br >> signifcance >> localp ;
    //std::cout << year << "\t" << mass << "\t" << br << "\t"<< signifcance << "\t" << localp << std::endl;
    gr->SetPoint(ipoint, mass, localp);
    ipoint++;
  }
  return true;
}
