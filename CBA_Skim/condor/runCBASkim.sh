#!/bin/bash
#To be run on remote machine
#Take input arguments as an array
myArray=( "$@" )
#Array: Size=$#, an element=$1, all element = $@

printf "Start Running Histogramming at ";/bin/date
printf "Worker node hostname ";/bin/hostname

if [ -z ${_CONDOR_SCRATCH_DIR} ] ; then 
    echo "Running Interactively" ; 
else
    echo "Running In Batch"
    echo ${_CONDOR_SCRATCH_DIR}
    # export SCRAM_ARCH=slc7_amd64_gcc700
    # source /cvmfs/cms.cern.ch/cmsset_default.sh
    # scramv1 project CMSSW CMSSW_10_6_29
    # cd CMSSW_10_6_29/src
    export SCRAM_ARCH=slc7_amd64_gcc900
    source /cvmfs/cms.cern.ch/cmsset_default.sh
    scramv1 project CMSSW CMSSW_12_1_0
    cd CMSSW_12_1_0/src
    eval `scramv1 runtime -sh`
    cd ../..
    
fi
tar --strip-components=1 -zxvf CBA_Skim.tar.gz
#Run for Base, Signal region
#./complib.sh
echo "All arguements: "$@
echo "Number of arguements: "$#
year=$1
sample=$2
input=$3
index=$4
syst=$5

#time root -l -b -q run.C\(\""sample=${sample}|year=${year}|input=${input}|index=${index}|syst=${syst}|aod=nano|run=prod"\"\)

time ./SkimAna $sample $year $input $index $syst

printf "Done Histogramming at ";/bin/date
#---------------------------------------------
#Copy the ouput root files
#---------------------------------------------
# condorOutDir=/eos/user/s/savarghe/Indra_Da/Output/cms-hcs-run2/CBA_muFmuR
# condorOutDir1=/eos/user/i/idas/Output/cms-hcs-run2/CBA_muFmuR
# condorOutDir2=/cms/store/user/idas/Output/cms-hcs-run2/KinTreeUL/CBA_muFmuR
condorOutDir=/eos/user/s/savarghe/Indra_Da/Output/cms-hcs-run2/CBA_muFmuR/pre
condorOutDir1=/eos/user/i/idas/Output/cms-hcs-run2/CBA_muFmuR/pre
condorOutDir2=/cms/store/user/idas/Output/cms-hcs-run2/KinTreeUL/CBA_muFmuR/pre
if [ -z ${_CONDOR_SCRATCH_DIR} ] ; then
    echo "Running Interactively" ;
else
    #xrdcp -f ${sample}_tree_*.root root://se01.indiacms.res.in:1094/${condorOutDir}/${year} 
    xrdcp -f ${sample}_tree_*.root root://eosuser.cern.ch/${condorOutDir}/${year}
    xrdcp -f ${sample}_hist_*.root root://eosuser.cern.ch/${condorOutDir1}/${year}
    xrdcp -f ${sample}_tree_*.root root://se01.indiacms.res.in:1094/${condorOutDir2}/${year}
    echo "Cleanup"
    rm -rf CMSSW_12_1_0
    rm *.root
fi
printf "Done ";/bin/date
