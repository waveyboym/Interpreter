/**
*@file parser.h parser.cpp
*@class parser
*@author Michael
*@brief parses the current line of code after receiving from the lexer
*/
#ifndef PARSER_h
#define PARSER_H
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
#include "../tokenNode/functionNode/functionNode.h"

/** 
*@brief mapping of different data types
*/
enum STATEMENT_DATATYPE{
    NUMBER_DT,
    WORD_DT,
    NULL_STATEMENT_DATATYPE,
    STATEMENT_DATATYPE_SIZE
};

/** 
*@brief parses the current line of code after receiving from the lexer
*/
class parser{
public:

    /**
    *@brief accepts a vector of tokens after the current line has been tokenized by the lexer
    *@param vect a vector of tokens
    *@param filepath name of the file currently being processed
    *@param linenumber the line number in the file which is currently being processed
    */
    parser(const std::vector<token>& vect, const std::string& filepath, const int& linenumber);

    /**
    *@brief begins parsing the tokenized vector
    *@param none
    *@return std::shared_ptr<tokenNode>
    */
    std::shared_ptr<tokenNode> __BEGIN__PARSE();

    /**
    *@brief returns a string representation of the current lines data type, whether word or number(to prevent collisions and mixing)
    *@param none
    *@return std::string
    */
    std::string getdatatype();

private:
    /** 
    *@brief stores the various supported tokens such as +, - etc
    */
    const static std::array<std::string, STATEMENT_DATATYPE::STATEMENT_DATATYPE_SIZE> datatypeARR;

    /** 
    *@brief a string representation of the default data type
    */
    const static std::string default_DT;

    /** 
    *@brief a string representation of the current lines data type, whether word or number(to prevent collisions and mixing)
    */
    std::string datatype;

    /** 
    *@brief a vector of tokens to process
    */
    std::vector<token> tokensVect;

    /** 
    *@brief current index in the tokensVect vector
    */
    int current_index;

    /** 
    *@brief current token taken from the tokensVect vector using current_index
    */
    token currentToken;

    /** 
    *@brief name of the file currently being processed
    */
    std::string filePath;

    /** 
    *@brief used for assigning data types to code blocks
    */
    std::string dataType;

    /** 
    *@brief used to keep track of the variable being processed to prevent collisions
    */
    std::string current_var_name;

    /** 
    *@brief used to keep track of whether or not a variable is being reassigned
    */
    bool isReassigningVariable;

    /** 
    *@brief used to keep track of whether or not function arguments are being attached
    */
    bool isAttaching__FuncArg;

    /** 
    *@brief the line number in the file which is currently being processed
    */
    int lnNum;

    /**
    *@brief advances current_index by one in the tokensVect
    *@param none
    *@return void
    */
    void advance();

    /**
    *@brief generates a tree for functions
    *@param none
    *@return std::shared_ptr<tokenNode>
    */
    std::shared_ptr<tokenNode> functions();

    /**
    *@brief generates a tree for control flow such as if, for and while statements
    *@param none
    *@return std::shared_ptr<tokenNode>
    */
    std::shared_ptr<tokenNode> controlflow();

    /**
    *@brief generates a tree for variables
    *@param none
    *@return std::shared_ptr<tokenNode>
    */
    std::shared_ptr<tokenNode> variables();

    /**
    *@brief generates a tree for the OR logical operator
    *@param none
    *@return std::shared_ptr<tokenNode>
    */
    std::shared_ptr<tokenNode> OR_logical_operator_expression();

    /**
    *@brief generates a tree for the AND logical operator
    *@param none
    *@return std::shared_ptr<tokenNode>
    */
    std::shared_ptr<tokenNode> AND_logical_operator_expression();

    /**
    *@brief generates a tree for relations operators such as ==, >, >=, <, <=, !=
    *@param none
    *@return std::shared_ptr<tokenNode>
    */
    std::shared_ptr<tokenNode> relational_operator_expression();

    /**
    *@brief generates a tree for expressions for numbers such as +, -
    *@param none
    *@return std::shared_ptr<tokenNode>
    */
    std::shared_ptr<tokenNode> expression();

    /**
    *@brief generates a tree for expressions for numbers such as *, /, ^, %
    *@param none
    *@return std::shared_ptr<tokenNode>
    */
    std::shared_ptr<tokenNode> term();

    /**
    *@brief generates a a basic node for either a word type or a number type
    *@param none
    *@return std::shared_ptr<tokenNode>
    */
    std::shared_ptr<tokenNode> factor();

    //helper functions

    /**
    *@brief creates a unary for a factor eg: -(<factor>) or +(<factor>)
    *@param numbernode factor to attach unary to (may be null if operatornode is not null) eg -(5)
    *@param operatornode expression to attach unary to (may be null if numbernode is not null) eg -(5 + 3)
    *@param operationtype unary type whether - or +
    *@param nodetype node type of the unary whether it is an expression or factor
    *@return std::shared_ptr<tokenNode>
    */
    std::shared_ptr<tokenNode> getCorrectUnaryType(std::shared_ptr<NumberNode>& numbernode, const std::shared_ptr<OperatorNode>& operatornode, const std::string& operationtype, const std::string& nodetype);
    
    /**
    *@brief determines append type between -=, +=, /=, ^=, %= depending on the enum mapping using the passed in argument tokentypenode
    *@param tokentypenode used to map into enum of node types to determine append type
    *@return std::string
    */
    std::string determineAppendType(const int& tokentypenode);

    /**
    *@brief a continuation of the createVariable() function
    *@param none
    *@return std::string
    */
    std::string continueReadingData();

    /**
    *@brief creates a number variable
    *@param none
    *@return std::shared_ptr<tokenNode>
    */
    std::shared_ptr<tokenNode> getNUMBERVARIABLE();

    /**
    *@brief creates a word variable
    *@param none
    *@return std::shared_ptr<tokenNode>
    */
    std::shared_ptr<tokenNode> getWORDVARIABLE();

    /**
    *@brief beings creation of a variable and pushes variable onto the stack after creating it
    *@param var_DT data type of variable whether word or number
    *@return std::shared_ptr<tokenNode>
    */
    std::shared_ptr<tokenNode> createVariable(const std::string& var_DT);

    /**
    *@brief a continuation of the createVariable() function
    *@param none
    *@return std::shared_ptr<tokenNode>
    */
    std::shared_ptr<tokenNode> getPRINTDATA();

    //control flow

    /**
    *@brief starts creating if, else if and else statements
    *@param none
    *@return std::shared_ptr<tokenNode>
    */
    std::shared_ptr<tokenNode> createifstatements();

    /**
    *@brief creates an if statement
    *@param none
    *@return std::shared_ptr<tokenNode>
    */
    std::shared_ptr<tokenNode> create__ifstatement();

    /**
    *@brief creates else if statements
    *@param none
    *@return std::shared_ptr<tokenNode>
    */
    std::shared_ptr<tokenNode> create__elseifstatements();

    /**
    *@brief creates an else statement
    *@param none
    *@return std::shared_ptr<ifNode>
    */
    std::shared_ptr<ifNode> create__elsestatements();

    /**
    *@brief creates a while statement
    *@param none
    *@return std::shared_ptr<tokenNode>
    */
    std::shared_ptr<tokenNode> create_whilestatements();

    /**
    *@brief creates a for loop statement
    *@param none
    *@return std::shared_ptr<tokenNode>
    */
    std::shared_ptr<tokenNode> create__forloops();

    //functions

    /**
    *@brief creates a function
    *@param none
    *@return std::shared_ptr<tokenNode>
    */
    std::shared_ptr<tokenNode> create__functions();

    /**
    *@brief attaches function arguments to a function after a function call is made
    *@param none
    *@return std::shared_ptr<tokenNode>
    */
    std::shared_ptr<tokenNode> attachFunctionArguments();

    /**
    *@brief creates a null variable, with no data attached to it
    *@param variabletype the data type of the null variable
    *@return std::shared_ptr<tokenNode>
    */
    std::shared_ptr<tokenNode> create_nullVariable(const std::string& variabletype);

    /**
    *@brief extracts a number node from a variable node
    *@param variablenode_data the node to extract a number from
    *@return std::shared_ptr<tokenNode>
    */
    std::shared_ptr<tokenNode> getNumberNode(std::shared_ptr<tokenNode>& variablenode_data);
};

#endif