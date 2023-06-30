#!/bin/sh

jobid=$1

for node in `condor_q -nobatch $jobid | grep idas | awk '{print $1}'`
do 
    tot=`condor_ssh_to_job $node tail -n 1 _condor_stderr | awk '{print $12}'` 
    comp=`condor_ssh_to_job $node tail -n 1 _condor_stderr | awk '{print $6}' | cut -f 1 -d '('`
    ratio=`echo 100*$comp/$tot | bc` 
    echo Node : $node completed $ratio% 
done
