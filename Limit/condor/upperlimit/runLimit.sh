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
cattype=$4
rundir=${_CONDOR_SCRATCH_DIR}
random=${RANDOM}
clusproc=$5
iloop=$6

outdir=limit_qcdrange0to50_qcddd6_bc3_uncorr_br0to0p1_sym_nzlbin_10GeV_iter$iloop
outpath=$outdir/${year}/${cattype}/${channel}
condorOutDir=/home/hep/idas/CMS-Analysis/NanoAOD-Analysis/SkimAna/limit_lx04/local/$outpath/Cat1_Inc/Mass$mass
testdir=$rundir/$outpath

if [ ! -d $testdir ] ; then
    mkdir -p $testdir
else
    rm $testdir/*.*
fi

if [ ! -d $condorOutDir ] ; then
    mkdir -p $condorOutDir
else
    rm $condorOutDir/*.*
fi

#mv local.tar.gz $testdir/
cd $testdir
rsync -avP  /home/hep/idas/temp/condor_test/test_limit_condor/tmpLog_limit_iter$iloop/local.tar.gz .
tar -zxf local.tar.gz
cd local/$year/$cattype/$channel/Cat1_Inc/Mass$mass
source condor_run.sh $clusproc > out_${clusproc}.log 2>&1
rsync -avP  *.AsymptoticLimits.*.root $condorOutDir
cd $testdir

printf "Done job at: ";/bin/date

# condorOutDir1=/home/hep/idas/CMS-Analysis/NanoAOD-Analysis/SkimAna/limit_lx04/local/

# if [ ! -d $condorOutDir2 ] ; then
#     mkdir -p $condorOutDir2
# fi

# rsync -avP  $rundir/* $condorOutDir1
# rsync -avP  $testdir/local/$cattype/$year/$channel/Cat1_Inc $condorOutDir2

# rsync -avP --include="*/" --include="*.GoodnessOfFit.*.root" --exclude="*"  $rundir/* $condorOutDir1
# rsync -avP --include="*/" --include="limit*" --exclude="*"  $rundir/* $condorOutDir1
# rsync -avP --include="*/" --include="*.txt" --exclude="*"  $rundir/* $condorOutDir1

printf "Done transfer: ";/bin/date
