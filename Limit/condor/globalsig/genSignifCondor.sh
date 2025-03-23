#!/bin/sh

mass=$1
year=$2
ch=$3
cattype=$4

echo "List arguements: "$@
echo "Now processing for $year and channel $ch"

basedir=/home/hep/idas/CMS-Analysis/NanoAOD-Analysis/SkimAna/limit
indir_SR_base=$basedir/Imperial-PA-2024-10-08/56_UMl_qcdrange0to50_qcddd6_bc3_uncorr_symm_nzlbin_10GeV/${year}/${cattype}/${ch}/Cat1_Inc/Mass$mass

outdir=local/${year}/${cattype}/${ch}/Cat1_Inc/Mass$mass
currdir=$PWD

testdir=${currdir}/${outdir}
if [ ! -d $testdir ]; then
    mkdir -p $testdir
fi

cardprenom=combine_datacard_hcs_13TeV_${ch}_Cat1_Inc_WH${mass}
cardprenombkp=combine_datacard_hcs_13TeV_${ch}_Cat1_Inc_WH${mass}_bkp
cardname=${cardprenom}.txt

wsname=t2w_${cardprenom}.root

cp $indir_SR_base/${cardname}  $testdir/
cp $indir_SR_base/Shapes_hcs_13TeV_*.root  $testdir/
cp $indir_SR_base/$wsname $testdir/
cp $indir_SR_base/higgsCombineTest.GenerateOnly.mH${mass}.123456.root $testdir/


cd $testdir
pwd
echo "==== END OF COPY ========"

#extraarginifit="--cminPreFit 0" #--cminDefaultMinimizerTolerance 0.4"
# if [ "$mass" = "80" ]; then
#     extraarginifit="--cminPreFit 0 --robustFit 1"
# fi

#tolerancefit=""
#tolerancefit="--setCrossingTolerance 0.02 --cminDefaultMinimizerTolerance 0.9"
tolerancefit="--setCrossingTolerance 0.02"
if [ "$year" = "2016" ]; then
    tolerancefit="--cminDefaultMinimizerTolerance 0.5 --setCrossingTolerance 0.04"
elif [ "$year" = "2017" ]; then
    tolerancefit="--setCrossingTolerance 0.02"
elif [ "$year" = "2018" ]; then
    tolerancefit=""
fi

minbr=0.0010
maxbr=0.0110

# if [ "$mass" = "150" ]; then
#     minbr=-0.1
#     maxbr=0.1
# fi
strategy=0
strategyfit=0
strategyprefit=$[$strategyfit+1]
extraarginprefit="--cminPreScan  --cminPreFit $strategyprefit --cminDefaultMinimizerStrategy $strategy -D higgsCombineTest.GenerateOnly.mH${mass}.123456.root:toys/toy_\${itoy}" 
extraarginfit="--cminPreScan  --cminPreFit $strategyprefit --cminDefaultMinimizerStrategy $strategy -D higgsCombineTest.GenerateOnly.mH${mass}.123456.root:toys/toy_\${itoy} --robustFit 1"

# ###  Asymptotic limit #####################
# command="combine -M AsymptoticLimits ${wsname} $extraarginifit --setParameterRanges BR=$minbr,$maxbr --mass ${mass} --name _hcs_13TeV_${ch}_Cat1_Inc_3sigma"
# echo $command > condor_run.sh
# ###  Asymptotic limit #####################

echo "itoy=\$1" > condor_run.sh

command="combine ${wsname} -M MultiDimFit --redefineSignalPOI BR --setParameters BR=0.0 --freezeParameters BR --saveNLL -n _bfit_toy\${itoy} -m $mass ${extraarginprefit}"
echo $command >> condor_run.sh

command="combine ${wsname} -M MultiDimFit --redefineSignalPOI BR --algo=grid --setParameterRanges BR=$minbr,$maxbr --points 100 --saveNLL -n _data_toy\${itoy} -m $mass ${extraarginfit}"
echo $command >> condor_run.sh

#ls -ltr
cd $currdir
