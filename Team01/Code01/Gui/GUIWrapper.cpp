#include <iostream>

#include "GUIWrapper.h"
#include "../source/Parser.h"
#include "../source/PKB/DesignEntities/AssignTable.cpp"
#include "../source/PKB/DesignEntities/ConstantTable.cpp"
#include "../source/PKB/DesignEntities/IfTable.cpp"
#include "../source/PKB/DesignEntities/PrintTable.cpp"
#include "../source/PKB/DesignEntities/ProcedureTable.cpp"
#include "../source/PKB/DesignEntities/ReadTable.cpp"
#include "../source/PKB/DesignEntities/StatementTable.cpp"
#include "../source/PKB/DesignEntities/VariableTable.cpp"
#include "../source/PKB/DesignEntities/WhileTable.cpp"
#include "../source/PKB/Relationships/FollowsTable.cpp"
#include "../source/PKB/Relationships/ParentTable.cpp"
#include "../source/PKB/Relationships/UsesTable.cpp"
#include "../source/PKB/Relationships/ModifiesTable.cpp"
#include "../source/QueryNodeContent.cpp"
#include "../source/QueryNode.cpp"
#include "../source/QueryProcessor.cpp"
#include "../source/QueryEvaluator.cpp"
#include "../source/ResultList.cpp"
#include "../source/ResultListManager.h"
#include "../source/PKB.cpp"
#include "../source/PKBBuilder.cpp"
#include "../source/PKB/ASTNode/VariableNode.cpp"
#include "../source/PKBStub.cpp"


// a default constructor
GUIWrapper::GUIWrapper() {
  // create any objects here as instance variables of this class
  // as well as any initialization required for your spa program
	this->pkb = PKBBuilder().build();
}

// method for parsing the SIMPLE source
void GUIWrapper::parse(std::string filename) {
	// call your parser to do the parsing
	std::cout << "parsed " << filename;
	Parser parser = Parser();
	
	try {
		
		this->pkb = parser.parseFile(filename);

	}
	catch (const char* msg) {
		std::cout << msg << "\n";
	}
	// ...rest of your code...
}

// method to evaluating a query
void GUIWrapper::evaluate(std::string query, std::list<std::string>& results){
// call your evaluator to evaluate the query here
  // ...code to evaluate query...

	// Create PKBStub -- to be deleted
	PKBStub pkb_init = PKBStub();
	PKB pkbstub = pkb_init.addVariables();


	QueryProcessor qp = QueryProcessor(this->pkb);
	//QueryProcessor qp = QueryProcessor(pkbstub);
	//QueryNode qn = QueryNode();
	QUERY_RESULT query_result = qp.processQuery(query);


	std::cout << "query=  " << query << std::endl;
	std::cout << "query result= " << query_result << std::endl;
	results.push_back(query + "\nQuery result: ");
  // store the answers to the query in the results list (it is initially empty)
  // each result must be a string.
	results.push_back(query_result);
}
