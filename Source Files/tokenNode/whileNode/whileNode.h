/**
*@file Exceptions.h Exceptions.cpp
*@class Exceptions
*@author Michael
*@brief creates a node in the syntax tree of type while
*/

#ifndef WHILENODE_H
#define WHILENODE_H
#include "../tokenNode.h"

/** 
*@brief creates a node in the syntax tree of type while
*/
class whileNode : public tokenNode{
public:
    /**
    *@brief constructor
    *@param none
    */
    whileNode();

    /**
    *@brief (virtual) returns a string representing the current state of this whilenode and it's syntax tree structure
    *@param none
    *@return std::string
    */
    std::string __represent__();

    /** 
    *@brief is used by interpreterr to determine the conditional type whether if, for or while
    */
    const std::string conditionaltype = "while";

    /** 
    *@brief is used by interpreterr to determine the condition's data type whether it is strings or numbers
    */
    std::string datatype;

    /** 
    *@brief pointer to this while loops conditions abstract syntax tree
    */
    std::shared_ptr<tokenNode> condition = nullptr;

    /** 
    *@brief vector of this while loops statements and their datatypes to be executed
    */
    std::vector<expressionData> statementsvect;
};

#endif