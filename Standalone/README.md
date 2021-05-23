Motivation :
======================

The main purpose of these codes is to run a "standalone" Kinematic Fitting on recotuple files (prepared using https://github.com/ravindkv/cms-hcs-run2).
The pair of files which performs the task are PerformKinFit.h and PerformKinFit.C. Please find more details about the codes and execution below.
Here I must admit that although it is said to be "standalone", it is not really a standalone Kinematic Fitting package, it uses the base Kinematic Package of CMS software.
So the user requires to perform Kinematic Fitting in a computer equipped with CMS analysis tools.  

Installation :
======================

'git clone https://github.com/indra-ehep/KinFit_Skim.git'

Then one needs to change directory to KinFit_Skim/Standalone to run the code..

Execution :
======================

To execute the Kinematic Fitting the user has to call,

'root -l -b -q run.C'

ofcourse after setting the standard CMS analysis environments such as the following commands in lxplus. 

'source /cvmfs/cms.cern.ch/cmsset_default.sh'  
'cmsrel CMSSW_10_2_13'  
'cd CMSSW_10_2_13/src'  
'cmsenv'  
'cd INSTALLATION_PATH_OF_KinFit_Skim/Standalone'  

There is one last thing before executing the root command is that the user needs to set the list of input files at files.txt (see below).


If the user is interested to execute Kinematic Fitting in loops, then one can look inside python script KinFitLoop.py. The user would realize that it invokes bash script run_root which in turn calls run.C for the execution in loop.


Body :
======================

files.txt:  
This file contains the list of files to be analyzed. Each item of the list is separated using new lines. One can add '#' sign infront of a files, to skip it in analysis. Should you use the files in xrootd server (such as eosuser.cern.ch or indiacms.res.in) for analysis, then do not forget to initialize your GRID credentials,  
'voms-proxy-init -voms cms'  

run.C:  
This a simple root macro that contains
1) Input arguments for PerformKinFit.   
2) Reads files.txt to create TChain.  
3) Then process the first 10000 as set in  
'chain->Process("PerformKinFit.C++", options.Data(), 10000);'.  
One can change it to,  
'chain->Process("PerformKinFit.C++", options.Data());'  
if wishes to process all data of TChain.

PerformKinFit.C:  

