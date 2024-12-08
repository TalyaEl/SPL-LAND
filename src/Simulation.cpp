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
facilitiesOptions() {
        readMe(configFilePath); //using helper function
}

void Simulation::start(){
     open();
     while (isRunning){
        string userInput;
        std::getline(std::cin, userInput); // Get user input
        if(!userInput.empty()){
                vector<string> parsedAr = Auxiliary::parseArguments(userInput); // Parse the input into arguments
                // Handle different commands based on user input
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
                cout << "invalid input"<< endl; //empty input
     }
}

void Simulation::addPlan(const Settlement &settlement, SelectionPolicy *selectionPolicy) {
     Plan p(planCounter, settlement, selectionPolicy, this->facilitiesOptions);
     plans.emplace_back(p);
     planCounter++;
}

void Simulation::addAction(BaseAction *action) {
     actionsLog.push_back(action);
}

bool Simulation::addSettlement(Settlement *settlement) {
        // Check if a settlement with the same name already exists
        for (Settlement* set : settlements) {
                if (set->getName() == settlement->getName()) {
                        return false;
                }
        }

        settlements.push_back(settlement);
        return true;
}

bool Simulation::addFacility(FacilityType facility) {
        // Check if a facility with the same name already exists
        for (FacilityType type : facilitiesOptions) {
                if (type.getName() == facility.getName()) {
                        return false;
                }
        }

        facilitiesOptions.push_back(facility);
        return true;
}

bool Simulation::isSettlementExists(const string &settlementName) {
        // Search through settlements for a match
        for (Settlement* set : settlements) {
                if (set->getName() == settlementName) {
                        return true;
                }
        }    

        return false;
}

Settlement &Simulation::getSettlement(const string &settlementName) {
        // Search for the settlement by name
        for (Settlement* set : settlements) {
                if (set->getName() == settlementName) { 
                        return *set; 
                }
        }
        // If not found, create a placeholder settlement
        Settlement* s = new Settlement("NoSuchSettlement",SettlementType::VILLAGE);
        return *s;
}

Plan &Simulation::getPlan(const int planID) {
        return plans[(size_t)planID];
}

void Simulation::step() {
        for (Plan &p : plans) {
                p.step(); //step on each plan
        }
}

void Simulation::close() {
        isRunning = false;
        for (Plan p : plans) {
                cout << p.toString() << endl; //print final status of each plan
        }
}

void Simulation::open() {
        isRunning = true;
        std::cout << "The simulation has started"  << std::endl;
}

int Simulation::getPlanCounter() {
        return planCounter;
}

vector<FacilityType> &Simulation::getfacilitiesOptions(){
        return facilitiesOptions;
}

bool Simulation::isFacilityExists(const string &FacilityName) {
        // Search through facilities options for a match
        for (const FacilityType facility : facilitiesOptions) {
                if (facility.getName() == FacilityName) {
                        return true;
                }
        }

        return false;
}

bool Simulation::isPlanID(int planID) { //checks if plan id is valid
        if (planID < planCounter && planID >= 0)
                return true;
        return false;
}

const vector<BaseAction*> Simulation::getActionLog() {
        return actionsLog;
}

void Simulation::readMe(const string &configFilePath) { //helper
        std::ifstream configFile(configFilePath); // Open the configuration file
        string line;
        
        if (!configFile.is_open()) {
                std::cerr << "Error: Could not open the config file: " << configFilePath << endl;
                return; // Exit if the config file cannot be opened
        }
        
        else {
                while (std::getline(configFile, line)) { // Read each line from the file
                        vector<string> parsedAr = Auxiliary::parseArguments(line); // Parse the line into arguments
                        // Ignore empty lines or comments
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

SettlementType Simulation::stringToSetType(const string &settlementType) { //helper
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

FacilityCategory Simulation::stringToFacCat(const string &facilityCategory) { //helper
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

SelectionPolicy* Simulation::stringToSelPol(const string &selectionPolicy) { //helper
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

Simulation::Simulation(const Simulation& other): //copy constructor 
isRunning(other.isRunning),
planCounter(other.planCounter),
actionsLog(),
plans(),
settlements(),
facilitiesOptions(other.facilitiesOptions){

        for (const Settlement* set : other.settlements) {
                settlements.push_back(new Settlement(*set));
        }

        for (BaseAction* action : other.actionsLog) {
                actionsLog.push_back(action->clone());
        }
        for(const Plan& p: other.plans){
                // Copy each plan with associated settlement
                plans.emplace_back(p, (this->getSettlement(p.getSettlement().getName())));
        }
}

Simulation::Simulation(Simulation&& otherTemp) noexcept: //move constructor
isRunning(otherTemp.isRunning),
planCounter(otherTemp.planCounter),
actionsLog(std::move(otherTemp.actionsLog)),
plans(std::move(otherTemp.plans)),
settlements(std::move(otherTemp.settlements)),
facilitiesOptions(std::move(otherTemp.facilitiesOptions)) {}


Simulation::~Simulation() { //destructor
        for (BaseAction* action : actionsLog) {
                delete action;
        } 
        actionsLog.clear();  

        for (Settlement* set : settlements) {
                delete set;
        }     
        settlements.clear(); 
         
        facilitiesOptions.clear();
        plans.clear();
}


Simulation& Simulation::operator=(const Simulation& other) { //assignment opertor
        if (this != &other) { // Avoid self-assignment
                // Clear existing resources
                for (BaseAction* action : actionsLog) {
                     delete action;
                } 
                actionsLog.clear();  

                plans.clear();
                for (Settlement* set : settlements) {
                     delete set;
                }     
                settlements.clear();   
                
                facilitiesOptions.clear();
                isRunning = other.isRunning;
                planCounter = other.planCounter;

                for (BaseAction* action : other.actionsLog) {
                        actionsLog.push_back(action->clone());
                } 

                for (const Settlement* set : other.settlements) { 
                        settlements.push_back(new Settlement(*set));
                }

                for (FacilityType fac: other.facilitiesOptions) { 
                        facilitiesOptions.push_back(fac);
                }

                for(const Plan& p: other.plans) {
                        plans.emplace_back(p, (this->getSettlement(p.getSettlement().getName())));
                }
        }

        return *this;
}

Simulation& Simulation::operator=(Simulation&& otherTemp)noexcept { //move assignment operator
        if (this != &otherTemp) { // Avoid self-assignment
                // Clear existing resources
                for (BaseAction* action : actionsLog) {
                     delete action;
                } 
                actionsLog.clear();  

                for (Settlement* set : settlements) {
                     delete set;
                }     
                settlements.clear();
                facilitiesOptions.clear();
                plans.clear();

                isRunning = otherTemp.isRunning;
                planCounter = otherTemp.planCounter;
                actionsLog = std::move(otherTemp.actionsLog);
                plans = std::move(otherTemp.plans);
                settlements = std::move(otherTemp.settlements);
                facilitiesOptions = std::move(otherTemp.facilitiesOptions);
        }

        return *this;        
}

void Simulation::backupAct() {
        if (backup != nullptr) {
                delete backup; // Cleanup any existing backup
        }
        backup = new Simulation(*this); // Create a new backup of the current state
}

void Simulation::restore() {
        if (backup != nullptr) {
                *this = *backup; // Restore the current instance to the backed-up state
        }
}
