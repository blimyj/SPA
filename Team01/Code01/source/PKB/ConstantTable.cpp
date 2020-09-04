#include <iostream>
#include <vector>
#include "ConstantTable.h"

typedef int INDEX;
typedef std::string CONSTANT_NAME;
typedef std::vector<CONSTANT_NAME> TABLE;
typedef std::vector<CONSTANT_NAME> CONSTANT_NAME_LIST;

INDEX ConstantTable::addConstantName(CONSTANT_NAME c) {
    INDEX index = table_.size();
    table_.push_back(c);
    return index;
}

CONSTANT_NAME_LIST ConstantTable::getConstantNameList() {
    CONSTANT_NAME_LIST copy;
    for (CONSTANT_NAME c : table_) {
        copy.push_back(c);
    }
    return copy;
}
