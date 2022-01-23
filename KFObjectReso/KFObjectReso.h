/**********************************************************************
 Created on : 14/07/2021
 Purpose    : Analyse the Skim tree.
              (format adapted from h1analysis)
 Author     : Indranil Das, Visiting Fellow, TIFR
 Email      : indranil.das@cern.ch | indra.ehep@gmail.com
**********************************************************************/

#ifndef KFObjectReso_h
#define KFObjectReso_h

#include <TROOT.h>
#include <TChain.h>
#include <TEntryList.h>
#include <TFile.h>
#include <TProofOutputFile.h>
#include <TSelector.h>
#include <TGraphAsymmErrors.h>
#include <TH2.h>
#include <vector>
#include <iostream>
#include <TLorentzVector.h>

class  TH1F;
class  TH1D;
class  TH2D;

class KFObjectReso : public TSelector {
   public :
   
   //File operation pointers
   ////////////////////////////////////////////////////////
   TFile            *fFile[3];
   TDirectory       **fFileDir;
   TProofOutputFile *fProofFile[3]; // For optimized merging of the ntuple

   //Declaration of histograms
   ////////////////////////////////////////////////////////   
   TH1F ***hBJetETReso, ***hLJetETReso, ***hBJetEtaReso, ***hLJetEtaReso, ***hBJetPhiReso, ***hLJetPhiReso;
   TH2F *hJetEtaETBin ;
   
   TH1F ***hMuETReso, ***hMuEtaReso, ***hMuPhiReso;
   TH2F *hMuEtaETBin ;
   
   TH1F ***hEleETReso, ***hEleEtaReso, ***hElePhiReso;
   TH2F *hEleEtaETBin ;
   
   TH1F **hMETETReso, **hMETPhiReso;
   TH1F *hMETETBin ;
   ////////////////////////////////////////////////////////

   Long64_t        fProcessed;//!
   TTree          *fChain;//!    //pointer to the analyzed TTree or TChain
   
   //Declaration of leaves types
   ////////////////////////////////////////////////////////
   UInt_t    nGenPart_;
   Float_t   GenPart_pt_[300];
   Float_t   GenPart_eta_[300];
   Float_t   GenPart_phi_[300];
   Float_t   GenPart_mass_[300];
   Int_t     GenPart_genPartIdxMother_[300];
   Int_t     GenPart_pdgId_[300];
   Int_t     GenPart_status_[300];
   Int_t     GenPart_statusFlags_[300];
  
   UInt_t    nGenJet_;  
   Float_t   GenJet_pt_[100];
   Float_t   GenJet_eta_[100];
   Float_t   GenJet_phi_[100];
   Float_t   GenJet_mass_[100];
   Int_t   GenJet_partonFlavour_[100];
   Int_t   GenJet_hadronFlavour_[100];
  
   // Electron
   UInt_t          nEle_;
   Float_t         elePt_[20];
   Float_t         eleEta_[20];
   Float_t         elePhi_[20];
   Int_t           eleCharge_[20];
   Float_t         eleMass_[20];
   Int_t           eleGenIdx_[20];
  
   // Muon
   UInt_t          nMuon_;
   Float_t         muPt_[15];
   Float_t         muEta_[15];
   Float_t         muPhi_[15];
   Int_t           muCharge_[15];
   Float_t         muMass_[15];
   Int_t           muGenIdx_[15];

   // Jet
   UInt_t          nJet_;
   Float_t         jetPt_[200];
   Float_t         jetEta_[200];
   Float_t         jetPhi_[200];
   Float_t         jetMass_[200];
   Int_t           jetHadFlvr_[200];
   Int_t           jetPartFlvr_[200];
   Int_t           jetGenJetIdx_[200];

   //MET
   Float_t  MET_pt_;
   Float_t  MET_phi_;

   Float_t  GenMET_pt_;
   Float_t  GenMET_phi_;
   ////////////////////////////////////////////////////////


   ////////////////////////////////////////////////////////
   //Assorted
   TString fSample;
   TString fSampleDir;
   TString fSampleType;
   TString fMode;
   Int_t fYear;
   bool isData ;
   TString fBasePath ;
   bool isPreVFP, isPostVFP;
   Int_t nMuEtaBins = 25;
   Int_t nEleEtaBins = 24;
   Int_t nJetEtaBins = 26;
   Int_t nETBins = 19;
   TLorentzVector mujetR, mujetG; 
   TLorentzVector elejetR, elejetG; 
   TLorentzVector metR, metG; 
   TLorentzVector bjetR, bjetG; 
   TLorentzVector ljetR, ljetG; 
   float eta, et ;
   int binEta, binET;
   ////////////////////////////////////////////////////////

   KFObjectReso(TTree *tree=0);
   virtual ~KFObjectReso() ;
   void    Reset();

   int     Version() const {return 1;}
   void    Begin(TTree *tree);
   void    SlaveBegin(TTree *tree);
   void    Init(TTree *tree);
   Bool_t  Notify();
   Bool_t  Process(Long64_t entry);
   void    SetOption(const char *option) { fOption = option; }
   void    SetObject(TObject *obj) { fObject = obj; }
   void    SetInputList(TList *input) {fInput = input;}
   TList  *GetOutputList() const { return fOutput; }
   void    SlaveTerminate();
   void    Terminate();

   void    GetArguments();
   Int_t   CreateHistoArrays();
   
   bool GetHistoBin(TH2F *, float, float, int&, int&);
   int GetHistoBin(TH1F *h, float et);

   ClassDef(KFObjectReso,2);

};

#endif



//_____________________________________________________________________
KFObjectReso::KFObjectReso(TTree * /*tree*/)
{
  // Constructor

   Reset();
}
//_____________________________________________________________________
void KFObjectReso::Reset()
{
   // Reset the data members to theit initial value

   fFileDir		= 0;
   fFile[0]		= 0;
   fProofFile[0]	= 0;
   fFile[1]		= 0;
   fProofFile[1]	= 0;
   fFile[2]		= 0;
   fProofFile[2]	= 0;
   
   fChain		= 0;
   fProcessed		= 0;

   fSample		= "";
   fSampleDir		= "";
   fSampleType		= "";
   fMode		= "";
   fYear		= 2016;
   fBasePath		= "";   
   isData		= false;

}
//_____________________________________________________________________
KFObjectReso::~KFObjectReso()
{
  if (fFile[0]) {
    SafeDelete(fFile[0]);
  }
  if (fFile[1]) {
    SafeDelete(fFile[1]);
  }
  if (fFile[2]) {
    SafeDelete(fFile[1]);
  }
}
//_____________________________________________________________________
void KFObjectReso::Init(TTree *tree)
{
  //   Set branch addresses

  Info("Init","tree: %p", tree);

  if (tree == 0) return;
  fChain    = tree;

  fChain->SetCacheSize(100*1024*1024);
  fChain->SetBranchStatus("*",0);

  ///////////////////////////////////////////////////////////////////////////
  fChain->SetBranchStatus("nGenPart",1);
  fChain->SetBranchAddress("nGenPart", &nGenPart_);
	
  fChain->SetBranchStatus("GenPart_pt",1);
  fChain->SetBranchAddress("GenPart_pt", &GenPart_pt_);
	
  fChain->SetBranchStatus("GenPart_eta",1);
  fChain->SetBranchAddress("GenPart_eta", &GenPart_eta_);
	
  fChain->SetBranchStatus("GenPart_phi",1);
  fChain->SetBranchAddress("GenPart_phi", &GenPart_phi_);

  fChain->SetBranchStatus("GenPart_mass",1);
  fChain->SetBranchAddress("GenPart_mass", &GenPart_mass_);

  fChain->SetBranchStatus("GenPart_genPartIdxMother",1);
  fChain->SetBranchAddress("GenPart_genPartIdxMother", &GenPart_genPartIdxMother_);
    
  fChain->SetBranchStatus("GenPart_pdgId",1);
  fChain->SetBranchAddress("GenPart_pdgId", &GenPart_pdgId_);

  fChain->SetBranchAddress("GenPart_status", &GenPart_status_);
  fChain->SetBranchAddress("GenPart_statusFlags", &GenPart_statusFlags_);
  /////////////////////////////////////////////////////////////////////////////
  fChain->SetBranchStatus("nGenJet",1);
  fChain->SetBranchAddress("nGenJet", &nGenJet_);
	
  fChain->SetBranchStatus("GenJet_pt",1);
  fChain->SetBranchAddress("GenJet_pt", &GenJet_pt_);

  fChain->SetBranchStatus("GenJet_eta",1);
  fChain->SetBranchAddress("GenJet_eta", &GenJet_eta_);

  fChain->SetBranchStatus("GenJet_phi",1);
  fChain->SetBranchAddress("GenJet_phi", &GenJet_phi_);
 
  fChain->SetBranchStatus("GenJet_mass",1);
  fChain->SetBranchAddress("GenJet_mass", &GenJet_mass_);

  fChain->SetBranchStatus("GenJet_partonFlavour",1);
  fChain->SetBranchAddress("GenJet_partonFlavour", &GenJet_partonFlavour_);
	
  fChain->SetBranchStatus("GenJet_hadronFlavour",1);
  fChain->SetBranchAddress("GenJet_hadronFlavour", &GenJet_hadronFlavour_);
  /////////////////////////////////////////////////////////////////////////////
  fChain->SetBranchStatus("nElectron",1);
  fChain->SetBranchAddress("nElectron", &nEle_);

  fChain->SetBranchStatus("Electron_pt",1);
  fChain->SetBranchAddress("Electron_pt", &elePt_);

  fChain->SetBranchStatus("Electron_eta",1);
  fChain->SetBranchAddress("Electron_eta", &eleEta_);

  fChain->SetBranchStatus("Electron_phi",1);
  fChain->SetBranchAddress("Electron_phi", &elePhi_);

  fChain->SetBranchStatus("Electron_charge",1);
  fChain->SetBranchAddress("Electron_charge", &eleCharge_);	

  fChain->SetBranchStatus("Electron_mass",1);
  fChain->SetBranchAddress("Electron_mass", &eleMass_);

  fChain->SetBranchStatus("Electron_mass",1);
  fChain->SetBranchAddress("Electron_mass", &eleMass_);

  fChain->SetBranchStatus("Electron_genPartIdx",1);
  fChain->SetBranchAddress("Electron_genPartIdx", &eleGenIdx_);
  ///////////////////////////////////////////////////////////////////////////
  fChain->SetBranchStatus("nMuon",1);
  fChain->SetBranchAddress("nMuon", &nMuon_);
	
  fChain->SetBranchStatus("Muon_pt",1);
  fChain->SetBranchAddress("Muon_pt", &muPt_);

  fChain->SetBranchStatus("Muon_eta",1);
  fChain->SetBranchAddress("Muon_eta", &muEta_);

  fChain->SetBranchStatus("Muon_phi",1);
  fChain->SetBranchAddress("Muon_phi", &muPhi_);

  fChain->SetBranchStatus("Muon_charge",1);
  fChain->SetBranchAddress("Muon_charge", &muCharge_);

  fChain->SetBranchStatus("Muon_mass",1);
  fChain->SetBranchAddress("Muon_mass", &muMass_);

  fChain->SetBranchStatus("Muon_genPartIdx",1);
  fChain->SetBranchAddress("Muon_genPartIdx", &muGenIdx_);
  ///////////////////////////////////////////////////////////////////////////
  fChain->SetBranchStatus("nJet",1);
  fChain->SetBranchAddress("nJet", &nJet_);
 
  fChain->SetBranchStatus("Jet_pt",1);
  fChain->SetBranchAddress("Jet_pt", &jetPt_);

  fChain->SetBranchStatus("Jet_eta",1);
  fChain->SetBranchAddress("Jet_eta", &jetEta_);
	
  fChain->SetBranchStatus("Jet_phi",1);
  fChain->SetBranchAddress("Jet_phi", &jetPhi_);

  fChain->SetBranchStatus("Jet_mass",1);
  fChain->SetBranchAddress("Jet_mass", &jetMass_);

  fChain->SetBranchStatus("Jet_hadronFlavour",1);
  fChain->SetBranchAddress("Jet_hadronFlavour", &jetHadFlvr_);
  
  fChain->SetBranchStatus("Jet_partonFlavour",1);
  fChain->SetBranchAddress("Jet_partonFlavour", &jetPartFlvr_);
  
  fChain->SetBranchStatus("Jet_genJetIdx",1);
  fChain->SetBranchAddress("Jet_genJetIdx", &jetGenJetIdx_);
  ///////////////////////////////////////////////////////////////////////////

  fChain->SetBranchStatus("MET_pt",1);
  fChain->SetBranchAddress("MET_pt", &MET_pt_);
  
  fChain->SetBranchStatus("MET_phi",1);
  fChain->SetBranchAddress("MET_phi", &MET_phi_);
  
  fChain->SetBranchStatus("GenMET_pt",1);
  fChain->SetBranchAddress("GenMET_pt", &GenMET_pt_);

  fChain->SetBranchStatus("GenMET_phi",1);
  fChain->SetBranchAddress("GenMET_phi", &GenMET_phi_);
  
  ///////////////////////////////////////////////////////////////////////////


}

//_____________________________________________________________________
Bool_t KFObjectReso::Notify()
{
//   called when loading a new file
//   get branch pointers

  isPreVFP = false ; isPostVFP = false ;
  string fname(fChain->GetCurrentFile()->GetName());
  fname = fname.substr(fname.find_last_of("/")+1,fname.size());
  if (fname.find("_preVFP_Skim") != string::npos){
    fname = fname.substr(0,fname.find("_preVFP_Skim"));
    isPreVFP = true;
  }else if (fname.find("_postVFP_Skim") != string::npos){
    fname = fname.substr(0,fname.find("_postVFP_Skim"));
    isPostVFP = true ;
  }else if (fname.find("_Skim") != string::npos)
    fname = fname.substr(0,fname.find("_Skim"));

  fSampleType = fname;
  
  Info("Notify","processing sample %s and file: %s",fSampleType.Data(), fChain->GetCurrentFile()->GetName());  
  
  return kTRUE;
}

