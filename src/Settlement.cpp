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

const string &Settlement::getName() const{
   return name;
}
SettlementType Settlement::getType() const{
         return type;
}
const string Settlement::toString() const{
         return name+"," + SettlementTypeToString(type);
}
size_t Settlement::getConstructionLimit() const{
        if(this->getType()==SettlementType::VILLAGE)
            return size_t(1);
        if(this->getType()==SettlementType::CITY)
            return size_t(2);
        else
            return size_t(3);
}
