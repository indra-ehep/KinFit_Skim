import itertools
import os
import sys
import subprocess
import time

#IMPORT MODULES FROM OTHER DIR

# samples_2016 = ["HplusM120", "DataMu", "DataEle", "TTbar", "singleTop", "Wjets", "DYjets", "VBFusion", "MCQCDMu", "MCQCDEle"]
# samples_2017 = ["DataEle", "DataMu", "TTbar", "singleTop", "Wjets", "DYjets", "VBFusion", "MCQCDMu", "MCQCDEle"]
# samples_2018 = ["DataMu", "DataEle", "TTbar", "singleTop", "Wjets", "DYjets", "VBFusion", "MCQCDMu", "MCQCDEle"]
samples_2016 = ["HplusM120", "DataMu", "DataEle", "TTbar", "singleTop", "Wjets", "DYjets", "VBFusion"]
samples_2017 = ["DataEle", "DataMu", "TTbar", "singleTop", "Wjets", "DYjets", "VBFusion"]
samples_2018 = ["DataMu", "DataEle", "TTbar", "singleTop", "Wjets", "DYjets", "VBFusion"]
# syst_2016 = ["base", "puup", "pudown", "mueffup", "mueffdown", "eleeffup", "eleeffdown",  "jecup", "jecdown", "jerup", "jerdown", "btagbup", "btagbdown", "btaglup", "btagldown", "prefireup", "prefiredown"]
# syst_2017 = ["base", "puup", "pudown", "mueffup", "mueffdown", "eleeffup", "eleeffdown",  "jecup", "jecdown", "jerup", "jerdown", "btagbup", "btagbdown", "btaglup", "btagldown", "prefireup", "prefiredown"]
# syst_2018 = ["base", "puup", "pudown", "mueffup", "mueffdown", "eleeffup", "eleeffdown",  "jecup", "jecdown", "jerup", "jerdown", "btagbup", "btagbdown", "btaglup", "btagldown"]
syst_2016 = ["base", "puup", "pudown", "mueffup", "mueffdown", "eleeffup", "eleeffdown",  "jerup", "jerdown", "btagbup", "btagbdown", "btaglup", "btagldown", "prefireup", "prefiredown"]
syst_2017 = ["base", "puup", "pudown", "mueffup", "mueffdown", "eleeffup", "eleeffdown",  "jerup", "jerdown", "btagbup", "btagbdown", "btaglup", "btagldown", "prefireup", "prefiredown"]
syst_2018 = ["base", "puup", "pudown", "mueffup", "mueffdown", "eleeffup", "eleeffdown",  "jerup", "jerdown", "btagbup", "btagbdown", "btaglup", "btagldown"]

if not os.path.exists("tmpSubSyst/log"):
    os.makedirs("tmpSubSyst/log")
condorLogDir = "log"
tarFile = "tmpSubSyst/CBA_Skim.tar.gz"
if os.path.exists(tarFile):
	os.system("rm %s"%tarFile)
os.system("tar -zcvf %s ../../CBA_Skim --exclude condor"%tarFile)
os.system("cp runCBASkim.sh tmpSubSyst/")
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
subFile = open('tmpSubSyst/condorSubmit.sh','w')
for year in [2016,2017,2018]:
    sampleList = eval("samples_%i"%year)
    jdlName = 'submitJobs_%s.jdl'%(year)
    jdlFile = open('tmpSubSyst/%s'%jdlName,'w')
    jdlFile.write('Executable =  runCBASkim.sh \n')
    jdlFile.write(common_command)
    condorOutDir1="/eos/user/i/idas/Output/cms-hcs-run2/CBA_Skim_Syst"
    os.system("eos root://eosuser.cern.ch mkdir -p %s/%s"%(condorOutDir1, year))
    condorOutDir="/cms/store/user/idas/Output/cms-hcs-run2/CBA_Skim_Syst"
    os.system("xrdfs root://se01.indiacms.res.in/ mkdir -p %s/%s"%(condorOutDir, year))
    jdlFile.write("X=$(step)\n")
    
    for sample in sampleList:
        
        if sample.find('Data') >=0:
            systList = ["base"]
        else:
            systList = eval("syst_%i"%year)
            
        for syst in systList:
            noflines = subprocess.Popen('wc -l ../input/eos/%i/%s_%i.txt | awk \'{print $1}\''%(year,sample,year),shell=True,stdout=subprocess.PIPE).communicate()[0].split('\n')[0]
            nJob = int(noflines)
            print "%s %s %s"%(sample,nJob,syst)
            if nJob==1:
                run_command =  'Arguments  = %s %s input/eos/%i/%s_%i.txt 0 %s \nQueue 1\n\n' %(year, sample, year, sample, year, syst)
            else:
                run_command =  'Arguments  = %s %s input/eos/%i/%s_%i.txt $INT(X) %s \nQueue %i\n\n' %(year, sample, year, sample, year, syst, nJob)
            jdlFile.write(run_command)
            #print "condor_submit jdl/%s"%jdlFile

    subFile.write("condor_submit %s\n"%jdlName)
    jdlFile.close() 
subFile.close()
