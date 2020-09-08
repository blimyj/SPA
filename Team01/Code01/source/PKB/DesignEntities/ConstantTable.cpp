#include "ConstantTable.h"

INDEX ConstantTable::addConstantNode(CONSTANT_NODE_PTR node) {
    INDEX index = table_.size();
    table_.push_back(node);
    return index;
}

CONSTANT_NODE_PTR_LIST ConstantTable::getConstantNodeList() {
    CONSTANT_NODE_PTR_LIST copy;
    for (CONSTANT_NODE_PTR node : table_) {
        copy.push_back(node);
    }
    return copy;
}
