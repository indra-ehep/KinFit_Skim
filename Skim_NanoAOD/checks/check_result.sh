#!/bin/sh

# compare file entries
input=$1
totjobs=0
totfound=0
grep arguements $input | grep 2017 > /tmp/$USER/fl_tmp0.txt
grep arguements $input | grep -v 2017 > /tmp/$USER/fl_tmp1.txt
skimdir=/eos/cms/store/group/phys_b2g/idas/Output/cms-hcs-run2/Skim_NanoAODUL

while read line
do
    # echo $line
    year=`echo $line | cut -d ' ' -f 3`
    dataset_name=`echo $line | cut -d ' ' -f 4`
    extention=`echo $line | cut -d ' ' -f 6`
    # extention2=`expr $extention`
    # echo dataset : $dataset_name
    # echo extention : $extention
    # echo extention2 : $extention2
    found=0;
    if [ $extention -gt 0 ] ; then
    	# echo need to loop
     	totjobs=$[$totjobs+$extention]
	for i in `seq 1 $extention` 
	do
	    if [ -f $skimdir/$year/${dataset_name}_Skim_NanoAOD_${i}of${extention}.root ] ; then
		found=$[$found+1]
	    else
     		echo File $skimdir/$year/${dataset_name}_Skim_NanoAOD_${i}of${extention}.root not found.
	    fi
	done
	#echo $dataset_name  : $found found out of ${extention}	
	#percent=`expr 100 \* $found \/ $extention`
	printf  "%30b : %02d of %02d complete.\n" ${dataset_name} ${found}  ${extention} #${percent}
    fi
    totfound=$[$totfound+$found]
done < /tmp/$USER/fl_tmp0.txt

# while read line
# do
#     # echo $line
#     year=`echo $line | cut -d ' ' -f 3`
#     dataset_name=`echo $line | cut -d ' ' -f 4`
#     found=0;
#     totjobs=$[$totjobs+1]
#     if [ -f $skimdir/$year/${dataset_name}_Skim_NanoAOD.root ] ; then
# 	found=$[$found+1]
#     else
#      	echo File $skimdir/$year/${dataset_name}_Skim_NanoAOD.root not found.
#     fi
#     totfound=$[$totfound+$found]
#     printf  "%30b : %01d of 1 complete.\n" ${dataset_name} ${found} #${percent}

# done < /tmp/$USER/fl_tmp1.txt

#remaining=`wc -l /tmp/$USER/fl_tmp1.txt  | awk '{print $1}'`
#totjobs=$[$totjobs+$remaining]

echo total jobs : $totjobs and total files : $totfound
