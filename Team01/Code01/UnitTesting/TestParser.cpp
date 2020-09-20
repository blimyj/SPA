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
				// For testing if file path is correct
		bool is_file_exist(const char* fileName)
		{
			std::ifstream infile(fileName);
			return infile.good();
		}

		/*
		procedure main {
			a = 1;
			print b;
			read c;
		}
		*/
		TEST_METHOD(makeSimpleAst_1) {
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

		/*
		procedure simple {
			x = a - b;
		}
		*/
		TEST_METHOD(makeSimpleAst_2) {
			Parser parser = Parser();
			PKB_PTR actual_pkb =
				std::make_shared<PKB>(parser.parseFile("../UnitTesting/Parser/TestParser-2.txt"));

			// Check program node is made
			PROGRAM_NODE_PTR actual_prog_node = actual_pkb->getProgramNode();
			PROGRAM_NODE_PTR prog_node = std::make_shared<ProgramNode>();
			Assert::IsTrue(typeid(prog_node) == typeid(actual_prog_node));

			// Check procedure list is made, with correct procedure name
			PROC_NODE_PTR_LIST actual_proc_list = actual_prog_node->getProcedureNodeList();
			PROC_NODE_PTR actual_proc_node = actual_proc_list.at(0);
			Assert::IsTrue(actual_proc_node->getProcedureName() == "simple");

			// Check statementlist is made with 1 statement(children)
			STMT_LIST_NODE_PTR actual_stmtlist_node = actual_proc_node->getProcedureStatementListNode();
			STMT_NODE_PTR_LIST actual_stmt_node_list = actual_stmtlist_node->getStatementNodeList();
			Assert::IsTrue(actual_stmt_node_list.size() == 1);

			// Check assign node validity (x = a - b)
			AssignNode* actual_assign_node = static_cast<AssignNode*>(actual_stmt_node_list.at(0).get());
			VAR_NODE_PTR actual_var1_node = actual_assign_node->getVariableNode();

			EXPR_NODE_PTR actual_expr_node = actual_assign_node->getExpressionNode();
			EXPR_TYPE actual_expr_type = actual_expr_node->getExpressionType();

			AST_NODE_PTR temp_var2_node = actual_expr_node->getLeftAstNode();
			VariableNode* actual_var2_node = static_cast<VariableNode*>(temp_var2_node.get());
			AST_NODE_PTR temp_var3_node = actual_expr_node->getRightAstNode();
			VariableNode* actual_var3_node = static_cast<VariableNode*>(temp_var3_node.get());

			Assert::IsTrue("x" == actual_var1_node->getVariableName());
			Assert::IsTrue(EXPR_TYPE::min == actual_expr_type);
			Assert::IsTrue("a" == actual_var2_node->getVariableName());
			Assert::IsTrue("b" == actual_var3_node->getVariableName());
			Assert::IsTrue(1 == actual_assign_node->getStatementNumber());
		}

	};
}