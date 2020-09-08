#include "AssignTable.h"

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
