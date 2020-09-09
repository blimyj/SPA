#pragma once

#include <string>

class QueryNode;

typedef std::string NODE_TYPE;
typedef QueryNode* QUERY_NODE_POINTERS;
typedef std::string SYNONYM;

class QueryNode {
private:
	NODE_TYPE node_type;
	QUERY_NODE_POINTERS children = NULL; //array of pointers to children nodes
	SYNONYM synonym;

public: 
	void setNodeType(NODE_TYPE node_type);
	void setSynonymNode(NODE_TYPE node_type, SYNONYM synonym); //synonym nodes MUST have snyonym name
	NODE_TYPE getNodeType();
	void setChildren(QUERY_NODE_POINTERS children); //need to add all children at once, in the right order
	QUERY_NODE_POINTERS getChildren();
	SYNONYM getSynonym();
};