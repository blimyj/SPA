#include <iostream>
#include <queue>
#include <vector>

#include "ASTDebugger.h"
#include "PKB/ASTNode/AssignNode.h"
#include "PKB/ASTNode/ConditionNode.h"
#include "PKB/ASTNode/ConstantNode.h"
#include "PKB/ASTNode/ExpressionNode.h"
#include "PKB/ASTNode/IfNode.h"
#include "PKB/ASTNode/PrintNode.h"
#include "PKB/ASTNode/ProcedureNode.h"
#include "PKB/ASTNode/ProgramNode.h"
#include "PKB/ASTNode/ReadNode.h"
#include "PKB/ASTNode/RelationNode.h"
#include "PKB/ASTNode/StatementListNode.h"
#include "PKB/ASTNode/StatementNode.h"
#include "PKB/ASTNode/VariableNode.h"
#include "PKB/ASTNode/WhileNode.h"

int printTree(AST_NODE_PTR parent_node_ptr) {
    node_queue(parent_node_ptr);

    while (node_queue.notEmpty()) {
        AST_NODE_PTR node_ptr = node_queue.dequeue();
        NODE_TYPE node_type = getNodeType(node_ptr);
        AST_NODE_PTR_LIST children_nodes = node.getChildren();

        // Get properties of current node, and print:
        STRING_LIST node_properties = getProperties(node_ptr, node_type);
        
        for (STRING properties : node_properties) {
            std::cout << properties << '\n';
        }
        
        // Enqueue currrent node's children nodes:
        for (AST_NODE_PTR child : children_nodes) {
            node_queue.enqueue(child);
        }

        // Print number of children nodes:
        std::cout << children_nodes.size << '\n';
    }

    return 0;
}

STRING_LIST getProperties(AST_NODE_PTR node_ptr, NODE_TYPE node_type, STRINGLIST node_properties) {
    switch (node_type) {

        case NODE_TYPE::assignNode:
            node_properties.insert("assignNode");
            break;

        case NODE_TYPE::conditionNode:
            node_properties.insert("conditionNode");
            node_properties.insert(node_ptr.getConditionType());
            break;

        case NODE_TYPE::constantNode:
            node_properties.insert("constantNode");
            node_properties.insert(node_ptr.getValue());
            break;

        case NODE_TYPE::expressionNode:
            node_properties.insert("expressionNode");
            node_properties.insert(node_ptr.getExpression());
            break;

        case NODE_TYPE::ifNode:
            node_properties.insert("ifNode");
            break;

        case NODE_TYPE::printNode:
            node_properties.insert("printNode");
            break;

        case NODE_TYPE::procedureNode:
            node_properties.insert("procedureNode");
            node_properties.insert(node_ptr.getProcedureName());
            break;

        case NODE_TYPE::programNode:
            node_properties.insert("programNode");
            break;

        case NODE_TYPE::readNode:
            node_properties.insert("readNode");
            break;

        case NODE_TYPE::relationNode:
            node_properties.insert("relationNode");
            node_properties.insert(node_ptr.getRelationType());
            break;

        case NODE_TYPE::statementListNode:
            node_properties.insert("statementListNode");
            break;

        case NODE_TYPE::statementNode:
            node_properties.insert("statementNode");
            node_properties.insert(node_ptr.getStatementNumber());
            break;

        case NODE_TYPE::variableNode:
            node_properties.insert("variableNode");
            node_properties.insert(node_ptr.getVariableName());
            break;

        case NODE_TYPE::whileNode:
            node_properties.insert("whileNode");
            break;

        default:
            node_properties.insert("Error: No such node.");
    }

    return node_properties;
    }
}