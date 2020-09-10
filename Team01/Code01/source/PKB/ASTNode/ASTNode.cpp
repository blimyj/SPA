#include "ASTNode.h"

BOOLEAN ASTNode::setParentNode(AST_NODE_PTR parent_node_ptr) {
	try {
		parent_node_ptr_ = parent_node_ptr;
	} catch (int e) {
		return false;
	}
	return true;
}

BOOLEAN ASTNode::addChildNode(AST_NODE_PTR child_node_ptr) {
	try {
		children_node_ptr_.push_back(child_node_ptr);
	} catch (int e) {
		return false;
	}
	return true;
}

AST_NODE_PTR ASTNode::getParentNode() {
	return parent_node_ptr_;
}

AST_NODE_PTR_LIST ASTNode::getChildrenNode() {
	return children_node_ptr_;
}

