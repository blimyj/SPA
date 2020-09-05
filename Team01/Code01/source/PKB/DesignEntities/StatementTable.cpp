#include <iostream>
#include <vector>
#include "StatementTable.h"
#include "../ASTNode/StatementNode.h"

typedef int INDEX;
typedef StatementNode* STMT_NODE_PTR;
typedef std::vector<STMT_NODE_PTR> TABLE;
typedef std::vector<STMT_NODE_PTR> STMT_NODE_PTR_LIST;

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
