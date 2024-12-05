#include "Action.h"
#include <string>
#include <vector>
#include "Simulation.h"
#include <iostream>
#include "SelectionPolicy.h"

using std::cout;
using std::endl;

extern Simulation* backup;

enum class SettlementType;
enum class FacilityCategory;

string ActionStatusToString(ActionStatus t){
    if (t == ActionStatus:: COMPLETED)
        return "COMPLETED";
    else if (t == ActionStatus:: ERROR)
        return "ERROR";

    return "unkown";
}

BaseAction::BaseAction():errorMsg(""),
 status(ActionStatus:: ERROR){}

ActionStatus BaseAction::getStatus() const{
    return status;
}

void BaseAction::complete(){
    status=ActionStatus:: COMPLETED;
}

void BaseAction::error(string errorMsg){
    cout << "Error: " << errorMsg << endl;
}

const string &BaseAction::getErrorMsg() const{
    return errorMsg;
}




//simulation step
SimulateStep::SimulateStep(const int numOfSteps):
BaseAction(),numOfSteps(numOfSteps)
{}

void SimulateStep::act(Simulation &simulation) {
  for (int i = 0; i < numOfSteps; i++)
  {
   simulation.step();
  } 
  complete();
}

const string SimulateStep::toString() const {
    return "step "+ std::to_string(numOfSteps)+" "+ActionStatusToString(this->getStatus()) ;
}

SimulateStep *SimulateStep::clone() const {
    return new SimulateStep(*this);
}


//addplan
AddPlan::AddPlan(const string &settlementName, const string &selectionPolicy):
BaseAction(), settlementName(settlementName),selectionPolicy(selectionPolicy) //use clone
{}

void AddPlan::act(Simulation &simulation){
    if (selectionPolicy!="nve" && selectionPolicy!="bal" && selectionPolicy!="eco" && selectionPolicy!="env")
         error("Cannot create this plan");
    else if(simulation.isSettlementExists(settlementName)==false)
             error("Cannot create this plan");
    else {
        Settlement temp= simulation.getSettlement(settlementName);
        simulation.addPlan(&temp,simulation.stringToSelPol(selectionPolicy));
        complete();
         }

}

const string AddPlan::toString() const{
    return "Plan "+ settlementName +" "+ this->selectionPolicy +" "+ActionStatusToString(this->getStatus()) ;
}

AddPlan *AddPlan::clone() const{
    return new AddPlan(*this);
}

//addsettlement
AddSettlement::AddSettlement(const string &settlementName,SettlementType settlementType):
BaseAction(), settlementName(settlementName), settlementType(settlementType)
{}

void AddSettlement::act(Simulation &simulation){
if(simulation.isSettlementExists(settlementName))
    error("Settlement already exists");
else{
    Settlement* s= new Settlement(settlementName,settlementType);
    simulation.addSettlement(s);
    complete();
}


} 

AddSettlement *AddSettlement::clone() const{
    return new AddSettlement(*this);
}

const string AddSettlement::toString() const{
    return "settlement "+ settlementName+" "+
    std::to_string((int)settlementType)+" "+
    ActionStatusToString(this->getStatus());
}

//addfacility
AddFacility::AddFacility(const string &facilityName, const FacilityCategory facilityCategory, const int price, const int lifeQualityScore, const int economyScore, const int environmentScore):
BaseAction(),
facilityName(facilityName),
facilityCategory(facilityCategory),
price(price),
lifeQualityScore(lifeQualityScore), 
economyScore(economyScore), 
environmentScore(environmentScore)
{}

void AddFacility::act(Simulation &simulation){
    if(simulation.isFacilityExists(facilityName))
        error("Facility already exists");
    else{
        FacilityType* temp = new FacilityType(facilityName,facilityCategory, price,lifeQualityScore,economyScore,environmentScore);
        simulation.addFacility(*temp);
        complete();
    }

}

AddFacility *AddFacility::clone() const{
        return new AddFacility(*this);
}

const string AddFacility::toString() const{
    return "facility "+ facilityName+" "+std::to_string((int)facilityCategory)+" "+
    std::to_string(price)+" "+std::to_string(lifeQualityScore)+" "+
    std::to_string(economyScore)+" "+std::to_string(environmentScore)+" "+
    ActionStatusToString(this->getStatus());
}


//print plan status
PrintPlanStatus::PrintPlanStatus(int planId):
BaseAction(), planId(planId)
{}

void PrintPlanStatus::act(Simulation &simulation){
    if(simulation.isPlanID(planId)==false)
        error("Plan doesn't exist");
    else{
        simulation.getPlan(planId).printStatus();
        complete();
    }
}

PrintPlanStatus *PrintPlanStatus::clone() const{
     return new PrintPlanStatus(*this);
}

const string PrintPlanStatus::toString() const{
    return "planStatus "+
    std::to_string(this->planId)+" "+
    ActionStatusToString(this->getStatus());
}

//change plan policy
ChangePlanPolicy::ChangePlanPolicy(const int planId, const string &newPolicy):
BaseAction(),planId(planId), newPolicy(newPolicy)
{}

void ChangePlanPolicy::act(Simulation &simulation){
    if (simulation.getPlan(planId).getSP() == newPolicy || simulation.isPlanID(planId)==false)
        error("Cannot change selection policy");
    else{
        string temp= simulation.getPlan(planId).getSP();
        simulation.getPlan(planId).setSelectionPolicy(simulation.stringToSelPol(newPolicy));
        complete();
        cout<< "PlanId: " << std::to_string(planId) << endl;
        cout<< "previousPolicy: " << temp << endl;
        cout<< "newPolicy: " << newPolicy<< endl;
    }
}

ChangePlanPolicy *ChangePlanPolicy::clone() const{
    return new ChangePlanPolicy(*this);
}

const string ChangePlanPolicy::toString() const{
    string s= std::to_string(planId);
    return "changePolicy "+ s +" "+newPolicy
    +" "+ActionStatusToString(this->getStatus());
}

//print actions log
PrintActionsLog::PrintActionsLog():BaseAction(){}
void PrintActionsLog::act(Simulation &simulation){
    for(BaseAction* temp: simulation.getActionLog()){
       cout << temp->toString()  << endl;}
    complete();
}

PrintActionsLog *PrintActionsLog::clone() const{
        return new PrintActionsLog(*this);
}

const string PrintActionsLog::toString() const{
    return "printActionsLog";
}

//close
Close::Close():BaseAction(){}
void Close::act(Simulation &simulation){
    complete();
    simulation.close();
}

Close *Close::clone() const{
    return new Close(*this);
}

const string Close::toString() const{
    return "Closed";
}

//backup simulation
BackupSimulation::BackupSimulation(): BaseAction(){}
void BackupSimulation::act(Simulation &simulation){
 
    delete backup;
    backup=nullptr;
    backup = new Simulation(simulation);
    complete();
}

BackupSimulation *BackupSimulation::clone() const{
    return new BackupSimulation(*this);
}

const string BackupSimulation::toString() const{
    return "backup "+ActionStatusToString(this->getStatus());
}

//restore simulation
RestoreSimulation::RestoreSimulation():BaseAction(){}
void RestoreSimulation::act(Simulation &simulation){
    if (backup == nullptr)
    {
       error("No backup available");
    }
    else{
        simulation = *backup;
        complete();
    }
}

RestoreSimulation *RestoreSimulation::clone() const{
    return new RestoreSimulation(*this);
}

const string RestoreSimulation::toString() const{
    return "restoreSimulation";
}























