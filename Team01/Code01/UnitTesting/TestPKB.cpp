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

		CONSTANT_NODE_PTR const_1 = std::make_shared<ConstantNode>("1");
		CONSTANT_NODE_PTR const_2 = std::make_shared<ConstantNode>("2");
		CONSTANT_NODE_PTR const_3 = std::make_shared<ConstantNode>("3");
		CONSTANT_NODE_PTR const_4 = std::make_shared<ConstantNode>("4");
		
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

	TEST_CLASS(PKB_RelationshipTests) {
	public:
		/*
		- procedure main {
		1   print x;
		2   print y;
		3   print z;
		- }
		*/
		std::shared_ptr<PKB> pkb1;

		/*
		- procedure main {
		1   while (x > 0) then {
		2     if (y > 0) then {
		3       read x;
		4       read y;
		-     } else {
		5       read z;
		6       y = y + 1;
		-     }
		-   }
		- }
		*/
		std::shared_ptr<PKB> pkb2;

		// FollowsT only
		/*
		- procedure {
		1   stmt
		2   stmt
		3   stmt
		4   while {
		5     stmt
		6     stmt
		-   }
		7   stmt
		8   stmt
		9   stmt
		- }
		*/
		std::shared_ptr<PKB> pkb3;

		// ParentT only
		/*
		- procedure {
		1   while {
		2     while {
		3       while {
		4         stmt
		-       }
		5       while {
		6         stmt
		-       }
		-     }
		7     while {
		8       stmt
		9       stmt
		-     }
		-   }
		- }
		*/
		std::shared_ptr<PKB> pkb4;

		TEST_METHOD_INITIALIZE(PKBInitialize) {
			PKBBuilder b1;
			b1.addFollows(1, 2);
			b1.addFollows(2, 3);
			b1.addUses("main", "x");
			b1.addUses("main", "y");
			b1.addUses("main", "z");
			b1.addUses(1, "x");
			b1.addUses(2, "y");
			b1.addUses(3, "z");
			pkb1 = std::make_shared<PKB>(b1.build());

			PKBBuilder b2;
			b2.addFollows(3, 4);
			b2.addFollows(5, 6);
			b2.addParent(1, 2);
			b2.addParent(2, 3);
			b2.addParent(2, 4);
			b2.addParent(2, 5);
			b2.addParent(2, 6);
			b2.addUses("main", "x");
			b2.addUses("main", "y");
			b2.addUses(1, "x");
			b2.addUses(1, "y");
			b2.addUses(2, "y");
			b2.addUses(6, "y");
			b2.addModifies("main", "x");
			b2.addModifies("main", "y");
			b2.addModifies("main", "z");
			b2.addModifies(1, "x");
			b2.addModifies(2, "y");
			b2.addModifies(3, "z");
			b2.addModifies(2, "x");
			b2.addModifies(2, "y");
			b2.addModifies(2, "z");
			b2.addModifies(3, "x");
			b2.addModifies(4, "y");
			b2.addModifies(5, "z");
			b2.addModifies(6, "y");
			pkb2 = std::make_shared<PKB>(b2.build());

			PKBBuilder b3;
			b3.addFollows(1, 2);
			b3.addFollows(2, 3);
			b3.addFollows(3, 4);
			b3.addFollows(4, 7);
			b3.addFollows(5, 6);
			b3.addFollows(7, 8);
			b3.addFollows(8, 9);
			pkb3 = std::make_shared<PKB>(b3.build());

			PKBBuilder b4;
			b4.addParent(1, 2);
			b4.addParent(1, 7);
			b4.addParent(2, 3);
			b4.addParent(2, 5);
			b4.addParent(3, 4);
			b4.addParent(5, 6);
			b4.addParent(7, 8);
			b4.addParent(7, 9);
			pkb4 = std::make_shared<PKB>(b4.build());
		}

		/* isFollows */
		TEST_METHOD(isFollows_Stored_True) {
			Assert::IsTrue(pkb1->isFollows(1, 2));
			Assert::IsTrue(pkb1->isFollows(2, 3));

			Assert::IsTrue(pkb2->isFollows(3, 4));
			Assert::IsTrue(pkb2->isFollows(5, 6));
		}

		TEST_METHOD(isFollows_Transitive_False) {
			Assert::IsFalse(pkb1->isFollows(1, 3));

			Assert::IsFalse(pkb3->isFollows(1, 9));
		}

		TEST_METHOD(isFollows_InvalidStmtNum_False) {
			Assert::IsFalse(pkb1->isFollows(0, 1));
			Assert::IsFalse(pkb1->isFollows(3, 4));
		}

		TEST_METHOD(isFollows_S1GeqS2_False) {
			Assert::IsFalse(pkb1->isFollows(1, 1));
			Assert::IsFalse(pkb1->isFollows(2, 1));
			Assert::IsFalse(pkb1->isFollows(3, 2));
		}

		TEST_METHOD(isFollows_IfBlocks_False) {
			Assert::IsFalse(pkb2->isFollows(4, 5));
		}

		TEST_METHOD(isFollows_Children_False) {
			Assert::IsFalse(pkb2->isFollows(1, 2));
			Assert::IsFalse(pkb2->isFollows(1, 3));
			Assert::IsFalse(pkb2->isFollows(2, 3));
			Assert::IsFalse(pkb2->isFollows(2, 6));
		}

		/* isFollowsTransitive */
		TEST_METHOD(isFollowsT_Stored_True) {
			Assert::IsTrue(pkb1->isFollowsTransitive(1, 2));
			Assert::IsTrue(pkb1->isFollowsTransitive(2, 3));

			Assert::IsTrue(pkb2->isFollowsTransitive(3, 4));
			Assert::IsTrue(pkb2->isFollowsTransitive(5, 6));
		}

		TEST_METHOD(isFollowsT_Transitive_True) {
			Assert::IsTrue(pkb1->isFollowsTransitive(1, 3));

			Assert::IsTrue(pkb3->isFollowsTransitive(1, 9));
		}

		TEST_METHOD(isFollowsT_InvalidStmtNum_False) {
			Assert::IsFalse(pkb1->isFollowsTransitive(0, 1));
			Assert::IsFalse(pkb1->isFollowsTransitive(3, 4));
		}

		TEST_METHOD(isFollowsT_S1GeqS2_False) {
			Assert::IsFalse(pkb1->isFollowsTransitive(1, 1));
			Assert::IsFalse(pkb1->isFollowsTransitive(2, 1));
			Assert::IsFalse(pkb1->isFollowsTransitive(3, 2));
		}

		TEST_METHOD(isFollowsT_IfBlocks_False) {
			Assert::IsFalse(pkb2->isFollowsTransitive(4, 5));
		}

		TEST_METHOD(isFollowsT_Children_False) {
			Assert::IsFalse(pkb2->isFollowsTransitive(1, 2));
			Assert::IsFalse(pkb2->isFollowsTransitive(1, 3));
			Assert::IsFalse(pkb2->isFollowsTransitive(2, 3));
			Assert::IsFalse(pkb2->isFollowsTransitive(2, 6));
		}

		/* isParent */
		TEST_METHOD(isParent_Stored_True) {
			Assert::IsTrue(pkb2->isParent(1, 2));
			Assert::IsTrue(pkb2->isParent(2, 3));
			Assert::IsTrue(pkb2->isParent(2, 4));
			Assert::IsTrue(pkb2->isParent(2, 5));
			Assert::IsTrue(pkb2->isParent(2, 6));
		}

		TEST_METHOD(isParent_Transitive_False) {
			Assert::IsFalse(pkb2->isParent(1, 3));
			Assert::IsFalse(pkb2->isParent(1, 4));
			Assert::IsFalse(pkb2->isParent(1, 5));
			Assert::IsFalse(pkb2->isParent(1, 6));

			Assert::IsFalse(pkb4->isParent(1, 4));
			Assert::IsFalse(pkb4->isParent(1, 6));
			Assert::IsFalse(pkb4->isParent(1, 8));
			Assert::IsFalse(pkb4->isParent(1, 9));
		}

		TEST_METHOD(isParent_InvalidStmtNum_False) {
			Assert::IsFalse(pkb1->isParent(0, 1));
			Assert::IsFalse(pkb1->isParent(3, 4));
		}

		TEST_METHOD(isParent_S1GeqS2_False) {
			Assert::IsFalse(pkb2->isParent(1, 1));
			Assert::IsFalse(pkb2->isParent(2, 1));
			Assert::IsFalse(pkb2->isParent(3, 2));
		}

		/* isParentTransitive */
		TEST_METHOD(isParentT_Stored_True) {
			Assert::IsTrue(pkb2->isParentTransitive(1, 2));
			Assert::IsTrue(pkb2->isParentTransitive(2, 3));
			Assert::IsTrue(pkb2->isParentTransitive(2, 4));
			Assert::IsTrue(pkb2->isParentTransitive(2, 5));
			Assert::IsTrue(pkb2->isParentTransitive(2, 6));
		}

		TEST_METHOD(isParentT_Transitive_True) {
			Assert::IsTrue(pkb2->isParentTransitive(1, 3));
			Assert::IsTrue(pkb2->isParentTransitive(1, 4));
			Assert::IsTrue(pkb2->isParentTransitive(1, 5));
			Assert::IsTrue(pkb2->isParentTransitive(1, 6));

			Assert::IsTrue(pkb4->isParentTransitive(1, 4));
			Assert::IsTrue(pkb4->isParentTransitive(1, 6));
			Assert::IsTrue(pkb4->isParentTransitive(1, 8));
			Assert::IsTrue(pkb4->isParentTransitive(1, 9));
		}

		TEST_METHOD(isParentT_InvalidStmtNum_False) {
			Assert::IsFalse(pkb1->isParentTransitive(0, 1));
			Assert::IsFalse(pkb1->isParentTransitive(3, 4));
		}

		TEST_METHOD(isParentT_S1GeqS2_False) {
			Assert::IsFalse(pkb2->isParentTransitive(1, 1));
			Assert::IsFalse(pkb2->isParentTransitive(2, 1));
			Assert::IsFalse(pkb2->isParentTransitive(3, 2));
		}

		/* isUses */
		TEST_METHOD(isUses_Stored_True) {
			Assert::IsTrue(pkb1->isUses("main", "x"));
			Assert::IsTrue(pkb1->isUses("main", "y"));
			Assert::IsTrue(pkb1->isUses("main", "z"));
			Assert::IsTrue(pkb1->isUses(1, "x"));
			Assert::IsTrue(pkb1->isUses(2, "y"));
			Assert::IsTrue(pkb1->isUses(3, "z"));

			Assert::IsTrue(pkb2->isUses("main", "x"));
			Assert::IsTrue(pkb2->isUses("main", "y"));
			Assert::IsTrue(pkb2->isUses(1, "x"));
			Assert::IsTrue(pkb2->isUses(1, "y"));
			Assert::IsTrue(pkb2->isUses(2, "y"));
			Assert::IsTrue(pkb2->isUses(6, "y"));
		}

		TEST_METHOD(isUses_InvalidArgs_False) {
			Assert::IsFalse(pkb1->isUses(0, ""));
			Assert::IsFalse(pkb1->isUses("", "a"));
		}

		/* isModifies */
		TEST_METHOD(isModifies_Stored_True) {
			Assert::IsTrue(pkb2->isModifies("main", "x"));
			Assert::IsTrue(pkb2->isModifies("main", "y"));
			Assert::IsTrue(pkb2->isModifies("main", "z"));
			Assert::IsTrue(pkb2->isModifies(1, "x"));
			Assert::IsTrue(pkb2->isModifies(2, "y"));
			Assert::IsTrue(pkb2->isModifies(3, "z"));
			Assert::IsTrue(pkb2->isModifies(2, "x"));
			Assert::IsTrue(pkb2->isModifies(2, "y"));
			Assert::IsTrue(pkb2->isModifies(2, "z"));
			Assert::IsTrue(pkb2->isModifies(3, "x"));
			Assert::IsTrue(pkb2->isModifies(4, "y"));
			Assert::IsTrue(pkb2->isModifies(5, "z"));
			Assert::IsTrue(pkb2->isModifies(6, "y"));
		}

		TEST_METHOD(isModifies_InvalidArgs_False) {
			Assert::IsFalse(pkb1->isModifies(0, ""));
			Assert::IsFalse(pkb1->isModifies("", "a"));
		}
	};
}