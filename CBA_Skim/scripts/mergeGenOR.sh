#!/bin/bash

basedir=$PWD

#inputdir=$basedir/root_files/grid_v40_Syst/CBA_genOR
#inputdir=$basedir/root_files/grid_v40_Syst/CBA_genOR-BJetHist
#inputdir=$basedir/root_files/grid_v40_Syst/CBA_genOR-Hist
#inputdir=$basedir/root_files/grid_v40_Syst/CBA_genOR-CombHist
#inputdir=$basedir/root_files/grid_v40_Syst/CBA_jecsyst
#inputdir=$basedir/root_files/grid_v40_Syst/CBA_jecsyst-CombHist
#inputdir=$basedir/root_files/grid_v40_Syst/CBA_metxycorr
#inputdir=$basedir/root_files/grid_v40_Syst/CBA_metxycorr-CombHist
#inputdir=$basedir/root_files/grid_v40_Syst/CBA_metxycorr-MCScale2
#inputdir=$basedir/root_files/grid_v40_Syst/CBA_metxycorr-MCScale4
inputdir=$basedir/root_files/QCDRBI

#years="2016 2017 2018"
#years="2018"
years="2016 2017 2018"

for year in $years
do
    fname=/tmp/fl_$(date +%Y-%m-%d__%H%M%S).txt

    #TTG
    if [ -f $fname ] ; then 
    	rm $fname
    fi
    for sample in TTGToLL TTGToLNu TTGToQQ
    do
    	echo Processing for sample : $sample
	find $inputdir/$year/ -name "*${sample}*.root" >> $fname
    done
    source ~/scripts/addhisto_file.sh $fname
    mv histo_merged.root $inputdir/$year/IsoMET_QCD_TTG_${year}.root
    while read filename
    do
	echo filename : $filename
	rm $filename
    done < $fname
    cat $fname
    
    #TTH
    if [ -f $fname ] ; then 
    	rm $fname
    fi
    for sample in TTHToGG TTHToNonbb TTHTobb
    do
    	echo Processing for sample : $sample
	find $inputdir/$year/ -name "*${sample}*.root" >> $fname
    done
    source ~/scripts/addhisto_file.sh $fname
    mv histo_merged.root $inputdir/$year/IsoMET_QCD_TTH_${year}.root
    while read filename
    do
	echo filename : $filename
	rm $filename
    done < $fname
    cat $fname


    #TTW
    if [ -f $fname ] ; then 
    	rm $fname
    fi
    for sample in TTWJetsToLNu TTWJetsToQQ
    do
    	echo Processing for sample : $sample
	find $inputdir/$year/ -name "*${sample}*.root" >> $fname
    done
    source ~/scripts/addhisto_file.sh $fname
    mv histo_merged.root $inputdir/$year/IsoMET_QCD_TTW_${year}.root
    while read filename
    do
	echo filename : $filename
	rm $filename
    done < $fname
    cat $fname
    

    #TTZ
    if [ -f $fname ] ; then 
    	rm $fname
    fi
    for sample in TTZToLLNuNu TTZToQQ
    do
    	echo Processing for sample : $sample
	find $inputdir/$year/ -name "*${sample}*.root" >> $fname
    done
    source ~/scripts/addhisto_file.sh $fname
    mv histo_merged.root $inputdir/$year/IsoMET_QCD_TTZ_${year}.root
    while read filename
    do
	echo filename : $filename
	rm $filename
    done < $fname
    cat $fname

    rm $fname
done

# Alternatively one can use commands like below to fuse the files
# rootcp all_HplusM080.root:HplusM080 /tmp/all_HplusM080.root:HplmiM080
# rootcp all_HminuM080.root:HminusM080 /tmp/all_HminusM080.root:HplmiM080
# hadd all_HplmiM080.root /tmp/all_HplusM080.root /tmp/all_HminusM080.root
