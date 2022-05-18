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

#for i in 80 90 100 110 120 130 140 150 155 160 #nanoAOD
#for i in 80 90 100 120 140 150 155 160  #miniAOD
for i in 80
#for i in 90 100 110 120 130 140 150 155 160
do 
    
    #python MyLimitComputer.py --ch ele --cat $category --mass $i --isGOF 1
    # cd local/ele/${cat_dir}/Mass$i 
    # source ../../../../impact_plot.sh t2w_combine_datacard_hcs_13TeV_ele_${cat_dir}_WH$i.root $i 
    # pdfseparate -f 1 -l 1 nuisImpactPDF.pdf nuisImpactPDF%d.pdf 
    # cd -  
    
    python MyLimitComputer.py --ch mu --cat $category --mass $i --isGOF 0
    #python MyLimitComputer.py --ch mu --cat $category --mass $i --isGOF 1
    # cd local/mu/${cat_dir}/Mass$i 
    # source ../../../../impact_plot.sh t2w_combine_datacard_hcs_13TeV_mu_${cat_dir}_WH$i.root $i 
    # pdfseparate -f 1 -l 1 nuisImpactPDF.pdf nuisImpactPDF%d.pdf 
    # cd -  
    
    # #python MyLimitComputer.py --ch mu_ele --cat $category --mass $i --isGOF 1 #Never run this instead use the commands below
    # combinedir=local/mu_ele/${cat_dir}/Mass$i
    # if [ ! -d $combinedir ] ; then
    # 	mkdir -p $combinedir
    # fi
    # cp local/ele/${cat_dir}/Mass$i/datacard*.txt  local/ele/${cat_dir}/Mass$i/Shapes*.root  $combinedir/
    # cp local/mu/${cat_dir}/Mass$i/datacard*.txt  local/mu/${cat_dir}/Mass$i/Shapes*.root  $combinedir/
    # cd $combinedir/
    # ls
    # combineCards.py datacard_*ele*.txt datacard_*mu*.txt > combine_datacard_hcs_13TeV_mu_ele_${cat_dir}_WH$i.txt
    # text2workspace.py combine_datacard_hcs_13TeV_mu_ele_${cat_dir}_WH$i.txt -P HiggsAnalysis.CombinedLimit.ChargedHiggs:brChargedHiggs -o t2w_combine_datacard_hcs_13TeV_mu_ele_${cat_dir}_WH$i.root
    # combine --rAbsAcc 0.000001 --run blind t2w_combine_datacard_hcs_13TeV_mu_ele_${cat_dir}_WH$i.root -M AsymptoticLimits --mass $i --name _hcs_13TeV_mu_ele_${cat_dir}
    # cd $currdir

    #ls
done 
#root -l MyLimitPlotterNano.C+ 
#root -l MyLimitPlotter.C+ 
#mv result.pdf result_old.pdf
