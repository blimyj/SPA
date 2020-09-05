#include "QueryNode.h"

QUERY_NODE_POINTER QueryNode::createNode(NODE_TYPE node_type, QUERY_NODE_POINTERS children) {
	QueryNode new_node = QueryNode();
	new_node.node_type = node_type;
	new_node.children = children;
	return new_node;
}

NODE_TYPE QueryNode::getNodeType() {
	return node_type;
}

QUERY_NODE_POINTERS QueryNode::getChildren() {
	return children;
}
