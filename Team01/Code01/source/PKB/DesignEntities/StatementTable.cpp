#include "StatementTable.h"

INDEX StatementTable::addStatementNode(STMT_NODE_PTR node) {
    INDEX index = table_.size();
    table_.push_back(node);
    return index;
}

STMT_NODE_PTR_LIST StatementTable::getStatementNodeList() {
    STMT_NODE_PTR_LIST copy;
    for (STMT_NODE_PTR node : table_) {
        copy.push_back(node);
    }
    return copy;
}
