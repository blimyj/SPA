#include <iostream>
#include <vector> 
#include "VariableTable.h"

typedef int INDEX;
typedef std::string VARIABLE_NAME;
typedef std::vector<VARIABLE_NAME> TABLE;
typedef std::vector<VARIABLE_NAME> VARIABLE_NAME_LIST;

INDEX VariableTable::addVariableName(VARIABLE_NAME v) {
    INDEX index = table_.size();
    table_.push_back(v);
    return index;
}

VARIABLE_NAME_LIST VariableTable::getVariableNameList() {
    VARIABLE_NAME_LIST copy;
    for (VARIABLE_NAME v : table_) {
        copy.push_back(v);
    }
    return copy;
}
