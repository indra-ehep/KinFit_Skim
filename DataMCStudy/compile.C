{
  gSystem->Load("libweight.so");
  
  TString path_lnx3 = "/work/CMS-Software/Source/cs8_amd64_gcc10/external/py3-correctionlib/2.1.0-bc1f1a24613552be911056d8eb959866/lib/python3.9/site-packages/correctionlib";
  TString path_ui = "/cvmfs/cms.cern.ch/slc7_amd64_gcc10/external/py3-correctionlib/2.1.0-bc1f1a24613552be911056d8eb959866/lib/python3.9/site-packages/correctionlib";
  
  TString hostname = gSystem->HostName();
  
  // if(hostname.BeginsWith("Indra-Rjn"))
  //    basePath = "/Data/CMS-Analysis/NanoAOD-Analysis/Git_KinFit_Skim/KinFit_Skim/DataMCStudy";
  //  else if(hostname.BeginsWith("lxplus"))
  //    basePath = "/afs/cern.ch/user/i/idas/CMS-Analysis/NanoAOD-Analysis/DataMCStudy";
  //  else if(hostname.BeginsWith("ui"))
  //    basePath = "/tmp/idas/DataMCStudy";
  //  else if(hostname.BeginsWith("localhost") or hostname.BeginsWith("lnx3"))
  //    basePath = "/home/idas/CMS-Analysis/NanoAOD-Analysis/DataMCStudy";
  //  Printf("Base Path is : %s",basePath.Data());
  
  TString corrlib_path = "";
  if(hostname.BeginsWith("Indra-Rjn"))
    corrlib_path = "";
  else if(hostname.BeginsWith("lxplus"))
    corrlib_path = "";
  else if(hostname.BeginsWith("ui"))
    corrlib_path = path_ui;
  else if(hostname.BeginsWith("localhost") or hostname.BeginsWith("lnx3"))
    corrlib_path = path_lnx3;

  Printf("Corrlib Path is : %s",corrlib_path.Data());
   
  TString inc_lnx3 = corrlib_path + "/include" ;
  TString lib_lnx3 = corrlib_path + "/lib/libcorrectionlib.so";
  
  gSystem->AddIncludePath(Form("-I%s",inc_lnx3.Data()));
  gSystem->Load(Form("%s",lib_lnx3.Data()));

  gROOT->ProcessLine(".L SkimAna.C++");
  
}
