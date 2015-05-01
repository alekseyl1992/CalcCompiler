#ifndef LEXER_H
#define LEXER_H
#include <sstream>
#include <vector>
#include <string>
#include <regex>
#include "Token.h"

class Lexer
{
public:
    Lexer(std::stringstream &str);

    Token getNextToken();

private:
    bool tryAppend(std::string &value, char ch);

    std::stringstream &str;

    struct Domain {
        Token::Type type;

        std::regex regex;
        std::string exact;
        bool isRegex;

        Domain(Token::Type type, std::string value, bool isRegex=false)
            : type(type), isRegex(isRegex) {
            if (isRegex)
                regex = std::regex(value);
            else
                exact = value;
        }

        bool match(std::string str) {
            if (isRegex)
                return std::regex_match(str, regex);
            else
                return exact.find(str) == 0;
        }
    };

    std::vector<Domain> domains = {
        Domain(Token::BEGIN,         "begin"),
        Domain(Token::END,           "end"),
        Domain(Token::ARRAY,         "array"),
        Domain(Token::STRING,        "string"),
        Domain(Token::LINE_BREAK,    "\n"),
        Domain(Token::NUMBER,        "([0-9A-F]|\\.)+", true),
        Domain(Token::VARIABLE,      "[a-z]\\d{1,3}", true),
        Domain(Token::ASSIGN,        "="),
        Domain(Token::LABEL,         "(\\d)+\\:", true),
        Domain(Token::PLUS,          "+"),
        Domain(Token::MINUS,         "-"),
        Domain(Token::MULTIPLY,      "*"),
        Domain(Token::DIVIDE,        ""),
        Domain(Token::AND,           "&"),
        Domain(Token::OR,            "|"),
        Domain(Token::LBRACE,        "("),
        Domain(Token::RBRACE,        ")")
    };
};

#endif // LEXER_H
