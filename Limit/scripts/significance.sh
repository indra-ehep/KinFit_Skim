mass=$1
ch=$2

wsname=t2w_combine_datacard_hcs_13TeV_${ch}_Cat1_Inc_WH${mass}.root
#combine $wsname -M MultiDimFit --redefineSignalPOI BR --setParameters BR=0.0 --freezeParameters BR --saveNLL -n _bfit_data -m $mass --cminPreScan  --cminPreFit 3 --cminDefaultMinimizerStrategy 0
combine $wsname -M MultiDimFit --redefineSignalPOI BR --algo=grid --setParameterRanges BR=0.0,1.0 --points 1000 --saveNLL -n _data -m $mass --cminPreScan --cminPreFit 3 --cminDefaultMinimizerStrategy 0 --robustFit 1 #--maxFailedSteps 20 --cminPoiOnlyFit 
