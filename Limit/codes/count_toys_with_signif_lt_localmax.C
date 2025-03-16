void count_toys_with_signif_lt_localmax(const char* year, int mass, const char* bkgfile, const char* datafile){
  // std::string bfitfname = "higgsCombine_bfit_data_1.MultiDimFit.mH80.root";
  // std::string datafname = "higgsCombine_data_1.MultiDimFit.mH80.root";
  std::string bfitfname(bkgfile);
  std::string datafname(datafile);
  
  TFile *fbfit = TFile::Open(bfitfname.c_str());
  TFile *fdata = TFile::Open(datafname.c_str());
  
  Float_t BR, deltaNLL, r;
  Double_t nll, nll0;
  //   TFile fbfit("higgsCombine_bfit_"+stoy+".MultiDimFit.mH120.root");
  //   TFile fscan("higgsCombine_"+stoy+".MultiDimFit.mH120.root");
  TTree *t=(TTree*)fbfit->Get("limit");
  t->SetBranchAddress("BR",&BR);
  t->SetBranchAddress("deltaNLL",&deltaNLL);
  t->SetBranchAddress("nll",&nll);
  t->SetBranchAddress("nll0",&nll0);

  //std::cout << "Nofbkg : " << t->GetEntries() << std::endl;
  
  double nll_bfit = 0;
  Long_t nentries = t->GetEntries();
  for (Int_t i = 0; i<1; i++) {
    t->GetEntry(i);
    nll_bfit = nll+nll0;
  }
  //cout<<"nll_bfit="<<nll_bfit<<endl;

  t=(TTree*)fdata->Get("limit");
  t->SetBranchAddress("BR",&BR);
  t->SetBranchAddress("deltaNLL",&deltaNLL);
  t->SetBranchAddress("nll",&nll);
  t->SetBranchAddress("nll0",&nll0);

  //hsignif.GetXaxis()->SetRangeUser(8,40);
  nentries = t->GetEntries();
  TGraph hsignif(nentries);
  int ivalid = 0;
  double sig_max = -1, BR_max;
  for (Int_t i = 0; i<nentries; i++) {
    t->GetEntry(i);
    double rel_nll = nll+nll0+deltaNLL - nll_bfit;
    if(rel_nll>0) rel_nll=0;
    //double sig = sqrt(2*fabs(nll+nll0+deltaNLL));
    double sig = sqrt(2*fabs(deltaNLL));
    //if(sig>5) continue;
    hsignif.Set(i+1);
    hsignif.SetPoint(i, BR, sig);
    std::cout << "i : " << i << ", (nll+nll0+deltaNLL): " << (nll+nll0+deltaNLL) << ", nll_bfit: " << nll_bfit << ", rel_nll: " << rel_nll << ", BR : " << BR << ",  sig: " << sig << std::endl;
    ivalid++;
  }
  hsignif.Set(ivalid);
  //std::cout << "Done 2" << std::endl;
  hsignif.Sort();
  //spikeKiller1D(&hsignif);
  for(int i=1; i< hsignif.GetN(); i++){
    double x, y; hsignif.GetPoint(i, x, y);
    if(y>=sig_max){ sig_max=y; BR_max=x;
    }
  }
  //std::cout << "BR_max: " << BR_max << ", sig_max: " << sig_max << ", local p-value: " << ROOT::Math::normal_cdf_c(sig_max) << std::endl;
  //std::cout << "year: " << year << ", mass " << mass << ", BR_max: " << BR_max << ", sig_max: " << sig_max << ", local p-value: " << ROOT::Math::normal_cdf_c(sig_max) << std::endl;
  //std::cout << year << "\t" << mass << "\t" << BR_max << "\t" << sig_max << "\t" << ROOT::Math::normal_cdf_c(sig_max) << std::endl;
  printf("%s\t%03d\t%5.4f\t%5.4f\t%5.4f\n",year,mass,BR_max,sig_max,ROOT::Math::normal_cdf_c(sig_max));
  //std::cout << year << "\t" << mass << "\t" << BR_max << "\t" << sig_max << "\t" << ROOT::Math::normal_cdf_c(sig_max) << std::endl;
  
  // TCanvas c("c","c",1000,500); 
  // c.cd();
  // // TH1F htmp("htmp","htmp",100,8,40);
  // // htmp.SetMaximum(5);
  // // htmp.SetMinimum(0);
  // // htmp.SetTitle("; m_{X} (GeV); Q = #sqrt{-2#Delta ln L}");
  // // htmp.SetStats(0);
  // // htmp.Draw();
  // hsignif.Draw("ALP");
  // c.SaveAs("result.png");
  
  //   TString ssig = TString::Format("Q_{max} = %.2f",sig_max);
  //   TLatex tsig;
  //   tsig.SetNDC();
  //   tsig.SetTextSize(0.06);
  //   if(sig_max>=max_significance_in_data) tsig.SetTextColor(kRed);
  //   tsig.DrawLatex(0.17,0.85, ssig.Data());

  //   TLine *lh = new TLine(10,max_significance_in_data, 35, max_significance_in_data);
  //   lh->SetLineStyle(kDashed);
  //   lh->Draw();

  //   c.SaveAs("scan_signif_"+stoy+(sig_max<max_significance_in_data?".png":"_red.png"));
  
  fbfit->Close();
  fdata->Close();

  delete fbfit;
  delete fdata;
  


  //   if(hello<=0)break;

}

