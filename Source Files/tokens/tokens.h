/**
*@file tokens.h tokens.cpp
*@class tokens
*@author Michael
*@brief includes Exceptions for classes that may include tokens
*@brief handles the creation of tokens when reading the program file
*/
#ifndef TOKEN_H
#define TOKEN_H
#include "../Exceptions/Exceptions.h"

/** *@brief mapping of different types of supported tokens*/
enum TOKENS{
    NUMBER,//=0
    PLUS,//=1
    MINUS,//=2
    MULTIPLY,//=3
    DIVIDE,//=4
    LPAREN,//=5
    RPAREN,//=6
    POWER,//=7
    IDENTIFIER,//=8
    KEYWORD,//=9
    EQUALS,//=10
    STRING,//=11
    AND,//=12
    NOT,//=13
    OR,//=14
    MODULUS,//=15
    EQUALSEQUALS,//=16
    GREATERTHAN,//=17
    LESSTHAN,//=18
    GREATERTHANOREQUALTO,//=19
    LESSTHANOREQUALTO,//=20
    NOTEQUALTO,//=21
    BEGINLOCALSCOPE,//=22
    ENDLOCALSCOPE,//=23
    PLUSEQUALS,//=24
    MINUSEQUALS,//=25
    MULTIPLYEQUALS,//=26
    DIVIDEEQUALS,//=27
    MODULUSEQUALS,//=28
    POWEREQUALS,//=29
    FORLOOPSEP,//=30 meaning ":" eg for(number val = 0 : val < 3 : val+= 1)
    FUNCARGSEP,//=31 meaning "," eg func(1, 2);
    NULLNODE//=32
};

/** *@brief mapping of different types nodes(interpreterr.cpp uses this)*/
enum VISITNODES{
    OPNODEPLUS,//=0
    OPNODEMINUS,//=1
    OPNODEMULTIPLY,//=2
    OPNODEDIVIDE,//=3
    NUMBERNODE,//=4
    PLUSUNARYOPNODE,//=5
    MINUSUNARYOPNODE,//=6
    POWEROPNODE,//=7
    NUMBERVARNODE,//=8
    STRINGVARNODE,//=9
    STRINGNODE,//=10
    OPNODEAND,//=11
    OPNODENOT,//=12
    OPNODEOR,//=13
    OPNODEMODULUS,//=14
    OPNODEEQUALSEQUALS,//=15
    OPNODEGREATERTHAN,//=16
    OPNODELESSTHAN,//=17
    OPNODEGREATERTHANOREQUALTO,//=18
    OPNODELESSTHANOREQUALTO,//=29
    OPNODENOTEQUALTO,//=20
    BUITINFUNCTION,//=21
    IFSTATEMENTNODE,//=22
    ELSEIFSTATEMENTNODE,//=23
    ELSESTATEMENT,//=24
    WHILESTATEMENT,//=25
    OPNODEPLUSEQUALS,//=26
    OPNODEMINUSEQUALS,//=27
    OPNODEMULTIPLYEQUALS,//=28
    OPNODEDIVIDEEQUALS,//=29
    OPNODEMODULUSEQUALS,//=30
    OPNODEPOWEREQUALS,//=31
    FORSTATEMENT,//=32
    FUNCTIONDECLARATION,//=33
    NULLPTRNODE//=34
};

/** *@brief mapping of supported keywords*/
enum KEYWRODSTYPE{
    NUMBERKEY,//=0
    STRINGKEY,//=1
    PRINTLINE,//=2
    PRINTNEWLINE,//=3
    DISPLAYLINE,//=4
    DISPLAYNEWLINE,//=5
    IF,//=6
    ELSEIF,//=7
    ELSE,//=8
    THEN,//=9
    WHILE,//=10
    FOR,//=11
    FUNCTION__DECL,//=12
    FUNCTION__CALL//=13
};

/** *@brief stores the mapping of different keywords and types*/
class tokens{
private:
    /** *@brief the sizes of the arrays which store all of the languages tokens and keywords*/
    const static int tokensArrSIZE = 33, ignoreCharArrSIZE = 3, DIGITSSIZE = 11, KEYWORDSSIZE = 14,
    LETTERSSIZE = 53, visitNodesArrSIZE = 34;
    
public:
    /** *@brief stores the various supported tokens such as +, - etc*/
    const static std::array<std::string, tokens::tokensArrSIZE> tokensArr;

    /** *@brief stores ignorable characters such as ' ', \\n etc*/
    const static std::array<char, tokens::ignoreCharArrSIZE> ignoreCharArr;

    /** *@brief stores range of all digits from 0 - 9*/
    const static std::array<char, tokens::DIGITSSIZE> DIGITS;

    /** *@brief stores the various keywords such number, for, while*/
    const static std::array<std::string, tokens::KEYWORDSSIZE> KEYWORDS;

    /** *@brief stores all letters in the alphabet in upper and lower case and the underscore symbol '_'*/
    const static std::array<char, tokens::LETTERSSIZE> LETTERS;

    /** *@brief stores which node type should be visited for the currently selected node(only used in parser.cpp and interpreterr.cpp) '_'*/
    const static std::array<std::string, tokens::visitNodesArrSIZE> visitNodesArr;

    /**
    *@brief checks if the passed in toCheck arg is an ignorable character
    *@param toCheck the string to test
    *@return bool*/
    static bool isInIgnoreCharArr(const std::string& toCheck);

    /**
    *@brief checks if the passed in toCheck arg is a digit
    *@param toCheck the string to test
    *@return bool*/
    static bool isInDIGITSarr(const std::string& toCheck);

    /**
    *@brief checks if the passed in toCheck arg is a letter
    *@param toCheck the string to test
    *@return bool*/
    static bool isInLETTERSarr(const std::string& toCheck);

    /**
    *@brief checks if the passed in toCheck arg is a keyword in the language
    *@param toCheck the string to test
    *@return bool*/
    static bool isInKEYWORDSarr(const std::string& toCheck);

    /**
    *@brief gets the token which maps to the passed in index arg in std::string format
    *@param index the index of the token mapped from the enum TOKENS
    *@return std::string*/
    static std::string tokentype(const int& index);

    /**
    *@brief checks if the passed in nodeType arg is an operator node
    *@param nodeType the string to test
    *@return bool*/
    static bool isOperatorNode(const std::string& nodeType);
};

/** *@brief creates an object with the mapping of a token that was assigned to it from the 'tokens' class*/
class token{
public:
    /** *@brief number used to represent token type in enums*/
    int type = tokens::tokensArr.size() - 1;
    /** *@brief can be none if the no value is assigned, eg plus or minus operations*/
    std::string value = "";

    /**
    *@brief returns a string representation of the the type and value class member variables
    *@param none
    *@return const std::string*/
    std::string __represent__ () const;
};

#endif