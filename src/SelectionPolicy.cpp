#include "SelectionPolicy.h"
#include <string>
#include <iostream>
#include <limits>
#include <algorithm>

using std::vector;
using std::string;

// Naive Selection
NaiveSelection::NaiveSelection(): lastSelectedIndex(-1) {}

const FacilityType& NaiveSelection::selectFacility(const vector<FacilityType>& facilitiesOptions){
    lastSelectedIndex = (lastSelectedIndex + 1) % facilitiesOptions.size();
    return facilitiesOptions[lastSelectedIndex];
} 

const string NaiveSelection::toString() const {
    return "nve";
}

NaiveSelection* NaiveSelection::clone() const {
    return new NaiveSelection(*this);
}

// Balanced Selection
BalancedSelection::BalancedSelection(int LifeQualityScore, int EconomyScore, int EnvironmentScore):
LifeQualityScore(LifeQualityScore), EconomyScore(EconomyScore), EnvironmentScore(EnvironmentScore) {}

const FacilityType& BalancedSelection::selectFacility(const vector<FacilityType>& facilitiesOptions) {
    int minDifference = std::numeric_limits<int>::max();
    size_t bestFacilityIndex = 0;

    for (size_t i = 0; i < facilitiesOptions.size(); i++) {
        const FacilityType& currentType = facilitiesOptions[i];
        int tempLifeQ = this->LifeQualityScore + currentType.getLifeQualityScore();
        int tempEconomy = this->EconomyScore + currentType.getEconomyScore();
        int tempEnvironment = this->EnvironmentScore + currentType.getEnvironmentScore();
        int maxScore = std::max({tempLifeQ, tempEconomy,tempEnvironment});
        int minScore = std::min({tempLifeQ, tempEconomy,tempEnvironment});
        
        if ((maxScore - minScore) < minDifference) {
            minDifference = maxScore - minScore;
            bestFacilityIndex = i;
        }
    }
    return facilitiesOptions[bestFacilityIndex];
}

const string BalancedSelection::toString() const {
    return "bal";
}

BalancedSelection* BalancedSelection::clone() const {
    return new BalancedSelection(*this);
}

// Economy Selection
EconomySelection::EconomySelection(): lastSelectedIndex(-1) {}

const FacilityType& EconomySelection::selectFacility(const vector<FacilityType>& facilitiesOptions){
    lastSelectedIndex = (lastSelectedIndex + 1) % facilitiesOptions.size();
    while (facilitiesOptions[lastSelectedIndex].getCategory() != FacilityCategory::ECONOMY){
        lastSelectedIndex = (lastSelectedIndex + 1) % facilitiesOptions.size();
    }
    return facilitiesOptions[lastSelectedIndex];
}

const string EconomySelection::toString() const {
    return "eco";
}

EconomySelection* EconomySelection::clone() const {
    return new EconomySelection(*this);
}

// Sustainability Selection
SustainabilitySelection::SustainabilitySelection(): lastSelectedIndex(-1) {}

const FacilityType& SustainabilitySelection::selectFacility(const vector<FacilityType>& facilitiesOptions) {
    lastSelectedIndex = (lastSelectedIndex + 1) % facilitiesOptions.size();
    while (facilitiesOptions[lastSelectedIndex].getCategory() != FacilityCategory::ENVIRONMENT){
        lastSelectedIndex = (lastSelectedIndex + 1) % facilitiesOptions.size();
    }
    return facilitiesOptions[lastSelectedIndex];
}

const string SustainabilitySelection::toString() const {
    return "env";
}

SustainabilitySelection* SustainabilitySelection::clone() const {
    return new SustainabilitySelection(*this);
}