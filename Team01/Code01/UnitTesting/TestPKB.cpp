#include <typeinfo>

#include "stdafx.h"
#include "CppUnitTest.h"
#include "PKB.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting {
	
	TEST_CLASS(PKBTest) {
	public:
		TEST_METHOD(getAssigns) {
			PKBBuilder pkb_builder;
			ASSIGN_NODE_PTR expected = std::make_shared<AssignNode>();
			pkb_builder.addAssignNode(expected);
			PKB pkb = pkb_builder.build();
			ASSIGN_NODE_PTR actual = pkb.getAssigns().at(0);
			Assert::IsTrue(typeid(*expected) == typeid(*actual));
		}
		
		TEST_METHOD(getConstants) {
			PKBBuilder pkb_builder;
			CONSTANT_NODE_PTR expected = std::make_shared<ConstantNode>();
			pkb_builder.addConstantNode(expected);
			PKB pkb = pkb_builder.build();
			CONSTANT_NODE_PTR actual = pkb.getConstants().at(0);
			Assert::IsTrue(typeid(*expected) == typeid(*actual));
		}

		TEST_METHOD(getIfs) {
			PKBBuilder pkb_builder;
			IF_NODE_PTR expected = std::make_shared<IfNode>();
			pkb_builder.addIfNode(expected);
			PKB pkb = pkb_builder.build();
			IF_NODE_PTR actual = pkb.getIfs().at(0);
			Assert::IsTrue(typeid(*expected) == typeid(*actual));
		}

		TEST_METHOD(getPrints) {
			PKBBuilder pkb_builder;
			PRINT_NODE_PTR expected = std::make_shared<PrintNode>();
			pkb_builder.addPrintNode(expected);
			PKB pkb = pkb_builder.build();
			PRINT_NODE_PTR actual = pkb.getPrints().at(0);
			Assert::IsTrue(typeid(*expected) == typeid(*actual));
		}

		TEST_METHOD(getProcedures) {
			PKBBuilder pkb_builder;
			PROC_NODE_PTR expected = std::make_shared<ProcedureNode>();
			pkb_builder.addProcedureNode(expected);
			PKB pkb = pkb_builder.build();
			PROC_NODE_PTR actual = pkb.getProcedures().at(0);
			Assert::IsTrue(typeid(*expected) == typeid(*actual));
		}

		TEST_METHOD(getReads) {
			PKBBuilder pkb_builder;
			READ_NODE_PTR expected = std::make_shared<ReadNode>();
			pkb_builder.addReadNode(expected);
			PKB pkb = pkb_builder.build();
			READ_NODE_PTR actual = pkb.getReads().at(0);
			Assert::IsTrue(typeid(*expected) == typeid(*actual));
		}

		TEST_METHOD(getStatementLists) {
			PKBBuilder pkb_builder;
			STMT_LIST_NODE_PTR expected = std::make_shared<StatementListNode>();
			pkb_builder.addStatementListNode(expected);
			PKB pkb = pkb_builder.build();
			STMT_LIST_NODE_PTR actual = pkb.getStatementLists().at(0);
			Assert::IsTrue(typeid(*expected) == typeid(*actual));
		}

		TEST_METHOD(getStatements) {
			PKBBuilder pkb_builder;
			ASSIGN_NODE_PTR expected = std::make_shared<AssignNode>();
			pkb_builder.addStatementNode(expected);
			PKB pkb = pkb_builder.build();
			AssignNode* actual = static_cast<AssignNode*>(pkb.getStatements().at(0).get());
			Assert::IsTrue(typeid(*expected) == typeid(*actual));
		}

		TEST_METHOD(getVariables) {
			PKBBuilder pkb_builder;
			VAR_NODE_PTR expected = std::make_shared<VariableNode>();
			pkb_builder.addVariableNode(expected);
			PKB pkb = pkb_builder.build();
			VAR_NODE_PTR actual = pkb.getVariables().at(0);
			Assert::IsTrue(typeid(*expected) == typeid(*actual));
		}

		TEST_METHOD(getWhiles) {
			PKBBuilder pkb_builder;
			WHILE_NODE_PTR expected = std::make_shared<WhileNode>();
			pkb_builder.addWhileNode(expected);
			PKB pkb = pkb_builder.build();
			WHILE_NODE_PTR actual = pkb.getWhiles().at(0);
			Assert::IsTrue(typeid(*expected) == typeid(*actual));
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