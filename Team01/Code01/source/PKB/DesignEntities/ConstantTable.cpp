#include <iostream>
#include <vector>
#include "ConstantTable.h"

typedef int INDEX;
typedef std::string CONSTANT_NODE_PTR;
typedef std::vector<CONSTANT_NODE_PTR> TABLE;
typedef std::vector<CONSTANT_NODE_PTR> CONSTANT_NODE_PTR_LIST;

INDEX ConstantTable::addConstantName(CONSTANT_NODE_PTR node) {
    INDEX index = table_.size();
    table_.push_back(node);
    return index;
}

CONSTANT_NODE_PTR_LIST ConstantTable::getConstantNameList() {
    CONSTANT_NODE_PTR_LIST copy;
    for (CONSTANT_NODE_PTR node : table_) {
        copy.push_back(node);
    }
    return copy;
}
