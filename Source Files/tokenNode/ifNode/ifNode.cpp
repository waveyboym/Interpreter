#include "ifNode.h"

ifNode::ifNode(){}

void ifNode::appendNew__If__ElseIf__Else__statement(const std::shared_ptr<ifNode>& token){
    if(this->next__If__ElseIf__Else == nullptr)this->next__If__ElseIf__Else = token;
    else if(this->next__If__ElseIf__Else != nullptr){
        std::shared_ptr<ifNode> nextNode = std::dynamic_pointer_cast<ifNode>(this->next__If__ElseIf__Else);
        if(nextNode == nullptr){
            Exceptions newExc("FATAL ERROR: Null reference exception. Could not cast node object.");
            throw newExc;
        }
        nextNode->appendNew__If__ElseIf__Else__statement(token);
    }
}

std::string ifNode::__represent__(){
    if(this->condition != nullptr && this->next__If__ElseIf__Else == nullptr && this->statementsvect.empty()){
        return this->conditionaltype + " : " + this->condition->__represent__() + " : \nno statements\n";
    }
    else if(this->condition != nullptr && this->next__If__ElseIf__Else == nullptr && !this->statementsvect.empty()){
        std::string outputdata = "";
        for(int i = 0; i < this->statementsvect.size(); ++i){
            outputdata += "  [" + std::to_string(i + 1) + "]" + " " + this->statementsvect[i].expression->__represent__() +"\n";
        }
        return this->conditionaltype + " : " + this->condition->__represent__() + " : \n" + outputdata;
    }
    else if(this->condition != nullptr && this->next__If__ElseIf__Else != nullptr && !this->statementsvect.empty()){
        std::string outputdata = "";
        for(int i = 0; i < this->statementsvect.size(); ++i){
            outputdata += "  [" + std::to_string(i + 1) + "]" + " " + this->statementsvect[i].expression->__represent__() + "\n";
        }
        return this->conditionaltype + " : " + this->condition->__represent__() + 
        " : \n" + outputdata + this->next__If__ElseIf__Else->__represent__();
    }
    else if(this->condition == nullptr && this->next__If__ElseIf__Else == nullptr && !this->statementsvect.empty()){
        std::string outputdata = "";
        for(int i = 0; i < this->statementsvect.size(); ++i){
            outputdata += "  [" + std::to_string(i + 1) + "]" + " " + this->statementsvect[i].expression->__represent__() + "\n";
        }
        return this->conditionaltype + " : " + " : \n" + outputdata;
    }
    else if(this->condition == nullptr && this->next__If__ElseIf__Else == nullptr && this->statementsvect.empty()){
        return this->conditionaltype + " :\n no statements\n";
    }
    else return this->nodeType;
}
