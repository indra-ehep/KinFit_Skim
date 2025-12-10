#include <iostream>
#include <iomanip>
#include <cstdint>
#include <cstring>
#include <cassert>
#include <map>
#include "TMath.h"

#include <yaml-cpp/yaml.h>

int main(int argc, char **argv)
{
  if(argc < 2){
    std::cerr << argv[0] << ": no input file has been specified specified" << std::endl;
    return false;
  }
  std::string inputpath;
  std::istringstream issInpath(argv[1]);
  issInpath >> inputpath;
  std::string fname = inputpath;
  std::cerr << "fname : " << fname << std::endl;

  uint32_t firstNNui = 10;

  YAML::Node node(YAML::LoadFile(fname));
  std::cout << "node size  : " << node.size() << std::endl;
  for (YAML::const_iterator it = node.begin(); it != node.end(); ++it) {
    std::string key1 = it->first.as<std::string>();
    YAML::Node value1 = it->second;
    std::cout << "Key1 : " << key1 << std::endl;
    if(key1.find("params")!=std::string::npos){
      std::cout << "value1-inside.size() : " << value1.size() << std::endl;
      std::map<double,std::string> impactlist;
      std::map<std::string,double> nuipobypre;
      std::map<double,std::string> reducedlist;
      for(int i=0;i<value1.size();i++){
	std::string nuiname = value1[i]["name"].as<std::string>();
	impactlist[value1[i]["impact_BR"].as<double>()] = value1[i]["name"].as<std::string>() ;
	double postfitmin = value1[i]["fit"][0].as<double>();
	double postfitmax = value1[i]["fit"][2].as<double>();
	double postfitval = value1[i]["fit"][1].as<double>();
	double prefitmin = value1[i]["prefit"][0].as<double>();
	double prefitmax = value1[i]["prefit"][2].as<double>();
	double prefitval = value1[i]["prefit"][1].as<double>();
	
	double postfitbyprefit = fabs(postfitmax - postfitmin)/fabs(prefitmax - prefitmin) ;
	// if(nuiname.find("prop_binch17_bin5") != std::string::npos){
	//   std::cout << "Nuisance: " << nuiname << ", prefit-value : " <<  prefitval << " +/- (" << prefitmin << ", " << prefitmax << ") " << std::endl;
	//   std::cout << "Nuisance: " << nuiname << ", postfit-value : " <<  postfitval << " +/- (" << postfitmin << ", " << postfitmax << ") " << std::endl;
	// }
	if(TMath::AreEqualAbs(abs(postfitmin-postfitval),0,1e-5) or TMath::AreEqualAbs(abs(postfitmax-postfitval),0,1e-5))
	  std::cout << "Nuisance: " << nuiname << ", value : " <<  postfitval << " +/- (" << postfitmin << ", " << postfitmax << ") " << std::endl;
	
	nuipobypre[value1[i]["name"].as<std::string>()] = postfitbyprefit;
	reducedlist[postfitbyprefit] = value1[i]["name"].as<std::string>() ;
	
	// if(nuiname.find("fsr",0,nuiname.size())!=std::string::npos){
	//   std::cout << "value1-inside.name : " << value1[i]["name"] << std::endl;
	//   std::cout << "value1-inside.impact_BR : " << value1[i]["impact_BR"] << std::endl;
	//   std::cout << "value1-inside.fit : " << value1[i]["fit"] << std::endl;
	//   std::cout << "value1-inside.fit.width : " << (postfitmax - postfitmin) << std::endl;
	//   std::cout << "value1-inside.prefit.width : " << (prefitmax - prefitmin) << std::endl;
	//   std::cout << value1[i] << std::endl;
	// }
	// if(nuiname.find("prop_binch3_ch3_bin4",0,nuiname.size())!=std::string::npos){
	//   std::cout << "value1-inside.name : " << value1[i]["name"] << std::endl;
	//   std::cout << "value1-inside.impact_BR : " << value1[i]["impact_BR"] << std::endl;
	//   std::cout << "value1-inside.fit.width : " << (postfitmax - postfitmin) << std::endl;
	//   std::cout << "value1-inside.prefit.width : " << (prefitmax - prefitmin) << std::endl;
	//   std::cout << value1[i] << std::endl;
	// }
      }//loop over parameters
      std::map<double,std::string>::reverse_iterator itim;
      int iloop = 0;
      //for(itim=impactlist.rbegin();itim!=impactlist.rend() and iloop<firstNNui ;itim++){
      for(const auto& itim : reducedlist){
      //for(const auto& itim : impactlist){
	//iloop++;
	//std::string nuiname = itim->second;
	std::string nuiname = itim.second;
	//if(nuiname.find("qcddd")!=std::string::npos or nuiname.find("qcdrate")!=std::string::npos or nuipobypre[nuiname]>0.5) continue;
	if(nuipobypre[nuiname]>0.5 or iloop>=firstNNui) continue;
	//std::cout<<"parameter : " << itim.second << ", post/pre: " << nuipobypre[nuiname] << std::endl;
	std::cout<< nuiname << std::endl;
	iloop++;
      }
    }//params 
  }//node iterator
  // std::string name = node["POIs"]["name"].as<std::string>();
  // std::cout << "Name : " << name << std::endl;
  return true;
}
