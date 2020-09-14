#pragma once

#include "QueryNode.h"
#include "QueryNodeType.h"
#include "QuerySynonymType.h"
#include "ResultList.h"
#include "ResultListManager.h"
#include "PKB.h"

#include <string>
#include <unordered_map>

class QueryEvaluator;

typedef std::string QUERY_RESULT;
/*may need to typedef processed_synonyms? check with huiming on the type from preprocessor*/
typedef std::unordered_map<std::string, QueryNode> PROCESSED_SYNONYMS;
typedef QueryNode PROCESSED_CLAUSES;

class QueryEvaluator {
private:
	PKB pkb = (PKBBuilder().build()); // because PKB has no default constructor
public:
	QueryEvaluator(PKB pkb);
	QUERY_RESULT evaluateQuery(PROCESSED_SYNONYMS synonyms, PROCESSED_CLAUSES clauses);
};