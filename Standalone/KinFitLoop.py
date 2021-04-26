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

mtop = ["161.0", "162.0", "163.0", "164.0", "166.0", "167.0", "168.0", "169.0", "170.0", "171.0", "174.0"]
 
for sampletype in mtop:
    # print ("Processing files for %s of electron..."%sampletype)
    status = subprocess.Popen('./run_root %s  > temp.out 2>&1'%sampletype,shell=True,stdout=subprocess.PIPE).communicate()[0].split('\n')
    print ("Output files created for mtop : %s"%sampletype)


