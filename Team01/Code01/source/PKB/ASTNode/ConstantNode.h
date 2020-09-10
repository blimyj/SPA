#pragma once
#include <string>


#include "ASTNode.h"

typedef std::string VALUE;
typedef bool BOOLEAN;

class ConstantNode : public ASTNode {

public:
	ConstantNode(VALUE value);
		/*
		Description: Constructs a ConstantNode with the VALUE of the Constant.
		*/

	BOOLEAN setValue(VALUE value);
		/*
		Description: Returns True if able to set the VALUE of the Constant in this ConstantNode
		*/

	VALUE getValue();
		/*
		Description: Returns the VALUE of the Constant in this ConstantNode
		*/


private:
	VALUE value_;
};
