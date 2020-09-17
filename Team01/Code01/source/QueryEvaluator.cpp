#include "QueryEvaluator.h"

QueryEvaluator::QueryEvaluator(PKB pkb) {
	this->pkb = pkb;
}

QUERY_RESULT QueryEvaluator::evaluateQuery(PROCESSED_SYNONYMS synonyms, PROCESSED_CLAUSES clauses) {
	ResultList result_list; //initialise to empty_result
	ResultList* result_list_ptr = &result_list;
	FINAL_RESULT result = "";
	QueryNode chosen_return_type;
	SYNONYM_NAME chosen_synonym_name;
	
	QUERY_NODE_POINTERS children = clauses.getChildren();
	if (clauses.getNodeType() == QueryNodeType::select) {
		chosen_return_type = children[0];
		chosen_synonym_name = chosen_return_type.getString(); // "v"

		// fill resultList with chosen_return_type

		int children_size = sizeof(children) / sizeof(QueryNode);
		for (int i = 1; i < children_size; i++) {
			// define resultList

			QueryNode clause = children[i];
			QueryNodeType clause_type = clause.getNodeType();
			if (clause_type == QueryNodeType::such_that) {
				QueryNode relationship = clause.getChildren()[0];
				QueryNodeType relationship_type = relationship.getNodeType();
				QueryNode child1 = relationship.getChildren()[0];
				QueryNode child2 = relationship.getChildren()[1];
				QueryNodeType child1_type = child1.getNodeType();
				QueryNodeType child2_type = child2.getNodeType();

				if (relationship_type == QueryNodeType::follows) {
					/* Follows(s1, s2)
					s1 = [1, 2, 3] if assign
					s2 = [1, 2, 3]
					cross = [[1,1], [1,2], [1,3]...]

					filter the cross with PKB

					then add to ResultList*/
					std::vector<int> list1;
					std::vector<int> list2;
					
					if (child1_type == QueryNodeType::integer) {
						list1.push_back(child1.getInteger());
					} else if (child1_type == QueryNodeType::synonym) {
						QuerySynonymType child1_syn_type = child1.getSynonymType();
						if (child1_syn_type == QuerySynonymType::assign) {
							list1.emplace_back(pkb.getAssignNumList());
						}
						// fill in the blanks :)
					}

					std::vector<std::pair<int, int>> cross;
					for (int s1 : list1) {
						for (int s2 : list2) {
							cross.push_back({s1, s2});
						}
					}

					// filter the cross with PKB.isFollows
					// and add to ResultList!

				} else if (relationship_type == QueryNodeType::followsT) {

				} else if (relationship_type == QueryNodeType::parent) {

				} else if (relationship_type == QueryNodeType::parentT) {

				} else if (relationship_type == QueryNodeType::uses) {
					std::vector<std::pair<int, std::string>> stmt_cross; 
					std::vector<std::pair<std::string, std::string>> proc_cross; 

				} else if (relationship_type == QueryNodeType::modifies) {

				}
			} else if (clause_type == QueryNodeType::pattern) {
				// magic
			}
			
			// if ResultList is empty, then return ""

			// merge resultList
			// resultList = merge(resultList, relationship_resultList)
		}
	}


	//intermediate result_list can have many synonyms
	//but final result should return just 1 string/empty

	//result_list = ResultListManager::addSynonymAndValues(result_list_ptr, chosen_synonym_name, variable_names);

	//if (ResultListManager::containsSynonym(result_list, chosen_synonym_name)) {
	//	result = ResultListManager::getValues(result_list, chosen_synonym_name);
	//}
	//else {
	// Don't need to "print" anything if ResultList is empty
	//	result = "";
	//}
	
	//select v such that Uses(a,v)
	//select v such that Follows(2,s)

	return result;
}

