#include "NumberNode.h"

NumberNode::NumberNode(){}

std::string NumberNode::__represent__(){
    if(this->isUnaryOperator && this->unaryopdata == nullptr){ //representing numbers like -5 or +5
        return "( " + this->unary_op_token + " ( " + std::to_string(this->value) + " ))";
    }
    else if(this->isUnaryOperator && this->unaryopdata != nullptr){//representing -(5 + 5)
        return "( " + this->unary_op_token + " ( " + this->unaryopdata->__represent__() + " ))";
    }
    else if(!this->isUnaryOperator && this->unaryopdata == nullptr){ //representing numbers like 5 or 10
        return std::to_string(this->value);
    }
    else return this->nodeType;
}