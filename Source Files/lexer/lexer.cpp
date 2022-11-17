#include "lexer.h"

lexer::lexer(const std::string& textfile, const std::string& filepath, const int& linenumber){
    this->filePath = filepath;
    this->lnNum = linenumber;
    this->textFile = textfile;
    this->current_index = 0;
    this->advance();
}

std::vector<token> lexer::__RUN__LEXER___(){
    this->generate_tokens();
    return this->tokenObjVector;
}

void lexer::advance(){
    if(this->current_index < textFile.length()){
        this->current_char = textFile[this->current_index];
        ++this->current_index;
    }
    else{
        this->current_char = "EOF";
    }
}

void lexer::generate_tokens(){
    while(this->current_char != "EOF"){
        if(tokens::isInIgnoreCharArr(this->current_char)){
            this->advance();
        }
        else if(tokens::isInDIGITSarr(this->current_char)){
            this->tokenObjVector.push_back(this->generate_number());
            } 
        else if(tokens::isInLETTERSarr(this->current_char)){
            this->tokenObjVector.push_back(this->generate_identifier());
            }
        else if(this->current_char == ","){
            token obj;
            obj.type = TOKENS::FUNCARGSEP;
            this->tokenObjVector.push_back(obj);
            this->advance();
        }
        else if(this->current_char == ":"){
            token obj;
            obj.type = TOKENS::FORLOOPSEP;
            this->tokenObjVector.push_back(obj);
            this->advance();
        }
        else if(this->current_char == "+"){
            this->advance();
            if(this->current_char == "="){
                token obj;
                obj.type = TOKENS::PLUSEQUALS;
                this->tokenObjVector.push_back(obj);
                this->advance();
            }
            else{
                token obj;
                obj.type = TOKENS::PLUS;
                this->tokenObjVector.push_back(obj);
            }
        }
        else if(this->current_char == "-"){
            this->advance();
            if(this->current_char == "="){
                token obj;
                obj.type = TOKENS::MINUSEQUALS;
                this->tokenObjVector.push_back(obj);
                this->advance();
            }
            else{
                token obj;
                obj.type = TOKENS::MINUS;
                this->tokenObjVector.push_back(obj);
            }
        }
        else if(this->current_char == "*"){
            this->advance();
            if(this->current_char == "="){
                token obj;
                obj.type = TOKENS::MULTIPLYEQUALS;
                this->tokenObjVector.push_back(obj);
                this->advance();
            }
            else{
                token obj;
                obj.type = TOKENS::MULTIPLY;
                this->tokenObjVector.push_back(obj);
            }
        }
        else if(this->current_char == "/"){
            this->advance();
            if(this->current_char == "/"){return;}
            else if(this->current_char == "="){
                token obj;
                obj.type = TOKENS::DIVIDEEQUALS;
                this->tokenObjVector.push_back(obj);
                this->advance();
            }
            else{
                token obj;
                obj.type = TOKENS::DIVIDE;
                this->tokenObjVector.push_back(obj);
            }
        }
        else if(this->current_char == "("){
            token obj;
            obj.type = TOKENS::LPAREN;
            this->tokenObjVector.push_back(obj);
            this->advance();
        }
        else if(this->current_char == ")"){
            token obj;
            obj.type = TOKENS::RPAREN;
            this->tokenObjVector.push_back(obj);
            this->advance();
        }
        else if(this->current_char == "^"){
            this->advance();
            if(this->current_char == "="){
                token obj;
                obj.type = TOKENS::POWEREQUALS;
                this->tokenObjVector.push_back(obj);
                this->advance();
            }
            else{
                token obj;
                obj.type = TOKENS::POWER;
                this->tokenObjVector.push_back(obj);
            }
        }
        else if(this->current_char == "&"){
            this->advance();
            if(this->current_char == "&"){
                token obj;
                obj.type = TOKENS::AND;
                this->tokenObjVector.push_back(obj);
                this->advance();
            }
            else{
                Exceptions newExc(EXCEPTIONS_MSG::EXPECTED__SECOND_and_symbol_, this->filePath, this->lnNum, this->current_index, this->current_char);
                throw newExc;
            }
        }
        else if(this->current_char == "|"){
            this->advance();
            if(this->current_char == "|"){
                token obj;
                obj.type = TOKENS::OR;
                this->tokenObjVector.push_back(obj);
                this->advance();
            }
            else{
                Exceptions newExc(EXCEPTIONS_MSG::EXPECTED__SECOND_or_symbol_, this->filePath, this->lnNum, this->current_index, this->current_char);
                throw newExc;
            }
        }
        else if(this->current_char == "!"){
            this->advance();
            if(this->current_char == "="){
                token obj;
                obj.type = TOKENS::NOTEQUALTO;
                this->tokenObjVector.push_back(obj);
                this->advance();
            }
            else{
                token obj;
                obj.type = TOKENS::NOT;
                this->tokenObjVector.push_back(obj);
            }
        }
        else if(this->current_char == "%"){
            this->advance();
            if(this->current_char == "="){
                token obj;
                obj.type = TOKENS::MODULUSEQUALS;
                this->tokenObjVector.push_back(obj);
                this->advance();
            }
            else{
                token obj;
                obj.type = TOKENS::MODULUS;
                this->tokenObjVector.push_back(obj);
            }
        }
        else if(this->current_char == "="){
            this->advance();
            if(this->current_char == "="){
                token obj;
                obj.type = TOKENS::EQUALSEQUALS;
                this->tokenObjVector.push_back(obj);
                this->advance();
            }
            else{
                token obj;
                obj.type = TOKENS::EQUALS;
                this->tokenObjVector.push_back(obj);
            }
        }
        else if(this->current_char == ">"){
            this->advance();
            if(this->current_char == "="){
                token obj;
                obj.type = TOKENS::GREATERTHANOREQUALTO;
                this->tokenObjVector.push_back(obj);
                this->advance();
            }
            else{
                token obj;
                obj.type = TOKENS::GREATERTHAN;
                this->tokenObjVector.push_back(obj);
            }
        }
        else if(this->current_char == "<"){
            this->advance();
            if(this->current_char == "="){
                token obj;
                obj.type = TOKENS::LESSTHANOREQUALTO;
                this->tokenObjVector.push_back(obj);
                this->advance();
            }
            else{
                token obj;
                obj.type = TOKENS::LESSTHAN;
                this->tokenObjVector.push_back(obj);
            }
        }
        else if(this->current_char[0] == '"'){
            this->tokenObjVector.push_back(this->generate_string());
        }
        else if(this->current_char == "{"){
            token obj;
            obj.type = TOKENS::BEGINLOCALSCOPE;
            this->tokenObjVector.push_back(obj);
            this->advance();
        }
        else if(this->current_char == "}"){
            token obj;
            obj.type = TOKENS::ENDLOCALSCOPE;
            this->tokenObjVector.push_back(obj);
            this->advance();
        }
        else{
            Exceptions newExc(EXCEPTIONS_MSG::INVALID_CHAR_INPUT, this->filePath, this->lnNum + 1, this->current_index, this->current_char);
            throw newExc;
        }
    }
}

token lexer::generate_number(){
    std::string number_str = "";
    
    int decimalPointCount = 0;

    while(this->current_char != "EOF" && tokens::isInDIGITSarr(this->current_char)){
        if(this->current_char == ".")++decimalPointCount;

        number_str += this->current_char;

        if(decimalPointCount > 1){
            //throw error
            Exceptions newExc(EXCEPTIONS_MSG::MULTIPLE_DOTS_IN_floatingpoint_, this->filePath, this->lnNum + 1, this->current_index, this->current_char, number_str);
            throw newExc;
        }

        this->advance();
    }

    if(number_str[0] == '.' && number_str.length() == 1){
        //throw error
            Exceptions newExc(EXCEPTIONS_MSG::EXPECTED__NUM__beforeDOT_, this->filePath, this->lnNum + 1, this->current_index, this->current_char, number_str);
            throw newExc;
    }
    if(number_str[0] == '.' && number_str.length() > 1)number_str = "0" + number_str;
    if(number_str[number_str.length() - 1] == '.' && number_str.length() > 1)number_str += "0";

    token obj;
    obj.type = TOKENS::NUMBER;
    obj.value = number_str;
    return obj;
}

token lexer::generate_identifier(){
    std::string id_string = "";

    while(this->current_char != "EOF" && tokens::isInLETTERSarr(this->current_char)){
        id_string += this->current_char;
        this->advance();
    }

    token obj;
    if(tokens::isInKEYWORDSarr(id_string)){
        obj.type = TOKENS::KEYWORD;
        obj.value = id_string;
    }
    else if(id_string.length() > 0){
        obj.type = TOKENS::IDENTIFIER;
        obj.value = id_string;
    }
    return obj;
}

token lexer::generate_string(){
    std::string stringData = "";
    this->advance();

    while(this->current_char != "EOF" && this->current_char[0] != '"'){
        stringData += this->current_char;
        this->advance();
    }
    this->advance();//incase if current char is currently = '"'

    token obj;
    obj.type = TOKENS::STRING;
    obj.value = stringData;

    return obj;
}
