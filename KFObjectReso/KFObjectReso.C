/**********************************************************************
 Created on : 14/07/2021
 Purpose    : Analyse the Skim tree.
              (format adapted from h1analysis)
 Author     : Indranil Das, Visiting Fellow
 Email      : indranil.das@cern.ch | indra.ehep@gmail.com
**********************************************************************/

#include "KFObjectReso.h"
#include "TH2.h"
#include "TF1.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TPaveStats.h"
#include "TMath.h"
#include "TProof.h"
#include "TObjString.h"
#include "TParticlePDG.h"
#include "TDatabasePDG.h"

//_____________________________________________________________________________
void KFObjectReso::GetArguments(){

  TString option = GetOption();
  //Info("GetArguments","ending KFObjectReso with process option: %s", option.Data());

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

  if(fYear==2016){  
    
    mu_Pt_cut = 26.;
    ele_Pt_cut = 30.;
    jet_Pt_cut = 25.;
    
    //DeepCSV
    btag_cut_DeepCSVa = 0.6001; 
    btag_cut_DeepCSVb = 0.5847; 
    //DeepJet
    btag_cuta = 0.2598 ; 
    btag_cutb = 0.2489 ; 

  }else if(fYear==2017){

    mu_Pt_cut = 30.;
    ele_Pt_cut = 35.;
    jet_Pt_cut = 25.;

    btag_cut_DeepCSV = 0.4506;
    btag_cut = 0.3040 ;

  }else if(fYear==2018){

    mu_Pt_cut = 26.;
    ele_Pt_cut = 35.;
    jet_Pt_cut = 25.;

    btag_cut_DeepCSV = 0.4168;
    btag_cut = 0.2783 ;

  }

}

//_____________________________________________________________________________
void KFObjectReso::Begin(TTree * /*tree*/)
{
   // This is needed when re-processing the object
   Reset();

   //print the option specified in the Process function.
   TString option = GetOption();
   Info("Begin", "starting KFObjectReso with process option: %s", option.Data());
   // Test tokenize

   if (fChain) fChain->SetEntryList(0);
}

Int_t KFObjectReso::CreateHistoArrays()
{
  // Create the histogram arrays

  nMuEtaBins = 50;
  Float_t muEtaBin[51] = {-2.500, 
			  -2.400, -2.300, -2.200, -2.100, -2.000, 
			  -1.900, -1.800, -1.700, -1.600, -1.500, 
			  -1.400, -1.300, -1.200, -1.100, -1.000, 
			  -0.900, -0.800, -0.700, -0.600, -0.500, 
			  -0.400, -0.300, -0.200, -0.100, 
			  0.0, 
			  0.100, 0.200, 0.300, 0.400, 
  			  0.500, 0.600, 0.700, 0.800, 0.900, 
  			  1.000, 1.100, 1.200, 1.300, 1.400, 
  			  1.500, 1.600, 1.700, 1.800, 1.900, 
  			  2.000, 2.100, 2.200, 2.300, 2.4,
                          2.5};
  // nMuEtaBins = 25;
  // Float_t muEtaBin[26] = {-2.5, -2.2, -1.9, -1.6, -1.3,
  // 			  -1.0, -0.9, -0.8, -0.6, -0.4,
  // 			  -0.3, -0.2, -0.1,  0.0,  0.1, 
  // 			   0.2,  0.3,  0.4,  0.6,  0.8, 
  //                          1.0,  1.3,  1.6,  1.9,  2.2, 2.5};
  
  nEleEtaBins = 48;
  Float_t eleEtaBin[49] = { -2.500, -2.322, -2.172, -2.043, -1.930, 
			    -1.830, -1.740, -1.653, -1.479, -1.392, 
			    -1.305, -1.218, -1.131, -1.044, -0.957, 
			    -0.870, -0.783, -0.696, -0.609, -0.522, 
			    -0.435, -0.348, -0.261, -0.174, 
			    0.0, 0.174, 0.261, 0.348, 0.435, 
			    0.522, 0.609, 0.696, 0.783, 0.870, 
			    0.957, 1.044, 1.131, 1.218, 1.305, 
			    1.392, 1.479, 1.653, 1.740, 1.830, 
			    1.930, 2.043, 2.172, 2.322, 2.5};
  
  // nEleEtaBins = 25;
  // Float_t eleEtaBin[26] = {-2.5, -2.2, -1.9, -1.6, -1.3,
  // 			  -1.0, -0.9, -0.8, -0.6, -0.4,
  // 			  -0.3, -0.2, -0.1,  0.0,  0.1, 
  // 			   0.2,  0.3,  0.4,  0.6,  0.8, 
  //                          1.0,  1.3,  1.6,  1.9,  2.2, 2.5};

  nJetEtaBins = 52;
  Float_t jetEtaBin[53] = {-2.500, -2.322, 
			   -2.172, -2.043, -1.930, -1.830, -1.740, 
			   -1.653, -1.566, -1.479, -1.392, -1.305, 
			   -1.218, -1.131, -1.044, -0.957, -0.870, 
			   -0.783, -0.696, -0.609, -0.522, -0.435, 
			   -0.348, -0.261, -0.174, -0.087, 
			   0.0, 0.087, 0.174, 0.261, 0.348, 
  			   0.435, 0.522, 0.609, 0.696, 0.783, 
  			   0.870, 0.957, 1.044, 1.131, 1.218, 
  			   1.305, 1.392, 1.479, 1.566, 1.653, 
  			   1.740, 1.830, 1.930, 2.043, 2.172, 
  			   2.322, 2.5};
  
  // nJetEtaBins = 25;
  // Float_t jetEtaBin[26] = {-2.5, -2.2, -1.9, -1.6, -1.3,
  // 			  -1.0, -0.9, -0.8, -0.6, -0.4,
  // 			  -0.3, -0.2, -0.1,  0.0,  0.1, 
  // 			   0.2,  0.3,  0.4,  0.6,  0.8, 
  //                          1.0,  1.3,  1.6,  1.9,  2.2, 2.5};
  
  // nJetEtaBins = 1;
  // Float_t jetEtaBin[2] = {0.435, 0.783};
  
  nETBins = 37;
  Float_t ETBin[38] = {25., 30., 35., 40., 45., 50., 55., 60., 65., 70., 75., 80., 85., 90., 95., 100.,  
                       110., 120., 130., 140., 150., 160., 170., 180., 190., 200.,
	               220., 240., 260., 280., 300.,
	               330., 360., 390., 420.,
                       440., 480., 520.}; 

  // nETBins = 29;
  // Float_t ETBin[30] = {20., 30., 40., 50., 60.,
  //                      70., 80., 90., 100., 110.,
  //                      120., 130., 140., 150., 160., 
  //                      170., 180., 190., 200., 210.,
  // 		       220., 230., 240., 250., 260.,
  // 		       270., 280., 290., 300., 310};
  
  for(int ifile=0;ifile<1;ifile++){

    TDirectory *savedir = gDirectory;
    savedir->cd();

    fFile[ifile]->cd();

    hNofMu = new TH1F("hNofMu","hNofMu",100,-5,5);
    hNofEle = new TH1F("hNofEle","hNofEle",100,-5,5);
    hNofBJets = new TH1F("hNofBJets","hNofBJets",55,-5,50); 
    hNofLJets = new TH1F("hNofLJets","hNofLJets",55,-5,50);
    
    hDelRMu = new TH1F("hDelRMu","hDelRMu",100,0.,1.);
    hDelREle = new TH1F("hDelREle","hDelREle",100,0.,1.);
    hDelRMET = new TH1F("hDelRMET","hDelRMET",100,0.,1.); 
    hDelRBJets = new TH1F("hDelRBJets","hDelRBJets",100,0.,1.); 
    hDelRLJets = new TH1F("hDelRLJets","hDelRLJets",100,0.,1.);
    
    hBJetETReso = new TH1F**[nJetEtaBins];
    hLJetETReso = new TH1F**[nJetEtaBins];
    hBJetEtaReso = new TH1F**[nJetEtaBins];
    hLJetEtaReso = new TH1F**[nJetEtaBins];
    hBJetPhiReso = new TH1F**[nJetEtaBins];
    hLJetPhiReso = new TH1F**[nJetEtaBins];
    hBJetPtReso = new TH1F**[nJetEtaBins];
    hLJetPtReso = new TH1F**[nJetEtaBins];
    hBJetEnReso = new TH1F**[nJetEtaBins];
    hLJetEnReso = new TH1F**[nJetEtaBins];
    // hBJetETRRel = new TH1F**[nJetEtaBins];
    // hLJetETRRel = new TH1F**[nJetEtaBins];
    // hBJetEtaRRel = new TH1F**[nJetEtaBins];
    // hLJetEtaRRel = new TH1F**[nJetEtaBins];
    // hBJetPhiRRel = new TH1F**[nJetEtaBins];
    // hLJetPhiRRel = new TH1F**[nJetEtaBins];
    for(int ieta=0;ieta<nJetEtaBins;ieta++){
      hBJetETReso[ieta] = new TH1F*[nETBins];
      hLJetETReso[ieta] = new TH1F*[nETBins];
      hBJetEtaReso[ieta] = new TH1F*[nETBins];
      hLJetEtaReso[ieta] = new TH1F*[nETBins];
      hBJetPhiReso[ieta] = new TH1F*[nETBins];
      hLJetPhiReso[ieta] = new TH1F*[nETBins];
      hBJetPtReso[ieta] = new TH1F*[nETBins];
      hLJetPtReso[ieta] = new TH1F*[nETBins];
      hBJetEnReso[ieta] = new TH1F*[nETBins];
      hLJetEnReso[ieta] = new TH1F*[nETBins];
      // hBJetETRRel[ieta] = new TH1F*[nETBins];
      // hLJetETRRel[ieta] = new TH1F*[nETBins];
      // hBJetEtaRRel[ieta] = new TH1F*[nETBins];
      // hLJetEtaRRel[ieta] = new TH1F*[nETBins];
      // hBJetPhiRRel[ieta] = new TH1F*[nETBins];
      // hLJetPhiRRel[ieta] = new TH1F*[nETBins];
      for(int iet=0;iet<nETBins;iet++){
	hBJetETReso[ieta][iet] = new TH1F(Form("hBJetETReso_%d_%d",ieta,iet),
					  Form("hBJetETReso #eta:(%4.3f-%4.3f) E_{T}:(%2.0f-%2.0f) GeV",jetEtaBin[ieta],jetEtaBin[ieta+1],ETBin[iet],ETBin[iet+1]),
					  200,-200.,200.);
	hLJetETReso[ieta][iet] = new TH1F(Form("hLJetETReso_%d_%d",ieta,iet),
					  Form("hLJetETReso #eta:(%4.3f-%4.3f) E_{T}:(%2.0f-%2.0f) GeV",jetEtaBin[ieta],jetEtaBin[ieta+1],ETBin[iet],ETBin[iet+1]),
					  200,-200.,200.);
	hBJetEtaReso[ieta][iet] = new TH1F(Form("hBJetEtaReso_%d_%d",ieta,iet),
					   Form("hBJetEtaReso #eta:(%4.3f-%4.3f) E_{T}:(%2.0f-%2.0f) GeV",jetEtaBin[ieta],jetEtaBin[ieta+1],ETBin[iet],ETBin[iet+1]),
					   200, -0.2, 0.2);
	hLJetEtaReso[ieta][iet] = new TH1F(Form("hLJetEtaReso_%d_%d",ieta,iet),
					   Form("hLJetEtaReso #eta:(%4.3f-%4.3f) E_{T}:(%2.0f-%2.0f) GeV",jetEtaBin[ieta],jetEtaBin[ieta+1],ETBin[iet],ETBin[iet+1]),
					   200, -0.2, 0.2);
	hBJetPhiReso[ieta][iet] = new TH1F(Form("hBJetPhiReso_%d_%d",ieta,iet),
					   Form("hBJetPhiReso #eta:(%4.3f-%4.3f) E_{T}:(%2.0f-%2.0f) GeV",jetEtaBin[ieta],jetEtaBin[ieta+1],ETBin[iet],ETBin[iet+1]),
					   200, -0.2, 0.2);
	hLJetPhiReso[ieta][iet] = new TH1F(Form("hLJetPhiReso_%d_%d",ieta,iet),
					   Form("hLJetPhiReso #eta:(%4.3f-%4.3f) E_{T}:(%2.0f-%2.0f) GeV",jetEtaBin[ieta],jetEtaBin[ieta+1],ETBin[iet],ETBin[iet+1]),
					   200, -0.2, 0.2);
	hBJetPtReso[ieta][iet] = new TH1F(Form("hBJetPtReso_%d_%d",ieta,iet),
					  Form("hBJetPtReso #eta:(%4.3f-%4.3f) E_{T}:(%2.0f-%2.0f) GeV",jetEtaBin[ieta],jetEtaBin[ieta+1],ETBin[iet],ETBin[iet+1]),
					  200,-200.,200.);
	hLJetPtReso[ieta][iet] = new TH1F(Form("hLJetPtReso_%d_%d",ieta,iet),
					  Form("hLJetPtReso #eta:(%4.3f-%4.3f) E_{T}:(%2.0f-%2.0f) GeV",jetEtaBin[ieta],jetEtaBin[ieta+1],ETBin[iet],ETBin[iet+1]),
					  200,-200.,200.);
	hBJetEnReso[ieta][iet] = new TH1F(Form("hBJetEnReso_%d_%d",ieta,iet),
					  Form("hBJetEnReso #eta:(%4.3f-%4.3f) E_{T}:(%2.0f-%2.0f) GeV",jetEtaBin[ieta],jetEtaBin[ieta+1],ETBin[iet],ETBin[iet+1]),
					  200,-200.,200.);
	hLJetEnReso[ieta][iet] = new TH1F(Form("hLJetEnReso_%d_%d",ieta,iet),
					  Form("hLJetEnReso #eta:(%4.3f-%4.3f) E_{T}:(%2.0f-%2.0f) GeV",jetEtaBin[ieta],jetEtaBin[ieta+1],ETBin[iet],ETBin[iet+1]),
					  200,-200.,200.);

	// hBJetETRRel[ieta][iet] = new TH1F(Form("hBJetETRRel_%d_%d",ieta,iet),
	// 				  Form("hBJetETRRel #eta:(%4.3f-%4.3f) E_{T}:(%2.0f-%2.0f) GeV",jetEtaBin[ieta],jetEtaBin[ieta+1],ETBin[iet],ETBin[iet+1]),
	// 				  200,-200.,200.);
	// hLJetETRRel[ieta][iet] = new TH1F(Form("hLJetETRRel_%d_%d",ieta,iet),
	// 				  Form("hLJetETRRel #eta:(%4.3f-%4.3f) E_{T}:(%2.0f-%2.0f) GeV",jetEtaBin[ieta],jetEtaBin[ieta+1],ETBin[iet],ETBin[iet+1]),
	// 				  200,-200.,200.);
	// hBJetEtaRRel[ieta][iet] = new TH1F(Form("hBJetEtaRRel_%d_%d",ieta,iet),
	// 				   Form("hBJetEtaRRel #eta:(%4.3f-%4.3f) E_{T}:(%2.0f-%2.0f) GeV",jetEtaBin[ieta],jetEtaBin[ieta+1],ETBin[iet],ETBin[iet+1]),
	// 				   200, -0.2, 0.2);
	// hLJetEtaRRel[ieta][iet] = new TH1F(Form("hLJetEtaRRel_%d_%d",ieta,iet),
	// 				   Form("hLJetEtaRRel #eta:(%4.3f-%4.3f) E_{T}:(%2.0f-%2.0f) GeV",jetEtaBin[ieta],jetEtaBin[ieta+1],ETBin[iet],ETBin[iet+1]),
	// 				   200, -0.2, 0.2);
	// hBJetPhiRRel[ieta][iet] = new TH1F(Form("hBJetPhiRRel_%d_%d",ieta,iet),
	// 				   Form("hBJetPhiRRel #eta:(%4.3f-%4.3f) E_{T}:(%2.0f-%2.0f) GeV",jetEtaBin[ieta],jetEtaBin[ieta+1],ETBin[iet],ETBin[iet+1]),
	// 				   200, -0.2, 0.2);
	// hLJetPhiRRel[ieta][iet] = new TH1F(Form("hLJetPhiRRel_%d_%d",ieta,iet),
	// 				   Form("hLJetPhiRRel #eta:(%4.3f-%4.3f) E_{T}:(%2.0f-%2.0f) GeV",jetEtaBin[ieta],jetEtaBin[ieta+1],ETBin[iet],ETBin[iet+1]),
	// 				   200, -0.2, 0.2);
	// hBJetETDelRReso[iet] = new TH1F(Form("hBJetETDelRReso_0_%d",iet),Form("hBJetETDelRReso_0_%d",iet), 200, 0.,1.);
      }// jet et
    }//jet eta
    hJetEtaETBin = new TH2F("hJetEtaETBin","hJetEtaETBin", nJetEtaBins, jetEtaBin, nETBins, ETBin);

    hMuETReso = new TH1F**[nMuEtaBins];
    hMuEtaReso = new TH1F**[nMuEtaBins];
    hMuPhiReso = new TH1F**[nMuEtaBins];
    hMuPtReso = new TH1F**[nMuEtaBins];
    hMuEnReso = new TH1F**[nMuEtaBins];
    // hMuETRRel = new TH1F**[nMuEtaBins];
    // hMuEtaRRel = new TH1F**[nMuEtaBins];
    // hMuPhiRRel = new TH1F**[nMuEtaBins];
    for(int ieta=0;ieta<nMuEtaBins;ieta++){
      hMuETReso[ieta] = new TH1F*[nETBins];
      hMuEtaReso[ieta] = new TH1F*[nETBins];
      hMuPhiReso[ieta] = new TH1F*[nETBins];
      hMuPtReso[ieta] = new TH1F*[nETBins];
      hMuEnReso[ieta] = new TH1F*[nETBins];
      // hMuETRRel[ieta] = new TH1F*[nETBins];
      // hMuEtaRRel[ieta] = new TH1F*[nETBins];
      // hMuPhiRRel[ieta] = new TH1F*[nETBins];
      for(int iet=0;iet<nETBins;iet++){
	hMuETReso[ieta][iet] = new TH1F(Form("hMuETReso_%d_%d",ieta,iet),
					Form("hMuETReso #eta:(%4.3f-%4.3f) E_{T}:(%2.0f-%2.0f) GeV",muEtaBin[ieta],muEtaBin[ieta+1],ETBin[iet],ETBin[iet+1]),
					200,-50.,50.);
	hMuEtaReso[ieta][iet] = new TH1F(Form("hMuEtaReso_%d_%d",ieta,iet),
					 Form("hMuEtaReso #eta:(%4.3f-%4.3f) E_{T}:(%2.0f-%2.0f) GeV",muEtaBin[ieta],muEtaBin[ieta+1],ETBin[iet],ETBin[iet+1]),
					 200, -0.05, 0.05);
	hMuPhiReso[ieta][iet] = new TH1F(Form("hMuPhiReso_%d_%d",ieta,iet),
					 Form("hMuPhiReso #eta:(%4.3f-%4.3f) E_{T}:(%2.0f-%2.0f) GeV",muEtaBin[ieta],muEtaBin[ieta+1],ETBin[iet],ETBin[iet+1]),
					 200, -0.05, 0.05);
	hMuPtReso[ieta][iet] = new TH1F(Form("hMuPtReso_%d_%d",ieta,iet),
					Form("hMuPtReso #eta:(%4.3f-%4.3f) E_{T}:(%2.0f-%2.0f) GeV",muEtaBin[ieta],muEtaBin[ieta+1],ETBin[iet],ETBin[iet+1]),
					200,-50.,50.);
	hMuEnReso[ieta][iet] = new TH1F(Form("hMuEnReso_%d_%d",ieta,iet),
					Form("hMuEnReso #eta:(%4.3f-%4.3f) E_{T}:(%2.0f-%2.0f) GeV",muEtaBin[ieta],muEtaBin[ieta+1],ETBin[iet],ETBin[iet+1]),
					200,-50.,50.);
	// hMuETRRel[ieta][iet] = new TH1F(Form("hMuETRRel_%d_%d",ieta,iet),
	// 				Form("hMuETRRel #eta:(%4.3f-%4.3f) E_{T}:(%2.0f-%2.0f) GeV",muEtaBin[ieta],muEtaBin[ieta+1],ETBin[iet],ETBin[iet+1]),
	// 				200,-50.,50.);
	// hMuEtaRRel[ieta][iet] = new TH1F(Form("hMuEtaRRel_%d_%d",ieta,iet),
	// 				 Form("hMuEtaRRel #eta:(%4.3f-%4.3f) E_{T}:(%2.0f-%2.0f) GeV",muEtaBin[ieta],muEtaBin[ieta+1],ETBin[iet],ETBin[iet+1]),
	// 				 200, -0.05, 0.05);
	// hMuPhiRRel[ieta][iet] = new TH1F(Form("hMuPhiRRel_%d_%d",ieta,iet),
	// 				 Form("hMuPhiRRel #eta:(%4.3f-%4.3f) E_{T}:(%2.0f-%2.0f) GeV",muEtaBin[ieta],muEtaBin[ieta+1],ETBin[iet],ETBin[iet+1]),
	// 				 200, -0.05, 0.05);
      }//mu et
    }//mu eta
    hMuEtaETBin = new TH2F("hMuEtaETBin","hMuEtaETBin", nMuEtaBins, muEtaBin, nETBins, ETBin);

    hEleETReso = new TH1F**[nEleEtaBins];
    hEleEtaReso = new TH1F**[nEleEtaBins];
    hElePhiReso = new TH1F**[nEleEtaBins];
    hElePtReso = new TH1F**[nEleEtaBins];
    hEleEnReso = new TH1F**[nEleEtaBins];
    // hEleETRRel = new TH1F**[nEleEtaBins];
    // hEleEtaRRel = new TH1F**[nEleEtaBins];
    // hElePhiRRel = new TH1F**[nEleEtaBins];
    for(int ieta=0;ieta<nEleEtaBins;ieta++){
      hEleETReso[ieta] = new TH1F*[nETBins];
      hEleEtaReso[ieta] = new TH1F*[nETBins];
      hElePhiReso[ieta] = new TH1F*[nETBins];
      hElePtReso[ieta] = new TH1F*[nETBins];
      hEleEnReso[ieta] = new TH1F*[nETBins];
      // hEleETRRel[ieta] = new TH1F*[nETBins];
      // hEleEtaRRel[ieta] = new TH1F*[nETBins];
      // hElePhiRRel[ieta] = new TH1F*[nETBins];
      for(int iet=0;iet<nETBins;iet++){
	hEleETReso[ieta][iet] = new TH1F(Form("hEleETReso_%d_%d",ieta,iet),
					 Form("hEleETReso #eta:(%4.3f-%4.3f) E_{T}:(%2.0f-%2.0f) GeV",eleEtaBin[ieta],eleEtaBin[ieta+1],ETBin[iet],ETBin[iet+1]),
					 200,-50.,50.);
	hEleEtaReso[ieta][iet] = new TH1F(Form("hEleEtaReso_%d_%d",ieta,iet),
					  Form("hEleEtaReso #eta:(%4.3f-%4.3f) E_{T}:(%2.0f-%2.0f) GeV",eleEtaBin[ieta],eleEtaBin[ieta+1],ETBin[iet],ETBin[iet+1]),
					  200, -0.05, 0.05);
	hElePhiReso[ieta][iet] = new TH1F(Form("hElePhiReso_%d_%d",ieta,iet),
					  Form("hElePhiReso #eta:(%4.3f-%4.3f) E_{T}:(%2.0f-%2.0f) GeV",eleEtaBin[ieta],eleEtaBin[ieta+1],ETBin[iet],ETBin[iet+1]),
					  200, -0.05, 0.05);
	hElePtReso[ieta][iet] = new TH1F(Form("hElePtReso_%d_%d",ieta,iet),
					 Form("hElePtReso #eta:(%4.3f-%4.3f) E_{T}:(%2.0f-%2.0f) GeV",eleEtaBin[ieta],eleEtaBin[ieta+1],ETBin[iet],ETBin[iet+1]),
					 200,-50.,50.);
	hEleEnReso[ieta][iet] = new TH1F(Form("hEleEnReso_%d_%d",ieta,iet),
					 Form("hEleEnReso #eta:(%4.3f-%4.3f) E_{T}:(%2.0f-%2.0f) GeV",eleEtaBin[ieta],eleEtaBin[ieta+1],ETBin[iet],ETBin[iet+1]),
					 200,-50.,50.);
	// hEleETRRel[ieta][iet] = new TH1F(Form("hEleETRRel_%d_%d",ieta,iet),
	// 				 Form("hEleETRRel #eta:(%4.3f-%4.3f) E_{T}:(%2.0f-%2.0f) GeV",eleEtaBin[ieta],eleEtaBin[ieta+1],ETBin[iet],ETBin[iet+1]),
	// 				 200,-50.,50.);
	// hEleEtaRRel[ieta][iet] = new TH1F(Form("hEleEtaRRel_%d_%d",ieta,iet),
	// 				  Form("hEleEtaRRel #eta:(%4.3f-%4.3f) E_{T}:(%2.0f-%2.0f) GeV",eleEtaBin[ieta],eleEtaBin[ieta+1],ETBin[iet],ETBin[iet+1]),
	// 				  200, -0.05, 0.05);
	// hElePhiRRel[ieta][iet] = new TH1F(Form("hElePhiRRel_%d_%d",ieta,iet),
	// 				  Form("hElePhiRRel #eta:(%4.3f-%4.3f) E_{T}:(%2.0f-%2.0f) GeV",eleEtaBin[ieta],eleEtaBin[ieta+1],ETBin[iet],ETBin[iet+1]),
	// 				  200, -0.05, 0.05);
      }//ele et
    }//ele eta
    hEleEtaETBin = new TH2F("hEleEtaETBin","hEleEtaETBin", nEleEtaBins, eleEtaBin, nETBins, ETBin);

    hMETETReso = new TH1F*[nETBins];
    hMETPhiReso = new TH1F*[nETBins];
    hMETPtReso = new TH1F*[nETBins];
    hMETETRRel = new TH1F*[nETBins];
    hMETPhiRRel = new TH1F*[nETBins];
    for(int iet=0;iet<nETBins;iet++){
      hMETETReso[iet] = new TH1F(Form("hMETETReso_%d",iet),Form("hMETETReso_%d E_{T}:(%2.0f-%2.0f) GeV",iet,ETBin[iet],ETBin[iet+1]),400,-400.,400.);
      hMETPhiReso[iet] = new TH1F(Form("hMETPhiReso_%d",iet),Form("hMETPhiReso_%d E_{T}:(%2.0f-%2.0f) GeV",iet,ETBin[iet],ETBin[iet+1]),200, -2.0, 2.0);
      hMETPtReso[iet] = new TH1F(Form("hMETPtReso_%d",iet),Form("hMETPtReso_%d E_{T}:(%2.0f-%2.0f) GeV",iet,ETBin[iet],ETBin[iet+1]),400,-400.,400.);
      hMETETRRel[iet] = new TH1F(Form("hMETETRRel_%d",iet),Form("hMETETRRel_%d E_{T}:(%2.0f-%2.0f) GeV",iet,ETBin[iet],ETBin[iet+1]),400,-400.,400.);
      hMETPhiRRel[iet] = new TH1F(Form("hMETPhiRRel_%d",iet),Form("hMETPhiRRel_%d E_{T}:(%2.0f-%2.0f) GeV",iet,ETBin[iet],ETBin[iet+1]),200, -2.0, 2.0);
    }
    hMETETBin = new TH1F("hMETETBin","hMETETBin", nETBins, ETBin);


  }//file loop

  
  return true;
}

//_____________________________________________________________________________
void KFObjectReso::SlaveBegin(TTree *tree)
{
  
  //print the option specified in the Process function.
  TString option = GetOption();
  Info("SlaveBegin",
       "starting KFObjectReso with process option: %s (tree: %p)", option.Data(), tree);

  GetArguments();
  Info("SlaveBegin",
       "sample : %s, year : %d, mode : %s", fSample.Data(), fYear, fMode.Data());
  
  //initialize the Tree branch addresses
  Init(tree);

  char *filename[3];
  
  filename[0] = Form("%s_KFObjectsReso_%d.root",fSample.Data(),fYear) ;
  
  for(int ifile=0;ifile<1;ifile++){
    
    if(fMode.BeginsWith("proof")){
      fProofFile[ifile] = new TProofOutputFile(filename[ifile], "M");
      fFile[ifile] = fProofFile[ifile]->OpenFile("RECREATE");
      if (fFile[ifile] && fFile[ifile]->IsZombie()) SafeDelete(fFile[ifile]);
    }else{
      fFile[ifile] = TFile::Open(filename[ifile],"RECREATE");
    }
    
    // Cannot continue
    if (!fFile[ifile]) {
      TString amsg = TString::Format("KFObjectReso::SlaveBegin: could not create '%s':"
				     " instance is invalid!", fFile[ifile]->GetName());
      Abort(amsg, kAbortProcess);
      return;
    }

  }//ifile loop
  
  CreateHistoArrays();

}

//_____________________________________________________________________________
int KFObjectReso::GetHistoBin(TH1F *h, float et)
{
  double minX = h->GetXaxis()->GetBinCenter(1);
  double maxX = h->GetXaxis()->GetBinCenter(h->GetNbinsX());
  Int_t binX = -1;
  if(et <= minX)
    binX = 1;
  else if(et >= maxX)
    binX = h->GetXaxis()->FindBin(maxX);
  else
    binX = h->GetXaxis()->FindBin(et);
  
  return binX;
}

//_____________________________________________________________________________
bool KFObjectReso::GetHistoBin(TH2F *h, float eta, float et, int& binX, int& binY)
{
  double minX = h->GetXaxis()->GetBinCenter(1);
  double maxX = h->GetXaxis()->GetBinCenter(h->GetNbinsX());
  double minY = h->GetYaxis()->GetBinCenter(1);
  double maxY = h->GetYaxis()->GetBinCenter(h->GetNbinsY());

  binX = -1;
  if(eta <= minX)
    binX = 1;
  else if(eta >= maxX)
    binX = h->GetXaxis()->FindBin(maxX);
  else
    binX = h->GetXaxis()->FindBin(eta);

  binY = -1;
  if(et <= minY)
    binY = 1;
  else if(et >= maxY)
    binY = h->GetYaxis()->FindBin(maxY);
  else
    binY = h->GetYaxis()->FindBin(et);

  return true;
}

//_____________________________________________________________________________
bool KFObjectReso::CheckTrigFilterVertex()
{
  
  Pass_trigger_mu  = false;
  Pass_trigger_ele = false;
 
  if (fYear==2016) {
    Pass_trigger_mu = ( HLT_IsoMu24_ || HLT_IsoTkMu24_ ) ;
    Pass_trigger_ele = HLT_Ele27_WPTight_Gsf_ ;
  }
  if (fYear==2017){
    Pass_trigger_mu = HLT_IsoMu27_ ;
	
    bool allSingleEGL1or = ( L1_SingleEG24_ ||
			    L1_SingleEG26_ ||
			    L1_SingleEG30_ ||
			    L1_SingleEG32_ ||
			    L1_SingleEG34_ ||
			    L1_SingleEG36_ ||
			    L1_SingleEG38_ ||
			    L1_SingleEG40_ ||
			    L1_SingleEG42_ ||
			    L1_SingleEG45_ ||
			    L1_SingleEG50_ ||
			    L1_SingleEG34er2p1_ ||
			    L1_SingleEG36er2p1_ ||
			    L1_SingleEG38er2p1_ ||
			    L1_SingleIsoEG24er2p1_ ||
			    L1_SingleIsoEG26er2p1_ ||
			    L1_SingleIsoEG28er2p1_ ||
			    L1_SingleIsoEG30er2p1_ ||
			    L1_SingleIsoEG32er2p1_ ||
			    L1_SingleIsoEG34er2p1_ ||
			    L1_SingleIsoEG36er2p1_ ||
			    L1_SingleIsoEG24_ ||
			    L1_SingleIsoEG26_ ||
			    L1_SingleIsoEG28_ ||
			    L1_SingleIsoEG30_ ||
			    L1_SingleIsoEG32_ ||
			    L1_SingleIsoEG34_ ||
			    L1_SingleIsoEG36_ ||
			    L1_SingleIsoEG38_ );

    Pass_trigger_ele = ( HLT_Ele32_WPTight_Gsf_L1DoubleEG_ && allSingleEGL1or );
    
  }
  if (fYear==2018){
    Pass_trigger_mu = HLT_IsoMu24_ ;
    Pass_trigger_ele = HLT_Ele32_WPTight_Gsf_ ;
  }
  
  bool filters = ( Flag_goodVertices_ &&
		   Flag_globalSuperTightHalo2016Filter_ &&
		   Flag_HBHENoiseFilter_ &&
		   Flag_HBHENoiseIsoFilter_ &&
		   Flag_EcalDeadCellTriggerPrimitiveFilter_ &&
		   Flag_BadPFMuonFilter_ );
  
  if (fYear==2017 || fYear==2018)
    filters = filters && Flag_ecalBadCalibFilter_ ;
    
  Pass_trigger_mu = Pass_trigger_mu && filters ;
  Pass_trigger_ele = Pass_trigger_ele && filters ;
  
  bool isPVGood = (pvNDOF_>4 &&
		   sqrt(pvX_ * pvX_ + pvY_ * pvY_)<=2. &&
		   abs(pvZ_) <= 24.);
    
  Pass_trigger_mu = Pass_trigger_mu && isPVGood;
  Pass_trigger_ele = Pass_trigger_ele && isPVGood;
  
  return true;

}

//_____________________________________________________________________________
bool KFObjectReso::passEleID(int eleInd, int cutVal, bool doRelisoCut){

    Int_t WPcutBits = eleVidWPBitmap_[eleInd];

    int nBits = 3;

    bool MinPtCut                            = (WPcutBits>>(0*nBits) & 7) >= cutVal;
    bool GsfEleSCEtaMultiRangeCut            = (WPcutBits>>(1*nBits) & 7) >= cutVal;
    bool GsfEleDEtaInSeedCut                 = (WPcutBits>>(2*nBits) & 7) >= cutVal;
    bool GsfEleDPhiInCut                     = (WPcutBits>>(3*nBits) & 7) >= cutVal;
    bool GsfEleFull5x5SigmaIEtaIEtaCut       = (WPcutBits>>(4*nBits) & 7) >= cutVal;
    bool GsfEleHadronicOverEMEnergyScaledCut = (WPcutBits>>(5*nBits) & 7) >= cutVal;
    bool GsfEleEInverseMinusPInverseCut      = (WPcutBits>>(6*nBits) & 7) >= cutVal;
    bool GsfEleEffAreaPFIsoCut               = (WPcutBits>>(7*nBits) & 7) >= cutVal;
    bool GsfEleConversionVetoCut             = (WPcutBits>>(8*nBits) & 7) >= cutVal;
    bool GsfEleMissingHitsCut                = (WPcutBits>>(9*nBits) & 7) >= cutVal;

    bool passID = (
		   MinPtCut
		   && GsfEleSCEtaMultiRangeCut
		   && GsfEleDEtaInSeedCut
		   && GsfEleDPhiInCut
		   && GsfEleFull5x5SigmaIEtaIEtaCut
		   && GsfEleHadronicOverEMEnergyScaledCut
		   && GsfEleEInverseMinusPInverseCut
		   && (GsfEleEffAreaPFIsoCut || !doRelisoCut)
		   && GsfEleConversionVetoCut
		   && GsfEleMissingHitsCut
		   );

    return passID;

}

//_____________________________________________________________________________
Bool_t KFObjectReso::Process(Long64_t entry)
{
  // entry is the entry number in the current Tree
  // Selection function to select D* and D0.

  fProcessed++;
  
  // to read complete event, call fChain->GetTree()->GetEntry(entry)
  //fChain->GetTree()->GetEntry(entry);
  
  fChain->GetTree()->GetEntry(entry);

  CheckTrigFilterVertex();
  if(!Pass_trigger_mu and !Pass_trigger_ele) return true;

  bool hasMu = false;
  int nofMu = 0;
  int muIndex = -1;
  for(int muInd = 0; muInd < int(nMuon_); ++muInd){
    int genIdx = int(muGenIdx_[muInd]);
    float eta = muEta_[muInd];
    float pt = muPt_[muInd];
    float phi = muPhi_[muInd];
    int nTrackerLayers = munTrackerLayers_[muInd];
    int charge =  muCharge_[muInd];
    float mudxy = mudxy_[muInd];
    float mudz = mudz_[muInd];
    double PFrelIso_corr = muPFRelIso_[muInd];
    bool mediumMuonID = muMediumId_[muInd];
    bool passMedium_Iso = (pt >= mu_Pt_cut &&
			   TMath::Abs(eta) <= 2.4 &&
			   mediumMuonID
			   && (PFrelIso_corr < 0.4)
			   );
    
    if(TMath::Abs(charge)!=1 or nTrackerLayers>=20 or nTrackerLayers<0 
       or !(TMath::Finite(eta)) or !(TMath::Finite(pt)) or !(TMath::Finite(phi)) 
       or TMath::Abs(mudxy)>=0.2 or TMath::Abs(mudz)>=0.5 or !passMedium_Iso) continue; 
    
    if ( (genIdx>-1) && (genIdx < int(nGenPart_))){
      unsigned int imc = genIdx ;
      TParticlePDG *partPDG = TDatabasePDG::Instance()->GetParticle(GenPart_pdgId_[imc]);
      TParticlePDG *partPDG_mother = TDatabasePDG::Instance()->GetParticle(GenPart_pdgId_[GenPart_genPartIdxMother_[imc]]);
      if(!partPDG_mother){
      }else{
  	// printf("\tMuon PDG : %5d (%7s), Rec:(%5.2f, %5.2f, %5.2f, %1d, %5.2f), Gen:(%5.2f, %5.2f, %5.2f, %1.0f, %5.2f), Mother : %7s\n", 
  	// 	 GenPart_pdgId_[imc], partPDG->GetName(), 
  	// 	 muPt_[muInd], muEta_[muInd] , muPhi_[muInd], muCharge_[muInd], muMass_[muInd],  
  	// 	 GenPart_pt_[imc], GenPart_eta_[imc] , GenPart_phi_[imc], partPDG->Charge()/3., GenPart_mass_[imc], 
  	// 	 partPDG_mother->GetName());
  	mujetR.SetPtEtaPhiM(muPt_[muInd], muEta_[muInd] , muPhi_[muInd], muMass_[muInd]);
  	mujetG.SetPtEtaPhiM(GenPart_pt_[imc], GenPart_eta_[imc] , GenPart_phi_[imc], GenPart_mass_[imc]);
  	if(mujetR.DeltaR(mujetG) < 0.1 and muCharge_[muInd]==int(partPDG->Charge()/3. and abs(GenPart_pdgId_[imc])==13)){
	//if(mujetR.DeltaR(mujetG) < 0.4 and muCharge_[muInd]==int(partPDG->Charge()/3. and abs(GenPart_pdgId_[imc])==13)){ //larger Delta R
	//if(muCharge_[muInd]==int(partPDG->Charge()/3. and abs(GenPart_pdgId_[imc])==13)){ //no Delta R
  	  hasMu = true;
	  nofMu++;
	  muIndex = muInd;
  	  //cout << "Found muon " << endl;
  	}
      }
    }
  }//muon loop
    
  bool hasEle = false;
  int nofEle = 0;
  int eleIndex = -1;
  for(int eleInd = 0; eleInd < int(nEle_); ++eleInd){
    int genIdx = int(eleGenIdx_[eleInd]);

    double eta = eleEta_[eleInd];
    double absEta = TMath::Abs(eta);
    double phi = elePhi_[eleInd];
    double SCeta = eta + eleDeltaEtaSC_[eleInd];
    double absSCEta = TMath::Abs(SCeta);    
    double pt = elePt_[eleInd];
    
    // // EA subtraction
    double PFrelIso_corr = elePFRelIso_[eleInd];
    
    uint eleID = eleIDcutbased_[eleInd];
    bool passVetoID   = eleID >= 1;
    // bool passLooseID  = eleID >= 2;
    // bool passMediumID = eleID >= 3;
    // bool passTightID  = eleID >= 4;
    
    // make sure it doesn't fall within the gap
    bool passEtaEBEEGap = (absSCEta < 1.4442) || (absSCEta > 1.566);
    
    // D0 and Dz cuts are different for barrel and endcap
    bool passD0 = ((absSCEta < 1.479 && abs(eleD0_[eleInd]) < 0.05) ||
		   (absSCEta > 1.479 && abs(eleD0_[eleInd]) < 0.1));
    bool passDz = ((absSCEta < 1.479 && abs(eleDz_[eleInd]) < 0.1) ||
		   (absSCEta > 1.479 && abs(eleDz_[eleInd]) < 0.2));
    bool passMediumID_noIso = passEleID(eleInd, 3,false) && passVetoID;
    
    bool eleSel_Medium_noIso = (passEtaEBEEGap && 
				absSCEta <= 2.4 &&
				pt >= ele_Pt_cut &&
				passMediumID_noIso &&
				elePFRelIso_[eleInd] < 0.3 && 
				passD0 &&
				passDz);
    
    if(!eleSel_Medium_noIso) continue;
    if ( (genIdx>-1) && (genIdx < int(nGenPart_))){
      unsigned int imc = genIdx ;
      TParticlePDG *partPDG = TDatabasePDG::Instance()->GetParticle(GenPart_pdgId_[imc]);
      TParticlePDG *partPDG_mother = TDatabasePDG::Instance()->GetParticle(GenPart_pdgId_[GenPart_genPartIdxMother_[imc]]);
      if(!partPDG_mother){
      }else{
  	// printf("\tElectron : PDG : %5d (%7s), Rec:(%5.2f, %5.2f, %5.2f, %1d, %5.2f), Gen:(%5.2f, %5.2f, %5.2f, %5.2f), Mother : %7s\n", 
  	// 	 GenPart_pdgId_[imc], partPDG->GetName(), 
  	// 	 elePt_[eleInd], eleEta_[eleInd] , elePhi_[eleInd], eleCharge_[eleInd], eleMass_[eleInd],  
  	// 	 GenPart_pt_[imc], GenPart_eta_[imc] , GenPart_phi_[imc], GenPart_mass_[imc], 
  	// 	 partPDG_mother->GetName());
  	elejetR.SetPtEtaPhiM(elePt_[eleInd], eleEta_[eleInd] , elePhi_[eleInd], eleMass_[eleInd]);
  	elejetG.SetPtEtaPhiM(GenPart_pt_[imc], GenPart_eta_[imc] , GenPart_phi_[imc], GenPart_mass_[imc]);
  	if(elejetR.DeltaR(elejetG) < 0.1 and eleCharge_[eleInd]==int(partPDG->Charge()/3.) and abs(GenPart_pdgId_[imc])==11){
  	//if(elejetR.DeltaR(elejetG) < 0.4 and eleCharge_[eleInd]==int(partPDG->Charge()/3.) and abs(GenPart_pdgId_[imc])==11){ //larger deltaR
	//if(eleCharge_[eleInd]==int(partPDG->Charge()/3.) and abs(GenPart_pdgId_[imc])==11){ //no deltaR
  	  hasEle = true;
  	  nofEle++;
	  eleIndex = eleInd;
	  //cout << "Found electron " << endl;
  	}
	  
      }
    }
  }//electron loop
  
  
  if((nofMu==1 and nofEle==0) or (nofMu==0 and nofEle==1)){

    hNofMu->Fill(nofMu);
    hNofEle->Fill(nofEle);

    if(nofMu==1){
      int genIdx = int(muGenIdx_[muIndex]);
      unsigned int imc = genIdx ;
      TParticlePDG *partPDG = TDatabasePDG::Instance()->GetParticle(GenPart_pdgId_[imc]);
      TParticlePDG *partPDG_mother = TDatabasePDG::Instance()->GetParticle(GenPart_pdgId_[GenPart_genPartIdxMother_[imc]]);
    
      mujetR.SetPtEtaPhiM(muPt_[muIndex], muEta_[muIndex] , muPhi_[muIndex], muMass_[muIndex]);
      mujetG.SetPtEtaPhiM(GenPart_pt_[imc], GenPart_eta_[imc] , GenPart_phi_[imc], GenPart_mass_[imc]);
    
      GetHistoBin(hMuEtaETBin, mujetR.Eta(), mujetR.Et(), binEta, binET);
    
      double etResoPercent = 100.*(mujetR.Et() - mujetG.Et())/mujetG.Et();
      double etReso = (mujetR.Et() - mujetG.Et());
      double ptReso = (mujetR.Pt() - mujetG.Pt());
      double enReso = (mujetR.E() - mujetG.E());
      double etaReso = mujetR.Eta() - mujetG.Eta();
      double phiReso = mujetR.DeltaPhi(mujetG) ; //mujetR.Phi() - mujetG.Phi();
      
      hDelRMu->Fill(mujetR.DeltaR(mujetG));

      hMuETReso[binEta-1][binET-1]->Fill(etReso);
      hMuEtaReso[binEta-1][binET-1]->Fill(etaReso);
      hMuPhiReso[binEta-1][binET-1]->Fill(phiReso);

      hMuPtReso[binEta-1][binET-1]->Fill(ptReso);
      hMuEnReso[binEta-1][binET-1]->Fill(enReso);
      // hMuETRRel[binEta-1][binET-1]->Fill(etResoPercent);
      // hMuEtaRRel[binEta-1][binET-1]->Fill(100.*etaReso/mujetG.Eta());
      // hMuPhiRRel[binEta-1][binET-1]->Fill(100.*phiReso/mujetG.Phi());
    }//muon loop

    if(nofEle==1){
      int genIdx = int(eleGenIdx_[eleIndex]);
      unsigned int imc = genIdx ;
      TParticlePDG *partPDG = TDatabasePDG::Instance()->GetParticle(GenPart_pdgId_[imc]);
      TParticlePDG *partPDG_mother = TDatabasePDG::Instance()->GetParticle(GenPart_pdgId_[GenPart_genPartIdxMother_[imc]]);

      elejetR.SetPtEtaPhiM(elePt_[eleIndex], eleEta_[eleIndex] , elePhi_[eleIndex], eleMass_[eleIndex]);
      elejetG.SetPtEtaPhiM(GenPart_pt_[imc], GenPart_eta_[imc] , GenPart_phi_[imc], GenPart_mass_[imc]);
    
      GetHistoBin(hEleEtaETBin, elejetR.Eta(), elejetR.Et(), binEta, binET);
    
      double etResoPercent = 100.*(elejetR.Et() - elejetG.Et())/elejetG.Et();
      double etReso = (elejetR.Et() - elejetG.Et());
      double ptReso = elejetR.Pt() - elejetG.Pt();
      double enReso = elejetR.E() - elejetG.E();
      double etaReso = elejetR.Eta() - elejetG.Eta();
      double phiReso = elejetR.DeltaPhi(elejetG) ; //elejetR.Phi() - elejetG.Phi();
    
      hDelREle->Fill(elejetR.DeltaR(elejetG));
      
      hEleETReso[binEta-1][binET-1]->Fill(etReso);
      hEleEtaReso[binEta-1][binET-1]->Fill(etaReso);
      hElePhiReso[binEta-1][binET-1]->Fill(phiReso);

      hElePtReso[binEta-1][binET-1]->Fill(ptReso);
      hEleEnReso[binEta-1][binET-1]->Fill(enReso);
      // hEleETRRel[binEta-1][binET-1]->Fill(etResoPercent);
      // hEleEtaRRel[binEta-1][binET-1]->Fill(100.*etaReso/elejetG.Eta());
      // hElePhiRRel[binEta-1][binET-1]->Fill(100.*phiReso/elejetG.Phi());
    }//electron loop
    
    int nbjet = 0, nljet = 0;
    for(int jetInd = 0; jetInd < int(nJet_) and int(nJet_) < 10000000; ++jetInd){
      int genIdx = int(jetGenJetIdx_[jetInd]);
      double pt = jetPt_[jetInd];
      double eta = jetEta_[jetInd];
      double phi = jetPhi_[jetInd];
      bool jetID_pass = (jetID_[jetInd]>=2 and (jetPUID_[jetInd]>=1 or pt>=50.0)) ; //lwp
      bool passDR_lep_jet = true;
      jetR.SetPtEtaPhiM(jetPt_[jetInd], jetEta_[jetInd] , jetPhi_[jetInd], jetMass_[jetInd]);
      if(nofMu==1)
	if ( jetR.DeltaR(mujetR) < 0.4) passDR_lep_jet = false;
      if(nofEle==1)
	if ( jetR.DeltaR(elejetR) < 0.4) passDR_lep_jet = false;
    
      bool jetPresel = (pt >= jet_Pt_cut &&
			TMath::Abs(eta) <= 2.4 &&
			jetID_pass &&
			passDR_lep_jet
			);

      if(!jetPresel) continue;
      if ( (genIdx>-1) && (genIdx < int(nGenJet_))){
	unsigned int imc = genIdx ;
	// printf("\tJet : Rec:(%2d, %5.2f, %5.2f, %5.2f, %5.2f), Gen:(%2d, %5.2f, %5.2f, %5.2f, %5.2f)\n", 
	//        jetPartFlvr_[jetInd],jetPt_[jetInd], jetEta_[jetInd] , jetPhi_[jetInd], jetMass_[jetInd],  
	//        GenJet_partonFlavour_[genIdx],GenJet_pt_[genIdx], GenJet_eta_[genIdx] , GenJet_phi_[genIdx], GenJet_mass_[genIdx]);
	if(jetPartFlvr_[jetInd]==GenJet_partonFlavour_[genIdx] and abs(jetPartFlvr_[jetInd])==5 and (jetBtagDeepB_[jetInd] > btag_cut_DeepCSV or jetBtagDeepFlavB_[jetInd] > btag_cut)){
	  bjetR.SetPtEtaPhiM(jetPt_[jetInd], jetEta_[jetInd] , jetPhi_[jetInd], jetMass_[jetInd]);
	  bjetG.SetPtEtaPhiM(GenJet_pt_[genIdx], GenJet_eta_[genIdx] , GenJet_phi_[genIdx], GenJet_mass_[genIdx]);
	  hDelRBJets->Fill(bjetR.DeltaR(bjetG)); 
	  if(bjetR.DeltaR(bjetG)<0.2)
	  //if(bjetR.DeltaR(bjetG)<0.4) //Driven by Jet Rec-Gen DeltaR	    
	     nbjet++;
	}//b-jet condition
	
	if(jetPartFlvr_[jetInd]==GenJet_partonFlavour_[genIdx] and ((abs(jetPartFlvr_[jetInd])>=1 and abs(jetPartFlvr_[jetInd])<=4) or abs(jetPartFlvr_[jetInd])==21) ){ //u,d,s,c,g
	  ljetR.SetPtEtaPhiM(jetPt_[jetInd], jetEta_[jetInd] , jetPhi_[jetInd], jetMass_[jetInd]);
	  ljetG.SetPtEtaPhiM(GenJet_pt_[genIdx], GenJet_eta_[genIdx] , GenJet_phi_[genIdx], GenJet_mass_[genIdx]);
	  hDelRLJets->Fill(ljetR.DeltaR(ljetG));
	  if(ljetR.DeltaR(ljetG)<0.2)
	  //if(ljetR.DeltaR(ljetG)<0.4) //Driven by Jet Rec-Gen DeltaR
	    nljet++;
	}//l-jet condition
	
      }//found the corresponding genjet 
    }//jet loop
  
    if(nljet < 2 or nbjet < 2) return true;
    
    hNofBJets->Fill(nbjet);
    hNofLJets->Fill(nljet);
    
    // //for (unsigned int imc = 0 ; imc < nGenPart_ ; imc++ ){      
    // for (unsigned int imc = 0 ; imc < 30 ; imc++ ){      
    //   TParticlePDG *partPDG = TDatabasePDG::Instance()->GetParticle(GenPart_pdgId_[imc]);
    //   if(!partPDG){
    // 	printf("\t id : %03d, PDG : %5d ( noPDGname), status : %2d, (Pt, Eta, Phi, Mass) = (%5.2f, %5.2f, %5.2f, %5.2f), Mother-id : %03d\n", 
    // 	       imc, GenPart_pdgId_[imc], GenPart_status_[imc], GenPart_pt_[imc], 
    // 	       GenPart_eta_[imc] , GenPart_phi_[imc], GenPart_mass_[imc], GenPart_genPartIdxMother_[imc]
    // 	       );
    //   }else{
    // 	printf("\t id : %03d, PDG : %5d (%7s), status : %2d, (Pt, Eta, Phi, Mass) = (%5.2f, %5.2f, %5.2f, %5.2f), Mother-id : %03d\n", 
    // 	       imc, GenPart_pdgId_[imc], partPDG->GetName(), GenPart_status_[imc], GenPart_pt_[imc],
    // 	       GenPart_eta_[imc] , GenPart_phi_[imc], GenPart_mass_[imc], GenPart_genPartIdxMother_[imc]
    // 	       );
    //   }
    // }// mc particle loop
    
    // printf("MET Rec:(%5.2f, %5.2f) Gen:(%5.2f, %5.2f), Reso : (%5.2f,%5.2f)\n",MET_pt_,MET_phi_,GenMET_pt_,GenMET_phi_, 
    // 	   100.*abs(MET_pt_-GenMET_pt_)/MET_pt_, 100.*abs(MET_phi_-GenMET_phi_)/MET_phi_);
    
    metR.SetPtEtaPhiM(MET_pt_, 0.0, MET_phi_, 0.0);
    metG.SetPtEtaPhiM(GenMET_pt_, 0.0, GenMET_phi_, 0.0);
    
    binET = GetHistoBin(hMETETBin, metR.Et());
    double etResoPercent = 100.*(metR.Et() - metG.Et())/metG.Et();
    double etReso = (metR.Et() - metG.Et());
    double ptReso = (metR.Pt() - metG.Pt());
    double phiReso = metR.DeltaPhi(metG) ; //metR.Phi() - metG.Phi();
    hDelRMET->Fill(metR.DeltaR(metG));
    hMETETReso[binET-1]->Fill(etReso);
    hMETPhiReso[binET-1]->Fill(phiReso);
    hMETPtReso[binET-1]->Fill(ptReso);
    hMETETRRel[binET-1]->Fill(etResoPercent);
    hMETPhiRRel[binET-1]->Fill(100.*phiReso/metG.Phi());
    
    for(int jetInd = 0; jetInd < int(nJet_) and int(nJet_) < 10000000; ++jetInd){
      int genIdx = int(jetGenJetIdx_[jetInd]);
      double pt = jetPt_[jetInd];
      double eta = jetEta_[jetInd];
      double phi = jetPhi_[jetInd];
      bool jetID_pass = (jetID_[jetInd]>=2 and (jetPUID_[jetInd]>=1 or pt>=50.0)) ; //lwp
      bool passDR_lep_jet = true;
      jetR.SetPtEtaPhiM(jetPt_[jetInd], jetEta_[jetInd] , jetPhi_[jetInd], jetMass_[jetInd]);
      if(nofMu==1)
	if ( jetR.DeltaR(mujetR) < 0.4) passDR_lep_jet = false;
      if(nofEle==1)
	if ( jetR.DeltaR(elejetR) < 0.4) passDR_lep_jet = false;
      
      bool jetPresel = (pt >= jet_Pt_cut &&
			TMath::Abs(eta) <= 2.4 &&
			jetID_pass &&
			passDR_lep_jet
			);
      if(!jetPresel) continue;
      if ( (genIdx>-1) && (genIdx < int(nGenJet_))){
	unsigned int imc = genIdx ;
	// printf("\tJet : Rec:(%2d, %5.2f, %5.2f, %5.2f, %5.2f), Gen:(%2d, %5.2f, %5.2f, %5.2f, %5.2f)\n", 
	//        jetPartFlvr_[jetInd],jetPt_[jetInd], jetEta_[jetInd] , jetPhi_[jetInd], jetMass_[jetInd],  
	//        GenJet_partonFlavour_[genIdx],GenJet_pt_[genIdx], GenJet_eta_[genIdx] , GenJet_phi_[genIdx], GenJet_mass_[genIdx]);
	if(jetPartFlvr_[jetInd]==GenJet_partonFlavour_[genIdx] and abs(jetPartFlvr_[jetInd])==5 and (jetBtagDeepB_[jetInd] > btag_cut_DeepCSV or jetBtagDeepFlavB_[jetInd] > btag_cut)){
	  //if(jetPartFlvr_[jetInd]==GenJet_partonFlavour_[genIdx] and abs(jetPartFlvr_[jetInd])==5){
	  bjetR.SetPtEtaPhiM(jetPt_[jetInd], jetEta_[jetInd] , jetPhi_[jetInd], jetMass_[jetInd]);
	  bjetG.SetPtEtaPhiM(GenJet_pt_[genIdx], GenJet_eta_[genIdx] , GenJet_phi_[genIdx], GenJet_mass_[genIdx]);

	  GetHistoBin(hJetEtaETBin, bjetR.Eta(), bjetR.Et(), binEta, binET);

	  double etResoPercent = 100.*(bjetR.Et() - bjetG.Et())/bjetG.Et();
	  double etReso = (bjetR.Et() - bjetG.Et());
	  double ptReso = (bjetR.Pt() - bjetG.Pt());
	  double enReso = (bjetR.E() - bjetG.E());
	  double etaReso = bjetR.Eta() - bjetG.Eta();
	  double phiReso = bjetR.DeltaPhi(bjetG) ; //bjetR.Phi() - bjetG.Phi();
	  
	  if(bjetR.DeltaR(bjetG)<0.2){
	  //if(bjetR.DeltaR(bjetG)<0.4){ //Driven by Jet Rec-Gen DeltaR
	    hBJetETReso[binEta-1][binET-1]->Fill(etReso);
	    hBJetEtaReso[binEta-1][binET-1]->Fill(etaReso);
	    hBJetPhiReso[binEta-1][binET-1]->Fill(phiReso);

	    hBJetPtReso[binEta-1][binET-1]->Fill(ptReso);
	    hBJetEnReso[binEta-1][binET-1]->Fill(enReso);
	    // hBJetETRRel[binEta-1][binET-1]->Fill(etResoPercent);
	    // hBJetEtaRRel[binEta-1][binET-1]->Fill(100.*etaReso/bjetG.Eta());
	    // hBJetPhiRRel[binEta-1][binET-1]->Fill(100.*phiReso/bjetG.Phi());
	  }
	  //hBJetETDelRReso[binET-1]->Fill(bjetR.DeltaR(bjetG));
	}//b-jet condition
      
	if(jetPartFlvr_[jetInd]==GenJet_partonFlavour_[genIdx] and ((abs(jetPartFlvr_[jetInd])>=1 and abs(jetPartFlvr_[jetInd])<=4) or abs(jetPartFlvr_[jetInd])==21) ){ //u,d,s,c,g
	  ljetR.SetPtEtaPhiM(jetPt_[jetInd], jetEta_[jetInd] , jetPhi_[jetInd], jetMass_[jetInd]);
	  ljetG.SetPtEtaPhiM(GenJet_pt_[genIdx], GenJet_eta_[genIdx] , GenJet_phi_[genIdx], GenJet_mass_[genIdx]);

	  GetHistoBin(hJetEtaETBin, ljetR.Eta(), ljetR.Et(), binEta, binET);

	  double etResoPercent = 100.*(ljetR.Et() - ljetG.Et())/ljetG.Et();
	  double etReso = (ljetR.Et() - ljetG.Et());
	  double ptReso = (ljetR.Pt() - ljetG.Pt());
	  double enReso = (ljetR.E() - ljetG.E());
	  double etaReso = ljetR.Eta() - ljetG.Eta();
	  double phiReso = ljetR.DeltaPhi(ljetG) ; //ljetR.Phi() - ljetG.Phi();
	  
	  if(ljetR.DeltaR(ljetG)<0.2){
	  //if(ljetR.DeltaR(ljetG)<0.4){ //Driven by Jet Rec-Gen DeltaR
	    hLJetETReso[binEta-1][binET-1]->Fill(etReso);
	    hLJetEtaReso[binEta-1][binET-1]->Fill(etaReso);
	    hLJetPhiReso[binEta-1][binET-1]->Fill(phiReso);
	    
	    hLJetPtReso[binEta-1][binET-1]->Fill(ptReso);
	    hLJetEnReso[binEta-1][binET-1]->Fill(enReso);
	    // hLJetETRRel[binEta-1][binET-1]->Fill(etResoPercent);
	    // hLJetEtaRRel[binEta-1][binET-1]->Fill(100.*etaReso/ljetG.Eta());
	    // hLJetPhiRRel[binEta-1][binET-1]->Fill(100.*phiReso/ljetG.Phi());
	  }
	}//l-jet condition
	
      }//found the corresponding genjet 
    }//jet loop
  }//if nmu==1 or nele==1

  fStatus++;
   
  return kTRUE;
}


//_____________________________________________________________________________
void KFObjectReso::SlaveTerminate()
{
  
  Info("SlaveTerminate",
       "sample : %s, year : %d, mode : %s", fSample.Data(), fYear, fMode.Data());

  
  // File closure
  
  for(int ifile=0;ifile<1;ifile++){
    
    TDirectory *savedir = gDirectory;
    savedir->cd();
    
    fFile[ifile]->cd();

    hNofMu->Write();
    hNofEle->Write();
    hNofBJets->Write();
    hNofLJets->Write();

    hDelRMu->Write();
    hDelREle->Write();
    hDelRMET->Write();
    hDelRBJets->Write();
    hDelRLJets->Write();

    ///////////////////////////////
    for(int ieta=0;ieta<nJetEtaBins;ieta++)
      for(int iet=0;iet<nETBins;iet++)
	hBJetETReso[ieta][iet]->Write();
    for(int ieta=0;ieta<nJetEtaBins;ieta++)
      for(int iet=0;iet<nETBins;iet++)  
	hLJetETReso[ieta][iet]->Write();
    for(int ieta=0;ieta<nJetEtaBins;ieta++)
      for(int iet=0;iet<nETBins;iet++)
	hBJetEtaReso[ieta][iet]->Write();
    for(int ieta=0;ieta<nJetEtaBins;ieta++)
      for(int iet=0;iet<nETBins;iet++)  
	hLJetEtaReso[ieta][iet]->Write();
    for(int ieta=0;ieta<nJetEtaBins;ieta++)
      for(int iet=0;iet<nETBins;iet++)
	hBJetPhiReso[ieta][iet]->Write();
    for(int ieta=0;ieta<nJetEtaBins;ieta++)
      for(int iet=0;iet<nETBins;iet++)  
	hLJetPhiReso[ieta][iet]->Write();
    for(int ieta=0;ieta<nMuEtaBins;ieta++)
      for(int iet=0;iet<nETBins;iet++)
	hMuETReso[ieta][iet]->Write();
    for(int ieta=0;ieta<nMuEtaBins;ieta++)
      for(int iet=0;iet<nETBins;iet++)
	hMuEtaReso[ieta][iet]->Write();
    for(int ieta=0;ieta<nMuEtaBins;ieta++)
      for(int iet=0;iet<nETBins;iet++)
	hMuPhiReso[ieta][iet]->Write();
    for(int ieta=0;ieta<nEleEtaBins;ieta++)
      for(int iet=0;iet<nETBins;iet++)
	hEleETReso[ieta][iet]->Write();
    for(int ieta=0;ieta<nEleEtaBins;ieta++)
      for(int iet=0;iet<nETBins;iet++)
	hEleEtaReso[ieta][iet]->Write();
    for(int ieta=0;ieta<nEleEtaBins;ieta++)
      for(int iet=0;iet<nETBins;iet++)
	hElePhiReso[ieta][iet]->Write();  
    for(int iet=0;iet<nETBins;iet++)
      hMETETReso[iet]->Write();
    for(int iet=0;iet<nETBins;iet++)
      hMETPhiReso[iet]->Write();

    for(int ieta=0;ieta<nJetEtaBins;ieta++)
      for(int iet=0;iet<nETBins;iet++)
	hBJetPtReso[ieta][iet]->Write();
    for(int ieta=0;ieta<nJetEtaBins;ieta++)
      for(int iet=0;iet<nETBins;iet++)  
	hLJetPtReso[ieta][iet]->Write();
    for(int ieta=0;ieta<nJetEtaBins;ieta++)
      for(int iet=0;iet<nETBins;iet++)
	hBJetEnReso[ieta][iet]->Write();
    for(int ieta=0;ieta<nJetEtaBins;ieta++)
      for(int iet=0;iet<nETBins;iet++)  
	hLJetEnReso[ieta][iet]->Write();
    for(int ieta=0;ieta<nMuEtaBins;ieta++)
      for(int iet=0;iet<nETBins;iet++)
	hMuPtReso[ieta][iet]->Write();
    for(int ieta=0;ieta<nMuEtaBins;ieta++)
      for(int iet=0;iet<nETBins;iet++)
	hMuEnReso[ieta][iet]->Write();
    for(int ieta=0;ieta<nEleEtaBins;ieta++)
      for(int iet=0;iet<nETBins;iet++)
	hElePtReso[ieta][iet]->Write();
    for(int ieta=0;ieta<nEleEtaBins;ieta++)
      for(int iet=0;iet<nETBins;iet++)
	hEleEnReso[ieta][iet]->Write();
    for(int iet=0;iet<nETBins;iet++)
      hMETPtReso[iet]->Write();
    
    // for(int ieta=0;ieta<nJetEtaBins;ieta++)
    //   for(int iet=0;iet<nETBins;iet++)
    // 	hBJetETRRel[ieta][iet]->Write();
    // for(int ieta=0;ieta<nJetEtaBins;ieta++)
    //   for(int iet=0;iet<nETBins;iet++)  
    // 	hLJetETRRel[ieta][iet]->Write();
    // for(int ieta=0;ieta<nJetEtaBins;ieta++)
    //   for(int iet=0;iet<nETBins;iet++)
    // 	hBJetEtaRRel[ieta][iet]->Write();
    // for(int ieta=0;ieta<nJetEtaBins;ieta++)
    //   for(int iet=0;iet<nETBins;iet++)  
    // 	hLJetEtaRRel[ieta][iet]->Write();
    // for(int ieta=0;ieta<nJetEtaBins;ieta++)
    //   for(int iet=0;iet<nETBins;iet++)
    // 	hBJetPhiRRel[ieta][iet]->Write();
    // for(int ieta=0;ieta<nJetEtaBins;ieta++)
    //   for(int iet=0;iet<nETBins;iet++)  
    // 	hLJetPhiRRel[ieta][iet]->Write();
    // for(int ieta=0;ieta<nMuEtaBins;ieta++)
    //   for(int iet=0;iet<nETBins;iet++)
    // 	hMuETRRel[ieta][iet]->Write();
    // for(int ieta=0;ieta<nMuEtaBins;ieta++)
    //   for(int iet=0;iet<nETBins;iet++)
    // 	hMuEtaRRel[ieta][iet]->Write();
    // for(int ieta=0;ieta<nMuEtaBins;ieta++)
    //   for(int iet=0;iet<nETBins;iet++)
    // 	hMuPhiRRel[ieta][iet]->Write();
    // for(int ieta=0;ieta<nEleEtaBins;ieta++)
    //   for(int iet=0;iet<nETBins;iet++)
    // 	hEleETRRel[ieta][iet]->Write();
    // for(int ieta=0;ieta<nEleEtaBins;ieta++)
    //   for(int iet=0;iet<nETBins;iet++)
    // 	hEleEtaRRel[ieta][iet]->Write();
    // for(int ieta=0;ieta<nEleEtaBins;ieta++)
    //   for(int iet=0;iet<nETBins;iet++)
    // 	hElePhiRRel[ieta][iet]->Write();  
    // for(int iet=0;iet<nETBins;iet++)
    //   hMETETRRel[iet]->Write();
    // for(int iet=0;iet<nETBins;iet++)
    //   hMETPhiRRel[iet]->Write();

    ///////////////////////////////
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


}

//_____________________________________________________________________________
void KFObjectReso::Terminate()
{
// function called at the end of the event loop

   if (!fInput) Info("Terminate", "processed %lld events", fProcessed);
   
   TString option = GetOption();
   Info("Terminate", "stopping KFObjectReso with process option: %s", option.Data());
   
}
