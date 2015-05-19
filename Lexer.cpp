#include "Lexer.h"
#include <algorithm>
#include <iostream>

Lexer::Lexer(std::wstringstream &str)
    : str(str) {

}

Token Lexer::getNextToken() {
    std::wstring value;

    while (tryAppend(value, str.get())) { }


    auto it = std::find_if(domains.begin(), domains.end(), [&] (auto &domain) {
        return domain.match(value, true);
    });

    if (it != domains.end()) {
        str.unget();
        std::wcout << L"Token: {" << it->type << L", " << value << L"}" << std::endl;
        return {it->type, value, str.tellg()};
    } else {
        return {Token::UNKNOWN, value, str.tellg()};
    }
}

bool Lexer::tryAppend(std::wstring &value, wchar_t ch) {
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

