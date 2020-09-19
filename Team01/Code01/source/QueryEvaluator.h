#pragma once

#include "QueryNode.h"
#include "QueryNodeType.h"
#include "QuerySynonymType.h"
#include "ResultList.h"
#include "ResultListManager.h"
#include "PKB.h"

#include <string>
#include <unordered_map>
#include <vector>

class QueryEvaluator;

typedef std::vector<std::string> QUERY_RESULT;
/*may need to typedef processed_synonyms? check with huiming on the type from preprocessor*/
typedef std::unordered_map<std::string, QueryNode> PROCESSED_SYNONYMS;
typedef QueryNode PROCESSED_CLAUSES;

class QueryEvaluator {
	/* Overview: Evaluates pre-processed queries and returns the result */

private:
	PKB pkb = (PKBBuilder().build()); // because PKB has no default constructor
	STMT_NUM_LIST QueryEvaluator::getStmtList(QueryNode child1);

public:
	QueryEvaluator(PKB pkb);
	/*
		Description:
		  Normal:
		*/

	QUERY_RESULT evaluateQuery(PROCESSED_SYNONYMS synonyms, PROCESSED_CLAUSES clauses);
	/*
		Requires: A query in the form of PROCESSED_SYNONYMS and PROCESSED_CLAUSES
		Description:
		  Normal: Returns the QUERY_RESULT
		  Abnormal: If 's' and 'c' is not a valid processed query, throw an exception
		*/
};