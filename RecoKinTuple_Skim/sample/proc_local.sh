#!/bin/bash

execdir=/home/idas/t3store3/git/KinFit_Skim/RecoKinTuple_Skim 

#source $execdir/sample/Skim_NanoAOD_FileLists_cff.sh
sample=ST_tW_channel
year=2016
fl=${sample}_FileList_${year}
#outfile=/tmp/fl_faltu.txt 
#rm $outfile 
for i in `echo $ST_tW_channel_FileList_2016`
do 
   dir=`echo $i | cut -f 13 -d '/' | cut -f 6 -d '_' | cut -f 1 -d '.'`
   #lastdir=`echo $i | awk -F/ '{for(i=NF;i<=NF;i++) printf "%s", $i;}'`
   #echo file : $i, dir : $dir, lastdir : $lastdir
   echo file : $i, dir : $dir
   #root -l -b -q $i
   #sleep 3
   $execdir/makeRecoKinTuple $year $sample $dir . $ST_tW_channel_FileList_2016 > output_${sample}_${dir}.log 2>&1 & 
done 

#$execdir/makeRecoKinTuple 2016 ST_tW_channel . $line > output_${dir}.log 2>&1 &
