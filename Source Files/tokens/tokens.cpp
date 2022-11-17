#include "tokens.h"

const std::array<std::string, tokens::tokensArrSIZE> tokens::tokensArr = {"NUMBER", "PLUS", "MINUS", "MULTIPLY", "DIVIDE", "LPAREN",
 "RPAREN", "POWER", "IDENTIFIER", "KEYWORD", "EQUALS", "STRING", "AND", "NOT", "OR", "MODULUS", "EQUALSEQUALS", "GREATERTHAN",
 "LESSTHAN", "GREATERTHANOREQUALTO", "LESSTHANOREQUALTO", "NOTEQUALTO", "BEGINLOCALSCOPE", "ENDLOCALSCOPE","PLUSEQUALS",
 "MINUSEQUALS", "MULTIPLYEQUALS", "DIVIDEEQUALS", "MODULUSEQUALS", "POWEREQUALS", "FORLOOPSEP", "FUNCARGSEP", "NULLNODE"};

const std::array<char, tokens::ignoreCharArrSIZE> tokens::ignoreCharArr = {' ', '\t', '\n'};

const std::array<char, tokens::DIGITSSIZE> tokens::DIGITS = {'.', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

const std::array<std::string, tokens::KEYWORDSSIZE> tokens::KEYWORDS = {"number", "word", "print", "println", "display", "displayln",
 "if", "elseif", "else", "then", "while", "for", "function", "callfunction"};

const std::array<char, tokens::LETTERSSIZE> tokens::LETTERS = {
    //SMALL LETTERS
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't','u', 'v', 'w', 'x', 'y', 'z',
    //BIG LETTERS
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T','U', 'V', 'W', 'X', 'Y', 'Z',
    //UNDERSCORES,string opening and close
    '_',};

const std::array<std::string, tokens::visitNodesArrSIZE> tokens::visitNodesArr = {"OpNodePLUS", "OpNodeMINUS", "OpNodeMULTIPLY", 
"OpNodeDIVIDE", "NumberNode", "UnaryNodePLUS", "UnaryNodeMINUS", "OpNodePOWER", "NodeNUMBERVAR", "NodeSTRINGVAR", "StringNode",
"OpNodeAND", "OpNodeNOT", "OpNodeOR", "OpNodeMODULUS", "OpNodeEQUALSEQUALS", "OpNodeGREATERTHAN", "OpNodeLESSTHAN",
"OpNodeGREATERTHANOREQUALTO", "OpNodeLESSTHANOREQUALTO", "OpNodeNOTEQUALTO", "OpNodeBUITINFUNCTION", "OpNodeIFSTATEMENT",
"OpNodeELSEIFSTATEMENT", "OpNodeELSESTATEMENT", "OpNodeWHILESTATEMENT", "OpNodePLUSEQUALS",
"OpNodeMINUSEQUALS", "OpNodeMULTIPLYEQUALS", "OpNodeDIVIDEEQUALS", "OpNodePOWEREQUALS", "OpNodeMODULUSEQUALS", "OpNodeFORSTATEMENT",
"FUNCTIONDECLARATION"};



bool tokens::isInIgnoreCharArr(const std::string& toCheck){
    for(int i = 0; i < ignoreCharArr.size(); ++i){
        if(toCheck[0] == ignoreCharArr[i])return true;
    }
    return false;
}

bool tokens::isInDIGITSarr(const std::string& toCheck){
    for(int i = 0; i < DIGITS.size(); ++i){
        if(toCheck[0] == DIGITS[i])return true;
    }
    return false;
}

bool tokens::isInLETTERSarr(const std::string& toCheck){
    for(int i = 0; i < LETTERS.size(); ++i){
        if(toCheck[0] == LETTERS[i])return true;
    }
    return false;
}

bool tokens::isInKEYWORDSarr(const std::string& toCheck){
    for(int i = 0; i < KEYWORDS.size(); ++i){
        if(toCheck == KEYWORDS[i])return true;
    }
    return false;
}

bool tokens::isOperatorNode(const std::string& nodeType){
    if(nodeType == visitNodesArr[VISITNODES::OPNODEDIVIDE] || nodeType == visitNodesArr[VISITNODES::OPNODEMINUS]
     || nodeType == visitNodesArr[VISITNODES::OPNODEMULTIPLY] || nodeType == visitNodesArr[VISITNODES::OPNODEMODULUS]
      || nodeType == visitNodesArr[VISITNODES::OPNODEPLUS] || nodeType == visitNodesArr[VISITNODES::POWEROPNODE]
       || nodeType == visitNodesArr[VISITNODES::OPNODEAND] || nodeType == visitNodesArr[VISITNODES::OPNODEOR] 
        || nodeType == visitNodesArr[VISITNODES::OPNODEEQUALSEQUALS] || nodeType == visitNodesArr[VISITNODES::OPNODEGREATERTHAN]
          || nodeType == visitNodesArr[VISITNODES::OPNODEGREATERTHANOREQUALTO] || nodeType == visitNodesArr[VISITNODES::OPNODELESSTHANOREQUALTO]
           || nodeType == visitNodesArr[VISITNODES::OPNODELESSTHAN] || nodeType == visitNodesArr[VISITNODES::OPNODENOTEQUALTO]){
        return true;
    }
    return false;
}

std::string tokens::tokentype(const int& index){
    if(index < 0 || index >= tokens::tokensArr.size() - 1)return "";
    else return tokens::tokensArr[index];
}

std::string token::__represent__() const{
    if(value == "")return tokens::tokensArr[type];
    else return tokens::tokensArr[type] + ":" + this->value;
}
