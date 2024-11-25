#include "Plan.h"
#include <vector>
#include "Facility.h"
#include "Settlement.h"
#include "SelectionPolicy.h"
#include <iostream>
using std::vector;

string PlanStatusToString(PlanStatus t){
    if (t == PlanStatus:: AVALIABLE)
        return "AVALIABLE";
    if (t == PlanStatus:: BUSY)
        return "BUSY"  ;
}
Plan::Plan(const int planId, const Settlement &settlement, SelectionPolicy *selectionPolicy, const vector<FacilityType> &facilityOptions)
:plan_id(planId),
settlement(&settlement),//why doesnt it allow &&&
selectionPolicy(selectionPolicy),
status(PlanStatus::AVALIABLE),
facilityOptions(facilityOptions),//check this
underConstruction(),//check if should be on heap
facilities(),//as we finish building somthing it needs to be added here
life_quality_score(0), economy_score(0), environment_score(0)
{}
const int Plan::getlifeQualityScore() const{
    return life_quality_score;
}
const int Plan::getEconomyScore() const{
    return economy_score;
}
const int Plan::getEnvironmentScore() const{
    return environment_score;
}
void Plan::setSelectionPolicy(SelectionPolicy *selectionPolicy){
    this->selectionPolicy = selectionPolicy;
}
void Plan::step(){
    for(int i=0;i<=underConstruction.size();i++){
        Facility* pf= underConstruction[i];
        pf->reduceTime();
        if(pf->getTimeLeft()<=0){
          facilities.push_back(pf);  
          underConstruction.erase(underConstruction.begin()+i);

    }}
}



