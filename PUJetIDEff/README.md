# Table of Contents
1. [Create efficiency files](#Create-efficiency-files)
   - [Set CMSSW](#set-cmssw)
   - [Process Skim files](#process-skim-files)


---
## Create efficiency files

### Set CMSSW

Set the environment for CMSSW. The CMSSW_X_X_X can be created in other location irrespective of the download directory of current project. 

   ```console
   export SCRAM_ARCH=slc7_amd64_gcc900
   source /cvmfs/cms.cern.ch/cmsset_default.sh
   scramv1 project CMSSW CMSSW_12_1_0
   cd CMSSW_12_1_0/src
   cmsenv
   ```

### Process Skim files

    We want to process the skim files mentioned in TTTT_2017.txt and produce histograms that will be used to generate the pujetid efficiency files.

    The content of TTTT_2017.txt is,
    
   ```console
   [idas@lxplus759 2017]$ cat TTTT_2017.txt 
   root://eosuser.cern.ch//eos/cms/store/group/phys_b2g/savarghe/cms-hcs-run2/Skim_NanoAODUL/2017/TTTT_Skim_NanoAOD_2of6.root
   root://eosuser.cern.ch//eos/cms/store/group/phys_b2g/savarghe/cms-hcs-run2/Skim_NanoAODUL/2017/TTTT_Skim_NanoAOD_4of6.root
   root://eosuser.cern.ch//eos/cms/store/group/phys_b2g/savarghe/cms-hcs-run2/Skim_NanoAODUL/2017/TTTT_Skim_NanoAOD_5of6.root
   root://eosuser.cern.ch//eos/cms/store/group/phys_b2g/savarghe/cms-hcs-run2/Skim_NanoAODUL/2017/TTTT_Skim_NanoAOD_6of6.root
   ```

   Keep it at your preferred path and mention that path in 'runloop.sh' file
   ```console
   input=../CBA_Skim/input/eos/$year/${sample}_${year}.txt
   ```
   Next update the sample name in that shell script.
   ```console
   samples_2017="TTTT"
   ````

   You can now execute the script, which will show the following output under normal condition.
   ```console
   [idas@lxplus759 PUJetIDEff]$ source runloop.sh 
   samples : TTTT
   -rw-r--r--. 1 idas zh 492 Aug 29 04:48 ../CBA_Skim/input/eos/2017/TTTT_2017.txt
   Processing run.C("sample=TTTT|year=2017|input=../CBA_Skim/input/eos/2017/TTTT_2017.txt|run=prod|mode=proof|workers=8")...
   Input filename: ../CBA_Skim/input/eos/2017/TTTT_2017.txt
   +++ Starting PROOF-Lite with 8 workers +++
   Opening connections to workers: OK (8 workers)                 
   Setting up worker servers: OK (8 workers)                 
   PROOF set to parallel mode (8 workers)
   Info in <TPackMgr::Install>: installing loadpackages.par ...
   [TFile::Cp] Total 0.01 MB	|====================| 100.00 % [25.4 MB/s]
   building loadpackages ...
   loadpackages: version change (current: 6.24/07, build: ): cleaning ... 
   event-BUILD: standard PROOF node
   building loadpackages ...
   event-SETUP: PROOF client
   Base Path is : /afs/cern.ch/user/i/idas/CMS-Analysis/NanoAOD-Analysis
   Wrk-0.1: building loadpackages ...
   Wrk-0.2: building loadpackages ...
   Wrk-0.0: building loadpackages ...
   Wrk-0.5: building loadpackages ...
   Wrk-0.7: building loadpackages ...
   Wrk-0.4: building loadpackages ...
   Wrk-0.3: building loadpackages ...
   Wrk-0.6: building loadpackages ...
   Info in <TProofLite::SetQueryRunning>: starting query: 1
   Info in <TProofQueryResult::SetRunning>: nwrks: 8
   Info in <TUnixSystem::ACLiC>: creating shared library /afs/cern.ch/user/i/idas/CMS-Analysis/NanoAOD-Analysis/PUJetIDEff/./PUJetIDEff_C.so
   Info in <PUJetIDEff::Begin>: starting PUJetIDEff with process option: sample=TTTT|year=2017|input=../CBA_Skim/input/eos/2017/TTTT_2017.txt|run=prod|mode=proof|workers=8
   Looking up for exact location of files: OK (4 files)                 
   Looking up for exact location of files: OK (4 files)                 
   Info in <TPacketizer::TPacketizer>: Initial number of workers: 8
   Validating files: OK (4 files)                 
   [TProof::Progress] Total 2525492 events |====================| 100.00 % [20001.4 evts/s, 24.8 MB/s, time left: 0.0 s]]
   Query processing time: 126.3 s
   Lite-0: merging output objects ... / (1 workers still sending)   
   Output file: TTTT_pujetid_eff_raw_2017.root
   Info in <PUJetIDEff::Terminate>: stopping PUJetIDEff with process option: sample=TTTT|year=2017|input=../CBA_Skim/input/eos/2017/TTTT_2017.txt|run=prod|mode=proof|workers=8
   Lite-0: all output objects have been merged                                                         
   (int) 1
   [idas@lxplus759 PUJetIDEff]$
   ```

   Once completed, it will produce file 'TTTT_pujetid_eff_raw_2017.root'

   The last step is to modify 'codes/CreatePUJetIDEff.C' so that is processes the raw histograms of TTTT_pujetid_eff_raw_2017.root to produce 'TTTT_pujetid_eff_2017.root'. Use the later file for the CBA analysis.
   The expected contents of the two files are shown below.

   ```console
   [idas@lxplus759 PUJetIDEff]$ root -l TTTT_pujetid_eff_raw_2017.root 
   root [0] 
   Attaching file TTTT_pujetid_eff_raw_2017.root as _file0...
   (TFile *) 0x2a093f0
   root [1] .ls
   TFile**		TTTT_pujetid_eff_raw_2017.root	
   TFile*		TTTT_pujetid_eff_raw_2017.root	
   KEY: TH2D	h2_PUJetIDEff_Denom;1	
   KEY: TH2D	h2_PUJetIDEff_Num_L;1	
   KEY: TH2D	h2_PUJetIDEff_Num_M;1	
   KEY: TH2D	h2_PUJetIDEff_Num_T;1	
   root [2] .q
   [idas@lxplus759 PUJetIDEff]$ root -l TTTT_pujetid_eff_2017.root 
   root [0] 
   Attaching file TTTT_pujetid_eff_2017.root as _file0...
   (TFile *) 0x2cccb40
   root [1] .ls
   TFile**		TTTT_pujetid_eff_2017.root	
   TFile*		TTTT_pujetid_eff_2017.root	
   KEY: TH2D	PUJetID_L_efficiency;1	
   KEY: TH2D	PUJetID_M_efficiency;1	
   KEY: TH2D	PUJetID_T_efficiency;1	
   root [2] .q
   [idas@lxplus759 PUJetIDEff]$
   ```
   
