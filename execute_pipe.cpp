#include "processes.h"

void execute_pipe(const std::string& input) {
    std::istringstream i_stream(input);
    std::vector<std::string> commands;
    std::string s_command;

    int pid = 0;
    int j = 0;

    while(std::getline(i_stream, s_command, '|')) {
        commands.push_back(s_command);
    }

    int num_commands = commands.size();
    int pipefd[(num_commands - 1) * 2];

    for(int i = 0; i < num_commands - 1; ++i) {
        if(pipe(pipefd + i * 2) < 0) {
            std::perror("pipe");
            std::exit(EXIT_FAILURE);
        }
    }

    for(int i = 0; i < num_commands; ++i){
        pid = fork();

        if(pid == 0){
            if(i != 0){
                if(dup2(pipefd[j - 2], 0) < 0){
                    std::perror("dup2");
                    std::exit(EXIT_FAILURE);
                }
            }
            
            if(i != num_commands - 1){
                if(dup2(pipefd[j + 1], 1) < 0){
                    std::perror("dup2");
                    std::exit(EXIT_FAILURE);
                }
            }

            //close all pipe file descriptors
            for (int k = 0; k < (num_commands - 1) * 2; k++){
                close(pipefd[k]);
            }

            std::istringstream cmd(commands[i]);
            std::vector<std::string> args;
            std::string arg;

            while (cmd >> arg) {
                args.push_back(arg);
            }

            // Convert the string to a char* array
            std::vector<char*> c_args(args.size() + 1);
            for (size_t k = 0; k < arg.size(); k++) {
                c_args[k] = &args[k][0];
            }

            c_args[args.size()] = nullptr;

            if(execvp(c_args[0], c_args.data()) < 0){
                std::perror("execvp");
                std::exit(EXIT_FAILURE);
            }
        }
        else if(pid < 0){
            // Error forking
            std::perror("fork");
        }
        
        j = j + 2;
    }

     //close all pipe file descriptors
    for (int i = 0; i < (num_commands - 1) * 2; ++i){
        close(pipefd[i]);
    }

    for(int i = 0; i < num_commands; ++i){
        wait(NULL);
    }
}