#pragma once

#include <memory>
#include <string>
#include "StatementListNode.h"
#include "ASTNode.h"

typedef std::shared_ptr<StatementListNode> STMT_LIST_NODE_PTR;
typedef std::string STRING;
typedef bool BOOLEAN;

class ProcedureNode : public ASTNode, std::enable_shared_from_this<ProcedureNode> {

public:
	ProcedureNode();
		/*
		Description: Sets NODE_TYPE of node to be procedureNode.
		*/

	BOOLEAN setProcedureName(STRING proc_name);
		/*
		Description: Returns True if able to set STRING of the procedure's name, false otherwise.
		*/

	BOOLEAN setProcedureStatementListNode(STMT_LIST_NODE_PTR stmt_list_node_ptr);
		/*
		Returns True if able to set the child STMT_LIST_NODE_PTR of the procedure, false otherwise.
		*/

	STRING getProcedureName();
		/*
		Description: Returns the STRING of the procedure's name
		*/

	STMT_LIST_NODE_PTR getProcedureStatementListNode();
		/*
		Description: Returns the child STMT_LIST_NODE_POINTER of the procedure.
		*/

private:
	STRING proc_name_;
	STMT_LIST_NODE_PTR stmt_list_node_ptr_;

};
