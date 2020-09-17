#include "stdafx.h"
#include "CppUnitTest.h"
#include "../source/QueryEvaluator.h"
#include "../source/PKBStub.h"
#include "../source/QueryNode.h"
#include "../source/QueryNodeType.h"
#include "../source/PKB/ASTNode/StatementNode.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestQueryEvaluator)
	{
	public:
		TEST_METHOD(processQuery_ValidQuery_Success)
		{
			//PKBStub fills PKB with some variables already
			PKBStub stub = PKBStub();
			PKB pkb = stub.addVariables();

			// Query: "Variable v; Select v"
			// Get processed_synonyms and processed clauses
			QueryNode variable_node = QueryNode();
			variable_node.setSynonymNode({ QuerySynonymType::variable }, "v");
			std::unordered_map<std::string, QueryNode> processed_synonyms = { {"v", variable_node} };

			QueryNode child1 = QueryNode();
			child1.setNodeType({ QueryNodeType::select });
			QueryNode child2 = QueryNode();
			child2.setSynonymNode({ QuerySynonymType::variable }, "v");
			QueryNode child1_children[] = { child2 };
			child1.setChildren(child1_children);

			QueryNode processed_clauses = child1; //stores root node of the tree


			QueryEvaluator qe = QueryEvaluator(pkb);
			QUERY_RESULT result = qe.evaluateQuery(processed_synonyms, processed_clauses);
			QUERY_RESULT correct_result = "C++ god, Help, me";
			Assert::IsTrue(result.compare(correct_result) == 0);
		}
		
		TEST_METHOD(processQuery_ValidQuery2_Success)
		{
			/*
			procedure main {
				print a;
				print b;
				print c;
				print d;
				print e;
			}
			*/
			// PKB
			PKBBuilder builder;
			builder.addVariableNode(std::make_shared<VariableNode>("a"));
			builder.addVariableNode(std::make_shared<VariableNode>("b"));
			builder.addVariableNode(std::make_shared<VariableNode>("c"));
			builder.addVariableNode(std::make_shared<VariableNode>("d"));
			builder.addVariableNode(std::make_shared<VariableNode>("e"));

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
			PKB pkb = builder.build();
			
			// Query: "stmt s1, s2; variable v; Select v such that Follows(s1,s2)"
			// Get processed_synonyms and processed clauses
			QueryNode variable_node = QueryNode();
			variable_node.setSynonymNode({ QuerySynonymType::variable }, "v");
			QueryNode s1_node = QueryNode();
			variable_node.setSynonymNode({ QuerySynonymType::stmt }, "s1");
			QueryNode s2_node = QueryNode();
			variable_node.setSynonymNode({ QuerySynonymType::stmt }, "s2");
			std::unordered_map<std::string, QueryNode> processed_synonyms = { {"v", variable_node}, {"s1", s1_node}, {"s2", s2_node} };

			QueryNode root = QueryNode();
			root.setNodeType({ QueryNodeType::select });
			QueryNode child1 = QueryNode();
			child1.setSynonymNode({ QuerySynonymType::variable }, "v");
			QueryNode child2 = QueryNode();
			child2.setNodeType({ QueryNodeType::such_that });
			QueryNode child_child1 = QueryNode();
			child_child1.setNodeType({ QueryNodeType::follows});
			QueryNode child_child_child1 = QueryNode();
			child_child_child1.setSynonymNode({ QuerySynonymType::stmt }, "s1");
			QueryNode child_child_child2 = QueryNode();
			child_child_child2.setSynonymNode({ QuerySynonymType::stmt }, "s2");
			QueryNode child_child1_children[] = { child_child_child1, child_child_child2 };
			child_child1.setChildren(child_child1_children);
			QueryNode child2_children[] = {child_child1};
			child2.setChildren(child2_children);
			QueryNode root_children[] = { child1, child2 };
			child1.setChildren(root_children);

			QueryNode processed_clauses = root; //stores root node of the tree

			// Evaluate
			QueryEvaluator qe = QueryEvaluator(pkb);
			QUERY_RESULT result = qe.evaluateQuery(processed_synonyms, processed_clauses);
			QUERY_RESULT correct_result = "a, b, c, d, e";
			Assert::IsTrue(result.compare(correct_result) == 0);
		}
	};
}