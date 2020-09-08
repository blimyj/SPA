typedef std::shared_ptr<ExpressionNode> EXPR_NODE_PTR;
typedef std::shared_ptr<VariableNode> VAR_NODE_PTR;
typedef bool BOOLEAN;

#include <iostream>
#include "AssignNode.h"
#include "ExpressionNode.h"
#include "VariableNode.h"

AssignNode::AssignNode(VAR_NODE_PTR var_node_ptr, EXPR_NODE_PTR expr_node_ptr) {
	setVariableNode(var_node_ptr);
	setExpressionNode(expr_node_ptr);
}

BOOLEAN AssignNode::setVariableNode(VAR_NODE_PTR var_node_ptr) {
	try {
		var_node_ptr_ = var_node_ptr;
	} catch (int e) {
		return false;
	}
	return true;
}

BOOLEAN AssignNode::setExpressionNode(EXPR_NODE_PTR expr_node_ptr) {
    try {
		expr_node_ptr_ = expr_node_ptr;
	} catch (int e) {
		return false;
	}
	return true;
}

VAR_NODE_PTR AssignNode::getVariableNode() {
	return var_node_ptr_;
}


EXPR_NODE_PTR AssignNode::getExpressionNode() {
	return expr_node_ptr_;
}


