#include "parser.h"

const std::array<std::string, STATEMENT_DATATYPE::STATEMENT_DATATYPE_SIZE> parser::datatypeARR = {"number", "word", "null"};
const std::string parser::default_DT = "DEFAULT";

parser::parser(const std::vector<token>& vect, const std::string& filepath, const int& linenumber){
    this->tokensVect = vect;
    this->current_index = 0;
    this->lnNum = linenumber;
    this->filePath = filepath;
    this->dataType = parser::default_DT;
    this->datatype = parser::datatypeARR[STATEMENT_DATATYPE::NULL_STATEMENT_DATATYPE];
    this->current_var_name = "";
    this->isReassigningVariable = false;
    this->isAttaching__FuncArg = false;
    this->advance();
}

void parser::advance(){
    if(this->current_index < tokensVect.size()){
        this->currentToken = tokensVect[this->current_index];
        ++this->current_index;
    }
    else{this->currentToken.value = "EOF";}
}

std::string parser::getdatatype(){return this->datatype;}

std::shared_ptr<tokenNode> parser::__BEGIN__PARSE(){return this->functions();}

std::shared_ptr<tokenNode> parser::functions(){
    if(tokens::tokensArr[this->currentToken.type] == tokens::tokensArr[TOKENS::KEYWORD]
    && this->currentToken.value == tokens::KEYWORDS[KEYWRODSTYPE::FUNCTION__DECL]){
        Exceptions newExc("Functions Are not yet supported");
        throw newExc;
        //return this->create__functions();
    }
    else return this->controlflow();
}

std::shared_ptr<tokenNode> parser::controlflow(){
    if(tokens::tokensArr[this->currentToken.type] == tokens::tokensArr[TOKENS::KEYWORD]
    && this->currentToken.value == tokens::KEYWORDS[KEYWRODSTYPE::IF]){
        return this->createifstatements();
    }
    else if(tokens::tokensArr[this->currentToken.type] == tokens::tokensArr[TOKENS::KEYWORD]
    && this->currentToken.value == tokens::KEYWORDS[KEYWRODSTYPE::WHILE]){
        return this->create_whilestatements();
    }
    else if(tokens::tokensArr[this->currentToken.type] == tokens::tokensArr[TOKENS::KEYWORD]
    && this->currentToken.value == tokens::KEYWORDS[KEYWRODSTYPE::FOR]){
        return this->create__forloops();
    }
    else if(tokens::tokensArr[this->currentToken.type] == tokens::tokensArr[TOKENS::KEYWORD]
    && (this->currentToken.value == tokens::KEYWORDS[KEYWRODSTYPE::ELSEIF] 
    || this->currentToken.value == tokens::KEYWORDS[KEYWRODSTYPE::ELSE])){
        Exceptions newExc(EXCEPTIONS_MSG::ELSEIF_ELSE_BEFORE_IF_STTMNT, this->filePath, this->lnNum, this->current_index, this->currentToken.value);
        throw newExc;
    }
    else {
        return this->variables();
    }
}

std::shared_ptr<tokenNode> parser::variables(){
    if(tokens::tokensArr[this->currentToken.type] == tokens::tokensArr[TOKENS::KEYWORD]){

        if(this->currentToken.value == tokens::KEYWORDS[KEYWRODSTYPE::NUMBERKEY]){
            return this->getNUMBERVARIABLE();
        }
        else if(this->currentToken.value == tokens::KEYWORDS[KEYWRODSTYPE::STRINGKEY]){
            return this->getWORDVARIABLE();
        }
        else if(this->currentToken.value == tokens::KEYWORDS[KEYWRODSTYPE::PRINTLINE]
         || this->currentToken.value == tokens::KEYWORDS[KEYWRODSTYPE::PRINTNEWLINE]
         || this->currentToken.value == tokens::KEYWORDS[KEYWRODSTYPE::DISPLAYLINE]
         || this->currentToken.value == tokens::KEYWORDS[KEYWRODSTYPE::DISPLAYNEWLINE]){
            return this->getPRINTDATA();
         }
         else{
            Exceptions newExc(EXCEPTIONS_MSG::UNSUPPORTED_TOKEN_IN_PARSER, this->filePath, this->lnNum, this->current_index, this->currentToken.value);
            throw newExc;
         }
    }
    else return this->OR_logical_operator_expression();//numbers
}

std::shared_ptr<tokenNode> parser::OR_logical_operator_expression(){
    std::shared_ptr<tokenNode> result = this->AND_logical_operator_expression();

    while((this->current_index - 1 < tokensVect.size()) &&
    tokens::tokensArr[this->currentToken.type] == tokens::tokensArr[TOKENS::OR]){

        if(tokens::tokensArr[currentToken.type] == tokens::tokensArr[TOKENS::OR]){
            std::shared_ptr<OperatorNode> ORobj = std::make_shared<OperatorNode>();
            ORobj->nodeType = tokens::visitNodesArr[VISITNODES::OPNODEOR];
            ORobj->op_token = "||";
            ORobj->left = result;
            this->advance();
            ORobj->right = this->AND_logical_operator_expression();
            result = ORobj;
        }
    }
    return result;
}

std::shared_ptr<tokenNode> parser::AND_logical_operator_expression(){
    std::shared_ptr<tokenNode> result = this->relational_operator_expression();

    while((this->current_index - 1 < tokensVect.size()) &&
        tokens::tokensArr[this->currentToken.type] == tokens::tokensArr[TOKENS::AND]){

        if(tokens::tokensArr[currentToken.type] == tokens::tokensArr[TOKENS::AND]){
            std::shared_ptr<OperatorNode> ANDobj = std::make_shared<OperatorNode>();
            ANDobj->nodeType = tokens::visitNodesArr[VISITNODES::OPNODEAND];
            ANDobj->op_token = "&&";
            ANDobj->left = result;
            this->advance();
            ANDobj->right = this->relational_operator_expression();
            result = ANDobj;
        }
    }
    return result;
}

std::shared_ptr<tokenNode> parser::relational_operator_expression(){
    std::shared_ptr<tokenNode> result = this->expression();

    while((this->current_index - 1 < tokensVect.size()) &&
    (tokens::tokensArr[this->currentToken.type] == tokens::tokensArr[TOKENS::EQUALSEQUALS]
     || tokens::tokensArr[this->currentToken.type] == tokens::tokensArr[TOKENS::GREATERTHAN]
      || tokens::tokensArr[this->currentToken.type] == tokens::tokensArr[TOKENS::GREATERTHANOREQUALTO]
       || tokens::tokensArr[this->currentToken.type] == tokens::tokensArr[TOKENS::LESSTHAN]
        || tokens::tokensArr[this->currentToken.type] == tokens::tokensArr[TOKENS::LESSTHANOREQUALTO]
         || tokens::tokensArr[this->currentToken.type] == tokens::tokensArr[TOKENS::NOTEQUALTO])){

            if(tokens::tokensArr[currentToken.type] == tokens::tokensArr[TOKENS::EQUALSEQUALS]){
                std::shared_ptr<OperatorNode> EEobj = std::make_shared<OperatorNode>();
                EEobj->nodeType = tokens::visitNodesArr[VISITNODES::OPNODEEQUALSEQUALS];
                EEobj->op_token = "==";
                EEobj->left = result;
                this->advance();
                EEobj->right = this->expression();
                result = EEobj;
            }
            else if(tokens::tokensArr[currentToken.type] == tokens::tokensArr[TOKENS::GREATERTHAN]){
                std::shared_ptr<OperatorNode> GTobj = std::make_shared<OperatorNode>();
                GTobj->nodeType = tokens::visitNodesArr[VISITNODES::OPNODEGREATERTHAN];
                GTobj->op_token = ">";
                GTobj->left = result;
                this->advance();
                GTobj->right = this->expression();
                result = GTobj;
            }
            else if(tokens::tokensArr[currentToken.type] == tokens::tokensArr[TOKENS::GREATERTHANOREQUALTO]){
                std::shared_ptr<OperatorNode> GTOETobj = std::make_shared<OperatorNode>();
                GTOETobj->nodeType = tokens::visitNodesArr[VISITNODES::OPNODEGREATERTHANOREQUALTO];
                GTOETobj->op_token = ">=";
                GTOETobj->left = result;
                this->advance();
                GTOETobj->right = this->expression();
                result = GTOETobj;
            }
            else if(tokens::tokensArr[currentToken.type] == tokens::tokensArr[TOKENS::LESSTHAN]){
                std::shared_ptr<OperatorNode> LTobj = std::make_shared<OperatorNode>();
                LTobj->nodeType = tokens::visitNodesArr[VISITNODES::OPNODELESSTHAN];
                LTobj->op_token = "<";
                LTobj->left = result;
                this->advance();
                LTobj->right = this->expression();
                result = LTobj;
            }
            else if(tokens::tokensArr[currentToken.type] == tokens::tokensArr[TOKENS::LESSTHANOREQUALTO]){
                std::shared_ptr<OperatorNode> LTOETobj = std::make_shared<OperatorNode>();
                LTOETobj->nodeType = tokens::visitNodesArr[VISITNODES::OPNODELESSTHANOREQUALTO];
                LTOETobj->op_token = "<=";
                LTOETobj->left = result;
                this->advance();
                LTOETobj->right = this->expression();
                result = LTOETobj;
            }
            else if(tokens::tokensArr[currentToken.type] == tokens::tokensArr[TOKENS::NOTEQUALTO]){
                std::shared_ptr<OperatorNode> NETTobj = std::make_shared<OperatorNode>();
                NETTobj->nodeType = tokens::visitNodesArr[VISITNODES::OPNODENOTEQUALTO];
                NETTobj->op_token = "!=";
                NETTobj->left = result;
                this->advance();
                NETTobj->right = this->expression();
                result = NETTobj;
            }
    }
    return result;
}

std::shared_ptr<tokenNode> parser::expression(){
    std::shared_ptr<tokenNode> result = this->term();

    while((this->current_index - 1 < tokensVect.size()) && 
    (tokens::tokensArr[this->currentToken.type] == tokens::tokensArr[TOKENS::PLUS]
     || tokens::tokensArr[this->currentToken.type] == tokens::tokensArr[TOKENS::MINUS])){

        if(tokens::tokensArr[currentToken.type] == tokens::tokensArr[TOKENS::PLUS]){
            std::shared_ptr<OperatorNode> addobj = std::make_shared<OperatorNode>();
            addobj->nodeType = tokens::visitNodesArr[VISITNODES::OPNODEPLUS];
            addobj->op_token = "+";
            addobj->left = result;
            this->advance();
            addobj->right = this->term();
            result = addobj;
        }
        else if(tokens::tokensArr[currentToken.type] == tokens::tokensArr[TOKENS::MINUS]){
            std::shared_ptr<OperatorNode> subtobj = std::make_shared<OperatorNode>();
            subtobj->nodeType = tokens::visitNodesArr[VISITNODES::OPNODEMINUS];
            subtobj->op_token = "-";
            subtobj->left = result;
            this->advance();
            subtobj->right = this->term();
            result = subtobj;
        }
    }

    return result;
}

std::shared_ptr<tokenNode> parser::term(){
    std::shared_ptr<tokenNode> result = this->factor();

    while((this->current_index - 1 < tokensVect.size()) && 
    (tokens::tokensArr[this->currentToken.type] == tokens::tokensArr[TOKENS::DIVIDE]
     || tokens::tokensArr[this->currentToken.type] == tokens::tokensArr[TOKENS::MULTIPLY]
     || tokens::tokensArr[this->currentToken.type] == tokens::tokensArr[TOKENS::POWER] 
     || tokens::tokensArr[this->currentToken.type] == tokens::tokensArr[TOKENS::MODULUS])){

        if(tokens::tokensArr[this->currentToken.type] == tokens::tokensArr[TOKENS::POWER]){
            std::shared_ptr<OperatorNode> powertobj = std::make_shared<OperatorNode>();
            powertobj->nodeType = tokens::visitNodesArr[VISITNODES::POWEROPNODE];
            powertobj->op_token = "^";
            powertobj->left = result;
            this->advance();
            powertobj->right = this->factor();
            result = powertobj;
        }
        else if(tokens::tokensArr[this->currentToken.type] == tokens::tokensArr[TOKENS::DIVIDE]){
            std::shared_ptr<OperatorNode> divtobj = std::make_shared<OperatorNode>();
            divtobj->nodeType = tokens::visitNodesArr[VISITNODES::OPNODEDIVIDE];
            divtobj->op_token = "/";
            divtobj->left = result;
            this->advance();
            divtobj->right = this->factor();
            result = divtobj;
        }
        else if(tokens::tokensArr[this->currentToken.type] == tokens::tokensArr[TOKENS::MULTIPLY]){
            std::shared_ptr<OperatorNode> multobj = std::make_shared<OperatorNode>();
            multobj->nodeType = tokens::visitNodesArr[VISITNODES::OPNODEMULTIPLY];
            multobj->op_token = "*";
            multobj->left = result;
            this->advance();
            multobj->right = this->factor();
            result = multobj;
        }
        else if(tokens::tokensArr[this->currentToken.type] == tokens::tokensArr[TOKENS::MODULUS]){
            std::shared_ptr<OperatorNode> modtobj = std::make_shared<OperatorNode>();
            modtobj->nodeType = tokens::visitNodesArr[VISITNODES::OPNODEMODULUS];
            modtobj->op_token = "%";
            modtobj->left = result;
            this->advance();
            modtobj->right = this->factor();
            result = modtobj;
        }
    }

    return result;
}

std::shared_ptr<tokenNode> parser::factor(){
    token tokenobj = this->currentToken;

    if(tokenobj.value == "EOF"){
        Exceptions newExc(EXCEPTIONS_MSG::EOF__INCOMPLETE__PROGRAM, this->filePath, this->lnNum, this->current_index, "");
        throw newExc;
    }

    if(tokens::tokensArr[tokenobj.type] == tokens::tokensArr[TOKENS::NUMBER]){
        
        if(this->datatype == parser::datatypeARR[STATEMENT_DATATYPE::NULL_STATEMENT_DATATYPE])
            this->datatype = parser::datatypeARR[STATEMENT_DATATYPE::NUMBER_DT];
        else if(this->datatype == parser::datatypeARR[STATEMENT_DATATYPE::WORD_DT]){
            Exceptions newExc(EXCEPTIONS_MSG::MIXING_DATA_TYPES, this->filePath, this->lnNum, this->current_index, this->currentToken.value);
            throw newExc;
        }

        this->advance();
        std::shared_ptr<NumberNode> number = std::make_shared<NumberNode>();
        number->nodeType = tokens::visitNodesArr[VISITNODES::NUMBERNODE];
        number->value = std::stod(tokenobj.value);
        return number;
    }
    else if(tokens::tokensArr[tokenobj.type] == tokens::tokensArr[TOKENS::STRING]){
        if(this->datatype == parser::datatypeARR[STATEMENT_DATATYPE::NULL_STATEMENT_DATATYPE])
        this->datatype = parser::datatypeARR[STATEMENT_DATATYPE::WORD_DT];
        else if(this->datatype == parser::datatypeARR[STATEMENT_DATATYPE::NUMBER_DT]){
            Exceptions newExc(EXCEPTIONS_MSG::MIXING_DATA_TYPES, this->filePath, this->lnNum, this->current_index, this->currentToken.value);
            throw newExc;
        }

        this->advance();
        std::shared_ptr<StringNode> word = std::make_shared<StringNode>();
        word->nodeType = tokens::visitNodesArr[VISITNODES::STRINGNODE];
        word->stringValue = tokenobj.value;
        return word;
    }
    else if(tokens::tokensArr[tokenobj.type] == tokens::tokensArr[TOKENS::IDENTIFIER]){
        
        this->advance();
        if(this->isReassigningVariable == false &&
        (tokens::tokensArr[this->currentToken.type] == tokens::tokensArr[TOKENS::EQUALS]
        || tokens::tokensArr[this->currentToken.type] == tokens::tokensArr[TOKENS::PLUSEQUALS]
        || tokens::tokensArr[this->currentToken.type] == tokens::tokensArr[TOKENS::MINUSEQUALS]
        || tokens::tokensArr[this->currentToken.type] == tokens::tokensArr[TOKENS::DIVIDEEQUALS]
        || tokens::tokensArr[this->currentToken.type] == tokens::tokensArr[TOKENS::MULTIPLYEQUALS]
        || tokens::tokensArr[this->currentToken.type] == tokens::tokensArr[TOKENS::MODULUSEQUALS]
        || tokens::tokensArr[this->currentToken.type] == tokens::tokensArr[TOKENS::POWEREQUALS])){

            this->isReassigningVariable = true;
            std::string variablename = tokenobj.value;
            this->current_var_name = variablename;
            std::string appendType = this->determineAppendType(this->currentToken.type);

            if(VariableNode::alreadyExistingVariable(variablename, tokens::visitNodesArr[VISITNODES::NUMBERVARNODE])){
                this->dataType = tokens::visitNodesArr[VISITNODES::NUMBERVARNODE];
                this->datatype = parser::datatypeARR[STATEMENT_DATATYPE::NUMBER_DT];
            }
            else if(VariableNode::alreadyExistingVariable(variablename, tokens::visitNodesArr[VISITNODES::STRINGVARNODE])){
                this->dataType = tokens::visitNodesArr[VISITNODES::STRINGVARNODE];
                this->datatype = parser::datatypeARR[STATEMENT_DATATYPE::WORD_DT];
            }
            else{
                Exceptions newExc(EXCEPTIONS_MSG::VARIABLE_NOTFOUND, this->filePath, this->lnNum, this->current_index, variablename);
                    throw newExc;
            }

            this->advance();
            VariableNode::reassignExistingVariable(this->OR_logical_operator_expression(), variablename, this->dataType, appendType);
            std::shared_ptr<VariableNode> existingVariable = VariableNode::getThisVariableobject(variablename, this->dataType);
            existingVariable->appendType = appendType;
            this->isReassigningVariable = false;
            return existingVariable;
        }
        else if(VariableNode::alreadyExistingVariable(tokenobj.value, this->dataType)){
            std::shared_ptr<VariableNode> existingVariable = VariableNode::getThisVariableobject(tokenobj.value, this->dataType);
            
            if(existingVariable == nullptr){
                Exceptions newExc(EXCEPTIONS_MSG::NULLPTREXCEPTION, this->filePath, this->lnNum, this->current_index, tokenobj.value);
                throw newExc;
            }
            
            if(existingVariable->varName == current_var_name){
                Exceptions newExc(EXCEPTIONS_MSG::INCORRECT_APPENDING, this->filePath, this->lnNum, this->current_index,current_var_name);
                throw newExc;
            }
            if(existingVariable->assignedData == nullptr){
                Exceptions newExc(EXCEPTIONS_MSG::NULLVARIABLE, this->filePath, this->lnNum, this->current_index, existingVariable->varName);
                throw newExc;
            }

            return existingVariable;
        }
        else if((this->datatype == parser::datatypeARR[STATEMENT_DATATYPE::NUMBER_DT] && 
            VariableNode::alreadyExistingVariable(tokenobj.value, tokens::visitNodesArr[VISITNODES::STRINGVARNODE]))
        || (this->datatype == parser::datatypeARR[STATEMENT_DATATYPE::WORD_DT] && 
            VariableNode::alreadyExistingVariable(tokenobj.value, tokens::visitNodesArr[VISITNODES::NUMBERVARNODE]))){
            
            Exceptions newExc(EXCEPTIONS_MSG::MIXING_DATA_TYPES, this->filePath, this->lnNum, this->current_index, this->currentToken.value);
            throw newExc;
        }
        else{//if(this->dataType == parser::default_DT && this->datatype == "null"){
            std::shared_ptr<VariableNode> existingVariable = VariableNode::getThisVariableobject(tokenobj.value, tokens::visitNodesArr[VISITNODES::STRINGVARNODE]);
            this->datatype = parser::datatypeARR[STATEMENT_DATATYPE::WORD_DT];
            if(existingVariable == nullptr){
                existingVariable = VariableNode::getThisVariableobject(tokenobj.value, tokens::visitNodesArr[VISITNODES::NUMBERVARNODE]);
                this->datatype = parser::datatypeARR[STATEMENT_DATATYPE::NUMBER_DT];
                if(existingVariable == nullptr){
                    Exceptions newExc(EXCEPTIONS_MSG::VARIABLE_NOTFOUND, this->filePath, this->lnNum, this->current_index, tokenobj.value );
                    throw newExc;
                }
            }

            if(existingVariable->varName == current_var_name){
                Exceptions newExc(EXCEPTIONS_MSG::INCORRECT_APPENDING, this->filePath, this->lnNum, this->current_index, current_var_name);
                throw newExc;
            }
            if(existingVariable->assignedData == nullptr){
                Exceptions newExc(EXCEPTIONS_MSG::NULLVARIABLE, this->filePath, this->lnNum, this->current_index, existingVariable->varName);
                throw newExc;
            }

            return existingVariable;
        }
    }
    else if(tokens::tokensArr[this->currentToken.type] == tokens::tokensArr[TOKENS::KEYWORD]
    && this->currentToken.value == tokens::KEYWORDS[KEYWRODSTYPE::FUNCTION__CALL]
    && !this->isAttaching__FuncArg){
        Exceptions newExc("Functions Are not yet supported");
        throw newExc;
        //this->isAttaching__FuncArg = true;
        //return this->attachFunctionArguments();
    }
    else if(tokens::tokensArr[tokenobj.type] == tokens::tokensArr[TOKENS::PLUS]){
        this->advance();
        std::shared_ptr<tokenNode> result = this->factor();
        std::shared_ptr<NumberNode> number = std::dynamic_pointer_cast<NumberNode>(result);
        std::shared_ptr<OperatorNode> operatorNode = std::dynamic_pointer_cast<OperatorNode>(result);

        return this->getCorrectUnaryType(number, operatorNode, "+", result->nodeType);
    }
    else if(tokens::tokensArr[tokenobj.type] == tokens::tokensArr[TOKENS::MINUS]){
        this->advance();
        std::shared_ptr<tokenNode> result = this->factor();
        std::shared_ptr<NumberNode> number = std::dynamic_pointer_cast<NumberNode>(result);
        std::shared_ptr<OperatorNode> operatorNode = std::dynamic_pointer_cast<OperatorNode>(result);

        return this->getCorrectUnaryType(number, operatorNode, "-", result->nodeType);
    }
    else if(tokens::tokensArr[tokenobj.type] == tokens::tokensArr[TOKENS::NOT]){
        this->advance();
        std::shared_ptr<tokenNode> result = this->factor();
        std::shared_ptr<OperatorNode> operatorNode = std::dynamic_pointer_cast<OperatorNode>(result);
        if(operatorNode != nullptr){
            std::shared_ptr<OperatorNode> notexpr = std::make_shared<OperatorNode>();
            notexpr->nodeType = tokens::visitNodesArr[VISITNODES::OPNODENOT];
            notexpr->unary_op_token = "!";
            notexpr->isUnaryOperator = true;
            notexpr->unaryopdata = operatorNode;
            return notexpr;
        }
        else{
            Exceptions newExc(EXCEPTIONS_MSG::NOT_ALLOWED_CHARACTER, this->filePath, this->lnNum, this->current_index, result->nodeType);
            throw newExc;
        }
    }
    else if(tokens::tokensArr[tokenobj.type] == tokens::tokensArr[TOKENS::LPAREN]){
        this->advance();
        std::shared_ptr<tokenNode> result = this->OR_logical_operator_expression();
        if(tokens::tokensArr[this->currentToken.type] != tokens::tokensArr[TOKENS::RPAREN]){
            Exceptions newExc(EXCEPTIONS_MSG::MISSING_RPAREN, this->filePath, this->lnNum, this->current_index, this->currentToken.value);
            throw newExc;
        }
        
        this->advance();
        return result;
    }
    else{
        Exceptions newExc(EXCEPTIONS_MSG::NO_MATCHINGTYPE, this->filePath, this->lnNum, this->current_index, this->currentToken.value);
            throw newExc;
    }
}


/*helper functions*/



std::shared_ptr<tokenNode> parser::getCorrectUnaryType(std::shared_ptr<NumberNode>& numbernode, const std::shared_ptr<OperatorNode>& operatornode, const std::string& operationtype, const std::string& nodetype){
    if(numbernode != nullptr){
        if(operationtype == "+")numbernode->nodeType = tokens::visitNodesArr[VISITNODES::PLUSUNARYOPNODE];
        else numbernode->nodeType = tokens::visitNodesArr[VISITNODES::MINUSUNARYOPNODE];
        
        numbernode->unary_op_token = operationtype;
        numbernode->isUnaryOperator = true;
        return numbernode;
    }
    else if(operatornode != nullptr){
        std::shared_ptr<NumberNode> numberexpr = std::make_shared<NumberNode>();
        
        if(operationtype == "+")numbernode->nodeType = tokens::visitNodesArr[VISITNODES::PLUSUNARYOPNODE];
        else numbernode->nodeType = tokens::visitNodesArr[VISITNODES::MINUSUNARYOPNODE];

        numberexpr->unary_op_token = operationtype;
        numberexpr->isUnaryOperator = true;
        numberexpr->unaryopdata = operatornode;
        return numberexpr;
    }
    else{
        Exceptions newExc(EXCEPTIONS_MSG::NULLPTREXC, this->filePath, this->lnNum, this->current_index, nodetype);
        throw newExc;
    }
}

std::string parser::determineAppendType(const int& tokentypenode){
    if(tokens::tokensArr[tokentypenode] == tokens::tokensArr[TOKENS::PLUSEQUALS]){
        return tokens::visitNodesArr[VISITNODES::OPNODEPLUSEQUALS];
    }
    else if(tokens::tokensArr[tokentypenode] == tokens::tokensArr[TOKENS::MINUSEQUALS]){
        return tokens::visitNodesArr[VISITNODES::OPNODEMINUSEQUALS];
    }
    else if(tokens::tokensArr[tokentypenode] == tokens::tokensArr[TOKENS::DIVIDEEQUALS]){
        return tokens::visitNodesArr[VISITNODES::OPNODEDIVIDEEQUALS];
    }
    else if(tokens::tokensArr[tokentypenode] == tokens::tokensArr[TOKENS::MULTIPLYEQUALS]){
        return tokens::visitNodesArr[VISITNODES::OPNODEMULTIPLYEQUALS];
    }
    else if(tokens::tokensArr[tokentypenode] == tokens::tokensArr[TOKENS::MODULUSEQUALS]){
        return tokens::visitNodesArr[VISITNODES::OPNODEMODULUSEQUALS];
    }
    else if(tokens::tokensArr[tokentypenode] == tokens::tokensArr[TOKENS::POWEREQUALS]){
        return tokens::visitNodesArr[VISITNODES::OPNODEPOWEREQUALS];
    }
    else return "null";
}

std::string parser::continueReadingData(){
    this->advance();

    if(tokens::tokensArr[this->currentToken.type] != tokens::tokensArr[TOKENS::IDENTIFIER]){
        Exceptions newExc(EXCEPTIONS_MSG::MISSING_VARNAME, this->filePath, this->lnNum, this->current_index, this->datatype);
        throw newExc;
    }

    std::string variablename = this->currentToken.value;
    this->advance();

    if(tokens::tokensArr[this->currentToken.type] != tokens::tokensArr[TOKENS::EQUALS]){
        Exceptions newExc(EXCEPTIONS_MSG::MISSING_ASSINGMENT_OP, this->filePath, this->lnNum, this->current_index, this->currentToken.value);
        throw newExc;
    }

    if(VariableNode::alreadyExistingVariable(variablename, tokens::visitNodesArr[VISITNODES::STRINGVARNODE])
    || VariableNode::alreadyExistingVariable(variablename, tokens::KEYWORDS[KEYWRODSTYPE::NUMBERKEY])){
        Exceptions newExc(EXCEPTIONS_MSG::VAR_ALREADY_EXISTS, this->filePath, this->lnNum, this->current_index, this->currentToken.value);
        throw newExc;
    }

    return variablename;
}

std::shared_ptr<tokenNode> parser::createVariable(const std::string& var_DT){
    std::string variablename = this->continueReadingData();
    this->advance();
    std::shared_ptr<VariableNode> newVariable = std::make_shared<VariableNode>();
    newVariable->assignedData = this->OR_logical_operator_expression();
    newVariable->nodeType = var_DT;
    newVariable->varName = variablename;
    VariableNode::pushIntoVector(newVariable, newVariable->nodeType);
    return newVariable;
}

std::shared_ptr<tokenNode> parser::getNUMBERVARIABLE(){
    this->datatype = parser::datatypeARR[STATEMENT_DATATYPE::NUMBER_DT];
    return this->createVariable(tokens::visitNodesArr[VISITNODES::NUMBERVARNODE]);
}

std::shared_ptr<tokenNode> parser::getWORDVARIABLE(){
    this->datatype = parser::datatypeARR[STATEMENT_DATATYPE::WORD_DT];
    return this->createVariable(tokens::visitNodesArr[VISITNODES::STRINGVARNODE]);
}

std::shared_ptr<tokenNode> parser::getPRINTDATA(){
    std::string displayType = this->currentToken.value;
    this->advance();
    if(tokens::tokensArr[this->currentToken.type] != tokens::tokensArr[TOKENS::LPAREN]){
        Exceptions newExc(EXCEPTIONS_MSG::MISSING_LPAREN_builtin, this->filePath, this->lnNum, this->current_index, tokens::tokensArr[this->currentToken.type]);
        throw newExc;
    }

    this->advance();
    std::shared_ptr<tokenNode> result = this->OR_logical_operator_expression();
    if(tokens::tokensArr[this->currentToken.type] != tokens::tokensArr[TOKENS::RPAREN]){
        Exceptions newExc(EXCEPTIONS_MSG::MISSING_RPAREN_builtin, this->filePath, this->lnNum, this->current_index, tokens::tokensArr[this->currentToken.type]);
        throw newExc;
    }
    
    this->advance();

    std::shared_ptr<builtinNode> func = std::make_shared<builtinNode>();
    func->assigneddata = result;
    func->built_in_name = displayType;
    func->nodeType = tokens::visitNodesArr[VISITNODES::BUITINFUNCTION];
    return func;
}

std::shared_ptr<tokenNode> parser::createifstatements(){
    this->dataType = parser::default_DT;
    this->datatype = parser::datatypeARR[STATEMENT_DATATYPE::NULL_STATEMENT_DATATYPE];
    std::shared_ptr<ifNode> newIFstatement = std::make_shared<ifNode>();
    newIFstatement->conditionaltype = "if";
    newIFstatement->nodeType = tokens::visitNodesArr[VISITNODES::IFSTATEMENTNODE];

    this->advance();
    newIFstatement->condition = this->OR_logical_operator_expression();
    newIFstatement->datatype = this->datatype;
    this->dataType = parser::default_DT;
    this->datatype = parser::datatypeARR[STATEMENT_DATATYPE::NULL_STATEMENT_DATATYPE];

    if(tokens::tokensArr[this->currentToken.type] != tokens::tokensArr[TOKENS::BEGINLOCALSCOPE]){
        Exceptions newExc(EXCEPTIONS_MSG::OPENINGSCOPE, this->filePath, this->lnNum, this->current_index, tokens::tokensArr[this->currentToken.type]);
        throw newExc;
    }
    
    this->advance();
    while(tokens::tokensArr[this->currentToken.type] == tokens::tokensArr[TOKENS::KEYWORD]
    && this->currentToken.value == tokens::KEYWORDS[KEYWRODSTYPE::THEN] 
    && tokens::tokensArr[this->currentToken.type] != tokens::tokensArr[TOKENS::ENDLOCALSCOPE]){
        //curently pointing to thenptr
        this->advance();
        //curently pointing to first token after thenptr
        expressionData newexpr;
        newexpr.expression = this->controlflow();
        newexpr.datatype = this->datatype;
        newIFstatement->statementsvect.push_back(newexpr);
        this->dataType = parser::default_DT;
        this->datatype = parser::datatypeARR[STATEMENT_DATATYPE::NULL_STATEMENT_DATATYPE];
        this->current_var_name = "";
        //curently pointing to last token on current thenptr line
        //this->advance();
        //curently pointing thenptr or endlocalscope
    }

    //currently pointing to endlocalscope
    //std::cout << this->currentToken.type << this->currentToken.value << std::endl;
    if(tokens::tokensArr[this->currentToken.type] != tokens::tokensArr[TOKENS::ENDLOCALSCOPE]){
        Exceptions newExc(EXCEPTIONS_MSG::CLOSINGSCOPE, this->filePath, this->lnNum, this->current_index, tokens::tokensArr[this->currentToken.type]);
        throw newExc;
    }
    this->advance();

    //currently pointing to EOF or pointing to elseif or else statement
    if(tokens::tokensArr[this->currentToken.type] == tokens::tokensArr[TOKENS::KEYWORD]
    && this->currentToken.value == tokens::KEYWORDS[KEYWRODSTYPE::ELSEIF]){

        newIFstatement->next__If__ElseIf__Else = this->create__elseifstatements();
    }
    
    if(tokens::tokensArr[this->currentToken.type] == tokens::tokensArr[TOKENS::KEYWORD]
    && this->currentToken.value == tokens::KEYWORDS[KEYWRODSTYPE::ELSE]){
        newIFstatement->appendNew__If__ElseIf__Else__statement(this->create__elsestatements());
    }

    newIFstatement->nodeType = tokens::visitNodesArr[VISITNODES::IFSTATEMENTNODE];
    this->dataType = parser::default_DT;
    this->datatype = parser::datatypeARR[STATEMENT_DATATYPE::NULL_STATEMENT_DATATYPE];
    return newIFstatement;
}

std::shared_ptr<tokenNode> parser::create__elseifstatements(){
    this->dataType = parser::default_DT;
    this->datatype = parser::datatypeARR[STATEMENT_DATATYPE::NULL_STATEMENT_DATATYPE];
    
    std::shared_ptr<ifNode> newELSEIFstatement = std::make_shared<ifNode>();
    newELSEIFstatement->nodeType = tokens::visitNodesArr[VISITNODES::ELSEIFSTATEMENTNODE];
    newELSEIFstatement->conditionaltype = "elseif";
    this->advance();
    newELSEIFstatement->condition = this->OR_logical_operator_expression();
    newELSEIFstatement->datatype = this->datatype;
    this->dataType = parser::default_DT;
    this->datatype = parser::datatypeARR[STATEMENT_DATATYPE::NULL_STATEMENT_DATATYPE];

    if(tokens::tokensArr[this->currentToken.type] != tokens::tokensArr[TOKENS::BEGINLOCALSCOPE]){
        Exceptions newExc(EXCEPTIONS_MSG::OPENINGSCOPE, this->filePath, this->lnNum, this->current_index, tokens::tokensArr[this->currentToken.type]);
        throw newExc;
    }

    this->advance();
    while(tokens::tokensArr[this->currentToken.type] == tokens::tokensArr[TOKENS::KEYWORD]
    && this->currentToken.value == tokens::KEYWORDS[KEYWRODSTYPE::THEN] 
    && tokens::tokensArr[this->currentToken.type] != tokens::tokensArr[TOKENS::ENDLOCALSCOPE]){
        //curently pointing to thenptr
        this->advance();
        //curently pointing to first token after thenptr
        expressionData newexpr;
        newexpr.expression = this->controlflow();
        newexpr.datatype = this->datatype;
        newELSEIFstatement->statementsvect.push_back(newexpr);
        this->dataType = parser::default_DT;
        this->datatype = parser::datatypeARR[STATEMENT_DATATYPE::NULL_STATEMENT_DATATYPE];
        this->current_var_name = "";
        //curently pointing to last token on current thenptr line
        //this->advance();
        //curently pointing thenptr or endlocalscope
    }

    //currently pointing to endlocalscope
    if(tokens::tokensArr[this->currentToken.type] != tokens::tokensArr[TOKENS::ENDLOCALSCOPE]){
        Exceptions newExc(EXCEPTIONS_MSG::CLOSINGSCOPE, this->filePath, this->lnNum, this->current_index, tokens::tokensArr[this->currentToken.type]);
        throw newExc;
    }
    this->advance();

    //currently pointing to EOF or pointing to elseif or else statement
    while(tokens::tokensArr[this->currentToken.type] == tokens::tokensArr[TOKENS::KEYWORD]
    && this->currentToken.value == tokens::KEYWORDS[KEYWRODSTYPE::ELSEIF]){

        std::shared_ptr<ifNode> newELSEIFstatementobj = std::make_shared<ifNode>();
        newELSEIFstatementobj->nodeType = tokens::visitNodesArr[VISITNODES::ELSEIFSTATEMENTNODE];
        newELSEIFstatementobj->conditionaltype = "elseif";
        this->advance();
        newELSEIFstatementobj->condition = this->OR_logical_operator_expression();
        newELSEIFstatementobj->datatype = this->datatype;
        this->dataType = parser::default_DT;
        this->datatype = parser::datatypeARR[STATEMENT_DATATYPE::NULL_STATEMENT_DATATYPE];

        if(tokens::tokensArr[this->currentToken.type] != tokens::tokensArr[TOKENS::BEGINLOCALSCOPE]){
            Exceptions newExc(EXCEPTIONS_MSG::OPENINGSCOPE, this->filePath, this->lnNum, this->current_index, tokens::tokensArr[this->currentToken.type]);
            throw newExc;
        }

        this->advance();
        while(tokens::tokensArr[this->currentToken.type] == tokens::tokensArr[TOKENS::KEYWORD]
        && this->currentToken.value == tokens::KEYWORDS[KEYWRODSTYPE::THEN] 
        && tokens::tokensArr[this->currentToken.type] != tokens::tokensArr[TOKENS::ENDLOCALSCOPE]){
            //curently pointing to thenptr
            this->advance();
            //curently pointing to first token after thenptr
            expressionData newexpr;
            newexpr.expression = this->controlflow();
            newexpr.datatype = this->datatype;
            newELSEIFstatementobj->statementsvect.push_back(newexpr);
            this->dataType = parser::default_DT;
            this->datatype = parser::datatypeARR[STATEMENT_DATATYPE::NULL_STATEMENT_DATATYPE];
            this->current_var_name = "";
            //curently pointing to last token on current thenptr line
            //this->advance();
            //curently pointing to thenptr or endlocalscope
        }

        //pointing to end of local scope
        if(tokens::tokensArr[this->currentToken.type] != tokens::tokensArr[TOKENS::ENDLOCALSCOPE]){
            Exceptions newExc(EXCEPTIONS_MSG::CLOSINGSCOPE, this->filePath, this->lnNum, this->current_index, tokens::tokensArr[this->currentToken.type]);
            throw newExc;
        }
        this->advance();

        newELSEIFstatement->appendNew__If__ElseIf__Else__statement(newELSEIFstatementobj);
    }
    
    this->dataType = parser::default_DT;
    this->datatype = parser::datatypeARR[STATEMENT_DATATYPE::NULL_STATEMENT_DATATYPE];
    return newELSEIFstatement;
}

std::shared_ptr<ifNode> parser::create__elsestatements(){
    std::shared_ptr<ifNode> newELSEstatement = std::make_shared<ifNode>();
    newELSEstatement->nodeType = tokens::visitNodesArr[VISITNODES::ELSESTATEMENT];
    newELSEstatement->conditionaltype = "else";

    this->advance();
    this->dataType = parser::default_DT;
    this->datatype = parser::datatypeARR[STATEMENT_DATATYPE::NULL_STATEMENT_DATATYPE];

    if(tokens::tokensArr[this->currentToken.type] != tokens::tokensArr[TOKENS::BEGINLOCALSCOPE]){
        Exceptions newExc(EXCEPTIONS_MSG::OPENINGSCOPE, this->filePath, this->lnNum, this->current_index, tokens::tokensArr[this->currentToken.type]);
        throw newExc;
    }

    this->advance();
    while(tokens::tokensArr[this->currentToken.type] == tokens::tokensArr[TOKENS::KEYWORD]
    && this->currentToken.value == tokens::KEYWORDS[KEYWRODSTYPE::THEN] 
    && tokens::tokensArr[this->currentToken.type] != tokens::tokensArr[TOKENS::ENDLOCALSCOPE]){
        //curently pointing to thenptr
        this->advance();
        //curently pointing to first token after thenptr
        expressionData newexpr;
        newexpr.expression = this->controlflow();
        newexpr.datatype = this->datatype;
        newELSEstatement->statementsvect.push_back(newexpr);
        this->dataType = parser::default_DT;
        this->datatype = parser::datatypeARR[STATEMENT_DATATYPE::NULL_STATEMENT_DATATYPE];
        this->current_var_name = "";
        //curently pointing to last token on current thenptr line
        //this->advance();
        //curently pointing thenptr or endlocalscope
    }

    //currently pointing to endlocalscope
    if(tokens::tokensArr[this->currentToken.type] != tokens::tokensArr[TOKENS::ENDLOCALSCOPE]){
        Exceptions newExc(EXCEPTIONS_MSG::CLOSINGSCOPE, this->filePath, this->lnNum, this->current_index, tokens::tokensArr[this->currentToken.type]);
        throw newExc;
    }
    this->advance();
    //currently pointing to EOF
    this->dataType = parser::default_DT;
    this->datatype = parser::datatypeARR[STATEMENT_DATATYPE::NULL_STATEMENT_DATATYPE];
    return newELSEstatement;
}

std::shared_ptr<tokenNode> parser::create_whilestatements(){
    this->dataType = parser::default_DT;
    this->datatype = parser::datatypeARR[STATEMENT_DATATYPE::NULL_STATEMENT_DATATYPE];
    
    std::shared_ptr<whileNode> newwhilestatement = std::make_shared<whileNode>();
    newwhilestatement->nodeType = tokens::visitNodesArr[VISITNODES::WHILESTATEMENT];
    this->advance();
    newwhilestatement->condition = this->OR_logical_operator_expression();
    newwhilestatement->datatype = this->datatype;
    this->dataType = parser::default_DT;
    this->datatype = parser::datatypeARR[STATEMENT_DATATYPE::NULL_STATEMENT_DATATYPE];

    if(tokens::tokensArr[this->currentToken.type] != tokens::tokensArr[TOKENS::BEGINLOCALSCOPE]){
        Exceptions newExc(EXCEPTIONS_MSG::OPENINGSCOPE, this->filePath, this->lnNum, this->current_index, tokens::tokensArr[this->currentToken.type]);
        throw newExc;
    }

    this->advance();
    while(tokens::tokensArr[this->currentToken.type] == tokens::tokensArr[TOKENS::KEYWORD]
    && this->currentToken.value == tokens::KEYWORDS[KEYWRODSTYPE::THEN] 
    && tokens::tokensArr[this->currentToken.type] != tokens::tokensArr[TOKENS::ENDLOCALSCOPE]){
        //curently pointing to thenptr
        this->advance();
        //curently pointing to first token after thenptr
        expressionData newexpr;
        newexpr.expression = this->controlflow();
        newexpr.datatype = this->datatype;
        newwhilestatement->statementsvect.push_back(newexpr);
        this->dataType = parser::default_DT;
        this->datatype = parser::datatypeARR[STATEMENT_DATATYPE::NULL_STATEMENT_DATATYPE];
        this->current_var_name = "";
        //curently pointing to last token on current thenptr line
        //this->advance();
        //curently pointing thenptr or endlocalscope
    }

    //currently pointing to endlocalscope
    if(tokens::tokensArr[this->currentToken.type] != tokens::tokensArr[TOKENS::ENDLOCALSCOPE]){
        Exceptions newExc(EXCEPTIONS_MSG::CLOSINGSCOPE, this->filePath, this->lnNum, this->current_index, tokens::tokensArr[this->currentToken.type]);
        throw newExc;
    }
    this->advance();
    //currently pointing to EOF
    this->dataType = parser::default_DT;
    this->datatype = parser::datatypeARR[STATEMENT_DATATYPE::NULL_STATEMENT_DATATYPE];
    return newwhilestatement;
}

std::shared_ptr<tokenNode> parser::create__forloops(){
    std::shared_ptr<forNode> newforstatement = std::make_shared<forNode>();
    newforstatement->nodeType = tokens::visitNodesArr[VISITNODES::FORSTATEMENT];
    this->advance();
    //curently pointing to left parenthesis
    if(tokens::tokensArr[this->currentToken.type] != tokens::tokensArr[TOKENS::LPAREN]){
        Exceptions newExc(EXCEPTIONS_MSG::MISSING_LPAREN_forloop, this->filePath, this->lnNum, this->current_index, tokens::tokensArr[this->currentToken.type]);
        throw newExc;
    }

    this->dataType = parser::default_DT;
    this->datatype = parser::datatypeARR[STATEMENT_DATATYPE::NULL_STATEMENT_DATATYPE];
    //curently pointing to variable declaration
    this->advance();
    if(tokens::tokensArr[this->currentToken.type] == tokens::tokensArr[TOKENS::KEYWORD]){

        if(this->currentToken.value == tokens::KEYWORDS[KEYWRODSTYPE::NUMBERKEY]){
            newforstatement->declaration = this->getNUMBERVARIABLE();
            newforstatement->init_declaration = getNumberNode(newforstatement->declaration);
        }
        else if(tokens::tokensArr[this->currentToken.type] == tokens::tokensArr[TOKENS::IDENTIFIER]){
            newforstatement->declaration = this->factor();
            newforstatement->decl_Var_Exists = true;
        }
        else{
            Exceptions newExc(EXCEPTIONS_MSG::INCORRECT_FORLOOP, this->filePath, this->lnNum, this->current_index, tokens::tokensArr[this->currentToken.type]);
            throw newExc;
        }
    }
    else{
        Exceptions newExc(EXCEPTIONS_MSG::NO_FORLOOP_DECL, this->filePath, this->lnNum, this->current_index, tokens::tokensArr[this->currentToken.type]);
        throw newExc;
    }

    newforstatement->datatype = this->datatype;

    if(tokens::tokensArr[this->currentToken.type] != tokens::tokensArr[TOKENS::FORLOOPSEP]){
        Exceptions newExc(EXCEPTIONS_MSG::FORLOOP_SEP,  this->filePath, this->lnNum, this->current_index, tokens::tokensArr[this->currentToken.type]);
        throw newExc;
    }

    //curently pointing to ':'
    this->advance();
    //currently pointing to condition
    newforstatement->condition = this->OR_logical_operator_expression();

    //curently pointing to ':'
    this->advance();
    //currently pointing to iterator
    newforstatement->iteration = this->expression();
    if(tokens::tokensArr[this->currentToken.type] != tokens::tokensArr[TOKENS::RPAREN]){
        Exceptions newExc(EXCEPTIONS_MSG::MISSING_RPAREN_forloop, this->filePath, this->lnNum, this->current_index, tokens::tokensArr[this->currentToken.type]);
        throw newExc;
    }

    //curently pointing to ')'
    this->advance();
    //currently pointing to begin local scope or '{'
    if(tokens::tokensArr[this->currentToken.type] != tokens::tokensArr[TOKENS::BEGINLOCALSCOPE]){
        Exceptions newExc(EXCEPTIONS_MSG::OPENINGSCOPE, this->filePath, this->lnNum, this->current_index, tokens::tokensArr[this->currentToken.type]);
        throw newExc;
    }

    //currently pointing to first statement in local scope
    this->advance();
    this->current_var_name = "";
    while(tokens::tokensArr[this->currentToken.type] == tokens::tokensArr[TOKENS::KEYWORD]
    && this->currentToken.value == tokens::KEYWORDS[KEYWRODSTYPE::THEN] 
    && tokens::tokensArr[this->currentToken.type] != tokens::tokensArr[TOKENS::ENDLOCALSCOPE]){
        //curently pointing to then
        this->advance();
        //curently pointing to first token after then
        expressionData newexpr;
        newexpr.expression = this->controlflow();
        newexpr.datatype = this->datatype;
        newforstatement->statementsvect.push_back(newexpr);
        this->dataType = parser::default_DT;
        this->datatype = parser::datatypeARR[STATEMENT_DATATYPE::NULL_STATEMENT_DATATYPE];
        this->current_var_name = "";
        //curently pointing to last token on current then line
        //this->advance();
        //curently pointing then or endlocalscope
    }

    //currently pointing to endlocalscope
    if(tokens::tokensArr[this->currentToken.type] != tokens::tokensArr[TOKENS::ENDLOCALSCOPE]){
        Exceptions newExc(EXCEPTIONS_MSG::CLOSINGSCOPE, this->filePath, this->lnNum, this->current_index, tokens::tokensArr[this->currentToken.type]);
        throw newExc;
    }
    this->advance();
    //currently pointing to EOF
    this->dataType = parser::default_DT;
    this->datatype = parser::datatypeARR[STATEMENT_DATATYPE::NULL_STATEMENT_DATATYPE];
    return newforstatement;
}

std::shared_ptr<tokenNode> parser::getNumberNode(std::shared_ptr<tokenNode>& variablenode_data){
    std::shared_ptr<VariableNode> variable = std::dynamic_pointer_cast<VariableNode>(variablenode_data);

    if(variable == nullptr){
        Exceptions newExc(EXCEPTIONS_MSG::NULLPTREXCEPTION, this->filePath, this->lnNum, this->current_index, variablenode_data->__represent__());
        throw newExc;
    }

    std::shared_ptr<NumberNode> number = std::dynamic_pointer_cast<NumberNode>(variable->assignedData);
    if(number != nullptr)return number;

    std::shared_ptr<OperatorNode> operator_data = std::dynamic_pointer_cast<OperatorNode>(variable->assignedData);
    if(operator_data == nullptr){
        Exceptions newExc(EXCEPTIONS_MSG::NULLPTREXCEPTION, this->filePath, this->lnNum, this->current_index, variable->__represent__());
        throw newExc;
    }

    return operator_data;
}

std::shared_ptr<tokenNode> parser::create__functions(){
    std::shared_ptr<functionNode> func = std::make_shared<functionNode>();
    //curently pointing to "function"
    this->advance();
    //curently pointing to function name
    func->functionName = this->currentToken.value;
    
    this->advance();
    //curently pointing to left parenthesis
    if(tokens::tokensArr[this->currentToken.type] != tokens::tokensArr[TOKENS::LPAREN]){
        Exceptions newExc(EXCEPTIONS_MSG::MISSING_LPAREN_function, this->filePath, this->lnNum, this->current_index, tokens::tokensArr[this->currentToken.type]);
        throw newExc;
    }

    while(tokens::tokensArr[this->currentToken.type] != tokens::tokensArr[TOKENS::RPAREN]){
        this->advance();//pointing to data type

        if(func->functionArgsAmounts >= func->FUNC_ARG_MAX){
            Exceptions newExc(EXCEPTIONS_MSG::MAX_FUNC_ARG,  this->filePath, this->lnNum, func->FUNC_ARG_MAX, func->__represent__());
            throw newExc;
        }

        if(tokens::tokensArr[this->currentToken.type] != tokens::tokensArr[TOKENS::KEYWORD]){
            Exceptions newExc(EXCEPTIONS_MSG::MISSING_DATATYPE, this->filePath, this->lnNum, this->current_index, this->currentToken.value);
            throw newExc;
        }

        if(this->currentToken.value == tokens::KEYWORDS[KEYWRODSTYPE::NUMBERKEY]){
            expressionData numbervariable;
            numbervariable.expression = this->create_nullVariable(tokens::visitNodesArr[VISITNODES::NUMBERVARNODE]);
            numbervariable.datatype = "number";
            func->arguments.push_back(numbervariable);
            ++func->functionArgsAmounts;
        }
        else if(this->currentToken.value == tokens::KEYWORDS[KEYWRODSTYPE::STRINGKEY]){
            expressionData wordvariable;
            wordvariable.expression = this->create_nullVariable(tokens::visitNodesArr[VISITNODES::STRINGVARNODE]);
            wordvariable.datatype = "word";
            func->arguments.push_back(wordvariable);
            ++func->functionArgsAmounts;
        }
        else{
            Exceptions newExc(EXCEPTIONS_MSG::INCORRECT_FUNCTIONARG_TYPE, this->filePath, this->lnNum, this->current_index, this->currentToken.value);
            throw newExc;
        }
        
        //currently pointing to ','
        if(tokens::tokensArr[this->currentToken.type] != tokens::tokensArr[TOKENS::FUNCARGSEP]
        && tokens::tokensArr[this->currentToken.type] != tokens::tokensArr[TOKENS::RPAREN]){
            Exceptions newExc(EXCEPTIONS_MSG::MISSING_COMMA_SEP, this->filePath, this->lnNum, this->current_index, tokens::tokensArr[this->currentToken.type]);
            throw newExc;
        }
    
        this->advance();
        //currently pointing to next data type in arguments
    }

    this->dataType = parser::default_DT;
    this->datatype = parser::datatypeARR[STATEMENT_DATATYPE::NULL_STATEMENT_DATATYPE];
    //curently pointing to right parenthesis
    if(tokens::tokensArr[this->currentToken.type] != tokens::tokensArr[TOKENS::RPAREN]){
        Exceptions newExc(EXCEPTIONS_MSG::MISSING_RPAREN_function, this->filePath, this->lnNum, this->current_index, tokens::tokensArr[this->currentToken.type]);
        throw newExc;
    }
    this->advance();
    //currently pointing to begin local scope

    if(tokens::tokensArr[this->currentToken.type] != tokens::tokensArr[TOKENS::BEGINLOCALSCOPE]){
        Exceptions newExc(EXCEPTIONS_MSG::OPENINGSCOPE, this->filePath, this->lnNum, this->current_index, tokens::tokensArr[this->currentToken.type]);
        throw newExc;
    }

    this->advance();
    while(tokens::tokensArr[this->currentToken.type] == tokens::tokensArr[TOKENS::KEYWORD]
    && this->currentToken.value == tokens::KEYWORDS[KEYWRODSTYPE::THEN] 
    && tokens::tokensArr[this->currentToken.type] != tokens::tokensArr[TOKENS::ENDLOCALSCOPE]){
        //curently pointing to then
        this->advance();
        //curently pointing to first token after thenptr
        expressionData newexpr;
        newexpr.expression = this->controlflow();
        newexpr.datatype = this->datatype;
        func->statementsvect.push_back(newexpr);
        this->dataType = parser::default_DT;
        this->datatype = parser::datatypeARR[STATEMENT_DATATYPE::NULL_STATEMENT_DATATYPE];
        this->current_var_name = "";
        //curently pointing to last token on current thenptr line
        this->advance();
        //curently pointing thenptr or endlocalscope
    }

    //currently pointing to endlocalscope
    if(tokens::tokensArr[this->currentToken.type] != tokens::tokensArr[TOKENS::ENDLOCALSCOPE]){
        Exceptions newExc(EXCEPTIONS_MSG::CLOSINGSCOPE, this->filePath, this->lnNum, this->current_index, tokens::tokensArr[this->currentToken.type]);
        throw newExc;
    }
    this->advance();
    //currently pointing to EOF
    this->dataType = parser::default_DT;
    this->datatype = parser::datatypeARR[STATEMENT_DATATYPE::NULL_STATEMENT_DATATYPE];

    functionNode::pushIntoFuncVector(func);

    return func;
}

std::shared_ptr<tokenNode> parser::attachFunctionArguments(){
    //curently pointing to "callfunction"
    this->advance();
    //curently pointing to function name
    std::shared_ptr<functionNode> func = functionNode::getThisFunction(this->currentToken.value);
    
    this->advance();
    //curently pointing to left parenthesis
    if(tokens::tokensArr[this->currentToken.type] != tokens::tokensArr[TOKENS::LPAREN]){
        Exceptions newExc(EXCEPTIONS_MSG::MISSING_LPAREN_function, this->filePath, this->lnNum, this->current_index, tokens::tokensArr[this->currentToken.type]);
        throw newExc;
    }

    this->dataType = parser::default_DT;
    this->datatype = parser::datatypeARR[STATEMENT_DATATYPE::NULL_STATEMENT_DATATYPE];

    int arg_index = 0;
    //currently pointing to "("
    while(tokens::tokensArr[this->currentToken.type] != tokens::tokensArr[TOKENS::RPAREN]){
        this->advance();//pointing to data type

        func->attachArgAt(arg_index, this->factor());
        ++arg_index;
        this->dataType = parser::default_DT;
        this->datatype = parser::datatypeARR[STATEMENT_DATATYPE::NULL_STATEMENT_DATATYPE];

        //currently pointing to ','
        if(tokens::tokensArr[this->currentToken.type] != tokens::tokensArr[TOKENS::FUNCARGSEP]
        && tokens::tokensArr[this->currentToken.type] != tokens::tokensArr[TOKENS::RPAREN]){
            Exceptions newExc(EXCEPTIONS_MSG::MISSING_COMMA_SEP, this->filePath, this->lnNum, this->current_index, tokens::tokensArr[this->currentToken.type]);
            throw newExc;
        }
    }

    //currently pointing to ")"
    if(tokens::tokensArr[this->currentToken.type] != tokens::tokensArr[TOKENS::RPAREN]){
        Exceptions newExc(EXCEPTIONS_MSG::MISSING_RPAREN_function, this->filePath, this->lnNum, this->current_index, tokens::tokensArr[this->currentToken.type]);
        throw newExc;
    }

    this->isAttaching__FuncArg = false;
    return func;
}

std::shared_ptr<tokenNode> parser::create_nullVariable(const std::string& variabletype){
    if(this->currentToken.value != tokens::KEYWORDS[KEYWRODSTYPE::NUMBERKEY]
    && this->currentToken.value != tokens::KEYWORDS[KEYWRODSTYPE::STRINGKEY]){
        Exceptions newExc(EXCEPTIONS_MSG::UNSUPPORTED_TOKEN_IN_PARSER, this->filePath, this->lnNum, this->current_index, this->currentToken.value);
        throw newExc;
    }

    this->advance();

    if(tokens::tokensArr[this->currentToken.type] != tokens::tokensArr[TOKENS::IDENTIFIER]){
        Exceptions newExc(EXCEPTIONS_MSG::MISSING_VARNAME, this->filePath, this->lnNum, this->current_index, this->datatype);
        throw newExc;
    }

    std::string variablename = this->currentToken.value;
    std::shared_ptr<VariableNode> newVariable = std::make_shared<VariableNode>();
    newVariable->nodeType = variabletype;
    newVariable->varName = variablename;
    VariableNode::pushIntoVector(newVariable, newVariable->nodeType);
    this->advance();//currently pointing to comma or right parentheisis
    return newVariable;
}
