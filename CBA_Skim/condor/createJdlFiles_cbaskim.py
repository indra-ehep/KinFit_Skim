import itertools
import os
import sys
import subprocess
import time

#IMPORT MODULES FROM OTHER DIR

samples_2016 = ["TTbar", "DataMu", "singleTop", "Wjets", "DYjets", "VBFusion", "MCQCDMu", "MCQCDEle", "DataEle",
                "HplusM040", "HplusM050", "HplusM060", "HplusM070", "HplusM080", "HplusM090", "HplusM100",
                "HplusM110", "HplusM120", "HplusM130", "HplusM140", "HplusM150", "HplusM155", "HplusM160",
                "HminusM040", "HminusM050", "HminusM060", "HminusM070", "HminusM080", "HminusM090", "HminusM100",
                "HminusM110", "HminusM120", "HminusM130", "HminusM140", "HminusM150", "HminusM155", "HminusM160",
                "TTGToLL", "TTGToLNu", "TTGToQQ", "TTHToNonbb", "TTHTobb", "TTHToGG",
                "TTWJetsToLNu", "TTWJetsToQQ", "TTZToLLNuNu", "TTZToQQ"]

syst_2016 = ["base", "iso20", "metup", "metdown",
             "absmpfbup", "abssclup", "absstatup",
             "flavorqcdup", "fragup", "timeptetaup",
             "pudatamcup", "puptbbup", "puptec1up", "puptec2up", "pupthfup", "puptrefup",
             "relfsrup", "relbalup", "relsampleup",
             "reljerec1up", "reljerec2up", "reljerhfup",
             "relptbbup", "relptec1up", "relptec2up", "relpthfup",
             "relstatecup", "relstatfsrup", "relstathfup",
             "singpiecalup", "singpihcalup",
             "absmpfbdown", "absscldown", "absstatdown",
             "flavorqcddown", "fragdown", "timeptetadown",
             "pudatamcdown", "pdowntbbdown", "pdowntec1down", "pdowntec2down", "pdownthfdown", "pdowntrefdown",
             "relfsrdown", "relbaldown", "relsampledown",
             "reljerec1down", "reljerec2down", "reljerhfdown",
             "relptbbdown", "relptec1down", "relptec2down", "relpthfdown",
             "relstatecdown", "relstatfsrdown", "relstathfdown",
             "singpiecaldown", "singpihcaldown"]

syst_long_2016 = ["base", "iso20", "metup", "metdown", "cp5up", "cp5down", "hdampup", "hdampdown", "mtopup", "mtopdown",
                  "absmpfbup", "abssclup", "absstatup",
                  "flavorqcdup", "fragup", "timeptetaup",
                  "pudatamcup", "puptbbup", "puptec1up", "puptec2up", "pupthfup", "puptrefup",
                  "relfsrup", "relbalup", "relsampleup",
                  "reljerec1up", "reljerec2up", "reljerhfup",
                  "relptbbup", "relptec1up", "relptec2up", "relpthfup",
                  "relstatecup", "relstatfsrup", "relstathfup",
                  "singpiecalup", "singpihcalup",
                  "absmpfbdown", "absscldown", "absstatdown",
                  "flavorqcddown", "fragdown", "timeptetadown",
                  "pudatamcdown", "pdowntbbdown", "pdowntec1down", "pdowntec2down", "pdownthfdown", "pdowntrefdown",
                  "relfsrdown", "relbaldown", "relsampledown",
                  "reljerec1down", "reljerec2down", "reljerhfdown",
                  "relptbbdown", "relptec1down", "relptec2down", "relpthfdown",
                  "relstatecdown", "relstatfsrdown", "relstathfdown",
                  "singpiecaldown", "singpihcaldown"]

tunedict = {
    "cp5up" : "CP5up_TTbar",
    "cp5down" : "CP5down_TTbar",
    "hdampup" : "hdampup_TTbar",
    "hdampdown" : "hdampdown_TTbar",
    "mtopup" : "mtopup_TTbar",
    "mtopdown" : "mtopdown_TTbar"
}

jdlDir = 'tmpLog_jecsyst_post'
if not os.path.exists("%s/log"%jdlDir):
    os.makedirs("%s/log"%jdlDir)
condorLogDir = "log"
tarFile = "%s/CBA_Skim.tar.gz"%jdlDir
if os.path.exists(tarFile):
	os.system("rm %s"%tarFile)
os.system("tar -zcvf %s ../../CBA_Skim --exclude condor"%tarFile)
os.system("cp runCBASkim.sh %s/"%jdlDir)
common_command = \
'Universe   = vanilla\n\
should_transfer_files = YES\n\
when_to_transfer_output = ON_EXIT\n\
Transfer_Input_Files = CBA_Skim.tar.gz, runCBASkim.sh\n\
x509userproxy = $ENV(X509_USER_PROXY)\n\
use_x509userproxy = true\n\
+BenchmarkJob = True\n\
#+JobFlavour = "testmatch"\n\
+MaxRuntime = 41220\n\
#+MaxRuntime = 604800\n\
notification = never\n\
MAX_TRANSFER_INPUT_MB = 4096\n\
request_disk = 4000000\n\
Output = %s/log_$(cluster)_$(process).stdout\n\
Error  = %s/log_$(cluster)_$(process).stderr\n\
Log    = %s/log_$(cluster)_$(process).condor\n\n'%(condorLogDir, condorLogDir, condorLogDir)

#----------------------------------------
#Create jdl files
#----------------------------------------
subFile = open('%s/condorSubmit.sh'%jdlDir,'w')
#for year in [2017,2018]:
for year in [2016]:
    sampleList = eval("samples_%i"%year)
    jdlName = 'submitJobs_%s.jdl'%(year)
    jdlFile = open('%s/%s'%(jdlDir,jdlName),'w')
    jdlFile.write('Executable =  runCBASkim.sh \n')
    jdlFile.write(common_command)
    condorOutDir1="/eos/user/i/idas/Output/cms-hcs-run2/CBA_jecsyst/post"
    os.system("eos root://eosuser.cern.ch mkdir -p %s/%s"%(condorOutDir1, year))
    condorOutDir3="/eos/user/d/dugad/idas/Output/cms-hcs-run2/CBA_jecsyst/post"
    os.system("eos root://eosuser.cern.ch mkdir -p %s/%s"%(condorOutDir3, year))
    condorOutDir4="/eos/cms/store/group/phys_b2g/idas/Output/cms-hcs-run2/Result/CBA_jecsyst/post"
    os.system("eos root://eosuser.cern.ch mkdir -p %s/%s"%(condorOutDir4, year))
    
    jdlFile.write("X=$(step)\n")
    
    for sample in sampleList:
        
        if sample.find('Data') >=0:
            systList = ["base", "iso20"]
            #systList = ["base"]
        elif sample.find('TTbar') >=0:
            systList = eval("syst_long_%i"%year)
        else:    
            systList = eval("syst_%i"%year)

        for syst in systList:

            if (syst.find('cp5')>=0 or syst.find('hdamp')>=0 or syst.find('mtop')>=0):
                fnamestart = tunedict[syst]
            else:
                fnamestart = sample

            noflines = subprocess.Popen('wc -l ../input/eos/%i/post/%s_%i.txt | awk \'{print $1}\''%(year,fnamestart,year),shell=True,stdout=subprocess.PIPE).communicate()[0].split('\n')[0]
            nJob = int(noflines)
            print "%s %s %s"%(sample,nJob,syst)
            if nJob==1:
                run_command =  'Arguments  = %s %s input/eos/%i/post/%s_%i.txt 0 %s \nQueue 1\n\n' %(year, sample, year, fnamestart, year, syst)
            else:
                run_command =  'Arguments  = %s %s input/eos/%i/post/%s_%i.txt $INT(X) %s \nQueue %i\n\n' %(year, sample, year, fnamestart, year, syst, nJob)
            jdlFile.write(run_command)
            #print "condor_submit jdl/%s"%jdlFile

    subFile.write("condor_submit %s\n"%jdlName)
    jdlFile.close() 
subFile.close()
