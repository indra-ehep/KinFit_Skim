/**********************************************************************
 Created on : 08/05/2023
 Purpose    : Compare the top-pt SF 0.09494 − 0.00084
 Author     : Indranil Das, Visiting Fellow
 Email      : indranil.das@cern.ch | indra.ehep@gmail.com
**********************************************************************/

int topptsf()
{
  
  TF1 *fn1 = new TF1("fn16","exp(0.09494 - 0.00084*x)",0.0,4000.0);
  TF1 *fn2 = new TF1("fn23","exp(0.0615 - 0.0005*x)",0.0,4000.0);

  fn1->SetLineWidth(2);
  fn2->SetLineWidth(2);

  fn1->SetNpx(1000);
  fn2->SetNpx(1000);
  
  fn1->SetLineColor(kRed);
  fn2->SetLineColor(kBlue);

  TLegend *leg = new TLegend(0.55,0.65,0.85,0.85);
  leg->SetFillColor(10);
  leg->AddEntry(fn1, Form("HIG-18-021 : exp(0.09494 - 0.00084*p_{T})") ,"lfp");
  leg->AddEntry(fn2, Form("TOP-23-001 : exp(0.0615 - 0.0005*p_{T})") ,"lfp");

  TCanvas *c1 = new TCanvas("c1","c1");
  c1->SetTickx();
  c1->SetTicky();
  fn1->Draw();
  fn2->Draw("sames");
  leg->Draw();
  fn1->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  fn1->GetYaxis()->SetTitle("SF");

  fn1->SetTitle("");
  
  return true;
}
