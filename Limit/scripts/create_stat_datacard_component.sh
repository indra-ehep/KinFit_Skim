#!/bin/bash

for i in `seq 1 30`
do 
    echo "CMS_stat_cat1_WH_bin_$i     shape  1.00    -        -           -         -         -       -        WH stat bin" 
    echo "CMS_stat_cat1_ttbar_bin_$i  shape  -       1.00     -           -         -         -       -        ttbar stat bin"
    echo "CMS_stat_cat1_wjet_bin_$i   shape  -       -        1.00        -         -         -       -        wjet stat bin"
    echo "CMS_stat_cat1_zjet_bin_$i   shape  -       -        -           1.00      -         -       -        zjet stat bin"
    echo "CMS_stat_cat1_stop_bin_$i   shape  -       -        -           -         1.00      -       -        stop stat bin"
    echo "CMS_stat_cat1_vv_bin_$i     shape  -       -        -           -         -         1.00    -        vv stat bin" 
    echo "CMS_stat_cat1_qcd_bin_$i    shape  -       -        -           -         -         -       1.00     qcddd stat bin"
done
