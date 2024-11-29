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

Simulation::Simulation(const string &configFilePath):
isRunning(false),
planCounter(0), 
actionsLog(),
plans(),
settlements(),
facilitiesOptions(){}


void Simulation::start(){
     open();
     while (isRunning){

     }
  
}

void Simulation::close(){
        isRunning=false;
}
void Simulation::open(){
        isRunning=true;
        std::cout << "The simulation has started"  << endl;

}
