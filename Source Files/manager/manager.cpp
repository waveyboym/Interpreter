#include "manager.h"

void manager::__BEGIN__PROCESSING(const std::string& filePath){
    this->filepath = filePath;
    this->lnNum = 1;

    std::string recentlyReadLine = "";
    std::string fileString = "";
    std::ifstream openedfilebuffer;
    openedfilebuffer.open(filepath.c_str());
    if(openedfilebuffer){
        while(getline(openedfilebuffer, recentlyReadLine)){
            fileString += recentlyReadLine;
        }
    }
    else{
        std::cout << "No file exists named: " << this->filepath << std::endl;
        return;
    }
    openedfilebuffer.close();

    std::vector<char> charvect;
    std::queue<std::string> program;

    for(int i = 0; i < fileString.length(); ++i){
        char current_char = fileString[i];
        if(current_char == '/'){
            ++i;
            if(i < fileString.length()){
                current_char = fileString[i];
                if(current_char == '*'){
                    this->isInComment = true;
                    ++i;
                    continue;
                }
            }
            charvect.push_back('/');
            --i;
            continue;
        }
        else if(current_char == '*'){
            ++i;
            if(i < fileString.length()){
                current_char = fileString[i];
                if(current_char == '/'){
                    this->isInComment = false;
                    continue;
                }
            }
            charvect.push_back('*');
            --i;
            continue;
        }

        if(current_char == ';' && !this->isInComment){
            std::string userData;
            for(int j = 0; j < charvect.size(); ++j){
                userData.push_back(charvect[j]);
            }
            program.push(userData);
            charvect.clear();
        }
        else if(aceptableChars(current_char) && !this->isInComment){
            charvect.push_back(current_char);
        }
    }

    try{
        while(!program.empty()){
            this->RUN__INTERPRETER(program.front());
            ++lnNum;
            program.pop();
        }
    }
    catch(Exceptions e){std::cout << e.getMessage() << std::endl;}
}

void manager::RUN__INTERPRETER(const std::string& currentLine){
    lexer Lexer(currentLine, this->filepath, this->lnNum);
    std::vector<token> data = Lexer.__RUN__LEXER___();
    
    if(data.size() > 0){
        //manager::displayVector(data);
        
        parser Parser(data, this->filepath, this->lnNum);
        std::shared_ptr<tokenNode> obj = Parser.__BEGIN__PARSE();
        //std::cout << "here is the object: " << std::endl << obj->__represent__() << std::endl;

        Interpreter interpreter(this->filepath, this->lnNum);
        
        interpreter.run__CODE(obj, Parser.getdatatype());
    }
    else return;
}

const std::array<char, manager::acceptable_charactersSIZE> manager::acceptable_characters = {
    //numbers
    '.', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
    //other characters
    ' ', '\t', '\n',
    //operators
    '+', '-', '/', '*', '^', '=', '(', ')', '%', '&', '|', '!', '<', '>', '{', '}', ':', ',',
    //letters
    //SMALL LETTERS
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't','u', 'v', 'w', 'x', 'y', 'z',
    //BIG LETTERS
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T','U', 'V', 'W', 'X', 'Y', 'Z',
    //UNDERSCORES,string opening and close
    '_',  '"'
};

bool manager::aceptableChars(const char& chraracter){
    for(int i = 0; i < manager::acceptable_characters.size(); ++i){
        if(chraracter == acceptable_characters[i])return true;
    }
    return false;
}

void manager::displayVector(const std::vector<token>& vect){
    std::cout << "[";
    for(int i = 0; i < vect.size(); ++i){
        if(i == vect.size() - 1){
            std::cout << vect[i].__represent__();
        }
        else{
            std::cout << vect[i].__represent__() << ",";
        }
    }
    std::cout << "]" << std::endl;
}
