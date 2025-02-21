cat_dir="Cat1_Inc"

echo cat_dir : $cat_dir
currdir=$PWD
#sampledir=Imperial-PA-2024-10-08/38_unblinded_MVA_lnNfixed_qcdddfulluncorr_symm_10GeVbin/Run2/Comb
#sampledir=Imperial-PA-2024-10-08/42_unblinded_MVA_lnNfixed_qcddd2_bc3_uncorr_symm_10GeV/Run2/Comb
#sampledir=Imperial-PA-2024-10-08/43_unblinded_MVA_lnNfixed_qcddd6_bc3_uncorr_symm_10GeV/Run2/Comb
#sampledir=Imperial-PA-2024-10-08/44_unblinded_MVA_lnNfixed_qcddd6_bc3_uncorr_symm/Run2/Comb
#sampledir=/home/hep/idas/CMS-Analysis/NanoAOD-Analysis/SkimAna/lx04_impact-data/local/mu_ele_Run2_impact_qcdrange50_qcddd6_bc3_uncorr_brpm2_x0p02_10GeV_iter128/local
sampledir=/home/hep/idas/CMS-Analysis/NanoAOD-Analysis/SkimAna/lx04_impact-data/local/mu_ele_Run2_impact_qcdrange50_qcddd6_bc3_uncorr_brpm2_x0p02_5GeV_iter130/local

#rm out-mu.log out-ele.log out*.log
for i in 40 50 60 70 80 90 100 110 120 130 140 150 155 160 #all
#for i in 40 #50 60 70
do
    
    echo -e "\nProcessing for mass point : $i\n\n"
    sleep 0

    rundir=$sampledir/ele/${cat_dir}/Mass$i
    cd $rundir
    pwd
    #rm *.AsymptoticLimits.*
    #combine --rAbsAcc 0.000001 -s 12543 --setParameterRanges BR=-2.0,2.0 t2w_combine_datacard_hcs_13TeV_ele_Cat1_Inc_WH${i}.root -M AsymptoticLimits --mass ${i} --name _hcs_13TeV_ele_Cat1_Inc
    combine --rAbsAcc 0.000001 -s 12543 --setParameterRanges BR=0.0,0.1 t2w_combine_datacard_hcs_13TeV_ele_Cat1_Inc_WH${i}.root -M AsymptoticLimits --mass ${i} --name _hcs_13TeV_ele_Cat1_Inc 
    cd -  
    
    rundir=$sampledir/mu/${cat_dir}/Mass$i
    cd $rundir
    pwd
    #rm *.AsymptoticLimits.*
    #combine --rAbsAcc 0.000001 -s 12543 --setParameterRanges BR=-2.0,2.0 t2w_combine_datacard_hcs_13TeV_mu_Cat1_Inc_WH${i}.root -M AsymptoticLimits --mass ${i} --name _hcs_13TeV_mu_Cat1_Inc
    combine --rAbsAcc 0.000001 -s 12543 --setParameterRanges BR=0.0,0.1 t2w_combine_datacard_hcs_13TeV_mu_Cat1_Inc_WH${i}.root -M AsymptoticLimits --mass ${i} --name _hcs_13TeV_mu_Cat1_Inc 
    cd -  

    rundir=$sampledir/mu_ele/${cat_dir}/Mass$i
    cd $rundir
    pwd
    #rm *.AsymptoticLimits.*
    #combine --rAbsAcc 0.000001 -s 12543 --setParameterRanges BR=-2.0,2.0 t2w_combine_datacard_hcs_13TeV_mu_ele_Cat1_Inc_WH${i}.root -M AsymptoticLimits --mass ${i} --name _hcs_13TeV_mu_ele_Cat1_Inc
    combine --rAbsAcc 0.000001 -s 12543 --setParameterRanges BR=0.0,0.1 t2w_combine_datacard_hcs_13TeV_mu_ele_Cat1_Inc_WH${i}.root -M AsymptoticLimits --mass ${i} --name _hcs_13TeV_mu_ele_Cat1_Inc 
    cd -  
    

    #source calc_limit.sh $i 2016 ele 0 >> out-ele.log 2>&1 
    #source calc_limit.sh $i 2016 mu 0 >> out-mu.log 2>&1
    #echo ========== ending calculation for mass $i ========== >> out-mu.log 2>&1
    # source calc_limit.sh $i 2016 mu_ele 0 > out_${i}.log 2>&1
    # source calc_limit.sh $i 2017 mu_ele 0 > out_${i}.log 2>&1
    #source calc_limit.sh $i 2018 mu_ele 0 > out_${i}.log 2>&1
    #source calc_limit.sh $i Run2 mu_ele 0 >> out.log 2>&1 
    #source calc_limit.sh $i Run2 mu_ele 0 > out_${i}.log 2>&1 
    # ls
    echo ========== ending calculation for mass $i ========== >> out.log 2>&1
done 
