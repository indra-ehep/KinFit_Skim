#ifndef SELECTOR_H
#define SELECTOR_H

#include <vector>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <TH1F.h>
#include <TMath.h>
#include <TLorentzVector.h>
#include "EventTree.h"

#include "Utils.h"

#include "../interface/JetResolution.h"
//#include "interface/JERScaleFactors.h"


#include "TRandom3.h"
#include <bitset>

#include "../interface/JetResolution.h"
#include "../interface/JetResolutionObject.h"
//#include"interface/JERScaleFactors.h"

#include <random>

#include "../interface/RoccoR.h"

//https://indico.cern.ch/event/482673/contributions/2187022/attachments/1282446/1905912/talk_electron_ID_spring16.pdf
static const double electronEA[7] = {0.1703,
									 0.1715,
									 0.1213,
									 0.1230,
									 0.1635,
									 0.1937,
									 0.2393};



//double dR(double eta1, double phi1, double eta2, double phi2);

class Selector{
public:
  enum TheRunEra{
		 y2016B,y2016C,y2016D,y2016E,y2016F,y2016G,y2016H,
		 y2017B,y2017C,y2017D,y2017E,y2017F,
		 y2018A,y2018B,y2018C,y2018D,
		 y2016MC,
		 y2017MC,
		 y2018MC,
		 yUL2016B,yUL2016C,yUL2016D,yUL2016E,yUL2016F,yUL2016Flate,yUL2016G,yUL2016H,
		 yUL2017B,yUL2017C,yUL2017D,yUL2017E,yUL2017F,
		 yUL2018A,yUL2018B,yUL2018C,yUL2018D,
		 yUL2016MCAPV,
		 yUL2016MCnonAPV,
		 yUL2017MC,
		 yUL2018MC
  };
	Selector();
	~Selector();
	
	void process_objects(string path, EventTree* inp_tree);
	
	std::vector<int> Electrons;
	std::vector<int> ElectronsLoose;
	std::vector<int> ElectronsMedium;
	std::vector<int> ElectronsNoIso;
	std::vector<int> ElectronsNoIsoLoose;

	std::vector<int> Muons;
	std::vector<int> MuonsLoose;
	std::vector<int> MuonsNoIso;
	std::vector<int> MuonsNoIsoLoose;
        std::vector<int> MuonsMiniAOD;

	std::vector<int> Jets;
	std::vector<int> bJets;
        std::vector<int> FwdJets;

	std::vector<double> jet_resolution;
	std::vector<bool>   jet_isTagged;
	
	std::vector<double> MuRelIso_corr;

	/* std::vector<double> JetsJERPt; */
	/* std::vector<double> JetsPreSelPt; */
	/* std::vector<double> JetsCleaningPt; */
	/* std::vector<int> JetsPreSel; */
	/* std::vector<int> JetsCleaning; */
	std::vector<double> JetsPtSmeared;

	std::vector<int> JetsNoCorr;

	float METPt;
	float METPhi;
	float METUnc;
	bool selectMETUnc ;

	bool isNanoAOD;
        bool isPVGood;
	
	double jet_Pt_cut;
	double jet_Eta_cut;
	double btag_cut;
	double btag_cuta;
	double btag_cutb;
	
	double ctag_CvsB_L_cut;
	double ctag_CvsL_L_cut;
	double ctag_CvsB_M_cut;
	double ctag_CvsL_M_cut;
	double ctag_CvsB_T_cut;
	double ctag_CvsL_T_cut;
	
	double ctag_CvsB_L_cuta;
	double ctag_CvsL_L_cuta;
	double ctag_CvsB_M_cuta;
	double ctag_CvsL_M_cuta;
	double ctag_CvsB_T_cuta;
	double ctag_CvsL_T_cuta;

	double ctag_CvsB_L_cutb;
	double ctag_CvsL_L_cutb;
	double ctag_CvsB_M_cutb;
	double ctag_CvsL_M_cutb;
	double ctag_CvsB_T_cutb;
	double ctag_CvsL_T_cutb;

	double btag_cut_DeepCSV;
        double btag_cut_DeepCSVa;
        double btag_cut_DeepCSVb;
	double veto_lep_jet_dR;
	int JERsystLevel; //0= syst down, 1 = central, 2 = syst up
	int JECsystLevel;//0= syst down, 1 = central, 2 = syst up
	int elesmearLevel;
	int elescaleLevel;
	bool   smearJetPt;
	bool scaleEle;
	bool smearEle;
	bool   looseJetID;
	bool   useDeepCSVbTag;
	bool   QCDselect;
	bool   DDselect;
	bool isPreVFP,isPostVFP ;

	bool  looseJetID_miniAOD;

	// electrons
	double ele_Pt_cut;
	double ele_PtLoose_cut;
	double ele_Eta_cut;
	double ele_EtaLoose_cut;
	double ele_Ptmedium_cut;
	double ele_RelIso_range[2];
	double ele_RelIsoLoose_cut;
	double ele_MVA_range[2];
	double ele_cutbased_range[2];
	double ele_MVALoose_cut;
	double ele_Dxy_cut;
	int    ele_MissInnHit_cut;
	bool   ele_Iso_MVA_invert;
        float  ele_RelIso_tight_EB ;
        float ele_RelIso_tight_EE ;
        float  ele_RelIso_loose_EB ;
        float ele_RelIso_loose_EE ;
        int nEleSelIso;
  
	// muons
	double mu_PtLoose_cut;
	double mu_RelIsoLoose_cut;
	double mu_RelIso_range[2];
 	double mu_MVA_range[2];
	bool   mu_Iso_invert;
	double mu_Eta_loose;
	double mu_Eta_tight;
	double mu_Pt_cut;
	double mu_RelIso_tight;
	double mu_RelIso_loose;
	int nMuSelIso ;
	//muons miniAOD
	float mu_Pt_cut_miniAOD;
        int s;
        int m;  

	//electron miniAOD
	float ele_Pt_cut_miniAOD ;
	float ele_Eta_cut_miniAOD ;
	float ele_muon_dR_miniAOD ;

	//jets miniAOD
	float jet_Pt_cut_miniAOD ; 
	float jet_Eta_cut_miniAOD ;
	float veto_lep_jet_dR_miniAOD ;


	std::string year;

	int printEvent;
	bool IsDebug ;

	void clear_vectors();
	
	void init_JER(std::string inputPrefix);
	void init_RoccoR(std::string inputPath);

	void filter_electrons(EventTree* tr);
	void filter_muons(EventTree* tr);
	void filter_jets();
	void filter_jetsNoCorr();
	void filter_mets();
	void metWithUncl();
        std::pair<double,double> METXYCorr_Met_MetPhi(double, double, int, TString, bool, int, bool, bool);

private:
	EventTree* tree;

	/* double JER(int jetInd); */
	
	// effective areas, see Selector.cpp for more information
	double eleEffArea03(double SCEta);
	double muEffArea04(double muEta);

	bool passEleID(int eleInd, int cutVal, bool doRelisoCut);
	//	bool passEleVetoID(int eleInd, bool doRelisoCut);
	JME::JetResolution *jetResolution;
	JME::JetResolutionScaleFactor *jetResolutionScaleFactor;
	JME::JetResolution *jetResolutiona;
	JME::JetResolutionScaleFactor *jetResolutionScaleFactora;
	JME::JetResolution *jetResolutionb;
	JME::JetResolutionScaleFactor *jetResolutionScaleFactorb;
	JME::JetParameters jetParam;
	
        RoccoR rc17;
        RoccoR rc18;
	RoccoR rc16;
        RoccoR rc16a;
        RoccoR rc16b;

};

class Selector_gen{
public:
        Selector_gen();
        ~Selector_gen();

        void process_objects(EventTree* inp_tree);

        std::vector<int> Electrons;
        std::vector<int> ElectronsLoose;
        std::vector<int> ElectronsMedium;
        std::vector<int> ElectronsNoIso;
        std::vector<int> Muons;
        std::vector<int> MuonsLoose;
        std::vector<int> MuonsNoIso;
        std::vector<int> Jets;
        std::vector<int> bJets;
        std::vector<int> FwdJets;
        std::vector<double> MuRelIso_corr;

        double jet_Pt_cut;
        double jet_Eta_cut;
        double btag_cut;
        double btag_cut_DeepCSV;
        bool   useDeepCSVbTag;
        double veto_lep_jet_dR;
	double ele_Pt_cut;
        double ele_PtLoose_cut;
        double ele_Eta_cut;
        double ele_EtaLoose_cut;
        double mu_Eta_loose;
        double mu_Eta_tight;
        double mu_Pt_cut;
        double mu_RelIso_tight;
        double mu_RelIso_loose;
        double ele_Ptmedium_cut;
        double ele_RelIso_range[2];
        double ele_RelIsoLoose_cut;
        double ele_MVA_range[2];
        double ele_cutbased_range[2];
        double ele_MVALoose_cut;
        double ele_Dxy_cut;
        int    ele_MissInnHit_cut;
        bool   ele_Iso_MVA_invert;

	double mu_PtLoose_cut;
        double mu_RelIsoLoose_cut;
        double mu_RelIso_range[2];
        double mu_MVA_range[2];
        bool   mu_Iso_invert;

        void clear_vectors();
	EventTree* tree;
        void filter_electrons();
        void filter_muons();
        void filter_jets();
	 double eleEffArea03(double SCEta);
        double muEffArea04(double muEta);

        bool passEleTightID(int eleInd, bool doRelisoCut);
        bool passEleVetoID(int eleInd, bool doRelisoCut);
};
       
#endif
