#pragma once

class ASTNode {

public:
	virtual BOOLEAN setParentNode(AST_NODE_PTR parent_node_ptr);
		/*
		Description: Sets the given AST_NODE_PTR node to be the parent of this node.
		*/

	virtual BOOLEAN addChildNode(AST_NODE_PTR child_node_ptr);
		/*
		Description: Sets the given AST_NODE_PTR node to be a child of this node.
					 The child added will be sorted from left to right based on the AST.
		*/

	virtual AST_NODE_PTR getParentNode();
		/*
		Description: Returns the AST_NODE_PTR that points to the parent AST_NODE of this node otherwise returns NULL.
		*/

	virtual AST_NODE_PTR_LIST getChildrenNode();
		/*
		Description: Returns a list of AST_NODE_PTR_LIST that point to AST_NODE that are children of this node, if there are no children, returns an empty list.
		*/

private:
	AST_NODE_PTR parent_node_ptr_;
	AST_NODE_PTR_LIST children_node_ptr_;
	STATEMENT_NUMBER statement_number_;
};
