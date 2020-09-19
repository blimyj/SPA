#include <typeinfo>
#include <string>

#include "stdafx.h"
#include "CppUnitTest.h"
#include "../source/QueryPreProcessor.h"
#include "../source/QueryNode.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestQueryPreProcessor) {
	public:

		/* Split query  */
		TEST_METHOD(splitQuery_Valid_Success) {
			QueryPreProcessor qpp = QueryPreProcessor();

			SPLIT_QUERY split_base = qpp.splitQuery("stmt s; Select s");
			SPLIT_QUERY split_base_var1 = qpp.splitQuery(" stmt s; Select s");
			SPLIT_QUERY split_base_var2 = qpp.splitQuery("stmt s; Select s ");
			SPLIT_QUERY split_base_var3 = qpp.splitQuery(" stmt s; Select s ");
			SPLIT_QUERY split_base_var4 = qpp.splitQuery("  stmt s; Select s  ");

			SPLIT_QUERY correct_split_base;
			correct_split_base.push_back("stmt s");
			correct_split_base.push_back("Select s");

			Assert::IsTrue(split_base[0].compare(correct_split_base[0]) == 0);
			Assert::IsTrue(split_base[1].compare(correct_split_base[1]) == 0);

			Assert::IsTrue(split_base_var1[0].compare(correct_split_base[0]) == 0);
			Assert::IsTrue(split_base_var1[1].compare(correct_split_base[1]) == 0);

			Assert::IsTrue(split_base_var2[0].compare(correct_split_base[0]) == 0);
			Assert::IsTrue(split_base_var2[1].compare(correct_split_base[1]) == 0);

			Assert::IsTrue(split_base_var3[0].compare(correct_split_base[0]) == 0);
			Assert::IsTrue(split_base_var3[1].compare(correct_split_base[1]) == 0);

			Assert::IsTrue(split_base_var4[0].compare(correct_split_base[0]) == 0);
			Assert::IsTrue(split_base_var4[1].compare(correct_split_base[1]) == 0);
		}

		TEST_METHOD(splitQuery_Invalid_Success) {
			QueryPreProcessor qpp = QueryPreProcessor();

			SPLIT_QUERY split_base = qpp.splitQuery("");
			SPLIT_QUERY split_base_var1 = qpp.splitQuery(" ");
			SPLIT_QUERY split_base_var2 = qpp.splitQuery("stmt s;");
			SPLIT_QUERY split_base_var3 = qpp.splitQuery("Select s");
			SPLIT_QUERY split_base_var4 = qpp.splitQuery("stmt s; select s");
			SPLIT_QUERY split_base_var5 = qpp.splitQuery("test");

			Assert::IsTrue(split_base[0].compare("") == 0 && split_base[1].compare("") == 0);
			Assert::IsTrue(split_base_var1[0].compare("") == 0 && split_base_var1[1].compare("") == 0);
			Assert::IsTrue(split_base_var2[0].compare("") == 0 && split_base_var2[1].compare("") == 0);
			Assert::IsTrue(split_base_var3[0].compare("") == 0 && split_base_var3[1].compare("") == 0);
			Assert::IsTrue(split_base_var4[0].compare("") == 0 && split_base_var4[1].compare("") == 0);
			Assert::IsTrue(split_base_var5[0].compare("") == 0 && split_base_var5[1].compare("") == 0);
		}

		/* Parse declaration */
		TEST_METHOD(preProcessSynonyms_Valid_Success) {
			QueryPreProcessor qpp = QueryPreProcessor();
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

			Assert::IsTrue(0 == 0);
		}

		/* Parse clauses */
		TEST_METHOD(preProcessClauses_Valid_Success) {
			QueryPreProcessor qpp = QueryPreProcessor();

			Assert::IsTrue(0 == 0);
		}
	};
}