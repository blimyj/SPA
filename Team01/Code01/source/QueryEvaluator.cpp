#include "QueryEvaluator.h"

QueryEvaluator::QueryEvaluator(PKB pkb) {
	this->pkb = pkb;
}

QUERY_RESULT QueryEvaluator::evaluateQuery(PROCESSED_SYNONYMS synonyms, PROCESSED_CLAUSES clauses) {
	ResultList result_list;
	const QUERY_RESULT no_result = QUERY_RESULT();

	// If no synonyms are declared, Query is INVALID. Return no result.
	if (synonyms.size() == 0) {
		return no_result;
	}

	// If root of clauses tree is unassigned, then the clause is syntactically incorrect. Return no result.
	if (clauses.getNodeType() == QueryNodeType::unassigned) {
		return no_result;
	}

	QUERY_NODE_LIST children = clauses.getChildren();
	if (children.size() == 0) {
		throw "Error: Select has no children, it should have at least 1 child (ie Select v)";
	}
	QueryNode return_synonym = children[0];
	QuerySynonymType return_synonym_type = return_synonym.getSynonymType();
	SYNONYM_NAME return_synonym_name = return_synonym.getString(); // "v"

	// fill resultList with return_synonym_name
	if (return_synonym_type == QuerySynonymType::assign) {
		result_list.addColumn(return_synonym_name, pkb.getAssignNumList());
	}
	else if (return_synonym_type == QuerySynonymType::constant) {
		result_list.addColumn(return_synonym_name, pkb.getConstantValueList());
	}
	else if (return_synonym_type == QuerySynonymType::ifs) {
		result_list.addColumn(return_synonym_name, pkb.getIfNumList());
	}
	else if (return_synonym_type == QuerySynonymType::print) {
		result_list.addColumn(return_synonym_name, pkb.getPrintNumList());
	}
	else if (return_synonym_type == QuerySynonymType::procedure) {
		result_list.addColumn(return_synonym_name, pkb.getProcedureNameList());
	}
	else if (return_synonym_type == QuerySynonymType::read) {
		result_list.addColumn(return_synonym_name, pkb.getReadNumList());
	}
	else if (return_synonym_type == QuerySynonymType::stmt) {
		result_list.addColumn(return_synonym_name, pkb.getStatementNumList());
	}
	else if (return_synonym_type == QuerySynonymType::variable) {
		result_list.addColumn(return_synonym_name, pkb.getVariableNameList());
	}
	else if (return_synonym_type == QuerySynonymType::whiles) {
		result_list.addColumn(return_synonym_name, pkb.getWhileNumList());
	}

	// for all clauses in Select (not including the synonym)
	for (int i = 1; i < children.size(); i++) {
		bool clause_bool = false;
		ResultList clause_result_list;

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

				// Initialize with list of all values for the given synonym
				std::vector<int> list1;
				std::vector<int> list2;

				try {
					list1 = getStmtList(child1);

					list2 = getStmtList(child2);
				}
				catch (const char* msg) {
					std::cout << msg << "\n";
				}


				// create all possible pairs of list1 and list2 values
				std::vector<std::pair<int, int>> cross;
				for (int s1 : list1) {
					for (int s2 : list2) {
						cross.push_back({ s1, s2 });
					}
				}

				// filter the cross with PKB.isFollows
				std::vector<std::pair<int, int>> filter;
				for (std::pair<int, int> p : cross) {
					if (pkb.isFollows(p.first, p.second)) {
						filter.push_back(p);
					}
				}

				// after filtering:
				// if the filtered list is empty, then we say that this clause is FALSE
				// else, this clause is TRUE
				clause_bool = (filter.size() > 0);

				// Add the filtered to ResultList!
				// 1. Add the synonym names to as column headers
				if (child1_type == QueryNodeType::synonym) {
					SYNONYM_NAME synonym_name = child1.getString();
					clause_result_list.addColumn(synonym_name);
				}
				if (child2_type == QueryNodeType::synonym) {
					SYNONYM_NAME synonym_name = child2.getString();
					clause_result_list.addColumn(synonym_name);
				}

				// 2. Add synonym values to the Resultlist row wise
				for (std::pair<int, int> p : filter) {
					ROW row;
					if (child1_type == QueryNodeType::synonym) {
						SYNONYM_NAME child1_synonym_name = child1.getString();
						SYNONYM_VALUE child1_synonym_value = std::to_string(p.first);
						row.insert({ child1_synonym_name, child1_synonym_value });
					}
					if (child2_type == QueryNodeType::synonym) {
						SYNONYM_NAME child2_synonym_name = child2.getString();
						SYNONYM_VALUE child2_synonym_value = std::to_string(p.second);
						row.insert({ child2_synonym_name, child2_synonym_value });
					}
					clause_result_list.addRow(row);
				}

			}
			else if (relationship_type == QueryNodeType::followsT) {

				std::vector<int> list1 = getStmtList(child1);
				std::vector<int> list2 = getStmtList(child2);

				// create all possible pairs of list1 and list2 values
				std::vector<std::pair<int, int>> cross;
				for (int s1 : list1) {
					for (int s2 : list2) {
						cross.push_back({ s1, s2 });
					}
				}

				// filter the cross with PKB.isFollows
				std::vector<std::pair<int, int>> filter;
				for (std::pair<int, int> p : cross) {
					if (pkb.isFollowsTransitive(p.first, p.second)) {
						filter.push_back(p);
					}
				}

				// after filtering:
				// if the filtered list is empty, then we say that this clause is FALSE
				// else, this clause is TRUE
				clause_bool = (filter.size() > 0);

				// Add the filtered to ResultList!
				// 1. Add the synonym names to as column headers
				if (child1_type == QueryNodeType::synonym) {
					SYNONYM_NAME synonym_name = child1.getString();
					clause_result_list.addColumn(synonym_name);
				}
				if (child2_type == QueryNodeType::synonym) {
					SYNONYM_NAME synonym_name = child2.getString();
					clause_result_list.addColumn(synonym_name);
				}

				// 2. Add synonym values to the Resultlist row wise
				for (std::pair<int, int> p : filter) {
					ROW row;
					if (child1_type == QueryNodeType::synonym) {
						SYNONYM_NAME child1_synonym_name = child1.getString();
						SYNONYM_VALUE child1_synonym_value = std::to_string(p.first);
						row.insert({ child1_synonym_name, child1_synonym_value });
					}
					if (child2_type == QueryNodeType::synonym) {
						SYNONYM_NAME child2_synonym_name = child2.getString();
						SYNONYM_VALUE child2_synonym_value = std::to_string(p.second);
						row.insert({ child2_synonym_name, child2_synonym_value });
					}
					clause_result_list.addRow(row);
				}
			}
			else if (relationship_type == QueryNodeType::parent) {
				
				std::vector<int> list1 = getStmtList(child1);
				std::vector<int> list2 = getStmtList(child2);

				// create all possible pairs of list1 and list2 values
				std::vector<std::pair<int, int>> cross;
				for (int s1 : list1) {
					for (int s2 : list2) {
						cross.push_back({ s1, s2 });
					}
				}

				// filter the cross with PKB.isFollows
				std::vector<std::pair<int, int>> filter;
				for (std::pair<int, int> p : cross) {
					if (pkb.isParent(p.first, p.second)) {
						filter.push_back(p);
					}
				}

				// after filtering:
				// if the filtered list is empty, then we say that this clause is FALSE
				// else, this clause is TRUE
				clause_bool = (filter.size() > 0);

				// Add the filtered to ResultList!
				// 1. Add the synonym names to as column headers
				if (child1_type == QueryNodeType::synonym) {
					SYNONYM_NAME synonym_name = child1.getString();
					clause_result_list.addColumn(synonym_name);
				}
				if (child2_type == QueryNodeType::synonym) {
					SYNONYM_NAME synonym_name = child2.getString();
					clause_result_list.addColumn(synonym_name);
				}

				// 2. Add synonym values to the Resultlist row wise
				for (std::pair<int, int> p : filter) {
					ROW row;
					if (child1_type == QueryNodeType::synonym) {
						SYNONYM_NAME child1_synonym_name = child1.getString();
						SYNONYM_VALUE child1_synonym_value = std::to_string(p.first);
						row.insert({ child1_synonym_name, child1_synonym_value });
					}
					if (child2_type == QueryNodeType::synonym) {
						SYNONYM_NAME child2_synonym_name = child2.getString();
						SYNONYM_VALUE child2_synonym_value = std::to_string(p.second);
						row.insert({ child2_synonym_name, child2_synonym_value });
					}
					clause_result_list.addRow(row);
				}
			}
			else if (relationship_type == QueryNodeType::parentT) {
				
				std::vector<int> list1 = getStmtList(child1);
				std::vector<int> list2 = getStmtList(child2);

				// create all possible pairs of list1 and list2 values
				std::vector<std::pair<int, int>> cross;
				for (int s1 : list1) {
					for (int s2 : list2) {
						cross.push_back({ s1, s2 });
					}
				}

				// filter the cross with PKB.isFollows
				std::vector<std::pair<int, int>> filter;
				for (std::pair<int, int> p : cross) {
					if (pkb.isParentTransitive(p.first, p.second)) {
						filter.push_back(p);
					}
				}

				// after filtering:
				// if the filtered list is empty, then we say that this clause is FALSE
				// else, this clause is TRUE
				clause_bool = (filter.size() > 0);

				// Add the filtered to ResultList!
				// 1. Add the synonym names to as column headers
				if (child1_type == QueryNodeType::synonym) {
					SYNONYM_NAME synonym_name = child1.getString();
					clause_result_list.addColumn(synonym_name);
				}
				if (child2_type == QueryNodeType::synonym) {
					SYNONYM_NAME synonym_name = child2.getString();
					clause_result_list.addColumn(synonym_name);
				}

				// 2. Add synonym values to the Resultlist row wise
				for (std::pair<int, int> p : filter) {
					ROW row;
					if (child1_type == QueryNodeType::synonym) {
						SYNONYM_NAME child1_synonym_name = child1.getString();
						SYNONYM_VALUE child1_synonym_value = std::to_string(p.first);
						row.insert({ child1_synonym_name, child1_synonym_value });
					}
					if (child2_type == QueryNodeType::synonym) {
						SYNONYM_NAME child2_synonym_name = child2.getString();
						SYNONYM_VALUE child2_synonym_value = std::to_string(p.second);
						row.insert({ child2_synonym_name, child2_synonym_value });
					}
					clause_result_list.addRow(row);
				}
			}
			else if (relationship_type == QueryNodeType::usesS) {
				//std::vector<std::pair<int, std::string>> stmt_cross;
				//std::vector<std::pair<std::string, std::string>> proc_cross;
				std::vector<int> list1 = getStmtList(child1);
				std::vector<VAR_NAME> list2 = getVarNameList(child2);

				// create all possible pairs of list1 and list2 values
				std::vector<std::pair<int, VAR_NAME>> cross;
				for (int s1 : list1) {
					for (VAR_NAME s2 : list2) {
						cross.push_back({ s1, s2 });
					}
				}

				// filter the cross with PKB.isFollows
				std::vector<std::pair<int, VAR_NAME>> filter;
				for (std::pair<int, VAR_NAME> p : cross) {
					if (pkb.isUses(p.first, p.second)) {
						filter.push_back(p);
					}
				}

				// after filtering:
				// if the filtered list is empty, then we say that this clause is FALSE
				// else, this clause is TRUE
				clause_bool = (filter.size() > 0);

				// Add the filtered to ResultList!
				// 1. Add the synonym names to as column headers
				if (child1_type == QueryNodeType::synonym) {
					SYNONYM_NAME synonym_name = child1.getString();
					clause_result_list.addColumn(synonym_name);
				}
				if (child2_type == QueryNodeType::synonym) {
					SYNONYM_NAME synonym_name = child2.getString();
					clause_result_list.addColumn(synonym_name);
				}

				// 2. Add synonym values to the Resultlist row wise
				for (std::pair<int, VAR_NAME> p : filter) {
					ROW row;
					if (child1_type == QueryNodeType::synonym) {
						SYNONYM_NAME child1_synonym_name = child1.getString();
						SYNONYM_VALUE child1_synonym_value = std::to_string(p.first);
						row.insert({ child1_synonym_name, child1_synonym_value });
					}
					if (child2_type == QueryNodeType::synonym) {
						SYNONYM_NAME child2_synonym_name = child2.getString();
						SYNONYM_VALUE child2_synonym_value = p.second;
						row.insert({ child2_synonym_name, child2_synonym_value });
					}
					clause_result_list.addRow(row);
				}

			}
			//else if (relationship_type == QueryNodeType::usesP) {}
			else if (relationship_type == QueryNodeType::modifiesS) {
				std::vector<int> list1 = getStmtList(child1);
				std::vector<VAR_NAME> list2 = getVarNameList(child2);

				// create all possible pairs of list1 and list2 values
				std::vector<std::pair<int, VAR_NAME>> cross;
				for (int s1 : list1) {
					for (VAR_NAME s2 : list2) {
						cross.push_back({ s1, s2 });
					}
				}

				// filter the cross with PKB.isFollows
				std::vector<std::pair<int, VAR_NAME>> filter;
				for (std::pair<int, VAR_NAME> p : cross) {
					if (pkb.isModifies(p.first, p.second)) {
						filter.push_back(p);
					}
				}

				// after filtering:
				// if the filtered list is empty, then we say that this clause is FALSE
				// else, this clause is TRUE
				clause_bool = (filter.size() > 0);

				// Add the filtered to ResultList!
				// 1. Add the synonym names to as column headers
				if (child1_type == QueryNodeType::synonym) {
					SYNONYM_NAME synonym_name = child1.getString();
					clause_result_list.addColumn(synonym_name);
				}
				if (child2_type == QueryNodeType::synonym) {
					SYNONYM_NAME synonym_name = child2.getString();
					clause_result_list.addColumn(synonym_name);
				}

				// 2. Add synonym values to the Resultlist row wise
				for (std::pair<int, VAR_NAME> p : filter) {
					ROW row;
					if (child1_type == QueryNodeType::synonym) {
						SYNONYM_NAME child1_synonym_name = child1.getString();
						SYNONYM_VALUE child1_synonym_value = std::to_string(p.first);
						row.insert({ child1_synonym_name, child1_synonym_value });
					}
					if (child2_type == QueryNodeType::synonym) {
						SYNONYM_NAME child2_synonym_name = child2.getString();
						SYNONYM_VALUE child2_synonym_value = p.second;
						row.insert({ child2_synonym_name, child2_synonym_value });
					}
					clause_result_list.addRow(row);
				}
			}
			//else if (relationship_type == QueryNodeType::modifiesP) {}
		}
		else if (clause_type == QueryNodeType::pattern) {
			// magic
		}

		// if the clause_bool is true => merge result_list with clause_result_list
		// if the clause_bool is false => return ""
		if (clause_bool) {
			result_list = ResultListManager::merge(result_list, clause_result_list);
		}
		else {
			return no_result;
		}
	}

	// convert result_list to string output
	return ResultListManager::getSynonymValues(result_list, return_synonym_name);
}

STMT_NUM_LIST QueryEvaluator::getStmtList(QueryNode child1) {
	QueryNodeType child1_type = child1.getNodeType();
	
	if (child1_type == QueryNodeType::integer) {
		STMT_NUM_LIST oneIntList = { child1.getInteger() };
		return oneIntList;
	}
	else if (child1_type == QueryNodeType::synonym) {
		QuerySynonymType child1_syn_type = child1.getSynonymType();
		if (child1_syn_type == QuerySynonymType::assign) {
			return pkb.getAssignNumList();
		}
		// else if (child1_syn_type == QuerySynonymType::call) { for iteration 2
		else if (child1_syn_type == QuerySynonymType::ifs) {
			return pkb.getIfNumList();
		}
		else if (child1_syn_type == QuerySynonymType::print) {
			return pkb.getPrintNumList();
		}
		else if (child1_syn_type == QuerySynonymType::read) {
			return pkb.getReadNumList();
		}
		else if (child1_syn_type == QuerySynonymType::stmt) {
			return pkb.getStatementNumList();
		}
		else if (child1_syn_type == QuerySynonymType::whiles) {
			return pkb.getWhileNumList();
		}
		else {
			throw "QE: Synonym is not a statement or an integer!";
		}
	}
	else {
		throw "QE: Synonym is not a statement or an integer!";
	}
}

VAR_NAME_LIST QueryEvaluator::getVarNameList(QueryNode node) {
	if (node.getSynonymType() == QuerySynonymType::variable) {
		return pkb.getVariableNameList();
	}
}
