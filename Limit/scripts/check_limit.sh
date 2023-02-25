datacard=$1
mass=$2
text2workspace.py $datacard -P HiggsAnalysis.CombinedLimit.ChargedHiggs:brChargedHiggs -o t2w.root
#combineCards.py datacard_ExcL_test.txt datacard_ExcM_test.txt datacard_ExcT_test.txt > datacard_ExcLMT_test.txt
combine --rAbsAcc 0.000001 --run blind t2w.root -M AsymptoticLimits --mass $mass
root -l -b -q /Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/limit/codes/ReadLimit.C\($mass\)
