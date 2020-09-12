#include <typeinfo>

#include "stdafx.h"
#include "CppUnitTest.h"
#include "PKB.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting {
	
	TEST_CLASS(TestPKB) {
	public:
		std::shared_ptr<PKB> pkb;
		PKBBuilder pkb_builder;

		VAR_NODE_PTR var_1 = std::make_shared<VariableNode>("var1");
		VAR_NODE_PTR var_2 = std::make_shared<VariableNode>("var2");
		VAR_NODE_PTR var_3 = std::make_shared<VariableNode>("var3");
		VAR_NODE_PTR var_4 = std::make_shared<VariableNode>("var4");

		CONSTANT_NODE_PTR constant = std::make_shared<ConstantNode>(5);
		
		EXPR_NODE_PTR expr = std::make_shared<ExpressionNode>(ExpressionTypeEnum::plus, var_1, var_2);
		CONDITION_NODE_PTR cond = std::make_shared<ConditionNode>(ConditionTypeEnum::not, var_3, var_4);
		// RELATION_NODE_PTR relation = std::make_shared

		// ASSIGN_NODE_PTR assign = std::make_shared<AssignNode>(assign_var, expr);
		
		STMT_LIST_NODE_PTR then_stmt = std::make_shared<StatementListNode>();
		STMT_LIST_NODE_PTR then_stmt = std::make_shared<StatementListNode>();
		IF_NODE_PTR ifs = std::make_shared<IfNode>(cond);

		void initializeTests() {
			

			pkb = std::make_shared<PKB>(pkb_builder.build());
		}

		TEST_METHOD(getAssigns) {
			initializeTests();
			ASSIGN_NODE_PTR actual = pkb->getAssigns().at(0);
			Assert::IsTrue(typeid(*assign) == typeid(*actual));
		}
		
		TEST_METHOD(getConstants) {
			initializeTests();
			CONSTANT_NODE_PTR actual = pkb->getConstants().at(0);
			Assert::IsTrue(typeid(*assign) == typeid(*actual));
		}

		TEST_METHOD(getIfs) {
			initializeTests();
			IF_NODE_PTR actual = pkb->getIfs().at(0);
			Assert::IsTrue(typeid(*assign) == typeid(*actual));
		}

		TEST_METHOD(getPrints) {
			initializeTests();
			PRINT_NODE_PTR actual = pkb->getPrints().at(0);
			Assert::IsTrue(typeid(*assign) == typeid(*actual));
		}

		TEST_METHOD(getProcedures) {
			initializeTests();
			PROC_NODE_PTR actual = pkb->getProcedures().at(0);
			Assert::IsTrue(typeid(*assign) == typeid(*actual));
		}

		TEST_METHOD(getReads) {
			initializeTests();
			READ_NODE_PTR actual = pkb->getReads().at(0);
			Assert::IsTrue(typeid(*assign) == typeid(*actual));
		}

		TEST_METHOD(getStatementLists) {
			initializeTests();
			STMT_LIST_NODE_PTR actual = pkb->getStatementLists().at(0);
			Assert::IsTrue(typeid(*assign) == typeid(*actual));
		}

		TEST_METHOD(getStatements) {
			initializeTests();
			STMT_NODE_PTR actual = pkb->getStatements().at(0);
			Assert::IsTrue(typeid(*assign) == typeid(*actual));
		}

		TEST_METHOD(getVariables) {
			initializeTests();
			VAR_NODE_PTR actual = pkb->getVariables().at(0);
			Assert::IsTrue(typeid(*assign) == typeid(*actual));
		}

		TEST_METHOD(getWhiles) {
			initializeTests();
			WHILE_NODE_PTR actual = pkb->getWhiles().at(0);
			Assert::IsTrue(typeid(*assign) == typeid(*actual));
		}

	};
}