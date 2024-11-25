#include "Action.h"
#include <string>
#include <vector>
#include "Simulation.h"
enum class SettlementType;
enum class FacilityCategory;
string ActionStatusToString(ActionStatus t){
    if (t == ActionStatus:: COMPLETED)
        return "COMPLETED";
    if (t == ActionStatus:: ERROR)
        return "ERROR";
}

//addplan
AddPlan::AddPlan(const string &settlementName, const string &selectionPolicy)
:settlementName(settlementName),selectionPolicy(selectionPolicy)
{}

