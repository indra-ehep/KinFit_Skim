#!/bin/bash
#To be run on remote machine
#Take input arguments as an array
myArray=( "$@" )
#Array: Size=$#, an element=$1, all element = $@

printf "Start Running job at: ";/bin/date
printf "Worker node hostname: ";/bin/hostname
#alias setcmsenv_combine_1410pre4='base_dir=$PWD ; source /cvmfs/cms.cern.ch/cmsset_default.sh ; cd /home/hep/idas/CMSSW/CMSSW_14_1_0_pre4/src ; eval `scramv1 runtime -sh` ; ls ;cd ${base_dir}'
#setcmsenv_combine_1410pre4
currdir=$PWD
source /cvmfs/cms.cern.ch/cmsset_default.sh
cd /home/hep/idas/CMSSW/CMSSW_14_1_0_pre4/src
eval `scramv1 runtime -sh`
ls
cd ${currdir}
echo "CMSSW_BASE : $CMSSW_BASE"
printf "SCRAM :  ${SCRAM_ARCH}\n"
which root
echo $ROOTSYS

echo "All arguements: "$@
echo "Number of arguements: "$#
mass=$1
year=$2
channel=$3
injpoint=$4
rundir=${_CONDOR_SCRATCH_DIR}
random=${RANDOM}
clusproc=$5

source gofmc_injp.sh  $mass $year $channel $injpoint $rundir $random $clusproc

printf "Done job at: ";/bin/date

condorOutDir1=/home/hep/idas/CMS-Analysis/NanoAOD-Analysis/SkimAna/lx04_gof-data/local/

rsync -avP  $rundir/* $condorOutDir1
rsync -avP --include="*/" --include="*.GoodnessOfFit.*.root" --exclude="*"  $rundir/* $condorOutDir1
rsync -avP --include="*/" --include="limit*" --exclude="*"  $rundir/* $condorOutDir1
rsync -avP --include="*/" --include="*.txt" --exclude="*"  $rundir/* $condorOutDir1

printf "Done transfer: ";/bin/date
