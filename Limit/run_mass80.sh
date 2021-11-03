text2workspace.py combine_datacard_hcs_13TeV_mu_Cat1_Inc_WH80.txt -P HiggsAnalysis.CombinedLimit.ChargedHiggs:brChargedHiggs -o t2w_combine_datacard_hcs_13TeV_mu_Cat1_Inc_WH80.root
combine --rAbsAcc 0.000001 t2w_combine_datacard_hcs_13TeV_mu_Cat1_Inc_WH80.root -M AsymptoticLimits --mass 80 --name _hcs_13TeV_mu_Cat1_Inc
