category=1

if [ $category -eq 1 ] ; then
    cat_dir="Cat1_Inc"
elif [ $category -eq 2 ] ; then
    cat_dir="Cat2_cTagInc"
elif [ $category -eq 3 ] ; then
    cat_dir="Cat3_cTagEx"
fi

echo cat_dir : $cat_dir
currdir=$PWD

#for i in 40 50 60 70 80 90 100 110 120 130 140 150 155 160 #nanoAOD
#for i in 40 50 60 70 90 100 110 120 130 140 150 155 160 #nanoAOD-80
#for i in 160 155 150 140 130 120 110 100 90 80 70 60 50 40 #nanoAOD reverse
#for i in 80 90 100 120 140 150 155 160  #miniAOD
for i in 40
#for i in 110 120 130 140 150 155 160 #nanoAOD 40 50 60 70 80 90 #
do
    
    echo -e "\nProcessing for mass point : $i\n\n"
    sleep 1
    
    # python3 MyLimitComputer.py --ch ele --cat $category --mass $i  --year "run2"
    # cd local/ele/${cat_dir}/Mass$i 
    # source ../../../../impact_plot.sh t2w_combine_datacard_hcs_13TeV_ele_${cat_dir}_WH$i.root $i 
    # cp nuisImpactPDF.pdf nuisImpactPDF_ele_${i}.pdf
    # # /usr/bin/pdfseparate nuisImpactPDF_ele_${i}.pdf nuisImpactPDF_ele_${i}_%d.pdf
    # cd -  
    
    # python3 MyLimitComputer.py --ch mu --cat $category --mass $i  --year "run2"
    # cd local/mu/${cat_dir}/Mass$i 
    # source ../../../../impact_plot.sh t2w_combine_datacard_hcs_13TeV_mu_${cat_dir}_WH$i.root $i 
    # cp nuisImpactPDF.pdf nuisImpactPDF_mu_${i}.pdf
    # # pdfseparate nuisImpactPDF_mu_${i}.pdf nuisImpactPDF_mu_${i}_%d.pdf
    # #atril nuisImpactPDF_mu_${i}.pdf &
    # cd -  
    
    #python3 MyLimitComputer.py --ch mu_ele --cat $category --mass $i  --year "run2"
    cd local/mu_ele/${cat_dir}/Mass$i
    for fname in `ls *.txt`
    do
    	sed 's:\[0.0,6.0\]::g' $fname > /tmp/$fname
    	mv  /tmp/$fname $fname
    done
    if [ -f t2w_combine_datacard_hcs_13TeV_mu_ele_${cat_dir}_WH${i}.root ] ; then
    	rm t2w_combine_datacard_hcs_13TeV_mu_ele_${cat_dir}_WH${i}.root
    fi
    text2workspace.py combine_datacard_hcs_13TeV_mu_ele_Cat1_Inc_WH${i}.txt -P HiggsAnalysis.CombinedLimit.ChargedHiggs:brChargedHiggs -o t2w_combine_datacard_hcs_13TeV_mu_ele_${cat_dir}_WH$i.root
    source ../../../../impact_plot.sh t2w_combine_datacard_hcs_13TeV_mu_ele_${cat_dir}_WH$i.root $i #> /tmp/out_GoF_Run2_mass${i}.log 2>&1 &
    # #source ../../../../impact_plot.sh bdt${i}.root $i #> /tmp/out_GoF_Run2_mass${i}.log 2>&1 &
    # cp nuisImpactPDF.pdf nuisImpactPDF_mu-ele_${i}.pdf
    # # /usr/bin/pdfseparate nuisImpactPDF_mu-ele_${i}.pdf nuisImpactPDF_mu-ele_${i}_%d.pdf
    # # atril nuisImpactPDF_mu-ele_${i}.pdf &
    cd -  
    # ls
    
done 
#root -l MyLimitPlotterNano.C+ 
#root -l MyLimitPlotter.C+ 
#mv result.* /tmp/
