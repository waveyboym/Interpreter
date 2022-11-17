/**
*@file OperatorNode.h OperatorNode.cpp
*@class OperatorNode
*@author Michael
*@brief creates a node in the syntax tree of type operator*/

#ifndef OPERATORNODE_H
#define OPERATORNODE_H
#include "../tokenNode.h"

/** *@brief creates a node in the syntax tree of type operator*/
class OperatorNode : public tokenNode{
public:
    /** *@brief left node in syntax tree*/
    std::shared_ptr<tokenNode> left = nullptr;
    /** *@brief right node in syntax tree*/
    std::shared_ptr<tokenNode> right = nullptr;
    /** *@brief pointer to unary operator eg: -5*/
    std::shared_ptr<tokenNode> unaryopdata = nullptr;
    /** *@brief operator symbol/token*/
    std::string op_token = "";
    /** *@brief use to verify if this node has a unary operator eg -5 or not like 5*/
    bool isUnaryOperator = false;
    /** *@brief unary operator symbol/token*/
    std::string unary_op_token = "";
    /**
    *@brief constructor
    *@param none*/
    OperatorNode();

    /**
    *@brief (virtual) returns a string representing the current state of this whilenode and it's syntax tree structure
    *@param none
    *@return std::string*/
    std::string __represent__();
};

#endif