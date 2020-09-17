#include <typeinfo>

#include "stdafx.h"
#include "CppUnitTest.h"
#include "../source/Parser.h"
#include "../source/PKB.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting {
	TEST_CLASS(TestParser) {
	public:

		TEST_METHOD(TestBasicProcedure)
		{	
			std::shared_ptr<PKB> pkb;
			PKB_BUILDER pkb_builder;
			
			STMT_LIST_NODE_PTR stmt_1 = std::make_shared<StatementListNode>();
			PROC_NODE_PTR proc_1 = std::make_shared<ProcedureNode>("main", stmt_1);
			pkb_builder.addProcedureNode(proc_1);
			pkb_builder.addStatementListNode(stmt_1);
			pkb = std::make_shared<PKB>(pkb_builder.build());

			Parser test_parser = Parser();
			std::shared_ptr <PKB> test_pkb = 
				std::make_shared<PKB> (test_parser.parseFile("../UnitTesting/Parser/TestParser-1.txt"));			
			
			PROC_NODE_PTR actual = test_pkb->getProcedures().at(0);
			PROC_NODE_PTR for_testing = pkb->getProcedures().at(0);
			Assert::IsTrue(typeid(*for_testing) == typeid(*actual));

			ASSIGN_NODE_PTR actual = test_pkb->getAssigns().at(0);
			ASSIGN_NODE_PTR for_testing = pkb->getAssigns().at(0);
			Assert::IsTrue(typeid(*for_testing) == typeid(*actual));

			VAR_NODE_PTR actual = test_pkb->getVariables().at(0);
			VAR_NODE_PTR for_testing = pkb->getVariables().at(0);
			Assert::IsTrue(typeid(*for_testing) == typeid(*actual));
		}

	};
}