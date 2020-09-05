#pragma once

#include "ASTNode.h"

class IfNode : public ASTNode {
public:
	IfNode(EXPR_NODE_PTR condition, STMT_LIST_NODE_PTR then_stmt_list, STMT_LIST_NODE_PTR else_stmt_list);
		/*
			Description: Constructs an IfNode with the given EXPRESSION_NODE_PTR, STATEMENT_LIST_PTR for both then and else.
		*/

	EXPR_NODE_PTR getCondition();
		/*
			Description: Returns the EXPRESSION_NODE_PTR of IfNode condition.
		*/

	STATEMENT_LIST_NODE_PTR getThenStatementList();
		/*
			Description: Returns a STATEMENT_LIST_NODE_PTR of the then statement body.
		*/

	STATEMENT_LIST_NODE_PTR getElseStatementList();
		/*
			Description: Returns a STATEMENT_LIST_NODE_PTR of the else statement body.
		*/

private:
	EXPR_NODE_PTR expr_node_;
	STMT_LIST_NODE_PTR then_stmt_list_node_;
	STMT_LIST_NODE_PTR else_stmt_list_node_;

};
