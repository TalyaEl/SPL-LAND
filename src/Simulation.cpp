#include <string>
#include <vector>
#include "Facility.h"
#include "Plan.h"
#include "Settlement.h"
#include <iostream>
#include "Simulation.h"
#include <fstream>
#include "Auxiliary.h"
#include "Action.h"

using std::string;
using std::vector;
using std::stoi;
using std::cout;
using std::endl;

class BaseAction;
class SelectionPolicy;

Simulation::Simulation(const string &configFilePath):
isRunning(false),
planCounter(0), 
actionsLog(),
plans(),
settlements(),
facilitiesOptions(),
invalidPlan(Plan(-1, Settlement("noSuchSettlement", SettlementType::VILLAGE), nullptr, {})){
        readMe(configFilePath);
}

void Simulation::start(){
     open();
     while (isRunning){

     }
}

void Simulation::addPlan(const Settlement *settlement, SelectionPolicy *selectionPolicy){
     Plan p(planCounter, *settlement, selectionPolicy->clone(), this->facilitiesOptions);
     plans.push_back(p);
     planCounter++;
}

void Simulation::addAction(BaseAction *action){
     actionsLog.push_back(action);
}

bool Simulation::addSettlement(Settlement *settlement){
        bool ans = true;
        int i = 0;
        while(i < settlements.size() && ans){
             if (settlements[i]->getName() == settlement->getName())
                ans = false;
             i++;   
        }
        
        if(ans)
             settlements.push_back(settlement);

        return ans;
}

bool Simulation::addFacility(FacilityType facility){
        bool ans = true;
        int i = 0;
        while(i < facilitiesOptions.size() && ans){
                if (facilitiesOptions[i].getName() == facility.getName())
                    ans = false; 
                i++;
        }

        if(ans)
                facilitiesOptions.push_back(facility);
        return ans;
}

bool Simulation::isSettlementExists(const string &settlementName){
        bool ans = false;
        int i = 0;
        while(i < settlements.size() && ans){
             if (settlements[i]->getName() == settlementName)
                ans = true;
             i++;   
        }
        return ans;
}

Settlement *Simulation::getSettlement(const string &settlementName) {
        if (!isSettlementExists(settlementName))
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
    if (planID < 0 || planID >= plans.size()) {
         return invalidPlan;
    }
    else     
        return plans[planID];
}

void Simulation::step(){
        for (Plan p : plans) {
                p.step();
        }
}

void Simulation::close(){
        isRunning = false;
        for (Plan p : plans) {
                cout << p.toString() << endl;
        }
}

void Simulation::open(){
        isRunning = true;
        std::cout << "The simulation has started"  << std::endl;
}

int Simulation::getPlanCounter(){
        return planCounter;
}

vector<FacilityType> Simulation::getfacilitiesOptions(){
        return facilitiesOptions;
}

bool Simulation::isFacilityExists(const string &FacilityName){
        for (const FacilityType facility : facilitiesOptions) {
                if (facility.getName() == FacilityName) {
                        return true;
                }
        }
        return false;
}

bool Simulation::isPlanID(int planID) {
        if(planID < planCounter && planID >= 0)
                return true;
        return false;
}

void Simulation::readMe(const string &configFilePath) {
        std::ifstream configFile(configFilePath);
        string line;
        
        if (!configFile.is_open()) {
                std::cerr << "Error: Could not open the config file: " << configFilePath << endl;
                return;
        }
        
        else {
                while (std::getline(configFile, line)) {
                        vector<string> parsedAr = Auxiliary::parseArguments(line);

                        if (parsedAr.empty()) {
                                continue;
                        }

                        if (parsedAr[0] == "settlement") {
                                SettlementType curSetType = stringToSetType(parsedAr[2]);
                                Settlement* curSet = new Settlement(parsedAr[1], curSetType);
                                addSettlement(curSet);
                        }

                        if (parsedAr[0] == "facility") {
                                FacilityCategory curFacCat = stringToFacCat(parsedAr[2]);
                                FacilityType curFac = FacilityType(parsedAr[1], curFacCat, stoi(parsedAr[3]), stoi(parsedAr[4]), stoi(parsedAr[5]), stoi(parsedAr[6]));
                                addFacility(curFac);
                        }

                        else {
                                Settlement* curSet = getSettlement(parsedAr[1]);
                                SelectionPolicy* curSelPol = stringToSelPol(parsedAr[2]);
                                addPlan(curSet, curSelPol);
                        }
                }
        }
}

SettlementType Simulation::stringToSetType(const string &settlementType) {
        if (settlementType == "0") {
                return SettlementType::VILLAGE;
        }

        if (settlementType == "1") {
                return SettlementType::CITY;
        }

        else {
                return SettlementType::METROPOLIS;
        }
}

FacilityCategory Simulation::stringToFacCat(const string &facilityCategory) {
        if (facilityCategory == "0") {
                return FacilityCategory::LIFE_QUALITY;
        }

        if (facilityCategory == "1") {
                return FacilityCategory::ECONOMY;
        }

        else {
                return FacilityCategory::ENVIRONMENT;
        }
}

SelectionPolicy* Simulation::stringToSelPol(const string &selectionPolicy) {
        if (selectionPolicy == "nve") {
                return new NaiveSelection();
        }

        if (selectionPolicy == "bal") {
                return new BalancedSelection(0,0,0);
        }

        if (selectionPolicy == "eco") {
                return new EconomySelection();
        }

        else {
                return new SustainabilitySelection();
        }
}

Simulation::Simulation(const Simulation& other):
isRunning(other.isRunning),
planCounter(other.planCounter),
actionsLog(),
plans(other.plans),
settlements(),
facilitiesOptions(other.facilitiesOptions),
invalidPlan(Plan(-1, Settlement("noSuchSettlement", SettlementType::VILLAGE), nullptr, {})) {
        for (BaseAction* action : other.actionsLog) {
                actionsLog.push_back(action->clone());
        }
        for (Settlement* set : other.settlements) {
                settlements.push_back(new Settlement(set->getName(), set->getType()));
        }
}

Simulation::Simulation(Simulation&& otherTemp):
isRunning(otherTemp.isRunning),
planCounter(otherTemp.planCounter),
actionsLog(std::move(otherTemp.actionsLog)),
plans(std::move(otherTemp.plans)),
settlements(std::move(otherTemp.settlements)),
facilitiesOptions(std::move(otherTemp.facilitiesOptions)),
invalidPlan(Plan(-1, Settlement("noSuchSettlement", SettlementType::VILLAGE), nullptr, {})){}

void Simulation::clear() {
        for (BaseAction* action : actionsLog) {
                delete action;
        } 
        actionsLog.clear();  

        for (Settlement* set : settlements) {
                delete set;
        }     
        settlements.clear();         
}

Simulation& Simulation::operator=(const Simulation& other) {
        if (this != &other) {
                clear();
                isRunning = other.isRunning;
                planCounter = other.planCounter;
                for (BaseAction* action : other.actionsLog) {
                        actionsLog.push_back(action->clone());
                }
                plans = other.plans;
                for (Settlement* set : other.settlements) {
                        settlements.push_back(new Settlement(set->getName(), set->getType()));
                }                 
                facilitiesOptions = other.facilitiesOptions;
        }

        return *this;
}

Simulation& Simulation::operator=(Simulation&& otherTemp) {
        if (this != &otherTemp) {
                clear();
                isRunning = otherTemp.isRunning;
                planCounter = otherTemp.planCounter;
                actionsLog = std::move(otherTemp.actionsLog);
                plans = std::move(otherTemp.plans);
                settlements = std::move(otherTemp.settlements);
                facilitiesOptions = std::move(otherTemp.facilitiesOptions);
        }

        return *this;        
}

Simulation::~Simulation() {
        clear();
}