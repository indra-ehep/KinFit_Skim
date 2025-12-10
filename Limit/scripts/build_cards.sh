#!/bin/bash

basedir=$PWD

echo Start:`date`
#create minimal exclusive files
for year in 2016 2017 2018
do
    for cat in 1 2 3
    do
	for ch in mu ele
	do
	    for mass in 40 50 60 70 80 90 100 110 120 130 140 150 155 160
	    do
		python3 MyLimitComputerNano.py --ch $ch --cat $cat --mass $mass  --year $year
	    done
	done
    done
done

#build Exc mu_ele
for year in 2016 2017 2018
do
    for cat in ExcL ExcM ExcT
    do
	for mass in 40 50 60 70 80 90 100 110 120 130 140 150 155 160
	do
	    destdir=local/$year/$cat/mu_ele/Cat1_Inc/Mass$mass
	    mudir=local/$year/$cat/mu/Cat1_Inc/Mass$mass
	    eledir=local/$year/$cat/ele/Cat1_Inc/Mass$mass
	    if [ ! -d $destdir ] ; then
		mkdir -p $destdir
	    fi
	    cp $mudir/Shapes*.root $destdir
	    cp $eledir/Shapes*.root $destdir
	    cp $mudir/datacard*.txt $destdir
	    cp $eledir/datacard*.txt $destdir
	    cd $destdir
	    unset array
	    declare -a array
	    ls datacard*.txt > fl.txt
	    nof_file=0
	    while read fname
	    do
		array[$nof_file]=$fname
		nof_file=$[$nof_file+1]
	    done < fl.txt
	    rm fl.txt
	    echo Dir : $destdir ====== files: ${array[@]}
	    combprenom=combine_datacard_hcs_13TeV_mu_ele_Cat1_Inc_WH${mass}
	    combineCards.py ${array[@]} > ${combprenom}.txt
	    text2workspace.py ${combprenom}.txt  -P HiggsAnalysis.CombinedLimit.ChargedHiggs:brChargedHiggs -o t2w_${combprenom}.root
	    cd $basedir
	done
    done
done

# #build Comb per year
for year in 2016 2017 2018
do
    for ch in mu ele mu_ele
    do
	for mass in 40 50 60 70 80 90 100 110 120 130 140 150 155 160
	do
	    destdir=local/$year/Comb/${ch}/Cat1_Inc/Mass$mass
	    excldir=local/$year/ExcL/${ch}/Cat1_Inc/Mass$mass
	    excmdir=local/$year/ExcM/${ch}/Cat1_Inc/Mass$mass
	    exctdir=local/$year/ExcT/${ch}/Cat1_Inc/Mass$mass
	    if [ ! -d $destdir ] ; then
		mkdir -p $destdir
	    fi
	    cp $excldir/Shapes*.root $destdir
	    cp $excmdir/Shapes*.root $destdir
	    cp $exctdir/Shapes*.root $destdir
	    cp $excldir/datacard*.txt $destdir
	    cp $excmdir/datacard*.txt $destdir
	    cp $exctdir/datacard*.txt $destdir
	    cd $destdir
	    unset array
	    declare -a array
	    ls datacard*.txt > fl.txt
	    nof_file=0
	    while read fname
	    do
		array[$nof_file]=$fname
		nof_file=$[$nof_file+1]
	    done < fl.txt
	    rm fl.txt
	    echo Dir : $destdir ====== files: ${array[@]}
	    combprenom=combine_datacard_hcs_13TeV_${ch}_Cat1_Inc_WH${mass}
	    combineCards.py ${array[@]} > ${combprenom}.txt
	    text2workspace.py ${combprenom}.txt  -P HiggsAnalysis.CombinedLimit.ChargedHiggs:brChargedHiggs -o t2w_${combprenom}.root
	    cd $basedir
	done
    done
done


#build Run2 cards
for cat in ExcL ExcM ExcT Comb
do
    for ch in mu ele mu_ele
    do
	for mass in 40 50 60 70 80 90 100 110 120 130 140 150 155 160
	do
	    destdir=local/Run2/$cat/${ch}/Cat1_Inc/Mass$mass
	    y2016dir=local/2016/$cat/${ch}/Cat1_Inc/Mass$mass
	    y2017dir=local/2017/$cat/${ch}/Cat1_Inc/Mass$mass
	    y2018dir=local/2018/$cat/${ch}/Cat1_Inc/Mass$mass
	    if [ ! -d $destdir ] ; then
		mkdir -p $destdir
	    fi
	    cp $y2016dir/Shapes*.root $destdir
	    cp $y2017dir/Shapes*.root $destdir
	    cp $y2018dir/Shapes*.root $destdir
	    cp $y2016dir/datacard*.txt $destdir
	    cp $y2017dir/datacard*.txt $destdir
	    cp $y2018dir/datacard*.txt $destdir
	    cd $destdir
	    unset array
	    declare -a array
	    ls datacard*.txt > fl.txt
	    nof_file=0
	    while read fname
	    do
		array[$nof_file]=$fname
		nof_file=$[$nof_file+1]
	    done < fl.txt
	    rm fl.txt
	    echo Dir : $destdir ====== files: ${array[@]}
	    combprenom=combine_datacard_hcs_13TeV_${ch}_Cat1_Inc_WH${mass}
	    combineCards.py ${array[@]} > ${combprenom}.txt
	    text2workspace.py ${combprenom}.txt  -P HiggsAnalysis.CombinedLimit.ChargedHiggs:brChargedHiggs -o t2w_${combprenom}.root
	    cd $basedir
	done
    done
done
echo End:`date`
