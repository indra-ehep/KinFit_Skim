/**********************************************************************
 Created on : 18/12/2021
 Purpose    : Create the joblist of JDL files
              Save the output of file_stat_check.py in processlist.txt and then run

              grep "Root >" processlist.txt | cut -d ' ' -f 4 | cut -d '|' -f 1  > missing.txt
              
              Then run the code below.
 Author     : Indranil Das, Visiting Fellow
 Email      : indranil.das@cern.ch | indra.ehep@gmail.com
**********************************************************************/
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int CreateJDLjoblist()
{
  const char *infile = "/home/indra/temp/missing.txt";
  int year = 2016;
  fstream fin;
  fin.open(infile,ios::in);
  string s;
  string search_str1 = "_Skim_NanoAOD";
  string search_str2 = "of";
  if (fin.is_open()){
    while(getline(fin,s)){
      //cout << "Filename : " << s << endl;
      if(s.find("of")!=string::npos){
	string sample = s.substr(0,s.find(search_str1));
	string aofb = s.substr(s.find(search_str1)+search_str1.size()+1, s.find("."));
	aofb = aofb.substr(0,aofb.find("."));
	string index = aofb.substr(0,aofb.find(search_str2));
	string njob = aofb.substr(aofb.find(search_str2)+search_str2.size(),aofb.size());
	//cout << "sample : " << sample << " " << aofb << ", index " << index << ", njobs : " << njob << endl;
	printf("Arguments = %d %s %s %s \nQueue 1\n\n",year,sample.data(),index.data(),njob.data());
      }else{
	//cout << "Filename2 : " << s << endl;
	string sample = s.substr(0,s.find(search_str1));
	printf("Arguments = %d %s\nQueue 1\n\n",year,sample.data());
      }
    }
  }else{
    cerr << "File " << infile << ", is not open" << endl;
  }
  fin.close();
  return true;
}

