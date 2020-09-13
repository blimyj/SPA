#pragma once

#include <vector>
#include <string>
#include <deque>

#include "../source/PKB.h"
#include "../source/OperatorTypeEnum.h"

typedef std::string STRING;
typedef std::vector<std::string> LIST_OF_STRINGS;
typedef std::deque<STRING>* STMT_TOKEN_QUEUE;
typedef std::deque<STRING>* PROCESS_TOKEN_QUEUE;
typedef int STMT_NUMBER;

class Parser {
public:
	int Parse();
	PKB parseFile(STRING str);
	int parseText(LIST_OF_STRINGS l_of_str);
private:
	int parseProcedure(STMT_TOKEN_QUEUE stmt_tok_queue, PROCESS_TOKEN_QUEUE proc_tok_queue);
	int parseRead(STMT_TOKEN_QUEUE stmt_tok_queue, PROCESS_TOKEN_QUEUE proc_tok_queue);
	int parsePrint(STMT_TOKEN_QUEUE stmt_tok_queue, PROCESS_TOKEN_QUEUE proc_tok_queue);
	int parseAssign(STMT_TOKEN_QUEUE stmt_tok_queue, PROCESS_TOKEN_QUEUE proc_tok_queue);

	int Parser::parseWhile(STRING str);
	int Parser::parseIfThen(STRING str);
	int Parser::parseElse(STRING str);
	int Parser::parseCall(STRING str);
	int Parser::parseStmtListClose();

	STRING getNextToken(std::istreambuf_iterator<char>* iter, std::istreambuf_iterator<char> eos);

	std::shared_ptr<ProgramNode> root_node_;
	std::shared_ptr<ASTNode> current_parent_node_;
	PKBBuilder pkb_builder_;

	std::deque<STRING> stmt_token_queue_;
	std::deque<STRING> process_token_stream_;

	STMT_NUMBER stmt_num_;

	//Helper variables & functions for parsing expressions
	int takesPrecedent(OperatorTypeEnum l_op, OperatorTypeEnum r_op);
	ExpressionTypeEnum getExpressionType(OperatorTypeEnum op);
};

