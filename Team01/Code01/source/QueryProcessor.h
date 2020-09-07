#pragma once

#include <string>

class QueryProcessor;

typedef std::string QUERY_RESULT;
typedef std::string QUERY;

class QueryProcessor {
public:
	QueryProcessor();
	QUERY_RESULT processQuery(QUERY q);
};
