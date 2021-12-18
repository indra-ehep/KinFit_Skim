import sys
import os
import subprocess
import time

def check_int(s):
    isInt = True
    try:
        # converting to integer
        int(s)
    except ValueError:
        isInt = False
    return isInt

def check_float(s):
    isFloat = True
    try:
        # converting to integer
        float(s)
    except ValueError:
        isFloat = False
    return isFloat
 
#directory = '/Data/root_files/AOD_files/NanoAOD_framework/Skim_nanoAOD/'
#directory = '/run/media/indra/DHEP_Storage_1/Data/NanoAOD/Skim_NanoAOD/2016'

tree_tuple = ("Events", "RecoNtuple_Skim")
hist1_tuple = ("Muon_pt" ,"muPt")
hist2_tuple = ("Electron_pt", "elePt")
root_filetype = 1 # 1 for skim and 2 for reco

storage_type=int(raw_input("Type 1 to scan files from local storage or 2 if you want to scan from xrootd storage or 3 if you want to scan eos storage\n"))

if storage_type == 1:
    directory = raw_input("You have selected local storage. Please enter the directory path\n")
elif storage_type == 2:
    server = raw_input("You have selected xrootd storage. Please enter the servername such as root://se01.indiacms.res.in \n")
    directory = raw_input("Please enter the directory path\n")
elif storage_type == 3:
    directory = raw_input("You have selected eos storage. Please enter the directory path\n")

if storage_type == 1:
    filelist = subprocess.Popen('find %s -name "*root"'%directory,shell=True,stdout=subprocess.PIPE).communicate()[0].split('\n')
elif storage_type == 2:
    filelist = subprocess.Popen('xrdfs %s ls -R %s | grep root'%(server,directory),shell=True,stdout=subprocess.PIPE).communicate()[0].split('\n')
elif storage_type == 3:
    filelist = subprocess.Popen('find %s -name "*root"'%directory,shell=True,stdout=subprocess.PIPE).communicate()[0].split('\n')

filelist.remove("")
nFiles = len(filelist)

dir_list = directory.split('/') 
last_dir_name = dir_list[len(dir_list)-1]
prev_to_last_dir = dir_list[len(dir_list)-2]
filestat = ""

flist = []

for fname in filelist:
    dir_list = fname.split('/') 
    last_file_name = dir_list[len(dir_list)-1]
    flist.append(last_file_name)
    #print (last_file_name)

flist.sort()

print "The first entry is : %s "%flist[0]
 
if flist[0].find('_Skim_NanoAOD_') >= 0 and flist[0].find('.root') >= 0: 
    root_filetype = 1
elif flist[0].find('_RecoNtuple_Skim_') >= 0 and flist[0].find('.root') >= 0: 
    root_filetype = 2

#print (flist)

print ("Total number of files to be scanned is : %i"%nFiles)
print "Directory|  filename|  filesize (in bytes)|  tree entries| mu hist entries|  mean mu pt|  mu hist underflow|  mu hist overflow| ele hist entries|  mean ele pt|  ele hist underflow|  ele hist overflow"
i = 0
for fname in flist:
    i += 1
    # if i%30 == 0: 
    #     print "Processing filenumber : %i of %i"%(i,nFiles) 

    if storage_type == 1 or storage_type == 3:
        file_size = subprocess.check_output('ls -la %s/%s | awk \'{print $5}\''%(directory,fname),shell=True).split('\n')
        outlist = subprocess.Popen('tree_list %s %s/%s 2>&1'%(root_filetype,directory,fname),shell=True,stdout=subprocess.PIPE).communicate()[0].split('\n')
    elif storage_type == 2:
        #file_size = subprocess.check_output('xrdfs root://se01.indiacms.res.in ls -l /cms/store/user/idas/Output/cms-hcs-run2/Skim_NanoAOD/2018/ | grep ZZTo4L_powheg_ext2_Skim_NanoAOD_9of14.root | | awk \'{print $4}\''%(directory,fname),shell=True).split('\n')
        file_size = subprocess.check_output('xrdfs %s ls -l %s | grep %s | awk \'{print $4}\''%(server,directory,fname),shell=True).split('\n')
        outlist = subprocess.Popen('tree_list %s %s/%s/%s 2>&1'%(root_filetype, server,directory,fname),shell=True,stdout=subprocess.PIPE).communicate()[0].split('\n')
    #print (outlist)
    tree_size = ""
    mu_pt_entries = ""
    mu_pt_mean = ""
    mu_pt_oflow = ""
    mu_pt_uflow = ""
    ele_pt_entries = ""
    ele_pt_mean = ""
    ele_pt_uflow = ""
    ele_pt_oflow = ""
    for out in outlist:
        search_string = "Tree  " + str(tree_tuple[root_filetype-1])  + " has Entries"
        if out.find(search_string) >= 0:
            wordlist = out.split(':')
            if check_int(wordlist[1]):
                tree_size=int(wordlist[1])
        search_string = "Histogram  " + str(hist1_tuple[root_filetype-1])  + " has Entries"
        if out.find(search_string) >= 0:
            wordlist = out.split(':')
            if check_float(wordlist[1]):
                mu_pt_entries=wordlist[1]
            if check_float(wordlist[3]):
                mu_pt_mean=wordlist[3]
            if check_float(wordlist[5]):
                mu_pt_uflow=wordlist[5]
            if check_float(wordlist[7]):
                mu_pt_oflow=wordlist[7]
        search_string = "Histogram  " + str(hist2_tuple[root_filetype-1])  + " has Entries"
        if out.find(search_string) >= 0:
            wordlist = out.split(':')
            if check_float(wordlist[1]):
                ele_pt_entries=wordlist[1]
            if check_float(wordlist[3]):
                ele_pt_mean=wordlist[3]
            if check_float(wordlist[5]):
                ele_pt_uflow=wordlist[5]
            if check_float(wordlist[7]):
                ele_pt_oflow=wordlist[7]
            
    print "%s| %s| %s| %s| %s| %s| %s| %s| %s| %s| %s| %s"%(directory, fname, file_size[0], tree_size, mu_pt_entries, mu_pt_mean, mu_pt_uflow, mu_pt_oflow, ele_pt_entries, ele_pt_mean, ele_pt_uflow, ele_pt_oflow)
    filestat += directory + "| " + fname + "| " + str(file_size[0]) + "| " + str(tree_size) + "| " + str(mu_pt_entries) + "| " + str(mu_pt_mean) + "| " + str(mu_pt_uflow) + "| " + str(mu_pt_oflow )+ "| " + str(ele_pt_entries) + "| " + str(ele_pt_mean) + "| " + str(ele_pt_uflow) + "| " + str(ele_pt_oflow) + "\n"

    
localts = time.localtime()

local_d = "%i-%02i-%02i"%(localts.tm_year, localts.tm_mon, localts.tm_mday)
local_dt = "%s__%02i%02i%02i"%(local_d, localts.tm_hour, localts.tm_min, localts.tm_sec)
if storage_type == 1:
    outpath =  "/Data/root_files/file_stat/Local" + "/" + local_d + "/" + prev_to_last_dir + "/" + last_dir_name
elif storage_type == 2:
    outpath = "/home/idas/t3store3/root_files/file_stat" + "/" + local_d + "/" + prev_to_last_dir + "/" + last_dir_name
elif storage_type == 3:
    outpath = "/afs/cern.ch/work/i/idas/root_files/file_stat" + "/" + local_d + "/" + prev_to_last_dir + "/" + last_dir_name
    
if not os.path.exists(outpath):
    os.makedirs(outpath)
    print ("Output directory %s has been created"%outpath)
else:
    print ("Output directory %s exists"%outpath)
    
fstat_filename = '%s/filestat_%s_%s_%s.txt'%(outpath, prev_to_last_dir, last_dir_name, local_dt)
fstat = open(fstat_filename,'w')
fstat.write(filestat)
fstat.close()

print "See final result in  file %s "%(fstat_filename)
