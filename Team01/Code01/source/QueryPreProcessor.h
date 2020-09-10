#pragma once

#include <string>

#include "QueryNode.h"

typedef string QUERY;
typedef QueryNode PROCESSED_SYNONYMS;
typedef QueryNode PROCESSED_CLAUSES;
typedef bool VALIDATION_RESULT;
typedef string SYNONYMS;
typedef string CLAUSES;

class QueryPreProcessor {
	/* Overview: Pre-processes queries into a suitable data structure for the evaluator */

public:
	PROCESSED_SYNONYMS preProcessSynonyms(QUERY q);
	/*
		Description:
		  Normal: Returns a PROCESSED_SYNONYMS
		*/

	PROCESSED_CLAUSES preProcessClauses(QUERY q);
	/*
		Description:
		  Normal: Returns a PROCESSED_CLAUSES
		*/

	VALIDATION_RESULT validateSynonyms(SYNONYMS s);
	/*
		Description:
		  Normal: Returns a VALIDATION_RESULT based on grammer for synonyms
		*/

	VALIDATION_RESULT validateClauses(CLAUSES c);
	/*
		Description:
		  Normal: Returns a VALIDATION_RESULT based on grammar for clauses
		*/

	VALIDATION_RESULT validateQuery(PROCESSED_SYNONYMS s, PROCESSED_CLAUSES c);
	/*
		Description:
		  Normal: Returns VALIDATION_RESULT based on looking at the query as a whole
		*/

};