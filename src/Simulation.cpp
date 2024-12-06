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

extern Simulation* backup; 

class BaseAction;
class SelectionPolicy;

Simulation::Simulation(const string &configFilePath):
isRunning(false),
planCounter(0), 
actionsLog(),
plans(),
settlements(),
facilitiesOptions()
{
        readMe(configFilePath);
}

void Simulation::start(){
     open();
     while (isRunning){
        string userInput;
        std::getline(std::cin, userInput);
        if(!userInput.empty()){
                vector<string> parsedAr = Auxiliary::parseArguments(userInput);
                if (parsedAr[0] == "close") {
                        Close closeSim =  Close();
                        closeSim.act(*this);
                        actionsLog.push_back(closeSim.clone());
                }

                if (parsedAr[0] == "log") {
                        PrintActionsLog printLog = PrintActionsLog();
                        printLog.act(*this);
                        actionsLog.push_back(printLog.clone());
                }

                if (parsedAr[0] == "backup") {
                        BackupSimulation* back = new BackupSimulation();
                        back->act(*this);
                        actionsLog.push_back(back);
                }

                if (parsedAr[0] == "restore") {
                        RestoreSimulation rest = RestoreSimulation();
                        rest.act(*this);
                        actionsLog.push_back(rest.clone());
                }

                if (parsedAr[0] == "changePolicy") {
                        ChangePlanPolicy changePP = ChangePlanPolicy(stoi(parsedAr[1]), parsedAr[2]);
                        changePP.act(*this);
                        actionsLog.push_back(changePP.clone());
                }

                if (parsedAr[0] == "planStatus") {
                        PrintPlanStatus printPS = PrintPlanStatus(stoi(parsedAr[1]));
                        printPS.act(*this);
                        actionsLog.push_back(printPS.clone());
                }

                if (parsedAr[0] == "settlement") {
                        AddSettlement set = AddSettlement(parsedAr[1], stringToSetType(parsedAr[2]));
                        set.act(*this);
                        actionsLog.push_back(set.clone());
                }

                if (parsedAr[0] == "plan") {
                        AddPlan plan = AddPlan(parsedAr[1], parsedAr[2]);
                        plan.act(*this);
                        actionsLog.push_back(plan.clone());  
                }

                if (parsedAr[0] == "step") {
                        SimulateStep simStep = SimulateStep(stoi(parsedAr[1]));
                        simStep.act(*this);
                        actionsLog.push_back(simStep.clone());
                }
                if (parsedAr[0] == "facility") {
                        AddFacility fac = AddFacility(parsedAr[1], stringToFacCat(parsedAr[2]), stoi(parsedAr[3]), stoi(parsedAr[4]), stoi(parsedAr[5]), stoi(parsedAr[6]));
                        fac.act(*this);
                        actionsLog.push_back(fac.clone());
                }
        }
        else
                cout << "invalid input"<< endl;
     }
}

void Simulation::addPlan(const Settlement &settlement, SelectionPolicy *selectionPolicy){
//      Settlement tempSet = Settlement(settlement.getName(), settlement.getType());  
     Plan p(planCounter, settlement, selectionPolicy, this->facilitiesOptions);
     plans.push_back(p);
     planCounter++;
}

void Simulation::addAction(BaseAction *action){
     actionsLog.push_back(action);
}

bool Simulation::addSettlement(Settlement *settlement){
        for (Settlement* set : settlements) {
                if (set->getName() == settlement->getName()) {
                        return false;
                }
        }
        settlements.push_back(settlement);
        return true;
}

bool Simulation::addFacility(FacilityType facility){
        for (FacilityType type : facilitiesOptions) {
                if (type.getName() == facility.getName()) {
                        return false;
                }
        }
        facilitiesOptions.push_back(facility);
        return true;
}

bool Simulation::isSettlementExists(const string &settlementName){

        for (Settlement* set : settlements) {
                if (set->getName() == settlementName) {
                        return true;
                }
        }        
        return false;
}

Settlement &Simulation::getSettlement(const string &settlementName) {
        for (Settlement* set : settlements) {
                if (set->getName() == settlementName) { 
                        return *set; 
                }
        }
        Settlement* s= new Settlement("NoSuchSettlement",SettlementType::VILLAGE);
        return *s;
}

Plan &Simulation::getPlan(const int planID) {
        return plans[(size_t)planID];
}

void Simulation::step(){
        for (Plan &p : plans) {
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

vector<FacilityType> &Simulation::getfacilitiesOptions(){
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

const vector<BaseAction*> Simulation::getActionLog(){
        return  actionsLog;
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

                        if (parsedAr.empty() || parsedAr[0] == "#") {
                                continue;
                        }

                        else if (parsedAr[0] == "settlement") {
                                SettlementType curSetType = stringToSetType(parsedAr[2]);
                                Settlement* curSet = new Settlement(parsedAr[1], curSetType);
                                addSettlement(curSet);
                        }

                        else if (parsedAr[0] == "facility") {
                                FacilityCategory curFacCat = stringToFacCat(parsedAr[2]);
                                FacilityType curFac = FacilityType(parsedAr[1], curFacCat, stoi(parsedAr[3]), stoi(parsedAr[4]), stoi(parsedAr[5]), stoi(parsedAr[6]));
                                addFacility(curFac);
                        }

                        else if (parsedAr[0] == "plan") {
                                Settlement& curSet = getSettlement(parsedAr[1]);
                                SelectionPolicy* curSelPol = stringToSelPol(parsedAr[2]);
                                addPlan(curSet, curSelPol);
                                delete curSelPol;
                        }
                        else {
                                std::cerr << "Invalid data" << endl;
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
facilitiesOptions(other.facilitiesOptions){

        for (Settlement* set : other.settlements) {
                settlements.push_back(new Settlement(*set));
        }

        for (BaseAction* action : other.actionsLog) {
                actionsLog.push_back(action->clone());
        }
}

Simulation::Simulation(Simulation&& otherTemp) noexcept:
isRunning(otherTemp.isRunning),
planCounter(otherTemp.planCounter),
actionsLog(std::move(otherTemp.actionsLog)),
plans(std::move(otherTemp.plans)),
settlements(std::move(otherTemp.settlements)),
facilitiesOptions(std::move(otherTemp.facilitiesOptions)){}

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
Simulation::~Simulation() {
        clear();
}


Simulation& Simulation::operator=(const Simulation& other) {
        if (this != &other) {
                this->clear();
                this->plans.clear();
                this->facilitiesOptions.clear();
                this->isRunning = other.isRunning;
                this->planCounter = other.planCounter;
        
                for (BaseAction* action : other.actionsLog) {
                        actionsLog.push_back(action->clone());
                } 

                for (const Settlement* set : other.settlements) { 
                        settlements.push_back(new Settlement(*set));
                }

                for (FacilityType fac: other.facilitiesOptions){ 
                        facilitiesOptions.push_back(fac);
                }

                for (Plan p: other.plans){ 
                        plans.push_back(p);
                }
        }

        return *this;
}

Simulation& Simulation::operator=(Simulation&& otherTemp)noexcept {
        if (this != &otherTemp) {
                this->clear();
                isRunning = otherTemp.isRunning;
                planCounter = otherTemp.planCounter;
                actionsLog = std::move(otherTemp.actionsLog);
                plans = std::move(otherTemp.plans);
                settlements = std::move(otherTemp.settlements);
                facilitiesOptions = std::move(otherTemp.facilitiesOptions);
        }

        return *this;        
}


