t2wDataCard=$1
mass=$2
#combineTool.py -M Impacts -d $t2wDataCard -m $mass --doInitialFit --robustFit 1 -t -1 --redefineSignalPOIs BR --setParameterRanges BR=0,0.1 | tee doInitialFit.log 
#combineTool.py -M Impacts -d $t2wDataCard -m $mass --doFit --robustFit 1 -t -1 --redefineSignalPOIs BR --setParameterRanges BR=0,0.1 --parallel 3 | tee doFit.log

# #AN
# combineTool.py -M Impacts -d $t2wDataCard -m $mass --doInitialFit --robustFit 1 --redefineSignalPOIs BR --setParameterRanges BR=0,0.1 --cminDefaultMinimizerStrategy 0 | tee doInitialFit.log 
# combineTool.py -M Impacts -d $t2wDataCard -m $mass --doFit --robustFit 1 --redefineSignalPOIs BR --setParameterRanges BR=0,0.1 --cminDefaultMinimizerStrategy 0  --parallel 3 | tee doFit.log

#AN
# combineTool.py -M Impacts -d $t2wDataCard -m $mass --doInitialFit --robustFit 1 --setParameterRanges r=-10.,10. --cminDefaultMinimizerStrategy 0 | tee doInitialFit.log 
# combineTool.py -M Impacts -d $t2wDataCard -m $mass --doFit --robustFit 1 --setParameterRanges r=-10.,10. --cminDefaultMinimizerStrategy 0  --parallel 3 | tee doFit.log

#toy
# combineTool.py -M Impacts -d $t2wDataCard -m $mass --doInitialFit --robustFit 1 --redefineSignalPOIs BR --setParameterRanges BR=-1,1  -t -1 | tee doInitialFit.log 
# combineTool.py -M Impacts -d $t2wDataCard -m $mass --doFit --robustFit 1 --redefineSignalPOIs BR --setParameterRanges BR=-1,1.0 --parallel 3 -t -1 | tee doFit.log

#test
combineTool.py -M Impacts -d $t2wDataCard -m $mass --doInitialFit --robustFit 1  --redefineSignalPOIs BR --setParameterRanges BR=0.0,1.0  -t -1 | tee doInitialFit.log 
combineTool.py -M Impacts -d $t2wDataCard -m $mass --doFit --robustFit 1  --redefineSignalPOIs BR --setParameterRanges BR=0.0,1.0 --parallel 7 -t -1 | tee doFit.log

combineTool.py -M Impacts -d $t2wDataCard -m $mass -o nuisImpactJSON 
plotImpacts.py --cms-label "Internal" -i nuisImpactJSON -o nuisImpactPDF

