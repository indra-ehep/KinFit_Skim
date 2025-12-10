import itertools
import os
import sys
import subprocess
import time

#IMPORT MODULES FROM OTHER DIR

iloop= "45"

#year = "Run2"
#yearlist = ["Run2"]
yearlist1 = ["Run2", "2016", "2017", "2018"]
yearlist2 = ["2016", "2017", "2018"]

catlist1 = ["Comb"]
catlist2 = ["ExcL", "ExcM", "ExcT"]

#channel = "mu_ele"
#channellist = ["mu","ele"]
#channellist = ["ele"]
channellist = ["mu_ele", "mu", "ele"]

jdlDir = 'tmpLog_limit_iter%s'%iloop
if not os.path.exists("%s/log"%jdlDir):
    os.makedirs("%s/log"%jdlDir)
condorLogDir = "log"
os.system("cp runLimit.sh %s/"%jdlDir)
os.system("cp listReducedNui.exe %s/"%jdlDir)
os.system("cp genLimitCondor.sh %s/"%jdlDir)
common_command = \
'executable = runLimit.sh\n\
+MaxRuntime = 10799\n\
request_memory = 4000\n\
output = %s/log_$(cluster)_$(process).stdout\n\
error  = %s/log_$(cluster)_$(process).stderr\n\
log    = %s/log_$(cluster)_$(process).condor\n\n'%(condorLogDir, condorLogDir, condorLogDir)

masslist = [40,50,60,70,80,90,100,110,120,130,140,150,155,160]
#masslist = [60,80,90,100,110,120,130,140]
#masslist = [80]
#masslist = [70]

#----------------------------------------
#Perform initial fit and impact commands for condor submission
#----------------------------------------
for year in yearlist1:
    for cattype in catlist1:
        for channel in channellist:
            for mass in masslist:
                os.system("sh genLimitCondor.sh %s %s %s %s" %(mass, year, channel, cattype))

                
for year in yearlist2:
    for cattype in catlist2:
        for channel in channellist:
            for mass in masslist:
                os.system("sh genLimitCondor.sh %s %s %s %s" %(mass, year, channel, cattype))

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
                jdlName = 'submitJobs_%s_%s_%s_%s.jdl'%(year,mass,channel,cattype)
                jdlFile = open('%s/%s'%(jdlDir,jdlName),'w')
                jdlFile.write(common_command)
                #nqueue = subprocess.Popen(['grep -i queue local/%s/%s/Cat1_Inc/Mass%s/condor_run.sub | awk \'{print $2}\''%(year,channel,mass)],shell=True,stdout=subprocess.PIPE).communicate()[0].decode("utf-8")
                run_command =  'Arguments  = %s %s %s %s $(process) %s\nQueue 1\n\n' %(mass,year,channel,cattype,iloop)
                jdlFile.write(run_command)        
                jdlFile.close()
                subFile.write("condor_submit %s\n"%jdlName)

for year in yearlist2:
    for cattype in catlist2:
        for channel in channellist:
            for mass in masslist:
                jdlName = 'submitJobs_%s_%s_%s_%s.jdl'%(year,mass,channel,cattype)
                jdlFile = open('%s/%s'%(jdlDir,jdlName),'w')
                jdlFile.write(common_command)
                #nqueue = subprocess.Popen(['grep -i queue local/%s/%s/Cat1_Inc/Mass%s/condor_run.sub | awk \'{print $2}\''%(year,channel,mass)],shell=True,stdout=subprocess.PIPE).communicate()[0].decode("utf-8")
                run_command =  'Arguments  = %s %s %s %s $(process) %s\nQueue 1\n\n' %(mass,year,channel,cattype,iloop)
                jdlFile.write(run_command)        
                jdlFile.close()
                subFile.write("condor_submit %s\n"%jdlName)
                
subFile.close()

print ("Now run from directory : %s/"%jdlDir)

