#include "Settlement.h"
#include <string>
#include <iostream>

using std::string;
using std::vector;

string SettlementTypeToString(SettlementType type){
    switch (type) {
        case SettlementType:: VILLAGE:
            return "VILLAGE";
        case SettlementType:: CITY:
            return "CITY";
        case SettlementType:: METROPOLIS:
            return "METROPOLIS";
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

int main(){
    std::cout << "hello\n";
    return 0;
}