#include "Action.h"
#include <string>
#include <vector>
#include "Simulation.h"
#include <iostream>
using std::cout;
using std::endl;

enum class SettlementType;
enum class FacilityCategory;

string ActionStatusToString(ActionStatus t){
    if (t == ActionStatus:: COMPLETED)
        return "COMPLETED";
    else (t == ActionStatus:: ERROR)
        return "ERROR";
   
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
    std::cout << errorMsg << std::endl;
}

const string &BaseAction::getErrorMsg() const{
    return errorMsg;
}

//simulation step
SimulateStep::SimulateStep(const int numOfSteps):
BaseAction(),numOfSteps(numOfSteps)
{}

void SimulateStep::act(Simulation &simulation){
  for (size_t i = 0; i < numOfSteps; i++)
  {
   simulation.step();
  } 
}

const string SimulateStep::toString() const{
    return "step done";
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
    if(simulation.isSettlementExists(settlementName)==false)
        error("Cannot create this plan");
    Settlement* temp= simulation.getSettlement(settlementName);
    Plan* p= new Plan(simulation.getPlanCounter(), temp , selectionPolicy, simulation.getfacilitiesOptions());
    simulation.addPlan(p);
}

const string AddPlan::toString() const{
    return "plan added";
}

AddPlan *AddPlan::clone() const{
    return new Addplan(*this);
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
}
} 

AddSettlement *AddSettlement::clone() const{
    return new AddSettlement(*this);
}

const string AddSettlement::toString() const{
    return "settlement added";
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
    }
}

AddFacility *AddFacility::clone() const{
        return new AddFacility(*this);
}

const string AddFacility::toString() const{
    return "facility added";
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
    }
}

PrintPlanStatus *PrintPlanStatus::clone() const{
     return new PrintPlanStatus(*this);
}

const string PrintPlanStatus::toString() const{
    return "plan printed";
}

//change plan policy
ChangePlanPolicy::ChangePlanPolicy(const int planId, const string &newPolicy):
BaseAction(),planId(planId), newPolicy(newPolicy)
{}

void ChangePlanPolicy::act(Simulation &simulation){
    if (simulation.getPlan(planId).getSP() == newPolicy)
        error("Cannot change selection policy")
    else
        simulation.getPlan(planId).setSelectionPolicy(stringToSelPol(newPolicy));
}

ChangePlanPolicy *ChangePlanPolicy::clone() const{
    return new ChangePlanPolicy(*this);
}

const string ChangePlanPolicy::toString() const{
    return "selection policy changed";
}

















