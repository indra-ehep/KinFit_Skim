int run(const char* opt = "ptmin=30.0|ptmax=10000.0|chi2cut=20.0|mtop=172.6|sample=TTbarPowheg|year=2016") // sample = data, bkg, signal
{ 
  
  TString options(opt);
  TChain *chain = new TChain("RecoNtuple_Skim");
  ifstream fin("files.txt");
  string s;
  while(getline(fin,s)){
    //cout << s << endl;
    // The following skips all lines of input file that starts with a '#'
    if (s.rfind("#", 0) == 0) continue;

    chain->Add(s.c_str());
  }
  
  chain->Process("PerformKinFit.C++", options.Data(), 10000);    
  
  return true;
}

