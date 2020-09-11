#include "ReadNode.h"

ReadNode::ReadNode(VAR_NODE_PTR var_node_ptr) {
	setVariableNode(var_node_ptr);
	node_type_ = { NODE_TYPE_ENUM::Read };
}

BOOLEAN ReadNode::setVariableNode(VAR_NODE_PTR var_node_ptr) {
	try {
		var_node_ptr_ = var_node_ptr;
	} catch (int e) {
		(void)e;
		return false;
	}
	return true;
}

VAR_NODE_PTR ReadNode::getVariableNode() {
	return var_node_ptr_;
}

