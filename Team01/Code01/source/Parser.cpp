#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>

<<<<<<< HEAD
using namespace std;

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
	for (string str : str_list) {
		std::cout << "\nNEWLINE " << line_cnt << ": " << str;
		//call parseLine
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



int parseLine(STRING str) {
	//Takes out only first set of whitespaces

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
	//We assume that this line will either terminate with '{' or ';' with the exception of whitespaces and newline?
	return 0;
}

int parseIf(STRING str) {
	//We assume that this line will either terminate with '{' or ';' with the exception of whitespaces and newline?

	return 0;
}

int parseElse(STRING str) {
	//We assume that '{' will follow 'else'
	//We assume that this line will either terminate with '{' or ';' with the exception of whitespaces and newline?
	return 0;
}

int parseAssign(STRING str) {
	//We assume that this line will terminate with ';'

	return 0;
}

int parseRead(STRING str) {
	//We assume that this line will terminate with ';'
	return 0;
}

int parsePrint(STRING str) {
	//We assume that this line will terminate with ';'
	return 0;
}

int parseProcedure(STRING str) {
	//We assume that this line will either terminate with '{' or ';' with the exception of whitespaces and newline?
	return 0;
}

int parseCall(STRING str) {
	//We assume that this line will terminate with ';'
	return 0;
}

int parseStmtListClose(STRING str) {
	//We make no assumptions that '}' ends this line. We check for any leftover non-whitespace characters
	//and call parseLine on the remainding stringif there are. 

	//look up parent to close the stmt node and change the parent node
	//If closing a stmtList Node, we must ensure there exists at least 1 stmt
	//remove '}'
	//check if there is remaining str
		//call parseLine on remainder of str
	//else end
	return 0;
}
>>>>>>> Change Parser assumptions
