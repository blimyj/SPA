#pragma once

#include <queue>
#include <vector>

#include "PKB.h"
#include "PKBBuilder.h"

typedef std::string STRING;
typedef std::vector<STRING> STRING_LIST;
typedef std::shared_ptr<ASTNode> AST_NODE_PTR;
typedef std::vector<std::shared_ptr<ASTNode>> AST_NODE_PTR_LIST;

class ASTDebugger {
/* Overview: A root node from an AST made by the Parser is provided to the ASTDebugger,
which then prints out all nodes in the tree and their properties. */

public:
	int printTree(AST_NODE_PTR);
		/*
		Description: Prints the nodes in the AST out, given the root node.
		*/

private:
	AST_NODE_PTR_LIST children_nodes;
	std::queue <AST_NODE_PTR> node_queue;

	STRING_LIST getProperties(AST_NODE_PTR_LIST, NODE_TYPE, STRING_LIST);
		/*
		Description: Returns a STRING_LIST of the properties of the given node. Return empty list if no properties.
		*/
};