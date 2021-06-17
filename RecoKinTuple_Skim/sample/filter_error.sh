#!/bin/bash

execdir=/eos/user/i/idas/CMS-Analysis/KinFit_Skim/RecoKinTuple_Skim

function cpucount(){

    top_outfile=/tmp/topoutput.txt
    top -b -n 1 > /tmp/out.txt
    nofline=`wc -l /tmp/out.txt | awk '{print $1}'`
    nofline=$[$nofline-7]
    tail -n $nofline /tmp/out.txt > $top_outfile
    totcpu=`awk -F ' ' '{SUM+=$9}END{print SUM}'  $top_outfile`
#echo totcpu : $totcpu
#nofcpu=$(($totcpu/100))
    nofcpu1=$(echo "$totcpu/100" | bc -l)
#echo nofcpu1 : $nofcpu1
    nofcpu2=`echo "$nofcpu1" | awk '{printf("%d\n",$0+=$0<0?-0.5:0.5)}'`
#echo nofcpu2 : $nofcpu2
    echo $nofcpu2

}

######## Set the following values ##############
maxnofcpuauproc=10
nsec=20
################################################


singlefile="NanoAOD"
year=2020

while read line
do
    sample=`echo $line | awk -F _ '{for(i=1;i<=NF-3;i++) printf "%s_", $i; for(i=NF-2;i<=NF-2;i++) printf "%s", $i;}'`
    #echo ${sample}
    year=`echo $line | awk -F _ '{for(i=NF;i<=NF;i++) printf "%s", $i;}'`
    for i in `echo ${!line}`
    do
	filename=`echo $i | cut -f 13 -d '/' | cut -f 1 -d '.'`
	dir=`echo $filename | awk -F _ '{for(i=NF;i<=NF;i++) printf "%s", $i;}'`
	#echo file : $filename, dir : $dir, year : $year
	if [ "$dir" = "$singlefile" ]; then
	    #echo "Single excution."	    
	    #echo $execdir/makeRecoKinTuple $year $sample . ${!line}
	    #$execdir/makeRecoKinTuple $year $sample . ${!line} > output_${sample}.log 2>&1 & 
            if [ -f output_${sample}.log ]; then 
		#noferror=`grep -i "Unable to open /cms/store/user/idas/Output/cms-hcs-run2/Skim_NanoAOD/2016/" output_${sample}.log | wc -l`
		noferror=`grep -i error output_${sample}.log | wc -l`
		if [ $noferror -gt 0 ] ; then
		    echo file output_${sample}.log and ${sample}_RecoKinTuple_Skim.root has problem.
		    #mv output_${sample}.log ${sample}_RecoKinTuple_Skim.root problem/
		fi
	    fi
	else
	    #echo "Partial excution"
	    #echo $execdir/makeRecoKinTuple $year $sample $dir . ${!line}
	    #$execdir/makeRecoKinTuple $year $sample $dir . ${!line} > output_${sample}_${dir}.log 2>&1 & 
	    if [ -f output_${sample}_${dir}.log ]; then 
		#noferror=`grep -i "Unable to open /cms/store/user/idas/Output/cms-hcs-run2/Skim_NanoAOD/2016/" output_${sample}_${dir}.log | wc -l`
		noferror=`grep -i error output_${sample}_${dir}.log | wc -l`
		if [ $noferror -gt 0 ] ; then
		    echo file output_${sample}_${dir}.log and ${sample}_RecoKinTuple_Skim_${dir}.root has problem.
                    #mv output_${sample}_${dir}.log ${sample}_RecoKinTuple_Skim_${dir}.root problem/
		fi
	    fi
	fi

    done
done < $1

#source $execdir/sample/Skim_NanoAOD_FileLists_cff.sh
# sample=ST_tbar_channel
# year=2016
# fl=${sample}_FileList_${year}
# echo ${fl}
# echo ${!fl}
# #outfile=/tmp/fl_faltu.txt 
# #rm $outfile 
# #for i in `echo $ST_tW_channel_FileList_2016`
# for i in `echo ${!fl}`
# do 
#    dir=`echo $i | cut -f 13 -d '/' | cut -f 6 -d '_' | cut -f 1 -d '.'`
#    #lastdir=`echo $i | awk -F/ '{for(i=NF;i<=NF;i++) printf "%s", $i;}'`
#    #echo file : $i, dir : $dir, lastdir : $lastdir
#    echo file : $i, dir : $dir
#    #root -l -b -q $i
#    #sleep 3
#    #$execdir/makeRecoKinTuple $year $sample $dir . $ST_tW_channel_FileList_2016 > output_${sample}_${dir}.log 2>&1 & 
# done 

#$execdir/makeRecoKinTuple 2016 ST_tW_channel . $line > output_${dir}.log 2>&1 &
