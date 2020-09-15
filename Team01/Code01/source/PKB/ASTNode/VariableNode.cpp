#include "VariableNode.h"

VariableNode::VariableNode() {
	node_type_ = { NODE_TYPE::variableNode };
	var_name_ = "";
}

BOOLEAN VariableNode::setVariableName(STRING var_name) {
	try {
		var_name_ = var_name;
	} catch (int e) {
		(void)e;
		return false;
	}
	return true;
}

STRING VariableNode::getVariableName() {
	return var_name_;
}

