#!/bin/bash

#samples_2016="HplusM120 DataMu DataEle TTbar singleTop Wjets DYjets VBFusion MCQCDMu MCQCDEle"
samples_2017="DataMu DataEle TTbar singleTop Wjets DYjets VBFusion MCQCDMu MCQCDEle"
samples_2018="DataMu DataEle TTbar singleTop Wjets DYjets VBFusion MCQCDMu MCQCDEle"

samples_2016="TTbar DataMu"

#years="2016 2017 2018"
years="2016"

basedir=`pwd`

time root -l -b -q compile.C

last_proc_stat=`echo $?`
echo Status of last process ${last_proc_stat}

for year in $years 
do
    samples=samples_$year
    echo year : $year samples : ${!samples}
    echo basedir : $basedir
    for sample in ${!samples}
    do
	####################### Pre #############################
	input=input/lnx3/${year}/pre/${sample}_${year}.txt #input has to be relative to $basedir
	nofline=`wc -l $input | awk '{print $1}'`
    	ls -la $input
        if [ "${sample}" = "MCQCDMu" ] || [ "${sample}" = "MCQCDEle" ] ; then
            echo workers = 1
    	    time root -l -b -q run.C\(\""sample=$sample|year=$year|input=$input|syst=base|aod=nano|mode=proof|workers=1|run=prod|index=0|trs=no"\"\)
	else
            echo workers = 8
    	    time root -l -b -q run.C\(\""sample=$sample|year=$year|input=$input|syst=base|aod=nano|mode=proof|workers=8|run=prod|index=0|trs=no"\"\)
	fi
	mv ${sample}_bjet_base_1of${nofline}.root root_files/output/${sample}_pre_bjet_base_1of${nofline}.root
	mv ${sample}_tree_base_1of${nofline}.root root_files/output/${sample}_pre_tree_base_1of${nofline}.root
	mv ${sample}_hist_base_1of${nofline}.root root_files/output/${sample}_pre_hist_base_1of${nofline}.root 
	####################### Post #############################
	input=input/lnx3/${year}/post/${sample}_${year}.txt #input has to be relative to $basedir
	nofline=`wc -l $input | awk '{print $1}'`
    	ls -la $input
        if [ "${sample}" = "MCQCDMu" ] || [ "${sample}" = "MCQCDEle" ] ; then
            echo workers = 1
    	    time root -l -b -q run.C\(\""sample=$sample|year=$year|input=$input|syst=base|aod=nano|mode=proof|workers=1|run=prod|index=0|trs=no"\"\)
	else
            echo workers = 8
    	    time root -l -b -q run.C\(\""sample=$sample|year=$year|input=$input|syst=base|aod=nano|mode=proof|workers=8|run=prod|index=0|trs=no"\"\)
	fi
	mv ${sample}_bjet_base_1of${nofline}.root root_files/output/${sample}_post_bjet_base_1of${nofline}.root
	mv ${sample}_tree_base_1of${nofline}.root root_files/output/${sample}_post_tree_base_1of${nofline}.root
	mv ${sample}_hist_base_1of${nofline}.root root_files/output/${sample}_post_hist_base_1of${nofline}.root 
    done
    cd $basedir
done
