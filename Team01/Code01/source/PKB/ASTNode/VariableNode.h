#pragma once

#include <string>
#include "StatementNode.h"

typedef std::string STRING;
typedef bool BOOLEAN;

class VariableNode : public ASTNode {

public:
	VariableNode();
		/*
		Description: Sets NODE_TYPE of node to be variableNode.
		*/

	BOOLEAN setVariableName(STRING var_name);
		/*
		Description: Returns True if able to set var_name_ as var_name, false otherwise.
		*/

	STRING getVariableName();
		/*
		Description: Returns a STRING of the variable's name
		*/

private:
	STRING var_name_;

};
