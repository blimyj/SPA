#include "ExpressionNode.h"

ExpressionNode::ExpressionNode(EXPR_TYPE expr_type, AST_NODE_PTR left_node_ptr, AST_NODE_PTR right_node_ptr) {
    setExpressionType(expr_type);
    setLeftAstNode(left_node_ptr);
    setRightAstNode(right_node_ptr);
    node_type_ = { NODE_TYPE_ENUM::Expression };
}

BOOLEAN ExpressionNode::setExpressionType(EXPR_TYPE expr_type) {
    try {
        expr_type_ = expr_type;
    } catch (int e) {
        (void)e;
        return false;
    }
    return true;
}

BOOLEAN ExpressionNode::setLeftAstNode(AST_NODE_PTR left_node_ptr) {
    try {
        left_node_ptr_ = left_node_ptr;
    } catch (int e) {
        (void)e;
        return false;
    }
    return true;
}

BOOLEAN ExpressionNode::setRightAstNode(AST_NODE_PTR right_node_ptr) {
    try {
        right_node_ptr_ = right_node_ptr;
    } catch (int e) {
        (void)e;
        return false;
    }
    return true;
}

EXPR_TYPE ExpressionNode::getExpressionType() {
    return expr_type_;
}

AST_NODE_PTR ExpressionNode::getLeftAstNode() {
    return left_node_ptr_;
}

AST_NODE_PTR ExpressionNode::getRightAstNode() {
    return right_node_ptr_;
}
