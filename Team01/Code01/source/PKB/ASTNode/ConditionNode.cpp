typedef std::shared_ptr<VariableNode> VAR_NODE_PTR;
typedef std::shared_ptr<ASTNode> AST_NODE_PTR;
typedef std::string CONDITION_TYPE;
typedef bool BOOLEAN;

#include <iostream>
#include "ConditionNode.h"
#include "VariableNode.h"

ConditionNode::ConditionNode(CONDITION_TYPE condition_type, AST_NODE_PTR left_node_ptr, AST_NODE_PTR right_node_ptr) {
    setRelationType(condition_type);
    setLeftAstNode(left_node_ptr);
    setRightAstNode(right_node_ptr);
}

BOOLEAN ConditionNode::setRelationType(CONDITION_TYPE condition_type) {
    try {
        condition_type_ = condition_type;
    } catch (int e) {
        return false;
    }
    return true;
}

BOOLEAN ConditionNode::setLeftAstNode(AST_NODE_PTR left_node_ptr) {
    try {
        left_node_ptr_ = left_node_ptr;
    } catch (int e) {
        return false;
    }
    return true;
}

BOOLEAN ConditionNode::setRightAstNode(AST_NODE_PTR right_node_ptr) {
    try {
        right_node_ptr_ = right_node_ptr;
    } catch (int e) {
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

