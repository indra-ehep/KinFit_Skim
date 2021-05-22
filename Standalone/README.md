The main purpose of these codes is to run standalone Kinematic Fitting on recotuple files (prepared using https://github.com/ravindkv/cms-hcs-run2).
The pair of files which performs the task are PerformKinFit.h and PerformKinFit.C. However, to execute them the user has call,

'root -l -b -q run.C'

ofcourse after setting the standard CMS analysis environments. There is one last thing before executing the root command is that the user needs to set the list of input files at files.txt.

If the user is interested to execute Kinematic Fitting in loops, then one can look inside python script KinFitLoop.py. The user would realize that it invokes run_root which in turn calls run.C for the execution in loop.
