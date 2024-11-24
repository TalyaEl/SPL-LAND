#include "Facility.h"
using namespace std;


// FacilityType:
        FacilityType::FacilityType(const string &name, const FacilityCategory category, const int price, const int lifeQuality_score, const int economy_score, const int environment_score):
        name(name), category(category), price(price), lifeQuality_score(lifeQuality_score), economy_score(economy_score), environment_score(environment_score),score({lifeQuality_score,economy_score,environment_score})
        {}
        const string & FacilityType::getName() const{
            return name;
        }
        int  FacilityType::getCost() const{
            return price;
        }
        int  FacilityType::getLifeQualityScore() const{
            return lifeQuality_score;
        }
        int  FacilityType::getEnvironmentScore() const{
            return environment_score;
        }
        int  FacilityType::getEconomyScore() const{
            return economy_score;
        }
        FacilityCategory  FacilityType::getCategory() const{
            return category;
        }

        //Facility:

        Facility::Facility(const string &name, const string &settlementName, const FacilityCategory category, const int price, const int lifeQuality_score, const int economy_score, const int environment_score);

        const string &Facility::getSettlementName() const{
            return  settlementName;
        }
        const int Facility::getTimeLeft() const{
            return timeLeft;
        }
        FacilityStatus Facility::step(){//not sure this is correct
            timeLeft--;
        }
        void Facility::setStatus(FacilityStatus status){
           _status=status;
        }
        const FacilityStatus& Facility::getStatus() const{
            return _status;
        }
        

