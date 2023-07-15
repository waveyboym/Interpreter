/**
*@file builtinNode.h builtinNode.cpp
*@class builtinNode
*@author Michael
*@brief creates a node in the syntax tree of type builtinNode
*/

#ifndef BUILTINNODE
#define BUILTINNODE
#include "../tokenNode.h"

/** 
*@brief creates a node in the syntax tree of type builtinNode
*/
class builtinNode : public tokenNode{
public:
    /** 
    *@brief assigned data for the built in function to use
    */
    std::shared_ptr<tokenNode> assigneddata = nullptr;

    /** 
    *@brief name of the built in function
    */
    std::string built_in_name = "";

    /**
    *@brief constructor
    *@param none
    */
    builtinNode();
    
    /**
    *@brief (virtual) returns a string representing the current state of this builtinNode and it's syntax tree structure
    *@param none
    *@return std::string
    */
    std::string __represent__();
};

#endif