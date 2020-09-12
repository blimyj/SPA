#include <iostream>
#include <queue>
#include <vector>

#include "PKB\ASTNode\ASTNode.h"
#include "ASTDebugger.h"

int printTree(AST_NODE_PTR parent_node_ptr) {
    node_queue(parent_node_ptr);

    while (node_queue.notEmpty()) {
        AST_NODE_PTR node_ptr = node_queue.dequeue();
        NODE_TYPE nodeType = getNodeType(node_ptr);
        AST_NODE_PTR_LIST children_nodes = node.getChildren();
        
        // Get properties of current node, and print:
        STRING_LIST node_properties = getProperties(node_ptr);

        for (std::string properties : node_properties) {
          std::cout << properties << ' ';
        }
        
        // Enqueue currrent node's children nodes:
        for (AST_NODE_PTR child : children_nodes) {
            node_queue.enqueue(child);
        }

        // Print number of children nodes:
        std::cout << children_nodes.size;
    }

    return 0;
}

STRING_LIST getProperties(AST_NODE_PTR node_ptr) {


}