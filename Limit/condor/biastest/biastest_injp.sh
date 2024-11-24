#!/bin/bash

mass=$1
year=$2
ch=$3
injpoint=$4
rundir=$5
random=$6
clusproc=$7

echo "List arguements: "$@

ntoys=50

basedir=/home/hep/idas/CMS-Analysis/NanoAOD-Analysis/SkimAna/limit
indir_SR_base=$basedir/Imperial-PA-2024-10-08/10_mixed_MVA_lnNfixed/${year}/Comb/${ch}/Cat1_Inc/Mass$mass
indir_MR_base=$basedir/Imperial-PA-2024-10-08/11_mixed_MVA_lnNfixed_exc0x50/${year}/Comb/${ch}/Cat1_Inc/Mass$mass
currdir=$PWD
testdir=$rundir/${ch}_${year}_x50_t${ntoys}_test/Cat1_Inc/Mass$mass

if [ ! -d $testdir ] ; then
    mkdir -p $testdir
else
    rm $testdir/*.*
fi

cp $indir_SR_base/combine_datacard_hcs_13TeV_${ch}_Cat1_Inc_WH${mass}.txt  $testdir/datacard_SR1_WH${mass}.txt
cp $indir_SR_base/Shapes_hcs_13TeV_*.root  $testdir/

cp $indir_MR_base/combine_datacard_hcs_13TeV_${ch}_Cat1_Inc_WH${mass}.txt  $testdir/datacard_MR1_WH${mass}.txt
cp $indir_MR_base/Shapes_hcs_13TeV_*.root  $testdir/

#The following lines are to remove the bound of qcdrate
sed 's:\[0.0,6.0\]::g' $testdir/datacard_SR1_WH${mass}.txt > /tmp/datacard_SR1_WH${mass}.txt
sed 's:\[0.0,6.0\]::g' $testdir/datacard_MR1_WH${mass}.txt > /tmp/datacard_MR1_WH${mass}.txt

mv  /tmp/datacard_SR1_WH${mass}.txt $testdir/datacard_SR1_WH${mass}.txt
mv  /tmp/datacard_MR1_WH${mass}.txt $testdir/datacard_MR1_WH${mass}.txt

cd $testdir
pwd
echo "==== END OF COPY ========"

# Copy and combine data card
combineCards.py signal=datacard_SR1_WH${mass}.txt nocharm=datacard_MR1_WH${mass}.txt > datacard_SR_MR_WH${mass}.txt
combineCards.py signal=datacard_SR1_WH${mass}.txt > datacard_SR_WH${mass}.txt
combineCards.py nocharm=datacard_MR1_WH${mass}.txt > datacard_MR_WH${mass}.txt
text2workspace.py datacard_SR_MR_WH${mass}.txt --channel-masks -P HiggsAnalysis.CombinedLimit.ChargedHiggs:brChargedHiggs #need to create workspace using physics model
text2workspace.py datacard_SR_WH${mass}.txt -P HiggsAnalysis.CombinedLimit.ChargedHiggs:brChargedHiggs
text2workspace.py datacard_MR_WH${mass}.txt -P HiggsAnalysis.CombinedLimit.ChargedHiggs:brChargedHiggs
echo "==== END OF SR and MR WORKSPACES ========"

#Calculate the limit in the signal region, later used as injected values for median and +/- 1sigmas
combine --run blind --rAbsAcc 0.000001 datacard_SR_WH${mass}.root -M AsymptoticLimits --mass ${mass}
outfile=limit.txt
root -l -b -q $basedir/codes/ReadLimit.C\(\""$outfile"\",$mass\)
cat $outfile
meanval=`tail -n 1 $outfile | awk '{print $2}'`
Lval=`head -n 1 $outfile | awk '{print $2}'`
Hval=`head -n 2 $outfile | tail -n 1 | awk '{print $2}'`
echo "==== END OF AsymptoticLimits results ========"

#script snippet to construct the string for masking signa channels
fl_file=/tmp/fl_$(date +%Y-%m-%d__%H%M%S).txt
grep autoMCStats datacard_SR_MR_WH${mass}.txt | grep signal | awk '{print $1}' > ${fl_file}
unset array ; declare -a array ; nof_line=0 ; while read ifile ; do array[$nof_line]=mask_${ifile}=1 ; nof_line=$[$nof_line+1] ; done < ${fl_file} ; echo Args are : ${array[@]}
app="" ; for i in `seq 0 $[$nof_line-1]`; do if [ $i -eq 0 ] ; then app=`echo ${array[$i]}` ; else app=$app,`echo ${array[$i]}` ; fi ; done
echo $app

# First perform FitDiagnostics SR+MR with mask for SR
# Step 1 "Measure the Nuisance Parameters in the MR" (https://twiki.cern.ch/twiki/bin/viewauth/CMS/B2GStatisticsRecommendations#B2G_Requested_Statistical_Tests)
combine datacard_SR_MR_WH${mass}.root -M FitDiagnostics -m $mass --redefineSignalPOIs BR --setParameterRanges BR=-2.0,2.0  --setParameters $app  --cminDefaultMinimizerStrategy 0 --robustFit 1  -n _SRMR
echo "==== END OF STEP1 ========"
python3 $currdir/importPars.py $testdir/datacard_SR_WH${mass}.txt $testdir/fitDiagnostics_SRMR.root
echo "==== END OF STEP2 ========"

if [ $injpoint = '0' ] ; then
    echo "==== BEGIN for BRinj=0  ========"
    combine morphedWorkspace.root -M GenerateOnly --toysFrequentist --bypassFrequentistFit -t $ntoys --saveToys -m $mass --redefineSignalPOIs BR --setParameters BR=0.0 -n _SRMR_0 -s ${random}
    combine morphedWorkspace.root -M FitDiagnostics  --toysFile higgsCombine_SRMR_0.GenerateOnly.mH${mass}.${random}.root -t $ntoys --toysFrequentist -m $mass --redefineSignalPOIs BR --setParameterRanges BR=-0.5,0.5  --cminDefaultMinimizerStrategy 0 --robustFit 1 -n BR_0.${clusproc}.${random}
    echo "==== END OF STEP3 BRinj=0.0 ========"
elif [ $injpoint = 'L' ] ; then
    echo "==== BEGIN for BRinj=${Lval}  ========"
    combine morphedWorkspace.root -M GenerateOnly --toysFrequentist --bypassFrequentistFit -t $ntoys --saveToys -m $mass --redefineSignalPOIs BR --setParameters BR=${Lval}  -n _SRMR_${injpoint} -s ${random}
    combine morphedWorkspace.root -M FitDiagnostics  --toysFile higgsCombine_SRMR_${injpoint}.GenerateOnly.mH${mass}.${random}.root -t $ntoys --toysFrequentist -m $mass --redefineSignalPOIs BR --setParameterRanges BR=-0.5,0.5  --cminDefaultMinimizerStrategy 0 --robustFit 1 -n BR_${injpoint}.${clusproc}.${random}
    echo "==== END OF STEP3 BRinj=${Lval} ========"
elif [ $injpoint = 'H' ] ; then
    echo "==== BEGIN for BRinj=${Hval}  ========"
    combine morphedWorkspace.root -M GenerateOnly --toysFrequentist --bypassFrequentistFit -t $ntoys --saveToys -m $mass --redefineSignalPOIs BR --setParameters BR=${Hval}  -n _SRMR_${injpoint} -s ${random}
    combine morphedWorkspace.root -M FitDiagnostics  --toysFile higgsCombine_SRMR_${injpoint}.GenerateOnly.mH${mass}.${random}.root -t $ntoys --toysFrequentist -m $mass --redefineSignalPOIs BR --setParameterRanges BR=-0.5,0.5  --cminDefaultMinimizerStrategy 0 --robustFit 1 -n BR_${injpoint}.${clusproc}.${random}
    echo "==== END OF STEP3 BRinj=${Hval} ========"
elif [ $injpoint = 'M' ] ; then
    echo "==== BEGIN for BRinj=${meanval}  ========"
    combine morphedWorkspace.root -M GenerateOnly --toysFrequentist --bypassFrequentistFit -t $ntoys --saveToys -m $mass --redefineSignalPOIs BR --setParameters BR=${meanval}  -n _SRMR_${injpoint} -s ${random}
    combine morphedWorkspace.root -M FitDiagnostics  --toysFile higgsCombine_SRMR_${injpoint}.GenerateOnly.mH${mass}.${random}.root -t $ntoys --toysFrequentist -m $mass --redefineSignalPOIs BR --setParameterRanges BR=-0.5,0.5  --cminDefaultMinimizerStrategy 0 --robustFit 1 -n BR_${injpoint}.${clusproc}.${random}
    echo "==== END OF STEP3 BRinj=${meanval} ========"
else
    echo "==== BEGIN for BRinj=1  ========"
    combine morphedWorkspace.root -M GenerateOnly --toysFrequentist --bypassFrequentistFit -t $ntoys --saveToys -m $mass --redefineSignalPOIs BR --setParameters BR=1.0 -n _SRMR_1 -s ${random}
    combine morphedWorkspace.root -M FitDiagnostics  --toysFile higgsCombine_SRMR_1.GenerateOnly.mH${mass}.${random}.root -t $ntoys --toysFrequentist -m $mass --redefineSignalPOIs BR --setParameterRanges BR=-0.5,1.5  --cminDefaultMinimizerStrategy 0 --robustFit 1 -n BR_1.${clusproc}.${random}
    echo "==== END OF STEP3 BRinj=0.0 ========"    
fi
# # echo "==== END OF STEP3 BRinj=1.0 ========"

cp $outfile $outfile.${clusproc}.${random}

ls -ltr
cd $currdir
