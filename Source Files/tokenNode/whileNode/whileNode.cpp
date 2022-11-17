#include "whileNode.h"

whileNode::whileNode(){}

std::string whileNode::__represent__(){
    if(this->condition != nullptr && this->statementsvect.empty()){
        return this->conditionaltype + " : " + this->condition->__represent__() + " : \nno statements\n";
    }
    else if(this->condition != nullptr && !this->statementsvect.empty()){
        std::string outputdata = "";
        for(int i = 0; i < this->statementsvect.size(); ++i){
            outputdata += "  [" + std::to_string(i + 1) + "]" + " " + this->statementsvect[i].expression->__represent__() +"\n";
        }
        return this->conditionaltype + " : " + this->condition->__represent__() + " : \n" + outputdata;
    }
    else return this->nodeType;
}