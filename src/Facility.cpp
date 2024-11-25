#include "Facility.h"
using namespace std;

string facilityStatusToString(FacilityStatus t){
    if (t == FacilityStatus:: UNDER_CONSTRUCTIONS)
        return "UNDER_CONSTRUCTIONS";
    if (t == FacilityStatus:: OPERATIONAL)
        return "OPERATIONAL"  ;
}
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

        Facility::Facility(const string &name, const string &settlementName, const FacilityCategory category, const int price, const int lifeQuality_score, const int economy_score, const int environment_score)
        : FacilityType(name, category, price,lifeQuality_score,economy_score ,environment_score),
          settlementName(settlementName),
          status(FacilityStatus::OPERATIONAL),
          timeLeft(0)
        {}
        Facility::Facility(const FacilityType &type, const string &settlementName)
        : FacilityType(type),
          settlementName(settlementName),
          status(FacilityStatus::OPERATIONAL),
          timeLeft(0)
           
        {}
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
           status=status;
        }
        const FacilityStatus& Facility::getStatus() const{
            return status;
        }
        const string Facility::toString() const{
            return getName()+", "+facilityStatusToString(status);
        }
        void Facility::reduceTime(){
            timeLeft--;

        }


