/**
*@file Exceptions.h Exceptions.cpp
*@class Exceptions
*@author Michael
*@brief node used for creating abstract syntax tree*/

#ifndef TOKENNODE_H
#define TOKENNODE_H
#include "../Exceptions/Exceptions.h"

/** *@brief node used for creating abstract syntax tree*/
class tokenNode{
public:

    /** *@brief used for directing execution in the syntax tree*/
    std::string nodeType = "None";

    /**
    *@brief constructor
    *@param none*/
    tokenNode();

    /**
    *@brief (virtual) returns a string representing the current state of the syntax tree
    *@param none
    *@return std::string*/
    virtual std::string __represent__() = 0;
};

/** *@brief expression of current line in control flow statements (if, while, for)
 *and functions 
*/
struct expressionData{
    /** *@brief this current lines statement/expression*/
    std::shared_ptr<tokenNode> expression;

    /** *@brief determines whether the current statement is a string or int related statement*/
    std::string datatype;
};

#endif