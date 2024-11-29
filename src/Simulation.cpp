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

Settlement *Simulation::getSettlement(const string &settlementName) {
        bool isFound = isSettlementExists(settlementName);
        if (!isFound)
                return nullptr;
        else {
                for (Settlement* set : settlements) {
                        if (set->getName() == settlementName) { 
                                return set; 
                        }
                }
        }
}

Plan &Simulation::getPlan(const int planID) {
    if (plans.size() < planID || planID < 0) {
         return noExist();
    }
    else     
        return plans[planID];
}

void Simulation::close(){
        isRunning=false;
}
void Simulation::open(){
        isRunning=true;
        std::cout << "The simulation has started"  << endl;

}

Plan& Simulation::noExist() {
        Settlement no("noSuchSettlement",SettlementType::VILLAGE);
        vector <FacilityType> temp;
        Plan p(-1,no,nullptr,temp);
        return p;
}
