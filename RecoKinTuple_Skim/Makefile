CPPFLAGS=  -Wall -g -O -fPIC
CPPFLAGS1= -Wall -g -O -fPIC

all: bin

bin: src/FactorizedJetCorrector.o src/JetCorrectorParameters.o src/SimpleJetCorrector.o src/JetCorrectionUncertainty.o src/JECvariation.o src/JetResolutionObject.o src/JetResolution.o src/Selector.o src/EventTree.o src/EventPick.o makeKineTuple #makeCutflows src/testLepSF

bin1: src/FactorizedJetCorrector.o src/JetCorrectorParameters.o src/SimpleJetCorrector.o src/JetCorrectionUncertainty.o src/JECvariation.o src/JetResolutionObject.o src/JetResolution.o src/Selector.o src/EventTree.o src/EventPick.o recom #makeCutflows src/testLepSF
	mv -f EventJetAna bin/

bin2: src/FactorizedJetCorrector.o src/JetCorrectorParameters.o src/SimpleJetCorrector.o src/JetCorrectionUncertainty.o src/JECvariation.o src/JetResolutionObject.o src/JetResolution.o src/Selector.o src/EventTree.o src/EventPick.o EventJetAna #makeCutflows src/testLepSF
	mv -f EventJetAna bin/

lib: libEventJetAna.so
	mv -f *.so lib/

libskimana: libSkimAna.so
	mv -f  *.so lib/

libSkimAna.so: src/Selector.o src/EventPick.o src/EventTree.o src/PUReweight.cpp interface/PUReweight.h src/BTagCalibrationStandalone.o interface/ScaleFactorFunction.h src/JECvariation.o src/TopEventCombinatorics.cpp interface/muSF_reader.h interface/eleSF_reader.h 
	mv -f *.o src/
	g++ $(CPPFLAGS) -shared -o $@ `root-config --libs` -I`root-config --incdir` -std=c++17 -D STANDALONE src/EventTree.o src/EventPick.o src/Selector.o  src/PUReweight.cpp src/BTagCalibrationStandalone.o src/Utils.cc src/FactorizedJetCorrector.o src/JetCorrectorParameters.o src/SimpleJetCorrector.o src/JetCorrectionUncertainty.o src/SimpleJetCorrectionUncertainty.o src/JECvariation.o src/JetResolution.cc src/JetResolutionObject.cc src/METzCalculator.cpp src/TopEventCombinatorics.cpp 

libEventJetAna.so: src/Selector.o src/EventPick.o src/EventTree.o src/EventJetAna.C interface/EventJetAna.h src/PUReweight.cpp interface/PUReweight.h src/BTagCalibrationStandalone.o interface/ScaleFactorFunction.h src/JECvariation.o src/TopEventCombinatorics.cpp interface/muSF_reader.h interface/eleSF_reader.h 
	mv -f *.o src/
	g++ $(CPPFLAGS) -shared -o $@ `root-config --libs` -I`root-config --incdir` -std=c++17 -D STANDALONE src/EventJetAna.C src/EventTree.o src/EventPick.o src/Selector.o  src/PUReweight.cpp src/BTagCalibrationStandalone.o src/Utils.cc src/FactorizedJetCorrector.o src/JetCorrectorParameters.o src/SimpleJetCorrector.o src/JetCorrectionUncertainty.o src/SimpleJetCorrectionUncertainty.o src/JECvariation.o src/JetResolution.cc src/JetResolutionObject.cc src/METzCalculator.cpp src/TopEventCombinatorics.cpp 

src/FactorizedJetCorrector.o: src/FactorizedJetCorrector.cpp interface/FactorizedJetCorrector.h interface/JetCorrectorParameters.h interface/SimpleJetCorrector.h src/Utilities.cc
	g++ $(CPPFLAGS) -c `root-config --libs` -I`root-config --incdir` -std=c++17 src/FactorizedJetCorrector.cpp
	mv *.o src/	

src/JetCorrectorParameters.o: src/JetCorrectorParameters.cpp interface/JetCorrectorParameters.h 
	g++ $(CPPFLAGS) -c `root-config --libs` -I`root-config --incdir` -std=c++17 src/JetCorrectorParameters.cpp

src/SimpleJetCorrector.o: src/JetCorrectorParameters.cpp interface/JetCorrectorParameters.h interface/SimpleJetCorrector.h
	g++ $(CPPFLAGS) -c `root-config --libs` -I`root-config --incdir` -std=c++17 src/SimpleJetCorrector.cpp 
	mv *.o src/	

src/JetCorrectionUncertainty.o: src/JetCorrectionUncertainty.cpp interface/JetCorrectionUncertainty.h src/SimpleJetCorrectionUncertainty.cpp interface/SimpleJetCorrectionUncertainty.h
	g++ $(CPPFLAGS) -c `root-config --libs` -I`root-config --incdir` -std=c++17 src/JetCorrectionUncertainty.cpp src/SimpleJetCorrectionUncertainty.cpp 
	mv *.o src/	

src/JECvariation.o: src/FactorizedJetCorrector.o src/JetCorrectorParameters.o src/SimpleJetCorrector.o src/JetCorrectionUncertainty.o src/JECvariation.cpp
	g++ $(CPPFLAGS) -c `root-config --libs` -I`root-config --incdir` -std=c++17 src/JECvariation.cpp
	mv *.o src/	

src/JetResolutionObject.o: src/JetResolutionObject.cc interface/JetResolutionObject.h
	g++ $(CPPFLAGS) -c `root-config --libs` -I`root-config --incdir` -std=c++17 -D STANDALONE interface/JERUtilities.h src/JetResolutionObject.cc 
	mv *.o src/	

src/JetResolution.o: interface/JetResolution.h src/JetResolution.cc
	g++ $(CPPFLAGS) -c `root-config --libs` -I`root-config --incdir` -std=c++17 -D STANDALONE src/JetResolution.cc 
	mv *.o src/	

src/testLepSF: src/testLepSF.cpp interface/muSF_reader.h interface/eleSF_reader.h 
	g++ $(CPPFLAGS) -o testLepSF `root-config --libs` -I`root-config --incdir` -std=c++17 src/testLepSF.cpp 
	mv *.o src/	

src/EventTree.o: src/EventTree.cpp interface/EventTree.h
	g++ $(CPPFLAGS) -c -I`root-config --incdir` -std=c++17 -D STANDALONE src/EventTree.cpp
	mv *.o src/	

src/BTagCalibrationStandalone.o: src/BTagCalibrationStandalone.cpp interface/BTagCalibrationStandalone.h
	g++ $(CPPFLAGS) -c -I`root-config --incdir` -std=c++17 -D STANDALONE src/BTagCalibrationStandalone.cpp
	mv *.o src/	

src/Selector.o: src/EventTree.o src/Selector.cpp interface/Selector.h
	g++ $(CPPFLAGS) -c -I `root-config --incdir` -std=c++17 -D STANDALONE src/Utils.cc src/JetResolution.cc src/JetResolutionObject.cc  src/Selector.cpp
	mv *.o src/	

src/EventPick.o: src/Selector.o src/EventPick.cpp interface/EventPick.h
	g++ $(CPPFLAGS) -c -I `root-config --incdir` -std=c++17 -D STANDALONE src/EventPick.cpp 
	mv *.o src/	

src/Selector_gen.o: src/EventTree.o src/Selector_gen.cpp interface/Selector.h
	g++ $(CPPFLAGS) -c -I`root-config --incdir` -std=c++17 -D STANDALONE src/Selector_gen.cpp
	mv *.o src/	

src/EventPick_gen.o: src/Selector_gen.o src/EventPick_gen.cpp interface/EventPick.h
	g++ $(CPPFLAGS) -c -I `root-config --incdir` -std=c++17 -D STANDALONE src/EventPick_gen.cpp 
	mv *.o src/

EventJetAna: src/Selector.o src/EventPick.o src/EventTree.o src/EventJetAna.C interface/EventJetAna.h src/PUReweight.cpp interface/PUReweight.h src/BTagCalibrationStandalone.o interface/ScaleFactorFunction.h src/JECvariation.o src/TopEventCombinatorics.cpp interface/muSF_reader.h interface/eleSF_reader.h 
	mv -f *.o src/
	g++ $(CPPFLAGS) -o EventJetAna `root-config --libs` -I`root-config --incdir` -std=c++17 -D STANDALONE src/EventJetAna.C src/EventTree.o src/EventPick.o src/Selector.o  src/PUReweight.cpp src/BTagCalibrationStandalone.o src/Utils.cc src/FactorizedJetCorrector.o src/JetCorrectorParameters.o src/SimpleJetCorrector.o src/JetCorrectionUncertainty.o src/SimpleJetCorrectionUncertainty.o src/JECvariation.o src/JetResolution.cc src/JetResolutionObject.cc src/METzCalculator.cpp src/TopEventCombinatorics.cpp 

recom: src/Selector.o src/EventPick.o src/EventTree.o src/EventJetAna.C interface/EventJetAna.h src/PUReweight.cpp interface/PUReweight.h src/BTagCalibrationStandalone.o interface/ScaleFactorFunction.h src/JECvariation.o src/TopEventCombinatorics.cpp interface/muSF_reader.h interface/eleSF_reader.h 
	g++ $(CPPFLAGS1) -o EventJetAna `root-config --libs` -I`root-config --incdir` -std=c++17 -D STANDALONE src/EventJetAna.C src/EventTree.o src/EventPick.o src/Selector.o  src/PUReweight.cpp src/BTagCalibrationStandalone.o src/Utils.cc src/FactorizedJetCorrector.o src/JetCorrectorParameters.o src/SimpleJetCorrector.o src/JetCorrectionUncertainty.o src/SimpleJetCorrectionUncertainty.o src/JECvariation.o src/JetResolution.cc src/JetResolutionObject.cc src/METzCalculator.cpp src/TopEventCombinatorics.cpp 

makeKineTuple:src/Selector.o src/EventPick.o src/EventTree.o src/EventJetAna.C interface/EventJetAna.h src/PUReweight.cpp interface/PUReweight.h src/BTagCalibrationStandalone.o interface/ScaleFactorFunction.h src/JECvariation.o src/TopEventCombinatorics.cpp interface/muSF_reader.h interface/eleSF_reader.h 
	g++ $(CPPFLAGS) -o makeRecoKinTuple `root-config --libs` -I`root-config --incdir` -std=c++17 -D STANDALONE src/makeRecoKinTuple.C src/EventTree.o src/EventPick.o src/Selector.o  src/PUReweight.cpp src/BTagCalibrationStandalone.o src/Utils.cc src/FactorizedJetCorrector.o src/JetCorrectorParameters.o src/SimpleJetCorrector.o src/JetCorrectionUncertainty.o src/SimpleJetCorrectionUncertainty.o src/JECvariation.o src/JetResolution.cc src/JetResolutionObject.cc src/METzCalculator.cpp src/TopEventCombinatorics.cpp 

clean:
	rm -f *.o src/*.o lib/*.so bin/* makeRecoKinTuple 
