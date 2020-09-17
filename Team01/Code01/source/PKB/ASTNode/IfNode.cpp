#include "IfNode.h"

IfNode::IfNode(CONDITION_NODE_PTR condition_node_ptr, STMT_LIST_NODE_PTR then_stmt_list_node_ptr, STMT_LIST_NODE_PTR else_stmt_list_node_ptr) {
    setConditionNode(condition_node_ptr);
    setThenStatementListNode(then_stmt_list_node_ptr);
    setElseStatementListNode(else_stmt_list_node_ptr);
    node_type_ = { NODE_TYPE::ifNode };
}

BOOLEAN IfNode::setConditionNode(CONDITION_NODE_PTR condition_node_ptr) {
    try {
        condition_node_ptr_ = condition_node_ptr;
    } catch (int e) {
        (void)e;
        return false;
    }
    return true;
}

BOOLEAN IfNode::setThenStatementListNode(STMT_LIST_NODE_PTR then_stmt_list_node_ptr) {
    try {
        then_stmt_list_node_ptr_ = then_stmt_list_node_ptr;
    } catch (int e) {
        (void)e;
        return false;
    }
    return true;
}

BOOLEAN IfNode::setElseStatementListNode(STMT_LIST_NODE_PTR else_stmt_list_node_ptr) {
    try {
        else_stmt_list_node_ptr_ = else_stmt_list_node_ptr;
    } catch (int e) {
        (void)e;
        return false;
    }
    return true;
}

CONDITION_NODE_PTR IfNode::getConditionNode() {
    return condition_node_ptr_;
}

STMT_LIST_NODE_PTR IfNode::getThenStatementListNode() {
    return then_stmt_list_node_ptr_;
}

STMT_LIST_NODE_PTR IfNode::getElseStatementListNode() {
    return else_stmt_list_node_ptr_;
}
