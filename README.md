# Introduction

The present repository is created to perform a search for low mass charged Higgs boson decaying to charm and strange quarks.
We have performed the analysis using the Run2 data of pp collision of CMS experiment of CERN, Geneva.
The NanoAOD files of Ultra-Legacy (UL) campaign are used for this purpose. 

A brief discussion of the main folders is provided below.

- **Skim_NanoAOD** : In current study we filter out a subset of the full Run2 data relevant for out analysis. This process is generally called as skimming and files are therefore known as Skim files. The codes of this folder is dedicated for skimming the data.
- **CBA_Skim** : In next step, we process the Skim files and apply various corrections and scale factors. This finally produce the output histograms and trees for the calculation of upper limit.
- **Limit** : The codes for limit calculation can be found in this folder.

```mermaid
flowchart TB
    subgraph **Skim_NanoAOD**
    NanoAOD --> Skim files
    end
    subgraph **CBA_Skim**
    Skim files --> Trigger 
    Trigger --> Lepton 
    Lepton --> JET 
    JET --> MET 
    MET --> b-jet 
    b-jet --> KinFit 
    KinFit --> c-tagging 
    end
    subgraph **Limit**
    c-tagging --> Upper Limit 
    end
```

```mermaid
flowchart LR
    c-tagging --> Upper Limit 
```

The analysis requires the creation of some efficiency and resolution files, which are used during the processing of Skim file in *CBA_Skim*.
The folders which are dedicated for these pupose are described below.

- **ProcessSkim** : The efficiency files required for *b*-jet and *c*-jet tagging.
- **KFObjectReso** : The production of resolution and offset values that are used in Kinematic Fitting (KinFit).
- **PUJetIDEff** : The efficiency file for pileup JetID selections cuts.

Finally, there are some folders which are just placeholders and contains codes that were useful at earlier time. 
These folders has no connection with the current analysis using UL sample.  

- **Legacy_ReReco_CBA** : Prior to UL, we were using the Legacy Rereco NanoAODs for analysis and this folder contains codes for that study.
- **RecoKinTuple_Skim** : This is another historical folder to perform KinFit on skimmed data.
- **EventCount** : This folder contains code for MC studies of hadronic, semileptonic and dileptonic decays of ![ttbar](https://latex.codecogs.com/svg.image?t\bar{t}).
- **Standalone** : The very first implementation of standalone codes for KinFit.

---

#### Acknowledgement

The basic format of codes and scripts were inherited from ![cms-hcs-run2](https://github.com/ravindkv/cms-hcs-run2). However then it went through various additions of new features, modifications, corrections, validations and finally comparisions with previous results of ![Phys. Rev D 102, 072001 (2020)](https://doi.org/10.1103/PhysRevD.102.072001) to attain the current version.
