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
     basePath = "/Data/CMS-Analysis/NanoAOD-Analysis/Git_KinFit_Skim/KinFit_Skim/Legacy_ReReco_CBA";
   else if(hostname.BeginsWith("lxplus"))
     basePath = "/afs/cern.ch/user/i/idas/CMS-Analysis/NanoAOD-Analysis/Legacy_ReReco_CBA";
   else if(hostname.BeginsWith("lnx3"))
     basePath = "/home/indra/CMS-Analysis/NanoAOD-Analysis/KinFit_Skim/Legacy_ReReco_CBA";
   Printf("Base Path is : %s",basePath.Data());

   if (gSystem->Load(Form("%s/libweight.so",basePath.Data())) == -1)
     return -1;
   else
     Printf("Loaded libweight.so");
   
   gSystem->SetIncludePath(Form("-I%s",basePath.Data())) ;


   return 0;
}
