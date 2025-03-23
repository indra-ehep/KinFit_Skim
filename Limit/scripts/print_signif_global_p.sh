#!/bin/bash

year=Run2
ch=mu_ele
basedir=$PWD

#dir=local
mass=60
#dir=Imperial-PA-2024-10-08/56_UMl_qcdrange0to50_qcddd6_bc3_uncorr_symm_nzlbin_10GeV
indir=signif_qcdrange0to50_qcddd6_bc3_uncorr_br0p0010to0p0110_sym_nzlbin_10GeV_grid100_iter1
dir=/home/hep/idas/CMS-Analysis/NanoAOD-Analysis/SkimAna/limit_lx04/local/$indir

while read index
do
    
    # echo -e "\nProcessing for mass point : $mass\n\n"
    cd $dir/$year/Comb/$ch/Cat1_Inc/Mass${mass}
    bkgfile=higgsCombine_bfit_toy${index}.MultiDimFit.mH${mass}.root
    datafile=higgsCombine_data_toy${index}.MultiDimFit.mH${mass}.root
    root -l -b -q $basedir/codes/count_toys_with_signif_lt_localmax.C+\(\""$year"\",$mass,\""${bkgfile}"\",\""${datafile}"\"\) #>> $basedir/out.log
    cd $basedir  
    
done < /tmp/indices.txt
