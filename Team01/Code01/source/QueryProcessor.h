#pragma once

class QueryProcessor {
	/* Overview: Oversees and drives the pre-processor and evaluator*/

public:
	QUERY_RESULT processQuery(QUERY q);
	/*
		Description:
		  Normal: Returns the QUERY_RESULT
		  Abnormal: If 'q' is not a valid query, throw an exception
		*/
};