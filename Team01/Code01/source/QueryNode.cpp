#include "QueryNode.h"
#include "QueryNodeType.h"


void QueryNode::setNodeType(NODE_TYPE node_type) {
	this->node_type = node_type;
}

NODE_TYPE QueryNode::getNodeType() {
	return node_type;
}


void QueryNode::setIntegerNode(INTEGER integer) {
	this->node_type = { QueryNodeType::integer };
	QueryNodeContent content = QueryNodeContent(integer);
	this->node_content = content;
}

INTEGER QueryNode::getInteger() {
	return node_content.getInt();
}


void QueryNode::setASTNode(NODE_TYPE node_type, AST_NODE astnode) {
	//NODE_TYPE can be expression or wild_card
	this->node_type = node_type;
	QueryNodeContent content = QueryNodeContent(astnode);
	this->node_content = content;
}

ASTNode QueryNode::getAstNode() {
	return node_content.getAstNode();
}

void QueryNode::setSynonymNode(SYNONYM_TYPE synonym_type, STRING synonym_name) {
	this->node_type = {QueryNodeType::synonym};
	this->synonym_type = synonym_type;
	QueryNodeContent content = QueryNodeContent(synonym_name);
	this->node_content = content;
}

SYNONYM_TYPE QueryNode::getSynonymType() {
	return synonym_type;
}

STRING QueryNode::getString() {
	return node_content.getString();
}


void QueryNode::setChildren(QUERY_NODE_POINTERS children) {
	this->children = children;
}

QUERY_NODE_POINTERS QueryNode::getChildren() {
	return children;
}



QUERY_NODE_CONTENT QueryNode::getQueryNodeContent() {
	return node_content;
}
