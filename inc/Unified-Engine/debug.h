#pragma once

#include <stdio.h>
#include <sstream>

#define LOG(...) \
    log(__LINE__, __FILE__, __VA_ARGS__)

#define WARN(...) \
    warn(__LINE__, __FILE__, __VA_ARGS__)

#define FAULT(...) \
    fault(__LINE__, __FILE__, __VA_ARGS__)

template <typename ...Args>
void log(int line, const char* fileName, Args&& ...args) {
    std::ostringstream stream;
    stream << fileName << "(" << line << ")::LOG::";
    (stream << ... << std::forward<Args>(args)) << '\n';

    printf(stream.str().c_str());
}

template <typename ...Args>
void warn(int line, const char* fileName, Args&& ...args){
    std::ostringstream stream;
    stream << fileName << "(" << line << ")::WARN::";
    (stream << ... << std::forward<Args>(args)) << '\n';

    printf(stream.str().c_str());
}

template <typename ...Args>
void fault(int line, const char* fileName, Args&& ...args){
    std::ostringstream stream;
    stream << fileName << "(" << line << ")::FAULT::";
    (stream << ... << std::forward<Args>(args)) << '\n';

    printf(stream.str().c_str());
}