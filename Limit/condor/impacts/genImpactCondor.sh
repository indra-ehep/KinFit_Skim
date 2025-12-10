#!/bin/sh

mass=$1
year=$2
ch=$3

echo "List arguements: "$@
echo "Now processing for $year and channel $ch"

basedir=/home/hep/idas/CMS-Analysis/NanoAOD-Analysis/SkimAna/limit
#basedir=/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/limit
#indir_SR_base=$basedir/Imperial-PA-2024-10-08/35_unblinded_MVA_lnNfixed_qcddduncorr_symmetrized/${year}/Comb/${ch}/Cat1_Inc/Mass$mass
#indir_SR_base=$basedir/Imperial-PA-2024-10-08/36_unblinded_MVA_lnNfixed_qcddduncorr_nosymm/${year}/Comb/${ch}/Cat1_Inc/Mass$mass
#indir_SR_base=$basedir/Imperial-PA-2024-10-08/38_unblinded_MVA_lnNfixed_qcdddfulluncorr_symm_10GeVbin/${year}/Comb/${ch}/Cat1_Inc/Mass$mass
#indir_SR_base=$basedir/Imperial-PA-2024-10-08/39_unblinded_MVA_lnNfixed_qcddd_bc_uncorr/${year}/Comb/${ch}/Cat1_Inc/Mass$mass
#indir_SR_base=$basedir/Imperial-PA-2024-10-08/42_unblinded_MVA_lnNfixed_qcddd2_bc3_uncorr_symm_10GeV/${year}/Comb/${ch}/Cat1_Inc/Mass$mass
indir_SR_base=$basedir/Imperial-PA-2024-10-08/43_unblinded_MVA_lnNfixed_qcddd6_bc3_uncorr_symm_10GeV/${year}/Comb/${ch}/Cat1_Inc/Mass$mass
#indir_SR_base=$basedir/Imperial-PA-2024-10-08/44_unblinded_MVA_lnNfixed_qcddd6_bc3_uncorr_symm/${year}/Comb/${ch}/Cat1_Inc/Mass$mass
#indir_SR_base=$basedir/Imperial-PA-2024-10-08/45_unblinded_MVA_lnNfixed_bc3_uncorr_symm_10GeV/${year}/Comb/${ch}/Cat1_Inc/Mass$mass
#indir_SR_base=$basedir/Imperial-PA-2024-10-08/46_unblinded_MVA_lnNfixed_qcddd3_bc3_uncorr_symm_10GeV/${year}/Comb/${ch}/Cat1_Inc/Mass$mass

outdir=local/${year}/${ch}/Cat1_Inc/Mass$mass
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
#cp $indir_SR_base/$wsname $testdir/

#The following lines are to remove the bound of qcdrate
#sed 's:\[0.0,10.0\]:\[0.0,30.0\]:g' $testdir/${cardname} > /tmp/${cardname}
#sed 's:1\ \[0.0,10.0\]::g' $testdir/${cardname} > /tmp/${cardname}
#sed 's:1\ \[0.0,10.0\]:15 :g' $testdir/${cardname} > /tmp/${cardname}
# sed 's:\[0.0,10.0\]:\[-30.0,30.0\]:g' $testdir/${cardname} > /tmp/${cardname}
# sed 's:1\ \[0.0,10.0\]:3.0 \[1.0,8.0\]:g' $testdir/${cardname} > /tmp/${cardname}
#sed 's:\[0.0,6.0\]:\[-50.0,50.0\]:g' $testdir/${cardname} > /tmp/${cardname}
sed 's:\[0.0,6.0\]:\[-30.0,30.0\]:g' $testdir/${cardname} > /tmp/${cardname}
mv  /tmp/${cardname} $testdir/${cardname}
sed 's:\[0.0,10.0\]:\[-30.0,30.0\]:g' $testdir/${cardname} > /tmp/${cardname}
mv  /tmp/${cardname} $testdir/${cardname}

# for syst in qcdratemuExcL2016 qcdratemuExcM2016 qcdratemuExcT2016 qcdrateeleExcL2016 qcdrateeleExcM2016 qcdrateeleExcT2016 qcdratemuExcL2017 qcdratemuExcM2017 qcdratemuExcT2017 qcdrateeleExcL2017 qcdrateeleExcM2017 qcdrateeleExcT2017 qcdratemuExcL2018 qcdratemuExcM2018 qcdratemuExcT2018 qcdrateeleExcL2018 qcdrateeleExcM2018 qcdrateeleExcT2018 
# do
#     sed "s:^${syst}:qcdrate:g" $testdir/${cardname} > /tmp/${cardname}
#     mv  /tmp/${cardname} $testdir/${cardname}
# done 

cd $testdir
pwd
echo "==== END OF COPY ========"


combineCards.py ${cardname} >  /tmp/${cardname}
mv /tmp/${cardname} ${cardname}
text2workspace.py ${cardname} -P HiggsAnalysis.CombinedLimit.ChargedHiggs:brChargedHiggs -o $wsname 
#cp $indir_SR_base/$wsname .
echo "==== END OF WORKSPACES ========"


extraarginifit="--cminPreFit 3"
if [ "$mass" = "80" ]; then
    extraarginifit="--cminPreFit 3 --robustFit 1 "
fi

tolerancefit=""
#tolerancefit="--setCrossingTolerance 0.02 --cminDefaultMinimizerTolerance 0.9"
#tolerancefit="--setCrossingTolerance 0.02"
if [ "$year" = "2016" ]; then
    tolerancefit="--cminDefaultMinimizerTolerance 0.5 --setCrossingTolerance 0.04"
elif [ "$year" = "2017" ]; then
    tolerancefit="--setCrossingTolerance 0.02"
elif [ "$year" = "2018" ]; then
    tolerancefit=""
fi

minbr=-0.1
maxbr=0.1
# if [ "$mass" = "150" ]; then
#     minbr=-0.1
#     maxbr=0.1
# fi
strategy=0
strategyfit=0
strategyprefit=$[$strategyfit+1]


## Impact plots #####################
combine -M MultiDimFit -d ${wsname} --redefineSignalPOIs BR $extraarginifit --setParameterRanges BR=$minbr,$maxbr --algo singles --cl=0.68 --cminDefaultMinimizerStrategy ${strategy} 
combineTool.py -M Impacts -d ${wsname} -m $mass --doInitialFit $extraarginifit --redefineSignalPOIs BR --setParameterRanges BR=$minbr,$maxbr --cminDefaultMinimizerStrategy ${strategy}    > doInitialFit.log 2>&1
combineTool.py -M Impacts -d ${wsname} -m $mass --doFit --robustFit 1 --redefineSignalPOIs BR --setParameterRanges BR=$minbr,$maxbr --cminDefaultMinimizerStrategy ${strategyfit} --maxFailedSteps 20 --parallel 32 --cminPoiOnlyFit --cminPreScan --cminPreFit ${strategyprefit} ${tolerancefit} --job-mode condor --task-name run --dry-run  > doFit_updatedtolerances.log  2>&1 #--cminDefaultMinimizerTolerance 0.7 --setCrossingTolerance 0.02 --freezeParameters MH,allConstrainedNuisances,rgx{.*}
nofline=`wc -l condor_run.sh | awk '{print $1}'`
tline=$[$nofline-8]
tail -n $tline condor_run.sh  > test.sh
mv test.sh condor_run.sh
## Impact plots #####################

#ls -ltr
cd $currdir
