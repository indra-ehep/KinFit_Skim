# root -l -b $1 << EOF
# RooWorkspace *w = (RooWorkspace *)_file0->Get("w");
# w->Print();
# .q
# EOF

# root -l -b $1 << EOF
# RooDataSet *dat = (RooDataSet *)_file0->Get("toys/toy_1");
# RooArgSet *as = (RooArgSet *)_file0->Get("toys/toy_1_snapshot");
# dat->Print("all");
# as->Print();
# .q
# EOF

# root -l -b $1 << EOF
# TCanvas *c1 = new TCanvas("c1","c1")
# TTree *tr = (TTree *)_file0->Get("tree_fit_sb")
# tr->Draw("(r-1)/(0.5*(rHiErr+rLoErr))>>h(200,-5,5)")
# c1->SaveAs("c1.pdf");
# .q
# EOF
# atril c1.pdf &

root -l -b $1 << EOF
TCanvas *c1 = new TCanvas("c1","c1")
TTree *tr = (TTree *)_file0->Get("tree_fit_sb")
tr->Scan("fit_status")
.q
EOF
#tr->Draw("(BR-0.0308)/(0.5*(BRHiErr+BRLoErr))>>h(200,-5,5)")
#c1->SaveAs("c1.pdf");
#atril c1.pdf &
