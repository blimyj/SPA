#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iterator>
#include <deque>
#include <set>

#include "PKB.h"
#include "Parser.h"
#include "PKB/ASTNode/NodeTypeEnum.h"
#include "PKB/ASTNode/RelationNode.h"

	int Parser::Parse() {

		return 0;
	}

	PKB Parser::parseFile(STRING filename) {
		//Construct program root node
		this->program_node_ = (std::make_shared<ProgramNode>)();
		this->pkb_builder_ = PKBBuilder();
		this->pkb_builder_.setProgramNode(this->program_node_);

		this->current_parent_node_ = this->program_node_;

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

			//After checking first two tokens, call appropriate parse function
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

			if (stmt_token == "while") {
				this->stmt_token_queue_.push_back(stmt_token); //This is "while" token
				parseWhile(&this->stmt_token_queue_, &this->process_token_stream_);
				continue;
			}

			if (stmt_token == "if") {
				this->stmt_token_queue_.push_back(stmt_token); //This is "if" token
				parseIfThen(&this->stmt_token_queue_, &this->process_token_stream_);
				continue;
			}

			if (stmt_token == "else") {
				this->stmt_token_queue_.push_back(stmt_token); //This is "else" token
				parseElse(&this->stmt_token_queue_, &this->process_token_stream_);
				continue;
			}

			if (stmt_token == "}") {
				parseStmtListClose();
				continue;
			}

			//Handler for all other tokens, prints them out
			throw "Unexpected Token Encountered.";
		}

		PKB pkb = this->pkb_builder_.build();
		
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

		//Check for arithmetic terminal tokens
		if (**iter == '+' || **iter == '-' || **iter == '*' || **iter == '/' || **iter == '%') {
			curr_token += **iter;
			++* iter;
			return curr_token;
		}

		//Check for "<" vs "<=" comparison terminal tokens
		if (*iter != eos && **iter == '<') { //Checks if first letter matches '<' terminal
			curr_token += **iter;
			++* iter;
			if (*iter != eos && **iter == '=') {
				curr_token += **iter;
				++* iter;
			}
			else {}
			return curr_token;
		}

		//Check for ">" vs ">=" comparison terminal tokens
		if (*iter != eos && **iter == '>') { //Checks if first letter matches '>' terminal
			curr_token += **iter;
			++* iter;
			if (*iter != eos && **iter == '=') {
				curr_token += **iter;
				++* iter;
			}
			else {}
			return curr_token;
		}


		//Check for boolean terminal "&&" tokens
		if (*iter != eos && **iter == '&') { //Checks if first letter matches "&" terminal
			curr_token += **iter;
			++* iter;
			if (*iter != eos && **iter == '&') {
				curr_token += **iter;
				++* iter;
				return curr_token;
			}
			else {
				curr_token = "UNEXPECTED TOKEN:" + curr_token;
				curr_token += **iter;
				++* iter;
				return curr_token;
			}
		}

		//Check for boolean terminal "||" tokens
		if (*iter != eos && **iter == '|') { //Checks if first letter matches '|' terminal
			curr_token += **iter;
			++* iter;
			if (*iter != eos && **iter == '|') {
				curr_token += **iter;
				++* iter;
				return curr_token;
			}
			else {
				curr_token = "UNEXPECTED TOKEN:" + curr_token;
				curr_token += **iter;
				++* iter;
				return curr_token;
			}
		}

		//Check for '' vs '!=' terminal tokens
		if (*iter != eos && **iter == '!') { //Checks if first letter matches '=' terminal
			curr_token += **iter;
			++* iter;
			if (*iter != eos && **iter == '=') {
				curr_token += **iter;
				++* iter;
			}
			else {}
			return curr_token;
		}

		//Check for other unexpected tokens
		curr_token += "UNEXPECTED TOKEN:";
		curr_token += **iter;
		++* iter;
		return curr_token;
	}

	int Parser::parseText(LIST_OF_STRINGS str_list) {

		// Not considered for now.
		return 0;
	}

	int Parser::parseWhile(STMT_TOKEN_QUEUE stmt_tok_queue, PROCESS_TOKEN_QUEUE proc_tok_queue) {

		if (this->stmt_token_queue_.front() != "while") {
			throw "Error: Expected 'while' terminal but was not found.";
		}
		this->stmt_token_queue_.pop_front(); // Remove stmt type token
		
		//Check for '('
		if (this->process_token_stream_.front() != "(") {
			throw "Error: Expected '(' terminal but was not found.";
		}
		//We no longer need to remove "(" terminal required because we parse this along with ')'
		//this->process_token_stream_.pop_front(); // Remove stmt type token

		//REPLACEMENT FOR THIRD TOKEN CONSUMPTION
		std::deque<std::shared_ptr<ASTNode>> output_node_stack = std::deque<std::shared_ptr<ASTNode>>();
		std::deque<RelOperatorTypeEnum> operator_stack = std::deque<RelOperatorTypeEnum>();
		RelOperatorTypeEnum op;
		RelOperatorTypeEnum temp_op;

		//===== Actual Code ======
		//Here we will keep consuming tokens until we reach '{'

		STRING rhs_token = this->process_token_stream_.front(); //Starts taking in tokens for condition
		this->process_token_stream_.pop_front(); // Remove var/const/operator/parentheses token for the next token

		//TODO: HANDLERS FOR EMPTY STACKS / UNEXCPECTED TOKENS
		//Need to handle gracefully

		while (!process_token_stream_.empty() && rhs_token != "{") {
			//These tokens will populate this->stmt_token_queue_
			this->stmt_token_queue_.push_back(rhs_token);
			rhs_token = this->process_token_stream_.front();
			this->process_token_stream_.pop_front(); // Remove var/const/operator/parentheses token for the next token
		}

		if (process_token_stream_.empty()) {
			throw "Error: Expected '{' terminal but was not found.";
		}

		//They will form the expr that is assigned to new_expr_node
		//Then they will be funneled through the shunting yard algo
		STRING temp_token = "";
		//While stmt_token_queue_ has tokens
		std::unordered_set<STRING> used_vars_set;

		while (!this->stmt_token_queue_.empty()) {
			//Get & remove first token from stmt_token_queue_
			temp_token = this->stmt_token_queue_.front();
			this->stmt_token_queue_.pop_front();

			//if isalpha(first_char) 
			if (isalpha(temp_token.at(0))) {
				//then create varnode enqueue to output_node_stack
				std::shared_ptr<VariableNode> new_var_node = std::make_shared<VariableNode>();
				new_var_node->setVariableName(temp_token);
				this->pkb_builder_.addVariableNode(new_var_node);
				//enqueue to output_stack
				output_node_stack.push_back(new_var_node);

				//add var to usedied_vars_set for Uses relationship
				used_vars_set.insert(temp_token);
			}
			else if (isdigit(temp_token.at(0))) {
				//else isdigit(first_char) then create const node
				std::shared_ptr<ConstantNode> new_const_node = std::make_shared<ConstantNode>();
				new_const_node->setValue(temp_token);
				this->pkb_builder_.addConstantNode(new_const_node);
				//enqueue to output_stack
				output_node_stack.push_back(new_const_node);
			}
			else {
				//Else means token is operator or parentheses
				//Create a Operator TypeEnum object
				if (temp_token == "+") {
					op = RelOperatorTypeEnum::ropPlus;
				}
				else if (temp_token == "-") {
					op = RelOperatorTypeEnum::ropMin;
				}
				else if (temp_token == "*") {
					op = RelOperatorTypeEnum::ropMult;
				}
				else if (temp_token == "/") {
					op = RelOperatorTypeEnum::ropDiv;
				}
				else if (temp_token == "%") {
					op = RelOperatorTypeEnum::ropMod;
				}
				else if (temp_token == "(") {
					op = RelOperatorTypeEnum::ropLparen;
				}
				else if (temp_token == ")") {
					op = RelOperatorTypeEnum::ropRparen;
				}
				else if (temp_token == "==") {
					op = RelOperatorTypeEnum::ropEq;
				}
				else if (temp_token == "!=") {
					op = RelOperatorTypeEnum::ropNeq;
				}
				else if (temp_token == ">") {
					op = RelOperatorTypeEnum::ropGt;
				}
				else if (temp_token == ">=") {
					op = RelOperatorTypeEnum::ropGte;
				}
				else if (temp_token == "<") {
					op = RelOperatorTypeEnum::ropLt;
				}
				else if (temp_token == "<=") {
					op = RelOperatorTypeEnum::ropLte;
				}
				else if (temp_token == "!") {
					op = RelOperatorTypeEnum::ropNot;
				}
				else if (temp_token == "||") {
					op = RelOperatorTypeEnum::ropOr;
				}
				else if (temp_token == "&&") {
					op = RelOperatorTypeEnum::ropAnd;
				}
				else {
					//If not any of the above tokens, return an error.
					STRING msg = "Error: Expected an operator, but \"" + temp_token + "\" found instead.";
					throw msg;
				}

				//throw into operator stack
				if (op == RelOperatorTypeEnum::ropLparen) {
					operator_stack.push_back(op);
				}
				else if (op == RelOperatorTypeEnum::ropRparen) {
					while (!operator_stack.empty() && operator_stack.back() != RelOperatorTypeEnum::ropLparen) {
						//Pop operator from operator stack onto the output queue. 
						//When we want to place an operator into the output stack,we instead create a new ExpressionNode (top Node of Stack is rhs, 2nd top is lhs)
						temp_op = operator_stack.back();
						operator_stack.pop_back();
						
						std::shared_ptr<ASTNode> rhs_operand;
						std::shared_ptr<ASTNode> lhs_operand;

						//Create a rel_node or expr_node based on whether temp_op is a relation or arithmetic operator
						if (isBooleanOp(temp_op) && temp_op == RelOperatorTypeEnum::ropNot) {
							lhs_operand = output_node_stack.back();
							output_node_stack.pop_back();

							//Note we must check if we are able to pop out 1 operand & the 1 operand is the type we want
							if (lhs_operand->getNodeType() != NodeTypeEnum::relationNode 
								&& lhs_operand->getNodeType() != NodeTypeEnum::conditionNode) {
								throw "Error: Expected RelationNode/ConditionNode, but received another type instead.";
							}

							ConditionTypeEnum cond_type = getBooleanRelationType(temp_op);
							if (temp_op == RelOperatorTypeEnum::ropNot) {

								std::shared_ptr<ConditionNode> new_cond_node = std::make_shared<ConditionNode>();
								new_cond_node->setConditionType(cond_type);
								//Even though the operand is techincally on the right of the not operator,
								//it is placed on the left for the sake of consistency when accessing.
								new_cond_node->setLeftAstNode(lhs_operand);

								//We then place this ConditionNode into the output_node_stack
								output_node_stack.push_back(new_cond_node);
							}
						}
						else if (isArithmeticOp(temp_op)) {
							rhs_operand = output_node_stack.back();
							output_node_stack.pop_back();

							lhs_operand = output_node_stack.back();
							output_node_stack.pop_back();

							//Note we must check if we are able to pop out 2 operands & the 2 operands is the type we want
							if (rhs_operand->getNodeType() != NodeTypeEnum::expressionNode
								&& rhs_operand->getNodeType() != NodeTypeEnum::variableNode
								&& rhs_operand->getNodeType() != NodeTypeEnum::constantNode) {
								throw "Error: Expected ExpressionNode/VariableNode/ConstantNode, but received another type instead.";
							}

							if (lhs_operand->getNodeType() != NodeTypeEnum::expressionNode
								&& lhs_operand->getNodeType() != NodeTypeEnum::variableNode
								&& lhs_operand->getNodeType() != NodeTypeEnum::constantNode) {
								throw "Error: Expected ExpressionNode/VariableNode/ConstantNode, but received another type instead.";
							}

							ExpressionTypeEnum expr_type = getExpressionType(temp_op);

							std::shared_ptr<ExpressionNode> new_expr_node = std::make_shared<ExpressionNode>();
							new_expr_node->setExpressionType(expr_type);
							new_expr_node->setLeftAstNode(lhs_operand);
							new_expr_node->setRightAstNode(rhs_operand);

							//We then place this ExpressionNode into the output_node_stack
							output_node_stack.push_back(new_expr_node);
						}
						else if (isRelationOp(temp_op)) {
							RelationTypeEnum rel_type = getArithmeticRelationType(temp_op);

							rhs_operand = output_node_stack.back();
							output_node_stack.pop_back();

							lhs_operand = output_node_stack.back();
							output_node_stack.pop_back();

							//Note we must check if we are able to pop out 2 operands & the 2 operands is the type we want
							if (rhs_operand->getNodeType() != NodeTypeEnum::expressionNode
								&& rhs_operand->getNodeType() != NodeTypeEnum::variableNode
								&& rhs_operand->getNodeType() != NodeTypeEnum::constantNode) {
								throw "Error: Expected ExpressionNode/VariableNode/ConstantNode, but received another type instead.";
							}

							if (lhs_operand->getNodeType() != NodeTypeEnum::expressionNode
								&& lhs_operand->getNodeType() != NodeTypeEnum::variableNode
								&& lhs_operand->getNodeType() != NodeTypeEnum::constantNode) {
								throw "Error: Expected ExpressionNode/VariableNode/ConstantNode, but received another type instead.";
							}

							std::shared_ptr<RelationNode> new_rel_node = std::make_shared<RelationNode>();
							new_rel_node->setRelationType(rel_type);
							new_rel_node->setLeftAstNode(lhs_operand);
							new_rel_node->setRightAstNode(rhs_operand);

							//We then place this RelationNode into the output_node_stack
							output_node_stack.push_back(new_rel_node);
						}
						else if (isBooleanOp(temp_op)) {
							ConditionTypeEnum cond_type = getBooleanRelationType(temp_op);

							rhs_operand = output_node_stack.back();
							output_node_stack.pop_back();

							lhs_operand = output_node_stack.back();
							output_node_stack.pop_back();

							//Note we must check if we are able to pop out 2 operands & the 2 operands is the type we want
							if (rhs_operand->getNodeType() != NodeTypeEnum::relationNode
								&& rhs_operand->getNodeType() != NodeTypeEnum::conditionNode) {
								throw "Error: Expected RelationNode/ConditionNode, but received another type instead.";
							}

							if (lhs_operand->getNodeType() != NodeTypeEnum::relationNode
								&& lhs_operand->getNodeType() != NodeTypeEnum::conditionNode) {
								throw "Error: Expected RelationNode/ConditionNode, but received another type instead.";
							}

							if (temp_op == RelOperatorTypeEnum::ropAnd || temp_op == RelOperatorTypeEnum::ropOr) {
								std::shared_ptr<ConditionNode> new_cond_node = std::make_shared<ConditionNode>();
								new_cond_node->setConditionType(cond_type);
								new_cond_node->setLeftAstNode(lhs_operand);
								new_cond_node->setRightAstNode(rhs_operand);

								//We then place this ConditionNode into the output_node_stack
								output_node_stack.push_back(new_cond_node);
							}
							else {
								throw "Error: Undefined behaviour.";
							}
						}
						else {
							throw "Error: Undefined behaviour.";
						}
					}
					// If operator_stack.empty() that means there are mismatched parentheses
					if (operator_stack.empty()) throw "Error: Mismatched parentheses found.";
					if (operator_stack.back() == RelOperatorTypeEnum::ropLparen) {
						operator_stack.pop_back();
					}
				}
				else {
					//This is when arithmetic operators are being handled
					while (!operator_stack.empty() && operator_stack.back() != RelOperatorTypeEnum::ropLparen
						&& ((takesPrecedent(operator_stack.back(), op) == 1)
							|| (takesPrecedent(operator_stack.back(), op) == 0))) {
						temp_op = operator_stack.back();
						operator_stack.pop_back();

						std::shared_ptr<ASTNode> rhs_operand;
						std::shared_ptr<ASTNode> lhs_operand;

						//Create a rel_node or expr_node based on whether temp_op is a relation or arithmetic operator
						if (isBooleanOp(temp_op) && temp_op == RelOperatorTypeEnum::ropNot) {
							lhs_operand = output_node_stack.back();
							output_node_stack.pop_back();

							//Note we must check if we are able to pop out 1 operand & the 1 operand is the type we want
							if (lhs_operand->getNodeType() != NodeTypeEnum::relationNode
								&& lhs_operand->getNodeType() != NodeTypeEnum::conditionNode) {
								throw "Error: Expected RelationNode/ConditionNode, but received another type instead.";
							}

							ConditionTypeEnum cond_type = getBooleanRelationType(temp_op);
							if (temp_op == RelOperatorTypeEnum::ropNot) {

								std::shared_ptr<ConditionNode> new_cond_node = std::make_shared<ConditionNode>();
								new_cond_node->setConditionType(cond_type);
								//Even though the operand is techincally on the right of the not operator,
								//it is placed on the left for the sake of consistency when accessing.
								new_cond_node->setLeftAstNode(lhs_operand);

								//We then place this ConditionNode into the output_node_stack
								output_node_stack.push_back(new_cond_node);
							}
						}
						else if (isArithmeticOp(temp_op)) {
							rhs_operand = output_node_stack.back();
							output_node_stack.pop_back();

							lhs_operand = output_node_stack.back();
							output_node_stack.pop_back();

							//Note we must check if we are able to pop out 2 operands & the 2 operands is the type we want
							if (rhs_operand->getNodeType() != NodeTypeEnum::expressionNode
								&& rhs_operand->getNodeType() != NodeTypeEnum::variableNode
								&& rhs_operand->getNodeType() != NodeTypeEnum::constantNode) {
								throw "Error: Expected ExpressionNode/VariableNode/ConstantNode, but received another type instead.";
							}

							if (lhs_operand->getNodeType() != NodeTypeEnum::expressionNode
								&& lhs_operand->getNodeType() != NodeTypeEnum::variableNode
								&& lhs_operand->getNodeType() != NodeTypeEnum::constantNode) {
								throw "Error: Expected ExpressionNode/VariableNode/ConstantNode, but received another type instead.";
							}

							ExpressionTypeEnum expr_type = getExpressionType(temp_op);

							std::shared_ptr<ExpressionNode> new_expr_node = std::make_shared<ExpressionNode>();
							new_expr_node->setExpressionType(expr_type);
							new_expr_node->setLeftAstNode(lhs_operand);
							new_expr_node->setRightAstNode(rhs_operand);

							//We then place this ExpressionNode into the output_node_stack
							output_node_stack.push_back(new_expr_node);
						}
						else if (isRelationOp(temp_op)) {
							RelationTypeEnum rel_type = getArithmeticRelationType(temp_op);

							rhs_operand = output_node_stack.back();
							output_node_stack.pop_back();

							lhs_operand = output_node_stack.back();
							output_node_stack.pop_back();

							//Note we must check if we are able to pop out 2 operands & the 2 operands is the type we want
							if (rhs_operand->getNodeType() != NodeTypeEnum::expressionNode
								&& rhs_operand->getNodeType() != NodeTypeEnum::variableNode
								&& rhs_operand->getNodeType() != NodeTypeEnum::constantNode) {
								throw "Error: Expected ExpressionNode/VariableNode/ConstantNode, but received another type instead.";
							}

							if (lhs_operand->getNodeType() != NodeTypeEnum::expressionNode
								&& lhs_operand->getNodeType() != NodeTypeEnum::variableNode
								&& lhs_operand->getNodeType() != NodeTypeEnum::constantNode) {
								throw "Error: Expected ExpressionNode/VariableNode/ConstantNode, but received another type instead.";
							}

							std::shared_ptr<RelationNode> new_rel_node = std::make_shared<RelationNode>();
							new_rel_node->setRelationType(rel_type);
							new_rel_node->setLeftAstNode(lhs_operand);
							new_rel_node->setRightAstNode(rhs_operand);

							//We then place this RelationNode into the output_node_stack
							output_node_stack.push_back(new_rel_node);
						}
						else if (isBooleanOp(temp_op)) {
							ConditionTypeEnum cond_type = getBooleanRelationType(temp_op);

							rhs_operand = output_node_stack.back();
							output_node_stack.pop_back();

							lhs_operand = output_node_stack.back();
							output_node_stack.pop_back();

							//Note we must check if we are able to pop out 2 operands & the 2 operands is the type we want
							if (rhs_operand->getNodeType() != NodeTypeEnum::relationNode
								&& rhs_operand->getNodeType() != NodeTypeEnum::conditionNode) {
								throw "Error: Expected RelationNode/ConditionNode, but received another type instead.";
							}

							if (lhs_operand->getNodeType() != NodeTypeEnum::relationNode
								&& lhs_operand->getNodeType() != NodeTypeEnum::conditionNode) {
								throw "Error: Expected RelationNode/ConditionNode, but received another type instead.";
							}

							if (temp_op == RelOperatorTypeEnum::ropAnd || temp_op == RelOperatorTypeEnum::ropOr) {
								std::shared_ptr<ConditionNode> new_cond_node = std::make_shared<ConditionNode>();
								new_cond_node->setConditionType(cond_type);
								new_cond_node->setLeftAstNode(lhs_operand);
								new_cond_node->setRightAstNode(rhs_operand);

								//We then place this ConditionNode into the output_node_stack
								output_node_stack.push_back(new_cond_node);
							}
							else {
								throw "Error: Undefined behaviour.";
							}
						}
						else {
							throw "Error: Undefined behaviour.";
						}
					}
					//Push operator to operator stack
					operator_stack.push_back(op);
				}
			}
		}

		//Handle remaining operators in operator_stack
		while (!operator_stack.empty()) {
			if (operator_stack.back() == RelOperatorTypeEnum::ropLparen || operator_stack.back() == RelOperatorTypeEnum::ropRparen) {
				//Presence of parenthesis indicates mismatched parenthesis as they should have all been discarded earlier.
				throw "Error: Mismatched parenthesis found.";
			}
			temp_op = operator_stack.back();
			operator_stack.pop_back();

			std::shared_ptr<ASTNode> rhs_operand;
			std::shared_ptr<ASTNode> lhs_operand;

			//Create a rel_node or expr_node based on whether temp_op is a relation or arithmetic operator
			if (isBooleanOp(temp_op) && temp_op == RelOperatorTypeEnum::ropNot) {
				lhs_operand = output_node_stack.back();
				output_node_stack.pop_back();

				//Note we must check if we are able to pop out 1 operand & the 1 operand is the type we want
				if (lhs_operand->getNodeType() != NodeTypeEnum::relationNode
					&& lhs_operand->getNodeType() != NodeTypeEnum::conditionNode) {
					throw "Error: Expected RelationNode/ConditionNode, but received another type instead.";
				}

				ConditionTypeEnum cond_type = getBooleanRelationType(temp_op);
				if (temp_op == RelOperatorTypeEnum::ropNot) {

					std::shared_ptr<ConditionNode> new_cond_node = std::make_shared<ConditionNode>();
					new_cond_node->setConditionType(cond_type);
					//Even though the operand is techincally on the right of the not operator,
					//it is placed on the left for the sake of consistency when accessing.
					new_cond_node->setLeftAstNode(lhs_operand);

					//We then place this ConditionNode into the output_node_stack
					output_node_stack.push_back(new_cond_node);
				}
			}
			else if (isArithmeticOp(temp_op)) {
				rhs_operand = output_node_stack.back();
				output_node_stack.pop_back();

				lhs_operand = output_node_stack.back();
				output_node_stack.pop_back();

				//Note we must check if we are able to pop out 2 operands & the 2 operands is the type we want
				if (rhs_operand->getNodeType() != NodeTypeEnum::expressionNode
					&& rhs_operand->getNodeType() != NodeTypeEnum::variableNode
					&& rhs_operand->getNodeType() != NodeTypeEnum::constantNode) {
					throw "Error: Expected ExpressionNode/VariableNode/ConstantNode, but received another type instead.";
				}

				if (lhs_operand->getNodeType() != NodeTypeEnum::expressionNode
					&& lhs_operand->getNodeType() != NodeTypeEnum::variableNode
					&& lhs_operand->getNodeType() != NodeTypeEnum::constantNode) {
					throw "Error: Expected ExpressionNode/VariableNode/ConstantNode, but received another type instead.";
				}

				ExpressionTypeEnum expr_type = getExpressionType(temp_op);

				std::shared_ptr<ExpressionNode> new_expr_node = std::make_shared<ExpressionNode>();
				new_expr_node->setExpressionType(expr_type);
				new_expr_node->setLeftAstNode(lhs_operand);
				new_expr_node->setRightAstNode(rhs_operand);

				//We then place this ExpressionNode into the output_node_stack
				output_node_stack.push_back(new_expr_node);
			}
			else if (isRelationOp(temp_op)) {
				RelationTypeEnum rel_type = getArithmeticRelationType(temp_op);

				rhs_operand = output_node_stack.back();
				output_node_stack.pop_back();

				lhs_operand = output_node_stack.back();
				output_node_stack.pop_back();

				//Note we must check if we are able to pop out 2 operands & the 2 operands is the type we want
				if (rhs_operand->getNodeType() != NodeTypeEnum::expressionNode
					&& rhs_operand->getNodeType() != NodeTypeEnum::variableNode
					&& rhs_operand->getNodeType() != NodeTypeEnum::constantNode) {
					throw "Error: Expected ExpressionNode/VariableNode/ConstantNode, but received another type instead.";
				}

				if (lhs_operand->getNodeType() != NodeTypeEnum::expressionNode
					&& lhs_operand->getNodeType() != NodeTypeEnum::variableNode
					&& lhs_operand->getNodeType() != NodeTypeEnum::constantNode) {
					throw "Error: Expected ExpressionNode/VariableNode/ConstantNode, but received another type instead.";
				}

				std::shared_ptr<RelationNode> new_rel_node = std::make_shared<RelationNode>();
				new_rel_node->setRelationType(rel_type);
				new_rel_node->setLeftAstNode(lhs_operand);
				new_rel_node->setRightAstNode(rhs_operand);

				//We then place this RelationNode into the output_node_stack
				output_node_stack.push_back(new_rel_node);
			}
			else if (isBooleanOp(temp_op)) {
				ConditionTypeEnum cond_type = getBooleanRelationType(temp_op);

				rhs_operand = output_node_stack.back();
				output_node_stack.pop_back();

				lhs_operand = output_node_stack.back();
				output_node_stack.pop_back();

				//Note we must check if we are able to pop out 2 operands & the 2 operands is the type we want
				if (rhs_operand->getNodeType() != NodeTypeEnum::relationNode
					&& rhs_operand->getNodeType() != NodeTypeEnum::conditionNode) {
					throw "Error: Expected RelationNode/ConditionNode, but received another type instead.";
				}

				if (lhs_operand->getNodeType() != NodeTypeEnum::relationNode
					&& lhs_operand->getNodeType() != NodeTypeEnum::conditionNode) {
					throw "Error: Expected RelationNode/ConditionNode, but received another type instead.";
				}

				if (temp_op == RelOperatorTypeEnum::ropAnd || temp_op == RelOperatorTypeEnum::ropOr) {
					std::shared_ptr<ConditionNode> new_cond_node = std::make_shared<ConditionNode>();
					new_cond_node->setConditionType(cond_type);
					new_cond_node->setLeftAstNode(lhs_operand);
					new_cond_node->setRightAstNode(rhs_operand);

					//We then place this ConditionNode into the output_node_stack
					output_node_stack.push_back(new_cond_node);
				}
				else {
					throw "Error: Undefined behaviour.";
				}
			}
			else {
				throw "Error: Undefined behaviour.";
			}
		}

		//Once ';' is reached or stmt_token_queue_ is empty we should have only 1 expression node or VarNode/ConstNode in the output stack.
		if (output_node_stack.size() != 1) {
			throw "Error: Expected 1 node left in output_node_stack after parsing all tokens.";
		}
		//Note that we must check if we need to encapsulate RelationNode to return a proper ConditionNode
		std::shared_ptr<ASTNode> last_node = output_node_stack.back();
		std::shared_ptr<ConditionNode> result;
		output_node_stack.pop_back();
		if (last_node->getNodeType() == NodeTypeEnum::variableNode
			|| last_node->getNodeType() == NodeTypeEnum::constantNode) {

			//TODO: Check if such node types are valid as condition.
			throw "Error: ConditionNode/RelationNode expected but VariableNode/ConstantNode found.";
		}
		else if (last_node->getNodeType() == NodeTypeEnum::expressionNode) {
			//TODO: Check if such node types are valid as condition.
			throw "Error: ConditionNode/RelationNode expected but ExpressionNode found.";
		}
		else if (last_node->getNodeType() == NodeTypeEnum::relationNode) {
			result = std::make_shared<ConditionNode>();
			std::static_pointer_cast<ConditionNode>(result)->setConditionType(ConditionTypeEnum::none);
			std::static_pointer_cast<ConditionNode>(result)->setLeftAstNode(last_node);
		}
		else if (last_node->getNodeType() == NodeTypeEnum::conditionNode) {
			result = std::static_pointer_cast<ConditionNode>(last_node);
		}
		else {
			throw "Error: ConditionNode/RelationNode expected, unknown node type found.";
		}

		//Construct new_stmt_list_node & new_procedure_node
		std::shared_ptr<StatementListNode> new_stmt_list_node = std::make_shared<StatementListNode>();

		std::shared_ptr<WhileNode> new_while_node = std::make_shared<WhileNode>();
		new_while_node->setConditionNode(result);
		new_while_node->setWhileStatementListNode(new_stmt_list_node);
		
		this->stmt_num_++;
		new_while_node->setStatementNumber(this->stmt_num_);
		std::static_pointer_cast<StatementListNode>(this->current_parent_node_)->addStatementNode(new_while_node);
		new_while_node->setStatementListNode(std::static_pointer_cast<StatementListNode>(this->current_parent_node_));		
		


		//add Parent relationship if this->current_parent_node_->getParentNode() is not procedureNode
		if (this->current_parent_node_->getParentNode()->getNodeType() != NodeTypeEnum::procedureNode) {
			this->pkb_builder_.addParent(std::static_pointer_cast<StatementNode>(this->current_parent_node_->getParentNode())->getStatementNumber()
				, new_while_node->getStatementNumber());
		}

		//add Follows relationship if this statement is not the first statement of this->current_parent_node_
		if (new_while_node != std::static_pointer_cast<StatementListNode>(this->current_parent_node_)->getStatementNodeList().at(0)) {
			int this_stmt_num = new_while_node->getStatementNumber();
			STMT_LIST_NODE_PTR stmtList = std::static_pointer_cast<StatementListNode>(this->current_parent_node_);
			STMT_NODE_PTR prevStmt = std::static_pointer_cast<StatementNode>(stmtList->getChildrenNode().end()[-2]);

			this->pkb_builder_.addFollows(prevStmt->getStatementNumber()
				, new_while_node->getStatementNumber());
		}

		//add Uses Relationship for all vars
		for (STRING var_name : used_vars_set) {
			//Set Uses Relationship for this statement
			this->pkb_builder_.addUses(new_while_node->getStatementNumber()
				, var_name);

			//Set Uses Relationship for all containers of this statement by going up 2 steps until we hit ProcedureNode.
			std::shared_ptr<ASTNode> curr_container = this->current_parent_node_->getParentNode();
			STMT_NUM curr_stmtnum = 0;
			while (curr_container->getNodeType() != NodeTypeEnum::procedureNode) {
				//Get stmt number of container
				if (curr_container->getNodeType() == NodeTypeEnum::whileNode) {
					curr_stmtnum = std::static_pointer_cast<WhileNode>(curr_container)->getStatementNumber();
				}
				else if (curr_container->getNodeType() == NodeTypeEnum::ifNode) {
					curr_stmtnum = std::static_pointer_cast<IfNode>(curr_container)->getStatementNumber();
				}
				//call addUses
				this->pkb_builder_.addUses(curr_stmtnum, var_name);

				//Check if can go up 2 steps
				if (curr_container->getParentNode()->getParentNode() == NULL) {
					//Throw exception if cant
					throw "Exception in parseWhile: curr_container missing grandparent node.";
				}
				else {
					//curr_container = go up 2 steps
					curr_container = curr_container->getParentNode()->getParentNode();
				}
			}
			//call addUses for procedureNode
			if (curr_container->getNodeType() != NodeTypeEnum::procedureNode) {
				//Throw exception if cant
				throw "Exception in parseWhile: curr_container should be ProcedureNode.";
			}
			else {
				//addUses for ProcedureNode
				std::static_pointer_cast<ProcedureNode>(curr_container)->getProcedureName();
				this->pkb_builder_.addUses(std::static_pointer_cast<ProcedureNode>(curr_container)->getProcedureName()
					, var_name);
			}
		}

		//change parent tracker to stmtlistnode_ptr
		this->current_parent_node_ = new_stmt_list_node;

		//Need to add new_stmt_list_node & new_while_node to PKB tables
		this->pkb_builder_.addWhileNode(new_while_node);
		this->pkb_builder_.addStatementNode(new_while_node);
		this->pkb_builder_.addStatementListNode(new_stmt_list_node);

		return 0;
	}

	int Parser::parseIfThen(STMT_TOKEN_QUEUE stmt_tok_queue, PROCESS_TOKEN_QUEUE proc_tok_queue) {
		//We assume that this opening segment will either terminate with '{' or ';' with the exception of whitespaces and newline?

		if (this->stmt_token_queue_.front() != "if") {
			throw "Error: Expected \"if\" terminal but not found.";
		}
		this->stmt_token_queue_.pop_front(); // Remove stmt type token

		//Check for '('
		if (this->process_token_stream_.front() != "(") {
			throw "Error: Expected \"(\" terminal but not found.";
		}
		//We no longer need to remove "(" terminal required because we parse this along with ')'
		//this->process_token_stream_.pop_front(); // Remove stmt type token

		//REPLACEMENT FOR THIRD TOKEN CONSUMPTION
		std::deque<std::shared_ptr<ASTNode>> output_node_stack = std::deque<std::shared_ptr<ASTNode>>();
		std::deque<RelOperatorTypeEnum> operator_stack = std::deque<RelOperatorTypeEnum>();
		RelOperatorTypeEnum op;
		RelOperatorTypeEnum temp_op;

		//===== Actual Code ======
		//Here we will keep consuming tokens until we reach '{'

		STRING rhs_token = this->process_token_stream_.front(); //Starts taking in tokens for condition
		this->process_token_stream_.pop_front(); // Remove var/const/operator/parentheses token for the next token

		//TODO: HANDLERS FOR EMPTY STACKS / UNEXCPECTED TOKENS
		//Need to handle gracefully

		while (!process_token_stream_.empty() && rhs_token != "then") {
			//These tokens will populate this->stmt_token_queue_
			this->stmt_token_queue_.push_back(rhs_token);
			rhs_token = this->process_token_stream_.front();
			this->process_token_stream_.pop_front(); // Remove var/const/operator/parentheses token for the next token
		}

		if (process_token_stream_.empty()) {
			throw "Error: Expected 'then' terminal but was not found.";
		}

		//They will form the expr that is assigned to new_expr_node
		//Then they will be funneled through the shunting yard algo
		STRING temp_token = "";
		//While stmt_token_queue_ has tokens
		std::unordered_set<STRING> used_vars_set;

		while (!this->stmt_token_queue_.empty()) {
			//Get & remove first token from stmt_token_queue_
			temp_token = this->stmt_token_queue_.front();
			this->stmt_token_queue_.pop_front();

			//if isalpha(first_char) 
			if (isalpha(temp_token.at(0))) {
				//then create varnode enqueue to output_node_stack
				std::shared_ptr<VariableNode> new_var_node = std::make_shared<VariableNode>();
				new_var_node->setVariableName(temp_token);
				this->pkb_builder_.addVariableNode(new_var_node);
				//enqueue to output_stack
				output_node_stack.push_back(new_var_node);

				//add var to usedied_vars_set for Uses relationship
				used_vars_set.insert(temp_token);
			}
			else if (isdigit(temp_token.at(0))) {
				//else isdigit(first_char) then create const node
				std::shared_ptr<ConstantNode> new_const_node = std::make_shared<ConstantNode>();
				new_const_node->setValue(temp_token);
				this->pkb_builder_.addConstantNode(new_const_node);
				//enqueue to output_stack
				output_node_stack.push_back(new_const_node);
			}
			else {
				//Else means token is operator or parentheses
				//Create a Operator TypeEnum object
				if (temp_token == "+") {
					op = RelOperatorTypeEnum::ropPlus;
				}
				else if (temp_token == "-") {
					op = RelOperatorTypeEnum::ropMin;
				}
				else if (temp_token == "*") {
					op = RelOperatorTypeEnum::ropMult;
				}
				else if (temp_token == "/") {
					op = RelOperatorTypeEnum::ropDiv;
				}
				else if (temp_token == "%") {
					op = RelOperatorTypeEnum::ropMod;
				}
				else if (temp_token == "(") {
					op = RelOperatorTypeEnum::ropLparen;
				}
				else if (temp_token == ")") {
					op = RelOperatorTypeEnum::ropRparen;
				}
				else if (temp_token == "==") {
					op = RelOperatorTypeEnum::ropEq;
				}
				else if (temp_token == "!=") {
					op = RelOperatorTypeEnum::ropNeq;
				}
				else if (temp_token == ">") {
					op = RelOperatorTypeEnum::ropGt;
				}
				else if (temp_token == ">=") {
					op = RelOperatorTypeEnum::ropGte;
				}
				else if (temp_token == "<") {
					op = RelOperatorTypeEnum::ropLt;
				}
				else if (temp_token == "<=") {
					op = RelOperatorTypeEnum::ropLte;
				}
				else if (temp_token == "!") {
					op = RelOperatorTypeEnum::ropNot;
				}
				else if (temp_token == "||") {
					op = RelOperatorTypeEnum::ropOr;
				}
				else if (temp_token == "&&") {
					op = RelOperatorTypeEnum::ropAnd;
				}
				else {
					//If not any of the above tokens, return an error.
					STRING msg = "Error: Expected an operator, but \"" + temp_token + "\" found instead.";
					throw msg;
				}

				//throw into operator stack
				if (op == RelOperatorTypeEnum::ropLparen) {
					operator_stack.push_back(op);
				}
				else if (op == RelOperatorTypeEnum::ropRparen) {
					while (!operator_stack.empty() && operator_stack.back() != RelOperatorTypeEnum::ropLparen) {
						//Pop operator from operator stack onto the output queue. 
						//When we want to place an operator into the output stack,we instead create a new ExpressionNode (top Node of Stack is rhs, 2nd top is lhs)
						temp_op = operator_stack.back();
						operator_stack.pop_back();

						std::shared_ptr<ASTNode> rhs_operand;
						std::shared_ptr<ASTNode> lhs_operand;

						//Create a rel_node or expr_node based on whether temp_op is a relation or arithmetic operator
						if (isBooleanOp(temp_op) && temp_op == RelOperatorTypeEnum::ropNot) {
							lhs_operand = output_node_stack.back();
							output_node_stack.pop_back();

							//Note we must check if we are able to pop out 1 operand & the 1 operand is the type we want
							if (lhs_operand->getNodeType() != NodeTypeEnum::relationNode
								&& lhs_operand->getNodeType() != NodeTypeEnum::conditionNode) {
								throw "Error: Expected RelationNode/ConditionNode, but received another type instead.";
							}

							ConditionTypeEnum cond_type = getBooleanRelationType(temp_op);
							if (temp_op == RelOperatorTypeEnum::ropNot) {

								std::shared_ptr<ConditionNode> new_cond_node = std::make_shared<ConditionNode>();
								new_cond_node->setConditionType(cond_type);
								//Even though the operand is techincally on the right of the not operator,
								//it is placed on the left for the sake of consistency when accessing.
								new_cond_node->setLeftAstNode(lhs_operand);

								//We then place this ConditionNode into the output_node_stack
								output_node_stack.push_back(new_cond_node);
							}
						}
						else if (isArithmeticOp(temp_op)) {
							rhs_operand = output_node_stack.back();
							output_node_stack.pop_back();

							lhs_operand = output_node_stack.back();
							output_node_stack.pop_back();

							//Note we must check if we are able to pop out 2 operands & the 2 operands is the type we want
							if (rhs_operand->getNodeType() != NodeTypeEnum::expressionNode
								&& rhs_operand->getNodeType() != NodeTypeEnum::variableNode
								&& rhs_operand->getNodeType() != NodeTypeEnum::constantNode) {
								throw "Error: Expected ExpressionNode/VariableNode/ConstantNode, but received another type instead.";
							}

							if (lhs_operand->getNodeType() != NodeTypeEnum::expressionNode
								&& lhs_operand->getNodeType() != NodeTypeEnum::variableNode
								&& lhs_operand->getNodeType() != NodeTypeEnum::constantNode) {
								throw "Error: Expected ExpressionNode/VariableNode/ConstantNode, but received another type instead.";
							}

							ExpressionTypeEnum expr_type = getExpressionType(temp_op);

							std::shared_ptr<ExpressionNode> new_expr_node = std::make_shared<ExpressionNode>();
							new_expr_node->setExpressionType(expr_type);
							new_expr_node->setLeftAstNode(lhs_operand);
							new_expr_node->setRightAstNode(rhs_operand);

							//We then place this ExpressionNode into the output_node_stack
							output_node_stack.push_back(new_expr_node);
						}
						else if (isRelationOp(temp_op)) {
							RelationTypeEnum rel_type = getArithmeticRelationType(temp_op);

							rhs_operand = output_node_stack.back();
							output_node_stack.pop_back();

							lhs_operand = output_node_stack.back();
							output_node_stack.pop_back();

							//Note we must check if we are able to pop out 2 operands & the 2 operands is the type we want
							if (rhs_operand->getNodeType() != NodeTypeEnum::expressionNode
								&& rhs_operand->getNodeType() != NodeTypeEnum::variableNode
								&& rhs_operand->getNodeType() != NodeTypeEnum::constantNode) {
								throw "Error: Expected ExpressionNode/VariableNode/ConstantNode, but received another type instead.";
							}

							if (lhs_operand->getNodeType() != NodeTypeEnum::expressionNode
								&& lhs_operand->getNodeType() != NodeTypeEnum::variableNode
								&& lhs_operand->getNodeType() != NodeTypeEnum::constantNode) {
								throw "Error: Expected ExpressionNode/VariableNode/ConstantNode, but received another type instead.";
							}

							std::shared_ptr<RelationNode> new_rel_node = std::make_shared<RelationNode>();
							new_rel_node->setRelationType(rel_type);
							new_rel_node->setLeftAstNode(lhs_operand);
							new_rel_node->setRightAstNode(rhs_operand);

							//We then place this RelationNode into the output_node_stack
							output_node_stack.push_back(new_rel_node);
						}
						else if (isBooleanOp(temp_op)) {
							ConditionTypeEnum cond_type = getBooleanRelationType(temp_op);

							rhs_operand = output_node_stack.back();
							output_node_stack.pop_back();

							lhs_operand = output_node_stack.back();
							output_node_stack.pop_back();

							//Note we must check if we are able to pop out 2 operands & the 2 operands is the type we want
							if (rhs_operand->getNodeType() != NodeTypeEnum::relationNode
								&& rhs_operand->getNodeType() != NodeTypeEnum::conditionNode) {
								throw "Error: Expected RelationNode/ConditionNode, but received another type instead.";
							}

							if (lhs_operand->getNodeType() != NodeTypeEnum::relationNode
								&& lhs_operand->getNodeType() != NodeTypeEnum::conditionNode) {
								throw "Error: Expected RelationNode/ConditionNode, but received another type instead.";
							}

							if (temp_op == RelOperatorTypeEnum::ropAnd || temp_op == RelOperatorTypeEnum::ropOr) {
								std::shared_ptr<ConditionNode> new_cond_node = std::make_shared<ConditionNode>();
								new_cond_node->setConditionType(cond_type);
								new_cond_node->setLeftAstNode(lhs_operand);
								new_cond_node->setRightAstNode(rhs_operand);

								//We then place this ConditionNode into the output_node_stack
								output_node_stack.push_back(new_cond_node);
							}
							else {
								throw "Error: Undefined behaviour.";
							}
						}
						else {
							throw "Error: Undefined behaviour.";
						}
					}
					// If operator_stack.empty() that means there are mismatched parentheses
					if (operator_stack.empty()) throw "Error: Mismatched parentheses found.";
					if (operator_stack.back() == RelOperatorTypeEnum::ropLparen) {
						operator_stack.pop_back();
					}
				}
				else {
					//This is when arithmetic operators are being handled
					while (!operator_stack.empty() && operator_stack.back() != RelOperatorTypeEnum::ropLparen
						&& ((takesPrecedent(operator_stack.back(), op) == 1)
							|| (takesPrecedent(operator_stack.back(), op) == 0))) {
						temp_op = operator_stack.back();
						operator_stack.pop_back();

						std::shared_ptr<ASTNode> rhs_operand;
						std::shared_ptr<ASTNode> lhs_operand;

						//Create a rel_node or expr_node based on whether temp_op is a relation or arithmetic operator
						if (isBooleanOp(temp_op) && temp_op == RelOperatorTypeEnum::ropNot) {
							lhs_operand = output_node_stack.back();
							output_node_stack.pop_back();

							//Note we must check if we are able to pop out 1 operand & the 1 operand is the type we want
							if (lhs_operand->getNodeType() != NodeTypeEnum::relationNode
								&& lhs_operand->getNodeType() != NodeTypeEnum::conditionNode) {
								throw "Error: Expected RelationNode/ConditionNode, but received another type instead.";
							}

							ConditionTypeEnum cond_type = getBooleanRelationType(temp_op);
							if (temp_op == RelOperatorTypeEnum::ropNot) {

								std::shared_ptr<ConditionNode> new_cond_node = std::make_shared<ConditionNode>();
								new_cond_node->setConditionType(cond_type);
								//Even though the operand is techincally on the right of the not operator,
								//it is placed on the left for the sake of consistency when accessing.
								new_cond_node->setLeftAstNode(lhs_operand);

								//We then place this ConditionNode into the output_node_stack
								output_node_stack.push_back(new_cond_node);
							}
						}
						else if (isArithmeticOp(temp_op)) {
							rhs_operand = output_node_stack.back();
							output_node_stack.pop_back();

							lhs_operand = output_node_stack.back();
							output_node_stack.pop_back();

							//Note we must check if we are able to pop out 2 operands & the 2 operands is the type we want
							if (rhs_operand->getNodeType() != NodeTypeEnum::expressionNode
								&& rhs_operand->getNodeType() != NodeTypeEnum::variableNode
								&& rhs_operand->getNodeType() != NodeTypeEnum::constantNode) {
								throw "Error: Expected ExpressionNode/VariableNode/ConstantNode, but received another type instead.";
							}

							if (lhs_operand->getNodeType() != NodeTypeEnum::expressionNode
								&& lhs_operand->getNodeType() != NodeTypeEnum::variableNode
								&& lhs_operand->getNodeType() != NodeTypeEnum::constantNode) {
								throw "Error: Expected ExpressionNode/VariableNode/ConstantNode, but received another type instead.";
							}

							ExpressionTypeEnum expr_type = getExpressionType(temp_op);

							std::shared_ptr<ExpressionNode> new_expr_node = std::make_shared<ExpressionNode>();
							new_expr_node->setExpressionType(expr_type);
							new_expr_node->setLeftAstNode(lhs_operand);
							new_expr_node->setRightAstNode(rhs_operand);

							//We then place this ExpressionNode into the output_node_stack
							output_node_stack.push_back(new_expr_node);
						}
						else if (isRelationOp(temp_op)) {
							RelationTypeEnum rel_type = getArithmeticRelationType(temp_op);

							rhs_operand = output_node_stack.back();
							output_node_stack.pop_back();

							lhs_operand = output_node_stack.back();
							output_node_stack.pop_back();

							//Note we must check if we are able to pop out 2 operands & the 2 operands is the type we want
							if (rhs_operand->getNodeType() != NodeTypeEnum::expressionNode
								&& rhs_operand->getNodeType() != NodeTypeEnum::variableNode
								&& rhs_operand->getNodeType() != NodeTypeEnum::constantNode) {
								throw "Error: Expected ExpressionNode/VariableNode/ConstantNode, but received another type instead.";
							}

							if (lhs_operand->getNodeType() != NodeTypeEnum::expressionNode
								&& lhs_operand->getNodeType() != NodeTypeEnum::variableNode
								&& lhs_operand->getNodeType() != NodeTypeEnum::constantNode) {
								throw "Error: Expected ExpressionNode/VariableNode/ConstantNode, but received another type instead.";
							}

							std::shared_ptr<RelationNode> new_rel_node = std::make_shared<RelationNode>();
							new_rel_node->setRelationType(rel_type);
							new_rel_node->setLeftAstNode(lhs_operand);
							new_rel_node->setRightAstNode(rhs_operand);

							//We then place this RelationNode into the output_node_stack
							output_node_stack.push_back(new_rel_node);
						}
						else if (isBooleanOp(temp_op)) {
							ConditionTypeEnum cond_type = getBooleanRelationType(temp_op);

							rhs_operand = output_node_stack.back();
							output_node_stack.pop_back();

							lhs_operand = output_node_stack.back();
							output_node_stack.pop_back();

							//Note we must check if we are able to pop out 2 operands & the 2 operands is the type we want
							if (rhs_operand->getNodeType() != NodeTypeEnum::relationNode
								&& rhs_operand->getNodeType() != NodeTypeEnum::conditionNode) {
								throw "Error: Expected RelationNode/ConditionNode, but received another type instead.";
							}

							if (lhs_operand->getNodeType() != NodeTypeEnum::relationNode
								&& lhs_operand->getNodeType() != NodeTypeEnum::conditionNode) {
								throw "Error: Expected RelationNode/ConditionNode, but received another type instead.";
							}

							if (temp_op == RelOperatorTypeEnum::ropAnd || temp_op == RelOperatorTypeEnum::ropOr) {
								std::shared_ptr<ConditionNode> new_cond_node = std::make_shared<ConditionNode>();
								new_cond_node->setConditionType(cond_type);
								new_cond_node->setLeftAstNode(lhs_operand);
								new_cond_node->setRightAstNode(rhs_operand);

								//We then place this ConditionNode into the output_node_stack
								output_node_stack.push_back(new_cond_node);
							}
							else {
								throw "Error: Undefined behaviour.";
							}
						}
						else {
							throw "Error: Undefined behaviour.";
						}
					}
					//Push operator to operator stack
					operator_stack.push_back(op);
				}
			}
		}

		//Handle remaining operators in operator_stack
		while (!operator_stack.empty()) {
			if (operator_stack.back() == RelOperatorTypeEnum::ropLparen || operator_stack.back() == RelOperatorTypeEnum::ropRparen) {
				//Presence of parenthesis indicates mismatched parenthesis as they should have all been discarded earlier.
				throw "Error: Mismatched parenthesis found.";
			}
			temp_op = operator_stack.back();
			operator_stack.pop_back();

			std::shared_ptr<ASTNode> rhs_operand;
			std::shared_ptr<ASTNode> lhs_operand;

			//Create a rel_node or expr_node based on whether temp_op is a relation or arithmetic operator
			if (isBooleanOp(temp_op) && temp_op == RelOperatorTypeEnum::ropNot) {
				lhs_operand = output_node_stack.back();
				output_node_stack.pop_back();

				//Note we must check if we are able to pop out 1 operand & the 1 operand is the type we want
				if (lhs_operand->getNodeType() != NodeTypeEnum::relationNode
					&& lhs_operand->getNodeType() != NodeTypeEnum::conditionNode) {
					throw "Error: Expected RelationNode/ConditionNode, but received another type instead.";
				}

				ConditionTypeEnum cond_type = getBooleanRelationType(temp_op);
				if (temp_op == RelOperatorTypeEnum::ropNot) {

					std::shared_ptr<ConditionNode> new_cond_node = std::make_shared<ConditionNode>();
					new_cond_node->setConditionType(cond_type);
					//Even though the operand is techincally on the right of the not operator,
					//it is placed on the left for the sake of consistency when accessing.
					new_cond_node->setLeftAstNode(lhs_operand);

					//We then place this ConditionNode into the output_node_stack
					output_node_stack.push_back(new_cond_node);
				}
			}
			else if (isArithmeticOp(temp_op)) {
				rhs_operand = output_node_stack.back();
				output_node_stack.pop_back();

				lhs_operand = output_node_stack.back();
				output_node_stack.pop_back();

				//Note we must check if we are able to pop out 2 operands & the 2 operands is the type we want
				if (rhs_operand->getNodeType() != NodeTypeEnum::expressionNode
					&& rhs_operand->getNodeType() != NodeTypeEnum::variableNode
					&& rhs_operand->getNodeType() != NodeTypeEnum::constantNode) {
					throw "Error: Expected ExpressionNode/VariableNode/ConstantNode, but received another type instead.";
				}

				if (lhs_operand->getNodeType() != NodeTypeEnum::expressionNode
					&& lhs_operand->getNodeType() != NodeTypeEnum::variableNode
					&& lhs_operand->getNodeType() != NodeTypeEnum::constantNode) {
					throw "Error: Expected ExpressionNode/VariableNode/ConstantNode, but received another type instead.";
				}

				ExpressionTypeEnum expr_type = getExpressionType(temp_op);

				std::shared_ptr<ExpressionNode> new_expr_node = std::make_shared<ExpressionNode>();
				new_expr_node->setExpressionType(expr_type);
				new_expr_node->setLeftAstNode(lhs_operand);
				new_expr_node->setRightAstNode(rhs_operand);

				//We then place this ExpressionNode into the output_node_stack
				output_node_stack.push_back(new_expr_node);
			}
			else if (isRelationOp(temp_op)) {
				RelationTypeEnum rel_type = getArithmeticRelationType(temp_op);

				rhs_operand = output_node_stack.back();
				output_node_stack.pop_back();

				lhs_operand = output_node_stack.back();
				output_node_stack.pop_back();

				//Note we must check if we are able to pop out 2 operands & the 2 operands is the type we want
				if (rhs_operand->getNodeType() != NodeTypeEnum::expressionNode
					&& rhs_operand->getNodeType() != NodeTypeEnum::variableNode
					&& rhs_operand->getNodeType() != NodeTypeEnum::constantNode) {
					throw "Error: Expected ExpressionNode/VariableNode/ConstantNode, but received another type instead.";
				}

				if (lhs_operand->getNodeType() != NodeTypeEnum::expressionNode
					&& lhs_operand->getNodeType() != NodeTypeEnum::variableNode
					&& lhs_operand->getNodeType() != NodeTypeEnum::constantNode) {
					throw "Error: Expected ExpressionNode/VariableNode/ConstantNode, but received another type instead.";
				}

				std::shared_ptr<RelationNode> new_rel_node = std::make_shared<RelationNode>();
				new_rel_node->setRelationType(rel_type);
				new_rel_node->setLeftAstNode(lhs_operand);
				new_rel_node->setRightAstNode(rhs_operand);

				//We then place this RelationNode into the output_node_stack
				output_node_stack.push_back(new_rel_node);
			}
			else if (isBooleanOp(temp_op)) {
				ConditionTypeEnum cond_type = getBooleanRelationType(temp_op);

				rhs_operand = output_node_stack.back();
				output_node_stack.pop_back();

				lhs_operand = output_node_stack.back();
				output_node_stack.pop_back();

				//Note we must check if we are able to pop out 2 operands & the 2 operands is the type we want
				if (rhs_operand->getNodeType() != NodeTypeEnum::relationNode
					&& rhs_operand->getNodeType() != NodeTypeEnum::conditionNode) {
					throw "Error: Expected RelationNode/ConditionNode, but received another type instead.";
				}

				if (lhs_operand->getNodeType() != NodeTypeEnum::relationNode
					&& lhs_operand->getNodeType() != NodeTypeEnum::conditionNode) {
					throw "Error: Expected RelationNode/ConditionNode, but received another type instead.";
				}

				if (temp_op == RelOperatorTypeEnum::ropAnd || temp_op == RelOperatorTypeEnum::ropOr) {
					std::shared_ptr<ConditionNode> new_cond_node = std::make_shared<ConditionNode>();
					new_cond_node->setConditionType(cond_type);
					new_cond_node->setLeftAstNode(lhs_operand);
					new_cond_node->setRightAstNode(rhs_operand);

					//We then place this ConditionNode into the output_node_stack
					output_node_stack.push_back(new_cond_node);
				}
				else {
					throw "Error: Undefined behaviour.";
				}
			}
			else {
				throw "Error: Undefined behaviour.";
			}
		}

		//Once ';' is reached or stmt_token_queue_ is empty we should have only 1 expression node or VarNode/ConstNode in the output stack.
		if (output_node_stack.size() != 1) {
			throw "Error: Expected 1 node left in output_node_stack after parsing all tokens.";
		}
		//Note that we must check if we need to encapsulate RelationNode to return a proper ConditionNode
		std::shared_ptr<ASTNode> last_node = output_node_stack.back();
		std::shared_ptr<ConditionNode> result;
		output_node_stack.pop_back();
		if (last_node->getNodeType() == NodeTypeEnum::variableNode
			|| last_node->getNodeType() == NodeTypeEnum::constantNode) {

			//TODO: Check if such node types are valid as condition.
			throw "Error: ConditionNode/RelationNode expected but VariableNode/ConstantNode found.";
		}
		else if (last_node->getNodeType() == NodeTypeEnum::expressionNode) {
			//TODO: Check if such node types are valid as condition.
			throw "Error: ConditionNode/RelationNode expected but ExpressionNode found.";
		}
		else if (last_node->getNodeType() == NodeTypeEnum::relationNode) {
			result = std::make_shared<ConditionNode>();
			std::static_pointer_cast<ConditionNode>(result)->setConditionType(ConditionTypeEnum::none);
			std::static_pointer_cast<ConditionNode>(result)->setLeftAstNode(last_node);
		}
		else if (last_node->getNodeType() == NodeTypeEnum::conditionNode) {
			result = std::static_pointer_cast<ConditionNode>(last_node);
		}
		else {
			throw "Error: ConditionNode/RelationNode expected, unknown node type found.";
		}

		if (this->process_token_stream_.front() != "{") {
			throw "Error: Expected \"{\" terminal but not found.";
		}
		this->process_token_stream_.pop_front(); // Pops out '{'

		//Construct new_stmt_list_node & new_procedure_node
		std::shared_ptr<StatementListNode> if_stmt_list_node = std::make_shared<StatementListNode>();
		std::shared_ptr<StatementListNode> else_stmt_list_node = std::make_shared<StatementListNode>();
		std::shared_ptr<IfNode> new_if_node = std::make_shared<IfNode>();
		new_if_node->setConditionNode(result);
		new_if_node->setThenStatementListNode(if_stmt_list_node);
		new_if_node->setElseStatementListNode(else_stmt_list_node);

		this->stmt_num_++;
		new_if_node->setStatementNumber(this->stmt_num_);
		std::static_pointer_cast<StatementListNode>(this->current_parent_node_)->addStatementNode(new_if_node);
		new_if_node->setStatementListNode(std::static_pointer_cast<StatementListNode>(this->current_parent_node_));



		//add Parent relationship if this->current_parent_node_->getParentNode() is not procedureNode
		if (this->current_parent_node_->getParentNode()->getNodeType() != NodeTypeEnum::procedureNode) {
			this->pkb_builder_.addParent(std::static_pointer_cast<StatementNode>(this->current_parent_node_->getParentNode())->getStatementNumber()
				, new_if_node->getStatementNumber());
		}

		//add Follows relationship if this statement is not the first statement of this->current_parent_node_
		if (new_if_node != std::static_pointer_cast<StatementListNode>(this->current_parent_node_)->getStatementNodeList().at(0)) {
			int this_stmt_num = new_if_node->getStatementNumber();
			STMT_LIST_NODE_PTR stmtList = std::static_pointer_cast<StatementListNode>(this->current_parent_node_);
			STMT_NODE_PTR prevStmt = std::static_pointer_cast<StatementNode>(stmtList->getChildrenNode().end()[-2]);

			this->pkb_builder_.addFollows(prevStmt->getStatementNumber()
				, new_if_node->getStatementNumber());
		}

		//add Uses Relationship for all vars
		for (STRING var_name : used_vars_set) {
			//Set Uses Relationship for this statement
			this->pkb_builder_.addUses(new_if_node->getStatementNumber()
				, var_name);

			//Set Uses Relationship for all containers of this statement by going up 2 steps until we hit ProcedureNode.
			std::shared_ptr<ASTNode> curr_container = this->current_parent_node_->getParentNode();
			STMT_NUM curr_stmtnum = 0;
			while (curr_container->getNodeType() != NodeTypeEnum::procedureNode) {
				//Get stmt number of container
				if (curr_container->getNodeType() == NodeTypeEnum::whileNode) {
					curr_stmtnum = std::static_pointer_cast<WhileNode>(curr_container)->getStatementNumber();
				}
				else if (curr_container->getNodeType() == NodeTypeEnum::ifNode) {
					curr_stmtnum = std::static_pointer_cast<IfNode>(curr_container)->getStatementNumber();
				}
				//call addUses
				this->pkb_builder_.addUses(curr_stmtnum, var_name);

				//Check if can go up 2 steps
				if (curr_container->getParentNode()->getParentNode() == NULL) {
					//Throw exception if cant
					throw "Exception in parseWhile: curr_container missing grandparent node.";
				}
				else {
					//curr_container = go up 2 steps
					curr_container = curr_container->getParentNode()->getParentNode();
				}
			}
			//call addUses for procedureNode
			if (curr_container->getNodeType() != NodeTypeEnum::procedureNode) {
				//Throw exception if cant
				throw "Exception in parseWhile: curr_container should be ProcedureNode.";
			}
			else {
				//addUses for ProcedureNode
				std::static_pointer_cast<ProcedureNode>(curr_container)->getProcedureName();
				this->pkb_builder_.addUses(std::static_pointer_cast<ProcedureNode>(curr_container)->getProcedureName()
					, var_name);
			}
		}

		//change parent tracker to stmtlistnode_ptr
		this->current_parent_node_ = if_stmt_list_node;

		//Need to add new_stmt_list_node & new_if_node to PKB tables
		this->pkb_builder_.addIfNode(new_if_node);
		this->pkb_builder_.addStatementNode(new_if_node);
		this->pkb_builder_.addStatementListNode(if_stmt_list_node);
		this->pkb_builder_.addStatementListNode(else_stmt_list_node);

		return 0;
	}

	int Parser::parseElse(STMT_TOKEN_QUEUE stmt_tok_queue, PROCESS_TOKEN_QUEUE proc_tok_queue) {
		//We assume that '{' will follow 'else'

		if (this->stmt_token_queue_.front() != "else") {
			throw "Error: Expected \"else\" terminal but not found.";
		}
		this->stmt_token_queue_.pop_front(); // Remove stmt type token

		//Check for "{"
		if (this->process_token_stream_.front() != "{") {
			throw "Error: Expected \"{\" terminal but not found.";
		}
		this->process_token_stream_.pop_front(); // Pops out '{'

		//Due to parseStmtListClose changing current_parent_node_ there is no need change parent tracker to stmtlistnode_ptr
		//This function exists just to remove the "else" & "{" tokens
		//Debugging statement
		std::cout << "\nParse else tokens\n";

		return 0;
	}

	int Parser::parseAssign(STMT_TOKEN_QUEUE stmt_tok_queue, PROCESS_TOKEN_QUEUE proc_tok_queue) {
		//We assume that this statement will terminate with ';'
		// First token is assign
		if (this->stmt_token_queue_.front() != "assign") {
			throw "Error: Expected \"assign\" terminal but not found.";
		}
		this->stmt_token_queue_.pop_front(); // Remove stmt type token

		//Second token is lhs var name 
		STRING lhs_name_token = this->stmt_token_queue_.front();
		this->stmt_token_queue_.pop_front(); // Remove varname token
		if (!isalpha(lhs_name_token.at(0)) && !isdigit(lhs_name_token.at(0))) {
			throw "Error: Expected token of NAME or INTEGER format but not found.";
		}



		//REPLACEMENT FOR THIRD TOKEN CONSUMPTION
		std::deque<std::shared_ptr<ASTNode>> output_node_stack = std::deque<std::shared_ptr<ASTNode>>();
		std::deque<OperatorTypeEnum> operator_stack = std::deque<OperatorTypeEnum>();
		OperatorTypeEnum op;
		OperatorTypeEnum temp_op;

		//===== Actual Code ======
		//Here we will keep consuming tokens until we reach ';'

		STRING rhs_token = this->process_token_stream_.front();
		this->process_token_stream_.pop_front(); // Remove rhs var/const/operator/parentheses token for the next token

		//TODO: HANDLERS FOR EMPTY STACKS / UNEXCPECTED TOKENS
		//Need to handle gracefully

		while (rhs_token != ";") {
			//These tokens will populate this->stmt_token_queue_
			this->stmt_token_queue_.push_back(rhs_token);
			rhs_token = this->process_token_stream_.front();
			this->process_token_stream_.pop_front(); // Remove rhs var/const/operator/parentheses token for the next token
		}

		//They will form the expr that is assigned to new_expr_node
		//Then they will be funneled through the shunting yard algo
		STRING temp_token = "";
		//While stmt_token_queue_ has tokens
		std::unordered_set<STRING> used_vars_set;

		while (!this->stmt_token_queue_.empty()) {
			//Get & remove first token from stmt_token_queue_
			temp_token = this->stmt_token_queue_.front();
			this->stmt_token_queue_.pop_front();

			//if isalpha(first_char) 
			if (isalpha(temp_token.at(0))) {
				//then create varnode enqueue to output_node_stack
				std::shared_ptr<VariableNode> new_var_node = std::make_shared<VariableNode>();
				new_var_node->setVariableName(temp_token);
				this->pkb_builder_.addVariableNode(new_var_node);
				//enqueue to output_stack
				output_node_stack.push_back(new_var_node);

				//add var to usedied_vars_set for Uses relationship
				used_vars_set.insert(temp_token);
			}
			else if (isdigit(temp_token.at(0))) {
				//else isdigit(first_char) then create const node
				std::shared_ptr<ConstantNode> new_const_node = std::make_shared<ConstantNode>();
				new_const_node->setValue(temp_token);
				this->pkb_builder_.addConstantNode(new_const_node);
				//enqueue to output_stack
				output_node_stack.push_back(new_const_node);
			}
			else {
				//Else means token is operator or parentheses
				//Create a Operator TypeEnum object
				if (temp_token == "+") {
					op = OperatorTypeEnum::opPlus;
				}
				else if (temp_token == "-") {
					op = OperatorTypeEnum::opMin;
				}
				else if (temp_token == "*") {
					op = OperatorTypeEnum::opMult;
				}
				else if (temp_token == "/") {
					op = OperatorTypeEnum::opDiv;
				}
				else if (temp_token == "%") {
					op = OperatorTypeEnum::opMod;
				}
				else if (temp_token == "(") {
					op = OperatorTypeEnum::opLparen;
				}
				else if (temp_token == ")") {
					op = OperatorTypeEnum::opRparen;
				}
				else {
					//If not any of the above tokens, return an error.
					throw "Error: Expected arithmetic operator terminal but not found.";
				}

				//throw into operator stack
				if (op == OperatorTypeEnum::opLparen) {
					operator_stack.push_back(op);
				}
				else if (op == OperatorTypeEnum::opRparen) {
					while (!operator_stack.empty() && operator_stack.back() != OperatorTypeEnum::opLparen) {
						//Pop operator from operator stack onto the output queue. 
						//When we want to place an operator into the output stack,we instead create a new ExpressionNode (top Node of Stack is rhs, 2nd top is lhs)
						temp_op = operator_stack.back();
						operator_stack.pop_back();

						std::shared_ptr<ASTNode> rhs_operand = output_node_stack.back();
						output_node_stack.pop_back();

						std::shared_ptr<ASTNode> lhs_operand = output_node_stack.back();
						output_node_stack.pop_back();

						//Note we must check if we are able to pop out 2 operands & the 2 operands is the type we want
						if (rhs_operand->getNodeType() != NodeTypeEnum::expressionNode
							&& rhs_operand->getNodeType() != NodeTypeEnum::variableNode
							&& rhs_operand->getNodeType() != NodeTypeEnum::constantNode) {
							throw "Error: Expected rhs operand node of type ExpressionNode, VariableNode or ConstantNode but not found.";
						}
						if (lhs_operand->getNodeType() != NodeTypeEnum::expressionNode
							&& lhs_operand->getNodeType() != NodeTypeEnum::variableNode
							&& lhs_operand->getNodeType() != NodeTypeEnum::constantNode) {
							throw "Error: Expected lhs operand node of type ExpressionNode, VariableNode or ConstantNode but not found.";
						}

						ExpressionTypeEnum expr_type = getExpressionType(temp_op);

						std::shared_ptr<ExpressionNode> new_expr_node = std::make_shared<ExpressionNode>();
						new_expr_node->setExpressionType(expr_type);
						new_expr_node->setLeftAstNode(lhs_operand);
						new_expr_node->setRightAstNode(rhs_operand);

						//We then place this ExpressionNode into the output_node_stack
						output_node_stack.push_back(new_expr_node);
					}
					// If operator_stack.empty() that means there are mismatched parentheses
					if (operator_stack.empty()) throw "Error: Mismatched parantheses";
					if (operator_stack.back() == OperatorTypeEnum::opLparen) {
						operator_stack.pop_back();
					}
				}
				else {
					while (!operator_stack.empty() && operator_stack.back() != OperatorTypeEnum::opLparen
						&& ((takesPrecedent(operator_stack.back(), op) == 1)
							|| (takesPrecedent(operator_stack.back(), op) == 0))) {
						//NOTE: Condition for takesPredence(op1, op2) == 0, i.e. same precedence also has the requirement
						// of operators being left associative, which I think all of them are for this case.
						temp_op = operator_stack.back();
						operator_stack.pop_back();

						//When we want to place an operator into the output stack, we instead create a new ExpressionNode (top Node of Stack is rhs, 2nd top is lhs)
						std::shared_ptr<ASTNode> rhs_operand = output_node_stack.back();
						output_node_stack.pop_back();

						std::shared_ptr<ASTNode> lhs_operand = output_node_stack.back();
						output_node_stack.pop_back();

						//Note we must check if we are able to pop out 2 operands & the 2 is the type we want
						if (rhs_operand->getNodeType() != NodeTypeEnum::expressionNode
							&& rhs_operand->getNodeType() != NodeTypeEnum::variableNode
							&& rhs_operand->getNodeType() != NodeTypeEnum::constantNode) {
							throw "Error: Expected rhs operand node of type ExpressionNode, VariableNode or ConstantNode but not found.";
						}
						if (lhs_operand->getNodeType() != NodeTypeEnum::expressionNode
							&& lhs_operand->getNodeType() != NodeTypeEnum::variableNode
							&& lhs_operand->getNodeType() != NodeTypeEnum::constantNode) {
							throw "Error: Expected lhs operand node of type ExpressionNode, VariableNode or ConstantNode but not found.";
						}

						ExpressionTypeEnum expr_type = getExpressionType(temp_op);

						std::shared_ptr<ExpressionNode> new_expr_node = std::make_shared<ExpressionNode>();
						new_expr_node->setExpressionType(expr_type);
						new_expr_node->setLeftAstNode(lhs_operand);
						new_expr_node->setRightAstNode(rhs_operand);

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
			if (operator_stack.back() == OperatorTypeEnum::opLparen || operator_stack.back() == OperatorTypeEnum::opRparen) {
				//Presence of parenthesis indicates mismatched parenthesis as they should have all been discarded earlier.
				throw "Error: Mismatched parentheses.";
			}
			//When we want to place an operator into the output stack,we instead create a new ExpressionNode (top Node of Stack is rhs, 2nd top is lhs)
			temp_op = operator_stack.back();
			operator_stack.pop_back();

			std::shared_ptr<ASTNode> rhs_operand = output_node_stack.back();
			output_node_stack.pop_back();

			std::shared_ptr<ASTNode> lhs_operand = output_node_stack.back();
			output_node_stack.pop_back();

			//Note we must check if we are able to pop out 2 & the 2 is the type we want
			if (rhs_operand->getNodeType() != NodeTypeEnum::expressionNode
				&& rhs_operand->getNodeType() != NodeTypeEnum::variableNode
				&& rhs_operand->getNodeType() != NodeTypeEnum::constantNode) {
				throw "Error: Expected rhs operand node of type ExpressionNode, VariableNode or ConstantNode but not found.";
			}
			if (lhs_operand->getNodeType() != NodeTypeEnum::expressionNode
				&& lhs_operand->getNodeType() != NodeTypeEnum::variableNode
				&& lhs_operand->getNodeType() != NodeTypeEnum::constantNode) {
				throw "Error: Expected lhs operand node of type ExpressionNode, VariableNode or ConstantNode but not found.";
			}

			ExpressionTypeEnum expr_type = getExpressionType(temp_op);

			std::shared_ptr<ExpressionNode> new_expr_node = std::make_shared<ExpressionNode>();
			new_expr_node->setExpressionType(expr_type);
			new_expr_node->setLeftAstNode(lhs_operand);
			new_expr_node->setRightAstNode(rhs_operand);

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
			throw "Error: Expected 1 node left in output_node_stack after parsing all tokens.";
		}
		//Note that we must check if we need to encapsulate VarNode/ConstNode to return a proper ExpressionNode
		//We then create the AssignNode similar to the code below.
		std::shared_ptr<ASTNode> last_node = output_node_stack.back();
		std::shared_ptr<ASTNode> result;
		output_node_stack.pop_back();
		if (last_node->getNodeType() == NodeTypeEnum::variableNode
			|| last_node->getNodeType() == NodeTypeEnum::constantNode) {

			result = std::make_shared<ExpressionNode>();
			std::static_pointer_cast<ExpressionNode>(result)->setExpressionType(ExpressionTypeEnum::none);
			std::static_pointer_cast<ExpressionNode>(result)->setLeftAstNode(last_node);

		}
		else {
			result = last_node;
		}

		//Finalise rhs_expr_node
		std::shared_ptr<ExpressionNode> rhs_expr_node = std::static_pointer_cast<ExpressionNode>(result);

		//Create lhs var token
		std::shared_ptr<VariableNode> new_lhs_var_node = std::make_shared<VariableNode>();
		new_lhs_var_node->setVariableName(lhs_name_token);
		this->pkb_builder_.addVariableNode(new_lhs_var_node);

		//Create AssignNode
		std::shared_ptr<AssignNode> new_assign_node = std::make_shared<AssignNode>();
		new_assign_node->setVariableNode(new_lhs_var_node);
		new_assign_node->setExpressionNode(rhs_expr_node);
		//Set AssignNode stmt_num
		this->stmt_num_++;
		new_assign_node->setStatementNumber(this->stmt_num_);

		std::static_pointer_cast<StatementListNode>(this->current_parent_node_)->addStatementNode(new_assign_node);
		new_assign_node->setStatementListNode(std::static_pointer_cast<StatementListNode>(this->current_parent_node_));

		//Need to add & new_assign_node to PKB tables
		this->pkb_builder_.addStatementNode(new_assign_node);
		this->pkb_builder_.addAssignNode(new_assign_node);

		//add Parent relationship if this->current_parent_node_->getParentNode() is not procedureNode
		if (this->current_parent_node_->getParentNode()->getNodeType() != NodeTypeEnum::procedureNode) {
			this->pkb_builder_.addParent(std::static_pointer_cast<StatementNode>(this->current_parent_node_->getParentNode())->getStatementNumber()
				, new_assign_node->getStatementNumber());
		}

		//add Follows relationship if this statement is not the first statement of this->current_parent_node_
		if (new_assign_node != std::static_pointer_cast<StatementListNode>(this->current_parent_node_)->getStatementNodeList().at(0)) {
			int this_stmt_num = new_assign_node->getStatementNumber();
			STMT_LIST_NODE_PTR stmtList = std::static_pointer_cast<StatementListNode>(this->current_parent_node_);
			STMT_NODE_PTR prevStmt = std::static_pointer_cast<StatementNode>(stmtList->getChildrenNode().end()[-2]);

			this->pkb_builder_.addFollows(prevStmt->getStatementNumber()
				, new_assign_node->getStatementNumber());
		}

		//add Modifies Relationship for this statement
		this->pkb_builder_.addModifies(new_assign_node->getStatementNumber()
			, lhs_name_token);

		//add Modifies Relationship for all containers of this statement by going up 2 steps until we hit ProcedureNode.
		std::shared_ptr<ASTNode> curr_container = this->current_parent_node_->getParentNode();
		STMT_NUM curr_stmtnum = 0;
		while (curr_container->getNodeType() != NodeTypeEnum::procedureNode) {
			//Get stmt number of container
			if (curr_container->getNodeType() == NodeTypeEnum::whileNode) {
				curr_stmtnum = std::static_pointer_cast<WhileNode>(curr_container)->getStatementNumber();
			}
			else if (curr_container->getNodeType() == NodeTypeEnum::ifNode) {
				curr_stmtnum = std::static_pointer_cast<IfNode>(curr_container)->getStatementNumber();
			}
			//call addModifies
			this->pkb_builder_.addModifies(curr_stmtnum, lhs_name_token);

			//Check if can go up 2 steps
			if (curr_container->getParentNode()->getParentNode() == NULL) {
				//Throw exception if cant
				throw "Exception in parseRead: curr_container missing grandparent node.";
			}
			else {
				//curr_container = go up 2 steps
				curr_container = curr_container->getParentNode()->getParentNode();
			}
		}

		//call addModifies for procedureNode
		if (curr_container->getNodeType() != NodeTypeEnum::procedureNode) {
			//Throw exception if cant
			throw "Exception in parseRead: curr_container should be ProcedureNode.";
		}
		else {
			//addModifies for ProcedureNode
			std::static_pointer_cast<ProcedureNode>(curr_container)->getProcedureName();
			this->pkb_builder_.addModifies(std::static_pointer_cast<ProcedureNode>(curr_container)->getProcedureName()
				, lhs_name_token);
		}

		//add Uses Relationship for all rhs vars
		for (STRING var_name : used_vars_set) {
			//Set Uses Relationship for this statement
			this->pkb_builder_.addUses(new_assign_node->getStatementNumber()
				, var_name);

			//Set Uses Relationship for all containers of this statement by going up 2 steps until we hit ProcedureNode.
			std::shared_ptr<ASTNode> curr_container = this->current_parent_node_->getParentNode();
			STMT_NUM curr_stmtnum = 0;
			while (curr_container->getNodeType() != NodeTypeEnum::procedureNode) {
				//Get stmt number of container
				if (curr_container->getNodeType() == NodeTypeEnum::whileNode) {
					curr_stmtnum = std::static_pointer_cast<WhileNode>(curr_container)->getStatementNumber();
				}
				else if (curr_container->getNodeType() == NodeTypeEnum::ifNode) {
					curr_stmtnum = std::static_pointer_cast<IfNode>(curr_container)->getStatementNumber();
				}
				//call addUses
				this->pkb_builder_.addUses(curr_stmtnum, var_name);

				//Check if can go up 2 steps
				if (curr_container->getParentNode()->getParentNode() == NULL) {
					//Throw exception if cant
					throw "Exception in parseRead: curr_container missing grandparent node.";
				}
				else {
					//curr_container = go up 2 steps
					curr_container = curr_container->getParentNode()->getParentNode();
				}
			}
			//call addUses for procedureNode
			if (curr_container->getNodeType() != NodeTypeEnum::procedureNode) {
				//Throw exception if cant
				throw "Exception in parseRead: curr_container should be ProcedureNode.";
			}
			else {
				//addUses for ProcedureNode
				std::static_pointer_cast<ProcedureNode>(curr_container)->getProcedureName();
				this->pkb_builder_.addUses(std::static_pointer_cast<ProcedureNode>(curr_container)->getProcedureName()
					, var_name);
			}
		}

		//TODO: Test for invalid assignment statement case. (Mismatch parentheses, missing operand, missing operator, no ';')
		//REPLACEMENT END
		return 0;
	}

	int Parser::parseRead(STMT_TOKEN_QUEUE stmt_tok_queue, PROCESS_TOKEN_QUEUE proc_tok_queue) {
		//We take in two tokens, expecting a NAME and a ';'
		if (this->stmt_token_queue_.front() != "read") {
			throw "Error: Expected 'read' terminal but was not found.";
		}
		this->stmt_token_queue_.pop_front(); // Remove stmt type token

		STRING name_token = this->process_token_stream_.front(); //Retrieves potential name token
		this->process_token_stream_.pop_front(); // Pops out NAME token
		if (!isalpha(name_token.at(0))) {
			throw "Error: Expected NAME token but was not found.";
		}

		if (this->process_token_stream_.front() != ";") {
			throw "Error: Expected ';' terminal but was not found.";
		}
		this->process_token_stream_.pop_front(); // Pops out ';'

		//Construct new_var_node & new_read_node
		std::shared_ptr<VariableNode> new_var_node = std::make_shared<VariableNode>();
		new_var_node->setVariableName(name_token);
		std::shared_ptr<ReadNode> new_read_node = std::make_shared<ReadNode>();
		new_read_node->setVariableNode(new_var_node);

		//Set ReadNode stmt_num
		this->stmt_num_++;
		new_read_node->setStatementNumber(this->stmt_num_);

		std::static_pointer_cast<StatementListNode>(this->current_parent_node_)->addStatementNode(new_read_node);
		new_read_node->setStatementListNode(std::static_pointer_cast<StatementListNode>(this->current_parent_node_));

		//Need to add new_var_node & new_read_node to PKB tables
		this->pkb_builder_.addStatementNode(new_read_node);
		this->pkb_builder_.addReadNode(new_read_node);
		this->pkb_builder_.addVariableNode(new_var_node);

		//add Parent relationship if this->current_parent_node_->getParentNode() is not procedureNode
		if (this->current_parent_node_->getParentNode()->getNodeType() != NodeTypeEnum::procedureNode) {
			this->pkb_builder_.addParent(std::static_pointer_cast<StatementNode>(this->current_parent_node_->getParentNode())->getStatementNumber()
				, new_read_node->getStatementNumber());
		}

		//add Follows relationship if this statement is not the first statement of this->current_parent_node_
		if (new_read_node != std::static_pointer_cast<StatementListNode>(this->current_parent_node_)->getStatementNodeList().at(0)) {
			int this_stmt_num = new_read_node->getStatementNumber();
			STMT_LIST_NODE_PTR stmtList = std::static_pointer_cast<StatementListNode>(this->current_parent_node_);
			STMT_NODE_PTR prevStmt = std::static_pointer_cast<StatementNode>(stmtList->getChildrenNode().end()[-2]);

			this->pkb_builder_.addFollows(prevStmt->getStatementNumber()
				, new_read_node->getStatementNumber());
		}

		//TODO: Set Modifies Relationship this is actually relative to constNode/varNode creation & operation on it
		//Set Modifies Relationship for this statement
		VAR_NAME var_name = new_var_node->getVariableName();
		this->pkb_builder_.addModifies(new_read_node->getStatementNumber()
			, var_name);

		//Set Modifies Relationship for all containers of this statement by going up 2 steps until we hit ProcedureNode.
		std::shared_ptr<ASTNode> curr_container = this->current_parent_node_->getParentNode();
		STMT_NUM curr_stmtnum = 0;
		while (curr_container->getNodeType() != NodeTypeEnum::procedureNode) {
			//Get stmt number of container
			if (curr_container->getNodeType() == NodeTypeEnum::whileNode) {
				curr_stmtnum = std::static_pointer_cast<WhileNode>(curr_container)->getStatementNumber();
			}
			else if (curr_container->getNodeType() == NodeTypeEnum::ifNode) {
				curr_stmtnum = std::static_pointer_cast<IfNode>(curr_container)->getStatementNumber();
			}
			//call addModifies
			this->pkb_builder_.addModifies(curr_stmtnum, var_name);

			//Check if can go up 2 steps
			if (curr_container->getParentNode()->getParentNode() == NULL) {
				//Throw exception if cant
				throw "Exception in parseRead: curr_container missing grandparent node.";
			}
			else {
				//curr_container = go up 2 steps
				curr_container = curr_container->getParentNode()->getParentNode();
			}
		}

		//call addModifies for procedureNode
		if (curr_container->getNodeType() != NodeTypeEnum::procedureNode) {
			//Throw exception if cant
			throw "Exception in parseRead: curr_container should be ProcedureNode.";
		}
		else {
			//addModifies for ProcedureNode
			std::static_pointer_cast<ProcedureNode>(curr_container)->getProcedureName();
			this->pkb_builder_.addModifies(std::static_pointer_cast<ProcedureNode>(curr_container)->getProcedureName()
				, var_name);
		}

		return 0;
	}

	int Parser::parsePrint(STMT_TOKEN_QUEUE stmt_tok_queue, PROCESS_TOKEN_QUEUE proc_tok_queue) {
		//We take in two tokens, expecting a NAME and a ';'
		if (this->stmt_token_queue_.front() != "print") {
			throw "Error: Expected 'print' terminal but was not found.";
		}
		this->stmt_token_queue_.pop_front(); // Remove stmt type token

		STRING name_token = this->process_token_stream_.front(); //Retrieves potential name token
		this->process_token_stream_.pop_front(); // Pops out NAME token
		if (!isalpha(name_token.at(0))) {
			throw "Error: Expected NAME token but was not found.";
		}

		if (this->process_token_stream_.front() != ";") {
			throw "Error: Expected ';' terminal but was not found.";
		}
		this->process_token_stream_.pop_front(); // Pops out ';'

		//Construct new_var_node & new_print_node
		std::shared_ptr<VariableNode> new_var_node = std::make_shared<VariableNode>();
		new_var_node->setVariableName(name_token);
		std::shared_ptr<PrintNode> new_print_node = std::make_shared<PrintNode>();
		new_print_node->setVariableNode(new_var_node);

		//Set PrintNode stmt_num
		this->stmt_num_++;
		new_print_node->setStatementNumber(this->stmt_num_);

		std::static_pointer_cast<StatementListNode>(this->current_parent_node_)->addStatementNode(new_print_node);
		new_print_node->setStatementListNode(std::static_pointer_cast<StatementListNode>(this->current_parent_node_));

		//Need to add new_var_node & new_print_node to PKB tables
		this->pkb_builder_.addStatementNode(new_print_node);
		this->pkb_builder_.addPrintNode(new_print_node);
		this->pkb_builder_.addVariableNode(new_var_node);

		//add Parent relationship if this->current_parent_node_->getParentNode() is not procedureNode
		if (this->current_parent_node_->getParentNode()->getNodeType() != NodeTypeEnum::procedureNode) {
			this->pkb_builder_.addParent(std::static_pointer_cast<StatementNode>(this->current_parent_node_->getParentNode())->getStatementNumber()
				, new_print_node->getStatementNumber());
		}

		//add Follows relationship if this statement is not the first statement of this->current_parent_node_
		if (new_print_node != std::static_pointer_cast<StatementListNode>(this->current_parent_node_)->getStatementNodeList().at(0)) {
			int this_stmt_num = new_print_node->getStatementNumber();
			STMT_LIST_NODE_PTR stmtList = std::static_pointer_cast<StatementListNode>(this->current_parent_node_);
			STMT_NODE_PTR prevStmt = std::static_pointer_cast<StatementNode>(stmtList->getChildrenNode().end()[-2]);

			this->pkb_builder_.addFollows(prevStmt->getStatementNumber()
				, new_print_node->getStatementNumber());
		}

		//TODO: Set Uses Relationship this is actually relative to constNode/varNode creation & operation on it
		//Set Uses Relationship for this statement
		VAR_NAME var_name = new_var_node->getVariableName();
		this->pkb_builder_.addUses(new_print_node->getStatementNumber()
			, var_name);

		//Set Uses Relationship for all containers of this statement by going up 2 steps until we hit ProcedureNode.
		std::shared_ptr<ASTNode> curr_container = this->current_parent_node_->getParentNode();
		STMT_NUM curr_stmtnum = 0;
		while (curr_container->getNodeType() != NodeTypeEnum::procedureNode) {
			//Get stmt number of container
			if (curr_container->getNodeType() == NodeTypeEnum::whileNode) {
				curr_stmtnum = std::static_pointer_cast<WhileNode>(curr_container)->getStatementNumber();
			}
			else if (curr_container->getNodeType() == NodeTypeEnum::ifNode) {
				curr_stmtnum = std::static_pointer_cast<IfNode>(curr_container)->getStatementNumber();
			}
			//call addUses
			this->pkb_builder_.addUses(curr_stmtnum, var_name);

			//Check if can go up 2 steps
			if (curr_container->getParentNode()->getParentNode() == NULL) {
				//Throw exception if cant
				throw "Exception in parseRead: curr_container missing grandparent node.";
			}
			else {
				//curr_container = go up 2 steps
				curr_container = curr_container->getParentNode()->getParentNode();
			}
		}
		//call addUses for procedureNode
		if (curr_container->getNodeType() != NodeTypeEnum::procedureNode) {
			//Throw exception if cant
			throw "Exception in parseRead: curr_container should be ProcedureNode.";
		}
		else {
			//addUses for ProcedureNode
			std::static_pointer_cast<ProcedureNode>(curr_container)->getProcedureName();
			this->pkb_builder_.addUses(std::static_pointer_cast<ProcedureNode>(curr_container)->getProcedureName()
				, var_name);
		}

		//Debugging statement
		std::cout << "\nCreated print node with var: " << new_var_node->getVariableName();

		return 0;
	}

	int Parser::parseProcedure(STMT_TOKEN_QUEUE stmt_tok_queue, PROCESS_TOKEN_QUEUE proc_tok_queue) {
		//We assume that this opening segment will either terminate with '{'
		if (this->stmt_token_queue_.front() != "procedure") {
			throw "Error: Expected 'procedure' terminal but was not found.";
		}
		this->stmt_token_queue_.pop_front(); // Remove stmt type token

		STRING name_token = this->process_token_stream_.front(); //Retrieves potential name token
		this->process_token_stream_.pop_front(); // Pops out NAME token
		if (!isalpha(name_token.at(0))) {
			throw "Error: Expected NAME token but was not found.";
		}
		
		if (this->process_token_stream_.front() != "{") {
			throw "Error: Expected '{' terminal but was not found.";
		}
		this->process_token_stream_.pop_front(); // Pops out '{'

		//Construct new_stmt_list_node & new_procedure_node
		std::shared_ptr<StatementListNode> new_stmt_list_node = std::make_shared<StatementListNode>();
		std::shared_ptr<ProcedureNode> new_procedure_node = std::make_shared<ProcedureNode>();
		new_procedure_node->setProcedureName(name_token);
		new_procedure_node->setProcedureStatementListNode(new_stmt_list_node);

		//Check that we are actually adding this new procedure to programNode
		if (this->current_parent_node_->getNodeType() != NodeTypeEnum::programNode) {
			throw "Error: Expected current_parent_node to be ProgramNode but not found.";
		}

		std::static_pointer_cast<ProgramNode>(this->current_parent_node_)->addProcedureNode(new_procedure_node);

		//change parent tracker to stmtlistnode_ptr
		this->current_parent_node_ = new_stmt_list_node;
		
		//Need to add new_stmt_list_node & new_procedure_node to PKB tables
		this->pkb_builder_.addProcedureNode(new_procedure_node);
		this->pkb_builder_.addStatementListNode(new_stmt_list_node);

		return 0;
	}

	int Parser::parseCall(STRING str) {
		//We assume that this statement will terminate with ';'
		return 0;
	}

	int Parser::parseStmtListClose() {	
		//Method 2: accounts for container statements
		
		//Part 1: When closing a stmtList Node, 
		//Checks if stmtlist size < 1, returns non-zero int as a signal that there is a problem
		if (this->current_parent_node_->getChildrenNode().size() < 1) {
			throw "Error: Expected statement list to have at least 1 statement, but 0 statements found.";
		}

		//Part 2:
		//Assuming we maintain curr_parent_node_

		//There are 2 different ways to change the curr_parent_node_ (Refer to StmtListCloseChangeParentNode image)
		if (this->current_parent_node_->getParentNode()->getNodeType() == NodeTypeEnum::ifNode){
			//cast to parent of curr_parent_node_ to IF_NODE*
			std::shared_ptr<IfNode> ifNode = std::static_pointer_cast<IfNode>(this->current_parent_node_->getParentNode());
			
				//check if its ThenStatementListNode is equal to curr_parent_node_ (after we cast curr_parent_node_ to STMT_LIST_NODE*)
			if (ifNode->getThenStatementListNode() == std::static_pointer_cast<StatementListNode>(this->current_parent_node_)) {
				//change curr_parent_node_ to point to ELSE_STMT_LIST_NODE
				//We assume that it was pre-created when we created the IF_STMT_LIST_NODE
				this->current_parent_node_ = ifNode->getElseStatementListNode();
			} else {
				//change curr_parent_node_ to point to STMT_LIST_NODE that contains the IF_NODE
				//curr_parent_node_ = curr_parent_node_.getParent().getParent()
				this->current_parent_node_ = ifNode->getParentNode();
			}
		} else {
			//change curr_parent_node_ to point to grandparent node of curr_parent_node_
			//curr_parent_node_ must be STMT_LIST_NODE
			//it's parent can be PROCEDURE_NODE, WHILE_NODE
			//therefore grandparent node can be PROGRAM_NODE or STMT_LIST_NODE
			this->current_parent_node_ = this->current_parent_node_->getParentNode()->getParentNode();

		}

		return 0;
	}

	//===== START OF HELPER FUNCTIONS =====
	int Parser::takesPrecedent(OperatorTypeEnum l_op, OperatorTypeEnum r_op) {
		//Returns 1 if left operator takes precendence
		if (l_op == OperatorTypeEnum::opMult || l_op == OperatorTypeEnum::opDiv || l_op == OperatorTypeEnum::opMod) {
			if (r_op == OperatorTypeEnum::opPlus || l_op == OperatorTypeEnum::opMin) {
				return 1;
			}
		}
		else if (l_op == OperatorTypeEnum::opPlus || l_op == OperatorTypeEnum::opMin) {
			if (r_op == OperatorTypeEnum::opMult || r_op == OperatorTypeEnum::opDiv || r_op == OperatorTypeEnum::opMod) {
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

	ExpressionTypeEnum Parser::getExpressionType(OperatorTypeEnum op) {
		if (op == OperatorTypeEnum::opPlus) {
			return ExpressionTypeEnum::plus;
		}
		else if (op == OperatorTypeEnum::opMin) {
			return ExpressionTypeEnum::min;
		}
		else if (op == OperatorTypeEnum::opMult) {
			return ExpressionTypeEnum::times;
		}
		else if (op == OperatorTypeEnum::opDiv) {
			return ExpressionTypeEnum::div;
		}
		else if (op == OperatorTypeEnum::opMod) {
			return ExpressionTypeEnum::mod;
		}
		else {
			return ExpressionTypeEnum::none;
		}
	}

	//===== END OF HELPER FUNCTIONS =====

	//===== START OF HELPER FUNCTIONS FOR RELATION NODE =====
	int Parser::takesPrecedent(RelOperatorTypeEnum l_op, RelOperatorTypeEnum r_op) {
		//Returns 1 if left operator takes precendence
		if (l_op == RelOperatorTypeEnum::ropMult || l_op == RelOperatorTypeEnum::ropDiv || l_op == RelOperatorTypeEnum::ropMod) {
			if (r_op == RelOperatorTypeEnum::ropMult || r_op == RelOperatorTypeEnum::ropDiv || r_op == RelOperatorTypeEnum::ropMod) {
				return 0;
			}
			else {
				return 1;
			}
		}
		else if (l_op == RelOperatorTypeEnum::ropPlus || l_op == RelOperatorTypeEnum::ropMin) {
			if (r_op == RelOperatorTypeEnum::ropEq || r_op == RelOperatorTypeEnum::ropNeq
				|| r_op == RelOperatorTypeEnum::ropGt || r_op == RelOperatorTypeEnum::ropGte
				|| r_op == RelOperatorTypeEnum::ropLt || r_op == RelOperatorTypeEnum::ropLte
				//Boolean comparison operator
				|| r_op == RelOperatorTypeEnum::ropNot || r_op == RelOperatorTypeEnum::ropAnd || r_op == RelOperatorTypeEnum::ropOr) {
				//1 if left operator takes precedence
				return 1;
			}
			else if (r_op == RelOperatorTypeEnum::ropMult || r_op == RelOperatorTypeEnum::ropDiv || r_op == RelOperatorTypeEnum::ropMod) {
				//-1 if right operator takes precedence
				return -1;
			}
			else {
				return 0;
			}
		}
		else if (l_op == RelOperatorTypeEnum::ropEq || l_op == RelOperatorTypeEnum::ropNeq
			|| l_op == RelOperatorTypeEnum::ropGt || l_op == RelOperatorTypeEnum::ropGte
			|| l_op == RelOperatorTypeEnum::ropLt || l_op == RelOperatorTypeEnum::ropLte) {
			if (r_op == RelOperatorTypeEnum::ropNot || r_op == RelOperatorTypeEnum::ropAnd || r_op == RelOperatorTypeEnum::ropOr) {
				//1 if left operator takes precedence
				return 1;
			}
			else if (r_op == RelOperatorTypeEnum::ropEq || r_op == RelOperatorTypeEnum::ropNeq
				|| r_op == RelOperatorTypeEnum::ropGt || r_op == RelOperatorTypeEnum::ropGte
				|| r_op == RelOperatorTypeEnum::ropLt || r_op == RelOperatorTypeEnum::ropLte) {
				return 0;
			}
			else {
				return -1;
			}
		}
		else if (l_op == RelOperatorTypeEnum::ropNot || l_op == RelOperatorTypeEnum::ropAnd || l_op == RelOperatorTypeEnum::ropOr) {
			if (r_op == RelOperatorTypeEnum::ropNot || r_op == RelOperatorTypeEnum::ropAnd || r_op == RelOperatorTypeEnum::ropOr) {
				return 0;
			}
			else {
				return -1;
			}
		}
		else {
			throw "Error undefined comparison.";
		}
	}

	ExpressionTypeEnum Parser::getExpressionType(RelOperatorTypeEnum op) {
		if (op == RelOperatorTypeEnum::ropPlus) {
			return ExpressionTypeEnum::plus;
		}
		else if (op == RelOperatorTypeEnum::ropMin) {
			return ExpressionTypeEnum::min;
		}
		else if (op == RelOperatorTypeEnum::ropMult) {
			return ExpressionTypeEnum::times;
		}
		else if (op == RelOperatorTypeEnum::ropDiv) {
			return ExpressionTypeEnum::div;
		}
		else if (op == RelOperatorTypeEnum::ropMod) {
			return ExpressionTypeEnum::mod;
		}
		else {
			return ExpressionTypeEnum::none;
		}
	}

	RelationTypeEnum Parser::getArithmeticRelationType(RelOperatorTypeEnum op) {
		if (op == RelOperatorTypeEnum::ropEq) {
			return RelationTypeEnum::eq;
		}
		else if (op == RelOperatorTypeEnum::ropNeq) {
			return RelationTypeEnum::neq;
		}
		else if (op == RelOperatorTypeEnum::ropGt) {
			return RelationTypeEnum::gt;
		}
		else if (op == RelOperatorTypeEnum::ropGte) {
			return RelationTypeEnum::gte;
		}
		else if (op == RelOperatorTypeEnum::ropLt) {
			return RelationTypeEnum::lt;
		}
		else if (op == RelOperatorTypeEnum::ropLte) {
			return RelationTypeEnum::lte;
		}
		else {
			return RelationTypeEnum::undefined;
		}
	}

	ConditionTypeEnum Parser::getBooleanRelationType(RelOperatorTypeEnum op) {
		if (op == RelOperatorTypeEnum::ropNot) {
			return ConditionTypeEnum::not;
		}
		else if (op == RelOperatorTypeEnum::ropOr) {
			return ConditionTypeEnum::or;
		}
		else if (op == RelOperatorTypeEnum::ropAnd) {
			return ConditionTypeEnum::and;
		}
		else {
			return ConditionTypeEnum::undefined;
		}
	}

	bool Parser::isArithmeticOp(RelOperatorTypeEnum op) {
		if (op == RelOperatorTypeEnum::ropPlus || op == RelOperatorTypeEnum::ropMin
			|| op == RelOperatorTypeEnum::ropMult || op == RelOperatorTypeEnum::ropDiv
			|| op == RelOperatorTypeEnum::ropMod) {
			return true;
		}
		else {
			return false;
		}
	}

	bool Parser::isRelationOp(RelOperatorTypeEnum op) {
		if (op == RelOperatorTypeEnum::ropEq || op == RelOperatorTypeEnum::ropNeq
			|| op == RelOperatorTypeEnum::ropGt || op == RelOperatorTypeEnum::ropGte
			|| op == RelOperatorTypeEnum::ropLt || op == RelOperatorTypeEnum::ropLte) {
			return true;
		}
		else {
			return false;
		}
	}

	bool Parser::isBooleanOp(RelOperatorTypeEnum op) {
		if (op == RelOperatorTypeEnum::ropBoolNone || op == RelOperatorTypeEnum::ropNot
			|| op == RelOperatorTypeEnum::ropAnd || op == RelOperatorTypeEnum::ropOr) {
			return true;
		}
		else {
			return false;
		}
	}

	//===== END OF HELPER FUNCTIONS FOR RELATION NODE =====

	//===== START OF DEBUGGER FUNCTIONS =====
	int Parser::printTree(AST_NODE_PTR parent_node_ptr) {
		std::deque< AST_NODE_PTR> node_queue = std::deque< AST_NODE_PTR>();
		node_queue.push_back(parent_node_ptr);

		while (!node_queue.empty()) {
			AST_NODE_PTR node_ptr = node_queue.front();
			node_queue.pop_front();
			NODE_TYPE node_type = node_ptr->getNodeType();
			AST_NODE_PTR_LIST children_nodes = node_ptr->getChildrenNode();

			// Get properties of current node, and print:
			std::vector<std::string> node_properties = getProperties(node_ptr, node_type);

			std::cout << "\n\n Node Type: ";
;			for (STRING properties : node_properties) {
				std::cout << properties << '\n';
			}

			// Enqueue currrent node's children nodes:
			for (AST_NODE_PTR child : children_nodes) {
				node_queue.push_back(child);
			}

			// Print number of children nodes:
			std::cout << "No. of Children: " << children_nodes.size() << '\n';
		}

		return 0;
	}

	std::vector<std::string> Parser::getProperties(AST_NODE_PTR node_ptr, NODE_TYPE node_type) {
		std::vector<std::string> node_properties;
		ExpressionTypeEnum expr = std::static_pointer_cast<ExpressionNode>(node_ptr)->getExpressionType();
		STRING expr_str = "ERROR NO EXPR";
		switch (node_type) {
		
		case NODE_TYPE::assignNode:
			node_properties.push_back("assignNode");
			break;

		case NODE_TYPE::conditionNode:
			node_properties.push_back("conditionNode");
			//node_properties.push_back(std::static_pointer_cast<ConditionNode>(node_ptr)->getConditionType());
			break;

		case NODE_TYPE::constantNode:
			node_properties.push_back("constantNode");
			node_properties.push_back(std::static_pointer_cast<ConstantNode>(node_ptr)->getValue());
			break;

		case NODE_TYPE::expressionNode:
			node_properties.push_back("expressionNode");
			
			if (expr == ExpressionTypeEnum::div) {
					expr_str = "DIVISION";
			} else if(expr == ExpressionTypeEnum::times) {
				expr_str = "MULTIPLICATION";
			} else if(expr == ExpressionTypeEnum::plus) {
				expr_str = "PLUS";
			} else if(expr == ExpressionTypeEnum::min) {
				expr_str = "MINUS";
			} else if(expr == ExpressionTypeEnum::mod) {
				expr_str = "MODULO";
			} else if(expr == ExpressionTypeEnum::none) {
				expr_str = "VAR OR CONST";
			}
			node_properties.push_back(expr_str);
			break;

		case NODE_TYPE::ifNode:
			node_properties.push_back("ifNode");
			break;

		case NODE_TYPE::printNode:
			node_properties.push_back("printNode");
			break;

		case NODE_TYPE::procedureNode:
			node_properties.push_back("procedureNode");
			node_properties.push_back(std::static_pointer_cast<ProcedureNode>(node_ptr)->getProcedureName());
			break;

		case NODE_TYPE::programNode:
			node_properties.push_back("programNode");
			break;

		case NODE_TYPE::readNode:
			node_properties.push_back("readNode");
			break;

		case NODE_TYPE::relationNode:
			node_properties.push_back("relationNode");
			//node_properties.push_back(std::static_pointer_cast<RelationNode>(node_ptr)->getRelationType());
			break;

		case NODE_TYPE::statementListNode:
			node_properties.push_back("statementListNode");
			break;

		case NODE_TYPE::variableNode:
			node_properties.push_back("variableNode");
			node_properties.push_back(std::static_pointer_cast<VariableNode>(node_ptr)->getVariableName());
			break;

		case NODE_TYPE::whileNode:
			node_properties.push_back("whileNode");
			break;

		default:
			node_properties.push_back("Error: No such node.");
		}

		return node_properties;
	}

