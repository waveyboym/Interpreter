/**
*@file NumberNode.h NumberNode.cpp
*@class NumberNode
*@author Michael
*@brief creates a node in the syntax tree of type NumberNode
*/

#ifndef NUMBERNODE_H
#define NUMBERNODE_H
#include "../tokenNode.h"

/** 
*@brief creates a node in the syntax tree of type NumberNode
*/
class NumberNode : public tokenNode{
public:
    /** 
    *@brief is used for testing if this node is a unary operator node eg: -5
    */
    bool isUnaryOperator = false;

    /** 
    *@brief symbol of the unary operator
    */
    std::string unary_op_token = "";

    /** 
    *@brief pointer to the unary operator data eg the 5 in -(5)
    */
    std::shared_ptr<tokenNode> unaryopdata = nullptr;

    /** 
    *@brief holds the value(int or double) of this node
    */
    double value = 0.0;

    /**
    *@brief constructor
    *@param none
    */
    NumberNode();

    /**
    *@brief (virtual) returns a string representing the current state of this NumberNode and it's syntax tree structure
    *@param none
    *@return std::string
    */
    std::string __represent__();
};

#endif