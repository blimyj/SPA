#include <typeinfo>

#include "stdafx.h"
#include "CppUnitTest.h"

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

#include "Parser.h"
#include "PKB.h"

typedef std::shared_ptr<PKB> PKB_PTR;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting {
	TEST_CLASS(TestParser) {
	public:
		/*
		procedure main {
			a = 1;
			print b;
			read c;
		}
		*/

		PKB_PTR pkb;
		/*
		// Meant to initialise expected pkb and actual pkb. 
		TEST_METHOD_INITIALIZE(PKBInitialize) {
			// PKB
			PKBBuilder builder;

			// Make ProgramNode
			PROGRAM_NODE_PTR prog1 = std::make_shared<ProgramNode>();
			builder.setProgramNode(prog1);

			// Make StatementListNode
			STMT_LIST_NODE_PTR sl1 = std::make_shared<StatementListNode>();
			builder.addStatementListNode(sl1);

			// Make ProcedureNode Main
			PROC_NODE_PTR prc1 = std::make_shared<ProcedureNode>();
			prc1->setProcedureName("main");
			prc1->setProcedureStatementListNode(sl1);
			builder.addProcedureNode(prc1);

			prog1->addProcedureNode(prc1);
			
			// Make VariableNodes a, b, c
			VAR_NODE_PTR v1 = std::make_shared<VariableNode>();
			v1->setVariableName("a");
			VAR_NODE_PTR v2 = std::make_shared<VariableNode>();
			v2->setVariableName("b");
			VAR_NODE_PTR v3 = std::make_shared<VariableNode>();
			v3->setVariableName("c");

			builder.addVariableNode(v1);
			builder.addVariableNode(v2);
			builder.addVariableNode(v3);

			// Make ConstNode 1
			CONSTANT_NODE_PTR c1 = std::make_shared<ConstantNode>();
			c1->setValue("1");

			builder.addConstantNode(c1);

			// Make ExpressionNode
			EXPR_NODE_PTR e1 = std::make_shared<ExpressionNode>();
			e1->setExpressionType(EXPR_TYPE::undefined);

			// Make AssignNode
			ASSIGN_NODE_PTR a1 = std::make_shared<AssignNode>();
			a1->setStatementNumber(1);
			a1->setVariableNode(v1);
			a1->setExpressionNode(e1);

			builder.addAssignNode(a1);

			// Make PrintNode
			PRINT_NODE_PTR p1 = std::make_shared<PrintNode>();
			p1->setStatementNumber(2);
			p1->setVariableNode(v2);
			
			builder.addPrintNode(p1);
			
			// Make ReadNode
			READ_NODE_PTR r1 = std::make_shared<ReadNode>();
			r1->setStatementNumber(3);
			r1->setVariableNode(v3);

			builder.addReadNode(r1);

			// Make StatementNode (1-3)
			StatementNode s1;
			s1.setStatementNumber(1);
			StatementNode s2;
			s2.setStatementNumber(2);
			StatementNode s3;
			s3.setStatementNumber(3);
			STMT_NODE_PTR s1ptr = std::make_shared<StatementNode>(s1);
			STMT_NODE_PTR s2ptr = std::make_shared<StatementNode>(s2);
			STMT_NODE_PTR s3ptr = std::make_shared<StatementNode>(s3);
			builder.addStatementNode(s1ptr);
			builder.addStatementNode(s2ptr);
			builder.addStatementNode(s3ptr);

			// Add StatementNode Pointers to StatementListNode
			sl1->addStatementNode(s1ptr);
			sl1->addStatementNode(s2ptr);
			sl1->addStatementNode(s3ptr);

			pkb = std::make_shared<PKB>(builder.build());

			Parser parser = Parser();
			actual_pkb =
				std::make_shared<PKB>(parser.parseFile("../UnitTesting/Parser/TestParser-1.txt"));
		}
		*/

		// For testing if file path is correct
		bool is_file_exist(const char* fileName)
		{
			std::ifstream infile(fileName);
			return infile.good();
		}
		
		// Test method to check if parser creates a program node.
		TEST_METHOD(makeSimpleAst) {
			Parser parser = Parser();
			PKB_PTR actual_pkb =
				std::make_shared<PKB>(parser.parseFile("../UnitTesting/Parser/TestParser-1.txt"));

			// Check program node is made
			PROGRAM_NODE_PTR actual_prog_node = actual_pkb->getProgramNode();
			PROGRAM_NODE_PTR prog_node = std::make_shared<ProgramNode>();
			Assert::IsTrue(typeid(prog_node) == typeid(actual_prog_node));

			// Check procedure list is made, with correct procedure name
			PROC_NODE_PTR_LIST actual_proc_list = actual_prog_node->getProcedureNodeList();
			PROC_NODE_PTR actual_proc_node = actual_proc_list.at(0);
			Assert::IsTrue(actual_proc_node->getProcedureName() == "main");

			// Check statementlist is made with 3 statements(children)
			STMT_LIST_NODE_PTR actual_stmtlist_node = actual_proc_node->getProcedureStatementListNode();
			STMT_NODE_PTR_LIST actual_stmt_node_list = actual_stmtlist_node->getStatementNodeList();
			Assert::IsTrue(actual_stmt_node_list.size() == 3);

			// Check assign node validity (a=1)
			AssignNode* actual_assign_node = static_cast<AssignNode*>(actual_stmt_node_list.at(0).get());
			VAR_NODE_PTR actual_var1_node = actual_assign_node->getVariableNode();
			EXPR_NODE_PTR actual_expr_node = actual_assign_node->getExpressionNode();
			AST_NODE_PTR temp_const_node = actual_expr_node->getLeftAstNode();
			ConstantNode* actual_const_node = static_cast<ConstantNode*>(temp_const_node.get());
			EXPR_TYPE actual_expr_type = actual_expr_node->getExpressionType();
			Assert::IsTrue("a" == actual_var1_node->getVariableName());
			Assert::IsTrue(EXPR_TYPE::none == actual_expr_type);
			Assert::IsTrue("1" == actual_const_node->getValue());
			Assert::IsTrue(1 == actual_assign_node->getStatementNumber());

			// Check print node (print b)
			PrintNode* actual_print_node = static_cast<PrintNode*>(actual_stmt_node_list.at(1).get());
			VAR_NODE_PTR actual_var2_node = actual_print_node->getVariableNode();
			Assert::IsTrue("b" == actual_var2_node->getVariableName());
			Assert::IsTrue(2 == actual_print_node->getStatementNumber());

			// Check read node (read c)
			ReadNode* actual_read_node = static_cast<ReadNode*>(actual_stmt_node_list.at(2).get());
			VAR_NODE_PTR actual_var3_node = actual_read_node->getVariableNode();
			Assert::IsTrue("c" == actual_var3_node->getVariableName());
			Assert::IsTrue(3 == actual_read_node->getStatementNumber());
		}


	};
}