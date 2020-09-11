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
class ProgramNode: public ASTNode {


public:
	ProgramNode();
	/*
	Description: Constructs a ProgramNode.
	*/

	BOOLEAN addProcedureNode(PROC_NODE_PTR proc_node_ptr);
	/*
	Description: Returns TRUE if able to add a PROC_NODE_PTR to PROC_NODE_PTR_LIST.
	*/

	PROC_NODE_PTR_LIST getProcedureNodeList();
	/*
	Description: Returns a PROC_NODE_PTR_LIST stored.
	*/

private:
	PROC_NODE_PTR_LIST proc_node_ptr_list_;

};
