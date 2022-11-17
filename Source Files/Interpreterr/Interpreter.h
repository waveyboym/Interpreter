/**
*@file Interpreter.h Interpreter.cpp
*@class Interpreter
*@author Michael
*@brief Interprets and executes code from the abstract syntax tree*/

#ifndef INTERPRETER_H
#define INTERPRETER_H
#include "../tokens/tokens.h"
#include "../tokenNode/tokenNode.h"
#include "../tokenNode/NumberNode/NumberNode.h"
#include "../tokenNode/OperatorNode/OperatorNode.h"
#include "../tokenNode/StringNode/StringNode.h"
#include "../tokenNode/VariableNode/VariableNode.h"
#include "../tokenNode/builtinNode/builtinNode.h"
#include "../tokenNode/ifNode/ifNode.h"
#include "../tokenNode/whileNode/whileNode.h"
#include "../tokenNode/forNode/forNode.h"

enum DATATYPES{
    
};

/** *@brief returns a struct containing number values from calculations*/
struct returnNumberValues{
    bool isbooleanstatement = false;
    bool result = false;
    double value = 0.0;
};

/** *@brief returns a struct containing string values from calculations*/
struct returnStringValues{
    bool isbooleanstatement = false;
    bool result = false;
    std::string value = "";
};

/** *@brief specifies the type of the return value and carries the return value*/
struct returnValues{
    bool isbooleanval = false;
    bool booleanval = false;
    bool isnumberval = false;
    bool iswordval = false;
    double numberval = 0.0;
    std::string wordval = "";
};

/** *@brief Interprets and executes code from the abstract syntax tree*/
class Interpreter{
public:
    /**
    *@brief Interpreter constructor
    *@param filepath name of the file currently being processed
    *@param linenumber the line number in the file which is currently being processed*/
    Interpreter(const std::string& filepath, const int& linenumber);
    
    /**
    *@brief runs the interpreter
    *@param TKNode a pointer to the beginning of a root node on the syntax tree
    *@param datatype datatype of the condition(in control flow) or values in variables or values in built in function etc
    *@return void*/
    void run__CODE(std::shared_ptr<tokenNode>& TKNode, const std::string& datatype);

private:
    /** *@brief name of the file currently being processed*/
    std::string filePath;
    /** *@brief the line number in the file which is currently being processed*/
    int lnNum;

    /** *@brief specifies whether or not what is currently being processed is a loop or not*/
    bool isInLoop;

    /**
    *@brief visits control flow on the syntax tree
    *@param TKNode a pointer to the beginning of a control flow( eg, for-loop, while-loop, if,else if, else) on the syntax tree
    *@param datatype datatype of the condition in the control flow
    *@return void*/
    void visit_controlflow(std::shared_ptr<tokenNode>& TKNode, const std::string& datatype);

    /**
    *@brief visits built in function
    *@param TKNode a pointer to the beginning of the built in function on the syntax tree
    *@param datatype datatype of the value passed onto the built in function
    *@return void*/
    void visit_built_in_func(std::shared_ptr<tokenNode>& TKNode, const std::string& datatype);

    /**
    *@brief checks if the condition of a control flow is true from visit_controlflow() on for-loop, while-loop, if,else if statements
    *@param TKNode a pointer to the condition being checked
    *@param datatype datatype of the condition being checked whether word or number
    *@return bool*/
    bool checkCondition(std::shared_ptr<tokenNode>& TKNode, const std::string& datatype);

    /**
    *@brief visits variable nodes and extracts their values
    *@param TKNode a pointer to the variable node in the syntax tree
    *@param datatype datatype of the variable
    *@return void*/
    void visit_Variables(std::shared_ptr<tokenNode>& TKNode, const std::string& datatype);

    /**
    *@brief attempts to figure out if the passed in argument is a StringNode, OperatorNode or VariableNode 
    *@param TKNode a pointer to a node in the syntax tree
    *@return returnStringValues*/
    returnStringValues visitWORDS(std::shared_ptr<tokenNode>& TKNode);

    /**
    *@brief visits a string and extracts it's value eg "value"
    *@param TKNode a pointer to a string value
    *@return std::string*/
    std::string visit__StringNode(std::shared_ptr<StringNode>& TKNode);

    /**
    *@brief appends a value to the end of a variable
    *@param nodeToAppendTo variable node to append passedvalue to
    *@param passedvalue string value to append
    *@return std::string*/
    std::string visit__StringAppendNode(std::shared_ptr<VariableNode>& nodeToAppendTo, const std::string& passedvalue);

    /**
    *@brief attempts to figure out if the passed in argument is a NumberNode, OperatorNode or VariableNode 
    *@param TKNode a pointer to a node in the syntax tree
    *@return returnNumberValues*/
    returnNumberValues visitNUMBERS(std::shared_ptr<tokenNode>& TKNode);

    /**
    *@brief extracts the number value from this node which is of type unary, eg -5 or +5
    *@param TKNode a pointer to a number type node
    *@return double*/
    double visit__unaryNumberNode(std::shared_ptr<NumberNode>& TKNode);

    /**
    *@brief visits a number node contained within an expression such as and multiplies it by it's unary, eg -(5 + 5)
    *@param TKNode a pointer to a number type node
    *@return double*/
    double visit__unaryNumberNodeExpr(std::shared_ptr<NumberNode>& TKNode);

    /**
    *@brief extracts the number value from this node , eg 5
    *@param TKNode a pointer to a number type node
    *@return double*/
    double visit__NumberNode(std::shared_ptr<NumberNode>& TKNode);

    /**
    *@brief appends/adds or any other operator,  a value to the end of a variable
    *@param nodeToAppendTo variable node to append/add or any other operator passedvalue to
    *@param passedvalue number value to append
    *@return double*/
    double visit__NumberAppendNode(std::shared_ptr<VariableNode>& nodeToAppendTo, const double& passedvalue);

    /**
    *@brief attempts to figure out which operator is being used between two number nodes
    *@param TKNode a pointer to an operator type node
    *@return returnNumberValues*/
    returnNumberValues visit__numberOPNODE(std::shared_ptr<OperatorNode>& TKNode);

    /**
    *@brief attempts to figure out which operator is being used between two word nodes
    *@param TKNode a pointer to an operator type node
    *@return returnStringValues*/
    returnStringValues visit__stringOPNODE(std::shared_ptr<OperatorNode>& TKNode);

    /**
    *@brief reset a variable in a for loop back to it's original value after the for loop has finished executing
    *@param TKNode a pointer to an ifnode type node
    *@return void*/
    void resetVariableValue(std::shared_ptr<forNode>& forobj);
};

#endif