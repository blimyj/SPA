#include <iostream>
#include <vector>
#include "AssignTable.h"
#include "AssignNode.h"

typedef int INDEX;
typedef AssignNode ASSIGN_NODE_PTR;
typedef std::vector<ASSIGN_NODE_PTR> TABLE;
typedef std::vector<ASSIGN_NODE_PTR> ASSIGN_NODE_PTR_LIST;

INDEX AssignTable::addAssignNode(ASSIGN_NODE_PTR node) {
    INDEX index = table_.size();
    table_.push_back(node);
    return index;
}

ASSIGN_NODE_PTR_LIST AssignTable::getAssignNodeList() {
    ASSIGN_NODE_PTR_LIST copy;
    for (ASSIGN_NODE_PTR node : table_) {
        copy.push_back(node);
    }
    return copy;
}
