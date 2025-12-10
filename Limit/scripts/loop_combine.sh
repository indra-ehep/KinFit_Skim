cat_dir="Cat1_Inc"

echo cat_dir : $cat_dir
currdir=$PWD
#sampledir=Imperial-PA-2024-10-08/20_mixed_MVA_lnNfixed_retest/Run2/Comb
#sampledir=Imperial-PA-2024-10-08/38_unblinded_MVA_lnNfixed_qcdddfulluncorr_symm_10GeVbin/Run2/Comb
#sampledir=Imperial-PA-2024-10-08/42_unblinded_MVA_lnNfixed_qcddd2_bc3_uncorr_symm_10GeV/Run2/Comb
#sampledir=Imperial-PA-2024-10-08/43_unblinded_MVA_lnNfixed_qcddd6_bc3_uncorr_symm_10GeV/Run2/Comb
#sampledir=Imperial-PA-2024-10-08/44_unblinded_MVA_lnNfixed_qcddd6_bc3_uncorr_symm/Run2/Comb
#sampledir=/home/hep/idas/CMS-Analysis/NanoAOD-Analysis/SkimAna/lx04_impact-data/local/mu_ele_Run2_impact_qcdrange50_qcddd6_bc3_uncorr_brpm2_x0p02_10GeV_iter128/local
#sampledir=/home/hep/idas/CMS-Analysis/NanoAOD-Analysis/SkimAna/lx04_impact-data/local/mu_ele_Run2_impact_qcdrange50_qcddd6_bc3_uncorr_brpm2_x0p02_5GeV_iter130/local
sampledir=Imperial-PA-2024-10-08/49_unblinded_MVA_lnNfixed_qcdrangepm50_qcddd6_bc3_uncorr_symm_10GeV/Run2/Comb
#sampledir=Imperial-PA-2024-10-08/50_unblinded_MVA_lnNfixed_qcdrange0to50_qcddd6_bc3_uncorr_symm_10GeV/Run2/Comb
#sampledir=Imperial-PA-2024-10-08/50_unblinded_MVA_lnNfixed_qcdrange0to50_qcddd6_bc3_uncorr_symm_5GeV/Run2/Comb
#sampledir=Imperial-PA-2024-10-08/51_unblinded_MVA_lnNfixed_qcdrangepm100_qcddd6_bc3_uncorr_symm_10GeV/Run2/Comb
#sampledir=Imperial-PA-2024-10-08/52_unblinded_MVA_lnNfixed_qcdrangepm100_qcddd3_bc3_uncorr_symm_10GeV/Run2/Comb
#sampledir=Imperial-PA-2024-10-08/53_unblinded_MVA_lnNfixed_qcdrange0to50_qcddd3_bc3_uncorr_symm_10GeV/Run2/Comb
#sampledir=Imperial-PA-2024-10-08/53_unblinded_MVA_lnNfixed_qcdrange0to50_qcddd3_bc3_uncorr_symm_5GeV/Run2/Comb
#sampledir=Imperial-PA-2024-10-08/54_unblinded_MVA_lnNfixed_qcdrange0to100_qcddd6_bc3_uncorr_symm_10GeV/Run2/Comb
#sampledir=Imperial-PA-2024-10-08/54_unblinded_MVA_lnNfixed_qcdrange0to100_qcddd6_bc3_uncorr_symm_5GeV/Run2/Comb

#iter1: 12543
#extraarginifit="--rAbsAcc 0.000001 -s 12543 --cminPreFit 0 --cminDefaultMinimizerStrategy 0 --cminPoiOnlyFit --cminPreScan "
#minbr=-0.5 maxbr=0.5

#iter2: 12544 (change range)
#extraarginifit="--rAbsAcc 0.000001 -s 12544 --cminPreFit 0 --cminDefaultMinimizerStrategy 0 --cminPoiOnlyFit --cminPreScan "
#minbr=0.0 maxbr=0.1

#iter3: 12545 (2016 setting)
#extraarginifit="--rAbsAcc 0.000001 -s 12545 "
#minbr=0.0 maxbr=0.1

#iter4: 12546 (new minimizer)
#extraarginifit="--rAbsAcc 0.000001 -s 12546 --cminDefaultMinimizerStrategy 2 "
#minbr=0.0 maxbr=0.1

#iter5: 12547 (new minimizer)
#extraarginifit="--rAbsAcc 0.000001 -s 12547 --cminDefaultMinimizerStrategy 1 "
#minbr=0.0 maxbr=0.1


#tolerancefit="--setCrossingTolerance 0.02"
tolerancefit="--cminDefaultMinimizerTolerance 0.5"
minbr=0.0
maxbr=0.1
strategy=0
extraarginifit="--rAbsAcc 0.000001 -s 12545" #--cminPreFit 0 --cminDefaultMinimizerStrategy ${strategy} --cminPoiOnlyFit --cminPreScan 

#rm out-mu.log out-ele.log out*.log
for i in 40 50 60 70 80 90 100 110 120 130 140 150 155 160 #all
#for i in 70 #50 60 70
do
    
    echo -e "\nProcessing for mass point : $i\n\n"
    sleep 0

    rundir=$sampledir/ele/${cat_dir}/Mass$i
    cd $rundir
    pwd
    #rm *.AsymptoticLimits.*
    #combine --rAbsAcc 0.000001 -s 12543 --setParameterRanges BR=-2.0,2.0 t2w_combine_datacard_hcs_13TeV_ele_Cat1_Inc_WH${i}.root -M AsymptoticLimits --mass ${i} --name _hcs_13TeV_ele_Cat1_Inc
    combine $extraarginifit --setParameterRanges BR=$minbr,$maxbr t2w_combine_datacard_hcs_13TeV_ele_Cat1_Inc_WH${i}.root -M AsymptoticLimits --mass ${i} --name _hcs_13TeV_ele_Cat1_Inc 
    cd -  
    
    rundir=$sampledir/mu/${cat_dir}/Mass$i
    cd $rundir
    pwd
    #rm *.AsymptoticLimits.*
    #combine --rAbsAcc 0.000001 -s 12543 --setParameterRanges BR=-2.0,2.0 t2w_combine_datacard_hcs_13TeV_mu_Cat1_Inc_WH${i}.root -M AsymptoticLimits --mass ${i} --name _hcs_13TeV_mu_Cat1_Inc
    combine $extraarginifit --setParameterRanges BR=$minbr,$maxbr t2w_combine_datacard_hcs_13TeV_mu_Cat1_Inc_WH${i}.root -M AsymptoticLimits --mass ${i} --name _hcs_13TeV_mu_Cat1_Inc 
    cd -  

    rundir=$sampledir/mu_ele/${cat_dir}/Mass$i
    cd $rundir
    pwd
    #rm *.AsymptoticLimits.*
    #combine --rAbsAcc 0.000001 -s 12543 --setParameterRanges BR=-2.0,2.0 t2w_combine_datacard_hcs_13TeV_mu_ele_Cat1_Inc_WH${i}.root -M AsymptoticLimits --mass ${i} --name _hcs_13TeV_mu_ele_Cat1_Inc
    command="combine $extraarginifit --setParameterRanges BR=$minbr,$maxbr t2w_combine_datacard_hcs_13TeV_mu_ele_Cat1_Inc_WH${i}.root -M AsymptoticLimits --mass ${i} --name _hcs_13TeV_mu_ele_Cat1_Inc"
    echo $command
    $command
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
date

#ATLAS results
# x[0]=60, y[0]=0.0023286
# x[1]=70, y[1]=0.0090516
# x[2]=80, y[2]=0.023004
# x[3]=90, y[3]=0.011793
# x[4]=100, y[4]=0.0039032
# x[5]=110, y[5]=0.0019335
# x[6]=120, y[6]=0.0014585
# x[7]=130, y[7]=0.0013884
# x[8]=140, y[8]=0.00082444
# x[9]=150, y[9]=0.00076943
# x[10]=160, y[10]=0.00099777
# x[11]=168, y[11]=0.0034834
# ATLAS nof mass points : 12
# ATLAS nof mass points1 : 12
