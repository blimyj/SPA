#pragma once

#include "./PKB/ASTNode/ASTNode.h"
#include <string>

class QueryNodeContent;


class QueryNodeContent {
private:
	std::string strings = NULL;
	int integer = -1;
	ASTNode astnode = NULL;
	
public:
	void QueryNodeContent(T content) {
		this->content = content;
	}
	T getContent() {
		return content;
	}
};