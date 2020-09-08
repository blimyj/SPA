#include "VariableNode.h"

VariableNode::VariableNode(STRING var_name) {
	setVariableName(var_name);
}

BOOLEAN VariableNode::setVariableName(STRING var_name) {
	try {
		var_name_ = var_name;
	} catch (int e) {
		return false;
	}
	return true;
}

STRING VariableNode::getVariableName() {
	return var_name_;
}

