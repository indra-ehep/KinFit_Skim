import itertools
import os
import sys
import subprocess
import time

#IMPORT MODULES FROM OTHER DIR

#injpoints = ["0", "M" , "1"]
injpoints = ["0", "M"]
jdlDir = 'tmpLog_gofmc_random_1'
if not os.path.exists("%s/log"%jdlDir):
    os.makedirs("%s/log"%jdlDir)
condorLogDir = "log"
os.system("cp runGofMcTest.sh %s/"%jdlDir)
os.system("cp gofmc_injp.sh %s/"%jdlDir)
os.system("cp importPars.py %s/"%jdlDir)
common_command = \
'executable = runGofMcTest.sh\n\
+MaxRuntime = 10799\n\
request_memory = 8000\n\
output = %s/log_$(cluster)_$(process).stdout\n\
error  = %s/log_$(cluster)_$(process).stderr\n\
log    = %s/log_$(cluster)_$(process).condor\n\n'%(condorLogDir, condorLogDir, condorLogDir)
#----------------------------------------
#Create jdl files
#----------------------------------------
subFile = open('%s/condorSubmit.sh'%jdlDir,'w')
#for mass in [40,50,60,70,80,90,100,110,120,130,140,150,155,160]:
for mass in [40,80,120,160]:
    injpointList = eval("injpoints")
    jdlName = 'submitJobs_%s.jdl'%(mass)
    jdlFile = open('%s/%s'%(jdlDir,jdlName),'w')
    jdlFile.write(common_command)    
    #jdlFile.write("X=$(step)\n")
    
    for injpoint in injpointList:        
        run_command =  'Arguments  = %s Run2 mu_ele %s $(cluster)_$(process)\nQueue 1\n\n' %(mass, injpoint)
        jdlFile.write(run_command)        
    jdlFile.close()
    subFile.write("condor_submit %s\n"%jdlName)
subFile.close()
