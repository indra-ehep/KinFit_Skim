
//////////////////////////
// Cross Sections Used  //
//////////////////////////

std::map<std::string, vector<double> > crossSections;
std::map<std::string, vector<double> > numberOfEvents;

void initCrossSections(){

  // Corresponding to AN2021_224_v8.pdf 
  crossSections["HminusM040"] = {266.16, 266.16, 266.16};
  crossSections["HminusM050"] = {266.16, 266.16, 266.16};
  crossSections["HminusM060"] = {266.16, 266.16, 266.16};
  crossSections["HminusM070"] = {266.16, 266.16, 266.16};
  crossSections["HminusM080"] = {266.16, 266.16, 266.16};
  crossSections["HminusM090"] = {266.16, 266.16, 266.16};
  crossSections["HminusM100"] = {266.16, 266.16, 266.16};
  crossSections["HminusM110"] = {266.16, 266.16, 266.16};
  crossSections["HminusM120"] = {266.16, 266.16, 266.16};
  crossSections["HminusM130"] = {266.16, 266.16, 266.16};
  crossSections["HminusM140"] = {266.16, 266.16, 266.16};
  crossSections["HminusM150"] = {266.16, 266.16, 266.16};
  crossSections["HminusM155"] = {266.16, 266.16, 266.16};
  crossSections["HminusM160"] = {266.16, 266.16, 266.16};

  crossSections["HplusM040"] = {266.16, 266.16, 266.16};
  crossSections["HplusM050"] = {266.16, 266.16, 266.16};
  crossSections["HplusM060"] = {266.16, 266.16, 266.16};
  crossSections["HplusM070"] = {266.16, 266.16, 266.16};
  crossSections["HplusM080"] = {266.16, 266.16, 266.16};
  crossSections["HplusM090"] = {266.16, 266.16, 266.16};
  crossSections["HplusM100"] = {266.16, 266.16, 266.16};
  crossSections["HplusM110"] = {266.16, 266.16, 266.16};
  crossSections["HplusM120"] = {266.16, 266.16, 266.16}; 
  crossSections["HplusM130"] = {266.16, 266.16, 266.16};
  crossSections["HplusM140"] = {266.16, 266.16, 266.16};
  crossSections["HplusM150"] = {266.16, 266.16, 266.16};
  crossSections["HplusM155"] = {266.16, 266.16, 266.16};
  crossSections["HplusM160"] = {266.16, 266.16, 266.16};


  //================================
  //Updated following GEN OR by Soti
  //================================

  // Corresponding to AN2021_224_v8.pdf 
  /* crossSections["TTbarPowheg_Dilepton"]			 =  { 87.315, 87.315, 87.315}; */
  /* crossSections["TTbarPowheg_Semilept"]			 =  {364.352,364.352,364.352}; */
  /* crossSections["TTbarPowheg_Hadronic"]			 =  {380.095,380.095,380.095}; */

  // https://twiki.cern.ch/twiki/bin/view/LHCPhysics/TtbarNNLO (version r21, 2023-03-03, WolfgangWagner) = 833.9 pb
  //Multiply by the numbers of eqn A,B,C of https://pdg.lbl.gov/2023/reviews/rpp2022-rev-top-quark.pdf, i.e. 45.7%, 43.8%,10.5% for hadronic, semileptonic and dilepton channels, respectively
  crossSections["TTbarPowheg_Dilepton"]			 =  { 87.559, 87.559, 87.559};
  crossSections["TTbarPowheg_Semilept"]			 =  {365.248,365.248,365.248};
  crossSections["TTbarPowheg_Hadronic"]			 =  {381.092,381.092,381.092};
  
  crossSections["TTbarPowheg_Dilepton_CP5up"]		 =  { 87.559, 87.559, 87.559};
  crossSections["TTbarPowheg_Dilepton_CP5down"]		 =  { 87.559, 87.559, 87.559};
  crossSections["TTbarPowheg_Dilepton_hdampup"]		 =  { 87.559, 87.559, 87.559};
  crossSections["TTbarPowheg_Dilepton_hdampdown"]	 =  { 87.559, 87.559, 87.559};
  crossSections["TTbarPowheg_Dilepton_mtop1715"]	 =  { 87.559, 87.559, 87.559};
  crossSections["TTbarPowheg_Dilepton_mtop1735"]	 =  { 87.559, 87.559, 87.559};

  crossSections["TTbarPowheg_Semilept_CP5up"]		 =  {365.248,365.248,365.248};
  crossSections["TTbarPowheg_Semilept_CP5down"]		 =  {365.248,365.248,365.248};
  crossSections["TTbarPowheg_Semilept_hdampup"]		 =  {365.248,365.248,365.248};
  crossSections["TTbarPowheg_Semilept_hdampdown"]	 =  {365.248,365.248,365.248};
  crossSections["TTbarPowheg_Semilept_mtop1715"]	 =  {365.248,365.248,365.248};
  crossSections["TTbarPowheg_Semilept_mtop1735"]	 =  {365.248,365.248,365.248};
    
  crossSections["TTbarPowheg_Hadronic_CP5up"]		 =  {381.092,381.092,381.092};
  crossSections["TTbarPowheg_Hadronic_CP5down"]		 =  {381.092,381.092,381.092};
  crossSections["TTbarPowheg_Hadronic_hdampup"]		 =  {381.092,381.092,381.092};
  crossSections["TTbarPowheg_Hadronic_hdampdown"]	 =  {381.092,381.092,381.092};
  crossSections["TTbarPowheg_Hadronic_mtop1715"]	 =  {381.092,381.092,381.092};
  crossSections["TTbarPowheg_Hadronic_mtop1735"]	 =  {381.092,381.092,381.092};
  
  // MiniAOD and Corresponding to AN2021_224_v8.pdf 
  /* crossSections["ST_s_channel"]	=  {  3.36,   3.36,   3.36}; */
  /* crossSections["ST_t_channel"]	=  {136.02, 136.02, 136.02}; */
  /* crossSections["ST_tbar_channel"]	=  { 80.95,  80.95,  80.95}; */
  /* crossSections["ST_tW_channel"]	=  { 35.85,  35.85,  35.85}; */
  /* crossSections["ST_tbarW_channel"]	=  { 35.85,  35.85,  35.85}; */

  //https://twiki.cern.ch/twiki/bin/view/LHCPhysics/SingleTopNNLORef (version r20, 2023-02-27, LukasKretschmann)
  crossSections["ST_s_channel"]		=  {  3.42,   3.42,   3.42}; 
  crossSections["ST_t_channel"]		=  { 134.2,  134.2,  134.2};
  crossSections["ST_tbar_channel"]	=  {  80.0,   80.0,   80.0};
  crossSections["ST_tW_channel"]	=  { 39.65,  39.65,  39.65};
  crossSections["ST_tbarW_channel"]	=  { 39.65,  39.65,  39.65};

  // MiniAOD and Corresponding to AN2021_224_v8.pdf 
  crossSections["Wjets"]	=  {50690., 50690., 50690.};
  crossSections["W1jets"]	=  {9493.0, 9493.0, 9493.0};
  crossSections["W2jets"]	=  {3120.0, 3120.0, 3120.0}; 
  crossSections["W3jets"]	=  { 942.3,  942.3,  942.3};
  crossSections["W4jets"]	=  { 524.2,  524.2,  524.2};

  // MiniAOD and Corresponding to AN2021_224_v8.pdf 
  crossSections["DYjetsM10to50"]	=  {15810.0, 15810.0, 15810.0}; 
  crossSections["DY1jetsM10to50"]	= {565.30, 565.30, 565.30};
  crossSections["DY2jetsM10to50"]	= {314.80, 314.80, 314.80};
  crossSections["DY3jetsM10to50"]	= {76.94, 76.94, 76.94};
  crossSections["DY4jetsM10to50"]	= {28.61, 28.61, 28.61};

  // MiniAOD and Corresponding to AN2021_224_v8.pdf 
  crossSections["DYjetsM50"]	=  {4963.0, 4963.0, 4963.0}; 
  crossSections["DY1jetsM50"]	=  {1012.0, 1012.0, 1012.0}; 
  crossSections["DY2jetsM50"]	=  { 334.7,  334.7,  334.7}; 
  crossSections["DY3jetsM50"]	=  { 102.3,  102.3,  102.3}; 
  crossSections["DY4jetsM50"]	=  { 54.52,  54.52,  54.52}; 
  
  /* // MiniAOD and Corresponding to AN2021_224_v8.pdf  */
  /* crossSections["WW"]	= {118.7, 118.7, 118.7};  */
  /* crossSections["WZ"]	= {46.74, 46.74, 46.74};  */
  /* crossSections["ZZ"]	= {17.72, 17.72, 17.72};  */
  
  //New following GEN OR
  crossSections["WW"]	= {118.7, 118.7, 118.7}; //https://arxiv.org/pdf/1408.5243.pdf
  crossSections["WZ"]	= {46.74, 46.74, 46.74}; //https://arxiv.org/pdf/1105.0020.pdf
  crossSections["ZZ"]	= {16.91, 16.91, 16.91}; //https://arxiv.org/pdf/1405.2219.pdf

  //First GEN OR following https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns (r155, 2022-11-02, IzaakNeutelings)
  /* crossSections["TTZToQQ"]		=  {0.5297, 0.5297, 0.5297}; */
  /* crossSections["TTZToLLNuNu"]	=  {0.2529, 0.2529, 0.2529}; */
  /* crossSections["TTWJetsToLNu"]	=  {0.2043, 0.2043, 0.2043}; */
  /* crossSections["TTWJetsToQQ"]	=  {0.4062, 0.4062, 0.4062}; */
  /* crossSections["TTGToLL"]		=  {2.2204, 2.2204, 2.2204}; //1.495(MCM page for LO)* kf (=1.4852) of B2G-23-001 */
  /* crossSections["TTGToLNu"]		=  {7.5092, 7.5092, 7.5092}; //5.056 * kf (=1.4852) of B2G-23-001 */
  /* crossSections["TTGToQQ"]		=  {6.1621, 6.1621, 6.1621}; //4.149 * kf (=1.4852) of B2G-23-001 */
  /* crossSections["TTHTobb"]		=  {0.2934, 0.2934, 0.2934}; */
  /* crossSections["TTHToNonbb"]	=  {0.2151, 0.2151, 0.2151}; */
  /* crossSections["TTHToGG"]		=  {0.0012, 0.0012, 0.0012}; */

  //https://link.springer.com/article/10.1140/epjc/s10052-019-6746-z
  crossSections["TTZToQQ"]      =  {0.6012, 0.6012, 0.6012}; //0.86 * br(Z->qq = 0.6991) https://pdg.lbl.gov/2022/listings/rpp2022-list-z-boson.pdf
  crossSections["TTZToLLNuNu"]  =  {0.2588, 0.2588, 0.2588}; //0.86 * br(Z->ll+missing = 1-0.6991) https://pdg.lbl.gov/2022/listings/rpp2022-list-z-boson.pdf
  crossSections["TTWJetsToLNu"] =  {0.1792, 0.1792, 0.1792}; //0.55 * br(W->lnu = 3*0.1086) https://pdg.lbl.gov/2022/listings/rpp2022-list-w-boson.pdf 
  crossSections["TTWJetsToQQ"]  =  {0.3708, 0.3708, 0.3708}; //0.55 * br(W->qq = 0.6741)

  crossSections["TTGToLL"]	=  {2.2204, 2.2204, 2.2204}; //1.495(MCM page for LO)* kf (=1.4852) of B2G-23-001 
  crossSections["TTGToLNu"]	=  {7.5092, 7.5092, 7.5092}; //5.056 * kf (=1.4852) of B2G-23-001
  crossSections["TTGToQQ"]	=  {6.1621, 6.1621, 6.1621}; //4.149 * kf (=1.4852) of B2G-23-001

  //https://twiki.cern.ch/twiki/bin/view/LHCPhysics/CERNYellowReportPageBR shared by Danny(IC)
  //https://e-publishing.cern.ch/index.php/CYRM/issue/view/32/3 (see appendix E for 13 TeV and mH=125.25 GeV as in https://pdg.lbl.gov/2022/listings/rpp2022-list-higgs-boson.pdf) = 504.75 fb (NLO+EW)
  crossSections["TTHTobb"]      =  {0.2919, 0.2919, 0.2919}; //0.50475 * br(SM H->bb = 0.5784 for mH=125.25 GeV ) https://twiki.cern.ch/twiki/bin/view/LHCPhysics/CERNYellowReportPageBR (version r22, 2016-12-08, MarcoPieri)
  crossSections["TTHToNonbb"]   =  {0.2128, 0.2128, 0.2128}; //0.50475 * br(SM H->nonbb = 1-0.5784 for mH=125.25 GeV ) https://twiki.cern.ch/twiki/bin/view/LHCPhysics/CERNYellowReportPageBR (version r22, 2016-12-08, MarcoPieri)
  crossSections["TTHToGG"]      =  {0.0011, 0.0011, 0.0011}; //0.50475 * br(SM H->gamma gamma = 0.002270 for mH=125.25 GeV ) https://twiki.cern.ch/twiki/bin/view/LHCPhysics/CERNYellowReportPageBR (version r22, 2016-12-08, MarcoPieri)

  // MiniAOD and Corresponding to AN2021_224_v8.pdf (not important due to DD application in analysis)
  crossSections["QCD_Pt15to20_Mu"]	= {2799000.00, 2799000.00, 2799000.00};
  crossSections["QCD_Pt20to30_Mu"]	= {2538000.00, 2538000.00, 2538000.00};
  crossSections["QCD_Pt30to50_Mu"]	= {1359000.00, 1359000.00, 1359000.00};
  crossSections["QCD_Pt50to80_Mu"]	= {377000.00, 377000.00, 377000.00};
  crossSections["QCD_Pt80to120_Mu"]	= {87470.00, 87470.00, 87470.00};
  crossSections["QCD_Pt120to170_Mu"]	= {21280.00, 21280.00, 21280.00};
  crossSections["QCD_Pt170to300_Mu"]	= {7012.00, 7012.00, 7012.00};
  crossSections["QCD_Pt300to470_Mu"]	= {617.20, 617.20, 617.20};
  crossSections["QCD_Pt470to600_Mu"]	= {59.20, 59.20, 59.20};
  crossSections["QCD_Pt600to800_Mu"]	= {18.20, 18.20, 18.20};
  crossSections["QCD_Pt800to1000_Mu"]	= {3.21, 3.21, 3.21};
  crossSections["QCD_Pt1000toInf_Mu"]	= {1.09, 1.09, 1.09};

  crossSections["QCD_Pt20to30_Ele"]	= {4865000.00, 4865000.00, 4865000.00};
  crossSections["QCD_Pt30to50_Ele"]	= {6287000.00, 6287000.00, 6287000.00};
  crossSections["QCD_Pt50to80_Ele"]	= {1990000.00, 1990000.00, 1990000.00};
  crossSections["QCD_Pt80to120_Ele"]	= {358600.00, 358600.00, 358600.00};
  crossSections["QCD_Pt120to170_Ele"]	= {66860.00, 66860.00, 66860.00};
  crossSections["QCD_Pt170to300_Ele"]	= {16320.00, 16320.00, 16320.00};
  crossSections["QCD_Pt300toInf_Ele"]	= {1088.00, 1088.00, 1088.00};  

  //The following were used as a test purpose for 2017 and not planned for final result
  crossSections["TTTT"]		=  {0.009103, 0.009103, 0.009103};
  crossSections["WWW"]		=  {0.2086, 0.2086, 0.2086};
  crossSections["WWZ"]		=  {0.1651, 0.1651, 0.1651};
  crossSections["WZZ"]		=  {0.05565, 0.05565, 0.05565};
  crossSections["ZZZ"]		=  {0.01398, 0.01398, 0.01398};
  crossSections["WWG"]		=  {0.2147, 0.2147, 0.2147};
  crossSections["WZG"]		=  {0.04123, 0.05565, 0.05565};
  crossSections["VHToGG"]	=  {2.456, 2.456, 2.456}; //check XSDB corresponding to dataset in CMS DAS as well as AN2022_104_v6.pdf of HIG-23-004
  crossSections["VHToNonbb"]	=  {2.605, 2.605, 2.605}; //check XSDB corresponding to dataset in CMS DAS as well as AN2022_156_v18.pdf of HIG-23-007
  crossSections["VHToEE"]	=  {2.439, 2.439, 2.439}; //check XSDB corresponding to dataset in CMS DAS
    
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

