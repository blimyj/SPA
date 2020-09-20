#include "stdafx.h"
#include "CppUnitTest.h"
#include "../source/QueryEvaluator.h"
#include "../source/PKBStub.h"
#include "../source/QueryNode.h"
#include "../source/QueryNodeType.h"
#include "../source/PKB/ASTNode/PrintNode.h"
#include "../source/PKB/ASTNode/StatementNode.h"
#include "../source/PKB/ASTNode/VariableNode.h"
#include "../source/PKBBuilder.h"
#include "../source/PKB.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestQueryEvaluator)
	{
	public:
		/*
		procedure main {
			print a;
			print b;
			print c;
			print d;
			print e;
		}
		*/
		std::shared_ptr<PKB> pkb;

		TEST_METHOD_INITIALIZE(PKBInitialize) {
			// PKB
			PKBBuilder builder;
			
			std::shared_ptr<VariableNode> v1 = std::make_shared<VariableNode>();
			v1->setVariableName("a");
			std::shared_ptr<VariableNode> v2 = std::make_shared<VariableNode>();
			v2->setVariableName("b");
			std::shared_ptr<VariableNode> v3 = std::make_shared<VariableNode>();
			v3->setVariableName("c");
			std::shared_ptr<VariableNode> v4 = std::make_shared<VariableNode>();
			v4->setVariableName("d");
			std::shared_ptr<VariableNode> v5 = std::make_shared<VariableNode>();
			v5->setVariableName("e");

			builder.addVariableNode(v1);
			builder.addVariableNode(v2);
			builder.addVariableNode(v3);
			builder.addVariableNode(v4);
			builder.addVariableNode(v5);

			std::shared_ptr<PrintNode> p1 = std::make_shared<PrintNode>();
			p1->setStatementNumber(1);
			p1->setVariableNode(v1);
			std::shared_ptr<PrintNode> p2 = std::make_shared<PrintNode>();
			p2->setStatementNumber(2);
			p2->setVariableNode(v2);
			std::shared_ptr<PrintNode> p3 = std::make_shared<PrintNode>();
			p3->setStatementNumber(3);
			p3->setVariableNode(v3);
			std::shared_ptr<PrintNode> p4 = std::make_shared<PrintNode>();
			p4->setStatementNumber(4);
			p4->setVariableNode(v4);
			std::shared_ptr<PrintNode> p5 = std::make_shared<PrintNode>();
			p5->setStatementNumber(5);
			p5->setVariableNode(v5);


			builder.addPrintNode(p1);
			builder.addPrintNode(p2);
			builder.addPrintNode(p3);
			builder.addPrintNode(p4);
			builder.addPrintNode(p5);

			StatementNode s1;
			s1.setStatementNumber(1);
			StatementNode s2;
			s2.setStatementNumber(2);
			StatementNode s3;
			s3.setStatementNumber(3);
			StatementNode s4;
			s4.setStatementNumber(4);
			StatementNode s5;
			s5.setStatementNumber(5);
			builder.addStatementNode(std::make_shared<StatementNode>(s1));
			builder.addStatementNode(std::make_shared<StatementNode>(s2));
			builder.addStatementNode(std::make_shared<StatementNode>(s3));
			builder.addStatementNode(std::make_shared<StatementNode>(s4));
			builder.addStatementNode(std::make_shared<StatementNode>(s5));

			builder.addFollows(1, 2);
			builder.addFollows(2, 3);
			builder.addFollows(3, 4);
			builder.addFollows(4, 5);

			pkb = std::make_shared<PKB>(builder.build());
		}

		TEST_METHOD(evaluateQuery_Select_Success)
		{
			// Query: "variable v; Select v"
			// Get processed_synonyms and processed clauses
			QueryNode variable_node = QueryNode();
			variable_node.setSynonymNode({ QuerySynonymType::variable }, "v");
			std::unordered_map<std::string, QueryNode> processed_synonyms = { {"v", variable_node} };

			QueryNode child1 = QueryNode();
			child1.setNodeType({ QueryNodeType::select });
			QueryNode child2 = QueryNode();
			child2.setSynonymNode({ QuerySynonymType::variable }, "v");
			QueryNode child1_children[] = { child2 };
			child1.setChildren(child1_children, 1);

			QueryNode processed_clauses = child1; //stores root node of the tree

			QueryEvaluator qe = QueryEvaluator(*pkb);
			QUERY_RESULT result = qe.evaluateQuery(processed_synonyms, processed_clauses);
			STRING_RESULT result_string = ResultListManager::getStringValues(result);
			STRING_RESULT correct_result = "a, b, c, d, e";
			
			Logger::WriteMessage(result_string.c_str());
			Assert::IsTrue(result_string.compare(correct_result) == 0);
		}

		TEST_METHOD(evaluateQuery_SelectPn_Success) {
			// Query: "print pn; Select pn"
			// Get processed_synonyms and processed clauses
			QueryNode variable_node = QueryNode();
			variable_node.setSynonymNode({ QuerySynonymType::print }, "pn");
			std::unordered_map<std::string, QueryNode> processed_synonyms = { {"pn", variable_node} };

			QueryNode child1 = QueryNode();
			child1.setNodeType({ QueryNodeType::select });
			QueryNode child2 = QueryNode();
			child2.setSynonymNode({ QuerySynonymType::print }, "pn");
			QueryNode child1_children[] = { child2 };
			child1.setChildren(child1_children, 1);

			QueryNode processed_clauses = child1; //stores root node of the tree

			QueryEvaluator qe = QueryEvaluator(*pkb);
			QUERY_RESULT result = qe.evaluateQuery(processed_synonyms, processed_clauses);
			STRING_RESULT result_string = ResultListManager::getStringValues(result);
			STRING_RESULT correct_result = "1, 2, 3, 4, 5";

			Logger::WriteMessage(result_string.c_str());
			Assert::IsTrue(result_string.compare(correct_result) == 0);
		}
		
		TEST_METHOD(evaluateQuery_SelectS1FollowsS1S2_ReturnsS1)
		{
			// Query: "stmt s1, s2; variable v; Select s1 such that Follows(s1,s2)"
			// Get processed_synonyms and processed clauses
			QueryNode variable_node = QueryNode();
			variable_node.setSynonymNode({ QuerySynonymType::variable }, "v");
			QueryNode s1_node = QueryNode();
			variable_node.setSynonymNode({ QuerySynonymType::stmt }, "s1");
			QueryNode s2_node = QueryNode();
			variable_node.setSynonymNode({ QuerySynonymType::stmt }, "s2");
			std::unordered_map<std::string, QueryNode> processed_synonyms = { {"v", variable_node}, {"s1", s1_node}, {"s2", s2_node} };

			QueryNode child1 = QueryNode();
			child1.setSynonymNode({ QuerySynonymType::stmt }, "s1");
			QueryNode child2 = QueryNode();
			child2.setNodeType({ QueryNodeType::such_that });
			QueryNode child_child1 = QueryNode();
			child_child1.setNodeType({ QueryNodeType::follows});
			QueryNode child_child_child1 = QueryNode();
			child_child_child1.setSynonymNode({ QuerySynonymType::stmt }, "s1");
			QueryNode child_child_child2 = QueryNode();
			child_child_child2.setSynonymNode({ QuerySynonymType::stmt }, "s2");
			QueryNode child_child1_children[] = { child_child_child1, child_child_child2 };
			child_child1.setChildren(child_child1_children, 2);
			QueryNode child2_children[] = {child_child1};
			child2.setChildren(child2_children, 1);

			QueryNode root = QueryNode();
			root.setNodeType({ QueryNodeType::select });
			QueryNode root_children[] = { child1, child2 };
			root.setChildren(root_children, 2);

			QueryNode processed_clauses = root; //stores root node of the tree

			// Evaluate
			QueryEvaluator qe = QueryEvaluator(*pkb);
			QUERY_RESULT result = qe.evaluateQuery(processed_synonyms, processed_clauses);
			STRING_RESULT result_string = ResultListManager::getStringValues(result);
			STRING_RESULT correct_result = "1, 2, 3, 4";

			Logger::WriteMessage(result_string.c_str());
			Assert::IsTrue(result_string.compare(correct_result) == 0);
		}
		
		TEST_METHOD(evaluateQuery_SelectAFollows1A_ReturnsEmpty)
		{ 
			// Query: "assign a; Select a such that Follows(1,a)"
			// Get processed_synonyms and processed clauses
			QueryNode assign_node = QueryNode();
			assign_node.setSynonymNode({ QuerySynonymType::assign }, "a");
			std::unordered_map<std::string, QueryNode> processed_synonyms = { {"a", assign_node} };

			QueryNode child1 = QueryNode();
			child1.setSynonymNode({ QuerySynonymType::assign }, "a");
			QueryNode child2 = QueryNode();
			child2.setNodeType({ QueryNodeType::such_that });
			QueryNode child_child1 = QueryNode();
			child_child1.setNodeType({ QueryNodeType::follows });
			QueryNode child_child_child1 = QueryNode();
			child_child_child1.setIntegerNode(1);
			QueryNode child_child_child2 = QueryNode();
			child_child_child2.setSynonymNode({ QuerySynonymType::assign }, "a");
			QueryNode child_child1_children[] = { child_child_child1, child_child_child2 };
			child_child1.setChildren(child_child1_children, 2);
			QueryNode child2_children[] = { child_child1 };
			child2.setChildren(child2_children, 1);

			QueryNode root = QueryNode();
			root.setNodeType({ QueryNodeType::select });
			QueryNode root_children[] = { child1, child2 };
			root.setChildren(root_children, 2);

			QueryNode processed_clauses = root; //stores root node of the tree

			// Evaluate
			QueryEvaluator qe = QueryEvaluator(*pkb);
			QUERY_RESULT result = qe.evaluateQuery(processed_synonyms, processed_clauses);
			STRING_RESULT result_string = ResultListManager::getStringValues(result);
			STRING_RESULT correct_result = "";

			Logger::WriteMessage(result_string.c_str());
			Assert::IsTrue(result_string.compare(correct_result) == 0);
		}

		TEST_METHOD(evaluateQuery_SelectPnFollows2_3_ReturnsPn)
		{ 
			// Query: "print pn; Select pn such that Follows(2,3)"
			// Get processed_synonyms and processed clauses
			QueryNode print_node = QueryNode();
			print_node.setSynonymNode({ QuerySynonymType::print }, "pn");
			std::unordered_map<std::string, QueryNode> processed_synonyms = { {"pn", print_node} };

			QueryNode child1 = QueryNode();
			child1.setSynonymNode({ QuerySynonymType::print }, "pn");
			QueryNode child2 = QueryNode();
			child2.setNodeType({ QueryNodeType::such_that });
			QueryNode child_child1 = QueryNode();
			child_child1.setNodeType({ QueryNodeType::follows });
			QueryNode child_child_child1 = QueryNode();
			child_child_child1.setIntegerNode(2);
			QueryNode child_child_child2 = QueryNode();
			child_child_child2.setIntegerNode(3);
			QueryNode child_child1_children[] = { child_child_child1, child_child_child2 };
			child_child1.setChildren(child_child1_children, 2);
			QueryNode child2_children[] = { child_child1 };
			child2.setChildren(child2_children, 1);

			QueryNode root = QueryNode();
			root.setNodeType({ QueryNodeType::select });
			QueryNode root_children[] = { child1, child2 };
			root.setChildren(root_children, 2);

			QueryNode processed_clauses = root; //stores root node of the tree

			// Evaluate
			QueryEvaluator qe = QueryEvaluator(*pkb);
			QUERY_RESULT result = qe.evaluateQuery(processed_synonyms, processed_clauses);
			STRING_RESULT result_string = ResultListManager::getStringValues(result);
			STRING_RESULT correct_result = "1, 2, 3, 4, 5";
			
			Logger::WriteMessage(result_string.c_str());
			Assert::IsTrue(result_string.compare(correct_result) == 0);
		}

		TEST_METHOD(evaluateQuery_SelectPnFollows2_4_ReturnsEmpty)
		{
			// Query: "print pn; Select pn such that Follows(2,3)"
			// Get processed_synonyms and processed clauses
			QueryNode print_node = QueryNode();
			print_node.setSynonymNode({ QuerySynonymType::print }, "pn");
			std::unordered_map<std::string, QueryNode> processed_synonyms = { {"pn", print_node} };

			QueryNode child1 = QueryNode();
			child1.setSynonymNode({ QuerySynonymType::print }, "pn");
			QueryNode child2 = QueryNode();
			child2.setNodeType({ QueryNodeType::such_that });
			QueryNode child_child1 = QueryNode();
			child_child1.setNodeType({ QueryNodeType::follows });
			QueryNode child_child_child1 = QueryNode();
			child_child_child1.setIntegerNode(2);
			QueryNode child_child_child2 = QueryNode();
			child_child_child2.setIntegerNode(4);
			QueryNode child_child1_children[] = { child_child_child1, child_child_child2 };
			child_child1.setChildren(child_child1_children, 2);
			QueryNode child2_children[] = { child_child1 };
			child2.setChildren(child2_children, 1);

			QueryNode root = QueryNode();
			root.setNodeType({ QueryNodeType::select });
			QueryNode root_children[] = { child1, child2 };
			root.setChildren(root_children, 2);

			QueryNode processed_clauses = root; //stores root node of the tree

			// Evaluate
			QueryEvaluator qe = QueryEvaluator(*pkb);
			QUERY_RESULT result = qe.evaluateQuery(processed_synonyms, processed_clauses);
			STRING_RESULT result_string = ResultListManager::getStringValues(result);
			STRING_RESULT correct_result = "";

			Logger::WriteMessage(result_string.c_str());
			Assert::IsTrue(result_string.compare(correct_result) == 0);
		}

		TEST_METHOD(evaluateQuery_SelectVFollowsT1_S_ReturnsV)
		{
			// Query: "variable v; Select v such that FollowsT(1,s)"
			// Get processed_synonyms and processed clauses
			QueryNode variable_node = QueryNode();
			variable_node.setSynonymNode({ QuerySynonymType::variable }, "v");
			QueryNode stmt_node = QueryNode();
			stmt_node.setSynonymNode({ QuerySynonymType::stmt }, "s");
			std::unordered_map<std::string, QueryNode> processed_synonyms = { {"v", variable_node}, {"s", stmt_node} };

			QueryNode child1 = QueryNode();
			child1.setSynonymNode({ QuerySynonymType::variable }, "v");
			QueryNode child2 = QueryNode();
			child2.setNodeType({ QueryNodeType::such_that });
			QueryNode child_child1 = QueryNode();
			child_child1.setNodeType({ QueryNodeType::followsT });
			QueryNode child_child_child1 = QueryNode();
			child_child_child1.setIntegerNode(1);
			QueryNode child_child_child2 = QueryNode();
			child_child_child2.setSynonymNode({ QuerySynonymType::stmt }, "s");
			QueryNode child_child1_children[] = { child_child_child1, child_child_child2 };
			child_child1.setChildren(child_child1_children, 2);
			QueryNode child2_children[] = { child_child1 };
			child2.setChildren(child2_children, 1);

			QueryNode root = QueryNode();
			root.setNodeType({ QueryNodeType::select });
			QueryNode root_children[] = { child1, child2 };
			root.setChildren(root_children, 2);

			QueryNode processed_clauses = root; //stores root node of the tree

			// Evaluate
			QueryEvaluator qe = QueryEvaluator(*pkb);
			QUERY_RESULT result;
			STRING_RESULT result_string;

			try {
				result = qe.evaluateQuery(processed_synonyms, processed_clauses);
				result_string = ResultListManager::getStringValues(result);
			}
			catch (const char* msg) {
				Logger::WriteMessage("Evaluate exception caught");
			}
			STRING_RESULT correct_result = "a, a, a, a, b, b, b, b, c, c, c, c, d, d, d, d, e, e, e, e";
			
			Logger::WriteMessage(result_string.c_str());
			Assert::IsTrue(result_string.compare(correct_result) == 0);
		}

		TEST_METHOD(evaluateQuery_SelectPnFollowsT1_Pn_Returns2)
		{
			// Query: "print pn; Select pn such that FollowsT(1,pn)"
			// Get processed_synonyms and processed clauses
			QueryNode variable_node = QueryNode();
			variable_node.setSynonymNode({ QuerySynonymType::print }, "pn");
			std::unordered_map<std::string, QueryNode> processed_synonyms = { {"pn", variable_node} };

			QueryNode child1 = QueryNode();
			child1.setSynonymNode({ QuerySynonymType::print }, "pn");
			QueryNode child2 = QueryNode();
			child2.setNodeType({ QueryNodeType::such_that });
			QueryNode child_child1 = QueryNode();
			child_child1.setNodeType({ QueryNodeType::followsT });
			QueryNode child_child_child1 = QueryNode();
			child_child_child1.setIntegerNode(1);
			QueryNode child_child_child2 = QueryNode();
			child_child_child2.setSynonymNode({ QuerySynonymType::print }, "pn");
			QueryNode child_child1_children[] = { child_child_child1, child_child_child2 };
			child_child1.setChildren(child_child1_children, 2);
			QueryNode child2_children[] = { child_child1 };
			child2.setChildren(child2_children, 1);

			QueryNode root = QueryNode();
			root.setNodeType({ QueryNodeType::select });
			QueryNode root_children[] = { child1, child2 };
			root.setChildren(root_children, 2);

			QueryNode processed_clauses = root; //stores root node of the tree

			// Evaluate
			QueryEvaluator qe = QueryEvaluator(*pkb);
			QUERY_RESULT result;
			STRING_RESULT result_string;

			try {
				result = qe.evaluateQuery(processed_synonyms, processed_clauses);
				result_string = ResultListManager::getStringValues(result);
			}
			catch (const char* msg) {
				Logger::WriteMessage("Evaluate exception caught");
			}
			STRING_RESULT correct_result = "2, 3, 4, 5";

			Logger::WriteMessage(result_string.c_str());
			Assert::IsTrue(result_string.compare(correct_result) == 0);
		}

		TEST_METHOD(evaluateQuery_SelectS2FollowsTS1_S2_Returns2)
		{
			// Query: "stmt s1, s2; Select s2 such that FollowsT(s1,s2)"
			// Get processed_synonyms and processed clauses
			QueryNode s1_node = QueryNode();
			s1_node.setSynonymNode({ QuerySynonymType::stmt }, "s1");
			QueryNode s2_node = QueryNode();
			s2_node.setSynonymNode({ QuerySynonymType::stmt }, "s2");
			std::unordered_map<std::string, QueryNode> processed_synonyms = { {"s1", s1_node}, {"s2", s2_node} };

			QueryNode child1 = QueryNode();
			child1.setSynonymNode({ QuerySynonymType::print }, "s2");
			QueryNode child2 = QueryNode();
			child2.setNodeType({ QueryNodeType::such_that });
			QueryNode child_child1 = QueryNode();
			child_child1.setNodeType({ QueryNodeType::followsT });
			QueryNode child_child_child1 = QueryNode();
			child_child_child1.setSynonymNode({ QuerySynonymType::stmt }, "s1");
			QueryNode child_child_child2 = QueryNode();
			child_child_child2.setSynonymNode({ QuerySynonymType::stmt }, "s2");
			QueryNode child_child1_children[] = { child_child_child1, child_child_child2 };
			child_child1.setChildren(child_child1_children, 2);
			QueryNode child2_children[] = { child_child1 };
			child2.setChildren(child2_children, 1);

			QueryNode root = QueryNode();
			root.setNodeType({ QueryNodeType::select });
			QueryNode root_children[] = { child1, child2 };
			root.setChildren(root_children, 2);

			QueryNode processed_clauses = root; //stores root node of the tree

			// Evaluate
			QueryEvaluator qe = QueryEvaluator(*pkb);
			QUERY_RESULT result;
			STRING_RESULT result_string;

			try {
				result = qe.evaluateQuery(processed_synonyms, processed_clauses);
				result_string = ResultListManager::getStringValues(result);
			}
			catch (const char* msg) {
				Logger::WriteMessage("Evaluate exception caught");
			}
			STRING_RESULT correct_result = "2, 3, 3, 4, 4, 4, 5, 5, 5, 5";

			Logger::WriteMessage(result_string.c_str());
			Assert::IsTrue(result_string.compare(correct_result) == 0);
		}

		TEST_METHOD(evaluateQuery_SelectVFollowsTPn_3_ReturnsV)
		{
			// Query: "print pn; variable v; Select v such that FollowsT(pn,3)"
			// Get processed_synonyms and processed clauses
			QueryNode print_node = QueryNode();
			print_node.setSynonymNode({ QuerySynonymType::print }, "pn");
			QueryNode variable_node = QueryNode();
			variable_node.setSynonymNode({ QuerySynonymType::variable }, "v");
			std::unordered_map<std::string, QueryNode> processed_synonyms = { {"pn", print_node}, {"v", variable_node} };

			QueryNode child1 = QueryNode();
			child1.setSynonymNode({ QuerySynonymType::variable }, "v");
			QueryNode child2 = QueryNode();
			child2.setNodeType({ QueryNodeType::such_that });
			QueryNode child_child1 = QueryNode();
			child_child1.setNodeType({ QueryNodeType::followsT });
			QueryNode child_child_child1 = QueryNode();
			child_child_child1.setSynonymNode({ QuerySynonymType::print }, "pn");
			QueryNode child_child_child2 = QueryNode();
			child_child_child2.setIntegerNode(3);
			QueryNode child_child1_children[] = { child_child_child1, child_child_child2 };
			child_child1.setChildren(child_child1_children, 2);
			QueryNode child2_children[] = { child_child1 };
			child2.setChildren(child2_children, 1);

			QueryNode root = QueryNode();
			root.setNodeType({ QueryNodeType::select });
			QueryNode root_children[] = { child1, child2 };
			root.setChildren(root_children, 2);

			QueryNode processed_clauses = root; //stores root node of the tree

			// Evaluate
			QueryEvaluator qe = QueryEvaluator(*pkb);
			QUERY_RESULT result;
			STRING_RESULT result_string;

			try {
				result = qe.evaluateQuery(processed_synonyms, processed_clauses);
				result_string = ResultListManager::getStringValues(result);
			}
			catch (const char* msg) {
				Logger::WriteMessage("Evaluate exception caught");
			}
			STRING_RESULT correct_result = "a, a, b, b, c, c, d, d, e, e";

			Logger::WriteMessage(result_string.c_str());
			Assert::IsTrue(result_string.compare(correct_result) == 0);
		}

		TEST_METHOD(evaluateQuery_SelectSParent1_2_ReturnsEmpty)
		{
			// Query: "stmt s; Select s such that Parent(1,2)"
			// Get processed_synonyms and processed clauses
			QueryNode variable_node = QueryNode();
			variable_node.setSynonymNode({ QuerySynonymType::stmt }, "s");
			std::unordered_map<std::string, QueryNode> processed_synonyms = { {"s", variable_node} };

			QueryNode child1 = QueryNode();
			child1.setSynonymNode({ QuerySynonymType::stmt }, "ss");
			QueryNode child2 = QueryNode();
			child2.setNodeType({ QueryNodeType::such_that });
			QueryNode child_child1 = QueryNode();
			child_child1.setNodeType({ QueryNodeType::parent });
			QueryNode child_child_child1 = QueryNode();
			child_child_child1.setIntegerNode(1);
			QueryNode child_child_child2 = QueryNode();
			child_child_child2.setIntegerNode(2);
			QueryNode child_child1_children[] = { child_child_child1, child_child_child2 };
			child_child1.setChildren(child_child1_children, 2);
			QueryNode child2_children[] = { child_child1 };
			child2.setChildren(child2_children, 1);

			QueryNode root = QueryNode();
			root.setNodeType({ QueryNodeType::select });
			QueryNode root_children[] = { child1, child2 };
			root.setChildren(root_children, 2);

			QueryNode processed_clauses = root; //stores root node of the tree

			// Evaluate
			QueryEvaluator qe = QueryEvaluator(*pkb);
			QUERY_RESULT result = qe.evaluateQuery(processed_synonyms, processed_clauses);
			STRING_RESULT result_string = ResultListManager::getStringValues(result);
			STRING_RESULT correct_result = "";

			Logger::WriteMessage(result_string.c_str());
			Assert::IsTrue(result_string.compare(correct_result) == 0);
		}

		TEST_METHOD(evaluateQuery_SelectPnParentT4_Pn_ReturnsEmpty)
		{
			// Query: "print pn; Select pn such that ParentT(4,pn)"
			// Get processed_synonyms and processed clauses
			QueryNode variable_node = QueryNode();
			variable_node.setSynonymNode({ QuerySynonymType::print }, "pn");
			std::unordered_map<std::string, QueryNode> processed_synonyms = { {"pn", variable_node} };

			QueryNode child1 = QueryNode();
			child1.setSynonymNode({ QuerySynonymType::print }, "pn");
			QueryNode child2 = QueryNode();
			child2.setNodeType({ QueryNodeType::such_that });
			QueryNode child_child1 = QueryNode();
			child_child1.setNodeType({ QueryNodeType::parentT });
			QueryNode child_child_child1 = QueryNode();
			child_child_child1.setIntegerNode(4);
			QueryNode child_child_child2 = QueryNode();
			child_child_child2.setSynonymNode({QuerySynonymType::print}, "pn");
			QueryNode child_child1_children[] = { child_child_child1, child_child_child2 };
			child_child1.setChildren(child_child1_children, 2);
			QueryNode child2_children[] = { child_child1 };
			child2.setChildren(child2_children, 1);

			QueryNode root = QueryNode();
			root.setNodeType({ QueryNodeType::select });
			QueryNode root_children[] = { child1, child2 };
			root.setChildren(root_children, 2);

			QueryNode processed_clauses = root; //stores root node of the tree

			// Evaluate
			QueryEvaluator qe = QueryEvaluator(*pkb);
			QUERY_RESULT result = qe.evaluateQuery(processed_synonyms, processed_clauses);
			STRING_RESULT result_string = ResultListManager::getStringValues(result);
			STRING_RESULT correct_result = "";

			Logger::WriteMessage(result_string.c_str());
			Assert::IsTrue(result_string.compare(correct_result) == 0);
		}
	};
}
