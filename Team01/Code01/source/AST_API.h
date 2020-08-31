#ifndef AST_API_H
#define AST_API_H

/* This file is an example of the consolidated AST API. More methods should be added to this file. Please also refer to API slides 21 to 30.*/

/* ASTNode Interface */
class ASTNode {
	virtual AST_NODE_POINTER getParent();
	/*
	Description:
		Normal: Returns the AST_NODE_POINTER that points to the parent AST_NODE of this node otherwise returns NULL.
	*/

	virtual LIST_AST_NODE_POINTER getChildren();
	/*
	Description:
		Normal: Returns a list of AST_NODE_POINTERS that point to AST_NODEs that are children of this node, if there are no children, returns an empty list.
	*/
};


/* Statement Interface */
class Statement {
	STMT_INDEX getStmtIndex();
	/*
	Description:
	  Normal: Returns STMT_INDEX of this statement.
*/
};


/* Read Node API */
class READ_AST_NODE : public ASTNode, public Statment {
public:
	READ_NODE_POINTER ReadNode(AST_NODE_POINTER var);
	/*
	Description:
		Normal: Constructs a READ_AST_NODE / Read AST_NODE / ReadNode & returns a pointer to it.
		Abnormal: If NULL var provided, throw exception.
	*/

	AST_NODE_POINTER getVar();
	/*
	Description:
		Normal: Returns AST_NODE_POINTER to the VarNode for this read statemnet.
		Abnormal: If no such AST_NODE exists, throws an exception.
	*/
};


/* Print Node API */
class PrintNode : public ASTNode, public Statment {
public:
	PRINT_NODE_POINTER PrintNode(AST_NODE_POINTER var);
	/*
	Description:
		Normal: Constructs a PRINT_AST_NODE & returns a pointer to it.
		Abnormal: If NULL var provided, throw exception.
	*/

	AST_NODE_POINTER getVar();
	/*
	Description:
		Normal: Returns AST_NODE_POINTER to the VarNode for this read statemnet.
		Abnormal: If no such AST_NODE exists, throws an exception.
	*/
};


class AssignNode : public ASTNode, public Statment {
public:
	ASSIGN_NODE_POINTER AssignNode(VAR_NODE var_node, EXPR_NODE expr_node);
	/*
	Description:
		Normal: Constructs an ASSIGN_AST_NODE & returns a pointer to it.
		Abnormal: If NULL var_node or expr_node provided, throw exception.
	*/

	AST_NODE_POINTER getVar();
	/*
	Description:
		Normal: Returns AST_NODE_POINTER to the VarNode that is on the lhs of this Assign statemnet.
		Abnormal: If no such AST_NODE exists, throws an exception.
	*/

	AST_NODE_POINTER getExpression();
	/*
	Description:
		Normal: Returns AST_NODE_POINTER to the EXPR_NODE that is on the rhs of this Assign statemnet.
		Abnormal: If no such AST_NODE exists, throws an exception.
	*/
}

class CallNode : public ASTNode, public Statment {
public:
	CALL_NODE_POINTER CallNode(PROC_NODE proc_node);
	/*
	Description:
		Normal: Constructs a CALL_AST_NODE & returns a pointer to it.
		Abnormal: If NULL var provided, throw exception.
	*/

	AST_NODE_POINTER getProcedure();
	/*
	Description:
		Normal: Returns AST_NODE_POINTER to the PROC_NODE for this call statment.
		Abnormal: If no such AST_NODE exists, throws an exception.
	*/

}

class WhileNode : public ASTNode, public Statment {
public:
	WHILE_NODE_POINTER WhileNode(COND_NODE cond_node, STMT_LIST stmt_list);
	/*
	Description:
		Normal: Constructs a WHILE_AST_NODE & returns a pointer to it.
		Abnormal: If NULL var provided, throw exception.
	*/

	AST_NODE_POINTER getCondition();
	/*
	Description:
		Normal: Returns AST_NODE_POINTER to the COND_NODE for this while statment.
		Abnormal: If no such AST_NODE exists, throws an exception.
	*/


	AST_NODE_POINTER getWhileStmtList();
	/*
	Description:
		Normal: Returns AST_NODE_POINTER to the STMT_LIST_NODE for this while statment.
		Abnormal: If no such AST_NODE exists, throws an exception.
	*/
}

/* If Node API */
class IfNode : public ASTNode, public Statment {
public:
	IF_NODE_POINTER IfNode(AST_NODE_POINTER condition, AST_NODE_POINTER ifStmtList, AST_NODE_POINTER elseStmtList);
	/*
	Description:
		Normal: Constructs an IfNode & returns a pointer to it.
		Abnormal: If null var provided, throw exception.
	*/

	AST_NODE_POINTER getCondition();
	/*
	Description:
		Normal: Returns a pointer to the condition of IfNode.
	*/

	AST_NODE_POINTER getIfStmtList();
	/*
	Description:
		Normal: Returns a pointer to the ifStmtList of the IfNode
	*/

	AST_NODE_POINTER getElseStmtList();
	/*
	Description:
		Normal: Returns a pointer to the elseStmtList of the IfNode
	*/
};

/* Var Node API */
class VarNode : public ASTNode, public Statment {
public:
	VAR_NODE_POINTER VarNode(STRING varName);
	/*
	Description:
		Normal: Constructs a VarNode & returns a pointer to it.
		Abnormal: If null varName is provided, throw exception.
	*/

	STRING getVarName();
	/*
	Description:
		Normal: Returns the varName of the VarNode.
	*/
};

/* Constant Node API */
class ConstantNode : public ASTNode, public Statment {
public:
	CONSTANT_NODE_POINTER ConstantNode(INT value);
	/*
	Description:
		Normal: Constructs a ConstantNode & returns a pointer to it.
		Abnormal: If null value is provided, throw exception.
	*/

	INT getValue();
	/*
	Description:
		Normal: Returns 
	*/
};

/* Procedure Node API */
class ProcedureNode : public ASTNode, public Statment {
public:
	PROCEDURE_NODE_POINTER ProcedureNode(STRING procName, AST_NODE_POINTER stmtList);
	/*
	Description:
		Normal: Constructs a ProcedureNode & returns a pointer to it.
		Abnormal: If null procName or stmtList is provided, throw exception.
	*/

	STRING getProcName();
	/*
	Description:
		Normal: Return a string of the ProcedureNode's procName.
	*/

	LIST_AST_NODE_POINTER getProcStmtList();
	/*
	Description:
		Normal: Return a list containing pointers to various statements in the statement list.
	*/
};

/* StmtList Node API */
class StmtListNode : public ASTNode, public Statment {
public:
	STMT_LIST_NODE_POINTER StmtListNode(LIST_AST_NODE_POINTER stmtList);
	/*
	Description:
		Normal: Constructs a StmtListNode & returns a pointer to it.
		Abnormal: If null stmtList is provided, throw exception.
	*/

	LIST_AST_NODE_POINTER getStmtList() {
	/*
	Description:
		Normal: Return the StmtListNode's stmtList.
	*/
	}
};

/* Expression Node API */
class ExprNode {
public:
	AST_NODE_POINTER ExprNode(EXPR_TYPE expr_type, AST_NODE_POINTER lhs, AST_NODE_POINTER rhs);
		/*
		Description:
		  Normal: Constructs an Expr AST_NODE & returns a pointer to it.
		*/   

	EXPR_TYPE getExprType();
		/*
		Requires: This node to have a valid ExprType.
		Description:
		  Normal: Returns the EXPR_TYPE of this conditional expression.
		  Abnormal: If no such EXPR_TYPE exists, throws an exception.
		*/

	AST_NODE_POINTER getLHS();
		/*
		Requires: This node to have a lhs expression.
		Description:
		  Normal: Returns the AST_NODE_POINTER that points to the AST_NODE that contains the expression on the lhs.
		  Abnormal: If no such AST_NODE exists, throws an exception.
		*/

	AST_NODE_POINTER getRHS();
		/*
		Requires: This node to have a rhs expression.
		Description:
		  Normal: Returns the AST_NODE_POINTER that points to the AST_NODE that contains the expression on the rhs.
		  Abnormal: If expr_type is not {PLUS, MINUS, TIMES, DIV, MOD}, throws an exception.
		*/
};


/* Conditional Expression Node API */
class CondExprNode {
public:
	AST_NODE_POINTER CondExprNode(RELATION_TYPE rel_type, AST_NODE_POINTER lhs, AST_NODE_POINTER rhs);
		/*
		Description:
		  Normal: Constructs a CondExpr AST_NODE & returns a pointer to it.
		  Abnormal: If lhs and rhs are not distinct, throw exception.
		*/    

	RELATION_TYPE getRelType();
		/*
		Requires: This node to have a valid RELATION_TYPE.
		Description:
		  Normal: Returns the RELATION_TYPE of this conditional expression.
		  Abnormal: If no such RELATION_TYPE exists, throws an exception.
		*/

	AST_NODE_POINTER getLHS();
		/*
		Requires: This node to have a lhs expression.
		Description:
		  Normal: Returns the AST_NODE_POINTER that points to the AST_NODE that contains the expression on the lhs.
		  Abnormal: If no such AST_NODE exists, throws an exception.
		*/

	AST_NODE_POINTER getRHS();
		/*
		Requires: This node to have a rhs expression.
		Description:
		  Normal: Returns the AST_NODE_POINTER that points to the AST_NODE that contains the expression on the rhs.
		  Abnormal: If no such AST_NODE exists, throws an exception.
		*/
};





#endif