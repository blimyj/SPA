#pragma once

#include <memory>
#include <string>
#include "PrintNode.h"
#include "StatementNode.h"
#include "VariableNode.h"

typedef std::shared_ptr<VariableNode> VAR_NODE_PTR;
typedef std::string STRING;
typedef bool BOOLEAN;

class PrintNode : public StatementNode, std::enable_shared_from_this<PrintNode> {

public:
	PrintNode();
		/*
		Description: Sets NODE_TYPE of node to be printNode.
		*/

	BOOLEAN setVariableNode(VAR_NODE_PTR var_node_ptr);
		/*
		Description: Returns True if able to set the child VAR_NODE_PTR of the print statement, false otherwise.
		*/

	VAR_NODE_PTR getVariableNode();
		/*
		Description: Returns the child VAR_NODE_PTR of the print statement.
		*/

private:
	VAR_NODE_PTR var_node_ptr_;

};
