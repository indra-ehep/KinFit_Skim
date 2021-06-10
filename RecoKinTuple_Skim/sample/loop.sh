#!/bin/bash

execdir=/home/idas/t3store3/git/KinFit_Skim/RecoKinTuple_Skim 
currdir=$PWD 

while read line 
do
   echo Processing for : $line 
   dir=`echo $line | cut -f 13 -d '/' | cut -f 5 -d '_' | cut -f 1 -d '.'`
   mkdir $dir  
   cd $dir
   ln -s $execdir/src .
   ln -s $execdir/weight .
   ln -s $execdir/sample .
   ln -s $execdir/interface .
   $execdir/makeRecoKinTuple 2016 TTbarPowheg_Hadronic . $line > output_${dir}.log 2>&1 &
   cd $currdir
done < files.txt
