#include "QueryNode.h"
#include "QueryNodeType.h"

void QueryNode::setNodeType(NODE_TYPE node_type) {
	this->node_type = node_type;
}

void QueryNode::setNodeType(NODE_TYPE node_type, NODE_TYPE_CONTENT node_content) {

}

void QueryNode::setSynonymNode(SYNONYM_TYPE synonym_type, SYNONYM_NAME synonym_name) {
	this->node_type = {QueryNodeType::synonym};
	this->synonym_type = synonym_type;
	this->synonym_name = synonym_name;
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

SYNONYM_TYPE QueryNode::getSynonymType() {
	return synonym_type;
}

SYNONYM_NAME QueryNode::getSynonymName() {
	return synonym_name;
}
