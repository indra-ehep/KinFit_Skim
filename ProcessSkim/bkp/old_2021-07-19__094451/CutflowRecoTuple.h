/**********************************************************************
 Created on : 14/06/2021
 Purpose    : Analyse the Reco tree to create the cutflow histograms
              (format adapted from h1analysis)
 Author     : Indranil Das, Visiting Fellow, TIFR
 Email      : indranil.das@cern.ch | indra.ehep@gmail.com
**********************************************************************/

#ifndef CutflowRecoTuple_h
#define CutflowRecoTuple_h

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
#include "interface/ScaleFactorFunction.h"
#include "interface/muSF_reader.h"
#include "interface/BTagCalibrationStandalone.h"

class  TH1F;
class  TH1D;

class CutflowRecoTuple : public TSelector {
   public :
   
   //File operation pointers
   ////////////////////////////////////////////////////////
   TFile            *fFile[3];
   TDirectory       **fFileDir;
   TProofOutputFile *fProofFile[3]; // For optimized merging of the ntuple

   //Declaration of histograms
   ////////////////////////////////////////////////////////
   TH1F           *hMuPt;//!
   TH1F           *hMuPt1;//!
   TH1F           *hMuPt2;//!
   TH1D           *hElePt;//!
   
   Int_t          fNHist;//!
   Int_t          fNSyst;//!
   TH1F           **hpresel_HT;//!
   TH1F           **hpresel_M3;//!
   TH1F           **hpresel_MET;//!
   TH1F           **hpresel_M_jjkF;//!
   TH1F           **hpresel_M_jj;//!
   TH1F           **hpresel_Nbjet;//!
   TH1F           **hpresel_Njet;//!
   TH1F           **hpresel_WtransMass;//!
   TH1F           **hpresel_elePhi;//!
   TH1F           **hpresel_elePt;//!
   TH1F           **hpresel_eleSCEta;//!
   TH1F           **hpresel_muEta;//!
   TH1F           **hpresel_muPhi;//!
   TH1F           **hpresel_muPt;//!
   TH1F           **hpresel_nVtx;//!
   
   Int_t          fNTestHist;//
   TH1D           **hCheck;//
   ////////////////////////////////////////////////////////

   Long64_t        fProcessed;//!
   TTree          *fChain;//!    //pointer to the analyzed TTree or TChain

   //Declaration of leaves types
   ////////////////////////////////////////////////////////
   Int_t	_run = 0 ;
   Long64_t	_event = 0 ;
   Int_t	_lumis = 0 ;
   Bool_t	_isData = 0 ;
   Long64_t	_skim_entryId = 0 ;

   Float_t	_PUweight = 0 ;
   Float_t	_PUweight_Up = 0 ;
   Float_t	_PUweight_Do = 0 ;
	
   Float_t	 _q2weight_Up = 0 ;
   Float_t	 _q2weight_Do = 0 ;
   Float_t	 _q2weight_nominal = 0 ;
   std::vector<float>	*_genScaleSystWeights = 0 ;

   Float_t	 _pdfWeight = 0 ;
   Float_t	 _pdfuncer = 0 ;
   Float_t	 _pdfweight_Up = 0 ;
   Float_t	 _pdfweight_Do = 0 ;
   std::vector<float>	*_pdfSystWeight = 0 ;

   Float_t	_ISRweight_Up = 0 ;
   Float_t	_ISRweight_Do = 0 ;

   Float_t	_FSRweight_Up = 0 ;
   Float_t	_FSRweight_Do = 0 ;

   float	_prefireSF = 0 ;
   float	_prefireSF_Up = 0 ;
   float	_prefireSF_Do = 0 ;

   float	_btagWeight_1a = 0 ;
   float	_btagWeight_1a_b_Up = 0 ;
   float	_btagWeight_1a_b_Do = 0 ;
   float	_btagWeight_1a_l_Up = 0 ;
   float	_btagWeight_1a_l_Do = 0 ;

   std::vector<float>	*_btagWeight = 0 ;
   std::vector<float>	*_btagWeight_b_Up = 0 ;
   std::vector<float>	*_btagWeight_b_Do = 0 ;
   std::vector<float>	*_btagWeight_l_Up = 0 ;
   std::vector<float>	*_btagWeight_l_Do = 0 ;

   std::vector<float>	*_btagSF = 0 ;
   std::vector<float>	*_btagSF_b_Up = 0 ;
   std::vector<float>	*_btagSF_b_Do = 0 ;
   std::vector<float>	*_btagSF_l_Up = 0 ;
   std::vector<float>	*_btagSF_l_Do = 0 ;

   Float_t	_muEffWeight = 0 ;
   Float_t	_muEffWeight_Up = 0 ;
   Float_t	_muEffWeight_Do = 0 ;

   Float_t	_muEffWeight_IdIso = 0 ;
   Float_t	_muEffWeight_IdIso_Up = 0 ;
   Float_t	_muEffWeight_IdIso_Do = 0 ;

   Float_t	_muEffWeight_Trig = 0 ;
   Float_t	_muEffWeight_Trig_Up = 0 ;
   Float_t	_muEffWeight_Trig_Do = 0 ;

   Float_t	_eleEffWeight = 0 ;
   Float_t	_eleEffWeight_Up = 0 ;
   Float_t	_eleEffWeight_Do = 0 ;

   Float_t	_eleEffWeight_IdReco = 0 ;
   Float_t	_eleEffWeight_IdReco_Up = 0 ;
   Float_t	_eleEffWeight_IdReco_Do = 0 ;

   Float_t	_eleEffWeight_Trig = 0 ;
   Float_t	_eleEffWeight_Trig_Up = 0 ;
   Float_t	_eleEffWeight_Trig_Do = 0 ;

   Float_t	_evtWeight = 0 ;
   Float_t	_lumiWeight = 0 ;
   Float_t	_sampleWeight = 0 ;
   Double_t     _nMC_total = 0 ;
   Double_t     _nMC_totalUS = 0;
   Float_t      _xss = 0;

   Int_t	_nVtx = 0 ;
   Int_t	_nGoodVtx = 0 ;
   Bool_t	_isPVGood = 0 ;
   
   Float_t	_genMET = 0 ;
   
   Float_t	_pfMET = 0 ;
   Float_t	_pfMETPhi = 0 ;
   Float_t	_nu_px = 0 ;
   Float_t	_nu_py = 0 ;
   Float_t	_nu_pz = 0 ;
   Float_t	_nu_pz_other = 0 ;
   Float_t	_WtransMass = 0 ;
  
   Float_t	_chi2 = 0 ;
   int		_NDF = 0 ;
   int		_Nbiter = 0 ;
   Float_t	_M_jj = 0 ;
   Float_t	_M_jjkF = 0 ;
   int		_bjlep_id = 0 ;
   int		_bjhad_id = 0 ;
   int		_cjhad_id = 0 ;
   int		_sjhad_id = 0 ;
   Float_t	_lepPt = 0 ;
   Float_t	_lepEta = 0 ;
   Float_t	_lepPhi = 0 ;
   Float_t	_lepEnergy = 0 ;
   Float_t	_metPx = 0 ;
   Float_t	_metPy = 0 ;
   Float_t	_metPz = 0 ;
   Float_t	_jetBlepPt = 0 ;
   Float_t	_jetBlepEta = 0 ;
   Float_t	_jetBlepPhi = 0 ;
   Float_t	_jetBlepEnergy = 0 ;
   Float_t	_jetBhadPt = 0 ;
   Float_t	_jetBhadEta = 0 ;
   Float_t	_jetBhadPhi = 0 ;
   Float_t	_jetBhadEnergy = 0 ;
   Float_t	_jetChadPt = 0 ;
   Float_t	_jetChadEta = 0 ;
   Float_t	_jetChadPhi = 0 ;
   Float_t	_jetChadEnergy = 0 ;
   Float_t	_jetShadPt = 0 ;
   Float_t	_jetShadEta = 0 ;
   Float_t	_jetShadPhi = 0 ;
   Float_t	_jetShadEnergy = 0 ;
   
   Int_t	 _nEle = 0 ;
   Int_t	 _nEleLoose = 0 ;
   std::vector<float>	 *_elePt = 0 ;
   std::vector<float>	 *_elePhi = 0 ;
   std::vector<float>	 *_eleSCEta = 0 ;
   std::vector<float>	 *_elePFRelIso = 0 ;
   
   Int_t	 _nMu = 0 ;
   Int_t	 _nMuLoose = 0 ;
   std::vector<float>	 *_muPt = 0 ;
   std::vector<float>	 *_muEta = 0 ;
   std::vector<float>	 *_muPhi = 0 ;
   std::vector<float>	 *_muPFRelIso = 0 ;
   std::vector<float>    *_muRoccoR = 0 ;
   
   Int_t	 _nJet = 0 ;
   Int_t	 _nBJet = 0 ;
   std::vector<float>	 *_jetPt = 0 ;
   std::vector<float>	 *_jetEta = 0 ;
   std::vector<float>	 *_jetPhi = 0 ;
   std::vector<float>	 *_jetMass = 0 ;

   Int_t	 _nfwdJet = 0 ;
   std::vector<float>	 *_fwdJetPt = 0 ;
   std::vector<float>	 *_fwdJetEta = 0 ;
   std::vector<float>	 *_fwdJetPhi = 0 ;
   std::vector<float>	 *_fwdJetMass = 0 ;

   std::vector<float>	 *_jetCMVA = 0 ;
   std::vector<float>	 *_jetCSVV2 = 0 ;
   std::vector<float>	 *_jetDeepB = 0 ;
   std::vector<float>	 *_jetDeepC = 0 ;

   std::vector<Int_t>	 *_jetHadFlvr = 0 ;
   std::vector<Int_t>	 *_jetPartFlvr = 0 ;
   std::vector<int>	 *_jetGenJetIdx = 0 ;
   

   Int_t	 _nGenJet = 0 ;
   std::vector<float>	 *_genJetPt = 0 ;
   std::vector<float>	 *_genJetEta = 0 ;
   std::vector<float>	 *_genJetPhi = 0 ;
   std::vector<float>	 *_genJetMass = 0 ;
   std::vector<float>	 *_genJetPartonFlavour = 0 ;
   std::vector<float>	 *_genJetHadronFlavour = 0 ;

   Int_t	 _nLHEPart = 0 ;
   Int_t	 _nGenPart = 0 ;
   std::vector<float>	 *_genPt = 0 ;
   std::vector<float>	 *_genEta = 0 ;
   std::vector<float>	 *_genPhi = 0 ;
   std::vector<float>	 *_genMass = 0 ;
   std::vector<int>	 *_genStatus = 0 ;
   std::vector<int>	 *_genStatusFlag = 0 ;
   std::vector<int>	 *_genPDGID = 0 ;
   std::vector<int>	 *_genMomIdx = 0 ;

   double	 _M3 = 0 ;
   double	 _HT = 0 ;
   bool		 _passPresel_Ele = 0 ;
   bool		 _passPresel_Mu = 0 ;
   bool		 _passAll_Ele = 0 ;
   bool		 _passAll_Mu = 0 ;
   bool	       	 _passTrigger_ele = 0 ;
   bool	       	 _passTrigger_mu = 0 ;
   bool	       	 _passFilter = 0 ;
   ////////////////////////////////////////////////////////


   //List of branches
   ////////////////////////////////////////////////////////
   TBranch	*br_run				= 0 ;
   TBranch	*br_event			= 0 ;
   TBranch	*br_lumis			= 0 ;
   TBranch	*br_isData			= 0 ;
   TBranch	*br_skim_entryId		= 0 ;

   TBranch	*br_PUweight			= 0 ;
   TBranch	*br_PUweight_Up			= 0 ;
   TBranch	*br_PUweight_Do			= 0 ;
   
   TBranch	*br_q2weight_Up			= 0 ;
   TBranch	*br_q2weight_Do			= 0 ;
   TBranch	*br_q2weight_nominal		= 0 ;
   TBranch	*br_genScaleSystWeights		= 0 ;
	
   TBranch	*br_pdfWeight			= 0 ;
   TBranch	*br_pdfuncer			= 0 ;
   TBranch	*br_pdfweight_Up		= 0 ;
   TBranch	*br_pdfweight_Do		= 0 ;
   TBranch	*br_pdfSystWeight		= 0 ;
   
   TBranch	*br_ISRweight_Up		= 0 ;
   TBranch	*br_ISRweight_Do		= 0 ;
   
   TBranch	*br_FSRweight_Up		= 0 ;
   TBranch	*br_FSRweight_Do		= 0 ;
   
   
   TBranch	*br_prefireSF			= 0 ;
   TBranch	*br_prefireSF_Up		= 0 ;
   TBranch	*br_prefireSF_Do		= 0 ;
   
   TBranch	*br_btagWeight_1a		= 0 ;
   TBranch	*br_btagWeight_1a_b_Up		= 0 ;
   TBranch	*br_btagWeight_1a_b_Do		= 0 ;
   TBranch	*br_btagWeight_1a_l_Up		= 0 ;
   TBranch	*br_btagWeight_1a_l_Do		= 0 ;
   
   TBranch	*br_btagWeight			= 0 ;
   TBranch	*br_btagWeight_b_Up		= 0 ;
   TBranch	*br_btagWeight_b_Do		= 0 ;
   TBranch	*br_btagWeight_l_Up		= 0 ;
   TBranch	*br_btagWeight_l_Do		= 0 ;
   
   TBranch	*br_btagSF			= 0 ;
   TBranch	*br_btagSF_b_Up			= 0 ;
   TBranch	*br_btagSF_b_Do			= 0 ;
   TBranch	*br_btagSF_l_Up			= 0 ;
   TBranch	*br_btagSF_l_Do			= 0 ;
   
   TBranch	*br_muEffWeight			= 0 ;
   TBranch	*br_muEffWeight_Up		= 0 ;
   TBranch	*br_muEffWeight_Do		= 0 ;
   
   TBranch	*br_muEffWeight_IdIso		= 0 ;
   TBranch	*br_muEffWeight_IdIso_Up	= 0 ;
   TBranch	*br_muEffWeight_IdIso_Do	= 0 ;
   
   TBranch	*br_muEffWeight_Trig		= 0 ;
   TBranch	*br_muEffWeight_Trig_Up		= 0 ;
   TBranch	*br_muEffWeight_Trig_Do		= 0 ;
   
   TBranch	*br_eleEffWeight		= 0 ;
   TBranch	*br_eleEffWeight_Up		= 0 ;
   TBranch	*br_eleEffWeight_Do		= 0 ;
   
   TBranch	*br_eleEffWeight_IdReco		= 0 ;
   TBranch	*br_eleEffWeight_IdReco_Up	= 0 ;
   TBranch	*br_eleEffWeight_IdReco_Do	= 0 ;
   
   TBranch	*br_eleEffWeight_Trig		= 0 ;
   TBranch	*br_eleEffWeight_Trig_Up	= 0 ;
   TBranch	*br_eleEffWeight_Trig_Do	= 0 ;
   
   TBranch	*br_evtWeight			= 0 ;
   TBranch	*br_lumiWeight			= 0 ;
   TBranch	*br_sampleWeight       		= 0 ;
   TBranch	*br_nMC_total			= 0 ;
   TBranch	*br_nMC_totalUS			= 0 ;
   TBranch	*br_xss				= 0 ;
   

   /* TBranch   *br_evtWeightAlt		= 0 ; */
   /* TBranch   *br_lumiWeightAlt		= 0 ; */

   TBranch	*br_nVtx			= 0 ;
   TBranch      *br_nGoodVtx			= 0 ;
   TBranch      *br_isPVGood			= 0 ;

   TBranch	*br_genMET			= 0 ;
   
   TBranch   *br_pfMET				= 0 ;
   TBranch	*br_pfMETPhi			= 0 ;
   TBranch	*br_nu_px			= 0 ;
   TBranch	*br_nu_py			= 0 ;
   TBranch	*br_nu_pz			= 0 ;
   TBranch	*br_nu_pz_other			= 0 ;
   TBranch	*br_WtransMass			= 0 ;
  
   TBranch	*br_chi2			= 0 ;
   TBranch	*br_NDF				= 0 ;
   TBranch	*br_Nbiter			= 0 ;
   TBranch	*br_M_jj			= 0 ;
   TBranch	*br_M_jjkF			= 0 ;
   TBranch	*br_bjlep_id			= 0 ;
   TBranch	*br_bjhad_id			= 0 ;
   TBranch	*br_cjhad_id			= 0 ;
   TBranch	*br_sjhad_id			= 0 ;
   TBranch	*br_lepPt			= 0 ;
   TBranch	*br_lepEta			= 0 ;
   TBranch	*br_lepPhi			= 0 ;
   TBranch	*br_lepEnergy			= 0 ;
   TBranch	*br_metPx			= 0 ;
   TBranch	*br_metPy			= 0 ;
   TBranch	*br_metPz			= 0 ;
   TBranch	*br_jetBlepPt			= 0 ;
   TBranch	*br_jetBlepEta			= 0 ;
   TBranch	*br_jetBlepPhi			= 0 ;
   TBranch	*br_jetBlepEnergy		= 0 ;
   TBranch	*br_jetBhadPt			= 0 ;
   TBranch	*br_jetBhadEta			= 0 ;
   TBranch	*br_jetBhadPhi			= 0 ;
   TBranch	*br_jetBhadEnergy		= 0 ;
   TBranch	*br_jetChadPt			= 0 ;
   TBranch	*br_jetChadEta			= 0 ;
   TBranch	*br_jetChadPhi			= 0 ;
   TBranch	*br_jetChadEnergy		= 0 ;
   TBranch	*br_jetShadPt			= 0 ;
   TBranch	*br_jetShadEta			= 0 ;
   TBranch	*br_jetShadPhi			= 0 ;
   TBranch	*br_jetShadEnergy		= 0 ;
   
   
   TBranch   *br_nEle				= 0 ;
   TBranch   *br_nEleLoose			= 0 ;
   TBranch   *br_elePt				= 0;
   TBranch   *br_elePhi				= 0 ;
   TBranch   *br_eleSCEta			= 0 ;
   TBranch   *br_elePFRelIso			= 0 ;
   TBranch   *br_nMu				= 0 ;
   TBranch   *br_nMuLoose			= 0 ;
   TBranch   *br_muPt				= 0;
   TBranch   *br_muEta				= 0 ;
   TBranch   *br_muPhi				= 0 ;
   TBranch   *br_muPFRelIso			= 0 ;
   TBranch   *br_muRoccoR			= 0 ;

   TBranch   *br_nJet				= 0 ;
   TBranch   *br_nBJet				= 0 ;
   TBranch   *br_jetPt				= 0 ;
   TBranch   *br_jetEta				= 0 ;
   TBranch   *br_jetPhi				= 0 ;
   TBranch   *br_jetMass			= 0 ;
   
   TBranch   *br_jetCMVA			= 0 ;
   TBranch   *br_jetCSVV2			= 0 ;
   TBranch   *br_jetDeepB			= 0 ;
   TBranch   *br_jetDeepC			= 0 ;
   
   TBranch   *br_jetPartFlvr			= 0 ;
   TBranch   *br_jetHadFlvr			= 0 ;
   TBranch   *br_jetGenJetIdx			= 0 ;
   
   TBranch   *br_nGenJet			= 0 ;
   TBranch   *br_genJetPt			= 0 ;
   TBranch   *br_genJetEta			= 0 ;
   TBranch   *br_genJetPhi			= 0 ;
   TBranch   *br_genJetMass			= 0 ;
   
   TBranch   *br_nfwdJet			= 0 ;
   TBranch   *br_fwdJetPt			= 0 ;
   TBranch   *br_fwdJetEta			= 0 ;
   TBranch   *br_fwdJetPhi			= 0 ;
   TBranch   *br_fwdJetMass			= 0 ;
   
   TBranch   *br_nLHEPart			= 0 ;
   TBranch   *br_nGenPart			= 0 ;
   TBranch   *br_genPt				= 0 ;
   TBranch   *br_genEta				= 0 ;
   TBranch   *br_genPhi				= 0 ;
   TBranch   *br_genMass			= 0 ;
   TBranch   *br_genStatus			= 0 ;
   TBranch   *br_genStatusFlag			= 0 ;
   TBranch   *br_genPDGID			= 0 ;
   TBranch   *br_genMomIdx			= 0 ;
   /* TBranch     *br_genMomPID			= 0 ; */
   /* TBranch     *br_genGMomPID		= 0 ; */
   

   TBranch   *br_M3				= 0 ;
   TBranch   *br_HT				= 0 ;
   
   TBranch   *br_passPresel_Ele			= 0 ;
   TBranch   *br_passPresel_Mu			= 0 ;
   TBranch   *br_passAll_Ele			= 0 ;
   TBranch   *br_passAll_Mu			= 0 ;
   TBranch   *br_passTrigger_ele 		= 0 ;
   TBranch   *br_passTrigger_mu 		= 0 ;
   TBranch   *br_passFilter 			= 0 ;

   TBranch   *br_dileptonsample			= 0 ;
   ////////////////////////////////////////////////////////
   //Assorted
   TString fSample;
   TString fSampleDir;
   TString fSampleType;
   TString fMode;
   Int_t fYear;
   bool isData ;
   TString fBasePath ;
   double local_evtWeight = 0.0;
   MuonSF *muSFa;
   MuonSF *muSFb;
   TFile *f_trackSF_BCDEF;
   TFile *f_trackSF_GH;
   TGraphAsymmErrors *tg_trackSF_BCDEF;
   TGraphAsymmErrors *tg_trackSF_GH;
   //trigger SF
   TFile *f_trigSF_BCDEF;
   TFile *f_trigSF_GH ;
   TH2D *h2_trigSF_BCDEF;
   TH2D *h2_trigSF_GH;
   //Identification SF
   TFile *f_idSF_BCDEF;
   TFile *f_idSF_GH ;
   TH2D *h2_idSF_BCDEF;
   TH2D *h2_idSF_GH;
   //Isolation SF
   TFile *f_isoSF_BCDEF ;
   TFile *f_isoSF_GH ;
   TH2D *h2_isoSF_BCDEF ;
   TH2D *h2_isoSF_GH ;
   //Btag
   BTagCalibration calib;
   BTagCalibrationReader reader;
   TH2D *l_eff,*c_eff,*b_eff;
   ////////////////////////////////////////////////////////

   CutflowRecoTuple(TTree *tree=0);
   virtual ~CutflowRecoTuple() ;
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
   double  ScaleLumiW(Int_t);
   double  ScaleLumiZ(Int_t);
   void    ReadMuEffFile(int);
   double  getMuonTrackSF(TGraphAsymmErrors *, double);
   double  GetMuEff(double, double, double, int);
   double  getMuonSF(TH2D *, double, double, double);   
   void    loadBtagEff();
   float   getBtagSF_1a(string, bool, float);
   
   ClassDef(CutflowRecoTuple,2);

};

#endif



//_____________________________________________________________________
CutflowRecoTuple::CutflowRecoTuple(TTree * /*tree*/)
{
  // Constructor

   Reset();
}
//_____________________________________________________________________
void CutflowRecoTuple::Reset()
{
   // Reset the data members to theit initial value


   fFileDir		= 0;
   fFile[0]		= 0;
   fProofFile[0]	= 0;
   fFile[1]		= 0;
   fProofFile[1]	= 0;
   fFile[2]		= 0;
   fProofFile[2]	= 0;

   hMuPt		= 0;
   hMuPt1		= 0;
   hMuPt2		= 0;
   hElePt		= 0;

   fNSyst		= 0;
   fNHist		= 0;
   hpresel_HT		= 0;
   hpresel_M3		= 0;
   hpresel_MET		= 0;
   hpresel_M_jjkF	= 0;
   hpresel_M_jj		= 0;
   hpresel_Nbjet	= 0;
   hpresel_Njet		= 0;
   hpresel_WtransMass	= 0;
   hpresel_elePhi	= 0;
   hpresel_elePt	= 0;
   hpresel_eleSCEta	= 0;
   hpresel_muEta	= 0;
   hpresel_muPhi	= 0;
   hpresel_muPt		= 0;
   hpresel_nVtx		= 0;

   fNTestHist		= 0;
   hCheck		= 0;
   
   fChain		= 0;
   fProcessed		= 0;

   fSample		= "";
   fSampleDir		= "";
   fSampleType		= "";
   fMode		= "";
   fYear		= 2016;
   fBasePath		= "";
   local_evtWeight      = 1.0;
   muSFa		= 0;
   muSFb		= 0;
   f_trackSF_BCDEF	= 0;
   f_trackSF_GH		= 0;
   tg_trackSF_BCDEF	= 0;
   tg_trackSF_GH	= 0;
   //trigger SF
   f_trigSF_BCDEF	= 0;
   f_trigSF_GH		= 0;
   h2_trigSF_BCDEF	= 0;
   h2_trigSF_GH		= 0;
   //Identification SF
   f_idSF_BCDEF		= 0;
   f_idSF_GH		= 0;
   h2_idSF_BCDEF	= 0;
   h2_idSF_GH		= 0;
   //Isolation SF
   f_isoSF_BCDEF	= 0;
   f_isoSF_GH		= 0;
   h2_isoSF_BCDEF	= 0;
   h2_isoSF_GH		= 0;
   
   isData		= false;
}
//_____________________________________________________________________
CutflowRecoTuple::~CutflowRecoTuple()
{
  if (fFile[0]) {
    SafeDelete(fFile[0]);
  }
  if (fFile[1]) {
    SafeDelete(fFile[1]);
  }
}
//_____________________________________________________________________
void CutflowRecoTuple::Init(TTree *tree)
{
   //   Set branch addresses

   Info("Init","tree: %p", tree);

   if (tree == 0) return;
   fChain    = tree;

   /* fChain->SetBranchAddress("muPt", &_muPt, &br_muPt); */
   /* fChain->SetBranchAddress("elePt", &_elePt, &br_elePt); */
   /* fChain->SetBranchAddress("nJet", &_nJet, &br_nJet); */
   /* fChain->SetBranchAddress("nBJet", &_nBJet, &br_nBJet); */
   /* fChain->SetBranchAddress("passPresel_Mu", &_passPresel_Mu, &br_passPresel_Mu); */

   /* fChain->SetBranchAddress("run"			, &_run				, &br_run			); */
   /* fChain->SetBranchAddress("event"			, &_event			, &br_event			);     */
   /* fChain->SetBranchAddress("lumis"			, &_lumis			, &br_lumis			); */
   fChain->SetBranchAddress("isData"			, &_isData			, &br_isData			); 
   /* fChain->SetBranchAddress("skim_entryId"		, &_skim_entryId       		, &br_skim_entryId     		);  */


   fChain->SetBranchAddress("PUweight"			, &_PUweight			, &br_PUweight			);
   /* fChain->SetBranchAddress("PUweight_Up"		, &_PUweight_Up			, &br_PUweight_Up		); */
   /* fChain->SetBranchAddress("PUweight_Do"		, &_PUweight_Do			, &br_PUweight_Do		); */


   /* fChain->SetBranchAddress("prefireSF"			, &_prefireSF			, &br_prefireSF			); */

   /* fChain->SetBranchAddress("prefireSF_Up"		, &_prefireSF_Up		, &br_prefireSF_Up		); */
   /* fChain->SetBranchAddress("prefireSF_Do"		, &_prefireSF_Do		, &br_prefireSF_Do		); */

   //fChain->SetBranchAddress("btagWeight"		, &_btagWeight			, &br_btagWeight		);
   fChain->SetBranchAddress("btagWeight_1a"		, &_btagWeight_1a		, &br_btagWeight_1a		);

   /* fChain->SetBranchAddress("btagWeight_b_Up"		, &_btagWeight_b_Up		, &br_btagWeight_b_Up		); */
   /* fChain->SetBranchAddress("btagWeight_b_Do"		, &_btagWeight_b_Do		, &br_btagWeight_b_Do		); */
   /* fChain->SetBranchAddress("btagWeight_l_Up"		, &_btagWeight_l_Up		, &br_btagWeight_l_Up		); */
   /* fChain->SetBranchAddress("btagWeight_l_Do"		, &_btagWeight_l_Do		, &br_btagWeight_l_Do		); */
   /* fChain->SetBranchAddress("btagWeight_1a_b_Up"	, &_btagWeight_1a_b_Up		, &br_btagWeight_1a_b_Up	); */
   /* fChain->SetBranchAddress("btagWeight_1a_b_Do"	, &_btagWeight_1a_b_Do		, &br_btagWeight_1a_b_Do	); */
   /* fChain->SetBranchAddress("btagWeight_1a_l_Up"	, &_btagWeight_1a_l_Up		, &br_btagWeight_1a_l_Up	); */
   /* fChain->SetBranchAddress("btagWeight_1a_l_Do"	, &_btagWeight_1a_l_Do		, &br_btagWeight_1a_l_Do	); */
   
   /* fChain->SetBranchAddress("btagSF"			, &_btagSF			, &br_btagSF			); */
   fChain->SetBranchAddress("muEffWeight"		, &_muEffWeight			, &br_muEffWeight		);
   /* fChain->SetBranchAddress("muEffWeight_IdIso"		, &_muEffWeight_IdIso		, &br_muEffWeight_IdIso		); */
   /* fChain->SetBranchAddress("muEffWeight_Trig"		, &_muEffWeight_Trig		, &br_muEffWeight_Trig		); */
   
   /* fChain->SetBranchAddress("muEffWeight_Up"		, &_muEffWeight_Up		, &br_muEffWeight_Up		); */
   /* fChain->SetBranchAddress("muEffWeight_Do"		, &_muEffWeight_Do		, &br_muEffWeight_Do		); */

   /* fChain->SetBranchAddress("muEffWeight_IdIso_Up"	, &_muEffWeight_IdIso_Up	, &br_muEffWeight_IdIso_Up	); */
   /* fChain->SetBranchAddress("muEffWeight_IdIso_Do"	, &_muEffWeight_IdIso_Do	, &br_muEffWeight_IdIso_Do	); */

   /* fChain->SetBranchAddress("muEffWeight_Trig_Up"	, &_muEffWeight_Trig_Up		, &br_muEffWeight_Trig_Up	); */
   /* fChain->SetBranchAddress("muEffWeight_Trig_Do"	, &_muEffWeight_Trig_Do		, &br_muEffWeight_Trig_Do	); */

   /* fChain->SetBranchAddress("eleEffWeight"		, &_eleEffWeight		, &br_eleEffWeight		); */
   /* fChain->SetBranchAddress("eleEffWeight_IdReco"	, &_eleEffWeight_IdReco		, &br_eleEffWeight_IdReco	); */
   /* fChain->SetBranchAddress("eleEffWeight_Trig"		, &_eleEffWeight_Trig		, &br_eleEffWeight_Trig		); */

   /* fChain->SetBranchAddress("eleEffWeight_Up"		, &_eleEffWeight_Up		, &br_eleEffWeight_Up		); */
   /* fChain->SetBranchAddress("eleEffWeight_Do"		, &_eleEffWeight_Do		, &br_eleEffWeight_Do		); */

   /* fChain->SetBranchAddress("eleEffWeight_IdReco_Up"	, &_eleEffWeight_IdReco_Up	, &br_eleEffWeight_IdReco_Up	); */
   /* fChain->SetBranchAddress("eleEffWeight_IdReco_Do"	, &_eleEffWeight_IdReco_Do	, &br_eleEffWeight_IdReco_Do	); */

   /* fChain->SetBranchAddress("eleEffWeight_Trig_Up"	, &_eleEffWeight_Trig_Up	, &br_eleEffWeight_Trig_Up	); */
   /* fChain->SetBranchAddress("eleEffWeight_Trig_Do"	, &_eleEffWeight_Trig_Do	, &br_eleEffWeight_Trig_Do	); */
   /* fChain->SetBranchAddress("q2weight_Up"		, &_q2weight_Up			, &br_q2weight_Up		); */
   /* fChain->SetBranchAddress("q2weight_Do"		, &_q2weight_Do			, &br_q2weight_Do		); */
   /* fChain->SetBranchAddress("q2weight_nominal"		, &_q2weight_nominal		, &br_q2weight_nominal		); */
   /* /\* fChain->SetBranchAddress("genScaleSystWeights"	, &_genScaleSystWeights		, &br_genScaleSystWeights	); *\/ */

   /* fChain->SetBranchAddress("pdfWeight"			, &_pdfWeight			, &br_pdfWeight			); */
   /* fChain->SetBranchAddress("pdfuncer"			, &_pdfuncer			, &br_pdfuncer			); */
   /* fChain->SetBranchAddress("pdfweight_Up"		, &_pdfweight_Up		, &br_pdfweight_Up		); */
   /* fChain->SetBranchAddress("pdfweight_Do"		, &_pdfweight_Do		, &br_pdfweight_Do		); */
   /* /\* fChain->SetBranchAddress("pdfSystWeight"		, &_pdfSystWeight		, &br_pdfSystWeight		); *\/ */

   /* fChain->SetBranchAddress("ISRweight_Up"		, &_ISRweight_Up		, &br_ISRweight_Up		); */
   /* fChain->SetBranchAddress("ISRweight_Do"		, &_ISRweight_Do		, &br_ISRweight_Do		); */

   /* fChain->SetBranchAddress("FSRweight_Up"		, &_FSRweight_Up		, &br_FSRweight_Up		); */
   /* fChain->SetBranchAddress("FSRweight_Do"		, &_FSRweight_Do		, &br_FSRweight_Do		); */

   fChain->SetBranchAddress("evtWeight"			, &_evtWeight			, &br_evtWeight			);      
   fChain->SetBranchAddress("lumiWeight"	       	, &_lumiWeight			, &br_lumiWeight	       	);      
   fChain->SetBranchAddress("sampleWeight"	       	, &_sampleWeight       		, &br_sampleWeight	       	);      
   fChain->SetBranchAddress("nMC_total"	       		, &_nMC_total			, &br_nMC_total	 	       	);      
   fChain->SetBranchAddress("nMC_totalUS"	       	, &_nMC_totalUS			, &br_nMC_totalUS	       	);      
   fChain->SetBranchAddress("xss"		       	, &_xss				, &br_xss		       	);      
   
   /* fChain->SetBranchAddress("nVtx"			, &_nVtx			, &br_nVtx			);  */
   /* fChain->SetBranchAddress("nGoodVtx"			, &_nGoodVtx			, &br_nGoodVtx			);  */
   fChain->SetBranchAddress("isPVGood"			, &_isPVGood			, &br_isPVGood			); 
   

   /* fChain->SetBranchAddress("genMET"			, &_genMET			, &br_genMET			); */

   fChain->SetBranchAddress("pfMET"			, &_pfMET			, &br_pfMET			);
   fChain->SetBranchAddress("pfMETPhi"			, &_pfMETPhi			, &br_pfMETPhi			); 
   /* fChain->SetBranchAddress("nu_px"			, &_nu_px			, &br_nu_px			); */
   /* fChain->SetBranchAddress("nu_py"			, &_nu_py			, &br_nu_py			); */
   /* fChain->SetBranchAddress("nu_pz"			, &_nu_pz			, &br_nu_pz			); */
   /* fChain->SetBranchAddress("nu_pz_other"		, &_nu_pz_other			, &br_nu_pz_other		); */
   /* fChain->SetBranchAddress("WtransMass"		, &_WtransMass			, &br_WtransMass		); */

   /* fChain->SetBranchAddress("chi2"			, &_chi2			, &br_chi2			); */
   /* fChain->SetBranchAddress("NDF"			, &_NDF				, &br_NDF			); */
   /* fChain->SetBranchAddress("Nbiter"			, &_Nbiter			, &br_Nbiter			); */
   /* fChain->SetBranchAddress("M_jj"			, &_M_jj			, &br_M_jj			); */
   /* fChain->SetBranchAddress("M_jjkF"			, &_M_jjkF			, &br_M_jjkF 			); */
   /* fChain->SetBranchAddress("bjlep_id"			, &_bjlep_id			, &br_bjlep_id			); */
   /* fChain->SetBranchAddress("bjhad_id"			, &_bjhad_id			, &br_bjhad_id			); */
   /* fChain->SetBranchAddress("cjhad_id"			, &_cjhad_id			, &br_cjhad_id			); */
   /* fChain->SetBranchAddress("sjhad_id"			, &_sjhad_id			, &br_sjhad_id			); */
   /* fChain->SetBranchAddress("lepPt"			, &_lepPt			, &br_lepPt			); */
   /* fChain->SetBranchAddress("lepEta"			, &_lepEta			, &br_lepEta			); */
   /* fChain->SetBranchAddress("lepPhi"			, &_lepPhi			, &br_lepPhi			); */
   /* fChain->SetBranchAddress("lepEnergy"			, &_lepEnergy			, &br_lepEnergy			); */
   /* fChain->SetBranchAddress("metPx"			, &_metPx			, &br_metPx			); */
   /* fChain->SetBranchAddress("metPy"			, &_metPy			, &br_metPy			); */
   /* fChain->SetBranchAddress("metPz"			, &_metPz			, &br_metPz			); */
   /* fChain->SetBranchAddress("jetBlepPt"			, &_jetBlepPt			, &br_jetBlepPt			); */
   /* fChain->SetBranchAddress("jetBlepEta"		, &_jetBlepEta			, &br_jetBlepEta		); */
   /* fChain->SetBranchAddress("jetBlepPhi"		, &_jetBlepPhi			, &br_jetBlepPhi		); */
   /* fChain->SetBranchAddress("jetBlepEnergy"		, &_jetBlepEnergy		, &br_jetBlepEnergy		); */
   /* fChain->SetBranchAddress("jetBhadPt"			, &_jetBhadPt			, &br_jetBhadPt			); */
   /* fChain->SetBranchAddress("jetBhadEta"		, &_jetBhadEta			, &br_jetBhadEta		); */
   /* fChain->SetBranchAddress("jetBhadPhi"		, &_jetBhadPhi			, &br_jetBhadPhi		); */
   /* fChain->SetBranchAddress("jetBhadEnergy"		, &_jetBhadEnergy		, &br_jetBhadEnergy		); */
   /* fChain->SetBranchAddress("jetChadPt"			, &_jetChadPt			, &br_jetChadPt			); */
   /* fChain->SetBranchAddress("jetChadEta"		, &_jetChadEta			, &br_jetChadEta		); */
   /* fChain->SetBranchAddress("jetChadPhi"		, &_jetChadPhi			, &br_jetChadPhi		); */
   /* fChain->SetBranchAddress("jetChadEnergy"		, &_jetChadEnergy		, &br_jetChadEnergy		); */
   /* fChain->SetBranchAddress("jetShadPt"			, &_jetShadPt			, &br_jetShadPt			); */
   /* fChain->SetBranchAddress("jetShadEta"		, &_jetShadEta			, &br_jetShadEta		); */
   /* fChain->SetBranchAddress("jetShadPhi"		, &_jetShadPhi			, &br_jetShadPhi		); */
   /* fChain->SetBranchAddress("jetShadEnergy"		, &_jetShadEnergy		, &br_jetShadEnergy		); */


   fChain->SetBranchAddress("nEle"			, &_nEle			, &br_nEle			);
   fChain->SetBranchAddress("nEleLoose"			, &_nEleLoose			, &br_nEleLoose			);
   /* fChain->SetBranchAddress("elePt"			, &_elePt			, &br_elePt			); */
   /* fChain->SetBranchAddress("elePhi"			, &_elePhi			, &br_elePhi			);  */
   /* fChain->SetBranchAddress("eleSCEta"			, &_eleSCEta			, &br_eleSCEta			);  */
   /* fChain->SetBranchAddress("elePFRelIso"		, &_elePFRelIso			, &br_elePFRelIso		);  */
   
   fChain->SetBranchAddress("nMu"			, &_nMu				, &br_nMu			); 
   fChain->SetBranchAddress("nMuLoose"			, &_nMuLoose		       	, &br_nMuLoose			); 
   fChain->SetBranchAddress("muPt"			, &_muPt			, &br_muPt			); 
   fChain->SetBranchAddress("muEta"			, &_muEta			, &br_muEta			);
   fChain->SetBranchAddress("muPhi"			, &_muPhi			, &br_muPhi			);
   fChain->SetBranchAddress("muPFRelIso"		, &_muPFRelIso			, &br_muPFRelIso		);
   fChain->SetBranchAddress("muRoccoR"			, &_muRoccoR			, &br_muRoccoR			);
   
   fChain->SetBranchAddress("nJet"			, &_nJet			, &br_nJet			);
   /* fChain->SetBranchAddress("nfwdJet"			, &_nfwdJet			, &br_nfwdJet			); */
   fChain->SetBranchAddress("nBJet"			, &_nBJet			, &br_nBJet			);

   fChain->SetBranchAddress("jetPt"			, &_jetPt			, &br_jetPt			);
   fChain->SetBranchAddress("jetEta"			, &_jetEta			, &br_jetEta			);
   /* fChain->SetBranchAddress("jetPhi"			, &_jetPhi			, &br_jetPhi			);  */
   /* fChain->SetBranchAddress("jetMass"			, &_jetMass			, &br_jetMass			); */

   fChain->SetBranchAddress("jetCSVV2"			, &_jetCSVV2			, &br_jetCSVV2			);
   /* fChain->SetBranchAddress("jetDeepB"			, &_jetDeepB			, &br_jetDeepB			); */
   /* fChain->SetBranchAddress("jetDeepC"			, &_jetDeepC			, &br_jetDeepC			); */
   fChain->SetBranchAddress("jetPartFlvr"		, &_jetPartFlvr			, &br_jetPartFlvr                );
   fChain->SetBranchAddress("jetHadFlvr"		, &_jetHadFlvr			, &br_jetHadFlvr                );
   /* fChain->SetBranchAddress("jetGenJetIdx"		, &_jetGenJetIdx		, &br_jetGenJetIdx		); */

   /* fChain->SetBranchAddress("fwdJetPt"			, &_fwdJetPt			, &br_fwdJetPt			); */
   /* fChain->SetBranchAddress("fwdJetEta"			, &_fwdJetEta			, &br_fwdJetEta			); */
   /* fChain->SetBranchAddress("fwdJetPhi"			, &_fwdJetPhi			, &br_fwdJetPhi			); */
   /* fChain->SetBranchAddress("fwdJetMass"		, &_fwdJetMass			, &br_fwdJetMass		); */


   /* fChain->SetBranchAddress("M3"			, &_M3				, &br_M3			);  */
   /* fChain->SetBranchAddress("HT"			, &_HT				, &br_HT			);  */
   
   fChain->SetBranchAddress("nLHEPart"			, &_nLHEPart			, &br_nLHEPart			);
   
   /* fChain->SetBranchAddress("passPresel_Ele"		, &_passPresel_Ele		, &br_passPresel_Ele		);  */
   fChain->SetBranchAddress("passPresel_Mu"		, &_passPresel_Mu		, &br_passPresel_Mu		);
   /* fChain->SetBranchAddress("passAll_Ele"		, &_passAll_Ele			, &br_passAll_Ele		);  */
   /* fChain->SetBranchAddress("passAll_Mu"		, &_passAll_Mu			, &br_passAll_Mu		); */
   fChain->SetBranchAddress("passTrigger_ele"		, &_passTrigger_ele		, &br_passTrigger_ele		);
   fChain->SetBranchAddress("passTrigger_mu"		, &_passTrigger_mu		, &br_passTrigger_mu		);
   fChain->SetBranchAddress("passFilter"		, &_passFilter			, &br_passFilter		);

}

//_____________________________________________________________________
Bool_t CutflowRecoTuple::Notify()
{
//   called when loading a new file
//   get branch pointers
  
  double luminosity = 35921.0;
  string fname(fChain->GetCurrentFile()->GetName());
  fname = fname.substr(fname.find_last_of("/")+1,fname.size());
  fname = fname.substr(0,fname.find("_RecoKinTuple"));
  fSampleType = fname;
  
  Info("Notify","processing sample %s and file: %s",fSampleType.Data(), fChain->GetCurrentFile()->GetName());  
  
  local_evtWeight = getEvtWeight(fname, fYear, luminosity);
  
  return kTRUE;
}

