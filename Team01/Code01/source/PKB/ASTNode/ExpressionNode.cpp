#include "ExpressionNode.h"

ExpressionNode::ExpressionNode(EXPR_TYPE expr_type, AST_NODE_PTR left_node_ptr, AST_NODE_PTR right_node_ptr) {
    setExpressionType(expr_type);
    setLeftAstNode(left_node_ptr);
    setRightAstNode(right_node_ptr);
    node_type_ = { NODE_TYPE::expressionNode };
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
        if (left_node_ptr == nullptr) {
            return false;
        }
        addChildNode(left_node_ptr);
        left_node_ptr->setParentNode(std::make_shared<ExpressionNode>(*this));
        left_node_ptr_ = left_node_ptr;
    } catch (int e) {
        (void)e;
        return false;
    }
    return true;
}

BOOLEAN ExpressionNode::setRightAstNode(AST_NODE_PTR right_node_ptr) {
    try {
        if (right_node_ptr == nullptr) {
            return false;
        }
        addChildNode(right_node_ptr);
        right_node_ptr->setParentNode(std::make_shared<ExpressionNode>(*this));
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
