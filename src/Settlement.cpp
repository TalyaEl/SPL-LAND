#include "Settlement.h"
#include <string>
#include <iostream>

using namespace std;

string SettlementTypeToString(SettlementType t){
    if (t == SettlementType:: VILLAGE)
        return "VILLAGE";
    if (t == SettlementType:: CITY)
        return "CITY"  ;
    if (t == SettlementType:: METROPOLIS)
        return "METROPOLIS";
    
}
class Settlement{
private:
        const string name;
        SettlementType type;

public:
    Settlement(const string &name , SettlementType type)
        :name(name), type(type){}

    const string &getName() const{
        return name;
}
    SettlementType getType() const{
         return type;
}
    const string toString() const{
         return name+"," + SettlementTypeToString(type);
}
};