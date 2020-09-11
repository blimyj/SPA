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

	// Hard coded result from PKBStub
	VAR_NODE_PTR_LIST all_variables = pkb.getVariables();
	std::string variable_string = "";
	for (VAR_NODE_PTR variable : all_variables) {
		VariableNode variable_node = *variable;
		variable_string += variable_node.getVariableName();
	}
	result_list[0] = result_list[0] + "\n" + variable_string;

	
	//intermediate result_list can have many synonyms
	//but final result should return just 1 string/empty
	
	return result_list[0]; 
}