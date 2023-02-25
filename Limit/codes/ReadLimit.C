/**********************************************************************
 Created on : 15/02/2023
 Purpose    : Read the limit results
 Author     : Indranil Das, Visiting Fellow
 Email      : indranil.das@cern.ch | indra.ehep@gmail.com
**********************************************************************/
int ReadLimit(int mass = 80)
{
  Double_t r;
  float obsY;
  float expY;
		      
  // float expX1sL;
  // float expX1sH;
  float expY1sL;
  float expY1sH;
		      
  // float expX2sL;
  // float expX2sH;
  float expY2sL;
  float expY2sH;

  TFile *fin = TFile::Open(Form("higgsCombineTest.AsymptoticLimits.mH%d.root",mass));
  //TFile *fin = TFile::Open(Form("higgsCombine_hcs_13TeV_mu_Cat1_Inc.AsymptoticLimits.mH%d.root",mass));
  TTree* limit = (TTree*)fin->Get("limit");
  limit->SetBranchAddress("limit",&r);
  for(int k = 0 ; k< limit->GetEntries() ; k++){
    limit->GetEntry(k);
    if(k==0) expY2sL = 100.*r;
    if(k==1) expY1sL = 100.*r;
    if(k==2) expY    = 100.*r;
    if(k==3) expY1sH = 100.*r;
    if(k==4) expY2sH = 100.*r;
    if(k==5) obsY    = 100.*r;
  }
  float Diff1sL = TMath::Abs(expY1sL-expY);
  float Diff1sH = TMath::Abs(expY1sH-expY);
  printf("& $%3.2f^{+%3.2f}_{-%3.2f}$ \n",expY,Diff1sH,Diff1sL);
  return true;
}
