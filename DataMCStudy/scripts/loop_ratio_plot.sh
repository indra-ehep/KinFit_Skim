st=0
# for i in `seq 0 10` ; do root  -l -q -b codes/PlotRatioSystematics.C+\(0,1,$i\) ; sleep $st ; done 
# for i in `seq 0 9` ; do root  -l -q -b codes/PlotRatioSystematics.C+\(1,1,$i\) ; sleep $st ; done
for i in `seq 0 9` ; do root  -l -q -b codes/PlotRatioSystematics.C+\(1,0,$i\) ; sleep $st ; done 
for i in `seq 0 10` ; do root  -l -q -b codes/PlotRatioSystematics.C+\(0,0,$i\) ; sleep $st ; done 

# st=2
# for i in `seq 0 9` ; do root  -l -q -b codes/CompareExclInclObs.C+\(0,0,$i\) ; sleep $st ; done 
# for i in `seq 0 9` ; do root  -l -q -b codes/CompareExclInclObs.C+\(0,1,$i\) ; sleep $st ; done 
# for i in `seq 0 9` ; do root  -l -q -b codes/CompareExclInclObs.C+\(1,0,$i\) ; sleep $st ; done 
# for i in `seq 0 9` ; do root  -l -q -b codes/CompareExclInclObs.C+\(1,1,$i\) ; sleep $st ; done
