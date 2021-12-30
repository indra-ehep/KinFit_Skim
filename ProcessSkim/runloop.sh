#!/bin/bash

# samples_2016="HplusM120 TTbar singleTop Wjets DYjets VBFusion MCQCDMu MCQCDEle"
# samples_2017="TTbar singleTop Wjets DYjets VBFusion MCQCDMu MCQCDEle"
# samples_2018="TTbar singleTop Wjets DYjets VBFusion MCQCDMu MCQCDEle"
#samples="TTbar"
samples_2016="TTbar singleTop Wjets DYjets VBFusion MCQCDMu MCQCDEle HplusM080 HplusM090 HplusM100 HplusM110 HplusM120 HplusM130 HplusM140 HplusM150 HplusM155 HplusM160 HminusM080 HminusM090 HminusM100 HminusM110 HminusM120 HminusM130 HminusM140 HminusM150 HminusM155 HminusM160"
#years="2016 2017 2018"
years="2016"

for year in $years 
do
    samples=samples_$year
    echo samples : ${!samples}
    for sample in ${!samples}
    do
	#input=input/${sample}_${year}.txt
	#input=../SkimAna/input/eos/$year/${sample}_${year}.txt
	input=../CBA_Skim/input/eos/$year/${sample}_${year}.txt
	#input=../SkimAna/input/inlap/$year/${sample}_${year}.txt
	ls -la $input
	root -l -b -q run.C\(\""sample=$sample|year=$year|input=$input|run=prod|mode=proof|workers=8"\"\)
	#root -l -b -q run.C\(\""sample=$sample|year=$year|input=$input|run=prod|mode=proof|workers=3"\"\)
    done
done
