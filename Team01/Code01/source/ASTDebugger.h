#pragma once

#include <queue>
#include <vector>

#include "PKB\ASTNode\ASTNode.h"

typedef std::vector<std::string> STRING_LIST;
typedef std::shared_ptr<ASTNode> AST_NODE_PTR;
typedef std::vector<std::shared_ptr<ASTNode>> AST_NODE_PTR_LIST;


class ASTDebugger {
/* Overview: A root node from an AST made by the Parser is provided to the ASTDebugger,
which then prints out all nodes in the tree and their properties. */

public:
	int printTree(AST_NODE_PTR);

private:
	AST_NODE_PTR_LIST children_nodes;
	std::queue <AST_NODE_PTR> node_queue;

	STRING_LIST getProperties(AST_NODE_PTR_LIST, NODE_TYPE);
};