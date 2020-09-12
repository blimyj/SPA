#pragma once

#include <memory>
#include "StatementNode.h"
#include "VariableNode.h"

typedef std::shared_ptr<VariableNode> VAR_NODE_PTR;
typedef bool BOOLEAN;

class ReadNode : public StatementNode {

public:
	ReadNode(VAR_NODE_PTR var_node_ptr);
		/*
		Description: Constructs a ReadNode with the child VAR_NODE_PTR of the read statement.
		*/

	BOOLEAN setVariableNode(VAR_NODE_PTR var_node_ptr);
		/*
		Description: Returns True if able to set the child VAR_NODE_PTR of the read statement, false otherwise.
		*/

	VAR_NODE_PTR getVariableNode();
		/*
		Description: Returns the child VAR_NODE_PTR of the read statement.
		*/

private:
	VAR_NODE_PTR var_node_ptr_;

};
