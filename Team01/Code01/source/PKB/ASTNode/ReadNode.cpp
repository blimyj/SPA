#include "ReadNode.h"

ReadNode::ReadNode(VAR_NODE_PTR var_node_ptr) {
	setVariableNode(var_node_ptr);
}

BOOLEAN ReadNode::setVariableNode(VAR_NODE_PTR var_node_ptr) {
	try {
		var_node_ptr_ = var_node_ptr;
	} catch (int e) {
		return false;
	}
	return true;
}

STRING ReadNode::getVariableNode() {
	return var_node_ptr_;
}

