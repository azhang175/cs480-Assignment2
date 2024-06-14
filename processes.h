#ifndef PROCESSES_H
#define PROCESSES_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <unistd.h>
#include <sys/wait.h>
#include <sstream>

void execute_command(const std::string&);
void execute_pipe(const std::string&);

#endif // PROCESSES_H