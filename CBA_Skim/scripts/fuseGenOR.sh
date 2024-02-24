#!/bin/bash

basedir=$PWD

#inputdir=$basedir/root_files/grid_v40_Syst/CBA_genOR
#inputdir=$basedir/root_files/grid_v40_Syst/CBA_genOR-BJetHist
#inputdir=$basedir/root_files/grid_v40_Syst/CBA_genOR-Hist
#inputdir=$basedir/root_files/grid_v40_Syst/CBA_genOR-CombHist
#inputdir=$basedir/root_files/grid_v40_Syst/CBA_jecsyst
inputdir=$basedir/root_files/grid_v40_Syst/CBA_jecsyst-CombHist
#inputdir=$basedir/root_files/grid_v40_Syst/CBA_metxycorr
#inputdir=$basedir/root_files/grid_v40_Syst/CBA_metxycorr-CombHist


#years="2016 2017 2018"
years="2018"
#years="2016 2017"

for year in $years
do
    fname=/tmp/fl_$(date +%Y-%m-%d__%H%M%S).txt

    # #triboson
    # if [ -f $fname ] ; then 
    # 	rm $fname
    # fi
    # for sample in WWG WWW WWZ WZG WZZ ZZZ
    # do
    # 	echo Processing for sample : $sample
    # 	root -l -q -b codes/ModifyTopDirName.C\(\""$inputdir/$year/all_${sample}.root"\",\""${sample}"\",\""${sample}_1.root"\",\""triboson"\"\) > /tmp/out.log 2>&1
    # 	echo $PWD/${sample}_1.root >> $fname
    # done
    # source ~/scripts/addhisto_file.sh $fname
    # for sample in WWG WWW WWZ WZG WZZ ZZZ
    # do
    # 	rm ${sample}_1.root 
    # done
    # mv histo_merged.root $inputdir/$year/all_triboson.root
    # cat $fname

    # #VH
    # if [ -f $fname ] ; then 
    # 	rm $fname
    # fi
    # for sample in VHToEE VHToGG VHToNonbb
    # do
    # 	echo Processing for sample : $sample
    # 	root -l -q -b codes/ModifyTopDirName.C\(\""$inputdir/$year/all_${sample}.root"\",\""${sample}"\",\""${sample}_1.root"\",\""VH"\"\) > /tmp/out.log 2>&1
    # 	echo $PWD/${sample}_1.root >> $fname
    # done
    # source ~/scripts/addhisto_file.sh $fname
    # for sample in VHToEE VHToGG VHToNonbb
    # do
    # 	rm ${sample}_1.root 
    # done
    # mv histo_merged.root $inputdir/$year/all_VH.root
    # cat $fname

    #TTG
    if [ -f $fname ] ; then 
    	rm $fname
    fi
    for sample in TTGToLL TTGToLNu TTGToQQ
    do
    	echo Processing for sample : $sample
    	root -l -q -b codes/ModifyTopDirName.C\(\""$inputdir/$year/all_${sample}.root"\",\""${sample}"\",\""${sample}_1.root"\",\""TTG"\"\) > /tmp/out.log 2>&1
    	echo $PWD/${sample}_1.root >> $fname
    done
    source ~/scripts/addhisto_file.sh $fname
    for sample in TTGToLL TTGToLNu TTGToQQ
    do
    	rm ${sample}_1.root 
    done
    mv histo_merged.root $inputdir/$year/all_TTG.root
    cat $fname
    
    #TTH
    if [ -f $fname ] ; then 
    	rm $fname
    fi
    for sample in TTHToGG TTHToNonbb TTHTobb
    do
    	echo Processing for sample : $sample
    	root -l -q -b codes/ModifyTopDirName.C\(\""$inputdir/$year/all_${sample}.root"\",\""${sample}"\",\""${sample}_1.root"\",\""TTH"\"\) > /tmp/out.log 2>&1
    	echo $PWD/${sample}_1.root >> $fname
    done
    source ~/scripts/addhisto_file.sh $fname
    for sample in TTHToGG TTHToNonbb TTHTobb
    do
    	rm ${sample}_1.root 
    done
    mv histo_merged.root $inputdir/$year/all_TTH.root
    cat $fname


    #TTW
    if [ -f $fname ] ; then 
    	rm $fname
    fi
    for sample in TTWJetsToLNu TTWJetsToQQ
    do
    	echo Processing for sample : $sample
    	root -l -q -b codes/ModifyTopDirName.C\(\""$inputdir/$year/all_${sample}.root"\",\""${sample}"\",\""${sample}_1.root"\",\""TTW"\"\) > /tmp/out.log 2>&1
    	echo $PWD/${sample}_1.root >> $fname
    done
    source ~/scripts/addhisto_file.sh $fname
    for sample in TTWJetsToLNu TTWJetsToQQ
    do
    	rm ${sample}_1.root 
    done
    mv histo_merged.root $inputdir/$year/all_TTW.root
    cat $fname
    

    #TTZ
    if [ -f $fname ] ; then 
    	rm $fname
    fi
    for sample in TTZToLLNuNu TTZToQQ
    do
    	echo Processing for sample : $sample
    	root -l -q -b codes/ModifyTopDirName.C\(\""$inputdir/$year/all_${sample}.root"\",\""${sample}"\",\""${sample}_1.root"\",\""TTZ"\"\) > /tmp/out.log 2>&1
    	echo $PWD/${sample}_1.root >> $fname
    done
    source ~/scripts/addhisto_file.sh $fname
    for sample in TTZToLLNuNu TTZToQQ
    do
    	rm ${sample}_1.root 
    done
    mv histo_merged.root $inputdir/$year/all_TTZ.root
    cat $fname

    rm $fname
done

# Alternatively one can use commands like below to fuse the files
# rootcp all_HplusM080.root:HplusM080 /tmp/all_HplusM080.root:HplmiM080
# rootcp all_HminuM080.root:HminusM080 /tmp/all_HminusM080.root:HplmiM080
# hadd all_HplmiM080.root /tmp/all_HplusM080.root /tmp/all_HminusM080.root
