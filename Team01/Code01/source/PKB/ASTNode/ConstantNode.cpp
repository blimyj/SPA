#include "ConstantNode.h"

ConstantNode::ConstantNode(VALUE value) {
    setValue(value);
    node_type_ = { NODE_TYPE_ENUM::Constant };
}

BOOLEAN ConstantNode::setValue(VALUE value) {
    try {
        value_ = value;
    }
    catch (int e) {
        (void)e;
        return false;
    }
    return true;
}

VALUE ConstantNode::getValue() {
    return value_;
}
