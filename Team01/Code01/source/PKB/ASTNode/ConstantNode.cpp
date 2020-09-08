#include "ConstantNode.h"

ConstantNode::ConstantNode(VALUE value) {
    setValue(value);
}

BOOLEAN ConstantNode::setValue(VALUE value) {
    try {
        value_ = value;
    }
    catch (int e) {
        return false;
    }
    return true;
}

VALUE ConstantNode::getValue() {
    return value_;
}
