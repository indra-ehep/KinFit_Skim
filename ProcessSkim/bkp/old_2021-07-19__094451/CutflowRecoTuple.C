/**********************************************************************
 Created on : 14/06/2021
 Purpose    : Analyse the Reco tree to create cutflow plots 
              (format adapted from h1analysis)
 Author     : Indranil Das, Visiting Fellow
 Email      : indranil.das@cern.ch | indra.ehep@gmail.com
**********************************************************************/

#include "CutflowRecoTuple.h"
#include "TH2.h"
#include "TF1.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TPaveStats.h"
#include "TMath.h"
#include "TProof.h"


//_____________________________________________________________________________
void CutflowRecoTuple::GetArguments(){

  TString option = GetOption();
  //Info("GetArguments","ending CutflowRecoTuple with process option: %s", option.Data());

  Ssiz_t from = 0;
  TString tok;
  // Now analyze the arguments
  while (option.Tokenize(tok , from , "|")) {
    if(tok.BeginsWith("sample"))
      fSample = ((TObjString *) (tok.Tokenize("="))->At(1))->GetString();
    if(tok.BeginsWith("year"))
      fYear = (((TObjString *) (tok.Tokenize("="))->At(1))->GetString()).Atoi();
    if(tok.BeginsWith("mode"))
      fMode = ((TObjString *) (tok.Tokenize("="))->At(1))->GetString();
  }
  
  if(fSample.BeginsWith("Data")){
    fSampleDir = "data_obs";
    isData = true;
  }else{
    fSampleDir = fSample;
    isData = false;
  }

  TString hostname = gSystem->HostName();
  if(hostname.BeginsWith("Indra-Rjn"))
    fBasePath = "/Data/CMS-Analysis/NanoAOD-Analysis";
  else if(hostname.BeginsWith("lxplus"))
    fBasePath = "/afs/cern.ch/user/i/idas/CMS-Analysis/NanoAOD-Analysis";
  else if(hostname.BeginsWith("ui"))
    fBasePath = "/home/idas";
    
}

//_____________________________________________________________________________
void CutflowRecoTuple::Begin(TTree * /*tree*/)
{
   // This is needed when re-processing the object
   Reset();

   //print the option specified in the Process function.
   TString option = GetOption();
   Info("Begin", "starting CutflowRecoTuple with process option: %s", option.Data());
   // Test tokenize

   if (fChain) fChain->SetEntryList(0);
}


//_____________________________________________________________________________
Int_t CutflowRecoTuple::CreateHistoArrays()
{
   // Create the histogram arrays
  fNSyst = 19;
  fNHist = 2*fNSyst ; 
  
  // Histos array
  hpresel_HT = new TH1F*[fNHist];
  hpresel_M3 = new TH1F*[fNHist];
  hpresel_MET = new TH1F*[fNHist];
  hpresel_M_jjkF = new TH1F*[fNHist];
  hpresel_M_jj = new TH1F*[fNHist];
  hpresel_Nbjet = new TH1F*[fNHist];
  hpresel_Njet = new TH1F*[fNHist];
  hpresel_WtransMass = new TH1F*[fNHist];
  hpresel_elePhi = new TH1F*[fNHist];
  hpresel_elePt = new TH1F*[fNHist];
  hpresel_eleSCEta = new TH1F*[fNHist];
  hpresel_muEta = new TH1F*[fNHist];
  hpresel_muPhi = new TH1F*[fNHist];
  hpresel_muPt = new TH1F*[fNHist];
  hpresel_nVtx = new TH1F*[fNHist];
  
  fFileDir = new TDirectory*[fNHist];  
  
  const char *syst[] = {"Base", "BTagSF_bDown", "BTagSF_bUp", "BTagSF_lDown", "BTagSF_lUp",
                        "EleEffDown", "EleEffUp", "fsrDown", "fsrUp", "isrDown", "isrUp",
                        "MuEffDown", "MuEffUp", "PdfDown", "PdfUp", "PUDown", "PUUp",
                        "Q2Down", "Q2Up"};

  for(int ifile=0;ifile<2;ifile++){

    TDirectory *savedir = gDirectory;
    savedir->cd();

    fFile[ifile]->cd();
    TDirectory *d1 = fFile[ifile]->mkdir(fSampleDir.Data());
    d1->cd();
    
    for(int isyst=0;isyst<fNSyst;isyst++){

      if(isData && isyst>0) continue;

      TDirectory *d2 = d1->mkdir(syst[isyst]);
      d2->cd();
      //d2->pwd();
      fFileDir[ifile*fNSyst + isyst] = d2->mkdir("SR");
      //fFileDir[ifile*fNSyst + isyst] = d2->mkdir("KF");
      fFileDir[ifile*fNSyst + isyst]->cd();
      //fFileDir[ifile*fNSyst + isyst]->pwd();
      // cout <<"file ptr : " << fFileDir[ifile*fNSyst + isyst] << endl;
      // cout << "index : " << ifile*fNSyst + isyst << endl;

      hpresel_HT[ifile*fNSyst + isyst] = new TH1F("presel_HT","presel_HT", 150, 0, 1500);
      hpresel_M3[ifile*fNSyst + isyst] = new TH1F("presel_M3","presel_M3", 100, 0, 1000);
      hpresel_MET[ifile*fNSyst + isyst] = new TH1F("presel_MET","presel_MET", 100, 0, 1000);
      hpresel_M_jjkF[ifile*fNSyst + isyst] = new TH1F("presel_M_jjkF","presel_M_jjkF", 80, 0, 400);
      hpresel_M_jj[ifile*fNSyst + isyst] = new TH1F("presel_M_jj","presel_M_jj", 80, 0, 400);
      hpresel_Nbjet[ifile*fNSyst + isyst] = new TH1F("presel_Nbjet","presel_Nbjet", 10, 0, 10);
      hpresel_Njet[ifile*fNSyst + isyst] = new TH1F("presel_Njet","presel_Njet", 16, -0.5, 15.5);
      hpresel_WtransMass[ifile*fNSyst + isyst] = new TH1F("presel_WtransMass","presel_WtransMass", 100, 0, 1000);
      hpresel_elePhi[ifile*fNSyst + isyst] = new TH1F("presel_elePhi","presel_elePhi", 100,-3.15,3.15);
      hpresel_elePt[ifile*fNSyst + isyst] = new TH1F("presel_elePt","presel_elePt", 100, 0, 1000);
      hpresel_eleSCEta[ifile*fNSyst + isyst] = new TH1F("presel_eleSCEta","presel_eleSCEta", 100,-2.4,2.4);
      hpresel_muEta[ifile*fNSyst + isyst] = new TH1F("presel_muEta","presel_muEta", 100,-2.4,2.4);
      hpresel_muPhi[ifile*fNSyst + isyst] = new TH1F("presel_muPhi","presel_muPhi", 100,-3.15,3.15);
      hpresel_muPt[ifile*fNSyst + isyst] = new TH1F("presel_muPt","presel_muPt", 100,0,1000);
      hpresel_nVtx[ifile*fNSyst + isyst] = new TH1F("presel_nVtx","presel_nVtx", 50,0,50);

      hpresel_HT[ifile*fNSyst + isyst]->SetDirectory(fFileDir[ifile*fNSyst + isyst]);
      hpresel_M3[ifile*fNSyst + isyst]->SetDirectory(fFileDir[ifile*fNSyst + isyst]);
      hpresel_MET[ifile*fNSyst + isyst]->SetDirectory(fFileDir[ifile*fNSyst + isyst]);
      hpresel_M_jjkF[ifile*fNSyst + isyst]->SetDirectory(fFileDir[ifile*fNSyst + isyst]);
      hpresel_M_jj[ifile*fNSyst + isyst]->SetDirectory(fFileDir[ifile*fNSyst + isyst]);
      hpresel_Nbjet[ifile*fNSyst + isyst]->SetDirectory(fFileDir[ifile*fNSyst + isyst]);
      hpresel_Njet[ifile*fNSyst + isyst]->SetDirectory(fFileDir[ifile*fNSyst + isyst]);
      hpresel_WtransMass[ifile*fNSyst + isyst]->SetDirectory(fFileDir[ifile*fNSyst + isyst]);
      hpresel_elePhi[ifile*fNSyst + isyst]->SetDirectory(fFileDir[ifile*fNSyst + isyst]);
      hpresel_elePt[ifile*fNSyst + isyst]->SetDirectory(fFileDir[ifile*fNSyst + isyst]);
      hpresel_eleSCEta[ifile*fNSyst + isyst]->SetDirectory(fFileDir[ifile*fNSyst + isyst]);
      hpresel_muEta[ifile*fNSyst + isyst]->SetDirectory(fFileDir[ifile*fNSyst + isyst]);
      hpresel_muPhi[ifile*fNSyst + isyst]->SetDirectory(fFileDir[ifile*fNSyst + isyst]);
      hpresel_muPt[ifile*fNSyst + isyst]->SetDirectory(fFileDir[ifile*fNSyst + isyst]);
      hpresel_nVtx[ifile*fNSyst + isyst]->SetDirectory(fFileDir[ifile*fNSyst + isyst]);

      hpresel_HT[ifile*fNSyst + isyst]->Sumw2(kTRUE);
      hpresel_M3[ifile*fNSyst + isyst]->Sumw2(kTRUE);
      hpresel_MET[ifile*fNSyst + isyst]->Sumw2(kTRUE);
      hpresel_M_jjkF[ifile*fNSyst + isyst]->Sumw2(kTRUE);
      hpresel_M_jj[ifile*fNSyst + isyst]->Sumw2(kTRUE);
      hpresel_Nbjet[ifile*fNSyst + isyst]->Sumw2(kTRUE);
      hpresel_Njet[ifile*fNSyst + isyst]->Sumw2(kTRUE);
      hpresel_WtransMass[ifile*fNSyst + isyst]->Sumw2(kTRUE);
      hpresel_elePhi[ifile*fNSyst + isyst]->Sumw2(kTRUE);
      hpresel_elePt[ifile*fNSyst + isyst]->Sumw2(kTRUE);
      hpresel_eleSCEta[ifile*fNSyst + isyst]->Sumw2(kTRUE);
      hpresel_muEta[ifile*fNSyst + isyst]->Sumw2(kTRUE);
      hpresel_muPhi[ifile*fNSyst + isyst]->Sumw2(kTRUE);
      hpresel_muPt[ifile*fNSyst + isyst]->Sumw2(kTRUE);
      hpresel_nVtx[ifile*fNSyst + isyst]->Sumw2(kTRUE);
      
    }

    savedir->cd();
  }
  
  fNTestHist = 40;
  hCheck = new TH1D*[fNTestHist+fNSyst];
  TDirectory *savedir = gDirectory;
  savedir->cd();
  fFile[2]->cd();
  
  hCheck[0] = new TH1D("_evtWeight","_evtWeight",2000, -1, 1);
  hCheck[1] = new TH1D("_PUweight","_PUweight", 100, 0, 2);
  hCheck[2] = new TH1D("_muEffWeight","_muEffWeight",100, 0, 2);
  hCheck[3] = new TH1D("_eleEffWeight","_eleEffWeight",100, 0, 2);
  hCheck[4] = new TH1D("_btagWeight_1a","_btagWeight_1a",2000, -1, 1);
  hCheck[5] = new TH1D("_btagWeight_1a_b_Do","_btagWeight_1a_b_Do",1000,-5.0,5.0);
  hCheck[6] = new TH1D("_btagWeight_1a_b_Up","_btagWeight_1a_b_Up",1000,-5.0,5.0);
  hCheck[7] = new TH1D("_btagWeight_1a_l_Do","_btagWeight_1a_l_Do",1000,-5.0,5.0);
  hCheck[8] = new TH1D("_btagWeight_1a_l_Up","_btagWeight_1a_l_Up",1000,-5.0,5.0);
  hCheck[9] = new TH1D("_eleEffWeight_Do","_eleEffWeight_Do",1000,-5.0,5.0);
  hCheck[10] = new TH1D("_eleEffWeight_Up","_eleEffWeight_Up",1000,-5.0,5.0);
  hCheck[11] = new TH1D("_FSRweight_Do","_FSRweight_Do",1000,-5.0,5.0);
  hCheck[12] = new TH1D("_FSRweight_Up","_FSRweight_Up",1000,-5.0,5.0);
  hCheck[13] = new TH1D("_ISRweight_Do","_ISRweight_Do",1000,-5.0,5.0);
  hCheck[14] = new TH1D("_ISRweight_Up","_ISRweight_Up",1000,-5.0,5.0);
  hCheck[15] = new TH1D("_muEffWeight_Do","_muEffWeight_Do",1000,-5.0,5.0);
  hCheck[16] = new TH1D("_muEffWeight_Up","_muEffWeight_Up",1000,-5.0,5.0);
  hCheck[17] = new TH1D("_pdfweight_Do","_pdfweight_Do",1000,-5.0,5.0);
  hCheck[18] = new TH1D("_pdfweight_Up","_pdfweight_Up",1000,-5.0,5.0);
  hCheck[19] = new TH1D("_PUweight_Do","_PUweight_Do",1000,-5.0,5.0);
  hCheck[20] = new TH1D("_PUweight_Up","_PUweight_Up",1000,-5.0,5.0);
  hCheck[21] = new TH1D("_q2weight_Do","_q2weight_Do",1000,-5.0,5.0);
  hCheck[22] = new TH1D("_q2weight_Up","_q2weight_Up",1000,-5.0,5.0);
  hCheck[23] = new TH1D("_cutflow", "_cutflow", 10, 0, 10);
  hCheck[24] = new TH1D("_cutflow_data", "_cutflow_data", 10, 0, 10);
  hCheck[25] = new TH1D("_cutflow1", "_cutflow1", 10, 0, 10);
  hCheck[26] = new TH1D("_cutflow2", "_cutflow2", 10, 0, 10);
  hCheck[27] = new TH1D("_cutflow3", "_cutflow3", 10, 0, 10);
  hCheck[28] = new TH1D("_cutflow4", "_cutflow4", 10, 0, 10);
  hCheck[29] = new TH1D("_sampleWeight", "_sampleWeight", 2000, -1, 1);
  hCheck[30] = new TH1D("_lumiWeight", "_lumiWeight", 2000, -1, 1);
  hCheck[31] = new TH1D("_nMC_totalUS", "_nMC_totalUS", 10000, 1.e6, 1.e10);
  hCheck[32] = new TH1D("_xss", "_xss", 10000, 0, 10000);
  hCheck[33] = new TH1D("njet", "njet", 20, 0, 20);
  hCheck[34] = new TH1D("hMuPt", "hMuPt", 1000,0.,1000.);
  hCheck[35] = new TH1D("hMuEta", "hMuEta", 100,-3.,3.);
  hCheck[36] = new TH1D("hJetPt", "hJetPt", 1000,0.,1000.);
  hCheck[37] = new TH1D("hJetEta", "hJetEta", 100,-3.,3.);
  hCheck[38] = new TH1D("hEvtwtBVC", "hEvtwtBVC",2000, -1, 1);
  hCheck[39] = new TH1D("hEvtwtAVC", "hEvtwtAVC",2000, -1, 1);

  // End of fNTestHist
  for(int isyst=0;isyst<fNSyst;isyst++)
    hCheck[fNTestHist+isyst] = new TH1D(Form("weight_%d",isyst), Form("weight_%d",isyst),1000,-5.0,5.0);
  
  savedir->cd();

   // Done
   return true;
}

//_____________________________________________________________________________
void CutflowRecoTuple::ReadMuEffFile(int year)
{
  if (year == 2016){

    // muSFa = new MuonSF("weight/MuEleSF/mu2016/EfficienciesStudies_2016_legacy_rereco_rootfiles_RunBCDEF_SF_ID.root", "NUM_TightID_DEN_genTracks_eta_pt",
    // 		       "weight/MuEleSF/mu2016/EfficienciesStudies_2016_legacy_rereco_rootfiles_RunBCDEF_SF_ISO.root", "NUM_TightRelIso_DEN_TightIDandIPCut_eta_pt",
    // 		       "weight/MuEleSF/mu2016/EfficienciesStudies_2016_trigger_EfficienciesAndSF_RunBtoF.root", "IsoMu24_OR_IsoTkMu24_PtEtaBins/abseta_pt_ratio");
	
    // muSFb = new MuonSF("weight/MuEleSF/mu2016/EfficienciesStudies_2016_legacy_rereco_rootfiles_RunGH_SF_ID.root", "NUM_TightID_DEN_genTracks_eta_pt",
    // 		       "weight/MuEleSF/mu2016/EfficienciesStudies_2016_legacy_rereco_rootfiles_RunGH_SF_ISO.root", "NUM_TightRelIso_DEN_TightIDandIPCut_eta_pt",
    // 		       "weight/MuEleSF/mu2016/EfficienciesStudies_2016_trigger_EfficienciesAndSF_RunGtoH.root", "IsoMu24_OR_IsoTkMu24_PtEtaBins/abseta_pt_ratio");

    // muSFa = new MuonSF("weight/MuEleSF/mu2016/EfficienciesStudies_2016_legacy_rereco_rootfiles_RunBCDEF_SF_ID.root", "NUM_MediumID_DEN_genTracks_eta_pt",
    // 		       "weight/MuEleSF/mu2016/EfficienciesStudies_2016_legacy_rereco_rootfiles_RunBCDEF_SF_ISO.root", "NUM_TightRelIso_DEN_MediumID_eta_pt",
    // 		       "weight/MuEleSF/mu2016/EfficienciesStudies_2016_trigger_EfficienciesAndSF_RunBtoF.root", "IsoMu24_OR_IsoTkMu24_PtEtaBins/abseta_pt_ratio");
	
    // muSFb = new MuonSF("weight/MuEleSF/mu2016/EfficienciesStudies_2016_legacy_rereco_rootfiles_RunGH_SF_ID.root", "NUM_MediumID_DEN_genTracks_eta_pt",
    // 		       "weight/MuEleSF/mu2016/EfficienciesStudies_2016_legacy_rereco_rootfiles_RunGH_SF_ISO.root", "NUM_TightRelIso_DEN_MediumID_eta_pt",
    // 		       "weight/MuEleSF/mu2016/EfficienciesStudies_2016_trigger_EfficienciesAndSF_RunGtoH.root", "IsoMu24_OR_IsoTkMu24_PtEtaBins/abseta_pt_ratio");

    muSFa = new MuonSF(Form("%s/CutFlow/weight/MuEleSF/mu2016/EfficienciesStudies_2016_legacy_rereco_rootfiles_RunBCDEF_SF_ID.root",fBasePath.Data()), 
		       "NUM_MediumID_DEN_genTracks_eta_pt",
    		       Form("%s/CutFlow/weight/MuEleSF/mu2016/EfficienciesStudies_2016_legacy_rereco_rootfiles_RunBCDEF_SF_ISO.root",fBasePath.Data()), 
		       "NUM_TightRelIso_DEN_MediumID_eta_pt",
    		       Form("%s/CutFlow/weight/MuEleSF/mu2016/EfficienciesStudies_2016_trigger_EfficienciesAndSF_RunBtoF.root",fBasePath.Data()), 
		       "IsoMu24_OR_IsoTkMu24_PtEtaBins/abseta_pt_ratio");
    
    muSFb = new MuonSF(Form("%s/CutFlow/weight/MuEleSF/mu2016/EfficienciesStudies_2016_legacy_rereco_rootfiles_RunGH_SF_ID.root",fBasePath.Data()), 
		       "NUM_MediumID_DEN_genTracks_eta_pt",
    		       Form("%s/CutFlow/weight/MuEleSF/mu2016/EfficienciesStudies_2016_legacy_rereco_rootfiles_RunGH_SF_ISO.root",fBasePath.Data()), 
		       "NUM_TightRelIso_DEN_MediumID_eta_pt",
    		       Form("%s/CutFlow/weight/MuEleSF/mu2016/EfficienciesStudies_2016_trigger_EfficienciesAndSF_RunGtoH.root",fBasePath.Data()), 
		       "IsoMu24_OR_IsoTkMu24_PtEtaBins/abseta_pt_ratio");
    
    // f_trackSF_BCDEF 	= new TFile("../Analysis/Analysis/stack/muonSF/trackingSF_BCDEF.root");
    // f_trackSF_GH	= new TFile("../Analysis/Analysis/stack/muonSF/trackingSF_GH.root");
    f_trackSF_BCDEF 	= new TFile(Form("%s/Analysis/Analysis/stack/muonSF/trackingSF_BCDEF.root",fBasePath.Data()));
    f_trackSF_GH	= new TFile(Form("%s/Analysis/Analysis/stack/muonSF/trackingSF_GH.root",fBasePath.Data()));
    tg_trackSF_BCDEF 	= (TGraphAsymmErrors*)f_trackSF_BCDEF->Get("ratio_eff_aeta_dr030e030_corr");
    tg_trackSF_GH 	= (TGraphAsymmErrors*)f_trackSF_GH->Get("ratio_eff_aeta_dr030e030_corr");
    
    //Trigger SF
    f_trigSF_BCDEF 	= new TFile(Form("%s/Analysis/Analysis/stack/muonSF/triggreSF_BCDEF.root",fBasePath.Data()));
    f_trigSF_GH 	= new TFile(Form("%s/Analysis/Analysis/stack/muonSF/triggreSF_GH.root",fBasePath.Data()));
    h2_trigSF_BCDEF 	= (TH2D*)f_trigSF_BCDEF->Get("IsoMu24_OR_IsoTkMu24_PtEtaBins/abseta_pt_ratio");
    h2_trigSF_GH 	= (TH2D*)f_trigSF_GH->Get("IsoMu24_OR_IsoTkMu24_PtEtaBins/abseta_pt_ratio");
    //Identification SF
    f_idSF_BCDEF 	= new TFile(Form("%s/Analysis/Analysis/stack/muonSF/idSF_BCDEF.root",fBasePath.Data()));
    f_idSF_GH 		= new TFile(Form("%s/Analysis/Analysis/stack/muonSF/idSF_GH.root",fBasePath.Data()));
    h2_idSF_BCDEF 	= (TH2D*)f_idSF_BCDEF->Get("MC_NUM_MediumID2016_DEN_genTracks_PAR_pt_eta/abseta_pt_ratio");
    h2_idSF_GH 		= (TH2D*)f_idSF_GH->Get("MC_NUM_MediumID2016_DEN_genTracks_PAR_pt_eta/abseta_pt_ratio");
    //Isolation SF
    f_isoSF_BCDEF	= new TFile(Form("%s/Analysis/Analysis/stack/muonSF/isoSF_BCDEF.root",fBasePath.Data()));
    f_isoSF_GH 		= new TFile(Form("%s/Analysis/Analysis/stack/muonSF/isoSF_GH.root",fBasePath.Data()));
    h2_isoSF_BCDEF	= (TH2D*)f_isoSF_BCDEF->Get("TightISO_MediumID_pt_eta/abseta_pt_ratio");
    h2_isoSF_GH 	= (TH2D*)f_isoSF_GH->Get("TightISO_MediumID_pt_eta/abseta_pt_ratio");
    
  }

  return;
}
//_____________________________________________________________________________
double CutflowRecoTuple::getMuonSF(TH2D *h2, double eta, double pt, double maxPt)
{
  TAxis *xaxis = h2->GetXaxis();
  TAxis *yaxis = h2->GetYaxis();
  double sf = 1.0;
  Int_t binX = xaxis->FindBin(abs(eta));
  Int_t binY = 1.0;
  //since the Pt range of 2D histo is <=maxPt
  //for Pt >maxPt, we use SF of Pt = maxPt
  if(pt<=maxPt) binY = yaxis->FindBin(pt);
  else binY = yaxis->FindBin(maxPt);
  sf = h2->GetBinContent(binX, binY);
  //double err = 1.0;
  //err = h2->GetBinError(binX, binY);
  return sf;
}
//_____________________________________________________________________________
double CutflowRecoTuple::getMuonTrackSF(TGraphAsymmErrors *tg, double eta)
{
  Double_t *eta_array = tg->GetX();
  Double_t *sf_array = tg->GetY();
  Int_t n_points = tg->GetN();
  double SF = 1.0;
  if(abs(eta)<eta_array[0]-0.10) SF = sf_array[0];//bin width is 0.20
  for(Int_t i = 0; i < n_points; i++){
    if(abs(eta)>=eta_array[i]-0.10 && abs(eta)< eta_array[i]+0.10) SF = sf_array[i];
  }
  if(abs(eta)>=eta_array[n_points-1]+0.10) SF = sf_array[n_points -1];
  return SF;
}
//_____________________________________________________________________________
double CutflowRecoTuple::GetMuEff(double pt, double eta, double iso, int year)
{
  double muEff_combined = 1.0;
  
  vector<double> muWeights_a    = muSFa->getMuSF(pt,eta,1, year);
  vector<double> muWeights_b    = muSFb->getMuSF(pt,eta,1, year);
  vector<double> muWeights;
  for (int i=0; i < int(muWeights_a.size()); i++){
    muWeights.push_back( muWeights_a.at(i) * 19.695422959/35.921875595 + 
			 muWeights_b.at(i) * 16.226452636/35.921875595);
  }
    
  double muSFtrack_BCDEF 	= getMuonTrackSF(tg_trackSF_BCDEF, eta);
  double muSFtrack_GH 	        = getMuonTrackSF(tg_trackSF_GH, eta);
  double muSFtrack 		= muSFtrack_BCDEF * 19.695422959/35.921875595 + muSFtrack_GH * 16.226452636/35.921875595;
  
  if(iso<0.15)
    muEff_combined    = muWeights.at(1) * muWeights.at(2) * muWeights.at(3) * muSFtrack; //id * iso * trig * track
  else
    muEff_combined    = muWeights.at(1) * muWeights.at(3) * muSFtrack; //id * trig * track
  

  // double muSFtrig_BCDEF 	= getMuonSF(h2_trigSF_BCDEF, eta, pt, 499);
  // double muSFtrig_GH 		= getMuonSF(h2_trigSF_GH, eta, pt, 499);
  // double muSFtrig 		= muSFtrig_BCDEF * 19.695422959/35.921875595 + muSFtrig_GH * 16.226452636/35.921875595;
  // //identification
  // double muSFid_BCDEF 	= getMuonSF(h2_idSF_BCDEF, eta, pt, 119);
  // double muSFid_GH 		= getMuonSF(h2_idSF_GH, eta, pt, 119);
  // double muSFid 		= muSFid_BCDEF * 19.695422959/35.921875595 + muSFid_GH * 16.226452636/35.921875595;
  // //isolation
  // double muSFiso = 1.0;
  // if(iso < 0.15){
  //   double muSFiso_BCDEF 	= getMuonSF(h2_isoSF_BCDEF, eta, pt, 119);
  //   double muSFiso_GH 		= getMuonSF(h2_isoSF_GH, eta, pt, 119);
  //   muSFiso 		= muSFiso_BCDEF * 19.695422959/35.921875595 + muSFiso_GH * 16.226452636/35.921875595;
  // }

  //muEff_combined    = muSFid * muSFiso * muSFtrig * muSFtrack; //id * iso * trig * track
  
  muWeights_a.clear();
  muWeights_b.clear();
  muWeights.clear();
  
  return muEff_combined;
}

//_____________________________________________________________________________
float CutflowRecoTuple::getBtagSF_1a(string sysType, bool verbose, float btag_cut){

    double weight = 1.0;

    double jetPt;
    double jetEta;
    double jetBtag;
    int jetFlavor;
    double SFb;
    double Eff;

    double pMC=1;
    double pData=1;
	
    string b_sysType = "central";
    string l_sysType = "central";
    if (sysType=="b_up"){
	b_sysType = "up";
    } else if (sysType=="b_down"){
	b_sysType = "down";
    } else if (sysType=="l_up"){
	l_sysType = "up";
    } else if (sysType=="l_down"){
	l_sysType = "down";
    }	
    if (verbose){
	cout << "Btagging Scale Factors"<<endl;
    }

    int xbin,ybin;
    int maxbinX, maxbinY;
    for(unsigned int ijet = 0 ; ijet < UInt_t(_nJet) ; ijet++){
      
      jetPt = _jetPt->at(ijet);
      jetEta = fabs(_jetEta->at(ijet));
      //jetFlavor = abs(_jetHadFlvr->at(ijet));
      jetFlavor = abs(_jetPartFlvr->at(ijet));
      jetBtag = _jetCSVV2->at(ijet);
      
      //To explicitly select tagged light quarks
      //if (jetBtag > btag_cut or jetFlavor==5) continue ;
      
      //To explicitly select the tagged b-quarks quarks
      //if (jetBtag < btag_cut and jetFlavor!=5) continue ;
      
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

      if (jetBtag > btag_cut){
	pMC *= Eff;
	pData *= Eff*SFb;
	//nBjet = nBjet + 1;
      } else {
	pMC *= 1. - Eff;
	pData *= 1. - (Eff*SFb);
      }
	
      //ijet    jetflavor   eff    pmc    pdata
       // printf("\t ijet : %03d, jetflavor : %0d, (pt,eta) : (%5.4f,%5.4f), (xbin,ybin) : (%d,%d), (maxbinX,maxbinY) : (%d,%d), jetBtag : %5.4f, nBjet : %d, Eff : %5.3f, pMC : %7.5f, pData : %7.5f\n",
       //        ijet,jetFlavor,jetPt,jetEta,xbin,ybin,maxbinX,maxbinY,jetBtag,nBjet,Eff,pMC,pData);

      if (verbose){
	//cout << "    jetPt="<<jetPt<<"  jetEta="<<jetEta<<"  jetFlavor="<<jetFlavor<<"  jetBtag="<<jetBtag<<"  Tagged="<<(jetBtag>selector->btag_cut)<<"  Eff="<<Eff<<"  SF="<<SFb<<endl;
	//cout << "          --p(MC)="<<pMC<<"  --p(Data)="<<pData << endl;
      }
      //niter =  niter + 1;
    }

    //    weight = pData/pMC;
    if (pMC==0){
	//      cout << "Inf weight" << endl;
	//	cout << pData << " / " << pMC << endl;
	weight = 0.;
    } else {
      weight = pData/pMC;
    }
    if (verbose){
	cout << "  FinalWeight="<<weight<<endl;
    }
    
    return weight;
    
}

//_____________________________________________________________________________
void CutflowRecoTuple::SlaveBegin(TTree *tree)
{
  //initialize the Tree branch addresses
  Init(tree);
  
  //print the option specified in the Process function.
  TString option = GetOption();
  Info("SlaveBegin",
       "starting CutflowRecoTuple with process option: %s (tree: %p)", option.Data(), tree);

  GetArguments();
  Info("SlaveBegin",
       "sample : %s, year : %d, mode : %s", fSample.Data(), fYear, fMode.Data());
  
  initCrossSections();

  hElePt = new TH1D("hElePt","hElePt",100,0,1000.0); 
  
  char *filename[3];
  // filename[0] = Form("/tmp/%s_Mu.root",fSample.Data()) ;
  // filename[1] = Form("/tmp/%s_Ele.root",fSample.Data()) ;
  // filename[2] = Form("root_files/%s_weights.root",fSample.Data()) ;
  filename[0] = Form("%s_Mu.root",fSample.Data()) ;
  filename[1] = Form("%s_Ele.root",fSample.Data()) ;
  filename[2] = Form("%s_weights.root",fSample.Data()) ;
  
  for(int ifile=0;ifile<3;ifile++){
    
    if(fMode.BeginsWith("proof")){
      fProofFile[ifile] = new TProofOutputFile(filename[ifile], "M");
      fFile[ifile] = fProofFile[ifile]->OpenFile("RECREATE");
      if (fFile[ifile] && fFile[ifile]->IsZombie()) SafeDelete(fFile[ifile]);
    }else{
      fFile[ifile] = TFile::Open(filename[ifile],"RECREATE");
    }
    
    // Cannot continue
    if (!fFile[ifile]) {
      TString amsg = TString::Format("CutflowRecoTuple::SlaveBegin: could not create '%s':"
				     " instance is invalid!", fFile[ifile]->GetName());
      Abort(amsg, kAbortProcess);
      return;
    }

  }//ifile loop
  
  
  CreateHistoArrays() ;
  ReadMuEffFile(fYear);
  loadBtagEff();

}

//_____________________________________________________________________________

// void CutflowRecoTuple::loadBtagEff()
// {
  
//   string year = "2016";
//   std::string fName = Form("%s/CutFlow/weight/BtagSF/btag_efficiencies_%s.root",fBasePath.Data(),year.c_str());
  
//   calib = BTagCalibration("csvv2", Form("%s/CutFlow/weight/BtagSF/CSVv2_Moriond17_B_H.csv",fBasePath.Data()));
//   reader = BTagCalibrationReader(BTagEntry::OP_MEDIUM, "central", {"up", "down"});
  
//   reader.load(calib, BTagEntry::FLAV_B,"comb");          
//   reader.load(calib, BTagEntry::FLAV_C, "comb"); 
//   reader.load(calib, BTagEntry::FLAV_UDSG, "incl"); 
  
//   std::string effType = "Other";
//   if (fSampleType.Contains("TTGamma") or fSample.Contains("TTGamma")){
//     effType = "Top";
//   }
//   if (fSampleType.Contains("TTbar") or fSample.Contains("TTbar")){
//     effType = "Top";
//   }
  
//   std::string leffName = effType+"_l_efficiency";
//   std::string ceffName = effType+"_c_efficiency";
//   std::string beffName = effType+"_b_efficiency";
  
//   TFile* inputFile = TFile::Open(fName.c_str(),"read");
//   l_eff = (TH2D*) inputFile->Get(leffName.c_str());
//   c_eff = (TH2D*) inputFile->Get(ceffName.c_str());
//   b_eff = (TH2D*) inputFile->Get(beffName.c_str());

// }				   

//_____________________________________________________________________________

void CutflowRecoTuple::loadBtagEff()
{
  
  //string year = "2016";
  std::string fName = Form("%s/CutFlow/weight/BtagSF/MiniAOD/%s_btag_efficiency.root",fBasePath.Data(),fSample.Data());
  
  calib = BTagCalibration("csvv2", Form("%s/CutFlow/weight/BtagSF/CSVv2_Moriond17_B_H.csv",fBasePath.Data()));
  reader = BTagCalibrationReader(BTagEntry::OP_MEDIUM, "central", {"up", "down"});
  
  reader.load(calib, BTagEntry::FLAV_B,"comb");          
  reader.load(calib, BTagEntry::FLAV_C, "comb"); 
  reader.load(calib, BTagEntry::FLAV_UDSG, "incl"); 
  
  std::string effType = "Other";
  // if (fSampleType.Contains("TTGamma") or fSample.Contains("TTGamma")){
  //   effType = "Top";
  // }
  // if (fSampleType.Contains("TTbar") or fSample.Contains("TTbar")){
  //   effType = "Top";
  // }
  
  std::string leffName = effType+"_l_efficiency";
  std::string ceffName = effType+"_c_efficiency";
  std::string beffName = effType+"_b_efficiency";
  
  TFile* inputFile = TFile::Open(fName.c_str(),"read");
  l_eff = (TH2D*) inputFile->Get(leffName.c_str());
  c_eff = (TH2D*) inputFile->Get(ceffName.c_str());
  b_eff = (TH2D*) inputFile->Get(beffName.c_str());

}				   

//_____________________________________________________________________________
double CutflowRecoTuple::ScaleLumiW(Int_t nLHEPart){

  //0.7060, 0.1937, 0.0583, 0.0191, 0.0195
  
  Int_t nJets = nLHEPart - 2;
  double fracLumiWt = 1.0;
  
  // switch(nJets) {
  // case 0:
  //   fracLumiWt = 0.7060 ;
  //   break;
  // case 1:
  //   fracLumiWt = 0.1937 ;
  //   break;
  // case 2:
  //   fracLumiWt = 0.0583 ;
  //   break;
  // case 3:
  //   fracLumiWt = 0.0191 ;
  //   break;
  // case 4:
  //   fracLumiWt = 0.0195 ;
  //   break;
  // default:
  //   fracLumiWt = 1.0;
  // }
  // return fracLumiWt ;
  
  //2.1028, 0.2368, 0.1206, 0.0571, 0.0639 //using dataset similar volume of miniAOD
  //2.1208, 0.2342, 0.1192, 0.0562, 0.0676 //using dataset similar volume of miniAOD
  switch(nJets) {
  case 0:
    fracLumiWt = 2.1208 ;
    break;
  case 1:
    fracLumiWt = 0.2342 ;
    break;
  case 2:
    fracLumiWt = 0.1192 ;
    break;
  case 3:
    fracLumiWt = 0.0562 ;
    break;
  case 4:
    fracLumiWt = 0.0676 ;
    break;
  default:
    fracLumiWt = 1.0;
  }
  return fracLumiWt ;
  
  // if(nJets==0)      return 2.11;
  // else if(nJets==1) return 0.23;
  // else if(nJets==2) return 0.119;
  // else if(nJets==3) return 0.0562;
  // else if(nJets>=4) return 0.0671;
  
  // //0.7120, 0.1922, 0.0577, 0.0188, 0.0206

  // switch(nJets) {
  // case 0:
  //   fracLumiWt = 0.7120 ;
  //   break;
  // case 1:
  //   fracLumiWt = 0.1922 ;
  //   break;
  // case 2:
  //   fracLumiWt = 0.0577 ;
  //   break;
  // case 3:
  //   fracLumiWt = 0.0188 ;
  //   break;
  // case 4:
  //   fracLumiWt = 0.0206 ;
  //   break;
  // default:
  //   fracLumiWt = 1.0;
  // }

  // return fracLumiWt ;

}


//_____________________________________________________________________________
double CutflowRecoTuple::ScaleLumiZ(Int_t nLHEPart){
  //0.0397, 0.0127, 0.0132, 0.0135, 0.0110
  //updated 0.0400, 0.0127, 0.0133, 0.0136, 0.0111


  Int_t nJets = nLHEPart - 2;
  double fracLumiWt = 1.0;
  
  // switch(nJets) {
  // case 0:
  //   fracLumiWt = 0.0400 ;
  //   break;
  // case 1:
  //   fracLumiWt = 0.0127 ;
  //   break;
  // case 2:
  //   fracLumiWt = 0.0133 ;
  //   break;
  // case 3:
  //   fracLumiWt = 0.0136 ;
  //   break;
  // case 4:
  //   fracLumiWt = 0.0111 ;
  //   break;
  // default:
  //   fracLumiWt = 1.0;
  // }

  //  0.1175, 0.0161, 0.0170, 0.0175, 0.0135
  switch(nJets) {
  case 0:
    fracLumiWt = 0.1175 ;
    break;
  case 1:
    fracLumiWt = 0.0161 ;
    break;
  case 2:
    fracLumiWt = 0.0170 ;
    break;
  case 3:
    fracLumiWt = 0.0175 ;
    break;
  case 4:
    fracLumiWt = 0.0135 ;
    break;
  default:
    fracLumiWt = 1.0;
  }

  return fracLumiWt ;
}


//_____________________________________________________________________________
Bool_t CutflowRecoTuple::Process(Long64_t entry)
{
// entry is the entry number in the current Tree
// Selection function to select D* and D0.

  fProcessed++;
  
  // to read complete event, call fChain->GetTree()->GetEntry(entry)
  //fChain->GetTree()->GetEntry(entry);
  _nJet  = -9999;
  _nBJet = -9999;
  
  
  // br_passPresel_Mu->GetEntry(entry);
  // br_passAll_Mu->GetEntry(entry);
  // br_passPresel_Ele->GetEntry(entry);
  // // br_HT->GetEntry(entry);
  // // br_M3->GetEntry(entry);
  // br_pfMET->GetEntry(entry);
  // // br_M_jjkF->GetEntry(entry);
  // // br_M_jj->GetEntry(entry);
  // br_nJet->GetEntry(entry);
  // br_nBJet->GetEntry(entry);
  // br_WtransMass->GetEntry(entry);
  // br_elePhi->GetEntry(entry);
  // br_elePt->GetEntry(entry);
  // br_eleSCEta->GetEntry(entry);
  // br_muEta->GetEntry(entry);
  // br_muPhi->GetEntry(entry);
  // br_muPt->GetEntry(entry);
  // br_nVtx->GetEntry(entry);
  // br_chi2->GetEntry(entry);

  _evtWeight = 1.0; _lumiWeight = 1.0; _PUweight = 1.0; _muEffWeight = 1.0; _eleEffWeight = 1.0; _btagWeight_1a = 1.0 ;
  
  _btagWeight_1a_b_Do = 1.0 ;  _btagWeight_1a_b_Up = 1.0 ; _btagWeight_1a_l_Do = 1.0 ; _btagWeight_1a_l_Up = 1.0;
  _eleEffWeight_Do = 1.0; _eleEffWeight_Up = 1.0 ; _FSRweight_Do = 1.0 ; _FSRweight_Up = 1.0 ;
  _ISRweight_Do = 1.0 ; _ISRweight_Up = 1.0 ; _muEffWeight_Do = 1.0 ; _muEffWeight_Up = 1.0 ; 
  _pdfweight_Do = 1.0 ; _pdfweight_Up = 1.0 ; _PUweight_Do = 1.0 ; _PUweight_Up = 1.0 ; 
  _q2weight_Do = 1.0 ; _q2weight_Up = 1.0 ;
  _isPVGood = false;
  
  // br_evtWeight->GetEntry(entry) ;
  // br_lumiWeight->GetEntry(entry) ;
  // br_PUweight->GetEntry(entry) ;
  // br_muEffWeight->GetEntry(entry) ;
  // br_eleEffWeight->GetEntry(entry) ;  // 1 * 1 * 1 * 1 for q2 * pdf * isr * fsr
  // br_btagWeight_1a->GetEntry(entry) ;

  // br_btagWeight_1a_b_Do->GetEntry(entry) ;
  // br_btagWeight_1a_b_Up->GetEntry(entry) ;
  // br_btagWeight_1a_l_Do->GetEntry(entry) ;
  // br_btagWeight_1a_l_Up->GetEntry(entry) ;
  // br_eleEffWeight_Do->GetEntry(entry) ;
  // br_eleEffWeight_Up->GetEntry(entry) ;
  // br_FSRweight_Do->GetEntry(entry) ;  
  // br_FSRweight_Up->GetEntry(entry) ;
  // br_ISRweight_Do->GetEntry(entry) ;
  // br_ISRweight_Up->GetEntry(entry) ;  
  // br_muEffWeight_Do->GetEntry(entry) ;
  // br_muEffWeight_Up->GetEntry(entry) ;
  // br_pdfweight_Do->GetEntry(entry) ;
  // br_pdfweight_Up->GetEntry(entry) ;
  // br_PUweight_Do->GetEntry(entry) ;
  // br_PUweight_Up->GetEntry(entry) ;
  // br_q2weight_Do->GetEntry(entry) ;
  // br_q2weight_Up->GetEntry(entry) ;
  
  fChain->GetTree()->GetEntry(entry);
  
  hCheck[0]->Fill(_evtWeight);
  hCheck[1]->Fill(_PUweight);
  hCheck[2]->Fill(_muEffWeight);
  // hCheck[3]->Fill(_eleEffWeight);
  hCheck[4]->Fill(_btagWeight_1a);
  // hCheck[5]->Fill(_btagWeight_1a_b_Do);
  // hCheck[6]->Fill(_btagWeight_1a_b_Up);
  // hCheck[7]->Fill(_btagWeight_1a_l_Do);
  // hCheck[8]->Fill(_btagWeight_1a_l_Up);
  // hCheck[9]->Fill(_eleEffWeight_Do);
  // hCheck[10]->Fill(_eleEffWeight_Up);
  // hCheck[11]->Fill(_FSRweight_Do);
  // hCheck[12]->Fill(_FSRweight_Up);
  // hCheck[13]->Fill(_ISRweight_Do);
  // hCheck[14]->Fill(_ISRweight_Up);
  // hCheck[15]->Fill(_muEffWeight_Do);
  // hCheck[16]->Fill(_muEffWeight_Up);
  // hCheck[17]->Fill(_pdfweight_Do);
  // hCheck[18]->Fill(_pdfweight_Up);
  // hCheck[19]->Fill(_PUweight_Do);
  // hCheck[20]->Fill(_PUweight_Up);
  // hCheck[21]->Fill(_q2weight_Do);
  // hCheck[22]->Fill(_q2weight_Up);
  hCheck[29]->Fill(_sampleWeight);
  hCheck[30]->Fill(_lumiWeight);
  hCheck[31]->Fill(_nMC_totalUS);
  hCheck[32]->Fill(_xss);
  
  // if(entry%1000==0)
  //   cout << "_nMC_totalUS " << _nMC_totalUS << endl;
  
  //double luminosity = 35921.0;
  double genWeight = _evtWeight / _lumiWeight ;
  double scalelumi = 1.0;
  if(fSampleType.Contains("Wjets") || fSampleType.Contains("W1jets") || fSampleType.Contains("W2jets") || fSampleType.Contains("W3jets") || fSampleType.Contains("W4jets")){
    scalelumi = ScaleLumiW(_nLHEPart);
    local_evtWeight = scalelumi * 35921.0/1000.;
  }
  
  if(fSampleType.Contains("DYjetsM50") || fSampleType.Contains("DY1jetsM50") || fSampleType.Contains("DY2jetsM50") || fSampleType.Contains("DY3jetsM50") || fSampleType.Contains("DY4jetsM50")){
    scalelumi = ScaleLumiZ(_nLHEPart) ;
    local_evtWeight = scalelumi * 35921.0/1000.;
  }

  if(entry==0){
    cout << " scalelumi " << scalelumi << endl;
    cout << " local_evtWeight " << local_evtWeight << endl;
  }

  //_evtWeight = _evtWeight; //_evtWeight should remain untouched

  //_lumiWeight = (_evtWeight<0.0) ? (-1.0*_lumiWeight) : _lumiWeight ;
  _lumiWeight = genWeight*local_evtWeight;

  _sampleWeight = local_evtWeight ; //_sampleWeight should mimic the MiniAOD

  int nBJetMD = 0;
  float btagCut = 0.8484;
  for(int ijet = 0 ; ijet<_nJet ; ijet++)
    if(_jetCSVV2->at(ijet) > btagCut)
      nBJetMD++;

  float btagWeight_1a_MD = getBtagSF_1a("central", false, 0.8484);

  bool hasMuon = false;
  //////////////////////////////////////////////////////////////////
  if(_passTrigger_mu){
    hCheck[23]->Fill(0.0,_evtWeight*_PUweight);
    hCheck[38]->Fill(_evtWeight);
  }
  if(_passTrigger_mu and _isPVGood and _passFilter){
    hCheck[23]->Fill(1.0,_evtWeight*_PUweight);

    hCheck[39]->Fill(_evtWeight);
    hCheck[33]->Fill(_nJet);
    for(int ijet = 0 ; ijet<_nJet ; ijet++){
      hCheck[36]->Fill(_jetPt->at(ijet));
      hCheck[37]->Fill(_jetEta->at(ijet));
    }
  }
  if(_passTrigger_mu and _isPVGood and _passFilter and _nMu == 1 and _nMuLoose == 0 and _nEle == 0 and _nEleLoose == 0){
    _muEffWeight = GetMuEff(_muPt->at(0), _muEta->at(0), _muPFRelIso->at(0), fYear);
    //if(_muPFRelIso->at(0) < 0.4 and _isPVGood){
    if(_muPFRelIso->at(0) < 0.15){
      hCheck[23]->Fill(2.0,_evtWeight*_PUweight*_muEffWeight);
      hasMuon = true;
    }
    hCheck[34]->Fill(_muPt->at(0));
    hCheck[35]->Fill(_muEta->at(0));
  }
  if(_passTrigger_mu and _isPVGood and _passFilter and hasMuon and _nJet>=4)
    hCheck[23]->Fill(3.0,_evtWeight*_PUweight*_muEffWeight);
  if(_passTrigger_mu and _isPVGood and _passFilter and hasMuon and _nJet>=4 and _pfMET >= 20.0)
    hCheck[23]->Fill(4.0,_evtWeight*_PUweight*_muEffWeight);
  if(_passTrigger_mu and _isPVGood and _passFilter and hasMuon and _nJet>=4 and _pfMET >= 20.0 and nBJetMD>=2)
    hCheck[23]->Fill(5.0,_evtWeight*_PUweight*_muEffWeight*btagWeight_1a_MD);
  // if(hasMuon and _nJet>=4 and nBJetMD>=2)
  //   hCheck[23]->Fill(6.0,_evtWeight*_PUweight*_muEffWeight*btagWeight_1a_MD);
  //////////////////////////////////////////////////////////////////

  // For Data i.e. without weights //////////////////////////////////
  if(_passTrigger_mu)
    hCheck[24]->Fill(0.0);
  if(_passTrigger_mu and _isPVGood and _passFilter)
    hCheck[24]->Fill(1.0);
  if(_passTrigger_mu and _isPVGood and _passFilter and hasMuon)
    hCheck[24]->Fill(2.0);
  if(_passTrigger_mu and _isPVGood and _passFilter and hasMuon and _nJet>=4)
    hCheck[24]->Fill(3.0);
  if(_passTrigger_mu and _isPVGood and _passFilter and hasMuon and _nJet>=4 and _pfMET >= 20.0)
    hCheck[24]->Fill(4.0);
  if(_passTrigger_mu and _isPVGood and _passFilter and hasMuon and _nJet>=4 and _pfMET >= 20.0 and nBJetMD>=2)
    hCheck[24]->Fill(5.0);
  // if(hasMuon and _nJet>=4 and nBJetMD>=2)
  //   hCheck[24]->Fill(6.0);
  //////////////////////////////////////////////////////////////////
  
  // Following Ravindra's suggestion
  /////////////////////////////////////////////////////////////////
  if(_passTrigger_mu)
    hCheck[25]->Fill(0.0,_lumiWeight*_PUweight);
  if(_passTrigger_mu and _isPVGood and _passFilter)
    hCheck[25]->Fill(1.0,_lumiWeight*_PUweight);
  if(_passTrigger_mu and _isPVGood and _passFilter and hasMuon)
    hCheck[25]->Fill(2.0,_lumiWeight*_PUweight*_muEffWeight);
  if(_passTrigger_mu and _isPVGood and _passFilter and hasMuon and _nJet>=4)
    hCheck[25]->Fill(3.0,_lumiWeight*_PUweight*_muEffWeight);
  if(_passTrigger_mu and _isPVGood and _passFilter and hasMuon and _nJet>=4 and _pfMET >= 20.0)
    hCheck[25]->Fill(4.0,_lumiWeight*_PUweight*_muEffWeight);
  if(_passTrigger_mu and _isPVGood and _passFilter and hasMuon and _nJet>=4 and _pfMET >= 20.0 and nBJetMD>=2)
    hCheck[25]->Fill(5.0,_lumiWeight*_PUweight*_muEffWeight*btagWeight_1a_MD);
  // if(hasMuon and _nJet>=4 and nBJetMD>=2)
  //   hCheck[25]->Fill(6.0,_lumiWeight*_PUweight*_muEffWeight*btagWeight_1a_MD);
  ////////////////////////////////////////////////////////////////

  // Following sampleweight as in miniAOD code
  /////////////////////////////////////////////////////////////////
  if(_passTrigger_mu)
    hCheck[26]->Fill(0.0, _sampleWeight*_PUweight);
  if(_passTrigger_mu and _isPVGood and _passFilter)
    hCheck[26]->Fill(1.0, _sampleWeight*_PUweight);
  if(_passTrigger_mu and _isPVGood and _passFilter and hasMuon)
    hCheck[26]->Fill(2.0,_sampleWeight*_PUweight*_muEffWeight);
  if(_passTrigger_mu and _isPVGood and _passFilter and hasMuon and _nJet>=4)
    hCheck[26]->Fill(3.0,_sampleWeight*_PUweight*_muEffWeight);
  if(_passTrigger_mu and _isPVGood and _passFilter and hasMuon and _nJet>=4 and _pfMET >= 20.0)
    hCheck[26]->Fill(4.0,_sampleWeight*_PUweight*_muEffWeight);
  if(_passTrigger_mu and _isPVGood and _passFilter and hasMuon and _nJet>=4 and _pfMET >= 20.0 and nBJetMD>=2)
    hCheck[26]->Fill(5.0,_sampleWeight*_PUweight*_muEffWeight*btagWeight_1a_MD);
  // if(hasMuon and _nJet>=4 and nBJetMD>=2)
  //   hCheck[25]->Fill(6.0,_lumiWeight*_PUweight*_muEffWeight*btagWeight_1a_MD);
  ////////////////////////////////////////////////////////////////
  
  // double *weight = new double[fNSyst];
  
  // weight[0] = _evtWeight * _PUweight * _muEffWeight * _eleEffWeight * 1.0 * 1.0 * 1.0 * 1.0 * _btagWeight_1a;
  // weight[1] = _evtWeight * _PUweight * _muEffWeight * _eleEffWeight * 1.0 * 1.0 * 1.0 * 1.0 * _btagWeight_1a_b_Do;
  // weight[2] = _evtWeight * _PUweight * _muEffWeight * _eleEffWeight * 1.0 * 1.0 * 1.0 * 1.0 * _btagWeight_1a_b_Up;
  // weight[3] = _evtWeight * _PUweight * _muEffWeight * _eleEffWeight * 1.0 * 1.0 * 1.0 * 1.0 * _btagWeight_1a_l_Do;
  // weight[4] = _evtWeight * _PUweight * _muEffWeight * _eleEffWeight * 1.0 * 1.0 * 1.0 * 1.0 * _btagWeight_1a_l_Up;
  // weight[5] = _evtWeight * _PUweight * _muEffWeight * _eleEffWeight_Do * 1.0 * 1.0 * 1.0 * 1.0 * _btagWeight_1a;
  // weight[6] = _evtWeight * _PUweight * _muEffWeight * _eleEffWeight_Up * 1.0 * 1.0 * 1.0 * 1.0 * _btagWeight_1a;
  // weight[7] = _evtWeight * _PUweight * _muEffWeight * _eleEffWeight * 1.0 * 1.0 * 1.0 * _FSRweight_Do * _btagWeight_1a;
  // weight[8] = _evtWeight * _PUweight * _muEffWeight * _eleEffWeight * 1.0 * 1.0 * 1.0 * _FSRweight_Up * _btagWeight_1a;
  // weight[9] = _evtWeight * _PUweight * _muEffWeight * _eleEffWeight * 1.0 * 1.0 * _ISRweight_Do * 1.0 * _btagWeight_1a;
  // weight[10] = _evtWeight * _PUweight * _muEffWeight * _eleEffWeight * 1.0 * 1.0 * _ISRweight_Up * 1.0 * _btagWeight_1a;
  // weight[11] = _evtWeight * _PUweight * _muEffWeight_Do * _eleEffWeight * 1.0 * 1.0 * 1.0 * 1.0 * _btagWeight_1a;
  // weight[12] = _evtWeight * _PUweight * _muEffWeight_Up * _eleEffWeight * 1.0 * 1.0 * 1.0 * 1.0 * _btagWeight_1a;
  // weight[13] = _evtWeight * _PUweight * _muEffWeight * _eleEffWeight * 1.0 * _pdfweight_Do * 1.0 * 1.0 * _btagWeight_1a;
  // weight[14] = _evtWeight * _PUweight * _muEffWeight * _eleEffWeight * 1.0 * _pdfweight_Up * 1.0 * 1.0 * _btagWeight_1a;
  // weight[15] = _evtWeight * _PUweight_Do * _muEffWeight * _eleEffWeight * 1.0 * 1.0 * 1.0 * 1.0 * _btagWeight_1a;
  // weight[16] = _evtWeight * _PUweight_Up * _muEffWeight * _eleEffWeight * 1.0 * 1.0 * 1.0 * 1.0 * _btagWeight_1a;
  // weight[17] = _evtWeight * _PUweight * _muEffWeight * _eleEffWeight * _q2weight_Do * 1.0 * 1.0 * 1.0 * _btagWeight_1a;
  // weight[18] = _evtWeight * _PUweight * _muEffWeight * _eleEffWeight * _q2weight_Up * 1.0 * 1.0 * 1.0 * _btagWeight_1a;

  // // weight[0] = _lumiWeight * _PUweight * _muEffWeight * _eleEffWeight * 1.0 * 1.0 * 1.0 * 1.0 * _btagWeight_1a;
  // // weight[1] = _lumiWeight * _PUweight * _muEffWeight * _eleEffWeight * 1.0 * 1.0 * 1.0 * 1.0 * _btagWeight_1a_b_Do;
  // // weight[2] = _lumiWeight * _PUweight * _muEffWeight * _eleEffWeight * 1.0 * 1.0 * 1.0 * 1.0 * _btagWeight_1a_b_Up;
  // // weight[3] = _lumiWeight * _PUweight * _muEffWeight * _eleEffWeight * 1.0 * 1.0 * 1.0 * 1.0 * _btagWeight_1a_l_Do;
  // // weight[4] = _lumiWeight * _PUweight * _muEffWeight * _eleEffWeight * 1.0 * 1.0 * 1.0 * 1.0 * _btagWeight_1a_l_Up;
  // // weight[5] = _lumiWeight * _PUweight * _muEffWeight * _eleEffWeight_Do * 1.0 * 1.0 * 1.0 * 1.0 * _btagWeight_1a;
  // // weight[6] = _lumiWeight * _PUweight * _muEffWeight * _eleEffWeight_Up * 1.0 * 1.0 * 1.0 * 1.0 * _btagWeight_1a;
  // // weight[7] = _lumiWeight * _PUweight * _muEffWeight * _eleEffWeight * 1.0 * 1.0 * 1.0 * _FSRweight_Do * _btagWeight_1a;
  // // weight[8] = _lumiWeight * _PUweight * _muEffWeight * _eleEffWeight * 1.0 * 1.0 * 1.0 * _FSRweight_Up * _btagWeight_1a;
  // // weight[9] = _lumiWeight * _PUweight * _muEffWeight * _eleEffWeight * 1.0 * 1.0 * _ISRweight_Do * 1.0 * _btagWeight_1a;
  // // weight[10] = _lumiWeight * _PUweight * _muEffWeight * _eleEffWeight * 1.0 * 1.0 * _ISRweight_Up * 1.0 * _btagWeight_1a;
  // // weight[11] = _lumiWeight * _PUweight * _muEffWeight_Do * _eleEffWeight * 1.0 * 1.0 * 1.0 * 1.0 * _btagWeight_1a;
  // // weight[12] = _lumiWeight * _PUweight * _muEffWeight_Up * _eleEffWeight * 1.0 * 1.0 * 1.0 * 1.0 * _btagWeight_1a;
  // // weight[13] = _lumiWeight * _PUweight * _muEffWeight * _eleEffWeight * 1.0 * _pdfweight_Do * 1.0 * 1.0 * _btagWeight_1a;
  // // weight[14] = _lumiWeight * _PUweight * _muEffWeight * _eleEffWeight * 1.0 * _pdfweight_Up * 1.0 * 1.0 * _btagWeight_1a;
  // // weight[15] = _lumiWeight * _PUweight_Do * _muEffWeight * _eleEffWeight * 1.0 * 1.0 * 1.0 * 1.0 * _btagWeight_1a;
  // // weight[16] = _lumiWeight * _PUweight_Up * _muEffWeight * _eleEffWeight * 1.0 * 1.0 * 1.0 * 1.0 * _btagWeight_1a;
  // // weight[17] = _lumiWeight * _PUweight * _muEffWeight * _eleEffWeight * _q2weight_Do * 1.0 * 1.0 * 1.0 * _btagWeight_1a;
  // // weight[18] = _lumiWeight * _PUweight * _muEffWeight * _eleEffWeight * _q2weight_Up * 1.0 * 1.0 * 1.0 * _btagWeight_1a;

  // for(int isyst=0;isyst<fNSyst;isyst++)
  //   hCheck[fNTestHist+isyst]->Fill(weight[isyst]);
  
  // bool isMu = (_passPresel_Mu && _nJet >= 4 && _nBJet >= 2) ? true : false;
  // bool isEle = (_passPresel_Ele && _nJet >= 4 && _nBJet >= 2) ? true : false;
  
  // for(int ifile=0;ifile<2;ifile++){
  //   bool isSel = (ifile==0) ? isMu : isEle ; 
  //   //for(int isyst=0 ; isyst<fNSyst && isSel && _M_jj > 20.0 && _chi2 > 0 ; isyst++){
  //   for(int isyst=0 ; isyst<fNSyst && isSel ; isyst++){
      
  //     if(isData && isyst>0) continue;
      
  //     //if(_lumiWeight < 0.0) continue;
      
  //     //Explicitly for KinFit
  //     //if(_chi2 < 0) continue;
      
  //     //if(TMath::AreEqualAbs(weight[isyst],0.0,1.0e-7)) continue;
      
  //     //fFileDir[ifile*fNSyst + isyst]->cd();

  //     for (int ipt = 0 ; ipt < int(_muPt->size()) ; ipt++ ){
  // 	hpresel_muPt[ifile*fNSyst + isyst]->Fill(_muPt->at(ipt),weight[isyst]);
  // 	//if(ifile==0 && isyst==0 && ipt==0){
  // 	//}
  //     }

  //     for (int ieta = 0 ; ieta < int(_muEta->size()) ; ieta++ )
  // 	hpresel_muEta[ifile*fNSyst + isyst]->Fill(_muEta->at(ieta),weight[isyst]);

  //     for (int iphi = 0 ; iphi < int(_muPhi->size()) ; iphi++ )
  // 	hpresel_muPhi[ifile*fNSyst + isyst]->Fill(_muPhi->at(iphi),weight[isyst]);

  //     for (int ipt = 0 ; ipt < int(_elePt->size()) ; ipt++ )
  // 	hpresel_elePt[ifile*fNSyst + isyst]->Fill(_elePt->at(ipt),weight[isyst]);

  //     for (int ieta = 0 ; ieta < int(_eleSCEta->size()) ; ieta++ )
  // 	hpresel_eleSCEta[ifile*fNSyst + isyst]->Fill(_eleSCEta->at(ieta),weight[isyst]);

  //     for (int iphi = 0 ; iphi < int(_elePhi->size()) ; iphi++ )
  // 	hpresel_elePhi[ifile*fNSyst + isyst]->Fill(_elePhi->at(iphi),weight[isyst]);
  

  //     hpresel_HT[ifile*fNSyst + isyst]->Fill(_HT,weight[isyst]);
  //     hpresel_M3[ifile*fNSyst + isyst]->Fill(_M3,weight[isyst]);
  //     hpresel_MET[ifile*fNSyst + isyst]->Fill(_pfMET,weight[isyst]);
  //     //hpresel_M_jjkF[ifile*fNSyst + isyst]->Fill(_M_jjkF,weight[isyst]);
  //     //No weight
  //     hpresel_M_jjkF[ifile*fNSyst + isyst]->Fill(_M_jjkF);
  //     //hpresel_M_jj[ifile*fNSyst + isyst]->Fill(_M_jj,weight[isyst]);
  //     //No weight
  //     hpresel_M_jj[ifile*fNSyst + isyst]->Fill(_M_jj);
  //     hpresel_Nbjet[ifile*fNSyst + isyst]->Fill(_nBJet,weight[isyst]);
  //     hpresel_Njet[ifile*fNSyst + isyst]->Fill(_nJet,weight[isyst]);
  //     hpresel_WtransMass[ifile*fNSyst + isyst]->Fill(_WtransMass,weight[isyst]);
  //     hpresel_nVtx[ifile*fNSyst + isyst]->Fill(_nVtx,weight[isyst]);
      
  //   }//isyst
  // }//ifile

  // delete []weight;

  fStatus++;
   
   return kTRUE;
}


//_____________________________________________________________________________
void CutflowRecoTuple::SlaveTerminate()
{
  
  Info("SlaveTerminate",
       "sample : %s, year : %d, mode : %s", fSample.Data(), fYear, fMode.Data());

  
  // File closure
  
  for(int ifile=0;ifile<2;ifile++){

    TDirectory *savedir = gDirectory;
    savedir->cd();

    fFile[ifile]->cd();
    
    for(int isyst=0;isyst<fNSyst;isyst++){

      if(isData && isyst>0) continue;

      fFileDir[ifile*fNSyst + isyst]->cd();
      
      hpresel_HT[ifile*fNSyst + isyst]->Write(); 
      hpresel_M3[ifile*fNSyst + isyst]->Write(); 
      hpresel_MET[ifile*fNSyst + isyst]->Write(); 
      hpresel_M_jjkF[ifile*fNSyst + isyst]->Write(); 
      hpresel_M_jj[ifile*fNSyst + isyst]->Write(); 
      hpresel_Nbjet[ifile*fNSyst + isyst]->Write(); 
      hpresel_Njet[ifile*fNSyst + isyst]->Write(); 
      hpresel_WtransMass[ifile*fNSyst + isyst]->Write(); 
      hpresel_elePhi[ifile*fNSyst + isyst]->Write(); 
      hpresel_elePt[ifile*fNSyst + isyst]->Write(); 
      hpresel_eleSCEta[ifile*fNSyst + isyst]->Write(); 
      hpresel_muEta[ifile*fNSyst + isyst]->Write(); 
      hpresel_muPhi[ifile*fNSyst + isyst]->Write(); 
      hpresel_muPt[ifile*fNSyst + isyst]->Write(); 
      hpresel_nVtx[ifile*fNSyst + isyst]->Write(); 

      hpresel_HT[ifile*fNSyst + isyst]->SetDirectory(0);
      hpresel_M3[ifile*fNSyst + isyst]->SetDirectory(0);
      hpresel_MET[ifile*fNSyst + isyst]->SetDirectory(0);
      hpresel_M_jjkF[ifile*fNSyst + isyst]->SetDirectory(0);
      hpresel_M_jj[ifile*fNSyst + isyst]->SetDirectory(0);
      hpresel_Nbjet[ifile*fNSyst + isyst]->SetDirectory(0);
      hpresel_Njet[ifile*fNSyst + isyst]->SetDirectory(0);
      hpresel_WtransMass[ifile*fNSyst + isyst]->SetDirectory(0);
      hpresel_elePhi[ifile*fNSyst + isyst]->SetDirectory(0);
      hpresel_elePt[ifile*fNSyst + isyst]->SetDirectory(0);
      hpresel_eleSCEta[ifile*fNSyst + isyst]->SetDirectory(0);
      hpresel_muEta[ifile*fNSyst + isyst]->SetDirectory(0);
      hpresel_muPhi[ifile*fNSyst + isyst]->SetDirectory(0);
      hpresel_muPt[ifile*fNSyst + isyst]->SetDirectory(0);
      hpresel_nVtx[ifile*fNSyst + isyst]->SetDirectory(0);

      // hMuPt1->Write();
      // hMuPt1->SetDirectory(0);
      
      fFile[ifile]->cd();
    }
    
    savedir->cd();

    // hMuPt->Write();
    // hMuPt->SetDirectory(0);

    // hElePt->Write();
    // hMuPt->SetDirectory(0);


    fFile[ifile]->Close();
    

    if (fMode.BeginsWith("proof")) {
      Info("SlaveTerminate", "objects saved into '%s%s': sending related TProofOutputFile ...",
	   fProofFile[ifile]->GetFileName(), fProofFile[ifile]->GetOptionsAnchor());
      fProofFile[ifile]->Print();
      fOutput->Add(fProofFile[ifile]);    
    }
  
  }//file loop

  TDirectory *savedir = gDirectory;
  savedir->cd();
  fFile[2]->cd();
  for(int icheck=0;icheck<(fNTestHist+fNSyst);icheck++)
    hCheck[icheck]->Write();
  savedir->cd();
  fFile[2]->Close();
  if (fMode.BeginsWith("proof")) {
    Info("SlaveTerminate", "objects saved into '%s%s': sending related TProofOutputFile ...",
	 fProofFile[2]->GetFileName(), fProofFile[2]->GetOptionsAnchor());
    fProofFile[2]->Print();
    fOutput->Add(fProofFile[2]);
  }

  tg_trackSF_BCDEF->Delete();
  tg_trackSF_GH->Delete();
  f_trackSF_BCDEF->Close();
  f_trackSF_GH->Close()	;
  delete f_trackSF_BCDEF;
  delete f_trackSF_GH;
  delete muSFa;
  delete muSFb;
  

   //trigger SF
   h2_trigSF_BCDEF->Delete();
   h2_trigSF_GH->Delete();
   f_trigSF_BCDEF->Close();
   f_trigSF_GH->Close();
   //Identification SF
   h2_idSF_BCDEF->Delete();
   h2_idSF_GH->Delete();
   f_idSF_BCDEF->Close();
   f_idSF_GH->Close();
   //Isolation SF
   h2_isoSF_BCDEF->Delete();
   h2_isoSF_GH->Delete();
   f_isoSF_BCDEF->Close();
   f_isoSF_GH->Close();

   delete f_trigSF_BCDEF ;
   delete f_trigSF_GH ;
   delete f_idSF_BCDEF ;
   delete f_idSF_GH ;
   delete f_isoSF_BCDEF ;
   delete f_isoSF_GH ;

}

//_____________________________________________________________________________
void CutflowRecoTuple::Terminate()
{
// function called at the end of the event loop

   // hMuPt = dynamic_cast<TH1D*>(fOutput->FindObject("hMuPt"));
   // hElePt = dynamic_cast<TH1D*>(fOutput->FindObject("hElePt"));

   // if (hMuPt == 0 || hElePt == 0) {
   //    Error("Terminate", "hMuPt = %p , hElePt = %p", hMuPt, hElePt);
   //    return;
   // }
   
   // //create the canvas for the CutflowRecoTuple fit
   // TCanvas *c1 = new TCanvas("c1","c1",10,10,800,600);
   // hMuPt->Draw();
   
   // TCanvas *c2 = new TCanvas("c2","c2",100,100,800,600);
   // hElePt->Draw();
   
   // Notify the amount of processed events
   if (!fInput) Info("Terminate", "processed %lld events", fProcessed);
   
   TString option = GetOption();
   Info("Terminate", "stopping CutflowRecoTuple with process option: %s", option.Data());
   
}
