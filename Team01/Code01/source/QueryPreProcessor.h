#pragma once

class QueryPreProcessor {
	/* Overview: Pre-processes queries into a suitable data structure for the evaluator */

public:
	PROCESSED_SYNONYMS preProcessSynonyms(QUERY q);
	/*
		Description:
		  Normal: Returns a PROCESSED_SYNONYMS
		  Abnormal: If 'q' is not a valid query, throw an exception
		*/

	PROCESSED_CLAUSES preProcessClauses(QUERY q);
	/*
		Description:
		  Normal: Returns a PROCESSED_CLAUSES
		  Abnormal: If 'q' is not a valid query, throw an exception
		*/
};