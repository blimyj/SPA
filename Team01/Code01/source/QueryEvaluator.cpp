﻿#include "QueryEvaluator.h"
#include <queue>

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
	for (size_t i = 1; i < children.size(); i++) {
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
				getFollowsResult(child1, child2, clause_bool, clause_result_list);
			}
			else if (relationship_type == QueryNodeType::followsT) {
				getFollowsTResult(child1, child2, clause_bool, clause_result_list);
			}
			else if (relationship_type == QueryNodeType::parent) {
				getParentResult(child1, child2, clause_bool, clause_result_list);
			}
			else if (relationship_type == QueryNodeType::parentT) {
				getParentTResult(child1, child2, clause_bool, clause_result_list);
			}
			else if (relationship_type == QueryNodeType::usesS) {
				//std::vector<std::pair<int, std::string>> stmt_cross;
				//std::vector<std::pair<std::string, std::string>> proc_cross;
				if (child1.getSynonymType() != QuerySynonymType::procedure) {
					getUsesSResult(child1, child2, clause_bool, clause_result_list);
				}
				else {
					getUsesPResult(child1, child2, clause_bool, clause_result_list);
				}

			}
			//else if (relationship_type == QueryNodeType::usesP) {}
			else if (relationship_type == QueryNodeType::modifiesS) {
				if (child1.getSynonymType() != QuerySynonymType::procedure) {
					getModifiesSResult(child1, child2, clause_bool, clause_result_list);
				}
				else {
					getModifiesPResult(child1, child2, clause_bool, clause_result_list);
				}
			}
			//else if (relationship_type == QueryNodeType::modifiesP) {}
		}
		else if (clause_type == QueryNodeType::pattern) {
			// magic
			// Only 1 node on the LHS and search for only 1 node on the RHS (Iteration 1)
			// Depends on whether the pattern is searchign for a constant or a variable (eg x = 3 or x = v )
			// Example pattern a(_, _"x"_) a(_, _"4"_) a("w", _"x"_) a("i", _"x"_) a("mango", _"x"_ ) a("mango", _"4"_)
			
			// idea for RHS variable:
				//get assign nodes, get their stmt numbers, check isUses(stmtnum, RHS thing eg 3/v)
				//if LHS is not wildcard, then check isModifies(stmtNum, v)
			// for constants:
				// find all the constant nodes, for each node, go up and find a stmt node (while if print read assign )
				// if not assign:
					//end
				// else:
					// for the assign node stmtNum, check isModifies(stmtNum, v)
			
			// RHS also has _ too :( yep then omg wait lemmme think
			// ><

			
			// a (_, _)
			QueryNode pattern = clause;
			QueryNode child1 = pattern.getChildren()[0];
			QueryNode child2 = pattern.getChildren()[1];
			QueryNode child3 = pattern.getChildren()[2];
			AST_NODE child3_ast = child3.getAstNode();
			
			QueryNodeType child2_type = child2.getNodeType();
			QueryNodeType child3_type = child3.getNodeType();
			
			SYNONYM_NAME assign_synonym_name = child1.getString();

			// ResultList only contains the assign synonym
			// a1
			// 1
			// 2
			// 5
			// ...
			clause_result_list.addColumn(assign_synonym_name);
		
			// pattern a (v, _)
			// add LHS search strings into lhs_set
			std::unordered_set<VAR_NAME> lhs_set;

			// if qpp_lhs is ident, add exact to lhs_set
			if (child2_type == QueryNodeType::ident) {
				STRING child2_content = child2.getString();
				lhs_set.insert(child2_content);

			// if qpp_lhs is synonym, add all synonym to lhs_set
			} else if (child2_type == QueryNodeType::synonym) {
				STRING child2_content = child2.getString();
				QueryNode node = synonyms.find(child2_content)->second;
				QuerySynonymType node_type = node.getSynonymType();
				if (node_type == QuerySynonymType::variable) {
					std::vector<SYNONYM_NAME> var_names = pkb.getVariableNameList();
					for (SYNONYM_NAME var_name : var_names) {
						lhs_set.insert(var_name);
					}
				} //check if other synonyms are valid
			
			// if qpp_lhs is wildcard, add all variables to lhs_set
			} else if (child2_type == QueryNodeType::wild_card) {
				for (VAR_NAME name : pkb.getVariableNameList()) {
					lhs_set.insert(name);
				}
			}
			
			// Iterate through all assign nodes
			std::vector<ASSIGN_NODE_PTR> pkb_assigns = pkb.getAssigns();
			for (ASSIGN_NODE_PTR assign_node : pkb_assigns) {
				std::string stmt_num = std::to_string(assign_node->getStatementNumber());
				VAR_NODE_PTR lhs_node = assign_node->getVariableNode();
				EXPR_NODE_PTR rhs_node = assign_node->getExpressionNode();

				// if lhs name is not in qpp_lhs_set, skip this assign node
				if (lhs_set.count(lhs_node->getVariableName()) == 0) {
					continue;
				}

				// if qpp_rhs is a wildcard, add to ResultList
				if (child3_type == QueryNodeType::wild_card) {
					ROW row;
					row.insert({ assign_synonym_name, stmt_num });
					clause_result_list.addRow(row);
				}
				else if (child3_type == QueryNodeType::expression) {
					// if qpp_rhs is a partial match, find in AST (rhs)
					// if found, add to ResultList 
					AST_NODE_PTR child3_ast = child3.getAstNode();
					NODE_TYPE child3_ast_type = child3_ast->getNodeType();

					// the string to search for in the AST
					std::string search_name;
					if (child3_ast_type == NodeTypeEnum::constantNode) {
						CONSTANT_NODE_PTR node = std::static_pointer_cast<ConstantNode>(child3_ast);
						search_name = node->getValue();
					} else if (child3_ast_type == NodeTypeEnum::variableNode) {
						VAR_NODE_PTR node = std::static_pointer_cast<VariableNode>(child3_ast);
						search_name = node->getVariableName();
					}

					bool match = findPartialPattern(rhs_node, search_name);

					// Pattern found, add to ResultList!
					if (match) {
						ROW row;
						row.insert({ assign_synonym_name, stmt_num });
						clause_result_list.addRow(row);
					}
				}
			}
			
			// if result_list is empty, clause_bool = false
			// Return a ResultList of assign synonyms
			clause_bool = (clause_result_list.getNumRows() > 0);
		}
			
			// Eg pattern a1("woof", _"x"_)
			//clause_bool = false;
			//ResultList clause_result_list;
			//ResultList initial_assign_list;
			//std::vector<ASSIGN_NODE_PTR> all_assigns = pkb.getAssigns();

			//// QueryNodeContent -> a1
			//QueryNode pattern_assign_synonym = clause.getChildren()[0];
			//// add column head a1
			//SYNONYM_NAME synonym_name = pattern_assign_synonym.getString();
			//clause_result_list.addColumn(synonym_name);
			//initial_assign_list.addColumn(synonym_name, pkb.getAssignNumList());

			//// QueryNodeContent -> "woof"
			//QueryNode lhs_node = clause.getChildren()[1];
			//STRING lhs = lhs_node.getString();
			//auto lhs_node_type = lhs_node.getNodeType();
			
			//// ASTNode -> "x"
			//QueryNode rhs_node = clause.getChildren()[2];
			//std::shared_ptr<ASTNode> rhs = (rhs_node.getAstNode());
			//NODE_TYPE rhs_node_type = rhs.get()->getNodeType();
			

			///* Ways to cast ASTNode to more specific nodes (use for VariableNode and ConstantNode)
			//AssignNode* assign = static_cast<AssignNode*>(rhs_node_content.get());
			//auto a = assign->getExpressionNode();

			//VariableNode* assign = static_cast<VariableNode*>(rhs_node_content.get());
			//*/
			
			
			//if (rhs_node_type == NodeTypeEnum::variableNode) {
			//	if (lhs_node_type == QueryNodeType::synonym) { //ie lhs == QueryNodeType::ident || lhs == QueryNodeType::synonym
			//		// pattern a(synonym/'IDENT', v)
			//		// check isModifies(synonym/'IDENT', v) && isUses(synonym/'IDENT', v)
			//		// if true:
			//			// somehow find the stmtNum, add to clause_result_list
					
			//	}
			//	else if (lhs_node_type == QueryNodeType::ident) { // ok!!oo I hope my logic makes sense >< ohh i havent read yet i was writing mine in the if else AHAHAHA okk lemme read
			//		// get VarNodeTable
			//		// find IDENT variable in VarNodeTable
			//		// with the VarNode, getParent() to get the direct parent which is an AssignNode
			//		// AssignNode get the stmtNum
			//		// with the stmtNum check isModifies(stmtNum, v) && isUses(stmtNum, v)

			//	}
			//	else if (lhs_node_type == QueryNodeType::wild_card) {
			//		// pattern a(_, _"v"_ )
			//		// for all stmt in stmts:
			//			// check isUses(stmt, v)

			//	}
			//	else {
			//		throw "QE Pattern lhs argument is not synonym, IDENT, wild card -- INVALID";
			//	}
			//}
			//else if (rhs_node_type == NodeTypeEnum::constantNode) {
			//	// search up until we hit assignNode
			//	// get AssignNode stmtNum 
			//	// ohh you don't want to traverse the AST? I see! ohh i thought it would be quite hard to do that maybe when im more familiar with ASTNode then i try? but now im manually checking
			//	// ohh this one looks scary it's like traversing the AST ohh>< LOL YEAH yeahhhh maybe can practice traversing heree im worried AHAHAHAHA
			//	// i can try writing some code to traverse the assign node! ohhh okay! 
			//}
			//else if (rhs_node.getNodeType() == QueryNodeType::wild_card) {
			//	if (lhs_node_type == QueryNodeType::wild_card) {
			//		// pattern a(_, _)
			//		// return all assign statements

			//	}
			//	else if (lhs_node_type == QueryNodeType::synonym) {
			//		// pattern a(v, _)

			//	}
			//	else if (lhs_node_type == QueryNodeType::ident) {
			//		// pattern a("mango", _)

			//	}
			//	else {
			//		throw "QE Pattern lhs argument is not synonym, IDENT, wild card -- INVALID";
			//	}
			//}
			//else {
			//	throw "QE Pattern rhs argument is not variable or constant --  INVALID";
			//}

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



void QueryEvaluator::getFollowsResult(QueryNode child1, QueryNode child2, bool &clause_bool, ResultList &clause_result_list) {
	/* Follows(s1, s2)
		s1 = [1, 2, 3] if assign
		s2 = [1, 2, 3]
		cross = [[1,1], [1,2], [1,3]...]

		filter the cross with PKB

		then add to ResultList
	*/

	// Initialize with list of all values for the given synonym
	QueryNodeType child1_type = child1.getNodeType();
	QueryNodeType child2_type = child2.getNodeType();

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

void QueryEvaluator::getFollowsTResult(QueryNode child1, QueryNode child2, bool& clause_bool, ResultList& clause_result_list) {
	QueryNodeType child1_type = child1.getNodeType();
	QueryNodeType child2_type = child2.getNodeType();

	std::vector<int> list1 = getStmtList(child1);
	std::vector<int> list2 = getStmtList(child2);

	// create all possible pairs of list1 and list2 values
	std::vector<std::pair<int, int>> cross;
	for (int s1 : list1) {
		for (int s2 : list2) {
			cross.push_back({ s1, s2 });
		}
	}

	// filter the cross with PKB.isFollowsTransitive
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

void QueryEvaluator::getParentResult(QueryNode child1, QueryNode child2, bool& clause_bool, ResultList& clause_result_list) {
	QueryNodeType child1_type = child1.getNodeType();
	QueryNodeType child2_type = child2.getNodeType();


	std::vector<int> list1 = getStmtList(child1);
	std::vector<int> list2 = getStmtList(child2);

	// create all possible pairs of list1 and list2 values
	std::vector<std::pair<int, int>> cross;
	for (int s1 : list1) {
		for (int s2 : list2) {
			cross.push_back({ s1, s2 });
		}
	}

	// filter the cross with PKB.isParent
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

void QueryEvaluator::getParentTResult(QueryNode child1, QueryNode child2, bool& clause_bool, ResultList& clause_result_list) {
	QueryNodeType child1_type = child1.getNodeType();
	QueryNodeType child2_type = child2.getNodeType();

	std::vector<int> list1 = getStmtList(child1);
	std::vector<int> list2 = getStmtList(child2);

	// create all possible pairs of list1 and list2 values
	std::vector<std::pair<int, int>> cross;
	for (int s1 : list1) {
		for (int s2 : list2) {
			cross.push_back({ s1, s2 });
		}
	}

	// filter the cross with PKB.isParentTransitive
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

void QueryEvaluator::getUsesSResult(QueryNode child1, QueryNode child2, bool& clause_bool, ResultList& clause_result_list) {
	QueryNodeType child1_type = child1.getNodeType();
	QueryNodeType child2_type = child2.getNodeType();

	std::vector<int> list1 = getStmtList(child1);
	std::vector<VAR_NAME> list2 = getVarNameList(child2);

	// create all possible pairs of list1 and list2 values
	std::vector<std::pair<int, VAR_NAME>> cross;
	for (int s1 : list1) {
		for (VAR_NAME s2 : list2) {
			cross.push_back({ s1, s2 });
		}
	}

	// filter the cross with PKB.isUses
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

void QueryEvaluator::getUsesPResult(QueryNode child1, QueryNode child2, bool& clause_bool, ResultList& clause_result_list) {
	QueryNodeType child1_type = child1.getNodeType();
	QueryNodeType child2_type = child2.getNodeType();

	// Iteration 1: procedure list only have 1 procedure
	// Approach: get all the stmts of that procedure, ignore all other procedures
	// Check isUses(stmt, v) as per normal
	std::vector<PROC_NAME> list1 = getProcList(child1);
	std::vector<VAR_NAME> list2 = getVarNameList(child2);

	// create all possible pairs of list1 and list2 values
	std::vector<std::pair<PROC_NAME, VAR_NAME>> cross;
	for (PROC_NAME s1 : list1) {
		for (VAR_NAME s2 : list2) {
			cross.push_back({ s1, s2 });
		}
	}

	// filter the cross with PKB.isFollows
	std::vector<std::pair<PROC_NAME, VAR_NAME>> filter;
	for (std::pair<PROC_NAME, VAR_NAME> p : cross) {
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
	for (std::pair<std::string, VAR_NAME> p : filter) {
		ROW row;
		if (child1_type == QueryNodeType::synonym) {
			SYNONYM_NAME child1_synonym_name = child1.getString();
			SYNONYM_VALUE child1_synonym_value = p.first;
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

void QueryEvaluator::getModifiesSResult(QueryNode child1, QueryNode child2, bool& clause_bool, ResultList& clause_result_list) {
	QueryNodeType child1_type = child1.getNodeType();
	QueryNodeType child2_type = child2.getNodeType();

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

void QueryEvaluator::getModifiesPResult(QueryNode child1, QueryNode child2, bool& clause_bool, ResultList& clause_result_list) {
	QueryNodeType child1_type = child1.getNodeType();
	QueryNodeType child2_type = child2.getNodeType();

	std::vector<PROC_NAME> list1 = getProcList(child1);
	std::vector<VAR_NAME> list2 = getVarNameList(child2);

	// create all possible pairs of list1 and list2 values
	std::vector<std::pair<PROC_NAME, VAR_NAME>> cross;
	for (PROC_NAME s1 : list1) {
		for (VAR_NAME s2 : list2) {
			cross.push_back({ s1, s2 });
		}
	}

	// filter the cross with PKB.isFollows
	std::vector<std::pair<PROC_NAME, VAR_NAME>> filter;
	for (std::pair<PROC_NAME, VAR_NAME> p : cross) {
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
	for (std::pair<std::string, VAR_NAME> p : filter) {
		ROW row;
		if (child1_type == QueryNodeType::synonym) {
			SYNONYM_NAME child1_synonym_name = child1.getString();
			SYNONYM_VALUE child1_synonym_value = p.first;
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

STMT_NUM_LIST QueryEvaluator::getStmtList(QueryNode child1) {
	QueryNodeType child1_type = child1.getNodeType();

	if (child1_type == QueryNodeType::integer) {
		STMT_NUM_LIST oneIntList = { child1.getInteger() };
		return oneIntList;
		//return STMT_NUM_LIST(chilld1.getInteger())
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
	else {
		throw "QE: node is not a variable, getVarNameList requires a variable node";
	}
}

PROC_NAME_LIST QueryEvaluator::getProcList(QueryNode node) {
	if (node.getSynonymType() == QuerySynonymType::procedure) {
		return pkb.getProcedureNameList();
	}
	else {
		throw "QE: node is not a procedure, getProcList requires a procedure node";
	}
}

bool QueryEvaluator::findPartialPattern(AST_NODE_PTR ast, std::string search_name) {
	// BFS
	std::queue<AST_NODE_PTR> queue;
	queue.push(ast);

	while (!queue.empty()) {
		AST_NODE_PTR node = queue.front();
		queue.pop();
						
		NODE_TYPE node_type = node->getNodeType();
		if (node_type == NodeTypeEnum::constantNode) {
			CONSTANT_NODE_PTR node = std::static_pointer_cast<ConstantNode>(node);
			VALUE node_name = node->getValue();
			if (node_name == search_name) {
				return true;
			}
		} else if (node_type == NodeTypeEnum::expressionNode) {
			EXPR_NODE_PTR node = std::static_pointer_cast<ExpressionNode>(node);
			for (AST_NODE_PTR child : node->getChildrenNode()) {
				queue.push(child);
			}
		} else if (node_type == NodeTypeEnum::variableNode) {
			VAR_NODE_PTR node = std::static_pointer_cast<VariableNode>(node);
			VAR_NAME node_name = node->getVariableName();
			if (node_name == search_name) {
				return true;
			}
		}
	}

	return false;
}