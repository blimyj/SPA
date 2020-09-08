#include "PKB.h"

PKB::PKB(PKB_BUILDER builder) {

}

STMT_NODE_PTR_LIST PKB::getStatements() {

}

READ_NODE_PTR_LIST PKB::getReads() {

}

PRINT_NODE_PTR_LIST PKB::getPrints() {

}

WHILE_NODE_PTR_LIST PKB::getWhiles() {

}

IF_NODE_PTR_LIST PKB::getIfs() {

}

ASSIGN_NODE_PTR_LIST PKB::getAssigns() {

}

CONSTANT_NODE_PTR_LIST PKB::getConstants() {

}

VAR_NODE_PTR_LIST PKB::getVariables() {

}

PROC_NODE_PTR_LIST PKB::getProcedures() {

}

BOOLEAN PKB::isFollows(STMT_NUM s1, STMT_NUM s2) {

}

BOOLEAN PKB::isParent(STMT_NUM s1, STMT_NUM s2) {

}

BOOLEAN PKB::isUses(STMT_NUM s, VAR_NAME v) {

}

BOOLEAN PKB::isUses(PROC_NAME p, VAR_NAME v) {

}

BOOLEAN PKB::isModifies(STMT_NUM s, VAR_NAME v) {

}

BOOLEAN PKB::isModifies(PROC_NAME p, VAR_NAME v) {

}

PROGRAM_AST_NODE getProgramAST() {

}
