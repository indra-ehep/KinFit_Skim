/**********************************************************************
 Created on : 16/07/2022
 Purpose    : Prepare the histograms from CBA results
 Author     : Indranil Das, Visiting Fellow
 Email      : indranil.das@cern.ch | indra.ehep@gmail.com
**********************************************************************/
#ifndef SkimAna_h
#define SkimAna_h

#include <TROOT.h>
#include <TTree.h>
#include <TChain.h>
#include <TEntryList.h>
#include <TFile.h>
#include <TProofOutputFile.h>
#include <TSelector.h>
#include <TGraphAsymmErrors.h>
#include <TH2.h>
#include <TProfile.h>
#include <TParticlePDG.h>
#include <TDatabasePDG.h>
#include <TRandom3.h>

#include <vector>
#include <iostream>
#include <map>
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <cmath>
#include <stdexcept>

#include "TMath.h"
#include "TLorentzVector.h"

using namespace std;
/////////////////////


class  TH1F;
class  TH1D;
class  TH2D;
class  TH2F;


class KinAna : public TSelector {
public :
   
  //File operation pointers
  ////////////////////////////////////////////////////////
  TFile            *fFile[3];
  TDirectory       **fFileDir;
  TDirectory       **fSelColDir;
  TProofOutputFile *fProofFile[3]; // For optimized merging of the ntuple


  /* //Declaration of leaves types */
  /* //////////////////////////////////////////////////////// */
  Long64_t        fProcessed;//!
  TTree          *fChain;//!    //pointer to the analyzed TTree or TChain
  bool           IsDebug;
  int            nCTag;

  ///////////////////////////////////////////////////////
  // Object values
  ///////////////////////////////////////////////////////
  Double_t  chi2;
  Float_t   jetChadPt;
  Float_t   jetChadEta;
  Float_t   jetChadPhi;
  Float_t   jetChadEn;
  Float_t   jetShadPt;
  Float_t   jetShadEta;
  Float_t   jetShadPhi;
  Float_t   jetShadEn;
  Float_t   metPx;
  Float_t   metPy;
  Float_t   metPz;
  Float_t   lepPt;
  Float_t   lepEta;
  Float_t   lepPhi;
  Float_t   lepEn;
  Float_t   jetBhadPt;
  Float_t   jetBhadEta;
  Float_t   jetBhadPhi;
  Float_t   jetBhadEn;
  Float_t   jetBlepPt;
  Float_t   jetBlepEta;
  Float_t   jetBlepPhi;
  Float_t   jetBlepEn;
  Int_t     nJet;
  Int_t     nBJet;
  
  TLorentzVector leptonAF, neutrinoAF, bjlepAF, bjhadAF, cjhadAF, sjhadAF;
  ///////////////////////////////////////////////////////
  // Type of KF Event
  ///////////////////////////////////////////////////////
  Bool_t singleMu;
  Bool_t singleEle;
  
  Bool_t muonIsoCut;  
  Bool_t muonNonIsoCut;
  Bool_t eleIsoCut;
  Bool_t eleNonIsoCut;
  
  Bool_t isLowMET;
  
  Bool_t hasKFMu;
  Bool_t hasKFEle;
  
  Bool_t isKFValid;
  Bool_t isCTagged;

  ///////////////////////////////////////////////////////
  // Weight/SF
  ///////////////////////////////////////////////////////
  Double_t weight, mjjKF;
  Double_t wt_before, wt_after, wt_ratio;
  
  Double_t _sampleWeight;
  
  Double_t _PUWeight;
  Double_t _PUWeight_Up;
  Double_t _PUWeight_Do;
  
  Double_t _prefireWeight;
  Double_t _prefireWeight_Up;
  Double_t _prefireWeight_Do;

  Double_t _muEffWeight;
  Double_t _muEffWeight_Up;
  Double_t _muEffWeight_Do;
  
  Double_t _eleEffWeight;
  Double_t _eleEffWeight_Up;
  Double_t _eleEffWeight_Do;
  
  Double_t _PUJetIDWeight;
  Double_t _PUJetIDWeight_Up;
  Double_t _PUJetIDWeight_Do;

  // CShapeCalib EOY
  Double_t _bcTagWeight;
  Double_t _bcTagWeight_stat_Up, _bcTagWeight_stat_Do, _bcTagWeight_pu_Up, _bcTagWeight_pu_Do; 
  Double_t _bcTagWeight_eleid_Up, _bcTagWeight_eleid_Do, _bcTagWeight_muid_Up, _bcTagWeight_muid_Do; 
  Double_t _bcTagWeight_lhemuf_Up, _bcTagWeight_lhemuf_Do, _bcTagWeight_lhemur_Up, _bcTagWeight_lhemur_Do; 
  Double_t _bcTagWeight_isr_Up, _bcTagWeight_isr_Do, _bcTagWeight_fsr_Up, _bcTagWeight_fsr_Do; 
  Double_t _bcTagWeight_xdy_Up, _bcTagWeight_xdy_Do, _bcTagWeight_xst_Up, _bcTagWeight_xst_Do; 
  Double_t _bcTagWeight_xwj_Up, _bcTagWeight_xwj_Do, _bcTagWeight_xtt_Up,  _bcTagWeight_xtt_Do; 
  Double_t _bcTagWeight_jes_Up, _bcTagWeight_jes_Do, _bcTagWeight_jer_Up, _bcTagWeight_jer_Do; 
  Double_t _bcTagWeight_bfrag_Up, _bcTagWeight_bfrag_Do; 
  
   /* // CShapeCalib UL */
   /* Double_t _bcTagWeight_stat_Up, _bcTagWeight_stat_Do, _bcTagWeight_pu_Up, _bcTagWeight_pu_Do;  */
   Double_t _bcTagWeight_intp_Up, _bcTagWeight_intp_Do, _bcTagWeight_extp_Up, _bcTagWeight_extp_Do;
   /* Double_t _bcTagWeight_lhemuf_Up, _bcTagWeight_lhemuf_Do, _bcTagWeight_lhemur_Up, _bcTagWeight_lhemur_Do;  */
   /* Double_t _bcTagWeight_isr_Up, _bcTagWeight_isr_Do, _bcTagWeight_fsr_Up, _bcTagWeight_fsr_Do;  */
   Double_t _bcTagWeight_xdyb_Up, _bcTagWeight_xdyb_Do, _bcTagWeight_xdyc_Up, _bcTagWeight_xdyc_Do;
   Double_t _bcTagWeight_xwjc_Up, _bcTagWeight_xwjc_Do;
   /* Double_t _bcTagWeight_jes_Up, _bcTagWeight_jes_Do, _bcTagWeight_jer_Up, _bcTagWeight_jer_Do;  */

   //Theory weights
  Float_t _q2weight_Up, _q2weight_Do;
  Float_t _muRweight_Up, _muRweight_Do ;
  Float_t _muFweight_Up, _muFweight_Do ;
  Float_t _pdfweight_Up, _pdfweight_Do, _pdfuncer;
  Float_t _ISRweight_Up, _ISRweight_Do;
  Float_t _FSRweight_Up, _FSRweight_Do;
  

  ///////////////////////////////////////////////////////
  // BCDisc and related values
  ///////////////////////////////////////////////////////
  Int_t count_cJetsIncL, count_cJetsIncM, count_cJetsIncT;
  Double_t cjhadCvsBdisc, sjhadCvsBdisc ;
  Double_t cjhadCvsLdisc, sjhadCvsLdisc ;

  Bool_t useDeepCSVbTag;
  Float_t btag_cut_DeepCSVa, btag_cut_DeepCSVb, btag_cut_DeepCSV; //DeepCSV
  Float_t btag_cuta, btag_cutb, btag_cut; //DeepJet
  Float_t ctag_CvsL_L_cuta, ctag_CvsB_L_cuta, ctag_CvsL_M_cuta, ctag_CvsB_M_cuta, ctag_CvsL_T_cuta, ctag_CvsB_T_cuta;
  Float_t ctag_CvsL_L_cutb, ctag_CvsB_L_cutb, ctag_CvsL_M_cutb, ctag_CvsB_M_cutb, ctag_CvsL_T_cutb, ctag_CvsB_T_cutb;
  Float_t ctag_CvsL_L_cut, ctag_CvsB_L_cut, ctag_CvsL_M_cut, ctag_CvsB_M_cut, ctag_CvsL_T_cut, ctag_CvsB_T_cut; 


   ////////////////////////////////////////////////////////
   //Assorted
   TString fSample;
   TString fFileName;
   TString fSampleDir;
   TString fSampleType;
    TString fMode;
   Int_t fYear;
   Int_t fIndex;
   Int_t fTotal;
   bool isData ;
   TString fBasePath ;
   TString fSyst ;
   vector<TString> fSystList;
   TString fRefFile, fRefPath;
   TFile *fRefF;
   Bool_t isPreVFP, isPostVFP;
   ////////////////////////////////////////////////////////

   ////////////////////////////////////////////////////////
   //Systematics
   enum SystType {kBase,
   		  kPUDown, kPUUp, kMuEffDown, kMuEffUp, kEleEffDown, kEleEffUp,
   		  kJECUp, kJECDown, kJERUp, kJERDown, kBTagbDown, kBTagbUp,
   		  kBTaglDown, kBTaglUp, kPdfDown, kPdfUp, kQ2Down, kQ2Up,
   		  kFsrDown, kFsrUp, kIsrDown, kIsrUp, kPreFireUp, kPreFireDown,
		  kIso20, kMETUp, kMETDown,
		  kCP5Up, kCP5Down, khDampUp, khDampDown, kmTopUp, kmTopDown
   };
   enum SlType { kSlEle, kSlMu, kSlTau, kSlcs, kSlud, kSlus,  kSldc};
   

   int puvar012_g ;		// 0:down, 1:norm, 2:up
   int mueffvar012_g ;		// 0:down, 1:norm, 2:up
   int eleeffvar012_g ;		// 0:down, 1:norm, 2:up
   int jecvar012_g ;		// 0:down, 1:norm, 2:up
   int jervar012_g ;		// 0:down, 1:norm, 2:up
   int btagbvar012_g ;		// 0:down, 1:norm, 2:up
   int btaglvar012_g ;		// 0:down, 1:norm, 2:up
   int pdfvar012_g ;		// 0:down, 1:norm, 2:up
   int q2var012_g ;		// 0:down, 1:norm, 2:up
   int fsrvar012_g ;		// 0:down, 1:norm, 2:up
   int isrvar012_g ;		// 0:down, 1:norm, 2:up
   int prefirevar012_g ;       	// 0:down, 1:norm, 2:up
   /* int musmear012_g ;	// 0:down, 1:norm, 2: up */
   /* int elesmear012_g ;	// 0:down, 1:norm, 2: up */
   SystType systType;
   SlType slType;

   // input files
   int nFiles;
   char **fileNames = 0x0;
   
  string PUJetIDSystType ;
  string btagSystType ;
  string ctagSystType;
  string bctagSystType ;
  
   ////////////////////////////////////////////////////////
   // Histogram for checking
   int fNSyst ;
   int fNDDReg ; 
   int fNBCFHists ;
   int fNCFHists ; 
   TH1D           **hCutFlow;//
   int fNBWtHists ; 
   int fNWtHists;
   TH1D           **histWt;//
   int fNBObHists ; 
   int fNObHists ;
   TH1D           **histObs;//
   int fNBSelCols;
   int fNBSelColHists;
   int fNSelColHists;
   int fNBSelColProfiles;
   int fNSelColProfiles;
   TH1D           **hControl;//
   TProfile       **pControl;//
  ////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////
   
   
   KinAna(TTree *tree=0);
   //KinAna();
   
   virtual ~KinAna() ;

   void    Reset();

   int     Version() const {return 1;}
   void    Begin(TTree *tree);
   void    SlaveBegin(TTree *tree);
   void    Init(TTree *tree);
   // void    InitOutBranches();
   // void    InitBjetOutBranches();
   Bool_t  Notify();
   Bool_t  Process(Long64_t entry);
   void    SetOption(const char *option) { fOption = option; }
   void    SetObject(TObject *obj) { fObject = obj; }
   void    SetInputList(TList *input) {fInput = input;}
   TList  *GetOutputList() const { return fOutput; }
   void    SlaveTerminate();
   void    Terminate();

   void    SetRefFile(const char *reffile) { fRefFile = reffile; }
   void    GetArguments();
   void    SelectSyst();
   void    SetTrio();
   void    Clean(void); //clear vector and arrays while read each event

   Int_t   CreateHistoArrays();
   
   
   // //// Fill the main physics object histograms 
   // bool    FillBTagObs();
   bool    FillKFCFObs();
   bool    FillCTagObs();   

  // /// These are called by above functions for cutflow and physics object filling functions
  bool    FillCFHists(TList *list, string hist_extn, bool isMu, double value, double wt, double wt_nobtagwt);
  bool    FillKFHists(TList *list, string hist_extn, bool isMu, double wt, double wt_nobtagwt);
  bool    FillCTHists(TList *list, string hist_extn, bool isMu, double wt,
		       int count_cJetsIncL, int count_cJetsIncM, int count_cJetsIncT, 
		       bool isIncL, bool isIncM, bool isIncT,
		       double ctagLwt, double ctagMwt, double ctagTwt);
  
   
   // /// Calculate the combine wt
   bool    GetCombinedWt(TString systname, double& combined_muwt, double& combined_muwt_nobtagwt, double& combined_elewt, double& combined_elewt_nobtagwt);
   bool    GetCTagWt(char CType, TString systname, double& ctagwt);
  bool    GetWtRatio(TString systname, TString DDzone, string hist_extn);
   // /// Fill the control histograms
   // bool    FillKinFitControlHists();
   // bool    FillCTagControlHists();
   void  FillWtHists(void);
   bool    ExecSerial(const char* infile);
   
   
   //ClassDef(KinAna,2);

};

#endif

//_____________________________________________________________________
KinAna::KinAna(TTree * /*tree*/)
{
  // Constructor

   Reset();
}
//_____________________________________________________________________
void KinAna::Reset()
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
   //outputTree           = 0;
   IsDebug              = false;

   fSample		= "";
   fFileName		= "";
   fSampleDir		= "";
   fSampleType		= "";
   fMode		= "";
   fYear		= 2016;
   fBasePath		= "";   
   fSyst		= "";   
   isData		= false;
}
//_____________________________________________________________________
KinAna::~KinAna()
{
  if (fFile[0]) {
    SafeDelete(fFile[0]);
  }
  if (fFile[1]) {
    SafeDelete(fFile[1]);
  }
  if (fFile[2]) {
    SafeDelete(fFile[2]);
  }
}
//_____________________________________________________________________
void KinAna::Init(TTree *tree)
{
  //   Set branch addresses
  
  //tree = event->chain ;
  Info("Init","tree: %p", tree);
  
  if (tree == 0) return;
  
  // //ESetBranchAddressStatus brAddrStatus;
  // Int_t brAddrStatus;
  
  // tree->SetCacheSize(100*1024*1024);
  // tree->SetBranchStatus("*",0);
  
  // tree->SetBranchStatus("PV_ndof",1);
  // tree->SetBranchAddress("PV_ndof", &(event->pvNDOF_));
  
  //   tree->SetBranchStatus("L1PreFiringWeight_Nom",1);
  //   brAddrStatus = tree->SetBranchAddress("L1PreFiringWeight_Nom", &(event->L1PreFiringWeight_Nom_));
  //   if(brAddrStatus == TTree::kMissingBranch || brAddrStatus == TTree::kInternalError){
  //     event->L1PreFiringWeight_Nom_ =  1.0 ;
  //     Info("Init", "Setting event->L1PreFiringWeight_Nom_ =  1.0");
  //   }

  tree->SetCacheSize(100*1024*1024);
  tree->SetBranchStatus("*",0);

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////
  tree->SetBranchStatus("chi2",1);		   tree->SetBranchAddress("chi2", &chi2);
  tree->SetBranchStatus("jetChadPt",1);		   tree->SetBranchAddress("jetChadPt", &jetChadPt);
  tree->SetBranchStatus("jetChadEta",1);	   tree->SetBranchAddress("jetChadEta", &jetChadEta);
  tree->SetBranchStatus("jetChadPhi",1);	   tree->SetBranchAddress("jetChadPhi", &jetChadPhi);
  tree->SetBranchStatus("jetChadEnergy",1);	   tree->SetBranchAddress("jetChadEnergy", &jetChadEn);
  tree->SetBranchStatus("jetShadPt",1);		   tree->SetBranchAddress("jetShadPt", &jetShadPt);
  tree->SetBranchStatus("jetShadEta",1);	   tree->SetBranchAddress("jetShadEta", &jetShadEta);
  tree->SetBranchStatus("jetShadPhi",1);	   tree->SetBranchAddress("jetShadPhi", &jetShadPhi);
  tree->SetBranchStatus("jetShadEnergy",1);	   tree->SetBranchAddress("jetShadEnergy", &jetShadEn);
  tree->SetBranchStatus("metPx",1);		   tree->SetBranchAddress("metPx", &metPx);
  tree->SetBranchStatus("metPy",1);		   tree->SetBranchAddress("metPy", &metPy);
  tree->SetBranchStatus("metPz",1);		   tree->SetBranchAddress("metPz", &metPz);
  tree->SetBranchStatus("lepPt",1);		   tree->SetBranchAddress("lepPt", &lepPt);
  tree->SetBranchStatus("lepEta",1);		   tree->SetBranchAddress("lepEta", &lepEta);
  tree->SetBranchStatus("lepPhi",1);		   tree->SetBranchAddress("lepPhi", &lepPhi);
  tree->SetBranchStatus("lepEnergy",1);		   tree->SetBranchAddress("lepEnergy", &lepEn);
  tree->SetBranchStatus("jetBhadPt",1);		   tree->SetBranchAddress("jetBhadPt", &jetBhadPt);
  tree->SetBranchStatus("jetBhadEta",1);	   tree->SetBranchAddress("jetBhadEta", &jetBhadEta);
  tree->SetBranchStatus("jetBhadPhi",1);	   tree->SetBranchAddress("jetBhadPhi", &jetBhadPhi);
  tree->SetBranchStatus("jetBhadEnergy",1);	   tree->SetBranchAddress("jetBhadEnergy", &jetBhadEn);
  tree->SetBranchStatus("jetBlepPt",1);		   tree->SetBranchAddress("jetBlepPt", &jetBlepPt);
  tree->SetBranchStatus("jetBlepEta",1);	   tree->SetBranchAddress("jetBlepEta", &jetBlepEta);
  tree->SetBranchStatus("jetBlepPhi",1);	   tree->SetBranchAddress("jetBlepPhi", &jetBlepPhi);
  tree->SetBranchStatus("jetBlepEnergy",1);	   tree->SetBranchAddress("jetBlepEnergy", &jetBlepEn);

  tree->SetBranchStatus("nJet",1);		   tree->SetBranchAddress("nJet", &nJet);
  tree->SetBranchStatus("nBJet",1);		   tree->SetBranchAddress("nBJet", &nBJet);
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  tree->SetBranchStatus("singleMu",1);		   tree->SetBranchAddress("singleMu", &singleMu);
  tree->SetBranchStatus("singleEle",1);		   tree->SetBranchAddress("singleEle", &singleEle);
  tree->SetBranchStatus("muonIsoCut",1);	   tree->SetBranchAddress("muonIsoCut", &muonIsoCut);
  tree->SetBranchStatus("muonNonIsoCut",1);	   tree->SetBranchAddress("muonNonIsoCut", &muonNonIsoCut);
  tree->SetBranchStatus("eleIsoCut",1);		   tree->SetBranchAddress("eleIsoCut", &eleIsoCut);
  tree->SetBranchStatus("eleNonIsoCut",1);	   tree->SetBranchAddress("eleNonIsoCut", &eleNonIsoCut);
  tree->SetBranchStatus("isLowMET",1);		   tree->SetBranchAddress("isLowMET", &isLowMET);
  tree->SetBranchStatus("hasKFMu",1);		   tree->SetBranchAddress("hasKFMu", &hasKFMu);
  tree->SetBranchStatus("hasKFEle",1);		   tree->SetBranchAddress("hasKFEle", &hasKFEle);  
  tree->SetBranchStatus("isKFValid",1);		   tree->SetBranchAddress("isKFValid", &isKFValid);
  tree->SetBranchStatus("isCTagged",1);		   tree->SetBranchAddress("isCTagged", &isCTagged);

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////


  tree->SetBranchStatus("sampleWeight",1);	   tree->SetBranchAddress("sampleWeight", &_sampleWeight);
  
  tree->SetBranchStatus("PUWeight",1);		   tree->SetBranchAddress("PUWeight", &_PUWeight);
  tree->SetBranchStatus("PUWeight_Up",1);	   tree->SetBranchAddress("PUWeight_Up", &_PUWeight_Up);
  tree->SetBranchStatus("PUWeight_Do",1);	   tree->SetBranchAddress("PUWeight_Do", &_PUWeight_Do);
  
  tree->SetBranchStatus("prefireWeight",1);	   tree->SetBranchAddress("prefireWeight", &_prefireWeight);
  tree->SetBranchStatus("prefireWeight_Up",1);	   tree->SetBranchAddress("prefireWeight_Up", &_prefireWeight_Up);
  tree->SetBranchStatus("prefireWeight_Do",1);	   tree->SetBranchAddress("prefireWeight_Do", &_prefireWeight_Do);

  tree->SetBranchStatus("muEffWeight",1);	   tree->SetBranchAddress("muEffWeight", &_muEffWeight);
  tree->SetBranchStatus("muEffWeight_Up",1);	   tree->SetBranchAddress("muEffWeight_Up", &_muEffWeight_Up);
  tree->SetBranchStatus("muEffWeight_Do",1);	   tree->SetBranchAddress("muEffWeight_Do", &_muEffWeight_Do);
  
  tree->SetBranchStatus("eleEffWeight",1);	   tree->SetBranchAddress("eleEffWeight", &_eleEffWeight);
  tree->SetBranchStatus("eleEffWeight_Up",1);	   tree->SetBranchAddress("eleEffWeight_Up", &_eleEffWeight_Up);
  tree->SetBranchStatus("eleEffWeight_Do",1);	   tree->SetBranchAddress("eleEffWeight_Do", &_eleEffWeight_Do);
  
  tree->SetBranchStatus("puJetIDWeight",1);	   tree->SetBranchAddress("puJetIDWeight", &_PUJetIDWeight);
  tree->SetBranchStatus("puJetIDWeight_Up",1);	   tree->SetBranchAddress("puJetIDWeight_Up", &_PUJetIDWeight_Up);
  tree->SetBranchStatus("puJetIDWeight_Do",1);	   tree->SetBranchAddress("puJetIDWeight_Do", &_PUJetIDWeight_Do);

  // CShapeCalib EOY
  tree->SetBranchStatus("bcTagWeight",1);		   tree->SetBranchAddress("bcTagWeight", &_bcTagWeight); 
  tree->SetBranchStatus("bcTagWeight_stat_Up",1);	   tree->SetBranchAddress("bcTagWeight_stat_Up", &_bcTagWeight_stat_Up); 
  tree->SetBranchStatus("bcTagWeight_stat_Do",1);	   tree->SetBranchAddress("bcTagWeight_stat_Do", &_bcTagWeight_stat_Do);
  tree->SetBranchStatus("bcTagWeight_pu_Up",1);		   tree->SetBranchAddress("bcTagWeight_pu_Up", &_bcTagWeight_pu_Up);
  tree->SetBranchStatus("bcTagWeight_pu_Do",1);		   tree->SetBranchAddress("bcTagWeight_pu_Do", &_bcTagWeight_pu_Do);
  if(fYear==2016 or fYear==2018){
    tree->SetBranchStatus("bcTagWeight_eleid_Up",1);	   tree->SetBranchAddress("bcTagWeight_eleid_Up", &_bcTagWeight_eleid_Up); 
    tree->SetBranchStatus("bcTagWeight_eleid_Do",1);	   tree->SetBranchAddress("bcTagWeight_eleid_Do", &_bcTagWeight_eleid_Do);
    tree->SetBranchStatus("bcTagWeight_muid_Up",1);	   tree->SetBranchAddress("bcTagWeight_muid_Up", &_bcTagWeight_muid_Up);
    tree->SetBranchStatus("bcTagWeight_muid_Do",1);	   tree->SetBranchAddress("bcTagWeight_muid_Do", &_bcTagWeight_muid_Do);
  }
  tree->SetBranchStatus("bcTagWeight_lhemuf_Up",1);	   tree->SetBranchAddress("bcTagWeight_lhemuf_Up", &_bcTagWeight_lhemuf_Up); 
  tree->SetBranchStatus("bcTagWeight_lhemuf_Do",1);	   tree->SetBranchAddress("bcTagWeight_lhemuf_Do", &_bcTagWeight_lhemuf_Do);
  tree->SetBranchStatus("bcTagWeight_lhemur_Up",1);	   tree->SetBranchAddress("bcTagWeight_lhemur_Up", &_bcTagWeight_lhemur_Up);
  tree->SetBranchStatus("bcTagWeight_lhemur_Do",1);	   tree->SetBranchAddress("bcTagWeight_lhemur_Do", &_bcTagWeight_lhemur_Do); 
  tree->SetBranchStatus("bcTagWeight_isr_Up",1);	   tree->SetBranchAddress("bcTagWeight_isr_Up", &_bcTagWeight_isr_Up); 
  tree->SetBranchStatus("bcTagWeight_isr_Do",1);	   tree->SetBranchAddress("bcTagWeight_isr_Do", &_bcTagWeight_isr_Do);
  tree->SetBranchStatus("bcTagWeight_fsr_Up",1);	   tree->SetBranchAddress("bcTagWeight_fsr_Up", &_bcTagWeight_fsr_Up);
  tree->SetBranchStatus("bcTagWeight_fsr_Do",1);	   tree->SetBranchAddress("bcTagWeight_fsr_Do", &_bcTagWeight_fsr_Do);
  if(fYear==2016 or fYear==2018) {
    tree->SetBranchStatus("bcTagWeight_xdy_Up",1);	   tree->SetBranchAddress("bcTagWeight_xdy_Up", &_bcTagWeight_xdy_Up); 
    tree->SetBranchStatus("bcTagWeight_xdy_Do",1);	   tree->SetBranchAddress("bcTagWeight_xdy_Do", &_bcTagWeight_xdy_Do);
    tree->SetBranchStatus("bcTagWeight_xst_Up",1);	   tree->SetBranchAddress("bcTagWeight_xst_Up", &_bcTagWeight_xst_Up);
    tree->SetBranchStatus("bcTagWeight_xst_Do",1);	   tree->SetBranchAddress("bcTagWeight_xst_Do", &_bcTagWeight_xst_Do); 
    tree->SetBranchStatus("bcTagWeight_xwj_Up",1);	   tree->SetBranchAddress("bcTagWeight_xwj_Up", &_bcTagWeight_xwj_Up); 
    tree->SetBranchStatus("bcTagWeight_xwj_Do",1);	   tree->SetBranchAddress("bcTagWeight_xwj_Do", &_bcTagWeight_xwj_Do);
    tree->SetBranchStatus("bcTagWeight_xtt_Up",1);	   tree->SetBranchAddress("bcTagWeight_xtt_Up", &_bcTagWeight_xtt_Up);
    tree->SetBranchStatus("bcTagWeight_xtt_Do",1);	   tree->SetBranchAddress("bcTagWeight_xtt_Do", &_bcTagWeight_xtt_Do);
  }
  tree->SetBranchStatus("bcTagWeight_jes_Up",1);	   tree->SetBranchAddress("bcTagWeight_jes_Up", &_bcTagWeight_jes_Up); 
  tree->SetBranchStatus("bcTagWeight_jes_Do",1);	   tree->SetBranchAddress("bcTagWeight_jes_Do", &_bcTagWeight_jes_Do);
  tree->SetBranchStatus("bcTagWeight_jer_Up",1);	   tree->SetBranchAddress("bcTagWeight_jer_Up", &_bcTagWeight_jer_Up);
  tree->SetBranchStatus("bcTagWeight_jer_Do",1);	   tree->SetBranchAddress("bcTagWeight_jer_Do", &_bcTagWeight_jer_Do);
  if(fYear==2016) {
    tree->SetBranchStatus("bcTagWeight_bfrag_Up",1);	   tree->SetBranchAddress("bcTagWeight_bfrag_Up", &_bcTagWeight_bfrag_Up); 
    tree->SetBranchStatus("bcTagWeight_bfrag_Do",1);	   tree->SetBranchAddress("bcTagWeight_bfrag_Do", &_bcTagWeight_bfrag_Do); 
  }
  
   /* // CShapeCalib UL */
   /* tree->SetBranchStatus("bcTagWeight_stat_Up",1);   tree->SetBranchAddress("bcTagWeight_stat_Up", &_bcTagWeight_stat_Up); 
   tree->SetBranchStatus("bcTagWeight_stat_Do",1);   tree->SetBranchAddress("bcTagWeight_stat_Do", &_bcTagWeight_stat_Do);
   tree->SetBranchStatus("bcTagWeight_pu_Up",1);   tree->SetBranchAddress("bcTagWeight_pu_Up", &_bcTagWeight_pu_Up);
    tree->SetBranchStatus("bcTagWeight_pu_Do",1);   tree->SetBranchAddress("bcTagWeight_pu_Do", &_bcTagWeight_pu_Do);  */
  if(fYear==2017){
    tree->SetBranchStatus("bcTagWeight_intp_Up",1);   tree->SetBranchAddress("bcTagWeight_intp_Up", &_bcTagWeight_intp_Up); 
    tree->SetBranchStatus("bcTagWeight_intp_Do",1);   tree->SetBranchAddress("bcTagWeight_intp_Do", &_bcTagWeight_intp_Do);
    tree->SetBranchStatus("bcTagWeight_extp_Up",1);   tree->SetBranchAddress("bcTagWeight_extp_Up", &_bcTagWeight_extp_Up);
    tree->SetBranchStatus("bcTagWeight_extp_Do",1);   tree->SetBranchAddress("bcTagWeight_extp_Do", &_bcTagWeight_extp_Do);
  }
   /* tree->SetBranchStatus("bcTagWeight_lhemuf_Up",1);   tree->SetBranchAddress("bcTagWeight_lhemuf_Up", &_bcTagWeight_lhemuf_Up); 
   tree->SetBranchStatus("bcTagWeight_lhemuf_Do",1);   tree->SetBranchAddress("bcTagWeight_lhemuf_Do", &_bcTagWeight_lhemuf_Do);
   tree->SetBranchStatus("bcTagWeight_lhemur_Up",1);   tree->SetBranchAddress("bcTagWeight_lhemur_Up", &_bcTagWeight_lhemur_Up);
    tree->SetBranchStatus("bcTagWeight_lhemur_Do",1);   tree->SetBranchAddress("bcTagWeight_lhemur_Do", &_bcTagWeight_lhemur_Do);  */
   /* tree->SetBranchStatus("bcTagWeight_isr_Up",1);   tree->SetBranchAddress("bcTagWeight_isr_Up", &_bcTagWeight_isr_Up); 
   tree->SetBranchStatus("bcTagWeight_isr_Do",1);   tree->SetBranchAddress("bcTagWeight_isr_Do", &_bcTagWeight_isr_Do);
   tree->SetBranchStatus("bcTagWeight_fsr_Up",1);   tree->SetBranchAddress("bcTagWeight_fsr_Up", &_bcTagWeight_fsr_Up);
    tree->SetBranchStatus("bcTagWeight_fsr_Do",1);   tree->SetBranchAddress("bcTagWeight_fsr_Do", &_bcTagWeight_fsr_Do);  */
  if(fYear==2017){
    tree->SetBranchStatus("bcTagWeight_xdyb_Up",1);   tree->SetBranchAddress("bcTagWeight_xdyb_Up", &_bcTagWeight_xdyb_Up); 
    tree->SetBranchStatus("bcTagWeight_xdyb_Do",1);   tree->SetBranchAddress("bcTagWeight_xdyb_Do", &_bcTagWeight_xdyb_Do);
    tree->SetBranchStatus("bcTagWeight_xdyc_Up",1);   tree->SetBranchAddress("bcTagWeight_xdyc_Up", &_bcTagWeight_xdyc_Up);
    tree->SetBranchStatus("bcTagWeight_xdyc_Do",1);   tree->SetBranchAddress("bcTagWeight_xdyc_Do", &_bcTagWeight_xdyc_Do);
    tree->SetBranchStatus("bcTagWeight_xwjc_Up",1);   tree->SetBranchAddress("bcTagWeight_xwjc_Up", &_bcTagWeight_xwjc_Up); 
    tree->SetBranchStatus("bcTagWeight_xwjc_Do",1);   tree->SetBranchAddress("bcTagWeight_xwjc_Do", &_bcTagWeight_xwjc_Do);
  }
   /* tree->SetBranchStatus("bcTagWeight_jes_Up",1);   tree->SetBranchAddress("bcTagWeight_jes_Up", &_bcTagWeight_jes_Up); 
   tree->SetBranchStatus("bcTagWeight_jes_Do",1);   tree->SetBranchAddress("bcTagWeight_jes_Do", &_bcTagWeight_jes_Do);
   tree->SetBranchStatus("bcTagWeight_jer_Up",1);   tree->SetBranchAddress("bcTagWeight_jer_Up", &_bcTagWeight_jer_Up);
    tree->SetBranchStatus("bcTagWeight_jer_Do",1);   tree->SetBranchAddress("bcTagWeight_jer_Do", &_bcTagWeight_jer_Do);  */
  // outputTree->Branch("muRweight_Up"		, &_muRweight_Up       	        );
  // outputTree->Branch("muRweight_Do"		, &_muRweight_Do       	        );
  // outputTree->Branch("muFweight_Up"		, &_muFweight_Up       	        );
  // outputTree->Branch("muFweight_Do"		, &_muFweight_Do       	        );
  
  
  //Theory weights
  //if(fYear==2017){
  tree->SetBranchStatus("muRweight_Up",1);	   tree->SetBranchAddress("muRweight_Up", &_muRweight_Up);
  tree->SetBranchStatus("muRweight_Do",1);	   tree->SetBranchAddress("muRweight_Do", &_muRweight_Do);
  tree->SetBranchStatus("muFweight_Up",1);	   tree->SetBranchAddress("muFweight_Up", &_muFweight_Up);
  tree->SetBranchStatus("muFweight_Do",1);	   tree->SetBranchAddress("muFweight_Do", &_muFweight_Do);
  //}
  tree->SetBranchStatus("q2weight_Up",1);	   tree->SetBranchAddress("q2weight_Up", &_q2weight_Up);
  tree->SetBranchStatus("q2weight_Do",1);	   tree->SetBranchAddress("q2weight_Do", &_q2weight_Do);
  tree->SetBranchStatus("pdfweight_Up",1);	   tree->SetBranchAddress("pdfweight_Up", &_pdfweight_Up);
  tree->SetBranchStatus("pdfweight_Do",1);	   tree->SetBranchAddress("pdfweight_Do", &_pdfweight_Do);
  tree->SetBranchStatus("ISRweight_Up",1);	   tree->SetBranchAddress("ISRweight_Up", &_ISRweight_Up);
  tree->SetBranchStatus("ISRweight_Do",1);	   tree->SetBranchAddress("ISRweight_Do", &_ISRweight_Do);
  tree->SetBranchStatus("FSRweight_Up",1);	   tree->SetBranchAddress("FSRweight_Up", &_FSRweight_Up);
  tree->SetBranchStatus("FSRweight_Do",1);	   tree->SetBranchAddress("FSRweight_Do", &_FSRweight_Do);
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // tree->SetBranchStatus("count_cJetsIncL",1);	   tree->SetBranchAddress("count_cJetsIncL", &count_cJetsIncL);
  // tree->SetBranchStatus("count_cJetsIncM",1);	   tree->SetBranchAddress("count_cJetsIncM", &count_cJetsIncM);
  // tree->SetBranchStatus("count_cJetsIncT",1);	   tree->SetBranchAddress("count_cJetsIncT", &count_cJetsIncT);
  
  tree->SetBranchStatus("cjhadCvsBdisc",1);	   tree->SetBranchAddress("cjhadCvsBdisc", &cjhadCvsBdisc);
  tree->SetBranchStatus("cjhadCvsLdisc",1);	   tree->SetBranchAddress("cjhadCvsLdisc", &cjhadCvsLdisc);
  tree->SetBranchStatus("sjhadCvsBdisc",1);	   tree->SetBranchAddress("sjhadCvsBdisc", &sjhadCvsBdisc);
  tree->SetBranchStatus("sjhadCvsLdisc",1);	   tree->SetBranchAddress("sjhadCvsLdisc", &sjhadCvsLdisc);
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////

  fChain    = tree;
  tree->GetEntry(0);  //Important to set the events weights via Notify and ScaleLumi metho
  
}


//_____________________________________________________________________
Bool_t KinAna::Notify()
{
  //   called when loading a new file
  //   get branch pointers
  
  Info("Notify","processing fSampleType %s and file: %s",fSampleType.Data(), fChain->GetCurrentFile()->GetName());  
  

  return kTRUE;
}

