#include "forNode.h"

forNode::forNode(){}

std::string forNode::__represent__(){
    if(this->declaration != nullptr && this->condition != nullptr && this->iteration != nullptr && this->statementsvect.empty()){
        return "for(" + this->declaration->__represent__() + " : " + this->condition->__represent__() + " : " + this->iteration->__represent__() + ")\n"
        "   no statements";
    }
    else if(this->declaration != nullptr && this->condition != nullptr && this->iteration != nullptr && !this->statementsvect.empty()){
        std::string outputdata = "";
        for(int i = 0; i < this->statementsvect.size(); ++i){
            outputdata += "  [" + std::to_string(i + 1) + "]" + " " + this->statementsvect[i].expression->__represent__() + "\n";
        }
        
        return "for(" + this->declaration->__represent__() + " : " + this->condition->__represent__() + " : " + this->iteration->__represent__() + ")\n"
        + outputdata;
    }
    else return this->nodeType;
}