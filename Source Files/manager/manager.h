/**
*@file manager.h manager.cpp
*@class manager
*@author Michael
*@brief is responsible for managing the opening of the file and running of the lexer, parser and interpreter*/

#ifndef MANAGER_H
#define MANAGER_H
#include "../lexer/lexer.h"
#include "../parser/parser.h"
#include "../Interpreterr/Interpreter.h"

/** *@brief is responsible for managing the opening of the file and running of the lexer, parser and interpreter*/
class manager{
private:
    /** *@brief filepath of the file to be processed*/
    std::string filepath = "";
    /** *@brief current line in the file being processed*/
    int lnNum = 0;
    /** *@brief array size of acceptable characters that can be processed by the lexer*/
    static const int acceptable_charactersSIZE = 86;

    /** *@brief is used to keep track of whether or not a comment is currently being read*/
    bool isInComment = false;
    
    /**
    *@brief determines if the character being read is part of acceptable characters
    *@param character character to check
    * @return bool*/
    static bool aceptableChars(const char& character);

    /** *@brief an array of acceptable characters that can be processed by the lexer*/
    static const std::array<char, manager::acceptable_charactersSIZE> acceptable_characters;

    /**
    *@brief runs the lexer, parser and interpreter for the current line
    *@param currentLine the data for current line being processed 
    * @return void*/
    void RUN__INTERPRETER(const std::string& currentLine);

    /**
    *@brief displays a vector of tokens for debugging purposes
    *@param vect a vector of tokens
    * @return void*/
    static void displayVector(const std::vector<token>& vect);

public:
    /**
    *@brief begins processing the file passed in as a string
    *@param filePath filepath of the file to be processed
    * @return void*/
    void __BEGIN__PROCESSING(const std::string& filePath);
};

#endif