#include <typeinfo>

#include "stdafx.h"
#include "CppUnitTest.h"
#include "TestParser.h"

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

#include "../source/Parser.h"
#include "../source/PKB.h"

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

		std::shared_ptr<PKB> pkb;
		
		TEST_METHOD_INITIALIZE(PKBInitialize) {
			// PKB
			PKBBuilder builder;

			// Make StatementListNode
			std::shared_ptr<StatementListNode> sl1 = std::make_shared<StatementListNode>();

			// Make ProcedureNode Main
			std::shared_ptr<ProcedureNode> prc1 = std::make_shared<ProcedureNode>();
			prc1->setProcedureName("main");
			prc1->setProcedureStatementListNode(sl1);
			
			// Make VariableNodes a, b, c
			std::shared_ptr<VariableNode> v1 = std::make_shared<VariableNode>();
			v1->setVariableName("a");
			std::shared_ptr<VariableNode> v2 = std::make_shared<VariableNode>();
			v2->setVariableName("b");
			std::shared_ptr<VariableNode> v3 = std::make_shared<VariableNode>();
			v3->setVariableName("c");

			builder.addVariableNode(v1);
			builder.addVariableNode(v2);
			builder.addVariableNode(v3);

			// Make ConstNode 1
			std::shared_ptr<ConstantNode> c1 = std::make_shared<ConstantNode>();
			c1->setValue("1");

			builder.addConstantNode(c1);

			// Make ExpressionNode
			std::shared_ptr<ExpressionNode> e1 = std::make_shared<ExpressionNode>();
			e1->setExpressionType(EXPR_TYPE::undefined);

			// Make AssignNode
			std::shared_ptr<AssignNode> a1 = std::make_shared<AssignNode>();
			a1->setStatementNumber(1);
			a1->setVariableNode(v1);
			a1->setExpressionNode(e1);

			builder.addAssignNode(a1);

			// Make PrintNode
			std::shared_ptr<PrintNode> p1 = std::make_shared<PrintNode>();
			p1->setStatementNumber(2);
			p1->setVariableNode(v2);
			
			builder.addPrintNode(p1);
			
			// Make ReadNode
			std::shared_ptr<ReadNode> r1 = std::make_shared<ReadNode>();
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
			std::shared_ptr<StatementNode> s1ptr = std::make_shared<StatementNode>(s1);
			std::shared_ptr<StatementNode> s2ptr = std::make_shared<StatementNode>(s2);
			std::shared_ptr<StatementNode> s3ptr = std::make_shared<StatementNode>(s3);
			builder.addStatementNode(s1ptr);
			builder.addStatementNode(s2ptr);
			builder.addStatementNode(s3ptr);

			// Add StatementNode Pointers to StatementListNode
			sl1->addStatementNode(s1ptr);
			sl1->addStatementNode(s2ptr);
			sl1->addStatementNode(s3ptr);

			pkb = std::make_shared<PKB>(builder.build());
		}
		
		TEST_METHOD(makeSimpleAst_checkProcedure_Valid_Success)
		{
			PKBInitialize();
			Parser parser = Parser();
			std::shared_ptr<PKB> actual_pkb =
				std::make_shared<PKB>(parser.parseFile("../UnitTesting/Parser/TestParser-1.txt"));
			
			PROC_NAME_LIST expected_list = pkb->getProcedureNameList();
			PROC_NAME_LIST actual_list = actual_pkb->getProcedureNameList();

			/*
			std::string actual_string;
			
			for (std::vector<std::string>::const_iterator i = actual_list.begin(); i != actual_list.end(); ++i)
				actual_string += *i + ' ';

			Logger::WriteMessage(actual_string.c_str());
			*/
			Assert::IsTrue(std::equal(expected_list.begin(), expected_list.end(), actual_list.begin()));
		}

		/*
		TEST_METHOD(testBasicProcedure)
		{
			ParserPrintTree printer;
			Parser parser = Parser();
			std::shared_ptr <PKB> pkb =
				std::make_shared<PKB> (parser.parseFile("../UnitTesting/Parser/TestParser-1.txt"));
			AST_NODE_PTR parent_node = pkb->getProcedures().at(0);

			std::string actual = printer.parserPrintTree(parent_node);

			std::ifstream infile{ "../UnitTesting/Parser/TestParser-1-out.txt" };
			std::string expected{ std::istreambuf_iterator<char>(infile), std::istreambuf_iterator<char>() };
			infile.close();

			Assert::IsTrue(actual == expected);

		}
		*/
	};
}