#!/bin/sh

waitingtime=120
allowed_max=28000
while true
do
    waiting $waitingtime
    echo waited for $waitingtime sec
    ls -l | grep "^d" | awk '{print $9}' | grep full
    nof_full=`ls -l | grep "^d" | awk '{print $9}' | grep "log_full" | wc -l`
    echo nof log_full folders : ${nof_full}
    next_full_index=$[$nof_full+1]
    if [ -d log ] ; then
	nof_log_files=`ls log/*.* | wc -l`
	echo next_full_index : ${next_full_index}, nof_log_files : ${nof_log_files}
	if [ ${nof_log_files} -gt ${allowed_max} ] ; then
	    echo mv log log_full_${next_full_index}
	    echo mkdir log
	    mv log log_full_${next_full_index}
	    mkdir log
	fi
    fi
    date
done
