rsync -avP --include="*/" --include="*.pdf" --exclude="*"  44_trigSF_impacts_bld_excLMT /tmp/v3
rsync -avP --include="*/" --include="combine_*0.txt" --include="combine_*5.txt" --include="Shapes_*.root" --include="t2w_*.root"  --exclude="*"  44_trigSF_impacts_bld_excLMT /tmp/cba_datacard
