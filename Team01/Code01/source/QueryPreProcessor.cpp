#include <regex>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "QueryPreProcessor.h"
#include "QueryNodeType.h"


const std::regex name_format_("[a-zA-Z][a-zA-Z0-9]*");
const std::regex declaration_format_("\\s*(stmt|read|print|while|if|assign|variable|constant|procedure)\\s+[a-zA-Z][a-zA-Z0-9]*\\s*(\\,\\s*[a-zA-Z][a-zA-Z0-9]*)*\\s*\\;\\s*");
//const std::regex clause_format_("Select\\s+[a-zA-Z][a-zA-Z0-9]*(()?()?|()?()?)");

SPLIT_QUERY splitQuery(QUERY q) {
	SPLIT_QUERY split_q;
	DECLARATIONS d = "";
	CLAUSES c = "";

	if (isValidStructure(q)) {
		// split the query into declarations and clauses
		std::string delimiter = ";";
		int split_index = q.rfind(delimiter);
		d = q.substr(0, split_index));
		c = q.substr(split_index + 1);
	}
	split_q.push_back(d);
	split_q.push_back(c);

	return split_q;
}

PROCESSED_SYNONYMS preProcessSynonyms(DECLARATIONS d) {
	PROCESSED_SYNONYMS proc_s;
	VALIDATION_RESULT is_valid;

	// process declaration-by-declaration
	std::string delimiter = ";";
	int index = 0;
	int split_index = s.find(delimiter);

	if (split_index == -1) {
		// if there is only one declaration (no other semicolons)
		is_valid = isValidDeclaration(d);

		// break into synonyms
		// create query node for each synonym
		// add query node to PROCESSED_SYNONYMS
	}
	else {
		while (split_index != -1) {

		}
	}

	if (is_valid) {
		return proc_s;
	}
	else {
		return PROCESSED_SYNONYMS empty_map;
	}

}

PROCESSED_CLAUSES preProcessClauses(PROCESSED_SYNONYMS proc_s, CLAUSES c) {

	// find the clauses in the query, which come after the last semicolon


	// validate grammar of clauses

}

VALIDATION_RESULT isValidStructure(QUERY q) {
	/*
	Validation rules:
		- Query is not empty
		- Has a declaration
		- Has 'Select'
	*/
	if (q.length() <= 0) {
		return false;
	}
	else if (q.find(";") == -1) {
		return false;
	}
	else if (q.find("Select") == -1) {
		return false;
	}
	else {
		return true;
	}
}

VALIDATION_RESULT isValidDeclaration(SINGLE_DECLARATION single_d) {
	/*
	Validation rules:
		- Declaration must not be empty
		- Follows the format: design-entity synonym (‘,’ synonym)* ‘;’
		- Declared design entiry is valid
		- Synonym names follows the format: LETTER ( LETTER | DIGIT )*
	*/
	if (single_d.length() <= 0) {
		return false;
	}
	else if (std::regex_match(single_d, declaration_format_)) {
		return false;
	}
	else {
		return true;
	}
}

VALIDATION_RESULT isValidClause(CLAUSES c) {
	/*
	Validation rules:
		- There is a synonym after 'Select'
		- Has at most one 'such that' and 'pattern' clauses
		- Clauses have correct number of arguments
	*/
	if () {
	}

}

VALIDATION_RESULT isValidQuery(PROCESSED_SYNONYMS proc_s, PROCESSED_CLAUSES proc_c) {

	// check if arguments used in clauses are declared

	// check if type of arguments used for clauses are correct

}

VALIDATION_RESULT isValidRelation(PROCESSED_SYNONYMS proc_s, PROCESSED_CLAUSE proc_c) {

	// check if type of arguments used for clause is correct

}

VALIDATION_RESULT isValidPattern(PROCESSED_SYNONYMS proc_s, PROCESSED_CLAUSE proc_c) {

	// check if type of arguments used for clause is correct

}