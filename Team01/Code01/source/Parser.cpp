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
>>>>>>> TEMP: Saving work on parser. Hit roadblock on calling parseSecondStreamToken after new lines

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
	std::cout << "parsed " << filename << "\n";
	
	std::string str;
	LIST_OF_STRINGS file_contents;
	

	// Read file
	std::ifstream fileObj(filename);
	while (std::getline(fileObj, str))
	{
		file_contents.push_back(str);
	}

	parseText(file_contents);
	// Consume each line append to vector
	// call parseText on vector
	/**/
	return 0;
}

int parseText(LIST_OF_STRINGS str_list) {
	int line_cnt = 0;
	
	/* Due to the 1 statement across multiple lines being allowed, splitting acording to lines is no longer a good idea.
	* I now intend to read every thing possibly from a buffer (which could be a line)
	*/
	for (string str : str_list) {
		parseFirstStreamToken(str, 0);
	}

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

AST_NODE_PTR current_parent_node_ = PROGRAM_NODE();

//curr_token_stream_ stores tokens for a particular statement / opening segment
//Note that first token always denotes type of statement
std::vector<std::string> curr_token_stream_; 

//Definition of function pointer hashtable
typedef int (*PARSE_FUNC_PTR)(string, int);

std::unordered_map<std::string, PARSE_FUNC_PTR> parse_func_table_ = {
	{"read", parseRead},
	{"print", parsePrint}
};


int parseFirstStreamToken(STRING str, int ind) {
	
	//Taking a string, we want to tokenize 1 at a time, with each token telling us what we expect next.
	//We must maintain class member curr_token_stream_ <--- A vector of important tokens, I believe we can ignore the following tokens: '{', '}', ';'
	
	//Takes out only first set of whitespaces
	int str_ind = ind;
	while (str_ind < str.size() && std::isspace(str.at(str_ind))) {
		str_ind++;
	}

	//If empty line, skips to next line
	if (str_ind == str.size()) return 0;
	//After this, we know str[str_ind] is not whitespace nor the end.
	
	//First Token Checker
	if (curr_token_stream_.empty() && str[str_ind].isalnum()) {
		start_ind = str_ind;
		//read in first token of the form LETTER(LETTER|DIGIT)* ---> could be a NAME or a terminal
		while (str_ind < str.size() && str[str_ind].isalnum()) {
			str_ind++;
		}
		//take substr(old_ind, (str_ind - old_ind)) as first token and put into curr_token_stream_
		std::string token = str.substr(old_ind, (str_ind - old_ind));
		
		//Note that first token could always be var name instead of actual stmt type.
		curr_token_stream_.append(token);
		parseFirstStreamToken(str, str_ind);
	}


	else {
		//Takes out only first set of whitespaces
		int str_ind = ind;
		while (str_ind < str.size() && std::isspace(str.at(str_ind))) {
			str_ind++;
		}

		//If empty line, skips to next line
		if (str_ind == str.size()) return 0;
		//After this, we know str[str_ind] is not whitespace nor the end.

		if (curr_token_stream_.size() == 1) {
			//Check if second token is '=' to differentiate assign statement from other statements
			if (str[str_ind] == '=') {
				//Change stmt type in curr_token_stream_ to assignment
				curr_token_stream_.insert(curr_token_stream_.begin(), "assign");
			} else {
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

int parseAssign(STRING str) {
	//We assume that this statement will terminate with ';'

	return 0;
}

int parseRead(STRING str, int ind) {
	//We assume that this statement will terminate with ';'
	return 0;
}

int parsePrint(STRING str) {
	//We assume that this statement will terminate with ';'
	return 0;
}

int parseProcedure(STRING str) {
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
