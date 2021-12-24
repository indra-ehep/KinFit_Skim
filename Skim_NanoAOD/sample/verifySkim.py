from NanoAOD_Gen_Samples import sampleList_2016, sampleList_2017, sampleList_2018
from getFilesFromDisk import getFileList_DAS, getNEvents_DAS, getFileList_EOS
import subprocess

directory = '/home/idas/t3store3/root_files/Skim_NanoAODUL/2016'

for year in [2016]:
    splitJobs = {}
    print '---------------------------------'
    print  year 
    #print  "nEvents\t  Samples"
    print  "Sample\t  Expected\t  Collected"
    print '---------------------------------'
    line = ""
    sampleListTmp = eval("sampleList_%i"%year)
    sampleList = sorted(sampleListTmp.items())
    for sampleName, sample in sampleList:
        #nevents = getNEvents_DAS(sample)
        fileList = getFileList_DAS(sample)
        nFiles = len(fileList.split(" "))
        nJob = 1
        if nFiles >= 5:
            nJob = int (nFiles/5)
        noffile = subprocess.Popen('find %s -name "%s_Skim_NanoAOD_*of*root" | wc -l'%(directory,sampleName),shell=True,stdout=subprocess.PIPE).communicate()[0].split('\n')
        noffile.remove("")
        #print("%s  %s"%(nevents,sample))
        print("%s  %i  %s"%(sampleName,nJob,noffile[0]))
    print '=================='

 
