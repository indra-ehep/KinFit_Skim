int run(const char* opt = "sample=ST_t_channel|year=2016") // sample = data, bkg, signal
{
  
  bool isproof  = 0 ;
  
  TString options(opt);
  TChain *chain = new TChain("Events");
  //TChain *chain = new TChain("Kinfit_Reco");
  ifstream fin("input/files.txt");
  
  string s;
  while(getline(fin,s)){
    //cout << s << endl;
    chain->Add(s.c_str());
  }
  
  if(isproof){
    //TProof *p = TProof::Open("workers=10");
    TProof *p = TProof::Open("workers=3");
    // p->ClearPackages();
    // p->UploadPackage("loadpackages.par");
    // p->EnablePackage("loadpackages");
    chain->SetProof();
    //sprintf(mode,"proof|%s",mode);
    options += "|mode=proof";
  }
  
  chain->Process("ProcessSkim.C++", options.Data() );    
  //chain->Process("ProcessSkim.C++", options.Data(), 1000 );    
  
  return true;
}

