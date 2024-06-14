#include "processes.h"


void execute_command(const std::string& input) {
    std::istringstream i_stream(input);
    std::vector<std::string> args;
    std::string arg;

    while (i_stream >> arg) {
        args.push_back(arg);
    }

    if(args.size() != 1) {
        std::cerr << "Invalid command\n";
        return;
    }

    // Convert the string to a char* array
    std::vector<char*> c_args(args.size() + 1);
    for (size_t i = 0; i < c_args.size(); ++i) {
       c_args[i] = &args[i][0];
    }

    pid_t pid = fork();
    if(pid == 0){
        // Child process
        if (execvp(c_args[0], c_args.data()) < 0) {
            std::perror("execvp");
            std::exit(EXIT_FAILURE);
        }
    } else if(pid > 0) {
        // Parent process
        wait(NULL);
    } else {
        // Error forking
        std::perror("fork");
        std::exit(EXIT_FAILURE);
    }
}