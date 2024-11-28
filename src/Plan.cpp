#include "Plan.h"
#include <vector>
#include "Facility.h"
#include "Settlement.h"
#include "SelectionPolicy.h"
#include <iostream>

using std::vector;
using std::string;
using std::cout;
using std::endl;

string PlanStatusToString(PlanStatus t){
    if (t == PlanStatus:: AVALIABLE)
        return "AVALIABLE";
    else
        return "BUSY";
}

Plan::Plan(const int planId, const Settlement &settlement, SelectionPolicy *selectionPolicy, const vector<FacilityType> &facilityOptions)
:plan_id(planId),
settlement(settlement),
selectionPolicy(selectionPolicy),
status(PlanStatus::AVALIABLE),
facilityOptions(facilityOptions),
underConstruction(),
facilities(),
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

void Plan::setSelectionPolicy(SelectionPolicy *selectionPolicy){/// ask
    this->selectionPolicy = selectionPolicy;
}

void Plan::step(){
    for(int i=0;i<underConstruction.size();i++){
        Facility* pf= underConstruction[i];
        pf->step();
    }

    while(underConstruction.size()<(int)this->settlement->getType()){
        Facility* fac = (selectionPolicy->selectFacility(facilityOptions),  &settlement.getName());
        fac->setStatus(FacilityStatus::UNDER_CONSTRUCTIONS);
        addFacility(fac);
    }

    for(int i=0;i<underConstruction.size();i++){
        Facility* pf=underConstruction[i];
        if(pf->getTimeLeft()<=0){
          pf->setStatus(FacilityStatus::OPERATIONAL);
          addFacility(pf);  
          underConstruction.erase(underConstruction.begin()+i);
          life_quality_score+= pf->getLifeQualityScore();
          economy_score+= pf->getEconomyScore();
          environment_score+= pf->getEnvironmentScore();
          pf->setStatus(FacilityStatus::OPERATIONAL);
        }
    }

    if(underConstruction.size()==(int)this->settlement->getType()) {
        this->status= PlanStatus::BUSY;
    }
    else
        this->status= PlanStatus::AVALIABLE;
}


void Plan::printStatus(){
    cout << "PlanID:" << plan_id << endl;
    cout << "SettlementName:" << settlement.getName() << endl;
    cout << "Status:" << PlanStatusToString(status) << endl;
    cout << "SelectionPolicy:" << selectionPolicy->toString() << endl;
    cout << "LifeQualityScore:" << life_quality_score << endl;
    cout << "EconomyScore:" << economy_score << endl;
    cout << "EnvironmentScore:" << environment_score << endl;

    for(Facility* f: facilities){
        cout << "FacilityName:" << f->getName() << endl;
        cout << "FacilityStatus: OPERATIONAL" << endl;
    }
    for(Facility* f: underConstruction){
        cout << "FacilityName:" << f->getName() << endl;
        cout << "FacilityStatus: UNDER_CONSTRUCTION" << endl;
    }
}

const vector<Facility*> &Plan::getFacilities() const{
    return facilities;
}

void Plan::addFacility(Facility* facility){ ///not sure this is right implementation!!!!
    if(facility->getStatus() == FacilityStatus::OPERATIONAL)
        facilities.push_back(facility);
    else
        underConstruction.push_back(facility);
}

const string Plan::toString() const{
    cout << "PlanId:" << plan_id << endl;
    cout << "SettlementName:" << settlement.getName() << endl;
    cout << "LifeQualityScore:" << life_quality_score << endl;
    cout << "EconomyScore:" << economy_score << endl;
    cout << "EnvironmentScore:" << environment_score << endl;
}





