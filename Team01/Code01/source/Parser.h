#pragma once

#include <vector>
#include <string>
#include <deque>

typedef std::string STRING;
typedef std::vector<std::string> LIST_OF_STRINGS;
typedef std::deque<STRING>* STMT_TOKEN_QUEUE;
typedef std::deque<STRING>* PROCESS_TOKEN_QUEUE;


int Parse();
int parseFile(STRING);
int parseText(LIST_OF_STRINGS);

int parseProcedure(STMT_TOKEN_QUEUE stmt_tok_queue, PROCESS_TOKEN_QUEUE proc_tok_queue);
int parseRead(STMT_TOKEN_QUEUE stmt_tok_queue, PROCESS_TOKEN_QUEUE proc_tok_queue);
int parsePrint(STMT_TOKEN_QUEUE stmt_tok_queue, PROCESS_TOKEN_QUEUE proc_tok_queue);
int parseAssign(STMT_TOKEN_QUEUE stmt_tok_queue, PROCESS_TOKEN_QUEUE proc_tok_queue);

STRING getNextToken(std::istreambuf_iterator<char>* iter, std::istreambuf_iterator<char> eos);
