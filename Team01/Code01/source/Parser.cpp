#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iterator>
#include <deque>

#include "PKB.h"
#include "Parser.h"

	int Parser::Parse() {

		return 0;
	}

	PKB Parser::parseFile(STRING filename) {
		//Construct program root node
		//Will this be deleted after function exits?
		this->root_node_ = (std::make_shared<ProgramNode>)();
		this->pkb_builder_ = PKBBuilder();
		this->pkb_builder_.setProgramNode(this->root_node_);

		this->current_parent_node_ = this->root_node_;

		this->stmt_num_ = 0;

		std::string str;

		// Construct file object
		std::ifstream fileObj(filename);
		// Construct file content iterator
		std::istreambuf_iterator<char> eos;
		std::istreambuf_iterator<char> iit(fileObj);
		std::istreambuf_iterator<char>* iit_p = &iit;
		std::string token;

		//This is to parse all token from file string and enqueue to token_stream_
		//While iterator not end of file

		while (*iit_p != eos) {
			//call getNextToken
			token = getNextToken(iit_p, eos);
			//Enqueue to process_token_stream_
			if (token != " ") {
				this->process_token_stream_.push_back(token);
			}
			else {
				break;
			}
		}


		//This loop processes the tokens to construct nodes

		//this->stmt_token_queue_ stores tokens for a particular statement / opening segment
		//Note that first token always denotes type of statement
		std::string stmt_token;
		while (!this->process_token_stream_.empty()) {

			//Check first two tokens, then call appropriate parse function
			stmt_token = this->process_token_stream_.front();
			this->process_token_stream_.pop_front();

			//Checks for '=' token that denotes assign type
			if (!this->process_token_stream_.empty() && this->process_token_stream_.front() == "=") {
				this->process_token_stream_.pop_front();
				this->stmt_token_queue_.push_back("assign"); //Note that this was enqueued instead of '='
				this->stmt_token_queue_.push_back(stmt_token); //This would be the variable name
				parseAssign(&this->stmt_token_queue_, &this->process_token_stream_);
				continue;
			}

			if (stmt_token == "procedure") {
				this->stmt_token_queue_.push_back(stmt_token); //This is "procedure" token
				parseProcedure(&this->stmt_token_queue_, &this->process_token_stream_);
				continue;
			}

			if (stmt_token == "read") {
				this->stmt_token_queue_.push_back(stmt_token); //This is "read" token
				parseRead(&this->stmt_token_queue_, &this->process_token_stream_);
				continue;
			}

			if (stmt_token == "print") {
				this->stmt_token_queue_.push_back(stmt_token); //This is "print" token
				parsePrint(&this->stmt_token_queue_, &this->process_token_stream_);
				continue;
			}

			if (stmt_token == "}") {
				parseStmtListClose();
				continue;
			}

			//Handler for all other tokens, prints them out
			std::cout << "\n" << stmt_token;
		}

		PKB pkb = this->pkb_builder_.build();
		
		for (std::shared_ptr<AssignNode> a_node : pkb.getAssigns()) {
			a_node->getVariableNode();
		}
		
		
		
		return pkb;
	}

	STRING Parser::getNextToken(std::istreambuf_iterator<char>* iter, std::istreambuf_iterator<char> eos) {
		std::string curr_token;

		//Skip past all whitespaces
		while (*iter != eos && isspace(**iter))++* iter;

		//Check if end of file
		if (*iter == eos) {
			return " ";
		}
		//NOTE: Loop calling getNextToken() is responsible for checking if return is a space before adding the returned token to this->process_token_stream__
		//Guaranteed to never return space otherwise due to skipping space.

		//Check for NAME token
		if (isalpha(**iter)) { //This guarantees first char is LETTER
			while (*iter != eos && isalnum(**iter)) {
				curr_token += **iter;
				++* iter;
			}
			return curr_token;
		}

		//Check for bracket terminal tokens
		if (**iter == '{' || **iter == '}' || **iter == '(' || **iter == ')') {
			curr_token += **iter;
			++* iter;
			return curr_token;
		}

		//Check for semicolon terminal tokens
		if (**iter == ';') {
			curr_token += **iter;
			++* iter;
			return curr_token;
		}

		//Check for CONSTANT tokens
		if (isdigit(**iter)) { //This guarantees first char is DIGIT
			while (*iter != eos && isdigit(**iter)) {
				curr_token += **iter;
				++* iter;
			}
			return curr_token;
		}
		//Check for '=' vs '==' terminal tokens
		if (*iter != eos && **iter == '=') { //Checks if first letter matches '=' terminal
			curr_token += **iter;
			++* iter;
			if (*iter != eos && **iter == '=') {
				curr_token += **iter;
				++* iter;
			} else {}
			return curr_token;
		}

		//Check for arithmetic terminal tokens & assign

		//Check for boolean terminal tokens

		//Check for unexpected tokens
		curr_token += "UNEXPECTED TOKEN:";
		curr_token += **iter;
		++* iter;
		return curr_token;
	}

	int Parser::parseText(LIST_OF_STRINGS str_list) {

		// Not considered for now.
		return 0;
	}

	/*Note: For 'read' / 'print' / 'procedure' / 'call' we are unsure if keyword<NAME> is valid.
	However we assume they are not for now. (This has been confirmed)
	For example
	"readx"
	"procedureabv"
	"callmain"
	*/

	/*Note: We assume that the first 4 terminals of the while stmt must be on the same line
	‘while’ ‘(’ cond_expr ‘)’ ‘{‘ stmtLst <----- Terminals must be on the same line, stmtLst could be on same or diff.

	stmtLst ‘}’ <---- Can be on a different line, we make no assumption if stmtLst & ‘}’ must be on the same line
	*/

	/*Note: We assume that the first 4 terminals of the if stmt must be on the same line
	‘if’ ‘(’ cond_expr ‘)’ ‘then’ ‘{‘ stmtLst <----- Terminals must be on the same line, stmtLst could be on same or diff.

	stmtLst ‘}’ ‘else’ ‘{‘ stmtLst ‘}’ <- Can be on a different line,
											we make no assumption if any of these terminals & non-terminals must be on the same line
	*/

	/*Note: We do not assume that a newline must follow '}' */

	/*Note: (WRONG ASSUMPTION) We are assuming each statement cannot be spread out across multiple lines
	For example, the following is invalid
	a
	=
	3;
	*/

	/*Note: (WRONG ASSUMPTION) We are assuming each statement must end with a ; on the same line.
	For example, the following is invalid
	a=3;
	*/


	/*
	For read, print, assign, call statements, the terminal ';' to indicate the end of the statement.

	For procedure, while, if-then, else statement, the terminal '{' indicates the end of the opening segment of the container statement.

	For statement lists, the terminal  '}' to indicate the end of the statement list.

	Please note that for the above statements that the end of the statement, statement list, or opening segment
	DOES NOT indicate the end of the line. There can be combinations of the aforementioned in a single line. (A 50 line program could be compressed to 1 line)
	*/

	/*
	Due to the possibility of 'read', 'print', 'if', 'else', 'then', 'while', 'procedure', 'call' being variable names,
	we must look ahead at least 1 token to see if it is an assign statement.
	*/

	/*
	Note that for cond_expr, if a boolean operator is applied to it, the operand(s) cond_expr will each be encapsulated by the terminals '(', ')'
	*/

	//AST_NODE_PTR current_parent_node_ = PROGRAM_NODE();

	/*
	int Parser::parseFirstStreamToken(std::deque<STRING>* stmt_token_stream, std::deque<STRING>* ) {

		//Taking a string, we want to tokenize 1 at a time, with each token telling us what we expect next.
		//We must maintain class member curr_token_stream_ <--- A vector of important tokens, I believe we can ignore the following tokens: '{', '}', ';'

		//Takes out only first set of whitespaces
		int Parser::str_ind = ind;
		int Parser::str_size = str.size();
		while (str_ind < str_size && std::isspace(str.at(str_ind))) {
			str_ind++;
		}

		//If empty line, skips to next line
		if (str_ind == str_size) { return 0; }
		//After this, we know str.at(str_ind)is not whitespace nor the end.

		//First Token Checker
		if (curr_token_stream_.empty() && isalnum(str.at(str_ind))) {
			int Parser::old_ind = str_ind;
			//read in first token of the form LETTER(LETTER|DIGIT)* ---> could be a NAME or a terminal
			while (str_ind < str_size && isalnum(str.at(str_ind))) {
				str_ind++;
			}
			//take substr(old_ind, (str_ind - old_ind)) as first token and put into curr_token_stream_
			std::string token = str.substr(old_ind, (str_ind - old_ind));

			//Note that first token could always be var name instead of actual stmt type.
			curr_token_stream_.push_back(token);
			parseFirstStreamToken(str, str_ind);
		}


		else {
			//Takes out only first set of whitespaces
			int Parser::str_ind = ind;
			while (str_ind < str_size && std::isspace(str.at(str_ind))) {
				str_ind++;
			}

			//If empty line, skips to next line
			if (str_ind == str_size) return 0;
			//After this, we know str.at(str_ind)is not whitespace nor the end.

			if (curr_token_stream_.size() == 1) {
				//Check if second token is '=' to differentiate assign statement from other statements
				if (str.at(str_ind)== '=') {
					//Change stmt type in curr_token_stream_ to assignment
					curr_token_stream_.insert(curr_token_stream_.begin(), "assign");
				} else {
					STRING token = curr_token_stream_.at(0);
					PARSE_FUNC_PTR parse_func = parse_func_table_[token];
					parse_func(str, str_ind);
				}
			}
			//could be another alnum token
			//could be assign operator
			//could be a terminal like '{', '}', ';', '(', ')', arithmetic operators, boolean operators
			//not sure if it could be terminals such as comparison operators
		}
		//check for 'if' / 'while' in the first 2 and 5 chars  respectively & a '(' exists (Otherwise it could be a var name)
			//call parseIf & parseWhile respectively

		//check for '='
			//call parseAssign

		//check for 'read' / 'print' / 'procedure' / 'call'
			//call parseRead & parsePrint & parseProc & parseCall respectively

		//check for '}'
			//call parseStmtListClose;

		//check for 'else'
			//call parseElse

		return 0;
	}
	*/
	int Parser::parseWhile(STRING str) {
		//We assume that this opening segment will either terminate with '{' or ';' with the exception of whitespaces and newline?
		return 0;
	}

	int Parser::parseIfThen(STRING str) {
		//We assume that this opening segment will either terminate with '{' or ';' with the exception of whitespaces and newline?

		return 0;
	}

	int Parser::parseElse(STRING str) {
		//We assume that '{' will follow 'else'
		//We assume that this opening segment will either terminate with '{' or ';' with the exception of whitespaces and newline?
		return 0;
	}

	int Parser::parseAssign(STMT_TOKEN_QUEUE stmt_tok_queue, PROCESS_TOKEN_QUEUE proc_tok_queue) {
		//We assume that this statement will terminate with ';'
		// First token is assign
		if (this->stmt_token_queue_.front() != "assign") {
			return -1;
		}
		this->stmt_token_queue_.pop_front(); // Remove stmt type token
		
		//Second token is lhs var name 
		STRING lhs_name_token = this->stmt_token_queue_.front();
		this->stmt_token_queue_.pop_front(); // Remove varname token
		if (!isalpha(lhs_name_token.at(0)) && !isdigit(lhs_name_token.at(0))) {
			return -1;
		}

		//Third token is rhs expr (For now, it will just be a single var name or constant)
		STRING rhs_token = this->process_token_stream_.front();
		this->process_token_stream_.pop_front(); // Remove rhs var/const token
		if (!isalpha(rhs_token.at(0)) && !isdigit(rhs_token.at(0))) {
			return -1;
		}

		if (this->process_token_stream_.front() != ";") {
			return -1;
		}
		this->process_token_stream_.pop_front(); // Pops out ';'

		//REPLACEMENT FOR THIRD TOKEN CONSUMPTION
		std::deque<ASTNode> output_node_stack = std::deque<ASTNode>();
		std::deque<OperatorTypeEnum> operator_stack = std::deque<OperatorTypeEnum>();
		OperatorTypeEnum op;
		OperatorTypeEnum temp_op;

		//===== Actual Code ======
		//Here we will keep consuming tokens until we reach ';'

		STRING rhs_token = this->process_token_stream_.front();

		while (rhs_token != ";") {
			//These tokens will populate this->stmt_token_queue_
			this->stmt_token_queue_.push_back(rhs_token);
			this->process_token_stream_.pop_front(); // Remove rhs var/const/operator/parentheses token for the next token
		}
		
		//They will form the expr that is assigned to new_expr_node
		//Then they will be funneled through the shunting yard algo
		STRING temp_token = "";
		//While stmt_token_queue_ has tokens
		while (!this->stmt_token_queue_.empty()) {
			//Get & remove first token from stmt_token_queue_
			temp_token = this->stmt_token_queue_.front();
			this->stmt_token_queue_.pop_front();

			//if isalpha(first_char) 
			if (isalpha(temp_token.at(0))) {
				//then create varnode enqueue to output_node_stack
				//TODO: Need to add to varTable
				VariableNode new_var_node = VariableNode(temp_token);
				//enqueue to output_stack
				output_node_stack.push_back(new_var_node);
			}
			else if (isdigit(temp_token.at(0))) {
				//else isdigit(first_char) then create const node
				//TODO: Need to add to constTable
				ConstantNode new_const_node = ConstantNode(temp_token);
				//enqueue to output_stack
				output_node_stack.push_back(new_const_node);
			}
			else {
				//Else means token is operator or parentheses
				//Create a Operator TypeEnum object
				if (temp_token == "+") {
					op = op_plus;
				} else if (temp_token == "-") {
					op = op_min;
				} else if (temp_token == "*") {
					op = op_mult;
				} else if (temp_token == "/") {
					op = op_div;
				} else if (temp_token == "%") {
					op = op_mod;
				} else if (temp_token == "(") {
					op = op_lparen;
				} else if (temp_token == ")") {
					op = op_rparen;
				} else {
					//If not any of the above tokens, return an error.
					return -1;
				}
				
				//throw into operator stack
				if (op == op_lparen) {
					operator_stack.push_back(op);
				} else if (op == op_rparen) {
					while (!operator_stack.empty() && operator_stack.back() != op_lparen) {
						//Pop operator from operator stack onto the output queue. 
						//When we want to place an operator into the output stack,we instead create a new ExpressionNode (top Node of Stack is rhs, 2nd top is lhs)
						temp_op = operator_stack.back();
						operator_stack.pop_back();

						ASTNode rhs_operand = output_node_stack.back();
						output_node_stack.pop_back();

						ASTNode lhs_operand = output_node_stack.back();
						output_node_stack.pop_back();

						//Note we must check if we are able to pop out 2 & the 2 is the type we want
						if (rhs_operand.getNodeType() != expressionNode || rhs_operand.getNodeType() != variableNode || rhs_operand.getNodeType() != constantNode) {
							return -1;
						}
						if (lhs_operand.getNodeType() != expressionNode || lhs_operand.getNodeType() != variableNode || lhs_operand.getNodeType() != constantNode) {
							return -1;
						}

						ExpressionTypeEnum expr_type = getExpressionType(OperatorTypeEnum op);

						//TODO: Need parent, child pointers
						ExpressionNode new_expr_node = ExpressionNode(expr_type, lhs_operand, rhs_operand);

						//We then place this ExpressionNode into the output_node_stack
						output_node_stack.push_back(new_expr_node);
					}
					// If operator_stack.empty() that means there are mismatched parentheses
					if (operator_stack.empty()) return -1;
					if (operator_stack.back() == op_lparen) {
						operator_stack.pop_back();
					}
				} else {
					while (!operator_stack.empty() && operator_stack.back() != op_lparen
						&& ((takesPrecedence(operator_stack.back(), op) == 1) 
							|| (takesPrecedence(operator_stack.back(), op) == 0))) {
						//NOTE: Condition for takesPredence(op1, op2) == 0, i.e. same precedence also has the requirement
						// of operators being left associative, which I think all of them are for this case.
						temp_op = operator_stack.back();
						operator_stack.pop_back();
						
						//When we want to place an operator into the output stack,we instead create a new ExpressionNode (top Node of Stack is rhs, 2nd top is lhs)
						ASTNode rhs_operand = output_node_stack.back();
						output_node_stack.pop_back();
						
						ASTNode lhs_operand = output_node_stack.back();
						output_node_stack.pop_back();

						//Note we must check if we are able to pop out 2 & the 2 is the type we want
						if (rhs_operand.getNodeType() != expressionNode || rhs_operand.getNodeType() != variableNode || rhs_operand.getNodeType() != constantNode) {
							return -1;
						}
						if (lhs_operand.getNodeType() != expressionNode || lhs_operand.getNodeType() != variableNode || lhs_operand.getNodeType() != constantNode) {
							return -1;
						}
						
						ExpressionTypeEnum expr_type = getExpressionType(OperatorTypeEnum op);
						
						//TODO: Need parent, child pointers
						ExpressionNode new_expr_node = ExpressionNode(expr_type, lhs_operand, rhs_operand);

						//We then place this ExpressionNode into the output_node_stack
						output_node_stack.push_back(new_expr_node);
					}
					//Push operator to operator stack
					operator_stack.push_back(op);
				}
			}
		}
		
		//Handle remaining operators in operator_stack
		while (!operator_stack.empty()) {
			if (operator_stack.back() == op_lparen || operator_stack.back() == op_rparen) {
				//Presence of parenthesis indicates mismatched parenthesis as they should have all been discarded earlier.
				return -1;
			}
			//When we want to place an operator into the output stack,we instead create a new ExpressionNode (top Node of Stack is rhs, 2nd top is lhs)
			temp_op = operator_stack.back();
			operator_stack.pop_back();

			ASTNode rhs_operand = output_node_stack.back();
			output_node_stack.pop_back();

			ASTNode lhs_operand = output_node_stack.back();
			output_node_stack.pop_back();

			//Note we must check if we are able to pop out 2 & the 2 is the type we want
			if (rhs_operand.getNodeType() != expressionNode || rhs_operand.getNodeType() != variableNode || rhs_operand.getNodeType() != constantNode) {
				return -1;
			}
			if (lhs_operand.getNodeType() != expressionNode || lhs_operand.getNodeType() != variableNode || lhs_operand.getNodeType() != constantNode) {
				return -1;
			}

			ExpressionTypeEnum expr_type = getExpressionType(OperatorTypeEnum op);

			//TODO: Need parent, child pointers
			ExpressionNode new_expr_node = ExpressionNode(expr_type, lhs_operand, rhs_operand);

			//We then place this ExpressionNode into the output_node_stack
			output_node_stack.push_back(new_expr_node);
		}

		//We maintain 1 node stacks, output
		//We maintain an operator stack as well with type OperatorEnum {Plus, Minus, Times, Divide, LParen, RParen}
		//We need a precedence checker


		//Converting tokens to nodes the moment we dequeue them from this->stmt_token_queue_
		//We use shunting yard algo with modifications
		//When we want to place an operator into the output stack,we instead create a new ExpressionNode (top Node of Stack is rhs, 2nd top is lhs)
			//Note we must check if we are able to pop out 2 & the 2 is the type we want
		//We then place this ExpressionNode into the output_node_stack
		
		//Once ';' is reached or stmt_token_queue_ is empty we should have only 1 expression node or VarNode/ConstNode in the output stack.
		if (output_node_stack.size() != 1) {
			return -1;
		}
		//Note that we must check if we need to encapsulate VarNode/ConstNode to return a proper ExpressionNode
		//We then create the AssignNode similar to the code below.
		std::shared_ptr<ASTNode> result = std::make_shared<ASTNode>(output_node_stack.back());
		output_node_stack.pop_back();
		if (result.getNodeType() == variableNode || result.getNodeType() == constantNode) {
			//TODO: Need parent, child pointers
			
			result = std::make_shared<ExpressionNode>(ExpressionTypeEnum::none, result, nullptr);
		}

		//Finalise rhs_expr_node
		std::shared_ptr<ExpressionNode> rhs_expr_node = std::static_pointer_cast<ExpressionNode>(result);
		
		//Create lhs var token
		std::shared_ptr<VariableNode> new_lhs_var_node = std::make_shared<VariableNode>(lhs_name_token);
		
		//Create AssignNode
		std::shared_ptr<AssignNode> new_assign_node = std::make_shared<AssignNode>(new_lhs_var_node, rhs_expr_node);

		//Set AssignNode stmt_num
		this->stmt_num_++;
		new_assign_node->setStatementNumber(this->stmt_num_);

		//Set child & parent pointers
		rhs_expr_node->setParentNode(new_assign_node);
		new_assign_node->setParentNode(this->current_parent_node_);
		this->current_parent_node_->addChildNode(new_assign_node);

		//Need to add & new_assign_node to PKB tables
		this->pkb_builder_.addStatementNode(new_assign_node);
		this->pkb_builder_.addAssignNode(new_assign_node);
		//TODO: SET PARENT AND CHILDREN POINTERS FOR PREVIOUS CONSTRUCTIONS
		//TODO: ADD NEWLY CONSTRUCTED NODES TO TABLES FOR PREVIOUS CONSTRUCTIONS
		//TODO: TEST THIS ALGO INDIVIDUALLY, ONLY 1 ASSSIGN STMT

		//REPLACEMENT END


		/*
		//OLD ASSIGNMENT HANDLER

		//Check if constant or var node to construct
		if (isalpha(rhs_token.at(0))) {
			//Construct var node
			std::shared_ptr<VariableNode> new_var_node = std::make_shared<VariableNode>(rhs_token);
			//Construct ExprNode
			std::shared_ptr<ExpressionNode> new_expr_node = std::make_shared<ExpressionNode>(ExpressionTypeEnum::none, new_var_node, nullptr);
			//Construct assign node
			std::shared_ptr<AssignNode> new_assign_node = std::make_shared<AssignNode>(new_lhs_var_node, new_expr_node);
			
			//Set AssignNode stmt_num
			this->stmt_num_++;
			new_assign_node->setStatementNumber(this->stmt_num_);

			//Set child & parent pointers
			new_var_node->setParentNode(new_expr_node);
			new_expr_node->setParentNode(new_assign_node);
			new_assign_node->setParentNode(this->current_parent_node_);
			this->current_parent_node_->addChildNode(new_assign_node);

			//Need to add new_var_node & new_assign_node to PKB tables
			this->pkb_builder_.addStatementNode(new_assign_node);
			this->pkb_builder_.addAssignNode(new_assign_node);
			this->pkb_builder_.addVariableNode(new_var_node);
			
			//Debugging statement
			std::cout << "\nCreated assign node with var: " << new_var_node->getVariableName();
		}
		else if (isdigit(rhs_token.at(0))) {
			//Construct constant node
			std::shared_ptr<ConstantNode> new_constant_node = std::make_shared<ConstantNode>(rhs_token);
			//Construct ExprNode
			std::shared_ptr<ExpressionNode> new_expr_node = std::make_shared<ExpressionNode>(ExpressionTypeEnum::none, new_constant_node, nullptr);
			//Construct assign node
			std::shared_ptr<AssignNode> new_assign_node = std::make_shared<AssignNode>(new_lhs_var_node, new_expr_node);

			//Set AssignNode stmt_num
			this->stmt_num_++;
			new_assign_node->setStatementNumber(this->stmt_num_);

			//Set child & parent pointers
			new_constant_node->setParentNode(new_expr_node);
			new_expr_node->setParentNode(new_assign_node);
			this->current_parent_node_->addChildNode(new_assign_node);
			new_constant_node->setParentNode(new_assign_node);

			//Need to add new_constant_node & new_assign_node to PKB tables
			this->pkb_builder_.addStatementNode(new_assign_node);
			this->pkb_builder_.addAssignNode(new_assign_node);
			this->pkb_builder_.addConstantNode(new_constant_node);

			//Debugging statement
			std::cout << "\nCreated constant node with var: " << new_constant_node->getValue();

			//Set AssignNode

		}
		else {
			return -1;
		}

		return 0;
		*/
		return 0;
	}

	int Parser::parseRead(STMT_TOKEN_QUEUE stmt_tok_queue, PROCESS_TOKEN_QUEUE proc_tok_queue) {
		//We take in two tokens, expecting a NAME and a ';'
		if (this->stmt_token_queue_.front() != "read") {
			return -1;
		}
		this->stmt_token_queue_.pop_front(); // Remove stmt type token

		STRING name_token = this->process_token_stream_.front(); //Retrieves potential name token
		this->process_token_stream_.pop_front(); // Pops out NAME token
		if (!isalpha(name_token.at(0))) {
			return -1;
		}

		if (this->process_token_stream_.front() != ";") {
			return -1;
		}
		this->process_token_stream_.pop_front(); // Pops out ';'

		//Construct new_var_node & new_read_node
		std::shared_ptr<VariableNode> new_var_node = std::make_shared<VariableNode>(name_token);
		std::shared_ptr<ReadNode> new_read_node = std::make_shared<ReadNode>(new_var_node);

		//Set ReadNode stmt_num
		this->stmt_num_++;
		new_read_node->setStatementNumber(this->stmt_num_);

		//Set child & parent pointers
		new_read_node->setParentNode(this->current_parent_node_);
		this->current_parent_node_->addChildNode(new_read_node);
		new_var_node->setParentNode(new_read_node);

		//Need to add new_var_node & new_read_node to PKB tables
		this->pkb_builder_.addStatementNode(new_read_node);
		this->pkb_builder_.addReadNode(new_read_node);
		this->pkb_builder_.addVariableNode(new_var_node);

		//Debugging statement
		std::cout << "\nCreated read node with var: " << new_var_node->getVariableName();

		return 0;
	}

	int Parser::parsePrint(STMT_TOKEN_QUEUE stmt_tok_queue, PROCESS_TOKEN_QUEUE proc_tok_queue) {
		//We take in two tokens, expecting a NAME and a ';'
		if (this->stmt_token_queue_.front() != "print") {
			return -1;
		}
		this->stmt_token_queue_.pop_front(); // Remove stmt type token

		STRING name_token = this->process_token_stream_.front(); //Retrieves potential name token
		this->process_token_stream_.pop_front(); // Pops out NAME token
		if (!isalpha(name_token.at(0))) {
			return -1;
		}

		if (this->process_token_stream_.front() != ";") {
			return -1;
		}
		this->process_token_stream_.pop_front(); // Pops out ';'

		//Construct new_var_node & new_print_node
		std::shared_ptr<VariableNode> new_var_node = std::make_shared<VariableNode>(name_token);
		std::shared_ptr<PrintNode> new_print_node = std::make_shared<PrintNode>(new_var_node);

		//Set PrintNode stmt_num
		this->stmt_num_++;
		new_print_node->setStatementNumber(this->stmt_num_);

		//Set child & parent pointers
		new_print_node->setParentNode(this->current_parent_node_);
		this->current_parent_node_->addChildNode(new_print_node);
		new_var_node->setParentNode(new_print_node);
		
		//Need to add new_var_node & new_print_node to PKB tables
		this->pkb_builder_.addStatementNode(new_print_node);
		this->pkb_builder_.addPrintNode(new_print_node);
		this->pkb_builder_.addVariableNode(new_var_node);

		//Debugging statement
		std::cout << "\nCreated print node with var: " << new_var_node->getVariableName();

		return 0;
	}

	int Parser::parseProcedure(STMT_TOKEN_QUEUE stmt_tok_queue, PROCESS_TOKEN_QUEUE proc_tok_queue) {
		//We assume that this opening segment will either terminate with '{'
		if (this->stmt_token_queue_.front() != "procedure") {
			return -1;
		}
		this->stmt_token_queue_.pop_front(); // Remove stmt type token

		STRING name_token = this->process_token_stream_.front(); //Retrieves potential name token
		this->process_token_stream_.pop_front(); // Pops out NAME token
		if (!isalpha(name_token.at(0))) {
			return -1;
		}
		
		if (this->process_token_stream_.front() != "{") {
			return -1;
		}
		this->process_token_stream_.pop_front(); // Pops out '{'

		//Construct new_stmt_list_node & new_procedure_node
		std::shared_ptr<StatementListNode> new_stmt_list_node = std::make_shared<StatementListNode>();
		std::shared_ptr<ProcedureNode> new_procedure_node = std::make_shared<ProcedureNode>(name_token, new_stmt_list_node);

		//Set child & parent pointers
		new_stmt_list_node->setParentNode(new_procedure_node);
		new_procedure_node->setParentNode(this->current_parent_node_);

		//change parent tracker to stmtlistnode_ptr
		this->root_node_->addChildNode(new_procedure_node);
		this->current_parent_node_ = new_stmt_list_node;
		
		//Need to add new_stmt_list_node & new_procedure_node to PKB tables
		this->pkb_builder_.addProcedureNode(new_procedure_node);
		std::cout << "\n ParentNode Size: " << this->current_parent_node_->getChildrenNode().size();

		//Debugging statement
		std::cout << "\nCreated procedure node: " << new_procedure_node->getProcedureName();

		return 0;
	}

	int Parser::parseCall(STRING str) {
		//We assume that this statement will terminate with ';'
		return 0;
	}

	int Parser::parseStmtListClose() {
		//Method 1: Accounts for procedure statement list only.
		
		//Checks if stmtlist size < 1, returns non-zero int as a signal that there is a problem
		if (this->current_parent_node_->getChildrenNode().size() < 1) {
			return -1;
		}
		std::cout << "\n ParentNode Size: " << this->current_parent_node_->getChildrenNode().size();
		//Set current_parent_node_ as parent of parent of curr_parent_node_
		//current_parent_node_ should be stmt_list_node
		this->current_parent_node_ = this->current_parent_node_->getParentNode();
		std::cout << "\n ParentNode Size: " << this->current_parent_node_->getChildrenNode().size();
		this->current_parent_node_ = this->current_parent_node_->getParentNode();
		std::cout << "\n ParentNode Size: " << this->current_parent_node_->getChildrenNode().size();

		//Debugging stmt
		std::shared_ptr<ProcedureNode> proc_node = std::static_pointer_cast<ProcedureNode>(this->current_parent_node_->getChildrenNode().at(0));
		std::cout << "\nExited out of procedure node: " << proc_node->getProcedureName();

		//Method 2: accounts for container statements
		//Part 1: When closing a stmtList Node, 
			//we must ensure there exists at least 1 stmt (if == 0 child)
				//print parsing error -> incorrect code
		//remove '}'


		//Part 2:
		//Assuming we maintain curr_parent_node_

		//There are 2 different ways to change the curr_parent_node_ (Refer to StmtListCloseChangeParentNode image)
		//if (curr_parent_node_.getParent().getType() == IF_NODETYPE_ENUM)
			//cast to parent of curr_parent_node_ to IF_NODE*
			//check if its ThenStatementListNode is equal to curr_parent_node_ (after we cast curr_parent_node_ to STMT_LIST_NODE*)
			//if ( ((IF_NODE*) curr_parent_node_.getParent()).getThenStatementListNode()) == ((STMT_LIST_NODE*) curr_parent_node_) )
				//change curr_parent_node_ to point to ELSE_STMT_LIST_NODE
				//We assume that it was pre-created when we created the IF_STMT_LIST_NODE
				//curr_parent_node_ =  (AST_NODE*) (((IF_NODE*) curr_parent_node_.getParent()).getElseStatementListNode())
			//else
				//change curr_parent_node_ to point to STMT_LIST_NODE that contains the IF_NODE
				//curr_parent_node_ = curr_parent_node_.getParent().getParent()
		//else
			//change curr_parent_node_ to point to grandparent node of curr_parent_node_
			//curr_parent_node_ must be STMT_LIST_NODE
			//it's parent can be PROCEDURE_NODE, WHILE_NODE or IF_NODE (if this is an ELSE_STMT_LIST_NODE)
			//therefore grandparent node can be PROGRAM_NODE or STMT_LIST_NODE
			//curr_parent_node_ = curr_parent_node_.getParent().getParent()





		//Part 3:
		//We make no assumptions that '}' ends this line. We check for any leftover non-whitespace characters
		//and call parseLine on the remainding string if there are remaining chars. 
		//check if there is remaining str
			//call parseLine on remainder of str
		//else end
		return 0;
	}

	//===== START OF HELPER FUNCTIONS =====
	int takesPrecedent(OperatorTypeEnum l_op, OperatorTypeEnum r_op) {
		//Returns 1 if left operator takes precendence
		if (l_op == op_mult && r_op == op_div && r_op == op_mod) {
			if (r_op == op_plus || l_op == op_min) {
				return 1;
			}
		}
		else if (l_op == op_plus || l_op == op_min) {
			if (r_op == op_mult && r_op == op_div && r_op == op_mod) {
				//-1 if right operator takes precedence
				return -1;
			}
		}
		else {
			//0 if neither
			//This includes any case where there is a paren in either op
			// or if both are the same
			return 0;
		}
	}

	ExpressionTypeEnum getExpressionType(OperatorTypeEnum op) {
		if (op == op_plus) {
			return plus;
		}
		else if (op == op_min) {
			return min;
		}
		else if (op == op_mult) {
			return times;
		}
		else if (op == op_div) {
			return div;
		}
		else if (op == op_mod) {
			return mod;
		}
		else {
			return -1;
		}
	}

	//===== END OF HELPER FUNCTIONS =====
