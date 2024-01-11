#include "util.h"
#include <sstream>

std::vector<std::string> string_split(const std::string &str, char delimeter){
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;

    while(std::getline(ss, token, delimeter)){
        tokens.push_back(token);
    }

    return tokens;
}


