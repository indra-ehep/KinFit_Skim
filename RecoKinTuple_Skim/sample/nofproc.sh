#!/bin/bash

while true 
do 
    nofproc=`ps -ef | grep makeRecoKinTuple | wc -l` 
    nofproc=$[$nofproc-1] 
    echo nofproc : $nofproc 
    sleep 20 
    if [ $nofproc -eq 0 ] ; then 
	break  
    fi 
done
