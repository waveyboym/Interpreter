#include "functionNode.h"

std::vector<std::shared_ptr<functionNode>> functionNode::stackFUNCvector;

functionNode::functionNode(){}

std::string functionNode::__represent__(){
    if(!this->statementsvect.empty()){
        std::string outputdata = "(";
        if(this->arguments.empty()){
            std::string outputdata = "(";
            for(int i = 0; i < this->arguments.size(); ++i){
                if(i == this->arguments.size() - 1){
                    outputdata += this->arguments[i].expression->__represent__();
                }
                else{
                    outputdata += this->arguments[i].expression->__represent__() + ",";
                }
            }
            outputdata += ")";
        }
        std::string statements = "";
        for(int i = 0; i < this->statementsvect.size(); ++i){
            statements += "[" + std::to_string(i) + "]" + this->statementsvect[i].expression->__represent__() + "\n";
        }

        if(this->arguments.empty()){
            return "function-name: " + this->functionName + outputdata + "\n" 
            "no statements";
        }
        else{
            return "function-name: " + this->functionName + outputdata + "\n" 
            + statements;
        }
    }
    else{
        return this->nodeType;
    }
}

void functionNode::attachArgAt(int& index, std::shared_ptr<tokenNode> value){

}

void functionNode::pushIntoFuncVector(std::shared_ptr<functionNode> token){
    functionNode::stackFUNCvector.push_back(token);
}

bool functionNode::alreadyExistingFunction(const std::string& toCheck){
    for(int i = 0; i < functionNode::stackFUNCvector.size(); ++i){
        if(functionNode::stackFUNCvector[i]->functionName == toCheck){
            return true;
        }
    }
    return false;
}

std::shared_ptr<functionNode> functionNode::getThisFunction(const std::string& funcname){
    for(int i = 0; i < functionNode::stackFUNCvector.size(); ++i){
        if(functionNode::stackFUNCvector[i]->functionName == funcname){
            return functionNode::stackFUNCvector[i];
        }
    }
    return nullptr;
}
