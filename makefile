all: server.out client.out

server.out: server.o vectorData.o validations.o CLI.o command.o connectionUtil.o vectorsDataStruct.o distanceAlgo.o classifiedVector.o disVector.o vecComparator.o distances.o
	g++ -std=c++11 -pthread server.o vectorData.o validations.o CLI.o command.o connectionUtil.o vectorsDataStruct.o distanceAlgo.o classifiedVector.o disVector.o vecComparator.o distances.o -o server.out

client.out: client.o vectorData.o validations.o CLI.o command.o connectionUtil.o vectorsDataStruct.o distanceAlgo.o classifiedVector.o disVector.o vecComparator.o distances.o
	g++ -std=c++11 -pthread client.o vectorData.o validations.o CLI.o command.o connectionUtil.o vectorsDataStruct.o distanceAlgo.o classifiedVector.o disVector.o vecComparator.o distances.o -o client.out

server.o: server.cpp validations.h
	g++ -c -std=c++11 -pthread server.cpp

client.o: client.cpp validations.h
	g++ -c -std=c++11 -pthread client.cpp

vectorsDataStruct.o: vectorsDataStruct.cpp vectorsDataStruct.h classifiedVector.h disVector.h
	g++ -c -std=c++11 -pthread vectorsDataStruct.cpp

distanceAlgo.o: distanceAlgo.cpp distanceAlgo.h distances.h
	g++ -c -std=c++11 -pthread distanceAlgo.cpp

CLI.o: CLI.cpp CLI.h distances.h connectionUtil.h command.h
	g++ -c -std=c++11 -pthread CLI.cpp

command.o: command.cpp command.h connectionUtil.h validations.h
	g++ -c -std=c++11 -pthread command.cpp

connectionUtil.o: connectionUtil.cpp connectionUtil.h validations.h vectorData.h
	g++ -c -std=c++11 -pthread connectionUtil.cpp

validations.o: validations.cpp validations.h
	g++ -c -std=c++11 -pthread validations.cpp

classifiedVector.o: classifiedVector.cpp classifiedVector.h
	g++ -c -std=c++11 -pthread classifiedVector.cpp

vectorData.o: vectorData.cpp vectorData.h
	g++ -c -std=c++11 -pthread vectorData.cpp

disVector.o: disVector.cpp disVector.h
	g++ -c -std=c++11 -pthread disVector.cpp

vecComparator.o: vecComparator.cpp vecComparator.h
	g++ -c -std=c++11 -pthread vecComparator.cpp

distances.o: distances.cpp distances.h
	g++ -c -std=c++11 -pthread distances.cpp

clean:
	rm *.o a.out