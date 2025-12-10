#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include "TH1F.h"
#include "TFile.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TMath.h"
#include <sys/stat.h>
#include <stdlib.h>
#include <algorithm>
#include <iterator>
#include "TPad.h"
#include "TLatex.h"
#include "TLine.h"
#include "TBox.h"
#include "TASImage.h"
#include "TGraphAsymmErrors.h"
#include "THStack.h"
#include "TPaveText.h"
#include "TGaxis.h"
#include "TFrame.h"
#include "TF1.h"


using namespace std;

//SAVE HISTOS ON DISK
bool isSaveHisto = true;
bool isData = true;
int iPeriod = 4;
int iPosX = 10;
double xMin = 1;
double xMax = 30;
double yMin = 0.4;
double yMax = 1.6;


//-----------------------
// CMS guidelines for fig
// https://twiki.cern.ch/twiki/bin/view/CMS/Internal/FigGuidelines
//-----------------------
TString cmsText     = "CMS";
float cmsTextFont   = 61;  // default is helvetic-bold
bool writeExtraText = true;
TString extraText   = "Preliminary";
float extraTextFont = 52;  // default is helvetica-italics
// text sizes and text offsets with respect to the top frame
// in unit of the top margin size
float lumiTextSize     = 0.6;
float lumiTextOffset   = 0.2;
float cmsTextSize      = 0.75;
float cmsTextOffset    = 0.1;  // only used in outOfFrame version
float relPosX    = 0.045;
float relPosY    = 0.035;
float relExtraDY = 1.2;
// ratio of "CMS" and extra text size
float extraOverCmsTextSize  = 0.76;
TString lumi_13TeV = "59.8 fb^{-1}";
TString lumi_13TeV_2016 = "36.3 fb^{-1}";
TString lumi_13TeV_2017 = "41.5 fb^{-1}";
TString lumi_13TeV_2018 = "59.8 fb^{-1}";
TString lumi_13TeV_run2 = "138 fb^{-1}";

TString lumi_8TeV  = "19.7 fb^{-1}";
TString lumi_7TeV  = "5.1 fb^{-1}";
TString lumi_sqrtS = "";
bool drawLogo      = false;

//--------------------------------------------//
//various functions
//--------------------------------------------//
//UP error in the unc band
double errBandUp(int iBin, TH1F *hCentral);
//down error in the unc band
double errBandDown(int iBin, TH1F *hCentral);
//unc graph
TGraphAsymmErrors *UNCGRAPH(TH1F *hCentral, bool isFullGraph, bool isRatioGraph);
//function to stack histos
void stackHisto(TH1F *hist, THStack* MuptStack, TH1F* hMC, int col);
TH1F* addHistoForUnc(TFile *file, TString chName);
TPaveText *paveText(double minX, double minY, double maxX, double maxY, int lineColor, int fillColor, int size, int style, int font );
//get histogram from root file. Return empty hist, if the hist does not exit.
TH1F* getHisto(TFile *fitDiagOut, TString channel, TString histName);
TH1F* getHistoSig(TFile *fitDiagOut, TString channel, TString histName);
TH1F *convertGraphToHist(TFile *fitDiagOut, TGraphAsymmErrors *gr);

//CMS guidelines
void CMS_lumi( TPad* pad, int iPeriod=3, int iPosX=10 , int year = 2016);
TCanvas * myCanvas(TString canvName, int iPeriod, int iPos, bool isData);
void setTDRStyle();

double errBandUp(int iBin, TH1F *hCentral){
		  return hCentral->GetBinError(iBin+1);
}

double errBandDown(int iBin, TH1F *hCentral){
		  return hCentral->GetBinError(iBin+1);
}

TGraphAsymmErrors *UNCGRAPH(TH1F *hCentral, bool isFullGraph = false, bool isRatioGraph = false){
  TGraphAsymmErrors *gr;
  int n1 = hCentral->GetNbinsX(); 
  double *Yval, *errorU, *errorD, *XerrorU, *XerrorD, *Xval ;
  Yval = new double[n1]; errorU = new double[n1]; errorD = new double[n1];
  XerrorU=new double[n1]; XerrorD=new double[n1]; Xval=new double[n1];
  //cout << "No. of bins= " << n1 << endl;
  for(int i=0; i<n1; i++){
    if(isFullGraph){
    Yval[i]   = hCentral->GetBinContent(i+1);
    errorU[i] = errBandUp(i, hCentral); 
    errorD[i] = errBandDown(i, hCentral); 
    }
    if(isRatioGraph){
    Yval[i]   = 1;
    errorU[i] = errBandUp(i, hCentral); 
    errorD[i] = errBandDown(i, hCentral); 
    errorU[i] = errorU[i]/hCentral->GetBinContent(i+1);
    errorD[i] = errorD[i]/hCentral->GetBinContent(i+1);
    //cout<<Yval[i]<<"\t"<<errorU[i]<<"\t"<<hCentral->GetBinContent(i+1)<<endl;
    }
    Xval[i]   = hCentral->GetBinCenter(i+1);
    XerrorU[i]= hCentral->GetBinWidth(i+1)/2;
    XerrorD[i]= hCentral->GetBinWidth(i+1)/2;
  }
  gr = new TGraphAsymmErrors(n1, Xval, Yval, XerrorD, XerrorU, errorD, errorU);
  return gr;
  delete [] Yval; delete [] errorU; delete [] errorD; delete [] XerrorU; delete [] XerrorD; delete [] Xval;
} 
double getStatUnc(TH1F* hCentral, double sError = 0.0){
  double  norm = hCentral->IntegralAndError(1, hCentral->GetNbinsX(), sError);
  //double statUnc = (norm > 0) ? 1 + (fabs(sError)/norm) : 1.00;
  double statUnc = sError;
  return statUnc;
}


TH1F* getHisto(TFile *histFile, TString chName, TString histName){
  cout << "getHisto::histFile : " << histFile->GetName() << ", chName: " << chName.Data() << ", histName: " << histName.Data() << endl;
  //TH1F* hist = (TH1F*)(histFile->Get("shapes_fit_b/"+chName+"/"+histName))->Clone(histName);
  TH1F* hist = (TH1F*)(histFile->Get("shapes_fit_s/"+chName+"/"+histName))->Clone(histName);
  //TH1F* hist = (TH1F*)(histFile->Get("shapes_prefit/"+chName+"/"+histName))->Clone(histName);
  //cout<<hist->Integral()<<endl;
  double err = 0.0;
  err = getStatUnc(hist, err);
  double err2 = 0.0;
  cout<<"-----------------"<<endl;
  for(int i = 1; i<hist->GetNbinsX()+1; i++){
    double binErr = hist->GetBinError(i);
    // cout<<"bin = "<<i<<endl;
    // cout<<"binCon = "<<hist->GetBinContent(i)<<endl;
    // cout<<"binErr = "<<hist->GetBinError(i)<<endl;
    err2 = err2 + binErr*binErr;
  }
  cout<<chName<<" : "<<histName<<" : "<<hist->Integral()<<" : "<<err<<": "<<sqrt(err2)<<endl;
  return hist;
}

TH1F* getHistoSig(TFile *histFile, TString chName, TString histName){
  cout << "getHistoSig::histFile : " << histFile->GetName() << ", chName: " << chName.Data() << ", histName: " << histName.Data() << endl;
  TH1F* hist = (TH1F*)(histFile->Get("shapes_prefit/"+chName+"/"+histName))->Clone(histName);
  double sf_combine = 2*0.10*(1-0.10);
  double sf_8TeV_BR = 0.12155; // 2*0.65*(1-0.65)
  hist->Scale(sf_8TeV_BR/sf_combine);
  cout<<hist->Integral()<<endl;
  return hist;
}

TH1F* getHistoPrefit(TFile *histFile, TString chName, TString histName){
  cout << "getHistoSig::histFile : " << histFile->GetName() << ", chName: " << chName.Data() << ", histName: " << histName.Data() << endl;
  TH1F* hist = (TH1F*)(histFile->Get("shapes_prefit/"+chName+"/"+histName))->Clone(histName);
  cout<<hist->Integral()<<endl;
  return hist;
}

TH1F* getHistoPostSignal(TFile *histFile, TString chName, TString histName){
  cout << "getHistoSig::histFile : " << histFile->GetName() << ", chName: " << chName.Data() << ", histName: " << histName.Data() << endl;
  TH1F* hist = (TH1F*)(histFile->Get("shapes_fit_s/"+chName+"/"+histName))->Clone(histName);
  cout<<"hist : " << hist << ", name : " << hist->GetName() << ", Entries : " << hist->GetEntries() << ", Integral: "<<hist->Integral()<<endl;
  return hist;
}

void stackHisto(TH1F *hist, THStack* MuptStack, TH1F* hMC, int col){
  hist->SetLineColor(col);
  hist->SetFillColor(col);
  MuptStack->Add(hist);
  hMC->Add(hist);
}
string intToStr(int val){
  //ostringstream convert;
     string result = Form("%d",val);
     //convert <<val;
     //result = convert.str();
  return result;
}

TH1F* addHistoForUnc(TFile *file, TString chName){
  TH1F* hvv   = getHisto (file, chName, "vv");
  TH1F* hqcd   = getHisto(file, chName, "qcd");
  TH1F* hstop  = getHisto(file, chName, "stop");
  TH1F* httbar = getHisto(file, chName, "ttbar");
  TH1F* hwjet  = getHisto(file, chName, "wjet");
  TH1F* hzjet  = getHisto(file, chName, "zjet");
  TH1F* hAll= (TH1F*)hvv->Clone("hAllMC");
  hAll->Add(hqcd);
  hAll->Add(hstop);
  hAll->Add(hwjet);
  hAll->Add(hzjet);
  hAll->Add(httbar);
  return hAll;
}

TCanvas * myCanvas(TString canvName, int iPeriod, int iPos, bool isData){
  int W = 800;
  int H = 800;
  int W_ref = 1000;
  int H_ref = 600;
  if(!isData){
    W = 800;
    H = 600;
    W_ref = 800;
    H_ref = 600;
  }
  // references for T, B, L, R
  float T = 0.08*H_ref;
  float B = 0.12*H_ref;
  float L = 0.12*W_ref;
  float R = 0.04*W_ref;
  canvName += W;
  canvName += "-";
  canvName += H;
  canvName += "_";
  canvName += iPeriod;
  if( writeExtraText ) canvName += "-prelim";
  if( iPos%10==0 ) canvName += "-out";
  else if( iPos%10==1 ) canvName += "-left";
  else if( iPos%10==2 )  canvName += "-center";
  else if( iPos%10==3 )  canvName += "-right";
  TCanvas* canv = new TCanvas(canvName,canvName,50,50,W,H);
  canv->SetFillColor(0);
  canv->SetBorderMode(0);
  canv->SetFrameFillStyle(0);
  canv->SetFrameBorderMode(0);
  canv->SetLeftMargin( L/W );
  canv->SetRightMargin( R/W );
  canv->SetTopMargin( T/H );
  canv->SetBottomMargin( B/H );
  canv->SetTickx(0);
  canv->SetTicky(0);
  return canv;
}


TPaveText *  paveText(double minX, double minY, double maxX, double maxY, int lineColor, int fillColor, int size, int style, int font ){
  TPaveText *pt = new TPaveText(minX, minY, maxX, maxY, "brNDC"); // good_v1
  pt->SetBorderSize(size);
  pt->SetFillColor(fillColor);
  pt->SetFillStyle(style);
  pt->SetLineColor(lineColor);
  pt->SetTextFont(font);
  return pt;
}

void setTDRStyle() {
  TStyle *tdrStyle = new TStyle("tdrStyle","Style for P-TDR");
// For the canvas:
  tdrStyle->SetCanvasBorderMode(0);
  tdrStyle->SetCanvasColor(kWhite);
  tdrStyle->SetCanvasDefH(600); //Height of canvas
  tdrStyle->SetCanvasDefW(600); //Width of canvas
  tdrStyle->SetCanvasDefX(0);   //POsition on screen
  tdrStyle->SetCanvasDefY(0);

// For the Pad:
  tdrStyle->SetPadBorderMode(0);
  // tdrStyle->SetPadBorderSize(Width_t size = 1);
  tdrStyle->SetPadColor(kWhite);
  tdrStyle->SetPadGridX(false);
  tdrStyle->SetPadGridY(false);
  tdrStyle->SetGridColor(0);
  tdrStyle->SetGridStyle(3);
  tdrStyle->SetGridWidth(1);

// For the frame:
  tdrStyle->SetFrameBorderMode(0);
  tdrStyle->SetFrameBorderSize(1);
  tdrStyle->SetFrameFillColor(0);
  tdrStyle->SetFrameFillStyle(0);
  tdrStyle->SetFrameLineColor(1);
  tdrStyle->SetFrameLineStyle(1);
  tdrStyle->SetFrameLineWidth(1);

// For the histo:
  // tdrStyle->SetHistFillColor(1);
  // tdrStyle->SetHistFillStyle(0);
  tdrStyle->SetHistLineColor(1);
  tdrStyle->SetHistLineStyle(0);
  tdrStyle->SetHistLineWidth(1);
  // tdrStyle->SetLegoInnerR(Float_t rad = 0.5);
  // tdrStyle->SetNumberContours(Int_t number = 20);

  tdrStyle->SetEndErrorSize(2);
  // tdrStyle->SetErrorMarker(20);
  //tdrStyle->SetErrorX(0.);

  tdrStyle->SetMarkerStyle(20);

//For the fit/function:
  tdrStyle->SetOptFit(1);
  tdrStyle->SetFitFormat("5.4g");
  tdrStyle->SetFuncColor(2);
  tdrStyle->SetFuncStyle(1);
  tdrStyle->SetFuncWidth(1);

//For the date:
  tdrStyle->SetOptDate(0);
  // tdrStyle->SetDateX(Float_t x = 0.01);
  // tdrStyle->SetDateY(Float_t y = 0.01);

// For the statistics box:
  tdrStyle->SetOptFile(0);
  tdrStyle->SetOptStat(0); // To display the mean and RMS:   SetOptStat("mr");
  tdrStyle->SetStatColor(kWhite);
  tdrStyle->SetStatFont(42);
  tdrStyle->SetStatFontSize(0.025);
  tdrStyle->SetStatTextColor(1);
  tdrStyle->SetStatFormat("6.4g");
  tdrStyle->SetStatBorderSize(1);
  tdrStyle->SetStatH(0.1);
  tdrStyle->SetStatW(0.15);
  // tdrStyle->SetStatStyle(Style_t style = 1001);
  // tdrStyle->SetStatX(Float_t x = 0);
  // tdrStyle->SetStatY(Float_t y = 0);

// Margins:
  tdrStyle->SetPadTopMargin(0.05);
  tdrStyle->SetPadBottomMargin(0.13);
  tdrStyle->SetPadLeftMargin(0.16);
  tdrStyle->SetPadRightMargin(0.02);

// For the Global title:

  tdrStyle->SetOptTitle(0);
  tdrStyle->SetTitleFont(42);
  tdrStyle->SetTitleColor(1);
  tdrStyle->SetTitleTextColor(1);
  tdrStyle->SetTitleFillColor(10);
  tdrStyle->SetTitleFontSize(0.05);
  // tdrStyle->SetTitleH(0); // Set the height of the title box
  // tdrStyle->SetTitleW(0); // Set the width of the title box
  // tdrStyle->SetTitleX(0); // Set the position of the title box
  // tdrStyle->SetTitleY(0.985); // Set the position of the title box
  // tdrStyle->SetTitleStyle(Style_t style = 1001);
  // tdrStyle->SetTitleBorderSize(2);

// For the axis titles:

  tdrStyle->SetTitleColor(1, "XYZ");
  tdrStyle->SetTitleFont(42, "XYZ");
  tdrStyle->SetTitleSize(0.06, "XYZ");
  // tdrStyle->SetTitleXSize(Float_t size = 0.02); // Another way to set the size?
  // tdrStyle->SetTitleYSize(Float_t size = 0.02);
  tdrStyle->SetTitleXOffset(0.9);
  tdrStyle->SetTitleYOffset(1.25);
  // tdrStyle->SetTitleOffset(1.1, "Y"); // Another way to set the Offset

// For the axis labels:

  tdrStyle->SetLabelColor(1, "XYZ");
  tdrStyle->SetLabelFont(42, "XYZ");
  tdrStyle->SetLabelOffset(0.007, "XYZ");
  tdrStyle->SetLabelSize(0.05, "XYZ");

// For the axis:

  tdrStyle->SetAxisColor(1, "XYZ");
  tdrStyle->SetStripDecimals(kTRUE);
  tdrStyle->SetTickLength(0.03, "XYZ");
  tdrStyle->SetNdivisions(510, "XYZ");
  tdrStyle->SetPadTickX(1);  // To get tick marks on the opposite side of the frame
  tdrStyle->SetPadTickY(1);

// Change for log plots:
  tdrStyle->SetOptLogx(0);
  tdrStyle->SetOptLogy(0);
  tdrStyle->SetOptLogz(0);

// Postscript options:
  tdrStyle->SetPaperSize(20.,20.);
  // tdrStyle->SetLineScalePS(Float_t scale = 3);
  // tdrStyle->SetLineStyleString(Int_t i, const char* text);
  // tdrStyle->SetHeaderPS(const char* header);
  // tdrStyle->SetTitlePS(const char* pstitle);

  // tdrStyle->SetBarOffset(Float_t baroff = 0.5);
  // tdrStyle->SetBarWidth(Float_t barwidth = 0.5);
  // tdrStyle->SetPaintTextFormat(const char* format = "g");
  // tdrStyle->SetPalette(Int_t ncolors = 0, Int_t* colors = 0);
  // tdrStyle->SetTimeOffset(Double_t toffset);
  // tdrStyle->SetHistMinimumZero(kTRUE);

  tdrStyle->SetHatchesLineWidth(5);
  tdrStyle->SetHatchesSpacing(0.05);

  tdrStyle->cd();

}

void CMS_lumi( TPad* pad, int iPeriod, int iPosX, int year ){
  bool outOfFrame    = false;
  if( iPosX/10==0 )
    {
      outOfFrame = true;
    }
  int alignY_=3;
  int alignX_=2;
  if( iPosX/10==0 ) alignX_=1;
  if( iPosX==0    ) alignX_=1;
  if( iPosX==0    ) alignY_=1;
  if( iPosX/10==1 ) alignX_=1;
  if( iPosX/10==2 ) alignX_=2;
  if( iPosX/10==3 ) alignX_=3;
  //if( iPosX == 0  ) relPosX = 0.12;
  int align_ = 10*alignX_ + alignY_;
  float H = pad->GetWh();
  float W = pad->GetWw();
  float l = pad->GetLeftMargin();
  float t = pad->GetTopMargin();
  float r = pad->GetRightMargin();
  float b = pad->GetBottomMargin();
  //  float e = 0.025;
  pad->cd();
  if(year==2016) lumi_13TeV = lumi_13TeV_2016 ;
  if(year==2017) lumi_13TeV = lumi_13TeV_2017 ;
  if(year==2018) lumi_13TeV = lumi_13TeV_2018 ;
  if(year==201678) lumi_13TeV = lumi_13TeV_run2 ;
  TString lumiText;
  if( iPeriod==1 )
    {
      lumiText += lumi_7TeV;
      lumiText += " (7 TeV)";
    }
  else if ( iPeriod==2 )
    {
      lumiText += lumi_8TeV;
      lumiText += " (8 TeV)";
    }
  else if( iPeriod==3 )
    {
      lumiText = lumi_8TeV;
      lumiText += " (8 TeV)";
      lumiText += " + ";
      lumiText += lumi_7TeV;
      lumiText += " (7 TeV)";
    }
  else if ( iPeriod==4 )
    {
      lumiText += lumi_13TeV;
      lumiText += " (13 TeV)";
    }
  else if ( iPeriod==7 )
    {
      if( outOfFrame ) lumiText += "#scale[0.85]{";
      lumiText += lumi_13TeV;
      lumiText += " (13 TeV)";
      lumiText += " + ";
      lumiText += lumi_8TeV;
      lumiText += " (8 TeV)";
      lumiText += " + ";
      lumiText += lumi_7TeV;
      lumiText += " (7 TeV)";
      if( outOfFrame) lumiText += "}";
    }
  else if ( iPeriod==12 )
    {
      lumiText += "8 TeV";
    }
  else if ( iPeriod==0 )
    {
      lumiText += lumi_sqrtS;
    }
  std::cout << lumiText << endl;
  TLatex latex;
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack);
  float extraTextSize = extraOverCmsTextSize*cmsTextSize;
  latex.SetTextFont(42);
  latex.SetTextAlign(31);
  latex.SetTextSize(lumiTextSize*t);
  latex.DrawLatex(1-r,1-t+lumiTextOffset*t,lumiText);
  if( outOfFrame )
    {
      latex.SetTextFont(cmsTextFont);
      latex.SetTextAlign(11);
      latex.SetTextSize(cmsTextSize*t);
      latex.DrawLatex(l,1-t+lumiTextOffset*t,cmsText);
    }
  pad->cd();
  float posX_=0;
  if( iPosX%10<=1 )
    {
      posX_ =   l + relPosX*(1-l-r);
    }
  else if( iPosX%10==2 )
    {
      posX_ =  l + 0.5*(1-l-r);
    }
  else if( iPosX%10==3 )
    {
      posX_ =  1-r - relPosX*(1-l-r);
    }
  float posY_ = 1-t - relPosY*(1-t-b);
  if( !outOfFrame )
    {
      if( drawLogo )
	{
	  posX_ =   l + 0.045*(1-l-r)*W/H;
	  posY_ = 1-t - 0.045*(1-t-b);
	  float xl_0 = posX_;
	  float yl_0 = posY_ - 0.15;
	  float xl_1 = posX_ + 0.15*H/W;
	  float yl_1 = posY_;
	  TASImage* CMS_logo = new TASImage("CMS-BW-label.png");
	  TPad* pad_logo = new TPad("logo","logo", xl_0, yl_0, xl_1, yl_1 );
	  pad_logo->Draw();
	  pad_logo->cd();
	  CMS_logo->Draw("X");
	  pad_logo->Modified();
	  pad->cd();
	}
      else
	{
	  latex.SetTextFont(cmsTextFont);
	  latex.SetTextSize(cmsTextSize*t);
	  latex.SetTextAlign(align_);
	  latex.DrawLatex(posX_, posY_, cmsText);
	  if( writeExtraText )
	    {
	      latex.SetTextFont(extraTextFont);
	      latex.SetTextAlign(align_);
	      latex.SetTextSize(extraTextSize*t);
	      latex.DrawLatex(posX_, posY_- relExtraDY*cmsTextSize*t, extraText);
	    }
	}
    }
  else if( writeExtraText )
    {
      if( iPosX==0)
	{
	  posX_ =   l +  relPosX*(1-l-r);
	  posY_ =   1-t+lumiTextOffset*t;
	}
      latex.SetTextFont(extraTextFont);
      latex.SetTextSize(extraTextSize*t);
      latex.SetTextAlign(align_);
      latex.DrawLatex(1.5*posX_, posY_, extraText);
    }
  return;
}
TH1F *convertGraphToHist(TFile *fitDiagOut, TString chName, TGraphAsymmErrors *graph){
  TH1F *h = getHisto(fitDiagOut,chName.Data(),"ttbar");
  h->Reset(); 
  auto nPoints = graph->GetN(); 
  //cout<<h->GetNbinsX()<<endl;
  for(int i=0; i < nPoints; i++) {
     double x,y;
     graph->GetPoint(i, x, y);
     //cout<<i<<"\t"<<", x = "<<x<<"\t"<<", y = "<<y<<endl;
     //cout<<graph->GetErrorY(i)<<endl;
     h->SetBinContent(i+1, y);
     h->SetBinError(i+1, graph->GetErrorX(i));
  }
  cout<<" Name : " <<h->GetName() << ", Integral : "<<h->Integral() << endl;
  return h;
}

//--------------------------------------------//
//stack histos
//--------------------------------------------//
void example_stack(TFile *fitDiagOut, TString outdir, int year, TString cattype, TString channel, TString chName, TString chLable, TString charmCat, bool isPrefit){
  //Pad
  setTDRStyle();
  TCanvas *c1 = myCanvas(chName, iPeriod, 1, isData);
  const float xpad[2] = {0.,1.0};
  const float ypad[4] = {0.,0.30,0.30,1.0};
  c1->Divide(1, 2); c1->cd(1)->SetLogy();
  gPad->SetRightMargin(0.03);
  gPad->SetPad(xpad[0],ypad[2],xpad[1],ypad[3]);

  //VV is the base histo
  TH1F* hVV = (isPrefit) ? getHistoPrefit(fitDiagOut, chName, "vv") : getHisto(fitDiagOut, chName, "vv");
  // cout << "hVV " << hVV << endl;
  // hVV->Draw();
  hVV->SetFillColor(kGreen +1);
  //Define stacked histo
  THStack* hStack = new THStack("hStack","");
  //hStack->SetMinimum(1.0);
  hStack->Add(hVV);
  //hMC = all Bkg MC samples
  
  TH1F* hMC = (TH1F*)hVV->Clone("hMC");
  TH1F* hQCD   = (isPrefit) ? getHistoPrefit(fitDiagOut, chName, "qcd") : getHisto(fitDiagOut, chName, "qcd");
  TH1F* hQCDPrefit = 0x0 ;
  if(!isPrefit)
    hQCDPrefit = getHistoPrefit(fitDiagOut, chName, "qcd");
  TH1F* hST  = (isPrefit) ? getHistoPrefit(fitDiagOut, chName, "stop") : getHisto(fitDiagOut, chName, "stop");
  TH1F* hTT = (isPrefit) ? getHistoPrefit(fitDiagOut, chName, "ttbar") : getHisto(fitDiagOut, chName, "ttbar");
  TH1F* hWjet  = (isPrefit) ? getHistoPrefit(fitDiagOut, chName, "wjet") : getHisto(fitDiagOut, chName, "wjet");
  TH1F* hDY  = (isPrefit) ? getHistoPrefit(fitDiagOut, chName, "zjet") : getHisto(fitDiagOut, chName, "zjet");
  TH1F* hTTG  = (isPrefit) ? getHistoPrefit(fitDiagOut, chName, "ttg") : getHisto(fitDiagOut, chName, "ttg");
  TH1F* hTTH  = (isPrefit) ? getHistoPrefit(fitDiagOut, chName, "tth") : getHisto(fitDiagOut, chName, "tth");
  TH1F* hTTZ  = (isPrefit) ? getHistoPrefit(fitDiagOut, chName, "ttz") : getHisto(fitDiagOut, chName, "ttz");
  TH1F* hTTW  = (isPrefit) ? getHistoPrefit(fitDiagOut, chName, "ttw") : getHisto(fitDiagOut, chName, "ttw");
  stackHisto(hTTG , hStack, hMC, kBlue);
  stackHisto(hTTH , hStack, hMC, kRed-1);
  stackHisto(hTTZ , hStack, hMC, kMagenta);
  stackHisto(hTTW , hStack, hMC, kCyan+3);
  stackHisto(hDY , hStack, hMC, kOrange +1);
  stackHisto(hWjet , hStack, hMC, kYellow +1);
  stackHisto(hQCD  , hStack, hMC, kRed +1);
  stackHisto(hST , hStack, hMC, kViolet +1);
  stackHisto(hTT, hStack, hMC, kCyan + 1);

  gPad->SetTopMargin(0.09);
  gPad->SetBottomMargin(0.0);
  hStack->Draw("HIST");
  hStack->SetMinimum(1.0);
  //hStack ->GetXaxis()->SetRangeUser(xMin, xMax);
  TGaxis::SetMaxDigits(3);
  hStack->GetYaxis()->SetTitle("Events / 10 GeV");
  hStack->GetXaxis()->SetTitle("xTitle");

  //-------------------------------------///
  //unc band
  //-------------------------------------///
  TGraphAsymmErrors *UncBand;
  UncBand = UNCGRAPH(addHistoForUnc(fitDiagOut, chName), true, false);
  UncBand->SetFillColor(kSpring +9);
  UncBand->SetFillStyle(3008);
  UncBand->Draw(" E2 same");

  //Data
  TGraphAsymmErrors *dataGraph = (TGraphAsymmErrors*)fitDiagOut->Get("shapes_fit_s/"+chName+"/data");
  TH1F *hData = convertGraphToHist(fitDiagOut, chName, dataGraph);
  hData->SetFillColor(kBlack);
  hData->SetMarkerStyle(20); 
  hData->SetMarkerSize(1.2);
  c1->Update();
  if(isData)hData->Draw("Esame");

  //-------------------------------
  //Signal
  //-------------------------------
  TH1F* hSig = getHistoPostSignal(fitDiagOut, chName, "WH60");
  hSig->SetLineColor(kRed); hSig->SetLineStyle(2);
  hSig->SetLineWidth(3); hSig->SetFillColor(0);
  hSig->Draw("HISTSAME");
  hStack->SetMaximum(1.1*hStack->GetMaximum());
  hStack->SetMaximum(5.e9);

  //-------------------------------------///
  //  Draw Pave Text
  //-------------------------------------///
  //channel
  TPaveText *ch = paveText(0.22,0.5061504,0.38,0.60, 0, 19, 1, 0, 132);
  ch->SetTextSize(0.05);
  // if(chName.Contains("ch1_ch1") || chName.Contains("ch2_ch1") ||chName.Contains("ch3_ch1") ) ch->AddText("#splitline{#mu + jets}{"+charmCat+"}");
  // if(chName.Contains("ch1_ch2") || chName.Contains("ch2_ch2") ||chName.Contains("ch3_ch2") ) ch->AddText("#splitline{e + jets}{"+charmCat+"}");
  // if( chName.Contains("ch1") || chName.Contains("ch2") ||chName.Contains("ch3")
  //     || chName.Contains("ch4") || chName.Contains("ch5") ||chName.Contains("ch6")
  //     || chName.Contains("ch7") || chName.Contains("ch8") ||chName.Contains("ch9"))
  //   ch->AddText("#splitline{#it{e} + jets}{"+charmCat+"}");
  // if( chName.Contains("ch10") || chName.Contains("ch11") ||chName.Contains("ch12")
  //     || chName.Contains("ch13") || chName.Contains("ch14") ||chName.Contains("ch15")
  //     || chName.Contains("ch16") || chName.Contains("ch17") ||chName.Contains("ch18"))
  //   ch->AddText("#splitline{#mu + jets}{"+charmCat+"}");

  ch->AddText("#splitline{"+chLable+"}{"+charmCat+"}");
  //if(chName.Contains("ch1_ch2") || chName.Contains("ch2_ch2") ||chName.Contains("ch3_ch2") ) ch->AddText("#splitline{#mu + jets}{"+charmCat+"}");
  gPad->RedrawAxis();
  c1->Update();
  

  //-------------------------------
  //Legends
  //-------------------------------
  TLegend* leg = new TLegend(0.5818792,0.5061504,0.7512081,0.908861,NULL,"brNDC");
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->SetFillColor(kBlack);
  leg->SetTextFont(42);
  leg->SetTextAngle(0);
  leg->SetTextSize(0.04);
  leg->SetTextAlign(12);
  leg->AddEntry(hST,"Single t","F");
  leg->AddEntry(hQCD,"QCD","F");
  leg->AddEntry(hWjet,"W + jets","F");
  leg->AddEntry(hDY,"Z/#gamma + jets","F");
  leg->AddEntry(hVV,"VV","F");
  leg->AddEntry(UncBand, "Post-fit unc.","F");
  //if(!isPrefit) leg->AddEntry("", Form("QCD post/pre = %5.4f",hQCD->Integral()/hQCDPrefit->Integral()),"");
  leg->AddEntry(hSig, "m_{H^{#pm}} = 60 GeV","L");
  //leg->AddEntry((TObject*)0, "B(t #rightarrow H^{+} b) = 0.065","");


  
  TLegend* leg1 = new TLegend(0.3818792,0.5061504,0.5512081,0.908861,NULL,"brNDC");
  leg1->SetFillStyle(0);
  leg1->SetBorderSize(0);
  leg1->SetFillColor(kBlack);
  leg1->SetTextFont(42);
  leg1->SetTextAngle(0);
  leg1->SetTextSize(0.04);
  leg1->SetTextAlign(12);
  if(isData)leg1->AddEntry(hData,"Data","PE");
  leg1->AddEntry(hTT,"t#bar{t} + jets","F");
  leg1->AddEntry(hTTG,"t#bar{t}g + jets","F");
  leg1->AddEntry(hTTH,"t#bar{t}h + jets","F");
  leg1->AddEntry(hTTZ,"t#bar{t}Z + jets","F");
  leg1->AddEntry(hTTW,"t#bar{t}W + jets","F");
  

  
  c1->Update();
  ch->Draw();
  leg->Draw();
  leg1->Draw();

  //-------------------------------------///
  // Ratio = DATA/Bkg
  //-------------------------------------///
  c1->cd(2);
  c1->Update();
  c1->RedrawAxis();
  c1->GetFrame()->Draw();
  gPad->SetTopMargin(0); 
  gPad->SetBottomMargin(0.30); //gPad->SetGridy();
  gPad->SetRightMargin(0.03);
  gPad->SetTickx(0);
  gPad->SetPad(xpad[0],ypad[0],xpad[1],ypad[2]);
  //gPad->SetGridx();
  gPad->SetGridy();
  TH1F *hRatio = (TH1F*)hData->Clone("hRatio");
  hRatio->Reset();
  hRatio->Add(hData);
  hRatio->Divide(hMC);
  hRatio->SetFillColor(kBlack);
  hRatio->GetYaxis()->SetRangeUser(yMin, yMax);
  hRatio->GetXaxis()->SetTitleSize(0.13);
  hRatio->GetXaxis()->SetLabelSize(0.15);
  hRatio->GetXaxis()->SetLabelFont(42);
  hRatio->GetXaxis()->SetLabelColor(kBlack);
  hRatio->GetXaxis()->SetAxisColor(kBlack);
  hRatio->GetXaxis()->SetTickLength(0.06);
  //hRatio->GetXaxis()->SetRangeUser(xMin, xMax);
  hRatio->GetXaxis()->SetTitleOffset(1);
  hRatio->GetXaxis()->SetLabelOffset(0.01);
  hRatio->SetMarkerStyle(20); 
  hRatio->SetMarkerSize(1.2);
  hRatio->GetYaxis()->SetTitleSize(0.13);
  hRatio->GetYaxis()->SetLabelSize(0.11);
  hRatio->GetYaxis()->SetLabelFont(42);
  hRatio->GetYaxis()->SetAxisColor(1);
  hRatio->GetYaxis()->SetTickLength(0.03);
  //hRatio->GetYaxis()->SetNdivisions(6,5,0);
  hRatio->GetYaxis()->SetNdivisions(505);
  hRatio->GetYaxis()->SetTitleOffset(0.5);
  hRatio->GetYaxis()->SetLabelOffset(0.01);
  hRatio->GetYaxis()->CenterTitle();
  hRatio->GetXaxis()->SetTitle("m_{jj} (GeV)");
  //for(int i = 0; i<32; i++){
  for(int i = 0; i<16; i++){
    //string lable = "    "+intToStr(i*5 + 20);
    string lable = "    "+intToStr(i*10 + 10);
    if(i%3==!0)hRatio->GetXaxis()->SetBinLabel(i, lable.c_str());
    hRatio->GetXaxis()->LabelsOption("h");
    //hRatio->GetXaxis()->SetTickLength(0.08);
    hRatio->GetXaxis()->SetLabelOffset(0.02);
  }
  hRatio->GetYaxis()->SetTitle("#frac{Data}{Bkg}");
  
  //unc band
  hRatio->Draw("E"); // use "P" or "AP"
  TGraphAsymmErrors *UncBand_Ratio;
  UncBand_Ratio = UNCGRAPH(addHistoForUnc(fitDiagOut, chName), false, true);
  UncBand_Ratio->SetFillColor(kSpring +9);
  //UncBand_Ratio->SetFillStyle(3001);
  UncBand_Ratio->Draw("E2 same");
  hRatio->Draw("E same"); // use "P" or "AP"
  //base line at 1
  TF1 *baseLine = new TF1("baseLine","1", -100, 2000); 
  baseLine->SetLineColor(kBlack);
  baseLine->Draw("SAME");
  CMS_lumi(c1, iPeriod, iPosX, year);
  c1->Update();
  if(isSaveHisto){
    // TString outFile = (isPrefit) ? Form("%s/mjj_prefit_%d_%s_%s.pdf",outdir.Data(),year,cattype.Data(),channel.Data()) : Form("%s/mjj_postfit_%s_%d_%s_%s.pdf",outdir.Data(),chName.Data(),year,cattype.Data(),channel.Data());
    // TString outFile1 = (isPrefit) ? Form("%s/mjj_prefit_%d_%s_%s.png",outdir.Data(),year,cattype.Data(),channel.Data()) : Form("%s/mjj_postfit_%s_%d_%s_%s.png",outdir.Data(),chName.Data(),year,cattype.Data(),channel.Data());
    TString outFile = (isPrefit) ? Form("%s/mjj_prefit_%d_%s_%s.pdf",outdir.Data(),year,cattype.Data(),channel.Data()) : Form("%s/mjj_postfit_%d_%s_%s.pdf",outdir.Data(),year,cattype.Data(),channel.Data());
    TString outFile1 = (isPrefit) ? Form("%s/mjj_prefit_%d_%s_%s.png",outdir.Data(),year,cattype.Data(),channel.Data()) : Form("%s/mjj_postfit_%d_%s_%s.png",outdir.Data(),year,cattype.Data(),channel.Data());
    c1->SaveAs(outFile);
    c1->SaveAs(outFile1);
    c1->Close();
  }
}


void MyPostFitPlot(){

  // example_stack(2016, "ch1_ch1", "#mu + jets", "No Charm, 2016");
  // example_stack(2016, "ch1_ch2", "#it{e} + jets", "No Charm, 2016");
  // example_stack(2017, "ch2_ch1", "#mu + jets", "No Charm, 2017");
  // example_stack(2017, "ch2_ch2", "#it{e} + jets", "No Charm, 2017");
  // example_stack(2018, "ch3_ch1", "#mu + jets", "No Charm, 2018");
  // example_stack(2018, "ch3_ch2", "#it{e} + jets", "No Charm, 2018");
  
  // //TString dirpath = "limit/Imperial-PA-2024-10-08/50_unblinded_MVA_lnNfixed_qcdrange0to50_qcddd6_bc3_uncorr_symm_10GeV/";
  // TString dirpath = "limit/local/";
  // TString fname = dirpath + "2016/ExcL/ele/Cat1_Inc/Mass80/fitDiagnosticsTest.root" ;
  // TString outdir;
  // for(int year=2016;year<=2018;year++){
  //   for(int cat=1;cat<=3;cat++){
  //     TString cattype = "";
  //     if(cat==1) cattype = "ExcL";
  //     else if(cat==2) cattype = "ExcM";
  //     else cattype = "ExcT";      
  //     for(int ch=1;ch<=2;ch++){
  // 	TString channel = (ch==1) ? "ele" : "mu" ;
  // 	outdir = dirpath + Form("%d/%s/%s/Cat1_Inc/Mass80/",year,cattype.Data(),channel.Data());
  // 	fname = outdir + "fitDiagnosticsTest.root";
  // 	cout<<"Processing.." << fname << endl;
  // 	TFile *fitDiagOut = TFile::Open(fname);
  // 	example_stack(fitDiagOut, outdir, year, cattype, channel, "ch1", ((ch==1)?"#it{e} + jets":"#mu + jets"), Form("%d %s",year,cattype.Data()),0);
  // 	fitDiagOut->Close();
  // 	delete fitDiagOut;
  //     }
  //   }
  // }

  TString dirpath = "limit/local/";
  TString fname = dirpath + "Run2/Comb/mu_ele/Cat1_Inc/Mass60/fitDiagnosticsTest_br0to0p1.root" ;
  TFile *fitDiagOut = TFile::Open(fname);
  TString channel = "mu_ele" ;
  TString cattype = "Comb";
  TString year = "Run2";
  TString outdir = dirpath + Form("%s/%s/%s/Cat1_Inc/Mass60/",year.Data(),cattype.Data(),channel.Data());
  example_stack(fitDiagOut, outdir, 2016, "ExcL", "ele", "ch1", "#it{e} + jets", "2016:ExcL", 0);
  example_stack(fitDiagOut, outdir, 2017, "ExcL", "ele", "ch2", "#it{e} + jets", "2017:ExcL", 0);
  example_stack(fitDiagOut, outdir, 2018, "ExcL", "ele", "ch3", "#it{e} + jets", "2018:ExcL", 0);
  example_stack(fitDiagOut, outdir, 2016, "ExcM", "ele", "ch4", "#it{e} + jets", "2016:ExcM", 0);
  example_stack(fitDiagOut, outdir, 2017, "ExcM", "ele", "ch5", "#it{e} + jets", "2017:ExcM", 0);
  example_stack(fitDiagOut, outdir, 2018, "ExcM", "ele", "ch6", "#it{e} + jets", "2018:ExcM", 0);
  example_stack(fitDiagOut, outdir, 2016, "ExcT", "ele", "ch7", "#it{e} + jets", "2016:ExcT", 0);
  example_stack(fitDiagOut, outdir, 2017, "ExcT", "ele", "ch8", "#it{e} + jets", "2017:ExcT", 0);
  example_stack(fitDiagOut, outdir, 2018, "ExcT", "ele", "ch9", "#it{e} + jets", "2018:ExcT", 0);

  example_stack(fitDiagOut, outdir, 2016, "ExcL", "mu", "ch10", "#mu + jets", "2016:ExcL", 0);
  example_stack(fitDiagOut, outdir, 2017, "ExcL", "mu", "ch11", "#mu + jets", "2017:ExcL", 0);
  example_stack(fitDiagOut, outdir, 2018, "ExcL", "mu", "ch12", "#mu + jets", "2018:ExcL", 0);
  example_stack(fitDiagOut, outdir, 2016, "ExcM", "mu", "ch13", "#mu + jets", "2016:ExcM", 0);
  example_stack(fitDiagOut, outdir, 2017, "ExcM", "mu", "ch14", "#mu + jets", "2017:ExcM", 0);
  example_stack(fitDiagOut, outdir, 2018, "ExcM", "mu", "ch15", "#mu + jets", "2018:ExcM", 0);
  example_stack(fitDiagOut, outdir, 2016, "ExcT", "mu", "ch16", "#mu + jets", "2016:ExcT", 0);
  example_stack(fitDiagOut, outdir, 2017, "ExcT", "mu", "ch17", "#mu + jets", "2017:ExcT", 0);
  example_stack(fitDiagOut, outdir, 2018, "ExcT", "mu", "ch18", "#mu + jets", "2018:ExcT", 0);

  // example_stack("ch5", "e + jets", "Medium");
  // example_stack("ch6", "e + jets", "Tight");

} 

