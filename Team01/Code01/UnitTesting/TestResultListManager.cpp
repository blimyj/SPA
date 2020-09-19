#include "stdafx.h"
#include "CppUnitTest.h"
#include "ResultListManager.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestResultListManager)
	{
	public:

		TEST_METHOD(merge_twoFilledLists_Filtered)
		{
			ResultList r1;
			r1.addColumn("a");
			r1.addColumn("s");
			r1.addColumn("x");
			r1.addRow({ {"a", "1"}, {"s", "3"}, {"x", "5"} });
			r1.addRow({ {"a", "1"}, {"s", "3"}, {"x", "6"} });
			r1.addRow({ {"a", "6"}, {"s", "4"}, {"x", "2"} });
			r1.addRow({ {"a", "6"}, {"s", "3"}, {"x", "7"} });
			r1.addRow({ {"a", "7"}, {"s", "3"}, {"x", "7"} });
			
			ResultList r2;
			r2.addColumn("x", { "5", "3", "4", "7" });
			r2.addColumn("m", { "3", "7", "3", "2" });
			
			ResultList result = ResultListManager::merge(r1, r2);
			for (auto row : result.getRowList()) {
				Logger::WriteMessage("Row: ");
				for (auto it : row) {
					std::string s = "{" + it.first + " : " + it.second + "} ";
					Logger::WriteMessage(s.c_str());
				}
				Logger::WriteMessage("\n");
			}

			Assert::IsTrue(result.getRowList().size() == 3);
		}

		TEST_METHOD(merge_OneEmptyOneFilledLists_Empty)
		{
			ResultList r1;
			r1.addColumn("a");
			r1.addColumn("s");
			r1.addColumn("x");
			r1.addRow({ {"a", "1"}, {"s", "3"}, {"x", "5"} });
			r1.addRow({ {"a", "1"}, {"s", "3"}, {"x", "6"} });
			r1.addRow({ {"a", "6"}, {"s", "4"}, {"x", "2"} });
			r1.addRow({ {"a", "6"}, {"s", "3"}, {"x", "7"} });
			r1.addRow({ {"a", "7"}, {"s", "3"}, {"x", "7"} });

			ResultList r2;

			ResultList result = ResultListManager::merge(r1, r2);
			for (auto row : result.getRowList()) {
				Logger::WriteMessage("Row: ");
				for (auto it : row) {
					std::string s = "{" + it.first + " : " + it.second + "} ";
					Logger::WriteMessage(s.c_str());
				}
				Logger::WriteMessage("\n");
			}

			Assert::IsTrue(result.getRowList().size() == r1.getRowList().size());
		}
	};
}