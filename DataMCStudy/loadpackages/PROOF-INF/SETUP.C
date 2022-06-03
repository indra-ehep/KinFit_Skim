Int_t SETUP()
{
   if (gSystem->Getenv("ROOTPROOFLITE")) {
      Printf("event-SETUP: PROOF-Lite node (session has %s workers)",
                                   gSystem->Getenv("ROOTPROOFLITE"));
   } else if (gSystem->Getenv("ROOTPROOFCLIENT")) {
      Printf("event-SETUP: PROOF client");
   } else {
      Printf("event-SETUP: standard PROOF node");
   }
   //if (gSystem->Load("libEvent") == -1)
   
   TString hostname = gSystem->HostName();
   TString basePath = "";

   if(hostname.BeginsWith("Indra-Rjn"))
     basePath = "/Data/CMS-Analysis/NanoAOD-Analysis/Git_KinFit_Skim/KinFit_Skim/CBA_Skim";
   // else if(hostname.BeginsWith("lxplus"))
   //   basePath = "/tmp/idas/CBA_Skim";
   else if(hostname.BeginsWith("lxplus"))
     basePath = "/afs/cern.ch/user/i/idas/CMS-Analysis/NanoAOD-Analysis/DataMCStudy";
   else if(hostname.BeginsWith("lnx3"))
     basePath = "/home/indra/CMS-Analysis/NanoAOD-Analysis/KinFit_Skim/CBA_Skim";
   else if(hostname.BeginsWith("ui"))
     basePath = "/tmp/idas/CBA_Skim";
   else if(hostname.BeginsWith("localhost") or hostname.BeginsWith("lnx3"))
     basePath = "/home/idas/CMS-Analysis/NanoAOD-Analysis/DataMCStudy";
   Printf("Base Path is : %s",basePath.Data());

   if (gSystem->Load(Form("%s/libweight.so",basePath.Data())) == -1)
     return -1;
   else
     Printf("Loaded libweight.so");

   TString corrlibIncPath = "/cvmfs/cms.cern.ch/slc7_amd64_gcc900/external/py3-correctionlib/2.0.0-0c4f44c8dd5561d8c0660135feeb81f4/lib/python3.9/site-packages/correctionlib/include" ;

   gSystem->SetIncludePath(Form("-I%s",basePath.Data())) ;
   gSystem->SetIncludePath(Form("-I%s",corrlibIncPath.Data())) ;


   return 0;
}
