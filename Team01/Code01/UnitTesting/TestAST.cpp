#include <typeinfo>

#include "stdafx.h"
#include "CppUnitTest.h"
#include "PKB.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting {		
	
	TEST_CLASS(ASTNodeTest) {
	public:
		// TODO: Not make them dangle
		VAR_NODE_PTR var = std::make_shared<VariableNode>("Variable");
		PRINT_NODE_PTR print = std::make_shared<PrintNode>(var);
		TEST_METHOD(GetParent_WithNodes_True) {
			PrintNode* parent = static_cast<PrintNode*>(var->getParentNode().get());
			Assert::IsTrue(typeid(*print) == typeid(*parent));
		}

		TEST_METHOD(GetChildren_WithNodes_True) {
			VariableNode* child = static_cast<VariableNode*>(print->getChildrenNode().at(0).get());
			Assert::IsTrue(typeid(*var) == typeid(*child));
		}
	};

	TEST_CLASS(AssignNodeTest) {
	public:
		ASSIGN_NODE_PTR assign = std::make_shared<AssignNode>(nullptr, nullptr);
		EXPR_NODE_PTR expr = std::make_shared<ExpressionNode>(ExpressionTypeEnum::div, nullptr, nullptr);
		VAR_NODE_PTR var = std::make_shared<VariableNode>("Variable");

		TEST_METHOD(SetVariableNode_GetVariableNode_True) {
			assign->setVariableNode(var);
			VAR_NODE_PTR child = assign->getVariableNode();
			Assert::IsTrue(typeid(*var) == typeid(*child));
			
		}

		TEST_METHOD(SetExpressionNode_GetExpressionNode_True) {
			assign->setExpressionNode(expr);
			EXPR_NODE_PTR child = assign->getExpressionNode();
			Assert::IsTrue(typeid(*var) == typeid(*child));
		}
	};
}