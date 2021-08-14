import itertools
import os
import sys
import subprocess
import time

#IMPORT MODULES FROM OTHER DIR

samples_2016 = ["HplusM120", "DataMu", "DataEle", "TTbar", "singleTop", "Wjets", "DYjets", "VBFusion", "MCQCDMu", "MCQCDEle"]
samples_2017 = ["DataEle", "DataMu", "TTbar", "singleTop", "Wjets", "DYjets", "VBFusion", "MCQCDMu", "MCQCDEle"]
samples_2018 = ["DataMu", "DataEle", "TTbar", "singleTop", "Wjets", "DYjets", "VBFusion", "MCQCDMu", "MCQCDEle"]

if not os.path.exists("tmpSub/log"):
    os.makedirs("tmpSub/log")
condorLogDir = "log"
tarFile = "tmpSub/CBA_Skim.tar.gz"
if os.path.exists(tarFile):
	os.system("rm %s"%tarFile)
os.system("tar -zcvf %s ../../CBA_Skim --exclude condor"%tarFile)
os.system("cp runCBASkim.sh tmpSub/")
common_command = \
'Universe   = vanilla\n\
should_transfer_files = YES\n\
when_to_transfer_output = ON_EXIT\n\
Transfer_Input_Files = CBA_Skim.tar.gz, runCBASkim.sh\n\
x509userproxy = $ENV(X509_USER_PROXY)\n\
use_x509userproxy = true\n\
+BenchmarkJob = True\n\
#+JobFlavour = "testmatch"\n\
+MaxRuntime = 259200\n\
Output = %s/log_$(cluster)_$(process).stdout\n\
Error  = %s/log_$(cluster)_$(process).stderr\n\
Log    = %s/log_$(cluster)_$(process).condor\n\n'%(condorLogDir, condorLogDir, condorLogDir)

#----------------------------------------
#Create jdl files
#----------------------------------------
subFile = open('tmpSub/condorSubmit.sh','w')
for year in [2016,2017,2018]:
    sampleList = eval("samples_%i"%year)
    jdlName = 'submitJobs_%s.jdl'%(year)
    jdlFile = open('tmpSub/%s'%jdlName,'w')
    jdlFile.write('Executable =  runCBASkim.sh \n')
    jdlFile.write(common_command)
    condorOutDir1="/eos/user/i/idas/Output/cms-hcs-run2/CBA_Skim"
    os.system("eos root://eosuser.cern.ch mkdir -p %s/%s"%(condorOutDir1, year))
    condorOutDir="/cms/store/user/idas/Output/cms-hcs-run2/CBA_Skim"
    os.system("xrdfs root://se01.indiacms.res.in/ mkdir -p %s/%s"%(condorOutDir, year))
    jdlFile.write("X=$(step)-1\n")
    
    for sample in sampleList:
        noflines = subprocess.Popen('wc -l ../input/eos/%i/%s_%i.txt | awk \'{print $1}\''%(year,sample,year),shell=True,stdout=subprocess.PIPE).communicate()[0].split('\n')[0]
        nJob = int(noflines)
        print "%s %s"%(sample,nJob)
        if nJob==1:
            run_command =  'Arguments  = %s %s input/eos/%i/%s_%i.txt 0 base \nQueue 1\n\n' %(year, sample, year, sample, year)
        else:
            run_command =  'Arguments  = %s %s input/eos/%i/%s_%i.txt $INT(X) base \nQueue %i\n\n' %(year, sample, year, sample, year, nJob)
        jdlFile.write(run_command)
	#print "condor_submit jdl/%s"%jdlFile
    subFile.write("condor_submit %s\n"%jdlName)
    jdlFile.close() 
subFile.close()
