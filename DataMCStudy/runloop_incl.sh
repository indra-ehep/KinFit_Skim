#!/bin/bash

#samples_2016="HplusM120 DataMu DataEle TTbar singleTop Wjets DYjets VBFusion MCQCDMu MCQCDEle"
samples_2017="DataMu DataEle TTbar singleTop Wjets DYjets VBFusion MCQCDMu MCQCDEle"
samples_2018="DataMu DataEle TTbar singleTop Wjets DYjets VBFusion MCQCDMu MCQCDEle"

#samples_2016="TTbar DataMu"
samples_2016="TTbar"
#samples_2016="DataMu DataEle TTbar singleTop Wjets DYjets VBFusion MCQCDMu MCQCDEle"
#samples_2016="TTbar singleTop Wjets DYjets VBFusion MCQCDMu MCQCDEle"
#samples_2016="DYjets"

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
	input=input/ui/${year}/${sample}_incl_${year}.txt #input has to be relative to $basedir
	nofline=`wc -l $input | awk '{print $1}'`
    	ls -la $input
        if [ "${sample}" = "MCQCDMu" ] || [ "${sample}" = "MCQCDEle" ] ; then
            echo workers = 1
    	    time root -l -b -q run.C\(\""sample=$sample|year=$year|input=$input|syst=base|aod=nano|mode=proof|workers=1|run=prod|index=0|trs=no"\"\)
	else
            echo workers = 8
    	    time root -l -b -q run.C\(\""sample=$sample|year=$year|input=$input|syst=base|aod=nano|mode=proof|workers=10|run=prod|index=0|trs=no"\"\)
	fi
	mv ${sample}_bjet_base_1of${nofline}.root root_files/output/${sample}_incl_bjet_base_1of${nofline}.root
	mv ${sample}_tree_base_1of${nofline}.root root_files/output/${sample}_incl_tree_base_1of${nofline}.root
	mv ${sample}_hist_base_1of${nofline}.root root_files/output/${sample}_incl_hist_base_1of${nofline}.root 
    done
    cd $basedir
done
