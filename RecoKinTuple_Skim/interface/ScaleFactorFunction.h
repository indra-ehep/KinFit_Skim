
//////////////////////////
// Cross Sections Used  //
//////////////////////////

std::map<std::string, vector<double> > crossSections;

void initCrossSections(){

    crossSections["TTbarPowheg"]		=  {831.76, 831.76, 831.76};  //ttbar NNLO (http://inspirehep.net/search?p=find+eprint+1112.5675)
    /* crossSections["TTbarPowheg_Dilepton"]       =  { 87.315, 87.315, 87.315}; */
    /* crossSections["TTbarPowheg_Semilept"]       =  {364.352,364.352,364.352}; */
    /* crossSections["TTbarPowheg_Hadronic"]       =  {380.095,380.095,380.095}; */
    // Obtained using CMSDAS and CMS_XSDB
    crossSections["TTbarPowheg_Dilepton"]       =  { 88.29, 88.29, 88.29}; //687.1
    crossSections["TTbarPowheg_Semilept"]       =  {365.34, 365.34, 365.34}; //687.1
    crossSections["TTbarPowheg_Hadronic"]       =  {377.96, 377.96, 377.96}; //687.1


    // // Default setting
    /* crossSections["HplusM080"]               =  {6.77, 6.77, 6.77};  */
    // //MiniAOD setting
    crossSections["HplusM080"]                  =  {21.55, 21.55, 21.55}; 
    crossSections["HplusM090"]                  =  {21.55, 21.55, 21.55}; 
    crossSections["HplusM100"]                  =  {21.55, 21.55, 21.55}; 
    crossSections["HplusM120"]                  =  {21.55, 21.55, 21.55}; 
    crossSections["HplusM140"]                  =  {21.55, 21.55, 21.55}; 
    crossSections["HplusM150"]                  =  {21.55, 21.55, 21.55}; 
    crossSections["HplusM155"]                  =  {21.55, 21.55, 21.55}; 
    crossSections["HplusM160"]                  =  {21.55, 21.55, 21.55}; 

    //crossSections["ST_s_channel"]		=  {3.68064, 3.68064, 3.68064}; //// Default setting
    /* crossSections["ST_s_channel"]		=  { 10.32,  10.32,  10.32}; */
    /* crossSections["ST_t_channel"]		=  {136.02, 136.02, 136.02}; */
    /* crossSections["ST_tbar_channel"]		=  { 80.95,  80.95,  80.95}; */
    /* crossSections["ST_tW_channel"]		=  { 35.85,  35.85,  35.85}; */
    /* crossSections["ST_tbarW_channel"]		=  { 35.85,  35.85,  35.85}; */

    // Obtained using CMSDAS and CMS_XSDB
    crossSections["ST_s_channel"]		=  { 3.74,  3.74,  3.74}; 
    crossSections["ST_t_channel"]		=  {113.3, 113.3, 113.3};
    crossSections["ST_tbar_channel"]		=  {67.91, 67.91, 67.91};
    crossSections["ST_tW_channel"]		=  {34.91, 34.91, 34.91};
    crossSections["ST_tbarW_channel"]		=  {34.97, 34.97, 34.97};

    // // Default
    /* crossSections["DYjetsM50"]		=  {6077.22, 6077.22, 6077.22}; //https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns */
    /* crossSections["DYjetsM50_ext1"]		=  {6077.22, 6077.22, 6077.22}; //https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns */
    /* crossSections["DYjetsM50_ext2"]		=  {6077.22, 6077.22, 6077.22}; //https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns */
    /* crossSections["DYjetsM10to50"]		=  {18610., 18610., 18610.}; //https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns */
    /* crossSections["DYjetsM10to50_ext1"]	=  {18610., 18610., 18610.}; //https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns */
    // Obtained using CMSDAS and CMS_XSDB
    crossSections["DYjetsM50"]			=  {4963.0, 4963.0, 4963.0}; // 4957. , 6077.22 (NNLO) so kf = 1.2245 for LO=4963
    crossSections["DYjetsM50_ext1"]		=  {4963.0, 4963.0, 4963.0};
    crossSections["DYjetsM50_ext2"]		=  {4963.0, 4963.0, 4963.0};
    crossSections["DYjetsM10to50"]		=  {16270.0, 16270.0, 16270.0}; //16290.
    crossSections["DYjetsM10to50_ext1"]		=  {16270.0, 16270.0, 16270.0}; 
    crossSections["DY1jetsM50"]			=  {1012.0, 1012.0, 1012.0}; //1003.0 
    crossSections["DY2jetsM50"]			=  { 334.7,  334.7,  334.7}; //336.7 
    crossSections["DY2jetsM50_ext1"]	       	=  { 334.7,  334.7,  334.7}; 
    crossSections["DY3jetsM50"]			=  { 102.3,  102.3,  102.3}; //102.9 
    crossSections["DY4jetsM50"]			=  { 54.52,  54.52,  54.52}; //54.71 

    // Unused crossSections["WjetsInclusive"]   = {61526.7, 61526.7, 61526.7}; //https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns#W_jets
    // // Default
    /* crossSections["W1jets"]			=  {11775.9345, 11775.9345, 11775.9345};//9493.0; */
    /* crossSections["W2jets"]			=  { 3839.4345,  3839.4345,  3839.4345}; //3120.0; */
    /* crossSections["W2jets_ext1"]		=  { 3839.4345,  3839.4345,  3839.4345}; //3120.0; */
    /* crossSections["W3jets"]			=  { 1165.8108,  1165.8108,  1165.8108};//942.3; */
    /* crossSections["W3jets_ext1"]		=  { 1165.8108,  1165.8108,  1165.8108};//942.3; */
    /* crossSections["W4jets"]			=  {  592.9176,   592.9176,   592.9176};//524.2; */
    /* crossSections["W4jets_ext1"]		=  {  592.9176,   592.9176,   592.9176};//524.2; */
    /* crossSections["W4jets_ext2"]		=  {  592.9176,   592.9176,   592.9176};//524.2; */
    // //MiniAOD
    /* crossSections["W1jets"]			=  {9493.0, 9493.0, 9493.0};//9493.0; */
    /* crossSections["W2jets"]			=  {3120.0, 3120.0, 3120.0}; //3120.0; */
    /* crossSections["W2jets_ext1"]		=  {3120.0, 3120.0, 3120.0}; //3120.0; */
    /* crossSections["W3jets"]			=  { 942.3,  942.3,  942.3};//942.3; */
    /* crossSections["W3jets_ext1"]		=  { 942.3,  942.3,  942.3};//942.3; */
    /* crossSections["W4jets"]			=  { 524.2,  524.2,  524.2};//524.2; */
    /* crossSections["W4jets_ext1"]		=  { 524.2,  524.2,  524.2};//524.2; */
    /* crossSections["W4jets_ext2"]		=  { 524.2,  524.2,  524.2};//524.2; */
    /* crossSections["WJetsToQQ"]			=  {95.14, 95.14, 95.14};  //Added */
    // Obtained using CMSDAS and CMS_XSDB
    crossSections["W1jets"]			=  {9625.0, 9625.0, 9625.0}; //9578.0
    crossSections["W2jets"]			=  {3161.0, 3161.0, 3161.0}; //3154.0;
    crossSections["W2jets_ext1"]		=  {3161.0, 3161.0, 3161.0}; 
    crossSections["W3jets"]			=  { 958.0,  958.0,  958.0}; //
    crossSections["W3jets_ext1"]		=  { 958.0,  958.0,  958.0};//942.3;
    crossSections["W4jets"]			=  { 494.6,  494.6,  494.6};//495.7;
    crossSections["W4jets_ext1"]		=  { 494.6,  494.6,  494.6};//524.2;
    crossSections["W4jets_ext2"]		=  { 494.6,  494.6,  494.6};//524.2;
    crossSections["Wjets"]			=  {50260., 50260., 50260.};//50380.0;
    crossSections["Wjets_ext1"]			=  {50260., 50260., 50260.};//524.2;
    crossSections["Wjets_ext2"]			=  {50260., 50260., 50260.};//524.2;
    crossSections["WJetsToQQ"]			=  {95.14, 95.14, 95.14};  //Added

    /* crossSections["DYjetsM10to50"]		= {18610.0, 18610.0, 18610.0};  */
    /* crossSections["DYjetsM50"]		= {6077.22, 6077.22, 6077.22}; */

    // // Default
    /* crossSections["WW"]				= {75.8 ,75.8 ,75.8 }; */
    /* crossSections["WW_ext1"]			= {75.8 ,75.8 ,75.8 }; */
    /* crossSections["WZ"]				= {27.6 ,27.6 ,27.6 }; */
    /* crossSections["WZ_ext1"]			= {27.6 ,27.6 ,27.6 }; */
    /* crossSections["ZZ"]				= {12.14,12.14,12.14}; */
    /* crossSections["ZZ_ext1"]			= {12.14,12.14,12.14}; */
    // MiniAOD
    /* crossSections["WW"]				= {118.7, 118.7, 118.7}; */
    /* crossSections["WW_ext1"]			= {118.7, 118.7, 118.7}; */
    /* crossSections["WZ"]				= {46.74, 46.74, 46.74}; */
    /* crossSections["WZ_ext1"]			= {46.74, 46.74, 46.74}; */
    /* crossSections["ZZ"]				= {17.72, 17.72, 17.72}; */
    /* crossSections["ZZ_ext1"]			= {17.72, 17.72, 17.72}; */
    // Obtained using CMSDAS and CMS_XSDB
    crossSections["WW"]				= { 64.3,  64.3,  64.3}; // 64.28
    crossSections["WW_ext1"]			= { 64.3,  64.3,  64.3};
    crossSections["WZ"]				= {23.43, 23.43, 23.43}; // 23.48
    crossSections["WZ_ext1"]			= {23.43, 23.43, 23.43};
    crossSections["ZZ"]				= {10.16, 10.16, 10.16};
    crossSections["ZZ_ext1"]			= {10.16, 10.16, 10.16};


    crossSections["TTWtoQQ"]			=  {0.4062, 0.4062, 0.4062}; //https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns
    crossSections["TTWtoLNu"]			=  {0.2043, 0.2043, 0.2043}; //https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns
    crossSections["TTWtoLNu_ext1"]		=  {0.2043, 0.2043, 0.2043}; //https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns
    crossSections["TTWtoLNu_ext2"]		=  {0.2043, 0.2043, 0.2043}; //https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns
    crossSections["TTZtoLL"]			=  {0.2728, 0.2728, 0.2728};  //????? https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns lists it as 0.2529
    crossSections["TTZtoLL_ext1"]		=  {0.2728, 0.2728, 0.2728};  //????? https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns lists it as 0.2529
    crossSections["TTZtoLL_ext2"]		=  {0.2728, 0.2728, 0.2728};  //????? https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns lists it as 0.2529
    crossSections["TTZtoLL_ext3"]		=  {0.2728, 0.2728, 0.2728};  //????? https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns lists it as 0.2529
    crossSections["TTZtoLL_M1to10"]		=  {0.0493, 0.0493, 0.0493};  //????? https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns lists it as 0.2529
    crossSections["TTZtoQQ"]			=  {0.5297, 0.5297, 0.5297};  //????? https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns lists it as 0.2529
    crossSections["TTZtoQQ_ext1"]		=  {0.5297, 0.5297, 0.5297};  //????? https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns lists it as 0.2529


    crossSections["WWToLNuQQ"]			= {49.997, 49.997, 49.997};
    crossSections["WWToLNuQQ_powheg"]		= {49.997, 49.997, 49.997};
    crossSections["WWToLNuQQ_powheg_ext1"]      = {49.997, 49.997, 49.997};
    crossSections["WWTo1L1Nu2Q_amcatnlo"]	= {49.997, 49.997, 49.997}; // Added : Could not find in above twiki so copied from above copied from above 
    crossSections["WWTo4Q"]			= {51.723, 51.723, 51.723};
    crossSections["WWTo4Q_powheg"]		= {51.723, 51.723, 51.723};
    crossSections["WWTo2L2Nu_powheg"]		= { 12.178, 12.178, 12.178}; // Added

    crossSections["WZTo1L3Nu"]			= { 3.033  ,  3.033  ,  3.033  };
    crossSections["WZTo1L3Nu_amcatnlo"]		= { 3.033  ,  3.033  ,  3.033  };
    crossSections["WZTo1L1Nu2Q"]		= {10.71   , 10.71   , 10.71   };
    crossSections["WZTo1L1Nu2Q_amcatnlo"]	= {10.71   , 10.71   , 10.71   };
    crossSections["WZTo2L2Q"]			= { 5.595  ,  5.595  ,  5.595  };
    crossSections["WZTo2L2Q_amcatnlo"]		= { 5.595  ,  5.595  ,  5.595  };
    crossSections["WZTo3LNu"]			= { 4.42965,  4.42965,  4.42965};
    crossSections["WZTo3LNu_amcatnlo"]		= { 4.42965,  4.42965,  4.42965};
    crossSections["WZTo3LNu_amcatnlo_ext1"]     = { 4.42965,  4.42965,  4.42965};
    crossSections["WZTo3LNu_powheg"]		= { 4.42965,  4.42965,  4.42965};
    crossSections["WZTo3LNu_powheg_ext1"]	= { 4.42965,  4.42965,  4.42965};

    crossSections["ZZTo2L2Q"]			= { 3.28, 3.28, 3.28};
    crossSections["ZZTo2L2Q_amcatnlo"]		= { 3.28, 3.28, 3.28};
    crossSections["ZZTo2L2Q_powheg"]		= { 3.28, 3.28, 3.28};
    crossSections["ZZTo2L2Nu_powheg"]		= { 0.564, 0.564, 0.564}; // Added
    crossSections["ZZTo2L2Nu_powheg_ext1"]      = { 0.564, 0.564, 0.564}; // Added
    crossSections["ZZTo2L2Nu_powheg_ext2"]      = { 0.564, 0.564, 0.564}; // Added
    crossSections["ZZTo2Q2Nu"]			= { 4.04, 4.04, 4.04};
    crossSections["ZZTo2Q2Nu_powheg"]		= { 4.04, 4.04, 4.04};
    crossSections["ZZTo2Q2Nu_amcatnlo"]		= { 4.04, 4.04, 4.04};
    crossSections["ZZTo4L"]			= { 1.3816, 1.3816, 1.3816};
    crossSections["ZZTo4L_powheg"]		= { 1.3816, 1.3816, 1.3816};
    crossSections["ZZTo4L_powheg_ext1"]         = { 1.3816, 1.3816, 1.3816};
    crossSections["ZZTo4L_powheg_ext2"]         = { 1.3816, 1.3816, 1.3816};
    crossSections["ZZTo4L_amcatnlo"]		= { 1.3816, 1.3816, 1.3816};

    crossSections["VVTo2L2Nu"]			= {11.95, 11.95, 11.95};
    crossSections["VVTo2L2Nu_amcatnlo"]		= {11.95, 11.95, 11.95};
    crossSections["VVTo2L2Nu_amcatnlo_ext1"]    = {11.95, 11.95, 11.95}; //Added

    
    //Product fo XS and filter eff from table at:
    //https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns#QCD
    crossSections["QCD_Pt15to20_Mu"]		= {3819570.0, 3819570.0, 3819570.0};
    crossSections["QCD_Pt20to30_Mu"]		= {2960198.4   , 2960198.4   , 2960198.4   };
    crossSections["QCD_Pt30to50_Mu"]		= {1652471.46  , 1652471.46  , 1652471.46  };
    crossSections["QCD_Pt50to80_Mu"]		= { 437504.1   ,  437504.1   ,  437504.1   };
    crossSections["QCD_Pt80to120_Mu"]		= { 106033.6648,  106033.6648,  106033.6648};
    crossSections["QCD_Pt80to120_Mu_ext1"]	= { 106033.6648,  106033.6648,  106033.6648};
    crossSections["QCD_Pt120to170_Mu"]		= {  25190.5151,   25190.5151,   25190.5151};
    crossSections["QCD_Pt120to170_Mu_ext1"]	= {  25190.5151,   25190.5151,   25190.5151};
    crossSections["QCD_Pt170to300_Mu"]		= {   8654.4932,    8654.4932,    8654.4932};
    crossSections["QCD_Pt170to300_Mu_ext1"]	= {   8654.4932,    8654.4932,    8654.4932};
    crossSections["QCD_Pt300to470_Mu"]		= {    797.3527,     797.3527,     797.3527};
    crossSections["QCD_Pt300to470_Mu_ext1"]	= {    797.3527,     797.3527,     797.3527};
    crossSections["QCD_Pt300to470_Mu_ext2"]	= {    797.3527,     797.3527,     797.3527};
    crossSections["QCD_Pt300to470_Mu_ext3"]	= {    797.3527,     797.3527,     797.3527};
    crossSections["QCD_Pt470to600_Mu"]		= {     79.0255,      79.0255,      79.0255};
    crossSections["QCD_Pt470to600_Mu_ext1"]	= {     79.0255,      79.0255,      79.0255};
    crossSections["QCD_Pt470to600_Mu_ext2"]	= {     79.0255,      79.0255,      79.0255};
    crossSections["QCD_Pt600to800_Mu"]		= {     25.0951,      25.0951,      25.0951};
    crossSections["QCD_Pt600to800_Mu_ext1"]	= {     25.0951,      25.0951,      25.0951};
    crossSections["QCD_Pt800to1000_Mu"]		= {      4.7074,       4.7074,       4.7074};
    crossSections["QCD_Pt800to1000_Mu_ext1"]	= {      4.7074,       4.7074,       4.7074};
    crossSections["QCD_Pt800to1000_Mu_ext2"]	= {      4.7074,       4.7074,       4.7074};
    crossSections["QCD_Pt1000toInf_Mu"]		= {      1.6213,       1.6213,       1.6213};
    crossSections["QCD_Pt1000toInf_Mu_ext1"]	= {      1.6213,       1.6213,       1.6213};
    crossSections["QCD_Pt20to30_Ele"]		= {5352960., 5352960., 5352960.};
    crossSections["QCD_Pt30to50_Ele"]		= {9928000., 9928000., 9928000.};
    crossSections["QCD_Pt30to50_Ele_ext1"]	= {9928000., 9928000., 9928000.};
    crossSections["QCD_Pt50to80_Ele"]		= {2890800., 2890800., 2890800.};
    crossSections["QCD_Pt50to80_Ele_ext1"]	= {2890800., 2890800., 2890800.};
    crossSections["QCD_Pt80to120_Ele"]		= { 350000.,  350000.,  350000.};
    crossSections["QCD_Pt80to120_Ele_ext1"]	= { 350000.,  350000.,  350000.};
    crossSections["QCD_Pt120to170_Ele"]		= {  62964.,   62964.,   62964.};
    crossSections["QCD_Pt120to170_Ele_ext1"]	= {  62964.,   62964.,   62964.};
    crossSections["QCD_Pt170to300_Ele"]		= {  18810.,   18810.,   18810.};
    crossSections["QCD_Pt300toInf_Ele"]		= {   1350.,    1350.,    1350.};

    return;
}

double getEvtWeight(string sampleType, int year, double luminosity, double nEvents_MC, float& xss){
    
    double evtWeight = -1.;

    if( sampleType.substr(0,4)=="Data") {evtWeight = 1.;}
    else if( sampleType=="Test") {evtWeight = 1.;}
    else if( sampleType=="TestAll") {evtWeight = 1.;}
    else if( sampleType=="TestFull") {evtWeight = 1.;}
    else {
	//	initCrossSections();
	if (crossSections.find(sampleType) != crossSections.end()) {
	    int index = year - 2016;
	    evtWeight = crossSections[sampleType][index] * luminosity / nEvents_MC;
	    xss = crossSections[sampleType][index];
	}
	else {
	    cout << "-------------------------------------------------" << endl;
	    cout << "-------------------------------------------------" << endl;
	    cout << "-- Unable to find event weight for this sample --" << endl;
	    cout << "-- Sample will be saved with a weight of -1    --" << endl;
	    cout << "-------------------------------------------------" << endl;
	    cout << "-------------------------------------------------" << endl;
	}
    }
    cout << "Using event weight " << evtWeight << endl;
    cout << "XS = " << evtWeight/luminosity*nEvents_MC << endl;
    cout << "lumi = " << luminosity << endl;
    cout << "nEvents_MC = " << nEvents_MC << endl;
    
    return evtWeight;
}

