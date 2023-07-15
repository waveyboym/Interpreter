/**
*@file functionNode.h functionNode.cpp
*@class functionNode
*@author Michael
*@brief creates a node in the syntax tree of type functionNode
*/

#ifndef FUNCTIONNODE_H
#define FUNCTIONNODE_H
#include "../tokenNode.h"


/** 
*@brief creates a node in the syntax tree of type functionNode
*/
class functionNode : public tokenNode{
public:
    const int FUNC_ARG_MAX = 5;
    functionNode();
    std::string __represent__();
    std::string functionName = "";
    int functionArgsAmounts = 0;
    std::vector<expressionData> arguments;
    std::vector<expressionData> statementsvect;

    void attachArgAt(int& index, std::shared_ptr<tokenNode> value);

    static std::vector<std::shared_ptr<functionNode>> stackFUNCvector;
    static void pushIntoFuncVector(std::shared_ptr<functionNode> token);
    static bool alreadyExistingFunction(const std::string& toCheck);
    static std::shared_ptr<functionNode> getThisFunction(const std::string& funcname);
};

#endif