#include "SelectionPolicy.h"
#include <string>
#include <iostream>
#include <stdexcept>
// #include <sstream>

using std::vector;
using std::string;
// using std::stringstream;

//Naive Selection
NaiveSelection::NaiveSelection(): lastSelectedIndex(-1) {}

const FacilityType& NaiveSelection::selectFacility(const vector<FacilityType>& facilitiesOptions){
    if (facilitiesOptions.empty()) {
        throw std::out_of_range("The list is empty");
    }
    lastSelectedIndex = (lastSelectedIndex + 1) % facilitiesOptions.size();
    return facilitiesOptions[lastSelectedIndex];
} ;  

const string NaiveSelection::toString() const {
    // stringstream ss;
    // if (lastSelectedIndex == -1) {
    //     ss << "Naive Selection, No facility has been chosen yet.";
    // }
    // else {
    //     ss << "Naive Selection, last selected index is:"+lastSelectedIndex;
    // }
    //return ss.str(); does we need to delete this object?
    return "Naive Selection";
}

NaiveSelection* NaiveSelection::clone() const {
    return new NaiveSelection(*this);
}

//Balanced Selection
BalancedSelection::BalancedSelection(int LifeQualityScore, int EconomyScore, int EnvironmentScore):
LifeQualityScore(LifeQualityScore), EconomyScore(EconomyScore), EnvironmentScore(EnvironmentScore) {}

const FacilityType& BalancedSelection::selectFacility(const vector<FacilityType>& facilitiesOptions) {

}

const string BalancedSelection::toString() const {
    return "Balanced Selection";
}

BalancedSelection* BalancedSelection::clone() const {
    return new BalancedSelection(*this);
}

//Economy Selection
EconomySelection::EconomySelection(): lastSelectedIndex(-1) {}

const FacilityType& EconomySelection::selectFacility(const vector<FacilityType>& facilitiesOptions){
    if (facilitiesOptions.empty()) {
        throw std::out_of_range("The list is empty");
    }
    int startIndex = lastSelectedIndex;
    lastSelectedIndex = (lastSelectedIndex + 1) % facilitiesOptions.size();
    while (facilitiesOptions[lastSelectedIndex].getCategory() != FacilityCategory::ECONOMY){
        if (lastSelectedIndex == startIndex) {
            throw std::runtime_error("No facility of economy category found.");
        }
        lastSelectedIndex = (lastSelectedIndex + 1) % facilitiesOptions.size();
    }
    return facilitiesOptions[lastSelectedIndex];
}

const string EconomySelection::toString() const {
    return "Economy Selection";
}

EconomySelection* EconomySelection::clone() const {
    return new EconomySelection(*this);
}

//Sustainability Selection
SustainabilitySelection::SustainabilitySelection(): lastSelectedIndex(-1) {}

const FacilityType& SustainabilitySelection::selectFacility(const vector<FacilityType>& facilitiesOptions) {
        if (facilitiesOptions.empty()) {
        throw std::out_of_range("The list is empty");
    }
    int startIndex = lastSelectedIndex;
    lastSelectedIndex = (lastSelectedIndex + 1) % facilitiesOptions.size();
    while (facilitiesOptions[lastSelectedIndex].getCategory() != FacilityCategory::ENVIRONMENT){
        if (lastSelectedIndex == startIndex) {
            throw std::runtime_error("No facility of environment category found.");
        }
        lastSelectedIndex = (lastSelectedIndex + 1) % facilitiesOptions.size();
    }
    return facilitiesOptions[lastSelect;..edIndex];
}

const string SustainabilitySelection::toString() const {
    return "Sustainability Selection";
}

SustainabilitySelection* SustainabilitySelection::clone() const {
    return new SustainabilitySelection(*this);
}

