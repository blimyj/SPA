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
		TEST_METHOD(preProcessSynonyms_Single_Valid_Success) {
			QueryPreProcessor qpp = QueryPreProcessor();

			DECLARATIONS stmt = "stmt s";
			DECLARATIONS read = "read re";
			DECLARATIONS print = "print pr";
			DECLARATIONS whiles = "while w";
			DECLARATIONS ifs = "if ifs";
			DECLARATIONS assign = "assign a";
			DECLARATIONS variable = "variable v";
			DECLARATIONS constant = "constant c";
			DECLARATIONS procedure = "procedure p";

			PROCESSED_SYNONYMS proc_stmt = qpp.preProcessSynonyms(stmt);
			PROCESSED_SYNONYMS proc_read = qpp.preProcessSynonyms(read);
			PROCESSED_SYNONYMS proc_print = qpp.preProcessSynonyms(print);
			PROCESSED_SYNONYMS proc_while = qpp.preProcessSynonyms(whiles);
			PROCESSED_SYNONYMS proc_ifs = qpp.preProcessSynonyms(ifs);
			PROCESSED_SYNONYMS proc_assign = qpp.preProcessSynonyms(assign);
			PROCESSED_SYNONYMS proc_variable = qpp.preProcessSynonyms(variable);
			PROCESSED_SYNONYMS proc_constant = qpp.preProcessSynonyms(constant);
			PROCESSED_SYNONYMS proc_procedure = qpp.preProcessSynonyms(procedure);
			
			Assert::IsTrue(proc_stmt.at("s").getNodeType() == QueryNodeType::synonym);
			Assert::IsTrue(proc_stmt.at("s").getSynonymType() == QuerySynonymType::stmt);
			Assert::IsTrue(proc_stmt.at("s").getString().compare("s") == 0);

			Assert::IsTrue(proc_read.at("re").getNodeType() == QueryNodeType::synonym);
			Assert::IsTrue(proc_read.at("re").getSynonymType() == QuerySynonymType::read);
			Assert::IsTrue(proc_read.at("re").getString().compare("re") == 0);

			Assert::IsTrue(proc_print.at("pr").getNodeType() == QueryNodeType::synonym);
			Assert::IsTrue(proc_print.at("pr").getSynonymType() == QuerySynonymType::print);
			Assert::IsTrue(proc_print.at("pr").getString().compare("pr") == 0);

			Assert::IsTrue(proc_while.at("w").getNodeType() == QueryNodeType::synonym);
			Assert::IsTrue(proc_while.at("w").getSynonymType() == QuerySynonymType::whiles);
			Assert::IsTrue(proc_while.at("w").getString().compare("w") == 0);

			Assert::IsTrue(proc_ifs.at("ifs").getNodeType() == QueryNodeType::synonym);
			Assert::IsTrue(proc_ifs.at("ifs").getSynonymType() == QuerySynonymType::ifs);
			Assert::IsTrue(proc_ifs.at("ifs").getString().compare("ifs") == 0);

			Assert::IsTrue(proc_assign.at("a").getNodeType() == QueryNodeType::synonym);
			Assert::IsTrue(proc_assign.at("a").getSynonymType() == QuerySynonymType::assign);
			Assert::IsTrue(proc_assign.at("a").getString().compare("a") == 0);

			Assert::IsTrue(proc_variable.at("v").getNodeType() == QueryNodeType::synonym);
			Assert::IsTrue(proc_variable.at("v").getSynonymType() == QuerySynonymType::variable);
			Assert::IsTrue(proc_variable.at("v").getString().compare("v") == 0);

			Assert::IsTrue(proc_constant.at("c").getNodeType() == QueryNodeType::synonym);
			Assert::IsTrue(proc_constant.at("c").getSynonymType() == QuerySynonymType::constant);
			Assert::IsTrue(proc_constant.at("c").getString().compare("c") == 0);

			Assert::IsTrue(proc_procedure.at("p").getNodeType() == QueryNodeType::synonym);
			Assert::IsTrue(proc_procedure.at("p").getSynonymType() == QuerySynonymType::procedure);
			Assert::IsTrue(proc_procedure.at("p").getString().compare("p") == 0);
		}
		
		TEST_METHOD(preProcessSynonyms_Multiple_Single_Valid_Success) {
			QueryPreProcessor qpp = QueryPreProcessor();

			DECLARATIONS stmt = "stmt s1, s2, s3";
			DECLARATIONS read = "read re1, re2, re3";
			DECLARATIONS assign = "assign a1, a2, a3";

			PROCESSED_SYNONYMS proc_stmt = qpp.preProcessSynonyms(stmt);
			PROCESSED_SYNONYMS proc_read = qpp.preProcessSynonyms(read);
			PROCESSED_SYNONYMS proc_assign = qpp.preProcessSynonyms(assign);


			Assert::IsTrue(proc_stmt.at("s1").getNodeType() == QueryNodeType::synonym);
			Assert::IsTrue(proc_stmt.at("s1").getSynonymType() == QuerySynonymType::stmt);
			Assert::IsTrue(proc_stmt.at("s1").getString().compare("s1") == 0);
			Assert::IsTrue(proc_stmt.at("s2").getNodeType() == QueryNodeType::synonym);
			Assert::IsTrue(proc_stmt.at("s2").getSynonymType() == QuerySynonymType::stmt);
			Assert::IsTrue(proc_stmt.at("s2").getString().compare("s2") == 0);
			Assert::IsTrue(proc_stmt.at("s3").getNodeType() == QueryNodeType::synonym);
			Assert::IsTrue(proc_stmt.at("s3").getSynonymType() == QuerySynonymType::stmt);
			Assert::IsTrue(proc_stmt.at("s3").getString().compare("s3") == 0);

			Assert::IsTrue(proc_read.at("re1").getNodeType() == QueryNodeType::synonym);
			Assert::IsTrue(proc_read.at("re1").getSynonymType() == QuerySynonymType::read);
			Assert::IsTrue(proc_read.at("re1").getString().compare("re1") == 0);
			Assert::IsTrue(proc_read.at("re2").getNodeType() == QueryNodeType::synonym);
			Assert::IsTrue(proc_read.at("re2").getSynonymType() == QuerySynonymType::read);
			Assert::IsTrue(proc_read.at("re2").getString().compare("re2") == 0);
			Assert::IsTrue(proc_read.at("re3").getNodeType() == QueryNodeType::synonym);
			Assert::IsTrue(proc_read.at("re3").getSynonymType() == QuerySynonymType::read);
			Assert::IsTrue(proc_read.at("re3").getString().compare("re3") == 0);

			Assert::IsTrue(proc_assign.at("a1").getNodeType() == QueryNodeType::synonym);
			Assert::IsTrue(proc_assign.at("a1").getSynonymType() == QuerySynonymType::assign);
			Assert::IsTrue(proc_assign.at("a1").getString().compare("a1") == 0);
			Assert::IsTrue(proc_assign.at("a2").getNodeType() == QueryNodeType::synonym);
			Assert::IsTrue(proc_assign.at("a2").getSynonymType() == QuerySynonymType::assign);
			Assert::IsTrue(proc_assign.at("a2").getString().compare("a2") == 0);
			Assert::IsTrue(proc_assign.at("a3").getNodeType() == QueryNodeType::synonym);
			Assert::IsTrue(proc_assign.at("a3").getSynonymType() == QuerySynonymType::assign);
			Assert::IsTrue(proc_assign.at("a3").getString().compare("a3") == 0);
		}

		TEST_METHOD(preProcessSynonyms_Multiple_Different_Valid_Success) {
			QueryPreProcessor qpp = QueryPreProcessor();

			DECLARATIONS query = "stmt s; read re; while w; assign a; variable v;";

			PROCESSED_SYNONYMS proc_query = qpp.preProcessSynonyms(query);

			Assert::IsTrue(proc_query.at("s").getNodeType() == QueryNodeType::synonym);
			Assert::IsTrue(proc_query.at("s").getSynonymType() == QuerySynonymType::stmt);
			Assert::IsTrue(proc_query.at("s").getString().compare("s") == 0);

			Assert::IsTrue(proc_query.at("re").getNodeType() == QueryNodeType::synonym);
			Assert::IsTrue(proc_query.at("re").getSynonymType() == QuerySynonymType::read);
			Assert::IsTrue(proc_query.at("re").getString().compare("re") == 0);

			Assert::IsTrue(proc_query.at("w").getNodeType() == QueryNodeType::synonym);
			Assert::IsTrue(proc_query.at("w").getSynonymType() == QuerySynonymType::whiles);
			Assert::IsTrue(proc_query.at("w").getString().compare("w") == 0);

			Assert::IsTrue(proc_query.at("a").getNodeType() == QueryNodeType::synonym);
			Assert::IsTrue(proc_query.at("a").getSynonymType() == QuerySynonymType::assign);
			Assert::IsTrue(proc_query.at("a").getString().compare("a") == 0);

			Assert::IsTrue(proc_query.at("v").getNodeType() == QueryNodeType::synonym);
			Assert::IsTrue(proc_query.at("v").getSynonymType() == QuerySynonymType::variable);
			Assert::IsTrue(proc_query.at("v").getString().compare("v") == 0);
		}

		TEST_METHOD(preProcessSynonyms_Invalid_Success) {
			QueryPreProcessor qpp = QueryPreProcessor();

			DECLARATIONS q1 = "";
			DECLARATIONS q2 = "test";
			DECLARATIONS q3 = "   ";
			DECLARATIONS q4 = ";";
			DECLARATIONS q5 = "1";
			DECLARATIONS q6 = "stmt";
			DECLARATIONS q7 = "stmt s v";
			DECLARATIONS q8 = "stmt 1";
			DECLARATIONS q9 = "stmt 1,";

			PROCESSED_SYNONYMS proc_q1 = qpp.preProcessSynonyms(q1);
			PROCESSED_SYNONYMS proc_q2 = qpp.preProcessSynonyms(q2);
			PROCESSED_SYNONYMS proc_q3 = qpp.preProcessSynonyms(q3);
			PROCESSED_SYNONYMS proc_q4 = qpp.preProcessSynonyms(q4);
			PROCESSED_SYNONYMS proc_q5 = qpp.preProcessSynonyms(q5);
			PROCESSED_SYNONYMS proc_q6 = qpp.preProcessSynonyms(q6);
			PROCESSED_SYNONYMS proc_q7 = qpp.preProcessSynonyms(q7);
			PROCESSED_SYNONYMS proc_q8 = qpp.preProcessSynonyms(q8);
			PROCESSED_SYNONYMS proc_q9 = qpp.preProcessSynonyms(q9);

			Assert::IsTrue(proc_q1.empty());
			Assert::IsTrue(proc_q2.empty());
			Assert::IsTrue(proc_q3.empty());
			Assert::IsTrue(proc_q4.empty());
			Assert::IsTrue(proc_q5.empty());
			Assert::IsTrue(proc_q6.empty());
			Assert::IsTrue(proc_q7.empty());
			Assert::IsTrue(proc_q8.empty());
			Assert::IsTrue(proc_q9.empty());
		}

		/* Parse clauses */
		TEST_METHOD(preProcessClauses_Select_Valid_Success) {
			QueryPreProcessor qpp = QueryPreProcessor();

			DECLARATIONS d = "stmt s; read re; print pr; while w; if ifs; assign a; variable v; constant c; procedure p";
			PROCESSED_SYNONYMS proc_s = qpp.preProcessSynonyms(d);

			CLAUSES c1 = "Select s";
			CLAUSES c2 = "Select ifs";
			CLAUSES c3 = "Select v";

			PROCESSED_CLAUSES proc_c1 = qpp.preProcessClauses(proc_s, c1);
			PROCESSED_CLAUSES proc_c2 = qpp.preProcessClauses(proc_s, c2);
			PROCESSED_CLAUSES proc_c3 = qpp.preProcessClauses(proc_s, c3);

			Assert::IsTrue(proc_c1.getNodeType() == QueryNodeType::select);
			Assert::IsTrue(proc_c1.getChildren()[0].getNodeType() == QueryNodeType::synonym);
			Assert::IsTrue(proc_c1.getChildren()[0].getSynonymType() == QuerySynonymType::stmt);
			Assert::IsTrue(proc_c1.getChildren()[0].getString().compare("s") == 0);

			Assert::IsTrue(proc_c2.getNodeType() == QueryNodeType::select);
			Assert::IsTrue(proc_c2.getChildren()[0].getNodeType() == QueryNodeType::synonym);
			Assert::IsTrue(proc_c2.getChildren()[0].getSynonymType() == QuerySynonymType::ifs);
			Assert::IsTrue(proc_c2.getChildren()[0].getString().compare("ifs") == 0);

			Assert::IsTrue(proc_c3.getNodeType() == QueryNodeType::select);
			Assert::IsTrue(proc_c3.getChildren()[0].getNodeType() == QueryNodeType::synonym);
			Assert::IsTrue(proc_c3.getChildren()[0].getSynonymType() == QuerySynonymType::variable);
			Assert::IsTrue(proc_c3.getChildren()[0].getString().compare("v") == 0);
		}

		TEST_METHOD(preProcessClauses_Follows_Valid_Success) {
			QueryPreProcessor qpp = QueryPreProcessor();

			DECLARATIONS d = "stmt s; assign a;";
			PROCESSED_SYNONYMS proc_s = qpp.preProcessSynonyms(d);

			CLAUSES c1 = "Select s such that Follows(1, s)";
			CLAUSES c2 = "Select s such that Follows(s, a)";
			CLAUSES c3 = "Select s such that Follows(_, s)";

			PROCESSED_CLAUSES proc_c1 = qpp.preProcessClauses(proc_s, c1);
			PROCESSED_CLAUSES proc_c2 = qpp.preProcessClauses(proc_s, c2);
			PROCESSED_CLAUSES proc_c3 = qpp.preProcessClauses(proc_s, c3);

			Assert::IsTrue(proc_c1.getChildren()[1].getNodeType() == QueryNodeType::such_that);
			Assert::IsTrue(proc_c1.getChildren()[1].getChildren()[0].getNodeType() == QueryNodeType::follows);
			Assert::IsTrue(proc_c1.getChildren()[1].getChildren()[0].getChildren()[0].getNodeType() == QueryNodeType::integer);
			Assert::IsTrue(proc_c1.getChildren()[1].getChildren()[0].getChildren()[0].getInteger() == 1);
			Assert::IsTrue(proc_c1.getChildren()[1].getChildren()[0].getChildren()[1].getNodeType() == QueryNodeType::synonym);
			Assert::IsTrue(proc_c1.getChildren()[1].getChildren()[0].getChildren()[1].getSynonymType() == QuerySynonymType::stmt);
			Assert::IsTrue(proc_c1.getChildren()[1].getChildren()[0].getChildren()[1].getString().compare("s") == 0);

			Assert::IsTrue(proc_c2.getChildren()[1].getNodeType() == QueryNodeType::such_that);
			Assert::IsTrue(proc_c2.getChildren()[1].getChildren()[0].getNodeType() == QueryNodeType::follows);
			Assert::IsTrue(proc_c2.getChildren()[1].getChildren()[0].getChildren()[0].getNodeType() == QueryNodeType::synonym);
			Assert::IsTrue(proc_c2.getChildren()[1].getChildren()[0].getChildren()[0].getSynonymType() == QuerySynonymType::stmt);
			Assert::IsTrue(proc_c2.getChildren()[1].getChildren()[0].getChildren()[0].getString().compare("s") == 0);
			Assert::IsTrue(proc_c2.getChildren()[1].getChildren()[0].getChildren()[1].getNodeType() == QueryNodeType::synonym);
			Assert::IsTrue(proc_c2.getChildren()[1].getChildren()[0].getChildren()[1].getSynonymType() == QuerySynonymType::assign);
			Assert::IsTrue(proc_c2.getChildren()[1].getChildren()[0].getChildren()[1].getString().compare("a") == 0);

			Assert::IsTrue(proc_c3.getChildren()[1].getNodeType() == QueryNodeType::such_that);
			Assert::IsTrue(proc_c3.getChildren()[1].getChildren()[0].getNodeType() == QueryNodeType::follows);
			Assert::IsTrue(proc_c3.getChildren()[1].getChildren()[0].getChildren()[0].getNodeType() == QueryNodeType::wild_card);
			Assert::IsTrue(proc_c3.getChildren()[1].getChildren()[0].getChildren()[1].getNodeType() == QueryNodeType::synonym);
			Assert::IsTrue(proc_c3.getChildren()[1].getChildren()[0].getChildren()[1].getSynonymType() == QuerySynonymType::stmt);
			Assert::IsTrue(proc_c3.getChildren()[1].getChildren()[0].getChildren()[1].getString().compare("s") == 0);
		}

		TEST_METHOD(preProcessClauses_Uses_Valid_Success) {
			QueryPreProcessor qpp = QueryPreProcessor();

			DECLARATIONS d = "variable v; assign a; procedure p;";
			PROCESSED_SYNONYMS proc_s = qpp.preProcessSynonyms(d);

			CLAUSES c1 = "Select v such that UsesS(a, v)";
			CLAUSES c2 = "Select v such that UsesS(p, v)";
			CLAUSES c3 = "Select v such that UsesS(a, _)";
			CLAUSES c4 = "Select v such that UsesS(1, v)";
			CLAUSES c5 = "Select v such that UsesS(a, \"hello\")";


			PROCESSED_CLAUSES proc_c1 = qpp.preProcessClauses(proc_s, c1);
			PROCESSED_CLAUSES proc_c2 = qpp.preProcessClauses(proc_s, c2);
			PROCESSED_CLAUSES proc_c3 = qpp.preProcessClauses(proc_s, c3);
			PROCESSED_CLAUSES proc_c4 = qpp.preProcessClauses(proc_s, c4);
			PROCESSED_CLAUSES proc_c5 = qpp.preProcessClauses(proc_s, c5);

			Assert::IsTrue(proc_c1.getChildren()[1].getNodeType() == QueryNodeType::such_that);
			Assert::IsTrue(proc_c1.getChildren()[1].getChildren()[0].getNodeType() == QueryNodeType::usesS);
			Assert::IsTrue(proc_c1.getChildren()[1].getChildren()[0].getChildren()[0].getNodeType() == QueryNodeType::synonym);
			Assert::IsTrue(proc_c1.getChildren()[1].getChildren()[0].getChildren()[0].getSynonymType() == QuerySynonymType::assign);
			Assert::IsTrue(proc_c1.getChildren()[1].getChildren()[0].getChildren()[0].getString().compare("a") == 0);
			Assert::IsTrue(proc_c1.getChildren()[1].getChildren()[0].getChildren()[1].getNodeType() == QueryNodeType::synonym);
			Assert::IsTrue(proc_c1.getChildren()[1].getChildren()[0].getChildren()[1].getSynonymType() == QuerySynonymType::variable);
			Assert::IsTrue(proc_c1.getChildren()[1].getChildren()[0].getChildren()[1].getString().compare("v") == 0);

			Assert::IsTrue(proc_c2.getChildren()[1].getNodeType() == QueryNodeType::such_that);
			Assert::IsTrue(proc_c2.getChildren()[1].getChildren()[0].getNodeType() == QueryNodeType::usesS);
			Assert::IsTrue(proc_c2.getChildren()[1].getChildren()[0].getChildren()[0].getNodeType() == QueryNodeType::synonym);
			Assert::IsTrue(proc_c2.getChildren()[1].getChildren()[0].getChildren()[0].getSynonymType() == QuerySynonymType::procedure);
			Assert::IsTrue(proc_c2.getChildren()[1].getChildren()[0].getChildren()[0].getString().compare("p") == 0);
			Assert::IsTrue(proc_c2.getChildren()[1].getChildren()[0].getChildren()[1].getNodeType() == QueryNodeType::synonym);
			Assert::IsTrue(proc_c2.getChildren()[1].getChildren()[0].getChildren()[1].getSynonymType() == QuerySynonymType::variable);
			Assert::IsTrue(proc_c2.getChildren()[1].getChildren()[0].getChildren()[1].getString().compare("v") == 0);

			Assert::IsTrue(proc_c3.getChildren()[1].getNodeType() == QueryNodeType::such_that);
			Assert::IsTrue(proc_c3.getChildren()[1].getChildren()[0].getNodeType() == QueryNodeType::usesS);
			Assert::IsTrue(proc_c3.getChildren()[1].getChildren()[0].getChildren()[0].getNodeType() == QueryNodeType::synonym);
			Assert::IsTrue(proc_c3.getChildren()[1].getChildren()[0].getChildren()[0].getSynonymType() == QuerySynonymType::assign);
			Assert::IsTrue(proc_c3.getChildren()[1].getChildren()[0].getChildren()[0].getString().compare("a") == 0);
			Assert::IsTrue(proc_c3.getChildren()[1].getChildren()[0].getChildren()[1].getNodeType() == QueryNodeType::wild_card);

			Assert::IsTrue(proc_c4.getChildren()[1].getNodeType() == QueryNodeType::such_that);
			Assert::IsTrue(proc_c4.getChildren()[1].getChildren()[0].getNodeType() == QueryNodeType::usesS);
			Assert::IsTrue(proc_c4.getChildren()[1].getChildren()[0].getChildren()[0].getNodeType() == QueryNodeType::integer);
			Assert::IsTrue(proc_c4.getChildren()[1].getChildren()[0].getChildren()[0].getInteger() == 1);
			Assert::IsTrue(proc_c4.getChildren()[1].getChildren()[0].getChildren()[1].getNodeType() == QueryNodeType::synonym);
			Assert::IsTrue(proc_c4.getChildren()[1].getChildren()[0].getChildren()[1].getSynonymType() == QuerySynonymType::variable);
			Assert::IsTrue(proc_c4.getChildren()[1].getChildren()[0].getChildren()[1].getString().compare("v") == 0);

			Assert::IsTrue(proc_c5.getChildren()[1].getNodeType() == QueryNodeType::such_that);
			Assert::IsTrue(proc_c5.getChildren()[1].getChildren()[0].getNodeType() == QueryNodeType::usesS);
			Assert::IsTrue(proc_c5.getChildren()[1].getChildren()[0].getChildren()[0].getNodeType() == QueryNodeType::synonym);
			Assert::IsTrue(proc_c5.getChildren()[1].getChildren()[0].getChildren()[0].getSynonymType() == QuerySynonymType::assign);
			Assert::IsTrue(proc_c5.getChildren()[1].getChildren()[0].getChildren()[0].getString().compare("a") == 0);
			Assert::IsTrue(proc_c5.getChildren()[1].getChildren()[0].getChildren()[1].getNodeType() == QueryNodeType::ident);
			Assert::IsTrue(proc_c5.getChildren()[1].getChildren()[0].getChildren()[1].getString().compare("hello") == 0);
		}
	};
}