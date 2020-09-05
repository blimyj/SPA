#pragma once

#include "StatementNode.h"

class WhileNode : public StatementNode {
public:
	While(CONDITION_NODE_PTR condition, STMT_LIST_NODE_PTR stmt_list_node);
		/*
		Description: Constructs an WhileNode with the given CONDITION_NODE_PTR condition and STMT_LIST_NODE_PTR statement body.
		*/

	BOOLEAN setExpressionNode(CONDITION_NODE_PTR condition_node_ptr);
		/*
		Description: Returns True if able to set the condition_node_ptr_ as condition_node_ptr  of IfNode condition.
		*/

	BOOLEAN setWhileStatementListNode(STMT_LIST_NODE_PTR stmt_list_node_ptr);
		/*
		Description: Returns True if able to set stmt_list_node_ptr_ as stmt_list_node_ptr, false otherwise.
		*/

	EXPR_NODE_PTR getConditionNode();
		/*
		Description: Returns the CONDITION_NODE_PTR of WhileNode condition.
		*/

	STATEMENT_LIST_NODE_PTR getWhileStatementListNode();
		/*
		Description: Returns a STATEMENT_LIST_NODE_PTR of the while statement body. 
		*/


private:
	CONDITION_NODE_PTR condition_node_ptr_;
	STMT_LIST_NODE_PTR stmt_list_node_ptr_;

};