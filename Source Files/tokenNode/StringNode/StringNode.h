/**
*@file StringNode.h StringNode.cpp
*@class StringNode
*@author Michael
*@brief creates a node in the syntax tree of type string
*/

#ifndef STRINGNODE_H
#define STRINGNODE_H
#include "../tokenNode.h"

/** 
*@brief creates a node in the syntax tree of type string
*/
class StringNode : public tokenNode{
public:
    /** 
    *@brief the value of this string node
    */
    std::string stringValue = "";
    
    /** 
    *@brief constructor
    *@param none
    */
    StringNode();

    /**
    *@brief (virtual) returns a string representing the current state of this whilenode and it's syntax tree structure
    *@param none
    *@return std::string
    */
    std::string __represent__();
};

#endif