#include <regex>
#include <string>

#include "QueryPreProcessor.h"

PROCESSED_SYNONYMS preProcessSynonyms(QUERY q) {
	// find the synonyms in the query, which come before semicolons

	// validate grammar of synonyms

}

PROCESSED_CLAUSES preProcessClauses(QUERY q) {
	// find the clauses in the query, which come after semicolons

	// validate grammar of clauses

}

VALIDATION_RESULT validateSynonyms(SYNONYMS s) {
	VALIDATION_RESULT result = true;

	// check if any synonyms are declared

	// check if declaration follows the rule of: design-entity synonym (‘,’ synonym)* ‘;’

	// check if name follows rule of: LETTER ( LETTER | DIGIT )*

	return result;
}

VALIDATION_RESULT validateClauses(CLAUSES c) {
	VALIDATION_RESULT result = true;

	// check if clauses start with "Select"

	// check if has at most one such that and pattern clauses

	// check if clause has correct number of arguments

	return result;
}

VALIDATION_RESULT validateQuery(PROCESSED_SYNONYMS s, PROCESSED_CLAUSES c) {
	VALIDATION_RESULT result = true;

	// check if arguments used in clauses are declared

	// check if type of arguments used for clause is correct

	return result;
}