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
		PKB_PTR actual_pkb;
		/*
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
		
		TEST_METHOD(makeSimpleAst_makeProgram)
		{	
			PROGRAM_NODE_PTR expected_prog_node = pkb->getProgramNode();
			PROGRAM_NODE_PTR actual_prog_node = actual_pkb->getProgramNode();

			Assert::IsTrue(typeid(*expected_prog_node) == typeid(*actual_prog_node));
		}
		*/
		TEST_METHOD(makeSimpleAst_makeProcedure)
		{
			
			/*
			PROGRAM_NODE_PTR expected_prog_node = pkb->getProgramNode();
			PROGRAM_NODE_PTR actual_prog_node = actual_pkb->getProgramNode();
			*/
			
			// Make Trial ProgramNode'
			PKBBuilder builder;

			PROGRAM_NODE_PTR prog10 = std::make_shared<ProgramNode>();
			builder.setProgramNode(prog10);
			PROC_NODE_PTR proc10 = std::make_shared<ProcedureNode>();

			prog10->addProcedureNode(proc10);
			builder.addProcedureNode(proc10);
			PKB test_pkb = builder.build();

			PROGRAM_NODE_PTR test_prog = test_pkb.getProgramNode();
			PROC_NODE_PTR_LIST test_proc_list = test_prog->getProcedureNodeList();

			Assert::IsTrue(true);
		}

	};
}