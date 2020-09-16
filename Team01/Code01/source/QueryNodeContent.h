#pragma once

#include "./PKB/ASTNode/ASTNode.h"
#include <string>

class QueryNodeContent;

typedef std::string STRING;
typedef int INTEGER;
typedef ASTNode AST_NODE;
typedef int MODIFIED_FLAG;

class QueryNodeContent {
private:
	STRING strings = "";
	INTEGER integer = -1;
	AST_NODE astnode = ASTNode();
	MODIFIED_FLAG modified = -1;
	
public:
	QueryNodeContent() {}

	QueryNodeContent(STRING content) {
		this->strings = content;
		this->modified = 1;
	}

	QueryNodeContent(INTEGER integer) {
		this->integer = integer;
		this->modified = 2;
	}

	QueryNodeContent(AST_NODE astnode) {
		this->astnode = astnode;
		this->modified = 3;
	}

	STRING getString() {
		return strings;
	}

	INTEGER getInt() {
		return integer;
	}

	AST_NODE getAstNode() {
		return astnode;
	}
};