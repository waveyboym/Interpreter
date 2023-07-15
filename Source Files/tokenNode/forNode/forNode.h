/**
*@file forNode.h forNode.cpp
*@class forNode
*@author Michael
*@brief creates a node in the syntax tree of type forNode
*/

#ifndef FORNODE_H
#define FORNODE_H
#include "../tokenNode.h"

/** 
*@brief creates a node in the syntax tree of type forNode
*/
class forNode : public tokenNode{
public:
    /**
    *@brief constructor
    *@param none
    */
    forNode();

    /**
    *@brief (virtual) returns a string representing the current state of this forNode and it's syntax tree structure
    *@param none
    *@return std::string
    */
    std::string __represent__();

    /** 
    *@brief conditional type whether word or number types
    */
    std::string conditionaltype = "";

    /** 
    *@brief data type whether word or number types
    */
    std::string datatype = "";

    /** 
    *@brief condition of this forNode
    */
    std::shared_ptr<tokenNode> condition = nullptr;

    /** 
    *@brief for creating or uses an existing variable as a start point
    */
    std::shared_ptr<tokenNode> declaration = nullptr;

    /** 
    *@brief preserves the state of initial declaration to reset for loop
    */
    std::shared_ptr<tokenNode> init_declaration = nullptr;

    /** 
    *@brief used to keep track of whether or not an initial declaration variable already existed beforehand
    */
    bool decl_Var_Exists = false;

    /** 
    *@brief value to change the existing variable by
    */
    std::shared_ptr<tokenNode> iteration = nullptr;

    /** 
    *@brief the statements vector this if node code block to execute if the condition is deemed true
    */
    std::vector<expressionData> statementsvect;
};

#endif