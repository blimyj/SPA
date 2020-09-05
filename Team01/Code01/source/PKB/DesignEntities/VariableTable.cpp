#include <iostream>
#include <vector> 
#include "VariableTable.h"
#include "../ASTNode/VariableNode.h"

typedef int INDEX;
typedef VariableNode* VAR_NODE_PTR;
typedef std::vector<VAR_NODE_PTR> TABLE;
typedef std::vector<VAR_NODE_PTR> VAR_NODE_PTR_LIST;

INDEX VariableTable::addVariableNode(VAR_NODE_PTR node) {
    INDEX index = table_.size();
    table_.push_back(node);
    return index;
}

VAR_NODE_PTR_LIST VariableTable::getVariableNodeList() {
    VAR_NODE_PTR_LIST copy;
    for (VAR_NODE_PTR node : table_) {
        copy.push_back(node);
    }
    return copy;
}
