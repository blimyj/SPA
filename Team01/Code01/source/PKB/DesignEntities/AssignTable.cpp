#include "AssignTable.h"

INDEX AssignTable::addAssignNode(ASSIGN_NODE_PTR node) {
    INDEX index = nodes_.size();
    nodes_.push_back(node);
    return index;
}

ASSIGN_NODE_PTR_LIST AssignTable::getAssignNodeList() {
    ASSIGN_NODE_PTR_LIST copy;
    for (ASSIGN_NODE_PTR node : nodes_) {
        copy.push_back(node);
    }
    return copy;
}

STMT_NUM_LIST AssignTable::getAssignNumList() {
    std::vector<STMT_NUM> result;
    for (ASSIGN_NODE_PTR n : nodes_) {
        STMT_NUM s = n.get()->getStatementNumber();
        result.push_back(s);
    }
    return result;
}
