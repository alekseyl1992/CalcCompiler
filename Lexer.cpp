#include "Lexer.h"
#include <algorithm>

Lexer::Lexer(std::stringstream &str)
    : str(str) {

}

Token Lexer::getNextToken() {
    std::string value;

    while (tryAppend(value, str.get())) { }


    auto it = std::find_if(domains.begin(), domains.end(), [&] (auto &domain) {
        return domain.match(value);
    });

    if (it != domains.end()) {
        str.unget();
        return {it->type, value};
    } else
        throw("Unknown token: " + value);
}

bool Lexer::tryAppend(std::string &value, char ch) {
    if (ch == ' ') {
        if (value.empty())
            return true;  //skip space before token
        else
            return false;  //end of token
    }

    auto extendedValue = value + ch;

    bool found = std::any_of(domains.begin(), domains.end(), [&] (auto &domain) {
        return domain.match(extendedValue);
    });

    if (found)
        value += ch;


    return found;
}

