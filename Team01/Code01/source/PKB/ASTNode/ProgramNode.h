#pragma once

#include <memory>
#include <string>
#include <vector>
#include "ProcedureNode.h"
#include "ASTNode.h"

typedef bool BOOLEAN;
typedef std::shared_ptr<ProcedureNode> PROC_NODE_PTR;
typedef std::vector<PROC_NODE_PTR> PROC_NODE_PTR_LIST;

/*This class is the root node of the AST, also known as the program node*/
class ProgramNode: public ASTNode, public std::enable_shared_from_this<ProgramNode> {


public:
	ProgramNode();
		/*
		Description: Constructs an empty ProgramNode.
		*/

	BOOLEAN addProcedureNode(PROC_NODE_PTR proc_node_ptr);
		/*
		Description: Returns True if able to add the PROC_NODE_PTR to the PROC_NODE_PTR_LIST, false otherwise.
		*/

	PROC_NODE_PTR_LIST getProcedureNodeList();
		/*
		Description: Returns the PROC_NODE_PTR_LIST containing the list of PROC_NODE_PTR of the program.
		*/

private:
	PROC_NODE_PTR_LIST proc_node_ptr_list_;

};
