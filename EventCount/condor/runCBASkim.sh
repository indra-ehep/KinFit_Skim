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
    source /cvmfs/cms.cern.ch/cmsset_default.sh
    scramv1 project CMSSW CMSSW_10_2_14
    cd CMSSW_10_2_14/src
    eval `scramv1 runtime -sh`
    cd ../..
    
fi
tar --strip-components=1 -zxvf EventCount.tar.gz
#Run for Base, Signal region
#./complib.sh
echo "All arguements: "$@
echo "Number of arguements: "$#
index=$1
sample=$2

#time root -l -b -q run.C\(\""sample=${sample}|year=${year}|input=${input}|index=${index}|syst=${syst}|aod=nano|run=prod"\"\)
#time ./SkimAna $sample $year $input $index $syst

time root -l -b -q  MCChannelStudy.C++\(${index},\""${sample}"\"\) 

printf "Done Histogramming at ";/bin/date
#---------------------------------------------
#Copy the ouput root files
#---------------------------------------------
condorOutDir1=/eos/user/i/imirza/idas/Output/cms-hcs-run2/EventCount_TTbar
#condorOutDir=/cms/store/user/idas/Output/cms-hcs-run2/EventCount_Syst_jet_tightID
if [ -z ${_CONDOR_SCRATCH_DIR} ] ; then
    echo "Running Interactively" ;
else
    #xrdcp -f ${sample}_tree_*.root root://se01.indiacms.res.in:1094/${condorOutDir}/${year} 
    xrdcp -f EventCount_*.root root://eosuser.cern.ch/${condorOutDir1}/${year}
    echo "Cleanup"
    rm -rf CMSSW_10_2_14
    rm *.root
fi
printf "Done ";/bin/date
