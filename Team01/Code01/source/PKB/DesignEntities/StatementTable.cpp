#include "StatementTable.h"

INDEX StatementTable::addStatementNode(STMT_NODE_PTR node) {
    INDEX index = nodes_.size();
    nodes_.push_back(node);
    return index;
}

STMT_NODE_PTR_LIST StatementTable::getStatementNodeList() {
    return STMT_NODE_PTR_LIST(nodes_);
}

STMT_NUM_LIST StatementTable::getStatementNumList() {
    std::vector<STMT_NUM> result;
    for (STMT_NODE_PTR n : nodes_) {
        STMT_NUM s = n.get()->getStatementNumber();
        result.push_back(s);
    }
    return result;
}
