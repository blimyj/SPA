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
		TEST_METHOD(TestBasicProcedure)
		{	
			ParserPrintTree printer;
			Parser parser = Parser();
			std::shared_ptr <PKB> pkb = 
				std::make_shared<PKB> (parser.parseFile("../UnitTesting/Parser/TestParser-1.txt"));			
			AST_NODE_PTR parent_node = pkb->getProcedures().at(0);
			
			/*
			std::ofstream actualOutput;
			actualOutput.open("../UnitTesting/Parser/ActualOutput.txt", std::ofstream::trunc);
			actualOutput << printer.parserPrintTree(parent_node);
			actualOutput.close();
			*/

			std::string actual = printer.parserPrintTree(parent_node);

			std::ifstream infile{ "../UnitTesting/Parser/TestParser-1-out.txt" };
			std::string expected{ std::istreambuf_iterator<char>(infile), std::istreambuf_iterator<char>() };
			infile.close();

			Assert::IsTrue(actual == expected);

			
		}

	};
}