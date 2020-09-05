#pragma once

#include "ASTNode.h"

class ConstantNode : public ASTNode {

public:
	ConstantNode(VALUE value);
		/*
			Description: Constructs an ConstantNode consisting of a VALUE of the constant's value.
		*/

	VALUE getValue();
		/*
			Description: Returns a VALUE of the constant's value.
		*/

private:
	VALUE value_;
};
