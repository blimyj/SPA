#include <typeinfo>

#include "stdafx.h"
#include "CppUnitTest.h"
#include "QueryPreProcessor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestQueryPreProcessor) {
	public:
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
		std::shared_ptr<> pkb;

		TEST_METHOD_INITIALIZE(QueryPreProcessorInitialize)
		{
			PKBBuilder b;
			b.addFollows(3, 4);
			b.addFollows(5, 6);
			b.addParent(1, 2);
			b.addParent(2, 3);
			b.addParent(2, 4);
			b.addParent(2, 5);
			b.addParent(2, 6);
			b.addUses("main", "x");
			b.addUses("main", "y");
			b.addUses(1, "x");
			b.addUses(1, "y");
			b.addUses(2, "y");
			b.addUses(6, "y");
			b.addModifies("main", "x");
			b.addModifies("main", "y");
			b.addModifies("main", "z");
			b.addModifies(1, "x");
			b.addModifies(2, "y");
			b.addModifies(3, "z");
			b.addModifies(2, "x");
			b.addModifies(2, "y");
			b.addModifies(2, "z");
			b.addModifies(3, "x");
			b.addModifies(4, "y");
			b.addModifies(5, "z");
			b.addModifies(6, "y");
			pkb = std::make_shared<PKB>(b.build());
		}

		/* Trim whitespace */
		TEST_METHOD(TrimWhitespaces) {

		}

		/* Validate general query structure */
		TEST_METHOD() {

		}

		/* Split query  */
		TEST_METHOD() {

		}

		/* Split declaration */
		TEST_METHOD() {

		}

		/* Validate declaration */
		TEST_METHOD() {

		}

		/* Parse declaration */
		TEST_METHOD() {
			// stmt s;
			std::string query1 = "stmt s;";

			// read re;
			// print pr;
			// while w;
			// if ifs;
			// assign a;
			// variable v;
			// constant c;
			// procedure p;
		}

		/* Create expression node */
		TEST_METHOD() {

		}

		/* Create argument node */
		TEST_METHOD() {

		}

		/* Create relationship node */
		TEST_METHOD() {

		}

		/* Create pattern node */
		TEST_METHOD() {

		}

		/* Validate general clause structure */
		TEST_METHOD() {

		}

		/* Check if synonym declared */
		TEST_METHOD() {

		}

		/* Validate relationship clause format */
		TEST_METHOD() {

		}

		/* Validate relationship clause arguments */
		TEST_METHOD() {

		}

		/* Validate pattern clause format */
		TEST_METHOD() {

		}

		/* Validate patternclause arguments */
		TEST_METHOD() {

		}

		/* Clause parsing*/
		TEST_METHOD() {

		}
	};
}