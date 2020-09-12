#include "StatementTable.h"

INDEX StatementTable::addStatementNode(STMT_NODE_PTR node) {
    INDEX index = nodes_.size();
    nodes_.push_back(node);
    return index;
}

STMT_NODE_PTR_LIST StatementTable::getStatementNodeList() {
    return std::vector<STMT_NODE_PTR>(nodes_);
}
