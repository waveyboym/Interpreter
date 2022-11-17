#include "manager/manager.h"

int main(){
    std::string filepath = "main.txt";//enter a file path here or be prompted for a file path in the terminal
    std::cout << "LANG begin >" << std::endl;
    if(filepath == ""){
        std::cout << "Enter file path: ";
        std::getline(std::cin, filepath);
    }
    std::cout << std::endl;
    
    manager Program;
    Program.__BEGIN__PROCESSING(filepath);
    std::cout << std::endl;
    std::cout << "LANG end <" << std::endl;
    return 0;
}