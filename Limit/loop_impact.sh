for i in 80 90 100 110 120 130 140 150 155 160 
#for i in 80 90 100 120 140 150 155 160
do 
    python MyLimitComputer.py --ch ele --cat 1 --mass $i 
    #cd local/mu/Cat1_Inc/Mass$i 
    #source ../../../../impact_plot.sh t2w_combine_datacard_hcs_13TeV_mu_Cat1_Inc_WH$i.root $i 
    #pdfseparate -f 1 -l 1 nuisImpactPDF.pdf nuisImpactPDF%d.pdf 
    #cd -  
    ls
done 
root -l MyLimitPlotterNano.C+ 
#mv result.pdf result_old.pdf
