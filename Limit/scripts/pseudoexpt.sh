#!/bin/bash

mass=$1
ch=mu_ele
ntoys=500
# indir_SR_base=/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/limit/local/mu_SR/Cat1_Inc/Mass$mass
# indir_MR_base=/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/limit/local/mu_MR/Cat1_Inc/Mass$mass

indir_SR_base=$PWD/TIFRAPAR-2023-01-15/33_elereliso_bld_excLMT_stat/Run2/Comb/${ch}/Cat1_Inc/Mass$mass
indir_MR_base=$PWD/TIFRAPAR-2023-01-15/32_elereliso_unbld_exc0_stat/Run2/Comb/${ch}/Cat1_Inc/Mass$mass

testdir=$PWD/local/${ch}/Cat1_Inc/Mass$mass

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

# ############################################################
# # B2G suggestion
# combineCards.py signal=datacard_SR1_WH${mass}.txt nocharm=datacard_MR1_WH${mass}.txt > datacard_SR_MR_WH${mass}.txt
# combineCards.py signal=datacard_SR1_WH${mass}.txt > datacard_SR_WH${mass}.txt
# combineCards.py nocharm=datacard_MR1_WH${mass}.txt > datacard_MR_WH${mass}.txt
# text2workspace.py datacard_SR_MR_WH${mass}.txt --channel-masks 
# text2workspace.py datacard_SR_WH${mass}.txt 
# text2workspace.py datacard_MR_WH${mass}.txt 

# combine --run blind --rAbsAcc 0.000001 datacard_SR_WH${mass}.root -M AsymptoticLimits --mass ${mass}

# combine datacard_SR_MR_WH${mass}.root -M FitDiagnostics --setParameters mask_signal_ch1_ch1=1,mask_signal_ch1_ch2=1,mask_signal_ch1_ch3=1 -m $mass

# python3 $basedir/importPars.py $testdir/datacard_SR_WH${mass}.txt $testdir/fitDiagnosticsTest.root
# combine morphedWorkspace.root -M GenerateOnly --toysFrequentist --bypassFrequentistFit -t $ntoys --saveToys -m $mass --expectSignal 0.0657 --freezeParameters r --setParameters r=0.1

# combine datacard_SR_WH${mass}.root -M GoodnessOfFit -m $mass --algo saturated  --toysFile higgsCombineTest.GenerateOnly.mH${mass}.123456.root --toysFrequentist -t $ntoys

# combine morphedWorkspace.root -M FitDiagnostics  --toysFile higgsCombineTest.GenerateOnly.mH${mass}.123456.root -t $ntoys --rMin -1.0 --rMax 1.0

############################################################
# Common
combineCards.py signal=datacard_SR1_WH${mass}.txt nocharm=datacard_MR1_WH${mass}.txt > datacard_SR_MR_WH${mass}.txt
combineCards.py signal=datacard_SR1_WH${mass}.txt > datacard_SR_WH${mass}.txt
combineCards.py nocharm=datacard_MR1_WH${mass}.txt > datacard_MR_WH${mass}.txt
text2workspace.py datacard_SR_MR_WH${mass}.txt --channel-masks -P HiggsAnalysis.CombinedLimit.ChargedHiggs:brChargedHiggs
text2workspace.py datacard_SR_WH${mass}.txt -P HiggsAnalysis.CombinedLimit.ChargedHiggs:brChargedHiggs
text2workspace.py datacard_MR_WH${mass}.txt -P HiggsAnalysis.CombinedLimit.ChargedHiggs:brChargedHiggs

combine --run blind --rAbsAcc 0.000001 datacard_SR_WH${mass}.root -M AsymptoticLimits --mass ${mass}
outfile=limit.txt
root -l -b -q $basedir/codes/ReadLimit.C\(\""$outfile"\",$mass\)


# First perform SR+MR with mask for SR

combine datacard_SR_MR_WH${mass}.root -M FitDiagnostics --setParameters mask_signal_ch1_ch1=1,mask_signal_ch1_ch2=1,mask_signal_ch1_ch3=1,mask_signal_ch1_ch4=1,mask_signal_ch1_ch5=1,mask_signal_ch1_ch6=1,mask_signal_ch2_ch1=1,mask_signal_ch2_ch2=1,mask_signal_ch2_ch3=1,mask_signal_ch2_ch4=1,mask_signal_ch2_ch5=1,mask_signal_ch2_ch6=1,mask_signal_ch3_ch1=1,mask_signal_ch3_ch2=1,mask_signal_ch3_ch3=1,mask_signal_ch3_ch4=1,mask_signal_ch3_ch5=1,mask_signal_ch3_ch6=1 -m $mass --redefineSignalPOIs BR --setParameterRanges BR=-0.5,0.5  --cminDefaultMinimizerStrategy 0 --robustFit 1 -n _SRMR

python3 $basedir/importPars.py $testdir/datacard_SR_WH${mass}.txt $testdir/fitDiagnostics_SRMR.root

combine morphedWorkspace.root -M GenerateOnly --toysFrequentist --bypassFrequentistFit -t $ntoys --saveToys -m $mass --redefineSignalPOIs BR --setParameters BR=0.0 --freezeParameters BR -n _SRMR_0
combine morphedWorkspace.root -M FitDiagnostics  --toysFile higgsCombine_SRMR_0.GenerateOnly.mH${mass}.123456.root -t $ntoys -m $mass --redefineSignalPOIs BR --setParameterRanges BR=-0.5,0.5 --setParameters BR=0.0 --cminDefaultMinimizerStrategy 0 --robustFit 1 -n BR_0

while read sigma brval
do
    echo $brval  and $sigma
    combine morphedWorkspace.root -M GenerateOnly --toysFrequentist --bypassFrequentistFit -t $ntoys --saveToys -m $mass --redefineSignalPOIs BR --setParameters BR=$brval --freezeParameters BR -n _SRMR_${sigma}
    combine morphedWorkspace.root -M FitDiagnostics  --toysFile higgsCombine_SRMR_${sigma}.GenerateOnly.mH${mass}.123456.root -t $ntoys -m $mass --redefineSignalPOIs BR --setParameterRanges BR=-0.5,0.5 --setParameters BR=$brval --cminDefaultMinimizerStrategy 0 --robustFit 1 -n BR_${sigma}
done < $outfile

combine datacard_SR_WH${mass}.root -M GoodnessOfFit -m $mass --algo saturated  --toysFile higgsCombine_SRMR_0.GenerateOnly.mH${mass}.123456.root --toysFrequentist -t $ntoys -n _SRMR_0
combine datacard_SR_WH${mass}.root -M GoodnessOfFit -m $mass --algo saturated  --toysFile higgsCombine_SRMR_M.GenerateOnly.mH${mass}.123456.root --toysFrequentist -t $ntoys -n _SRMR_M

# ###########################################################

############################################################
# Next perform MR_only test 

# # Fit the MR region
# combine datacard_MR_WH${mass}.root -M FitDiagnostics -m $mass --redefineSignalPOIs BR --setParameterRanges BR=-0.5,0.5  --plots --saveShapes --saveWithUncertainties --saveNormalizations --cminDefaultMinimizerStrategy 0 -n _MR

# # Step 2 : Generate toys
# python3 $basedir/importPars.py $testdir/datacard_SR_WH${mass}.txt $testdir/fitDiagnostics_MR.root
# combine morphedWorkspace.root -M GenerateOnly --toysFrequentist --bypassFrequentistFit --expectSignal 1 -t $ntoys --saveToys -m $mass --redefineSignalPOIs BR --setParameters BR=0.0 --freezeParameters BR -n _MR

# # Goodness of fit
# combine datacard_SR_WH${mass}.root -M GoodnessOfFit -m $mass --algo saturated -n _MR
# combine datacard_SR_WH${mass}.root -M GoodnessOfFit -m $mass --algo saturated  --toysFile higgsCombine_MR.GenerateOnly.mH${mass}.123456.root --toysFrequentist -t $ntoys  -n _MR

############################################################

# combine datacard_MR_WH${mass}.root -M GoodnessOfFit -m $mass --algo saturated -n _MR_AN
# combine datacard_MR_WH${mass}.root -M GoodnessOfFit -m $mass --algo saturated  -t $ntoys -n _MR_AN

###########################################################

ls -ltr
cd $basedir
