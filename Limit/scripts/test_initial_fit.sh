#!/bin/bash

mass=$1
year=$2
ch=$3
# injpoint=$4
# rundir=$5
# random=$6
# clusproc=$7
# condorOutDir1=$8

echo "List arguements: "$@

ntoys=50
fnnui=$4

basedir=/home/hep/idas/CMS-Analysis/NanoAOD-Analysis/SkimAna/limit
indir_SR_base=$basedir/Imperial-PA-2024-10-08/10_mixed_MVA_lnNfixed/${year}/Comb/${ch}/Cat1_Inc/Mass$mass

outdir=local/${ch}/Cat1_Inc/Mass$mass
currdir=$PWD

testdir=${currdir}/${outdir}
cardprenom=combine_datacard_hcs_13TeV_${ch}_Cat1_Inc_WH${mass}
cardprenombkp=combine_datacard_hcs_13TeV_${ch}_Cat1_Inc_WH${mass}_bkp
cardname=${cardprenom}.txt
wsname=${cardprenom}.root

# The following lines are to remove the bound of qcdrate
if [ -f ${testdir}/${cardprenombkp}.txt ] ; then 
    cp ${testdir}/${cardprenombkp}.txt $testdir/$cardname
else
    cp $testdir/$cardname ${testdir}/${cardprenombkp}.txt
fi

sed 's:\[0.0,6.0\]::g' $testdir/$cardname > /tmp/$cardname
mv  /tmp/$cardname $testdir/$cardname

${currdir}/listReducedNui.exe ${indir_SR_base} ${fnnui} > $testdir/highimnui.txt
cat $testdir/highimnui.txt

while read syst 
do
    sed "s:^${syst}:\#${syst}:g" $testdir/$cardname > /tmp/$cardname
    mv  /tmp/$cardname $testdir/$cardname
    
done < $testdir/highimnui.txt

exclnui=`grep "^#" $testdir/$cardname | wc -l`
nofnui=`grep kmax $testdir/$cardname | awk '{print $2}'`
modnui=$[$nofnui-$exclnui]
sed "s:kmax ${nofnui}:kmax ${modnui}:g" $testdir/$cardname > /tmp/$cardname
mv  /tmp/$cardname $testdir/$cardname

cd $testdir
pwd
echo "==== END OF COPY ========"

text2workspace.py $cardname -P HiggsAnalysis.CombinedLimit.ChargedHiggs:brChargedHiggs
echo "==== END OF SR and MR WORKSPACES ========"

combineTool.py -M Impacts -d ${wsname} -m ${mass} --doInitialFit --robustFit 1 --redefineSignalPOIs BR --setParameterRanges BR=-2.0,2.0  --cminDefaultMinimizerStrategy 0

# #Calculate the limit in the signal region, later used as injected values for median and +/- 1sigmas
# if [ -f ${condorOutDir1}/${outdir}/limit.txt ] ; then
#     cp ${condorOutDir1}/${outdir}/limit.txt .
# else
#     combine --run blind --rAbsAcc 0.000001 datacard_SR_WH${mass}.root -M AsymptoticLimits --mass ${mass}
# fi
# outfile=limit.txt
# root -l -b -q $basedir/codes/ReadLimit.C\(\""$outfile"\",$mass\)
# cat $outfile
# meanval=`tail -n 1 $outfile | awk '{print $2}'`
# Lval=`head -n 1 $outfile | awk '{print $2}'`
# Hval=`head -n 2 $outfile | tail -n 1 | awk '{print $2}'`
# echo "==== END OF AsymptoticLimits results ========"


#ls -ltr
cd $currdir
