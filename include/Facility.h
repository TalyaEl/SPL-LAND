#pragma once
#include <string>
#include <vector>
#include <array>
using std::string;
using std::vector;

enum class FacilityStatus {
    UNDER_CONSTRUCTIONS,
    OPERATIONAL,
};

enum class FacilityCategory {
    LIFE_QUALITY,
    ECONOMY,
    ENVIRONMENT,
};


class FacilityType {
    public:
        FacilityType(const string &name, const FacilityCategory category, const int price, const int lifeQuality_score, const int economy_score, const int environment_score);
        //builder created
        const string &getName() const; //v
        int getCost() const;//v
        int getLifeQualityScore() const;//v
        int getEnvironmentScore() const;//v
        int getEconomyScore() const;//v
        FacilityCategory getCategory() const;//v

    protected:
        const string name;
        const FacilityCategory category;
        const int price;
        const int lifeQuality_score;
        const int economy_score;
        const int environment_score;
};



class Facility: public FacilityType {

    public:
        Facility(const string &name, const string &settlementName, const FacilityCategory category, const int price, const int lifeQuality_score, const int economy_score, const int environment_score);
        Facility(const FacilityType &type, const string &settlementName);//what is the difference of both builders???
        const string &getSettlementName() const;//v
        const int getTimeLeft() const;//v
        FacilityStatus step();//v
        void setStatus(FacilityStatus status);//v
        const FacilityStatus& getStatus() const;//v
        const string toString() const;
        


    private:
        const string settlementName;
        FacilityStatus status;
        int timeLeft;
};