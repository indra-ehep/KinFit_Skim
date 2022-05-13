# Motivation

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
<summary markdown="span">Click to see the output</summary>
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




3. Excute : 

### GRID job submission

---
## Description and processing flow



---
#### Acknowledgement

The structure of central code `SkimAna` is inspired by ![h1Analysis](https://root.cern/doc/master/h1analysis_8C.html).
