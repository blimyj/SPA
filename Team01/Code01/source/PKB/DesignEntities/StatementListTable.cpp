#include "StatementListTable.h"

INDEX StatementListTable::addStatementListNode(STMT_LIST_NODE_PTR node) {
    INDEX index = nodes_.size();
    nodes_.push_back(node);
    return index;
}

STMT_LIST_NODE_PTR_LIST StatementListTable::getStatementListNodeList() {
    return STMT_LIST_NODE_PTR_LIST(nodes_);
}
