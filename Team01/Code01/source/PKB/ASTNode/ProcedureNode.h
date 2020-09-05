#pragma once

#include "ASTNode.h"

class ProcedureNode : public ASTNode {

public:
	ProcedureNode(STRING proc_name, STMT_LIST_NODE_PTR stmt_list);
		/*
			Description: Constructs an ProcedureNode consisting of a STRING procedure name and STATEMENT_LIST_NODE_PTR statement list.
		*/

	STRING getProcedureName();
		/*
			Description: Returns a STRING of the procedure's name 
		*/

	STMT_LIST_NODE_PTR getProcedureStatementList();
		/*
			Description: Returns a STATEMENT_LIST_NODE_PTR of the procedure's statement list.
		*/
	

private:
	STRING proc_name_;
	STMT_LIST_NODE_PTR stmt_list_node_;

};
