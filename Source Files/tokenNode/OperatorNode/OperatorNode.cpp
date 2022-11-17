#include "OperatorNode.h"

OperatorNode::OperatorNode(){}

std::string OperatorNode::__represent__(){
    if(this->left != nullptr && this->right != nullptr && !this->isUnaryOperator){
        return "( " + this->left->__represent__() + " " + this->op_token + " " + this->right->__represent__() + " )";
    }
    else if(this->unaryopdata != nullptr && this->isUnaryOperator){
        return "( " + this->unary_op_token +  " ( " + this->unaryopdata->__represent__() + " ) )";
    }
    else return this->nodeType;
}