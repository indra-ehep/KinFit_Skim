import sys
import subprocess

def getRunList_DAS(sample):
    std_output, std_error = subprocess.Popen("dasgoclient --query='run dataset=%s'"%sample,shell=True,stdout=subprocess.PIPE,stderr=subprocess.PIPE).communicate()

    names = std_output.decode("ascii").replace('\n',' ')

    if names=='':
        print ("PROBLEM")
        print (sample)
        print ()
    return names

def getFileList_DAS(sample):
    std_output, std_error = subprocess.Popen("dasgoclient --query='file dataset=%s status=*'"%sample,shell=True,stdout=subprocess.PIPE,stderr=subprocess.PIPE).communicate()

    names = std_output.decode("ascii").replace('\n',' ')

    if names=='':
        print ("PROBLEM")
        print (sample)
        print ()
    return names

def getNEvents_DAS(sample):
    std_output, std_error = subprocess.Popen("dasgoclient --query='summary dataset=%s' | cut -d ':' -f 7 | cut -d ',' -f 1"%sample,shell=True,stdout=subprocess.PIPE,stderr=subprocess.PIPE).communicate()

    names = std_output.replace('\n',' ')

    if names=='':
        print ("PROBLEM")
        print (sample)
        print ()
    return names

def getFileList_EOS(sample):
    std_output, std_error = subprocess.Popen("xrdfs root://cmseos.fnal.gov/ ls -u %s | grep '.root'"%sample,shell=True,stdout=subprocess.PIPE,stderr=subprocess.PIPE).communicate()

    names = std_output.decode("ascii").replace('\n',' ')

    if names=='':
        print ("PROBLEM")
        print (sample)
        print ()

    return names

if __name__=="__main__":
    location=sys.argv[1]
    s = sys.argv[2]
    if location=="DAS":
        print (getFileList_DAS(s))
    if location=="EOS":
        print (getFileList_EOS(s))
