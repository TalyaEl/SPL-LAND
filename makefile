# Please implement your Makefile rules and targets below.
all: clean compile link

link:
	g++ -o bin/skeleton bin/main.o bin/Settlement.o bin/Simulation.o bin/Facility.o bin/Auxiliary.o

compile:
	g++ -g -Wall -Weffc++ -c -o bin/main.o src/main.cpp -Iinclude
sett:
	g++ -g -Wall -Weffc++ -c -o bin/Settlement.o src/Settlement.cpp -Iinclude
	g++ -o Settlement bin/Settlement.o
sim:
	g++ -g -Wall -Weffc++ -c -o bin/Simulation.o src/Simulation.cpp -Iinclude
fact:
	g++ -g -Wall -Weffc++ -c -o bin/Facility.o src/Facility.cpp -Iinclude
aux:
	g++ -g -Wall -Weffc++ -c -o bin/Auxiliary.o src/Auxiliary.cpp -Iinclude

clean:
	rm -f bin/*
# Customize this file to define how to build your project.