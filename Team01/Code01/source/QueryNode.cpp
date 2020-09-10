#include "QueryNode.h"
#include "QueryNodeType.h"

void QueryNode::setNodeType(NODE_TYPE node_type) {
	this->node_type = node_type;
}

void QueryNode::setSynonymNode(SYNONYM_NAME synonym) {
	this->node_type = {QueryNodeType::synonym};
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
