from NanoAOD_Gen_Samples import sampleList_2016, sampleList_2017, sampleList_2018
from getFilesFromDisk import getRunList_DAS, getFileList_DAS, getNEvents_DAS, getFileList_EOS

allJobs = 0
allFiles = 0
for year in [2016,2017,2018]:
#for year in [2016]:
    splitJobs = {}
    print '--------------------------'
    print  year 
    print  "nFiles\t  nJobs\t nRuns\t Samples"
    print '--------------------------'
    line = ""

    runListFile = 'runList_%i.txt'%year
    f3 = open(runListFile, "w")

    sampleListTmp = eval("sampleList_%i"%year)
    sampleList = sorted(sampleListTmp.items())
    jobs = 0
    files = 0
    runs = 0
    for sampleName, sample in sampleList:
        line += '%s_FileList_%i="'%(sampleName,year)
        if '/store/user/' in sample:
            fileList = getFileList_EOS(sample)
            line += fileList
            line += '"\n\n'
        else:
            line += "xrootd "
            fileList = getFileList_DAS(sample)
            line += fileList 
            line += '"\n\n'
        nFiles = len(fileList.split(" "))
        files += nFiles
        nJob = 1
        if nFiles >= 5:
            nJob = int (nFiles/5)
        splitJobs[sampleName] = nJob
        jobs += nJob
        runList = getRunList_DAS(sample)
        nRuns = len(runList.split(" ")) - 1
        runs += nRuns
        runlist = runList.split(" ")
        for run in runlist:
            if len(run) > 3:
                f3.write("%s\n"%(str(run)))
        print("%i\t %i\t %i\t %s"%(nFiles, nJob, nRuns, sample))
    print '=================='
    print "AllFiles_%i = %i"%(year, files)
    print "AllJobs_%i = %i"%(year, jobs)
    print "AllRuns_%i = %i"%(year, runs)
    print '=================='
    allFiles += files
    allJobs += jobs

 
