#include "stdafx.h"
#include "CppUnitTest.h"
#include "../source/QueryNode.h"
#include "../source/QueryNodeType.h"

#include <string>
#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(VariableNodeTest)
	{
	public:

		TEST_METHOD(Constructor_Default_Success)
		{
			QueryNode query_node;
			Assert::IsNull(query_node.getChildren());
		}

		TEST_METHOD(setNodeType_Select_Success)
		{
			QueryNode query_node;
			QueryNodeType chosen_type = { QueryNodeType::select };
			query_node.setNodeType({ QueryNodeType::select });
			NODE_TYPE type = query_node.getNodeType();
			Assert::IsTrue(type == chosen_type);
		}

		TEST_METHOD(setNodeType_Synonym_Success)
		{
			QueryNode query_node;
			QueryNodeType chosen_type = { QueryNodeType::synonym };
			query_node.setNodeType({ QueryNodeType::synonym });
			NODE_TYPE type = query_node.getNodeType();
			Assert::IsTrue(type == chosen_type);
		}

		TEST_METHOD(setNodeType_SuchThat_Success)
		{
			QueryNode query_node;
			QueryNodeType chosen_type = { QueryNodeType::such_that };
			query_node.setNodeType({ QueryNodeType::such_that });
			NODE_TYPE type = query_node.getNodeType();
			Assert::IsTrue(type == chosen_type);
		}

		TEST_METHOD(setNodeType_Parent_Success)
		{
			QueryNode query_node;
			QueryNodeType chosen_type = { QueryNodeType::parent };
			query_node.setNodeType({ QueryNodeType::parent });
			NODE_TYPE type = query_node.getNodeType();
			Assert::IsTrue(type == chosen_type);
		}

		TEST_METHOD(setNodeType_ParentT_Success)
		{
			QueryNode query_node;
			QueryNodeType chosen_type = { QueryNodeType::parentT };
			query_node.setNodeType({ QueryNodeType::parentT });
			NODE_TYPE type = query_node.getNodeType();
			Assert::IsTrue(type == chosen_type);
		}

		TEST_METHOD(setNodeType_Follows_Success)
		{
			QueryNode query_node;
			QueryNodeType chosen_type = { QueryNodeType::follows };
			query_node.setNodeType({ QueryNodeType::follows });
			NODE_TYPE type = query_node.getNodeType();
			Assert::IsTrue(type == chosen_type);
		}

		TEST_METHOD(setNodeType_FollowsT_Success)
		{
			QueryNode query_node;
			QueryNodeType chosen_type = { QueryNodeType::followsT };
			query_node.setNodeType({ QueryNodeType::followsT });
			NODE_TYPE type = query_node.getNodeType();
			Assert::IsTrue(type == chosen_type);
		}

		TEST_METHOD(setChildren_EmptyArray_Success)
		{

		}

		TEST_METHOD(setChildren_OneElementArray_Success)
		{

		}

		TEST_METHOD(setChildren_ThreeElementArray_Success)
		{

		}

		TEST_METHOD(setSynonymNode_AssignA1_Success)
		{

		}

		TEST_METHOD(setSynonymNode_VariableV1_Success)
		{

		}

		TEST_METHOD(setSynonymNode_NoArguments_Failure)
		{

		}

		TEST_METHOD(setSynonymNode_OneArgument_Failure)
		{

		}

		TEST_METHOD(setSynonymNode_InvalidArguments_Failure)
		{

		}

		TEST_METHOD(getSynonymName_NoArguments_Success)
		{

		}

		TEST_METHOD(getSynonymType_NoArguments_Success)
		{

		}
	};
}