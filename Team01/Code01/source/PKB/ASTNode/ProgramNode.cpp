#include "ProgramNode.h"

ProgramNode::ProgramNode() {
    node_type_ = { NodeTypeEnum::programNode };
}

BOOLEAN ProgramNode::addProcedureNode(PROC_NODE_PTR proc_node_ptr) {
	try {
		if (proc_node_ptr == nullptr) {
			return false;
		}
		addChildNode(proc_node_ptr);
		proc_node_ptr->setParentNode(std::make_shared<ProgramNode>(*this));
		proc_node_ptr_list_.push_back(proc_node_ptr);
	} catch (int e) {
		(void)e;
		return false;
	}
	return true;
}

PROC_NODE_PTR_LIST ProgramNode::getProcedureNodeList() {
	return proc_node_ptr_list_;
}