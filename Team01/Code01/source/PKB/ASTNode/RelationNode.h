#pragma once

#include "ASTNode.h"

class RelationNode : public ASTNode {

public:
	RelationNode(RELATION_TYPE relation_type, AST_NODE_PTR left_node_ptr, AST_NODE_PTR right_node_ptr);
		/*
		Description: Constructs an RelationNode consisting of a RELATION_TYPE, left and right AST_NODE_PTR.
		*/

	BOOLEAN setRelationType(RELATION_TYPE relation_type);
		/*
		Description: Returns the RELATION_TYPE enum of the relation.
		Can be RELATION_TYPE enum of EQ, NEQ, GT, GTE, LT, LTE
		*/

	BOOLEAN setLeftAstNode(AST_NODE_PTR left_node_ptr);
		/*
		Description: Returns True if able to set left_node_ as left_node_ptr, false otherwise.
		*/

	BOOLEAN setRightAstNode(AST_NODE_PTR right_node_ptr);
		/*
		Description: Returns True if able to set right_node_ as right_node_ptr, false otherwise.
		*/

	RELATION_TYPE getRelationType();
		/*
		Description: Returns the RELATION_TYPE of this relation.
		*/

	AST_NODE_PTR getLeftAstNode();
		/*
		Description: Returns the AST_NODE_PTR of the left hand side of the expression.
		*/

	AST_NODE_PTR getRightAstNode();
		/*
		Description: Returns the AST_NODE_PTR of the right hand side of the expression, throws exception if this is RELATION_TYPE NONE.
		*/

private:
	RELATION_TYPE relation_type_;
	AST_NODE_PTR left_node_ptr_;
	AST_NODE_PTR right_node_ptr_;

};
