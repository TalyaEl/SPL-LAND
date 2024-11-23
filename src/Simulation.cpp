#include <string>
#include <vector>
#include "Facility.h"
#include "Plan.h"
#include "Settlement.h"
#include <iostream>
using std::string;
using std::vector;

class BaseAction;
class SelectionPolicy;
class Simulation{
 private:
        bool isRunning;
        int planCounter; //For assigning unique plan IDs
        vector<BaseAction*> actionsLog;
        vector<Plan> plans;
        vector<Settlement> settlements;
        vector<FacilityType> facilitiesOptions;

public:
void start(){
     std::cout << "the simulation has started";
}
void close(){
        isRunning=false;
}
};