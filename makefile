# target: dependencies
# <tab> rule

# make (without arguments) executes first rule in file
# Ideally, one target for every object file and a target for final binary.

final: cheatersMain.o hashTable.o
	g++ -o plagiarismCatcher cheatersMain.o hashTable.o

cheatersMain.o: cheatersMain.cpp hashTable.cpp hashTable.h
		g++ -c cheatersMain.cpp

hashTable.o: hashTable.cpp hashTable.h
		g++ -c hashTable.cpp
