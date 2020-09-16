#pragma once

#include "QueryNodeType.h"
#include "QuerySynonymType.h"
#include "QueryNodeContent.h"

#include <string>

class QueryNode;

typedef QueryNodeType NODE_TYPE;
typedef QueryNode* QUERY_NODE_POINTERS;
typedef QuerySynonymType SYNONYM_TYPE;
typedef QueryNodeContent QUERY_NODE_CONTENT;

class QueryNode {
private:
	NODE_TYPE node_type;
	QUERY_NODE_POINTERS children = NULL; //array of pointers to children nodes
	SYNONYM_TYPE synonym_type;
	QUERY_NODE_CONTENT node_content = QueryNodeContent();

public:
	void setNodeType(NODE_TYPE node_type);
	NODE_TYPE getNodeType();

	void setSynonymNode(SYNONYM_TYPE synonym_type, STRING synonym_name); //synonym nodes MUST have snyonym name
	SYNONYM_TYPE getSynonymType();
	STRING getString();

	void setIntegerNode(INTEGER integer);
	INTEGER getInteger();

	void setASTNode(NODE_TYPE node_type, AST_NODE astnode);
	AST_NODE getAstNode();

	void setChildren(QUERY_NODE_POINTERS children); //need to add all children at once, in the right order
	QUERY_NODE_POINTERS getChildren();

	QUERY_NODE_CONTENT getQueryNodeContent(); //generic case to get all the node content

};