#pragma once

#include "ASTNode.h"

class StatementListNode : public ASTNode {

public:
	StatementListNode(AST_NODE_PTR_LIST node_list);
		/*
			Description: Constructs an ProcedureNode consisting of a STRING procedure name and STATEMENT_LIST_NODE_PTR statement list.
		*/

	AST_NODE_PTR_LIST getAstNodeList();
		/*
			Description: Returns a AST_NODE_PTR_LIST of the statement list body.
		*/


private:
	AST_NODE_PTR_LIST node_list_;

};
