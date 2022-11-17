#include "builtinNode.h"

builtinNode::builtinNode(){}

std::string builtinNode::__represent__(){
    if(this->assigneddata != nullptr){
        return this->built_in_name + " ( '" + this->assigneddata->__represent__() + "' ) ";
    }
    else{
        return this->nodeType;
    }
}