#include "PKB.h"

PKB::PKB(PKB_BUILDER builder) {
    stmt_table_ = builder.stmt_table_;
    stmt_list_table_ = builder.stmt_list_table_;
    read_table_ = builder.read_table_;
    print_table_ = builder.print_table_;
    while_table_ = builder.while_table_;
    if_table_ = builder.if_table_;
    assign_table_ = builder.assign_table_;
    constant_table_ = builder.constant_table_;
    var_table_ = builder.var_table_;
    proc_table_ = builder.proc_table_;
    follows_table_ = builder.follows_table_;
    parent_table_ = builder.parent_table_;
    uses_table_ = builder.uses_table_;
    modifies_table_ = builder.modifies_table_;
    program_node_ptr_ = builder.program_node_ptr;
}

STMT_NODE_PTR_LIST PKB::getStatements() {
    return stmt_table_.getStatementNodeList();
}

STMT_LIST_NODE_PTR_LIST PKB::getStatementLists() {
    return stmt_list_table_.getStatementListNodeList();
}

READ_NODE_PTR_LIST PKB::getReads() {
    return read_table_.getReadNodeList();
}

PRINT_NODE_PTR_LIST PKB::getPrints() {
    return print_table_.getPrintNodeList();
}

WHILE_NODE_PTR_LIST PKB::getWhiles() {
    return while_table_.getWhileNodeList();
}

IF_NODE_PTR_LIST PKB::getIfs() {
    return if_table_.getIfNodeList();
}

ASSIGN_NODE_PTR_LIST PKB::getAssigns() {
    return assign_table_.getAssignNodeList();
}

CONSTANT_NODE_PTR_LIST PKB::getConstants() {
    return constant_table_.getConstantNodeList();
}

VAR_NODE_PTR_LIST PKB::getVariables() {
    return var_table_.getVariableNodeList();
}

PROC_NODE_PTR_LIST PKB::getProcedures() {
    return proc_table_.getProcedureNodeList();
}

BOOLEAN PKB::isFollows(STMT_NUM s1, STMT_NUM s2) {
    return follows_table_.isFollows(s1, s2);
}

BOOLEAN PKB::isParent(STMT_NUM s1, STMT_NUM s2) {
    return parent_table_.isParent(s1, s2);
}

BOOLEAN PKB::isUses(STMT_NUM s, VAR_NAME v) {
    return uses_table_.isUses(s, v);
}

BOOLEAN PKB::isUses(PROC_NAME p, VAR_NAME v) {
    return uses_table_.isUses(p, v);
}

BOOLEAN PKB::isModifies(STMT_NUM s, VAR_NAME v) {
    return modifies_table_.isModifies(s, v);
}

BOOLEAN PKB::isModifies(PROC_NAME p, VAR_NAME v) {
    return modifies_table_.isModifies(p, v);
}

PROGRAM_NODE_PTR PKB::getProgramNode() {
    return program_node_ptr_;
}
