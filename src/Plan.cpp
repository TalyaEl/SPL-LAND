#include "Plan.h"
#include <vector>
#include "Facility.h"
#include "Settlement.h"
#include "SelectionPolicy.h"
using std::vector;

string PlanStatusToString(PlanStatus t){
    if (t == PlanStatus:: AVALIABLE)
        return "AVALIABLE";
    if (t == PlanStatus:: BUSY)
        return "BUSY"  ;
}
Plan::Plan(const int planId, const Settlement &settlement, SelectionPolicy *selectionPolicy, const vector<FacilityType> &facilityOptions)
:plan_id(planId), 
settlement(settlement)//why doesnt it allow &&&
selectionPolicy(selectionPolicy)
status(AVALIABLE)
facilityOptions(facilityOptions)//check this
underConstruction(vector<Facility*>)//check if should be on heap
facilities(vector<Facility*>)//as we finish building somthing it needs to be adde here
life_quality_score(0), economy_score(0), environment_score(0)
{}
