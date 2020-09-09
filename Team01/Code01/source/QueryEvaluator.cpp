#include "QueryEvaluator.h"

#include <string>
#include <vector>


QUERY_RESULT QueryEvaluator::evaluateQuery(PROCESSED_SYNONYMS synonyms, PROCESSED_CLAUSES clauses) {
	std::vector<std::string> result_list;
	result_list.push_back("yo yo im here");
	
	//intermediate result_list can have many synonyms
	//but final result should return just 1 string/empty
	
	return result_list[0]; 
}