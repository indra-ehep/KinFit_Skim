indir=$1
logfile=/tmp/limit_out.log

if [ -f $logfile ] ; then
    rm $logfile
fi

echo "\centering\cmsTable{" > sec08_limit_excY_2016-8.tex
for year in 2016 2017 2018   
do
    echo "\centering\cmsTable{" > sec08_limit_excLMT_${year}.tex
    for excType in ExcL ExcM ExcT
    do
	dir=$indir/$year/$excType/
	echo Processing for dir : $dir
	root -l -b -q codes/LoopLimitPlotsNano.C+\(\""$dir"\"\) >> $logfile 
	cat $dir/limit.tex >> sec08_limit_excLMT_${year}.tex
    done
    echo "}" >> sec08_limit_excLMT_${year}.tex

    dir=$indir/$year/Comb/
    echo Processing for dir : $dir
    root -l -b -q codes/LoopLimitPlotsNano.C+\(\""$dir"\"\) >> $logfile 
    cat $dir/limit.tex >> sec08_limit_excY_2016-8.tex

done
echo "}" >> sec08_limit_excY_2016-8.tex

echo "\centering\cmsTable{" > sec08_limit_Comb_Run2.tex
dir=$indir/Run2/Comb/
echo Processing for dir : $dir
root -l -b -q codes/LoopLimitPlotsNano.C+\(\""$dir"\"\) >> $logfile 
cat $dir/limit.tex >> sec08_limit_Comb_Run2.tex

echo "\begin{tabular}{ccccccc}
     \multicolumn{7}{c}{2016 : published}\\\\\\hline
      \multirow{2}{*}{\$m_{H^+}\$ (GeV)} & \multicolumn{5}{c}{Expected} & \multirow{2}{*}{Observed} \\\\
      & \$-2\sigma\$ & \$-1\sigma\$ & median & \$+1\sigma\$ & \$+2\sigma\$ & \\\\
    \hline
    80  & 1.29 & 1.72 & 2.39 & 3.36 & 4.50 & 1.68\\\\
    90  & 0.54 & 0.72 & 0.99 & 1.38 & 1.84 & 0.60\\\\
    100 & 0.28 & 0.37 & 0.51 & 0.71 & 0.94 & 0.25\\\\
    120 & 0.19 & 0.25 & 0.35 & 0.49 & 0.64 & 0.25\\\\
    140 & 0.17 & 0.22 & 0.31 & 0.42 & 0.56 & 0.28\\\\
    150 & 0.16 & 0.21 & 0.29 & 0.41 & 0.54 & 0.26\\\\
    155 & 0.16 & 0.21 & 0.29 & 0.41 & 0.54 & 0.28\\\\
    160 & 0.17 & 0.23 & 0.32 & 0.45 & 0.61 & 0.29\\\\\\hline
 \end{tabular}" >> sec08_limit_Comb_Run2.tex

echo "}" >> sec08_limit_Comb_Run2.tex
