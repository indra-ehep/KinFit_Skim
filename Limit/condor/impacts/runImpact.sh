#!/bin/bash
#To be run on remote machine
#Take input arguments as an array
myArray=( "$@" )
# #Array: Size=$#, an element=$1, all element = $@

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
rundir=${_CONDOR_SCRATCH_DIR}
random=${RANDOM}
clusproc=$4
iloop=$5

testdir=$rundir/${channel}_${year}_impact_qcdrangepm30_qcddd6_bc3_uncorr_brpm0p1_10GeV_iter$iloop

if [ ! -d $testdir ] ; then
    mkdir -p $testdir
else
    rm $testdir/*.*
fi

#mv local.tar.gz $testdir/
cd $testdir
rsync -avP  /home/hep/idas/temp/condor_test/test_combine_condor/tmpLog_impact_iter$iloop/local.tar.gz .
tar -zxf local.tar.gz
cd local/$year/$channel/Cat1_Inc/Mass$mass
source condor_run.sh $clusproc > out_${clusproc}.log 2>&1
cd $testdir

printf "Done job at: ";/bin/date

condorOutDir1=/home/hep/idas/CMS-Analysis/NanoAOD-Analysis/SkimAna/lx04_impact-data/local/

rsync -avP  $rundir/* $condorOutDir1
# rsync -avP --include="*/" --include="*.GoodnessOfFit.*.root" --exclude="*"  $rundir/* $condorOutDir1
# rsync -avP --include="*/" --include="limit*" --exclude="*"  $rundir/* $condorOutDir1
# rsync -avP --include="*/" --include="*.txt" --exclude="*"  $rundir/* $condorOutDir1

printf "Done transfer: ";/bin/date
