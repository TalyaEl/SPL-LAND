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
    else
        return "Shouldn't be here :(";
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

int main(){
    std::cout << "hello\n";
    return 0;
}