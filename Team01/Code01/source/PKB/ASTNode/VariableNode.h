#pragma once

#include "ASTNode.h"

class VariableNode : public ASTNode {

public:
	VariableNode(STRING var_name);
		/*
			Description: Constructs an ProcedureNode consisting of a STRING variable name.
		*/

	STRING getVariableName();
		/*
			Description: Returns a STRING of the variable's name
		*/

private:
	STRING var_name_;

};
