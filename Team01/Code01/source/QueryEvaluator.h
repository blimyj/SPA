#pragma once

class QueryEvaluator {
	/* Overview: Evaluates pre-processed queries and returns the result */

public:
	QUERY_RESULT evaluateQuery(PROCESSED_SYNONYMS s, PROCESSED_CLAUSES c);
	/*
		Requires: A query in the form of PROCESSED_SYNONYMS and PROCESSED_CLAUSES
		Description:
		  Normal: Returns the QUERY_RESULT
		  Abnormal: If 's' and 'c' is not a valid processed query, throw an exception
		*/
};