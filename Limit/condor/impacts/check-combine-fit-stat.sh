#!/bin/bash

#dir=iter1_muon_2018
dir=iter0_mu_ele_Run2
index=$1
echo >> summary.txt
# echo >> summary.txt
#for i in 40
#for i in 155 160
for i in 40 50 60 70 80 90 100 110 120 130 140 150 155 160 #all 
do
    fname=$dir/Mass${i}/doFit_updatedtolerances_${index}.log
    nnuisances=`grep "Random number generator seed" $fname | wc -l`
    nfitfails=`grep "MultiDimFit failed" $fname | wc -l`
    nfcrosserrors=`grep "Closed range without finding crossing" $fname | wc -l`
    nminfails=`grep "Minimization failed at" $fname | wc -l`
    echo FILENAME=$fname nof_nuisances : $nnuisances , nof_fit_fails : $nfitfails , nof_crossing_missed : $nfcrosserrors , nof_minimization_fails : $nminfails  >> summary.txt
done
cat summary.txt

# for i in 40 #50 60 70 80 90 100 110 120 130 140 150 155 160 #all 
# do
#     fname=$dir/Mass${i}/doNui_json_${index}.log
#     nminputs=`grep "Missing inputs:" $fname | cut -f 2 -d ':' | tr , '\n' | wc -l`
#     echo FILENAME=$fname missing_inputs : $nminputs 
# done

