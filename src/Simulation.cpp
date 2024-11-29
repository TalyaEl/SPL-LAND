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

//tester

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



void Simulation::close(){
        isRunning=false;
}
void Simulation::open(){
        isRunning=true;
        std::cout << "The simulation has started"  << endl;

}
