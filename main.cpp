#include "processes.h"

int main() {
    std::string userInput;
    
    while(true) {
        std::cout << "cssc4405% ";
        std::getline(std::cin, userInput);
        if(userInput == "exit") {
            std::cout << "Exiting...\n";
            break;
        }else if(userInput.find("|") != std::string::npos){
            execute_pipe(userInput);
        }else {
            execute_command(userInput);
        }
    }
}