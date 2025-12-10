#!/bin/bash

mass=$1
year=$2
ch=$3
ch1=mu
ch2=ele

echo "List arguements: "$@
echo "Now processing for $year and channel $ch"

fnnui=$4

basedir=/home/hep/idas/CMS-Analysis/NanoAOD-Analysis/SkimAna/limit
#basedir=/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/limit
#indir_SR_base=$basedir/Imperial-PA-2024-10-08/35_unblinded_MVA_lnNfixed_qcddduncorr_symmetrized/${year}/Comb/${ch}/Cat1_Inc/Mass$mass
indir_SR_base=$basedir/Imperial-PA-2024-10-08/36_unblinded_MVA_lnNfixed_qcddduncorr_nosymm/${year}/Comb/${ch}/Cat1_Inc/Mass$mass

outdir=local/${ch}/Cat1_Inc/Mass$mass
currdir=$PWD

testdir=${currdir}/${outdir}
cardprenom=combine_datacard_hcs_13TeV_${ch}_Cat1_Inc_WH${mass}
cardprenombkp=combine_datacard_hcs_13TeV_${ch}_Cat1_Inc_WH${mass}_bkp
cardname=${cardprenom}.txt
excLcardname=datacard_hcs_13TeV_${ch}___ct_ExcL_mjj_${ch}_WH${mass}_${year}.txt
excMcardname=datacard_hcs_13TeV_${ch}___ct_ExcM_mjj_${ch}_WH${mass}_${year}.txt
excTcardname=datacard_hcs_13TeV_${ch}___ct_ExcT_mjj_${ch}_WH${mass}_${year}.txt
excLcardnamech1=datacard_hcs_13TeV_${ch1}___ct_ExcL_mjj_${ch1}_WH${mass}_${year}.txt
excMcardnamech1=datacard_hcs_13TeV_${ch1}___ct_ExcM_mjj_${ch1}_WH${mass}_${year}.txt
excTcardnamech1=datacard_hcs_13TeV_${ch1}___ct_ExcT_mjj_${ch1}_WH${mass}_${year}.txt
excLcardnamech2=datacard_hcs_13TeV_${ch2}___ct_ExcL_mjj_${ch2}_WH${mass}_${year}.txt
excMcardnamech2=datacard_hcs_13TeV_${ch2}___ct_ExcM_mjj_${ch2}_WH${mass}_${year}.txt
excTcardnamech2=datacard_hcs_13TeV_${ch2}___ct_ExcT_mjj_${ch2}_WH${mass}_${year}.txt
if [ "$year" = "Run2" ]; then
    year1=2016
    excLcardnamech1y1=datacard_hcs_13TeV_${ch1}___ct_ExcL_mjj_${ch1}_WH${mass}_${year1}.txt
    excMcardnamech1y1=datacard_hcs_13TeV_${ch1}___ct_ExcM_mjj_${ch1}_WH${mass}_${year1}.txt
    excTcardnamech1y1=datacard_hcs_13TeV_${ch1}___ct_ExcT_mjj_${ch1}_WH${mass}_${year1}.txt
    excLcardnamech2y1=datacard_hcs_13TeV_${ch2}___ct_ExcL_mjj_${ch2}_WH${mass}_${year1}.txt
    excMcardnamech2y1=datacard_hcs_13TeV_${ch2}___ct_ExcM_mjj_${ch2}_WH${mass}_${year1}.txt
    excTcardnamech2y1=datacard_hcs_13TeV_${ch2}___ct_ExcT_mjj_${ch2}_WH${mass}_${year1}.txt
    year2=2017
    excLcardnamech1y2=datacard_hcs_13TeV_${ch1}___ct_ExcL_mjj_${ch1}_WH${mass}_${year2}.txt
    excMcardnamech1y2=datacard_hcs_13TeV_${ch1}___ct_ExcM_mjj_${ch1}_WH${mass}_${year2}.txt
    excTcardnamech1y2=datacard_hcs_13TeV_${ch1}___ct_ExcT_mjj_${ch1}_WH${mass}_${year2}.txt
    excLcardnamech2y2=datacard_hcs_13TeV_${ch2}___ct_ExcL_mjj_${ch2}_WH${mass}_${year2}.txt
    excMcardnamech2y2=datacard_hcs_13TeV_${ch2}___ct_ExcM_mjj_${ch2}_WH${mass}_${year2}.txt
    excTcardnamech2y2=datacard_hcs_13TeV_${ch2}___ct_ExcT_mjj_${ch2}_WH${mass}_${year2}.txt
    year3=2018
    excLcardnamech1y3=datacard_hcs_13TeV_${ch1}___ct_ExcL_mjj_${ch1}_WH${mass}_${year3}.txt
    excMcardnamech1y3=datacard_hcs_13TeV_${ch1}___ct_ExcM_mjj_${ch1}_WH${mass}_${year3}.txt
    excTcardnamech1y3=datacard_hcs_13TeV_${ch1}___ct_ExcT_mjj_${ch1}_WH${mass}_${year3}.txt
    excLcardnamech2y3=datacard_hcs_13TeV_${ch2}___ct_ExcL_mjj_${ch2}_WH${mass}_${year3}.txt
    excMcardnamech2y3=datacard_hcs_13TeV_${ch2}___ct_ExcM_mjj_${ch2}_WH${mass}_${year3}.txt
    excTcardnamech2y3=datacard_hcs_13TeV_${ch2}___ct_ExcT_mjj_${ch2}_WH${mass}_${year3}.txt
fi

wsname=t2w_${cardprenom}.root
parlistname=parlist.txt
if [ ! -f ${testdir}/${cardprenombkp}.txt ] ; then 
    cp $testdir/$cardname ${testdir}/${cardprenombkp}.txt
    if [ "$ch" = "mu" -o "$ch" = "ele" ]; then
	cp $testdir/$excLcardname ${testdir}/${excLcardname}.bkp 
	cp $testdir/$excMcardname ${testdir}/${excMcardname}.bkp 
	cp $testdir/$excTcardname ${testdir}/${excTcardname}.bkp
    fi
    if [ "$year" != "Run2" -a "$ch" = "mu_ele" ]; then
	cp $testdir/$excLcardnamech1 ${testdir}/${excLcardnamech1}.bkp 
	cp $testdir/$excMcardnamech1 ${testdir}/${excMcardnamech1}.bkp 
	cp $testdir/$excTcardnamech1 ${testdir}/${excTcardnamech1}.bkp 
	cp $testdir/$excLcardnamech2 ${testdir}/${excLcardnamech2}.bkp 
	cp $testdir/$excMcardnamech2 ${testdir}/${excMcardnamech2}.bkp 
	cp $testdir/$excTcardnamech2 ${testdir}/${excTcardnamech2}.bkp
    fi
    if [ "$year" = "Run2" ]; then
	cp $testdir/$excLcardnamech1y1 ${testdir}/${excLcardnamech1y1}.bkp 
	cp $testdir/$excMcardnamech1y1 ${testdir}/${excMcardnamech1y1}.bkp 
	cp $testdir/$excTcardnamech1y1 ${testdir}/${excTcardnamech1y1}.bkp 
	cp $testdir/$excLcardnamech2y1 ${testdir}/${excLcardnamech2y1}.bkp 
	cp $testdir/$excMcardnamech2y1 ${testdir}/${excMcardnamech2y1}.bkp 
	cp $testdir/$excTcardnamech2y1 ${testdir}/${excTcardnamech2y1}.bkp
	cp $testdir/$excLcardnamech1y2 ${testdir}/${excLcardnamech1y2}.bkp 
	cp $testdir/$excMcardnamech1y2 ${testdir}/${excMcardnamech1y2}.bkp 
	cp $testdir/$excTcardnamech1y2 ${testdir}/${excTcardnamech1y2}.bkp 
	cp $testdir/$excLcardnamech2y2 ${testdir}/${excLcardnamech2y2}.bkp 
	cp $testdir/$excMcardnamech2y2 ${testdir}/${excMcardnamech2y2}.bkp 
	cp $testdir/$excTcardnamech2y2 ${testdir}/${excTcardnamech2y2}.bkp
	cp $testdir/$excLcardnamech1y3 ${testdir}/${excLcardnamech1y3}.bkp 
	cp $testdir/$excMcardnamech1y3 ${testdir}/${excMcardnamech1y3}.bkp 
	cp $testdir/$excTcardnamech1y3 ${testdir}/${excTcardnamech1y3}.bkp 
	cp $testdir/$excLcardnamech2y3 ${testdir}/${excLcardnamech2y3}.bkp 
	cp $testdir/$excMcardnamech2y3 ${testdir}/${excMcardnamech2y3}.bkp 
	cp $testdir/$excTcardnamech2y3 ${testdir}/${excTcardnamech2y3}.bkp
    fi
else
    cp ${testdir}/${cardprenombkp}.txt $testdir/$cardname
    if [ "$ch" = "mu" -o "$ch" = "ele" ]; then
	cp ${testdir}/${excLcardname}.bkp $testdir/$excLcardname
	cp ${testdir}/${excMcardname}.bkp $testdir/$excMcardname
	cp ${testdir}/${excTcardname}.bkp $testdir/$excTcardname
    fi
    if [ "$year" != "Run2" -a "$ch" = "mu_ele" ]; then
	cp ${testdir}/${excLcardnamech1}.bkp $testdir/$excLcardnamech1 
	cp ${testdir}/${excMcardnamech1}.bkp $testdir/$excMcardnamech1
	cp ${testdir}/${excTcardnamech1}.bkp $testdir/$excTcardnamech1 
	cp ${testdir}/${excLcardnamech2}.bkp $testdir/$excLcardnamech2 
	cp ${testdir}/${excMcardnamech2}.bkp $testdir/$excMcardnamech2
	cp ${testdir}/${excTcardnamech2}.bkp $testdir/$excTcardnamech2
    fi
    if [ "$year" = "Run2" ]; then
	cp ${testdir}/${excLcardnamech1y1}.bkp $testdir/$excLcardnamech1y1 
	cp ${testdir}/${excMcardnamech1y1}.bkp $testdir/$excMcardnamech1y1
	cp ${testdir}/${excTcardnamech1y1}.bkp $testdir/$excTcardnamech1y1 
	cp ${testdir}/${excLcardnamech2y1}.bkp $testdir/$excLcardnamech2y1 
	cp ${testdir}/${excMcardnamech2y1}.bkp $testdir/$excMcardnamech2y1
	cp ${testdir}/${excTcardnamech2y1}.bkp $testdir/$excTcardnamech2y1
	cp ${testdir}/${excLcardnamech1y2}.bkp $testdir/$excLcardnamech1y2 
	cp ${testdir}/${excMcardnamech1y2}.bkp $testdir/$excMcardnamech1y2
	cp ${testdir}/${excTcardnamech1y2}.bkp $testdir/$excTcardnamech1y2 
	cp ${testdir}/${excLcardnamech2y2}.bkp $testdir/$excLcardnamech2y2 
	cp ${testdir}/${excMcardnamech2y2}.bkp $testdir/$excMcardnamech2y2
	cp ${testdir}/${excTcardnamech2y2}.bkp $testdir/$excTcardnamech2y2
	cp ${testdir}/${excLcardnamech1y3}.bkp $testdir/$excLcardnamech1y3 
	cp ${testdir}/${excMcardnamech1y3}.bkp $testdir/$excMcardnamech1y3
	cp ${testdir}/${excTcardnamech1y3}.bkp $testdir/$excTcardnamech1y3 
	cp ${testdir}/${excLcardnamech2y3}.bkp $testdir/$excLcardnamech2y3 
	cp ${testdir}/${excMcardnamech2y3}.bkp $testdir/$excMcardnamech2y3
	cp ${testdir}/${excTcardnamech2y3}.bkp $testdir/$excTcardnamech2y3
    fi
fi

# sed 's:1.33\ \[0.0,6.0\]:10\ \[0.0,12.0\]:g' $testdir/$cardname > /tmp/$cardname
# mv  /tmp/$cardname $testdir/$cardname

# sed "s:CMS_norm_:\#CMS_norm_:g" $testdir/$cardname > /tmp/$cardname
# mv  /tmp/$cardname $testdir/$cardname

# ${currdir}/listReducedNui.exe ${indir_SR_base} ${fnnui} > $testdir/highimnui.txt
# cat $testdir/highimnui.txt

# while read syst 
# do
#     sed "s:^${syst}:\#${syst}:g" $testdir/$cardname > /tmp/$cardname
#     mv  /tmp/$cardname $testdir/$cardname
# done < $testdir/highimnui.txt

qcdindex=1
#for dcname in $excLcardname $excMcardname $excTcardname
#for dcname in $excLcardnamech1 $excMcardnamech1 $excTcardnamech1 $excLcardnamech2 $excMcardnamech2 $excTcardnamech2
for dcname in $excLcardnamech1y1 $excMcardnamech1y1 $excTcardnamech1y1 $excLcardnamech2y1 $excMcardnamech2y1 $excTcardnamech2y1	$excLcardnamech1y2 $excMcardnamech1y2 $excTcardnamech1y2 $excLcardnamech2y2 $excMcardnamech2y2 $excTcardnamech2y2 $excLcardnamech1y3 $excMcardnamech1y3 $excTcardnamech1y3 $excLcardnamech2y3 $excMcardnamech2y3 $excTcardnamech2y3	      
do
    if [ -f /tmp/$dcname ] ; then
	rm /tmp/$dcname
    fi
    echo Processing for dcname : $dcname
    # #sed 's:\[0.0,6.0\]:\[0.0,20.0\]:g' $testdir/$dcname > /tmp/$dcname
    # sed 's:\[0.0,6.0\]:\[0.0,10.0\]:g' $testdir/$dcname > /tmp/$dcname
    # mv  /tmp/$dcname $testdir/$dcname
    # for syst in qcdrate
    # do
    # 	#sed "s:^${syst}:\#${syst}:g" $testdir/$dcname > /tmp/$dcname
    # 	sed "s:^${syst}:${syst}${qcdindex}:g" $testdir/$dcname > /tmp/$dcname
    # 	mv  /tmp/$dcname $testdir/$dcname
    # done
    qcdindex=$[$qcdindex+1]
    # for syst in reljerec singpiecal pudatamc relfsr relptec2 puptec1 CMS_norm_wjet bcxwjc singpihcal puptec2
    # do
    # 	sed "s:^${syst}:\#${syst}:g" $testdir/$dcname > /tmp/$dcname
    # 	mv  /tmp/$dcname $testdir/$dcname
    # done
    # for syst in absmpfb CMS_norm_tt bclhemur bclhemuf pudatamc isr frag relbal absstat2016 CMS_pdf_ hDamp_tt flavorqcd singpiecal bcxdyb CMS_eff_m_ CMS_lumi_16 absscl CMS_prefire
    # do
    # 	echo Excluding nuisance : $syst
    # 	sed "s:^${syst}:\#${syst}:g" $testdir/$dcname > /tmp/$dcname
    # 	mv  /tmp/$dcname $testdir/$dcname
    # done
done

# for dcname in $excLcardnamech1y1 $excMcardnamech1y1 $excTcardnamech1y1 $excLcardnamech2y1 $excMcardnamech2y1 $excTcardnamech2y1
# do
#     for syst in qcdrate
#     do
# 	sed "s:^${syst}:${syst}${year1}:g" $testdir/$dcname > /tmp/$dcname
# 	mv  /tmp/$dcname $testdir/$dcname
#     done
# done
# for dcname in $excLcardnamech1y2 $excMcardnamech1y2 $excTcardnamech1y2 $excLcardnamech2y2 $excMcardnamech2y2 $excTcardnamech2y2
# do
#     for syst in qcdrate
#     do
# 	sed "s:^${syst}:${syst}${year2}:g" $testdir/$dcname > /tmp/$dcname
# 	mv  /tmp/$dcname $testdir/$dcname
#     done
# done
# for dcname in $excLcardnamech1y3 $excMcardnamech1y3 $excTcardnamech1y3 $excLcardnamech2y3 $excMcardnamech2y3 $excTcardnamech2y3
# do
#     for syst in qcdrate
#     do
# 	sed "s:^${syst}:${syst}${year3}:g" $testdir/$dcname > /tmp/$dcname
# 	mv  /tmp/$dcname $testdir/$dcname
#     done
# done
    


# while read syst 
# do
#     sed "s:^${syst}:\#${syst}:g" $testdir/$cardname > /tmp/$cardname
#     mv  /tmp/$cardname $testdir/$cardname
# done < $testdir/highimnui.txt

# exclnui=`grep "^#" $testdir/$cardname | wc -l`
# nofnui=`grep kmax $testdir/$cardname | awk '{print $2}'`
# echo "exclnui: " $exclnui
# echo "nofnui: " $nofnui

# modnui=$[$nofnui-$exclnui]
# modnui=$[$modnui+3]
# sed "s:kmax ${nofnui}:kmax ${modnui}:g" $testdir/$cardname > /tmp/$cardname
# mv  /tmp/$cardname $testdir/$cardname

cd $testdir
pwd
echo "==== END OF COPY ========"

# #combineCards.py $excLcardname $excMcardname $excTcardname > $cardname
# #combineCards.py $excLcardname > $cardname
# #combineCards.py $excLcardnamech1 $excLcardnamech2  $excMcardnamech1 $excMcardnamech2  $excTcardnamech1 $excTcardnamech2  > $cardname
# combineCards.py $excLcardnamech1y1 $excLcardnamech2y1  $excMcardnamech1y1 $excMcardnamech2y1  $excTcardnamech1y1 $excTcardnamech2y1 $excLcardnamech1y2 $excLcardnamech2y2  $excMcardnamech1y2 $excMcardnamech2y2  $excTcardnamech1y2 $excTcardnamech2y2 $excLcardnamech1y3 $excLcardnamech2y3  $excMcardnamech1y3 $excMcardnamech2y3  $excTcardnamech1y3 $excTcardnamech2y3   > $cardname

# #index=230
# # index_freeze=19
# # grep "Missing inputs:"  doNui_json_${index_freeze}.log | cut -f 2 -d ':' | tr , '\n' > /tmp/fl_${index}.txt
# # nfreezepara=0
# # while read line
# # do
# #     if [[ $line != "prop_binch"* ]] && [[ $line != "qcdrate"* ]] ; then
# # 	nfreezepara=$[$nfreezepara+1]
# #     fi
# # done < /tmp/fl_${index}.txt
# # echo nfreezepara : $nfreezepara

# # iar=0
# # unset array
# # declare -a array
# # while read line
# # do
# #     if [[ $line != "prop_binch"* ]] && [[ $line != "qcdrate"* ]] ; then
# # 	if [ $iar -lt $[$nfreezepara-1] ] ; then
# # 	    array[$iar]=$line,
# # 	else
# # 	    array[$iar]=$line
# # 	fi
# # 	iar=$[$iar+1]
# # 	sed "s:^${line}:\#${line}:g" $cardname > /tmp/$cardname
# # 	mv  /tmp/$cardname $cardname
# #     fi
# # done < /tmp/fl_${index}.txt
# # freezepara=`echo ${array[@]} | sed 's/, /,/g'`
# # echo freezepara : $freezepara

# # exclnui=`grep "^#" $cardname | wc -l`
# # nofnui=`grep kmax $cardname | awk '{print $2}'`
# # modnui=$[$nofnui-$exclnui]
# # sed "s:kmax ${nofnui}:kmax ${modnui}:g" $cardname >  /tmp/$cardname
# # mv /tmp/$cardname $cardname

# rm $wsname
# text2workspace.py $cardname -P HiggsAnalysis.CombinedLimit.ChargedHiggs:brChargedHiggs -o $wsname
echo "==== END OF SR and MR WORKSPACES ========"


extraarginifit="--cminPreFit 3 "
# if [ "$mass" = "80" ]; then
#     extraarginifit="--robustFit 1"
# fi
minbr=-2.0
maxbr=2.0
# if [ "$mass" = "150" ]; then
#     minbr=-0.1
#     maxbr=0.1
# fi
strategy=0
strategyfit=0
strategyprefit=$[$strategyfit+1]
index=23

## Impact plots #####################
# rm *.MultiDimFit.*
# rm nuisImpactJSON nuisImpactPDF.pdf
# combine -M MultiDimFit -d ${wsname} --redefineSignalPOIs BR $extraarginifit --setParameterRanges BR=$minbr,$maxbr --algo singles --cl=0.68 --cminDefaultMinimizerStrategy ${strategy} 
# combineTool.py -M Impacts -d ${wsname} -m $mass --doInitialFit $extraarginifit --redefineSignalPOIs BR --setParameterRanges BR=$minbr,$maxbr --cminDefaultMinimizerStrategy ${strategy}  > doInitialFit.log 2>&1
# #if [ $nfreezepara -gt 0 ]  ; then
#combineTool.py -M Impacts -d ${wsname} -m $mass --doFit --freezeParameters ${freezepara} --robustFit 1 --redefineSignalPOIs BR --setParameterRanges BR=$minbr,$maxbr --cminDefaultMinimizerStrategy ${strategyfit} --maxFailedSteps 20 --parallel 32  --cminPoiOnlyFit --cminPreScan  --cminPreFit ${strategyprefit}   > doFit_updatedtolerances_${index}.log  2>&1
combineTool.py -M Impacts -d ${wsname} -m $mass --doFit --robustFit 1 --redefineSignalPOIs BR --setParameterRanges BR=$minbr,$maxbr --cminDefaultMinimizerStrategy ${strategyfit} --maxFailedSteps 20 --parallel 32  --cminPoiOnlyFit --cminPreScan  --cminPreFit ${strategyprefit}   > doFit_updatedtolerances_${index}.log  2>&1
combineTool.py -M Impacts -d ${wsname} -m $mass -o nuisImpactJSON > doNui_json_${index}.log  2>&1
cp nuisImpactJSON nuisImpactJSON_${index}.json
plotImpacts.py --blind --cms-label "Internal" -i nuisImpactJSON -o nuisImpactPDF > doNui_pdf_${index}.log  2>&1
cp nuisImpactPDF.pdf nuisImpactPDF_${ch}_${mass}_minstrat-${strategy}_range\(${minbr}-${maxbr}\)_newtolarances_${index}.pdf
# #fi
# # rm *.MultiDimFit.*
####################################
# # 1D parameter scan
#para=puptec2
# combine -M MultiDimFit -d t2w_combine_datacard_hcs_13TeV_mu_Cat1_Inc_WH80.root -m 80 --redefineSignalPOIs BR --setParameterRanges BR=0.0,1.0 -P $para --trackParameters BR --algo=grid --points 100 --name .${para} --floatOtherPOIs 1
# plot1DScan.py higgsCombine.${para}.MultiDimFit.mH80.root --POI $para
####################################

# grep " shape " $testdir/$cardname | awk '{print $1}' > $testdir/$parlistname
# grep " lnN " $testdir/$cardname | awk '{print $1}' >> $testdir/$parlistname

# while read parname
# do
#     echo "Scanning for parameter : $parname"
#     #combine ${wsname} -M MultiDimFit -m $mass --redefineSignalPOIs BR --setParameterRanges BR=-1.,1. -P $parname  --trackParameters BR --algo grid --name _scan_$parname
#     combine ${wsname} -M MultiDimFit -m $mass --redefineSignalPOIs BR --setParameterRanges BR=-2.,2. -t -1 -P $parname  --trackParameters BR --algo grid --name _scan_$parname
# done < $testdir/$parlistname

# # #Calculate the limit in the signal region, later used as injected values for median and +/- 1sigmas
# # if [ -f ${condorOutDir1}/${outdir}/limit.txt ] ; then
# #     cp ${condorOutDir1}/${outdir}/limit.txt .
# # else
# #     combine --run blind --rAbsAcc 0.000001 datacard_SR_WH${mass}.root -M AsymptoticLimits --mass ${mass}
# # fi
# # outfile=limit.txt
# # root -l -b -q $basedir/codes/ReadLimit.C\(\""$outfile"\",$mass\)
# # cat $outfile
# # meanval=`tail -n 1 $outfile | awk '{print $2}'`
# # Lval=`head -n 1 $outfile | awk '{print $2}'`
# # Hval=`head -n 2 $outfile | tail -n 1 | awk '{print $2}'`
# # echo "==== END OF AsymptoticLimits results ========"


#ls -ltr
cd $currdir
