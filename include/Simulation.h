#pragma once
#include <string>
#include <vector>
#include "Facility.h"
#include "Plan.h"
#include "Settlement.h"

using std::string;
using std::vector;

class BaseAction;
class SelectionPolicy;
class Simulation {
    public:
        Simulation(const string &configFilePath);
        Simulation(const Simulation& other);
        Simulation(Simulation&& otherTemp) noexcept;
        Simulation& operator=(const Simulation& other);
        Simulation& operator=(Simulation&& otherTemp) noexcept;
        ~Simulation();

        // void start();
        void addPlan(const Settlement *settlement, SelectionPolicy *selectionPolicy);
        void addAction(BaseAction *action);
        bool addSettlement(Settlement *settlement);
        bool addFacility(FacilityType facility);
        bool isSettlementExists(const string &settlementName);
        Settlement *getSettlement(const string &settlementName);
        Plan &getPlan(const int planID);
        void step();
        void close();
        void open();
        
        int getPlanCounter();
        vector<FacilityType> &getfacilitiesOptions();
        bool isFacilityExists(const string &FacilityName);
        bool isPlanID(int planID);
        const vector<BaseAction*> getActionLog();

        void readMe(const string &configFilePath);
        SettlementType stringToSetType(const string &settlementType);
        FacilityCategory stringToFacCat(const string &facilityCategory);
        SelectionPolicy* stringToSelPol(const string &selectionPolicy);
        void clear();

    private:
        bool isRunning;
        int planCounter; //For assigning unique plan IDs
        vector<BaseAction*> actionsLog;
        vector<Plan> plans;
        vector<Settlement*> settlements;
        vector<FacilityType> facilitiesOptions;

        Plan invalidPlan;

};