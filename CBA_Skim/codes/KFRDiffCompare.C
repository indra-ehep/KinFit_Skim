/**********************************************************************
 Created on : 21/11/2025
 Purpose    : Compare the RDiff of jets before and after KF.
 Author     : Indranil Das, Research Associate, Imperial
 Email      : indranil.das@cern.ch | indra.ehep@gmail.com
**********************************************************************/

int KFRDiffCompare()
{
  void GetRDiffDist(const char* infile, TH1D*& hbjet, TH1D*& hljet);
  
  std::string basedir = "/Data/root_files/RDiffTest/root_files/without_RdiffCut/";
  std::string sname_ttbar = basedir + "TTbar_tree_base_1of1.root";
  std::string sname_hplus = basedir + "HplusM120_tree_base_1of1.root";
  std::string sname_data = basedir + "DataMu_tree_base_1of2.root";

  TH1D *hbjet_ttbar = new TH1D("hbjet_ttbar","#DeltaR distribution of b-jets",100,0,0.3);
  TH1D *hljet_ttbar = new TH1D("hljet_ttbar","#DeltaR distribution of light jets",100,0,0.3);
  TH1D *hbjet_hplus = new TH1D("hbjet_hplus","#DeltaR distribution of b-jets",100,0,0.3);
  TH1D *hljet_hplus = new TH1D("hljet_hplus","#DeltaR distribution of light jets",100,0,0.3);
  TH1D *hbjet_data = new TH1D("hbjet_data","#DeltaR distribution of b-jets",100,0,0.3);
  TH1D *hljet_data = new TH1D("hljet_data","#DeltaR distribution of light jets",100,0,0.3);

  GetRDiffDist(sname_ttbar.c_str(), hbjet_ttbar, hljet_ttbar);
  GetRDiffDist(sname_hplus.c_str(), hbjet_hplus, hljet_hplus);
  GetRDiffDist(sname_data.c_str(), hbjet_data, hljet_data);

  gStyle->SetOptStat(1111111);

  hbjet_ttbar->SetLineColor(kRed);
  hljet_ttbar->SetLineColor(kRed);
  hbjet_hplus->SetLineColor(kBlue);
  hljet_hplus->SetLineColor(kBlue);
  hbjet_data->SetLineColor(kBlack);
  hljet_data->SetLineColor(kBlack);
  
  hbjet_ttbar->SetLineWidth(4);
  hljet_ttbar->SetLineWidth(4);
  hbjet_hplus->SetLineWidth(4);
  hljet_hplus->SetLineWidth(4);
  hbjet_data->SetLineWidth(4);
  hljet_data->SetLineWidth(4);

  TCanvas *c1 = new TCanvas("c1","c1",900,900);
  c1->SetLogy();
  hbjet_ttbar->Draw();
  hbjet_hplus->Draw("sames");
  hbjet_data->Draw("sames");
  hbjet_ttbar->GetXaxis()->SetTitle("#DeltaR");
  hbjet_ttbar->GetYaxis()->SetTitle("normalized entries");
  
  TCanvas *c2 = new TCanvas("c2","c2",900,900);
  c2->SetLogy();
  hljet_ttbar->Draw();
  hljet_hplus->Draw("sames");
  hljet_data->Draw("sames");
  hljet_ttbar->GetXaxis()->SetTitle("#DeltaR");
  hljet_ttbar->GetYaxis()->SetTitle("normalized entries");
  
  return true;
}

void GetRDiffDist(const char* infile, TH1D*& hbjet, TH1D*& hljet)
{

  TFile *fin	= TFile::Open(infile);
  cout<<"filename : " << fin->GetName() << endl;
  TTree *tr	= (TTree*)fin->Get("Kinfit_Reco");

  Float_t	_Rdiffbjlep = 0 ;
  Float_t	_Rdiffbjhad = 0 ;
  Float_t	_Rdiffcjhad = 0 ;
  Float_t	_Rdiffsjhad = 0 ;

  tr->SetBranchAddress("Rdiffbjlep"	, &_Rdiffbjlep);
  tr->SetBranchAddress("Rdiffbjhad"	, &_Rdiffbjhad);
  tr->SetBranchAddress("Rdiffcjhad"	, &_Rdiffcjhad);
  tr->SetBranchAddress("Rdiffsjhad"	, &_Rdiffsjhad);
  
  
  cout << "Total Entries : " << tr->GetEntries() << endl;
  for (Long64_t ievent = 0 ; ievent < tr->GetEntries() ; ievent++ ) {    
  //for (Long64_t ievent = 0 ; ievent < 20000 ; ievent++ ) {    
    
    tr->GetEntry(ievent) ;

    hbjet->Fill(_Rdiffbjlep);
    hbjet->Fill(_Rdiffbjhad);
    hljet->Fill(_Rdiffcjhad);
    hljet->Fill(_Rdiffsjhad);
    
  }//event loop

  hbjet->Scale(1/hbjet->Integral());
  hljet->Scale(1/hljet->Integral());
  
  fin->Close();
  delete fin;

}
