/**
*@file Exceptions.h Exceptions.cpp
*@class Exceptions
*@author Michael
*@brief creates exception objects with a message for the object to display when thrown*/

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include <string>
#include <vector>//storing functions and variables
#include <memory>//pointers in syntax tree
#include <math.h>//for complex math operations
#include <iostream>//for i/o stream
#include <fstream>//to read program file
#include <queue>//storing each line of of the program in file
#include <array>//for easy use of arrays

/** *@brief creates exception objects with a message for the object to display when thrown*/
class Exceptions{
    public:
        
        /**
        *@brief Exceptions constructor
        *@param newMessage the message to display when the exception is thrown*/
        Exceptions(const std::string& newMessage);
        
        /**
        *@brief Exceptions constructor
        *@param Error_index the index of the error in the enum 'EXCEPTIONS_MSG'
        *@param filePath name of the file where exception was thrown from
        *@param lnNum line where exception was thrown from
        *@param current_index index where exception was thrown from
        *@param current_char the character which caused an exception to be thrown*/
        Exceptions(const int& Error_index, const std::string& filePath, const int& lnNum, const int& current_index,const std::string& current_char);
        
        /**
        *@brief Exceptions constructor
        *@param Error_index the index of the error in the enum 'EXCEPTIONS_MSG'
        *@param filePath name of the file where exception was thrown from
        *@param lnNum line where exception was thrown from
        *@param current_index index where exception was thrown from
        *@param current_char the character which caused an exception to be thrown
        *@param number_str if an exeption was caused by a number, the number which caused an exception to be thrown*/
        Exceptions(const int& Error_index, const std::string& filePath, const int& lnNum, const int& current_index,const std::string& current_char, const std::string& number_str);
        
        /**
        *@brief gets the message that was created or stored when the exception was created and thrown
        *@param none
        * @return std::string*/
        std::string getMessage();
    
    private:
        
        /** *@brief stores the message to display when exception is thrown*/
        std::string message;
        
        /** *@brief name of the file where exception was thrown from*/
        std::string filePath;
        
        /** *@brief line where exception was thrown from*/
        int lnNum;
        
        /** *@brief index where exception was thrown from*/
        int current_index;
        
        /** *@brief the character which caused an exception to be thrown*/
        std::string current_char;
        
        /** *@brief (optional) if an exception was caused by a number, the number which caused an exception to be thrown*/
        std::string number_str;
        
        /**
        *@brief makes empty spaces eg ' ', of a specified length and returns a string with these spaces
        *@param length length of requested space string. A single space is represented by one 
        *@return std::string*/
        std::string makeSpaces(const int& length);
        
        /**
        *@brief determines which error message must be thrown depending on the index passed in which
        corresponds to the index's in the enum 'EXCEPTIONS_MSG'
        *@param Error_index the index which corresponds to the index's in the enum 'EXCEPTIONS_MSG'
        *@return std::string*/
        std::string createErrorMessage(const int& Error_index);
};

/** *@brief enum that stores error codes for exceptions*/
enum EXCEPTIONS_MSG{
    EXPECTED__SECOND_and_symbol_,
    EXPECTED__SECOND_or_symbol_,
    INVALID_CHAR_INPUT,
    MULTIPLE_DOTS_IN_floatingpoint_,
    EXPECTED__NUM__beforeDOT_,
    ELSEIF_ELSE_BEFORE_IF_STTMNT,
    UNSUPPORTED_TOKEN_IN_PARSER,
    EOF__INCOMPLETE__PROGRAM,
    MIXING_DATA_TYPES,
    VARIABLE_NOTFOUND,
    NULLPTREXCEPTION,//with variables
    INCORRECT_APPENDING,// word data = data + "extra data";
    NULLVARIABLE,
    NOT_ALLOWED_CHARACTER,
    MISSING_RPAREN,
    NO_MATCHINGTYPE,
    NULLPTREXC,//no variable
    MISSING_VARNAME,
    MISSING_ASSINGMENT_OP,
    VAR_ALREADY_EXISTS,
    MISSING_LPAREN_builtin, 
    MISSING_RPAREN_builtin,
    OPENINGSCOPE,
    CLOSINGSCOPE,
    MISSING_LPAREN_forloop,
    MISSING_RPAREN_forloop,
    INCORRECT_FORLOOP,
    NO_FORLOOP_DECL,
    FORLOOP_SEP,
    MISSING_LPAREN_function,
    MISSING_RPAREN_function,
    MISSING_COMMA_SEP,
    MAX_FUNC_ARG,
    MISSING_DATATYPE,
    INCORRECT_FUNCTIONARG_TYPE,
    NULLPTREXCEPTION_INTERPRETER,
    ATTEMPTED_BOOLEAN_APPEND,
    INCORRECT_VARIABLE_DATATYPE,
    INCORRECT_OPERATION,
    INVALID_UNARY_TYPE,
    DIVISION_BY_ZERO,
    UNRECOGNIZABLE_OPERATOR,
    UNRECOGNIZABLE_WORD_DATATYPE_OPERATOR, 
    CANNOT_APPEND_BOOLEANS,
    INCORRECT_CONDITIONAL_CHECKER,
};

#endif