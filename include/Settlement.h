#pragma once
#include <string>
#include <vector>
using std::string;
using std::vector;

class Facility;

enum class SettlementType {
    VILLAGE,
    CITY,
    METROPOLIS,
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