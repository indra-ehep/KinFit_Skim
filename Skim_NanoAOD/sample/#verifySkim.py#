from NanoAOD_Gen_Samples import sampleList_2016, sampleList_2017, sampleList_2018
from getFilesFromDisk import getFileList_DAS, getNEvents_DAS, getFileList_EOS
import subprocess
import ROOT as rt

directory = '/eos/user/i/idas/Output/cms-hcs-run2/Skim_NanoAODUL/2016'

for year in [2016]:
    splitJobs = {}
    print '----------------------------------------------'
    print  year 
    #print  "nEvents\t  Samples"
    print  "Sample\t  Expected\t  Collected\t  Difference"
    print '----------------------------------------------'
    line = ""
    sampleListTmp = eval("sampleList_%i"%year)
    sampleList = sorted(sampleListTmp.items())
    for sampleName, sample in sampleList:
        nevents = getNEvents_DAS(sample)
        fileList = getFileList_DAS(sample)
        nFiles = len(fileList.split(" "))
        nJob = 1
        if nFiles >= 5:
            nJob = int (nFiles/5)
        filelist = subprocess.Popen('find %s -name "%s_Skim_NanoAOD*.root"'%(directory,sampleName),shell=True,stdout=subprocess.PIPE).communicate()[0].split('\n')
        filelist.remove("")
        nskims = len(filelist)
        
        nofevents = 0;
        for fname in filelist:
            tfile = rt.TFile(fname, 'READ')
            hEvents = tfile.Get('hEvents')
            nofevents += hEvents.GetEntries()/2.0
        evt = int(nevents)
        diffevt = evt - nofevents
        difference = nJob - nskims
        print("%40s\t  %s\t  %i\t %i"%(sampleName, nevents, nofevents, diffevt))
        #print("%50s\t  %i\t  %i\t %i"%(sampleName,nJob,nskims,difference))
    print '======================================================================='

 
