#include "QueryNode.h"

void QueryNode::setNodeType(NODE_TYPE node_type) {
	this->node_type = node_type;
}

void QueryNode::setSynonymNode(NODE_TYPE node_type, SYNONYM_NAME synonym) {
	this->node_type = node_type;
	this->synonym = synonym;
}

NODE_TYPE QueryNode::getNodeType() {
	return node_type;
}

void QueryNode::setChildren(QUERY_NODE_POINTERS children) {
	this->children = children;
}

QUERY_NODE_POINTERS QueryNode::getChildren() {
	return children;
}

SYNONYM_NAME QueryNode::getSynonym() {
	return synonym;
}
