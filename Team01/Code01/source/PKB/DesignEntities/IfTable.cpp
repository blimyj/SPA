#include <iostream>
#include <vector>
#include "IfTable.h"
#include "../ASTNode/IfNode.h"

typedef int INDEX;
typedef IfNode* IF_NODE_PTR;
typedef std::vector<IF_NODE_PTR> TABLE;
typedef std::vector<IF_NODE_PTR> IF_NODE_PTR_LIST;

INDEX IfTable::addIfNode(IF_NODE_PTR node) {
    INDEX index = table_.size();
    table_.push_back(node);
    return index;
}

IF_NODE_PTR_LIST IfTable::getIfNodeList() {
    IF_NODE_PTR_LIST copy;
    for (IF_NODE_PTR node : table_) {
        copy.push_back(node);
    }
    return copy;
}
