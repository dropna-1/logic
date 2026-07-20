#pragma once
#include <string>

struct Option {
    std::string text;
    int id;

    bool operator<(const Option& other){
        return id < other.id; 
    }
};