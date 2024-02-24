#indir=44_trigSF_impacts_bld_excLMT
indir=$1
rsync -avP --include="*/" --include="*.pdf" --exclude="*"  $indir /tmp/v3
rsync -avP --include="*/" --include="combine_*0.txt" --include="combine_*5.txt" --include="Shapes_*.root" --include="t2w_*.root"  --exclude="*"  $indir /tmp/cba_datacard
