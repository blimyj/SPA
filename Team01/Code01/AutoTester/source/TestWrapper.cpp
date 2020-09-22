#include "TestWrapper.h"

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

// implementation code of WrapperFactory - do NOT modify the next 5 lines
AbstractWrapper* WrapperFactory::wrapper = 0;
AbstractWrapper* WrapperFactory::createWrapper() {
  if (wrapper == 0) wrapper = new TestWrapper;
  return wrapper;
}
// Do not modify the following line
volatile bool TestWrapper::GlobalStop = false;

// a default constructor
TestWrapper::TestWrapper() {
  // create any objects here as instance variables of this class
  // as well as any initialization required for your spa program
	this->pkb = PKBBuilder().build();
}

// method for parsing the SIMPLE source
void TestWrapper::parse(std::string filename) {
	// call your parser to do the parsing
  // ...rest of your code...
}

// method to evaluating a query
void TestWrapper::evaluate(std::string query, std::list<std::string>& results){
// call your evaluator to evaluate the query here
  // ...code to evaluate query...

	QueryProcessor qp = QueryProcessor(this->pkb);
	QUERY_RESULT query_result;
	STRING_RESULT result_string;

	try {
		query_result = qp.processQuery(query);
		result_string = ResultListManager::getStringValues(query_result);
	}
	catch (const char* msg) {
		std::cout << msg << "\n";
	}

	// store the answers to the query in the results list (it is initially empty)
	// each result must be a string.
	for (auto query : query_result) {
		results.push_back(query);
	}

	std::cout << "query=  " << query << std::endl;
	std::cout << "query result= " << result_string << std::endl;
}
