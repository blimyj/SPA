typedef std::shared_ptr<VariableNode> VAR_NODE_PTR;
typedef std::string STRING;
typedef bool BOOLEAN;

#include <iostream>
#include "PrintNode.h"
#include "VariableNode.h"

PrintNode::PrintNode(VAR_NODE_PTR var_node_ptr) {
	setVariableNode(var_node_ptr);
}

BOOLEAN PrintNode::setVariableNode(VAR_NODE_PTR var_node_ptr) {
	try {
		var_node_ptr_ = var_node_ptr;
	} catch (int e) {
		return false;
	}
	return true;
}

STRING PrintNode::getVariableNode() {
	return var_node_ptr_;
}

