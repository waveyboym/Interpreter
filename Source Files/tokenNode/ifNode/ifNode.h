/**
*@file ifNode.h ifNode.cpp
*@class ifNode
*@author Michael
*@brief creates a node in the syntax tree of type ifNode
*/

#ifndef IFNODE_H
#define IFNODE_H
#include "../tokenNode.h"

/** 
*@brief creates a node in the syntax tree of type ifNode
*/
class ifNode : public tokenNode{
public:
    /**
    *@brief constructor
    *@param none
    */
    ifNode();

    /**
    *@brief (virtual) returns a string representing the current state of this ifNode and it's syntax tree structure
    *@param none
    *@return std::string
    */
    std::string __represent__();

    /**
    *@brief appends an ifnode to the end of this ifnodes linked list of ifnodes
    *@param token the ifNode to append to the end of the linked list
    *@return void
    */
    void appendNew__If__ElseIf__Else__statement(const std::shared_ptr<ifNode>& token);

    /** 
    *@brief conditional type whether word or number types
    */
    std::string conditionaltype = "";

    /** 
    *@brief data type whether word or number types
    */
    std::string datatype;

    /** 
    *@brief condition of this ifNode (only for if and elseif, excluding else)
    */
    std::shared_ptr<tokenNode> condition = nullptr;

    /** 
    *@brief pointer to next elseif or else statement (doesn't apply to else statemments)
    */
    std::shared_ptr<tokenNode> next__If__ElseIf__Else = nullptr;

    /** 
    *@brief the statements vector this if node code block to execute if the condition is deemed true
    */
    std::vector<expressionData> statementsvect;
};

#endif