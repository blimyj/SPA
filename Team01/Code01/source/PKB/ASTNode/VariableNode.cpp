#include "VariableNode.h"

VariableNode::VariableNode(STRING var_name) {
	setVariableName(var_name);
	node_type_ = { NODE_TYPE::variableNode };
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

