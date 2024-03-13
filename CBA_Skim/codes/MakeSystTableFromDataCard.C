/**********************************************************************
 Created on : 12/03/2024
 Purpose    : Make systematics table from Datacard
 Author     : Indranil Das, Visiting Fellow
 Email      : indranil.das@cern.ch | indra.ehep@gmail.com
**********************************************************************/
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <map>
#include <TFile.h>
#include <TH1F.h>

int MakeSystTableFromDataCard()
{
  string indir="91_no-dijet-edge-effect_bld";
  const char* nuisances[] = {"lumi_13TeV", "lumi_16", "lumi_17", "lumi_18", "lumi_17_18", "eff", "prefire", "pujetid", "pileup", "absmpfb", "absscl", "absstat", "flavorqcd",
			    "frag", "timepteta", "pudatamc", "puptbb", "puptec1", "puptec2", "pupthf", "puptref", "relfsr", "relbal",
			    "relsample", "reljerec1", "reljerec2", "relptbb", "relptec1", "relptec2", "relpthf", "relstatfsr", "relstathf", "relstatec",
			    "singpiecal", "singpihcal", "JER", "norm_sig", "norm_tt ", "norm_ttg", "norm_tth", "norm_ttz", "norm_ttw", "norm_stop",
			    "norm_wjet", "norm_zjet", "norm_qcd_", "norm_vv",  "CP5", "hDamp", "topMass", "pdf", "isr", "bcstat",
			    "bclhemuf", "bclhemur", "bcxdyb", "bcxdyc", "bcxwjc", "bcintp", "bcextp", "topPt"};//58
  const int nM = 14;
  const int ncT = 3;
  map<string,map<int,float>> syst_array[ncT][nM];
  map<string,int> chid[ncT][nM];
  map<string,pair<double,double>> yield[2][ncT][nM];
  int mass[nM] = {40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 155, 160};
  
  int ReadDataCard(string, int, string, int, string, const char* [], map<string,map<int,float>>&, map<string,int>&);
  int WriteSystTable(int year, string ch, string cTag, const char* [], map<string,map<int,float>> [], map<string,int> []);
  int GetYieldResult(string, int, string, int, string, map<string,pair<double,double>>&, map<string,int>);
  int WriteYieldTable(int year, map<string,pair<double,double>> [][3][14], map<string,int> [][14]);
  
  for(int year=2016; year<=2018 ; year++){
    for(int im=0;im<nM;im++){
      ReadDataCard(indir, year, "mu", mass[im], "L", nuisances, syst_array[0][im], chid[0][im]);
      ReadDataCard(indir, year, "mu", mass[im], "M", nuisances, syst_array[1][im], chid[1][im]);
      ReadDataCard(indir, year, "mu", mass[im], "T", nuisances, syst_array[2][im], chid[2][im]);

      GetYieldResult(indir, year, "mu", mass[im], "L", yield[0][0][im], chid[0][im]);
      GetYieldResult(indir, year, "mu", mass[im], "M", yield[0][1][im], chid[1][im]);
      GetYieldResult(indir, year, "mu", mass[im], "T", yield[0][2][im], chid[2][im]);
    }
    WriteSystTable(year, "mu", "L", nuisances, syst_array[0], chid[0]);
    WriteSystTable(year, "mu", "M", nuisances, syst_array[1], chid[1]);
    WriteSystTable(year, "mu", "T", nuisances, syst_array[2], chid[2]);
    
    for(int im=0;im<nM;im++){
      ReadDataCard(indir, year, "ele", mass[im], "L", nuisances, syst_array[0][im], chid[0][im]);
      ReadDataCard(indir, year, "ele", mass[im], "M", nuisances, syst_array[1][im], chid[1][im]);
      ReadDataCard(indir, year, "ele", mass[im], "T", nuisances, syst_array[2][im], chid[2][im]);
      
      GetYieldResult(indir, year, "ele", mass[im], "L", yield[1][0][im], chid[0][im]);
      GetYieldResult(indir, year, "ele", mass[im], "M", yield[1][1][im], chid[1][im]);
      GetYieldResult(indir, year, "ele", mass[im], "T", yield[1][2][im], chid[2][im]);
    }
    WriteSystTable(year, "ele", "L", nuisances, syst_array[0], chid[0]);
    WriteSystTable(year, "ele", "M", nuisances, syst_array[1], chid[1]);
    WriteSystTable(year, "ele", "T", nuisances, syst_array[2], chid[2]);

    WriteYieldTable(year, yield, chid);
  }
  
  //ReadDataCard(indir, 2016, "mu", mass[0], "L", nuisances, syst_array[0][0], chid[0][0]);
  //GetYieldResult(indir, 2016, "mu", mass[0], "L", yield[0][0], chid[0][0]);
  
  return true;
}

int WriteYieldTable(int year, map<string,pair<double,double>> yield[][3][14], map<string,int> chid[][14])
{
  int PrintYield(string, string, int, ofstream&, map<string,pair<double,double>> [][3][14]);
  
  ofstream outFile;
  outFile.open("syst/mjjTable_yield_"+to_string(year)+".tex");
  outFile<<"\\documentclass[]{article}"<<endl;
  outFile<<"\\usepackage{amsmath}"<<endl;
  outFile<<"\\usepackage{array}"<<endl;
  outFile<<"\\usepackage{multirow}"<<endl;
  outFile<<"\\usepackage{graphicx}"<<endl;
  outFile<<"\\usepackage{adjustbox}"<<endl;
  outFile<<"\\usepackage{pdflscape}"<<endl;
  outFile<<"\\usepackage[cm]{fullpage}"<<endl;
  outFile<<"\\begin{document}"<<endl;
  outFile<<""<<endl;
  outFile<<""<<endl;

  string nEvents = "$N_{events} \\pm stat$";

  string tab1_caption = "Event yield for exclusive charm tagging category in " + to_string(year) + ".";;
  outFile<<"\\begin{table}"<<endl;
  outFile<<"\\caption{"<<tab1_caption<<"}"<<endl;
  outFile<<"\\label{tab:sec07_eventYield_Exc_"<<year<<"}"<<endl;
  outFile<<"\\begin{adjustbox}{width=\\textwidth}"<<endl;
  outFile<<"\\begin{tabular}{cc cc cc cc}"<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<" Process & "<<nEvents<<"(ExcL) & "<<nEvents<<"(ExcL) & "<<nEvents<<"(ExcM) & "<<nEvents<<"(ExcM) & "<<nEvents<<"(ExcT) & "<<nEvents<<"(ExcT) \\\\ "<<endl;
  outFile<<" & $\\mu$ + jets &  e + jets & $\\mu$ + jets &  e + jets & $\\mu$ + jets &  e + jets\\\\"<<endl;
  outFile<<"\\hline "<<endl;
  PrintYield("$\\text{H}^{+} + \\text{H}^{-} (\\text{m}=40$ GeV)", "WH40", 0, outFile, yield);
  PrintYield("$\\text{H}^{+} + \\text{H}^{-} (\\text{m}=50$ GeV)", "WH50", 1, outFile, yield);
  PrintYield("$\\text{H}^{+} + \\text{H}^{-} (\\text{m}=60$ GeV)", "WH60", 2, outFile, yield);
  PrintYield("$\\text{H}^{+} + \\text{H}^{-} (\\text{m}=70$ GeV)", "WH70", 3, outFile, yield);
  PrintYield("$\\text{H}^{+} + \\text{H}^{-} (\\text{m}=80$ GeV)", "WH80", 4, outFile, yield);
  PrintYield("$\\text{H}^{+} + \\text{H}^{-} (\\text{m}=90$ GeV)", "WH90", 5, outFile, yield);
  PrintYield("$\\text{H}^{+} + \\text{H}^{-} (\\text{m}=100$ GeV)","WH100",6, outFile, yield);
  PrintYield("$\\text{H}^{+} + \\text{H}^{-} (\\text{m}=110$ GeV)","WH110",7, outFile, yield);
  PrintYield("$\\text{H}^{+} + \\text{H}^{-} (\\text{m}=120$ GeV)","WH120",8, outFile, yield);
  PrintYield("$\\text{H}^{+} + \\text{H}^{-} (\\text{m}=130$ GeV)","WH130",9, outFile, yield);
  PrintYield("$\\text{H}^{+} + \\text{H}^{-} (\\text{m}=140$ GeV)","WH140",10,outFile, yield);
  PrintYield("$\\text{H}^{+} + \\text{H}^{-} (\\text{m}=150$ GeV)","WH150",11,outFile, yield);
  PrintYield("$\\text{H}^{+} + \\text{H}^{-} (\\text{m}=155$ GeV)","WH155",12,outFile, yield);
  PrintYield("$\\text{H}^{+} + \\text{H}^{-} (\\text{m}=160$ GeV)","WH160",13,outFile, yield);
  outFile<<"\\hline "<<endl;
  PrintYield("SM $t\\bar{t}$ + jets", "ttbar", 0, outFile, yield);
  PrintYield("Single $t$","stop",0,outFile, yield);
  PrintYield("W + jets","wjet",0,outFile, yield);
  PrintYield("Z/$\\gamma$ + jets","zjet",0,outFile, yield);
  PrintYield("SM $t\\bar{t}\\gamma$ + jets","ttg",0,outFile, yield);
  PrintYield("SM $t\\bar{t}\\text{H}$ + jets","tth",0,outFile, yield);
  PrintYield("SM $t\\bar{t}\\text{Z}$ + jets","ttz",0,outFile, yield);
  PrintYield("SM $t\\bar{t}\\text{W}$ + jets","ttw",0,outFile, yield);
  PrintYield("VV","vv",0,outFile, yield);
  PrintYield("QCD multijet","qcd",0,outFile, yield);
  outFile<<"\\hline "<<endl;
  outFile<<"\\end{tabular}"<<endl;
  outFile<<"\\end{adjustbox}"<<endl;
  outFile<<"\\end{table}"<<endl;
  outFile<<""<<endl;
  outFile<<""<<endl;
  outFile<<"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"<<endl;
  outFile<<"\\end{document}"<<endl;
  outFile.close();


  return true;
}

int PrintYield(string mcname, string chname, int imass, ofstream& outFile, map<string,pair<double,double>> yield[][3][14])
{
  
  outFile << mcname << fixed << setprecision(1) 
	  << "& $" << yield[0][0][imass][chname].first << " \\pm " << yield[0][0][imass][chname].second << "$ "
	  << "& $" << yield[1][0][imass][chname].first << " \\pm " << yield[1][0][imass][chname].second << "$ "
	  << "& $" << yield[0][1][imass][chname].first << " \\pm " << yield[0][1][imass][chname].second << "$ "
	  << "& $" << yield[1][1][imass][chname].first << " \\pm " << yield[1][1][imass][chname].second << "$ "
    	  << "& $" << yield[0][2][imass][chname].first << " \\pm " << yield[0][2][imass][chname].second << "$ "
	  << "& $" << yield[1][2][imass][chname].first << " \\pm " << yield[1][2][imass][chname].second << "$ "
	  << "\\\\" << endl;
  
  return true;
}

int WriteSystTable(int year, string ch, string cTag, const char* nuisances[], map<string,map<int,float>> syst_array[], map<string,int> chid[])
{
  int PrintDiffSyst(string systfullname, string systnickname, ofstream&, const char* [], map<string,map<int,float>> [], map<string,int> []);
  string channel;
  if(ch.find("mu")!=string::npos)
    channel = "muon";
  else
    channel = "electron";

  string category;
  if(cTag.find("L")!=string::npos)
    category = "loose";
  else if(cTag.find("M")!=string::npos)
    category = "medium";
  else
    category = "tight";
  
  ofstream outFile;
  outFile.open("syst/mjjTable_"+ch+"_"+cTag+"_"+to_string(year)+".tex");
  outFile<<"\\documentclass[]{article}"<<endl;
  outFile<<"\\usepackage{amsmath}"<<endl;
  outFile<<"\\usepackage{array}"<<endl;
  outFile<<"\\usepackage{multirow}"<<endl;
  outFile<<"\\usepackage{graphicx}"<<endl;
  outFile<<"\\usepackage{adjustbox}"<<endl;
  outFile<<"\\usepackage{pdflscape}"<<endl;
  outFile<<"\\usepackage[cm]{fullpage}"<<endl;
  outFile<<"\\begin{document}"<<endl;
  outFile<<""<<endl;
  outFile<<""<<endl;
  string tab2_caption = "Systematic and statistical uncertainties in \\% for "+channel+" channel for exclusive "+category+" charm tagging category in " + to_string(year) + ".";;
  
  outFile<<"\\begin{table}"<<endl;
  outFile<<"\\centering\\caption{"+tab2_caption+"}"<<endl;
  outFile<<"\\label{tab:sec07_syst_Exc"<<cTag<<"_"<<ch<<"_"<<year<<"}"<<endl;
  outFile<<"\\begin{adjustbox}{width=\\textwidth}"<<endl;
  ///outFile<<"\\footnotesize\\setlength{\\tabcolsep}{0.3pt}"<<endl;
  outFile<<"\\begin{tabular}{ ll  cccc cccc cccc cccc cccc cccc}"<<endl;
  outFile<<"\\hline "<<endl;  

  outFile<<" Category & Nuisances "
	 <<"& {\\rotatebox{90}{$\\text{H}^{+} + \\text{H}^{-} (\\text{m}=40$ GeV)}} & {\\rotatebox{90}{$\\text{H}^{+} + \\text{H}^{-} (\\text{m}=50$ GeV)}} "
	 <<"& {\\rotatebox{90}{$\\text{H}^{+} + \\text{H}^{-} (\\text{m}=60$ GeV)}} & {\\rotatebox{90}{$\\text{H}^{+} + \\text{H}^{-} (\\text{m}=70$ GeV)}} "
	 <<"& {\\rotatebox{90}{$\\text{H}^{+} + \\text{H}^{-} (\\text{m}=80$ GeV)}} & {\\rotatebox{90}{$\\text{H}^{+} + \\text{H}^{-} (\\text{m}=90$ GeV)}} "
	 <<"& {\\rotatebox{90}{$\\text{H}^{+} + \\text{H}^{-} (\\text{m}=100$ GeV)}} & {\\rotatebox{90}{$\\text{H}^{+} + \\text{H}^{-} (\\text{m}=110$ GeV)}} "
	 <<"& {\\rotatebox{90}{$\\text{H}^{+} + \\text{H}^{-} (\\text{m}=120$ GeV)}} & {\\rotatebox{90}{$\\text{H}^{+} + \\text{H}^{-} (\\text{m}=130$ GeV)}} "
	 <<"& {\\rotatebox{90}{$\\text{H}^{+} + \\text{H}^{-} (\\text{m}=140$ GeV)}} & {\\rotatebox{90}{$\\text{H}^{+} + \\text{H}^{-} (\\text{m}=150$ GeV)}} "
	 <<"& {\\rotatebox{90}{$\\text{H}^{+} + \\text{H}^{-} (\\text{m}=155$ GeV)}} & {\\rotatebox{90}{$\\text{H}^{+} + \\text{H}^{-} (\\text{m}=160$ GeV)}} "
	 <<"& {\\rotatebox{90}{SM $t\\bar{t}$ + jets}} "
	 <<"& {\\rotatebox{90}{SM $t\\bar{t}\\gamma$ + jets}} "
    	 <<"& {\\rotatebox{90}{SM $t\\bar{t}\\text{H}$ + jets}} "
	 <<"& {\\rotatebox{90}{SM $t\\bar{t}\\text{Z}$ + jets}} "
    	 <<"& {\\rotatebox{90}{SM $t\\bar{t}\\text{W}$ + jets}} "
	 <<"& {\\rotatebox{90}{W + jets}} "
    	 <<"& {\\rotatebox{90}{Z/$\\gamma$ + jets}} "
	 <<"& {\\rotatebox{90}{Single $t$}} "
    	 <<"& {\\rotatebox{90}{VV}} "
	 <<"& {\\rotatebox{90}{QCD multijet}} "
	 <<"\\\\ " << endl;
  //pu, mu, btagb, btagl, prefire, jec, jer, norm
  outFile<<"\\hline "<<endl;
  outFile<<"\\multicolumn{26}{c}{"<<channel<<" + jets } \\\\"<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<category<<endl;  
  // const char* nuisances[] = {"lumi_13TeV", "lumi_16", "lumi_17", "lumi_18", "eff", "prefire", "pujetid", "pileup", "absmpfb", "absscl", "absstat", "flavorqcd",
  // 			    "frag", "timepteta", "pudatamc", "puptbb", "puptec1", "puptec2", "pupthf", "puptref", "relfsr", "relbal",
  // 			    "relsample", "reljerec1", "reljerec2", "relptbb", "relptec1", "relptec2", "relpthf", "relstatfsr", "relstathf", "relstatec",
  // 			    "singpiecal", "singpihcal", "JER", "norm_sig", "norm_tt ", "norm_ttg", "norm_tth", "norm_ttz", "norm_ttw", "norm_stop",
  // 			    "norm_wjet", "norm_zjet", "norm_qcd_", "norm_vv",  "CP5", "hDamp", "topMass", "pdf", "isr", "bcstat",
  // 			    "bclhemuf", "bclhemur", "bcxdyb", "bcxdyc", "bcxwjc", "bcintp", "bcextp", "topPt"};//58
  PrintDiffSyst("Luminosity (Run2)", "lumi_13TeV", outFile, nuisances, syst_array, chid);
  if(year==2016)
    PrintDiffSyst("Luminosity (2016)", "lumi_16", outFile, nuisances, syst_array, chid);
  if(year==2017){
    PrintDiffSyst("Luminosity (2017)", "lumi_17", outFile, nuisances, syst_array, chid);
    PrintDiffSyst("Luminosity (2017-18)", "lumi_17_18", outFile, nuisances, syst_array, chid);
  }
  if(year==2018){
    PrintDiffSyst("Luminosity (2018)", "lumi_18", outFile, nuisances, syst_array, chid);
    PrintDiffSyst("Luminosity (2017-18)", "lumi_17_18", outFile, nuisances, syst_array, chid);
  }
  if(year!=2018)
    PrintDiffSyst("Prefire", "prefire", outFile, nuisances, syst_array, chid);
  PrintDiffSyst("Pileup", "pileup", outFile, nuisances, syst_array, chid);
  PrintDiffSyst("Lepton", "eff", outFile, nuisances, syst_array, chid);
  PrintDiffSyst("Pileup jet identification", "pujetid", outFile, nuisances, syst_array, chid);
  PrintDiffSyst("JES:Absolute MPF Bias", "absmpfb", outFile, nuisances, syst_array, chid);
  PrintDiffSyst("JES:Absolute Scale", "absscl", outFile, nuisances, syst_array, chid);
  PrintDiffSyst("JES:Absolute Statistics", "absstat", outFile, nuisances, syst_array, chid);
  PrintDiffSyst("JES:Flavor QCD", "flavorqcd", outFile, nuisances, syst_array, chid);
  PrintDiffSyst("JES:Fragmentation", "frag", outFile, nuisances, syst_array, chid);
  PrintDiffSyst("JES:TimePtEta", "timepteta", outFile, nuisances, syst_array, chid);
  PrintDiffSyst("JES:Pileup Data/MC", "pudatamc", outFile, nuisances, syst_array, chid);
  PrintDiffSyst("JES:Pileup Pt bb", "puptbb", outFile, nuisances, syst_array, chid);
  PrintDiffSyst("JES:Pileup Pt EC1", "puptec1", outFile, nuisances, syst_array, chid);
  PrintDiffSyst("JES:Pileup Pt EC2", "puptec2", outFile, nuisances, syst_array, chid);
  PrintDiffSyst("JES:Pileup Pt HF", "pupthf", outFile, nuisances, syst_array, chid);
  PrintDiffSyst("JES:Pileup Pt ref", "puptref", outFile, nuisances, syst_array, chid);
  PrintDiffSyst("JES:Relative FSR", "relfsr", outFile, nuisances, syst_array, chid);
  PrintDiffSyst("JES:Relative Bal", "relbal", outFile, nuisances, syst_array, chid);
  PrintDiffSyst("JES:Relative Sample", "relsample", outFile, nuisances, syst_array, chid);
  PrintDiffSyst("JES:Relative JER EC1", "reljerec1", outFile, nuisances, syst_array, chid);
  PrintDiffSyst("JES:Relative JER EC2", "reljerec2", outFile, nuisances, syst_array, chid);
  PrintDiffSyst("JES:Relative Pt bb", "relptbb", outFile, nuisances, syst_array, chid);
  PrintDiffSyst("JES:Relative Pt EC1", "relptec1", outFile, nuisances, syst_array, chid);
  PrintDiffSyst("JES:Relative Pt EC2", "relptec2", outFile, nuisances, syst_array, chid);
  PrintDiffSyst("JES:Relative Pt HF", "relpthf", outFile, nuisances, syst_array, chid);
  PrintDiffSyst("JES:Relative Stat FSR", "relstatfsr", outFile, nuisances, syst_array, chid);
  PrintDiffSyst("JES:Relative Stat HF", "relstathf", outFile, nuisances, syst_array, chid);
  PrintDiffSyst("JES:Relative Stat EC", "relstatec", outFile, nuisances, syst_array, chid);
  PrintDiffSyst("JES:Single pion ECAL", "singpiecal", outFile, nuisances, syst_array, chid);
  PrintDiffSyst("JES:Single pion HCAL", "singpihcal", outFile, nuisances, syst_array, chid);
  PrintDiffSyst("JER", "JER", outFile, nuisances, syst_array, chid);
  PrintDiffSyst("$bc$ tagging stat.", "bcstat", outFile, nuisances, syst_array, chid);
  PrintDiffSyst("$bc$ tagging XS DY-b", "bcxdyb", outFile, nuisances, syst_array, chid);
  PrintDiffSyst("$bc$ tagging XS DY-c", "bcxdyc", outFile, nuisances, syst_array, chid);
  PrintDiffSyst("$bc$ tagging XS Wjet-c", "bcxwjc", outFile, nuisances, syst_array, chid);
  PrintDiffSyst("$bc$ tagging interpolation", "bcintp", outFile, nuisances, syst_array, chid);
  PrintDiffSyst("$bc$ tagging extrapolation", "bcextp", outFile, nuisances, syst_array, chid);
  PrintDiffSyst("Renomalization", "bclhemur", outFile, nuisances, syst_array, chid);
  PrintDiffSyst("Factorization", "bclhemuf", outFile, nuisances, syst_array, chid);
  PrintDiffSyst("PDF", "pdf", outFile, nuisances, syst_array, chid);
  PrintDiffSyst("ISR", "isr", outFile, nuisances, syst_array, chid);
  PrintDiffSyst("CP5", "CP5", outFile, nuisances, syst_array, chid);
  PrintDiffSyst("$h_{\\text{damp}}$", "hDamp", outFile, nuisances, syst_array, chid);
  PrintDiffSyst("top quark mass", "topMass", outFile, nuisances, syst_array, chid);
  PrintDiffSyst("top $p_T$ reweight", "topPt", outFile, nuisances, syst_array, chid);
  PrintDiffSyst("Normalization", "norm", outFile, nuisances, syst_array, chid);  
  outFile<<"\\hline "<<endl;  
  outFile<<"\\hline "<<endl;
  outFile<<"\\end{tabular}"<<endl;
  outFile<<"\\end{adjustbox}"<<endl;
  outFile<<"\\end{table}"<<endl;
  //outFile<<"\\end{landscape}"<<endl;
  outFile<<""<<endl;
  outFile<<""<<endl;
  outFile<<"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"<<endl;
  outFile<<"\\end{document}"<<endl;
  outFile.close();

  return true;
}

int PrintDiffSyst(string systfullname, string systnickname, ofstream& outFile, const char* nuisances[], map<string,map<int,float>> syst_array[], map<string,int> chid[])
{
  if(systnickname.find("norm")!=string::npos){

    float qcd_syst = syst_array[0]["norm_qcd_"][chid[0]["qcd"]] ;
    //cout << " qcd_syst : " << qcd_syst << endl;
    outFile << "& " << systfullname
	    << "& 6.1 " << "& 6.1 " << "& 6.1 " << "& 6.1 " << "& 6.1 " << "& 6.1 " << "& 6.1 " << "& 6.1 " << "& 6.1 " << "& 6.1 "
	    << "& 6.1 " << "& 6.1 " << "& 6.1 " << "& 6.1 " << "& 6.1 " << "& 6.1 " << "& 6.1 " << "& 6.1 " << "& 6.1 "
	    << "& 4.5 "<< "& 5.0 "<< "& 7.0 "<< "& 4.0 "<<"& "<<qcd_syst<<" \\\\"<<endl;
  }else{
    //map<int,float> qcd_syst_map = syst_array[0][systnickname] ;
    const int nM = 14;
    int mass[nM] = {40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 155, 160};
  
    float systs[24]; //14 charged higgs + 9 MC bkg + 1 QCD
    for(int im=0;im<nM;im++){
      string mName = "WH" + to_string(mass[im]) ;
      systs[im] = syst_array[im][systnickname][chid[im][mName]] ;
    }
    for(int ich=1;ich<int(chid[0].size());ich++){
      for(const auto ch : chid[0]){
	if(ch.second == ich)
	  systs[ich-1+nM] = syst_array[0][systnickname][ch.second] ;
      }
    }
    outFile << "& " << systfullname << fixed << setprecision(1) ;
    for(int isys=0;isys<24;isys++){
      if(systs[isys]>0.0)
	outFile << "& " << systs[isys] ;
      else
	outFile << "& - ";
    }
    outFile<<" \\\\"<<endl;
  }
  
  return true;
}

int GetYieldResult(string indir, int year, string ch, int mass, string ctag, map<string,pair<double,double>>& yield, map<string,int> chid)
{

  string infile="limit/TIFRAPAR-2023-01-15/"+indir+"/"+to_string(year)+"/Comb/"+ch+"/Cat1_Inc/Mass"+to_string(mass)+"/Shapes_hcs_13TeV_"+ch+"___ct_Exc"+ctag+"_mjj_"+ch+"_WH"+to_string(mass)+"_"+to_string(year)+".root";
  cout << "Infile : " << infile << endl;
  TFile *fin = TFile::Open(infile.c_str());
  for(const auto ch : chid){
    TH1F *h1 = (TH1F *)fin->Get(ch.first.c_str());
    double error;
    double integral = h1->IntegralAndError(1, h1->GetNbinsX(), error);
    yield[ch.first] = make_pair(integral,error);
    //cout << "Name : " << h1->GetName() << ", Integral : " << integral << " +/- " << error << endl;
  }
  fin->Close();
  delete fin;
  
  return true;
}

int ReadDataCard(string indir, int year, string ch, int mass, string ctag, const char* nuisances[], map<string,map<int,float>>& syst_array, map<string,int>& chid)
{
  string infile="limit/TIFRAPAR-2023-01-15/"+indir+"/"+to_string(year)+"/Comb/"+ch+"/Cat1_Inc/Mass"+to_string(mass)+"/datacard_hcs_13TeV_"+ch+"___ct_Exc"+ctag+"_mjj_"+ch+"_WH"+to_string(mass)+"_"+to_string(year)+".txt";
  
  ifstream fin(infile);
  string s;
  string systname, nui_prof, comment, comment1;
  float syst_p[11]; //1 signal + 9 mc bkgs + 1 qcd
  string syst_p_s[11]; //1 signal + 9 mc bkgs + 1 qcd
  vector<float> sb_syst_p;
  while(getline(fin,s)){
    //cout << " " << s << endl;
    if(s.find("process")!=string::npos and s.find("ttbar")!=string::npos){
      //cout << " " << s << endl;
      stringstream ssp;
      ssp << s << endl;
      ssp >> comment >> syst_p_s[0] >> syst_p_s[1] >> syst_p_s[2] >> syst_p_s[3] >> syst_p_s[4] >> syst_p_s[5] >> syst_p_s[6] >>
	syst_p_s[7] >> syst_p_s[8] >> syst_p_s[9] >> syst_p_s[10];
      //cout << "process " ;
      for(int iv=0;iv<11;iv++){
	//chname[iv] = syst_p_s[iv] ;
	//cout << " " << chname[iv] ;
	chid[syst_p_s[iv]] = iv ;
      }
      //cout << "\t" << endl;
    }
    for(int isys=0;isys<61;isys++){
      string systname = "CMS_" + string(nuisances[isys]);
      if(s.find(systname)!=string::npos){
	//cout << "F" << s << endl;
	stringstream ss;
	ss << s << endl;
	ss >> systname >> nui_prof >> syst_p_s[0] >> syst_p_s[1] >> syst_p_s[2] >> syst_p_s[3] >> syst_p_s[4] >> syst_p_s[5] >> syst_p_s[6] >>
	  syst_p_s[7] >> syst_p_s[8] >> syst_p_s[9] >> syst_p_s[10] >> comment >> comment1 ;
	map<int,float> ch_syst;
	//cout << "val " << string(nuisances[isys]) << " " << fixed << setprecision(1);
	for(int iv=0;iv<11;iv++){
	  if(syst_p_s[iv].find("-")==string::npos){
	    syst_p[iv] = stof(syst_p_s[iv]);
	    float syst_percent = (syst_p[iv]-1.000)*100.0;
	    //cout << " " << syst_percent;
	    ch_syst[iv] = syst_percent;
	  }else
	    ch_syst[iv] = -1.0;
	}
	//cout << "\t" << comment << endl;
	syst_array[string(nuisances[isys])] = ch_syst;
      }
    }
  }
  fin.close();
  cout<<"File " << infile << " closed" << endl;
  return true;
}
