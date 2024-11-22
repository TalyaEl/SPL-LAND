#include "Settelment.h"
Settlement(const string &name, SettlementType type)
: const string name =&name, SettlementType =type
{}
~Settelment(){
    delete type;
}
const string &getName() const{
    return this.&name
}
SettlementType getType() const{
    return this.type;
}
const string toString() const{
    return string s(this.&name "," this.type)
}