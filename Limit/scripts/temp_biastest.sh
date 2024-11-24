#!/bin/bash

mass=$1
year=$2
ch=$3
ntoys=500

indir_SR_base=$PWD/TIFRAPAR-2023-01-15/95_no-dijet-edge-effect_bld_unbound_qcdrate/${year}/Comb/${ch}/Cat1_Inc/Mass$mass

# indir_MR_base=$PWD/TIFRAPAR-2023-01-15/97_no-dijet-edge-effect_unbld_exc0x50_unbound_qcdrate/${year}/Comb/${ch}/Cat1_Inc/Mass$mass
indir_MR_base=$PWD/TIFRAPAR-2023-01-15/99_no-dijet-edge-effect_unbld_exc0_no_qcdrate_pull-test/${year}/Comb/${ch}/Cat1_Inc/Mass$mass

testdir=$PWD/local/${ch}_${year}_x1_t${ntoys}_test/Cat1_Inc/Mass$mass
#testdir=$PWD/local/${ch}_${year}_x50_t${ntoys}_test_lx04/mu_ele_Run2_x50_t500_test/Cat1_Inc/Mass$mass
#testdir=$PWD/local/${ch}_${year}_x50_t${ntoys}_test_lxplus/mu_ele_Run2_x50_t500_test/Cat1_Inc/Mass$mass

if [ ! -d $testdir ] ; then
    mkdir -p $testdir
else
    rm $testdir/*.*
fi

cp $indir_SR_base/combine_datacard_hcs_13TeV_${ch}_Cat1_Inc_WH${mass}.txt  $testdir/datacard_SR1_WH${mass}.txt
cp $indir_SR_base/Shapes_hcs_13TeV_*.root  $testdir/

cp $indir_MR_base/combine_datacard_hcs_13TeV_${ch}_Cat1_Inc_WH${mass}.txt  $testdir/datacard_MR1_WH${mass}.txt
cp $indir_MR_base/Shapes_hcs_13TeV_*.root  $testdir/

basedir=$PWD
cd $testdir
pwd
echo "==== END OF COPY ========"


############################################################
# Common
# Copy and combine data card
combineCards.py signal=datacard_SR1_WH${mass}.txt nocharm=datacard_MR1_WH${mass}.txt > datacard_SR_MR_WH${mass}.txt
combineCards.py signal=datacard_SR1_WH${mass}.txt > datacard_SR_WH${mass}.txt
combineCards.py nocharm=datacard_MR1_WH${mass}.txt > datacard_MR_WH${mass}.txt
text2workspace.py datacard_SR_MR_WH${mass}.txt --channel-masks -P HiggsAnalysis.CombinedLimit.ChargedHiggs:brChargedHiggs
text2workspace.py datacard_SR_WH${mass}.txt -P HiggsAnalysis.CombinedLimit.ChargedHiggs:brChargedHiggs
text2workspace.py datacard_MR_WH${mass}.txt -P HiggsAnalysis.CombinedLimit.ChargedHiggs:brChargedHiggs
echo "==== END OF SR and MR WORKSPACES ========"

#Calculate the limit in the signal region, later used as injected values for median and +/- 1sigmas
combine --run blind --rAbsAcc 0.000001 datacard_SR_WH${mass}.root -M AsymptoticLimits --mass ${mass}
outfile=limit.txt
root -l -b -q $basedir/codes/ReadLimit.C\(\""$outfile"\",$mass\)
meanval=`tail -n 1 $outfile | awk '{print $2}'`
echo Meanvalue : $meanval
echo "==== END OF AsymptoticLimits results ========"

# First perform SR+MR with mask for SR
combine datacard_SR_MR_WH${mass}.root -M FitDiagnostics --setParameters mask_signal_ch1_ch1=1,mask_signal_ch1_ch2=1,mask_signal_ch1_ch3=1,mask_signal_ch1_ch4=1,mask_signal_ch1_ch5=1,mask_signal_ch1_ch6=1,mask_signal_ch2_ch1=1,mask_signal_ch2_ch2=1,mask_signal_ch2_ch3=1,mask_signal_ch2_ch4=1,mask_signal_ch2_ch5=1,mask_signal_ch2_ch6=1,mask_signal_ch3_ch1=1,mask_signal_ch3_ch2=1,mask_signal_ch3_ch3=1,mask_signal_ch3_ch4=1,mask_signal_ch3_ch5=1,mask_signal_ch3_ch6=1 -m $mass --redefineSignalPOIs BR --setParameterRanges BR=-0.5,0.5  --cminDefaultMinimizerStrategy 0 --robustFit 1 -n _SRMR

python3 $basedir/importPars.py $testdir/datacard_SR_WH${mass}.txt $testdir/fitDiagnostics_SRMR.root

combine morphedWorkspace.root -M GenerateOnly --toysFrequentist --bypassFrequentistFit -t $ntoys --saveToys -m $mass --redefineSignalPOIs BR --setParameters BR=0.0 --freezeParameters BR -n _SRMR_0
combine morphedWorkspace.root -M GenerateOnly --toysFrequentist --bypassFrequentistFit -t $ntoys --saveToys -m $mass --redefineSignalPOIs BR --setParameters BR=$meanval --freezeParameters BR -n _SRMR_M
combine morphedWorkspace.root -M GenerateOnly --toysFrequentist --bypassFrequentistFit -t $ntoys --saveToys -m $mass --redefineSignalPOIs BR --setParameters BR=1.0 --freezeParameters BR -n _SRMR_1
echo "==== END OF Toys generation ========"

combine datacard_SR_WH${mass}.root -M GoodnessOfFit -m $mass --algo saturated  --toysFile higgsCombine_SRMR_0.GenerateOnly.mH${mass}.123456.root --toysFrequentist -t $ntoys -n _SRMR_0 --redefineSignalPOIs BR --setParameterRanges BR=-0.5,0.5 --setParameters BR=0.0 > /tmp/out_${year}_mass${mass}_${ch}_t${ntoys}_0.log 2>&1 &
combine datacard_SR_WH${mass}.root -M GoodnessOfFit -m $mass --algo saturated  --toysFile higgsCombine_SRMR_M.GenerateOnly.mH${mass}.123456.root --toysFrequentist -t $ntoys -n _SRMR_M --redefineSignalPOIs BR --setParameterRanges BR=-0.5,0.5 --setParameters BR=$meanval > /tmp/out_${year}_mass${mass}_${ch}_t${ntoys}_M.log 2>&1 &
combine datacard_SR_WH${mass}.root -M GoodnessOfFit -m $mass --algo saturated  --toysFile higgsCombine_SRMR_1.GenerateOnly.mH${mass}.123456.root --toysFrequentist -t $ntoys -n _SRMR_1 --redefineSignalPOIs BR --setParameterRanges BR=-1.0,2.0 --setParameters BR=1.0 > /tmp/out_${year}_mass${mass}_${ch}_t${ntoys}_1.log 2>&1 &

# ###########################################################

#ls -ltr
cd $basedir
