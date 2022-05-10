/**********************************************************************
 Created on : 14/07/2021
 Purpose    : Analyse the Skim tree.
              (format adapted from h1analysis)
 Author     : Indranil Das, Visiting Fellow, TIFR
 Email      : indranil.das@cern.ch | indra.ehep@gmail.com
**********************************************************************/

#ifndef PUJetIDEff_h
#define PUJetIDEff_h

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
#include <TVector3.h>

class  TH1F;
class  TH1D;
class  TH2D;

class PUJetIDEff : public TSelector {
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
   TH2D *h2_PUJetIDEff_Denom ; 
   //Loose PUJetID efficiency 2D histos          
   TH2D *h2_PUJetIDEff_Num_L ; 
   //Medium PUJetID efficiency 2D histos          
   TH2D *h2_PUJetIDEff_Num_M ; 
   //Tight PUJetID efficiency 2D histos          
   TH2D *h2_PUJetIDEff_Num_T ; 
   ////////////////////////////////////////////////////////
   
   Long64_t        fProcessed;//!
   TTree          *fChain;//!    //pointer to the analyzed TTree or TChain
   
   //Declaration of leaves types
   ////////////////////////////////////////////////////////
   UInt_t	nGenPart_;
   Float_t	GenPart_pt_[300];
   Float_t	GenPart_eta_[300];
   Float_t	GenPart_phi_[300];
   Float_t	GenPart_mass_[300];
   Int_t	GenPart_genPartIdxMother_[300];
   Int_t	GenPart_pdgId_[300];
   Int_t	GenPart_status_[300];
   Int_t	GenPart_statusFlags_[300];
  
   UInt_t	nGenJet_;  
   Float_t	GenJet_pt_[100];
   Float_t	GenJet_eta_[100];
   Float_t	GenJet_phi_[100];
   Float_t	GenJet_mass_[100];
   Int_t	GenJet_partonFlavour_[100];
   Int_t	GenJet_hadronFlavour_[100];
   
   // Trigger and vertex
   bool Pass_trigger_mu ;
   bool Pass_trigger_ele ;

   //muon and ele 2016
   Bool_t	HLT_IsoMu24_, HLT_IsoTkMu24_;
   Bool_t	HLT_Ele27_WPTight_Gsf_;
   //muon and ele 2017
   Bool_t	HLT_IsoMu27_;
   Bool_t	HLT_Ele32_WPTight_Gsf_L1DoubleEG_;
   Bool_t	L1_SingleEG24_;
   Bool_t	L1_SingleEG26_;
   Bool_t	L1_SingleEG30_;
   Bool_t	L1_SingleEG32_;
   Bool_t	L1_SingleEG34_;
   Bool_t	L1_SingleEG36_;
   Bool_t	L1_SingleEG38_;
   Bool_t	L1_SingleEG40_;
   Bool_t	L1_SingleEG42_;
   Bool_t	L1_SingleEG45_;
   Bool_t	L1_SingleEG50_;
   Bool_t	L1_SingleEG34er2p1_;
   Bool_t	L1_SingleEG36er2p1_;
   Bool_t	L1_SingleEG38er2p1_;
   Bool_t	L1_SingleIsoEG24er2p1_;
   Bool_t	L1_SingleIsoEG26er2p1_;
   Bool_t	L1_SingleIsoEG28er2p1_;
   Bool_t	L1_SingleIsoEG30er2p1_;
   Bool_t	L1_SingleIsoEG32er2p1_;
   Bool_t	L1_SingleIsoEG34er2p1_;
   Bool_t	L1_SingleIsoEG36er2p1_;
   Bool_t	L1_SingleIsoEG24_;
   Bool_t	L1_SingleIsoEG26_;
   Bool_t	L1_SingleIsoEG28_;
   Bool_t	L1_SingleIsoEG30_;
   Bool_t	L1_SingleIsoEG32_;
   Bool_t	L1_SingleIsoEG34_;
   Bool_t	L1_SingleIsoEG36_;
   Bool_t	L1_SingleIsoEG38_;
   //muon and ele 2018
   Bool_t	HLT_Ele32_WPTight_Gsf_;
   //filters
   Bool_t	Flag_goodVertices_ ;
   Bool_t	Flag_globalSuperTightHalo2016Filter_ ;
   Bool_t	Flag_HBHENoiseFilter_ ;
   Bool_t	Flag_HBHENoiseIsoFilter_ ;
   Bool_t	Flag_EcalDeadCellTriggerPrimitiveFilter_ ;
   Bool_t	Flag_BadPFMuonFilter_ ;
   Bool_t	Flag_ecalBadCalibFilter_ ;

   Float_t    pvNDOF_;
   Float_t    pvX_;
   Float_t    pvY_;
   Float_t    pvZ_;


   // Electron
   UInt_t       nEle_;
   Float_t      elePt_[20];
   Float_t      eleEta_[20];
   Float_t      elePhi_[20];
   Int_t        eleCharge_[20];
   Float_t      eleMass_[20];
   Int_t        eleGenIdx_[20];

   Float_t      eleDeltaEtaSC_[20];
   Float_t      elePFRelIso_[20];
   Float_t      elePFRelChIso_[20];
   Int_t        eleIDcutbased_[20];
   Float_t      eleD0_[20];
   Float_t      eleDz_[20];
   Float_t      eleSIEIE_[20];
   
   Int_t        eleVidWPBitmap_[20];
   Float_t      eleEcalSumEtDr03_[20];
   Float_t      eleHcalSumEtDr03_[20];
   Float_t      eleTrkSumPtDr03_[20];
   //
   Float_t      ele_Pt_cut;
   
   // Muon
   UInt_t       nMuon_;
   Float_t      muPt_[15];
   Float_t      muEta_[15];
   Float_t      muPhi_[15];
   Int_t        muCharge_[15];
   Float_t      muMass_[15];
   Int_t        muGenIdx_[15];
   Float_t      muPFRelIso_[15];
   Bool_t       muMediumId_[15];
   Bool_t       muTightId_[15];
   Bool_t       muIsPFMuon_[15];
   Bool_t       muIsGlobal_[15];
   Bool_t       muIsTracker_[15];
   Float_t      mudxy_[15];
   Float_t      mudz_[15];
   Int_t        munTrackerLayers_[15];
   //
   Float_t      mu_Pt_cut;

   // Jet
   UInt_t       nJet_;
   Float_t      jetPt_[200];
   Float_t      jetEta_[200];
   Float_t      jetPhi_[200];
   Float_t      jetMass_[200];
   Int_t        jetHadFlvr_[200];
   Int_t        jetPartFlvr_[200];
   Int_t        jetGenJetIdx_[200];
   Int_t        jetID_[200];
   Int_t        jetPUID_[200];
   Float_t      jetBtagDeepB_[200];
   Float_t         jetBtagDeepCvB_[200];
   Float_t         jetBtagDeepCvL_[200];
   Float_t      jetBtagDeepFlavB_[200];
   Float_t         jetBtagDeepFlavCvB_[200];
   Float_t         jetBtagDeepFlavCvL_[200];
   //
   Float_t      jet_Pt_cut;
   Float_t      jet_Pt_cut_Max;
   Float_t	btag_cut;
   Float_t	btag_cuta;
   Float_t	btag_cutb;   
   Float_t	btag_cut_DeepCSV;
   Float_t	btag_cut_DeepCSVa;
   Float_t	btag_cut_DeepCSVb;

   //MET
   Float_t	MET_pt_;
   Float_t	MET_phi_;

   Float_t	GenMET_pt_;
   Float_t	GenMET_phi_;
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
   Int_t		nMuEtaBins  = 25;
   Int_t		nEleEtaBins = 24;
   Int_t		nJetEtaBins = 26;
   Int_t		nETBins	    = 19;
   TLorentzVector	mujetR, mujetG; 
   TLorentzVector	elejetR, elejetG; 
   TLorentzVector	metR, metG; 
   TLorentzVector	bjetR, bjetG; 
   TLorentzVector	ljetR, ljetG; 
   TLorentzVector	jetR, jetG; 
   float		ObsEta, ObsET ;
   int			binEta, binET;
   ////////////////////////////////////////////////////////

   PUJetIDEff(TTree *tree=0);
   virtual ~PUJetIDEff() ;
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

   bool CheckTrigFilterVertex(void);
   bool passEleID(int eleInd, int cutVal, bool doRelisoCut);

   ClassDef(PUJetIDEff,2);

};

#endif



//_____________________________________________________________________
PUJetIDEff::PUJetIDEff(TTree * /*tree*/)
{
  // Constructor

   Reset();
}
//_____________________________________________________________________
void PUJetIDEff::Reset()
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
PUJetIDEff::~PUJetIDEff()
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
void PUJetIDEff::Init(TTree *tree)
{
  //   Set branch addresses

  Info("Init","tree: %p", tree);

  if (tree == 0) return;
  fChain    = tree;

  fChain->SetCacheSize(100*1024*1024);
  fChain->SetBranchStatus("*",0);

  ///////////////////////////////////////////////////////////////////////////
  fChain->SetBranchStatus("PV_ndof",1);
  fChain->SetBranchAddress("PV_ndof", &pvNDOF_);
  
  fChain->SetBranchStatus("PV_x",1);
  fChain->SetBranchAddress("PV_x", &pvX_);
  
  fChain->SetBranchStatus("PV_y",1);
  fChain->SetBranchAddress("PV_y", &pvY_);
  
  fChain->SetBranchStatus("PV_z",1);
  fChain->SetBranchAddress("PV_z", &pvZ_);
  
  if (fYear==2016){
    fChain->SetBranchStatus("HLT_IsoMu24",1);
    fChain->SetBranchAddress("HLT_IsoMu24",&HLT_IsoMu24_);
    
    fChain->SetBranchStatus("HLT_IsoTkMu24",1);
    fChain->SetBranchAddress("HLT_IsoTkMu24",&HLT_IsoTkMu24_);
    
    fChain->SetBranchStatus("HLT_Ele27_WPTight_Gsf",1);
    fChain->SetBranchAddress("HLT_Ele27_WPTight_Gsf",&HLT_Ele27_WPTight_Gsf_);    
  }
  
  if (fYear==2017){
    fChain->SetBranchStatus("HLT_IsoMu27",1);
    fChain->SetBranchAddress("HLT_IsoMu27",&HLT_IsoMu27_);
    
    fChain->SetBranchStatus("HLT_Ele32_WPTight_Gsf_L1DoubleEG",1);
    fChain->SetBranchAddress("HLT_Ele32_WPTight_Gsf_L1DoubleEG",&HLT_Ele32_WPTight_Gsf_L1DoubleEG_);
    
    fChain->SetBranchStatus("L1_SingleEG24",1);
    fChain->SetBranchStatus("L1_SingleEG26",1);
    fChain->SetBranchStatus("L1_SingleEG30",1);
    fChain->SetBranchStatus("L1_SingleEG32",1);
    fChain->SetBranchStatus("L1_SingleEG34",1);
    fChain->SetBranchStatus("L1_SingleEG36",1);
    fChain->SetBranchStatus("L1_SingleEG38",1);
    fChain->SetBranchStatus("L1_SingleEG40",1);
    fChain->SetBranchStatus("L1_SingleEG42",1);
    fChain->SetBranchStatus("L1_SingleEG45",1);
    fChain->SetBranchStatus("L1_SingleEG50",1);
    fChain->SetBranchStatus("L1_SingleEG34er2p1",1);
    fChain->SetBranchStatus("L1_SingleEG36er2p1",1);
    fChain->SetBranchStatus("L1_SingleEG38er2p1",1);
    fChain->SetBranchStatus("L1_SingleIsoEG24er2p1",1);
    fChain->SetBranchStatus("L1_SingleIsoEG26er2p1",1);
    fChain->SetBranchStatus("L1_SingleIsoEG28er2p1",1);
    fChain->SetBranchStatus("L1_SingleIsoEG30er2p1",1);
    fChain->SetBranchStatus("L1_SingleIsoEG32er2p1",1);
    fChain->SetBranchStatus("L1_SingleIsoEG34er2p1",1);
    fChain->SetBranchStatus("L1_SingleIsoEG36er2p1",1);
    fChain->SetBranchStatus("L1_SingleIsoEG24",1);
    fChain->SetBranchStatus("L1_SingleIsoEG26",1);
    fChain->SetBranchStatus("L1_SingleIsoEG28",1);
    fChain->SetBranchStatus("L1_SingleIsoEG30",1);
    fChain->SetBranchStatus("L1_SingleIsoEG32",1);    
    fChain->SetBranchStatus("L1_SingleIsoEG34",1);
    fChain->SetBranchStatus("L1_SingleIsoEG36",1);
    fChain->SetBranchStatus("L1_SingleIsoEG38",1);
    
    fChain->SetBranchAddress("L1_SingleEG24",&L1_SingleEG24_);
    fChain->SetBranchAddress("L1_SingleEG26",&L1_SingleEG26_);
    fChain->SetBranchAddress("L1_SingleEG30",&L1_SingleEG30_);
    fChain->SetBranchAddress("L1_SingleEG32",&L1_SingleEG32_);
    fChain->SetBranchAddress("L1_SingleEG34",&L1_SingleEG34_);
    fChain->SetBranchAddress("L1_SingleEG36",&L1_SingleEG36_);
    fChain->SetBranchAddress("L1_SingleEG38",&L1_SingleEG38_);
    fChain->SetBranchAddress("L1_SingleEG40",&L1_SingleEG40_);
    fChain->SetBranchAddress("L1_SingleEG42",&L1_SingleEG42_);
    fChain->SetBranchAddress("L1_SingleEG45",&L1_SingleEG45_);
    fChain->SetBranchAddress("L1_SingleEG50",&L1_SingleEG50_);
    fChain->SetBranchAddress("L1_SingleEG34er2p1",&L1_SingleEG34er2p1_);
    fChain->SetBranchAddress("L1_SingleEG36er2p1",&L1_SingleEG36er2p1_);
    fChain->SetBranchAddress("L1_SingleEG38er2p1",&L1_SingleEG38er2p1_);
    fChain->SetBranchAddress("L1_SingleIsoEG24er2p1",&L1_SingleIsoEG24er2p1_);
    fChain->SetBranchAddress("L1_SingleIsoEG26er2p1",&L1_SingleIsoEG26er2p1_);
    fChain->SetBranchAddress("L1_SingleIsoEG28er2p1",&L1_SingleIsoEG28er2p1_);
    fChain->SetBranchAddress("L1_SingleIsoEG30er2p1",&L1_SingleIsoEG30er2p1_);
    fChain->SetBranchAddress("L1_SingleIsoEG32er2p1",&L1_SingleIsoEG32er2p1_);
    fChain->SetBranchAddress("L1_SingleIsoEG34er2p1",&L1_SingleIsoEG34er2p1_);
    fChain->SetBranchAddress("L1_SingleIsoEG36er2p1",&L1_SingleIsoEG36er2p1_);
    fChain->SetBranchAddress("L1_SingleIsoEG24",&L1_SingleIsoEG24_);
    fChain->SetBranchAddress("L1_SingleIsoEG26",&L1_SingleIsoEG26_);
    fChain->SetBranchAddress("L1_SingleIsoEG28",&L1_SingleIsoEG28_);
    fChain->SetBranchAddress("L1_SingleIsoEG30",&L1_SingleIsoEG30_);
    fChain->SetBranchAddress("L1_SingleIsoEG32",&L1_SingleIsoEG32_);
    fChain->SetBranchAddress("L1_SingleIsoEG34",&L1_SingleIsoEG34_);
    fChain->SetBranchAddress("L1_SingleIsoEG36",&L1_SingleIsoEG36_);
    fChain->SetBranchAddress("L1_SingleIsoEG38",&L1_SingleIsoEG38_);
    
    /* fChain->SetBranchStatus("HLT_IsoMu24",1); */
    /* fChain->SetBranchAddress("HLT_IsoMu24",&HLT_IsoMu24_); */
    
    /* // fChain->SetBranchStatus("HLT_IsoTkMu24",1); */
    /* // fChain->SetBranchAddress("HLT_IsoTkMu24",&HLT_IsoTkMu24_); */
    
  }
  
  if (fYear==2018){
    fChain->SetBranchStatus("HLT_IsoMu24",1);
    fChain->SetBranchAddress("HLT_IsoMu24",&HLT_IsoMu24_);
    
    fChain->SetBranchStatus("HLT_Ele32_WPTight_Gsf",1);
    fChain->SetBranchAddress("HLT_Ele32_WPTight_Gsf",&HLT_Ele32_WPTight_Gsf_);
  }	
  //Fliters
  fChain->SetBranchStatus("Flag_goodVertices",1);
  fChain->SetBranchAddress("Flag_goodVertices",&Flag_goodVertices_);
  
  fChain->SetBranchStatus("Flag_globalSuperTightHalo2016Filter",1);
  fChain->SetBranchAddress("Flag_globalSuperTightHalo2016Filter", &Flag_globalSuperTightHalo2016Filter_);
  
  fChain->SetBranchStatus("Flag_HBHENoiseFilter",1);
  fChain->SetBranchAddress("Flag_HBHENoiseFilter", &Flag_HBHENoiseFilter_);
  
  fChain->SetBranchStatus("Flag_HBHENoiseIsoFilter",1);
  fChain->SetBranchAddress("Flag_HBHENoiseIsoFilter", &Flag_HBHENoiseIsoFilter_);
  
  fChain->SetBranchStatus("Flag_EcalDeadCellTriggerPrimitiveFilter",1);
  fChain->SetBranchAddress("Flag_EcalDeadCellTriggerPrimitiveFilter", &Flag_EcalDeadCellTriggerPrimitiveFilter_);
  
  fChain->SetBranchStatus("Flag_BadPFMuonFilter",1);
  fChain->SetBranchAddress("Flag_BadPFMuonFilter",&Flag_BadPFMuonFilter_);
  
  if(fYear==2017 || fYear==2018){
    fChain->SetBranchStatus("Flag_ecalBadCalibFilter",1);
    fChain->SetBranchAddress("Flag_ecalBadCalibFilter",&Flag_ecalBadCalibFilter_);
  }
  
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

  fChain->SetBranchStatus("Electron_genPartIdx",1);
  fChain->SetBranchAddress("Electron_genPartIdx", &eleGenIdx_);

  fChain->SetBranchStatus("Electron_deltaEtaSC",1);
  fChain->SetBranchAddress("Electron_deltaEtaSC", &eleDeltaEtaSC_);

  fChain->SetBranchStatus("Electron_pfRelIso03_chg",1);
  fChain->SetBranchAddress("Electron_pfRelIso03_chg", &elePFRelChIso_);

  fChain->SetBranchStatus("Electron_pfRelIso03_all",1);
  fChain->SetBranchAddress("Electron_pfRelIso03_all", &elePFRelIso_);

  fChain->SetBranchStatus("Electron_sieie",1);
  fChain->SetBranchAddress("Electron_sieie", &eleSIEIE_);
	
  if (fYear==2016){
    fChain->SetBranchStatus("Electron_cutBased",1); 
    fChain->SetBranchAddress("Electron_cutBased", &eleIDcutbased_);

    fChain->SetBranchStatus("Electron_vidNestedWPBitmap",1);
    fChain->SetBranchAddress("Electron_vidNestedWPBitmap", &eleVidWPBitmap_);
  }
  if (fYear==2017 || fYear==2018){
    fChain->SetBranchStatus("Electron_cutBased",1);
    fChain->SetBranchAddress("Electron_cutBased", &eleIDcutbased_);

    fChain->SetBranchStatus("Electron_vidNestedWPBitmap",1);
    fChain->SetBranchAddress("Electron_vidNestedWPBitmap", &eleVidWPBitmap_);
  }

  fChain->SetBranchStatus("Electron_dxy",1);
  fChain->SetBranchAddress("Electron_dxy", &eleD0_);

  fChain->SetBranchStatus("Electron_dz",1);
  fChain->SetBranchAddress("Electron_dz", &eleDz_);
    
  fChain->SetBranchStatus("Electron_dr03EcalRecHitSumEt",1);
  fChain->SetBranchAddress("Electron_dr03EcalRecHitSumEt", &eleEcalSumEtDr03_);

  fChain->SetBranchStatus("Electron_dr03HcalDepth1TowerSumEt",1);
  fChain->SetBranchAddress("Electron_dr03HcalDepth1TowerSumEt", &eleHcalSumEtDr03_);

  fChain->SetBranchStatus("Electron_dr03TkSumPt",1);
  fChain->SetBranchAddress("Electron_dr03TkSumPt", &eleTrkSumPtDr03_);

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

  fChain->SetBranchStatus("Muon_pfRelIso04_all",1);
  fChain->SetBranchAddress("Muon_pfRelIso04_all", &muPFRelIso_);

  fChain->SetBranchStatus("Muon_tightId",1);
  fChain->SetBranchAddress("Muon_tightId", &muTightId_);

  fChain->SetBranchStatus("Muon_mediumId",1);
  fChain->SetBranchAddress("Muon_mediumId", &muMediumId_);

  fChain->SetBranchStatus("Muon_isPFcand",1);
  fChain->SetBranchAddress("Muon_isPFcand", &muIsPFMuon_);

  fChain->SetBranchStatus("Muon_isGlobal",1);
  fChain->SetBranchAddress("Muon_isGlobal", &muIsGlobal_);

  fChain->SetBranchStatus("Muon_isTracker",1);
  fChain->SetBranchAddress("Muon_isTracker", &muIsTracker_);

  fChain->SetBranchStatus("Muon_dxy",1);
  fChain->SetBranchAddress("Muon_dxy", &mudxy_);

  fChain->SetBranchStatus("Muon_dz",1);
  fChain->SetBranchAddress("Muon_dz", &mudz_);

  fChain->SetBranchStatus("Muon_nTrackerLayers",1);
  fChain->SetBranchAddress("Muon_nTrackerLayers", &munTrackerLayers_);
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

  fChain->SetBranchStatus("Jet_jetId",1);
  fChain->SetBranchAddress("Jet_jetId", &jetID_);

  fChain->SetBranchStatus("Jet_puId",1);
  fChain->SetBranchAddress("Jet_puId", &jetPUID_);
  
  /* fChain->SetBranchStatus("Jet_btagDeepB",1); */
  /* fChain->SetBranchAddress("Jet_btagDeepB", &jetBtagDeepB_); */
  
  /* fChain->SetBranchStatus("Jet_btagDeepFlavB",1); */
  /* fChain->SetBranchAddress("Jet_btagDeepFlavB", &jetBtagDeepFlavB_); */

  fChain->SetBranchStatus("Jet_btagDeepB",1);
  fChain->SetBranchAddress("Jet_btagDeepB", &jetBtagDeepB_);

  fChain->SetBranchStatus("Jet_btagDeepCvB",1);
  fChain->SetBranchAddress("Jet_btagDeepCvB", &jetBtagDeepCvB_);

  fChain->SetBranchStatus("Jet_btagDeepCvL",1);
  fChain->SetBranchAddress("Jet_btagDeepCvL", &jetBtagDeepCvL_);

  fChain->SetBranchStatus("Jet_btagDeepFlavB",1);
  fChain->SetBranchAddress("Jet_btagDeepFlavB", &jetBtagDeepFlavB_);

  fChain->SetBranchStatus("Jet_btagDeepFlavCvB",1);
  fChain->SetBranchAddress("Jet_btagDeepFlavCvB", &jetBtagDeepFlavCvB_);

  fChain->SetBranchStatus("Jet_btagDeepFlavCvL",1);
  fChain->SetBranchAddress("Jet_btagDeepFlavCvL", &jetBtagDeepFlavCvL_);
  
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

  /* fChain->SetBranchStatus("nJet",1); */
  /* fChain->SetBranchAddress("nJet", &nJet_); */
  
  /* fChain->SetBranchStatus("Jet_pt",1); */
  /* fChain->SetBranchAddress("Jet_pt", &jetPt_); */
    
  /* fChain->SetBranchStatus("Jet_eta",1); */
  /* fChain->SetBranchAddress("Jet_eta", &jetEta_); */
  
  /* fChain->SetBranchStatus("Jet_phi",1); */
  /* fChain->SetBranchAddress("Jet_phi", &jetPhi_); */
  
  /* fChain->SetBranchStatus("Jet_mass",1); */
  /* fChain->SetBranchAddress("Jet_mass", &jetMass_); */
  
  /* fChain->SetBranchStatus("Jet_btagCSVV2",1); */
  /* fChain->SetBranchAddress("Jet_btagCSVV2", &jetBtagCSVV2_); */
  
  /* fChain->SetBranchStatus("Jet_btagDeepB",1); */
  /* fChain->SetBranchAddress("Jet_btagDeepB", &jetBtagDeepB_); */

  /* fChain->SetBranchStatus("Jet_btagDeepCvB",1); */
  /* fChain->SetBranchAddress("Jet_btagDeepCvB", &jetBtagDeepCvB_); */

  /* fChain->SetBranchStatus("Jet_btagDeepCvL",1); */
  /* fChain->SetBranchAddress("Jet_btagDeepCvL", &jetBtagDeepCvL_); */

  /* fChain->SetBranchStatus("Jet_btagDeepFlavB",1); */
  /* fChain->SetBranchAddress("Jet_btagDeepFlavB", &jetBtagDeepFlavB_); */

  /* fChain->SetBranchStatus("Jet_btagDeepFlavCvB",1); */
  /* fChain->SetBranchAddress("Jet_btagDeepFlavCvB", &jetBtagDeepFlavCvB_); */

  /* fChain->SetBranchStatus("Jet_btagDeepFlavCvL",1); */
  /* fChain->SetBranchAddress("Jet_btagDeepFlavCvL", &jetBtagDeepFlavCvL_); */
    
  /* fChain->SetBranchStatus("Jet_partonFlavour",1); */
  /* fChain->SetBranchAddress("Jet_partonFlavour", &jetPartFlvr_); */
  
  /* fChain->SetBranchStatus("Jet_hadronFlavour",1); */
  /* fChain->SetBranchAddress("Jet_hadronFlavour", &jetHadFlvr_); */

  /* fChain->SetBranchStatus("Jet_genJetIdx",1); */
  /* fChain->SetBranchAddress("Jet_genJetIdx", &jetGenJetIdx_); */

}

//_____________________________________________________________________
Bool_t PUJetIDEff::Notify()
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

  if(isPreVFP or isPostVFP){
    if(isPreVFP){ 
      btag_cut_DeepCSV = btag_cut_DeepCSVa ; 
      btag_cut = btag_cuta ; 
    }
    if(isPostVFP){ 
      btag_cut_DeepCSV = btag_cut_DeepCSVb ; 
      btag_cut = btag_cutb ; 
    }
  }
  
  Info("Notify","processing sample %s and file: %s",fSampleType.Data(), fChain->GetCurrentFile()->GetName());  
  
  return kTRUE;
}

