#!/bin/bash

year=Run2
ch=mu_ele
basedir=$PWD

dir=local
mass=60
maxproc=25
    
echo -e "\nProcessing for mass point : $mass\n\n"
sleep 1

cd $dir/$year/Comb/$ch/Cat1_Inc/Mass${mass}
wsname=t2w_combine_datacard_hcs_13TeV_${ch}_Cat1_Inc_WH${mass}.root

# #Generate Toys
# combine $wsname -M GenerateOnly --toysFrequentist -m $mass -t 1000 --saveToys --setParameters BR=0.0

for itoy in `seq 1 1000`
do
    echo ================= Processing Toy : $itoy ========================
    nofproc=`ps -ef | grep combine | grep idas | wc -l`
    while [ $nofproc -gt $maxproc ];
    do
        sleep 60
        nofproc=`ps -ef | grep combine | grep idas | wc -l`
    done
    commadbkg="combine $wsname -M MultiDimFit --redefineSignalPOI BR --setParameters BR=0.0 --freezeParameters BR --saveNLL -n _bfit_toy${itoy} -m $mass --cminPreScan  --cminPreFit 1 --cminDefaultMinimizerStrategy 0 -D higgsCombineTest.GenerateOnly.mH${mass}.123456.root:toys/toy_${itoy}"
    commadsig="combine $wsname -M MultiDimFit --redefineSignalPOI BR --algo=grid --setParameterRanges BR=0.0,1.0 --points 1000 --saveNLL -n _data_toy${itoy} -m $mass --cminPreScan --cminPreFit 1 --cminDefaultMinimizerStrategy 0 --robustFit 1 -D higgsCombineTest.GenerateOnly.mH${mass}.123456.root:toys/toy_${itoy}"

    echo -e "combine $wsname -M MultiDimFit --redefineSignalPOI BR --setParameters BR=0.0 --freezeParameters BR --saveNLL -n _bfit_toy${itoy} -m $mass --cminPreScan  --cminPreFit 1 --cminDefaultMinimizerStrategy 0 -D higgsCombineTest.GenerateOnly.mH${mass}.123456.root:toys/toy_${itoy}"
    combine $wsname -M MultiDimFit --redefineSignalPOI BR --setParameters BR=0.0 --freezeParameters BR --saveNLL -n _bfit_toy${itoy} -m $mass --cminPreScan  --cminPreFit 1 --cminDefaultMinimizerStrategy 0 -D higgsCombineTest.GenerateOnly.mH${mass}.123456.root:toys/toy_${itoy} > gpout_bkg_toy_${itoy}.log 2>&1 &
    
    echo -e "combine $wsname -M MultiDimFit --redefineSignalPOI BR --algo=grid --setParameterRanges BR=0.0,1.0 --points 1000 --saveNLL -n _data_toy${itoy} -m $mass --cminPreScan --cminPreFit 1 --cminDefaultMinimizerStrategy 0 --robustFit 1 -D higgsCombineTest.GenerateOnly.mH${mass}.123456.root:toys/toy_${itoy}"
    combine $wsname -M MultiDimFit --redefineSignalPOI BR --algo=grid --setParameterRanges BR=0.0,1.0 --points 1000 --saveNLL -n _data_toy${itoy} -m $mass --cminPreScan --cminPreFit 1 --cminDefaultMinimizerStrategy 0 --robustFit 1 -D higgsCombineTest.GenerateOnly.mH${mass}.123456.root:toys/toy_${itoy} > gpout_sig_toy_${itoy}.log 2>&1 &
    echo ================================================================
done

cd $basedir  

    

