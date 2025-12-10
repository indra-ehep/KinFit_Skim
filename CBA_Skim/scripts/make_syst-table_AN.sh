indir=$1

for year in 2016 2017 2018
do
    for ch in ele mu
    do
	for tag  in L M T
	do
	    fname=$indir/mjjTable_${ch}_${tag}_${year}.tex
	    fout=sec07_syst_${ch}_Exc${tag}_${year}.tex
	    start=`grep adjustbox -n $fname | grep begin | cut -d ':' -f 1`
	    stop=`grep adjustbox -n $fname | grep end | cut -d ':' -f 1`
	    echo $fname : start:stop $start : $stop
	    diff=`echo $stop-$start+1|bc -l`
	    head -n $stop $fname | tail -n $diff > $fout

	    nofline=`wc -l $fout | awk '{print $1}'`
	    nofline_1=$[$nofline-1]
	    nofline_2=$[$nofline-2]
	    echo "\centering\cmsTable{" > /tmp/$fout
	    tail -n ${nofline_1} $fout | head -n ${nofline_2} >> /tmp/$fout
	    echo "}" >> /tmp/$fout
	    mv /tmp/$fout $fout 
	done
    done
done

for year in 2016 2017 2018
do
    fname=$indir/mjjTable_yield_${year}.tex
    fout=sec07_yield_Exc_${year}.tex
    start=`grep adjustbox -n $fname | grep begin | cut -d ':' -f 1`
    stop=`grep adjustbox -n $fname | grep end | cut -d ':' -f 1`
    echo $fname : start:stop $start : $stop
    diff=`echo $stop-$start+1|bc -l`
    head -n $stop $fname | tail -n $diff > $fout

    nofline=`wc -l $fout | awk '{print $1}'`
    nofline_1=$[$nofline-1]
    nofline_2=$[$nofline-2]
    echo "\centering\cmsTable{" > /tmp/$fout
    tail -n ${nofline_1} $fout | head -n ${nofline_2} >> /tmp/$fout
    echo "}" >> /tmp/$fout
    mv /tmp/$fout $fout 
done


