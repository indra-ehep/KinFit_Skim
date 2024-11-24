#!/bin/bash

mass=$1
year=$2
ch=$3
ntoys=500

#indir_SR_base=$PWD/TIFRAPAR-2023-01-15/44_trigSF_impacts_bld_excLMT/${year}/Comb/${ch}/Cat1_Inc/Mass$mass
#indir_SR_base=$PWD/TIFRAPAR-2023-01-15/57_JECSplit_bld_all_uncorr_7Shapes/${year}/Comb/${ch}/Cat1_Inc/Mass$mass
#indir_SR_base=$PWD/TIFRAPAR-2023-01-15/81_JECSplit_bld_all_uncorr_7Shapes_unbound_qcdrate/${year}/Comb/${ch}/Cat1_Inc/Mass$mass
#indir_SR_base=$PWD/TIFRAPAR-2023-01-15/95_no-dijet-edge-effect_bld_unbound_qcdrate/${year}/Comb/${ch}/Cat1_Inc/Mass$mass
indir_SR_base=$PWD/Imperial-PA-2024-10-08/10_mixed_MVA_lnNfixed/${year}/Comb/${ch}/Cat1_Inc/Mass$mass

#indir_MR_base=$PWD/TIFRAPAR-2023-01-15/47_trigSF_unbld_exc0_stat/${year}/Comb/${ch}/Cat1_Inc/Mass$mass
#indir_MR_base=$PWD/TIFRAPAR-2023-01-15/48_trigSF_unbld_exc0x200_stat/${year}/Comb/${ch}/Cat1_Inc/Mass$mass
#indir_MR_base=$PWD/TIFRAPAR-2023-01-15/48_trigSF_unbld_exc0x2E5_stat/${year}/Comb/${ch}/Cat1_Inc/Mass$mass
#indir_MR_base=$PWD/TIFRAPAR-2023-01-15/78_JECSplit_unbld_exc0x200_all_uncorr_7Shapes/${year}/Comb/${ch}/Cat1_Inc/Mass$mass
#indir_MR_base=$PWD/TIFRAPAR-2023-01-15/80_JECSplit_unbld_exc0x200_all_uncorr_7Shapes_unbound_qcdrate/${year}/Comb/${ch}/Cat1_Inc/Mass$mass
#indir_MR_base=$PWD/TIFRAPAR-2023-01-15/97_no-dijet-edge-effect_unbld_exc0x50_unbound_qcdrate/${year}/Comb/${ch}/Cat1_Inc/Mass$mass
indir_MR_base=$PWD/Imperial-PA-2024-10-08/11_mixed_MVA_lnNfixed_exc0x50/${year}/Comb/${ch}/Cat1_Inc/Mass$mass

testdir=$PWD/local/${ch}_${year}_x50_t${ntoys}_gof_mc/Cat1_Inc/Mass$mass

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

basedir=$PWD
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
echo meanval : $meanval
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

# Step 2 "Generate Toys"
python3 $basedir/importPars.py $testdir/datacard_SR_WH${mass}.txt $testdir/fitDiagnostics_SRMR.root
combine morphedWorkspace.root -M GenerateOnly --toysFrequentist --bypassFrequentistFit -t $ntoys --saveToys -m $mass --redefineSignalPOIs BR --setParameters BR=0.0 --freezeParameters BR -n _SRMR_0
echo "==== END OF STEP2 BRinj=0.0 ========"

# Step 3 MC GoF for BR==0
combine datacard_SR_WH${mass}.root -M GoodnessOfFit -m $mass --algo saturated  --toysFile higgsCombine_SRMR_0.GenerateOnly.mH${mass}.123456.root --toysFrequentist -t $ntoys -n _SRMR_0 --redefineSignalPOIs BR --setParameterRanges BR=-0.5,0.5 --setParameters BR=0.0
echo "==== END OF STEP3 BRinj=0.0 ========"

# Now repeat step2+3 other BR values from AsymptoticLimits
echo "==== BEGIN Loop ========"
while read sigma brval
do
    echo $brval  and $sigma
    echo "==== BEGIN for BRinj=$brval  ========"
    combine morphedWorkspace.root -M GenerateOnly --toysFrequentist --bypassFrequentistFit -t $ntoys --saveToys -m $mass --redefineSignalPOIs BR --setParameters BR=$brval  --freezeParameters BR -n _SRMR_${sigma}
    echo "==== END OF STEP2 BRinj=$brval ========"
done < $outfile
echo "==== END Loop ========"

# Step 3 MC GoF for BR==$meanval
echo Meanvalue : $meanval
combine datacard_SR_WH${mass}.root -M GoodnessOfFit -m $mass --algo saturated  --toysFile higgsCombine_SRMR_M.GenerateOnly.mH${mass}.123456.root --toysFrequentist -t $ntoys -n _SRMR_M --redefineSignalPOIs BR --setParameterRanges BR=-0.5,0.5 --setParameters BR=$meanval
echo "==== END OF STEP3 BRinj=$meanval ========"

# Step 2 "Generate Toys"
combine morphedWorkspace.root -M GenerateOnly --toysFrequentist --bypassFrequentistFit -t $ntoys --saveToys -m $mass --redefineSignalPOIs BR --setParameters BR=1.0 --freezeParameters BR -n _SRMR_1
echo "==== END OF STEP2 BRinj=1.0 ========"

# Step 3 MC GoF for BR==1
combine datacard_SR_WH${mass}.root -M GoodnessOfFit -m $mass --algo saturated  --toysFile higgsCombine_SRMR_1.GenerateOnly.mH${mass}.123456.root --toysFrequentist -t $ntoys -n _SRMR_1 --redefineSignalPOIs BR --setParameterRanges BR=-1.0,2.0 --setParameters BR=1.0
echo "==== END OF STEP3 BRinj=1.0 ========"

ls -ltr
cd $basedir
