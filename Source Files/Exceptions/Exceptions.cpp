#include "Exceptions.h"

Exceptions::Exceptions(const std::string& newMessage){this->message = newMessage;}

Exceptions::Exceptions(const int& Error_index, const std::string& filePath, const int& lnNum, const int& current_index,const std::string& current_char){
    this->filePath = filePath;
    this->lnNum = lnNum;
    this->current_index = current_index;
    Exceptions::current_char = current_char;
    this->message = createErrorMessage(Error_index);
}

Exceptions::Exceptions(const int& Error_index, const std::string& filePath, const int& lnNum, const int& current_index,const std::string& current_char, const std::string& number_str){
    this->filePath = filePath;
    this->lnNum = lnNum;
    this->current_index = current_index;
    this->current_char = current_char;
    this->number_str = number_str;
    this->message = createErrorMessage(Error_index);
}

std::string Exceptions::getMessage(){return this->message;}

std::string Exceptions::makeSpaces(const int& length){
    std::string spaces = "";

    for(int i = 0; i < length; ++i){
        spaces += " ";
    }
    return spaces;
}

std::string Exceptions::createErrorMessage(const int& Error_index){
    if(Error_index == EXCEPTIONS_MSG::EXPECTED__SECOND_and_symbol_){
        return "ERROR: Cannot determine instructions here. File: " + this->filePath + " At line: " + std::to_string(this->lnNum) + "\n"
                    "Expected a second AND symbol after the first one: '&'\n"
                    "\n"
                    "In position: " + std::to_string(this->current_index) + " value: &"+ Exceptions::current_char +"\n"
                    "                      "+ Exceptions::makeSpaces(Exceptions::current_char.length()) +"^\n";
    }
    else if(Error_index == EXCEPTIONS_MSG::EXPECTED__SECOND_or_symbol_){
        return  "ERROR: Cannot determine instructions here. File: " + this->filePath + " At line: " + std::to_string(this->lnNum) + "\n"
                    "Expected a second OR symbol after the first one: '|'\n"
                    "\n"
                    "In position: " + std::to_string(this->current_index) + " value: |"+ Exceptions::current_char +"\n"
                    "                      "+ Exceptions::makeSpaces(Exceptions::current_char.length()) +"^\n";
    }
    else if(Error_index == EXCEPTIONS_MSG::INVALID_CHAR_INPUT){
        return 
        "ERROR: This character is not currently supported. File: " + this->filePath + " At line: " + std::to_string(this->lnNum) + "\n"
                    "\n"
                    "In position: " + std::to_string(this->current_index) + " value: "+ Exceptions::current_char +"\n"
                    "                       ^\n";
    }
    else if(Error_index == EXCEPTIONS_MSG::MULTIPLE_DOTS_IN_floatingpoint_){
        return
        "ERROR: You cannot have more than one dot in a single number type. File: " + this->filePath + " At line: " + std::to_string(this->lnNum) + "\n"
                    "Did not expect more than one: '.'\n"
                    "\n"
                    "In position: " + std::to_string(this->current_index) + " value: "+ this->number_str +"\n"
                    "                      "+ Exceptions::makeSpaces(this->number_str.length()) +"^\n";
    }
    else if(Error_index == EXCEPTIONS_MSG::EXPECTED__NUM__beforeDOT_){
        return "ERROR: You cannot have one dot with no numbers. File: " + this->filePath + " At line: " + std::to_string(this->lnNum) + "\n"
                    "Expected numbers either or before: '.'\n"
                    "\n"
                    "In position: " + std::to_string(this->current_index) + " value: "+ this->number_str +"\n"
                    "                      "+ Exceptions::makeSpaces(this->number_str.length()) +"^\n";
    }
    else if(Error_index == EXCEPTIONS_MSG::ELSEIF_ELSE_BEFORE_IF_STTMNT){
        return "ERROR: No else or elseif statements are allowed before declaring an if statement first. File: " + this->filePath + " line number: " + std::to_string(this->lnNum) + "\n"
                "Expected an if statement before else or elseif statement:\n\n"
                "'if(<conditional expression>){<statements>}\n"
                "elseif(<conditional expression>){<statements>}\n"
                "else{<statements>}'\n\n"
                "In position: " + std::to_string(this->current_index) + " data: "+ Exceptions::current_char +"\n"
                "                        ^\n\n";
    }
    else if(Error_index == EXCEPTIONS_MSG::UNSUPPORTED_TOKEN_IN_PARSER){
        return "ERROR: This keyword is not supported. File: " + this->filePath + " line number: " + std::to_string(this->lnNum) +
                "\n\n"
                "In position: " + std::to_string(this->current_index) + " data: "+ Exceptions::current_char +"\n"
                "                        ^\n\n";
    }
    else if(Error_index == EXCEPTIONS_MSG::EOF__INCOMPLETE__PROGRAM){
        return "WARNING: End of file reached with no meaningful data read. File: " + this->filePath + " line number: " + std::to_string(this->lnNum) + "\n"
                    "Expected numbers and operators in file.\n"
                    "\n"
                    "In position: " + std::to_string(this->current_index) + "\n\n";
    }
    else if(Error_index == EXCEPTIONS_MSG::MIXING_DATA_TYPES){
        return "FATAL ERROR: You cannot mix word and number types. File: " + this->filePath + " line number: " + std::to_string(this->lnNum) + "\n"
                    "\n"
                    "In position: " + std::to_string(this->current_index) + " data: "+ Exceptions::current_char + "\n"
                    "                        ^\n\n";
    }
    else if(Error_index == EXCEPTIONS_MSG::VARIABLE_NOTFOUND){
        return "FATAL ERROR: No matching variable could be found. File: " + this->filePath + " line number: " + std::to_string(this->lnNum) + "\n"
                    "You cannot mix 'number' and 'word' data types together\n\n"
                    "In position: " + std::to_string(this->current_index) + " name: "+ Exceptions::current_char + "\n"
                    "                        ^\n\n";
    }
    else if(Error_index == EXCEPTIONS_MSG::NULLPTREXCEPTION){
        return "FATAL ERROR: NULL pointer exception. File: " + this->filePath + " line number: " + std::to_string(this->lnNum) + "\n"
                "\n"
                "In position: " + std::to_string(this->current_index) + " name: "+ Exceptions::current_char + "\n"
                "                        ^\n\n";
    }
    else if(Error_index == EXCEPTIONS_MSG::INCORRECT_APPENDING){
        return "FATAL ERROR: This operation is not supported. File: " + this->filePath + " line number: " + std::to_string(this->lnNum) + "\n"
                    "You cannot mix append a variable to itself in this manner. Expected: <var name> (+, -, *, / or %)= (<number> or other <var>)\n\n"
                    "In position: " + std::to_string(this->current_index) + " name: "+ Exceptions::current_char + "\n"
                    "                        ^\n\n";
    }
    else if(Error_index == EXCEPTIONS_MSG::NULLVARIABLE){
        return "FATAL ERROR: variable has no data assigned to it. File: " + this->filePath + " line number: " + std::to_string(this->lnNum) + "\n"
                    "Excpected a variable with assigned data\n"
                    "In position: " + std::to_string(this->current_index) + " name: "+ Exceptions::current_char + " = null\n"
                    "                        ^\n\n";
    }
    else if(Error_index == EXCEPTIONS_MSG::NOT_ALLOWED_CHARACTER){
        return "ERROR: This character token is not permissible after or before this sequence.\n File: " 
                + this->filePath + " line number: " + std::to_string(this->lnNum) + "\n\n"
                "Token type: " + Exceptions::current_char + "\n"
                "             ^ In position: " + std::to_string(this->current_index) + "\n\n";
    }
    else if(Error_index == EXCEPTIONS_MSG::MISSING_RPAREN){
        return "ERROR: No closing bracket detected to close of the expression. File: " + this->filePath + " line number: " + std::to_string(this->lnNum) + "\n"
                    "Expected a right parenthesis to close of expression: ')'\n"
                    "\n"
                    "In position: " + std::to_string(this->current_index) + " data: "+ Exceptions::current_char +"\n"
                    "                        ^\n\n";
    }
    else if(Error_index == EXCEPTIONS_MSG::NO_MATCHINGTYPE){
        return "FATAL ERROR: No matching type could be generated for a character. File: " + this->filePath + " line number: " + std::to_string(this->lnNum) + "\n"
                    "\n"
                    "In position: " + std::to_string(this->current_index) + " data: "+ Exceptions::current_char + "\n"
                    "                        ^\n\n";
    }
    else if(Error_index == EXCEPTIONS_MSG::NULLPTREXC){
        return "ERROR: NULLPTR exception occured. File: " 
                + this->filePath + " line number: " +  std::to_string(this->lnNum) + "\n\n"
                "Token type: " + Exceptions::current_char + "\n"
                "             ^ In position: " + std::to_string(this->current_index) + "\n\n";
    }
    else if(Error_index == EXCEPTIONS_MSG::MISSING_VARNAME){
        return "FATAL ERROR: No identifier name detected after creation of new data type. File: " + this->filePath + " line number: " + std::to_string(this->lnNum) + "\n"
                "\n"
                "In position: " + std::to_string(this->current_index) + " "+ Exceptions::current_char +"\n"
                "                       ^....Excpected an identifier name here\n\n";
    }
    else if(Error_index == EXCEPTIONS_MSG::MISSING_ASSINGMENT_OP){
        return "ERROR: No assignment operator detected. File: " + this->filePath + " line number: " + std::to_string(this->lnNum) + "\n"
                "Expected an assignment operator: '='\n\n"
                "In position: " + std::to_string(this->current_index) + " data: "+ Exceptions::current_char + "\n"
                "                       ^\n\n";
    }
    else if(Error_index == EXCEPTIONS_MSG::VAR_ALREADY_EXISTS){
        return "ERROR: You cannot redeclare an already existing variable. File: " + this->filePath + " line number: " + std::to_string(this->lnNum) + "\n"
                    "\n"
                    "In position: " + std::to_string(this->current_index) + " data: "+ Exceptions::current_char + "\n"
                    "                       ^\n\n";
    }
    else if(Error_index == EXCEPTIONS_MSG::MISSING_LPAREN_builtin){
        return "ERROR: No opening bracket detected to begin expression. File: " + this->filePath + " line number: " + std::to_string(this->lnNum) + "\n"
                "Expected a left parenthesis to open a new expression: '('\n\n"
                "All built in function calls should have their expressions wrapped in brackets like so:\n"
                "<built-in name>(<expression>);\n\n"
                "In position: " + std::to_string(this->current_index) + " data: "+ Exceptions::current_char +"\n"
                "                        ^\n\n";
    }
    else if(Error_index == EXCEPTIONS_MSG::MISSING_RPAREN_builtin){
        return "ERROR: No closing bracket detected to close of the expression. File: " + this->filePath + " line number: " + std::to_string(this->lnNum) + "\n"
                "Expected a right parenthesis to close of expression: ')'\n\n"
                "All built in function calls should have their expressions wrapped in brackets like so:\n"
                "<built-in name>(<expression>);\n\n"
                "In position: " + std::to_string(this->current_index) + " data: "+ Exceptions::current_char +"\n"
                "                        ^\n\n";
    }
    else if(Error_index == EXCEPTIONS_MSG::OPENINGSCOPE){
        return "ERROR: No opening brace detected. File: " + this->filePath  + " line number: " + std::to_string(this->lnNum) + "\n"
                "Expected a left opening brace to begin a new local scope: '{'\n\n"
                "In position: " + std::to_string(this->current_index) + " data: "+ Exceptions::current_char +"\n"
                "                        ^\n\n";
    }
    else if(Error_index == EXCEPTIONS_MSG::CLOSINGSCOPE){
        return "ERROR: No closing brace detected. File: " + this->filePath  + " line number: " + std::to_string(this->lnNum) + "\n"
                "Expected a right closing brace to end a previously opened local scope: '}'\n\n"
                "In position: " + std::to_string(this->current_index) + " data: "+ Exceptions::current_char +"\n"
                "                        ^\n\n";
    }
    else if(Error_index == EXCEPTIONS_MSG::MISSING_LPAREN_forloop){
        return "ERROR: No opening brace detected. File: " + this->filePath + " line number: " + std::to_string(this->lnNum) + "\n"
                "Expected a left opening brace to begin for-loop: '('\n\n"
                "In position: " + std::to_string(this->current_index) + " data: "+ Exceptions::current_char +"\n"
                "                        ^\n\n";
    }
    else if(Error_index == EXCEPTIONS_MSG::MISSING_RPAREN_forloop){
        return "ERROR: No closing brace detected. File: " + this->filePath + " line number: " + std::to_string(this->lnNum) + "\n"
                "Expected a right closing brace to close of for-loop: ')'\n\n"
                "In position: " + std::to_string(this->current_index) + " data: "+ Exceptions::current_char +"\n"
                "                        ^\n\n";
    }
    else if(Error_index == EXCEPTIONS_MSG::INCORRECT_FORLOOP){
        return "ERROR: Did not expect this declaration type. File: " + this->filePath + " line number: " + std::to_string(this->lnNum) + "\n"
                "Expected a number declaration: 'for(number example = 0 : example < 1 : example += 1)'\n\n"
                "In position: " + std::to_string(this->current_index) + " data: "+ Exceptions::current_char +"\n"
                "                        ^\n\n";
    }
    else if(Error_index == EXCEPTIONS_MSG::NO_FORLOOP_DECL){
        return "ERROR: No declaration detected. File: " + this->filePath + " line number: " + std::to_string(this->lnNum) + "\n"
                "Expected a declaration to start of for loop: 'for(number example = 0 : example < 1 : example += 1)'\n\n"
                "                                                        ^^^^^^^---???"
                "In position: " + std::to_string(this->current_index) + " data: "+ Exceptions::current_char +"\n"
                "                        ^\n\n";
    }
    else if(Error_index == EXCEPTIONS_MSG::FORLOOP_SEP){
        return "ERROR: No seperator detected in for loop. File: " + this->filePath + " line number: " + std::to_string(this->lnNum) + "\n"
                "Expected a seperator between each statement in for loop: for(number example = 0 ':' example < 1 ':' example += 1)\n\n"
                "                                                                                 ^               ^"
                "In position: " + std::to_string(this->current_index) + " data: "+ Exceptions::current_char +"\n"
                "                        ^\n\n";
    }
    else if(Error_index == EXCEPTIONS_MSG::MISSING_LPAREN_function){
        return "ERROR: No opening brace detected. File: " + this->filePath + " line number: " + std::to_string(this->lnNum) + "\n"
                "Expected a left opening brace for function arguments: '('\n\n"
                "In position: " + std::to_string(this->current_index) + " data: "+ Exceptions::current_char +"\n"
                "                        ^\n\n";
    }
    else if(Error_index == EXCEPTIONS_MSG::MISSING_RPAREN_function){
        return "ERROR: No closing brace detected. File: " + this->filePath + " line number: " + std::to_string(this->lnNum) + "\n"
                "Expected a right closing brace for function arguments: ')'\n\n"
                "In position: " + std::to_string(this->current_index) + " data: "+ Exceptions::current_char +"\n"
                "                        ^\n\n";
    }
    else if(Error_index == EXCEPTIONS_MSG::MISSING_COMMA_SEP){
        return "ERROR: No comma detected. File: " + this->filePath + " line number: " + std::to_string(this->lnNum) + "\n"
                "Expected a comma to separate function arguments: ','\n\n"
                "In position: " + std::to_string(this->current_index) + " data: "+ Exceptions::current_char +"\n"
                "                        ^\n\n";
    }
    else if(Error_index == EXCEPTIONS_MSG::MAX_FUNC_ARG){
        return "ERROR: Exceeded Max amount of allowed function arguments. File: " + this->filePath + " line number: " + std::to_string(this->lnNum) +
            "\nDid not expect more than " + std::to_string(this->current_index) + "arguments. Function:\n\n"
            + Exceptions::current_char +
            "                        \n\n";
    }
    else if(Error_index == EXCEPTIONS_MSG::MISSING_DATATYPE){
        return "ERROR: No data-type detected. File: " + this->filePath + " line number: " + std::to_string(this->lnNum) +
            "\nExpected a data-type: 'number <variable>' or 'word <variable>'\n\n"
            "In position: " + std::to_string(this->current_index) + " data: "+ Exceptions::current_char +"\n"
            "                        ^\n\n";
    }
    else if(Error_index == EXCEPTIONS_MSG::INCORRECT_FUNCTIONARG_TYPE){
        return "ERROR: This keyword is not supported as a function argument. File: " + this->filePath + " line number: " + std::to_string(this->lnNum) +
            "\n\n"
            "In position: " + std::to_string(this->current_index) + " data: "+ Exceptions::current_char +"\n"
            "                        ^\n\n";
    }
    else if(Error_index == EXCEPTIONS_MSG::NULLPTREXCEPTION_INTERPRETER){
        return "FATAL ERROR: NULL pointer exception. File: " + this->filePath + " line number: " + std::to_string(this->lnNum) + "\n"
                "\n"
                " Current data: "+ Exceptions::current_char + "\n"
                "                        ^\n\n";
    }
    else if(Error_index == EXCEPTIONS_MSG::ATTEMPTED_BOOLEAN_APPEND){
        return "FATAL ERROR: Boolean statements cannot be appended to each other:\n" 
                + Exceptions::current_char + "\n"
                "\n\nFile: " + this->filePath + " line number: " + std::to_string(this->lnNum) + "\n\n";
    }
    else if(Error_index == EXCEPTIONS_MSG::INCORRECT_VARIABLE_DATATYPE){
        return "FATAL ERROR: A variable can not exist with such a datatype:\n" 
                + Exceptions::current_char + "\n"
                "\n\nFile: " + this->filePath + " line number: " + std::to_string(this->lnNum) + "\n\n";
    }
    else if(Error_index == EXCEPTIONS_MSG::INCORRECT_OPERATION){
        return "FATAL ERROR: Could not find the appropriate node type for this token or this operation is not supported on word data types:\n" 
                          + Exceptions::current_char +
                          "\n\nFile: " + this->filePath + " line number: " + std::to_string(this->lnNum) + "\n\n";
    }
    else if(Error_index == EXCEPTIONS_MSG::INVALID_UNARY_TYPE){
        return "FATAL ERROR: This unary operation could not be recognised: " + Exceptions::current_char +
                          "\n\nFile: " + this->filePath + " line number: " + std::to_string(this->lnNum) + "\n\n";
    }
    else if(Error_index == EXCEPTIONS_MSG::DIVISION_BY_ZERO){
        return "FATAL ERROR: Attempted a division by 0\n"
                "          data:" + Exceptions::current_char +
                "File: " + this->filePath + " line number: " + std::to_string(this->lnNum);
    }
    else if(Error_index == EXCEPTIONS_MSG::UNRECOGNIZABLE_OPERATOR){
        return "FATAL ERROR: This operation could not be recognized: " + Exceptions::current_char +
                            "\n\nFile: " + this->filePath + " line number: " + std::to_string(this->lnNum) + "\n\n";
    }
    else if(Error_index == EXCEPTIONS_MSG::UNRECOGNIZABLE_WORD_DATATYPE_OPERATOR){
        return "FATAL ERROR: This operation is not allowed on word data types: " + Exceptions::current_char +
                            "\n\nFile: " + this->filePath + " line number: " + std::to_string(this->lnNum) + "\n\n";
    }
    else if(Error_index == EXCEPTIONS_MSG::CANNOT_APPEND_BOOLEANS){
        return "FATAL ERROR: Boolean statements cannot be appended to each other:\n" 
                          + Exceptions::current_char + "\n"
                          "\n\nFile: " + this->filePath + " line number: " + std::to_string(this->lnNum) + "\n\n";
    }
    else if(Error_index == EXCEPTIONS_MSG::INCORRECT_CONDITIONAL_CHECKER){
        return "FATAL ERROR: This operation is not allowed for conditonal checking: " + Exceptions::current_char +
                            "\n\nFile: " + this->filePath + " line number: " + std::to_string(this->lnNum) + "\n\n";
    }
    else{
        return "null";
    }
}
