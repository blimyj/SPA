#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include "QueryNode.h"

typedef std::string QUERY;
typedef std::vector<std::string> SPLIT_QUERY;
typedef std::string SINGLE_DECLARATION;
typedef std::string DECLARATIONS;
typedef std::unordered_map<std::string, QueryNode> PROCESSED_SYNONYMS;
typedef std::string CLAUSES;
typedef QueryNode PROCESSED_CLAUSES;
typedef QueryNode PROCESSED_CLAUSE;
typedef bool VALIDATION_RESULT;

class QueryPreProcessor {
	/* Overview: Pre-processes queries into a suitable data structure for the evaluator */

public:
	SPLIT_QUERY splitQuery(QUERY q);
	/*
		Description:
		  Normal: Returns a SPLIT_QUERY
		*/

	PROCESSED_SYNONYMS preProcessSynonyms(DECLARATIONS d);
	/*
		Description:
		  Normal: Returns PROCESSED_SYNONYMS
		  Abnormal: If synonyms are not valid, returns an empty map
		*/

	PROCESSED_CLAUSES preProcessClauses(PROCESSED_SYNONYMS proc_s, CLAUSES c);
	/*
		Description:
		  Normal: Returns PROCESSED_CLAUSES
		  Abnormal: If clauses are not valid, returns a query node with a null NODE_TYPE
		*/

private:
	VALIDATION_RESULT isValidStructure(QUERY q);
	/*
		Description:
		  Normal: Returns a VALIDATION_RESULT based on general structure of input query
		*/

	VALIDATION_RESULT isValidDeclaration(SINGLE_DECLARATION single_d);
	/*
		Description:
		  Normal: Returns a VALIDATION_RESULT based on grammer for declarations
		*/

	VALIDATION_RESULT isValidClause(CLAUSES c);
	/*
		Description:
		  Normal: Returns a VALIDATION_RESULT based on grammar for clauses
		*/

	VALIDATION_RESULT isValidQuery(PROCESSED_SYNONYMS proc_s, PROCESSED_CLAUSES proc_c);
	/*
		Description:
		  Normal: Returns VALIDATION_RESULT based on looking at the query as a whole
		*/

	VALIDATION_RESULT isValidRelation(PROCESSED_SYNONYMS proc_s, PROCESSED_CLAUSE proc_c);
	/*
		Description:
		  Normal: Returns a VALIDATION_RESULT based on relationship semantics
		*/

	VALIDATION_RESULT isValidPattern(PROCESSED_SYNONYMS proc_s, PROCESSED_CLAUSE proc_c);
	/*
		Description:
		  Normal: Returns a VALIDATION_RESULT based on pattern semantics
		*/
};