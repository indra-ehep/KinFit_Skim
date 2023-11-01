from NanoAOD_Gen_Samples import sampleList_2016, sampleList_2017, sampleList_2018
from getFilesFromDisk import getFileList_DAS, getNEvents_DAS, getFileList_EOS

totevents = 0;
for year in [2016,2017,2018]:
    splitJobs = {}
    print '--------------------------'
    print  year 
    print  "Samples\t nEvents"
    print '--------------------------'
    line = ""
    sampleListTmp = eval("sampleList_%i"%year)
    sampleList = sorted(sampleListTmp.items())
    for sampleName, sample in sampleList:
        nevents = getNEvents_DAS(sample)
        evt = int(float(nevents))
        totevents += evt
        print("%40s  %s"%(sample, nevents))
    print '=================='
print("Total events produced : %i"%totevents)
print '=================='
