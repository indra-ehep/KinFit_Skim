{
  gSystem->Load("libweight.so");

  TString corrlib_path = "/work/CMS-Software/Source/cs8_amd64_gcc10/external/py3-correctionlib/2.1.0-bc1f1a24613552be911056d8eb959866/lib/python3.9/site-packages/correctionlib";
  TString inc_lnx3 = corrlib_path + "/include" ;
  TString lib_lnx3 = corrlib_path + "/lib/libcorrectionlib.so";
  
  gSystem->AddIncludePath(Form("-I%s",inc_lnx3.Data()));
  gSystem->Load(Form("%s",lib_lnx3.Data()));

  gROOT->ProcessLine(".L SkimAna.C++");
  
}
