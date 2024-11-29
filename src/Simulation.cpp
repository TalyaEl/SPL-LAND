#include <string>
#include <vector>
#include "Facility.h"
#include "Plan.h"
#include "Settlement.h"
#include <iostream>
#include "Simulation.h"
using std::string;
using std::vector;

class BaseAction;
class SelectionPolicy;

Simulation::Simulation(const string &configFilePath):isRunning(true),
planCounter(1), actionLog(), Plans(),settlements(),facilityOptions(){}


void Simulation::start(){
     std::cout << "the simulation has started";
}

void Simulation::close(){
        isRunning=false;
}
