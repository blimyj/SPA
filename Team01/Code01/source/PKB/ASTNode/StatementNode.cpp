#include "StatementNode.h"

StatementNode::StatementNode() {
    stmt_num_ = NULL;
    stmt_list_node_ptr_ = nullptr;
}

BOOLEAN_TYPE StatementNode::setStatementNumber(STMT_NUM stmt_num) {
    try {
        stmt_num_ = stmt_num;
    } catch (int e) {
        (void)e;
        return false;
    }
    return true;
}

BOOLEAN_TYPE StatementNode::setStatementListNode(STMT_LIST_NODE_PTR stmt_list_node_ptr) {
    try {
        stmt_list_node_ptr_ = stmt_list_node_ptr;
    } catch (int e) {
        (void)e;
        return false;
    }
    return true;
}

STMT_NUM StatementNode::getStatementNumber() {
    return stmt_num_;
}

STMT_LIST_NODE_PTR StatementNode::getParentStatementListNode() {
    return stmt_list_node_ptr_;
}
