#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
<<<<<<< HEAD

<<<<<<< HEAD
using namespace std;
=======
#include <sstream>
#include <fstream>
#include <unordered_map>
<<<<<<< HEAD
>>>>>>> TEMP: Saving work on parser. Hit roadblock on calling parseSecondStreamToken after new lines
=======
#include <iterator>
#include <deque>
>>>>>>> Add tokenization to parser

#include "PKB.h"

int Parse () {

	return 0;
}
=======
#include "PKB.h"
#include "TNode.h"
#include "Parser.h"

int Parse() {

	return 0;
}

int parseFile(STRING filename) {
	//Construct program root node on heap using new
	
	
	std::string str;	

	// Construct file object
	std::ifstream fileObj(filename);
	// Construct file content iterator
	std::istreambuf_iterator<char> eos;
	std::istreambuf_iterator<char> iit(fileObj);
	std::istreambuf_iterator<char>* iit_p = &iit;
	std::deque<STRING> process_token_stream;
	std::string token;

	//This is to parse all token from file string and enqueue to token_stream_
	//While iterator not end of file

	while (*iit_p != eos) {
		//call getNextToken
		token = getNextToken(iit_p, eos);
		//Enqueue to token_stream_
		if (token != " ") {
			process_token_stream.push_back(token);
		}
		else {
			break;
		}
	}
	
	
	//This loop processes the tokens to construct nodes

	//stmt_token_queue stores tokens for a particular statement / opening segment
	//Note that first token always denotes type of statement
	std::deque<STRING> stmt_token_queue;
	std::string stmt_token;
	while (!process_token_stream.empty()) {
		
		//Check first two tokens, then call appropriate parse function
		stmt_token = process_token_stream.front();
		process_token_stream.pop_front();

		//Checks for '=' token that denotes assign type
		if (!process_token_stream.empty() && process_token_stream.front() == "=") {
			process_token_stream.pop_front();
			stmt_token_queue.push_back("assign");
			stmt_token_queue.push_back(stmt_token); //This would be the variable name
			parseAssign(&stmt_token_queue, &process_token_stream);
			continue;
		}
		
		if (stmt_token == "procedure") {
			stmt_token_queue.push_back(stmt_token); //This is "procedure" token
			parseProcedure(&stmt_token_queue, &process_token_stream);
			continue;
		}

		if (stmt_token == "read") {
			stmt_token_queue.push_back(stmt_token); //This is "read" token
			parseRead(&stmt_token_queue, &process_token_stream);
			continue;
		}

		if (stmt_token == "print") {
			stmt_token_queue.push_back(stmt_token); //This is "print" token
			parsePrint(&stmt_token_queue, &process_token_stream);
			continue;
		}

		//Handler for all other tokens, prints them out
		std::cout << "\n" << stmt_token;
	}
	

	return 0;
}

STRING getNextToken(std::istreambuf_iterator<char>* iter, std::istreambuf_iterator<char> eos) {
	std::string curr_token;

	//Skip past all whitespaces
	while (*iter != eos && isspace(**iter)) ++*iter;

	//Check if end of file
	if (*iter == eos) {
		return " ";
	}
	//TODO: Loop calling getNextToken() is responsible for checking if return is a space before adding the returned token to process_token_stream_
	//Guaranteed to never return space otherwise due to skipping space.

	//Check for NAME token
	if (isalpha(**iter)) { //This guarantees first char is LETTER
		while (*iter != eos && isalnum(**iter)) {
			curr_token += **iter;
			++*iter;
		}
		return curr_token;
	}

	//Check for bracket terminal tokens
	if (**iter == '{' || **iter == '}' || **iter == '(' || **iter == ')') {
		curr_token += **iter;
		++* iter;
		return curr_token;
	}

	//Check for semicolon terminal tokens
	if (**iter == ';') {
		curr_token += **iter;
		++* iter;
		return curr_token;
	}

	//TILL HERE

	//Check for CONSTANT tokens

	//Check for '=' vs '==' terminal tokens

	//Check for arithmetic terminal tokens & assign

	//Check for boolean terminal tokens

	//Check for unexpected tokens
	curr_token += "UNEXPECTED TOKEN:";
	curr_token += **iter;
	++* iter;
	return curr_token;
}

int parseText(LIST_OF_STRINGS str_list) {

	// Not considered for now.
	return 0;
}

/*Note: For 'read' / 'print' / 'procedure' / 'call' we are unsure if keyword<NAME> is valid.
However we assume they are not for now. (This has been confirmed)
For example
"readx"
"procedureabv"
"callmain"
*/

/*Note: We assume that the first 4 terminals of the while stmt must be on the same line
‘while’ ‘(’ cond_expr ‘)’ ‘{‘ stmtLst <----- Terminals must be on the same line, stmtLst could be on same or diff.

stmtLst ‘}’ <---- Can be on a different line, we make no assumption if stmtLst & ‘}’ must be on the same line
*/

/*Note: We assume that the first 4 terminals of the if stmt must be on the same line
‘if’ ‘(’ cond_expr ‘)’ ‘then’ ‘{‘ stmtLst <----- Terminals must be on the same line, stmtLst could be on same or diff.

stmtLst ‘}’ ‘else’ ‘{‘ stmtLst ‘}’ <- Can be on a different line,
										we make no assumption if any of these terminals & non-terminals must be on the same line
*/

/*Note: We do not assume that a newline must follow '}' */

/*Note: (WRONG ASSUMPTION) We are assuming each statement cannot be spread out across multiple lines
For example, the following is invalid
a
=
3;
*/

/*Note: (WRONG ASSUMPTION) We are assuming each statement must end with a ; on the same line.
For example, the following is invalid
a=3;
*/


/*
For read, print, assign, call statements, the terminal ';' to indicate the end of the statement.

For procedure, while, if-then, else statement, the terminal '{' indicates the end of the opening segment of the container statement.

For statement lists, the terminal  '}' to indicate the end of the statement list.

Please note that for the above statements that the end of the statement, statement list, or opening segment
DOES NOT indicate the end of the line. There can be combinations of the aforementioned in a single line. (A 50 line program could be compressed to 1 line)
*/

/*
Due to the possibility of 'read', 'print', 'if', 'else', 'then', 'while', 'procedure', 'call' being variable names,
we must look ahead at least 1 token to see if it is an assign statement.
*/

/*
Note that for cond_expr, if a boolean operator is applied to it, the operand(s) cond_expr will each be encapsulated by the terminals '(', ')'
*/

//AST_NODE_PTR current_parent_node_ = PROGRAM_NODE();

/*
int parseFirstStreamToken(std::deque<STRING>* stmt_token_stream, std::deque<STRING>* ) {
	
	//Taking a string, we want to tokenize 1 at a time, with each token telling us what we expect next.
	//We must maintain class member curr_token_stream_ <--- A vector of important tokens, I believe we can ignore the following tokens: '{', '}', ';'
	
	//Takes out only first set of whitespaces
	int str_ind = ind;
	int str_size = str.size();
	while (str_ind < str_size && std::isspace(str.at(str_ind))) {
		str_ind++;
	}

	//If empty line, skips to next line
	if (str_ind == str_size) { return 0; }
	//After this, we know str.at(str_ind)is not whitespace nor the end.

	//First Token Checker
	if (curr_token_stream_.empty() && isalnum(str.at(str_ind))) {
		int old_ind = str_ind;
		//read in first token of the form LETTER(LETTER|DIGIT)* ---> could be a NAME or a terminal
		while (str_ind < str_size && isalnum(str.at(str_ind))) {
			str_ind++;
		}
		//take substr(old_ind, (str_ind - old_ind)) as first token and put into curr_token_stream_
		std::string token = str.substr(old_ind, (str_ind - old_ind));
		
		//Note that first token could always be var name instead of actual stmt type.
		curr_token_stream_.push_back(token);
		parseFirstStreamToken(str, str_ind);
	}


	else {
		//Takes out only first set of whitespaces
		int str_ind = ind;
		while (str_ind < str_size && std::isspace(str.at(str_ind))) {
			str_ind++;
		}

		//If empty line, skips to next line
		if (str_ind == str_size) return 0;
		//After this, we know str.at(str_ind)is not whitespace nor the end.

		if (curr_token_stream_.size() == 1) {
			//Check if second token is '=' to differentiate assign statement from other statements
			if (str.at(str_ind)== '=') {
				//Change stmt type in curr_token_stream_ to assignment
				curr_token_stream_.insert(curr_token_stream_.begin(), "assign");
			} else {
				STRING token = curr_token_stream_.at(0);
				PARSE_FUNC_PTR parse_func = parse_func_table_[token];
				parse_func(str, str_ind);
			}
		}
		//could be another alnum token
		//could be assign operator
		//could be a terminal like '{', '}', ';', '(', ')', arithmetic operators, boolean operators
		//not sure if it could be terminals such as comparison operators
	}
	//check for 'if' / 'while' in the first 2 and 5 chars  respectively & a '(' exists (Otherwise it could be a var name)
		//call parseIf & parseWhile respectively
	
	//check for '='
		//call parseAssign
	
	//check for 'read' / 'print' / 'procedure' / 'call'
		//call parseRead & parsePrint & parseProc & parseCall respectively

	//check for '}'
		//call parseStmtListClose;
	
	//check for 'else'
		//call parseElse
	
	return 0;
}
*/
int parseWhile(STRING str) {
	//We assume that this opening segment will either terminate with '{' or ';' with the exception of whitespaces and newline?
	return 0;
}

int parseIfThen(STRING str) {
	//We assume that this opening segment will either terminate with '{' or ';' with the exception of whitespaces and newline?

	return 0;
}

int parseElse(STRING str) {
	//We assume that '{' will follow 'else'
	//We assume that this opening segment will either terminate with '{' or ';' with the exception of whitespaces and newline?
	return 0;
}

int parseAssign(STMT_TOKEN_QUEUE stmt_tok_queue, PROCESS_TOKEN_QUEUE proc_tok_queue) {
	//We assume that this statement will terminate with ';'

	return 0;
}

int parseRead(STMT_TOKEN_QUEUE stmt_tok_queue, PROCESS_TOKEN_QUEUE proc_tok_queue) {
	//We take in two tokens, expecting a NAME and a ';'
		//Then we construct a node and insert to parent.
	//return a non-zero int otherwise
	return 0;
}

int parsePrint(STMT_TOKEN_QUEUE stmt_tok_queue, PROCESS_TOKEN_QUEUE proc_tok_queue) {
	//We take in two tokens, expecting a NAME and a ';'

	//return a non-zero int otherwise	return 0;
}

int parseProcedure(STMT_TOKEN_QUEUE stmt_tok_queue, PROCESS_TOKEN_QUEUE proc_tok_queue) {
	//We assume that this opening segment will either terminate with '{' or ';' with the exception of whitespaces and newline?
	return 0;
}

int parseCall(STRING str) {
	//We assume that this statement will terminate with ';'
	return 0;
}

int parseStmtListClose(STRING str) {
	//Part 1: When closing a stmtList Node, 
		//we must ensure there exists at least 1 stmt (if == 0 child)
			//print parsing error -> incorrect code
	//remove '}'
	

	//Part 2:
	//Assuming we maintain curr_parent_node_

	//There are 2 different ways to change the curr_parent_node_ (Refer to StmtListCloseChangeParentNode image)
	//if (curr_parent_node_.getParent().getType() == IF_NODETYPE_ENUM)
		//cast to parent of curr_parent_node_ to IF_NODE*
		//check if its ThenStatementListNode is equal to curr_parent_node_ (after we cast curr_parent_node_ to STMT_LIST_NODE*)
		//if ( ((IF_NODE*) curr_parent_node_.getParent()).getThenStatementListNode()) == ((STMT_LIST_NODE*) curr_parent_node_) )
			//change curr_parent_node_ to point to ELSE_STMT_LIST_NODE
			//We assume that it was pre-created when we created the IF_STMT_LIST_NODE
			//curr_parent_node_ =  (AST_NODE*) (((IF_NODE*) curr_parent_node_.getParent()).getElseStatementListNode())
		//else
			//change curr_parent_node_ to point to STMT_LIST_NODE that contains the IF_NODE
			//curr_parent_node_ = curr_parent_node_.getParent().getParent()
	//else
		//change curr_parent_node_ to point to grandparent node of curr_parent_node_
		//curr_parent_node_ must be STMT_LIST_NODE
		//it's parent can be PROCEDURE_NODE, WHILE_NODE or IF_NODE (if this is an ELSE_STMT_LIST_NODE)
		//therefore grandparent node can be PROGRAM_NODE or STMT_LIST_NODE
		//curr_parent_node_ = curr_parent_node_.getParent().getParent()





	//Part 3:
	//We make no assumptions that '}' ends this line. We check for any leftover non-whitespace characters
	//and call parseLine on the remainding string if there are remaining chars. 
	//check if there is remaining str
		//call parseLine on remainder of str
	//else end
	return 0;
}
>>>>>>> Change Parser assumptions
