
//////////////////////////
// Cross Sections Used  //
//////////////////////////

std::map<std::string, vector<double> > crossSections;
std::map<std::string, vector<double> > numberOfEvents;

void initCrossSections(){

    crossSections["TTbarPowheg_inclusive"]     	=  {831.76, 831.76, 831.76};  //ttbar NNLO (http://inspirehep.net/search?p=find+eprint+1112.5675)
    crossSections["TTbarPowheg_Dilepton"]       =  { 87.315, 87.315, 87.315};
    crossSections["TTbarPowheg_Semilept"]       =  {364.352,364.352,364.352};
    crossSections["TTbarPowheg_Hadronic"]       =  {380.095,380.095,380.095};
    crossSections["TTbarMadgraph_inclusive"]    =  {831.76, 831.76, 831.76};
    
    crossSections["TTbarPowheg_Dilepton_CP5up"]		 =  { 87.315, 87.315, 87.315};
    crossSections["TTbarPowheg_Dilepton_CP5down"]	 =  { 87.315, 87.315, 87.315};
    crossSections["TTbarPowheg_Dilepton_hdampup"]	 =  { 87.315, 87.315, 87.315};
    crossSections["TTbarPowheg_Dilepton_hdampdown"]      =  { 87.315, 87.315, 87.315};
    crossSections["TTbarPowheg_Dilepton_mtop1695"]       =  { 87.315, 87.315, 87.315};
    crossSections["TTbarPowheg_Dilepton_mtop1755"]       =  { 87.315, 87.315, 87.315};

    crossSections["TTbarPowheg_Semilept_CP5up"]		 =  {364.352,364.352,364.352};
    crossSections["TTbarPowheg_Semilept_CP5down"]	 =  {364.352,364.352,364.352};
    crossSections["TTbarPowheg_Semilept_hdampup"]	 =  {364.352,364.352,364.352};
    crossSections["TTbarPowheg_Semilept_hdampdown"]      =  {364.352,364.352,364.352};
    crossSections["TTbarPowheg_Semilept_mtop1695"]       =  {364.352,364.352,364.352};
    crossSections["TTbarPowheg_Semilept_mtop1755"]       =  {364.352,364.352,364.352};
    
    crossSections["TTbarPowheg_Hadronic_CP5up"]		 =  {380.095,380.095,380.095};
    crossSections["TTbarPowheg_Hadronic_CP5down"]	 =  {380.095,380.095,380.095};
    crossSections["TTbarPowheg_Hadronic_hdampup"]	 =  {380.095,380.095,380.095};
    crossSections["TTbarPowheg_Hadronic_hdampdown"]      =  {380.095,380.095,380.095};
    crossSections["TTbarPowheg_Hadronic_mtop1695"]       =  {380.095,380.095,380.095};
    crossSections["TTbarPowheg_Hadronic_mtop1755"]       =  {380.095,380.095,380.095};
    
    // Obtained using CMSDAS and CMS_XSDB
    //crossSections["TTbarPowheg_Dilepton"]       =  { 88.29, 88.29, 88.29}; //687.1
    //crossSections["TTbarPowheg_Semilept"]       =  {365.34, 365.34, 365.34}; //687.1
    //crossSections["TTbarPowheg_Hadronic"]       =  {377.96, 377.96, 377.96}; //687.1
    
    numberOfEvents["TTbarPowheg_Dilepton"]       =  { 67926800.,  1.0,  1.0}; 
    numberOfEvents["TTbarPowheg_Semilept"]       =  {107604800.,  1.0,  1.0}; 
    numberOfEvents["TTbarPowheg_Hadronic"]       =  { 68518800.,  1.0,  1.0}; 
    
    // // Default setting
    /* crossSections["HplusM080"]               =  {6.77, 6.77, 6.77};  */
    // //MiniAOD setting
    crossSections["HplusM080"]                  =  {21.55, 21.55, 21.55}; //831.76*0.2132*scaleSig; 
    //with scaleSig = 0.12155 = 2*0.065*(1-0.065), where 6.5% is the observed limit for 90 GeV at 8 TeV
    crossSections["HplusM090"]                  =  {21.55, 21.55, 21.55}; 
    crossSections["HplusM100"]                  =  {21.55, 21.55, 21.55}; 
    crossSections["HplusM110"]                  =  {21.55, 21.55, 21.55}; 
    crossSections["HplusM120"]                  =  {21.55, 21.55, 21.55}; 
    crossSections["HplusM130"]                  =  {21.55, 21.55, 21.55}; 
    crossSections["HplusM140"]                  =  {21.55, 21.55, 21.55}; 
    crossSections["HplusM150"]                  =  {21.55, 21.55, 21.55}; 
    crossSections["HplusM155"]                  =  {21.55, 21.55, 21.55}; 
    crossSections["HplusM160"]                  =  {21.55, 21.55, 21.55}; 
    
    numberOfEvents["HplusM080"]                 =  { 1.0,  1.0,  1.0}; 
    numberOfEvents["HplusM090"]                 =  { 1.0,  1.0,  1.0}; 
    numberOfEvents["HplusM100"]                 =  { 1.0,  1.0,  1.0}; 
    numberOfEvents["HplusM120"]                 =  { 1000000.,  1.0,  1.0}; 
    numberOfEvents["HplusM140"]                 =  { 1.0,  1.0,  1.0}; 
    numberOfEvents["HplusM150"]                 =  { 1.0,  1.0,  1.0}; 
    numberOfEvents["HplusM155"]                 =  { 1.0,  1.0,  1.0}; 
    numberOfEvents["HplusM160"]                 =  { 1.0,  1.0,  1.0}; 

    // Obtained from MiniAOD except s_channel using the updated https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns#Single_top
    crossSections["ST_s_channel"]		=  {3.36, 3.36, 3.36}; //// Default setting
    /* crossSections["ST_s_channel"]		=  { 10.32,  10.32,  10.32}; */
    crossSections["ST_t_channel"]		=  {136.02, 136.02, 136.02};
    crossSections["ST_tbar_channel"]		=  { 80.95,  80.95,  80.95};
    crossSections["ST_tW_channel"]		=  { 35.85,  35.85,  35.85};
    crossSections["ST_tbarW_channel"]		=  { 35.85,  35.85,  35.85};
    
    // Obtained using CMSDAS and CMS_XSDB
    /* crossSections["ST_s_channel"]		=  { 3.74,  3.74,  3.74};  */
    /* crossSections["ST_t_channel"]		=  {113.3, 113.3, 113.3}; */
    /* crossSections["ST_tbar_channel"]		=  {67.91, 67.91, 67.91}; */
    /* crossSections["ST_tW_channel"]		=  {34.91, 34.91, 34.91}; */
    /* crossSections["ST_tbarW_channel"]		=  {34.97, 34.97, 34.97}; */
    
    numberOfEvents["ST_s_channel"]		=  { 9842599.0,  1.0,  1.0}; 
    numberOfEvents["ST_t_channel"]		=  {31848000.0,  1.0,  1.0};
    numberOfEvents["ST_tbar_channel"]		=  {17780700.0,  1.0,  1.0};
    numberOfEvents["ST_tW_channel"]		=  { 4983500.0,  1.0,  1.0};
    numberOfEvents["ST_tbarW_channel"]		=  { 4980600.0,  1.0,  1.0};
    
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

    /* numberOfEvents["DYjetsM50"]			=  {146280395.0,  1.0,  1.0}; */
    /* numberOfEvents["DYjetsM50_ext1"]		=  {146280395.0,  1.0,  1.0}; */
    /* numberOfEvents["DYjetsM50_ext2"]		=  {146280395.0,  1.0,  1.0}; */
    /* numberOfEvents["DYjetsM10to50"]		=  { 35114961.0,  1.0,  1.0}; */
    /* numberOfEvents["DYjetsM10to50_ext1"]	=  { 35114961.0,  1.0,  1.0}; */
    /* numberOfEvents["DY1jetsM50"]		=  { 63730337.0,  1.0,  1.0}; */
    /* numberOfEvents["DY2jetsM50"]		=  { 19879279.0,  1.0,  1.0}; */
    /* numberOfEvents["DY2jetsM50_ext1"]	       	=  { 19879279.0,  1.0,  1.0}; */
    /* numberOfEvents["DY3jetsM50"]		=  {  5857441.0,  1.0,  1.0}; */
    /* numberOfEvents["DY4jetsM50"]		=  {  4197868.0,  1.0,  1.0}; */

    numberOfEvents["DYjetsM50_ext1"]		=  { 49748967.0,  1.0,  1.0};
    numberOfEvents["DY1jetsM50"]		=  { 63730337.0,  1.0,  1.0};
    numberOfEvents["DY2jetsM50"]		=  { 19879279.0,  1.0,  1.0};
    numberOfEvents["DY3jetsM50"]		=  {  5857441.0,  1.0,  1.0};
    numberOfEvents["DY4jetsM50"]		=  {  4197868.0,  1.0,  1.0};
    
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
    //MiniAOD
    crossSections["W1jets"]			=  {9493.0, 9493.0, 9493.0};//9493.0;
    crossSections["W2jets"]			=  {3120.0, 3120.0, 3120.0}; //3120.0;
    crossSections["W2jets_ext1"]		=  {3120.0, 3120.0, 3120.0}; //3120.0;
    crossSections["W3jets"]			=  { 942.3,  942.3,  942.3};//942.3;
    crossSections["W3jets_ext1"]		=  { 942.3,  942.3,  942.3};//942.3;
    crossSections["W4jets"]			=  { 524.2,  524.2,  524.2};//524.2;
    crossSections["W4jets_ext1"]		=  { 524.2,  524.2,  524.2};//524.2;
    crossSections["W4jets_ext2"]		=  { 524.2,  524.2,  524.2};//524.2;
    crossSections["Wjets"]			=  {50690., 50690., 50690.};//50380.0;
    crossSections["Wjets_ext1"]			=  {50690., 50690., 50690.};//524.2;
    crossSections["Wjets_ext2"]			=  {50690., 50690., 50690.};//524.2;
    crossSections["WJetsToQQ"]			=  {95.14, 95.14, 95.14};  //Added

    /* // Obtained using CMSDAS and CMS_XSDB */
    /* crossSections["W1jets"]			=  {9625.0, 9625.0, 9625.0}; //9578.0 */
    /* crossSections["W2jets"]			=  {3161.0, 3161.0, 3161.0}; //3154.0; */
    /* crossSections["W2jets_ext1"]		=  {3161.0, 3161.0, 3161.0};  */
    /* crossSections["W3jets"]			=  { 958.0,  958.0,  958.0}; // */
    /* crossSections["W3jets_ext1"]		=  { 958.0,  958.0,  958.0};//942.3; */
    /* crossSections["W4jets"]			=  { 494.6,  494.6,  494.6};//495.7; */
    /* crossSections["W4jets_ext1"]		=  { 494.6,  494.6,  494.6};//524.2; */
    /* crossSections["W4jets_ext2"]		=  { 494.6,  494.6,  494.6};//524.2; */
    /* crossSections["Wjets"]			=  {50260., 50260., 50260.};//50380.0; */
    /* crossSections["Wjets_ext1"]			=  {50260., 50260., 50260.};//524.2; */
    /* crossSections["Wjets_ext2"]			=  {50260., 50260., 50260.};//524.2; */
    /* crossSections["WJetsToQQ"]			=  {95.14, 95.14, 95.14};  //Added */

    /* numberOfEvents["W1jets"]			=  { 43773492.0,  1.0,  1.0}; */
    /* numberOfEvents["W2jets"]			=  { 60366929.0,  1.0,  1.0}; */
    /* numberOfEvents["W2jets_ext1"]		=  { 60366929.0,  1.0,  1.0}; */
    /* numberOfEvents["W3jets"]			=  { 59300029.0,  1.0,  1.0}; */
    /* numberOfEvents["W3jets_ext1"]		=  { 59300029.0,  1.0,  1.0}; */
    /* numberOfEvents["W4jets"]			=  { 29941394.0,  1.0,  1.0}; */
    /* numberOfEvents["W4jets_ext1"]		=  { 29941394.0,  1.0,  1.0}; */
    /* numberOfEvents["W4jets_ext2"]		=  { 29941394.0,  1.0,  1.0}; */
    /* numberOfEvents["Wjets"]			=  { 86413370.0,  1.0,  1.0}; */
    /* numberOfEvents["Wjets_ext1"]		=  { 86413370.0,  1.0,  1.0}; */
    /* numberOfEvents["Wjets_ext2"]		=  { 86413370.0,  1.0,  1.0}; */

    numberOfEvents["W1jets"]			=  { 43773492.0,  1.0,  1.0};
    numberOfEvents["W2jets"]			=  { 29992425.0,  1.0,  1.0};
    numberOfEvents["W3jets"]			=  { 19798117.0,  1.0,  1.0};
    numberOfEvents["W4jets"]			=  { 9116657.0,  1.0,  1.0};
    numberOfEvents["Wjets"]			=  { 29010935.0,  1.0,  1.0};


    numberOfEvents["WJetsToQQ"]			=  { 1.0,  1.0,  1.0};  //Added
    
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
    crossSections["WW"]				= {118.7, 118.7, 118.7};
    crossSections["WW_ext1"]			= {118.7, 118.7, 118.7};
    crossSections["WZ"]				= {46.74, 46.74, 46.74};
    crossSections["WZ_ext1"]			= {46.74, 46.74, 46.74};
    crossSections["ZZ"]				= {17.72, 17.72, 17.72};
    crossSections["ZZ_ext1"]			= {17.72, 17.72, 17.72};
    // Obtained using CMSDAS and CMS_XSDB
    /* crossSections["WW"]				= { 64.3,  64.3,  64.3}; // 64.28 */
    /* crossSections["WW_ext1"]			= { 64.3,  64.3,  64.3}; */
    /* crossSections["WZ"]				= {23.43, 23.43, 23.43}; // 23.48 */
    /* crossSections["WZ_ext1"]			= {23.43, 23.43, 23.43}; */
    /* crossSections["ZZ"]				= {10.16, 10.16, 10.16}; */
    /* crossSections["ZZ_ext1"]			= {10.16, 10.16, 10.16}; */

    /* numberOfEvents["WW"]	       		= { 7982180.0,  1.0,  1.0}; */
    /* numberOfEvents["WW_ext1"]			= { 7982180.0,  1.0,  1.0}; */
    /* numberOfEvents["WZ"]       			= { 3997571.0,  1.0,  1.0}; */
    /* numberOfEvents["WZ_ext1"]			= { 3997571.0,  1.0,  1.0}; */
    /* numberOfEvents["ZZ"]       			= { 1988098.0,  1.0,  1.0}; */
    /* numberOfEvents["ZZ_ext1"]			= { 1988098.0,  1.0,  1.0}; */
    
    numberOfEvents["WW"]	       		= { 994012.0,  1.0,  1.0};
    numberOfEvents["WZ"]       			= { 1000000.0,  1.0,  1.0};
    numberOfEvents["ZZ"]       			= { 990064.0,  1.0,  1.0};
    
    //numberOfEvents["TTbarPowheg_Dilepton"]       =  { 1.0,  1.0,  1.0}; 

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

double getEvtWeight(string sampleType, int year, double luminosity){
    
    double evtWeight = -1.;

    if( sampleType.substr(0,4)=="Data") {evtWeight = 1.;}
    else if( sampleType=="Test") {evtWeight = 1.;}
    else if( sampleType=="TestAll") {evtWeight = 1.;}
    else if( sampleType=="TestFull") {evtWeight = 1.;}
    else {
      //	initCrossSections();
      if (crossSections.find(sampleType) != crossSections.end()) {
	int index = year - 2016;
	evtWeight = crossSections[sampleType][index] * luminosity / numberOfEvents[sampleType][index];
	//xss = crossSections[sampleType][index];
	cout << "total events " << numberOfEvents[sampleType][index] << endl;
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
    /* cout << "XS = " << evtWeight/luminosity*nEvents_MC << endl; */
    cout << "lumi = " << luminosity << endl;
    /* cout << "nEvents_MC = " << nEvents_MC << endl; */
    
    return evtWeight;
}

