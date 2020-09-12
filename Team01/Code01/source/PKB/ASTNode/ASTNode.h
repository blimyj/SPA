#pragma once

#include <memory>
#include <vector>
#include "NodeTypeEnum.h"

class ASTNode;

typedef std::shared_ptr<ASTNode> AST_NODE_PTR;
typedef std::vector<std::shared_ptr<ASTNode>> AST_NODE_PTR_LIST;
typedef bool BOOLEAN;
typedef NodeTypeEnum NODE_TYPE;

class ASTNode {

public:

	BOOLEAN setParentNode(AST_NODE_PTR parent_node_ptr);
		/*
		Description: Returns True if able to set AST_NODE_PTR as a parent of this node, false otherwise
		*/

	BOOLEAN addChildNode(AST_NODE_PTR child_node_ptr);
		/*
		Description: Returns True if able to set AST_NODE_PTR as a child of this node, false otherwise
		*/

	AST_NODE_PTR getParentNode();
		/*
		Description: Returns the parent AST_NODE_PTR of this ASTNode
		*/

	AST_NODE_PTR_LIST getChildrenNode();
		/*
		Description: Returns the children AST_NODE_PTR_LIST of this ASTNode
		*/

	NODE_TYPE getNodeType();
		/*
		Description: Returns the Sub Class's NODE_TYPE of this ASTNode.
		*/

private:
	AST_NODE_PTR parent_node_ptr_;
	AST_NODE_PTR_LIST children_node_ptr_;

protected:
	NODE_TYPE node_type_;
};
