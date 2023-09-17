#pragma once

#include <iostream>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_WHITE   "\x1b[37m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define LOG(...) \
    log(__LINE__, __FILE__, __VA_ARGS__)

#define WARN(...) \
    warn(__LINE__, __FILE__, __VA_ARGS__)

#define FAULT(...) \
    fault(__LINE__, __FILE__, __VA_ARGS__)

template <typename ...Args>
void log(int line, const char* fileName, Args&& ...args) {
    std::cout << ANSI_COLOR_CYAN << fileName << "(" << line << ")" << ANSI_COLOR_RESET << "::"
              << ANSI_COLOR_GREEN << "LOG" << ANSI_COLOR_RESET << "::" << ANSI_COLOR_WHITE;
    (std::cout << ... << std::forward<Args>(args)) << ANSI_COLOR_RESET << '\n';
}

template <typename ...Args>
void warn(int line, const char* fileName, Args&& ...args){
    std::cout << ANSI_COLOR_CYAN << fileName << "(" << line << ")"  << ANSI_COLOR_RESET << "::"
              << ANSI_COLOR_MAGENTA << "WARN"  << ANSI_COLOR_RESET << "::" << ANSI_COLOR_WHITE;
    (std::cout << ... << std::forward<Args>(args)) << ANSI_COLOR_RESET << '\n';
}

template <typename ...Args>
void fault(int line, const char* fileName, Args&& ...args){
    std::cout << ANSI_COLOR_CYAN << fileName << "(" << line << ")"  << ANSI_COLOR_RESET << "::" 
              << ANSI_COLOR_RED << "FAULT"  << ANSI_COLOR_RESET << "::" << ANSI_COLOR_WHITE;
    (std::cout << ... << std::forward<Args>(args)) << ANSI_COLOR_RESET << '\n';
}
