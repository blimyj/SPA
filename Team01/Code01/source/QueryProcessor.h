#pragma once

#include "PKB.h"
#include "PKBBuilder.h"

#include <string>

class QueryProcessor;

typedef std::string QUERY_RESULT;
typedef std::string QUERY;

class QueryProcessor {
private:
	PKB pkb = (PKBBuilder().build()); // because PKB has no default constructor
public:
	QueryProcessor();
	QueryProcessor(PKB pkb);
	QUERY_RESULT processQuery(QUERY q);
};
