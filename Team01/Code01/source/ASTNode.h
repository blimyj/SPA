#pragma once

class ASTNode {
/* Overview: The node */

public:
    /*==== Constructor ====*/
    ASTNode(NODE_TYPE type);

    /*==== Setters ====*/
    VOID appendChild(AST_NODE node);
        /*
        Description: Appends a AST_NODE as a child node of this node.
        */

    VOID setAttribute(ATTRIBUTE_NAME name, ATTRIBUTE_VALUE value);
        /*
        Description: Sets a ATTRIBUTE_VALUE to a given ATTRIBUTE_NAME of this node.
        */

    /*==== Getters ====*/
    NODE_TYPE getType();
        /*
        Description: Returns the NODE_TYPE of this node.
        */

    AST_NODE_LIST getChildren();
        /*
        Description: Returns a AST_NODE_LIST of the children of this node.
        */

    AST_NODE getParent();
        /*
        Description: Returns the parent AST_NODE of this node.
        */

    ATTRIBUTE_VALUE getAttributeValue(ATTRIBUTE_NAME name);
        /*
        Description: Returns the ATTRIBUTE_VALUE that is attached to the ATTRIBUTE_NAME.
        */
};
