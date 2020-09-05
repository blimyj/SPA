#pragma once

class ASTNode {

public:
	virtual VOID setParent(AST_NODE_PTR parent);
		/*
			Description: Sets the given AST_NODE_PTR node to be the parent of this node.
		*/

	virtual VOID addChild(AST_NODE_PTR child);
		/*
			Description: Sets the given AST_NODE_PTR node to be a child of this node.
						 The child added will be sorted from left to right based on the AST.
		*/

	virtual AST_NODE_PTR getParent();
		/*
			Description: Returns the AST_NODE_PTR that points to the parent AST_NODE of this node otherwise returns NULL.
		*/

	virtual AST_NODE_PTR_LIST getChildren();
		/*
			Description: Returns a list of AST_NODE_PTR_LIST that point to AST_NODE that are children of this node, if there are no children, returns an empty list.
		*/

	virtual STATEMENT_NUMBER getStatementNumber();
		/*
			Description: Returns a STATEMENT_NUMBER based on the node's statement.
		*/

private:
	AST_NODE_PTR parent_node_;
	AST_NODE_PTR_LIST children_node_;
	STATEMENT_NUMBER statement_number_;

};
