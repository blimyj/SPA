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
		VAR_NODE_PTR var_5 = std::make_shared<VariableNode>("var5");
		VAR_NODE_PTR var_6 = std::make_shared<VariableNode>("var6");
		VAR_NODE_PTR var_7 = std::make_shared<VariableNode>("var7");
		VAR_NODE_PTR var_8 = std::make_shared<VariableNode>("var8");
		VAR_NODE_PTR var_9 = std::make_shared<VariableNode>("var9");

		CONSTANT_NODE_PTR const_1 = std::make_shared<ConstantNode>(1);
		CONSTANT_NODE_PTR const_2 = std::make_shared<ConstantNode>(2);
		CONSTANT_NODE_PTR const_3 = std::make_shared<ConstantNode>(3);
		CONSTANT_NODE_PTR const_4 = std::make_shared<ConstantNode>(4);
		
		EXPR_NODE_PTR expr = std::make_shared<ExpressionNode>(ExpressionTypeEnum::plus, var_1, var_2);

		RELATION_NODE_PTR relation_1 = std::make_shared<RelationNode>(RelationTypeEnum::eq, var_3, const_1);
		RELATION_NODE_PTR relation_2 = std::make_shared<RelationNode>(RelationTypeEnum::eq, const_2, var_4);
		RELATION_NODE_PTR relation_3 = std::make_shared<RelationNode>(RelationTypeEnum::eq, var_5, var_6);
		RELATION_NODE_PTR relation_4 = std::make_shared<RelationNode>(RelationTypeEnum::eq, const_3, const_4);
		
		CONDITION_NODE_PTR cond_1 = std::make_shared<ConditionNode>(ConditionTypeEnum::and, relation_1, relation_2);
		CONDITION_NODE_PTR cond_2 = std::make_shared<ConditionNode>(ConditionTypeEnum::and, relation_3, relation_4);
		
		STMT_LIST_NODE_PTR stmt_1 = std::make_shared<StatementListNode>();
		STMT_LIST_NODE_PTR stmt_2 = std::make_shared<StatementListNode>();
		STMT_LIST_NODE_PTR stmt_3 = std::make_shared<StatementListNode>();
		STMT_LIST_NODE_PTR stmt_4 = std::make_shared<StatementListNode>();

		ASSIGN_NODE_PTR assign_1 = std::make_shared<AssignNode>(var_7, expr);
		PRINT_NODE_PTR print_1 = std::make_shared<PrintNode>(var_8);
		READ_NODE_PTR read_1 = std::make_shared<ReadNode>(var_9);

		IF_NODE_PTR if_1 = std::make_shared<IfNode>(cond_1, stmt_1, stmt_2);
		WHILE_NODE_PTR while_1 = std::make_shared<WhileNode>(cond_2, stmt_3);

		PROC_NODE_PTR proc_1 = std::make_shared<ProcedureNode>("proc4", stmt_4);

		void initializeTests() {
			pkb_builder.addAssignNode(assign_1);
			pkb_builder.addConstantNode(const_1);
			pkb_builder.addIfNode(if_1);
			pkb_builder.addPrintNode(print_1);
			pkb_builder.addProcedureNode(proc_1);
			pkb_builder.addReadNode(read_1);
			pkb_builder.addStatementListNode(stmt_1);
			pkb_builder.addStatementNode(assign_1);
			pkb_builder.addVariableNode(var_1);
			pkb_builder.addWhileNode(while_1);

			pkb = std::make_shared<PKB>(pkb_builder.build());
		}

		TEST_METHOD(getAssigns) {
			initializeTests();
			ASSIGN_NODE_PTR actual = pkb->getAssigns().at(0);
			Assert::IsTrue(typeid(*assign_1) == typeid(*actual));
		}
		
		TEST_METHOD(getConstants) {
			initializeTests();
			CONSTANT_NODE_PTR actual = pkb->getConstants().at(0);
			Assert::IsTrue(typeid(*const_1) == typeid(*actual));
		}

		TEST_METHOD(getIfs) {
			initializeTests();
			IF_NODE_PTR actual = pkb->getIfs().at(0);
			Assert::IsTrue(typeid(*if_1) == typeid(*actual));
		}

		TEST_METHOD(getPrints) {
			initializeTests();
			PRINT_NODE_PTR actual = pkb->getPrints().at(0);
			Assert::IsTrue(typeid(*print_1) == typeid(*actual));
		}

		TEST_METHOD(getProcedures) {
			initializeTests();
			PROC_NODE_PTR actual = pkb->getProcedures().at(0);
			Assert::IsTrue(typeid(*proc_1) == typeid(*actual));
		}

		TEST_METHOD(getReads) {
			initializeTests();
			READ_NODE_PTR actual = pkb->getReads().at(0);
			Assert::IsTrue(typeid(*read_1) == typeid(*actual));
		}

		TEST_METHOD(getStatementLists) {
			initializeTests();
			STMT_LIST_NODE_PTR actual = pkb->getStatementLists().at(0);
			Assert::IsTrue(typeid(*stmt_1) == typeid(*actual));
		}

		TEST_METHOD(getStatements) {
			initializeTests();
			STMT_NODE_PTR actual = pkb->getStatements().at(0);
			Assert::IsTrue(assign_1.get()->getNodeType() == actual.get()->getNodeType());
			AssignNode* actual_casted = (AssignNode*) &*actual;
			// Test if it is the same node by checking the child, because the parent of the child is always unique.
			VAR_NODE_PTR var_node = actual_casted->getVariableNode();
			Assert::IsTrue(typeid(*var_1) == typeid(*var_node));
		}

		TEST_METHOD(getVariables) {
			initializeTests();
			VAR_NODE_PTR actual = pkb->getVariables().at(0);
			Assert::IsTrue(typeid(*var_1) == typeid(*actual));
		}

		TEST_METHOD(getWhiles) {
			initializeTests();
			WHILE_NODE_PTR actual = pkb->getWhiles().at(0);
			Assert::IsTrue(typeid(*while_1) == typeid(*actual));
		}

	};
}