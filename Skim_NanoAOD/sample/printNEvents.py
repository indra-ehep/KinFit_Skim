from NanoAOD_Gen_Samples import sampleList_2016, sampleList_2017, sampleList_2018
from getFilesFromDisk import getRunList_DAS, getFileList_DAS, getNEvents_DAS, getFileList_EOS
import subprocess
import ROOT as rt

for year in [2018]:
    splitJobs = {}
    print '----------------------------------------------'
    print  year 
    #print  "nEvents\t  Samples"
    print  "\t\t\t\tSample\t  NEvents"
    print '----------------------------------------------'
    line = ""
    sampleListTmp = eval("sampleList_%i"%year)
    sampleList = sorted(sampleListTmp.items())
    for sampleName, sample in sampleList:
        nevents = getNEvents_DAS(sample)
        print("%150s\t  %s"%(sample, nevents))
        #print("%50s\t  %i\t  %i\t %i"%(sampleName,nJob,nskims,difference))
    print '======================================================================='

 
