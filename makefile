# Please implement your Makefile rules and targets below.
all: clean compile link

link:
	g++ -o bin/skeleton bin/main.o bin/Settlement.o bin/Simulation.o \
	bin/Facility.o bin/Auxiliary.o bin/SelectionPolicy.o bin/Action.o

compile:
	g++ -g -Wall -Weffc++ -std=c++11 -c -o bin/main.o src/main.cpp -Iinclude
	g++ -o main bin/main.o
fornow:
	g++ -g -Wall -Weffc++ -std=c++11 -c -o bin/Settlement.o src/Settlement.cpp -Iinclude
	g++ -g -Wall -Weffc++ -std=c++11 -c -o bin/Facility.o src/Facility.cpp -Iinclude
	g++ -g -Wall -Weffc++ -std=c++11 -c -o bin/SelectionPolicy.o src/SelectionPolicy.cpp -Iinclude
	g++ -g -Wall -Weffc++ -std=c++11 -c -o bin/Plan.o src/Plan.cpp -Iinclude 
sim:
	g++ -g -Wall -Weffc++ -std=c++11 -c -o bin/Simulation.o src/Simulation.cpp -Iinclude
	g++ -o Simulation bin/Simulation.o

aux:
	g++ -g -Wall -Weffc++ -std=c++11 -c -o bin/Auxiliary.o src/Auxiliary.cpp -Iinclude
	g++ -o Auxiliary bin/Auxiliary.o

action:
	g++ -g -Wall -Weffc++ -std=c++11 -c -o bin/Action.o src/Action.cpp -Iinclude
	g++ -o Action bin/Action.o

clean:
	rm -f bin/*
# Customize this file to define how to build your project.