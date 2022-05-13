## Motivation

In this folder, we process the Skim files and apply various corrections and scale factors. 
The final outputs are stored as TH1 and TTree objects in separate files.
The codes `SkimAna.C` and `SkimAna.h` are the central codes that call other classes and methods to perform the main tasks.

We first show how to quick start the analysis and then describe the list of important codes and processing flow.

---
## Quick Start

### Local processing

Once the repository is downloaded in a `lxplus` machine, the skim file processing can be in three simple steps.

1. CMSSW : Set the environment for CMSSW. The CMSSW_X_X_X can be created in other location irrespective of the download directory of current project. Since we are using `correctionlib` for reading the json files, we use CMSSW_12_1_X as per suggestion at ![link](https://cms-nanoaod.github.io/correctionlib/install.html#inside-cmssw). 

   ```console
   export SCRAM_ARCH=slc7_amd64_gcc900
   source /cvmfs/cms.cern.ch/cmsset_default.sh
   scramv1 project CMSSW CMSSW_12_1_0
   cd CMSSW_12_1_0/src
   cmsenv
   ```

2. Compile : Now change directory to downloaded KinFit_Skim/CBA_Skim folder and run the following command.
   ```console
   [idas@lxplus7113 CBA_Skim]$ make
   ```

   <details>
         <summary markdown="span"> Click to check expected output.</summary>
   
   
	 ```console	 
	 g++ -fPIC -g  -c `root-config --libs` -I`root-config --incdir` -std=c++17 -D STANDALONE src/FactorizedJetCorrector.cpp -o src/FactorizedJetCorrector.o
	 g++ -fPIC -g  -c `root-config --libs` -I`root-config --incdir` -std=c++17 -D STANDALONE src/JetCorrectorParameters.cpp -o src/JetCorrectorParameters.o
	 g++ -fPIC -g  -c `root-config --libs` -I`root-config --incdir` -std=c++17 -D STANDALONE src/SimpleJetCorrector.cpp -o src/SimpleJetCorrector.o
	 g++ -fPIC -g  -c `root-config --libs` -I`root-config --incdir` -std=c++17 -D STANDALONE src/JetCorrectionUncertainty.cpp -o src/JetCorrectionUncertainty.o 
	 g++ -fPIC -g  -c `root-config --libs` -I`root-config --incdir` -std=c++17 -D STANDALONE src/SimpleJetCorrectionUncertainty.cpp -o src/SimpleJetCorrectionUncertainty.o
	 g++ -fPIC -g  -c `root-config --libs` -I`root-config --incdir` -std=c++17 -D STANDALONE src/JECvariation.cpp -o src/JECvariation.o
	 g++ -fPIC -g  -c `root-config --libs` -I`root-config --incdir` -std=c++17 -D STANDALONE src/JetResolutionObject.cc -o src/JetResolutionObject.o
	 g++ -fPIC -g  -c `root-config --libs` -I`root-config --incdir` -std=c++17 -D STANDALONE src/JetResolution.cc -o src/JetResolution.o
	 g++ -fPIC -g  -c -I`root-config --incdir` -std=c++17 -D STANDALONE src/EventTree.cpp -o src/EventTree.o
	 g++ -fPIC -g  -c -I`root-config --incdir` -std=c++17 -D STANDALONE src/Selector.cpp -o src/Selector.o
	 g++ -fPIC -g  -c -I`root-config --incdir` -std=c++17 -D STANDALONE src/EventPick.cpp -o src/EventPick.o
	 g++ -fPIC -g  -c `root-config --libs` -I`root-config --incdir` -std=c++17 -D STANDALONE src/RoccoR.cc -o src/RoccoR.o
	 g++ -fPIC -g  -c -I`root-config --incdir` -std=c++17 -D STANDALONE src/PUReweight.cpp -o src/PUReweight.o
	 g++ -fPIC -g  -c -I`root-config --incdir` -std=c++17 -D STANDALONE src/BTagCalibrationStandalone.cpp -o src/BTagCalibrationStandalone.o
	 g++ -fPIC -g  -o SkimAna `correction config --cflags --ldflags --rpath` `root-config --libs` -I`root-config --incdir` -I/cvmfs/cms.cern.ch/slc7_amd64_gcc900/cms/cmssw/CMSSW_12_1_0/src -L/cvmfs/cms.cern.ch/slc7_amd64_gcc900/cms/cmssw/CMSSW_12_1_0/lib/slc7_amd64_gcc900 -std=c++17 -D STANDALONE src/EventTree.o src/EventPick.o src/Selector.o  src/PUReweight.o src/BTagCalibrationStandalone.o src/Utils.cc src/FactorizedJetCorrector.o src/JetCorrectorParameters.o src/SimpleJetCorrector.o src/JetCorrectionUncertainty.o src/SimpleJetCorrectionUncertainty.o src/JECvariation.o src/RoccoR.o src/JetResolution.cc src/JetResolutionObject.cc SkimAna.C -lPhysicsToolsKinFitter -lEG -lProof
	 ```
   </details>



3. Excute : Apply the following command to excute the `SkimAna` on a single Skim file mentioned in `HplusM120_2017.txt`.
   ```console
   [idas@lxplus7113 CBA_Skim]$ ./SkimAna HplusM120 2017 input/eos/2017/HplusM120_2017.txt  0 base
   ```

   <details>
         <summary markdown="span"> Click to check expected output.</summary>
   
   
	 ```console	 
	 Input filename: input/eos/2017/HplusM120_2017.txt
	 Total files 1
	 Info in <UnknownClass::ExecSerial>: starting SkimAna with process option: sample=HplusM120|year=2017|input=input/eos/2017/HplusM120_2017.txt|index=0|syst=base|aod=nano|run=prod|trs=yes|total=1
	 Info in <TSelector::ExecSerial>: opening file root://eosuser.cern.ch//eos/cms/store/group/phys_higgs/HiggsExo/idas/cms-hcs-run2/Skim_NanoAODUL/2017/HplusM120_Skim_NanoAOD.root
	 Info in <TSelector::SlaveBegin>: starting SkimAna with process option: sample=HplusM120|year=2017|input=input/eos/2017/HplusM120_2017.txt|index=0|syst=base|aod=nano|run=prod|trs=yes|total=1 (tree: 0x4e3fd90)
	 Info in <TSelector::SlaveBegin>: sample : HplusM120, year : 2017, mode : 
	 Info in <TSelector::SelectSyst>: Syst : base
	 Info in <TSelector::Init>: tree: 0x4e3fd90
	 Info in <TSelector::SlaveBegin>: CS Init
	 Info in <TSelector::SlaveBegin>: GetNumber of Events and files
	 Info in <TSelector::GetNumberofEvents>: filename : root://eosuser.cern.ch//eos/cms/store/group/phys_higgs/HiggsExo/idas/cms-hcs-run2/Skim_NanoAODUL/2017/HplusM120_Skim_NanoAOD.root
	 sample  "HplusM120" has number of events = 2.35738e+07
	 Info in <TSelector::SlaveBegin>: Loading Lepton SF
	 Info in <TSelector::SlaveBegin>: Loading JEC JER
	 Info in <TSelector::SlaveBegin>: Loading BTag
	 Info in <TSelector::LoadBTag>: Begin
	 Info in <TSelector::LoadBTag>: DeepJet calibration has been selected
	 Info in <TSelector::LoadBTag>: DeepJet calibration has been selected : 2017
	 Info in <TSelector::LoadBTag>: /afs/cern.ch/user/i/idas/CMS-Analysis/NanoAOD-Analysis/CBA_Skim/weightUL/BtagSF/SF/2017/DeepJet_formatted.csv
	 Info in <TSelector::LoadBTag>: /afs/cern.ch/user/i/idas/CMS-Analysis/NanoAOD-Analysis/CBA_Skim/weightUL/BtagSF/SF/2017/ctagger_wp_deepJet_106XUL_v1_formatted.csv
	 Info in <TSelector::SlaveBegin>: Create Histos
	 Output (down, nom, up) : (0.981743,0.989425,0.997108)
	 ===============Sample : HplusM120
	 Syst : base, requested syst : base
	 Syst : puup, requested syst : base
	 Syst : pudown, requested syst : base
	 Syst : mueffup, requested syst : base
	 Syst : mueffdown, requested syst : base
	 Syst : eleeffup, requested syst : base
	 Syst : eleeffdown, requested syst : base
	 Syst : btagbup, requested syst : base
	 Syst : btagbdown, requested syst : base
	 Syst : btaglup, requested syst : base
	 Syst : btagldown, requested syst : base
	 Syst : prefireup, requested syst : base
	 Syst : prefiredown, requested syst : base
	 Syst : pdfup, requested syst : base
	 Syst : pdfdown, requested syst : base
	 Syst : q2fup, requested syst : base
	 Syst : q2down, requested syst : base
	 Syst : isrup, requested syst : base
	 Syst : isrdown, requested syst : base
	 Syst : fsrup, requested syst : base
	 Syst : fsrdown, requested syst : base
	 Syst : bctag1up, requested syst : base
	 Syst : bctag1down, requested syst : base
	 Syst : bctag2up, requested syst : base
	 Syst : bctag2down, requested syst : base
	 Syst : bctag3up, requested syst : base
	 Syst : bctag3down, requested syst : base
	 Syst : pujetidup, requested syst : base
	 Syst : pujetiddown, requested syst : base
	 Info in <TSelector::SlaveBegin>: End of SlaveBegin
	 Info in <TSelector::Notify>: processing fSampleType HplusM120 and file: root://eosuser.cern.ch//eos/cms/store/group/phys_higgs/HiggsExo/idas/cms-hcs-run2/Skim_NanoAODUL/2017/HplusM120_Skim_NanoAOD.root
	 Using event weight 0.46889
	 XS = 266.16
	 lumi = 41529.5
	 nEvents_MC = 2.35738e+07
	 Wrong number of bins in the pileup histogram
	 PU reading file root://eosuser.cern.ch//eos/cms/store/group/phys_higgs/HiggsExo/idas/cms-hcs-run2/Skim_NanoAODUL/2017/HplusM120_Skim_NanoAOD.root
	 Wrong number of bins in the pileup histogram
	 PU reading file root://eosuser.cern.ch//eos/cms/store/group/phys_higgs/HiggsExo/idas/cms-hcs-run2/Skim_NanoAODUL/2017/HplusM120_Skim_NanoAOD.root
	 Wrong number of bins in the pileup histogram
	 PU reading file root://eosuser.cern.ch//eos/cms/store/group/phys_higgs/HiggsExo/idas/cms-hcs-run2/Skim_NanoAODUL/2017/HplusM120_Skim_NanoAOD.root
	 Info in <TSelector::Notify>: Efficientcy file : /afs/cern.ch/user/i/idas/CMS-Analysis/NanoAOD-Analysis/CBA_Skim/weightUL/BtagSF/Efficiency/btag_deepjet/2017/HplusM120_btag_eff_deepjet_2017.root
	 Info in <TSelector::Notify>: Btag threshold : 0.304000
	 PV 1
	 ndof=77.25   (>4)
	 pX=-0.0240631   (<2)
	 pY=0.069397   (<2)
	 pZ=0.544418   (<24)
	 Info in <TSelector::Process>: Processing : 10000(9999) of number of events : 447389 and total number of events : 1227000, year : 2017
	 Info in <TSelector::Process>: Processing : 20000(19999) of number of events : 447389 and total number of events : 1227000, year : 2017
	 Info in <TSelector::Process>: Processing : 30000(29999) of number of events : 447389 and total number of events : 1227000, year : 2017
	 Info in <TSelector::Process>: Processing : 40000(39999) of number of events : 447389 and total number of events : 1227000, year : 2017
	 Info in <TSelector::Process>: Processing : 50000(49999) of number of events : 447389 and total number of events : 1227000, year : 2017
	 Info in <TSelector::Process>: Processing : 60000(59999) of number of events : 447389 and total number of events : 1227000, year : 2017
	 Info in <TSelector::Process>: Processing : 70000(69999) of number of events : 447389 and total number of events : 1227000, year : 2017
	 Info in <TSelector::Process>: Processing : 80000(79999) of number of events : 447389 and total number of events : 1227000, year : 2017
	 Info in <TSelector::Process>: Processing : 90000(89999) of number of events : 447389 and total number of events : 1227000, year : 2017
	 Info in <TSelector::Process>: Processing : 100000(99999) of number of events : 447389 and total number of events : 1227000, year : 2017
	 Info in <TSelector::Process>: Processing : 110000(109999) of number of events : 447389 and total number of events : 1227000, year : 2017
	 Info in <TSelector::Process>: Processing : 120000(119999) of number of events : 447389 and total number of events : 1227000, year : 2017
	 Info in <TSelector::Process>: Processing : 130000(129999) of number of events : 447389 and total number of events : 1227000, year : 2017
	 Info in <TSelector::Process>: Processing : 140000(139999) of number of events : 447389 and total number of events : 1227000, year : 2017
	 Info in <TSelector::Process>: Processing : 150000(149999) of number of events : 447389 and total number of events : 1227000, year : 2017
	 Info in <TSelector::Process>: Processing : 160000(159999) of number of events : 447389 and total number of events : 1227000, year : 2017
	 Info in <TSelector::Process>: Processing : 170000(169999) of number of events : 447389 and total number of events : 1227000, year : 2017
	 Info in <TSelector::Process>: Processing : 180000(179999) of number of events : 447389 and total number of events : 1227000, year : 2017
	 Info in <TSelector::Process>: Processing : 190000(189999) of number of events : 447389 and total number of events : 1227000, year : 2017
	 Info in <TSelector::Process>: Processing : 200000(199999) of number of events : 447389 and total number of events : 1227000, year : 2017
	 Info in <TSelector::Process>: Processing : 210000(209999) of number of events : 447389 and total number of events : 1227000, year : 2017
	 Info in <TSelector::Process>: Processing : 220000(219999) of number of events : 447389 and total number of events : 1227000, year : 2017
	 Info in <TSelector::Process>: Processing : 230000(229999) of number of events : 447389 and total number of events : 1227000, year : 2017
	 Info in <TSelector::Process>: Processing : 240000(239999) of number of events : 447389 and total number of events : 1227000, year : 2017
	 Info in <TSelector::Process>: Processing : 250000(249999) of number of events : 447389 and total number of events : 1227000, year : 2017
	 Info in <TSelector::Process>: Processing : 260000(259999) of number of events : 447389 and total number of events : 1227000, year : 2017
	 Info in <TSelector::Process>: Processing : 270000(269999) of number of events : 447389 and total number of events : 1227000, year : 2017
	 Info in <TSelector::Process>: Processing : 280000(279999) of number of events : 447389 and total number of events : 1227000, year : 2017
	 Info in <TSelector::Process>: Processing : 290000(289999) of number of events : 447389 and total number of events : 1227000, year : 2017
	 Info in <TSelector::Process>: Processing : 300000(299999) of number of events : 447389 and total number of events : 1227000, year : 2017
	 Info in <TSelector::Process>: Processing : 310000(309999) of number of events : 447389 and total number of events : 1227000, year : 2017
	 Info in <TSelector::Process>: Processing : 320000(319999) of number of events : 447389 and total number of events : 1227000, year : 2017
	 Info in <TSelector::Process>: Processing : 330000(329999) of number of events : 447389 and total number of events : 1227000, year : 2017
	 Info in <TSelector::Process>: Processing : 340000(339999) of number of events : 447389 and total number of events : 1227000, year : 2017
	 Info in <TSelector::Process>: Processing : 350000(349999) of number of events : 447389 and total number of events : 1227000, year : 2017
	 Info in <TSelector::Process>: Processing : 360000(359999) of number of events : 447389 and total number of events : 1227000, year : 2017
	 Info in <TSelector::Process>: Processing : 370000(369999) of number of events : 447389 and total number of events : 1227000, year : 2017
	 Info in <TSelector::Process>: Processing : 380000(379999) of number of events : 447389 and total number of events : 1227000, year : 2017
	 Info in <TSelector::Process>: Processing : 390000(389999) of number of events : 447389 and total number of events : 1227000, year : 2017
	 Info in <TSelector::Process>: Processing : 400000(399999) of number of events : 447389 and total number of events : 1227000, year : 2017
	 Info in <TSelector::Process>: Processing : 410000(409999) of number of events : 447389 and total number of events : 1227000, year : 2017
	 Info in <TSelector::Process>: Processing : 420000(419999) of number of events : 447389 and total number of events : 1227000, year : 2017
	 Info in <TSelector::Process>: Processing : 430000(429999) of number of events : 447389 and total number of events : 1227000, year : 2017
	 Info in <TSelector::Process>: Processing : 440000(439999) of number of events : 447389 and total number of events : 1227000, year : 2017
	 Info in <TSelector::SlaveTerminate>: sample : HplusM120, year : 2017, mode : 
	 DataMu & 244686.0 & 210189.0 & 120681.0 & 110417.0 & 55290.0 & 44637.0 & 43891.0 & 30490.0 & 7734.0 \\\hline 
	 WtMu & 2.1654e+06 & 1.8138e+06 & 974724.7 & 893635.8 & 426592.4 & 342535.9 & 333051.0 & 229136.6 & 31495.5 \\\hline 
	 DataEle & 187400.0 & 153056.0 & 88441.0 & 80736.0 & 40618.0 & 31950.0 & 31467.0 & 21642.0 & 5383.0 \\\hline 
	 WtEle & 1.6343e+06 & 1.2305e+06 & 666226.7 & 608397.9 & 294183.3 & 229086.9 & 223281.4 & 152158.8 & 20004.9 \\\hline 
	 ```
   </details>
   
   The arguments are,

   `./SkimAna $samplename $year $skim_filelist  $skim_index $syst_type`

   -  `samplename` : This represents the sample names such as *TTbar*,*singleTop*. Find the full list defined as `samples_$year` at ![link](condor/createJdlFiles_cbaskim_syst.py). 
   -  `skim_filelist` : This file contains the list of Skim files for a given sample type (e.g. *TTbar*). Such input files contianing the Skim filelist can be checked at `input/eos/$year/`. Note that for 2016, the preVFP and postVFP file lists are available at,  `input/eos/2016/pre` and `input/eos/2016/post`, respectively.
   -  `skim_index` : This index tells that n-th file of skim file list will be processed.
   -  `syst_type` : These are possible systematics type. See a longer list as `syst_long_$year` at ![link](condor/createJdlFiles_cbaskim_syst.py). Note that, to optimize the computation several other systematics are processed when executed for `base` type which are listed as `const char *systbase[]` in ![SkimAna.C](SkimAna.C)
### GRID job submission

---
## Description and processing flow



---
#### Acknowledgement

The structure of central code `SkimAna` is inspired by ![h1Analysis](https://root.cern/doc/master/h1analysis_8C.html).
