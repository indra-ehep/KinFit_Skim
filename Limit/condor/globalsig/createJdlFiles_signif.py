import itertools
import os
import sys
import subprocess
import time

#IMPORT MODULES FROM OTHER DIR

iloop= "1"

yearlist1 = ["Run2"]
catlist1 = ["Comb"]
channellist = ["mu_ele"]

jdlDir = 'tmpLog_globalsig_iter%s'%iloop
if not os.path.exists("%s/log"%jdlDir):
    os.makedirs("%s/log"%jdlDir)
condorLogDir = "log"
os.system("cp runSignif.sh %s/"%jdlDir)
os.system("cp genSignifCondor.sh %s/"%jdlDir)
common_command = \
'executable = runSignif.sh\n\
+MaxRuntime = 10799\n\
request_memory = 4000\n\
output = %s/log_$(cluster)_$(process).stdout\n\
error  = %s/log_$(cluster)_$(process).stderr\n\
log    = %s/log_$(cluster)_$(process).condor\n\n'%(condorLogDir, condorLogDir, condorLogDir)

masslist = [60]

#----------------------------------------
#Perform initial fit and impact commands for condor submission
#----------------------------------------
for year in yearlist1:
    for cattype in catlist1:
        for channel in channellist:
            for mass in masslist:
                os.system("sh genSignifCondor.sh %s %s %s %s" %(mass, year, channel, cattype))

                
#----------------------------------------
#Create tar file
#----------------------------------------
tarFile = "local.tar.gz"
if os.path.exists(tarFile):
    os.system("rm %s"%tarFile)
os.system("tar -zcvf %s local "%tarFile)
os.system("cp local.tar.gz %s/"%jdlDir)

#----------------------------------------
#Create jdl files
#----------------------------------------
subFile = open('%s/condorSubmit.sh'%jdlDir,'w')
for year in yearlist1:
    for cattype in catlist1:
        for channel in channellist:
            for mass in masslist:
                for itoy in range(1, 3001):
                    jdlName = 'submitJobs_%d_%s_%s_%s_%s.jdl'%(itoy,year,mass,channel,cattype)
                    jdlFile = open('%s/%s'%(jdlDir,jdlName),'w')
                    jdlFile.write(common_command)
                    #nqueue = subprocess.Popen(['grep -i queue local/%s/%s/Cat1_Inc/Mass%s/condor_run.sub | awk \'{print $2}\''%(year,channel,mass)],shell=True,stdout=subprocess.PIPE).communicate()[0].decode("utf-8")
                    run_command =  'Arguments  = %s %s %s %s $(process) %s %s\nQueue 1\n\n' %(mass,year,channel,cattype,iloop,itoy)
                    jdlFile.write(run_command)        
                    jdlFile.close()
                    subFile.write("condor_submit %s\n"%jdlName)

                
subFile.close()

print ("Now run from directory : %s/"%jdlDir)

