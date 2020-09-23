#pragma once

#include <vector>
#include <string>
#include <deque>

#include "../source/PKB.h"
#include "OperatorTypeEnum.h"
#include "RelOperatorTypeEnum.h"

typedef std::string STRING;
typedef std::vector<std::string> LIST_OF_STRINGS;
typedef std::deque<STRING>* STMT_TOKEN_QUEUE_PTR;
typedef std::deque<STRING>* PROCESS_TOKEN_QUEUE_PTR;
typedef std::deque<STRING> STMT_TOKEN_QUEUE;
typedef std::deque<STRING> PROCESS_TOKEN_QUEUE;
typedef int STMT_NUMBER;
typedef bool BOOLEAN_TYPE;
typedef int PRECEDENCE;

class Parser {
public:
	PKB parseFile(STRING str);

private:
	void parseProcedure();
	void parseRead();
	void parsePrint();
	void parseAssign();

	void parseWhile();
	void parseIfThen();
	void parseElse();
	//int parseCall(STRING str);
	void parseStmtListClose();

	STRING getNextToken(std::istreambuf_iterator<char>* iter, std::istreambuf_iterator<char> eos);

	PROGRAM_NODE_PTR program_node_;
	AST_NODE_PTR current_parent_node_;
	PKBBuilder pkb_builder_;

	STMT_TOKEN_QUEUE stmt_token_queue_;
	PROCESS_TOKEN_QUEUE process_token_stream_;

	STMT_NUMBER stmt_num_;

	//Helper variables & functions for parsing expressions
	PRECEDENCE takesPrecedent(OperatorTypeEnum l_op, OperatorTypeEnum r_op);
	ExpressionTypeEnum getExpressionType(OperatorTypeEnum op);

	PRECEDENCE takesPrecedent(RelOperatorTypeEnum l_op, RelOperatorTypeEnum r_op);
	ExpressionTypeEnum getExpressionType(RelOperatorTypeEnum op);
	RelationTypeEnum getArithmeticRelationType(RelOperatorTypeEnum op);
	ConditionTypeEnum getBooleanRelationType(RelOperatorTypeEnum op);

	BOOLEAN_TYPE isArithmeticOp(RelOperatorTypeEnum op);
	BOOLEAN_TYPE isRelationOp(RelOperatorTypeEnum op);
	BOOLEAN_TYPE isBooleanOp(RelOperatorTypeEnum op);
};

