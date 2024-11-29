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

void Simulation::addPlan(const Settlement *settlement, SelectionPolicy *selectionPolicy){
     Plan p(planCounter, *settlement,selectionPolicy,this->facilitiesOptions);
     plans.push_back(p);
     planCounter++;
}
void Simulation::addAction(BaseAction *action){
     actionsLog.push_back(action);
}

bool Simulation::addSettlement(Settlement *settlement){
        bool ans=true;
        int i=0;
        while(i < settlements.size() && ans){
             i++;
             if (settlements[i]->getName()==settlement->getName())
                ans=false;
        }
        if(ans)
             settlements.push_back(settlement);
}

bool Simulation::addFacility(FacilityType facility){
        bool ans=true;
        int i=0;
        while(i< facilitiesOptions.size()&& ans){
                i++;
                if (facilitiesOptions[i].getName()== facility.getName())
                    ans=false; 
        }
        if(ans)
        facilitiesOptions.push_back(facility);
}

bool Simulation::isSettlementExists(const string &settlementName){
        bool ans=true;
        int i=0;
        while(i < settlements.size() && ans){
             i++;
             if (settlements[i]->getName()==settlementName)
                ans=false;
        }
        return ans;
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
