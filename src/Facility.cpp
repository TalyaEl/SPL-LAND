#include "Facility.h"

// FacilityType:
FacilityType(const string &name, const FacilityCategory category, const int price, const int lifeQuality_score, const int economy_score, const int environment_score):
_name(&name), _FacilityCategory(category), _price(price), _lifeQuality_score(lifeQuality_score), _economy_score(economy_score), _environment_score(environment_score)
{}//builder
const string &getName() const{
    return _name
}
int getCost() const{
    return _price;
}
int getLifeQualityScore() const{
    return _lifeQuality_score
}
int getEnvironmentScore() const{
    return _environment_score;
}
int getEconomyScore() const{
    return _economy_score;
}
FacilityCategory getCategory() const{
    return _FacilityCategory;
}
~FacilityType(){
    delete FacilityCategory
}

//Facility:
        Facility(const string &name, const string &settlementName, const FacilityCategory category, const int price, const int lifeQuality_score, const int economy_score, const int environment_score);
