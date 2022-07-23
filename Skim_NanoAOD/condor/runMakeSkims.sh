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
    export SCRAM_ARCH=slc7_amd64_gcc700
    source /cvmfs/cms.cern.ch/cmsset_default.sh
    # scramv1 project CMSSW CMSSW_10_2_14
    # cd CMSSW_10_2_14/src
    scramv1 project CMSSW CMSSW_10_6_29
    cd CMSSW_10_6_29/src
    eval `scramv1 runtime -sh`
    cd ../..
	tar --strip-components=1 -zxvf Skim_NanoAOD.tar.gz
fi

#Run for Base, Signal region
echo "All arguements: "$@
echo "Number of arguements: "$#
year=$1
sample=$2
job=$3
nJobTotal=$4
varname=${sample}_FileList_${year}
cd sample
source NanoAOD_Gen_FileLists_cff.sh 
cd -
if [ -z $job ] ; then
    jobNum=""
else
    jobNum=" ${job}of${nJobTotal}"
fi
echo "./makeSkim ${year}${jobNum} ${sample}_Skim_NanoAOD.root ${!varname}"
./makeSkim ${year}$jobNum ${sample}_Skim_NanoAOD.root ${!varname}

printf "Done Histogramming at ";/bin/date
#---------------------------------------------
#Copy the ouput root files
#---------------------------------------------
#condorOutDir=/store/user/rverma/Output/cms-hcs-run2/Skim_NanoAOD
#condorOutDir1="/eos/user/i/idas/Output/cms-hcs-run2/Skim_NanoAODUL"
#condorOutDir1="/eos/cms/store/group/phys_higgs/HiggsExo/idas/cms-hcs-run2/Skim_NanoAODUL"
condorOutDir1="/eos/user/d/dugad/idas/Output/cms-hcs-run2/Skim_NanoAODUL"

if [ -z ${_CONDOR_SCRATCH_DIR} ] ; then
    echo "Running Interactively" ;
else
    #xrdcp -f ${sample}_Skim_NanoAOD*.root root://cmseos.fnal.gov/${condorOutDir}/${year}
    xrdcp -f ${sample}_Skim_NanoAOD*.root root://eosuser.cern.ch/${condorOutDir1}/${year}
    echo "Cleanup"
    rm -rf CMSSW*
    rm *.root
fi
printf "Done ";/bin/date
