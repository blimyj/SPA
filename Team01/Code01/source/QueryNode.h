#pragma once

#include "QueryNodeType.h"
#include "QuerySynonymType.h"
#include "QueryNodeContent.h"

#include <string>

class QueryNode;

typedef QueryNodeType QUERY_NODE_TYPE;
typedef std::string NODE_TYPE_STRING;
typedef QueryNode* QUERY_NODE_POINTERS;
typedef QuerySynonymType SYNONYM_TYPE;
typedef std::string SYNONYM_TYPE_STRING;
typedef std::string SYNONYM_NAME;
typedef QueryNodeContent QUERY_NODE_CONTENT;

class QueryNode {
private:
	QUERY_NODE_TYPE node_type;
	QUERY_NODE_POINTERS children = NULL; //array of pointers to children nodes
	SYNONYM_TYPE synonym_type;
	QUERY_NODE_CONTENT node_content = QueryNodeContent();

public:
	QueryNode();
	void setNodeType(QUERY_NODE_TYPE node_type);
	void setNodeType(NODE_TYPE_STRING node_type_string);
	QUERY_NODE_TYPE getNodeType();

	void setSynonymNode(SYNONYM_TYPE synonym_type, STRING synonym_name); //synonym nodes MUST have snyonym name
	void setSynonymNode(SYNONYM_TYPE_STRING synonym_type_string, SYNONYM_NAME synonym_name); //synonym nodes MUST have snyonym name
	SYNONYM_TYPE getSynonymType();
	void setIdentityNode(STRING identity);
	STRING getString();

	void setIntegerNode(INTEGER integer);
	INTEGER getInteger();

	void setASTNode(QUERY_NODE_TYPE node_type, AST_NODE astnode);
	AST_NODE getAstNode();

	void setChildren(QUERY_NODE_POINTERS children); //need to add all children at once, in the right order
	QUERY_NODE_POINTERS getChildren();

	QUERY_NODE_CONTENT getQueryNodeContent(); //generic case to get all the node content

};