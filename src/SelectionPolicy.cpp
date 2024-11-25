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
    std::cout << "Naive Selection";
}

NaiveSelection* NaiveSelection::clone() const {
    return new NaiveSelection(*this);
}

//Balanced Selection

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
    std::cout << "Economy Selection";
}

EconomySelection* EconomySelection::clone() const {
    return new EconomySelection(*this);
}

//Sustainability Selection
SustainabilitySelection();
