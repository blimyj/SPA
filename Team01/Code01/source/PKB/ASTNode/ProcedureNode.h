#pragma once

#include "ASTNode.h"

class ProcedureNode : public ASTNode {

public:
	ProcedureNode(STRING proc_name, STMT_LIST_NODE_PTR stmt_list_node_ptr);
		/*
		Description: Constructs an ProcedureNode consisting of a STRING procedure name and STATEMENT_LIST_NODE_PTR statement list.
		*/

	BOOLEAN setProcedureName(STRING proc_name);
		/*
		Description: Returns TRUE if able to set proc_name_ as proc_name, false otherwise.
		*/

	BOOLEAN setProcedureStatementListNode(STMT_LIST_NODE_PTR stmt_list_node_ptr);
		/*
		Description: Returns True if able to set stmt_list_node_ as stmt_list, false otherwise.
		*/

	STRING getProcedureName();
		/*
		Description: Returns a STRING of the procedure's name 
		*/

	STMT_LIST_NODE_PTR getProcedureStatementListNode();
		/*
		Description: Returns a STATEMENT_LIST_NODE_PTR of the procedure's statement list.
		*/

private:
	STRING proc_name_;
	STMT_LIST_NODE_PTR stmt_list_node_ptr_;

};
