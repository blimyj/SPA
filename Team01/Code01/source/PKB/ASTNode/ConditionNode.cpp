#include "ConditionNode.h"

ConditionNode::ConditionNode() {
    condition_type_ = { CONDITION_TYPE::undefined };
    node_type_ = { NODE_TYPE::conditionNode };
    left_node_ptr_ = nullptr;
    right_node_ptr_ = nullptr;
}

BOOLEAN_TYPE ConditionNode::setConditionType(CONDITION_TYPE condition_type) {
    try {
        condition_type_ = condition_type;
    }
    catch (int e) {
        (void)e;
        return false;
    }
    return true;
}

BOOLEAN_TYPE ConditionNode::setLeftAstNode(AST_NODE_PTR left_relation_node_ptr) {
    try {
        if (left_relation_node_ptr == nullptr) {
            return false;
        }
        addChildNode(left_relation_node_ptr);
        left_relation_node_ptr->setParentNode(shared_from_this());
        left_node_ptr_ = left_relation_node_ptr;
    }
    catch (int e) {
        (void)e;
        return false;
    }
    return true;
}

BOOLEAN_TYPE ConditionNode::setRightAstNode(AST_NODE_PTR right_relation_node_ptr) {
    try {
        if (right_relation_node_ptr == nullptr) {
            return false;
        }
        addChildNode(right_relation_node_ptr);
        right_relation_node_ptr->setParentNode(shared_from_this());
        right_node_ptr_ = right_relation_node_ptr;
    }
    catch (int e) {
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
    if (right_node_ptr_ == NULL) {
        throw "Relation is of 'none' Type, there is no right relation node!";
    }
    return right_node_ptr_;
}

