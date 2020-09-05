#include <iostream>
#include <vector>
#include "WhileTable.h"
#include "../ASTNode/WhileNode.h"

typedef int INDEX;
typedef WhileNode* WHILE_NODE_PTR;
typedef std::vector<WHILE_NODE_PTR> TABLE;
typedef std::vector<WHILE_NODE_PTR> WHILE_NODE_PTR_LIST;

INDEX WhileTable::addWhileNode(WHILE_NODE_PTR node) {
    INDEX index = table_.size();
    table_.push_back(node);
    return index;
}

WHILE_NODE_PTR_LIST WhileTable::getWhileNodeList() {
    WHILE_NODE_PTR_LIST copy;
    for (WHILE_NODE_PTR node : table_) {
        copy.push_back(node);
    }
    return copy;
}
