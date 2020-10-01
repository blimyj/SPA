#include "CallNode.h"

CallNode::CallNode() {
	node_type_ = { NODE_TYPE::callNode };
	proc_name_ = "";
}

BOOLEAN_TYPE CallNode::setProcedureName(PROC_NAME proc_name) {
	try {
		proc_name_ = proc_name;
	}
	catch (int e) {
		(void)e;
		return false;
	}
	return true;
}

PROC_NAME CallNode::getProcedureName() {
	return proc_name_;
}
