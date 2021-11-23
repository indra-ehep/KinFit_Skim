all: src/EventTree_Skim.o src/EventPick_Skim.o makeSkim 

makeSkim:  src/EventPick_Skim.o src/EventTree_Skim.o  makeSkim.C
	g++ -o makeSkim `root-config --libs` -I `root-config --incdir` -std=c++17 src/EventTree_Skim.o src/EventPick_Skim.o makeSkim.C

src/EventTree_Skim.o: src/EventTree_Skim.cpp interface/EventTree_Skim.h
	g++ -c -I `root-config --incdir` -std=c++17 src/EventTree_Skim.cpp -o src/EventTree_Skim.o

src/EventPick_Skim.o: src/EventPick_Skim.cpp interface/EventPick_Skim.h
	g++ -c -I `root-config --incdir` -std=c++17 src/EventPick_Skim.cpp -o src/EventPick_Skim.o 


clean:
	rm src/*.o 
