/**********************************************************************
 Created on : 06/03/2024
 Purpose    : Read the systematics from datacard
 Author     : Indranil Das, Visiting Fellow
 Email      : indranil.das@cern.ch | indra.ehep@gmail.com
**********************************************************************/
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <map>

using namespace std;

int ReadDataCard()
{
  string infile="limit/TIFRAPAR-2023-01-15/91_no-dijet-edge-effect_bld/2016/Comb/mu/Cat1_Inc/Mass40/datacard_hcs_13TeV_mu___ct_ExcL_mjj_mu_WH40_2016.txt";
  const char* nuisance[] = {"lumi_13TeV", "lumi_16", "eff", "prefire", "pujetid", "pileup", "absmpfb", "absscl", "absstat", "flavorqcd",
			"frag", "timepteta", "pudatamc", "puptbb", "puptec1", "puptec2", "pupthf", "puptref", "relfsr", "relbal",
			"relsample", "reljerec1", "reljerec2", "relptbb", "relptec1", "relptec2", "relpthf", "relstatfsr", "relstathf", "relstatec",
			"singpiecal", "singpihcal", "JER", "norm_sig", "norm_tt ", "norm_ttg", "norm_tth", "norm_ttz", "norm_ttw", "norm_stop",
			"norm_wjet", "norm_zjet", "norm_qcd_", "norm_vv",  "CP5", "hDamp", "topMass", "pdf", "isr", "bcstat",
			"bclhemuf", "bclhemur", "bcxdyb", "bcxdyc", "bcxwjc", "bcintp", "bcextp", "topPt"};//58
  
  ifstream fin(infile);
  string s;
  string systname, nui_prof, comment, comment1;
  float syst_p[11]; //1 signal + 9 mc bkgs + 1 qcd
  string syst_p_s[11]; //1 signal + 9 mc bkgs + 1 qcd
  vector<float> sb_syst_p;
  map<string,map<int,float>> syst_array;
  map<int,string> chname;
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
	chname[iv] = syst_p_s[iv] ;
	//cout << " " << chname[iv] ;
      }
      //cout << "\t" << endl;
    }
    for(int isys=0;isys<58;isys++){
      string systname = "CMS_" + string(nuisance[isys]);
      if(s.find(systname)!=string::npos){
	//cout << "F" << s << endl;
	stringstream ss;
	ss << s << endl;
	ss >> systname >> nui_prof >> syst_p_s[0] >> syst_p_s[1] >> syst_p_s[2] >> syst_p_s[3] >> syst_p_s[4] >> syst_p_s[5] >> syst_p_s[6] >>
	  syst_p_s[7] >> syst_p_s[8] >> syst_p_s[9] >> syst_p_s[10] >> comment >> comment1 ;
	map<int,float> ch_syst;
	//cout << "val " << string(nuisance[isys]) << " " << fixed << setprecision(1);
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
	syst_array[string(nuisance[isys])] = ch_syst;
      }
    }
  }
  fin.close();
  cout<<"File " << infile << " closed" << endl;
  return true;
}
