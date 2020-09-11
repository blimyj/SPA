#include "QueryEvaluator.h"

#include <string>
#include <vector>

QueryEvaluator::QueryEvaluator(PKB pkb) {
	this->pkb = pkb;
}

QUERY_RESULT QueryEvaluator::evaluateQuery(PROCESSED_SYNONYMS synonyms, PROCESSED_CLAUSES clauses) {
	std::vector<std::string> result_list;
	result_list.push_back("yo yo im here"); //initialise to empty_result
	QueryNode chosen_return_type;
	
	QUERY_NODE_POINTERS children = clauses.getChildren();
	if (clauses.getNodeType() == QueryNodeType::select) {
		result_list[0] = result_list[0] + "\n" + "Select Worked";
		chosen_return_type = children[0];
		result_list[0] = result_list[0] + "\n" + "chosen return synonym name: " + chosen_return_type.getSynonymName();
	}
	
	//intermediate result_list can have many synonyms
	//but final result should return just 1 string/empty
	
	return result_list[0]; 
}