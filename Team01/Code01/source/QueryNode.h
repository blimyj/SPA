#pragma once

#include <string>

class QueryNode;

typedef std::string NODE_TYPE;
typedef QueryNode* QUERY_NODE_POINTER;
typedef QueryNode** QUERY_NODE_POINTERS;

class QueryNode {
private:
	NODE_TYPE node_type;
	QUERY_NODE_POINTERS children; //array of pointers to children nodes

public: 
	QueryNode();
	void setNodeType(NODE_TYPE node_type);
	NODE_TYPE getNodeType();
	void setChildren(QUERY_NODE_POINTERS children); //need to add all children at once, in the right order
	QUERY_NODE_POINTERS getChildren();

};