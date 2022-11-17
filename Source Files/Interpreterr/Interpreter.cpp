#include "Interpreter.h"

Interpreter::Interpreter(const std::string& filepath, const int& linenumber){
    this->filePath = filepath;
    this->lnNum = linenumber;
    this->isInLoop = false;
}

void Interpreter::run__CODE(std::shared_ptr<tokenNode>& TKNode, const std::string& datatype){
    this->visit_controlflow(TKNode, datatype);
}

void Interpreter::visit_controlflow(std::shared_ptr<tokenNode>& TKNode, const std::string& datatype){
    if(TKNode->nodeType == tokens::visitNodesArr[VISITNODES::IFSTATEMENTNODE]){
        
        std::shared_ptr<tokenNode> traverser = TKNode;
        while(traverser != nullptr){
            std::shared_ptr<ifNode> ifstatementsobj = std::dynamic_pointer_cast<ifNode>(traverser);
            if(ifstatementsobj == nullptr){
                Exceptions newExc(EXCEPTIONS_MSG::NULLPTREXCEPTION_INTERPRETER, this->filePath, this->lnNum, 0, TKNode->__represent__());
                throw newExc;
            }

            if(ifstatementsobj->conditionaltype == "if" || ifstatementsobj->conditionaltype == "elseif"){
                bool conditionstatus = this->checkCondition(ifstatementsobj->condition, ifstatementsobj->datatype);
                if(!conditionstatus){
                    traverser = ifstatementsobj->next__If__ElseIf__Else;
                    continue;
                }
            }
            for(int i = 0; i < ifstatementsobj->statementsvect.size(); ++i){
                this->visit_controlflow(ifstatementsobj->statementsvect[i].expression, ifstatementsobj->statementsvect[i].datatype);
            }
            break;
        }
    }
    else if(TKNode->nodeType == tokens::visitNodesArr[VISITNODES::WHILESTATEMENT]){
        std::shared_ptr<whileNode> whileobj = std::dynamic_pointer_cast<whileNode>(TKNode);

        if(whileobj == nullptr){
            Exceptions newExc(EXCEPTIONS_MSG::NULLPTREXCEPTION_INTERPRETER, this->filePath, this->lnNum, 0, TKNode->__represent__());
            throw newExc;
        }

        bool wasInLoop = false;
        if(this->isInLoop)wasInLoop = this->isInLoop;
        this->isInLoop = true;
        while(true){
            
            bool conditionstatus = this->checkCondition(whileobj->condition, whileobj->datatype);
            if(!conditionstatus){//condition true so break out of while loop
                this->isInLoop = wasInLoop;
                return;
            }

            for(int i = 0; i < whileobj->statementsvect.size(); ++i){
                this->visit_controlflow(whileobj->statementsvect[i].expression, whileobj->statementsvect[i].datatype);
            }
        }

    }
    else if(TKNode->nodeType == tokens::visitNodesArr[VISITNODES::FORSTATEMENT]){
        std::shared_ptr<forNode> forobj = std::dynamic_pointer_cast<forNode>(TKNode);

        if(forobj == nullptr){
            Exceptions newExc(EXCEPTIONS_MSG::NULLPTREXCEPTION_INTERPRETER, this->filePath, this->lnNum, 0, TKNode->__represent__());
            throw newExc;
        }
        
        bool wasInLoop = false;
        if(this->isInLoop)wasInLoop = this->isInLoop;
        /*if a loop was started before visit_controlflow() 
        was called recursively
        then make was in loop true*/
        this->isInLoop = true;
        while(true){
            
            bool conditionstatus = this->checkCondition(forobj->condition, forobj->datatype);
            if(!conditionstatus){//condition true so break out of while loop
                //reset for loop declaration to it's initial data if the variable was declared in for decl loop
                //else don't do anything
                if(!forobj->decl_Var_Exists){
                    if(forobj->init_declaration != nullptr )this->resetVariableValue(forobj);
                    else{
                        Exceptions newExc(EXCEPTIONS_MSG::NULLPTREXCEPTION_INTERPRETER, this->filePath, this->lnNum, 0, TKNode->__represent__());
                        throw newExc;
                    }
                }
                this->isInLoop = wasInLoop;
                return;
            }

            for(int i = 0; i < forobj->statementsvect.size(); ++i){
                this->visit_controlflow(forobj->statementsvect[i].expression, forobj->statementsvect[i].datatype);
            }

            this->visit_controlflow(forobj->iteration, forobj->datatype);
        }
    }
    else{ 
        this->visit_built_in_func(TKNode, datatype);
    }
}

void Interpreter::visit_built_in_func(std::shared_ptr<tokenNode>& TKNode, const std::string& datatype){
    if(TKNode->nodeType == tokens::visitNodesArr[VISITNODES::BUITINFUNCTION]){
        std::shared_ptr<builtinNode> display = std::dynamic_pointer_cast<builtinNode>(TKNode);
        if(display == nullptr){
            Exceptions newExc(EXCEPTIONS_MSG::NULLPTREXCEPTION_INTERPRETER, this->filePath, this->lnNum, 0, TKNode->__represent__());
            throw newExc;
        }

        if(datatype == "word"){
            returnStringValues stringobj = this->visitWORDS(display->assigneddata);
            if(stringobj.isbooleanstatement){
                if(display->built_in_name == tokens::KEYWORDS[KEYWRODSTYPE::DISPLAYLINE] || display->built_in_name == tokens::KEYWORDS[KEYWRODSTYPE::PRINTLINE]){
                    std::cout << stringobj.result;
                }
                else if(display->built_in_name == tokens::KEYWORDS[KEYWRODSTYPE::DISPLAYNEWLINE] || display->built_in_name == tokens::KEYWORDS[KEYWRODSTYPE::PRINTNEWLINE]){
                    std::cout << stringobj.result << std::endl;
                }
            }
            else{
                if(display->built_in_name == tokens::KEYWORDS[KEYWRODSTYPE::DISPLAYLINE] || display->built_in_name == tokens::KEYWORDS[KEYWRODSTYPE::PRINTLINE]){
                    std::cout << stringobj.value;
                }
                else if(display->built_in_name == tokens::KEYWORDS[KEYWRODSTYPE::DISPLAYNEWLINE] || display->built_in_name == tokens::KEYWORDS[KEYWRODSTYPE::PRINTNEWLINE]){
                    std::cout << stringobj.value << std::endl;
                }
            }
        }
        else if(datatype == "number"){
            returnNumberValues numberobj = this->visitNUMBERS(display->assigneddata);
            if(numberobj.isbooleanstatement){
                if(display->built_in_name == tokens::KEYWORDS[KEYWRODSTYPE::DISPLAYLINE] || display->built_in_name == tokens::KEYWORDS[KEYWRODSTYPE::PRINTLINE]){
                    std::cout << numberobj.value;
                }
                else if(display->built_in_name == tokens::KEYWORDS[KEYWRODSTYPE::DISPLAYNEWLINE] || display->built_in_name == tokens::KEYWORDS[KEYWRODSTYPE::PRINTNEWLINE]){
                    std::cout << numberobj.value << std::endl;
                }
            }
            else{
                if(display->built_in_name == tokens::KEYWORDS[KEYWRODSTYPE::DISPLAYLINE] || display->built_in_name == tokens::KEYWORDS[KEYWRODSTYPE::PRINTLINE]){
                    std::cout << numberobj.value;
                }
                else if(display->built_in_name == tokens::KEYWORDS[KEYWRODSTYPE::DISPLAYNEWLINE] || display->built_in_name == tokens::KEYWORDS[KEYWRODSTYPE::PRINTNEWLINE]){
                    std::cout << numberobj.value << std::endl;
                }
            }
        }
    }
    else{
        this->visit_Variables(TKNode, datatype);
    }
}

void Interpreter::visit_Variables(std::shared_ptr<tokenNode>& TKNode, const std::string& datatype){
    if(TKNode->nodeType == tokens::visitNodesArr[VISITNODES::STRINGVARNODE] || datatype == "word"){
        std::shared_ptr<VariableNode> variable = std::dynamic_pointer_cast<VariableNode>(TKNode);
        returnStringValues obj;

        if(variable != nullptr){
            if(variable->appendType == "null"){
                obj = this->visitWORDS(TKNode);
                std::shared_ptr<StringNode> word = std::make_shared<StringNode>();
                word->nodeType = tokens::visitNodesArr[VISITNODES::STRINGNODE];

                if(obj.isbooleanstatement) word->stringValue = obj.result;
                else word->stringValue = obj.value;

                VariableNode::reassignExistingVariable(word, variable->varName, variable->nodeType, "null");
            }
            else{
                obj = this->visitWORDS(variable->appendData);

                if(obj.isbooleanstatement){
                    Exceptions newExc(EXCEPTIONS_MSG::ATTEMPTED_BOOLEAN_APPEND, this->filePath, this->lnNum, 0, TKNode->__represent__());
                    throw newExc;
                }
                obj.value = this->visit__StringAppendNode(variable, obj.value);

                std::shared_ptr<StringNode> word = std::make_shared<StringNode>();
                word->nodeType = tokens::visitNodesArr[VISITNODES::STRINGNODE];
                word->stringValue = obj.value;

                if(this->isInLoop){
                    VariableNode::reassignExistingVariable(word, variable->varName, variable->nodeType, "loop");
                }
                else{
                    VariableNode::reassignExistingVariable(word, variable->varName, variable->nodeType, "null");
                }
            }
        }
        else this->visitWORDS(TKNode);
    }
    else if(TKNode->nodeType == tokens::visitNodesArr[VISITNODES::NUMBERVARNODE] || datatype == "number"){
        std::shared_ptr<VariableNode> variable = std::dynamic_pointer_cast<VariableNode>(TKNode);
        returnNumberValues obj;

        if(variable == nullptr)this->visitNUMBERS(TKNode);

        if(variable->appendType == "null"){
            obj = this->visitNUMBERS(TKNode);
            std::shared_ptr<NumberNode> number = std::make_shared<NumberNode>();
            number->nodeType = tokens::visitNodesArr[VISITNODES::NUMBERNODE];

            if(obj.isbooleanstatement) number->value = obj.result;
            else number->value = obj.value;

            VariableNode::reassignExistingVariable(number, variable->varName, variable->nodeType, "null");
        }
        else{
                obj = this->visitNUMBERS(variable->appendData);

                if(obj.isbooleanstatement){
                    Exceptions newExc(EXCEPTIONS_MSG::ATTEMPTED_BOOLEAN_APPEND, this->filePath, this->lnNum, 0, TKNode->__represent__());
                    throw newExc;
                }
                obj.value = this->visit__NumberAppendNode(variable, obj.value);

                std::shared_ptr<NumberNode> number = std::make_shared<NumberNode>();
                number->nodeType = tokens::visitNodesArr[VISITNODES::NUMBERNODE];
                number->value = obj.value;
                if(this->isInLoop){
                    VariableNode::reassignExistingVariable(number, variable->varName, variable->nodeType, "loop");
                }
                else{
                    VariableNode::reassignExistingVariable(number, variable->varName, variable->nodeType, "null");
                }
            }

    }
    else{
        Exceptions newExc(EXCEPTIONS_MSG::INCORRECT_VARIABLE_DATATYPE, this->filePath, this->lnNum, 0, TKNode->__represent__());
        throw newExc;
    }
}

returnStringValues Interpreter::visitWORDS(std::shared_ptr<tokenNode>& TKNode){
    if(TKNode == nullptr){
        Exceptions newExc(EXCEPTIONS_MSG::NULLPTREXCEPTION_INTERPRETER, this->filePath, this->lnNum, 0, "null");
        throw newExc;
    }

    std::shared_ptr<StringNode> word = std::dynamic_pointer_cast<StringNode>(TKNode);
    if(word != nullptr){
        returnStringValues obj;
        obj.value = this->visit__StringNode(word);
        return obj;
    }

    std::shared_ptr<OperatorNode> operatornode = std::dynamic_pointer_cast<OperatorNode>(TKNode);
    if(operatornode != nullptr && operatornode->left != nullptr && operatornode->right != nullptr && !operatornode->isUnaryOperator){
        return this->visit__stringOPNODE(operatornode);
    }
    else if(operatornode != nullptr && operatornode->isUnaryOperator && operatornode->unaryopdata != nullptr){//create for not !
        returnStringValues obj = this->visitWORDS(operatornode->unaryopdata);
        if(obj.isbooleanstatement)obj.result = !(obj.result);
        else {
            Exceptions newExc("");
            throw newExc;
        }

        return obj;
    }
    
    std::shared_ptr<VariableNode> variable = std::dynamic_pointer_cast<VariableNode>(TKNode);
    if(variable != nullptr && variable->assignedData != nullptr){
        return this->visitWORDS(variable->assignedData);
    }
    else{
        Exceptions newExc(EXCEPTIONS_MSG::INCORRECT_OPERATION, this->filePath,this->lnNum, 0, TKNode->__represent__());
        throw newExc;
    }
}

returnNumberValues Interpreter::visitNUMBERS(std::shared_ptr<tokenNode>& TKNode){
    if(TKNode == nullptr){
        Exceptions newExc(EXCEPTIONS_MSG::NULLPTREXCEPTION_INTERPRETER, this->filePath, this->lnNum, 0, "null");
        throw newExc;
    }

    std::shared_ptr<NumberNode> number = std::dynamic_pointer_cast<NumberNode>(TKNode);
    if(number != nullptr && !number->isUnaryOperator && number->unaryopdata == nullptr){
        returnNumberValues obj;
        obj.value = this->visit__NumberNode(number);
        return obj;
    }
    else if(number != nullptr && number->isUnaryOperator && number->unaryopdata == nullptr){
        returnNumberValues obj;
        obj.value = this->visit__unaryNumberNode(number);
        return obj;
    }
    else if(number != nullptr && number->isUnaryOperator && number->unaryopdata != nullptr){
        returnNumberValues obj;
        obj.value = this->visit__unaryNumberNodeExpr(number);
        return obj;
    }

    std::shared_ptr<OperatorNode> operatornode = std::dynamic_pointer_cast<OperatorNode>(TKNode);
    if(operatornode != nullptr && operatornode->left != nullptr && operatornode->right != nullptr && !operatornode->isUnaryOperator){
        return this->visit__numberOPNODE(operatornode);
    }
    else if(operatornode != nullptr && operatornode->isUnaryOperator && operatornode->unaryopdata != nullptr){//create for not !
        returnNumberValues obj = this->visitNUMBERS(operatornode->unaryopdata);
        if(obj.isbooleanstatement)obj.result = !(obj.result);
        else obj.value = !(obj.value);

        return obj;
    }
    
    std::shared_ptr<VariableNode> variable = std::dynamic_pointer_cast<VariableNode>(TKNode);
    if(variable != nullptr && variable->assignedData != nullptr){
        return this->visitNUMBERS(variable->assignedData);
    }
    
    else{
        Exceptions newExc(EXCEPTIONS_MSG::INCORRECT_OPERATION, this->filePath,this->lnNum, 0, TKNode->__represent__());
        throw newExc;
    }
}

std::string Interpreter::visit__StringNode(std::shared_ptr<StringNode>& TKNode){return TKNode->stringValue;};

double Interpreter::visit__NumberNode(std::shared_ptr<NumberNode>& TKNode){return TKNode->value;}

double Interpreter::visit__unaryNumberNode(std::shared_ptr<NumberNode>& TKNode){
    if(TKNode->unary_op_token == "+")return TKNode->value;
    else if(TKNode->unary_op_token == "-")return -1 * TKNode->value;
    else{
        Exceptions newExc(EXCEPTIONS_MSG::INVALID_UNARY_TYPE, this->filePath, this->lnNum, 0, TKNode->__represent__());
        throw newExc;
    }
}

double Interpreter::visit__unaryNumberNodeExpr(std::shared_ptr<NumberNode>& TKNode){
    if(TKNode->unary_op_token == "+") return this->visitNUMBERS(TKNode->unaryopdata).value;
    else if(TKNode->unary_op_token == "-")return -1 * this->visitNUMBERS(TKNode->unaryopdata).value;
    else{
        Exceptions newExc(EXCEPTIONS_MSG::INVALID_UNARY_TYPE, this->filePath, this->lnNum, 0, TKNode->__represent__());
        throw newExc;
    }
}

returnNumberValues Interpreter::visit__numberOPNODE(std::shared_ptr<OperatorNode>& TKNode){
    if(TKNode->op_token == "+"){
        returnNumberValues obj;
        obj.value = this->visitNUMBERS(TKNode->left).value + this->visitNUMBERS(TKNode->right).value;
        return obj;
    }
    else if(TKNode->op_token == "-"){
        returnNumberValues obj;
        obj.value = this->visitNUMBERS(TKNode->left).value - this->visitNUMBERS(TKNode->right).value;
        return obj;
    }
    else if(TKNode->op_token == "*"){
        returnNumberValues obj;
        obj.value = this->visitNUMBERS(TKNode->left).value * this->visitNUMBERS(TKNode->right).value;
        return obj;
    }
    else if(TKNode->op_token == "/"){
        returnNumberValues obj;

        double numerator = this->visitNUMBERS(TKNode->left).value;
        double denominator = this->visitNUMBERS(TKNode->right).value;

        if(denominator == 0.0 && numerator != 0.0){
            Exceptions newExc(EXCEPTIONS_MSG::DIVISION_BY_ZERO, this->filePath, this->lnNum, 0, TKNode->__represent__());
            throw newExc;
        }
        else{
            obj.value =  numerator / denominator;
            return obj;
        }
    }
    else if(TKNode->op_token == "^"){
        returnNumberValues obj;
        obj.value = pow(this->visitNUMBERS(TKNode->left).value, this->visitNUMBERS(TKNode->right).value);
        return obj;
    }
    else if(TKNode->op_token == "%"){
        returnNumberValues obj;
        int calcresult = (int)this->visitNUMBERS(TKNode->left).value % (int)this->visitNUMBERS(TKNode->right).value;
        obj.value = (double)calcresult;
        return obj;
    }
    else if(TKNode->op_token == "&&"){
        returnNumberValues leftside = this->visitNUMBERS(TKNode->left);
        returnNumberValues rightside = this->visitNUMBERS(TKNode->right);

        if(!leftside.isbooleanstatement && !rightside.isbooleanstatement){
            leftside.result = (int)leftside.value;
            rightside.result = (int)rightside.value;
        }

        returnNumberValues obj;
        obj.isbooleanstatement = true;
        obj.result = (leftside.result && rightside.result);
        return obj;
    }
    else if(TKNode->op_token == "||"){
        returnNumberValues leftside = this->visitNUMBERS(TKNode->left);
        returnNumberValues rightside = this->visitNUMBERS(TKNode->right);

        if(!leftside.isbooleanstatement && !rightside.isbooleanstatement){
            leftside.result = (int)leftside.value;
            rightside.result = (int)rightside.value;
        }

        returnNumberValues obj;
        obj.isbooleanstatement = true;
        obj.result = (leftside.result || rightside.result);
        return obj;
    }
    else if(TKNode->op_token == ">"){
        returnNumberValues obj;
        obj.isbooleanstatement = true;
        obj.result = (this->visitNUMBERS(TKNode->left).value > this->visitNUMBERS(TKNode->right).value);
        return obj;
    }
    else if(TKNode->op_token == "<"){
        returnNumberValues obj;
        obj.isbooleanstatement = true;
        obj.result = (this->visitNUMBERS(TKNode->left).value < this->visitNUMBERS(TKNode->right).value);
        return obj;
    }
    else if(TKNode->op_token == ">="){
        returnNumberValues obj;
        obj.isbooleanstatement = true;
        obj.result = (this->visitNUMBERS(TKNode->left).value >= this->visitNUMBERS(TKNode->right).value);
        return obj;
    }
    else if(TKNode->op_token == "<="){
        returnNumberValues obj;
        obj.isbooleanstatement = true;
        obj.result = (this->visitNUMBERS(TKNode->left).value <= this->visitNUMBERS(TKNode->right).value);
        return obj;
    }
    else if(TKNode->op_token == "!="){
        returnNumberValues obj;
        obj.isbooleanstatement = true;
        obj.result = (this->visitNUMBERS(TKNode->left).value != this->visitNUMBERS(TKNode->right).value);
        return obj;
    }
    else if(TKNode->op_token == "=="){
        returnNumberValues obj;
        obj.isbooleanstatement = true;
        obj.result = (this->visitNUMBERS(TKNode->left).value == this->visitNUMBERS(TKNode->right).value);
        return obj;
    }
    else{
        Exceptions newExc(EXCEPTIONS_MSG::UNRECOGNIZABLE_OPERATOR, this->filePath, this->lnNum, 0, TKNode->__represent__());
        throw newExc;
    }
}

returnStringValues Interpreter::visit__stringOPNODE(std::shared_ptr<OperatorNode>& TKNode){
    if(TKNode->op_token == "+"){
        returnStringValues obj;
        obj.value = this->visitWORDS(TKNode->left).value + this->visitWORDS(TKNode->right).value;
        return obj;
    }
    else if(TKNode->op_token == "&&"){
        returnStringValues obj;
        obj.isbooleanstatement = true;
        returnStringValues leftside = this->visitWORDS(TKNode->left);
        returnStringValues rightside = this->visitWORDS(TKNode->right);

        if(!leftside.isbooleanstatement || !rightside.isbooleanstatement){
            Exceptions newExc(EXCEPTIONS_MSG::UNRECOGNIZABLE_WORD_DATATYPE_OPERATOR, this->filePath, this->lnNum, 0, TKNode->__represent__());
            throw newExc;
        }

        obj.result = (leftside.result && leftside.result);
        return obj;
    }
    else if(TKNode->op_token == "||"){
        returnStringValues obj;
        obj.isbooleanstatement = true;
        returnStringValues leftside = this->visitWORDS(TKNode->left);
        returnStringValues rightside = this->visitWORDS(TKNode->right);

        if(!leftside.isbooleanstatement || !rightside.isbooleanstatement){
            Exceptions newExc(EXCEPTIONS_MSG::UNRECOGNIZABLE_WORD_DATATYPE_OPERATOR, this->filePath, this->lnNum, 0, TKNode->__represent__());
            throw newExc;
        }

        obj.result = (leftside.result || leftside.result);
        return obj;
    }
    else if(TKNode->op_token == ">"){
        returnStringValues obj;
        obj.isbooleanstatement = true;
        obj.result = (this->visitWORDS(TKNode->left).value > this->visitWORDS(TKNode->right).value);
        return obj;
    }
    else if(TKNode->op_token == "<"){
        returnStringValues obj;
        obj.isbooleanstatement = true;
        obj.result = (this->visitWORDS(TKNode->left).value < this->visitWORDS(TKNode->right).value);
        return obj;
    }
    else if(TKNode->op_token == ">="){
        returnStringValues obj;
        obj.isbooleanstatement = true;
        obj.result = (this->visitWORDS(TKNode->left).value >= this->visitWORDS(TKNode->right).value);
        return obj;
    }
    else if(TKNode->op_token == "<="){
        returnStringValues obj;
        obj.isbooleanstatement = true;
        obj.result = (this->visitWORDS(TKNode->left).value <= this->visitWORDS(TKNode->right).value);
        return obj;
    }
    else if(TKNode->op_token == "!="){
        returnStringValues obj;
        obj.isbooleanstatement = true;
        obj.result = (this->visitWORDS(TKNode->left).value != this->visitWORDS(TKNode->right).value);
        return obj;
    }
    else if(TKNode->op_token == "=="){
        returnStringValues obj;
        obj.isbooleanstatement = true;
        obj.result = (this->visitWORDS(TKNode->left).value == this->visitWORDS(TKNode->right).value);
        return obj;
    }
    else{
        Exceptions newExc(EXCEPTIONS_MSG::UNRECOGNIZABLE_WORD_DATATYPE_OPERATOR, this->filePath, this->lnNum, 0, TKNode->__represent__());
            throw newExc;
    }
}

double Interpreter::visit__NumberAppendNode(std::shared_ptr<VariableNode>& nodeToAppendTo, const double& passedvalue){
    returnNumberValues obj = this->visitNUMBERS(nodeToAppendTo->assignedData);

    if(obj.isbooleanstatement){
        Exceptions newExc(EXCEPTIONS_MSG::CANNOT_APPEND_BOOLEANS, this->filePath, this->lnNum, 0, nodeToAppendTo->__represent__());
        throw newExc;
    }
    
    if(nodeToAppendTo->appendType == tokens::visitNodesArr[VISITNODES::OPNODEPLUSEQUALS]){
        obj.value = obj.value + passedvalue;
        return obj.value;
    }
    else if(nodeToAppendTo->appendType == tokens::visitNodesArr[VISITNODES::OPNODEMINUSEQUALS]){
        obj.value = obj.value - passedvalue;
        return obj.value;
    }
    else if(nodeToAppendTo->appendType == tokens::visitNodesArr[VISITNODES::OPNODEDIVIDEEQUALS]){
        if(passedvalue == 0.0){
            Exceptions newExc(EXCEPTIONS_MSG::DIVISION_BY_ZERO, this->filePath, this->lnNum, 0, nodeToAppendTo->__represent__());
            throw newExc;
        }
        obj.value = obj.value / passedvalue;
        return obj.value;
    }
    else if(nodeToAppendTo->appendType == tokens::visitNodesArr[VISITNODES::OPNODEMULTIPLYEQUALS]){
        obj.value = obj.value * passedvalue;
        return obj.value;
    }
    else if(nodeToAppendTo->appendType == tokens::visitNodesArr[VISITNODES::OPNODEMODULUSEQUALS]){
        obj.value = (int)obj.value % (int)passedvalue;
        return obj.value;
    }
    else if(nodeToAppendTo->appendType == tokens::visitNodesArr[VISITNODES::OPNODEPOWEREQUALS]){
        obj.value = pow(obj.value, passedvalue);
        return obj.value;
    }
    else{
        Exceptions newExc(EXCEPTIONS_MSG::UNRECOGNIZABLE_WORD_DATATYPE_OPERATOR, this->filePath, this->lnNum, 0, nodeToAppendTo->__represent__());
        throw newExc;
    }
}

std::string Interpreter::visit__StringAppendNode(std::shared_ptr<VariableNode>& nodeToAppendTo, const std::string& passedvalue){
    returnStringValues obj = this->visitWORDS(nodeToAppendTo->assignedData);
    
    if(obj.isbooleanstatement){
        Exceptions newExc(EXCEPTIONS_MSG::CANNOT_APPEND_BOOLEANS, this->filePath, this->lnNum, 0, nodeToAppendTo->__represent__());
        throw newExc;
    }

    if(nodeToAppendTo->appendType == tokens::visitNodesArr[VISITNODES::OPNODEPLUSEQUALS]){
        obj.value = obj.value + passedvalue;
        return obj.value;
    }
    else{
        Exceptions newExc(EXCEPTIONS_MSG::UNRECOGNIZABLE_OPERATOR, this->filePath, this->lnNum, 0, nodeToAppendTo->__represent__());
        throw newExc;
    }
}

bool Interpreter::checkCondition(std::shared_ptr<tokenNode>& TKNode, const std::string& datatype){
    if(datatype == "word"){
        returnStringValues stringobj = this->visitWORDS(TKNode);
        if(!stringobj.isbooleanstatement){
            Exceptions newExc(EXCEPTIONS_MSG::INCORRECT_CONDITIONAL_CHECKER, this->filePath, this->lnNum, 0, TKNode->__represent__());
            throw newExc;
        }

        if(stringobj.result)return true;
        else return false;
    }
    else{//datatype = number
        returnNumberValues numberobj = this->visitNUMBERS(TKNode);
        if(!numberobj.isbooleanstatement){
            Exceptions newExc(EXCEPTIONS_MSG::INCORRECT_CONDITIONAL_CHECKER, this->filePath, this->lnNum, 0, TKNode->__represent__());
            throw newExc;
        }

        if(numberobj.result)return true;
        else return false;
    }
}

void Interpreter::resetVariableValue(std::shared_ptr<forNode>& forobj){
    std::shared_ptr<NumberNode> number = std::dynamic_pointer_cast<NumberNode>(forobj->init_declaration);
    std::shared_ptr<VariableNode> variable = std::dynamic_pointer_cast<VariableNode>(forobj->declaration);
    if(variable == nullptr){
        Exceptions newExc(EXCEPTIONS_MSG::NULLPTREXCEPTION_INTERPRETER, this->filePath, this->lnNum, 0, forobj->__represent__());
        throw newExc;
    }
    if(number != nullptr){
        VariableNode::reassignExistingVariable(number, variable->varName, variable->nodeType, "loop");
    }
    else{
        std::shared_ptr<OperatorNode> operator_data = std::dynamic_pointer_cast<OperatorNode>(forobj->init_declaration);
        if(operator_data == nullptr){
            Exceptions newExc(EXCEPTIONS_MSG::NULLPTREXCEPTION_INTERPRETER, this->filePath, this->lnNum, 0, forobj->__represent__());
            throw newExc;
        }
        VariableNode::reassignExistingVariable(operator_data, variable->varName, variable->nodeType, "loop");
    }
}