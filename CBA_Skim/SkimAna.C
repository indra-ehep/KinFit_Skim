/**********************************************************************
 Created on : 14/07/2021
 Purpose    : Analyse the Skim tree.
              (format adapted from h1analysis)
 Author     : Indranil Das, Visiting Fellow
 Email      : indranil.das@cern.ch | indra.ehep@gmail.com
**********************************************************************/

#include <fstream>
#include <string>
#include <cstring>

#include "SkimAna.h"
#include "TH2.h"
#include "TF1.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TPaveStats.h"
#include "TMath.h"
#include "TProof.h"


Int_t SkimAna::CreateHistoArrays()
{
  // Create the histogram arrays
  
  fNSyst = 19;
  fNHist = 2*fNSyst ; 

  fNTestHist = 75;
  hCheck = new TH1D*[fNTestHist+fNSyst];
  TDirectory *savedir = gDirectory;
  savedir->cd();
  fFile[0]->cd();

  hCheck[0] = new TH1D("_cutflow_data", "_cutflow_data", 10, 0, 10);
  hCheck[1] = new TH1D("_cutflowUS_mu", "_cutflowUS_mu", 10, 0, 10);
  hCheck[2] = new TH1D("_cutflow_mu", "_cutflow_mu", 10, 0, 10);
  hCheck[3] = new TH1D("_cutflowUS_ele", "_cutflowUS_ele", 10, 0, 10);
  hCheck[4] = new TH1D("_cutflow_ele", "_cutflow_ele", 10, 0, 10);
  hCheck[5] = new TH1D("_cutflow5", "_cutflow5", 10, 0, 10);
  
  hCheck[6] = new TH1D("_sampleWeight","_sampleWeight",2000, -10, 10);
  hCheck[7] = new TH1D("_PUWeight","_PUWeight", 2000, -10, 10);
  hCheck[8] = new TH1D("_prefireWeight","_prefireWeight",2000, -10, 10);
  hCheck[9] = new TH1D("_muEffWeight","_muEffWeight",2000, -10, 10);
  hCheck[10] = new TH1D("_eleEffWeight","_eleEffWeight",2000, -10, 10);
  hCheck[11] = new TH1D("_btagWeight_1a","_btagWeight_1a",2000, -10, 10);
  hCheck[12] = new TH1D("_btagWeight_1a_b_Do","_btagWeight_1a_b_Do",2000, -10, 10);
  hCheck[13] = new TH1D("_btagWeight_1a_b_Up","_btagWeight_1a_b_Up",2000, -10, 10);
  hCheck[14] = new TH1D("_btagWeight_1a_l_Do","_btagWeight_1a_l_Do",2000, -10, 10);
  hCheck[15] = new TH1D("_btagWeight_1a_l_Up","_btagWeight_1a_l_Up",2000, -10, 10);
  hCheck[16] = new TH1D("_eleEffWeight_Do","_eleEffWeight_Do",2000, -10, 10);
  hCheck[17] = new TH1D("_eleEffWeight_Up","_eleEffWeight_Up",2000, -10, 10);
  hCheck[18] = new TH1D("_FSRweight_Do","_FSRweight_Do",2000, -10, 10);
  hCheck[19] = new TH1D("_FSRweight_Up","_FSRweight_Up",2000, -10, 10);
  hCheck[20] = new TH1D("_ISRweight_Do","_ISRweight_Do",2000, -10, 10);
  hCheck[21] = new TH1D("_ISRweight_Up","_ISRweight_Up",2000, -10, 10);
  hCheck[22] = new TH1D("_muEffWeight_Do","_muEffWeight_Do",2000, -10, 10);
  hCheck[23] = new TH1D("_muEffWeight_Up","_muEffWeight_Up",2000, -10, 10);
  hCheck[24] = new TH1D("_pdfweight_Do","_pdfweight_Do",2000, -10, 10);
  hCheck[25] = new TH1D("_pdfweight_Up","_pdfweight_Up",2000, -10, 10);
  hCheck[26] = new TH1D("_PUweight_Do","_PUweight_Do",2000, -10, 10);
  hCheck[27] = new TH1D("_PUweight_Up","_PUweight_Up",2000, -10, 10);
  hCheck[28] = new TH1D("_q2weight_Do","_q2weight_Do",2000, -10, 10);
  hCheck[29] = new TH1D("_q2weight_Up","_q2weight_Up",2000, -10, 10);
  hCheck[30] = new TH1D("_lb_pt_mu","_lb_pt_mu",100, 0., 1000.);
  hCheck[31] = new TH1D("_lb_eta_mu","_lb_eta_mu", 30, -3., 3.);
  hCheck[32] = new TH1D("_lb_phi_mu","_lb_phi_mu", 35, -3.5, 3.5);
  hCheck[33] = new TH1D("_lb_pt_ele","_lb_pt_ele",100, 0., 1000.);
  hCheck[34] = new TH1D("_lb_eta_ele","_lb_eta_ele", 30, -3., 3.);
  hCheck[35] = new TH1D("_lb_phi_ele","_lb_phi_ele", 35, -3.5, 3.5);
  hCheck[36] = new TH1D("_lb_pt_mu_jets","_lb_pt_mu_jets",100, 0., 1000.);
  hCheck[37] = new TH1D("_lb_eta_mu_jets","_lb_eta_mu_jets", 30, -3., 3.);
  hCheck[38] = new TH1D("_lb_phi_mu_jets","_lb_phi_mu_jets", 35, -3.5, 3.5);
  hCheck[39] = new TH1D("_lb_pt_ele_jets","_lb_pt_ele_jets",100, 0., 1000.);
  hCheck[40] = new TH1D("_lb_eta_ele_jets","_lb_eta_ele_jets", 30, -3., 3.);
  hCheck[41] = new TH1D("_lb_phi_ele_jets","_lb_phi_ele_jets", 35, -3.5, 3.5);
  hCheck[42] = new TH1D("_lb_pt_mu_met","_lb_pt_mu_met",100, 0., 1000.);
  hCheck[43] = new TH1D("_lb_phi_mu_met","_lb_phi_mu_met", 35, -3.5, 3.5);
  hCheck[44] = new TH1D("_lb_pt_ele_met","_lb_pt_ele_met",100, 0., 1000.);
  hCheck[45] = new TH1D("_lb_phi_ele_met","_lb_phi_ele_met", 35, -3.5, 3.5);
  hCheck[46] = new TH1D("_lb_njet_mu","_lb_njet_mu", 20, 0., 20);
  hCheck[47] = new TH1D("_lb_nbjet_mu","_lb_nbjet_mu", 20, 0., 20);
  hCheck[48] = new TH1D("_lb_njet_ele","_lb_njet_ele", 20, 0., 20);
  hCheck[49] = new TH1D("_lb_nbjet_ele","_lb_nbjet_ele", 20, 0., 20);
  hCheck[50] = new TH1D("_kb_pt_mu","_kb_pt_mu",100, 0., 1000.);
  hCheck[51] = new TH1D("_kb_eta_mu","_kb_eta_mu", 30, -3., 3.);
  hCheck[52] = new TH1D("_kb_phi_mu","_kb_phi_mu", 35, -3.5, 3.5);
  hCheck[53] = new TH1D("_kb_pt_ele","_kb_pt_ele",100, 0., 1000.);
  hCheck[54] = new TH1D("_kb_eta_ele","_kb_eta_ele", 30, -3., 3.);
  hCheck[55] = new TH1D("_kb_phi_ele","_kb_phi_ele", 35, -3.5, 3.5);
  hCheck[56] = new TH1D("_kb_pt_mu_jets","_kb_pt_mu_jets",100, 0., 1000.);
  hCheck[57] = new TH1D("_kb_eta_mu_jets","_kb_eta_mu_jets", 30, -3., 3.);
  hCheck[58] = new TH1D("_kb_phi_mu_jets","_kb_phi_mu_jets", 35, -3.5, 3.5);
  hCheck[59] = new TH1D("_kb_pt_ele_jets","_kb_pt_ele_jets",100, 0., 1000.);
  hCheck[60] = new TH1D("_kb_eta_ele_jets","_kb_eta_ele_jets", 30, -3., 3.);
  hCheck[61] = new TH1D("_kb_phi_ele_jets","_kb_phi_ele_jets", 35, -3.5, 3.5);
  hCheck[62] = new TH1D("_kb_pt_mu_met","_kb_pt_mu_met",100, 0., 1000.);
  hCheck[63] = new TH1D("_kb_phi_mu_met","_kb_phi_mu_met", 35, -3.5, 3.5);
  hCheck[64] = new TH1D("_kb_pt_ele_met","_kb_pt_ele_met",100, 0., 1000.);
  hCheck[65] = new TH1D("_kb_phi_ele_met","_kb_phi_ele_met", 35, -3.5, 3.5);
  hCheck[66] = new TH1D("_kb_njet_mu","_kb_njet_mu", 20, 0., 20);
  hCheck[67] = new TH1D("_kb_nbjet_mu","_kb_nbjet_mu", 20, 0., 20);
  hCheck[68] = new TH1D("_kb_njet_ele","_kb_njet_ele", 20, 0., 20);
  hCheck[69] = new TH1D("_kb_nbjet_ele","_kb_nbjet_ele", 20, 0., 20);
  hCheck[70] = new TH1D("_kb_mjj_mu","_kb_mjj_mu", 50, 0., 250);
  hCheck[71] = new TH1D("_kb_mjj_ele","_kb_mjj_ele", 50, 0., 250);
  hCheck[72] = new TH1D("_kb_mjj_bf_mu","_kb_mjj_bf_mu", 50, 0., 250);
  hCheck[73] = new TH1D("_kb_mjj_bf_ele","_kb_mjj_bf_ele", 50, 0., 250);
  hCheck[74] = new TH1D("_topPtReweight","_topPtReweight",2000, -10, 10);

  for(int isyst=0;isyst<fNSyst;isyst++)
    hCheck[fNTestHist+isyst] = new TH1D(Form("weight_%d",isyst), Form("weight_%d",isyst),2000, -10, 10);

  hMinChi2_mu = new TH1F("hMinChi2_mu","1^{st} minimum",500,0,100.0); 
  h2MinChi2_mu = new TH1F("h2MinChi2_mu","2^{nd} minimum",500,0,100.0); 
  h3MinChi2_mu = new TH1F("h3MinChi2_mu","3^{rd} minimum",500,0,100.0); 
  h4MinChi2_mu = new TH1F("h4MinChi2_mu","4^{th} minimum",500,0,100.0); 
  h5MinChi2_mu = new TH1F("h5MinChi2_mu","5^{th} minimum",500,0,100.0); 

  hMinChi2_ele = new TH1F("hMinChi2_ele","1^{st} minimum",500,0,100.0); 
  h2MinChi2_ele = new TH1F("h2MinChi2_ele","2^{nd} minimum",500,0,100.0); 
  h3MinChi2_ele = new TH1F("h3MinChi2_ele","3^{rd} minimum",500,0,100.0); 
  h4MinChi2_ele = new TH1F("h4MinChi2_ele","4^{th} minimum",500,0,100.0); 
  h5MinChi2_ele = new TH1F("h5MinChi2_ele","5^{th} minimum",500,0,100.0); 

  savedir->cd();

  fFile[1]->cd();
  outputTree = new TTree("Kinfit_Reco","Kinfit_Reco");
  outputTree->SetAutoSave();
  InitOutBranches();
  
  savedir->cd();

  return true;
}

//_____________________________________________________________________________
void SkimAna::GetArguments(){
  
  TString option = GetOption();
  //Info("GetArguments","ending SkimAna with process option: %s", option.Data());
  
  Ssiz_t from = 0;
  TString tok;
  // Now analyze the arguments
  while (option.Tokenize(tok , from , "|")) {
    if(tok.BeginsWith("sample"))
      fSample = ((TObjString *) (tok.Tokenize("="))->At(1))->GetString();
    if(tok.BeginsWith("input"))
      fFileName = ((TObjString *) (tok.Tokenize("="))->At(1))->GetString();
    if(tok.BeginsWith("year"))
      fYear = (((TObjString *) (tok.Tokenize("="))->At(1))->GetString()).Atoi();
    if(tok.BeginsWith("mode"))
      fMode = ((TObjString *) (tok.Tokenize("="))->At(1))->GetString();
    if(tok.BeginsWith("index"))
      fIndex = (((TObjString *) (tok.Tokenize("="))->At(1))->GetString()).Atoi();
    if(tok.BeginsWith("total"))
      fTotal = (((TObjString *) (tok.Tokenize("="))->At(1))->GetString()).Atoi();
    if(tok.BeginsWith("syst"))
      fSyst = ((TObjString *) (tok.Tokenize("="))->At(1))->GetString();
    if(tok.BeginsWith("aod"))
      isNanoAOD = (((TObjString *) (tok.Tokenize("="))->At(1))->GetString() == "mini") ? false : true;
  }
  fSyst.ToLower();
  fIndex++;

  if(fSample.BeginsWith("Data")){
    fSampleDir = "data_obs";
    isData = true;
  }else{
    fSampleDir = fSample;
    isData = false;
  }
  
  TString hostname = gSystem->HostName();
  if(fMode.Contains("proof")){
    if(hostname.BeginsWith("Indra-Rjn"))
      fBasePath = "/Data/CMS-Analysis/NanoAOD-Analysis";
    else if(hostname.BeginsWith("lxplus"))
      fBasePath = "/afs/cern.ch/user/i/idas/CMS-Analysis/NanoAOD-Analysis";
    else if(hostname.BeginsWith("ui"))
      fBasePath = "/home/idas/t3store3/NanoAOD-Analysis";
    else if(hostname.BeginsWith("lnx3"))
      fBasePath = "/home/indra/CMS-Analysis/NanoAOD-Analysis";
    fBasePath += "/SkimAna";
  }else{
    fBasePath = gSystem->pwd();
  }
  
}
//_____________________________________________________________________________
void SkimAna::SelectSyst()
{
  
  puvar012_g		= 1 ;		// 0:down, 1:norm, 2:up
  mueffvar012_g		= 1 ;		// 0:down, 1:norm, 2:up
  eleeffvar012_g	= 1 ;		// 0:down, 1:norm, 2:up
  jecvar012_g		= 1 ;		// 0:down, 1:norm, 2:up
  jervar012_g		= 1 ;		// 0:down, 1:norm, 2:up
  btagbvar012_g		= 1 ;		// 0:down, 1:norm, 2:up
  btaglvar012_g		= 1 ;		// 0:down, 1:norm, 2:up
  pdfvar012_g		= 1 ;		// 0:down, 1:norm, 2:up
  q2var012_g		= 1 ;		// 0:down, 1:norm, 2:up
  fsrvar012_g		= 1 ;		// 0:down, 1:norm, 2:up
  isrvar012_g		= 1 ;		// 0:down, 1:norm, 2:up
  prefirevar012_g	= 1 ;           // 0:down, 1:norm, 2:up
  btagSystType		= "central" ;
  
  if (fSyst == "base"){

    systType = kBase ;

  } else if (fSyst == "puup") {

    systType = kPUUp;
    puvar012_g = 2;

  } else if (fSyst == "pudown") {

    systType = kPUDown;
    puvar012_g = 0;

  } else if (fSyst == "mueffup") {

    systType = kMuEffUp;
    mueffvar012_g = 2;

  } else if (fSyst == "mueffdown") {

    systType = kMuEffDown;
    mueffvar012_g = 0;

  } else if (fSyst == "eleeffup") {

    systType = kEleEffUp;
    eleeffvar012_g = 2;  

  } else if (fSyst == "eleeffdown") {

    systType = kEleEffDown;
    eleeffvar012_g = 0;  

  } else if (fSyst == "jecup") {

    systType = kJECUp;
    jecvar012_g = 2;      

  } else if (fSyst == "jecdown") {

    systType = kJECDown;
    jecvar012_g = 0;      

  } else if (fSyst == "jerup") {

    systType = kJERUp;
    jervar012_g = 2;      
    
  } else if (fSyst == "jerdown") {

    systType = kJERDown;
    jervar012_g = 0;      

  } else if (fSyst == "btagbup") {

    systType = kBTagbUp;
    btagbvar012_g = 2;      
    btagSystType = "b_up";

  } else if (fSyst == "btagbdown") {

    systType = kBTagbDown;
    btagbvar012_g  = 0;   
    btagSystType = "b_down";    

  } else if (fSyst == "btaglup") {

    systType = kBTaglUp;
    btaglvar012_g = 2;    
    btagSystType = "l_up";  
  
  } else if (fSyst == "btagldown") {

    systType = kBTaglDown;
    btaglvar012_g = 0;
    btagSystType = "l_down";      
    
  } else if (fSyst == "pdfup") {

    systType = kPdfUp;
    pdfvar012_g = 2;      
  
  } else if (fSyst == "pdfdown") {

    systType = kPdfDown;
    pdfvar012_g = 0;      
  
  } else if (fSyst == "q2up") {

    systType = kQ2Up;
    q2var012_g = 2;      
  
  } else if (fSyst == "q2down") {

    systType = kQ2Down;
    q2var012_g = 0;      
  
  } else if (fSyst == "fsrup") {

    systType = kFsrUp;
    fsrvar012_g = 2;      
  
  } else if (fSyst == "fsrdown") {

    systType = kFsrDown;
    fsrvar012_g = 0;      
    
  } else if (fSyst == "isrup") {

    systType = kIsrUp;
    isrvar012_g = 2;      
    
  } else if (fSyst == "isrdown") {

    systType = kIsrDown;
    isrvar012_g = 0;      
    
  } else if (fSyst == "prefireup") {

    systType = kPreFireUp;
    prefirevar012_g = 2;      
    
  } else if (fSyst == "prefiredown") {
    
    systType = kPreFireDown;
    prefirevar012_g = 0;      
    
  }

  // if(systematicType=="elesmear_down") {elesmear012_g=0;selector->elesmearLevel=0; isSystematicRun = true;}
  // if(systematicType=="elesmear_up")   {elesmear012_g=2;selector->elesmearLevel=2; isSystematicRun = true;}
  // if(systematicType=="elescale_down") {elescale012_g=0;selector->elescaleLevel=0; isSystematicRun = true;}
  // if(systematicType=="elescale_up")   {elescale012_g=2;  selector->elescaleLevel=2; isSystematicRun = true;}
  // if( systematicType=="musmear_up") {musmear012_g = 2; isSystematicRun = true;}
  // if( systematicType=="musmear_do") {musmear012_g = 0; isSystematicRun = true;}

  
}

//_____________________________________________________________________________
void SkimAna::SetTrio()
{
  
  //event = new EventTree(nFiles, false, Form("%d",fYear), isData, fileNames);
  event = new EventTree();
  selector = new Selector();    
  evtPick = new EventPick("");
  
  selector->year = Form("%d",fYear);
  selector->looseJetID = false;
  selector->smearJetPt = true; // default setting was false for cutflow and for prining jet pt
  selector->useDeepCSVbTag = (isNanoAOD) ? true : false ;
  selector->JECsystLevel = jecvar012_g;
  selector->JERsystLevel = jervar012_g;
  selector->isNanoAOD = isNanoAOD ;
  
  selector->mu_Pt_cut = 30.;
  selector->mu_Eta_tight = 2.4;
  selector->ele_Pt_cut = 35.;
  selector->ele_Eta_cut = 2.4;
  selector->jet_Pt_cut = 30.;
  selector->jet_Eta_cut = 2.4;

  evtPick->year = Form("%d",fYear);
  evtPick->Njet_ge = 2;
  evtPick->NBjet_ge = 0;
  evtPick->applyMetFilter = true; 
  // bool applyHemVeto=true; 
  
  if (selector->useDeepCSVbTag){
    // While changing cut to L,M,T make sure to change the efficiency file
    //Light
    // if (fYear==2016) selector->btag_cut_DeepCSV = 0.2219; 
    // if (fYear==2017) selector->btag_cut_DeepCSV = 0.1522;
    // if (fYear==2018) selector->btag_cut_DeepCSV = 0.1241;
    //Medium
    if (fYear==2016) selector->btag_cut_DeepCSV = 0.6324; //in twiki it is 0.6324 instead of 0.6321
    if (fYear==2017) selector->btag_cut_DeepCSV = 0.4941;
    if (fYear==2018) selector->btag_cut_DeepCSV = 0.4184;
    // //Tight
    // if (fYear==2016) selector->btag_cut_DeepCSV = 0.8958; 
    // if (fYear==2017) selector->btag_cut_DeepCSV = 0.8001;
    // if (fYear==2018) selector->btag_cut_DeepCSV = 0.7527;
    selector->btag_cut = 1.0;
    kinFit.SetBtagThresh(selector->btag_cut_DeepCSV);
  }else{
    // CSVv2M
    if (fYear==2016) selector->btag_cut = 0.8484 ;
    if (fYear==2017) selector->btag_cut = 0.8838 ;
    if (fYear==2018) selector->btag_cut = 0.8838 ;
    selector->btag_cut_DeepCSV = 1.0;
    // Twiki not found for WP recommendation for CSVv2 for 2018;
    kinFit.SetBtagThresh(selector->btag_cut);
  }
  
  float mTop = 172.76;
  kinFit.SetTopMass(mTop);
  
}


//_____________________________________________________________________________
void SkimAna::GetNumberofEvents()
{
  ifstream fin(Form("%s/%s",fBasePath.Data(),fFileName.Data()));
  string s;
  
  totEvents.clear();
  totEventsUS.clear();
  fnameList.clear();
  std::map<std::string, vector<double> >::iterator crossIt;
  for(crossIt = crossSections.begin(); crossIt != crossSections.end(); crossIt++)
    totEvents[crossIt->first] = 0.0;
  
  while(getline(fin,s)){
    
    Info("GetNumberofEvents", "filename : %s", s.c_str());

    string sample = s.substr(s.find_last_of("/")+1,s.size());    
    if(sample.find("_ext4_Skim") != string::npos)
      sample = sample.substr(0,sample.find("_ext4_Skim"));
    else if (sample.find("_ext3_Skim") != string::npos)
      sample = sample.substr(0,sample.find("_ext3_Skim"));
    else if (sample.find("_ext2_Skim") != string::npos)
      sample = sample.substr(0,sample.find("_ext2_Skim"));
    else if (sample.find("_ext1_Skim") != string::npos)
      sample = sample.substr(0,sample.find("_ext1_Skim"));
    else if (sample.find("_Skim") != string::npos)
      sample = sample.substr(0,sample.find("_Skim"));
    
    TFile *file = TFile::Open(s.c_str(),"read");
    TH1D *hEvents = (TH1D*) file->Get("hEvents");
    double nMC_thisFile = (hEvents->GetBinContent(2)); //sum of gen weights
    
    totEvents[sample] += nMC_thisFile;
    totEventsUS[sample] += hEvents->GetEntries()/2.0;
    fnameList[sample].push_back(s);

    file->Close();
    delete file;
  }
  fin.close();

  LumiWZ.clear();
  map<string,double>::iterator evIt;
  for(evIt = totEvents.begin(); evIt != totEvents.end(); evIt++){
    if(evIt->second > 0.0){
      cout<<"sample  \""<< evIt->first <<"\" has number of events = " << evIt->second << endl;
      if(fSample.Contains("Wjets")){
	double kf  = 1.21377; 
	LumiWZ[evIt->first] = totEventsUS[evIt->first] / ( kf * crossSections[evIt->first].at(0)); // Here at(0) is for year 2016, but we consider it same for all years
      }
      if(fSample.Contains("DYjets")){
	double kf  = 1.1777; 
	LumiWZ[evIt->first] = totEventsUS[evIt->first] / ( kf * crossSections[evIt->first].at(0)); // Here at(0) is for year 2016, but we consider it same for all years
      }
    }
  }

  if (fYear==2016) {
    luminosity = 35921.875595;
    lumiFracI  = 19.695422959/35.921875595 ;
    lumiFracII = 16.226452636/35.921875595 ;
  }
  if (fYear==2017) {
    luminosity = 41529.548819;
    lumiFracI  = 1.;
    lumiFracII = 1.;
  }
  if (fYear==2018) {
    luminosity = 59740.565202;
    lumiFracI  = 8.950818835/59.740565202;
    lumiFracII = 50.789746366/59.740565202;
  }
  
}

//_____________________________________________________________________________
void SkimAna::LoadPU()
{
  
  std::string PUfilename; 
  std::string PUfilename_up;
  std::string PUfilename_down;
  
  if (fYear==2016){
    PUfilename      = Form("%s/weight/PileupSF/Data_2016BCDGH_Pileup.root", fBasePath.Data()) ;
    PUfilename_up   = Form("%s/weight/PileupSF/Data_2016BCDGH_Pileup_scaledUp.root", fBasePath.Data()) ;
    PUfilename_down = Form("%s/weight/PileupSF/Data_2016BCDGH_Pileup_scaledDown.root", fBasePath.Data()) ;
  }
  if (fYear==2017){
    PUfilename      = Form("%s/weight/PileupSF/Data_2017BCDEF_Pileup.root", fBasePath.Data()) ;
    PUfilename_up   = Form("%s/weight/PileupSF/Data_2017BCDEF_Pileup_scaledUp.root", fBasePath.Data()) ;
    PUfilename_down = Form("%s/weight/PileupSF/Data_2017BCDEF_Pileup_scaledDown.root", fBasePath.Data()) ;
  }
  if (fYear==2018){
    PUfilename      = Form("%s/weight/PileupSF/Data_2018ABCD_Pileup.root", fBasePath.Data()) ;
    PUfilename_up   = Form("%s/weight/PileupSF/Data_2018ABCD_Pileup_scaledUp.root", fBasePath.Data()) ;
    PUfilename_down = Form("%s/weight/PileupSF/Data_2018ABCD_Pileup_scaledDown.root", fBasePath.Data()) ;
  }
  
  vector<string> fnames = fnameList[fSampleType.Data()];
  unsigned int maxArraySize = 0;
  vector<string>::iterator fnIt;
  for(fnIt = fnames.begin(); fnIt != fnames.end(); fnIt++){
    string s = *fnIt;
    if(s.size()>maxArraySize)
      maxArraySize = s.size();
  }
  nFiles = int(fnames.size());
  fileNames = new char*[nFiles];
  for(int i = 0; i < nFiles; i++){
    fileNames[i] = new char[maxArraySize+2];
    strcpy(fileNames[i],fnames.at(i).c_str());
  }
  fnames.clear();
  
  switch (systType) {
  case kPUUp:
    PUweighter = new PUReweight(nFiles, fileNames, PUfilename_up);
    break;
  case kPUDown:
    PUweighter = new PUReweight(nFiles, fileNames, PUfilename_down);
    break;
  default:
    PUweighter = new PUReweight(nFiles, fileNames, PUfilename);
    break;
  }  
  
  for(int i = 0; i < nFiles; i++) 
    delete [] fileNames[i];
  delete [] fileNames;

}

//_____________________________________________________________________________
void SkimAna::LoadJECJER()
{
  if (!isData){
    if (fYear==2016) selector->init_JER( Form("%s/weight/JetSF/JER/Summer16_25nsV1",fBasePath.Data()) );
    if (fYear==2017) selector->init_JER( Form("%s/weight/JetSF/JER/Fall17_V3",fBasePath.Data()) );
    if (fYear==2018) selector->init_JER( Form("%s/weight/JetSF/JER/Autumn18_V7b",fBasePath.Data()) );
    
  
    if (systType == kJECUp or systType == kJECDown) { // if (isMC && jecvar012_g!=1) {
      //		jecvar = new JECvariation("weight/JetSF/Summer16_23Sep2016V4", isMC, "Total");//SubTotalAbsolute");
      //cout << "Applying JEC uncertainty variations : " << JECsystLevel << endl;
      string JECsystLevel = "Total";
      if (fYear==2016) jecvar = new JECvariation( Form("%s/weight/JetSF/Summer16_07Aug2017_V11",fBasePath.Data()), !isData, JECsystLevel);
      if (fYear==2017) jecvar = new JECvariation( Form("%s/weight/JetSF/Fall17_17Nov2017_V32",fBasePath.Data()), !isData, JECsystLevel);
      if (fYear==2018) jecvar = new JECvariation( Form("%s/weight/JetSF/Autumn18_V19",fBasePath.Data()), !isData, JECsystLevel);
    }
  }//isData

}

//_____________________________________________________________________________
void SkimAna::LoadBTag()
{
  
  if(isData)
    return ;

  Info("LoadBTag","Begin");
  // DeepCSV
  
  if (!selector->useDeepCSVbTag){
    Info("LoadBTag","CSVV2 calibration has been selected");
    if (fYear==2016) calib = BTagCalibration("csvv2", Form("%s/weight/BtagSF/CSVv2_Moriond17_B_H.csv",fBasePath.Data()));
    if (fYear==2017) calib = BTagCalibration("csvv2", Form("%s/weight/BtagSF/CSVv2_94XSF_V2_B_F.csv",fBasePath.Data()));
    if (fYear==2018) calib = BTagCalibration("csvv2", Form("%s/weight/BtagSF/CSVv2_94XSF_V2_B_F.csv",fBasePath.Data()));
    Info("LoadBTag","CSVV2 calibration has been loaded");
  } else {
    Info("LoadBTag","DeepCSV calibration has been selected");
    // if (fYear==2016){ calib = BTagCalibration( "deepcsv", Form("%s/weight/BtagSF/DeepCSV_2016LegacySF_V1.csv",fBasePath.Data()) ) ;}
    // if (fYear==2017){ calib = BTagCalibration( "deepcsv", Form("%s/weight/BtagSF/DeepCSV_94XSF_V3_B_F.csv",fBasePath.Data()) ) ;}
    // if (fYear==2018){ calib = BTagCalibration( "deepcsv", Form("%s/weight/BtagSF/DeepCSV_102XSF_V1.csv",fBasePath.Data()) ) ;} //DeepCSV_102XSF_V1.csv  
    if (fYear==2016){ 
      Info("LoadBTag","DeepCSV calibration has been selected : 2016");
      calib = BTagCalibration( "deepcsv", Form("%s/weight/BtagSF/new/DeepCSV_Moriond17_B_H.csv",fBasePath.Data()) ) ;
      Info("LoadBTag","%s/weight/BtagSF/new/DeepCSV_Moriond17_B_H.csv",fBasePath.Data());
    }
    if (fYear==2017){ 
      Info("LoadBTag","DeepCSV calibration has been selected : 2017 %s",fBasePath.Data());
      calib = BTagCalibration( "deepcsv", Form("%s/weight/BtagSF/new/DeepCSV_94XSF_V5_B_F.csv",fBasePath.Data()) ) ;
      Info("LoadBTag","%s/weight/BtagSF/new/DeepCSV_94XSF_V5_B_F.csv",fBasePath.Data());
    }
    if (fYear==2018){ 
      Info("LoadBTag","DeepCSV calibration has been selected : 2018");
      calib = BTagCalibration( "deepcsv", Form("%s/weight/BtagSF/new/DeepCSV_102XSF_V2.csv",fBasePath.Data()) ) ;
      Info("LoadBTag","%s/weight/BtagSF/new/DeepCSV_102XSF_V2.csv",fBasePath.Data());
    } //DeepCSV_102XSF_V1.csv  
  }
  
  reader = BTagCalibrationReader(BTagEntry::OP_MEDIUM, "central", {"up", "down"});
  
  reader.load(calib, BTagEntry::FLAV_B,"comb");          
  reader.load(calib, BTagEntry::FLAV_C, "comb"); 
  reader.load(calib, BTagEntry::FLAV_UDSG, "incl"); 
  
  //string year = "2016";
  std::string fName = "" ;
  if(!selector->useDeepCSVbTag){ //CSVV2
    if(fSample.BeginsWith("MCQCD"))
      fName = Form("%s/weight/BtagSF/btag_efficiencies_%d.root",fBasePath.Data(),fYear);
    else
      fName = Form("%s/weight/BtagSF/Efficiency/MiniAOD/CSVV2/%s_btag_efficiency.root",fBasePath.Data(),fSample.Data());
  }else{ //DeepCSV
    
    // if(fSample.BeginsWith("TTbar") or fSample.BeginsWith("Hplus"))
    //   fName = Form("%s/weight/BtagSF/Efficiency/NanoAOD/DeepCSV/%d/TTB_btag_efficiency_%d.root",fBasePath.Data(),fYear,fYear);    
    // else
    //   fName = Form("%s/weight/BtagSF/Efficiency/NanoAOD/DeepCSV/%d/Others_btag_efficiency_%d.root",fBasePath.Data(),fYear,fYear);    
    
    //fName = Form("%s/weight/BtagSF/Efficiency/NanoAOD/DeepCSV/btagL/%d/%s_btag_efficiency_%d.root",fBasePath.Data(),fYear,fSample.Data(),fYear);
    fName = Form("%s/weight/BtagSF/Efficiency/NanoAOD/DeepCSV/%d/%s_btag_efficiency_%d.root",fBasePath.Data(),fYear,fSample.Data(),fYear);    
    //fName = Form("%s/weight/BtagSF/Efficiency/NanoAOD/DeepCSV_hfl/%d/%s_btag_efficiency_%d.root",fBasePath.Data(),fYear,fSample.Data(),fYear);    
    //fName = Form("%s/weight/BtagSF/btag_efficiencies_%d.root",fBasePath.Data(),fYear);
  }
  Info("LoadBTag","Efficientcy file : %s",fName.c_str());
  Info("LoadBTag","Btag threshold : %lf",((selector->useDeepCSVbTag) ? selector->btag_cut_DeepCSV  : selector->btag_cut));
  
  std::string effType = "Other";
  // if (fSample.BeginsWith("TTbar"))
  //   effType = "Top";
  
  std::string leffName = effType+"_l_efficiency";
  std::string ceffName = effType+"_c_efficiency";
  std::string beffName = effType+"_b_efficiency";
  
  TFile* inputFile = TFile::Open(fName.c_str(),"read");
  l_eff = (TH2D*) inputFile->Get(leffName.c_str());
  c_eff = (TH2D*) inputFile->Get(ceffName.c_str());
  b_eff = (TH2D*) inputFile->Get(beffName.c_str());
  
}

//_____________________________________________________________________________
void SkimAna::LoadLeptonSF(){

  if (fYear==2016){
    if(isNanoAOD){
      muSFa = new MuonSF(Form("%s/weight/MuEleSF/mu2016/EfficienciesStudies_2016_legacy_rereco_rootfiles_RunBCDEF_SF_ID.root",fBasePath.Data()), 
			 "NUM_TightID_DEN_genTracks_eta_pt",
			 Form("%s/weight/MuEleSF/mu2016/EfficienciesStudies_2016_legacy_rereco_rootfiles_RunBCDEF_SF_ISO.root",fBasePath.Data()), 
			 "NUM_TightRelIso_DEN_TightIDandIPCut_eta_pt",
			 Form("%s/weight/MuEleSF/mu2016/EfficienciesStudies_2016_trigger_EfficienciesAndSF_RunBtoF.root",fBasePath.Data()), 
			 "IsoMu24_OR_IsoTkMu24_PtEtaBins/abseta_pt_ratio");
      
      muSFb = new MuonSF(Form("%s/weight/MuEleSF/mu2016/EfficienciesStudies_2016_legacy_rereco_rootfiles_RunGH_SF_ID.root",fBasePath.Data()), 
			 "NUM_TightID_DEN_genTracks_eta_pt",
			 Form("%s/weight/MuEleSF/mu2016/EfficienciesStudies_2016_legacy_rereco_rootfiles_RunGH_SF_ISO.root",fBasePath.Data()), 
			 "NUM_TightRelIso_DEN_TightIDandIPCut_eta_pt",
			 Form("%s/weight/MuEleSF/mu2016/EfficienciesStudies_2016_trigger_EfficienciesAndSF_RunGtoH.root",fBasePath.Data()), 
			 "IsoMu24_OR_IsoTkMu24_PtEtaBins/abseta_pt_ratio");
      
      eleSF = new ElectronSF(Form("%s/weight/MuEleSF/ele2016/2016LegacyReReco_ElectronTight_Fall17V2.root",fBasePath.Data()),
			     Form("%s/weight/MuEleSF/ele2016/EGM2D_BtoH_GT20GeV_RecoSF_Legacy2016.root",fBasePath.Data()),
			     Form("%s/weight/MuEleSF/ele2016/sf_ele_2016_trig_v5.root",fBasePath.Data()));
    }else{

      muSFa = new MuonSF(Form("%s/weight/MuEleSF/mu2016/EfficienciesStudies_2016_legacy_rereco_rootfiles_RunBCDEF_SF_ID.root",fBasePath.Data()), 
			 "NUM_MediumID_DEN_genTracks_eta_pt",
			 Form("%s/weight/MuEleSF/mu2016/EfficienciesStudies_2016_legacy_rereco_rootfiles_RunBCDEF_SF_ISO.root",fBasePath.Data()), 
			 "NUM_TightRelIso_DEN_MediumID_eta_pt",
			 Form("%s/weight/MuEleSF/mu2016/EfficienciesStudies_2016_trigger_EfficienciesAndSF_RunBtoF.root",fBasePath.Data()), 
			 "IsoMu24_OR_IsoTkMu24_PtEtaBins/abseta_pt_ratio");
      
      muSFb = new MuonSF(Form("%s/weight/MuEleSF/mu2016/EfficienciesStudies_2016_legacy_rereco_rootfiles_RunGH_SF_ID.root",fBasePath.Data()), 
			 "NUM_MediumID_DEN_genTracks_eta_pt",
			 Form("%s/weight/MuEleSF/mu2016/EfficienciesStudies_2016_legacy_rereco_rootfiles_RunGH_SF_ISO.root",fBasePath.Data()), 
			 "NUM_TightRelIso_DEN_MediumID_eta_pt",
			 Form("%s/weight/MuEleSF/mu2016/EfficienciesStudies_2016_trigger_EfficienciesAndSF_RunGtoH.root",fBasePath.Data()), 
			 "IsoMu24_OR_IsoTkMu24_PtEtaBins/abseta_pt_ratio");
      
      f_trackSF_BCDEF 	= new TFile(Form("%s/../Analysis/Analysis/stack/muonSF/trackingSF_BCDEF.root",fBasePath.Data()));
      f_trackSF_GH	= new TFile(Form("%s/../Analysis/Analysis/stack/muonSF/trackingSF_GH.root",fBasePath.Data()));
      tg_trackSF_BCDEF 	= (TGraphAsymmErrors*)f_trackSF_BCDEF->Get("ratio_eff_aeta_dr030e030_corr");
      tg_trackSF_GH 	= (TGraphAsymmErrors*)f_trackSF_GH->Get("ratio_eff_aeta_dr030e030_corr");
      
      //eleSF may not be currect for MiniAOD, take care.
      eleSF = new ElectronSF(Form("%s/weight/MuEleSF/ele2016/2016LegacyReReco_ElectronMedium_Fall17V2.root",fBasePath.Data()),
			     Form("%s/weight/MuEleSF/ele2016/EGM2D_BtoH_GT20GeV_RecoSF_Legacy2016.root",fBasePath.Data()),
			     Form("%s/weight/MuEleSF/ele2016/sf_ele_2016_trig_v5.root",fBasePath.Data()));
      
    }
  } else if (fYear==2017) {
	
    muSFa = new MuonSF(Form("%s/weight/MuEleSF/mu2017/RunBCDEF_SF_ID.root",fBasePath.Data()), "NUM_TightID_DEN_genTracks_pt_abseta",
		       Form("%s/weight/MuEleSF/mu2017/RunBCDEF_SF_ISO.root",fBasePath.Data()), "NUM_TightRelIso_DEN_TightIDandIPCut_pt_abseta",
		       Form("%s/weight/MuEleSF/mu2017/EfficienciesAndSF_RunBtoF_Nov17Nov2017.root",fBasePath.Data()), "IsoMu27_PtEtaBins/abseta_pt_ratio");
	
    eleSF = new ElectronSF(Form("%s/weight/MuEleSF/ele2017/2017_ElectronTight.root",fBasePath.Data()),
			   Form("%s/weight/MuEleSF/ele2017/egammaEffi.txt_EGM2D_runBCDEF_passingRECO.root",fBasePath.Data()),
			   Form("%s/weight/MuEleSF/ele2017/sf_ele_2017_trig_v5.root",fBasePath.Data()));

  } else if (fYear==2018) {

    muSFa = new MuonSF(Form("%s/weight/MuEleSF/mu2018/EfficienciesStudies_2018_rootfiles_RunABCD_SF_ID.root",fBasePath.Data()),  
		       "NUM_TightID_DEN_TrackerMuons_pt_abseta",
		       Form("%s/weight/MuEleSF/mu2018/EfficienciesStudies_2018_rootfiles_RunABCD_SF_ISO.root",fBasePath.Data()), 
		       "NUM_TightRelIso_DEN_TightIDandIPCut_pt_abseta",
		       Form("%s/weight/MuEleSF/mu2018/EfficienciesStudies_2018_trigger_EfficienciesAndSF_2018Data_BeforeMuonHLTUpdate.root",fBasePath.Data()), 
		       "IsoMu24_PtEtaBins/abseta_pt_ratio");
    
    muSFb = new MuonSF(Form("%s/weight/MuEleSF/mu2018/EfficienciesStudies_2018_rootfiles_RunABCD_SF_ID.root",fBasePath.Data()),  
		       "NUM_TightID_DEN_TrackerMuons_pt_abseta",
		       Form("%s/weight/MuEleSF/mu2018/EfficienciesStudies_2018_rootfiles_RunABCD_SF_ISO.root",fBasePath.Data()), 
		       "NUM_TightRelIso_DEN_TightIDandIPCut_pt_abseta",
		       Form("%s/weight/MuEleSF/mu2018/EfficienciesStudies_2018_trigger_EfficienciesAndSF_2018Data_AfterMuonHLTUpdate.root",fBasePath.Data()), 
		       "IsoMu24_PtEtaBins/abseta_pt_ratio");
    
    eleSF = new ElectronSF(Form("%s/weight/MuEleSF/ele2018/2018_ElectronTight.root",fBasePath.Data()),
			   Form("%s/weight/MuEleSF/ele2018/egammaEffi.txt_EGM2D_updatedAll.root",fBasePath.Data()),
			   Form("%s/weight/MuEleSF/ele2018/sf_ele_2018_trig_v5.root",fBasePath.Data()));
  }

}
//_____________________________________________________________________________
void SkimAna::GetBtagSF_1a(){
  
  double jetPt;
  double jetEta;
  double jetBtag;
  int jetFlavor;
  double SFb;
  double Eff;

  double pMC = 1.0;
  double pData = 1.0;
	
  string b_sysType = "central";
  string l_sysType = "central";
  if (btagSystType=="b_up"){
    b_sysType = "up";
  } else if (btagSystType=="b_down"){
    b_sysType = "down";
  } else if (btagSystType=="l_up"){
    l_sysType = "up";
  } else if (btagSystType=="l_down"){
    l_sysType = "down";
  }	
  
  double btagThreshold = (selector->useDeepCSVbTag) ? selector->btag_cut_DeepCSV  : selector->btag_cut  ;
  
  int xbin,ybin;
  int maxbinX, maxbinY;
  
  for(std::vector<int>::const_iterator jetInd = selector->Jets.begin(); jetInd != selector->Jets.end(); jetInd++){
    
    jetPt = event->jetPt_[*jetInd];
    jetEta = fabs(event->jetEta_[*jetInd]);
    jetFlavor = abs(event->jetPartFlvr_[*jetInd]);
    //jetFlavor = abs(event->jetHadFlvr_[*jetInd]);
    jetBtag = (selector->useDeepCSVbTag) ? event->jetBtagDeepB_[*jetInd] : event->jetBtagCSVV2_[*jetInd] ;

    if (jetFlavor == 5){
      SFb = reader.eval_auto_bounds(b_sysType, BTagEntry::FLAV_B, jetEta, jetPt); 
      xbin = b_eff->GetXaxis()->FindBin(min(jetPt,799.));
      ybin = b_eff->GetYaxis()->FindBin(abs(jetEta));
      maxbinX = b_eff->GetXaxis()->GetLast();
      maxbinY = b_eff->GetYaxis()->GetLast();
      Eff = b_eff->GetBinContent(xbin,ybin);
    }
    else if(jetFlavor == 4){
      SFb = reader.eval_auto_bounds(b_sysType, BTagEntry::FLAV_C, jetEta, jetPt); 
      xbin = c_eff->GetXaxis()->FindBin(min(jetPt,799.));
      ybin = c_eff->GetYaxis()->FindBin(abs(jetEta));
      maxbinX = c_eff->GetXaxis()->GetLast();
      maxbinY = c_eff->GetYaxis()->GetLast();
      Eff = c_eff->GetBinContent(xbin,ybin);
    }
    else {
      SFb = reader.eval_auto_bounds(l_sysType, BTagEntry::FLAV_UDSG, jetEta, jetPt); 
      xbin = l_eff->GetXaxis()->FindBin(min(jetPt,799.));
      ybin = l_eff->GetYaxis()->FindBin(abs(jetEta));
      maxbinX = l_eff->GetXaxis()->GetLast();
      maxbinY = l_eff->GetYaxis()->GetLast();
      Eff = l_eff->GetBinContent(xbin,ybin);
    }
	
    if( (xbin==0 or xbin>maxbinX or ybin==0 or ybin>maxbinY) and TMath::AreEqualAbs(Eff,0.0,1.0e-7) ) continue;

    if (jetBtag > btagThreshold ){
      pMC *= Eff;
      pData *= Eff*SFb;
    } else {
      pMC *= 1. - Eff;
      pData *= 1. - (Eff*SFb);
    }
  }//end of jet loop
  
  //   _bTagWeight = pData/pMC;
  if ( TMath::AreEqualAbs(pMC,0.0,1.0e-7) )
    _bTagWeight = 0.;
  else 
    _bTagWeight = pData/pMC;

}

//_____________________________________________________________________________
void SkimAna::GetMuonEff(double iso){

  int muInd_ = selector->Muons.at(0);
  
  if (fYear==2016){
    vector<double> muWeights_a    = muSFa->getMuSF(event->muPt_[muInd_],event->muEta_[muInd_], mueffvar012_g, 2016);
    vector<double> muWeights_b    = muSFb->getMuSF(event->muPt_[muInd_],event->muEta_[muInd_], mueffvar012_g, 2016);
    vector<double> muWeights;

    for (int i=0; i < int(muWeights_a.size()); i++)
      muWeights.push_back( muWeights_a.at(i)*lumiFracI + muWeights_b.at(i)*lumiFracII );    
    
    if(isNanoAOD){
      _muEffWeight = (iso < 0.15) ? muWeights.at(0) : (muWeights.at(1) * muWeights.at(3));  // if iso>=0.15 then exclude iso eff at(2)
    }else{
      double muSFtrack_BCDEF 	= getMuonTrackSF(tg_trackSF_BCDEF, event->muEta_[muInd_]);
      double muSFtrack_GH 	= getMuonTrackSF(tg_trackSF_GH, event->muEta_[muInd_]);
      double muSFtrack 		= muSFtrack_BCDEF*lumiFracI + muSFtrack_GH*lumiFracII;

      if(iso<0.15)
	_muEffWeight    = muWeights.at(1) * muWeights.at(2) * muWeights.at(3) * muSFtrack; //id * iso * trig * track
      else
	_muEffWeight    = muWeights.at(1) * muWeights.at(3) * muSFtrack; //id * trig * track
    }

    muWeights_a.clear(); muWeights_b.clear(); muWeights.clear();
  }
  if (fYear==2017){    
    vector<double> muWeights    = muSFa->getMuSF(event->muPt_[muInd_],event->muEta_[muInd_],mueffvar012_g, 2017);

    _muEffWeight = (iso < 0.15) ? muWeights.at(0) : (muWeights.at(1) * muWeights.at(3)) ;  
    
    muWeights.clear();
  }
  if(fYear==2018){
    vector<double> muWeights_a    = muSFa->getMuSF(event->muPt_[muInd_],event->muEta_[muInd_],mueffvar012_g, 2018);
    vector<double> muWeights_b    = muSFb->getMuSF(event->muPt_[muInd_],event->muEta_[muInd_],mueffvar012_g, 2018);
    vector<double> muWeights;

    for (int i=0; i < int(muWeights_a.size()); i++)
      muWeights.push_back( muWeights_a.at(i)*lumiFracI + muWeights_b.at(i)*lumiFracII );    

    _muEffWeight = (iso < 0.15) ? muWeights.at(0) : (muWeights.at(1) * muWeights.at(3));  // if iso>=0.15 then exclude iso eff at(2)

    muWeights_a.clear(); muWeights_b.clear(); muWeights.clear();
  }
  
}

//_____________________________________________________________________________
void SkimAna::GetElectronEff(){

  int eleInd_ = selector->Electrons.at(0);
  vector<double> eleWeights    = eleSF->getEleSF(event->elePt_[eleInd_],event->eleEta_[eleInd_] + event->eleDeltaEtaSC_[eleInd_],eleeffvar012_g);
  _eleEffWeight    = eleWeights.at(0);
  eleWeights.clear();
}

//_____________________________________________________________________________
void SkimAna::Begin(TTree */*tree*/)
{
   // This is needed when re-processing the object
   Reset();
   
   //print the option specified in the Process function.
   TString option = GetOption();
   Info("Begin", "starting SkimAna with process option: %s", option.Data());
   
   //if (fChain) fChain->SetEntryList(0);
}


//_____________________________________________________________________________
void SkimAna::SlaveBegin(TTree *tree)
{  
  //print the option specified in the Process function.
  TString option = GetOption();
  Info("SlaveBegin",
       "starting SkimAna with process option: %s (tree: %p)", option.Data(), tree);
  
  GetArguments();  
  Info("SlaveBegin",
       "sample : %s, year : %d, mode : %s", fSample.Data(), fYear, fMode.Data());

  SelectSyst();
  SetTrio(); // SetTrio method should be after SelectSyst
  // Info("SlaveBegin",
  //      "Chain %p (tree: %p)", event->chain, tree);
  
  //initialize the Tree branch addresses
  Init(tree);
  
  char *filename[3];
  
  filename[0] = Form("%s_hist_%dof%d.root",fSample.Data(),fIndex,fTotal) ;
  filename[1] = Form("%s_tree_%dof%d.root",fSample.Data(),fIndex,fTotal) ;
  
  for(int ifile=0;ifile<2;ifile++){
    
    if(fMode.BeginsWith("proof")){
      fProofFile[ifile] = new TProofOutputFile(filename[ifile], "M");
      fFile[ifile] = fProofFile[ifile]->OpenFile("RECREATE");
      if (fFile[ifile] && fFile[ifile]->IsZombie()) SafeDelete(fFile[ifile]);
    }else{
      fFile[ifile] = TFile::Open(filename[ifile],"RECREATE");
    }
    
    // Cannot continue
    if (!fFile[ifile]) {
      TString amsg = TString::Format("SkimAna::SlaveBegin: could not create '%s':"
				     " instance is invalid!", fFile[ifile]->GetName());
      Abort(amsg, kAbortProcess);
      return;
    }
        
  }//ifile loop
  
  

  if(!isData){
    Info("SlaveBegin", "CS Init");
    initCrossSections();
    Info("SlaveBegin", "GetNumber of Events and files");
    GetNumberofEvents();
    
    //LoadPU();
    Info("SlaveBegin", "Loading Lepton SF");
    LoadLeptonSF();
    Info("SlaveBegin", "Loading JEC JER");
    LoadJECJER();
    Info("SlaveBegin", "Loading BTag");
    LoadBTag();
  }
  Info("SlaveBegin", "Create Histos");
  CreateHistoArrays();
  Info("SlaveBegin", "End of SlaveBegin");

       

}

//_____________________________________________________________________________
void SkimAna::TheoWeights(){

  _q2weight_Up = 1.;
  _q2weight_Do = 1.;

  if(event->nLHEScaleWeight_ >=9 ){

    vector<float>     genScaleSystWeights;
    if (event->nLHEScaleWeight_==9){
      for (int i = 0; i < 9; i++){
	if(i==2||i==6){continue;}
	genScaleSystWeights.push_back(event->LHEScaleWeight_[i]);
      }
    
      double nomWeight=event->LHEScaleWeight_[4];
      if (!TMath::AreEqualAbs(nomWeight,0.0,1.e-7)){
	_q2weight_Up = *max_element(genScaleSystWeights.begin(), genScaleSystWeights.end())/nomWeight;
	_q2weight_Do = *min_element(genScaleSystWeights.begin(), genScaleSystWeights.end())/nomWeight;
      }
    }

    if (event->nLHEScaleWeight_==44){
      genScaleSystWeights.push_back(event->LHEScaleWeight_[0]);
      genScaleSystWeights.push_back(event->LHEScaleWeight_[5]);
      genScaleSystWeights.push_back(event->LHEScaleWeight_[15]);
      genScaleSystWeights.push_back(event->LHEScaleWeight_[24]);
      genScaleSystWeights.push_back(event->LHEScaleWeight_[34]);
      genScaleSystWeights.push_back(event->LHEScaleWeight_[39]);

      _q2weight_Up = *max_element(genScaleSystWeights.begin(), genScaleSystWeights.end());
      _q2weight_Do = *min_element(genScaleSystWeights.begin(), genScaleSystWeights.end());
    }
    genScaleSystWeights.clear();
  }
  
  _pdfweight_Up = 1. ;
  _pdfweight_Do = 1. ;
  
  if(event->nLHEPdfWeight_ > 0){
    
    vector<float>	 pdfSystWeight;
    double pdfMean = 0.;

    for (int j=0; j < int(event->nLHEPdfWeight_); j++ ){
      pdfSystWeight.push_back(event->LHEPdfWeight_[j]);
      pdfMean += event->LHEPdfWeight_[j];
    }
    pdfMean = pdfMean/pdfSystWeight.size();
    
    double pdfVariance = 0.;
    for (int j=0; j < int(pdfSystWeight.size()); j++){
      pdfVariance += pow((pdfSystWeight[j]-pdfMean),2.);
    }
    
    if (TMath::AreEqualAbs(pdfMean,0.0,1.0e-7)) 
      pdfMean = 1;
    
    _pdfuncer = sqrt(pdfVariance/pdfSystWeight.size())/pdfMean;
    _pdfweight_Up = (1. + _pdfuncer);
    _pdfweight_Do = (1. - _pdfuncer);
    pdfSystWeight.clear();
  }
  
  _ISRweight_Up = 1.;
  _ISRweight_Do = 1.;
  
  _FSRweight_Up = 1.;
  _FSRweight_Do = 1.;
  
  if (event->nPSWeight_==4){
    if (event->genWeight_ != 0){
      _ISRweight_Up = event->PSWeight_[2];
      _ISRweight_Do = event->PSWeight_[0];
      
      _FSRweight_Up = event->PSWeight_[3];
      _FSRweight_Do = event->PSWeight_[1];
    }
  }


}

//_____________________________________________________________________________
Bool_t SkimAna::Process(Long64_t entry)
{
  // entry is the entry number in the current Tree
  
  // to read complete event, call fChain->GetTree()->GetEntry(entry)
  // if(fMode.Contains("proof"))
  //   fChain->GetTree()->GetEntry(entry);  
  // else
  //   fChain->GetEntry(fProcessed);  
  
  fChain->GetTree()->GetEntry(entry);  
  //fChain->GetEntry(entry);
  
  //    fChain->GetEntry(fProcessed);  

  fProcessed++;
  fStatus++;
  
  // OldMethod();

  _sampleWeight	 = 1.0;
  _prefireWeight = 1.0;
  _PUWeight	 = 1.0;
  _muEffWeight	 = 1.0;
  _eleEffWeight	 = 1.0;
  _bTagWeight	 = 1.0;
  _topPtReWeight = 1.0;

  int mod_num = 10000;

  if(fProcessed%mod_num==0){
    Info("Process","Processing : %lld(%lld) of number of events : %lld and total number of events : %.0lf, year : %s", 
	 fProcessed, entry, fChain->GetEntries(), totEventsUS[fSampleType.Data()],evtPick->year.c_str());
  }
  
  
  // Set JEC syst
  if( !isData and (systType == kJECUp or systType == kJECDown)){
    jecvar->applyJEC(event, jecvar012_g); // 0:down, 1:norm, 2:up
  }
  
  // //Clear selector vectors
  selector->clear_vectors();
  
  // if(fProcessed%mod_num==0)
  //   Info("Process","Level 0");
  
  // This is main method to process the objects read from tree
  evtPick->process_event(fBasePath.Data(), event, selector, 1.0); // here last argument 1.0 is weight applied to cutflow

  //Special case of Wjets and DY
  //if(!isNanoAOD and !isData and fSampleType.Contains("Wjets")){
  if(!isData and fSampleType.Contains("Wjets")){
    _local_evtWeight = ScaleLumiW(event->nLHEPart_) * luminosity/1000.;
    if(fProcessed%100000==0)
      Info("Process", "Wjets : Updated special event weight : %lf for nLHEPart_ : %d", _local_evtWeight, event->nLHEPart_);
  }
  
  if(!isData and fSampleType.Contains("DYjetsM50")){
    _local_evtWeight = ScaleLumiZ(event->nLHEPart_) * luminosity/1000.;
    if(fProcessed%100000==0)
      Info("Notify", "DYjets : Updated special event weight : %lf for nLHEPart_ : %d", _local_evtWeight, event->nLHEPart_);
  }

  // if(fProcessed%mod_num==0)
  //   Info("Process","Level 1");
 

  // Sample weight 
  if(!isData)
    _sampleWeight = _local_evtWeight * ((event->genWeight_ >= 0) ? 1.0 : -1.0) ; //_sampleWeight should mimic the MiniAOD

  // Access the prefire weight
  if(!isData){
    switch (systType) {
    case kPreFireUp:
      _prefireWeight = event->L1PreFiringWeight_Up_ ;
      break;
    case kPreFireDown:
      _prefireWeight = event->L1PreFiringWeight_Dn_ ;
      break;
    default:
      _prefireWeight = event->L1PreFiringWeight_Nom_ ;
      break;
    }  
  }

  // Access the PU weight
  if(!isData){
    _PUWeight = PUweighter->getWeight(event->nPUTrue_);
  }
  
  // if(fProcessed%mod_num==0)
  //   Info("Process","Level 2");

  hCheck[6]->Fill(_sampleWeight);
  hCheck[7]->Fill(_PUWeight);
  hCheck[8]->Fill(_prefireWeight);
  //Event level or trigger level conditions will be placed in block below
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //hCheck[1]->Fill(_PUWeight); //filled later;
  
  if(evtPick->passTrigger_mu || evtPick->passTrigger_ele)
    hCheck[0]->Fill(0.0);
  if((evtPick->passTrigger_mu || evtPick->passTrigger_ele) && selector->isPVGood && evtPick->passFilter)
    hCheck[0]->Fill(1.0);
  
  if(evtPick->passTrigger_mu){
    hCheck[1]->Fill(0.0);
    hCheck[2]->Fill(0.0, _sampleWeight*_prefireWeight*_PUWeight);
    hCheck[5]->Fill(0.0, _sampleWeight*_PUWeight);
  }
  
  if(evtPick->passTrigger_mu and selector->isPVGood and evtPick->passFilter){
    hCheck[1]->Fill(1.0);
    hCheck[2]->Fill(1.0, _sampleWeight*_prefireWeight*_PUWeight);
    hCheck[5]->Fill(1.0, _sampleWeight*_PUWeight);
  }
  
  //elec
  if(evtPick->passTrigger_ele){
    hCheck[3]->Fill(0.0);
    hCheck[4]->Fill(0.0, _sampleWeight*_prefireWeight*_PUWeight);
  }

  if(evtPick->passTrigger_ele and selector->isPVGood and evtPick->passFilter){
    hCheck[3]->Fill(1.0);
    hCheck[4]->Fill(1.0, _sampleWeight*_prefireWeight*_PUWeight);
  }
  
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  // if(fProcessed%mod_num==0)
  //   Info("Process","Level 3");

  bool singleMu = (evtPick->passFilter and selector->isPVGood and evtPick->passTrigger_mu and selector->Electrons.size() == 0 and selector->ElectronsLoose.size() == 0 and selector->Muons.size() == 1 and selector->MuonsLoose.size() == 0);
  bool singleEle = (evtPick->passFilter and selector->isPVGood and evtPick->passTrigger_ele and selector->Electrons.size() == 1 and selector->ElectronsLoose.size() == 0 and selector->Muons.size() == 0 and selector->MuonsLoose.size() == 0);
  //////=====================================================
  if(!singleMu and !singleEle) return true;
  //////=====================================================

  // if(fProcessed%mod_num==0)
  //   Info("Process","Level 4");

  //Processes after single muon/electron selection will be placed in block below
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////
  if(!isData){
    if(singleMu) GetMuonEff(event->muPFRelIso_[selector->Muons.at(0)]);
    if(singleEle) GetElectronEff();
  }
  
  hCheck[9]->Fill(_muEffWeight);
  hCheck[10]->Fill(_eleEffWeight);

  bool muonIsoCut = false;
  if(singleMu)
    muonIsoCut = (event->muPFRelIso_[selector->Muons.at(0)] < 0.15) ? true : false; 
  
  bool eleIsoCut = false;
  if(singleEle)
    eleIsoCut =  (
  		  (TMath::Abs(event->eleEta_[selector->Electrons.at(0)]) <= 1.479 and event->elePFRelIso_[selector->Electrons.at(0)] < 0.0695) 
  		  or 
  		  (TMath::Abs(event->eleEta_[selector->Electrons.at(0)]) > 1.479 and  event->elePFRelIso_[selector->Electrons.at(0)] < 0.0821)
  		  ) ? true : false;

  if((singleMu and muonIsoCut) or (singleEle and eleIsoCut))
    hCheck[0]->Fill(2.0);
  
  if(singleMu and muonIsoCut){
    hCheck[1]->Fill(2.0);
    hCheck[2]->Fill(2.0, _sampleWeight*_prefireWeight*_PUWeight*_muEffWeight);
    hCheck[5]->Fill(2.0, _sampleWeight*_PUWeight*_muEffWeight);
  }
  
  //elec
  if(singleEle and eleIsoCut){
    hCheck[3]->Fill(2.0);
    hCheck[4]->Fill(2.0, _sampleWeight*_prefireWeight*_PUWeight*_eleEffWeight);
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  //////=====================================================
  if(selector->Jets.size() < 4 ) return true;
  //////=====================================================

  // if(fProcessed%mod_num==0)
  //   Info("Process","Level 5");

  //Processes after njet >= 4 selection will be placed in block below
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  if((singleMu and muonIsoCut) or (singleEle and eleIsoCut))
    hCheck[0]->Fill(3.0);
  
  if(singleMu and muonIsoCut){
    hCheck[1]->Fill(3.0);
    hCheck[2]->Fill(3.0, _sampleWeight*_prefireWeight*_PUWeight*_muEffWeight);
    hCheck[5]->Fill(3.0, _sampleWeight*_PUWeight*_muEffWeight);
  }
  
  //elec
  if(singleEle and eleIsoCut){
    hCheck[3]->Fill(3.0);
    hCheck[4]->Fill(3.0, _sampleWeight*_prefireWeight*_PUWeight*_eleEffWeight);
  }
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  METThreshold = 20. ;
  //////=====================================================
  if(selector->METPt < METThreshold ) return true;
  //////=====================================================

  // if(fProcessed%mod_num==0)
  //   Info("Process","Level 6");

  //Processes after MET selection will be placed in block below
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////
  if((singleMu and muonIsoCut) or (singleEle and eleIsoCut))
    hCheck[0]->Fill(4.0);
  
  if(singleMu and muonIsoCut){
    hCheck[1]->Fill(4.0);
    hCheck[2]->Fill(4.0, _sampleWeight*_prefireWeight*_PUWeight*_muEffWeight);
    hCheck[5]->Fill(4.0, _sampleWeight*_PUWeight*_muEffWeight);
  }
  
  //elec
  if(singleEle and eleIsoCut){
    hCheck[3]->Fill(4.0);
    hCheck[4]->Fill(4.0, _sampleWeight*_prefireWeight*_PUWeight*_eleEffWeight);
  }
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////

  //////=====================================================
  if(selector->bJets.size() < 2 ) return true;
  //////=====================================================
  
  // if(fProcessed%mod_num==0)
  //   Info("Process","Level 7");

  //Processes after nbjet >= 2 selection will be placed in block below
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////
  if(!isData){
    GetBtagSF_1a();
    //_topPtReWeight = topPtReweight();
    _topPtReWeight = 1.0;
  }
  switch (systType) {
  case kBTagbDown:
    hCheck[12]->Fill(_bTagWeight);
    break;      
  case kBTagbUp:
    hCheck[13]->Fill(_bTagWeight);
    break;
  case kBTaglDown:
    hCheck[14]->Fill(_bTagWeight);
    break;
  case kBTaglUp:
    hCheck[15]->Fill(_bTagWeight);
    break;
  default:
    hCheck[11]->Fill(_bTagWeight);
    break;
  }
  hCheck[74]->Fill(_topPtReWeight);
  
  double mu_wt = _sampleWeight*_prefireWeight*_PUWeight*_muEffWeight*_bTagWeight*_topPtReWeight ;
  double ele_wt = _sampleWeight*_prefireWeight*_PUWeight*_eleEffWeight*_bTagWeight*_topPtReWeight ;
  
  if((singleMu and muonIsoCut) or (singleEle and eleIsoCut))
    hCheck[0]->Fill(5.0);
  
  if(singleMu and muonIsoCut){
    hCheck[1]->Fill(5.0);
    hCheck[2]->Fill(5.0, mu_wt);
    hCheck[5]->Fill(5.0, _sampleWeight*_PUWeight*_muEffWeight*_bTagWeight*_topPtReWeight);
    hCheck[30]->Fill(event->muPt_[selector->Muons.at(0)] * event->muRoccoR_[selector->Muons.at(0)], mu_wt);
    hCheck[31]->Fill(event->muEta_[selector->Muons.at(0)], mu_wt);
    hCheck[32]->Fill(event->muPhi_[selector->Muons.at(0)], mu_wt);
    for(unsigned int ijet = 0; ijet < selector->Jets.size(); ijet++){
      int jetInd = selector->Jets.at(ijet);
      hCheck[36]->Fill(selector->JetsPtSmeared.at(ijet), mu_wt);
      hCheck[37]->Fill(event->jetEta_[jetInd], mu_wt);
      hCheck[38]->Fill(event->jetPhi_[jetInd], mu_wt);
    }
    hCheck[42]->Fill(selector->METPt, mu_wt);
    hCheck[43]->Fill(selector->METPhi, mu_wt);
    hCheck[46]->Fill(selector->Jets.size(), mu_wt);
    hCheck[47]->Fill(selector->bJets.size(), mu_wt);
  }
  
  //elec
  if(singleEle and eleIsoCut){
    hCheck[3]->Fill(5.0);
    hCheck[4]->Fill(5.0, ele_wt);
    hCheck[33]->Fill(event->elePt_[selector->Electrons.at(0)], ele_wt);
    hCheck[34]->Fill(event->eleEta_[selector->Electrons.at(0)], ele_wt);
    hCheck[35]->Fill(event->elePhi_[selector->Electrons.at(0)], ele_wt);
    for(unsigned int ijet = 0; ijet < selector->Jets.size(); ijet++){
      int jetInd = selector->Jets.at(ijet);
      hCheck[39]->Fill(selector->JetsPtSmeared.at(ijet), ele_wt);
      hCheck[40]->Fill(event->jetEta_[jetInd], ele_wt);
      hCheck[41]->Fill(event->jetPhi_[jetInd], ele_wt);
    }
    hCheck[44]->Fill(selector->METPt, ele_wt);
    hCheck[45]->Fill(selector->METPhi, ele_wt);
    hCheck[48]->Fill(selector->Jets.size(), ele_wt);
    hCheck[49]->Fill(selector->bJets.size(), ele_wt);
  }


  ////////////////////////////////////////////////////////////////////////////////////////////////////////////

  
  if(ProcessKinFit((singleMu and muonIsoCut), false)){

    hCheck[1]->Fill(6.0);
    hCheck[2]->Fill(6.0, mu_wt);
    hCheck[5]->Fill(6.0, _sampleWeight*_PUWeight*_muEffWeight*_bTagWeight*_topPtReWeight);
    hCheck[50]->Fill(leptonAF.Pt(), mu_wt);
    hCheck[51]->Fill(leptonAF.Eta(), mu_wt);
    hCheck[52]->Fill(leptonAF.Phi(), mu_wt);
  
    hCheck[56]->Fill(bjlepAF.Pt(), mu_wt);
    hCheck[56]->Fill(bjhadAF.Pt(), mu_wt);
    hCheck[56]->Fill(cjhadAF.Pt(), mu_wt);
    hCheck[56]->Fill(sjhadAF.Pt(), mu_wt);

    hCheck[57]->Fill(bjlepAF.Eta(), mu_wt);
    hCheck[57]->Fill(bjhadAF.Eta(), mu_wt);
    hCheck[57]->Fill(cjhadAF.Eta(), mu_wt);
    hCheck[57]->Fill(sjhadAF.Eta(), mu_wt);

    hCheck[58]->Fill(bjlepAF.Phi(), mu_wt);
    hCheck[58]->Fill(bjhadAF.Phi(), mu_wt);
    hCheck[58]->Fill(cjhadAF.Phi(), mu_wt);
    hCheck[58]->Fill(sjhadAF.Phi(), mu_wt);
    
    hCheck[62]->Fill(neutrinoAF.Pt(), mu_wt);
    hCheck[63]->Fill(neutrinoAF.Phi(), mu_wt);

    hCheck[66]->Fill(selector->Jets.size(), mu_wt);
    hCheck[67]->Fill(selector->bJets.size(), mu_wt);
  
    hCheck[70]->Fill((cjhadAF+sjhadAF).M(), mu_wt);
    hCheck[72]->Fill((cjhadBF+sjhadBF).M(), mu_wt);
  }

  if(ProcessKinFit(false, (singleEle and eleIsoCut))){
    hCheck[3]->Fill(6.0);
    hCheck[4]->Fill(6.0, ele_wt);
    hCheck[53]->Fill(leptonAF.Pt(), ele_wt);
    hCheck[54]->Fill(leptonAF.Eta(), ele_wt);
    hCheck[55]->Fill(leptonAF.Phi(), ele_wt);

    hCheck[59]->Fill(bjlepAF.Pt(), ele_wt);
    hCheck[59]->Fill(bjhadAF.Pt(), ele_wt);
    hCheck[59]->Fill(cjhadAF.Pt(), ele_wt);
    hCheck[59]->Fill(sjhadAF.Pt(), ele_wt);

    hCheck[60]->Fill(bjlepAF.Eta(), ele_wt);
    hCheck[60]->Fill(bjhadAF.Eta(), ele_wt);
    hCheck[60]->Fill(cjhadAF.Eta(), ele_wt);
    hCheck[60]->Fill(sjhadAF.Eta(), ele_wt);

    hCheck[61]->Fill(bjlepAF.Phi(), ele_wt);
    hCheck[61]->Fill(bjhadAF.Phi(), ele_wt);
    hCheck[61]->Fill(cjhadAF.Phi(), ele_wt);
    hCheck[61]->Fill(sjhadAF.Phi(), ele_wt);

    hCheck[64]->Fill(neutrinoAF.Pt(), ele_wt);
    hCheck[65]->Fill(neutrinoAF.Phi(), ele_wt);

    hCheck[68]->Fill(selector->Jets.size(), ele_wt);
    hCheck[69]->Fill(selector->bJets.size(), ele_wt);    

    hCheck[71]->Fill((cjhadAF+sjhadAF).M(), ele_wt);
    hCheck[73]->Fill((cjhadBF+sjhadBF).M(), ele_wt);
  }
  
  // if(fProcessed%mod_num==0)
  //   Info("Process","Level 8");

  return kTRUE;
}
//_____________________________________________________________________________
bool SkimAna::ProcessKinFit(bool isMuon, bool isEle)
{
  if( (isMuon and isEle) or (!isMuon and !isEle) ) return false;

  bool isValid = false;
  float jetPtThresh, lepPtThresh;
  if(isNanoAOD){
    jetPtThresh = selector->jet_Pt_cut ;
    lepPtThresh = (isEle)? selector->ele_Pt_cut : selector->mu_Pt_cut ;
  }else{
    jetPtThresh = selector->jet_Pt_cut_miniAOD ;
    lepPtThresh = (isEle)? selector->ele_Pt_cut_miniAOD : selector->mu_Pt_cut_miniAOD ;
  }

  float jetEtaThresh, lepEtaThresh;
  if(isNanoAOD){
    jetEtaThresh = selector->jet_Eta_cut ;
    lepEtaThresh = (isEle)? selector->ele_Eta_cut : selector->mu_Eta_tight ; 
  }else{
    jetEtaThresh = selector->jet_Eta_cut_miniAOD ;
    lepEtaThresh = (isEle)? selector->ele_Eta_cut_miniAOD : selector->mu_Eta_tight ; //tight for muon in miniAOD is correct
  }
  

  jetVectors.clear();
  jetBtagVectors.clear();

  _run = event->run_ ;
  _event = event->event_ ;
  _lumis = event->lumis_ ;
  _isData = event->isData_ ;
  _nVtx = event->nVtx_ ;
  _nGoodVtx = event->nGoodVtx_ ;
  
  _nJet = selector->Jets.size();
  _nBJet = 0 ;
  _jetPt->clear() ;
  _jetEta->clear() ;
  _jetPhi->clear() ;
  _jetMass->clear() ;
  _jetDeepB->clear() ;
  double btagThreshold = (selector->useDeepCSVbTag) ? selector->btag_cut_DeepCSV  : selector->btag_cut  ;
  for (unsigned int ijet = 0; ijet < selector->Jets.size(); ijet++){
    int jetInd = selector->Jets.at(ijet);
    jetVector.SetPtEtaPhiM(selector->JetsPtSmeared.at(ijet), event->jetEta_[jetInd] , event->jetPhi_[jetInd] , event->jetMass_[jetInd] );
    jetVectors.push_back(jetVector);
    double jetBtag = (selector->useDeepCSVbTag) ? event->jetBtagDeepB_[jetInd] : event->jetBtagCSVV2_[jetInd] ;
    jetBtagVectors.push_back( jetBtag );
    
    _jetPt->push_back(selector->JetsPtSmeared.at(ijet));
    _jetEta->push_back(event->jetEta_[jetInd]);
    _jetPhi->push_back(event->jetPhi_[jetInd]);
    _jetMass->push_back(event->jetMass_[jetInd]);
    _jetDeepB->push_back(jetBtag);
    if(jetBtag>btagThreshold)
      _nBJet++;
  }
  
  _nMu = selector->Muons.size();
  _muPt->clear();
  _muEta->clear();
  _muPhi->clear();
  _muCharge->clear();
  if(isMuon){
    lepVector.SetPtEtaPhiM( event->muPt_[selector->Muons.at(0)] * event->muRoccoR_[selector->Muons.at(0)], 
			    event->muEta_[selector->Muons.at(0)] , event->muPhi_[selector->Muons.at(0)], 
			    TDatabasePDG::Instance()->GetParticle(13)->Mass());
    
    _muPt->push_back(event->muPt_[selector->Muons.at(0)] * event->muRoccoR_[selector->Muons.at(0)]);
    _muEta->push_back(event->muEta_[selector->Muons.at(0)]);
    _muPhi->push_back(event->muPhi_[selector->Muons.at(0)]);
    _muCharge->push_back(event->muCharge_[selector->Muons.at(0)]);
  }

  _nEle = selector->Electrons.size();
  _elePt->clear();
  _eleEta->clear();
  _elePhi->clear();
  _eleCharge->clear();
  if(isEle){
    lepVector.SetPtEtaPhiM( event->elePt_[selector->Electrons.at(0)], event->eleEta_[selector->Electrons.at(0)], 
			    event->elePhi_[selector->Electrons.at(0)], TDatabasePDG::Instance()->GetParticle(11)->Mass());
    _elePt->push_back(event->elePt_[selector->Electrons.at(0)]);
    _eleEta->push_back(event->eleEta_[selector->Electrons.at(0)]);
    _elePhi->push_back(event->elePhi_[selector->Electrons.at(0)]);
    _eleCharge->push_back(event->eleCharge_[selector->Electrons.at(0)]);
  }		    
  

  kinFit.SetJetVector(jetVectors);
  //kinFit.SetJetResVector(jetResolutionVectors);
  kinFit.SetBtagVector(jetBtagVectors);
  kinFit.SetLepton(lepVector);
  KinFit::LeptonType ltype = (isEle)?(KinFit::kElectron):(KinFit::kMuon); 
  kinFit.SetLeptonType(ltype);
  kinFit.SetMETPtPhi(selector->METPt, selector->METPhi);
  
  if ( kinFit.Fit() ){

    Chi2Array	     Chi2ToMass;
    vector<Chi2Array> Chi2ToMass_arr;    	    
    //Chi2ToMass_arr.clear();    
    
    for (unsigned int i = 0 ; i < kinFit.GetNCombinations() ; i++ ){
      
      leptonAF		= kinFit.GetLepton(i);
      neutrinoAF	= kinFit.GetNeutrino(i);
      bjlepAF		= kinFit.GetBLepton(i);
      bjhadAF		= kinFit.GetBHadron(i);
      cjhadAF		= kinFit.GetCHadron(i);
      sjhadAF		= kinFit.GetSHadron(i);
      
      leptonBF		= kinFit.GetLeptonUM(i);
      neutrinoBF        = kinFit.GetNeutrinoUM(i);
      bjlepBF		= kinFit.GetBLeptonUM(i);
      bjhadBF		= kinFit.GetBHadronUM(i);
      cjhadBF		= kinFit.GetCHadronUM(i);
      sjhadBF		= kinFit.GetSHadronUM(i);
      
      if(leptonAF.E()<0.0 or neutrinoAF.E()<0.0 or bjlepAF.E()<0.0 or bjhadAF.E()<0.0 or cjhadAF.E()<0.0 or sjhadAF.E()<0.0) continue;

      lepTopAF = (leptonAF + neutrinoAF + bjlepAF) ;
      hadTopAF = (bjhadAF + cjhadAF + sjhadAF);
      
      double mjj	= (cjhadBF + sjhadBF).M(); 
      double mjjkF	= (cjhadAF + sjhadAF).M(); 
      
      Chi2ToMass.chi2			= kinFit.GetChi2(i);
      Chi2ToMass.mass			= mjjkF;
      Chi2ToMass.mW			= (leptonAF + neutrinoAF).M();
      Chi2ToMass.A			= 1.;
      Chi2ToMass.B			= 1.;
      Chi2ToMass.ndf			= kinFit.GetNDF(i);
      Chi2ToMass.nb_iter		= kinFit.GetNumberOfIter(i);
      Chi2ToMass.chi2_thad		= kinFit.GetChi2_thad(i);
      Chi2ToMass.chi2_tlep		= kinFit.GetChi2_tlep(i);
      Chi2ToMass.leptonAF		= leptonAF;
      Chi2ToMass.neutrinoAF		= neutrinoAF;
      Chi2ToMass.bjlepAF		= bjlepAF; 
      Chi2ToMass.bjhadAF		= bjhadAF;
      Chi2ToMass.cjhadAF		= cjhadAF;
      Chi2ToMass.sjhadAF		= sjhadAF;
      Chi2ToMass.leptonBF		= leptonBF;
      Chi2ToMass.neutrinoBF		= neutrinoBF;
      Chi2ToMass.bjlepBF		= bjlepBF; 
      Chi2ToMass.bjhadBF		= bjhadBF;
      Chi2ToMass.cjhadBF		= cjhadBF;
      Chi2ToMass.sjhadBF		= sjhadBF;
      Chi2ToMass.bjhadAF_thad		= kinFit.GetBHadron_thad(i);
      Chi2ToMass.cjhadAF_thad		= kinFit.GetCHadron_thad(i);    
      Chi2ToMass.sjhadAF_thad		= kinFit.GetSHadron_thad(i);
      Chi2ToMass.leptonAF_tlep		= kinFit.GetLepton_tlep(i);
      Chi2ToMass.neutrinoAF_tlep	= kinFit.GetNeutrino_tlep(i);
      Chi2ToMass.bjlepAF_tlep		= kinFit.GetBLepton_tlep(i);
      
      Chi2ToMass.reslepEta		= kinFit.GetResLepEta(i);
      Chi2ToMass.reslepPhi		= kinFit.GetResLepPhi(i);
      Chi2ToMass.resneuEta		= kinFit.GetResNeuEta(i);
      Chi2ToMass.resneuPhi		= kinFit.GetResNeuPhi(i);
      Chi2ToMass.resbjlepEta		= kinFit.GetResBjLepEta(i);
      Chi2ToMass.resbjlepPhi		= kinFit.GetResBjLepPhi(i);
      Chi2ToMass.resbjhadEta		= kinFit.GetResBjHadEta(i);
      Chi2ToMass.resbjhadPhi		= kinFit.GetResBjHadPhi(i);
      Chi2ToMass.rescjhadEta		= kinFit.GetResCjHadEta(i);
      Chi2ToMass.rescjhadPhi		= kinFit.GetResCjHadPhi(i);
      Chi2ToMass.ressjhadEta		= kinFit.GetResSjHadEta(i);
      Chi2ToMass.ressjhadPhi		= kinFit.GetResSjHadPhi(i);
      
      Chi2ToMass.bjlep_id		= kinFit.GetJetID_BLep(i); 
      Chi2ToMass.bjhad_id		= kinFit.GetJetID_BHad(i); 
      Chi2ToMass.cjhad_id		= kinFit.GetJetID_CHad(i);
      Chi2ToMass.sjhad_id		= kinFit.GetJetID_SHad(i);
      
      Chi2ToMass_arr.push_back(Chi2ToMass);
      
      
    }// for loop over all kinfit combinations
    
    std::sort(Chi2ToMass_arr.begin(), Chi2ToMass_arr.end(), compareChi2Array);
    //
    int iloop = 0;
    for (auto x : Chi2ToMass_arr){
      //cout << "[" << x.chi2 << ", " << x.mass << "] ";
      
      //new
      double Rdifflep	= x.leptonBF.DeltaR(x.leptonAF); 
      double Rdiffbjlep	= x.bjlepBF.DeltaR(x.bjlepAF);  
      double Rdiffbjhad	= x.bjhadBF.DeltaR(x.bjhadAF); 
      double Rdiffcjhad	= x.cjhadBF.DeltaR(x.cjhadAF); 
      double Rdiffsjhad	= x.sjhadBF.DeltaR(x.sjhadAF); 
      
      double dRcjsjBF,	dRcjsjAF,  dRLepNuBF,	dRLepNuAF;
      dRcjsjBF	= x.cjhadBF.DeltaR(x.sjhadBF);     dRcjsjAF  = x.cjhadAF.DeltaR(x.sjhadAF);
      dRLepNuBF	= x.leptonBF.DeltaR(x.neutrinoBF); dRLepNuAF = x.leptonAF.DeltaR(x.neutrinoAF);
      //
      
      //if(iloop == 0 && x.chi2 > -1.0 ){ // Only 1st min chi2
      if(iloop == 0 && x.chi2 >= 0.0 && x.chi2 < 20.){ // Only 1st min chi2
    	if(
	   x.leptonAF.Pt() > lepPtThresh and x.neutrinoAF.Pt() > METThreshold 
	   and 
	   x.bjhadAF.Pt()  > jetPtThresh and x.bjlepAF.Pt() > jetPtThresh and x.cjhadAF.Pt() > jetPtThresh and x.sjhadAF.Pt() > jetPtThresh 
	   and
	   abs(x.leptonAF.Eta()) < lepEtaThresh 
	   and
	   abs(x.bjhadAF.Eta()) < jetEtaThresh and abs(x.bjlepAF.Eta()) < jetEtaThresh and abs(x.cjhadAF.Eta()) < jetEtaThresh and abs(x.sjhadAF.Eta()) < jetEtaThresh
    	   and
	   Rdifflep < 0.2 and Rdiffbjlep < 0.2 and Rdiffbjhad < 0.2 and Rdiffcjhad < 0.2 and Rdiffsjhad < 0.2
	   ){
	  
    	  //hMjjkFsc->Fill(x.mass);
	  
	  kinFitMinChi2		= x.chi2;
	  
	  leptonAF		= x.leptonAF;
	  neutrinoAF		= x.neutrinoAF;
	  
	  bjlepAF		= x.bjlepAF;
	  bjhadAF		= x.bjhadAF;
	  
	  cjhadAF		= x.cjhadAF;
	  sjhadAF		= x.sjhadAF;
	  
	  cjhadBF		= x.cjhadBF;
	  sjhadBF		= x.sjhadBF;
	  
	  isValid		= true;
	  
	  //To fill the Tree for DNN other MVA
	  _chi2			= x.chi2;
	  _chi2_thad     	= x.chi2_thad;
	  _chi2_tlep     	= x.chi2_tlep;
	  _NDF			= x.ndf;
	  _Nbiter		= x.nb_iter ;
	  _M_jj			= (x.cjhadBF + x.sjhadBF).M();
	  _M_jjkF		= x.mass;
	  
	  _pfMET		= x.neutrinoBF.Pt() ;
	  _pfMETPhi		= x.neutrinoBF.Phi() ;
	  _nu_px		= x.neutrinoBF.Px() ;
	  _nu_py		= x.neutrinoBF.Py() ;
	  _nu_pz		= x.neutrinoBF.Pz() ;
	  //_nu_pz_other	= 0 ;
	  _jetBlepPtUM		= x.bjlepBF.Pt() ;
	  _jetBlepEtaUM		= x.bjlepBF.Eta() ;
	  _jetBlepPhiUM		= x.bjlepBF.Phi() ;
	  _jetBlepEnergyUM	= x.bjlepBF.E() ;
	  _jetBhadPtUM		= x.bjhadBF.Pt() ;
	  _jetBhadEtaUM		= x.bjhadBF.Eta() ;
	  _jetBhadPhiUM		= x.bjhadBF.Phi() ;
	  _jetBhadEnergyUM	= x.bjhadBF.E() ;
	  _jetChadPtUM		= x.cjhadBF.Pt() ;
	  _jetChadEtaUM		= x.cjhadBF.Eta() ;
	  _jetChadPhiUM		= x.cjhadBF.Phi() ;
	  _jetChadEnergyUM	= x.cjhadBF.E() ;
	  _jetShadPtUM		= x.sjhadBF.Pt() ;
	  _jetShadEtaUM		= x.sjhadBF.Eta()  ;
	  _jetShadPhiUM		= x.sjhadBF.Phi()  ;
	  _jetShadEnergyUM	= x.sjhadBF.E()  ;
	  
	  _lepPt		= x.leptonAF.Pt() ;
	  _lepEta		= x.leptonAF.Eta() ;
	  _lepPhi		= x.leptonAF.Phi() ;
	  _lepEnergy		= x.leptonAF.E() ;
	  _metPx		= x.neutrinoAF.Px() ;
	  _metPy		= x.neutrinoAF.Py() ;
	  _metPz		= x.neutrinoAF.Pz() ;
	  _jetBlepPt		= x.bjlepAF.Pt() ;
	  _jetBlepEta		= x.bjlepAF.Eta() ;
	  _jetBlepPhi		= x.bjlepAF.Phi() ;
	  _jetBlepEnergy	= x.bjlepAF.E() ;
	  _jetBhadPt		= x.bjhadAF.Pt() ;
	  _jetBhadEta		= x.bjhadAF.Eta() ;
	  _jetBhadPhi		= x.bjhadAF.Phi() ;
	  _jetBhadEnergy	= x.bjhadAF.E() ;
	  _jetChadPt		= x.cjhadAF.Pt() ;
	  _jetChadEta		= x.cjhadAF.Eta() ;
	  _jetChadPhi		= x.cjhadAF.Phi() ;
	  _jetChadEnergy	= x.cjhadAF.E() ;
	  _jetShadPt		= x.sjhadAF.Pt() ;
	  _jetShadEta		= x.sjhadAF.Eta()  ;
	  _jetShadPhi		= x.sjhadAF.Phi()  ;
	  _jetShadEnergy	= x.sjhadAF.E()  ;
	  
	  _reslepEta		= x.reslepEta ;   
	  _reslepPhi		= x.reslepPhi ;   
	  _resneuEta		= x.resneuEta ;   
	  _resneuPhi		= x.resneuPhi ;
	  _resbjlepEta		= x.resbjlepEta ;
	  _resbjlepPhi		= x.resbjlepPhi ; 
	  _resbjhadEta		= x.resbjhadEta ; 
	  _resbjhadPhi		= x.resbjhadPhi ;
	  _rescjhadEta		= x.rescjhadEta ; 
	  _rescjhadPhi		= x.rescjhadPhi ; 
	  _ressjhadEta		= x.ressjhadEta ; 
	  _ressjhadPhi		= x.ressjhadPhi ; 
	  _bjlepDeepCSV		= event->jetBtagDeepB_[x.bjlep_id] ;
	  _bjhadDeepCSV		= event->jetBtagDeepB_[x.bjhad_id] ; 
	  _cjhadDeepCSV		= event->jetBtagDeepB_[x.cjhad_id] ;  
	  _sjhadDeepCSV		= event->jetBtagDeepB_[x.sjhad_id] ;
	  
	  //Fill for non-negative chi2
	  outputTree->Fill();
	}//DeltaR and pt cuts
      }//iloop == 0 condition      
      iloop++;
    }// for loop over chi2 arrays

    if(isMuon){
      if(Chi2ToMass_arr.size()>=1 and Chi2ToMass_arr.at(0).leptonAF.Pt() > 0.0)
	hMinChi2_mu->Fill(Chi2ToMass_arr.at(0).chi2);
      if(Chi2ToMass_arr.size()>=2 and Chi2ToMass_arr.at(0).leptonAF.Pt() > 0.0)
	h2MinChi2_mu->Fill(Chi2ToMass_arr.at(1).chi2);
      if(Chi2ToMass_arr.size()>=3 and Chi2ToMass_arr.at(0).leptonAF.Pt() > 0.0)
	h3MinChi2_mu->Fill(Chi2ToMass_arr.at(2).chi2);
      if(Chi2ToMass_arr.size()>=4 and Chi2ToMass_arr.at(0).leptonAF.Pt() > 0.0)
	h4MinChi2_mu->Fill(Chi2ToMass_arr.at(3).chi2);
      if(Chi2ToMass_arr.size()>=5 and Chi2ToMass_arr.at(0).leptonAF.Pt() > 0.0)
	h5MinChi2_mu->Fill(Chi2ToMass_arr.at(4).chi2);
    }else{
      if(Chi2ToMass_arr.size()>=1 and Chi2ToMass_arr.at(0).leptonAF.Pt() > 0.0)
	hMinChi2_ele->Fill(Chi2ToMass_arr.at(0).chi2);
      if(Chi2ToMass_arr.size()>=2 and Chi2ToMass_arr.at(0).leptonAF.Pt() > 0.0)
	h2MinChi2_ele->Fill(Chi2ToMass_arr.at(1).chi2);
      if(Chi2ToMass_arr.size()>=3 and Chi2ToMass_arr.at(0).leptonAF.Pt() > 0.0)
	h3MinChi2_ele->Fill(Chi2ToMass_arr.at(2).chi2);
      if(Chi2ToMass_arr.size()>=4 and Chi2ToMass_arr.at(0).leptonAF.Pt() > 0.0)
	h4MinChi2_ele->Fill(Chi2ToMass_arr.at(3).chi2);
      if(Chi2ToMass_arr.size()>=5 and Chi2ToMass_arr.at(0).leptonAF.Pt() > 0.0)
	h5MinChi2_ele->Fill(Chi2ToMass_arr.at(4).chi2);
    }

    Chi2ToMass_arr.clear();
    
  }//if fit converges
  
  kinFit.Clear();
  jetVectors.clear();
  jetBtagVectors.clear();
  _jetPt->clear() ;
  _jetEta->clear() ;
  _jetPhi->clear() ;
  _jetMass->clear() ;
  _jetDeepB->clear() ;
  _muPt->clear();
  _muEta->clear();
  _muPhi->clear();
  _muCharge->clear();
  _elePt->clear();
  _eleEta->clear();
  _elePhi->clear();
  _eleCharge->clear();
  
  return isValid;
}

//_____________________________________________________________________________
void SkimAna::SlaveTerminate()
{
  
  Info("SlaveTerminate",
       "sample : %s, year : %d, mode : %s", fSample.Data(), fYear, fMode.Data());

  
  // File closure
  TDirectory *savedir = gDirectory;
  
  for(int ifile=0;ifile<1;ifile++){

    savedir->cd();
    
    fFile[ifile]->cd();
    
    for(int icheck=0;icheck<(fNTestHist+fNSyst);icheck++)
      hCheck[icheck]->Write();
    
    printf("DataMu & ");
    for (int ibin=2;ibin<hCheck[1]->GetNbinsX();ibin++){
      if(hCheck[1]->GetBinContent(ibin)>0.0 and hCheck[1]->GetBinContent(ibin+1)>0.0){
	if(hCheck[1]->GetBinContent(ibin)>1e6){
	  printf("%.4e & ",hCheck[1]->GetBinContent(ibin)); 
	}else{
	  printf("%.1f & ",hCheck[1]->GetBinContent(ibin));
	}
      }else if(hCheck[1]->GetBinContent(ibin)>0.0 and TMath::AreEqualAbs(hCheck[1]->GetBinContent(ibin+1),0.0,1.e-5)){
	printf("%.1f \\\\\\hline ",hCheck[1]->GetBinContent(ibin));
      }
    }
    printf("\n");
    
    printf("DataEle & ");
    for (int ibin=2;ibin<hCheck[3]->GetNbinsX();ibin++){
      if(hCheck[3]->GetBinContent(ibin)>0.0 and hCheck[3]->GetBinContent(ibin+1)>0.0){
	if(hCheck[3]->GetBinContent(ibin)>1e6){
	  printf("%.4e & ",hCheck[3]->GetBinContent(ibin)); 
	}else{
	  printf("%.1f & ",hCheck[3]->GetBinContent(ibin));
	}
      }else if(hCheck[3]->GetBinContent(ibin)>0.0 and TMath::AreEqualAbs(hCheck[3]->GetBinContent(ibin+1),0.0,1.e-5)){
	printf("%.1f \\\\\\hline ",hCheck[3]->GetBinContent(ibin));
      }
    }
    printf("\n");
    
    hMinChi2_mu->Write();
    h2MinChi2_mu->Write();
    h3MinChi2_mu->Write();
    h4MinChi2_mu->Write();
    h5MinChi2_mu->Write();

    hMinChi2_ele->Write();
    h2MinChi2_ele->Write();
    h3MinChi2_ele->Write();
    h4MinChi2_ele->Write();
    h5MinChi2_ele->Write();
      
    fFile[ifile]->cd();
    
    savedir->cd();
    
    fFile[ifile]->Close();
    
    
    if (fMode.BeginsWith("proof")) {
      Info("SlaveTerminate", "objects saved into '%s%s': sending related TProofOutputFile ...",
	   fProofFile[ifile]->GetFileName(), fProofFile[ifile]->GetOptionsAnchor());
      fProofFile[ifile]->Print();
      fOutput->Add(fProofFile[ifile]);    
    }
    
  }//file loop
  
  
  for(int ifile=1;ifile<2;ifile++){
    
    savedir->cd();
    fFile[ifile]->cd();
    outputTree->Write();
    fFile[ifile]->Close();
    savedir->cd();
    
    if (fMode.BeginsWith("proof")) {
      Info("SlaveTerminate", "objects saved into '%s%s': sending related TProofOutputFile ...",
	   fProofFile[ifile]->GetFileName(), fProofFile[ifile]->GetOptionsAnchor());
      fProofFile[ifile]->Print();
      fOutput->Add(fProofFile[ifile]);    
    }
  }  

  if(PUweighter)
    delete PUweighter;
    
  if(jecvar)
    delete jecvar;
  
  if(event)
    delete event;
  if(selector)
    delete selector;
  if(evtPick)
    delete evtPick;
  
  if(muSFa)
    delete muSFa ;
  if(muSFb)
    delete muSFb ;
  if(eleSF)
    delete eleSF ;
  
  if(f_trackSF_BCDEF)
    delete f_trackSF_BCDEF;
  if(f_trackSF_GH)
    delete f_trackSF_GH;
  
  totEvents.clear();
  totEventsUS.clear();
  fnameList.clear();

  crossSections.clear();
  numberOfEvents.clear();
  LumiWZ.clear();
}

//_____________________________________________________________________________
void SkimAna::Terminate()
{
// function called at the end of the event loop

   if (!fInput) Info("Terminate", "processed %lld events", fProcessed);
   
   TString option = GetOption();
   Info("Terminate", "stopping SkimAna with process option: %s", option.Data());
   
}

bool SkimAna::ExecSerial(const char* infile)
{
  
  TString option = GetOption();
  Info("ExecSerial", "starting SkimAna with process option: %s", option.Data());
  Info("ExecSerial", "opening file %s", infile);
       
  TFile *fin = TFile::Open(infile);
  TTree *tree = (TTree *)fin->Get("Events");
  SlaveBegin(tree);
  tree->GetEntry(0);
  Notify();
  for(Long64_t ientry = 0 ; ientry < tree->GetEntries() ; ientry++){
  //for(Long64_t ientry = 0 ; ientry < 20 ; ientry++){
    Process(ientry);
  }
  SlaveTerminate();

  fin->Close();
  delete fin;

  return true;
}
