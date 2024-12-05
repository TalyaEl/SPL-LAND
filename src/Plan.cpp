#include "Plan.h"
#include <vector>
#include "Facility.h"
#include "Settlement.h"
#include "SelectionPolicy.h"
#include <iostream>
#include <sstream>

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
selectionPolicy(selectionPolicy->clone()),
status(PlanStatus::AVALIABLE),
facilities(),
underConstruction(),
facilityOptions(facilityOptions),
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
    delete selectionPolicy;
    this->selectionPolicy = selectionPolicy->clone();
}

void Plan::step(){
    if(status == PlanStatus::AVALIABLE){
    while (underConstruction.size()<settlement.getConstructionLimit()) {
        Facility* newFacility = new Facility(selectionPolicy->selectFacility(facilityOptions), settlement.getName());
        underConstruction.push_back(newFacility);
     
    }}

    for (Facility* f: underConstruction) {
        f->step();
    }

    for (int i = underConstruction.size() - 1; i >= 0; i--) {
        if (underConstruction[i]->getStatus() == FacilityStatus::OPERATIONAL) {
            life_quality_score += underConstruction[i]->getLifeQualityScore();
            economy_score += underConstruction[i]->getEconomyScore();
            environment_score += underConstruction[i]->getEnvironmentScore();
            addFacility(underConstruction[i]);
            underConstruction.erase(underConstruction.begin() + i);
            status= PlanStatus::AVALIABLE;
        }
    }
    if(underConstruction.size()== settlement.getConstructionLimit())
        status= PlanStatus::BUSY;
    else
        status= PlanStatus::AVALIABLE;
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

void Plan::addFacility(Facility* facility){ 
    if (facility->getStatus() == FacilityStatus::OPERATIONAL)
        facilities.push_back(facility);
    else
        underConstruction.push_back(facility);
}

const string Plan::toString() const{ 
    std::ostringstream oss;
    oss << "PlanId:" << plan_id << endl;
    oss << "SettlementName:" << settlement.getName() << endl;
    oss << "LifeQualityScore:" << life_quality_score << endl;
    oss << "EconomyScore:" << economy_score << endl;
    oss << "EnvironmentScore:" << environment_score << endl;
    return oss.str();
}

 Plan::Plan(const Plan& other): 
 plan_id(other.plan_id), 
 settlement(other.settlement), 
 selectionPolicy(other.selectionPolicy->clone()), 
 status(other.status), 
 facilities(), 
 underConstruction(), 
 facilityOptions(other.facilityOptions), 
 life_quality_score(other.life_quality_score),
 economy_score(other.economy_score), 
 environment_score(other.environment_score){
    for (size_t i = 0; i < other.facilities.size(); i++) {
        Facility* temp = new Facility(other.facilities[i]->getName(), other.facilities[i]->getSettlementName(),
        other.facilities[i]->getCategory(), other.facilities[i]->getCost(), other.facilities[i]->getLifeQualityScore(), 
        other.facilities[i]->getEconomyScore(), other.facilities[i]->getEnvironmentScore());
        facilities.push_back(temp);
    }
    for (size_t i = 0; i < other.underConstruction.size(); i++) {
        Facility* temp = new Facility(other.underConstruction[i]->getName(), other.underConstruction[i]->getSettlementName(),
        other.underConstruction[i]->getCategory(), other.underConstruction[i]->getCost(), other.underConstruction[i]->getLifeQualityScore(), 
        other.underConstruction[i]->getEconomyScore(), other.underConstruction[i]->getEnvironmentScore());  
        underConstruction.push_back(temp);
    }
 }

 Plan::Plan(const Plan& other, const Settlement &settlement): //helper
 plan_id(other.plan_id),
 settlement(settlement),
 selectionPolicy(other.selectionPolicy->clone()), 
 status(other.status), 
 facilities(), 
 underConstruction(), 
 facilityOptions(other.facilityOptions), 
 life_quality_score(other.life_quality_score),
 economy_score(other.economy_score), 
 environment_score(other.environment_score){
    for (size_t i = 0; i < other.facilities.size(); i++) {
        Facility* temp = new Facility(other.facilities[i]->getName(), other.facilities[i]->getSettlementName(),
        other.facilities[i]->getCategory(), other.facilities[i]->getCost(), other.facilities[i]->getLifeQualityScore(), 
        other.facilities[i]->getEconomyScore(), other.facilities[i]->getEnvironmentScore());
        facilities.push_back(temp);
    }
    for (size_t i = 0; i < other.underConstruction.size(); i++) {
        Facility* temp = new Facility(other.underConstruction[i]->getName(), other.underConstruction[i]->getSettlementName(),
        other.underConstruction[i]->getCategory(), other.underConstruction[i]->getCost(), other.underConstruction[i]->getLifeQualityScore(), 
        other.underConstruction[i]->getEconomyScore(), other.underConstruction[i]->getEnvironmentScore());  
        underConstruction.push_back(temp);
    }
 }

 Plan::Plan(Plan&& other): 
 plan_id(other.plan_id), 
 settlement(other.settlement), 
 selectionPolicy(other.selectionPolicy->clone()), 
 status(other.status), 
 facilities(), 
 underConstruction(), 
 facilityOptions(other.facilityOptions), 
 life_quality_score(other.life_quality_score),
 economy_score(other.economy_score), 
 environment_score(other.environment_score){
    other.selectionPolicy = nullptr;
    for (size_t i = 0; i < other.facilities.size(); i++) {
        facilities.push_back(other.facilities[i]);
        delete other.facilities[i];
    }
    for (size_t i = 0; i < other.underConstruction.size(); i++) {
        underConstruction.push_back(other.underConstruction[i]);
        delete other.underConstruction[i];
    }
 }

 Plan::~Plan() {
    delete selectionPolicy;
    for (size_t i = 0; i < facilities.size(); i++) {
        delete facilities[i];
    }
    for (size_t i = 0; i < underConstruction.size(); i++) {
        delete underConstruction[i];
    }
 }

string Plan::getSP(){
    return selectionPolicy->toString();
}

const Settlement& Plan::getSettlement(){
    return settlement;
}