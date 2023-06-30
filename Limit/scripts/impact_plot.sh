t2wDataCard=$1
mass=$2

######################################## Impacts ############################################
#combineTool.py -M Impacts -d $t2wDataCard -m $mass --doInitialFit --robustFit 1 -t -1 --redefineSignalPOIs BR --setParameterRanges BR=0,0.1 | tee doInitialFit.log 
#combineTool.py -M Impacts -d $t2wDataCard -m $mass --doFit --robustFit 1 -t -1 --redefineSignalPOIs BR --setParameterRanges BR=0,0.1 --parallel 3 | tee doFit.log

# #AN
# combineTool.py -M Impacts -d $t2wDataCard -m $mass --doInitialFit --robustFit 1 --redefineSignalPOIs BR --setParameterRanges BR=0,1.0 --cminDefaultMinimizerStrategy 0 | tee doInitialFit.log 
# combineTool.py -M Impacts -d $t2wDataCard -m $mass --doFit --robustFit 1 --redefineSignalPOIs BR --setParameterRanges BR=0,1.0 --cminDefaultMinimizerStrategy 0  --parallel 8 | tee doFit.log

#toy
# combineTool.py -M Impacts -d $t2wDataCard -m $mass --doInitialFit --robustFit 1 --redefineSignalPOIs BR --setParameterRanges BR=-1,1  -t -1 | tee doInitialFit.log 
# combineTool.py -M Impacts -d $t2wDataCard -m $mass --doFit --robustFit 1 --redefineSignalPOIs BR --setParameterRanges BR=-1,1.0 --parallel 3 -t -1 | tee doFit.log

# #test
# combineTool.py -M Impacts -d $t2wDataCard -m $mass --doInitialFit --robustFit 1  --redefineSignalPOIs BR --setParameterRanges BR=0.0,1.0  -t -1 | tee doInitialFit.log 
# combineTool.py -M Impacts -d $t2wDataCard -m $mass --doFit --robustFit 1  --redefineSignalPOIs BR --setParameterRanges BR=0.0,1.0 --parallel 16 -t -1 | tee doFit.log

#test1 no parameter range
combineTool.py -M Impacts -d $t2wDataCard -m $mass --doInitialFit --robustFit 1  --redefineSignalPOIs BR --setParameterRanges BR=-1.0,1.0 -t -1 | tee doInitialFit.log 
combineTool.py -M Impacts -d $t2wDataCard -m $mass --doFit --robustFit 1  --redefineSignalPOIs BR --setParameterRanges BR=-1.0,1.0 --parallel 7 -t -1 | tee doFit.log

combineTool.py -M Impacts -d $t2wDataCard -m $mass -o nuisImpactJSON 
plotImpacts.py --cms-label "Internal" -i nuisImpactJSON -o nuisImpactPDF

######################################## Nuisance parameter pulls / Fit dianostics ############################################
# AN
# combine $t2wDataCard -m $mass -M FitDiagnostics --expectSignal 1 --redefineSignalPOIs BR --setParameterRanges BR=0,1.0 --plots --saveShapes --saveWithUncertainties --saveNormalizations --cminDefaultMinimizerStrategy 0
# python diffNuisances.py -a fitDiagnostics.root --poi=BR -g fitDiag.pdf

# https://twiki.cern.ch/twiki/bin/viewauth/CMS/HiggsWG/HiggsPAGPreapprovalChecks
# combine -M FitDiagnostics -t -1 --expectSignal 0
# python diffNuisances.py -a fitDiagnostics.root -g plots.root

#combine $t2wDataCard -m $mass -M FitDiagnostics -t -1 --expectSignal 1 --redefineSignalPOIs BR --setParameterRanges BR=-1.0,1.0 --plots --saveShapes --saveWithUncertainties --saveNormalizations --cminDefaultMinimizerStrategy 0 --robustFit=1 --stepSize=0.001 --minos none --ignoreCovWarning

#combine $t2wDataCard -m $mass -M FitDiagnostics  --expectSignal 1 --redefineSignalPOIs BR --setParameterRanges BR=-0.5,0.5 -t -1 --plots --saveShapes --saveWithUncertainties --saveNormalizations --cminDefaultMinimizerStrategy 0 

# python3 $CMSSW_BASE/src/HiggsAnalysis/CombinedLimit/data/tutorials/longexercise/diffNuisances.py -a fitDiagnosticsTest.root --poi=BR -g pull_result.root
# cp pull_result.root /tmp/pull_result.root

######################################## Scan parameters ############################################

# fname=pararray.txt 
# if [ -f $fname ] ; then
#     rm $fname 
# fi
# for ifile in `ls higgsCombine_paramFit_Test_*.root`
# do 
#     ininame=`echo $ifile | cut -d '.' -f 1` 
#     nuiname1=`echo $ininame | awk -F_ '{for(i=4;i<=NF-1;i++) printf "%s_", $i;}'`
#     nuiname2=`echo $ininame | awk -F_ '{for(i=NF;i<=NF;i++) printf "%s", $i;}'` 
#     echo ${nuiname1}${nuiname2} >> $fname 
# done

# while read parname
# do
#     echo "Scanning for parameter : $parname"
#     #combine $t2wDataCard -M MultiDimFit -m $mass --redefineSignalPOIs BR --setParameterRanges BR=-1.,1. -P $parname  --trackParameters BR --algo grid --name _scan_$parname
#     combine $t2wDataCard -M MultiDimFit -m $mass --redefineSignalPOIs BR --setParameterRanges BR=-1.,1. -t -1 -P $parname  --trackParameters BR --algo grid --name _scan_$parname
# done < $fname
# #rm $fname

#combine $t2wDataCard -M MultiDimFit -m 80 --redefineSignalPOIs BR --setParameterRanges BR=-1.,1. -P CMS_norm_tt --trackParameters BR --algo grid -n CMS_norm_tt
# root higgsCombineCMS_norm_tt.MultiDimFit.mH80.root
# TTree *limit = (TTree *)_file0->Get("limit")
# limit->Draw("deltaNLL:CMS_norm_tt")

######################################## Goodness of fit ############################################

# combine $t2wDataCard -M GoodnessOfFit -m $mass --algo saturated 
# combine $t2wDataCard -M GoodnessOfFit -m $mass --algo saturated -t 1000 -s 1234
