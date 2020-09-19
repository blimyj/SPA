#include "ExpressionNode.h"

ExpressionNode::ExpressionNode() {
    expr_type_ = { EXPR_TYPE::undefined };
    node_type_ = { NODE_TYPE::expressionNode };
    left_node_ptr_ = nullptr;
    right_node_ptr_ = nullptr;
}

BOOLEAN_TYPE ExpressionNode::setExpressionType(EXPR_TYPE expr_type) {
    try {
        expr_type_ = expr_type;
    } catch (int e) {
        (void)e;
        return false;
    }
    return true;
}

BOOLEAN_TYPE ExpressionNode::setLeftAstNode(AST_NODE_PTR left_node_ptr) {
    try {
        if (left_node_ptr == nullptr) {
            return false;
        }
        addChildNode(left_node_ptr);
        left_node_ptr->setParentNode(shared_from_this());
        left_node_ptr_ = left_node_ptr;
    } catch (int e) {
        (void)e;
        return false;
    }
    return true;
}

BOOLEAN_TYPE ExpressionNode::setRightAstNode(AST_NODE_PTR right_node_ptr) {
    try {
        if (right_node_ptr == nullptr) {
            return false;
        }
        addChildNode(right_node_ptr);
        right_node_ptr->setParentNode(shared_from_this());
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
    if (right_node_ptr_ == NULL) {
        throw "ASTNode is of 'none' Type, there is right AST Node!";
    }
    return right_node_ptr_;
}
