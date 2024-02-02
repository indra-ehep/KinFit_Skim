#!/bin/bash

#/**********************************************************************
#  Created on : 22/10/2021
#  Purpose    : Add systematics histos
#  Author     : Indranil Das, Visiting Fellow
#  Email      : indranil.das@cern.ch | indra.ehep@gmail.com
# **********************************************************************/

#samples_2016="TTbar DataMu DataEle HplusM040 HplusM050 HplusM060 HplusM070 HplusM080 HplusM090 HplusM100 HplusM110 HplusM120 HplusM130 HplusM140 HplusM150 HplusM155 HplusM160 HminusM040 HminusM050 HminusM060 HminusM070 HminusM080 HminusM090 HminusM100 HminusM110 HminusM120 HminusM130 HminusM140 HminusM150 HminusM155 HminusM160 singleTop Wjets DYjets VBFusion MCQCDMu MCQCDEle TTGToLL TTGToLNu TTGToQQ TTHToNonbb TTHTobb TTHToGG TTWJetsToLNu TTWJetsToQQ TTZToLLNuNu TTZToQQ"
#samples_2016="DataMu DataEle HplusM050 HplusM060 HplusM070 HplusM080 HplusM090 HplusM100 HplusM110 HplusM120 HplusM130 HplusM140 HplusM150 HplusM155 HplusM160 HminusM040 HminusM050 HminusM060 HminusM070 HminusM080 HminusM090 HminusM100 HminusM110 HminusM120 HminusM130 HminusM140 HminusM150 HminusM155 HminusM160 singleTop Wjets VBFusion MCQCDMu MCQCDEle"

samples_2016="TTbar DYjets TTGToLL TTGToLNu TTGToQQ TTHToNonbb TTHToGG TTWJetsToLNu TTWJetsToQQ TTZToLLNuNu TTZToQQ"
#samples_2016="TTHTobb"

#syst_2016="base jecup jecdown jerup jerdown iso20 metup metdown cp5up cp5down hdampup hdampdown mtopup mtopdown stotpuup stotpudown stotrelup stotreldown stotptup stotptdown stotscaleup stotscaledown flavorqcdup flavorqcddown timeptetaup timeptetadown"
syst_2016="base iso20 metup metdown cp5up cp5down hdampup hdampdown mtopup mtopdown absmpfbup abssclup absstatup flavorqcdup fragup timeptetaup pudatamcup puptbbup puptec1up puptec2up pupthfup puptrefup relfsrup relbalup relsampleup reljerec1up reljerec2up reljerhfup relptbbup relptec1up relptec2up relpthfup relstatecup relstatfsrup relstathfup singpiecalup singpihcalup absmpfbdown absscldown absstatdown flavorqcddown fragdown timeptetadown pudatamcdown puptbbdown puptec1down puptec2down pupthfdown puptrefdown relfsrdown relbaldown relsampledown reljerec1down reljerec2down reljerhfdown relptbbdown relptec1down relptec2down relpthfdown relstatecdown relstatfsrdown relstathfdown singpiecaldown singpihcaldown"

declare -A tunedict
tunedict["cp5up"]="CP5up_TTbar"
tunedict["cp5down"]="CP5down_TTbar"
tunedict["hdampup"]="hdampup_TTbar"
tunedict["hdampdown"]="hdampdown_TTbar"
tunedict["mtopup"]="mtopup_TTbar"
tunedict["mtopdown"]="mtopdown_TTbar"

syst_base="base iso20"
#syst_base="base"

#inputdir="/eos/user/i/idas/Output/cms-hcs-run2/CBA_elereliso20/pre"
#inputdir="/eos/user/i/idas/Output/cms-hcs-run2/CBA_elemva90/pre"
#inputdir="/eos/user/i/idas/Output/cms-hcs-run2/CBA_jetpt15/pre"
#inputdir="/eos/user/i/idas/Output/cms-hcs-run2/CBA_lowjetpt-highmet/pre"
#inputdir="/eos/user/i/idas/Output/cms-hcs-run2/CBA_lowmass/pre"
inputdir="/eos/user/i/idas/Output/cms-hcs-run2/CBA_jecsyst/pre"
#inputdir="/eos/user/d/dugad/idas/Output/cms-hcs-run2/CBA_elereliso20-BJetHist1/pre"
#inputdir="/eos/user/d/dugad/idas/Output/cms-hcs-run2/CBA_elereliso30-BJetHist1/pre"
#inputdir="/eos/user/d/dugad/idas/Output/cms-hcs-run2/CBA_mutight-BJetHist1/pre"
#inputdir="/eos/user/d/dugad/idas/Output/cms-hcs-run2/CBA_elemva90-BJetHist1/pre"
#inputdir="/eos/user/d/dugad/idas/Output/cms-hcs-run2/CBA_lowmass-BJetHist1/pre"
#inputdir="/eos/user/a/anayak/HplusAnalysisRun2/idas/Output/cms-hcs-run2/CBA_mutight-Hist1/pre"
#inputdir="/eos/cms/store/group/phys_b2g/idas/Output/cms-hcs-run2/Result/CBA_jetpt15-lowptheta-Hist1/pre"
#inputdir="/eos/cms/store/group/phys_b2g/idas/Output/cms-hcs-run2/Result/CBA_jetpt15-ptcut25-Hist1/pre"
# inputdir="/eos/cms/store/group/phys_b2g/idas/Output/cms-hcs-run2/Result/CBA_lowmass-Hist1/pre"
skimflistdir="/afs/cern.ch/user/i/$USER/CMS-Analysis/NanoAOD-Analysis/CBA_Skim/input/eos"

years="2016"
#years="2016"

basedir=`pwd`
for year in $years
do
    # noffiles=`ls $inputdir/$year/*.root  | wc -l`
    # echo total number of files $noffiles
    samples=samples_$year
    echo year : $year samples : ${!samples}
    echo inputdir : $inputdir
    if [ -f /tmp/$USER/missing_${year}.txt ] ; then
	rm /tmp/$USER/missing_${year}.txt
    fi
    for sample in ${!samples}
    do
	systs=""
	if [[ $sample == *"Data"* ]]; then
	    echo "It's there!" $sample
	    systs=syst_base
	else
	    echo "Sample is " $sample
	    systs=syst_$year
	fi
	for syst in ${!systs}
	do
	    noffiles=`ls $inputdir/$year/${sample}_hist_${syst}*.root 2>/dev/null | wc -l`
	    flist=`ls $inputdir/$year/${sample}_hist_${syst}*.root  2>/dev/null `
	    #echo -e "\t ${syst} has nof files ${noffiles}"
	    if [ -f /tmp/$USER/fl.txt ] ; then
	        rm /tmp/$USER/fl.txt
	    fi
	    if [ ! -d $inputdir/$year/syst ] ; then
		mkdir $inputdir/$year/syst
	    fi
	    for file in ${flist} ; do
		echo -e "\t ${file}" >> /tmp/$USER/fl.txt
	    done
	    echo -e "Adding files for sample: ${sample} and syst ${syst}"
	    if [[ ${syst} == "cp5"* ]] || [[ ${syst} == "hdamp"* ]]  || [[ ${syst} == "mtop"* ]] ; then
		if [[ $sample == *"TTbar"* ]]; then
		    #sh ~/scripts/addhisto_file.sh /tmp/$USER/fl.txt | tee /tmp/$USER/out.log 2>&1
		    sh ~/scripts/addhisto_file.sh /tmp/$USER/fl.txt > /tmp/$USER/out.log 2>&1
		    mv histo_merged.root $inputdir/$year/syst/${sample}_syst-${syst}.root
		    #expected_noffiles=`wc -l $skimflistdir/$year/${tunedict[$syst]}_${year}.txt | cut -f 1 -d " "`
		    expected_noffiles=`wc -l $skimflistdir/$year/pre/${tunedict[$syst]}_${year}.txt | cut -f 1 -d " "`
		else
		    expected_noffiles=0
		fi
	    else
		#sh ~/scripts/addhisto_file.sh /tmp/$USER/fl.txt | tee  /tmp/$USER/out.log 2>&1
		sh ~/scripts/addhisto_file.sh /tmp/$USER/fl.txt > /tmp/$USER/out.log 2>&1
		mv histo_merged.root $inputdir/$year/syst/${sample}_syst-${syst}.root
		#expected_noffiles=`wc -l $skimflistdir/$year/${sample}_${year}.txt | cut -f 1 -d " "`
		expected_noffiles=`wc -l $skimflistdir/$year/pre/${sample}_${year}.txt | cut -f 1 -d " "`
	    fi
	    echo -e "sample : ${sample} | syst : ${syst} | expected : ${expected_noffiles} | found : $noffiles"

	    diff=`echo "${expected_noffiles} - ${noffiles}" | bc -l`
	    if [ $diff -gt 0 ] ; then
		echo Nof missing files : $diff for syst : ${syst}
		for imiss in `seq 1 ${expected_noffiles}`
		do
		    if [ ! -f $inputdir/$year/${sample}_hist_${syst}_${imiss}of${expected_noffiles}.root ] ; then
			echo File : $inputdir/$year/${sample}_hist_${syst}_${imiss}of${expected_noffiles}.root is missing.
			ifindex=$[$imiss-1]
			# Arguments  = 2017 TTbar input/eos/2017/TTbar_2017.txt $INT(X) jecup 
			#echo "Arguments  = $year ${sample} input/eos/$year/${sample}_${year}.txt $ifindex $syst" >> /tmp/$USER/missing_${year}.txt
			echo "Arguments  = $year ${sample} input/eos/$year/pre/${sample}_${year}.txt $ifindex $syst" >> /tmp/$USER/missing_${year}_pre.txt
			echo "" >> /tmp/$USER/missing_${year}.txt
		    fi
		done
	    fi
	done

	flist=`ls $inputdir/$year/syst/${sample}_syst-*.root`
	if [ -f /tmp/$USER/fl.txt ] ; then
	    rm /tmp/$USER/fl.txt
	fi
	if [ ! -d $inputdir/$year/all ] ; then
	    mkdir $inputdir/$year/all
	fi
	for file in ${flist} ; do
	    echo -e "\t ${file}" >> /tmp/$USER/fl.txt
	done
	echo -e "Adding files for sample ${sample}"
	#sh ~/scripts/addhisto_file.sh /tmp/$USER/fl.txt | tee /tmp/$USER/out.log 2>&1
	sh ~/scripts/addhisto_file.sh /tmp/$USER/fl.txt > /tmp/$USER/out.log 2>&1
	cp histo_merged.root $inputdir/$year/all/all_${sample}.root
	mv histo_merged.root /tmp/$USER/all_${sample}.root	
    done
    if [ -f /tmp/$USER/missing_${year}.txt ] ; then
	noflines=`wc -l /tmp/$USER/missing_${year}.txt`
	if [ $noflines -gt 0 ] ; then
	    echo "See the input aruments for jdl files at /tmp/$USER/missing_${year}.txt"
	fi
    fi
done
