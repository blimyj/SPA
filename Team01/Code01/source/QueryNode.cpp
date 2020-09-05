#include "QueryNode.h"

QueryNode::QueryNode(){}

/*
QUERY_NODE_POINTER QueryNode::createNode(NODE_TYPE node_type, QUERY_NODE_POINTERS children) {
	node_type = node_type;
	new_node.children = children;
	return new_node;
}
*/

NODE_TYPE QueryNode::getNodeType() {
	return node_type;
}

QUERY_NODE_POINTERS QueryNode::getChildren() {
	return children;
}
