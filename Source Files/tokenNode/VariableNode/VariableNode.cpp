#include "VariableNode.h"

std::vector<std::shared_ptr<VariableNode>> VariableNode::stackNUMBERvector;
std::vector<std::shared_ptr<VariableNode>> VariableNode::stackWORDvector;

VariableNode::VariableNode(){}

std::string VariableNode::__represent__(){
    if(this->assignedData != nullptr && this->appendData == nullptr){
        return this->varName + " : " + this->assignedData->__represent__();
    }
    else if(this->assignedData != nullptr && this->appendData != nullptr){
        return this->varName + " : " + this->assignedData->__represent__() + " " + this->appendType + " = " + this->appendData->__represent__();
    }
    else{
        return this->varName + " : 'null data'";
    }
}

void VariableNode::pushIntoVector(std::shared_ptr<VariableNode> token, const std::string& stacktype){
    if(stacktype == "NodeNUMBERVAR")stackNUMBERvector.push_back(token);
    else if(stacktype == "NodeSTRINGVAR")stackWORDvector.push_back(token);
}

bool VariableNode::alreadyExistingVariable(const std::string& toCheck, const std::string& stacktype){
    if(stacktype == "NodeNUMBERVAR"){
        for(int i = 0; i < stackNUMBERvector.size(); ++i){
            if(stackNUMBERvector[i]->varName == toCheck)return true;
        }
        return false;
    }
    else if(stacktype == "NodeSTRINGVAR"){
        for(int i = 0; i < stackWORDvector.size(); ++i){
            if(stackWORDvector[i]->varName == toCheck)return true;
        }
        return false;
    }
    else return false;
}

std::shared_ptr<VariableNode> VariableNode::getThisVariableobject(const std::string& variablename, const std::string& stacktype){
    if(stacktype == "NodeNUMBERVAR"){
        for(int i = 0; i < stackNUMBERvector.size(); ++i){
            if(stackNUMBERvector[i]->varName == variablename)return stackNUMBERvector[i];
        }
        return nullptr;
    }
    else if(stacktype == "NodeSTRINGVAR"){
        for(int i = 0; i < stackWORDvector.size(); ++i){
            if(stackWORDvector[i]->varName == variablename)return stackWORDvector[i];
        }
        return nullptr;
    }
    else return nullptr;
}

bool VariableNode::reassignExistingVariable(std::shared_ptr<tokenNode> token, const std::string& variablename, const std::string& stacktype, const std::string& appendtype){
    if(stacktype == "NodeNUMBERVAR"){
        for(int i = 0; i < stackNUMBERvector.size(); ++i){
            if(stackNUMBERvector[i]->varName == variablename){
                if(appendtype == "null"){
                    stackNUMBERvector[i]->assignedData = token;
                    stackNUMBERvector[i]->appendData = nullptr;
                    stackNUMBERvector[i]->appendType = "null";
                    return true;
                }
                else if(appendtype == "loop"){
                    stackNUMBERvector[i]->assignedData = token;
                    return true;
                }
                else{
                    stackNUMBERvector[i]->appendData = token;
                    return true;
                }
            }
        }
        return false;
    }
    else if(stacktype == "NodeSTRINGVAR"){
        for(int i = 0; i < stackWORDvector.size(); ++i){
            if(stackWORDvector[i]->varName == variablename){
                if(appendtype == "null"){
                    stackWORDvector[i]->assignedData = token;
                    stackWORDvector[i]->appendData = nullptr;
                    stackWORDvector[i]->appendType = "null";
                    return true;
                }
                else if(appendtype == "OpNodePLUSEQUALS"){
                    stackWORDvector[i]->appendData = token;
                    return true;
                }
                else{
                    Exceptions newExc("FATAL ERROR: Only addition operation are permited on words.\n"
                    "\n"
                    "Expected: " + variablename + " += "+ token->__represent__() + "\n"
                    "                           ^\n\n");
                    throw newExc;
                }
            }
        }
        return false;
    }
    else return false;
}
