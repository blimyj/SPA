#pragma once

#include "QueryNodeType.h"
#include "QuerySynonymType.h"

#include <string>

class QueryNode;

typedef QueryNodeType NODE_TYPE;
typedef std::string NODE_TYPE_STRING;
typedef QueryNode* QUERY_NODE_POINTERS;
typedef QuerySynonymType SYNONYM_TYPE;
typedef std::string SYNONYM_TYPE_STRING;
typedef std::string SYNONYM_NAME;

class QueryNode {
private:
	NODE_TYPE node_type;
	QUERY_NODE_POINTERS children = NULL; //array of pointers to children nodes
	SYNONYM_TYPE synonym_type;
	SYNONYM_NAME synonym_name;

public: 
	void setNodeType(NODE_TYPE node_type);
	void setNodeType(NODE_TYPE_STRING node_type_string);
	void setSynonymNode(SYNONYM_TYPE synonym_type, SYNONYM_NAME synonym_name); //synonym nodes MUST have snyonym name
	void setSynonymNode(SYNONYM_TYPE_STRING synonym_type_string, SYNONYM_NAME synonym_name); //synonym nodes MUST have snyonym name
	NODE_TYPE getNodeType();
	void setChildren(QUERY_NODE_POINTERS children); //need to add all children at once, in the right order
	QUERY_NODE_POINTERS getChildren();
	SYNONYM_TYPE getSynonymType();
	/*
		Requires: Node type must be "synonym"
		Returns: The type of the synonym (eg stmt, assign)
	*/
	SYNONYM_NAME getSynonymName();
	/*
		Requires: Node type must be "synonym"
		Returns: The name of the synonym (eg a1, w)
	*/
};