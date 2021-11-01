Pre-Exec:
================
Download and compile

 git clone https://github.com/cms-analysis/HiggsAnalysis-CombinedLimit.git HiggsAnalysis/CombinedLimit
 
 git clone https://github.com/cms-analysis/CombineHarvester.git
 
 scram b 

at your CMSSW project src directory.
 
 Exec:
 ==============
 In current folder, one can then run for all mass points (mu+jets channel) using,

rm -rf local ; for i in 80 90 100 120 140 150 155 160 ; do python MyLimitComputerNano.py --ch mu --cat 1 --mass $i ; done

Next you can plot the results using,

root -l MyLimitPlotterNano.C+

If you are interested to produce impact plot, then first change directory to "cd local/mu/Cat1_Inc/Mass80/" and then execute,

source ../../../../impact_plot.sh t2w_combine_datacard_hcs_13TeV_mu_Cat1_Inc_WH80.root 80
 
 To Do:
 ==============
 If one wishes to check the result for election channel, then (s)he might needs to modify two plces,
 1. comment/uncomment the syst line for appropriate lepton in MyTemplateDataCardNano.txt
 2. Change "_kb_mjj_mu" to "_kb_mjj_ele" in MyLimitComputerNano.py
 before the running the above mentioned code again.
