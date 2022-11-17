/**
*@file VariableNode.h VariableNode.cpp
*@class VariableNode
*@author Michael
*@brief creates a node in the syntax tree of type variable*/

#ifndef VARIABLENODE_H
#define VARIABLENODE_H
#include "../tokenNode.h"

/** *@brief creates a node in the syntax tree of type variable*/
class VariableNode : public tokenNode{
public:
    /** *@brief pointer to this variables assigned data*/
    std::shared_ptr<tokenNode> assignedData = nullptr;
    
    /** *@brief the value to add to this variable's assigned data*/
    std::shared_ptr<tokenNode> appendData = nullptr;
    
    /** *@brief append type of append data eg, '+=', '-=', '*=' etc*/
    std::string appendType = "null";
    
    /** *@brief the name of the variable*/
    std::string varName = "";

    /**
    *@brief constructor
    *@param none*/
    VariableNode();

    /**
    *@brief (virtual) returns a string representing the current state of this whilenode and it's syntax tree structure
    *@param none
    *@return std::string*/
    std::string __represent__();

    //static variables
    /** *@brief stack vector of all number variables*/
    static std::vector<std::shared_ptr<VariableNode>> stackNUMBERvector;
    /** *@brief stack vector of all word variables*/
    static std::vector<std::shared_ptr<VariableNode>> stackWORDvector;

    //static functions
    /**
    *@brief pushes a new variable onto the stack depending on the stack to put it in
    *@param token the variable to pushed onto the stack
    *@param stacktype the stack to push it onto, whether number of word stack
    *@return void*/
    static void pushIntoVector(std::shared_ptr<VariableNode> token, const std::string& stacktype);
    
    /**
    *@brief checks if the variable name in toCheck is an exisitng variable
    *@param toCheck variable name
    *@param stacktype the stack to push it onto, whether number of word stack
    *@return bool*/
    static bool alreadyExistingVariable(const std::string& toCheck, const std::string& stacktype);
    
    /**
    *@brief returns a pointer to the variable with the name of the variablename in the correct stacktype whether it be the 'number' or 'word' stack
    *@param variablename variable name
    *@param stacktype the stack to push it onto, whether number of word stack
    *@return std::shared_ptr<VariableNode>*/
    static std::shared_ptr<VariableNode> getThisVariableobject(const std::string& variablename, const std::string& stacktype);
    
    /**
    *@brief reassigns new data to a variable in the stack
    *@param token variable
    *@param variablename variable name
    *@param stacktype the stack to push it onto, whether number of word stack
    *@param appendtype append type of append data eg, '+=', '-=', '*=' etc
    *@return bool*/
    static bool reassignExistingVariable(std::shared_ptr<tokenNode> token, const std::string& variablename, const std::string& stacktype, const std::string& appendtype);

};

#endif