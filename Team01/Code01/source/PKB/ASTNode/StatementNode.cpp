typedef std::vector<std::shared_ptr<StatementNode>> STMT_LIST_NODE_PTR;
typedef bool BOOLEAN;
typedef int STMT_NUMBER;

#include <iostream>
#include <vector>
#include "StatementNode.h"

BOOLEAN StatementNode::setStatementNumber(STMT_NUMBER stmt_num) {
    try {
        stmt_num_ = stmt_num;
    } catch (int e) {
        return false;
    }
    return true;
}

BOOLEAN StatementNode::setStatementListNode(STMT_LIST_NODE_PTR stmt_list_node_ptr) {
    try {
        stmt_list_node_ptr_ = stmt_list_node_ptr;
    } catch (int e) {
        return false;
    }
    return true;
}

STMT_NUMBER StatementNode::getStatementNumber() {
    return stmt_num_;
}

STMT_LIST_NODE_PTR StatementNode::getParentStatementListNode() {
    return stmt_list_node_ptr_;
}
