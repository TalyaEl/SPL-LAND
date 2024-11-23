#pragma once
#include <string>
#include <vector>
using std::string;
using std::vector;

class Facility;

enum class SettlementType {
    VILLAGE, //1 at a time
    CITY, //2 at a time
    METROPOLIS, //3 at a time
    //it starts from 0 like in an array
};

class Settlement {
    public:
        Settlement(const string &name, SettlementType type);// builder created
        const string &getName() const;//func created
        SettlementType getType() const;// func created
        const string toString() const;//func created
//destructor created
        private:
            const string name;
            SettlementType type;
};