int QCDScale()
{
  TString dirpath = "Imperial-PA-2024-10-08/50_unblinded_MVA_lnNfixed_qcdrange0to50_qcddd6_bc3_uncorr_symm_10GeV/";
  //TString dirpath = "Imperial-PA-2024-10-08/56_UMl_qcdrange0to50_qcddd6_bc3_uncorr_symm_nzlbin_10GeV/";
  //TString dirpath = "local/";
  TString dirpath1 = dirpath;//"Imperial-PA-2024-10-08/50_unblinded_MVA_lnNfixed_qcdrange0to50_qcddd6_bc3_uncorr_symm_10GeV/";
  TString fname = dirpath + "2016/ExcL/ele/Cat1_Inc/Mass80/fitDiagnosticsTest.root" ;
  TString outdir;
  for(int year=2016;year<=2016;year++){
    for(int ch=1;ch<=1;ch++){
      TString channel = (ch==1) ? "ele" : "mu" ;
      for(int cat=1;cat<=1;cat++){
	TString cattype = "";
	if(cat==1) cattype = "ExcL";
	else if(cat==2) cattype = "ExcM";
	else cattype = "ExcT";
	if(year==2017 and ch==1 and cat==3)
	  outdir = dirpath1 + Form("%d/%s/%s/Cat1_Inc/Mass80/",year,cattype.Data(),channel.Data());
	else
	  outdir = dirpath + Form("%d/%s/%s/Cat1_Inc/Mass80/",year,cattype.Data(),channel.Data());
	fname = outdir + "fitDiagnosticsTest.root";
	TFile *fitDiagOut = TFile::Open(fname);
	//example_stack(fitDiagOut, outdir, year, cattype, channel, "ch1", ((ch==1)?"#it{e} + jets":"#mu + jets"), Form("%d %s",year,cattype.Data()));
	TH1F *qcd_prefit = (TH1F *) fitDiagOut->Get("shapes_prefit/ch1/qcd");
	TH1F *qcd_bkg = (TH1F *) fitDiagOut->Get("shapes_fit_b/ch1/qcd");
	TH1F *qcdratio = (TH1F *)qcd_bkg->Clone("qcdratio");
	qcdratio->Divide(qcd_prefit);
	TCanvas *c1 = new TCanvas("c1","c1");
	qcdratio->Draw();
	double scale = qcd_bkg->Integral()/qcd_prefit->Integral();
	cout << year << " " << cattype << " " << channel << " " << scale << endl;
	//fitDiagOut->Close();
	//delete fitDiagOut;
      }
    }
  }

  return true;
}
