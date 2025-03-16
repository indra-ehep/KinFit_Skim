#!/bin/bash

year=Run2
ch=mu_ele
basedir=$PWD

dir=local
#dir=Imperial-PA-2024-10-08/56_UMl_qcdrange0to50_qcddd6_bc3_uncorr_symm_nzlbin_10GeV

#for mass in 40 50 60 70 80 90 100 110 120 130 140 150 155 160 #nanoAOD
for mass in 150 
#for mass in 50 60 70 80 90 100 110 120 130 140 150 155 160 #nanoAOD
do
    
    echo -e "\nProcessing for mass point : $mass\n\n"
    sleep 1
    

    cd $dir/$year/Comb/$ch/Cat1_Inc/Mass${mass}
    source $basedir/significance.sh $mass $ch > $basedir/out_new_${year}_${ch}_${mass}.log 2>&1 &
    cd $basedir  
    # # ls
    
done 
