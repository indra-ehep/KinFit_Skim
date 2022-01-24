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

  // nMuEtaBins = 25;
  // Float_t muEtaBin[26] = {0.0, 0.100, 0.200, 0.300, 0.400, 
  // 			  0.500, 0.600, 0.700, 0.800, 0.900, 
  // 			  1.000, 1.100, 1.200, 1.300, 1.400, 
  // 			  1.500, 1.600, 1.700, 1.800, 1.900, 
  // 			  2.000, 2.100, 2.200, 2.300, 2.4,
  //                         2.5};
  nMuEtaBins = 20;
  Float_t muEtaBin[21] = {-2.5, -2.2, -1.9, -1.6, -1.3,
			  -1.0, -0.9, -0.8, -0.6, -0.4,
			  -0.3, -0.2, -0.1,  0.0,  0.1, 
			   0.2,  0.3,  0.4,  0.6,  0.8, 
                           1.0,  1.3,  1.6,  1.9,  2.2, 2.5};
  
  // nEleEtaBins = 24;
  // Float_t eleEtaBin[25] = {0.0, 0.174, 0.261, 0.348, 0.435, 
  // 			   0.522, 0.609, 0.696, 0.783, 0.870, 
  // 			   0.957, 1.044, 1.131, 1.218, 1.305, 
  // 			   1.392, 1.479, 1.653, 1.740, 1.830, 
  // 			   1.930, 2.043, 2.172, 2.322, 2.5};
  
  nEleEtaBins = 20;
  Float_t eleEtaBin[21] = {-2.5, -2.2, -1.9, -1.6, -1.3,
			  -1.0, -0.9, -0.8, -0.6, -0.4,
			  -0.3, -0.2, -0.1,  0.0,  0.1, 
			   0.2,  0.3,  0.4,  0.6,  0.8, 
                           1.0,  1.3,  1.6,  1.9,  2.2, 2.5};

  // nJetEtaBins = 26;
  // Float_t jetEtaBin[27] = {0.0, 0.087, 0.174, 0.261, 0.348, 
  // 			   0.435, 0.522, 0.609, 0.696, 0.783, 
  // 			   0.870, 0.957, 1.044, 1.131, 1.218, 
  // 			   1.305, 1.392, 1.479, 1.566, 1.653, 
  // 			   1.740, 1.830, 1.930, 2.043, 2.172, 
  // 			   2.322, 2.5};
  
  nJetEtaBins = 20;
  Float_t jetEtaBin[21] = {-2.5, -2.2, -1.9, -1.6, -1.3,
			  -1.0, -0.9, -0.8, -0.6, -0.4,
			  -0.3, -0.2, -0.1,  0.0,  0.1, 
			   0.2,  0.3,  0.4,  0.6,  0.8, 
                           1.0,  1.3,  1.6,  1.9,  2.2, 2.5};
  
  // nJetEtaBins = 1;
  // Float_t jetEtaBin[2] = {0.435, 0.783};
  
  nETBins = 19;
  Float_t ETBin[20] = {20., 30., 40., 50., 60.,
                       70., 80., 90., 100., 120.,
                       140., 160., 180., 200., 240., 
                       280., 320., 360., 400., 500.};
  
  for(int ifile=0;ifile<1;ifile++){

    TDirectory *savedir = gDirectory;
    savedir->cd();

    fFile[ifile]->cd();
  
    hBJetETReso = new TH1F**[nJetEtaBins];
    hLJetETReso = new TH1F**[nJetEtaBins];
    hBJetEtaReso = new TH1F**[nJetEtaBins];
    hLJetEtaReso = new TH1F**[nJetEtaBins];
    hBJetPhiReso = new TH1F**[nJetEtaBins];
    hLJetPhiReso = new TH1F**[nJetEtaBins];
    for(int ieta=0;ieta<nJetEtaBins;ieta++){
      hBJetETReso[ieta] = new TH1F*[nETBins];
      hLJetETReso[ieta] = new TH1F*[nETBins];
      hBJetEtaReso[ieta] = new TH1F*[nETBins];
      hLJetEtaReso[ieta] = new TH1F*[nETBins];
      hBJetPhiReso[ieta] = new TH1F*[nETBins];
      hLJetPhiReso[ieta] = new TH1F*[nETBins];
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
	// hBJetETDelRReso[iet] = new TH1F(Form("hBJetETDelRReso_0_%d",iet),Form("hBJetETDelRReso_0_%d",iet), 200, 0.,1.);
      }// jet et
    }//jet eta
    hJetEtaETBin = new TH2F("hJetEtaETBin","hJetEtaETBin", nJetEtaBins, jetEtaBin, nETBins, ETBin);

    hMuETReso = new TH1F**[nMuEtaBins];
    hMuEtaReso = new TH1F**[nMuEtaBins];
    hMuPhiReso = new TH1F**[nMuEtaBins];
    for(int ieta=0;ieta<nMuEtaBins;ieta++){
      hMuETReso[ieta] = new TH1F*[nETBins];
      hMuEtaReso[ieta] = new TH1F*[nETBins];
      hMuPhiReso[ieta] = new TH1F*[nETBins];
      for(int iet=0;iet<nETBins;iet++){
	hMuETReso[ieta][iet] = new TH1F(Form("hMuETReso_%d_%d",ieta,iet),
					Form("hMuETReso #eta:(%4.3f-%4.3f) E_{T}:(%2.0f-%2.0f) GeV",muEtaBin[ieta],muEtaBin[ieta+1],ETBin[iet],ETBin[iet+1]),
					200,-20.,20.);
	hMuEtaReso[ieta][iet] = new TH1F(Form("hMuEtaReso_%d_%d",ieta,iet),
					 Form("hMuEtaReso #eta:(%4.3f-%4.3f) E_{T}:(%2.0f-%2.0f) GeV",muEtaBin[ieta],muEtaBin[ieta+1],ETBin[iet],ETBin[iet+1]),
					 200, -0.01, 0.01);
	hMuPhiReso[ieta][iet] = new TH1F(Form("hMuPhiReso_%d_%d",ieta,iet),
					 Form("hMuPhiReso #eta:(%4.3f-%4.3f) E_{T}:(%2.0f-%2.0f) GeV",muEtaBin[ieta],muEtaBin[ieta+1],ETBin[iet],ETBin[iet+1]),
					 200, -0.01, 0.01);
      }//mu et
    }//mu eta
    hMuEtaETBin = new TH2F("hMuEtaETBin","hMuEtaETBin", nMuEtaBins, muEtaBin, nETBins, ETBin);

    hEleETReso = new TH1F**[nEleEtaBins];
    hEleEtaReso = new TH1F**[nEleEtaBins];
    hElePhiReso = new TH1F**[nEleEtaBins];
    for(int ieta=0;ieta<nEleEtaBins;ieta++){
      hEleETReso[ieta] = new TH1F*[nETBins];
      hEleEtaReso[ieta] = new TH1F*[nETBins];
      hElePhiReso[ieta] = new TH1F*[nETBins];
      for(int iet=0;iet<nETBins;iet++){
	hEleETReso[ieta][iet] = new TH1F(Form("hEleETReso_%d_%d",ieta,iet),
					 Form("hEleETReso #eta:(%4.3f-%4.3f) E_{T}:(%2.0f-%2.0f) GeV",eleEtaBin[ieta],eleEtaBin[ieta+1],ETBin[iet],ETBin[iet+1]),
					 200,-40.,40.);
	hEleEtaReso[ieta][iet] = new TH1F(Form("hEleEtaReso_%d_%d",ieta,iet),
					  Form("hEleEtaReso #eta:(%4.3f-%4.3f) E_{T}:(%2.0f-%2.0f) GeV",eleEtaBin[ieta],eleEtaBin[ieta+1],ETBin[iet],ETBin[iet+1]),
					  50, -0.05, 0.05);
	hElePhiReso[ieta][iet] = new TH1F(Form("hElePhiReso_%d_%d",ieta,iet),
					  Form("hElePhiReso #eta:(%4.3f-%4.3f) E_{T}:(%2.0f-%2.0f) GeV",eleEtaBin[ieta],eleEtaBin[ieta+1],ETBin[iet],ETBin[iet+1]),
					  40, -0.05, 0.05);
      }//ele et
    }//ele eta
    hEleEtaETBin = new TH2F("hEleEtaETBin","hEleEtaETBin", nEleEtaBins, eleEtaBin, nETBins, ETBin);

    hMETETReso = new TH1F*[nETBins];
    hMETPhiReso = new TH1F*[nETBins];
    for(int iet=0;iet<nETBins;iet++){
      hMETETReso[iet] = new TH1F(Form("hMETETReso_%d",iet),Form("hMETETReso_%d E_{T}:(%2.0f-%2.0f) GeV",iet,ETBin[iet],ETBin[iet+1]),400,-400.,400.);
      hMETPhiReso[iet] = new TH1F(Form("hMETPhiReso_%d",iet),Form("hMETPhiReso_%d E_{T}:(%2.0f-%2.0f) GeV",iet,ETBin[iet],ETBin[iet+1]),200, -2.0, 2.0);
    }
    hMETETBin = new TH1F("hMETETBin","hMETETBin", nETBins, ETBin);


  }//file loop

  
  return true;
}

//_____________________________________________________________________________
void KFObjectReso::SlaveBegin(TTree *tree)
{
  //initialize the Tree branch addresses
  Init(tree);
  
  //print the option specified in the Process function.
  TString option = GetOption();
  Info("SlaveBegin",
       "starting KFObjectReso with process option: %s (tree: %p)", option.Data(), tree);

  GetArguments();
  Info("SlaveBegin",
       "sample : %s, year : %d, mode : %s", fSample.Data(), fYear, fMode.Data());
  
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
Bool_t KFObjectReso::Process(Long64_t entry)
{
  // entry is the entry number in the current Tree
  // Selection function to select D* and D0.

  fProcessed++;
  
  // to read complete event, call fChain->GetTree()->GetEntry(entry)
  //fChain->GetTree()->GetEntry(entry);
  
  fChain->GetTree()->GetEntry(entry);
  
  // bool hasMu = false;
  // for(int muInd = 0; muInd < int(nMuon_); ++muInd){
  //   int genIdx = int(muGenIdx_[muInd]);
  //   if ( (genIdx>-1) && (genIdx < int(nGenPart_))){
  //     unsigned int imc = genIdx ;
  //     TParticlePDG *partPDG = TDatabasePDG::Instance()->GetParticle(GenPart_pdgId_[imc]);
  //     TParticlePDG *partPDG_mother = TDatabasePDG::Instance()->GetParticle(GenPart_pdgId_[GenPart_genPartIdxMother_[imc]]);
  //     if(!partPDG_mother){
  //     }else{
  // 	// printf("\tMuon PDG : %5d (%7s), Rec:(%5.2f, %5.2f, %5.2f, %1d, %5.2f), Gen:(%5.2f, %5.2f, %5.2f, %1.0f, %5.2f), Mother : %7s\n", 
  // 	// 	 GenPart_pdgId_[imc], partPDG->GetName(), 
  // 	// 	 muPt_[muInd], muEta_[muInd] , muPhi_[muInd], muCharge_[muInd], muMass_[muInd],  
  // 	// 	 GenPart_pt_[imc], GenPart_eta_[imc] , GenPart_phi_[imc], partPDG->Charge()/3., GenPart_mass_[imc], 
  // 	// 	 partPDG_mother->GetName());
  // 	mujetR.SetPtEtaPhiM(muPt_[muInd], muEta_[muInd] , muPhi_[muInd], muMass_[muInd]);
  // 	mujetG.SetPtEtaPhiM(GenPart_pt_[imc], GenPart_eta_[imc] , GenPart_phi_[imc], GenPart_mass_[imc]);
  // 	if(mujetR.DeltaR(mujetG) < 0.1 and muCharge_[muInd]==int(partPDG->Charge()/3. and abs(GenPart_pdgId_[imc])==13)){
  // 	  hasMu = true;
  // 	  //cout << "Found muon " << endl;
  // 	}
  //     }
  //   }
  // }//muon loop
    
  // bool hasEle = false;
  // for(int eleInd = 0; eleInd < int(nEle_); ++eleInd){
  //   int genIdx = int(eleGenIdx_[eleInd]);
  //   if ( (genIdx>-1) && (genIdx < int(nGenPart_))){
  //     unsigned int imc = genIdx ;
  //     TParticlePDG *partPDG = TDatabasePDG::Instance()->GetParticle(GenPart_pdgId_[imc]);
  //     TParticlePDG *partPDG_mother = TDatabasePDG::Instance()->GetParticle(GenPart_pdgId_[GenPart_genPartIdxMother_[imc]]);
  //     if(!partPDG_mother){
  //     }else{
  // 	// printf("\tElectron : PDG : %5d (%7s), Rec:(%5.2f, %5.2f, %5.2f, %1d, %5.2f), Gen:(%5.2f, %5.2f, %5.2f, %5.2f), Mother : %7s\n", 
  // 	// 	 GenPart_pdgId_[imc], partPDG->GetName(), 
  // 	// 	 elePt_[eleInd], eleEta_[eleInd] , elePhi_[eleInd], eleCharge_[eleInd], eleMass_[eleInd],  
  // 	// 	 GenPart_pt_[imc], GenPart_eta_[imc] , GenPart_phi_[imc], GenPart_mass_[imc], 
  // 	// 	 partPDG_mother->GetName());
  // 	elejetR.SetPtEtaPhiM(elePt_[eleInd], eleEta_[eleInd] , elePhi_[eleInd], eleMass_[eleInd]);
  // 	elejetG.SetPtEtaPhiM(GenPart_pt_[imc], GenPart_eta_[imc] , GenPart_phi_[imc], GenPart_mass_[imc]);
  // 	if(elejetR.DeltaR(elejetG) < 0.1 and eleCharge_[eleInd]==int(partPDG->Charge()/3.) and abs(GenPart_pdgId_[imc])==11){
  // 	  hasEle = true;
  // 	  //cout << "Found electron " << endl;
  // 	}
	  
  //     }
  //   }
  // }//electron loop
    
  // int nbjet = 0, nljet = 0;
  // for(int jetInd = 0; jetInd < int(nJet_); ++jetInd){
  //   int genIdx = int(jetGenJetIdx_[jetInd]);
  //   if ( (genIdx>-1) && (genIdx < int(nGenJet_))){
  //     unsigned int imc = genIdx ;
  //     // printf("\tJet : Rec:(%2d, %5.2f, %5.2f, %5.2f, %5.2f), Gen:(%2d, %5.2f, %5.2f, %5.2f, %5.2f)\n", 
  //     //        jetPartFlvr_[jetInd],jetPt_[jetInd], jetEta_[jetInd] , jetPhi_[jetInd], jetMass_[jetInd],  
  //     //        GenJet_partonFlavour_[genIdx],GenJet_pt_[genIdx], GenJet_eta_[genIdx] , GenJet_phi_[genIdx], GenJet_mass_[genIdx]);
  //     if(jetPartFlvr_[jetInd]==GenJet_partonFlavour_[genIdx] and abs(jetPartFlvr_[jetInd])==5){
  // 	bjetR.SetPtEtaPhiM(jetPt_[jetInd], jetEta_[jetInd] , jetPhi_[jetInd], jetMass_[jetInd]);
  // 	bjetG.SetPtEtaPhiM(GenJet_pt_[genIdx], GenJet_eta_[genIdx] , GenJet_phi_[genIdx], GenJet_mass_[genIdx]);
  // 	if(bjetR.DeltaR(bjetG)<0.2)
  // 	  nbjet++;
  //     }//b-jet condition
	
  //     if(jetPartFlvr_[jetInd]==GenJet_partonFlavour_[genIdx] and ((abs(jetPartFlvr_[jetInd])>=1 and abs(jetPartFlvr_[jetInd])<=4) or abs(jetPartFlvr_[jetInd])==21) ){ //u,d,s,c,g
  // 	ljetR.SetPtEtaPhiM(jetPt_[jetInd], jetEta_[jetInd] , jetPhi_[jetInd], jetMass_[jetInd]);
  // 	ljetG.SetPtEtaPhiM(GenJet_pt_[genIdx], GenJet_eta_[genIdx] , GenJet_phi_[genIdx], GenJet_mass_[genIdx]);
  // 	if(ljetR.DeltaR(ljetG)<0.2)
  // 	  nljet++;
  //     }//l-jet condition
	
  //   }//found the corresponding genjet 
  // }//jet loop
    
  // if((!hasMu and !hasEle) or (nbjet+nljet) < 4 or nbjet < 2) return true;

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

  for(int muInd = 0; muInd < int(nMuon_); ++muInd){
    int genIdx = int(muGenIdx_[muInd]);
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

	  eta = muEta_[muInd];
	  et = mujetR.Et();
	  GetHistoBin(hMuEtaETBin, eta, et, binEta, binET);
	    
	  double etResoPercent = 100.*(et - mujetG.Et())/mujetG.Et();
	  double etaReso = mujetR.Eta() - mujetG.Eta();
	  double phiReso = mujetR.Phi() - mujetG.Phi();

	  hMuETReso[binEta-1][binET-1]->Fill(etResoPercent);
	  hMuEtaReso[binEta-1][binET-1]->Fill(etaReso);
	  hMuPhiReso[binEta-1][binET-1]->Fill(phiReso);
	}
      }
    }
  }//muon loop
  
  for(int eleInd = 0; eleInd < int(nEle_); ++eleInd){
    int genIdx = int(eleGenIdx_[eleInd]);
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
	  
	  eta = eleEta_[eleInd];
	  et = elejetR.Et();
	  GetHistoBin(hEleEtaETBin, eta, et, binEta, binET);
	  
	  double etResoPercent = 100.*(et - elejetG.Et())/elejetG.Et();
	  double etaReso = elejetR.Eta() - elejetG.Eta();
	  double phiReso = elejetR.Phi() - elejetG.Phi();

	  hEleETReso[binEta-1][binET-1]->Fill(etResoPercent);
	  hEleEtaReso[binEta-1][binET-1]->Fill(etaReso);
	  hElePhiReso[binEta-1][binET-1]->Fill(phiReso);

	}
	  
      }
    }
  }//electron loop
  
  // printf("MET Rec:(%5.2f, %5.2f) Gen:(%5.2f, %5.2f), Reso : (%5.2f,%5.2f)\n",MET_pt_,MET_phi_,GenMET_pt_,GenMET_phi_, 
  // 	   100.*abs(MET_pt_-GenMET_pt_)/MET_pt_, 100.*abs(MET_phi_-GenMET_phi_)/MET_phi_);
  
  metR.SetPtEtaPhiM(MET_pt_, 0.0, MET_phi_, 0.0);
  metG.SetPtEtaPhiM(GenMET_pt_, 0.0, GenMET_phi_, 0.0);
  
  et = metR.Et();
  binET = GetHistoBin(hMETETBin, et);
  double etResoPercent = 100.*(et - metG.Et())/metG.Et();
  double phiReso = metR.Phi() - metG.Phi();
  hMETETReso[binET-1]->Fill(etResoPercent);
  hMETPhiReso[binET-1]->Fill(phiReso);
  
  for(int jetInd = 0; jetInd < int(nJet_); ++jetInd){
    int genIdx = int(jetGenJetIdx_[jetInd]);
    if ( (genIdx>-1) && (genIdx < int(nGenJet_))){
      unsigned int imc = genIdx ;
      // printf("\tJet : Rec:(%2d, %5.2f, %5.2f, %5.2f, %5.2f), Gen:(%2d, %5.2f, %5.2f, %5.2f, %5.2f)\n", 
      //        jetPartFlvr_[jetInd],jetPt_[jetInd], jetEta_[jetInd] , jetPhi_[jetInd], jetMass_[jetInd],  
      //        GenJet_partonFlavour_[genIdx],GenJet_pt_[genIdx], GenJet_eta_[genIdx] , GenJet_phi_[genIdx], GenJet_mass_[genIdx]);
      if(jetPartFlvr_[jetInd]==GenJet_partonFlavour_[genIdx] and abs(jetPartFlvr_[jetInd])==5){
	bjetR.SetPtEtaPhiM(jetPt_[jetInd], jetEta_[jetInd] , jetPhi_[jetInd], jetMass_[jetInd]);
	bjetG.SetPtEtaPhiM(GenJet_pt_[genIdx], GenJet_eta_[genIdx] , GenJet_phi_[genIdx], GenJet_mass_[genIdx]);
	eta = jetEta_[jetInd];
	et = bjetR.Et();
	GetHistoBin(hJetEtaETBin, eta, et, binEta, binET);
	double etResoPercent = 100.*(et - bjetG.Et())/bjetG.Et();
	double etaReso = bjetR.Eta() - bjetG.Eta();
	double phiReso = bjetR.Phi() - bjetG.Phi();
	if(bjetR.DeltaR(bjetG)<0.2){
	  hBJetETReso[binEta-1][binET-1]->Fill(etResoPercent);
	  hBJetEtaReso[binEta-1][binET-1]->Fill(etaReso);
	  hBJetPhiReso[binEta-1][binET-1]->Fill(phiReso);
	}
	//hBJetETDelRReso[binET-1]->Fill(bjetR.DeltaR(bjetG));
      }//b-jet condition
      
      if(jetPartFlvr_[jetInd]==GenJet_partonFlavour_[genIdx] and ((abs(jetPartFlvr_[jetInd])>=1 and abs(jetPartFlvr_[jetInd])<=4) or abs(jetPartFlvr_[jetInd])==21) ){ //u,d,s,c,g
	ljetR.SetPtEtaPhiM(jetPt_[jetInd], jetEta_[jetInd] , jetPhi_[jetInd], jetMass_[jetInd]);
	ljetG.SetPtEtaPhiM(GenJet_pt_[genIdx], GenJet_eta_[genIdx] , GenJet_phi_[genIdx], GenJet_mass_[genIdx]);
	eta = jetEta_[jetInd];
	et = ljetR.Et();
	GetHistoBin(hJetEtaETBin, eta, et, binEta, binET);
	double etResoPercent = 100.*(et - ljetG.Et())/ljetG.Et();
	double etaReso = ljetR.Eta() - ljetG.Eta();
	double phiReso = ljetR.Phi() - ljetG.Phi();
	if(ljetR.DeltaR(ljetG)<0.2){
	  hLJetETReso[binEta-1][binET-1]->Fill(etResoPercent);
	  hLJetEtaReso[binEta-1][binET-1]->Fill(etaReso);
	  hLJetPhiReso[binEta-1][binET-1]->Fill(phiReso);
	}
      }//l-jet condition
	
    }//found the corresponding genjet 
  }//jet loop

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
