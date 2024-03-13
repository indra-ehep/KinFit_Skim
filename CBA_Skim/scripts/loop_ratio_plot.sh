st=2
#year=2016
year=$1
#KF mu
for i in `seq 0 10` ; do root  -l -q -b codes/PlotRatioSystematicsV5UL.C+\($year,0,1,$i\) ; sleep $st ; done
for i in `seq 14 17` ; do root  -l -q -b codes/PlotRatioSystematicsV5UL.C+\($year,0,1,$i\) ; sleep $st ; done 
for i in `seq 18 26` ; do root  -l -q -b codes/PlotRatioSystematicsV5UL.C+\($year,0,1,$i\) ; sleep $st ; done

#KF ele
for i in `seq 0 10` ; do root  -l -q -b codes/PlotRatioSystematicsV5UL.C+\($year,0,0,$i\) ; sleep $st ; done 
for i in `seq 14 17` ; do root  -l -q -b codes/PlotRatioSystematicsV5UL.C+\($year,0,0,$i\) ; sleep $st ; done 
for i in `seq 18 26` ; do root  -l -q -b codes/PlotRatioSystematicsV5UL.C+\($year,0,0,$i\) ; sleep $st ; done

#BTag
for i in `seq 0 9` ; do root  -l -q -b codes/PlotRatioSystematicsV5UL.C+\($year,1,1,$i\) ; sleep $st ; done
for i in `seq 0 9` ; do root  -l -q -b codes/PlotRatioSystematicsV5UL.C+\($year,1,0,$i\) ; sleep $st ; done 

# st=2
# for i in `seq 0 9` ; do root  -l -q -b codes/CompareExclInclObs.C+\(0,0,$i\) ; sleep $st ; done 
# for i in `seq 0 9` ; do root  -l -q -b codes/CompareExclInclObs.C+\(0,1,$i\) ; sleep $st ; done 
# for i in `seq 0 9` ; do root  -l -q -b codes/CompareExclInclObs.C+\(1,0,$i\) ; sleep $st ; done 
# for i in `seq 0 9` ; do root  -l -q -b codes/CompareExclInclObs.C+\(1,1,$i\) ; sleep $st ; done
