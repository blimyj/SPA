#pragma once

class QueryTree {
	/* Overview: A data structure that represents clauses in the form of a Tree */

public:
	QUERY_NODE_POINTER createNode(NODE_TYPE node_type, QUERY_NODE_POINTERS children);
	/*
	Description:
	  Normal: Constructs a CLAUSE_NODE & returns a pointer to it.
	  Abnormal: If 'node_type' is not 'synonym' and 'children' is empty,
				or if 'node_type' is not 'such that'/'select' and does not have exactly two 'children', throw an exception.
	*/

	NODE_TYPE getNodeType();
	/*
	Requires: The node should have a valid CLAUSE_TYPE.
	Description:
	  Normal: Returns the CLAUSE_TYPE of the node.
	  Abnormal: If no such CLAUSE_TYPE exists, throws an exception.
	*/

	QUERY_NODE_POINTERS getChildren();
	/*
	Description:
	  Normal: Returns the CLAUSE_NODE_POINTERS that points to the children of the node.
	  Abnormal: If CLAUSE_NODE_POINTERS is empty, throw an exception.
	*/
};