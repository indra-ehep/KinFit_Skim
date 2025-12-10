#!/bin/bash

refdir=$1
basedir=/home/hep/idas/CMS-Analysis/NanoAOD-Analysis/SkimAna/limit_lx04/local
# for year in Run2 2016 2017 2018
# do
#     for cat in Comb ExcL ExcM ExcT
#     do
# 	dir=$basedir/$refdir/$year/$cat/
# 	root -l -b -q codes/LoopLimitPlotsNano.C\(\""${dir}"\"\)
#     done
# done

for year in Run2 2016 2017 2018
do
    for cat in Comb 
    do
	dir=$basedir/$refdir/$year/$cat/
	root -l -b -q codes/LoopLimitPlotsNano.C\(\""${dir}"\"\)
    done
done

for year in 2016 2017 2018
do
    for cat in ExcL ExcM ExcT
    do
	dir=$basedir/$refdir/$year/$cat/
	root -l -b -q codes/LoopLimitPlotsNano.C\(\""${dir}"\"\)
    done
done
