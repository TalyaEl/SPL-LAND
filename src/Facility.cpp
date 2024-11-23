#include "Facility.h"
using namespace std;

class FacilityType {
    protected:
    const string name;
    const FacilityCategory category;
    const int price;
    const int lifeQuality_score;
    const int economy_score;
    const int environment_score;
    const int score[3]; //added feild

    public:
// FacilityType:
        FacilityType(const string &name, const FacilityCategory category, const int price, const int lifeQuality_score, const int economy_score, const int environment_score):
        name(name), category(category), price(price), lifeQuality_score(lifeQuality_score), economy_score(economy_score), environment_score(environment_score),score({lifeQuality_score,economy_score,environment_score})
        {}
        const string &getName() const{
            return name;
        }
        int getCost() const{
            return price;
        }
        int getLifeQualityScore() const{
            return lifeQuality_score;
        }
        int getEnvironmentScore() const{
            return environment_score;
        }
        int getEconomyScore() const{
            return economy_score;
        }
        FacilityCategory getCategory() const{
            return category;
        }
 };
        //Facility:
class Facility {
    private:
        const string settlementName;
        FacilityStatus _status;
        int timeLeft;
    
    public:
        Facility(const string &name, const string &settlementName, const FacilityCategory category, const int price, const int lifeQuality_score, const int economy_score, const int environment_score);

        const string &getSettlementName() const{
            return  settlementName;
        }
        const int getTimeLeft() const{
            return timeLeft;
        }
        FacilityStatus step(){//not sure this is correct
            timeLeft--;
        }
        void setStatus(FacilityStatus status){
           _status=status;
        }
        const FacilityStatus& getStatus() const{
            return _status;
        }
        const string toString() const{

        }
};
