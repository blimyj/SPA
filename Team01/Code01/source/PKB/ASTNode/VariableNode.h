#pragma once

#include "StatementNode.h"

class VariableNode : public StatementNode {

public:
	VariableNode(STRING var_name);
		/*
		Description: Constructs an ProcedureNode consisting of a STRING variable name.
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
