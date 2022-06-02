#!/bin/bash

inputdir=/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v39_Syst/CBA_CTagDD

years="2017 2018"

for year in $years
do
    for mass in 080 090 100 110 120 130 140 150 155 160 
    do
	echo Processing for year $year and mass $mass
	root -l -q -b codes/ModifyTopDirName.C\(\""$inputdir/$year/all_HplusM${mass}.root"\",\""HplusM${mass}"\",\""HplmiM${mass}_1.root"\",\""HplmiM${mass}"\"\) > /tmp/out.log 2>&1
	root -l -q -b codes/ModifyTopDirName.C\(\""$inputdir/$year/all_HminusM${mass}.root"\",\""HminusM${mass}"\",\""HplmiM${mass}_2.root"\",\""HplmiM${mass}"\"\) >> /tmp/out.log 2>&1
	hadd HplmiM${mass}.root HplmiM${mass}_1.root HplmiM${mass}_2.root >> /tmp/out.log 2>&1
	rm HplmiM${mass}_1.root HplmiM${mass}_2.root
	mv HplmiM${mass}.root $inputdir/$year/all_HplmiM${mass}.root
    done
done
