#include "SelectionPolicy.h"
#include <string>
#include <iostream>
#include <stdexcept>

using std::vector;

NaiveSelection::NaiveSelection(): lastSelectedIndex(-1) {}
const FacilityType& NaiveSelection::selectFacility(const vector<FacilityType>& facilitiesOptions){
    if (facilitiesOptions.empty()) {
        throw std::out_of_range("The list is empty");
    }
    if (lastSelectedIndex == facilitiesOptions.size() - 1){
        lastSelectedIndex = 0;
    }
    else {
        lastSelectedIndex++;
    }
    return facilitiesOptions[lastSelectedIndex];
} ;  