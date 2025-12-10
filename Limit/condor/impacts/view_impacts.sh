#!/bin/bash

#dir=iter1_muon_2016
dir=$1
index=226
unset array
declare -a array
iarr=0

for i in 40 50 60 70 80 90 100 110 120 130 140 150 155 160 #all
#for i in 40 #all
#for i in 40 50 60 70 90 100 110 120 130 140 150 155 #all
do
    prenom=nuisImpactPDF_mu_ele_${i}_newtolarances_${index}
    fname=$dir/Mass${i}/${prenom}.pdf
    #evince $fname &
    pdfseparate $fname /tmp/${prenom}_%d.pdf
    array[$iarr]=/tmp/${prenom}_1.pdf
    iarr=$[$iarr+1]
done
echo array : ${array[@]}
pdfunite ${array[@]} /tmp/impact_summary_${index}.pdf
evince /tmp/impact_summary_${index}.pdf &

