#pragma once

#include <memory>
#include <string>
#include "CallNode.h"
#include "StatementNode.h"

typedef std::shared_ptr<VariableNode> VAR_NODE_PTR;
typedef std::string PROC_NAME;
typedef bool BOOLEAN_TYPE;

class CallNode: public StatementNode, public std::enable_shared_from_this<CallNode> {

public:
	CallNode();
	/*
	Description: Sets NODE_TYPE of node to be callNode.
	*/

	BOOLEAN_TYPE setProcedureName(PROC_NAME proc_name);
	/*
	Description: Returns True if able to set the PROC_NAME of the procedure that the call statement is calling, false otherwise.
	*/

	PROC_NAME getProcedureName();
	/*
	Description: Returns the PROC_NAME of the procedure that the call statement is calling.
	*/

private:
	PROC_NAME proc_name_;

};
