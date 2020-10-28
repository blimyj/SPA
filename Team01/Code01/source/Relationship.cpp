#include "Relationship.h"

Relationship::Relationship(QueryNodeType relationship_type, QueryNode child1, QueryNode child2) {
	this->child1 = child1;
	this->child2 = child2;
	this->relationship_type = relationship_type;
}

void Relationship::getRelationshipResult(PKB pkb, bool& clause_bool, ResultList& clause_result_list) {
	if (relationship_type == QueryNodeType::follows) {
		getFollowsResult(pkb, clause_bool, clause_result_list);
	}
	else if (relationship_type == QueryNodeType::followsT) {
		getFollowsTResult(pkb, clause_bool, clause_result_list);
	}
	else if (relationship_type == QueryNodeType::parent) {
		getParentResult(pkb, clause_bool, clause_result_list);
	}
	else if (relationship_type == QueryNodeType::parentT) {
		getParentTResult(pkb, clause_bool, clause_result_list);
	}
	else if (relationship_type == QueryNodeType::usesS) {
		getUsesSResult(pkb, clause_bool, clause_result_list);
	}
	else if (relationship_type == QueryNodeType::usesP) {
		getUsesPResult(pkb, clause_bool, clause_result_list);
	}
	else if (relationship_type == QueryNodeType::modifiesS) {
		getModifiesSResult(pkb, clause_bool, clause_result_list);
	}
	else if (relationship_type == QueryNodeType::modifiesP) {
		getModifiesPResult(pkb, clause_bool, clause_result_list);
	}
	else if (relationship_type == QueryNodeType::calls) {
		getCallsResult(pkb, clause_bool, clause_result_list);
	}
	else if (relationship_type == QueryNodeType::callsT) {
		getCallsTResult(pkb, clause_bool, clause_result_list);
	}
	else if (relationship_type == QueryNodeType::next) {
		getNextResult(pkb, clause_bool, clause_result_list);
	}
	else if (relationship_type == QueryNodeType::nextT) {
		getNextTResult(pkb, clause_bool, clause_result_list);
	}
	else if (relationship_type == QueryNodeType::affects) {
		
	}
	else if (relationship_type == QueryNodeType::affectsT) {

	}
	else {
		throw "QE: Relationship: Relationship given is not valid.";
	}
}

void Relationship::getFollowsResult(PKB pkb, bool& clause_bool, ResultList& clause_result_list) {
	/* 
	Format: Follows( stmtRef, stmtRef )
	Relationship between: Statements
	
	Follows(s1, s2)
	s1 = [1, 2, 3] if assign
	s2 = [1, 2, 3]
	cross = [[1,1], [1,2], [1,3]...]

	filter the cross with PKB

	then add to ResultList
	*/

	// Initialize with list of all values for the given synonym
	QueryNodeType child1_type = child1.getNodeType();
	QueryNodeType child2_type = child2.getNodeType();

	if (isSameSynonymName(child1, child2)) {
		return;
	}

	std::vector<int> list1;
	std::vector<int> list2;

	try {
		list1 = getStmtList(pkb, child1);

		list2 = getStmtList(pkb, child2);
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

void Relationship::getFollowsTResult(PKB pkb, bool& clause_bool, ResultList& clause_result_list) {
	/*
	Format: FollowsT( stmtRef, stmtRef )
	Relationship between: Statements
	*/

	QueryNodeType child1_type = child1.getNodeType();
	QueryNodeType child2_type = child2.getNodeType();

	if (isSameSynonymName(child1, child2)) {
		return;
	}

	std::vector<int> list1 = getStmtList(pkb, child1);
	std::vector<int> list2 = getStmtList(pkb, child2);

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

void Relationship::getParentResult(PKB pkb, bool& clause_bool, ResultList& clause_result_list) {
	/*
	Format: Parent( stmtRef, stmtRef )
	Relationship between: Statements
	*/

	QueryNodeType child1_type = child1.getNodeType();
	QueryNodeType child2_type = child2.getNodeType();

	if (isSameSynonymName(child1, child2)) {
		return;
	}

	std::vector<int> list1 = getStmtList(pkb, child1);
	std::vector<int> list2 = getStmtList(pkb, child2);

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

void Relationship::getParentTResult(PKB pkb, bool& clause_bool, ResultList& clause_result_list) {
	/*
	Format: ParentT( stmtRef, stmtRef )
	Relationship between: Statements
	*/

	QueryNodeType child1_type = child1.getNodeType();
	QueryNodeType child2_type = child2.getNodeType();

	if (isSameSynonymName(child1, child2)) {
		return;
	}

	std::vector<int> list1 = getStmtList(pkb, child1);
	std::vector<int> list2 = getStmtList(pkb, child2);

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

void Relationship::getUsesSResult(PKB pkb, bool& clause_bool, ResultList& clause_result_list) {
	/*
	Format: Uses(stmtRef, entRef)
	Relationship between: Statements/Procedure/Variables

	stmtRef: synonym | INTEGER
	entRef: synonym | _ | IDENT (synonym can only be v, wildcard is just all v)

	Possible Combinations:
	1. Uses(synonym, synonym)		-> eg UsesS(pn, v)
	2. Uses(INTEGER, synonym)		-> eg UsesS(5, v)
	3. Uses(synonym, IDENT)			-> eg UsesS(w, "woof")
	4. Uses(synonym, _)				-> eg UsesS(ifs, _)
	5. Uses(INTEGER, IDENT)			-> eg UsesS(5, "woof")
	6. Uses(INTEGER, _)				-> eg UsesS(5, _)
	*/

	QueryNodeType child1_type = child1.getNodeType();
	QueryNodeType child2_type = child2.getNodeType();

	// Populate list1 with stmtRef values
	std::vector<int> list1;
	if (child1_type == QueryNodeType::wild_card) {
		throw "QE: First argument of Uses cannot be a wildcard!";
	}
	else {
		list1 = getStmtList(pkb, child1);
	}

	// Populate list2 with entRef values
	/*
		if IDENT: add IDENT string to the list
		if SYNONYM: add all values of SYNONYM v to the list
		if WILDCARD: add all v to the list
	*/
	std::vector<VAR_NAME> list2;
	if (child2_type == QueryNodeType::ident) {
		list2.push_back(child2.getString());
	}
	else if (child2_type == QueryNodeType::synonym) {
		list2 = getVarNameList(pkb, child2);
	}
	else if (child2_type == QueryNodeType::wild_card) {
		list2 = pkb.getVariableNameList();
	}
	else {
		throw "QE: Second argument of UsesS should be SYNONYM or IDENT or WILDCARD";
	}

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

void Relationship::getUsesPResult(PKB pkb, bool& clause_bool, ResultList& clause_result_list) {
	/*
	Format: UsesP( entRef1, entRef2)
	Relationship between: Statements/Procedure/Variables

	entRef1: synonym | IDENT  (semantically invalid to have �_� as the first argument for Modifies and Uses: unclear whether �_� stands for a statement or a procedure.)
	entRef2: synonym | _ | IDENT (synonym can only be v, wildcard is just all v)

	Possible Combinations:
	1. UsesP(synonym, synonym)		-> eg UsesP(p1, v)
	2. UsesP(synonym, _)			-> eg UsesP(p1, _)
	3. UsesP(synonym, IDENT)		-> eg UsesP(p1, "woof")
	4. UsesP(IDENT, synonym)		-> eg UsesP("main", v)
	5. UsesP(IDENT, _)				-> eg UsesP("main", _)
	6. UsesP(IDENT, IDENT)			-> eg UsesP("main", "woof")
	*/

	QueryNodeType child1_type = child1.getNodeType();
	QueryNodeType child2_type = child2.getNodeType();


	// Populate list1 with child1 values
	std::vector<PROC_NAME> list1;
	if (child1_type == QueryNodeType::ident) {
		list1.push_back(child1.getString());
	}
	else if (child1_type == QueryNodeType::synonym) {
		list1 = getProcList(pkb, child1);
	}
	else {
		throw "QE: First argument of UsesP should be SYNONYM or IDENT";
	}

	// Populate list2 with child2 values
	std::vector<VAR_NAME> list2;
	if (child2_type == QueryNodeType::ident) {
		list2.push_back(child2.getString());
	}
	else if (child2_type == QueryNodeType::synonym) {
		list2 = getVarNameList(pkb, child2);
	}
	else if (child2_type == QueryNodeType::wild_card) {
		list2 = pkb.getVariableNameList();
	}
	else {
		throw "QE: Second argument of UsesP should be SYNONYM or IDENT or WILDCARD";
	}

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

void Relationship::getModifiesSResult(PKB pkb, bool& clause_bool, ResultList& clause_result_list) {
	/*
	Format: Modifies(stmtRef, entRef)
	Relationship between: Statements/Procedure/Variables

	stmtRef: synonym | INTEGER
	entRef: synonym | _ | IDENT (synonym can only be v, wildcard is just all v)

	Possible Combinations:
	1. Modifies(synonym, synonym)
	2. Modifies(INTEGER, synonym)
	3. Modifies(synonym, IDENT)
	4. Modifies(synonym, _)
	5. Modifies(INTEGER, IDENT)
	6. Modifies(INTEGER, _)
	*/

	QueryNodeType child1_type = child1.getNodeType();
	QueryNodeType child2_type = child2.getNodeType();

	// Populate list1 with child1 values
	std::vector<int> list1;
	if (child1_type == QueryNodeType::wild_card) {
		throw "QE: First argument of Uses cannot be a wildcard!";
	}
	else {
		list1 = getStmtList(pkb, child1);
	}

	// Populate list2 with child2 values
	/*
		if IDENT: add IDENT string to the list
		if SYNONYM: add all values of SYNONYM v to the list
		if WILDCARD: add all v to the list
	*/
	std::vector<VAR_NAME> list2;
	if (child2_type == QueryNodeType::ident) {
		list2.push_back(child2.getString());
	}
	else if (child2_type == QueryNodeType::synonym) {
		list2 = getVarNameList(pkb, child2);
	}
	else if (child2_type == QueryNodeType::wild_card) {
		list2 = pkb.getVariableNameList();
	}
	else {
		throw "QE: Second argument of ModifiesS should be SYNONYM or IDENT or WILDCARD";
	}

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

void Relationship::getModifiesPResult(PKB pkb, bool& clause_bool, ResultList& clause_result_list) {
	/*
	Format: ModifiesP ( entRef1, entRef2)
	Relationship between: Statements/Procedure/Variables

	entRef1: synonym | IDENT  (semantically invalid to have �_� as the first argument for Modifies and Uses: unclear whether �_� stands for a statement or a procedure.)
	entRef2: synonym | _ | IDENT (synonym can only be v, wildcard is just all v)

	Possible Combinations:
	1. ModifiesP(synonym, synonym)		-> eg ModifiesP(p1, v)
	2. ModifiesP(synonym, _)			-> eg ModifiesP(p1, _)
	3. ModifiesP(synonym, IDENT)		-> eg ModifiesP(p1, "woof")
	4. ModifiesP(IDENT, synonym)		-> eg ModifiesP("main", v)
	5. ModifiesP(IDENT, _)				-> eg ModifiesP("main", _)
	6. ModifiesP(IDENT, IDENT)			-> eg ModifiesP("main", "woof")
	*/

	QueryNodeType child1_type = child1.getNodeType();
	QueryNodeType child2_type = child2.getNodeType();

	// Populate list1 with child1 values
	std::vector<PROC_NAME> list1;
	if (child1_type == QueryNodeType::ident) {
		list1.push_back(child1.getString());
	}
	else if (child1_type == QueryNodeType::synonym) {
		list1 = getProcList(pkb, child1);
	}
	else {
		throw "QE: First argument of ModifiesP should be SYNONYM or IDENT";
	}

	// Populate list2 with child2 values
	std::vector<VAR_NAME> list2;
	if (child2_type == QueryNodeType::ident) {
		list2.push_back(child2.getString());
	}
	else if (child2_type == QueryNodeType::synonym) {
		list2 = getVarNameList(pkb, child2);
	}
	else if (child2_type == QueryNodeType::wild_card) {
		list2 = pkb.getVariableNameList();
	}
	else {
		throw "QE: Second argument of ModifesP should be SYNONYM or IDENT or WILDCARD";
	}

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

void Relationship::getCallsResult(PKB pkb, bool& clause_bool, ResultList& clause_result_list) {
	/*
	Format: Calls( entRef, entRef)
	Relationship between: Procedures

	entRef: synonym | _ | IDENT

		synonym: procedure
		_ : all procedures
		IDENT: procedure name

	Possible Combinations:
	1. Calls(synonym, synonym)			-> Calls(p1, p2)
	2. Calls(synonym, _)				-> Calls(p, _)
	3. Calls(synonym, IDENT)			-> Calls(p, "main")
	4. Calls(_, synonym)				-> Calls(_, p)
	5. Calls(_, _)						-> Calls(_, _)
	6. Calls(_, IDENT)					-> Calls(_, "main")
	7. Calls(IDENT, synonym)			-> Calls("main", p)
	8. Calls(IDENT, _)					-> Calls("main", _)
	9. Calls(IDENT, IDENT)				-> Calls("main", "woof")
	*/

	QueryNodeType child1_type = child1.getNodeType();
	QueryNodeType child2_type = child2.getNodeType();

	// Populate list1 with child1 values
	std::vector<PROC_NAME> list1;
	if (child1_type == QueryNodeType::ident) {
		list1.push_back(child1.getString());
	}
	else if (child1_type == QueryNodeType::synonym) {
		list1 = getProcList(pkb, child1);
	}
	else if (child1_type == QueryNodeType::wild_card) {
		list1 = getProcList(pkb, child1);
	}
	else {
		throw "QE: First argument of Calls should be SYNONYM or IDENT or WILDCARD";
	}

	// Populate list2 with child2 values
	std::vector<PROC_NAME> list2;
	if (child2_type == QueryNodeType::ident) {
		list2.push_back(child2.getString());
	}
	else if (child2_type == QueryNodeType::synonym) {
		list2 = getProcList(pkb, child2);
	}
	else if (child2_type == QueryNodeType::wild_card) {
		list2 = getProcList(pkb, child2);
	}
	else {
		throw "QE: Second argument of Calls should be SYNONYM or IDENT or WILDCARD";
	}

	// create all possible pairs of list1 and list2 values
	std::vector<std::pair<PROC_NAME, PROC_NAME>> cross;
	for (PROC_NAME s1 : list1) {
		for (PROC_NAME s2 : list2) {
			cross.push_back({ s1, s2 });
		}
	}

	// filter the cross with PKB.isFollows
	std::vector<std::pair<PROC_NAME, PROC_NAME>> filter;
	for (std::pair<PROC_NAME, PROC_NAME> p : cross) {
		if (pkb.isCalls(p.first, p.second)) {
			filter.push_back(p);
		}
	}

	// after filtering:
	// if the filtered list is empty, then we say that this clause is FALSE
	// else, this clause is TRUE
	clause_bool = (filter.size() > 0);

	// Add the filtered to ResultList!
	// 1. Add the synonym names as column headers
	if (child1_type == QueryNodeType::synonym) {
		SYNONYM_NAME synonym_name = child1.getString();
		clause_result_list.addColumn(synonym_name);
	}
	if (child2_type == QueryNodeType::synonym) {
		SYNONYM_NAME synonym_name = child2.getString();
		clause_result_list.addColumn(synonym_name);
	}

	// 2. Add synonym values to the Resultlist row wise
	for (std::pair<PROC_NAME, PROC_NAME> p : filter) {
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

void Relationship::getCallsTResult(PKB pkb, bool& clause_bool, ResultList& clause_result_list) {
	/*
	Format: CallsT( entRef, entRef)
	Relationship between: Procedures

	entRef: synonym | _ | IDENT

		synonym: procedure
		_ : all procedures
		IDENT: procedure name

	Possible Combinations:
	1. CallsT(synonym, synonym)			-> CallsT(p1, p2)
	2. CallsT(synonym, _)				-> CallsT(p, _)
	3. CallsT(synonym, IDENT)			-> CallsT(p, "main")
	4. CallsT(_, synonym)				-> CallsT(_, p)
	5. CallsT(_, _)						-> CallsT(_, _)
	6. CallsT(_, IDENT)					-> CallsT(_, "main")
	7. CallsT(IDENT, synonym)			-> CallsT("main", p)
	8. CallsT(IDENT, _)					-> CallsT("main", _)
	9. CallsT(IDENT, IDENT)				-> CallsT("main", "woof")
	*/

	QueryNodeType child1_type = child1.getNodeType();
	QueryNodeType child2_type = child2.getNodeType();

	// Populate list1 with child1 values
	std::vector<PROC_NAME> list1;
	if (child1_type == QueryNodeType::ident) {
		list1.push_back(child1.getString());
	}
	else if (child1_type == QueryNodeType::synonym) {
		list1 = getProcList(pkb, child1);
	}
	else if (child1_type == QueryNodeType::wild_card) {
		list1 = getProcList(pkb, child1);
	}
	else {
		throw "QE: First argument of Calls should be SYNONYM or IDENT or WILDCARD";
	}

	// Populate list2 with child2 values
	std::vector<PROC_NAME> list2;
	if (child2_type == QueryNodeType::ident) {
		list2.push_back(child2.getString());
	}
	else if (child2_type == QueryNodeType::synonym) {
		list2 = getProcList(pkb, child2);
	}
	else if (child2_type == QueryNodeType::wild_card) {
		list2 = getProcList(pkb, child2);
	}
	else {
		throw "QE: Second argument of Calls should be SYNONYM or IDENT or WILDCARD";
	}

	// create all possible pairs of list1 and list2 values
	std::vector<std::pair<PROC_NAME, PROC_NAME>> cross;
	for (PROC_NAME s1 : list1) {
		for (PROC_NAME s2 : list2) {
			cross.push_back({ s1, s2 });
		}
	}

	// filter the cross with PKB.isFollows
	std::vector<std::pair<PROC_NAME, PROC_NAME>> filter;
	for (std::pair<PROC_NAME, PROC_NAME> p : cross) {
		if (pkb.isCallsTransitive(p.first, p.second)) {
			filter.push_back(p);
		}
	}

	// after filtering:
	// if the filtered list is empty, then we say that this clause is FALSE
	// else, this clause is TRUE
	clause_bool = (filter.size() > 0);

	// Add the filtered to ResultList!
	// 1. Add the synonym names as column headers
	if (child1_type == QueryNodeType::synonym) {
		SYNONYM_NAME synonym_name = child1.getString();
		clause_result_list.addColumn(synonym_name);
	}
	if (child2_type == QueryNodeType::synonym) {
		SYNONYM_NAME synonym_name = child2.getString();
		clause_result_list.addColumn(synonym_name);
	}

	// 2. Add synonym values to the Resultlist row wise
	for (std::pair<PROC_NAME, PROC_NAME> p : filter) {
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

void Relationship::getNextResult(PKB pkb, bool& clause_bool, ResultList& clause_result_list) {
	/*
	Format: Next( lineRef, lineRef )
	Relationship between: Program Lines
	Note: Synonyms of stmt, assign, call, read, print, while and if can appear in place of program lines (and vice-versa). Statement numbers are then interpreted as program lines.

	lineRef: synonym | _ | INTEGER
		
		synonym: prog_line | stmt | assign | call | read | print | while | if
		_: stmt_num_list
		INTEGER: stmt line number 

	Possible Combinations:
	1. Next(synonym, synonym)			-> Next(a, r)
	2. Next(synonym, _)					-> Next(n, _)
	3. Next(synonym, INTEGER)			-> Next(n, 10)
	4. Next(_, synonym)					-> Next(_, n)
	5. Next(_, _)						-> Next(_, _)
	6. Next(_, INTEGER)					-> Next(_, 10)
	7. Next(INTEGER, synonym)			-> Next(10, n)
	8. Next(INTEGER, _)					-> Next(10, _)
	9. Next(INTEGER, INTEGER)			-> Next(3, 4)
	*/
	QueryNodeType child1_type = child1.getNodeType();
	QueryNodeType child2_type = child2.getNodeType();

	// Populate list1 with child1 values
	std::vector<INTEGER> list1;
	list1 = getStmtList(pkb, child1);

	// Populate list2 with child2 values
	std::vector<INTEGER> list2;
	list2 = getStmtList(pkb, child2);

	// create all possible pairs of list1 and list2 values
	std::vector<std::pair<INTEGER, INTEGER>> cross;
	for (INTEGER s1 : list1) {
		for (INTEGER s2 : list2) {
			cross.push_back({ s1, s2 });
		}
	}

	// filter the cross with PKB.isFollows
	std::vector<std::pair<INTEGER, INTEGER>> filter;
	for (std::pair<INTEGER, INTEGER> p : cross) {
		if (pkb.isNext(p.first, p.second)) {
			filter.push_back(p);
		}
	}

	// after filtering:
	// if the filtered list is empty, then we say that this clause is FALSE
	// else, this clause is TRUE
	clause_bool = (filter.size() > 0);

	// Add the filtered to ResultList!
	// 1. Add the synonym names as column headers
	if (child1_type == QueryNodeType::synonym) {
		SYNONYM_NAME synonym_name = child1.getString();
		clause_result_list.addColumn(synonym_name);
	}
	if (child2_type == QueryNodeType::synonym) {
		SYNONYM_NAME synonym_name = child2.getString();
		clause_result_list.addColumn(synonym_name);
	}

	// 2. Add synonym values to the Resultlist row wise
	for (std::pair<INTEGER, INTEGER> p : filter) {
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

void Relationship::getNextTResult(PKB pkb, bool& clause_bool, ResultList& clause_result_list) {
	/*
	Format: NextT( lineRef, lineRef )
	Relationship between: Program Lines
	Note: Synonyms of stmt, assign, call, read, print, while and if can appear in place of program lines (and vice-versa). Statement numbers are then interpreted as program lines.

	lineRef: synonym | _ | INTEGER

		synonym: prog_line | stmt | assign | call | read | print | while | if
		_: stmt_num_list
		INTEGER: stmt line number

	Possible Combinations:					   
	1. NextT(synonym, synonym)			-> NextT(a, r)
	2. NextT(synonym, _)				-> NextT(n, _)
	3. NextT(synonym, INTEGER)			-> NextT(n, 10)
	4. NextT(_, synonym)				-> NextT(_, n)
	5. NextT(_, _)						-> NextT(_, _)
	6. NextT(_, INTEGER)				-> NextT(_, 10)
	7. NextT(INTEGER, synonym)			-> NextT(10, n)
	8. NextT(INTEGER, _)				-> NextT(10, _)
	9. NextT(INTEGER, INTEGER)			-> NextT(3, 4)
	*/

	QueryNodeType child1_type = child1.getNodeType();
	QueryNodeType child2_type = child2.getNodeType();

	// Populate list1 with child1 values
	std::vector<INTEGER> list1;
	list1 = getStmtList(pkb, child1);

	// Populate list2 with child2 values
	std::vector<INTEGER> list2;
	list2 = getStmtList(pkb, child2);

	// create all possible pairs of list1 and list2 values
	std::vector<std::pair<INTEGER, INTEGER>> cross;
	for (INTEGER s1 : list1) {
		for (INTEGER s2 : list2) {
			cross.push_back({ s1, s2 });
		}
	}

	// filter the cross with PKB.isFollows
	std::vector<std::pair<INTEGER, INTEGER>> filter;
	for (std::pair<INTEGER, INTEGER> p : cross) {
		if (pkb.isNextTransitive(p.first, p.second)) {
			filter.push_back(p);
		}
	}

	// after filtering:
	// if the filtered list is empty, then we say that this clause is FALSE
	// else, this clause is TRUE
	clause_bool = (filter.size() > 0);

	// Add the filtered to ResultList!
	// 1. Add the synonym names as column headers
	if (child1_type == QueryNodeType::synonym) {
		SYNONYM_NAME synonym_name = child1.getString();
		clause_result_list.addColumn(synonym_name);
	}
	if (child2_type == QueryNodeType::synonym) {
		SYNONYM_NAME synonym_name = child2.getString();
		clause_result_list.addColumn(synonym_name);
	}

	// 2. Add synonym values to the Resultlist row wise
	for (std::pair<INTEGER, INTEGER> p : filter) {
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

void Relationship::getAffectsResult(PKB pkb, bool& clause_bool, ResultList& clause_result_list) {
	/*
	Format: Affects( stmtRef, stmtRef )
	Relationship between: Assignments
	Note: Affects is defined only among assignment statements aand involves a variable.

	stmtRef: synonym | _ | INTEGER

		synonym: assign
		_: assign num list
		INTEGER: assign line number

	Possible Combinations:
	1. Affects(synonym, synonym)		-> Affects(a1, a2)
	2. Affects(synonym, _)				-> Affects(a1, _ )
	3. Affects(synonym, INTEGER)		-> Affects(a1, 10)
	4. Affects(_, synonym)				-> Affects(_, a1)
	5. Affects(_, _)					-> Affects(_, _)
	6. Affects(_, INTEGER)				-> Affects(_, 10)
	7. Affects(INTEGER, synonym)		-> Affects(10, a1)
	8. Affects(INTEGER, _)				-> Affects(10, _)
	9. Affects(INTEGER, INTEGER)		-> Affects(10, 11)

	Note: Affects(a, a) may be valid. Do not short circuit by checking isSameSynonymName.
	*/

	QueryNodeType child1_type = child1.getNodeType();
	QueryNodeType child2_type = child2.getNodeType();

	std::vector<int> list1;
	std::vector<int> list2;

	// If the node is not a valid assignment type, clause is not valid.
	try {
		list1 = getAssignList(pkb, child1);
		list2 = getAssignList(pkb, child2);
	}
	catch (const char* msg) {
		clause_bool = false;
		return;
	}

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
		/*
		if (pkb.isAffects(p.first, p.second)) {
			filter.push_back(p);
		}
		*/
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

void Relationship::getAffectsTResult(PKB pkb, bool& clause_bool, ResultList& clause_result_list) {
	/*
	Format: AffectsT( stmtRef, stmtRef )
	Relationship between: Assignments
	Note: AffectsT is defined only among assignment statements aand involves a variable.

	stmtRef: synonym | _ | INTEGER

		synonym: assign
		_: assign num list
		INTEGER: assign line number

	Possible Combinations:
	1. AffectsT(synonym, synonym)		-> AffectsT(a1, a2)
	2. AffectsT(synonym, _)				-> AffectsT(a1, _ )
	3. AffectsT(synonym, INTEGER)		-> AffectsT(a1, 10)
	4. AffectsT(_, synonym)				-> AffectsT(_, a1)
	5. AffectsT(_, _)					-> AffectsT(_, _)
	6. AffectsT(_, INTEGER)				-> AffectsT(_, 10)
	7. AffectsT(INTEGER, synonym)		-> AffectsT(10, a1)
	8. AffectsT(INTEGER, _)				-> AffectsT(10, _)
	9. AffectsT(INTEGER, INTEGER)		-> AffectsT(10, 11)
	*/

	QueryNodeType child1_type = child1.getNodeType();
	QueryNodeType child2_type = child2.getNodeType();

	std::vector<int> list1;
	std::vector<int> list2;

	// If the node is not a valid assignment type, clause is not valid.
	try {
		list1 = getAssignList(pkb, child1);
		list2 = getAssignList(pkb, child2);
	}
	catch (const char* msg) {
		clause_bool = false;
		return;
	}

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
		/*
		if (pkb.isAffectsTransitive(p.first, p.second)) {
			filter.push_back(p);
		}
		*/
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

bool Relationship::isSameSynonymName(QueryNode child1, QueryNode child2) {
	bool same = false;
	STRING child1_synonym_name = child1.getString();
	STRING child2_synonym_name = child2.getString();
	bool child1_is_synonym = (child1.getNodeType() == QueryNodeType::synonym);
	bool child2_is_synonym = (child2.getNodeType() == QueryNodeType::synonym);

	if (child1_is_synonym && child2_is_synonym && (child1_synonym_name.compare(child2_synonym_name) == 0)) {
		same = true;
	}

	return same;
}

STMT_NUM_LIST Relationship::getStmtList(PKB pkb, QueryNode child1) {
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
		else if (child1_syn_type == QuerySynonymType::call) {
			return pkb.getCallNumList();
		}
		else if (child1_syn_type == QuerySynonymType::prog_line) {
			return pkb.getStatementNumList();
		}
		else {
			throw "QE: Synonym is not a statement or an integer!";
		}
	}
	else if (child1_type == QueryNodeType::wild_card) {
		return pkb.getStatementNumList();
	}
	else {
		throw "QE: stmtRef is not a integer, synonym or wildcard!";
	}
}

STMT_NUM_LIST Relationship::getAssignList(PKB pkb, QueryNode node) {
	QueryNodeType node_type = node.getNodeType();

	if (node_type == QueryNodeType::integer) {
		STMT_NUM_LIST oneIntList = { node.getInteger() };
		return oneIntList;
	}
	else if (node_type == QueryNodeType::wild_card) {
		return pkb.getAssignNumList();
	}
	else if (node_type == QueryNodeType::synonym) {
		if (node.getSynonymType() == QuerySynonymType::assign) {
			return pkb.getAssignNumList();
		}
	}
	else {
		throw "QE: Relationship: getAssignList: Node is not INTEGER | wild_card | synonym assign";
	}
}

VAR_NAME_LIST Relationship::getVarNameList(PKB pkb, QueryNode node) {
	return pkb.getVariableNameList();
}

PROC_NAME_LIST Relationship::getProcList(PKB pkb,QueryNode node) {
	return pkb.getProcedureNameList();
}
