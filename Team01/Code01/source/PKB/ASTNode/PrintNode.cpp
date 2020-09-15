#include "PrintNode.h"

PrintNode::PrintNode(VAR_NODE_PTR var_node_ptr) {
	setVariableNode(var_node_ptr);
	node_type_ = { NODE_TYPE::printNode };
}

BOOLEAN PrintNode::setVariableNode(VAR_NODE_PTR var_node_ptr) {
	try {
		addChildNode(var_node_ptr);
		var_node_ptr->setParentNode(std::make_shared<PrintNode>(*this));
		var_node_ptr_ = var_node_ptr;
	} catch (int e) {
		(void)e;
		return false;
	}
	return true;
}

VAR_NODE_PTR PrintNode::getVariableNode() {
	return var_node_ptr_;
}

