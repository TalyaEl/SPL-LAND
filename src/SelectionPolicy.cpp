#include "SelectionPolicy.h"
#include <string>
#include <iostream>
#include <stdexcept>

using std::vector;
using std::string;

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

const string NaiveSelection::toString() const {
    if (lastSelectedIndex == -1) {
        return "No facility has been chosen yet.";
    }
    else {
        return "Naive Selection, last selected index is:"+lastSelectedIndex;
    }
}

NaiveSelection* NaiveSelection::clone() const {
    return new NaiveSelection(*this);
}
