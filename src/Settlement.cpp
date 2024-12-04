#include "Settlement.h"
#include <string>
#include <iostream>

using std::string;
using std::vector;

string SettlementTypeToString(SettlementType type){ //helper
    switch (type) {
        case SettlementType:: VILLAGE:
            return "VILLAGE";
        case SettlementType:: CITY:
            return "CITY";
        case SettlementType:: METROPOLIS:
            return "METROPOLIS";
        default:
            return "UNKNOWN";
    }
}

Settlement::Settlement(const string &name , SettlementType type)
        :name(name), type(type){}

    const  string &Settlement::getName() const{
        return name;
}
    SettlementType Settlement::getType() const{
         return type;
}
    const string Settlement::toString() const{
         return name+"," + SettlementTypeToString(type);
}
    int Settlement::getConstructionLimit() const{
        if(type==SettlementType::VILLAGE)
            return 1;
        if(type==SettlementType::CITY)
            return 2;
        else
            return 3;
    }
