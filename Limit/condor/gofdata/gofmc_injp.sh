#!/bin/bash

mass=$1
year=$2
ch=$3
injpoint=$4
rundir=$5
random=$6
clusproc=$7

echo "List arguements: "$@

ntoys=40
fnnui=10

basedir=/home/hep/idas/CMS-Analysis/NanoAOD-Analysis/SkimAna/limit
#indir_SR_base=$basedir/Imperial-PA-2024-10-08/10_mixed_MVA_lnNfixed/${year}/Comb/${ch}/Cat1_Inc/Mass$mass
#indir_SR_base=$basedir/Imperial-PA-2024-10-08/35_unblinded_MVA_lnNfixed_qcddduncorr_symmetrized/${year}/Comb/${ch}/Cat1_Inc/Mass$mass
#indir_SR_base=$basedir/Imperial-PA-2024-10-08/36_unblinded_MVA_lnNfixed_qcddduncorr_nosymm/${year}/Comb/${ch}/Cat1_Inc/Mass$mass
#indir_SR_base=$basedir/Imperial-PA-2024-10-08/37_unblinded_MVA_lnNfixed_qcdddfulluncorr_symm/${year}/Comb/${ch}/Cat1_Inc/Mass$mass
#indir_SR_base=$basedir/Imperial-PA-2024-10-08/38_unblinded_MVA_lnNfixed_qcdddfulluncorr_symm_10GeVbin/${year}/Comb/${ch}/Cat1_Inc/Mass$mass
#indir_SR_base=$basedir/Imperial-PA-2024-10-08/39_unblinded_MVA_lnNfixed_qcddd_bc_uncorr/${year}/Comb/${ch}/Cat1_Inc/Mass$mass
#indir_SR_base=$basedir/Imperial-PA-2024-10-08/40_unblinded_MVA_lnNfixed_qcddd_uncorr_nosymm_10GeVbin/${year}/Comb/${ch}/Cat1_Inc/Mass$mass
#indir_SR_base=$basedir/Imperial-PA-2024-10-08/42_unblinded_MVA_lnNfixed_qcddd2_bc3_uncorr_symm_10GeV/${year}/Comb/${ch}/Cat1_Inc/Mass$mass
#indir_SR_base=/home/hep/idas/CMS-Analysis/NanoAOD-Analysis/SkimAna/lx04_impact-data/local/mu_ele_Run2_impact_qcdrange30_qcddd6_bc3_uncorr_brpm2_x0p02_10GeV_iter122/local/${ch}/Cat1_Inc/Mass$mass
#indir_SR_base=/home/hep/idas/CMS-Analysis/NanoAOD-Analysis/SkimAna/lx04_impact-data/local/mu_ele_Run2_impact_qcdrange50_qcddd6_bc3_uncorr_brpm2_x0p02_10GeV_iter128/local/${ch}/Cat1_Inc/Mass$mass
#indir_SR_base=/home/hep/idas/CMS-Analysis/NanoAOD-Analysis/SkimAna/lx04_impact-data/local/mu_ele_Run2_impact_qcdrange50_qcddd6_bc3_uncorr_brpm2_x0p02_5GeV_iter130/local/${ch}/Cat1_Inc/Mass$mass
indir_SR_base=$basedir/Imperial-PA-2024-10-08/43_unblinded_MVA_lnNfixed_qcddd6_bc3_uncorr_symm_10GeV/${year}/Comb/${ch}/Cat1_Inc/Mass$mass
#indir_SR_base=$basedir/Imperial-PA-2024-10-08/44_unblinded_MVA_lnNfixed_qcddd6_bc3_uncorr_symm/${year}/Comb/${ch}/Cat1_Inc/Mass$mass

currdir=$PWD
qcdval=1.0
iter=100
testdir=$rundir/${ch}_${year}_t${ntoys}_gofdata_iter${iter}_qcddd6_bc3_symm_10GeV/Cat1_Inc/Mass$mass

if [ ! -d $testdir ] ; then
    mkdir -p $testdir
else
    rm $testdir/*.*
fi

cardprenom=combine_datacard_hcs_13TeV_${ch}_Cat1_Inc_WH${mass}
cardname=${cardprenom}.txt
wsname=t2w_${cardprenom}.root

cp $indir_SR_base/${cardname}  $testdir/
cp $indir_SR_base/Shapes_hcs_13TeV_*.root  $testdir/
cp $indir_SR_base/$wsname  $testdir/

#The following lines are to remove the bound of qcdrate
#sed 's:\[0.0,10.0\]::g' $testdir/${cardname} > /tmp/${cardname}
# sed 's:\[0.0,10.0\]:\[0.0,40.0\]:g' $testdir/${cardname} > /tmp/${cardname}
# mv  /tmp/${cardname} $testdir/${cardname}

# for value in 1.46 0.94999999 1.01 1.05 1.33 2.04 
# do
#     #sed "s:${value}\s\[0.0,10.0\]:${qcdval} \[0.0,5.0\]:g" $testdir/${cardname} > /tmp/${cardname}
#     sed "s:${value}\s\[0.0,6.0\]:${qcdval} \[0.0,6.0\]:g" $testdir/${cardname} > /tmp/${cardname}
#     mv  /tmp/${cardname} $testdir/${cardname}
# done

# sed "s:qcddd:\#qcddd:g" $testdir/${cardname} > /tmp/${cardname}
# mv  /tmp/${cardname} $testdir/${cardname}

# sed "s:qcdrate:\#qcdrate:g" $testdir/${cardname} > /tmp/${cardname}
# mv  /tmp/${cardname} $testdir/${cardname}

# nuiindex=19
# ${currdir}/listReducedNui.exe ${indir_SR_base}/nuisImpactJSON_${nuiindex}.json ${fnnui} > $testdir/highimnui.txt
# cat $testdir/highimnui.txt

# while read syst 
# do
#     sed "s:^${syst}:\#${syst}:g" $testdir/${cardname} > /tmp/${cardname}
#     mv  /tmp/${cardname} $testdir/${cardname}
# done < $testdir/highimnui.txt

# exclnui=`grep "^#" $testdir/${cardname} | wc -l`
# nofnui=`grep kmax ${testdir}/${cardname} | awk '{print $2}'`
# # modnui=$[$nofnui-$exclnui]
# modnui=$[$nofnui-3]
# sed "s:kmax ${nofnui}:kmax ${modnui}:g" ${testdir}/${cardname} >  /tmp/${cardname}
# mv /tmp/${cardname} $testdir/${cardname}

cd $testdir
pwd
echo "==== END OF COPY ========"

# Copy and combine data card
# combineCards.py ${cardname} >  /tmp/${cardname}
# mv /tmp/${cardname} ${cardname}

# text2workspace.py ${cardname} -P HiggsAnalysis.CombinedLimit.ChargedHiggs:brChargedHiggs -o $wsname 

#cp $indir_SR_base/$wsname .
echo "==== END OF SR and MR WORKSPACES ========"

# # #Calculate the limit in the signal region, later used as injected values for median and +/- 1sigmas
# combine $wsname -M AsymptoticLimits --mass ${mass}
# outfile=limit.txt
# root -l -b -q $basedir/codes/ReadLimit.C\(\""$outfile"\",$mass\)
# cat $outfile
# meanval=`tail -n 1 $outfile | awk '{print $2}'`
# Lval=`head -n 1 $outfile | awk '{print $2}'`
# Hval=`head -n 2 $outfile | tail -n 1 | awk '{print $2}'`
# echo "==== END OF AsymptoticLimits results ========"

minbr=0.0
maxbr=1.0
strategyfit=0
strategyprefit=$[$strategyfit+1]

echo "==== Start of GoF results ========"
combine $wsname -M GoodnessOfFit -m $mass --algo saturated #--redefineSignalPOIs BR --setParameterRanges BR=$minbr,$maxbr
echo "==== END OF GoF results iter1 ========"
combine $wsname -M GoodnessOfFit -m $mass --algo saturated -t $ntoys -n _SRMR_1.${clusproc}.${random} -s ${random} #--redefineSignalPOIs BR --setParameterRanges BR=$minbr,$maxbr --setParameters BR=${meanval}
#--cminDefaultMinimizerStrategy ${strategyfit}  --cminPreScan  --cminPreFit ${strategyprefit} 
echo "==== END OF GoF results iter2 ========"

# cp $outfile $outfile.${clusproc}.${random}

ls -ltr
cd $currdir
