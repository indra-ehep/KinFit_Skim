/**********************************************************************
 Created on : 14/07/2021
 Purpose    : Analyse the Skim tree.
              (format adapted from h1analysis)
 Author     : Indranil Das, Visiting Fellow, TIFR
 Email      : indranil.das@cern.ch | indra.ehep@gmail.com
**********************************************************************/

#ifndef ProcessSkim_h
#define ProcessSkim_h

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

class  TH1F;
class  TH1D;
class  TH2D;

class ProcessSkim : public TSelector {
   public :
   
   //File operation pointers
   ////////////////////////////////////////////////////////
   TFile            *fFile[3];
   TDirectory       **fFileDir;
   TProofOutputFile *fProofFile[3]; // For optimized merging of the ntuple

   //Declaration of histograms
   ////////////////////////////////////////////////////////   
   /* Int_t          fNTestHist;// */
   /* TH2D           **hCheck;// */
   TH2D *h2_BTagEff_Denom_b ; 
   TH2D *h2_BTagEff_Denom_c ; 
   TH2D *h2_BTagEff_Denom_udsg ; 
   //Loose BTag efficiency 2D histos          
   TH2D *h2_BTagEff_Num_bL ; 
   TH2D *h2_BTagEff_Num_cL ; 
   TH2D *h2_BTagEff_Num_udsgL ; 
   //Medium BTag efficiency 2D histos          
   TH2D *h2_BTagEff_Num_bM ; 
   TH2D *h2_BTagEff_Num_cM ; 
   TH2D *h2_BTagEff_Num_udsgM ; 
   //Tight BTag efficiency 2D histos          
   TH2D *h2_BTagEff_Num_bT ; 
   TH2D *h2_BTagEff_Num_cT ; 
   TH2D *h2_BTagEff_Num_udsgT ; 
   ////////////////////////////////////////////////////////

   Long64_t        fProcessed;//!
   TTree          *fChain;//!    //pointer to the analyzed TTree or TChain
   
   //Declaration of leaves types
   ////////////////////////////////////////////////////////
   UInt_t          nJet_;
   Float_t         jetPt_[200];
   Float_t         jetEta_[200];
   Float_t         jetPhi_[200];
   Float_t         jetMass_[200];
   // Float_t         jetRawFactor_[200];
   // Int_t           jetID_[200];
   // Float_t         jetArea_[200];
   // Float_t         jetBtagCMVA_[200];
   Float_t         jetBtagCSVV2_[200];
   Float_t         jetBtagDeepB_[200];
   Float_t         jetBtagDeepC_[200];
   // Float_t         jetBtagDeepFlavB_[200];
   // Float_t         jetchEmEF_[200];
   // Float_t         jetneEmEF_[200];
   Int_t           jetPartFlvr_[200];
   Int_t           jetHadFlvr_[200];
   Int_t           jetGenJetIdx_[200];
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
   ////////////////////////////////////////////////////////

   ProcessSkim(TTree *tree=0);
   virtual ~ProcessSkim() ;
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

   ClassDef(ProcessSkim,2);

};

#endif



//_____________________________________________________________________
ProcessSkim::ProcessSkim(TTree * /*tree*/)
{
  // Constructor

   Reset();
}
//_____________________________________________________________________
void ProcessSkim::Reset()
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
ProcessSkim::~ProcessSkim()
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
void ProcessSkim::Init(TTree *tree)
{
  //   Set branch addresses

  Info("Init","tree: %p", tree);

  if (tree == 0) return;
  fChain    = tree;

  fChain->SetCacheSize(100*1024*1024);
  fChain->SetBranchStatus("*",0);

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
  
  fChain->SetBranchStatus("Jet_btagCSVV2",1);
  fChain->SetBranchAddress("Jet_btagCSVV2", &jetBtagCSVV2_);
  
  fChain->SetBranchStatus("Jet_btagDeepB",1);
  fChain->SetBranchAddress("Jet_btagDeepB", &jetBtagDeepB_);
    
  fChain->SetBranchStatus("Jet_partonFlavour",1);
  fChain->SetBranchAddress("Jet_partonFlavour", &jetPartFlvr_);
  
  fChain->SetBranchStatus("Jet_hadronFlavour",1);
  fChain->SetBranchAddress("Jet_hadronFlavour", &jetHadFlvr_);

  fChain->SetBranchStatus("Jet_genJetIdx",1);
  fChain->SetBranchAddress("Jet_genJetIdx", &jetGenJetIdx_);

}

//_____________________________________________________________________
Bool_t ProcessSkim::Notify()
{
//   called when loading a new file
//   get branch pointers
  
  string fname(fChain->GetCurrentFile()->GetName());
  fname = fname.substr(fname.find_last_of("/")+1,fname.size());
  fname = fname.substr(0,fname.find("_Skim"));
  fSampleType = fname;
  
  Info("Notify","processing sample %s and file: %s",fSampleType.Data(), fChain->GetCurrentFile()->GetName());  
  
  return kTRUE;
}

