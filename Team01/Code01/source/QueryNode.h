#pragma once

#include <string>

typedef string NODE_TYPE;
typedef QueryNode* QUERY_NODE_POINTER;
typedef QueryNode** QUERY_NODE_POINTERS;

class QueryNode {
private:
	NODE_TYPE node_type;
	QUERY_NODE_POINTERS children; //array of pointers to children nodes

	QueryNode();
public: 
	QUERY_NODE_POINTER createNode(NODE_TYPE node_type, QUERY_NODE_POINTERS children);
	NODE_TYPE getNodeType();
	QUERY_NODE_POINTERS getChildren();

};