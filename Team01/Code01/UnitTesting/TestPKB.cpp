#include <typeinfo>

#include "stdafx.h"
#include "CppUnitTest.h"
#include "PKB.h"
#include "PKBBuilder.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting {
	
	TEST_CLASS(PKB) {
	public:
		TEST_METHOD(getAssigns) {
			PKBBuilder pkb_builder;
			VAR_NODE_PTR assign_var = std::make_shared<VariableNode>("assigned");
			VAR_NODE_PTR left_var = std::make_shared<VariableNode>("left");
			VAR_NODE_PTR right_var = std::make_shared<VariableNode>("right");
			EXPR_NODE_PTR expr = std::make_shared<ExpressionNode>(ExpressionTypeEnum::plus, left_var, right_var);
			ASSIGN_NODE_PTR assign = std::make_shared<AssignNode>(assign_var, expr);
			pkb_builder.addStatementNode(assign);
			ASSIGN_NODE_PTR_LIST list = pkb_builder.build().getAssigns();
			Assert::IsTrue(typeid(*assign) == typeid(*list.at(0)));
		}

	};
}