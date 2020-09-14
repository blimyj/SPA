#include "AssignTable.h"

INDEX AssignTable::addAssignNode(ASSIGN_NODE_PTR node) {
    INDEX index = nodes_.size();
    nodes_.push_back(node);
    return index;
}

ASSIGN_NODE_PTR_LIST AssignTable::getAssignNodeList() {
    return ASSIGN_NODE_PTR_LIST(nodes_);
}

STMT_NUM_LIST AssignTable::getAssignNumList() {
    std::vector<STMT_NUM> result;
    for (ASSIGN_NODE_PTR n : nodes_) {
        STMT_NUM s = n.get()->getStatementNumber();
        result.push_back(s);
    }
    return result;
}
