import itertools
import os
import sys
import subprocess
import time

#IMPORT MODULES FROM OTHER DIR

#samples_2016 = ["TTGToLL"]

# samples_2016 = ["TTbar", "DataMu", "DataEle",
#                 "HplusM040", "HplusM050", "HplusM060", "HplusM070", "HplusM080", "HplusM090", "HplusM100",
#                 "HplusM110", "HplusM120", "HplusM130", "HplusM140", "HplusM150", "HplusM155", "HplusM160",
#                 "HminusM040", "HminusM050", "HminusM060", "HminusM070", "HminusM080", "HminusM090", "HminusM100",
#                 "HminusM110", "HminusM120", "HminusM130", "HminusM140", "HminusM150", "HminusM155", "HminusM160",
#                 "singleTop", "Wjets", "DYjets", "VBFusion", "MCQCDMu", "MCQCDEle",
#                 "TTGToLL", "TTGToLNu", "TTGToQQ", "TTHToNonbb", "TTHTobb", "TTHToGG",
#                 "TTWJetsToLNu", "TTWJetsToQQ", "TTZToLLNuNu", "TTZToQQ"]


# samples_2016 = ["TTbar", "DataMu", "DataEle",
#                 "HplusM040", "HplusM050", "HplusM060", "HplusM070", "HplusM080", "HplusM090", "HplusM100",
#                 "HplusM110", "HplusM120", "HplusM130", "HplusM140", "HplusM150", "HplusM155", "HplusM160",
#                 "HminusM040", "HminusM050", "HminusM060", "HminusM070", "HminusM080", "HminusM090", "HminusM100",
#                 "HminusM110", "HminusM120", "HminusM130", "HminusM140", "HminusM150", "HminusM155", "HminusM160",
#                 "singleTop", "Wjets", "DYjets", "VBFusion", "MCQCDMu", "MCQCDEle",
#                 "TTGToLL", "TTGToLNu", "TTGToQQ", "TTHToNonbb", "TTHToGG",
#                 "TTWJetsToLNu", "TTWJetsToQQ", "TTZToLLNuNu", "TTZToQQ"]
# #samples_2016 = ["TTHTobb"]

samples_2016 = ["TTbar", "DataMu", "DataEle",
                "HplusM040", "HplusM050", "HplusM060", "HplusM070", "HplusM080", "HplusM090", "HplusM100",
                "HplusM110", "HplusM120", "HplusM130", "HplusM140", "HplusM150", "HplusM155", "HplusM160",
                "HminusM040", "HminusM050", "HminusM060", "HminusM070", "HminusM080", "HminusM090", "HminusM100",
                "HminusM110", "HminusM120", "HminusM130", "HminusM140", "HminusM150", "HminusM155", "HminusM160",
                "singleTop", "Wjets", "DYjets", "VBFusion", "MCQCDMu", "MCQCDEle",
                "TTGToLL", "TTGToLNu", "TTGToQQ", "TTHToGG",
                "TTWJetsToQQ", "TTZToLLNuNu", "TTZToQQ"]
# #samples_2016 = ["TTHToNonbb", "TTHTobb", "TTWJetsToLNu"]


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
             "pudatamcdown", "puptbbdown", "puptec1down", "puptec2down", "pupthfdown", "puptrefdown",
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
                  "pudatamcdown", "puptbbdown", "puptec1down", "puptec2down", "pupthfdown", "puptrefdown",
                  "relfsrdown", "relbaldown", "relsampledown",
                  "reljerec1down", "reljerec2down", "reljerhfdown",
                  "relptbbdown", "relptec1down", "relptec2down", "relpthfdown",
                  "relstatecdown", "relstatfsrdown", "relstathfdown",
                  "singpiecaldown", "singpihcaldown"]

inputdir="CBA_jecsyst"
outputdir="CBA_jecsyst-BJetHist1"
iosubdir="post"

refpath='/eos/user/i/idas/Output/cms-hcs-run2/%s/%s'%(inputdir,iosubdir)
bjetpath='/eos/user/d/dugad/idas/Output/cms-hcs-run2/%s/%s'%(inputdir,iosubdir)

for year in [2016]:
    os.system("if [ ! -d ../input/%s/post ] ; then mkdir -p ../input/%s/post ; fi"%(year,year))
    os.system("rm -f ../input/%s/post/*"%year)
    sampleList = eval("samples_%i"%year)
    for sample in sampleList:

        if sample.find('Data') >=0:
            systList = ["base", "iso20"]
        elif sample.find('TTbar') >=0:
            systList = eval("syst_long_%i"%year)
        else:    
            systList = eval("syst_%i"%year)

        for syst in systList:
            inputfile = '../input/%s/post/%s_%s_bjet.txt'%(year, sample, syst)
            os.system('for i in `xrdfs root://eosuser.cern.ch ls %s/%s | grep %s | grep \"_%s_\" | grep -v \".sys.v\"` ; do echo root://eosuser.cern.ch/$i >> %s ; done '%(bjetpath, year, sample, syst, inputfile))
            print("Creating input file %s"%inputfile)


jdlDir = 'btag_tmpLog_%s_%s'%(outputdir,iosubdir)
if not os.path.exists("%s/log"%jdlDir):
    os.makedirs("%s/log"%jdlDir)
condorLogDir = "log"
tarFile = "%s/Hist_CBA.tar.gz"%jdlDir
if os.path.exists(tarFile):
    os.system("rm %s"%tarFile)
os.system("tar --exclude='condor/*' -zcvf %s ../../Hist_CBA "%tarFile)
os.system("cp runBJetCBA.sh %s/"%jdlDir)

common_command = \
'Universe   = vanilla\n\
should_transfer_files = YES\n\
when_to_transfer_output = ON_EXIT\n\
Transfer_Input_Files = Hist_CBA.tar.gz, runBJetCBA.sh\n\
x509userproxy = $ENV(X509_USER_PROXY)\n\
use_x509userproxy = true\n\
+BenchmarkJob = True\n\
#+MaxRuntime = 41220\n\
+MaxRuntime = 7200\n\
Output = %s/log_$(cluster)_$(process).stdout\n\
Error  = %s/log_$(cluster)_$(process).stderr\n\
Log    = %s/log_$(cluster)_$(process).condor\n\n'%(condorLogDir, condorLogDir, condorLogDir)

totjobs = 0
#----------------------------------------
#Create jdl files
#----------------------------------------
subFile = open('%s/condorSubmit.sh'%jdlDir,'w')
samplesubFile = open('%s/condorSampleSubmit.sh'%jdlDir,'w')
for year in [2016]:
    sampleList = eval("samples_%i"%year)
    jdlName = 'submitJobs_%s.jdl'%(year)
    jdlFile = open('%s/%s'%(jdlDir,jdlName),'w')
    jdlFile.write('Executable =  runBJetCBA.sh \n')
    jdlFile.write(common_command)
    condorOutDir='/eos/user/d/dugad/idas/Output/cms-hcs-run2/%s/%s'%(outputdir,iosubdir)
    os.system("xrdfs root://eosuser.cern.ch mkdir -p %s/%s"%(condorOutDir, year))
    condorOutDir1='/eos/cms/store/group/phys_b2g/idas/Output/cms-hcs-run2/Result/%s/%s'%(outputdir,iosubdir)
    os.system("xrdfs root://eosuser.cern.ch mkdir -p %s/%s"%(condorOutDir1, year))

    jdlFile.write("X=$(step)\n")
    
    for sample in sampleList:

        subjdlName = 'submit_%s_%s.jdl'%(sample,year)
        subjdlFile = open('%s/%s'%(jdlDir,subjdlName),'w')
        subjdlFile.write('Executable =  runBJetCBA.sh \n')
        subjdlFile.write(common_command)
        subjdlFile.write("X=$(step)\n")

        reffile = 'root://eosuser.cern.ch/%s/%s/all/all_%s.root'%(refpath,year,sample)
        print("Reffile %s"%reffile)
        
        if sample.find('Data') >=0:
            systList = ["base", "iso20"]
        elif sample.find('TTbar') >=0:
            systList = eval("syst_long_%i"%year)
        else:    
            systList = eval("syst_%i"%year)

        for syst in systList:
            
            inputfile = '../input/%s/post/%s_%s_bjet.txt'%(year, sample, syst)
            noflines = subprocess.Popen('wc -l %s | awk \'{print $1}\''%(inputfile),shell=True,stdout=subprocess.PIPE).communicate()[0].split(b'\n')[0]
            nJob = int(noflines)
            totjobs += nJob
            print("%s %s %s"%(sample,nJob,syst))
            if nJob==1:
                run_command =  'Arguments  = %s %s input/%s/post/%s_%s_bjet.txt 0 %s %s\nQueue 1\n\n' %(year, sample, year, sample, syst, syst, reffile)
            else:
                run_command =  'Arguments  = %s %s input/%s/post/%s_%s_bjet.txt $INT(X) %s %s\nQueue %i\n\n' %(year, sample, year, sample, syst, syst, reffile, nJob)
            jdlFile.write(run_command)
            subjdlFile.write(run_command)
            #print("condor_submit jdl/%s"%jdlFile
            
        samplesubFile.write("condor_submit %s\n"%subjdlName)
    subFile.write("condor_submit %s\n"%jdlName)
    jdlFile.close() 
subFile.close()
print("Total number of jobs to be submitted is %s"%(totjobs))
