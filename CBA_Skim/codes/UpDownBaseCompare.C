/**********************************************************************
 Created on : 12/09/2021
 Purpose    : Compare Up/Down with base
 Author     : Indranil Das, Visiting Fellow
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
#include <TROOT.h>

#include <TRatioPlot.h>

#include <iostream>

using namespace std;

int UpDownBaseCompare(int isMu = 1, int year = 2016, int isysup = 98){
  
  int PlotRatio(TH1D *h1, TH1D *h2, float maxmin, const char *cname);
  int ModifyUpDownHisto(TH1D*& hnom, TH1D*& hup, TH1D*& hdown, TH1D *hupbynom, TH1D *hdownbynom);
  
  const char *samples[] = {"HplusM080", "HplusM090", "HplusM100", "HplusM140", 
			   "HplusM150", "HplusM155", "HplusM160", "HplusM120", 
			   "DataMu", "DataEle", "TTbar", "singleTop", 
			   "Wjets", "DYjets", "VBFusion", "MCQCDMu", 
			   "MCQCDEle"};
  
  const int nShapes = 0;
  const char* listShapes[] = {""};
  
  const char *syst_2016[] = {"base", 
			     "pdfup", "pdfdown", "q2up", "q2down",                             //2,4    
			     "isrup", "isrdown", "fsrup", "fsrdown",                           //6,8
			     "puup", "pudown", "prefireup", "prefiredown",                     //10,12
			     "mueffup", "mueffdown", "eleeffup", "eleeffdown",                 //14,16
			     "pujetidup", "pujetiddown", "metup", "metdown",                   //18,20
			     "absmpfbup", "absmpfbdown", "abssclup", "absscldown",             //22,24
			     "absstatup", "absstatdown", "flavorqcdup", "flavorqcddown",       //26,28
			     "fragup", "fragdown", "timeptetaup", "timeptetadown",             //30,32
			     "pudatamcup", "pudatamcdown", "puptbbup", "puptbbdown",           //34,36 
			     "puptec1up", "puptec1down", "puptec2up", "puptec2down",           //38,40 
			     "pupthfup", "pupthfdown", "puptrefup", "puptrefdown",             //42,44 
			     "relfsrup", "relfsrdown", "relbalup", "relbaldown",               //46,48 
			     "relsampleup", "relsampledown", "reljerec1up", "reljerec1down",   //50,52 
			     "reljerec2up", "reljerec2down", "reljerhfup", "reljerhfdown",     //54,56 
			     "relptbbup", "relptbbdown", "relptec1up", "relptec1down",         //58,60 
			     "relptec2up", "relptec2down", "relpthfup", "relpthfdown",         //62,64 
			     "relstatecup", "relstatecdown", "relstatfsrup","relstatfsrdown",  //66,68 
			     "relstathfup", "relstathfdown",                                   //70
			     "singpiecalup", "singpiecaldown", "singpihcalup", "singpihcaldown", //72,74 
			     // CShapeCalib UL
			     "bcstatup", "bcstatdown", "bcjesup", "bcjesdown",                 //76,78   
			     "bcintpup", "bcintpdown", "bcextpup", "bcextpdown",               //80,82
			     "bclhemufup", "bclhemufdown", "bclhemurup", "bclhemurdown",       //84,86
			     "bcxdybup", "bcxdybdown", "bcxdycup", "bcxdycdown",               //88,90
			     "bcxwjcup", "bcxwjcdown",                                         //92
			     "topptup", "topptdown",                                           //96
			     "cp5up", "cp5down","mtopup", "mtopdown", "hdampup", "hdampdown",   //96,98,100
			       "jerup", "jerdown" //102
			     //"jecup", "jecdown"
  };

  const char *syst_2017[] = {"base", 
			     "pdfup", "pdfdown", "q2up", "q2down",                             //2,4    
			     "isrup", "isrdown", "fsrup", "fsrdown",                           //6,8
			     "puup", "pudown", "prefireup", "prefiredown",                     //10,12
			     "mueffup", "mueffdown", "eleeffup", "eleeffdown",                 //14,16
			     "pujetidup", "pujetiddown", "metup", "metdown",                   //18,20
			     "absmpfbup", "absmpfbdown", "abssclup", "absscldown",             //22,24
			     "absstatup", "absstatdown", "flavorqcdup", "flavorqcddown",       //26,28
			     "fragup", "fragdown", "timeptetaup", "timeptetadown",             //30,32
			     "pudatamcup", "pudatamcdown", "puptbbup", "puptbbdown",           //34,36 
			     "puptec1up", "puptec1down", "puptec2up", "puptec2down",           //38,40 
			     "pupthfup", "pupthfdown", "puptrefup", "puptrefdown",             //42,44 
			     "relfsrup", "relfsrdown", "relbalup", "relbaldown",               //46,48 
			     "relsampleup", "relsampledown", "reljerec1up", "reljerec1down",   //50,52 
			     "reljerec2up", "reljerec2down", "reljerhfup", "reljerhfdown",     //54,56 
			     "relptbbup", "relptbbdown", "relptec1up", "relptec1down",         //58,60 
			     "relptec2up", "relptec2down", "relpthfup", "relpthfdown",         //62,64 
			     "relstatecup", "relstatecdown", "relstatfsrup","relstatfsrdown",  //66,68 
			     "relstathfup", "relstathfdown",                                   //70
			     "singpiecalup", "singpiecaldown", "singpihcalup", "singpihcaldown", //72,74 
			     // CShapeCalib UL
			     "bcstatup", "bcstatdown", "bcjesup", "bcjesdown",                 //76,78   
			     "bcintpup", "bcintpdown", "bcextpup", "bcextpdown",               //80,82
			     "bclhemufup", "bclhemufdown", "bclhemurup", "bclhemurdown",       //84,86
			     "bcxdybup", "bcxdybdown", "bcxdycup", "bcxdycdown",               //88,90
			     "bcxwjcup", "bcxwjcdown",                                         //92
			     "topptup", "topptdown",                                           //96
			     "cp5up", "cp5down","mtopup", "mtopdown", "hdampup", "hdampdown",   //96,98,100
			       "jerup", "jerdown" //102
			     //"jecup", "jecdown"
  };

  const char *syst_2018[] = {"base", 
			     "pdfup", "pdfdown", "q2up", "q2down",                             //2,4    
			     "isrup", "isrdown", "fsrup", "fsrdown",                           //6,8
			     "puup", "pudown", "prefireup", "prefiredown",                     //10,12
			     "mueffup", "mueffdown", "eleeffup", "eleeffdown",                 //14,16
			     "pujetidup", "pujetiddown", "metup", "metdown",                   //18,20
			     "absmpfbup", "absmpfbdown", "abssclup", "absscldown",             //22,24
			     "absstatup", "absstatdown", "flavorqcdup", "flavorqcddown",       //26,28
			     "fragup", "fragdown", "timeptetaup", "timeptetadown",             //30,32
			     "pudatamcup", "pudatamcdown", "puptbbup", "puptbbdown",           //34,36 
			     "puptec1up", "puptec1down", "puptec2up", "puptec2down",           //38,40 
			     "pupthfup", "pupthfdown", "puptrefup", "puptrefdown",             //42,44 
			     "relfsrup", "relfsrdown", "relbalup", "relbaldown",               //46,48 
			     "relsampleup", "relsampledown", "reljerec1up", "reljerec1down",   //50,52 
			     "reljerec2up", "reljerec2down", "reljerhfup", "reljerhfdown",     //54,56 
			     "relptbbup", "relptbbdown", "relptec1up", "relptec1down",         //58,60 
			     "relptec2up", "relptec2down", "relpthfup", "relpthfdown",         //62,64 
			     "relstatecup", "relstatecdown", "relstatfsrup","relstatfsrdown",  //66,68 
			     "relstathfup", "relstathfdown",                                   //70
			     "singpiecalup", "singpiecaldown", "singpihcalup", "singpihcaldown", //72,74 
			     // CShapeCalib UL
			     "bcstatup", "bcstatdown", "bcjesup", "bcjesdown",                 //76,78   
			     "bcintpup", "bcintpdown", "bcextpup", "bcextpdown",               //80,82
			     "bclhemufup", "bclhemufdown", "bclhemurup", "bclhemurdown",       //84,86
			     "bcxdybup", "bcxdybdown", "bcxdycup", "bcxdycdown",               //88,90
			     "bcxwjcup", "bcxwjcdown",                                         //92
			     "topptup", "topptdown",                                           //96
			     "cp5up", "cp5down","mtopup", "mtopdown", "hdampup", "hdampdown",   //96,98,100
			       "jerup", "jerdown" //102
			     //"jecup", "jecdown"
  };

  // const char *syst_2016[] = {"base", 
  // 			     "pdfup", "pdfdown", "q2up", "q2down",                             //2,4    
  // 			     "isrup", "isrdown", "fsrup", "fsrdown",                           //6,8
  // 			     "puup", "pudown", "prefireup", "prefiredown",                     //10,12
  // 			     "mueffup", "mueffdown", "eleeffup", "eleeffdown",                 //14,16
  // 			     "pujetidup", "pujetiddown", "metup", "metdown",                   //18,20
  // 			     "jecup", "jecdown", "jerup", "jerdown",                           //22,24
  // 			     "stotpuup", "stotpudown", "stotrelup", "stotreldown",             //26,28
  // 			     "stotptup", "stotptdown", "stotscaleup", "stotscaledown",         //30,32
  // 			     "flavorqcdup", "flavorqcddown", "timeptetaup", "timeptetadown",   //34,36   
  // 			     // CShapeCalib UL
  // 			     "bcstatup", "bcstatdown", "bcjesup", "bcjesdown",                 //38,40   
  // 			     "bcintpup", "bcintpdown", "bcextpup", "bcextpdown",               //40,42
  // 			     "bclhemufup", "bclhemufdown", "bclhemurup", "bclhemurdown",       //44,46
  // 			     "bcxdybup", "bcxdybdown", "bcxdycup", "bcxdycdown",               //48,50
  // 			     "bcxwjcup", "bcxwjcdown",                                         //52
  // 			     "topptup", "topptdown",                                           //54
  // 			     "cp5up", "cp5down","mtopup", "mtopdown", "hdampup", "hdampdown"   //56,58,62
  // 			     //"jecup", "jecdown"
  // };
  
  // const char *syst_2017[] = {"base", 
  // 			     "pdfup", "pdfdown", "q2up", "q2down",                             //2,4    
  // 			     "isrup", "isrdown", "fsrup", "fsrdown",                           //6,8
  // 			     "puup", "pudown", "prefireup", "prefiredown",                     //10,12
  // 			     "mueffup", "mueffdown", "eleeffup", "eleeffdown",                 //14,16
  // 			     "pujetidup", "pujetiddown", "metup", "metdown",                   //18,20
  // 			     "jecup", "jecdown", "jerup", "jerdown",                           //22,24
  // 			     "stotpuup", "stotpudown", "stotrelup", "stotreldown",             //26,28
  // 			     "stotptup", "stotptdown", "stotscaleup", "stotscaledown",         //30,32
  // 			     "flavorqcdup", "flavorqcddown", "timeptetaup", "timeptetadown",   //34,36   
  // 			     // CShapeCalib UL
  // 			     "bcstatup", "bcstatdown", //"bcjesup", "bcjesdown",               //38,   
  // 			     "bcintpup", "bcintpdown", "bcextpup", "bcextpdown",               //40,42
  // 			     "bclhemufup", "bclhemufdown", "bclhemurup", "bclhemurdown",       //44,46
  // 			     "bcxdybup", "bcxdybdown", "bcxdycup", "bcxdycdown",               //48,50
  // 			     "bcxwjcup", "bcxwjcdown",                                         //52
  // 			     "topptup", "topptdown",                                           //54
  // 			     "cp5up", "cp5down","mtopup", "mtopdown", "hdampup", "hdampdown"   //56,58,60
  // };  

  // const char *syst_2018[] = {"base", 
  // 			     "pdfup", "pdfdown", "q2up", "q2down",                             //2,4    
  // 			     "isrup", "isrdown", "fsrup", "fsrdown",                           //6,8
  // 			     "puup", "pudown", "prefireup", "prefiredown",                     //10,12
  // 			     "mueffup", "mueffdown", "eleeffup", "eleeffdown",                 //14,16
  // 			     "pujetidup", "pujetiddown", "metup", "metdown",                   //18,20
  // 			     "jecup", "jecdown", "jerup", "jerdown",                           //22,24
  // 			     "stotpuup", "stotpudown", "stotrelup", "stotreldown",             //26,28
  // 			     "stotptup", "stotptdown", "stotscaleup", "stotscaledown",         //30,32
  // 			     "flavorqcdup", "flavorqcddown", "timeptetaup", "timeptetadown",   //34,36   
  // 			     // CShapeCalib UL
  // 			     "bcstatup", "bcstatdown", //"bcjesup", "bcjesdown",               //38,   
  // 			     "bcintpup", "bcintpdown", "bcextpup", "bcextpdown",               //40,42
  // 			     "bclhemufup", "bclhemufdown", "bclhemurup", "bclhemurdown",       //44,46
  // 			     "bcxdybup", "bcxdybdown", "bcxdycup", "bcxdycdown",               //48,50
  // 			     "bcxwjcup", "bcxwjcdown",                                         //52
  // 			     "topptup", "topptdown",                                           //54
  // 			     "cp5up", "cp5down","mtopup", "mtopdown", "hdampup", "hdampdown"   //56,58,60
  // };  
  
  //const char* inputdir = "/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v40_Syst/CBA_jetpt15-CombHist";
  //const char* inputdir = "/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v40_Syst/CBA_jecsyst-CombHist";
  const char* inputdir = "/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v40_Syst/CBA_metxycorr-CombHist";
  
  int isample = 11; isample--; //11 for TTbar,  8  for HplusM120
  //int isample = 8; isample--; //11 for TTbar,  8  for HplusM120
  //int isample = 13; isample--; //11 for TTbar,  8  for HplusM120
  int ibase = 1; ibase--;
  int isysdown = isysup ;
  //int isysup = 2; 
  isysup--;
  
  string lep = (isMu==1) ? "mu" : "ele" ;
  //const char *histname = Form("_kb_mjj_%s",lep.c_str());
  const char *histname = Form("_ct_ExcT_mjj_%s",lep.c_str());
  
  // const char *histnameup = (isysup<=16) ? Form("%s",histname) :  Form("%s_%s",histname,syst_2016[isysup]) ;
  // const char *histnamedown = (isysdown<=17) ? Form("%s",histname) :  Form("%s_%s",histname,syst_2016[isysdown]) ;
  
  // vector<string> lstShps;
  // for(int i=0;i<nShapes;i++)
  //   lstShps.push_back(listShapes[i]);
  
  if(year==2016)
    cout << "sample : "<<samples[isample] << ", hisname : " << histname << ", ibase : "<<ibase << ", sysup : "<< syst_2016[isysup] << ", sysdown : " << syst_2016[isysdown] << endl;
  else if(year==2017)
    cout << "sample : "<<samples[isample] << ", hisname : " << histname << ", ibase : "<<ibase << ", sysup : "<< syst_2017[isysup] << ", sysdown : " << syst_2017[isysdown] << endl;
  else if(year==2018)
    cout << "sample : "<<samples[isample] << ", hisname : " << histname << ", ibase : "<<ibase << ", sysup : "<< syst_2018[isysup] << ", sysdown : " << syst_2018[isysdown] << endl;

  
  TFile *finBase = TFile::Open(Form("%s/%d/all_%s.root",inputdir,year,samples[isample])); 
  TH1D *hBase = 0x0;
  TH1D *hSysUp = 0x0;
  TH1D *hSysDown = 0x0;

  if(year==2016){
    hBase = (TH1D *)finBase->Get(Form("%s/base/Iso/%s",samples[isample],histname));
    hSysUp = (TH1D *)finBase->Get(Form("%s/%s/Iso/%s",samples[isample],syst_2016[isysup],histname));
    hSysDown = (TH1D *)finBase->Get(Form("%s/%s/Iso/%s",samples[isample],syst_2016[isysdown],histname));
  }else if(year==2017){
    hBase = (TH1D *)finBase->Get(Form("%s/base/Iso/%s",samples[isample],histname));
    hSysUp = (TH1D *)finBase->Get(Form("%s/%s/Iso/%s",samples[isample],syst_2017[isysup],histname));
    hSysDown = (TH1D *)finBase->Get(Form("%s/%s/Iso/%s",samples[isample],syst_2017[isysdown],histname));
  }else if(year==2018){
    hBase = (TH1D *)finBase->Get(Form("%s/base/Iso/%s",samples[isample],histname));
    hSysUp = (TH1D *)finBase->Get(Form("%s/%s/Iso/%s",samples[isample],syst_2018[isysup],histname));
    hSysDown = (TH1D *)finBase->Get(Form("%s/%s/Iso/%s",samples[isample],syst_2018[isysdown],histname));
  }
  
  
  // hBase->Sumw2();
  // hSysUp->Sumw2();
  // hSysDown->Sumw2();

  int rebin = 100;
  hBase->Rebin(rebin);
  hSysUp->Rebin(rebin);
  hSysDown->Rebin(rebin);

  bool isShape = false;
  TString histUp = hSysUp->GetDirectory()->GetMotherDir()->GetName();
  TString histDown = hSysDown->GetDirectory()->GetMotherDir()->GetName();
  
  for(int i=0;i<nShapes;i++)
    if(histUp.Contains(listShapes[i]) or histDown.Contains(listShapes[i])) isShape = true ;
  
  if(isShape){
    hSysUp->Scale(hBase->Integral()/hSysUp->Integral());
    hSysDown->Scale(hBase->Integral()/hSysDown->Integral());
    cout << "Using shape comparison " << endl;
  }
  
  Double_t error_frac = max(fabs(hSysUp->Integral() - hBase->Integral()), fabs(hBase->Integral() - hSysDown->Integral()))/hBase->Integral();
  TH1D *hRelErrUp = (TH1D *)hBase->Clone("hRelErrUp");
  TH1D *hRelErrDown = (TH1D *)hBase->Clone("hRelErrDown");
  for(int ibin=1; ibin<hRelErrUp->GetNbinsX(); ibin++){
    //cout<<"ibin : "<<ibin<<", Error Frac : "<<error_frac<<endl;
    hRelErrUp->SetBinContent(ibin, 1+error_frac);
    hRelErrUp->SetBinError(ibin, 0.1*error_frac);
    hRelErrDown->SetBinContent(ibin, 1.-error_frac);
    hRelErrDown->SetBinError(ibin, 0.1*error_frac);
  }
  hRelErrUp->SetTitle(Form("Max. Unc. %5.3lf",(1+error_frac)));

  TH1D *hupbynom = (TH1D *)hSysUp->Clone("hupbynom");
  hupbynom->Divide(hBase);
  TH1D *hdownbynom = (TH1D *)hSysDown->Clone("hdownbynom");
  hdownbynom->Divide(hBase);
  ModifyUpDownHisto(hBase, hSysUp, hSysDown, hupbynom, hdownbynom);
  
  double maxUp = 0.;
  double maxDown = 0.;
  double maxvalbin = 0.0;
  for(int ibin=1;ibin<=hBase->GetNbinsX();ibin++){
    if(hBase->GetXaxis()->GetBinCenter(ibin)<15.0 or hBase->GetXaxis()->GetBinCenter(ibin)>165.0) continue;
    double upBin = TMath::Abs(hSysUp->GetBinContent(ibin));
    double downBin = TMath::Abs(hSysDown->GetBinContent(ibin));
    double baseBin = TMath::Abs(hBase->GetBinContent(ibin));
    double fracBase = baseBin/hBase->Integral(); //to avoid edge bins that contains less than 1% of total yield
    //if(TMath::AreEqualAbs(upBin,0.0,1.e-5) or TMath::AreEqualAbs(downBin,0.0,1.e-5) or TMath::AreEqualAbs(baseBin,0.0,1.e-5) or fracBase<0.03) continue;
    //if(TMath::AreEqualAbs(upBin,0.0,1.e-5) or TMath::AreEqualAbs(downBin,0.0,1.e-5) or TMath::AreEqualAbs(baseBin,0.0,1.e-5)) continue;
    double ratioUp = (baseBin>upBin) ?  upBin/baseBin : baseBin/upBin;
    double ratioDown = (baseBin>downBin) ?  downBin/baseBin : baseBin/downBin;
    //cout << "binX : " << hBase->GetXaxis()->GetBinCenter(ibin) << ", ratioUp : " << ratioUp << ", ratioDown: " << ratioDown << endl;
    double fracUp = 1.0 - ratioUp;
    double fracDown = 1.0 - ratioDown;
    maxvalbin = (fracUp>fracDown)?fracUp:fracDown;
    // maxUp = (fracUp>maxUp)?fracUp:maxUp;
    // maxDown = (fracDown>maxDown)?fracDown:maxDown;
    maxUp = (maxvalbin>maxUp)?maxvalbin:maxUp;
  }
  double maxupdown = (maxUp>maxDown)?maxUp:maxDown;
  double errorP = 1.1*maxupdown;
  cout << "maxupdown: " << errorP << endl;
  
  hBase->SetLineColor(kRed);
  hSysUp->SetLineColor(kBlue);
  hSysDown->SetLineColor(kGreen+1);
  hRelErrUp->SetLineColor(kMagenta);
  hRelErrDown->SetLineColor(kMagenta);
    
  hBase->SetLineWidth(2);
  hSysUp->SetLineWidth(2);
  hSysDown->SetLineWidth(2);
  hRelErrUp->SetLineWidth(2);
  hRelErrDown->SetLineWidth(2);

  TLegend *leg = new TLegend(0.6729323,0.753838,0.9974937,0.9957356);
  leg->SetFillColor(10);
  //leg->SetHeader("m_{H^{+}} = 120 GeV, #mu + jets (2016)");
  //leg->SetHeader("m_{H^{+}} = 120 GeV, #it{e} + jets (2016)");
  leg->SetHeader(Form("%s : %s (%d)",samples[isample],histname,year));
  if(year==2016){
    leg->AddEntry(hSysUp, Form("%s",syst_2016[isysup]) ,"lfp");
    leg->AddEntry(hBase, Form("%s",syst_2016[ibase]) ,"lfp");
    leg->AddEntry(hSysDown, Form("%s",syst_2016[isysdown]) ,"lfp");
  }else if(year==2017){
    leg->AddEntry(hSysUp, Form("%s",syst_2017[isysup]) ,"lfp");
    leg->AddEntry(hBase, Form("%s",syst_2017[ibase]) ,"lfp");
    leg->AddEntry(hSysDown, Form("%s",syst_2017[isysdown]) ,"lfp");
  }else if(year==2018){
    leg->AddEntry(hSysUp, Form("%s",syst_2018[isysup]) ,"lfp");
    leg->AddEntry(hBase, Form("%s",syst_2018[ibase]) ,"lfp");
    leg->AddEntry(hSysDown, Form("%s",syst_2018[isysdown]) ,"lfp");
  }
  //leg->AddEntry(hRelErrUp, Form("total uncertainty band") ,"lfp");
  leg->AddEntry((TObject*)0, Form("max. unc. : %4.2lf",100.*maxupdown),"");

  double masspoint = (isample==7)?120.:85.0;
  double upbincontent = hSysUp->GetBinContent(hSysUp->FindBin(masspoint));
  double downbincontent = hSysDown->GetBinContent(hSysDown->FindBin(masspoint));
  double maxbincontent = (upbincontent>downbincontent)?upbincontent:downbincontent;
  hSysUp->SetMaximum(1.2*maxbincontent);
  hSysUp->SetTitle("");
  hSysUp->GetXaxis()->SetRangeUser(15.,165.);
  PlotRatio(hSysUp, hBase, errorP, "c1");
  PlotRatio(hSysDown, hBase, errorP, "c1");
  leg->Draw();

  
  TCanvas *c1 = (TCanvas *)gROOT->GetListOfCanvases()->FindObject("c1");
  if(year==2016){
    string s = syst_2016[isysdown];
    string systname = s.substr(0,s.find("down"));
    c1->SaveAs(Form("%s_%s%s_sys_%d.pdf",lep.c_str(),systname.c_str(),histname,year));
    c1->SaveAs(Form("%s_%s%s_sys_%d.png",lep.c_str(),systname.c_str(),histname,year));
  }else if(year==2017){
    string s = syst_2017[isysdown];
    string systname = s.substr(0,s.find("down"));
    c1->SaveAs(Form("%s_%s%s_sys_%d.pdf",lep.c_str(),systname.c_str(),histname,year));
    c1->SaveAs(Form("%s_%s%s_sys_%d.png",lep.c_str(),systname.c_str(),histname,year));
  }else if(year==2018){
    string s = syst_2018[isysdown];
    string systname = s.substr(0,s.find("down"));
    c1->SaveAs(Form("%s_%s%s_sys_%d.pdf",lep.c_str(),systname.c_str(),histname,year));
    c1->SaveAs(Form("%s_%s%s_sys_%d.png",lep.c_str(),systname.c_str(),histname,year));
  }
  
  c1->SaveAs("output.pdf");
  
  return true;
}

int PlotRatio(TH1D *h1, TH1D *h2, float maxmin, const char *cname)
{
  //cout<<"h1 name : "<<h1->GetName() <<", Directory : " << h1->GetDirectory()->GetMotherDir()->GetName() << endl;

  TCanvas *canvas = (TCanvas *)gROOT->GetListOfCanvases()->FindObject(cname);
  
  if(!canvas){
    TCanvas *c = new TCanvas(cname, cname, 800, 800);
 
    // Upper plot will be in pad1
    TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
    pad1->SetBottomMargin(0.01); // Upper and lower plot are joined
    //pad1->SetGridx();         // Vertical grid
    pad1->Draw();             // Draw the upper pad: pad1
    pad1->cd();               // pad1 becomes the current pad
    pad1->SetTickx();
    pad1->SetTicky();
    h1->SetStats(0);          // No statistics on upper plot
    h1->Draw("hist");               // Draw h1
    h2->Draw("hist same");         // Draw h2 on top of h1

    // Define the ratio plot
    TH1D *h3 = (TH1D*)h1->Clone("h3");

#if ROOT_VERSION_CODE >= ROOT_VERSION(6,8,0)
    // Avoid the first label (0) to be clipped.
    TAxis *axis = h1->GetYaxis();
    axis->ChangeLabel(1, -1, -1, -1, -1, -1, " ");
    axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    axis->SetLabelSize(15);
#else
    // Do not draw the Y axis label on the upper plot and redraw a small
    // axis instead, in order to avoid the first label (0) to be clipped.
    h1->GetYaxis()->SetLabelSize(0.);
    TGaxis *axis = new TGaxis( -5, 20, -5, 220, 20,220,510,"");
    axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    axis->SetLabelSize(15);
    axis->Draw();
#endif
 
    // lower plot will be in pad
    c->cd();          // Go back to the main canvas before defining pad2
    TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
    pad2->SetTopMargin(0.1);
    pad2->SetBottomMargin(0.2);
    //pad2->SetGridx(); // vertical grid
    pad2->SetGridy(); // vertical grid
    pad2->Draw();
    pad2->cd();       // pad2 becomes the current pad
    pad2->SetTickx();
    pad2->SetTicky();
 
    h3->SetLineColor(h1->GetLineColor());

    h3->Sumw2();
    h3->SetStats(0);      // No statistics on lower plot
    h3->Divide(h2);
    
    // h3->SetMinimum(0.8);  // Define Y ..
    // h3->SetMaximum(1.2); // .. range

    h3->SetMinimum(0.88);  // Define Y ..
    h3->SetMaximum(1.12); // .. range

    // h3->SetMinimum(0.5);  // Define Y ..
    // h3->SetMaximum(1.5); // .. range

    // h3->SetMinimum(1-maxmin);  // Define Y ..
    // h3->SetMaximum(1+maxmin); // .. range

    // cout << "h3->GetBinContent(h3->FindBin(80.0))" << h3->GetBinContent(h3->FindBin(80.0)) << endl;
    // h3->SetMaximum(1+2*(h3->GetBinContent(h3->FindBin(80.0))-1.));
    // h3->SetMinimum(1-2*(h3->GetBinContent(h3->FindBin(80.0))-1.));

    // float minX = 20.;
    // float maxX = 165.;
    // int minbinX = h3->FindBin(minX);
    // int maxbinX = h3->FindBin(maxX);
    // double integral = h3->Integral(minbinX,maxbinX);
    // //double avgBinContent = integral/double(maxbinX-minbinX);
    // //double avgBinContent = integral/double(maxX-minX);
    // //cout << "integral : " << integral << ", (Avg bin - 1) :  " << TMath::Abs(avgBinContent-1) << endl;
    // // double maxZoom = TMath::Abs(avgBinContent-1)<0.08 ? TMath::Abs(avgBinContent-1) : 0.2/1.2 ;
    // // cout << "maxZoom " << maxZoom << endl;
    // // cout << "Max:Min " << (1+1.2*maxZoom) << " : " << (1-1.2*maxZoom) << endl;
    // // h3->SetMaximum(1+1.2*maxZoom);
    // // h3->SetMinimum(1-1.2*maxZoom);

    // int maxBin = 0;
    // double maxDiff = -1.;
    // cout<<" h3->GetNbinsX() : " << h3->GetNbinsX() << endl;
    // for (Int_t i=int(minX); i<=int(maxX); ++i) {
    //   int bin = h3->FindBin(i);
    //   if (TMath::Abs(h3->GetBinContent(bin)-1)>=maxDiff) {
    // 	maxDiff = TMath::Abs(h3->GetBinContent(bin)-1);
    // 	maxBin  = bin;
    //   }
    // }
    // cout << "h3->GetBinContent(maxBin) : " << h3->GetBinContent(maxBin) << ", maxDiff : " << maxDiff << ", bincenter : " << h3->GetXaxis()->GetBinCenter(maxBin) << endl;
    // h3->SetMaximum(1+1.2*maxDiff);
    // h3->SetMinimum(1-1.2*maxDiff);
    
    //h3->SetMarkerStyle(21);
    h3->Draw("ep");       // Draw the ratio plot

    
    // h1 settings
    //h1->SetLineColor(kBlue+1);
    //h1->SetLineWidth(2);
 
    // Y axis h1 plot settings
    h1->GetYaxis()->SetTitle(Form("Entries / %1.0f GeV",h1->GetBinWidth(2)));
    h1->GetYaxis()->SetTitleSize(20);
    h1->GetYaxis()->SetTitleFont(43);
    h1->GetYaxis()->SetTitleOffset(1.55);
 
    // h2 settings
    //h2->SetLineColor(kRed);
    //h2->SetLineWidth(2);
 
    // Ratio plot (h3) settings
    h3->SetTitle(""); // Remove the ratio title
 
    // Y axis ratio plot settings
    h3->GetYaxis()->SetTitle("#frac{unc}{nominal}");
    h3->GetYaxis()->SetNdivisions(6,5,0);
    h3->GetYaxis()->SetTitleSize(20);
    h3->GetYaxis()->SetTitleFont(43);
    h3->GetYaxis()->SetTitleOffset(1.55);
    h3->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    h3->GetYaxis()->SetLabelSize(15);
    h3->GetYaxis()->CenterTitle();
    
    // X axis ratio plot settings
    h3->GetXaxis()->SetTitle("m_{jj} (GeV)");
    h3->GetXaxis()->SetTitleSize(20);
    h3->GetXaxis()->SetTitleFont(43);
    h3->GetXaxis()->SetTitleOffset(0.8);
    h3->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    h3->GetXaxis()->SetLabelSize(15);
    
    pad1->cd();

    cout<<" nof canvas primitives " << c->GetListOfPrimitives()->GetEntries() << endl ;
    
  }else {

    TPad *pad1 = (TPad *)canvas->GetListOfPrimitives()->FindObject("pad1") ;
    pad1->cd();
    
    h1->Draw("hist same");             
    h2->Draw("hist same");         
    
    TPad *pad2 = (TPad *)canvas->GetListOfPrimitives()->FindObject("pad2") ;
    pad2->cd();
    

    TH1D *h3 = (TH1D*)h1->Clone("h3");
    h3->SetLineColor(h1->GetLineColor());
    h3->Sumw2();
    h3->SetStats(0);      // No statistics on lower plot
    h3->Divide(h2);
    h3->Draw("ep same");       // Draw the ratio plot
    pad1->cd();
  }

  return true;
}


int ModifyUpDownHisto(TH1D*& hnom, TH1D*& hup, TH1D*& hdown, TH1D *hupbynom, TH1D *hdownbynom)
{
  
  for(int ibin=1; ibin<hupbynom->GetNbinsX(); ibin++){
    double bindiff = TMath::Abs(hupbynom->GetBinContent(ibin) - hdownbynom->GetBinContent(ibin));
    double binerror = hupbynom->GetBinError(ibin) + hdownbynom->GetBinError(ibin);
    double bindiff_up = TMath::Abs(hupbynom->GetBinContent(ibin) - 1.0);
    double bindiff_down = TMath::Abs(hdownbynom->GetBinContent(ibin) - 1.0);
    // cout << hupbynom->GetName() << " at bin : " << ibin << ", at x = " << hupbynom->GetXaxis()->GetBinCenter(ibin) << " has bindiff_up: " << bindiff_up << " has content: " << hupbynom->GetBinContent(ibin) << endl;
    // cout << hdownbynom->GetName() << " at bin : " << ibin << ", at x = " << hdownbynom->GetXaxis()->GetBinCenter(ibin) << " has bindiff_down: " << bindiff_down << " has content: " << hdownbynom->GetBinContent(ibin) << endl;
    // cout << hnom->GetName() << " at bin : " << ibin << ", at x = " << hnom->GetXaxis()->GetBinCenter(ibin) << " has content: " << hnom->GetBinContent(ibin) << endl;
    if(TMath::AreEqualAbs(hup->GetBinContent(ibin),0.0,1e-5)  or TMath::AreEqualAbs(hdown->GetBinContent(ibin),0.0,1e-5) or bindiff_down>1.0 or bindiff_up>1.0){
      //cout << "ZERO for " << hupbynom->GetName() << " at bin : " << ibin << ", at x = " << hupbynom->GetXaxis()->GetBinCenter(ibin) << " has bindiff: " << bindiff << " and binerror: " << binerror << endl ;
      hup->SetBinContent(ibin, hnom->GetBinContent(ibin));
      hup->SetBinError(ibin, hnom->GetBinError(ibin));
      hdown->SetBinContent(ibin, hnom->GetBinContent(ibin));
      hdown->SetBinError(ibin, hnom->GetBinError(ibin));
    }else{
      if(bindiff_up>bindiff_down){
        hdown->SetBinContent(ibin, (2.0-hupbynom->GetBinContent(ibin))*hnom->GetBinContent(ibin));
      }else{
        hup->SetBinContent(ibin, (2.0-hdownbynom->GetBinContent(ibin))*hnom->GetBinContent(ibin));
      }//content symmetric condition   
    }//binerror condn
  }
  return true;
  
}
