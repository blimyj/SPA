#pragma once

#include "ASTNode.h"

class StatementListNode : public ASTNode {

public:
	StatementListNode(AST_NODE_PTR_LIST node_ptr_list);
		/*
		Description: Constructs an ProcedureNode consisting of a STRING procedure name and STATEMENT_LIST_NODE_PTR statement list.
		*/

	BOOLEAN addStatementNode(STMT_NODE_PTR stmt_node_ptr);
		/*
		Description: Returns True if able to append stmt_node_ptr to stmt_node_ptr_list_, false otherwise.
					 Serves as a function wrapper for addChild(STMT_NODE_PTR);
		*/

	STMT_NODE_PTR_LIST getStatementNodeList();
		/*
		Description: Returns a STMT_NODE_PTR_LIST of the statement list body.
					 Serves as a function wrapper for getChildren();
		*/

private:
	STMT_NODE_PTR_LIST stmt_node_ptr_list_;

};
