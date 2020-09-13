#include "ConditionNode.h"

ConditionNode::ConditionNode(CONDITION_TYPE condition_type, AST_NODE_PTR left_node_ptr, AST_NODE_PTR right_node_ptr) {
    setConditionType(condition_type);
    setLeftAstNode(left_node_ptr);
    setRightAstNode(right_node_ptr);
    node_type_ = { NODE_TYPE::conditionNode };
}

BOOLEAN ConditionNode::setConditionType(CONDITION_TYPE condition_type) {
    try {
        condition_type_ = condition_type;
    } catch (int e) {
        (void)e;
        return false;
    }
    return true;
}

BOOLEAN ConditionNode::setLeftAstNode(AST_NODE_PTR left_node_ptr) {
    try {
        left_node_ptr_ = left_node_ptr;
    } catch (int e) {
        (void)e;
        return false;
    }
    return true;
}

BOOLEAN ConditionNode::setRightAstNode(AST_NODE_PTR right_node_ptr) {
    try {
        right_node_ptr_ = right_node_ptr;
    } catch (int e) {
        (void)e;
        return false;
    }
    return true;
}

CONDITION_TYPE ConditionNode::getConditionType() {
    return condition_type_;
}

AST_NODE_PTR ConditionNode::getLeftAstNode() {
    return left_node_ptr_;
}

AST_NODE_PTR ConditionNode::getRightAstNode() {
    return right_node_ptr_;
}

