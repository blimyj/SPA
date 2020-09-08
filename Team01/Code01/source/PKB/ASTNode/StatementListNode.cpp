typedef std::shared_ptr<StatementNode> STMT_NODE_PTR;
typedef std::vector<std::shared_ptr<StatementNode>> STMT_NODE_PTR_LIST;
typedef bool BOOLEAN;

#include <iostream>
#include <vector>
#include "StatementListNode.h"
#include "StatementNode.h"

BOOLEAN StatementListNode::addStatementNode(STMT_NODE_PTR stmt_node_ptr) {
    try {
        stmt_node_ptr_list_.push_back(stmt_node_ptr);
    } catch (int e) {
        return false;
    }
    return true;
}

STMT_NODE_PTR_LIST StatementListNode::getStatementNodeList() {
    return stmt_node_ptr_list_;
}
