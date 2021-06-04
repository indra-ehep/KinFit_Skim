/**********************************************************************
 Created on : 12/04/2021
 Purpose    : Analyse the Reco tree for To Perform the KinFit again.
              (format adapted from h1analysis)
 Author     : Indranil Das, Visiting Fellow
 Email      : indranil.das@cern.ch | indra.ehep@gmail.com
**********************************************************************/

#ifndef PerformKinFit_h
#define PerformKinFit_h

#include <TROOT.h>
#include <TChain.h>
#include <TEntryList.h>
#include <TFile.h>
#include <TProofOutputFile.h>
#include <TSelector.h>
#include <vector>
//#include "KinFit.C"

#include "TMath.h"
#include "TLorentzVector.h"

#include "PhysicsTools/KinFitter/interface/TFitConstraintM.h"
#include "PhysicsTools/KinFitter/interface/TFitConstraintEp.h"
#include "PhysicsTools/KinFitter/interface/TFitParticleEtEtaPhi.h"
#include "PhysicsTools/KinFitter/interface/TFitParticleEScaledMomDev.h"
#include "PhysicsTools/KinFitter/interface/TFitParticleMCMomDev.h"
#include "PhysicsTools/KinFitter/interface/TKinFitter.h"

#include <iostream>


class  TH1F;
class  TH2F;

typedef struct  {
  double chi2, mass, mW, A, B;
  int ndf, nb_iter;
  //int bjlep_id, bjhad_id, cjhad_id, sjhad_id;
  TLorentzVector leptonAF, neutrinoAF, bjlepAF, bjhadAF, cjhadAF, sjhadAF;  
  TLorentzVector leptonBF, neutrinoBF, bjlepBF, bjhadBF, cjhadBF, sjhadBF;    
} Chi2Array;

bool compareChi2Array(Chi2Array i1, Chi2Array i2)
{
  return (i1.chi2 < i2.chi2);
}

class METzCalculator {

 public:
  /// constructor
  METzCalculator();
  //METzCalculator(const edm::ParameterSEt& iConf);
  /// destructor
  virtual ~METzCalculator();
  /// Set MET
  void SetMET(TLorentzVector MET) {
    MET_ = MET;
  }
  /// Set Muon
  void SetLepton(TLorentzVector lepton) {
    lepton_ = lepton;
  }
  /// Set lepton type. The default (set in the constructor) is "muon"
  /// to be compatible with earlier code.
  /// The values are from the 2010 PDG tables.
  void SetLeptonType(std::string leptonName) {
    if(leptonName == "muon")      leptonMass_ = 0.105658367;
    if(leptonName == "electron")  leptonMass_ = 0.00051099891;
    if(leptonName == "tau")       leptonMass_ = 1.77682;
  }

  /// Calculate MEz
  /// options to choose roots from quadratic equation:
  /// type = 0 (defalut): if real roots, pick the one nearest to
  ///                     the lepton Pz except when the Pz so chosen
  ///                     is greater than 300 GeV in which case pick
  ///                     the most central root.
  /// type = 1: if real roots, choose the one closest to the lepton Pz
  ///           if complex roots, use only the real part.
  /// type = 2: if real roots, choose the most central solution.
  ///           if complex roots, use only the real part.
  /// type = 3: if real roots, pick the largest value of the cosine*
  double Calculate(int type = 0);
  /// check for complex root
  bool IsComplex() const { return isComplex_; };
  double getOther() const { return otherSol_; };
  void Print() {
    std::cout << " METzCalculator: pxmu = " << lepton_.Px() << " pzmu= " << lepton_.Pz() << std::endl;
    std::cout << " METzCalculator: pxnu = " << MET_.Px() << " pynu= " << MET_.Py() << std::endl;
  }
	
 private:
	
  bool isComplex_;
  TLorentzVector lepton_;
  TLorentzVector MET_;
  double otherSol_;
  double leptonMass_;
};

class KinFit{

 public:

    enum LeptonType {kElectron, kMuon, kTau};

    KinFit(){
      Clear();
      mTop	    = 172.76;
      isComplex     = false;
    }
    
    // The following are the mandatory setters
    /////////////////////////////////////////////////////////////////////////////
    // For a given year
    void SetBtagThresh(double thresh_){ btagThresh		= thresh_;}

    // For a given event
    void Clear(){
      	//--------------------
	_nu_px	     = -9999.0;
	_nu_py	     = -9999.0;
	_nu_pz	     = -9999.0; 
	_nu_pz_other = -9999.0; 
	_nu_pt	     = -9999.0;
	_nu_phi	     = -9999.0;
	leptonType   = kTau;

	jets.clear();
	jetsRes.clear();
	btag.clear();
	//--------------------
	nCombinations = 0;
	leptonAF.clear(); 
	neutrinoAF.clear(); 

	bjlepAF.clear();
	bjhadAF.clear(); 
	cjhadAF.clear(); 
	sjhadAF.clear();

	blep_id.clear();
	bhad_id.clear();
	chad_id.clear();
	shad_id.clear();

	Chi2.clear();
	NDF.clear();
	Nb_Iter.clear();

	leptonUM.clear();
	neutrinoUM.clear();
	bjlepUM.clear(); 
	bjhadUM.clear();
	cjhadUM.clear(); 
	sjhadUM.clear();
	
	ReslepEta.clear();
	ReslepPhi.clear();
	ResneuEta.clear();
	ResneuPhi.clear();
	ResbjlepEta.clear();
	ResbjlepPhi.clear();
	ResbjhadEta.clear();
	ResbjhadPhi.clear();
	RescjhadEta.clear();
	RescjhadPhi.clear();
	RessjhadEta.clear();
	RessjhadPhi.clear(); 
	
    }    
    void SetJetVector(std::vector<TLorentzVector> jets_){ jets	= jets_;}
    void SetJetResVector(std::vector<double> jetres_){ jetsRes	= jetres_;}
    void SetBtagVector(std::vector<double> jetsTag_){ btag	= jetsTag_;}
    void SetLepton(TLorentzVector lepton_){ lepton		= lepton_;}
    void SetLeptonType(LeptonType ltype_){ leptonType		= ltype_;} 
    void SetMET(double px_, double py_, double pz_, double pz_other_) {  
      _nu_px	   = px_;
      _nu_py	   = py_;
      _nu_pz	   = pz_;
      _nu_pz_other = pz_other_;
    }
    void SetMETPtPhi(double MET_pt_ , double MET_phi_) {
      _nu_pt	   = MET_pt_;
      _nu_phi	   = MET_phi_;
    }
    /////////////////////////////////////////////////////////////////////////////

    // The following are the optional setters
    /////////////////////////////////////////////////////////////////////////////
    void SetTopMass(double topMass) { mTop = topMass ;}
    /////////////////////////////////////////////////////////////////////////////

    // The return of fit function is "true" if fit is converged
    /////////////////////////////////////////////////////////////////////////////
    bool Fit();
    /////////////////////////////////////////////////////////////////////////////
    
    // The following are the minimal getters
    /////////////////////////////////////////////////////////////////////////////
    unsigned int	GetNCombinations()		{ return nCombinations;}
    TLorentzVector	GetLepton(unsigned int i)	{ return leptonAF.at(i);}
    TLorentzVector	GetNeutrino(unsigned int i)	{ return neutrinoAF.at(i);}
    TLorentzVector	GetBLepton(unsigned int i)	{ return bjlepAF.at(i);}
    TLorentzVector	GetBHadron(unsigned int i)	{ return bjhadAF.at(i);}
    TLorentzVector	GetCHadron(unsigned int i)	{ return cjhadAF.at(i);}
    TLorentzVector	GetSHadron(unsigned int i)	{ return sjhadAF.at(i);}
    unsigned int	GetJetID_BLep(unsigned int i)	{ return blep_id.at(i);}
    unsigned int	GetJetID_BHad(unsigned int i)	{ return bhad_id.at(i);}
    unsigned int	GetJetID_CHad(unsigned int i)	{ return chad_id.at(i);}
    unsigned int	GetJetID_SHad(unsigned int i)	{ return shad_id.at(i);}
    /////////////////////////////////////////////////////////////////////////////

    // The following are the additional getters
    /////////////////////////////////////////////////////////////////////////////
    TLorentzVector	GetLeptonUM(unsigned int i)	{ return leptonUM.at(i);}
    TLorentzVector	GetNeutrinoUM(unsigned int i)	{ return neutrinoUM.at(i);}
    TLorentzVector	GetBLeptonUM(unsigned int i)	{ return bjlepUM.at(i);}
    TLorentzVector	GetBHadronUM(unsigned int i)	{ return bjhadUM.at(i);}
    TLorentzVector	GetCHadronUM(unsigned int i)	{ return cjhadUM.at(i);}
    TLorentzVector	GetSHadronUM(unsigned int i)	{ return sjhadUM.at(i);}
    double		GetChi2(unsigned int i)		{ return Chi2.at(i); }
    int			GetNDF(unsigned int i)		{ return NDF.at(i); }
    int			GetNumberOfIter(unsigned int i)	{ return Nb_Iter.at(i); }	// Number of iterations to converge
    double              GetResLepEta(unsigned int i)    { return ReslepEta.at(i);}
    double              GetResLepPhi(unsigned int i)    { return ReslepPhi.at(i);}
    double              GetResNeuEta(unsigned int i)    { return ResneuEta.at(i);}
    double              GetResNeuPhi(unsigned int i)    { return ResneuPhi.at(i);}
    double              GetResBjLepEta(unsigned int i)  { return ResbjlepEta.at(i);}
    double              GetResBjLepPhi(unsigned int i)  { return ResbjlepPhi.at(i);}
    double              GetResBjHadEta(unsigned int i)  { return ResbjhadEta.at(i);}
    double              GetResBjHadPhi(unsigned int i)  { return ResbjhadPhi.at(i);}
    double              GetResCjHadEta(unsigned int i)  { return RescjhadEta.at(i);}
    double              GetResCjHadPhi(unsigned int i)  { return RescjhadPhi.at(i);}
    double              GetResSjHadEta(unsigned int i)  { return RessjhadEta.at(i);}
    double              GetResSjHadPhi(unsigned int i)  { return RessjhadPhi.at(i);}
    bool		IsComplex()                     { return isComplex; };
    /////////////////////////////////////////////////////////////////////////////
    
    struct PtDescending
    {
      inline bool operator() (const TLorentzVector& vec1, const TLorentzVector& vec2)
      {
        return (vec1.Pt() > vec2.Pt());
      }
    };

 private:
    
    void	print(TKinFitter *fitter);
    
    // The elements of covariance matrix setup following CMS NOTE AN 2005/005
    double	ErrEt(float Et, float Eta) ;
    double	ErrEta(float Et, float Eta) ;
    double	ErrPhi(float Et, float Eta) ;
	
    // The elements of covariance matrix setup following TopQuarkAnalysis/TopKinFitter
    int udscResolution(double et, double eta, double& resEt, double& resEta, double& resPhi);
    int bjetResolution(double et, double eta, double& resEt, double& resEta, double& resPhi);
    int muonResolution(double et, double eta, double& resEt, double& resEta, double& resPhi);
    int elecResolution(double et, double eta, double& resEt, double& resEta, double& resPhi);
    int metResolution(double et, double& resEt, double& resEta, double& resPhi);
    int JetEnergyResolution(double eta, double& JERbase, double& JERdown, double& JERup);

    // The following variables are set by mandatory setters
    // To be set for a given year
    double			btagThresh;
    // To be set for a given event
    std::vector<TLorentzVector> jets;
    std::vector<double>		jetsRes;
    std::vector<double>		btag;
    double			_nu_px, _nu_py, _nu_pz, _nu_pz_other, _nu_pt, _nu_phi; 
    TLorentzVector		lepton;
    LeptonType			leptonType;

    // The following variables are optional setters
    double			mTop;
    
    // The following variables are minimal getters
    unsigned int		nCombinations;                                                  // Number of converged combinations
    std::vector<TLorentzVector> leptonAF, neutrinoAF, bjlepAF, bjhadAF, cjhadAF, sjhadAF;	// Four vectors after KinFit
    std::vector<unsigned int>	blep_id, bhad_id, chad_id, shad_id;
    
    // The following variables are additional getters
    std::vector<double>		Chi2;
    std::vector<int>		NDF, Nb_Iter ;
    std::vector<TLorentzVector>	leptonUM, neutrinoUM, bjlepUM, bjhadUM, cjhadUM, sjhadUM;	// Unmodified four vectors before KinFit
    std::vector<double>		ReslepEta, ReslepPhi, ResneuEta, ResneuPhi, ResbjlepEta, ResbjlepPhi, ResbjhadEta, ResbjhadPhi, RescjhadEta, RescjhadPhi, RessjhadEta, RessjhadPhi ; 
    bool			isComplex;
};


class PerformKinFit : public TSelector {
   public :
   
   //File operation pointers
   ////////////////////////////////////////////////////////
   TFile            *fFile;
   TProofOutputFile *fProofFile; // For optimized merging of the ntuple
   
   //Declaration of histograms
   ////////////////////////////////////////////////////////
   TH1F           *hMuPt;//!
   TH1F           *hMjj;//!
   TH1F           *hMjjkF;//!
   TH1F           *hMjjkFsc;//!
   TH1F           *hMjjkF3s;//!
   TH1F           *hMjjkF_ms;//!
   TH1F           *hMjjkF_01;//!
   TH1F           *hMjjkF_02;//!
   TH1F           *hMjjkF_03;//!
   TH1F           *hMjjkF_04;//!
   TH1F           *hMjjkF_05;//!
   TH1F           *hMjjkF_06;//!
   TH1F           *hMjjkF_07;//!
   TH1F           *hMjjkF_08;//!
   TH1F           *hMjjkF_09;//!
   TH1F           *hMjjkF_10;//!
   TH1F           *hMjjkF_11;//!
   TH1F           *hMjjkF_12;//!
   TH1F           *hMjjkF_13;//!
   TH1F           *hMjjkF_14;//!
   TH1F           *hMjjkF_15;//!
   TH1F           *hMjjkF_16;//!
   TH1F           *hMjjkF_17;//!
   TH1F           *hNlep;//!
   TH1F           *hChi2;//!
   TH1F           *hMinChi2;//!
   TH1F           *h2MinChi2;//!
   TH1F           *h3MinChi2;//!
   TH1F           *h4MinChi2;//!
   TH1F           *h5MinChi2;//!
   TH1F           *hNbiter;//!
   TH1F           *hNbCombiBRD;//!
   TH1F           *hNbCombiARD;//!
   TH1F           *hdRSigLep;//!
   TH1F           *hdRSigNeu;//!
   TH1F           *hdRSigBjHad;//!
   TH1F           *hdRSigBjLep;//!
   TH1F           *hdRSigCjHad;//!
   TH1F           *hdRSigSjHad;//!
   TH1F           *hMindRSigLep;//!
   TH1F           *hMindRSigNeu;//!
   TH1F           *hMindRSigBjHad;//!
   TH1F           *hMindRSigBjLep;//!
   TH1F           *hMindRSigCjHad;//!
   TH1F           *hMindRSigSjHad;//!

   TH1F           *hPtvsdEtLep;//!
   TH1F           *hPtvsdEtBjHad;//!
   TH1F           *hPtvsdEtBjLep;//!
   TH1F           *hPtvsdEtCjHad;//!
   TH1F           *hPtvsdEtSjHad;//!

   TH1F           *hPtvsdetaLep;//!
   TH1F           *hPtvsdetaBjHad;//!
   TH1F           *hPtvsdetaBjLep;//!
   TH1F           *hPtvsdetaCjHad;//!
   TH1F           *hPtvsdetaSjHad;//!

   TH1F           *hPtvsdPhiLep;//!
   TH1F           *hPtvsdPhiBjHad;//!
   TH1F           *hPtvsdPhiBjLep;//!
   TH1F           *hPtvsdPhiCjHad;//!
   TH1F           *hPtvsdPhiSjHad;//!
     
   TH1F           *hMinPtvsdEtLep;//!
   TH1F           *hMinPtvsdEtBjHad;//!
   TH1F           *hMinPtvsdEtBjLep;//!
   TH1F           *hMinPtvsdEtCjHad;//!
   TH1F           *hMinPtvsdEtSjHad;//!

   TH1F           *hMinPtvsdetaLep;//!
   TH1F           *hMinPtvsdetaBjHad;//!
   TH1F           *hMinPtvsdetaBjLep;//!
   TH1F           *hMinPtvsdetaCjHad;//!
   TH1F           *hMinPtvsdetaSjHad;//!

   TH1F           *hMinPtvsdPhiLep;//! 
   TH1F           *hMinPtvsdPhiBjHad;//!
   TH1F           *hMinPtvsdPhiBjLep;//!
   TH1F           *hMinPtvsdPhiCjHad;//!
   TH1F           *hMinPtvsdPhiSjHad;//!
  
   //---------------------------------------------------
   TH1F           **hPtBFLep;//!
   TH1F           **hPtBFNeu;//!
   TH1F           **hPtBFBjHad;//!
   TH1F           **hPtBFBjLep;//!
   TH1F           **hPtBFCjHad;//!
   TH1F           **hPtBFSjHad;//!
   
   TH1F           **hPtAFLep;//!
   TH1F           **hPtAFNeu;//!
   TH1F           **hPtAFBjHad;//!
   TH1F           **hPtAFBjLep;//!
   TH1F           **hPtAFCjHad;//!
   TH1F           **hPtAFSjHad;//!
   
   TH1F           **hPtvsRatioPtLep;//!
   TH1F           **hPtvsRatioPtNeu;//!
   TH1F           **hPtvsRatioPtBjHad;//!
   TH1F           **hPtvsRatioPtBjLep;//!
   TH1F           **hPtvsRatioPtCjHad;//!
   TH1F           **hPtvsRatioPtSjHad;//!
   
   TH1F           **hMinPtBFLep;//!
   TH1F           **hMinPtBFNeu;//!
   TH1F           **hMinPtBFBjHad;//!
   TH1F           **hMinPtBFBjLep;//!
   TH1F           **hMinPtBFCjHad;//!
   TH1F           **hMinPtBFSjHad;//!
   
   TH1F           **hMinPtAFLep;//!
   TH1F           **hMinPtAFNeu;//!
   TH1F           **hMinPtAFBjHad;//!
   TH1F           **hMinPtAFBjLep;//!
   TH1F           **hMinPtAFCjHad;//!
   TH1F           **hMinPtAFSjHad;//!

   TH1F           **hMinPtvsRatioPtLep;//!
   TH1F           **hMinPtvsRatioPtNeu;//!
   TH1F           **hMinPtvsRatioPtBjHad;//!
   TH1F           **hMinPtvsRatioPtBjLep;//!
   TH1F           **hMinPtvsRatioPtCjHad;//!
   TH1F           **hMinPtvsRatioPtSjHad;//!

   TH1F           *hPtTopLep;//!
   TH1F           *hPtTopHad;//!
   TH2F           *hPtTopHL;//!
   TH1F           *hAssymPt;//!
   TH1F           *hNeuEta_Ptlow;//!
   TH1F           *hNeuEta_Pthigh;//!
   TH1F           *hMuEta_Ptlow;//!
   TH1F           *hMuEta_Pthigh;//!

   TH1F           *hHadTop;//!
   TH1F           *hLepTop;//!
   TH1F           *hEtaNeu;//!
  
   TH1F           *hIsNeuComplex;//!
   TH1F           *hMW;//!

   TH1F           **hDiffAvg;//!
   TH1F           **hMinDiffAvg;//!
   TH1F           *hbtagweight_1a;//
   
   //Declaration of output tree
   ////////////////////////////////////////////////////////
   TTree          *outputTree;//!

   std::vector<bool>	 _selStep;
   ////////////////////////////////////////////////////////

   Long64_t        fProcessed;//!
   TTree          *fChain;//!    //pointer to the analyzed TTree or TChain

   //Declaration of leaves types
   ////////////////////////////////////////////////////////
  Int_t		_run = 0 ;
  Long64_t	_event = 0 ;
  Int_t		_lumis = 0 ;
  Bool_t	_isData = 0 ;

  Float_t	_PUweight = 0 ;
  Float_t	_PUweight_Up = 0 ;
  Float_t	_PUweight_Do = 0 ;
	
  Float_t		 _q2weight_Up = 0 ;
  Float_t		 _q2weight_Do = 0 ;
  Float_t		 _q2weight_nominal = 0 ;
  std::vector<float>	*_genScaleSystWeights = 0 ;

  Float_t		 _pdfWeight = 0 ;
  Float_t		 _pdfuncer = 0 ;
  Float_t		 _pdfweight_Up = 0 ;
  Float_t		 _pdfweight_Do = 0 ;
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
  Int_t		_nVtx = 0 ;
  Int_t		_nGoodVtx = 0 ;

  Float_t	_genMET = 0 ;
        
  Float_t	_pfMET = 0 ;
  Float_t	_pfMETPhi = 0 ;
  Float_t	_nu_px = 0 ;
  Float_t	_nu_py = 0 ;
  Float_t	_nu_pz = 0 ;
  Float_t	_nu_pz_other = 0 ;
  Float_t	_WtransMass = 0 ;
  
  int		_kFType = 0;
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
  Float_t	_jetBlepPtUM = 0 ;
  Float_t	_jetBlepEtaUM = 0 ;
  Float_t	_jetBlepPhiUM = 0 ;
  Float_t	_jetBlepEnergyUM = 0 ;
  Float_t	_jetBhadPtUM = 0 ;
  Float_t	_jetBhadEtaUM = 0 ;
  Float_t	_jetBhadPhiUM = 0 ;
  Float_t	_jetBhadEnergyUM = 0 ;
  Float_t	_jetChadPtUM = 0 ;
  Float_t	_jetChadEtaUM = 0 ;
  Float_t	_jetChadPhiUM = 0 ;
  Float_t	_jetChadEnergyUM = 0 ;
  Float_t	_jetShadPtUM = 0 ;
  Float_t	_jetShadEtaUM = 0 ;
  Float_t	_jetShadPhiUM = 0 ;
  Float_t	_jetShadEnergyUM = 0 ;
  
  Int_t			 _nEle = 0 ;
  Int_t			 _nEleLoose = 0 ;
  std::vector<float>	 *_elePt = 0 ;
  std::vector<float>	 *_elePhi = 0 ;
  std::vector<float>	 *_eleSCEta = 0 ;
  std::vector<float>	 *_elePFRelIso = 0 ;
  
  Int_t			 _nMu = 0 ;
  Int_t			 _nMuLoose = 0 ;
  std::vector<float>	 *_muPt = 0 ;
  std::vector<float>	 *_muEta = 0 ;
  std::vector<float>	 *_muPhi = 0 ;
  std::vector<float>	 *_muPFRelIso = 0 ;
	
  Int_t			 _nJet = 0 ;
  Int_t			 _nBJet = 0 ;
  std::vector<float>	 *_jetPt = 0 ;
  std::vector<float>	 *_jetEta = 0 ;
  std::vector<float>	 *_jetPhi = 0 ;
  std::vector<float>	 *_jetMass = 0 ;

  Int_t			 _nfwdJet = 0 ;
  std::vector<float>	 *_fwdJetPt = 0 ;
  std::vector<float>	 *_fwdJetEta = 0 ;
  std::vector<float>	 *_fwdJetPhi = 0 ;
  std::vector<float>	 *_fwdJetMass = 0 ;

  std::vector<float>	 *_jetCMVA = 0 ;
  std::vector<float>	 *_jetCSVV2 = 0 ;
  std::vector<float>	 *_jetDeepB = 0 ;
  std::vector<float>	 *_jetDeepC = 0 ;

  std::vector<int>	 *_jetGenJetIdx = 0 ;

  Int_t			 _nGenJet = 0 ;
  std::vector<float>	 *_genJetPt = 0 ;
  std::vector<float>	 *_genJetEta = 0 ;
  std::vector<float>	 *_genJetPhi = 0 ;
  std::vector<float>	 *_genJetMass = 0 ;
  std::vector<float>	 *_genJetPartonFlavour = 0 ;
  std::vector<float>	 *_genJetHadronFlavour = 0 ;

  Int_t			 _nGenPart = 0 ;
  std::vector<float>	 *_genPt = 0 ;
  std::vector<float>	 *_genEta = 0 ;
  std::vector<float>	 *_genPhi = 0 ;
  std::vector<float>	 *_genMass = 0 ;
  std::vector<int>	 *_genStatus = 0 ;
  std::vector<int>	 *_genStatusFlag = 0 ;
  std::vector<int>	 *_genPDGID = 0 ;
  std::vector<int>	 *_genMomIdx = 0 ;

  double		 _M3 = 0 ;
  double		 _HT = 0 ;
  bool			 _passPresel_Ele = 0 ;
  bool			 _passPresel_Mu = 0 ;
  bool			 _passAll_Ele = 0 ;
  bool			 _passAll_Mu = 0 ;
   ////////////////////////////////////////////////////////


   //List of branches
   ////////////////////////////////////////////////////////
   TBranch	*br_run				= 0 ;
   TBranch	*br_event			= 0 ;
   TBranch	*br_lumis			= 0 ;
   TBranch	*br_isData			= 0 ;
   
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
   /* TBranch   *br_evtWeightAlt		= 0 ; */
   /* TBranch   *br_lumiWeightAlt		= 0 ; */

   TBranch	*br_nVtx			= 0 ;
   TBranch   *br_nGoodVtx			= 0 ;
   
   TBranch	*br_genMET			= 0 ;
   
   TBranch      *br_pfMET	       		= 0 ;
   TBranch	*br_pfMETPhi			= 0 ;
   TBranch	*br_nu_px			= 0 ;
   TBranch	*br_nu_py			= 0 ;
   TBranch	*br_nu_pz			= 0 ;
   TBranch	*br_nu_pz_other			= 0 ;
   TBranch	*br_WtransMass			= 0 ;
  
   //TBranch	*br_kFType			= 0 ;
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
   TBranch	*br_jetBlepPtUM			= 0 ;
   TBranch	*br_jetBlepEtaUM		= 0 ;
   TBranch	*br_jetBlepPhiUM		= 0 ;
   TBranch	*br_jetBlepEnergyUM		= 0 ;
   TBranch	*br_jetBhadPtUM			= 0 ;
   TBranch	*br_jetBhadEtaUM		= 0 ;
   TBranch	*br_jetBhadPhiUM		= 0 ;
   TBranch	*br_jetBhadEnergyUM		= 0 ;
   TBranch	*br_jetChadPtUM			= 0 ;
   TBranch	*br_jetChadEtaUM		= 0 ;
   TBranch	*br_jetChadPhiUM		= 0 ;
   TBranch	*br_jetChadEnergyUM		= 0 ;
   TBranch	*br_jetShadPtUM			= 0 ;
   TBranch	*br_jetShadEtaUM		= 0 ;
   TBranch	*br_jetShadPhiUM		= 0 ;
   TBranch	*br_jetShadEnergyUM		= 0 ;
   
   
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
   TBranch   *br_dileptonsample			= 0 ;

   /* TBranch  *bvpt1				= 0; */
   /* TBranch  *bvpt2				= 0; */
   /* TBranch  *bnjet				= 0; */
   /* TBranch  *bnbjet				= 0; */
   /* TBranch  *bpassmu				= 0; */

   ////////////////////////////////////////////////////////
   //Assorted
   TString fSample;
   TString fSampleDir;
   TString fMode;
   Int_t fYear;
   bool isData ;
   ////////////////////////////////////////////////////////
   KinFit kinFit ; 
   std::vector<TLorentzVector> jetVectors;
   std::vector<double> jetBtagVectors;
   TLorentzVector jetVector;
   TLorentzVector lepVector;
   TLorentzVector	leptonBF, neutrinoBF, bjlepBF, bjhadBF, cjhadBF, sjhadBF;
   TLorentzVector	leptonAF, neutrinoAF, bjlepAF, bjhadAF, cjhadAF, sjhadAF;
   TLorentzVector	lepTopAF, hadTopAF;
   double  fmTop ;
   double  fchi2cut ;
   double  fptmin, fptmax ;
   int fNPtBins;
   float   *fPtmin,*fPtmax;
   int fNDiffAvgBins;
   float   *fDAmin,*fDAmax;
   ////////////////////////////////////////////////////////

   PerformKinFit(TTree *tree=0);
   virtual ~PerformKinFit() ;
   void    Reset();
   
   int     Version() const {return 1;}
   void    Begin(TTree *tree);
   void    SlaveBegin(TTree *tree);
   void    Init(TTree *tree);
   void    InitOutBranches();
   Bool_t  Notify();
   Bool_t  Process(Long64_t entry);
   void    SetOption(const char *option) { fOption = option; }
   void    SetObject(TObject *obj) { fObject = obj; }
   void    SetInputList(TList *input) {fInput = input;}
   TList  *GetOutputList() const { return fOutput; }
   void    SlaveTerminate();
   void    Terminate();
   
   void    GetArguments();
   //Int_t   CreateHistoArrays();
   Int_t   FindBinIndex(float, float *, float *, int);

   ClassDef(PerformKinFit,2);

};

#endif

/// constructor
METzCalculator::METzCalculator() {
  isComplex_ = false;
  otherSol_ = 0.;
  leptonMass_ = 0.105658367;
}

/// destructor
METzCalculator::~METzCalculator() {
}

/// member functions
double METzCalculator::Calculate(int type) {

  double M_W  = 80.379;
  double M_mu =  leptonMass_;
  double emu = lepton_.E();
  double pxmu = lepton_.Px();
  double pymu = lepton_.Py();
  double pzmu = lepton_.Pz();
  double pxnu = MET_.Px();
  double pynu = MET_.Py();
  double pznu = 0.;
  otherSol_ = 0.;
		
  double a = M_W*M_W - M_mu*M_mu + 2.0*pxmu*pxnu + 2.0*pymu*pynu;
  double A = 4.0*(emu*emu - pzmu*pzmu);
  double B = -4.0*a*pzmu;
  double C = 4.0*emu*emu*(pxnu*pxnu + pynu*pynu) - a*a;

  double tmproot = B*B - 4.0*A*C;

  if (tmproot<0) {
    isComplex_= true;
    pznu = - B/(2*A); // take real part of complex roots
    otherSol_ = pznu;
    //std::cout << " Neutrino Solutions: complex, real part " << pznu << std::endl;
  }
  else {
    isComplex_ = false;
    double tmpsol1 = (-B + TMath::Sqrt(tmproot))/(2.0*A);
    double tmpsol2 = (-B - TMath::Sqrt(tmproot))/(2.0*A);

    //std::cout << " Neutrino Solutions: " << tmpsol1 << ", " << tmpsol2 << std::endl;
			
    if (type == 0 ) {
      // two real roots, pick the one closest to pz of muon
      if (TMath::Abs(tmpsol2-pzmu) < TMath::Abs(tmpsol1-pzmu)) { pznu = tmpsol2; otherSol_ = tmpsol1;}
      else { pznu = tmpsol1; otherSol_ = tmpsol2; } 
      // if pznu is > 300 pick the most central root
      /* if ( pznu > 300. ) { */
      /* 	if (TMath::Abs(tmpsol1)<TMath::Abs(tmpsol2) ) { pznu = tmpsol1; otherSol_ = tmpsol2; } */
      /* 	else { pznu = tmpsol2; otherSol_ = tmpsol1; } */
      /* } */
    }
    if (type == 1 ) {
      // two real roots, pick the one closest to pz of muon
      if (TMath::Abs(tmpsol2-pzmu) < TMath::Abs(tmpsol1-pzmu)) { pznu = tmpsol2; otherSol_ = tmpsol1; }
      else {pznu = tmpsol1; otherSol_ = tmpsol2; }
    }
    if (type == 2 ) {
      // pick the most central root.
      if (TMath::Abs(tmpsol1)<TMath::Abs(tmpsol2) ) { pznu = tmpsol1; otherSol_ = tmpsol2; }
      else { pznu = tmpsol2; otherSol_ = tmpsol1; }
    }
    if (type == 3 ) {
      // pick the largest value of the cosine
      TVector3 p3w, p3mu;
      p3w.SetXYZ(pxmu+pxnu, pymu+pynu, pzmu+ tmpsol1);
      p3mu.SetXYZ(pxmu, pymu, pzmu );
				
      double sinthcm1 = 2.*(p3mu.Perp(p3w))/M_W;
      p3w.SetXYZ(pxmu+pxnu, pymu+pynu, pzmu+ tmpsol2);
      double sinthcm2 = 2.*(p3mu.Perp(p3w))/M_W;

      double costhcm1 = TMath::Sqrt(1. - sinthcm1*sinthcm1);
      double costhcm2 = TMath::Sqrt(1. - sinthcm2*sinthcm2);

      if ( costhcm1 > costhcm2 ) { pznu = tmpsol1; otherSol_ = tmpsol2; }
      else { pznu = tmpsol2;otherSol_ = tmpsol1; }
    }
		
  }

  //Particle neutrino;
  //neutrino.setP4( LorentzVector(pxnu, pynu, pznu, TMath::Sqrt(pxnu*pxnu + pynu*pynu + pznu*pznu ))) ;

  return pznu;
}

//_____________________________________________________________________
PerformKinFit::PerformKinFit(TTree * /*tree*/)
{
  // Constructor

   Reset();
}
//_____________________________________________________________________
void PerformKinFit::Reset()
{
   // Reset the data members to theit initial value
  
  fFile	     = 0;
  fProofFile = 0;
  outputTree = 0;  
  
  hMuPt		 = 0;
  hMjj		 = 0;
  hMjjkF	 = 0;
  hMjjkFsc	 = 0;
  hMjjkF3s	 = 0;
  hNlep		 = 0;
  hChi2		 = 0;
  hMjjkF_ms	 = 0;
  hMjjkF_01	 = 0;
  hMjjkF_02	 = 0;
  hMjjkF_03	 = 0;
  hMjjkF_04	 = 0;
  hMjjkF_05	 = 0;
  hMjjkF_06	 = 0;
  hMjjkF_07	 = 0;
  hMjjkF_08	 = 0;
  hMjjkF_09	 = 0;
  hMjjkF_10	 = 0;
  hMjjkF_11	 = 0;
  hMjjkF_12	 = 0;
  hMjjkF_13	 = 0;
  hMjjkF_14	 = 0;
  hMjjkF_15	 = 0;
  hMjjkF_16	 = 0;
  hMjjkF_17	 = 0;
  hMinChi2	 = 0;
  h2MinChi2	 = 0;
  h3MinChi2	 = 0;
  h4MinChi2	 = 0;
  h5MinChi2	 = 0;
  hNbiter	 = 0;
  hNbCombiBRD	 = 0;
  hNbCombiARD	 = 0;
  hdRSigLep	 = 0;
  hdRSigNeu	 = 0;
  hdRSigBjHad	 = 0;
  hdRSigBjLep	 = 0;
  hdRSigCjHad	 = 0;
  hdRSigSjHad	 = 0;
  hMindRSigLep	 = 0;
  hMindRSigNeu	 = 0;
  hMindRSigBjHad = 0;
  hMindRSigBjLep = 0;
  hMindRSigCjHad = 0;
  hMindRSigSjHad = 0;

  hPtvsdEtLep	 = 0;
  hPtvsdEtBjHad	 = 0;
  hPtvsdEtBjLep	 = 0;
  hPtvsdEtCjHad	 = 0;
  hPtvsdEtSjHad	 = 0;

  hPtvsdetaLep	 = 0;
  hPtvsdetaBjHad = 0;
  hPtvsdetaBjLep = 0;
  hPtvsdetaCjHad = 0;
  hPtvsdetaSjHad = 0;

  hPtvsdPhiLep	 = 0;
  hPtvsdPhiBjHad = 0;
  hPtvsdPhiBjLep = 0;
  hPtvsdPhiCjHad = 0;
  hPtvsdPhiSjHad = 0;
  
  hPtvsRatioPtLep   = 0;
  hPtvsRatioPtNeu   = 0;
  hPtvsRatioPtBjHad = 0;
  hPtvsRatioPtBjLep = 0;
  hPtvsRatioPtCjHad = 0;
  hPtvsRatioPtSjHad = 0;

  hMinPtvsdEtLep   = 0;
  hMinPtvsdEtBjHad = 0;
  hMinPtvsdEtBjLep = 0;
  hMinPtvsdEtCjHad = 0;
  hMinPtvsdEtSjHad = 0;

  hMinPtvsdetaLep   = 0;
  hMinPtvsdetaBjHad = 0;
  hMinPtvsdetaBjLep = 0;
  hMinPtvsdetaCjHad = 0;
  hMinPtvsdetaSjHad = 0;

  hMinPtvsdPhiLep   = 0; 
  hMinPtvsdPhiBjHad = 0;
  hMinPtvsdPhiBjLep = 0;
  hMinPtvsdPhiCjHad = 0;
  hMinPtvsdPhiSjHad = 0;
  
  hMinPtvsRatioPtLep   = 0;
  hMinPtvsRatioPtNeu   = 0;
  hMinPtvsRatioPtBjHad = 0;
  hMinPtvsRatioPtBjLep = 0;
  hMinPtvsRatioPtCjHad = 0;
  hMinPtvsRatioPtSjHad = 0;

  hPtBFLep   = 0;
  hPtBFNeu   = 0;
  hPtBFBjHad = 0;
  hPtBFBjLep = 0;
  hPtBFCjHad = 0;
  hPtBFSjHad = 0;
   
  hPtAFLep   = 0;
  hPtAFNeu   = 0;
  hPtAFBjHad = 0;
  hPtAFBjLep = 0;
  hPtAFCjHad = 0;
  hPtAFSjHad = 0;
  
  hMinPtBFLep	= 0;
  hMinPtBFNeu	= 0;
  hMinPtBFBjHad = 0;
  hMinPtBFBjLep = 0;
  hMinPtBFCjHad = 0;
  hMinPtBFSjHad = 0;
   
  hMinPtAFLep	= 0;
  hMinPtAFNeu	= 0;
  hMinPtAFBjHad = 0;
  hMinPtAFBjLep = 0;
  hMinPtAFCjHad = 0;
  hMinPtAFSjHad = 0;
  
  hPtTopLep	 = 0;
  hPtTopHad	 = 0;
  hPtTopHL	 = 0;
  hAssymPt	 = 0;
  hNeuEta_Ptlow	 = 0;
  hNeuEta_Pthigh = 0;
  hMuEta_Ptlow	 = 0;
  hMuEta_Pthigh	 = 0;
  
  hHadTop = 0;
  hLepTop = 0;
  hEtaNeu = 0;
  
  hIsNeuComplex = 0;
  hMW		= 0;
  hbtagweight_1a = 0;

  fNPtBins	= 7;
  fPtmin	= 0 ;		//30
  fPtmax	= 0 ;		//40
  fNDiffAvgBins = 6;
  fDAmin	= 0;
  fDAmax	= 0;

  hDiffAvg    = 0;
  hMinDiffAvg = 0;

  _selStep.clear();
  jetVectors.clear();
  jetBtagVectors.clear();

  fmTop		= 172.6;
  fchi2cut     	= 100.0;
  fptmin        = 10.0 ; //30
  fptmax        = 40.0 ; //40
  
  fChain	= 0;
  fProcessed	= 0;
  
  fSample	= "";
  fSampleDir	= "";
  fMode		= "";
  fYear		= 0;
  isData	= false;
}
//_____________________________________________________________________
PerformKinFit::~PerformKinFit()
{
  if (fFile) {
    SafeDelete(fFile);
  }
  /* if (fFile[1]) { */
  /*   SafeDelete(fFile[1]); */
  /* } */
}
//_____________________________________________________________________
void PerformKinFit::Init(TTree *tree)
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
   
   fChain->SetBranchAddress("run"			, &_run				, &br_run			);
   fChain->SetBranchAddress("event"			, &_event			, &br_event			);    
   fChain->SetBranchAddress("lumis"			, &_lumis			, &br_lumis			);
   fChain->SetBranchAddress("isData"			, &_isData			, &br_isData			); 
   fChain->SetBranchAddress("PUweight"			, &_PUweight			, &br_PUweight			);

   fChain->SetBranchAddress("PUweight_Up"		, &_PUweight_Up			, &br_PUweight_Up		);
   fChain->SetBranchAddress("PUweight_Do"		, &_PUweight_Do			, &br_PUweight_Do		);


   fChain->SetBranchAddress("prefireSF"			, &_prefireSF			, &br_prefireSF			);

   fChain->SetBranchAddress("prefireSF_Up"		, &_prefireSF_Up		, &br_prefireSF_Up		);
   fChain->SetBranchAddress("prefireSF_Do"		, &_prefireSF_Do		, &br_prefireSF_Do		);

   fChain->SetBranchAddress("btagWeight"		, &_btagWeight			, &br_btagWeight		);
   fChain->SetBranchAddress("btagWeight_1a"		, &_btagWeight_1a		, &br_btagWeight_1a		);

   fChain->SetBranchAddress("btagWeight_b_Up"		, &_btagWeight_b_Up		, &br_btagWeight_b_Up		);
   fChain->SetBranchAddress("btagWeight_b_Do"		, &_btagWeight_b_Do		, &br_btagWeight_b_Do		);
   fChain->SetBranchAddress("btagWeight_l_Up"		, &_btagWeight_l_Up		, &br_btagWeight_l_Up		);
   fChain->SetBranchAddress("btagWeight_l_Do"		, &_btagWeight_l_Do		, &br_btagWeight_l_Do		);
   fChain->SetBranchAddress("btagWeight_1a_b_Up"	, &_btagWeight_1a_b_Up		, &br_btagWeight_1a_b_Up	);
   fChain->SetBranchAddress("btagWeight_1a_b_Do"	, &_btagWeight_1a_b_Do		, &br_btagWeight_1a_b_Do	);
   fChain->SetBranchAddress("btagWeight_1a_l_Up"	, &_btagWeight_1a_l_Up		, &br_btagWeight_1a_l_Up	);
   fChain->SetBranchAddress("btagWeight_1a_l_Do"	, &_btagWeight_1a_l_Do		, &br_btagWeight_1a_l_Do	);

   fChain->SetBranchAddress("btagSF"			, &_btagSF			, &br_btagSF			);
   fChain->SetBranchAddress("muEffWeight"		, &_muEffWeight			, &br_muEffWeight		);
   fChain->SetBranchAddress("muEffWeight_IdIso"		, &_muEffWeight_IdIso		, &br_muEffWeight_IdIso		);
   fChain->SetBranchAddress("muEffWeight_Trig"		, &_muEffWeight_Trig		, &br_muEffWeight_Trig		);

   fChain->SetBranchAddress("muEffWeight_Up"		, &_muEffWeight_Up		, &br_muEffWeight_Up		);
   fChain->SetBranchAddress("muEffWeight_Do"		, &_muEffWeight_Do		, &br_muEffWeight_Do		);

   fChain->SetBranchAddress("muEffWeight_IdIso_Up"	, &_muEffWeight_IdIso_Up	, &br_muEffWeight_IdIso_Up	);
   fChain->SetBranchAddress("muEffWeight_IdIso_Do"	, &_muEffWeight_IdIso_Do	, &br_muEffWeight_IdIso_Do	);

   fChain->SetBranchAddress("muEffWeight_Trig_Up"	, &_muEffWeight_Trig_Up		, &br_muEffWeight_Trig_Up	);
   fChain->SetBranchAddress("muEffWeight_Trig_Do"	, &_muEffWeight_Trig_Do		, &br_muEffWeight_Trig_Do	);

   fChain->SetBranchAddress("eleEffWeight"		, &_eleEffWeight		, &br_eleEffWeight		);
   fChain->SetBranchAddress("eleEffWeight_IdReco"	, &_eleEffWeight_IdReco		, &br_eleEffWeight_IdReco	);
   fChain->SetBranchAddress("eleEffWeight_Trig"		, &_eleEffWeight_Trig		, &br_eleEffWeight_Trig		);

   fChain->SetBranchAddress("eleEffWeight_Up"		, &_eleEffWeight_Up		, &br_eleEffWeight_Up		);
   fChain->SetBranchAddress("eleEffWeight_Do"		, &_eleEffWeight_Do		, &br_eleEffWeight_Do		);

   fChain->SetBranchAddress("eleEffWeight_IdReco_Up"	, &_eleEffWeight_IdReco_Up	, &br_eleEffWeight_IdReco_Up	);
   fChain->SetBranchAddress("eleEffWeight_IdReco_Do"	, &_eleEffWeight_IdReco_Do	, &br_eleEffWeight_IdReco_Do	);

   fChain->SetBranchAddress("eleEffWeight_Trig_Up"	, &_eleEffWeight_Trig_Up	, &br_eleEffWeight_Trig_Up	);
   fChain->SetBranchAddress("eleEffWeight_Trig_Do"	, &_eleEffWeight_Trig_Do	, &br_eleEffWeight_Trig_Do	);
   fChain->SetBranchAddress("q2weight_Up"		, &_q2weight_Up			, &br_q2weight_Up		);
   fChain->SetBranchAddress("q2weight_Do"		, &_q2weight_Do			, &br_q2weight_Do		);
   fChain->SetBranchAddress("q2weight_nominal"		, &_q2weight_nominal		, &br_q2weight_nominal		);
   fChain->SetBranchAddress("genScaleSystWeights"	, &_genScaleSystWeights		, &br_genScaleSystWeights	);

   fChain->SetBranchAddress("pdfWeight"			, &_pdfWeight			, &br_pdfWeight			);
   fChain->SetBranchAddress("pdfuncer"			, &_pdfuncer			, &br_pdfuncer			);
   fChain->SetBranchAddress("pdfweight_Up"		, &_pdfweight_Up		, &br_pdfweight_Up		);
   fChain->SetBranchAddress("pdfweight_Do"		, &_pdfweight_Do		, &br_pdfweight_Do		);
   fChain->SetBranchAddress("pdfSystWeight"		, &_pdfSystWeight		, &br_pdfSystWeight		);

   fChain->SetBranchAddress("ISRweight_Up"		, &_ISRweight_Up		, &br_ISRweight_Up		);
   fChain->SetBranchAddress("ISRweight_Do"		, &_ISRweight_Do		, &br_ISRweight_Do		);

   fChain->SetBranchAddress("FSRweight_Up"		, &_FSRweight_Up		, &br_FSRweight_Up		);
   fChain->SetBranchAddress("FSRweight_Do"		, &_FSRweight_Do		, &br_FSRweight_Do		);

   fChain->SetBranchAddress("evtWeight"			, &_evtWeight			, &br_evtWeight			);      

   fChain->SetBranchAddress("nVtx"			, &_nVtx			, &br_nVtx			); 
   fChain->SetBranchAddress("nGoodVtx"			, &_nGoodVtx			, &br_nGoodVtx			); 
   fChain->SetBranchAddress("genMET"			, &_genMET			, &br_genMET			);

   fChain->SetBranchAddress("pfMET"			, &_pfMET			, &br_pfMET			);
   fChain->SetBranchAddress("pfMETPhi"			, &_pfMETPhi			, &br_pfMETPhi			); 
   fChain->SetBranchAddress("nu_px"			, &_nu_px			, &br_nu_px			);
   fChain->SetBranchAddress("nu_py"			, &_nu_py			, &br_nu_py			);
   fChain->SetBranchAddress("nu_pz"			, &_nu_pz			, &br_nu_pz			);
   fChain->SetBranchAddress("nu_pz_other"		, &_nu_pz_other			, &br_nu_pz_other		);
   fChain->SetBranchAddress("WtransMass"		, &_WtransMass			, &br_WtransMass		);

   fChain->SetBranchAddress("chi2"			, &_chi2			, &br_chi2			);
   fChain->SetBranchAddress("NDF"			, &_NDF				, &br_NDF			);
   fChain->SetBranchAddress("Nbiter"			, &_Nbiter			, &br_Nbiter			);
   fChain->SetBranchAddress("M_jj"			, &_M_jj			, &br_M_jj			);
   fChain->SetBranchAddress("M_jjkF"			, &_M_jjkF			, &br_M_jjkF 			);
   fChain->SetBranchAddress("bjlep_id"			, &_bjlep_id			, &br_bjlep_id			);
   fChain->SetBranchAddress("bjhad_id"			, &_bjhad_id			, &br_bjhad_id			);
   fChain->SetBranchAddress("cjhad_id"			, &_cjhad_id			, &br_cjhad_id			);
   fChain->SetBranchAddress("sjhad_id"			, &_sjhad_id			, &br_sjhad_id			);
   fChain->SetBranchAddress("lepPt"			, &_lepPt			, &br_lepPt			);
   fChain->SetBranchAddress("lepEta"			, &_lepEta			, &br_lepEta			);
   fChain->SetBranchAddress("lepPhi"			, &_lepPhi			, &br_lepPhi			);
   fChain->SetBranchAddress("lepEnergy"			, &_lepEnergy			, &br_lepEnergy			);
   fChain->SetBranchAddress("metPx"			, &_metPx			, &br_metPx			);
   fChain->SetBranchAddress("metPy"			, &_metPy			, &br_metPy			);
   fChain->SetBranchAddress("metPz"			, &_metPz			, &br_metPz			);
   fChain->SetBranchAddress("jetBlepPt"			, &_jetBlepPt			, &br_jetBlepPt			);
   fChain->SetBranchAddress("jetBlepEta"		, &_jetBlepEta			, &br_jetBlepEta		);
   fChain->SetBranchAddress("jetBlepPhi"		, &_jetBlepPhi			, &br_jetBlepPhi		);
   fChain->SetBranchAddress("jetBlepEnergy"		, &_jetBlepEnergy		, &br_jetBlepEnergy		);
   fChain->SetBranchAddress("jetBhadPt"			, &_jetBhadPt			, &br_jetBhadPt			);
   fChain->SetBranchAddress("jetBhadEta"		, &_jetBhadEta			, &br_jetBhadEta		);
   fChain->SetBranchAddress("jetBhadPhi"		, &_jetBhadPhi			, &br_jetBhadPhi		);
   fChain->SetBranchAddress("jetBhadEnergy"		, &_jetBhadEnergy		, &br_jetBhadEnergy		);
   fChain->SetBranchAddress("jetChadPt"			, &_jetChadPt			, &br_jetChadPt			);
   fChain->SetBranchAddress("jetChadEta"		, &_jetChadEta			, &br_jetChadEta		);
   fChain->SetBranchAddress("jetChadPhi"		, &_jetChadPhi			, &br_jetChadPhi		);
   fChain->SetBranchAddress("jetChadEnergy"		, &_jetChadEnergy		, &br_jetChadEnergy		);
   fChain->SetBranchAddress("jetShadPt"			, &_jetShadPt			, &br_jetShadPt			);
   fChain->SetBranchAddress("jetShadEta"		, &_jetShadEta			, &br_jetShadEta		);
   fChain->SetBranchAddress("jetShadPhi"		, &_jetShadPhi			, &br_jetShadPhi		);
   fChain->SetBranchAddress("jetShadEnergy"		, &_jetShadEnergy		, &br_jetShadEnergy		);


   fChain->SetBranchAddress("nEle"			, &_nEle			, &br_nEle			); 
   fChain->SetBranchAddress("elePt"			, &_elePt			, &br_elePt			);
   fChain->SetBranchAddress("elePhi"			, &_elePhi			, &br_elePhi			); 
   fChain->SetBranchAddress("eleSCEta"			, &_eleSCEta			, &br_eleSCEta			); 
   fChain->SetBranchAddress("elePFRelIso"		, &_elePFRelIso			, &br_elePFRelIso		); 

   fChain->SetBranchAddress("nMu"			, &_nMu				, &br_nMu			); 
   fChain->SetBranchAddress("muPt"			, &_muPt			, &br_muPt			); 
   fChain->SetBranchAddress("muEta"			, &_muEta			, &br_muEta			);
   fChain->SetBranchAddress("muPhi"			, &_muPhi			, &br_muPhi			);
   fChain->SetBranchAddress("muPFRelIso"		, &_muPFRelIso			, &br_muPFRelIso		);
    
   fChain->SetBranchAddress("nJet"			, &_nJet			, &br_nJet			); 
   fChain->SetBranchAddress("nfwdJet"			, &_nfwdJet			, &br_nfwdJet			);
   fChain->SetBranchAddress("nBJet"			, &_nBJet			, &br_nBJet			); 
   fChain->SetBranchAddress("jetPt"			, &_jetPt			, &br_jetPt			);
   fChain->SetBranchAddress("jetEta"			, &_jetEta			, &br_jetEta			); 
   fChain->SetBranchAddress("jetPhi"			, &_jetPhi			, &br_jetPhi			); 
   fChain->SetBranchAddress("jetMass"			, &_jetMass			, &br_jetMass			);

   fChain->SetBranchAddress("jetDeepB"			, &_jetDeepB			, &br_jetDeepB			);
   fChain->SetBranchAddress("jetDeepC"			, &_jetDeepC			, &br_jetDeepC			);
   fChain->SetBranchAddress("jetGenJetIdx"		, &_jetGenJetIdx		, &br_jetGenJetIdx		);

   fChain->SetBranchAddress("fwdJetPt"			, &_fwdJetPt			, &br_fwdJetPt			);
   fChain->SetBranchAddress("fwdJetEta"			, &_fwdJetEta			, &br_fwdJetEta			);
   fChain->SetBranchAddress("fwdJetPhi"			, &_fwdJetPhi			, &br_fwdJetPhi			);
   fChain->SetBranchAddress("fwdJetMass"		, &_fwdJetMass			, &br_fwdJetMass		);


   fChain->SetBranchAddress("M3"			, &_M3				, &br_M3			); 
   fChain->SetBranchAddress("HT"			, &_HT				, &br_HT			); 

   fChain->SetBranchAddress("passPresel_Ele"		, &_passPresel_Ele		, &br_passPresel_Ele		); 
   fChain->SetBranchAddress("passPresel_Mu"		, &_passPresel_Mu		, &br_passPresel_Mu		);
   fChain->SetBranchAddress("passAll_Ele"		, &_passAll_Ele			, &br_passAll_Ele		); 
   fChain->SetBranchAddress("passAll_Mu"		, &_passAll_Mu			, &br_passAll_Mu		);

}
//_____________________________________________________________________

void PerformKinFit::InitOutBranches(){
  
    outputTree->Branch("run"			, &_run				);
    outputTree->Branch("event"			, &_event			);    
    outputTree->Branch("lumis"			, &_lumis			);
    outputTree->Branch("isData"			, &_isData			);
    
    outputTree->Branch("PUweight"		, &_PUweight			);
    //if (!isSystematicRun){
	outputTree->Branch("PUweight_Up"	, &_PUweight_Up			);
	outputTree->Branch("PUweight_Do"	, &_PUweight_Do			);
    //}

    //if (!isSystematicRun){
	outputTree->Branch("q2weight_Up"	, &_q2weight_Up			);
	outputTree->Branch("q2weight_Do"	, &_q2weight_Do			);
	outputTree->Branch("q2weight_nominal"	, &_q2weight_nominal		);
	outputTree->Branch("genScaleSystWeights", &_genScaleSystWeights		);

	outputTree->Branch("pdfWeight"		, &_pdfWeight			);
	outputTree->Branch("pdfuncer"		, &_pdfuncer			);
	outputTree->Branch("pdfweight_Up"	, &_pdfweight_Up		);
	outputTree->Branch("pdfweight_Do"	, &_pdfweight_Do		);
	outputTree->Branch("pdfSystWeight"	, &_pdfSystWeight		);

	outputTree->Branch("ISRweight_Up"	, &_ISRweight_Up		);
	outputTree->Branch("ISRweight_Do"	, &_ISRweight_Do		);

	outputTree->Branch("FSRweight_Up"	, &_FSRweight_Up		);
	outputTree->Branch("FSRweight_Do"	, &_FSRweight_Do		);
     //}

    /* outputTree->Branch("prefireSF"		, &_prefireSF			); */
    /* if (!isSystematicRun){ */
    /* 	outputTree->Branch("prefireSF_Up"	, &_prefireSF_Up		); */
    /* 	outputTree->Branch("prefireSF_Do"	, &_prefireSF_Do		); */
    /* } */

    outputTree->Branch("btagWeight"		, &_btagWeight			);
    outputTree->Branch("btagWeight_1a"		, &_btagWeight_1a		);
    //if (!isSystematicRun){
	outputTree->Branch("btagWeight_b_Up"	, &_btagWeight_b_Up		);
	outputTree->Branch("btagWeight_b_Do"	, &_btagWeight_b_Do		);
	outputTree->Branch("btagWeight_l_Up"	, &_btagWeight_l_Up		);
	outputTree->Branch("btagWeight_l_Do"	, &_btagWeight_l_Do		);
	outputTree->Branch("btagWeight_1a_b_Up"	, &_btagWeight_1a_b_Up		);
	outputTree->Branch("btagWeight_1a_b_Do"	, &_btagWeight_1a_b_Do		);
	outputTree->Branch("btagWeight_1a_l_Up"	, &_btagWeight_1a_l_Up		);
	outputTree->Branch("btagWeight_1a_l_Do"	, &_btagWeight_1a_l_Do		);
    //}
    outputTree->Branch("btagSF"			, &_btagSF			);
    //if (!isSystematicRun){
      outputTree->Branch("btagSF_b_Up"		, &_btagSF_b_Up			);
      outputTree->Branch("btagSF_b_Do"		, &_btagSF_b_Do			);
      outputTree->Branch("btagSF_l_Up"		, &_btagSF_l_Up			);
      outputTree->Branch("btagSF_l_Do"		, &_btagSF_l_Do			);
    //}
    outputTree->Branch("muEffWeight"		, &_muEffWeight			);
    outputTree->Branch("muEffWeight_IdIso"	, &_muEffWeight_IdIso		);
    outputTree->Branch("muEffWeight_Trig"	, &_muEffWeight_Trig		);
    //if (!isSystematicRun){
	outputTree->Branch("muEffWeight_Up"	, &_muEffWeight_Up		);
	outputTree->Branch("muEffWeight_Do"	, &_muEffWeight_Do		);

	outputTree->Branch("muEffWeight_IdIso_Up", &_muEffWeight_IdIso_Up	);
	outputTree->Branch("muEffWeight_IdIso_Do", &_muEffWeight_IdIso_Do	);

	outputTree->Branch("muEffWeight_Trig_Up", &_muEffWeight_Trig_Up		);
	outputTree->Branch("muEffWeight_Trig_Do", &_muEffWeight_Trig_Do		);
    //}
    outputTree->Branch("eleEffWeight"		, &_eleEffWeight		);
    outputTree->Branch("eleEffWeight_IdReco"	, &_eleEffWeight_IdReco		);
    outputTree->Branch("eleEffWeight_Trig"	, &_eleEffWeight_Trig		);
    //if (!isSystematicRun){
	outputTree->Branch("eleEffWeight_Up"	, &_eleEffWeight_Up		);
	outputTree->Branch("eleEffWeight_Do"	, &_eleEffWeight_Do		);

	outputTree->Branch("eleEffWeight_IdReco_Up", &_eleEffWeight_IdReco_Up	);
	outputTree->Branch("eleEffWeight_IdReco_Do", &_eleEffWeight_IdReco_Do	);

	outputTree->Branch("eleEffWeight_Trig_Up", &_eleEffWeight_Trig_Up	);
	outputTree->Branch("eleEffWeight_Trig_Do", &_eleEffWeight_Trig_Do	);
    //}

    outputTree->Branch("evtWeight"		, &_evtWeight			);      
    outputTree->Branch("lumiWeight"		, &_lumiWeight			);      
    outputTree->Branch("nVtx"			, &_nVtx			); 
    outputTree->Branch("nGoodVtx"		, &_nGoodVtx			); 
    //if (!isSystematicRun){
	outputTree->Branch("genMET"		, &_genMET			); 
    //}
    outputTree->Branch("pfMET"			, &_pfMET			);
    outputTree->Branch("pfMETPhi"		, &_pfMETPhi			); 
    outputTree->Branch("nu_px"			, &_nu_px			);
    outputTree->Branch("nu_py"			, &_nu_py			);
    outputTree->Branch("nu_pz"			, &_nu_pz			);
    outputTree->Branch("nu_pz_other"		, &_nu_pz_other			);
    outputTree->Branch("WtransMass"		, &_WtransMass			);

    /* outputTree->Branch("hasConv"		, &_hasConv			); */
    /* outputTree->Branch("hasRDPass"	       	, &_hasRDPass			); */
    /* outputTree->Branch("ltype"		        , &_ltype			); */
    /* outputTree->Branch("ltypekF"       	        , &_ltypekF			); */
    outputTree->Branch("kFType"			, &_kFType			);
    outputTree->Branch("chi2"			, &_chi2			);
    outputTree->Branch("NDF"			, &_NDF				);
    outputTree->Branch("Nbiter"			, &_Nbiter			);
    outputTree->Branch("M_jj"			, &_M_jj			);
    outputTree->Branch("M_jjkF"			, &_M_jjkF			);
    /* outputTree->Branch("bjlep_id"		, &_bjlep_id			); */
    /* outputTree->Branch("bjhad_id"		, &_bjhad_id			); */
    /* outputTree->Branch("cjhad_id"		, &_cjhad_id			); */
    /* outputTree->Branch("sjhad_id"		, &_sjhad_id			); */
    outputTree->Branch("lepPt"			, &_lepPt			);
    outputTree->Branch("lepEta"			, &_lepEta			);
    outputTree->Branch("lepPhi"			, &_lepPhi			);
    outputTree->Branch("lepEnergy"		, &_lepEnergy			);
    outputTree->Branch("metPx"			, &_metPx			);
    outputTree->Branch("metPy"			, &_metPy			);
    outputTree->Branch("metPz"			, &_metPz			);
    outputTree->Branch("jetBlepPt"		, &_jetBlepPt			);
    outputTree->Branch("jetBlepEta"		, &_jetBlepEta			);
    outputTree->Branch("jetBlepPhi"		, &_jetBlepPhi			);
    outputTree->Branch("jetBlepEnergy"		, &_jetBlepEnergy		);
    outputTree->Branch("jetBhadPt"		, &_jetBhadPt			);
    outputTree->Branch("jetBhadEta"		, &_jetBhadEta			);
    outputTree->Branch("jetBhadPhi"		, &_jetBhadPhi			);
    outputTree->Branch("jetBhadEnergy"		, &_jetBhadEnergy		);
    outputTree->Branch("jetChadPt"		, &_jetChadPt			);
    outputTree->Branch("jetChadEta"		, &_jetChadEta			);
    outputTree->Branch("jetChadPhi"		, &_jetChadPhi			);
    outputTree->Branch("jetChadEnergy"		, &_jetChadEnergy		);
    outputTree->Branch("jetShadPt"		, &_jetShadPt			);
    outputTree->Branch("jetShadEta"		, &_jetShadEta			);
    outputTree->Branch("jetShadPhi"		, &_jetShadPhi			);
    outputTree->Branch("jetShadEnergy"		, &_jetShadEnergy		);
    outputTree->Branch("jetBlepPtUM"		, &_jetBlepPtUM			);
    outputTree->Branch("jetBlepEtaUM"		, &_jetBlepEtaUM	       	);
    outputTree->Branch("jetBlepPhiUM"		, &_jetBlepPhiUM       		);
    outputTree->Branch("jetBlepEnergyUM"	, &_jetBlepEnergyUM		);
    outputTree->Branch("jetBhadPtUM"		, &_jetBhadPtUM			);
    outputTree->Branch("jetBhadEtaUM"		, &_jetBhadEtaUM       		);
    outputTree->Branch("jetBhadPhiUM"		, &_jetBhadPhiUM       		);
    outputTree->Branch("jetBhadEnergyUM"	, &_jetBhadEnergyUM		);
    outputTree->Branch("jetChadPtUM"		, &_jetChadPtUM			);
    outputTree->Branch("jetChadEtaUM"		, &_jetChadEtaUM       		);
    outputTree->Branch("jetChadPhiUM"		, &_jetChadPhiUM       		);
    outputTree->Branch("jetChadEnergyUM"	, &_jetChadEnergyUM		);
    outputTree->Branch("jetShadPtUM"		, &_jetShadPtUM			);
    outputTree->Branch("jetShadEtaUM"		, &_jetShadEtaUM       		);
    outputTree->Branch("jetShadPhiUM"		, &_jetShadPhiUM       		);
    outputTree->Branch("jetShadEnergyUM"	, &_jetShadEnergyUM		);

    outputTree->Branch("nEle"			, &_nEle			); 
    outputTree->Branch("nEleLoose"		, &_nEleLoose			); 
    outputTree->Branch("elePt"			, &_elePt			);
    outputTree->Branch("elePhi"			, &_elePhi			); 
    outputTree->Branch("eleSCEta"		, &_eleSCEta			); 
    outputTree->Branch("elePFRelIso"		, &_elePFRelIso			); 

    outputTree->Branch("nMu"			, &_nMu				); 
    outputTree->Branch("nMuLoose"		, &_nMuLoose			); 
    outputTree->Branch("muPt"			, &_muPt			); 
    outputTree->Branch("muEta"			, &_muEta			);
    outputTree->Branch("muPhi"			, &_muPhi			);
    outputTree->Branch("muPFRelIso"		, &_muPFRelIso			);
    
    /* outputTree->Branch("nJet"			, &_nJet			);  */
    /* outputTree->Branch("nBJet"			, &_nBJet			);  */
    /* outputTree->Branch("jetPt"			, &_jetPt			); */
    /* outputTree->Branch("jetEta"			, &_jetEta			);  */
    /* outputTree->Branch("jetPhi"			, &_jetPhi			);  */
    /* outputTree->Branch("jetMass"		, &_jetMass			); */

    /* outputTree->Branch("nfwdJet"		, &_nfwdJet			); */
    /* outputTree->Branch("fwdJetPt"		, &_fwdJetPt			); */
    /* outputTree->Branch("fwdJetEta"		, &_fwdJetEta			); */
    /* outputTree->Branch("fwdJetPhi"		, &_fwdJetPhi			); */
    /* outputTree->Branch("fwdJetMass"		, &_fwdJetMass			); */
    /* //if (!isSystematicRun){ */
    /* 	/\* outputTree->Branch("jetCMVA"		, &_jetCMVA			); *\/ */
    /* 	/\* outputTree->Branch("jetCSVV2"	, &_jetCSVV2			); *\/ */
    /* 	outputTree->Branch("jetDeepB"		, &_jetDeepB			); */
    /* 	outputTree->Branch("jetDeepC"		, &_jetDeepC			); */
    /* 	outputTree->Branch("jetGenJetIdx"	, &_jetGenJetIdx		); */
    /* //} */
	
    /* //if (!tree->isData_ && !isSystematicRun){ */
    /* 	outputTree->Branch("nGenPart"		, &_nGenPart			);  */
    /* 	outputTree->Branch("genPt"		, &_genPt			); */
    /* 	outputTree->Branch("genEta"		, &_genEta			);  */
    /* 	outputTree->Branch("genPhi"		, &_genPhi			);  */
    /* 	outputTree->Branch("genMass"		, &_genMass			);  */
    /* 	outputTree->Branch("genStatus"		, &_genStatus			); */
    /* 	outputTree->Branch("genStatusFlag"	, &_genStatusFlag		); */
    /* 	outputTree->Branch("genPDGID"		, &_genPDGID			);  */
    /* 	outputTree->Branch("genMomIdx"		, &_genMomIdx			); */

    /* 	outputTree->Branch("nGenJet"			, &_nGenJet			);  */
    /* 	outputTree->Branch("genJetPt"			, &_genJetPt			); */
    /* 	outputTree->Branch("genJetEta"			, &_genJetEta			);  */
    /* 	outputTree->Branch("genJetPhi"			, &_genJetPhi			);  */
    /* 	outputTree->Branch("genJetMass"			, &_genJetMass			);  */
    /* 	outputTree->Branch("genJetPartonFlavour"	, &_genJetPartonFlavour		);  */
    /* 	outputTree->Branch("genJetHadronFlavour"	, &_genJetHadronFlavour		);  */
    /* //} */
	
    outputTree->Branch("M3"				, &_M3				); 
    outputTree->Branch("HT"				, &_HT				); 
    
    outputTree->Branch("passPresel_Ele"			, &_passPresel_Ele		); 
    outputTree->Branch("passPresel_Mu"			, &_passPresel_Mu		);
    outputTree->Branch("passAll_Ele"			, &_passAll_Ele			); 
    outputTree->Branch("passAll_Mu"			, &_passAll_Mu			);
    outputTree->Branch("selStep"			, &_selStep		);
}


//_____________________________________________________________________
Bool_t PerformKinFit::Notify()
{
//   called when loading a new file
//   get branch pointers

  Info("Notify","processing file: %s",fChain->GetCurrentFile()->GetName());  

  return kTRUE;
}


// Kinfit methods
//////////////////////////////////////////////////////////////////////////////////

double KinFit::ErrEt(float Et, float Eta) {
  double InvPerr2, a, b, c;
  if(fabs(Eta) < 1.4){
    a = 5.6;
    b = 1.25;
    c = 0.033;
  }
  else{
    a = 4.8;
    b = 0.89;
    c = 0.043;
  }
  InvPerr2 = (a * a) + (b * b) * Et + (c * c) * Et * Et;
  return InvPerr2;
}

double KinFit::ErrEta(float Et, float Eta) {
  double InvPerr2, a, b, c;
  if(fabs(Eta) < 1.4){
    a = 1.215;
    b = 0.037;
    c = 7.941 * 0.0001;
  }
  else{
    a = 1.773;
    b = 0.034;
    c = 3.56 * 0.0001;
  }
  InvPerr2 = a/(Et * Et) + b/Et + c;
  return InvPerr2;
}

double KinFit::ErrPhi(float Et, float Eta) {
  double InvPerr2, a, b, c;
  if(fabs(Eta) < 1.4){
    a = 6.65;
    b = 0.04;
    c = 8.49 * 0.00001;
  }
  else{
    a = 2.908;
    b = 0.021;
    c = 2.59 * 0.0001;
  }
  InvPerr2 = a/(Et * Et) + b/Et + c;
  return InvPerr2;
}

void KinFit::print(TKinFitter *fitter)
{
  std::cout << "=============================================" << std ::endl;
  std::cout << "-> Number of measured Particles  : " << fitter->nbMeasParticles() << std::endl;
  std::cout << "-> Number of unmeasured particles: " << fitter->nbUnmeasParticles() << std::endl;
  std::cout << "-> Number of constraints         : " << fitter->nbConstraints() << std::endl;
  std::cout << "-> Number of degrees of freedom  : " << fitter->getNDF() << std::endl;
  std::cout << "-> Number of parameters A        : " << fitter->getNParA() << std::endl;
  std::cout << "-> Number of parameters B        : " << fitter->getNParB() << std::endl;
  std::cout << "-> Maximum number of iterations  : " << fitter->getMaxNumberIter() << std::endl;
  std::cout << "-> Maximum deltaS                : " << fitter->getMaxDeltaS() << std::endl;
  std::cout << "-> Maximum F                     : " << fitter->getMaxF() << std::endl;
  std::cout << "+++++++++++++++++++++++++++++++++++++++++++++" << std ::endl;
  std::cout << "-> Status                        : " << fitter->getStatus() << std::endl;
  std::cout << "-> Number of iterations          : " << fitter->getNbIter() << std::endl;
  std::cout << "-> S                             : " << fitter->getS() << std::endl;
  std::cout << "-> F                             : " << fitter->getF() << std::endl;
  std::cout << "+++++++++++++++++++++++++++++++++++++++++++++" << std ::endl;
  for (int ipart = 0 ; ipart < fitter->nbMeasParticles() ; ipart++ ){
    std::cout << "---------------------------------------------" << std ::endl;
    std::cout<<"-> Particle :" << ipart << ",  name :" << fitter->getMeasParticle(ipart)->GetName() << std::endl;
    fitter->get4Vec(ipart)->Print();
    std::cout << "---------------------------------------------" << std ::endl;
  }
  std::cout << "+++++++++++++++++++++++++++++++++++++++++++++" << std ::endl;
  std::cout << "-> Covariance Matrix                        : " << std::endl;
  fitter->getCovMatrix()->Print();
  std::cout << "---------------------------------------------" << std ::endl;
  std::cout << "-> Fitted Covariance Matrix                        : " << std::endl;
  fitter->getCovMatrixFit()->Print();
  std::cout << "=============================================" << std ::endl;
  
}

int KinFit::udscResolution(double et, double eta, double& resEt, double& resEta, double& resPhi)
{

  double abseta = fabs(eta) ;
  
  if (0.000 <= abseta  and  abseta < 0.087){
    resEt   = et * (TMath::Sqrt( TMath::Power(0.0591,2) + TMath::Power(1/TMath::Sqrt(et),2) + TMath::Power(0.891/et,2) ) ) ;
    resEta  = TMath::Sqrt( TMath::Power(0.00915,2) + TMath::Power(1.51/et,2) ) ;
    resPhi  = TMath::Sqrt( TMath::Power(0.01,2) + TMath::Power(1.6/et,2) ) ;
  }
    
  else if (0.087 <= abseta  and  abseta < 0.174){
    resEt   = et * (TMath::Sqrt( TMath::Power(0.0619,2) + TMath::Power(0.975/TMath::Sqrt(et),2) + TMath::Power(1.54/et,2) ) ) ;
    resEta  = TMath::Sqrt( TMath::Power(0.00887,2) + TMath::Power(1.53/et,2) ) ;
    resPhi  = TMath::Sqrt( TMath::Power(0.00982,2) + TMath::Power(1.61/et,2) ) ;
  }
    
  else if (0.174 <= abseta  and  abseta < 0.261){
    resEt   = et * (TMath::Sqrt( TMath::Power(0.0574,2) + TMath::Power(1/TMath::Sqrt(et),2) + TMath::Power(1.49e-05/et,2) ) ) ;
    resEta  = TMath::Sqrt( TMath::Power(0.00865,2) + TMath::Power(1.54/et,2)) ;
    resPhi  = TMath::Sqrt( TMath::Power(0.0101,2) + TMath::Power(1.59/et,2)) ;
  }
    
  else if (0.261 <= abseta  and  abseta < 0.348){
    resEt   = et * (TMath::Sqrt( TMath::Power(0.0569,2) + TMath::Power(1.01/TMath::Sqrt(et),2) + TMath::Power(1.22e-07/et,2) ) ) ;
    resEta  = TMath::Sqrt( TMath::Power(0.00867,2) + TMath::Power(1.55/et,2) ) ;
    resPhi  = TMath::Sqrt( TMath::Power(0.00988,2) + TMath::Power(1.6/et,2) ) ;
  }
    
  else if (0.348 <= abseta  and  abseta < 0.435){
    resEt   = et * (TMath::Sqrt( TMath::Power(0.057,2) + TMath::Power(1/TMath::Sqrt(et),2) + TMath::Power(2.17e-08/et,2) ) ) ;
    resEta  = TMath::Sqrt( TMath::Power(0.00907,2) + TMath::Power(1.55/et,2) ) ;
    resPhi  = TMath::Sqrt( TMath::Power(0.0102,2) + TMath::Power(1.59/et,2) ) ;
  }
    
  else if (0.435 <= abseta  and  abseta < 0.522){
    resEt   = et * (TMath::Sqrt( TMath::Power(0.0522,2) + TMath::Power(1.02/TMath::Sqrt(et),2) + TMath::Power(2.64e-05/et,2) ) ) ;
    resEta  = TMath::Sqrt( TMath::Power(0.00844,2) + TMath::Power(1.59/et,2) ) ;
    resPhi  = TMath::Sqrt( TMath::Power(0.00982,2) + TMath::Power(1.6/et,2) ) ;
  }
    
  else if (0.522 <= abseta  and  abseta < 0.609){
    resEt   = et * (TMath::Sqrt( TMath::Power(0.0502,2) + TMath::Power(1.02/TMath::Sqrt(et),2) + TMath::Power(2.6e-06/et,2) ) ) ;
    resEta  = TMath::Sqrt( TMath::Power(0.00915,2) + TMath::Power(1.57/et,2) ) ;
    resPhi  = TMath::Sqrt( TMath::Power(0.00979,2) + TMath::Power(1.6/et,2) ) ;
  }
    
  else if (0.609 <= abseta  and  abseta < 0.696){
    resEt   = et * (TMath::Sqrt( TMath::Power(0.053,2) + TMath::Power(1.03/TMath::Sqrt(et),2) + TMath::Power(4.87e-07/et,2) ) ) ;
    resEta  = TMath::Sqrt( TMath::Power(0.00856,2) + TMath::Power(1.58/et,2) ) ;
    resPhi  = TMath::Sqrt( TMath::Power(0.00925,2) + TMath::Power(1.62/et,2) ) ;
  }
    
  else if (0.696 <= abseta  and  abseta < 0.783){
    resEt   = et * (TMath::Sqrt( TMath::Power(0.051,2) + TMath::Power(1.03/TMath::Sqrt(et),2) + TMath::Power(7.53e-06/et,2) ) ) ;
    resEta  = TMath::Sqrt( TMath::Power(0.00897,2) + TMath::Power(1.58/et,2) ) ;
    resPhi  = TMath::Sqrt( TMath::Power(0.00973,2) + TMath::Power(1.61/et,2) ) ;
  }
    
  else if (0.783 <= abseta  and  abseta < 0.870){
    resEt   = et * (TMath::Sqrt( TMath::Power(0.0549,2) + TMath::Power(1.04/TMath::Sqrt(et),2) + TMath::Power(5.62e-08/et,2) ) ) ;
    resEta  = TMath::Sqrt( TMath::Power(0.0095,2) + TMath::Power(1.6/et,2) ) ;
    resPhi  = TMath::Sqrt( TMath::Power(0.00971,2) + TMath::Power(1.62/et,2) ) ;
  }
    
  else if (0.870 <= abseta  and  abseta < 0.957){
    resEt   = et * (TMath::Sqrt( TMath::Power(0.0544,2) + TMath::Power(1.06/TMath::Sqrt(et),2) + TMath::Power(1.07e-05/et,2) ) ) ;
    resEta  = TMath::Sqrt( TMath::Power(0.00836,2) + TMath::Power(1.65/et,2) ) ;
    resPhi  = TMath::Sqrt( TMath::Power(0.00916,2) + TMath::Power(1.64/et,2) ) ;
  }
    
  else if (0.957 <= abseta  and  abseta < 1.044){
    resEt   = et * (TMath::Sqrt( TMath::Power(0.0519,2) + TMath::Power(1.09/TMath::Sqrt(et),2) + TMath::Power(8.43e-06/et,2) ) ) ;
    resEta  = TMath::Sqrt( TMath::Power(0.00782,2) + TMath::Power(1.68/et,2) ) ;
    resPhi  = TMath::Sqrt( TMath::Power(0.00959,2) + TMath::Power(1.66/et,2) ) ;
  }
    
  else if (1.044 <= abseta  and  abseta < 1.131){
    resEt   = et * (TMath::Sqrt( TMath::Power(0.0539,2) + TMath::Power(1.12/TMath::Sqrt(et),2) + TMath::Power(1.97e-07/et,2) ) ) ;
    resEta  = TMath::Sqrt( TMath::Power(0.0093,2) + TMath::Power(1.65/et,2) ) ;
    resPhi  = TMath::Sqrt( TMath::Power(0.00964,2) + TMath::Power(1.67/et,2) ) ;
  }
    
  else if (1.131 <= abseta  and  abseta < 1.218){
    resEt   = et * (TMath::Sqrt( TMath::Power(0.0492,2) + TMath::Power(1.16/TMath::Sqrt(et),2) + TMath::Power(1.37e-08/et,2) ) ) ;
    resEta  = TMath::Sqrt( TMath::Power(0.00986,2) + TMath::Power(1.69/et,2) ) ;
    resPhi  = TMath::Sqrt( TMath::Power(0.00969,2) + TMath::Power(1.71/et,2) ) ;
  }
    
  else if (1.218 <= abseta  and  abseta < 1.305){
    resEt   = et * (TMath::Sqrt( TMath::Power(0.0489,2) + TMath::Power(1.18/TMath::Sqrt(et),2) + TMath::Power(3.44e-07/et,2) ) ) ;
    resEta  = TMath::Sqrt( TMath::Power(0.0124,2) + TMath::Power(1.72/et,2) ) ;
    resPhi  = TMath::Sqrt( TMath::Power(0.00992,2) + TMath::Power(1.76/et,2) ) ;
  }
    
  else if (1.305 <= abseta  and  abseta < 1.392){
    resEt   = et * (TMath::Sqrt( TMath::Power(0.0414,2) + TMath::Power(1.25/TMath::Sqrt(et),2) + TMath::Power(1.98e-07/et,2) ) ) ;
    resEta  = TMath::Sqrt( TMath::Power(0.0181,2) + TMath::Power(1.63/et,2) ) ;
    resPhi  = TMath::Sqrt( TMath::Power(0.0124,2) + TMath::Power(1.79/et,2) ) ;
  }
    
  else if (1.392 <= abseta  and  abseta < 1.479){
    resEt   = et * (TMath::Sqrt( TMath::Power(0.0373,2) + TMath::Power(1.26/TMath::Sqrt(et),2) + TMath::Power(5.4e-07/et,2) ) ) ;
    resEta  = TMath::Sqrt( TMath::Power(0.0121,2) + TMath::Power(1.69/et,2) ) ;
    resPhi  = TMath::Sqrt( TMath::Power(0.0135,2) + TMath::Power(1.8/et,2) ) ;
  }
    
  else if (1.479 <= abseta  and  abseta < 1.566){
    resEt   = et * (TMath::Sqrt( TMath::Power(0.0125,2) + TMath::Power(1.24/TMath::Sqrt(et),2) + TMath::Power(1e-06/et,2) ) ) ;
    resEta  = TMath::Sqrt( TMath::Power(0.0122,2) + TMath::Power(1.69/et,2) ) ;
    resPhi  = TMath::Sqrt( TMath::Power(0.0107,2) + TMath::Power(1.85/et,2) ) ;
  }
    
  else if (1.566 <= abseta  and  abseta < 1.653){
    resEt   = et * (TMath::Sqrt( TMath::Power(1.37e-07,2) + TMath::Power(1.08/TMath::Sqrt(et),2) + TMath::Power(3.06/et,2) ) ) ;
    resEta  = TMath::Sqrt( TMath::Power(0.00975,2) + TMath::Power(1.69/et,2) ) ;
    resPhi  = TMath::Sqrt( TMath::Power(0.00895,2) + TMath::Power(1.84/et,2) ) ;
  }
    
  else if (1.653 <= abseta  and  abseta < 1.740){
    resEt   = et * (TMath::Sqrt( TMath::Power(2.37e-07,2) + TMath::Power(1.04/TMath::Sqrt(et),2) + TMath::Power(3.01/et,2) ) ) ;
    resEta  = TMath::Sqrt( TMath::Power(0.00881,2) + TMath::Power(1.71/et,2) ) ;
    resPhi  = TMath::Sqrt( TMath::Power(0.00902,2) + TMath::Power(1.81/et,2) ) ;
  }
    
  else if (1.740 <= abseta  and  abseta < 1.830){
    resEt   = et * (TMath::Sqrt( TMath::Power(2.3e-07,2) + TMath::Power(1/TMath::Sqrt(et),2) + TMath::Power(3.1/et,2) ) ) ;
    resEta  = TMath::Sqrt( TMath::Power(0.00938,2) + TMath::Power(1.75/et,2) ) ;
    resPhi  = TMath::Sqrt( TMath::Power(0.00861,2) + TMath::Power(1.79/et,2) ) ;
  }
    
  else if (1.830 <= abseta  and  abseta < 1.930){
    resEt   = et * (TMath::Sqrt( TMath::Power(1.25e-07,2) + TMath::Power(0.965/TMath::Sqrt(et),2) + TMath::Power(3.14/et,2) ) ) ;
    resEta  = TMath::Sqrt( TMath::Power(0.00894,2) + TMath::Power(1.8/et,2)) ;
    resPhi  = TMath::Sqrt( TMath::Power(0.00877,2) + TMath::Power(1.75/et,2)) ;
  }
    
  else if (1.930 <= abseta  and  abseta < 2.043){
    resEt   = et * (TMath::Sqrt( TMath::Power(5.78e-08,2) + TMath::Power(0.924/TMath::Sqrt(et),2) + TMath::Power(3.14/et,2) ) ) ;
    resEta  = TMath::Sqrt( TMath::Power(0.00893,2) + TMath::Power(1.83/et,2) ) ;
    resPhi  = TMath::Sqrt( TMath::Power(0.00791,2) + TMath::Power(1.73/et,2) ) ;
  }
    
  else if (2.043 <= abseta  and  abseta < 2.172){
    resEt   = et * (TMath::Sqrt( TMath::Power(4.25e-08,2) + TMath::Power(0.923/TMath::Sqrt(et),2) + TMath::Power(2.85/et,2) ) ) ;
    resEta  = TMath::Sqrt( TMath::Power(0.0099,2) + TMath::Power(1.82/et,2) ) ;
    resPhi  = TMath::Sqrt( TMath::Power(0.00775,2) + TMath::Power(1.73/et,2) ) ;
  }
    
  else if (2.172 <= abseta  and  abseta < 2.322){
    resEt   = et * (TMath::Sqrt( TMath::Power(0.00601,2) + TMath::Power(0.881/TMath::Sqrt(et),2) + TMath::Power(3.23/et,2) ) ) ;
    resEta  = TMath::Sqrt( TMath::Power(0.00944,2) + TMath::Power(1.8/et,2) ) ;
    resPhi  = TMath::Sqrt( TMath::Power(0.00807,2) + TMath::Power(1.71/et,2) ) ;
  }
    
  else if (2.322 <= abseta  and  abseta < 2.500){
    resEt   = et * (TMath::Sqrt( TMath::Power(4.94e-08,2) + TMath::Power(0.86/TMath::Sqrt(et),2) + TMath::Power(3.56/et,2) ) ) ;
    resEta  = TMath::Sqrt( TMath::Power(0.0103,2) + TMath::Power(2.15/et,2) ) ;
    resPhi  = TMath::Sqrt( TMath::Power(0.0103,2) + TMath::Power(1.81/et,2) ) ;
  }

  return true;
}

int KinFit::bjetResolution(double et, double eta, double& resEt, double& resEta, double& resPhi)
{

  double abseta = fabs(eta) ;


  if (0.000 <= abseta and abseta < 0.087) {
    resEt   = et * ( TMath::Sqrt( TMath::Power(0.0686,2) + TMath::Power(1.03/TMath::Sqrt(et),2) + TMath::Power(1.68/et,2) ) )  ;
    resEta  =  TMath::Sqrt( TMath::Power(0.00605,2) + TMath::Power(1.63/et,2) )  ;
    resPhi  =  TMath::Sqrt( TMath::Power(0.00787,2) + TMath::Power(1.74/et,2) )  ;
  }

  else if (0.087 <= abseta and abseta < 0.174) {
    resEt   = et * ( TMath::Sqrt( TMath::Power(0.0737,2) + TMath::Power(1.01/TMath::Sqrt(et),2) + TMath::Power(1.74/et,2) ) )  ;
    resEta  =  TMath::Sqrt( TMath::Power(0.00592,2) + TMath::Power(1.64/et,2) )  ;
    resPhi  =  TMath::Sqrt( TMath::Power(0.00766,2) + TMath::Power(1.74/et,2) )  ;
  }

  else if (0.174 <= abseta and abseta < 0.261) {
    resEt   = et * ( TMath::Sqrt( TMath::Power(0.0657,2) + TMath::Power(1.07/TMath::Sqrt(et),2) + TMath::Power(5.16e-06/et,2) ) )  ;
    resEta  =  TMath::Sqrt( TMath::Power(0.00584,2) + TMath::Power(1.65/et,2) )  ;
    resPhi  =  TMath::Sqrt( TMath::Power(0.00755,2) + TMath::Power(1.74/et,2) )  ;
  }

  else if (0.261 <= abseta and abseta < 0.348) {
    resEt   = et * ( TMath::Sqrt( TMath::Power(0.062,2) + TMath::Power(1.07/TMath::Sqrt(et),2) +  TMath::Power(0.000134/et,2) ) )  ;
    resEta  =  TMath::Sqrt( TMath::Power(0.00593,2) + TMath::Power(1.65/et,2) )  ;
    resPhi  =  TMath::Sqrt( TMath::Power(0.00734,2) + TMath::Power(1.74/et,2) )  ;
  }

  else if (0.348 <= abseta and abseta < 0.435) {
    resEt   = et * ( TMath::Sqrt( TMath::Power(0.0605,2) + TMath::Power(1.07/TMath::Sqrt(et),2) + TMath::Power(1.84e-07/et,2) ) )  ;
    resEta  =  TMath::Sqrt( TMath::Power(0.00584,2) + TMath::Power(1.68/et,2) )  ;
    resPhi  =  TMath::Sqrt( TMath::Power(0.00734,2) + TMath::Power(1.75/et,2) )  ;
  }

  else if (0.435 <= abseta and abseta < 0.522) {
    resEt   = et * ( TMath::Sqrt( TMath::Power(0.059,2) + TMath::Power(1.08/TMath::Sqrt(et),2) + TMath::Power(9.06e-09/et,2) ) )  ;
    resEta  =  TMath::Sqrt( TMath::Power(0.00646,2) + TMath::Power(1.67/et,2) )  ;
    resPhi  =  TMath::Sqrt( TMath::Power(0.00767,2) + TMath::Power(1.74/et,2) )  ;
  }

  else if (0.522 <= abseta and abseta < 0.609) {
    resEt   = et * ( TMath::Sqrt( TMath::Power(0.0577,2) + TMath::Power(1.08/TMath::Sqrt(et),2) + TMath::Power(5.46e-06/et,2) ) )  ;
    resEta  =  TMath::Sqrt( TMath::Power(0.00661,2) + TMath::Power(1.67/et,2) )  ;
    resPhi  =  TMath::Sqrt( TMath::Power(0.00742,2) + TMath::Power(1.75/et,2) )  ;
  }

  else if (0.609 <= abseta and abseta < 0.696) {
    resEt   = et * ( TMath::Sqrt( TMath::Power(0.0525,2) + TMath::Power(1.09/TMath::Sqrt(et),2) + TMath::Power(4.05e-05/et,2) ) )  ;
    resEta  =  TMath::Sqrt( TMath::Power(0.00724,2) + TMath::Power(1.65/et,2) )  ;
    resPhi  =  TMath::Sqrt( TMath::Power(0.00771,2) + TMath::Power(1.73/et,2) )  ;
  }

  else if (0.696 <= abseta and abseta < 0.783) {
    resEt   = et * ( TMath::Sqrt( TMath::Power(0.0582,2) + TMath::Power(1.09/TMath::Sqrt(et),2) + TMath::Power(1.17e-05/et,2) ) )  ;
    resEta  =  TMath::Sqrt( TMath::Power(0.00763,2) + TMath::Power(1.67/et,2) )  ;
    resPhi  =  TMath::Sqrt( TMath::Power(0.00758,2) + TMath::Power(1.76/et,2) )  ;
  }

  else if (0.783 <= abseta and abseta < 0.870) {
    resEt   = et * ( TMath::Sqrt( TMath::Power(0.0649,2) + TMath::Power(1.08/TMath::Sqrt(et),2) + TMath::Power(7.85e-06/et,2) ) )  ;
    resEta  =  TMath::Sqrt( TMath::Power(0.00746,2) + TMath::Power(1.7/et,2) )  ;
    resPhi  =  TMath::Sqrt( TMath::Power(0.00789,2) + TMath::Power(1.75/et,2) )  ;
  }

  else if (0.870 <= abseta and abseta < 0.957) {
    resEt   = et * ( TMath::Sqrt( TMath::Power(0.0654,2) + TMath::Power(1.1/TMath::Sqrt(et),2) + TMath::Power(1.09e-07/et,2) ) )  ;
    resEta  =  TMath::Sqrt( TMath::Power(0.00807,2) + TMath::Power(1.7/et,2) )  ;
    resPhi  =  TMath::Sqrt( TMath::Power(0.00802,2) + TMath::Power(1.76/et,2) )  ;
  }

  else if (0.957 <= abseta and abseta < 1.044) {
    resEt   = et * ( TMath::Sqrt( TMath::Power(0.0669,2) + TMath::Power(1.11/TMath::Sqrt(et),2) + TMath::Power(1.87e-06/et,2) ) )  ;
    resEta  =  TMath::Sqrt( TMath::Power(0.00843,2) + TMath::Power(1.72/et,2) )  ;
    resPhi  =  TMath::Sqrt( TMath::Power(0.0078,2) + TMath::Power(1.79/et,2) )  ;
  }

  else if (1.044 <= abseta and abseta < 1.131) {
    resEt   = et * ( TMath::Sqrt( TMath::Power(0.0643,2) + TMath::Power(1.15/TMath::Sqrt(et),2) + TMath::Power(2.76e-05/et,2) ) )  ;
    resEta  =  TMath::Sqrt( TMath::Power(0.00886,2) + TMath::Power(1.74/et,2) )  ;
    resPhi  =  TMath::Sqrt( TMath::Power(0.00806,2) + TMath::Power(1.82/et,2) )  ;
  }

  else if (1.131 <= abseta and abseta < 1.218) {
    resEt   = et * ( TMath::Sqrt( TMath::Power(0.0645,2) + TMath::Power(1.16/TMath::Sqrt(et),2) + TMath::Power(1.04e-06/et,2) ) )  ;
    resEta  =  TMath::Sqrt( TMath::Power(0.0101,2) + TMath::Power(1.76/et,2) )  ;
    resPhi  =  TMath::Sqrt( TMath::Power(0.00784,2) + TMath::Power(1.86/et,2) )  ;
  }

  else if (1.218 <= abseta and abseta < 1.305) {
    resEt   = et * ( TMath::Sqrt( TMath::Power(0.0637,2) + TMath::Power(1.19/TMath::Sqrt(et),2) + TMath::Power(1.08e-07/et,2) ) )  ;
    resEta  =  TMath::Sqrt( TMath::Power(0.0127,2) + TMath::Power(1.78/et,2) )  ;
    resPhi  =  TMath::Sqrt( TMath::Power(0.00885,2) + TMath::Power(1.9/et,2) )  ;
  }

  else if (1.305 <= abseta and abseta < 1.392) {
    resEt   = et * ( TMath::Sqrt( TMath::Power(0.0695,2) + TMath::Power(1.21/TMath::Sqrt(et),2) + TMath::Power(5.75e-06/et,2) ) )  ;
    resEta  =  TMath::Sqrt( TMath::Power(0.0161,2) + TMath::Power(1.73/et,2) )  ;
    resPhi  =  TMath::Sqrt( TMath::Power(0.0108,2) + TMath::Power(1.93/et,2) )  ;
  }

  else if (1.392 <= abseta and abseta < 1.479) {
    resEt   = et * ( TMath::Sqrt( TMath::Power(0.0748,2) + TMath::Power(1.2/TMath::Sqrt(et),2) + TMath::Power(5.15e-08/et,2) ) )  ;
    resEta  =  TMath::Sqrt( TMath::Power(0.0122,2) + TMath::Power(1.77/et,2) )  ;
    resPhi  =  TMath::Sqrt( TMath::Power(0.0112,2) + TMath::Power(2/et,2) )  ;
  }

  else if (1.479 <= abseta and abseta < 1.566) {
    resEt   = et * ( TMath::Sqrt( TMath::Power(0.0624,2) + TMath::Power(1.23/TMath::Sqrt(et),2) + TMath::Power(2.28e-05/et,2) ) )  ;
    resEta  =  TMath::Sqrt( TMath::Power(0.0123,2) + TMath::Power(1.79/et,2) )  ;
    resPhi  =  TMath::Sqrt( TMath::Power(0.0102,2) + TMath::Power(2.02/et,2) )  ;
  }

  else if (1.566 <= abseta and abseta < 1.653) {
    resEt   = et * ( TMath::Sqrt( TMath::Power(0.0283,2) + TMath::Power(1.25/TMath::Sqrt(et),2) + TMath::Power(4.79e-07/et,2) ) )  ;
    resEta  =  TMath::Sqrt( TMath::Power(0.0111,2) + TMath::Power(1.79/et,2) )  ;
    resPhi  =  TMath::Sqrt( TMath::Power(0.00857,2) + TMath::Power(2.01/et,2) )  ;
  }

  else if (1.653 <= abseta and abseta < 1.740) {
    resEt   = et * ( TMath::Sqrt( TMath::Power(0.0316,2) + TMath::Power(1.21/TMath::Sqrt(et),2) + TMath::Power(5e-05/et,2) ) )  ;
    resEta  =  TMath::Sqrt( TMath::Power(0.0106,2) + TMath::Power(1.8/et,2) )  ;
    resPhi  =  TMath::Sqrt( TMath::Power(0.00856,2) + TMath::Power(1.97/et,2) )  ;
  }

  else if (1.740 <= abseta and abseta < 1.830) {
    resEt   = et * ( TMath::Sqrt( TMath::Power(2.29e-07,2) + TMath::Power(1.2/TMath::Sqrt(et),2) + TMath::Power(1.71e-05/et,2) ) )  ;
    resEta  =  TMath::Sqrt( TMath::Power(0.0115,2) + TMath::Power(1.83/et,2) )  ;
    resPhi  =  TMath::Sqrt( TMath::Power(0.00761,2) + TMath::Power(1.95/et,2) )  ;
  }

  else if (1.830 <= abseta and abseta < 1.930) {
    resEt   = et * ( TMath::Sqrt( TMath::Power(5.18e-09,2) + TMath::Power(1.14/TMath::Sqrt(et),2) + TMath::Power(1.7/et,2) ) )  ;
    resEta  =  TMath::Sqrt( TMath::Power(0.012,2) + TMath::Power(1.88/et,2) )  ;
    resPhi  =  TMath::Sqrt( TMath::Power(0.00721,2) + TMath::Power(1.92/et,2) )  ;
  }

  else if (1.930 <= abseta and abseta < 2.043) {
    resEt   = et * ( TMath::Sqrt( TMath::Power(2.17e-07,2) + TMath::Power(1.09/TMath::Sqrt(et),2) + TMath::Power(2.08/et,2) ) )  ;
    resEta  =  TMath::Sqrt( TMath::Power(0.0131,2) + TMath::Power(1.91/et,2) )  ;
    resPhi  =  TMath::Sqrt( TMath::Power(0.00722,2) + TMath::Power(1.86/et,2) )  ;
  }

  else if (2.043 <= abseta and abseta < 2.172) {
    resEt   = et * ( TMath::Sqrt( TMath::Power(3.65e-07,2) + TMath::Power(1.09/TMath::Sqrt(et),2) + TMath::Power(1.63/et,2) ) )  ;
    resEta  =  TMath::Sqrt( TMath::Power(0.0134,2) + TMath::Power(1.92/et,2) )  ;
    resPhi  =  TMath::Sqrt( TMath::Power(0.00703,2) + TMath::Power(1.86/et,2) )  ;
  }

  else if (2.172 <= abseta and abseta < 2.322) {
    resEt   = et * ( TMath::Sqrt( TMath::Power(2.02e-07,2) + TMath::Power(1.09/TMath::Sqrt(et),2) + TMath::Power(1.68/et,2) ) )  ;
    resEta  =  TMath::Sqrt( TMath::Power(0.0132,2) + TMath::Power(1.89/et,2) )  ;
    resPhi  =  TMath::Sqrt( TMath::Power(0.00845,2) + TMath::Power(1.86/et,2) )  ;
  }

  else if (2.322 <= abseta and abseta < 2.500) {
    resEt   = et * ( TMath::Sqrt( TMath::Power(5.27e-07,2) + TMath::Power(1.12/TMath::Sqrt(et),2) + TMath::Power(1.78/et,2) ) )  ;
    resEta  =  TMath::Sqrt( TMath::Power(0.0121,2) + TMath::Power(2.28/et,2) )  ;
    resPhi  =  TMath::Sqrt( TMath::Power(0.00975,2) + TMath::Power(2/et,2) )  ;        
  }

  return true;
}

int KinFit::muonResolution(double et, double eta, double& resEt, double& resEta, double& resPhi)
{

  double abseta = fabs(eta) ;
  

  if ( 0.000 <= abseta and abseta < 0.100 ) {
    resEt   = et * (0.00517 + 0.000143 * et) ;
    resEta  = TMath::Sqrt( TMath::Power(0.000433,2) + TMath::Power(0.000161/TMath::Sqrt(et),2) + TMath::Power(0.00334/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(7.21e-05,2) + TMath::Power(7e-05/TMath::Sqrt(et),2) + TMath::Power(0.00296/et,2) ) ; 
  }

  else if ( 0.100 <= abseta and abseta < 0.200 ) {
    resEt   = et * (0.00524 + 0.000143 * et); 
    resEta  = TMath::Sqrt( TMath::Power(0.000381,2) + TMath::Power(0.000473/TMath::Sqrt(et),2) + TMath::Power(0.00259/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(6.79e-05,2) + TMath::Power(0.000245/TMath::Sqrt(et),2) + TMath::Power(0.00274/et,2) ) ; 
  }

  else if ( 0.200 <= abseta and abseta < 0.300 ) {
    resEt   = et * (0.00585 + 0.000138 * et); 
    resEta  = TMath::Sqrt( TMath::Power(0.000337,2) + TMath::Power(0.000381/TMath::Sqrt(et),2) + TMath::Power(0.0023/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(7.08e-05,2) + TMath::Power(6.75e-05/TMath::Sqrt(et),2) + TMath::Power(0.00307/et,2) ) ; 
  }

  else if ( 0.300 <= abseta and abseta < 0.400 ) {
    resEt   = et * (0.0065 + 0.000133 * et); 
    resEta  = TMath::Sqrt( TMath::Power(0.000308,2) + TMath::Power(0.000166/TMath::Sqrt(et),2) + TMath::Power(0.00249/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(6.59e-05,2) + TMath::Power(0.000301/TMath::Sqrt(et),2) + TMath::Power(0.00281/et,2) ) ; 
  }

  else if ( 0.400 <= abseta and abseta < 0.500 ) {
    resEt   = et * (0.0071 + 0.000129 * et); 
    resEta  = TMath::Sqrt( TMath::Power(0.000289,2) + TMath::Power(5.37e-09/TMath::Sqrt(et),2) + TMath::Power(0.00243/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(6.27e-05,2) + TMath::Power(0.000359/TMath::Sqrt(et),2) + TMath::Power(0.00278/et,2) ) ; 
  }

  else if ( 0.500 <= abseta and abseta < 0.600 ) {
    resEt   = et * (0.00721 + 0.00013 * et); 
    resEta  = TMath::Sqrt( TMath::Power(0.000279,2) + TMath::Power(0.000272/TMath::Sqrt(et),2) + TMath::Power(0.0026/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(6.46e-05,2) + TMath::Power(0.00036/TMath::Sqrt(et),2) + TMath::Power(0.00285/et,2) ) ; 
  }

  else if ( 0.600 <= abseta and abseta < 0.700 ) {
    resEt   = et * (0.00757 + 0.000129 * et); 
    resEta  = TMath::Sqrt( TMath::Power(0.000282,2) + TMath::Power(3.63e-10/TMath::Sqrt(et),2) + TMath::Power(0.00288/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(6.54e-05,2) + TMath::Power(0.000348/TMath::Sqrt(et),2) + TMath::Power(0.00301/et,2) ) ; 
  }

  else if ( 0.700 <= abseta and abseta < 0.800 ) {
    resEt   = et * (0.0081 + 0.000127 * et); 
    resEta  = TMath::Sqrt( TMath::Power(0.000265,2) + TMath::Power(0.000609/TMath::Sqrt(et),2) + TMath::Power(0.00212/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(6.2e-05,2) + TMath::Power(0.000402/TMath::Sqrt(et),2) + TMath::Power(0.00304/et,2) ) ; 
  }

  else if ( 0.800 <= abseta and abseta < 0.900 ) {
    resEt   = et * (0.00916 + 0.000131 * et); 
    resEta  = TMath::Sqrt( TMath::Power(0.000241,2) + TMath::Power(0.000678/TMath::Sqrt(et),2) + TMath::Power(0.00221/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(6.26e-05,2) + TMath::Power(0.000458/TMath::Sqrt(et),2) + TMath::Power(0.0031/et,2) ) ; 
  }

  else if ( 0.900 <= abseta and abseta < 1.000 ) {
    resEt   = et * (0.0108 + 0.000151 * et); 
    resEta  = TMath::Sqrt( TMath::Power(0.000228,2) + TMath::Power(0.000612/TMath::Sqrt(et),2) + TMath::Power(0.00245/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(7.18e-05,2) + TMath::Power(0.000469/TMath::Sqrt(et),2) + TMath::Power(0.00331/et,2) ) ; 
  }

  else if ( 1.000 <= abseta and abseta < 1.100 ) {
    resEt   = et * (0.0115 + 0.000153 * et); 
    resEta  = TMath::Sqrt( TMath::Power(0.000217,2) + TMath::Power(0.000583/TMath::Sqrt(et),2) + TMath::Power(0.00307/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(6.98e-05,2) + TMath::Power(0.000507/TMath::Sqrt(et),2) + TMath::Power(0.00338/et,2) ) ; 
  }

  else if ( 1.100 <= abseta and abseta < 1.200 ) {
    resEt   = et * (0.013 + 0.000136 * et); 
    resEta  = TMath::Sqrt( TMath::Power(0.000195,2) + TMath::Power(0.000751/TMath::Sqrt(et),2) + TMath::Power(0.00282/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(6.21e-05,2) + TMath::Power(0.000584/TMath::Sqrt(et),2) + TMath::Power(0.00345/et,2) ) ; 
  }

  else if ( 1.200 <= abseta and abseta < 1.300 ) {
    resEt   = et * (0.0144 + 0.000131 * et); 
    resEta  = TMath::Sqrt( TMath::Power(0.000183,2) + TMath::Power(0.000838/TMath::Sqrt(et),2) + TMath::Power(0.00227/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(5.37e-05,2) + TMath::Power(0.000667/TMath::Sqrt(et),2) + TMath::Power(0.00352/et,2) ) ; 
  }

  else if ( 1.300 <= abseta and abseta < 1.400 ) {
    resEt   = et * (0.0149 + 0.000141 * et); 
    resEta  = TMath::Sqrt( TMath::Power(0.000196,2) + TMath::Power(0.000783/TMath::Sqrt(et),2) + TMath::Power(0.00274/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(5.37e-05,2) + TMath::Power(0.000711/TMath::Sqrt(et),2) + TMath::Power(0.00358/et,2) ) ; 
  }

  else if ( 1.400 <= abseta and abseta < 1.500 ) {
    resEt   = et * (0.014 + 0.000155 * et); 
    resEta  = TMath::Sqrt( TMath::Power(0.0002,2) + TMath::Power(0.000832/TMath::Sqrt(et),2) + TMath::Power(0.00254/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(5.98e-05,2) + TMath::Power(0.000713/TMath::Sqrt(et),2) + TMath::Power(0.00362/et,2) ) ; 
  }

  else if ( 1.500 <= abseta and abseta < 1.600 ) {
    resEt   = et * (0.0132 + 0.000169 * et); 
    resEta  = TMath::Sqrt( TMath::Power(0.000205,2) + TMath::Power(0.0007/TMath::Sqrt(et),2) + TMath::Power(0.00304/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(6.21e-05,2) + TMath::Power(0.000781/TMath::Sqrt(et),2) + TMath::Power(0.00348/et,2) ) ; 
  }

  else if ( 1.600 <= abseta and abseta < 1.700 ) {
    resEt   = et * (0.0129 + 0.0002 * et); 
    resEta  = TMath::Sqrt( TMath::Power(0.000214,2) + TMath::Power(0.000747/TMath::Sqrt(et),2) + TMath::Power(0.00319/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(6.92e-05,2) + TMath::Power(0.000865/TMath::Sqrt(et),2) + TMath::Power(0.00337/et,2) ) ; 
  }

  else if ( 1.700 <= abseta and abseta < 1.800 ) {
    resEt   = et * (0.0135 + 0.000264 * et); 
    resEta  = TMath::Sqrt( TMath::Power(0.000238,2) + TMath::Power(0.000582/TMath::Sqrt(et),2) + TMath::Power(0.00343/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(9.13e-05,2) + TMath::Power(0.000896/TMath::Sqrt(et),2) + TMath::Power(0.00348/et,2) ) ; 
  }

  else if ( 1.800 <= abseta and abseta < 1.900 ) {
    resEt   = et * (0.0144 + 0.00034 * et); 
    resEta  = TMath::Sqrt( TMath::Power(0.000263,2) + TMath::Power(0.000721/TMath::Sqrt(et),2) + TMath::Power(0.00322/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.000102,2) + TMath::Power(0.000994/TMath::Sqrt(et),2) + TMath::Power(0.00337/et,2) ) ; 
  }

  else if ( 1.900 <= abseta and abseta < 2.000 ) {
    resEt   = et * (0.0147 + 0.000441 * et); 
    resEta  = TMath::Sqrt( TMath::Power(0.000284,2) + TMath::Power(0.000779/TMath::Sqrt(et),2) + TMath::Power(0.0031/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.000123,2) + TMath::Power(0.00108/TMath::Sqrt(et),2) + TMath::Power(0.00315/et,2) ) ; 
  }

  else if ( 2.000 <= abseta and abseta < 2.100 ) {
    resEt   = et * (0.0154 + 0.000604 * et); 
    resEta  = TMath::Sqrt( TMath::Power(0.000316,2) + TMath::Power(0.000566/TMath::Sqrt(et),2) + TMath::Power(0.00384/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.000169,2) + TMath::Power(0.000947/TMath::Sqrt(et),2) + TMath::Power(0.00422/et,2) ) ; 
  }

  else if ( 2.100 <= abseta and abseta < 2.200 ) {
    resEt   = et * (0.0163 + 0.000764 * et); 
    resEta  = TMath::Sqrt( TMath::Power(0.000353,2) + TMath::Power(0.000749/TMath::Sqrt(et),2) + TMath::Power(0.0038/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.000176,2) + TMath::Power(0.00116/TMath::Sqrt(et),2) + TMath::Power(0.00423/et,2) ) ; 
  }

  else if ( 2.200 <= abseta and abseta < 2.300 ) {
    resEt   = et * (0.0173 + 0.000951 * et); 
    resEta  = TMath::Sqrt( TMath::Power(0.000412,2) + TMath::Power(0.00102/TMath::Sqrt(et),2) + TMath::Power(0.00351/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.000207,2) + TMath::Power(0.00115/TMath::Sqrt(et),2) + TMath::Power(0.00469/et,2) ) ; 
  }

  else if ( 2.300 <= abseta and abseta < 2.400 ) {
    resEt   = et * (0.0175 + 0.00126 * et); 
    resEta  = TMath::Sqrt( TMath::Power(0.000506,2) + TMath::Power(0.000791/TMath::Sqrt(et),2) + TMath::Power(0.0045/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.00027,2) + TMath::Power(0.00113/TMath::Sqrt(et),2) + TMath::Power(0.00528/et,2) ) ; 
  }

  return true;
}

int KinFit::elecResolution(double et, double eta, double& resEt, double& resEta, double& resPhi)
{

  double abseta = fabs(eta) ;


  if ( 0.000 <= abseta and abseta < 0.174 ) {
    resEt   = et * TMath::Sqrt( TMath::Power(0.00534,2) + TMath::Power(0.079/TMath::Sqrt(et),2) + TMath::Power(0.163/et,2) ) ; 
    resEta  = TMath::Sqrt( TMath::Power(0.000452,2) + TMath::Power(0.000285/TMath::Sqrt(et),2) + TMath::Power(0.00376/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.000101,2) + TMath::Power(0.0011/TMath::Sqrt(et),2) + TMath::Power(0.00346/et,2) ) ; 
  }

  else if ( 0.174 <= abseta and abseta < 0.261 ) {
    resEt   = et * TMath::Sqrt( TMath::Power(0.00518,2) + TMath::Power(0.0749/TMath::Sqrt(et),2) + TMath::Power(0.227/et,2) ) ; 
    resEta  = TMath::Sqrt( TMath::Power(0.00038,2) + TMath::Power(0.000571/TMath::Sqrt(et),2) + TMath::Power(0.00276/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(9.3e-05,2) + TMath::Power(0.00115/TMath::Sqrt(et),2) + TMath::Power(0.0035/et,2) ) ; 
  }

  else if ( 0.261 <= abseta and abseta < 0.348 ) {
    resEt   = et * TMath::Sqrt( TMath::Power(0.00332,2) + TMath::Power(0.0879/TMath::Sqrt(et),2) + TMath::Power(0.12/et,2) ) ; 
    resEta  = TMath::Sqrt( TMath::Power(0.000351,2) + TMath::Power(1.36e-09/TMath::Sqrt(et),2) + TMath::Power(0.00324/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.000103,2) + TMath::Power(0.00117/TMath::Sqrt(et),2) + TMath::Power(0.00333/et,2) ) ; 
  }

  else if ( 0.348 <= abseta and abseta < 0.435 ) {
    resEt   = et * TMath::Sqrt( TMath::Power(0.00445,2) + TMath::Power(0.0895/TMath::Sqrt(et),2) + TMath::Power(0.186/et,2) ) ; 
    resEta  = TMath::Sqrt( TMath::Power(0.000319,2) + TMath::Power(0.00061/TMath::Sqrt(et),2) + TMath::Power(0.00182/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.00011,2) + TMath::Power(0.00115/TMath::Sqrt(et),2) + TMath::Power(0.00365/et,2) ) ; 
  }

  else if ( 0.435 <= abseta and abseta < 0.522 ) {
    resEt   = et * TMath::Sqrt( TMath::Power(0.00453,2) + TMath::Power(0.0893/TMath::Sqrt(et),2) + TMath::Power(0.21/et,2) ) ; 
    resEta  = TMath::Sqrt( TMath::Power(0.000301,2) + TMath::Power(0.000612/TMath::Sqrt(et),2) + TMath::Power(0.00146/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.000105,2) + TMath::Power(0.00122/TMath::Sqrt(et),2) + TMath::Power(0.00343/et,2) ) ; 
  }

  else if ( 0.522 <= abseta and abseta < 0.609 ) {
    resEt   = et * TMath::Sqrt( TMath::Power(0.00308,2) + TMath::Power(0.0886/TMath::Sqrt(et),2) + TMath::Power(0.188/et,2) ) ; 
    resEta  = TMath::Sqrt( TMath::Power(0.000297,2) + TMath::Power(0.000791/TMath::Sqrt(et),2) + TMath::Power(2.09e-08/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.000102,2) + TMath::Power(0.00129/TMath::Sqrt(et),2) + TMath::Power(0.00328/et,2) ) ; 
  }

  else if ( 0.609 <= abseta and abseta < 0.696 ) {
    resEt   = et * TMath::Sqrt( TMath::Power(0.00308,2) + TMath::Power(0.0914/TMath::Sqrt(et),2) + TMath::Power(0.182/et,2) ) ; 
    resEta  = TMath::Sqrt( TMath::Power(0.00032,2) + TMath::Power(0.000329/TMath::Sqrt(et),2) + TMath::Power(0.00325/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.000103,2) + TMath::Power(0.00139/TMath::Sqrt(et),2) + TMath::Power(0.00253/et,2) ) ; 
  }

  else if ( 0.696 <= abseta and abseta < 0.783 ) {
    resEt   = et * TMath::Sqrt( TMath::Power(0.00442,2) + TMath::Power(0.0914/TMath::Sqrt(et),2) + TMath::Power(0.231/et,2) ) ; 
    resEta  = TMath::Sqrt( TMath::Power(0.000309,2) + TMath::Power(0.000821/TMath::Sqrt(et),2) + TMath::Power(0.00119/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.000115,2) + TMath::Power(0.00139/TMath::Sqrt(et),2) + TMath::Power(0.00293/et,2) ) ; 
  }

  else if ( 0.783 <= abseta and abseta < 0.870 ) {
    resEt   = et * TMath::Sqrt( TMath::Power(0.00455,2) + TMath::Power(0.0949/TMath::Sqrt(et),2) + TMath::Power(0.335/et,2) ) ; 
    resEta  = TMath::Sqrt( TMath::Power(0.000293,2) + TMath::Power(0.000767/TMath::Sqrt(et),2) + TMath::Power(0.00211/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.000121,2) + TMath::Power(0.00158/TMath::Sqrt(et),2) + TMath::Power(0.00151/et,2) ) ; 
  }

  else if ( 0.870 <= abseta and abseta < 0.957 ) {
    resEt   = et * TMath::Sqrt( TMath::Power(0.00181,2) + TMath::Power(0.102/TMath::Sqrt(et),2) + TMath::Power(0.333/et,2) ) ; 
    resEta  = TMath::Sqrt( TMath::Power(0.000275,2) + TMath::Power(0.000765/TMath::Sqrt(et),2) + TMath::Power(0.00227/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.000128,2) + TMath::Power(0.00169/TMath::Sqrt(et),2) + TMath::Power(1.93e-08/et,2) ) ; 
  }

  else if ( 0.957 <= abseta and abseta < 1.044 ) {
    resEt   = et * TMath::Sqrt( TMath::Power(0.000764,2) + TMath::Power(0.108/TMath::Sqrt(et),2) + TMath::Power(0.42/et,2) ) ; 
    resEta  = TMath::Sqrt( TMath::Power(0.000274,2) + TMath::Power(0.000622/TMath::Sqrt(et),2) + TMath::Power(0.00299/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.000145,2) + TMath::Power(0.00179/TMath::Sqrt(et),2) + TMath::Power(1.69e-08/et,2) ) ; 
  }

  else if ( 1.044 <= abseta and abseta < 1.131 ) {
    resEt   = et * TMath::Sqrt( TMath::Power(0.00114,2) + TMath::Power(0.128/TMath::Sqrt(et),2) + TMath::Power(0.55/et,2) ) ; 
    resEta  = TMath::Sqrt( TMath::Power(0.000269,2) + TMath::Power(0.000929/TMath::Sqrt(et),2) + TMath::Power(0.00183/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.000185,2) + TMath::Power(0.00182/TMath::Sqrt(et),2) + TMath::Power(2.99e-09/et,2) ) ; 
  }

  else if ( 1.131 <= abseta and abseta < 1.218 ) {
    resEt   = et * TMath::Sqrt( TMath::Power(4.14e-09,2) + TMath::Power(0.155/TMath::Sqrt(et),2) + TMath::Power(0.674/et,2) ) ; 
    resEta  = TMath::Sqrt( TMath::Power(0.000268,2) + TMath::Power(0.000876/TMath::Sqrt(et),2) + TMath::Power(0.00234/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.000194,2) + TMath::Power(0.002/TMath::Sqrt(et),2) + TMath::Power(2.39e-08/et,2) ) ; 
  }

  else if ( 1.218 <= abseta and abseta < 1.305 ) {
    resEt   = et * TMath::Sqrt( TMath::Power(8.03e-09,2) + TMath::Power(0.144/TMath::Sqrt(et),2) + TMath::Power(0.8/et,2) ) ; 
    resEta  = TMath::Sqrt( TMath::Power(0.000258,2) + TMath::Power(0.000782/TMath::Sqrt(et),2) + TMath::Power(0.00246/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.000226,2) + TMath::Power(0.00206/TMath::Sqrt(et),2) + TMath::Power(5.88e-08/et,2) ) ; 
  }

  else if ( 1.305 <= abseta and abseta < 1.392 ) {
    resEt   = et * TMath::Sqrt( TMath::Power(0.00842,2) + TMath::Power(0.118/TMath::Sqrt(et),2) + TMath::Power(0.951/et,2) ) ; 
    resEta  = TMath::Sqrt( TMath::Power(0.000269,2) + TMath::Power(0.000817/TMath::Sqrt(et),2) + TMath::Power(0.00278/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.000247,2) + TMath::Power(0.00225/TMath::Sqrt(et),2) + TMath::Power(1.47e-09/et,2) ) ; 
  }

  else if ( 1.392 <= abseta and abseta < 1.479 ) {
    resEt   = et * TMath::Sqrt( TMath::Power(0.00684,2) + TMath::Power(0.144/TMath::Sqrt(et),2) + TMath::Power(0.892/et,2) ) ; 
    resEta  = TMath::Sqrt( TMath::Power(0.000267,2) + TMath::Power(0.000734/TMath::Sqrt(et),2) + TMath::Power(0.00327/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.000234,2) + TMath::Power(0.00233/TMath::Sqrt(et),2) + TMath::Power(4.92e-09/et,2) ) ; 
  }

  else if ( 1.479 <= abseta and abseta < 1.653 ) {
    resEt   = et * TMath::Sqrt( TMath::Power(0.0245,2) + TMath::Power(0.196/TMath::Sqrt(et),2) + TMath::Power(0.555/et,2) ) ; 
    resEta  = TMath::Sqrt( TMath::Power(0.000268,2) + TMath::Power(0.000757/TMath::Sqrt(et),2) + TMath::Power(0.00295/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.00025,2) + TMath::Power(0.00268/TMath::Sqrt(et),2) + TMath::Power(7.5e-09/et,2) ) ; 
  }

  else if ( 1.653 <= abseta and abseta < 1.740 ) {
    resEt   = et * TMath::Sqrt( TMath::Power(0.0174,2) + TMath::Power(0.127/TMath::Sqrt(et),2) + TMath::Power(0.894/et,2) ) ; 
    resEta  = TMath::Sqrt( TMath::Power(0.000274,2) + TMath::Power(1.77e-09/TMath::Sqrt(et),2) + TMath::Power(0.00435/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.000284,2) + TMath::Power(0.00275/TMath::Sqrt(et),2) + TMath::Power(6.56e-09/et,2) ) ; 
  }

  else if ( 1.740 <= abseta and abseta < 1.830 ) {
    resEt   = et * TMath::Sqrt( TMath::Power(0.0144,2) + TMath::Power(0.133/TMath::Sqrt(et),2) + TMath::Power(0.708/et,2) ) ; 
    resEta  = TMath::Sqrt( TMath::Power(0.000274,2) + TMath::Power(0.00101/TMath::Sqrt(et),2) + TMath::Power(0.000982/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.000356,2) + TMath::Power(0.00279/TMath::Sqrt(et),2) + TMath::Power(0.00261/et,2) ) ; 
  }

  else if ( 1.830 <= abseta and abseta < 1.930 ) {
    resEt   = et * TMath::Sqrt( TMath::Power(0.0149,2) + TMath::Power(0.126/TMath::Sqrt(et),2) + TMath::Power(0.596/et,2) ) ; 
    resEta  = TMath::Sqrt( TMath::Power(0.000299,2) + TMath::Power(0.000686/TMath::Sqrt(et),2) + TMath::Power(0.00341/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.000347,2) + TMath::Power(0.00298/TMath::Sqrt(et),2) + TMath::Power(1.02e-08/et,2) ) ; 
  }

  else if ( 1.930 <= abseta and abseta < 2.043 ) {
    resEt   = et * TMath::Sqrt( TMath::Power(0.0143,2) + TMath::Power(0.12/TMath::Sqrt(et),2) + TMath::Power(0.504/et,2) ) ; 
    resEta  = TMath::Sqrt( TMath::Power(0.000329,2) + TMath::Power(3.05e-10/TMath::Sqrt(et),2) + TMath::Power(0.00439/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.000302,2) + TMath::Power(0.00322/TMath::Sqrt(et),2) + TMath::Power(5.22e-08/et,2) ) ; 
  }

  else if ( 2.043 <= abseta and abseta < 2.172 ) {
    resEt   = et * TMath::Sqrt( TMath::Power(0.0162,2) + TMath::Power(0.0965/TMath::Sqrt(et),2) + TMath::Power(0.483/et,2) ) ; 
    resEta  = TMath::Sqrt( TMath::Power(0.00037,2) + TMath::Power(1.32e-08/TMath::Sqrt(et),2) + TMath::Power(0.00447/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.000287,2) + TMath::Power(0.00349/TMath::Sqrt(et),2) + TMath::Power(3e-11/et,2) ) ; 
  }

  else if ( 2.172 <= abseta and abseta < 2.322 ) {
    resEt   = et * TMath::Sqrt( TMath::Power(0.0122,2) + TMath::Power(0.13/TMath::Sqrt(et),2) + TMath::Power(0.207/et,2) ) ; 
    resEta  = TMath::Sqrt( TMath::Power(0.000442,2) + TMath::Power(4.03e-10/TMath::Sqrt(et),2) + TMath::Power(0.00544/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.000214,2) + TMath::Power(0.00436/TMath::Sqrt(et),2) + TMath::Power(2.98e-09/et,2) ) ; 
  }

  else if ( 2.322 <= abseta and abseta < 2.500 ) {
    resEt   = et * TMath::Sqrt( TMath::Power(0.0145,2) + TMath::Power(0.127/TMath::Sqrt(et),2) + TMath::Power(0.0782/et,2) ) ; 
    resEta  = TMath::Sqrt( TMath::Power(0.000577,2) + TMath::Power(0.000768/TMath::Sqrt(et),2) + TMath::Power(0.00331/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(8.02e-05,2) + TMath::Power(0.00525/TMath::Sqrt(et),2) + TMath::Power(0.00581/et,2) ) ; 
  }


  return true;
}


int KinFit::metResolution(double et, double& resEt, double& resEta, double& resPhi)
{
  
  //summer 2011
  /* resEt   = et * TMath::Sqrt( TMath::Power(0.0351,2) + TMath::Power(0/TMath::Sqrt(et),2) + TMath::Power(20.288/et,2) ) ; */
  /* resEta  = TMath::Sqrt( TMath::Power(0,2) + TMath::Power(0/TMath::Sqrt(et),2) + TMath::Power(0/et,2) ) ; */
  /* resPhi  = TMath::Sqrt( TMath::Power(0,2) + TMath::Power(1.1664/TMath::Sqrt(et),2) + TMath::Power(3.579/et,2)) ; */

  //fall 2011
  resEt   = et * TMath::Sqrt( TMath::Power(0.0337,2) + TMath::Power(0.888/TMath::Sqrt(et),2) + TMath::Power(19.6/et,2) ) ;
  resEta  = TMath::Sqrt( TMath::Power(0,2) + TMath::Power(0/TMath::Sqrt(et),2) + TMath::Power(0/et,2) ) ;
  resPhi  = TMath::Sqrt( TMath::Power(1.28e-08,2) + TMath::Power(1.45/TMath::Sqrt(et),2) + TMath::Power(1.03/et,2) );
  
  return true;
}

int KinFit::JetEnergyResolution(double eta, double& JERbase, double& JERdown, double& JERup)
{

  double abseta = fabs(eta) ;

  if ( 0.0 <= abseta and abseta < 0.5 ) {
    JERbase = 1.109 ; JERdown = 1.044 ; JERup = 1.174 ;
  } else if ( 0.5 <= abseta and abseta < 0.8 ) {
    JERbase = 1.138 ; JERdown = 1.072 ; JERup = 1.204 ;
  } else if ( 0.8 <= abseta and abseta < 1.1 ) {
    JERbase = 1.114 ; JERdown = 1.050 ; JERup = 1.178 ;
  } else if ( 1.1 <= abseta and abseta < 1.3 ) {
    JERbase = 1.123 ; JERdown = 1.022 ; JERup = 1.224 ;
  } else if ( 1.3 <= abseta and abseta < 1.7 ) {
    JERbase = 1.084 ; JERdown = 0.985 ; JERup = 1.183 ;
  } else if ( 1.7 <= abseta and abseta < 1.9 ) {
    JERbase = 1.082 ; JERdown = 0.973 ; JERup = 1.191 ;
  } else if ( 1.9 <= abseta and abseta < 2.1 ) {
    JERbase = 1.140 ; JERdown = 1.020 ; JERup = 1.260 ;
  } else if ( 2.1 <= abseta and abseta < 2.3 ) {
    JERbase = 1.067 ; JERdown = 0.953 ; JERup = 1.181 ;
  } else if ( 2.3 <= abseta and abseta < 2.5 ) {
    JERbase = 1.177 ; JERdown = 0.967 ; JERup = 1.387 ;
  } else if ( 2.5 <= abseta and abseta < 2.8 ) {
    JERbase = 1.364 ; JERdown = 1.203 ; JERup = 1.525 ;
  } else if ( 2.8 <= abseta and abseta < 3.0 ) {
    JERbase = 1.857 ; JERdown = 1.654 ; JERup = 2.060 ;
  } else if ( 3.0 <= abseta and abseta < 3.2 ) {
    JERbase = 1.328 ; JERdown = 1.203 ; JERup = 1.453 ;
  }else {
    JERbase = 1.160 ; JERdown = 1.013 ; JERup = 1.307 ;
  }


  return true;
}

bool KinFit::Fit(){
  
  bool				goodCombo = false;
  TLorentzVector		neutrino, bjlep, bjhad, cjhad, sjhad;
  TMatrixD			ml(3,3), mn(3,3), mbl(3,3), mbh(3,3), mc(3,3), ms(3,3);
  double			resEt, resEta, resPhi;
  double			JERbase, JERdown, JERup;
  std::vector<TLorentzVector>	ljetlist;
  std::vector<TLorentzVector>	bjetlist;
  std::map<unsigned		int, unsigned int> list2jet;
  METzCalculator		metZ;
  TLorentzVector		METVector;
  double			reslepEta, reslepPhi, resneuEta, resneuPhi, resbjlepEta, resbjlepPhi, resbjhadEta, resbjhadPhi, rescjhadEta, rescjhadPhi, ressjhadEta, ressjhadPhi ; 
  unsigned int			max_nu	  = 2;

  metZ.SetLepton(lepton);
  
  if(leptonType == kElectron)
    metZ.SetLeptonType("electron");
  if(leptonType == kMuon)
    metZ.SetLeptonType("muon");
  
  METVector.SetPtEtaPhiM(_nu_pt, 0., _nu_phi, 0.);
  metZ.SetMET(METVector);
  
  _nu_px = METVector.Px();
  _nu_py = METVector.Py();
  _nu_pz = metZ.Calculate();
  _nu_pz_other = metZ.getOther();
  isComplex = metZ.IsComplex();

  //bool PtDescending (unsigned int i, unsigned int j) { 
  //  return ( jets.at(i).Pt() > jets.at(j).Pt() ); 
  //}
  
  bjetlist.clear();
  ljetlist.clear();
  list2jet.clear();
  int ib = 0, il = 0;
  for (unsigned int i = 0 ; i < jets.size() ; i++){
    if (btag[i] > btagThresh){ 
      bjetlist.push_back(jets.at(i));
      list2jet[ib] = i;
      ib++;
    }else{
      ljetlist.push_back(jets.at(i));
      list2jet[il] = i;
      il++;
    }
  }
  
  if(bjetlist.size() < 2 or ljetlist.size() < 2){
    
    bjetlist.clear();
    ljetlist.clear();
    list2jet.clear();
    
    return goodCombo;
  }
  
  std::sort ( ljetlist.begin(), ljetlist.end() , PtDescending() ) ;
  std::sort ( bjetlist.begin(), bjetlist.end() , PtDescending() ) ;
  
  /* cout<<"bjetlist--"<<endl; */
  /* for (auto x : bjetlist)  */
  /*   x.Print(); */
  /* cout<<"ljetlist--"<<endl; */
  /* for (auto x : ljetlist)  */
  /*   x.Print(); */
  
  int loop = 0;
  for(unsigned int ib1 = 0 ; ib1 < bjetlist.size() ; ib1++){
    for(unsigned int ib2 = 0 ; ib2 < bjetlist.size() ; ib2++){
      if(bjetlist.at(ib1) == bjetlist.at(ib2)) continue;
      for(unsigned int ij1 = 0 ; ij1 < ljetlist.size()-1 ; ij1++){
	for (unsigned int ij2 = ij1+1 ; ij2 < ljetlist.size() ; ij2++){
	  /* if(TMath::AreEqualAbs(_nu_pz,_nu_pz_other,1.e-7)) */
	  /*   max_nu = 1; */
	  /* else */
	  /*   max_nu = 2; */
	  max_nu = 1;
	  for(unsigned int inu_root = 0 ; inu_root < max_nu ; inu_root++){
	    //float nuz = (inu_root==0) ? _nu_pz : _nu_pz_other ;
	    
	    //neutrino.SetXYZM(_nu_px, _nu_py, nuz, 0.0);
	    neutrino.SetXYZM(_nu_px, _nu_py, 0.0, 0.0);
	    
	    bjlep = bjetlist.at(ib1);
	    bjhad = bjetlist.at(ib2);
	    cjhad = ljetlist.at(ij1);
	    sjhad = ljetlist.at(ij2);
	    
	    /* cout<<"loop " << loop++ << endl; */
	    /* bjlep.Print(); */
	    /* bjhad.Print(); */
	    /* cjhad.Print(); */
	    /* sjhad.Print(); */
	    /* neutrino.Print(); */
	    /* lepton.Print(); */
	    /* cout <<"_nu_pz : " << _nu_pz << " _nu_pz_other : " << _nu_pz_other << endl; */
	    
	    ml.Zero() ;  mn.Zero() ;  mbl.Zero() ;  mbh.Zero() ;  mc.Zero() ;  ms.Zero();
	      
	    // This is following covariance matrix setup is using CMS NOTE AN 2005/005.
	    // ml(0,0) = ErrEt (lepton.Et(), lepton.Eta()); // et
	    // ml(1,1) = ErrEta(lepton.Et(), lepton.Eta()); // eta
	    // ml(2,2) = ErrPhi(lepton.Et(), lepton.Eta()); // phi
	      
	    // mn(0,0) = ErrEt (neutrino.Et(), neutrino.Eta()); // et
	    // mn(1,1) = ErrEta(neutrino.Et(), neutrino.Eta()); // eta
	    // mn(2,2) = ErrPhi(neutrino.Et(), neutrino.Eta()); // phi
	      
	    // mbl(0,0) = ErrEt (bjlep.Et(), bjlep.Eta()); // et
	    // mbl(1,1) = ErrEta(bjlep.Et(), bjlep.Eta()); // eta
	    // mbl(2,2) = ErrPhi(bjlep.Et(), bjlep.Eta()); // phi
	      
	    // mbh(0,0) = ErrEt (bjhad.Et(), bjhad.Eta()); // et
	    // mbh(1,1) = ErrEta(bjhad.Et(), bjhad.Eta()); // eta
	    // mbh(2,2) = ErrPhi(bjhad.Et(), bjhad.Eta()); // phi
	      
	    // mc(0,0) = ErrEt (cjhad.Et(), cjhad.Eta()); // et
	    // mc(1,1) = ErrEta(cjhad.Et(), cjhad.Eta()); // eta
	    // mc(2,2) = ErrPhi(cjhad.Et(), cjhad.Eta()); // phi
	      
	    // ms(0,0) = ErrEt (sjhad.Et(), sjhad.Eta()); // et
	    // ms(1,1) = ErrEta(sjhad.Et(), sjhad.Eta()); // eta
	    // ms(2,2) = ErrPhi(sjhad.Et(), sjhad.Eta()); // phi
	    
	    // This is following covariance matrix setup is using TopQuarkAnalysis/TopKinFitter
	    if (leptonType != kElectron and leptonType != kMuon) continue;
	    
	    if(leptonType == kMuon)
	      muonResolution(lepton.Et(), lepton.Eta(), resEt, resEta, resPhi);	    
	    if(leptonType == kElectron)
	      elecResolution(lepton.Et(), lepton.Eta(), resEt, resEta, resPhi);
	    
	    ml(0,0)	= TMath::Power(resEt, 2);	// et
	    ml(1,1)	= TMath::Power(resEta, 2);	// eta
	    ml(2,2)	= TMath::Power(resPhi, 2);	// phi
	    
	    reslepEta	= resEta ; 
	    reslepPhi	= resPhi ; 
	    
	    metResolution(neutrino.Et(), resEt, resEta, resPhi);
	    resEta	= 1.e-7; // This is to avoid the matrix inversion problem: such as panic printout below
	    //Error in <TDecompLU::InvertLU>: matrix is singular, 1 diag elements < tolerance of 2.2204e-16
	    mn(0,0)	= TMath::Power(resEt, 2); // et
	    mn(1,1)	= TMath::Power(resEta, 2); // eta
	    mn(2,2)	= TMath::Power(resPhi, 2); // eta
	    /* cout <<"_nu Et : " << neutrino.Et()  */
	    /* 	 << " _nu E : " << neutrino.E()  */
	    /* 	 << " _nu Pt : " << neutrino.Pt()  */
	    /* 	 << " _nu |P| : " << neutrino.Vect().Mag()  */
	    /* 	 << endl; */

	    /* mn(0,0)	= 9999; // et */
	    /* mn(1,1)	= 9999; // eta */
	    /* mn(2,2)	= TMath::Power(0.54, 2); // phi */
	    /* cout<<"Before fit====="<<endl; */
	    /* mn.Print(); */
	    /* cout<<"Before fit====="<<endl; */

	    resneuEta	= resEta ; 
	    resneuPhi	= resPhi ; 
	    
	    bjetResolution(bjlep.Et(), bjlep.Eta(), resEt, resEta, resPhi);
	    JetEnergyResolution(bjlep.Eta(), JERbase, JERdown, JERup);
	    mbl(0,0)	= TMath::Power(resEt, 2); // et
	    mbl(0,0)   *= TMath::Power(JERbase, 2);
	    //mbl(0,0)   *= TMath::Power(jetsRes.at(bjetlist.at(ib1)), 2);
	    mbl(1,1)	= TMath::Power(resEta, 2); // eta
	    mbl(2,2)	= TMath::Power(resPhi, 2); // eta

	    resbjlepEta = resEta ;
	    resbjlepPhi = resPhi ; 
	    
	    bjetResolution(bjhad.Et(), bjhad.Eta(), resEt, resEta, resPhi);
	    JetEnergyResolution(bjhad.Eta(), JERbase, JERdown, JERup);
	    mbh(0,0)	= TMath::Power(resEt, 2); // et
	    mbh(0,0)   *= TMath::Power(JERbase, 2);
	    //mbh(0,0)   *= TMath::Power(jetsRes.at(bjetlist.at(ib2)), 2);
	    mbh(1,1)	= TMath::Power(resEta, 2); // eta
	    mbh(2,2)	= TMath::Power(resPhi, 2); // eta	      

	    resbjhadEta = resEta ; 
	    resbjhadPhi = resPhi ;  
	      
	    udscResolution(cjhad.Et(), cjhad.Eta(), resEt, resEta, resPhi);
	    JetEnergyResolution(cjhad.Eta(), JERbase, JERdown, JERup);
	    mc(0,0)	= TMath::Power(resEt, 2); // et
	    mc(0,0)    *= TMath::Power(JERbase, 2);
	    //mc(0,0)    *= TMath::Power(jetsRes.at(ij1), 2);
	    mc(1,1)	= TMath::Power(resEta, 2); // eta
	    mc(2,2)	= TMath::Power(resPhi, 2); // eta	      

	    rescjhadEta = resEta ;
	    rescjhadPhi = resPhi ;
	      
	    udscResolution(sjhad.Et(), sjhad.Eta(), resEt, resEta, resPhi);
	    JetEnergyResolution(sjhad.Eta(), JERbase, JERdown, JERup);
	    ms(0,0)	= TMath::Power(resEt, 2); // et
	    ms(0,0)    *= TMath::Power(JERbase, 2);
	    //ms(0,0)    *= TMath::Power(jetsRes.at(ij2), 2);
	    ms(1,1)	= TMath::Power(resEta, 2); // eta
	    ms(2,2)	= TMath::Power(resPhi, 2); // eta	      
	    
	    ressjhadEta = resEta ;
	    ressjhadPhi = resPhi ; 
	    
	    // For collider setup (Et, eta. phi) setup is suggested in KinFit original document  
	    TFitParticleEtEtaPhi *lep = new TFitParticleEtEtaPhi( "lep", "lep", &lepton,   &ml );
	    TFitParticleEtEtaPhi *neu = new TFitParticleEtEtaPhi( "neu", "neu", &neutrino, &mn );
	    /* TFitParticleEScaledMomDev *lep = new TFitParticleEScaledMomDev( "lep", "lep", &lepton,   &ml ); */
	    /* TFitParticleEScaledMomDev *neu = new TFitParticleEScaledMomDev( "neu", "neu", &neutrino, &mn ); */
	    TFitParticleEtEtaPhi *bl  = new TFitParticleEtEtaPhi( "bl",  "bl",  &bjlep,    &mbl );
	    TFitParticleEtEtaPhi *bh  = new TFitParticleEtEtaPhi( "bh",  "bh",  &bjhad,    &mbh );
	    TFitParticleEtEtaPhi *cj  = new TFitParticleEtEtaPhi( "cj",  "cj",  &cjhad,    &mc );
	    TFitParticleEtEtaPhi *sj  = new TFitParticleEtEtaPhi( "sj",  "sj",  &sjhad,    &ms );
	    
	    //leptoniccally decayed top constrain
	    TFitConstraintM *ltop = new TFitConstraintM( "ltop", "leptonic top", 0, 0 , mTop); // Values set from PDG 2021 mTop = 172.76
	    ltop->addParticles1( lep, neu, bl );
	    //hadronically decayed top constrain
	    TFitConstraintM *htop = new TFitConstraintM( "htop", "hadronic top", 0, 0 , mTop); // Values set from PDG 2021 mTop = 172.76
	    htop->addParticles1( bh, cj, sj );
	    
	    TFitConstraintM *lW = new TFitConstraintM( "lW", "W mass", 0, 0 , 80.379); // Values set from PDG 2021 mW = 80.379
	    lW->addParticles1( lep, neu);

	    
	    /* TFitConstraintEp *sumPxConstr_  = new TFitConstraintEp("SumPx",        "SumPx", nullptr, TFitConstraintEp::pX, 0.); */
	    /* TFitConstraintEp *sumPyConstr_  = new TFitConstraintEp("SumPy",        "SumPy", nullptr, TFitConstraintEp::pY, 0.); */
	    /* TFitConstraintEp *sumPzConstr_  = new TFitConstraintEp("SumPz",        "SumPz", nullptr, TFitConstraintEp::pZ, 0.); */
	    /* TFitConstraintEp *sumEConstr_   = new TFitConstraintEp("SumE",        "SumE", nullptr, TFitConstraintEp::E, mTop+mTop); */

	    /* sumPxConstr_->addParticles(lep, neu, bl, bh, cj, sj); */
	    /* sumPyConstr_->addParticles(lep, neu, bl, bh, cj, sj); */
	    /* sumPzConstr_->addParticles(lep, neu, bl, bh, cj, sj); */
	    /* sumEConstr_->addParticles(lep, neu, bl, bh, cj, sj); */

	    /* sumPxConstr_->setConstraint( lepton.Px() + neutrino.Px() + bjlep.Px() + bjhad.Px() + cjhad.Px() + sjhad.Px() ); */
	    /* sumPyConstr_->setConstraint( lepton.Py() + neutrino.Py() + bjlep.Py() + bjhad.Py() + cjhad.Py() + sjhad.Py() ); */
	    /* sumPzConstr_->setConstraint( lepton.Pz() + neutrino.Pz() + bjlep.Pz() + bjhad.Pz() + cjhad.Pz() + sjhad.Pz() ); */
	    /* sumEConstr_->setConstraint( lepton.E() + neutrino.E() + bjlep.E() + bjhad.E() + cjhad.E() + sjhad.E() ); */
	    
	    TKinFitter* fitter = new TKinFitter("fitter", "fitter");
	    fitter->addMeasParticle( lep );
	    fitter->addMeasParticle( neu );
	    fitter->addMeasParticle( bl );
	    fitter->addMeasParticle( bh );
	    fitter->addMeasParticle( cj );
	    fitter->addMeasParticle( sj );
	    fitter->addConstraint( ltop );
	    fitter->addConstraint( htop );
	    fitter->addConstraint( lW );
	    /* fitter->addConstraint(sumPxConstr_); */
	    /* fitter->addConstraint(sumPyConstr_); */
	    /* fitter->addConstraint(sumPzConstr_); */
	    /* fitter->addConstraint(sumEConstr_); */
	    
	    // Tested with 2016 analysis
	    fitter->setMaxNbIter( 500 );
	    fitter->setMaxDeltaS( 5e-05 );
	    fitter->setMaxF( 0.0001 );
	    fitter->setVerbosity(0);
	    
	    //print(fitter);
	    fitter->fit();
	    //print(fitter);

	    /* cout<<"====== After fit"<<endl; */
	    /* mn.Print(); */
	    /* cout<<"====== After fit"<<endl; */
	    /* cout<<endl; */

	    /* if(fitter->getStatus()==0 and fitter->getS() < Chi2){ */
	    /*   Chi2	 = fitter->getS() ; */
	    /*   NDF	 = fitter->getNDF();  */
	    /*   Nb_Iter	 = fitter->getNbIter(); */
	    /*   blep_id	 = bjetlist.at(ib1) ;  */
	    /*   bhad_id	 = bjetlist.at(ib2) ;  */
	    /*   chad_id	 = ij1 ; */
	    /*   shad_id	 = ij2 ; */
	    /*   leptonUM	 = lepton ; */
	    /*   neutrinoUM = neutrino ; */
	    /*   bjlepUM	 = bjlep ; */
	    /*   bjhadUM	 = bjhad ; */
	    /*   cjhadUM	 = cjhad ; */
	    /*   sjhadUM	 = sjhad ; */
	    /*   leptonAF	 = *(fitter->get4Vec(0)); */
	    /*   neutrinoAF = *(fitter->get4Vec(1)); */
	    /*   bjlepAF	 = *(fitter->get4Vec(2)); */
	    /*   bjhadAF	 = *(fitter->get4Vec(3)); */
	    /*   cjhadAF	 = *(fitter->get4Vec(4)); */
	    /*   sjhadAF	 = *(fitter->get4Vec(5)); */
	    /*   goodCombo	 = true; */
	    /* } */

	    if(fitter->getStatus()==0){
	      Chi2.push_back( fitter->getS() );
	      NDF.push_back( fitter->getNDF() ); 
	      Nb_Iter.push_back( fitter->getNbIter() );
	      blep_id.push_back( list2jet[ib1] ); 
	      bhad_id.push_back( list2jet[ib2] ); 
	      chad_id.push_back( list2jet[ij1] );
	      shad_id.push_back( list2jet[ij2] );
	      leptonUM.push_back( lepton );
	      neutrinoUM.push_back( neutrino );
	      bjlepUM.push_back( bjlep );
	      bjhadUM.push_back( bjhad );
	      cjhadUM.push_back( cjhad );
	      sjhadUM.push_back( sjhad );
	      leptonAF.push_back( *(fitter->get4Vec(0)) );
	      neutrinoAF.push_back( *(fitter->get4Vec(1)) );
	      bjlepAF.push_back( *(fitter->get4Vec(2)) );
	      bjhadAF.push_back( *(fitter->get4Vec(3)) );
	      cjhadAF.push_back( *(fitter->get4Vec(4)) );
	      sjhadAF.push_back( *(fitter->get4Vec(5)) );
	      ReslepEta.push_back(reslepEta);
	      ReslepPhi.push_back(reslepPhi);
	      ResneuEta.push_back(resneuEta);
	      ResneuPhi.push_back(resneuPhi);
	      ResbjlepEta.push_back(resbjlepEta);
	      ResbjlepPhi.push_back(resbjlepPhi);
	      ResbjhadEta.push_back(resbjhadEta);
	      ResbjhadPhi.push_back(resbjhadPhi);
	      RescjhadEta.push_back(rescjhadEta);
	      RescjhadPhi.push_back(rescjhadPhi);
	      RessjhadEta.push_back(ressjhadEta);
	      RessjhadPhi.push_back(ressjhadPhi); 
	      goodCombo = true;
	      nCombinations++ ;
	    }
	    
	    delete lep;
	    delete neu;
	    delete bl;
	    delete bh;
	    delete cj;
	    delete sj;
	    delete ltop;
	    delete htop;
	    delete fitter;
	      
	  }//inu_root
	}//ijet 2 
      }//ijet 1
    }//bjet 2
  }//bjet 1
    
  //cout<<endl<<endl;

  bjetlist.clear();
  ljetlist.clear();
  list2jet.clear();
  
  return goodCombo;
  
}
