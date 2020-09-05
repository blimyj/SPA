#include "QueryNode.h"

QueryNode::QueryNode(){}

void QueryNode::setNodeType(NODE_TYPE node_type) {
	this->node_type = node_type;
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
