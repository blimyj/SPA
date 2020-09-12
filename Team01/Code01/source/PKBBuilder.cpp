#include "PKBBuilder.h"

INDEX PKBBuilder::addStatementNode(STMT_NODE_PTR stmt_node_ptr) {
    return stmt_table_.addStatementNode(stmt_node_ptr);
}

INDEX PKBBuilder::addReadNode(READ_NODE_PTR read_node_ptr) {
    return read_table_.addReadNode(read_node_ptr);
}

INDEX PKBBuilder::addPrintNode(PRINT_NODE_PTR print_node_ptr) {
    return print_table_.addPrintNode(print_node_ptr);
}

INDEX PKBBuilder::addWhileNode(WHILE_NODE_PTR while_node_ptr) {
    return while_table_.addWhileNode(while_node_ptr);
}

INDEX PKBBuilder::addIfNode(IF_NODE_PTR if_node_ptr) {
    return if_table_.addIfNode(if_node_ptr);
}

INDEX PKBBuilder::addAssignNode(ASSIGN_NODE_PTR assign_node_ptr) {
    return assign_table_.addAssignNode(assign_node_ptr);
}

INDEX PKBBuilder::addConstantNode(CONSTANT_NODE_PTR constant_node_ptr) {
    return constant_table_.addConstantNode(constant_node_ptr);
}

INDEX PKBBuilder::addVariableNode(VAR_NODE_PTR var_node_ptr) {
    return var_table_.addVariableNode(var_node_ptr);
}

INDEX PKBBuilder::addProcedureNode(PROC_NODE_PTR proc_node_ptr) {
    return proc_table_.addProcedureNode(proc_node_ptr);
}

VOID PKBBuilder::addFollows(STMT_NUM s1, STMT_NUM s2) {
    follows_table_.addFollows(s1, s2);
}

VOID PKBBuilder::addParent(STMT_NUM s1, STMT_NUM s2) {
    parent_table_.addParent(s1, s2);
}

VOID PKBBuilder::addUses(STMT_NUM s, VAR_NAME v) {
    uses_table_.addUses(s, v);
}

VOID PKBBuilder::addUses(PROC_NAME p, VAR_NAME v) {
    uses_table_.addUses(p, v);
}

VOID PKBBuilder::addModifies(STMT_NUM s, VAR_NAME v) {
    modifies_table_.addModifies(s, v);
}

VOID PKBBuilder::addModifies(PROC_NAME p, VAR_NAME v) {
    modifies_table_.addModifies(p, v);
}

VOID PKBBuilder::setProgramNode(PROGRAM_NODE_PTR program_node_ptr) {
    program_node_ptr = program_node_ptr;
}

PKB PKBBuilder::build() {
    return PKB(*this);
}
