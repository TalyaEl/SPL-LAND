#include <string>
#include <vector>
#include "Facility.h"
#include "Plan.h"
#include "Settlement.h"
#include <iostream>
using std::string;
using std::vector;

class BaseAction;
class SelectionPolicy;

void Simulation::start(){
     std::cout << "the simulation has started";
}

void Simulation::close(){
        isRunning=false;
}
