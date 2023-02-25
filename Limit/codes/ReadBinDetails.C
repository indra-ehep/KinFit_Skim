/**********************************************************************
 Created on : 13/02/2023
 Purpose    : Read the bin statistics
 Author     : Indranil Das, Visiting Fellow
 Email      : indranil.das@cern.ch | indra.ehep@gmail.com
**********************************************************************/
int ReadBinDetails(int cat=1, int ihist = 1)
{
  
  string bdtCat, cbaCat;
  if(cat==1){
    bdtCat = "Loose";
    cbaCat = "L";
  }else if(cat==2){
    bdtCat = "Medium";
    cbaCat = "M";
  }else if(cat==3){
    bdtCat = "Tight";
    cbaCat = "T";
  }
  
  string histname = "ttbar";
  string histname1 = "ttbar";
  if(ihist==1){
    histname = "ttbar";
    //histname = "ttbar_JESUp";
    // histname = "ttbar_bc_statUp";
    // histname1 = "ttbar_bcstatUp";
    histname1 = histname;
  }else if(ihist==2){
    histname = "WH80";
    histname1 = histname;
  }else if(ihist==3){
    histname = "stop";
    histname1 = histname;
  }else if(ihist==4){
    histname = "wjet";
    histname1 = histname;
  }else if(ihist==5){
    histname = "zjet";
    histname1 = histname;
  }else if(ihist==6){
    histname = "vv";
    histname1 = histname;
  }else if(ihist==7){
    histname = "qcd";
    histname1 = histname;
  }else if(ihist==8){
    histname = "data_obs";
    histname1 = histname;
  }
  
  TFile *fin = TFile::Open(Form("savarghe/HplusDatacards/muon2016/mass80/Shapes_hcs_13TeV_mu_KinFit_Exc%sbdt_WH80.root",bdtCat.c_str()));
  TH1F *h1sv = (TH1F *)fin->Get(histname.c_str());
  TFile *fin1 = TFile::Open(Form("TIFRAPAR-2023-01-15/21_elereliso_unbld_unNorm_cmdMiniAOD_7Shapes_RD/2016/Comb/mu/Cat1_Inc/Mass80/Shapes_hcs_13TeV_mu___ct_Exc%s_mjj_mu_WH80_2016.root",cbaCat.c_str()));
  TH1F *h1id = (TH1F *)fin1->Get(histname1.c_str());
  for(int ibin=1;ibin<h1sv->GetNbinsX();ibin++){
    cout << "ibin : " << ibin <<", center : " << h1sv->GetBinCenter(ibin) 
	 << ", content : " << h1sv->GetBinContent(ibin) << ", Error : " << h1sv->GetBinError(ibin) <<" (" << 100.*h1sv->GetBinError(ibin)/h1sv->GetBinContent(ibin) <<"\%) "
	 <<", center1 : " << h1id->GetBinCenter(ibin) 
	 << ", content1 : " << h1id->GetBinContent(ibin) << ", Error1 : " << h1id->GetBinError(ibin) <<" (" << 100.*h1id->GetBinError(ibin)/h1id->GetBinContent(ibin) <<"\%) "
	 << endl;
  }
  cout <<histname<<":: Integral(MVA) : " << h1sv->Integral(20.,170.) << ", Integral(CBA) : " << h1id->Integral(20.,170.) 
       << ", Diff in percent : "<< 100.0*fabs(h1id->Integral(20.,170.)-h1sv->Integral(20.,170.))/h1id->Integral(20.,170.) << endl;
  
  h1sv->SetLineColor(kRed);
  h1id->SetLineColor(kBlue);
  h1sv->SetLineWidth(2.0);
  h1id->SetLineWidth(2.0);
  h1id->SetMaximum(1.6*h1id->GetBinContent(h1id->GetXaxis()->FindBin(81.)));
  TLegend *leg = new TLegend(0.39162,0.6771911,0.642121,0.8745237);
  leg->AddEntry(h1sv, "MVA" ,"lfp");
  leg->AddEntry(h1id, "CBA" ,"lfp");
  TF1 *gaus = new TF1("fn","gaus",60.,95.);
  TF1 *gaus1 = new TF1("fn1","gaus",60.,95.);
  TCanvas *c1 = new TCanvas("c1","c1");
  h1id->Draw("sames hist");
  h1id->Fit("fn1","LR");
  h1sv->Draw("sames hist");
  h1sv->Fit("fn","LR");
  leg->Draw();

  return true;
}
