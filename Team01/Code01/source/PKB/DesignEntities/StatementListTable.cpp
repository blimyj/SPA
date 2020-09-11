#include "StatementListTable.h"

INDEX StatementListTable::addStatementListNode(STMT_LIST_NODE_PTR node) {
    INDEX index = table_.size();
    table_.push_back(node);
    return index;
}

STMT_LIST_NODE_PTR_LIST StatementListTable::getStatementListNodeList() {
    STMT_LIST_NODE_PTR_LIST copy;
    for (STMT_LIST_NODE_PTR node : table_) {
        copy.push_back(node);
    }
    return copy;
}
