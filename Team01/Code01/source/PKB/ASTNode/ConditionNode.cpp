#include "ConditionNode.h"

ConditionNode::ConditionNode(CONDITION_TYPE condition_type, RELATION_NODE_PTR left_relation_node_ptr, RELATION_NODE_PTR right_relation_node_ptr) {
    setConditionType(condition_type);
    setLeftRelationNode(left_relation_node_ptr);
    setRightRelationNode(right_relation_node_ptr);
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

BOOLEAN ConditionNode::setLeftRelationNode(RELATION_NODE_PTR left_relation_node_ptr) {
    try {
        left_relation_node_ptr_ = left_relation_node_ptr;
    } catch (int e) {
        (void)e;
        return false;
    }
    return true;
}

BOOLEAN ConditionNode::setRightRelationNode(RELATION_NODE_PTR right_relation_node_ptr) {
    try {
        right_relation_node_ptr_ = right_relation_node_ptr;
    } catch (int e) {
        (void)e;
        return false;
    }
    return true;
}

CONDITION_TYPE ConditionNode::getConditionType() {
    return condition_type_;
}

RELATION_NODE_PTR ConditionNode::getLeftRelationNode() {
    return left_relation_node_ptr_;
}

RELATION_NODE_PTR ConditionNode::getRightRelationNode() {
    return right_relation_node_ptr_;
}

