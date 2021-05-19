int runProof(const char* opt = "ptmin=30.0|ptmax=50.0|chi2cut=20.0|mtop=172.6|sample=TTbarPowheg|year=2016") // sample = data, bkg, signal
{
  
  bool isproof  = 0 ;
  
  TString options(opt);
  TChain *chain = new TChain("RecoNtuple_Skim");
  ifstream fin("files.txt");
  string s;
  while(getline(fin,s)){
    //cout << s << endl;
    chain->Add(s.c_str());
  }
  
  if(isproof){
    TProof *p = TProof::Open("workers=3");
    chain->SetProof();
    //sprintf(mode,"proof|%s",mode);
    options += "|mode=proof";
  }
  
  chain->Process("PerformKinFit.C++", options.Data(), 10000);    
  
  return true;
}

