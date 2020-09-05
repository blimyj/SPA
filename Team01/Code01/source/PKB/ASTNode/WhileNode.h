#pragma once

#include "ASTNode.h"

class WhileNode : public ASTNode {
public:
	While(EXPR_NODE_PTR condition, STMT_LIST_NODE_PTR stmt_list);
		/*
			Description: Constructs an WhileNode with the given EXPRESSION_NODE_PTR condition and STATEMENT_LIST_PTR statement body.
		*/

	EXPR_NODE_PTR getCondition();
		/*
			Description: Returns the EXPRESSION_NODE_PTR of WhileNode condition.
		*/

	STATEMENT_LIST_NODE_PTR getIfStatementList();
		/*
			Description: Returns a STATEMENT_LIST_NODE_PTR of the while statement body.
		*/

private:
	EXPR_NODE_PTR expr_node_;
	STMT_LIST_NODE_PTR stmt_list_node;

};
