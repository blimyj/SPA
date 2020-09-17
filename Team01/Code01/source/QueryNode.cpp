#include <regex>

#include "QueryNode.h"
#include "QueryNodeType.h"


void QueryNode::setNodeType(NODE_TYPE node_type) {
	this->node_type = node_type;
}

void QueryNode::setNodeType(NODE_TYPE_STRING node_type_string) {
	if (std::regex_match(node_type_string, std::regex("select"))) {
		this->node_type = QueryNodeType::select;
	}
	else if (std::regex_match(node_type_string, std::regex("synonym"))) {
		this->node_type = QueryNodeType::synonym;
	}
	else if (std::regex_match(node_type_string, std::regex("such that"))) {
		this->node_type = QueryNodeType::such_that;
	}
	else if (std::regex_match(node_type_string, std::regex("pattern"))) {
		this->node_type = QueryNodeType::pattern;
	}
	else if (std::regex_match(node_type_string, std::regex("Follows"))) {
		this->node_type = QueryNodeType::follows;
	}
	else if (std::regex_match(node_type_string, std::regex("FollowsT"))) {
		this->node_type = QueryNodeType::followsT;
	}
	else if (std::regex_match(node_type_string, std::regex("Parent"))) {
		this->node_type = QueryNodeType::parent;
	}
	else if (std::regex_match(node_type_string, std::regex("ParentT"))) {
		this->node_type = QueryNodeType::parentT;
	}
	else if (std::regex_match(node_type_string, std::regex("UsesS"))) {
		this->node_type = QueryNodeType::usesS;
	}
	else if (std::regex_match(node_type_string, std::regex("ModifiesS"))) {
		this->node_type = QueryNodeType::modifiesS;
	}
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

void QueryNode::setSynonymNode(SYNONYM_TYPE synonym_type, SYNONYM_NAME synonym_name) {
	this->node_type = { QueryNodeType::synonym };
	this->synonym_type = synonym_type;
	QueryNodeContent content = QueryNodeContent(synonym_name);
	this->node_content = content;
}

void QueryNode::setSynonymNode(SYNONYM_TYPE_STRING synonym_type_string, SYNONYM_NAME synonym_name) {
	this->node_type = {QueryNodeType::synonym};

	if (std::regex_match(synonym_type_string, std::regex("stmt"))) {
		this->synonym_type = QuerySynonymType::stmt;
	}
	else if (std::regex_match(synonym_type_string, std::regex("read"))) {
		this->synonym_type = QuerySynonymType::read;
	}
	else if (std::regex_match(synonym_type_string, std::regex("print"))) {
		this->synonym_type = QuerySynonymType::print;
	}
	else if (std::regex_match(synonym_type_string, std::regex("while"))) {
		this->synonym_type = QuerySynonymType::whiles;
	}
	else if (std::regex_match(synonym_type_string, std::regex("if"))) {
		this->synonym_type = QuerySynonymType::ifs;
	}
	else if (std::regex_match(synonym_type_string, std::regex("assign"))) {
		this->synonym_type = QuerySynonymType::assign;
	}
	else if (std::regex_match(synonym_type_string, std::regex("variable"))) {
		this->synonym_type = QuerySynonymType::variable;
	}
	else if (std::regex_match(synonym_type_string, std::regex("constant"))) {
		this->synonym_type = QuerySynonymType::constant;
	}
	else if (std::regex_match(synonym_type_string, std::regex("procedure"))) {
		this->synonym_type = QuerySynonymType::procedure;
	}

	this->synonym_name = synonym_name;
}

NODE_TYPE QueryNode::getNodeType() {
	return node_type;
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
