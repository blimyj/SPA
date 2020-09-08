typedef int INDEX;
typedef std::shared_ptr<ConstantNode> CONSTANT_NODE_PTR;
typedef std::vector<CONSTANT_NODE_PTR> TABLE;
typedef std::vector<CONSTANT_NODE_PTR> CONSTANT_NODE_PTR_LIST;

#include <iostream>
#include <vector>
#include "ConstantTable.h"
#include "../ASTNode/ConstantNode.h"

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
