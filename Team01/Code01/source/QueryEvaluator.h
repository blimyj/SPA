#pragma once

#include "QueryNode.h"

#include <string>
#include <unordered_map>

class QueryEvaluator;

typedef std::string QUERY_RESULT;
/*may need to typedef processed_synonyms? check with huiming on the type from preprocessor*/
typedef std::unordered_map<std::string, QueryNode> PROCESSED_SYNONYMS;
typedef QueryNode PROCESSED_CLAUSES;

class QueryEvaluator {
public:
	QUERY_RESULT evaluateQuery(PROCESSED_SYNONYMS synonyms, PROCESSED_CLAUSES clauses);
};