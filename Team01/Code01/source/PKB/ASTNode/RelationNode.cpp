#include "RelationNode.h"

RelationNode::RelationNode(RELATION_TYPE relation_type, AST_NODE_PTR left_node_ptr, AST_NODE_PTR right_node_ptr) {
    setRelationType(relation_type);
    setLeftAstNode(left_node_ptr);
    setRightAstNode(right_node_ptr);
}

BOOLEAN RelationNode::setRelationType(RELATION_TYPE relation_type) {
    try {
        relation_type_ = relation_type;
    } catch (int e) {
        (void)e;
        return false;
    }
    return true;
}

BOOLEAN RelationNode::setLeftAstNode(AST_NODE_PTR left_node_ptr) {
    try {
        left_node_ptr_ = left_node_ptr;
    } catch (int e) {
        (void)e;
        return false;
    }
    return true;
}

BOOLEAN RelationNode::setRightAstNode(AST_NODE_PTR right_node_ptr) {
    try {
        right_node_ptr_ = right_node_ptr;
    } catch (int e) {
        (void)e;
        return false;
    }
    return true;
}

RELATION_TYPE RelationNode::getRelationType() {
    return relation_type_;
}

AST_NODE_PTR RelationNode::getLeftAstNode() {
    return left_node_ptr_;
}

AST_NODE_PTR RelationNode::getRightAstNode() {
    return right_node_ptr_;
}
