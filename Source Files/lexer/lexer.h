/**
*@file lexer.h lexer.cpp
*@class lexer
*@author Michael
*@brief tokenizes the entire program line by line*/

#ifndef LEXER_H
#define LEXER_H
#include "../tokens/tokens.h"

/** *@brief tokenizes the entire program line by line*/
class lexer{
public:
    
    /**
    *@brief constructor
    *@param textfile file data in string format
    *@param filepath path of the file
    *@param linenumber current line number in the file*/
    lexer(const std::string& textfile, const std::string& filepath, const int& linenumber);
    
    /**
    *@brief tokenizes the program
    *@param none
    *@return std::vector<token>*/
    std::vector<token> __RUN__LEXER___();

private:
    /** *@brief file data in string format*/
    std::string textFile;

    /** *@brief path of the file*/
    std::string filePath;

    /** *@brief stores the tokens of the current line in the program*/
    std::vector<token> tokenObjVector;

    /** *@brief current line number in the file*/
    int lnNum;

    /** *@brief the current char in the textfile being read*/
    std::string current_char;

    /** *@brief the current index of the current char in the textfile being read*/
    int current_index;

    /**
    *@brief advances the lexer to the next character to tokenize in the textfile being read
    *@param none
    *@return void*/
    void advance();

    /**
    *@brief generates an identifier or keyword based on the sequence of characters being read
    *@param none
    *@return token*/
    token generate_identifier();

    /**
    *@brief matches the current character to it's corresponding token type
    *@param none
    *@return void*/
    void generate_tokens();

    /**
    *@brief generates a number data type
    *@param none
    *@return token*/
    token generate_number();

    /**
    *@brief generates a string data type
    *@param none
    *@return token*/
    token generate_string();
};
#endif